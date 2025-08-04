#include "MainWindow.h"
#include "ui_MainWindow.h" // The generated UI header

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Timer for live feed
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);

    // --- New: Setup the playback timer ---
    playbackTimer = new QTimer(this);
    connect(playbackTimer, &QTimer::timeout, this, &MainWindow::advancePlayback);

    // Populate the resolution dropdown
    ui->resolutionComboBox->addItem("640x480", QSize(640, 480));
    ui->resolutionComboBox->addItem("1280x720", QSize(1280, 720));
    ui->resolutionComboBox->addItem("1920x1080", QSize(1920, 1080));

    // Initial state of controls
    ui->pauseButton->setEnabled(false);
    ui->resolutionComboBox->setEnabled(false);
    setPlaybackControlsEnabled(false);

    statusBar()->showMessage("Ready. Press Play to begin.");
}

MainWindow::~MainWindow() {
    if (cap.isOpened()) {
        cap.release();
    }
    delete ui;
}

void MainWindow::setPlaybackControlsEnabled(bool enabled) {
    ui->rewindButton->setEnabled(enabled);
    ui->forwardButton->setEnabled(enabled);
    ui->timelineSlider->setEnabled(enabled);
}

// --- Modified: on_playButton_clicked now cleanly exits any playback mode ---
void MainWindow::on_playButton_clicked() {
    // Stop any playback that might be happening
    if (playbackTimer->isActive()) {
        playbackTimer->stop();
    }

    isPlaybackPaused = false;
    frameBuffer.clear();
    setPlaybackControlsEnabled(false);
    ui->pauseButton->setText("⏸️ Pause"); // Ensure button text is correct

    if (!cap.isOpened()) {
        initializeCamera();
    }

    if (cap.isOpened()) {
        on_resolutionComboBox_currentIndexChanged(ui->resolutionComboBox->currentIndex());
        timer->start(1000 / frameRate);
        ui->playButton->setEnabled(false);
        ui->pauseButton->setEnabled(true);
        ui->resolutionComboBox->setEnabled(true);
        ui->timelineLabel->setText("Time: Live");
        statusBar()->showMessage("Camera feed is live.");
    }
}

// --- Modified: on_pauseButton_clicked now has a dual role ---
void MainWindow::on_pauseButton_clicked() {
    // Case 1: We are in the live feed, so pause it.
    if (!isPlaybackPaused) {
        timer->stop();
        isPlaybackPaused = true;
        ui->playButton->setEnabled(true);
        ui->pauseButton->setText("▶️ Resume Playback"); // Change text for new role

        if (!frameBuffer.empty()) {
            setPlaybackControlsEnabled(true);
            ui->timelineSlider->setRange(0, frameBuffer.size() - 1);
            ui->timelineSlider->setValue(frameBuffer.size() - 1);
            updatePlaybackFrame(frameBuffer.size() - 1);
        }
        statusBar()->showMessage("Feed paused. Use timeline or resume playback.");
    }
    // Case 2: We are already paused, so toggle playback of the buffer.
    else {
        if (playbackTimer->isActive()) {
            playbackTimer->stop();
            ui->pauseButton->setText("▶️ Resume Playback");
        }
        else {
            // Don't start if we are at the very end of the timeline
            if (ui->timelineSlider->value() >= ui->timelineSlider->maximum()) {
                return;
            }
            playbackTimer->start(1000 / frameRate);
            ui->pauseButton->setText("⏸️ Pause");
        }
    }
}

// Rewind button skips back 1 second
void MainWindow::on_rewindButton_clicked() {
    playbackTimer->stop();
    ui->pauseButton->setText("▶️ Resume Playback");
    ui->timelineSlider->setValue(ui->timelineSlider->value() - frameRate);
}

// Forward button skips forward 1 second
void MainWindow::on_forwardButton_clicked() {
    playbackTimer->stop();
    ui->pauseButton->setText("▶️ Resume Playback");
    ui->timelineSlider->setValue(ui->timelineSlider->value() + frameRate);
}


void MainWindow::initializeCamera() {
    cap.open(0);
    if (!cap.isOpened()) {
        QMessageBox::critical(this, "Camera Error", "Unable to access the camera!");
    }
}

void MainWindow::updateFrame() {
    if (!isPlaybackPaused) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            statusBar()->showMessage("Error: Could not grab frame from camera.");
            return;
        }
        frameBuffer.push_back(frame);
        if (frameBuffer.size() > bufferSize) {
            frameBuffer.erase(frameBuffer.begin());
        }
        updatePlaybackFrame(frameBuffer.size() - 1);
    }
}

// --- New: This function moves the timeline slider forward during playback ---
void MainWindow::advancePlayback() {
    int currentValue = ui->timelineSlider->value();
    if (currentValue < ui->timelineSlider->maximum()) {
        ui->timelineSlider->setValue(currentValue + 1);
    }
    else {
        playbackTimer->stop();
        ui->pauseButton->setText("▶️ Resume Playback");
    }
}

void MainWindow::on_timelineSlider_valueChanged(int value) {
    updatePlaybackFrame(value);
}

void MainWindow::updatePlaybackFrame(int frameIndex) {
    if (frameIndex < 0 || frameIndex >= frameBuffer.size()) {
        return;
    }
    cv::Mat frame = frameBuffer[frameIndex].clone();
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    ui->cameraFeedLabel->setPixmap(QPixmap::fromImage(qimg).scaled(
        ui->cameraFeedLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    if (isPlaybackPaused) {
        float timeOffset = -1.0f * (frameBuffer.size() - 1 - frameIndex) / frameRate;
        ui->timelineLabel->setText(QString("Time: %1s").arg(timeOffset, 0, 'f', 1));
    }
    else {
        ui->timelineLabel->setText("Time: Live");
    }
}

void MainWindow::on_resolutionComboBox_currentIndexChanged(int index) {
    if (index < 0 || !timer->isActive() || isPlaybackPaused) return;
    QSize resolution = ui->resolutionComboBox->itemData(index).toSize();
    setCameraResolution(resolution.width(), resolution.height());
}

void MainWindow::setCameraResolution(int width, int height) {
    if (timer->isActive()) {
        timer->stop();
    }
    cap.release();
    cap.open(0);
    if (!cap.isOpened()) {
        QMessageBox::critical(this, "Camera Error", "Unable to re-open the camera after resolution change.");
        return;
    }
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    QString resText = QString("Current: %1x%2")
        .arg(cap.get(cv::CAP_PROP_FRAME_WIDTH))
        .arg(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    ui->currentResolutionLabel->setText(resText);
    timer->start(1000 / frameRate);
}
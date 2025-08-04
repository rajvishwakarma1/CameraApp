#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QStyle>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);

    playbackTimer = new QTimer(this);
    connect(playbackTimer, &QTimer::timeout, this, &MainWindow::advancePlayback);

    ui->resolutionComboBox->addItem("640x480", QSize(640, 480));
    ui->resolutionComboBox->addItem("1280x720", QSize(1280, 720));
    ui->resolutionComboBox->addItem("1920x1080", QSize(1920, 1080));

    applyStylesheet();
    setupIconsAndTooltips();

    updateButtonStates();
    statusBar()->showMessage("Ready. Press Live Stream to begin.");
}

void MainWindow::setupIconsAndTooltips() {
    const QSize iconSize(16, 16);
    ui->playButton->setIconSize(iconSize);
    ui->pauseButton->setIconSize(iconSize);
    ui->resumeButton->setIconSize(iconSize);
    ui->rewindButton->setIconSize(iconSize);
    ui->forwardButton->setIconSize(iconSize);

    ui->playButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pauseButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaPause));
    ui->resumeButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaPlay));
    ui->rewindButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->forwardButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaSeekForward));

    ui->playButton->setToolTip("Start or return to the live stream");
    ui->pauseButton->setToolTip("Pause live feed or buffered playback");
    ui->resumeButton->setToolTip("Resume buffered playback");
    ui->rewindButton->setToolTip("Skip back 1 second in buffer");
    ui->forwardButton->setToolTip("Skip forward 1 second in buffer");
}

// --- THIS IS THE NEW STYLESHEET USING YOUR BLUE/GRAY PALETTE ---
void MainWindow::applyStylesheet() {
    /*
     * [cite_start]Color Palette Used: [cite: 36]
     * #536B78 (Payne's gray)    - Backgrounds
     * #FFFFFF (White)            - Main Text (for contrast)
     * #637081 (Payne's gray)    - Subtle Borders / Disabled state
     * #7C98B3 (Air superiority) - Buttons & Highlights
    */
    QString style = R"(
        QMainWindow, QStatusBar {
            background-color: #536B78; /* Payne's gray */
            color: #FFFFFF;
        }
        #headerFrame, #footerFrame {
            background-color: #637081; /* Lighter Payne's gray */
        }
        #headerTitle {
            font-size: 18px;
            font-weight: bold;
            color: white;
            padding: 5px;
        }
        QLabel {
            color: white;
        }
        #cameraFeedLabel {
            background-color: black;
            color: white;
            font-size: 20px;
        }
        QPushButton {
            background-color: #7C98B3; /* Air superiority blue */
            color: #FFFFFF;
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #8FB0C8; /* Lighter version of the blue */
        }
        QPushButton:disabled {
            background-color: #637081; /* Lighter Payne's gray */
            color: #9099A2;
        }
        Line {
            background-color: #536B78;
        }
        QComboBox {
            background-color: #536B78;
            color: white;
            border: 1px solid #637081;
            padding: 5px;
            border-radius: 3px;
        }
        QComboBox::drop-down {
            border: none;
        }
        QComboBox QAbstractItemView {
             background-color: #536B78;
             border: 1px solid #637081;
             selection-background-color: #7C98B3;
        }
        QSlider::groove:horizontal {
            border: 1px solid #637081;
            height: 6px;
            background: #536B78;
            margin: 2px 0;
            border-radius: 3px;
        }
        QSlider::handle:horizontal {
            background: #7C98B3; /* Air superiority blue */
            border: 1px solid #7C98B3;
            width: 16px;
            margin: -6px 0;
            border-radius: 8px;
        }
    )";
    this->setStyleSheet(style);
}

// --- ALL LOGIC BELOW THIS LINE REMAINS UNCHANGED ---

MainWindow::~MainWindow() {
    if (cap.isOpened()) cap.release();
    delete ui;
}

void MainWindow::updateButtonStates() {
    bool isLive = timer->isActive();
    bool isPlayingBack = playbackTimer->isActive();
    ui->playButton->setEnabled(!isLive);
    ui->pauseButton->setEnabled(isLive || isPlayingBack);
    ui->resumeButton->setEnabled(isPlaybackPaused && !isPlayingBack);
    bool playbackControlsEnabled = isPlaybackPaused;
    ui->rewindButton->setEnabled(playbackControlsEnabled);
    ui->forwardButton->setEnabled(playbackControlsEnabled);
    ui->timelineSlider->setEnabled(playbackControlsEnabled);
    ui->resolutionComboBox->setEnabled(isLive);
}

void MainWindow::on_playButton_clicked() {
    if (playbackTimer->isActive()) playbackTimer->stop();
    isPlaybackPaused = false;
    frameBuffer.clear();
    if (!cap.isOpened()) initializeCamera();
    if (cap.isOpened()) {
        on_resolutionComboBox_currentIndexChanged(ui->resolutionComboBox->currentIndex());
        timer->start(1000 / frameRate);
        ui->timelineLabel->setText("Time: Live");
        statusBar()->showMessage("Camera feed is live.");
    }
    updateButtonStates();
}

void MainWindow::on_pauseButton_clicked() {
    if (timer->isActive()) {
        timer->stop();
        isPlaybackPaused = true;
        if (!frameBuffer.empty()) {
            ui->timelineSlider->setRange(0, frameBuffer.size() - 1);
            ui->timelineSlider->setValue(frameBuffer.size() - 1);
            updatePlaybackFrame(frameBuffer.size() - 1);
        }
        statusBar()->showMessage("Feed paused. Use timeline or resume playback.");
    }
    else if (playbackTimer->isActive()) {
        playbackTimer->stop();
        statusBar()->showMessage("Playback paused.");
    }
    updateButtonStates();
}

void MainWindow::on_resumeButton_clicked() {
    if (isPlaybackPaused && !playbackTimer->isActive()) {
        if (ui->timelineSlider->value() >= ui->timelineSlider->maximum()) return;
        playbackTimer->start(1000 / frameRate);
        statusBar()->showMessage("Resuming playback...");
        updateButtonStates();
    }
}

void MainWindow::on_rewindButton_clicked() {
    if (playbackTimer->isActive()) playbackTimer->stop();
    ui->timelineSlider->setValue(ui->timelineSlider->value() - frameRate);
    updateButtonStates();
}

void MainWindow::on_forwardButton_clicked() {
    if (playbackTimer->isActive()) playbackTimer->stop();
    ui->timelineSlider->setValue(ui->timelineSlider->value() + frameRate);
    updateButtonStates();
}

void MainWindow::initializeCamera() {
    cap.open(0);
    if (!cap.isOpened()) QMessageBox::critical(this, "Camera Error", "Unable to access the camera!");
}

void MainWindow::updateFrame() {
    if (isPlaybackPaused) return;
    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) {
        statusBar()->showMessage("Error: Could not grab frame from camera.");
        return;
    }
    frameBuffer.push_back(frame);
    if (frameBuffer.size() > bufferSize) frameBuffer.erase(frameBuffer.begin());
    updatePlaybackFrame(frameBuffer.size() - 1);
}

void MainWindow::advancePlayback() {
    int currentValue = ui->timelineSlider->value();
    if (currentValue < ui->timelineSlider->maximum()) {
        ui->timelineSlider->setValue(currentValue + 1);
    }
    else {
        playbackTimer->stop();
        updateButtonStates();
    }
}

void MainWindow::on_timelineSlider_valueChanged(int value) {
    updatePlaybackFrame(value);
}

void MainWindow::updatePlaybackFrame(int frameIndex) {
    if (frameIndex < 0 || frameIndex >= frameBuffer.size()) return;
    cv::Mat frame = frameBuffer[frameIndex].clone();
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    ui->cameraFeedLabel->setPixmap(QPixmap::fromImage(qimg).scaled(ui->cameraFeedLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

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
    if (timer->isActive()) timer->stop();
    cap.release();
    cap.open(0);
    if (!cap.isOpened()) {
        QMessageBox::critical(this, "Camera Error", "Unable to re-open the camera.");
        return;
    }
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    QString resText = QString("Current: %1x%2").arg(cap.get(cv::CAP_PROP_FRAME_WIDTH)).arg(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    ui->currentResolutionLabel->setText(resText);
    timer->start(1000 / frameRate);
}
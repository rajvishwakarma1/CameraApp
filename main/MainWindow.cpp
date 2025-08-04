#include "MainWindow.h"
#include "ui_MainWindow.h" // The generated UI header

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Initialize the timer but don't start it yet
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);

    // Populate the resolution dropdown [cite: 28]
    ui->resolutionComboBox->addItem("640x480", QSize(640, 480));
    ui->resolutionComboBox->addItem("1280x720", QSize(1280, 720));
    ui->resolutionComboBox->addItem("1920x1080", QSize(1920, 1080));

    // Disable controls that shouldn't be used until the camera is on
    ui->pauseButton->setEnabled(false);
    ui->resolutionComboBox->setEnabled(false);

    // As per requirements, Forward/Rewind buttons exist but are nonsensical for a live feed.
    // They are disabled to reflect this. [cite: 8, 9, 21, 23]
    ui->forwardButton->setEnabled(false);
    ui->rewindButton->setEnabled(false);
    statusBar()->showMessage("Ready. Press Play to begin.");
}

MainWindow::~MainWindow() {
    // Release resources
    if (cap.isOpened()) {
        cap.release();
    }
    delete ui;
}

// Play button starts or resumes the camera feed [cite: 18]
void MainWindow::on_playButton_clicked() {
    if (!cap.isOpened()) {
        initializeCamera();
    }
    if (cap.isOpened()) {
        // The resume functionality is handled here too [cite: 20]
        timer->start(30); // Update roughly 33 times per second
        ui->playButton->setEnabled(false);
        ui->pauseButton->setEnabled(true);
        ui->resolutionComboBox->setEnabled(true);
        statusBar()->showMessage("Camera feed is live.");
    }
}

// Pause button freezes the current frame [cite: 19]
void MainWindow::on_pauseButton_clicked() {
    timer->stop();
    ui->playButton->setEnabled(true); // Re-enable play to act as resume
    ui->playButton->setText("▶️ Resume");
    ui->pauseButton->setEnabled(false);
    statusBar()->showMessage("Feed paused.");
}


void MainWindow::initializeCamera() {
    // Open the default camera (ID 0)
    cap.open(0);

    // Error Handling: Check if camera was successfully opened [cite: 36, 59]
    if (!cap.isOpened()) {
        QMessageBox::critical(this, "Camera Error", "Unable to access the camera!");
        return;
    }
    // Set initial resolution from the dropdown
    on_resolutionComboBox_currentIndexChanged(ui->resolutionComboBox->currentIndex());
}


// Main loop to capture and display frames [cite: 16]
void MainWindow::updateFrame() {
    cv::Mat frame;
    cap >> frame; // Capture a new frame

    if (frame.empty()) {
        // Handle error if frame is empty
        statusBar()->showMessage("Error: Could not grab frame.");
        return;
    }

    // Convert the OpenCV frame (BGR) to a QImage (RGB)
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);

    // Display the QImage in the QLabel, scaling it to fit the label's size
    ui->cameraFeedLabel->setPixmap(QPixmap::fromImage(qimg).scaled(
        ui->cameraFeedLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

// Slot to handle resolution changes [cite: 25]
void MainWindow::on_resolutionComboBox_currentIndexChanged(int index) {
    if (index < 0) return;

    QSize resolution = ui->resolutionComboBox->itemData(index).toSize();
    setCameraResolution(resolution.width(), resolution.height());
}

void MainWindow::setCameraResolution(int width, int height) {
    if (cap.isOpened()) {
        cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    }

    // Update the label to show current resolution [cite: 27]
    QString resText = QString("Current: %1x%2")
        .arg(cap.get(cv::CAP_PROP_FRAME_WIDTH))
        .arg(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    ui->currentResolutionLabel->setText(resText);
}

// Forward/Rewind buttons are not applicable for a live feed. [cite: 41]
void MainWindow::on_forwardButton_clicked() {
    statusBar()->showMessage("Forward is not applicable for a live stream.");
}

void MainWindow::on_rewindButton_clicked() {
    statusBar()->showMessage("Rewind is not applicable for a live stream.");
}
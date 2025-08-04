#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <vector>
#include <opencv2/opencv.hpp>

// Forward declaration of the UI class generated from the .ui file
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void updateFrame();

    // Slots for button clicks
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_forwardButton_clicked();
    void on_rewindButton_clicked();
    void on_timelineSlider_valueChanged(int value);
    void on_resolutionComboBox_currentIndexChanged(int index);

    // --- New Slot for playback ---
    void advancePlayback();


private:
    void initializeCamera();
    void setCameraResolution(int width, int height);
    void updatePlaybackFrame(int frameIndex);
    void setPlaybackControlsEnabled(bool enabled);

    Ui::MainWindow* ui;
    cv::VideoCapture cap;
    QTimer* timer; // Timer for live feed capture

    // --- New timer for buffered playback ---
    QTimer* playbackTimer;

    // Frame buffer variables
    std::vector<cv::Mat> frameBuffer;
    static const int bufferSize = 300;
    bool isPlaybackPaused = false;
    int frameRate = 30;
};

#endif // MAINWINDOW_H
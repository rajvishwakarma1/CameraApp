#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <vector>
#include <opencv2/opencv.hpp>

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
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_resumeButton_clicked(); // New slot for the resume button
    void on_forwardButton_clicked();
    void on_rewindButton_clicked();
    void on_timelineSlider_valueChanged(int value);
    void on_resolutionComboBox_currentIndexChanged(int index);
    void advancePlayback();

private:
    void initializeCamera();
    void setCameraResolution(int width, int height);
    void updatePlaybackFrame(int frameIndex);
    void setPlaybackControlsEnabled(bool enabled);
    void applyStylesheet();
    void setupIconsAndTooltips();
    void updateButtonStates();

    Ui::MainWindow* ui;
    cv::VideoCapture cap;
    QTimer* timer;
    QTimer* playbackTimer;

    std::vector<cv::Mat> frameBuffer;
    static const int bufferSize = 300;
    bool isPlaybackPaused = false;
    int frameRate = 30;
};

#endif 
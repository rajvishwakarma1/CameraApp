#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
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
    // Slot to update the camera feed display
    void updateFrame();

    // Slots for button clicks, automatically connected by Qt from the .ui file
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_forwardButton_clicked();
    void on_rewindButton_clicked();

    // Slot for when the resolution is changed in the dropdown
    void on_resolutionComboBox_currentIndexChanged(int index);

private:
    void initializeCamera();
    void setCameraResolution(int width, int height);

    Ui::MainWindow* ui; // Pointer to the UI elements
    cv::VideoCapture cap; // OpenCV video capture object
    QTimer* timer; // Timer to trigger frame updates
};

#endif // MAINWINDOW_H
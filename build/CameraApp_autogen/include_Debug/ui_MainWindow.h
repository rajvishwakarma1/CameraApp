/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *cameraFeedLabel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *timelineLabel;
    QSlider *timelineSlider;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *resumeButton;
    QPushButton *rewindButton;
    QPushButton *forwardButton;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *resolutionComboBox;
    QLabel *currentResolutionLabel;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1300, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        cameraFeedLabel = new QLabel(centralwidget);
        cameraFeedLabel->setObjectName("cameraFeedLabel");
        cameraFeedLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(cameraFeedLabel);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        timelineLabel = new QLabel(centralwidget);
        timelineLabel->setObjectName("timelineLabel");
        timelineLabel->setMinimumSize(QSize(80, 0));

        horizontalLayout_4->addWidget(timelineLabel);

        timelineSlider = new QSlider(centralwidget);
        timelineSlider->setObjectName("timelineSlider");
        timelineSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(timelineSlider);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        playButton = new QPushButton(groupBox);
        playButton->setObjectName("playButton");

        horizontalLayout_2->addWidget(playButton);

        pauseButton = new QPushButton(groupBox);
        pauseButton->setObjectName("pauseButton");

        horizontalLayout_2->addWidget(pauseButton);

        resumeButton = new QPushButton(groupBox);
        resumeButton->setObjectName("resumeButton");

        horizontalLayout_2->addWidget(resumeButton);

        rewindButton = new QPushButton(groupBox);
        rewindButton->setObjectName("rewindButton");

        horizontalLayout_2->addWidget(rewindButton);

        forwardButton = new QPushButton(groupBox);
        forwardButton->setObjectName("forwardButton");

        horizontalLayout_2->addWidget(forwardButton);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        resolutionComboBox = new QComboBox(groupBox_2);
        resolutionComboBox->setObjectName("resolutionComboBox");

        horizontalLayout_3->addWidget(resolutionComboBox);

        currentResolutionLabel = new QLabel(groupBox_2);
        currentResolutionLabel->setObjectName("currentResolutionLabel");

        horizontalLayout_3->addWidget(currentResolutionLabel);


        horizontalLayout->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Camera Feed App", nullptr));
        cameraFeedLabel->setText(QCoreApplication::translate("MainWindow", "Camera is off. Press Live Stream to start.", nullptr));
        timelineLabel->setText(QCoreApplication::translate("MainWindow", "Time: --", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Playback Controls", nullptr));
        playButton->setText(QCoreApplication::translate("MainWindow", "Live Stream", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        resumeButton->setText(QCoreApplication::translate("MainWindow", "Resume", nullptr));
        rewindButton->setText(QCoreApplication::translate("MainWindow", "Rewind", nullptr));
        forwardButton->setText(QCoreApplication::translate("MainWindow", "Forward", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Camera Settings", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Resolution:", nullptr));
        currentResolutionLabel->setText(QCoreApplication::translate("MainWindow", "Current: N/A", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QFrame *headerFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *headerTitle;
    QSpacerItem *horizontalSpacer;
    QLabel *cameraFeedLabel;
    QFrame *footerFrame;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *timelineLayout;
    QLabel *timelineLabel;
    QSlider *timelineSlider;
    QHBoxLayout *controlsLayout;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *resumeButton;
    QFrame *separator1;
    QPushButton *rewindButton;
    QPushButton *forwardButton;
    QSpacerItem *horizontalSpacer_2;
    QLabel *resolutionLabel;
    QComboBox *resolutionComboBox;
    QLabel *currentResolutionLabel;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        headerFrame = new QFrame(centralwidget);
        headerFrame->setObjectName("headerFrame");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(headerFrame->sizePolicy().hasHeightForWidth());
        headerFrame->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(headerFrame);
        horizontalLayout->setObjectName("horizontalLayout");
        headerTitle = new QLabel(headerFrame);
        headerTitle->setObjectName("headerTitle");

        horizontalLayout->addWidget(headerTitle);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        mainLayout->addWidget(headerFrame);

        cameraFeedLabel = new QLabel(centralwidget);
        cameraFeedLabel->setObjectName("cameraFeedLabel");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cameraFeedLabel->sizePolicy().hasHeightForWidth());
        cameraFeedLabel->setSizePolicy(sizePolicy1);
        cameraFeedLabel->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(cameraFeedLabel);

        footerFrame = new QFrame(centralwidget);
        footerFrame->setObjectName("footerFrame");
        sizePolicy.setHeightForWidth(footerFrame->sizePolicy().hasHeightForWidth());
        footerFrame->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(footerFrame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        timelineLayout = new QHBoxLayout();
        timelineLayout->setObjectName("timelineLayout");
        timelineLabel = new QLabel(footerFrame);
        timelineLabel->setObjectName("timelineLabel");
        timelineLabel->setMinimumSize(QSize(100, 0));
        timelineLabel->setAlignment(Qt::AlignCenter);

        timelineLayout->addWidget(timelineLabel);

        timelineSlider = new QSlider(footerFrame);
        timelineSlider->setObjectName("timelineSlider");
        timelineSlider->setOrientation(Qt::Horizontal);

        timelineLayout->addWidget(timelineSlider);


        verticalLayout_2->addLayout(timelineLayout);

        controlsLayout = new QHBoxLayout();
        controlsLayout->setSpacing(15);
        controlsLayout->setObjectName("controlsLayout");
        playButton = new QPushButton(footerFrame);
        playButton->setObjectName("playButton");

        controlsLayout->addWidget(playButton);

        pauseButton = new QPushButton(footerFrame);
        pauseButton->setObjectName("pauseButton");

        controlsLayout->addWidget(pauseButton);

        resumeButton = new QPushButton(footerFrame);
        resumeButton->setObjectName("resumeButton");

        controlsLayout->addWidget(resumeButton);

        separator1 = new QFrame(footerFrame);
        separator1->setObjectName("separator1");
        separator1->setFrameShape(QFrame::Shape::VLine);
        separator1->setFrameShadow(QFrame::Shadow::Sunken);

        controlsLayout->addWidget(separator1);

        rewindButton = new QPushButton(footerFrame);
        rewindButton->setObjectName("rewindButton");

        controlsLayout->addWidget(rewindButton);

        forwardButton = new QPushButton(footerFrame);
        forwardButton->setObjectName("forwardButton");

        controlsLayout->addWidget(forwardButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        controlsLayout->addItem(horizontalSpacer_2);

        resolutionLabel = new QLabel(footerFrame);
        resolutionLabel->setObjectName("resolutionLabel");

        controlsLayout->addWidget(resolutionLabel);

        resolutionComboBox = new QComboBox(footerFrame);
        resolutionComboBox->setObjectName("resolutionComboBox");
        resolutionComboBox->setMinimumSize(QSize(120, 0));

        controlsLayout->addWidget(resolutionComboBox);

        currentResolutionLabel = new QLabel(footerFrame);
        currentResolutionLabel->setObjectName("currentResolutionLabel");
        currentResolutionLabel->setMinimumSize(QSize(120, 0));

        controlsLayout->addWidget(currentResolutionLabel);


        verticalLayout_2->addLayout(controlsLayout);


        mainLayout->addWidget(footerFrame);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "VisionApp", nullptr));
        headerTitle->setText(QCoreApplication::translate("MainWindow", "QT Webcam + Player", nullptr));
        cameraFeedLabel->setText(QCoreApplication::translate("MainWindow", "Press Live Stream to Begin", nullptr));
        timelineLabel->setText(QCoreApplication::translate("MainWindow", "Time: --", nullptr));
        playButton->setText(QCoreApplication::translate("MainWindow", "Live Stream", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        resumeButton->setText(QCoreApplication::translate("MainWindow", "Resume", nullptr));
        rewindButton->setText(QCoreApplication::translate("MainWindow", "Rewind", nullptr));
        forwardButton->setText(QCoreApplication::translate("MainWindow", "Forward", nullptr));
        resolutionLabel->setText(QCoreApplication::translate("MainWindow", "Resolution:", nullptr));
        currentResolutionLabel->setText(QCoreApplication::translate("MainWindow", "Current: N/A", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'pravekshaui.ui'
**
** Created: Wed Dec 4 09:26:13 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRAVEKSHAUI_H
#define UI_PRAVEKSHAUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PravekshaUIClass
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tbGeneral;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnStartCallibration;
    QPushButton *btnStopCallibration;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnStat;
    QListView *lstLog;
    QLabel *label;
    QLabel *lblImage;
    QWidget *tbStat;
    QWidget *widgetGraph;
    QLabel *label_2;
    QLabel *label_3;
    QLCDNumber *txtTotVehicles;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLCDNumber *txtWrongLane;
    QLCDNumber *txtHighSpeed;
    QLCDNumber *txtBoth;
    QFrame *line;
    QFrame *line_2;
    QWidget *tbSettings;
    QPushButton *btnSetLoggerPath;
    QPushButton *btnSetDistance;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *txtLoggerPath;
    QPushButton *btnBrowse;
    QLineEdit *txtDistance;
    QLineEdit *txtPath;
    QLabel *label1_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PravekshaUIClass)
    {
        if (PravekshaUIClass->objectName().isEmpty())
            PravekshaUIClass->setObjectName(QString::fromUtf8("PravekshaUIClass"));
        PravekshaUIClass->resize(836, 540);
        centralWidget = new QWidget(PravekshaUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 821, 461));
        tbGeneral = new QWidget();
        tbGeneral->setObjectName(QString::fromUtf8("tbGeneral"));
        layoutWidget = new QWidget(tbGeneral);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 801, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnStartCallibration = new QPushButton(layoutWidget);
        btnStartCallibration->setObjectName(QString::fromUtf8("btnStartCallibration"));

        horizontalLayout_2->addWidget(btnStartCallibration);

        btnStopCallibration = new QPushButton(layoutWidget);
        btnStopCallibration->setObjectName(QString::fromUtf8("btnStopCallibration"));

        horizontalLayout_2->addWidget(btnStopCallibration);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnStat = new QPushButton(layoutWidget);
        btnStat->setObjectName(QString::fromUtf8("btnStat"));

        horizontalLayout_2->addWidget(btnStat);

        lstLog = new QListView(tbGeneral);
        lstLog->setObjectName(QString::fromUtf8("lstLog"));
        lstLog->setGeometry(QRect(10, 60, 341, 361));
        label = new QLabel(tbGeneral);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 81, 16));
        lblImage = new QLabel(tbGeneral);
        lblImage->setObjectName(QString::fromUtf8("lblImage"));
        lblImage->setGeometry(QRect(360, 60, 441, 251));
        lblImage->setScaledContents(true);
        tabWidget->addTab(tbGeneral, QString());
        tbStat = new QWidget();
        tbStat->setObjectName(QString::fromUtf8("tbStat"));
        widgetGraph = new QWidget(tbStat);
        widgetGraph->setObjectName(QString::fromUtf8("widgetGraph"));
        widgetGraph->setGeometry(QRect(360, 30, 451, 361));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetGraph->sizePolicy().hasHeightForWidth());
        widgetGraph->setSizePolicy(sizePolicy);
        widgetGraph->setAutoFillBackground(false);
        label_2 = new QLabel(tbStat);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 20, 261, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setTextFormat(Qt::RichText);
        label_3 = new QLabel(tbStat);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 90, 171, 21));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_3->setFont(font1);
        txtTotVehicles = new QLCDNumber(tbStat);
        txtTotVehicles->setObjectName(QString::fromUtf8("txtTotVehicles"));
        txtTotVehicles->setGeometry(QRect(230, 90, 64, 23));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        txtTotVehicles->setFont(font2);
        txtTotVehicles->setNumDigits(4);
        txtTotVehicles->setProperty("value", QVariant(0));
        label_4 = new QLabel(tbStat);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 210, 101, 21));
        QFont font3;
        font3.setPointSize(9);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setWeight(75);
        label_4->setFont(font3);
        label_5 = new QLabel(tbStat);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 250, 101, 21));
        QFont font4;
        font4.setPointSize(9);
        font4.setBold(true);
        font4.setWeight(75);
        label_5->setFont(font4);
        label_6 = new QLabel(tbStat);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 290, 201, 21));
        label_6->setFont(font4);
        label_7 = new QLabel(tbStat);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(120, 180, 61, 16));
        label_7->setFont(font1);
        txtWrongLane = new QLCDNumber(tbStat);
        txtWrongLane->setObjectName(QString::fromUtf8("txtWrongLane"));
        txtWrongLane->setGeometry(QRect(230, 210, 64, 23));
        txtWrongLane->setFont(font2);
        txtWrongLane->setNumDigits(4);
        txtHighSpeed = new QLCDNumber(tbStat);
        txtHighSpeed->setObjectName(QString::fromUtf8("txtHighSpeed"));
        txtHighSpeed->setGeometry(QRect(230, 250, 64, 23));
        txtHighSpeed->setFont(font2);
        txtHighSpeed->setNumDigits(4);
        txtBoth = new QLCDNumber(tbStat);
        txtBoth->setObjectName(QString::fromUtf8("txtBoth"));
        txtBoth->setGeometry(QRect(230, 290, 64, 23));
        txtBoth->setFont(font2);
        txtBoth->setAutoFillBackground(false);
        txtBoth->setNumDigits(4);
        txtBoth->setSegmentStyle(QLCDNumber::Filled);
        line = new QFrame(tbStat);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 130, 321, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(tbStat);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(340, 20, 20, 381));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        tabWidget->addTab(tbStat, QString());
        tbSettings = new QWidget();
        tbSettings->setObjectName(QString::fromUtf8("tbSettings"));
        btnSetLoggerPath = new QPushButton(tbSettings);
        btnSetLoggerPath->setObjectName(QString::fromUtf8("btnSetLoggerPath"));
        btnSetLoggerPath->setGeometry(QRect(400, 71, 41, 23));
        btnSetDistance = new QPushButton(tbSettings);
        btnSetDistance->setObjectName(QString::fromUtf8("btnSetDistance"));
        btnSetDistance->setGeometry(QRect(190, 41, 41, 23));
        label_8 = new QLabel(tbSettings);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 41, 46, 13));
        label_9 = new QLabel(tbSettings);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 71, 61, 16));
        txtLoggerPath = new QLineEdit(tbSettings);
        txtLoggerPath->setObjectName(QString::fromUtf8("txtLoggerPath"));
        txtLoggerPath->setGeometry(QRect(80, 71, 321, 20));
        txtLoggerPath->setCursorPosition(32);
        btnBrowse = new QPushButton(tbSettings);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setGeometry(QRect(570, 11, 21, 23));
        QFont font5;
        font5.setPointSize(8);
        font5.setKerning(true);
        font5.setStyleStrategy(QFont::PreferDefault);
        btnBrowse->setFont(font5);
        btnBrowse->setLayoutDirection(Qt::LeftToRight);
        txtDistance = new QLineEdit(tbSettings);
        txtDistance->setObjectName(QString::fromUtf8("txtDistance"));
        txtDistance->setGeometry(QRect(80, 41, 111, 20));
        txtPath = new QLineEdit(tbSettings);
        txtPath->setObjectName(QString::fromUtf8("txtPath"));
        txtPath->setGeometry(QRect(80, 11, 491, 20));
        txtPath->setReadOnly(true);
        label1_2 = new QLabel(tbSettings);
        label1_2->setObjectName(QString::fromUtf8("label1_2"));
        label1_2->setGeometry(QRect(10, 10, 51, 23));
        tabWidget->addTab(tbSettings, QString());
        PravekshaUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PravekshaUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 836, 21));
        PravekshaUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PravekshaUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PravekshaUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PravekshaUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PravekshaUIClass->setStatusBar(statusBar);

        retranslateUi(PravekshaUIClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PravekshaUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *PravekshaUIClass)
    {
        PravekshaUIClass->setWindowTitle(QApplication::translate("PravekshaUIClass", "Praveksha", 0, QApplication::UnicodeUTF8));
        btnStartCallibration->setText(QApplication::translate("PravekshaUIClass", "Start Callibration", 0, QApplication::UnicodeUTF8));
        btnStopCallibration->setText(QApplication::translate("PravekshaUIClass", "Stop Callibration", 0, QApplication::UnicodeUTF8));
        btnStat->setText(QApplication::translate("PravekshaUIClass", "Refresh Stat", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PravekshaUIClass", "Violations :", 0, QApplication::UnicodeUTF8));
        lblImage->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tbGeneral), QApplication::translate("PravekshaUIClass", "General", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PravekshaUIClass", "Statistics for the past 24 hours", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("PravekshaUIClass", "Total Number of Vehicles:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("PravekshaUIClass", "1 - Wrong Lane", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PravekshaUIClass", "2 - High Speed", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("PravekshaUIClass", "3 - High Speed and Wrong Lane", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("PravekshaUIClass", "Legend", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tbStat), QApplication::translate("PravekshaUIClass", "Statistics", 0, QApplication::UnicodeUTF8));
        btnSetLoggerPath->setText(QApplication::translate("PravekshaUIClass", "Set", 0, QApplication::UnicodeUTF8));
        btnSetDistance->setText(QApplication::translate("PravekshaUIClass", "Set", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("PravekshaUIClass", "Distance", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("PravekshaUIClass", "Logger Path", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        txtLoggerPath->setToolTip(QApplication::translate("PravekshaUIClass", "Logger Path", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        txtLoggerPath->setText(QApplication::translate("PravekshaUIClass", "F:/20july2013_time_7am_9am/Logs/", 0, QApplication::UnicodeUTF8));
        btnBrowse->setText(QApplication::translate("PravekshaUIClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        txtDistance->setWhatsThis(QApplication::translate("PravekshaUIClass", "Length of the mapping region", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        txtDistance->setText(QApplication::translate("PravekshaUIClass", "50", 0, QApplication::UnicodeUTF8));
        txtPath->setText(QApplication::translate("PravekshaUIClass", "F:/20july2013_time_7am_9am/Export_2013-07-24_114637/0 - 2013-07-20 12-00-00-033.asf", 0, QApplication::UnicodeUTF8));
        label1_2->setText(QApplication::translate("PravekshaUIClass", "Video Path", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tbSettings), QApplication::translate("PravekshaUIClass", "Settings", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PravekshaUIClass: public Ui_PravekshaUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRAVEKSHAUI_H

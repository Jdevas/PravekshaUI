/********************************************************************************
** Form generated from reading UI file 'pravekshaui.ui'
**
** Created: Sat 30. Nov 11:44:01 2013
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
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
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
    QHBoxLayout *horizontalLayout;
    QLabel *label1;
    QLineEdit *txtPath;
    QPushButton *btnBrowse;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnStartCallibration;
    QPushButton *btnStopCallibration;
    QListView *lstLog;
    QLabel *label;
    QLabel *lblImage;
    QWidget *tbStat;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PravekshaUIClass)
    {
        if (PravekshaUIClass->objectName().isEmpty())
            PravekshaUIClass->setObjectName(QString::fromUtf8("PravekshaUIClass"));
        PravekshaUIClass->resize(871, 540);
        centralWidget = new QWidget(PravekshaUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 841, 461));
        tbGeneral = new QWidget();
        tbGeneral->setObjectName(QString::fromUtf8("tbGeneral"));
        layoutWidget = new QWidget(tbGeneral);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 641, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label1 = new QLabel(layoutWidget);
        label1->setObjectName(QString::fromUtf8("label1"));

        horizontalLayout->addWidget(label1);

        txtPath = new QLineEdit(layoutWidget);
        txtPath->setObjectName(QString::fromUtf8("txtPath"));
        txtPath->setReadOnly(true);

        horizontalLayout->addWidget(txtPath);

        btnBrowse = new QPushButton(layoutWidget);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));

        horizontalLayout->addWidget(btnBrowse);

        layoutWidget1 = new QWidget(tbGeneral);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(650, 20, 182, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnStartCallibration = new QPushButton(layoutWidget1);
        btnStartCallibration->setObjectName(QString::fromUtf8("btnStartCallibration"));

        horizontalLayout_2->addWidget(btnStartCallibration);

        btnStopCallibration = new QPushButton(layoutWidget1);
        btnStopCallibration->setObjectName(QString::fromUtf8("btnStopCallibration"));

        horizontalLayout_2->addWidget(btnStopCallibration);

        lstLog = new QListView(tbGeneral);
        lstLog->setObjectName(QString::fromUtf8("lstLog"));
        lstLog->setGeometry(QRect(10, 80, 241, 341));
        label = new QLabel(tbGeneral);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 60, 81, 16));
        lblImage = new QLabel(tbGeneral);
        lblImage->setObjectName(QString::fromUtf8("lblImage"));
        lblImage->setGeometry(QRect(300, 130, 481, 271));
        lblImage->setScaledContents(true);
        tabWidget->addTab(tbGeneral, QString());
        tbStat = new QWidget();
        tbStat->setObjectName(QString::fromUtf8("tbStat"));
        tabWidget->addTab(tbStat, QString());
        PravekshaUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PravekshaUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 871, 21));
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
        PravekshaUIClass->setWindowTitle(QApplication::translate("PravekshaUIClass", "PravekshaUI", 0, QApplication::UnicodeUTF8));
        label1->setText(QApplication::translate("PravekshaUIClass", "Video Path", 0, QApplication::UnicodeUTF8));
        txtPath->setText(QApplication::translate("PravekshaUIClass", "D:/Academic/FYP/Video/Export_2013-07-24_121107/0 - 2013-07-20 12-00-00-033.asf", 0, QApplication::UnicodeUTF8));
        btnBrowse->setText(QApplication::translate("PravekshaUIClass", "Browse", 0, QApplication::UnicodeUTF8));
        btnStartCallibration->setText(QApplication::translate("PravekshaUIClass", "Start Callibration", 0, QApplication::UnicodeUTF8));
        btnStopCallibration->setText(QApplication::translate("PravekshaUIClass", "Stop Callibration", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PravekshaUIClass", "Violations :", 0, QApplication::UnicodeUTF8));
        lblImage->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tbGeneral), QApplication::translate("PravekshaUIClass", "General", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tbStat), QApplication::translate("PravekshaUIClass", "Statistics", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PravekshaUIClass: public Ui_PravekshaUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRAVEKSHAUI_H

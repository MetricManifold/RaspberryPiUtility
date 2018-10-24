/********************************************************************************
** Form generated from reading UI file 'raspberrypiutility.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RASPBERRYPIUTILITY_H
#define UI_RASPBERRYPIUTILITY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RaspberryPiUtilityClass
{
public:
    QWidget *centralWidget;
    QTabWidget *tab_widget;
    QWidget *tab;
    QLCDNumber *pitch_dis;
    QLCDNumber *yaw_dis;
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *pitch_input;
    QDoubleSpinBox *yaw_input;
    QWidget *tab_2;
    QLabel *console;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *RaspberryPiUtilityClass)
    {
        if (RaspberryPiUtilityClass->objectName().isEmpty())
            RaspberryPiUtilityClass->setObjectName(QStringLiteral("RaspberryPiUtilityClass"));
        RaspberryPiUtilityClass->resize(600, 420);
        RaspberryPiUtilityClass->setMinimumSize(QSize(300, 200));
        centralWidget = new QWidget(RaspberryPiUtilityClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tab_widget = new QTabWidget(centralWidget);
        tab_widget->setObjectName(QStringLiteral("tab_widget"));
        tab_widget->setGeometry(QRect(10, 10, 571, 191));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pitch_dis = new QLCDNumber(tab);
        pitch_dis->setObjectName(QStringLiteral("pitch_dis"));
        pitch_dis->setGeometry(QRect(30, 60, 64, 23));
        yaw_dis = new QLCDNumber(tab);
        yaw_dis->setObjectName(QStringLiteral("yaw_dis"));
        yaw_dis->setGeometry(QRect(140, 60, 64, 23));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 61, 20));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(140, 30, 61, 20));
        label_2->setAlignment(Qt::AlignCenter);
        pitch_input = new QDoubleSpinBox(tab);
        pitch_input->setObjectName(QStringLiteral("pitch_input"));
        pitch_input->setGeometry(QRect(30, 100, 62, 22));
        yaw_input = new QDoubleSpinBox(tab);
        yaw_input->setObjectName(QStringLiteral("yaw_input"));
        yaw_input->setGeometry(QRect(140, 100, 62, 22));
        tab_widget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tab_widget->addTab(tab_2, QString());
        console = new QLabel(centralWidget);
        console->setObjectName(QStringLiteral("console"));
        console->setGeometry(QRect(10, 210, 571, 161));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        console->setPalette(palette);
        console->setAutoFillBackground(true);
        console->setFrameShape(QFrame::Box);
        console->setFrameShadow(QFrame::Plain);
        console->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        console->setWordWrap(true);
        console->setMargin(10);
        RaspberryPiUtilityClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(RaspberryPiUtilityClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RaspberryPiUtilityClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(RaspberryPiUtilityClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        RaspberryPiUtilityClass->setMenuBar(menuBar);

        retranslateUi(RaspberryPiUtilityClass);

        tab_widget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RaspberryPiUtilityClass);
    } // setupUi

    void retranslateUi(QMainWindow *RaspberryPiUtilityClass)
    {
        RaspberryPiUtilityClass->setWindowTitle(QApplication::translate("RaspberryPiUtilityClass", "RaspberryPiUtility", nullptr));
        label->setText(QApplication::translate("RaspberryPiUtilityClass", "Pitch", nullptr));
        label_2->setText(QApplication::translate("RaspberryPiUtilityClass", "Yaw", nullptr));
        tab_widget->setTabText(tab_widget->indexOf(tab), QApplication::translate("RaspberryPiUtilityClass", "Tab 1", nullptr));
        tab_widget->setTabText(tab_widget->indexOf(tab_2), QApplication::translate("RaspberryPiUtilityClass", "Tab 2", nullptr));
        console->setText(QApplication::translate("RaspberryPiUtilityClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RaspberryPiUtilityClass: public Ui_RaspberryPiUtilityClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RASPBERRYPIUTILITY_H

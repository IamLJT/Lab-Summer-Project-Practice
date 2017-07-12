/********************************************************************************
** Form generated from reading UI file 'plotwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTWINDOW_H
#define UI_PLOTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlotWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QWidget *widget;
    QPushButton *pushButton_2;
    QToolButton *toolButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PlotWindow)
    {
        if (PlotWindow->objectName().isEmpty())
            PlotWindow->setObjectName(QStringLiteral("PlotWindow"));
        PlotWindow->resize(500, 400);
        centralwidget = new QWidget(PlotWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(390, 80, 75, 23));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(100, 90, 181, 121));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(400, 160, 75, 23));
        toolButton = new QToolButton(centralwidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(410, 230, 41, 21));
        PlotWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PlotWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 500, 23));
        PlotWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PlotWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        PlotWindow->setStatusBar(statusbar);

        retranslateUi(PlotWindow);

        QMetaObject::connectSlotsByName(PlotWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PlotWindow)
    {
        PlotWindow->setWindowTitle(QApplication::translate("PlotWindow", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("PlotWindow", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("PlotWindow", "PushButton", Q_NULLPTR));
        toolButton->setText(QApplication::translate("PlotWindow", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PlotWindow: public Ui_PlotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTWINDOW_H

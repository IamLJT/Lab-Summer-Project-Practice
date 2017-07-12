/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *mainbutton;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *user_name;
    QLabel *label;
    QPushButton *pushButton_6;
    QTableWidget *tableWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 350);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 20, 461, 41));
        mainbutton = new QHBoxLayout(horizontalLayoutWidget);
        mainbutton->setSpacing(1);
        mainbutton->setContentsMargins(11, 11, 11, 11);
        mainbutton->setObjectName(QStringLiteral("mainbutton"));
        mainbutton->setContentsMargins(2, 0, 2, 1);
        pushButton_1 = new QPushButton(horizontalLayoutWidget);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));

        mainbutton->addWidget(pushButton_1);

        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        mainbutton->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(horizontalLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        mainbutton->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(horizontalLayoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        mainbutton->addWidget(pushButton_4);

        user_name = new QLabel(centralWidget);
        user_name->setObjectName(QStringLiteral("user_name"));
        user_name->setGeometry(QRect(80, 90, 83, 12));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 90, 36, 12));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(410, 70, 75, 23));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(30, 110, 341, 201));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(400, 130, 81, 151));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_5 = new QPushButton(verticalLayoutWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButton_1->setText(QApplication::translate("MainWindow", "\344\270\212\344\274\240", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\345\272\223", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "\345\267\245\345\205\267\347\256\261", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\347\231\273\345\275\225", Q_NULLPTR));
        user_name->setText(QString());
        label->setText(QApplication::translate("MainWindow", "\344\275\240\345\245\275\357\274\201", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\347\273\230\345\233\276", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

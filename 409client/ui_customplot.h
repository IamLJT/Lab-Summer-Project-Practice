/********************************************************************************
** Form generated from reading UI file 'customplot.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMPLOT_H
#define UI_CUSTOMPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomPlot
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *CustomPlot)
    {
        if (CustomPlot->objectName().isEmpty())
            CustomPlot->setObjectName(QStringLiteral("CustomPlot"));
        CustomPlot->resize(450, 350);
        pushButton = new QPushButton(CustomPlot);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 10, 75, 23));

        retranslateUi(CustomPlot);

        QMetaObject::connectSlotsByName(CustomPlot);
    } // setupUi

    void retranslateUi(QWidget *CustomPlot)
    {
        CustomPlot->setWindowTitle(QApplication::translate("CustomPlot", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CustomPlot", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CustomPlot: public Ui_CustomPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMPLOT_H

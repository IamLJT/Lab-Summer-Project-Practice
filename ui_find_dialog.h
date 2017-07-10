/********************************************************************************
** Form generated from reading UI file 'find_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIND_DIALOG_H
#define UI_FIND_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_find_dialog
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *find_dialog)
    {
        if (find_dialog->objectName().isEmpty())
            find_dialog->setObjectName(QStringLiteral("find_dialog"));
        find_dialog->resize(400, 300);
        pushButton = new QPushButton(find_dialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(290, 170, 75, 23));
        pushButton_2 = new QPushButton(find_dialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(290, 100, 75, 23));

        retranslateUi(find_dialog);

        QMetaObject::connectSlotsByName(find_dialog);
    } // setupUi

    void retranslateUi(QDialog *find_dialog)
    {
        find_dialog->setWindowTitle(QApplication::translate("find_dialog", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("find_dialog", "\344\270\213\350\275\275", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("find_dialog", "\346\237\245\350\257\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class find_dialog: public Ui_find_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIND_DIALOG_H

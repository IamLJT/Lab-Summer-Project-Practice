/********************************************************************************
** Form generated from reading UI file 'tabnamedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABNAMEDIALOG_H
#define UI_TABNAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tabNameDialog
{
public:
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QPushButton *pushButton;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;

    void setupUi(QDialog *tabNameDialog)
    {
        if (tabNameDialog->objectName().isEmpty())
            tabNameDialog->setObjectName(QStringLiteral("tabNameDialog"));
        tabNameDialog->resize(300, 175);
        label = new QLabel(tabNameDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 251, 16));
        horizontalLayoutWidget = new QWidget(tabNameDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 60, 203, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalLayoutWidget_2 = new QWidget(tabNameDialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(20, 110, 261, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lineEdit = new QLineEdit(horizontalLayoutWidget_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        pushButton_2 = new QPushButton(horizontalLayoutWidget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        retranslateUi(tabNameDialog);

        QMetaObject::connectSlotsByName(tabNameDialog);
    } // setupUi

    void retranslateUi(QDialog *tabNameDialog)
    {
        tabNameDialog->setWindowTitle(QApplication::translate("tabNameDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("tabNameDialog", "\350\257\245\346\225\260\346\215\256\345\272\223\344\270\255\346\234\211\347\233\270\345\220\214\350\241\250\345\220\215\357\274\201\357\274\201\357\274\201", Q_NULLPTR));
        label_2->setText(QApplication::translate("tabNameDialog", "1.\350\246\206\347\233\226\346\225\260\346\215\256\345\272\223\344\270\255\347\232\204\346\226\207\344\273\266", Q_NULLPTR));
        pushButton->setText(QApplication::translate("tabNameDialog", "\347\241\256\350\256\244", Q_NULLPTR));
        label_3->setText(QApplication::translate("tabNameDialog", "2.\346\226\260\345\273\272\350\241\250\345\220\215\357\274\232", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("tabNameDialog", "\346\233\264\346\224\271", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class tabNameDialog: public Ui_tabNameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABNAMEDIALOG_H

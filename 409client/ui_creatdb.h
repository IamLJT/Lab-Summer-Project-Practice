/********************************************************************************
** Form generated from reading UI file 'creatdb.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATDB_H
#define UI_CREATDB_H

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

class Ui_creatDb
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *creatDb)
    {
        if (creatDb->objectName().isEmpty())
            creatDb->setObjectName(QStringLiteral("creatDb"));
        creatDb->resize(324, 134);
        horizontalLayoutWidget = new QWidget(creatDb);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 30, 271, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(horizontalLayoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(creatDb);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(40, 90, 75, 23));
        pushButton_2 = new QPushButton(creatDb);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(190, 90, 75, 23));

        retranslateUi(creatDb);

        QMetaObject::connectSlotsByName(creatDb);
    } // setupUi

    void retranslateUi(QDialog *creatDb)
    {
        creatDb->setWindowTitle(QApplication::translate("creatDb", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("creatDb", "\346\226\260\345\273\272\346\225\260\346\215\256\345\272\223\345\220\215\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("creatDb", "\347\241\256\350\256\244", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("creatDb", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class creatDb: public Ui_creatDb {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATDB_H

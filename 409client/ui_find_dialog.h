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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_find_dialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QTableView *tableView;

    void setupUi(QDialog *find_dialog)
    {
        if (find_dialog->objectName().isEmpty())
            find_dialog->setObjectName(QStringLiteral("find_dialog"));
        find_dialog->resize(450, 350);
        horizontalLayoutWidget = new QWidget(find_dialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 50, 171, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox_2 = new QComboBox(horizontalLayoutWidget);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        horizontalLayout->addWidget(comboBox_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);
        horizontalLayoutWidget_2 = new QWidget(find_dialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(20, 20, 261, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        comboBox = new QComboBox(horizontalLayoutWidget_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_2->addWidget(comboBox);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 5);
        verticalLayoutWidget = new QWidget(find_dialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(350, 140, 71, 131));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        tableView = new QTableView(find_dialog);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(20, 90, 280, 230));
        horizontalLayoutWidget->raise();
        horizontalLayoutWidget_2->raise();
        label->raise();
        verticalLayoutWidget->raise();
        tableView->raise();

        retranslateUi(find_dialog);

        QMetaObject::connectSlotsByName(find_dialog);
    } // setupUi

    void retranslateUi(QDialog *find_dialog)
    {
        find_dialog->setWindowTitle(QApplication::translate("find_dialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("find_dialog", "\344\270\212\344\274\240\344\272\272\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("find_dialog", "\346\225\260\346\215\256\345\272\223\357\274\232", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("find_dialog", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton->setText(QApplication::translate("find_dialog", "\344\270\213\350\275\275", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class find_dialog: public Ui_find_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIND_DIALOG_H

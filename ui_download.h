/********************************************************************************
** Form generated from reading UI file 'download.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOAD_H
#define UI_DOWNLOAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_download
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QComboBox *comboBox;
    QLabel *label;
    QWidget *formLayoutWidget_2;
    QGridLayout *fill_open;
    QLabel *label_2;
    QLabel *date_name_label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QPushButton *pushButton_2;

    void setupUi(QDialog *download)
    {
        if (download->objectName().isEmpty())
            download->setObjectName(QStringLiteral("download"));
        download->resize(440, 360);
        verticalLayoutWidget = new QWidget(download);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(340, 100, 77, 201));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_5 = new QPushButton(verticalLayoutWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        formLayoutWidget = new QWidget(download);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(30, 20, 291, 22));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(formLayoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEditable(false);
        comboBox->setInsertPolicy(QComboBox::InsertAtTop);

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBox);

        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        formLayoutWidget_2 = new QWidget(download);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(30, 50, 311, 25));
        fill_open = new QGridLayout(formLayoutWidget_2);
        fill_open->setSpacing(1);
        fill_open->setObjectName(QStringLiteral("fill_open"));
        fill_open->setSizeConstraint(QLayout::SetFixedSize);
        fill_open->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(formLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        fill_open->addWidget(label_2, 0, 0, 1, 1);

        date_name_label = new QLabel(formLayoutWidget_2);
        date_name_label->setObjectName(QStringLiteral("date_name_label"));

        fill_open->addWidget(date_name_label, 0, 1, 1, 1);

        horizontalLayoutWidget = new QWidget(download);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 80, 281, 241));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(horizontalLayoutWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        horizontalLayout->addWidget(tableWidget);

        pushButton_2 = new QPushButton(download);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(350, 45, 28, 28));
        pushButton_2->setStyleSheet(QStringLiteral("border-image: url(:/icon/doc-open.png);"));

        retranslateUi(download);

        QMetaObject::connectSlotsByName(download);
    } // setupUi

    void retranslateUi(QDialog *download)
    {
        download->setWindowTitle(QApplication::translate("download", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("download", "\344\270\212\344\274\240", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("download", "\344\277\235\345\255\230", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("download", "\345\210\240\351\231\244", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("download", "\347\273\230\345\233\276", Q_NULLPTR));
        label->setText(QApplication::translate("download", "\346\225\260\346\215\256\345\272\223\357\274\232 ", Q_NULLPTR));
        label_2->setText(QApplication::translate("download", "\345\220\215\347\247\260\357\274\232 ", Q_NULLPTR));
        date_name_label->setText(QString());
        pushButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class download: public Ui_download {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOAD_H

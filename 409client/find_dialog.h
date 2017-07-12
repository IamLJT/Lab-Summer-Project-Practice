#ifndef FIND_DIALOG_H
#define FIND_DIALOG_H

#include <QDialog>
#include<myclient.h>
#include<QSettings>
#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<QTextStream>
namespace Ui {
class find_dialog;
}

class find_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit find_dialog(QWidget *parent = 0);
    ~find_dialog();

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::find_dialog *ui;
};

#endif // FIND_DIALOG_H

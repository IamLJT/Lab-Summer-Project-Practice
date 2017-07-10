#ifndef TABNAMEDIALOG_H
#define TABNAMEDIALOG_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
namespace Ui {
class tabNameDialog;
}

class tabNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit tabNameDialog(QWidget *parent = 0);
    ~tabNameDialog();
    QString getTabName();
    void tabNameWrite(QString);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::tabNameDialog *ui;
    QString tabName;
};

#endif // TABNAMEDIALOG_H

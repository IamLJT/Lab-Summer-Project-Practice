#ifndef SING_IN_H
#define SING_IN_H
#include<QDialog>
#include<QString>
#include<QSettings>
namespace Ui {
class sing_in;
}

class sing_in : public QDialog
{
    Q_OBJECT

public:
    explicit sing_in(QWidget *parent = 0);
    QString GetSingUserName();

    ~sing_in();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

public:

private:
    Ui::sing_in *ui;
    QString user_name="";
};


#endif // SING_IN_H

#include "sing_in.h"
#include "ui_sing_in.h"

sing_in::sing_in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sing_in)
{
    ui->setupUi(this);
}
sing_in::~sing_in()
{
    delete ui;
}
void sing_in::on_pushButton_2_clicked()
{
    QString name= ui->name->text();
    user_name=name;
    accept();
}
void sing_in::on_pushButton_clicked()
{
    ui->name->clear();
}
QString sing_in::GetSingUserName() {
    return user_name;
}

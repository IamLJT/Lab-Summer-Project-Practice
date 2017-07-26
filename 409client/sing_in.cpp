#include "sing_in.h"
#include "ui_sing_in.h"

sing_in::sing_in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sing_in)
{
    ui->setupUi(this);
    ui->name->setPlaceholderText("请输入用户名");
}
sing_in::~sing_in()
{
    delete ui;
}
void sing_in::on_pushButton_2_clicked()
{ 
    user_name=ui->name->text();
    accept();
}
void sing_in::on_pushButton_clicked()
{
    ui->name->clear();
}
QString sing_in::GetSingUserName() {
    return user_name;
}

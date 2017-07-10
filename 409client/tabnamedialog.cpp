#include "tabnamedialog.h"
#include "ui_tabnamedialog.h"

tabNameDialog::tabNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tabNameDialog)
{
    ui->setupUi(this);
}

tabNameDialog::~tabNameDialog()
{
    delete ui;
}
QString tabNameDialog::getTabName(){
    return tabName;
}
void tabNameDialog::tabNameWrite(QString tab){
    tabName=tab;
}
void tabNameDialog::on_pushButton_clicked()
{
    accept();
}

void tabNameDialog::on_pushButton_2_clicked()
{
    if(!ui->lineEdit->text().isEmpty()){
        tabName=ui->lineEdit->text();
        accept();
    }
    else
        QMessageBox::information(this,"提示","请输入表名！");
}

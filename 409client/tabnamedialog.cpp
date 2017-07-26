#include "tabnamedialog.h"
#include "ui_tabnamedialog.h"

tabNameDialog::tabNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tabNameDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("请输入表名");
}

tabNameDialog::~tabNameDialog()
{
    delete ui;
}
QString tabNameDialog::getTabName(){
    return tabName;
}
bool tabNameDialog::getCoverFlag(){
    return coverFlag;
}
void tabNameDialog::tabNameWrite(QString tab){
    tabName=tab;
}
void tabNameDialog::on_pushButton_clicked()
{
    coverFlag=true;
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

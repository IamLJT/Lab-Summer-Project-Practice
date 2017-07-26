#include "creatdb.h"
#include "ui_creatdb.h"

creatDb::creatDb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creatDb)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("请输入英文数据库名");
    QRegExp regExp("[A-Za-z0-9]+");
    ui->lineEdit->setValidator(new QRegExpValidator(regExp,this));
}

creatDb::~creatDb()
{
    delete ui;
}
QString creatDb::getDbName(){
    return dbName;
}

void creatDb::on_pushButton_clicked()
{
    dbName=ui->lineEdit->text();
    accept();
}

void creatDb::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
}


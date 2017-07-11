#include "creatdb.h"
#include "ui_creatdb.h"

creatDb::creatDb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creatDb)
{
    ui->setupUi(this);
}

creatDb::~creatDb()
{
    delete ui;
}

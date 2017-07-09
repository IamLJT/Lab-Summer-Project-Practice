#include "find_dialog.h"
#include "ui_find_dialog.h"

find_dialog::find_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::find_dialog)
{
    ui->setupUi(this);
}

find_dialog::~find_dialog()
{
    delete ui;
}

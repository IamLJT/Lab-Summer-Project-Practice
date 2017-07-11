#include "find_dialog.h"
#include "ui_find_dialog.h"

find_dialog::find_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::find_dialog)
{
    ui->setupUi(this);
    //-----------------从数据库获取数据库名初始化--------------------
    MyClient *db = new MyClient();
    db->GetDataBaseListFromServer();
    QStringList DbList = db->GetDataBaseList();
    delete db;
    //初始化comboBox
    QSettings *shield = new QSettings("config/fileInfo.ini", QSettings::IniFormat);
    shield->beginGroup("shieldSql");
    QStringList sql=shield->allKeys();
    shield->endGroup();
    delete shield;
    foreach (QString tmp, DbList) {
       int index=sql.indexOf(tmp);
       if(index!=-1){
           DbList.removeOne(sql[index]);
       }
    }
    ui->comboBox->addItems(DbList);
}

find_dialog::~find_dialog()
{
    delete ui;
}
//数据库确认后请求该数据库中的所有上传用户
void find_dialog::on_comboBox_activated(const QString &arg1)
{
    MyClient *db=new MyClient();
    db->SetDbName(arg1);
    QStringList user=;
}










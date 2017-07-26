#include "find_dialog.h"
#include "ui_find_dialog.h"
#include<QDebug>
find_dialog::find_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::find_dialog)
{
    ui->setupUi(this);
    //-----------------从数据库获取数据库名初始化--------------------
    MyClient *db = new MyClient();
    db->GetDataBaseListFromServer();
    QStringList DbList = db->GetDataBaseList();

    //初始化comboBox
    QVector<QStringList> sql= Section_Read("config/fileInfo.ini","shieldSql");
    foreach (QString tmp, DbList) {
       int index=sql[0].indexOf(tmp);
       if(index!=-1){
           DbList.removeOne(tmp);
       }
    }
    ui->comboBox->addItems(DbList);
    //初始化comboBox1
    if(!ui->comboBox->currentText().isEmpty()){
        db->SetDbName(ui->comboBox->currentText());
        QStringList userlist = db->GetUserNameList();
        ui->comboBox_2->addItems(userlist);
    }
    delete db;
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
    QStringList user=db->QueryDataFromServer(USERNAME_QUERY)[0];
    delete db;
    foreach (QString tmp, user) {
        qDebug()<<"数据库用户："<<tmp;
    }
    ui->comboBox_2->addItems(user);
}
//查询按钮槽函数
void find_dialog::on_pushButton_2_clicked()
{
    MyClient *db=new MyClient();
    db->SetDbName(ui->comboBox->currentText());
    db->SetUserName(ui->comboBox_2->currentText());
    QStringList tabName=(db->QueryDataFromServer(TABLENAME_QUERY))[0];
    delete db;
    ui->listWidget->clear();
    ui->listWidget->insertItems(0,tabName);
}
//下载按钮槽函数，将云端数据下载到本地TXT
void find_dialog::on_pushButton_clicked()
{
    MyClient *db=new MyClient();
    db->SetDbName(ui->comboBox->currentText());
    db->SetUserName(ui->comboBox_2->currentText());
    db->SetTbName(ui->listWidget->currentItem()->text());
    QVector<QStringList> tabdata=db->QueryDataFromServer(XYCONTENT_QUERY);
    delete db;
    QString fileName = QFileDialog :: getSaveFileName(this,"保存数据",".","*.txt");
    QFile file(fileName);
       if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
       {
         QMessageBox::information(this,"提示","文件打开失败");
       }
       else{
         QTextStream in(&file);
         for(int index=0;index<tabdata[0].size();++index)
            in<<tabdata[0][index]<<" "<<tabdata[1][index]<<"\n";
           }
       file.close();
}
//删除数据库中的这个
void find_dialog::on_pushButton_4_clicked()
{
    MyClient *db= new MyClient();
    db->SetDbName(ui->comboBox->currentText());
    db->SetUserName(ui->comboBox_2->currentText());
    db->SetTbName(ui->listWidget->currentItem()->text());
    db->DeleteTable();
    QStringList tabName=(db->QueryDataFromServer(TABLENAME_QUERY))[0];
    delete db;
    ui->listWidget->clear();
    ui->listWidget->insertItems(0,tabName);
}

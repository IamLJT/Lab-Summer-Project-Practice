#include "download.h"
#include "ui_download.h"
#include "publicfunction.h"
#include<QDebug>
download::download(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::download)
{
    ui->setupUi(this);
    Table_Widget_initia(ui->tableWidget,"变量","因变量");
    MyClient *db = new MyClient();
    db->GetDataBaseListFromServer();
    QStringList DbList = db->GetDataBaseList();
    delete db;
    //初始化comboBox
    DbList<<"New DataBases";
    QVector<QStringList> shiledSql= Section_Read("config/fileInfo.ini","shieldSql");
    foreach (QString tmp, DbList) {
       int index=shiledSql[0].indexOf(tmp);
       if(index!=-1){
           DbList.removeOne(shiledSql[0][index]);
       }
    }
    ui->comboBox->addItems(DbList);
}
download::~download()
{
    delete ui;
}
//获取私有数据函数
void download::currentUser(QString username){
     current_user=username;
}
bool download::getChangFile(){
    return changFile;
}
//文件打开按钮槽函数
void download::on_pushButton_2_clicked()
{
    QString filePath = QFileDialog :: getOpenFileName(this,"实验数据",NULL, "*.xlsx *.txt");
    QVector<QStringList> fileData=File_Read(filePath);
    if(!fileData.isEmpty()){
        ui->date_name_label->setText(filePath);
        Flush_Table_Widget(ui->tableWidget,fileData);
        fileName=filePath;
    }
    else
        QMessageBox::information(this,"提示","文件打开失败");
}
//删除按钮槽函数，删除当前视图中的值
void download::on_pushButton_3_clicked()
{
     ui->tableWidget->clearContents();
     ui->tableWidget->setRowCount(0);
     ui->date_name_label->clear();
     xFileDate.clear();
     yFileDate.clear();
}
//保存按钮槽函数
void download::on_pushButton_5_clicked()
{
    //如果存在当前用户，将文件保存到配置文件中
    QString fileAddress=ui->date_name_label->text();
    if(!current_user.isEmpty()&&!fileAddress.isEmpty()){
        QDateTime tmp = QDateTime::currentDateTime();//获取系统现在的时间
        QString time = tmp.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式
        Section_Write("config/userInfo.ini",current_user,fileAddress,time);
        Section_Write("config/fileInfo.ini","txt",fileAddress,time);
        changFile=true;
    }

}
//上传按钮槽函数，上传到数据库
void download::on_pushButton_clicked()
{
    MyClient *db = new MyClient();
    db->SetDbName(ui->comboBox->currentText());

    db->CreateDataBase();
    if(current_user==""){     //设置用户名
        db->SetUserName("visitor");
    }
    else{
        db->SetUserName(current_user);
    }
    if(fileName.size()==0)
        QMessageBox::information(this,"提示","请打开文件！");
    else{
        QString tabName=QFileInfo(fileName).fileName();
        int index;
        index=tabName.lastIndexOf(".");
        tabName.truncate(index);

        db->GetTableListFromServer();
        //QStringList tabList = db->GetTableList();
        QStringList tabList=(db->QueryDataFromServer(TABLENAME_QUERY))[0];
        qDebug()<<"tabListsize:"<<tabList.size();

        for(int index=0;index<tabList.size();++index){
           qDebug()<<"tabName:"<<tabList[index];
           if(tabName==tabList[index]){ //若有相同表名可选择改名或者覆盖
            tabNameDialog *tn=new tabNameDialog();
            tn->tabNameWrite(tabName);
            tn->exec();
            if(tn->getCoverFlag()){
                db->SetTbName(tabName);
                db->DeleteTable();
               }
            tabName=tn->getTabName();
            delete tn;
            break;
           }
        }
        qDebug()<<"表名：" << tabName;
        db->SetTbName(tabName);
        db->CreateTable();
        //上传数据 fileDate
        int rowNum=ui->tableWidget->rowCount();
        xFileDate.resize(rowNum);
        yFileDate.resize(rowNum);
        for(int i=0;i<rowNum;++i){
            xFileDate[i]=ui->tableWidget->item(i,0)->text();
            yFileDate[i]=ui->tableWidget->item(i,1)->text();
        }
        db->InsertTable(xFileDate,yFileDate);
        delete db;
        on_pushButton_5_clicked();
    }
}

void download::on_comboBox_activated(const QString &arg1)
{
    if(arg1=="New DataBases"){
        creatDb *cDb= new creatDb();
        cDb->exec();
        QString dbName=cDb->getDbName();
        if(!dbName.isEmpty()){
            int index=ui->comboBox->count();
            ui->comboBox->insertItem(index-1,dbName);
        }
        delete cDb;
    }
}
//删除数据库
void download::on_pushButton_6_clicked()
{
    if(QMessageBox::Ok==QMessageBox::question(this,"提示","确认删除？",
                                              QMessageBox::Ok|QMessageBox::Cancel,
                                              QMessageBox::Cancel)){
        int index=ui->comboBox->currentIndex();
        MyClient *db=new MyClient();
        db->SetDbName(ui->comboBox->itemText(index));
        db->DeleteDatabase();
        delete db;
        ui->comboBox->removeItem(index);
    }
}

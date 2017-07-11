#include "download.h"
#include "ui_download.h"
#include<QDebug>
download::download(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::download)
{
    ui->setupUi(this);
    //---------------初始化ui界面--------------------------------
    //设置QTableWidget的界面
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(0);
    QStringList name;
    name<<"变量"<<"因变量";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    //ui->tableWidget->set(0,10);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    //ui->tableWidget->verticalHeader()->setHidden(true);//表格前的序列号设置为隐藏
    ui->tableWidget->horizontalHeader()->setFixedHeight(25); //设置表头的高度
    // 设置文件打开grid
    ui->fill_open->setColumnStretch(0,1);
    ui->fill_open->setColumnStretch(1,4);

    //-----------------从数据库获取数据库名初始化--------------------
    MyClient *db = new MyClient();
    db->GetDataBaseListFromServer();
    QStringList DbList = db->GetDataBaseList();
    delete db;
    //初始化comboBox
    DbList<<"New DataBases";
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
    //-----------------------------------------------------------
    // -----------------获取数据库列表-----------------------------
//    MyClient *db = new MyClient();
//    db->SetUserName("LJT");// 设置当前用户名

//    db->GetDataBaseListFromServer();//从服务器获取数据库列表
//    QStringList DbList = db->GetDataBaseList();

//    QString dbname = "mysql";
//    db->SetDbName(dbname);//设置当前数据库
//    db->GetTableListFromServer();
//    DbList = db->GetTableList();
//    qDebug() << dbname << "表名";
//    foreach (db_data, DbList)
//        qDebug() << db_data;
//    //
//    dbname = "sss";
//    db->SetDbName(dbname);//设置数据库名
//    db->CreateDataBase();

//    QString tbname = "ta";
//    db->SetTbName(tbname);//设置表名
//    db->CreateTable();

//    delete db;
    //-----------------------------------------------------

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
    QString file_name = QFileDialog :: getOpenFileName(this,"实验数据",NULL, "*.xlsx *.txt");
    if(!file_name.isEmpty()){
        ui->date_name_label->setText(file_name);
    QFile txt_file(file_name);
    if(!txt_file.open(QIODevice::ReadOnly))
        QMessageBox::information(this,"提示","文件打开失败");
    else{
        ui->tableWidget->clearContents();
        fileName=file_name;
        QTextStream in(&txt_file);
        qint32 row;
        qint32 row_index=0;
        QString col1,col2;//只能显示string变量
        while(!in.atEnd()){
            in>>col1>>col2;
            row=ui->tableWidget->rowCount();
            if(row_index>=row){
               ui->tableWidget->insertRow(row);
            }
            ui->tableWidget->setItem(row_index,0,new QTableWidgetItem(col1));
            ui->tableWidget->setItem(row_index,1,new QTableWidgetItem(col2));
            ui->tableWidget->item(row_index,0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->item(row_index,1)->setTextAlignment(Qt::AlignCenter);
            //保存到一个二维字符串中保存，等待传到数据库
            xFileDate.push_back(col1);
            yFileDate.push_back(col2);
            ++row_index; 
        }
    }
    txt_file.close();
    }
}
//删除按钮槽函数，删除当前视图中的值
void download::on_pushButton_3_clicked()
{
     ui->tableWidget->clearContents();
     ui->date_name_label->clear();
     xFileDate.clear();
     yFileDate.clear();
}
//保存按钮槽函数
void download::on_pushButton_5_clicked()
{
    //如果存在当前用户，将文件保存到配置文件中
    QString file_address=ui->date_name_label->text();
    const QString user_name=current_user;
    QString file_name= QFileInfo(file_address).fileName();
    if(!user_name.isEmpty()&&!file_address.isEmpty()){
        QDateTime tmp = QDateTime::currentDateTime();//获取系统现在的时间
        QString time = tmp.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
        QString file_time=file_name+".time";
        QSettings *userInfoWrite = new QSettings("config/userInfo.ini", QSettings::IniFormat);
        userInfoWrite->beginGroup(user_name);
        userInfoWrite->setValue(file_name, file_address);
        userInfoWrite->setValue(file_time, time);
        userInfoWrite->endGroup();
        delete userInfoWrite;
        QSettings *fileInfoWrite = new QSettings("config/fileInfo.ini", QSettings::IniFormat);
        fileInfoWrite->beginGroup("txt");
        fileInfoWrite->setValue(file_name,file_address);
        fileInfoWrite->setValue(file_time, time);
        fileInfoWrite->endGroup();
        delete fileInfoWrite;
    }
    changFile=true;
}
//上传按钮槽函数，上传到数据库
void download::on_pushButton_clicked()
{
    MyClient *db = new MyClient();
    db->SetDbName(ui->comboBox->currentText().toLocal8Bit());
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
        QStringList tabList = db->GetTableList();
        QString tabData;
        foreach (tabData, tabList)
           if(tabName==tabData){ //若有相同表名可选择改名或者覆盖
            tabNameDialog *tn=new tabNameDialog();
            tn->tabNameWrite(tabName);
            tn->exec();
            if(tn->getCoverFlag()){
                db->SetTbName(tabName);
                db->DeleteTable();
               }
            tabName=tn->getTabName();
            delete tn;
           }
        db->SetTbName(tabName);
        db->CreateTable();
        //上传数据 fileDate
        int rowNum=ui->tableWidget->rowCount();
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
    int index=ui->comboBox->currentIndex();
    MyClient *db=new MyClient();
    db->SetDbName(ui->comboBox->itemText(index));
    db->DeleteDatabase();
    delete db;
    ui->comboBox->removeItem(index);
}

#include "download.h"
#include "ui_download.h"
#include<QDebug>
download::download(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::download)
{
    ui->setupUi(this);
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

    // 获取数据库列表
    MyClient *db = new MyClient();
    db->SetUserName("qwer");

    db->GetDataBaseListFromServer();
    QStringList DbList = db->GetDataBaseList();
    QString db_data;
    qDebug() << "数据库名：";
    foreach (db_data, DbList)
        qDebug() << db_data;

    QString dbname = "myfirstsql";
    db->SetDbName(dbname);
    db->GetTableListFromServer();
    DbList = db->GetTableList();
    qDebug() << dbname << "表名";
    foreach (db_data, DbList)
        qDebug() << db_data;

    // 新建数据库名
    dbname = "sss";
    db->SetDbName(dbname);
    db->CreateDataBase();
    // 新建表名
    QString tbname = "ta";
    db->SetTbName(tbname);
    db->CreateTable();

    QVector<QString> x, y;
    for (int i = 0; i < 10; ++i) {
        x.push_back("AAA");
        y.push_back("BBB");
    }
    db->InsertTable(x, y);

    QVector<QStringList> dbveclist = db->QueryDataFromServer(TABLENAME_QUERY);
    qDebug() << dbname << "USER表名:";
    foreach (db_data, dbveclist[0])
        qDebug() << db_data;
    dbveclist = db->QueryDataFromServer(USERNAME_QUERY);
    qDebug() << dbname << "users:";
    foreach (db_data, dbveclist[0])
        qDebug() << db_data;

    dbveclist = db->QueryDataFromServer(XYCONTENT_QUERY);
    qDebug() << dbname << "表" << tbname << "内容: x and y";
    for (int i = 0; i < dbveclist[0].size(); ++i)
        qDebug() << "x:" << dbveclist[0][i] << " y:" << dbveclist[1][i];

    // 删除前面新建的数据库和表
    //db->DeleteTable();
    //db->DeleteDatabase();

    delete db;
}

download::~download()
{
    delete ui;
}

//文件打开按钮槽函数
void download::on_pushButton_2_clicked()
{
    ui->tableWidget->clearContents();
    //添加按钮的槽函数，调出filldialog，打开文件
    //点击添加后调用文件位置
    QString file_name = QFileDialog :: getOpenFileName(this,"实验数据",NULL, "*.xlsx *.txt");
    ui->date_name_label->setText(file_name); //读取文件位置之后显示在label
    //读取txt中的内容到tablewidget中显示
    QFile txt_file(file_name);
    if(!txt_file.open(QIODevice::ReadOnly))
        QMessageBox::information(this,"提示","文件打开失败");
    else{
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
            fileDate.push_back(QVector<QString>(2,""));
            fileDate.back()[0] = col1;
            fileDate.back()[1] = col2;
            ++row_index; 
        }

    }
    txt_file.close();
   // 读取表格中的数据
    //QString str = ui->TableWidget->item(row,column)->text();//取出字符串
    //int num = str.toInt();//转成int
}
//删除按钮槽函数，删除当前视图中的值
void download::on_pushButton_3_clicked()
{
     ui->tableWidget->clearContents();
     ui->date_name_label->clear();
     fileDate.clear();
}

void download::currentUser(QString username){
     current_user=username;
}
//保存按钮槽函数,如果存在当前用户，将文件保存到配置文件中
void download::on_pushButton_5_clicked()
{
    QString file_address=ui->date_name_label->text();
    const QString user_name=current_user;
    QString file_name= QFileInfo(file_address).fileName();
    if(!user_name.isEmpty()&&!file_address.isEmpty()){
        QDateTime tmp = QDateTime::currentDateTime();//获取系统现在的时间
        QString time = tmp.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
        QString file_time=file_name+".time";

        //QString runPath = QCoreApplication::applicationDirPath();//获取当前路径
        //qDebug()<<runPath;

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
        qDebug()<<"更改写入成功";
    }
    changFile=true;
}
bool download::getChangFile(){
    return changFile;
}
//上传按钮槽函数，上传到数据库
void download::on_pushButton_clicked()
{

}

















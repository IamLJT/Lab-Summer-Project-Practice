#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "download.h"
#include "sing_in.h"
#include "find_dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置QTableWidget的界面
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(0);
    QStringList name;
    name<<"文件名"<<"修改时间";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget->horizontalHeader()->setFixedHeight(25); //设置表头的高度
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//只能选中一行

    //主界面数据初始化
    QSettings *userInfoRead = new QSettings("config/userInfo.ini", QSettings::IniFormat);
    QString user = userInfoRead->value("/last/name").toString();//当前用户名
    ui->user_name->setText(user);
    delete userInfoRead;
    iniWidget(user);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//“上传”Button槽函数
void MainWindow::on_pushButton_1_clicked()
{
    download *down=new download();
    down->currentUser(ui->user_name->text());
    down->exec();
    if(down->getChangFile()){
        iniWidget(ui->user_name->text());
    }
    delete down;
}
//“用户登录”Button槽函数
void MainWindow::on_pushButton_4_clicked()
{
    QString oldUser=ui->user_name->text();
    sing_in *login=new sing_in();
    login->setWindowTitle("用户登录");
    login->exec();//只要窗口还在运行，就会在这中断，当窗口关闭时，会继续运行
    QString currentName=login->GetSingUserName();
    if(oldUser!=currentName&&currentName!=""){
        ui->tableWidget->clearContents();
        ui->user_name->setText(currentName);
        iniWidget(currentName);
         //写入配置文件，用户信息
        QSettings *userInfoWrite = new QSettings("config/userInfo.ini", QSettings::IniFormat);
        userInfoWrite->setValue("last/name", currentName);
        delete userInfoWrite;
    }
    delete login;
}
//查询按钮，打开查询的界面
void MainWindow::on_pushButton_2_clicked()
{
   find_dialog *findFile=new find_dialog();
   findFile->exec();
   delete findFile;
}
//更新tablewidget
 void MainWindow::iniWidget(QString user){
    if(!user.isEmpty()){
       flushWidget(user);
    }
}
//主界面tablewidget刷新
void MainWindow::flushWidget(QString user){
    QSettings *userInfoRead = new QSettings("config/userInfo.ini", QSettings::IniFormat);
    userInfoRead->beginGroup(user);
    QStringList keys=userInfoRead->allKeys();
    userInfoRead->endGroup();
     ui->tableWidget->clearContents();
     qint32 row;
     qint32 row_index=0;
     QString col1,col2;
     for(int i=0;i<keys.size();){
         row=ui->tableWidget->rowCount();
         if(row_index>=row){
            ui->tableWidget->insertRow(row);
         }
         userInfoRead->beginGroup(user);
         col1=keys[i];
         col2=userInfoRead->value(keys[i+1]).toString();
         userInfoRead->endGroup();
         ui->tableWidget->setItem(row_index,0,new QTableWidgetItem(col1));
         ui->tableWidget->setItem(row_index,1,new QTableWidgetItem(col2));
         ui->tableWidget->item(row_index,0)->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->item(row_index,1)->setTextAlignment(Qt::AlignCenter);
         ++row_index;
         i=i+2;
     }
     delete userInfoRead;
}

//退出登录按钮槽函数，删除该用户的相关信息
void MainWindow::on_pushButton_6_clicked()
{
     ui->tableWidget->clearContents();
     QString currentName=ui->user_name->text();
     if(currentName!=""){
        QSettings *userInfoRead= new QSettings("config/userInfo.ini", QSettings::IniFormat);
        userInfoRead->remove(currentName);
        userInfoRead->setValue("last/name","");
        delete userInfoRead;
     }
     ui->user_name->setText("");
}
//删除按钮，删除选中行和配置文件中该文件的信息
void MainWindow::on_pushButton_5_clicked()
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem()); // 判断是否选中一行
    if(focus){
        qint32 rowNum =ui->tableWidget->currentItem()->row(); // 当前选中行
        QString fileName=ui->tableWidget->item(rowNum,0)->text();
        QString currentName=ui->user_name->text();
        QSettings *userInfoWrite=new QSettings("config/userInfo.ini",QSettings::IniFormat);
        userInfoWrite->beginGroup(currentName);
        userInfoWrite->remove(fileName);
        userInfoWrite->remove(fileName+".time");
        userInfoWrite->endGroup();
        delete userInfoWrite;
        flushWidget(currentName);
    }
}

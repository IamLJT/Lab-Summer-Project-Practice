#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //主界面数据初始化
    Table_Widget_initia(ui->tableWidget,"文件名","修改时间");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//只能选中一行
    QVector<QStringList> lastUser=Section_Read("config/userInfo.ini","last");
    Flush_Widget(lastUser[1][0]);
    ui->user_name->setText(lastUser[1][0]);
    //CommonHelper::setStyle("white.qss");
}

MainWindow::~MainWindow()
{
    delete ui;
}
//主界面tablewidget刷新
void MainWindow::Flush_Widget(QString user){
    if(!user.isEmpty()){
        QVector<QStringList> fileAddress=Section_Read("config/userInfo.ini",user);
        for(int index=0;index<fileAddress[0].size();++index)
            fileAddress[0][index]=QFileInfo(fileAddress[0][index]).fileName();
        Flush_Table_Widget(ui->tableWidget,fileAddress);
      }
}

//绘图
void MainWindow::on_pushButton_clicked()
{
  PlotWindow *plot=new PlotWindow();
  plot->setWindowTitle("绘图");
  QString filePath=Click_Table_widget(ui->tableWidget,ui->user_name->text());
  QVector<QStringList> fileData=File_Read(filePath);
  if(!fileData.isEmpty()){
      plot->dataWrite(fileData);
      plot->show();//关闭窗口之后自动调用析构函数，不需要自己进行 删除操作
  }
  else
      QMessageBox::information(this,"提示","请选择文件！");
}
//“上传”Button槽函数
void MainWindow::on_pushButton_1_clicked()
{
    download *down=new download();
    down->currentUser(ui->user_name->text());
    down->setWindowTitle("上传");
    down->exec();
    if(down->getChangFile()){
        Flush_Widget(ui->user_name->text());
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
        ui->user_name->setText(currentName);
        Flush_Widget(currentName);
        Section_Write("config/userInfo.ini","last","name",currentName);
    }
    delete login;
}
//查询按钮，打开查询的界面
void MainWindow::on_pushButton_2_clicked()
{
   find_dialog *findFile=new find_dialog();
   findFile->setWindowTitle("数据库查询");
   findFile->exec();
   delete findFile;
}
//退出登录按钮槽函数，删除该用户的相关信息
void MainWindow::on_pushButton_6_clicked()
{
    if(QMessageBox::Ok==QMessageBox::question(this,"提示","确认删除所有本地资料？",
                                              QMessageBox::Ok|QMessageBox::Cancel,
                                              QMessageBox::Cancel)){
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
}
//删除按钮，删除选中行和配置文件中该文件的信息
void MainWindow::on_pushButton_5_clicked()
{
    if(!ui->user_name->text().isEmpty()){
        QString filePath=Click_Table_widget(ui->tableWidget,ui->user_name->text());
        QSettings *userInfoWrite=new QSettings("config/userInfo.ini",QSettings::IniFormat);
        userInfoWrite->beginGroup(ui->user_name->text());
        userInfoWrite->remove(filePath);
        userInfoWrite->endGroup();
        delete userInfoWrite;
        Flush_Widget(ui->user_name->text());
    }
}


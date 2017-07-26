#include"publicfunction.h"
#include<QDebug>

//文件读写
QVector<QStringList> File_Read(QString filePath){
    QVector<QStringList> fileData;
    if(!filePath.isEmpty()){
        QFile txt_file(filePath);
        if(txt_file.open(QIODevice::ReadOnly)){
            QStringList xFileData;
            QStringList yFileData;
            QTextStream in(&txt_file);
            int count = 0;
            int type = 0;
            QString tmp;
            QStringList list;
            while(!in.atEnd()){
                tmp = in.readLine();
                if(tmp.isEmpty())
                    continue;
                if (count == 0) {
                    if (tmp.contains(",",Qt::CaseInsensitive))
                        type = 1;
                    else if (tmp.contains("\t",Qt::CaseInsensitive))
                        type = 2;
                    else if (tmp.contains(" ",Qt::CaseInsensitive))
                        type = 3;
                    else
                        continue;
                }
                switch(type) {
                case 1:
                    list = tmp.split(",");
                    break;
                case 2:
                    list = tmp.split("\t");
                    break;
                case 3:
                    list = tmp.split(" ");
                    break;
                }
                xFileData<<list[0];
                yFileData<<list[1];
                count++;
            }
            fileData.push_back(xFileData);
            fileData.push_back(yFileData);
        }
         txt_file.close();
    }
    return fileData;
}
//配置文件、读是读一整个section，写是单条插入
QVector<QStringList> Section_Read(QString iniPath,QString section){
    QVector<QStringList> fileAddress;
    QSettings *userInfoRead = new QSettings(iniPath, QSettings::IniFormat);
    userInfoRead->beginGroup(section);
    QStringList keys=userInfoRead->allKeys();
    QStringList value;
    for(int index=0;index<keys.size();++index){
        value<<userInfoRead->value(keys[index]).toString();
    }
    fileAddress.push_back(keys);
    fileAddress.push_back(value);
    userInfoRead->endGroup();
    return fileAddress;
}
void Section_Write(QString iniPath,QString section,QString key,QString value){
    QSettings *userInfoWrite = new QSettings(iniPath, QSettings::IniFormat);
    userInfoWrite->beginGroup(section);
    userInfoWrite->setValue(key, value);
    userInfoWrite->endGroup();
    delete userInfoWrite;
    return;
}

//刷新tableWidget
void Flush_Table_Widget(QTableWidget* tw,QVector<QStringList> fileData){
    tw->clearContents();
    tw->setRowCount(0);
    int row;
    for(int rowIndex=0;rowIndex<fileData[0].size();++rowIndex){
        row=tw->rowCount();
        tw->insertRow(row);
        tw->setItem(rowIndex,0,new QTableWidgetItem(fileData[0][rowIndex]));
        tw->setItem(rowIndex,1,new QTableWidgetItem(fileData[1][rowIndex]));
        tw->item(rowIndex,0)->setTextAlignment(Qt::AlignCenter);
        tw->item(rowIndex,1)->setTextAlignment(Qt::AlignCenter);
    }
    return;
}
void Table_Widget_initia(QTableWidget *tw,QString head1,QString head2){
    tw->setColumnCount(2);
    tw->setRowCount(0);
    QStringList name;
    name<<head1<<head2;
    tw->setHorizontalHeaderLabels(name);
    tw->horizontalHeader()->setStretchLastSection(true);
    tw->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tw->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    tw->horizontalHeader()->setFixedHeight(25); //设置表头的高度
    //tw->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    //tw->setSelectionBehavior(QAbstractItemView::SelectRows);//只能选中一行
}


QString Click_Table_widget(QTableWidget* tab,QString currentName){
    QString fileName;
    bool focus = tab->isItemSelected(tab->currentItem()); // 判断是否选中一行
    if(focus){
        qint32 rowNum =tab->currentItem()->row(); // 当前选中行
        fileName=tab->item(rowNum,0)->text();
        QSettings *userInfoWrite=new QSettings("config/userInfo.ini",QSettings::IniFormat);
        userInfoWrite->beginGroup(currentName);
        QStringList keys=userInfoWrite->allKeys();
        foreach(QString tmp,keys){
            if(fileName==QFileInfo(tmp).fileName()){
                fileName=tmp;
            }
        }
        userInfoWrite->endGroup();
        delete userInfoWrite;
        return fileName;
    }
    else
        return fileName;
}





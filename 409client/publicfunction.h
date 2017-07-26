#ifndef PUBLICFUNCTION_H
#define PUBLICFUNCTION_H

#endif // PUBLICFUNCTION_H
#include<QSettings>
#include<QTextStream>
#include<QVector>
#include<QStringList>
#include<QFile>
#include <QTableWidget>
#include<QMessageBox>
#include<QString>
#include<QHeaderView>
#include<QFileInfo>
//txt文件读写
QVector<QStringList> File_Read(QString);

//刷新tablewidget
void Flush_Table_Widget(QTableWidget *,QVector<QStringList>);

//配置文件读写
QVector<QStringList> Section_Read(QString,QString);
void Section_Write(QString,QString,QString,QString);

//tablewidget格式初始化
void Table_Widget_initia(QTableWidget *,QString,QString);

//点击一行tablewidget
QString Click_Table_widget(QTableWidget*,QString);

#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QStringList>
#include <WinSock2.h>
#include <QDebug>

class MyClient
{
public:
    MyClient();
    void GetFromServer(int order_type); // 从服务器获取信息
    void GetDataBaseListFromServer();   // 获取服务器上数据库列表
    void GetTableListFromServer();      // 获取服务器上某数据库的表
    void CreateDataBase();              // 新建数据库
    void CreateTable();                 // 新建表
    void DeleteDatabase();              // 删除数据库
    void DeleteTable();                 // 删除数据库中表
    QStringList GetTableList();         // 获取本地数据库中的表内容
    QStringList GetDataBaseList();      // 获取本地数据库列表
    QStringList GetUserNameList();      // 获取当前数据库的用户
    void GetTableContent();             // 获取表内容

    QVector<QStringList> QueryDataFromServer(int QueryStr);    // 查询数据

    void SetDbName(QString dbname);     // 设置数据库名
    void SetTbName(QString tbname);     // 设置表名
    void SetUserName(QString username); // 设置用户名
    void SetTbContent(QVector<QString>& x, QVector<QString>& y);// 设置表内容

    void InsertTable(QVector<QString> x, QVector<QString> y);   // 向表插入内容

    ~MyClient();

private:
    // DataBase data
    QStringList DataBaseList;
    QStringList TableList;
    QString DB_name;
    QString TB_name;
    QString User_name;

    // socket data
    WSADATA wsaData;
    SOCKET ClientSocket;
    sockaddr_in RecvAddr;

    QString hostname;       // 域名
    int Port;               // 端口

    // 常用的变量
    int len;
    QVector<QString> xString;
    QVector<QString> yString;
    int QueryOrder;
    QVector<QStringList> QueryData;
};

#endif // MYCLIENT_H

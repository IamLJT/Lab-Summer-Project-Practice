#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QStringList>
#include <WinSock2.h>
#include <QDebug>

class MyClient
{
public:
    MyClient();
    void GetFromServer(int order_type);
    void GetDataBaseListFromServer();
    void GetTableListFromServer();
    void CreateDataBase();
    void CreateTable();
    QStringList GetTableList();
    QStringList GetDataBaseList();

    void SetDbName(QString dbname);
    void SetTbName(QString tbname);
    void SetUserName(QString username);

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
    const int MaxLen;
    int len;

};

#endif // MYCLIENT_H

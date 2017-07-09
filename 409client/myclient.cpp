#include "myclient.h"

MyClient::MyClient() :
    MaxLen(100),
    hostname("115.156.217.168"),
    Port(1234)
{
    len = sizeof(SOCKADDR);
    // 初始化DLL
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    // 创建套接字
    ClientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    // 设置服务器地址
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(Port);
    RecvAddr.sin_addr.s_addr = inet_addr(hostname.toLatin1().data());
}

void MyClient::GetDataBaseListFromServer() {
    GetFromServer(QUERYDB_ORDER);
}

void MyClient::GetTableListFromServer() {
    GetFromServer(QUERYTB_ORDER);
}

void MyClient::CreateDataBase() {
    GetFromServer(CREATEDB_ORDER);
}

void MyClient::CreateTable() {
    GetFromServer(CREATETB_ORDER);
}

void MyClient::GetFromServer(int order_type) {
    // Json数据流
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QString data_str;
    // 放入查询命令
    QJsonObject send_jsonobj;
    send_jsonobj.insert("order_type", order_type);
    send_jsonobj.insert("user", User_name);
    switch(order_type) {
    case QUERYTB_ORDER:
        TableList.clear();
        send_jsonobj.insert("db_name", DB_name);
        break;
    case QUERYDB_ORDER:
        DataBaseList.clear();
        break;
    case CREATEDB_ORDER:
        send_jsonobj.insert("db_name", DB_name);
        break;
    case CREATETB_ORDER:
        send_jsonobj.insert("db_name", DB_name);
        send_jsonobj.insert("tb_name", TB_name);
        break;
    }

    QString order_str = QString(QJsonDocument(send_jsonobj).toJson());
    const char* sendBuf = order_str.toLatin1().data();
    int sendLen = order_str.length()+1;
    // 发送命令
    ::sendto(ClientSocket, sendBuf, sendLen, 0, (SOCKADDR*)&RecvAddr, sizeof(SOCKADDR));
    // 接收数据
    char recvBuf[MaxLen] = { 0 };
    bool isStop = false;

    while (!isStop) {
        ::recvfrom(ClientSocket, recvBuf, MaxLen, 0, (SOCKADDR*)&RecvAddr, &len);
        if ('\0' == recvBuf[0]) { qDebug() << "服务器未打开！"; break; }
        data_str = QString(QLatin1String(recvBuf));
        jsonDocument = QJsonDocument::fromJson(data_str.toLocal8Bit().data());
        jsonObject = jsonDocument.object();
        //qDebug() << jsonObject;
        switch(jsonObject["order_type"].toInt()) {
        case EXIT_DATA:
            qDebug() << "数据传输结束！！！";
            isStop = true;
            break;
        case TABLE_DATA:
            TableList.push_back(jsonObject["table"].toString());
            break;
        case DATABASE_DATA:
            DataBaseList.push_back(jsonObject["database"].toString());
            break;
        case RETURNDB_DATA:
            switch(jsonObject["value"].toInt()) {
            case EXISTDB_VALUE:
                qDebug() << "该数据库已存在！";
                break;
            case FAILCDB_VALUE:
                qDebug() << "数据库" << DB_name << "创建失败！请检查原因！";
                break;
            case SUCSCDB_VALUE:
                qDebug() << "数据库" << DB_name << "创建成功";
                break;
            }
            break;
        case RETURNTB_DATA:
            switch(jsonObject["value"].toInt()) {
            case EXISTTB_VALUE:
                qDebug() << TB_name << "表已存在！";
                break;
            case FAILCTB_VALUE:
                qDebug() << "数据库" << DB_name << "中表" << TB_name << "创建失败！请检查原因！";
                break;
            case SUCSCTB_VALUE:
                qDebug() << "数据库" << DB_name << "中表" << TB_name <<  "创建成功";
                break;
            }
            break;
        }
    }
}

void MyClient::SetDbName(QString dbname) {
    DB_name = dbname;
}

void MyClient::SetTbName(QString tbname) {
    TB_name = tbname;
}

void MyClient::SetUserName(QString username) {
    User_name = username;
}

QStringList MyClient::GetDataBaseList() {
    return DataBaseList;
}

QStringList MyClient::GetTableList() {
    return TableList;
}

MyClient::~MyClient() {
    closesocket(ClientSocket);
    WSACleanup();
}

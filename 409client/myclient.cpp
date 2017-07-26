﻿#include "myclient.h"

MyClient::MyClient() :
    hostname("115.156.217.168"),
    //hostname("127.0.0.1"),
    Port(1235),
    User_name("")
{
    len = sizeof(SOCKADDR);
    // 初始化DLL
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    // 创建套接字
    ClientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    // 设置服务器地址
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(Port);
    RecvAddr.sin_addr.s_addr = inet_addr(hostname.toLocal8Bit().data());
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

void MyClient::DeleteDatabase() {
    GetFromServer(DELETEDB_ORDER);
}

void MyClient::DeleteTable() {
    GetFromServer(DELETETB_ORDER);
}

QVector<QStringList> MyClient::QueryDataFromServer(int QueryStr) {
    QueryOrder = QueryStr;
    GetFromServer(QUERY_ORDER);
    return QueryData;
}

void MyClient::InsertTable(QVector<QString> x, QVector<QString> y) {
    // x和y的长度一定要相等
    xString = x;
    yString = y;
    GetFromServer(INSERTTB_ORDER);
}

void MyClient::GetFromServer(int order_type) {
    const int maxbyte = 128 * 1024;
    const int maxlen = 10000;
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
    case DELETEDB_ORDER:
        send_jsonobj.insert("db_name", DB_name);
        break;
    case CREATETB_ORDER:
    case DELETETB_ORDER:
    case INSERTTB_ORDER:
        send_jsonobj.insert("db_name", DB_name);
        send_jsonobj.insert("tb_name", TB_name);
        break;
    case QUERY_ORDER:
        QueryData.clear();
        send_jsonobj.insert("db_name", DB_name);
        send_jsonobj.insert("tb_name", TB_name);
        send_jsonobj.insert("content", QueryOrder);
        break;
    }
    if (TABLENAME_QUERY == QueryOrder || USERNAME_QUERY == QueryOrder)
        QueryData.resize(1);
    else if (XYCONTENT_QUERY == QueryOrder)
        QueryData.resize(2);
    //QString order_str = QString::fromLocal8Bit(send_jsonobj);
    QString order_str = QString(QJsonDocument(send_jsonobj).toJson(QJsonDocument::Compact));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    const char* sendBuf = order_str.toLocal8Bit().data();
    int sendLen = 2 * order_str.length() + 1;
    qDebug() << order_str << "\n" << sendBuf;
    // 发送命令
    ::sendto(ClientSocket, order_str.toLocal8Bit().data(), sendLen, 0, (SOCKADDR*)&RecvAddr, sizeof(SOCKADDR));
    // 接收数据
    char recvBuf[maxbyte] = { 0 };
    bool isStop = false;

    while (!isStop) {
        int count  = 0;
        QString tempx = "", tempy = "";
        ::recvfrom(ClientSocket, recvBuf, maxbyte, 0, (SOCKADDR*)&RecvAddr, &len);
        if ('\0' == recvBuf[0]) { qDebug() << "服务器未打开！"; break; }
        data_str = QString::fromLocal8Bit(recvBuf);
        jsonDocument = QJsonDocument::fromJson(data_str.toLocal8Bit().data());
        jsonObject = jsonDocument.object();
        //qDebug() << jsonObject;
        int stringlen = xString.size();
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
        case DELETEDB_DATA:
            switch(jsonObject["value"].toInt()) {
            case NEXISDB_VALUE:
                qDebug() << "该数据库不存在！";
                break;
            case FAILDDB_VALUE:
                qDebug() << "数据库" << DB_name << "删除失败！请检查原因！";
                break;
            case SUCSDDB_VALUE:
                qDebug() << "数据库" << DB_name << "删除成功";
                break;
            }
            break;
        case DELETETB_DATA:
            switch(jsonObject["value"].toInt()) {
            case NEXISTB_VALUE:
                qDebug() << TB_name << "表不存在！";
                break;
            case FAILDTB_VALUE:
                qDebug() << "数据库" << DB_name << "中表" << TB_name << "删除失败！请检查原因！";
                break;
            case SUCSDTB_VALUE:
                qDebug() << "数据库" << DB_name << "中表" << TB_name <<  "删除成功";
                break;
            }
            break;
        case INSERTTB_DATA:
            send_jsonobj["order_type"] = INSERTTB_DATA;
            for (int i = 0; i < stringlen; ++i) {
                count++;
                if (xString[i].isEmpty() || yString[i].isEmpty())
                    continue;
                tempx += xString[i];
                tempy += yString[i];
                if (count == maxlen) {
                    qDebug() << "正在发送..." << "len: " << count << " type: " << send_jsonobj["order_type"].toInt();
                    count = 0;
                    send_jsonobj.insert("x", tempx);
                    send_jsonobj.insert("y", tempy);
                    tempx = "";
                    tempy = "";
                    order_str = QString(QJsonDocument(send_jsonobj).toJson(QJsonDocument::Compact));
                    sendBuf = order_str.toLocal8Bit().data();
                    sendLen = 2 * order_str.length()+1;
                    // 发送命令
                    ::sendto(ClientSocket, order_str.toLocal8Bit().data(), sendLen, 0, (SOCKADDR*)&RecvAddr, sizeof(SOCKADDR));
                    //::sendto(ClientSocket, sendBuf, sendLen, 0, (SOCKADDR*)&RecvAddr, sizeof(SOCKADDR));

                }
                else if (count < stringlen)
                    tempx += " ", tempy += " ";
            }
            if (count) {
                send_jsonobj.insert("x", tempx);
                send_jsonobj.insert("y", tempy);
                order_str = QString(QJsonDocument(send_jsonobj).toJson());
                sendBuf = order_str.toLocal8Bit().data();
                sendLen = 2 * order_str.length()+1;
                ::sendto(ClientSocket, order_str.toLocal8Bit().data(), sendLen, 0, (SOCKADDR*)&RecvAddr, sizeof(SOCKADDR));
                //::sendto(ClientSocket, sendBuf, sendLen, 0, (SOCKADDR*)&RecvAddr, sizeof(SOCKADDR));
                qDebug() << "正在发送..." << "len: " << count << " type: " << send_jsonobj["order_type"].toInt();
            }
            send_jsonobj.remove("x");
            send_jsonobj.remove("y");
            send_jsonobj["order_type"] = EXITINTB_DATA;
            order_str = QString(QJsonDocument(send_jsonobj).toJson());
            sendBuf = order_str.toLocal8Bit().data();
            sendLen = 2 * order_str.length()+1;
            ::sendto(ClientSocket, order_str.toLocal8Bit().data(), sendLen, 0, (SOCKADDR*)&RecvAddr, sizeof(SOCKADDR));
            //::sendto(ClientSocket, sendBuf, sendLen, 0, (SOCKADDR*)&RecvAddr, sizeof(SOCKADDR));
            qDebug() << "结束传输!" << send_jsonobj;
            do {
                ::recvfrom(ClientSocket, recvBuf, maxbyte, 0, (SOCKADDR*)&RecvAddr, &len);
                qDebug() << "收到结束返回";
                data_str = QString(QLatin1String(recvBuf));
                jsonDocument = QJsonDocument::fromJson(data_str.toLocal8Bit().data());
                jsonObject = jsonDocument.object();
            } while (RINSRTTB_DATA != jsonObject["order_type"].toInt());
            //qDebug() << send_jsonobj;
            switch(jsonObject["value"].toInt()) {
            case NEXISTB_VALUE:
                qDebug() << "该表不存在！";
                break;
            case FINSRTTB_VALUE:
                qDebug() << "表" << TB_name << "插入数据失败！请检查原因！";
                break;
            case INSERTTB_VALUE:
                qDebug() << "表" << TB_name << "插入数据成功";
                break;
            }
            break;
        case QUERY_DATA:
            qDebug() << "查询成功";
            if (TABLENAME_QUERY == QueryOrder)
                QueryData[0].append(jsonObject["table_name"].toString().split(" "));
            else if (USERNAME_QUERY == QueryOrder)
                QueryData[0].append(jsonObject["user_name"].toString().split(" "));
            else if (XYCONTENT_QUERY == QueryOrder) {
                QueryData[0].append(jsonObject["x"].toString().split(" "));
                QueryData[1].append(jsonObject["y"].toString().split(" "));
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
QStringList MyClient::GetUserNameList(){
    return QueryDataFromServer(USERNAME_QUERY)[0];
}
MyClient::~MyClient() {
    closesocket(ClientSocket);
    WSACleanup();
}

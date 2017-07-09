#include "MySocket.h"

MySocket::MySocket() :
	hostname("localhost"),
	root("root"),
	passwd("930930"),
	port(3306),
	ip_addr("115.156.217.168")
{
}

MySocket::~MySocket()
{
	// 删除MySql对象
	delete Sql_data;
	// 关闭套接字
	closesocket(servSock);
	// 终止 DLL 的使用
	WSACleanup();
}

void MySocket::InitSocket() {
	//初始化 DLL
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建套接字
	servSock = socket(AF_INET, SOCK_DGRAM, 0);
	nSize = sizeof(SOCKADDR);
	//绑定套接字
	memset(&sockAddr, 0, sizeof(sockAddr));		// 每个字节都用0填充
	sockAddr.sin_family = AF_INET;				// 使用IPv4地址
	sockAddr.sin_addr.S_un.S_addr = inet_addr(ip_addr.c_str());  //具体的IP地址
	sockAddr.sin_port = htons(1234);			// 端口
	bind(servSock, (SOCKADDR*)&sockAddr, nSize);

	Sql_data = new My_MySQL();
	Sql_data->InitMySql(hostname, port, root, passwd);

	stopsend["order_type"] = EXIT_DATA;
	stopsend_str = stopsend.toStyledString();
}

//向客户端发送数据
void MySocket::ListenClient() {
	char recvBuf[100];

	while (1) {
		datasend.clear();
		recvfrom(servSock, recvBuf, 100, 0, (SOCKADDR*)&sockAddr, &nSize);
		int order_list = -1;
		Json::Value val;
		Json::Reader reader;
		//std::cout << recvBuf;
		if (reader.parse(recvBuf, val)) {
			order_list = val["order_type"].asInt();
		}
		Sql_data->SetUserName(val["user"].asString());
		vector<string> res;
		if (order_list == QUERYDB_ORDER) {
			datasend["order_type"] = DATABASE_DATA;
			res = Sql_data->GetMysqlDataBase();
			for each (string var in res) {
				datasend["database"] = var;
				datasend_str = datasend.toStyledString();
				sendto(servSock, datasend_str.c_str(), datasend_str.length() + 1, \
					0, (SOCKADDR*)&sockAddr, nSize);
			}
		}
		else if (order_list == QUERYTB_ORDER) {
			datasend["order_type"] = TABLE_DATA;
			string dbname = val["db_name"].asString();
			Sql_data->SetDataBaseName(dbname);
			res = Sql_data->GetMysqlTable();
			for each (string var in res) {
				datasend["table"] = var;
				datasend_str = datasend.toStyledString();
				sendto(servSock, datasend_str.c_str(), datasend_str.length() + 1, \
					0, (SOCKADDR*)&sockAddr, nSize);
			}
		}
		else if (order_list == CREATEDB_ORDER) {
			datasend["order_type"] = RETURNDB_DATA;
			string dbname = val["db_name"].asString();
			Sql_data->SetDataBaseName(dbname);
			int flag = Sql_data->CreateDataBase();
			datasend["value"] = flag;
			datasend_str = datasend.toStyledString();
			sendto(servSock, datasend_str.c_str(), datasend_str.length() + 1, \
				0, (SOCKADDR*)&sockAddr, nSize);
		}
		else if (order_list == CREATETB_ORDER) {
			datasend["order_type"] = RETURNTB_DATA;
			string dbname = val["db_name"].asString();
			string tbname = val["tb_name"].asString();
			Sql_data->SetDataBaseName(dbname);
			Sql_data->SetTableName(tbname);
			int flag = Sql_data->CreateTable();
			datasend["value"] = flag;
			datasend_str = datasend.toStyledString();
			sendto(servSock, datasend_str.c_str(), datasend_str.length() + 1, \
				0, (SOCKADDR*)&sockAddr, nSize);
		}
		sendto(servSock, stopsend_str.c_str(), stopsend_str.length() + 1, \
			0, (SOCKADDR*)&sockAddr, nSize);
	}
	// 删除数据库对象
	delete Sql_data;
}
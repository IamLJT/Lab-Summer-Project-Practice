#include "MySocket.h"

MySocket::MySocket() :
	hostname("localhost"),
	root("root"),
	passwd("930930"),
	port(3306),
	ip_addr("115.156.217.168")
	//ip_addr("10.11.73.61")
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
	sockAddr.sin_port = htons(1235);			// 端口
	bind(servSock, (SOCKADDR*)&sockAddr, nSize);

	Sql_data = new My_MySQL();
	Sql_data->InitMySql(hostname, port, root, passwd);

	stopsend["order_type"] = EXIT_DATA;
	stopsend_str = stopsend.toStyledString();
}

//向客户端发送数据
void MySocket::ListenClient() {
	int insertflag = -1;

	while (1) {
		datasend.clear();
		char recvBuf[MAXBYTE] = { 0 };
		recvfrom(servSock, recvBuf, MAXBYTE, 0, (SOCKADDR*)&sockAddr, &nSize);
		cout << recvBuf << endl;
		int order_list = -1;
		Json::Value val;
		Json::Reader reader;
		if (reader.parse(recvBuf, val)) {
			order_list = val["order_type"].asInt();
		}
		Sql_data->SetUserName(val["user"].asString());
		vector<string> res;
		// 查询数据库
		if (order_list == QUERYDB_ORDER) {
			datasend["order_type"] = DATABASE_DATA;
			res = Sql_data->GetMysqlDataBase();
			for each (string var in res) {
				datasend["database"] = var;
				datasend_str = datasend.toStyledString();
				cout << datasend_str << endl;
				sendto(servSock, datasend_str.c_str(), datasend_str.length() + 1, \
					0, (SOCKADDR*)&sockAddr, nSize);
			}
		}
		// 查询表
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
		// 创建数据库
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
		// 创建表
		else if (order_list == CREATETB_ORDER) {
			datasend["order_type"] = RETURNTB_DATA;
			string dbname = val["db_name"].asString();
			string tbname = val["tb_name"].asString();
			cout << tbname << endl;
			Sql_data->SetDataBaseName(dbname);
			Sql_data->SetTableName(tbname);
			int flag = Sql_data->CreateTable();
			datasend["value"] = flag;
			datasend_str = datasend.toStyledString();
			sendto(servSock, datasend_str.c_str(), datasend_str.length() + 1, \
				0, (SOCKADDR*)&sockAddr, nSize);
		}
		// 删除数据库
		else if (order_list == DELETEDB_ORDER) {
			datasend["order_type"] = DELETEDB_DATA;
			string dbname = val["db_name"].asString();
			Sql_data->SetDataBaseName(dbname);
			int flag = Sql_data->DeleteDataBase();
			datasend["value"] = flag;
			datasend_str = datasend.toStyledString();
			sendto(servSock, datasend_str.c_str(), datasend_str.length() + 1, \
				0, (SOCKADDR*)&sockAddr, nSize);
		}
		// 删除表
		else if (order_list == DELETETB_ORDER) {
			datasend["order_type"] = DELETETB_DATA;
			string dbname = val["db_name"].asString();
			string tbname = val["tb_name"].asString();
			Sql_data->SetDataBaseName(dbname);
			Sql_data->SetTableName(tbname);
			int flag = Sql_data->DeleteTable();
			datasend["value"] = flag;
			datasend_str = datasend.toStyledString();
			sendto(servSock, datasend_str.c_str(), datasend_str.length() + 1, \
				0, (SOCKADDR*)&sockAddr, nSize);
		}
		// 插入数据
		else if (order_list == INSERTTB_ORDER) {
			//cout << recvBuf << endl;
			datasend["order_type"] = INSERTTB_DATA;
			datasend_str = datasend.toStyledString();
			sendto(servSock, datasend_str.c_str(), datasend_str.length() + 1, \
				0, (SOCKADDR*)&sockAddr, nSize);

			datasend.clear();
			int flag0 = INSERTTB_VALUE, flag = -1;
			datasend["order_type"] = RINSRTTB_DATA;
			if (false == Sql_data->ExistTable()) {
				flag0 = NEXISTB_VALUE;
			}
			Sql_data->MyQuery("START TRANSACTION");
			while (1) {
				memset(recvBuf, 0, MAXBYTE);
				recvfrom(servSock, recvBuf, MAXBYTE, 0, (SOCKADDR*)&sockAddr, &nSize);
				if (reader.parse(recvBuf, val)) {
					order_list = val["order_type"].asInt();
				}
				cout << recvBuf << endl;
				if (INSERTTB_DATA == order_list) {
					string x = val["x"].asString();
					string y = val["y"].asString();
					if (x.empty()) continue;
					string dbname = val["db_name"].asString();
					string tbname = val["tb_name"].asString();
					Sql_data->SetDataBaseName(dbname);
					Sql_data->SetTableName(tbname);
					flag = Sql_data->InsertTable(x, y);
					if (flag == NEXISTB_VALUE) {
						flag0 = flag;
						continue;
					}
					else if (flag == FINSRTTB_VALUE) {
						if (flag0 != NEXISTB_VALUE)
							flag0 = flag;
						continue;
					}
				}
				else if (EXITINTB_DATA == order_list) {
					Sql_data->MyQuery("COMMIT");
					Sql_data->CloseMySql();
					datasend["value"] = flag0;
					datasend_str = datasend.toStyledString();
					//cout << datasend_str << endl;
					sendto(servSock, datasend_str.c_str(), datasend_str.length() + 1, \
						0, (SOCKADDR*)&sockAddr, nSize);
					break;
				}
			}
		}
		else if (order_list == QUERY_ORDER) {
			datasend["order_type"] = QUERY_DATA;
			int content = val["content"].asInt();
			string dbname = val["db_name"].asString();
			string tbname = val["tb_name"].asString();
			Sql_data->SetDataBaseName(dbname);
			Sql_data->SetTableName(tbname);
			if (TABLENAME_QUERY == content) {
				vector<string> res = Sql_data->QueryTableByName();
				for each (string var in res) {
					datasend["table_name"] = var;
					datasend_str = datasend.toStyledString();
					cout << datasend_str << endl;
					sendto(servSock, datasend_str.c_str(), datasend_str.length() + 1, \
						0, (SOCKADDR*)&sockAddr, nSize);
				}
			}
			else if (USERNAME_QUERY == content) {
				vector<string> res = Sql_data->QueryTableUserName();
				for each (string var in res) {
					datasend["user_name"] = var;
					datasend_str = datasend.toStyledString();
					cout << datasend_str << endl;
					sendto(servSock, datasend_str.c_str(), datasend_str.length() + 1, \
						0, (SOCKADDR*)&sockAddr, nSize);
				}
			}
			else if (XYCONTENT_QUERY == content) {
				vector<pair<string, string>> res = Sql_data->QueryTableByCont();
				for each (pair<string, string> var in res) {
					datasend["x"] = var.first;
					datasend["y"] = var.second;
					datasend_str = datasend.toStyledString();
					cout << datasend_str << endl;
					sendto(servSock, datasend_str.c_str(), datasend_str.length() + 1, \
						0, (SOCKADDR*)&sockAddr, nSize);
				}
			}
		}
		sendto(servSock, stopsend_str.c_str(), stopsend_str.length() + 1, \
			0, (SOCKADDR*)&sockAddr, nSize);
	}
}
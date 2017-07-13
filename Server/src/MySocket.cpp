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
	const int maxlen = 10000;
	const int maxbyte = 128 * 1024;
	/*Sql_data->SetUserName("zjh");
	Sql_data->SetDataBaseName("zjh");
	Sql_data->CreateDataBase();
	Sql_data->SetTableName("ruili");
	Sql_data->CreateTable();
	Sql_data->ExistTable();
	Sql_data->MyQuery("START TRANSACTION");
	for (int i = 0; i < 10000; ++i) {
		Sql_data->InsertTable("x", "y");
	}
	Sql_data->MyQuery("COMMIT");
	Sql_data->CloseMySql();
	*//**/
	while (1) {
		datasend.clear();
		char recvBuf[maxbyte] = { 0 };
		recvfrom(servSock, recvBuf, maxbyte, 0, (SOCKADDR*)&sockAddr, &nSize);
		string str = recvBuf;
		//str = GBKToUTF8(str);
		//cout << recvBuf << endl;
		
		//cout << recvBuf << endl;
		int order_list = -1;
		Json::Value val;
		Json::Reader reader;
		
		if (reader.parse(recvBuf, val)) {
			order_list = val["order_type"].asInt();
		}
		//cout << val << endl;
		//cout << val["user"].asString();
		Sql_data->SetUserName(val["user"].asString());
		vector<string> res;
		// 查询数据库
		if (order_list == QUERYDB_ORDER) {
			datasend["order_type"] = DATABASE_DATA;
			res = Sql_data->GetMysqlDataBase();
			for each (string var in res) {
				datasend["database"] = var;
				datasend_str = datasend.toStyledString();
				//cout << datasend_str << endl;
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
			//cout << dbname << endl;
			Sql_data->SetDataBaseName(dbname);
			int flag = Sql_data->CreateDataBase();
			datasend["value"] = flag;
			datasend_str = datasend.toStyledString();
			sendto(servSock, datasend_str.c_str(), datasend_str.size() + 1, \
				0, (SOCKADDR*)&sockAddr, nSize);
		}
		// 创建表
		else if (order_list == CREATETB_ORDER) {
			datasend["order_type"] = RETURNTB_DATA;
			string dbname = val["db_name"].asString();
			string tbname = val["tb_name"].asString();
			Sql_data->SetDataBaseName(dbname);
			Sql_data->SetTableName(tbname);
			int flag = Sql_data->CreateTable();
			datasend["value"] = flag;
			datasend_str = datasend.toStyledString();
			sendto(servSock, datasend_str.c_str(), datasend_str.size() + 1, \
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
			sendto(servSock, datasend_str.c_str(), datasend_str.size() + 1, \
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
			sendto(servSock, datasend_str.c_str(), datasend_str.size() + 1, \
				0, (SOCKADDR*)&sockAddr, nSize);
		}
		// 插入数据
		else if (order_list == INSERTTB_ORDER) {
			//cout << recvBuf << endl;
			datasend["order_type"] = INSERTTB_DATA;
			datasend_str = datasend.toStyledString();
			sendto(servSock, datasend_str.c_str(), datasend_str.size() + 1, \
				0, (SOCKADDR*)&sockAddr, nSize);

			datasend.clear();
			string dbname = val["db_name"].asString();
			string tbname = val["tb_name"].asString();
			Sql_data->SetDataBaseName(dbname);
			Sql_data->SetTableName(tbname);
			int flag0 = INSERTTB_VALUE, flag = -1;
			if (false == Sql_data->ExistTable()) {
				flag0 = NEXISTB_VALUE;
			}
			Sql_data->MyQuery("START TRANSACTION");
			int i = 0;
			while (1) {
				memset(recvBuf, 0, maxbyte);
				order_list = -1;
				val.clear();
				
				recvfrom(servSock, recvBuf, maxbyte, 0, (SOCKADDR*)&sockAddr, &nSize);
				if (reader.parse(recvBuf, val)) {
					order_list = val["order_type"].asInt();
				}
				vector<string> vx, vy;
				cout << (++i) << "次" << order_list << endl;
				if (INSERTTB_DATA == order_list) {
					cout << "正在插入..." << endl;
					string x = val["x"].asString();
					string y = val["y"].asString();
					SplitString(x, vx, " ");
					SplitString(y, vy, " ");
					if (vx.empty() || vy.empty()) continue;
					cout << "len:" << vx.size() << endl;
					for (int i = 0; i < vx.size(); ++i) {
						if (vx[i].empty() || vy[i].empty()) continue;
						flag = Sql_data->InsertTable(vx[i], vy[i]);
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
				}
				else if (EXITINTB_DATA == order_list) {
					cout << "收到结束" << endl;
					Sql_data->MyQuery("COMMIT");
					Sql_data->CloseMySql();
					datasend["order_type"] = RINSRTTB_DATA;
					datasend["value"] = flag0;
					datasend_str = datasend.toStyledString();
					cout << "插入结束" << endl;
					sendto(servSock, datasend_str.c_str(), datasend_str.size() + 1, \
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
			int count = 0;
			int len = 0;
			string temp = "";
			if (TABLENAME_QUERY == content) {
				vector<string> res = Sql_data->QueryTableByName();
				len = res.size();
				for each (string var in res) {
					temp += var;
					count++;
					if (count % maxlen == 0) {
						datasend["table_name"] = temp;
						temp = "";
						datasend_str = datasend.toStyledString();
						sendto(servSock, datasend_str.c_str(), datasend_str.size() + 1, \
							0, (SOCKADDR*)&sockAddr, nSize);
					}
					else if (count < len){
						temp += " ";
					}
				}
				if (count % maxlen) {
					datasend["table_name"] = temp;
					datasend_str = datasend.toStyledString();
					//cout << datasend_str << endl;
					sendto(servSock, datasend_str.c_str(), datasend_str.size() + 1, \
						0, (SOCKADDR*)&sockAddr, nSize);
				}
			}
			else if (USERNAME_QUERY == content) {
				vector<string> res = Sql_data->QueryTableUserName();
				len = res.size();
				for each (string var in res) {
					temp += var;
					count++;
					if (count % maxlen == 0) {
						datasend["user_name"] = temp;
						temp = "";
						datasend_str = datasend.toStyledString();
						cout << datasend_str << endl;
						sendto(servSock, datasend_str.c_str(), datasend_str.size() + 1, \
							0, (SOCKADDR*)&sockAddr, nSize);
					}
					else if (count < len) {
						temp += " ";
					}
				}
				if (count % maxlen) {
					datasend["user_name"] = temp;
					datasend_str = datasend.toStyledString();
					//cout << datasend_str << endl;
					sendto(servSock, datasend_str.c_str(), datasend_str.size() + 1, \
						0, (SOCKADDR*)&sockAddr, nSize);
				}
			}
			else if (XYCONTENT_QUERY == content) {
				vector<pair<string, string>> res = Sql_data->QueryTableByCont();
				len = res.size();
				string tempx = "", tempy = "";
				for each (pair<string, string> var in res) {
					tempx += var.first;
					tempy += var.second;
					count++;
					if (count % maxlen == 0) {
						datasend["x"] = tempx;
						datasend["y"] = tempy;
						tempx = "";
						tempy = "";
						datasend_str = datasend.toStyledString();
						cout << datasend_str << endl;
						sendto(servSock, datasend_str.c_str(), datasend_str.size() + 1, \
							0, (SOCKADDR*)&sockAddr, nSize);
					}
					else if (count < len)
						tempx += " ", tempy += " ";
				}
				if (count % maxlen) {
					datasend["x"] = tempx;
					datasend["y"] = tempy;
					datasend_str = datasend.toStyledString();
					//cout << datasend_str << endl;
					sendto(servSock, datasend_str.c_str(), datasend_str.size() + 1, \
						0, (SOCKADDR*)&sockAddr, nSize);
				}
			}
			cout << "查询成功！" << endl;
		}
		sendto(servSock, stopsend_str.c_str(), stopsend_str.size() + 1, \
			0, (SOCKADDR*)&sockAddr, nSize);
	}/**/
}

// 切割字符串
void SplitString(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

//GBK编码转换到UTF8编码
int GBKToUTF8(unsigned char * lpGBKStr, unsigned char * lpUTF8Str, int nUTF8StrLen)
{
	wchar_t * lpUnicodeStr = NULL;
	int nRetLen = 0;

	if (!lpGBKStr)  //如果GBK字符串为NULL则出错退出
		return 0;

	nRetLen = ::MultiByteToWideChar(CP_ACP, 0, (char *)lpGBKStr, -1, NULL, NULL);  //获取转换到Unicode编码后所需要的字符空间长度
	lpUnicodeStr = new WCHAR[nRetLen + 1];  //为Unicode字符串空间
	nRetLen = ::MultiByteToWideChar(CP_ACP, 0, (char *)lpGBKStr, -1, lpUnicodeStr, nRetLen);  //转换到Unicode编码
	if (!nRetLen)  //转换失败则出错退出
		return 0;

	nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, NULL, 0, NULL, NULL);  //获取转换到UTF8编码后所需要的字符空间长度

	if (!lpUTF8Str)  //输出缓冲区为空则返回转换后需要的空间大小
	{
		if (lpUnicodeStr)
			delete[]lpUnicodeStr;
		return nRetLen;
	}

	if (nUTF8StrLen < nRetLen)  //如果输出缓冲区长度不够则退出
	{
		if (lpUnicodeStr)
			delete[]lpUnicodeStr;
		return 0;
	}

	nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, (char *)lpUTF8Str, nUTF8StrLen, NULL, NULL);  //转换到UTF8编码

	if (lpUnicodeStr)
		delete[]lpUnicodeStr;

	return nRetLen;
}

string GBKToUTF8(const std::string& strGBK)
{
	string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n); 
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUTF8;
}
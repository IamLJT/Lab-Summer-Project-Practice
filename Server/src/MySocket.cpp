#include "MySocket.h"

MySocket::MySocket() :
	hostname("localhost"),
	port(3306)
	//ip_addr("115.156.217.168")
	//ip_addr("10.11.73.61")
{
	
}

MySocket::~MySocket()
{
	// ɾ��MySql����
	delete Sql_data;
	// �ر��׽���
	closesocket(servSock);
	// ��ֹ DLL ��ʹ��
	WSACleanup();
}

string GetInternetIP()
{
	char buf[2048] = { 0 };    //����ҳ�ж��������ݷ��ڴ˴�  
	char chURL[128] = { "http://myip.com.tw" };

	//����ҳ����д��c:\i.ini�ļ���  

	char filename[] = { "E:\\myip.ini" };
	
	HRESULT hr = URLDownloadToFileA(0, "http://myip.com.tw", filename, 0, NULL);

	string str_ip("");
	FILE *fp = fopen(filename, "rb+");
	if (fp != NULL)
	{
		//  
		fseek(fp, 0, SEEK_SET);
		fread(buf, 2048, 1, fp);
		fclose(fp);

		//��buf�в��� [ ��λ��, iIndex��buf�д�[��ʼʣ�µ��ַ���������[����ַ��� ==   
		string str = buf;
		int nstart = str.find("<font");
		int nend = str.substr(nstart).find( "</font");
		int lenth = nend - 18;

		str_ip = str.substr(nstart + 18, lenth);
	}

	remove(filename);

	return str_ip;
}

string GetLocalIpAddress()
{
	WORD wVersionRequested = MAKEWORD(2, 2);

	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
		return "";

	char local[255] = { 0 };
	gethostname(local, sizeof(local));
	hostent* ph = gethostbyname(local);
	if (ph == NULL)
		return "";

	in_addr addr;
	memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr)); // �������ȡ��һ��ip  

	string localIP;
	localIP.assign(inet_ntoa(addr));

	WSACleanup();
	return localIP;
}

void MySocket::InitSocket() {
	cout << "��������ʼ��..." << endl;
	string ip_addr = GetInternetIP();
	cout << "����ip��" << ip_addr << endl;

	//��ʼ�� DLL
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//�����׽���
	servSock = socket(AF_INET, SOCK_DGRAM, 0);
	nSize = sizeof(SOCKADDR);
	//���׽���
	memset(&sockAddr, 0, sizeof(sockAddr));		// ÿ���ֽڶ���0���
	sockAddr.sin_family = AF_INET;				// ʹ��IPv4��ַ
	sockAddr.sin_addr.S_un.S_addr = inet_addr(ip_addr.c_str());  //�����IP��ַ
	sockAddr.sin_port = htons(1235);			// �˿�
	bind(servSock, (SOCKADDR*)&sockAddr, nSize);

	Sql_data = new My_MySQL();
	do {
		cout << "���ݿ��˻���";
		getline(cin, root);
		cout << "���ݿ����룺";
		getline(cin, passwd);
	} while(!Sql_data->InitMySql(hostname, port, root, passwd));

	stopsend["order_type"] = EXIT_DATA;
	stopsend_str = stopsend.toStyledString();
}

//��ͻ��˷�������
void MySocket::ListenClient() {
	int insertflag = -1;
	const int maxlen = 10000;
	const int maxbyte = 128 * 1024;

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
		else {
			sendto(servSock, stopsend_str.c_str(), stopsend_str.size() + 1, \
				0, (SOCKADDR*)&sockAddr, nSize);
			continue;
		}
		//cout << val << endl;
		//cout << val["user"].asString();
		Sql_data->SetUserName(val["user"].asString());
		vector<string> res;
		// ��ѯ���ݿ�
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
		// ��ѯ��
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
		// �������ݿ�
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
		// ������
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
		// ɾ�����ݿ�
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
		// ɾ����
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
		// ��������
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
				cout << (++i) << "��" << order_list << endl;
				if (INSERTTB_DATA == order_list) {
					cout << "���ڲ���..." << endl;
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
					cout << "�յ�����" << endl;
					Sql_data->MyQuery("COMMIT");
					Sql_data->CloseMySql();
					datasend["order_type"] = RINSRTTB_DATA;
					datasend["value"] = flag0;
					datasend_str = datasend.toStyledString();
					cout << "�������" << endl;
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
			cout << "��ѯ�ɹ���" << endl;
		}
		sendto(servSock, stopsend_str.c_str(), stopsend_str.size() + 1, \
			0, (SOCKADDR*)&sockAddr, nSize);
	}/**/
}

// �и��ַ���
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

//GBK����ת����UTF8����
int GBKToUTF8(unsigned char * lpGBKStr, unsigned char * lpUTF8Str, int nUTF8StrLen)
{
	wchar_t * lpUnicodeStr = NULL;
	int nRetLen = 0;

	if (!lpGBKStr)  //���GBK�ַ���ΪNULL������˳�
		return 0;

	nRetLen = ::MultiByteToWideChar(CP_ACP, 0, (char *)lpGBKStr, -1, NULL, NULL);  //��ȡת����Unicode���������Ҫ���ַ��ռ䳤��
	lpUnicodeStr = new WCHAR[nRetLen + 1];  //ΪUnicode�ַ����ռ�
	nRetLen = ::MultiByteToWideChar(CP_ACP, 0, (char *)lpGBKStr, -1, lpUnicodeStr, nRetLen);  //ת����Unicode����
	if (!nRetLen)  //ת��ʧ��������˳�
		return 0;

	nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, NULL, 0, NULL, NULL);  //��ȡת����UTF8���������Ҫ���ַ��ռ䳤��

	if (!lpUTF8Str)  //���������Ϊ���򷵻�ת������Ҫ�Ŀռ��С
	{
		if (lpUnicodeStr)
			delete[]lpUnicodeStr;
		return nRetLen;
	}

	if (nUTF8StrLen < nRetLen)  //���������������Ȳ������˳�
	{
		if (lpUnicodeStr)
			delete[]lpUnicodeStr;
		return 0;
	}

	nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, (char *)lpUTF8Str, nUTF8StrLen, NULL, NULL);  //ת����UTF8����

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
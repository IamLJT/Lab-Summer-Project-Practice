#pragma once

#include <winsock2.h>
#include "My_MySQL.h"
#include "order_define.h"
#include "json/json.h"

#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

class MySocket
{
public:
	MySocket();
	~MySocket();

public:
	void InitSocket();
	void ListenClient();

private:
	// 服务器端需要的变量
	WSADATA wsaData;		// 用于初始化DLL
	SOCKET servSock;		// 服务器端套接字
	sockaddr_in sockAddr;	// 绑定的地址
	int nSize;
	string ip_addr;

	// 访问mysql需要的变量
	My_MySQL *Sql_data;
	string hostname;		// 域名
	string root;			// 用户名
	string passwd;			// 密码
	int port;				// 端口

	// 访问关键字
	Json::Value stopsend;	// 传输结束
	Json::Value datasend;	// 传输数据
	string stopsend_str;
	string datasend_str;
};


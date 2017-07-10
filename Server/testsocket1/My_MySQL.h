#pragma once
#include <mysql.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "order_define.h"

using namespace std;

class My_MySQL
{
public:
	My_MySQL();
	~My_MySQL();

	bool InitMySql(string hostname, int port, string root, string passwd); // 初始化数据库

	void SetDataBaseName(string DBname);
	void SetTableName(string TBname);
	void SetUserName(string UserName);

	vector<string> GetMysqlDataBase();
	vector<string> GetMysqlTable();
	int CreateDataBase();
	int CreateTable();
	int DeleteDataBase();
	int DeleteTable();
	bool ExistTable();
	int InsertTable(string x, string y);
	int QueryTable(string user = "ALL");

	MYSQL MyQuery(string query_sql, string database);
	void CloseMySql();

private:
	MYSQL mydata;					// 数据库对象
	MYSQL_RES *result;				// 查询指针
	MYSQL_ROW sql_row;				// 行内容
	string default_databasename;	// 默认访问数据库名
	string databasename;
	string tablename;

	string hostname;
	int port;
	string root;
	string passwd;
	string username;
};


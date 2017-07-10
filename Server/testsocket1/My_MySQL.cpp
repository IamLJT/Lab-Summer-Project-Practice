#include "My_MySQL.h"

My_MySQL::My_MySQL(): 
	default_databasename("myfirstsql")
{

}


My_MySQL::~My_MySQL()
{
}

bool My_MySQL::InitMySql(string hostname, int port, string root, string passwd) {
	this->hostname = hostname;
	this->port = port;
	this->root = root;
	this->passwd = passwd;

	//初始化数据库
	if (0 == mysql_library_init(0, NULL, NULL)) {
		cout << "mysql_library_init() succeed" << endl;
	}
	else {
		cout << "mysql_library_init() failed" << endl;
		return false;
	}

	//初始化数据结构
	if (NULL != mysql_init(&mydata)) {
		cout << "mysql_init() succeed" << endl;
	}
	else {
		cout << "mysql_init() failed" << endl;
		return false;
	}

	//在连接数据库之前，设置额外的连接选项
	//可以设置的选项很多，这里设置字符集，否则无法处理中文
	if (0 == mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk")) {
		cout << "mysql_options() succeed" << endl;
	}
	else {
		cout << "mysql_options() failed" << endl;
		return false;
	}

	return true;
}

vector<string> My_MySQL::GetMysqlDataBase() {
	vector<string> res;

	if (NULL == mysql_real_connect(&mydata, hostname.c_str(), root.c_str(), passwd.c_str(), \
		default_databasename.c_str(), port, NULL, 0)) {
		cout << "连接错误，请检查参数设置" << endl;
		return res;
	}
	string query_sql = "SHOW DATABASES";
	if (mysql_real_query(&mydata, query_sql.c_str(), query_sql.size())) {
		cout << "查询失败，请检查命令是否正确！" << endl;
		return res;
	}

	result = mysql_store_result(&mydata);
	if (result) {
		while (sql_row = mysql_fetch_row(result)){			//获取具体的数据 
			res.push_back(sql_row[0]);
		}
	}

	// 释放数据库
	if (result != NULL)
		mysql_free_result(result);
	mysql_close(&mydata);

	return res;
}

int My_MySQL::CreateDataBase() {
	if (NULL != mysql_real_connect(&mydata, hostname.c_str(), root.c_str(),\
		passwd.c_str(), databasename.c_str(), port, NULL, 0)) {
		return EXISTDB_VALUE;
	}
	string query_sql = "CREATE DATABASE " + databasename;
	// 连接默认数据库
	mysql_real_connect(&mydata, hostname.c_str(), root.c_str(), \
		passwd.c_str(), default_databasename.c_str(), port, NULL, 0);
	if (mysql_real_query(&mydata, query_sql.c_str(), query_sql.size())) {
		mysql_close(&mydata);
		return FAILCDB_VALUE;
	}
	mysql_close(&mydata);
	// 建立查询表
	mysql_real_connect(&mydata, hostname.c_str(), root.c_str(), \
		passwd.c_str(), databasename.c_str(), port, NULL, 0);
	query_sql = "CREATE TABLE IF NOT EXISTS TABLES";
	query_sql += " (id INT UNSIGNED AUTO_INCREMENT, ";
	query_sql += "table_name VARCHAR(40) NOT NULL, ";
	query_sql += "user VARCHAR(20) NOT NULL, ";
	query_sql += "PRIMARY KEY(id))";
	mysql_real_query(&mydata, query_sql.c_str(), query_sql.size());
	mysql_close(&mydata);
	return SUCSCDB_VALUE;
}

void My_MySQL::SetDataBaseName(string DBname) {
	databasename = DBname;
}

void My_MySQL::SetTableName(string TBname) {
	tablename = TBname;
}

int My_MySQL::CreateTable() {
	mysql_real_connect(&mydata, hostname.c_str(), root.c_str(), \
		passwd.c_str(), databasename.c_str(), port, NULL, 0);

	string query_sql = "SELECT TABLE_NAME FROM ";
	query_sql += "INFORMATION_SCHEMA.TABLES ";
	query_sql += "WHERE TABLE_SCHEMA='";
	query_sql += databasename;
	query_sql += "' AND TABLE_NAME='";
	query_sql += tablename+"'";
	// 判断表是否存在
	mysql_real_query(&mydata, query_sql.c_str(), query_sql.size());
	if (0 != mysql_num_rows(mysql_store_result(&mydata))) {
		mysql_close(&mydata);
		return EXISTTB_VALUE;
	}

	// 创建表
	query_sql = "CREATE TABLE IF NOT EXISTS ";
	query_sql += tablename;
	query_sql += " (id INT UNSIGNED AUTO_INCREMENT, ";
	query_sql += "x VARCHAR(10) NOT NULL, ";
	query_sql += "y VARCHAR(10) NOT NULL, ";
	query_sql += "user VARCHAR(20) NOT NULL, ";
	query_sql += "PRIMARY KEY (id))";
	if (mysql_real_query(&mydata, query_sql.c_str(), query_sql.size())) {
		mysql_close(&mydata);
		return FAILCTB_VALUE;
	}
	query_sql = "INSERT INTO ";
	query_sql += "TABLES (id, table_name, user) ";
	query_sql += "VALUES (default, '";
	query_sql += tablename + "', '";
	query_sql += username + "')";
	if (mysql_real_query(&mydata, query_sql.c_str(), query_sql.size()))
		cout << "Tables表插入失败" << endl;
	mysql_close(&mydata);
	return SUCSCTB_VALUE;
}

vector<string> My_MySQL::GetMysqlTable() {
	vector<string> res;
	if (NULL == mysql_real_connect(&mydata, hostname.c_str(), root.c_str(), passwd.c_str(), \
		databasename.c_str(), port, NULL, 0)) {
		cout << "连接错误，请检查参数设置" << endl;
		return res;
	}
	string query_sql = "SHOW TABLES";
	if (mysql_real_query(&mydata, query_sql.c_str(), query_sql.size())) {
		cout << "查询失败，请检查命令是否正确！" << endl;
		mysql_close(&mydata);
		return res;
	}

	result = mysql_store_result(&mydata);
	if (result) {
		while (sql_row = mysql_fetch_row(result)) {			//获取具体的数据 
			res.push_back(sql_row[0]);
		}
	}

	if (result != NULL)
		mysql_free_result(result);
	mysql_close(&mydata);

	return res;
}

int My_MySQL::DeleteDataBase() {
	if (NULL == mysql_real_connect(&mydata, hostname.c_str(), root.c_str(), \
		passwd.c_str(), databasename.c_str(), port, NULL, 0)) {
		cout << databasename << "数据库不存在" << endl;
		return NEXISDB_VALUE;
	}
	string query_sql = "DROP DATABASE " + databasename;
	if (mysql_real_query(&mydata, query_sql.c_str(), query_sql.size())) {
		cout << "数据库删除失败" << endl;
		mysql_close(&mydata);
		return FAILDDB_VALUE;
	}
	mysql_close(&mydata);
	return SUCSDDB_VALUE;
}

int My_MySQL::DeleteTable() {
	if (false == ExistTable()) {
		mysql_close(&mydata);
		cout << "表不存在" << endl;
		return NEXISTB_VALUE;
	}
	string query_sql = "DROP TABLE " + tablename;
	if (mysql_real_query(&mydata, query_sql.c_str(), query_sql.size())) {
		cout << "表删除失败" << endl;
		mysql_close(&mydata);
		return FAILDTB_VALUE;
	}
	query_sql = "DELETE FROM TABLES WHERE table_name = '" + tablename + "'";
	if (mysql_real_query(&mydata, query_sql.c_str(), query_sql.size())) {
		cout << "表删除失败" << endl;
		mysql_close(&mydata);
		return FAILDTB_VALUE;
	}
	mysql_close(&mydata);
	return SUCSDTB_VALUE;
}

bool My_MySQL::ExistTable() {
	mysql_real_connect(&mydata, hostname.c_str(), root.c_str(), \
		passwd.c_str(), databasename.c_str(), port, NULL, 0);
	string query_sql = "SELECT TABLE_NAME FROM ";
	query_sql += "INFORMATION_SCHEMA.TABLES ";
	query_sql += "WHERE TABLE_SCHEMA='";
	query_sql += databasename;
	query_sql += "' AND TABLE_NAME='";
	query_sql += tablename + "'";
	// 判断表是否存在
	mysql_real_query(&mydata, query_sql.c_str(), query_sql.size());
	if (0 == mysql_num_rows(mysql_store_result(&mydata))) {
		return false;
	}
	return true;
}

int My_MySQL::InsertTable(string x, string y) {
	string query_sql = "INSERT INTO " + tablename;
	query_sql += " (id, x, y, user) VALUES (default, '";
	query_sql += x + "', '" + y + "', '" + username + "')";
	if (mysql_real_query(&mydata, query_sql.c_str(), query_sql.size())) {
		cout << "插入失败" << endl;
		return FINSRTTB_VALUE;
	}
	return INSERTTB_VALUE;
}

vector<string> My_MySQL::QueryTableByName() {
	mysql_real_connect(&mydata, hostname.c_str(), root.c_str(), \
		passwd.c_str(), databasename.c_str(), port, NULL, 0);
	string query_sql = "SELECT TABLE_NAME FROM TABLES ";
	if ("ALL" != username) query_sql += "WHERE USER='" + username + "'";

	vector<string> res;
	if (mysql_real_query(&mydata, query_sql.c_str(), query_sql.size())) {
		cout << "查询失败，请检查命令是否正确！" << endl;
		return res;
	}

	result = mysql_store_result(&mydata);
	if (result) {
		while (sql_row = mysql_fetch_row(result)) {			//获取具体的数据 
			res.push_back(sql_row[0]);
		}
	}
	// 释放数据库
	if (result != NULL)
		mysql_free_result(result);
	mysql_close(&mydata);

	return res;
}

MYSQL My_MySQL::MyQuery(string query_sql) {
	
	return mydata;
}

void My_MySQL::SetUserName(string UserName) {
	username = UserName;
}

void My_MySQL::CloseMySql() {
	mysql_close(&mydata);
}
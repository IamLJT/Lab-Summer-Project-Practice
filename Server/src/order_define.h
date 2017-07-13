#ifndef ORDER_DEFINE_H
#define ORDER_DEFINE_H

//  命令
#define QUERYDB_ORDER   1   //  查询数据库名
#define QUERYTB_ORDER   2   //  查询表名
#define SIGNIN_ORDER    3   //  登录
#define VISIT_ORDER     4   //  访问
#define CREATEDB_ORDER	5   //  新建数据库
#define CREATETB_ORDER	6   //  新建表
#define DELETEDB_ORDER	7   //  删除数据库
#define DELETETB_ORDER	8   //  删除表
#define INSERTTB_ORDER	9   //  插入内容
#define STOPINTB_ORDER	10  //  停止插入
#define QUERY_ORDER		11  //  查询

//  返回数据类型
#define DATABASE_DATA   101   //  数据库名列表
#define TABLE_DATA      102   //  表名列表

#define RETURNTB_DATA	103   //  新建数据库返回
#define RETURNDB_DATA	104   //  新建表返回
#define DELETEDB_DATA	105   //  删除数据库返回
#define DELETETB_DATA	106   //  删除表返回
#define INSERTTB_DATA	107   //  插入内容标记
#define RINSRTTB_DATA   108   //  插入内容返回
#define EXITINTB_DATA	109   //  结束插入标记
#define QUERY_DATA		110  //  查询返回

#define EXIT_DATA       120  //  结束返回

//  返回值
#define EXISTDB_VALUE	0   //  数据库已存在
#define FAILCDB_VALUE	1   //  创建数据库失败
#define SUCSCDB_VALUE	2   //  创建数据库成功
#define EXISTTB_VALUE	0   //  表已存在
#define FAILCTB_VALUE	1   //  创建表失败
#define SUCSCTB_VALUE	2   //  创建表成功
#define NEXISDB_VALUE	0   //  数据库不存在
#define FAILDDB_VALUE	1   //  删除数据库失败
#define SUCSDDB_VALUE	2   //  删除数据库成功
#define NEXISTB_VALUE	0   //  表不存在
#define FAILDTB_VALUE	1   //  删除表失败
#define SUCSDTB_VALUE	2   //  删除表成功
#define INSERTTB_VALUE	1   //  向表插入内容成功
#define FINSRTTB_VALUE	2   //  向表插入内容失败
#define SUCSQTB_VALUE	1   //  查询成功
#define FAILQTB_VALUE	2   //  查询失败

// 查询内容
#define USERNAME_QUERY  0	// 查询当前表的用户名
#define TABLENAME_QUERY 1	// 查询当前用户的表名
#define XYCONTENT_QUERY 2   // 查询当前表的xy内容

#endif // ORDER_DEFINE_H

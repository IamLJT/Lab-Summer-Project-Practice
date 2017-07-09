# Lab-Summer-Project-Practice

## 客户端上的代码
## 首先运行服务器上的Server，目前只能对本地的有效，且只能有一台作为主服务器
## 服务器需要安装mysql，下载链接为：http://pan.baidu.com/s/1jIbvKmM
## 然后将安装目录下的include添加的vs的包含目录，lib添加到附加库目录中，并添加依赖项libmysql.lib（这里一定写的只能有.lib，有的资料上写着要添加.dll，但是添加后就无法使用了）,还要看mysql用的是多少位的附加库，附加库链接为：http://pan.baidu.com/s/1c4IoCQ。
## 此外代码中使用的json包链接为：http://pan.baidu.com/s/1skF2HNf，两种方法使用，第一种用makefile进行编译，第二种是直接将src和include的文件拷贝到项目目录下，代码中已实现。
## 从客户机上访问打开409client目录中的.pro文件

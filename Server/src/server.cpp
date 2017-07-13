#include <iostream>
#include <string>
#include <vector>

#include "MySocket.h"

using namespace std;

int main() {
	//接收客户端请求N
	MySocket *mysocket = new MySocket;
	mysocket->InitSocket();
	mysocket->ListenClient();

	/*char *uu = "{\n\"name\":\"刘鉴霆\"}";
	Json::Value val;
	Json::Reader reader;
	reader.parse(uu, val);
	cout << val["name"].asString() << endl;*/

	delete mysocket;
	
	system("pause");
	return 0;
}
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

	delete mysocket;
	
	return 0;
}
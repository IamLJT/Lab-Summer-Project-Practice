#include <iostream>
#include <string>
#include <vector>

#include "MySocket.h"

using namespace std;

int main() {
	//���տͻ�������N
	MySocket *mysocket = new MySocket;
	mysocket->InitSocket();
	mysocket->ListenClient();

	delete mysocket;
	
	return 0;
}
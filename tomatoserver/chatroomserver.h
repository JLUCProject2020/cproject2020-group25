#include<stdio.h>
#include<windows.h>
#include<process.h>
#include<conio.h>
#pragma once
#pragma comment(lib,"ws2_32.lib")
//----------------全局变量---用于定义socket和协议版本号-------------------
WSADATA wsaData1;
SOCKET clientsocket1[200], serversocket1;
int i1 = 0;//i为记录用户个数的变量
//------------------------------------------------------------------------
void communicate(int t) {
	char buff[1024];
	int r = 0;
	while (1) {
		memset(buff, 0, sizeof(char) * 1023);
		r = recv(clientsocket1[t], buff, 1023, NULL);
		printf("%s", buff);
		if (r > 0) {
			buff[r] = 0;
			for (int g = 0; g < i1; g++) {
				if (g != t) {
					send(clientsocket1[g], buff, strlen(buff), NULL);
				}
			}

		}
	}
}
//-此函数用于服务端用于与客户端通信，不停地从客户端recv字符串并广播出去---
//可看作接受用户的子函数--------------------------------------------------
void jieshouyonghu() {
	int t;
	t = listen(serversocket1, 5);
	if (t == -1) {
		printf("监听失败");
		closesocket(serversocket1);
		WSACleanup();
	}
	SOCKADDR_IN cadd = { 0 };//定义用户地址
	int len = sizeof cadd;
	while (1) {
		//等待客户端连接 阻塞
		clientsocket1[i1] = accept(serversocket1, (sockaddr*)&cadd, &len);
		printf("当前有%d位用户接入聊天室\n", i1 + 1);//一旦有用户接入就创造一个线程与之通信
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)communicate, (char*)i1, NULL, NULL);
		i1++;
	}
}
//此函数用于监听和接受用户，一旦有用户加入就添加新的线程用于连接----------
void serversocketmake() {
	//-------------------------请求协议版本-----------------------------------
	WSAStartup(MAKEWORD(2, 2), &wsaData1);	if (LOBYTE(wsaData1.wVersion) != 2 || HIBYTE(wsaData1.wVersion) != 2) {
		printf("请求协议版本失败");
	}
	//--------------------------创建socket------------------------------------
	serversocket1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serversocket1) {
		printf("创建socket失败");
		WSACleanup();
	}
	//---------------------初始化服务器端socket地址族--------------------------
	SOCKADDR_IN add = { 0 };
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add.sin_port = htons(12301);//80,23 号已经被系统内核占用了，别用
//---------------------------绑定socket与地址------------------------------
	int r = bind(serversocket1, (sockaddr*)&add, sizeof add);
	if (r == -1) {
		printf("socket绑定地址失败");
		closesocket(serversocket1);
		WSACleanup();
	}

}
int chatroomserver() {
	serversocketmake();
	jieshouyonghu();
	return 0;
}

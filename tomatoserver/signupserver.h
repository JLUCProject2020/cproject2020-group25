#pragma once
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
typedef struct u {
	char name[20];
	char passward[20];
	int times;//记录次数
}people;
#pragma comment(lib,"ws2_32.lib")
//-------------------------------------------------------------------------
int i = 0;//用于记录用户个数
WSADATA wsaData;
SOCKET clientsocket[200], serversocket;
//-------------------------------全局变量----------------------------------
people tornup(char mes[1024]) {
	int count = 0, j = 0;
	people client = { 0 };
	while (mes[count] != '\0') {
		while (mes[count] != (char)127) {
			client.name[j] = mes[count];
			count++;
			j++;
		}
		count++;
		client.name[count] = '\0';
		j = 0;
		while (mes[count] != '\0') {
			client.passward[j] = mes[count];
			count++;
			j++;
		}
		count++;
		client.passward[count] = '\0';
		break;
	}
	return client;
}
void doc(char mes[]) {
	FILE *fp;
	people client;
	fopen_s(&fp, "D://tomato/clientinformation.txt", "ab+");
	client = tornup(mes);
	fwrite((void*)&client, sizeof(people), 1, fp);
	fclose(fp);
}
void signup(int i) {
	char mes[1051] = { 0 };
	int r = recv(clientsocket[i], mes, 1024, NULL);
	doc(mes);
	closesocket(clientsocket[i]);
}
void clientrecv4() {
	SOCKADDR_IN cadd = { 0 };
	int len = sizeof(cadd);
	while (1) {
		int t;
		t = listen(serversocket, 5);
		if (t == -1) {
			printf("监听失败");
			closesocket(serversocket);
			WSACleanup();
		}
		//等待客户端连接 阻塞
		clientsocket[i] = accept(serversocket, (sockaddr*)&cadd, &len);
		printf("排行榜系统有%d人注册\n", i + 1);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)signup, (char*)i, NULL, NULL);
		//一旦有用户接入就创造一个线程与之交流
		i++;
	}
}
void serversocketmake4() {
	//-------------------------请求协议版本-----------------------------------
	WSAStartup(MAKEWORD(2, 2), &wsaData);	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		printf("请求协议版本失败");
	}
	//--------------------------创建socket------------------------------------
	serversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serversocket) {
		printf("创建socket失败");
		WSACleanup();
	}
	//---------------------初始化服务器端socket地址族--------------------------
	SOCKADDR_IN add = { 0 };
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add.sin_port = htons(12356);//80,23 号已经被系统内核占用了，别用
//---------------------------绑定socket与地址------------------------------
	int r = bind(serversocket, (sockaddr*)&add, sizeof add);
	if (r == -1) {
		printf("socket绑定地址失败");
		closesocket(serversocket);
		WSACleanup();
	}
}
int signupserver() {
	serversocketmake4();
	clientrecv4();
	return 0;
}

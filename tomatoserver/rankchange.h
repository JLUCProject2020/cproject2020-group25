#pragma once
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
typedef struct {
	char name[20];
	char passward[20];
	int times;//记录次数
}people5;
#pragma comment(lib,"ws2_32.lib")
//-------------------------------------------------------------------------
int i5 = 0;//用于记录用户个数
WSADATA wsaData5;
SOCKET clientsocket5[200], serversocket5;
char name[20];
//-------------------------------全局变量----------------------------------
void order() {
	FILE *fp;
	fp=fopen( "D://tomato/clientinformation.txt", "rb+");
	fseek(fp, 0, SEEK_SET);
	people5 moumou, tem;//tem是交换时使用的变量
	int times[100], i = 0;//times用于存储变量的次数，从而完成排序
	char ch = 0;
	memset(times, 0, sizeof(int) * 100);
	while (feof(fp) == 0 && ch != EOF) {//ch的作用避免因为结束符号再跑一遍
		fread(&moumou, sizeof(people5), 1, fp);
		times[i] = moumou.times;
		i++;//记录用户个数
		ch = getc(fp);
		fseek(fp, i * sizeof(people5), SEEK_SET);
	}
	for (int j = 0; j <= i; j++) {
		for (int g = j + 1; g <= i; g++) {
			if (times[j] < times[g]) {
				fseek(fp, sizeof(people5)*j, SEEK_SET);
				fread(&moumou, sizeof(people5), 1, fp);
				tem = moumou;
				fseek(fp, sizeof(people5)*g, SEEK_SET);
				fread(&moumou, sizeof(people5), 1, fp);
				fseek(fp, sizeof(people5)*j, SEEK_SET);
				fwrite(&moumou, sizeof(people5), 1, fp);//将大的值交换到小的值里面
				fseek(fp, sizeof(people5)*g, SEEK_SET);
				fwrite(&tem, sizeof(people5), 1, fp);//将小的值交换到大的值里
			}
		}
	}
	fclose(fp);
}
int addtion() {
	FILE *fp=fopen("D://tomato/clientinformation.txt", "rb+");
	int flag = 20, i = 0;
	people5 moumou;
	char ch = 0;
	while (fread(&moumou, sizeof(people5), 1, fp)!=0) {
		flag = strcmp(moumou.name, name);
		if (flag == 0) {
			moumou.times++;
			fseek(fp, -44, SEEK_CUR);
			fwrite(&moumou, sizeof(people5), 1, fp);
			break;
		}
	}
	fclose(fp);
	return 0;
}
void changerank(int i) {
	while (1) {
		recv(clientsocket5[i], name, 20, NULL);
		addtion();
		order();
	}
}
void clientrecv5() {
	SOCKADDR_IN cadd = { 0 };
	int len = sizeof(cadd);
		int t;
		t = listen(serversocket5, 5);
		if (t == -1) {
			printf("监听失败");
			closesocket(serversocket5);
			WSACleanup();
		}
		while (1) {
		//等待客户端连接 阻塞
		clientsocket5[i5] = accept(serversocket5, (sockaddr*)&cadd, &len);
		printf("有%d人学习\n", i5 + 1);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)changerank, (char*)i5, NULL, NULL);
		//一旦有用户接入就创造一个线程与之交流
		i5++;
	}
}
void serversocketmake5() {
	//-------------------------请求协议版本-----------------------------------
	WSAStartup(MAKEWORD(2, 2), &wsaData5);	if (LOBYTE(wsaData5.wVersion) != 2 || HIBYTE(wsaData5.wVersion) != 2) {
		printf("请求协议版本失败");
	}
	//--------------------------创建socket------------------------------------
	serversocket5 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serversocket5) {
		printf("创建socket失败5");
		WSACleanup();
	}
	//---------------------初始化服务器端socket地址族--------------------------
	SOCKADDR_IN add5 = { 0 };
	add5.sin_family = AF_INET;
	add5.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add5.sin_port = htons(11111);//80,23 号已经被系统内核占用了，别用
//---------------------------绑定socket与地址------------------------------
	int r = bind(serversocket5, (sockaddr*)&add5, sizeof add5);
	if (r == -1) {
		printf("socket绑定地址失败5");
		closesocket(serversocket5);
		WSACleanup();
	}
}
int rankchange() {
	serversocketmake5();
	clientrecv5();
	return 0;
}

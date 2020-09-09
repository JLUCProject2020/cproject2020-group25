#pragma once
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
typedef struct{
	char name[20];
	char passward[20];
	int times;//记录次数
}people3;
#pragma comment(lib,"ws2_32.lib")
//-------------------------------------------------------------------------
int i3= 0;//用于记录用户个数
WSADATA wsaData3;
SOCKET clientsocket3[200], serversocket3;
//-------------------------------全局变量----------------------------------
void broadcasting(int gt) {//gt代表第几个socket
	FILE *fp;
	fp=fopen("D://tomato/clientinformation.txt", "rb+");
	int	j = 0, total = 0, i = 0;
	char mes[1051], ch = 0;
	people3 moumou;
	memset(mes, 0, 1051);
	while (feof(fp) == 0 && ch != EOF) {
		fread(&moumou, sizeof(people3), 1, fp);
		printf("%s:%d\n", moumou.name, moumou.times);
		while (moumou.name[j] != '\0') {
			mes[total] = moumou.name[j];
			total++;
			j++;
		}
		mes[total] = (char)127;
		//---------------------------------大于126的数据和小于126的数据分类
		if (moumou.times < 126) {
			mes[++total] = char(moumou.times % 126);
			mes[++total] = char(moumou.times % 126);
		}
		else {
			mes[++total] = char(moumou.times % 126);
			mes[++total] = char(moumou.times / 126);
		}
		mes[++total] = (char)127;//间隔数据
		total++;
		j = 0;
		i++;
		ch = getc(fp);
		fseek(fp, sizeof(people3)*i, SEEK_SET);
	}
	mes[total + 1] = '\0';
	send(clientsocket3[gt], mes, 1024, NULL);
	fclose(fp);
}
void clientrecv3() {
	SOCKADDR_IN cadd = { 0 };
	int len = sizeof(cadd);
	while (1) {
		int t;
		t = listen(serversocket3, 5);
		if (t == -1) {
			printf("监听失败");
			closesocket(serversocket3);
			WSACleanup();
		}
		//等待客户端连接 阻塞
		clientsocket3[i3] = accept(serversocket3, (sockaddr*)&cadd, &len);
		printf("排行榜系统有%d人查询\n", i3 + 1);
		broadcasting(i3);
		//一旦有用户接入就创造一个线程与之交流
		i3++;
	}
}
void serversocketmake3() {
	//-------------------------请求协议版本-----------------------------------
	WSAStartup(MAKEWORD(2, 2), &wsaData3);	if (LOBYTE(wsaData3.wVersion) != 2 || HIBYTE(wsaData3.wVersion) != 2) {
		printf("请求协议版本失败");
	}
	//--------------------------创建socket------------------------------------
	serversocket3 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serversocket3) {
		printf("创建socket失败");
		WSACleanup();
	}
	//---------------------初始化服务器端socket地址族--------------------------
	SOCKADDR_IN add = { 0 };
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add.sin_port = htons(12315);//80,23 号已经被系统内核占用了，别用
//---------------------------绑定socket与地址------------------------------
	int r = bind(serversocket3, (sockaddr*)&add, sizeof add);
	if (r == -1) {
		printf("socket绑定地址失败");
		closesocket(serversocket3);
		WSACleanup();
	}
}
int ranklistserver() {
	serversocketmake3();
	clientrecv3();
	return 0;
}


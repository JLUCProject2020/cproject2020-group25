#include<stdio.h>
#include<windows.h>
#include<process.h>
#include<conio.h>
#pragma once
#pragma comment(lib,"ws2_32.lib")
//----------------ȫ�ֱ���---���ڶ���socket��Э��汾��-------------------
WSADATA wsaData1;
SOCKET clientsocket1[200], serversocket1;
int i1 = 0;//iΪ��¼�û������ı���
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
//-�˺������ڷ����������ͻ���ͨ�ţ���ͣ�شӿͻ���recv�ַ������㲥��ȥ---
//�ɿ��������û����Ӻ���--------------------------------------------------
void jieshouyonghu() {
	int t;
	t = listen(serversocket1, 5);
	if (t == -1) {
		printf("����ʧ��");
		closesocket(serversocket1);
		WSACleanup();
	}
	SOCKADDR_IN cadd = { 0 };//�����û���ַ
	int len = sizeof cadd;
	while (1) {
		//�ȴ��ͻ������� ����
		clientsocket1[i1] = accept(serversocket1, (sockaddr*)&cadd, &len);
		printf("��ǰ��%dλ�û�����������\n", i1 + 1);//һ�����û�����ʹ���һ���߳���֮ͨ��
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)communicate, (char*)i1, NULL, NULL);
		i1++;
	}
}
//�˺������ڼ����ͽ����û���һ�����û����������µ��߳���������----------
void serversocketmake() {
	//-------------------------����Э��汾-----------------------------------
	WSAStartup(MAKEWORD(2, 2), &wsaData1);	if (LOBYTE(wsaData1.wVersion) != 2 || HIBYTE(wsaData1.wVersion) != 2) {
		printf("����Э��汾ʧ��");
	}
	//--------------------------����socket------------------------------------
	serversocket1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serversocket1) {
		printf("����socketʧ��");
		WSACleanup();
	}
	//---------------------��ʼ����������socket��ַ��--------------------------
	SOCKADDR_IN add = { 0 };
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add.sin_port = htons(12301);//80,23 ���Ѿ���ϵͳ�ں�ռ���ˣ�����
//---------------------------��socket���ַ------------------------------
	int r = bind(serversocket1, (sockaddr*)&add, sizeof add);
	if (r == -1) {
		printf("socket�󶨵�ַʧ��");
		closesocket(serversocket1);
		WSACleanup();
	}

}
int chatroomserver() {
	serversocketmake();
	jieshouyonghu();
	return 0;
}

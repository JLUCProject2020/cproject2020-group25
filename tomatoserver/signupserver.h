#pragma once
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
typedef struct u {
	char name[20];
	char passward[20];
	int times;//��¼����
}people;
#pragma comment(lib,"ws2_32.lib")
//-------------------------------------------------------------------------
int i = 0;//���ڼ�¼�û�����
WSADATA wsaData;
SOCKET clientsocket[200], serversocket;
//-------------------------------ȫ�ֱ���----------------------------------
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
			printf("����ʧ��");
			closesocket(serversocket);
			WSACleanup();
		}
		//�ȴ��ͻ������� ����
		clientsocket[i] = accept(serversocket, (sockaddr*)&cadd, &len);
		printf("���а�ϵͳ��%d��ע��\n", i + 1);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)signup, (char*)i, NULL, NULL);
		//һ�����û�����ʹ���һ���߳���֮����
		i++;
	}
}
void serversocketmake4() {
	//-------------------------����Э��汾-----------------------------------
	WSAStartup(MAKEWORD(2, 2), &wsaData);	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		printf("����Э��汾ʧ��");
	}
	//--------------------------����socket------------------------------------
	serversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serversocket) {
		printf("����socketʧ��");
		WSACleanup();
	}
	//---------------------��ʼ����������socket��ַ��--------------------------
	SOCKADDR_IN add = { 0 };
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add.sin_port = htons(12356);//80,23 ���Ѿ���ϵͳ�ں�ռ���ˣ�����
//---------------------------��socket���ַ------------------------------
	int r = bind(serversocket, (sockaddr*)&add, sizeof add);
	if (r == -1) {
		printf("socket�󶨵�ַʧ��");
		closesocket(serversocket);
		WSACleanup();
	}
}
int signupserver() {
	serversocketmake4();
	clientrecv4();
	return 0;
}

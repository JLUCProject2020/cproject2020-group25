#pragma once
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
typedef struct {
	char name[20];
	char passward[20];
	int times;//��¼����
}people5;
#pragma comment(lib,"ws2_32.lib")
//-------------------------------------------------------------------------
int i5 = 0;//���ڼ�¼�û�����
WSADATA wsaData5;
SOCKET clientsocket5[200], serversocket5;
char name[20];
//-------------------------------ȫ�ֱ���----------------------------------
void order() {
	FILE *fp;
	fp=fopen( "D://tomato/clientinformation.txt", "rb+");
	fseek(fp, 0, SEEK_SET);
	people5 moumou, tem;//tem�ǽ���ʱʹ�õı���
	int times[100], i = 0;//times���ڴ洢�����Ĵ������Ӷ��������
	char ch = 0;
	memset(times, 0, sizeof(int) * 100);
	while (feof(fp) == 0 && ch != EOF) {//ch�����ñ�����Ϊ������������һ��
		fread(&moumou, sizeof(people5), 1, fp);
		times[i] = moumou.times;
		i++;//��¼�û�����
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
				fwrite(&moumou, sizeof(people5), 1, fp);//�����ֵ������С��ֵ����
				fseek(fp, sizeof(people5)*g, SEEK_SET);
				fwrite(&tem, sizeof(people5), 1, fp);//��С��ֵ���������ֵ��
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
			printf("����ʧ��");
			closesocket(serversocket5);
			WSACleanup();
		}
		while (1) {
		//�ȴ��ͻ������� ����
		clientsocket5[i5] = accept(serversocket5, (sockaddr*)&cadd, &len);
		printf("��%d��ѧϰ\n", i5 + 1);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)changerank, (char*)i5, NULL, NULL);
		//һ�����û�����ʹ���һ���߳���֮����
		i5++;
	}
}
void serversocketmake5() {
	//-------------------------����Э��汾-----------------------------------
	WSAStartup(MAKEWORD(2, 2), &wsaData5);	if (LOBYTE(wsaData5.wVersion) != 2 || HIBYTE(wsaData5.wVersion) != 2) {
		printf("����Э��汾ʧ��");
	}
	//--------------------------����socket------------------------------------
	serversocket5 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serversocket5) {
		printf("����socketʧ��5");
		WSACleanup();
	}
	//---------------------��ʼ����������socket��ַ��--------------------------
	SOCKADDR_IN add5 = { 0 };
	add5.sin_family = AF_INET;
	add5.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add5.sin_port = htons(11111);//80,23 ���Ѿ���ϵͳ�ں�ռ���ˣ�����
//---------------------------��socket���ַ------------------------------
	int r = bind(serversocket5, (sockaddr*)&add5, sizeof add5);
	if (r == -1) {
		printf("socket�󶨵�ַʧ��5");
		closesocket(serversocket5);
		WSACleanup();
	}
}
int rankchange() {
	serversocketmake5();
	clientrecv5();
	return 0;
}

#pragma once
#include<stdio.h>
#include<windows.h>
#include<process.h>
#include<string.h>
#pragma comment(lib,"ws2_32.lib")
typedef struct {
	char name[20];
	char passward[20];
	int times;
}people2;
//----------------ȫ�ֱ���---���ڶ���socket��Э��汾��-------------------
WSADATA wsaData2;
SOCKET clientsocket2[200], serversocket2;
people2 client2,sta2;
int i2 = 0;//iΪ��¼�û������ı���
//------------------------------------------------------------------------
bool check(){
	FILE *fp;
	fp=fopen( "D://tomato/clientinformation.txt", "rb+");
	int flag = 0,count=0;
	char ch = 0,j=0;//j �����ж��Ƿ��Ѿ���ȡ���
	fseek(fp, 0, SEEK_SET);
	while (fread(&sta2,44,1,fp)!=0) {
	if (strcmp(sta2.name,client2.name)==0) {
		flag = strcmp(sta2.passward, client2.passward);
		if (flag == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	}
	fclose(fp);
}
void getnameandpassword(){
	int count = 0,j=0;
	char mes[1024];
	recv(clientsocket2[i2], mes, 1024, NULL);
	while (mes[count] != (char)127) {
		client2.name[j] = mes[count];
		j++;
		count++;
	}
	count++; j = 0;
	while (mes[count] != '\0') {
		client2.passward[j] = mes[count];
		j++;
		count++;
	}
	printf("%s\n%s", client2.name, client2.passward);
}
void clientrecv() {
	SOCKADDR_IN cadd = { 0 };
	int len = sizeof(cadd);
	int t;
		t = listen(serversocket2, 5);
		if (t == -1) {
			printf("����ʧ��");
			closesocket(serversocket2);
			WSACleanup();
		}
	while (1) {
		//�ȴ��ͻ������� ����
		clientsocket2[i2] = accept(serversocket2, (sockaddr*)&cadd, &len);
		printf("ϵͳ��%d�˳��Ե�¼\n", i2 + 1);
//--------------------------��ȡ�û���������------------------------------
		getnameandpassword();
//------------------------���ļ�����˶Բ�����----------------------------
		if (check() == true) {
			printf("%dλ�û���¼�ɹ�\n", i2+1);
			send(clientsocket2[i2], "T", 10, NULL);
			i2++;
		}else{
			printf("���û���¼ʧ��");
			send(clientsocket2[i2], "F", 10, NULL);
			i2++;
		}
		client2 = { 0 };
		sta2 = { 0 };
	}
}
void serversocketmake2() {
	//-------------------------����Э��汾-----------------------------------
	WSAStartup(MAKEWORD(2, 2), &wsaData2);	if (LOBYTE(wsaData2.wVersion) != 2 || HIBYTE(wsaData2.wVersion) != 2) {
		printf("����Э��汾ʧ��");
	}
	//--------------------------����socket------------------------------------
	serversocket2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serversocket2) {
		printf("����socketʧ��");
		WSACleanup();
	}
	//---------------------��ʼ����������socket��ַ��--------------------------
	SOCKADDR_IN add = { 0 };
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add.sin_port = htons(12479);//80,23 ���Ѿ���ϵͳ�ں�ռ���ˣ�����
//---------------------------��socket���ַ------------------------------
	int r = bind(serversocket2, (sockaddr*)&add, sizeof add);
	if (r == -1) {
		printf("socket�󶨵�ַʧ��");
		closesocket(serversocket2);
		WSACleanup();
	}
}
int loginserver() { 
	serversocketmake2();
	clientrecv();
	return 0;
}

#pragma once
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
typedef struct{
	char name[20];
	char passward[20];
	int times;//��¼����
}people3;
#pragma comment(lib,"ws2_32.lib")
//-------------------------------------------------------------------------
int i3= 0;//���ڼ�¼�û�����
WSADATA wsaData3;
SOCKET clientsocket3[200], serversocket3;
//-------------------------------ȫ�ֱ���----------------------------------
void broadcasting(int gt) {//gt����ڼ���socket
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
		//---------------------------------����126�����ݺ�С��126�����ݷ���
		if (moumou.times < 126) {
			mes[++total] = char(moumou.times % 126);
			mes[++total] = char(moumou.times % 126);
		}
		else {
			mes[++total] = char(moumou.times % 126);
			mes[++total] = char(moumou.times / 126);
		}
		mes[++total] = (char)127;//�������
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
			printf("����ʧ��");
			closesocket(serversocket3);
			WSACleanup();
		}
		//�ȴ��ͻ������� ����
		clientsocket3[i3] = accept(serversocket3, (sockaddr*)&cadd, &len);
		printf("���а�ϵͳ��%d�˲�ѯ\n", i3 + 1);
		broadcasting(i3);
		//һ�����û�����ʹ���һ���߳���֮����
		i3++;
	}
}
void serversocketmake3() {
	//-------------------------����Э��汾-----------------------------------
	WSAStartup(MAKEWORD(2, 2), &wsaData3);	if (LOBYTE(wsaData3.wVersion) != 2 || HIBYTE(wsaData3.wVersion) != 2) {
		printf("����Э��汾ʧ��");
	}
	//--------------------------����socket------------------------------------
	serversocket3 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serversocket3) {
		printf("����socketʧ��");
		WSACleanup();
	}
	//---------------------��ʼ����������socket��ַ��--------------------------
	SOCKADDR_IN add = { 0 };
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add.sin_port = htons(12315);//80,23 ���Ѿ���ϵͳ�ں�ռ���ˣ�����
//---------------------------��socket���ַ------------------------------
	int r = bind(serversocket3, (sockaddr*)&add, sizeof add);
	if (r == -1) {
		printf("socket�󶨵�ַʧ��");
		closesocket(serversocket3);
		WSACleanup();
	}
}
int ranklistserver() {
	serversocketmake3();
	clientrecv3();
	return 0;
}


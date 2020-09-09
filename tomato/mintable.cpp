// mintable.cpp: 实现文件
//

#include "pch.h"
#include "tomato.h"
#include "mintable.h"
#include "afxdialogex.h"
#include"chatroom.h"
#include"ranklist.h"
#include"todolist.h"
#include "music.h"

char msc[7][100] = { "bgm1", "bgm2", "bgm3", "bgm4", "bgm5", "bgm6", "bgm7" };
// mintable 对话框

IMPLEMENT_DYNAMIC(mintable, CDialogEx)

mintable::mintable(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_mintable, pParent)
{

}

mintable::~mintable()
{
}

void mintable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(mintable, CDialogEx)
	ON_BN_CLICKED(IDOK, &mintable::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &mintable::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &mintable::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &mintable::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &mintable::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &mintable::OnBnClickedButton5)
	ON_BN_DOUBLECLICKED(IDC_BUTTON5, &mintable::OnBnDoubleclickedButton5)
END_MESSAGE_MAP()


// mintable 消息处理程序
	SOCKET clientsocket1;

void mintable::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
}


void mintable::OnBnClickedButton1()//学习
{
	FILE *fp = fopen("name.txt", "r+");
	char name[20], c;
	int i = 0;
	c = getc(fp);
	while (c != EOF) {
		name[i] = c;
		i++;
		c = getc(fp);
	}
	name[i] = '\0';
	fclose(fp);
	//创建socket
	clientsocket1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN add = { 0 };
	SOCKADDR_IN cadd = { 0 };
	//初始化服务器地址族
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add.sin_port = htons(11111);//80,23 号已经被系统内核占用了
	//绑定socket和地址
	bind(clientsocket1, (sockaddr*)&cadd, sizeof cadd);
	int r = connect(clientsocket1, (sockaddr*)&add, sizeof add);
	if (r == -1) {
		MessageBox(L"连接失败,请联系管理员", L"", MB_OK);
	}
	else {
		send(clientsocket1, name,strlen(name), NULL);
		ShellExecute(this->GetSafeHwnd(), NULL, L"final_screen.exe", NULL, NULL, SW_SHOWNORMAL);
	}
}


void mintable::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	delete this;
	CDialogEx::PostNcDestroy();
}


void mintable::OnBnClickedButton2()//聊天室
{
	chatroom *p = new chatroom;
	p->Create(IDD_chatroom, this);
	p->ShowWindow(SW_SHOW);
	ShowWindow(HIDE_WINDOW);
	// TODO: 在此添加控件通知处理程序代码
}


void mintable::OnBnClickedButton3()//排行榜
{
	ranklist *p = new ranklist;
	p->Create(IDD_ranklist, this);
	p->ShowWindow(SW_SHOW);
	ShowWindow(HIDE_WINDOW);
	// TODO: 在此添加控件通知处理程序代码
}


void mintable::OnBnClickedButton4()//任务清单
{
	todolist *p = new todolist;
	p->Create(IDD_todolist, this);
	p->ShowWindow(SW_SHOW);
	ShowWindow(HIDE_WINDOW);
	// TODO: 在此添加控件通知处理程序代码
}




void mintable::OnBnClickedButton5()
{
	ShellExecute(this->GetSafeHwnd(), NULL, L"music.exe", NULL, NULL, SW_SHOWNORMAL);

	// TODO: 在此添加控件通知处理程序代码
	/*music* p = new music;
	p->Create(IDD_music, this);
	p->ShowWindow(SW_SHOW);
	ShowWindow(HIDE_WINDOW);
	//mciSendString(L"open bgm1.mp3 alias bgm", NULL, 0, NULL);
	//mciSendString(L"play bgm repeat", NULL, 0, NULL);*/
}


void mintable::OnBnDoubleclickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

}

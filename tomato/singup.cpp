// singup.cpp: 实现文件
//

#include "pch.h"
#include "tomato.h"
#include "singup.h"
#include "afxdialogex.h"
#include"tomatoDlg.h"


// singup 对话框

IMPLEMENT_DYNAMIC(singup, CDialog)

singup::singup(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_singup, pParent)
{

}

singup::~singup()
{
}

void singup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(singup, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &singup::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &singup::OnBnClickedButton2)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT1, &singup::OnEnChangeEdit1)
END_MESSAGE_MAP()


// singup 消息处理程序


void singup::OnBnClickedButton1()
{	
	typedef struct u {
		char name[20];
		char passward[20];
	}people;
	SOCKET clientsocket;
	//创建socket
	clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN add = { 0 };
	SOCKADDR_IN cadd = { 0 };
	//初始化服务器地址族
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add.sin_port = htons(12356);//80,23 号已经被系统内核占用了
	//绑定socket和地址
	bind(clientsocket, (sockaddr*)&cadd, sizeof cadd);
	int r = connect(clientsocket, (sockaddr*)&add, sizeof add);
	if (r == -1) {
		MessageBox(L"连接失败,请联系管理员",L"",MB_OK);
	}
	else {
		TCHAR namew[40], passwardwf[40], passwardws[40];
		GetDlgItemText(IDC_EDIT1, namew, 40); //获取
		GetDlgItemText(IDC_EDIT2, passwardwf, 40); //获取
		GetDlgItemText(IDC_EDIT3, passwardws, 40); //获取
		if (StrCmpW(passwardwf, passwardws)!=0) {
			MessageBox(L"前后密码不一致，请修改",L" ",MB_OK);
		}
		else {
			char name[40] = { 0 }, passward[40] = { 0 };
			INT namelen = lstrlenW(namew);
			INT passwardlen = lstrlenW(passwardwf);
			namelen = WideCharToMultiByte(CP_OEMCP, 0, namew, -1, NULL, 0, NULL, NULL);
			passwardlen = WideCharToMultiByte(CP_OEMCP, 0, passwardwf, -1, NULL, 0, NULL, NULL);
			WideCharToMultiByte(CP_OEMCP, 0, namew, -1, name, namelen, NULL, NULL);
			WideCharToMultiByte(CP_OEMCP, 0, passwardwf, -1, passward, passwardlen, NULL, NULL);
			char mes[100];
			memset(mes, 0, 100);
			char c = (char)127;
			char fen[1] = { c };
			strncat_s(mes, name, 20);
			strncat_s(mes, fen, 1);
			strncat_s(mes, passward, 20);
			send(clientsocket, mes, 1051, NULL);
			MessageBox(L"注册成功", L"", MB_OK);
			CtomatoDlg *p = new CtomatoDlg;
			p->Create(IDD_TOMATO_DIALOG, this);
			p->ShowWindow(SW_SHOW);
			ShowWindow(HIDE_WINDOW);
		}
		}
	}


void singup::OnBnClickedButton2()
{
	CtomatoDlg *p = new CtomatoDlg;
	p->Create(IDD_TOMATO_DIALOG, this);
	p->ShowWindow(SW_SHOW);
	ShowWindow(HIDE_WINDOW);
	// TODO: 在此添加控件通知处理程序代码
}


void singup::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	delete this;
	CDialog::PostNcDestroy();
}


void singup::OnDestroy()
{
	MessageBox(NULL, NULL, MB_OK);
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


void singup::OnClose()
{
	CtomatoDlg* p = new CtomatoDlg;
	p->Create(IDD_TOMATO_DIALOG, this);
	p->ShowWindow(SW_SHOW);
	ShowWindow(HIDE_WINDOW);
	CDialog::OnClose();
}


void singup::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

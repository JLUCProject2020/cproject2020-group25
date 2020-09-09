// login.cpp: 实现文件
//

#include "pch.h"
#include "tomato.h"
#include "login.h"
#include "afxdialogex.h"
#include "mintable.h"
#include "tomatoDlg.h"


// login 对话框

IMPLEMENT_DYNAMIC(login, CDialog)

login::login(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_login, pParent)
{

}

login::~login()
{
}

void login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(login, CDialog)
	ON_EN_CHANGE(IDC_EDIT2, &login::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON3, &login::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT1, &login::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &login::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &login::OnBnClickedButton2)
END_MESSAGE_MAP()


// login 消息处理程序

void login::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void login::OnBnClickedButton3()
{
	TCHAR namew[20] = { 0 }, passwardw[20] = { 0 };
	GetDlgItemText(IDC_EDIT1,namew, 20); //获取
	GetDlgItemText(IDC_EDIT2,passwardw, 20); //获取
	//把宽字符转化为a字符-----------------------------------------------------------
	char name[40] = { 0 }, passward[40] = { 0 };
	INT namelen = lstrlenW(namew);
	INT passwardlen = lstrlenW(passwardw);
	namelen = WideCharToMultiByte(CP_OEMCP, 0, namew, -1, NULL, 0, NULL, NULL);
	passwardlen = WideCharToMultiByte(CP_OEMCP, 0, passwardw, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_OEMCP, 0, namew, -1, name, namelen, NULL, NULL);
	WideCharToMultiByte(CP_OEMCP, 0, passwardw, -1, passward, passwardlen, NULL, NULL);
	//--------------------------------------------------------------------
	SOCKET clientsocket;
	clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN add = { 0 };
	SOCKADDR_IN cadd = { 0 };
	//------------------------------------------------初始化服务器地址族
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add.sin_port = htons(12479);//80,23 号已经被系统内核占用了
	//绑定socket和地址
	bind(clientsocket, (sockaddr*)&cadd, sizeof cadd);
	int r = connect(clientsocket, (sockaddr*)&add, sizeof add);
	//组合名字和密码
	char fengge[1] = { 0 }, mes[100] = { 0 };
	fengge[0] = (char)127;
	strncat_s(mes, name, 20);
	strncat_s(mes, fengge, 1);
	strncat_s(mes, passward, 20);
	send(clientsocket, mes, 100, NULL);
	//把message传递出去
	char u[10] = { 0 };
	recv(clientsocket, u, 10, NULL);
	if (u[0] == 'T') {
		MessageBox(L"登录成功", NULL, MB_OK); 
		FILE *fp=fopen("flag.txt","w+");
		fwrite("1", 1, 1, fp);
		fclose(fp);
		CtomatoDlg *p = new CtomatoDlg;
		fp = fopen("name.txt", "w+");
		fwrite(name,strlen(name),1, fp);
		fclose(fp);
		p->Create(IDD_TOMATO_DIALOG, this);
		p->ShowWindow(SW_SHOW);
		ShowWindow(HIDE_WINDOW);
	
	}
	if (u[0] == 'F')MessageBox(L"登录失败，请检查账号和密码", NULL, MB_OK);
	//反馈登录成功或失败*/
	
	// TODO: 在此添加控件通知处理程序代码
}


void login::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void login::OnBnClickedButton1()
{
		CtomatoDlg *p = new CtomatoDlg;
		p->Create(IDD_TOMATO_DIALOG, this);
		p->ShowWindow(SW_SHOW);
		ShowWindow(HIDE_WINDOW);
		OnClose();
		// TODO: 在此添加控件通知处理程序代码
	
}


void login::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

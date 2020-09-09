// chatroom.cpp: 实现文件
//

#include "pch.h"
#include "tomato.h"
#include "chatroom.h"
#include "afxdialogex.h"
#include"mintable.h"

SOCKET clientsocket;
// chatroom 对话框
UINT CHATA(LPVOID pParam) {
	int len = 0, r = 1, t = 0;
	char mes[1024] = { 0 };
	TCHAR mest[1024], all[20000], fen[20] = { L'\n' };
	HWND hwnd= GetForegroundWindow();
	while (1) {
		memset(mes, 0, sizeof(char) * 1024);
		r = recv(clientsocket, mes, 1023, NULL);
		//转换为宽字符---------------------------------
		len = MultiByteToWideChar(
			CP_ACP,//表示转换后的字符串的类型
			0,//空字表字，一般设为0
			mes,//欲转换的字符集的指针
			-1,//表示转换多少个字符,-1表示全转
			NULL,
			0);
		MultiByteToWideChar(CP_ACP, 0, mes, -1, mest, len);
		//-------------------------改变文本框内容-------
		GetDlgItemText(hwnd, IDC_EDIT1, all, 20000);
		StrCatW(all, fen);
		StrCatW(all, mest);
		StrCatW(all, fen);
		SetDlgItemText(hwnd, IDC_EDIT1,all);
	}
	return 0;
}

IMPLEMENT_DYNAMIC(chatroom, CDialog)

chatroom::chatroom(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_chatroom, pParent)
{

}

chatroom::~chatroom()
{
}

void chatroom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(chatroom, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &chatroom::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &chatroom::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &chatroom::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// chatroom 消息处理程序


void chatroom::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
void chatroom::OnBnClickedButton2()
{
	TCHAR mes[100] = { 0 }, semes[200] = { 0 };
		GetDlgItemText(IDC_EDIT2,mes, 100); //获取
		TCHAR name[20] = { L"我:"};
		StrCatW(semes, name);
		StrCatW(semes,mes);
		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
		pEdit->SetSel(-1);
		pEdit->ReplaceSel(_T("\r\n"));
		pEdit->ReplaceSel(semes);
		pEdit->ReplaceSel(_T("\r\n"));
		char mess[1024] = { 0 };
		int len=WideCharToMultiByte(CP_OEMCP, 0, mes, -1, NULL, 0, NULL, NULL);//比前面多了两个不需要的参数null就可
		WideCharToMultiByte(CP_OEMCP, 0,mes, -1, mess, len, NULL, NULL);
		FILE *fp = fopen("name.txt", "r+");
		char name2[20] = { 0 }, dou[3] = { ':' }, semt[1024] = {0};
		int i = 0;
		while(fgetc(fp) != EOF) {
			fseek(fp, i * 1, SEEK_SET);
			name2[i] = fgetc(fp);
			i++;
		}
		name[i] = '\0';
		fclose(fp);
		strcat(semt, name2);
		strcat(semt, dou);
		strcat(semt, mess);
		send(clientsocket,semt,strlen(semt),NULL);
	// TODO: 在此添加控件通知处理程序代码
}

void chatroom::OnBnClickedButton1()
{

	}


void chatroom::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	mintable *p = new mintable;
	p->Create(IDD_mintable, this);
	p->ShowWindow(SW_SHOW);
	ShowWindow(HIDE_WINDOW);
	CDialog::OnClose();
}


BOOL chatroom::OnInitDialog()
{
	CDialog::OnInitDialog();
		clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN add = { 0 };
	SOCKADDR_IN cadd = { 0 };
	CString w;
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add.sin_port = htons(12301);//80,23 号已经被系统内核占用了
	bind(clientsocket,(sockaddr*)&cadd, sizeof cadd);
	int r = 1;
	r= connect(clientsocket, (sockaddr*)&add, sizeof add);
	if (r == -1) {
		MessageBox(L"与服务端连接失败", L"", MB_OK);
	}
	else {
		MessageBox(L"与服务端连接成功", L"", MB_OK);
		AfxBeginThread(CHATA, NULL);
		}
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

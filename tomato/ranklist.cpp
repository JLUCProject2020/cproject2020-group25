// ranklist.cpp: 实现文件
//

#include "pch.h"
#include "tomato.h"
#include "ranklist.h"
#include "afxdialogex.h"
#include"mintable.h"


// ranklist 对话框

IMPLEMENT_DYNAMIC(ranklist, CDialog)

ranklist::ranklist(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ranklist, pParent)
{

}

ranklist::~ranklist()
{
}

void ranklist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, rank);
}


BEGIN_MESSAGE_MAP(ranklist, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &ranklist::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ranklist::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_LBN_SELCHANGE(IDC_LIST1, &ranklist::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// ranklist 消息处理程序


void ranklist::OnBnClickedButton1()
{

}


void ranklist::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void ranklist::OnClose()
{
	mintable *p = new mintable;
	p->Create(IDD_mintable, this);
	p->ShowWindow(SW_SHOW);
	ShowWindow(HIDE_WINDOW);
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}


void ranklist::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL ranklist::OnInitDialog()
{
	CDialog::OnInitDialog();
	rank.ResetContent();
	char mes[1024] = { 0 };
	int i = 0;
	//--------------------------------------------------------------------
	SOCKET clientsocket;
	clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN add = { 0 };
	SOCKADDR_IN cadd = { 0 };
	//------------------------------------------------初始化服务器地址族
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("192.168.192.214");
	add.sin_port = htons(12315);//80,23 号已经被系统内核占用了
	//绑定socket和地址
	bind(clientsocket, (sockaddr*)&cadd, sizeof cadd);
	int r = connect(clientsocket, (sockaddr*)&add, sizeof add);
	if (r == -1) MessageBox(L"服务器没有启动，请联系管理员", L" ", MB_OK);
	else {
		int times = 0, count = 0, j = 0, i = 0, len = 0;
		char mes[1051], name[20] = { 0 };
		memset(mes, 0, sizeof(mes));
		recv(clientsocket, mes, sizeof(char) * 1051, NULL);
		//--------------------------------拆分数据------------------------------------------
		while (mes[count] != '\0') {
			j = 0;
			memset(name, 0, sizeof(name));
			while (mes[count] != (char)127) {
				name[j] = mes[count];
				count++;
				j++;
			}
			name[j + 1] = '\0';
			count++;
			if (mes[count] == mes[count + 1])times = (int)mes[count];
			else {
				times = (int)mes[count] + (int)mes[count + 1] * 126;
			}
			i++;
			//将字符转化为宽字符-------------------------------------------------------------------
			char out[200] = { 0 };
			out[0] = (char)i + 48;
			out[1] = ':';
			out[2] = '\0';
			strcat(out, name);
			char* p1 = "完成了";
			strcat(out, p1);
			char ci[10] = { (char)times + 48 };
			strcat(out, ci);
			char* p2 = "个番茄钟\0";
			strcat(out, p2);
			len = MultiByteToWideChar(
				CP_ACP,//表示转换后的字符串的类型
				0,//空字表字，一般设为0
				out,//欲转换的字符集的指针
				-1,//表示转换多少个字符,-1表示全转
				NULL,
				0);
			WCHAR outw[200] = { 0 };
			MultiByteToWideChar(CP_ACP, 0, out, -1, outw, len);
			rank.AddString(outw);
			count = count + 3;
		}
	}
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

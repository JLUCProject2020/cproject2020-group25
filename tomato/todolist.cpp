// todolist.cpp: 实现文件
//

#include "pch.h"
#include "tomato.h"
#include "todolist.h"
#include "afxdialogex.h"
#include<atlconv.h>
#include"mintable.h"

// todolist 对话框

IMPLEMENT_DYNAMIC(todolist, CDialog)

todolist::todolist(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_todolist, pParent)
{
	
}

todolist::~todolist()
{
}

void todolist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox_Content);
}


BEGIN_MESSAGE_MAP(todolist, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &todolist::OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_EDIT1, &todolist::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &todolist::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// todolist 消息处理程序


void todolist::OnLbnSelchangeList1()
{	
	int t =m_ListBox_Content.GetCurSel();
	CString s;
	char mes[200];
	m_ListBox_Content.GetText(t, s);
	s.ReleaseBuffer();
	int len = WideCharToMultiByte(CP_OEMCP, 0, s, -1, NULL, 0, NULL, NULL);//比前面多了两个不需要的参数null就可
	WideCharToMultiByte(CP_OEMCP, 0, s, -1,mes, len, NULL, NULL);
	FILE *fp = fopen("todolist.txt", "r+");
	t = -1;
	char  tw[200] = { 0 }, sta[200] = { 0 };
	while (strcmp(tw,mes)!=0) {
		fread(tw, 100, 1, fp) != 0;
		t++;
	}
	fseek(fp, (t + 1) * 100, SEEK_SET);
	while (fread(tw, 100, 1, fp) != 0) {	
		fseek(fp, t  * 100, SEEK_SET);
		fwrite(tw, 100, 1, fp);
		t++;
		fseek(fp, (t+1) * 100, SEEK_SET);
	}
	fseek(fp, t * 100, SEEK_SET);
	fwrite(sta, 100, 1, fp);
	fclose(fp);
m_ListBox_Content.DeleteString(m_ListBox_Content.GetCurSel());
}


void todolist::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	
	
}


BOOL todolist::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  在此添加额外的初始化
	SetDlgItemText(IDC_EDIT1, L"例如:1--2020.9.6--C语言期末答辩");
	TCHAR todow[100] = { 0 };
	char todo[100] = { 0 }, sta[100] = {0};
	int i = 0, total = 0,len=0;
	FILE *fp;
	fp = fopen("todolist.txt", "r+");
	while (fread(todo, 100, 1, fp) != 0)
	{
		//转换为宽字符---------------------------------
		len = MultiByteToWideChar(
			CP_ACP,//表示转换后的字符串的类型
			0,//空字表字，一般设为0
			todo,//欲转换的字符集的指针
			-1,//表示转换多少个字符,-1表示全转
			NULL,
			0);
		MultiByteToWideChar(CP_ACP, 0, todo, -1, todow, len);
		if(strcmp(todo, sta) != 0)m_ListBox_Content.AddString(todow);
		i = 0;
		total++;
	}
	fclose(fp);
	// TODO: 在此添加控件通知处理程序代码



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void todolist::OnBnClickedButton1()//
{
	int i = 0,total=0;
	TCHAR todow[100] = { 0 };
	char todo[100] = { 0 }, sta[200] = {0};
	GetDlgItemText(IDC_EDIT1, todow, 100);
	FILE* fp;
	int len = WideCharToMultiByte(CP_OEMCP, 0, todow, -1, NULL, 0, NULL, NULL);//比前面多了两个不需要的参数null就可
	WideCharToMultiByte(CP_OEMCP, 0,todow, -1, todo, len, NULL, NULL);
	fp = fopen("todolist.txt", "a+");
	fwrite(todo,100, 1, fp);
	fclose(fp);
	m_ListBox_Content.ResetContent();
	fp = fopen("todolist.txt", "r+");
	while (fread(todo, 100, 1, fp) != 0 )
	{
		//转换为宽字符---------------------------------
		len = MultiByteToWideChar(
			CP_ACP,//表示转换后的字符串的类型
			0,//空字表字，一般设为0
			todo,//欲转换的字符集的指针
			-1,//表示转换多少个字符,-1表示全转
			NULL,
			0);
		MultiByteToWideChar(CP_ACP, 0, todo, -1, todow, len);
		if (strcmp(todo, sta) != 0)m_ListBox_Content.AddString(todow);
		i = 0;
		total++;
	}
	fclose(fp);
	MessageBox(L"任务导入成功");
	// TODO: 在此添加控件通知处理程序代码
}


void todolist::OnClose()
{

	mintable *p = new mintable;
	p->Create(IDD_mintable, this);
	p->ShowWindow(SW_SHOW);
	ShowWindow(HIDE_WINDOW);
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnClose();
}

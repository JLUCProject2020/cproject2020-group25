
// tomatoDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "tomato.h"
#include "tomatoDlg.h"
#include "afxdialogex.h"
#include "login.h"
#include"singup.h"
#include"mintable.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CtomatoDlg 对话框



CtomatoDlg::CtomatoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOMATO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
}

void CtomatoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtomatoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtomatoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CtomatoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CtomatoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CtomatoDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CtomatoDlg 消息处理程序

BOOL CtomatoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtomatoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtomatoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtomatoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtomatoDlg::OnBnClickedButton1()
{	
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_SHOW);
	login *p = new login;
	p->Create(IDD_login, this);
	p->ShowWindow(SW_SHOW);
	ShowWindow(HIDE_WINDOW);
	// TODO: 在此添加控件通知处理程序代码
}


void CtomatoDlg::OnBnClickedButton3()
{
	mintable *p = new mintable;
	p->Create(IDD_mintable, this);
	p->ShowWindow(SW_SHOW);
	ShowWindow(HIDE_WINDOW);
}


void CtomatoDlg::OnBnClickedButton2()
{
	
	singup *p = new singup;
	p->Create(IDD_singup, this);
	p->ShowWindow(SW_SHOW);
	ShowWindow(HIDE_WINDOW);
	// TODO: 在此添加控件通知处理程序代码
}


void CtomatoDlg::OnBnClickedButton4()
{
	/*FILE *fp = fopen("flag.txt", "rb+");
	char c=fgetc(fp);
	if (c == '1') {
		fseek(fp, 0, SEEK_SET);
		c = 0;
		fwrite(&c, 1, 1, fp);*/
		mintable *p = new mintable;
		p->Create(IDD_mintable, this);
		p->ShowWindow(SW_SHOW);
		ShowWindow(HIDE_WINDOW);
	/*}
	else {
		MessageBox(L"您还未登录，请登录重试", L"系统提示",MB_OK);
	}
		fclose(fp);*/
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CtomatoDlg::OnQueryEndSession()
{
	MessageBox(NULL, NULL, MB_OK);
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	FILE *fp = fopen("flag.txt", "w+");
	fwrite("0", 1, 1, fp);
	fclose(fp);
	if (!CDialogEx::OnQueryEndSession())
		return FALSE;

	// TODO:  在此添加专用的查询结束会话代码

	return TRUE;
}

void CtomatoDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
}

void CtomatoDlg::OnClose()
{
}




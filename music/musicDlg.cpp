
// musicDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "music.h"
#include "musicDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>
#include <Digitalv.h>
#pragma comment(lib, "winmm.lib")

//全局变量
HWND m_hwnd;
DWORD DeviceId;
tagMCI_OPEN_PARMSA mciopenparms;

//全局函数
void load(HWND hwnd, CString strFilepath)
{
	m_hwnd = hwnd;
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0);
	CStringA strA(strFilepath);
	//LPCSTR ptr = strA;
	//mciopenparms.lpstrElementName = ptr;
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)(&mciopenparms)))
	{
		char buffer[256];
		mciGetErrorString(dwReturn, buffer, 256);
		MessageBox(hwnd, buffer, "警告", MB_ICONHAND | MB_ICONERROR | MB_ICONSTOP);
	}
	DeviceId = mciopenparms.wDeviceID;
}



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


// CmusicDlg 对话框



CmusicDlg::CmusicDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MUSIC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmusicDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CmusicDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CmusicDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CmusicDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT1, &CmusicDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON4, &CmusicDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CmusicDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CmusicDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CmusicDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CmusicDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CmusicDlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CmusicDlg 消息处理程序

BOOL CmusicDlg::OnInitDialog()
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

void CmusicDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmusicDlg::OnPaint()
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
HCURSOR CmusicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmusicDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	char szFileFilter[1000] = "mp3文件(*.mp3)|*.mp3|"
		"所有文件(*.*)|*.*|";
	//int len = WideCharToMultiByte(CP_OEMCP, 0, mes, -1, NULL, 0, NULL, NULL);//比前面多了两个不需要的参数null就可
	//WideCharToMultiByte(CP_OEMCP, 0, mes, -1, mess, len, NULL, NULL);
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY, szFileFilter);
	if (dlg.DoModal() == IDOK)
	{
		CString strFilepath = dlg.GetPathName();
		CString strFilename = dlg.GetFileName();
		SetDlgItemText(IDC_EDIT1, strFilename);
		//load(this->m_hWnd, strFilepath);
	}
}


void CmusicDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	/*MCI_PLAY_PARMS mciplayparms;
	mciplayparms.dwCallback = (DWORD)m_hwnd;
	mciplayparms.dwFrom = 0;
	//mciSendCommand(DeviceId, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciplayparms);
	mciSendCommand(DeviceId, MCI_PLAY, 0, 0);
	//mciSendCommand(NULL, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciplayparms);*/
	mciSendString("close bgm", NULL, 0, NULL);
	mciSendString("open bgm4.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);

	
}


void CmusicDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	mciSendCommand(DeviceId, MCI_STOP, 0, 0);
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0);
}


void CmusicDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmusicDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	mciSendString("close bgm", NULL, 0, NULL);
	mciSendString("open bgm1.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
}


void CmusicDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	mciSendString("close bgm", NULL, 0, NULL);
	mciSendString("open bgm2.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
}


void CmusicDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	mciSendString("close bgm", NULL, 0, NULL);
	mciSendString("open bgm3.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
}


void CmusicDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	mciSendString("close bgm", NULL, 0, NULL);
	mciSendString("open bgm4.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
}


void CmusicDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	mciSendString("close bgm", NULL, 0, NULL);
	mciSendString("open bgm5.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
}


void CmusicDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	mciSendString("close bgm", NULL, 0, NULL);
	mciSendString("open bgm6.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
}

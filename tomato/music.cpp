// music.cpp: 实现文件
//

#include "pch.h"
#include "tomato.h"
#include "music.h"
#include "afxdialogex.h"
#include <mmsystem.h>
#include <Digitalv.h>
#pragma comment(lib, "winmm.lib")

//全局变量
HWND m_hwnd;
DWORD DeviceId;
tagMCI_OPEN_PARMSA mciopenparms;

//全局函数
/*void load(HWND hwnd, CString strFilepath)
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
}*/


// music 对话框

IMPLEMENT_DYNAMIC(music, CDialog)

music::music(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_music, pParent)
{

}

music::~music()
{
}

void music::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(music, CDialog)

	ON_EN_CHANGE(IDC_EDIT1, &music::OnEnChangeEdit1)

	
	ON_BN_CLICKED(IDC_BUTTONfile, &music::OnBnClickedButtonfile)
	ON_BN_CLICKED(IDC_BUTTONplay, &music::OnBnClickedButtonplay)
	ON_BN_CLICKED(IDC_BUTTONclose, &music::OnBnClickedButtonclose)
	ON_BN_CLICKED(IDC_BUTTON1, &music::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &music::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &music::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &music::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &music::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &music::OnBnClickedButton6)
END_MESSAGE_MAP()


// music 消息处理程序





void music::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}







	void music::OnBnClickedButtonfile()
	{
		// TODO: 在此添加控件通知处理程序代码
		/*char szFileFilter[] = L"mp3文件(*.mp3)|*.mp3|"
			L"所有文件(*.*)|*.*|";
		//int len = WideCharToMultiByte(CP_OEMCP, 0, mes, -1, NULL, 0, NULL, NULL);//比前面多了两个不需要的参数null就可
		//WideCharToMultiByte(CP_OEMCP, 0, mes, -1, mess, len, NULL, NULL);
		BOOL bo = 1;
		CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY, szFileFilter );
		if (dlg.DoModal() == IDOK)
		{
			CString strFilepath = dlg.GetPathName();
			CString strFilename = dlg.GetFileName();
			SetDlgItemText(IDC_EDIT1, strFilename);
			load(this->m_hWnd, strFilepath);
		}*/
	}


	void music::OnBnClickedButtonplay()
	{
		// TODO: 在此添加控件通知处理程序代码

	}


	void music::OnBnClickedButtonclose()
	{
		// TODO: 在此添加控件通知处理程序代码
	}


	void music::OnBnClickedButton1()
	{
		// TODO: 在此添加控件通知处理程序代码
	mciSendString(L"close bgm", NULL, 0, NULL);
	mciSendString(L"open bgm1.mp3 alias bgm", NULL, 0, NULL);
	mciSendString(L"play bgm repeat", NULL, 0, NULL);

	}


	void music::OnBnClickedButton2()
	{
		// TODO: 在此添加控件通知处理程序代码
		mciSendString(L"close bgm", NULL, 0, NULL);
		mciSendString(L"open bgm2.mp3 alias bgm", NULL, 0, NULL);
		mciSendString(L"play bgm repeat", NULL, 0, NULL);
	}


	void music::OnBnClickedButton3()
	{
		// TODO: 在此添加控件通知处理程序代码
		mciSendString(L"close bgm", NULL, 0, NULL);
		mciSendString(L"open bgm3.mp3 alias bgm", NULL, 0, NULL);
		mciSendString(L"play bgm repeat", NULL, 0, NULL);
	}


	void music::OnBnClickedButton4()
	{
		// TODO: 在此添加控件通知处理程序代码
		mciSendString(L"close bgm", NULL, 0, NULL);
		mciSendString(L"open bgm4.mp3 alias bgm", NULL, 0, NULL);
		mciSendString(L"play bgm repeat", NULL, 0, NULL);
	}


	void music::OnBnClickedButton5()
	{
		// TODO: 在此添加控件通知处理程序代码
		mciSendString(L"close bgm", NULL, 0, NULL);
		mciSendString(L"open bgm5.mp3 alias bgm", NULL, 0, NULL);
		mciSendString(L"play bgm repeat", NULL, 0, NULL);
	}


	void music::OnBnClickedButton6()
	{
		// TODO: 在此添加控件通知处理程序代码
		mciSendString(L"close bgm", NULL, 0, NULL);
		mciSendString(L"open bgm6.mp3 alias bgm", NULL, 0, NULL);
		mciSendString(L"play bgm repeat", NULL, 0, NULL);
	}

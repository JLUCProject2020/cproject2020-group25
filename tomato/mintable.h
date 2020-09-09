#pragma once
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// mintable 对话框


class mintable : public CDialogEx
{
	DECLARE_DYNAMIC(mintable)

public:
	mintable(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~mintable();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_mintable };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnDoubleclickedButton5();
};

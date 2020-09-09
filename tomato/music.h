#pragma once


// music 对话框

class music : public CDialog
{
	DECLARE_DYNAMIC(music)

public:
	music(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~music();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_music };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	

	afx_msg void OnBnClickedButtonfile();
	afx_msg void OnBnClickedButtonplay();
	afx_msg void OnBnClickedButtonclose();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};

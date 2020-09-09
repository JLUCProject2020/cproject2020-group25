#pragma once


// singup 对话框

class singup : public CDialog
{
	DECLARE_DYNAMIC(singup)

public:
	singup(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~singup();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_singup };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual void PostNcDestroy();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnEnChangeEdit1();
};

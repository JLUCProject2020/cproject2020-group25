#pragma once


// ranklist 对话框

class ranklist : public CDialog
{
	DECLARE_DYNAMIC(ranklist)

public:
	ranklist(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ranklist();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ranklist };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CListBox rank;
	afx_msg void OnClose();
	afx_msg void OnLbnSelchangeList1();
	virtual BOOL OnInitDialog();
};

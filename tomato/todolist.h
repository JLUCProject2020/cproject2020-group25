#pragma once


// todolist 对话框

class todolist : public CDialog
{
	DECLARE_DYNAMIC(todolist)

public:
	todolist(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~todolist();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_todolist };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnEnChangeEdit1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	CListBox m_ListBox_Content;
	afx_msg void OnClose();
};

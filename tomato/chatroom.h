#pragma once
UINT CHATA(LPVOID pParam);

// chatroom 对话框

class chatroom : public CDialog
{
	DECLARE_DYNAMIC(chatroom)

public:
	chatroom(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~chatroom();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_chatroom };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
};

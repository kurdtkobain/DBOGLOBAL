#pragma once


// CNotifyDlg 대화 상자입니다.

class CNotifyDlg : public CDialog
{
	DECLARE_DYNAMIC(CNotifyDlg)

public:
	CNotifyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CNotifyDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_NOTIFY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};

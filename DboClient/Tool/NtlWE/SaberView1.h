#pragma once


// CSaberView1 대화 상자입니다.

class CSaberView1 : public CDialog
{
	DECLARE_DYNAMIC(CSaberView1)

public:
	CSaberView1(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSaberView1();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SABER_VIEW1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

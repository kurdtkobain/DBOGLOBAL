#pragma once


#include "Attr_Page.h"


// CAttr_EVT_ClickObject 대화 상자입니다.

class CAttr_EVT_ClickObject : public CAttr_Page
{
	DECLARE_SERIAL(CAttr_EVT_ClickObject)

public:
	CAttr_EVT_ClickObject(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAttr_EVT_ClickObject();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TS_EVT_CLICK_OBJECT_ATTR_DIAG };

	virtual CString	GetPageData( void );
	virtual void	UnPakingPageData( CString& strKey, CString& strValue );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	DWORD m_dwWorldIdx;
	CString m_strObjectIdx;
};

#pragma once


#include "Attr_Page.h"


// CAttr_ACT_TWaitTS 대화 상자입니다.

class CAttr_ACT_TWaitTS : public CAttr_Page
{
	DECLARE_SERIAL(CAttr_ACT_TWaitTS)

public:
	CAttr_ACT_TWaitTS();
	virtual ~CAttr_ACT_TWaitTS();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TS_ACT_TWAITTS_ATTR_DIAG };

	virtual CString	GetPageData( void );
	virtual void	UnPakingPageData( CString& strKey, CString& strValue );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	DWORD m_taID;
	DWORD m_dwWTime;
};

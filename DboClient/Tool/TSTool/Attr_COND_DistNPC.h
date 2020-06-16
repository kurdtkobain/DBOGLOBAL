#pragma once


#include "Attr_Page.h"
#include "afxwin.h"


// CAttr_COND_DistNPC 대화 상자입니다.

class CAttr_COND_DistNPC : public CAttr_Page
{
	DECLARE_SERIAL(CAttr_COND_DistNPC)

public:
	CAttr_COND_DistNPC();
	virtual ~CAttr_COND_DistNPC();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TS_COND_DIST_NPC_ATTR_DIAG };

	virtual CString	GetPageData( void );
	virtual void	UnPakingPageData( CString& strKey, CString& strValue );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	float m_fDistance;
	CString m_strNPCList;
};

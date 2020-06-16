// Attr_ACT_TelMinorMatch.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TSTool.h"
#include "Attr_ACT_TelMinorMatch.h"


// CAttr_ACT_TelMinorMatch 대화 상자입니다.

IMPLEMENT_SERIAL(CAttr_ACT_TelMinorMatch, CAttr_Page, 1)

CAttr_ACT_TelMinorMatch::CAttr_ACT_TelMinorMatch()
	: CAttr_Page(CAttr_ACT_TelMinorMatch::IDD)
	, m_taID(NTL_TS_TA_ID_INVALID)
{

}

CAttr_ACT_TelMinorMatch::~CAttr_ACT_TelMinorMatch()
{
}

CString CAttr_ACT_TelMinorMatch::GetPageData( void )
{
	UpdateData( true );

	CString strData;

	strData += PakingPageData( _T("taid"), m_taID );

	return strData;
}

void CAttr_ACT_TelMinorMatch::UnPakingPageData( CString& strKey, CString& strValue )
{
	if ( _T("taid") == strKey )
	{
		m_taID = atoi( strValue.GetBuffer() );
	}
}

void CAttr_ACT_TelMinorMatch::DoDataExchange(CDataExchange* pDX)
{
	CAttr_Page::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TS_ACT_ATTR_TELMINORMATCH_ID_EDITOR, m_taID);
	DDV_MinMaxUInt(pDX, m_taID, 0, NTL_TS_TA_ID_INVALID);
}

BOOL CAttr_ACT_TelMinorMatch::OnInitDialog()
{
	CAttr_Page::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	if ( m_strData.GetLength() > 0 ) SetPageData( m_strData );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BEGIN_MESSAGE_MAP(CAttr_ACT_TelMinorMatch, CAttr_Page)
END_MESSAGE_MAP()


// CAttr_ACT_TelMinorMatch 메시지 처리기입니다.

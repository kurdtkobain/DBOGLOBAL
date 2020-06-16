#ifndef _DBO_TSACTOUTMSG_H_
#define _DBO_TSACTOUTMSG_H_


#include "DboTSCoreDefine.h"


/**
	Out msg action
*/


class CDboTSActOutMsg : public CNtlTSAction
{
	NTL_TS_DECLARE_RTTI

// Member variables
protected:

	unsigned int						m_uiIdx;
	NTL_TS_TA_ID						m_TaIdx;

// Constructions
public:
	CDboTSActOutMsg( void );

// Methods
public:
	virtual unsigned int				GetEntityType( void ) const { return DBO_ACT_TYPE_ID_ACT_OUT_MSG; }


	unsigned int						GetIdx( void ) const;
	NTL_TS_TA_ID						GetTaIdx( void ) const;

// Implementations
protected:
	// 스크립트로 부터 컴포넌트 객체의 데이터를 로딩 및 입력 시키기 위한 함수
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );
};


inline unsigned int CDboTSActOutMsg::GetIdx( void ) const
{
	return m_uiIdx;
}

inline NTL_TS_TA_ID CDboTSActOutMsg::GetTaIdx( void ) const
{
	return m_TaIdx;
}


#endif
#ifndef _DBO_TSACTMININARRATION_H_
#define _DBO_TSACTMININARRATION_H_


#include "DboTSCoreDefine.h"


/**
	Mini narration
*/


class CDboTSActMiniNarration : public CNtlTSAction
{
	NTL_TS_DECLARE_RTTI

// Member variables
protected:
	unsigned int						m_uiNarrationTblIdx;

// Constructions
public:
	CDboTSActMiniNarration( void );

// Methods
public:
	virtual unsigned int				GetEntityType( void ) const { return DBO_ACT_TYPE_ID_ACT_MINI_NARRATION; }

	unsigned int						GetNarrationTableIndex( void ) const;

// Implementations
protected:
	// 스크립트로 부터 컴포넌트 객체의 데이터를 로딩 및 입력 시키기 위한 함수
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );
};


inline unsigned int CDboTSActMiniNarration::GetNarrationTableIndex( void ) const
{
	return m_uiNarrationTblIdx;
}


#endif
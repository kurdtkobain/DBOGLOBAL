#ifndef _DBO_TSSEARCHQUEST_H_
#define _DBO_TSSEARCHQUEST_H_


#include "DboTSCoreDefine.h"


/**
	Search quest event
*/


class CDboTSSearchQuest : public CNtlTSEvent
{
	NTL_TS_DECLARE_RTTI

// Constructions
public:
	CDboTSSearchQuest( void );

// Methods
public:
	virtual unsigned int				GetEntityType( void ) const { return DBO_EVENT_TYPE_ID_SEARCH_QUEST; }

// Implementations
protected:
	// 스크립트로 부터 컴포넌트 객체의 데이터를 로딩 및 입력 시키기 위한 함수
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );
};


#endif
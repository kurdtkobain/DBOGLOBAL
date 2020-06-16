#ifndef _DBO_TSACTTELMINORMATCH_H_
#define _DBO_TSACTTELMINORMATCH_H_


#include "DboTSCoreDefine.h"


/**
	Teleport Minor-match
*/


class CDboTSActTelMinorMatch : public CNtlTSAction
{
	NTL_TS_DECLARE_RTTI

// Member variables
protected:

// Constructions
public:
	CDboTSActTelMinorMatch( void );

// Methods
public:
	virtual unsigned int				GetEntityType( void ) const { return DBO_ACT_TYPE_ID_ACT_TELMINORMATCH; }


// Implementations
protected:
	// 스크립트로 부터 컴포넌트 객체의 데이터를 로딩 및 입력 시키기 위한 함수
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );
};


#endif
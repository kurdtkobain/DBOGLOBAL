#ifndef _DBO_TSCHECKOBJSTATE_H_
#define _DBO_TSCHECKOBJSTATE_H_


#include "DboTSCoreDefine.h"


/**
	Check object state
*/


class CDboTSCheckObjState : public CNtlTSCond
{
	NTL_TS_DECLARE_RTTI

// Declarations
public:
enum eMAIN_STATE
	{
		eMAIN_STATE_0					= 0,
		eMAIN_STATE_1					= 1,
		eMAIN_STATE_2					= 2,
		eMAIN_STATE_3					= 3,
		eMAIN_STATE_4					= 4,
		eMAIN_STATE_5					= 5,
		eMAIN_STATE_6					= 6,
		eMAIN_STATE_7					= 7,
		eMAIN_STATE_8					= 8,
		eMAIN_STATE_9					= 9,
		eMAIN_STATE_IGNORE				= 255
	};

	enum eSUB_STATE_OBJECT
	{
		SUB_STATE_OBJECT_HIDE			= 0,
		SUB_STATE_OBJECT_SHOW			= 1,
		SUB_STATE_OBJECT_IGNORE			= 255,
	};

// Member variables
protected:
	unsigned int						m_uiWorldIdx;
	unsigned int						m_uiObjIdx;
	eMAIN_STATE							m_eObjMainState;
	eSUB_STATE_OBJECT					m_eObjectShowHide;

// Constructions
public:
	CDboTSCheckObjState( void );

// Methods
public:
	virtual unsigned int				GetEntityType( void ) const { return DBO_COND_TYPE_ID_CHECK_OBJ_STATE; }

	unsigned int						GetWorldIdx( void ) const;
	void								SetWorldIdx( unsigned int uiWorldIdx );

	unsigned int						GetObjectIdx( void ) const;
	void								SetObjectIdx( unsigned int uiObjectIdx );

	eMAIN_STATE							GetObjectMainState( void ) const;
	void								SetObjectMainState( eMAIN_STATE eObjectMainState );

	eSUB_STATE_OBJECT					GetObjectShowHide( void ) const;
	void								SetObjectShowHide( eSUB_STATE_OBJECT eObjectShowHide );

// Implementations
protected:
	// 스크립트로 부터 컴포넌트 객체의 데이터를 로딩 및 입력 시키기 위한 함수
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );
};


inline unsigned int CDboTSCheckObjState::GetWorldIdx( void ) const
{
	return m_uiWorldIdx;
}


inline unsigned int CDboTSCheckObjState::GetObjectIdx( void ) const
{
	return m_uiObjIdx;
}


inline CDboTSCheckObjState::eMAIN_STATE CDboTSCheckObjState::GetObjectMainState( void ) const
{
	return m_eObjMainState;
}


inline CDboTSCheckObjState::eSUB_STATE_OBJECT CDboTSCheckObjState::GetObjectShowHide( void ) const
{
	return m_eObjectShowHide;
}


#endif
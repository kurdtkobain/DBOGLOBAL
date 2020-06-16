/******************************************************************************
* File			: GMChatGui.h
* Author		: Hong SungBock
* Copyright		: (주)NTL
* Date			: 2008. 10. 21
* Abstract		: 
*****************************************************************************
* Desc			: GM과의 채팅 다이얼로그
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presetation
#include "NtlPLGui.h"

// cleint
#include "Windowby3.h"
#include "SurfaceGui.h"

class CGMChatGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CGMChatGui(const RwChar* pName);
	virtual ~CGMChatGui();

	RwBool		Create();
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);

	// avooo's comment : GM 채팅은 게임의 내용이 아니며 이미 다른 다이얼로그가
	//					 꽉 들어찬 상태에서 고정적으로 GM 채팅을 위해 자리를 만들 수도 없다.
	//					 GM 채팅은 언제나 유저가 위치를 변경할 수 있도록 한다.
	virtual void	SetMovable(RwBool bMovable) {}

	VOID		SetGMText(const WCHAR* pwcText);

protected:
	CGMChatGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			OnGotFocus();
	VOID			OnLostFocus();
	VOID			OnInputReturn();
	VOID			OnIMEChange( RwInt32 uiIMEState );
	VOID			OnCaptureWheelMove(RwInt32 iFlag, RwInt16 sDelta, CPos& pos);

	VOID			OnMove( RwInt32 iOldX, RwInt32 iOldY );
	VOID			OnPaint();

protected:
	gui::CSlot			m_slotGotFocus;
	gui::CSlot			m_slotLostFocus;
	gui::CSlot			m_slotReturn;
	gui::CSlot			m_slotIMEChange;
	gui::CSlot			m_slotCaptureWheelMove;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotPaint;

	gui::COutputBox*	m_pOutDisplay;			// 대화내용
	gui::CStaticBox*	m_pDialogName;			// 다이얼로그 제목
	gui::CStaticBox*	m_pIME;					// IME 상태
	gui::CInputBox*		m_pInput;				// 유저 인풋창

	CWindowby3			m_BackPanel;			// 배경
	CSurfaceGui			m_InputBack;			// 인풋 배경
};
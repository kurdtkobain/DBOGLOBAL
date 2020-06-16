/*****************************************************************************
 *
 * File			: NTLCamera.h
 * Author		: HongHoDong
 * Copyright	: (주)NTL
 * Date			: 2005. 7. 14	
 * Abstract		: NTl Camera
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/
#ifndef __NTL_GAME_CAMERA__
#define __NTL_GAME_CAMERA__

#include "NtlCamera.h"
#include "InputHandler.h"
#include "NtlPLCharacter.h"

#define MIN_DELTA_EPLISION	0.00000001f

class CNtlGameCamera : public CNtlCamera
{
public:
	CNtlGameCamera(void);
	~CNtlGameCamera(void);

private:
	RwReal	m_fDistance;		//Camera와 Target과의 거리

	RwReal	m_fMaxDistance;
	RwReal	m_fMinDistance;
	RwReal	m_fSmoothDistance;
	RwReal	m_fPrefDistance;

	RwReal	m_fXAngle;
	RwReal	m_fMaxXAngle;
	RwReal	m_fMinXAngle;
	RwReal	m_fSmoothXAngle;
	RwReal	m_fPrefXAngle;

	RwReal	m_fYAngle;
	RwReal	m_fMaxYAngle;
	RwReal	m_fMinYAngle;
	RwReal	m_fSmoothYAngle;
	RwReal	m_fOldSmoothYAngle;
	RwReal	m_fPrefYAngle;

	RwMatrix *m_pCachedMatrix;

	RwV3d	m_vLookAt; 
	RwReal	m_fLookAtHeight;
	
	INPUT_HANDLE	m_handleMouseWheel;
	INPUT_HANDLE	m_handleMouseMove;
	INPUT_HANDLE	m_handleMouseDown;
	INPUT_HANDLE	m_handleMouseUp;
	INPUT_HANDLE	m_handleKeyDown;

	RwV2d	m_OldMouseMove;
	RwBool	m_bMouseMoveValidFlag;
	CNtlPLCharacter *m_pTarget;
public:
	void	HandleMouse(RwReal fAngleX, RwReal fAngleY);
	void	HandleMouse(RwReal fDeltaZ);

	void	Update(RwReal fElapsed);

	int		MouseDownHandler(unsigned int uiMouseData);
	int		MouseUpHandler(unsigned int uiMouseData);
	int		MouseMoveHandler(unsigned int uiMouseData);
	int		MouseWheelHandler(unsigned int uiMouseData);
	int		KeyboardDownHandler(unsigned int uiKeyData);
};

#endif
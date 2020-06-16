//***********************************************************************************
//	File		:	NtlResourceHurricaneSystem.h
//	Desc		:	
//	Begin		:	2005. 7.28
//	Copyright	:	ⓒ 2005 by agebreak CO., Ltd
//	Author		:	agebreak
//	Update		:	
//***********************************************************************************

#pragma once

#include ".\ntlresourceImVertexsystem.h"

class CNtlResourceHurricaneSystem : public CNtlResourceImVertexSystem
{
public:
	SNtlHurricaneEmitterStandard	m_EmitterStandard;

public:
	CNtlResourceHurricaneSystem(const RwChar* strName);
	virtual ~CNtlResourceHurricaneSystem(void);

	virtual void	Destroy();

	virtual RwBool	Load(FILE* pFile);
};

/*****************************************************************************
 *
 * File			: NtlLoadingController.cpp
 * Author		: JeongHo,Rho
 * Copyright	: (주)NTL
 * Date			: 2007. 2. 13	
 * Abstract		: 
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/
#include "precomp_ntlcore.h"
#include "NtlLoadingController.h"



CNtlLoadingController* CNtlLoadingController::GetInstance( void )
{
	static CNtlLoadingController clInstance;
	return &clInstance;
}

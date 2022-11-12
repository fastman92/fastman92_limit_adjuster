/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CCamera.h"

#include "../../Core/LimitAdjuster.h"

using namespace Game;

CCamera* TheCamera;
CCamera_VarInitialisation g_CCamera_varInitialisation;

void CCamera::TakeControl(CEntity *, short, short, int)
{

}

// Initialize
void CCamera_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if(gameVersion == GAME_VERSION_GTA_III_1_0_WIN_X86)
		TheCamera = (CCamera*)0x6FACF8;
#endif
	else
		TheCamera = nullptr;
}
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CTimer.h"

#include "../../Core/LimitAdjuster.h"

using namespace Game;

unsigned int* CTimer::m_snTimeInMilliseconds = 0;

// Initialize
void CTimer_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (!g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		return;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		CTimer::m_snTimeInMilliseconds = (unsigned int*)0xB7CB84;
	}
	#elif defined(IS_PLATFORM_ANDROID)
	{
		CTimer::m_snTimeInMilliseconds = (unsigned int*)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN6CTimer22m_snTimeInMillisecondsE"
		);
	}
	#endif
}

CTimer_VarInitialisation g_CTimer_varInitialisation;
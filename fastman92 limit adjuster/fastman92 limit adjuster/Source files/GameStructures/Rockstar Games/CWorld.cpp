/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CWorld.h"

#include "../../Core/LimitAdjuster.h"

using namespace Game;

uintptr_t Address_CWorld__FindGroundZForCoord = 0;

// Finds ground Z for XY coordinates
float CWorld::FindGroundZForCoord(float x, float y)
{
	return g_memoryCall.Function<float>(Address_CWorld__FindGroundZForCoord, x, y);
}

// Initialize
void CWorld_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (!g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		return;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		Address_CWorld__FindGroundZForCoord = (uintptr_t)0x569660;
	}
	#elif defined(IS_PLATFORM_ANDROID_ARM32)
	{
		Address_CWorld__FindGroundZForCoord = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN6CWorld19FindGroundZForCoordEff"
		);
	}
	#endif
}

CWorld_VarInitialisation g_CWorld_varInitialisation;
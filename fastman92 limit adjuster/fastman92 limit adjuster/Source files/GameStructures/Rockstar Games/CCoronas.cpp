/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CCoronas.h"

#include "../../Core/LimitAdjuster.h"

using namespace Game;

uintptr_t Address_CCoronas__RegisterCorona_with_texture = 0;
uintptr_t Address_CCoronas__RegisterCorona_with_coronaType = 0;

void CCoronas::RegisterCorona(unsigned int id, CEntity *attachTo, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const &posn, float radius, float farClip, RwTexture *texture, unsigned char flare, bool enableReflection, bool checkObstacles, int _param_not_used, float angle, bool longDistance, float nearClip, unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay)
{
	g_memoryCall.Function<void>(Address_CCoronas__RegisterCorona_with_texture, id, attachTo, red, green, blue, alpha, &posn, radius, farClip, texture, flare, enableReflection, checkObstacles, _param_not_used, angle, longDistance, nearClip, fadeState, fadeSpeed, onlyFromBelow, reflectionDelay);
}

// Allows to call memory functions
void CCoronas::RegisterCorona(unsigned int id, CEntity *attachTo, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const &posn, float radius, float farClip, unsigned char coronaType, unsigned char flare, bool enableReflection, bool checkObstacles, int _param_not_used, float angle, bool longDistance, float nearClip, unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay)
{
	g_memoryCall.Function<void>(Address_CCoronas__RegisterCorona_with_coronaType, id, attachTo, red, green, blue, alpha, &posn, radius, farClip, coronaType, flare, enableReflection, checkObstacles, _param_not_used, angle, longDistance, nearClip, fadeState, fadeSpeed, onlyFromBelow, reflectionDelay);
}

// Initialize
void CCoronas_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (!g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		return;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		Address_CCoronas__RegisterCorona_with_texture = 0x6FC180;
		Address_CCoronas__RegisterCorona_with_coronaType = 0x6FC580;
	}
	#elif defined(IS_PLATFORM_ANDROID)
	Address_CCoronas__RegisterCorona_with_texture = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN8CCoronas14RegisterCoronaEjP7CEntityhhhhRK7CVectorffP9RwTexturehhhhfbfbfbb"
	);

	Address_CCoronas__RegisterCorona_with_coronaType = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN8CCoronas14RegisterCoronaEjP7CEntityhhhhRK7CVectorffhhhhhfbfbfbb"
	);
	#endif
}

CCoronas_VarInitialisation g_CCoronas_varInitialisation;
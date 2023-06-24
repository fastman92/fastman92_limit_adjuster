/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "RwStream.h"
#include "../../Core/LimitAdjuster.h"

using namespace Game;

RwStream_varInitialisation g_RwStream_varInitialisation;

static uintptr_t Address_RwStreamRead;

int RwStreamRead(RwStream *stream, void *buffer, unsigned int length)
{
	return g_memoryCall.Function<int>(Address_RwStreamRead, stream, buffer, length);
};

// Inits function memory addresses
void RwStream_varInitialisation::Initialise()
{
	if (!g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		return;

	MAKE_VAR_GAME_VERSION();

	#ifdef IS_PLATFORM_WIN_X86
	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		Address_RwStreamRead = 0x7EC9D0;
	}
	#elif defined(IS_PLATFORM_ANDROID)
	Address_RwStreamRead = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_Z12RwStreamReadP8RwStreamPvj"
	);
	#endif
}
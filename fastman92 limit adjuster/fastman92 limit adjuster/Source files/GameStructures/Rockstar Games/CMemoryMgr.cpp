/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CMemoryMgr.h"
#include "../../Core/LimitAdjuster.h"

using namespace Game;

CMemoryMgr_varInitialisation g_CMemoryMgr_varInitialisation;

static uintptr_t Address_CMemoryMgr__Malloc;

void* CMemoryMgr::Malloc(size_t size)
{
	return g_memoryCall.Function<void*>(Address_CMemoryMgr__Malloc, size);
}

static uintptr_t Address_CMemoryMgr__Free;

void CMemoryMgr::Free(void* ptr)
{
	return g_memoryCall.Function<void>(Address_CMemoryMgr__Free, ptr);
}

// Inits function memory addresses
void CMemoryMgr_varInitialisation::Initialise()
{
	if (!g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		return;

	MAKE_VAR_GAME_VERSION();

	#ifdef IS_PLATFORM_WIN_X86
	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		Address_CMemoryMgr__Malloc = 0x72F420;
		Address_CMemoryMgr__Free = 0x72F430;
	}
	#elif defined(IS_PLATFORM_ANDROID)
	Address_CMemoryMgr__Malloc = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN10CMemoryMgr6MallocEj"
	);

	Address_CMemoryMgr__Free = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN10CMemoryMgr4FreeEPv"
	);
	#endif
}
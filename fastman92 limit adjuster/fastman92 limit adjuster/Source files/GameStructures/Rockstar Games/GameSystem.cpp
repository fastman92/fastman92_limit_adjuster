/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "GameSystem.h"

#include "../../Core/LimitAdjuster.h"

CGameSystem_VarInitialisation g_CSystem_varInitialisation;

using namespace Game;

// Addresses
static void* RsGlobal = 0;
static uintptr_t Address_OS_ScreenGetWidth = 0;
static uintptr_t Address_OS_ScreenGetHeight = 0;

unsigned int CGameSystem::ScreenGetWidth()
{
	#if IS_PLATFORM_ANDROID
	return g_memoryCall.Function<unsigned int>(Address_OS_ScreenGetWidth);
	#else
	return *(unsigned int*)((char*)RsGlobal + 4);
	#endif
}

unsigned int CGameSystem::ScreenGetHeight()
{
	#if IS_PLATFORM_ANDROID
	return g_memoryCall.Function<unsigned int>(Address_OS_ScreenGetHeight);
	#else
	return *(unsigned int*)((char*)RsGlobal + 8);
	#endif
}

// Initialize
void CGameSystem_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (!g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		return;

	#if IS_PLATFORM_ANDROID
	Address_OS_ScreenGetWidth = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_Z17OS_ScreenGetWidthv"
	);

	Address_OS_ScreenGetHeight = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_Z18OS_ScreenGetHeightv"
	);
	#else
	if (gameVersion == GAME_VERSION_GTA_III_1_0_WIN_X86)
		RsGlobal = (void*)0x8F4368;
	else if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
		RsGlobal = (void*)0x9B48E0;
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		RsGlobal = (void*)0x0C17040;
	else
		RsGlobal = 0;
#endif
}
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "functions.h"
#include "../../Core/LimitAdjuster.h"

using namespace Game;

Functions_varInitialisation g_functions_varInitialisation;

static uint32_t pGTAIV_crc32FromLowerCaseString = 0;
static uintptr_t Address_FindPlayerCoors = 0;

// Finds player coords
CVector FindPlayerCoors(int playerIndex = -1)
{
	return g_memoryCall.Function<CVector>(Address_FindPlayerCoors, playerIndex);
}

static uintptr_t Address_malloc = 0;
static uintptr_t Address_free = 0;

void* game_malloc(size_t size)
{
	return g_memoryCall.Function<void*>(Address_malloc, size);
}
void game_free(void* ptr)
{
	g_memoryCall.Function<void>(Address_free, ptr);
}

static uintptr_t Address_fopen = 0;
static uintptr_t Address_fclose = 0;

FILE	*game_fopen(const char * filename, const char *mode)
{
	return g_memoryCall.Function<FILE*>(Address_fopen, filename, mode);
}

int	 game_fclose(FILE * fp)
{
	return g_memoryCall.Function<int>(Address_fclose, fp);
}

static uintptr_t Address_GetFirstAtomic = 0;

// Returns pointer to first atomic in clump
RpAtomic* GetFirstAtomic(RpClump* pClump)
{
	return g_memoryCall.Function<RpAtomic*>(Address_GetFirstAtomic, pClump);
}

static uint32_t Address_emu_ArraysGetID = 0;

unsigned int emu_ArraysGetID(unsigned int pEmuArray)
{
	return g_memoryCall.Function<unsigned int>(Address_emu_ArraysGetID, pEmuArray);
}

// Inits function memory addresses
void Functions_varInitialisation::Initialise()
{
	if (!g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		return;

	MAKE_VAR_GAME_VERSION();

	#ifdef IS_PLATFORM_WIN_X86
	if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		Address_FindPlayerCoors = 0x56E010;
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86)
		pGTAIV_crc32FromLowerCaseString = g_mCalc.GetCurrentVAbyPreferedVA(0x45A300);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		pGTAIV_crc32FromLowerCaseString = g_mCalc.GetCurrentVAbyPreferedVA(0x5B1C30);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		pGTAIV_crc32FromLowerCaseString = g_mCalc.GetCurrentVAbyPreferedVA(0x45CF50);
	else if(gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
		pGTAIV_crc32FromLowerCaseString = g_mCalc.GetCurrentVAbyPreferedVA(0x45A8B0);
	#elif defined(IS_PLATFORM_ANDROID)
	Address_FindPlayerCoors = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_Z15FindPlayerCoorsi"
	);

	Address_malloc = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"malloc"
	);

	Address_free = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"free"
	);

	Address_fopen = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"fopen"
	);

	Address_fclose = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"fclose"
	);

	Address_GetFirstAtomic = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_Z14GetFirstAtomicP7RpClump"
	);

	Address_emu_ArraysGetID = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_Z15emu_ArraysGetIDj"
	);	
	#endif
}

// Calculates GTA IV CRC32 from string characters that are first turned into lower case.
uint32_t GTAIV_crc32FromLowerCaseString(const char* str, uint32_t curHash)
{
	return ((uint32_t(*)(const char* str, uint32_t curHash))pGTAIV_crc32FromLowerCaseString)(str, curHash);
}
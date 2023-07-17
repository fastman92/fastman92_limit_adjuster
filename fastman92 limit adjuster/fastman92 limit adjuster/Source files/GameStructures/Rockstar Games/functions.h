/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <stdint.h>
#include <CVector.h>

#include "../../Core/CLimitAdjusterModule.h"

#include "Renderware.h"

#include <stdio.h>

#define FUNC_GTASA_crc32fromBlock 0x53CED0
#define FUNC_GTASA_crc32FromString 0x53CF00
#define FUNC_GTASA_crc32FromUpcaseString 0x53CF30
#define FUNC_GTASA_crc32Continue 0x53CF70

#define FUNC_FindPlayerCoors 0x56E010
#define FUNC_GetRandomBool 0x4D9C80
#define FUNC_FindPlayerPed 0x56E210

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	// Returns bool depending on randomized value.
	// Uses probability value whereas 0.0 means always FALSE, 1.0 or more means always TRUE.
	static auto GetRandomBool = (bool (__cdecl*)(float probability))FUNC_GetRandomBool;
}
#endif

// uinptr_t 

// Finds player coords
CVector FindPlayerCoors(int playerIndex);

// Calculates GTA IV CRC32 from string characters that are first turned into lower case.
uint32_t GTAIV_crc32FromLowerCaseString(const char* str, uint32_t curHash);

// Calculates GTA IV CRC32 from string characters that are first turned into lower case.
static uint32_t GTAIV_crc32FromLowerCaseString(const char* str)
{
	return GTAIV_crc32FromLowerCaseString(str, 0);
}

void* game_malloc(size_t size);
void game_free(void* ptr);
FILE	*game_fopen(const char *, const char *);
int	 game_fclose(FILE *);

// Returns pointer to first atomic in clump
RpAtomic* GetFirstAtomic(RpClump* pClump);

// unsigned int emu_ArraysGetID(unsigned int pEmuArray);

class Functions_varInitialisation : public CLimitAdjusterModule
{
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {};
};

extern Functions_varInitialisation g_functions_varInitialisation;
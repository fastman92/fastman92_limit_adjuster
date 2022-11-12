/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CKeyGen.h"

#include "../../Core/LimitAdjuster.h"

#include <stdio.h>

using namespace Game;

CKeygen_VarInitialisation g_CKeygen_varInitialization;

uintptr_t Address_CKeyGen__GetUppercaseKey;

// Returns hash of upper case key
uint32_t CKeyGen::GetUppercaseKey(const char* str)
{
	return ((uint32_t(__cdecl *)(const char* str)) Address_CKeyGen__GetUppercaseKey)(str);
}

// Initialize
void CKeygen_VarInitialisation::Initialise()
{	
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		Address_CKeyGen__GetUppercaseKey = 0x53CF30;
#endif
	else
		Address_CKeyGen__GetUppercaseKey = NULL;
}
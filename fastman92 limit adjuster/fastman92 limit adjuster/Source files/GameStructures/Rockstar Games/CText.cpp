/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CText.h"
#include "../../Core/LimitAdjuster.h"

using namespace Game;

CText_VarInitialisation g_CText_VarInitialisation;
CText* TheText;

uintptr_t Address_CText__Get;

// Returns the pointer to text
// May return NULL
const void* CText::Get(const char* GXTkey)
{
	return ((const void*(__thiscall *)(CText*, const char *))Address_CText__Get)(this, GXTkey);
}

// Initialize
void CText_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		Address_CText__Get = g_mCalc.GetCurrentVAbyPreferedVA(0x6A0050);
		TheText = (CText*)g_mCalc.GetCurrentVAbyPreferedVA(0xC1B340);
	}
#endif
	else
	{
		Address_CText__Get = 0;
		TheText = nullptr;
	}
}
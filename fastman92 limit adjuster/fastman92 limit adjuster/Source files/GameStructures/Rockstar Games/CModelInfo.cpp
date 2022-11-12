/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CModelInfo.h"
#include "../../Core/LimitAdjuster.h"

using namespace Game;

CModelInfo_VarInitialisation g_CModelInfo_varInitialisation;

void* Address_CModelInfo_GetModelInfo = NULL;

CBaseModelInfo_generic * CModelInfo::GetModelInfo(const char *modelName, int *pIndex)
{
	return ((CBaseModelInfo_generic*( *)(const char *modelName, int *))Address_CModelInfo_GetModelInfo)(
		modelName,
		pIndex
		);
}

// Initialize
void CModelInfo_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if(gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
		Address_CModelInfo_GetModelInfo = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x55F7D0);
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		Address_CModelInfo_GetModelInfo = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x4C5940);
	else if (CGameVersion::Is_GTA_SA_1_0_1_EU_WIN_X86(gameVersion))
		Address_CModelInfo_GetModelInfo = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x4C59C0);
	else if(gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86)
		Address_CModelInfo_GetModelInfo = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x875F90);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		Address_CModelInfo_GetModelInfo = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x98AA80);
	else if(gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		Address_CModelInfo_GetModelInfo = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x8DD270);
	else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
		Address_CModelInfo_GetModelInfo = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x9BCB10);
	else if(gameVersion == GAME_VERSION_GTA_EFLC_1_1_3_0_WIN_X86)
		Address_CModelInfo_GetModelInfo = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x8A7DA0);
#elif defined(IS_PLATFORM_ANDROID_ARM32)
	else if (true)
		Address_CModelInfo_GetModelInfo = (void*)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN10CModelInfo12GetModelInfoEPKcPi");
#endif
	else
		Address_CModelInfo_GetModelInfo = NULL;
}
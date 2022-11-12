/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CStreaming.h"

#include "../../Core/LimitAdjuster.h"

using namespace Game;

// Last selected cab driver ID
unsigned int& CStreaming::LastSelectedCabDriver = *(unsigned int*)0x965524;

uintptr_t Address_CStreaming__AddImageToList = 0;

// Adds image to list
void CStreaming::AddImageToList(const char* filename, bool bIsNotPlayerImg)
{
	((void(*)(const char* filename, bool bIsNotPlayerImg))Address_CStreaming__AddImageToList)(filename, bIsNotPlayerImg);
}

uintptr_t Address_CStreaming__LoadCdDirectory = 0;

// Load CD directory
void CStreaming::LoadCdDirectory(const char* filename, int imgID)
{
	g_memoryCall.Function<void>(Address_CStreaming__LoadCdDirectory, filename, imgID);
}

uintptr_t Address_CStreaming__RequestModel = 0;

// Requests model
void CStreaming::RequestModel(int dwModelId, int flags)
{
	((void(*)(int dwModelId, int flags))Address_CStreaming__RequestModel)(dwModelId, flags);
}

uintptr_t Address_CStreaming__RemoveModel = 0;

// Removes file
void CStreaming::RemoveModel(
	int fileID
	)
{
	((void(*)(int fileID)) Address_CStreaming__RemoveModel)(fileID);
}

// Sets model deletable
void CStreaming::SetModelIsDeletable(int dwModelId)
{
	((void(*)(int index))0x409C10)(dwModelId);
}

// Loads all requested models
void CStreaming::LoadAllRequestedModels(bool bOnlyPriorityRequests)
{
	((void(*)(bool bOnlyPriorityRequests))0x40EA10)(bOnlyPriorityRequests);
}

// Initialize
void CStreaming_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (!g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		return;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		Address_CStreaming__AddImageToList = (uintptr_t)0x407610;
		Address_CStreaming__RequestModel = 0x4087E0;
		Address_CStreaming__RemoveModel = 0x4089A0;
	}
	#elif defined(IS_PLATFORM_ANDROID_ARM32)
	{
		Address_CStreaming__AddImageToList = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN10CStreaming14AddImageToListEPKcb"
		);

		Address_CStreaming__LoadCdDirectory = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN10CStreaming15LoadCdDirectoryEv"
		);

		Address_CStreaming__RequestModel = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN10CStreaming12RequestModelEii"
		);

		Address_CStreaming__RemoveModel = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN10CStreaming11RemoveModelEi"
		);
	}
	#endif
}

CStreaming_VarInitialisation g_CStreaming_varInitialisation;
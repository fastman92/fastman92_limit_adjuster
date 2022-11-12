/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "Directory limits.h"
#include "../Core/CPatch.h"
#include "../Core/CGenericLogStorage.h"
#include "IMGlimits.h"
#include "../Core/LimitAdjuster.h"

using namespace Game;

DirectoryLimits g_directoryLimits;

// Sets the limit for extra objects directory
void DirectoryLimits::SetExtraObjects(int iExtraObjects)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iExtraObjects = this->ms_iExtraObjectsDirLimit;

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x5B8DDF + 1, iExtraObjects);	// push    550	
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_iExtraObjectsDirLimit = iExtraObjects;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DIRECTORY LIMITS: Extra to: %d",
		iExtraObjects
		);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Sets the limit for cutscene directory
void DirectoryLimits::SetCutsceneDirLimit(int iCutsceneDirLimit)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if(CPatch::IsDebugModeActive())
		iCutsceneDirLimit = this->ms_iCutsceneDirLimit;

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x4D5A79 + 1, iCutsceneDirLimit);	// push    512	
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_iCutsceneDirLimit = iCutsceneDirLimit;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DIRECTORY LIMITS: Cutscene directory to: %d",
		iCutsceneDirLimit
		);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}


// Sets the limit for clothes directory
void DirectoryLimits::SetClothesDirLimit(int iClothesDirLimit)
{
	if (iClothesDirLimit != -1)
		this->ms_iClothesDirLimit = iClothesDirLimit;

	this->ms_bClothesDirLimitEnabled = true;
}

// Applies enabled limits
void DirectoryLimits::ApplyEnabledLimits()
{
	if (this->ms_bClothesDirLimitEnabled)
		this->PatchClothesDirLimit();
}

// Initialize
void DirectoryLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		// Extra objects dir limit
		this->ms_iExtraObjectsDirLimit = 550;

		// Cutscene directory limit
		this->ms_iCutsceneDirLimit = 512;

		// Clothes directory limit
		this->ms_iClothesDirLimit = 550;

		// Clothes directory limit enabled?
		this->ms_bClothesDirLimitEnabled = false;

		// player IMG entries
		this->playerImgEntries.ptr = (char*)0xBBCDC8;
	}
#endif
}

// Shutdown
void DirectoryLimits::Shutdown()
{
	if (playerImgEntries.bIsAllocated.Get())
		delete playerImgEntries.ptr;
}

// Patches clothes dir limit
void DirectoryLimits::PatchClothesDirLimit()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		CPatch::EnterNewLevelAndDisableDebugState();
		// CPatch::EnableDebugMode();

		if (CPatch::IsDebugModeActive())
			this->ms_iClothesDirLimit = 550;

		// Allocate
		if (g_IMGlimits.bHandlingOfNewEnhancedFormatOfImgArchivesEnabled || DirectoryLimits::ms_iClothesDirLimit > 550)
		{
			playerImgEntries.ptr = new char[ms_iClothesDirLimit * g_IMGlimits.ms_iCurrentSizeOfCDirectoryEntry];
			playerImgEntries.bIsAllocated.Set(true);
		}

		// Patch
		#if TRUE
		{
			// CClothesBuilder::LoadCdDirectory(void)
			CPatch::PatchPointer(0x5A4190 + 1, playerImgEntries.ptr); // push    offset _playerImgEntries; headers
			CPatch::PatchUINT32(0x5A4195 + 1, ms_iClothesDirLimit); // push    550             ; count

			// int __cdecl CClothesBuilder::CreateSkinnedClump(RpClump *clump, RwTexDictionary *dict, CPedClothesDesc *a3, CPedClothesDesc *old, char a5)
			CPatch::PatchPointer(0x5A69E3 + 1, playerImgEntries.ptr); // push    offset _playerImgEntries; headers
			CPatch::PatchUINT32(0x5A69E8 + 1, ms_iClothesDirLimit); // push    550             ; count
		}
		#endif
	}
#endif
	else
		return;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DIRECTORY LIMITS: Clothes directory to: %d",
		DirectoryLimits::ms_iClothesDirLimit
		);

	CGenericLogStorage::WriteLineSeparator();
}
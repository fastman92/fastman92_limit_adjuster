/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "VisibilityLimits.h"
#include "../Core/CPatch.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/LimitAdjuster.h"

using namespace Game;

VisibilityLimits g_visibilityLimits;

// Sets alpha list limit
void VisibilityLimits::SetAlphaListLimit(int iAlphaListLimit)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iAlphaListLimit = this->ms_alphaListLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		int sizeOfElements = iAlphaListLimit * CLinkList_CVisibilityPlugins__AlphaObjectInfo;

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(0x733A21 + 1, sizeOfElements);	// push    400
			CPatch::PatchUINT32(0x733A5D + 1, sizeOfElements);	// mov     ecx, 400
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	VisibilityLimits::ms_alphaListLimit = iAlphaListLimit;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of VISIBILITY: Alpha list limit to: %d",
		iAlphaListLimit
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets alpha boat atomic list limit
void VisibilityLimits::SetAlphaBoatAtomicListLimit(int iAlphaBoatAtomicListLimit)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iAlphaBoatAtomicListLimit = this->ms_alphaBoatAtomicListLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		int sizeOfElements = iAlphaBoatAtomicListLimit * CLinkList_CVisibilityPlugins__AlphaObjectInfo;

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(0x733A86 + 1, sizeOfElements);	// push    400
			CPatch::PatchUINT32(0x733AD6 + 1, sizeOfElements);	// mov     ecx, 400
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	VisibilityLimits::ms_alphaBoatAtomicListLimit = iAlphaBoatAtomicListLimit;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of VISIBILITY: Alpha boat atomic list to: %d",
		iAlphaBoatAtomicListLimit
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets alpha entity list limit
void VisibilityLimits::SetAlphaEntityListLimit(int iAlphaEntityListLimit)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iAlphaEntityListLimit = this->ms_alphaEntityListLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		int sizeOfElements = iAlphaEntityListLimit * CLinkList_CVisibilityPlugins__AlphaObjectInfo;

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(0x733B04 + 1, sizeOfElements);	// push    4000
			CPatch::PatchUINT32(0x733B54 + 1, sizeOfElements);	// mov     ecx, 4000
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	VisibilityLimits::ms_alphaEntityListLimit = iAlphaEntityListLimit;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of VISIBILITY: Alpha entity list limit to: %d",
		iAlphaEntityListLimit
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets alpha underwater entity list limit
void VisibilityLimits::SetAlphaUnderwaterEntityListLimit(int iAlphaUnderwaterEntityListLimit)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iAlphaUnderwaterEntityListLimit = this->ms_alphaUnderwaterEntityListLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		int sizeOfElements = iAlphaUnderwaterEntityListLimit * CLinkList_CVisibilityPlugins__AlphaObjectInfo;

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(0x733B84 + 1, sizeOfElements);	// push    2000
			CPatch::PatchUINT32(0x733BD4 + 1, sizeOfElements);	// mov     ecx, 2000
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_alphaUnderwaterEntityListLimit = iAlphaUnderwaterEntityListLimit;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of VISIBILITY: Alpha really draw last list limit to: %d",
		iAlphaUnderwaterEntityListLimit
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets alpha really draw last list limit
void VisibilityLimits::SetAlphaReallyDrawLastListLimit(int iAlphaReallyDrawLastListLimit)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iAlphaReallyDrawLastListLimit = this->ms_alphaUnderwaterEntityListLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{	
		int sizeOfElements = iAlphaReallyDrawLastListLimit * CLinkList_CVisibilityPlugins__AlphaObjectInfo;

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(0x733C04 + 1, sizeOfElements);	// push    1000
			CPatch::PatchUINT32(0x733C54 + 1, sizeOfElements);	// mov     ecx, 1000
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_alphaReallyDrawLastListLimit = iAlphaReallyDrawLastListLimit;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of VISIBILITY: Alpha really draw last list limit to: %d",
		iAlphaReallyDrawLastListLimit
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets weapon peds for PC limit
void VisibilityLimits::SetWeaponPedsForPCLimit(int iWeaponPedsForPClimit)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iWeaponPedsForPClimit = this->ms_weaponPedsForPCLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		int sizeOfElements = iWeaponPedsForPClimit * CLinkList_CVisibilityPlugins__WeaponPedInfo;

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(0x733C84 + 1, sizeOfElements);	// push    1200
			CPatch::PatchUINT32(0x733CD4 + 1, sizeOfElements);	// mov     ecx, 1200
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	VisibilityLimits::ms_weaponPedsForPCLimit = iWeaponPedsForPClimit;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of VISIBILITY: Weapon peds for PC limit to: %d",
		iWeaponPedsForPClimit
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Initialize
void VisibilityLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		this->CLinkList_CVisibilityPlugins__AlphaObjectInfo = 20;
		this->CLinkList_CVisibilityPlugins__WeaponPedInfo = 12;

		this->ms_alphaListLimit = 20;
		this->ms_alphaBoatAtomicListLimit = 20;
		this->ms_alphaEntityListLimit = 200;
		this->ms_alphaUnderwaterEntityListLimit = 100;
		this->ms_alphaReallyDrawLastListLimit = 50;
		this->ms_weaponPedsForPCLimit = 100;
	}
}
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "SCMlimits.h"

#include "../Core/CCodeMover.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

using namespace Game;

SCMlimits g_SCMlimits;

// Returns script space size
unsigned int SCMlimits::GetScriptSpaceSize()
{
	return this->iMAINsegmentSize + this->iMissionSize;
}

// Sets max size of main.scm
void SCMlimits::SetMaxMAINsegmentSize(int maxMAINsegmentSize)
{
	this->iMAINsegmentSize = maxMAINsegmentSize;
}

// Sets max size of mission
void SCMlimits::SetMaxMissionSize(int iMaxMissionSize)
{
	this->iMissionSize = iMaxMissionSize;
}

// Sets the limit for scripts array
void SCMlimits::SetScriptsArrayLimit(int iScriptsArrayLimit)
{
	this->ms_iScriptsArrayLimit = iScriptsArrayLimit;
	this->ms_bScriptsArrayLimitSet = true;
}

// Sets the mission cleanup limit
void SCMlimits::SetMissionCleanUpLimit(int iMissionCleanUpLimit)
{
	this->ms_iMissionCleanupLimit = iMissionCleanUpLimit;
	this->ms_bMissionCleanUpLimitSet = true;
}

// Sets the used object array limit
void SCMlimits::SetUsedObjectArrayLimit(int iUsedObjectArrayLimit)
{
	this->ms_iUsedObjectArrayLimit = iUsedObjectArrayLimit;
	this->ms_bUsedObjectArrayLimitSet = true;
}

// Sets the switch jump table limit
void SCMlimits::SetSwitchJumpTableLimit(int iSwitchJumpTableLimit)
{
	this->ms_iScriptJumpTableLimit = iSwitchJumpTableLimit;
	this->ms_bScriptJumpTableLimitSet = true;
}

// Sets the scripts for brains limit
void SCMlimits::SetScriptsForBrainsLimit(int iScriptsForBrainsLimit)
{
	this->ms_iScriptsForBrainsLimit = iScriptsForBrainsLimit;
	this->ms_bScriptsForBrainsLimitSet = true;
}

extern "C"
{
	uint32_t ScriptSpaceSize;
	uint32_t MAINsegmentSize;
	uint32_t MissionSize;

	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
	// patch for 0x329EC4
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CTheScripts__Init_329ECC_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTheScripts__Init_329EC4()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, ScriptSpaceSize)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__Init_329ECC_thumb)
			);
	}

	// patch for 0x32A060
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CTheScripts__Init_32A068_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTheScripts__Init_32A060()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R8, MAINsegmentSize)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__Init_32A068_thumb)
			);
	}

	// patch for 0x32A0DA
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CTheScripts__Init_32A09E_thumb = 0;	// loc_32A09E
		uintptr_t Address_GTA_SA_2_00_CTheScripts__Init_32A0E4_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTheScripts__Init_32A0DA()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R8, MAINsegmentSize)
			"BLT 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__Init_32A0E4_thumb)

			// Branches
			"1:\n"	// loc_32A09E
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__Init_32A09E_thumb)
			);
	}

	// patch for 0x34E1C0
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_LoadMissionScript_34E1C8_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_LoadMissionScript_34E1C0()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, MissionSize)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_LoadMissionScript_34E1C8_thumb)
			);
	}

	// patch for 0x34E6F0
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E6F8_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E6F0()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R9, MissionSize)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E6F8_thumb)
			);
	}

	// patch for 0x34E782
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E738_thumb = 0;	// loc_34E738
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E78C_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E782()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R9, MissionSize)
			"BLT 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E78C_thumb)

			// Branches
			"1:\n"	// loc_34E738
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E738_thumb)
			);
	}

	// patch for 0x34E794
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E79C_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E794()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, MAINsegmentSize)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E79C_thumb)
			);
	}

	// patch for 0x48C98A
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CTheScripts__Load_48C994_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTheScripts__Load_48C98A()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R3, MAINsegmentSize)
			"LDR R1, =("/* missionScript_ptr */"0x67627C - 0x48C99C)\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__Load_48C994_thumb)
			);
	}

	// patch for 0x48CA62
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CTheScripts__Load_48CA6C_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTheScripts__Load_48CA62()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, MAINsegmentSize)
			"ADDS R5, R1, R0\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__Load_48CA6C_thumb)
			);
	}
	#endif
}

bool SCMlimits::ScriptSpaceLimitsCheckIfSupportedVersion(Game::eGameVersion gameVersion)
{
	return gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A;
}

// Patches script space limits, should be executed when limits are set.
void SCMlimits::PatchScriptSpaceLimits()
{
	MAKE_VAR_GAME_VERSION();

	if (!ScriptSpaceLimitsCheckIfSupportedVersion(gameVersion))
		return;

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if(CPatch::IsDebugModeActive())
	{
		this->iMAINsegmentSize = defaultMAINsegmentSize;
		this->iMissionSize = defaultMissionSize;
	}
	else
	{
		if(this->iMAINsegmentSize == defaultMAINsegmentSize
			&& this->iMissionSize == defaultMissionSize)
			return;
	}

	// See if sizes are multiplies of 4
	if (this->iMAINsegmentSize % 4 != 0 || this->iMissionSize % 4 != 0)
		throw f92_runtime_error(
			"'Max size of MAIN segment' and 'Max mission size' have to be multiplies of 4\n"
			"Given values:\n"
			"SCMlimits::iMAINsegmentSize = %d\n"
			"SCMlimits::iMissionSize = %d",

			this->iMAINsegmentSize,
			this->iMissionSize
			);

	////
	::MAINsegmentSize = this->iMAINsegmentSize;
	::MissionSize = this->iMissionSize;
	////
	
	ScriptSpaceSize = this->GetScriptSpaceSize();

	if (ScriptSpaceSize > defaultMAINsegmentSize + defaultMissionSize)
	{
		this->CTheScripts__ScriptSpace.ptr = new uint8_t[ScriptSpaceSize];
		this->CTheScripts__ScriptSpace.bIsAllocated.Set(true);
	}

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
	{
		// Patch references to CTheScripts::ScriptSpace
		#if TRUE
		{
			CPatch::PatchPointer(0x44CA42 + 2, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x44CA92 + 2, CTheScripts__ScriptSpace.ptr);	// mov     eax, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x44CAB1 + 2, CTheScripts__ScriptSpace.ptr);	// mov     esi, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[esi]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x44CB36 + 2, CTheScripts__ScriptSpace.ptr);	// mov     ecx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[edi]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x44CB58 + 2, CTheScripts__ScriptSpace.ptr);	// mov     dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[edi], ecx; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x44CB60 + 2, CTheScripts__ScriptSpace.ptr);	// mov     ecx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x44CB6B + 2, CTheScripts__ScriptSpace.ptr);	// mov     dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax], 0; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x44CBAD + 2, CTheScripts__ScriptSpace.ptr);	// mov     dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[edi], ecx; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x463DAD + 1, CTheScripts__ScriptSpace.ptr);	// add     eax, offset _ZN11CTheScripts11ScriptSpaceE; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x463E00 + 3, CTheScripts__ScriptSpace.ptr);	// lea     eax, _ZN11CTheScripts11ScriptSpaceE[ecx+edx*8]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x463E38 + 3, CTheScripts__ScriptSpace.ptr);	// lea     edx, _ZN11CTheScripts11ScriptSpaceE[eax+ecx]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x463E51 + 3, CTheScripts__ScriptSpace.ptr);	// lea     eax, _ZN11CTheScripts11ScriptSpaceE[ecx+edx]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x463FC7 + 2, CTheScripts__ScriptSpace.ptr);	// add     ecx, offset _ZN11CTheScripts11ScriptSpaceE; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x463FE9 + 1, CTheScripts__ScriptSpace.ptr);	// add     eax, offset _ZN11CTheScripts11ScriptSpaceE; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x4640DE + 2, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x464159 + 2, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[edx]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x464165 + 3, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax+edx*4]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x464191 + 3, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax+edx*4]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x4641BA + 2, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[edx]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x46429A + 2, CTheScripts__ScriptSpace.ptr);	// mov     eax, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x464310 + 3, CTheScripts__ScriptSpace.ptr);	// mov     eax, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax+edx*4]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x4643C0 + 2, CTheScripts__ScriptSpace.ptr);	// mov     dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax], edx; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x464412 + 2, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[edx]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x464420 + 3, CTheScripts__ScriptSpace.ptr);	// mov     dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax+edx*4], esi; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x46444C + 3, CTheScripts__ScriptSpace.ptr);	// mov     dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax+edx*4], esi; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x464473 + 2, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[edx]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x464555 + 2, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x4645D0 + 2, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[edx]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x4645DC + 3, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax+edx*4]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x464608 + 3, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax+edx*4]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x464631 + 2, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[edx]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x4647CA + 1, CTheScripts__ScriptSpace.ptr);	// add     eax, offset _ZN11CTheScripts11ScriptSpaceE; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x46482A + 3, CTheScripts__ScriptSpace.ptr);	// lea     eax, _ZN11CTheScripts11ScriptSpaceE[ecx+edx]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x464846 + 3, CTheScripts__ScriptSpace.ptr);	// lea     eax, _ZN11CTheScripts11ScriptSpaceE[eax+ecx*8]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x46485D + 3, CTheScripts__ScriptSpace.ptr);	// lea     eax, _ZN11CTheScripts11ScriptSpaceE[edx+eax*4]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x466834 + 2, CTheScripts__ScriptSpace.ptr);	// lea     eax, _ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x468D5D + 1, CTheScripts__ScriptSpace.ptr);	// mov     edi, offset _ZN11CTheScripts11ScriptSpaceE; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x468E79 + 1, CTheScripts__ScriptSpace.ptr);	// push    offset _ZN11CTheScripts11ScriptSpaceE; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x468ED5 + 1, CTheScripts__ScriptSpace.ptr);	// push    offset _ZN11CTheScripts11ScriptSpaceE; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x469448 + 2, CTheScripts__ScriptSpace.ptr);	// lea     ecx, _ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x5D4C43 + 1, CTheScripts__ScriptSpace.ptr + 3);	// mov     eax, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE+3
			CPatch::PatchPointer(0x5D4C92 + 2, CTheScripts__ScriptSpace.ptr);	// lea     ecx, _ZN11CTheScripts11ScriptSpaceE[edi]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x5D4CAF + 2, CTheScripts__ScriptSpace.ptr);	// lea     edx, _ZN11CTheScripts11ScriptSpaceE[edi]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x5D4F6A + 1, CTheScripts__ScriptSpace.ptr);	// sub     eax, offset _ZN11CTheScripts11ScriptSpaceE; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x5D4F92 + 1, CTheScripts__ScriptSpace.ptr);	// sub     eax, offset _ZN11CTheScripts11ScriptSpaceE; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x5D5020 + 2, CTheScripts__ScriptSpace.ptr);	// lea     ecx, _ZN11CTheScripts11ScriptSpaceE[edi]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x5D503D + 2, CTheScripts__ScriptSpace.ptr);	// lea     edx, _ZN11CTheScripts11ScriptSpaceE[edi]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x5D534F + 2, CTheScripts__ScriptSpace.ptr);	// lea     eax, _ZN11CTheScripts11ScriptSpaceE[edx]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x5D537E + 2, CTheScripts__ScriptSpace.ptr);	// lea     edx, _ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x15620C3 + 2, CTheScripts__ScriptSpace.ptr);	// lea     eax, _ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x1564F1E + 2, CTheScripts__ScriptSpace.ptr);	// mov     ecx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x1564FB2 + 2, CTheScripts__ScriptSpace.ptr);	// mov     dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[edx], 0; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x1565610 + 1, CTheScripts__ScriptSpace.ptr);	// push    offset _ZN11CTheScripts11ScriptSpaceE; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x1565E20 + 1, CTheScripts__ScriptSpace.ptr+3);	// mov     eax, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE+3
			CPatch::PatchPointer(0x1565E25 + 2, CTheScripts__ScriptSpace.ptr + 3);	// mov     eax, dword ptr ds:(_ZN11CTheScripts11ScriptSpaceE+3)[eax]
			CPatch::PatchPointer(0x1565E2B + 1, CTheScripts__ScriptSpace.ptr + 8);	// add     eax, (offset _ZN11CTheScripts11ScriptSpaceE+8)
			CPatch::PatchPointer(0x1569FF2 + 2, CTheScripts__ScriptSpace.ptr);	// mov     ecx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x156A082 + 2, CTheScripts__ScriptSpace.ptr);	// mov     eax, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x156A09F + 2, CTheScripts__ScriptSpace.ptr);	// mov     ebx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x156AA19 + 2, CTheScripts__ScriptSpace.ptr);	// cmp     dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[eax], 1; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x156E375 + 2, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[edx]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x156F378 + 2, CTheScripts__ScriptSpace.ptr);	// mov     edx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE[edx]; CTheScripts::ScriptSpace
			CPatch::PatchPointer(0x156F453 + 1, CTheScripts__ScriptSpace.ptr + 3);	// mov     eax, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE+3
			CPatch::PatchPointer(0x156F45C + 2, CTheScripts__ScriptSpace.ptr + 3);	// mov     ecx, dword ptr ds:(_ZN11CTheScripts11ScriptSpaceE+3)[eax]
			CPatch::PatchPointer(0x156F462 + 2, CTheScripts__ScriptSpace.ptr + 3);	// mov     esi, dword ptr ds:(_ZN11CTheScripts11ScriptSpaceE+3)[ecx]
			CPatch::PatchPointer(0x156F468 + 2, CTheScripts__ScriptSpace.ptr + 8);	// add     esi, (offset _ZN11CTheScripts11ScriptSpaceE+8)
			CPatch::PatchPointer(0x156F5A0 + 2, CTheScripts__ScriptSpace.ptr + 3);	// mov     ecx, dword ptr ds:_ZN11CTheScripts11ScriptSpaceE+3
			CPatch::PatchPointer(0x156F5A6 + 3, CTheScripts__ScriptSpace.ptr + 8);	// mov     ax, word ptr ds:(_ZN11CTheScripts11ScriptSpaceE+8)[ecx]
			CPatch::PatchPointer(0x156F5AD + 2, CTheScripts__ScriptSpace.ptr + 8);	// lea     ecx, (_ZN11CTheScripts11ScriptSpaceE+8)[ecx]
		}
		#endif

		// Patch sizes of MAIN segment size
		#if TRUE
		{
			CPatch::PatchUINT32(0x468E74 + 1, iMAINsegmentSize);	// push    200000          ; len
			CPatch::PatchUINT32(0x468ECE + 1, iMAINsegmentSize);	// push    200000          ; len
		}
		#endif

		// Patch references to CTheScripts::ScriptSpace + iMissionSize
		#if TRUE
		{
			CPatch::PatchPointer(0x4899D6 + 1, CTheScripts__ScriptSpace.ptr + iMAINsegmentSize);	// push    offset unk_A7A6A0
			CPatch::PatchPointer(0x4899F5 + 1, CTheScripts__ScriptSpace.ptr + iMAINsegmentSize);	// push    offset unk_A7A6A0
			CPatch::PatchPointer(0x489A0B + 3, CTheScripts__ScriptSpace.ptr + iMAINsegmentSize);	// mov     dword ptr [eax+10h], offset unk_A7A6A0
			CPatch::PatchPointer(0x489A5F + 1, CTheScripts__ScriptSpace.ptr + iMAINsegmentSize);	// push    offset unk_A7A6A0
			CPatch::PatchPointer(0x489A75 + 1, CTheScripts__ScriptSpace.ptr + iMAINsegmentSize);	// push    offset unk_A7A6A0
			CPatch::PatchPointer(0x489A8B + 3, CTheScripts__ScriptSpace.ptr + iMAINsegmentSize);	// mov     dword ptr [eax+10h], offset unk_A7A6A0
		}
		#endif

		// Patch sizes of mission space
		#if TRUE
		{
			CPatch::PatchUINT32(0x4899D1 + 1, iMissionSize);	// push    69000
			CPatch::PatchUINT32(0x489A5A + 1, iMissionSize);	// push    69000
			 
		}
		#endif

		// Patch sizes of CTheScripts::ScriptSpace
		#if TRUE
		{
			CPatch::PatchUINT32(
				0x401CF8 + 1,
				ScriptSpaceSize / sizeof(uint32_t)
				);	// mov     ecx, 106B2h

		}
		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		// Patch references to CTheScripts::ScriptSpace
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x676040), CTheScripts__ScriptSpace.ptr);	// DCD _ZN11CTheScripts11ScriptSpaceE; CTheScripts::ScriptSpace

		// Changes
		Address_GTA_SA_2_00_CTheScripts__Init_329ECC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x329ECC));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x329EC4),
			(void*)&patch_GTA_SA_2_00_CTheScripts__Init_329EC4, 8
		);

		Address_GTA_SA_2_00_CTheScripts__Init_32A068_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32A068));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32A060),
			(void*)&patch_GTA_SA_2_00_CTheScripts__Init_32A060, 8
		);

		Address_GTA_SA_2_00_CTheScripts__Init_32A09E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32A09E));
		Address_GTA_SA_2_00_CTheScripts__Init_32A0E4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32A0E4));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32A0DA),
			(void*)&patch_GTA_SA_2_00_CTheScripts__Init_32A0DA, 10
		);

		Address_GTA_SA_2_00_LoadMissionScript_34E1C8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x34E1C8));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x34E1C0),
			(void*)&patch_GTA_SA_2_00_LoadMissionScript_34E1C0, 8
		);

		Address_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E6F8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x34E6F8));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x34E6F0),
			(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E6F0, 8
		);

		Address_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E738_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x34E738));
		Address_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E78C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x34E78C));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x34E782),
			(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E782, 10
		);

		Address_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E79C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x34E79C));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x34E794),
			(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands1000To1099_34E794, 8
		);

		Address_GTA_SA_2_00_CTheScripts__Load_48C994_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x48C994));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x48C98A),
			(void*)&patch_GTA_SA_2_00_CTheScripts__Load_48C98A, 10
		);

		Address_GTA_SA_2_00_CTheScripts__Load_48CA6C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x48CA6C));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x48CA62),
			(void*)&patch_GTA_SA_2_00_CTheScripts__Load_48CA62, 10
		);
	}	
	#endif

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified script space limits:\n"
		" - max size of MAIN segment from main.scm: %d bytes\n"
		" - max size of mission from main.scm: %d bytes\n"
		"Total size of CTheScripts::ScriptSpace: %d bytes"
		,
		this->iMAINsegmentSize,
		this->iMissionSize,
		ScriptSpaceSize);

	CGenericLogStorage::WriteLineSeparator();
}

extern "C"
{
	uint32_t ScriptsArraySize;

	#ifdef IS_PLATFORM_ANDROID_ARM32
	// patch for 0x329F88
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CTheScripts__Init_329F14_thumb = 0;	// loc_329F14
		uintptr_t Address_GTA_SA_2_00_CTheScripts__Init_329F90_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTheScripts__Init_329F88()
	{
		__asm(
		".thumb\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, ScriptsArraySize)
			"MOV R9, R8\n"
			"BNE 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__Init_329F90_thumb)

			// Branches
			"1:\n"	// loc_329F14
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__Init_329F14_thumb)
			);
	}
	#endif
}
	
// Patches scripts array limits
void SCMlimits::PatchScriptsArrayLimit()
{
	if(!SCMlimits::ms_bScriptsArrayLimitSet)
		return;

	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();
	
	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if(CPatch::IsDebugModeActive())
			this->ms_iScriptsArrayLimit = 96;
		else if (this->ms_iScriptsArrayLimit > 96)
		{
			CTheScripts__ScriptsArray.array.SetArrayPtr((CRunningScript*)
				new char[
					TypeDetails::SizeOf<CRunningScript>()
				* this->ms_iScriptsArrayLimit]);
		
			memset(
				this->CTheScripts__ScriptsArray.array.GetArrayPointer(),
				NULL,
				this->ms_iScriptsArrayLimit * TypeDetails::SizeOf<CRunningScript>()
			);

			CTheScripts__ScriptsArray.bIsAllocated.Set(true);
		}

		::ScriptsArraySize = this->ms_iScriptsArrayLimit * TypeDetails::SizeOf<CRunningScript>();
		
		MAKE_DEAD_IF();
		#ifdef IS_PLATFORM_WIN_X86
		else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			// Patch pointers
			CPatch::PatchPointer(0x468D7A + 1, &*CTheScripts__ScriptsArray.array);	// mov     esi, offset _ZN11CTheScripts12ScriptsArrayE; CTheScripts::ScriptsArray	; _ZN11CTheScripts4InitEv
			CPatch::PatchPointer(0x468D9B + 2, &CTheScripts__ScriptsArray.array[SCMlimits::ms_iScriptsArrayLimit]);	// cmp     esi, offset word_A90830	; _ZN11CTheScripts4InitEv
			
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
			{
				CPatch::PatchPointer(0x464D24 + 2, &*CTheScripts__ScriptsArray.array);	// sub     ecx, offset _ZN11CTheScripts12ScriptsArrayE; CTheScripts::ScriptsArray	; sub_464D20
				CPatch::PatchPointer(0x464CA2 + 1, &*CTheScripts__ScriptsArray.array);	// add     eax, offset _ZN11CTheScripts12ScriptsArrayE; CTheScripts::ScriptsArray	; sub_464C90
			}
			else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				CPatch::PatchPointer(0x1562034 + 2, &*CTheScripts__ScriptsArray.array);	// sub     ecx, offset _ZN11CTheScripts12ScriptsArrayE; CTheScripts::ScriptsArray	; sub_464D20
				CPatch::PatchPointer(0x156E222 + 1, &*CTheScripts__ScriptsArray.array);	// add     eax, offset _ZN11CTheScripts12ScriptsArrayE; CTheScripts::ScriptsArray	; sub_464C90
			}
		}
		#elif defined(IS_PLATFORM_ANDROID_ARM32)
		else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		{
			// Patch pointers
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x679658), &*CTheScripts__ScriptsArray.array);	// DCD _ZN11CTheScripts12ScriptsArrayE; CTheScripts::ScriptsArray

			// Changes
			Address_GTA_SA_2_00_CTheScripts__Init_329F14_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x329F14));
			Address_GTA_SA_2_00_CTheScripts__Init_329F90_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x329F90));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x329F88),
				(void*)&patch_GTA_SA_2_00_CTheScripts__Init_329F88, 8
			);
		}
		#endif
	}
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of SCM LIMITS: Running scripts to: %d",
		this->ms_iScriptsArrayLimit
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Patches script space limits, should be executed when limits are set.
void SCMlimits::PatchSCMlimits()
{
	this->PatchScriptSpaceLimits();
	this->PatchScriptsArrayLimit();

	this->PatchMissionCleanUpLimit();
		
	this->PatchUsedObjectArrayLimit();

	this->PatchSwitchJumpTableLimit();

	this->PatchScriptsForBrainsLimit();
}

extern "C"
{
	uint32_t offset_CMissionCleanup_count;
	uint32_t MissionCleanupLimit;

	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
	// patch for 0x1A37A4
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_sub_1A3750_1A37AE = 0;	// loc_1A37AE
		uintptr_t Address_GTA_SA_2_00_sub_1A3750_1A37AC_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_sub_1A3750_1A37A4()
	{
		__asm(
		".thumb\n"
			"PUSH {R1, R2}\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, offset_CMissionCleanup_count)
			"STRB R4, [R0,R1]\n"
			"POP {R1, R2}\n"
			"LDR R0, =("/* _ZN11CTheScripts14MissionCleanUpE_ptr */"0x677318 - 0x1A37AE)\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_sub_1A3750_1A37AE)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_sub_1A3750_1A37AC_thumb)
			);
	}

	// patch for 0x1A37B8
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_sub_1A3750_1A37AE_thumb = 0;	// loc_1A37AE
		uintptr_t Address_GTA_SA_2_00_sub_1A3750_1A37C0_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_sub_1A3750_1A37B8()
	{
		__asm(
		".thumb\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, MissionCleanupLimit)
			"STR R4, [R2,#4]\n"
			"BNE 1f\n"
			"LDR R0, =("/* _ZN11CTheScripts16ScriptsForBrainsE_ptr */"0x67763C - 0x1A37C4)\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_sub_1A3750_1A37C0_thumb)

			// Branches
			"1:\n"	// loc_1A37AE
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_sub_1A3750_1A37AE_thumb)
			);
	}

	// patch for 0x2E2A98
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CColStore__LoadCollision_2E29E4_thumb = 0;	// loc_2E29E4
		uintptr_t Address_GTA_SA_2_00_CColStore__LoadCollision_2E2AA2_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__LoadCollision_2E2A98()
	{
		__asm(
		".thumb\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, MissionCleanupLimit)
			"BNE 1f\n"
			"LDR R0, =("/* _ZN9CColStore11ms_pColPoolE_ptr */"0x679660 - 0x2E2AAC)\n"
			"MOV R9, #0\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__LoadCollision_2E2AA2_thumb)

			// Branches
			"1:\n"	// loc_2E29E4
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__LoadCollision_2E29E4_thumb)
			);
	}

	// patch for 0x327360
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CMissionCleanup__FindFree_327352_thumb = 0;	// loc_327352
		uintptr_t Address_GTA_SA_2_00_CMissionCleanup__FindFree_327368_thumb = 0;	// _ZN15CMissionCleanup42CheckIfCollisionHasLoadedForMissionObjectsEv
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CMissionCleanup__FindFree_327360()
	{
		__asm(
		".thumb\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, MissionCleanupLimit)
			"BCC 1f\n"
			"MOVS R0, #0\n"
			"BX LR\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CMissionCleanup__FindFree_327368_thumb)

			// Branches
			"1:\n"	// loc_327352
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CMissionCleanup__FindFree_327352_thumb)
			);
	}

	// patch for 0x3274EE
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CMissionCleanup__CheckIfCollisionHasLoadedForMissionObjects_327398_thumb = 0;	// loc_327398
		uintptr_t Address_GTA_SA_2_00_CMissionCleanup__CheckIfCollisionHasLoadedForMissionObjects_3274FA_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CMissionCleanup__CheckIfCollisionHasLoadedForMissionObjects_3274EE()
	{
		__asm(
		".thumb\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, MissionCleanupLimit)
			"BCC 1f\n"
			"ADD SP, SP, #0xC\n"
			"POP {R8-R11}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CMissionCleanup__CheckIfCollisionHasLoadedForMissionObjects_3274FA_thumb)

			// Branches
			"1:\n"	// loc_327398
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CMissionCleanup__CheckIfCollisionHasLoadedForMissionObjects_327398_thumb)
			);
	}

	// patch for 0x32751E
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CMissionCleanup__AddEntityToList_327528_thumb = 0;	// loc_327528
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CMissionCleanup__AddEntityToList_32751E()
	{
		__asm(
		".thumb\n"
			"UXTH R3, LR\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, MissionCleanupLimit)
			"IT CS\n"
			"POPCS {R7,PC}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CMissionCleanup__AddEntityToList_327528_thumb)
			);
	}

	// patch for 0x327534
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CMissionCleanup__AddEntityToList_32754A_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CMissionCleanup__AddEntityToList_327534()
	{
		__asm(
		".thumb\n"
			"BEQ 500f\n"
			"STRB R2, [R12,#-4]\n"
			"STR R1, [R12]\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, offset_CMissionCleanup_count)
			"LDRB R1, [R0,R1]\n"
			"ADD R1, #1\n"
			"500:\n"	// past the IT block
			"BEQ 500f\n"
			"PUSH {R2, R3}\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, offset_CMissionCleanup_count)
			"STRB R1, [R0,R2]\n"
			"POP {R2, R3}\n"
			"500:\n"	// past the IT block
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CMissionCleanup__AddEntityToList_32754A_thumb)
			);
	}

	// patch for 0x327638
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CMissionCleanup__RemoveEntityFromList_327642_thumb = 0;	// loc_327642
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CMissionCleanup__RemoveEntityFromList_327638()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, offset_CMissionCleanup_count)
			"LDRB R0, [R8,R0]\n"
			"SUBS R0, #1\n"
			"PUSH {R1, R2}\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, offset_CMissionCleanup_count)
			"STRB R0, [R8,R1]\n"
			"POP {R1, R2}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CMissionCleanup__RemoveEntityFromList_327642_thumb)
			);
	}

	// patch for 0x32764C
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CMissionCleanup__RemoveEntityFromList_327582_thumb = 0;	// loc_327582
		uintptr_t Address_GTA_SA_2_00_CMissionCleanup__RemoveEntityFromList_327656_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CMissionCleanup__RemoveEntityFromList_32764C()
	{
		__asm(
		".thumb\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, MissionCleanupLimit)
			"BCC 1f\n"
			"ADD SP, SP, #0xC\n"
			"POP {R8-R11}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CMissionCleanup__RemoveEntityFromList_327656_thumb)

			// Branches
			"1:\n"	// loc_327582
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CMissionCleanup__RemoveEntityFromList_327582_thumb)
			);
	}

	// patch for 0x327EBE
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CMissionCleanup__Process_327D18_thumb = 0;	// loc_327D18
		uintptr_t Address_GTA_SA_2_00_CMissionCleanup__Process_327EC8_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CMissionCleanup__Process_327EBE()
	{
		__asm(
		".thumb\n"
			"UXTH R0, R8\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, MissionCleanupLimit)
			"BCC 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CMissionCleanup__Process_327EC8_thumb)

			// Branches
			"1:\n"	// loc_327D18
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CMissionCleanup__Process_327D18_thumb)
			);
	}

	// patch for 0x329FB8
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CTheScripts__Init_329FC0 = 0;	// loc_329FC0
		uintptr_t Address_GTA_SA_2_00_CTheScripts__Init_329FC0_thumb = 0;	// loc_329FC0
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTheScripts__Init_329FB8()
	{
		__asm(
		".thumb\n"
			"PUSH {R1, R2}\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, offset_CMissionCleanup_count)
			"STRB R0, [R3,R1]\n"
			"POP {R1, R2}\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CTheScripts__Init_329FC0)
			"LDR R1, [R1]\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__Init_329FC0_thumb)
			);
	}

	// patch for 0x329FCA
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CTheScripts__Init_329FD4_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTheScripts__Init_329FCA()
	{
		__asm(
		".thumb\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, MissionCleanupLimit)
			"STR R0, [R3,#4]\n"
			"BNE 1f\n"
			"LDR R0, =("/* _ZN11CTheScripts14UpsideDownCarsE_ptr */"0x677538 - 0x329FE4)\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__Init_329FD4_thumb)

			// Branches
			"1:\n"	// loc_329FC0
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__Init_329FC0_thumb)
			);
	}

	// patch for 0x32CCEE
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32CCF8_thumb = 0;	// loc_32CCF8
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32CCEE()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, offset_CMissionCleanup_count)
			"LDRB R0, [R11,R0]\n"
			"SUBS R0, #1\n"
			"PUSH {R1, R2}\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, offset_CMissionCleanup_count)
			"STRB R0, [R11,R1]\n"
			"POP {R1, R2}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32CCF8_thumb)
			);
	}

	// patch for 0x32CD00
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32CC96_thumb = 0;	// loc_32CC96
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32CD08_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32CD00()
	{
		__asm(
		".thumb\n"
			"UXTH R0, R10\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, MissionCleanupLimit)
			"BCC 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32CD08_thumb)

			// Branches
			"1:\n"	// loc_32CC96
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32CC96_thumb)
			);
	}

	// patch for 0x32D186
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D190_thumb = 0;	// loc_32D190
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D186()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, offset_CMissionCleanup_count)
			"LDRB R0, [R11,R0]\n"
			"SUBS R0, #1\n"
			"PUSH {R1, R2}\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, offset_CMissionCleanup_count)
			"STRB R0, [R11,R1]\n"
			"POP {R1, R2}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D190_thumb)
			);
	}

	// patch for 0x32D198
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D12E_thumb = 0;	// loc_32D12E
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D1A0_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D198()
	{
		__asm(
		".thumb\n"
			"UXTH R0, R10\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, MissionCleanupLimit)
			"BCC 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D1A0_thumb)

			// Branches
			"1:\n"	// loc_32D12E
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D12E_thumb)
			);
	}

	// patch for 0x32D730
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D726_thumb = 0;	// loc_32D726
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D42E_thumb = 0;	// loc_32D42E
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D730()
	{
		__asm(
		".thumb\n"
			"UXTH R3, R2\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, MissionCleanupLimit)
			"BCC 1f\n"
			"B 2f\n"

			// Branches
			"1:\n"	// loc_32D726
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D726_thumb)
			"2:\n"	// loc_32D42E
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D42E_thumb)
			);
	}

	// patch for 0x32D748
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D752_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D748()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, offset_CMissionCleanup_count)
			"LDRB R0, [R2,R0]\n"
			"ADDS R0, #1\n"
			"PUSH {R1, R3}\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, offset_CMissionCleanup_count)
			"STRB R0, [R2,R1]\n"
			"POP {R1, R3}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D752_thumb)
			);
	}

	// patch for 0x32DC56
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DC60_thumb = 0;	// loc_32DC60
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DC56()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, offset_CMissionCleanup_count)
			"LDRB R0, [R9,R0]\n"
			"SUBS R0, #1\n"
			"PUSH {R1, R2}\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, offset_CMissionCleanup_count)
			"STRB R0, [R9,R1]\n"
			"POP {R1, R2}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DC60_thumb)
			);
	}

	// patch for 0x32DC64
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DC6C_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DC64()
	{
		__asm(
		".thumb\n"
			"ADDS R5, #8\n"
			"UXTH R0, R8\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, MissionCleanupLimit)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DC6C_thumb)
			);
	}

	// patch for 0x32DF5E
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DF68_thumb = 0;	// loc_32DF68
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DF5E()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, offset_CMissionCleanup_count)
			"LDRB R0, [R11,R0]\n"
			"SUBS R0, #1\n"
			"PUSH {R1, R2}\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, offset_CMissionCleanup_count)
			"STRB R0, [R11,R1]\n"
			"POP {R1, R2}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DF68_thumb)
			);
	}

	// patch for 0x32DF70
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DF02_thumb = 0;	// loc_32DF02
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DF78_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DF70()
	{
		__asm(
		".thumb\n"
			"UXTH R0, R10\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, MissionCleanupLimit)
			"BCC 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DF78_thumb)

			// Branches
			"1:\n"	// loc_32DF02
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DF02_thumb)
			);
	}

	// patch for 0x32E424
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E41C_thumb = 0;	// loc_32E41C
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E42C_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E424()
	{
		__asm(
		".thumb\n"
			"ADDS R0, #8\n"
			"UXTH R3, R2\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, MissionCleanupLimit)
			"BCC 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E42C_thumb)

			// Branches
			"1:\n"	// loc_32E41C
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E41C_thumb)
			);
	}

	// patch for 0x32E554
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E54A_thumb = 0;	// loc_32E54A
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E62A_thumb = 0;	// loc_32E62A
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E554()
	{
		__asm(
		".thumb\n"
			"UXTH R3, R2\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, MissionCleanupLimit)
			"BCC 1f\n"
			"B 2f\n"

			// Branches
			"1:\n"	// loc_32E54A
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E54A_thumb)
			"2:\n"	// loc_32E62A
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E62A_thumb)
			);
	}

	// patch for 0x32E56C
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E576_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E56C()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, offset_CMissionCleanup_count)
			"LDRB R0, [R2,R0]\n"
			"ADDS R0, #1\n"
			"PUSH {R1, R3}\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, offset_CMissionCleanup_count)
			"STRB R0, [R2,R1]\n"
			"POP {R1, R3}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E576_thumb)
			);
	}

	// patch for 0x32E5B8
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5B0_thumb = 0;	// loc_32E5B0
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5C0_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5B8()
	{
		__asm(
		".thumb\n"
			"ADDS R0, #8\n"
			"UXTH R1, R5\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, MissionCleanupLimit)
			"BCC 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5C0_thumb)

			// Branches
			"1:\n"	// loc_32E5B0
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5B0_thumb)
			);
	}

	// patch for 0x32E5F0
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5E8_thumb = 0;	// loc_32E5E8
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5F8_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5F0()
	{
		__asm(
		".thumb\n"
			"ADDS R0, #8\n"
			"UXTH R1, R5\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, MissionCleanupLimit)
			"BCC 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5F8_thumb)

			// Branches
			"1:\n"	// loc_32E5E8
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5E8_thumb)
			);
	}

	// patch for 0x32E60E
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E618_thumb = 0;	// def_32DC84
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E60E()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, offset_CMissionCleanup_count)
			"LDRB R0, [R1,R0]\n"
			"ADDS R0, #1\n"
			"STRB R0, [R1,#0x258]\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E618_thumb)
			);
	}
	#endif
}

class CMissionCleanup
{
public:
	// Init
	void Init()
	{
		*(uint8_t*)(this + offset_CMissionCleanup_count) = 0;

		for (unsigned int i = 0; i < MissionCleanupLimit; i++)
		{
			CMissionCleanupEntry* pEntry = ((CMissionCleanupEntry*)(char*)(this + i * sizeof(CMissionCleanupEntry)));

			pEntry->type = 0;
			pEntry->handle = 0;
		}
	}

	CMissionCleanup* Constructor()
	{
		this->Init();
		return this;
	}
};

// Patches mission cleanup limit
void SCMlimits::PatchMissionCleanUpLimit()
{
	if(!this->ms_bMissionCleanUpLimitSet)
		return;

	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();	
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if(CPatch::IsDebugModeActive())		
			this->ms_iMissionCleanupLimit = 75;
		else if (this->ms_iMissionCleanupLimit > 75)
		{
			if (this->ms_iMissionCleanupLimit > 127)
				throw f92_runtime_error("'Mission cleanup' limit may not be higher than 127.");

			this->CTheScripts__MissionCleanUp.ptr =
				new char
				[ms_iMissionCleanupLimit * sizeof(CMissionCleanupEntry) + sizeof(uint32_t)];

			this->CTheScripts__MissionCleanUp.bIsAllocated.Set(true);
		}

		// Set variables
		#if TRUE
		{
			offset_CMissionCleanup_count = ms_iMissionCleanupLimit * sizeof(CMissionCleanupEntry);
			::MissionCleanupLimit = ms_iMissionCleanupLimit;
		}
		#endif

		MAKE_DEAD_IF();
		#ifdef IS_PLATFORM_WIN_X86
		else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x405250 + 2, CTheScripts__MissionCleanUp.ptr);	// mov     al, byte ptr ds:_ZN11CTheScripts14MissionCleanUpE.objects.type[esi]; CTheScripts::MissionCleanUp	; sub_405175
			CPatch::PatchPointer(0x40525A + 2, &((CMissionCleanupEntry*)CTheScripts__MissionCleanUp.ptr)->handle);	// mov     ecx, ds:_ZN11CTheScripts14MissionCleanUpE.objects.handle[esi]	; sub_405175
			CPatch::PatchPointer(0x4052B4 + 2, &((CMissionCleanupEntry*)CTheScripts__MissionCleanUp.ptr)->handle);	// mov     ecx, ds:_ZN11CTheScripts14MissionCleanUpE.objects.handle[esi]	; sub_405175
			CPatch::PatchPointer(0x410950 + 2, &((CMissionCleanupEntry*)CTheScripts__MissionCleanUp.ptr)->type);	// mov     al, byte ptr ds:_ZN11CTheScripts14MissionCleanUpE.objects.type[esi]; CTheScripts::MissionCleanUp	; sub_410865
			CPatch::PatchPointer(0x41095A + 2, &((CMissionCleanupEntry*)CTheScripts__MissionCleanUp.ptr)->handle);	// mov     ecx, ds:_ZN11CTheScripts14MissionCleanUpE.objects.handle[esi]	; sub_410865
			CPatch::PatchPointer(0x410996 + 2, &((CMissionCleanupEntry*)CTheScripts__MissionCleanUp.ptr)->handle);	// mov     ecx, ds:_ZN11CTheScripts14MissionCleanUpE.objects.handle[esi]	; sub_410865
			CPatch::PatchPointer(0x4320ED + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_431F80
			CPatch::PatchPointer(0x432271 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_431F80
			CPatch::PatchPointer(0x46776A + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_466DE0
			CPatch::PatchPointer(0x4677C3 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_466DE0
			CPatch::PatchPointer(0x467B64 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_466DE0
			CPatch::PatchPointer(0x468DA9 + 2, (char*)CTheScripts__MissionCleanUp.ptr+offset_CMissionCleanup_count);	// mov     byte ptr ds:_ZN11CTheScripts14MissionCleanUpE.count, bl	; _ZN11CTheScripts4InitEv
			CPatch::PatchPointer(0x468DAF + 1, &((CMissionCleanupEntry*)CTheScripts__MissionCleanUp.ptr)->handle);	// mov     eax, offset _ZN11CTheScripts14MissionCleanUpE.objects.handle	; _ZN11CTheScripts4InitEv
			CPatch::PatchPointer(0x46946C + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_469390
			CPatch::PatchPointer(0x46951A + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_469390
			CPatch::PatchPointer(0x469550 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_469390
			CPatch::PatchPointer(0x469575 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_469390
			CPatch::PatchPointer(0x4698B1 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_469390
			CPatch::PatchPointer(0x469911 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_469390
			CPatch::PatchPointer(0x469DAF + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_469390
			CPatch::PatchPointer(0x46A053 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_46A000
			CPatch::PatchPointer(0x46E324 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_46D050
			CPatch::PatchPointer(0x46EC91 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_46D050
			CPatch::PatchPointer(0x472A21 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_472310
			CPatch::PatchPointer(0x472AAE + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_472310
			CPatch::PatchPointer(0x474BB0 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_474900
			CPatch::PatchPointer(0x475B72 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_474D49
			CPatch::PatchPointer(0x4786C5 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_478000
			CPatch::PatchPointer(0x4787D8 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_478000
			CPatch::PatchPointer(0x47916B + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_478000
			CPatch::PatchPointer(0x47D7C1 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_47D210
			CPatch::PatchPointer(0x47D7F3 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_47D210
			CPatch::PatchPointer(0x47D825 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_47D210
			CPatch::PatchPointer(0x47D9EB + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_47D210
			CPatch::PatchPointer(0x47F624 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_47F370
			CPatch::PatchPointer(0x4804E7 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_47FA30
			CPatch::PatchPointer(0x4815F3 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_481300
			CPatch::PatchPointer(0x482B3E + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_481300
			CPatch::PatchPointer(0x48351C + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_481300
			CPatch::PatchPointer(0x4841AA + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_483BD0
			CPatch::PatchPointer(0x4841D2 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_483BD0
			CPatch::PatchPointer(0x48C9E3 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_48B590
			CPatch::PatchPointer(0x48D80A + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_48CDD0
			CPatch::PatchPointer(0x49151C + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_490DB0
			CPatch::PatchPointer(0x4918D4 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_490DB0
			CPatch::PatchPointer(0x491AAB + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_490DB0
			CPatch::PatchPointer(0x491C19 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_490DB0
			CPatch::PatchPointer(0x491C6E + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_490DB0
			CPatch::PatchPointer(0x491FBB + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_490DB0
			CPatch::PatchPointer(0x4922C7 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_490DB0
			CPatch::PatchPointer(0x492769 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_490DB0
			CPatch::PatchPointer(0x4942EF + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_493FE0
			CPatch::PatchPointer(0x4943F1 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_493FE0
			CPatch::PatchPointer(0x4947B8 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_493FE0
			CPatch::PatchPointer(0x494DAC + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_49485A
			CPatch::PatchPointer(0x497359 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_496E00
			CPatch::PatchPointer(0x4974EB + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_496E00
			CPatch::PatchPointer(0x49754C + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_496E00
			CPatch::PatchPointer(0x497F40 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_496E00
			CPatch::PatchPointer(0x64CF09 + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_64CEA0
			CPatch::PatchPointer(0x64D1BB + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_64CF40
			CPatch::PatchPointer(0x84A720 + 1, &((CMissionCleanupEntry*)CTheScripts__MissionCleanUp.ptr)->handle);	// mov     eax, offset _ZN11CTheScripts14MissionCleanUpE.objects.handle	; sub_84A720
			CPatch::PatchPointer(0x15621BF + 1, CTheScripts__MissionCleanUp.ptr);	// mov     ecx, offset _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp	; sub_1562160
		}
		#endif

		// Patch offset_CMissionCleanup_count
		#if TRUE
		{
			CPatch::PatchUINT32(0x405349 + 2, offset_CMissionCleanup_count);	// cmp     esi, 258h	; sub_405175
			CPatch::PatchUINT32(0x410A21 + 2, offset_CMissionCleanup_count);	// cmp     esi, 258h	; sub_410865
			CPatch::PatchUINT32(0x4637A4 + 2, offset_CMissionCleanup_count);	// mov     [eax+258h], dl	; 
			CPatch::PatchUINT32(0x1565D63 + 2, offset_CMissionCleanup_count);	// inc     byte ptr [ecx+258h]	; sub_1565D40
			CPatch::PatchUINT32(0x156E8D3 + 2, offset_CMissionCleanup_count);	// dec     byte ptr [ebp+258h]	; sub_156E810
		}
		#endif

		// Set variable for automatic patch
		CCodeMover::SetVariable("NUMBER_OF_MISSION_CLEANUP_ELEMENTS", ms_iMissionCleanupLimit);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 7
			CCodeMover::FixOnAddress(0x4637AA, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_MISSION_CLEANUP_ELEMENTS\x00\x00", 0x4637AF);	// line 1, 0x4637A0 - sub_4637A0 : mov     ecx, 4Bh
			CCodeMover::FixOnAddress(0x4637CD, 6, "\x01\x03\x66\x81\xfa\x05\x02NUMBER_OF_MISSION_CLEANUP_ELEMENTS\x00\x01\x02\x0F\x82\x03\xc4\x37\x46\x00\x00", 0x4637D3);	// line 2, 0x4637C0 - sub_4637C0 : cmp     dx, 75
			CCodeMover::FixOnAddress(0x468A99, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_MISSION_CLEANUP_ELEMENTS\x00\x00", 0x468A9E);	// line 3, 0x468560 - sub_468560 : mov     ebp, 75
			CCodeMover::FixOnAddress(0x468DB4, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_MISSION_CLEANUP_ELEMENTS\x00\x00", 0x468DB9);	// line 4, 0x468D50 - _ZN11CTheScripts4InitEv : mov     ecx, 4Bh
			CCodeMover::FixOnAddress(0x84A725, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_MISSION_CLEANUP_ELEMENTS\x00\x00", 0x84A72A);	// line 5, 0x84A720 - sub_84A720 : mov     ecx, 4Bh			
			CCodeMover::FixOnAddress(0x1565D4D, 6, "\x01\x03\x66\x81\xfa\x05\x02NUMBER_OF_MISSION_CLEANUP_ELEMENTS\x00\x01\x02\x0F\x82\x03\x44\x5d\x56\x01\x00", 0x1565D53);	// line 7, 0x1565D40 - sub_1565D40 : cmp     dx, 4Bh
		}
		#endif

		// Delete variable of automatic patch
		CCodeMover::DeleteVariable("NUMBER_OF_MISSION_CLEANUP_ELEMENTS");
		#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
		else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		{
			// Patch pointers
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x677318), CTheScripts__MissionCleanUp.ptr);	// DCD _ZN11CTheScripts14MissionCleanUpE; CTheScripts::MissionCleanUp

			CPatch::RedirectMethod((uintptr_t)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN15CMissionCleanup4InitEv"
			), &CMissionCleanup::Init);

			CPatch::RedirectMethod((uintptr_t)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN15CMissionCleanupC2Ev"
			), &CMissionCleanup::Constructor);

			// Changes
			Address_GTA_SA_2_00_sub_1A3750_1A37AE = g_mCalc.GetCurrentVAbyPreferedVA(0x1A37AE);
			Address_GTA_SA_2_00_sub_1A3750_1A37AC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1A37AC));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x1A37A4),
				(void*)&patch_GTA_SA_2_00_sub_1A3750_1A37A4, 8
			);

			Address_GTA_SA_2_00_sub_1A3750_1A37AE_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1A37AE));
			Address_GTA_SA_2_00_sub_1A3750_1A37C0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1A37C0));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x1A37B8),
				(void*)&patch_GTA_SA_2_00_sub_1A3750_1A37B8, 8
			);

			Address_GTA_SA_2_00_CColStore__LoadCollision_2E29E4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2E29E4));
			Address_GTA_SA_2_00_CColStore__LoadCollision_2E2AA2_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2E2AA2));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2E2A98),
				(void*)&patch_GTA_SA_2_00_CColStore__LoadCollision_2E2A98, 10
			);

			Address_GTA_SA_2_00_CMissionCleanup__FindFree_327352_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x327352));
			Address_GTA_SA_2_00_CMissionCleanup__FindFree_327368_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x327368));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x327360),
				(void*)&patch_GTA_SA_2_00_CMissionCleanup__FindFree_327360, 8
			);

			Address_GTA_SA_2_00_CMissionCleanup__CheckIfCollisionHasLoadedForMissionObjects_327398_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x327398));
			Address_GTA_SA_2_00_CMissionCleanup__CheckIfCollisionHasLoadedForMissionObjects_3274FA_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3274FA));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3274EE),
				(void*)&patch_GTA_SA_2_00_CMissionCleanup__CheckIfCollisionHasLoadedForMissionObjects_3274EE, 12
			);

			Address_GTA_SA_2_00_CMissionCleanup__AddEntityToList_327528_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x327528));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32751E),
				(void*)&patch_GTA_SA_2_00_CMissionCleanup__AddEntityToList_32751E, 10
			);

			Address_GTA_SA_2_00_CMissionCleanup__AddEntityToList_32754A_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32754A));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x327534),
				(void*)&patch_GTA_SA_2_00_CMissionCleanup__AddEntityToList_327534, 22
			);

			Address_GTA_SA_2_00_CMissionCleanup__RemoveEntityFromList_327642_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x327642));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x327638),
				(void*)&patch_GTA_SA_2_00_CMissionCleanup__RemoveEntityFromList_327638, 10
			);

			Address_GTA_SA_2_00_CMissionCleanup__RemoveEntityFromList_327582_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x327582));
			Address_GTA_SA_2_00_CMissionCleanup__RemoveEntityFromList_327656_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x327656));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32764C),
				(void*)&patch_GTA_SA_2_00_CMissionCleanup__RemoveEntityFromList_32764C, 10
			);

			Address_GTA_SA_2_00_CMissionCleanup__Process_327D18_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x327D18));
			Address_GTA_SA_2_00_CMissionCleanup__Process_327EC8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x327EC8));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x327EBE),
				(void*)&patch_GTA_SA_2_00_CMissionCleanup__Process_327EBE, 10
			);

			Address_GTA_SA_2_00_CTheScripts__Init_329FC0 = g_mCalc.GetCurrentVAbyPreferedVA(0x329FC0);
			Address_GTA_SA_2_00_CTheScripts__Init_329FC0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x329FC0));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x329FB8),
				(void*)&patch_GTA_SA_2_00_CTheScripts__Init_329FB8, 8
			);

			Address_GTA_SA_2_00_CTheScripts__Init_329FD4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x329FD4));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x329FCA),
				(void*)&patch_GTA_SA_2_00_CTheScripts__Init_329FCA, 10
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32CCF8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32CCF8));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32CCEE),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32CCEE, 10
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32CC96_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32CC96));
			Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32CD08_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32CD08));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32CD00),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32CD00, 8
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D190_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32D190));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32D186),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D186, 10
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D12E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32D12E));
			Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D1A0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32D1A0));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32D198),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D198, 8
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D726_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32D726));
			Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D42E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32D42E));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32D730),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D730, 8
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D752_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32D752));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32D748),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands100To199_32D748, 10
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DC60_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32DC60));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32DC56),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DC56, 10
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DC6C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32DC6C));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32DC64),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DC64, 8
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DF68_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32DF68));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32DF5E),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DF5E, 10
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DF02_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32DF02));
			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DF78_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32DF78));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32DF70),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32DF70, 8
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E41C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32E41C));
			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E42C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32E42C));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32E424),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E424, 8
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E54A_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32E54A));
			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E62A_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32E62A));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32E554),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E554, 8
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E576_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32E576));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32E56C),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E56C, 10
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5B0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32E5B0));
			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5C0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32E5C0));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32E5B8),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5B8, 8
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5E8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32E5E8));
			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5F8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32E5F8));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32E5F0),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E5F0, 8
			);

			Address_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E618_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32E618));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32E60E),
				(void*)&patch_GTA_SA_2_00_CRunningScript__ProcessCommands200To299_32E60E, 10
			);
		}
		#endif
	}
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CPatch::LeaveThisLevel();
	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of SCM LIMITS: Mission cleanup to: %d",
		ms_iMissionCleanupLimit
		);
	CGenericLogStorage::WriteLineSeparator();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_CTheScripts__ReadObjectNamesFromScript_156F5C4()
	{
		__asm
		{
			mov edi, ASM_ACCESS_LIMIT_VAR_32_BIT(g_SCMlimits, SCMlimits, CTheScripts__UsedObjectArray);
			add edi, CScriptRequestedModel::dwModelIndex;

			// go back
			push 0x156F5E5;
			retn;
		}
	}
}
#endif

extern "C"
{
	uint32_t UsedObjectArrayLimit;

	#ifdef IS_PLATFORM_ANDROID_ARM32
	// patch for 0x32A180
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CTheScripts__Init_32A188_thumb = 0;	// loc_32A188
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTheScripts__Init_32A180()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, UsedObjectArrayLimit)
			"STR R3, [R5]\n"
			"STR R6, [R2]\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__Init_32A188_thumb)
			);
	}
	#endif
}

// Patches used object array limit
void SCMlimits::PatchUsedObjectArrayLimit()
{
	if (!this->ms_bUsedObjectArrayLimitSet)
		return;

	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if (CPatch::IsDebugModeActive())
			this->ms_iUsedObjectArrayLimit = 395;
		else if (this->ms_iUsedObjectArrayLimit > 395)
		{
			this->CTheScripts__UsedObjectArray.gta_sa = new CScriptRequestedModel[this->ms_iUsedObjectArrayLimit];

			memset(
				this->CTheScripts__UsedObjectArray.gta_sa,
				NULL,
				this->ms_iUsedObjectArrayLimit * sizeof(CScriptRequestedModel)
				);

			this->CTheScripts__UsedObjectArray.bIsAllocated.Set(true);
		}

		UsedObjectArrayLimit = this->ms_iUsedObjectArrayLimit;

		MAKE_DEAD_IF();
		#ifdef IS_PLATFORM_WIN_X86
		else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		{
			// Patch pointers
			#if TRUE
			{
				CPatch::PatchPointer(0x468F18 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; _ZN11CTheScripts4InitEv
				CPatch::PatchPointer(0x468F31 + 2, &CTheScripts__UsedObjectArray.gta_sa[ms_iUsedObjectArrayLimit].dwModelIndex);	// cmp     edx, offset unk_A476BC	; _ZN11CTheScripts4InitEv
				CPatch::PatchPointer(0x469784 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     ecx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_469390
				CPatch::PatchPointer(0x46D5C3 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     ecx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_46D050
				CPatch::PatchPointer(0x471F57 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_470A90
				CPatch::PatchPointer(0x47279B + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_472310
				CPatch::PatchPointer(0x472947 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     ecx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_472310
				CPatch::PatchPointer(0x472CE3 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_472310
				CPatch::PatchPointer(0x474CE0 + 2, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     ebp, ds:_ZN11CTheScripts15UsedObjectArrayE.dwModelIndex[ecx]	; sub_474900
				CPatch::PatchPointer(0x475C17 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_474D49
				CPatch::PatchPointer(0x476964 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     ecx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; _opcode_handler_23
				CPatch::PatchPointer(0x476DCA + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; _opcode_handler_23
				CPatch::PatchPointer(0x478A80 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     ecx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_478000
				CPatch::PatchPointer(0x47A20D + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_479DA0
				CPatch::PatchPointer(0x47AA28 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_47A760
				CPatch::PatchPointer(0x47E590 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_47E090
				CPatch::PatchPointer(0x47EFA6 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_47E090
				CPatch::PatchPointer(0x47EFF3 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     ecx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_47E090
				CPatch::PatchPointer(0x47F054 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     ecx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_47E090
				CPatch::PatchPointer(0x47F506 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     ecx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_47F370
				CPatch::PatchPointer(0x481690 + 2, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edi, ds:_ZN11CTheScripts15UsedObjectArrayE.dwModelIndex[edi]	; sub_481300
				CPatch::PatchPointer(0x482FF4 + 2, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     esi, ds:_ZN11CTheScripts15UsedObjectArrayE.dwModelIndex[esi]	; sub_481300
				CPatch::PatchPointer(0x48488C + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     ecx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_483BD0
				CPatch::PatchPointer(0x4848A5 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_483BD0
				CPatch::PatchPointer(0x49839D + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_496E00
				CPatch::PatchPointer(0x4985CE + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     ecx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_496E00
				CPatch::PatchPointer(0x49860C + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     ecx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_496E00
				CPatch::PatchPointer(0x498639 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     edx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_496E00
				CPatch::PatchPointer(0x498669 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     ecx, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_496E00
				CPatch::PatchPointer(0x4986A3 + 1, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// mov     eax, offset _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex	; sub_496E00
				CPatch::PatchPointer(0x1562676 + 2, &CTheScripts__UsedObjectArray.gta_sa->dwModelIndex);	// lea     ecx, _ZN11CTheScripts15UsedObjectArrayE.dwModelIndex[eax]	; sub_1562660
				CPatch::PatchPointer(0x156267D + 2, CTheScripts__UsedObjectArray.gta_sa);	// lea     eax, _ZN11CTheScripts15UsedObjectArrayE.szModelName[eax]; CTheScripts::UsedObjectArray	; sub_1562660
			}
			#endif

			CPatch::RedirectCode(0x156F5C4, &patch_CTheScripts__ReadObjectNamesFromScript_156F5C4);
		}
		#elif defined(IS_PLATFORM_ANDROID_ARM32)
		else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		{
			// Patch pointers
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x679FBC), CTheScripts__UsedObjectArray.gta_sa);	// DCD _ZN11CTheScripts15UsedObjectArrayE; CTheScripts::UsedObjectArray

			// Changes
			Address_GTA_SA_2_00_CTheScripts__Init_32A188_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32A188));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32A180),
				(void*)&patch_GTA_SA_2_00_CTheScripts__Init_32A180
			);
		}
		#endif
	}
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of SCM LIMITS: Max number of used objects to: %d",
		this->ms_iUsedObjectArrayLimit
		);
	CGenericLogStorage::WriteLineSeparator();
}


// Patches switch jump table limit
void SCMlimits::PatchSwitchJumpTableLimit()
{
	if (!this->ms_bScriptJumpTableLimitSet)
		return;

	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if (CPatch::IsDebugModeActive())
			this->ms_iScriptJumpTableLimit = 75;
		else if (this->ms_iScriptJumpTableLimit > 75)
		{
			this->CTheScripts__SwitchJumpTable.gta_sa = new tScriptSwitchCase[this->ms_iScriptJumpTableLimit];
			this->CTheScripts__SwitchJumpTable.bIsAllocated.Set(true);
		}

		MAKE_DEAD_IF();
		#ifdef IS_PLATFORM_WIN_X86
		else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		{
			// Patch pointers
			#if TRUE
			{
				CPatch::PatchPointer(0x4703A1 + 2, CTheScripts__SwitchJumpTable.gta_sa);	// mov     dword ptr ds:_ZN11CTheScripts15SwitchJumpTableE.when[eax], edx; CTheScripts::SwitchJumpTable	; sub_470390
				CPatch::PatchPointer(0x4703AD + 2, &CTheScripts__SwitchJumpTable.gta_sa->then);	// mov     ds:_ZN11CTheScripts15SwitchJumpTableE.then[eax], edx	; sub_470390
				CPatch::PatchPointer(0x1561BBB + 3, CTheScripts__SwitchJumpTable.gta_sa);	// mov     ecx, ds:_ZN11CTheScripts15SwitchJumpTableE.when[ecx*8]; CTheScripts::SwitchJumpTable	; sub_1561B80
				CPatch::PatchPointer(0x1561BD5 + 3, &CTheScripts__SwitchJumpTable.gta_sa->then);	// mov     eax, ds:_ZN11CTheScripts15SwitchJumpTableE.then[edx*8]	; sub_1561B80
				CPatch::PatchPointer(0x1561BE4 + 2, CTheScripts__SwitchJumpTable.gta_sa);	// cmp     esi, dword ptr ds:_ZN11CTheScripts15SwitchJumpTableE.when[eax]; CTheScripts::SwitchJumpTable	; sub_1561B80
				CPatch::PatchPointer(0x1561BEC + 2, &CTheScripts__SwitchJumpTable.gta_sa->then);	// mov     ecx, ds:_ZN11CTheScripts15SwitchJumpTableE.then[eax]	; sub_1561B80
				CPatch::PatchPointer(0x1561BFE + 2, CTheScripts__SwitchJumpTable.gta_sa);	// cmp     esi, dword ptr ds:_ZN11CTheScripts15SwitchJumpTableE.when[eax]; CTheScripts::SwitchJumpTable	; sub_1561B80
				CPatch::PatchPointer(0x1561C06 + 2, &CTheScripts__SwitchJumpTable.gta_sa->then);	// mov     edx, ds:_ZN11CTheScripts15SwitchJumpTableE.then[eax]	; sub_1561B80
			}
			#endif
		}
		#elif defined(IS_PLATFORM_ANDROID_ARM32)
		else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		{
			// Patch pointer
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x676660), CTheScripts__SwitchJumpTable.gta_sa);	// DCD _ZN11CTheScripts15SwitchJumpTableE; CTheScripts::SwitchJumpTable
		}
		#endif
	}
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of SCM LIMITS: Switch jump table cases to: %d",
		this->ms_iUsedObjectArrayLimit
		);
	CGenericLogStorage::WriteLineSeparator();
}

namespace Game_GTASA
{
	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CScriptsForBrains__AddNewScriptBrain_46A931()
	{
		__asm
		{
			xor edx, edx;

		ourLoop:
			mov eax, edx;
			lea     eax, [eax + eax * 4];
			cmp     word ptr[ecx + eax * 4], 0FFFFh;
			je success;
			
			inc edx;
			cmp edx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_SCMlimits, SCMlimits, ms_iScriptsForBrainsLimit);
			jb ourLoop;

			push 0x46A9AF;
			retn;

		success:
			push 0x46A955;
			retn;
		}
	}

	NAKED void patch_CScriptsForBrains__CheckIfNewEntityNeedsScript_46FF30()
	{
		__asm
		{
			xor ecx, ecx;
			test bl, bl;
			mov[esp + 14h - 4], ecx;

			push 0x46FF38;
			retn;
		}
	}

	NAKED void patch_CScriptsForBrains__CheckIfNewEntityNeedsScript_46FFD0()
	{
		__asm
		{
			mov     ecx, [esp + 18h - 4];
			inc ecx;
			cmp ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_SCMlimits, SCMlimits, ms_iScriptsForBrainsLimit);
			mov[esp + 18h - 4], ecx;

			push 0x46FFDD;
			retn;
		}
	}
	#endif
}

// Patches the scripts for brains limit
void SCMlimits::PatchScriptsForBrainsLimit()
{
	if (!this->ms_bScriptsForBrainsLimitSet)
		return;

	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (CPatch::IsDebugModeActive())
			this->ms_iScriptsForBrainsLimit = 70;
		else if (this->ms_iScriptsForBrainsLimit > 70)
		{
			this->CTheScripts__ScriptsForBrains.gta_sa = new CScriptTrigger[this->ms_iScriptsForBrainsLimit];
			this->CTheScripts__ScriptsForBrains.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x468DF9 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; this	; _ZN11CTheScripts4InitEv
			CPatch::PatchPointer(0x46CF61 + 3, &CTheScripts__ScriptsForBrains.gta_sa->AttachType);	// mov     al, _ZN11CTheScripts16ScriptsForBrainsE.AttachType[eax*4]	; _ZN11CTheScripts33ProcessWaitingForScriptBrainArrayEv
			CPatch::PatchPointer(0x46CFAB + 4, &CTheScripts__ScriptsForBrains.gta_sa->SCM_script_index);	// movsx   eax, _ZN11CTheScripts16ScriptsForBrainsE.SCM_script_index[eax*4]; CTheScripts::ScriptsForBrains	; _ZN11CTheScripts33ProcessWaitingForScriptBrainArrayEv
			CPatch::PatchPointer(0x46CFC8 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _ZN11CTheScripts33ProcessWaitingForScriptBrainArrayEv
			CPatch::PatchPointer(0x46D000 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; this	; _ZN11CTheScripts33ProcessWaitingForScriptBrainArrayEv
			CPatch::PatchPointer(0x46D01F + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _ZN11CTheScripts33ProcessWaitingForScriptBrainArrayEv
			CPatch::PatchPointer(0x471CD7 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _opcode_handler_21
			CPatch::PatchPointer(0x4723B4 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _opcode_handler_20
			CPatch::PatchPointer(0x476D7C + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _opcode_handler_23
			CPatch::PatchPointer(0x476DF1 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _opcode_handler_23
			CPatch::PatchPointer(0x478734 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; this	; _opcode_handler_24
			CPatch::PatchPointer(0x47A5B0 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _opcode_handler_26
			CPatch::PatchPointer(0x5337FC + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _ZN7CEntity13CreateEffectsEv
			CPatch::PatchPointer(0x533C41 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _ZN7CEntity14DestroyEffectsEv
			CPatch::PatchPointer(0x59678E + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _ZN15InteriorGroup_c14SetupHousePedsEv
			CPatch::PatchPointer(0x59EAF2 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _ZN12CDummyObject12CreateObjectEv
			CPatch::PatchPointer(0x59F6A4 + 4, &CTheScripts__ScriptsForBrains.gta_sa->SCM_script_index);	// movsx   eax, _ZN11CTheScripts16ScriptsForBrainsE.SCM_script_index[eax*4]; CTheScripts::ScriptsForBrains	; ??1CObject@@UAE@XZ
			CPatch::PatchPointer(0x5D4CBF + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     esi, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _ZN11CTheScripts4SaveEv
			CPatch::PatchPointer(0x5D504D + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     esi, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _ZN11CTheScripts4LoadEv
			CPatch::PatchPointer(0x5E866D + 4, &CTheScripts__ScriptsForBrains.gta_sa->SCM_script_index);	// movsx   eax, _ZN11CTheScripts16ScriptsForBrainsE.SCM_script_index[eax*4]; CTheScripts::ScriptsForBrains	; ??1CPed@@UAE@XZ
			CPatch::PatchPointer(0x615907 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _ZN11CPopulation15AddToPopulationEffff
			CPatch::PatchPointer(0x638769 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; this	; CTaskComplexUseAttractor__m24
			CPatch::PatchPointer(0x6387B4 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; CTaskComplexUseAttractor__m24
			CPatch::PatchPointer(0x6F3D71 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; CTheScripts::ScriptsForBrains	; _ZN13CCarGenerator20DoInternalProcessingEv
			CPatch::PatchPointer(0x84A740 + 1, CTheScripts__ScriptsForBrains.gta_sa);	// mov     ecx, offset _ZN11CTheScripts16ScriptsForBrainsE; this	; unknown_libname_128
		}
		#endif

		// CScriptsForBrains::Init
		if(gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
			CPatch::PatchUINT32(0x46A8C8 + 1, ms_iScriptsForBrainsLimit);
		else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			CPatch::PatchUINT32(0x156BB78 + 1, ms_iScriptsForBrainsLimit);

		// CScriptsForBrains::AddNewScriptBrain
		CPatch::RedirectCode(0x46A931, &patch_CScriptsForBrains__AddNewScriptBrain_46A931);
	
		// CScriptsForBrains::CheckIfNewEntityNeedsScript
		{
			bool oldDebugLevel = CPatch::GetPointerToSettings()->bDebugEnabled;
			CPatch::GetPointerToSettings()->bDebugEnabled = false;

			CPatch::RedirectCode(0x46FF30, &patch_CScriptsForBrains__CheckIfNewEntityNeedsScript_46FF30);
			CPatch::PatchMemoryData(0x46FF78, "\x8B\xC1\x90", 3);
			CPatch::RedirectCode(0x46FFD0, &patch_CScriptsForBrains__CheckIfNewEntityNeedsScript_46FFD0);

			CPatch::GetPointerToSettings()->bDebugEnabled = oldDebugLevel;
		}

		// Set variable for automatic patch
		CCodeMover::SetVariable("NUMBER_OF_SCRIPTS_FOR_BRAINS", ms_iScriptsForBrainsLimit);

		// Apply automatic patch
		#if TRUE
		{
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
				CCodeMover::FixOnAddressRel(0x46AA63, 6, "\x01\x03\x66\x81\xfe\x05\x02""NUMBER_OF_SCRIPTS_FOR_BRAINS\x00\x01\x02\x0F\x82\x15\x40\xaa\x06\x00\x00", 0x46AA69);	// line 1, 0x46AA30 - _ZN17CScriptsForBrains33GetIndexOfScriptBrainWithThisNameEPKca : cmp     si, 70
			else if(gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
				CCodeMover::FixOnAddressRel(0x1569133, 6, "\x01\x03\x66\x81\xfe\x05\x02""NUMBER_OF_SCRIPTS_FOR_BRAINS\x00\x01\x02\x0F\x82\x15\x10\x91\x16\x01\x00", 0x1569139);	// line 1, 0x46AA30 - _ZN17CScriptsForBrains33GetIndexOfScriptBrainWithThisNameEPKca : cmp     si, 70
		}
		#endif

		// Delete variable of automatic patch
		CCodeMover::DeleteVariable("NUMBER_OF_SCRIPTS_FOR_BRAINS");
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of SCM LIMITS: Scripts for brains to: %d",
		this->ms_iScriptsForBrainsLimit
	);
	CGenericLogStorage::WriteLineSeparator();
}

// Initialize
void SCMlimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	this->ms_bMissionCleanUpLimitSet = false;
	this->ms_bScriptsArrayLimitSet = false;
	this->ms_bScriptJumpTableLimitSet = false;
	this->ms_bUsedObjectArrayLimitSet = false;
	this->ms_bScriptsForBrainsLimitSet = false;

	MAKE_DEAD_IF();
	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		using namespace Game_GTASA;

		// Script space
		if(CGameVersion::Is_GTA_SA_Android_Renderware(gameVersion) || CGameVersion::IsAny_GTA_SA_UnrealEngine(gameVersion))
			this->defaultMAINsegmentSize = 270000;
		else
			this->defaultMAINsegmentSize = 200000;

		this->defaultMissionSize = 69000;
		
		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
				this->CTheScripts__ScriptSpace.ptr = (uint8_t*)0xA49960;
			#elif defined(IS_PLATFORM_ANDROID_ARM32)
			this->CTheScripts__ScriptSpace.ptr = (uint8_t*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN11CTheScripts11ScriptSpaceE"
			);
			#else
			;
			#endif



		// Mission cleanup
		this->ms_iMissionCleanupLimit = 75;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
				this->CTheScripts__MissionCleanUp.ptr = (void*)0xA90850;
			#elif defined(IS_PLATFORM_ANDROID_ARM32)
			this->CTheScripts__MissionCleanUp.ptr = (void*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN11CTheScripts14MissionCleanUpE"
			);
			#else
			;
			#endif

		// Scripts array	
		this->ms_iScriptsArrayLimit = 96;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
				this->CTheScripts__ScriptsArray.array.SetArrayPtr((CRunningScript*)0xA8B430);
			#elif defined(IS_PLATFORM_ANDROID_ARM32)
			this->CTheScripts__ScriptsArray.array.SetArrayPtr((CRunningScript*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN11CTheScripts12ScriptsArrayE"
			));
			#else
			;
			#endif

		// Used object array	
		this->ms_iUsedObjectArrayLimit = 395;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
				this->CTheScripts__UsedObjectArray.gta_sa = (CScriptRequestedModel*)0xA44B70;	
			#elif defined(IS_PLATFORM_ANDROID_ARM32)
			this->CTheScripts__UsedObjectArray.gta_sa = (CScriptRequestedModel*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN11CTheScripts15UsedObjectArrayE"
			);
			#else
			;
			#endif

		// Script jump table array	
		this->ms_iScriptJumpTableLimit = 75;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
				this->CTheScripts__SwitchJumpTable.gta_sa = (tScriptSwitchCase*)0xA43CF8;
			#elif defined(IS_PLATFORM_ANDROID_ARM32)
			this->CTheScripts__SwitchJumpTable.gta_sa = (tScriptSwitchCase*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN11CTheScripts15SwitchJumpTableE"
			);
			#else
			;
			#endif
		

		// Scripts for brains
		this->ms_iScriptsForBrainsLimit = 70;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
				this->CTheScripts__ScriptsForBrains.gta_sa = (CScriptsForBrains*)0xA90CF0;
			#elif defined(IS_PLATFORM_ANDROID_ARM32)
			this->CTheScripts__ScriptsForBrains.gta_sa = (CScriptsForBrains*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN11CTheScripts16ScriptsForBrainsE"
			);
			#else
			;
			#endif
	}

	this->iMAINsegmentSize = this->defaultMAINsegmentSize;
	this->iMissionSize = this->defaultMissionSize;
}

// Shutdown
void SCMlimits::Shutdown()
{
	MAKE_VAR_GAME_VERSION();

	if (CTheScripts__ScriptSpace.bIsAllocated.Get())
		delete[] CTheScripts__ScriptSpace.ptr;

	if (CTheScripts__MissionCleanUp.bIsAllocated.Get())
		delete[] CTheScripts__MissionCleanUp.ptr;

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		if (CTheScripts__ScriptsArray.bIsAllocated.Get())
			delete[] CTheScripts__ScriptsArray.array.GetArrayPointer();

		if (CTheScripts__UsedObjectArray.bIsAllocated.Get())
			delete[] CTheScripts__UsedObjectArray.gta_sa;

		if (CTheScripts__SwitchJumpTable.bIsAllocated.Get())
			delete[] CTheScripts__SwitchJumpTable.gta_sa;

		if (CTheScripts__ScriptsForBrains.bIsAllocated.Get())
			delete[] CTheScripts__ScriptsForBrains.gta_sa;
	}
}
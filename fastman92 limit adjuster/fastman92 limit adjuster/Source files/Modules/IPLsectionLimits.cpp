/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "IPLsectionLimits.h"

#include "../Core/CCodeMover.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/CGenericGameStorage.h"
#include "../GameStructures/Rockstar Games/ePedType.h"

#include "../Modules/SaveOfVariableLength.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

#pragma warning(disable:4305)
#pragma warning(disable:4267)

using namespace Game;

IPLsectionLimits g_IPLsectionlimits;

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
extern uintptr_t Address_CPools__Initialise_18E9A8_arm;

uintptr_t IPL_section_limits_address_operator_new_array = 0;

namespace Game_GTASA
{
	extern "C"
	{
		uintptr_t Address_CPools__Initialise_goBack_Buildings = 0;
	}

	static TARGET_THUMB NAKED void CPools__Initialise_40CAD4()
	{
		__asm volatile(
		".thumb\n"
		ASM_LOAD_ADDRESS_OF_SYMBOL(R0, g_IPLsectionlimits)
		"LDR R0, [R0, #%c[offset_BuildingsLimit]]\n"

		// R0 *= 60, size of CBuilding
		"RSB           R0, R0, R0,LSL#4\n"	// *= 15
		"LSLS            R0, R0, #2\n" // * 4

		ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(IPL_section_limits_address_operator_new_array)

		"STR             R0, [R4]\n"

		ASM_LOAD_ADDRESS_OF_SYMBOL(R0, g_IPLsectionlimits)
		"LDR R0, [R0, #%c[offset_BuildingsLimit]]\n"
		"MOV R5, R0\n"

		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPools__Initialise_goBack_Buildings)

		::[offset_BuildingsLimit]"i"(offsetof(IPLsectionLimits, BuildingsLimit))
			
			);
	}
}
#endif

// IPL : inst section
void IPLsectionLimits::SetIplBuildings(unsigned int iBuildings)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iBuildings = this->BuildingsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x55105E + 1, iBuildings);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xB1B485 + 1), iBuildings);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8DDDE5 + 1), iBuildings);
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
		CPatch::PatchUINT32(0x44D788 + 3, iBuildings);
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;
		Address_CPools__Initialise_goBack_Buildings = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x40CAEA));
		
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x40CAD4),
			(void*)&CPools__Initialise_40CAD4
			);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->BuildingsLimit = iBuildings;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IPL:inst, buildings to: %d", iBuildings);
	CGenericLogStorage::WriteLineSeparator();
}

// IPL : inst section, animated buildings
void IPLsectionLimits::SetIplAnimatedBuildings(unsigned int iAnimatedBuildings)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iAnimatedBuildings = this->AnimatedBuildingsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xC79638 + 1), iAnimatedBuildings);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xBA9AB8 + 1), iAnimatedBuildings);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->AnimatedBuildingsLimit = iAnimatedBuildings;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of IPL:inst, animated buildings to: %d",
		iAnimatedBuildings
	);

	CGenericLogStorage::WriteLineSeparator();	
}

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
namespace Game_GTASA
{
	extern "C"
	{
		uint32_t IplDummyLimit;
		uint32_t IplDummyLimitMultipliedBySizeofCDummy;
		int32_t MinusIplDummyLimitMinusTwo;
	}

	// patch for 0x40CBAE
	extern "C"
	{
		uintptr_t Address_CPools__Initialise_40CC18_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPools__Initialise_40CBAE()
	{
		__asm(
			".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, IplDummyLimitMultipliedBySizeofCDummy)

			"BL 1f\n"
			"STR R0, [R4]\n"

			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, IplDummyLimit)
			"MOV R5, R0\n"

			"BL 1f\n"
			"MOVS R1, #1\n"
			"MOVS R2, #0x80\n"
			"STRB R1, [R4,#0x10]\n"
			"MOV R1, #0xFFFF\n"
			"MOVT R1, #0xFFFF\n"
			"STRD R0, R5, [R4,#4]\n"
			"STR R1, [R4,#0xC]\n"
			"LDRB R1, [R0,#1]\n"
			"STRB R2, [R0]\n"
			"ORR R1, R1, #0x80\n"
			"STRB R1, [R0,#1]\n"
			"LDR R0, [R4,#4]\n"
			"LDRB R1, [R0,#1]\n"
			"AND R1, R1, #0x80\n"
			"STRB R1, [R0,#1]\n"

			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, MinusIplDummyLimitMinusTwo)
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R3, IplDummyLimit)

			// Loop
			"2:\n"
			"LDR R1, [R4,#4]\n"
			"ADD R1, R0\n"
			"LDRB R2, [R1,R3]\n"
			"ORR R2, R2, #0x80\n"
			"STRB R2, [R1,R3]\n"
			"LDR R1, [R4,#4]\n"
			"ADD R1, R0\n"
			"ADDS R0, #1\n"
			"LDRB R2, [R1,R3]\n"
			"AND R2, R2, #0x80\n"
			"STRB R2, [R1,R3]\n"
			"BNE 2b\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPools__Initialise_40CC18_thumb)

			// Branches
			"1:\n"	// _Znaj
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPools__Initialise_18E9A8_arm)
			);
	}
}
#endif

// IPL : inst section, dummies
void IPLsectionLimits::SetIplDummies(unsigned int iDummies)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iDummies = this->DummiesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x5510CE + 1, iDummies);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xB257B8 + 1), iDummies);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x900B58 + 1), iDummies);
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
		CPatch::PatchUINT32(0x44D70C + 3, iDummies);
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		// Set variables
		Game_GTASA::IplDummyLimit = iDummies;
		Game_GTASA::IplDummyLimitMultipliedBySizeofCDummy = iDummies * 0x3C;
		Game_GTASA::MinusIplDummyLimitMinusTwo = -((signed int)iDummies) + 2;

		// Changes
		Address_CPools__Initialise_18E9A8_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18E9A8));
		Address_CPools__Initialise_40CC18_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x40CC18));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x40CBAE),
			(void*)&patch_CPools__Initialise_40CBAE
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->DummiesLimit = iDummies;

	CPatch::LeaveThisLevel();
	
	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IPL:inst, dummies to: %d", iDummies);
	CGenericLogStorage::WriteLineSeparator();
}

// IPL: inst per file
void IPLsectionLimits::SetInstLimitPerFile(unsigned int iInstPerFile)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iInstPerFile = this->IPLentriesPerFileLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		if (iInstPerFile > this->IPLentriesPerFileLimit)
		{
			IPLentriesOfFile.ptr = new void*[iInstPerFile];
			IPLentriesOfFile.bIsAllocated.Set(true);
		}

		// Patch addresses
		#if TRUE
		{
			CPatch::PatchPointer(0x5B51F0 + 3, IPLentriesOfFile.ptr);		// mov     eax, ds:__iplInst[edx*4]
			CPatch::PatchPointer(0x5B51FF + 3, IPLentriesOfFile.ptr);		// mov     ecx, ds:__iplInst[ecx*4]
			CPatch::PatchPointer(0x5B524B + 1, IPLentriesOfFile.ptr);		// push    offset __iplInst
			CPatch::PatchPointer(0x5B5258 + 3, IPLentriesOfFile.ptr);		// mov     esi, ds:__iplInst[ebx*4]
			CPatch::PatchPointer(0x5B531C + 1, IPLentriesOfFile.ptr);		// push    offset __iplInst
			CPatch::PatchPointer(0x5B5340 + 3, IPLentriesOfFile.ptr);		// mov     edx, ds:__iplInst[esi*4]
			CPatch::PatchPointer(0x5B8938 + 3, IPLentriesOfFile.ptr);		// mov     ds:__iplInst[ecx*4], eax
			CPatch::PatchPointer(0x5B8A50 + 1, IPLentriesOfFile.ptr);		// mov     ecx, offset __iplInst
			CPatch::PatchPointer(0x5B8A50 + 1, IPLentriesOfFile.ptr);		// mov     ecx, offset __iplInst
			CPatch::PatchPointer(0x5B8A6F + 3, IPLentriesOfFile.ptr);		// lea     eax, __iplInst[edx*4]
		}
		#endif
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
	{
		// Patch count
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8D7BDC + 1), iInstPerFile * sizeof(void*));	// push    32768	; _ZN11CFileLoader9LoadSceneEPKc
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8D7152 + 1), iInstPerFile * sizeof(void*));	// push    8000h	; _ZN11CFileLoader15LoadSceneBinaryEPKc
		}
		#endif
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
		// Patch count
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xACC09C + 1), iInstPerFile * sizeof(void*));	// push    32768	; _ZN11CFileLoader9LoadSceneEPKc
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xACB612 + 1), iInstPerFile * sizeof(void*));	// push    8000h	; _ZN11CFileLoader15LoadSceneBinaryEPKc
		}
		#endif
	}	
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->IPLentriesPerFileLimit = iInstPerFile;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IPL: inst per file to: %d", iInstPerFile);
	CGenericLogStorage::WriteLineSeparator();
}

// IPL: entity index array (40)
void IPLsectionLimits::SetEntityIndexArray(unsigned int iEntityIndexArrayLimit)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iEntityIndexArrayLimit = this->IPLentityIndexArrayLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
	{
		if (iEntityIndexArrayLimit > this->IPLentityIndexArrayLimit)
		{
			IPLentityIndexArray.ptr = new void**[iEntityIndexArrayLimit];
			IPLentityIndexArray.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x404797 + 3, IPLentityIndexArray.ptr);	// mov     _iplInstBlocks[ecx*4], eax; _8E3F08[_8E3F00++] = new u32[_a0];	; _ZN9CIplStore25GetNewIplEntityIndexArrayEi
			CPatch::PatchPointer(0x4047B4 + 3, IPLentityIndexArray.ptr);	// mov     eax, _iplInstBlocks[eax*4]	; _ZN9CIplStore22GetIplEntityIndexArrayEi
			CPatch::PatchPointer(0x405C3A + 3, IPLentityIndexArray.ptr);	// mov     eax, _iplInstBlocks[edx*4]	; _ZN9CIplStore18LoadIplBoundingBoxEiPhi
			CPatch::PatchPointer(0x406030 + 3, IPLentityIndexArray.ptr);	// mov     edx, _iplInstBlocks[esi*4]	; _ZN9CIplStore8ShutdownEv
			CPatch::PatchPointer(0x406198 + 3, IPLentityIndexArray.ptr);	// mov     edx, _iplInstBlocks[ecx*4]	; _ZN9CIplStore7LoadIplEiPhi
		}
		#endif
	}
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
	{			
		if (iEntityIndexArrayLimit > this->IPLentityIndexArrayLimit)
		{
			IPLentityIndexArray.ptr = new void**[iEntityIndexArrayLimit];
			IPLentityIndexArray.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x405C3A + 3, IPLentityIndexArray.ptr);	// mov     eax, ds:dword_8E3F08[edx*4]	; sub_405C00
			CPatch::PatchPointer(0x406198 + 3, IPLentityIndexArray.ptr);	// mov     edx, ds:dword_8E3F08[ecx*4]	; loadIPLfromIMGarchive
			CPatch::PatchPointer(0x156115D + 3, IPLentityIndexArray.ptr);	// mov     edx, ds:dword_8E3F08[esi*4]	; sub_15610B0
			CPatch::PatchPointer(0x15649F7 + 3, IPLentityIndexArray.ptr);	// mov     ds:dword_8E3F08[ecx*4], eax	; sub_404780
			CPatch::PatchPointer(0x1569774 + 3, IPLentityIndexArray.ptr);	// mov     eax, ds:dword_8E3F08[eax*4]	; sub_1569770
		}
		#endif
	}
	else if(gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
	{
		if (iEntityIndexArrayLimit > this->IPLentityIndexArrayLimit)
		{
			IPLentityIndexArray.ptr = new void**[iEntityIndexArrayLimit];
			IPLentityIndexArray.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB25B5E + 3), IPLentityIndexArray.ptr);	// mov     _iplInstBlocks[ecx*4], eax	; sub_B25B50
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB25B8E + 3), IPLentityIndexArray.ptr);	// mov     _iplInstBlocks[ecx*4], eax	; sub_B25B50
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB25BB4 + 3), IPLentityIndexArray.ptr);	// mov     eax, _iplInstBlocks[eax*4]	; sub_B25BB0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB276A0 + 3), IPLentityIndexArray.ptr);	// mov     eax, _iplInstBlocks[esi*4]	; sub_B27690
		}
		#endif
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
		if (iEntityIndexArrayLimit > this->IPLentityIndexArrayLimit)
		{
			IPLentityIndexArray.ptr = new void**[iEntityIndexArrayLimit];
			IPLentityIndexArray.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA0A35E + 3), IPLentityIndexArray.ptr);	// mov     _iplInstBlocks[ecx*4], eax	; sub_A0A350
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA0A38E + 3), IPLentityIndexArray.ptr);	// mov     _iplInstBlocks[ecx*4], eax	; sub_A0A350
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA0A3B4 + 3), IPLentityIndexArray.ptr);	// mov     eax, _iplInstBlocks[eax*4]	; sub_A0A3B0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA0C080 + 3), IPLentityIndexArray.ptr);	// mov     eax, _iplInstBlocks[esi*4]	; sub_A0C070
		}
		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		if (iEntityIndexArrayLimit > this->IPLentityIndexArrayLimit)
		{
			IPLentityIndexArray.ptr = new void**[iEntityIndexArrayLimit];
			IPLentityIndexArray.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x2805E0), (char*)IPLentityIndexArray.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x280578));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x280C78), (char*)IPLentityIndexArray.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x2809F0));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x281080), (char*)IPLentityIndexArray.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x280CEA));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x2810C8), (char*)IPLentityIndexArray.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x2810C2));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x28208C), (char*)IPLentityIndexArray.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x28207A));
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	IPLentityIndexArrayLimit = iEntityIndexArrayLimit;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IPL: entity index array to: %d", iEntityIndexArrayLimit);
	CGenericLogStorage::WriteLineSeparator();
}

// IPL: map zones
void IPLsectionLimits::SetMapZones(unsigned int iMapZones)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iMapZones = this->MapZonesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		bool bShouldSaveBeEnhanced = false;

		if (iMapZones > this->MapZonesLimit)
		{
			CTheZones__MapZoneArray.gta_sa = new CZone[iMapZones];
			CTheZones__MapZoneArray.bIsAllocated.Set(true);

			bShouldSaveBeEnhanced = true;
		}		

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(0x57274C + 1, iMapZones);	// mov     ecx, 39
		}
		#endif

		// Map zone array
		#if TRUE
		{
			CPatch::PatchPointer(0x572313 + 1, CTheZones__MapZoneArray.gta_sa);	// mov     ebp, offset _ZN9CTheZones12MapZoneArrayE; CTheZones::MapZoneArray
			CPatch::PatchPointer(0x572326 + 1, CTheZones__MapZoneArray.gta_sa);	// add     eax, offset _ZN9CTheZones12MapZoneArrayE; CTheZones::MapZoneArray
			CPatch::PatchPointer(0x572350 + 1, CTheZones__MapZoneArray.gta_sa);	// add     eax, offset _ZN9CTheZones12MapZoneArrayE; CTheZones::MapZoneArray
			CPatch::PatchPointer(0x5725A8 + 1, CTheZones__MapZoneArray.gta_sa);	// add     eax, offset _ZN9CTheZones12MapZoneArrayE; CTheZones::MapZoneArray
			CPatch::PatchPointer(0x572747 + 1, &CTheZones__MapZoneArray.gta_sa->text);	// mov     eax, offset _ZN9CTheZones12MapZoneArrayE.text
			CPatch::PatchPointer(0x57279C + 3, &CTheZones__MapZoneArray.gta_sa->pos2.x);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.pos2.x, di
			CPatch::PatchPointer(0x5727A3 + 3, &CTheZones__MapZoneArray.gta_sa->pos2.y);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.pos2.y, di
			CPatch::PatchPointer(0x5727AB + 3, &CTheZones__MapZoneArray.gta_sa->name[4]);	// mov     word ptr ds:_ZN9CTheZones12MapZoneArrayE.name+4, si
			CPatch::PatchPointer(0x5727B2 + 3, &CTheZones__MapZoneArray.gta_sa->text[4]);	// mov     word ptr ds:_ZN9CTheZones12MapZoneArrayE.text+4, si
			CPatch::PatchPointer(0x5727BA + 3, &CTheZones__MapZoneArray.gta_sa->pos1.x);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.pos1.x, bp
			CPatch::PatchPointer(0x5727C1 + 3, &CTheZones__MapZoneArray.gta_sa->pos1.y);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.pos1.y, bp
			CPatch::PatchPointer(0x5727C9 + 2, &CTheZones__MapZoneArray.gta_sa->level);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.level, bl
			CPatch::PatchPointer(0x5727CF + 1, &CTheZones__MapZoneArray.gta_sa->name[0]);	// mov     dword ptr ds:_ZN9CTheZones12MapZoneArrayE.name, eax; CTheZones::MapZoneArray
			CPatch::PatchPointer(0x5727D4 + 2, &CTheZones__MapZoneArray.gta_sa->name[6]);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.name+6, cl
			CPatch::PatchPointer(0x5727DA + 1, &CTheZones__MapZoneArray.gta_sa->text[0]);	// mov     dword ptr ds:_ZN9CTheZones12MapZoneArrayE.text, eax
			CPatch::PatchPointer(0x5727DF + 2, &CTheZones__MapZoneArray.gta_sa->text[6]);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.text+6, cl
			CPatch::PatchPointer(0x5727E5 + 3, &CTheZones__MapZoneArray.gta_sa->pos1.z);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.pos1.z, 0F830h
			CPatch::PatchPointer(0x5727EE + 3, &CTheZones__MapZoneArray.gta_sa->pos2.z);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.pos2.z, 7D0h
			CPatch::PatchPointer(0x5729C7 + 2, &CTheZones__MapZoneArray.gta_sa->name);	// lea     edi, _ZN9CTheZones12MapZoneArrayE.name[edx]; CTheZones::MapZoneArray
			CPatch::PatchPointer(0x5729E4 + 2, &CTheZones__MapZoneArray.gta_sa->text);	// lea     edx, _ZN9CTheZones12MapZoneArrayE.text[ecx]
			CPatch::PatchPointer(0x5729FE + 2, &CTheZones__MapZoneArray.gta_sa->type);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.type[esi], 3
			CPatch::PatchPointer(0x572A0E + 3, &CTheZones__MapZoneArray.gta_sa->pos1.x);	// mov     word ptr ds:_ZN9CTheZones12MapZoneArrayE.pos1.x[esi], ax
			CPatch::PatchPointer(0x572A1E + 3, &CTheZones__MapZoneArray.gta_sa->pos1.y);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.pos1.y[esi], ax
			CPatch::PatchPointer(0x572A2E + 3, &CTheZones__MapZoneArray.gta_sa->pos1.z);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.pos1.z[esi], ax
			CPatch::PatchPointer(0x572A3E + 3, &CTheZones__MapZoneArray.gta_sa->pos2.x);	// mov     word ptr ds:_ZN9CTheZones12MapZoneArrayE.pos2.x[esi], ax
			CPatch::PatchPointer(0x572A4E + 3, &CTheZones__MapZoneArray.gta_sa->pos2.y);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.pos2.y[esi], ax
			CPatch::PatchPointer(0x572A61 + 3, &CTheZones__MapZoneArray.gta_sa->pos2.z);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.pos2.z[esi], ax
			CPatch::PatchPointer(0x572A6D + 2, &CTheZones__MapZoneArray.gta_sa->level);	// mov     ds:_ZN9CTheZones12MapZoneArrayE.level[esi], al
			CPatch::PatchPointer(0x5D2F06 + 2, CTheZones__MapZoneArray.gta_sa);	// add     edx, offset _ZN9CTheZones12MapZoneArrayE; CTheZones::MapZoneArray
			CPatch::PatchPointer(0x5D2FE6 + 2, CTheZones__MapZoneArray.gta_sa);	// add     edx, offset _ZN9CTheZones12MapZoneArrayE; CTheZones::MapZoneArray
		}
		#endif

		if (bShouldSaveBeEnhanced)
			g_SaveOfVariableLength.MakeSaveOfVariableLength();
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	MapZonesLimit = iMapZones;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IPL:map zones to: %d", MapZonesLimit);
	CGenericLogStorage::WriteLineSeparator();
}

// IPL: navigation zones
void IPLsectionLimits::SetNavigationZones(unsigned int iNavigationZones)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iNavigationZones = this->NavigationZonesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
	{
		using namespace Game_GTASA;
		bool bShouldSaveBeEnhanced = false;

		if (iNavigationZones > this->NavigationZonesLimit)
		{
			CTheZones__NavigationZoneArray.gta_sa = new CZone[iNavigationZones];
			CTheZones__NavigationZoneArray.bIsAllocated.Set(true);

			CTheZones__ZoneInfoArray.gta_sa = new CZoneInfo[iNavigationZones];
			CTheZones__ZoneInfoArray.bIsAllocated.Set(true);

			bShouldSaveBeEnhanced = true;
		}		

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(0x572679 + 1, iNavigationZones);	// mov     ecx, 380
		}
		#endif

		// Navigation zone array
		#if TRUE
		{
			CPatch::PatchPointer(0x403C3C + 3, &CTheZones__NavigationZoneArray.gta_sa->pos1);	// movsx   eax, ds:_ZN9CTheZones19NavigationZoneArrayE.x1
			CPatch::PatchPointer(0x44398C + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// movzx   esi, ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[esi]
			CPatch::PatchPointer(0x443B3B + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// mov     ax, ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[edx]
			CPatch::PatchPointer(0x443B87 + 1, &CTheZones__NavigationZoneArray.gta_sa->pos1);	// mov     esi, offset _ZN9CTheZones19NavigationZoneArrayE.x1
			CPatch::PatchPointer(0x443C1A + 2, &CTheZones__NavigationZoneArray.gta_sa->name);	// lea     ecx, _ZN9CTheZones19NavigationZoneArrayE.name[edx]; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x443E04 + 1, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// mov     edi, offset _ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex
			CPatch::PatchPointer(0x46B4F9 + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// movzx   eax, ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[edx]
			CPatch::PatchPointer(0x46B546 + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// movzx   eax, ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[edx]
			CPatch::PatchPointer(0x46ECD9 + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// movzx   eax, ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[edx]
			CPatch::PatchPointer(0x46ED3B + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// movzx   edx, ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[ecx]
			CPatch::PatchPointer(0x46ED6F + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// movzx   ecx, ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[eax]
			CPatch::PatchPointer(0x4718EA + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// movzx   eax, ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[edx]
			CPatch::PatchPointer(0x47522D + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// movzx   ecx, ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[eax]
			CPatch::PatchPointer(0x479642 + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// movzx   eax, ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[edx]
			CPatch::PatchPointer(0x5721B2 + 2, &CTheZones__NavigationZoneArray.gta_sa->name);	// mov     ebp, dword ptr ds:_ZN9CTheZones19NavigationZoneArrayE.name[eax]; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x5721BB + 2, &CTheZones__NavigationZoneArray.gta_sa->name);	// cmp     ebp, dword ptr ds:_ZN9CTheZones19NavigationZoneArrayE.name[ecx]; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x5721C3 + 2, &CTheZones__NavigationZoneArray.gta_sa->name[4]);	// mov     eax, dword ptr ds:(_ZN9CTheZones19NavigationZoneArrayE.name+4)[eax]
			CPatch::PatchPointer(0x5721C9 + 2, &CTheZones__NavigationZoneArray.gta_sa->name[4]);	// cmp     eax, dword ptr ds:(_ZN9CTheZones19NavigationZoneArrayE.name+4)[ecx]
			CPatch::PatchPointer(0x5721E9 + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// mov     ax, ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[ecx]
			CPatch::PatchPointer(0x5721F5 + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[edx], ax
			CPatch::PatchPointer(0x57220C + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[ecx], ax
			CPatch::PatchPointer(0x572368 + 3, &CTheZones__NavigationZoneArray.gta_sa->pos1.y);	// movsx   ecx, ds:_ZN9CTheZones19NavigationZoneArrayE.y1
			CPatch::PatchPointer(0x57236F + 3, &CTheZones__NavigationZoneArray.gta_sa->pos2.y);	// movsx   edx, ds:_ZN9CTheZones19NavigationZoneArrayE.y2
			CPatch::PatchPointer(0x572378 + 3, &CTheZones__NavigationZoneArray.gta_sa->pos2.x);	// movsx   ebp, ds:_ZN9CTheZones19NavigationZoneArrayE.x2
			CPatch::PatchPointer(0x57238E + 1, CTheZones__NavigationZoneArray.gta_sa);	// mov     ebx, offset _ZN9CTheZones19NavigationZoneArrayE; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x57239B + 1, &CTheZones__NavigationZoneArray.gta_sa[1].pos1.y);	// mov     esi, (offset _ZN9CTheZones19NavigationZoneArrayE.y1+20h)
			CPatch::PatchPointer(0x572432 + 2, CTheZones__NavigationZoneArray.gta_sa);	// mov     dword ptr [eax], offset _ZN9CTheZones19NavigationZoneArrayE; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x572598 + 1, CTheZones__NavigationZoneArray.gta_sa);	// add     eax, offset _ZN9CTheZones19NavigationZoneArrayE; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x572674 + 1, &CTheZones__NavigationZoneArray.gta_sa->text);	// mov     eax, offset _ZN9CTheZones19NavigationZoneArrayE.text
			CPatch::PatchPointer(0x5726DD + 1, &CTheZones__NavigationZoneArray.gta_sa->name[0]);	// mov     dword ptr ds:_ZN9CTheZones19NavigationZoneArrayE.name, eax; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x5726E2 + 2, &CTheZones__NavigationZoneArray.gta_sa->name[4]);	// mov     dword ptr ds:_ZN9CTheZones19NavigationZoneArrayE.name+4, ecx
			CPatch::PatchPointer(0x5726E8 + 1, &CTheZones__NavigationZoneArray.gta_sa->text[0]);	// mov     dword ptr ds:_ZN9CTheZones19NavigationZoneArrayE.text, eax
			CPatch::PatchPointer(0x5726ED + 2, &CTheZones__NavigationZoneArray.gta_sa->text[4]);	// mov     dword ptr ds:_ZN9CTheZones19NavigationZoneArrayE.text+4, ecx
			CPatch::PatchPointer(0x572707 + 3, &CTheZones__NavigationZoneArray.gta_sa->pos1.x);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.x1, bp
			CPatch::PatchPointer(0x57270E + 3, &CTheZones__NavigationZoneArray.gta_sa->pos1.y);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.y1, bp
			CPatch::PatchPointer(0x572715 + 3, &CTheZones__NavigationZoneArray.gta_sa->pos1.z);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.z1, 0F830h
			CPatch::PatchPointer(0x57271E + 3, &CTheZones__NavigationZoneArray.gta_sa->pos2.x);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.x2, di
			CPatch::PatchPointer(0x572725 + 3, &CTheZones__NavigationZoneArray.gta_sa->pos2.y);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.y2, di
			CPatch::PatchPointer(0x57272C + 3, &CTheZones__NavigationZoneArray.gta_sa->pos2.z);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.z2, 7D0h
			CPatch::PatchPointer(0x572735 + 2, &CTheZones__NavigationZoneArray.gta_sa->level);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.level, bl
			CPatch::PatchPointer(0x57273B + 2, &CTheZones__NavigationZoneArray.gta_sa->type);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.type, bl
			CPatch::PatchPointer(0x572A98 + 2, &CTheZones__NavigationZoneArray.gta_sa->name);	// lea     edi, _ZN9CTheZones19NavigationZoneArrayE.name[edx]; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x572AB4 + 2, &CTheZones__NavigationZoneArray.gta_sa->text);	// lea     edx, _ZN9CTheZones19NavigationZoneArrayE.text[ecx]
			CPatch::PatchPointer(0x572ACE + 2, &CTheZones__NavigationZoneArray.gta_sa->type);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.type[esi], bl
			CPatch::PatchPointer(0x572ADD + 3, &CTheZones__NavigationZoneArray.gta_sa->pos1.x);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.x1[esi], ax
			CPatch::PatchPointer(0x572AED + 3, &CTheZones__NavigationZoneArray.gta_sa->pos1.y);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.y1[esi], ax
			CPatch::PatchPointer(0x572AFD + 3, &CTheZones__NavigationZoneArray.gta_sa->pos1.z);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.z1[esi], ax
			CPatch::PatchPointer(0x572B0D + 3, &CTheZones__NavigationZoneArray.gta_sa->pos2.x);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.x2[esi], ax
			CPatch::PatchPointer(0x572B1D + 3, &CTheZones__NavigationZoneArray.gta_sa->pos2.y);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.y2[esi], ax
			CPatch::PatchPointer(0x572B2E + 3, &CTheZones__NavigationZoneArray.gta_sa->pos2.z);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.z2[esi], ax
			CPatch::PatchPointer(0x572B39 + 2, &CTheZones__NavigationZoneArray.gta_sa->level);	// mov     ds:_ZN9CTheZones19NavigationZoneArrayE.level[esi], al
			CPatch::PatchPointer(0x572BB6 + 1, CTheZones__NavigationZoneArray.gta_sa);	// add     eax, offset _ZN9CTheZones19NavigationZoneArrayE; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x572C0A + 1, CTheZones__NavigationZoneArray.gta_sa);	// add     eax, offset _ZN9CTheZones19NavigationZoneArrayE; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x572C96 + 2, &CTheZones__NavigationZoneArray.gta_sa->name[0]);	// mov     ebx, dword ptr ds:_ZN9CTheZones19NavigationZoneArrayE.name[ecx]; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x572CA0 + 2, &CTheZones__NavigationZoneArray.gta_sa->name[4]);	// mov     ecx, dword ptr ds:(_ZN9CTheZones19NavigationZoneArrayE.name+4)[ecx]
			CPatch::PatchPointer(0x572CCC + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// movzx   eax, ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[eax]
			CPatch::PatchPointer(0x5866C1 + 1, &CTheZones__NavigationZoneArray.gta_sa->pos1.x);	// mov     edi, offset _ZN9CTheZones19NavigationZoneArrayE.x1
			CPatch::PatchPointer(0x5D268F + 1, CTheZones__NavigationZoneArray.gta_sa);	// mov     edx, offset _ZN9CTheZones19NavigationZoneArrayE; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x5D278A + 1, CTheZones__NavigationZoneArray.gta_sa);	// add     eax, offset _ZN9CTheZones19NavigationZoneArrayE; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x5D2EA6 + 1, CTheZones__NavigationZoneArray.gta_sa);	// add     eax, offset _ZN9CTheZones19NavigationZoneArrayE; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x5D2F8A + 1, CTheZones__NavigationZoneArray.gta_sa);	// add     eax, offset _ZN9CTheZones19NavigationZoneArrayE; CTheZones::NavigationZoneArray
			CPatch::PatchPointer(0x1569A00 + 3, &CTheZones__NavigationZoneArray.gta_sa->ZoneInfoIndex);	// movzx   esi, ds:_ZN9CTheZones19NavigationZoneArrayE.ZoneInfoIndex[esi]
		}
		#endif

		// Zone info array
		#if TRUE
		{
			CPatch::PatchPointer(0x443996 + 3, (void*)((int)&CTheZones__ZoneInfoArray.gta_sa->GangDensity - PED_TYPE_GANG1));	// mov     bl, ds:byte_BA1DE9[esi+edx]

			CPatch::PatchPointer(0x443B58 + 3, &CTheZones__ZoneInfoArray.gta_sa->GangDensity[2]);	// movzx   ecx, ds:(_ZN9CTheZones13ZoneInfoArrayE.GangDensity+2)[ebx]
			CPatch::PatchPointer(0x443B5F + 3, &CTheZones__ZoneInfoArray.gta_sa->GangDensity);	// movzx   eax, byte ptr ds:_ZN9CTheZones13ZoneInfoArrayE.GangDensity[ebx]; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x443C0A + 2, &CTheZones__ZoneInfoArray.gta_sa->GangDensity[1]);	// cmp     ds:(_ZN9CTheZones13ZoneInfoArrayE.GangDensity+1)[edi], 0Fh
			CPatch::PatchPointer(0x443C3B + 2, &CTheZones__ZoneInfoArray.gta_sa->GangDensity);	// mov     dl, byte ptr ds:_ZN9CTheZones13ZoneInfoArrayE.GangDensity[ebx]; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x443C43 + 2, &CTheZones__ZoneInfoArray.gta_sa->GangDensity[2]);	// cmp     ds:(_ZN9CTheZones13ZoneInfoArrayE.GangDensity+2)[ebx], dl
			CPatch::PatchPointer(0x443C4F + 2, &CTheZones__ZoneInfoArray.gta_sa->GangDensity);	// lea     ecx, _ZN9CTheZones13ZoneInfoArrayE.GangDensity[edi]; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x443E1E + 2, &CTheZones__ZoneInfoArray.gta_sa->GangDensity[2]);	// mov     dl, ds:(_ZN9CTheZones13ZoneInfoArrayE.GangDensity+2)[eax]
			CPatch::PatchPointer(0x443E24 + 2, &CTheZones__ZoneInfoArray.gta_sa->GangDensity);	// mov     bl, byte ptr ds:_ZN9CTheZones13ZoneInfoArrayE.GangDensity[eax]; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x443E2A + 3, &CTheZones__ZoneInfoArray.gta_sa->GangDensity[1]);	// movzx   eax, ds:(_ZN9CTheZones13ZoneInfoArrayE.GangDensity+1)[eax]
			CPatch::PatchPointer(0x46B509 + 3, &CTheZones__ZoneInfoArray.gta_sa->GangDensity);	// mov     byte ptr ds:_ZN9CTheZones13ZoneInfoArrayE.GangDensity[eax+edx], cl; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x46B550 + 4, &CTheZones__ZoneInfoArray.gta_sa->GangDensity);	// movzx   edx, byte ptr ds:_ZN9CTheZones13ZoneInfoArrayE.GangDensity[eax+ecx]; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x46ECE3 + 2, &CTheZones__ZoneInfoArray.gta_sa->Flags1);	// mov     cl, ds:_ZN9CTheZones13ZoneInfoArrayE.Flags1[eax]
			CPatch::PatchPointer(0x46ECE9 + 2, &CTheZones__ZoneInfoArray.gta_sa->Flags1);	// mov     dl, ds:_ZN9CTheZones13ZoneInfoArrayE.Flags1[eax]
			CPatch::PatchPointer(0x46ECEF + 2, &CTheZones__ZoneInfoArray.gta_sa->Flags1);	// lea     eax, _ZN9CTheZones13ZoneInfoArrayE.Flags1[eax]
			CPatch::PatchPointer(0x46ED45 + 2, &CTheZones__ZoneInfoArray.gta_sa->DrugDealerCounter);	// mov     ds:_ZN9CTheZones13ZoneInfoArrayE.DrugDealerCounter[edx], al
			CPatch::PatchPointer(0x46ED79 + 3, &CTheZones__ZoneInfoArray.gta_sa->DrugDealerCounter);	// movzx   edx, ds:_ZN9CTheZones13ZoneInfoArrayE.DrugDealerCounter[ecx]
			CPatch::PatchPointer(0x4718F4 + 2, &CTheZones__ZoneInfoArray.gta_sa->Flags2);	// mov     cl, ds:_ZN9CTheZones13ZoneInfoArrayE.Flags2[eax]
			CPatch::PatchPointer(0x4718FA + 2, &CTheZones__ZoneInfoArray.gta_sa->Flags2);	// mov     dl, ds:_ZN9CTheZones13ZoneInfoArrayE.Flags2[eax]
			CPatch::PatchPointer(0x471900 + 2, &CTheZones__ZoneInfoArray.gta_sa->Flags2);	// lea     eax, _ZN9CTheZones13ZoneInfoArrayE.Flags2[eax]
			CPatch::PatchPointer(0x479652 + 2, &CTheZones__ZoneInfoArray.gta_sa->Flags1);	// mov     cl, ds:_ZN9CTheZones13ZoneInfoArrayE.Flags1[eax]
			CPatch::PatchPointer(0x479658 + 2, &CTheZones__ZoneInfoArray.gta_sa->Flags1);	// lea     eax, _ZN9CTheZones13ZoneInfoArrayE.Flags1[eax]
			CPatch::PatchPointer(0x5720D2 + 1, &CTheZones__ZoneInfoArray.gta_sa->Flags1);	// mov     eax, offset _ZN9CTheZones13ZoneInfoArrayE.Flags1
			CPatch::PatchPointer(0x572104 + 1, &CTheZones__ZoneInfoArray.gta_sa[iNavigationZones].Flags1);	// cmp     eax, offset unk_BA373B
			CPatch::PatchPointer(0x572424 + 1, CTheZones__ZoneInfoArray.gta_sa);	// add     eax, offset _ZN9CTheZones13ZoneInfoArrayE; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x572438 + 1, CTheZones__ZoneInfoArray.gta_sa);	// mov     eax, offset _ZN9CTheZones13ZoneInfoArrayE; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x57245D + 1, &CTheZones__ZoneInfoArray.gta_sa->GangDensity[2]);	// mov     edi, (offset _ZN9CTheZones13ZoneInfoArrayE.GangDensity+2)
			CPatch::PatchPointer(0x572CD6 + 1, CTheZones__ZoneInfoArray.gta_sa);	// add     eax, offset _ZN9CTheZones13ZoneInfoArrayE; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x5866E3 + 2, &CTheZones__ZoneInfoArray.gta_sa->Flags1);	// test    ds:_ZN9CTheZones13ZoneInfoArrayE.Flags1[esi], 60h
			CPatch::PatchPointer(0x5866F0 + 2, CTheZones__ZoneInfoArray.gta_sa);	// lea     eax, _ZN9CTheZones13ZoneInfoArrayE.GangDensity[esi]; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x586732 + 2, &CTheZones__ZoneInfoArray.gta_sa->Flags1);	// mov     al, ds:_ZN9CTheZones13ZoneInfoArrayE.Flags1[esi]
			CPatch::PatchPointer(0x586797 + 3, &CTheZones__ZoneInfoArray.gta_sa->ZoneRGBA.alpha);	// movzx   eax, ds:(_ZN9CTheZones13ZoneInfoArrayE.ZoneRGBA+3)[esi]
			CPatch::PatchPointer(0x5867DA + 3, &CTheZones__ZoneInfoArray.gta_sa->ZoneRGBA.alpha);	// movzx   edx, ds:(_ZN9CTheZones13ZoneInfoArrayE.ZoneRGBA+3)[esi]
			CPatch::PatchPointer(0x586806 + 2, &CTheZones__ZoneInfoArray.gta_sa->ZoneRGBA.blue);	// mov     cl, ds:(_ZN9CTheZones13ZoneInfoArrayE.ZoneRGBA+2)[esi]
			CPatch::PatchPointer(0x586810 + 2, &CTheZones__ZoneInfoArray.gta_sa->ZoneRGBA.green);	// mov     dl, ds:(_ZN9CTheZones13ZoneInfoArrayE.ZoneRGBA+1)[esi]
			CPatch::PatchPointer(0x586818 + 2, &CTheZones__ZoneInfoArray.gta_sa->ZoneRGBA.red);	// mov     al, ds:_ZN9CTheZones13ZoneInfoArrayE.ZoneRGBA[esi]
			CPatch::PatchPointer(0x586829 + 2, &CTheZones__ZoneInfoArray.gta_sa->ZoneRGBA.alpha);	// mov     cl, ds:(_ZN9CTheZones13ZoneInfoArrayE.ZoneRGBA+3)[esi]
			CPatch::PatchPointer(0x586832 + 2, &CTheZones__ZoneInfoArray.gta_sa->ZoneRGBA.blue);	// mov     dl, ds:(_ZN9CTheZones13ZoneInfoArrayE.ZoneRGBA+2)[esi]
			CPatch::PatchPointer(0x58683A + 2, &CTheZones__ZoneInfoArray.gta_sa->ZoneRGBA.green);	// mov     al, ds:(_ZN9CTheZones13ZoneInfoArrayE.ZoneRGBA+1)[esi]
			CPatch::PatchPointer(0x586843 + 2, &CTheZones__ZoneInfoArray.gta_sa->ZoneRGBA.red);	// mov     cl, ds:_ZN9CTheZones13ZoneInfoArrayE.ZoneRGBA[esi]
			CPatch::PatchPointer(0x5D2658 + 1, CTheZones__ZoneInfoArray.gta_sa);	// mov     edx, offset _ZN9CTheZones13ZoneInfoArrayE; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x5D276D + 1, CTheZones__ZoneInfoArray.gta_sa);	// add     eax, offset _ZN9CTheZones13ZoneInfoArrayE; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x5D2ED6 + 2, CTheZones__ZoneInfoArray.gta_sa);	// add     ecx, offset _ZN9CTheZones13ZoneInfoArrayE; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x5D2FB6 + 2, CTheZones__ZoneInfoArray.gta_sa);	// add     ecx, offset _ZN9CTheZones13ZoneInfoArrayE; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x6104EF + 1, &CTheZones__ZoneInfoArray.gta_sa->DrugDealerCounter);	// mov     esi, offset _ZN9CTheZones13ZoneInfoArrayE.DrugDealerCounter
			CPatch::PatchPointer(0x15699D6 + 1, CTheZones__ZoneInfoArray.gta_sa);	// add     eax, offset _ZN9CTheZones13ZoneInfoArrayE; CTheZones::ZoneInfoArray
			CPatch::PatchPointer(0x1569A0A + 2, CTheZones__ZoneInfoArray.gta_sa);	// add     esi, offset _ZN9CTheZones13ZoneInfoArrayE; CTheZones::ZoneInfoArray
		}
		#endif

		if (bShouldSaveBeEnhanced)
			g_SaveOfVariableLength.MakeSaveOfVariableLength();
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->NavigationZonesLimit = iNavigationZones;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IPL:navigation zones to: %d", NavigationZonesLimit);
	CGenericLogStorage::WriteLineSeparator();
}

// IPL: COccluder structure coordinate extension
void IPLsectionLimits::SetCOccluderCoordinateLimitHack(bool bCOccluderLimitHack)
{
	this->bCOccluderCoordLimitHackEnabled = bCOccluderLimitHack;
}

// IPL: interior occluders
void IPLsectionLimits::SetInteriorOccluders(unsigned int iInteriorOccluders)
{
	this->InteriorOccludersLimit = iInteriorOccluders;
	this->bInteriorOccludersLimitSet = true;
}

// IPL: occluders
void IPLsectionLimits::SetOccluders(unsigned int iOccluders)
{
	this->OccludersLimit = iOccluders;
	this->bOccludersLimitSet = true;
}

// IPL: tcyc
void IPLsectionLimits::SetTcyc(unsigned int iTcycEntries)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iTcycEntries = this->TcycLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (iTcycEntries > this->TcycLimit)
		{
			CTimeCycle__m_aBoxes.gta_sa = new CTimecycleBox[iTcycEntries];
			CTimeCycle__m_aBoxes.bIsAllocated.Set(true);
		}

		// Patch references to CTimeCycle::m_aBoxes
		#if TRUE
		{
			CPatch::PatchPointer(0x55FF68 + 2, &CTimeCycle__m_aBoxes.gta_sa->m_box.m_vInf);	// lea     edi, _ZN10CTimeCycle8m_aBoxesE.m_box.m_vInf.x[ebx]; CTimeCycle::m_aBoxes	; _ZN10CTimeCycle6AddOneER4CBoxsifff
			CPatch::PatchPointer(0x55FF79 + 3, &CTimeCycle__m_aBoxes.gta_sa->m_farClip);	// mov     _ZN10CTimeCycle8m_aBoxesE.m_farClip[ebx], ax	; _ZN10CTimeCycle6AddOneER4CBoxsifff
			CPatch::PatchPointer(0x55FF80 + 2, &CTimeCycle__m_aBoxes.gta_sa->m_interiorCycleAndWeather);	// mov     _ZN10CTimeCycle8m_aBoxesE.m_interiorCycleAndWeather[ebx], ecx	; _ZN10CTimeCycle6AddOneER4CBoxsifff
			CPatch::PatchPointer(0x55FF86 + 2, &CTimeCycle__m_aBoxes.gta_sa->field_20);	// fstp    _ZN10CTimeCycle8m_aBoxesE.field_20[ebx]	; _ZN10CTimeCycle6AddOneER4CBoxsifff
			CPatch::PatchPointer(0x55FF8C + 2, &CTimeCycle__m_aBoxes.gta_sa->field_24);	// mov     _ZN10CTimeCycle8m_aBoxesE.field_24[ebx], edx	; _ZN10CTimeCycle6AddOneER4CBoxsifff
			CPatch::PatchPointer(0x55FFC4 + 2, &CTimeCycle__m_aBoxes.gta_sa->field_1A);	// mov     _ZN10CTimeCycle8m_aBoxesE.field_1A[ebx], al	; _ZN10CTimeCycle6AddOneER4CBoxsifff
			CPatch::PatchPointer(0x55FFFB + 1, &CTimeCycle__m_aBoxes.gta_sa->m_box.m_vSup);	// mov     ecx, offset _ZN10CTimeCycle8m_aBoxesE.m_box.m_vSup	; _ZN10CTimeCycle16FindTimeCycleBoxE7CVectorPP13CTimeCycleBoxPfbbS2_
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	IPLsectionLimits::TcycLimit = iTcycEntries;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IPL:Timecycle modifiers to: %d", OccludersLimit);
	CGenericLogStorage::WriteLineSeparator();	
}

// IPL: cull mirror attribute zones
void IPLsectionLimits::SetCullMirrorAttributeZones(unsigned int iCullMirrorAttributeZones)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iCullMirrorAttributeZones = this->CullMirrorAttributeZonesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (iCullMirrorAttributeZones > this->CullMirrorAttributeZonesLimit)
		{
			CCullZones__aMirrorAttributeZones.gta_sa = new CCullZoneReflection[iCullMirrorAttributeZones];
			CCullZones__aMirrorAttributeZones.bIsAllocated.Set(true);
		}

		// Patch
		#if TRUE
		{
			CPatch::PatchPointer(0x72DA84 + 1, CCullZones__aMirrorAttributeZones.gta_sa);	// mov     esi, offset _ZN10CCullZones21aMirrorAttributeZonesE; CCullZones::aMirrorAttributeZones	; _ZN10CCullZones28FindMirrorAttributesForCoorsE7CVector
			CPatch::PatchPointer(0x72DAC5 + 3, &CCullZones__aMirrorAttributeZones.gta_sa->x);	// lea     eax, _ZN10CCullZones21aMirrorAttributeZonesE.__parent.x[eax*8]; CCullZones::aMirrorAttributeZones	; _ZN10CCullZones28FindMirrorAttributesForCoorsE7CVector
			CPatch::PatchPointer(0x72DC32 + 3, &CCullZones__aMirrorAttributeZones.gta_sa->x);	// mov     word ptr _ZN10CCullZones21aMirrorAttributeZonesE.__parent.x[esi], ax; CCullZones::aMirrorAttributeZones	; _ZN10CCullZones22AddMirrorAttributeZoneERK7CVectorfffffftffff
			CPatch::PatchPointer(0x72DC4F + 3, &CCullZones__aMirrorAttributeZones.gta_sa->y);	// mov     _ZN10CCullZones21aMirrorAttributeZonesE.__parent.y[esi], ax	; _ZN10CCullZones22AddMirrorAttributeZoneERK7CVectorfffffftffff
			CPatch::PatchPointer(0x72DC61 + 3, &CCullZones__aMirrorAttributeZones.gta_sa->field_4);	// mov     _ZN10CCullZones21aMirrorAttributeZonesE.__parent.field_4[esi], ax	; _ZN10CCullZones22AddMirrorAttributeZoneERK7CVectorfffffftffff
			CPatch::PatchPointer(0x72DC71 + 3, &CCullZones__aMirrorAttributeZones.gta_sa->Ywidth);	// mov     _ZN10CCullZones21aMirrorAttributeZonesE.__parent.Ywidth[esi], ax	; _ZN10CCullZones22AddMirrorAttributeZoneERK7CVectorfffffftffff
			CPatch::PatchPointer(0x72DC83 + 3, &CCullZones__aMirrorAttributeZones.gta_sa->Zbottom);	// mov     _ZN10CCullZones21aMirrorAttributeZonesE.__parent.Zbottom[esi], ax	; _ZN10CCullZones22AddMirrorAttributeZoneERK7CVectorfffffftffff
			CPatch::PatchPointer(0x72DC95 + 3, &CCullZones__aMirrorAttributeZones.gta_sa->Xwidth);	// mov     _ZN10CCullZones21aMirrorAttributeZonesE.__parent.Xwidth[esi], ax	; _ZN10CCullZones22AddMirrorAttributeZoneERK7CVectorfffffftffff
			CPatch::PatchPointer(0x72DCA5 + 3, &CCullZones__aMirrorAttributeZones.gta_sa->field_A);	// mov     _ZN10CCullZones21aMirrorAttributeZonesE.__parent.field_A[esi], ax	; _ZN10CCullZones22AddMirrorAttributeZoneERK7CVectorfffffftffff
			CPatch::PatchPointer(0x72DCBF + 3, &CCullZones__aMirrorAttributeZones.gta_sa->Ztop);	// mov     _ZN10CCullZones21aMirrorAttributeZonesE.__parent.Ztop[esi], ax	; _ZN10CCullZones22AddMirrorAttributeZoneERK7CVectorfffffftffff
			CPatch::PatchPointer(0x72DCCA + 2, &CCullZones__aMirrorAttributeZones.gta_sa->flags);	// mov     _ZN10CCullZones21aMirrorAttributeZonesE.flags[esi], al	; _ZN10CCullZones22AddMirrorAttributeZoneERK7CVectorfffffftffff
			CPatch::PatchPointer(0x72DCD0 + 2, &CCullZones__aMirrorAttributeZones.gta_sa->cm);	// mov     _ZN10CCullZones21aMirrorAttributeZonesE.cm[esi], ecx	; _ZN10CCullZones22AddMirrorAttributeZoneERK7CVectorfffffftffff
			CPatch::PatchPointer(0x72DCE5 + 2, &CCullZones__aMirrorAttributeZones.gta_sa->vx);	// mov     _ZN10CCullZones21aMirrorAttributeZonesE.vx[esi], al	; _ZN10CCullZones22AddMirrorAttributeZoneERK7CVectorfffffftffff
			CPatch::PatchPointer(0x72DCFA + 2, &CCullZones__aMirrorAttributeZones.gta_sa->vy);	// mov     _ZN10CCullZones21aMirrorAttributeZonesE.vy[esi], al	; _ZN10CCullZones22AddMirrorAttributeZoneERK7CVectorfffffftffff
			CPatch::PatchPointer(0x72DD0D + 2, &CCullZones__aMirrorAttributeZones.gta_sa->vz);	// mov     _ZN10CCullZones21aMirrorAttributeZonesE.vz[esi], al	; _ZN10CCullZones22AddMirrorAttributeZoneERK7CVectorfffffftffff
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	IPLsectionLimits::CullMirrorAttributeZonesLimit = iCullMirrorAttributeZones;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of 'IPL:CULL mirror attribute zones' to: %d",
		iCullMirrorAttributeZones
		);
	CGenericLogStorage::WriteLineSeparator();
}

// IPL: cull tunnel attribute zones
void IPLsectionLimits::SetCullTunnelAttributeZones(unsigned int iCullTunnelAttributeZones)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iCullTunnelAttributeZones = this->CullTunnelAttributeZonesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (iCullTunnelAttributeZones > this->CullTunnelAttributeZonesLimit)
		{
			CCullZones__aTunnelAttributeZones.gta_sa = new CCullZone[iCullTunnelAttributeZones];
			CCullZones__aTunnelAttributeZones.bIsAllocated.Set(true);
		}

		// Patch references
		#if TRUE
		{
			CPatch::PatchPointer(0x72DA12 + 1, &CCullZones__aTunnelAttributeZones.gta_sa->flags);	// mov     esi, offset _ZN10CCullZones21aTunnelAttributeZonesE.flags	; _ZN10CCullZones28FindTunnelAttributesForCoorsE7CVector
			CPatch::PatchPointer(0x72DB71 + 3, &CCullZones__aTunnelAttributeZones.gta_sa->x);	// mov     word ptr _ZN10CCullZones21aTunnelAttributeZonesE.__parent.x[esi], ax; CCullZones::aTunnelAttributeZones	; _ZN10CCullZones22AddTunnelAttributeZoneERK7CVectorfffffft
			CPatch::PatchPointer(0x72DB8E + 3, &CCullZones__aTunnelAttributeZones.gta_sa->y);	// mov     _ZN10CCullZones21aTunnelAttributeZonesE.__parent.y[esi], ax	; _ZN10CCullZones22AddTunnelAttributeZoneERK7CVectorfffffft
			CPatch::PatchPointer(0x72DBA0 + 3, &CCullZones__aTunnelAttributeZones.gta_sa->field_4);	// mov     _ZN10CCullZones21aTunnelAttributeZonesE.__parent.field_4[esi], ax	; _ZN10CCullZones22AddTunnelAttributeZoneERK7CVectorfffffft
			CPatch::PatchPointer(0x72DBB0 + 3, &CCullZones__aTunnelAttributeZones.gta_sa->Ywidth);	// mov     _ZN10CCullZones21aTunnelAttributeZonesE.__parent.Ywidth[esi], ax	; _ZN10CCullZones22AddTunnelAttributeZoneERK7CVectorfffffft
			CPatch::PatchPointer(0x72DBC2 + 3, &CCullZones__aTunnelAttributeZones.gta_sa->Zbottom);	// mov     _ZN10CCullZones21aTunnelAttributeZonesE.__parent.Zbottom[esi], ax	; _ZN10CCullZones22AddTunnelAttributeZoneERK7CVectorfffffft
			CPatch::PatchPointer(0x72DBD4 + 3, &CCullZones__aTunnelAttributeZones.gta_sa->Xwidth);	// mov     _ZN10CCullZones21aTunnelAttributeZonesE.__parent.Xwidth[esi], ax	; _ZN10CCullZones22AddTunnelAttributeZoneERK7CVectorfffffft
			CPatch::PatchPointer(0x72DBE4 + 3, &CCullZones__aTunnelAttributeZones.gta_sa->field_A);	// mov     _ZN10CCullZones21aTunnelAttributeZonesE.__parent.field_A[esi], ax	; _ZN10CCullZones22AddTunnelAttributeZoneERK7CVectorfffffft
			CPatch::PatchPointer(0x72DBF0 + 3, &CCullZones__aTunnelAttributeZones.gta_sa->Ztop);	// mov     _ZN10CCullZones21aTunnelAttributeZonesE.__parent.Ztop[esi], ax	; _ZN10CCullZones22AddTunnelAttributeZoneERK7CVectorfffffft
			CPatch::PatchPointer(0x72DC04 + 3, &CCullZones__aTunnelAttributeZones.gta_sa->flags);	// mov     _ZN10CCullZones21aTunnelAttributeZonesE.flags[esi], ax	; _ZN10CCullZones22AddTunnelAttributeZoneERK7CVectorfffffft
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	IPLsectionLimits::CullTunnelAttributeZonesLimit = iCullTunnelAttributeZones;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of 'IPL:CULL tunnel attribute zones' to: %d",
		iCullTunnelAttributeZones
		);
	CGenericLogStorage::WriteLineSeparator();
}

// IPL: cull attribute zones
void IPLsectionLimits::SetCullAttributeZones(unsigned int iCullAttributeZones)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iCullAttributeZones = this->CullAttributeZonesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (iCullAttributeZones > this->CullAttributeZonesLimit)
		{
			CCullZones__aAttributeZones.gta_sa = new CCullZone[iCullAttributeZones];
			CCullZones__aAttributeZones.bIsAllocated.Set(true);
		}

		// Patch references
		#if TRUE
		{
			CPatch::PatchPointer(0x72D992 + 1, &CCullZones__aAttributeZones.gta_sa->flags);	// mov     esi, offset _ZN10CCullZones15aAttributeZonesE.flags	; sub_72D970
			CPatch::PatchPointer(0x72DAF9 + 1, CCullZones__aAttributeZones.gta_sa);	// mov     esi, offset _ZN10CCullZones15aAttributeZonesE; CCullZones::aAttributeZones	; sub_72DAD0
			CPatch::PatchPointer(0x72DB3F + 3, &CCullZones__aAttributeZones.gta_sa->x);	// lea     eax, _ZN10CCullZones15aAttributeZonesE.__parent.x[eax*2]; CCullZones::aAttributeZones	; sub_72DAD0
			CPatch::PatchPointer(0x72DFD7 + 3, &CCullZones__aAttributeZones.gta_sa->x);	// mov     word ptr ds:_ZN10CCullZones15aAttributeZonesE.__parent.x[esi], ax; CCullZones::aAttributeZones	; sub_72DF70
			CPatch::PatchPointer(0x72DFF4 + 3, &CCullZones__aAttributeZones.gta_sa->y);	// mov     ds:_ZN10CCullZones15aAttributeZonesE.__parent.y[esi], ax	; sub_72DF70
			CPatch::PatchPointer(0x72E006 + 3, &CCullZones__aAttributeZones.gta_sa->field_4);	// mov     ds:_ZN10CCullZones15aAttributeZonesE.__parent.field_4[esi], ax	; sub_72DF70
			CPatch::PatchPointer(0x72E016 + 3, &CCullZones__aAttributeZones.gta_sa->Ywidth);	// mov     ds:_ZN10CCullZones15aAttributeZonesE.__parent.Ywidth[esi], ax	; sub_72DF70
			CPatch::PatchPointer(0x72E028 + 3, &CCullZones__aAttributeZones.gta_sa->Zbottom);	// mov     ds:_ZN10CCullZones15aAttributeZonesE.__parent.Zbottom[esi], ax	; sub_72DF70
			CPatch::PatchPointer(0x72E03A + 3, &CCullZones__aAttributeZones.gta_sa->Xwidth);	// mov     ds:_ZN10CCullZones15aAttributeZonesE.__parent.Xwidth[esi], ax	; sub_72DF70
			CPatch::PatchPointer(0x72E04A + 3, &CCullZones__aAttributeZones.gta_sa->field_A);	// mov     ds:_ZN10CCullZones15aAttributeZonesE.__parent.field_A[esi], ax	; sub_72DF70
			CPatch::PatchPointer(0x72E057 + 3, &CCullZones__aAttributeZones.gta_sa->Ztop);	// mov     ds:_ZN10CCullZones15aAttributeZonesE.__parent.Ztop[esi], ax	; sub_72DF70
			CPatch::PatchPointer(0x72E065 + 3, &CCullZones__aAttributeZones.gta_sa->flags);	// mov     ds:_ZN10CCullZones15aAttributeZonesE.flags[esi], bx	; sub_72DF70

		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	IPLsectionLimits::CullTunnelAttributeZonesLimit = iCullAttributeZones;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of 'IPL:CULL attribute zones' to: %d",
		iCullAttributeZones
		);
	CGenericLogStorage::WriteLineSeparator();
}

// IPL: Sets the Stunt jumps limit
void IPLsectionLimits::SetStuntJumps(unsigned int iStuntJumps)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iStuntJumps = this->StuntJumpsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
			CPatch::PatchUINT32(0x49CA84 + 1, iStuntJumps);
		else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			CPatch::PatchUINT32(0x156DDE4 + 1, iStuntJumps);

		// CStuntJumpManager::Update
		CPatch::PatchUINT32(0x49C8D1 + 2, iStuntJumps);	// cmp     ebp, 256

		// CStuntJumpManager::Save
		CPatch::PatchUINT32(0x5D55B3 + 2, iStuntJumps * 68);	// cmp     esi, 4400h
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->StuntJumpsLimit = iStuntJumps;
	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IPL:Stunt jumps to: %d", iStuntJumps);
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}


extern "C"
{
	unsigned int NumberOfEntryExits;
	unsigned int NumberOfEntryExitsMultipliedBySizeofElement;
	unsigned int NumberOfEntryExitsMinus2negated;
}

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
namespace Game_GTASA
{
	// patch for 0x304A22
	extern "C"
	{
		uintptr_t Address_CEntryExitManager__Init_18E9A8_arm = 0;	// _Znaj
		uintptr_t Address_CEntryExitManager__Init_304A34_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CEntryExitManager__Init_304A22()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, NumberOfEntryExitsMultipliedBySizeofElement)
			"BL 1f\n"
			"STR R0, [R4]\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, NumberOfEntryExits)
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, NumberOfEntryExits)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CEntryExitManager__Init_304A34_thumb)

			// Branches
			"1:\n"	// _Znaj
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CEntryExitManager__Init_18E9A8_arm)
			);
	}

	// patch for 0x304A56
	extern "C"
	{
		uintptr_t Address_CEntryExitManager__Init_304A60_thumb = 0;	// loc_304A60
	}

	static TARGET_THUMB NAKED void patch_CEntryExitManager__Init_304A56()
	{
		__asm(
		".thumb\n"
			"AND R1, R1, #0x80\n"
			"STRB R1, [R0,#1]\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, NumberOfEntryExitsMinus2negated)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CEntryExitManager__Init_304A60_thumb)
			);
	}

	// patch for 0x304A64
	extern "C"
	{
		uintptr_t Address_CEntryExitManager__Init_304A70_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CEntryExitManager__Init_304A64()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, NumberOfEntryExits)
			"LDRB R2, [R1,R2]\n"
			"ORR R2, R2, #0x80\n"
			"PUSH {R0, R3}\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, NumberOfEntryExits)
			"STRB R2, [R1,R0]\n"
			"POP {R0, R3}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CEntryExitManager__Init_304A70_thumb)
			);
	}

	// patch for 0x304A76
	extern "C"
	{
		uintptr_t Address_CEntryExitManager__Init_304A82_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CEntryExitManager__Init_304A76()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, NumberOfEntryExits)
			"LDRB R2, [R1,R2]\n"
			"AND R2, R2, #0x80\n"
			"PUSH {R0, R3}\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, NumberOfEntryExits)
			"STRB R2, [R1,R0]\n"
			"POP {R0, R3}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CEntryExitManager__Init_304A82_thumb)
			);
	}
}
#endif

// IPL: enex
void IPLsectionLimits::SetEntryExits(unsigned int iEntryExits)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iEntryExits = this->EntryExitsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
			CPatch::PatchUINT32(0x43F927 + 1, iEntryExits);
		else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			CPatch::PatchUINT32(0x156A797 + 1, iEntryExits);

		CPatch::PatchUINT32(0x5D5A5F + 2, iEntryExits * sizeof(CEntryExit));
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		// Set variables
		::NumberOfEntryExits = iEntryExits;
		::NumberOfEntryExitsMultipliedBySizeofElement = iEntryExits * 60;
		NumberOfEntryExitsMinus2negated = -(iEntryExits - 2);

		// Changes
		Address_CEntryExitManager__Init_18E9A8_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18E9A8));
		Address_CEntryExitManager__Init_304A34_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x304A34));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x304A22),
			(void*)&patch_CEntryExitManager__Init_304A22, 18
		);

		Address_CEntryExitManager__Init_304A60_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x304A60));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x304A56),
			(void*)&patch_CEntryExitManager__Init_304A56, 10
		);

		Address_CEntryExitManager__Init_304A70_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x304A70));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x304A64),
			(void*)&patch_CEntryExitManager__Init_304A64, 12
		);

		Address_CEntryExitManager__Init_304A82_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x304A82));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x304A76),
			(void*)&patch_CEntryExitManager__Init_304A76, 12
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	IPLsectionLimits::EntryExitsLimit = iEntryExits;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IPL:Entry exits to: %d", iEntryExits);
	CGenericLogStorage::WriteLineSeparator();
}

// IPL: auzo, boxes coordinate limit
void IPLsectionLimits::SetAudioZoneBoxesCoordinateLimitHack(bool bAudioZoneBoxesCoordLimitHack)
{
	this->bAudioZonesBoxesCoordLimitHackEnabled = bAudioZoneBoxesCoordLimitHack;
}

// IPL: auzo, boxes
void IPLsectionLimits::SetAudioZoneBoxes(unsigned int iAudioZonesBoxes)
{
	this->AudioZoneBoxesLimit = iAudioZonesBoxes;
	this->bAudioZoneBoxesLimitSet = true;
}

// IPL: auzo, spheres
void IPLsectionLimits::SetAudioZoneSpheres(unsigned int iAudioZoneSpheres)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iAudioZoneSpheres = this->AudioZoneSpheresLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (iAudioZoneSpheres > this->AudioZoneSpheresLimit)
		{
			CAudioZones__m_aSpheres.gta_sa = new tAudioZoneSphere[iAudioZoneSpheres];
			CAudioZones__m_aSpheres.bIsAllocated.Set(true);
		}

		// Patch references
		#if TRUE
		{
			CPatch::PatchPointer(0x4D6F0D + 3, &CAudioZones__m_aSpheres.gta_sa->m_ID);	// mov     cx, ds:_ZN11CAudioZones10m_aSpheresE.m_ID[eax]	; sub_4D6E60
			CPatch::PatchPointer(0x4D6F14 + 2, &CAudioZones__m_aSpheres.gta_sa->m_Pos);	// lea     edx, _ZN11CAudioZones10m_aSpheresE.m_Pos.x[eax]	; sub_4D6E60
			CPatch::PatchPointer(0x4D8047 + 3, &CAudioZones__m_aSpheres.gta_sa->m_ID);	// mov     ax, ds:_ZN11CAudioZones10m_aSpheresE.m_ID[edx]	; sub_4D8010
			CPatch::PatchPointer(0x5081CD + 2, CAudioZones__m_aSpheres.gta_sa);	// lea     esi, _ZN11CAudioZones10m_aSpheresE.m_Name[eax]; CAudioZones::m_aSpheres	; sub_5081C0
			CPatch::PatchPointer(0x5081E8 + 3, &CAudioZones__m_aSpheres.gta_sa->m_ID);	// mov     ds:_ZN11CAudioZones10m_aSpheresE.m_ID[eax], cx	; sub_5081C0
			CPatch::PatchPointer(0x5081F8 + 3, &CAudioZones__m_aSpheres.gta_sa->m_Flags);	// mov     dx, ds:_ZN11CAudioZones10m_aSpheresE.m_Flags[eax]	; sub_5081C0
			CPatch::PatchPointer(0x508209 + 3, &CAudioZones__m_aSpheres.gta_sa->m_Flags);	// mov     ds:_ZN11CAudioZones10m_aSpheresE.m_Flags[eax], cx	; sub_5081C0
			CPatch::PatchPointer(0x508214 + 2, &CAudioZones__m_aSpheres.gta_sa->m_Pos.x);	// mov     dword ptr ds:_ZN11CAudioZones10m_aSpheresE.m_Pos.x[eax], ecx	; sub_5081C0
			CPatch::PatchPointer(0x50821E + 2, &CAudioZones__m_aSpheres.gta_sa->m_Pos.y);	// mov     ds:_ZN11CAudioZones10m_aSpheresE.m_Pos.y[eax], edx	; sub_5081C0
			CPatch::PatchPointer(0x508228 + 2, &CAudioZones__m_aSpheres.gta_sa->m_Pos.z);	// mov     ds:_ZN11CAudioZones10m_aSpheresE.m_Pos.z[eax], ecx	; sub_5081C0
			CPatch::PatchPointer(0x50822E + 2, &CAudioZones__m_aSpheres.gta_sa->m_Radius);	// mov     ds:_ZN11CAudioZones10m_aSpheresE.m_Radius[eax], edx	; sub_5081C0
			CPatch::PatchPointer(0x508337 + 1, &CAudioZones__m_aSpheres.gta_sa->m_Flags);	// mov     esi, offset _ZN11CAudioZones10m_aSpheresE.m_Flags	; sub_508320
			CPatch::PatchPointer(0x50845A + 1, &CAudioZones__m_aSpheres.gta_sa->m_Pos.z);	// mov     edx, offset _ZN11CAudioZones10m_aSpheresE.m_Pos.z	; sub_5083C0
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	IPLsectionLimits::AudioZoneSpheresLimit = iAudioZoneSpheres;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of 'IPL:AUZO spheres' to: %d",
		iAudioZoneSpheres
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Enables pickup patch
void IPLsectionLimits::EnablePickupPatch(bool bEnable)
{
	MAKE_VAR_GAME_VERSION();
	
	if(gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		this->bPickupPatchEnabled = bEnable;
}

// IPL: pick
void IPLsectionLimits::SetPickups(unsigned int iPickups)
{
	this->PickupsLimit = iPickups;
}

// IPL: pickup collectives
void IPLsectionLimits::SetPickupCollected(unsigned int iPickupCollected)
{
	IPLsectionLimits::PickupsCollectedLimit = iPickupCollected;
}

// Applies enabled limits
void IPLsectionLimits::ApplyEnabledLimits()
{
	// Both need to be enabled if bCOccluderLimitHackEnabled is on.
	{
		CPatch::EnterNewLevel();

		// CPatch::EnableDebugMode();

		if (CPatch::IsDebugModeActive())
			this->bCOccluderCoordLimitHackEnabled = false;

		if (bInteriorOccludersLimitSet || bCOccluderCoordLimitHackEnabled)
			this->PatchInteriorOccluders();

		if (bOccludersLimitSet || bCOccluderCoordLimitHackEnabled)
			this->PatchOccluders();

		if (bCOccluderCoordLimitHackEnabled)
			this->PatchCOccluderCoordinateLimit();

		CPatch::LeaveThisLevel();
	}

	if (bAudioZoneBoxesLimitSet || bAudioZonesBoxesCoordLimitHackEnabled)
		this->PatchAudioZoneBoxes();

	if (bPickupPatchEnabled)
		this->PatchPickups();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	// Fixes loaded pickup
	void FixLoadedPickup(CPickup* pPickup)
	{
		if (pPickup->nbPickupType && pPickup->pObject)
		{
			pPickup->flags &= 0xF7;
			pPickup->pObject = NULL;
		}
	}

	// Convert standard pickup to extended pickup
	void ConvertStandardPickupToExtendedPickup(CPickup_extended* pPickup)
	{
		pPickup->exPos.x = pPickup->pos.x;
		pPickup->exPos.y = pPickup->pos.y;
		pPickup->exPos.z = pPickup->pos.z;

		memset(&pPickup->pos, 0, sizeof(pPickup->pos));
	}

	// CPickups::Save replacement
	bool CPickups__Save()
	{
		CPickup firstPickup = { 0 };

		strcpy((char*)&firstPickup, "fastman92_pickups");
		firstPickup.nbPickupType = 0xFE;

		CGenericGameStorage::SaveDataToWorkBuffer(&firstPickup, sizeof(CPickup));

		uint32_t magicID = '2REV';
		CGenericGameStorage::SaveDataToWorkBuffer(&magicID, sizeof(uint32_t));

		// find the number of pickups
		uint32_t numberOfActivePickups = 0;

		for (unsigned int i = 0; i < g_IPLsectionlimits.PickupsLimit; i++)
			if (g_IPLsectionlimits.CPickups__aPickUps.gta_sa[i].nbPickupType)
				numberOfActivePickups++;

		CGenericGameStorage::SaveDataToWorkBuffer(&numberOfActivePickups, sizeof(uint32_t));

		for (WORD i = 0; i < g_IPLsectionlimits.PickupsLimit; i++)
			if (g_IPLsectionlimits.CPickups__aPickUps.gta_sa[i].nbPickupType)
			{
				CGenericGameStorage::SaveDataToWorkBuffer(&i, sizeof(WORD));
				CGenericGameStorage::SaveDataToWorkBuffer(&g_IPLsectionlimits.CPickups__aPickUps.gta_sa[i], sizeof(CPickup_extended));
			}


		CGenericGameStorage::SaveDataToWorkBuffer((WORD*)0x978624, sizeof(WORD));	// CPickups::CollectedPickUpIndex

		CGenericGameStorage::SaveDataToWorkBuffer((BYTE*)0x8A5F48, sizeof(BYTE));	// CPickups::DisplayHelpMessage

		// pickups collected
		CGenericGameStorage::SaveDataToWorkBuffer(&g_IPLsectionlimits.PickupsCollectedLimit, sizeof(uint32_t));

		CGenericGameStorage::SaveDataToWorkBuffer(
			g_IPLsectionlimits.CPickups__aPickUpsCollected.ptr,
			sizeof(uint32_t) * g_IPLsectionlimits.PickupsCollectedLimit);

		return true;
	}

	// CPickups::Load replacement
	bool CPickups__Load()
	{
		*(WORD*)0x978678 = 0;	// CPickups::NumMessages

		CPickup_extended firstPickup;

		CGenericGameStorage::LoadDataFromWorkBuffer(&firstPickup, sizeof(CPickup));

		if (firstPickup.nbPickupType == 0xFE)
		{
			if (!g_IPLsectionlimits.bPickupPatchEnabled)
			{
				printf_MessageBox("Selected savefile requires IPL pickups patch enabled.");
				return false;
			}

			uint32_t magicID;
			CGenericGameStorage::LoadDataFromWorkBuffer(&magicID, sizeof(uint32_t));

			if (magicID != '2REV')
			{
				printf_MessageBox("Wrong magic ID for pickups section in savefile: 0x%08X", magicID);
				return false;
			}

			uint32_t numberOfPickupsInSave;

			CGenericGameStorage::LoadDataFromWorkBuffer(&numberOfPickupsInSave, sizeof(uint32_t));

			CPickup_extended uselessPickup;

			memset(
				g_IPLsectionlimits.CPickups__aPickUps.gta_sa,
				NULL,
				sizeof(CPickup_extended) * g_IPLsectionlimits.PickupsLimit);

			for (unsigned int i = 0; i < numberOfPickupsInSave; i++)
			{
				WORD pickupID;
				CGenericGameStorage::LoadDataFromWorkBuffer(&pickupID, sizeof(WORD));

				if (pickupID < g_IPLsectionlimits.PickupsLimit)
				{
					CGenericGameStorage::LoadDataFromWorkBuffer(
						&g_IPLsectionlimits.CPickups__aPickUps.gta_sa[pickupID],
						sizeof(CPickup_extended)
					);

					FixLoadedPickup(&g_IPLsectionlimits.CPickups__aPickUps.gta_sa[pickupID]);
				}
				else
				{
					printf_MessageBox("Pickup ID = %d, but current pickup limit = %d\nDiscarding a pickup.");
					CGenericGameStorage::LoadDataFromWorkBuffer(&uselessPickup, sizeof(CPickup_extended));
				}
			}

			CGenericGameStorage::LoadDataFromWorkBuffer((uint16_t*)0x978624, sizeof(uint16_t));	// CPickups::CollectedPickUpIndex

			if (*(WORD*)0x978624 >= g_IPLsectionlimits.PickupsCollectedLimit)
				*(WORD*)0x978624 = 0;

			CGenericGameStorage::LoadDataFromWorkBuffer((uint8_t*)0x8A5F48, sizeof(uint8_t));	// CPickups::DisplayHelpMessage

			uint32_t savePickupsCollectedLimit;
			CGenericGameStorage::LoadDataFromWorkBuffer(&savePickupsCollectedLimit, sizeof(uint32_t));

			for (unsigned int i = 0; i < savePickupsCollectedLimit; i++)
			{
				uint32_t value;

				CGenericGameStorage::LoadDataFromWorkBuffer(&value, sizeof(uint32_t));

				if (i < g_IPLsectionlimits.PickupsCollectedLimit)
					g_IPLsectionlimits.CPickups__aPickUpsCollected.ptr[i] = value;
			}
		}
		else
		{
			// standard save section is going to be loaded
			if (g_IPLsectionlimits.bPickupPatchEnabled)
			{
				if (g_IPLsectionlimits.PickupsLimit < 620)
				{
					printf_MessageBox("Selected savefile has standard pickup section and requires a pickup limit to be 620 or higher.");
					return false;
				}

				CPickup_extended* pPickup = g_IPLsectionlimits.CPickups__aPickUps.gta_sa;

				memcpy(pPickup, &firstPickup, sizeof(CPickup));
				FixLoadedPickup(&g_IPLsectionlimits.CPickups__aPickUps.gta_sa[0]);
				ConvertStandardPickupToExtendedPickup(&g_IPLsectionlimits.CPickups__aPickUps.gta_sa[0]);

				for (int i = 1; i < 620; i++)
				{
					pPickup = g_IPLsectionlimits.CPickups__aPickUps.gta_sa + i;
					CGenericGameStorage::LoadDataFromWorkBuffer(pPickup, sizeof(CPickup));

					FixLoadedPickup(pPickup);
					ConvertStandardPickupToExtendedPickup(pPickup);
				}

				CGenericGameStorage::LoadDataFromWorkBuffer((uint16_t*)0x978624, sizeof(uint16_t));	// CPickups::CollectedPickUpIndex

				if (*(uint16_t*)0x978624 >= g_IPLsectionlimits.PickupsCollectedLimit)
					*(uint16_t*)0x978624 = 0;

				CGenericGameStorage::LoadDataFromWorkBuffer((uint8_t*)0x8A5F48, sizeof(uint8_t));	// CPickups::DisplayHelpMessage

				for (unsigned int i = 0; i < 20; i++)
				{
					uint32_t unused;

					if (i < g_IPLsectionlimits.PickupsCollectedLimit)
						CGenericGameStorage::LoadDataFromWorkBuffer(
							&g_IPLsectionlimits.CPickups__aPickUpsCollected.ptr[i],
							sizeof(uint32_t));
					else
						CGenericGameStorage::LoadDataFromWorkBuffer(
							&unused,
							sizeof(uint32_t));
				}
			}
			else
			{
				CPickup* pPickUpArray = (CPickup *)0x9788C0;

				CPickup* pPickup = pPickUpArray;

				memcpy(pPickup, &firstPickup, sizeof(CPickup));
				FixLoadedPickup(pPickup);

				for (int i = 1; i < 620; i++)
				{
					pPickup = pPickUpArray + i;
					CGenericGameStorage::LoadDataFromWorkBuffer(pPickup, sizeof(CPickup));

					FixLoadedPickup(pPickup);
				}

				CGenericGameStorage::LoadDataFromWorkBuffer((uint16_t*)0x978624, sizeof(uint16_t));	// CPickups::CollectedPickUpIndex
				CGenericGameStorage::LoadDataFromWorkBuffer((uint8_t*)0x8A5F48, sizeof(uint8_t));	// CPickups::DisplayHelpMessage

				for (unsigned int i = 0; i < 20; i++)
					CGenericGameStorage::LoadDataFromWorkBuffer(
						&g_IPLsectionlimits.CPickups__aPickUpsCollected.ptr[i],
						sizeof(uint32_t));
			}
		}

		return true;
	}
}
#endif

// Patches loading functions
void IPLsectionLimits::PatchSaveBlockLoadingFunctions()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		CPatch::RedirectCode(0x5D35A0, &CPickups__Load);
	}
	#endif
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_CAudioZones__RegisterAudioBox_50824B()
	{
		__asm
		{
			mov ecx, ebx;
			imul ecx, SIZE tAudioZoneBoxExtended;

			push 0x508251;
			retn;
		}
	}

	NAKED void patch_CAEAmbienceTrackManager__UpdateAmbienceTrackAndVolume_4D6F42()
	{
		__asm
		{
			imul eax, SIZE tAudioZoneBoxExtended;
			add eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_IPLsectionlimits, IPLsectionLimits, CAudioZones__m_aBoxes);
			mov cx, [eax + tAudioZoneBoxExtended::m_ID];

			push 0x4D6F4D;
			retn;
		}
	}

	NAKED void patch_CAEAudioEnvironment__GetReverbEnvironmentAndDepth_4D805E()
	{
		__asm
		{
			imul eax, SIZE tAudioZoneBoxExtended;
			add eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_IPLsectionlimits, IPLsectionLimits, CAudioZones__m_aBoxes);
			mov ax, [eax + tAudioZoneBoxExtended::m_ID];

			push 0x4D8069;
			retn;
		}
	}

	NAKED void patch_CAudioZones__Update_50880C()
	{
		__asm
		{
			add ecx, SIZE tAudioZoneBoxExtended * 4;
			cmp edx, edi;

			push 0x508811;
			retn;
		}
	}

	NAKED void patch_CAudioZones__Update_patch_508825()
	{
		__asm
		{
			mov ecx, esi;
			imul ecx, SIZE tAudioZoneBoxExtended;

			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_IPLsectionlimits, IPLsectionLimits, CAudioZones__m_aBoxes);
			lea ecx, [eax + ecx + tAudioZoneBox::m_Box];

			push 0x508830;
			retn;
		}
	}

	NAKED void patch_CAudioZones__Update_patch_50873A()
	{
		__asm
		{
			test[ecx + 3 * SIZE tAudioZoneBoxExtended + tAudioZoneBox::m_Flags - tAudioZoneBox::m_Box], bl;
			jz loopContinue;

			push 0x508743;
			retn;

		loopContinue:
			push 0x508806;
			retn;
		}
	}
}
#endif

// Patches interior occluders
void IPLsectionLimits::PatchInteriorOccluders()
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (CPatch::IsDebugModeActive())
			this->InteriorOccludersLimit = 40;
		else if (this->InteriorOccludersLimit > 40 || bCOccluderCoordLimitHackEnabled)
		{
			if (this->bCOccluderCoordLimitHackEnabled)
			{
				COcclusion__aInteriorOccluders.gta_sa_extended = new COccluderExtended[InteriorOccludersLimit];
				COcclusion__aInteriorOccluders.bIsAllocated.Set(true);
			}
			else
			{
				COcclusion__aInteriorOccluders.gta_sa = new COccluder[InteriorOccludersLimit];
				COcclusion__aInteriorOccluders.bIsAllocated.Set(true);
			}
		}

		// Patch references to COcclusion::aInteriorOccluders
		#if TRUE
		{
			CPatch::PatchPointer(0x71DF8C + 3, COcclusion__aInteriorOccluders.gta_sa);	// mov     word ptr ds:_ZN10COcclusion18aInteriorOccludersE.midX[esi], ax; COcclusion::aInteriorOccluders
			CPatch::PatchPointer(0x71DFA2 + 3, &COcclusion__aInteriorOccluders.gta_sa->midY);	// mov     ds:_ZN10COcclusion18aInteriorOccludersE.midY[esi], ax
			CPatch::PatchPointer(0x71DFB2 + 3, &COcclusion__aInteriorOccluders.gta_sa->midZ);	// mov     ds:_ZN10COcclusion18aInteriorOccludersE.midZ[esi], ax
			CPatch::PatchPointer(0x71DFC8 + 3, &COcclusion__aInteriorOccluders.gta_sa->widthY);	// mov     ds:_ZN10COcclusion18aInteriorOccludersE.widthY[esi], ax
			CPatch::PatchPointer(0x71DFDE + 3, &COcclusion__aInteriorOccluders.gta_sa->widthX);	// mov     ds:_ZN10COcclusion18aInteriorOccludersE.widthX[esi], ax
			CPatch::PatchPointer(0x71DFFA + 3, &COcclusion__aInteriorOccluders.gta_sa->height);	// mov     ds:_ZN10COcclusion18aInteriorOccludersE.height[esi], ax
			CPatch::PatchPointer(0x71E010 + 2, &COcclusion__aInteriorOccluders.gta_sa->rotation3);	// mov     ds:_ZN10COcclusion18aInteriorOccludersE.rotation3[esi], al
			CPatch::PatchPointer(0x71E025 + 2, &COcclusion__aInteriorOccluders.gta_sa->rotation2);	// mov     ds:_ZN10COcclusion18aInteriorOccludersE.rotation2[esi], al
			CPatch::PatchPointer(0x71E031 + 2, &COcclusion__aInteriorOccluders.gta_sa->rotation);	// mov     ds:_ZN10COcclusion18aInteriorOccludersE.rotation[esi], al
			CPatch::PatchPointer(0x7203FE + 1, COcclusion__aInteriorOccluders.gta_sa);	// mov     ebx, offset _ZN10COcclusion18aInteriorOccludersE; COcclusion::aInteriorOccluders
		}
		#endif

		// Set variable for automatic patch
		CCodeMover::SetVariable("NUMBER_OF_INTERIOR_OCCLUDERS", InteriorOccludersLimit);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddress(0x71DF65, 9, "\x01\x02\x81\xff\x05\x04NUMBER_OF_INTERIOR_OCCLUDERS\x00\x01\x02\x0F\x8D\x03\x3d\xe0\x71\x00\x00", 0x71DF6E);	// line 1, 0x71DCD0 - sub_71DCD0 : cmp     edi, 28h
		}
		#endif

		// Unset variable of automatic patch
		CCodeMover::DeleteVariable("NUMBER_OF_INTERIOR_OCCLUDERS");
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IPL:interior occluders to: %d", InteriorOccludersLimit);
	CGenericLogStorage::WriteLineSeparator();
}

// Patches occluders
void IPLsectionLimits::PatchOccluders()
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();
	
	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (CPatch::IsDebugModeActive())
			this->OccludersLimit = 1000;
		else if (this->OccludersLimit > 1000 || bCOccluderCoordLimitHackEnabled)
		{
			if (this->bCOccluderCoordLimitHackEnabled)
			{
				COcclusion__aOccluders.gta_sa_extended = new COccluderExtended[OccludersLimit];
				COcclusion__aOccluders.bIsAllocated.Set(true);
			}
			else
			{
				COcclusion__aOccluders.gta_sa = new COccluder[OccludersLimit];
				COcclusion__aOccluders.bIsAllocated.Set(true);
			}
		}

		// Patch references to COcclusion::aOccluders
		#if TRUE
		{
			CPatch::PatchPointer(0x71DE6D + 3, &COcclusion__aOccluders.gta_sa->midX);	// mov     word ptr ds:_ZN10COcclusion10aOccludersE.midX[esi], ax; COcclusion::aOccluders
			CPatch::PatchPointer(0x71DE83 + 3, &COcclusion__aOccluders.gta_sa->midY);	// mov     ds:_ZN10COcclusion10aOccludersE.midY[esi], ax
			CPatch::PatchPointer(0x71DE93 + 3, &COcclusion__aOccluders.gta_sa->midZ);	// mov     ds:_ZN10COcclusion10aOccludersE.midZ[esi], ax
			CPatch::PatchPointer(0x71DEA9 + 3, &COcclusion__aOccluders.gta_sa->widthY);	// mov     ds:_ZN10COcclusion10aOccludersE.widthY[esi], ax
			CPatch::PatchPointer(0x71DEBF + 3, &COcclusion__aOccluders.gta_sa->widthX);	// mov     ds:_ZN10COcclusion10aOccludersE.widthX[esi], ax
			CPatch::PatchPointer(0x71DEDB + 3, &COcclusion__aOccluders.gta_sa->height);	// mov     ds:_ZN10COcclusion10aOccludersE.height[esi], ax
			CPatch::PatchPointer(0x71DEF1 + 2, &COcclusion__aOccluders.gta_sa->rotation3);	// mov     ds:_ZN10COcclusion10aOccludersE.rotation3[esi], al
			CPatch::PatchPointer(0x71DF06 + 2, &COcclusion__aOccluders.gta_sa->rotation2);	// mov     ds:_ZN10COcclusion10aOccludersE.rotation2[esi], al
			CPatch::PatchPointer(0x71DF11 + 2, &COcclusion__aOccluders.gta_sa->rotation);	// mov     ds:_ZN10COcclusion10aOccludersE.rotation[esi], al
			CPatch::PatchPointer(0x71DF1F + 3, &COcclusion__aOccluders.gta_sa->flags);	// or      ds:_ZN10COcclusion10aOccludersE.flags[esi], 8000h
			CPatch::PatchPointer(0x71DF2A + 2, (void*)((int)&COcclusion__aOccluders.gta_sa->flags + 1));	// and     byte ptr (_ZN10COcclusion10aOccludersE.flags+1)[esi], 7Fh
			CPatch::PatchPointer(0x71DF33 + 3, &COcclusion__aOccluders.gta_sa->flags);	// mov     ax, ds:_ZN10COcclusion10aOccludersE.flags[esi]
			CPatch::PatchPointer(0x71DF4D + 3, &COcclusion__aOccluders.gta_sa->flags);	// xor     ds:_ZN10COcclusion10aOccludersE.flags[esi], ax
			CPatch::PatchPointer(0x720228 + 2, &COcclusion__aOccluders.gta_sa->midX);	// lea     ecx, _ZN10COcclusion10aOccludersE.midX[ebx]; COcclusion::aOccluders
			CPatch::PatchPointer(0x720247 + 3, &COcclusion__aOccluders.gta_sa->flags);	// mov     ax, ds:_ZN10COcclusion10aOccludersE.flags[ebx]
			CPatch::PatchPointer(0x72025E + 3, &COcclusion__aOccluders.gta_sa->flags);	// mov     dx, ds:_ZN10COcclusion10aOccludersE.flags[ebx]
			CPatch::PatchPointer(0x720270 + 4, &COcclusion__aOccluders.gta_sa->flags);	// xor     dx, ds:_ZN10COcclusion10aOccludersE.flags[eax*2]
			CPatch::PatchPointer(0x72027E + 4, &COcclusion__aOccluders.gta_sa->flags);	// xor     ds:_ZN10COcclusion10aOccludersE.flags[eax*2], dx
			CPatch::PatchPointer(0x720286 + 3, &COcclusion__aOccluders.gta_sa->flags);	// mov     si, ds:_ZN10COcclusion10aOccludersE.flags[ebx]
			CPatch::PatchPointer(0x720295 + 4, &COcclusion__aOccluders.gta_sa->flags);	// mov     dx, ds:_ZN10COcclusion10aOccludersE.flags[eax*2]
			CPatch::PatchPointer(0x7202B7 + 4, &COcclusion__aOccluders.gta_sa->flags);	// xor     ds:_ZN10COcclusion10aOccludersE.flags[eax*2], dx
			CPatch::PatchPointer(0x7202C4 + 3, &COcclusion__aOccluders.gta_sa->flags);	// mov     si, ds:_ZN10COcclusion10aOccludersE.flags[ebx]
			CPatch::PatchPointer(0x72031C + 3, &COcclusion__aOccluders.gta_sa->midX);	// lea     ecx, _ZN10COcclusion10aOccludersE.midX[ecx*2]; COcclusion::aOccluders
			CPatch::PatchPointer(0x720341 + 2, &COcclusion__aOccluders.gta_sa->midX);	// lea     ecx, _ZN10COcclusion10aOccludersE.midX[ebx]; COcclusion::aOccluders
			CPatch::PatchPointer(0x72035C + 3, &COcclusion__aOccluders.gta_sa->flags);	// mov     ax, ds:_ZN10COcclusion10aOccludersE.flags[ebx]
			CPatch::PatchPointer(0x720373 + 3, &COcclusion__aOccluders.gta_sa->flags);	// mov     dx, ds:_ZN10COcclusion10aOccludersE.flags[ebx]
			CPatch::PatchPointer(0x720385 + 4, &COcclusion__aOccluders.gta_sa->flags);	// xor     dx, ds:_ZN10COcclusion10aOccludersE.flags[eax*2]
			CPatch::PatchPointer(0x720393 + 4, &COcclusion__aOccluders.gta_sa->flags);	// xor     ds:_ZN10COcclusion10aOccludersE.flags[eax*2], dx
			CPatch::PatchPointer(0x72039B + 3, &COcclusion__aOccluders.gta_sa->flags);	// mov     si, ds:_ZN10COcclusion10aOccludersE.flags[ebx]
			CPatch::PatchPointer(0x7203AA + 4, &COcclusion__aOccluders.gta_sa->flags);	// mov     dx, ds:_ZN10COcclusion10aOccludersE.flags[eax*2]
			CPatch::PatchPointer(0x7203CC + 4, &COcclusion__aOccluders.gta_sa->flags);	// xor     ds:_ZN10COcclusion10aOccludersE.flags[eax*2], dx
			CPatch::PatchPointer(0x7203DA + 3, &COcclusion__aOccluders.gta_sa->flags);	// mov     si, ds:_ZN10COcclusion10aOccludersE.flags[ebx]
		}
		#endif

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(0x71DE43 + 2, OccludersLimit);
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}
	
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IPL:occluders to: %d", OccludersLimit);
	CGenericLogStorage::WriteLineSeparator();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	static NAKED void patch_COcclusion__AddOne_71DE53()
	{
		__asm
		{
			mov esi, edi;
			imul esi, SIZE COccluderExtended;
			mov eax, 858B90h;
			fmul[eax];

			push 0x71DE5E;
			retn;
		}
	}

	static NAKED void patch_COcclusion__AddOne_71DF72()
	{
		__asm
		{
			mov esi, edi;
			imul esi, SIZE COccluderExtended;
			mov eax, 858B90h;
			fmul[eax];

			push 0x71DF7D;
			retn;
		}
	}

	static NAKED void patch_COcclusion__ProcessBeforeRendering_720223()
	{
		__asm
		{
			mov ebx, eax;
			imul esi, SIZE COccluderExtended;

			// go back
			push 0x0720228;
			retn;
		}
	}

	static NAKED void patch_COcclusion__ProcessBeforeRendering_720380()
	{
		__asm
		{
			imul eax, SIZE COccluderExtended/2;
			sar     edx, 1;

			push 0x720385;
			retn;
		}
	}

	static NAKED void patch_COcclusion__ProcessBeforeRendering_7203A5()
	{
		__asm
		{
			xor     edx, edx;
			imul eax, SIZE COccluderExtended / 2;

			push 0x7203AA;
			retn;
		}
	}
}
#endif

// Patch COccluder coordinate limit
void IPLsectionLimits::PatchCOccluderCoordinateLimit()
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevelAndDisableDebugState();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	// Patch size
	{
		using namespace Game_GTASA;

		// COcclusion::AddOne
		{
			CPatch::RedirectCode(0x71DE53, &patch_COcclusion__AddOne_71DE53);
			CPatch::RedirectCode(0x71DF72, &patch_COcclusion__AddOne_71DF72);
		}

		// COcclusion::ProcessBeforeRendering
		{
			CPatch::RedirectCode(0x720223, &patch_COcclusion__ProcessBeforeRendering_720223);
			CPatch::RedirectCode(0x720380, &patch_COcclusion__ProcessBeforeRendering_720380);
			CPatch::RedirectCode(0x7203A5, &patch_COcclusion__ProcessBeforeRendering_7203A5);

			CPatch::PatchUINT8(0x720433 + 2, sizeof(COccluderExtended));
		}

		// Set variables for automatic patch
		#if TRUE
		{
			CCodeMover::SetVariable("COCCLUDER_EXCOORDS_OFFSET", offsetof(COccluderExtended, exMidX));

			CCodeMover::SetVariable(
				"COCCLUSION__AOCCLUDERS_EXCOORDS",
				&COcclusion__aOccluders.gta_sa_extended->exMidX
			);

			CCodeMover::SetVariable(
				"COCCLUSION__AINTERIOROCCLUDERS_EXCOORDS",
				&COcclusion__aInteriorOccluders.gta_sa_extended->exMidX
			);
		}
		#endif

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 33
			CCodeMover::FixOnAddressRel(0x71DE6D, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x00\x00\x00\x00\x02""COCCLUSION__AOCCLUDERS_EXCOORDS\x00\x00", 0x71DE74);	// line 1, 0x71DCD0 - _ZN10COcclusion6AddOneEfffffffffjb : mov     word ptr _ZN10COcclusion10aOccludersE.midX[esi], ax; COcclusion::aOccluders
			CCodeMover::FixOnAddressRel(0x71DE83, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x04\x00\x00\x00\x02""COCCLUSION__AOCCLUDERS_EXCOORDS\x00\x00", 0x71DE8A);	// line 2, 0x71DCD0 - _ZN10COcclusion6AddOneEfffffffffjb : mov     _ZN10COcclusion10aOccludersE.midY[esi], ax
			CCodeMover::FixOnAddressRel(0x71DE93, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x08\x00\x00\x00\x02""COCCLUSION__AOCCLUDERS_EXCOORDS\x00\x00", 0x71DE9A);	// line 3, 0x71DCD0 - _ZN10COcclusion6AddOneEfffffffffjb : mov     _ZN10COcclusion10aOccludersE.midZ[esi], ax
			CCodeMover::FixOnAddressRel(0x71DEA9, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x0C\x00\x00\x00\x02""COCCLUSION__AOCCLUDERS_EXCOORDS\x00\x00", 0x71DEB0);	// line 4, 0x71DCD0 - _ZN10COcclusion6AddOneEfffffffffjb : mov     _ZN10COcclusion10aOccludersE.widthY[esi], ax
			CCodeMover::FixOnAddressRel(0x71DEBF, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x10\x00\x00\x00\x02""COCCLUSION__AOCCLUDERS_EXCOORDS\x00\x00", 0x71DEC6);	// line 5, 0x71DCD0 - _ZN10COcclusion6AddOneEfffffffffjb : mov     _ZN10COcclusion10aOccludersE.widthX[esi], ax
			CCodeMover::FixOnAddressRel(0x71DEDB, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x14\x00\x00\x00\x02""COCCLUSION__AOCCLUDERS_EXCOORDS\x00\x00", 0x71DEE2);	// line 6, 0x71DCD0 - _ZN10COcclusion6AddOneEfffffffffjb : mov     _ZN10COcclusion10aOccludersE.height[esi], ax
			CCodeMover::FixOnAddressRel(0x71DF8C, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x00\x00\x00\x00\x02""COCCLUSION__AINTERIOROCCLUDERS_EXCOORDS\x00\x00", 0x71DF93);	// line 7, 0x71DCD0 - _ZN10COcclusion6AddOneEfffffffffjb : mov     word ptr _ZN10COcclusion18aInteriorOccludersE.midX[esi], ax; COcclusion::aInteriorOccluders
			CCodeMover::FixOnAddressRel(0x71DFA2, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x04\x00\x00\x00\x02""COCCLUSION__AINTERIOROCCLUDERS_EXCOORDS\x00\x00", 0x71DFA9);	// line 8, 0x71DCD0 - _ZN10COcclusion6AddOneEfffffffffjb : mov     _ZN10COcclusion18aInteriorOccludersE.midY[esi], ax
			CCodeMover::FixOnAddressRel(0x71DFB2, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x08\x00\x00\x00\x02""COCCLUSION__AINTERIOROCCLUDERS_EXCOORDS\x00\x00", 0x71DFB9);	// line 9, 0x71DCD0 - _ZN10COcclusion6AddOneEfffffffffjb : mov     _ZN10COcclusion18aInteriorOccludersE.midZ[esi], ax
			CCodeMover::FixOnAddressRel(0x71DFC8, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x0C\x00\x00\x00\x02""COCCLUSION__AINTERIOROCCLUDERS_EXCOORDS\x00\x00", 0x71DFCF);	// line 10, 0x71DCD0 - _ZN10COcclusion6AddOneEfffffffffjb : mov     _ZN10COcclusion18aInteriorOccludersE.widthY[esi], ax
			CCodeMover::FixOnAddressRel(0x71DFDE, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x10\x00\x00\x00\x02""COCCLUSION__AINTERIOROCCLUDERS_EXCOORDS\x00\x00", 0x71DFE5);	// line 11, 0x71DCD0 - _ZN10COcclusion6AddOneEfffffffffjb : mov     _ZN10COcclusion18aInteriorOccludersE.widthX[esi], ax
			CCodeMover::FixOnAddressRel(0x71DFFA, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x14\x00\x00\x00\x02""COCCLUSION__AINTERIOROCCLUDERS_EXCOORDS\x00\x00", 0x71E001);	// line 12, 0x71DCD0 - _ZN10COcclusion6AddOneEfffffffffjb : mov     _ZN10COcclusion18aInteriorOccludersE.height[esi], ax
			CCodeMover::FixOnAddressRel(0x71E5FA, 11, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x08\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x04\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x00\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x00", 0x71E605);	// line 13, 0x71E5D0 - _ZN9COccluder18ProcessOneOccluderEP15CActiveOccluder : movsx   eax, [esi+COccluder.midZ]
			CCodeMover::FixOnAddressRel(0x71E6A3, 12, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x14\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x10\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x0c\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x00", 0x71E6AF);	// line 14, 0x71E5D0 - _ZN9COccluder18ProcessOneOccluderEP15CActiveOccluder : movsx   eax, [esi+COccluder.height]
			CCodeMover::FixOnAddressRel(0x71E854, 8, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x0c\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x13\x04\x58\xE8\x31\x00\x00", 0x71E85C);	// line 15, 0x71E5D0 - _ZN9COccluder18ProcessOneOccluderEP15CActiveOccluder : movsx   eax, [esi+COccluder.widthY]
			CCodeMover::FixOnAddressRel(0x71E87B, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x10\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x13\x04\x7F\xE8\x31\x00\x00", 0x71E883);	// line 16, 0x71E5D0 - _ZN9COccluder18ProcessOneOccluderEP15CActiveOccluder : movsx   ecx, [esi+COccluder.widthX]
			CCodeMover::FixOnAddressRel(0x71E89E, 8, "\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x14\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x13\x04\xA2\xE8\x31\x00\x00", 0x71E8A6);	// line 17, 0x71E5D0 - _ZN9COccluder18ProcessOneOccluderEP15CActiveOccluder : movsx   edx, [esi+COccluder.height]
			CCodeMover::FixOnAddressRel(0x71E8F9, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x10\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x13\x04\xFD\xE8\x31\x00\x00", 0x71E901);	// line 18, 0x71E5D0 - _ZN9COccluder18ProcessOneOccluderEP15CActiveOccluder : movsx   ecx, [esi+COccluder.widthX]
			CCodeMover::FixOnAddressRel(0x71E949, 8, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x14\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x13\x04\x4D\xE9\x31\x00\x00", 0x71E951);	// line 19, 0x71E5D0 - _ZN9COccluder18ProcessOneOccluderEP15CActiveOccluder : movsx   eax, [esi+COccluder.height]
			CCodeMover::FixOnAddressRel(0x71F435, 6, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x10\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x01\x02\x0F\x8A\x15\x8b\xf4\x31\x00\x00", 0x71F43B);	// line 20, 0x71E5D0 - _ZN9COccluder18ProcessOneOccluderEP15CActiveOccluder : movsx   eax, [esi+COccluder.widthX]
			CCodeMover::FixOnAddressRel(0x71F47D, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x14\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x13\x04\x81\xF4\x31\x00\x00", 0x71F485);	// line 21, 0x71E5D0 - _ZN9COccluder18ProcessOneOccluderEP15CActiveOccluder : movsx   ecx, [esi+COccluder.height]
			CCodeMover::FixOnAddressRel(0x71F4E4, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x14\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x13\x04\xE8\xF4\x31\x00\x00", 0x71F4EC);	// line 22, 0x71E5D0 - _ZN9COccluder18ProcessOneOccluderEP15CActiveOccluder : movsx   ecx, [esi+COccluder.height]
			CCodeMover::FixOnAddressRel(0x71F511, 8, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x14\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x13\x04\x15\xF5\x31\x00\x00", 0x71F519);	// line 23, 0x71E5D0 - _ZN9COccluder18ProcessOneOccluderEP15CActiveOccluder : movsx   eax, [esi+COccluder.height]
			CCodeMover::FixOnAddressRel(0x71F572, 7, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x10\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x13\x03\x76\xF5\x31\x00\x00", 0x71F579);	// line 24, 0x71E5D0 - _ZN9COccluder18ProcessOneOccluderEP15CActiveOccluder : movsx   ecx, [esi+COccluder.widthX]
			CCodeMover::FixOnAddressRel(0x71F963, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x0c\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x01\x01\x8B\x01\x01\x51\x0c\x01\x01\x10\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x00", 0x71F96B);	// line 25, 0x71F960 - _ZN9COccluder10NearCameraEv : movsx   eax, [ecx+COccluder.widthY]
			CCodeMover::FixOnAddressRel(0x71F99C, 7, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x00\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x01\x01\x8B\x01\x01\x51\x0c\x01\x01\x04\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x00", 0x71F9A3);	// line 26, 0x71F960 - _ZN9COccluder10NearCameraEv : movsx   eax, [ecx+COccluder.midX]
			CCodeMover::FixOnAddressRel(0x71F9A7, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x08\x02""COCCLUDER_EXCOORDS_OFFSET\x00\x13\x04\xAB\xF9\x31\x00\x00", 0x71F9AF);	// line 27, 0x71F960 - _ZN9COccluder10NearCameraEv : movsx   eax, [ecx+COccluder.midZ]
		}
		#endif

		// Unset variables of automatic patch
		#if TRUE
		{
			CCodeMover::DeleteVariable("COCCLUDER_EXCOORDS_OFFSET");
			CCodeMover::DeleteVariable("COCCLUSION__AOCCLUDERS");
			CCodeMover::DeleteVariable("COCCLUSION__AINTERIOROCCLUDERS");
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"'IPL -> COccluder, apply coordinate limit patch' is enabled."
	);
}

// Patches audio zone boxes
void IPLsectionLimits::PatchAudioZoneBoxes()
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (CPatch::IsDebugModeActive())
		{
			this->AudioZoneBoxesLimit = 158;
			this->bAudioZonesBoxesCoordLimitHackEnabled = false;
		}
		else if (this->AudioZoneBoxesLimit > 158 || bAudioZonesBoxesCoordLimitHackEnabled)
		{
			if (bAudioZonesBoxesCoordLimitHackEnabled)
			{
				IPLsectionLimits::CAudioZones__m_aBoxes.ptr = new tAudioZoneBoxExtended[AudioZoneBoxesLimit];
				memset(CAudioZones__m_aBoxes.ptr, NULL, AudioZoneBoxesLimit * sizeof(tAudioZoneBoxExtended));
				CAudioZones__m_aBoxes.bIsAllocated.Set(true);
			}
			else
			{
				IPLsectionLimits::CAudioZones__m_aBoxes.ptr = new tAudioZoneBox[AudioZoneBoxesLimit];
				memset(CAudioZones__m_aBoxes.ptr, NULL, AudioZoneBoxesLimit * sizeof(tAudioZoneBox));
				CAudioZones__m_aBoxes.bIsAllocated.Set(true);
			}
		}

		// Patch references to CAudioZones::m_aBoxes
		#if TRUE
		{
			CPatch::PatchPointer(0x4D6F45 + 4, &((tAudioZoneBox*)CAudioZones__m_aBoxes.ptr)->m_ID);	// mov     cx, ds:_ZN11CAudioZones8m_aBoxesE.m_ID[eax*8]	; sub_4D6E60
			CPatch::PatchPointer(0x4D8061 + 4, &((tAudioZoneBox*)CAudioZones__m_aBoxes.ptr)->m_ID);	// mov     ax, ds:_ZN11CAudioZones8m_aBoxesE.m_ID[eax*8]	; sub_4D8010
			CPatch::PatchPointer(0x508253 + 2, CAudioZones__m_aBoxes.ptr);	// lea     esi, _ZN11CAudioZones8m_aBoxesE.m_Name[ecx]; CAudioZones::m_aBoxes	; sub_508240
			CPatch::PatchPointer(0x508280 + 3, &((tAudioZoneBox*)CAudioZones__m_aBoxes.ptr)->m_ID);	// mov     ds:_ZN11CAudioZones8m_aBoxesE.m_ID[ecx], ax	; sub_508240
			CPatch::PatchPointer(0x50828D + 3, &((tAudioZoneBox*)CAudioZones__m_aBoxes.ptr)->m_Flags);	// mov     dx, ds:_ZN11CAudioZones8m_aBoxesE.m_Flags[ecx]	; sub_508240
			CPatch::PatchPointer(0x508299 + 3, &((tAudioZoneBox*)CAudioZones__m_aBoxes.ptr)->m_Flags);	// mov     ds:_ZN11CAudioZones8m_aBoxesE.m_Flags[ecx], ax	; sub_508240
			CPatch::PatchPointer(0x50837F + 1, &((tAudioZoneBox*)CAudioZones__m_aBoxes.ptr)->m_Flags);	// mov     esi, offset _ZN11CAudioZones8m_aBoxesE.m_Flags	; sub_508320


			CPatch::PatchPointer(0x5084CC + 1, &((tAudioZoneBox*)CAudioZones__m_aBoxes.ptr)->m_Box);	// mov     ecx, offset _ZN11CAudioZones8m_aBoxesE.m_Box	; sub_5083C0
			CPatch::PatchPointer(0x508828 + 3, &((tAudioZoneBox*)CAudioZones__m_aBoxes.ptr)->m_Box);	// lea     ecx, _ZN11CAudioZones8m_aBoxesE.m_Box.m_vInf.x[ecx*8]	; sub_5083C0
		}
		#endif

		// Coordinate limit
		#if TRUE
		if (bAudioZonesBoxesCoordLimitHackEnabled)
		{
			// Patch the size of tAudioZoneBox
			#if TRUE
			{
				CPatch::RedirectCode(0x50824B, &patch_CAudioZones__RegisterAudioBox_50824B);
				CPatch::RedirectCode(0x4D6F42, &patch_CAEAmbienceTrackManager__UpdateAmbienceTrackAndVolume_4D6F42);
				CPatch::RedirectCode(0x4D805E, &patch_CAEAudioEnvironment__GetReverbEnvironmentAndDepth_4D805E);
				CPatch::PatchUINT8(0x5083B1 + 2, sizeof(tAudioZoneBoxExtended));	// add     esi, size tAudioZoneBox

				#if TRUE
				{
					CPatch::EnterNewLevel();
					//CPatch::EnableDebugMode();

					unsigned int sizeof_tAudioZoneBox = sizeof(tAudioZoneBoxExtended);
				
					CPatch::PatchUINT8(0x5084D1 + 2, ((int)&((tAudioZoneBoxExtended*)0)->m_Flags) - offsetof(tAudioZoneBox, m_Box));	// test    [ecx-2], bl	; sub_5083C0
					// CPatch::PatchUINT8(0x5084DA + 3, tAudioZoneBoxExtended - 2);	// movsx   eax, word ptr [ecx]	; sub_5083C0
					CPatch::PatchUINT8(0x5084FA + 3, ((int)&((tAudioZoneBoxExtended*)0)->m_Box.m_vSup.x) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+6]	; sub_5083C0
					CPatch::PatchUINT8(0x50851B + 3, ((int)&((tAudioZoneBoxExtended*)0)->m_Box.m_vInf.y) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+2]	; sub_5083C0
					CPatch::PatchUINT8(0x508538 + 3, ((int)&((tAudioZoneBoxExtended*)0)->m_Box.m_vSup.y) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+8]	; sub_5083C0
					CPatch::PatchUINT8(0x508555 + 3, ((int)&((tAudioZoneBoxExtended*)0)->m_Box.m_vInf.z) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+4]	; sub_5083C0
					CPatch::PatchUINT8(0x508572 + 3, ((int)&((tAudioZoneBoxExtended*)0)->m_Box.m_vSup.z) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+0Ah]	; sub_5083C0

					CPatch::PatchUINT8(0x50859C + 2, ((int)&((tAudioZoneBoxExtended*)0 + 1)->m_Flags) - offsetof(tAudioZoneBox, m_Box));	// test    [ecx+16h], bl	; sub_5083C0
					CPatch::PatchUINT8(0x5085A5 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 1)->m_Box.m_vInf.x) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+18h]	; sub_5083C0
					CPatch::PatchUINT8(0x5085C6 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 1)->m_Box.m_vSup.x) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+1Eh]	; sub_5083C0
					CPatch::PatchUINT8(0x5085E7 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 1)->m_Box.m_vInf.y) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+1Ah]	; sub_5083C0
					CPatch::PatchUINT8(0x508604 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 1)->m_Box.m_vSup.y) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+20h]	; sub_5083C0
					CPatch::PatchUINT8(0x508621 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 1)->m_Box.m_vInf.z) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+1Ch]	; sub_5083C0
					CPatch::PatchUINT8(0x50863E + 3, ((int)&((tAudioZoneBoxExtended*)0 + 1)->m_Box.m_vSup.z) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+22h]	; sub_5083C0

					CPatch::PatchUINT8(0x50866B + 2, ((int)&((tAudioZoneBoxExtended*)0 + 2)->m_Flags) - offsetof(tAudioZoneBox, m_Box));	// test    [ecx+2Eh], bl	; sub_5083C0
					CPatch::PatchUINT8(0x508674 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 2)->m_Box.m_vInf.x) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+30h]	; sub_5083C0
					CPatch::PatchUINT8(0x508695 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 2)->m_Box.m_vSup.x) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+36h]	; sub_5083C0
					CPatch::PatchUINT8(0x5086B6 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 2)->m_Box.m_vInf.y) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+32h]	; sub_5083C0
					CPatch::PatchUINT8(0x5086D3 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 2)->m_Box.m_vSup.y) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+38h]	; sub_5083C0
					CPatch::PatchUINT8(0x5086F0 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 2)->m_Box.m_vInf.z) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+34h]	; sub_5083C0
					CPatch::PatchUINT8(0x50870D + 3, ((int)&((tAudioZoneBoxExtended*)0 + 2)->m_Box.m_vSup.z) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+3Ah]	; sub_5083C0

					CPatch::PatchUINT8(0x50873A + 2, ((int)&((tAudioZoneBoxExtended*)0 + 3)->m_Flags) - offsetof(tAudioZoneBox, m_Box));	// test    [ecx+46h], bl	; sub_5083C0
					CPatch::PatchUINT8(0x508743 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 3)->m_Box.m_vInf.x) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+48h]	; sub_5083C0
					CPatch::PatchUINT8(0x508764 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 3)->m_Box.m_vSup.x) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+4Eh]	; sub_5083C0
					CPatch::PatchUINT8(0x508785 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 3)->m_Box.m_vInf.y) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+4Ah]	; sub_5083C0
					CPatch::PatchUINT8(0x5087A2 + 3, ((int)&((tAudioZoneBoxExtended*)0 + 3)->m_Box.m_vSup.y) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+50h]	; sub_5083C0
					CPatch::PatchUINT8(0x5087BF + 3, ((int)&((tAudioZoneBoxExtended*)0 + 3)->m_Box.m_vInf.z) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+4Ch]	; sub_5083C0
					CPatch::PatchUINT8(0x5087DC + 3, ((int)&((tAudioZoneBoxExtended*)0 + 3)->m_Box.m_vSup.z) - offsetof(tAudioZoneBox, m_Box));	// movsx   eax, word ptr [ecx+52h]	; sub_5083C0

					CPatch::RedirectCode(0x50880C, &patch_CAudioZones__Update_50880C);
					CPatch::PatchUINT8(0x5088FC + 2, sizeof_tAudioZoneBox);	// add     ecx, size tAudioZoneBox
				
					CPatch::RedirectCode(0x508825, &patch_CAudioZones__Update_patch_508825);

					CPatch::RedirectCode(0x50873A, &patch_CAudioZones__Update_patch_50873A);

					CPatch::LeaveThisLevel();
				}
				#endif

			}
			#endif

			#if FALSE
			{
				FILE* fp = fopen("audioZones.bin", "rb");
				fseek(fp, 0, SEEK_END);
				int filesize = ftell(fp);
				fseek(fp, 0, SEEK_SET);

				int numberOfBoxes = filesize / sizeof(tAudioZoneBox);

				tAudioZoneBox* DebugAudioBoxes = new tAudioZoneBox[numberOfBoxes];
				fread(DebugAudioBoxes, numberOfBoxes * sizeof(tAudioZoneBox), 1, fp);
				fclose(fp);

				CPatch::PatchPointer(0x5084CC + 1, &((tAudioZoneBox*)DebugAudioBoxes)->m_Box);	// mov     ecx, offset _ZN11CAudioZones8m_aBoxesE.m_Box	; sub_5083C0
				CPatch::PatchPointer(0x508828 + 3, &((tAudioZoneBox*)DebugAudioBoxes)->m_Box);	// lea     ecx, _ZN11CAudioZones8m_aBoxesE.m_Box.m_vInf.x[ecx*8]	; sub_5083C0
			}
			#endif
		
			// Set variables for automatic patch
			#if TRUE
			{
				CCodeMover::SetVariable("TAUDIOZONEBOX_EXBOX_OFFSET", offsetof(tAudioZoneBoxExtended, m_exBox));

				CCodeMover::SetVariable("TAUDIOZONEBOX_INDEX_1_EXBOX_OFFSET", (int)&(((tAudioZoneBoxExtended*)0 + 1)->m_Box));
				CCodeMover::SetVariable("TAUDIOZONEBOX_INDEX_2_EXBOX_OFFSET", (int)&(((tAudioZoneBoxExtended*)0 + 2)->m_Box));
				CCodeMover::SetVariable("TAUDIOZONEBOX_INDEX_3_EXBOX_OFFSET", (int)&(((tAudioZoneBoxExtended*)0 + 3)->m_Box));
			}
			#endif

			// Apply automatic patch
			#if TRUE
			{
				// Count of active addresses: 36
				CCodeMover::FixOnAddress(0x5082AF, 9, "\x01\x01\x89\x01\x01\x46\x0c\x01\x01\x00\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x01\x01\xE8\x03\x40\x1b\x82\x00\x00", 0x5082B8);	// line 1, 0x508240 - sub_508240 : mov     [esi+0Ch], ax
				CCodeMover::FixOnAddress(0x5082C2, 9, "\x01\x01\x89\x01\x01\x46\x0c\x01\x01\x04\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x01\x01\xE8\x03\x40\x1b\x82\x00\x00", 0x5082CB);	// line 2, 0x508240 - sub_508240 : mov     [esi+0Eh], ax
				CCodeMover::FixOnAddress(0x5082D5, 9, "\x01\x01\x89\x01\x01\x46\x0c\x01\x01\x08\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x01\x01\xE8\x03\x40\x1b\x82\x00\x00", 0x5082DE);	// line 3, 0x508240 - sub_508240 : mov     [esi+10h], ax
				CCodeMover::FixOnAddress(0x5082E8, 9, "\x01\x01\x89\x01\x01\x46\x0c\x01\x01\x0c\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x01\x01\xE8\x03\x40\x1b\x82\x00\x00", 0x5082F1);	// line 4, 0x508240 - sub_508240 : mov     [esi+12h], ax
				CCodeMover::FixOnAddress(0x5082FB, 9, "\x01\x01\x89\x01\x01\x46\x0c\x01\x01\x10\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x01\x01\xE8\x03\x40\x1b\x82\x00\x00", 0x508304);	// line 5, 0x508240 - sub_508240 : mov     [esi+14h], ax
				CCodeMover::FixOnAddress(0x508306, 5, "\x01\x01\x89\x01\x01\x46\x0c\x01\x01\x14\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x02\x01\x0A\x83\x50\x00\x00", 0x50830B);	// line 6, 0x508240 - sub_508240 : mov     [esi+16h], ax
				CCodeMover::FixOnAddress(0x5084DA, 7, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\xf4\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x02\x04\xDD\x84\x50\x00\x00", 0x5084E1);	// line 7, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx]
				CCodeMover::FixOnAddress(0x5084FA, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x00\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x02\x04\xFE\x84\x50\x00\x00", 0x508502);	// line 8, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+6]
				CCodeMover::FixOnAddress(0x50851B, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\xf8\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x02\x04\x1F\x85\x50\x00\x00", 0x508523);	// line 9, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+2]
				CCodeMover::FixOnAddress(0x508538, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x04\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x02\x04\x3C\x85\x50\x00\x00", 0x508540);	// line 10, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+8]
				CCodeMover::FixOnAddress(0x508555, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\xfc\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x02\x04\x59\x85\x50\x00\x00", 0x50855D);	// line 11, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+4]
				CCodeMover::FixOnAddress(0x508572, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x08\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x02\x04\x76\x85\x50\x00\x00", 0x50857A);	// line 12, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+0Ah]
				CCodeMover::FixOnAddress(0x5085A5, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\xf4\x02""TAUDIOZONEBOX_INDEX_1_EXBOX_OFFSET\x00\x02\x04\xA9\x85\x50\x00\x00", 0x5085AD);	// line 13, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+18h]
				CCodeMover::FixOnAddress(0x5085C6, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x00\x02""TAUDIOZONEBOX_INDEX_1_EXBOX_OFFSET\x00\x02\x04\xCA\x85\x50\x00\x00", 0x5085CE);	// line 14, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+1Eh]
				CCodeMover::FixOnAddress(0x5085E7, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\xf8\x02""TAUDIOZONEBOX_INDEX_1_EXBOX_OFFSET\x00\x02\x04\xEB\x85\x50\x00\x00", 0x5085EF);	// line 15, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+1Ah]
				CCodeMover::FixOnAddress(0x508604, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x04\x02""TAUDIOZONEBOX_INDEX_1_EXBOX_OFFSET\x00\x02\x04\x08\x86\x50\x00\x00", 0x50860C);	// line 16, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+20h]
				CCodeMover::FixOnAddress(0x508621, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\xfc\x02""TAUDIOZONEBOX_INDEX_1_EXBOX_OFFSET\x00\x02\x04\x25\x86\x50\x00\x00", 0x508629);	// line 17, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+1Ch]
				CCodeMover::FixOnAddress(0x50863E, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x08\x02""TAUDIOZONEBOX_INDEX_1_EXBOX_OFFSET\x00\x02\x04\x42\x86\x50\x00\x00", 0x508646);	// line 18, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+22h]
				CCodeMover::FixOnAddress(0x508674, 8, "\x01\x01\x8B\x01\x01\x81\x0d\x01\x04\xF4\xFF\xFF\xFF\x02""TAUDIOZONEBOX_INDEX_2_EXBOX_OFFSET\x00\x02\x04\x78\x86\x50\x00\x00", 0x50867C);	// line 19, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+30h]
				CCodeMover::FixOnAddress(0x508695, 8, "\x01\x01\x8B\x01\x01\x81\x0d\x01\x04\x00\x00\x00\x00\x02""TAUDIOZONEBOX_INDEX_2_EXBOX_OFFSET\x00\x02\x04\x99\x86\x50\x00\x00", 0x50869D);	// line 20, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+36h]
				CCodeMover::FixOnAddress(0x5086B6, 8, "\x01\x01\x8B\x01\x01\x81\x0d\x01\x04\xF8\xFF\xFF\xFF\x02""TAUDIOZONEBOX_INDEX_2_EXBOX_OFFSET\x00\x02\x04\xBA\x86\x50\x00\x00", 0x5086BE);	// line 21, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+32h]
				CCodeMover::FixOnAddress(0x5086D3, 8, "\x01\x01\x8B\x01\x01\x81\x0d\x01\x04\x04\x00\x00\x00\x02""TAUDIOZONEBOX_INDEX_2_EXBOX_OFFSET\x00\x02\x04\xD7\x86\x50\x00\x00", 0x5086DB);	// line 22, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+38h]
				CCodeMover::FixOnAddress(0x5086F0, 8, "\x01\x01\x8B\x01\x01\x81\x0d\x01\x04\xFC\xFF\xFF\xFF\x02""TAUDIOZONEBOX_INDEX_2_EXBOX_OFFSET\x00\x02\x04\xF4\x86\x50\x00\x00", 0x5086F8);	// line 23, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+34h]
				CCodeMover::FixOnAddress(0x50870D, 8, "\x01\x01\x8B\x01\x01\x81\x0d\x01\x04\x08\x00\x00\x00\x02""TAUDIOZONEBOX_INDEX_2_EXBOX_OFFSET\x00\x02\x04\x11\x87\x50\x00\x00", 0x508715);	// line 24, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+3Ah]
				CCodeMover::FixOnAddress(0x508743, 8, "\x01\x01\x8B\x01\x01\x81\x0d\x01\x04\xF4\xFF\xFF\xFF\x02""TAUDIOZONEBOX_INDEX_3_EXBOX_OFFSET\x00\x02\x04\x47\x87\x50\x00\x00", 0x50874B);	// line 25, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+48h]
				CCodeMover::FixOnAddress(0x508764, 8, "\x01\x01\x8B\x01\x01\x81\x0d\x01\x04\x00\x00\x00\x00\x02""TAUDIOZONEBOX_INDEX_3_EXBOX_OFFSET\x00\x02\x04\x68\x87\x50\x00\x00", 0x50876C);	// line 26, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+4Eh]
				CCodeMover::FixOnAddress(0x508785, 8, "\x01\x01\x8B\x01\x01\x81\x0d\x01\x04\xF8\xFF\xFF\xFF\x02""TAUDIOZONEBOX_INDEX_3_EXBOX_OFFSET\x00\x02\x04\x89\x87\x50\x00\x00", 0x50878D);	// line 27, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+4Ah]
				CCodeMover::FixOnAddress(0x5087A2, 8, "\x01\x01\x8B\x01\x01\x81\x0d\x01\x04\x04\x00\x00\x00\x02""TAUDIOZONEBOX_INDEX_3_EXBOX_OFFSET\x00\x02\x04\xA6\x87\x50\x00\x00", 0x5087AA);	// line 28, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+50h]
				CCodeMover::FixOnAddress(0x5087BF, 8, "\x01\x01\x8B\x01\x01\x81\x0d\x01\x04\xFC\xFF\xFF\xFF\x02""TAUDIOZONEBOX_INDEX_3_EXBOX_OFFSET\x00\x02\x04\xC3\x87\x50\x00\x00", 0x5087C7);	// line 29, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+4Ch]
				CCodeMover::FixOnAddress(0x5087DC, 8, "\x01\x01\x8B\x01\x01\x81\x0d\x01\x04\x08\x00\x00\x00\x02""TAUDIOZONEBOX_INDEX_3_EXBOX_OFFSET\x00\x02\x04\xE0\x87\x50\x00\x00", 0x5087E4);	// line 30, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+52h]
				CCodeMover::FixOnAddress(0x508839, 7, "\x01\x01\x8B\x01\x01\x51\x0c\x01\x01\xf4\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x02\x04\x3C\x88\x50\x00\x00", 0x508840);	// line 31, 0x5083C0 - sub_5083C0 : movsx   edx, word ptr [ecx]
				CCodeMover::FixOnAddress(0x508859, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x00\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x02\x04\x5D\x88\x50\x00\x00", 0x508861);	// line 32, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+6]
				CCodeMover::FixOnAddress(0x50887A, 8, "\x01\x01\x8B\x01\x01\x51\x0c\x01\x01\xf8\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x02\x04\x7E\x88\x50\x00\x00", 0x508882);	// line 33, 0x5083C0 - sub_5083C0 : movsx   edx, word ptr [ecx+2]
				CCodeMover::FixOnAddress(0x508897, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x04\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x02\x04\x9B\x88\x50\x00\x00", 0x50889F);	// line 34, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+8]
				CCodeMover::FixOnAddress(0x5088B4, 8, "\x01\x01\x8B\x01\x01\x51\x0c\x01\x01\xfc\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x02\x04\xB8\x88\x50\x00\x00", 0x5088BC);	// line 35, 0x5083C0 - sub_5083C0 : movsx   edx, word ptr [ecx+4]
				CCodeMover::FixOnAddress(0x5088D1, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x08\x02""TAUDIOZONEBOX_EXBOX_OFFSET\x00\x02\x04\xD5\x88\x50\x00\x00", 0x5088D9);	// line 36, 0x5083C0 - sub_5083C0 : movsx   eax, word ptr [ecx+0Ah]
			}
			#endif

			// Unset variables of automatic patch
			#if TRUE
			{
				CCodeMover::DeleteVariable("TAUDIOZONEBOX_EXBOX_OFFSET");

				CCodeMover::DeleteVariable("TAUDIOZONEBOX_INDEX_1_EXBOX_OFFSET");
				CCodeMover::DeleteVariable("TAUDIOZONEBOX_INDEX_2_EXBOX_OFFSET");
				CCodeMover::DeleteVariable("TAUDIOZONEBOX_INDEX_3_EXBOX_OFFSET");
			}
			#endif
		
			// disable optimized loop
			CPatch::RedirectCode(0x5084BE, 0x50881D);
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of IPL:AUZO boxes to: %d Is extended structure used: %d",
		this->AudioZoneBoxesLimit,
		this->bAudioZonesBoxesCoordLimitHackEnabled
		);
	CGenericLogStorage::WriteLineSeparator();	
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	int __cdecl GetIndexFromMultipliedSizeOfCPickupInfo(int value)
	{
		return value / sizeof(CPickup_extended);
	}

	NAKED void patch_CPickup__Remove_4556CA()
	{
		__asm
		{
			push eax;
			call GetIndexFromMultipliedSizeOfCPickupInfo;
			add esp, 4;

			movzx   edx, word ptr[esi + CPickup::wGeneration];

			push 0x4556D9;
			retn;
		}		
	}

	NAKED void patch_CPickups__PictureTaken_456C02()
	{
		__asm
		{
			push eax;
			call GetIndexFromMultipliedSizeOfCPickupInfo;
			add esp, 4;

			movzx   ecx, word ptr[esi + CPickup::wGeneration];

			push 0x456C11;
			retn;
		}
	}

	NAKED void patch_CPickups__RemoveMissionPickUps_456DF8()
	{
		__asm
		{
			push eax;
			call GetIndexFromMultipliedSizeOfCPickupInfo;
			add esp, 4;

			movzx   edx, word ptr[esi + CPickup::wGeneration - CPickup::pObject];

			push 0x456E07;
			retn;
		}
	}

	NAKED void patch_CPickups__ReInit_456E7A()
	{
		__asm
		{
			push eax;
			call GetIndexFromMultipliedSizeOfCPickupInfo;
			add esp, 4;

			movzx   edx, word ptr[esi + CPickup::wGeneration - CPickup::pObject];

			push 0x456E89;
			retn;
		}
	}

	NAKED void patch_CPickups__Update_458E17()
	{
		__asm
		{
			push eax;

			push edi;
			call GetIndexFromMultipliedSizeOfCPickupInfo;
			add esp, 4;

			mov edi, eax;

			pop eax;

			push eax;
			call GetIndexFromMultipliedSizeOfCPickupInfo;
			add esp, 4;
		
			push 0x458E1D;
			retn;
		}
	}

	#define MAKE_CODE_FOR_PATCH_456F70(multiplier, labelName) \
	__asm cmp     byte ptr[eax + multiplier * SIZE CPickup_extended], 0 \
	__asm jz labelName

	NAKED void patch_CPickups__GenerateNewOne_456F70()
	{
		MAKE_CODE_FOR_PATCH_456F70(-1, zero);
		MAKE_CODE_FOR_PATCH_456F70(0, one);
		MAKE_CODE_FOR_PATCH_456F70(1, two);
		MAKE_CODE_FOR_PATCH_456F70(2, three);
		MAKE_CODE_FOR_PATCH_456F70(3, four);
		MAKE_CODE_FOR_PATCH_456F70(4, five);
		MAKE_CODE_FOR_PATCH_456F70(5, six);
		MAKE_CODE_FOR_PATCH_456F70(6, seven);
		MAKE_CODE_FOR_PATCH_456F70(7, eight);
		MAKE_CODE_FOR_PATCH_456F70(8, nine);

		__asm
		{
			push 0x456FBA;
			retn;

		zero:
			push 0x456FF4;
			retn;

		one:
			push 0x456FCB;
			retn;

		two:
			push 0x456FCE;
			retn;

		three:
			push 0x456FD3;
			retn;

		four:
			push 0x456FD8;
			retn;

		five:
			push 0x456FDD;
			retn;

		six:
			push 0x456FE2;
			retn;

		seven:
			push 0x456FE7;
			retn;

		eight:
			push 0x456FEC;
			retn;

		nine:
			push 0x456FF1;
			retn;

		}
	}

	#define MAKE_CODE_FOR_PATCH_457007(multiplier, labelName) \
	__asm cmp     byte ptr[eax + multiplier * SIZE CPickup_extended], 8 \
	__asm jz labelName

	NAKED void patch_CPickups__GenerateNewOne_457007()
	{
		MAKE_CODE_FOR_PATCH_457007(-1, zero);
		MAKE_CODE_FOR_PATCH_457007(0, one);
		MAKE_CODE_FOR_PATCH_457007(1, two);
		MAKE_CODE_FOR_PATCH_457007(2, three);
		MAKE_CODE_FOR_PATCH_457007(3, four);
		MAKE_CODE_FOR_PATCH_457007(4, five);
		MAKE_CODE_FOR_PATCH_457007(5, six);
		MAKE_CODE_FOR_PATCH_457007(6, seven);
		MAKE_CODE_FOR_PATCH_457007(7, eight);
		MAKE_CODE_FOR_PATCH_457007(8, nine);

		__asm
		{
			push 0x457051;
			retn;

		zero:
			push 0x45708B;
			retn;

		one:
			push 0x457062;
			retn;

		two:
			push 0x457065;
			retn;

		three:
			push 0x45706A;
			retn;

		four:
			push 0x45706F;
			retn;

		five:
			push 0x457074;
			retn;

		six:
			push 0x457079;
			retn;

		seven:
			push 0x45707E;
			retn;

		eight:
			push 0x457083;
			retn;

		nine:
			push 0x457088;
			retn;
		}
	}

	#define MAKE_CODE_FOR_PATCH_4570A0(multiplier, labelName) \
	__asm mov     cl, [eax + multiplier * SIZE CPickup_extended] \
	\
	__asm cmp     cl, 4 \
	__asm jz labelName \
	__asm cmp cl, 5 \
	__asm jz labelName

	NAKED void patch_CPickups__GenerateNewOne_4570A0()
	{
		MAKE_CODE_FOR_PATCH_4570A0(-1, zero);
		MAKE_CODE_FOR_PATCH_4570A0(0, one);
		MAKE_CODE_FOR_PATCH_4570A0(1, two);
		MAKE_CODE_FOR_PATCH_4570A0(2, three);
		MAKE_CODE_FOR_PATCH_4570A0(3, four);
		MAKE_CODE_FOR_PATCH_4570A0(4, five);
		MAKE_CODE_FOR_PATCH_4570A0(5, six);
		MAKE_CODE_FOR_PATCH_4570A0(6, seven);
		MAKE_CODE_FOR_PATCH_4570A0(7, eight);
		MAKE_CODE_FOR_PATCH_4570A0(8, nine);

		__asm
		{
			push 0x45714C;
			retn;

		zero:
			push 0x45718E;
			retn;

		one:
			push 0x457165;
			retn;

		two:
			push 0x457168;
			retn;

		three:
			push 0x45716D;
			retn;

		four:
			push 0x457172;
			retn;

		five:
			push 0x457177;
			retn;

		six:
			push 0x45717C;
			retn;

		seven:
			push 0x457181;
			retn;

		eight:
			push 0x457186;
			retn;

		nine:
			push 0x45718B;
			retn;			
		}
	}
}
#endif

// Patches pickups
void IPLsectionLimits::PatchPickups()
{
	MAKE_VAR_GAME_VERSION();

	if (gameVersion != GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		return;

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	#ifdef IS_PLATFORM_WIN_X86
	using namespace Game_GTASA;
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	unsigned int sizeof_CPickup;

	bool bShouldSaveBeEnhanced = false;

	// Set up the main variables
	#if TRUE
	if (CPatch::IsDebugModeActive())
	{
		CPickups__aPickUps.gta_sa = (CPickup_extended*)0x9788C0;
		sizeof_CPickup = sizeof(CPickup);
		PickupsLimit = 620;
		PickupsCollectedLimit = 20;
	}
	else
	{
		bShouldSaveBeEnhanced = true;

		CPickups__aPickUps.gta_sa = new CPickup_extended[PickupsLimit];
		memset(CPickups__aPickUps.gta_sa, NULL, PickupsLimit * sizeof(CPickup_extended));
		CPickups__aPickUps.bIsAllocated.Set(true);

		sizeof_CPickup = sizeof(CPickup_extended);

		if (PickupsCollectedLimit > 127)
			throw f92_runtime_error("'Pickup collected' limit may not be higher than 127.");

		if (PickupsCollectedLimit > 20)
		{
			CPickups__aPickUpsCollected.ptr = new uint32_t[PickupsCollectedLimit];
			CPickups__aPickUpsCollected.bIsAllocated.Set(true);
		}
	}
	#endif

	// Patch references to CPickups::aPickUps
	#if TRUE
	{
		CPatch::PatchPointer(0x4020BB + 1, CPickups__aPickUps.gta_sa);	// sub     eax, offset _ZN8CPickups8aPickUpsE; CPickups::aPickUps	; sub_4556C0
		CPatch::PatchPointer(0x455204 + 1, &CPickups__aPickUps.gta_sa->regenerationTime);	// mov     eax, offset _ZN8CPickups8aPickUpsE.regenerationTime	; sub_4414C0
		CPatch::PatchPointer(0x455471 + 1, &CPickups__aPickUps.gta_sa->pObject);	// mov     esi, offset _ZN8CPickups8aPickUpsE.pObject	; sub_455470
		CPatch::PatchPointer(0x4555BD + 1, &CPickups__aPickUps.gta_sa->pos.y);	// mov     ecx, offset _ZN8CPickups8aPickUpsE.pos.y	; sub_4555A0
		CPatch::PatchPointer(0x455664 + 2, &CPickups__aPickUps.gta_sa->field_8);	// lea     eax, _ZN8CPickups8aPickUpsE.field_8[edx]	; sub_4555A0
		CPatch::PatchPointer(0x4556D2 + 3, &CPickups__aPickUps.gta_sa->wGeneration);	// movzx   edx, ds:_ZN8CPickups8aPickUpsE.wGeneration[ecx]	; sub_4556C0
		CPatch::PatchPointer(0x4563A9 + 1, &CPickups__aPickUps.gta_sa->pos.y);	// mov     esi, offset _ZN8CPickups8aPickUpsE.pos.y	; sub_4563A0
		CPatch::PatchPointer(0x456453 + 1, &CPickups__aPickUps.gta_sa->pos.y);	// mov     ecx, offset _ZN8CPickups8aPickUpsE.pos.y	; sub_456450
		CPatch::PatchPointer(0x456A39 + 2, &CPickups__aPickUps.gta_sa->wGeneration);	// lea     eax, _ZN8CPickups8aPickUpsE.wGeneration[eax]	; sub_456A30
		CPatch::PatchPointer(0x456A83 + 1, &CPickups__aPickUps.gta_sa->pos.y);	// mov     esi, offset _ZN8CPickups8aPickUpsE.pos.y	; sub_456A70
		CPatch::PatchPointer(0x456BF3 + 2, CPickups__aPickUps.gta_sa);	// add     edi, offset _ZN8CPickups8aPickUpsE; CPickups::aPickUps	; sub_456A70
		CPatch::PatchPointer(0x456BFD + 1, CPickups__aPickUps.gta_sa);	// sub     eax, offset _ZN8CPickups8aPickUpsE; CPickups::aPickUps	; sub_456A70
		CPatch::PatchPointer(0x456C0A + 3, &CPickups__aPickUps.gta_sa->wGeneration);	// movzx   ecx, ds:_ZN8CPickups8aPickUpsE.wGeneration[edx]	; sub_456A70
		CPatch::PatchPointer(0x456D32 + 1, &CPickups__aPickUps.gta_sa->pos);	// mov     esi, offset _ZN8CPickups8aPickUpsE.pos	; sub_456D30
		CPatch::PatchPointer(0x456DE2 + 1, &CPickups__aPickUps.gta_sa->pObject);	// mov     esi, offset _ZN8CPickups8aPickUpsE.pObject	; sub_456DE0
		CPatch::PatchPointer(0x456E00 + 3, &CPickups__aPickUps.gta_sa->wGeneration);	// movzx   edx, ds:_ZN8CPickups8aPickUpsE.wGeneration[ecx]	; sub_456DE0
		CPatch::PatchPointer(0x456E6C + 1, &CPickups__aPickUps.gta_sa->pObject);	// mov     esi, offset _ZN8CPickups8aPickUpsE.pObject	; sub_456E60
		CPatch::PatchPointer(0x456E82 + 3, &CPickups__aPickUps.gta_sa->wGeneration);	// movzx   edx, ds:_ZN8CPickups8aPickUpsE.wGeneration[ecx]	; sub_456E60
		CPatch::PatchPointer(0x456ED6 + 1, &CPickups__aPickUps.gta_sa->wGeneration);	// mov     eax, offset _ZN8CPickups8aPickUpsE.wGeneration	; sub_456E60
		CPatch::PatchPointer(0x456F43 + 1, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*(PickupsLimit - 1)))->nbPickupType);	// mov     eax, (offset _ZN8CPickups8aPickUpsE.nbPickupType+4D60h)	; sub_456F20
		CPatch::PatchPointer(0x456F51 + 1, &CPickups__aPickUps.gta_sa->nbPickupType);	// cmp     eax, offset _ZN8CPickups8aPickUpsE.nbPickupType	; sub_456F20
		CPatch::PatchPointer(0x456F64 + 1, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup)) ->nbPickupType);	// mov     eax, (offset _ZN8CPickups8aPickUpsE.nbPickupType+20h)	; sub_456F20
		CPatch::PatchPointer(0x457002 + 1, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup))->nbPickupType);	// mov     eax, (offset _ZN8CPickups8aPickUpsE.nbPickupType+20h)	; sub_456F20
		CPatch::PatchPointer(0x457099 + 1, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup))->nbPickupType);	// mov     eax, (offset _ZN8CPickups8aPickUpsE.nbPickupType+20h)	; sub_456F20
		CPatch::PatchPointer(0x45719F + 2, CPickups__aPickUps.gta_sa);	// add     esi, offset _ZN8CPickups8aPickUpsE; CPickups::aPickUps	; sub_456F20
		CPatch::PatchPointer(0x4571E8 + 2, &CPickups__aPickUps.gta_sa->field_8);	// mov     ds:_ZN8CPickups8aPickUpsE.field_8[esi], eax	; sub_456F20
		CPatch::PatchPointer(0x4571F3 + 3, &CPickups__aPickUps.gta_sa->field_16);	// mov     ds:_ZN8CPickups8aPickUpsE.field_16[esi], ax	; sub_456F20
		CPatch::PatchPointer(0x4571FA + 2, &CPickups__aPickUps.gta_sa->flags);	// mov     al, ds:_ZN8CPickups8aPickUpsE.flags[esi]	; sub_456F20
		CPatch::PatchPointer(0x457214 + 2, &CPickups__aPickUps.gta_sa->field_0);	// lea     edi, _ZN8CPickups8aPickUpsE.field_0[esi]; CPickups::aPickUps	; sub_456F20
		CPatch::PatchPointer(0x45721A + 2, &CPickups__aPickUps.gta_sa->nbPickupType);	// mov     ds:_ZN8CPickups8aPickUpsE.nbPickupType[esi], cl	; sub_456F20
		CPatch::PatchPointer(0x457226 + 2, &CPickups__aPickUps.gta_sa->regenerationTime);	// mov     ds:_ZN8CPickups8aPickUpsE.regenerationTime[esi], ebp	; sub_456F20
		CPatch::PatchPointer(0x45722C + 2, &CPickups__aPickUps.gta_sa->flags);	// mov     ds:_ZN8CPickups8aPickUpsE.flags[esi], dl	; sub_456F20
		CPatch::PatchPointer(0x457266 + 2, &CPickups__aPickUps.gta_sa->nbPickupType);	// mov     ds:_ZN8CPickups8aPickUpsE.nbPickupType[esi], 9	; sub_456F20
		CPatch::PatchPointer(0x45726D + 2, &CPickups__aPickUps.gta_sa->regenerationTime);	// mov     ds:_ZN8CPickups8aPickUpsE.regenerationTime[esi], edx	; sub_456F20
		CPatch::PatchPointer(0x45727D + 2, &CPickups__aPickUps.gta_sa->nbPickupType);	// mov     ds:_ZN8CPickups8aPickUpsE.nbPickupType[esi], 0Bh	; sub_456F20
		CPatch::PatchPointer(0x45728A + 2, &CPickups__aPickUps.gta_sa->regenerationTime);	// mov     ds:_ZN8CPickups8aPickUpsE.regenerationTime[esi], ebp	; sub_456F20
		CPatch::PatchPointer(0x45729A + 3, &CPickups__aPickUps.gta_sa->wModelID);	// mov     ds:_ZN8CPickups8aPickUpsE.wModelID[esi], ax	; sub_456F20
		CPatch::PatchPointer(0x4572AA + 2, &CPickups__aPickUps.gta_sa->flags);	// mov     cl, ds:_ZN8CPickups8aPickUpsE.flags[esi]	; sub_456F20
		CPatch::PatchPointer(0x4572C2 + 2, &CPickups__aPickUps.gta_sa->flags);	// mov     ds:_ZN8CPickups8aPickUpsE.flags[esi], cl	; sub_456F20
		CPatch::PatchPointer(0x4572FE + 2, &CPickups__aPickUps.gta_sa->flags);	// mov     cl, ds:_ZN8CPickups8aPickUpsE.flags[esi]	; sub_456F20
		CPatch::PatchPointer(0x457313 + 2, &CPickups__aPickUps.gta_sa->pObject);	// lea     ebp, _ZN8CPickups8aPickUpsE.pObject[esi]	; sub_456F20
		CPatch::PatchPointer(0x457319 + 2, &CPickups__aPickUps.gta_sa->flags);	// mov     ds:_ZN8CPickups8aPickUpsE.flags[esi], dl	; sub_456F20
		CPatch::PatchPointer(0x457344 + 3, &CPickups__aPickUps.gta_sa->wGeneration);	// mov     ax, ds:_ZN8CPickups8aPickUpsE.wGeneration[esi]	; sub_456F20
		CPatch::PatchPointer(0x457354 + 3, &CPickups__aPickUps.gta_sa->wGeneration);	// mov     ds:_ZN8CPickups8aPickUpsE.wGeneration[esi], ax	; sub_456F20
		CPatch::PatchPointer(0x457366 + 3, &CPickups__aPickUps.gta_sa->wGeneration);	// mov     ds:_ZN8CPickups8aPickUpsE.wGeneration[esi], 1	; sub_456F20
		CPatch::PatchPointer(0x45736F + 3, &CPickups__aPickUps.gta_sa->wGeneration);	// movzx   eax, ds:_ZN8CPickups8aPickUpsE.wGeneration[esi]	; sub_456F20
		CPatch::PatchPointer(0x4573E8 + 3, &CPickups__aPickUps.gta_sa->wGeneration);	// cmp     cx, ds:_ZN8CPickups8aPickUpsE.wGeneration[edx]	; sub_4573D0
		CPatch::PatchPointer(0x4573F6 + 2, &CPickups__aPickUps.gta_sa->field_0);	// lea     ecx, _ZN8CPickups8aPickUpsE.field_0[edx]; CPickups::aPickUps	; sub_4573D0
		CPatch::PatchPointer(0x458E2A + 2, &CPickups__aPickUps.gta_sa->pObject);	// add     esi, offset _ZN8CPickups8aPickUpsE.pObject	; sub_458DE0
		CPatch::PatchPointer(0x458FE4 + 2, &CPickups__aPickUps.gta_sa->nbPickupType);	// add     esi, offset _ZN8CPickups8aPickUpsE.nbPickupType	; sub_458DE0
		CPatch::PatchPointer(0x4590CB + 1, CPickups__aPickUps.gta_sa);	// mov     esi, offset _ZN8CPickups8aPickUpsE; CPickups::aPickUps	; sub_4590C0
		CPatch::PatchPointer(0x4590E2 + 2, ((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit)));	// cmp     esi, offset dword_97D640	; sub_4590C0
		CPatch::PatchPointer(0x47AC91 + 1, CPickups__aPickUps.gta_sa);	// mov     edi, offset _ZN8CPickups8aPickUpsE; CPickups::aPickUps	; sub_47A760
		CPatch::PatchPointer(0x48ADC2 + 1, CPickups__aPickUps.gta_sa);	// mov     edi, offset _ZN8CPickups8aPickUpsE; CPickups::aPickUps	; sub_48A320
		CPatch::PatchPointer(0x494725 + 2, CPickups__aPickUps.gta_sa);	// add     ecx, offset _ZN8CPickups8aPickUpsE; CPickups::aPickUps	; sub_493FE0
		CPatch::PatchPointer(0x585F08 + 2, CPickups__aPickUps.gta_sa);	// add     ecx, offset _ZN8CPickups8aPickUpsE; CPickups::aPickUps	; sub_585BF0
		CPatch::PatchPointer(0x587110 + 1, CPickups__aPickUps.gta_sa);	// add     eax, offset _ZN8CPickups8aPickUpsE; CPickups::aPickUps	; sub_587000
		CPatch::PatchPointer(0x5D3542 + 1, CPickups__aPickUps.gta_sa);	// mov     esi, offset _ZN8CPickups8aPickUpsE; CPickups::aPickUps	; sub_5D3540
		CPatch::PatchPointer(0x5D3555 + 2, ((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit)));	// cmp     esi, offset dword_97D640	; sub_5D3540
		// CPatch::PatchPointer(0x5D35A2 + 1, &CPickups__aPickUps.gta_sa->pObject);	// mov     esi, offset _ZN8CPickups8aPickUpsE.pObject	; sub_5D35A0
		CPatch::PatchPointer(0x1561589 + 3, &CPickups__aPickUps.gta_sa->wGeneration);	// movzx   edx, ds:_ZN8CPickups8aPickUpsE.wGeneration[ecx]	; sub_1561580
		CPatch::PatchPointer(0x1564659 + 1, &CPickups__aPickUps.gta_sa->wGeneration);	// mov     eax, offset _ZN8CPickups8aPickUpsE.wGeneration	; sub_1564650
		CPatch::PatchPointer(0x1564BC8 + 3, &CPickups__aPickUps.gta_sa->wGeneration);	// cmp     cx, ds:_ZN8CPickups8aPickUpsE.wGeneration[edx]	; sub_1564BB0
		CPatch::PatchPointer(0x156B378 + 3, &CPickups__aPickUps.gta_sa->wGeneration);	// cmp     cx, ds:_ZN8CPickups8aPickUpsE.wGeneration[edx]	; sub_156B360
		CPatch::PatchPointer(0x156B38B + 3, &CPickups__aPickUps.gta_sa->field_16);	// mov     ds:_ZN8CPickups8aPickUpsE.field_16[edx], ax	; sub_156B360
		CPatch::PatchPointer(0x156D876 + 1, &CPickups__aPickUps.gta_sa->pObject);	// mov     ecx, offset _ZN8CPickups8aPickUpsE.pObject	; sub_156D870
		CPatch::PatchPointer(0x156D896 + 1, CPickups__aPickUps.gta_sa);	// mov     eax, offset _ZN8CPickups8aPickUpsE; CPickups::aPickUps	; sub_156D870
		CPatch::PatchPointer(0x156D8A0 + 1, CPickups__aPickUps.gta_sa);	// add     eax, offset _ZN8CPickups8aPickUpsE; CPickups::aPickUps	; sub_156D870

		CPatch::PatchPointer(0x455231 + 1, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit))->regenerationTime);	// cmp     eax, offset flt_97D64C	; sub_4414C0
		CPatch::PatchPointer(0x4554A9 + 2, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit))->pObject);	// cmp     esi, offset dword_97D644	; sub_455470
		CPatch::PatchPointer(0x455649 + 2, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit))->pos.y);	// cmp     ecx, (offset flt_97D650+2)	; sub_4555A0
		CPatch::PatchPointer(0x456436 + 2, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit))->pos.y);	// cmp     esi, (offset flt_97D650+2)	; sub_4563A0
		CPatch::PatchPointer(0x4564D7 + 2, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit))->pos.y);	// cmp     ecx, (offset flt_97D650+2)	; sub_456450
		CPatch::PatchPointer(0x456BDC + 2, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit))->pos.y);	// cmp     esi, (offset flt_97D650+2)	; sub_456A70
		CPatch::PatchPointer(0x456DD1 + 2, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit))->pos);	// cmp     esi, offset flt_97D650	; sub_456D30
		CPatch::PatchPointer(0x456E4A + 2, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit))->pObject);	// cmp     esi, offset dword_97D644	; sub_456DE0
		CPatch::PatchPointer(0x456EC7 + 2, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit))->pObject);	// cmp     esi, offset dword_97D644	; sub_456E60
		CPatch::PatchPointer(0x456EEE + 1, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit))->wGeneration);	// cmp     eax, (offset flt_97D658+2)	; sub_456E60
		CPatch::PatchPointer(0x5D35D2 + 2, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit))->pObject);	// cmp     esi, offset dword_97D644	; sub_5D35A0
		CPatch::PatchPointer(0x156466E + 1, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit))->wGeneration);	// cmp     eax, (offset flt_97D658+2)	; sub_1564650
		CPatch::PatchPointer(0x156D88E + 2, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*PickupsLimit))->pObject);	// cmp     ecx, offset dword_97D644	; sub_156D870

		CPatch::PatchPointer(0x456FC2 + 1, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*(PickupsLimit + 1)))->nbPickupType);	// cmp     eax, offset unk_97D67C
		CPatch::PatchPointer(0x457059 + 1, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*(PickupsLimit + 1)))->nbPickupType);	// cmp     eax, offset unk_97D67C
		CPatch::PatchPointer(0x457154 + 1, &((CPickup*)((char*)CPickups__aPickUps.gta_sa + sizeof_CPickup*(PickupsLimit + 1)))->nbPickupType);	// cmp     eax, offset unk_97D67C
	}
	#endif

	// Patch the number of pickups (620)
	#if TRUE
	{
		CPatch::PatchUINT32(0x456FF4 + 2, PickupsLimit);	// cmp     ebx, 26Ch	; sub_456F20
		CPatch::PatchUINT32(0x45708B + 2, PickupsLimit);	// cmp     ebx, 620	; sub_456F20
		CPatch::PatchUINT32(0x45718E + 2, PickupsLimit);	// cmp     ebx, 26Ch	; sub_456F20
		CPatch::PatchUINT32(0x4571D1 + 2, PickupsLimit);	// cmp     ebx, 26Ch	; sub_456F20
		CPatch::PatchUINT32(0x458DF7 + 2, PickupsLimit);	// imul    ecx, 26Ch	; sub_458DE0
		CPatch::PatchUINT32(0x458E0B + 2, PickupsLimit);	// lea     eax, [ecx+26Ch]	; sub_458DE0
		CPatch::PatchUINT32(0x458FB0 + 2, PickupsLimit);	// imul    ecx, 26Ch	; sub_458DE0
		CPatch::PatchUINT32(0x458FBF + 2, PickupsLimit);	// add     ecx, 26Ch	; sub_458DE0
	}
	#endif

	// Patch the number of pickups minus one (620 - 1)
	#if TRUE
	{
		CPatch::PatchUINT32(0x456F3E + 1, PickupsLimit - 1);	// mov     ebx, 26Bh	; sub_456F20
	}
	#endif

	// Patch references to CPickups::aPickUpsCollected
	#if TRUE
	{
		CPatch::PatchPointer(0x456EFC + 1, CPickups__aPickUpsCollected.ptr);	// mov     edi, offset _ZN8CPickups17aPickUpsCollectedE; CPickups::aPickUpsCollected	; sub_456E60
		CPatch::PatchPointer(0x45904F + 3, CPickups__aPickUpsCollected.ptr);	// mov     ds:_ZN8CPickups17aPickUpsCollectedE[edx*4], ecx; CPickups::aPickUpsCollected	; sub_458DE0
		CPatch::PatchPointer(0x5D3578 + 1, CPickups__aPickUpsCollected.ptr);	// mov     esi, offset _ZN8CPickups17aPickUpsCollectedE; CPickups::aPickUpsCollected	; sub_5D3540
		CPatch::PatchPointer(0x5D35FE + 1, CPickups__aPickUpsCollected.ptr);	// mov     esi, offset _ZN8CPickups17aPickUpsCollectedE; CPickups::aPickUpsCollected	; sub_5D35A0
		CPatch::PatchPointer(0x15615A4 + 3, CPickups__aPickUpsCollected.ptr);	// mov     ds:_ZN8CPickups17aPickUpsCollectedE[ecx*4], edx; CPickups::aPickUpsCollected	; sub_1561580
		CPatch::PatchPointer(0x156467D + 1, CPickups__aPickUpsCollected.ptr);	// mov     edi, offset _ZN8CPickups17aPickUpsCollectedE; CPickups::aPickUpsCollected	; sub_1564650
		CPatch::PatchPointer(0x156DA66 + 3, CPickups__aPickUpsCollected.ptr);	// cmp     ds:_ZN8CPickups17aPickUpsCollectedE[eax*4], ecx; CPickups::aPickUpsCollected	; sub_156DA60
		CPatch::PatchPointer(0x156DA78 + 3, CPickups__aPickUpsCollected.ptr);	// mov     ds:_ZN8CPickups17aPickUpsCollectedE[eax*4], 0; CPickups::aPickUpsCollected	; sub_156DA60
	}
	#endif

	// Patch the number of pickups collected
	#if TRUE
	{
		CPatch::PatchUINT32(0x1564676 + 1, PickupsCollectedLimit);	// mov     ecx, 20

		CPatch::PatchUINT8(0x156DA70 + 2, PickupsCollectedLimit);	// cmp     eax, 20

		CPatch::PatchUINT8(0x15615A0 + 3, PickupsCollectedLimit);	// cmp     ax, 20

		CPatch::PatchUINT32(0x456EF5 + 1, PickupsCollectedLimit);	// mov     ecx, 20

		CPatch::PatchUINT16(0x45904B + 2, PickupsCollectedLimit);	// cmp     ax, 20			
	}
	#endif
	
	// Patch the size of CPickup and coordinate limit
	#if TRUE
	if (!CPatch::IsDebugModeActive())
	{
		// size of CPickup
		#if TRUE
		{
			CPatch::PatchUINT8(0x45522E + 2, sizeof_CPickup);	// add     eax, 20h	; sub_4414C0
			CPatch::PatchUINT8(0x4554A6 + 2, sizeof_CPickup);	// add     esi, 20h	; sub_455470
			CPatch::PatchUINT8(0x455645 + 2, sizeof_CPickup);	// add     ecx, 20h	; sub_4555A0
			CPatch::PatchUINT8(0x456433 + 2, sizeof_CPickup);	// add     esi, 20h	; sub_4563A0
			CPatch::PatchUINT8(0x4564D4 + 2, sizeof_CPickup);	// add     ecx, 20h	; sub_456450
			CPatch::PatchUINT8(0x456BD8 + 2, sizeof_CPickup);	// add     esi, 20h	; sub_456A70
			CPatch::PatchUINT8(0x456DCE + 2, sizeof_CPickup);	// add     esi, 20h	; sub_456D30
			CPatch::PatchUINT8(0x456E44 + 2, sizeof_CPickup);	// add     esi, 20h	; sub_456DE0
			CPatch::PatchUINT8(0x456E47 + 2, sizeof_CPickup);	// add     edi, 20h	; sub_456DE0
			CPatch::PatchUINT8(0x456EC1 + 2, sizeof_CPickup);	// add     esi, 20h	; sub_456E60
			CPatch::PatchUINT8(0x456EC4 + 2, sizeof_CPickup);	// add     edi, 20h	; sub_456E60
			CPatch::PatchUINT8(0x456EEB + 2, sizeof_CPickup);	// add     eax, 20h	; sub_456E60
			CPatch::PatchUINT8(0x456F4D + 2, sizeof_CPickup);	// sub     eax, 32	; sub_456F20
			CPatch::PatchUINT32(0x456FBA + 1, sizeof_CPickup * 10);	// add     eax, 140h	; sub_456F20
			CPatch::PatchUINT32(0x457051 + 1, sizeof_CPickup * 10);	// add     eax, 140h	; sub_456F20
			CPatch::PatchUINT32(0x45714C + 1, sizeof_CPickup * 10);	// add     eax, 140h	; sub_456F20
			CPatch::PatchUINT8(0x458EA4 + 2, sizeof_CPickup);	// add     esi, 20h	; sub_458DE0
			CPatch::PatchUINT8(0x4590A8 + 2, sizeof_CPickup);	// add     esi, 20h	; sub_458DE0
			CPatch::PatchUINT8(0x4590DF + 2, sizeof_CPickup);	// add     esi, 20h	; sub_4590C0
			CPatch::PatchUINT8(0x47ACEB + 2, sizeof_CPickup);	// add     ebp, 20h	; sub_47A760
			CPatch::PatchUINT8(0x47ACEE + 2, sizeof_CPickup);	// add     edi, 20h	; sub_47A760
			CPatch::PatchUINT8(0x48AE37 + 2, sizeof_CPickup);	// add     ebp, 20h	; sub_48A320
			CPatch::PatchUINT8(0x48AE3A + 2, sizeof_CPickup);	// add     edi, 20h	; sub_48A320
			CPatch::PatchUINT8(0x5D354F + 2, sizeof_CPickup);	// add     esi, 20h	; sub_5D3540
			CPatch::PatchUINT8(0x5D35CF + 2, sizeof_CPickup);	// add     esi, 20h	; sub_5D35A0
			CPatch::PatchUINT8(0x156466B + 2, sizeof_CPickup);	// add     eax, 20h	; sub_1564650
			CPatch::PatchUINT8(0x156D88A + 2, sizeof_CPickup);	// add     ecx, 20h	; sub_156D870
		}
		#endif

		// sizeof(CPickup) * 620
		#if TRUE
		{
			CPatch::PatchUINT32(0x47ACF1 + 2, PickupsLimit * sizeof_CPickup);	// cmp     ebp, 19840	; sub_47A760
			CPatch::PatchUINT32(0x48AE3D + 2, PickupsLimit * sizeof_CPickup);	// cmp     ebp, 19840	; sub_48A320
		}
		#endif

		// Patch sar, 5
		#if TRUE
		if(!CPatch::IsDebugModeActive())
		{
			CPatch::RedirectCode(0x4556CA, &patch_CPickup__Remove_4556CA);
			CPatch::RedirectCode(0x456C02, &patch_CPickups__PictureTaken_456C02);
			CPatch::RedirectCode(0x456DF8, &patch_CPickups__RemoveMissionPickUps_456DF8);
			CPatch::RedirectCode(0x456E7A, &patch_CPickups__ReInit_456E7A);
			CPatch::RedirectCode(0x458E17, &patch_CPickups__Update_458E17);
		}
		#endif
		
		// Patch some code
		#if TRUE
		{
			CPatch::RedirectCode(0x456F70, &patch_CPickups__GenerateNewOne_456F70);
			CPatch::RedirectCode(0x457007, &patch_CPickups__GenerateNewOne_457007);
			CPatch::RedirectCode(0x4570A0, &patch_CPickups__GenerateNewOne_4570A0);
		}
		#endif

		// Set variables for automatic patch
		#if TRUE
		{
			CCodeMover::SetVariable("SIZEOF_CPICKUP", sizeof_CPickup);
			CCodeMover::SetVariable("CPICKUP_EXPOS_OFFSET", offsetof(CPickup_extended, exPos));
		}
		#endif

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 56
			CCodeMover::FixOnAddress(0x4549A1, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x08\x02""CPICKUP_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x51\x0c\x01\x01\x04\x02""CPICKUP_EXPOS_OFFSET\x00\x00", 0x4549A9);	// line 1, 0x4549A0 - sub_4549A0 : movsx   eax, word ptr [ecx+14h]
			CCodeMover::FixOnAddress(0x4549AD, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x00\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\xB1\x49\x45\x00\x00", 0x4549B5);	// line 2, 0x4549A0 - sub_4549A0 : movsx   eax, word ptr [ecx+10h]
			CCodeMover::FixOnAddress(0x4549F1, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x00\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\xF5\x49\x45\x00\x00", 0x4549F9);	// line 3, 0x4549F0 - sub_4549F0 : movsx   eax, word ptr [ecx+10h]
			CCodeMover::FixOnAddress(0x454A11, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x04\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\x15\x4A\x45\x00\x00", 0x454A19);	// line 4, 0x454A10 - sub_454A10 : movsx   eax, word ptr [ecx+12h]
			CCodeMover::FixOnAddress(0x454A31, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x08\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\x35\x4A\x45\x00\x00", 0x454A39);	// line 5, 0x454A30 - sub_454A30 : movsx   eax, word ptr [ecx+14h]
			CCodeMover::FixOnAddress(0x454C73, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x00\x02""CPICKUP_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x49\x0c\x01\x01\x04\x02""CPICKUP_EXPOS_OFFSET\x00\x00", 0x454C7B);	// line 6, 0x454C70 - sub_454C70 : movsx   eax, word ptr [ecx+10h]
			CCodeMover::FixOnAddress(0x4555CF, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\xee\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\xD3\x55\x45\x00\x00", 0x4555D7);	// line 7, 0x4555A0 - sub_4555A0 : movsx   eax, word ptr [ecx-2]
			CCodeMover::FixOnAddress(0x4555D7, 7, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\xf2\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\xDA\x55\x45\x00\x00", 0x4555DE);	// line 8, 0x4555A0 - sub_4555A0 : movsx   eax, word ptr [ecx]
			CCodeMover::FixOnAddress(0x4555E2, 10, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\xf6\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x06\xE6\x55\x45\x00\x00", 0x4555EC);	// line 9, 0x4555A0 - sub_4555A0 : movsx   eax, word ptr [ecx+2]
			CCodeMover::FixOnAddress(0x455661, 9, "\x0e\x02\x02""SIZEOF_CPICKUP\x00\x02\x06\x64\x56\x45\x00\x00", 0x45566A);	// line 10, 0x4555A0 - sub_4555A0 : shl     edx, 5
			CCodeMover::FixOnAddress(0x4556CF, 10, "\x0e\x01\x02""SIZEOF_CPICKUP\x00\x02\x07\xD2\x56\x45\x00\x00", 0x4556D9);	// line 11, 0x4556C0 - sub_4556C0 : shl     ecx, 5
			CCodeMover::FixOnAddress(0x4563BB, 7, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\xee\x02""CPICKUP_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\xf2\x02""CPICKUP_EXPOS_OFFSET\x00\x00", 0x4563C2);	// line 12, 0x4563A0 - sub_4563A0 : movsx   eax, word ptr [esi-2]
			CCodeMover::FixOnAddress(0x4563C2, 8, "\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\xf6\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\xC6\x63\x45\x00\x00", 0x4563CA);	// line 13, 0x4563A0 - sub_4563A0 : movsx   edx, word ptr [esi+2]
			CCodeMover::FixOnAddress(0x456460, 7, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\xee\x02""CPICKUP_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x51\x0c\x01\x01\xf2\x02""CPICKUP_EXPOS_OFFSET\x00\x00", 0x456467);	// line 14, 0x456450 - sub_456450 : movsx   eax, word ptr [ecx-2]
			CCodeMover::FixOnAddress(0x45646B, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\xf6\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\x6F\x64\x45\x00\x00", 0x456473);	// line 15, 0x456450 - sub_456450 : movsx   eax, word ptr [ecx+2]
			CCodeMover::FixOnAddress(0x456A36, 9, "\x0e\x00\x02""SIZEOF_CPICKUP\x00\x02\x06\x39\x6A\x45\x00\x00", 0x456A3F);	// line 16, 0x456A30 - sub_456A30 : shl     eax, 5
			CCodeMover::FixOnAddress(0x456AAD, 7, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\xee\x02""CPICKUP_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\xf2\x02""CPICKUP_EXPOS_OFFSET\x00\x00", 0x456AB4);	// line 17, 0x456A70 - sub_456A70 : movsx   ecx, word ptr [esi-2]
			CCodeMover::FixOnAddress(0x456AB8, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\xf6\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\xBC\x6A\x45\x00\x00", 0x456AC0);	// line 18, 0x456A70 - sub_456A70 : movsx   ecx, word ptr [esi+2]
			CCodeMover::FixOnAddress(0x456B3B, 7, "\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\xee\x02""CPICKUP_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\xf2\x02""CPICKUP_EXPOS_OFFSET\x00\x00", 0x456B42);	// line 19, 0x456A70 - sub_456A70 : movsx   edx, word ptr [esi-2]
			CCodeMover::FixOnAddress(0x456B42, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\xf6\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\x46\x6B\x45\x00\x00", 0x456B4A);	// line 20, 0x456A70 - sub_456A70 : movsx   ecx, word ptr [esi+2]
			CCodeMover::FixOnAddress(0x456BF0, 9, "\x0e\x07\x02""SIZEOF_CPICKUP\x00\x02\x06\xF3\x6B\x45\x00\x00", 0x456BF9);	// line 21, 0x456A70 - sub_456A70 : shl     edi, 5
			CCodeMover::FixOnAddress(0x456C07, 10, "\x0e\x02\x02""SIZEOF_CPICKUP\x00\x02\x07\x0A\x6C\x45\x00\x00", 0x456C11);	// line 22, 0x456A70 - sub_456A70 : shl     edx, 5
			CCodeMover::FixOnAddress(0x456D4B, 7, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\xf0\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\x4E\x6D\x45\x00\x00", 0x456D52);	// line 23, 0x456D30 - sub_456D30 : movsx   eax, word ptr [esi]
			CCodeMover::FixOnAddress(0x456D72, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\xf4\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\x76\x6D\x45\x00\x00", 0x456D7A);	// line 24, 0x456D30 - sub_456D30 : movsx   ecx, word ptr [esi+2]
			CCodeMover::FixOnAddress(0x456D9A, 8, "\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\xf8\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\x9E\x6D\x45\x00\x00", 0x456DA2);	// line 25, 0x456D30 - sub_456D30 : movsx   edx, word ptr [esi+4]
			CCodeMover::FixOnAddress(0x456DFD, 10, "\x0e\x01\x02""SIZEOF_CPICKUP\x00\x02\x07\x00\x6E\x45\x00\x00", 0x456E07);	// line 26, 0x456DE0 - sub_456DE0 : shl     ecx, 5
			CCodeMover::FixOnAddress(0x456E7F, 10, "\x0e\x01\x02""SIZEOF_CPICKUP\x00\x02\x07\x82\x6E\x45\x00\x00", 0x456E89);	// line 27, 0x456E60 - sub_456E60 : shl     ecx, 5
			CCodeMover::FixOnAddress(0x45719C, 9, "\x0e\x06\x02""SIZEOF_CPICKUP\x00\x02\x06\x9F\x71\x45\x00\x00", 0x4571A5);	// line 28, 0x456F20 - sub_456F20 : shl     esi, 5
			CCodeMover::FixOnAddress(0x4571E5, 9, "\x0e\x06\x02""SIZEOF_CPICKUP\x00\x02\x06\xE8\x71\x45\x00\x00", 0x4571EE);	// line 29, 0x456F20 - sub_456F20 : shl     esi, 5
			CCodeMover::FixOnAddress(0x4572D7, 9, "\x01\x01\x89\x01\x01\x47\x0c\x01\x01\x00\x02""CPICKUP_EXPOS_OFFSET\x00\x01\x01\xE8\x03\x40\x1b\x82\x00\x00", 0x4572E0);	// line 30, 0x456F20 - sub_456F20 : mov     [edi+10h], ax
			CCodeMover::FixOnAddress(0x4572EA, 9, "\x01\x01\x89\x01\x01\x47\x0c\x01\x01\x04\x02""CPICKUP_EXPOS_OFFSET\x00\x01\x01\xE8\x03\x40\x1b\x82\x00\x00", 0x4572F3);	// line 31, 0x456F20 - sub_456F20 : mov     [edi+12h], ax
			CCodeMover::FixOnAddress(0x4572F5, 9, "\x01\x01\x89\x01\x01\x47\x0c\x01\x01\x08\x02""CPICKUP_EXPOS_OFFSET\x00\x01\x01\xE8\x03\x70\x4c\x45\x00\x00", 0x4572FE);	// line 32, 0x456F20 - sub_456F20 : mov     [edi+14h], ax
			CCodeMover::FixOnAddress(0x4573E2, 6, "\x0e\x02\x02""SIZEOF_CPICKUP\x00\x02\x03\xE5\x73\x45\x00\x00", 0x4573E8);	// line 33, 0x4573D0 - sub_4573D0 : shl     edx, 5
			CCodeMover::FixOnAddress(0x45742C, 8, "\x01\x01\x8B\x01\x01\x4B\x0c\x01\x01\x00\x02""CPICKUP_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x53\x0c\x01\x01\x04\x02""CPICKUP_EXPOS_OFFSET\x00\x00", 0x457434);	// line 34, 0x457410 - sub_457410 : movsx   ecx, word ptr [ebx+10h]
			CCodeMover::FixOnAddress(0x457438, 8, "\x01\x01\x8B\x01\x01\x4B\x0c\x01\x01\x08\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\x3C\x74\x45\x00\x00", 0x457440);	// line 35, 0x457410 - sub_457410 : movsx   ecx, word ptr [ebx+14h]
			CCodeMover::FixOnAddress(0x4574AD, 6, "\x01\x01\x8B\x01\x01\x53\x0c\x01\x01\x08\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x02\xB1\x74\x45\x00\x00", 0x4574B3);	// line 36, 0x457410 - sub_457410 : movsx   edx, word ptr [ebx+14h]
			CCodeMover::FixOnAddress(0x4574B6, 8, "\x01\x01\x8B\x01\x01\x43\x0c\x01\x01\x00\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x04\xBA\x74\x45\x00\x00", 0x4574BE);	// line 37, 0x457410 - sub_457410 : movsx   eax, word ptr [ebx+10h]
			CCodeMover::FixOnAddress(0x4574C4, 10, "\x01\x01\x8B\x01\x01\x4B\x0c\x01\x01\x04\x02""CPICKUP_EXPOS_OFFSET\x00\x02\x06\xC8\x74\x45\x00\x00", 0x4574CE);	// line 38, 0x457410 - sub_457410 : movsx   ecx, word ptr [ebx+12h]
			CCodeMover::FixOnAddress(0x45874E, 8, "\x01\x01\x8B\x01\x01\x4B\x0c\x01\x01\x00\x02""CPICKUP_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x53\x0c\x01\x01\x04\x02""CPICKUP_EXPOS_OFFSET\x00\x00", 0x458756);	// line 39, 0x457410 - sub_457410 : movsx   ecx, word ptr [ebx+10h]
			CCodeMover::FixOnAddress(0x458E27, 9, "\x0e\x06\x02""SIZEOF_CPICKUP\x00\x02\x06\x2A\x8E\x45\x00\x00", 0x458E30);	// line 40, 0x458DE0 - sub_458DE0 : shl     esi, 5
			CCodeMover::FixOnAddress(0x458FE1, 9, "\x0e\x06\x02""SIZEOF_CPICKUP\x00\x02\x06\xE4\x8F\x45\x00\x00", 0x458FEA);	// line 41, 0x458DE0 - sub_458DE0 : shl     esi, 5
			CCodeMover::FixOnAddress(0x494722, 9, "\x0e\x01\x02""SIZEOF_CPICKUP\x00\x02\x06\x25\x47\x49\x00\x00", 0x49472B);	// line 42, 0x493FE0 - sub_493FE0 : shl     ecx, 5
			CCodeMover::FixOnAddress(0x585F04, 10, "\x0e\x01\x02""SIZEOF_CPICKUP\x00\x02\x01\x07\x5F\x58\x00\x02\x06\x08\x5F\x58\x00\x00", 0x585F0E);	// line 43, 0x585BF0 - sub_585BF0 : shl     ecx, 5
			CCodeMover::FixOnAddress(0x58710D, 8, "\x0e\x00\x02""SIZEOF_CPICKUP\x00\x02\x05\x10\x71\x58\x00\x00", 0x587115);	// line 44, 0x587000 - sub_587000 : shl     eax, 5
			CCodeMover::FixOnAddress(0x1561586, 10, "\x0e\x01\x02""SIZEOF_CPICKUP\x00\x02\x07\x89\x15\x56\x01\x00", 0x1561590);	// line 45, 0x1561580 - sub_1561580 : shl     ecx, 5
			CCodeMover::FixOnAddress(0x1564BC2, 6, "\x0e\x02\x02""SIZEOF_CPICKUP\x00\x02\x03\xC5\x4B\x56\x01\x00", 0x1564BC8);	// line 46, 0x1564BB0 - sub_1564BB0 : shl     edx, 5
			CCodeMover::FixOnAddress(0x156B372, 6, "\x0e\x02\x02""SIZEOF_CPICKUP\x00\x02\x03\x75\xB3\x56\x01\x00", 0x156B378);	// line 47, 0x156B360 - sub_156B360 : shl     edx, 5
			CCodeMover::FixOnAddress(0x156D89D, 8, "\x0e\x00\x02""SIZEOF_CPICKUP\x00\x02\x05\xA0\xD8\x56\x01\x00", 0x156D8A5);	// line 48, 0x156D870 - sub_156D870 : shl     eax, 5
		}
		#else
			{
				// Count of active addresses: 19
				CCodeMover::FixOnAddress(0x455661, 9, "\x0e\x02\x02""SIZEOF_CPICKUP\x00\x02\x06\x64\x56\x45\x00\x00", 0x45566A);	// line 1, 0x4555A0 - sub_4555A0 : shl     edx, 5
				CCodeMover::FixOnAddress(0x4556CF, 10, "\x0e\x01\x02""SIZEOF_CPICKUP\x00\x02\x07\xD2\x56\x45\x00\x00", 0x4556D9);	// line 2, 0x4556C0 - sub_4556C0 : shl     ecx, 5
				CCodeMover::FixOnAddress(0x456A36, 9, "\x0e\x00\x02""SIZEOF_CPICKUP\x00\x02\x06\x39\x6A\x45\x00\x00", 0x456A3F);	// line 3, 0x456A30 - sub_456A30 : shl     eax, 5
				CCodeMover::FixOnAddress(0x456BF0, 9, "\x0e\x07\x02""SIZEOF_CPICKUP\x00\x02\x06\xF3\x6B\x45\x00\x00", 0x456BF9);	// line 4, 0x456A70 - sub_456A70 : shl     edi, 5
				CCodeMover::FixOnAddress(0x456C07, 10, "\x0e\x02\x02""SIZEOF_CPICKUP\x00\x02\x07\x0A\x6C\x45\x00\x00", 0x456C11);	// line 5, 0x456A70 - sub_456A70 : shl     edx, 5
				CCodeMover::FixOnAddress(0x456DFD, 10, "\x0e\x01\x02""SIZEOF_CPICKUP\x00\x02\x07\x00\x6E\x45\x00\x00", 0x456E07);	// line 6, 0x456DE0 - sub_456DE0 : shl     ecx, 5
				CCodeMover::FixOnAddress(0x456E7F, 10, "\x0e\x01\x02""SIZEOF_CPICKUP\x00\x02\x07\x82\x6E\x45\x00\x00", 0x456E89);	// line 7, 0x456E60 - sub_456E60 : shl     ecx, 5
				CCodeMover::FixOnAddress(0x45719C, 9, "\x0e\x06\x02""SIZEOF_CPICKUP\x00\x02\x06\x9F\x71\x45\x00\x00", 0x4571A5);	// line 8, 0x456F20 - sub_456F20 : shl     esi, 5
				CCodeMover::FixOnAddress(0x4571E5, 9, "\x0e\x06\x02""SIZEOF_CPICKUP\x00\x02\x06\xE8\x71\x45\x00\x00", 0x4571EE);	// line 9, 0x456F20 - sub_456F20 : shl     esi, 5
				CCodeMover::FixOnAddress(0x4573E2, 6, "\x0e\x02\x02""SIZEOF_CPICKUP\x00\x02\x03\xE5\x73\x45\x00\x00", 0x4573E8);	// line 10, 0x4573D0 - sub_4573D0 : shl     edx, 5
				CCodeMover::FixOnAddress(0x458E27, 9, "\x0e\x06\x02""SIZEOF_CPICKUP\x00\x02\x06\x2A\x8E\x45\x00\x00", 0x458E30);	// line 11, 0x458DE0 - sub_458DE0 : shl     esi, 5
				CCodeMover::FixOnAddress(0x458FE1, 9, "\x0e\x06\x02""SIZEOF_CPICKUP\x00\x02\x06\xE4\x8F\x45\x00\x00", 0x458FEA);	// line 12, 0x458DE0 - sub_458DE0 : shl     esi, 5
				CCodeMover::FixOnAddress(0x494722, 9, "\x0e\x01\x02""SIZEOF_CPICKUP\x00\x02\x06\x25\x47\x49\x00\x00", 0x49472B);	// line 13, 0x493FE0 - sub_493FE0 : shl     ecx, 5
				CCodeMover::FixOnAddress(0x585F04, 10, "\x0e\x01\x02""SIZEOF_CPICKUP\x00\x02\x01\x07\x5F\x58\x00\x02\x06\x08\x5F\x58\x00\x00", 0x585F0E);	// line 14, 0x585BF0 - sub_585BF0 : shl     ecx, 5
				CCodeMover::FixOnAddress(0x58710D, 8, "\x0e\x00\x02""SIZEOF_CPICKUP\x00\x02\x05\x10\x71\x58\x00\x00", 0x587115);	// line 15, 0x587000 - sub_587000 : shl     eax, 5
				CCodeMover::FixOnAddress(0x1561586, 10, "\x0e\x01\x02""SIZEOF_CPICKUP\x00\x02\x07\x89\x15\x56\x01\x00", 0x1561590);	// line 16, 0x1561580 - sub_1561580 : shl     ecx, 5
				CCodeMover::FixOnAddress(0x1564BC2, 6, "\x0e\x02\x02""SIZEOF_CPICKUP\x00\x02\x03\xC5\x4B\x56\x01\x00", 0x1564BC8);	// line 17, 0x1564BB0 - sub_1564BB0 : shl     edx, 5
				CCodeMover::FixOnAddress(0x156B372, 6, "\x0e\x02\x02""SIZEOF_CPICKUP\x00\x02\x03\x75\xB3\x56\x01\x00", 0x156B378);	// line 18, 0x156B360 - sub_156B360 : shl     edx, 5
				CCodeMover::FixOnAddress(0x156D89D, 8, "\x0e\x00\x02""SIZEOF_CPICKUP\x00\x02\x05\xA0\xD8\x56\x01\x00", 0x156D8A5);	// line 19, 0x156D870 - sub_156D870 : shl     eax, 5
			}
		#endif

		// Unset variables of automatic patch
		#if TRUE
		{
			CCodeMover::DeleteVariable("SIZEOF_CPICKUP");
			CCodeMover::DeleteVariable("CPICKUP_EXPOS_OFFSET");
		}
		#endif
	}
	#endif

	// Redirect the save function		
	CPatch::RedirectCode(0x5D3540, &CPickups__Save);

	if (bShouldSaveBeEnhanced)
		g_SaveOfVariableLength.MakeSaveOfVariableLength();

	CGenericLogStorage::SaveFormattedTextLn(
		"Format of new savefiles will be different: patch for pickups is applied.\n");

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of 'IPL:PICK' to: %d, pickups collected: %d",
		PickupsLimit,
		PickupsCollectedLimit
		);
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
#endif
}

// Initialize
void IPLsectionLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	// Audio boxes coordinate limit hack enabled
	this->bAudioZonesBoxesCoordLimitHackEnabled = false;

	// Audio boxes limit set?
	this->bAudioZoneBoxesLimitSet = false;

	// Pickup patch enabled?
	this->bPickupPatchEnabled = false;

	// COccluder structure coordinate extension coordinate limit hack enabled
	this->bAudioZonesBoxesCoordLimitHackEnabled = false;

	// Interior occluders limit set?
	this->bInteriorOccludersLimitSet = false;

	// Occluders limit set?
	this->bOccludersLimitSet = false;

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		using namespace Game_GTASA;

		#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
		if(g_LimitAdjuster.IsGameVersionSetUpWithMemory())
			IPL_section_limits_address_operator_new_array = (uintptr_t)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_Znaj"
			);
		#endif

		// Buildings limit
		if(CGameVersion::Is_GTA_SA_Android_Renderware(gameVersion))
			this->BuildingsLimit = 14000;
		else
			this->BuildingsLimit = 13000;
		
		// Dummies
		if(CGameVersion::Is_GTA_SA_Android_Renderware(gameVersion))
			this->DummiesLimit = 3500;
		else
			this->DummiesLimit = 2500;

		// IPL entries of file.
		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
				this->IPLentriesOfFile.ptr = (void**)0xBCC0E0;
			#endif
		}

		// Current limit of IPL entries per file.
		this->IPLentriesPerFileLimit = 4096;

		// IPL entity index array.
		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
				this->IPLentityIndexArray.ptr = (void***)0x8E3F08;
			#elif defined(IS_PLATFORM_ANDROID_ARM32)
			if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
				this->IPLentityIndexArray.ptr = (void***)g_mCalc.GetCurrentVAbyPreferedVA(0x6DFDA8);
			#endif
		}

		// Current limit of IPL entity index array
		this->IPLentityIndexArrayLimit = 40;

		// Current limit of Map zones
		this->MapZonesLimit = 39;

		// Current limit of Navigation zones.
		this->NavigationZonesLimit = 380;

		// Current limit of interior occluders
		this->InteriorOccludersLimit = 40;

		// Current limit of occluders
		this->OccludersLimit = 1000;

		// Current limit of timecyc boxes
		this->TcycLimit = 32;

		// Current limit of CULL mirror attribute zones
		this->CullMirrorAttributeZonesLimit = 72;

		// Current limit of CULL tunnel attribute zones
		this->CullTunnelAttributeZonesLimit = 40;

		// Current limit of CULL attribute zones
		this->CullAttributeZonesLimit = 1300;

		// Stunt jumps limit
		this->StuntJumpsLimit = 256;

		// Entry exits limit
		if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			this->EntryExitsLimit = 455;
		else
			this->EntryExitsLimit = 400;

		// Audio spheres limit
		this->AudioZoneSpheresLimit = 3;

		// Audio boxes limit
		this->AudioZoneBoxesLimit = 158;
		
		// Pickups limit
		this->PickupsLimit = 620;

		// Pickups collected limit
		this->PickupsCollectedLimit = 20;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				// Map zones
				this->CTheZones__MapZoneArray.gta_sa = (CZone*)0xBA1908;

				// Navigation zones
				this->CTheZones__NavigationZoneArray.gta_sa = (CZone*)0xBA3798;

				// Zone info array
				this->CTheZones__ZoneInfoArray.gta_sa = (CZoneInfo *)0xBA1DF0;

				// Interior occluders
				this->COcclusion__aInteriorOccluders.gta_sa = (COccluder*)0xC73CC8;

				// Occluders
				this->COcclusion__aOccluders.gta_sa = (COccluder*)0xC73FA0;

				// Timecycle boxes
				this->CTimeCycle__m_aBoxes.gta_sa = (CTimecycleBox*)0xB7C550;

				// CULL mirror attribute zones
				this->CCullZones__aMirrorAttributeZones.gta_sa = (CCullZoneReflection*)0xC815C0;

				// CULL tunnel attribute zones
				this->CCullZones__aTunnelAttributeZones.gta_sa = (CCullZone*)0xC81C80;

				// CULL attribute zones
				this->CCullZones__aAttributeZones.gta_sa = (CCullZone*)0xC81F50;

				// Audio zone boxes
				this->CAudioZones__m_aBoxes.ptr = (void*)0xB6DCD0;

				// Audio zone spheres
				this->CAudioZones__m_aSpheres.gta_sa = (tAudioZoneSphere*)0xB6EBA8;

				// Pickups collected
				this->CPickups__aPickUpsCollected.ptr = (uint32_t*)0x978628;

				// CEntryExitManager::mp_poolEntryExits pool
				this->CEntryExitManager__mp_poolEntryExits.gta_sa = (CPool_GTASA<CEntryExit>**)0x96A7D8;
			}
			#endif
		}

		// Pickups
		this->CPickups__aPickUps.gta_sa = NULL;
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
	{
		#ifdef IS_PLATFORM_WIN_X86
		// IPL entity index array.
		this->IPLentityIndexArray.ptr = (void***)g_mCalc.GetCurrentVAbyPreferedVA(0x168FFB8);
		#endif

		// Buildings limit
		this->BuildingsLimit = 32000;

		// Dummies
		this->DummiesLimit = 14000;

		// AnimatedBuildings
		this->AnimatedBuildingsLimit = 500;

		// Current limit of IPL entries per file.
		this->IPLentriesPerFileLimit = 8192;

		// Current limit of IPL entity index array
		this->IPLentityIndexArrayLimit = 60;
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
		// Buildings limit
		this->BuildingsLimit = 32000;

		// Dummies
		this->DummiesLimit = 14000;

		// AnimatedBuildings
		this->AnimatedBuildingsLimit = 500;

		#ifdef IS_PLATFORM_WIN_X86
		// IPL entity index array.
		this->IPLentityIndexArray.ptr = (void***)g_mCalc.GetCurrentVAbyPreferedVA(0x136E488);
		#endif

		// Current limit of IPL entries per file.
		this->IPLentriesPerFileLimit = 8192;

		// Current limit of IPL entity index array
		this->IPLentityIndexArrayLimit = 60;
	}
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
	{
		// Buildings limit
		this->BuildingsLimit = 2250;
		
		// Dummies
		this->DummiesLimit = 300;
	}
}

// Shutdown
void IPLsectionLimits::Shutdown()
{
	MAKE_VAR_GAME_VERSION();

	if (IPLentriesOfFile.bIsAllocated.Get())
		delete[] IPLentriesOfFile.ptr;
	
	if (IPLentityIndexArray.bIsAllocated.Get())
		delete[] IPLentityIndexArray.ptr;

	if (COcclusion__aInteriorOccluders.bIsAllocated.Get())
		delete[] COcclusion__aInteriorOccluders.gta_sa;

	if (COcclusion__aOccluders.bIsAllocated.Get())
		delete[] COcclusion__aOccluders.gta_sa;

	if (CAudioZones__m_aBoxes.bIsAllocated.Get())
		delete (char*)CAudioZones__m_aBoxes.ptr;

	if (CPickups__aPickUpsCollected.bIsAllocated.Get())
		delete[] CPickups__aPickUpsCollected.ptr;

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		if (CTheZones__MapZoneArray.bIsAllocated.Get())
			delete[] CTheZones__MapZoneArray.gta_sa;

		if (CTheZones__NavigationZoneArray.bIsAllocated.Get())
			delete[] CTheZones__NavigationZoneArray.gta_sa;

		if (CTheZones__ZoneInfoArray.bIsAllocated.Get())
			delete[] CTheZones__ZoneInfoArray.gta_sa;

		if (CTimeCycle__m_aBoxes.bIsAllocated.Get())
			delete[] CTimeCycle__m_aBoxes.gta_sa;

		if (CCullZones__aMirrorAttributeZones.bIsAllocated.Get())
			delete[] CCullZones__aMirrorAttributeZones.gta_sa;

		if (CCullZones__aTunnelAttributeZones.bIsAllocated.Get())
			delete[] CCullZones__aTunnelAttributeZones.gta_sa;

		if (CCullZones__aAttributeZones.bIsAllocated.Get())
			delete[] CCullZones__aAttributeZones.gta_sa;

		if (CAudioZones__m_aSpheres.bIsAllocated.Get())
			delete[] CAudioZones__m_aSpheres.gta_sa;

		if (CPickups__aPickUps.bIsAllocated.Get())
			delete[] CPickups__aPickUps.gta_sa;
	}
}
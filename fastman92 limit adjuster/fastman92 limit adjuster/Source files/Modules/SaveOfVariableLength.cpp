/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "SaveOfVariableLength.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/CGenericGameStorage.h"
#include "../Core/FormattedOutput.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

using namespace Game;

SaveOfVariableLength g_SaveOfVariableLength;

extern "C"
{
	static const char* footerText = "fastman92 limit adjuster";
	static const unsigned int footerTextLength = 24;
	static const unsigned int footerTextSumOfBytes = 0x916;

	unsigned int workBufferSizeMinusFooter = 0;
	char** CGenericGameStorage__ms_WorkBuffer = 0;
	unsigned int* CGenericGameStorage__ms_WorkBufferPos = 0;

	struct Fastman92saveFooter
	{
		char text[footerTextLength];
		uint32_t checksum;
		uint32_t zero;
	};

	void __cdecl MakeSaveAlignment()
	{
		const int alignmentSize = sizeof(Fastman92saveFooter);

		unsigned int FilePos = *CGenericGameStorage::ms_FilePos + *CGenericGameStorage::ms_WorkBufferPos;

		int reminder = FilePos % alignmentSize;

		if (reminder != 0)
		{
			char alignment[alignmentSize];

			for (int i = 0; i < alignmentSize; i++)
				alignment[i] = 0;

			CGenericGameStorage::SaveDataToWorkBuffer(&alignment, alignmentSize - reminder);
		}
	}

	void SaveFastman92footer()
	{
		Fastman92saveFooter* pFooter = (Fastman92saveFooter*)(char*)(*CGenericGameStorage::ms_WorkBuffer + *CGenericGameStorage::ms_WorkBufferPos);

		memcpy(pFooter->text, footerText, footerTextLength);

		// add checksum of pFooter->text
		uint8_t* pCheckStart = (uint8_t*)&pFooter->text;
		uint8_t* pCheckEnd = (uint8_t*)&pFooter->checksum;

		for (uint8_t* pCheck = pCheckStart; pCheck < pCheckEnd; pCheck++)
			*CGenericGameStorage::ms_CheckSum += *pCheck;

		///////
		
		pFooter->checksum = *CGenericGameStorage::ms_CheckSum;
		pFooter->zero = 0;

		*CGenericGameStorage::ms_WorkBufferPos += sizeof(Fastman92saveFooter);
	}

	bool CheckFastman92footer(unsigned int calculated_checksum)
	{
		uint32_t read_checksum = *(uint32_t*)(char*)(*CGenericGameStorage::ms_WorkBuffer + *CGenericGameStorage::ms_WorkBufferSize - 4);
		
		// Discard last 4 bytes
		uint32_t discardedPart = (read_checksum >> 24)
			+ ((read_checksum >> 16) & 0xFF)
			+ ((read_checksum >> 8) & 0xFF)
			+ ((read_checksum) & 0xFF);

		calculated_checksum -= discardedPart;

		if (calculated_checksum == read_checksum)
			return true;

		if (*CGenericGameStorage::ms_WorkBufferSize < sizeof(Fastman92saveFooter))
			return false;

		Fastman92saveFooter* pFooter = (Fastman92saveFooter*)(char*)(*CGenericGameStorage::ms_WorkBuffer + *CGenericGameStorage::ms_WorkBufferSize - sizeof(Fastman92saveFooter));

		if (pFooter->zero != 0)
			return false;

		if (memcmp(pFooter->text, footerText, footerTextLength))
			return false;

		read_checksum = pFooter->checksum;

		discardedPart = (read_checksum >> 24)
			+ ((read_checksum >> 16) & 0xFF)
			+ ((read_checksum >> 8) & 0xFF)
			+ ((read_checksum) & 0xFF);

		calculated_checksum -= discardedPart;

		return calculated_checksum == read_checksum;
	}
}

namespace Game_GTASA
{
	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CGenericGameStorage__GenericSave_5D15D1()
	{
		__asm
		{
			call MakeSaveAlignment;

			// go back
			mov eax, 0x5D16A0;
			jmp eax;
		}
	}

	NAKED void patch_CGenericGameStorage__SaveWorkBuffer_5D0FEE()
	{
		__asm
		{
			call SaveFastman92footer;

			mov edx, CGenericGameStorage::ms_WorkBuffer;
			mov edx, [edx];

			mov ecx, CGenericGameStorage::ms_WorkBufferPos;
			mov ecx, [ecx];

			// go back
			mov eax, 0x5D100B;
			jmp eax;
		}
	}

	/////////////

	NAKED void patch_CGenericGameStorage__CheckDataNotCorrupt_5D1216()
	{
		__asm
		{
			push esi;
			call CheckFastman92footer;
			add esp, 4;

			mov esi, 1;
			movzx edi, al;

			mov eax, CGenericGameStorage::ms_WorkBuffer;
			mov eax, [eax];

			cmp     eax, ebx;

			push 0x5D123F;
			retn;
		}
	}
	#endif

	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
	// patch for 0x4827BC
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CGenericGameStorage__GenericSave_4827C2 = 0;
		uintptr_t Address_GTA_SA_2_00_CGenericGameStorage__GenericSave_4827EE_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGenericGameStorage__GenericSave_4827BC()
	{
		__asm(
		".thumb\n"
			"BLX MakeSaveAlignment\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGenericGameStorage__GenericSave_4827EE_thumb)
			);
	}

	// patch for 0x482A46
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A5C_thumb = 0;	// loc_482A5C
		uintptr_t Address_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A50_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A46()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, workBufferSizeMinusFooter)
			"CMP R2, R0\n"
			"BCC 1f\n"
			"MOVS R0, #0\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A50_thumb)

			// Branches
			"1:\n"	// loc_482A5C
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A5C_thumb)
			);
	}

	// patch for 0x482A5C
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A64 = 0;
		uintptr_t Address_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A7A_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A5C()
	{
		__asm(
		".thumb\n"
			"BLX SaveFastman92footer\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R2, CGenericGameStorage__ms_WorkBufferPos)
			"LDR             R2, [R2]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A7A_thumb)
			);
	}

	// patch for 0x483A36
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CGenericGameStorage__CheckDataNotCorrupt_483A3E = 0;
		uintptr_t Address_GTA_SA_2_00_CGenericGameStorage__CheckDataNotCorrupt_483A6E_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGenericGameStorage__CheckDataNotCorrupt_483A36()
	{
		__asm(
		".thumb\n"
			"MOV R0, R4\n"
			"BLX CheckFastman92footer\n"
			"MOV R6, R0\n"

			"MOVS            R8, #1\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, CGenericGameStorage__ms_WorkBuffer)
			"LDR             R0, [R0]\n"
			"CMP             R0, #0\n"
			
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGenericGameStorage__CheckDataNotCorrupt_483A6E_thumb)
			);
	}
	#endif
}

static void SetExternVariables()
{
	CGenericGameStorage__ms_WorkBuffer = CGenericGameStorage::ms_WorkBuffer;
	CGenericGameStorage__ms_WorkBufferPos = CGenericGameStorage::ms_WorkBufferPos;
}

// Patches a save function, the save file will have unlimited length.
bool SaveOfVariableLength::MakeSaveOfVariableLength()
{
	if (this->bIsSavingPatchApplied)
		return true;

	MAKE_VAR_GAME_VERSION();

	SetExternVariables();
	
	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		CPatch::EnterNewLevel();
		CPatch::DisableDebugMode();

		// CGenericGameStorage::GenericSave
		CPatch::RedirectCode(0x5D15D1, &patch_CGenericGameStorage__GenericSave_5D15D1);

		// CGenericGameStorage::SaveWorkBuffer
		CPatch::PatchUINT32(0x5D0FD0 + 2, 52000 - sizeof(Fastman92saveFooter));	// cmp     ecx, 51196
		CPatch::RedirectCode(0x5D0FEE, &patch_CGenericGameStorage__SaveWorkBuffer_5D0FEE);

		// Patch loading function if it's not patched yet.
		PatchLoadingFunction();

		CPatch::LeaveThisLevel();

		this->bIsSavingPatchApplied = true;
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		CPatch::EnterNewLevel();
		CPatch::DisableDebugMode();

		// CGenericGameStorage::GenericSave
		Address_GTA_SA_2_00_CGenericGameStorage__GenericSave_4827C2 = g_mCalc.GetCurrentVAbyPreferedVA(0x4827C2);
		Address_GTA_SA_2_00_CGenericGameStorage__GenericSave_4827EE_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x4827EE));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x4827BC),
			(void*)&patch_GTA_SA_2_00_CGenericGameStorage__GenericSave_4827BC
		);

		// CGenericGameStorage::SaveWorkBuffer
		workBufferSizeMinusFooter = 65001 - sizeof(Fastman92saveFooter);

		Address_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A5C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x482A5C));
		Address_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A50_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x482A50));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x482A46),
			(void*)&patch_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A46
		);		

		Address_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A64 = g_mCalc.GetCurrentVAbyPreferedVA(0x482A64);
		Address_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A7A_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x482A7A));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x482A5C),
			(void*)&patch_GTA_SA_2_00_CGenericGameStorage__SaveWorkBuffer_482A5C
		);

		// Patch loading function if it's not patched yet.
		PatchLoadingFunction();

		CPatch::LeaveThisLevel();

		this->bIsSavingPatchApplied = true;
	}
	#endif
	else
		return this->bIsSavingPatchApplied;
	
	if(this->bIsSavingPatchApplied)
		CGenericLogStorage::SaveFormattedTextLn("Format of new savefiles will be different: patch for save game of variable length is applied!");

	return this->bIsSavingPatchApplied;
}

// Patches a loading function, the savefile of any length may be considered as valid savefile.
void SaveOfVariableLength::PatchLoadingFunction()
{
	MAKE_VAR_GAME_VERSION();

	if (this->bIsLoadingPatchApplied)
		return;

	SetExternVariables();
	
	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		// CGenericGameStorage::CheckDataNotCorrupt
		CPatch::RedirectCode(0x5D1216, &patch_CGenericGameStorage__CheckDataNotCorrupt_5D1216);

		this->bIsLoadingPatchApplied = true;
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;
		
		// CGenericGameStorage::CheckDataNotCorrupt
		Address_GTA_SA_2_00_CGenericGameStorage__CheckDataNotCorrupt_483A3E = g_mCalc.GetCurrentVAbyPreferedVA(0x483A3E);
		Address_GTA_SA_2_00_CGenericGameStorage__CheckDataNotCorrupt_483A6E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x483A6E));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x483A36),
			(void*)&patch_GTA_SA_2_00_CGenericGameStorage__CheckDataNotCorrupt_483A36
		);

		this->bIsLoadingPatchApplied = true;
	}
	#endif
}

// Initialize
void SaveOfVariableLength::Initialise()
{
	this->bIsSavingPatchApplied = false;
	this->bIsLoadingPatchApplied = false;
}
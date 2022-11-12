/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "RendererLimits.h"
#include "../Core/CPatch.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/LimitAdjuster.h"

using namespace Game;

RendererLimits g_rendererLimits;

#ifdef IS_PLATFORM_ANDROID_ARM32
namespace Game_GTASA
{
	extern "C"
	{
		unsigned int InvisibleEntityPtrsLimitMinusTwo;
	}

	// patch for 0x410BEC
	extern "C"
	{
		uintptr_t Address_CRenderer__ScanSectorList_410AF8_thumb = 0;
		uintptr_t Address_CRenderer__ScanSectorList_410BF6_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CRenderer__ScanSectorList_410BEC()
	{
		__asm(
		".thumb\n"
			"LDR R0, [SP,#20]\n"
			"LDR R0, [R0]\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, InvisibleEntityPtrsLimitMinusTwo)
			"BGT 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CRenderer__ScanSectorList_410BF6_thumb)

			// Branches
			"1:\n"	// def_410B2A
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CRenderer__ScanSectorList_410AF8_thumb)
			);
	}
}
#endif

// Sets the invisible entity pointers
void RendererLimits::SetInvisibleEntityPtrs(int iInvisibleEntityPtrs)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iInvisibleEntityPtrs = this->ms_InvisibleEntityPtrsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		if (iInvisibleEntityPtrs > this->ms_InvisibleEntityPtrsLimit)
		{
			CRenderer__ms_aInVisibleEntityPtrs.ptr = new void*[iInvisibleEntityPtrs];
			CRenderer__ms_aInVisibleEntityPtrs.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x553983 + 3, CRenderer__ms_aInVisibleEntityPtrs.ptr);	// mov     ecx, _ZN9CRenderer23ms_aInVisibleEntityPtrsE[esi*4]; CRenderer::ms_aInVisibleEntityPtrs	; sub_553910
			CPatch::PatchPointer(0x554AC4 + 3, CRenderer__ms_aInVisibleEntityPtrs.ptr);	// mov     _ZN9CRenderer23ms_aInVisibleEntityPtrsE[eax*4], esi; CRenderer::ms_aInVisibleEntityPtrs	; _ZN9CRenderer14ScanSectorListEii
		}
		#endif

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(0x554ABD + 1, ms_InvisibleEntityPtrsLimit - 1);	// cmp     eax, 149	; _ZN9CRenderer14ScanSectorListEii
		}
		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID_ARM32)	
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if (iInvisibleEntityPtrs > this->ms_InvisibleEntityPtrsLimit)
		{
			CRenderer__ms_aInVisibleEntityPtrs.ptr = new void*[iInvisibleEntityPtrs];
			CRenderer__ms_aInVisibleEntityPtrs.bIsAllocated.Set(true);
		}

		// Set variable
		Game_GTASA::InvisibleEntityPtrsLimitMinusTwo = iInvisibleEntityPtrs - 2;

		// Patch pointer
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x678B88), CRenderer__ms_aInVisibleEntityPtrs.ptr);

		// Changes
		Address_CRenderer__ScanSectorList_410AF8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x410AF8));
		Address_CRenderer__ScanSectorList_410BF6_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x410BF6));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x410BEC),
			(void*)&patch_CRenderer__ScanSectorList_410BEC
		);
	}	
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_InvisibleEntityPtrsLimit = iInvisibleEntityPtrs;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of RENDERER: Invisible entity pointers to: %d",
		iInvisibleEntityPtrs
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets the visible super LOD pointers
void RendererLimits::SetVisibleSuperLodPtrs(int iVisibleSuperLodPtrs)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iVisibleSuperLodPtrs = this->ms_VisibleSuperLodPtrsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		if (iVisibleSuperLodPtrs > this->ms_VisibleSuperLodPtrsLimit)
		{
			CRenderer__ms_aVisibleSuperLodPtrs.ptr = new void*[iVisibleSuperLodPtrs];
			CRenderer__ms_aVisibleSuperLodPtrs.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x553962 + 3, CRenderer__ms_aVisibleSuperLodPtrs.ptr);	//  mov     ecx, _ZN9CRenderer23ms_aVisibleSuperLodPtrsE[esi*4] ; CRenderer::ms_aVisibleSuperLodPtrs
		}
		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID_ARM32)	
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		if (iVisibleSuperLodPtrs > this->ms_VisibleSuperLodPtrsLimit)
		{
			CRenderer__ms_aVisibleSuperLodPtrs.ptr = new void*[iVisibleSuperLodPtrs];
			CRenderer__ms_aVisibleSuperLodPtrs.bIsAllocated.Set(true);
		}

		// Patch pointer
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x676B2C), CRenderer__ms_aVisibleSuperLodPtrs.ptr);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_VisibleSuperLodPtrsLimit = iVisibleSuperLodPtrs;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of RENDERER: Visible super LOD pointers to: %d",
		iVisibleSuperLodPtrs
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets the visible LOD pointers
void RendererLimits::SetVisibleLodPtrs(int iVisibleLodPtrs)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iVisibleLodPtrs = this->ms_VisibleLodPtrsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		if (iVisibleLodPtrs > this->ms_VisibleLodPtrsLimit)
		{
			CRenderer__ms_aVisibleLodPtrs.ptr = new void*[iVisibleLodPtrs];
			CRenderer__ms_aVisibleLodPtrs.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x5534F2 + 3, CRenderer__ms_aVisibleLodPtrs.ptr);	// mov     _ZN9CRenderer18ms_aVisibleLodPtrsE[eax*4], esi; CRenderer::ms_aVisibleLodPtrs	; sub_5534B0
			CPatch::PatchPointer(0x553920 + 3, CRenderer__ms_aVisibleLodPtrs.ptr);	// mov     ecx, _ZN9CRenderer18ms_aVisibleLodPtrsE[esi*4]; CRenderer::ms_aVisibleLodPtrs	; sub_553910
			CPatch::PatchPointer(0x553CB0 + 3, CRenderer__ms_aVisibleLodPtrs.ptr);	// mov     ecx, _ZN9CRenderer18ms_aVisibleLodPtrsE[esi*4]; CRenderer::ms_aVisibleLodPtrs	; _ZN9CRenderer24RenderEverythingBarRoadsEv
		}
		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID_ARM32)	
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		if (iVisibleLodPtrs > this->ms_VisibleLodPtrsLimit)
		{
			CRenderer__ms_aVisibleLodPtrs.ptr = new void*[iVisibleLodPtrs];
			CRenderer__ms_aVisibleLodPtrs.bIsAllocated.Set(true);
		}

		// Patch pointer
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x676484), CRenderer__ms_aVisibleLodPtrs.ptr);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_VisibleLodPtrsLimit = iVisibleLodPtrs;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of RENDERER: Visible LOD pointers to: %d",
		iVisibleLodPtrs
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets the visible entity pointers
void RendererLimits::SetVisibleEntityPtrs(int iVisibleEntityPtrs)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iVisibleEntityPtrs = this->ms_VisibleEntityPtrsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		if (iVisibleEntityPtrs > this->ms_VisibleEntityPtrsLimit)
		{
			CRenderer__ms_aVisibleEntityPtrs.ptr = new void*[iVisibleEntityPtrs];
			CRenderer__ms_aVisibleEntityPtrs.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x553526 + 3, CRenderer__ms_aVisibleEntityPtrs.ptr);	// mov     _ZN9CRenderer21ms_aVisibleEntityPtrsE[eax*4], esi; CRenderer::ms_aVisibleEntityPtrs	; sub_5534B0
			CPatch::PatchPointer(0x553941 + 3, CRenderer__ms_aVisibleEntityPtrs.ptr);	// mov     ecx, _ZN9CRenderer21ms_aVisibleEntityPtrsE[esi*4]; CRenderer::ms_aVisibleEntityPtrs	; sub_553910
			CPatch::PatchPointer(0x553A50 + 3, CRenderer__ms_aVisibleEntityPtrs.ptr);	// mov     esi, _ZN9CRenderer21ms_aVisibleEntityPtrsE[edi*4]; CRenderer::ms_aVisibleEntityPtrs	; _ZN9CRenderer11RenderRoadsEv
			CPatch::PatchPointer(0x553B00 + 3, CRenderer__ms_aVisibleEntityPtrs.ptr);	// mov     esi, _ZN9CRenderer21ms_aVisibleEntityPtrsE[edi*4]; CRenderer::ms_aVisibleEntityPtrs	; _ZN9CRenderer24RenderEverythingBarRoadsEv
		}
		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID_ARM32)	
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		if (iVisibleEntityPtrs > this->ms_VisibleEntityPtrsLimit)
		{
			CRenderer__ms_aVisibleEntityPtrs.ptr = new void*[iVisibleEntityPtrs];
			CRenderer__ms_aVisibleEntityPtrs.bIsAllocated.Set(true);
		}

		// Patch pointer
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x6778F4), CRenderer__ms_aVisibleEntityPtrs.ptr);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_VisibleEntityPtrsLimit = iVisibleEntityPtrs;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of RENDERER: Visible entity pointers to: %d",
		iVisibleEntityPtrs
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Initialize
void RendererLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if(CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		this->ms_InvisibleEntityPtrsLimit = 150;
		this->ms_VisibleSuperLodPtrsLimit = 50;
		this->ms_VisibleLodPtrsLimit = 1000;
		this->ms_VisibleEntityPtrsLimit = 1000;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				this->CRenderer__ms_aInVisibleEntityPtrs.ptr = (void**)0xB745D8;
				this->CRenderer__ms_aVisibleSuperLodPtrs.ptr = (void**)0xB74830;
				this->CRenderer__ms_aVisibleLodPtrs.ptr = (void**)0xB748F8;
				this->CRenderer__ms_aVisibleEntityPtrs.ptr = (void**)0xB75898;
			}
			#elif defined(IS_PLATFORM_ANDROID_ARM32)
			this->CRenderer__ms_aInVisibleEntityPtrs.ptr = (void**)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN9CRenderer23ms_aInVisibleEntityPtrsE"
			);
			this->CRenderer__ms_aVisibleSuperLodPtrs.ptr = (void**)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN9CRenderer23ms_aVisibleSuperLodPtrsE"
			);
			this->CRenderer__ms_aVisibleLodPtrs.ptr = (void**)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN9CRenderer18ms_aVisibleLodPtrsE"
			);
			this->CRenderer__ms_aVisibleEntityPtrs.ptr = (void**)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN9CRenderer21ms_aVisibleEntityPtrsE"
			);
			#endif
		}
	}
}

// Shutdown
void RendererLimits::Shutdown()
{
	if (CRenderer__ms_aInVisibleEntityPtrs.bIsAllocated.Get())
		delete[] CRenderer__ms_aInVisibleEntityPtrs.ptr;
	
	if (CRenderer__ms_aVisibleSuperLodPtrs.bIsAllocated.Get())
		delete[] CRenderer__ms_aVisibleSuperLodPtrs.ptr;

	if (CRenderer__ms_aVisibleLodPtrs.bIsAllocated.Get())
		delete[] CRenderer__ms_aVisibleLodPtrs.ptr;

	if (CRenderer__ms_aVisibleEntityPtrs.bIsAllocated.Get())
		delete[] CRenderer__ms_aVisibleEntityPtrs.ptr;
}
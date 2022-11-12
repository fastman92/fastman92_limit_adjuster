/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#include "LoadingScreenFontHooks.h"

#include "../Core/CPatch.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include "GameText.h"

#include <Array\countof.h>
#include <MultiPlatformSupport/PlatformGeneralisation.h>
#include <StrLexStuff.h>

#include <stdio.h>
#include <wchar.h>

using namespace Game;

LoadingScreenFontHooks g_LoadingScreenFontHooks;

extern "C"
{
	unsigned int* CLoadingScreen__m_numChunksLoaded;

	static void CallLoadingScreenFontHooks()
	{
		for (unsigned int i = 0; i < g_LoadingScreenFontHooks.m_numberOfCallbacksRegistered; i++)
		{
			const tLoadingScreenFontCallback* pCallback = &g_LoadingScreenFontHooks.m_callbackList[i];
			pCallback->funcPtr(pCallback->pCustomData);
		}
	}

	void LoadingScreenExtraCodeASCIIalways(const char* a, const char* b)
	{
		if (a == nullptr)
			a = "";

		if (b == nullptr)
			b = "";

		if (g_GameText.UsesUnsignedShortForCharacters())
		{
			char buffer[1024];

			sprintf(
				buffer,
				"%s, %s",
				a, b
			);

			g_GameText.AsciiToUnicode(buffer, g_LoadingScreenFontHooks.loadingScreenText.Unicode);
		}
		else
			sprintf(
				g_LoadingScreenFontHooks.loadingScreenText.Char,
				"%s, %s",
				a, b
			);

		//////
		CallLoadingScreenFontHooks();
	}

	void LoadingScreenExtraCodeASCIIorWide(const void* a, const void* b)
	{
		if (a == nullptr)
			a = L"";

		if (b == nullptr)
			b = L"";

		if (g_GameText.UsesUnsignedShortForCharacters())
		{
			#if PROJECT_IS_UNRELEASED_EDITION
			// Process empty strings
			static const unsigned short emptyStr[] = { 'U', 'n', 's', 'e', 't', NULL };

			if (!*(const unsigned short*)a)
				a = emptyStr;

			if (!*(const unsigned short*)b)
				b = emptyStr;

			char buffer1[300];
			char buffer2[300];
			g_GameText.UnicodeTextToAscii((unsigned short*)a, buffer1);
			g_GameText.UnicodeTextToAscii((unsigned short*)b, buffer2);

			// printf_MessageBox("Value: \"%s\" \"%s\" thread: %d", buffer1, buffer2, gettid());
			#endif

			unsigned short* pString = g_LoadingScreenFontHooks.loadingScreenText.Unicode;

			unsigned int len_left = _countof(g_LoadingScreenFontHooks.loadingScreenText.Unicode);

			unsigned int num_chars_copied = g_GameText.CopyUnicodeStringSafe((const unsigned short*)a,
				pString, len_left);

			// protection against buffer overflow
			if (num_chars_copied < len_left)
			{
				pString += num_chars_copied;
				len_left -= num_chars_copied;

				if (len_left > 2)
				{
					*pString = ',';
					*(pString + 1) = ' ';

					len_left -= 2;
					pString += 2;

					pString += g_GameText.CopyUnicodeStringSafe((const unsigned short*)b,
						pString,
						len_left
					);
			
					// Text entries won't be displayed if there's a space in the end
					TrimRight(g_LoadingScreenFontHooks.loadingScreenText.Unicode);		
				}
			}
		}
		else
		{
			#if PROJECT_IS_UNRELEASED_EDITION
			// Process empty strings
			const char* emptyStr = "EMPTY";

			if (!*(const char*)a)
				a = emptyStr;

			if (!*(const char*)b)
				b = emptyStr;
			#endif

			sprintf(
				g_LoadingScreenFontHooks.loadingScreenText.Char,
				"%s, %s",
				(const char*)a, (const char*)b
			);

			// Text entries won't be displayed if there's a space in the end
			TrimRight(g_LoadingScreenFontHooks.loadingScreenText.Char);
		}

		//////
		CallLoadingScreenFontHooks();
	}
}

extern "C"
{
	uintptr_t Address_CLoadingScreen__LoadingScreen_prolog_goBack = 0;
	uintptr_t Address_CLoadingScreen__LoadingScreen_callExtraCode_goBack = 0;
}

namespace Game_GTAIII
{
	#ifdef IS_PLATFORM_WIN_X86
	static NAKED void patch_LoadingScreen_48D9C7()
	{
		__asm
		{
			mov eax, [esp + 0x54 + 0x8];
			push eax;

			mov eax, [esp + 0x58 + 0x4];
			push eax;

			call LoadingScreenExtraCodeASCIIalways;
			add esp, 8;

			push 0x48DA11;
			retn;
		}
	}
	#endif

	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
	TARGET_THUMB NAKED void patch_LoadingScreen_1BF6D8()
	{
		__asm volatile (
			".thumb\n"
			"PUSH.W          {R4-R11,LR}\n"
			"SUB             SP, SP, #4\n"
			"VPUSH           {D8-D15}\n"

			"PUSH.W          {R0, R1}\n"

			// Access [SP, #0]? Access to the first value.

			// stack = -0x70
			"SUB             SP, SP, #0x50\n"

			// stack 
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CLoadingScreen__LoadingScreen_prolog_goBack)
			);
	}
	#endif
}

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
// For GTA III and GTA VC
template<int stack_value> TARGET_THUMB NAKED void patch_LoadingScreen_callingExtraCode()
{
	__asm volatile(
		".thumb\n"
		"LDR R0, [SP, #%c[stack_value]]\n"
		"LDR R1, [SP, #%c[stack_value]+4]\n"
		"BLX LoadingScreenExtraCodeASCIIalways\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CLoadingScreen__LoadingScreen_callExtraCode_goBack)
		::[stack_value]"i"(stack_value)
		);
}
#endif

namespace Game_GTAVC
{
	#ifdef IS_PLATFORM_WIN_X86
	static NAKED void patch_LoadingScreen_4A6CD6()
	{
		__asm
		{
			mov eax, [esp + 0x6C + 0x8];
			push eax;

			mov eax, [esp + 0x70 + 0x4];
			push eax;

			call LoadingScreenExtraCodeASCIIalways;
			add esp, 8;

			push 0x4A6D47;
			retn;
		}
	}
	#endif

	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
	static TARGET_THUMB NAKED void patch_LoadingScreen_14E172()
	{
		__asm volatile (
		".thumb\n"
			// stack = -0x68
			"PUSH.W          {R0, R1}\n"

			// Access [SP, #0]? Access to the first value.

			"SUB             SP, SP, #0x38\n"
			"LDR             R3, [R2]\n"
			"CMP             R3, #0\n"
			"ADD.W           R1, R3, #-1\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CLoadingScreen__LoadingScreen_prolog_goBack)
			);
	};
	#endif
}

uintptr_t Address_CFont_InitPerFrame;
uintptr_t Address_CFont__RenderFontBuffer;
void* CLoadingScreen__m_LoadingGxtMsg1;
void* CLoadingScreen__m_LoadingGxtMsg2;

static uintptr_t Address_CSprite2d__DrawBarChart;
static uintptr_t Address_RwRenderStateSet;

static void RwRenderStateSet(int state, int value)
{
	g_memoryCall.Function<void>(Address_RwRenderStateSet, state, value);
}

namespace Game_GTASA
{
	extern "C"
	{
		void LoadingScreenExtraCodeThisGame()
		{
			// state 11 - rwRENDERSTATEDESTBLEND
			#ifdef IS_PLATFORM_ANDROID_ARM32
			RwRenderStateSet(11, 1);	// rwBLENDZERO
			RwRenderStateSet(11, 6);	// rwBLENDINVSRCALPHA
			#endif

			LoadingScreenExtraCodeASCIIorWide(
				CLoadingScreen__m_LoadingGxtMsg1,
				CLoadingScreen__m_LoadingGxtMsg2
			);
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	static NAKED void patch_CLoadingScreen__RenderLoadingBar_59047B()
	{
		__asm
		{
			push edx;
			push edi;
			push esi;
			push eax;
			push ecx;

			//////			
			mov eax, Address_CFont_InitPerFrame;
			call eax;
			//////

			ASM_JMP_STATIC_ADDRESS(0x590480)
		}
	}

	static NAKED void patch_CLoadingScreen__RenderLoadingBar_590485()
	{
		__asm
		{
			call LoadingScreenExtraCodeThisGame;

			mov eax, Address_CFont__RenderFontBuffer;
			call eax;

			mov eax, 0xBAB338;	// address of flt_BAB338
			fld dword ptr[eax];

			ASM_JMP_STATIC_ADDRESS(0x59048B)
		}
	}

	/*
	static NAKED void patch_CLoadingScreen__RenderLoadingBar_590480()
	{
		__asm
		{
			mov eax, Address_CFont_InitPerFrame;
			call eax;

			mov eax, Address_CSprite2d__DrawBarChart;
			call eax;
			
			call LoadingScreenExtraCodeThisGame;
			
			push 0x590485;	// go back
			mov eax, Address_CFont__RenderFontBuffer;
			jmp eax;
		}
	}
	*/
	#endif

	extern "C"
	{
		float* CLoadingScreen__m_TimeBarAppeared = 0;
		uintptr_t Address_CLoadingScreen__RenderLoadingBar_goBack1 = 0;
		uintptr_t Address_CLoadingScreen__RenderLoadingBar_goBack2 = 0;

		#ifdef IS_PLATFORM_ANDROID_ARM32
		namespace Game_GTA_SA_1_08
		{
			static TARGET_THUMB NAKED void patch_CLoadingScreen__RenderLoadingBar_3D7C08()
			{
				__asm volatile(
					".thumb\n"
					ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CFont_InitPerFrame)
					"BLX R0\n"

					"VLDR            S13, 1f\n"
					"MOVS            R3, #1\n"

					"STR             R3, [SP,#0x44-0x38]\n"

					ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CLoadingScreen__RenderLoadingBar_goBack1)

					ASM_PUT_CONSTANT_FLOAT(1, 640.0)
					);
			}

			static DLL_EXPORT TARGET_THUMB NAKED void patch_CLoadingScreen__RenderLoadingBar_3D7C68()
			{
				__asm volatile(
					".thumb\n"
					"BLX LoadingScreenExtraCodeThisGame\n"

					ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CFont__RenderFontBuffer)
					"BLX R0\n"

					"VLDR            S15, [R4]\n"
					"VCMP.F32        S15, S21\n"

					ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CLoadingScreen__RenderLoadingBar_goBack2)
					);
			}
		}

		namespace Game_GTA_SA_2_00
		{
			static TARGET_THUMB NAKED void patch_CLoadingScreen__RenderLoadingBar_43B4D0()
			{
				__asm volatile(
					".thumb\n"
					"STR             R0, [SP,#0x70-0x5C]\n"

					ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CFont_InitPerFrame)
					"BLX R0\n"

					"VLDR            S0, 1f\n"
					"VMOV.F32        S2, #-14.0\n"

					"LDR             R0, [SP,#0x70-0x5C]\n"
					
					ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CLoadingScreen__RenderLoadingBar_goBack1)

					ASM_PUT_CONSTANT_FLOAT(1, 640.0)
					);
			}

			static DLL_EXPORT TARGET_THUMB NAKED void patch_CLoadingScreen__RenderLoadingBar_43B530()
			{
				__asm volatile(
					".thumb\n"
					"BLX LoadingScreenExtraCodeThisGame\n"

					ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CFont__RenderFontBuffer)
					"BLX R0\n"
					
					ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, CLoadingScreen__m_TimeBarAppeared)

					"VLDR            S0, [R0]\n"
					ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CLoadingScreen__RenderLoadingBar_goBack2)
					);
			}
		}

		namespace Game_GTA_SA_GER_2_09
		{
			// patch for 0x43B4E0
			static TARGET_THUMB NAKED void patch_GTA_SA_GER_2_09_CLoadingScreen__RenderLoadingBar_43B4E0()
			{
				__asm(
				".thumb\n"
					"STR             R0, [SP,#0x70-0x5C]\n"

					ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CFont_InitPerFrame)
					"BLX R0\n"

					"VLDR S0, 101f\n"
					"VMOV.F32 S2, #-14.0\n"
					ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CLoadingScreen__RenderLoadingBar_goBack1)

					// Data
					ASM_PUT_CONSTANT_FLOAT(101, 640.0)
					);
			}

			// patch for 0x43B540
			static TARGET_THUMB NAKED void patch_GTA_SA_GER_2_09_CLoadingScreen__RenderLoadingBar_43B540()
			{
				__asm(
				".thumb\n"
					".thumb\n"
					"BLX LoadingScreenExtraCodeThisGame\n"

					ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CFont__RenderFontBuffer)
					"BLX R0\n"

					ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, CLoadingScreen__m_TimeBarAppeared)

					"VLDR S0, [R0]\n"
					ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CLoadingScreen__RenderLoadingBar_goBack2)
					);
			}
		}
		#endif
	}
}

namespace Game_BullyScholarschipEdition
{
	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_LoadingScreen_43C8A9()
	{
		__asm
		{
			mov eax, [esp + 0x4F4 + 0x8];
			push eax;

			mov eax, [esp + 0x4F4 + 0x4];
			push eax;

			call LoadingScreenExtraCodeASCIIalways;
			add esp, 8;
			////

			mov     eax, [esp + 4F4h + 8];	// [esp+4F4h+second]
			ASM_JMP_STATIC_ADDRESS(0x43C8B0);
		}
	}
	#endif
}

// Initialize
void LoadingScreenFontHooks::Initialise()
{
	this->m_numberOfCallbacksRegistered = 0;
}

const wchar_t* test()
{
	return L"TEST";
}

static void ApplyHook_GTASA_prolog()
{
	using namespace Game_GTASA;

	Address_RwRenderStateSet = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_Z16RwRenderStateSet13RwRenderStatePv"
	);

	Address_CFont_InitPerFrame = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN5CFont12InitPerFrameEv"
	);

	Address_CFont__RenderFontBuffer = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN5CFont16RenderFontBufferEv"
	);

	CLoadingScreen__m_TimeBarAppeared = (float*)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN14CLoadingScreen17m_TimeBarAppearedE"
	);

	CLoadingScreen__m_LoadingGxtMsg1 = (void*)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN14CLoadingScreen16m_LoadingGxtMsg1E"
	);

	CLoadingScreen__m_LoadingGxtMsg2 = (void*)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN14CLoadingScreen16m_LoadingGxtMsg2E"
	);

	CLoadingScreen__m_numChunksLoaded = (unsigned int*)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN14CLoadingScreen17m_numChunksLoadedE"
	);
}

// Applies the patch
void LoadingScreenFontHooks::ApplyHook()
{
	if (this->m_numberOfCallbacksRegistered == 0)
		return;

	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_III_1_0_WIN_X86)
	{
		using namespace Game_GTAIII;
		
		CPatch::RedirectCode(0x48D9C7, &patch_LoadingScreen_48D9C7);
	}
	else if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
	{
		using namespace Game_GTAVC;
		
		CPatch::RedirectCode(0x4A6CD6, &patch_LoadingScreen_4A6CD6);
	}
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		Address_CFont_InitPerFrame = g_mCalc.GetCurrentVAbyPreferedVA(0x719800);
		Address_CFont__RenderFontBuffer = g_mCalc.GetCurrentVAbyPreferedVA(0x71A210);
		CLoadingScreen__m_LoadingGxtMsg1 = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0xBAB2C8);
		CLoadingScreen__m_LoadingGxtMsg2 = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0xBAB278);

		Address_CSprite2d__DrawBarChart = g_mCalc.GetCurrentVAbyPreferedVA(0x728640);

		CPatch::RedirectCode(0x59047B, &patch_CLoadingScreen__RenderLoadingBar_59047B);
		CPatch::RedirectCode(0x590485, &patch_CLoadingScreen__RenderLoadingBar_590485);
	}
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
	{
		using namespace Game_BullyScholarschipEdition;

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x43C8A9), &patch_LoadingScreen_43C8A9);
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_III_1_8_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTAIII;

		// prolog and epilog
		Address_CLoadingScreen__LoadingScreen_prolog_goBack = g_mCalc.GetCurrentVAbyPreferedVA(
			ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1BF6E4)
		);
		
		CPatch::RedirectCodeEx(
			INSTRUCTION_SET_THUMB,
			g_mCalc.GetCurrentVAbyPreferedVA(0x1BF6D8),
			(void*)&patch_LoadingScreen_1BF6D8
		);

		CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x1BFBB6), 0xB016);	// ADD             SP, SP, #0x58

		// calling extra code
		Address_CLoadingScreen__LoadingScreen_callExtraCode_goBack = g_mCalc.GetCurrentVAbyPreferedVA(
			ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1BFB90)
		);
				
		CPatch::RedirectCodeEx(
			INSTRUCTION_SET_THUMB,
			g_mCalc.GetCurrentVAbyPreferedVA(0x1BFB3E),
			(void*)&patch_LoadingScreen_callingExtraCode<0x50>
		);
	}
	else if (gameVersion == GAME_VERSION_GTA_VC_1_09_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTAVC;

		// prolog and epilog
		Address_CLoadingScreen__LoadingScreen_prolog_goBack = g_mCalc.GetCurrentVAbyPreferedVA(
			ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x14E17C)
			);
		
		CPatch::RedirectCodeEx(
			INSTRUCTION_SET_THUMB,
			g_mCalc.GetCurrentVAbyPreferedVA(0x14E172),
			(void*)&patch_LoadingScreen_14E172
		);

		CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x14E1C4), 0xB010);	// ADD             SP, SP, #0x40

		// calling extra code
		Address_CLoadingScreen__LoadingScreen_callExtraCode_goBack = g_mCalc.GetCurrentVAbyPreferedVA(
			ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x14E3E0)
		);

		CPatch::RedirectCodeEx(
			INSTRUCTION_SET_THUMB,
			g_mCalc.GetCurrentVAbyPreferedVA(0x14E388),
			(void*)&patch_LoadingScreen_callingExtraCode<0x38>
		);
	}
	/*
	This will require a Java code
	else if (gameVersion == GAME_VERSION_GTA_LCS_2_4_ANDROID_ARMEABI_V7A)
	{
		// OutputFormattedDebugString("dhere\n");
		// CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x245150), "\x1E\xFF\x2F\xE1", 4);
	}
	*/
	else if (gameVersion == GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A
		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
		|| gameVersion == GAME_VERSION_GTA_SA_GER_2_09_ANDROID_ARMEABI_V7A)
	{
		ApplyHook_GTASA_prolog();

		using namespace Game_GTASA;

		if (gameVersion == GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A)
		{
			using namespace Game_GTA_SA_1_08;

			Address_CLoadingScreen__RenderLoadingBar_goBack1 = g_mCalc.GetCurrentVAbyPreferedVA(
				ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3D7C10)
			);

			Address_CLoadingScreen__RenderLoadingBar_goBack2 = g_mCalc.GetCurrentVAbyPreferedVA(
				ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3D7C70)
			);

			CPatch::RedirectCodeEx(
				INSTRUCTION_SET_THUMB,
				g_mCalc.GetCurrentVAbyPreferedVA(0x3D7C08),
				(void*)&patch_CLoadingScreen__RenderLoadingBar_3D7C08
			);
			
			CPatch::RedirectCodeEx(
				INSTRUCTION_SET_THUMB,
				g_mCalc.GetCurrentVAbyPreferedVA(0x3D7C64),
				(void*)&patch_CLoadingScreen__RenderLoadingBar_3D7C68
			);			
		}
		else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		{
			using namespace Game_GTA_SA_2_00;

			Address_CLoadingScreen__RenderLoadingBar_goBack1 = g_mCalc.GetCurrentVAbyPreferedVA(
				ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x43B4D8)
			);

			Address_CLoadingScreen__RenderLoadingBar_goBack2 = g_mCalc.GetCurrentVAbyPreferedVA(
				ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x43B53A)
			);
			
			CPatch::RedirectCodeEx(
				INSTRUCTION_SET_THUMB,
				g_mCalc.GetCurrentVAbyPreferedVA(0x43B4D0),
				(void*)&patch_CLoadingScreen__RenderLoadingBar_43B4D0
			);			
						
			CPatch::RedirectCodeEx(
				INSTRUCTION_SET_THUMB,
				g_mCalc.GetCurrentVAbyPreferedVA(0x43B530),
				(void*)&patch_CLoadingScreen__RenderLoadingBar_43B530
			);
			
		}

		else if (gameVersion == GAME_VERSION_GTA_SA_GER_2_09_ANDROID_ARMEABI_V7A)
		{
			using namespace Game_GTA_SA_GER_2_09;

			Address_CLoadingScreen__RenderLoadingBar_goBack1 = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x43B4E8));

			Address_CLoadingScreen__RenderLoadingBar_goBack2 = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x43B54A));
			
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x43B4E0),
				(void*)&patch_GTA_SA_GER_2_09_CLoadingScreen__RenderLoadingBar_43B4E0
			);
			
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x43B540),
				(void*)&patch_GTA_SA_GER_2_09_CLoadingScreen__RenderLoadingBar_43B540
			);
			
		}
	}
	/*
	else if (gameVersion == GAME_VERSION_BULLY_AE_1_0_0_18_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_BullyScholarschipEdition;

		OutputFormattedDebugString("fsafsa");

		CPatch::RedirectFunction(
			(uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN11TextManager3GetEPKc"),
				(void*)&test);

		// CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x43C8A9), &patch_LoadingScreen_43C8A9);
	}
	*/
	#elif defined(IS_PLATFORM_ANDROID_ARM64_V8A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_10_ANDROID_ARM64_V8A)
	{
		ApplyHook_GTASA_prolog();

		using namespace Game_GTASA;

		if (gameVersion == GAME_VERSION_GTA_SA_2_10_ANDROID_ARM64_V8A)
		{
			// asm_
		}
	}
	#endif
}

// Adds callback
void LoadingScreenFontHooks::AddCallback(tLoadingScreenFontFunction function, void* pCustomData)
{
	if (m_numberOfCallbacksRegistered >= _countof(this->m_callbackList))
		throw f92_runtime_error(
			"Too many elements into LoadingScreenFontHooks function list"
		);

	tLoadingScreenFontCallback* pCallback
		= &this->m_callbackList[this->m_numberOfCallbacksRegistered++];
	
	pCallback->funcPtr = function;
	pCallback->pCustomData = pCustomData;
}
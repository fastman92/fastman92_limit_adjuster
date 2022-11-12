/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "FXTloader.h"
#include "../Core/LimitAdjuster.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/FormattedOutput.h"

#include <fileIO.h>
#include <MultiPlatformSupport/PlatformGeneralisation.h>
#include <StrLexStuff.h>

#ifdef IS_PLATFORM_WIN_X64
#include <MinHook\include\MinHook.h>
#endif

using namespace Game;

FXTloader g_FxtLoader;

// Returns pointer to GXT entry
const void* __cdecl GetFXTentryGen(const char* key)
{
	return g_FxtLoader.pUsedFXTloader->GetFXTentryGen(key);
}

// Constructor
CFXTloaderBase::CFXTloaderBase()
{
	this->m_MaxKeyLength = -1;
}

// Sets max key length
void CFXTloaderBase::SetMaxKeyLength(int keyLength)
{
	this->m_MaxKeyLength = keyLength;
}

// Loads FXT files
void CFXTloaderBase::LoadFXTfiles(const char* directory)
{
#ifdef IS_PLATFORM_WIN
	BrowseDirectory(
		directory, 
		[](const char* filename, void* pUserData)
		{
			CFXTloaderBase* pFXTloader = (CFXTloaderBase*)pUserData;

			FILE* fp = fopen(filename, "r");

			if (!fp)
				return false;

			char line[1024];
			std::string GXTlabel;

			while (fgets(line, sizeof(line), fp))
			{
				char* iLine = FindFirstNonWhiteCharacter(line);

				if (*iLine == '#' || iLine == NULL)
					continue;

				GXTlabel = ReadIdentifier<char, std::string>(iLine, &iLine);

				if (*iLine != ' ')
					continue;

				iLine++;

				char* pText = iLine;

				// remove white characters
				{
					int i = 0;

					while (pText[i])
						i++;

					if (i > 0)
					{
						i--;

						while (i >= 0 && pText[i] == '\n' || pText[i] == '\r')
							pText[i--] = NULL;
					}
				}

				pFXTloader->AddFXTentry(GXTlabel.c_str(), pText);
			}

			fclose(fp);

			return false;
		},
		this
	);
#endif
}

// Adds FXT entry
void CFXTloaderUnicode::AddFXTentry(const char* key, const char* text)
{
	std::string xKey = key;

	if (m_MaxKeyLength > 0 && xKey.length() > (size_t)m_MaxKeyLength)
		xKey.erase(xKey.begin() + m_MaxKeyLength, xKey.end());
		
	this->m_FXTentryMap[xKey] = std::wstring(text, text + strlen(text));
}

// Returns pointer to GXT entry
const wchar_t* CFXTloaderUnicode::GetFXTentry(const char* key)
{
	auto it = this->m_FXTentryMap.find(key);

	if (it != this->m_FXTentryMap.end())
		return it->second.c_str();
	else
		return NULL;
}

// Adds FXT entry
void CFXTloaderASCII::AddFXTentry(const char* key, const char* text)
{
	std::string xKey = key;

	if (m_MaxKeyLength > 0 && xKey.length() > (size_t)m_MaxKeyLength)
		xKey.erase(xKey.begin() + m_MaxKeyLength, xKey.end());

	this->m_FXTentryMap[xKey] = text;
}

// Returns pointer to GXT entry
const char* CFXTloaderASCII::GetFXTentry(const char* key)
{
	auto it = this->m_FXTentryMap.find(key);

	if (it != this->m_FXTentryMap.end())
		return it->second.c_str();
	else
		return NULL;
}

// GTA IV
#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTAIV
{
	uint32_t Address_CText__GetText_goBack = NULL;
	uint32_t Address__security_cookie = NULL;

	NAKED void CText__GetText_start()
	{
		__asm
		{
			sub     esp, 44h;
			mov eax, Address__security_cookie;
			mov eax, [eax];
			jmp Address_CText__GetText_goBack;
		}
	}

	NAKED void patch_CText__GetText()
	{
		__asm
		{
			push esi;

			mov esi, ecx;

			mov eax, [esp + 8];
			push eax;
			call GetFXTentryGen;
			add esp, 4;

			test eax, eax;
			jnz doReturn;

			mov ecx, esi;
			mov eax, [esp + 8];
			push eax;
			call CText__GetText_start;

			doReturn:
			pop esi;
			retn 4;
		}
	}
}
#endif

#ifdef IS_PLATFORM_WIN_X64
// GTA V
namespace Game_GTAV
{
	// Pointer for calling original CText::GetText
	void* fpCText__GetText;

	const char* example = "EXAMPLE";

	NAKED void DetourCText__GetText()
	{
		__asm
		{
			mov[rsp + 8], rcx;
			mov[rsp + 16], rdx;
			push rbp;

			// rsp = -8
			lea rbp, [rsp+8];
			sub rsp, 0x20;
			// rsp = -0x28

			mov rcx, rdx;
			call GetFXTentryGen;

			test rax, rax;
			jnz doReturn;

			mov rcx, [rbp + 8];
			mov rdx, [rbp + 16];

			call qword ptr[fpCText__GetText];

			// mov rax, 355;

		doReturn:
			add rsp, 0x20;

			pop rbp;
			retn;
		}
	}

	// Applies FXT loader
	const char* DoApplyFXTloader()
	{
		uintptr_t pReplayOutOfMemory = (uintptr_t)g_mScanner.FindString("REPLAY_OUT_OF_MEMORY");

		if (!pReplayOutOfMemory)
			return "pReplayOutOfMemory = NULL;";

		uintptr_t pCallToGetText = (uintptr_t)g_mScanner.FindWithFunction(
			[](tMemoryScanControl& control, void* pCustomData)
		{
			uintptr_t pReplayOutOfMemory = (uintptr_t)pCustomData;

			const uint8_t* ptr = (const uint8_t*)control.pMemoryAccessor->Read(control.ptr, 7 + 7 + 5);

			/*
				.text:000000014012C7D4 048                 lea     rdx, aReplay_out_of_ ; "REPLAY_OUT_OF_MEMORY"
				.text:000000014012C7DB 048                 lea     rcx, unk_1422B89B0
				.text:000000014012C7E2 048                 call    CText__GetText
			*/
			if (ptr[0] == 0x48 && ptr[1] == 0x8D && ptr[2] == 0x15
				&& ptr[7] == 0x48 && ptr[8] == 0x8D
				&& ptr[14] == 0xE8
				)
			{
				uintptr_t RDX_target = (uintptr_t)ptr + 7 + *(DWORD*)(ptr + 3);

				return RDX_target == pReplayOutOfMemory;
			}

			return false;
		},

			7 + 7 + 5,

			1,

			(void*)pReplayOutOfMemory
			);

		if (!pCallToGetText)
			return "pCallToGetText = NULL;";

		pCallToGetText += 15;	// call argument.

		uintptr_t pGetText = *(DWORD*)pCallToGetText + pCallToGetText + 4;

		if(MH_CreateHook((void*)pGetText, &DetourCText__GetText, &fpCText__GetText) != MH_OK)
			return "MH_CreateHook unsuccessful";

		if (MH_EnableHook((void*)pGetText) != MH_OK)
			return "MH_EnableHook unsuccessful";

		// printf_MessageBox("replay: 0x%llX", pGetText);

		/////////////////////////////

		g_FxtLoader.pUsedFXTloader = &g_FxtLoader.m_FXTloaderASCII;
		g_FxtLoader.pUsedFXTloader->LoadFXTfiles("FXT");
		
		return NULL;
	}
}
#endif

// Applies FXT loader
void FXTloader::ApplyFXTloader()
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86	
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_3_0_WIN_X86)
	{
		using namespace Game_GTAIV;
		uintptr_t Address_CText__GetText = 0;		
		
		if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86)
		{
			pUsedFXTloader = &this->m_FXTloaderASCII;
			Address_CText__GetText = g_mCalc.GetCurrentVAbyPreferedVA(0x7E9010);
			Address_CText__GetText_goBack = g_mCalc.GetCurrentVAbyPreferedVA(0x7E9018);
			Address__security_cookie = g_mCalc.GetCurrentVAbyPreferedVA(0xEC9BE0);
		}
		else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		{
			pUsedFXTloader = &this->m_FXTloaderUnicode;
			Address_CText__GetText = g_mCalc.GetCurrentVAbyPreferedVA(0x7B54C0);
			Address_CText__GetText_goBack = g_mCalc.GetCurrentVAbyPreferedVA(0x7B54C8);
			Address__security_cookie = g_mCalc.GetCurrentVAbyPreferedVA(0xF43F40);			
		}
		else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		{
			pUsedFXTloader = &this->m_FXTloaderUnicode;
			Address_CText__GetText = g_mCalc.GetCurrentVAbyPreferedVA(0x8A4000);
			Address_CText__GetText_goBack = g_mCalc.GetCurrentVAbyPreferedVA(0x8A4008);
			Address__security_cookie = g_mCalc.GetCurrentVAbyPreferedVA(0xF62C40);
		}
		else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
		{
			pUsedFXTloader = &this->m_FXTloaderUnicode;
			Address_CText__GetText = g_mCalc.GetCurrentVAbyPreferedVA(0x7D0120);
			Address_CText__GetText_goBack = g_mCalc.GetCurrentVAbyPreferedVA(0x7D0128);
			Address__security_cookie = g_mCalc.GetCurrentVAbyPreferedVA(0xF3EF54);
		}
		else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_3_0_WIN_X86)
		{
			pUsedFXTloader = &this->m_FXTloaderUnicode;
			Address_CText__GetText = g_mCalc.GetCurrentVAbyPreferedVA(0x86EC10);
			Address_CText__GetText_goBack = g_mCalc.GetCurrentVAbyPreferedVA(0x86EC18);
			Address__security_cookie = g_mCalc.GetCurrentVAbyPreferedVA(0xF5EBB0);
		}

		// Address_CText__GetText_goBack = Address_CText__GetText + 8;

		CPatch::RedirectCode(Address_CText__GetText, &patch_CText__GetText);	

		pUsedFXTloader->SetMaxKeyLength(8);
		pUsedFXTloader->LoadFXTfiles("FXT");

		CGenericLogStorage::SaveTextLn("FXT loader is enabled.");
		CGenericLogStorage::WriteLineSeparator();
	}
	#elif defined(IS_PLATFORM_WIN_X64)
	else if (CGameVersion::IsAny_GTA_V_WIN_X64(gameVersion))
	{
		using namespace Game_GTAV;
		const char* error = DoApplyFXTloader();

		if (error)
			CGenericLogStorage::SaveFormattedTextLn("FXT loader, error: %s", error);
		else
			CGenericLogStorage::SaveTextLn("FXT loader is enabled.");

		CGenericLogStorage::WriteLineSeparator();
	}
#endif
}
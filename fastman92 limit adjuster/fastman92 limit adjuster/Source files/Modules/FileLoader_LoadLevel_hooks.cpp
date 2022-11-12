/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "FileLoader_LoadLevel_hooks.h"

#include "../Core/CPatch.h"
#include "../Core/FormattedOutput.h"

#include "../Core/LimitAdjuster.h"

#include <Array\countof.h>
#include <MultiPlatformSupport/PlatformGeneralisation.h>

#include <string.h>

using namespace Game;

LoadLevelHooks g_loadLevelHooks;

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	static const char* TEXDICTION = "TEXDICTION";

	NAKED void patch_CFileLoader__LoadLevel_5B90A1()
	{
		__asm
		{
			push esi;
			mov ecx, ASM_GET_OFFSET_OF_FLA_MODULE(g_loadLevelHooks);
			call LoadLevelHooks::ProcessListOfKeywords;

			test al, al;
			jnz loadNextLine;

			push    10;
			push esi;
			push TEXDICTION;

			push 0x5B90A9;
			retn;

		loadNextLine:
			push 0x5B92E1;
			retn;
		}
	}
}
#endif

// Checks list of keywords and calls function
bool LoadLevelHooks::ProcessListOfKeywords(const char* line)
{
	for (unsigned int i = 0; i < ms_numberOfKeywordsRegistered; i++)
	{
		const tLoadLevelHook* pHook = &ms_keywordList[i];

		if (!strncmp(line, pHook->keyword, strlen(pHook->keyword)))
		{
			pHook->function(line);
			return true;
		}
	}

	return false;
}

// Adds function handler
void LoadLevelHooks::AddKeywordHandler(const char* keywordName, bool(* function)(const char* line))
{
	if (ms_numberOfKeywordsRegistered > _countof(ms_keywordList))
		throw f92_runtime_error(
			"Too many elements into LoadLevelHooks keyword list"
		);

	tLoadLevelHook* pHook = &ms_keywordList[ms_numberOfKeywordsRegistered++];
	pHook->function = function;
	strncpy(pHook->keyword, keywordName, sizeof(pHook->keyword));
}

// Initializes class
void LoadLevelHooks::Initialise()
{
	ms_numberOfKeywordsRegistered = 0;
	this->bIsHookActive = false;
}

// Applies hook if neccessary
void LoadLevelHooks::ApplyHook()
{
	if (this->ms_numberOfKeywordsRegistered == 0)
		return;

	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		this->bIsHookActive = true;
		
		CPatch::RedirectCode(0x5B90A1, &patch_CFileLoader__LoadLevel_5B90A1);
	}
#endif	
}
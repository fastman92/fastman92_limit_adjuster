/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "DebugOutput.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/FormattedOutput.h"
#include "IMGlimits.h"
#include "../Core/LimitAdjuster.h"

using namespace Game;

DebugOutput g_debugOutput;

#ifdef IS_PLATFORM_WIN
void DoSomethingWithDebugString(const char* str)
{
	OutputDebugStringA(str);
}

// sprintf altered
int sprintf_altered(char * str, const char * format, ...)
{
	va_list args;
	va_start(args, format);
	int l = vsprintf(str, format, args);

	DoSomethingWithDebugString(str);

	va_end(args);

	return l;
}
#endif

// Enables debug output
void DebugOutput::EnableDebugOutput()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		CPatch::GetPointerToSettings()->bPatchForbiddenCheck = false;

		CPatch::RedirectFunction(0x821982, &OutputFormattedDebugString);

		////////// sprintf ///////////
		#if TRUE
		{
			CPatch::PutCallFunction(0x40E9A6, &sprintf_altered);	// call    _sprintf	; sub_40E960
			CPatch::PutCallFunction(0x424CC3, &sprintf_altered);	// call    _sprintf	; sub_424210
			CPatch::PutCallFunction(0x4A9399, &sprintf_altered);	// call    _sprintf	; sub_4A9360
			CPatch::PutCallFunction(0x50F8E5, &sprintf_altered);	// call    _sprintf	; sub_50F3F0
			CPatch::PutCallFunction(0x50F916, &sprintf_altered);	// call    _sprintf	; sub_50F3F0
			CPatch::PutCallFunction(0x50F94F, &sprintf_altered);	// call    _sprintf	; sub_50F3F0
			CPatch::PutCallFunction(0x54EC68, &sprintf_altered);	// call    _sprintf	; sub_54EC00
			CPatch::PutCallFunction(0x56423F, &sprintf_altered);	// call    _sprintf	; sub_564050
			CPatch::PutCallFunction(0x56426E, &sprintf_altered);	// call    _sprintf	; sub_564050
			CPatch::PutCallFunction(0x5642B0, &sprintf_altered);	// call    _sprintf	; sub_564050
			CPatch::PutCallFunction(0x5642DF, &sprintf_altered);	// call    _sprintf	; sub_564050
			CPatch::PutCallFunction(0x564309, &sprintf_altered);	// call    _sprintf	; sub_564050
			CPatch::PutCallFunction(0x5B36A4, &sprintf_altered);	// call    _sprintf	; sub_5B3680
			CPatch::PutCallFunction(0x5B90EF, &sprintf_altered);	// call    _sprintf	; sub_5B9030
			CPatch::PutCallFunction(0x5C046A, &sprintf_altered);	// call    _sprintf	; sub_5C0280
			CPatch::PutCallFunction(0x5D0C60, &sprintf_altered);	// call    _sprintf	; sub_5D08C0
			CPatch::PutCallFunction(0x5D0C7E, &sprintf_altered);	// call    _sprintf	; sub_5D08C0
			CPatch::PutCallFunction(0x5D0C9C, &sprintf_altered);	// call    _sprintf	; sub_5D08C0
			CPatch::PutCallFunction(0x5DD64A, &sprintf_altered);	// call    _sprintf	; sub_5DD3B0
			CPatch::PutCallFunction(0x6F0DB2, &sprintf_altered);	// call    _sprintf	; sub_6F0D90
			CPatch::PutCallFunction(0x6F0DD3, &sprintf_altered);	// call    _sprintf	; sub_6F0D90
		}
		#endif
		//////////////////////////////
	}
	#elif defined(IS_PLATFORM_WIN_X64)
	else if (gameVersion == GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14718_WIN_X64)
	{
		CPatch::RedirectFunction(g_mCalc.GetCurrentVAbyPreferedVA(0x140B7D9D0), &DoSomethingWithDebugString);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CGenericLogStorage::SaveFormattedTextLn("Debugging output is enabled now. Use debugger to catch messages.");
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

#ifdef IS_PLATFORM_WIN_X86
void __cdecl LogLoadedFile(int ID)
{
	const char* filename = g_fileIDlimits.CStreaming__ms_aInfoForModelExtension[ID].m_Filename;

	CGenericLogStorage::SaveFormattedTextLn("Loaded ID %d, file %s", ID, filename);
	CGenericLogStorage::SaveWorkBuffer();
}

namespace Game_GTASA
{
	NAKED void patch_CStreaming__ConvertBufferToObject_40C6BE()
	{
		__asm
		{
			push ecx;

			push esi;
			call LogLoadedFile;
			add esp, 4;

			pop ecx;

			push    edi;
			lea     edx, [esp + 30h - 0x1C];

			push 0x40C6C3;
			retn;
		}
	}
}
#endif

// Enables logging of files loaded
void DebugOutput::EnableLoggingOfFilesLoaded()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
	{
		using namespace Game_GTASA;

		if (!g_IMGlimits.bHandlingOfNewEnhancedFormatOfImgArchivesEnabled)
			throw f92_runtime_error(
				"\"Enable logging of files loaded\" requires handling of enhanced IMG archives to be enabled."
			);

		CPatch::RedirectCode(0x40C6BE, &patch_CStreaming__ConvertBufferToObject_40C6BE);
	}
	#endif
	else
		return;

	CGenericLogStorage::SaveFormattedTextLn("\"Enable logging of files loaded\" is enabled now.");
	CGenericLogStorage::WriteLineSeparator();
}

// Redirects game new and delete to the FLA
void DebugOutput::RedirectGameNewAndDeleteToTheFLA()
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();	

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		CPatch::GetPointerToSettings()->bPatchForbiddenCheck = false;

		// operator new(unsigned int)
		{
			void* (*ptr)(size_t size) = operator new;
			CPatch::RedirectFunction(0x82119A, ptr);
		}

		// operator new[](unsigned int)
		{
			void* (*ptr)(size_t size) = operator new[];
			CPatch::RedirectFunction(0x821195, ptr);
		}

		// operator delete(void *ptr)
		{
			void(*ptr)(void* block) = operator delete;
			CPatch::RedirectFunction(0x8214BD, ptr);
		}
		
		// operator delete[](void *)
		{
			void (*ptr)(void* block) = operator delete[];
			CPatch::RedirectFunction(0x8213AE, ptr);
		}
	}
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CGenericLogStorage::SaveFormattedTextLn("\"Redirect game new and delete to the FLA\" is enabled now.");
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}
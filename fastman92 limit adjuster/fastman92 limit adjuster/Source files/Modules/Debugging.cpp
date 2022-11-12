/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "Debugging.h"
#include "../Core/CPatch.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

using namespace Game;

Debugging g_debugging;

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_CPad__UpdatePads_541E10()
	{
		__asm
		{
			mov     ecx, 0x4D;		// sizeof(CPad) / 4
			mov     esi, 0xB73458;	// &Pads[0];
			mov     edi, 0xB7358C;	// &Pads[1];
			rep movsd;

			mov eax, 0x541E1C;
			jmp eax;
		}
	}
}
#endif

// Sets pad 1 to act like pad 0
void Debugging::SetPad1actLikePad0()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		CPatch::RedirectCode(0x541E10, &patch_CPad__UpdatePads_541E10);
	}
	#endif
	else
		return;

	CGenericLogStorage::SaveFormattedTextLn("\"Copy info to pad 1 from pad 0\" is enabled now.");
	CGenericLogStorage::WriteLineSeparator();
}
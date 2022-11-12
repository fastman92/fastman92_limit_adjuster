#include "InlinedCodeRemoving.h"


#include "../Core/CCodeMover.h"
#include "../Core/LimitAdjuster.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

#include <string.h>

using namespace Game;

InlinedCodeRemoving g_InlinedCodeRemoving;

// Initializes
void InlinedCodeRemoving::Initialise()
{
	memset(this->m_bInlineRemove, false, eInlineRemove_Max);
}

// Switches action state
void InlinedCodeRemoving::SwitchHookEnabled(eInlineRemove type, bool bEnable)
{
	this->m_bInlineRemove[type] = bEnable;
}

// Returns true if action is enabled.
bool InlinedCodeRemoving::IsHookEnabled(eInlineRemove type)
{
	return this->m_bInlineRemove[type];
}


#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	static NAKED void patch_CTxdStore__Initialise_731F86()
	{
		__asm
		{
			push 0x872AEC;	// *
			mov eax, 0x731C80;	// CTxdStore::AddTxdSlot
			call eax;
			add esp, 4;

			mov edx, eax;
			push 0x731FC4;
			retn;
		}
	}
}
#endif

// Applies patch of inline removing
void InlinedCodeRemoving::ApplyHook()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (IsHookEnabled(eInlineRemove_CTxdStore__AddTxdSlot))
		{
			CPatch::RedirectCode(0x731F86, &patch_CTxdStore__Initialise_731F86);
			CPatch::NOPinstructions(0x731FCA, 3);
		}
	}
#endif
}
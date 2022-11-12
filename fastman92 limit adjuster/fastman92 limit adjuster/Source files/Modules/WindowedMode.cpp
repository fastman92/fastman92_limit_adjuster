#include "WindowedMode.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/LimitAdjuster.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

using namespace Game;

WindowedMode g_windowedMode;

#ifdef IS_PLATFORM_WIN_X86
#include <MinHook\include\MinHook.h>
// Bully Scholarschip Edition
namespace Game_BullyScholarschipEdition
{
	NAKED void patch_82BA8A()
	{
		__asm
		{
			mov byte ptr[ebx + 34h], 0;

			push    esi;
			mov esi, ecx;
			mov     ecx, [esi + 14h];

			push 0x82BA90;
			retn;
		}
	}

	int
		(WINAPI*
			fpShowCursor)(
				_In_ BOOL bShow) = &ShowCursor;

	int
		WINAPI
		DetouredShowCursor(
			_In_ BOOL bShow) {
		return fpShowCursor(true);
	}
}
#endif


// Initialize
void WindowedMode::Initialise()
{

}

// Applies loader
void WindowedMode::ApplyWindowedMode()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
	{
		using namespace Game_BullyScholarschipEdition;

		CPatch::RedirectCode(0x82BA8A, &patch_82BA8A);
		CPatch::PatchUINT8(0x405580, 0xC3);
		MH_CreateHook(&ShowCursor, &DetouredShowCursor, (void**)&fpShowCursor);
		MH_EnableHook(&ShowCursor);
	}
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CGenericLogStorage::SaveTextLn(
		"Windowed mode enabled."
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}
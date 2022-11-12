/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CoordinateMover.h"
#include "FileLoader_LoadLevel_hooks.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/CPatch.h"
#include "../Core/LimitAdjuster.h"

#include <CVector.h>
#include <MultiPlatformSupport/PlatformGeneralisation.h>

using namespace Game;

CoordinateMover g_coordinateMover;

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	// Patch 0x5386D9
	NAKED void patch_5386D9()
	{
		__asm
		{
			fld[esp + 0x74 - 0x28];		// position X
			fadd ASM_ACCESS_LIMIT_VAR_32_BIT(g_coordinateMover, CoordinateMover, m_fRelativePosX);
			fstp[esp + 0x74 - 0x28];

			fld[esp + 0x74 - 0x28 + 4];		// position Y
			fadd ASM_ACCESS_LIMIT_VAR_32_BIT(g_coordinateMover, CoordinateMover, m_fRelativePosY);
			fstp[esp + 0x74 - 0x28 + 4];

			fld[esp + 0x74 - 0x28 + 8];		// position Z
			fadd ASM_ACCESS_LIMIT_VAR_32_BIT(g_coordinateMover, CoordinateMover, m_fRelativePosZ);
			fstp[esp + 0x74 - 0x28 + 8];

			////

			lea eax, [esp + 34h];	// modelName
			push eax;

			lea ecx, [esp + 50h];
			push ecx;

			// go back
			push 0x5386E3;
			retn;
		}
	}
}
#endif

// Command MOVE_COORDS
bool LoadLevel_MOVE_COORDS(const char* line)
{

	//sscanf(line, "MOVE_COORDS %f %f %f",
	//	&CCodeMover::m_fRelativePosX, &m_fRelativePosY, &m_fRelativePosZ);

	// printf_MessageBox("move coords! %f %f %f", pos.x, pos.y, pos.z);
	return false;
}

// Command MOVE_COORDS
bool LoadLevel_RESET_COORDS(const char* line)
{
	g_coordinateMover.m_fRelativePosX = 0.0;
	g_coordinateMover.m_fRelativePosY = 0.0;
	g_coordinateMover.m_fRelativePosZ = 0.0;
		
	return false;
}

// Initialize
void CoordinateMover::Initialise()
{
	this->m_fRelativePosX = 0.0;
	this->m_fRelativePosY = 0.0;
	this->m_fRelativePosZ = 0.0;
}

// Applies patch of coordinate mover.
void CoordinateMover::ApplyHook()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		g_loadLevelHooks.AddKeywordHandler("MOVE_COORDS", &LoadLevel_MOVE_COORDS);
		g_loadLevelHooks.AddKeywordHandler("RESET_COORDS", &LoadLevel_RESET_COORDS);

		CPatch::RedirectCode(0x5386D9, &patch_5386D9);
	}
#endif
	else
		return;

	CGenericLogStorage::SaveFormattedTextLn("Coordinate mover enabled.");
	CGenericLogStorage::WriteLineSeparator();
}
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPad.h"

#include "../../Core/LimitAdjuster.h"

using namespace Game;

CPad_VarInitialisation g_CPad_varInitialisation;

void* Address_CPad__GetPad;

// Returns a pointer to pad structure
CPad* CPad::GetPad(int padNumber)
{
	return ((CPad* (*)(int padNumber))Address_CPad__GetPad)(padNumber);
}

// Initialize
void CPad_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_III_1_0_WIN_X86)
		Address_CPad__GetPad = (void*)0x492F60;
#endif
	else
		Address_CPad__GetPad = nullptr;
}
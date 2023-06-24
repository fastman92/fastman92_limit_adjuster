/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CFont.h"

#include "../../Core/LimitAdjuster.h"

CFont_VarInitialisation g_CFont_varInitialisation;

using namespace Game;

//////////
// FASTMAN92_TODO:
// figure out why CRGBA gets passed by pointer on ANDROID_ARM32

//////////
static uintptr_t Address_CFont__SetBackground = 0;;
static uintptr_t Address_CFont__SetBackgroundOff = 0;
static uintptr_t Address_CFont__SetScale_oneParam = 0;
static uintptr_t Address_CFont__SetScale_twoParams = 0;
static uintptr_t Address_CFont__SetJustify = 0;
static uintptr_t Address_CFont__SetOrientation = 0;
static uintptr_t Address_CFont__SetFontStyle = 0;
static uintptr_t Address_CFont__SetCentreSize = 0;
static uintptr_t Address_CFont__SetColor = 0;;
static uintptr_t Address_CFont__SetWrapx = 0;;
static uintptr_t Address_CFont__PrintString = 0;
static uintptr_t Address_CFont__PrintStringBully = 0;
static uintptr_t Address_CFont__SetPropOn = 0;
static uintptr_t Address_CFont__SetRightJustifyOff = 0;
static uintptr_t Address_CFont__SetRightJustifyWrap = 0;
static uintptr_t Address_CFont__SetJustifyOff = 0;

//////////

void CFont::SetPropOn()
{
	g_memoryCall.Function<void>(Address_CFont__SetPropOn);
}

void CFont::SetRightJustifyOff()
{
	g_memoryCall.Function<void>(Address_CFont__SetRightJustifyOff);
}

void CFont::SetScale(float w, float h)
{
	g_memoryCall.Function<void>(Address_CFont__SetScale_twoParams, w, h);
}

void CFont::SetScale(float w)
{
	g_memoryCall.Function<void>(Address_CFont__SetScale_oneParam, w);
}

void CFont::SetColor(CRGBA color)
{
	MAKE_VAR_GAME_VERSION();

	if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		g_memoryCall.Function<void>(Address_CFont__SetColor, color);
	else
		g_memoryCall.Function<void>(Address_CFont__SetColor, &color);
}

// setups text background
void CFont::SetBackground(bool enable, bool includeWrap)
{
	g_memoryCall.Function<void>(Address_CFont__SetBackground, enable, includeWrap);
}

void CFont::SetBackgroundOff()
{
	g_memoryCall.Function<void>(Address_CFont__SetBackgroundOff);
}

void CFont::SetJustify(unsigned char on)
{
	g_memoryCall.Function<void>(Address_CFont__SetJustify, on);
}

// set text style
void CFont::SetFontStyle(int style)
{
	g_memoryCall.Function<void>(Address_CFont__SetFontStyle, style);
}

void CFont::SetOrientation(unsigned char alignment)
{
	g_memoryCall.Function<void>(Address_CFont__SetOrientation, alignment);
}

// set line width at center
void CFont::SetCentreSize(float value)
{
	g_memoryCall.Function<void>(Address_CFont__SetCentreSize, value);
}

// set line width at right
void CFont::SetWrapx(float value)
{
	g_memoryCall.Function<void>(Address_CFont__SetWrapx, value);
}

// Prints a string
void CFont::PrintString(float x, float y, const void *text)
{
	g_memoryCall.Function<void>(Address_CFont__PrintString, x, y, text);
}

// Prints a string
void CFont::PrintStringBully(float x, float y, const void *text, bool flag)
{
	g_memoryCall.Function<void>(Address_CFont__PrintStringBully, x, y, text, flag);
}

// Initialize
void CFont_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (!g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		return;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_III_1_0_WIN_X86)
	{
		Address_CFont__SetBackgroundOff = 0x501CF0;
		Address_CFont__SetScale_twoParams = 0x501B80;
		Address_CFont__SetFontStyle = 0x501DB0;
		Address_CFont__SetCentreSize = 0x501CD0;
		Address_CFont__SetColor = 0x501BD0;
		Address_CFont__PrintString = 0x500F50;
		Address_CFont__SetPropOn = 0x501DA0;
	}
	else if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
	{
		Address_CFont__SetBackgroundOff = 0x5500D0;
		Address_CFont__SetFontStyle = 0x54FFE0;
		Address_CFont__SetColor = 0x550170;
		Address_CFont__PrintString = 0x551040;
		Address_CFont__SetPropOn = 0x550020;
		Address_CFont__SetRightJustifyOff = 0x550040;
	}
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		Address_CFont__SetBackground = 0x7195C0;
		Address_CFont__SetJustify = 0x719600;
		Address_CFont__SetScale_twoParams = 0x719380;
		Address_CFont__SetOrientation = 0x719610;
		Address_CFont__SetFontStyle = 0x719490;
		Address_CFont__SetCentreSize = 0x7194E0;
		Address_CFont__SetColor = 0x719430;
		Address_CFont__SetWrapx = 0x7194D0;
		Address_CFont__PrintString = 0x71A700;
	}
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
	{
		Address_CFont__PrintStringBully = 0x68D450;
	}
	#elif defined(IS_PLATFORM_ANDROID)	
	{
		Address_CFont__SetBackground = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont13SetBackgroundEhh"
		);

		Address_CFont__SetBackgroundOff = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont16SetBackgroundOffEv"
		);

		Address_CFont__SetScale_oneParam = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont8SetScaleEf"
		);

		Address_CFont__SetScale_twoParams = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont8SetScaleEff"
		);

		Address_CFont__SetJustify = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont10SetJustifyEh"
		);

		Address_CFont__SetOrientation = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont14SetOrientationEh"
		);

		
		Address_CFont__SetFontStyle = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont12SetFontStyleEs"
		);	// void CFont::SetFontStyle(short)

		if(!Address_CFont__SetFontStyle)
			Address_CFont__SetFontStyle = (uintptr_t)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN5CFont12SetFontStyleEh"
			);	// void CFont::SetFontStyle(uchar)

		Address_CFont__SetCentreSize = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont13SetCentreSizeEf"
		);

		Address_CFont__SetColor = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont8SetColorE5CRGBA"
		);

		Address_CFont__SetWrapx = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont8SetWrapxEf"
		);

		Address_CFont__PrintString = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont11PrintStringEffPt"
		);

		Address_CFont__SetPropOn = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont9SetPropOnEv"
		);

		Address_CFont__SetRightJustifyOff = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont18SetRightJustifyOffEv"
		);

		Address_CFont__SetRightJustifyWrap = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont19SetRightJustifyWrapEf"
		);

		Address_CFont__SetJustifyOff = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN5CFont13SetJustifyOffEv"
		);
	}
	#endif
}
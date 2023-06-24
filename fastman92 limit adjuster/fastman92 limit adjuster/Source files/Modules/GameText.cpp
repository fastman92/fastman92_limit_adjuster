/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "GameText.h"

#include "../Core/LimitAdjuster.h"

CGameText g_GameText;

using namespace Game;

// Converts ASCII text to Unicode text
unsigned int CGameText::AsciiToUnicode(const char* src, unsigned short* dst)
{
	unsigned int len = 0;

	while (char c = *src)
	{
		*dst = c;
		len++;
		src++;
		dst++;
	}

	*dst = 0;
	return len;
}

// Converts ASCII text to Unicode text. Returns the length of string
unsigned int CGameText::UnicodeTextToAscii(const unsigned short* src, char* dst)
{
	unsigned int len = 0;

	while (*src)
	{
		*dst = (char)*src;
		len++;
		src++;
		dst++;
	}

	*dst = 0;
	return len;
}

// Copies Unicode string
unsigned int CGameText::CopyUnicodeString(const unsigned short* src, unsigned short* dst)
{
	unsigned int len = 0;

	while (unsigned short c = *src)
	{
		*dst = c;
		len++;
		src++;
		dst++;
	}

	*dst = 0;
	return len;
}

// Copies Unicode string, safe version, returns how many characters got copied
unsigned int CGameText::CopyUnicodeStringSafe(const unsigned short* src, unsigned short* dst, unsigned int dst_size)
{
	if (dst_size > 0) {
		size_t i;
		for (i = 0; i < dst_size - 1 && src[i]; i++) {
			dst[i] = src[i];
		}
		dst[i] = '\0';

		return i;
	}
	else
		return 0;
}

/*
// Compares strings
static int CompareStrings(const unsigned short* str1, const char* str2);
{
	return 0;
}
*/

// Initialize
void CGameText::Initialise()
{
	MAKE_VAR_GAME_VERSION();
	this->bUsesUnsignedShortForChars = false;
	
	//////////

#if IS_PLATFORM_ANDROID
	this->bUsesUnsignedShortForChars = true;
#else
	if (gameVersion == GAME_VERSION_GTA_III_1_0_WIN_X86)
		this->bUsesUnsignedShortForChars = true;
	else if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
		this->bUsesUnsignedShortForChars = true;
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		this->bUsesUnsignedShortForChars = false;
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
		this->bUsesUnsignedShortForChars = true;
#endif
}
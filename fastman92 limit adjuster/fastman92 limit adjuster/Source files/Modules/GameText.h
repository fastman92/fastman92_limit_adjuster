/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "../Core/CLimitAdjusterModule.h"

class CGameText : public CLimitAdjusterModule
{
	bool bUsesUnsignedShortForChars;
public:
	// Returns true if game uses unsigned short for characters
	inline bool UsesUnsignedShortForCharacters() {
		return bUsesUnsignedShortForChars;
	};

	// Converts ASCII text to Unicode text. Returns the length of string
	static unsigned int AsciiToUnicode(const char* src, unsigned short* dst);

	// Converts ASCII text to Unicode text. Returns the length of string
	static unsigned int UnicodeTextToAscii(const unsigned short* src, char* dst);

	// Copies Unicode string
	static unsigned int CopyUnicodeString(const unsigned short* src, unsigned short* dst);

	// Copies Unicode string, safe version, returns how many characters got copied
	static unsigned int CopyUnicodeStringSafe(const unsigned short* src, unsigned short* dst, unsigned int dst_size);

	// Compares strings
	static int CompareStrings(const unsigned short* str1, const char* str2);

	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern CGameText g_GameText;
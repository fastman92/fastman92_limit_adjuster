/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CheatStringLoader.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"
#include "../Core/StringFunctions.h"

#include "../GameStructures/Rockstar Games/CKeyGen.h"

#include <fileIO.h>
#include <StrLexStuff.h>

#include <string.h>


using namespace Game;

CheatStringLoader g_cheatStringLoader;

// Initialize
void CheatStringLoader::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	#ifdef IS_PLATFORM_WIN_X86
	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CCheat__m_aCheatHashKeys = (uint32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x8A5CC8);
	#endif
}

// Loads cheat strings
void CheatStringLoader::LoadCheatStrings()
{
	MAKE_VAR_GAME_VERSION();

	if (!CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		return;

#ifdef IS_PLATFORM_WIN_X86
	auto filenamePath = g_LimitAdjuster.GetPathToFlaFileFromRootDirectory("data\\cheatStrings.dat");
	FILE* fp = fopen(filenamePath.c_str(), "r");

	if (!fp)
	{
		CGenericLogStorage::SaveFormattedTextLn("Cheat string loader: cheatStrings.dat coudn't be opened!");
		CGenericLogStorage::WriteLineSeparator();
		return;
	}

	const int numberOfCheats = 92;

	char line[1024];
		
	unsigned int ID;

	char str[31];
	char strReversed[31];

	int lineNum = 0;

	while (LoadLineWithoutCommas(line, sizeof(line), fp))
	{
		lineNum++;

		char* iLine = FindFirstNonWhiteCharacter(line);

		if (!iLine[0] || iLine[0] == '#')
			continue;

		str[0] = NULL;
		sscanf(iLine, "%d %s", &ID, &str);

		if (ID >= numberOfCheats)
		{
			printf_MessageBox(
					"Cheat string loader, line %d, wrong ID: %d\nThere are %d cheats in game",
					lineNum,
					ID,
					numberOfCheats
				);

			continue;
		}

		int l = strlen(str);

		if (!(l == 0 || (l >= 6 || l <= 30)) )
		{
			printf_MessageBox(
				"Cheat string loader, line %d, cheat string has invalid number of characters.\n"
				"The number of characters in string should have zero or between 6 and 30",
				lineNum
				);

			continue;
		}

		uint32_t hash;
			
		if (l != 0)
		{
			GetReversedString(str, strReversed);
			hash = CKeyGen::GetUppercaseKey(strReversed);
		}
		else
			hash = 0;

		// Check if new hash is equal to old hash
		#if FALSE
		{
			if (CCheat__m_aCheatHashKeys[ID] != hash)
			{
				printf_MessageBox("Cheat %d\nOld hash: 0x%X\nNew hash: 0x%X\nNew string: %s",
					ID,
					CCheat__m_aCheatHashKeys[ID],
					hash,
					strReversed
					);
			}
		}
		#endif
			

		CCheat__m_aCheatHashKeys[ID] = hash;
	}

	fclose(fp);

	CGenericLogStorage::SaveFormattedTextLn("Cheat string loader: cheatStrings.dat was loaded.");
	CGenericLogStorage::WriteLineSeparator();
#endif
}
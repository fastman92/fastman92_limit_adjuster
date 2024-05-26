/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "NotApropIDrangeLoader.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"
#include <fileIO.h>
#include "FileIDlimit.h"
#include <StrLexStuff.h>

using namespace Game;

NotApropIDrangeLoader g_notApropIDrangeLoader;

// Checks if ID is not a prop
bool NotApropIDrangeLoader::IsModelUnique(int modelID)
{
	for (auto it = NotAPropIDranges.begin(); it != NotAPropIDranges.end(); ++it)
	{
		if (modelID >= it->lowestID && modelID <= it->highestID)
			return true;
	}

	return false;
}

static bool IsModelUnique(int modelID)
{
	return g_notApropIDrangeLoader.IsModelUnique(modelID);
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_BullyScholarschipEdition
{
	// patch to solve a problem of ECX not being saved
	// the compiler from Bully knew ECX wouldn't be overwritten in the function IsModelUnique
	// my function may overwrite it though
	NAKED void patch_CFileLoader__LoadObject_42AF62()
	{
		__asm
		{
			mov     ecx, [esp + 0B8h - 0xA8];
			push    ecx;
			call IsModelUnique;
			add     esp, 4;

			mov     ecx, [esp + 0B8h - 0xA8];

			test    al, al;

			push 0x42AF71;
			retn;
		}
	}
}
#endif

// Loads not a prop ID ranges
void NotApropIDrangeLoader::LoadNotApropIDranges()
{
	MAKE_VAR_GAME_VERSION();

	using namespace Game_BullyScholarschipEdition;

	this->NotAPropIDranges.clear();

	#ifdef IS_PLATFORM_WIN_X86
	if (gameVersion != GAME_VERSION_BULLY_SE_1_2_WIN_X86)
		return;

	CPatch::EnterNewLevel();

	CPatch::RedirectFunction(0x429FC0, &::IsModelUnique);
	CPatch::RedirectCode(0x42AF62, &patch_CFileLoader__LoadObject_42AF62);

	CPatch::LeaveThisLevel();

	//////////////////////////////////////////////////		

	using namespace Game_BullyScholarschipEdition;

	auto filenamePath = g_LimitAdjuster.GetPathToFlaFileFromRootDirectory(
		"Objects\\bully_scholarship_edition_not_prop_id_ranges.dat");

	FILE* fp = fopen(
		filenamePath.c_str(),
		"r");

	if (!fp)
	{
		CGenericLogStorage::SaveFormattedTextLn("Not a prop ID range loader: bully_scholarship_edition_not_prop_id_ranges.dat coudn't be opened!");
		CGenericLogStorage::WriteLineSeparator();
		return;
	}

	char line[1024];
		
	tModelIDrange range;

	int lineNum = 0;

	tFileTypeLimit modelLimit = g_fileIDlimits.GetFileIDcurrentLimit(GENERAL_FILE_TYPE_MODEL_ARCHIVE);

	while (LoadLineWithoutCommas(line, sizeof(line), fp))
	{
		lineNum++;

		char* iLine = FindFirstNonWhiteCharacter(line);

		if (!iLine[0] || iLine[0] == '#')
			continue;

		sscanf(iLine, "%d %d", &range.lowestID, &range.highestID);
			
		if (range.lowestID <= 0
			|| range.highestID >= modelLimit)
		{
			printf_MessageBox(
				"Not a prop ID range loader: IDs are invalid: %d %d",
				range.lowestID, range.highestID
				);

			continue;
		}
			
		NotAPropIDranges.push_back(range);			
	}

	fclose(fp);

	CGenericLogStorage::SaveTextLn("Not a prop ID range loader: config was loaded.");
	CGenericLogStorage::WriteLineSeparator();
	#endif
}
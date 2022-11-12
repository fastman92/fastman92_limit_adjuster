/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "RadarBlipSpriteFilenameLoader.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/CText.h"

#include <Array\countof.h>
#include <fileIO.h>
#include <StrLexStuff.h>

#include <MultiPlatformSupport/PlatformGeneralisation.h>

using namespace Game;

RadarBlipSpriteFilenameLoader g_RadarBlipSpriteFilenameLoader;

// Set number of type IDs
void RadarBlipSpriteFilenameLoader::SetNumberOfTypeIDs(unsigned int newValue)
{
	this->ms_numberOfTypeIDs = newValue;
}

namespace Game_GTASA
{
	const char* defaultGXTnamesForBlips[] =
	{
		"", // 0
		"", // 1
		"", // 2
		"LG_01", // 3
		"", // 4
		"LG_02", // 5
		"LG_03", // 6
		"LG_04", // 7
		"LG_05", // 8
		"LG_06", // 9
		"LG_07", // 10
		"LG_66", // 11
		"LG_09", // 12
		"LG_10", // 13
		"LG_11", // 14
		"LG_12", // 15
		"LG_13", // 16
		"LG_67", // 17
		"LG_15", // 18
		"LG_16", // 19
		"LG_17", // 20
		"LG_18", // 21
		"LG_19", // 22
		"LG_20", // 23
		"LG_21", // 24
		"LG_22", // 25
		"LG_23", // 26
		"LG_24", // 27
		"LG_25", // 28
		"LG_26", // 29
		"LG_27", // 30
		"LG_28", // 31
		"LG_29", // 32
		"LG_30", // 33
		"LG_31", // 34
		"LG_32", // 35
		"LG_33", // 36
		"LG_63", // 37
		"LG_35", // 38
		"LG_36", // 39
		"LG_37", // 40
		"LG_64", // 41
		"LG_39", // 42
		"LG_40", // 43
		"LG_41", // 44
		"LG_42", // 45
		"LG_43", // 46
		"LG_44", // 47
		"LG_45", // 48
		"LG_46", // 49
		"LG_47", // 50
		"LG_48", // 51
		"LG_51", // 52
		"LG_52", // 53
		"LG_53", // 54
		"LG_57", // 55
		"", // 56
		"LG_65", // 57
		"LG_58", // 58
		"LG_59", // 59
		"LG_60", // 60
		"LG_61", // 61
		"LG_62", // 62
		"LG_34", // 63
	};

	const char* GetGXTkeyByRadarTraceBlipID(int blipID)
	{
		switch (blipID)
		{
		case -1:
			return "LG_49";
		case -2:
			return "LG_50";
		case -3:
			return "LG_54";
		case -4:
			return "LG_55";
		case -5:
			return "LG_56";
		default:
			if (blipID >= 0 &&
				blipID < g_RadarBlipSpriteFilenameLoader.ms_numberOfTypeIDs)
				return g_RadarBlipSpriteFilenameLoader.RadarBlipSpriteInfoExtension[blipID].GXTkey;
		}

		return nullptr;
	}

	const void* GetGXTtextForRadarTraceBlipID(int blipID)
	{
		const char* key = GetGXTkeyByRadarTraceBlipID(blipID);

		if (key)
			return TheText->Get(key);
		else
			return nullptr;
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_84F0DA()
	{
		__asm
		{
			push ASM_ACCESS_LIMIT_VAR_32_BIT(g_RadarBlipSpriteFilenameLoader, RadarBlipSpriteFilenameLoader, ms_numberOfTypeIDs);
			push 4;
			push ASM_ACCESS_LIMIT_VAR_32_BIT(g_RadarBlipSpriteFilenameLoader, RadarBlipSpriteFilenameLoader, CRadar__RadarBlipSprites);

			push 0x84F0E3;
			retn;
		}
	}

	NAKED void patch_856595()
	{
		__asm
		{
			push ASM_ACCESS_LIMIT_VAR_32_BIT(g_RadarBlipSpriteFilenameLoader, RadarBlipSpriteFilenameLoader, ms_numberOfTypeIDs);
			push 4;
			push ASM_ACCESS_LIMIT_VAR_32_BIT(g_RadarBlipSpriteFilenameLoader, RadarBlipSpriteFilenameLoader, CRadar__RadarBlipSprites);

			push 0x85659E;
			retn;
		}
	}

	NAKED void patch_Menu_MapRender_5828A8()
	{
		__asm
		{
			push esi;
			call GetGXTtextForRadarTraceBlipID;
			add esp, 4;

			// go to printing of string
			push 0x582DA7;
			retn;
		}
	}

	NAKED void patch_Menu_MapRender_582DEE()
	{
		__asm
		{
			cmp[esp + 8], 0;
			je doReturn;

			push 0x582DF3;
			push 0x71A700;	// CFont::PrintString
			retn;

		doReturn:
			push 0x582DF3;
			retn;
		}
	}
	#endif
}

// Loads blip sprite filenames
void RadarBlipSpriteFilenameLoader::LoadBlipSpriteFilenames()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	int totalNumberOfElements;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (CPatch::IsDebugModeActive())
			ms_numberOfTypeIDs = 64;

		totalNumberOfElements = RadarBlipSpriteFilenameLoader::ms_numberOfTypeIDs * 2;

		if (this->ms_numberOfTypeIDs > 64)
		{
			CRadar__RadarBlipSprites.gta_sa = new CSprite2d[ms_numberOfTypeIDs];
			memset(CRadar__RadarBlipSprites.gta_sa, NULL, ms_numberOfTypeIDs * sizeof(CSprite2d));
			CRadar__RadarBlipSprites.bIsAllocated.Set(true);

			RadarBlipSpriteFilenames.ptr = new const char*[totalNumberOfElements];
			RadarBlipSpriteFilenames.bIsAllocated.Set(true);

			RadarBlipSpriteInfoExtension = new CRadarBlipSpriteInfoExtension[ms_numberOfTypeIDs];
		}

		// Patch pointers to CRadar::RadarBlipSprites
		#if TRUE
		{ 
			CPatch::PatchPointer(0x5827EA + 1, CRadar__RadarBlipSprites.gta_sa);	// mov     edi, offset _ZN6CRadar16RadarBlipSpritesE; CRadar::RadarBlipSprites	; sub_5827D0
			CPatch::PatchPointer(0x582E51 + 3, CRadar__RadarBlipSprites.gta_sa);	// lea     ecx, _ZN6CRadar16RadarBlipSpritesE.texture[esi*4]; CRadar::RadarBlipSprites	; sub_5828A0
			CPatch::PatchPointer(0x584A4D + 1, CRadar__RadarBlipSprites.gta_sa + 3);	// push    (offset _ZN6CRadar16RadarBlipSpritesE.texture+0Ch); int	; sub_584960
			CPatch::PatchPointer(0x585941 + 1, CRadar__RadarBlipSprites.gta_sa);	// mov     esi, offset _ZN6CRadar16RadarBlipSpritesE; CRadar::RadarBlipSprites	; sub_585940
			CPatch::PatchPointer(0x585950 + 2, CRadar__RadarBlipSprites.gta_sa + ms_numberOfTypeIDs);	// cmp     esi, offset byte_BAA350	; sub_585940
			CPatch::PatchPointer(0x5860F0 + 3, CRadar__RadarBlipSprites.gta_sa);	// lea     ecx, _ZN6CRadar16RadarBlipSpritesE.texture[esi*4]; CRadar::RadarBlipSprites	; sub_585FF0
			CPatch::PatchPointer(0x5876FE + 1, CRadar__RadarBlipSprites.gta_sa + 2);	// push    (offset _ZN6CRadar16RadarBlipSpritesE.texture+8); int	; sub_587000
			CPatch::PatchPointer(0x58777B + 1, CRadar__RadarBlipSprites.gta_sa + 2);	// push    (offset _ZN6CRadar16RadarBlipSpritesE.texture+8); int	; sub_587000
			CPatch::PatchPointer(0x58794C + 1, CRadar__RadarBlipSprites.gta_sa + 56);	// push    (offset _ZN6CRadar16RadarBlipSpritesE.texture+0E0h); int	; sub_587000
			CPatch::PatchPointer(0x587A44 + 1, CRadar__RadarBlipSprites.gta_sa + 57);	// push    (offset _ZN6CRadar16RadarBlipSpritesE.texture+0E4h); int	; sub_587000
			CPatch::PatchPointer(0x587AF0 + 1, CRadar__RadarBlipSprites.gta_sa + 57);	// push    (offset _ZN6CRadar16RadarBlipSpritesE.texture+0E4h); int	; sub_587000
			CPatch::PatchPointer(0x58871D + 1, CRadar__RadarBlipSprites.gta_sa + 2);	// push    (offset _ZN6CRadar16RadarBlipSpritesE.texture+8); int	; sub_588050
			CPatch::PatchPointer(0x84F0DE + 1, CRadar__RadarBlipSprites.gta_sa);	// push    offset _ZN6CRadar16RadarBlipSpritesE; CRadar::RadarBlipSprites	; sub_84F0D0
			CPatch::PatchPointer(0x856599 + 1, CRadar__RadarBlipSprites.gta_sa);	// push    offset _ZN6CRadar16RadarBlipSpritesE; CRadar::RadarBlipSprites	; sub_856590
		}
		#endif

		// Patch pointers to RadarBlipSpriteFilenames
		#if TRUE
		{
			CPatch::PatchPointer(0x5827EF + 1, RadarBlipSpriteFilenames.ptr);
			CPatch::PatchPointer(0x582804 + 2, RadarBlipSpriteFilenames.ptr + totalNumberOfElements);
		}
		#endif

		// Constructor and destructor
		CPatch::RedirectCode(0x84F0DA, &patch_84F0DA);
		CPatch::RedirectCode(0x856595, &patch_856595);

		// Fix a legend map crash
		#if FALSE
		{
			CPatch::EnterNewLevelAndDisableDebugState();

			CPatch::PutOnAddressRelative4byteAddressToAddress(0x5828AE + 2, 0x5831D3);

			static const uint8_t indexes[] = { 5, 6, 7, 9, 61 };

			for (int i = 0; i < _countof(indexes); i++)
				CPatch::PatchUINT32(0x5831D8 + indexes[i] * 4, 0x5831D8);

			CPatch::LeaveThisLevel();
		}
		#endif

		// Patch for the GXT keys
		CPatch::RedirectCode(0x5828A8, &patch_Menu_MapRender_5828A8);
		CPatch::RedirectCode(0x582DEE, &patch_Menu_MapRender_582DEE);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CPatch::LeaveThisLevel();

	//////////////////////////////////////////////////

	using namespace Game_GTASA;

	totalNumberOfElements = this->ms_numberOfTypeIDs * 2;

	for (int i = 0; i < totalNumberOfElements; i++)
		RadarBlipSpriteFilenames.ptr[i] = "";	// empty string
	
	FILE* fp = fopen(g_LimitAdjuster.GetPathToFlaFileFromRootDirectory("data\\gtasa_radarBlipSpriteFilenames.dat").c_str(), "r");

	if (!fp)
	{
		printf_MessageBox("Radar blip sprite filename loader: gtasa_radarBlipSpriteFilenames.dat coudn't be opened!");
		g_LimitAdjuster.TerminateProcess();
		return;
	}
	
	char line[1024];

	unsigned int typeID;

	char textureName[64];
	char GXTkey[16];

	int lineNum = 0;

	while (LoadLineWithoutCommas(line, sizeof(line), fp))
	{
		lineNum++;

		char* iLine = FindFirstNonWhiteCharacter(line);

		if (!iLine[0] || iLine[0] == '#')
			continue;

		textureName[0] = 0;
		int numberOfArgumentsRead = sscanf(iLine, "%d %s %s", &typeID, textureName, GXTkey);				

		if (typeID >= ms_numberOfTypeIDs)
		{
			printf_MessageBox(
				"Radar blip sprite filename loader: type ID %d exceeds the limit of %d IDs.",
				typeID,
				ms_numberOfTypeIDs
				);

			continue;
		}

		// Set the texture name, only if not empty string
		if (textureName[0] && strcmp(textureName, "NULL"))
		{
			int l = strlen(textureName);
			char* strAlloc = new char[l + 1];
			RadarBlipSpriteFilenamesAllocated.push_back(strAlloc);

			strcpy(strAlloc, textureName);

			const char** pSpriteName = RadarBlipSpriteFilenames.ptr + typeID * 2;
			*pSpriteName = strAlloc;
		}

		CRadarBlipSpriteInfoExtension* pExtension = &RadarBlipSpriteInfoExtension[typeID];
		pExtension->GXTkey[0] = 0;

		if (numberOfArgumentsRead >= 3)
		{
			if (strcmp(GXTkey, "NULL"))
				strcpy(pExtension->GXTkey, GXTkey);
		}
		else
		{
			if (typeID <= _countof(defaultGXTnamesForBlips))
				strcpy(pExtension->GXTkey, defaultGXTnamesForBlips[typeID]);
		}
	}

	fclose(fp);

	CGenericLogStorage::SaveFormattedTextLn(
		"Radar blip sprite filename loader: config was loaded. ms_numberOfTypeIDs = %d",
		ms_numberOfTypeIDs
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Initialize
void RadarBlipSpriteFilenameLoader::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	// Radar blip sprite info extension
	this->RadarBlipSpriteInfoExtension = nullptr;

	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		// Number of type IDs
		this->ms_numberOfTypeIDs = 64;

		#ifdef IS_PLATFORM_WIN_X86
		// Radar blip sprite filenames
		this->RadarBlipSpriteFilenames.ptr = (const char**)0x8D0720;

		// Radar blip sprites
		this->CRadar__RadarBlipSprites.gta_sa = (CSprite2d*)0xBAA250;
		#endif
	}
}

// Shutdown
void RadarBlipSpriteFilenameLoader::Shutdown()
{
	MAKE_VAR_GAME_VERSION();

	for (auto str : RadarBlipSpriteFilenamesAllocated)
		delete[] str;

	if (RadarBlipSpriteFilenames.bIsAllocated.Get())
		delete[] RadarBlipSpriteFilenames.ptr;

	if (CGameVersion::IsAny_GTA_SA(gameVersion) && CRadar__RadarBlipSprites.bIsAllocated.Get())
		delete[] CRadar__RadarBlipSprites.gta_sa;

	delete[] RadarBlipSpriteInfoExtension;
}
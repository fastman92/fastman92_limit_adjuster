/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "MapLimits.h"

#include "FileIDlimit.h"
#include "StructureExtension.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"
#include "../Core/ProjectConstants.h"

#include "../GameStructures/Rockstar Games/CCoronas.h"
#include "../GameStructures/Rockstar Games/CMemoryMgr.h"
#include "../GameStructures/Rockstar Games/CStreaming.h"
#include "../GameStructures/Rockstar Games/CWorld.h"
#include "../GameStructures/Rockstar Games/CVehicle.h"
#include "../GameStructures/Rockstar Games/functions.h"
#include "../GameStructures/Rockstar Games/CTimer.h"
#include "../GameStructures/Rockstar Games/Renderware.h"

#include <BitwiseOperation.h>
#include <CBox2D.h>
#include <CVector.h>
#include <PathStructures.h>
#include <StrLexStuff.h>

#include <array>
#include <algorithm>
#include <iterator>

#include <MemoryPermission/MemoryPermission.h>

// Define square root of 2
#ifndef M_SQRT2
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#endif

using namespace Game;

MapLimits g_mapLimits;

// Loads data
void CTrackFilenameLoader::Load(const char* filename)
{
	this->m_vecTrackFilenames.clear();

	FILE* fp = fopen(filename, "r");

	if (!fp)
	{
		printf_MessageBox("Unable to load %s", filename);
		g_LimitAdjuster.TerminateProcess();
	}

	char line[512];

	while (fgets(line, sizeof(line), fp))
	{
		char* iLine = FindFirstNonWhiteCharacter(line);

		if (!iLine[0] || iLine[0] == '#')
			continue;

		std::string filename;

		filename = ReadAnyValue<char, std::string>(iLine, NULL);

		this->m_vecTrackFilenames.push_back(filename);
	}

	fclose(fp);
}

// Track filename loader
CTrackFilenameLoader TrackFilenameLoader;

// Returns a new offset offset, aligned by 4
uint32_t GetNextOffset(uint32_t prev_offset, uint32_t prev_size)
{
	prev_offset += prev_size;

	return prev_offset % 4 == 0 ? prev_offset : ((prev_offset / 4) + 1) * 4;
};

// Validates map size
static bool ValidateMapSize(int originalMapSize, int newMapSize)
{
	if (originalMapSize % 2)
		return false;

	if (newMapSize >= originalMapSize)
	{
		do
		{
			if (newMapSize == originalMapSize)
				return true;

			newMapSize /= 2;
		} while (newMapSize >= originalMapSize);
	}

	return false;
}

// Validates map size, prints a message if map size is wrong.
bool ValidateMapSizeOrShowMessage(int mapSize, const char* limitName)
{
	if (!ValidateMapSize(3000, mapSize))
	{
		throw f92_runtime_error(
			"%s map size should be have a value of 3000, 6000, 12000, 24000 and so on.\nCurrent value: %d",
			limitName,
			mapSize
		);

		return false;
	}
	else
		return true;
}

extern "C"
{
	float fWorldMapMinCoord;
	int iWorldMapMaxCoord;
	float fWorldMapMaxCoord;
	float fWorldMapMaxCoordMinusOne;

	// Sectors
	int iNumberOfWorldSectorsPerDimension;
	int iNumberOfWorldSectorsPerDimensionMinusOne;
	int iNumberOfWorldSectorsPerDimensionMultipliedBy2;
	int iNumberOfWorldSectorsPerDimensionDividedBy8;

	float fNumberOfWorldSectorsPerDimension;

	int iTotalNumberOfWorldSectors;
	int iNegativeTotalNumberOfWorldSectors;
	int iNumberOfWorldSectorsPerDimensionHalf;

	float fWorldSectorSize;
	float fWorldSectorSizeHalf;
	float fWorldSectorSizeInversed;
	float fWorldSectorSizeDoubledThenSquared;
	float fNumberOfWorldSectorsPerDimensionHalf;
	float f250inWorldSectors;

	// Repeat sectors
	int iNumberOfWorldRepeatSectorsPerDimension;
	int iTotalNumberOfWorldRepeatSectors;

	// LOD sectors
	int iNumberOfWorldLODsectorsPerDimension;
	int iNumberOfWorldLODsectorsPerDimensionMinusOne;
	int iNumberOfWorldLODsectorsPerDimensionHalf;
	int iTotalNumberOfWorldLODsectors;
	float fWorldLODsectorSize;
	float fWorldLODsectorSizeHalf;
	float fWorldLODsectorSizeInversed;
	float fWorldLODsectorSizeTimesSquareRootOfTwoThenSquared;
	float fNumberOfWorldLODsectorsPerDimensionHalf;
}

// Does the initialising work for patching the world sectors
bool MapLimits::PatchWorldSectors_DoInitialisingWork()
{
	if (!ValidateMapSizeOrShowMessage(ms_worldMapSize, "World"))
		return false;

	MAKE_VAR_GAME_VERSION();

	// Set variables
	#if TRUE
	{
		// coordinates
		iWorldMapMaxCoord = this->ms_worldMapSize / 2;
		fWorldMapMaxCoord = (float)ms_worldMapSize / 2;
		fWorldMapMinCoord = -fWorldMapMaxCoord;

		fWorldMapMaxCoordMinusOne = fWorldMapMaxCoord - 1;

		// world sectors
		iNumberOfWorldSectorsPerDimension = ms_worldMapSize / ms_worldSectorSize;
		iNumberOfWorldSectorsPerDimensionMinusOne = iNumberOfWorldSectorsPerDimension - 1;
		iNumberOfWorldSectorsPerDimensionMultipliedBy2 = iNumberOfWorldSectorsPerDimension * 2;
		iNumberOfWorldSectorsPerDimensionDividedBy8 = iNumberOfWorldSectorsPerDimension / 8;
		fNumberOfWorldSectorsPerDimension = (float)iNumberOfWorldSectorsPerDimension;
		iTotalNumberOfWorldSectors = iNumberOfWorldSectorsPerDimension * iNumberOfWorldSectorsPerDimension;
		iNegativeTotalNumberOfWorldSectors = -iTotalNumberOfWorldSectors;
		fWorldSectorSize = (float)ms_worldSectorSize;
		fWorldSectorSizeHalf = fWorldSectorSize / 2.0;
		fWorldSectorSizeInversed = (float)(1.0 / ms_worldSectorSize);
		fWorldSectorSizeDoubledThenSquared = (fWorldSectorSize * 2.0) * (fWorldSectorSize * 2.0);
		iNumberOfWorldSectorsPerDimensionHalf = iNumberOfWorldSectorsPerDimension / 2;
		fNumberOfWorldSectorsPerDimensionHalf = (float)iNumberOfWorldSectorsPerDimensionHalf;
		f250inWorldSectors = (float)(250 / this->ms_worldSectorSize);

		// world repeat sectors
		iNumberOfWorldRepeatSectorsPerDimension = 16;
		iTotalNumberOfWorldRepeatSectors = iNumberOfWorldRepeatSectorsPerDimension * iNumberOfWorldRepeatSectorsPerDimension;

		// world lod sectors
		iNumberOfWorldLODsectorsPerDimension = ms_worldMapSize / ms_worldLODsectorSize;
		iNumberOfWorldLODsectorsPerDimensionMinusOne = iNumberOfWorldLODsectorsPerDimension - 1;
		iNumberOfWorldLODsectorsPerDimensionHalf = iNumberOfWorldLODsectorsPerDimension / 2;

		iTotalNumberOfWorldLODsectors = iNumberOfWorldLODsectorsPerDimension * iNumberOfWorldLODsectorsPerDimension;
		fWorldLODsectorSize = (float)ms_worldLODsectorSize;
		fWorldLODsectorSizeHalf = fWorldLODsectorSize / 2.0;
		fWorldLODsectorSizeInversed = (float)(1.0 / ms_worldLODsectorSize);
		fWorldLODsectorSizeTimesSquareRootOfTwoThenSquared =
			(fWorldLODsectorSize * M_SQRT2) * (fWorldLODsectorSize * M_SQRT2);
		fNumberOfWorldLODsectorsPerDimensionHalf = (float)(iNumberOfWorldLODsectorsPerDimension / 2);

		// stru_1136170
		#if TRUE
		if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
		{
			using namespace Game_GTAIV;

			uint32_t* Class_1136170_MemberOffsetArray = CWorld__ms_class_1136170.gta_iv->MemberOffsetArray;

			Class_1136170_MemberOffsetArray[Offset_class_1136170__field_0] = 0;

			Class_1136170_MemberOffsetArray[Offset_class_1136170__field_4]
				= GetNextOffset(
					Class_1136170_MemberOffsetArray[Offset_class_1136170__field_0],
					sizeof(int32_t)
				);

			Class_1136170_MemberOffsetArray[Offset_class_1136170__field_8]
				= GetNextOffset(
					Class_1136170_MemberOffsetArray[Offset_class_1136170__field_4],
					sizeof(int32_t)
				);

			Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E108]
				= GetNextOffset(
					Class_1136170_MemberOffsetArray[Offset_class_1136170__field_8],
					iTotalNumberOfWorldSectors * sizeof(int32_t)
				);

			Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E2E8]
				= GetNextOffset(
					Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E108],
					iNumberOfWorldSectorsPerDimension * sizeof(int32_t)
				);

			Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4C8]
				= GetNextOffset(
					Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E2E8],
					iNumberOfWorldSectorsPerDimension * sizeof(int32_t)
				);

			Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4CC]
				= GetNextOffset(
					Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4C8],
					sizeof(int32_t)
				);

			Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4D0]
				= GetNextOffset(
					Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4CC],
					sizeof(int32_t)
				);

			Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4D4]
				= GetNextOffset(
					Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4D0],
					sizeof(int32_t)
				);

			Class_1136170_MemberOffsetArray[Offset_class_1136170__endOfStructure]
				= GetNextOffset(
					Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4D4],
					sizeof(int32_t)
				);

			// Dump offsets to log file
			#ifdef FALSE
			{
				CGenericLogStorage::SaveTextLn("Dumping Class_1136170 offsets.");

				for (eClass_1136170_offset offset = Offset_class_1136170__firstEnumMember; offset != Offset_class_1136170__enumCount; offset++)
				{
					CGenericLogStorage::SaveFormattedTextLn(
						"member %d, offset: 0x%X",
						offset,
						Class_1136170_MemberOffsetArray[offset]
					);
				}

				CGenericLogStorage::SaveWorkBuffer();
				// CLimitAdjusterForGame::TerminateProcess();
			}
			#endif
		}
		#endif
	}
	#endif

	// Print to log
	#if TRUE
	{
		CGenericLogStorage::SaveFormattedTextLn(
			"\nWorld map info info:\n"
			"World map size: %d x %d\n"
			"\nWorld sectors:\n"
			"CWorld::ms_aSectors\n"
			"type: buildings, dummies\n"
			"count: %d * %d = %d\n"
			"sector area: %d x %d\n\n"

			"CWorld::ms_aLodPtrLists\n"
			"type: lod\n"
			"count: %d * %d = %d\n"
			"sector area: %d x %d\n\n"

			"CWorld::ms_aRepeatSectors\n"
			"type: vehicles, peds, object\n"
			"count: %d * %d = %d\n\n"
			,
			ms_worldMapSize, ms_worldMapSize,
			iNumberOfWorldSectorsPerDimension,
			iNumberOfWorldSectorsPerDimension,
			iTotalNumberOfWorldSectors,
			ms_worldSectorSize,
			ms_worldSectorSize,

			iNumberOfWorldLODsectorsPerDimension,
			iNumberOfWorldLODsectorsPerDimension,
			iTotalNumberOfWorldLODsectors,
			ms_worldLODsectorSize,
			ms_worldLODsectorSize,

			iNumberOfWorldRepeatSectorsPerDimension,
			iNumberOfWorldRepeatSectorsPerDimension,
			iTotalNumberOfWorldRepeatSectors
		);
	}
	#endif

	return true;
}

#ifdef IS_PLATFORM_WIN_X86
// GTA San Andreas
namespace Game_GTASA
{
	void __cdecl LimitCameraCoordinates(CVector& pos)
	{
		const float minAllowedCoord = 250.0;
		const float maxAllowedCoord = fWorldMapMaxCoord - minAllowedCoord;

		// X
		if (pos.x > maxAllowedCoord)
		{
			do
				pos.x -= 1.0;
			while (pos.x > maxAllowedCoord);
		}

		if (pos.x < minAllowedCoord)
		{
			do
				pos.x += 1.0;
			while (pos.x < minAllowedCoord);
		}

		// Y
		if (pos.y > maxAllowedCoord)
		{
			do
				pos.y -= 1.0;
			while (pos.y > maxAllowedCoord);
		}

		if (pos.y < minAllowedCoord)
		{
			do
				pos.y += 1.0;
			while (pos.y < minAllowedCoord);
		}
	}

	NAKED void patch_CCam__Process_Editor_50F720()
	{
		__asm
		{
			push edi;
			call LimitCameraCoordinates;
			add esp, 4;


			mov eax, 0x50F847;
			jmp eax;
		}
	}

	NAKED void patch_CWorld__GetIsLineOfSightClear_56B025()
	{
		__asm
		{
			mov ecx, ebx;
			sub ecx, iNumberOfWorldSectorsPerDimensionHalf;

			mov[esp + 74h + 4], ecx;

			push 0x56B02C;
			retn;
		}
	}

	NAKED void patch_CWorld__GetIsLineOfSightClear_56B1C0()
	{
		__asm
		{
			mov     edx, [esp + 6Ch + 8];
			sub edx, iNumberOfWorldSectorsPerDimensionHalf;

			push 0x56B1C7;
			retn
		}
	}

	NAKED void patch_CWorld__GetIsLineOfSightClear_56AA0F()
	{
		__asm
		{
			lea edx, [ebx + 1];
			sub edx, iNumberOfWorldSectorsPerDimensionHalf;

			mov[esp + 74h + 4], edx;
			push 0x56AA16;
			retn;
		}
	}

	NAKED void patch_CWorld__GetIsLineOfSightClear_56ABA0()
	{
		__asm
		{
			mov     eax, [esp + 6Ch + 8];
			inc eax;
			sub eax, iNumberOfWorldSectorsPerDimensionHalf;

			push 0x56ABA7;
			retn;
		}
	}

	NAKED void patch_CWorld__ProcessLineOfSight_56C714()
	{
		__asm
		{
			sub ebp, iNumberOfWorldSectorsPerDimensionHalf;
			mov[esp + 78h - 0x44], ebp;

			push 0x56C71B;
			retn;
		}
	}

	NAKED void patch_CWorld__ProcessLineOfSight_56C924()
	{
		__asm
		{
			sub ecx, iNumberOfWorldSectorsPerDimensionHalf;
			mov[esp + 70h - 0x44], ecx;

			push 0x56C92B;
			retn;
		}
	}

	NAKED void patch_CWorld__ProcessLineOfSight_56C020()
	{
		__asm
		{
			inc ebp;
			sub ebp, iNumberOfWorldSectorsPerDimensionHalf;
			mov[esp + 78h - 0x48], ebp;

			push 0x56C027;
			retn;
		}
	}

	NAKED void patch_CWorld__ProcessLineOfSight_56C218()
	{
		__asm
		{
			inc ecx;
			sub ecx, iNumberOfWorldSectorsPerDimensionHalf;
			mov[esp + 70h - 0x48], ecx;

			push 0x56C21F;
			retn;
		}
	}

	NAKED void patch_CRenderer__ScanSectorList_554846()
	{
		__asm
		{
			mov     esi, [esp + 18h + 4];
			mov eax, esi;
			sub eax, iNumberOfWorldSectorsPerDimensionHalf;

			push 0x55484D;
			retn;
		}
	}

	NAKED void patch_CRenderer__ScanSectorList_554856()
	{
		__asm
		{
			mov     edi, [esp + 1Ch + 8];
			mov ecx, edi;
			sub ecx, iNumberOfWorldSectorsPerDimensionHalf;

			push 0x55485D;
			retn;
		}
	}

	NAKED void original_CCoronas__RegisterCorona()
	{
		__asm
		{
			sub     esp, 1Ch;
			push ebp;
			push esi;

			push 0x6FC185;
			retn;
		}
	}
}

// Patches world sectors
void MapLimits::PatchWorldSectors_GTA_SA_PC_1_0_HOODLUM()
{
	using namespace Game_GTASA;

	// Debugging the problem of the sun going through the building
	#if FALSE
	{
		CPatch::EnterNewLevelAndDisableDebugState();

		// CPatch::PutCallFunction(0x6FC6B1, &original_CCoronas__RegisterCorona);

		CPatch::NOPinstructions(0x6FC6B1, 5);

		CPatch::PutCallFunction(0x6FC73D, &original_CCoronas__RegisterCorona);
		CPatch::PatchUINT8(0x6FC180, 0xC3);

		CPatch::LeaveThisLevel();
	}
	#endif

	// Patch coordinates
	#if TRUE
	{
		CPatch::EnterNewLevelAndDisableDebugState();

		// float 0x859A90, -3000.0
		#if TRUE
		{
			CPatch::PatchPointer(0x47F0E6 + 2, &fWorldMapMinCoord);	// fsub    ds:flt_859A90
			CPatch::PatchPointer(0x47F17B + 2, &fWorldMapMinCoord);	// fsub    ds:flt_859A90

			CPatch::PatchPointer(0x5347EB + 2, &fWorldMapMinCoord);	// fcomp   ds:flt_859A90
			CPatch::PatchPointer(0x534832 + 2, &fWorldMapMinCoord);	// fcomp   ds:flt_859A90
			CPatch::PatchPointer(0x534AFD + 2, &fWorldMapMinCoord);	// fcomp   ds:flt_859A90
			CPatch::PatchPointer(0x534B2A + 2, &fWorldMapMinCoord);	// fld     ds:flt_859A90
			CPatch::PatchPointer(0x534B53 + 2, &fWorldMapMinCoord);	// fcomp   ds:flt_859A90
			CPatch::PatchPointer(0x5615DF + 2, &fWorldMapMinCoord);	// fcomp   ds:flt_859A90
			CPatch::PatchPointer(0x5615EE + 2, &fWorldMapMinCoord);	// fld     ds:flt_859A90
			CPatch::PatchPointer(0x561627 + 2, &fWorldMapMinCoord);	// fcomp   ds:flt_859A90
			CPatch::PatchPointer(0x6C660F + 2, &fWorldMapMinCoord);	// fcomp   ds:flt_859A90
			CPatch::PatchPointer(0x6C6631 + 2, &fWorldMapMinCoord);	// fcomp   ds:flt_859A90																				
			CPatch::PatchPointer(0x7361B0 + 2, &fWorldMapMinCoord);	// fcomp   ds:flt_859A90
			CPatch::PatchPointer(0x7361DE + 2, &fWorldMapMinCoord);	// fcomp   ds:flt_859A90			
		}
		#endif

		// float 0x859A94, 3000.0
		#if TRUE
		{
			CPatch::PatchPointer(0x534819 + 2, &fWorldMapMaxCoord);	// fcomp   ds:flt_859A94
			CPatch::PatchPointer(0x53484B + 2, &fWorldMapMaxCoord);	// fcomp   ds:flt_859A94
			CPatch::PatchPointer(0x534B3A + 2, &fWorldMapMaxCoord);	// fcomp   ds:flt_859A94
			CPatch::PatchPointer(0x534B6C + 2, &fWorldMapMaxCoord);	// fcomp   ds:flt_859A94
			CPatch::PatchPointer(0x561604 + 2, &fWorldMapMaxCoord);	// fcomp   ds:flt_859A94
			CPatch::PatchPointer(0x56161A + 2, &fWorldMapMaxCoord);	// fsub    ds:flt_859A94
			CPatch::PatchPointer(0x56163B + 2, &fWorldMapMaxCoord);	// fadd    ds:flt_859A94
			CPatch::PatchPointer(0x561645 + 2, &fWorldMapMaxCoord);	// fcomp   ds:flt_859A94
			CPatch::PatchPointer(0x561659 + 2, &fWorldMapMaxCoord);	// fsub    ds:flt_859A94


			CPatch::PatchPointer(0x6C6620 + 2, &fWorldMapMaxCoord);	// fcomp   ds:flt_859A94
			CPatch::PatchPointer(0x6C6642 + 2, &fWorldMapMaxCoord);	// fcomp   ds:flt_859A94



			CPatch::PatchPointer(0x70E416 + 2, &fWorldMapMaxCoord);	// fmul    ds:flt_859A94
			// CPatch::PatchPointer(0x70E43C + 2, &fWorldMapMaxCoord);	// fmul    ds:flt_859A94

			CPatch::PatchPointer(0x7361C9 + 2, &fWorldMapMaxCoord);	// fcomp   ds:flt_859A94
			CPatch::PatchPointer(0x7361F3 + 2, &fWorldMapMaxCoord);	// fcomp   ds:flt_859A94
		}
		#endif

		// float -3000.0
		#if TRUE
		{
			CPatch::PatchFloat(0x405EE2 + 4, fWorldMapMinCoord);	// mov     [esp+24h+var_1C], -3000.0	; sub_5631E0
			CPatch::PatchFloat(0x405EEA + 4, fWorldMapMinCoord);	// mov     [esp+24h+var_10], -3000.0	; sub_5631E0
			CPatch::PatchFloat(0x41140F + 4, fWorldMapMinCoord);	// mov     [esp+20h+var_1C], -3000.0	; sub_416260
			CPatch::PatchFloat(0x411417 + 4, fWorldMapMinCoord);	// mov     [esp+20h+var_10], -3000.0	; sub_416260
			CPatch::PatchFloat(0x53480D + 4, fWorldMapMinCoord);	// mov     [esp+28h+var_10], -3000.0	; _ZN7CEntity3AddERK5CRect
			CPatch::PatchFloat(0x53483F + 4, fWorldMapMinCoord);	// mov     [esp+28h+var_4], -3000.0	; _ZN7CEntity3AddERK5CRect
			CPatch::PatchFloat(0x534B60 + 4, fWorldMapMinCoord);	// mov     [esp+40h+var_14], -3000.0	; sub_534AE0
			CPatch::PatchFloat(0x156A70B + 4, fWorldMapMinCoord);	// mov     [esp+28h+var_1C], -3000.0	; sub_156A6F0
			CPatch::PatchFloat(0x156A713 + 4, fWorldMapMinCoord);	// mov     [esp+28h+var_10], -3000.0	; sub_156A6F0
		}
		#endif

		// float 3000.0
		#if TRUE
		{
			CPatch::PatchFloat(0x405EF2 + 4, fWorldMapMaxCoord);	// mov     [esp+24h+var_14], 3000.0	; sub_5631E0
			CPatch::PatchFloat(0x405EFA + 4, fWorldMapMaxCoord);	// mov     [esp+24h+var_18], 3000.0	; sub_5631E0
			CPatch::PatchFloat(0x41141F + 4, fWorldMapMaxCoord);	// mov     [esp+20h+var_14], 3000.0	; sub_416260
			CPatch::PatchFloat(0x411427 + 4, fWorldMapMaxCoord);	// mov     [esp+20h+var_18], 3000.0	; sub_416260
			CPatch::PatchFloat(0x156A71B + 4, fWorldMapMaxCoord);	// mov     [esp+28h+var_14], 3000.0	; sub_156A6F0
			CPatch::PatchFloat(0x156A723 + 4, fWorldMapMaxCoord);	// mov     [esp+28h+var_18], 3000.0	; sub_156A6F0
		}
		#endif

		// float, 2999.0
		#if TRUE
		{
			CPatch::PatchFloat(0x534826 + 4, fWorldMapMaxCoordMinusOne);	// mov     [esp+28h+var_8], 2999.0
			CPatch::PatchFloat(0x534858 + 4, fWorldMapMaxCoordMinusOne);	// mov     [esp+28h+var_C], 2999.0
			CPatch::PatchFloat(0x534B47 + 4, fWorldMapMaxCoordMinusOne);	// mov     [esp+40h+var_18], 2999.0
			CPatch::PatchFloat(0x534B79 + 4, fWorldMapMaxCoordMinusOne);	// mov     [esp+40h+var_1C], 2999.0
		}
		#endif

		CPatch::LeaveThisLevel();
	}
	#endif

	// CWorld::ms_aSectors
	#if TRUE
	{
		// Patch pointers to CWorld::ms_aSectors
		#if TRUE
		{
			CPatch::PatchPointer(0x408258 + 1, CWorld__ms_aSectors.gta_sa);	// mov     ecx, offset _ZN6CWorld11ms_aSectorsE; CWorld::ms_aSectors
			CPatch::PatchPointer(0x4086FF + 3, CWorld__ms_aSectors.gta_sa);	// mov     esi, ds:_ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x408706 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ebx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x40914E + 3, CWorld__ms_aSectors.gta_sa);	// mov     esi, ds:_ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x4091C5 + 3, &CWorld__ms_aSectors.gta_sa->dummyList);	// mov     esi, ds:_ZN6CWorld11ms_aSectorsE.dummyList[eax*8]
			CPatch::PatchPointer(0x4092E9 + 3, CWorld__ms_aSectors.gta_sa);	// mov     esi, ds:_ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x409367 + 3, &CWorld__ms_aSectors.gta_sa->dummyList);	// mov     esi, ds:_ZN6CWorld11ms_aSectorsE.dummyList[eax*8]
			CPatch::PatchPointer(0x40D68C + 3, CWorld__ms_aSectors.gta_sa);	// lea     edi, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x40D98C + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x40D9C5 + 3, &CWorld__ms_aSectors.gta_sa->dummyList);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.dummyList[eax*8]
			CPatch::PatchPointer(0x40DB0E + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x40DB47 + 3, &CWorld__ms_aSectors.gta_sa->dummyList);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.dummyList[eax*8]
			CPatch::PatchPointer(0x40DC29 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x40DC61 + 3, &CWorld__ms_aSectors.gta_sa->dummyList);	// lea     edx, _ZN6CWorld11ms_aSectorsE.dummyList[eax*8]
			CPatch::PatchPointer(0x40DDCE + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x40DE07 + 3, &CWorld__ms_aSectors.gta_sa->dummyList);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.dummyList[eax*8]
			CPatch::PatchPointer(0x40DF5E + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x40DF97 + 3, &CWorld__ms_aSectors.gta_sa->dummyList);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.dummyList[eax*8]
			CPatch::PatchPointer(0x40E061 + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x40E09A + 3, &CWorld__ms_aSectors.gta_sa->dummyList);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.dummyList[eax*8]
			CPatch::PatchPointer(0x41A85A + 3, CWorld__ms_aSectors.gta_sa);	// mov     ebp, ds:_ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x41A861 + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x534A09 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x534A98 + 3, &CWorld__ms_aSectors.gta_sa->dummyList);	// lea     ebx, _ZN6CWorld11ms_aSectorsE.dummyList[eax*8]
			CPatch::PatchPointer(0x534D6B + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x534DFA + 3, &CWorld__ms_aSectors.gta_sa->dummyList);	// lea     ebx, _ZN6CWorld11ms_aSectorsE.dummyList[eax*8]
			CPatch::PatchPointer(0x546738 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[ecx*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x54BB23 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[ecx*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x563844 + 1, CWorld__ms_aSectors.gta_sa);	// mov     esi, offset _ZN6CWorld11ms_aSectorsE; CWorld::ms_aSectors
			CPatch::PatchPointer(0x564171 + 1, CWorld__ms_aSectors.gta_sa);	// mov     esi, offset _ZN6CWorld11ms_aSectorsE; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56421F + 1, CWorld__ms_aSectors.gta_sa);	// mov     esi, offset _ZN6CWorld11ms_aSectorsE; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56479D + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x564B59 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x564DA9 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x5664D7 + 3, CWorld__ms_aSectors.gta_sa);	// lea     edi, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x566586 + 3, CWorld__ms_aSectors.gta_sa);	// lea     esi, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x5675FA + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[ebx*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x567735 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[ebx*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x568CB9 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x568EFB + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x569127 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x569537 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x569F57 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56A685 + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[ebp*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56A766 + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[ebp*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56A85F + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[ebx*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56A940 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[ebx*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56ACA3 + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[ebp*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56AD91 + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[ebp*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56AE95 + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[ebp*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56AF74 + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[ebp*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56B2C3 + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[ebp*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56B3B1 + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[ebp*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56B4B5 + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[ebp*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56B594 + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[ebp*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56BC53 + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56BD46 + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56BE56 + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[ebp*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56BF4F + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[ebp*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56C341 + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56C445 + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56C569 + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56C664 + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56CA4A + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56CB51 + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56CC79 + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x56CD84 + 3, CWorld__ms_aSectors.gta_sa);	// lea     edx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x5DC7A7 + 3, CWorld__ms_aSectors.gta_sa);	// mov     ebp, ds:_ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x6063C7 + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x67FF5D + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x699CF5 + 3, CWorld__ms_aSectors.gta_sa);	// mov     edi, ds:_ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x699CFE + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x6E31AA + 3, CWorld__ms_aSectors.gta_sa);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.buildingList[ecx*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x70ACB2 + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x70B9BA + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x711B2F + 3, CWorld__ms_aSectors.gta_sa);	// mov     edi, ds:_ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors
			CPatch::PatchPointer(0x71CDB0 + 3, &CWorld__ms_aSectors.gta_sa->dummyList);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.dummyList[esi*8]
			CPatch::PatchPointer(0x84E9C1 + 1, CWorld__ms_aSectors.gta_sa);	// push    offset _ZN6CWorld11ms_aSectorsE; CWorld::ms_aSectors
			CPatch::PatchPointer(0x85652C + 1, CWorld__ms_aSectors.gta_sa);	// push    offset _ZN6CWorld11ms_aSectorsE; CWorld::ms_aSectors
			CPatch::PatchPointer(0x1566855 + 3, CWorld__ms_aSectors.gta_sa);	// lea     eax, _ZN6CWorld11ms_aSectorsE.buildingList[eax*8]; CWorld::ms_aSectors

			CPatch::PatchPointer(0x5634A4 + 2, &CWorld__ms_aSectors.gta_sa[iTotalNumberOfWorldSectors]);	// cmp     ecx, offset _ZN6CWorld17ms_aRepeatSectorsE; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x5634A4 + 2, &CWorld__ms_aSectors.gta_sa[iTotalNumberOfWorldSectors]);	// cmp     ecx, offset _ZN6CWorld17ms_aRepeatSectorsE; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x5638DD + 2, &CWorld__ms_aSectors.gta_sa[iTotalNumberOfWorldSectors]);	// cmp     esi, offset _ZN6CWorld17ms_aRepeatSectorsE; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x5638DD + 2, &CWorld__ms_aSectors.gta_sa[iTotalNumberOfWorldSectors]);	// cmp     esi, offset _ZN6CWorld17ms_aRepeatSectorsE; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56420D + 2, &CWorld__ms_aSectors.gta_sa[iTotalNumberOfWorldSectors]);	// cmp     esi, offset _ZN6CWorld17ms_aRepeatSectorsE; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56420D + 2, &CWorld__ms_aSectors.gta_sa[iTotalNumberOfWorldSectors]);	// cmp     esi, offset _ZN6CWorld17ms_aRepeatSectorsE; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x564281 + 2, &CWorld__ms_aSectors.gta_sa[iTotalNumberOfWorldSectors]);	// cmp     esi, offset _ZN6CWorld17ms_aRepeatSectorsE; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x564281 + 2, &CWorld__ms_aSectors.gta_sa[iTotalNumberOfWorldSectors]);	// cmp     esi, offset _ZN6CWorld17ms_aRepeatSectorsE; CWorld::ms_aRepeatSectors
		}
		#endif

		// Patch count of CWorld::ms_aSectors (14440)
		#if TRUE
		{
			CPatch::PatchUINT32(0x84E9BA + 1, iTotalNumberOfWorldSectors);	// push    14400
			CPatch::PatchUINT32(0x856525 + 1, iTotalNumberOfWorldSectors);	// push    14400
		}
		#endif

		// Patch pointers to size of sector (50.0), flt_858B40
		// related values nearby: integer -59, -60
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();
		{
			CPatch::PatchPointer(0x55485D + 2, &fWorldSectorSize);	// fmul    ds:flt_858B40	; sub_554840
			CPatch::PatchPointer(0x554879 + 2, &fWorldSectorSize);	// fmul    ds:flt_858B40	; sub_554840
			CPatch::PatchPointer(0x56AA1E + 2, &fWorldSectorSize);	// fmul    ds:flt_858B40	; sub_56A490
			CPatch::PatchPointer(0x56ABB2 + 2, &fWorldSectorSize);	// fmul    ds:flt_858B40	; sub_56A490
			CPatch::PatchPointer(0x56B034 + 2, &fWorldSectorSize);	// fmul    ds:flt_858B40	; sub_56A490
			CPatch::PatchPointer(0x56B1D2 + 2, &fWorldSectorSize);	// fmul    ds:flt_858B40	; sub_56A490
			CPatch::PatchPointer(0x56C02F + 2, &fWorldSectorSize);	// fmul    ds:flt_858B40	; sub_56BA00
			CPatch::PatchPointer(0x56C226 + 2, &fWorldSectorSize);	// fmul    ds:flt_858B40	; sub_56BA00
			CPatch::PatchPointer(0x56C723 + 2, &fWorldSectorSize);	// fmul    ds:flt_858B40	; sub_56BA00
			CPatch::PatchPointer(0x56C932 + 2, &fWorldSectorSize);	// fmul    ds:flt_858B40	; sub_56BA00
		}
		CPatch::LeaveThisLevel();
		#endif

		// Patch pointers to half a size of sector per dimension (25.0)
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();
		{
			CPatch::PatchPointer(0x554869 + 2, &fWorldSectorSizeHalf);	// fadd    ds:flt_858FE8	; _ZN9CRenderer14ScanSectorListEii
			CPatch::PatchPointer(0x55487F + 2, &fWorldSectorSizeHalf);	// fadd    ds:flt_858FE8	; _ZN9CRenderer14ScanSectorListEii
		}
		CPatch::LeaveThisLevel();
		#endif

		// Patch pointers to size of sector per dimension doubled, then squared (10000.0)
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();
		{
			CPatch::PatchPointer(0x554895 + 2, &fWorldSectorSizeDoubledThenSquared);	// fcomp   ds:flt_859AA4	; _ZN9CRenderer14ScanSectorListEii
		}
		CPatch::LeaveThisLevel();
		#endif

		/* Pay attention to
			CWorld::GetIsLineOfSightClear
			CWorld::ProcessLineOfSight
		*/

		// Patch pointers to inversed size of sector (0.02), flt_858B38
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();

		{
			CPatch::PatchPointer(0x408536 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x40854F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x408569 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x4085BF + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x408607 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x408658 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x4090C6 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x4090EB + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x40921D + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x40923C + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x40D444 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x40D451 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x40D474 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x40D495 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x40D4E3 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x40D527 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x40D578 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x40D7EA + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x40D82B + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x41ACED + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x41AD3C + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x41AD80 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x41ADD1 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x42CECC + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x42CF1C + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x42CF60 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x42CFAC + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x432662 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x4326B2 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x4326FE + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x43274F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x434491 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x4344E1 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x434525 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x434576 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x4538BB + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x45390B + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x453953 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x45399F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x50F722 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x50F746 + 2, &fWorldSectorSizeInversed);	// fld     ds:flt_858B38
			CPatch::PatchPointer(0x50F765 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x50F786 + 2, &fWorldSectorSizeInversed);	// fld     ds:flt_858B38
			CPatch::PatchPointer(0x50F7A9 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x50F7D6 + 2, &fWorldSectorSizeInversed);	// fld     ds:flt_858B38
			CPatch::PatchPointer(0x50F7FD + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x50F826 + 2, &fWorldSectorSizeInversed);	// fld     ds:flt_858B38
			CPatch::PatchPointer(0x533068 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x533085 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x53309F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5330B9 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5330DD + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x533106 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x53491E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x53493E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x53495F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x53497E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x534C79 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x534C99 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x534CBC + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x534CDB + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x54259D + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5425BD + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5425E0 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5425FF + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x544A7A + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x544A9A + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x544ABD + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x544ADC + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x54D9E8 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x54DA08 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x54DA29 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x54DA48 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x54DC12 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x54DC2F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x54DC50 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x54DC6F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x54DD0A + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x54DD2C + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x54DD4D + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x54DD6C + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x554DED + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x554E13 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x554E27 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x554E3B + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x554E4F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x554E63 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x55544E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x55547B + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x555495 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5554AF + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5554C9 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5554E3 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5554FD + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x555517 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x555531 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x55554B + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x555C00 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x555C26 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x555C3D + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x555C54 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x555C6E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x555C88 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x564608 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x564656 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5646A4 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5646F0 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x564A34 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x564A5A + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x564A7B + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x564A9F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x564C84 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x564CAA + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x564CCB + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x564CEF + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x566AA5 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x566AC2 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x566AE5 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x566B04 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x567519 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x567538 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x567652 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56766E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x568B94 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x568BBA + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x568BDB + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x568BFF + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x568DE0 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x568DFC + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x568E22 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x568E3E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x568FF8 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56901A + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56903D + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56905C + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x569250 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56926C + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x569292 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5692AE + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x569404 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56942A + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56944B + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56946F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x569E2F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x569E5B + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x569E7E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x569EA3 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56A4BF + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56A4DE + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56A501 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56A51D + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56A99B + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56A9B6 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56A9D4 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56A9F4 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56AA2D + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56ABC1 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56AFB1 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56AFCC + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56AFEA + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56B00A + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56B043 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56B1E1 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56B7A3 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56B7C9 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56B7EA + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56B80E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56BA42 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56BA62 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56BA8A + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56BAA6 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56BFA3 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56BFBE + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56BFE3 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56C003 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56C03E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56C235 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56C697 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56C6B2 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56C6D7 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56C6F7 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56C732 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56C941 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56DC7E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56DCCE + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56DD12 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x56DD63 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x57067A + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x570697 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5706B8 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5706D7 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5DC5F1 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5DC647 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5DC68F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5DC6E0 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5FFACA + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5FFAF9 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5FFB2D + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5FFB57 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5FFB86 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5FFBB0 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5FFBE4 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x5FFC0F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x605BA8 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x605BD7 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x605C10 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x605C3F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x605C70 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x605CA4 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x605CD9 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x605D08 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x606194 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6061CE + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x606213 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x60624E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x60628A + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6062C9 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x60630A + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x606345 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6123D4 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x61240B + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x61244D + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x612485 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6124BE + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6124FA + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x612538 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x612570 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x67FE32 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x67FE59 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x67FE7E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x67FEA5 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x699B5A + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x699BA2 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x699BEE + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x699C3F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6B426F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6B42BF + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6B4303 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6B434F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6B464F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6B469B + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6B46DF + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6B4730 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6E2F9E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6E2FC9 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6E2FFE + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6E3029 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6E3056 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6E3082 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6E30B7 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6E30E3 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6E76FB + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6E7717 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6F6675 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6F66CB + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6F6713 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x6F6764 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x70AAE2 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x70AB32 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x70AB82 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x70ABD3 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x70B7B8 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x70B80E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x70B856 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x70B8A7 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x71197F + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x7119D5 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x711A1D + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x711A6E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x71CBBE + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x71CC0E + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x71CC52 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
			CPatch::PatchPointer(0x71CCA3 + 2, &fWorldSectorSizeInversed);	// fmul    ds:flt_858B38
		}

		CPatch::LeaveThisLevel();
		#endif

		// Patch pointers to half of number of world sectors per dimension (60.0)
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();
		{
			CPatch::PatchPointer(0x40853C + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x408555 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x40856F + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x4085C5 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x40860D + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x40865E + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x4090D7 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x4090F1 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x409226 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x409246 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x40D45E + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x40D47E + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x40D49D + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x40D4E9 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x40D52D + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x40D57E + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x40D7F3 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x40D831 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x41ACF6 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x41AD42 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x41AD86 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x41ADD7 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x42CED2 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x42CF22 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x42CF66 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x42CFB2 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x432668 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x4326B8 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x432704 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x432755 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x434497 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x4344E7 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x43452B + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x43457C + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x4538C1 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x453911 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x453959 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x4539A5 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x50F728 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x50F74E + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x50F76B + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x50F78E + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x50F7AF + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x50F7DE + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x50F803 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x50F82E + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x533071 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x53308B + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5330A5 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5330BF + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5330E3 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x53310C + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x534927 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x534948 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x534967 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x534988 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x534C82 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x534CA5 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x534CC4 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x534CE5 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5425A6 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5425C9 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5425E8 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x542609 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x544A83 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x544AA6 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x544AC5 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x544AE6 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x54D9F1 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x54DA12 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x54DA31 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x54DA50 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x54DC18 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x54DC39 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x54DC58 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x54DC77 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x54DD15 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x54DD36 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x54DD55 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x54DD74 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x554DFF + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x554E19 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x554E2D + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x554E41 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x554E55 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x554E69 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x555462 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x555481 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x55549B + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5554B5 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5554CF + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5554E9 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x555503 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x55551D + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x555537 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x555551 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x555C14 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x555C2C + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x555C43 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x555C5A + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x555C74 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x555C8E + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56460E + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56465F + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5646AA + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5646F6 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x564A3A + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x564A60 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x564A81 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x564AA5 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x564C8A + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x564CB0 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x564CD1 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x564CF5 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x566AAB + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x566ACE + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x566AED + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x566B0E + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x567522 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x567540 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x567658 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x567676 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x568B9A + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x568BC0 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x568BE1 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x568C05 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x568DE6 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x568E06 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x568E28 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x568E48 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569003 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569026 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569045 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569066 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569256 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569276 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569298 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5692B8 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56940A + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569430 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569451 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569475 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569E3A + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569E61 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569E84 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x569EA9 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56A4C8 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56A4E6 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56A507 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56A527 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56A9A1 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56A9BE + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56A9DE + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56A9FC + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56AA33 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56ABC7 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56AFB7 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56AFD4 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56AFF4 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56B012 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56B049 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56B1E7 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56B7A9 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56B7CF + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56B7F0 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56B814 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56BA4C + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56BA6A + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56BA90 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56BAB0 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56BFA9 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56BFCD + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56BFED + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56C00D + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56C044 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56C23B + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56C69D + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56C6C1 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56C6E1 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56C701 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56C738 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56C947 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56DC84 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56DCD4 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56DD18 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x56DD69 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x570680 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5706A1 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5706C0 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5706DF + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5DC5F7 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5DC64D + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5DC695 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5DC6E6 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5FFAD6 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5FFAFF + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5FFB33 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5FFB5D + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5FFB8C + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5FFBB6 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5FFBEA + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x5FFC15 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x605BAE + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x605BDD + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x605C16 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x605C45 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x605C76 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x605CAA + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x605CDF + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x605D0E + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x60619A + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6061D4 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x606219 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x606254 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x606290 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6062CF + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x606310 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x60634B + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6123DA + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x612411 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x612453 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x61248B + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6124C4 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x612500 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x61253E + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x612576 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x67FE38 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x67FE5F + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x67FE84 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x67FEAB + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x699B60 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x699BAC + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x699BF4 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x699C45 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6B4275 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6B42C5 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6B4309 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6B4355 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6B4655 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6B46A1 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6B46E5 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6B4736 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6E2FA4 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6E2FCF + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6E3004 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6E302F + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6E305C + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6E3088 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6E30BD + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6E30E9 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6E7701 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6E771F + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6F667B + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6F66D1 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6F6719 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x6F676A + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x70AAE8 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x70AB38 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x70AB88 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x70ABD9 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x70B7BE + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x70B814 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x70B85C + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x70B8AD + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x711985 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x7119DB + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x711A23 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x711A74 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x71CBC4 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x71CC14 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x71CC58 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
			CPatch::PatchPointer(0x71CCA9 + 2, &fNumberOfWorldSectorsPerDimensionHalf);	// fadd    ds:flt_858B34
		}
		CPatch::LeaveThisLevel();
		#endif

		// Patch values, which relate to number of sectors: -59, -60
		#if TRUE
		{
			// CWorld::GetIsLineOfSightClear
			CPatch::RedirectCode(0x56B025, &patch_CWorld__GetIsLineOfSightClear_56B025);
			CPatch::RedirectCode(0x56B1C0, &patch_CWorld__GetIsLineOfSightClear_56B1C0);
			CPatch::RedirectCode(0x56AA0F, &patch_CWorld__GetIsLineOfSightClear_56AA0F);
			CPatch::RedirectCode(0x56ABA0, &patch_CWorld__GetIsLineOfSightClear_56ABA0);

			// CWorld::ProcessLineOfSight
			CPatch::RedirectCode(0x56C714, &patch_CWorld__ProcessLineOfSight_56C714);
			CPatch::RedirectCode(0x56C924, &patch_CWorld__ProcessLineOfSight_56C924);
			CPatch::RedirectCode(0x56C020, &patch_CWorld__ProcessLineOfSight_56C020);
			CPatch::RedirectCode(0x56C218, &patch_CWorld__ProcessLineOfSight_56C218);

			// CRenderer::ScanSectorList
			CPatch::RedirectCode(0x554846, &patch_CRenderer__ScanSectorList_554846);
			CPatch::RedirectCode(0x554856, &patch_CRenderer__ScanSectorList_554856);
		}
		#endif

		// Patch values 119 & 120
		#if TRUE
		{
			// value 119
			#if TRUE
			{
				CPatch::PatchUINT32(0x40D89B + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+30h+var_14], 77h
				CPatch::PatchUINT32(0x40DCE8 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+30h+var_14], 77h
				CPatch::PatchUINT32(0x42CFEE + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+34h+var_20], 77h
				CPatch::PatchUINT32(0x4539E1 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     dword ptr [esp+10h], 77h
				CPatch::PatchUINT32(0x567588 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+3Ch+arg_0], 77h
				CPatch::PatchUINT32(0x5676C8 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+3Ch+arg_0], 77h
				CPatch::PatchUINT32(0x56A602 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+6Ch+var_4C], 77h
				CPatch::PatchUINT32(0x56A6E3 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+6Ch+var_4C], 77h
				CPatch::PatchUINT32(0x56A7E8 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+6Ch+var_4C], 77h
				CPatch::PatchUINT32(0x56A8C9 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+6Ch+var_4C], 77h
				CPatch::PatchUINT32(0x56AC20 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+6Ch+var_48], 77h
				CPatch::PatchUINT32(0x56AD10 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+6Ch+var_48], 77h
				CPatch::PatchUINT32(0x56AE12 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+6Ch+var_48], 77h
				CPatch::PatchUINT32(0x56AEF1 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+6Ch+var_48], 77h
				CPatch::PatchUINT32(0x56B240 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+6Ch+var_54], 77h
				CPatch::PatchUINT32(0x56B330 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+6Ch+var_5C], 77h
				CPatch::PatchUINT32(0x56B432 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+6Ch+var_48], 77h
				CPatch::PatchUINT32(0x56B511 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+6Ch+var_48], 77h
				CPatch::PatchUINT32(0x56BDC2 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+70h+var_54], 77h
				CPatch::PatchUINT32(0x56BEBD + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+70h+var_54], 77h
				CPatch::PatchUINT32(0x5FFBD2 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+74h+var_58], 77h
				CPatch::PatchUINT32(0x5FFC31 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+74h+var_54], 77h
				CPatch::PatchUINT32(0x6B4391 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+28h+var_10], 77h
				CPatch::PatchUINT32(0x70ABC4 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+100h+var_C4], 77h
				CPatch::PatchUINT32(0x70AC15 + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+100h+var_CC], 77h
				CPatch::PatchUINT32(0x711A5F + 4, iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+2Ch+arg_4], 77h
			}
			#endif

			// value 120
			#if TRUE
			{
				CPatch::PatchUINT32(0x564732 + 4, iNumberOfWorldSectorsPerDimension);	// mov     [esp+14h+arg_0], 78h
				CPatch::PatchUINT32(0x6E30A4 + 4, iNumberOfWorldSectorsPerDimension);	// mov     dword ptr [esp+48h+m], 78h
				CPatch::PatchUINT32(0x6E3105 + 4, iNumberOfWorldSectorsPerDimension);	// mov     [esp+48h+var_38], 78h
			}
			#endif
		}
		#endif		

		// Section for debugging
		#if FALSE
		{
			CPatch::EnterNewLevelAndDisableDebugState();
			CPatch::PatchFloat(0x858B38, fWorldSectorSizeInversed);
			CPatch::PatchFloat(0x858B34, fNumberOfWorldSectorsPerDimensionHalf);
			CPatch::LeaveThisLevel();
		}
		#endif
	}
	#endif

	// CWorld::ms_aRepeatSectors
	#if TRUE
	{
		// Patch pointers to CWorld::ms_aRepeatSectors
		#if TRUE
		{
			CPatch::PatchPointer(0x408719 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x409183 + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// mov     esi, ds:_ZN6CWorld17ms_aRepeatSectorsE.objectList[eax*4]
			CPatch::PatchPointer(0x409320 + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// mov     esi, ds:_ZN6CWorld17ms_aRepeatSectorsE.objectList[eax*4]
			CPatch::PatchPointer(0x40D6AA + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ebx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ebx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x40D9F0 + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.objectList[eax*4]
			CPatch::PatchPointer(0x40DB72 + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.objectList[eax*4]
			CPatch::PatchPointer(0x40DC8C + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// lea     eax, _ZN6CWorld17ms_aRepeatSectorsE.objectList[edx*4]
			CPatch::PatchPointer(0x40DE32 + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.objectList[eax*4]
			CPatch::PatchPointer(0x40DFC2 + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.objectList[eax*4]
			CPatch::PatchPointer(0x40E0C1 + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.objectList[eax*4]
			CPatch::PatchPointer(0x41534E + 3, &CWorld__ms_aRepeatSectors.gta_sa->pedList);	// lea     eax, _ZN6CWorld17ms_aRepeatSectorsE.pedList[eax*4]
			CPatch::PatchPointer(0x41A9AA + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     eax, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x41AB3A + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// lea     eax, _ZN6CWorld17ms_aRepeatSectorsE.objectList[eax*4]
			CPatch::PatchPointer(0x42D076 + 3, &CWorld__ms_aRepeatSectors.gta_sa->pedList);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.pedList[ecx*4]
			CPatch::PatchPointer(0x432867 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     esi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[esi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x434641 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x453A29 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x534A2C + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ebx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ebx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x534A47 + 3, &CWorld__ms_aRepeatSectors.gta_sa->pedList);	// lea     ebx, _ZN6CWorld17ms_aRepeatSectorsE.pedList[ebx*4]
			CPatch::PatchPointer(0x534A62 + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// lea     ebx, _ZN6CWorld17ms_aRepeatSectorsE.objectList[ebx*4]
			CPatch::PatchPointer(0x534D8E + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ebx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ebx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x534DA9 + 3, &CWorld__ms_aRepeatSectors.gta_sa->pedList);	// lea     ebx, _ZN6CWorld17ms_aRepeatSectorsE.pedList[ebx*4]
			CPatch::PatchPointer(0x534DC4 + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// lea     ebx, _ZN6CWorld17ms_aRepeatSectorsE.objectList[ebx*4]
			CPatch::PatchPointer(0x542664 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ebx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ebx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x544B55 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ebx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ebx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x54673F + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ebp, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ebp*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x54BB3C + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ecx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x55355F + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     esi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[esi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x555943 + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.objectList[eax*4]
			CPatch::PatchPointer(0x5634AC + 1, CWorld__ms_aRepeatSectors.gta_sa);	// mov     ecx, offset _ZN6CWorld17ms_aRepeatSectorsE; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x5634F4 + 2, &CWorld__ms_aRepeatSectors.gta_sa[iTotalNumberOfWorldRepeatSectors]);	// cmp     ecx, offset _ZN6CWorld15ms_aLodPtrListsE; CWorld::ms_aLodPtrLists
			CPatch::PatchPointer(0x5638ED + 1, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// mov     ebp, offset _ZN6CWorld17ms_aRepeatSectorsE.objectList
			CPatch::PatchPointer(0x563935 + 2, &CWorld__ms_aRepeatSectors.gta_sa[iTotalNumberOfWorldRepeatSectors].objectList);	// cmp     ebp, (offset _ZN6CWorld15ms_aLodPtrListsE+8)
			CPatch::PatchPointer(0x5640A4 + 1, CWorld__ms_aRepeatSectors.gta_sa);	// mov     ebp, offset _ZN6CWorld17ms_aRepeatSectorsE; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x564165 + 2, &CWorld__ms_aRepeatSectors.gta_sa[iTotalNumberOfWorldRepeatSectors]);	// cmp     ebp, offset _ZN6CWorld15ms_aLodPtrListsE; CWorld::ms_aLodPtrLists
			CPatch::PatchPointer(0x56428B + 1, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// mov     edi, offset _ZN6CWorld17ms_aRepeatSectorsE.objectList
			CPatch::PatchPointer(0x56431C + 2, &CWorld__ms_aRepeatSectors.gta_sa[iTotalNumberOfWorldRepeatSectors].objectList);	// cmp     edi, (offset _ZN6CWorld15ms_aLodPtrListsE+8)
			CPatch::PatchPointer(0x564386 + 1, CWorld__ms_aRepeatSectors.gta_sa);	// mov     ebp, offset _ZN6CWorld17ms_aRepeatSectorsE; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x564405 + 2, &CWorld__ms_aRepeatSectors.gta_sa[iTotalNumberOfWorldRepeatSectors]);	// cmp     ebp, offset _ZN6CWorld15ms_aLodPtrListsE; CWorld::ms_aLodPtrLists
			CPatch::PatchPointer(0x564B74 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     esi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[esi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x564DC4 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     esi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[esi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x566BAA + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x5675F0 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56772B + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     eax, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x568CD4 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     esi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[esi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x568F16 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     esi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[esi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x569142 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     esi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[esi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x569344 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     esi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[esi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x569552 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     esi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[esi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x569F72 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56A5A5 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     eax, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56A67B + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ecx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56A75C + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ecx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56A855 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56A936 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     eax, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56AAB8 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ecx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56AB58 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ecx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56AC99 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ecx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56AD85 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56AE8B + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ecx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56AF6A + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ecx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56B0D8 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56B178 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56B2B9 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ecx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56B3A5 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56B4AB + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ecx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56B58A + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ecx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56B884 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     esi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[esi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56BB5E + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56BC40 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56BD33 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56BE4C + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     eax, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56BF43 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ecx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56C0F5 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     eax, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56C1C5 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56C32E + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56C432 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56C556 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56C651 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56C7F8 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     eax, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56C8C8 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56CA37 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56CB3E + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56CC66 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56CD71 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x56DDFC + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// mov     esi, ds:_ZN6CWorld17ms_aRepeatSectorsE.objectList[eax*4]
			CPatch::PatchPointer(0x5FFCA2 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x605D8A + 3, &CWorld__ms_aRepeatSectors.gta_sa->pedList);	// mov     esi, ds:_ZN6CWorld17ms_aRepeatSectorsE.pedList[edi*4]
			CPatch::PatchPointer(0x605D93 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x6063E1 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     eax, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x61260A + 3, CWorld__ms_aRepeatSectors.gta_sa);	// mov     ebp, ds:_ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x612613 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     eax, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x67FF96 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[edi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x6B43DA + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x6B47C0 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     edx, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[ecx*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x6E31B9 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     esi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[esi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x6F67FA + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     esi, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[esi*4]; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x711C4F + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// mov     edi, ds:_ZN6CWorld17ms_aRepeatSectorsE.objectList[edx*4]
			CPatch::PatchPointer(0x71CD85 + 3, &CWorld__ms_aRepeatSectors.gta_sa->objectList);	// lea     ecx, _ZN6CWorld17ms_aRepeatSectorsE.objectList[eax*4]
			CPatch::PatchPointer(0x84E9F1 + 1, CWorld__ms_aRepeatSectors.gta_sa);	// push    offset _ZN6CWorld17ms_aRepeatSectorsE; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x85654C + 1, CWorld__ms_aRepeatSectors.gta_sa);	// push    offset _ZN6CWorld17ms_aRepeatSectorsE; CWorld::ms_aRepeatSectors
			CPatch::PatchPointer(0x156C6C6 + 3, CWorld__ms_aRepeatSectors.gta_sa);	// lea     eax, _ZN6CWorld17ms_aRepeatSectorsE.vehicleList[eax*4]; CWorld::ms_aRepeatSectors
		}
		#endif

		// Patch count of CWorld::ms_aRepeatSectors (256)
		#if TRUE
		{
			CPatch::PatchUINT32(0x84E9EA + 1, iTotalNumberOfWorldRepeatSectors);	// push    256
			CPatch::PatchUINT32(0x856545 + 1, iTotalNumberOfWorldRepeatSectors);	// push    256
		}
		#endif
	}
	#endif		

	// CWorld::ms_aLodPtrLists
	#if TRUE
	{
		// Patch pointers to CWorld::aLodPtrLists
		#if TRUE
		{
			CPatch::PatchPointer(0x4072CD + 3, CWorld__ms_aLodPtrLists.gta_sa);	// lea     eax, _ZN6CWorld15ms_aLodPtrListsE[eax*4]; CWorld::ms_aLodPtrLists
			CPatch::PatchPointer(0x40C61A + 3, CWorld__ms_aLodPtrLists.gta_sa);	// lea     eax, _ZN6CWorld15ms_aLodPtrListsE[edx*4]; CWorld::ms_aLodPtrLists
			CPatch::PatchPointer(0x5348DA + 3, CWorld__ms_aLodPtrLists.gta_sa);	// lea     ebp, _ZN6CWorld15ms_aLodPtrListsE[ecx*4]; CWorld::ms_aLodPtrLists
			CPatch::PatchPointer(0x534BF8 + 3, CWorld__ms_aLodPtrLists.gta_sa);	// lea     edi, _ZN6CWorld15ms_aLodPtrListsE[ecx*4]; CWorld::ms_aLodPtrLists
			CPatch::PatchPointer(0x554B54 + 3, CWorld__ms_aLodPtrLists.gta_sa);	// lea     edx, _ZN6CWorld15ms_aLodPtrListsE[edx*4]; CWorld::ms_aLodPtrLists
			CPatch::PatchPointer(0x56405A + 1, CWorld__ms_aLodPtrLists.gta_sa);	// mov     ebp, offset _ZN6CWorld15ms_aLodPtrListsE; CWorld::ms_aLodPtrLists
			CPatch::PatchPointer(0x56409C + 2, &CWorld__ms_aLodPtrLists.gta_sa[iTotalNumberOfWorldLODsectors]);	// cmp     ebp, offset _ZN6CWorld23ms_listMovingEntityPtrsE; CWorld::ms_listMovingEntityPtrs
			CPatch::PatchPointer(0x564F87 + 3, CWorld__ms_aLodPtrLists.gta_sa);	// lea     edx, _ZN6CWorld15ms_aLodPtrListsE[ecx*4]; CWorld::ms_aLodPtrLists
			CPatch::PatchPointer(0x84EA21 + 1, CWorld__ms_aLodPtrLists.gta_sa);	// push    offset _ZN6CWorld15ms_aLodPtrListsE; CWorld::ms_aLodPtrLists
			CPatch::PatchPointer(0x8564CC + 1, CWorld__ms_aLodPtrLists.gta_sa);	// push    offset _ZN6CWorld15ms_aLodPtrListsE; CWorld::ms_aLodPtrLists
		}
		#endif

		// Patch count of CWorld::ms_aLodPtrLists (900)
		#if TRUE
		{
			CPatch::PatchUINT32(0x84EA1A + 1, iTotalNumberOfWorldLODsectors);	// push    256
			CPatch::PatchUINT32(0x8564C5 + 1, iTotalNumberOfWorldLODsectors);	// push    256
		}
		#endif

		// Patch pointers to size of LOD sector (200.0), flt_858B40
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();
		{
			CPatch::PatchPointer(0x554B5B + 2, &fWorldLODsectorSize);	// fmul    ds:flt_858A48   ; 200.0f	; _ZN9CRenderer19ScanBigBuildingListEii
			CPatch::PatchPointer(0x554B76 + 2, &fWorldLODsectorSize);	// fmul    ds:flt_858A48   ; 200.0f	; _ZN9CRenderer19ScanBigBuildingListEii
		}
		CPatch::LeaveThisLevel();
		#endif

		// Patch pointers to half a size of LOD sector per dimension (100.0)
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();
		{
			CPatch::PatchPointer(0x554B64 + 2, &fWorldLODsectorSizeHalf);	// fadd    ds:flt_858628   ; 100.0	; _ZN9CRenderer19ScanBigBuildingListEii
			CPatch::PatchPointer(0x554B7C + 2, &fWorldLODsectorSizeHalf);	// fadd    ds:flt_858628   ; 100.0	; _ZN9CRenderer19ScanBigBuildingListEii
		}
		CPatch::LeaveThisLevel();
		#endif

		// Patch pointers to size of LOD sector per dimension multiplied by square root of 2, then squared (80000.0)
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();
		{
			CPatch::PatchPointer(0x554B92 + 2, &fWorldLODsectorSizeTimesSquareRootOfTwoThenSquared);	// fcomp   ds:flt_863E14	; _ZN9CRenderer19ScanBigBuildingListEii
		}
		CPatch::LeaveThisLevel();
		#endif

		// Patch pointers to half of number of world LOD sectors per dimension
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();
		{
			CPatch::PatchPointer(0x40C568 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x40C584 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x40C5A7 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x40C5D2 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x534876 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x53488D + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x5348A6 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x5348BD + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x534B93 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x534BAA + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x534BC5 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x534BDC + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x55556D + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x555584 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x5555AA + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x5555C1 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x5555D8 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x5555EF + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x555609 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x555623 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x55563D + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x555657 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x564EE7 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x564F03 + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x564F1C + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48
			CPatch::PatchPointer(0x564F3A + 2, &fNumberOfWorldLODsectorsPerDimensionHalf);	// fadd    ds:flt_858B48				
		}
		CPatch::LeaveThisLevel();
		#endif

		// Patch pointers to inversed size of LOD sector (1/200),  flt_858B4C
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();
		{
			CPatch::PatchPointer(0x40C562 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x40C577 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x40C59A + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x40C5CC + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x534870 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x534885 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x53489C + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x5348B5 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x534B8D + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x534BA2 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x534BB9 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x534BD4 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x555567 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x55557E + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x5555A3 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x5555BB + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x5555D2 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x5555E9 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x555603 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x55561D + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x555637 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x555651 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x564EE1 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x564EFD + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x564F16 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
			CPatch::PatchPointer(0x564F34 + 2, &fWorldLODsectorSizeInversed);	// fmul    ds:flt_858B4C
		}
		CPatch::LeaveThisLevel();
		#endif
	}
	#endif

	// Function CCam::ProcessEditor
	#if TRUE
	{
		CPatch::RedirectCode(0x50F720, patch_CCam__Process_Editor_50F720);
	}
	#endif

	// Define variables for automatic patch
	#if TRUE
	{
		CCodeMover::SetVariable("NUMBER_OF_WORLD_SECTORS_PER_DIMENSION", iNumberOfWorldSectorsPerDimension);
		CCodeMover::SetVariable("NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE", iNumberOfWorldSectorsPerDimension - 1);

		CCodeMover::SetVariable("NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION", iNumberOfWorldLODsectorsPerDimension);
		CCodeMover::SetVariable("NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_MINUS_ONE", iNumberOfWorldLODsectorsPerDimension - 1);
		CCodeMover::SetVariable("SIZE_OF_WORLD_LOD_SECTORS_FOR_ONE_DIMENSION", iNumberOfWorldLODsectorsPerDimension * sizeof(void*));
		CCodeMover::SetVariable("MINUS_NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_HALF", -iNumberOfWorldLODsectorsPerDimension / 2);
	}
	#endif

	// Apply automatic patch
	#if TRUE
	{
		// Count of active addresses: 397
		CCodeMover::FixOnAddress(0x408627, 5, "\x01\x01\xbf\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40862C);	// line 1, 0x4084F0 - sub_4084F0 : mov     edi, 77h
		CCodeMover::FixOnAddress(0x4086E2, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xec\x86\x40\x00\x00", 0x4086E7);	// line 2, 0x4084F0 - sub_4084F0 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x4086E7, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x4086EC);	// line 3, 0x4084F0 - sub_4084F0 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x4086F0, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xfa\x86\x40\x00\x00", 0x4086F5);	// line 4, 0x4084F0 - sub_4084F0 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x4086F5, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x4086FA);	// line 5, 0x4084F0 - sub_4084F0 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x409129, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x33\x91\x40\x00\x00", 0x40912E);	// line 6, 0x4090A0 - sub_4090A0 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40912E, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x409133);	// line 7, 0x4090A0 - sub_4090A0 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40913F, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x49\x91\x40\x00\x00", 0x409144);	// line 8, 0x4090A0 - sub_4090A0 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x409144, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x409149);	// line 9, 0x4090A0 - sub_4090A0 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x4091AA, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xb4\x91\x40\x00\x00", 0x4091AF);	// line 10, 0x4090A0 - sub_4090A0 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x4091AF, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x4091B4);	// line 11, 0x4090A0 - sub_4090A0 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x4091B6, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xc0\x91\x40\x00\x00", 0x4091BB);	// line 12, 0x4090A0 - sub_4090A0 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x4091BB, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x4091C0);	// line 13, 0x4090A0 - sub_4090A0 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x4092C4, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xce\x92\x40\x00\x00", 0x4092C9);	// line 14, 0x409210 - sub_409210 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x4092C9, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x4092CE);	// line 15, 0x409210 - sub_409210 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x4092DA, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xe4\x92\x40\x00\x00", 0x4092DF);	// line 16, 0x409210 - sub_409210 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x4092DF, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x4092E4);	// line 17, 0x409210 - sub_409210 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40934C, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x56\x93\x40\x00\x00", 0x409351);	// line 18, 0x409210 - sub_409210 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x409351, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x409356);	// line 19, 0x409210 - sub_409210 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x409358, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x62\x93\x40\x00\x00", 0x40935D);	// line 20, 0x409210 - sub_409210 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40935D, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x409362);	// line 21, 0x409210 - sub_409210 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40D547, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40D54C);	// line 22, 0x40D3F8 - sub_40D3F8 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x40D66B, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x75\xd6\x40\x00\x00", 0x40D670);	// line 23, 0x40D3F8 - sub_40D3F8 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40D670, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40D675);	// line 24, 0x40D3F8 - sub_40D3F8 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40D679, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x83\xd6\x40\x00\x00", 0x40D67E);	// line 25, 0x40D3F8 - sub_40D3F8 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40D67E, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40D683);	// line 26, 0x40D3F8 - sub_40D3F8 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40D88E, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\x91\xD8\x40\x00\x00", 0x40D895);	// line 27, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40D8E4, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x02\xE7\xD8\x40\x00\x00", 0x40D8E9);	// line 28, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40D8EB, 5, "\x01\x01\xbf\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40D8F0);	// line 29, 0x4037EB - sub_4037EB : mov     edi, 77h
		CCodeMover::FixOnAddress(0x40D8F3, 7, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\xF6\xD8\x40\x00\x00", 0x40D8FA);	// line 30, 0x4037EB - sub_4037EB : cmp     esi, 77h
		CCodeMover::FixOnAddress(0x40D8FC, 5, "\x01\x01\xbe\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40D901);	// line 31, 0x4037EB - sub_4037EB : mov     esi, 77h
		CCodeMover::FixOnAddress(0x40D962, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x6c\xd9\x40\x00\x00", 0x40D967);	// line 32, 0x4037EB - sub_4037EB : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40D967, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40D96C);	// line 33, 0x4037EB - sub_4037EB : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40D976, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x02\x79\xD9\x40\x00\x00", 0x40D97B);	// line 34, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40D97D, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40D982);	// line 35, 0x4037EB - sub_4037EB : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40D9A6, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xb0\xd9\x40\x00\x00", 0x40D9AB);	// line 36, 0x4037EB - sub_4037EB : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40D9AB, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40D9B0);	// line 37, 0x4037EB - sub_4037EB : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40D9B2, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xbc\xd9\x40\x00\x00", 0x40D9B7);	// line 38, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40D9B7, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40D9BC);	// line 39, 0x4037EB - sub_4037EB : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40DA4D, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x02\x50\xDA\x40\x00\x00", 0x40DA52);	// line 40, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DA5A, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DA5F);	// line 41, 0x4037EB - sub_4037EB : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x40DA6C, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x02\x6F\xDA\x40\x00\x00", 0x40DA71);	// line 42, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DA73, 5, "\x01\x01\xbe\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DA78);	// line 43, 0x4037EB - sub_4037EB : mov     esi, 77h
		CCodeMover::FixOnAddress(0x40DAE2, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xec\xda\x40\x00\x00", 0x40DAE7);	// line 44, 0x4037EB - sub_4037EB : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40DAE7, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DAEC);	// line 45, 0x4037EB - sub_4037EB : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40DAFA, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x04\xdb\x40\x00\x00", 0x40DAFF);	// line 46, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DAFF, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DB04);	// line 47, 0x4037EB - sub_4037EB : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40DB28, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x32\xdb\x40\x00\x00", 0x40DB2D);	// line 48, 0x4037EB - sub_4037EB : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40DB2D, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DB32);	// line 49, 0x4037EB - sub_4037EB : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40DB34, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x3e\xdb\x40\x00\x00", 0x40DB39);	// line 50, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DB39, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DB3E);	// line 51, 0x4037EB - sub_4037EB : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40DC04, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x0e\xdc\x40\x00\x00", 0x40DC09);	// line 52, 0x4037EB - sub_4037EB : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40DC09, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DC0E);	// line 53, 0x4037EB - sub_4037EB : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40DC18, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x02\x1B\xDC\x40\x00\x00", 0x40DC1D);	// line 54, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DC1F, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DC24);	// line 55, 0x4037EB - sub_4037EB : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40DC46, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x50\xdc\x40\x00\x00", 0x40DC4B);	// line 56, 0x4037EB - sub_4037EB : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40DC4B, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DC50);	// line 57, 0x4037EB - sub_4037EB : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40DC52, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x5c\xdc\x40\x00\x00", 0x40DC57);	// line 58, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DC57, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DC5C);	// line 59, 0x4037EB - sub_4037EB : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40DCDB, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\xDE\xDC\x40\x00\x00", 0x40DCE2);	// line 60, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DD31, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x02\x34\xDD\x40\x00\x00", 0x40DD36);	// line 61, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DD38, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DD3D);	// line 62, 0x4037EB - sub_4037EB : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x40DD40, 7, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\x43\xDD\x40\x00\x00", 0x40DD47);	// line 63, 0x4037EB - sub_4037EB : cmp     esi, 77h
		CCodeMover::FixOnAddress(0x40DD49, 5, "\x01\x01\xbe\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DD4E);	// line 64, 0x4037EB - sub_4037EB : mov     esi, 77h
		CCodeMover::FixOnAddress(0x40DDAE, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xb8\xdd\x40\x00\x00", 0x40DDB3);	// line 65, 0x4037EB - sub_4037EB : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40DDB3, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DDB8);	// line 66, 0x4037EB - sub_4037EB : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40DDBA, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xc4\xdd\x40\x00\x00", 0x40DDBF);	// line 67, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DDBF, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DDC4);	// line 68, 0x4037EB - sub_4037EB : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40DDE8, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xf2\xdd\x40\x00\x00", 0x40DDED);	// line 69, 0x4037EB - sub_4037EB : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40DDED, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DDF2);	// line 70, 0x4037EB - sub_4037EB : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40DDF4, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xfe\xdd\x40\x00\x00", 0x40DDF9);	// line 71, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DDF9, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DDFE);	// line 72, 0x4037EB - sub_4037EB : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40DE93, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x02\x96\xDE\x40\x00\x00", 0x40DE98);	// line 73, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DEA0, 5, "\x01\x01\xbf\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DEA5);	// line 74, 0x4037EB - sub_4037EB : mov     edi, 77h
		CCodeMover::FixOnAddress(0x40DEB2, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x02\xB5\xDE\x40\x00\x00", 0x40DEB7);	// line 75, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DEB9, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DEBE);	// line 76, 0x4037EB - sub_4037EB : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x40DF3E, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x48\xdf\x40\x00\x00", 0x40DF43);	// line 77, 0x4037EB - sub_4037EB : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40DF43, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DF48);	// line 78, 0x4037EB - sub_4037EB : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40DF4A, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x54\xdf\x40\x00\x00", 0x40DF4F);	// line 79, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DF4F, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DF54);	// line 80, 0x4037EB - sub_4037EB : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40DF78, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x82\xdf\x40\x00\x00", 0x40DF7D);	// line 81, 0x4037EB - sub_4037EB : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40DF7D, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DF82);	// line 82, 0x4037EB - sub_4037EB : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40DF84, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x8e\xdf\x40\x00\x00", 0x40DF89);	// line 83, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40DF89, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40DF8E);	// line 84, 0x4037EB - sub_4037EB : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40E03F, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x02\x42\xE0\x40\x00\x00", 0x40E044);	// line 85, 0x4037EB - sub_4037EB : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40E046, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40E04B);	// line 86, 0x4037EB - sub_4037EB : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40E04D, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x57\xe0\x40\x00\x00", 0x40E052);	// line 87, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40E052, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40E057);	// line 88, 0x4037EB - sub_4037EB : mov     eax, 77h
		CCodeMover::FixOnAddress(0x40E07B, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x85\xe0\x40\x00\x00", 0x40E080);	// line 89, 0x4037EB - sub_4037EB : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x40E080, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40E085);	// line 90, 0x4037EB - sub_4037EB : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x40E087, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x91\xe0\x40\x00\x00", 0x40E08C);	// line 91, 0x4037EB - sub_4037EB : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x40E08C, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40E091);	// line 92, 0x4037EB - sub_4037EB : mov     eax, 77h
		CCodeMover::FixOnAddress(0x41A831, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x3b\xa8\x41\x00\x00", 0x41A836);	// line 93, 0x41A820 - sub_41A820 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x41A836, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x41A83B);	// line 94, 0x41A820 - sub_41A820 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x41A849, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x53\xa8\x41\x00\x00", 0x41A84E);	// line 95, 0x41A820 - sub_41A820 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x41A84E, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x41A853);	// line 96, 0x41A820 - sub_41A820 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x41ADA0, 5, "\x01\x01\xbe\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x41ADA5);	// line 97, 0x41AC40 - sub_41AC40 : mov     esi, 77h
		CCodeMover::FixOnAddress(0x42CF80, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x03\xa0\xcf\x42\x00\x00", 0x42CF85);	// line 98, 0x42CE40 - sub_42CE40 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x42CFA0, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x42CFA5);	// line 99, 0x42CE40 - sub_42CE40 : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x42CFCC, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x03\xee\xcf\x42\x00\x00", 0x42CFD1);	// line 100, 0x42CE40 - sub_42CE40 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x43271E, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x432723);	// line 101, 0x4325C0 - sub_4325C0 : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x434545, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x43454A);	// line 102, 0x434400 - sub_434400 : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x453973, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x03\x93\x39\x45\x00\x00", 0x453978);	// line 103, 0x453690 - sub_453690 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x453993, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x453998);	// line 104, 0x453690 - sub_453690 : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x4539BF, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x03\xe1\x39\x45\x00\x00", 0x4539C4);	// line 105, 0x453690 - sub_453690 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x5349E5, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xef\x49\x53\x00\x00", 0x5349EA);	// line 106, 0x5347D0 - sub_5347D0 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x5349EA, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x5349EF);	// line 107, 0x5347D0 - sub_5347D0 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x5349F9, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x03\x4a\x53\x00\x00", 0x5349FE);	// line 108, 0x5347D0 - sub_5347D0 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x5349FE, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x534A03);	// line 109, 0x5347D0 - sub_5347D0 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x534A75, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x7f\x4a\x53\x00\x00", 0x534A7A);	// line 110, 0x5347D0 - sub_5347D0 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x534A7A, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x534A7F);	// line 111, 0x5347D0 - sub_5347D0 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x534A89, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x93\x4a\x53\x00\x00", 0x534A8E);	// line 112, 0x5347D0 - sub_5347D0 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x534A8E, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x534A93);	// line 113, 0x5347D0 - sub_5347D0 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x534D47, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x51\x4d\x53\x00\x00", 0x534D4C);	// line 114, 0x534AE0 - sub_534AE0 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x534D4C, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x534D51);	// line 115, 0x534AE0 - sub_534AE0 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x534D5B, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x65\x4d\x53\x00\x00", 0x534D60);	// line 116, 0x534AE0 - sub_534AE0 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x534D60, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x534D65);	// line 117, 0x534AE0 - sub_534AE0 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x534DD7, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xe1\x4d\x53\x00\x00", 0x534DDC);	// line 118, 0x534AE0 - sub_534AE0 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x534DDC, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x534DE1);	// line 119, 0x534AE0 - sub_534AE0 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x534DEB, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xf5\x4d\x53\x00\x00", 0x534DF0);	// line 120, 0x534AE0 - sub_534AE0 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x534DF0, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x534DF5);	// line 121, 0x534AE0 - sub_534AE0 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x5466F4, 5, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xfe\x66\x54\x00\x00", 0x5466F9);	// line 122, 0x546670 - sub_546670 : cmp     esi, 77h
		CCodeMover::FixOnAddress(0x5466F9, 5, "\x01\x01\xbe\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x5466FE);	// line 123, 0x546670 - sub_546670 : mov     esi, 77h
		CCodeMover::FixOnAddress(0x54670F, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x19\x67\x54\x00\x00", 0x546714);	// line 124, 0x546670 - sub_546670 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x546714, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x546719);	// line 125, 0x546670 - sub_546670 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x54BAF6, 5, "\x01\x02\x81\xff\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x00\xbb\x54\x00\x00", 0x54BAFB);	// line 126, 0x54BA60 - sub_54BA60 : cmp     edi, 77h
		CCodeMover::FixOnAddress(0x54BAFB, 5, "\x01\x01\xbf\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x54BB00);	// line 127, 0x54BA60 - sub_54BA60 : mov     edi, 77h
		CCodeMover::FixOnAddress(0x54BB11, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x1b\xbb\x54\x00\x00", 0x54BB16);	// line 128, 0x54BA60 - sub_54BA60 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x54BB16, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x54BB1B);	// line 129, 0x54BA60 - sub_54BA60 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x55DF3A, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x55DF3F);	// line 130, 0x55D220 - sub_55D220 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x564782, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x8c\x47\x56\x00\x00", 0x564787);	// line 131, 0x564600 - sub_564600 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x564787, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56478C);	// line 132, 0x564600 - sub_564600 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x56478E, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x98\x47\x56\x00\x00", 0x564793);	// line 133, 0x564600 - sub_564600 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x564793, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x564798);	// line 134, 0x564600 - sub_564600 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x564B3C, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x46\x4b\x56\x00\x00", 0x564B41);	// line 135, 0x564A20 - sub_564A20 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x564B41, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x564B46);	// line 136, 0x564A20 - sub_564A20 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x564B4A, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x54\x4b\x56\x00\x00", 0x564B4F);	// line 137, 0x564A20 - sub_564A20 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x564B4F, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x564B54);	// line 138, 0x564A20 - sub_564A20 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x564D8C, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x96\x4d\x56\x00\x00", 0x564D91);	// line 139, 0x564C70 - sub_564C70 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x564D91, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x564D96);	// line 140, 0x564C70 - sub_564C70 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x564D9A, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xa4\x4d\x56\x00\x00", 0x564D9F);	// line 141, 0x564C70 - sub_564C70 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x564D9F, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x564DA4);	// line 142, 0x564C70 - sub_564C70 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x5664BC, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xc6\x64\x56\x00\x00", 0x5664C1);	// line 143, 0xFFFFFFFF -  : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x5664C1, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x5664C6);	// line 144, 0xFFFFFFFF -  : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x5664C8, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xd2\x64\x56\x00\x00", 0x5664CD);	// line 145, 0xFFFFFFFF -  : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x5664CD, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x5664D2);	// line 146, 0xFFFFFFFF -  : mov     eax, 77h
		CCodeMover::FixOnAddress(0x56656B, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x75\x65\x56\x00\x00", 0x566570);	// line 147, 0x566510 - sub_566510 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x566570, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x566575);	// line 148, 0x566510 - sub_566510 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x566577, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x81\x65\x56\x00\x00", 0x56657C);	// line 149, 0x566510 - sub_566510 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56657C, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x566581);	// line 150, 0x566510 - sub_566510 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x56757F, 7, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\x82\x75\x56\x00\x00", 0x567586);	// line 151, 0xFFFFFFFF -  : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x56759A, 5, "\x01\x02\x81\xfb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xa4\x75\x56\x00\x00", 0x56759F);	// line 152, 0xFFFFFFFF -  : cmp     ebx, 77h
		CCodeMover::FixOnAddress(0x56759F, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x5675A4);	// line 153, 0xFFFFFFFF -  : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x5676BF, 7, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\xC2\x76\x56\x00\x00", 0x5676C6);	// line 154, 0xFFFFFFFF -  : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x5676DA, 5, "\x01\x02\x81\xfb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xe4\x76\x56\x00\x00", 0x5676DF);	// line 155, 0xFFFFFFFF -  : cmp     ebx, 77h
		CCodeMover::FixOnAddress(0x5676DF, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x5676E4);	// line 156, 0xFFFFFFFF -  : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x568C9C, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xa6\x8c\x56\x00\x00", 0x568CA1);	// line 157, 0x568B80 - sub_568B80 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x568CA1, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x568CA6);	// line 158, 0x568B80 - sub_568B80 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x568CAA, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xb4\x8c\x56\x00\x00", 0x568CAF);	// line 159, 0x568B80 - sub_568B80 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x568CAF, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x568CB4);	// line 160, 0x568B80 - sub_568B80 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x568EDE, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xe8\x8e\x56\x00\x00", 0x568EE3);	// line 161, 0x568DD0 - sub_568DD0 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x568EE3, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x568EE8);	// line 162, 0x568DD0 - sub_568DD0 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x568EEC, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xf6\x8e\x56\x00\x00", 0x568EF1);	// line 163, 0x568DD0 - sub_568DD0 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x568EF1, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x568EF6);	// line 164, 0x568DD0 - sub_568DD0 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x56910A, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x14\x91\x56\x00\x00", 0x56910F);	// line 165, 0x568FF0 - sub_568FF0 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x56910F, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x569114);	// line 166, 0x568FF0 - sub_568FF0 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x569118, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x22\x91\x56\x00\x00", 0x56911D);	// line 167, 0x568FF0 - sub_568FF0 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56911D, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x569122);	// line 168, 0x568FF0 - sub_568FF0 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x56951A, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x24\x95\x56\x00\x00", 0x56951F);	// line 169, 0x5693F0 - sub_5693F0 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x56951F, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x569524);	// line 170, 0x5693F0 - sub_5693F0 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x569528, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x32\x95\x56\x00\x00", 0x56952D);	// line 171, 0x5693F0 - sub_5693F0 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56952D, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x569532);	// line 172, 0x5693F0 - sub_5693F0 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x569F3A, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x44\x9f\x56\x00\x00", 0x569F3F);	// line 173, 0x569E20 - sub_569E20 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x569F3F, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x569F44);	// line 174, 0x569E20 - sub_569E20 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x569F48, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x52\x9f\x56\x00\x00", 0x569F4D);	// line 175, 0x569E20 - sub_569E20 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x569F4D, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x569F52);	// line 176, 0x569E20 - sub_569E20 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x56A5F9, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\xFC\xA5\x56\x00\x00", 0x56A600);	// line 177, 0x56A490 - sub_56A490 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56A61A, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x24\xa6\x56\x00\x00", 0x56A61F);	// line 178, 0x56A490 - sub_56A490 : cmp     ebp, 77h
		CCodeMover::FixOnAddress(0x56A61F, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56A624);	// line 179, 0x56A490 - sub_56A490 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x56A6DA, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\xDD\xA6\x56\x00\x00", 0x56A6E1);	// line 180, 0x56A490 - sub_56A490 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56A6FB, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x05\xa7\x56\x00\x00", 0x56A700);	// line 181, 0x56A490 - sub_56A490 : cmp     ebp, 77h
		CCodeMover::FixOnAddress(0x56A700, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56A705);	// line 182, 0x56A490 - sub_56A490 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x56A7DF, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\xE2\xA7\x56\x00\x00", 0x56A7E6);	// line 183, 0x56A490 - sub_56A490 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56A7F4, 5, "\x01\x02\x81\xfb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xfe\xa7\x56\x00\x00", 0x56A7F9);	// line 184, 0x56A490 - sub_56A490 : cmp     ebx, 77h
		CCodeMover::FixOnAddress(0x56A7F9, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56A7FE);	// line 185, 0x56A490 - sub_56A490 : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x56A8C0, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\xC3\xA8\x56\x00\x00", 0x56A8C7);	// line 186, 0x56A490 - sub_56A490 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56A8D5, 5, "\x01\x02\x81\xfb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xdf\xa8\x56\x00\x00", 0x56A8DA);	// line 187, 0x56A490 - sub_56A490 : cmp     ebx, 77h
		CCodeMover::FixOnAddress(0x56A8DA, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56A8DF);	// line 188, 0x56A490 - sub_56A490 : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x56AC17, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\x1A\xAC\x56\x00\x00", 0x56AC1E);	// line 189, 0x56A490 - sub_56A490 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56AC38, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x42\xac\x56\x00\x00", 0x56AC3D);	// line 190, 0x56A490 - sub_56A490 : cmp     ebp, 77h
		CCodeMover::FixOnAddress(0x56AC3D, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56AC42);	// line 191, 0x56A490 - sub_56A490 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x56AD07, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\x0A\xAD\x56\x00\x00", 0x56AD0E);	// line 192, 0x56A490 - sub_56A490 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56AD28, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x32\xad\x56\x00\x00", 0x56AD2D);	// line 193, 0x56A490 - sub_56A490 : cmp     ebp, 77h
		CCodeMover::FixOnAddress(0x56AD2D, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56AD32);	// line 194, 0x56A490 - sub_56A490 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x56AE09, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\x0C\xAE\x56\x00\x00", 0x56AE10);	// line 195, 0x56A490 - sub_56A490 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56AE2A, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x34\xae\x56\x00\x00", 0x56AE2F);	// line 196, 0x56A490 - sub_56A490 : cmp     ebp, 77h
		CCodeMover::FixOnAddress(0x56AE2F, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56AE34);	// line 197, 0x56A490 - sub_56A490 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x56AEE8, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\xEB\xAE\x56\x00\x00", 0x56AEEF);	// line 198, 0x56A490 - sub_56A490 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56AF09, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x13\xaf\x56\x00\x00", 0x56AF0E);	// line 199, 0x56A490 - sub_56A490 : cmp     ebp, 77h
		CCodeMover::FixOnAddress(0x56AF0E, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56AF13);	// line 200, 0x56A490 - sub_56A490 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x56B237, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\x3A\xB2\x56\x00\x00", 0x56B23E);	// line 201, 0x56A490 - sub_56A490 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56B258, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x62\xb2\x56\x00\x00", 0x56B25D);	// line 202, 0x56A490 - sub_56A490 : cmp     ebp, 77h
		CCodeMover::FixOnAddress(0x56B25D, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56B262);	// line 203, 0x56A490 - sub_56A490 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x56B327, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\x2A\xB3\x56\x00\x00", 0x56B32E);	// line 204, 0x56A490 - sub_56A490 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56B348, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x52\xb3\x56\x00\x00", 0x56B34D);	// line 205, 0x56A490 - sub_56A490 : cmp     ebp, 77h
		CCodeMover::FixOnAddress(0x56B34D, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56B352);	// line 206, 0x56A490 - sub_56A490 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x56B429, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\x2C\xB4\x56\x00\x00", 0x56B430);	// line 207, 0x56A490 - sub_56A490 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56B44A, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x54\xb4\x56\x00\x00", 0x56B44F);	// line 208, 0x56A490 - sub_56A490 : cmp     ebp, 77h
		CCodeMover::FixOnAddress(0x56B44F, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56B454);	// line 209, 0x56A490 - sub_56A490 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x56B508, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\x0B\xB5\x56\x00\x00", 0x56B50F);	// line 210, 0x56A490 - sub_56A490 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56B529, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x33\xb5\x56\x00\x00", 0x56B52E);	// line 211, 0x56A490 - sub_56A490 : cmp     ebp, 77h
		CCodeMover::FixOnAddress(0x56B52E, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56B533);	// line 212, 0x56A490 - sub_56A490 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x56BBAC, 5, "\x01\x01\xba\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56BBB1);	// line 213, 0x56BA00 - sub_56BA00 : mov     edx, 77h
		CCodeMover::FixOnAddress(0x56BC9F, 5, "\x01\x01\xba\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56BCA4);	// line 214, 0x56BA00 - sub_56BA00 : mov     edx, 77h
		CCodeMover::FixOnAddress(0x56BDB9, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\xBC\xBD\x56\x00\x00", 0x56BDC0);	// line 215, 0x56BA00 - sub_56BA00 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56BDCE, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xd8\xbd\x56\x00\x00", 0x56BDD3);	// line 216, 0x56BA00 - sub_56BA00 : cmp     ebp, 77h
		CCodeMover::FixOnAddress(0x56BDD3, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56BDD8);	// line 217, 0x56BA00 - sub_56BA00 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x56BEB4, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\xB7\xBE\x56\x00\x00", 0x56BEBB);	// line 218, 0x56BA00 - sub_56BA00 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x56BEC9, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xd3\xbe\x56\x00\x00", 0x56BECE);	// line 219, 0x56BA00 - sub_56BA00 : cmp     ebp, 77h
		CCodeMover::FixOnAddress(0x56BECE, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56BED3);	// line 220, 0x56BA00 - sub_56BA00 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x56C29A, 5, "\x01\x01\xba\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56C29F);	// line 221, 0x56BA00 - sub_56BA00 : mov     edx, 77h
		CCodeMover::FixOnAddress(0x56C39B, 5, "\x01\x01\xba\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56C3A0);	// line 222, 0x56BA00 - sub_56BA00 : mov     edx, 77h
		CCodeMover::FixOnAddress(0x56C4BF, 5, "\x01\x01\xba\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56C4C4);	// line 223, 0x56BA00 - sub_56BA00 : mov     edx, 77h
		CCodeMover::FixOnAddress(0x56C5BA, 5, "\x01\x01\xba\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56C5BF);	// line 224, 0x56BA00 - sub_56BA00 : mov     edx, 77h
		CCodeMover::FixOnAddress(0x56C9A0, 5, "\x01\x01\xba\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56C9A5);	// line 225, 0x56BA00 - sub_56BA00 : mov     edx, 77h
		CCodeMover::FixOnAddress(0x56CAAA, 5, "\x01\x01\xba\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56CAAF);	// line 226, 0x56BA00 - sub_56BA00 : mov     edx, 77h
		CCodeMover::FixOnAddress(0x56CBCF, 5, "\x01\x01\xba\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56CBD4);	// line 227, 0x56BA00 - sub_56BA00 : mov     edx, 77h
		CCodeMover::FixOnAddress(0x56CCDA, 5, "\x01\x01\xba\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56CCDF);	// line 228, 0x56BA00 - sub_56BA00 : mov     edx, 77h
		CCodeMover::FixOnAddress(0x56DD32, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x56DD37);	// line 229, 0x56DBD0 - sub_56DBD0 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x5DC6AF, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x5DC6B4);	// line 230, 0x5DC510 - sub_5DC510 : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x5DC78A, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x94\xc7\x5d\x00\x00", 0x5DC78F);	// line 231, 0x5DC510 - sub_5DC510 : cmp     ecx, 77h	
		CCodeMover::FixOnAddress(0x5DC78F, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x5DC794);	// line 232, 0x5DC510 - sub_5DC510 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x5DC798, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xa2\xc7\x5d\x00\x00", 0x5DC79D);	// line 233, 0x5DC510 - sub_5DC510 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x5DC79D, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x5DC7A2);	// line 234, 0x5DC510 - sub_5DC510 : mov     eax, 77h

		CCodeMover::FixOnAddress(0x5FFBA2, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x03\xd2\xfb\x5f\x00\x00", 0x5FFBA7);	// line 235, 0x5FFA20 - sub_5FFA20 : cmp     eax, 77h				
		CCodeMover::FixOnAddress(0x5FFC00, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x03\x31\xfc\x5f\x00\x00", 0x5FFC05);	// line 236, 0x5FFA20 - sub_5FFA20 : cmp     eax, 77h		

		CCodeMover::FixOnAddress(0x605C8C, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x605C91);	// line 237, 0x605A30 - sub_605A30 : mov     ebp, 77h		
		CCodeMover::FixOnAddress(0x6062A6, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x6062AB);	// line 238, 0x6060A0 - sub_6060A0 : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x6063AA, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xb4\x63\x60\x00\x00", 0x6063AF);	// line 239, 0x6060A0 - sub_6060A0 : cmp     ecx, 77h		
		CCodeMover::FixOnAddress(0x6063AF, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x6063B4);	// line 240, 0x6060A0 - sub_6060A0 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x6063B8, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xc2\x63\x60\x00\x00", 0x6063BD);	// line 241, 0x6060A0 - sub_6060A0 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x6063BD, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x6063C2);	// line 242, 0x6060A0 - sub_6060A0 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x67FF40, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x4a\xff\x67\x00\x00", 0x67FF45);	// line 243, 0x40103C - sub_40103C : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x67FF45, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x67FF4A);	// line 244, 0x40103C - sub_40103C : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x67FF4E, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x58\xff\x67\x00\x00", 0x67FF53);	// line 245, 0x40103C - sub_40103C : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x67FF53, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x67FF58);	// line 246, 0x40103C - sub_40103C : mov     eax, 77h
		CCodeMover::FixOnAddress(0x699C0E, 5, "\x01\x01\xbf\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x699C13);	// line 247, 0x6997E0 - sub_6997E0 : mov     edi, 77h
		CCodeMover::FixOnAddress(0x699CDA, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xe4\x9c\x69\x00\x00", 0x699CDF);	// line 248, 0x6997E0 - sub_6997E0 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x699CDF, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x699CE4);	// line 249, 0x6997E0 - sub_6997E0 : mov     ecx, 77h		
		CCodeMover::FixOnAddress(0x699CE6, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xf0\x9c\x69\x00\x00", 0x699CEB);	// line 250, 0x6997E0 - sub_6997E0 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x699CEB, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x699CF0);	// line 251, 0x6997E0 - sub_6997E0 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x6B4323, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x03\x43\x43\x6b\x00\x00", 0x6B4328);	// line 252, 0x6B4200 - sub_6B4200 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x6B4343, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x6B4348);	// line 253, 0x6B4200 - sub_6B4200 : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x6B436F, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x03\x91\x43\x6b\x00\x00", 0x6B4374);	// line 254, 0x6B4200 - sub_6B4200 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x6B46FF, 5, "\x01\x01\xbf\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x6B4704);	// line 255, 0x6B45E0 - sub_6B45E0 : mov     edi, 77h
		CCodeMover::FixOnAddress(0x6E317E, 5, "\x01\x02\x81\xfa\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x88\x31\x6e\x00\x00", 0x6E3183);	// line 256, 0x6E2E50 - sub_6E2E50 : cmp     edx, 77h
		CCodeMover::FixOnAddress(0x6E3183, 5, "\x01\x01\xba\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x6E3188);	// line 257, 0x6E2E50 - sub_6E2E50 : mov     edx, 77h
		CCodeMover::FixOnAddress(0x6E318C, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x96\x31\x6e\x00\x00", 0x6E3191);	// line 258, 0x6E2E50 - sub_6E2E50 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x6E3191, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x6E3196);	// line 259, 0x6E2E50 - sub_6E2E50 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x6F6733, 5, "\x01\x01\xbe\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x6F6738);	// line 260, 0x6F6640 - sub_6F6640 : mov     esi, 77h
		CCodeMover::FixOnAddress(0x70ABA2, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x03\xc4\xab\x70\x00\x00", 0x70ABA7);	// line 261, 0x70A960 - sub_70A960 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x70ABF3, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x03\x15\xac\x70\x00\x00", 0x70ABF8);	// line 262, 0x70A960 - sub_70A960 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x70AC90, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x9a\xac\x70\x00\x00", 0x70AC95);	// line 263, 0x70A960 - sub_70A960 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x70AC95, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x70AC9A);	// line 264, 0x70A960 - sub_70A960 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x70AC9E, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\xa8\xac\x70\x00\x00", 0x70ACA3);	// line 265, 0x70A960 - sub_70A960 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x70ACA3, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x70ACA8);	// line 266, 0x70A960 - sub_70A960 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x70B876, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x70B87B);	// line 267, 0x70B730 - sub_70B730 : mov     ebp, 77h
		CCodeMover::FixOnAddress(0x70B94E, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x58\xb9\x70\x00\x00", 0x70B953);	// line 268, 0x70B730 - sub_70B730 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x70B953, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x70B958);	// line 269, 0x70B730 - sub_70B730 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x70B95C, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x66\xb9\x70\x00\x00", 0x70B961);	// line 270, 0x70B730 - sub_70B730 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x70B961, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x70B966);	// line 271, 0x70B730 - sub_70B730 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x711A3D, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x03\x5f\x1a\x71\x00\x00", 0x711A42);	// line 272, 0x711760 - sub_711760 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x711A8E, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x03\xae\x1a\x71\x00\x00", 0x711A93);	// line 273, 0x711760 - sub_711760 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x711AAE, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x711AB3);	// line 274, 0x711760 - sub_711760 : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x711B12, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x1c\x1b\x71\x00\x00", 0x711B17);	// line 275, 0x711760 - sub_711760 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x711B17, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x711B1C);	// line 276, 0x711760 - sub_711760 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x711B20, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x2a\x1b\x71\x00\x00", 0x711B25);	// line 277, 0x711760 - sub_711760 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x711B25, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x711B2A);	// line 278, 0x711760 - sub_711760 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x71CC72, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x71CC77);	// line 279, 0x71CB70 - sub_71CB70 : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x71CD4A, 5, "\x01\x02\x81\xfb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x54\xcd\x71\x00\x00", 0x71CD4F);	// line 280, 0x71CB70 - sub_71CB70 : cmp     ebx, 77h
		CCodeMover::FixOnAddress(0x71CD4F, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x71CD54);	// line 281, 0x71CB70 - sub_71CB70 : mov     ebx, 77h
		CCodeMover::FixOnAddress(0x71CD58, 5, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x62\xcd\x71\x00\x00", 0x71CD5D);	// line 282, 0x71CB70 - sub_71CB70 : cmp     esi, 77h
		CCodeMover::FixOnAddress(0x71CD5D, 5, "\x01\x01\xbe\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x71CD62);	// line 283, 0x71CB70 - sub_71CB70 : mov     esi, 77h
		CCodeMover::FixOnAddress(0x156682E, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x38\x68\x56\x01\x00", 0x1566833);	// line 284, 0x1566820 - sub_1566820 : cmp     ecx, 77h
		CCodeMover::FixOnAddress(0x1566833, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x1566838);	// line 285, 0x1566820 - sub_1566820 : mov     ecx, 77h
		CCodeMover::FixOnAddress(0x1566846, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x50\x68\x56\x01\x00", 0x156684B);	// line 286, 0x1566820 - sub_1566820 : cmp     eax, 77h
		CCodeMover::FixOnAddress(0x156684B, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x1566850);	// line 287, 0x1566820 - sub_1566820 : mov     eax, 77h
		CCodeMover::FixOnAddress(0x4086FA, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xFD\x86\x40\x00\x00", 0x4086FF);	// line 288, 0x4084F0 - sub_4084F0 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x409149, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x4C\x91\x40\x00\x00", 0x40914E);	// line 289, 0x4090A0 - sub_4090A0 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x4091C0, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xC3\x91\x40\x00\x00", 0x4091C5);	// line 290, 0x4090A0 - sub_4090A0 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x4091E7, 9, "\x01\x02\x81\xff\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8C\x03\x25\x91\x40\x00\x00", 0x4091F0);	// line 291, 0x4090A0 - sub_4090A0 : cmp     edi, 78h
		CCodeMover::FixOnAddress(0x4091F5, 7, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\xF8\x91\x40\x00\x00", 0x4091FC);	// line 292, 0x4090A0 - sub_4090A0 : cmp     eax, 78h
		CCodeMover::FixOnAddress(0x4092E4, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xE7\x92\x40\x00\x00", 0x4092E9);	// line 293, 0x409210 - sub_409210 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x409362, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x65\x93\x40\x00\x00", 0x409367);	// line 294, 0x409210 - sub_409210 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x40938D, 9, "\x01\x02\x81\xff\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8C\x03\x80\x92\x40\x00\x00", 0x409396);	// line 295, 0x409210 - sub_409210 : cmp     edi, 78h
		CCodeMover::FixOnAddress(0x409397, 7, "\x01\x02\x81\xfa\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\x9A\x93\x40\x00\x00", 0x40939E);	// line 296, 0x409210 - sub_409210 : cmp     edx, 78h
		CCodeMover::FixOnAddress(0x40D683, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x86\xD6\x40\x00\x00", 0x40D688);	// line 297, 0x40D3F8 - sub_40D3F8 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x40D986, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x89\xD9\x40\x00\x00", 0x40D98B);	// line 298, 0x4037EB - sub_4037EB : imul    eax, 78h
		CCodeMover::FixOnAddress(0x40D9C0, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xC3\xD9\x40\x00\x00", 0x40D9C5);	// line 299, 0x4037EB - sub_4037EB : imul    eax, 78h
		CCodeMover::FixOnAddress(0x40DB08, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x0B\xDB\x40\x00\x00", 0x40DB0D);	// line 300, 0x4037EB - sub_4037EB : imul    eax, 78h
		CCodeMover::FixOnAddress(0x40DB42, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x45\xDB\x40\x00\x00", 0x40DB47);	// line 301, 0x4037EB - sub_4037EB : imul    eax, 78h
		CCodeMover::FixOnAddress(0x40DC24, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x27\xDC\x40\x00\x00", 0x40DC29);	// line 302, 0x4037EB - sub_4037EB : imul    eax, 78h
		CCodeMover::FixOnAddress(0x40DC5C, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x5F\xDC\x40\x00\x00", 0x40DC61);	// line 303, 0x4037EB - sub_4037EB : imul    eax, 78h
		CCodeMover::FixOnAddress(0x40DDC8, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xCB\xDD\x40\x00\x00", 0x40DDCD);	// line 304, 0x4037EB - sub_4037EB : imul    eax, 78h
		CCodeMover::FixOnAddress(0x40DE02, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x05\xDE\x40\x00\x00", 0x40DE07);	// line 305, 0x4037EB - sub_4037EB : imul    eax, 78h
		CCodeMover::FixOnAddress(0x40DF58, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x5B\xDF\x40\x00\x00", 0x40DF5D);	// line 306, 0x4037EB - sub_4037EB : imul    eax, 78h
		CCodeMover::FixOnAddress(0x40DF92, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x95\xDF\x40\x00\x00", 0x40DF97);	// line 307, 0x4037EB - sub_4037EB : imul    eax, 78h
		CCodeMover::FixOnAddress(0x40E05B, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x5E\xE0\x40\x00\x00", 0x40E060);	// line 308, 0x4037EB - sub_4037EB : imul    eax, 78h
		CCodeMover::FixOnAddress(0x40E095, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x98\xE0\x40\x00\x00", 0x40E09A);	// line 309, 0x4037EB - sub_4037EB : imul    eax, 78h
		CCodeMover::FixOnAddress(0x41A853, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x56\xA8\x41\x00\x02\x01\x57\xA8\x41\x00\x00", 0x41A858);	// line 310, 0x41A820 - sub_41A820 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x534A03, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x06\x4A\x53\x00\x00", 0x534A08);	// line 311, 0x5347D0 - sub_5347D0 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x534A93, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x96\x4A\x53\x00\x00", 0x534A98);	// line 312, 0x5347D0 - sub_5347D0 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x534D65, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x68\x4D\x53\x00\x00", 0x534D6A);	// line 313, 0x534AE0 - sub_534AE0 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x534DF5, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xF8\x4D\x53\x00\x00", 0x534DFA);	// line 314, 0x534AE0 - sub_534AE0 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x54671D, 7, "\x01\x02\x69\xc9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\x20\x67\x54\x00\x00", 0x546724);	// line 315, 0x546670 - sub_546670 : imul    ecx, 78h
		CCodeMover::FixOnAddress(0x54BB1B, 5, "\x01\x02\x69\xc9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x1E\xBB\x54\x00\x00", 0x54BB20);	// line 316, 0x54BA60 - sub_54BA60 : imul    ecx, 78h
		CCodeMover::FixOnAddress(0x55356C, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\xa7\x35\x55\x00\x00", 0x553571);	// line 317, 0x553540 - sub_553540 : cmp     ecx, 78h
		CCodeMover::FixOnAddress(0x553571, 5, "\x01\x02\x81\xfa\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\xa7\x35\x55\x00\x00", 0x553576);	// line 318, 0x553540 - sub_553540 : cmp     edx, 78h
		CCodeMover::FixOnAddress(0x555912, 5, "\x01\x02\x81\xff\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\x54\x59\x55\x00\x00", 0x555917);	// line 319, 0x555900 - sub_555900 : cmp     edi, 78h
		CCodeMover::FixOnAddress(0x555917, 5, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\x54\x59\x55\x00\x00", 0x55591C);	// line 320, 0x555900 - sub_555900 : cmp     esi, 78h
		CCodeMover::FixOnAddress(0x56422C, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x00", 0x564231);	// line 321, 0x564050 - sub_564050 : mov     ecx, 78h
		CCodeMover::FixOnAddress(0x56425B, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x00", 0x564260);	// line 322, 0x564050 - sub_564050 : mov     ecx, 78h
		CCodeMover::FixOnAddress(0x56429D, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x00", 0x5642A2);	// line 323, 0x564050 - sub_564050 : mov     ecx, 78h
		CCodeMover::FixOnAddress(0x5642CC, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x00", 0x5642D1);	// line 324, 0x564050 - sub_564050 : mov     ecx, 78h
		CCodeMover::FixOnAddress(0x5642F6, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x00", 0x5642FB);	// line 325, 0x564050 - sub_564050 : mov     ecx, 78h
		CCodeMover::FixOnAddress(0x5646C4, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\xe4\x46\x56\x00\x00", 0x5646C9);	// line 326, 0x564600 - sub_564600 : cmp     eax, 78h
		CCodeMover::FixOnAddress(0x5646E4, 5, "\x01\x01\xbb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x00", 0x5646E9);	// line 327, 0x564600 - sub_564600 : mov     ebx, 78h
		CCodeMover::FixOnAddress(0x564710, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\x32\x47\x56\x00\x00", 0x564715);	// line 328, 0x564600 - sub_564600 : cmp     eax, 78h
		CCodeMover::FixOnAddress(0x564798, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x9B\x47\x56\x00\x00", 0x56479D);	// line 329, 0x564600 - sub_564600 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x564B54, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x57\x4B\x56\x00\x00", 0x564B59);	// line 330, 0x564A20 - sub_564A20 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x564DA4, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xA7\x4D\x56\x00\x00", 0x564DA9);	// line 331, 0x564C70 - sub_564C70 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x5664D2, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xD5\x64\x56\x00\x00", 0x5664D7);	// line 332, 0xFFFFFFFF -  : imul    eax, 78h
		CCodeMover::FixOnAddress(0x5664F1, 5, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8C\x03\xb2\x64\x56\x00\x00", 0x5664F6);	// line 333, 0xFFFFFFFF -  : cmp     esi, 78h
		CCodeMover::FixOnAddress(0x5664F7, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8C\x03\xa6\x64\x56\x00\x00", 0x5664FC);	// line 334, 0xFFFFFFFF -  : cmp     ebp, 78h
		CCodeMover::FixOnAddress(0x566581, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x84\x65\x56\x00\x00", 0x566586);	// line 335, 0x566510 - sub_566510 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x5665ED, 9, "\x01\x02\x81\xff\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8C\x03\x61\x65\x56\x00\x00", 0x5665F6);	// line 336, 0x566510 - sub_566510 : cmp     edi, 78h
		CCodeMover::FixOnAddress(0x5665F7, 9, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8C\x03\x55\x65\x56\x00\x00", 0x566600);	// line 337, 0x566510 - sub_566510 : cmp     ebp, 78h
		CCodeMover::FixOnAddress(0x5675E0, 7, "\x01\x02\x69\xdb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\xE3\x75\x56\x00\x00", 0x5675E7);	// line 338, 0xFFFFFFFF -  : imul    ebx, 78h
		CCodeMover::FixOnAddress(0x56771B, 6, "\x01\x02\x69\xdb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x03\x1E\x77\x56\x00\x00", 0x567721);	// line 339, 0xFFFFFFFF -  : imul    ebx, 78h
		CCodeMover::FixOnAddress(0x568CB4, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xB7\x8C\x56\x00\x00", 0x568CB9);	// line 340, 0x568B80 - sub_568B80 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x568EF6, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xF9\x8E\x56\x00\x00", 0x568EFB);	// line 341, 0x568DD0 - sub_568DD0 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x569122, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x25\x91\x56\x00\x00", 0x569127);	// line 342, 0x568FF0 - sub_568FF0 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x569532, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x35\x95\x56\x00\x00", 0x569537);	// line 343, 0x5693F0 - sub_5693F0 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x569F52, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x55\x9F\x56\x00\x00", 0x569F57);	// line 344, 0x569E20 - sub_569E20 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x56A667, 7, "\x01\x02\x69\xed\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\x6A\xA6\x56\x00\x00", 0x56A66E);	// line 345, 0x56A490 - sub_56A490 : imul    ebp, 78h
		CCodeMover::FixOnAddress(0x56A748, 7, "\x01\x02\x69\xed\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\x4B\xA7\x56\x00\x00", 0x56A74F);	// line 346, 0x56A490 - sub_56A490 : imul    ebp, 78h
		CCodeMover::FixOnAddress(0x56A841, 8, "\x01\x02\x69\xdb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x44\xA8\x56\x00\x02\x04\x45\xA8\x56\x00\x00", 0x56A849);	// line 347, 0x56A490 - sub_56A490 : imul    ebx, 78h
		CCodeMover::FixOnAddress(0x56A922, 8, "\x01\x02\x69\xdb\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x25\xA9\x56\x00\x02\x04\x26\xA9\x56\x00\x00", 0x56A92A);	// line 348, 0x56A490 - sub_56A490 : imul    ebx, 78h
		CCodeMover::FixOnAddress(0x56AC85, 7, "\x01\x02\x69\xed\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\x88\xAC\x56\x00\x00", 0x56AC8C);	// line 349, 0x56A490 - sub_56A490 : imul    ebp, 78h
		CCodeMover::FixOnAddress(0x56AD75, 8, "\x01\x02\x69\xed\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x78\xAD\x56\x00\x02\x04\x79\xAD\x56\x00\x00", 0x56AD7D);	// line 350, 0x56A490 - sub_56A490 : imul    ebp, 78h
		CCodeMover::FixOnAddress(0x56AE77, 7, "\x01\x02\x69\xed\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\x7A\xAE\x56\x00\x00", 0x56AE7E);	// line 351, 0x56A490 - sub_56A490 : imul    ebp, 78h
		CCodeMover::FixOnAddress(0x56AF56, 7, "\x01\x02\x69\xed\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\x59\xAF\x56\x00\x00", 0x56AF5D);	// line 352, 0x56A490 - sub_56A490 : imul    ebp, 78h
		CCodeMover::FixOnAddress(0x56B2A5, 7, "\x01\x02\x69\xed\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\xA8\xB2\x56\x00\x00", 0x56B2AC);	// line 353, 0x56A490 - sub_56A490 : imul    ebp, 78h
		CCodeMover::FixOnAddress(0x56B395, 8, "\x01\x02\x69\xed\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x98\xB3\x56\x00\x02\x04\x99\xB3\x56\x00\x00", 0x56B39D);	// line 354, 0x56A490 - sub_56A490 : imul    ebp, 78h
		CCodeMover::FixOnAddress(0x56B497, 7, "\x01\x02\x69\xed\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\x9A\xB4\x56\x00\x00", 0x56B49E);	// line 355, 0x56A490 - sub_56A490 : imul    ebp, 78h
		CCodeMover::FixOnAddress(0x56B576, 7, "\x01\x02\x69\xed\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\x79\xB5\x56\x00\x00", 0x56B57D);	// line 356, 0x56A490 - sub_56A490 : imul    ebp, 78h
		CCodeMover::FixOnAddress(0x56BC4B, 8, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x4E\xBC\x56\x00\x02\x04\x4F\xBC\x56\x00\x00", 0x56BC53);	// line 357, 0x56BA00 - sub_56BA00 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x56BD3E, 8, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x41\xBD\x56\x00\x02\x04\x42\xBD\x56\x00\x00", 0x56BD46);	// line 358, 0x56BA00 - sub_56BA00 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x56BE34, 7, "\x01\x02\x69\xed\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\x37\xBE\x56\x00\x00", 0x56BE3B);	// line 359, 0x56BA00 - sub_56BA00 : imul    ebp, 78h
		CCodeMover::FixOnAddress(0x56BF2F, 7, "\x01\x02\x69\xed\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\x32\xBF\x56\x00\x00", 0x56BF36);	// line 360, 0x56BA00 - sub_56BA00 : imul    ebp, 78h
		CCodeMover::FixOnAddress(0x56C339, 8, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x3C\xC3\x56\x00\x02\x04\x3D\xC3\x56\x00\x00", 0x56C341);	// line 361, 0x56BA00 - sub_56BA00 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x56C43D, 8, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x40\xC4\x56\x00\x02\x04\x41\xC4\x56\x00\x00", 0x56C445);	// line 362, 0x56BA00 - sub_56BA00 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x56C561, 8, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x64\xC5\x56\x00\x02\x04\x65\xC5\x56\x00\x00", 0x56C569);	// line 363, 0x56BA00 - sub_56BA00 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x56C65C, 8, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x5F\xC6\x56\x00\x02\x04\x60\xC6\x56\x00\x00", 0x56C664);	// line 364, 0x56BA00 - sub_56BA00 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x56CA42, 8, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x45\xCA\x56\x00\x02\x04\x46\xCA\x56\x00\x00", 0x56CA4A);	// line 365, 0x56BA00 - sub_56BA00 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x56CB49, 8, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x4C\xCB\x56\x00\x02\x04\x4D\xCB\x56\x00\x00", 0x56CB51);	// line 366, 0x56BA00 - sub_56BA00 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x56CC71, 8, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x74\xCC\x56\x00\x02\x04\x75\xCC\x56\x00\x00", 0x56CC79);	// line 367, 0x56BA00 - sub_56BA00 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x56CD7C, 8, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\x7F\xCD\x56\x00\x02\x04\x80\xCD\x56\x00\x00", 0x56CD84);	// line 368, 0x56BA00 - sub_56BA00 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x5DC7A2, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xA5\xC7\x5D\x00\x00", 0x5DC7A7);	// line 369, 0x5DC510 - sub_5DC510 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x6063C2, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xC5\x63\x60\x00\x00", 0x6063C7);	// line 370, 0x6060A0 - sub_6060A0 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x6124DA, 5, "\x01\x01\xbd\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x00", 0x6124DF);	// line 371, 0x6123A0 - sub_6123A0 : mov     ebp, 78h
		CCodeMover::FixOnAddress(0x67FF58, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x5B\xFF\x67\x00\x00", 0x67FF5D);	// line 372, 0x40103C - sub_40103C : imul    eax, 78h
		CCodeMover::FixOnAddress(0x699CF0, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xF3\x9C\x69\x00\x00", 0x699CF5);	// line 373, 0x6997E0 - sub_6997E0 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x6E3072, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\xa4\x30\x6e\x00\x00", 0x6E3077);	// line 374, 0x6E2E50 - sub_6E2E50 : cmp     eax, 78h
		CCodeMover::FixOnAddress(0x6E30D3, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\x05\x31\x6e\x00\x00", 0x6E30D8);	// line 375, 0x6E2E50 - sub_6E2E50 : cmp     eax, 78h
		CCodeMover::FixOnAddress(0x6E3196, 6, "\x01\x02\x69\xc9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x03\x99\x31\x6E\x00\x00", 0x6E319C);	// line 376, 0x6E2E50 - sub_6E2E50 : imul    ecx, 78h
		CCodeMover::FixOnAddress(0x6E773D, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x00", 0x6E7742);	// line 377, 0x6E76F0 - sub_6E76F0 : mov     ecx, 78h
		CCodeMover::FixOnAddress(0x70ACA8, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\xAB\xAC\x70\x00\x00", 0x70ACAD);	// line 378, 0x70A960 - sub_70A960 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x70B96C, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x6F\xB9\x70\x00\x00", 0x70B971);	// line 379, 0x70B730 - sub_70B730 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x711B2A, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x2D\x1B\x71\x00\x00", 0x711B2F);	// line 380, 0x711760 - sub_711760 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x71CD92, 7, "\x01\x02\x69\xf6\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\x95\xCD\x71\x00\x00", 0x71CD99);	// line 381, 0x71CB70 - sub_71CB70 : imul    esi, 78h
		CCodeMover::FixOnAddress(0x1566850, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x02\x53\x68\x56\x01\x00", 0x1566855);	// line 382, 0x1566820 - sub_1566820 : imul    eax, 78h
		CCodeMover::FixOnAddress(0x4072C8, 5, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION\x00\x02\x02\xCB\x72\x40\x00\x00", 0x4072CD);	// line 383, 0x4072C0 - sub_4072C0 : imul    eax, 1Eh
		CCodeMover::FixOnAddress(0x5348D2, 5, "\x01\x02\x69\xc9\x05\x04NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION\x00\x02\x02\xD5\x48\x53\x00\x00", 0x5348D7);	// line 384, 0x5347D0 - sub_5347D0 : imul    ecx, 1Eh
		CCodeMover::FixOnAddress(0x53490A, 8, "\x01\x02\x81\xc5\x05\x04SIZE_OF_WORLD_LOD_SECTORS_FOR_ONE_DIMENSION\x00\x02\x01\x0D\x49\x53\x00\x02\x04\x0E\x49\x53\x00\x00", 0x534912);	// line 385, 0x5347D0 - sub_5347D0 : add     ebp, 78h
		CCodeMover::FixOnAddress(0x534BF1, 5, "\x01\x02\x69\xc9\x05\x04NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION\x00\x02\x02\xF4\x4B\x53\x00\x00", 0x534BF6);	// line 386, 0x534AE0 - sub_534AE0 : imul    ecx, 1Eh
		CCodeMover::FixOnAddress(0x534C63, 8, "\x01\x02\x81\xc7\x05\x04SIZE_OF_WORLD_LOD_SECTORS_FOR_ONE_DIMENSION\x00\x02\x01\x66\x4C\x53\x00\x02\x04\x67\x4C\x53\x00\x00", 0x534C6B);	// line 387, 0x534AE0 - sub_534AE0 : add     edi, 78h
		CCodeMover::FixOnAddress(0x554B28, 9, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\x52\x4c\x55\x00\x00", 0x554B31);	// line 388, 0x554B10 - sub_554B10 : cmp     ecx, 1Eh
		CCodeMover::FixOnAddress(0x554B31, 9, "\x01\x01\x3d\x05\x04NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\x52\x4c\x55\x00\x00", 0x554B3A);	// line 389, 0x554B10 - sub_554B10 : cmp     eax, 1Eh
		CCodeMover::FixOnAddress(0x554B3C, 5, "\x01\x02\x69\xd2\x05\x04NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION\x00\x02\x02\x3F\x4B\x55\x00\x00", 0x554B41);	// line 390, 0x554B10 - sub_554B10 : imul    edx, 1Eh
		CCodeMover::FixOnAddress(0x554B41, 7, "\x01\x02\x81\xc1\x05\x04MINUS_NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_HALF\x00\x02\x04\x44\x4B\x55\x00\x00", 0x554B48);	// line 391, 0x554B10 - sub_554B10 : add     ecx, 0FFFFFFF1h
		CCodeMover::FixOnAddress(0x554B48, 7, "\x01\x01\x05\x05\x04MINUS_NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_HALF\x00\x02\x04\x4B\x4B\x55\x00\x00", 0x554B4F);	// line 392, 0x554B10 - sub_554B10 : add     eax, 0FFFFFFF1h
		CCodeMover::FixOnAddress(0x564F7C, 5, "\x01\x02\x69\xc9\x05\x04NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION\x00\x02\x02\x7F\x4F\x56\x00\x00", 0x564F81);	// line 393, 0x564ED0 - sub_564ED0 : imul    ecx, 1Eh
		CCodeMover::FixOnAddress(0x564FE6, 8, "\x01\x02\x81\xc1\x05\x04SIZE_OF_WORLD_LOD_SECTORS_FOR_ONE_DIMENSION\x00\x02\x01\xE9\x4F\x56\x00\x02\x04\xEA\x4F\x56\x00\x00", 0x564FEE);	// line 394, 0x564ED0 - sub_564ED0 : add     ecx, 78h
		CCodeMover::FixOnAddress(0x40C5B7, 5, "\x01\x01\xbe\x05\x04NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x40C5BC);	// line 395, 0x40C520 - sub_40C520 : mov     esi, 29
		CCodeMover::FixOnAddress(0x40C60F, 5, "\x01\x02\x69\xd2\x05\x04NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION\x00\x02\x02\x12\xC6\x40\x00\x00", 0x40C614);	// line 396, 0x40C520 - sub_40C520 : imul    edx, 1Eh
		CCodeMover::FixOnAddress(0x40C68C, 8, "\x01\x02\x81\xc1\x05\x04SIZE_OF_WORLD_LOD_SECTORS_FOR_ONE_DIMENSION\x00\x02\x01\x8F\xC6\x40\x00\x02\x04\x90\xC6\x40\x00\x00", 0x40C694);	// line 397, 0x40C520 - sub_40C520 : add     ecx, 78h
	}
	#endif

	//printf_MessageBox("dgfgg");
	//return;

	// Undefine variables of automatic patch
	#if TRUE
	{
		CCodeMover::DeleteVariable("NUMBER_OF_WORLD_SECTORS_PER_DIMENSION");
		CCodeMover::DeleteVariable("NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE");

		CCodeMover::DeleteVariable("NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION");
		CCodeMover::DeleteVariable("NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_MINUS_ONE");
		CCodeMover::DeleteVariable("SIZE_OF_WORLD_LOD_SECTORS_FOR_ONE_DIMENSION");
		CCodeMover::DeleteVariable("MINUS_NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_HALF");
	}
	#endif
}
#endif

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
namespace Game_GTASA
{
	extern "C"
	{
		uint32_t TotalNumberOfWorldSectorsMultipliedBySizeOfCSector = 0;
		uint32_t TotalNumberOfWorldLODsectorsMultipliedBySizeOfLODsector = 0;
		uint32_t NumberOfWorldLODSectorsPerDimensionMultipliedByListSize = 0;	// default: 30 * 4
	}

	// Automatic patches
	#include "WorldSectorLimits/GTA SA 2.0 ANDROID_ARMEABI_V7A/functions.cpp"	

	// Manual patches
	#if TRUE
	// patch for 0x3FCE94
	extern "C"
	{
		uintptr_t Address_CPhysical__Add_3FCFA4_thumb = 0;
		uintptr_t Address_CPhysical__Add_3FCEC6_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPhysical__Add_3FCE94()
	{
		__asm(
		".thumb\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMultipliedBy2)

			"BHI 10f\n"
			"VMOV R0, S4\n"
			"MOV R1, R0\n"
			"STR R1, [SP,#12]\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
			"10:\n"

			"BHI 10f\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMultipliedBy2)
			"10:\n"

			"BHI 1f\n"
			"VMOV R0, S2\n"
			"MOV R1, R0\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMultipliedBy2)
			"STR R1, [SP,#28]\n"

			"BHI 10f\n"
			"VMOV R0, S0\n"
			"MOV R1, R0\n"
			"STR R1, [SP,#4]\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
			"10:\n"

			"BHI 10f\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMultipliedBy2)
			"10:\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPhysical__Add_3FCEC6_thumb)

			// Branches
			"1:\n"	// loc_3FCFA4
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPhysical__Add_3FCFA4_thumb)
			);
	}

	// patch for 0x59BE1E
	extern "C"
	{
		uintptr_t Address_CWaterLevel__IsLocationOutOfWorldBounds_WS_59BE30_thumb = 0;
		uintptr_t Address_CWaterLevel__IsLocationOutOfWorldBounds_WS_59BE28_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CWaterLevel__IsLocationOutOfWorldBounds_WS_59BE1E()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimension)

			"ITT GE\n"
			"RSBGE R0, R4, R2\n"
			"CMPGE R0, R1\n"

			"BGT 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CWaterLevel__IsLocationOutOfWorldBounds_WS_59BE28_thumb)

			// Branches
			"1:\n"	// loc_59BE30
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CWaterLevel__IsLocationOutOfWorldBounds_WS_59BE30_thumb)
			);
	}

	// patch for 0x40A592
	extern "C"
	{
		uintptr_t Address_CPlayerInfo__Process_40A59E_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPlayerInfo__Process_40A592()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S20, fWorldSectorSize)
			"VDIV.F32 S6, S6, S20\n"
			"VADD.F32 S6, S6, S22\n"
			"VMOV R0, S6\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPlayerInfo__Process_40A59E_thumb)
			);
	}
	#endif
}

// Patches world sectors
void MapLimits::PatchWorldSectors_GTA_SA_2_0_ANDROID_ARM32()
{
	using namespace Game_GTASA;

	// Address to see: 0x40A5C0, manual patch should be here
	// 0x3FCEB6 - manual patch
	// See _ZN6CWorld19TestForUnusedModelsEv

	// Adress to see: CPhysicall:Add 240
	// Address to see: 0x59BE1E CWaterLevel::IsLocationOutOfWorldBounds_WS

	// Value to look for: 14440
	// See CEntity::Add, multiplication by 0x20, memory size

	// Set variables
	#if TRUE
	{
		TotalNumberOfWorldSectorsMultipliedBySizeOfCSector = iTotalNumberOfWorldSectors * sizeof(CSector);
		TotalNumberOfWorldLODsectorsMultipliedBySizeOfLODsector = iTotalNumberOfWorldLODsectors * sizeof(void*);
		NumberOfWorldLODSectorsPerDimensionMultipliedByListSize = iNumberOfWorldLODsectorsPerDimension * sizeof(void*);
	}
	#endif

	// Patch coordinates
	#if TRUE
	{
		struct {
			float l;
			float t;
			float r;
			float b;
		} mapCoordRect;

		mapCoordRect.l = fWorldMapMinCoord;
		mapCoordRect.t = fWorldMapMaxCoord;
		mapCoordRect.r = fWorldMapMaxCoord;
		mapCoordRect.b = fWorldMapMinCoord;

		// CIplStore::Initialise
		CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x280330), &mapCoordRect, sizeof(mapCoordRect));
	}
	#endif

	// CWorld::ms_aSectors
	#if TRUE
	{
		// Patch pointers to CWorld::ms_aSectors
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x676734), CWorld__ms_aSectors.gta_sa);
		}
		#endif

		// Manual patches
		#if TRUE
		{
			Address_CPhysical__Add_3FCFA4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3FCFA4));
			Address_CPhysical__Add_3FCEC6_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3FCEC6));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3FCE94),
				(void*)&patch_CPhysical__Add_3FCE94
			);

			Address_CWaterLevel__IsLocationOutOfWorldBounds_WS_59BE30_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x59BE30));
			Address_CWaterLevel__IsLocationOutOfWorldBounds_WS_59BE28_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x59BE28));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x59BE1E),
				(void*)&patch_CWaterLevel__IsLocationOutOfWorldBounds_WS_59BE1E
			);

			Address_CPlayerInfo__Process_40A59E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x40A59E));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x40A592),
				(void*)&patch_CPlayerInfo__Process_40A592
			);
		}
		#endif
	}
	#endif

	// CWorld::ms_aLodPtrLists
	#if TRUE
	{
		// Patch pointer
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x67738C), CWorld__ms_aLodPtrLists.gta_sa);
	}
	#endif

	// Automatic patches
	#if TRUE
	{
		#include "WorldSectorLimits/GTA SA 2.0 ANDROID_ARMEABI_V7A/changes.cpp"
	}
	#endif
}
#endif

// GTA IV
namespace Game_GTAIV
{
	uint32_t CClass_1136170::MemberOffsetArray[Offset_class_1136170__enumCount];
}

#ifdef IS_PLATFORM_WIN_X86
// GTA IV
namespace Game_GTAIV
{
	uintptr_t Address_7D7749 = NULL;

	NAKED void patch_7D773D()
	{
		__asm
		{
			push iNumberOfWorldSectorsPerDimensionDividedBy8;
			mulss   xmm0, xmm1;
			addss   xmm0, xmm2;
			push iNumberOfWorldSectorsPerDimensionDividedBy8;

			jmp Address_7D7749;
		}
	}

	// Fixes optimized multiplication, 7 bytes
	void FixOptimizedMul(uintptr_t dwAddress, __int8 multiplier)
	{
		uint8_t byte1 = *((const uint8_t*)dwAddress + 1);

		// int fromReg = byte1 & 7;
		// int intoReg = (byte1 >> 3) & 7;

		uint8_t newData[7];

		newData[0] = 0x6B;
		newData[1] = byte1;
		newData[2] = multiplier;

		newData[3] = 0x90;
		newData[4] = 0x90;
		newData[5] = 0x90;
		newData[6] = 0x90;

		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchMemoryData(dwAddress, newData, sizeof(newData));
		CPatch::LeaveThisLevel();
	}
}

// Patches world sectors
void MapLimits::PatchWorldSectors_GTA_IV_1_0_7_0()
{
	using namespace Game_GTAIV;

	if (CPatch::IsDebugModeActive())
	{
		this->ms_worldMapSize = 6000;
		this->ms_worldSectorSize = 50;
		this->ms_worldLODsectorSize = 200;
	}

	if (!this->PatchWorldSectors_DoInitialisingWork())
		return;

	uint32_t* Class_1136170_MemberOffsetArray = CWorld__ms_class_1136170.gta_iv->MemberOffsetArray;

	// Allocate memory
	#if TRUE
	// if(!CPatch::IsDebugModeActive())
	{
		if (iNumberOfWorldSectorsPerDimension > 120)
		{
			CWorld__ms_aSectors.gta_iv = new CSector[iTotalNumberOfWorldSectors];
			memset(
				CWorld__ms_aSectors.gta_iv,
				NULL,
				iTotalNumberOfWorldSectors * sizeof(CSector));
			CWorld__ms_aSectors.bIsAllocated.Set(true);

			CWorld__ms_aSectorObjectCount.ptr = new uint8_t[iTotalNumberOfWorldSectors];
			memset(CWorld__ms_aSectorObjectCount.ptr,
				NULL,
				iTotalNumberOfWorldSectors
			);
			CWorld__ms_aSectorObjectCount.bIsAllocated.Set(true);

			CWorld__ms_aSectorFlags.ptr = new uint16_t[iTotalNumberOfWorldSectors];
			memset(CWorld__ms_aSectorFlags.ptr,
				NULL,
				iTotalNumberOfWorldSectors * sizeof(uint16_t)
			);
			CWorld__ms_aSectorFlags.bIsAllocated.Set(true);

			CWorld__ms_class_1136170.gta_iv = (CClass_1136170*)new char[Class_1136170_MemberOffsetArray[Offset_class_1136170__endOfStructure]];
			memset(
				CWorld__ms_class_1136170.gta_iv,
				NULL,
				Class_1136170_MemberOffsetArray[Offset_class_1136170__endOfStructure]
			);
			CWorld__ms_class_1136170.bIsAllocated.Set(true);
		}

		if (iNumberOfWorldRepeatSectorsPerDimension > 16)
		{
			CWorld__ms_aRepeatSectors.gta_iv = new CRepeatSector[iTotalNumberOfWorldRepeatSectors];
			memset(
				CWorld__ms_aRepeatSectors.gta_iv,
				NULL,
				iTotalNumberOfWorldRepeatSectors * sizeof(CRepeatSector)
			);
			CWorld__ms_aRepeatSectors.bIsAllocated.Set(true);
		}

		if (iNumberOfWorldLODsectorsPerDimension > 30)
		{
			MapLimits::CWorld__ms_aLodPtrLists.gta_iv = new void*[iTotalNumberOfWorldLODsectors];
			memset(
				MapLimits::CWorld__ms_aLodPtrLists.gta_iv,
				NULL,
				iTotalNumberOfWorldLODsectors * sizeof(void*)
			);
			CWorld__ms_aLodPtrLists.bIsAllocated.Set(true);
		}
	}
	#endif

	// Patch coordinates
	#if TRUE
	{
		CPatch::EnterNewLevelAndDisableDebugState();

		// float 0xEBE168, -3000.0
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x491427 + 4), &fWorldMapMinCoord);	// movss   xmm1, ds:flt_EBE168	; sub_4913A0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x87074A + 4), &fWorldMapMinCoord);	// movss   xmm4, ds:flt_EBE168	; sub_870490
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8BB539 + 4), &fWorldMapMinCoord);	// movss   xmm1, ds:flt_EBE168	; sub_8BB4B0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8BE5E9 + 4), &fWorldMapMinCoord);	// movss   xmm1, ds:flt_EBE168	; sub_8BE200
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8BE605 + 4), &fWorldMapMinCoord);	// movss   xmm0, ds:flt_EBE168	; sub_8BE200
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x93CDD0 + 4), &fWorldMapMinCoord);	// movss   xmm0, ds:flt_EBE168	; sub_93CC50
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x93CE00 + 4), &fWorldMapMinCoord);	// movss   xmm1, ds:flt_EBE168	; sub_93CC50

			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9704E7 + 4), &fWorldMapMinCoord);	// movss   xmm0, ds:flt_EBE168	; sub_9704C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E9E20 + 4), &fWorldMapMinCoord);	// movss   xmm2, ds:flt_EBE168	; sub_9E9E10
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA6CB + 4), &fWorldMapMinCoord);	// movss   xmm2, ds:flt_EBE168	; _ZN7CEntity3AddERK5CRect
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA73C9B + 4), &fWorldMapMinCoord);	// movss   xmm0, ds:flt_EBE168	; sub_A73BE0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB27317 + 4), &fWorldMapMinCoord);	// movss   xmm0, ds:flt_EBE168	; sub_B272F0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB53846 + 4), &fWorldMapMinCoord);	// movss   xmm0, ds:flt_EBE168	; sub_B53830
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB68866 + 2), &fWorldMapMinCoord);	// fld     ds:flt_EBE168	; sub_B68850
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBE60F4 + 4), &fWorldMapMinCoord);	// mulss   xmm0, ds:flt_EBE168	; sub_BE60D0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xC0A227 + 4), &fWorldMapMinCoord);	// movss   xmm0, ds:flt_EBE168	; sub_C0A200
		}
		#endif

		// float 0xEBE164, 3000.0
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x491432 + 4), &fWorldMapMaxCoord);	// movss   xmm2, ds:flt_EBE164	; sub_4913A0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x870774 + 4), &fWorldMapMaxCoord);	// movss   xmm2, ds:flt_EBE164	; sub_870490
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8BB564 + 4), &fWorldMapMaxCoord);	// movss   xmm3, ds:flt_EBE164	; sub_8BB4B0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8BE5F3 + 4), &fWorldMapMaxCoord);	// movss   xmm1, ds:flt_EBE164	; sub_8BE200
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8BE60F + 4), &fWorldMapMaxCoord);	// movss   xmm0, ds:flt_EBE164	; sub_8BE200

			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x93DDC7 + 4), &fWorldMapMaxCoord);	// mulss   xmm2, ds:flt_EBE164	; sub_93D7C0

			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x970501 + 4), &fWorldMapMaxCoord);	// movss   xmm0, ds:flt_EBE164	; CreatePhysicsStore
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E9E56 + 4), &fWorldMapMaxCoord);	// movss   xmm5, ds:flt_EBE164	; sub_9E9E10
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA6FD + 4), &fWorldMapMaxCoord);	// movss   xmm5, ds:flt_EBE164	; _ZN7CEntity3AddERK5CRect
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA73C75 + 4), &fWorldMapMaxCoord);	// movss   xmm0, ds:flt_EBE164	; sub_A73BE0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB27331 + 4), &fWorldMapMaxCoord);	// movss   xmm0, ds:flt_EBE164	; CreateIPLstore
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB53860 + 4), &fWorldMapMaxCoord);	// movss   xmm0, ds:flt_EBE164	; sub_B53830
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB68850 + 2), &fWorldMapMaxCoord);	// fld     ds:flt_EBE164	; sub_B68850
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xC0A241 + 4), &fWorldMapMaxCoord);	// movss   xmm0, ds:flt_EBE164	; sub_C0A200
		}
		#endif

		// float 0xD83C7C, 2999.0
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E9E61 + 4), &fWorldMapMaxCoordMinusOne);	// movss   xmm6, ds:flt_D83C7C	; _ZN7CEntity3AddERK5CRect
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA708 + 4), &fWorldMapMaxCoordMinusOne);	// movss   xmm6, ds:flt_D83C7C	; _ZN7CEntity6RemoveEv
		}
		#endif

		CPatch::LeaveThisLevel();
	}
	#endif

	// debug
	#if FALSE
	{
		/*
		CPatch::PatchFloat(g_mCalc.GetCurrentVAbyPreferedVA(0xEBE164), fWorldMapMaxCoord);
		CPatch::PatchFloat(g_mCalc.GetCurrentVAbyPreferedVA(0xEBE168), fWorldMapMinCoord);
		CPatch::PatchFloat(g_mCalc.GetCurrentVAbyPreferedVA(0xD83C7C), fWorldMapMaxCoordMinusOne);
		*/


		// World sectors
		#if FALSE
		{
			CPatch::PatchFloat(g_mCalc.GetCurrentVAbyPreferedVA(0xD96D20), fWorldSectorSize);
			CPatch::PatchFloat(g_mCalc.GetCurrentVAbyPreferedVA(0xD529C4), fWorldSectorSizeInversed);
			CPatch::PatchFloat(g_mCalc.GetCurrentVAbyPreferedVA(0xDCE040), fNumberOfWorldSectorsPerDimensionHalf);
		}
		#endif

		// World LOD sectors
		#if TRUE
		{
			CPatch::PatchFloat(g_mCalc.GetCurrentVAbyPreferedVA(0xEBE284), fWorldLODsectorSizeInversed);
			CPatch::PatchFloat(g_mCalc.GetCurrentVAbyPreferedVA(0xD50960), fNumberOfWorldLODsectorsPerDimensionHalf);
		}
		#endif

		// 3000
		#if FALSE
		{
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x45ABB9 + 6), iWorldMapMaxCoord);	// mov     dword ptr [ecx+210h], 0BB8h	; sub_45AB70
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x46B18F + 2), iWorldMapMaxCoord);	// add     ecx, 0BB8h	; sub_46AD90
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x46B8CA + 2), iWorldMapMaxCoord);	// add     ecx, 0BB8h	; sub_46B8B0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x47714E + 2), iWorldMapMaxCoord);	// cmp     ecx, 0BB8h	; sub_477110
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x48A941 + 3), iWorldMapMaxCoord);	// mov     dword ptr [esi+4], 0BB8h	; sub_48A900
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x48CD88 + 1), iWorldMapMaxCoord);	// cmp     eax, 0BB8h	; sub_48CD80
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x491B29 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_491A60
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x491B3F + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_491A60
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x49448F + 2), iWorldMapMaxCoord);	// add     ecx, 0BB8h	; sub_494460
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x4944A5 + 2), iWorldMapMaxCoord);	// add     edx, 0BB8h	; sub_494460
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x49699F + 6), iWorldMapMaxCoord);	// mov     dword_1980320, 0BB8h	; sub_496880
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x4A3D74 + 1), iWorldMapMaxCoord);	// cmp     eax, 0BB8h	; sub_4A3D60
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x4EBF65 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_4EBDE0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x4FE78A + 2), iWorldMapMaxCoord);	// cmp     edx, 0BB8h	; sub_4FE750
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x70DEF2 + 2), iWorldMapMaxCoord);	// mov     [esi+0BB8h], eax	; sub_70DE60
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x70E0A2 + 2), iWorldMapMaxCoord);	// mov     eax, [esi+0BB8h]	; sub_70E040
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x70EA85 + 2), iWorldMapMaxCoord);	// cmp     [edx+0BB8h], esi	; sub_70EA80
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x70EAA3 + 2), iWorldMapMaxCoord);	// cmp     esi, [edx+0BB8h]	; sub_70EA80
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x7976ED + 3), iWorldMapMaxCoord);	// mov     dword ptr [eax+0Ch], 0BB8h	; sub_7976D0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x7977E7 + 1), iWorldMapMaxCoord);	// cmp     eax, 0BB8h	; sub_7977B0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x7A2CB8 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_7A2490
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x7A2CFF + 1), iWorldMapMaxCoord);	// cmp     eax, 0BB8h	; sub_7A2490
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x7A6FC6 + 4), iWorldMapMaxCoord);	// mov     [esp+0B58h+var_AEC], 0BB8h	; sub_7A6CC0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x7B8D34 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_7B7F70
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x7B9E00 + 4), iWorldMapMaxCoord);	// mov     [esp+17Ch+var_144], 0BB8h	; sub_7B9C50
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x81717D + 2), iWorldMapMaxCoord);	// add     edx, 0BB8h	; sub_816EE0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x82C3E5 + 2), iWorldMapMaxCoord);	// cmp     ecx, 0BB8h	; sub_82C320
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x82C3F6 + 2), iWorldMapMaxCoord);	// cmp     ecx, 0BB8h	; sub_82C320
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x82C44C + 2), iWorldMapMaxCoord);	// cmp     dword ptr [ecx], 0BB8h	; sub_82C440
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x84F1C1 + 2), iWorldMapMaxCoord);	// lea     edx, [edi+0BB8h]	; sub_84F0A0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x84F1D1 + 6), iWorldMapMaxCoord);	// mov     dword_11DE7FC, 0BB8h	; sub_84F0A0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x87085A + 2), iWorldMapMaxCoord);	// add     edx, 0BB8h	; sub_870490
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x8776F1 + 4), iWorldMapMaxCoord);	// mov     [esp+30h+var_14], 0BB8h	; sub_877300
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x879A37 + 1), iWorldMapMaxCoord);	// cmp     eax, 0BB8h	; sub_8795B0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x879AA3 + 1), iWorldMapMaxCoord);	// cmp     eax, 0BB8h	; sub_8795B0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x88C52F + 1), iWorldMapMaxCoord);	// mov     eax, 0BB8h	; sub_88C490
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x93EFE4 + 1), iWorldMapMaxCoord);	// mov     edi, 3000	; sub_93EFA0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x93F016 + 1), iWorldMapMaxCoord);	// mov     esi, 0BB8h	; sub_93EFA0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x94D338 + 1), iWorldMapMaxCoord);	// cmp     eax, 0BB8h	; sub_94CE70
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x96C8F7 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_96C750
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x9BC082 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_9BBFE0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x9D96F3 + 4), iWorldMapMaxCoord);	// mov     [esp+30h+var_18], 0BB8h	; sub_9D9680
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x9D9B12 + 2), iWorldMapMaxCoord);	// add     ecx, 0BB8h	; sub_9D98C0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x9ED9C5 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_9ED9B0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA0533C + 1), iWorldMapMaxCoord);	// add     eax, 0BB8h	; sub_A05010
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA0577E + 1), iWorldMapMaxCoord);	// add     eax, 0BB8h	; sub_A056A0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA058AA + 1), iWorldMapMaxCoord);	// add     eax, 0BB8h	; sub_A056A0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA1953B + 1), iWorldMapMaxCoord);	// mov     ebx, 0BB8h	; sub_A194F0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA2381A + 1), iWorldMapMaxCoord);	// mov     edx, 0BB8h	; sub_A23670
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA25BAD + 6), iWorldMapMaxCoord);	// mov     dword ptr [edi+0E8h], 0BB8h	; sub_A25650
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA32FEF + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_A32110
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA35F19 + 1), iWorldMapMaxCoord);	// cmp     eax, 0BB8h	; sub_A35EE0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA42B33 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_A42B00
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA42CD3 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_A42CA0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA52291 + 1), iWorldMapMaxCoord);	// mov     ecx, 0BB8h	; sub_A52110
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA546CA + 3), iWorldMapMaxCoord);	// mov     dword ptr [esi+14h], 0BB8h	; sub_A54560
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA54DC2 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_A54770
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA69537 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_A69390
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA699A0 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_A69930
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xA6CCC4 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_A6CAF0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xAA116C + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_AA0DA0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xAB8AFD + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_AB8AA0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xAB8B04 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_AB8AA0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xAB8EAA + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_AB8DD0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xABDC77 + 1), iWorldMapMaxCoord);	// add     eax, 0BB8h	; sub_ABDC50
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xAC001F + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_ABFE20
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xAC609A + 2), iWorldMapMaxCoord);	// cmp     ecx, 0BB8h	; sub_AC5FA0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xAC60C4 + 2), iWorldMapMaxCoord);	// cmp     edx, 0BB8h	; sub_AC5FA0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xAD19E6 + 1), iWorldMapMaxCoord);	// add     eax, 0BB8h	; sub_AD1870
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xAD44AD + 4), iWorldMapMaxCoord);	// mov     [esp+88h+var_40], 0BB8h	; sub_AD4280
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xAE5149 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_AE4F00
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xAE5A69 + 2), iWorldMapMaxCoord);	// mov     [esi+0BB8h], eax	; sub_AE57D0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xAF20BD + 2), iWorldMapMaxCoord);	// add     edx, 0BB8h	; sub_AF1640
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xAF4B85 + 1), iWorldMapMaxCoord);	// add     eax, 0BB8h	; sub_AF4050
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xB07FA9 + 3), iWorldMapMaxCoord);	// mov     dword ptr [esi+0Ch], 0BB8h	; sub_B07F90
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xBC08A8 + 4), iWorldMapMaxCoord);	// movss   xmm0, dword ptr [edi+0BB8h]	; sub_BC0880
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xBC0AE9 + 4), iWorldMapMaxCoord);	// movss   dword ptr [esi+0BB8h], xmm0	; sub_BC09A0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xBC0B50 + 4), iWorldMapMaxCoord);	// movss   dword ptr [esi+0BB8h], xmm0	; sub_BC0B00
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xBC111B + 4), iWorldMapMaxCoord);	// movss   xmm0, dword ptr [esi+0BB8h]	; sub_BC10F0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xBE0AAD + 1), iWorldMapMaxCoord);	// mov     esi, 0BB8h	; sub_BE0930
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xBE1A78 + 2), iWorldMapMaxCoord);	// lea     ecx, [edx+0BB8h]	; sub_BE1A60
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xBE6126 + 1), iWorldMapMaxCoord);	// mov     eax, 0BB8h	; sub_BE60D0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xC3D63D + 2), iWorldMapMaxCoord);	// cmp     edx, 0BB8h	; sub_C3D630
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xC3F37A + 1), iWorldMapMaxCoord);	// mov     eax, 0BB8h	; sub_C3F370
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xC5F8E1 + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_C5F7B0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xC61D1D + 1), iWorldMapMaxCoord);	// push    0BB8h	; sub_C61BD0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xC64D51 + 1), iWorldMapMaxCoord);	// add     eax, 0BB8h	; sub_C64B70
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xC67582 + 1), iWorldMapMaxCoord);	// mov     edi, 0BB8h	; sub_C66FB0
			CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0xC7ED49 + 1), iWorldMapMaxCoord);	// add     eax, 0BB8h	; sub_C7EC80
		}
		#endif
	}
	#endif

	// Nav meshes
	#if FALSE
	{
		// CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x938F99 + 4), &fWorldSectorSizeInversed);	// movss   xmm6, ds:fWorldSectorSizeInversed	; sub_938F90
		// CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x938FA1 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// movss   xmm7, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_938F90
		// CCodeMover::FixOnAddressRel(0x93AD20, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x00", 0x93AD25);	// line 52, 0x93AC60 - readNavDat : mov     eax, 120

		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x93CD53 + 4), &fWorldMapMaxCoord);	// movss   xmm5, ds:flt_EBE164	; sub_93CC50
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x93CE3F + 4), &fWorldMapMaxCoord);	// movss   xmm5, ds:flt_EBE164	; sub_93CC50

		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA5A7A + 4), &fWorldSectorSizeInversed);	// mulss   xmm1, ds:fWorldSectorSizeInversed	; sub_AA59D0
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA5AFA + 4), &fWorldSectorSizeInversed);	// mulss   xmm3, ds:fWorldSectorSizeInversed	; sub_AA59D0
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA5B66 + 4), &fWorldSectorSizeInversed);	// mulss   xmm1, ds:fWorldSectorSizeInversed	; sub_AA59D0
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA5BDE + 4), &fWorldSectorSizeInversed);	// mulss   xmm3, ds:fWorldSectorSizeInversed	; sub_AA59D0

		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA5A82 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm1, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_AA59D0
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA5B02 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm3, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_AA59D0
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA5B6E + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm1, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_AA59D0
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA5BE6 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm3, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_AA59D0

		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA5F8E + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_AA5EA0
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA6009 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_AA5EA0
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA607D + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_AA5EA0
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA60F8 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_AA5EA0

		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA5F86 + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_AA5EA0
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA6001 + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_AA5EA0
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA6075 + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_AA5EA0
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAA60F0 + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_AA5EA0
	}
	#endif

	/* search for:
		8B F0 C1 E6 04 2B F0
			mov     esi, eax
			shl     esi, 4
			sub     esi, eax

		8B D0 C1 E2 04 2B D0
			mov     edx, eax
			shl     edx, 4
			sub     edx, eax

		8B F1 C1 E6 04 2B F1
			mov     esi, ecx
			shl     esi, 4
			sub     esi, ecx

		8B D1 C1 E2 04 2B D1
			mov     edx, ecx
			shl     edx, 4
			sub     edx, ecx

		8B F8 C1 E7 04 2B F8
			mov     edi, eax
			shl     edi, 4
			sub     edi, eax

	*/

	// World sectors
	#if TRUE
	{

		// CWorld::ms_aSectors
		#if TRUE
		{
			// Patch pointers to CWorld::ms_aSectors
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8177D0 + 1), CWorld__ms_aSectors.gta_iv);	// mov     ecx, offset _ZN6CWorld11ms_aSectorsE; CWorld::ms_aSectors	; _ZN6CWorld14ClearScanCodesEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x817802 + 2), CWorld__ms_aSectors.gta_iv + iTotalNumberOfWorldSectors);	// cmp     ecx, offset dword_11D2868	; _ZN6CWorld14ClearScanCodesEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x818E40 + 3), CWorld__ms_aSectors.gta_iv);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.field_0[ecx*4]; CWorld::ms_aSectors	; sub_818C40
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81B133 + 1), CWorld__ms_aSectors.gta_iv);	// mov     ebp, offset _ZN6CWorld11ms_aSectorsE; CWorld::ms_aSectors	; _ZN6CWorld8ShutDownEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81B1A5 + 2), CWorld__ms_aSectors.gta_iv + iTotalNumberOfWorldSectors);	// cmp     ebp, offset dword_11D2868	; _ZN6CWorld8ShutDownEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81B6D0 + 3), CWorld__ms_aSectors.gta_iv);	// lea     edi, _ZN6CWorld11ms_aSectorsE.field_0[edi*4]; CWorld::ms_aSectors	; sub_81B4A0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81BDC4 + 3), CWorld__ms_aSectors.gta_iv);	// lea     ebx, _ZN6CWorld11ms_aSectorsE.field_0[ebx*4]; CWorld::ms_aSectors	; sub_81BB90
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C208 + 3), CWorld__ms_aSectors.gta_iv);	// lea     edi, _ZN6CWorld11ms_aSectorsE.field_0[edi*4]; CWorld::ms_aSectors	; sub_81BFD0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C606 + 3), CWorld__ms_aSectors.gta_iv);	// lea     esi, _ZN6CWorld11ms_aSectorsE.field_0[esi*4]; CWorld::ms_aSectors	; sub_81C3D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8FCA04 + 3), CWorld__ms_aSectors.gta_iv);	// lea     ebx, _ZN6CWorld11ms_aSectorsE.field_0[ebx*4]; CWorld::ms_aSectors	; sub_8FC7D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E1A66 + 3), &CWorld__ms_aSectors.gta_iv->dummyList);	// lea     esi, _ZN6CWorld11ms_aSectorsE.dummyList[esi*4]	; sub_9E1960
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E2098 + 3), &CWorld__ms_aSectors.gta_iv->dummyList);	// lea     edi, _ZN6CWorld11ms_aSectorsE.dummyList[edi*4]	; sub_9E1F70
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA245 + 3), CWorld__ms_aSectors.gta_iv);	// lea     esi, _ZN6CWorld11ms_aSectorsE.field_0[esi*4]; CWorld::ms_aSectors	; _ZN7CEntity3AddERK5CRect
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA304 + 3), &CWorld__ms_aSectors.gta_iv->dummyList);	// lea     esi, _ZN6CWorld11ms_aSectorsE.dummyList[esi*4]	; _ZN7CEntity3AddERK5CRect
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA346 + 3), &CWorld__ms_aSectors.gta_iv->dummyList);	// lea     esi, _ZN6CWorld11ms_aSectorsE.dummyList[esi*4]	; _ZN7CEntity3AddERK5CRect
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA9B8 + 3), CWorld__ms_aSectors.gta_iv);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.field_0[ecx*4]; CWorld::ms_aSectors	; _ZN7CEntity6RemoveEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EAA5C + 3), &CWorld__ms_aSectors.gta_iv->dummyList);	// lea     eax, _ZN6CWorld11ms_aSectorsE.dummyList[eax*4]	; _ZN7CEntity6RemoveEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EAA9E + 3), &CWorld__ms_aSectors.gta_iv->dummyList);	// lea     eax, _ZN6CWorld11ms_aSectorsE.dummyList[eax*4]	; _ZN7CEntity6RemoveEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9FA312 + 4), &CWorld__ms_aSectors.gta_iv->lowestID);	// movsx   esi, _ZN6CWorld11ms_aSectorsE.lowestID[eax*4]	; sub_9FA130
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9FA31C + 3), CWorld__ms_aSectors.gta_iv);	// lea     eax, _ZN6CWorld11ms_aSectorsE.field_0[eax*4]; CWorld::ms_aSectors	; sub_9FA130
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA73B59 + 3), CWorld__ms_aSectors.gta_iv);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.field_0[eax*4]; CWorld::ms_aSectors	; sub_A739C0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB259AF + 3), CWorld__ms_aSectors.gta_iv);	// lea     ebx, _ZN6CWorld11ms_aSectorsE.field_0[ebx*4]; CWorld::ms_aSectors	; sub_B257E0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB2B95F + 3), CWorld__ms_aSectors.gta_iv);	// lea     eax, _ZN6CWorld11ms_aSectorsE.field_0[edx*4]; CWorld::ms_aSectors	; sub_B2B660
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE3AB + 3), CWorld__ms_aSectors.gta_iv);	// lea     eax, _ZN6CWorld11ms_aSectorsE.field_0[eax*4]; CWorld::ms_aSectors	; sub_BBE1A0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE5F9 + 4), &CWorld__ms_aSectors.gta_iv->lowestID);	// movsx   eax, _ZN6CWorld11ms_aSectorsE.lowestID[ecx*4]	; sub_BBE440
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE603 + 3), CWorld__ms_aSectors.gta_iv);	// lea     ecx, _ZN6CWorld11ms_aSectorsE.field_0[ecx*4]; CWorld::ms_aSectors	; sub_BBE440
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD3D270 + 1), CWorld__ms_aSectors.gta_iv);	// mov     eax, offset _ZN6CWorld11ms_aSectorsE; CWorld::ms_aSectors	; sub_D3D270
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD4A532 + 1), CWorld__ms_aSectors.gta_iv + iTotalNumberOfWorldSectors);	// mov     esi, offset dword_11D2868	; sub_D4A530
			}
			#endif

			// Patch count of world sectors minus one (14399)
			#if TRUE
			{
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD3D275 + 1), iTotalNumberOfWorldSectors - 1);	// mov     ecx, 383Fh	; sub_D3D270
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD4A537 + 1), iTotalNumberOfWorldSectors - 1);	// mov     edi, 383Fh	; sub_D4A530
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD3D275 + 1), iTotalNumberOfWorldSectors - 1);	// mov     ecx, 383Fh	; sub_D3D270
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD4A537 + 1), iTotalNumberOfWorldSectors - 1);	// mov     edi, 383Fh	; sub_D4A530
			}
			#endif
		}
		#endif

		// CWorld::ms_aSectorsObjectCount
		#if TRUE
		{
			// Patch pointers to CWorld::ms_aSectorsObjectCount
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81731A + 1), CWorld__ms_aSectorObjectCount.ptr);	// push    offset CWorld__ms_aSectorsObjectCount	; sub_817310
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x818137 + 3), CWorld__ms_aSectorObjectCount.ptr);	// movzx   edx, CWorld__ms_aSectorsObjectCount[ecx]	; sub_818110
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x818142 + 2), CWorld__ms_aSectorObjectCount.ptr);	// mov     CWorld__ms_aSectorsObjectCount[ecx], al	; sub_818110
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x818169 + 4), CWorld__ms_aSectorObjectCount.ptr);	// movzx   eax, CWorld__ms_aSectorsObjectCount[ecx+edx*8]	; sub_818150
			}

			#endif

			// Patch count of world sectors (14440)
			#if TRUE
			{
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x817313 + 1), iTotalNumberOfWorldSectors);	// push    3840h	; sub_817310
			}
			#endif
		}
		#endif

		// CWorld::ms_aSectorFlags
		#if TRUE
		{
			// Patch pointers to CWorld::ms_aSectorFlags
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAD9A6C + 4), CWorld__ms_aSectorFlags.ptr);	// movsx   ecx, byte ptr CWorld__ms_aSectorFlags.ptr[eax*2]	; sub_AD9A50
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE7E7 + 4), CWorld__ms_aSectorFlags.ptr);	// movsx   edx, byte ptr CWorld__ms_aSectorFlags.ptr[eax*2]	; sub_ADE7D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE7EF + 3), CWorld__ms_aSectorFlags.ptr);	// lea     ecx, CWorld__ms_aSectorFlags.ptr[eax*2]	; sub_ADE7D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE843 + 3), (char*)CWorld__ms_aSectorFlags.ptr + 1);	// mov     cl, byte ptr (CWorld__ms_aSectorFlags.ptr+1)[eax*2]	; sub_ADE7D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE854 + 3), (char*)CWorld__ms_aSectorFlags.ptr + 1);	// mov     al, byte ptr (CWorld__ms_aSectorFlags.ptr+1)[ecx*2]	; sub_ADE7D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE867 + 3), (char*)CWorld__ms_aSectorFlags.ptr + 1);	// mov     byte ptr (CWorld__ms_aSectorFlags.ptr+1)[ecx*2], dl	; sub_ADE7D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE892 + 3), (char*)CWorld__ms_aSectorFlags.ptr + 1);	// test    byte ptr (CWorld__ms_aSectorFlags.ptr+1)[eax*2], 7Fh	; sub_ADE7D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE89E + 3), (char*)CWorld__ms_aSectorFlags.ptr + 1);	// mov     al, byte ptr (CWorld__ms_aSectorFlags.ptr+1)[ecx*2]	; sub_ADE7D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE8B1 + 3), (char*)CWorld__ms_aSectorFlags.ptr + 1);	// mov     byte ptr (CWorld__ms_aSectorFlags.ptr+1)[ecx*2], dl	; sub_ADE7D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE91C + 3), (char*)CWorld__ms_aSectorFlags.ptr + 1);	// mov     cl, byte ptr (CWorld__ms_aSectorFlags.ptr+1)[esi*2]	; sub_ADE8F0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE971 + 3), (char*)CWorld__ms_aSectorFlags.ptr + 1);	// mov     dl, byte ptr (CWorld__ms_aSectorFlags.ptr+1)[esi*2]	; sub_ADE8F0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE9B2 + 3), (char*)CWorld__ms_aSectorFlags.ptr + 1);	// test    byte ptr (CWorld__ms_aSectorFlags.ptr+1)[esi*2], 7Fh	; sub_ADE8F0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE9BC + 4), CWorld__ms_aSectorFlags.ptr);	// movsx   ecx, byte ptr CWorld__ms_aSectorFlags.ptr[esi*2]	; sub_ADE8F0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAE30C3 + 3), (char*)CWorld__ms_aSectorFlags.ptr + 1);	// or      byte ptr (CWorld__ms_aSectorFlags.ptr+1)[esi*2], 80h	; sub_AE2E20
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD439C1 + 1), (char*)CWorld__ms_aSectorFlags.ptr + 3);	// mov     eax, (offset CWorld__ms_aSectorFlags.ptr+3)	; sub_D439C0
			}
			#endif

			// Patch count of world sectors / 6, (2400)
			#if TRUE
			{
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD439C6 + 1), iTotalNumberOfWorldSectors / 6);	// mov     esi, 2400	; sub_D439C0
			}
			#endif
		}
		#endif

		// stru_1136170
		#if TRUE
		{
			// Patch references to stru_1136170
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7D7749 + 1), CWorld__ms_class_1136170.gta_iv);	// mov     ecx, offset stru_1136170; this	; sub_7D7700
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7D9871 + 1), CWorld__ms_class_1136170.gta_iv);	// mov     ecx, offset stru_1136170; this	; sub_7D9830
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7D98D7 + 1), CWorld__ms_class_1136170.gta_iv);	// mov     ecx, offset stru_1136170	; sub_7D98B0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7D98F3 + 1), CWorld__ms_class_1136170.gta_iv);	// mov     ecx, offset stru_1136170	; sub_7D98B0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7E0DEA + 2), CWorld__ms_class_1136170.gta_iv->GetPointerToMember(Offset_class_1136170__field_E4D0));	// mov     ebp, stru_1136170.field_E4D0	; sub_7E0C70
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7E0DF0 + 2), CWorld__ms_class_1136170.gta_iv->GetPointerToMember(Offset_class_1136170__field_E4D4));	// cmp     ebp, stru_1136170.field_E4D4	; sub_7E0C70
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7E0E02 + 2), CWorld__ms_class_1136170.gta_iv->GetPointerToMember(Offset_class_1136170__field_4));	// sub     eax, stru_1136170.field_4	; sub_7E0C70
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7E0E08 + 3), CWorld__ms_class_1136170.gta_iv->GetPointerToMember(Offset_class_1136170__field_E108));	// mov     esi, stru_1136170.field_E108[eax*4]	; sub_7E0C70
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7E0E0F + 3), CWorld__ms_class_1136170.gta_iv->GetPointerToMember(Offset_class_1136170__field_E2E8));	// mov     edi, stru_1136170.field_E2E8[eax*4]	; sub_7E0C70
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7E0E47 + 2), CWorld__ms_class_1136170.gta_iv->GetPointerToMember(Offset_class_1136170__field_E4D4));	// cmp     ebp, stru_1136170.field_E4D4	; sub_7E0C70
			}
			#endif

			// Patch values
			#if TRUE
			{
				Address_7D7749 = g_mCalc.GetCurrentVAbyPreferedVA(0x7D7749);
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x7D773D), &patch_7D773D);
			}
			#endif

			// Patch class methods
			#if TRUE
			{
				// sub_7D6520
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D652B + 1), iTotalNumberOfWorldSectors * sizeof(__int32)); // push    0E100h
				CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0x7D6530 + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_8]);	// lea     edx, [esi+8]
				CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0x7D653E + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_4]);	// mov     [esi+4], ecx
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D6546 + 1), iNumberOfWorldSectorsPerDimension * sizeof(__int32)); // push    1E0h            ; num
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D654B + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E108]);	// lea     eax, [esi+class_1136170.field_E108]
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D6559 + 1), iNumberOfWorldSectorsPerDimension * sizeof(__int32)); // push    1E0h            ; num
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D655E + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E2E8]);	// lea     ecx, [esi+class_1136170.field_E2E8]

				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D657C + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4C8]);	// mov     [esi+class_1136170.field_E4C8], ecx
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D6582 + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4CC]);	// mov     [esi+class_1136170.field_E4CC], eax
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D6588 + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4D0]);	// mov     [esi+class_1136170.field_E4D0], ecx
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D658E + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4D4]);	// mov     [esi+class_1136170.field_E4D4], eax

				// sub_7D9450
				CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0x7D9466 + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_4]);	// mov     edi, [ecx+class_1136170.field_4]
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D948E + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4D4]);	// mov     edi, [ecx+class_1136170.field_E4D4]
				CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0x7D9494 + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_4]);	// mov     ebp, [ecx+class_1136170.field_4]
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D9497 + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4D0]); // mov     ebx, [ecx+class_1136170.field_E4D0]
				CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0x7D94CD + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_4]);	// mov     eax, [ecx+class_1136170.field_4]
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D9510 + 3), iNumberOfWorldSectorsPerDimension * sizeof(__int32));	// prefetcht0 byte ptr [ecx+1E0h]
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D9517 + 2), iNumberOfWorldSectorsPerDimension * sizeof(__int32));	// lea     edi, [ecx+1E0h]

				// sub_7D9370
				CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0x7D937A + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_4]);	// sub     edx, [ecx+class_1136170.field_4]
				CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0x7D93B1 + 3), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_8]);	// or      [ecx+esi*4+class_1136170.field_8], ebx
				CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0x7D93B7 + 3), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_8]);	// lea     esi, [ecx+esi*4+class_1136170.field_8]
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D93BB + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4C8]);	// mov     esi, [ecx+class_1136170.field_E4C8]
				CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0x7D93C4 + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_4]);	// add     edx, [ecx+class_1136170.field_4]

				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D93CD + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4C8]);	// mov     [ecx+class_1136170.field_E4C8], esi
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D93D3 + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4CC]); // mov     esi, [ecx + class_1136170.field_E4CC]);	// mov     esi, [ecx+class_1136170.field_E4CC]

				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D93DF + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4CC]); // mov     esi, [ecx + class_1136170.field_E4CC])
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D93E5 + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4D0]);	// mov     esi, [ecx+class_1136170.field_E4D0]

				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D93F1 + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4D0]); // mov     [ecx+class_1136170.field_E4D0], esi
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D93F7 + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4D4]);	// mov     esi, [ecx+class_1136170.field_E4D4]

				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D9403 + 2), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E4D4]); // mov     [ecx+class_1136170.field_E4D4], edx
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D9409 + 3), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E108]);	// mov     edx, [ecx+edi*4+class_1136170.field_E108]

				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D9416 + 3), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E108]);	// mov     [ecx+edi*4+class_1136170.field_E108], edx
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D941D + 3), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E2E8]);	// mov     edx, [ecx+edi*4+class_1136170.field_E2E8]

				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D9428 + 3), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E2E8]);	// mov     [ecx+edi*4+class_1136170.field_E2E8], eax
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D9435 + 3), Class_1136170_MemberOffsetArray[Offset_class_1136170__field_E2E8]);	// mov     [ecx+edi*4+class_1136170.field_E2E8], eax
			}
			#endif
		}
		#endif

		// Patch values 119 & 120
		#if TRUE
		{
			// 119
			#if TRUE
			{
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x7D9486 + 4), iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+10h+arg_0], 77h ; 'w'	; sub_7D9450
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xAE3024 + 4), iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+28h+arg_8], 77h ; 'w'	; sub_AE2E20
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xB2B930 + 4), iNumberOfWorldSectorsPerDimension - 1);	// mov     [esp+34h+arg_20], 77h ; 'w'	; sub_B2B660
			}
			#endif
		}
		#endif

		// float 0xD96D18, 120.0
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();

		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE762 + 4), &fNumberOfWorldSectorsPerDimension);	// movss   xmm3, ds:flt_D96D18	; sub_ADE6C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE79B + 2), &fNumberOfWorldSectorsPerDimension);	// fmul    ds:flt_D96D18	; sub_ADE6C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE7B7 + 2), &fNumberOfWorldSectorsPerDimension);	// fmul    ds:flt_D96D18	; sub_ADE6C0
		}

		CPatch::LeaveThisLevel();
		#endif

		// float 0xD96D20, 50.0
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();

		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE945 + 2), &fWorldSectorSize);	// fld     ds:flt_D96D20	; sub_ADE8F0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAE3AFA + 2), &fWorldSectorSize);	// fld     ds:flt_D96D20	; sub_AE3900
		}

		CPatch::LeaveThisLevel();
		#endif

		// float 0xDCE040, 60.0
		#if TRUE
		{
			CPatch::EnterNewLevelAndDisableDebugState();

			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7D7722 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// movss   xmm2, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_7D7700
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DDDDA + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// movss   xmm1, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_7DC050
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DF16A + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// movss   xmm7, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_7DE200
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DF225 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// movss   xmm1, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_7DE200
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x818C4F + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// movss   xmm7, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_818C40
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81B4D5 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81B4A0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81B51F + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81B4A0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81B575 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81B4A0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81B5A7 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm2, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81B4A0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81BBD1 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81BB90
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81BBEB + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm3, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81BB90
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81BC07 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm4, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81BB90
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81BC5D + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm5, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81BB90
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C011 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81BFD0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C02B + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm3, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81BFD0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C047 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm4, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81BFD0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C09D + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm5, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81BFD0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C411 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81C3D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C42B + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm3, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81C3D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C447 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm4, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81C3D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C49D + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm5, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_81C3D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8B8E79 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// movss   xmm7, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_8B8E70
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8FC811 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_8FC7D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8FC82B + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm3, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_8FC7D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8FC847 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm4, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_8FC7D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8FC89D + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm5, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_8FC7D0					
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E00AE + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// movss   xmm7, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_9E0090
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E9FAA + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; _ZN7CEntity3AddERK5CRect
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E9FCA + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm4, ds:fNumberOfWorldSectorsPerDimensionHalf	; _ZN7CEntity3AddERK5CRect
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA005 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm3, ds:fNumberOfWorldSectorsPerDimensionHalf	; _ZN7CEntity3AddERK5CRect
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA054 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; _ZN7CEntity3AddERK5CRect
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA82A + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; _ZN7CEntity6RemoveEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA84D + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm3, ds:fNumberOfWorldSectorsPerDimensionHalf	; _ZN7CEntity6RemoveEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA896 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; _ZN7CEntity6RemoveEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA8A6 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm4, ds:fNumberOfWorldSectorsPerDimensionHalf	; _ZN7CEntity6RemoveEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9FA171 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_9FA130
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9FA189 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm2, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_9FA130
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9FA1D4 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_9FA130
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9FA1E9 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm3, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_9FA130
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA739F1 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_A739C0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA73A0A + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm2, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_A739C0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA73A54 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_A739C0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA73A6A + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm3, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_A739C0

				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE6D1 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// movss   xmm7, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_ADE6C0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE93A + 2), &fNumberOfWorldSectorsPerDimensionHalf);	// fld     ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_ADE8F0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAE3AE4 + 2), &fNumberOfWorldSectorsPerDimensionHalf);	// fld     ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_AE3900
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB257F5 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// movss   xmm7, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_B257E0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB2B6A8 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_B2B660
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB2B717 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm4, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_B2B660
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB2B76F + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm2, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_B2B660
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB2B7BD + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm5, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_B2B660
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB2B813 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm3, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_B2B660
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB2B86B + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm2, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_B2B660
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE218 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// movss   xmm6, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BBE1A0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE47D + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BBE440
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE4C7 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm2, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BBE440
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE519 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BBE440
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE54B + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm2, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BBE440
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBF5F0C + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BF5EA0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBF5F79 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm1, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BF5EA0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBF5FCD + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm2, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BF5EA0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBF602F + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm1, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BF5EA0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBF7C2B + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BF7B90
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBF7C92 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm1, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BF7B90
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBF7CE6 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm2, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BF7B90
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBF7D44 + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm1, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BF7B90
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBF82FB + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// addss   xmm0, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BF81E0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBF831E + 4), &fNumberOfWorldSectorsPerDimensionHalf);	// movss   xmm7, ds:fNumberOfWorldSectorsPerDimensionHalf	; sub_BF81E0
			}

			CPatch::LeaveThisLevel();
		}
		#endif

		// Patch pointers to inversed size of sector (0.02), flt_D529C4
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();

		{

			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7D7716 + 4), &fWorldSectorSizeInversed);	// movss   xmm1, ds:fWorldSectorSizeInversed	; sub_7D7700
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DDDD2 + 4), &fWorldSectorSizeInversed);	// movss   xmm0, ds:fWorldSectorSizeInversed	; sub_7DC050


			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DF162 + 4), &fWorldSectorSizeInversed);	// movss   xmm6, ds:fWorldSectorSizeInversed	; sub_7DE200
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DF21D + 4), &fWorldSectorSizeInversed);	// movss   xmm0, ds:fWorldSectorSizeInversed	; sub_7DE200
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x818C47 + 4), &fWorldSectorSizeInversed);	// movss   xmm6, ds:fWorldSectorSizeInversed	; sub_818C40



			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81B4A7 + 4), &fWorldSectorSizeInversed);	// movss   xmm7, ds:fWorldSectorSizeInversed	; sub_81B4A0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81B56D + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_81B4A0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81B59F + 4), &fWorldSectorSizeInversed);	// mulss   xmm2, ds:fWorldSectorSizeInversed	; sub_81B4A0



			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81BBC9 + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_81BB90
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81BBE3 + 4), &fWorldSectorSizeInversed);	// mulss   xmm3, ds:fWorldSectorSizeInversed	; sub_81BB90
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81BBFF + 4), &fWorldSectorSizeInversed);	// mulss   xmm4, ds:fWorldSectorSizeInversed	; sub_81BB90
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81BC55 + 4), &fWorldSectorSizeInversed);	// mulss   xmm5, ds:fWorldSectorSizeInversed	; sub_81BB90

			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C009 + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_81BFD0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C023 + 4), &fWorldSectorSizeInversed);	// mulss   xmm3, ds:fWorldSectorSizeInversed	; sub_81BFD0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C03F + 4), &fWorldSectorSizeInversed);	// mulss   xmm4, ds:fWorldSectorSizeInversed	; sub_81BFD0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C095 + 4), &fWorldSectorSizeInversed);	// mulss   xmm5, ds:fWorldSectorSizeInversed	; sub_81BFD0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C409 + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_81C3D0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C423 + 4), &fWorldSectorSizeInversed);	// mulss   xmm3, ds:fWorldSectorSizeInversed	; sub_81C3D0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C43F + 4), &fWorldSectorSizeInversed);	// mulss   xmm4, ds:fWorldSectorSizeInversed	; sub_81C3D0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81C495 + 4), &fWorldSectorSizeInversed);	// mulss   xmm5, ds:fWorldSectorSizeInversed	; sub_81C3D0


			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8B8E71 + 4), &fWorldSectorSizeInversed);	// movss   xmm6, ds:fWorldSectorSizeInversed	; sub_8B8E70


			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8FC809 + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_8FC7D0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8FC823 + 4), &fWorldSectorSizeInversed);	// mulss   xmm3, ds:fWorldSectorSizeInversed	; sub_8FC7D0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8FC83F + 4), &fWorldSectorSizeInversed);	// mulss   xmm4, ds:fWorldSectorSizeInversed	; sub_8FC7D0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8FC895 + 4), &fWorldSectorSizeInversed);	// mulss   xmm5, ds:fWorldSectorSizeInversed	; sub_8FC7D0				
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E00A6 + 4), &fWorldSectorSizeInversed);	// movss   xmm6, ds:fWorldSectorSizeInversed	; sub_9E0090


			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E9FA2 + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; _ZN7CEntity3AddERK5CRect
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E9FC2 + 4), &fWorldSectorSizeInversed);	// mulss   xmm4, ds:fWorldSectorSizeInversed	; _ZN7CEntity3AddERK5CRect
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E9FFD + 4), &fWorldSectorSizeInversed);	// mulss   xmm3, ds:fWorldSectorSizeInversed	; _ZN7CEntity3AddERK5CRect
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA04C + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; _ZN7CEntity3AddERK5CRect
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA822 + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; _ZN7CEntity6RemoveEv
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA845 + 4), &fWorldSectorSizeInversed);	// mulss   xmm3, ds:fWorldSectorSizeInversed	; _ZN7CEntity6RemoveEv
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA88E + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; _ZN7CEntity6RemoveEv
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA89E + 4), &fWorldSectorSizeInversed);	// mulss   xmm4, ds:fWorldSectorSizeInversed	; _ZN7CEntity6RemoveEv


			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9FA169 + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_9FA130
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9FA181 + 4), &fWorldSectorSizeInversed);	// mulss   xmm2, ds:fWorldSectorSizeInversed	; sub_9FA130
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9FA1CC + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_9FA130
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9FA1E1 + 4), &fWorldSectorSizeInversed);	// mulss   xmm3, ds:fWorldSectorSizeInversed	; sub_9FA130
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA739E9 + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_A739C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA73A02 + 4), &fWorldSectorSizeInversed);	// mulss   xmm2, ds:fWorldSectorSizeInversed	; sub_A739C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA73A4C + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_A739C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA73A62 + 4), &fWorldSectorSizeInversed);	// mulss   xmm3, ds:fWorldSectorSizeInversed	; sub_A739C0


			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xADE6C5 + 4), &fWorldSectorSizeInversed);	// movss   xmm6, ds:fWorldSectorSizeInversed	; sub_ADE6C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAE3B08 + 2), &fWorldSectorSizeInversed);	// fld     ds:fWorldSectorSizeInversed	; sub_AE3900
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB257ED + 4), &fWorldSectorSizeInversed);	// movss   xmm6, ds:fWorldSectorSizeInversed	; sub_B257E0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB2B69C + 4), &fWorldSectorSizeInversed);	// movss   xmm6, ds:fWorldSectorSizeInversed	; sub_B2B660
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE210 + 4), &fWorldSectorSizeInversed);	// movss   xmm5, ds:fWorldSectorSizeInversed	; sub_BBE1A0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE475 + 4), &fWorldSectorSizeInversed);	// mulss   xmm0, ds:fWorldSectorSizeInversed	; sub_BBE440
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE4B7 + 4), &fWorldSectorSizeInversed);	// movss   xmm6, ds:fWorldSectorSizeInversed	; sub_BBE440
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE543 + 4), &fWorldSectorSizeInversed);	// mulss   xmm2, ds:fWorldSectorSizeInversed	; sub_BBE440


		}

		CPatch::LeaveThisLevel();
		#endif


		//////////////

		// Patch multiplication by 120
		#if TRUE
		{
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x48A474), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; sub_48A440
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x48FBD0), iNumberOfWorldSectorsPerDimension / 8);	// mov     esi, ecx	; sub_48F9F0
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x7D93A7), iNumberOfWorldSectorsPerDimension / 8);	// mov     esi, edx	; sub_7D9370
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x7D94EE), iNumberOfWorldSectorsPerDimension / 8);	// mov     ebp, esi	; sub_7D9450
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x818118), iNumberOfWorldSectorsPerDimension / 8);	// mov     ecx, eax	; sub_818110
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x818162), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; sub_818150
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x818E27), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; sub_818C40
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x81B6B4), iNumberOfWorldSectorsPerDimension / 8);	// mov     edi, eax	; sub_81B4A0
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x81BDA8), iNumberOfWorldSectorsPerDimension / 8);	// mov     ebx, eax	; sub_81BB90
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x81C1EC), iNumberOfWorldSectorsPerDimension / 8);	// mov     edi, eax	; sub_81BFD0
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x81C5EA), iNumberOfWorldSectorsPerDimension / 8);	// mov     esi, eax	; sub_81C3D0
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x8FC9E8), iNumberOfWorldSectorsPerDimension / 8);	// mov     ebx, eax	; sub_8FC7D0
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x9E1A59), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, ecx        ; jumptable 009E1A44 case 4	; sub_9E1960
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x9E208B), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, ecx        ; jumptable 009E2076 case 6	; sub_9E1F70
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA232), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; _ZN7CEntity3AddERK5CRect
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA2F7), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; _ZN7CEntity3AddERK5CRect
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA339), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; _ZN7CEntity3AddERK5CRect
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA9AA), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; _ZN7CEntity6RemoveEv
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x9EAA4F), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; _ZN7CEntity6RemoveEv
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x9EAA91), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; _ZN7CEntity6RemoveEv
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x9FA305), iNumberOfWorldSectorsPerDimension / 8);	// mov     esi, eax	; sub_9FA130
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xA73B4C), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; sub_A739C0
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xAD9A62), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; sub_AD9A50
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xADE912), iNumberOfWorldSectorsPerDimension / 8);	// mov     ecx, edx	; sub_ADE8F0
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xAE2F1C), iNumberOfWorldSectorsPerDimension / 8);	// mov     eax, edx	; sub_AE2E20
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xAE2F4F), iNumberOfWorldSectorsPerDimension / 8);	// mov     eax, edx	; sub_AE2E20
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xAE2F7C), iNumberOfWorldSectorsPerDimension / 8);	// mov     eax, edx	; sub_AE2E20
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xAE3090), iNumberOfWorldSectorsPerDimension / 8);	// mov     eax, edx	; sub_AE2E20
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xAE30FD), iNumberOfWorldSectorsPerDimension / 8);	// mov     eax, edx	; sub_AE30E0
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xAE3A42), iNumberOfWorldSectorsPerDimension / 8);	// mov     ecx, edx	; sub_AE3900
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xB2599C), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; sub_B257E0
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xB2B94E), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; sub_B2B660
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE358), iNumberOfWorldSectorsPerDimension / 8);	// mov     edx, eax	; sub_BBE1A0
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE39B), iNumberOfWorldSectorsPerDimension / 8);	// mov     edi, eax	; sub_BBE1A0
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xBBE5EC), iNumberOfWorldSectorsPerDimension / 8);	// mov     ebx, eax	; sub_BBE440
		}
		#endif
	}
	#endif

	// CWorld::ms_aLodPtrLists
	#if TRUE
	{
		// Patch pointers to CWorld::aLodPtrLists
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DA2FF + 3), CWorld__ms_aLodPtrLists.gta_iv);	// mov     ebx, _ZN6CWorld15ms_aLodPtrListsE[eax*4]; CWorld::ms_aLodPtrLists	; sub_7DA2C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DA308 + 3), CWorld__ms_aLodPtrLists.gta_iv);	// lea     eax, _ZN6CWorld15ms_aLodPtrListsE[eax*4]; CWorld::ms_aLodPtrLists	; sub_7DA2C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8190A2 + 3), CWorld__ms_aLodPtrLists.gta_iv);	// lea     esi, _ZN6CWorld15ms_aLodPtrListsE[esi*4]; CWorld::ms_aLodPtrLists	; sub_818FF0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81B054 + 1), CWorld__ms_aLodPtrLists.gta_iv);	// mov     ebx, offset _ZN6CWorld15ms_aLodPtrListsE; CWorld::ms_aLodPtrLists	; _ZN6CWorld8ShutDownEv
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x81B08D + 2), CWorld__ms_aLodPtrLists.gta_iv + iTotalNumberOfWorldLODsectors);	// cmp     ebx, offset dword_11D3680	; _ZN6CWorld8ShutDownEv
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E9F40 + 3), CWorld__ms_aLodPtrLists.gta_iv);	// lea     esi, _ZN6CWorld15ms_aLodPtrListsE[esi*4]; CWorld::ms_aLodPtrLists	; _ZN7CEntity3AddERK5CRect
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA7A0 + 3), CWorld__ms_aLodPtrLists.gta_iv);	// lea     ebx, _ZN6CWorld15ms_aLodPtrListsE[ebx*4]; CWorld::ms_aLodPtrLists	; _ZN7CEntity6RemoveEv
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB2BB4E + 3), CWorld__ms_aLodPtrLists.gta_iv);	// lea     ebx, _ZN6CWorld15ms_aLodPtrListsE[ebx*4]; CWorld::ms_aLodPtrLists	; sub_B2BA70
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD3D2E8 + 1), CWorld__ms_aLodPtrLists.gta_iv);	// mov     edi, offset _ZN6CWorld15ms_aLodPtrListsE; CWorld::ms_aLodPtrLists	; sub_D3D2E0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD4A4F2 + 1), CWorld__ms_aLodPtrLists.gta_iv + iTotalNumberOfWorldLODsectors);	// mov     esi, offset dword_11D3680	; sub_D4A4F0
		}
		#endif

		// Patch count of LOD sectors - 1, (899)
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD4A4F7 + 1), iTotalNumberOfWorldLODsectors - 1);	// mov     edi, 383h	; sub_D4A4F0
		}
		#endif

		// Patch pointers to inversed size of LOD sector (1/200),  flt_858B4C
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();

		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DE004 + 4), &fWorldLODsectorSizeInversed);	// movss   xmm0, ds:fWorldLODsectorSizeInversed	; sub_7DC050
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DF44E + 4), &fWorldLODsectorSizeInversed);	// movss   xmm4, ds:fWorldLODsectorSizeInversed	; sub_7DE200
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DF501 + 4), &fWorldLODsectorSizeInversed);	// movss   xmm0, ds:fWorldLODsectorSizeInversed	; sub_7DE200
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x818FFC + 4), &fWorldLODsectorSizeInversed);	// movss   xmm2, ds:fWorldLODsectorSizeInversed	; sub_818FF0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E9E9A + 4), &fWorldLODsectorSizeInversed);	// movss   xmm2, ds:fWorldLODsectorSizeInversed	; _ZN7CEntity3AddERK5CRect
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA741 + 4), &fWorldLODsectorSizeInversed);	// movss   xmm2, ds:fWorldLODsectorSizeInversed	; _ZN7CEntity6RemoveEv
		}

		CPatch::LeaveThisLevel();
		#endif

		// Patch pointers to half number of sectors per dimension (15), 0xD50960
		#if TRUE
		{
			CPatch::EnterNewLevelAndDisableDebugState();

			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DE00C + 4), &fNumberOfWorldLODsectorsPerDimensionHalf);	// movss   xmm1, ds:fNumberOfWorldLODsectorsPerDimensionHalf	; sub_7DC050
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DF456 + 4), &fNumberOfWorldLODsectorsPerDimensionHalf);	// movss   xmm6, ds:fNumberOfWorldLODsectorsPerDimensionHalf	; sub_7DE200
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7DF509 + 4), &fNumberOfWorldLODsectorsPerDimensionHalf);	// movss   xmm1, ds:fNumberOfWorldLODsectorsPerDimensionHalf	; sub_7DE200
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x819004 + 4), &fNumberOfWorldLODsectorsPerDimensionHalf);	// movss   xmm3, ds:fNumberOfWorldLODsectorsPerDimensionHalf	; sub_818FF0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E9EA2 + 4), &fNumberOfWorldLODsectorsPerDimensionHalf);	// movss   xmm5, ds:fNumberOfWorldLODsectorsPerDimensionHalf	; _ZN7CEntity3AddERK5CRect
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA749 + 4), &fNumberOfWorldLODsectorsPerDimensionHalf);	// movss   xmm5, ds:fNumberOfWorldLODsectorsPerDimensionHalf	; _ZN7CEntity6RemoveEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB2BA86 + 4), &fNumberOfWorldLODsectorsPerDimensionHalf);	// movss   xmm5, ds:fNumberOfWorldLODsectorsPerDimensionHalf	; sub_B2BA70
			}

			CPatch::LeaveThisLevel();
		}
		#endif

		// Fix multiplication by 30
		#if TRUE
		{
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x7DA2F2), iNumberOfWorldLODsectorsPerDimension / 2);	// mov     edx, eax	; sub_7DA2C0
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x819098), iNumberOfWorldLODsectorsPerDimension / 2);	// mov     ecx, esi	; sub_818FF0
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x9E9F32), iNumberOfWorldLODsectorsPerDimension / 2);	// mov     edx, eax	; _ZN7CEntity3AddERK5CRect
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0x9EA791), iNumberOfWorldLODsectorsPerDimension / 2);	// mov     esi, ecx	; _ZN7CEntity6RemoveEv
			FixOptimizedMul(g_mCalc.GetCurrentVAbyPreferedVA(0xB2BB3D), iNumberOfWorldLODsectorsPerDimension / 2);	// mov     eax, edi	; sub_B2BA70
		}
		#endif

		// Patch count of LOD sectors per dimension - 1, (29)
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xB2BAF8 + 4), iNumberOfWorldLODsectorsPerDimension - 1);	// mov     [esp+0Ch+arg_10], 1Dh
		}
		#endif

		// Patch count of LOD sectors, (900)
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD3D2E3 + 1), iTotalNumberOfWorldLODsectors);	// mov     ecx, 900
		}
		#endif
	}
	#endif

	// Define variables for automatic patch
	#if TRUE
	{
		CCodeMover::SetVariable("NUMBER_OF_WORLD_SECTORS_PER_DIMENSION", iNumberOfWorldSectorsPerDimension);
		CCodeMover::SetVariable("NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE", iNumberOfWorldSectorsPerDimension - 1);
		CCodeMover::SetVariable("MINUS_NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_HALF", -(iNumberOfWorldSectorsPerDimension) / 2);


		CCodeMover::SetVariable("NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION", iNumberOfWorldLODsectorsPerDimension);
		CCodeMover::SetVariable("NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_MINUS_ONE", iNumberOfWorldLODsectorsPerDimension - 1);
		CCodeMover::SetVariable("SIZE_OF_WORLD_LOD_SECTORS_FOR_ONE_DIMENSION", iNumberOfWorldLODsectorsPerDimension * sizeof(void*));
		CCodeMover::SetVariable("MINUS_NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_HALF", -iNumberOfWorldLODsectorsPerDimension / 2);
	}
	#endif

	// Apply automatic patch
	#if TRUE
	{
		// Count of active addresses: 127
		CCodeMover::FixOnAddressRel(0x48A450, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x5a\xa4\x48\x00\x00", 0x48A455);	// line 1, 0x48A440 - sub_48A440 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x48A455, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x48A45A);	// line 2, 0x48A440 - sub_48A440 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x48A46A, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x74\xa4\x48\x00\x00", 0x48A46F);	// line 3, 0x48A440 - sub_48A440 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x48A46F, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x48A474);	// line 4, 0x48A440 - sub_48A440 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x48FBB0, 5, "\x01\x02\x81\xfa\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xba\xfb\x48\x00\x00", 0x48FBB5);	// line 5, 0x48F9F0 - sub_48F9F0 : cmp     edx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x48FBB5, 5, "\x01\x01\xba\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x48FBBA);	// line 6, 0x48F9F0 - sub_48F9F0 : mov     edx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x48FBC6, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xd0\xfb\x48\x00\x00", 0x48FBCB);	// line 7, 0x48F9F0 - sub_48F9F0 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x48FBCB, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x48FBD0);	// line 8, 0x48F9F0 - sub_48F9F0 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x7D5E72, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x0F\xab\x5e\x7d\x00\x00", 0x7D5E77);	// line 9, 0x7D5E40 - sub_7D5E40 : cmp     ecx, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0x7D5E77, 5, "\x01\x02\x81\xfa\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x0F\xab\x5e\x7d\x00\x00", 0x7D5E7C);	// line 10, 0x7D5E40 - sub_7D5E40 : cmp     edx, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0x7D6533, 6, "\x01\x01\x05\x05\x04""MINUS_NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_HALF\x00\x01\x02\x81\xc1\x05\x04""MINUS_NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_HALF\x00\x00", 0x7D6539);	// line 11, 0x7D6520 - sub_7D6520 : add     eax, 0FFFFFFC4h
		CCodeMover::FixOnAddressRel(0x7D9385, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8E\x0F\x8f\x93\x7d\x00\x00", 0x7D938A);	// line 12, 0x7D9370 - sub_7D9370 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x7D938A, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x7D938F);	// line 13, 0x7D9370 - sub_7D9370 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x7D9397, 5, "\x01\x02\x81\xfa\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8E\x0F\xa1\x93\x7d\x00\x00", 0x7D939C);	// line 14, 0x7D9370 - sub_7D9370 : cmp     edx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x7D939C, 5, "\x01\x01\xba\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x7D93A1);	// line 15, 0x7D9370 - sub_7D9370 : mov     edx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x7D9481, 5, "\x01\x02\x81\xfb\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8E\x0F\x8e\x94\x7d\x00\x00", 0x7D9486);	// line 16, 0x7D9450 - sub_7D9450 : cmp     ebx, 119
		CCodeMover::FixOnAddressRel(0x7D94C3, 5, "\x01\x02\x81\xfd\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8E\x0F\xcd\x94\x7d\x00\x00", 0x7D94C8);	// line 17, 0x7D9450 - sub_7D9450 : cmp     ebp, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x7D94C8, 5, "\x01\x01\xbd\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x7D94CD);	// line 18, 0x7D9450 - sub_7D9450 : mov     ebp, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x7D98BC, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8E\x0F\xc6\x98\x7d\x00\x00", 0x7D98C1);	// line 19, 0x7D98B0 - sub_7D98B0 : cmp     ecx, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0x7D98C1, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x00", 0x7D98C6);	// line 20, 0x7D98B0 - sub_7D98B0 : mov     ecx, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0x7D98E2, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8E\x0F\xec\x98\x7d\x00\x00", 0x7D98E7);	// line 21, 0x7D98B0 - sub_7D98B0 : cmp     eax, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0x7D98E7, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x00", 0x7D98EC);	// line 22, 0x7D98B0 - sub_7D98B0 : mov     eax, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0x818154, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x87\x0F\x7c\x81\x81\x00\x00", 0x818159);	// line 23, 0x818150 - sub_818150 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81815D, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x87\x0F\x7c\x81\x81\x00\x00", 0x818162);	// line 24, 0x818150 - sub_818150 : cmp     eax, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0x818E07, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x11\x8e\x81\x00\x00", 0x818E0C);	// line 25, 0x818C40 - sub_818C40 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x818E0C, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x818E11);	// line 26, 0x818C40 - sub_818C40 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x818E1D, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x27\x8e\x81\x00\x00", 0x818E22);	// line 27, 0x818C40 - sub_818C40 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x818E22, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x818E27);	// line 28, 0x818C40 - sub_818C40 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x8190ED, 7, "\x01\x02\x81\xc6\x05\x04""SIZE_OF_WORLD_LOD_SECTORS_FOR_ONE_DIMENSION\x00\x02\x04\xF0\x90\x81\x00\x00", 0x8190F4);	// line 29, 0x818FF0 - sub_818FF0 : add     esi, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0x81B690, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x9a\xb6\x81\x00\x00", 0x81B695);	// line 30, 0x81B4A0 - sub_81B4A0 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81B695, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x81B69A);	// line 31, 0x81B4A0 - sub_81B4A0 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81B6AA, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xb4\xb6\x81\x00\x00", 0x81B6AF);	// line 32, 0x81B4A0 - sub_81B4A0 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81B6AF, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x81B6B4);	// line 33, 0x81B4A0 - sub_81B4A0 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81BD88, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x92\xbd\x81\x00\x00", 0x81BD8D);	// line 34, 0x81BB90 - sub_81BB90 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81BD8D, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x81BD92);	// line 35, 0x81BB90 - sub_81BB90 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81BD9E, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xa8\xbd\x81\x00\x00", 0x81BDA3);	// line 36, 0x81BB90 - sub_81BB90 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81BDA3, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x81BDA8);	// line 37, 0x81BB90 - sub_81BB90 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81C1C8, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xd2\xc1\x81\x00\x00", 0x81C1CD);	// line 38, 0x81BFD0 - sub_81BFD0 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81C1CD, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x81C1D2);	// line 39, 0x81BFD0 - sub_81BFD0 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81C1E2, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xec\xc1\x81\x00\x00", 0x81C1E7);	// line 40, 0x81BFD0 - sub_81BFD0 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81C1E7, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x81C1EC);	// line 41, 0x81BFD0 - sub_81BFD0 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81C5C6, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xd0\xc5\x81\x00\x00", 0x81C5CB);	// line 42, 0x81C3D0 - sub_81C3D0 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81C5CB, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x81C5D0);	// line 43, 0x81C3D0 - sub_81C3D0 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81C5E0, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xea\xc5\x81\x00\x00", 0x81C5E5);	// line 44, 0x81C3D0 - sub_81C3D0 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x81C5E5, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x81C5EA);	// line 45, 0x81C3D0 - sub_81C3D0 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x83AD19, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x8C\x0F\x23\xad\x83\x00\x00", 0x83AD1E);	// line 46, 0x83AD10 - sub_83AD10 : cmp     eax, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0x83AD1E, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x00", 0x83AD23);	// line 47, 0x83AD10 - sub_83AD10 : mov     eax, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0x8FC9C8, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xd2\xc9\x8f\x00\x00", 0x8FC9CD);	// line 48, 0x8FC7D0 - sub_8FC7D0 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x8FC9CD, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x8FC9D2);	// line 49, 0x8FC7D0 - sub_8FC7D0 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x8FC9DE, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xe8\xc9\x8f\x00\x00", 0x8FC9E3);	// line 50, 0x8FC7D0 - sub_8FC7D0 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x8FC9E3, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x8FC9E8);	// line 51, 0x8FC7D0 - sub_8FC7D0 : mov     eax, 77h ; 'w'			
		CCodeMover::FixOnAddressRel(0x9E1A11, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x1b\x1a\x9e\x00\x00", 0x9E1A16);	// line 53, 0x9E1960 - sub_9E1960 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9E1A16, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9E1A1B);	// line 54, 0x9E1960 - sub_9E1960 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9E1A27, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x31\x1a\x9e\x00\x00", 0x9E1A2C);	// line 55, 0x9E1960 - sub_9E1960 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9E1A2C, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9E1A31);	// line 56, 0x9E1960 - sub_9E1960 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9E2041, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x4b\x20\x9e\x00\x00", 0x9E2046);	// line 57, 0x9E1F70 - sub_9E1F70 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9E2046, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9E204B);	// line 58, 0x9E1F70 - sub_9E1F70 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9E2057, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x61\x20\x9e\x00\x00", 0x9E205C);	// line 59, 0x9E1F70 - sub_9E1F70 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9E205C, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9E2061);	// line 60, 0x9E1F70 - sub_9E1F70 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9E9F8B, 8, "\x01\x02\x81\xc6\x05\x04""SIZE_OF_WORLD_LOD_SECTORS_FOR_ONE_DIMENSION\x00\x02\x05\x8E\x9F\x9E\x00\x00", 0x9E9F93);	// line 61, 0x9E9E10 - _ZN7CEntity3AddERK5CRect : add     esi, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0x9EA212, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x1c\xa2\x9e\x00\x00", 0x9EA217);	// line 62, 0x9E9E10 - _ZN7CEntity3AddERK5CRect : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA217, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9EA21C);	// line 63, 0x9E9E10 - _ZN7CEntity3AddERK5CRect : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA228, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x32\xa2\x9e\x00\x00", 0x9EA22D);	// line 64, 0x9E9E10 - _ZN7CEntity3AddERK5CRect : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA22D, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9EA232);	// line 65, 0x9E9E10 - _ZN7CEntity3AddERK5CRect : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA2D7, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xe1\xa2\x9e\x00\x00", 0x9EA2DC);	// line 66, 0x9E9E10 - _ZN7CEntity3AddERK5CRect : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA2DC, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9EA2E1);	// line 67, 0x9E9E10 - _ZN7CEntity3AddERK5CRect : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA2ED, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xf7\xa2\x9e\x00\x00", 0x9EA2F2);	// line 68, 0x9E9E10 - _ZN7CEntity3AddERK5CRect : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA2F2, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9EA2F7);	// line 69, 0x9E9E10 - _ZN7CEntity3AddERK5CRect : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA319, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x23\xa3\x9e\x00\x00", 0x9EA31E);	// line 70, 0x9E9E10 - _ZN7CEntity3AddERK5CRect : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA31E, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9EA323);	// line 71, 0x9E9E10 - _ZN7CEntity3AddERK5CRect : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA32F, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xf7\xa2\x9e\x00\x00", 0x9EA334);	// line 72, 0x9E9E10 - _ZN7CEntity3AddERK5CRect : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA334, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9EA339);	// line 73, 0x9E9E10 - _ZN7CEntity3AddERK5CRect : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA810, 8, "\x01\x02\x81\xc3\x05\x04""SIZE_OF_WORLD_LOD_SECTORS_FOR_ONE_DIMENSION\x00\x02\x05\x13\xA8\x9E\x00\x00", 0x9EA818);	// line 74, 0x9EA680 - _ZN7CEntity6RemoveEv : add     ebx, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0x9EA98A, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x94\xa9\x9e\x00\x00", 0x9EA98F);	// line 75, 0x9EA680 - _ZN7CEntity6RemoveEv : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA98F, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9EA994);	// line 76, 0x9EA680 - _ZN7CEntity6RemoveEv : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA9A0, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xaa\xa9\x9e\x00\x00", 0x9EA9A5);	// line 77, 0x9EA680 - _ZN7CEntity6RemoveEv : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EA9A5, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9EA9AA);	// line 78, 0x9EA680 - _ZN7CEntity6RemoveEv : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EAA2F, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x39\xaa\x9e\x00\x00", 0x9EAA34);	// line 79, 0x9EA680 - _ZN7CEntity6RemoveEv : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EAA34, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9EAA39);	// line 80, 0x9EA680 - _ZN7CEntity6RemoveEv : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EAA45, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x4f\xaa\x9e\x00\x00", 0x9EAA4A);	// line 81, 0x9EA680 - _ZN7CEntity6RemoveEv : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EAA4A, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9EAA4F);	// line 82, 0x9EA680 - _ZN7CEntity6RemoveEv : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EAA71, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x7b\xaa\x9e\x00\x00", 0x9EAA76);	// line 83, 0x9EA680 - _ZN7CEntity6RemoveEv : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EAA76, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9EAA7B);	// line 84, 0x9EA680 - _ZN7CEntity6RemoveEv : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EAA87, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x4f\xaa\x9e\x00\x00", 0x9EAA8C);	// line 85, 0x9EA680 - _ZN7CEntity6RemoveEv : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9EAA8C, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9EAA91);	// line 86, 0x9EA680 - _ZN7CEntity6RemoveEv : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9FA2E1, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xeb\xa2\x9f\x00\x00", 0x9FA2E6);	// line 87, 0x9FA130 - sub_9FA130 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9FA2E6, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9FA2EB);	// line 88, 0x9FA130 - sub_9FA130 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9FA2FB, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x05\xa3\x9f\x00\x00", 0x9FA300);	// line 89, 0x9FA130 - sub_9FA130 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0x9FA300, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0x9FA305);	// line 90, 0x9FA130 - sub_9FA130 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xA73B2C, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x36\x3b\xa7\x00\x00", 0xA73B31);	// line 91, 0xA739C0 - sub_A739C0 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xA73B31, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xA73B36);	// line 92, 0xA739C0 - sub_A739C0 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xA73B42, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x4c\x3b\xa7\x00\x00", 0xA73B47);	// line 93, 0xA739C0 - sub_A739C0 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xA73B47, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xA73B4C);	// line 94, 0xA739C0 - sub_A739C0 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xAD9A54, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x83\x0F\x85\x9a\xad\x00\x00", 0xAD9A59);	// line 95, 0xAD9A50 - sub_AD9A50 : cmp     ecx, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0xAD9A5D, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x83\x0F\x85\x9a\xad\x00\x00", 0xAD9A62);	// line 96, 0xAD9A50 - sub_AD9A50 : cmp     eax, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0xADE8FC, 10, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x01\xFF\xE8\xAD\x00\x01\x02\x0F\x83\x0F\xd5\xe9\xad\x00\x00", 0xADE906);	// line 97, 0xADE8F0 - sub_ADE8F0 : cmp     eax, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0xADE909, 9, "\x01\x02\x81\xfa\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x01\x02\x0F\x83\x0F\xd5\xe9\xad\x00\x00", 0xADE912);	// line 98, 0xADE8F0 - sub_ADE8F0 : cmp     edx, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0xAE301B, 7, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\x1E\x30\xAE\x00\x00", 0xAE3022);	// line 99, 0xAE2E20 - sub_AE2E20 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xAE306E, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x02\x71\x30\xAE\x00\x00", 0xAE3073);	// line 100, 0xAE2E20 - sub_AE2E20 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xAE3075, 5, "\x01\x01\xbd\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xAE307A);	// line 101, 0xAE2E20 - sub_AE2E20 : mov     ebp, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xB2597C, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x86\x59\xb2\x00\x00", 0xB25981);	// line 102, 0xB257E0 - sub_B257E0 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xB25981, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xB25986);	// line 103, 0xB257E0 - sub_B257E0 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xB25992, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x9c\x59\xb2\x00\x00", 0xB25997);	// line 104, 0xB257E0 - sub_B257E0 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xB25997, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xB2599C);	// line 105, 0xB257E0 - sub_B257E0 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xB2B84E, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xB2B853);	// line 106, 0xB2B660 - sub_B2B660 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xB2B927, 7, "\x01\x02\x81\xfa\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\x2A\xB9\xB2\x00\x00", 0xB2B92E);	// line 107, 0xB2B660 - sub_B2B660 : cmp     edx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xB2B944, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x4e\xb9\xb2\x00\x00", 0xB2B949);	// line 108, 0xB2B660 - sub_B2B660 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xB2B949, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xB2B94E);	// line 109, 0xB2B660 - sub_B2B660 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xB2BAED, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x02\x02\xF0\xBA\xB2\x00\x00", 0xB2BAF2);	// line 110, 0xB2BA70 - sub_B2BA70 : cmp     eax, 1Dh
		CCodeMover::FixOnAddressRel(0xB2BB0C, 5, "\x01\x02\x81\xfe\x05\x04""NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x16\xbb\xb2\x00\x00", 0xB2BB11);	// line 111, 0xB2BA70 - sub_B2BA70 : cmp     esi, 1Dh
		CCodeMover::FixOnAddressRel(0xB2BB11, 5, "\x01\x01\xbe\x05\x04""NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xB2BB16);	// line 112, 0xB2BA70 - sub_B2BA70 : mov     esi, 1Dh
		CCodeMover::FixOnAddressRel(0xB2BB85, 8, "\x01\x02\x81\xc3\x05\x04""SIZE_OF_WORLD_LOD_SECTORS_FOR_ONE_DIMENSION\x00\x02\x05\x88\xBB\xB2\x00\x00", 0xB2BB8D);	// line 113, 0xB2BA70 - sub_B2BA70 : add     ebx, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0xBBE379, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x83\xe3\xbb\x00\x00", 0xBBE37E);	// line 114, 0xBBE1A0 - sub_BBE1A0 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xBBE37E, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xBBE383);	// line 115, 0xBBE1A0 - sub_BBE1A0 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xBBE391, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\x9b\xe3\xbb\x00\x00", 0xBBE396);	// line 116, 0xBBE1A0 - sub_BBE1A0 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xBBE396, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xBBE39B);	// line 117, 0xBBE1A0 - sub_BBE1A0 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xBBE3FC, 7, "\x01\x02\x81\xfe\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x04\xFF\xE3\xBB\x00\x00", 0xBBE403);	// line 118, 0xBBE1A0 - sub_BBE1A0 : cmp     esi, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0xBBE412, 6, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION\x00\x02\x03\x15\xE4\xBB\x00\x00", 0xBBE418);	// line 119, 0xBBE1A0 - sub_BBE1A0 : cmp     eax, 78h ; 'x'
		CCodeMover::FixOnAddressRel(0xBBE5CC, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xd6\xe5\xbb\x00\x00", 0xBBE5D1);	// line 120, 0xBBE440 - sub_BBE440 : cmp     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xBBE5D1, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xBBE5D6);	// line 121, 0xBBE440 - sub_BBE440 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xBBE5E2, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xec\xe5\xbb\x00\x00", 0xBBE5E7);	// line 122, 0xBBE440 - sub_BBE440 : cmp     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xBBE5E7, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xBBE5EC);	// line 123, 0xBBE440 - sub_BBE440 : mov     eax, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xBF6014, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xBF6019);	// line 124, 0xBF5EA0 - sub_BF5EA0 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xBF7D21, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xBF7D26);	// line 125, 0xBF7B90 - sub_BF7B90 : mov     ecx, 77h ; 'w'
		CCodeMover::FixOnAddressRel(0xBF83F6, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE\x00\x00", 0xBF83FB);	// line 126, 0xBF81E0 - sub_BF81E0 : mov     ecx, 77h ; 'w'
	}
	#endif

	// Undefine variables of automatic patch
	#if TRUE
	{
		CCodeMover::DeleteVariable("NUMBER_OF_WORLD_SECTORS_PER_DIMENSION");
		CCodeMover::DeleteVariable("NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_MINUS_ONE");
		CCodeMover::DeleteVariable("MINUS_NUMBER_OF_WORLD_SECTORS_PER_DIMENSION_HALF");

		CCodeMover::DeleteVariable("NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION");
		CCodeMover::DeleteVariable("NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_MINUS_ONE");
		CCodeMover::DeleteVariable("SIZE_OF_WORLD_LOD_SECTORS_FOR_ONE_DIMENSION");
		CCodeMover::DeleteVariable("MINUS_NUMBER_OF_WORLD_LOD_SECTORS_PER_DIMENSION_HALF");
	}
	#endif
}
#endif

// Patches world sectors
void MapLimits::PatchWorldSectors_GTA_SA()
{
	using namespace Game_GTASA;
	MAKE_VAR_GAME_VERSION();

	if (CPatch::IsDebugModeActive())
	{
		ms_worldMapSize = 6000;
		ms_worldSectorSize = 50;
		ms_worldLODsectorSize = 200;
	}

	if (!this->PatchWorldSectors_DoInitialisingWork())
		return;

	// Allocate memory
	#if TRUE
	if (!CPatch::IsDebugModeActive())
	{
		if (iNumberOfWorldSectorsPerDimension > 120)
		{
			CWorld__ms_aSectors.gta_sa = new CSector[iTotalNumberOfWorldSectors];
			memset(CWorld__ms_aSectors.gta_sa, 0, iTotalNumberOfWorldSectors * sizeof(CSector));
			CWorld__ms_aSectors.bIsAllocated.Set(true);
		}

		if (iNumberOfWorldRepeatSectorsPerDimension > 16)
		{
			CWorld__ms_aRepeatSectors.gta_sa = new CRepeatSector[iTotalNumberOfWorldRepeatSectors];
			memset(CWorld__ms_aRepeatSectors.gta_sa, 0, iTotalNumberOfWorldRepeatSectors * sizeof(CRepeatSector));
			CWorld__ms_aRepeatSectors.bIsAllocated.Set(true);
		}

		if (iNumberOfWorldLODsectorsPerDimension > 30)
		{
			CWorld__ms_aLodPtrLists.gta_sa = new Game_GTA::CPtrNodeSingleLink*[iTotalNumberOfWorldLODsectors];
			memset(CWorld__ms_aLodPtrLists.gta_sa, 0, iTotalNumberOfWorldLODsectors * sizeof(void*));
			CWorld__ms_aLodPtrLists.bIsAllocated.Set(true);
		}
	}
	#endif

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		this->PatchWorldSectors_GTA_SA_PC_1_0_HOODLUM();
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		this->PatchWorldSectors_GTA_SA_2_0_ANDROID_ARM32();
	#endif
}

// Patches world sectors
void MapLimits::PatchWorldSectors()
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#if defined(IS_PLATFORM_WIN_X86) || defined(IS_PLATFORM_ANDROID_ARM32)
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
	|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	this->PatchWorldSectors_GTA_SA();

	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
	this->PatchWorldSectors_GTA_IV_1_0_7_0();
	#endif
	#endif

	CPatch::LeaveThisLevel();
}

namespace Game_GTASA
{
	extern "C"
	{
		RwBBox RwWorldMapSizeBox;
	}

	#ifdef IS_PLATFORM_ANDROID_ARM32
	// patch for 0x46F5D0
	extern "C"
	{
		uintptr_t Address_CGame__InitialiseRenderWare_46F5EA_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CGame__InitialiseRenderWare_46F5D0()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_ADDRESS_OF_SYMBOL(R0, RwWorldMapSizeBox)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CGame__InitialiseRenderWare_46F5EA_thumb)
			);
	}
	#endif
}

// Patches Renderware world map size limit
void MapLimits::PatchRwWorldMapSize()
{
	using namespace Game_GTASA;
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		this->ms_rwWorldMapSize = 20000;

	// Set variables
	float fRwWorldMapMaxCoord = (float)MapLimits::ms_rwWorldMapSize / 2;
	float fRwWorldMapMinCoord = -fRwWorldMapMaxCoord;

	RwWorldMapSizeBox.inf.x = fRwWorldMapMinCoord;
	RwWorldMapSizeBox.inf.y = fRwWorldMapMinCoord;
	RwWorldMapSizeBox.inf.z = fRwWorldMapMinCoord;

	RwWorldMapSizeBox.sup.x = fRwWorldMapMaxCoord;
	RwWorldMapSizeBox.sup.y = fRwWorldMapMaxCoord;
	RwWorldMapSizeBox.sup.z = fRwWorldMapMaxCoord;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		// Patch coordinates
		#if TRUE
		{
			CPatch::PatchFloat(0x5BD6EC + 4, fRwWorldMapMaxCoord);	// mov     [esp+3Ch+boundingBox.sup.z], 10000.0	; _ZN5CGame20InitialiseRenderWareEv
			CPatch::PatchFloat(0x5BD6F4 + 4, fRwWorldMapMaxCoord);	// mov     [esp+3Ch+boundingBox.sup.y], 10000.0	; _ZN5CGame20InitialiseRenderWareEv
			CPatch::PatchFloat(0x5BD6FC + 4, fRwWorldMapMaxCoord);	// mov     [esp+3Ch+boundingBox.sup.x], 10000.0	; _ZN5CGame20InitialiseRenderWareEv
			CPatch::PatchFloat(0x5BD704 + 4, fRwWorldMapMinCoord);	// mov     [esp+3Ch+boundingBox.inf.z], -10000.0	; _ZN5CGame20InitialiseRenderWareEv
			CPatch::PatchFloat(0x5BD70C + 4, fRwWorldMapMinCoord);	// mov     [esp+3Ch+boundingBox.inf.y], -10000.0	; _ZN5CGame20InitialiseRenderWareEv
			CPatch::PatchFloat(0x5BD714 + 4, fRwWorldMapMinCoord);	// mov     [esp+3Ch+boundingBox.inf.x], -10000.0	; _ZN5CGame20InitialiseRenderWareEv
		}
		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID_ARM32)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		Address_CGame__InitialiseRenderWare_46F5EA_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x46F5EA));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x46F5D0),
			(void*)&patch_CGame__InitialiseRenderWare_46F5D0
		);
	}
	#endif

	CPatch::LeaveThisLevel();
}

extern "C"
{
	int iNumberOfWaterBlocksPerDimension;
	int iNumberOfWaterBlocksPerDimensionMinusOne;
	int iNumberOfWaterBlocksPerDimensionMinusThree;
	int iNumberOfWaterBlocksPerDimensionMultipliedBySizeOfBlock;
	int iTotalNumberOfWaterBlocks;
	int iTotalNumberOfWaterBlocksMultipliedBySizeOfBlock;

	float fNumberOfWaterBlocksPerDimensionHalf;

	int iWaterMapMinCoord;
	int iWaterMapMaxCoord;

	float fWaterMapMinCoord;
	float fWaterMapMaxCoord;
}

// Do initializing work for water map size patching
bool MapLimits::PatchWaterMapSize_DoInitialisingWork()
{
	if (!ValidateMapSizeOrShowMessage(ms_waterMapSize, "Water"))
		return false;

	// Set variables
	#if TRUE
	{
		iNumberOfWaterBlocksPerDimension = ms_waterMapSize / ms_waterBlockSize;
		iNumberOfWaterBlocksPerDimensionMinusOne = iNumberOfWaterBlocksPerDimension - 1;
		iNumberOfWaterBlocksPerDimensionMinusThree = iNumberOfWaterBlocksPerDimension - 3;
		iNumberOfWaterBlocksPerDimensionMultipliedBySizeOfBlock = iNumberOfWaterBlocksPerDimension * sizeof(int16_t);
		iTotalNumberOfWaterBlocks = iNumberOfWaterBlocksPerDimension * iNumberOfWaterBlocksPerDimension;
		iTotalNumberOfWaterBlocksMultipliedBySizeOfBlock = iTotalNumberOfWaterBlocks * sizeof(int16_t);

		fNumberOfWaterBlocksPerDimensionHalf = (float)(iNumberOfWaterBlocksPerDimension / 2);

		iWaterMapMaxCoord = ms_waterMapSize / 2;
		iWaterMapMinCoord = -iWaterMapMaxCoord;

		fWaterMapMinCoord = (float)iWaterMapMinCoord;
		fWaterMapMaxCoord = (float)iWaterMapMaxCoord;
		////////////////////
		iWaterMapMaxCoord = ms_waterMapSize / 2;
		iWaterMapMinCoord = -iWaterMapMaxCoord;

		fWaterMapMinCoord = (float)iWaterMapMinCoord;
		fWaterMapMaxCoord = (float)iWaterMapMaxCoord;
	}
	#endif

	CGenericLogStorage::SaveFormattedTextLn(
		"\nWater info:\n"
		"Water map size: %d x %d\n"
		"Number of water blocks per dimension: %d\n"
		"Total number of water blocks: %d",

		MapLimits::ms_waterMapSize, MapLimits::ms_waterMapSize,
		iNumberOfWaterBlocksPerDimension,
		iTotalNumberOfWaterBlocks
	);

	// Allocate memory
	#if TRUE
	if (!CPatch::IsDebugModeActive())
	{
		if (iTotalNumberOfWaterBlocks > 144)
		{
			CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr = new int16_t[iTotalNumberOfWaterBlocks];
			CWaterLevel__m_QuadsAndTrianglesInEachBlock.bIsAllocated.Set(true);
		}
	}
	#endif

	return true;
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	///// patches /////
	NAKED void patch_CWaterLevel__AddToQuadsAndTrianglesList_6E5758()
	{
		__asm
		{
			imul	eax, [iNumberOfWaterBlocksPerDimension];
			add     ecx, eax;

			// go back
			push 6E575Eh;
			retn;
		}
	}

	NAKED void patch_CWaterLevel__GetWaterLevelNoWaves_6E85E9()
	{
		__asm
		{
			mov		ecx, esi;
			imul	ecx, [iNumberOfWaterBlocksPerDimension];
			lea     edx, [eax + ecx];

			// go back
			push 6E85EFh;
			retn;
		}
	}

	NAKED void patch_CWaterLevel__MarkQuadsAndPolysToBeRendered_6E5818()
	{
		__asm
		{
			imul eax, [iNumberOfWaterBlocksPerDimension];
			lea     edx, [ecx + eax];

			// go back
			push 6E581Eh;
			retn;
		}
	}

	NAKED void patch_CWaterLevel__TestLineAgainstWater_6E6318()
	{
		__asm
		{
			mov ebp, edi;
			imul ebp, [iNumberOfWaterBlocksPerDimension];

			// go back
			push 6E631Eh;
			retn;
		}
	}

	// Debug function
	void patch_CWaterLevel__ScanThroughBlocks()
	{
		*(DWORD*)0xC215EC = 0;

		for (int blockY = 0; blockY < iNumberOfWaterBlocksPerDimension; blockY++)
			for (int blockX = 0; blockX < iNumberOfWaterBlocksPerDimension; blockX++)
				((void(__cdecl*)(int, int))0x6E6CA0)(blockX, blockY);	// CWaterLevel::BlockHit		
	}
}

// Patches water map size
void MapLimits::PatchWaterMapSize_GTA_SA_PC_1_0_HOODLUM()
{
	using namespace Game_GTASA;

	if (CPatch::IsDebugModeActive())
		ms_waterMapSize = 6000;

	if (!this->PatchWaterMapSize_DoInitialisingWork())
		return;

	#if FALSE

	// Multiply by 12
	#if TRUE
	{
		CPatch::RedirectCode(0x6E5758, &patch_CWaterLevel__AddToQuadsAndTrianglesList_6E5758);
		CPatch::RedirectCode(0x6E85E9, &patch_CWaterLevel__GetWaterLevelNoWaves_6E85E9);
		CPatch::RedirectCode(0x6E5818, &patch_CWaterLevel__MarkQuadsAndPolysToBeRendered_6E5818);
		CPatch::RedirectCode(0x6E6318, &patch_CWaterLevel__TestLineAgainstWater_6E6318);
	}
	#endif
	#else

	// Debug code
	#if FALSE
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		// CPatch::PatchFloat(0x859A90, fWaterMapMinCoord);
		// CPatch::PatchFloat(0x859A94, fWaterMapMaxCoord);
		// CPatch::PatchFloat(0x858B44, fNumberOfWaterBlocksPerDimensionHalf);
		CPatch::NOPinstructions(0x6E6CFF, 5);
		CPatch::RedirectFunction(0x6E6D10, &patch_CWaterLevel__ScanThroughBlocks);
		CPatch::LeaveThisLevel();
	}
	#endif

	// Patch pointers to CWaterLevel::m_QuadsAndTrianglesInEachBlock
	#if TRUE
	CPatch::PatchPointer(0x6E575E + 4, CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// mov     dx, ds:_ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE[ecx*2]; CWaterLevel::m_QuadsAndTrianglesInEachBlock
	CPatch::PatchPointer(0x6E577F + 4, CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// mov     ds:_ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE[ecx*2], dx; CWaterLevel::m_QuadsAndTrianglesInEachBlock
	CPatch::PatchPointer(0x6E57FD + 4, CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// mov     ds:_ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE[ecx*2], dx; CWaterLevel::m_QuadsAndTrianglesInEachBlock
	CPatch::PatchPointer(0x6E581E + 4, CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// movzx   eax, ds:_ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE[edx*2]; CWaterLevel::m_QuadsAndTrianglesInEachBlock
	CPatch::PatchPointer(0x6E635A + 4, CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// movzx   eax, ds:_ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE[ecx*2]; CWaterLevel::m_QuadsAndTrianglesInEachBlock
	CPatch::PatchPointer(0x6E85EF + 4, CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// movzx   eax, ds:_ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE[edx*2]; CWaterLevel::m_QuadsAndTrianglesInEachBlock
	CPatch::PatchPointer(0x6EAE93 + 1, CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// mov     edi, offset _ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE; CWaterLevel::m_QuadsAndTrianglesInEachBlock
	#endif

	// Patch values
	#if TRUE
	{
		// CWaterLevel::AddToQuadsAndTrianglesList
		CPatch::RedirectCode(0x6E5758, &patch_CWaterLevel__AddToQuadsAndTrianglesList_6E5758);

		// CWaterLevel::AddWaterLevelVertex
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(0x6E5A48 + 2, &fWaterMapMinCoord);	// fcomp   ds:flt_859A90
		CPatch::PatchPointer(0x6E5A81 + 2, &fWaterMapMaxCoord);	// fcomp   ds:flt_859A94
		CPatch::PatchPointer(0x6E5AB7 + 2, &fWaterMapMinCoord);	// fcomp   ds:flt_859A90
		CPatch::PatchPointer(0x6E5AF7 + 2, &fWaterMapMaxCoord);	// fcomp   ds:flt_859A94
		CPatch::LeaveThisLevel();

		CPatch::PatchUINT32(0x6E5A56 + 1, iWaterMapMinCoord); // mov     ebx, 0FFFFF448h
		CPatch::PatchUINT32(0x6E5A8E + 1, iWaterMapMaxCoord); // mov     ebx, 3000
		CPatch::PatchUINT32(0x6E5AC4 + 1, iWaterMapMinCoord); // mov     edi, 0FFFFF448h
		CPatch::PatchUINT32(0x6E5B04 + 1, iWaterMapMaxCoord); // mov     edi, 3000

		// CWaterLevel::FillQuadsAndTrianglesList
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(0x6E7B4A + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6E7B6D + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::LeaveThisLevel();

		CPatch::PatchUINT32(0x6E7D0C + 1, ms_waterMapSize);	// cmp     eax, 6000
		CPatch::PatchUINT32(0x6E7D29 + 1, ms_waterMapSize);	// cmp     eax, 6000

		// CWaterLevel::FindNearestWaterAndItsFlow(void)
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(0x6E9D9F + 2, &fWaterMapMinCoord);	// fcomp   ds:flt_859A90				
		CPatch::PatchPointer(0x6E9DD0 + 2, &fWaterMapMaxCoord);	// fcomp   ds:flt_859A94
		CPatch::PatchPointer(0x6E9DE5 + 2, &fWaterMapMinCoord);	// fcomp   ds:flt_859A90
		CPatch::PatchPointer(0x6E9DFA + 2, &fWaterMapMaxCoord);	// fcomp   ds:flt_859A94
		CPatch::LeaveThisLevel();

		// CWaterLevel::GetWaterLevelNoWaves
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(0x6E858F + 2, &fNumberOfWaterBlocksPerDimensionHalf); // fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E85B1 + 2, &fNumberOfWaterBlocksPerDimensionHalf); // fadd    ds:flt_858B44
		CPatch::LeaveThisLevel();

		CPatch::RedirectCode(0x6E85E9, &patch_CWaterLevel__GetWaterLevelNoWaves_6E85E9);

		// CWaterLevel::MarkQuadsAndPolysToBeRendered
		CPatch::RedirectCode(0x6E5818, &patch_CWaterLevel__MarkQuadsAndPolysToBeRendered_6E5818);

		// CWaterLevel::RenderDetailedSeaBedSegment
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(0x6E6AED + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6E6B0F + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6E6B88 + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6E6BD0 + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::LeaveThisLevel();

		// CWaterLevel::RenderSeaBedSegment
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(0x6E68BA + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6E68D6 + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6E6924 + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6E696C + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94				
		CPatch::LeaveThisLevel();

		// CWaterLevel::RenderWater
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(0x6EF70F + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6EF725 + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6EFFE9 + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6F0018 + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6F0032 + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6F0042 + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94				
		CPatch::LeaveThisLevel();

		// CWaterLevel::ScanThroughBlock
		CPatch::EnterNewLevelAndDisableDebugState();

		CPatch::PatchPointer(0x6E6DC2 + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E6DD6 + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E6DEA + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E6DFE + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E6E12 + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E6E26 + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E6E46 + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E6E5A + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E6E6E + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E6E82 + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44

		CPatch::LeaveThisLevel();

		// CWaterLevel::TestLineAgainstWater
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(0x6E62B7 + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E62CC + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E62E3 + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E62F8 + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E6732 + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::PatchPointer(0x6E674A + 2, &fNumberOfWaterBlocksPerDimensionHalf);	// fadd    ds:flt_858B44
		CPatch::LeaveThisLevel();

		CPatch::RedirectCode(0x6E6318, &patch_CWaterLevel__TestLineAgainstWater_6E6318);

		// CWaterLevel::WaterLevelInitialise
		CPatch::PatchUINT32(0x6EAE8E + 1, (iTotalNumberOfWaterBlocks * sizeof(WORD)) / sizeof(DWORD));
	}
	#endif

	// Set variables for automatic patch
	#if TRUE
	{
		CCodeMover::SetVariable("NUMBER_OF_WATER_BLOCKS_PER_DIMENSION", iNumberOfWaterBlocksPerDimension);
		CCodeMover::SetVariable("NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE", iNumberOfWaterBlocksPerDimension - 1);
		CCodeMover::SetVariable("TOTAL_NUMBER_OF_WATER_BLOCKS", iTotalNumberOfWaterBlocks);
	}
	#endif

	// Apply automatic patch
	#if TRUE
	{
		// Count of active addresses: 14
		CCodeMover::FixOnAddress(0x6E6CB2, 5, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_WATER_BLOCKS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\xd2\x6c\x6e\x00\x00", 0x6E6CB7);	// line 1, 0x6E6CA0 - _ZN11CWaterLevel8BlockHitEii : cmp     esi, 12
		CCodeMover::FixOnAddress(0x6E6CB7, 5, "\x01\x02\x81\xff\x05\x04NUMBER_OF_WATER_BLOCKS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\xd2\x6c\x6e\x00\x00", 0x6E6CBC);	// line 2, 0x6E6CA0 - _ZN11CWaterLevel8BlockHitEii : cmp     edi, 12
		CCodeMover::FixOnAddress(0x6E6CDA, 5, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x03\xe4\x6c\x6e\x00\x00", 0x6E6CDF);	// line 3, 0x6E6CA0 - _ZN11CWaterLevel8BlockHitEii : cmp     esi, 0Bh
		CCodeMover::FixOnAddress(0x6E6CDF, 5, "\x01\x02\x81\xff\x05\x04NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x03\x04\x6d\x6e\x00\x00", 0x6E6CE4);	// line 4, 0x6E6CA0 - _ZN11CWaterLevel8BlockHitEii : cmp     edi, 0Bh
		CCodeMover::FixOnAddress(0x6E85CF, 9, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_WATER_BLOCKS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\x33\x87\x6e\x00\x00", 0x6E85D8);	// line 5, 0x6E8580 - sub_6E8580 : cmp     esi, 0Ch
		CCodeMover::FixOnAddress(0x6E85E0, 9, "\x01\x01\x3d\x05\x04NUMBER_OF_WATER_BLOCKS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\x33\x87\x6e\x00\x00", 0x6E85E9);	// line 6, 0x6E8580 - sub_6E8580 : cmp     eax, 0Ch
		CCodeMover::FixOnAddress(0x6EF796, 5, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_WATER_BLOCKS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\xf7\xf7\x6e\x00\x00", 0x6EF79B);	// line 7, 0x6EF650 - sub_6EF650 : cmp     esi, 0Ch
		CCodeMover::FixOnAddress(0x6EF79B, 5, "\x01\x02\x81\xff\x05\x04NUMBER_OF_WATER_BLOCKS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\xf7\xf7\x6e\x00\x00", 0x6EF7A0);	// line 8, 0x6EF650 - sub_6EF650 : cmp     edi, 0Ch
		CCodeMover::FixOnAddress(0x6EF7B4, 5, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x85\x03\xcb\xf7\x6e\x00\x00", 0x6EF7B9);	// line 9, 0x6EF650 - sub_6EF650 : cmp     esi, 0Bh
		CCodeMover::FixOnAddress(0x6EF7D9, 5, "\x01\x02\x81\xff\x05\x04NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x85\x03\xf3\xf7\x6e\x00\x00", 0x6EF7DE);	// line 10, 0x6EF650 - sub_6EF650 : cmp     edi, 0Bh
		CCodeMover::FixOnAddress(0x6EFE8F, 6, "\x01\x03\x66\x81\xf9\x05\x02NUMBER_OF_WATER_BLOCKS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\xac\xfe\x6e\x00\x00", 0x6EFE95);	// line 11, 0x6EF650 - sub_6EF650 : cmp     cx, 0Ch
		CCodeMover::FixOnAddress(0x6EFEA2, 10, "\x01\x02\x66\x3d\x05\x02NUMBER_OF_WATER_BLOCKS_PER_DIMENSION\x00\x01\x02\x0F\x8C\x03\x56\x00\x6f\x00\x00", 0x6EFEAC);	// line 12, 0x6EF650 - sub_6EF650 : cmp     ax, 0Ch
		CCodeMover::FixOnAddress(0x6E633A, 6, "\x01\x02\x81\xfd\x05\x04TOTAL_NUMBER_OF_WATER_BLOCKS\x00\x00", 0x6E6340);	// line 13, 0x6E61B0 - sub_6E61B0 : cmp     ebp, 144
		CCodeMover::FixOnAddress(0x6E634E, 9, "\x01\x02\x81\xfb\x05\x04NUMBER_OF_WATER_BLOCKS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x03\x62\x66\x6e\x00\x00", 0x6E6357);	// line 14, 0x6E61B0 - sub_6E61B0 : cmp     ebx, 12
	}
	#endif

	// Unset variables of automatic patch
	#if TRUE
	{
		CCodeMover::DeleteVariable("NUMBER_OF_WATER_BLOCKS_PER_DIMENSION");
		CCodeMover::DeleteVariable("NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE");
		CCodeMover::DeleteVariable("TOTAL_NUMBER_OF_WATER_BLOCKS");
	}
	#endif
	#endif
}

///// patches /////
namespace Game_GTAIV
{
	static uint32_t Address_93EE2E = NULL;

	NAKED void patch_CWaterLevel__AddToQuadsAndTrianglesList_93EE28()
	{
		__asm
		{
			imul	eax, [iNumberOfWaterBlocksPerDimension];
			add     ecx, eax;

			// go back
			jmp[Address_93EE2E];
		}
	}

	unsigned int Address_941EA2 = NULL;

	NAKED void patch_CWaterLevel__GetWaterLevelNoWaves_941E9C()
	{
		__asm
		{
			imul	eax, [iNumberOfWaterBlocksPerDimension];
			add     ecx, eax;

			// go back
			jmp Address_941EA2;
		}
	}

	unsigned int Address_941347 = NULL;

	NAKED void patch_CWaterLevel__MarkQuadsAndPolysToBeRendered_941340()
	{
		__asm
		{
			imul eax, [iNumberOfWaterBlocksPerDimension];
			push esi;
			lea     edx, [ecx + eax];

			// go back
			jmp Address_941347;
		}
	}

	unsigned int Address_942198 = NULL;

	NAKED void patch_CWaterLevel__TestLineAgainstWater_942191()
	{
		__asm
		{
			mov eax, ecx;
			imul eax, [iNumberOfWaterBlocksPerDimension];

			// go back
			jmp Address_942198;
		}
	}

	unsigned int Address_942590 = NULL;

	NAKED void patch_CWaterLevel__TestLineAgainstWater_94258B()
	{
		__asm
		{
			mov eax, [iNumberOfWaterBlocksPerDimension];
			add[esp + 50h - 0x34], eax;

			// go back
			jmp Address_942590;
		}

	}
}

// Patches water map size
void MapLimits::PatchWaterMapSize_GTA_IV_1_0_7_0()
{
	using namespace Game_GTAIV;

	if (CPatch::IsDebugModeActive())
		MapLimits::ms_waterMapSize = 6000;

	if (!this->PatchWaterMapSize_DoInitialisingWork())
		return;

	#if FALSE

	// Multiply by 12
	#if TRUE
	{
		CPatch::RedirectCode(0x6E5758, &patch_CWaterLevel__AddToQuadsAndTrianglesList_6E5758);
		CPatch::RedirectCode(0x6E85E9, &patch_CWaterLevel__GetWaterLevelNoWaves_6E85E9);
		CPatch::RedirectCode(0x6E5818, &patch_CWaterLevel__MarkQuadsAndPolysToBeRendered_6E5818);
		CPatch::RedirectCode(0x6E6318, &patch_CWaterLevel__TestLineAgainstWater_6E6318);
	}
	#endif
	#else

	// Debug code
	#if FALSE
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		// CPatch::PatchFloat(0x859A90, fWaterMapMinCoord);
		// CPatch::PatchFloat(0x859A94, fWaterMapMaxCoord);
		// CPatch::PatchFloat(0x858B44, fNumberOfWaterBlocksPerDimensionHalf);
		CPatch::NOPinstructions(0x6E6CFF, 5);
		CPatch::RedirectFunction(0x6E6D10, &patch_CWaterLevel__ScanThroughBlocks);
		CPatch::LeaveThisLevel();
	}
	#endif		



	// Patch pointers to CWaterLevel::m_QuadsAndTrianglesInEachBlock
	#if TRUE
	{
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x93E8E8 + 1), CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// mov     edi, offset _ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE; CWaterLevel::m_QuadsAndTrianglesInEachBlock	; _ZN11CWaterLevel4InitEv
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x93EE2E + 4), CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// movzx   edx, _ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE[ecx*2]; CWaterLevel::m_QuadsAndTrianglesInEachBlock	; _ZN11CWaterLevel26AddToQuadsAndTrianglesListEiiij
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x93EE4A + 4), CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// mov     _ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE[ecx*2], dx; CWaterLevel::m_QuadsAndTrianglesInEachBlock	; _ZN11CWaterLevel26AddToQuadsAndTrianglesListEiiij
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x93EEC4 + 4), CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// mov     _ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE[ecx*2], dx; CWaterLevel::m_QuadsAndTrianglesInEachBlock	; _ZN11CWaterLevel26AddToQuadsAndTrianglesListEiiij
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x941348 + 4), CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// movzx   edi, _ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE[edx*2]; CWaterLevel::m_QuadsAndTrianglesInEachBlock	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x941EA2 + 4), CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// movzx   eax, _ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE[ecx*2]; CWaterLevel::m_QuadsAndTrianglesInEachBlock	; _ZN11CWaterLevel20GetWaterLevelNoWavesEfffPfS0_S0_
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9421C8 + 4), CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);	// movzx   eax, _ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE[ecx*2]; CWaterLevel::m_QuadsAndTrianglesInEachBlock	; _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_
	}
	#endif

	// Patch values
	#if TRUE
	{
		// CPatch::PatchFloat(0xD54D94, fNumberOfWaterBlocksPerDimensionHalf);

		/*
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::RedirectCode(0x9482AD, 0x9483C0);
		//CPatch::PatchUINT8(0x947930, 0xC3);	// CWaterLevel::RenderWater(void)
		//CPatch::PatchUINT8(0x945390, 0xC3);	// CWaterLevel::PreRenderWater
		//CPatch::PatchUINT8(0x944920, 0xC3);	// CWaterLevel::WaterLevelInitialise
		// CPatch::PatchUINT8(0x941330, 0xC3);	// CWaterLevel::MarkQuadsAndPolysToBeRendered
		CPatch::LeaveThisLevel();
		*/


		// CWaterLevel::AddToQuadsAndTrianglesList
		Address_93EE2E = g_mCalc.GetCurrentVAbyPreferedVA(0x93EE2E);
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x93EE28), &patch_CWaterLevel__AddToQuadsAndTrianglesList_93EE28);

		// CWaterLevel::AddWaterLevelVertex
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x93EFA0 + 4), &fWaterMapMinCoord);	// movss   xmm2, ds:flt_EBE168	; sub_93EFA0
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x93EFD0 + 4), &fWaterMapMaxCoord);	// movss   xmm3, ds:flt_EBE164	; sub_93EFA0
		CPatch::LeaveThisLevel();

		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x93EFBD + 1), iWaterMapMinCoord);	// mov     edi, 0FFFFF448h
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x93EFE4 + 1), iWaterMapMaxCoord);	// mov     edi, 3000
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x93EFFF + 1), iWaterMapMinCoord);	// mov     esi, 0FFFFF448h
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x93F016 + 1), iWaterMapMaxCoord);	// mov     esi, 3000

		// CWaterLevel::FillQuadsAndTrianglesList
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x941163 + 4), &fWaterMapMaxCoord);	// movss   xmm7, ds:fWorldMapMaxCoord
		CPatch::LeaveThisLevel();

		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x9412F1 + 1), ms_waterMapSize);	// cmp     eax, 6000
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x94130C + 1), ms_waterMapSize);	// cmp     eax, 6000

		// CWaterLevel::FindNearestWaterAndItsFlow(void)
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x94386A + 4), &fWaterMapMinCoord);	// movss   xmm0, ds:fWorldMapMinCoord				
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x943889 + 4), &fWaterMapMaxCoord);	// movss   xmm1, ds:fWorldMapMaxCoord
		CPatch::LeaveThisLevel();

		// CWaterLevel::GetWaterLevelNoWaves
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x941DFE + 4), &fNumberOfWaterBlocksPerDimensionHalf); // movss   xmm7, ds:fNumberOfWaterBlocksPerDimensionHalf
		CPatch::LeaveThisLevel();

		Address_941EA2 = g_mCalc.GetCurrentVAbyPreferedVA(0x941EA2);
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x941E9C), &patch_CWaterLevel__GetWaterLevelNoWaves_941E9C);

		// CWaterLevel::Init
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x93E8E3 + 1), (iTotalNumberOfWaterBlocks * sizeof(WORD)) / sizeof(DWORD));

		// CWaterLevel::MarkQuadsAndPolysToBeRendered
		Address_941347 = g_mCalc.GetCurrentVAbyPreferedVA(0x941347);
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x941340), &patch_CWaterLevel__MarkQuadsAndPolysToBeRendered_941340);

		#if FALSE
		// CWaterLevel::RenderDetailedSeaBedSegment
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(0x6E6AED + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6E6B0F + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6E6B88 + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6E6BD0 + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::LeaveThisLevel();

		// CWaterLevel::RenderSeaBedSegment
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchPointer(0x6E68BA + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6E68D6 + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6E6924 + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x6E696C + 2, &fWaterMapMaxCoord);	// fsub    ds:flt_859A94				
		CPatch::LeaveThisLevel();
		#endif			

		// CWaterLevel::RenderWater
		{
			CPatch::EnterNewLevelAndDisableDebugState();

			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9482B3 + 4), &fWaterMapMaxCoord);	// movss   xmm1, ds:fWorldMapMaxCoord
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x94838C + 4), &fWaterMapMaxCoord);	// movss   xmm1, ds:fWorldMapMaxCoord

			CPatch::LeaveThisLevel();
		}


		// CWaterLevel::ScanThroughBlocks
		CPatch::EnterNewLevelAndDisableDebugState();
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x943263 + 4), &fNumberOfWaterBlocksPerDimensionHalf);	// movss   xmm3, ds:fNumberOfWaterBlocksPerDimensionHalf
		}
		CPatch::LeaveThisLevel();


		// CWaterLevel::TestLineAgainstWater

		{
			CPatch::EnterNewLevelAndDisableDebugState();

			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x94213B + 4), &fNumberOfWaterBlocksPerDimensionHalf);	// movss   xmm2, ds:fNumberOfWaterBlocksPerDimensionHalf
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x942507 + 4), &fNumberOfWaterBlocksPerDimensionHalf);	// movss   xmm2, ds:fNumberOfWaterBlocksPerDimensionHalf

			CPatch::LeaveThisLevel();
		}

		Address_942198 = g_mCalc.GetCurrentVAbyPreferedVA(0x942198);
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x942191), &patch_CWaterLevel__TestLineAgainstWater_942191);

		Address_942590 = g_mCalc.GetCurrentVAbyPreferedVA(0x942590);
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x94258B), &patch_CWaterLevel__TestLineAgainstWater_94258B);

	}
	#endif

	// Set variables for automatic patch
	#if TRUE
	{
		CCodeMover::SetVariable("NUMBER_OF_WATER_BLOCKS_PER_DIMENSION", iNumberOfWaterBlocksPerDimension);
		CCodeMover::SetVariable("NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE", iNumberOfWaterBlocksPerDimension - 1);
		CCodeMover::SetVariable("TOTAL_NUMBER_OF_WATER_BLOCKS", iTotalNumberOfWaterBlocks);
	}
	#endif

	// Apply automatic patch
	#if TRUE
	{
		// Count of active addresses: 10
		CCodeMover::FixOnAddressRel(0x941E5A, 7, "\x01\x01\x3d\x05\x04""NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE\x00\x02\x04\x5D\x1E\x94\x00\x00", 0x941E61);	// line 1, 0x941DF0 - _ZN11CWaterLevel20GetWaterLevelNoWavesEfffPfS0_S0_ : cmp     eax, 11
		CCodeMover::FixOnAddressRel(0x941E93, 9, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x87\x0F\x73\x20\x94\x00\x00", 0x941E9C);	// line 2, 0x941DF0 - _ZN11CWaterLevel20GetWaterLevelNoWavesEfffPfS0_S0_ : cmp     ecx, 11
		CCodeMover::FixOnAddressRel(0x9421B0, 9, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x87\x0F\x90\x24\x94\x00\x00", 0x9421B9);	// line 3, 0x9420B0 - _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_ : cmp     ecx, 11
		CCodeMover::FixOnAddressRel(0x9421B9, 9, "\x01\x01\x3d\x05\x04""NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x87\x0F\x90\x24\x94\x00\x00", 0x9421C2);	// line 4, 0x9420B0 - _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_ : cmp     eax, 11
		CCodeMover::FixOnAddressRel(0x942E62, 5, "\x01\x02\x81\xfe\x05\x04""NUMBER_OF_WATER_BLOCKS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x0F\x78\x2e\x94\x00\x00", 0x942E67);	// line 5, 0x942E50 - _ZN11CWaterLevel8BlockHitEii : cmp     esi, 0Ch
		CCodeMover::FixOnAddressRel(0x942E67, 5, "\x01\x02\x81\xff\x05\x04""NUMBER_OF_WATER_BLOCKS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x0F\x78\x2e\x94\x00\x00", 0x942E6C);	// line 6, 0x942E50 - _ZN11CWaterLevel8BlockHitEii : cmp     edi, 0Ch
		CCodeMover::FixOnAddressRel(0x942E80, 5, "\x01\x02\x81\xfe\x05\x04""NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x0F\x8a\x2e\x94\x00\x00", 0x942E85);	// line 7, 0x942E50 - _ZN11CWaterLevel8BlockHitEii : cmp     esi, 11
		CCodeMover::FixOnAddressRel(0x942E85, 5, "\x01\x02\x81\xff\x05\x04""NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x0F\xde\x2e\x94\x00\x00", 0x942E8A);	// line 8, 0x942E50 - _ZN11CWaterLevel8BlockHitEii : cmp     edi, 11
		CCodeMover::FixOnAddressRel(0x9482DB, 6, "\x01\x03\x66\x81\xfa\x05\x02""NUMBER_OF_WATER_BLOCKS_PER_DIMENSION\x00\x01\x02\x0F\x8D\x0F\xf7\x82\x94\x00\x00", 0x9482E1);	// line 9, 0x947930 - _ZN11CWaterLevel11RenderWaterEv : cmp     dx, 12
		CCodeMover::FixOnAddressRel(0x9482ED, 10, "\x01\x03\x66\x81\xfb\x05\x02""NUMBER_OF_WATER_BLOCKS_PER_DIMENSION\x00\x01\x02\x0F\x8C\x0F\x97\x83\x94\x00\x00", 0x9482F7);	// line 10, 0x947930 - _ZN11CWaterLevel11RenderWaterEv : cmp     bx, 12
	}
	#endif

	// Unset variables of automatic patch
	#if TRUE
	{
		CCodeMover::DeleteVariable("NUMBER_OF_WATER_BLOCKS_PER_DIMENSION");
		CCodeMover::DeleteVariable("NUMBER_OF_WATER_BLOCKS_PER_DIMENSION_MINUS_ONE");
		CCodeMover::DeleteVariable("TOTAL_NUMBER_OF_WATER_BLOCKS");
	}
	#endif
	#endif
}
#endif

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
namespace Game_GTASA
{
	// Automatic patches
	#include "WaterMapSizeLimits/GTA SA 2.0 ANDROID_ARMEABI_V7A/functions.cpp"
}

// Patches water map size
void MapLimits::PatchWaterMapSize_GTA_SA_2_0_ANDROID_ARM32()
{
	using namespace Game_GTASA;

	if (CPatch::IsDebugModeActive())
		ms_waterMapSize = 6000;

	if (!this->PatchWaterMapSize_DoInitialisingWork())
		return;

	// Patch pointers to CWaterLevel::m_QuadsAndTrianglesInEachBlock
	CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x5CDE54), CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr);

	// Automatic patches
	#if TRUE
	{
		#include "WaterMapSizeLimits/GTA SA 2.0 ANDROID_ARMEABI_V7A/changes.cpp"
	}
	#endif
}
#endif

// Patches water map size
void MapLimits::PatchWaterMapSize()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		this->PatchWaterMapSize_GTA_SA_PC_1_0_HOODLUM();
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		this->PatchWaterMapSize_GTA_IV_1_0_7_0();
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		this->PatchWaterMapSize_GTA_SA_2_0_ANDROID_ARM32();
	#endif

	CPatch::LeaveThisLevel();
}

// Checks contraints
void MapLimits::CheckConstraints()
{
	MAKE_VAR_GAME_VERSION();

	if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
		&& this->ms_worldMapSize > this->ms_rwWorldMapSize)
		throw f92_runtime_error(
			"Renderware world map size should have higher value than World map size\n"
			"\nCurrent values:\n"
			"Renderware world map size = %d\n"
			"World map size = %d",

			this->ms_rwWorldMapSize,
			this->ms_worldMapSize
		);

	if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
	{
		unsigned int expectedWorldSectorSize = MapLimits::ms_worldMapSize / 120;

		if (MapLimits::ms_worldSectorSize != expectedWorldSectorSize)
			throw f92_runtime_error(
				"For GTA IV modifying a number of world sectors is currently unsupported\n"
				"\nYou need to set:\n"
				"World sector size = %d",

				expectedWorldSectorSize
			);

		unsigned int expectedWorldLODsectorSize = MapLimits::ms_worldMapSize / 30;

		if (MapLimits::ms_worldLODsectorSize != expectedWorldLODsectorSize)
			throw f92_runtime_error(
				"For GTA IV modifying a number of world LOD sectors is currently unsupported\n"
				"\nYou need to set:\n"
				"World LOD sector size = %d",

				expectedWorldLODsectorSize
			);
	}

	#if FLA_DEPRECATED
	if (MapLimits::ms_bPathDebuggingEnabled && !MapLimits::ms_bPathsPatchEnabled)
		throw f92_runtime_error("Path debugging requires paths patch enabled.");
	#endif
}

static CVector** pNaviNodePositions = NULL;
static unsigned int TimeOfLastNaviNodeUpdate = 0;

// Initializes map changes
void MapLimits::InitChanges()
{
}

// Commits changes
void MapLimits::CommitChanges()
{
	if (this->ms_bPathsPatchEnabled)
		CGenericLogStorage::SaveFormattedTextLn(
			"Paths limit patch enabled.\n"
			"Paths map size set to %d x %d",
			this->ms_pathsMapSize,
			this->ms_pathsMapSize
		);

	this->CheckConstraints();

	if (this->ms_bRadarLimitSet)
		PatchRadarSize();

	if (this->ms_bIsFrontentMapDifferent)
		PatchFrontendMapDifferent();

	if (MapLimits::ms_bRadarTextureArrayReallocated)
		PatchReferencesToRadarTextures();

	if (this->ms_bWaterLimitSet)
		PatchWaterMapSize();

	if (this->ms_bRwWorldMapSizeLimitSet)
		PatchRwWorldMapSize();

	if (this->ms_bWorldSectorLimitSet)
		PatchWorldSectors();

	if (this->ms_bPathsPatchEnabled)
		PatchPaths();

	if (this->ms_bPathDebuggingEnabled)
		ApplyPathDebugging();

	// tracks.dat related stuff
	if (this->ms_bTracksDatCoordinateLimitPatchEnabled)
		PatchTracksDatCoordinateLimit();

	if (this->ms_bTracksDatFileSizeLimitSet)
		PatchTracksDatFileSizeLimit();

	if (this->ms_bMaxNumberOfTrainStationsLimitSet)
		PatchMaxNumberOfTrackStations();

	if (this->ms_bNumberOfTracksDatFilesSet)
		PatchNumberOfTracksDatFiles();

	#if PROJECT_USE_DEVELOPMENT_INI
	PatchLeftSidedTraffic();
	#endif

	CGenericLogStorage::WriteLineSeparator();
}

extern "C"
{
	int numberOfRadarTilesPerOneDimension;
	int iNumberOfRadarTilesPerOneDimensionHalf;
	float fNumberOfRadarTilesPerOneDimensionMinusOne;
	float fRadarMapMinCoord;
	float fRadarMapMaxCoord;
	float fRadarRange;		// 2990.0 by default
	float fNumberOfRadarTilesPerOneDimensionHalfInversed;


	int numberOfZoneRevealedBlocksPerOneDimension;
	int iNumberOfZoneRevealedBlocksPerOneDimensionHalf;
	float fNumberOfZoneRevealedBlocksPerOneDimensionHalfInversed;
	int iPositionOfZoneRevealedBlockOfDefaultMap;

	float fMaxMapZoomValue;
	float fKeyAddMapZoomValue;
	float fMouseAddMapZoomValue;
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	void NAKED patch_radar_584B7B()
	{
		__asm
		{
			imul	ecx, [numberOfRadarTilesPerOneDimension];
			lea     eax, [eax + ecx];

			// go back
			push 0x584B81;
			retn;
		}
	}

	void NAKED patch_radar_584BCA()
	{
		__asm
		{
			imul	eax, [numberOfRadarTilesPerOneDimension];
			lea     eax, [ecx + eax];

			// go back
			push 0x584BD0;
			retn;
		}
	}

	void NAKED patch_radar_586172()
	{
		__asm
		{
			mov		ecx, ebp;
			imul	ecx, [numberOfRadarTilesPerOneDimension];
			lea     eax, [esi + ecx]

				// go back
				push 0x586179;
			retn;
		}
	}

	void NAKED patch_radar_586551()
	{
		__asm
		{
			imul	eax, [numberOfRadarTilesPerOneDimension];
			lea     eax, [edx + eax];

			// go back
			push 0x586557;
			retn;
		}
	}

	void NAKED patch_CRadar__SetupRadarRect()
	{

		__asm
		{
			mov ecx, [esp + 4];
			mov edx, [esp + 8];

			sub ecx, [iNumberOfRadarTilesPerOneDimensionHalf];
			mov eax, [iNumberOfRadarTilesPerOneDimensionHalf];
			dec eax;

			// go back
			push 0x584A90;
			retn;
		}
	}

	void NAKED patch_radar_584D90()
	{
		__asm
		{
			mov edx, [esp + 4];
			mov eax, [esp + 8];

			sub edx, [iNumberOfRadarTilesPerOneDimensionHalf];
			imul    edx, 500;

			mov ecx, [iNumberOfRadarTilesPerOneDimensionHalf];
			dec ecx;

			// go back
			push 0x584DA6;
			retn;
		}
	}

	// CMenuManager__PrintMap patches
	NAKED void patch_CMenuManager__PrintMap_575AA0()
	{
		__asm
		{
			mov edx, [esp + 0x64 - 0x3C];
			add edx, [iPositionOfZoneRevealedBlockOfDefaultMap];
			mov[esp + 0x64 - 0x18], edx;
			fild[esp + 0x64 - 0x18];

			// go back
			push 0x575AAE;
			retn;
		}
	}

	NAKED void patch_CMenuManager__PrintMap_575ACF()
	{
		__asm
		{
			mov edx, [esp + 0x74 - 0x40];
			add edx, [iPositionOfZoneRevealedBlockOfDefaultMap];
			mov[esp + 0x74 - 0x18], edx;

			fild[esp + 0x74 - 0x18];
			fmul st(0), st(1);

			// go back
			push 0x575AD5;
			retn;
		}
	}

	NAKED void patch_CMenuManager__PrintMap_575ADF()
	{
		__asm
		{
			lea     edx, [ebp + 1];
			add edx, [iPositionOfZoneRevealedBlockOfDefaultMap];
			mov[esp + 0x74 - 0x18], edx;
			fild[esp + 0x74 - 0x18];

			lea     edx, [esi + 1];
			add edx, [iPositionOfZoneRevealedBlockOfDefaultMap];
			mov[esp + 0x74 - 0x18], edx;

			// go back
			push 0x575AE7;
			retn;
		}
	}
}

// Patches radar size
void MapLimits::PatchRadarSize_GTA_SA_PC_1_0()
{
	using namespace Game_GTASA;

	if (CPatch::IsDebugModeActive())
		this->ms_radarMapSize = 6000;
	else if (this->ms_radarMapSize > 6000)
		this->ms_bRadarTextureArrayReallocated = true;

	// validate
	if (!ValidateMapSizeOrShowMessage(this->ms_radarMapSize, "Radar"))
		return;

	////////
	const bool bSupportNewZonesRevealedSize = false;

	////////
	// radar
	numberOfRadarTilesPerOneDimension = this->ms_radarMapSize / this->ms_radarBlockSize;
	iNumberOfRadarTilesPerOneDimensionHalf = numberOfRadarTilesPerOneDimension / 2;
	fNumberOfRadarTilesPerOneDimensionMinusOne = (float)numberOfRadarTilesPerOneDimension - 1;
	int iRadarMapMaxCoord = MapLimits::ms_radarMapSize / 2;
	int iRadarMapMinCoord = -iRadarMapMaxCoord;

	fRadarMapMaxCoord = (float)MapLimits::ms_radarMapSize / 2;
	fRadarMapMinCoord = -fRadarMapMaxCoord;
	fRadarRange = (float)(fRadarMapMaxCoord - ((fRadarMapMaxCoord / 3000.0) * 10.0));
	fNumberOfRadarTilesPerOneDimensionHalfInversed = (float)1.0 / iNumberOfRadarTilesPerOneDimensionHalf;

	// zones revealed
	numberOfZoneRevealedBlocksPerOneDimension = MapLimits::ms_radarMapSize / MapLimits::ms_zoneRevealedBlockSize;
	iNumberOfZoneRevealedBlocksPerOneDimensionHalf = numberOfZoneRevealedBlocksPerOneDimension / 2;
	fNumberOfZoneRevealedBlocksPerOneDimensionHalfInversed = (float)1.0 / iNumberOfZoneRevealedBlocksPerOneDimensionHalf;
	iPositionOfZoneRevealedBlockOfDefaultMap = iNumberOfZoneRevealedBlocksPerOneDimensionHalf - 5;

	//  printf_MessageBox("var: %.3f", fNumberOfZoneRevealedBlocksPerOneDimensionHalfInversed);

	// zoom
	fMaxMapZoomValue = (float)(fRadarMapMaxCoord / 3000.0 * 1100.0);
	fKeyAddMapZoomValue = (float)(fRadarMapMaxCoord / 3000.0 * 7.0);
	fMouseAddMapZoomValue = (float)(fRadarMapMaxCoord / 3000.0 * 21.0);

	////////
	const int totalNumberOfTiles = numberOfRadarTilesPerOneDimension * numberOfRadarTilesPerOneDimension;

	CGenericLogStorage::SaveFormattedTextLn(
		"\nRadar info:\n"
		"Number of radar tiles per dimension: %d\n"
		"Total number of radar tiles: %d",

		numberOfRadarTilesPerOneDimension,
		totalNumberOfTiles
	);

	// Patch values
	#if TRUE
	{
		// Set variables
		CCodeMover::SetVariable(
			"NUMBER_OF_RADAR_TILES_PER_DIMENSION",
			numberOfRadarTilesPerOneDimension
		);

		CCodeMover::SetVariable(
			"NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE",
			numberOfRadarTilesPerOneDimension - 1
		);

		CCodeMover::SetVariable(
			"SIZE_OF_RADAR_IDS_FOR_ONE_DIMENSION_IN_ARRAY",
			numberOfRadarTilesPerOneDimension * 4
		);

		CCodeMover::SetVariable(
			"TOTAL_NUMBER_OF_RADAR_TILES",
			totalNumberOfTiles
		);

		////////

		CPatch::RedirectCode(0x584B7B, &patch_radar_584B7B);
		CPatch::RedirectCode(0x584BCA, &patch_radar_584BCA);
		CPatch::RedirectCode(0x586172, &patch_radar_586172);
		CPatch::RedirectCode(0x586551, &patch_radar_586551);
		CPatch::RedirectCode(0x584A80, &patch_CRadar__SetupRadarRect);
		CPatch::RedirectCode(0x584D90, &patch_radar_584D90);


		CPatch::PatchUINT32(0x584C9E + 1, numberOfRadarTilesPerOneDimension - 1);		// mov     eax, 0Bh
		CPatch::PatchUINT32(0x584CA9 + 2, totalNumberOfTiles - numberOfRadarTilesPerOneDimension);		// cmp     esi, 132
		CPatch::PatchUINT32(0x584CE9 + 2, totalNumberOfTiles - numberOfRadarTilesPerOneDimension);		// cmp     esi, 132

		CPatch::PatchUINT32(0x586343 + 1, numberOfRadarTilesPerOneDimension);	// mov     ecx, 12

		CPatch::PatchUINT32(0x588035 + 2, totalNumberOfTiles);

		CPatch::PatchUINT32(0x573D3D + 4, numberOfRadarTilesPerOneDimension);	// mov     [esp+30h+var_8], 12
		CPatch::PatchUINT32(0x573D7C + 1, numberOfRadarTilesPerOneDimension);	// mov     [esp+30h+var_8], 12

		CPatch::PatchUINT32(0x58361B + 1, numberOfRadarTilesPerOneDimension);

		CPatch::EnterNewLevelAndDisableDebugState();
		{
			CPatch::PatchPointer(0x585905 + 2, &fNumberOfRadarTilesPerOneDimensionMinusOne);	// fsubr   ds:flt_858FBC
			CPatch::PatchPointer(0x5868CA + 2, &fNumberOfRadarTilesPerOneDimensionMinusOne);	// fsubr   ds:flt_858FBC				

			CPatch::PatchPointer(0x573D28 + 2, &fNumberOfRadarTilesPerOneDimensionHalfInversed);	// fmul    ds:flt_85F0A0
			CPatch::PatchPointer(0x575255 + 2, &fNumberOfRadarTilesPerOneDimensionHalfInversed);	// fmul    ds:flt_85F0A0
			CPatch::PatchPointer(0x583432 + 2, &fNumberOfRadarTilesPerOneDimensionHalfInversed);	// fmul    ds:flt_85F0A0

			CPatch::PatchPointer(0x575262 + 2, &fNumberOfZoneRevealedBlocksPerOneDimensionHalfInversed);	// fmul    ds:flt_858CC4   ; 0.02

		}
		CPatch::LeaveThisLevel();

		// Automatic patches
		#if TRUE
		{
			// Count of active addresses: 17
			CCodeMover::FixOnAddress(0x584C18, 5, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8F\x03\x32\x4c\x58\x00\x00", 0x584C1D);	// line 1, 0x584BF0 - sub_584BF0 : cmp     esi, 0Bh
			CCodeMover::FixOnAddress(0x584C33, 6, "\x01\x02\x81\xc7\x05\x04SIZE_OF_RADAR_IDS_FOR_ONE_DIMENSION_IN_ARRAY\x00\x01\x02\x81\xfe\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION\x00\x00", 0x584C39);	// line 2, 0x584BF0 - sub_584BF0 : add     edi, 30h
			CCodeMover::FixOnAddress(0x584B5E, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8E\x03\x6a\x4b\x58\x00\x00", 0x584B63);	// line 3, 0x584B50 - sub_584B50 : cmp     eax, 0Bh
			CCodeMover::FixOnAddress(0x584B63, 5, "\x01\x01\xb8\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x584B68);	// line 4, 0x584B50 - sub_584B50 : mov     eax, 0Bh
			CCodeMover::FixOnAddress(0x584B72, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8F\x03\xa3\x4b\x58\x00\x00", 0x584B77);	// line 5, 0x584B50 - sub_584B50 : cmp     ecx, 0Bh
			CCodeMover::FixOnAddress(0x584BB8, 5, "\x01\x02\x81\xf9\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8F\x03\xe3\x4b\x58\x00\x00", 0x584BBD);	// line 6, 0x584BB0 - sub_584BB0 : cmp     ecx, 0Bh
			CCodeMover::FixOnAddress(0x584BC5, 5, "\x01\x01\x3d\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8F\x03\xe3\x4b\x58\x00\x00", 0x584BCA);	// line 7, 0x584BB0 - sub_584BB0 : cmp     eax, 0Bh
			CCodeMover::FixOnAddress(0x584D0B, 7, "\x01\x02\x81\xc6\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION\x00\x02\x01\x0E\x4D\x58\x00\x01\x02\x81\xc5\x05\x04SIZE_OF_RADAR_IDS_FOR_ONE_DIMENSION_IN_ARRAY\x00\x00", 0x584D12);	// line 8, 0x584C50 - sub_584C50 : add     esi, 0Ch
			CCodeMover::FixOnAddress(0x584D12, 6, "\x01\x02\x81\xfe\x05\x04TOTAL_NUMBER_OF_RADAR_TILES\x00\x00", 0x584D18);	// line 9, 0x584C50 - sub_584C50 : cmp     esi, 144
			CCodeMover::FixOnAddress(0x586140, 5, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8E\x03\x4a\x61\x58\x00\x00", 0x586145);	// line 10, 0x586110 - sub_586110 : cmp     esi, 0Bh
			CCodeMover::FixOnAddress(0x586155, 5, "\x01\x02\x81\xfd\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8E\x03\x61\x61\x58\x00\x00", 0x58615A);	// line 11, 0x586110 - sub_586110 : cmp     ebp, 0Bh
			CCodeMover::FixOnAddress(0x58652D, 5, "\x01\x02\x81\xfa\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8E\x03\x34\x65\x58\x00\x00", 0x586532);	// line 12, 0x586520 - sub_586520 : cmp     edx, 0Bh
			CCodeMover::FixOnAddress(0x586540, 9, "\x01\x01\x3d\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8F\x03\x40\x66\x58\x00\x00", 0x586549);	// line 13, 0x586520 - sub_586520 : cmp     eax, 0Bh
			CCodeMover::FixOnAddress(0x5756F5, 7, "\x01\x02\x81\xfe\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION\x00\x02\x04\xF8\x56\x57\x00\x00", 0x5756FC);	// line 14, 0x575130 - _ZN12CMenuManager8PrintMapEv : cmp     esi, 0Ch
			CCodeMover::FixOnAddress(0x575703, 7, "\x01\x02\x81\xfb\x05\x04NUMBER_OF_RADAR_TILES_PER_DIMENSION\x00\x02\x04\x06\x57\x57\x00\x00", 0x57570A);	// line 15, 0x575130 - _ZN12CMenuManager8PrintMapEv : cmp     ebx, 0Ch
		}
		#endif

		/////
		// Unset variables
		CCodeMover::DeleteVariable("NUMBER_OF_RADAR_TILES_PER_DIMENSION");

		CCodeMover::DeleteVariable("NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE");

		CCodeMover::DeleteVariable("SIZE_OF_RADAR_IDS_FOR_ONE_DIMENSION_IN_ARRAY");

		CCodeMover::DeleteVariable("TOTAL_NUMBER_OF_RADAR_TILES");
	}
	#endif

	// New zones revealed size
	#if TRUE
	{
		if (bSupportNewZonesRevealedSize)
		{

		}
		else
		{
			CPatch::RedirectCode(0x575AA0, &patch_CMenuManager__PrintMap_575AA0);
			CPatch::RedirectCode(0x575ACF, &patch_CMenuManager__PrintMap_575ACF);
			CPatch::RedirectCode(0x575ADF, &patch_CMenuManager__PrintMap_575ADF);
		}
	}
	#endif

	// Patch coordinates
	#if TRUE
	{
		CPatch::EnterNewLevelAndDisableDebugState();

		CPatch::PatchPointer(0x5858D8 + 2, &fRadarMapMaxCoord);	// fadd    ds:flt_859A94
		CPatch::PatchPointer(0x5858F7 + 2, &fRadarMapMaxCoord);	// fadd    ds:flt_859A94

		CPatch::PatchPointer(0x586360 + 2, &fRadarMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x58636E + 2, &fRadarMapMaxCoord);	// fsub    ds:flt_859A94

		CPatch::PatchPointer(0x586892 + 2, &fRadarMapMaxCoord);	// fadd    ds:flt_859A94
		CPatch::PatchPointer(0x5868A1 + 2, &fRadarMapMaxCoord);	// fadd    ds:flt_859A94

		// 
		CPatch::PatchFloat(0x58598C + 6, fRadarRange);	// mov     _ZN6CRadar12m_radarRangeE, 2990.0 ; CRadar::m_radarRange
		//

		CPatch::PatchFloat(0x578824 + 1, fRadarMapMaxCoord);	// mov     edx, 3000.0

		CPatch::PatchPointer(0x578829 + 2, &fRadarMapMaxCoord);	// fcomp   ds:flt_859A94
		CPatch::PatchPointer(0x578854 + 2, &fRadarMapMaxCoord);	// fcomp   ds:flt_859A94


		CPatch::PatchPointer(0x578841 + 2, &fRadarMapMinCoord);	// fcomp   ds:flt_859A90
		CPatch::PatchPointer(0x578867 + 2, &fRadarMapMinCoord);	// fcomp   ds:flt_859A90

		CPatch::PatchFloat(0x57883C + 1, fRadarMapMinCoord);	// mov     ecx, -3000.0

		CPatch::PatchPointer(0x58362C + 2, &fRadarMapMaxCoord);	// fsub    ds:flt_859A94
		CPatch::PatchPointer(0x58363F + 2, &fRadarMapMaxCoord);	// fsub    ds:flt_859A94

		// patch zoom
		{
			CPatch::PatchFloat(0x57453A + 3, fMaxMapZoomValue);	// mov     dword ptr [esi+64h], 1100.0
			CPatch::PatchFloat(0x5776C8 + 3, fMaxMapZoomValue);	// mov     dword ptr [esi+64h], 1100.0

			CPatch::PatchPointer(0x574521 + 2, &fMaxMapZoomValue);	// fsub    ds:flt_864F94   ; 1100.0
			CPatch::PatchPointer(0x574534 + 2, &fMaxMapZoomValue);	// fadd    ds:flt_864F94   ; 1100.0
			CPatch::PatchPointer(0x574548 + 2, &fMaxMapZoomValue);	// fsub    ds:flt_864F94   ; 1100.0
			CPatch::PatchPointer(0x574551 + 2, &fMaxMapZoomValue);	// fadd    ds:flt_864F94   ; 1100.0
			CPatch::PatchPointer(0x577662 + 2, &fMaxMapZoomValue);	// fcomp   ds:flt_864F94   ; 1100.0

			////
			CPatch::PatchPointer(0x577679 + 2, &fKeyAddMapZoomValue);	// fadd    ds:flt_858F48
			CPatch::PatchPointer(0x5779A8 + 2, &fKeyAddMapZoomValue);	// fsub    ds:flt_858F48
			CPatch::PatchPointer(0x577E70 + 2, &fKeyAddMapZoomValue);	// fmul    ds:flt_858F48
			CPatch::PatchPointer(0x578320 + 2, &fKeyAddMapZoomValue);	// fmul    ds:flt_858F48
			CPatch::PatchPointer(0x5784B5 + 2, &fKeyAddMapZoomValue);	// fmul    ds:flt_858F48
			CPatch::PatchPointer(0x578650 + 2, &fKeyAddMapZoomValue);	// fmul    ds:flt_858F48

			CPatch::PatchPointer(0x577698 + 2, &fMouseAddMapZoomValue);	// fadd    ds:flt_8653E4
			CPatch::PatchPointer(0x5779C7 + 2, &fMouseAddMapZoomValue);	// fsub    ds:flt_8653E4
		}

		CPatch::LeaveThisLevel();

		// Zone coordinates
		#if TRUE
		{
			CPatch::PatchUINT32(0x5726D3 + 1, iRadarMapMinCoord); // mov     ebp, 0FFFFF448h
			CPatch::PatchUINT32(0x5726D8 + 1, iRadarMapMaxCoord);	// mov     edi, 3000
		}
		#endif
	}
	#endif
}

// Patches radar size
void MapLimits::PatchRadarSize_GTA_IV_or_EFLC()
{
	MAKE_VAR_GAME_VERSION();

	if (CPatch::IsDebugModeActive())
		this->ms_radarMapSize = 6000;

	// validate
	if (!ValidateMapSizeOrShowMessage(this->ms_radarMapSize, "Radar"))
		return;

	////////

	////////
	// radar
	numberOfRadarTilesPerOneDimension = MapLimits::ms_radarMapSize / MapLimits::ms_radarBlockSize;
	iNumberOfRadarTilesPerOneDimensionHalf = numberOfRadarTilesPerOneDimension / 2;
	fNumberOfRadarTilesPerOneDimensionMinusOne = (float)numberOfRadarTilesPerOneDimension - 1;
	int iRadarMapMaxCoord = MapLimits::ms_radarMapSize / 2;
	int iRadarMapMinCoord = -iRadarMapMaxCoord;

	fRadarMapMaxCoord = (float)MapLimits::ms_radarMapSize / 2;
	fRadarMapMinCoord = -fRadarMapMaxCoord;
	fRadarRange = (float)(fRadarMapMaxCoord - ((fRadarMapMaxCoord / 3000.0) * 10.0));
	fNumberOfRadarTilesPerOneDimensionHalfInversed = (float)1.0 / iNumberOfRadarTilesPerOneDimensionHalf;

	////////
	const int numberOfRadarVariations = 2;
	const int totalNumberOfTiles = numberOfRadarTilesPerOneDimension * numberOfRadarTilesPerOneDimension;

	CGenericLogStorage::SaveFormattedTextLn(
		"\nRadar info:\n"
		"Number of radar tiles per dimension: %d\n"
		"Total number of radar tiles: %d",

		numberOfRadarTilesPerOneDimension,
		totalNumberOfTiles
	);

	if (totalNumberOfTiles * numberOfRadarVariations > 288)
	{
		gRadarTextures.ptr = new int[totalNumberOfTiles * numberOfRadarVariations];
		gRadarTextures.bIsAllocated.Set(true);
	}

	// Set variables
	{
		CCodeMover::SetVariable(
			"RADAR_MAP_SIZE_INT",
			ms_radarMapSize);

		CCodeMover::SetVariable(
			"NUMBER_OF_RADAR_TILES_PER_DIMENSION",
			numberOfRadarTilesPerOneDimension
		);

		CCodeMover::SetVariable(
			"NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE",
			numberOfRadarTilesPerOneDimension - 1
		);

		CCodeMover::SetVariable(
			"SIZE_OF_RADAR_IDS_FOR_ONE_DIMENSION_IN_ARRAY",
			numberOfRadarTilesPerOneDimension * 4
		);

		CCodeMover::SetVariable(
			"TOTAL_NUMBER_OF_RADAR_TILES",
			totalNumberOfTiles
		);
	}

	// version specific stuff
	if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
	{
		// Patch references to gRadarTextures
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x4421D2 + 1), gRadarTextures.ptr);	// mov     edi, offset gRadarTextures	; sub_4421B0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x4421D9 + 6), gRadarTextures.ptr);	// mov     pRadarTextures, offset gRadarTextures	; sub_4421B0
		}
		#endif

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x4421CD + 1), totalNumberOfTiles * numberOfRadarVariations);	// mov     ecx, 288

			// Automatic patches
			#if TRUE
			{
				// Count of active addresses: 3
				CCodeMover::FixOnAddressRel(0x4421B4, 5, "\x01\x01\x68\x05\x04""TOTAL_NUMBER_OF_RADAR_TILES\x00\x00", 0x4421B9);	// line 1, 0x4421B0 - sub_4421B0 : push    144
				CCodeMover::FixOnAddressRel(0x4421BE, 7, "\x01\x01\x68\x05\x04""NUMBER_OF_RADAR_TILES_PER_DIMENSION\x00\x01\x01\x68\x05\x04""RADAR_MAP_SIZE_INT\x00\x00", 0x4421C5);	// line 2, 0x4421B0 - sub_4421B0 : push    12
			}
			#endif		
		}
		#endif
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
		// Patch references to gRadarTextures
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x4B1F12 + 1), gRadarTextures.ptr);	// mov     edi, offset gRadarTextures	; sub_4421B0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x4B1F19 + 6), gRadarTextures.ptr);	// mov     pRadarTextures, offset gRadarTextures	; sub_4421B0
		}
		#endif

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x4B1F0D + 1), totalNumberOfTiles * numberOfRadarVariations);	// mov     ecx, 288

			// Automatic patches
			#if TRUE
			{
				// Count of active addresses: 3
				CCodeMover::FixOnAddressRel(0x4B1EF4, 5, "\x01\x01\x68\x05\x04""TOTAL_NUMBER_OF_RADAR_TILES\x00\x00", 0x4B1EF9);	// line 1, 0x4B1EF0 - sub_4B1EF0 : push    144
				CCodeMover::FixOnAddressRel(0x4B1EFE, 7, "\x01\x01\x68\x05\x04""NUMBER_OF_RADAR_TILES_PER_DIMENSION\x00\x01\x01\x68\x05\x04""RADAR_MAP_SIZE_INT\x00\x00", 0x4B1F05);	// line 2, 0x4B1EF0 - sub_4B1EF0 : push    12
			}
			#endif		
		}
		#endif
	}

	// Unset variables
	{
		CCodeMover::DeleteVariable("RADAR_MAP_SIZE_INT");

		CCodeMover::DeleteVariable("NUMBER_OF_RADAR_TILES_PER_DIMENSION");

		CCodeMover::DeleteVariable("NUMBER_OF_RADAR_TILES_PER_DIMENSION_MINUS_ONE");

		CCodeMover::DeleteVariable("SIZE_OF_RADAR_IDS_FOR_ONE_DIMENSION_IN_ARRAY");

		CCodeMover::DeleteVariable("TOTAL_NUMBER_OF_RADAR_TILES");
	}

	// printf_MessageBox("number of tiles: %d", totalNumberOfTiles);
}
#endif

// Patches radar size
void MapLimits::PatchRadarSize()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	this->PatchRadarSize_GTA_SA_PC_1_0();
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
	this->PatchRadarSize_GTA_IV_or_EFLC();
	#endif

	CPatch::LeaveThisLevel();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	void __cdecl CRadar__InitialiseFrontend()
	{
		char name[16];

		int numberOfRadarTilesPerOneDimension = g_mapLimits.ms_radarMapSize / MapLimits::ms_radarBlockSize;
		const int totalNumberOfTiles = numberOfRadarTilesPerOneDimension * numberOfRadarTilesPerOneDimension;
		int* pFrontendRadarTextures = g_mapLimits.gRadarTextures.ptr + totalNumberOfTiles;

		for (int i = 0; i < totalNumberOfTiles; i++)
		{
			sprintf(name, "fradar%02d", i);

			pFrontendRadarTextures[i] =
				((int(__cdecl *)(const char *))0x731850)(
					name
					);		// CTxdStore::FindTxdSlot
		}
	}

	// Remoes all radar sections
	void CRadar__RemoveRadarSections()
	{
		int numberOfRadarTilesPerOneDimension = g_mapLimits.ms_radarMapSize / MapLimits::ms_radarBlockSize;
		const int totalNumberOfTiles = numberOfRadarTilesPerOneDimension * numberOfRadarTilesPerOneDimension;
		int totalNumberOfFiles = totalNumberOfTiles;

		for (int i = 0; i < totalNumberOfFiles; i++)
		{
			int TXD_ID = g_mapLimits.gRadarTextures.ptr[i];

			if (TXD_ID != -1)
				CStreaming::RemoveModel(TXD_ID + g_fileIDlimits.GetBaseID(FILE_TYPE_TXD));
		}
	}

	void CRadar__RequestMapSectionFrontend(int regionX, int regionY)
	{
		int numberOfRadarTilesPerOneDimension = g_mapLimits.ms_radarMapSize / MapLimits::ms_radarBlockSize;
		const int totalNumberOfTiles = numberOfRadarTilesPerOneDimension * numberOfRadarTilesPerOneDimension;
		int* pFrontendRadarTextures = g_mapLimits.gRadarTextures.ptr + totalNumberOfTiles;

		if (regionX >= 0 && regionX < numberOfRadarTilesPerOneDimension
			&& regionY >= 0 && regionY < numberOfRadarTilesPerOneDimension)
		{
			int TXD_ID = pFrontendRadarTextures[regionY * numberOfRadarTilesPerOneDimension + regionX];

			if (TXD_ID != -1)
				CStreaming::RequestModel(
					TXD_ID + g_fileIDlimits.GetBaseID(GENERAL_FILE_TYPE_TEXTURE_ARCHIVE),
					10);
		}
	}

	void CRadar__RemoveMapSectionFrontend(int regionX, int regionY)
	{
		int numberOfRadarTilesPerOneDimension = g_mapLimits.ms_radarMapSize / MapLimits::ms_radarBlockSize;
		const int totalNumberOfTiles = numberOfRadarTilesPerOneDimension * numberOfRadarTilesPerOneDimension;
		int* pFrontendRadarTextures = g_mapLimits.gRadarTextures.ptr + totalNumberOfTiles;

		if (regionX >= 0 && regionX < numberOfRadarTilesPerOneDimension
			&& regionY >= 0 && regionY < numberOfRadarTilesPerOneDimension)
		{
			int TXD_ID = pFrontendRadarTextures[regionY * numberOfRadarTilesPerOneDimension + regionX];

			if (TXD_ID != -1)
				CStreaming::RemoveModel(
					TXD_ID +
					g_fileIDlimits.GetBaseID(GENERAL_FILE_TYPE_TEXTURE_ARCHIVE));
		}
	}
}

// Patch frontend map to be different
void MapLimits::PatchFrontendMapDifferent_GTA_SA_PC_1_0()
{
	using namespace Game_GTASA;

	this->ms_bRadarTextureArrayReallocated = true;

	CPatch::RedirectCode(0x588041, &CRadar__InitialiseFrontend);
	CPatch::RedirectCode(0x584BF0, &CRadar__RemoveRadarSections);

	CPatch::PutCallFunction(0x573E04, &CRadar__RequestMapSectionFrontend);
	CPatch::PutCallFunction(0x573E0D, &CRadar__RemoveMapSectionFrontend);
}
#endif

// Patch frontend map to be different
void MapLimits::PatchFrontendMapDifferent()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	this->PatchFrontendMapDifferent_GTA_SA_PC_1_0();
	#endif
}

#ifdef IS_PLATFORM_WIN_X86
// Patches radar textures pointers
void MapLimits::PatchReferencesToRadarTextures_GTA_SA_PC_1_0()
{
	CPatch::EnterNewLevel();

	int numberOfRadarTilesPerOneDimension = ms_radarMapSize / ms_radarBlockSize;
	const int totalNumberOfTiles = numberOfRadarTilesPerOneDimension * numberOfRadarTilesPerOneDimension;
	int totalNumberOfFiles = totalNumberOfTiles;

	if (ms_bIsFrontentMapDifferent)
		totalNumberOfFiles *= 2;

	if (totalNumberOfFiles > 144)
	{
		gRadarTextures.ptr = new int[totalNumberOfFiles];
		gRadarTextures.bIsAllocated.Set(true);
	}

	int* pFrontendRadarTextures;

	if (ms_bIsFrontentMapDifferent)
		pFrontendRadarTextures = gRadarTextures.ptr + totalNumberOfTiles;
	else
		pFrontendRadarTextures = gRadarTextures.ptr;

	#if TRUE
	{
		CPatch::PatchPointer(0x401C33 + 1, gRadarTextures.ptr);	// mov     ebx, offset gRadarTextures

		CPatch::PatchPointer(0x584B81 + 3, gRadarTextures.ptr);	// mov     eax, ds:gRadarTextures[eax*4]
		CPatch::PatchPointer(0x584BD0 + 3, gRadarTextures.ptr);	// mov     eax, ds:gRadarTextures[eax*4]

		CPatch::PatchPointer(0x584C04 + 2, gRadarTextures.ptr);	// cmp     ebx, offset gRadarTextures
		CPatch::PatchPointer(0x584C0C + 2, gRadarTextures.ptr + numberOfRadarTilesPerOneDimension - 1);	// cmp     ebx, (offset gRadarTextures+2Ch)
		CPatch::PatchPointer(0x584C3E + 2, gRadarTextures.ptr + numberOfRadarTilesPerOneDimension);	// cmp     ebx, (offset gRadarTextures+30h)

		CPatch::PatchPointer(0x584C5B + 1, gRadarTextures.ptr);	// mov     edi, offset gRadarTextures
		CPatch::PatchPointer(0x584C88 + 2, gRadarTextures.ptr);	// cmp     edi, offset gRadarTextures
		CPatch::PatchPointer(0x584C96 + 2, gRadarTextures.ptr + numberOfRadarTilesPerOneDimension - 1);	// cmp     edi, (offset gRadarTextures+2Ch)
		CPatch::PatchPointer(0x584CB7 + 3, gRadarTextures.ptr);	// mov     eax, ds:gRadarTextures[eax*4]
		CPatch::PatchPointer(0x584CD5 + 2, gRadarTextures.ptr);	// cmp     edi, offset gRadarTextures
		CPatch::PatchPointer(0x584CDD + 2, gRadarTextures.ptr + numberOfRadarTilesPerOneDimension - 1);	// cmp     edi, (offset gRadarTextures+2Ch)
		CPatch::PatchPointer(0x584D22 + 2, gRadarTextures.ptr + numberOfRadarTilesPerOneDimension);	// cmp     edi, (offset gRadarTextures+30h)

		CPatch::PatchPointer(0x586179 + 3, gRadarTextures.ptr);	// mov     eax, ds:gRadarTextures[eax*4]
		CPatch::PatchPointer(0x586557 + 3, pFrontendRadarTextures);	// mov     eax, ds:gRadarTextures[eax*4]
		CPatch::PatchPointer(0x58802D + 3, gRadarTextures.ptr);	// mov     ds:gRadarTextures[esi*4], eax
	}
	#endif

	CPatch::LeaveThisLevel();
}
#endif

// Patches radar textures pointers
void MapLimits::PatchReferencesToRadarTextures()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	this->PatchReferencesToRadarTextures_GTA_SA_PC_1_0();
	#endif
}

extern "C"
{
	unsigned int iNumberOfPathFilesPerDimension;
	unsigned int iNumberOfPathFilesPerDimensionMinusOne;
	unsigned int iTotalNumberOfPathFiles;
	unsigned int iTotalNumberOfPathFilesMinusOne;
	unsigned int iTotalNumberOfPathFilesMinusTwo;
	unsigned int iTotalNumberOfPathFilesIncludingInterior;
	unsigned int iNumberOfPathInteriorSlots;

	float fPathsMapMinCoord;
	float fPathsMapMaxCoord;

	uint32_t CPathFind_field_1544_numberOfElementsPerPathFile;
	uint32_t NumberOfBitsPerVehicleNode;
	uint32_t NaviLinksMask;
	uint32_t SizeOfNaviLink;
	uint32_t SizeOfCPathNode;
	uint32_t SizeOfCPathNodeDividedBy4;
	uint32_t SizeOfCCarPathLink;
	uint32_t SizeOfCCarPathLinkDividedBy2;

	
}

// Does the initialising work for patching the paths map size
bool MapLimits::PatchPaths_DoInitialisingWork()
{
	using namespace Game_GTASA;

	if (CPatch::IsDebugModeActive())
		this->ms_pathsMapSize = 6000;

	// Set variables
	#if TRUE
	{
		g_structureExtension.m_CLinkAddress_extension.Enable();

		if (!CPatch::IsDebugModeActive())
		{
			SizeOfNaviLink = sizeof(CLinkAddress_extended);
			SizeOfCPathNode = sizeof(CPathNode_extended_latest);
			SizeOfCCarPathLink = sizeof(CCarPathLink_extended_latest);

			NumberOfBitsPerVehicleNode = 16;
		}
		else
		{
			SizeOfNaviLink = sizeof(CLinkAddress);
			SizeOfCPathNode = sizeof(CPathNode);
			SizeOfCCarPathLink = sizeof(CCarPathLink);

			NumberOfBitsPerVehicleNode = 10;
		}

		// debugging
		{
			// SizeOfCPathNode = sizeof(CPathNode);
			// SizeOfCCarPathLink = sizeof(CCarPathLink);
		}

		SizeOfCPathNodeDividedBy4 = SizeOfCPathNode / 4;
		SizeOfCCarPathLinkDividedBy2 = SizeOfCCarPathLink / 2;

		NaviLinksMask = (1 << NumberOfBitsPerVehicleNode) - 1;

		iNumberOfPathFilesPerDimension = ms_pathsMapSize / this->ms_pathBlockSize;
		iNumberOfPathFilesPerDimensionMinusOne = iNumberOfPathFilesPerDimension - 1;

		iTotalNumberOfPathFiles = iNumberOfPathFilesPerDimension * iNumberOfPathFilesPerDimension;
		iTotalNumberOfPathFilesMinusOne = iTotalNumberOfPathFiles - 1;
		iTotalNumberOfPathFilesMinusTwo = iTotalNumberOfPathFiles - 2;
		::iNumberOfPathInteriorSlots = this->iNumberOfPathInteriorSlots;

		iTotalNumberOfPathFilesIncludingInterior = iTotalNumberOfPathFiles + iNumberOfPathInteriorSlots;

		fPathsMapMaxCoord = (float)(MapLimits::ms_pathsMapSize / 2);
		fPathsMapMinCoord = -fPathsMapMaxCoord;

		CPathFind_field_1544_numberOfElementsPerPathFile = 16;

		// Set offsets
		if (!CPatch::IsDebugModeActive())
			this->AllocateCPathFind(
				iTotalNumberOfPathFiles,
				iNumberOfPathInteriorSlots,
				CPathFind_field_1544_numberOfElementsPerPathFile
			);
	}
	#endif

	// Allocate memory
	#if TRUE
	{
		if (!CPatch::IsDebugModeActive())
		{
			ThePaths.gta_sa = (CPathFind_extended*)new char[
				TypeDetails::SizeOf<CPathFind>()];
			memset(
				ThePaths.gta_sa,
				0xEE,
				TypeDetails::SizeOf<CPathFind>()
			);
			ThePaths.bIsAllocated.Set(true);
		}

		if (iTotalNumberOfPathFiles > 64)
		{
			ToBeStreamed.ptr = new bool[iTotalNumberOfPathFiles];
			ToBeStreamed.bIsAllocated.Set(true);

			ToBeStreamedForScript.ptr = new bool[iTotalNumberOfPathFiles];
			ToBeStreamedForScript.bIsAllocated.Set(true);

			DontWanderGiven.ptr = new uint8_t[iTotalNumberOfPathFiles];
			DontWanderGiven.bIsAllocated.Set(true);

			XCoorGiven.ptr = new float[iTotalNumberOfPathFiles];
			XCoorGiven.bIsAllocated.Set(true);
			YCoorGiven.ptr = new float[iTotalNumberOfPathFiles];
			YCoorGiven.bIsAllocated.Set(true);
			ZCoorGiven.ptr = new float[iTotalNumberOfPathFiles];
			ZCoorGiven.bIsAllocated.Set(true);

			ConnectsToGiven.ptr = new uint8_t[iTotalNumberOfPathFiles * 6];
			ConnectsToGiven.bIsAllocated.Set(true);
		}
	}
	#endif

	// Print info
	#if TRUE
	{
		CGenericLogStorage::SaveFormattedTextLn(
			"\nPaths info:\n"
			"ThePaths: 0x%X\n"
			"Number of path tiles per dimension: %d\n"
			"Total number of path tiles: %d",

			ThePaths.gta_sa,
			iNumberOfPathFilesPerDimension,
			iTotalNumberOfPathFiles
		);
	}
	#endif

	return true;
}

namespace Game_GTASA
{
	CLinkAddress_extended SteerAICarWithPhysicsFollowPath_Racing_naviLinks[8];

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CPathFind__DoPathSearch_451750()
	{
		__asm
		{
			// call CDynamicStructMember<CPathFind, int>::GetPtr;
		}
	}

	NAKED void patch_CPathFind__MarkRegionsForCoors_44DC85()
	{
		__asm
		{
			mov edx, ebp;
			imul edx, [iNumberOfPathFilesPerDimension];
			add edx, ebx;
			add edx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_mapLimits, MapLimits, ToBeStreamed);

			// go back
			push 44DC8Ch;
			retn;
		}
	}

	NAKED void patch_CPathFind__UpdateStreaming_450CBF()
	{
		__asm
		{
			mov edi, ebx;
			imul edi, [iNumberOfPathFilesPerDimension];
			add edi, esi;
			add edi, ASM_ACCESS_LIMIT_VAR_32_BIT(g_mapLimits, MapLimits, ToBeStreamed);

			// go back
			push 450CC6h;
			retn;
		}
	}

	NAKED void patch_CPathFind__UpdateStreaming_450CA5()
	{
		__asm
		{
			mov edi, ebx;
			imul edi, [iNumberOfPathFilesPerDimension];
			add edi, esi;
			add edi, ASM_ACCESS_LIMIT_VAR_32_BIT(g_mapLimits, MapLimits, ToBeStreamedForScript);

			// go back
			push 450CACh;
			retn;
		}
	}

	NAKED void patch_CPathFind__UpdateStreaming_450D11()
	{
		__asm
		{
			mov eax, ebp;
			imul eax, [iNumberOfPathFilesPerDimension];
			add eax, esi;
			add eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_mapLimits, MapLimits, ToBeStreamedForScript);
			mov al, [eax];

			// go back
			push 450D18h;
			retn;
		}
	}

	NAKED void patch_CPathFind__UpdateStreaming_450D00()
	{
		__asm
		{
			mov eax, ebp;
			imul eax, [iNumberOfPathFilesPerDimension];
			add eax, esi;
			add eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_mapLimits, MapLimits, ToBeStreamed);
			mov al, [eax];

			// go back
			push 450D07h;
			retn;

		}
	}

	NAKED void patch_CCarCtrl__JoinCarWithRoadSystemGotoCoors_156A57D()
	{
		__asm
		{
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_mapLimits, MapLimits, ThePaths);

			// go back
			push 156A596h;
			retn;
		}
	}

	NAKED void patch_CCarCtrl__PickNextNodeToChaseCar_42749E()
	{
		__asm
		{
			mov   ecx, ebp;
			mov   edi, ebp;
			mov   ebp, ebp;

			// go back
			push 0x4274A7;
			retn;
		}
	}

	// patch for 0x44F07E
	static uintptr_t Address_CPathFind__CalcRoadDensity_44F084 = 0;

	static NAKED void patch_CPathFind__CalcRoadDensity_44F07E()
	{
		__asm
		{
			mov esi, eax;
			shl esi, 2;
			lea edi, dword ptr[edi + eax * 4];
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__CalcRoadDensity_44F084);
		}
	}

	static NAKED void patch_CLinkAddress__Constructor_4241B0()
	{
		__asm
		{
			mov eax, ecx;
			mov dword ptr[eax], 0xFFFFFFFF;
			retn;
		}
	}

	NAKED void patch_CPathFind__CountFloodFillGroups_44E666()
	{
		__asm
		{
			mov     word ptr[ecx + eax + CPathNode_extended_latest::GroupExtended], 0;
			push 0x44E66B;
			retn;
		}
	}

	NAKED void patch_CPathFind__CountFloodFillGroups_44E6D0()
	{
		__asm
		{
			cmp     word ptr[eax + CPathNode_extended_latest::GroupExtended], 0;
			jz loc_44E6F1;

			push 0x44E6D6;
			retn;

		loc_44E6F1:
			push 0x44E6F1;
			retn;
		}
	}

	NAKED void patch_CPathFind__CountFloodFillGroups_44E6F1()
	{
		__asm
		{
			mov     dx, word ptr[esp + 20h - 0x10];
			mov esi, eax;
			mov     dword ptr[eax + CPathNode::pNext], 0;
			mov[eax + CPathNode_extended_latest::GroupExtended], dl;

			push 0x44E700;
			retn;
		}
	}

	NAKED void patch_CPathFind__CountFloodFillGroups_44E744()
	{
		__asm
		{
			mov bx, [eax + CPathNode_extended_latest::GroupExtended];
			test bx, bx;
			push 0x44E749;
			retn;
		}
	}

	NAKED void patch_CPathFind__CountFloodFillGroups_44E74B()
	{
		__asm
		{
			mov     bx, word ptr[esp + 20h - 0x10];
			test bx, bx;
			mov[eax + CPathNode_extended_latest::GroupExtended], bx;

			jnz loc_44E75A;

			mov     word ptr[eax + CPathNode_extended_latest::GroupExtended], 8000h;

			push 0x44E75A;
			retn;

		loc_44E75A:
			push 0x44E75A;
			retn;
		}
	}

	NAKED void patch_CPathFind__DoPathSearch_451715()
	{
		__asm
		{
			mov     cx, [ebp + ebx + CPathNode_extended_latest::GroupExtended];
			mov     dx, [eax + edi + CPathNode_extended_latest::GroupExtended];
			add     ebp, ebx;
			add     eax, edi;
			cmp     cx, dx;

			push 0x451723;
			retn;
		}
	}

	NAKED void patch_CPathFind__CompleteNewInterior_4522BF()
	{
		__asm
		{
			mov     dx, [eax + edx + CPathNode_extended_latest::GroupExtended];
			mov     word ptr[esp + 10h + 4], dx;

			push 0x4522C7;
			retn;
		}
	}

	NAKED void patch_CPathFind__CompleteNewInterior_45239A()
	{
		__asm
		{
			mov     cx, word ptr[esp + 1Ch + 4];
			mov[eax + esi + CPathNode_extended_latest::GroupExtended], cx;

			push 0x4523A2;
			retn;
		}
	}

	// racing
	NAKED void patch_CPathFind__FindLinkBetweenNodes_156A20C()
	{
		__asm
		{
			mov[eax], edx;
			pop ebx;
			retn 0Ch;
		}
	}

	NAKED void patch_CPathFind__FindLinkBetweenNodes_156A194()
	{
		__asm
		{
			mov     dword ptr[eax], 0xFFFFFFFF;
			retn 0Ch;
		}
	}

	NAKED void patch_CPathFind__FindLinkBetweenNodes_156A1B5()
	{
		__asm
		{
			mov     dword ptr[eax], 0xFFFFFFFF;
			pop ebx;
			retn 0Ch;
		}
	}

	NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435C93()
	{
		__asm
		{
			push 8;
			push 4;
			push offset SteerAICarWithPhysicsFollowPath_Racing_naviLinks;

			push 0x435C9C;
			retn;
		}
	}

	NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435CC7()
	{
		__asm
		{
			mov[SteerAICarWithPhysicsFollowPath_Racing_naviLinks], ecx;

			push 0x435CCC;
			retn;
		}
	}

	NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435CD3()
	{
		__asm
		{
			mov[SteerAICarWithPhysicsFollowPath_Racing_naviLinks + SIZE CLinkAddress_extended], ecx;

			push 0x435CD8;
			retn;
		}
	}

	NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435D63()
	{
		__asm
		{
			mov[SteerAICarWithPhysicsFollowPath_Racing_naviLinks + edi * SIZE CLinkAddress_extended + 2 * SIZE CLinkAddress_extended], ecx;

			push 0x435D68;
			retn;
		}
	}

	NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435D40()
	{
		__asm
		{
			mov     eax, [eax];
			push    ebp;
			mov     ecx, ebx;
			mov[SteerAICarWithPhysicsFollowPath_Racing_naviLinks + 2 * SIZE CLinkAddress_extended + edi * SIZE CLinkAddress_extended], eax;


			push 0x435D4B;
			retn;
		}
	}

	NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435D85()
	{
		__asm
		{
			mov     dword ptr[SteerAICarWithPhysicsFollowPath_Racing_naviLinks + 6 * SIZE CLinkAddress_extended], 0xFFFFFFFF;
			mov     dword ptr[SteerAICarWithPhysicsFollowPath_Racing_naviLinks + 7 * SIZE CLinkAddress_extended], 0xFFFFFFFF;

			push 0x435D8D;
			retn;
		}
	}

	NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435DAC()
	{
		__asm
		{
			xor edi, edi;
			lea ebp, [SteerAICarWithPhysicsFollowPath_Racing_naviLinks + 2 * SIZE CLinkAddress_extended];

			push 0x435DB2;
			retn;
		}
	}

	NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435DE6()
	{
		__asm
		{
			mov ecx, [ebp + 1 * SIZE CLinkAddress_extended]
			push edx;
			mov edx, [ebp + 0];
			push eax;
			mov eax, [ebp - 1 * SIZE CLinkAddress_extended];
			push ecx;
			mov ecx, [ebp - 2 * SIZE CLinkAddress_extended];

			push 0x435E01;
			retn;
		}
	}

	NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435E21()
	{
		__asm
		{
			mov edi, [SteerAICarWithPhysicsFollowPath_Racing_naviLinks + edi * SIZE CLinkAddress_extended];

			push 0x435E26;
			retn;

		}
	}

	NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435E54()
	{
		__asm
		{
			lea edi, [SteerAICarWithPhysicsFollowPath_Racing_naviLinks + 5 * SIZE CLinkAddress_extended];

			push 0x435E60;
			retn;
		}
	}

	NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435E60()
	{
		__asm
		{
			mov     ecx, [edi];
			cmp     ecx, 0xFFFFFFFF;

			push 0x435E68;
			retn;
		}
	}

	NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435DA7()
	{
		__asm
		{
			mov[esp + 78h + -48h], ecx;

			push 0x435DAC;
			retn;
		}
	}

	NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435E1A()
	{
		__asm
		{
			mov edi, [esp + 78h + -48h];

			push 0x435E26;
			retn;
		}
	}

	void NAKED patch_4241B0()
	{
		__asm
		{
			mov     eax, ecx;
			mov     dword ptr[eax], 0xFFFFFFFF;
			retn;
		}
	}

	void NAKED patch_CCarCtrl__FindPercDependingOnDistToLink_422620()
	{
		__asm
		{
			mov eax, dword ptr[esp + 8];

			push 0x422625;
			retn;
		}
	}

	void NAKED patch_CCarCtrl__ClipTargetOrientationToLink_401E69()
	{
		__asm
		{
			mov eax, dword ptr[esp + 8];

			push 0x422765;
			retn;
		}
	}
	#endif

	uint32_t* NumTempExternalNodes;

	// Initializes a structure
	void CPathFind_extended::Init()
	{
		MapLimits* pMapLimits = &g_mapLimits;
		*NumTempExternalNodes = 0;

		this->m_dwNumForbiddenAreas(this) = 0;
		this->m_bForbiddenForScriptedCarsEnabled(this) = 0;

		//////////////////////
		for (unsigned int i = 0; i < pMapLimits->iTotalNumberOfPathIndicesIncludingInterior; i++)
		{
			this->m_pPathNodes.extended(this)[i] = nullptr;
			this->m_pNaviNodes.extended(this)[i] = nullptr;
			this->m_pNodeLinks(this)[i] = nullptr;
			this->m_pLinkLengths(this)[i] = nullptr;
			this->m_pPathIntersections(this)[i] = nullptr;

			#ifdef ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA
			this->m_pPathNodesStandard(this)[i] = nullptr;
			this->m_pNaviNodesStandard(this)[i] = nullptr;
			#endif
		}

		unsigned int NumberOfNaviElements = this->m_field_EA4.GetArrayCount();

		for (unsigned int i = 0; i < NumberOfNaviElements; i++)
		{
			this->m_pNaviLinks.extended(this)[i] = nullptr;
			this->m_field_EA4(this)[i] = nullptr;
		}

		///////////
		memset(
			this->m_interiorAreaIDarray(this),
			-1,
			iNumberOfPathInteriorSlots * sizeof(unsigned int)
		);
	}

	// Shutdown
	// Used in FileIDlimit.cpp, should work without Paths map size limit enabled.
	void CPathFind_extended::Shutdown()
	{
		MapLimits* pMapLimits = &g_mapLimits;
		unsigned int numberOfPathFilesPerDimension = pMapLimits->ms_pathsMapSize / pMapLimits->ms_pathBlockSize;
		unsigned int FILE_TYPE_PATH_BASE_ID = g_fileIDlimits.GetBaseID(GENERAL_FILE_TYPE_PATH_NODES);

		for (unsigned int y_region = 0; y_region < numberOfPathFilesPerDimension; y_region++)
		{
			for (unsigned int x_region = 0; x_region < numberOfPathFilesPerDimension; x_region++)
				CStreaming::RemoveModel(FILE_TYPE_PATH_BASE_ID + y_region * numberOfPathFilesPerDimension + x_region);
		}
	}

	uintptr_t Address_CPathFind_SwitchRoadsOffInAreaForOneRegion = 0;

	// Switches roads off in area for one region.
	void __thiscall CPathFind_extended::SwitchRoadsOffInAreaForOneRegion(
		float x1, float x2,
		float y1, float y2,
		float z1, float z2,
		bool bEnable,
		char type,
		int index,
		char a11)
	{
		return g_memoryCall.Method<void>(
			Address_CPathFind_SwitchRoadsOffInAreaForOneRegion,
			this, x1, x2, y1, y2, z1, z2, bEnable, type, index, a11);
	}

	// #define CONVERT_AREA_IDS_FROM_DEFAULT_MAP_SIZE
	// #define SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE

	#ifdef CONVERT_AREA_IDS_FROM_DEFAULT_MAP_SIZE
		// Function used for debugging
	int GetNewAreaIndex(int areaID)
	{
		int oldSectionCount = 6000 / 750;
		int newSectionCount = MapLimits::ms_pathsMapSize / 750;

		int oldSectionX = areaID % oldSectionCount;
		int oldSectionY = areaID / oldSectionCount;

		int newSectionX = oldSectionX - (oldSectionCount / 2) + (newSectionCount / 2);
		int newSectionY = oldSectionY - (oldSectionCount / 2) + (newSectionCount / 2);

		int newAreaID = newSectionX + newSectionY * newSectionCount;

		/*
		printf_MessageBox(
			"GetNewAreaIndex,\n"

			"oldSectionCount: %d\n"
			"newSectionCount: %d\n"
			"oldSectionX: %d\n"
			"oldSectionY: %d\n"
			"newSectionX: %d\n"
			"newSectionY: %d\n"

			"input: %d output: %d"

			,
			oldSectionCount,
			newSectionCount,
			oldSectionX,
			oldSectionY,

			newSectionX,
			newSectionY,

			areaID,
			newAreaID
			);
		*/

		#ifdef SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE
		if (newAreaID > 255)
		{
			printf_MessageBox("something is wrong");
		}
		#endif

		return newAreaID;
	}
	#endif

	#if 0
	// Function 0: 0x315348
	extern "C"
	{
		uintptr_t Address_CPathFind__LoadPathFindData_315350_thumb = 0;
	}

	static TARGET_THUMB NAKED void original_CPathFind__LoadPathFindData_315348()
	{
		__asm(
		".thumb\n"
			"PUSH {R4-R7,LR}\n"
			"ADD R7, SP, #0xC\n"
			"PUSH {R8-R11}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__LoadPathFindData_315350_thumb)
			);
	}

	static void debugging_CPathFind__LoadPathFindData_315348(void* pathFind, RwStream *stream, int index)
	{
		g_memoryCall.Method<void>((uintptr_t)&original_CPathFind__LoadPathFindData_315348, pathFind, stream, index);
	}

	// Loads path file.
	void __thiscall CPathFind_extended::LoadPathFindDataDebug(RwStream *stream, int index)
	{
		RwStream savedStream = *stream;

		// call custom function
		Address_CPathFind__LoadPathFindData_315350_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315350));
		debugging_CPathFind__LoadPathFindData_315348(this, stream, index);

		// save values
		auto perhapsBadNodes = this->m_pLinkLengths(this)[index];

		// call original function
		*stream = savedStream;

		this->LoadPathFindData(stream, index);

		if (memcmp(this->m_pLinkLengths(this)[index], perhapsBadNodes, this->m_dwNumAddresses(this)[index]) == 0)
			OutputFormattedDebugString("Nodes good, ptr1: 0x%X ptr2: 0x%X count: %d", this->m_pLinkLengths(this)[index], perhapsBadNodes, this->m_dwNumAddresses(this)[index]);
		else
			OutputFormattedDebugString("Nodes bad, ptr1: 0x%X ptr2: 0x%X count: %d", this->m_pLinkLengths(this)[index], perhapsBadNodes, this->m_dwNumAddresses(this)[index]);

		// this->m_pPathNodes.standard(this)[index] = perhapsBadNodes;
	}
	#endif

	void SetCPathNodeFromSerializedData(CPathNode* pPathNodeToSet, const CPathNodeSerialize* pSerialized)
	{
		pPathNodeToSet->pNext = 0;
		pPathNodeToSet->pPrevious = 0;
		pPathNodeToSet->Coors = pSerialized->Coors;
		pPathNodeToSet->DistanceToTarget = pSerialized->DistanceToTarget;
		pPathNodeToSet->IndexAdjacentNodes = pSerialized->IndexAdjacentNodes;
		pPathNodeToSet->Address = pSerialized->Address;
		pPathNodeToSet->Width = pSerialized->Width;
		pPathNodeToSet->Group = pSerialized->Group;
		pPathNodeToSet->m_dwFlags = pSerialized->m_dwFlags;
	}

	void SetCPathNode_fastman92_version_2_fromSerializedData(CPathNode_fastman92_version_2* pPathNodeToSet, const CPathNode_fastman92_version_2_Serialize* pSerialized)
	{
		SetCPathNodeFromSerializedData(pPathNodeToSet, pSerialized);
		pPathNodeToSet->CoorsExtended = pSerialized->CoorsExtended;
	}

	void SetCPathNode_fastman92_version_4_fromSerializedData(CPathNode_fastman92_version_4* pPathNodeToSet, const CPathNode_fastman92_version_4_Serialize* pSerialized)
	{
		SetCPathNode_fastman92_version_2_fromSerializedData(pPathNodeToSet, pSerialized);
		pPathNodeToSet->GroupExtended = pSerialized->GroupExtended;
	}

	// Loads path file.
	void __thiscall CPathFind_extended::LoadPathFindData(RwStream *stream, int index)
	{
		// OutputFormattedDebugString("LoadPathFindData: %d", index);

		//// variables ////
		const int newValueForDeprecatedCoordinate = 4095 * 8;

		// numbers
		uint32_t firstDWORD;
		uint32_t numNodes;
		uint32_t numVehicleNodes;
		uint32_t numPedNodes;
		uint32_t numCarPathLinks;
		uint32_t numAddresses;

		// memory
		CPathNode_extended_latest* pPathNodesMemory = NULL;

		// For debugging
		#ifdef ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA
		CPathNode* pPathNodesMemoryStandard = NULL;
		CCarPathLink* pNaviNodesMemoryStandard = NULL;
		#endif

		CCarPathLink_extended_latest* pNaviNodesMemory = NULL;
		CNodeAddress* pNodeLinksData = NULL;
		CLinkAddress_extended* pNaviLinksData = NULL;
		uint8_t* pLinkLengthsData = NULL;
		CPathIntersectionInfo* pPathIntersectionsData = NULL;
		////		

		{
			RwStreamRead(stream, &firstDWORD, sizeof(firstDWORD));

			if (firstDWORD != 0xFFFFFFFF)	// is standard format
			{
				numNodes = firstDWORD;

				RwStreamRead(stream, &numVehicleNodes, sizeof(numVehicleNodes));
				RwStreamRead(stream, &numPedNodes, sizeof(numPedNodes));
				RwStreamRead(stream, &numCarPathLinks, sizeof(numCarPathLinks));
				RwStreamRead(stream, &numAddresses, sizeof(numAddresses));

				/*
				printf_MessageBox(
					"index: %d\n"
					"numNodes: %d\n"
					"numVehicleNodes: %d\n"
					"numPedNodes: %d\n"
					"numCarPathLinks: %d\n"
					"numAddresses: %d\n",
					index,
					numNodes,
					numVehicleNodes,
					numPedNodes,
					numCarPathLinks,
					numAddresses
					);
				*/

				#define PATH_NODES_EXTENDED_IMPLEMENTED

				// path nodes	 
				if (numNodes)
				{
					// Is extended structure already implemented?
					#ifdef PATH_NODES_EXTENDED_IMPLEMENTED
					{
						uint32_t sizeOfOriginalData = numNodes * sizeof(CPathNodeSerialize);

						CPathNodeSerialize* pPathNodesDataOrig = (CPathNodeSerialize*)CMemoryMgr::Malloc(sizeOfOriginalData);
						pPathNodesMemory = (CPathNode_extended_latest*)CMemoryMgr::Malloc(numNodes * sizeof(CPathNode_extended_latest));

						RwStreamRead(stream, pPathNodesDataOrig, sizeOfOriginalData);

						/*
						OutputFormattedDebugString(
							"index: %d number of path nodes: %d size of original nodes: 0x%X size of new nodes: 0x%X",
							index,
							numNodes,
							sizeOfOriginalData,
							numNodes * sizeof(CPathNode_extended_latest)
						);
						*/

						if (0)
						{
							tMemoryPermissionChangeRequest request;
							request.lpAddress = (char*)pPathNodesMemory + 0x2000;
							request.dwSize = 0x1000;
							request.flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_NOACCESS);

							SetMemoryPermission(&request);
						}


						// for debugging
						#ifdef ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA
						pPathNodesMemoryStandard = (CPathNode*)CMemoryMgr::Malloc(sizeOfOriginalData);
						memcpy(pPathNodesMemoryStandard, pPathNodesDataOrig, sizeOfOriginalData);
						#endif

						// convert data from old format to new format
						for (unsigned i = 0; i < numNodes; i++)
						{
							SetCPathNodeFromSerializedData(&pPathNodesMemory[i], &pPathNodesDataOrig[i]);

							// memset(pPathNodesMemory[i].useless, 0xEE, sizeof(pPathNodesMemory[i].useless));

							///////
							#ifdef CONVERT_AREA_IDS_FROM_DEFAULT_MAP_SIZE
							pPathNodesMemory[i].m_wAreaId = GetNewAreaIndex(pPathNodesMemory[i].m_wAreaId);
							#endif

							pPathNodesMemory[i].CoorsExtended.x = pPathNodesMemory[i].Coors.x;
							pPathNodesMemory[i].CoorsExtended.y = pPathNodesMemory[i].Coors.y;
							pPathNodesMemory[i].CoorsExtended.z = pPathNodesMemory[i].Coors.z;

							// Are extended coordinates already implemented?
							#if TRUE
							{
								pPathNodesMemory[i].Coors.x = newValueForDeprecatedCoordinate;
								pPathNodesMemory[i].Coors.y = newValueForDeprecatedCoordinate;
								pPathNodesMemory[i].Coors.z = newValueForDeprecatedCoordinate;
							}
							#endif

							pPathNodesMemory[i].GroupExtended = pPathNodesMemory[i].Group;

							/////////////

							// memset(&pPathNodesMemory[i].test, 0xDF, sizeof(pPathNodesMemory[i].test));

							// pPathNodesMemory[i].m_posn.x += 30 * 8;
							// pPathNodesMemory[i].m_posn.y += 30 * 8;
						}

						CMemoryMgr::Free(pPathNodesDataOrig);
					}
					#else
					{
						uint32_t sizeOfOriginalData = numNodes * sizeof(CPathNode);
						CPathNode* pPathNodesDataOrig = (CPathNode*)CMemoryMgr::Malloc(sizeOfOriginalData);
						pPathNodesMemory = (CPathNode_extended_latest*)CMemoryMgr::Malloc(numNodes * sizeof(CPathNode));

						RwStreamRead(stream, pPathNodesMemory, sizeOfOriginalData);
					}
					#endif
				}
				else
				{
					pPathNodesMemory = (CPathNode_extended_latest*)CMemoryMgr::Malloc(sizeof(CPathNode_extended_latest));

					#ifdef ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA
					pPathNodesMemoryStandard = (CPathNode*)CMemoryMgr::Malloc(sizeof(CPathNode));
					#endif
				}

				// navi nodes
				if (numCarPathLinks)
				{
					// Is extended structure already implemented?
					#if TRUE
					{
						uint32_t sizeOfOriginalData = numCarPathLinks * sizeof(CCarPathLink);

						CCarPathLink* pNaviNodesDataOrig = (CCarPathLink*)CMemoryMgr::Malloc(sizeOfOriginalData);
						pNaviNodesMemory = (CCarPathLink_extended_latest*)CMemoryMgr::Malloc(numCarPathLinks *
							sizeof(CCarPathLink_extended_latest));

						RwStreamRead(stream, pNaviNodesDataOrig, sizeOfOriginalData);

						// for debugging
						#ifdef ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA
						pNaviNodesMemoryStandard = (CCarPathLink*)CMemoryMgr::Malloc(sizeOfOriginalData);
						memcpy(pNaviNodesMemoryStandard, pNaviNodesDataOrig, sizeOfOriginalData);
						#endif

						// copy data from old format to new format
						for (unsigned int i = 0; i < numCarPathLinks; i++)
						{
							memcpy(&pNaviNodesMemory[i], &pNaviNodesDataOrig[i], sizeof(CCarPathLink));

							//////

							pNaviNodesMemory[i].CoorsExtended.x = pNaviNodesMemory[i].Coors.x;
							pNaviNodesMemory[i].CoorsExtended.y = pNaviNodesMemory[i].Coors.y;

							// Are extended coordinates already implemented?
							#if TRUE
							pNaviNodesMemory[i].Coors.x = newValueForDeprecatedCoordinate;
							pNaviNodesMemory[i].Coors.y = newValueForDeprecatedCoordinate;
							#endif

							// pNaviNodesMemory[i].extended_posX = newValueForDeprecatedCoordinate;
							// pNaviNodesMemory[i].extended_posY = newValueForDeprecatedCoordinate;

							// memset(&pNaviNodesMemory[i].test, 0xDF, sizeof(pNaviNodesMemory[i].test));

							// pNaviNodesMemory[i].x += 30 * 8;
							// pNaviNodesMemory[i].y += 30 * 8;

							#ifdef CONVERT_AREA_IDS_FROM_DEFAULT_MAP_SIZE
							pNaviNodesMemory[i].info.areaId = GetNewAreaIndex(pNaviNodesMemory[i].info.areaId);
							#endif
						}

						CMemoryMgr::Free(pNaviNodesDataOrig);
					}
					#else
					uint32_t sizeOfOriginalData = numCarPathLinks * sizeof(CCarPathLink);

					pNaviNodesMemory = (CCarPathLink_extended_latest*)CMemoryMgr::Malloc(sizeOfOriginalData);

					RwStreamRead(stream, pNaviNodesMemory, sizeOfOriginalData);
					#endif
				}

				// links
				if (numAddresses)
				{
					pNodeLinksData = (CNodeAddress*)CMemoryMgr::Malloc((numAddresses + 192) * sizeof(CNodeAddress));
					pNaviLinksData = (CLinkAddress_extended*)CMemoryMgr::Malloc(sizeof(CLinkAddress_extended) * numAddresses);
					pLinkLengthsData = (uint8_t*)CMemoryMgr::Malloc(numAddresses + 192);
					pPathIntersectionsData = (CPathIntersectionInfo*)CMemoryMgr::Malloc(numAddresses + 192);

					// pNodeLinksData
					{
						RwStreamRead(stream, pNodeLinksData, sizeof(CNodeAddress) * (numAddresses + 192));

						#ifdef CONVERT_AREA_IDS_FROM_DEFAULT_MAP_SIZE
						{
							for (unsigned int i = 0; i < numAddresses; i++)
								pNodeLinksData[i].areaId = GetNewAreaIndex(pNodeLinksData[i].areaId);
						}
						#endif
					}

					// pNaviLinksData
					// Is extended structure already implemented?
					#if TRUE
					{
						CLinkAddress* pNaviLinksDataOrig = (CLinkAddress*)CMemoryMgr::Malloc(sizeof(CLinkAddress) * numAddresses);
						RwStreamRead(stream, pNaviLinksDataOrig, sizeof(CLinkAddress) * numAddresses);

						for (unsigned int i = 0; i < numAddresses; i++)
						{
							int areaID = pNaviLinksDataOrig[i].m_wAreaId;
							int naviNodeID = pNaviLinksDataOrig[i].m_wCarPathLinkId;

							#ifdef CONVERT_AREA_IDS_FROM_DEFAULT_MAP_SIZE
							areaID = GetNewAreaIndex(areaID);
							#endif

							pNaviLinksData[i].m_wAreaId = areaID;
							pNaviLinksData[i].m_wCarPathLinkId = naviNodeID;

							/*
							printf_MessageBox("Old link: %d New link: %d\nNumberOfBitsPerVehicleNode: %d",
								pNaviLinksData[i], pNaviLinksDataOrig[i],
								NumberOfBitsPerVehicleNode
								);
							*/
						}

						CMemoryMgr::Free(pNaviLinksDataOrig);
					}
					#else
					/*
					CLinkAddress* pNaviLinksDataOrig = (CLinkAddress*)CMemoryMgr::Malloc(sizeof(CLinkAddress) * numAddresses);
					RwStreamRead(stream, pNaviLinksDataOrig, sizeof(CLinkAddress) * numAddresses);

					for (unsigned int i = 0; i < numAddresses; i++)
					{
						*(CLinkAddress*)&pNaviLinksData[i] = *(CLinkAddress*)&pNaviLinksDataOrig[i];
						*(uint16_t*)((char*)&pNaviLinksData[i] + 2) = 0;
					}

					CMemoryMgr::Free(pNaviLinksDataOrig);
					*/

					pNaviLinksData = (CLinkAddress_extended*)CMemoryMgr::Malloc(sizeof(CLinkAddress) * numAddresses);
					RwStreamRead(stream, pNaviLinksData, sizeof(CLinkAddress) * numAddresses);
					#endif

					///////
					RwStreamRead(stream, pLinkLengthsData, numAddresses + 192);
					RwStreamRead(stream, pPathIntersectionsData, numAddresses + 192);
				}
			}
			else
			{
				uint32_t format;
				int formatVersion;

				RwStreamRead(stream, &format, sizeof(format));

				if (format == '29MF')
				{
					uint8_t myNameSize;
					char myName[32];

					RwStreamRead(stream, &myNameSize, sizeof(myNameSize));

					if (myNameSize != 0xB)
					{
						printf_MessageBox(
							"Path index %d, wrong value for name size: %d",
							index,
							myNameSize
						);

						goto errorHappened;
					}

					RwStreamRead(stream, myName, myNameSize);

					static const char validMyName[] = "\x00" "fastman92" "\x00";

					if (memcmp(myName, validMyName, sizeof(validMyName) - 1))
					{
						printf_MessageBox(
							"Path index %d, wrong value for name: %s",
							index,
							myName
						);

						goto errorHappened;
					}

					// check version
					{
						tFastman92PathFileHeaderThirdPart HeaderThirdPart;
						RwStreamRead(stream, &HeaderThirdPart, sizeof(HeaderThirdPart));

						if (HeaderThirdPart.formatVersion == '2REV')
							formatVersion = 2;
						else if (HeaderThirdPart.formatVersion == '3REV')
							formatVersion = 3;
						else
						{
							printf_MessageBox(
								"Path index %d, unsupported version value: 0x%08X",
								index,
								format
							);

							goto errorHappened;
						}

						// load header values
						{
							numNodes = HeaderThirdPart.numberOfPathNodes;
							numVehicleNodes = HeaderThirdPart.numberOfPathVehicleNodes;
							numPedNodes = HeaderThirdPart.numberOfPathPedNodes;
							numCarPathLinks = HeaderThirdPart.numberOfCarPathLinks;
							numAddresses = HeaderThirdPart.numberOfAdjacentAddresses;
						}
					}
				}
				else if (format == '4ALF')
				{
					formatVersion = 4;

					tStandardPathFileHeaderCounts header;
					RwStreamRead(stream, &header, sizeof(header));

					// load header values
					{
						numNodes = header.numberOfPathNodes;
						numVehicleNodes = header.numberOfPathVehicleNodes;
						numPedNodes = header.numberOfPathPedNodes;
						numCarPathLinks = header.numberOfCarPathLinks;
						numAddresses = header.numberOfAdjacentAddresses;
					}
				}
				else
				{
					printf_MessageBox(
						"Path index %d, unsupported format value: 0x%08X",
						index,
						format
					);

					goto errorHappened;
				}

				// path nodes			 
				if (numNodes)
				{
					pPathNodesMemory = (CPathNode_extended_latest*)CMemoryMgr::Malloc(numNodes * sizeof(CPathNode_extended_latest));

					if (formatVersion == 2)
					{
						uint32_t sizeOfOldData = numNodes * sizeof(CPathNode_fastman92_version_2_Serialize);

						CPathNode_fastman92_version_2_Serialize* pPathNodesDataOld = (CPathNode_fastman92_version_2_Serialize*)CMemoryMgr::Malloc(sizeOfOldData);

						RwStreamRead(stream, pPathNodesDataOld, sizeOfOldData);

						// convert data from old format to new format
						for (unsigned i = 0; i < numNodes; i++)
						{
							SetCPathNode_fastman92_version_2_fromSerializedData(&pPathNodesMemory[i], &pPathNodesDataOld[i]);

							pPathNodesMemory[i].GroupExtended = pPathNodesMemory[i].Group;
						}

						CMemoryMgr::Free(pPathNodesDataOld);
					}
					else if (formatVersion == 3)
					{
						uint32_t sizeOfOldData = numNodes * sizeof(CPathNode_fastman92_version_3_Serialize);

						CPathNode_fastman92_version_3_Serialize* pPathNodesDataOld = (CPathNode_fastman92_version_3_Serialize*)CMemoryMgr::Malloc(sizeOfOldData);

						RwStreamRead(stream, pPathNodesDataOld, sizeOfOldData);

						// convert data from old format to new format
						for (unsigned i = 0; i < numNodes; i++)
						{
							SetCPathNode_fastman92_version_2_fromSerializedData(&pPathNodesMemory[i], &pPathNodesDataOld[i]);

							pPathNodesMemory[i].GroupExtended = pPathNodesDataOld[i].GroupExtended;
						}

						CMemoryMgr::Free(pPathNodesDataOld);
					}
					else if (formatVersion == 4)
					{
						uint32_t sizeOfOldData = numNodes * sizeof(CPathNode_fastman92_version_4_Serialize);

						CPathNode_fastman92_version_4_Serialize* pPathNodesDataOld = (CPathNode_fastman92_version_4_Serialize*)CMemoryMgr::Malloc(sizeOfOldData);

						RwStreamRead(stream, pPathNodesDataOld, sizeOfOldData);

						// convert data from old format to new format
						for (unsigned i = 0; i < numNodes; i++)
							SetCPathNode_fastman92_version_4_fromSerializedData(&pPathNodesMemory[i], &pPathNodesDataOld[i]);

						CMemoryMgr::Free(pPathNodesDataOld);
					}
					else
					{
						printf_MessageBox("Code for selected path file version needs to be made");
						goto errorHappened;
					}
				}
				else
					pPathNodesMemory = (CPathNode_extended_latest*)CMemoryMgr::Malloc(sizeof(CPathNode_extended_latest));

				// navi nodes
				if (numCarPathLinks)
				{
					if (formatVersion == 2 || formatVersion == 3)
					{
						uint32_t sizeOfOldData = numCarPathLinks * sizeof(CCarPathLink_fastman92_version_2);

						CCarPathLink_fastman92_version_2* pNaviNodesDataOld = (CCarPathLink_fastman92_version_2*)CMemoryMgr::Malloc(sizeOfOldData);
						pNaviNodesMemory = (CCarPathLink_extended_latest*)CMemoryMgr::Malloc(numCarPathLinks *
							sizeof(CCarPathLink_extended_latest));

						RwStreamRead(stream, pNaviNodesDataOld, sizeOfOldData);

						// copy data from old format to new format
						for (unsigned int i = 0; i < numCarPathLinks; i++)
						{
							memcpy(&pNaviNodesMemory[i], &pNaviNodesDataOld[i], sizeof(CCarPathLink));

							//////
							pNaviNodesMemory[i].CoorsExtended.x = pNaviNodesDataOld[i].CoorsExtended.x;
							pNaviNodesMemory[i].CoorsExtended.y = pNaviNodesDataOld[i].CoorsExtended.y;
						}

						CMemoryMgr::Free(pNaviNodesDataOld);
					}
					else if (formatVersion == 4)
					{
						uint32_t sizeOfOldData = numCarPathLinks * sizeof(CCarPathLink_fastman92_version_4);

						CCarPathLink_fastman92_version_4* pNaviNodesDataOld = (CCarPathLink_fastman92_version_4*)CMemoryMgr::Malloc(sizeOfOldData);
						pNaviNodesMemory = (CCarPathLink_extended_latest*)CMemoryMgr::Malloc(numCarPathLinks *
							sizeof(CCarPathLink_extended_latest));

						RwStreamRead(stream, pNaviNodesDataOld, sizeOfOldData);

						// copy data from old format to new format
						for (unsigned int i = 0; i < numCarPathLinks; i++)
						{
							memcpy(&pNaviNodesMemory[i], &pNaviNodesDataOld[i], sizeof(CCarPathLink));

							//////
							pNaviNodesMemory[i].CoorsExtended.x = pNaviNodesDataOld[i].CoorsExtended.x;
							pNaviNodesMemory[i].CoorsExtended.y = pNaviNodesDataOld[i].CoorsExtended.y;
						}

						CMemoryMgr::Free(pNaviNodesDataOld);
					}
				}

				// links
				if (numAddresses)
				{
					pNodeLinksData = (CNodeAddress*)CMemoryMgr::Malloc((numAddresses + 192) * sizeof(CNodeAddress));
					pNaviLinksData = (CLinkAddress_extended*)CMemoryMgr::Malloc(sizeof(CLinkAddress_extended) * numAddresses);
					pLinkLengthsData = (uint8_t*)CMemoryMgr::Malloc(numAddresses + 192);
					pPathIntersectionsData = (CPathIntersectionInfo*)CMemoryMgr::Malloc(numAddresses + 192);

					// pNodeLinksData
					{
						RwStreamRead(stream, pNodeLinksData, sizeof(CNodeAddress) * numAddresses + 768);
					}

					// pNaviLinksData
					{
						RwStreamRead(stream, pNaviLinksData, sizeof(uint32_t) * numAddresses);
					}

					RwStreamRead(stream, pLinkLengthsData, numAddresses + 192);
					RwStreamRead(stream, pPathIntersectionsData, numAddresses + 192);
				}

				// check is EOF
				uint32_t fileEOF = 0;

				RwStreamRead(stream, &fileEOF, sizeof(fileEOF));

				if (fileEOF != 'FOE')	// 'EOF'
				{
					printf_MessageBox(
						"Path index %d, EOF expected, but other value found: 0x%08X",
						index,
						fileEOF
					);

					goto errorHappened;
				}
			}

			// the rest of code
			// Set data in arrays			
			this->m_dwNumNodes(this)[index] = numNodes;
			this->m_dwNumVehicleNodes(this)[index] = numVehicleNodes;
			this->m_dwNumPedNodes(this)[index] = numPedNodes;
			this->m_dwNumCarPathLinks(this)[index] = numCarPathLinks;
			this->m_dwNumAddresses(this)[index] = numAddresses;

			this->m_pPathNodes.extended(this)[index] = pPathNodesMemory;

			#ifdef ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA
			this->m_pPathNodesStandard(this)[index] = pPathNodesMemoryStandard;
			this->m_pNaviNodesStandard(this)[index] = pNaviNodesMemoryStandard;
			#endif

			this->m_pNaviNodes.extended(this)[index] = pNaviNodesMemory;

			this->m_pNodeLinks(this)[index] = pNodeLinksData;
			this->m_pNaviLinks.extended(this)[index] = pNaviLinksData;

			this->m_pLinkLengths(this)[index] = pLinkLengthsData;
			this->m_pPathIntersections(this)[index] = pPathIntersectionsData;

			// post process
			{
				// post process vehicle nodes
				for (unsigned int i = 0; i < numVehicleNodes; i++)
					this->PostProcessPathNode(&pPathNodesMemory[i], PATH_TYPE_VEHICLE);

				// post process ped nodes
				for (unsigned int i = numVehicleNodes; i < numNodes; i++)
					this->PostProcessPathNode(&pPathNodesMemory[i], PATH_TYPE_PED);

				// post process navi nodes
				for (unsigned int i = 0; i < numCarPathLinks; i++)
					this->PostProcessNaviNode(&pNaviNodesMemory[i]);
			}

			#ifdef SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE
			{
				CGenericLogStorage::SaveFormattedTextLn(
					"Loaded path index: %d\n"
					"m_pPathNodes = 0x%X\n"
					"m_pNaviNodes = 0x%X\n"
					"m_pNodeLinks = 0x%X\n"
					"m_pNaviLinks = 0x%X\n"
					"m_pLinkLengthsData = 0x%X\n"
					"m_pPathIntersections = 0x%X\n",


					index,
					pPathNodesMemory,
					pNaviNodesMemory,
					pNodeLinksData,
					pNaviLinksData,
					pLinkLengthsData,
					pPathIntersectionsData
				);
			}
			#endif

			#ifdef SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE
			{
				int oldSectionCount = 6000 / 750;
				int newSectionCount = g_mapLimits.ms_pathsMapSize / 750;

				int newSectionX = index % newSectionCount;
				int newSectionY = index / newSectionCount;

				int oldSectionX = newSectionX - (newSectionCount / 2) + (oldSectionCount / 2);
				int oldSectionY = newSectionY - (newSectionCount / 2) + (oldSectionCount / 2);

				int oldAreaID = oldSectionX + oldSectionY * oldSectionCount;

				if (oldSectionX >= 0 && oldSectionX < oldSectionCount &&
					oldSectionY >= 0 && oldSectionY < oldSectionCount)
				{
					if (!pNaviNodesMemory
						|| !pNaviNodesMemory
						|| !pNodeLinksData
						|| !pNaviLinksData
						)
					{
						CGenericLogStorage::SaveWorkBuffer();

						printf_MessageBox(
							"Some data is not loaded for index: %d\n"
							"m_pPathNodes = 0x%X\n"
							"m_pNaviNodes = 0x%X\n"
							"m_pNodeLinks = 0x%X\n"
							"m_pNaviLinks = 0x%X\n"
							"m_pLinkLengthsData = 0x%X\n"
							"m_pPathIntersections = 0x%X\n",


							index,
							pPathNodesMemory,
							pNaviNodesMemory,
							pNodeLinksData,
							pNaviLinksData,
							pLinkLengthsData,
							pPathIntersectionsData
						);
					}

				}

				/*
				else
					printf_MessageBox("out of default path area: %d\n", index);

					*/
			}
			#endif
			
			// set flags properly
			if (numNodes > 0)
			{
				#ifdef PATH_NODES_EXTENDED_IMPLEMENTED
				auto realPathNodesMemory = pPathNodesMemory;
				#else
				auto realPathNodesMemory = (CPathNode*)pPathNodesMemory;
				#endif

				auto pPathNode = realPathNodesMemory;

				unsigned int i = 0;

				do
				{
					// bit 8 gets the value of bit 5
					pPathNode->SwitchedOffOriginal = pPathNode->SwitchedOff;

					/*
					pPathNode->m_dwFlags = BitwiseOperation::ChangeOneBit(
						pPathNode->m_dwFlags,
						8,
						BitwiseOperation::TestBit(pPathNode->m_dwFlags, 5)
					);
					*/

					pPathNode++;
					i++;					
				} while (i < numNodes);

				#if defined(ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA) && defined(PATH_NODES_EXTENDED_IMPLEMENTED)
				{
					unsigned int i = 0;

					do
					{
						pPathNodesMemoryStandard[i].m_dwFlags = realPathNodesMemory[i].m_dwFlags;

						i++;
					} while (i < numNodes);
				}
				#endif
			}

			// forbidden areas
			uint32_t numForbiddenAreas = this->m_dwNumForbiddenAreas(this);

			/*
			printf_MessageBox(
				"offset: 0x%X num forbidden areas: 0xX",
				this -> MemberOffsetArray[Offset_CPathFind__m_dwNumForbiddenAreas],
				numForbiddenAreas
				);
			*/

			if (numForbiddenAreas > 0)
			{
				unsigned int i = 0;
				CForbiddenArea* pForbiddenArea = this->m_aForbiddenAreas(this);

				do
				{
					this->SwitchRoadsOffInAreaForOneRegion(
						pForbiddenArea->x1,
						pForbiddenArea->x2,
						pForbiddenArea->y1,
						pForbiddenArea->y2,
						pForbiddenArea->z1,
						pForbiddenArea->z2,
						pForbiddenArea->bEnable != 0,
						pForbiddenArea->type,
						index,
						0
					);

					pForbiddenArea++;
					i++;
				} while (i < numForbiddenAreas);
			}

			// field_1544
			int* pField_1544_forThisIndex = this->m_field_1544(this)
				+ CPathFind_field_1544_numberOfElementsPerPathFile * index;

			for (unsigned int i = 0; i < CPathFind_field_1544_numberOfElementsPerPathFile; i++)
			{
				*pField_1544_forThisIndex = -1;
				*(pField_1544_forThisIndex + iTotalNumberOfPathFiles * CPathFind_field_1544_numberOfElementsPerPathFile) = -1;

				pField_1544_forThisIndex++;
			}

			return;
		}

	errorHappened:
		{
			CMemoryMgr::Free(pPathNodesMemory);
			CMemoryMgr::Free(pNaviNodesMemory);
			CMemoryMgr::Free(pNodeLinksData);
			CMemoryMgr::Free(pNaviLinksData);
			CMemoryMgr::Free(pLinkLengthsData);
			CMemoryMgr::Free(pPathIntersectionsData);

			#ifdef ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA
			CMemoryMgr::Free(pPathNodesMemoryStandard);
			CMemoryMgr::Free(pNaviNodesMemoryStandard);
			#endif

			return;
		}
	}

	// Unloads path file
	void __thiscall CPathFind_extended::UnLoadPathFindData(int index)
	{
		#ifdef SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE
		char buffer[1024];
		char* iBuffer = buffer;


		iBuffer += sprintf(iBuffer, "Unloading path index: %d\n", index);
		#endif

		// ppPathNodesMemory
		CPathNode_extended_latest** ppPathNodesMemory = &this->m_pPathNodes.extended(this)[index];

		#ifdef SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE
		iBuffer += sprintf(iBuffer, "m_pPathNodes = 0x%X\n", (unsigned int)*ppPathNodesMemory);
		#endif

		if (*ppPathNodesMemory)
		{
			CMemoryMgr::Free(*ppPathNodesMemory);
			*ppPathNodesMemory = NULL;
		}

		// ppPathNodesMemoryStandard
		#ifdef ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA
		CPathNode** ppPathNodesMemoryStandard = &this->m_pPathNodesStandard(this)[index];

		#ifdef SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE
		iBuffer += sprintf(iBuffer, "m_pPathNodesStandard = 0x%X\n", (unsigned int)*ppPathNodesMemoryStandard);
		#endif

		if (*ppPathNodesMemoryStandard)
		{
			CMemoryMgr::Free(*ppPathNodesMemoryStandard);
			*ppPathNodesMemoryStandard = NULL;
		}
		#endif

		// ppNaviNodesMemory
		CCarPathLink_extended_latest** ppNaviNodesMemory = &this->m_pNaviNodes.extended(this)[index];

		#ifdef SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE
		iBuffer += sprintf(iBuffer, "m_pNaviNodes = 0x%X\n", (unsigned int)*ppNaviNodesMemory);
		#endif

		if (*ppNaviNodesMemory)
		{
			CMemoryMgr::Free(*ppNaviNodesMemory);
			*ppNaviNodesMemory = NULL;
		}

		// ppNaviNodesMemoryStandard
		#ifdef ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA
		CCarPathLink** ppNaviNodesMemoryStandard = &this->m_pNaviNodesStandard(this)[index];

		#ifdef SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE
		iBuffer += sprintf(iBuffer, "m_pNaviNodesStandard = 0x%X\n", (unsigned int)*ppNaviNodesMemoryStandard);
		#endif

		if (*ppNaviNodesMemory)
		{
			CMemoryMgr::Free(*ppNaviNodesMemoryStandard);
			*ppNaviNodesMemoryStandard = NULL;
		}
		#endif

		// ppNodeLinksData
		CNodeAddress** ppNodeLinksData = &this->m_pNodeLinks(this)[index];

		#ifdef SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE
		iBuffer += sprintf(iBuffer, "m_pNodeLinks = 0x%X\n", (unsigned int)*ppNodeLinksData);
		#endif

		if (*ppNodeLinksData)
		{
			CMemoryMgr::Free(*ppNodeLinksData);
			*ppNodeLinksData = NULL;
		}

		// ppNaviLinksData
		CLinkAddress_extended** ppNaviLinksData = &this->m_pNaviLinks.extended(this)[index];

		#ifdef SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE
		iBuffer += sprintf(iBuffer, "m_pNaviLinks = 0x%X\n", (unsigned int)*ppNaviLinksData);
		#endif

		if (*ppNaviLinksData)
		{
			CMemoryMgr::Free(*ppNaviLinksData);
			*ppNaviLinksData = NULL;
		}

		// ppLinkLengthsData
		uint8_t** ppLinkLengthsData = &this->m_pLinkLengths(this)[index];

		#ifdef SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE
		iBuffer += sprintf(iBuffer, "m_pLinkLengths = 0x%X\n", (unsigned int)*ppLinkLengthsData);
		#endif

		if (*ppLinkLengthsData)
		{
			CMemoryMgr::Free(*ppLinkLengthsData);
			*ppLinkLengthsData = NULL;
		}

		// ppPathIntersectionsData
		CPathIntersectionInfo** ppPathIntersectionsData = &this->m_pPathIntersections(this)[index];

		#ifdef SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE
		iBuffer += sprintf(iBuffer, "m_pPathIntersections = 0x%X\n", (unsigned int)*ppPathIntersectionsData);
		#endif

		if (*ppPathIntersectionsData)
		{
			CMemoryMgr::Free(*ppPathIntersectionsData);
			*ppPathIntersectionsData = NULL;
		}

		#ifdef SHOW_DEBUG_MESSAGES_FOR_LOADED_PATH_FILE
		CGenericLogStorage::SaveFormattedTextLn(buffer);
		#endif
	}

	// Loads scene for path nodes
	void CPathFind_extended::LoadSceneForPathNodes(CVector pos)
	{
		// OutputFormattedDebugString("pos: %f %f %f", pos.x, pos.y, pos.z);

		unsigned iNumberOfPathFilesPerDimension = g_mapLimits.ms_pathsMapSize / g_mapLimits.ms_pathBlockSize;
		unsigned int iTotalNumberOfPathFiles = iNumberOfPathFilesPerDimension * iNumberOfPathFilesPerDimension;

		bool* ToBeStreamed = g_mapLimits.ToBeStreamed.ptr;

		memset(ToBeStreamed, NULL, iTotalNumberOfPathFiles);

		this->MarkRegionsForCoors(pos, 350.0);

		//////
		unsigned int FILE_TYPE_PATH_BASE_ID = g_fileIDlimits.GetBaseID(GENERAL_FILE_TYPE_PATH_NODES);

		unsigned int blockY = 0;

		do
		{
			unsigned int blockX = 0;

			do
			{
				if (ToBeStreamed[blockY * iNumberOfPathFilesPerDimension + blockX])
				{
					unsigned int PATH_ID = blockY + blockX * iNumberOfPathFilesPerDimension;

					CStreaming::RequestModel(
						FILE_TYPE_PATH_BASE_ID + PATH_ID,
						0);
				}

				++blockX;
			} while (blockX < iNumberOfPathFilesPerDimension);

			++blockY;

		} while (blockY < iNumberOfPathFilesPerDimension);
	}

	static uintptr_t Address_CPathFind_MarkRegionsForCoors = 0;

	// Marks region for coordinates
	void CPathFind_extended::MarkRegionsForCoors(CVector pos, float radius)
	{
		g_memoryCall.Function<void>(Address_CPathFind_MarkRegionsForCoors, pos, radius);
	}

	// Returns interior node index
	CNodeAddress CPathFind_extended::ReturnInteriorNodeIndex(unsigned int InteriorID, int nodeIndex)
	{
		CNodeAddress result;
		result.nodeId = nodeIndex;

		MapLimits* pMapLimits = &g_mapLimits;

		for (unsigned int ID = 0; ID < iNumberOfPathInteriorSlots; ID++)
		{
			if (this->m_interiorAreaIDarray(this)[ID] == InteriorID)
			{
				result.areaId = pMapLimits->iTotalNumberOfPathIndices + ID;
				return result;
			}
		}

		result.areaId = -1;

		return result;
	}

	// Checks grid
	void CPathFind_extended::CheckGrid() {

	}

	// Post process path node
	void CPathFind_extended::PostProcessPathNode(CPathNode_extended_latest* node, ePathType pathType)
	{
		#if PROJECT_IS_UNRELEASED_EDITION


		// node -> m_nNodeType = 159;

		CompressedVector_extended* pos = &node->CoorsExtended;

		// pos -> x += 5 * COORD_INT_MULTIPLIER;
		// pos -> y += 5 * COORD_INT_MULTIPLIER;
		// pos -> z += 2 * COORD_INT_MULTIPLIER;

		// node -> m_dwFlags = BitwiseOperation::ChangeMultipleBits(node -> m_dwFlags, 4, 2, 0);

		// node->m_dwFlags = BitwiseOperation::ClearOneBit(node->m_dwFlags, 7);

		int numberOfLinks = node->GetNumberOfLinks();


		CNodeAddress* nodeLinks = this->m_pNodeLinks(this)[node->Address.areaId];

		// node->m_nFloodID = assignedFloodID++;

		/*
		BitwiseOperation::ClearMultipleBits(node -> m_dwFlags, 0, 4);

		printf_MessageBox("number of links: %d", numberOfLinks);
		std::random_shuffle(nodeLinks, nodeLinks + numberOfLinks);
		std::random_shuffle(naviLinks, naviLinks + numberOfLinks);
		*/
		// node -> m_wConnectedNodesStartId

		// node -> m_dwFlags = node -> m_dwFlags & ~(


		/*
		printf_MessageBox(
			"position: %.3f %.3f %.3f",
			(float)pos -> x / COORD_INT_MULTIPLIER,
			(float)pos -> y / COORD_INT_MULTIPLIER,
			(float)pos -> z / COORD_INT_MULTIPLIER
			);
			*/


			//node -> m_extended_posn.z += 4 * COORD_INT_MULTIPLIER;

			// (DWORD*)&node -> m_dwFlags m_PathType 
			// printf_MessageBox("nodeType: %d", node -> m_nNodeType);

		#endif
	}

	// Post process navi node
	void CPathFind_extended::PostProcessNaviNode(CCarPathLink_extended_latest* pathLink)
	{
		#if PROJECT_IS_UNRELEASED_EDITION
		// pathLink -> extended_posX += 5 * COORD_INT_MULTIPLIER;
		// pathLink -> extended_posY += 5 * COORD_INT_MULTIPLIER;
		// pathLink->dirX = 100 - pathLink->dirX;
		// pathLink->dirY = 100 - pathLink->dirY;
		// pathLink->m_nPathNodeWidth = 80;
		// pathLink->dirX = 0;
		// pathLink->dirY = 0;

		// printf_MessageBox("

		// pathLink->m_dwFlags = BitwiseOperation::ClearMultipleBits(pathLink->m_dwFlags, 0, 14);

		/*
		pathLink->m_dwFlags = BitwiseOperation::ChangeMultipleBits(pathLink->m_dwFlags, 8, 3, numberOfRightLanes);

		pathLink->m_dwFlags = BitwiseOperation::ChangeMultipleBits(
			pathLink->m_dwFlags, 11, 3,
			numberOfLeftLanes
			);
			*/

			// pathLink->dirX = -pathLink->dirX;
			// pathLink->dirY = -pathLink->dirY;


		#endif
	}

	////// CVehicle functions
	uint32_t* GetPointerToPathPointIndexElementByCVehicleOffset(CVehicle_generic* pVehicle, int offset)
	{
		return g_structureExtension.m_CLinkAddress_extension.GetPointerToExtendedData((char*)pVehicle + offset);
	};

	uint32_t __cdecl GetPathPointIndexForVehicle(CVehicle_generic* pVehicle, int offset)
	{
		uint32_t* pValue = GetPointerToPathPointIndexElementByCVehicleOffset(pVehicle, offset);

		return *pValue;
	}

	void __cdecl SetPathPointIndexForVehicle(CVehicle_generic* pVehicle, int offset, uint32_t newValue)
	{
		uint32_t* pValue = GetPointerToPathPointIndexElementByCVehicleOffset(pVehicle, offset);

		*pValue = newValue;
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void GetPathPointIndexForVehicle_hook()
	{
		// + 4 CVehicle* ptr
		// + 8 int offset
		// + 12 new value

		__asm
		{
			pushad;

			mov eax, [esp + 32 + 8];	// offset
			push eax;

			mov ecx, [esp + 36 + 4];	// CVehicle*
			push ecx;

			call GetPathPointIndexForVehicle;
			add esp, 8;

			mov[esp + 32 + 12], eax;

			popad;
			retn;
		}

		/*
		__asm
		{
			push eax;
			push ecx;

			mov	ecx, [esp+8 + 4];
			add ecx, [esp+8 + 8];

			movzx eax, word ptr [ecx];

			mov [esp+8 + 12], eax;

			pop ecx;
			pop eax;

			retn;
		}
		*/
	}

	NAKED void SetPathPointIndexForVehicle_hook()
	{
		// + 4 CVehicle* ptr
		// + 8 int offset
		// + 12 new value

		__asm
		{
			pushad;

			mov eax, [esp + 32 + 12];
			// movzx eax, word ptr[esp+32 + 12];			
			push eax;		// new value

			mov eax, [esp + 36 + 8];
			push eax;	// offset

			mov eax, [esp + 40 + 4];
			push eax;	// CVehicle* ptr

			call SetPathPointIndexForVehicle;
			add esp, 12;

			popad;

			retn;
		}
	}
	#endif
}

#ifdef IS_PLATFORM_WIN_X86
// Patches paths
void MapLimits::PatchPaths_GTA_SA_PC_1_0_HOODLUM()
{
	using namespace Game_GTASA;

	const bool bDisableLoadingPaths = false;

	// Disable paths (for debugging)
	if (bDisableLoadingPaths)
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchMemoryData(0x4529F0, "\xC2\x08\x00", 3);	// CPathFind_extended::LoadPathFindData	
		CPatch::LeaveThisLevel();

		return;
	}

	// CPatch::EnableDumpingMemoryAddressesToLogFile(false);

	if (!this->PatchPaths_DoInitialisingWork())
		return;

	// Patch pointers to ToBeStreamed
	#if TRUE
	{
		CPatch::PatchPointer(0x44DC85 + 3, ToBeStreamed.ptr);	// lea     edx, ToBeStreamed[ebx+ebp*8]
		CPatch::PatchPointer(0x450A9B + 1, ToBeStreamed.ptr);	// mov     edi, offset ToBeStreamed
		CPatch::PatchPointer(0x450CBF + 3, ToBeStreamed.ptr);	// lea     edi, ToBeStreamed[esi+ebx*8]
		CPatch::PatchPointer(0x450D00 + 3, ToBeStreamed.ptr);	// mov     al, ds:ToBeStreamed[esi+ebp*8]
		CPatch::PatchPointer(0x15656A2 + 1, ToBeStreamed.ptr);	// mov     edi, offset ToBeStreamed
		CPatch::PatchPointer(0x15656CB + 1, ToBeStreamed.ptr);	// mov     ebx, offset ToBeStreamed

		CPatch::PatchPointer(0x15656F6 + 2, ToBeStreamed.ptr + iTotalNumberOfPathFiles);	// cmp     ebx, offset DummyResult2
	}
	#endif

	// Patch pointers to ToBeStreamedForScript
	#if TRUE
	{
		CPatch::PatchPointer(0x450AA7 + 1, ToBeStreamedForScript.ptr);	// mov     edi, offset ToBeStreamedForScript
		CPatch::PatchPointer(0x450CA5 + 3, ToBeStreamedForScript.ptr);	// lea     edi, ToBeStreamedForScript[esi+ebx*8]
		CPatch::PatchPointer(0x450D11 + 3, ToBeStreamedForScript.ptr);	// mov     al, ds:ToBeStreamedForScript[esi+ebp*8]
	}
	#endif

	// Patch pointers to DontWanderGiven
	#if TRUE
	{
		CPatch::PatchPointer(0x450EAD + 2, DontWanderGiven.ptr);	// mov     ds:DontWanderGiven[ecx], al
		CPatch::PatchPointer(0x452435 + 2, DontWanderGiven.ptr);	// mov     cl, ss:DontWanderGiven[ebp]
	}
	#endif

	// Patch pointers to XCoorGiven
	#if TRUE
	{
		CPatch::PatchPointer(0x450E9E + 3, XCoorGiven.ptr);	// fstp    ds:XCoorGiven[ecx*4]
		CPatch::PatchPointer(0x450F37 + 3, XCoorGiven.ptr);	// fld     ds:XCoorGiven[eax*4]
		CPatch::PatchPointer(0x45232A + 3, XCoorGiven.ptr);	// fld     ds:XCoorGiven[ebp*4]
	}
	#endif

	// Patch pointers to YCoorGiven
	#if TRUE
	{
		CPatch::PatchPointer(0x450EB3 + 3, YCoorGiven.ptr);	// fstp    ds:YCoorGiven[ecx*4]
		CPatch::PatchPointer(0x450F46 + 3, YCoorGiven.ptr);	// fld     ds:YCoorGiven[eax*4]
		CPatch::PatchPointer(0x45231C + 3, YCoorGiven.ptr);	// fld     ds:YCoorGiven[ebp*4]
	}
	#endif

	// Patch pointers to ZCoorGiven
	#if TRUE
	{
		CPatch::PatchPointer(0x450EC3 + 3, ZCoorGiven.ptr);	// fstp    ds:ZCoorGiven[ecx*4]
		CPatch::PatchPointer(0x450F65 + 3, ZCoorGiven.ptr);	// fld     ds:ZCoorGiven[eax*4]
		CPatch::PatchPointer(0x452310 + 3, ZCoorGiven.ptr);	// fld     ds:ZCoorGiven[ebp*4]
	}
	#endif

	// Patch pointers to ConnectsToGiven
	#if TRUE
	{
		CPatch::PatchPointer(0x450ECA + 2, ConnectsToGiven.ptr);	// mov     ds:ConnectsToGiven[eax], dl
		CPatch::PatchPointer(0x450ED4 + 2, ConnectsToGiven.ptr + 1);	// mov     ds:(ConnectsToGiven+1)[eax], dl
		CPatch::PatchPointer(0x450EDE + 2, ConnectsToGiven.ptr + 2);	// mov     ds:(ConnectsToGiven+2)[eax], dl
		CPatch::PatchPointer(0x450EE8 + 2, ConnectsToGiven.ptr + 3);	// mov     ds:(ConnectsToGiven+3)[eax], dl
		CPatch::PatchPointer(0x450EF2 + 2, ConnectsToGiven.ptr + 4);	// mov     ds:(ConnectsToGiven+4)[eax], dl
		CPatch::PatchPointer(0x450EFC + 2, ConnectsToGiven.ptr + 5);	// mov     ds:(ConnectsToGiven+5)[eax], dl
		CPatch::PatchPointer(0x4524D2 + 4, ConnectsToGiven.ptr);	// mov     [esp+1Ch+arg_0], offset ConnectsToGiven
		CPatch::PatchPointer(0x4524F5 + 3, ConnectsToGiven.ptr);	// cmp     ds:ConnectsToGiven[eax+ecx*2], bl
		CPatch::PatchPointer(0x452506 + 3, ConnectsToGiven.ptr);	// cmp     ds:ConnectsToGiven[eax+ecx*2], 0
		CPatch::PatchPointer(0x45251B + 3, ConnectsToGiven.ptr);	// mov     ds:ConnectsToGiven[eax+ecx*2], bl
		CPatch::PatchPointer(0x452542 + 1, ConnectsToGiven.ptr + 1);	// mov     eax, (offset ConnectsToGiven+1)
		CPatch::PatchPointer(0x4525E5 + 4, ConnectsToGiven.ptr);	// mov     [esp+1Ch+arg_0], offset ConnectsToGiven
		CPatch::PatchPointer(0x156EC9A + 2, ConnectsToGiven.ptr);	// mov     dl, ds:ConnectsToGiven[eax]
		CPatch::PatchPointer(0x156ECAB + 3, ConnectsToGiven.ptr + 1);	// mov     dl, ds:(ConnectsToGiven+1)[ecx+eax]
		CPatch::PatchPointer(0x156ECBB + 3, ConnectsToGiven.ptr);	// mov     ds:ConnectsToGiven[ecx+eax], dl
		CPatch::PatchPointer(0x156ECC7 + 2, ConnectsToGiven.ptr);	// mov     dl, ds:ConnectsToGiven[eax]
		CPatch::PatchPointer(0x156ECD8 + 3, ConnectsToGiven.ptr + 1);	// mov     dl, ds:(ConnectsToGiven+1)[ecx+eax]
		CPatch::PatchPointer(0x156ECE4 + 3, ConnectsToGiven.ptr);	// mov     ds:ConnectsToGiven[ecx+eax], bl
	}
	#endif

	// Patch pointers to ThePaths
	#if TRUE
	{
		CPatch::PatchPointer(0x408A85 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x40CA26 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x40E77F + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x40ECAE + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x41B9CE + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x41B9E8 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x41BA07 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     eax, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x41BA20 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x41BAA0 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x41BAEA + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x4220C8 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x4220DA + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x4220EC + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x4223A4 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x4223C6 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x4223E1 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x422415 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x422445 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x422498 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x422639 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x42276D + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx]
		CPatch::PatchPointer(0x42277E + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[ecx]
		CPatch::PatchPointer(0x4242FA + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x42431A + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x42435A + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x424378 + 3, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviLinks[edx*4]
		CPatch::PatchPointer(0x424391 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx]
		CPatch::PatchPointer(0x42439B + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[ecx]
		CPatch::PatchPointer(0x42444F + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x4244B7 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42450B + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[esi]
		CPatch::PatchPointer(0x42459C + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pNodeLinks[esi]
		CPatch::PatchPointer(0x4245A8 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x4245B7 + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviLinks[esi]
		CPatch::PatchPointer(0x4245C4 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x424B5F + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x424B77 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x424B94 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x424C2A + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x424C4F + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x424C5E + 3, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.m_pNodeLinks[ecx*4]
		CPatch::PatchPointer(0x424C93 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x426F87 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edi]
		CPatch::PatchPointer(0x42704D + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x4270DF + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edi]
		CPatch::PatchPointer(0x4270FD + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pNodeLinks[edi]
		CPatch::PatchPointer(0x427136 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edi]
		CPatch::PatchPointer(0x427159 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pNodeLinks[edi]
		CPatch::PatchPointer(0x4271AA + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edi]
		CPatch::PatchPointer(0x4271F0 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edi]
		CPatch::PatchPointer(0x427205 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pNodeLinks[edi]
		CPatch::PatchPointer(0x427234 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x4273CC + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edi]
		CPatch::PatchPointer(0x4273D7 + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviLinks[edi]
		CPatch::PatchPointer(0x427442 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x42746E + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x4274D1 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.pNaviNodes[ebp*4]
		CPatch::PatchPointer(0x4274F8 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x42750F + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x42753B + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x427568 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x427599 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x4275D1 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x4275FC + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x4276FD + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x427720 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x427806 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x427900 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x427914 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pNodeLinks[eax]
		CPatch::PatchPointer(0x42793E + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviLinks[eax]
		CPatch::PatchPointer(0x42794F + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x4279AE + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x4279DD + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x427A16 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x427A41 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x427A81 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x427ABB + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x427B1C + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.pNaviNodes[ebp*4]
		CPatch::PatchPointer(0x427B47 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.pNaviNodes[ebp*4]
		CPatch::PatchPointer(0x427B72 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.pNaviNodes[ebp*4]
		CPatch::PatchPointer(0x427B93 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.pNaviNodes[ebp*4]
		CPatch::PatchPointer(0x427BB1 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x427BE1 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x427C21 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x427C3E + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x427D08 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x427D3E + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x427D76 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x427D9D + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x427DEC + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x427E1A + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x427E99 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.pNaviNodes[ebx*4]
		CPatch::PatchPointer(0x427EC1 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x427EEF + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x427F1D + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x427F8A + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x427FA6 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x4280BD + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edx]
		CPatch::PatchPointer(0x4280D6 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.m_pPathNodes[esi]
		CPatch::PatchPointer(0x4280E4 + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edx]
		CPatch::PatchPointer(0x4280EA + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[esi]
		CPatch::PatchPointer(0x4281B6 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     eax, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x42825E + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     eax, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x42B4AA + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42B4C0 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.m_pNodeLinks[eax]
		CPatch::PatchPointer(0x42B4F9 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.m_pPathNodes[edi*4]
		CPatch::PatchPointer(0x42B50A + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviLinks[eax]
		CPatch::PatchPointer(0x42B55F + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x42B587 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x42B59F + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42B5D6 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x42B5E5 + 3, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pNodeLinks[ecx*4]
		CPatch::PatchPointer(0x42B617 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x42B633 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     eax, ds:ThePaths.m_pPathNodes[ebx*4]
		CPatch::PatchPointer(0x42B714 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42B744 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x42B75C + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviLinks[eax]
		CPatch::PatchPointer(0x42B76D + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pNodeLinks[eax]
		CPatch::PatchPointer(0x42B784 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x42B883 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42BA2C + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42BA49 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x42BD5A + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x42BD79 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x42BD93 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x42BDB2 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x42BE85 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[edx]
		CPatch::PatchPointer(0x42BE95 + 2, &ThePaths.gta_sa->m_dwNumVehicleNodes(ThePaths.gta_sa));	// cmp     ds:ThePaths.NumVehicleNodes[edx], edi
		CPatch::PatchPointer(0x42BEB0 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.m_pPathNodes[edx]
		CPatch::PatchPointer(0x42BF65 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     esi, ds:ThePaths.m_pNodeLinks[edx]
		CPatch::PatchPointer(0x42BF73 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42C1AD + 2, &ThePaths.gta_sa->m_dwNumVehicleNodes(ThePaths.gta_sa));	// mov     esi, ds:ThePaths.NumVehicleNodes[edx]
		CPatch::PatchPointer(0x42C36F + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42DAB7 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42DB05 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     esi, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x42DEAE + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x42DEC9 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x42DEE5 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.m_pPathNodes[edi*4]
		CPatch::PatchPointer(0x42DF08 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edi]
		CPatch::PatchPointer(0x42DF2A + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.pNaviNodes[ebx*4]
		CPatch::PatchPointer(0x42DF5D + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x42DF79 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x42DF9C + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x42DFB8 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x42E083 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edi]
		CPatch::PatchPointer(0x42E094 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pNodeLinks[edi]
		CPatch::PatchPointer(0x42E0A8 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x42E0CE + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edi]
		CPatch::PatchPointer(0x42E0E1 + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviLinks[edi]
		CPatch::PatchPointer(0x42E0F8 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax]
		CPatch::PatchPointer(0x42E12A + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[eax]
		CPatch::PatchPointer(0x42E21D + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[edi]
		CPatch::PatchPointer(0x42E228 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pNodeLinks[edi]
		CPatch::PatchPointer(0x42E240 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42E24F + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[edi]
		CPatch::PatchPointer(0x42E25A + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviLinks[edi]
		CPatch::PatchPointer(0x42E276 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax]
		CPatch::PatchPointer(0x42E286 + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[eax]
		CPatch::PatchPointer(0x42E2E2 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x42E30B + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x42E37E + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edi]
		CPatch::PatchPointer(0x42E389 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pNodeLinks[edi]
		CPatch::PatchPointer(0x42E39D + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x42E3AC + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edi]
		CPatch::PatchPointer(0x42E3B9 + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviLinks[edi]
		CPatch::PatchPointer(0x42E3D3 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax]
		CPatch::PatchPointer(0x42E3DF + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[eax]
		CPatch::PatchPointer(0x42E4D8 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x42E5C0 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42E692 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx]
		CPatch::PatchPointer(0x42E69C + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[ecx]
		CPatch::PatchPointer(0x42E6CD + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx]
		CPatch::PatchPointer(0x42E6D7 + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[ecx]
		CPatch::PatchPointer(0x42E71F + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.pNaviNodes[ebp*4]
		CPatch::PatchPointer(0x42E73E + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[ecx]
		CPatch::PatchPointer(0x42E750 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x42E7DC + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x42E805 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x42E82E + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x42E857 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x42E880 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x42E8A9 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x42E8DE + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42E8FF + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42EA06 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x42EA3C + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x42EA74 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x42EA9B + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x42EAEA + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x42EB1C + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x42EB97 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.pNaviNodes[ebx*4]
		CPatch::PatchPointer(0x42EBBF + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x42EBED + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x42EC1B + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x42F619 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x42F63B + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[eax]
		CPatch::PatchPointer(0x42F677 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pNodeLinks[eax]
		CPatch::PatchPointer(0x42F695 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x42F7CE + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x42FEB8 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x42FF77 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x43047F + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x430489 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ebx]
		CPatch::PatchPointer(0x4304CE + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ebx]
		CPatch::PatchPointer(0x43058B + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ebx]
		CPatch::PatchPointer(0x4305AF + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pNodeLinks[ebx]
		CPatch::PatchPointer(0x4305CD + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviLinks[ebx]
		CPatch::PatchPointer(0x4305F1 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x430951 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ebx]
		CPatch::PatchPointer(0x43098B + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x430AB2 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ebx]
		CPatch::PatchPointer(0x430AE4 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ebx]
		CPatch::PatchPointer(0x430AF7 + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviLinks[ebx]
		CPatch::PatchPointer(0x430B17 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x430B26 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ebx]
		CPatch::PatchPointer(0x430B39 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pNodeLinks[ebx]
		CPatch::PatchPointer(0x430B62 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x430B6D + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ebx]
		CPatch::PatchPointer(0x430C9D + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x430CC1 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x430D13 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x430D43 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x430DA3 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x430DCD + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x430E0F + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x430E88 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x430EB4 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x430EEF + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x430F19 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x430F5C + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x431028 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x43104C + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x43108B + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x4310C1 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x4310FB + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x43113B + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x4311A2 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x431204 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x431235 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x431272 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x4312B8 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x431332 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.pNaviNodes[ebx*4]
		CPatch::PatchPointer(0x43135A + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x43137D + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x4313BB + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x431486 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.pNaviNodes[ebx*4]
		CPatch::PatchPointer(0x4314C4 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x4314FD + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.pNaviNodes[ebx*4]
		CPatch::PatchPointer(0x431541 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x4315D4 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx]
		CPatch::PatchPointer(0x4315E9 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x432B29 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x432B55 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x433BC8 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x433BE1 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x433BFB + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x433C13 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x433EC8 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x433EE1 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x433F01 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ebp, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x433F15 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x434975 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x434992 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x4349C0 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x4349EA + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x434A28 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x434A5E + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x434A8C + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x434ACC + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x434B27 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x434B5F + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x434B7F + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x434BC6 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x434E70 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x434E89 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x434EA9 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x434EF4 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.pNaviNodes[ebp*4]
		CPatch::PatchPointer(0x434F31 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.pNaviNodes[ebp*4]
		CPatch::PatchPointer(0x434F86 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x434FBC + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x434FF7 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.pNaviNodes[ebp*4]
		CPatch::PatchPointer(0x43502D + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x43506D + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x435096 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x43513B + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x43515C + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x435394 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x4353E0 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.pNaviNodes[ebp*4]
		CPatch::PatchPointer(0x435416 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x4358CC + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x4358E8 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x435907 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.pNaviNodes[ebx*4]
		CPatch::PatchPointer(0x435930 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.pNaviNodes[ebx*4]
		CPatch::PatchPointer(0x435950 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.pNaviNodes[ebx*4]
		CPatch::PatchPointer(0x435987 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.pNaviNodes[ebx*4]
		CPatch::PatchPointer(0x435AFE + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x435C07 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x435C27 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pNodeLinks[eax]
		CPatch::PatchPointer(0x435C48 + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviLinks[eax]
		CPatch::PatchPointer(0x435C5F + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x435D33 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x435E7D + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x435E9F + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x435F0A + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x435F2C + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x435FAA + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.pNaviNodes[ebx*4]
		CPatch::PatchPointer(0x435FD4 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x435FEC + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x436036 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x43607F + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x4360A1 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x436119 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ebx, ds:ThePaths.pNaviNodes[ebx*4]
		CPatch::PatchPointer(0x436146 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x436188 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x436198 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[eax*4]
		CPatch::PatchPointer(0x436603 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x43663F + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x43667D + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edi*4]
		CPatch::PatchPointer(0x4366B3 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x4366E1 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x436725 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x43684C + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x43686E + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x4368CA + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x4368FC + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x437D1A + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x44055C + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x444878 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x445441 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x445484 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x4454AA + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x4458A6 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x4458BD + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x45064D + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x450F87 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x450FB7 + 3, ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa) + iTotalNumberOfPathFiles);	// mov     edx, ds:ThePaths.m_pNodeLinks+100h[ecx*4]
		CPatch::PatchPointer(0x450FE4 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x45100D + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x45128E + 3, ThePaths.gta_sa->m_pLinkLengths(ThePaths.gta_sa) + iTotalNumberOfPathFiles);	// mov     edx, ds:ThePaths.pLinkLengths+100h[eax*4]
		CPatch::PatchPointer(0x451298 + 3, ThePaths.gta_sa->m_pPathIntersections(ThePaths.gta_sa) + iTotalNumberOfPathFiles);	// mov     ecx, ds:ThePaths.pPathIntersections+100h[eax*4]
		CPatch::PatchPointer(0x4512A6 + 3, ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa) + iTotalNumberOfPathFiles);	// mov     eax, ds:ThePaths.m_pPathNodes+100h[eax*4]
		CPatch::PatchPointer(0x460EF2 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx]
		CPatch::PatchPointer(0x460EF8 + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviLinks[ecx]
		CPatch::PatchPointer(0x460F1A + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[edx]
		CPatch::PatchPointer(0x460F34 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.m_pPathNodes[esi]
		CPatch::PatchPointer(0x460F42 + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edi, ds:ThePaths.pNaviNodes[edx]
		CPatch::PatchPointer(0x460F48 + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviNodes[esi]
		CPatch::PatchPointer(0x462AC7 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x462EF4 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x4657F9 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x465897 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x4658B1 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x4658D8 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x46864B + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x468669 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x468673 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x473768 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x476AB3 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x476B89 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x478E30 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x478E41 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths; jumptable 00478037 case 53
		CPatch::PatchPointer(0x47DC2B + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x47DD0F + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x47EBB1 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x47ECA2 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x47FB62 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x47FB8C + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x47FC5A + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x47FC71 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x4852E0 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x4852F7 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x48531C + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x48B815 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x48B839 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x48B872 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x48BE76 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x48BE90 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x491483 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x491494 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths; jumptable 00490DE7 case 43
		CPatch::PatchPointer(0x49898D + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x4989A4 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x4989C9 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x49D459 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x49D478 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     esi, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x49D493 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     esi, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x49D4B4 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviNodes[ecx*4]
		CPatch::PatchPointer(0x49D651 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x49D670 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     eax, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x49D7C7 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x49D7E6 + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     eax, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x49D93D + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x49D95C + 3, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// add     eax, ds:ThePaths.pNaviNodes[edx*4]
		CPatch::PatchPointer(0x53BC30 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x53BD60 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x53BFD3 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x565D6F + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x565DCC + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x565F8C + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x565FF8 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x570248 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x571684 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595306 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595572 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5955B4 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595617 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595649 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x59565A + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x59569E + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5956B2 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5956D7 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595789 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5957B1 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5957D5 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x59584A + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595856 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595866 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595890 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ebp*4]
		CPatch::PatchPointer(0x59593E + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ebp*4]
		CPatch::PatchPointer(0x5959D6 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595A1E + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595A44 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595A68 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595AD6 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595AE6 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595AF6 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595B20 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ebp*4]
		CPatch::PatchPointer(0x595BBC + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ebp*4]
		CPatch::PatchPointer(0x595C54 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595C9C + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595CC2 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595CE6 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595D54 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595D64 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595D74 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595D9E + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ebp*4]
		CPatch::PatchPointer(0x595E34 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ebp*4]
		CPatch::PatchPointer(0x595EC6 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595F0E + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595F34 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595F58 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595FC1 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595FD1 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x595FE1 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x59600B + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ebp*4]
		CPatch::PatchPointer(0x5960B9 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ebp*4]
		CPatch::PatchPointer(0x596151 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x596188 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5961A5 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5961C2 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5961E5 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x596202 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x59646B + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x59658B + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5965B8 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x59F7DA + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5A0C82 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5B4309 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5B4366 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5B449E + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5B451B + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5B6E80 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5BA1D0 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5BF99B + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5BF9A5 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5D14FD + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths; jumptable 005D14A3 case 5
		CPatch::PatchPointer(0x5D1925 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths; jumptable 005D18A2 case 5
		CPatch::PatchPointer(0x5E11BB + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5E11F7 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x5E1220 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x5E125B + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x6134FA + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x613562 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x614B17 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x614B3B + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x614B53 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x614B96 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x616549 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x64CF8A + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x64CFA3 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x669A0F + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x669A99 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x669B22 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x669BAC + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x669C4D + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x669DC5 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x669DD7 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x669F18 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x669F7B + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x66A009 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x66A030 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x66A07E + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x66A0A5 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x66F044 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x66F0A0 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x66F0C5 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x66F170 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x66F195 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x66F246 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x66F2D9 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x66F30C + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x66F352 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x66F388 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x66F3A9 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x66F3DB + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x66F548 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x671F07 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x674468 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x674498 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x6767E4 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     ecx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x6F3BDF + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x6F3C08 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     eax, ds:ThePaths.m_pPathNodes[ecx]
		CPatch::PatchPointer(0x6F3C18 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pNodeLinks[ecx]
		CPatch::PatchPointer(0x6F3C24 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x1567AEC + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     esi, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x1567B09 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     esi, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x1567B24 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     esi, ds:ThePaths.m_pPathNodes[ecx*4]
		CPatch::PatchPointer(0x1567B3F + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x1569722 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// add     eax, ds:ThePaths.m_pPathNodes[ecx]
		CPatch::PatchPointer(0x156973A + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.m_pNodeLinks[ecx]
		CPatch::PatchPointer(0x1569F55 + 3, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pNodeLinks[eax*4]
		CPatch::PatchPointer(0x156A1C2 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     esi, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x156A1D4 + 3, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pNodeLinks[edx*4]
		CPatch::PatchPointer(0x156A1FF + 3, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     ecx, ds:ThePaths.pNaviLinks[edx*4]
		CPatch::PatchPointer(0x156A54D + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x156D1F0 + 1, ThePaths.gta_sa);	// mov     ecx, offset ThePaths
		CPatch::PatchPointer(0x156E9E6 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x156E9FC + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x156EA1C + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x156EA38 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.m_pNodeLinks[ebx]
		CPatch::PatchPointer(0x156EA45 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x156EA8D + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x156EA99 + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviLinks[ebx]
		CPatch::PatchPointer(0x156EAAD + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// cmp     ds:ThePaths.m_pPathNodes[eax], 0
		CPatch::PatchPointer(0x156EAB6 + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[eax]
		CPatch::PatchPointer(0x156EAD5 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x156EB11 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     esi, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x156EB31 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.m_pPathNodes[eax*4]
		CPatch::PatchPointer(0x156EB52 + 2, &ThePaths.gta_sa->m_pNodeLinks(ThePaths.gta_sa));	// mov     ebp, ds:ThePaths.m_pNodeLinks[ebx]
		CPatch::PatchPointer(0x156EB60 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x156EB99 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
		CPatch::PatchPointer(0x156EBAF + 2, &ThePaths.gta_sa->m_pNaviLinks.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.pNaviLinks[ebx]
		CPatch::PatchPointer(0x156EBC3 + 2, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// cmp     ds:ThePaths.m_pPathNodes[eax], 0
		CPatch::PatchPointer(0x156EBCC + 2, &ThePaths.gta_sa->m_pNaviNodes.extended(ThePaths.gta_sa));	// mov     eax, ds:ThePaths.pNaviNodes[eax]
		CPatch::PatchPointer(0x156EBE7 + 3, &ThePaths.gta_sa->m_pPathNodes.extended(ThePaths.gta_sa));	// mov     edx, ds:ThePaths.m_pPathNodes[edx*4]
	}
	#endif

	// Patch CPathFind absolute offsets
	#if TRUE
	{
		// Offset_CPathFind__m_fForbiddenForScrCarsY2
		#if TRUE
		{
			CPatch::PatchUINT32(0x450C51 + 2, CPathFind::m_fForbiddenForScrCarsY2.GetOffset());	// fld     dword ptr [ebx+3C7Ch]
			CPatch::PatchUINT32(0x450DB0 + 2, CPathFind::m_fForbiddenForScrCarsY2.GetOffset());	// mov     eax, [ecx+3C7Ch]
			CPatch::PatchUINT32(0x156A6DB + 2, CPathFind::m_fForbiddenForScrCarsY2.GetOffset());	// mov     [ecx+3C7Ch], edx
		}
		#endif

		// Offset_CPathFind__m_fForbiddenForScrCarsY1
		#if TRUE
		{
			CPatch::PatchUINT32(0x450C24 + 2, CPathFind::m_fForbiddenForScrCarsY1.GetOffset());	// fld     dword ptr [ebx+3C78h]
			CPatch::PatchUINT32(0x450DB6 + 2, CPathFind::m_fForbiddenForScrCarsY1.GetOffset());	// mov     edx, [ecx+3C78h]
			CPatch::PatchUINT32(0x156A6D5 + 2, CPathFind::m_fForbiddenForScrCarsY1.GetOffset());	// mov     [ecx+3C78h], eax
		}
		#endif

		// Offset_CPathFind__m_fForbiddenForScrCarsX2
		#if TRUE
		{
			CPatch::PatchUINT32(0x450BEF + 2, CPathFind::m_fForbiddenForScrCarsX2.GetOffset());	// fld     dword ptr [ebx+3C74h]
			CPatch::PatchUINT32(0x450DBD + 2, CPathFind::m_fForbiddenForScrCarsX2.GetOffset());	// mov     eax, [ecx+3C74h]
			CPatch::PatchUINT32(0x156A6C2 + 2, CPathFind::m_fForbiddenForScrCarsX2.GetOffset());	// mov     [ecx+3C74h], edx
		}
		#endif

		// Offset_CPathFind__m_fForbiddenForScrCarsX1
		#if TRUE
		{
			CPatch::PatchUINT32(0x450BC2 + 2, CPathFind::m_fForbiddenForScrCarsX1.GetOffset());	// fld     dword ptr [ebx+3C70h]
			CPatch::PatchUINT32(0x450DC4 + 2, CPathFind::m_fForbiddenForScrCarsX1.GetOffset());	// mov     edx, [ecx+3C70h]
			CPatch::PatchUINT32(0x156A6B8 + 2, CPathFind::m_fForbiddenForScrCarsX1.GetOffset());	// mov     [ecx+3C70h], eax
		}
		#endif

		// Offset_CPathFind__m_bForbiddenForScriptedCarsEnabled
		#if TRUE
		{
			CPatch::PatchUINT32(0x450BB4 + 2, CPathFind::m_bForbiddenForScriptedCarsEnabled.GetOffset());	// mov     al, [ebx+3C6Ch]
			CPatch::PatchUINT32(0x1560DD0 + 2, CPathFind::m_bForbiddenForScriptedCarsEnabled.GetOffset());	// mov     [ecx+3C6Ch], dl
			CPatch::PatchUINT32(0x1561B10 + 2, CPathFind::m_bForbiddenForScriptedCarsEnabled.GetOffset());	// mov     byte ptr [ecx+3C6Ch], 0
			CPatch::PatchUINT32(0x156A602 + 2, CPathFind::m_bForbiddenForScriptedCarsEnabled.GetOffset());	// mov     [ecx+3C6Ch], al
			CPatch::PatchUINT32(0x156A6CE + 2, CPathFind::m_bForbiddenForScriptedCarsEnabled.GetOffset());	// mov     byte ptr [ecx+3C6Ch], 1
		}
		#endif

		// Offset_CPathFind__m_aForbiddenAreas
		#if TRUE
		{
			CPatch::PatchUINT32(0x452CDA + 2, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, z2));	// lea     eax, [ebp+3580h]
			CPatch::PatchUINT32(0x452CE4 + 2, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, y2));	// lea     eax, [ebp+3578h]
			CPatch::PatchUINT32(0x452CEE + 2, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, x2));	// lea     eax, [ebp+3570h]
			CPatch::PatchUINT32(0x452CF4 + 2, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, z1));	// lea     esi, [ebp+357Ch]
			CPatch::PatchUINT32(0x452CFA + 2, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, y1));	// lea     edi, [ebp+3574h]
			CPatch::PatchUINT32(0x452D00 + 2, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, x1));	// lea     edx, [ebp+356Ch]
			CPatch::PatchUINT32(0x452D06 + 2, CPathFind::m_aForbiddenAreas.GetOffset() + sizeof(CForbiddenArea));	// lea     ebx, [ebp+3588h]
			CPatch::PatchUINT32(0x452E4F + 3, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, x1));	// fstp    dword ptr [eax+ebp+356Ch]
			CPatch::PatchUINT32(0x452E63 + 3, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, x2));	// fstp    dword ptr [edx+ebp+3570h]
			CPatch::PatchUINT32(0x452E77 + 3, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, y1));	// fstp    dword ptr [eax+ebp+3574h]
			CPatch::PatchUINT32(0x452E8B + 3, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, y2));	// fstp    dword ptr [ecx+ebp+3578h]
			CPatch::PatchUINT32(0x452EB9 + 3, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, z2));	// fstp    dword ptr [eax+ebp+3580h]
			CPatch::PatchUINT32(0x452EC9 + 3, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, bEnable));	// mov     [ecx+ebp+3584h], dl
			CPatch::PatchUINT32(0x452EDD + 3, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, type));	// mov     [eax+ebp+3585h], cl
			CPatch::PatchUINT32(0x5D34DE + 2, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, x1));	// add     ebx, 356Ch
			CPatch::PatchUINT32(0x5D351E + 2, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, x1));	// add     ebx, 356Ch
			CPatch::PatchUINT32(0x156F9B3 + 2, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, bEnable));	// lea     ebx, [esi+3584h]

			// 489
			CPatch::EnterNewLevelAndDisableDebugState();
			{
				CPatch::PatchUINT32(0x452E9C + 2, CPathFind::m_aForbiddenAreas.GetOffset() + offsetof(CForbiddenArea, z1));	// add     edx, 1E9h
				CPatch::NOPinstructions(0x452EA2, 3);
			}
			CPatch::LeaveThisLevel();
		}
		#endif

		// Offset_CPathFind__m_dwNumForbiddenAreas
		#if TRUE
		{
			CPatch::PatchUINT32(0x401956 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     eax, [ebp+3568h]
			CPatch::PatchUINT32(0x452D86 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     edi, [ebp+3568h]
			CPatch::PatchUINT32(0x452D9E + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     ecx, [ebp+3568h]
			CPatch::PatchUINT32(0x452DB6 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     edi, [ebp+3568h]
			CPatch::PatchUINT32(0x452DD3 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     [ebp+3568h], edi
			CPatch::PatchUINT32(0x452E07 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     eax, [ebp+3568h]
			CPatch::PatchUINT32(0x452E39 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     eax, [ebp+3568h]
			CPatch::PatchUINT32(0x452E56 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     edx, [ebp+3568h]
			CPatch::PatchUINT32(0x452E6A + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     eax, [ebp+3568h]
			CPatch::PatchUINT32(0x452E7E + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     ecx, [ebp+3568h]
			CPatch::PatchUINT32(0x452E92 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     edx, [ebp+3568h]
			CPatch::PatchUINT32(0x452EA8 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     eax, [ebp+3568h]
			CPatch::PatchUINT32(0x452EC0 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     ecx, [ebp+3568h]
			CPatch::PatchUINT32(0x452ED0 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     eax, [ebp+3568h]
			CPatch::PatchUINT32(0x452EE4 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// inc     dword ptr [ebp+3568h]
			CPatch::PatchUINT32(0x5D34C5 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// lea     edi, [ebx+3568h]
			CPatch::PatchUINT32(0x5D3505 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// lea     edi, [ebx+3568h]
			CPatch::PatchUINT32(0x1560DCA + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     [ecx+3568h], edx
			CPatch::PatchUINT32(0x156A608 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     [ecx+3568h], eax
			CPatch::PatchUINT32(0x156DE10 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     eax, [ecx+3568h]
			CPatch::PatchUINT32(0x156DE20 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     [ecx+3568h], eax
			CPatch::PatchUINT32(0x156F9A7 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     eax, [esi+3568h]
			CPatch::PatchUINT32(0x156F9E7 + 2, CPathFind::m_dwNumForbiddenAreas.GetOffset());	// mov     eax, [esi+3568h]
		}
		#endif

		// Offset_CPathFind__m_interiorNodes
		#if TRUE
		{
			CPatch::PatchUINT32(0x451306 + 2, CPathFind::m_interiorAreaIDarray.GetOffset());	// add     ecx, 3548h
			CPatch::PatchUINT32(0x4522CC + 3, CPathFind::m_interiorAreaIDarray.GetOffset());	// mov     [edi+ecx*4+3548h], eax
			CPatch::PatchUINT32(0x1560E0D + 2, CPathFind::m_interiorAreaIDarray.GetOffset());	// lea     edi, [ecx+3548h]
			CPatch::PatchUINT32(0x156AD62 + 2, CPathFind::m_interiorAreaIDarray.GetOffset());	// mov     esi, [ecx+3548h]
			CPatch::PatchUINT32(0x156AD76 + 3, CPathFind::m_interiorAreaIDarray.GetOffset());	// cmp     [ecx+eax*4+3548h], edx
		}
		#endif

		// Offset_CPathFind__m_dwTotalNumNodesInSearchList
		#if TRUE
		{
			CPatch::PatchUINT32(0x4515E5 + 2, CPathFind::m_dwTotalNumNodesInSearchList.GetOffset());	// mov     dword ptr [esi+3544h], 0
			CPatch::PatchUINT32(0x451777 + 2, CPathFind::m_dwTotalNumNodesInSearchList.GetOffset());	// inc     dword ptr [esi+3544h]
			CPatch::PatchUINT32(0x4518E4 + 2, CPathFind::m_dwTotalNumNodesInSearchList.GetOffset());	// dec     dword ptr [esi+3544h]
			CPatch::PatchUINT32(0x451934 + 2, CPathFind::m_dwTotalNumNodesInSearchList.GetOffset());	// inc     dword ptr [esi+3544h]
			CPatch::PatchUINT32(0x45196A + 2, CPathFind::m_dwTotalNumNodesInSearchList.GetOffset());	// dec     dword ptr [esi+3544h]
			CPatch::PatchUINT32(0x451982 + 2, CPathFind::m_dwTotalNumNodesInSearchList.GetOffset());	// mov     eax, [esi+3544h]
		}
		#endif

		// Offset_CPathFind__field_1544
		#if TRUE
		{
			// array index 0
			CPatch::PatchUINT32(0x1560D1A + 3, CPathFind::m_field_1544.GetOffset());	// lea     esi, [ecx+esi+1544h]
			CPatch::PatchUINT32(0x1560D3C + 3, CPathFind::m_field_1544.GetOffset());	// mov     [ecx+edx*4+1544h], esi
			CPatch::PatchUINT32(0x156F9F8 + 3, CPathFind::m_field_1544.GetOffset());	// lea     eax, [esi+edi+1544h]

			// array index 1024
			CPatch::PatchUINT32(0x1560D43 + 3, CPathFind::m_field_1544.GetOffset() + iTotalNumberOfPathFiles * sizeof(__int32) * CPathFind_field_1544_numberOfElementsPerPathFile);	// mov     [ecx+edx*4+2544h], ebp	; _ZN9CPathFind36AddDynamicLinkBetween2Nodes_For1NodeE20CNodeAddress_HOODLUMS0_
			CPatch::PatchUINT32(0x156434F + 2, CPathFind::m_field_1544.GetOffset() + iTotalNumberOfPathFiles * sizeof(__int32) * CPathFind_field_1544_numberOfElementsPerPathFile);	// lea     ecx, [edi+2544h]	; _ZN9CPathFind14RemoveInteriorEj
		}
		#endif

		// Offset_CPathFind__NumAddresses
		#if TRUE
		{
			// array index 0
			CPatch::PatchUINT32(0x1560C2A + 3, CPathFind::m_dwNumAddresses.GetOffset());	// mov     ebp, [ecx+eax*4+1424h]	; _ZN9CPathFind36AddDynamicLinkBetween2Nodes_For1NodeE20CNodeAddress_HOODLUMS0_
			CPatch::PatchUINT32(0x156F7A0 + 3, CPathFind::m_dwNumAddresses.GetOffset());	// lea     ebp, [esi+edi*4+1424h]	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami

			// array index iTotalNumberOfPathFile
			CPatch::PatchUINT32(0x4526ED + 3, CPathFind::m_dwNumAddresses.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     [edi+eax*4+1524h], ebp	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
		}
		#endif

		// Offset_CPathFind__NumCarPathLinks
		#if TRUE
		{
			// array index 0
			CPatch::PatchUINT32(0x44D968 + 2, CPathFind::m_dwNumCarPathLinks.GetOffset());	// lea     edx, [ecx+1304h]
			CPatch::PatchUINT32(0x156F78E + 3, CPathFind::m_dwNumCarPathLinks.GetOffset());	// lea     eax, [esi+edi*4+1304h]
			CPatch::PatchUINT32(0x156F7F6 + 3, CPathFind::m_dwNumCarPathLinks.GetOffset());	// mov     eax, [esi+edi*4+1304h]
			CPatch::PatchUINT32(0x156F80C + 3, CPathFind::m_dwNumCarPathLinks.GetOffset());	// mov     ecx, [esi+edi*4+1304h]

			// array index iTotalNumberOfPathFile
			CPatch::PatchUINT32(0x4526E1 + 3, CPathFind::m_dwNumCarPathLinks.GetOffset() + iTotalNumberOfPathFiles * sizeof(uint32_t));	// mov     [edi+edx*4+1404h], esi	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
		}
		#endif

		// Offset_CPathFind__NumPedNodes
		#if TRUE
		{
			// array index 0
			CPatch::PatchUINT32(0x44E81F + 3, CPathFind::m_dwNumPedNodes.GetOffset());	// mov     eax, [edi+ebp*4+11E4h]
			CPatch::PatchUINT32(0x44E837 + 3, CPathFind::m_dwNumPedNodes.GetOffset());	// idiv    dword ptr [edi+ebp*4+11E4h]
			CPatch::PatchUINT32(0x44ECDF + 3, CPathFind::m_dwNumPedNodes.GetOffset());	// mov     eax, [ebp+esi*4+11E4h]
			CPatch::PatchUINT32(0x44ECF7 + 3, CPathFind::m_dwNumPedNodes.GetOffset());	// idiv    dword ptr [ebp+esi*4+11E4h]
			CPatch::PatchUINT32(0x156F780 + 3, CPathFind::m_dwNumPedNodes.GetOffset());	// lea     ecx, [esi+edi*4+11E4h]

			// array index iTotalNumberOfPathFile
			CPatch::PatchUINT32(0x4526D4 + 3, CPathFind::m_dwNumPedNodes.GetOffset() + iTotalNumberOfPathFiles * sizeof(uint32_t));	// mov     [edi+eax*4+12E4h], ecx	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
		}
		#endif

		// Offset_CPathFind__NumVehicleNodes
		#if TRUE
		{
			// array index 0
			CPatch::PatchUINT32(0x44E623 + 2, CPathFind::m_dwNumVehicleNodes.GetOffset());	// lea     esi, [ecx+10C4h]
			CPatch::PatchUINT32(0x44E696 + 2, CPathFind::m_dwNumVehicleNodes.GetOffset());	// lea     esi, [ecx+10C4h]
			CPatch::PatchUINT32(0x44E83E + 3, CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     ecx, [edi+ebp*4+10C4h]
			CPatch::PatchUINT32(0x44ECFE + 3, CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     ecx, [ebp+esi*4+10C4h]
			CPatch::PatchUINT32(0x44F2F1 + 3, CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     eax, [esi+ebx*4+10C4h]
			CPatch::PatchUINT32(0x44F2FE + 3, CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     edx, [esi+ebx*4+10C4h]
			CPatch::PatchUINT32(0x44F8D3 + 2, CPathFind::m_dwNumVehicleNodes.GetOffset());	// lea     esi, [ecx+10C4h]
			CPatch::PatchUINT32(0x44FA3F + 2, CPathFind::m_dwNumVehicleNodes.GetOffset());	// lea     esi, [ebx+10C4h]
			CPatch::PatchUINT32(0x44FB68 + 2, CPathFind::m_dwNumVehicleNodes.GetOffset());	// lea     ebp, [ecx+10C4h]
			CPatch::PatchUINT32(0x44FD4D + 2, CPathFind::m_dwNumVehicleNodes.GetOffset());	// lea     edi, [ecx+10C4h]
			CPatch::PatchUINT32(0x44FEFB + 2, CPathFind::m_dwNumVehicleNodes.GetOffset());	// lea     esi, [edi+10C4h]
			CPatch::PatchUINT32(0x452841 + 3, CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     eax, [edi+edx*4+10C4h]
			CPatch::PatchUINT32(0x45284C + 3, CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     ecx, [edi+edx*4+10C4h]
			CPatch::PatchUINT32(0x1565423 + 2, CPathFind::m_dwNumVehicleNodes.GetOffset());	// add     ecx, 10C4h
			CPatch::PatchUINT32(0x156F770 + 3, CPathFind::m_dwNumVehicleNodes.GetOffset());	// lea     eax, [esi+edi*4+10C4h]

			// array index iTotalNumberOfPathFile
			CPatch::PatchUINT32(0x4526C2 + 3, CPathFind::m_dwNumVehicleNodes.GetOffset() + iTotalNumberOfPathFiles * sizeof(uint32_t));	// mov     [edi+edx*4+11C4h], esi	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
		}
		#endif

		// Offset_CPathFind__NumNodes
		#if TRUE
		{
			// array index 0
			CPatch::PatchUINT32(0x44F2EA + 3, CPathFind::m_dwNumNodes.GetOffset());	// mov     ecx, [esi+ebx*4+0FA4h]
			CPatch::PatchUINT32(0x452853 + 3, CPathFind::m_dwNumNodes.GetOffset());	// mov     eax, [edi+edx*4+0FA4h]
			CPatch::PatchUINT32(0x156F75E + 3, CPathFind::m_dwNumNodes.GetOffset());	// lea     eax, [esi+edi*4+0FA4h]
			CPatch::PatchUINT32(0x156F7AE + 3, CPathFind::m_dwNumNodes.GetOffset());	// mov     eax, [esi+edi*4+0FA4h]
			CPatch::PatchUINT32(0x156F7C7 + 3, CPathFind::m_dwNumNodes.GetOffset());	// mov     edx, [esi+edi*4+0FA4h]
			CPatch::PatchUINT32(0x156F966 + 3, CPathFind::m_dwNumNodes.GetOffset());	// mov     eax, [esi+edi*4+0FA4h]
			CPatch::PatchUINT32(0x156F998 + 3, CPathFind::m_dwNumNodes.GetOffset());	// mov     eax, [esi+edi*4+0FA4h]

			// array index iTotalNumberOfPathFile
			CPatch::PatchUINT32(0x4526B3 + 3, CPathFind::m_dwNumNodes.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     [edi+eax*4+10A4h], ecx	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
		}
		#endif

		// Offset_CPathFind__field_EC4
		{
			// I found no references to this field. May be unused.
		}

		// Offset_CPathFind__pNaviLinks
		#if TRUE
		{
			// array index 0
			CPatch::PatchUINT32(0x450376 + 3, CPathFind::m_pNaviLinks.extended.GetOffset());	// mov     edx, [ecx+edx*4+0DA4h]	; _ZN9CPathFind34FindNodeOrientationForCarPlacementE12CNodeAddress
			CPatch::PatchUINT32(0x451816 + 3, CPathFind::m_pNaviLinks.extended.GetOffset());	// mov     ecx, [esi+edi*4+0DA4h]	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
			CPatch::PatchUINT32(0x1563FF7 + 3, CPathFind::m_pNaviLinks.extended.GetOffset());	// mov     eax, [esi+edi*4+0DA4h]	; _ZN9CPathFind26UnLoadPathFindData_HOODLUMEi
			CPatch::PatchUINT32(0x1564048 + 3, CPathFind::m_pNaviLinks.extended.GetOffset());	// mov     [esi+edi*4+0DA4h], ebx	; _ZN9CPathFind26UnLoadPathFindData_HOODLUMEi
			CPatch::PatchUINT32(0x156F8BA + 3, CPathFind::m_pNaviLinks.extended.GetOffset());	// mov     [esi+edi*4+CPathFind.pNaviLinks], eax	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami
			CPatch::PatchUINT32(0x156F901 + 3, CPathFind::m_pNaviLinks.extended.GetOffset());	// mov     ecx, [esi+edi*4+0DA4h]	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami
			CPatch::PatchUINT32(0x156F951 + 3, CPathFind::m_pNaviLinks.extended.GetOffset());	// mov     [esi+edi*4+0DA4h], ecx	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami

			// array index iTotalNumberOfPathFile
			// there are none
		}
		#endif

		// Offset_CPathFind__pPathIntersections
		#if TRUE
		{
			// array index 0
			CPatch::PatchUINT32(0x44E904 + 3, CPathFind::m_pPathIntersections.GetOffset());	// mov     edx, [edi+ebp*4+0C84h]	; _ZN9CPathFind24GeneratePedCreationCoorsEffffffP7CVectorP12CNodeAddressS3_PfbP7CMatrix
			CPatch::PatchUINT32(0x1560CD4 + 3, CPathFind::m_pPathIntersections.GetOffset());	// mov     edx, [ecx+eax*4+0C84h]	; _ZN9CPathFind36AddDynamicLinkBetween2Nodes_For1NodeE20CNodeAddress_HOODLUMS0_
			CPatch::PatchUINT32(0x1560D7C + 3, CPathFind::m_pPathIntersections.GetOffset());	// mov     esi, [ecx+eax*4+0C84h]	; _ZN9CPathFind36AddDynamicLinkBetween2Nodes_For1NodeE20CNodeAddress_HOODLUMS0_
			CPatch::PatchUINT32(0x156401F + 3, CPathFind::m_pPathIntersections.GetOffset());	// mov     eax, [esi+edi*4+0C84h]	; _ZN9CPathFind26UnLoadPathFindData_HOODLUMEi
			CPatch::PatchUINT32(0x1564056 + 3, CPathFind::m_pPathIntersections.GetOffset());	// mov     [esi+edi*4+0C84h], ebx	; _ZN9CPathFind26UnLoadPathFindData_HOODLUMEi
			CPatch::PatchUINT32(0x1565B72 + 3, CPathFind::m_pPathIntersections.GetOffset());	// add     esi, [ecx+eax*4+0C84h]	; _ZN9CPathFind23TestCrossesRoad_HOODLUME12CNodeAddressS0_
			CPatch::PatchUINT32(0x156A482 + 3, CPathFind::m_pPathIntersections.GetOffset());	// add     esi, [ecx+eax*4+0C84h]	; _ZN9CPathFind30TestForPedTrafficLight_HOODLUME12CNodeAddressS0_
			CPatch::PatchUINT32(0x156F8E5 + 3, CPathFind::m_pPathIntersections.GetOffset());	// mov     [esi+edi*4+CPathFind.pPathIntersections], eax	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami
			CPatch::PatchUINT32(0x156F92D + 3, CPathFind::m_pPathIntersections.GetOffset());	// mov     edx, [esi+edi*4+0C84h]	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami
			CPatch::PatchUINT32(0x156F95F + 3, CPathFind::m_pPathIntersections.GetOffset());	// mov     [esi+edi*4+0C84h], ecx	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami


			// array index iTotalNumberOfPathFiles
			CPatch::PatchUINT32(0x4525C4 + 3, CPathFind::m_pPathIntersections.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     [edi+ecx*4+0D84h], eax	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
		}
		#endif

		// Offset_CPathFind__pLinkLengths
		#if TRUE
		{
			// array index 0
			CPatch::PatchUINT32(0x4518A4 + 3, CPathFind::m_pLinkLengths.GetOffset());	// mov     edx, [esi+edi*4+0B64h]	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
			CPatch::PatchUINT32(0x451A5F + 3, CPathFind::m_pLinkLengths.GetOffset());	// mov     edi, [esi+edi*4+0B64h]	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
			CPatch::PatchUINT32(0x1560CBC + 3, CPathFind::m_pLinkLengths.GetOffset());	// mov     edx, [ecx+eax*4+0B64h]	; _ZN9CPathFind36AddDynamicLinkBetween2Nodes_For1NodeE20CNodeAddress_HOODLUMS0_
			CPatch::PatchUINT32(0x1560D66 + 3, CPathFind::m_pLinkLengths.GetOffset());	// mov     esi, [ecx+eax*4+0B64h]	; _ZN9CPathFind36AddDynamicLinkBetween2Nodes_For1NodeE20CNodeAddress_HOODLUMS0_
			CPatch::PatchUINT32(0x156400B + 3, CPathFind::m_pLinkLengths.GetOffset());	// mov     eax, [esi+edi*4+0B64h]	; _ZN9CPathFind26UnLoadPathFindData_HOODLUMEi
			CPatch::PatchUINT32(0x156404F + 3, CPathFind::m_pLinkLengths.GetOffset());	// mov     [esi+edi*4+0B64h], ebx	; _ZN9CPathFind26UnLoadPathFindData_HOODLUMEi
			CPatch::PatchUINT32(0x156F8D2 + 3, CPathFind::m_pLinkLengths.GetOffset());	// mov     [esi+edi*4+0B64h], eax	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami
			CPatch::PatchUINT32(0x156F915 + 3, CPathFind::m_pLinkLengths.GetOffset());	// mov     eax, [esi+edi*4+0B64h]	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami
			CPatch::PatchUINT32(0x156F958 + 3, CPathFind::m_pLinkLengths.GetOffset());	// mov     [esi+edi*4+0B64h], ecx	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami

			// array index iTotalNumberOfPathFiles
			CPatch::PatchUINT32(0x4525B2 + 3, CPathFind::m_pLinkLengths.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     [edi+edx*4+0C64h], eax	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
		}
		#endif

		// Offset_CPathFind__m_pNodeLinks
		#if TRUE
		{
			// array index 0
			CPatch::PatchUINT32(0x44E722 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     eax, [ecx+ebx*4+0A44h]	; _ZN9CPathFind20CountFloodFillGroupsEh
			CPatch::PatchUINT32(0x44E917 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     edx, [edi+ebp*4+0A44h]	; _ZN9CPathFind24GeneratePedCreationCoorsEffffffP7CVectorP12CNodeAddressS3_PfbP7CMatrix
			CPatch::PatchUINT32(0x44EDC4 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     eax, [ebp+esi*4+0A44h]	; _ZN9CPathFind33GeneratePedCreationCoors_InteriorEffP7CVectorP12CNodeAddressS3_Pf
			CPatch::PatchUINT32(0x44F1B9 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     edx, [ebx+eax*4+0A44h]	; _ZN9CPathFind28CalcDistToAnyConnectingLinksEP9CPathNode7CVector
			CPatch::PatchUINT32(0x4503D7 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     edx, [ecx+edx*4+0A44h]	; _ZN9CPathFind34FindNodeOrientationForCarPlacementE12CNodeAddress
			CPatch::PatchUINT32(0x450659 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     edx, [edi+edx*4+0A44h]	; _ZN9CPathFind22FindNodeCoorsForScriptE12CNodeAddressPb
			CPatch::PatchUINT32(0x4517DF + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     eax, [esi+edi*4+0A44h]	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
			CPatch::PatchUINT32(0x451A38 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     ebx, [esi+edi*4+0A44h]	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
			CPatch::PatchUINT32(0x451D38 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     eax, [ebx+eax*4+0A44h]	; _ZN9CPathFind21FindNextNodeWanderingEh7CVectorP12CNodeAddressS2_hPh
			CPatch::PatchUINT32(0x451FA3 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     ecx, [ebx+ecx*4+0A44h]	; _ZN9CPathFind21FindNextNodeWanderingEh7CVectorP12CNodeAddressS2_hPh
			CPatch::PatchUINT32(0x1560C57 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     esi, [ecx+eax*4+0A44h]	; _ZN9CPathFind36AddDynamicLinkBetween2Nodes_For1NodeE20CNodeAddress_HOODLUMS0_
			CPatch::PatchUINT32(0x1560CA6 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     edx, [ecx+eax*4+0A44h]	; _ZN9CPathFind36AddDynamicLinkBetween2Nodes_For1NodeE20CNodeAddress_HOODLUMS0_
			CPatch::PatchUINT32(0x1560D4E + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     esi, [ecx+eax*4+0A44h]	; _ZN9CPathFind36AddDynamicLinkBetween2Nodes_For1NodeE20CNodeAddress_HOODLUMS0_
			CPatch::PatchUINT32(0x1563FE3 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     eax, [esi+edi*4+0A44h]	; _ZN9CPathFind26UnLoadPathFindData_HOODLUMEi
			CPatch::PatchUINT32(0x1564041 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     [esi+edi*4+0A44h], ebx	; _ZN9CPathFind26UnLoadPathFindData_HOODLUMEi
			CPatch::PatchUINT32(0x15643FF + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     [ebx+edx*4+0A44h], ebp	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x1564718 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     eax, [ecx+eax*4+0A44h]	; _ZN9CPathFind34SwitchOffNodeAndNeighbours_HOODLUMEP9CPathNodePS1_S2_bb
			CPatch::PatchUINT32(0x1565B30 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     esi, [ecx+esi*4+0A44h]	; _ZN9CPathFind23TestCrossesRoad_HOODLUME12CNodeAddressS0_
			CPatch::PatchUINT32(0x156A440 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     esi, [ecx+esi*4+0A44h]	; _ZN9CPathFind30TestForPedTrafficLight_HOODLUME12CNodeAddressS0_
			CPatch::PatchUINT32(0x156A9AC + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     eax, [ecx+eax*4+0A44h]	; _ZN9CPathFind38CountNeighboursToBeSwitchedOff_HOODLUMEP9CPathNode
			CPatch::PatchUINT32(0x156F850 + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     [esi+edi*4+CPathFind.m_pNodeLinks], eax	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami
			CPatch::PatchUINT32(0x156F8DE + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     edx, [esi+edi*4+CPathFind.m_pNodeLinks]	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami
			CPatch::PatchUINT32(0x156F94A + 3, CPathFind::m_pNodeLinks.GetOffset());	// mov     [esi+edi*4+0A44h], ecx	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami

			// array index 1
			CPatch::PatchUINT32(0x15643F8 + 3, CPathFind::m_pNodeLinks.GetOffset() + 1 * sizeof(void*));	// mov     [ebx+edx*4+8844h], ebp	; _ZN9CPathFind22RemoveInterior_HOODLUMEj

			// array index iTotalNumberOfPathFiles
			CPatch::PatchUINT32(0x45259E + 3, CPathFind::m_pNodeLinks.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     [edi+ecx*4+0B44h], eax	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x452696 + 3, CPathFind::m_pNodeLinks.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     edx, [edi+edx*4+0B44h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
		}
		#endif

		// Offset_CPathFind__pNaviNodes
		#if TRUE
		{
			// array index 0
			CPatch::PatchUINT32(0x44F103 + 3, CPathFind::m_pNaviNodes.extended.GetOffset());	// mov     edx, [ecx+edx*4+924h]
			CPatch::PatchUINT32(0x450393 + 3, CPathFind::m_pNaviNodes.extended.GetOffset());	// mov     edx, [ecx+edx*4+924h]
			CPatch::PatchUINT32(0x451839 + 3, CPathFind::m_pNaviNodes.extended.GetOffset());	// add     ecx, [esi+edx*4+924h]
			CPatch::PatchUINT32(0x1560DD6 + 2, CPathFind::m_pNaviNodes.extended.GetOffset());	// lea     eax, [ecx+924h]
			CPatch::PatchUINT32(0x1563FCF + 3, CPathFind::m_pNaviNodes.extended.GetOffset());	// mov     eax, [esi+edi*4+924h]
			CPatch::PatchUINT32(0x156403A + 3, CPathFind::m_pNaviNodes.extended.GetOffset());	// mov     [esi+edi*4+924h], ebx
			CPatch::PatchUINT32(0x156F819 + 3, CPathFind::m_pNaviNodes.extended.GetOffset());	// mov     [esi+edi*4+924h], eax
			CPatch::PatchUINT32(0x156F82A + 3, CPathFind::m_pNaviNodes.extended.GetOffset());	// mov     dword ptr [esi+edi*4+924h], 0

			// array index iTotalNumberOfPathFiles
			// not found.
		}
		#endif

		// Offset_CPathFind__m_pPathNodes
		#if TRUE
		{
			// array index 0
			CPatch::PatchUINT32(0x420AA6 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     esi, [ecx+eax*4+804h]
			CPatch::PatchUINT32(0x420ACF + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// add     eax, [ecx+edx*4+804h]
			CPatch::PatchUINT32(0x44DA41 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edx, [ecx+eax*4+804h]
			CPatch::PatchUINT32(0x44DA61 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [ecx+eax*4+804h]
			CPatch::PatchUINT32(0x44DDCB + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// lea     eax, [ebp+eax*4+804h]
			CPatch::PatchUINT32(0x44E50C + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edi, [ecx+esi*4+804h]
			CPatch::PatchUINT32(0x44E521 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edi, [ecx+esi*4+804h]
			CPatch::PatchUINT32(0x44E541 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edi, [ecx+eax*4+804h]
			CPatch::PatchUINT32(0x44E559 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ebp, [ecx+edx*4+804h]
			CPatch::PatchUINT32(0x44E73D + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// add     eax, [ecx+ebx*4+804h]
			CPatch::PatchUINT32(0x44E810 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [edi+ebp*4+804h]
			CPatch::PatchUINT32(0x44E845 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [edi+ebp*4+804h]
			CPatch::PatchUINT32(0x44E934 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [edi+eax*4+804h]
			CPatch::PatchUINT32(0x44ECD0 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [ebp+esi*4+804h]
			CPatch::PatchUINT32(0x44ED05 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [ebp+esi*4+804h]
			CPatch::PatchUINT32(0x44EDE1 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [ebp+edx*4+804h]
			CPatch::PatchUINT32(0x44EFCD + 2, CPathFind::m_pPathNodes.extended.GetOffset());	// lea     ebp, [ecx+804h]
			CPatch::PatchUINT32(0x44F08F + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edx, [ecx+eax*4+804h]
			CPatch::PatchUINT32(0x44F0DD + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// cmp     dword ptr [ecx+edx*4+804h], 0
			CPatch::PatchUINT32(0x44F1CC + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// lea     ecx, [ebx+eax*4+804h]
			CPatch::PatchUINT32(0x44F2CD + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [esi+ebx*4+804h]
			CPatch::PatchUINT32(0x44F330 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ecx, [esi+ebx*4+804h]
			CPatch::PatchUINT32(0x44F9BE + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ecx, [eax+ecx*4+804h]
			CPatch::PatchUINT32(0x44FB30 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ecx, [ebx+ecx*4+804h]
			CPatch::PatchUINT32(0x450059 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edx, [edx+eax*4+804h]
			CPatch::PatchUINT32(0x4501C5 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ebx, [edi+ecx*4+804h]
			CPatch::PatchUINT32(0x4501D1 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     esi, [edi+ecx*4+804h]
			CPatch::PatchUINT32(0x450328 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [ecx+edx*4+804h]
			CPatch::PatchUINT32(0x450389 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// cmp     dword ptr [ecx+edx*4+804h], 0
			CPatch::PatchUINT32(0x4503EA + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ecx, [ecx+eax*4+804h]
			CPatch::PatchUINT32(0x4505FC + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// cmp     [edi+edx*4+804h], ecx
			CPatch::PatchUINT32(0x450618 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     esi, [edi+edx*4+804h]
			CPatch::PatchUINT32(0x45066A + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [edi+eax*4+804h]
			CPatch::PatchUINT32(0x4507A8 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// lea     edx, [ecx+eax*4+804h]
			CPatch::PatchUINT32(0x4507BA + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// lea     eax, [ecx+eax*4+804h]
			CPatch::PatchUINT32(0x4509B6 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [ecx+eax*4+804h]
			CPatch::PatchUINT32(0x450CE2 + 2, CPathFind::m_pPathNodes.extended.GetOffset());	// add     ebx, 804h
			CPatch::PatchUINT32(0x450DE9 + 2, CPathFind::m_pPathNodes.extended.GetOffset());	// lea     edi, [ecx+804h]
			CPatch::PatchUINT32(0x451402 + 2, CPathFind::m_pPathNodes.extended.GetOffset());	// add     ecx, 804h
			CPatch::PatchUINT32(0x4515FD + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edx, [esi+ecx*4+804h]
			CPatch::PatchUINT32(0x451668 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edx, [esi+ecx*4+804h]
			CPatch::PatchUINT32(0x451707 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ebx, [esi+edi*4+804h]
			CPatch::PatchUINT32(0x45170E + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edi, [esi+edx*4+804h]
			CPatch::PatchUINT32(0x4517EC + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ecx, [esi+ecx*4+804h]
			CPatch::PatchUINT32(0x451826 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// cmp     dword ptr [esi+edx*4+804h], 0
			CPatch::PatchUINT32(0x451A4C + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ebx, [esi+eax*4+804h]
			CPatch::PatchUINT32(0x451AD8 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ecx, [esi+ecx*4+804h]
			CPatch::PatchUINT32(0x451B48 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ecx, [esi+ecx*4+804h]
			CPatch::PatchUINT32(0x451BA0 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ecx, [ebx+eax*4+804h]
			CPatch::PatchUINT32(0x451BDB + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// add     ecx, [ebx+edx*4+804h]
			CPatch::PatchUINT32(0x451C1A + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edx, [ebx+eax*4+804h]
			CPatch::PatchUINT32(0x451CC3 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ecx, [ebx+eax*4+804h]
			CPatch::PatchUINT32(0x451CCC + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// lea     eax, [ebx+eax*4+804h]
			CPatch::PatchUINT32(0x451D47 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     esi, [ebx+eax*4+804h]
			CPatch::PatchUINT32(0x451F7A + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ecx, [ebx+ecx*4+804h]
			CPatch::PatchUINT32(0x451FB5 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ebp, [ebx+edi*4+804h]
			CPatch::PatchUINT32(0x4522B8 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [edi+eax*4+804h]
			CPatch::PatchUINT32(0x45282A + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [edi+edx*4+804h]
			CPatch::PatchUINT32(0x452880 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     esi, [edi+edx*4+804h]
			CPatch::PatchUINT32(0x1560C32 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     esi, [ecx+eax*4+804h]
			CPatch::PatchUINT32(0x1562754 + 2, CPathFind::m_pPathNodes.extended.GetOffset());	// lea     esi, [ecx+804h]
			CPatch::PatchUINT32(0x1563FB9 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [esi+edi*4+804h]
			CPatch::PatchUINT32(0x1564033 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     [esi+edi*4+804h], ebx
			CPatch::PatchUINT32(0x156436B + 2, CPathFind::m_pPathNodes.extended.GetOffset());	// lea     esi, [edi+804h]
			CPatch::PatchUINT32(0x156472B + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [ecx+edx*4+804h]
			CPatch::PatchUINT32(0x1565AF8 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [ecx+esi*4+804h]
			CPatch::PatchUINT32(0x1565B09 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edi, [ecx+edx*4+804h]
			CPatch::PatchUINT32(0x1569F6C + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edx, [eax+edx*4+804h]
			CPatch::PatchUINT32(0x156A185 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [ecx+edx*4+804h]
			CPatch::PatchUINT32(0x156A1A5 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     esi, [ecx+eax*4+804h]
			CPatch::PatchUINT32(0x156A408 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [ecx+esi*4+804h]
			CPatch::PatchUINT32(0x156A419 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edi, [ecx+edx*4+804h]
			CPatch::PatchUINT32(0x156A9C5 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     esi, [ecx+edx*4+804h]
			CPatch::PatchUINT32(0x156ED59 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edx, [esi+eax*4+804h]
			CPatch::PatchUINT32(0x156F7D4 + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     [esi+edi*4+804h], eax
			CPatch::PatchUINT32(0x156F7EF + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     [esi+edi*4+804h], eax
			CPatch::PatchUINT32(0x156F97A + 3, CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [esi+edi*4+804h]

			// array index iTotalNumberOfPathFiles
			CPatch::PatchUINT32(0x4522ED + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     [edi+edx*4+904h], eax	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x452323 + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     ebx, [edi+eax*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x452366 + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     edx, [edi+ecx*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x452381 + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     ecx, [edi+eax*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x452393 + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     eax, [edi+edx*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x4523A8 + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     eax, [edi+edx*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x4523C2 + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     edx, [edi+ecx*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x4523D5 + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     ecx, [edi+eax*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x4523E9 + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     eax, [edi+edx*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x452403 + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     edx, [edi+ecx*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x452416 + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     ecx, [edi+eax*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x45242A + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     eax, [edi+edx*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x452451 + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     eax, [edi+edx*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x45246B + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     edx, [edi+ecx*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x45247E + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     ecx, [edi+eax*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x452492 + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     eax, [edi+edx*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x4524AC + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     edx, [edi+ecx*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x4525F6 + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     ecx, [edi+edx*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x45260D + 3, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// mov     edx, [edi+ecx*4+904h]	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
			CPatch::PatchUINT32(0x156432B + 2, CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*));	// lea     ebp, [edi+904h]			; _ZN9CPathFind14RemoveInteriorEj
		}
		#endif

		// Offset_CPathFind__m_apNodesSearchLists
		{

		}
	}
	#endif

	// Patch CPathFind relative offsets
	#if TRUE
	{
		// 0x1000
		{
			CPatch::PatchUINT32(0x1564507 + 3, iTotalNumberOfPathFiles * sizeof(__int32) * CPathFind_field_1544_numberOfElementsPerPathFile);	// mov     dword ptr [ebx+edi*4+1000h], 0FFFFFFFFh	; _ZN9CPathFind14RemoveInteriorEj
			CPatch::PatchUINT32(0x156FA0B + 2, iTotalNumberOfPathFiles * sizeof(__int32) * CPathFind_field_1544_numberOfElementsPerPathFile);	// mov     [eax+1000h], edx	; _ZN9CPathFind24LoadPathFindData_HOODLUMEP8RwStreami
		}

		// -0x120
		{
			CPatch::PatchUINT32(0x44E63F + 2, CPathFind::m_dwNumNodes.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     ebp, [esi-120h]	; _ZN9CPathFind20CountFloodFillGroupsEh
			CPatch::PatchUINT32(0x44E6AF + 2, CPathFind::m_dwNumNodes.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     ebp, [esi-120h]	; _ZN9CPathFind20CountFloodFillGroupsEh
			CPatch::PatchUINT32(0x44F8FC + 2, CPathFind::m_dwNumNodes.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     ebp, [esi-120h]	; _ZN9CPathFind25FindNthNodeClosestToCoorsE7CVectorhfbbibbP12CNodeAddress
			CPatch::PatchUINT32(0x44FA69 + 2, CPathFind::m_dwNumNodes.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     ebp, [esi-120h]	; _ZN9CPathFind25RecordNodesClosestToCoorsE7CVectorhiP12CNodeAddressfbbbb
			CPatch::PatchUINT32(0x44FB9E + 2, CPathFind::m_dwNumNodes.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     eax, [ebp-120h]	; _ZN9CPathFind19RecordNodesInCircleERK7CVectorfhiP12CNodeAddressbbbbb
			CPatch::PatchUINT32(0x44FD7D + 2, CPathFind::m_dwNumNodes.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     esi, [edi-120h]	; _ZN9CPathFind37FindNodeClosestToCoorsFavourDirectionE7CVectorhff
			CPatch::PatchUINT32(0x44FF40 + 2, CPathFind::m_dwNumNodes.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     eax, [esi-120h]	; _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb
			CPatch::PatchUINT32(0x1560DE1 + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_pNaviNodes.extended.GetOffset());	// mov     [eax-288], edx	; _ZN9CPathFind12Init_HOODLUMEv
		}

		// 0x120
		{
			CPatch::PatchUINT32(0x1560DE9 + 2, CPathFind::m_pNodeLinks.GetOffset() - CPathFind::m_pNaviNodes.extended.GetOffset());	// mov     [eax+120h], edx	; _ZN9CPathFind12Init_HOODLUMEv
		}

		// 0x240
		{
			CPatch::PatchUINT32(0x44F078 + 2, CPathFind::m_pNodeLinks.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edi, [ebp+240h]	; _ZN9CPathFind15CalcRoadDensityEff
			CPatch::PatchUINT32(0x1560DEF + 2, CPathFind::m_pLinkLengths.GetOffset() - CPathFind::m_pNaviNodes.extended.GetOffset());	// mov     [eax+240h], edx	; _ZN9CPathFind12Init_HOODLUMEv
			CPatch::PatchUINT32(0x15643C3 + 2, CPathFind::m_pNodeLinks.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edx, [esi+240h]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x1564465 + 2, CPathFind::m_pNodeLinks.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edi, [esi+240h]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x1564475 + 2, CPathFind::m_pNodeLinks.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edi, [esi+240h]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x1564486 + 2, CPathFind::m_pNodeLinks.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edi, [esi+240h]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x1564497 + 2, CPathFind::m_pNodeLinks.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edi, [esi+240h]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x15644A8 + 2, CPathFind::m_pNodeLinks.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edi, [esi+240h]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x15644B9 + 2, CPathFind::m_pNodeLinks.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edi, [esi+240h]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x1564565 + 2, CPathFind::m_pNodeLinks.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     ecx, [ebp+240h]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x156457B + 2, CPathFind::m_pNodeLinks.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     [ebp+240h], ebx	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
		}

		// 0x360
		{
			CPatch::PatchUINT32(0x1560DF5 + 2, CPathFind::m_pPathIntersections.GetOffset() - CPathFind::m_pNaviNodes.extended.GetOffset());	// mov     [eax+360h], edx	; _ZN9CPathFind12Init_HOODLUMEv
			CPatch::PatchUINT32(0x1564574 + 2, CPathFind::m_pLinkLengths.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edx, [ebp+360h]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x156458D + 2, CPathFind::m_pLinkLengths.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     [ebp+360h], ebx	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
		}

		// 0x480
		{
			CPatch::PatchUINT32(0x1560DFB + 2, CPathFind::m_pNaviLinks.extended.GetOffset() - CPathFind::m_pNaviNodes.extended.GetOffset());	// mov     [eax+480h], edx	; _ZN9CPathFind12Init_HOODLUMEv
			CPatch::PatchUINT32(0x1564586 + 2, CPathFind::m_pPathIntersections.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     eax, [ebp+480h]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x156459B + 2, CPathFind::m_pPathIntersections.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     [ebp+480h], ebx	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
		}

		// 0x580
		{
			CPatch::PatchUINT32(0x1560E01 + 2, (CPathFind::m_pNaviLinks.extended.GetOffset() + iTotalNumberOfPathFiles * 4) - CPathFind::m_pNaviNodes.extended.GetOffset());	// mov     [eax+580h], edx	; _ZN9CPathFind4InitEv
		}

		// 0x5A0
		{
			CPatch::PatchUINT32(0x44F0BA + 2, CPathFind::m_pNaviLinks.extended.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edx, [ebp+5A0h]	; _ZN9CPathFind15CalcRoadDensityEff
		}

		// -0x680
		{
			CPatch::PatchUINT32(0x45003C + 2, CPathFind::m_pNodeLinks.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     esi, [esi-680h]	; _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb
		}

		// 0x7A0
		{
			CPatch::PatchUINT32(0x156437F + 2, CPathFind::m_dwNumNodes.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// cmp     ecx, [esi+(CPathFind.NumNodes-804h)]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x156451E + 2, CPathFind::m_dwNumNodes.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     edx, [esi+7A0h]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x15645A1 + 2, CPathFind::m_dwNumNodes.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     [ebp+7A0h], ebx	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
		}

		// 0x8c0
		{
			uint32_t offset =
				CPathFind::m_dwNumVehicleNodes.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset();

			CPatch::PatchUINT32(0x44EFEB + 2, offset);	// mov     eax, [ebp+8C0h]	; _ZN9CPathFind15CalcRoadDensityEff
			CPatch::PatchUINT32(0x450DF7 + 2, offset);	// mov     esi, [edi+8C0h]	; _ZN9CPathFind17IsWaterNodeNearbyE7CVectorf
			CPatch::PatchUINT32(0x45142A + 2, offset);	// mov     eax, [ecx+8C0h]	; _ZN9CPathFind21FindParkingNodeInAreaEffffff
			CPatch::PatchUINT32(0x1564379 + 2, offset);	// mov     ecx, [esi+(CPathFind.NumVehicleNodes-804h)]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x15645A7 + 2, offset);	// mov     [ebp+8C0h], ebx	; _ZN9CPathFind22RemoveInterior_HOODLUMEj				
		}

		// -0x8C0
		{
			CPatch::PatchUINT32(0x44E660 + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     ecx, [esi-8C0h]	; _ZN9CPathFind20CountFloodFillGroupsEh
			CPatch::PatchUINT32(0x44E6CA + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// add     eax, [esi-8C0h]	; _ZN9CPathFind20CountFloodFillGroupsEh
			CPatch::PatchUINT32(0x44F8E3 + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     eax, [esi-8C0h]	; _ZN9CPathFind25FindNthNodeClosestToCoorsE7CVectorhfbbibbP12CNodeAddress
			CPatch::PatchUINT32(0x44F920 + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     eax, [esi-8C0h]	; _ZN9CPathFind25FindNthNodeClosestToCoorsE7CVectorhfbbibbP12CNodeAddress
			CPatch::PatchUINT32(0x44FA50 + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     eax, [esi-8C0h]	; _ZN9CPathFind25RecordNodesClosestToCoorsE7CVectorhiP12CNodeAddressfbbbb
			CPatch::PatchUINT32(0x44FA90 + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     eax, [esi-8C0h]	; _ZN9CPathFind25RecordNodesClosestToCoorsE7CVectorhiP12CNodeAddressfbbbb
			CPatch::PatchUINT32(0x44FB80 + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     eax, [ebp-8C0h]	; _ZN9CPathFind19RecordNodesInCircleERK7CVectorfhiP12CNodeAddressbbbbb
			CPatch::PatchUINT32(0x44FBE0 + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     eax, [ebp-8C0h]	; _ZN9CPathFind19RecordNodesInCircleERK7CVectorfhiP12CNodeAddressbbbbb
			CPatch::PatchUINT32(0x44FD60 + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     edx, [edi-8C0h]	; _ZN9CPathFind37FindNodeClosestToCoorsFavourDirectionE7CVectorhff
			CPatch::PatchUINT32(0x44FF20 + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     edx, [esi-8C0h]	; _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb
			CPatch::PatchUINT32(0x1565430 + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     eax, [ecx-8C0h]	; _ZN9CPathFind38UnMarkAllRoadNodesAsDontWander_HOODLUMEv
			CPatch::PatchUINT32(0x1565444 + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_dwNumVehicleNodes.GetOffset());	// mov     eax, [ecx-8C0h]	; _ZN9CPathFind38UnMarkAllRoadNodesAsDontWander_HOODLUMEv
		}

		// -0x9E0
		{
			CPatch::PatchUINT32(0x44D9A0 + 2, CPathFind::m_pNaviNodes.extended.GetOffset() - CPathFind::m_dwNumCarPathLinks.GetOffset());	// mov     ecx, [edx-9E0h]	; _ZN9CPathFind20SetLinksBridgeLightsEffffb
		}

		// 0x9E0
		{
			CPatch::PatchUINT32(0x15645AD + 2, CPathFind::m_dwNumPedNodes.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     [ebp+9E0h], ebx	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
		}

		// -0B00
		{
			CPatch::PatchUINT32(0x44D980 + 2, CPathFind::m_pPathNodes.extended.GetOffset() - CPathFind::m_dwNumCarPathLinks.GetOffset());	// mov     eax, [edx-0B00h]	; _ZN9CPathFind20SetLinksBridgeLightsEffffb
		}

		// 0xB00
		{
			CPatch::PatchUINT32(0x15645B3 + 2, CPathFind::m_dwNumCarPathLinks.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     [ebp+0B00h], ebx	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
		}

		// 0xC20
		{
			CPatch::PatchUINT32(0x156439F + 2, CPathFind::m_dwNumAddresses.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// cmp     edx, [esi+0C20h]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x15645B9 + 2, CPathFind::m_dwNumAddresses.GetOffset() - CPathFind::m_pPathNodes.extended.GetOffset());	// mov     [ebp+0C20h], ebx	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
		}

		// 0x2C44
		{
			uint32_t offset =
				CPathFind::m_interiorAreaIDarray.GetOffset() - (CPathFind::m_pPathNodes.extended.GetOffset() + iTotalNumberOfPathFiles * 4);

			CPatch::PatchUINT32(0x156433F + 2, offset);	// mov     eax, [ebp+2C44h]	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
			CPatch::PatchUINT32(0x1564355 + 2, offset);	// mov     dword ptr [ebp+2C44h], 0FFFFFFFFh	; _ZN9CPathFind22RemoveInterior_HOODLUMEj
		}

		// 0x551 and 0x951
		{
			uint32_t offset = CPathFind::m_field_1544.GetOffset() / 4;

			CPatch::PatchUINT32(0x156435F + 4, offset);	// mov     [esp+30h+var_10], 551h	; _ZN9CPathFind14RemoveInteriorEj
			CPatch::PatchUINT32(0x156454D + 1, offset + iTotalNumberOfPathFiles * CPathFind_field_1544_numberOfElementsPerPathFile);
		}
	}
	#endif

	// Patch coordinates
	#if TRUE
	{
		// -3000.0
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();
		{
			CPatch::PatchPointer(0x44D835 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind18FindRegionForCoorsEff
			CPatch::PatchPointer(0x44D860 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind18FindRegionForCoorsEff
			CPatch::PatchPointer(0x44D894 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind19FindXRegionForCoorsEf
			CPatch::PatchPointer(0x44D8C4 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind19FindYRegionForCoorsEf
			CPatch::PatchPointer(0x44DB6C + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf
			CPatch::PatchPointer(0x44DBB2 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf
			CPatch::PatchPointer(0x44DBF9 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf
			CPatch::PatchPointer(0x44DC3F + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf
			CPatch::PatchPointer(0x44DD15 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind21AreNodesLoadedForAreaEffff
			CPatch::PatchPointer(0x44DD45 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind21AreNodesLoadedForAreaEffff
			CPatch::PatchPointer(0x44DD70 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind21AreNodesLoadedForAreaEffff
			CPatch::PatchPointer(0x44DD99 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind21AreNodesLoadedForAreaEffff
			CPatch::PatchPointer(0x44F46B + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb
			CPatch::PatchPointer(0x44F4B2 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb
			CPatch::PatchPointer(0x450BC8 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind15UpdateStreamingEb
			CPatch::PatchPointer(0x450BF5 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind15UpdateStreamingEb
			CPatch::PatchPointer(0x450C2A + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind15UpdateStreamingEb
			CPatch::PatchPointer(0x450C57 + 2, &fPathsMapMinCoord);	// fsub    ds:flt_859A90   ; -3000.0f	; _ZN9CPathFind15UpdateStreamingEb
		}
		CPatch::LeaveThisLevel();
		#endif

		// 3000.0
		#if TRUE
		CPatch::EnterNewLevelAndDisableDebugState();
		{
			CPatch::PatchPointer(0x44D8FA + 2, &fPathsMapMaxCoord);	// fsub    ds:flt_859A94   ; 3000.0	; _ZN9CPathFind19FindXCoorsForRegionEi
			CPatch::PatchPointer(0x44D91A + 2, &fPathsMapMaxCoord);	// fsub    ds:flt_859A94   ; 3000.0	; _ZN9CPathFind19FindYCoorsForRegionEi
			CPatch::PatchPointer(0x44D942 + 2, &fPathsMapMaxCoord);	// fsub    ds:flt_859A94   ; 3000.0	; _ZN9CPathFind22FindStartPointOfRegionEiiRfS0_
			CPatch::PatchPointer(0x44D954 + 2, &fPathsMapMaxCoord);	// fsub    ds:flt_859A94   ; 3000.0	; _ZN9CPathFind22FindStartPointOfRegionEiiRfS0_
			CPatch::PatchPointer(0x44F4ED + 2, &fPathsMapMaxCoord);	// fsub    ds:flt_859A94   ; 3000.0	; _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb
			CPatch::PatchPointer(0x44F505 + 2, &fPathsMapMaxCoord);	// fsub    ds:flt_859A94   ; 3000.0	; _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb
			CPatch::PatchPointer(0x44F52E + 2, &fPathsMapMaxCoord);	// fsub    ds:flt_859A94   ; 3000.0	; _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb
			CPatch::PatchPointer(0x44F55C + 2, &fPathsMapMaxCoord);	// fsub    ds:flt_859A94   ; 3000.0	; _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb
		}
		CPatch::LeaveThisLevel();
		#endif
	}
	#endif

	// Patch some values
	#if TRUE
	{
		CPatch::PatchUINT32(0x450A96 + 1, iTotalNumberOfPathFiles / 4);	// mov     ecx, 10h	; _ZN9CPathFind15UpdateStreamingEb
		CPatch::PatchUINT32(0x450AA2 + 1, iTotalNumberOfPathFiles / 4);	// mov     ecx, 10h	; _ZN9CPathFind15UpdateStreamingEb
		CPatch::PatchUINT32(0x156569D + 1, iTotalNumberOfPathFiles / 4);	// mov     ecx, 10h	; _ZN9CPathFind29LoadSceneForPathNodes_HOODLUME7CVector
	}
	#endif

	// Patch navi links mask (0x3FF)
	#if TRUE
	{
		CPatch::PatchUINT32(0x41B9FC + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_41B980
		CPatch::PatchUINT32(0x41BA15 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_41B980
		CPatch::PatchUINT32(0x41BA8E + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_41B980
		CPatch::PatchUINT32(0x41BAD8 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_41B980
		CPatch::PatchUINT32(0x42262B + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_422620
		CPatch::PatchUINT32(0x422784 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_422760
		CPatch::PatchUINT32(0x4243A1 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_424210
		CPatch::PatchUINT32(0x427430 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_426EF0
		CPatch::PatchUINT32(0x42745C + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_426EF0
		CPatch::PatchUINT32(0x4274C6 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_426EF0
		CPatch::PatchUINT32(0x4274E2 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_426EF0
		CPatch::PatchUINT32(0x427516 + 2, NaviLinksMask);	// and     edx, 3FFh	; sub_426EF0
		CPatch::PatchUINT32(0x42752F + 2, NaviLinksMask);	// and     edi, 3FFh	; sub_426EF0
		CPatch::PatchUINT32(0x427550 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_426EF0
		CPatch::PatchUINT32(0x42758E + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_426EF0
		CPatch::PatchUINT32(0x4275C5 + 2, NaviLinksMask);	// and     ebx, 3FFh	; sub_426EF0
		CPatch::PatchUINT32(0x4275EB + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_426EF0
		CPatch::PatchUINT32(0x4276F1 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_426EF0
		CPatch::PatchUINT32(0x427714 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_426EF0
		CPatch::PatchUINT32(0x42799B + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x4279CA + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427A0A + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427A35 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427A6F + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427AA6 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427B11 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427B36 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427B5D + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427B88 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427BA5 + 2, NaviLinksMask);	// and     edi, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427BE8 + 2, NaviLinksMask);	// and     ebx, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427C15 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427C2E + 2, NaviLinksMask);	// and     edx, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427CFC + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427D2C + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427D6B + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427D92 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427DD5 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427E25 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427E8E + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427EAF + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427ECF + 2, NaviLinksMask);	// and     edx, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x427F03 + 2, NaviLinksMask);	// and     edi, 3FFh	; sub_427740
		CPatch::PatchUINT32(0x4280F0 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_428040
		CPatch::PatchUINT32(0x4280F6 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_428040
		CPatch::PatchUINT32(0x4281AB + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_428040
		CPatch::PatchUINT32(0x428253 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_428040
		CPatch::PatchUINT32(0x42DF1F + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42DF52 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42DF6E + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42DF91 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42DFAD + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42E130 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42E291 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42E3EA + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42E6A4 + 2, NaviLinksMask);	// and     edx, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42E6DF + 2, NaviLinksMask);	// and     edx, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42E713 + 2, NaviLinksMask);	// and     edx, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42E744 + 2, NaviLinksMask);	// and     edx, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42E769 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42E9FA + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42EA26 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42EA69 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42EA90 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42EAC7 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42EB27 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42EB8C + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42EBAD + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42EBCD + 2, NaviLinksMask);	// and     edx, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x42EC01 + 2, NaviLinksMask);	// and     edi, 3FFh	; sub_42DE80
		CPatch::PatchUINT32(0x4305E6 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x430CB2 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x430D2C + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x430DB8 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x430EA6 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x430F04 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x431019 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x43103D + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x431072 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x4310A4 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x4310E5 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x431125 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x4311E2 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x43122A + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x431255 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x4312A7 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x431323 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x431344 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x431368 + 2, NaviLinksMask);	// and     edx, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x4313A1 + 2, NaviLinksMask);	// and     edi, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x431474 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x4314B2 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x4314DF + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x43152F + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_403AEE
		CPatch::PatchUINT32(0x4349B5 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x4349D9 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434A17 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434A4D + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434A72 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434AB6 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434B1C + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434B4C + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434B74 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434BAB + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434E9D + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434EE7 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434F26 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434F71 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434FAB + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x434FE6 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x43501C + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x435062 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x435085 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x435130 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x435163 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x435388 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x4353D5 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x4353F5 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_434900
		CPatch::PatchUINT32(0x4358FC + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x43591F + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x435945 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x435964 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x435E6F + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x435E8B + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x435EFC + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x435F18 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x435F9E + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x435FC9 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x435FFC + 2, NaviLinksMask);	// and     edi, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x436024 + 2, NaviLinksMask);	// and     edx, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x436071 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x43608D + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x43610E + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x43612E + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x43616D + 2, NaviLinksMask);	// and     edx, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x4361A1 + 2, NaviLinksMask);	// and     edi, 3FFh	; sub_435830
		CPatch::PatchUINT32(0x4365FB + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_436540
		CPatch::PatchUINT32(0x43662E + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_436540
		CPatch::PatchUINT32(0x43666C + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_436540
		CPatch::PatchUINT32(0x4366A2 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_436540
		CPatch::PatchUINT32(0x4366C7 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_436540
		CPatch::PatchUINT32(0x436719 + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_436540
		CPatch::PatchUINT32(0x436841 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_436540
		CPatch::PatchUINT32(0x436879 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_436540
		CPatch::PatchUINT32(0x4368BF + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_436540
		CPatch::PatchUINT32(0x4368E3 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_436540
		CPatch::PatchUINT32(0x44F10A + 1, NaviLinksMask);	// and     eax, 3FFh	; _ZN9CPathFind15CalcRoadDensityEff
		CPatch::PatchUINT32(0x45039A + 1, NaviLinksMask);	// and     eax, 3FFh	; _ZN9CPathFind34FindNodeOrientationForCarPlacementE12CNodeAddress
		CPatch::PatchUINT32(0x451830 + 2, NaviLinksMask);	// and     ecx, 3FFh	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
		CPatch::PatchUINT32(0x460F4E + 2, NaviLinksMask);	// and     ecx, 3FFh	; sub_460EE0
		CPatch::PatchUINT32(0x460F5D + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_460EE0
		CPatch::PatchUINT32(0x49D488 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_49D420
		CPatch::PatchUINT32(0x49D4A9 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_49D420
		CPatch::PatchUINT32(0x49D665 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_49D610
		CPatch::PatchUINT32(0x49D7DB + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_49D610
		CPatch::PatchUINT32(0x49D951 + 1, NaviLinksMask);	// and     eax, 3FFh	; sub_49D610
		CPatch::PatchUINT32(0x156EABC + 2, NaviLinksMask);	// and     edx, 3FFh	; sub_156E9C0
		CPatch::PatchUINT32(0x156EBD2 + 2, NaviLinksMask);	// and     edx, 3FFh	; sub_156E9C0
	}
	#endif

	// Patch navi links number of bits per vehicle node (10)
	#if TRUE
	{
		CPatch::PatchUINT8(0x41B9C4 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_41B980
		CPatch::PatchUINT8(0x41B9E4 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_41B980
		CPatch::PatchUINT8(0x41BA04 + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_41B980
		CPatch::PatchUINT8(0x41BA1D + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_41B980
		CPatch::PatchUINT8(0x41BA9D + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_41B980
		CPatch::PatchUINT8(0x41BAE1 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_41B980			
		CPatch::PatchUINT8(0x422634 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_422620
		CPatch::PatchUINT8(0x422767 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_422760
		CPatch::PatchUINT8(0x42438B + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_424210
		CPatch::PatchUINT8(0x4245C1 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_424210
		CPatch::PatchUINT8(0x427435 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_426EF0
		CPatch::PatchUINT8(0x427464 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_426EF0
		CPatch::PatchUINT8(0x4274CE + 2, NumberOfBitsPerVehicleNode);	// shr     ebp, 0Ah	; sub_426EF0
		CPatch::PatchUINT8(0x4274F5 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_426EF0
		CPatch::PatchUINT8(0x427508 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_426EF0
		CPatch::PatchUINT8(0x427535 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_426EF0
		CPatch::PatchUINT8(0x427558 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_426EF0
		CPatch::PatchUINT8(0x427593 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_426EF0
		CPatch::PatchUINT8(0x4275CE + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_426EF0
		CPatch::PatchUINT8(0x4275F9 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_426EF0
		CPatch::PatchUINT8(0x4276FA + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_426EF0
		CPatch::PatchUINT8(0x42771D + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_426EF0
		CPatch::PatchUINT8(0x4279A4 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x4279D0 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427A13 + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427A3E + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427A7E + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427AB5 + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427B19 + 2, NumberOfBitsPerVehicleNode);	// shr     ebp, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427B44 + 2, NumberOfBitsPerVehicleNode);	// shr     ebp, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427B6F + 2, NumberOfBitsPerVehicleNode);	// shr     ebp, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427B90 + 2, NumberOfBitsPerVehicleNode);	// shr     ebp, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427BAE + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427BD8 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427C1E + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427C37 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427D05 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427D35 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427D73 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427D9A + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427DE9 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427E11 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427E96 + 2, NumberOfBitsPerVehicleNode);	// shr     ebx, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427EBE + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427EEC + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x427F1A + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_427740
		CPatch::PatchUINT8(0x4280B7 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_428040
		CPatch::PatchUINT8(0x4280D0 + 2, NumberOfBitsPerVehicleNode);	// shr     esi, 0Ah	; sub_428040
		CPatch::PatchUINT8(0x4281B3 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_428040
		CPatch::PatchUINT8(0x42825B + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_428040
		CPatch::PatchUINT8(0x42DEE2 + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42DF27 + 2, NumberOfBitsPerVehicleNode);	// shr     ebx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42DF5A + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42DF76 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42DF99 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42DFB5 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42E0F2 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42E270 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42E3CD + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42E685 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42E6C0 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42E71C + 2, NumberOfBitsPerVehicleNode);	// shr     ebp, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42E74D + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42EA03 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42EA33 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42EA71 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42EA98 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42EAE7 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42EB15 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42EB94 + 2, NumberOfBitsPerVehicleNode);	// shr     ebx, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42EBBC + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42EBEA + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x42EC18 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_42DE80
		CPatch::PatchUINT8(0x4305EE + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x430B0D + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x430CBE + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x430D3F + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x430DC9 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x430EB1 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x430F15 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x431025 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x431045 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x43107A + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x4310BA + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x4310F8 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x431132 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x431201 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x431232 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x43126B + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x4312AC + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x43132F + 2, NumberOfBitsPerVehicleNode);	// shr     ebx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x431357 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x43137A + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x4313B8 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x431483 + 2, NumberOfBitsPerVehicleNode);	// shr     ebx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x4314C1 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x4314F6 + 2, NumberOfBitsPerVehicleNode);	// shr     ebx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x43153E + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_403AEE
		CPatch::PatchUINT8(0x434972 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x43498F + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x4349BD + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x4349E7 + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434A25 + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434A5B + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434A89 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434AC3 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434B24 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434B5C + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434B7C + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434BC3 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434E6D + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434E86 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434EA6 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434EEF + 2, NumberOfBitsPerVehicleNode);	// shr     ebp, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434F2E + 2, NumberOfBitsPerVehicleNode);	// shr     ebp, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434F83 + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434FB9 + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x434FF4 + 2, NumberOfBitsPerVehicleNode);	// shr     ebp, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x435027 + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x43506A + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x435093 + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x435138 + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x435153 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x435391 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x4353DD + 2, NumberOfBitsPerVehicleNode);	// shr     ebp, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x435413 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_434900
		CPatch::PatchUINT8(0x4358C9 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x4358E5 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x435904 + 2, NumberOfBitsPerVehicleNode);	// shr     ebx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x43592D + 2, NumberOfBitsPerVehicleNode);	// shr     ebx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x43594D + 2, NumberOfBitsPerVehicleNode);	// shr     ebx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x43597A + 2, NumberOfBitsPerVehicleNode);	// shr     ebx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x435E7A + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x435E98 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x435F07 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x435F25 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x435FA7 + 2, NumberOfBitsPerVehicleNode);	// shr     ebx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x435FD1 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x435FE9 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x43602A + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x43607C + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x43609A + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x436116 + 2, NumberOfBitsPerVehicleNode);	// shr     ebx, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x43613D + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x436185 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x436195 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_435830
		CPatch::PatchUINT8(0x436600 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_436540
		CPatch::PatchUINT8(0x43663C + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_436540
		CPatch::PatchUINT8(0x43667A + 2, NumberOfBitsPerVehicleNode);	// shr     edi, 0Ah	; sub_436540
		CPatch::PatchUINT8(0x4366B0 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_436540
		CPatch::PatchUINT8(0x4366DE + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_436540
		CPatch::PatchUINT8(0x436722 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_436540
		CPatch::PatchUINT8(0x436849 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_436540
		CPatch::PatchUINT8(0x436865 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_436540
		CPatch::PatchUINT8(0x4368C7 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_436540
		CPatch::PatchUINT8(0x4368F9 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_436540
		CPatch::PatchUINT8(0x44F0DA + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; _ZN9CPathFind15CalcRoadDensityEff
		CPatch::PatchUINT8(0x450386 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; _ZN9CPathFind34FindNodeOrientationForCarPlacementE12CNodeAddress
		CPatch::PatchUINT8(0x451823 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
		CPatch::PatchUINT8(0x460F14 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_460EE0
		CPatch::PatchUINT8(0x460F2E + 2, NumberOfBitsPerVehicleNode);	// shr     esi, 0Ah	; sub_460EE0
		CPatch::PatchUINT8(0x49D456 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_49D420
		CPatch::PatchUINT8(0x49D475 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_49D420
		CPatch::PatchUINT8(0x49D490 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_49D420
		CPatch::PatchUINT8(0x49D4B1 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_49D420
		CPatch::PatchUINT8(0x49D64E + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_49D610
		CPatch::PatchUINT8(0x49D66D + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_49D610
		CPatch::PatchUINT8(0x49D7C4 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_49D610
		CPatch::PatchUINT8(0x49D7E3 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_49D610
		CPatch::PatchUINT8(0x49D93A + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_49D610
		CPatch::PatchUINT8(0x49D959 + 2, NumberOfBitsPerVehicleNode);	// shr     edx, 0Ah	; sub_49D610
		CPatch::PatchUINT8(0x1567AE9 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_1567AD0
		CPatch::PatchUINT8(0x1567B06 + 2, NumberOfBitsPerVehicleNode);	// shr     ecx, 0Ah	; sub_1567AD0
		CPatch::PatchUINT8(0x156EAA7 + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_156E9C0
		CPatch::PatchUINT8(0x156EBBD + 2, NumberOfBitsPerVehicleNode);	// shr     eax, 0Ah	; sub_156E9C0
	}
	#endif

	// Patch size of CPathNode, 0x1C
	#if TRUE
	{
		CPatch::PatchUINT8(0x420ACC + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_420AC0
		CPatch::PatchUINT8(0x422100 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_422090
		CPatch::PatchUINT8(0x42211A + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_422090
		CPatch::PatchUINT8(0x422164 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_422090
		CPatch::PatchUINT8(0x4223DA + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_422370
		CPatch::PatchUINT8(0x422404 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_422370
		CPatch::PatchUINT8(0x42243A + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_422370
		CPatch::PatchUINT8(0x42248E + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_422370
		CPatch::PatchUINT8(0x424370 + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; sub_424210
		CPatch::PatchUINT8(0x424522 + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_424210
		CPatch::PatchUINT8(0x4245DB + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; sub_424210
		CPatch::PatchUINT8(0x424B6F + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_424210
		CPatch::PatchUINT8(0x424B88 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_424210
		CPatch::PatchUINT8(0x424C24 + 2, SizeOfCPathNode);	// imul    ebx, 1Ch	; sub_424210
		CPatch::PatchUINT8(0x424C49 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_424210
		CPatch::PatchUINT8(0x424C8D + 2, SizeOfCPathNode);	// imul    ebx, 1Ch	; sub_424210
		CPatch::PatchUINT8(0x426F7A + 2, SizeOfCPathNode);	// imul    ebp, 1Ch	; sub_426EF0
		CPatch::PatchUINT8(0x427246 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_426EF0
		CPatch::PatchUINT8(0x4278EA + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_427740
		CPatch::PatchUINT8(0x427949 + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_427740
		CPatch::PatchUINT8(0x427FA0 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_427740
		CPatch::PatchUINT8(0x42B49E + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_42B470
		CPatch::PatchUINT8(0x42B4F3 + 2, SizeOfCPathNode);	// imul    ebx, 1Ch	; sub_42B470
		CPatch::PatchUINT8(0x42B559 + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_42B470
		CPatch::PatchUINT8(0x42B581 + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_42B470
		CPatch::PatchUINT8(0x42B5A9 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_42B470
		CPatch::PatchUINT8(0x42B5D0 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_42B470
		CPatch::PatchUINT8(0x42B630 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_42B470
		CPatch::PatchUINT8(0x42B669 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_42B470
		CPatch::PatchUINT8(0x42B70E + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_42B470
		CPatch::PatchUINT8(0x42B73E + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_42B470
		CPatch::PatchUINT8(0x42B77E + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_42B470
		CPatch::PatchUINT8(0x42B880 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_42B7D7
		CPatch::PatchUINT8(0x42BA22 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_42B7D7
		CPatch::PatchUINT8(0x42BA42 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_42B7D7
		CPatch::PatchUINT8(0x42BF8F + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; sub_42BD20
		CPatch::PatchUINT8(0x42C1B4 + 2, SizeOfCPathNode);	// add     edi, 1Ch	; sub_42BD20
		CPatch::PatchUINT8(0x42C367 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_42C2B0
		CPatch::PatchUINT8(0x42DB01 + 2, SizeOfCPathNode);	// imul    ebp, 1Ch	; sub_42DAB0
		CPatch::PatchUINT8(0x42DB15 + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; sub_42DAB0
		CPatch::PatchUINT8(0x42DEF9 + 2, SizeOfCPathNode);	// imul    ebp, 1Ch	; sub_42DE80
		CPatch::PatchUINT8(0x42E2F0 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_42DE80
		CPatch::PatchUINT8(0x42E308 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_42DE80
		CPatch::PatchUINT8(0x42E4CE + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_42DE80
		CPatch::PatchUINT8(0x42E5BA + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_42DE80
		CPatch::PatchUINT8(0x42E7D6 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_42DE80
		CPatch::PatchUINT8(0x42E7F3 + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_42DE80
		CPatch::PatchUINT8(0x42E81C + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_42DE80
		CPatch::PatchUINT8(0x42E845 + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_42DE80
		CPatch::PatchUINT8(0x42E86E + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_42DE80
		CPatch::PatchUINT8(0x42E897 + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_42DE80
		CPatch::PatchUINT8(0x42E8D8 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_42DE80
		CPatch::PatchUINT8(0x42E90D + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_42DE80
		CPatch::PatchUINT8(0x42F64E + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_42F5A0
		CPatch::PatchUINT8(0x42F6AD + 2, SizeOfCPathNode);	// imul    ebx, 1Ch	; sub_42F5A0
		CPatch::PatchUINT8(0x42F7C2 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_42F5A0
		CPatch::PatchUINT8(0x43046F + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_403AEE
		CPatch::PatchUINT8(0x430477 + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; sub_403AEE
		CPatch::PatchUINT8(0x430C92 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_403AEE
		CPatch::PatchUINT8(0x430D05 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_403AEE
		CPatch::PatchUINT8(0x430D9D + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_403AEE
		CPatch::PatchUINT8(0x430E01 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_403AEE
		CPatch::PatchUINT8(0x430E7A + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_403AEE
		CPatch::PatchUINT8(0x430EE5 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_403AEE
		CPatch::PatchUINT8(0x430F57 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_403AEE
		CPatch::PatchUINT8(0x431198 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_403AEE
		CPatch::PatchUINT8(0x432B23 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_432B10
		CPatch::PatchUINT8(0x432B43 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_432B10
		CPatch::PatchUINT8(0x433C0A + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_433BA0
		CPatch::PatchUINT8(0x433C0D + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_433BA0
		CPatch::PatchUINT8(0x433EFB + 2, SizeOfCPathNode);	// imul    ebp, 1Ch	; sub_433EA0
		CPatch::PatchUINT8(0x433F0F + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_433EA0
		CPatch::PatchUINT8(0x435BEE + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_435830
		CPatch::PatchUINT8(0x435C59 + 2, SizeOfCPathNode);	// imul    ebx, 1Ch	; sub_435830
		CPatch::PatchUINT8(0x4454A4 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_4453D0
		CPatch::PatchUINT8(0x4458BA + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_4453D0
		CPatch::PatchUINT8(0x44DA7F + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; _ZN9CPathFind28TakeWidthIntoAccountForCoorsE12CNodeAddressS0_tPfS1_
		CPatch::PatchUINT8(0x44DA82 + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; _ZN9CPathFind28TakeWidthIntoAccountForCoorsE12CNodeAddressS0_tPfS1_
		CPatch::PatchUINT8(0x44E53B + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; _ZN9CPathFind18RemoveBadStartNodeE7CVectorP12CNodeAddressPs
		CPatch::PatchUINT8(0x44E551 + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; _ZN9CPathFind18RemoveBadStartNodeE7CVectorP12CNodeAddressPs
		CPatch::PatchUINT8(0x44E653 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind20CountFloodFillGroupsEh
		CPatch::PatchUINT8(0x44E66B + 2, SizeOfCPathNode);	// add     eax, 1Ch	; _ZN9CPathFind20CountFloodFillGroupsEh
		CPatch::PatchUINT8(0x44E6C7 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind20CountFloodFillGroupsEh
		CPatch::PatchUINT8(0x44E6D7 + 2, SizeOfCPathNode);	// add     eax, 1Ch	; _ZN9CPathFind20CountFloodFillGroupsEh
		CPatch::PatchUINT8(0x44E73A + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind20CountFloodFillGroupsEh
		CPatch::PatchUINT8(0x44E84E + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; _ZN9CPathFind24GeneratePedCreationCoorsEffffffP7CVectorP12CNodeAddressS3_PfbP7CMatrix
		CPatch::PatchUINT8(0x44E94A + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; _ZN9CPathFind24GeneratePedCreationCoorsEffffffP7CVectorP12CNodeAddressS3_PfbP7CMatrix
		CPatch::PatchUINT8(0x44ED0E + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; _ZN9CPathFind33GeneratePedCreationCoors_InteriorEffP7CVectorP12CNodeAddressS3_Pf
		CPatch::PatchUINT8(0x44EDF7 + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; _ZN9CPathFind33GeneratePedCreationCoors_InteriorEffP7CVectorP12CNodeAddressS3_Pf
		CPatch::PatchUINT8(0x44F0A9 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind15CalcRoadDensityEff
		CPatch::PatchUINT8(0x44F155 + 2, SizeOfCPathNode);	// add     esi, 1Ch	; _ZN9CPathFind15CalcRoadDensityEff
		CPatch::PatchUINT8(0x44F1E9 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind28CalcDistToAnyConnectingLinksEP9CPathNode7CVector
		CPatch::PatchUINT8(0x44F321 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind23FindNodeClosestInRegionEP12CNodeAddresst7CVectorhPfbbbb
		CPatch::PatchUINT8(0x44F439 + 2, SizeOfCPathNode);	// add     eax, 1Ch	; _ZN9CPathFind23FindNodeClosestInRegionEP12CNodeAddresst7CVectorhPfbbbb
		CPatch::PatchUINT8(0x44F910 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; _ZN9CPathFind25FindNthNodeClosestToCoorsE7CVectorhfbbibbP12CNodeAddress
		CPatch::PatchUINT8(0x44F92C + 2, SizeOfCPathNode);	// add     ecx, 1Ch	; _ZN9CPathFind25FindNthNodeClosestToCoorsE7CVectorhfbbibbP12CNodeAddress
		CPatch::PatchUINT8(0x44F9B4 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; _ZN9CPathFind25FindNthNodeClosestToCoorsE7CVectorhfbbibbP12CNodeAddress
		CPatch::PatchUINT8(0x44FA7D + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; _ZN9CPathFind25RecordNodesClosestToCoorsE7CVectorhiP12CNodeAddressfbbbb
		CPatch::PatchUINT8(0x44FA9F + 2, SizeOfCPathNode);	// add     ecx, 1Ch	; _ZN9CPathFind25RecordNodesClosestToCoorsE7CVectorhiP12CNodeAddressfbbbb
		CPatch::PatchUINT8(0x44FB2A + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; _ZN9CPathFind25RecordNodesClosestToCoorsE7CVectorhiP12CNodeAddressfbbbb
		CPatch::PatchUINT8(0x44FBDB + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; _ZN9CPathFind19RecordNodesInCircleERK7CVectorfhiP12CNodeAddressbbbbb
		CPatch::PatchUINT8(0x44FCB1 + 2, SizeOfCPathNode);	// add     edi, 1Ch	; _ZN9CPathFind19RecordNodesInCircleERK7CVectorfhiP12CNodeAddressbbbbb
		CPatch::PatchUINT8(0x44FD95 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind37FindNodeClosestToCoorsFavourDirectionE7CVectorhff
		CPatch::PatchUINT8(0x44FEA5 + 2, SizeOfCPathNode);	// add     edx, 1Ch	; _ZN9CPathFind37FindNodeClosestToCoorsFavourDirectionE7CVectorhff			
		CPatch::PatchUINT8(0x44FF77 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb
		CPatch::PatchUINT8(0x450071 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb
		CPatch::PatchUINT8(0x45015A + 2, SizeOfCPathNode);	// add     ebx, 1Ch	; _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb
		CPatch::PatchUINT8(0x4501BC + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb
		CPatch::PatchUINT8(0x4501C2 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb
		CPatch::PatchUINT8(0x45034B + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; _ZN9CPathFind34FindNodeOrientationForCarPlacementE12CNodeAddress
		CPatch::PatchUINT8(0x450406 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind34FindNodeOrientationForCarPlacementE12CNodeAddress
		CPatch::PatchUINT8(0x450622 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind22FindNodeCoorsForScriptE12CNodeAddressPb
		CPatch::PatchUINT8(0x45067A + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; _ZN9CPathFind22FindNodeCoorsForScriptE12CNodeAddressPb
		CPatch::PatchUINT8(0x4507E4 + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; _ZN9CPathFind22FindNodeCoorsForScriptE12CNodeAddressS0_PfPb
		CPatch::PatchUINT8(0x4507E7 + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; _ZN9CPathFind22FindNodeCoorsForScriptE12CNodeAddressS0_PfPb
		CPatch::PatchUINT8(0x4509CD + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; _ZN9CPathFind32TakeWidthIntoAccountForWanderingE12CNodeAddresst
		CPatch::PatchUINT8(0x450E5E + 2, SizeOfCPathNode);	// add     ecx, 1Ch	; _ZN9CPathFind17IsWaterNodeNearbyE7CVectorf
		CPatch::PatchUINT8(0x450FD6 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_450FB0
		CPatch::PatchUINT8(0x450FE1 + 2, SizeOfCPathNode);	// imul    ebx, 1Ch	; sub_450FB0
		CPatch::PatchUINT8(0x451533 + 2, SizeOfCPathNode);	// add     esi, 1Ch	; _ZN9CPathFind21FindParkingNodeInAreaEffffff
		CPatch::PatchUINT8(0x4516FB + 2, SizeOfCPathNode);	// imul    ebp, 1Ch	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
		CPatch::PatchUINT8(0x451701 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
		CPatch::PatchUINT8(0x451804 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
		CPatch::PatchUINT8(0x451A69 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
		CPatch::PatchUINT8(0x451AD2 + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
		CPatch::PatchUINT8(0x451B42 + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
		CPatch::PatchUINT8(0x451BCF + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; _ZN9CPathFind21FindNextNodeWanderingEh7CVectorP12CNodeAddressS2_hPh
		CPatch::PatchUINT8(0x451BF2 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; _ZN9CPathFind21FindNextNodeWanderingEh7CVectorP12CNodeAddressS2_hPh
		CPatch::PatchUINT8(0x451CE2 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; _ZN9CPathFind21FindNextNodeWanderingEh7CVectorP12CNodeAddressS2_hPh
		CPatch::PatchUINT8(0x451D5F + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind21FindNextNodeWanderingEh7CVectorP12CNodeAddressS2_hPh
		CPatch::PatchUINT8(0x451F88 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind21FindNextNodeWanderingEh7CVectorP12CNodeAddressS2_hPh
		CPatch::PatchUINT8(0x4522B5 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
		CPatch::PatchUINT8(0x4522D9 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
		CPatch::PatchUINT8(0x4524C1 + 2, SizeOfCPathNode);	// add     esi, 1Ch	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
		CPatch::PatchUINT8(0x452665 + 2, SizeOfCPathNode);	// add     eax, 1Ch	; _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress
		CPatch::PatchUINT8(0x45286A + 2, SizeOfCPathNode);	// imul    ebp, 1Ch	; _ZN9CPathFind32SwitchRoadsOffInAreaForOneRegionEffffffbbib
		CPatch::PatchUINT8(0x4529C9 + 2, SizeOfCPathNode);	// add     ebp, 1Ch	; _ZN9CPathFind32SwitchRoadsOffInAreaForOneRegionEffffffbbib
		CPatch::PatchUINT8(0x460EEC + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_460EE0
		CPatch::PatchUINT8(0x462ADF + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; sub_4629E0
		CPatch::PatchUINT8(0x462F0A + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; sub_4629E0
		CPatch::PatchUINT8(0x47FB86 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_47FA30
		CPatch::PatchUINT8(0x565DC6 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_565CB0
		CPatch::PatchUINT8(0x565FF2 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_565E80
		CPatch::PatchUINT8(0x595884 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_595590
		CPatch::PatchUINT8(0x595B14 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_595590
		CPatch::PatchUINT8(0x595D92 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_595590
		CPatch::PatchUINT8(0x595FFF + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_595590
		CPatch::PatchUINT8(0x5E121A + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_5E0820
		CPatch::PatchUINT8(0x5E1255 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_5E0820
		CPatch::PatchUINT8(0x613570 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_6133F0
		CPatch::PatchUINT8(0x614B38 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN11CPopulation15AddToPopulationEffff
		CPatch::PatchUINT8(0x614B50 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; _ZN11CPopulation15AddToPopulationEffff		
		CPatch::PatchUINT8(0x669A21 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_6699E0
		CPatch::PatchUINT8(0x669AAB + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_6699E0
		CPatch::PatchUINT8(0x669B34 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_6699E0
		CPatch::PatchUINT8(0x669BBE + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_6699E0
		CPatch::PatchUINT8(0x669C5F + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_6699E0
		CPatch::PatchUINT8(0x669DE5 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_669DA0
		CPatch::PatchUINT8(0x66A025 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_669FF0
		CPatch::PatchUINT8(0x66A09D + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_669FF0
		CPatch::PatchUINT8(0x66F0BA + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_66EFA0
		CPatch::PatchUINT8(0x66F18A + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_66EFA0
		CPatch::PatchUINT8(0x66F25D + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_66EFA0
		CPatch::PatchUINT8(0x66F302 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_66EFA0
		CPatch::PatchUINT8(0x6767D9 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; sub_676640
		CPatch::PatchUINT8(0x6F3C02 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN13CCarGenerator20DoInternalProcessingEv
		CPatch::PatchUINT8(0x1560C41 + 2, SizeOfCPathNode);	// imul    edi, 1Ch	; _ZN9CPathFind36AddDynamicLinkBetween2Nodes_For1NodeE20CNodeAddress_HOODLUMS0_
		CPatch::PatchUINT8(0x156438F + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; _ZN9CPathFind14RemoveInteriorEj
		CPatch::PatchUINT8(0x1564525 + 2, SizeOfCPathNode);	// add     ecx, 1Ch	; _ZN9CPathFind14RemoveInteriorEj
		CPatch::PatchUINT8(0x156473D + 2, SizeOfCPathNode);	// imul    esi, 1Ch	; _ZN9CPathFind26SwitchOffNodeAndNeighboursEP9CPathNodePS1_S2_bb
		CPatch::PatchUINT8(0x1565453 + 2, SizeOfCPathNode);	// add     esi, 1Ch	; _ZN9CPathFind38UnMarkAllRoadNodesAsDontWander_HOODLUMEv
		CPatch::PatchUINT8(0x1565B1B + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; _ZN9CPathFind15TestCrossesRoadE12CNodeAddressS0_
		CPatch::PatchUINT8(0x156971C + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind30These2NodesAreAdjacent_HOODLUME12CNodeAddressS0_
		CPatch::PatchUINT8(0x1569F7E + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind28ThisNodeWillLeadIntoADeadEndEP9CPathNodeS1_
		CPatch::PatchUINT8(0x156A1CC + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind28FindLinkBetweenNodes_HOODLUME12CNodeAddressS0_
		CPatch::PatchUINT8(0x156A42B + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; _ZN9CPathFind22TestForPedTrafficLightE12CNodeAddressS0_
		CPatch::PatchUINT8(0x156A9D7 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; _ZN9CPathFind38CountNeighboursToBeSwitchedOff_HOODLUMEP9CPathNode
		CPatch::PatchUINT8(0x156EA10 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_156E9C0
		CPatch::PatchUINT8(0x156EA53 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_156E9C0
		CPatch::PatchUINT8(0x156EA81 + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; sub_156E9C0
		CPatch::PatchUINT8(0x156EAE3 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_156E9C0
		CPatch::PatchUINT8(0x156EB25 + 2, SizeOfCPathNode);	// imul    ebx, 1Ch	; sub_156E9C0
		CPatch::PatchUINT8(0x156EB6E + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_156E9C0
		CPatch::PatchUINT8(0x156EBA7 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_156E9C0
		CPatch::PatchUINT8(0x156EBF5 + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; sub_156E9C0
		CPatch::PatchUINT8(0x156ED53 + 2, SizeOfCPathNode);	// imul    ecx, 1Ch	; _ZN9CPathFind32MarkRoadNodeAsDontWander_HOODLUMEfff
		CPatch::PatchUINT8(0x156F7BE + 2, SizeOfCPathNode);	// imul    eax, 1Ch	; _ZN9CPathFind16LoadPathFindDataEP8RwStreami
		CPatch::PatchUINT8(0x156F7CE + 2, SizeOfCPathNode);	// imul    edx, 1Ch	; _ZN9CPathFind16LoadPathFindDataEP8RwStreami
		CPatch::PatchUINT8(0x156F7E5 + 1, SizeOfCPathNode);	// push    1Ch	; _ZN9CPathFind16LoadPathFindDataEP8RwStreami
		CPatch::PatchUINT8(0x156F9A0 + 2, SizeOfCPathNode);	// add     ebp, 1Ch	; _ZN9CPathFind16LoadPathFindDataEP8RwStreami
		CPatch::PatchUINT8(0x156F9EE + 2, SizeOfCPathNode);	// add     ebx, 1Ch	; _ZN9CPathFind16LoadPathFindDataEP8RwStreami
	}
	#endif		

	// Patch size of CCarPathLink, 0xE
	#if TRUE
	{
		CPatch::PatchUINT8(0x41BA01 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_41B980
		CPatch::PatchUINT8(0x41BA1A + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_41B980
		CPatch::PatchUINT8(0x41BA9A + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_41B980
		CPatch::PatchUINT8(0x41BADE + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_41B980
		CPatch::PatchUINT8(0x422630 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_422620
		CPatch::PatchUINT8(0x422789 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_422760
		CPatch::PatchUINT8(0x4243A6 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_424210
		CPatch::PatchUINT8(0x427438 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_426EF0
		CPatch::PatchUINT8(0x427461 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_426EF0
		CPatch::PatchUINT8(0x4274CB + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_426EF0
		CPatch::PatchUINT8(0x4274EC + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_426EF0
		CPatch::PatchUINT8(0x427520 + 2, SizeOfCCarPathLink);	// imul    edx, 0Eh	; sub_426EF0
		CPatch::PatchUINT8(0x427538 + 2, SizeOfCCarPathLink);	// imul    edi, 0Eh	; sub_426EF0
		CPatch::PatchUINT8(0x427555 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_426EF0
		CPatch::PatchUINT8(0x427596 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_426EF0
		CPatch::PatchUINT8(0x4275CB + 2, SizeOfCCarPathLink);	// imul    ebx, 0Eh	; sub_426EF0
		CPatch::PatchUINT8(0x4275F0 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_426EF0
		CPatch::PatchUINT8(0x4276F7 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_426EF0
		CPatch::PatchUINT8(0x42771A + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_426EF0
		CPatch::PatchUINT8(0x4279A1 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x4279D3 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427A10 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427A3B + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427A7B + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427AB2 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427B16 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427B3B + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427B66 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427B8D + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427BAB + 2, SizeOfCCarPathLink);	// imul    edi, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427BEE + 2, SizeOfCCarPathLink);	// imul    ebx, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427C1B + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427C34 + 2, SizeOfCCarPathLink);	// imul    edx, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427D02 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427D32 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427D70 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427D97 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427DDA + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427E2E + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427E93 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427EB5 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427EDB + 2, SizeOfCCarPathLink);	// imul    edx, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x427F09 + 2, SizeOfCCarPathLink);	// imul    edi, 0Eh	; sub_427740
		CPatch::PatchUINT8(0x4280FB + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_428040
		CPatch::PatchUINT8(0x4280FE + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_428040
		CPatch::PatchUINT8(0x4281B0 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_428040
		CPatch::PatchUINT8(0x428258 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_428040
		CPatch::PatchUINT8(0x42DF24 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42DF57 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42DF73 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42DF96 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42DFB2 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42E136 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42E297 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42E3F0 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42E6AA + 2, SizeOfCCarPathLink);	// imul    edx, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42E6E5 + 2, SizeOfCCarPathLink);	// imul    edx, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42E719 + 2, SizeOfCCarPathLink);	// imul    edx, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42E74A + 2, SizeOfCCarPathLink);	// imul    edx, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42E772 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42EA00 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42EA30 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42EA6E + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42EA95 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42EACE + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42EB2C + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42EB91 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42EBB3 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42EBD9 + 2, SizeOfCCarPathLink);	// imul    edx, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x42EC07 + 2, SizeOfCCarPathLink);	// imul    edi, 0Eh	; sub_42DE80
		CPatch::PatchUINT8(0x4305EB + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x430CB8 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x430D32 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x430DBE + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x430EAC + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x430F0A + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x43101E + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x431042 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x431077 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x4310A9 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x4310EF + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x43112F + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x4311E7 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x43122F + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x43125A + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x4312AF + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x43132C + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x43134E + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x43136E + 2, SizeOfCCarPathLink);	// imul    edx, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x4313A7 + 2, SizeOfCCarPathLink);	// imul    edi, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x43147A + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x4314BE + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x4314E5 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x43153B + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_403AEE
		CPatch::PatchUINT8(0x4349BA + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x4349E4 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434A22 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434A58 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434A78 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434ABC + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434B21 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434B55 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434B79 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434BB0 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434EA3 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434EEC + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434F2B + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434F78 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434FB6 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x434FF1 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x43502A + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x435067 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x435090 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x435135 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x435168 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x43538E + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x4353DA + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x4353FF + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_434900
		CPatch::PatchUINT8(0x435901 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x43592A + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x43594A + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x43596D + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x435E74 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x435E91 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x435F01 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x435F1E + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x435FA4 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x435FCE + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x436002 + 2, SizeOfCCarPathLink);	// imul    edi, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x43602D + 2, SizeOfCCarPathLink);	// imul    edx, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x436076 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x436093 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x436113 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x436134 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x436173 + 2, SizeOfCCarPathLink);	// imul    edx, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x4361A7 + 2, SizeOfCCarPathLink);	// imul    edi, 0Eh	; sub_435830
		CPatch::PatchUINT8(0x436611 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_436540
		CPatch::PatchUINT8(0x436639 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_436540
		CPatch::PatchUINT8(0x436677 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_436540
		CPatch::PatchUINT8(0x4366AD + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_436540
		CPatch::PatchUINT8(0x4366CD + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_436540
		CPatch::PatchUINT8(0x43671F + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_436540
		CPatch::PatchUINT8(0x436846 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_436540
		CPatch::PatchUINT8(0x436882 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_436540
		CPatch::PatchUINT8(0x4368C4 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_436540
		CPatch::PatchUINT8(0x4368EE + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_436540
		CPatch::PatchUINT8(0x44DA0C + 2, SizeOfCCarPathLink);	// add     esi, 0Eh	; _ZN9CPathFind20SetLinksBridgeLightsEffffb
		CPatch::PatchUINT8(0x44F10F + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; _ZN9CPathFind15CalcRoadDensityEff
		CPatch::PatchUINT8(0x45039F + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; _ZN9CPathFind34FindNodeOrientationForCarPlacementE12CNodeAddress
		CPatch::PatchUINT8(0x451836 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb
		CPatch::PatchUINT8(0x460F54 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; sub_460EE0
		CPatch::PatchUINT8(0x460F62 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_460EE0
		CPatch::PatchUINT8(0x49D48D + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_49D420
		CPatch::PatchUINT8(0x49D4AE + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_49D420
		CPatch::PatchUINT8(0x49D66A + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_49D610
		CPatch::PatchUINT8(0x49D7E0 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_49D610
		CPatch::PatchUINT8(0x49D956 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; sub_49D610
		CPatch::PatchUINT8(0x156EAC2 + 2, SizeOfCCarPathLink);	// imul    edx, 0Eh	; sub_156E9C0
		CPatch::PatchUINT8(0x156EBD8 + 2, SizeOfCCarPathLink);	// imul    edx, 0Eh	; sub_156E9C0
		CPatch::PatchUINT8(0x156F801 + 2, SizeOfCCarPathLink);	// imul    eax, 0Eh	; _ZN9CPathFind16LoadPathFindDataEP8RwStreami
		CPatch::PatchUINT8(0x156F813 + 2, SizeOfCCarPathLink);	// imul    ecx, 0Eh	; _ZN9CPathFind16LoadPathFindDataEP8RwStreami
	}
	#endif		

	// Define variables for automatic patch
	#if TRUE
	{
		// variables
		CCodeMover::SetVariable("PATHS_DEBUG", CPatch::IsDebugModeActive());

		CCodeMover::SetVariable("TOTAL_NUMBER_OF_PATH_INDICES", iTotalNumberOfPathFiles);
		CCodeMover::SetVariable("TOTAL_NUMBER_OF_PATH_INDICES_WITH_INTERIOR_SLOTS", iTotalNumberOfPathIndicesIncludingInterior);
		CCodeMover::SetVariable("NUMBER_OF_PATH_FILES_PER_DIMENSION", iNumberOfPathFilesPerDimension);
		CCodeMover::SetVariable("NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE", iNumberOfPathFilesPerDimension - 1);
		CCodeMover::SetVariable("NUMBER_OF_PATH_INTERIOR_SLOTS", iNumberOfPathInteriorSlots);
		CCodeMover::SetVariable("SIZE_OF_POINTERS_FOR_ONE_DIMENSION", iNumberOfPathFilesPerDimension * 4);
		CCodeMover::SetVariable("MINUS_1", -1);

		// functions
		CCodeMover::SetVariable("GET_PATH_POINT_INDEX", &GetPathPointIndexForVehicle_hook);
		CCodeMover::SetVariable("SET_PATH_POINT_INDEX", &SetPathPointIndexForVehicle_hook);
	}
	#endif

	// Manual patches
	#if TRUE
	{
		CPatch::RedirectCode(0x44DC85, &patch_CPathFind__MarkRegionsForCoors_44DC85);	// lea     edx, ToBeStreamed[ebx+ebp*8]
		CPatch::RedirectCode(0x450CBF, &patch_CPathFind__UpdateStreaming_450CBF);	// lea     edi, ToBeStreamed[esi+ebx*8]
		CPatch::RedirectCode(0x450CA5, &patch_CPathFind__UpdateStreaming_450CA5);	// lea     edi, ToBeStreamedForScript[esi+ebx*8]
		CPatch::RedirectCode(0x450D11, &patch_CPathFind__UpdateStreaming_450D11);	// mov     al, ToBeStreamedForScript[esi+ebp*8]
		CPatch::RedirectCode(0x450D00, &patch_CPathFind__UpdateStreaming_450D00);	// mov     al, ToBeStreamed[esi+ebp*8]

		CPatch::RedirectCode(0x156A57D, &patch_CCarCtrl__JoinCarWithRoadSystemGotoCoors_156A57D);

		CPatch::PatchUINT32(0x44EFD3 + 4, iTotalNumberOfPathFiles);		// mov     [esp+28h+var_8], 64
		CPatch::PatchUINT32(0x44F844 + 4, iTotalNumberOfPathFiles);		// mov     [esp+2Ch+unk6], 64
		CPatch::PatchUINT32(0x451414 + 4, iTotalNumberOfPathFiles);		// mov     [esp+54h+var_38], 64
		CPatch::PatchUINT32(0x44F8D9 + 4, iTotalNumberOfPathIndicesIncludingInterior);		// mov     [esp+18h+var_4], 72
		CPatch::PatchUINT32(0x44FA45 + 4, iTotalNumberOfPathIndicesIncludingInterior);		// mov     [esp+14h+pResult], 72

		// size of navi link
		CPatch::PatchUINT8(0x4503C7 + 2, SizeOfNaviLink);	// add     edi, 2
		CPatch::PatchUINT8(0x44F143 + 2, SizeOfNaviLink);	// add     esi, 2

		//////////////

		CCodeMover::FixOnAddress(0x45263E, 3, "\x01\x02\x8d\x82\x05\x04TOTAL_NUMBER_OF_PATH_INDICES\x00\x01\x02\x50\x53", 0x452643);

		if (!CPatch::IsDebugModeActive())
		{
			CPatch::RedirectMethod(0x44D080, &CPathFind_extended::Init);

			if (!bDisableLoadingPaths)
				CPatch::RedirectMethod(0x4529F0, &CPathFind_extended::LoadPathFindData);

			CPatch::RedirectMethod(0x44D0F0, &CPathFind_extended::UnLoadPathFindData);

			CPatch::RedirectCode(0x42749E, &patch_CCarCtrl__PickNextNodeToChaseCar_42749E);

			// size of navi link
			CPatch::PatchMemoryData(0x45037E, "\x8d\x3c\x82", 3);
			CPatch::PatchMemoryData(0x460F04, "\x8d\x04\x81", 3);

			Address_CPathFind__CalcRoadDensity_44F084 = g_mCalc.GetCurrentVAbyPreferedVA(0x44F084);
			CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x44F07E), &patch_CPathFind__CalcRoadDensity_44F07E);

			// flood IDs
			{
				CPatch::RedirectCode(0x44E666, &patch_CPathFind__CountFloodFillGroups_44E666);
				CPatch::RedirectCode(0x44E6D0, &patch_CPathFind__CountFloodFillGroups_44E6D0);
				CPatch::RedirectCode(0x44E6F1, &patch_CPathFind__CountFloodFillGroups_44E6F1);
				CPatch::RedirectCode(0x44E744, &patch_CPathFind__CountFloodFillGroups_44E744);
				CPatch::RedirectCode(0x44E74B, &patch_CPathFind__CountFloodFillGroups_44E74B);
				CPatch::RedirectCode(0x451715, &patch_CPathFind__DoPathSearch_451715);
				CPatch::RedirectCode(0x4522BF, &patch_CPathFind__CompleteNewInterior_4522BF);
				CPatch::RedirectCode(0x45239A, &patch_CPathFind__CompleteNewInterior_45239A);
			}

			// CLinkAddress constructor
			CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x4241B0), &patch_CLinkAddress__Constructor_4241B0);

			// racing
			{
				CPatch::EnterNewLevelAndDisableDebugState();
				CPatch::RedirectCode(0x156A20C, &patch_CPathFind__FindLinkBetweenNodes_156A20C);
				CPatch::RedirectCode(0x156A194, &patch_CPathFind__FindLinkBetweenNodes_156A194);
				CPatch::RedirectCode(0x156A1B5, &patch_CPathFind__FindLinkBetweenNodes_156A1B5);
				CPatch::RedirectCode(0x435C93, &patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435C93);
				CPatch::RedirectCode(0x435CC7, &patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435CC7);
				CPatch::RedirectCode(0x435CD3, &patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435CD3);
				CPatch::RedirectFunction(0x4241B0, &patch_4241B0);
				CPatch::PatchUINT32(0x435D04 + 1, -1);
				CPatch::RedirectCode(0x435D63, &patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435D63);
				CPatch::RedirectCode(0x435D40, &patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435D40);
				CPatch::PatchUINT32(0x435D5C + 1, -1);
				CPatch::RedirectCode(0x435D85, &patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435D85);
				CPatch::RedirectCode(0x435DAC, &patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435DAC);
				CPatch::RedirectCode(0x435DE6, &patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435DE6);
				CPatch::RedirectCode(0x435E21, &patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435E21);
				CPatch::RedirectCode(0x435E54, &patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435E54);
				CPatch::RedirectCode(0x435E60, &patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435E60);
				CPatch::PatchUINT8(0x435EE4 + 2, sizeof(uint32_t));	// sub     edi, 2
				CPatch::PatchUINT8(0x435E12 + 2, sizeof(uint32_t));	// add     ebp, 2
				CPatch::RedirectCode(0x435DA7, &patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435DA7);
				CPatch::RedirectCode(0x435E1A, &patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_435E1A);
				CPatch::RedirectCode(0x422620, &patch_CCarCtrl__FindPercDependingOnDistToLink_422620);
				CPatch::RedirectCode(0x401E69, &patch_CCarCtrl__ClipTargetOrientationToLink_401E69);

				CPatch::LeaveThisLevel();
			}

			// CCarCtrl::StopCarIfNodesAreInvalid
			{
				CPatch::EnterNewLevelAndDisableDebugState();

				CPatch::PatchUINT32(0x1567ADB + 1, 0xFFFFFFFF);	// mov     edx, 0FFFFh

				CPatch::PatchMemoryData(0x1567AE0, "\x39\xd1\x90", 3);	// cmp     cx, dx
				CPatch::PatchMemoryData(0x1567AFE, "\x39\xd1\x90", 3);	// cmp     cx, dx				

				CPatch::LeaveThisLevel();
			}
		}
	}
	#endif

	// Apply automatic patch
	#if TRUE
	{
		// Count of active addresses: 678
		CCodeMover::FixOnAddressRel(0x403AE2, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xE2\x3A\x40\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x44\x24\xfc\x08\x00", 0x403AE9);	// line 1, 0x49D610 - sub_49D610 : mov     ax, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x41B9BD, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xBD\xB9\x41\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x07\x81\x2c\x24\x90\x03\x00\x00\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xC1\xB9\x41\x00\x16\x01\x02\x8b\xd1\x08\x00", 0x41B9C4);	// line 2, 0x41B980 - sub_41B980 : mov     cx, [esi+14h]
		CCodeMover::FixOnAddressRel(0x41B9DD, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xDD\xB9\x41\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x07\x81\x2c\x24\x90\x03\x00\x00\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xE1\xB9\x41\x00\x16\x01\x02\x8b\xc2\x08\x00", 0x41B9E4);	// line 3, 0x41B980 - sub_41B980 : mov     dx, [esi+16h]
		CCodeMover::FixOnAddressRel(0x41B9F7, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xF7\xB9\x41\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\xFA\xB9\x01\x00\x00", 0x41B9FC);	// line 4, 0x41B980 - sub_41B980 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x41BA10, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x10\xBA\x41\x00\x16\x01\x02\x8b\xc2\x08\x13\x02\x13\xBA\x01\x00\x00", 0x41BA15);	// line 5, 0x41B980 - sub_41B980 : movzx   eax, dx
		CCodeMover::FixOnAddressRel(0x41BA59, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x59\xBA\x41\x00\x16\x08\x13\x02\x5C\xBA\x01\x00\x00", 0x41BA5E);	// line 6, 0x41B980 - sub_41B980 : movzx   ecx, cx
		CCodeMover::FixOnAddressRel(0x41BACE, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xCE\xBA\x41\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x07\x81\x2c\x24\x90\x03\x00\x00\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x13\x04\xD2\xBA\x01\x00\x00", 0x41BAD6);	// line 7, 0x41B980 - sub_41B980 : movzx   ecx, word ptr [esi+16h]
		CCodeMover::FixOnAddressRel(0x41BB00, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x00\xBB\x41\x00\x16\x01\x03\x8b\x4b\x10\x08\x13\x04\x03\xBB\x01\x00\x00", 0x41BB07);	// line 8, 0x41B980 - sub_41B980 : movsx   ecx, word ptr [ebx]
		CCodeMover::FixOnAddressRel(0x41BB19, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x19\xBB\x41\x00\x16\x01\x03\x8b\x53\x14\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x1D\xBB\x41\x00\x16\x01\x03\x8b\x47\x10\x08\x00", 0x41BB20);	// line 9, 0x41B980 - sub_41B980 : movsx   edx, word ptr [ebx+2]
		CCodeMover::FixOnAddressRel(0x41BB2C, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x2C\xBB\x41\x00\x16\x01\x03\x8b\x4f\x14\x08\x13\x04\x30\xBB\x01\x00\x00", 0x41BB34);	// line 10, 0x41B980 - sub_41B980 : movsx   ecx, word ptr [edi+2]
		CCodeMover::FixOnAddressRel(0x420A11, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x11\x0A\x42\x00\x16\x01\x03\x8b\x41\x24\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x15\x0A\x42\x00\x16\x01\x03\x8b\x51\x20\x08\x00", 0x420A19);	// line 11, 0x420A10 - sub_420A10 : movsx   eax, word ptr [ecx+0Ch]
		CCodeMover::FixOnAddressRel(0x420A1D, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x1D\x0A\x42\x00\x16\x01\x03\x8b\x41\x1C\x08\x13\x04\x21\x0A\x02\x00\x00", 0x420A25);	// line 12, 0x420A10 - sub_420A10 : movsx   eax, word ptr [ecx+8]
		CCodeMover::FixOnAddressRel(0x420A61, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x61\x0A\x42\x00\x16\x01\x03\x8b\x41\x14\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x65\x0A\x42\x00\x16\x01\x03\x8b\x49\x10\x08\x00", 0x420A68);	// line 13, 0x420A60 - sub_420A60 : movsx   eax, word ptr [ecx+2]
		CCodeMover::FixOnAddressRel(0x42265F, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x5F\x26\x42\x00\x16\x01\x03\x8b\x50\x14\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x63\x26\x42\x00\x16\x01\x03\x8b\x40\x10\x08\x00", 0x422666);	// line 14, 0x422620 - sub_422620 : movsx   edx, word ptr [eax+2]
		CCodeMover::FixOnAddressRel(0x424385, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x85\x43\x42\x00\x16\x01\x03\x8b\x04\x81\x08\x13\x02\x89\x43\x02\x00\x00", 0x42438B);	// line 15, 0x424210 - sub_424210 : movzx   eax, word ptr [ecx+eax*2]
		CCodeMover::FixOnAddressRel(0x4245BD, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xBD\x45\x42\x00\x16\x01\x03\x8b\x0c\x8a\x08\x13\x03\xC1\x45\x02\x00\x00", 0x4245C4);	// line 16, 0x424210 - sub_424210 : movzx   ecx, word ptr [edx+ecx*2]
		CCodeMover::FixOnAddressRel(0x42463E, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x3E\x46\x42\x00\x16\x01\x03\x8b\x57\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x42\x46\x42\x00\x16\x01\x03\x8b\x47\x20\x08\x00", 0x424646);	// line 17, 0x424210 - sub_424210 : movsx   edx, word ptr [edi+8]
		CCodeMover::FixOnAddressRel(0x42464A, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x4A\x46\x42\x00\x16\x01\x03\x8b\x4e\x1C\x08\x13\x04\x4E\x46\x02\x00\x00", 0x424652);	// line 18, 0x424210 - sub_424210 : movsx   ecx, word ptr [esi+8]
		CCodeMover::FixOnAddressRel(0x424656, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x56\x46\x42\x00\x16\x01\x03\x8b\x56\x20\x08\x13\x06\x5A\x46\x02\x00\x00", 0x424660);	// line 19, 0x424210 - sub_424210 : movsx   edx, word ptr [esi+0Ah]
		CCodeMover::FixOnAddressRel(0x424764, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x64\x47\x42\x00\x16\x01\x03\x8b\x47\x24\x08\x13\x04\x68\x47\x02\x00\x00", 0x42476C);	// line 20, 0x424210 - sub_424210 : movsx   eax, word ptr [edi+0Ch]
		CCodeMover::FixOnAddressRel(0x424770, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x70\x47\x42\x00\x16\x01\x03\x8b\x4e\x24\x08\x13\x04\x74\x47\x02\x00\x00", 0x424778);	// line 21, 0x424210 - sub_424210 : movsx   ecx, word ptr [esi+0Ch]
		CCodeMover::FixOnAddressRel(0x4249AC, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xAC\x49\x42\x00\x16\x01\x03\x8b\x4e\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB0\x49\x42\x00\x16\x01\x03\x8b\x56\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB4\x49\x42\x00\x16\x01\x03\x8b\x47\x1C\x08\x00", 0x4249B8);	// line 22, 0x424210 - sub_424210 : movsx   ecx, word ptr [esi+8]
		CCodeMover::FixOnAddressRel(0x4249BC, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xBC\x49\x42\x00\x16\x01\x03\x8b\x4f\x20\x08\x13\x04\xC0\x49\x02\x00\x00", 0x4249C4);	// line 23, 0x424210 - sub_424210 : movsx   ecx, word ptr [edi+0Ah]
		CCodeMover::FixOnAddressRel(0x4249CE, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xCE\x49\x42\x00\x16\x01\x03\x8b\x57\x24\x08\x13\x04\xD2\x49\x02\x00\x00", 0x4249D6);	// line 24, 0x424210 - sub_424210 : movsx   edx, word ptr [edi+0Ch]
		CCodeMover::FixOnAddressRel(0x4249E0, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xE0\x49\x42\x00\x16\x01\x03\x8b\x46\x24\x08\x13\x04\xE4\x49\x02\x00\x00", 0x4249E8);	// line 25, 0x424210 - sub_424210 : movsx   eax, word ptr [esi+0Ch]
		CCodeMover::FixOnAddressRel(0x424A92, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x92\x4A\x42\x00\x16\x01\x03\x8b\x4f\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x96\x4A\x42\x00\x16\x01\x03\x8b\x57\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x9A\x4A\x42\x00\x16\x01\x03\x8b\x46\x1C\x08\x00", 0x424A9E);	// line 26, 0x424210 - sub_424210 : movsx   ecx, word ptr [edi+8]
		CCodeMover::FixOnAddressRel(0x424AA2, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA2\x4A\x42\x00\x16\x01\x03\x8b\x4e\x20\x08\x13\x04\xA6\x4A\x02\x00\x00", 0x424AAA);	// line 27, 0x424210 - sub_424210 : movsx   ecx, word ptr [esi+0Ah]
		CCodeMover::FixOnAddressRel(0x426F8D, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x8D\x6F\x42\x00\x16\x01\x04\x8b\x54\x28\x1C\x08\x00", 0x426F92);	// line 28, 0x426EF0 - sub_426EF0 : movsx   edx, word ptr [eax+ebp+8]
		CCodeMover::FixOnAddressRel(0x426F9E, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x9E\x6F\x42\x00\x16\x01\x03\x8b\x50\x24\x08\x13\x04\xA2\x6F\x02\x00\x00", 0x426FA6);	// line 29, 0x426EF0 - sub_426EF0 : movsx   edx, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x426FAA, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xAA\x6F\x42\x00\x16\x01\x03\x8b\x48\x20\x08\x13\x06\xAE\x6F\x02\x00\x00", 0x426FB4);	// line 30, 0x426EF0 - sub_426EF0 : movsx   ecx, word ptr [eax+0Ah]
		CCodeMover::FixOnAddressRel(0x42724B, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x4B\x72\x42\x00\x16\x01\x03\x8b\x51\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x4F\x72\x42\x00\x16\x01\x03\x8b\x49\x1C\x08\x00", 0x427253);	// line 31, 0x426EF0 - sub_426EF0 : movsx   edx, word ptr [ecx+0Ah]
		CCodeMover::FixOnAddressRel(0x427257, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x57\x72\x42\x00\x16\x01\x03\x8b\x50\x20\x08\x13\x04\x5B\x72\x02\x00\x00", 0x42725F);	// line 32, 0x426EF0 - sub_426EF0 : movsx   edx, word ptr [eax+0Ah]
		CCodeMover::FixOnAddressRel(0x427269, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x69\x72\x42\x00\x16\x01\x03\x8b\x50\x1C\x08\x13\x03\x6D\x72\x02\x00\x00", 0x427270);	// line 33, 0x426EF0 - sub_426EF0 : movsx   edx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x42738C, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x8C\x73\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x00", 0x427393);	// line 34, 0x426EF0 - sub_426EF0 : mov     dx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x427399, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x99\x73\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x4273A0);	// line 35, 0x426EF0 - sub_426EF0 : mov     cx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x4273A0, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xA0\x73\x42\x00\x16\x01\x01\x51\x01\x05\x68\xA8\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x4273A7);	// line 36, 0x426EF0 - sub_426EF0 : mov     [esi+3A8h], cx
		CCodeMover::FixOnAddressRel(0x4273AD, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xAD\x73\x42\x00\x16\x01\x01\x52\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x4273B4);	// line 37, 0x426EF0 - sub_426EF0 : mov     [esi+3A4h], dx
		CCodeMover::FixOnAddressRel(0x4273E2, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xE2\x73\x42\x00\x16\x01\x03\x8b\x0c\x88\x08\x13\x01\xE6\x73\x02\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xE7\x73\x42\x00\x16\x01\x01\x51\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x4273EE);	// line 38, 0x426EF0 - sub_426EF0 : mov     cx, [eax+ecx*2]
		CCodeMover::FixOnAddressRel(0x427424, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x24\x74\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x5C\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x2B\x74\x42\x00\x16\x01\x02\x8b\xc3\x08\x00", 0x42742E);	// line 39, 0x426EF0 - sub_426EF0 : mov     bx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x427450, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x50\x74\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x5C\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x57\x74\x42\x00\x16\x01\x02\x8b\xc3\x08\x00", 0x42745A);	// line 40, 0x426EF0 - sub_426EF0 : mov     bx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x427497, 16, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x97\x74\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x6C\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x9E\x74\x42\x00\x16\x01\x02\x8b\xcd\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xA1\x74\x42\x00\x16\x01\x02\x8b\xfd\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xA4\x74\x42\x00\x16\x08\x00", 0x4274A7);	// line 41, 0x426EF0 - sub_426EF0 : mov     bp, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x4274AB, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xAB\x74\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x6C\x24\xfc\x08\x00", 0x4274B2);	// line 42, 0x426EF0 - sub_426EF0 : movzx   ebp, word ptr [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x4274B6, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xB6\x74\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x6C\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xBD\x74\x42\x00\x16\x01\x02\x8b\xc3\x08\x00", 0x4274C0);	// line 43, 0x426EF0 - sub_426EF0 : movzx   ebp, word ptr [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x4274D8, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xD8\x74\x42\x00\x16\x01\x04\x8b\x44\x28\x10\x08\x13\x04\xDC\x74\x02\x00\x00", 0x4274E0);	// line 44, 0x426EF0 - sub_426EF0 : movsx   eax, word ptr [eax+ebp]
		CCodeMover::FixOnAddressRel(0x4274FF, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xFF\x74\x42\x00\x16\x01\x04\x8b\x4c\x08\x10\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x03\x75\x42\x00\x16\x01\x02\x8b\xd3\x08\x00", 0x427506);	// line 45, 0x426EF0 - sub_426EF0 : movsx   ecx, word ptr [eax+ecx]
		CCodeMover::FixOnAddressRel(0x427529, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x29\x75\x42\x00\x16\x01\x04\x8b\x54\x11\x10\x08\x13\x02\x2D\x75\x02\x00\x00", 0x42752F);	// line 46, 0x426EF0 - sub_426EF0 : movsx   edx, word ptr [ecx+edx]
		CCodeMover::FixOnAddressRel(0x42754A, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x4A\x75\x42\x00\x16\x01\x04\x8b\x54\x39\x10\x08\x13\x02\x4E\x75\x02\x00\x00", 0x427550);	// line 47, 0x426EF0 - sub_426EF0 : movsx   edx, word ptr [ecx+edi]
		CCodeMover::FixOnAddressRel(0x42755D, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x5D\x75\x42\x00\x16\x08\x13\x04\x60\x75\x02\x00\x00", 0x427564);	// line 48, 0x426EF0 - sub_426EF0 : movzx   ebx, bx
		CCodeMover::FixOnAddressRel(0x42756F, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x6F\x75\x42\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x427574);	// line 49, 0x426EF0 - sub_426EF0 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x4275A0, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xA0\x75\x42\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x4275A5);	// line 50, 0x426EF0 - sub_426EF0 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x4275D8, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xD8\x75\x42\x00\x16\x01\x04\x8b\x44\x1a\x14\x08\x00", 0x4275DD);	// line 51, 0x426EF0 - sub_426EF0 : movsx   eax, word ptr [edx+ebx+2]
		CCodeMover::FixOnAddressRel(0x427603, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x03\x76\x42\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x427608);	// line 52, 0x426EF0 - sub_426EF0 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x4276E8, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xE8\x76\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x4276EF);	// line 53, 0x426EF0 - sub_426EF0 : movzx   ecx, word ptr [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x427709, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x09\x77\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x427710);	// line 54, 0x426EF0 - sub_426EF0 : movzx   ecx, word ptr [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x4278A1, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xA1\x78\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x44\x24\xfc\x08\x00", 0x4278A8);	// line 55, 0x427740 - sub_427740 : mov     ax, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x4278AE, 14, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xAE\x78\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xB5\x78\x42\x00\x16\x01\x01\x50\x01\x05\x68\xA8\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x4278BC);	// line 56, 0x427740 - sub_427740 : mov     cx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x4278ED, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xED\x78\x42\x00\x16\x01\x01\x51\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x4278F4);	// line 57, 0x427740 - sub_427740 : mov     [esi+3A4h], cx
		CCodeMover::FixOnAddressRel(0x427960, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x60\x79\x42\x00\x16\x01\x03\x8b\x0c\x90\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x64\x79\x42\x00\x16\x01\x01\x51\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x42796B);	// line 58, 0x427740 - sub_427740 : mov     cx, [eax+edx*2]
		CCodeMover::FixOnAddressRel(0x42798F, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x8F\x79\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x44\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x96\x79\x42\x00\x16\x01\x02\x8b\xc8\x08\x00", 0x427999);	// line 59, 0x427740 - sub_427740 : mov     ax, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x4279BE, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xBE\x79\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x44\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xC5\x79\x42\x00\x16\x01\x02\x8b\xc8\x08\x00", 0x4279C8);	// line 60, 0x427740 - sub_427740 : mov     ax, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x4279E8, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xE8\x79\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x5C\x24\xfc\x08\x00", 0x4279EF);	// line 61, 0x427740 - sub_427740 : mov     bx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x427A01, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x01\x7A\x42\x00\x16\x01\x02\x8b\xcb\x08\x13\x04\x04\x7A\x02\x00\x00", 0x427A08);	// line 62, 0x427740 - sub_427740 : movzx   ecx, bx
		CCodeMover::FixOnAddressRel(0x427A26, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x26\x7A\x42\x00\x16\x01\x02\x8b\xcb\x08\x13\x04\x29\x7A\x02\x00\x00", 0x427A2D);	// line 63, 0x427740 - sub_427740 : movzx   ecx, bx
		CCodeMover::FixOnAddressRel(0x427A58, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x58\x7A\x42\x00\x16\x01\x02\x8b\xc8\x08\x13\x02\x5B\x7A\x02\x00\x00", 0x427A5D);	// line 64, 0x427740 - sub_427740 : movzx   ecx, ax
		CCodeMover::FixOnAddressRel(0x427AA1, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xA1\x7A\x42\x00\x16\x01\x02\x8b\xc8\x08\x13\x02\xA4\x7A\x02\x00\x00", 0x427AA6);	// line 65, 0x427740 - sub_427740 : movzx   ecx, ax
		CCodeMover::FixOnAddressRel(0x427AE9, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xE9\x7A\x42\x00\x16\x01\x02\x8b\xe8\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xEC\x7A\x42\x00\x16\x01\x02\x8b\xf8\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xEF\x7A\x42\x00\x16\x01\x02\x8b\xc8\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xF2\x7A\x42\x00\x16\x08\x00", 0x427AF5);	// line 66, 0x427740 - sub_427740 : movzx   ebp, ax
		CCodeMover::FixOnAddressRel(0x427AF9, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xF9\x7A\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x6C\x24\xfc\x08\x00", 0x427B00);	// line 67, 0x427740 - sub_427740 : movzx   ebp, word ptr [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x427B04, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x04\x7B\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x6C\x24\xfc\x08\x00", 0x427B0B);	// line 68, 0x427740 - sub_427740 : movzx   ebp, word ptr [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x427B23, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x23\x7B\x42\x00\x16\x01\x04\x8b\x44\x28\x14\x08\x00", 0x427B28);	// line 69, 0x427740 - sub_427740 : movsx   eax, word ptr [eax+ebp+2]
		CCodeMover::FixOnAddressRel(0x427B4E, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x4E\x7B\x42\x00\x16\x01\x04\x8b\x44\x28\x14\x08\x00", 0x427B53);	// line 70, 0x427740 - sub_427740 : movsx   eax, word ptr [eax+ebp+2]
		CCodeMover::FixOnAddressRel(0x427B79, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x79\x7B\x42\x00\x16\x01\x04\x8b\x44\x28\x14\x08\x00", 0x427B7E);	// line 71, 0x427740 - sub_427740 : movsx   eax, word ptr [eax+ebp+2]
		CCodeMover::FixOnAddressRel(0x427B9A, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x9A\x7B\x42\x00\x16\x01\x04\x8b\x44\x28\x14\x08\x00", 0x427B9F);	// line 72, 0x427740 - sub_427740 : movsx   eax, word ptr [eax+ebp+2]
		CCodeMover::FixOnAddressRel(0x427BB8, 9, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB8\x7B\x42\x00\x16\x01\x04\x8b\x44\x38\x10\x08\x13\x02\xBC\x7B\x02\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xBE\x7B\x42\x00\x16\x01\x02\x8b\xd3\x08\x00", 0x427BC1);	// line 73, 0x427740 - sub_427740 : movsx   eax, word ptr [eax+edi]
		CCodeMover::FixOnAddressRel(0x427BC5, 9, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xC5\x7B\x42\x00\x16\x08\x13\x06\xC8\x7B\x02\x00\x00", 0x427BCE);	// line 74, 0x427740 - sub_427740 : movzx   ebx, bx
		CCodeMover::FixOnAddressRel(0x427BF1, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xF1\x7B\x42\x00\x16\x01\x04\x8b\x44\x18\x10\x08\x13\x02\xF5\x7B\x02\x00\x00", 0x427BF7);	// line 75, 0x427740 - sub_427740 : movsx   eax, word ptr [eax+ebx]
		CCodeMover::FixOnAddressRel(0x427C28, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x28\x7C\x42\x00\x16\x01\x04\x8b\x4c\x08\x10\x08\x13\x02\x2C\x7C\x02\x00\x00", 0x427C2E);	// line 76, 0x427740 - sub_427740 : movsx   ecx, word ptr [eax+ecx]
		CCodeMover::FixOnAddressRel(0x427C45, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x45\x7C\x42\x00\x16\x01\x04\x8b\x54\x11\x10\x08\x13\x04\x49\x7C\x02\x00\x00", 0x427C4D);	// line 77, 0x427740 - sub_427740 : movsx   edx, word ptr [ecx+edx]
		CCodeMover::FixOnAddressRel(0x427CF3, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xF3\x7C\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x427CFA);	// line 78, 0x427740 - sub_427740 : movzx   ecx, word ptr [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x427D1F, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x1F\x7D\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x427D26);	// line 79, 0x427740 - sub_427740 : movzx   ecx, word ptr [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x427D57, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x57\x7D\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x427D5E);	// line 80, 0x427740 - sub_427740 : mov     cx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x427D62, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x62\x7D\x42\x00\x16\x01\x02\x8b\xc1\x08\x13\x04\x65\x7D\x02\x00\x00", 0x427D69);	// line 81, 0x427740 - sub_427740 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x427D7D, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x7D\x7D\x42\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x427D82);	// line 82, 0x427740 - sub_427740 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x427D86, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x86\x7D\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x7c\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x8D\x7D\x42\x00\x16\x01\x02\x8b\xc1\x08\x00", 0x427D90);	// line 83, 0x427740 - sub_427740 : mov     di, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x427DA4, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA4\x7D\x42\x00\x16\x01\x04\x8b\x44\x10\x10\x08\x13\x08\xA8\x7D\x02\x00\x00", 0x427DB0);	// line 84, 0x427740 - sub_427740 : movsx   eax, word ptr [edx+eax]
		CCodeMover::FixOnAddressRel(0x427DCA, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xCA\x7D\x42\x00\x16\x01\x02\x8b\xc7\x08\x13\x02\xCD\x7D\x02\x00\x00", 0x427DCF);	// line 85, 0x427740 - sub_427740 : movzx   eax, di
		CCodeMover::FixOnAddressRel(0x427DFF, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xFF\x7D\x42\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x427E04);	// line 86, 0x427740 - sub_427740 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x427E08, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x08\x7E\x42\x00\x16\x01\x02\x8b\xc7\x08\x13\x04\x0B\x7E\x02\x00\x00", 0x427E0F);	// line 87, 0x427740 - sub_427740 : movzx   eax, di
		CCodeMover::FixOnAddressRel(0x427E33, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x33\x7E\x42\x00\x16\x01\x04\x8b\x44\x10\x10\x08\x13\x07\x37\x7E\x02\x00\x00", 0x427E3E);	// line 88, 0x427740 - sub_427740 : movsx   eax, word ptr [edx+eax]
		CCodeMover::FixOnAddressRel(0x427E49, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x49\x7E\x42\x00\x16\x01\x02\x8b\xc1\x08\x13\x04\x4C\x7E\x02\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x50\x7E\x42\x00\x16\x08\x00", 0x427E53);	// line 89, 0x427740 - sub_427740 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x427E6D, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x6D\x7E\x42\x00\x16\x01\x02\x8b\xd7\x08\x13\x02\x70\x7E\x02\x00\x00", 0x427E72);	// line 90, 0x427740 - sub_427740 : movzx   edx, di
		CCodeMover::FixOnAddressRel(0x427E75, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x75\x7E\x42\x00\x16\x08\x13\x04\x78\x7E\x02\x00\x00", 0x427E7C);	// line 91, 0x427740 - sub_427740 : movzx   edi, di
		CCodeMover::FixOnAddressRel(0x428047, 6, "\x01\x01\x3d\x05\x04""MINUS_1\x00\x01\x02\x0F\x85\x15\x53\x80\x02\x00\x00", 0x42804D);	// line 92, 0x428040 - sub_428040 : cmp     ax, 0FFFFh
		CCodeMover::FixOnAddressRel(0x42805A, 5, "\x01\x02\x81\xfe\x05\x04""MINUS_1\x00\x00", 0x42805F);	// line 93, 0x428040 - sub_428040 : cmp     si, 0FFFFh
		CCodeMover::FixOnAddressRel(0x4280B2, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xB2\x80\x42\x00\x16\x01\x02\x8b\xc8\x08\x13\x02\xB5\x80\x02\x00\x00", 0x4280B7);	// line 94, 0x428040 - sub_428040 : movzx   ecx, ax
		CCodeMover::FixOnAddressRel(0x4280CB, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xCB\x80\x42\x00\x16\x01\x02\x8b\xc6\x08\x13\x02\xCE\x80\x02\x00\x00", 0x4280D0);	// line 95, 0x428040 - sub_428040 : movzx   eax, si
		CCodeMover::FixOnAddressRel(0x428107, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x07\x81\x42\x00\x16\x01\x03\x8b\x57\x10\x08\x13\x04\x0A\x81\x02\x00\x00", 0x42810E);	// line 96, 0x428040 - sub_428040 : movsx   edx, word ptr [edi]
		CCodeMover::FixOnAddressRel(0x428114, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x14\x81\x42\x00\x16\x01\x03\x8b\x47\x14\x08\x13\x06\x18\x81\x02\x00\x00", 0x42811E);	// line 97, 0x428040 - sub_428040 : movsx   eax, word ptr [edi+2]
		CCodeMover::FixOnAddressRel(0x42819C, 13, "\x01\x01\x3d\x05\x04""MINUS_1\x00\x01\x02\x0F\x84\x15\xd4\x82\x02\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xA6\x81\x42\x00\x16\x08\x00", 0x4281A9);	// line 98, 0x428040 - sub_428040 : cmp     ax, 0FFFFh
		CCodeMover::FixOnAddressRel(0x4281BF, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xBF\x81\x42\x00\x16\x01\x03\x8b\x46\x14\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xC3\x81\x42\x00\x16\x01\x03\x8b\x51\x14\x08\x00", 0x4281C7);	// line 99, 0x428040 - sub_428040 : movsx   eax, word ptr [esi+2]
		CCodeMover::FixOnAddressRel(0x4281CB, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xCB\x81\x42\x00\x16\x01\x03\x8b\x46\x10\x08\x13\x04\xCE\x81\x02\x00\x00", 0x4281D2);	// line 100, 0x428040 - sub_428040 : movsx   eax, word ptr [esi]
		CCodeMover::FixOnAddressRel(0x4281D6, 9, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xD6\x81\x42\x00\x16\x01\x03\x8b\x51\x10\x08\x13\x06\xD9\x81\x02\x00\x00", 0x4281DF);	// line 101, 0x428040 - sub_428040 : movsx   edx, word ptr [ecx]
		CCodeMover::FixOnAddressRel(0x428244, 13, "\x01\x01\x3d\x05\x04""MINUS_1\x00\x01\x02\x0F\x84\x15\xd8\x82\x02\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x4E\x82\x42\x00\x16\x08\x00", 0x428251);	// line 102, 0x428040 - sub_428040 : cmp     ax, 0FFFFh
		CCodeMover::FixOnAddressRel(0x428267, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x67\x82\x42\x00\x16\x01\x03\x8b\x46\x14\x08\x13\x04\x6B\x82\x02\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x6F\x82\x42\x00\x16\x01\x03\x8b\x41\x14\x08\x00", 0x428273);	// line 103, 0x428040 - sub_428040 : movsx   eax, word ptr [esi+2]
		CCodeMover::FixOnAddressRel(0x42827B, 9, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x7B\x82\x42\x00\x16\x01\x03\x8b\x46\x10\x08\x13\x06\x7E\x82\x02\x00\x00", 0x428284);	// line 104, 0x428040 - sub_428040 : movsx   eax, word ptr [esi]
		CCodeMover::FixOnAddressRel(0x42828C, 9, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x8C\x82\x42\x00\x16\x01\x03\x8b\x41\x10\x08\x13\x06\x8F\x82\x02\x00\x00", 0x428295);	// line 105, 0x428040 - sub_428040 : movsx   eax, word ptr [ecx]
		CCodeMover::FixOnAddressRel(0x4282D8, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xD8\x82\x42\x00\x16\x01\x03\x8b\x4e\x10\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xDB\x82\x42\x00\x16\x01\x03\x8b\x46\x14\x08\x00", 0x4282DF);	// line 106, 0x428040 - sub_428040 : movsx   ecx, word ptr [esi]
		CCodeMover::FixOnAddressRel(0x42B510, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x10\xB5\x42\x00\x16\x01\x03\x8b\x14\xba\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x14\xB5\x42\x00\x16\x01\x01\x52\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x42B51B);	// line 107, 0x42B470 - sub_42B470 : mov     dx, [edx+edi*2]
		CCodeMover::FixOnAddressRel(0x42B63A, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x3A\xB6\x42\x00\x16\x01\x03\x8b\x58\x24\x08\x13\x04\x3E\xB6\x02\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x42\xB6\x42\x00\x16\x01\x03\x8b\x58\x20\x08\x00", 0x42B646);	// line 108, 0x42B470 - sub_42B470 : movsx   ebx, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x42B64A, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x4A\xB6\x42\x00\x16\x01\x03\x8b\x40\x1C\x08\x13\x06\x4E\xB6\x02\x00\x00", 0x42B654);	// line 109, 0x42B470 - sub_42B470 : movsx   eax, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x42B684, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x84\xB6\x42\x00\x16\x01\x03\x8b\x48\x24\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x88\xB6\x42\x00\x16\x01\x03\x8b\x50\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x8C\xB6\x42\x00\x16\x01\x03\x8b\x40\x1C\x08\x00", 0x42B690);	// line 110, 0x42B470 - sub_42B470 : movsx   ecx, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x42B762, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x62\xB7\x42\x00\x16\x01\x03\x8b\x14\x97\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x66\xB7\x42\x00\x16\x01\x01\x52\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x42B76D);	// line 111, 0x42B470 - sub_42B470 : mov     dx, [edi+edx*2]
		CCodeMover::FixOnAddressRel(0x42BA33, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x33\xBA\x42\x00\x16\x01\x04\x8b\x44\x11\x24\x08\x00", 0x42BA38);	// line 112, 0x42B7D7 - sub_42B7D7 : movsx   eax, word ptr [edx+ecx+0Ch]
		CCodeMover::FixOnAddressRel(0x42BA54, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x54\xBA\x42\x00\x16\x01\x04\x8b\x4c\x10\x24\x08\x00", 0x42BA59);	// line 113, 0x42B7D7 - sub_42B7D7 : movsx   ecx, word ptr [eax+edx+0Ch]
		CCodeMover::FixOnAddressRel(0x42BEC4, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xC4\xBE\x42\x00\x16\x01\x03\x8b\x77\x1C\x08\x13\x04\xC8\xBE\x02\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xCC\xBE\x42\x00\x16\x01\x03\x8b\x77\x20\x08\x00", 0x42BED0);	// line 114, 0x42BD20 - sub_42BD20 : movsx   esi, word ptr [edi+8]
		CCodeMover::FixOnAddressRel(0x42BEDE, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xDE\xBE\x42\x00\x16\x01\x03\x8b\x77\x24\x08\x13\x04\xE2\xBE\x02\x00\x00", 0x42BEE6);	// line 115, 0x42BD20 - sub_42BD20 : movsx   esi, word ptr [edi+0Ch]
		CCodeMover::FixOnAddressRel(0x42BF86, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x86\xBF\x42\x00\x16\x01\x03\x8b\x57\x1C\x08\x13\x02\x8A\xBF\x02\x00\x00", 0x42BF8C);	// line 116, 0x42BD20 - sub_42BD20 : movsx   edx, word ptr [edi+8]
		CCodeMover::FixOnAddressRel(0x42BF96, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x96\xBF\x42\x00\x16\x01\x03\x8b\x57\x24\x08\x13\x04\x9A\xBF\x02\x00\x00", 0x42BF9E);	// line 117, 0x42BD20 - sub_42BD20 : movsx   edx, word ptr [edi+0Ch]
		CCodeMover::FixOnAddressRel(0x42BFA8, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA8\xBF\x42\x00\x16\x01\x03\x8b\x47\x20\x08\x13\x04\xAC\xBF\x02\x00\x00", 0x42BFB0);	// line 118, 0x42BD20 - sub_42BD20 : movsx   eax, word ptr [edi+0Ah]
		CCodeMover::FixOnAddressRel(0x42BFD4, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xD4\xBF\x42\x00\x16\x01\x03\x8b\x46\x24\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xD8\xBF\x42\x00\x16\x01\x03\x8b\x56\x20\x08\x00", 0x42BFDC);	// line 119, 0x42BD20 - sub_42BD20 : movsx   eax, word ptr [esi+0Ch]
		CCodeMover::FixOnAddressRel(0x42BFE0, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xE0\xBF\x42\x00\x16\x01\x03\x8b\x46\x1C\x08\x13\x04\xE4\xBF\x02\x00\x00", 0x42BFE8);	// line 120, 0x42BD20 - sub_42BD20 : movsx   eax, word ptr [esi+8]
		CCodeMover::FixOnAddressRel(0x42C075, 16, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x75\xC0\x42\x00\x16\x01\x03\x8b\x4f\x1C\x08\x13\x04\x79\xC0\x02\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x7D\xC0\x42\x00\x16\x01\x03\x8b\x57\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x81\xC0\x42\x00\x16\x01\x03\x8b\x47\x24\x08\x00", 0x42C085);	// line 121, 0x42BD20 - sub_42BD20 : movsx   ecx, word ptr [edi+8]
		CCodeMover::FixOnAddressRel(0x42C089, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x89\xC0\x42\x00\x16\x01\x03\x8b\x4e\x1C\x08\x13\x04\x8D\xC0\x02\x00\x00", 0x42C091);	// line 122, 0x42BD20 - sub_42BD20 : movsx   ecx, word ptr [esi+8]
		CCodeMover::FixOnAddressRel(0x42C09B, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x9B\xC0\x42\x00\x16\x01\x03\x8b\x56\x20\x08\x13\x04\x9F\xC0\x02\x00\x00", 0x42C0A3);	// line 123, 0x42BD20 - sub_42BD20 : movsx   edx, word ptr [esi+0Ah]
		CCodeMover::FixOnAddressRel(0x42C0AD, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xAD\xC0\x42\x00\x16\x01\x03\x8b\x46\x24\x08\x13\x03\xB1\xC0\x02\x00\x00", 0x42C0B4);	// line 124, 0x42BD20 - sub_42BD20 : movsx   eax, word ptr [esi+0Ch]
		CCodeMover::FixOnAddressRel(0x42DED8, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xD8\xDE\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xDF\xDE\x42\x00\x16\x01\x02\x8b\xf9\x08\x00", 0x42DEE2);	// line 125, 0x42DE80 - sub_42DE80 : mov     cx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x42DF1A, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x1A\xDF\x42\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\x1D\xDF\x02\x00\x00", 0x42DF1F);	// line 126, 0x42DE80 - sub_42DE80 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x42DF4D, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x4D\xDF\x42\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\x50\xDF\x02\x00\x00", 0x42DF52);	// line 127, 0x42DE80 - sub_42DE80 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x42DF69, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x69\xDF\x42\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\x6C\xDF\x02\x00\x00", 0x42DF6E);	// line 128, 0x42DE80 - sub_42DE80 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x42DF8C, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x8C\xDF\x42\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\x8F\xDF\x02\x00\x00", 0x42DF91);	// line 129, 0x42DE80 - sub_42DE80 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x42DFA8, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xA8\xDF\x42\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\xAB\xDF\x02\x00\x00", 0x42DFAD);	// line 130, 0x42DE80 - sub_42DE80 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x42E0E9, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xE9\xE0\x42\x00\x16\x01\x03\x8b\x2c\x8a\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xED\xE0\x42\x00\x16\x01\x02\x8b\xcd\x08\x00", 0x42E0F0);	// line 131, 0x42DE80 - sub_42DE80 : mov     bp, [edx+ecx*2]
		CCodeMover::FixOnAddressRel(0x42E262, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x62\xE2\x42\x00\x16\x01\x03\x8b\x04\x81\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x66\xE2\x42\x00\x16\x01\x02\x8b\xc8\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x69\xE2\x42\x00\x07\x04\x00\x00\x00\x00PATHS_DEBUG\x00\x01\x04\x89\x44\x24\x58\x00", 0x42E26E);	// line 132, 0x42DE80 - sub_42DE80 : mov     ax, [ecx+eax*2]
		CCodeMover::FixOnAddressRel(0x42E3BF, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xBF\xE3\x42\x00\x16\x01\x03\x8b\x04\x8a\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xC3\xE3\x42\x00\x16\x01\x02\x8b\xc8\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xC6\xE3\x42\x00\x07\x04\x00\x00\x00\x00PATHS_DEBUG\x00\x01\x04\x89\x44\x24\x58\x00", 0x42E3CB);	// line 133, 0x42DE80 - sub_42DE80 : mov     ax, [edx+ecx*2]
		CCodeMover::FixOnAddressRel(0x42E451, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x51\xE4\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x42E458);	// line 134, 0x42DE80 - sub_42DE80 : mov     cx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x42E45E, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x5E\xE4\x42\x00\x07\x04\x00\x00\x00\x00PATHS_DEBUG\x00\x01\x04\x89\x4c\x24\x58\x00", 0x42E463);	// line 135, 0x42DE80 - sub_42DE80 : mov     word ptr [esp+54h+arg_0], cx
		CCodeMover::FixOnAddressRel(0x42E463, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x63\xE4\x42\x00\x07\x04\x00\x00\x00\x00PATHS_DEBUG\x00\x01\x04\x8b\x6c\x24\x58\x00", 0x42E468);	// line 136, 0x42DE80 - sub_42DE80 : mov     bp, word ptr [esp+54h+arg_0]
		CCodeMover::FixOnAddressRel(0x42E605, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x05\xE6\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x42E60C);	// line 137, 0x42DE80 - sub_42DE80 : mov     cx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x42E612, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x12\xE6\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x00", 0x42E619);	// line 138, 0x42DE80 - sub_42DE80 : mov     dx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x42E627, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x27\xE6\x42\x00\x16\x01\x01\x51\x01\x05\x68\xA8\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x42E62E);	// line 139, 0x42DE80 - sub_42DE80 : mov     [esi+3A8h], cx
		CCodeMover::FixOnAddressRel(0x42E634, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x34\xE6\x42\x00\x16\x01\x01\x52\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x42E63B);	// line 140, 0x42DE80 - sub_42DE80 : mov     [esi+3A4h], dx
		CCodeMover::FixOnAddressRel(0x42E65D, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x5D\xE6\x42\x00\x16\x01\x01\x55\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x42E664);	// line 141, 0x42DE80 - sub_42DE80 : mov     [esi+3A6h], bp
		CCodeMover::FixOnAddressRel(0x42E680, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x80\xE6\x42\x00\x16\x01\x02\x8b\xc5\x08\x13\x02\x83\xE6\x02\x00\x00", 0x42E685);	// line 142, 0x42DE80 - sub_42DE80 : movzx   eax, bp
		CCodeMover::FixOnAddressRel(0x42E6BB, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xBB\xE6\x42\x00\x16\x01\x02\x8b\xc5\x08\x13\x02\xBE\xE6\x02\x00\x00", 0x42E6C0);	// line 143, 0x42DE80 - sub_42DE80 : movzx   eax, bp
		CCodeMover::FixOnAddressRel(0x42E6F8, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xF8\xE6\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x7c\x24\xfc\x08\x00", 0x42E6FF);	// line 144, 0x42DE80 - sub_42DE80 : mov     di, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x42E706, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x06\xE7\x42\x00\x16\x01\x02\x8b\xd7\x08\x13\x04\x09\xE7\x02\x00\x00", 0x42E70D);	// line 145, 0x42DE80 - sub_42DE80 : movzx   edx, di
		CCodeMover::FixOnAddressRel(0x42E72F, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x2F\xE7\x42\x00\x16\x01\x02\x8b\xd7\x08\x13\x04\x32\xE7\x02\x00\x00", 0x42E736);	// line 146, 0x42DE80 - sub_42DE80 : movzx   edx, di
		CCodeMover::FixOnAddressRel(0x42E7E3, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xE3\xE7\x42\x00\x16\x01\x04\x8b\x54\x11\x1C\x08\x00", 0x42E7E8);	// line 147, 0x42DE80 - sub_42DE80 : movsx   edx, word ptr [ecx+edx+8]
		CCodeMover::FixOnAddressRel(0x42E80C, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x0C\xE8\x42\x00\x16\x01\x04\x8b\x54\x3a\x1C\x08\x00", 0x42E811);	// line 148, 0x42DE80 - sub_42DE80 : movsx   edx, word ptr [edx+edi+8]
		CCodeMover::FixOnAddressRel(0x42E835, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x35\xE8\x42\x00\x16\x01\x04\x8b\x54\x3a\x1C\x08\x00", 0x42E83A);	// line 149, 0x42DE80 - sub_42DE80 : movsx   edx, word ptr [edx+edi+8]
		CCodeMover::FixOnAddressRel(0x42E85E, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x5E\xE8\x42\x00\x16\x01\x04\x8b\x54\x3a\x1C\x08\x00", 0x42E863);	// line 150, 0x42DE80 - sub_42DE80 : movsx   edx, word ptr [edx+edi+8]
		CCodeMover::FixOnAddressRel(0x42E887, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x87\xE8\x42\x00\x16\x01\x04\x8b\x54\x3a\x20\x08\x00", 0x42E88C);	// line 151, 0x42DE80 - sub_42DE80 : movsx   edx, word ptr [edx+edi+0Ah]
		CCodeMover::FixOnAddressRel(0x42E8B6, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xB6\xE8\x42\x00\x16\x01\x04\x8b\x54\x3a\x20\x08\x00", 0x42E8BB);	// line 152, 0x42DE80 - sub_42DE80 : movsx   edx, word ptr [edx+edi+0Ah]
		CCodeMover::FixOnAddressRel(0x42E8E5, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xE5\xE8\x42\x00\x16\x01\x04\x8b\x54\x10\x20\x08\x00", 0x42E8EA);	// line 153, 0x42DE80 - sub_42DE80 : movsx   edx, word ptr [eax+edx+0Ah]
		CCodeMover::FixOnAddressRel(0x42E910, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x10\xE9\x42\x00\x16\x01\x04\x8b\x44\x11\x20\x08\x00", 0x42E915);	// line 154, 0x42DE80 - sub_42DE80 : movsx   eax, word ptr [edx+ecx+0Ah]
		CCodeMover::FixOnAddressRel(0x42E9F1, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xF1\xE9\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x42E9F8);	// line 155, 0x42DE80 - sub_42DE80 : movzx   ecx, word ptr [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x42EA12, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x12\xEA\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x42EA19);	// line 156, 0x42DE80 - sub_42DE80 : movzx   ecx, word ptr [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x42EA55, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x55\xEA\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x42EA5C);	// line 157, 0x42DE80 - sub_42DE80 : mov     cx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x42EA60, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x60\xEA\x42\x00\x16\x01\x02\x8b\xc1\x08\x13\x04\x63\xEA\x02\x00\x00", 0x42EA67);	// line 158, 0x42DE80 - sub_42DE80 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x42EA7B, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x7B\xEA\x42\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x42EA80);	// line 159, 0x42DE80 - sub_42DE80 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x42EA84, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x84\xEA\x42\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x7c\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x8B\xEA\x42\x00\x16\x01\x02\x8b\xc1\x08\x00", 0x42EA8E);	// line 160, 0x42DE80 - sub_42DE80 : mov     di, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x42EAA2, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA2\xEA\x42\x00\x16\x01\x04\x8b\x44\x10\x10\x08\x13\x08\xA6\xEA\x02\x00\x00", 0x42EAAE);	// line 161, 0x42DE80 - sub_42DE80 : movsx   eax, word ptr [edx+eax]
		CCodeMover::FixOnAddressRel(0x42EABC, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xBC\xEA\x42\x00\x16\x01\x02\x8b\xc7\x08\x13\x02\xBF\xEA\x02\x00\x00", 0x42EAC1);	// line 162, 0x42DE80 - sub_42DE80 : movzx   eax, di
		CCodeMover::FixOnAddressRel(0x42EAFD, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xFD\xEA\x42\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x42EB02);	// line 163, 0x42DE80 - sub_42DE80 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x42EB06, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x06\xEB\x42\x00\x16\x01\x02\x8b\xc7\x08\x13\x04\x09\xEB\x02\x00\x00", 0x42EB0D);	// line 164, 0x42DE80 - sub_42DE80 : movzx   eax, di
		CCodeMover::FixOnAddressRel(0x42EB31, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x31\xEB\x42\x00\x16\x01\x04\x8b\x44\x10\x10\x08\x13\x07\x35\xEB\x02\x00\x00", 0x42EB3C);	// line 165, 0x42DE80 - sub_42DE80 : movsx   eax, word ptr [edx+eax]
		CCodeMover::FixOnAddressRel(0x42EB47, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x47\xEB\x42\x00\x16\x01\x02\x8b\xc1\x08\x13\x04\x4A\xEB\x02\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x4E\xEB\x42\x00\x16\x08\x00", 0x42EB51);	// line 166, 0x42DE80 - sub_42DE80 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x42EB6D, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x6D\xEB\x42\x00\x16\x01\x02\x8b\xd7\x08\x13\x03\x70\xEB\x02\x00\x00", 0x42EB73);	// line 167, 0x42DE80 - sub_42DE80 : movzx   edx, di
		CCodeMover::FixOnAddressRel(0x42EB77, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x77\xEB\x42\x00\x16\x08\x13\x04\x7A\xEB\x02\x00\x00", 0x42EB7E);	// line 168, 0x42DE80 - sub_42DE80 : movzx   edi, di
		CCodeMover::FixOnAddressRel(0x42F5CF, 21, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xCF\xF5\x42\x00\x16\x01\x01\x53\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xD6\xF5\x42\x00\x16\x01\x01\x53\x01\x05\x68\xA8\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xDD\xF5\x42\x00\x16\x01\x01\x53\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x42F5E4);	// line 169, 0x42F5A0 - sub_42F5A0 : mov     [esi+3A4h], bx
		CCodeMover::FixOnAddressRel(0x42F6B2, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB2\xF6\x42\x00\x16\x01\x03\x8b\x58\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB6\xF6\x42\x00\x16\x01\x03\x8b\x40\x20\x08\x00", 0x42F6BA);	// line 170, 0x42F5A0 - sub_42F5A0 : movsx   ebx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x42F6BE, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xBE\xF6\x42\x00\x16\x01\x03\x8b\x59\x1C\x08\x13\x04\xC2\xF6\x02\x00\x00", 0x42F6C6);	// line 171, 0x42F5A0 - sub_42F5A0 : movsx   ebx, word ptr [ecx+8]
		CCodeMover::FixOnAddressRel(0x42F6E1, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xE1\xF6\x42\x00\x16\x01\x03\x8b\x41\x20\x08\x13\x06\xE5\xF6\x02\x00\x00", 0x42F6EB);	// line 172, 0x42F5A0 - sub_42F5A0 : movsx   eax, word ptr [ecx+0Ah]
		CCodeMover::FixOnAddressRel(0x42F7AD, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xAD\xF7\x42\x00\x16\x01\x03\x8b\x41\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB1\xF7\x42\x00\x16\x01\x03\x8b\x49\x20\x08\x00", 0x42F7B5);	// line 173, 0x42F5A0 - sub_42F5A0 : movsx   eax, word ptr [ecx+8]
		CCodeMover::FixOnAddressRel(0x42F7D7, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xD7\xF7\x42\x00\x16\x01\x03\x8b\x50\x1C\x08\x13\x04\xDB\xF7\x02\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xDF\xF7\x42\x00\x16\x01\x03\x8b\x50\x20\x08\x00", 0x42F7E3);	// line 174, 0x42F5A0 - sub_42F5A0 : movsx   edx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x4305D8, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xD8\x05\x43\x00\x16\x01\x03\x8b\x04\x82\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xDC\x05\x43\x00\x07\x04\x00\x00\x00\x00PATHS_DEBUG\x00\x01\x04\x89\x44\x24\x10\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xE1\x05\x43\x00\x16\x08\x00", 0x4305E4);	// line 175, 0x403AEE - sub_403AEE : mov     ax, [edx+eax*2]
		CCodeMover::FixOnAddressRel(0x4308B0, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xB0\x08\x43\x00\x07\x04\x00\x00\x00\x00PATHS_DEBUG\x00\x01\x04\x8b\x4c\x24\x10\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xB5\x08\x43\x00\x16\x01\x01\x51\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x4308BC);	// line 176, 0x403AEE - sub_403AEE : mov     cx, word ptr [esp+13Ch+var_12C]
		CCodeMover::FixOnAddressRel(0x430AFD, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xFD\x0A\x43\x00\x16\x01\x03\x8b\x04\x88\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x01\x0B\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x3b\x44\x24\xfc\x08\x00", 0x430B08);	// line 177, 0x403AEE - sub_403AEE : mov     ax, [eax+ecx*2]
		CCodeMover::FixOnAddressRel(0x430B0A, 13, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x0A\x0B\x43\x00\x16\x01\x02\x8b\xc8\x08\x13\x03\x0D\x0B\x03\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x10\x0B\x43\x00\x16\x01\x01\x50\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x430B17);	// line 178, 0x403AEE - sub_403AEE : movzx   ecx, ax
		CCodeMover::FixOnAddressRel(0x430C86, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x86\x0C\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x6C\x24\xfc\x08\x00", 0x430C8D);	// line 179, 0x403AEE - sub_403AEE : mov     bp, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x430CA8, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xA8\x0C\x43\x00\x16\x01\x02\x8b\xfd\x08\x01\x01\xE8\x15\x10\x0a\x02\x00\x00", 0x430CB0);	// line 180, 0x403AEE - sub_403AEE : movzx   edi, bp
		CCodeMover::FixOnAddressRel(0x430D1A, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x1A\x0D\x43\x00\x16\x01\x02\x8b\xfd\x08\x13\x02\x1D\x0D\x03\x00\x00", 0x430D1F);	// line 181, 0x403AEE - sub_403AEE : movzx   edi, bp
		CCodeMover::FixOnAddressRel(0x430D8C, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x8C\x0D\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x7c\x24\xfc\x08\x00", 0x430D93);	// line 182, 0x403AEE - sub_403AEE : mov     di, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x430DB3, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xB3\x0D\x43\x00\x16\x01\x02\x8b\xcf\x08\x13\x02\xB6\x0D\x03\x00\x00", 0x430DB8);	// line 183, 0x403AEE - sub_403AEE : movzx   ecx, di
		CCodeMover::FixOnAddressRel(0x430E6E, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x6E\x0E\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x6C\x24\xfc\x08\x00", 0x430E75);	// line 184, 0x403AEE - sub_403AEE : mov     bp, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x430E93, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x93\x0E\x43\x00\x16\x01\x02\x8b\xfd\x08\x01\x01\xE8\x15\x10\x0a\x02\x00\x00", 0x430E9B);	// line 185, 0x403AEE - sub_403AEE : movzx   edi, bp
		CCodeMover::FixOnAddressRel(0x430ECE, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xCE\x0E\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x7c\x24\xfc\x08\x00", 0x430ED5);	// line 186, 0x403AEE - sub_403AEE : mov     di, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x430EFF, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xFF\x0E\x43\x00\x16\x01\x02\x8b\xcf\x08\x13\x02\x02\x0F\x03\x00\x00", 0x430F04);	// line 187, 0x403AEE - sub_403AEE : movzx   ecx, di
		CCodeMover::FixOnAddressRel(0x431014, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x14\x10\x43\x00\x16\x01\x02\x8b\xc7\x08\x13\x02\x17\x10\x03\x00\x00", 0x431019);	// line 188, 0x403AEE - sub_403AEE : movzx   eax, di
		CCodeMover::FixOnAddressRel(0x431038, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x38\x10\x43\x00\x16\x01\x02\x8b\xc7\x08\x13\x02\x3B\x10\x03\x00\x00", 0x43103D);	// line 189, 0x403AEE - sub_403AEE : movzx   eax, di
		CCodeMover::FixOnAddressRel(0x43106D, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x6D\x10\x43\x00\x16\x01\x02\x8b\xc5\x08\x13\x02\x70\x10\x03\x00\x00", 0x431072);	// line 190, 0x403AEE - sub_403AEE : movzx   eax, bp
		CCodeMover::FixOnAddressRel(0x43109D, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x9D\x10\x43\x00\x16\x01\x02\x8b\xc5\x08\x13\x02\xA0\x10\x03\x00\x00", 0x4310A2);	// line 191, 0x403AEE - sub_403AEE : movzx   eax, bp
		CCodeMover::FixOnAddressRel(0x4310D3, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xD3\x10\x43\x00\x16\x01\x02\x8b\xcf\x08\x13\x02\xD6\x10\x03\x00\x00", 0x4310D8);	// line 192, 0x403AEE - sub_403AEE : movzx   ecx, di
		CCodeMover::FixOnAddressRel(0x431111, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x11\x11\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x431118);	// line 193, 0x403AEE - sub_403AEE : movzx   ecx, word ptr [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x4311D0, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xD0\x11\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x4311D7);	// line 194, 0x403AEE - sub_403AEE : mov     cx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x4311DB, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xDB\x11\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\xDE\x11\x03\x00\x00", 0x4311E0);	// line 195, 0x403AEE - sub_403AEE : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x43120B, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x0B\x12\x43\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x431210);	// line 196, 0x403AEE - sub_403AEE : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x431214, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x14\x12\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x7c\x24\xfc\x08\x00", 0x43121B);	// line 197, 0x403AEE - sub_403AEE : mov     di, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x43121F, 9, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x1F\x12\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x06\x22\x12\x03\x00\x00", 0x431228);	// line 198, 0x403AEE - sub_403AEE : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x43123C, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x3C\x12\x43\x00\x16\x01\x04\x8b\x44\x10\x10\x08\x13\x04\x40\x12\x03\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x44\x12\x43\x00\x16\x01\x02\x8b\xc7\x08\x00", 0x431247);	// line 199, 0x403AEE - sub_403AEE : movsx   eax, word ptr [edx+eax]
		CCodeMover::FixOnAddressRel(0x431289, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x89\x12\x43\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x43128E);	// line 200, 0x403AEE - sub_403AEE : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x43129A, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x9A\x12\x43\x00\x16\x01\x02\x8b\xc7\x08\x13\x04\x9D\x12\x03\x00\x00", 0x4312A1);	// line 201, 0x403AEE - sub_403AEE : movzx   eax, di
		CCodeMover::FixOnAddressRel(0x4312BF, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xBF\x12\x43\x00\x16\x01\x04\x8b\x44\x10\x10\x08\x13\x04\xC3\x12\x03\x00\x00", 0x4312C7);	// line 202, 0x403AEE - sub_403AEE : movsx   eax, word ptr [edx+eax]
		CCodeMover::FixOnAddressRel(0x4312EF, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xEF\x12\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x04\xF2\x12\x03\x00\x00", 0x4312F6);	// line 203, 0x403AEE - sub_403AEE : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x4312FA, 14, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xFA\x12\x43\x00\x16\x08\x13\x0B\xFD\x12\x03\x00\x00", 0x431308);	// line 204, 0x403AEE - sub_403AEE : movzx   ecx, cx
		CCodeMover::FixOnAddressRel(0x43130F, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x0F\x13\x43\x00\x16\x01\x02\x8b\xd7\x08\x13\x07\x12\x13\x03\x00\x00", 0x431319);	// line 205, 0x403AEE - sub_403AEE : movzx   edx, di
		CCodeMover::FixOnAddressRel(0x431393, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x93\x13\x43\x00\x16\x08\x13\x02\x96\x13\x03\x00\x00", 0x431398);	// line 206, 0x403AEE - sub_403AEE : movzx   edi, di
		CCodeMover::FixOnAddressRel(0x431468, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x68\x14\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x6F\x14\x43\x00\x16\x01\x02\x8b\xca\x08\x00", 0x431472);	// line 207, 0x403AEE - sub_403AEE : mov     dx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x4314A0, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xA0\x14\x43\x00\x16\x01\x04\x8b\x4c\x19\x14\x08\x00", 0x4314A5);	// line 208, 0x403AEE - sub_403AEE : movsx   ecx, word ptr [ebx+ecx+2]
		CCodeMover::FixOnAddressRel(0x4314A9, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xA9\x14\x43\x00\x16\x01\x02\x8b\xca\x08\x13\x04\xAC\x14\x03\x00\x00", 0x4314B0);	// line 209, 0x403AEE - sub_403AEE : movzx   ecx, dx
		CCodeMover::FixOnAddressRel(0x4314CB, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xCB\x14\x43\x00\x16\x01\x04\x8b\x4c\x11\x10\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xCF\x14\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x00", 0x4314D6);	// line 210, 0x403AEE - sub_403AEE : movsx   ecx, word ptr [edx+ecx]
		CCodeMover::FixOnAddressRel(0x4314DA, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xDA\x14\x43\x00\x16\x01\x02\x8b\xca\x08\x13\x02\xDD\x14\x03\x00\x00", 0x4314DF);	// line 211, 0x403AEE - sub_403AEE : movzx   ecx, dx
		CCodeMover::FixOnAddressRel(0x43151D, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x1D\x15\x43\x00\x16\x01\x04\x8b\x4c\x19\x14\x08\x00", 0x431522);	// line 212, 0x403AEE - sub_403AEE : movsx   ecx, word ptr [ebx+ecx+2]
		CCodeMover::FixOnAddressRel(0x431526, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x26\x15\x43\x00\x16\x01\x02\x8b\xca\x08\x13\x04\x29\x15\x03\x00\x00", 0x43152D);	// line 213, 0x403AEE - sub_403AEE : movzx   ecx, dx
		CCodeMover::FixOnAddressRel(0x431548, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x48\x15\x43\x00\x16\x01\x04\x8b\x4c\x11\x10\x08\x13\x04\x4C\x15\x03\x00\x00", 0x431550);	// line 214, 0x403AEE - sub_403AEE : movsx   ecx, word ptr [edx+ecx]
		CCodeMover::FixOnAddressRel(0x434966, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x66\x49\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x43496D);	// line 215, 0x434900 - sub_434900 : mov     cx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x43496F, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x6F\x49\x43\x00\x16\x01\x02\x8b\xd1\x08\x13\x03\x72\x49\x03\x00\x00", 0x434975);	// line 216, 0x434900 - sub_434900 : movzx   edx, cx
		CCodeMover::FixOnAddressRel(0x434985, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x85\x49\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x8C\x49\x43\x00\x16\x01\x02\x8b\xc2\x08\x00", 0x43498F);	// line 217, 0x434900 - sub_434900 : mov     dx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x4349AC, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xAC\x49\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x04\xAF\x49\x03\x00\x00", 0x4349B3);	// line 218, 0x434900 - sub_434900 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x4349D0, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xD0\x49\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x04\xD3\x49\x03\x00\x00", 0x4349D7);	// line 219, 0x434900 - sub_434900 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x434A01, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x01\x4A\x43\x00\x16\x01\x02\x8b\xc2\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x04\x4A\x43\x00\x16\x08\x00", 0x434A07);	// line 220, 0x434900 - sub_434900 : movzx   eax, dx
		CCodeMover::FixOnAddressRel(0x434A48, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x48\x4A\x43\x00\x16\x01\x02\x8b\xc2\x08\x13\x02\x4B\x4A\x03\x00\x00", 0x434A4D);	// line 221, 0x434900 - sub_434900 : movzx   eax, dx
		CCodeMover::FixOnAddressRel(0x434AA9, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xA9\x4A\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x434AB0);	// line 222, 0x434900 - sub_434900 : movzx   ecx, word ptr [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x434B10, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x10\x4B\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x17\x4B\x43\x00\x16\x01\x02\x8b\xc1\x08\x00", 0x434B1A);	// line 223, 0x434900 - sub_434900 : mov     cx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x434B2E, 18, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x2E\x4B\x43\x00\x16\x01\x04\x8b\x44\x10\x10\x08\x13\x04\x32\x4B\x03\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x36\x4B\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x7c\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x3D\x4B\x43\x00\x16\x01\x02\x8b\xc1\x08\x00", 0x434B40);	// line 224, 0x434900 - sub_434900 : movsx   eax, word ptr [edx+eax]
		CCodeMover::FixOnAddressRel(0x434B66, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x66\x4B\x43\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x434B6B);	// line 225, 0x434900 - sub_434900 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x434B6F, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x6F\x4B\x43\x00\x16\x01\x02\x8b\xc7\x08\x13\x02\x72\x4B\x03\x00\x00", 0x434B74);	// line 226, 0x434900 - sub_434900 : movzx   eax, di
		CCodeMover::FixOnAddressRel(0x434B88, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x88\x4B\x43\x00\x16\x01\x04\x8b\x44\x10\x10\x08\x13\x04\x8C\x4B\x03\x00\x00", 0x434B90);	// line 227, 0x434900 - sub_434900 : movsx   eax, word ptr [edx+eax]
		CCodeMover::FixOnAddressRel(0x434B98, 9, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x98\x4B\x43\x00\x16\x01\x02\x8b\xc7\x08\x13\x06\x9B\x4B\x03\x00\x00", 0x434BA1);	// line 228, 0x434900 - sub_434900 : movzx   eax, di
		CCodeMover::FixOnAddressRel(0x434BD3, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xD3\x4B\x43\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x434BD8);	// line 229, 0x434900 - sub_434900 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x434E63, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x63\x4E\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x44\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x6A\x4E\x43\x00\x16\x01\x02\x8b\xc8\x08\x00", 0x434E6D);	// line 230, 0x434900 - sub_434900 : mov     ax, [esi+3A4h]; jumptable 00434CDE default case
		CCodeMover::FixOnAddressRel(0x434E7F, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x7F\x4E\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x00", 0x434E86);	// line 231, 0x434900 - sub_434900 : movzx   edx, word ptr [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x434E98, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x98\x4E\x43\x00\x16\x01\x02\x8b\xc8\x08\x13\x02\x9B\x4E\x03\x00\x00", 0x434E9D);	// line 232, 0x434900 - sub_434900 : movzx   ecx, ax
		CCodeMover::FixOnAddressRel(0x434EC5, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xC5\x4E\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x434ECC);	// line 233, 0x434900 - sub_434900 : mov     cx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x434EE2, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xE2\x4E\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\xE5\x4E\x03\x00\x00", 0x434EE7);	// line 234, 0x434900 - sub_434900 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x434EFB, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xFB\x4E\x43\x00\x16\x01\x04\x8b\x44\x28\x10\x08\x13\x04\xFF\x4E\x03\x00\x00", 0x434F03);	// line 235, 0x434900 - sub_434900 : movsx   eax, word ptr [eax+ebp]
		CCodeMover::FixOnAddressRel(0x434F21, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x21\x4F\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\x24\x4F\x03\x00\x00", 0x434F26);	// line 236, 0x434900 - sub_434900 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x434F38, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x38\x4F\x43\x00\x16\x01\x04\x8b\x44\x28\x14\x08\x00", 0x434F3D);	// line 237, 0x434900 - sub_434900 : movsx   eax, word ptr [eax+ebp+2]
		CCodeMover::FixOnAddressRel(0x434F41, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x41\x4F\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x04\x44\x4F\x03\x00\x00", 0x434F48);	// line 238, 0x434900 - sub_434900 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x434FA6, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xA6\x4F\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\xA9\x4F\x03\x00\x00", 0x434FAB);	// line 239, 0x434900 - sub_434900 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x434FC8, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xC8\x4F\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x7c\x24\xfc\x08\x00", 0x434FCF);	// line 240, 0x434900 - sub_434900 : mov     di, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x434FD3, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xD3\x4F\x43\x00\x16\x01\x02\x8b\xc7\x08\x13\x02\xD6\x4F\x03\x00\x00", 0x434FD8);	// line 241, 0x434900 - sub_434900 : movzx   eax, di
		CCodeMover::FixOnAddressRel(0x435017, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x17\x50\x43\x00\x16\x01\x02\x8b\xc7\x08\x13\x02\x1A\x50\x03\x00\x00", 0x43501C);	// line 242, 0x434900 - sub_434900 : movzx   eax, di
		CCodeMover::FixOnAddressRel(0x435059, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x59\x50\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x04\x5C\x50\x03\x00\x00", 0x435060);	// line 243, 0x434900 - sub_434900 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x435074, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x74\x50\x43\x00\x16\x01\x04\x8b\x44\x38\x10\x08\x13\x04\x78\x50\x03\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x7C\x50\x43\x00\x16\x01\x02\x8b\xc1\x08\x00", 0x43507F);	// line 244, 0x434900 - sub_434900 : movsx   eax, word ptr [edi+eax]
		CCodeMover::FixOnAddressRel(0x43509F, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x9F\x50\x43\x00\x16\x01\x04\x8b\x44\x38\x14\x08\x00", 0x4350A4);	// line 245, 0x434900 - sub_434900 : movsx   eax, word ptr [edi+eax+2]
		CCodeMover::FixOnAddressRel(0x43512B, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x2B\x51\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\x2E\x51\x03\x00\x00", 0x435130);	// line 246, 0x434900 - sub_434900 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x435142, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x42\x51\x43\x00\x16\x01\x04\x8b\x44\x38\x10\x08\x13\x04\x46\x51\x03\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x4A\x51\x43\x00\x16\x01\x02\x8b\xc1\x08\x00", 0x43514D);	// line 247, 0x434900 - sub_434900 : movsx   eax, word ptr [edi+eax]
		CCodeMover::FixOnAddressRel(0x43516B, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x6B\x51\x43\x00\x16\x01\x04\x8b\x44\x08\x14\x08\x00", 0x435170);	// line 248, 0x434900 - sub_434900 : movsx   eax, word ptr [ecx+eax+2]
		CCodeMover::FixOnAddressRel(0x43537F, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x7F\x53\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x435386);	// line 249, 0x434900 - sub_434900 : movzx   ecx, word ptr [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x4353B0, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xB0\x53\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x4353B7);	// line 250, 0x434900 - sub_434900 : mov     cx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x4353D0, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xD0\x53\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\xD3\x53\x03\x00\x00", 0x4353D5);	// line 251, 0x434900 - sub_434900 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x4353E7, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xE7\x53\x43\x00\x16\x01\x04\x8b\x44\x28\x14\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xEC\x53\x43\x00\x16\x08\x00", 0x4353EF);	// line 252, 0x434900 - sub_434900 : movsx   eax, word ptr [eax+ebp+2]
		CCodeMover::FixOnAddressRel(0x43541F, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x1F\x54\x43\x00\x16\x01\x04\x8b\x4c\x08\x10\x08\x13\x03\x23\x54\x03\x00\x00", 0x435426);	// line 253, 0x434900 - sub_434900 : movsx   ecx, word ptr [eax+ecx]
		CCodeMover::FixOnAddressRel(0x4358BD, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xBD\x58\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x7c\x24\xfc\x08\x00", 0x4358C4);	// line 254, 0x435830 - sub_435830 : mov     di, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x4358C6, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xC6\x58\x43\x00\x16\x01\x02\x8b\xd7\x08\x13\x03\xC9\x58\x03\x00\x00", 0x4358CC);	// line 255, 0x435830 - sub_435830 : movzx   edx, di
		CCodeMover::FixOnAddressRel(0x4358DB, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xDB\x58\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xE2\x58\x43\x00\x16\x01\x02\x8b\xc2\x08\x00", 0x4358E5);	// line 256, 0x435830 - sub_435830 : mov     dx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x4358F7, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xF7\x58\x43\x00\x16\x01\x02\x8b\xc7\x08\x13\x02\xFA\x58\x03\x00\x00", 0x4358FC);	// line 257, 0x435830 - sub_435830 : movzx   eax, di
		CCodeMover::FixOnAddressRel(0x43590E, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x0E\x59\x43\x00\x16\x01\x04\x8b\x44\x18\x10\x08\x13\x04\x12\x59\x03\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x16\x59\x43\x00\x16\x01\x02\x8b\xc7\x08\x00", 0x435919);	// line 258, 0x435830 - sub_435830 : movsx   eax, word ptr [ebx+eax]
		CCodeMover::FixOnAddressRel(0x435937, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x37\x59\x43\x00\x16\x01\x04\x8b\x44\x18\x14\x08\x00", 0x43593C);	// line 259, 0x435830 - sub_435830 : movsx   eax, word ptr [ebx+eax+2]
		CCodeMover::FixOnAddressRel(0x435940, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x40\x59\x43\x00\x16\x01\x02\x8b\xc2\x08\x13\x02\x43\x59\x03\x00\x00", 0x435945);	// line 260, 0x435830 - sub_435830 : movzx   eax, dx
		CCodeMover::FixOnAddressRel(0x435957, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x57\x59\x43\x00\x16\x01\x04\x8b\x44\x18\x10\x08\x13\x04\x5B\x59\x03\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x5F\x59\x43\x00\x16\x01\x02\x8b\xc2\x08\x00", 0x435962);	// line 261, 0x435830 - sub_435830 : movsx   eax, word ptr [ebx+eax]
		CCodeMover::FixOnAddressRel(0x43598E, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x8E\x59\x43\x00\x16\x01\x04\x8b\x44\x18\x14\x08\x00", 0x435993);	// line 262, 0x435830 - sub_435830 : movsx   eax, word ptr [ebx+eax+2]
		CCodeMover::FixOnAddressRel(0x435BB4, 14, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xB4\x5B\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xBB\x5B\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x00", 0x435BC2);	// line 263, 0x435830 - sub_435830 : mov     cx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x435BC8, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xC8\x5B\x43\x00\x16\x01\x01\x52\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x435BCF);	// line 264, 0x435830 - sub_435830 : mov     [esi+3A4h], dx
		CCodeMover::FixOnAddressRel(0x435BF1, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xF1\x5B\x43\x00\x16\x01\x01\x51\x01\x05\x68\xA8\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x435BF8);	// line 265, 0x435830 - sub_435830 : mov     [esi+3A8h], cx
		CCodeMover::FixOnAddressRel(0x435C6D, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x6D\x5C\x43\x00\x16\x01\x03\x8b\x0c\x90\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x71\x5C\x43\x00\x16\x01\x01\x51\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06SET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x08\x00", 0x435C78);	// line 266, 0x435830 - sub_435830 : mov     cx, [eax+edx*2]
		CCodeMover::FixOnAddressRel(0x435CB4, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xB4\x5C\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x435CBB);	// line 267, 0x435830 - sub_435830 : mov     cx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x435CCC, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xCC\x5C\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x435CD3);	// line 268, 0x435830 - sub_435830 : mov     cx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x435E3C, 5, "\x01\x02\x81\xff\x05\x04""MINUS_1\x00\x00", 0x435E41);	// line 269, 0x435830 - sub_435830 : cmp     di, 0FFFFh
		CCodeMover::FixOnAddressRel(0x435E6A, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x6A\x5E\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\x6D\x5E\x03\x00\x00", 0x435E6F);	// line 270, 0x435830 - sub_435830 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x435E77, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x77\x5E\x43\x00\x16\x08\x13\x03\x7A\x5E\x03\x00\x00", 0x435E7D);	// line 271, 0x435830 - sub_435830 : movzx   ecx, cx
		CCodeMover::FixOnAddressRel(0x435E84, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x84\x5E\x43\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x435E89);	// line 272, 0x435830 - sub_435830 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x435EA6, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA6\x5E\x43\x00\x16\x01\x04\x8b\x4c\x08\x10\x08\x13\x06\xAA\x5E\x03\x00\x00", 0x435EB0);	// line 273, 0x435830 - sub_435830 : movsx   ecx, word ptr [eax+ecx]
		CCodeMover::FixOnAddressRel(0x435EF0, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xF0\x5E\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xF7\x5E\x43\x00\x16\x01\x02\x8b\xc1\x08\x00", 0x435EFA);	// line 274, 0x435830 - sub_435830 : mov     cx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x435F04, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x04\x5F\x43\x00\x16\x08\x13\x03\x07\x5F\x03\x00\x00", 0x435F0A);	// line 275, 0x435830 - sub_435830 : movzx   ecx, cx
		CCodeMover::FixOnAddressRel(0x435F11, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x11\x5F\x43\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x435F16);	// line 276, 0x435830 - sub_435830 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x435F33, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x33\x5F\x43\x00\x16\x01\x04\x8b\x4c\x08\x10\x08\x13\x06\x37\x5F\x03\x00\x00", 0x435F3D);	// line 277, 0x435830 - sub_435830 : movsx   ecx, word ptr [eax+ecx]
		CCodeMover::FixOnAddressRel(0x435F56, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x56\x5F\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x435F5D);	// line 278, 0x435830 - sub_435830 : mov     cx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x435F75, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x75\x5F\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x00", 0x435F7C);	// line 279, 0x435830 - sub_435830 : mov     dx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x435F89, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x89\x5F\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x7c\x24\xfc\x08\x00", 0x435F90);	// line 280, 0x435830 - sub_435830 : mov     di, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x435F92, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x92\x5F\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x99\x5F\x43\x00\x16\x01\x02\x8b\xcf\x08\x00", 0x435F9C);	// line 281, 0x435830 - sub_435830 : mov     dx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x435FB1, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xB1\x5F\x43\x00\x16\x01\x04\x8b\x4c\x19\x14\x08\x00", 0x435FB6);	// line 282, 0x435830 - sub_435830 : movsx   ecx, word ptr [ebx+ecx+2]
		CCodeMover::FixOnAddressRel(0x435FBA, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xBA\x5F\x43\x00\x16\x01\x02\x8b\xc2\x08\x13\x04\xBD\x5F\x03\x00\x00", 0x435FC1);	// line 283, 0x435830 - sub_435830 : movzx   eax, dx
		CCodeMover::FixOnAddressRel(0x435FDB, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xDB\x5F\x43\x00\x16\x01\x04\x8b\x44\x08\x14\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xE0\x5F\x43\x00\x16\x08\x00", 0x435FE3);	// line 284, 0x435830 - sub_435830 : movsx   eax, word ptr [ecx+eax+2]
		CCodeMover::FixOnAddressRel(0x43600B, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x0B\x60\x43\x00\x16\x01\x04\x8b\x4C\x38\x10\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x0F\x60\x43\x00\x16\x08\x00", 0x436012);	// line 285, 0x435830 - sub_435830 : movsx   ecx, word ptr [eax+edi]
		CCodeMover::FixOnAddressRel(0x43603D, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x3D\x60\x43\x00\x16\x01\x04\x8b\x54\x11\x10\x08\x13\x04\x41\x60\x03\x00\x00", 0x436045);	// line 286, 0x435830 - sub_435830 : movsx   edx, word ptr [ecx+edx]
		CCodeMover::FixOnAddressRel(0x436058, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x58\x60\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x39\x7c\x24\xfc\x08\x00", 0x43605F);	// line 287, 0x435830 - sub_435830 : cmp     [esi+3A4h], di
		CCodeMover::FixOnAddressRel(0x436065, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x65\x60\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x6C\x60\x43\x00\x16\x01\x02\x8b\xc1\x08\x00", 0x43606F);	// line 288, 0x435830 - sub_435830 : mov     cx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x436079, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x79\x60\x43\x00\x16\x08\x13\x03\x7C\x60\x03\x00\x00", 0x43607F);	// line 289, 0x435830 - sub_435830 : movzx   ecx, cx
		CCodeMover::FixOnAddressRel(0x436086, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x86\x60\x43\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x43608B);	// line 290, 0x435830 - sub_435830 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x4360A8, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA8\x60\x43\x00\x16\x01\x04\x8b\x4c\x08\x10\x08\x13\x06\xAC\x60\x03\x00\x00", 0x4360B2);	// line 291, 0x435830 - sub_435830 : movsx   ecx, word ptr [eax+ecx]
		CCodeMover::FixOnAddressRel(0x4360CB, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xCB\x60\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x4360D2);	// line 292, 0x435830 - sub_435830 : mov     cx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x4360ED, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xED\x60\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x00", 0x4360F4);	// line 293, 0x435830 - sub_435830 : mov     dx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x4360FB, 17, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xFB\x60\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x02\x61\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x7c\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x09\x61\x43\x00\x16\x01\x02\x8b\xc2\x08\x00", 0x43610C);	// line 294, 0x435830 - sub_435830 : mov     dx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x436120, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x20\x61\x43\x00\x16\x01\x04\x8b\x44\x18\x14\x08\x00", 0x436125);	// line 295, 0x435830 - sub_435830 : movsx   eax, word ptr [ebx+eax+2]
		CCodeMover::FixOnAddressRel(0x436129, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x29\x61\x43\x00\x16\x01\x02\x8b\xcf\x08\x13\x02\x2C\x61\x03\x00\x00", 0x43612E);	// line 296, 0x435830 - sub_435830 : movzx   ecx, di
		CCodeMover::FixOnAddressRel(0x436153, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x53\x61\x43\x00\x16\x01\x04\x8b\x4C\x08\x14\x08\x00", 0x436158);	// line 297, 0x435830 - sub_435830 : movsx   ecx, word ptr [eax+ecx+2]
		CCodeMover::FixOnAddressRel(0x43615A, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x5A\x61\x43\x00\x16\x08\x13\x04\x5D\x61\x03\x00\x00", 0x436161);	// line 298, 0x435830 - sub_435830 : movzx   edx, dx
		CCodeMover::FixOnAddressRel(0x436182, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x82\x61\x43\x00\x16\x08\x13\x03\x85\x61\x03\x00\x00", 0x436188);	// line 299, 0x435830 - sub_435830 : movzx   edi, di
		CCodeMover::FixOnAddressRel(0x43618F, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x8F\x61\x43\x00\x16\x01\x04\x8b\x54\x11\x10\x08\x13\x02\x93\x61\x03\x00\x00", 0x436195);	// line 300, 0x435830 - sub_435830 : movsx   edx, word ptr [ecx+edx]
		CCodeMover::FixOnAddressRel(0x4361B4, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB4\x61\x43\x00\x16\x01\x04\x8b\x54\x39\x10\x08\x13\x04\xB8\x61\x03\x00\x00", 0x4361BC);	// line 301, 0x435830 - sub_435830 : movsx   edx, word ptr [ecx+edi]
		CCodeMover::FixOnAddressRel(0x4361E0, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xE0\x61\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x00", 0x4361E7);	// line 302, 0x435830 - sub_435830 : mov     dx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x4365E4, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xE4\x65\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x4365EB);	// line 303, 0x436540 - sub_436540 : mov     cx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x4365F6, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xF6\x65\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\xF9\x65\x03\x00\x00", 0x4365FB);	// line 304, 0x436540 - sub_436540 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x436625, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x25\x66\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x04\x28\x66\x03\x00\x00", 0x43662C);	// line 305, 0x436540 - sub_436540 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x43664B, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x4B\x66\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x54\x24\xfc\x08\x00", 0x436652);	// line 306, 0x436540 - sub_436540 : mov     dx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x436656, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x56\x66\x43\x00\x16\x01\x02\x8b\xc2\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x59\x66\x43\x00\x16\x08\x00", 0x43665C);	// line 307, 0x436540 - sub_436540 : movzx   eax, dx
		CCodeMover::FixOnAddressRel(0x43669D, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x9D\x66\x43\x00\x16\x01\x02\x8b\xc2\x08\x13\x02\xA0\x66\x03\x00\x00", 0x4366A2);	// line 308, 0x436540 - sub_436540 : movzx   eax, dx
		CCodeMover::FixOnAddressRel(0x4366FE, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xFE\x66\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x436705);	// line 309, 0x436540 - sub_436540 : movzx   ecx, word ptr [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x436773, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x73\x67\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x43677A);	// line 310, 0x436540 - sub_436540 : movzx   ecx, word ptr [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x43679A, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x9A\x67\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x4367A1);	// line 311, 0x436540 - sub_436540 : movzx   ecx, word ptr [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x436835, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x35\x68\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x3C\x68\x43\x00\x16\x01\x02\x8b\xc1\x08\x00", 0x43683F);	// line 312, 0x436540 - sub_436540 : mov     cx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x436853, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x53\x68\x43\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x436858);	// line 313, 0x436540 - sub_436540 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x43685C, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x5C\x68\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x04\x5F\x68\x03\x00\x00", 0x436863);	// line 314, 0x436540 - sub_436540 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x436885, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x85\x68\x43\x00\x16\x01\x04\x8b\x44\x10\x10\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x89\x68\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x436890);	// line 315, 0x436540 - sub_436540 : movsx   eax, word ptr [edx+eax]
		CCodeMover::FixOnAddressRel(0x4368BA, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xBA\x68\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\xBD\x68\x03\x00\x00", 0x4368BF);	// line 316, 0x436540 - sub_436540 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x4368D1, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xD1\x68\x43\x00\x16\x01\x04\x8b\x44\x10\x14\x08\x00", 0x4368D6);	// line 317, 0x436540 - sub_436540 : movsx   eax, word ptr [edx+eax+2]
		CCodeMover::FixOnAddressRel(0x4368DA, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xDA\x68\x43\x00\x16\x01\x02\x8b\xc1\x08\x13\x04\xDD\x68\x03\x00\x00", 0x4368E1);	// line 318, 0x436540 - sub_436540 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x436903, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x03\x69\x43\x00\x16\x01\x04\x8b\x44\x10\x10\x08\x13\x04\x07\x69\x03\x00\x00", 0x43690B);	// line 319, 0x436540 - sub_436540 : movsx   eax, word ptr [edx+eax]
		CCodeMover::FixOnAddressRel(0x436983, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x83\x69\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x43698A);	// line 320, 0x436540 - sub_436540 : mov     cx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x43698D, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x8D\x69\x43\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x3b\x4c\x24\xfc\x08\x00", 0x436994);	// line 321, 0x436540 - sub_436540 : cmp     cx, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x4458C4, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xC4\x58\x44\x00\x16\x01\x04\x8b\x4C\x10\x20\x08\x00", 0x4458C9);	// line 322, 0x4453D0 - sub_4453D0 : movsx   ecx, word ptr [eax+edx+0Ah]
		CCodeMover::FixOnAddressRel(0x4458CB, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xCB\x58\x44\x00\x16\x01\x03\x8b\x50\x1C\x08\x13\x04\xCF\x58\x04\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xD3\x58\x44\x00\x16\x01\x03\x8b\x50\x24\x08\x00", 0x4458D7);	// line 323, 0x4453D0 - sub_4453D0 : movsx   edx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x44D852, 10, "\x01\x02\x81\xfe\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\x5c\xd8\x04\x00\x01\x01\xbe\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44D85C);	// line 324, 0x44D830 - _ZN9CPathFind18FindRegionForCoorsEff : cmp     esi, 7
		CCodeMover::FixOnAddressRel(0x44D87B, 10, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\x85\xd8\x04\x00\x01\x01\xb8\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44D885);	// line 325, 0x44D830 - _ZN9CPathFind18FindRegionForCoorsEff : cmp     eax, 7
		CCodeMover::FixOnAddressRel(0x44D885, 7, "\x01\x02\x69\xc0\x05\x04NUMBER_OF_PATH_FILES_PER_DIMENSION\x0\x01\x02\x01\xf0\x13\x01\x88\xD8\x04\x00\x13\x03\x89\xD8\x04\x00\x00", 0x44D88C);	// line 326, 0x44D830 - _ZN9CPathFind18FindRegionForCoorsEff : lea     eax, [esi+eax*8]
		CCodeMover::FixOnAddressRel(0x44D8AF, 10, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\xb9\xd8\x04\x00\x01\x01\xb8\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44D8B9);	// line 327, 0x44D890 - _ZN9CPathFind19FindXRegionForCoorsEf : cmp     eax, 7
		CCodeMover::FixOnAddressRel(0x44D8DF, 10, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\xe9\xd8\x04\x00\x01\x01\xb8\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44D8E9);	// line 328, 0x44D8C0 - _ZN9CPathFind19FindYRegionForCoorsEf : cmp     eax, 7
		CCodeMover::FixOnAddressRel(0x44D96E, 5, "\x01\x01\xbd\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES\x00\x00", 0x44D973);	// line 329, 0x44D960 - _ZN9CPathFind20SetLinksBridgeLightsEffffb : mov     ebp, 40h ; '@'
		CCodeMover::FixOnAddressRel(0x44D9A6, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA6\xD9\x44\x00\x16\x01\x04\x8b\x44\x31\x10\x08\x13\x02\xAA\xD9\x04\x00\x00", 0x44D9AC);	// line 330, 0x44D960 - _ZN9CPathFind20SetLinksBridgeLightsEffffb : movsx   eax, word ptr [ecx+esi]
		CCodeMover::FixOnAddressRel(0x44D9D0, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xD0\xD9\x44\x00\x16\x01\x03\x8b\x41\x14\x08\x13\x04\xD4\xD9\x04\x00\x00", 0x44D9D8);	// line 331, 0x44D960 - _ZN9CPathFind20SetLinksBridgeLightsEffffb : movsx   eax, word ptr [ecx+2]
		CCodeMover::FixOnAddressRel(0x44DB87, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x15\x94\xdb\x04\x00\x00", 0x44DB8C);	// line 332, 0x44DB60 - _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf : cmp     ecx, 7
		CCodeMover::FixOnAddressRel(0x44DB9E, 10, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\xa8\xdb\x04\x00\x01\x01\xb8\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44DBA8);	// line 333, 0x44DB60 - _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf : cmp     eax, 7
		CCodeMover::FixOnAddressRel(0x44DBCD, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x15\xdb\xdb\x04\x00\x00", 0x44DBD2);	// line 334, 0x44DB60 - _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf : cmp     ecx, 7
		CCodeMover::FixOnAddressRel(0x44DBD4, 5, "\x01\x01\xbf\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44DBD9);	// line 335, 0x44DB60 - _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf : mov     edi, 7
		CCodeMover::FixOnAddressRel(0x44DBE5, 10, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\xef\xdb\x04\x00\x01\x01\xb8\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44DBEF);	// line 336, 0x44DB60 - _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf : cmp     eax, 7
		CCodeMover::FixOnAddressRel(0x44DC14, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x15\x21\xdc\x04\x00\x00", 0x44DC19);	// line 337, 0x44DB60 - _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf : cmp     ecx, 7
		CCodeMover::FixOnAddressRel(0x44DC2B, 10, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\x35\xdc\x04\x00\x01\x01\xb8\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44DC35);	// line 338, 0x44DB60 - _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf : cmp     eax, 7
		CCodeMover::FixOnAddressRel(0x44DC5A, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8D\x15\x68\xdc\x04\x00\x00", 0x44DC5F);	// line 339, 0x44DB60 - _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf : cmp     ecx, 7
		CCodeMover::FixOnAddressRel(0x44DC61, 5, "\x01\x01\xbe\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44DC66);	// line 340, 0x44DB60 - _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf : mov     esi, 7
		CCodeMover::FixOnAddressRel(0x44DC72, 10, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\x7c\xdc\x04\x00\x01\x01\xb8\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44DC7C);	// line 341, 0x44DB60 - _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf : cmp     eax, 7
		CCodeMover::FixOnAddressRel(0x44DCB2, 8, "\x01\x02\x81\xc2\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x13\x01\xB5\xDC\x04\x00\x13\x04\xB6\xDC\x04\x00\x00", 0x44DCBA);	// line 342, 0x44DB60 - _ZN9CPathFind19MarkRegionsForCoorsE7CVectorf : add     edx, 8
		CCodeMover::FixOnAddressRel(0x44DD37, 10, "\x01\x02\x81\xfe\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\x41\xdd\x04\x00\x01\x01\xbe\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44DD41);	// line 343, 0x44DD10 - _ZN9CPathFind21AreNodesLoadedForAreaEffff : cmp     esi, 7
		CCodeMover::FixOnAddressRel(0x44DD62, 10, "\x01\x02\x81\xff\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\x6c\xdd\x04\x00\x01\x01\xbf\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44DD6C);	// line 344, 0x44DD10 - _ZN9CPathFind21AreNodesLoadedForAreaEffff : cmp     edi, 7
		CCodeMover::FixOnAddressRel(0x44DD8B, 10, "\x01\x02\x81\xfb\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\x95\xdd\x04\x00\x01\x01\xbb\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44DD95);	// line 345, 0x44DD10 - _ZN9CPathFind21AreNodesLoadedForAreaEffff : cmp     ebx, 7
		CCodeMover::FixOnAddressRel(0x44DDB4, 10, "\x01\x02\x81\xfa\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\xbe\xdd\x04\x00\x01\x01\xba\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44DDBE);	// line 346, 0x44DD10 - _ZN9CPathFind21AreNodesLoadedForAreaEffff : cmp     edx, 7
		CCodeMover::FixOnAddressRel(0x44DDC8, 10, "\x01\x04\x8b\xc7\x69\xc0\x05\x04NUMBER_OF_PATH_FILES_PER_DIMENSION\x0\x01\x02\x01\xf0\x13\x07\xCB\xDD\x04\x00\x00", 0x44DDD2);	// line 347, 0x44DD10 - _ZN9CPathFind21AreNodesLoadedForAreaEffff : lea     eax, [esi+edi*8]
		CCodeMover::FixOnAddressRel(0x44DDD8, 5, "\x01\x01\x05\x05\x04""SIZE_OF_POINTERS_FOR_ONE_DIMENSION\x00\x13\x02\xDB\xDD\x04\x00\x00", 0x44DDDD);	// line 348, 0x44DD10 - _ZN9CPathFind21AreNodesLoadedForAreaEffff : add     eax, 20h ; ' '
		CCodeMover::FixOnAddressRel(0x44E629, 5, "\x01\x01\xbf\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES\x00\x00", 0x44E62E);	// line 349, 0x44E610 - _ZN9CPathFind20CountFloodFillGroupsEh : mov     edi, 40h ; '@'
		CCodeMover::FixOnAddressRel(0x44E6E2, 5, "\x01\x02\x81\xff\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES\x00\x01\x02\x0F\x8C\x15\xa0\xe6\x04\x00\x00", 0x44E6E7);	// line 350, 0x44E610 - _ZN9CPathFind20CountFloodFillGroupsEh : cmp     edi, 40h ; '@'
		CCodeMover::FixOnAddressRel(0x44E855, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x55\xE8\x44\x00\x16\x01\x03\x8b\x53\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x59\xE8\x44\x00\x16\x01\x03\x8b\x43\x20\x08\x00", 0x44E85D);	// line 351, 0x44E790 - _ZN9CPathFind24GeneratePedCreationCoorsEffffffP7CVectorP12CNodeAddressS3_PfbP7CMatrix : movsx   edx, word ptr [ebx+8]
		CCodeMover::FixOnAddressRel(0x44E923, 8, "\x01\x02\x66\x3d\x05\x02""TOTAL_NUMBER_OF_PATH_INDICES\x00\x13\x04\x27\xE9\x04\x00\x00", 0x44E92B);	// line 352, 0x44E790 - _ZN9CPathFind24GeneratePedCreationCoorsEffffffP7CVectorP12CNodeAddressS3_PfbP7CMatrix : cmp     ax, 64
		CCodeMover::FixOnAddressRel(0x44ED15, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x15\xED\x44\x00\x16\x01\x03\x8b\x57\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x19\xED\x44\x00\x16\x01\x03\x8b\x47\x20\x08\x00", 0x44ED1D);	// line 353, 0x44ECA0 - _ZN9CPathFind33GeneratePedCreationCoors_InteriorEffP7CVectorP12CNodeAddressS3_Pf : movsx   edx, word ptr [edi+8]
		CCodeMover::FixOnAddressRel(0x44ED74, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x74\xED\x44\x00\x16\x01\x03\x8b\x4f\x24\x08\x13\x04\x78\xED\x04\x00\x00", 0x44ED7C);	// line 354, 0x44ECA0 - _ZN9CPathFind33GeneratePedCreationCoors_InteriorEffP7CVectorP12CNodeAddressS3_Pf : movsx   ecx, word ptr [edi+0Ch]
		CCodeMover::FixOnAddressRel(0x44EDD0, 8, "\x01\x02\x66\x3d\x05\x02""TOTAL_NUMBER_OF_PATH_INDICES\x00\x13\x04\xD4\xED\x04\x00\x00", 0x44EDD8);	// line 355, 0x44ECA0 - _ZN9CPathFind33GeneratePedCreationCoors_InteriorEffP7CVectorP12CNodeAddressS3_Pf : cmp     ax, 64
		CCodeMover::FixOnAddressRel(0x44EE27, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x27\xEE\x44\x00\x16\x01\x03\x8b\x4e\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x2B\xEE\x44\x00\x16\x01\x03\x8b\x56\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x2F\xEE\x44\x00\x16\x01\x03\x8b\x46\x24\x08\x00", 0x44EE33);	// line 356, 0x44ECA0 - _ZN9CPathFind33GeneratePedCreationCoors_InteriorEffP7CVectorP12CNodeAddressS3_Pf : movsx   ecx, word ptr [esi+8]
		CCodeMover::FixOnAddressRel(0x44EE37, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x37\xEE\x44\x00\x16\x01\x03\x8b\x4f\x1C\x08\x13\x04\x3B\xEE\x04\x00\x00", 0x44EE3F);	// line 357, 0x44ECA0 - _ZN9CPathFind33GeneratePedCreationCoors_InteriorEffP7CVectorP12CNodeAddressS3_Pf : movsx   ecx, word ptr [edi+8]
		CCodeMover::FixOnAddressRel(0x44EE43, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x43\xEE\x44\x00\x16\x01\x03\x8b\x57\x20\x08\x13\x06\x47\xEE\x04\x00\x00", 0x44EE4D);	// line 358, 0x44ECA0 - _ZN9CPathFind33GeneratePedCreationCoors_InteriorEffP7CVectorP12CNodeAddressS3_Pf : movsx   edx, word ptr [edi+0Ah]
		CCodeMover::FixOnAddressRel(0x44EE55, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x55\xEE\x44\x00\x16\x01\x03\x8b\x47\x24\x08\x13\x06\x59\xEE\x04\x00\x00", 0x44EE5F);	// line 359, 0x44ECA0 - _ZN9CPathFind33GeneratePedCreationCoors_InteriorEffP7CVectorP12CNodeAddressS3_Pf : movsx   eax, word ptr [edi+0Ch]
		CCodeMover::FixOnAddressRel(0x44F004, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x04\xF0\x44\x00\x16\x01\x03\x8b\x46\x12\x08\x13\x04\x08\xF0\x04\x00\x00", 0x44F00C);	// line 360, 0x44EFC0 - _ZN9CPathFind15CalcRoadDensityEff : movsx   eax, word ptr [esi-2]
		CCodeMover::FixOnAddressRel(0x44F031, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x31\xF0\x44\x00\x16\x01\x03\x8b\x56\x16\x08\x13\x04\x34\xF0\x04\x00\x00", 0x44F038);	// line 361, 0x44EFC0 - _ZN9CPathFind15CalcRoadDensityEff : movsx   edx, word ptr [esi]
		CCodeMover::FixOnAddressRel(0x44F0AE, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xAE\xF0\x44\x00\x16\x01\x03\x8b\x50\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB2\xF0\x44\x00\x16\x01\x03\x8b\x40\x20\x08\x00", 0x44F0B6);	// line 362, 0x44EFC0 - _ZN9CPathFind15CalcRoadDensityEff : movsx   edx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x44F0C8, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xC8\xF0\x44\x00\x16\x01\x03\x8b\04\x32\x08\x13\x06\xCC\xF0\x04\x00\x00", 0x44F0D2);	// line 363, 0x44EFC0 - _ZN9CPathFind15CalcRoadDensityEff : movzx   eax, word ptr [esi+edx]
		CCodeMover::FixOnAddressRel(0x44F1E2, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xE2\xF1\x44\x00\x16\x01\x03\x8b\x4e\x1C\x08\x13\x03\xE6\xF1\x04\x00\x00", 0x44F1E9);	// line 364, 0x44F190 - _ZN9CPathFind28CalcDistToAnyConnectingLinksEP9CPathNode7CVector : movsx   ecx, word ptr [esi+8]
		CCodeMover::FixOnAddressRel(0x44F1F0, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xF0\xF1\x44\x00\x16\x01\x03\x8b\x4e\x24\x08\x13\x04\xF4\xF1\x04\x00\x00", 0x44F1F8);	// line 365, 0x44F190 - _ZN9CPathFind28CalcDistToAnyConnectingLinksEP9CPathNode7CVector : movsx   ecx, word ptr [esi+0Ch]
		CCodeMover::FixOnAddressRel(0x44F200, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x00\xF2\x44\x00\x16\x01\x03\x8b\x56\x20\x08\x13\x04\x04\xF2\x04\x00\x00", 0x44F208);	// line 366, 0x44F190 - _ZN9CPathFind28CalcDistToAnyConnectingLinksEP9CPathNode7CVector : movsx   edx, word ptr [esi+0Ah]
		CCodeMover::FixOnAddressRel(0x44F22C, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x2C\xF2\x44\x00\x16\x01\x03\x8b\x50\x24\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x30\xF2\x44\x00\x16\x01\x03\x8b\x48\x20\x08\x00", 0x44F234);	// line 367, 0x44F190 - _ZN9CPathFind28CalcDistToAnyConnectingLinksEP9CPathNode7CVector : movsx   edx, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x44F238, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x38\xF2\x44\x00\x16\x01\x03\x8b\x50\x1C\x08\x13\x04\x3C\xF2\x04\x00\x00", 0x44F240);	// line 368, 0x44F190 - _ZN9CPathFind28CalcDistToAnyConnectingLinksEP9CPathNode7CVector : movsx   edx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x44F36F, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x6F\xF3\x44\x00\x16\x01\x03\x8b\x51\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x73\xF3\x44\x00\x16\x01\x03\x8b\x41\x20\x08\x00", 0x44F377);	// line 369, 0x44F2C9 - sub_44F2C9 : movsx   edx, word ptr [ecx+8]
		CCodeMover::FixOnAddressRel(0x44F37B, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x7B\xF3\x44\x00\x16\x01\x03\x8b\x51\x24\x08\x13\x04\x7F\xF3\x04\x00\x00", 0x44F383);	// line 370, 0x44F2C9 - sub_44F2C9 : movsx   edx, word ptr [ecx+0Ch]
		CCodeMover::FixOnAddressRel(0x44F496, 5, "\x01\x01\xbf\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x44F49B);	// line 371, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : mov     edi, 7
		CCodeMover::FixOnAddressRel(0x44F4DF, 8, "\x01\x04\x8b\xca\x69\xc9\x05\x04NUMBER_OF_PATH_FILES_PER_DIMENSION\x0\x01\x02\x01\xf1\x13\x01\xE2\xF4\x04\x00\x13\x04\xE3\xF4\x04\x00\x00", 0x44F4E7);	// line 372, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : lea     ecx, [esi+edx*8]
		CCodeMover::FixOnAddressRel(0x44F607, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x01\x02\x0F\x8D\x15\x80\xf6\x04\x00\x00", 0x44F60C);	// line 373, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : cmp     eax, 8
		CCodeMover::FixOnAddressRel(0x44F62C, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x01\x02\x0F\x8D\x15\x77\xf6\x04\x00\x00", 0x44F631);	// line 374, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : cmp     ecx, 8
		CCodeMover::FixOnAddressRel(0x44F65D, 8, "\x01\x02\x69\xc9\x05\x04NUMBER_OF_PATH_FILES_PER_DIMENSION\x0\x01\x02\x01\xc1\x13\x01\x60\xF6\x04\x00\x13\x04\x61\xF6\x04\x00\x00", 0x44F665);	// line 375, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : lea     ecx, [eax+ecx*8]
		CCodeMover::FixOnAddressRel(0x44F688, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x01\x02\x0F\x8D\x15\xfc\xf6\x04\x00\x00", 0x44F68D);	// line 376, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : cmp     ecx, 8
		CCodeMover::FixOnAddressRel(0x44F6A9, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x01\x02\x0F\x8D\x15\xf3\xf6\x04\x00\x00", 0x44F6AE);	// line 377, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : cmp     eax, 8
		CCodeMover::FixOnAddressRel(0x44F6D9, 7, "\x01\x04\x8b\xd0\x69\xd2\x05\x04NUMBER_OF_PATH_FILES_PER_DIMENSION\x0\x01\x02\x01\xca\x13\x04\xDC\xF6\x04\x00\x00", 0x44F6E0);	// line 378, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : lea     edx, [ecx+eax*8]
		CCodeMover::FixOnAddressRel(0x44F704, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x01\x02\x0F\x8D\x15\x79\xf7\x04\x00\x00", 0x44F709);	// line 379, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : cmp     eax, 8
		CCodeMover::FixOnAddressRel(0x44F724, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x01\x02\x0F\x8D\x15\x6a\xf7\x04\x00\x00", 0x44F729);	// line 380, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : cmp     eax, 8
		CCodeMover::FixOnAddressRel(0x44F754, 7, "\x01\x04\x8b\xd1\x69\xd2\x05\x04NUMBER_OF_PATH_FILES_PER_DIMENSION\x0\x01\x02\x01\xc2\x13\x04\x57\xF7\x04\x00\x00", 0x44F75B);	// line 381, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : lea     edx, [eax+ecx*8]
		CCodeMover::FixOnAddressRel(0x44F78F, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x01\x02\x0F\x8D\x15\xfb\xf7\x04\x00\x00", 0x44F794);	// line 382, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : cmp     eax, 8
		CCodeMover::FixOnAddressRel(0x44F7A4, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x01\x02\x0F\x8D\x15\xea\xf7\x04\x00\x00", 0x44F7A9);	// line 383, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : cmp     eax, 8
		CCodeMover::FixOnAddressRel(0x44F7D4, 7, "\x01\x04\x8b\xd1\x69\xd2\x05\x04NUMBER_OF_PATH_FILES_PER_DIMENSION\x0\x01\x02\x01\xc2\x13\x04\xD7\xF7\x04\x00\x00", 0x44F7DB);	// line 384, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : lea     edx, [eax+ecx*8]
		CCodeMover::FixOnAddressRel(0x44F88C, 8, "\x01\x02\x66\x3d\x05\x02""TOTAL_NUMBER_OF_PATH_INDICES_WITH_INTERIOR_SLOTS\x00\x13\x04\x90\xF8\x04\x00\x00", 0x44F894);	// line 385, 0x44F460 - _ZN9CPathFind22FindNodeClosestToCoorsE7CVectorhfbbbbb : cmp     ax, 72
		CCodeMover::FixOnAddressRel(0x44FC1A, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x1A\xFC\x44\x00\x16\x01\x03\x8b\x58\x1C\x08\x13\x04\x1E\xFC\x04\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x22\xFC\x44\x00\x16\x01\x03\x8b\x58\x20\x08\x00", 0x44FC26);	// line 386, 0x44FB60 - _ZN9CPathFind19RecordNodesInCircleERK7CVectorfhiP12CNodeAddressbbbbb : movsx   ebx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x44FC2A, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x2A\xFC\x44\x00\x16\x01\x03\x8b\x40\x24\x08\x13\x06\x2E\xFC\x04\x00\x00", 0x44FC34);	// line 387, 0x44FB60 - _ZN9CPathFind19RecordNodesInCircleERK7CVectorfhiP12CNodeAddressbbbbb : movsx   eax, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x44FCC4, 7, "\x01\x01\x3d\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES_WITH_INTERIOR_SLOTS\x00\x13\x04\xC7\xFC\x04\x00\x00", 0x44FCCB);	// line 388, 0x44FB60 - _ZN9CPathFind19RecordNodesInCircleERK7CVectorfhiP12CNodeAddressbbbbb : cmp     eax, 48h ; 'H'
		CCodeMover::FixOnAddressRel(0x44FDA0, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xA0\xFD\x44\x00\x16\x01\x03\x8b\x42\x14\x08\x13\x04\xA3\xFD\x04\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA7\xFD\x44\x00\x16\x01\x03\x8b\x42\x18\x08\x00", 0x44FDAB);	// line 389, 0x44FCE0 - _ZN9CPathFind37FindNodeClosestToCoorsFavourDirectionE7CVectorhff : movsx   eax, word ptr [edx]
		CCodeMover::FixOnAddressRel(0x44FDB3, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB3\xFD\x44\x00\x16\x01\x03\x8b\x42\x1C\x08\x13\x06\xB7\xFD\x04\x00\x00", 0x44FDBD);	// line 390, 0x44FCE0 - _ZN9CPathFind37FindNodeClosestToCoorsFavourDirectionE7CVectorhff : movsx   eax, word ptr [edx+4]
		CCodeMover::FixOnAddressRel(0x44FEB4, 9, "\x01\x02\x81\xfb\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES_WITH_INTERIOR_SLOTS\x00\x01\x02\x0F\x8C\x15\x60\xfd\x04\x00\x00", 0x44FEBD);	// line 391, 0x44FCE0 - _ZN9CPathFind37FindNodeClosestToCoorsFavourDirectionE7CVectorhff : cmp     ebx, 48h ; 'H'
		CCodeMover::FixOnAddressRel(0x44FFA5, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA5\xFF\x44\x00\x16\x01\x03\x8b\x43\x12\x08\x13\x04\xA9\xFF\x04\x00\x00", 0x44FFAD);	// line 392, 0x44FEE0 - _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb : movsx   eax, word ptr [ebx-2]
		CCodeMover::FixOnAddressRel(0x44FFC3, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xC3\xFF\x44\x00\x16\x01\x03\x8b\x43\x16\x08\x13\x04\xC6\xFF\x04\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xCA\xFF\x44\x00\x16\x01\x03\x8b\x43\x1A\x08\x00", 0x44FFCE);	// line 393, 0x44FEE0 - _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb : movsx   eax, word ptr [ebx]
		CCodeMover::FixOnAddressRel(0x450099, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x99\x00\x45\x00\x16\x01\x03\x8b\x50\x1C\x08\x13\x04\x9D\x00\x05\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA1\x00\x45\x00\x16\x01\x03\x8b\x50\x20\x08\x00", 0x4500A5);	// line 394, 0x44FEE0 - _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb : movsx   edx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x4500A9, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA9\x00\x45\x00\x16\x01\x03\x8b\x40\x24\x08\x13\x06\xAD\x00\x05\x00\x00", 0x4500B3);	// line 395, 0x44FEE0 - _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb : movsx   eax, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x450175, 7, "\x01\x01\x3d\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES_WITH_INTERIOR_SLOTS\x00\x13\x04\x78\x01\x05\x00\x00", 0x45017C);	// line 396, 0x44FEE0 - _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb : cmp     eax, 48h ; 'H'
		CCodeMover::FixOnAddressRel(0x4501D8, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xD8\x01\x45\x00\x16\x01\x04\x8b\x4c\x32\x1C\x08\x00", 0x4501DD);	// line 397, 0x44FEE0 - _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb : movsx   ecx, word ptr [edx+esi+8]
		CCodeMover::FixOnAddressRel(0x4501E6, 15, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xE6\x01\x45\x00\x16\x01\x03\x8b\x4a\x20\x08\x13\x07\xEA\x01\x05\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xF1\x01\x45\x00\x16\x01\x03\x8b\x52\x24\x08\x00", 0x4501F5);	// line 398, 0x44FEE0 - _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb : movsx   ecx, word ptr [edx+0Ah]
		CCodeMover::FixOnAddressRel(0x450202, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x02\x02\x45\x00\x16\x01\x04\x8b\x4c\x18\x1C\x08\x00", 0x450207);	// line 399, 0x44FEE0 - _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb : movsx   ecx, word ptr [eax+ebx+8]
		CCodeMover::FixOnAddressRel(0x450215, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x15\x02\x45\x00\x16\x01\x04\x8b\x54\x18\x20\x08\x00", 0x45021A);	// line 400, 0x44FEE0 - _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb : movsx   edx, word ptr [eax+ebx+0Ah]
		CCodeMover::FixOnAddressRel(0x45025F, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x5F\x02\x45\x00\x16\x01\x03\x8b\x40\x24\x08\x13\x07\x63\x02\x05\x00\x00", 0x45026A);	// line 401, 0x44FEE0 - _ZN9CPathFind26FindNodePairClosestToCoorsE7CVectorhP12CNodeAddressS2_Pfffbbb : movsx   eax, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x4503FF, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xFF\x03\x45\x00\x16\x01\x03\x8b\x56\x20\x08\x13\x03\x03\x04\x05\x00\x00", 0x450406);	// line 402, 0x450320 - _ZN9CPathFind34FindNodeOrientationForCarPlacementE12CNodeAddress : movsx   edx, word ptr [esi+0Ah]
		CCodeMover::FixOnAddressRel(0x45040B, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x0B\x04\x45\x00\x16\x01\x03\x8b\x4e\x1C\x08\x13\x04\x0F\x04\x05\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x13\x04\x45\x00\x16\x01\x03\x8b\x4e\x24\x08\x00", 0x450417);	// line 403, 0x450320 - _ZN9CPathFind34FindNodeOrientationForCarPlacementE12CNodeAddress : movsx   ecx, word ptr [esi+8]
		CCodeMover::FixOnAddressRel(0x450425, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x25\x04\x45\x00\x16\x01\x03\x8b\x50\x1C\x08\x13\x04\x29\x04\x05\x00\x00", 0x45042D);	// line 404, 0x450320 - _ZN9CPathFind34FindNodeOrientationForCarPlacementE12CNodeAddress : movsx   edx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x450437, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x37\x04\x45\x00\x16\x01\x03\x8b\x48\x20\x08\x13\x04\x3B\x04\x05\x00\x00", 0x45043F);	// line 405, 0x450320 - _ZN9CPathFind34FindNodeOrientationForCarPlacementE12CNodeAddress : movsx   ecx, word ptr [eax+0Ah]
		CCodeMover::FixOnAddressRel(0x450469, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x69\x04\x45\x00\x16\x01\x03\x8b\x50\x24\x08\x13\x04\x6D\x04\x05\x00\x00", 0x450471);	// line 406, 0x450320 - _ZN9CPathFind34FindNodeOrientationForCarPlacementE12CNodeAddress : movsx   edx, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x450BE5, 10, "\x01\x02\x81\xfd\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\xef\x0b\x05\x00\x01\x01\xbd\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x450BEF);	// line 407, 0x450A60 - _ZN9CPathFind15UpdateStreamingEb : cmp     ebp, 7
		CCodeMover::FixOnAddressRel(0x450C12, 7, "\x01\x02\x81\xff\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x13\x04\x15\x0C\x05\x00\x00", 0x450C19);	// line 408, 0x450A60 - _ZN9CPathFind15UpdateStreamingEb : cmp     edi, 7
		CCodeMover::FixOnAddressRel(0x450C1B, 5, "\x01\x01\xbf\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x450C20);	// line 409, 0x450A60 - _ZN9CPathFind15UpdateStreamingEb : mov     edi, 7
		CCodeMover::FixOnAddressRel(0x450C47, 10, "\x01\x02\x81\xfe\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x01\x02\x0F\x8C\x15\x51\x0c\x05\x00\x01\x01\xbe\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x450C51);	// line 410, 0x450A60 - _ZN9CPathFind15UpdateStreamingEb : cmp     esi, 7
		CCodeMover::FixOnAddressRel(0x450C72, 7, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x13\x04\x75\x0C\x05\x00\x00", 0x450C79);	// line 411, 0x450A60 - _ZN9CPathFind15UpdateStreamingEb : cmp     eax, 7
		CCodeMover::FixOnAddressRel(0x450C7B, 5, "\x01\x01\xb8\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x450C80);	// line 412, 0x450A60 - _ZN9CPathFind15UpdateStreamingEb : mov     eax, 7
		CCodeMover::FixOnAddressRel(0x450D44, 9, "\x01\x02\x81\xc3\x05\x04""SIZE_OF_POINTERS_FOR_ONE_DIMENSION\x00\x01\x02\x81\xc7\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x01\x02\x81\xfe\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x00", 0x450D4D);	// line 413, 0x450A60 - _ZN9CPathFind15UpdateStreamingEb : add     ebx, 20h ; ' '
		CCodeMover::FixOnAddressRel(0x450D57, 7, "\x01\x02\x81\xfd\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x13\x04\x5A\x0D\x05\x00\x00", 0x450D5E);	// line 414, 0x450A60 - _ZN9CPathFind15UpdateStreamingEb : cmp     ebp, 8
		CCodeMover::FixOnAddressRel(0x450E0B, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x0B\x0E\x45\x00\x16\x01\x03\x8b\x41\x10\x08\x13\x04\x0E\x0E\x05\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x12\x0E\x45\x00\x16\x01\x03\x8b\x41\x14\x08\x00", 0x450E16);	// line 415, 0x450DE0 - _ZN9CPathFind17IsWaterNodeNearbyE7CVectorf : movsx   eax, word ptr [ecx]
		CCodeMover::FixOnAddressRel(0x450E69, 5, "\x01\x02\x81\xfd\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES\x00\x01\x02\x0F\x8C\x15\xf1\x0d\x05\x00\x00", 0x450E6E);	// line 416, 0x450DE0 - _ZN9CPathFind17IsWaterNodeNearbyE7CVectorf : cmp     ebp, 40h ; '@'
		CCodeMover::FixOnAddressRel(0x450F07, 8, "\x01\x01\x05\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES\x00\x13\x05\x0A\x0F\x05\x00\x00", 0x450F0F);	// line 417, 0x450E90 - _ZN9CPathFind20AddNodeToNewInteriorEfffbaaaaaa : add     eax, 40h ; '@'
		CCodeMover::FixOnAddressRel(0x450FEB, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xEB\x0F\x45\x00\x16\x01\x04\x8b\x54\x08\x1C\x08\x00", 0x450FF0);	// line 418, 0x450FB0 - sub_450FB0 : movsx   edx, word ptr [ecx+eax+8]
		CCodeMover::FixOnAddressRel(0x450FF4, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xF4\x0F\x45\x00\x16\x01\x03\x8b\x46\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xF8\x0F\x45\x00\x16\x01\x03\x8b\x4e\x24\x08\x00", 0x450FFC);	// line 419, 0x450FB0 - sub_450FB0 : movsx   eax, word ptr [esi+0Ah]
		CCodeMover::FixOnAddressRel(0x451039, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x39\x10\x45\x00\x16\x01\x03\x8b\x4f\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x3D\x10\x45\x00\x16\x01\x03\x8b\x57\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x41\x10\x45\x00\x16\x01\x03\x8b\x47\x24\x08\x00", 0x451045);	// line 420, 0x450FB0 - sub_450FB0 : movsx   ecx, word ptr [edi+8]
		CCodeMover::FixOnAddressRel(0x4510C1, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xC1\x10\x45\x00\x16\x01\x03\x8b\x4e\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xC5\x10\x45\x00\x16\x01\x03\x8b\x56\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xC9\x10\x45\x00\x16\x01\x03\x8b\x46\x24\x08\x00", 0x4510CD);	// line 421, 0x450FB0 - sub_450FB0 : movsx   ecx, word ptr [esi+8]
		CCodeMover::FixOnAddressRel(0x4510FB, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xFB\x10\x45\x00\x16\x01\x03\x8b\x4f\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xFF\x10\x45\x00\x16\x01\x03\x8b\x57\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x03\x11\x45\x00\x16\x01\x03\x8b\x47\x24\x08\x00", 0x451107);	// line 422, 0x450FB0 - sub_450FB0 : movsx   ecx, word ptr [edi+8]
		CCodeMover::FixOnAddressRel(0x45117E, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x7E\x11\x45\x00\x16\x01\x03\x8b\x4e\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x82\x11\x45\x00\x16\x01\x03\x8b\x56\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x86\x11\x45\x00\x16\x01\x03\x8b\x46\x24\x08\x00", 0x45118A);	// line 423, 0x450FB0 - sub_450FB0 : movsx   ecx, word ptr [esi+8]
		CCodeMover::FixOnAddressRel(0x4511B8, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB8\x11\x45\x00\x16\x01\x03\x8b\x4f\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xBC\x11\x45\x00\x16\x01\x03\x8b\x57\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xC0\x11\x45\x00\x16\x01\x03\x8b\x47\x24\x08\x00", 0x4511C4);	// line 424, 0x450FB0 - sub_450FB0 : movsx   ecx, word ptr [edi+8]
		CCodeMover::FixOnAddressRel(0x451318, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_INTERIOR_SLOTS\x00\x01\x02\x0F\x8C\x15\x10\x13\x05\x00\x00", 0x45131D);	// line 425, 0x451300 - _ZN9CPathFind23ReturnInteriorNodeIndexEji : cmp     eax, 8
		CCodeMover::FixOnAddressRel(0x451331, 8, "\x01\x01\x05\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES\x00\x13\x05\x34\x13\x05\x00\x00", 0x451339);	// line 426, 0x451300 - _ZN9CPathFind23ReturnInteriorNodeIndexEji : add     eax, 40h ; '@'
		CCodeMover::FixOnAddressRel(0x451440, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x40\x14\x45\x00\x16\x01\x03\x8b\x46\x1C\x08\x13\x04\x44\x14\x05\x00\x00", 0x451448);	// line 427, 0x4513F0 - _ZN9CPathFind21FindParkingNodeInAreaEffffff : movsx   eax, word ptr [esi+8]
		CCodeMover::FixOnAddressRel(0x451470, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x70\x14\x45\x00\x16\x01\x03\x8b\x4e\x20\x08\x13\x04\x74\x14\x05\x00\x00", 0x451478);	// line 428, 0x4513F0 - _ZN9CPathFind21FindParkingNodeInAreaEffffff : movsx   ecx, word ptr [esi+0Ah]
		CCodeMover::FixOnAddressRel(0x4514A0, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA0\x14\x45\x00\x16\x01\x03\x8b\x46\x24\x08\x13\x04\xA4\x14\x05\x00\x00", 0x4514A8);	// line 429, 0x4513F0 - _ZN9CPathFind21FindParkingNodeInAreaEffffff : movsx   eax, word ptr [esi+0Ch]
		CCodeMover::FixOnAddressRel(0x45181D, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x1D\x18\x45\x00\x16\x01\x03\x8b\x0c\x91\x08\x13\x02\x21\x18\x05\x00\x00", 0x451823);	// line 430, 0x4515D0 - _ZN9CPathFind12DoPathSearchEh7CVector12CNodeAddressS0_PS1_PsiPffS2_fbS1_bb : movzx   ecx, word ptr [ecx+edx*2]
		CCodeMover::FixOnAddressRel(0x451D83, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x83\x1D\x45\x00\x16\x01\x03\x8b\x50\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x87\x1D\x45\x00\x16\x01\x03\x8b\x40\x20\x08\x00", 0x451D8B);	// line 431, 0x451B70 - _ZN9CPathFind21FindNextNodeWanderingEh7CVectorP12CNodeAddressS2_hPh : movsx   edx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x451D8F, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x8F\x1D\x45\x00\x16\x01\x03\x8b\x51\x1C\x08\x13\x04\x93\x1D\x05\x00\x00", 0x451D97);	// line 432, 0x451B70 - _ZN9CPathFind21FindNextNodeWanderingEh7CVectorP12CNodeAddressS2_hPh : movsx   edx, word ptr [ecx+8]
		CCodeMover::FixOnAddressRel(0x451DA1, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA1\x1D\x45\x00\x16\x01\x03\x8b\x51\x20\x08\x13\x04\xA5\x1D\x05\x00\x00", 0x451DA9);	// line 433, 0x451B70 - _ZN9CPathFind21FindNextNodeWanderingEh7CVectorP12CNodeAddressS2_hPh : movsx   edx, word ptr [ecx+0Ah]
		CCodeMover::FixOnAddressRel(0x452344, 9, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x44\x23\x45\x00\x16\x01\x03\x89\x43\x1C\x08\x01\x01\xE8\x15\x40\x1b\x42\x00\x00", 0x45234D);	// line 434, 0x452270 - _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress : mov     [ebx+8], ax
		CCodeMover::FixOnAddressRel(0x452353, 13, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x53\x23\x45\x00\x16\x01\x03\x89\x43\x20\x08\x01\x01\xE8\x15\x40\x1b\x42\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x5C\x23\x45\x00\x16\x01\x03\x89\x43\x24\x08\x00", 0x452360);	// line 435, 0x452270 - _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress : mov     [ebx+0Ah], ax
		CCodeMover::FixOnAddressRel(0x452376, 6, "\x01\x02\x81\xc1\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES\x00\x13\x03\x79\x23\x05\x00\x00", 0x45237C);	// line 436, 0x452270 - _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress : add     ecx, 40h ; '@'
		CCodeMover::FixOnAddressRel(0x452715, 8, "\x01\x02\x81\xc1\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES\x00\x13\x05\x18\x27\x05\x00\x00", 0x45271D);	// line 437, 0x452270 - _ZN9CPathFind19CompleteNewInteriorEP12CNodeAddress : add     ecx, 40h ; '@'
		CCodeMover::FixOnAddressRel(0x452887, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x87\x28\x45\x00\x16\x01\x04\x8b\x44\x35\x1C\x08\x00", 0x45288C);	// line 438, 0x452820 - _ZN9CPathFind32SwitchRoadsOffInAreaForOneRegionEffffffbbib : movsx   eax, word ptr [esi+ebp+8]
		CCodeMover::FixOnAddressRel(0x4528BA, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xBA\x28\x45\x00\x16\x01\x03\x8b\x4e\x20\x08\x13\x04\xBE\x28\x05\x00\x00", 0x4528C2);	// line 439, 0x452820 - _ZN9CPathFind32SwitchRoadsOffInAreaForOneRegionEffffffbbib : movsx   ecx, word ptr [esi+0Ah]
		CCodeMover::FixOnAddressRel(0x452CC1, 5, "\x01\x02\x81\xfe\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES\x00\x01\x02\x0F\x8C\x15\x93\x2c\x05\x00\x00", 0x452CC6);	// line 440, 0x452C80 - _ZN9CPathFind20SwitchRoadsOffInAreaEffffffbbb : cmp     esi, 40h ; '@'
		CCodeMover::FixOnAddressRel(0x452D93, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE\x00\x00", 0x452D98);	// line 441, 0x452C80 - _ZN9CPathFind20SwitchRoadsOffInAreaEffffffbbb : mov     ecx, 7
		CCodeMover::FixOnAddressRel(0x452E3F, 9, "\x01\x01\x3d\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES\x00\x01\x02\x0F\x8D\x15\xea\x2e\x05\x00\x00", 0x452E48);	// line 442, 0x452C80 - _ZN9CPathFind20SwitchRoadsOffInAreaEffffffbbb : cmp     eax, 40h ; '@'
		CCodeMover::FixOnAddressRel(0x460F07, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x07\x0F\x46\x00\x16\x01\x02\x8b\x08\x08\x13\x01\x0A\x0F\x06\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x0B\x0F\x46\x00\x16\x01\x03\x8b\x70\x04\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x0F\x0F\x46\x00\x16\x01\x02\x8b\xc1\x08\x00", 0x460F12);	// line 443, 0x460EE0 - sub_460EE0 : mov     cx, [eax]
		CCodeMover::FixOnAddressRel(0x460F29, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x29\x0F\x46\x00\x16\x01\x02\x8b\xce\x08\x13\x02\x2C\x0F\x06\x00\x00", 0x460F2E);	// line 444, 0x460EE0 - sub_460EE0 : movzx   ecx, si
		CCodeMover::FixOnAddressRel(0x460FA7, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xA7\x0F\x46\x00\x16\x01\x03\x8b\x51\x10\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xAA\x0F\x46\x00\x16\x01\x03\x8b\x49\x14\x08\x00", 0x460FAE);	// line 445, 0x460EE0 - sub_460EE0 : movsx   edx, word ptr [ecx]
		CCodeMover::FixOnAddressRel(0x460FB2, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xB2\x0F\x46\x00\x16\x01\x03\x8b\x50\x10\x08\x13\x04\xB5\x0F\x06\x00\x00", 0x460FB9);	// line 446, 0x460EE0 - sub_460EE0 : movsx   edx, word ptr [eax]
		CCodeMover::FixOnAddressRel(0x460FC3, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xC3\x0F\x46\x00\x16\x01\x03\x8b\x50\x14\x08\x13\x04\xC7\x0F\x06\x00\x00", 0x460FCB);	// line 447, 0x460EE0 - sub_460EE0 : movsx   edx, word ptr [eax+2]
		CCodeMover::FixOnAddressRel(0x462AE2, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xE2\x2A\x46\x00\x16\x01\x04\x8b\x4c\x30\x1C\x08\x00", 0x462AE7);	// line 448, 0x4629E0 - sub_4629E0 : movsx   ecx, word ptr [esi+eax+8]
		CCodeMover::FixOnAddressRel(0x462B43, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x43\x2B\x46\x00\x16\x01\x03\x8b\x46\x20\x08\x13\x04\x47\x2B\x06\x00\x00", 0x462B4B);	// line 449, 0x4629E0 - sub_4629E0 : movsx   eax, word ptr [esi+0Ah]
		CCodeMover::FixOnAddressRel(0x49D446, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x46\xD4\x49\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x44\x24\xfc\x08\x00", 0x49D44D);	// line 450, 0x49D420 - sub_49D420 : mov     ax, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x49D453, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x53\xD4\x49\x00\x16\x01\x02\x8b\xc8\x08\x13\x03\x56\xD4\x09\x00\x00", 0x49D459);	// line 451, 0x49D420 - sub_49D420 : movzx   ecx, ax
		CCodeMover::FixOnAddressRel(0x49D464, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x64\xD4\x49\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x49D46B);	// line 452, 0x49D420 - sub_49D420 : mov     cx, [esi+3A4h]
		CCodeMover::FixOnAddressRel(0x49D472, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x72\xD4\x49\x00\x16\x01\x02\x8b\xd1\x08\x13\x03\x75\xD4\x09\x00\x00", 0x49D478);	// line 453, 0x49D420 - sub_49D420 : movzx   edx, cx
		CCodeMover::FixOnAddressRel(0x49D483, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x83\xD4\x49\x00\x16\x08\x13\x02\x86\xD4\x09\x00\x00", 0x49D488);	// line 454, 0x49D420 - sub_49D420 : movzx   eax, ax
		CCodeMover::FixOnAddressRel(0x49D4A4, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xA4\xD4\x49\x00\x16\x01\x02\x8b\xc1\x08\x13\x02\xA7\xD4\x09\x00\x00", 0x49D4A9);	// line 455, 0x49D420 - sub_49D420 : movzx   eax, cx
		CCodeMover::FixOnAddressRel(0x49D64B, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x4B\xD6\x49\x00\x16\x01\x02\x8b\xc8\x08\x13\x03\x4E\xD6\x09\x00\x00", 0x49D651);	// line 456, 0x49D610 - sub_49D610 : movzx   ecx, ax
		CCodeMover::FixOnAddressRel(0x49D660, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x60\xD6\x49\x00\x16\x08\x13\x02\x63\xD6\x09\x00\x00", 0x49D665);	// line 457, 0x49D610 - sub_49D610 : movzx   eax, ax
		CCodeMover::FixOnAddressRel(0x49D70D, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x0D\xD7\x49\x00\x16\x01\x03\x8b\x57\x14\x08\x13\x04\x11\xD7\x09\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x15\xD7\x49\x00\x16\x01\x03\x8b\x57\x10\x08\x00", 0x49D718);	// line 458, 0x49D610 - sub_49D610 : movsx   edx, word ptr [edi+2]
		CCodeMover::FixOnAddressRel(0x49D7B0, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xB0\xD7\x49\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x44\x24\xfc\x08\x00", 0x49D7B7);	// line 459, 0x49D610 - sub_49D610 : mov     ax, [esi+3A6h]
		CCodeMover::FixOnAddressRel(0x49D7C1, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xC1\xD7\x49\x00\x16\x01\x02\x8b\xc8\x08\x13\x03\xC4\xD7\x09\x00\x00", 0x49D7C7);	// line 460, 0x49D610 - sub_49D610 : movzx   ecx, ax
		CCodeMover::FixOnAddressRel(0x49D7D6, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xD6\xD7\x49\x00\x16\x08\x13\x02\xD9\xD7\x09\x00\x00", 0x49D7DB);	// line 461, 0x49D610 - sub_49D610 : movzx   eax, ax
		CCodeMover::FixOnAddressRel(0x49D883, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x83\xD8\x49\x00\x16\x01\x03\x8b\x57\x14\x08\x13\x04\x87\xD8\x09\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x8B\xD8\x49\x00\x16\x01\x03\x8b\x57\x10\x08\x00", 0x49D88E);	// line 462, 0x49D610 - sub_49D610 : movsx   edx, word ptr [edi+2]
		CCodeMover::FixOnAddressRel(0x49D926, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\x26\xD9\x49\x00\x16\x01\x02\x6a\x00\x01\x05\x68\xA8\x03\x00\x00\x01\x01\x56\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x44\x24\xfc\x08\x00", 0x49D92D);	// line 463, 0x49D610 - sub_49D610 : mov     ax, [esi+3A8h]
		CCodeMover::FixOnAddressRel(0x49D937, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x37\xD9\x49\x00\x16\x01\x02\x8b\xc8\x08\x13\x03\x3A\xD9\x09\x00\x00", 0x49D93D);	// line 464, 0x49D610 - sub_49D610 : movzx   ecx, ax
		CCodeMover::FixOnAddressRel(0x49D94C, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x4C\xD9\x49\x00\x16\x08\x13\x02\x4F\xD9\x09\x00\x00", 0x49D951);	// line 465, 0x49D610 - sub_49D610 : movzx   eax, ax
		CCodeMover::FixOnAddressRel(0x49DA04, 11, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x04\xDA\x49\x00\x16\x01\x03\x8b\x57\x14\x08\x13\x04\x08\xDA\x09\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x0C\xDA\x49\x00\x16\x01\x03\x8b\x57\x10\x08\x00", 0x49DA0F);	// line 466, 0x49D610 - sub_49D610 : movsx   edx, word ptr [edi+2]
		CCodeMover::FixOnAddressRel(0x508051, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x51\x80\x50\x00\x16\x01\x03\x8b\x41\x24\x08\x13\x04\x55\x80\x10\x00\x00", 0x508059);	// line 467, 0x508050 - sub_508050 : movsx   eax, word ptr [ecx+0Ch]
		CCodeMover::FixOnAddressRel(0x565DD6, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xD6\x5D\x56\x00\x16\x01\x03\x8b\x48\x24\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xDA\x5D\x56\x00\x16\x01\x03\x8b\x50\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xDE\x5D\x56\x00\x16\x01\x03\x8b\x40\x1C\x08\x00", 0x565DE2);	// line 468, 0x565CB0 - sub_565CB0 : movsx   ecx, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x566002, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x02\x60\x56\x00\x16\x01\x03\x8b\x48\x24\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x06\x60\x56\x00\x16\x01\x03\x8b\x50\x20\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x0A\x60\x56\x00\x16\x01\x03\x8b\x40\x1C\x08\x00", 0x56600E);	// line 469, 0x565E80 - sub_565E80 : movsx   ecx, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x595897, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x97\x58\x59\x00\x16\x01\x04\x8b\x5c\x08\x1C\x08\x00", 0x59589C);	// line 470, 0x595590 - sub_595590 : movsx   ebx, word ptr [eax+ecx+8]
		CCodeMover::FixOnAddressRel(0x5958A2, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA2\x58\x59\x00\x16\x01\x03\x8b\x58\x20\x08\x13\x04\xA6\x58\x19\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xAA\x58\x59\x00\x16\x01\x03\x8b\x40\x24\x08\x00", 0x5958AE);	// line 471, 0x595590 - sub_595590 : movsx   ebx, word ptr [eax+0Ah]
		CCodeMover::FixOnAddressRel(0x595947, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x47\x59\x59\x00\x16\x01\x03\x8b\x48\x1C\x08\x13\x04\x4B\x59\x19\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x4F\x59\x59\x00\x16\x01\x03\x8b\x48\x20\x08\x00", 0x595953);	// line 472, 0x595590 - sub_595590 : movsx   ecx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x595957, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x57\x59\x59\x00\x16\x01\x03\x8b\x40\x24\x08\x13\x06\x5B\x59\x19\x00\x00", 0x595961);	// line 473, 0x595590 - sub_595590 : movsx   eax, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x595B27, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x27\x5B\x59\x00\x16\x01\x04\x8b\x5c\x08\x1C\x08\x00", 0x595B2C);	// line 474, 0x595590 - sub_595590 : movsx   ebx, word ptr [eax+ecx+8]
		CCodeMover::FixOnAddressRel(0x595B32, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x32\x5B\x59\x00\x16\x01\x03\x8b\x58\x20\x08\x13\x04\x36\x5B\x19\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x3A\x5B\x59\x00\x16\x01\x03\x8b\x40\x24\x08\x00", 0x595B3E);	// line 475, 0x595590 - sub_595590 : movsx   ebx, word ptr [eax+0Ah]
		CCodeMover::FixOnAddressRel(0x595BC5, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xC5\x5B\x59\x00\x16\x01\x03\x8b\x48\x1C\x08\x13\x04\xC9\x5B\x19\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xCD\x5B\x59\x00\x16\x01\x03\x8b\x48\x20\x08\x00", 0x595BD1);	// line 476, 0x595590 - sub_595590 : movsx   ecx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x595BD5, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xD5\x5B\x59\x00\x16\x01\x03\x8b\x40\x24\x08\x13\x06\xD9\x5B\x19\x00\x00", 0x595BDF);	// line 477, 0x595590 - sub_595590 : movsx   eax, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x595DA5, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\xA5\x5D\x59\x00\x16\x01\x04\x8b\x5c\x08\x1C\x08\x00", 0x595DAA);	// line 478, 0x595590 - sub_595590 : movsx   ebx, word ptr [eax+ecx+8]
		CCodeMover::FixOnAddressRel(0x595DB0, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB0\x5D\x59\x00\x16\x01\x03\x8b\x58\x20\x08\x13\x04\xB4\x5D\x19\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB8\x5D\x59\x00\x16\x01\x03\x8b\x40\x24\x08\x00", 0x595DBC);	// line 479, 0x595590 - sub_595590 : movsx   ebx, word ptr [eax+0Ah]
		CCodeMover::FixOnAddressRel(0x595E3D, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x3D\x5E\x59\x00\x16\x01\x03\x8b\x48\x1C\x08\x13\x04\x41\x5E\x19\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x45\x5E\x59\x00\x16\x01\x03\x8b\x48\x20\x08\x00", 0x595E49);	// line 480, 0x595590 - sub_595590 : movsx   ecx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x595E4D, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x4D\x5E\x59\x00\x16\x01\x03\x8b\x40\x24\x08\x13\x06\x51\x5E\x19\x00\x00", 0x595E57);	// line 481, 0x595590 - sub_595590 : movsx   eax, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x596012, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x12\x60\x59\x00\x16\x01\x04\x8b\x5c\x08\x1C\x08\x00", 0x596017);	// line 482, 0x595590 - sub_595590 : movsx   ebx, word ptr [eax+ecx+8]
		CCodeMover::FixOnAddressRel(0x59601D, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x1D\x60\x59\x00\x16\x01\x03\x8b\x58\x20\x08\x13\x04\x21\x60\x19\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x25\x60\x59\x00\x16\x01\x03\x8b\x40\x24\x08\x00", 0x596029);	// line 483, 0x595590 - sub_595590 : movsx   ebx, word ptr [eax+0Ah]
		CCodeMover::FixOnAddressRel(0x5960C2, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xC2\x60\x59\x00\x16\x01\x03\x8b\x48\x1C\x08\x13\x04\xC6\x60\x19\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xCA\x60\x59\x00\x16\x01\x03\x8b\x48\x20\x08\x00", 0x5960CE);	// line 484, 0x595590 - sub_595590 : movsx   ecx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x5960D2, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xD2\x60\x59\x00\x16\x01\x03\x8b\x40\x24\x08\x13\x06\xD6\x60\x19\x00\x00", 0x5960DC);	// line 485, 0x595590 - sub_595590 : movsx   eax, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x613573, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x05\x73\x35\x61\x00\x16\x01\x04\x8b\x4C\x10\x20\x08\x00", 0x613578);	// line 486, 0x6133F0 - sub_6133F0 : movsx   ecx, word ptr [eax+edx+0Ah]
		CCodeMover::FixOnAddressRel(0x61357A, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x7A\x35\x61\x00\x16\x01\x03\x8b\x50\x24\x08\x13\x04\x7E\x35\x21\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x82\x35\x61\x00\x16\x01\x03\x8b\x50\x1C\x08\x00", 0x613586);	// line 487, 0x6133F0 - sub_6133F0 : movsx   edx, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x667313, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x13\x73\x66\x00\x16\x01\x03\x8b\x41\x1C\x08\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x17\x73\x66\x00\x16\x01\x03\x8b\x51\x20\x08\x00", 0x66731B);	// line 488, 0x667310 - sub_667310 : movsx   eax, word ptr [ecx+8]
		CCodeMover::FixOnAddressRel(0x66731F, 8, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x1F\x73\x66\x00\x16\x01\x03\x8b\x41\x24\x08\x13\x04\x23\x73\x26\x00\x00", 0x667327);	// line 489, 0x667310 - sub_667310 : movsx   eax, word ptr [ecx+0Ch]
		CCodeMover::FixOnAddressRel(0x669A26, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x26\x9A\x66\x00\x16\x01\x03\x8b\x50\x1C\x08\x13\x04\x2A\x9A\x26\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x2E\x9A\x66\x00\x16\x01\x03\x8b\x50\x20\x08\x00", 0x669A32);	// line 490, 0x6699E0 - sub_6699E0 : movsx   edx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x669A36, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x36\x9A\x66\x00\x16\x01\x03\x8b\x40\x24\x08\x13\x06\x3A\x9A\x26\x00\x00", 0x669A40);	// line 491, 0x6699E0 - sub_6699E0 : movsx   eax, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x669AB0, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB0\x9A\x66\x00\x16\x01\x03\x8b\x50\x1C\x08\x13\x04\xB4\x9A\x26\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB8\x9A\x66\x00\x16\x01\x03\x8b\x50\x20\x08\x00", 0x669ABC);	// line 492, 0x6699E0 - sub_6699E0 : movsx   edx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x669AC0, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xC0\x9A\x66\x00\x16\x01\x03\x8b\x40\x24\x08\x13\x06\xC4\x9A\x26\x00\x00", 0x669ACA);	// line 493, 0x6699E0 - sub_6699E0 : movsx   eax, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x669B39, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x39\x9B\x66\x00\x16\x01\x03\x8b\x50\x1C\x08\x13\x04\x3D\x9B\x26\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x41\x9B\x66\x00\x16\x01\x03\x8b\x50\x20\x08\x00", 0x669B45);	// line 494, 0x6699E0 - sub_6699E0 : movsx   edx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x669B49, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x49\x9B\x66\x00\x16\x01\x03\x8b\x40\x24\x08\x13\x06\x4D\x9B\x26\x00\x00", 0x669B53);	// line 495, 0x6699E0 - sub_6699E0 : movsx   eax, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x669BC3, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xC3\x9B\x66\x00\x16\x01\x03\x8b\x50\x1C\x08\x13\x04\xC7\x9B\x26\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xCB\x9B\x66\x00\x16\x01\x03\x8b\x50\x20\x08\x00", 0x669BCF);	// line 496, 0x6699E0 - sub_6699E0 : movsx   edx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x669BD3, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xD3\x9B\x66\x00\x16\x01\x03\x8b\x40\x24\x08\x13\x06\xD7\x9B\x26\x00\x00", 0x669BDD);	// line 497, 0x6699E0 - sub_6699E0 : movsx   eax, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x669C64, 12, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x64\x9C\x66\x00\x16\x01\x03\x8b\x50\x1C\x08\x13\x04\x68\x9C\x26\x00\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x6C\x9C\x66\x00\x16\x01\x03\x8b\x50\x20\x08\x00", 0x669C70);	// line 498, 0x6699E0 - sub_6699E0 : movsx   edx, word ptr [eax+8]
		CCodeMover::FixOnAddressRel(0x669C74, 10, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x74\x9C\x66\x00\x16\x01\x03\x8b\x40\x24\x08\x13\x06\x78\x9C\x26\x00\x00", 0x669C7E);	// line 499, 0x6699E0 - sub_6699E0 : movsx   eax, word ptr [eax+0Ch]
		CCodeMover::FixOnAddressRel(0x1560D0E, 5, "\x01\x01\x3d\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES\x00\x01\x02\x0F\x8D\x15\x4e\x0d\x16\x01\x00", 0x1560D13);	// line 500, 0x44E000 - _ZN9CPathFind36AddDynamicLinkBetween2Nodes_For1NodeE12CNodeAddressS0_ : cmp     eax, 40h ; '@'
		CCodeMover::FixOnAddressRel(0x1560DDC, 5, "\x01\x01\xbe\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES_WITH_INTERIOR_SLOTS\x00\x00", 0x1560DE1);	// line 501, 0x44D080 - _ZN9CPathFind4InitEv : mov     esi, 48h ; 'H'
		CCodeMover::FixOnAddressRel(0x1560E13, 5, "\x01\x01\xb9\x05\x04""NUMBER_OF_PATH_INTERIOR_SLOTS\x00\x00", 0x1560E18);	// line 502, 0x44D080 - _ZN9CPathFind4InitEv : mov     ecx, 8
		CCodeMover::FixOnAddressRel(0x1562767, 5, "\x01\x01\xbb\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x00", 0x156276C);	// line 503, 0x450950 - _ZN9CPathFind8ShutdownEv : mov     ebx, 8
		CCodeMover::FixOnAddressRel(0x156277D, 6, "\x01\x02\x81\xc6\x05\x04""SIZE_OF_POINTERS_FOR_ONE_DIMENSION\x00\x01\x02\x81\xc7\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x00", 0x1562783);	// line 504, 0x450950 - _ZN9CPathFind8ShutdownEv : add     esi, 20h ; ' '
		CCodeMover::FixOnAddressRel(0x156278E, 7, "\x01\x02\x81\xfd\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x13\x04\x91\x27\x16\x01\x00", 0x1562795);	// line 505, 0x450950 - _ZN9CPathFind8ShutdownEv : cmp     ebp, 8
		CCodeMover::FixOnAddressRel(0x15643D5, 5, "\x01\x02\x81\xc2\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES\x00\x13\x02\xD8\x43\x16\x01\x00", 0x15643DA);	// line 506, 0x44E1A0 - _ZN9CPathFind14RemoveInteriorEj : add     edx, 40h ; '@'
		CCodeMover::FixOnAddressRel(0x156442A, 6, "\x01\x03\x66\x81\xf9\x05\x02""TOTAL_NUMBER_OF_PATH_INDICES\x00\x01\x02\x0F\x82\x15\x35\x44\x16\x01\x00", 0x1564430);	// line 507, 0x44E1A0 - _ZN9CPathFind14RemoveInteriorEj : cmp     cx, 64
		CCodeMover::FixOnAddressRel(0x15645C7, 7, "\x01\x01\x3d\x05\x04""NUMBER_OF_PATH_INTERIOR_SLOTS\x00\x13\x04\xCA\x45\x16\x01\x00", 0x15645CE);	// line 508, 0x44E1A0 - _ZN9CPathFind14RemoveInteriorEj : cmp     eax, 8
		CCodeMover::FixOnAddressRel(0x1565429, 5, "\x01\x01\xbf\x05\x04""TOTAL_NUMBER_OF_PATH_INDICES\x00\x00", 0x156542E);	// line 509, 0x44D400 - _ZN9CPathFind30UnMarkAllRoadNodesAsDontWanderEv : mov     edi, 40h ; '@'
		CCodeMover::FixOnAddressRel(0x15656EA, 6, "\x01\x02\x81\xc7\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x01\x02\x81\xfe\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x00", 0x15656F0);	// line 510, 0x44DE00 - _ZN9CPathFind21LoadSceneForPathNodesE7CVector : add     edi, 8
		CCodeMover::FixOnAddressRel(0x15656F2, 10, "\x01\x02\x81\xc3\x05\x04""NUMBER_OF_PATH_FILES_PER_DIMENSION\x00\x13\x01\xF5\x56\x16\x01\x13\x06\xF6\x56\x16\x01\x00", 0x15656FC);	// line 511, 0x44DE00 - _ZN9CPathFind21LoadSceneForPathNodesE7CVector : add     ebx, 8
		CCodeMover::FixOnAddressRel(0x1567AD4, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xD4\x7A\x56\x01\x16\x01\x02\x6a\x00\x01\x05\x68\xA4\x03\x00\x00\x01\x01\x50\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x1567ADB);	// line 512, 0x1567AD0 - sub_1567AD0 : mov     cx, [eax+3A4h]
		CCodeMover::FixOnAddressRel(0x1567AE6, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\xE6\x7A\x56\x01\x16\x08\x13\x03\xE9\x7A\x16\x01\x00", 0x1567AEC);	// line 513, 0x1567AD0 - sub_1567AD0 : movzx   ecx, cx
		CCodeMover::FixOnAddressRel(0x1567AF7, 7, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x07\xF7\x7A\x56\x01\x16\x01\x02\x6a\x00\x01\x05\x68\xA6\x03\x00\x00\x01\x01\x50\x01\x01\xe8\x06GET_PATH_POINT_INDEX\x00\x01\x03\x83\xc4\x0c\x01\x04\x8b\x4C\x24\xfc\x08\x00", 0x1567AFE);	// line 514, 0x1567AD0 - sub_1567AD0 : mov     cx, [eax+3A6h]
		CCodeMover::FixOnAddressRel(0x1567B03, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x03\x03\x7B\x56\x01\x16\x08\x13\x03\x06\x7B\x16\x01\x00", 0x1567B09);	// line 515, 0x1567AD0 - sub_1567AD0 : movzx   ecx, cx
		CCodeMover::FixOnAddressRel(0x156A206, 5, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\x06\xA2\x56\x01\x16\x01\x03\x8b\x14\xb1\x08\x13\x01\x0A\xA2\x16\x01\x00", 0x156A20B);	// line 516, 0x451350 - _ZN9CPathFind20FindLinkBetweenNodesE12CNodeAddressS0_ : mov     dx, [ecx+esi*2]
		CCodeMover::FixOnAddressRel(0x156EAA1, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xA1\xEA\x56\x01\x16\x01\x03\x8b\x14\x90\x08\x13\x02\xA5\xEA\x16\x01\x00", 0x156EAA7);	// line 517, 0x156E9C0 - sub_156E9C0 : movzx   edx, word ptr [eax+edx*2]
		CCodeMover::FixOnAddressRel(0x156EBB7, 6, "\x07\x04\x01\x00\x00\x00PATHS_DEBUG\x00\x02\x04\xB7\xEB\x56\x01\x16\x01\x03\x8b\x14\x82\x08\x13\x02\xBB\xEB\x16\x01\x00", 0x156EBBD);	// line 518, 0x156E9C0 - sub_156E9C0 : movzx   edx, word ptr [edx+eax*2]
	}
	#endif

	// Undefine variables of automatic patch
	#if TRUE
	{
		// variables
		CCodeMover::DeleteVariable("PATHS_DEBUG");

		CCodeMover::DeleteVariable("TOTAL_NUMBER_OF_PATH_INDICES");
		CCodeMover::DeleteVariable("TOTAL_NUMBER_OF_PATH_INDICES_WITH_INTERIOR_SLOTS");
		CCodeMover::DeleteVariable("NUMBER_OF_PATH_FILES_PER_DIMENSION");
		CCodeMover::DeleteVariable("NUMBER_OF_PATH_FILES_PER_DIMENSION_MINUS_ONE");
		CCodeMover::DeleteVariable("NUMBER_OF_PATH_INTERIOR_SLOTS");
		CCodeMover::DeleteVariable("SIZE_OF_POINTERS_FOR_ONE_DIMENSION");
		CCodeMover::DeleteVariable("MINUS_1");

		// functions
		CCodeMover::DeleteVariable("GET_PATH_POINT_INDEX");
		CCodeMover::DeleteVariable("SET_PATH_POINT_INDEX");
	}
	#endif
}
#endif

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
namespace Game_GTASA
{
	extern "C"
	{
		MAKE_GTA_SA_CPATH_FIND(CPathFind, STRUCTURE_MEMBER_OFFSET_VARIABLE_DEFINITION);

		// m_field_1544
		#define NAMEOF_m_field_1544_index(index) Offset_CPathFind__m_field_1544_index_##index

		#define MAKE_m_field_1544_indices(macro) \
			macro(0); \
			macro(1); \
			macro(2); \
			macro(3); \
			macro(4); \
			macro(5); \
			macro(6); \
			macro(7); \
			macro(8); \
			macro(9); \
			macro(10); \
			macro(11); \
			macro(12); \
			macro(13); \
			macro(14); \
			macro(15);

		#define m_field_1544_indices_DEFINITION(index) uint32_t NAMEOF_m_field_1544_index(index)

		MAKE_m_field_1544_indices(m_field_1544_indices_DEFINITION)

			#define MAKE_m_field_1544_plus_1024_indices(macro) \
			macro(1024); \
			macro(1025); \
			macro(1026); \
			macro(1027); \
			macro(1028); \
			macro(1029); \
			macro(1030); \
			macro(1031); \
			macro(1032); \
			macro(1033); \
			macro(1034); \
			macro(1035); \
			macro(1036); \
			macro(1037); \
			macro(1038); \
			macro(1039);

			MAKE_m_field_1544_plus_1024_indices(m_field_1544_indices_DEFINITION)

			// m_interiorAreaIDarray
			#define NAMEOF_m_interiorNodes_index(index) Offset_CPathFind__m_interiorAreaIDarray_index_##index
			#define MAKE_interior_indices(macro) \
			macro(0); \
			macro(1); \
			macro(2); \
			macro(3); \
			macro(4); \
			macro(5); \
			macro(6); \
			macro(7);

			#define m_interiorNodes_indices_DEFINITION(index) uint32_t NAMEOF_m_interiorNodes_index(index);
			MAKE_interior_indices(m_interiorNodes_indices_DEFINITION);

		uint32_t Offset_CPathFind__m_dwNumAddresses_index_TotalNumberOfPathFile = 0;
		uint32_t Offset_CPathFind__m_dwNumCarPathLinks_index_TotalNumberOfPathFile = 0;
		uint32_t Offset_CPathFind__m_dwNumPedNodes_index_TotalNumberOfPathFile = 0;
		uint32_t Offset_CPathFind__m_dwNumVehicleNodes_index_TotalNumberOfPathFile = 0;
		uint32_t Offset_CPathFind__m_dwNumNodes_index_TotalNumberOfPathFile = 0;
		uint32_t Offset_CPathFind__pPathIntersections_index_TotalNumberOfPathFile = 0;
		uint32_t Offset_CPathFind__m_pLinkLengths_index_1 = 0;
		uint32_t Offset_CPathFind__m_pLinkLengths_index_TotalNumberOfPathFile = 0;
		uint32_t Offset_CPathFind__m_pNodeLinks_index_1 = 0;
		uint32_t Offset_CPathFind__m_pNodeLinks_index_TotalNumberOfPathFile = 0;
		uint32_t Offset_CPathNode_index_1_m_dwFlags = 0;

		int iNumberOfPathFilesPerDimensionNegated;
		int iNumberOfPathFilesPerDimensionTimes2Negated;
		int iNumberOfPathFilesPerDimensionTimes2Plus1Negated;
		int iNumberOfPathFilesPerDimensionTimes2Plus2Negated;
		int iNumberOfPathFilesPerDimensionPlus1;
		unsigned int iNumberOfPathFilesPerDimension_multiplied_by_sizeof_CNodeAddress;
		int iTotalNumberOfPathFilesNegatedCNodeAddressMask;

		uint32_t Offset_CPathFind__m_pPathNodes_divided_by_sizeOf_CNodeAddress_minus_NumberOfPathFilesPerDimension_minus_2;

		// for interior nodes
		#define MAKE_interior_indices_plus_totalNumberOfPathFiles(macro) \
			macro(64); \
			macro(65); \
			macro(66); \
			macro(67); \
			macro(68); \
			macro(69); \
			macro(70); \
			macro(71);
		#define NAMEOF_totalNumberOfPathFiles_index(index) iTotalNumberOfPathFiles_plus_##index
		#define totalNumberOfPathFiles_indices_DEFINITION(index) uint32_t NAMEOF_totalNumberOfPathFiles_index(index)
		MAKE_interior_indices_plus_totalNumberOfPathFiles(totalNumberOfPathFiles_indices_DEFINITION);

		/////
		
	}

	// Automatic patches
	#include "PathsMapSize/GTA SA 2.0 ANDROID_ARMEABI_V7A/functions.cpp"

	// Manual patches
	#if TRUE

// patch for 0x3153E0
	extern "C"
	{
		uintptr_t Address_CPathFind__LoadPathFindData_31540A_thumb = 0;	// loc_315404
		uintptr_t Address_CPathFind__LoadPathFindData_3153E8_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPathFind__LoadPathFindData_3153E0()
	{
		__asm(
		".thumb\n"
			"LDR R0, [R4]\n"
			"CBZ R0, 1f\n"
			ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__LoadPathFindData_3153E8_thumb)

			// Branches
			"1:\n"	// loc_315404
			"MOVS R0, #0\n"

			"PUSH {R1, R2}\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
			"STR R0, [R11,R1]\n"
			"POP {R1, R2}\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__LoadPathFindData_31540A_thumb)
			);
	}

	static TARGET_THUMB void patch_CPathFind__DoPathSearch_3158F8();

	// patch for 0x3158F8
	extern "C"
	{
		uintptr_t Address_CPathFind__DoPathSearch_315918_thumb = 0;	// loc_315914
		uintptr_t Address_CPathFind__DoPathSearch_315900_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPathFind__DoPathSearch_3158F8()
	{
		__asm(
		".thumb\n"
			"UXTH R1, R0\n"
			"CMP R1, R11\n"
			"BNE 1f\n"
			"LDR R0, [R7,#"/* arg_18 */"0x20]\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__DoPathSearch_315900_thumb)

			// Branches
			"1:\n"	// loc_315914
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R8, Offset_CPathFind__m_dwTotalNumNodesInSearchList)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__DoPathSearch_315918_thumb)
			);
	}

	// patch for 0x317B88
	extern "C"
	{
		uintptr_t Address_CPathFind__RecordNodesClosestToCoors_317B9C_thumb = 0;	// loc_317B96
		uintptr_t Address_CPathFind__RecordNodesClosestToCoors_317BA0_thumb = 0;	// loc_317BA0
		uintptr_t Address_CPathFind__RecordNodesClosestToCoors_317B90_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPathFind__RecordNodesClosestToCoors_317B88()
	{
		__asm(
		".thumb\n"
			"BEQ 1f\n"
			"CMP R12, #0\n"
			"BNE 2f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__RecordNodesClosestToCoors_317B90_thumb)

			// Branches
			"1:\n"	// loc_317B96
			"LDR R0, [R5,R3]\n"
			"MOV R2, R5\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_dwNumNodes)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__RecordNodesClosestToCoors_317B9C_thumb)
			"2:\n"	// loc_317BA0
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__RecordNodesClosestToCoors_317BA0_thumb)
			);
	}

	// patch for 0x317F84
	extern "C"
	{
		uintptr_t Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317EDE_thumb = 0;	// loc_317EDE
	}

	static TARGET_THUMB NAKED void patch_CPathFind__FindNodeClosestToCoorsFavourDirection_317F84()
	{
		__asm(
		".thumb\n"
			"ITTT LT\n"
			"MOVLT LR, R11\n"
			"MOVLT R10, R4\n"
			"VMOVLT.F32 S12, S7\n"

			"ADDS R4, #1\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNode)
			"CMP R5, R4\n"
			"BNE 1f\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317F96_thumb_)

			// Branches
			"1:\n"	// loc_317EDE
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317EDE_thumb)
			);
	}

	// patch for 0x317EAC
	extern "C"
	{
		uintptr_t Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317ECA_thumb = 0;	// loc_317EC2
		uintptr_t Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317EB6_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPathFind__FindNodeClosestToCoorsFavourDirection_317EAC()
	{
		__asm(
		".thumb\n"
			"CMP R12, #1\n"
			"BEQ 1f\n"
			"CMP R12, #0\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317EB6_thumb)

			// Branches
			"1:\n"	// loc_317EC2
			"LDR R9, [R6,R8]\n"
			"MOV R5, R6\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_dwNumNodes)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317ECA_thumb)
			);
	}

	// patch for 0x317F32
	extern "C"
	{
		uintptr_t Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317F96_thumb_ = 0;	// loc_317F8E
		uintptr_t Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317F3C_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPathFind__FindNodeClosestToCoorsFavourDirection_317F32()
	{
		__asm(
		".thumb\n"
			"VCMPE.F32 S9, S12\n"
			"VMRS APSR_nzcv, FPSCR\n"
			"BGE 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317F3C_thumb)

			// Branches
			"1:\n"	// loc_317F8E
			"ADDS R4, #1\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNode)
			"CMP R5, R4\n"
			"BNE 2f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317F96_thumb_)

			"2:\n"	// loc_317EDE
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317EDE_thumb)
			);
	}

	// patch for 0x31AE5E
	extern "C"
	{
		uintptr_t Address_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEE4_thumb_ = 0;
		uintptr_t Address_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE68_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE5E()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_15)
			"LDR R1, [R0,R1]\n"
			"CMP R1, #0\n"
			"BLT 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE68_thumb)

			// Branches
			"1:\n"	// loc_31AEDE
			"MOV R2, R0\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_field_1544_index_15)
			"MOVS R6, #0xF\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEE4_thumb_)
			);
	}

	extern "C"
	{
		void memset_ToBeStreamed()
		{
			memset(g_mapLimits.ToBeStreamed.ptr, 0, iTotalNumberOfPathFiles);
		}

		void memset_ToBeStreamedForScript()
		{
			memset(g_mapLimits.ToBeStreamedForScript.ptr, 0, iTotalNumberOfPathFiles);
		}
	}

	// patch for 0x3195E2
	extern "C"
	{
		uintptr_t Address_CPathFind__UpdateStreaming_31962A_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPathFind__UpdateStreaming_3195E2()
	{
		__asm(
		".thumb\n"
			"BLX memset_ToBeStreamed\n"
			"BLX memset_ToBeStreamedForScript\n"
			"MOV R0, #0xFFFF\n"
			"MOVT R0, #0xFFFF\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__UpdateStreaming_31962A_thumb)
			);
	}

	// patch for 0x319E48
	extern "C"
	{
		uintptr_t Address_CPathFind__LoadSceneForPathNodes_319E52_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPathFind__LoadSceneForPathNodes_319E48()
	{
		__asm(
		".thumb\n"
			"SUB SP, SP, #4\n"

			"BLX memset_ToBeStreamed\n"

			"VLDR S0, 101f\n"
			"VMOV S2, R1\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__LoadSceneForPathNodes_319E52_thumb)

			// Data
			ASM_PUT_CONSTANT_FLOAT(101, -350.0)
			);
	}

	// patch for 0x31A0B2
	extern "C"
	{
		uintptr_t Address_CPathFind__IsWaterNodeNearby_31A102_thumb_ = 0;	// loc_31A0FA
		uintptr_t Address_CPathFind__IsWaterNodeNearby_31A0B2_thumb = 0;	// loc_31A0B2
		uintptr_t Address_CPathFind__IsWaterNodeNearby_31A0C0_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPathFind__IsWaterNodeNearby_31A0B2()
	{
		__asm(
		".thumb\n"
			"LDRH R4, [R1]\n"
			"LSLS R4, R4, #0x18\n"
			"BPL 1f\n"

			// new coordinates
			"LDR R4, [R1,#0x4]\n"
			"LDR R5, [R1,#0x8]\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__IsWaterNodeNearby_31A0C0_thumb)

			// Branches
			"1:\n"	// loc_31A0FA
			"ADDS            R2, #1\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNode)
			"CMP R2, R3\n"
			"BLT 2f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__IsWaterNodeNearby_31A102_thumb_)

			"2:\n"	// loc_31A0B2
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__IsWaterNodeNearby_31A0B2_thumb)
			);
	}

	// patch for 0x31B4B6
	extern "C"
	{
		uintptr_t Address_CPathFind__FindParkingNodeInArea_31B54E_thumb_ = 0;	// loc_31B548
		uintptr_t Address_CPathFind__FindParkingNodeInArea_31B4C2_thumb = 0;
		uintptr_t Address_CPathFind__FindParkingNodeInArea_31B492_thumb = 0;	// loc_31B492
	}

	static TARGET_THUMB NAKED void patch_CPathFind__FindParkingNodeInArea_31B4B6()
	{
		__asm(
		".thumb\n"
			"BLE 1f\n"
			"VCMPE.F32 S11, S14\n"
			"VMRS APSR_nzcv, FPSCR\n"
			"BGE 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindParkingNodeInArea_31B4C2_thumb)

			// Branches
			"1:\n"	// loc_31B548
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, SizeOfCPathNode)
			"SUBS R4, #1\n"
			"BNE 2f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindParkingNodeInArea_31B54E_thumb_)

			"2:\n"	// loc_31B492
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindParkingNodeInArea_31B492_thumb)
			);
	}

	// patch for 0x31B4DA
	extern "C"
	{
		uintptr_t Address_CPathFind__FindParkingNodeInArea_31B548_thumb = 0;	// loc_31B548
		uintptr_t Address_CPathFind__FindParkingNodeInArea_31B4E4_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPathFind__FindParkingNodeInArea_31B4DA()
	{
		__asm(
		".thumb\n"
			"BLE 1f\n"
			"VCMPE.F32 S13, S10\n"
			"VMRS APSR_nzcv, FPSCR\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindParkingNodeInArea_31B4E4_thumb)

			// Branches
			"1:\n"	// loc_31B548
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, SizeOfCPathNode)
			"SUBS R4, #1\n"
			"BNE 2f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindParkingNodeInArea_31B54E_thumb_)

			"2:\n"	// loc_31B492
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindParkingNodeInArea_31B492_thumb)
			);
	}

	// patch for 0x319F50
	extern "C"
	{
		uintptr_t Address_CPathFind__LoadSceneForPathNodes_319F5E_thumb = 0;	// loc_319F5E
		uintptr_t Address_CPathFind__LoadSceneForPathNodes_18B35C_arm = 0;	// __aeabi_memset
		uintptr_t Address_CPathFind__LoadSceneForPathNodes_319F50_thumb_ = 0;	// loc_319F50
		uintptr_t Address_CPathFind__LoadSceneForPathNodes_319F66_thumb_ = 0;	// loc_319F66
	}

	static TARGET_THUMB NAKED void patch_CPathFind__LoadSceneForPathNodes_319F50()
	{
		__asm(
		".thumb\n"
			"CMP R9, R10\n"
			"BGT 1f\n"
			"MOV R0, R5\n"
			"MOV R1, R8\n"
			"MOVS R2, #1\n"
			"BL 2f\n"

			"1:\n"	// loc_319F5E
			"ADDS R6, #1\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimension)
			"CMP R6, R4\n"
			"BLT 3f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__LoadSceneForPathNodes_319F66_thumb_)

			// Branches
			"2:\n"	// __aeabi_memset
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__LoadSceneForPathNodes_18B35C_arm)
			"3:\n"	// loc_319F50
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__LoadSceneForPathNodes_319F50_thumb_)
			);
	}

	// patch for 0x315EF0
	extern "C"
	{
		uintptr_t Address_CPathFind__FindNodeClosestToCoors_315F20_thumb = 0;	// loc_315F20
		uintptr_t Address_CPathFind__FindNodeClosestToCoors_19BB40_arm = 0;	// j__ZN9CPathFind23FindNodeClosestInRegionEP12CNodeAddresst7CVectorhPfbbbb
		uintptr_t Address_CPathFind__FindNodeClosestToCoors_315EEE_thumb = 0;	// loc_315EEE
		uintptr_t Address_CPathFind__FindNodeClosestToCoors_315F26_thumb_ = 0;	// loc_315F26
	}

	static TARGET_THUMB NAKED void patch_CPathFind__FindNodeClosestToCoors_315EF0()
	{
		__asm(
		".thumb\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iNumberOfPathFilesPerDimensionMinusOne)
			"BHI 1f\n"
			"LDR R0, [SP,#0x98+"/* var_4C */"-0x4C]\n"
			"ADD R1, SP, #0x98+"/* var_3C */"-0x3C\n"
			"STR R0, [SP,#0x98+"/* var_98 */"-0x98]\n"
			"UXTH R2, R5\n"
			"LDR R0, [SP,#0x98+"/* var_48 */"-0x48]\n"
			"MOV R3, R8\n"
			"STR R0, [SP,#0x98+"/* var_94 */"-0x94]\n"
			"LDR R0, [R7,#"/* arg_0 */"0x8]\n"
			"STR R0, [SP,#0x98+"/* var_90 */"-0x90]\n"
			"ADD R0, SP, #0x98+"/* var_40 */"-0x40\n"
			"STR R0, [SP,#0x98+"/* var_8C */"-0x8C]\n"
			"LDR R0, [R7,#"/* arg_8 */"0x10]\n"
			"STR R0, [SP,#0x98+"/* var_88 */"-0x88]\n"
			"LDR R0, [R7,#"/* arg_10 */"0x18]\n"
			"STR R0, [SP,#0x98+"/* var_84 */"-0x84]\n"
			"LDR R0, [R7,#"/* arg_14 */"0x1C]\n"
			"STR R0, [SP,#0x98+"/* var_80 */"-0x80]\n"
			"MOVS R0, #0\n"
			"STR R0, [SP,#0x98+"/* var_7C */"-0x7C]\n"
			"LDR R0, [SP,#0x98+"/* var_44 */"-0x44]\n"
			"BL 2f\n"

			"1:\n"	// loc_315F20
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimension)
			"CMP R6, R4\n"
			"BLT 3f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindNodeClosestToCoors_315F26_thumb_)

			// Branches
			"2:\n"	// j__ZN9CPathFind23FindNodeClosestInRegionEP12CNodeAddresst7CVectorhPfbbbb
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindNodeClosestToCoors_19BB40_arm)
			"3:\n"	// loc_315EEE
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindNodeClosestToCoors_315EEE_thumb)
			);
	}

	// patch for 0x315F48
	extern "C"
	{
		uintptr_t Address_CPathFind__FindNodeClosestToCoors_315F78_thumb = 0;	// loc_315F78
		uintptr_t Address_CPathFind__FindNodeClosestToCoors_315F46_thumb = 0;	// loc_315F46
		uintptr_t Address_CPathFind__FindNodeClosestToCoors_315F7E_thumb_ = 0;	// loc_315F7E
	}

	static TARGET_THUMB NAKED void patch_CPathFind__FindNodeClosestToCoors_315F48()
	{
		__asm(
		".thumb\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimensionMinusOne)
			"BHI 1f\n"
			"LDR R0, [SP,#0x98+"/* var_4C */"-0x4C]\n"
			"ADD R1, SP, #0x98+"/* var_3C */"-0x3C\n"
			"STR R0, [SP,#0x98+"/* var_98 */"-0x98]\n"
			"UXTH R2, R5\n"
			"LDR R0, [SP,#0x98+"/* var_48 */"-0x48]\n"
			"MOV R3, R8\n"
			"STR R0, [SP,#0x98+"/* var_94 */"-0x94]\n"
			"LDR R0, [R7,#"/* arg_0 */"0x8]\n"
			"STR R0, [SP,#0x98+"/* var_90 */"-0x90]\n"
			"ADD R0, SP, #0x98+"/* var_40 */"-0x40\n"
			"STR R0, [SP,#0x98+"/* var_8C */"-0x8C]\n"
			"LDR R0, [R7,#"/* arg_8 */"0x10]\n"
			"STR R0, [SP,#0x98+"/* var_88 */"-0x88]\n"
			"LDR R0, [R7,#"/* arg_10 */"0x18]\n"
			"STR R0, [SP,#0x98+"/* var_84 */"-0x84]\n"
			"LDR R0, [R7,#"/* arg_14 */"0x1C]\n"
			"STR R0, [SP,#0x98+"/* var_80 */"-0x80]\n"
			"MOVS R0, #0\n"
			"STR R0, [SP,#0x98+"/* var_7C */"-0x7C]\n"
			"LDR R0, [SP,#0x98+"/* var_44 */"-0x44]\n"
			"BL 2f\n"

			"1:\n"	// loc_315F78
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimension)
			"CMP R4, R6\n"
			"BLT 3f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindNodeClosestToCoors_315F7E_thumb_)

			// Branches
			"2:\n"	// j__ZN9CPathFind23FindNodeClosestInRegionEP12CNodeAddresst7CVectorhPfbbbb
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindNodeClosestToCoors_19BB40_arm)
			"3:\n"	// loc_315F46
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__FindNodeClosestToCoors_315F46_thumb)
			);
	}

	// patch for 0x319558
	extern "C"
	{
		uintptr_t Address_CPathFind__MarkRegionsForCoors_319566_thumb = 0;	// loc_319566
		uintptr_t Address_CPathFind__MarkRegionsForCoors_18B35C_arm = 0;	// __aeabi_memset
		uintptr_t Address_CPathFind__MarkRegionsForCoors_319558_thumb_ = 0;	// loc_319558
		uintptr_t Address_CPathFind__MarkRegionsForCoors_31956E_thumb_ = 0;	// loc_31956E
	}

	static TARGET_THUMB NAKED void patch_CPathFind__MarkRegionsForCoors_319558()
	{
		__asm(
		".thumb\n"
			"CMP R9, R10\n"
			"BGT 1f\n"
			"MOV R0, R5\n"
			"MOV R1, R8\n"
			"MOVS R2, #1\n"
			"BL 2f\n"

			"1:\n"	// loc_319566
			"ADDS R6, #1\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimension)
			"CMP R6, R4\n"
			"BLT 3f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__MarkRegionsForCoors_31956E_thumb_)

			// Branches
			"2:\n"	// __aeabi_memset
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__MarkRegionsForCoors_18B35C_arm)
			"3:\n"	// loc_319558
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__MarkRegionsForCoors_319558_thumb_)
			);
	}

	// patch for 0x319724
	extern "C"
	{
		uintptr_t Address_CPathFind__UpdateStreaming_319732_thumb = 0;	// loc_319732
		uintptr_t Address_CPathFind__UpdateStreaming_18B35C_arm = 0;	// __aeabi_memset
		uintptr_t Address_CPathFind__UpdateStreaming_319724_thumb_ = 0;	// loc_319724
		uintptr_t Address_CPathFind__UpdateStreaming_31973A_thumb = 0;	// loc_31973A
	}

	static TARGET_THUMB NAKED void patch_CPathFind__UpdateStreaming_319724()
	{
		__asm(
		".thumb\n"
			"CMP R9, R10\n"
			"BGT 1f\n"
			"MOV R0, R5\n"
			"MOV R1, R8\n"
			"MOVS R2, #1\n"
			"BL 2f\n"

			"1:\n"	// loc_319732
			"ADDS R6, #1\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimension)
			"CMP R6, R4\n"
			"BLT 3f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__UpdateStreaming_31973A_thumb)

			// Branches
			"2:\n"	// __aeabi_memset
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__UpdateStreaming_18B35C_arm)
			"3:\n"	// loc_319724
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__UpdateStreaming_319724_thumb_)
			);
	}

	// patch for 0x319834
	extern "C"
	{
		uintptr_t Address_CPathFind__UpdateStreaming_319842_thumb = 0;	// loc_319842
		uintptr_t Address_CPathFind__UpdateStreaming_319834_thumb_ = 0;	// loc_319834
		uintptr_t Address_CPathFind__UpdateStreaming_31984A_thumb_ = 0;	// loc_31984A
	}

	static TARGET_THUMB NAKED void patch_CPathFind__UpdateStreaming_319834()
	{
		__asm(
		".thumb\n"
			"CMP R10, R11\n"
			"BGT 1f\n"
			"MOV R0, R5\n"
			"MOV R1, R9\n"
			"MOVS R2, #1\n"
			"BL 2f\n"

			"1:\n"	// loc_319842
			"ADDS R6, #1\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimension)
			"CMP R6, R4\n"
			"BLT 3f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__UpdateStreaming_31984A_thumb_)

			// Branches
			"2:\n"	// __aeabi_memset
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__UpdateStreaming_18B35C_arm)
			"3:\n"	// loc_319834
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPathFind__UpdateStreaming_319834_thumb_)
			);
	}

	// patch for 0x2F4AD8
	extern "C"
	{
		uintptr_t Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4AE2_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4AD8()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_ADDRESS_OF_SYMBOL(R9, SteerAICarWithPhysicsFollowPath_Racing_naviLinks)
			"ADD R9, 4 * 2\n"	// array index 2

			"LDR R0, =("/* ThePaths_ptr */"0x677378 - 0x2F4AEA)\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4AE2_thumb)
			);
	}

	// patch for 0x2F4A94
	extern "C"
	{
		uintptr_t Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4A9E_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4A94()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_ADDRESS_OF_SYMBOL(R3, SteerAICarWithPhysicsFollowPath_Racing_naviLinks)

			"STRD.W          R1, R1, [R3,#4]\n"
			"STRD.W          R1, R1, [R3,#12]\n"
			"STRD.W          R1, R1, [R3,#20]\n"
			"STR             R1, R1, [R3,#28]\n"
			"STR			 R0, [R1]\n"
			"STR			 R10, [R1,#4]\n"

			"ADD.W           R9, R0, #4*2\n"

			"VMUL.F32 S4, S30, S24\n"
			
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4A9E_thumb)
			);
	}

	// patch for 0x2F4B96
	extern "C"
	{
		uintptr_t Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4BA0_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4B96()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_ADDRESS_OF_SYMBOL(R1, SteerAICarWithPhysicsFollowPath_Racing_naviLinks)

			"STRD.W          R0, R0, [R1,#0xC*2]\n"
			
			"MOV R0, #0x0\n"
			"MOVT R0, #0x3F80\n"
			"STR R0, [SP,#0x120+"/* var_7C */"-0x7C]\n"

			ASM_LOAD_ADDRESS_OF_SYMBOL(R0, SteerAICarWithPhysicsFollowPath_Racing_naviLinks)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4BA0_thumb)
			);
	}

	// patch for 0x2F4BBE
	extern "C"
	{
		uintptr_t Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4BC8_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4BBE()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_ADDRESS_OF_SYMBOL(R2, SteerAICarWithPhysicsFollowPath_Racing_naviLinks)
			"ADD R2, R2, R10,LSL#2\n"
			"ADD R3, R0, R10\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4BC8_thumb)
			);
	}
	#endif

	//////////////////////////
	///// For debugging
	#ifdef ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA
	extern "C"
	{
		static bool bArePathNodesExtended = true;

		F92_LA_API void MakePathNodesStandard()
		{
			Offset_CPathFind__m_pPathNodes = CPathFind::m_pPathNodesStandard.GetOffset();
			SizeOfCPathNode = sizeof(CPathNode);
			SizeOfCPathNodeDividedBy4 = SizeOfCPathNode / 4;
			Offset_CPathNode_index_1_m_dwFlags = SizeOfCPathNode + offsetof(CPathNode, m_dwFlags);
			bArePathNodesExtended = false;
		}

		F92_LA_API void MakePathNodesExtended()
		{
			Offset_CPathFind__m_pPathNodes = CPathFind::m_pPathNodes.GetOffset();
			SizeOfCPathNode = sizeof(CPathNode_extended_latest);
			SizeOfCPathNodeDividedBy4 = SizeOfCPathNode / 4;
			Offset_CPathNode_index_1_m_dwFlags = SizeOfCPathNode + offsetof(CPathNode, m_dwFlags);
			bArePathNodesExtended = true;
		}

		static bool bAreCarPathLinksExtended = true;

		F92_LA_API void MakeCarPathLinksStandard()
		{
			Offset_CPathFind__m_pNaviNodes = CPathFind::m_pNaviNodesStandard.GetOffset();
			SizeOfCCarPathLink = sizeof(CCarPathLink);
			SizeOfCCarPathLinkDividedBy2 = SizeOfCCarPathLink / 2;
			bAreCarPathLinksExtended = false;
		}

		F92_LA_API void MakeCarPathLinksExtended()
		{
			Offset_CPathFind__m_pNaviNodes = CPathFind::m_pNaviNodes.GetOffset();
			SizeOfCCarPathLink = sizeof(CCarPathLink_extended_latest);
			SizeOfCCarPathLinkDividedBy2 = SizeOfCCarPathLink / 2;
			bAreCarPathLinksExtended = true;
		}
	}

	#define PATH_PROCESSING_FOR_DEBUGGING_PATH_NODES
	// define PATH_PROCESSING_FOR_DEBUGGING_CAR_PATH_LINKS

	class CPathProcessingForDebugging
	{
		#ifdef PATH_PROCESSING_FOR_DEBUGGING_PATH_NODES
		bool bOldArePathNodesExtended;
		#endif

		#ifdef PATH_PROCESSING_FOR_DEBUGGING_CAR_PATH_LINKS
		bool bOldAreCarPathLinksExtended;
		#endif

	public:

		void Preprocess()
		{
			#ifdef PATH_PROCESSING_FOR_DEBUGGING_PATH_NODES
			this->bOldArePathNodesExtended = bArePathNodesExtended;
			#endif

			#ifdef PATH_PROCESSING_FOR_DEBUGGING_CAR_PATH_LINKS
			this->bOldAreCarPathLinksExtended = bAreCarPathLinksExtended;
			#endif

			#ifdef PATH_PROCESSING_FOR_DEBUGGING_PATH_NODES
			MakePathNodesStandard();
			#endif

			#ifdef PATH_PROCESSING_FOR_DEBUGGING_CAR_PATH_LINKS
			MakeCarPathLinksStandard();
			#endif
		}

		void Postprocess()
		{
			#ifdef PATH_PROCESSING_FOR_DEBUGGING_PATH_NODES
			if (this->bOldArePathNodesExtended)
				MakePathNodesExtended();
			else
				MakePathNodesStandard();
			#endif

			#ifdef PATH_PROCESSING_FOR_DEBUGGING_CAR_PATH_LINKS
			if (this->bOldAreCarPathLinksExtended)
				MakeCarPathLinksExtended();
			else
				MakeCarPathLinksStandard();
			#endif
		}
	};


	#define DEBUG_FUNCTION_PREPROCESS() CPathProcessingForDebugging processing; processing.Preprocess();
	#define DEBUG_FUNCTION_POSTPROCESS()processing.Postprocess();

	extern "C"
	{
		void PrintCLinkAddress(uint32_t link_address, unsigned int r8, unsigned int r3)
		{
			return;
			auto our_link_address = *(CLinkAddress_extended*)&link_address;

			OutputFormattedDebugString(
				"Area ID: %d Link ID: %d First: %d Second: %d",
				our_link_address.m_wAreaId, our_link_address.m_wCarPathLinkId,
				r8 / 4, r3

			);
		}

		void VerifyCLinkAddress(uint32_t link_address, uintptr_t location, bool bIsStore)
		{
			return;
			auto our_link_address = *(CLinkAddress_extended*)&link_address;

			// if(our_link_address.m_wCarPathLinkId > 65000 && our_link_address.m_wCarPathLinkId != 0xFFFF)

			OutputFormattedDebugString(
				"Area ID: %d Link ID: %d bIsStore: %d Location: 0x%llX",
				our_link_address.m_wAreaId, our_link_address.m_wCarPathLinkId, bIsStore, (uint64_t)location
			);
		}
	}

	// Automatic patches
	#include "PathsMapSizeDebugging/GTA SA 2.0 ANDROID_ARMEABI_V7A/functions.cpp"
	#endif

	extern "C"
	{
		void CheckForCCarPathLink_extended(const CCarPathLink_extended_latest* ptr, uintptr_t address)
		{
			if (ptr->Coors.x == ptr->CoorsExtended.x
				&& ptr->Coors.y == ptr->CoorsExtended.y)
				return;

			OutputFormattedDebugString("Bad CCarPathLink: 0x%X", address);
		}

		void CheckForCPathNode_extended(const CPathNode_extended_latest* ptr, uintptr_t address)
		{
			if (ptr->Coors.x == ptr->CoorsExtended.x
				&& ptr->Coors.y == ptr->CoorsExtended.y
				&& ptr->Coors.z == ptr->CoorsExtended.z)
				return;

			OutputFormattedDebugString("Bad CPathNode: 0x%X", address);
		}
	}
}

// Patches paths
void MapLimits::PatchPaths_GTA_SA_2_0_ANDROID_ARM32()
{
	using namespace Game_GTASA;

	const bool bDisableLoadingPaths = false;

	// Disable paths (for debugging)
	// not done

	// CPatch::EnableDumpingMemoryAddressesToLogFile(false);

	if (!this->PatchPaths_DoInitialisingWork())
		return;

	// Set variables
	#if TRUE
	{
		MAKE_GTA_SA_CPATH_FIND(CPathFind, STRUCTURE_MEMBER_OFFSET_VARIABLE_ASSIGNMENT);

		// m_field_1544
		#define m_field_1544_indices_ASSIGNMENT(index) NAMEOF_m_field_1544_index(index) = CPathFind::m_field_1544.GetOffset() + index * sizeof(void*)
		#define m_field_1544_plus_1024_indices_ASSIGNMENT(index) NAMEOF_m_field_1544_index(index) = CPathFind::m_field_1544.GetOffset() + (CPathFind_field_1544_numberOfElementsPerPathFile + index) * sizeof(void*)

		MAKE_m_field_1544_indices(m_field_1544_indices_ASSIGNMENT);
		MAKE_m_field_1544_plus_1024_indices(m_field_1544_plus_1024_indices_ASSIGNMENT);

		// m_interiorAreaIDarray
		#define m_interiorNodes_indices_ASSIGNMENT(index) NAMEOF_m_interiorNodes_index(index) = CPathFind::m_interiorAreaIDarray.GetOffset() + index * sizeof(CNodeAddress)
		MAKE_interior_indices(m_interiorNodes_indices_ASSIGNMENT);

		// totalNumberOfPathFiles__indices
		#define totalNumberOfPathFiles__indices_ASSIGNMENT(index) NAMEOF_totalNumberOfPathFiles_index(index) = iTotalNumberOfPathFiles + index;
		MAKE_interior_indices_plus_totalNumberOfPathFiles(totalNumberOfPathFiles__indices_ASSIGNMENT);

		Offset_CPathFind__m_dwNumAddresses_index_TotalNumberOfPathFile = CPathFind::m_dwNumAddresses.GetOffset() + iTotalNumberOfPathFiles * sizeof(uint32_t*);
		Offset_CPathFind__m_dwNumCarPathLinks_index_TotalNumberOfPathFile = CPathFind::m_dwNumCarPathLinks.GetOffset() + iTotalNumberOfPathFiles * sizeof(uint32_t);
		Offset_CPathFind__m_dwNumPedNodes_index_TotalNumberOfPathFile = CPathFind::m_dwNumPedNodes.GetOffset() + iTotalNumberOfPathFiles * sizeof(uint32_t);
		Offset_CPathFind__m_dwNumVehicleNodes_index_TotalNumberOfPathFile = CPathFind::m_dwNumVehicleNodes.GetOffset() + iTotalNumberOfPathFiles * sizeof(uint32_t*);
		Offset_CPathFind__m_dwNumNodes_index_TotalNumberOfPathFile = CPathFind::m_dwNumNodes.GetOffset() + iTotalNumberOfPathFiles * sizeof(uint32_t*);

		Offset_CPathFind__pPathIntersections_index_TotalNumberOfPathFile = CPathFind::m_pPathIntersections.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*);
		Offset_CPathFind__m_pLinkLengths_index_1 = CPathFind::m_pLinkLengths.GetOffset() + 1 * sizeof(void*);
		Offset_CPathFind__m_pLinkLengths_index_TotalNumberOfPathFile = CPathFind::m_pLinkLengths.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*);
		Offset_CPathFind__m_pNodeLinks_index_1 = CPathFind::m_pNodeLinks.GetOffset() + 1 * sizeof(void*);
		Offset_CPathFind__m_pNodeLinks_index_TotalNumberOfPathFile = CPathFind::m_pNodeLinks.GetOffset() + iTotalNumberOfPathFiles * sizeof(void*);
		Offset_CPathNode_index_1_m_dwFlags = SizeOfCPathNode + offsetof(CPathNode, m_dwFlags);

		iNumberOfPathFilesPerDimensionNegated = -iNumberOfPathFilesPerDimension;
		iNumberOfPathFilesPerDimensionTimes2Negated = -(iNumberOfPathFilesPerDimension * 2);
		iNumberOfPathFilesPerDimensionTimes2Plus1Negated = -(iNumberOfPathFilesPerDimension * 2 + 1);
		iNumberOfPathFilesPerDimensionTimes2Plus2Negated = -(iNumberOfPathFilesPerDimension * 2 + 2);
		iNumberOfPathFilesPerDimensionPlus1 = iNumberOfPathFilesPerDimension + 1;
		iNumberOfPathFilesPerDimension_multiplied_by_sizeof_CNodeAddress = iNumberOfPathFilesPerDimension * sizeof(CNodeAddress);
		iTotalNumberOfPathFilesNegatedCNodeAddressMask = (~iTotalNumberOfPathFilesMinusOne) & 0xFFFF;
		
		Offset_CPathFind__m_pPathNodes_divided_by_sizeOf_CNodeAddress_minus_NumberOfPathFilesPerDimension_minus_2 =
			(CPathFind::m_pPathNodes.standard.GetOffset() / sizeof(CNodeAddress)) - iNumberOfPathFilesPerDimension - 2;
	}
	#endif	

	// Patch pointers to ToBeStreamed
	#if TRUE
	{
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x67899C), ToBeStreamed.ptr);
	}
	#endif

	// Patch pointers to ToBeStreamedForScript
	#if TRUE
	{
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x678944), ToBeStreamedForScript.ptr);
	}
	#endif

	// Patch pointers to DontWanderGiven
	#if TRUE
	{
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x678DCC), DontWanderGiven.ptr);
	}
	#endif

	// Patch pointers to XCoorGiven
	#if TRUE
	{
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x6778FC), XCoorGiven.ptr);
	}
	#endif

	// Patch pointers to YCoorGiven
	#if TRUE
	{
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x677FAC), YCoorGiven.ptr);
	}
	#endif

	// Patch pointers to ZCoorGiven
	#if TRUE
	{
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x678A1C), ZCoorGiven.ptr);
	}
	#endif

	// Patch pointers to ConnectsToGiven
	#if TRUE
	{
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x679000), ConnectsToGiven.ptr);
	}
	#endif

	// Patch pointers to ThePaths
	#if TRUE
	{
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x677378), ThePaths.gta_sa);
	}
	#endif

	// Automatic patches
	#if TRUE
	if (!CPatch::IsDebugModeActive())
	{
		#include "PathsMapSize/GTA SA 2.0 ANDROID_ARMEABI_V7A/changes.cpp"
	}
	#endif

	// for debugging
	#ifdef ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA
	{
		/*
		Address_CCarCtrl__SteerAICarWithPhysics_OnlyMission_2F252C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F252C));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F2524),
			(void*)&debugging_CCarCtrl__SteerAICarWithPhysics_OnlyMission_2F2524
		);
		*/
		

		#include "PathsMapSizeDebugging/GTA SA 2.0 ANDROID_ARMEABI_V7A/changes.cpp"
	}
	#endif

	// Manual patches
	#if TRUE
	{
		// Loading and unloading
		if (!CPatch::IsDebugModeActive())
		{
			// loading and unloading
			#if 1
			{
				CPatch::RedirectMethod((uintptr_t)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN9CPathFind16LoadPathFindDataEP8RwStreami"
				), &CPathFind_extended::LoadPathFindData);

				CPatch::RedirectMethod((uintptr_t)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN9CPathFind18UnLoadPathFindDataEi"
				), &CPathFind_extended::UnLoadPathFindData);
			}
			#endif

			// Group
			#if 1
			{
			}
			#endif

			CPatch::RedirectMethod((uintptr_t)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN9CPathFind4InitEv"
			), &CPathFind_extended::Init);

			CPatch::RedirectMethod((uintptr_t)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN9CPathFind8ShutdownEv"
			), &CPathFind_extended::Shutdown);

			CPatch::RedirectMethod((uintptr_t)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN9CPathFind21LoadSceneForPathNodesE7CVector"
			), &CPathFind_extended::LoadSceneForPathNodes);
		}

		CPatch::RedirectMethod((uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN9CPathFind23ReturnInteriorNodeIndexEji"
		), &CPathFind_extended::ReturnInteriorNodeIndex);

		CPatch::RedirectMethod((uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN9CPathFind9CheckGridEv"
		), &CPathFind_extended::CheckGrid);

		Address_CPathFind__LoadPathFindData_31540A_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31540A));
		Address_CPathFind__LoadPathFindData_3153E8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3153E8));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3153E0),
			(void*)&patch_CPathFind__LoadPathFindData_3153E0
		);

		Address_CPathFind__DoPathSearch_315918_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315918));
		Address_CPathFind__DoPathSearch_315900_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315900));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3158F8),
			(void*)&patch_CPathFind__DoPathSearch_3158F8
		);

		Address_CPathFind__RecordNodesClosestToCoors_317B9C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317B9C));
		Address_CPathFind__RecordNodesClosestToCoors_317BA0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317BA0));
		Address_CPathFind__RecordNodesClosestToCoors_317B90_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317B90));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317B88),
			(void*)&patch_CPathFind__RecordNodesClosestToCoors_317B88
		);

		Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317EDE_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317EDE));
		Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317F96_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317F96));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317F84),
			(void*)&patch_CPathFind__FindNodeClosestToCoorsFavourDirection_317F84
		);

		Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317ECA_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317ECA));
		Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317EB6_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317EB6));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317EAC),
			(void*)&patch_CPathFind__FindNodeClosestToCoorsFavourDirection_317EAC
		);

		Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317F96_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317F96));
		Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317F3C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317F3C));
		Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317EDE_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317EDE));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317F32),
			(void*)&patch_CPathFind__FindNodeClosestToCoorsFavourDirection_317F32
		);

		Address_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEE4_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31AEE4));
		Address_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE68_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31AE68));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31AE5E),
			(void*)&patch_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE5E, 10
		);		

		Address_CPathFind__UpdateStreaming_31962A_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31962A));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3195E2),
			(void*)&patch_CPathFind__UpdateStreaming_3195E2
		);

		Address_CPathFind__LoadSceneForPathNodes_319E52_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319E52));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x319E48),
			(void*)&patch_CPathFind__LoadSceneForPathNodes_319E48
		);

		Address_CPathFind__IsWaterNodeNearby_31A0B2_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31A0B2));
		Address_CPathFind__IsWaterNodeNearby_31A102_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31A102));
		Address_CPathFind__IsWaterNodeNearby_31A0C0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31A0C0));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31A0B2),
			(void*)&patch_CPathFind__IsWaterNodeNearby_31A0B2
		);

		Address_CPathFind__FindParkingNodeInArea_31B54E_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31B54E));
		Address_CPathFind__FindParkingNodeInArea_31B4C2_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31B4C2));
		Address_CPathFind__FindParkingNodeInArea_31B492_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31B492));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31B4B6),
			(void*)&patch_CPathFind__FindParkingNodeInArea_31B4B6
		);

		Address_CPathFind__FindParkingNodeInArea_31B548_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31B548));
		Address_CPathFind__FindParkingNodeInArea_31B4E4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31B4E4));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31B4DA),
			(void*)&patch_CPathFind__FindParkingNodeInArea_31B4DA
		);

		Address_CPathFind__LoadSceneForPathNodes_319F5E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319F5E));
		Address_CPathFind__LoadSceneForPathNodes_18B35C_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18B35C));
		Address_CPathFind__LoadSceneForPathNodes_319F50_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319F50));
		Address_CPathFind__LoadSceneForPathNodes_319F66_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319F66));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x319F50),
			(void*)&patch_CPathFind__LoadSceneForPathNodes_319F50
		);

		Address_CPathFind__FindNodeClosestToCoors_315F20_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315F20));
		Address_CPathFind__FindNodeClosestToCoors_19BB40_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x19BB40));
		Address_CPathFind__FindNodeClosestToCoors_315EEE_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315EEE));
		Address_CPathFind__FindNodeClosestToCoors_315F26_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315F26));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x315EF0),
			(void*)&patch_CPathFind__FindNodeClosestToCoors_315EF0
		);

		Address_CPathFind__FindNodeClosestToCoors_315F78_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315F78));
		Address_CPathFind__FindNodeClosestToCoors_19BB40_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x19BB40));
		Address_CPathFind__FindNodeClosestToCoors_315F46_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315F46));
		Address_CPathFind__FindNodeClosestToCoors_315F7E_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315F7E));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x315F48),
			(void*)&patch_CPathFind__FindNodeClosestToCoors_315F48
		);

		Address_CPathFind__MarkRegionsForCoors_319566_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319566));
		Address_CPathFind__MarkRegionsForCoors_18B35C_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18B35C));
		Address_CPathFind__MarkRegionsForCoors_319558_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319558));
		Address_CPathFind__MarkRegionsForCoors_31956E_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31956E));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x319558),
			(void*)&patch_CPathFind__MarkRegionsForCoors_319558
		);

		Address_CPathFind__UpdateStreaming_319732_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319732));
		Address_CPathFind__UpdateStreaming_18B35C_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18B35C));
		Address_CPathFind__UpdateStreaming_319724_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319724));
		Address_CPathFind__UpdateStreaming_31973A_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31973A));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x319724),
			(void*)&patch_CPathFind__UpdateStreaming_319724
		);

		Address_CPathFind__UpdateStreaming_319842_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319842));
		Address_CPathFind__UpdateStreaming_18B35C_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18B35C));
		Address_CPathFind__UpdateStreaming_319834_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319834));
		Address_CPathFind__UpdateStreaming_31984A_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31984A));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x319834),
			(void*)&patch_CPathFind__UpdateStreaming_319834
		);

		// Group
		

		//// racing
		#if 0
		{
			Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4AE2_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F4AE2));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F4AD8),
				(void*)&patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4AD8
			);

			Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4A9E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F4A9E));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F4A94),
				(void*)&patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4A94
			);
			CPatch::NOPinstructions(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F4ADA), 4);

			Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4BA0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F4BA0));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F4B96),
				(void*)&patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4B96
			);

			Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4BC8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F4BC8));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F4BBE),
				(void*)&patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4BBE
			);

			Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4D7C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F4D7C));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F4D72),
				(void*)&patch_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4D72
			);

			// More of CCarCtrl::SteerAICarWithPhysicsFollowPath remains to do
			//////////////////////////////////////////////////////////
		}
		#endif
	}
	#endif
}
#endif

namespace Game_GTASA
{
	////////////
	MAKE_GTA_SA_CPATH_FIND(CPathFind, STRUCTURE_STATIC_MEMBER_DEFINITION);
}

// Allocates CPathFind
void MapLimits::AllocateCPathFind(
	unsigned int iTotalNumberOfPathFiles,
	unsigned int iNumberOfPathInteriorSlots,
	unsigned int CPathFind_field_1544_numberOfElementsPerPathFile
)
{
	MAKE_VAR_GAME_VERSION();
	using namespace Game_GTASA;

	// Number of path indices
	this->iTotalNumberOfPathIndices = iTotalNumberOfPathFiles;

	// Number of path interior slots
	this->iNumberOfPathInteriorSlots = iNumberOfPathInteriorSlots;

	// Number of path indices including interior
	this->iTotalNumberOfPathIndicesIncludingInterior = iTotalNumberOfPathFiles + iNumberOfPathInteriorSlots;

	g_StructAllocator.InitPerStruct();
	g_StructAllocator.Allocate(CPathFind::m_info);

	#if PROJECT_IS_UNRELEASED_EDITION
	// g_StructAllocator.SkipBytes(0x100000);
	#endif

	g_StructAllocator.Allocate(CPathFind::m_apNodesSearchLists.extended, 512);
	g_StructAllocator.Allocate(CPathFind::m_pPathNodes.extended, iTotalNumberOfPathIndicesIncludingInterior);
	g_StructAllocator.Allocate(CPathFind::m_pNaviNodes.extended, iTotalNumberOfPathIndicesIncludingInterior);
	g_StructAllocator.Allocate(CPathFind::m_pNodeLinks, iTotalNumberOfPathIndicesIncludingInterior);
	g_StructAllocator.Allocate(CPathFind::m_pLinkLengths, iTotalNumberOfPathIndicesIncludingInterior);
	g_StructAllocator.Allocate(CPathFind::m_pPathIntersections, iTotalNumberOfPathIndicesIncludingInterior);

	if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		g_StructAllocator.Allocate(CPathFind::m_pNaviLinks.extended, iTotalNumberOfPathIndicesIncludingInterior);
		g_StructAllocator.Allocate(CPathFind::m_field_EA4, iTotalNumberOfPathIndicesIncludingInterior);
	}
	else
	{
		g_StructAllocator.Allocate(CPathFind::m_pNaviLinks.extended, iTotalNumberOfPathFiles);
		g_StructAllocator.Allocate(CPathFind::m_field_EA4, iTotalNumberOfPathFiles);
	}

	g_StructAllocator.Allocate(CPathFind::m_dwNumNodes, iTotalNumberOfPathIndicesIncludingInterior);
	g_StructAllocator.Allocate(CPathFind::m_dwNumVehicleNodes, iTotalNumberOfPathIndicesIncludingInterior);
	g_StructAllocator.Allocate(CPathFind::m_dwNumPedNodes, iTotalNumberOfPathIndicesIncludingInterior);
	g_StructAllocator.Allocate(CPathFind::m_dwNumCarPathLinks, iTotalNumberOfPathIndicesIncludingInterior);
	g_StructAllocator.Allocate(CPathFind::m_dwNumAddresses, iTotalNumberOfPathIndicesIncludingInterior);
	g_StructAllocator.Allocate(CPathFind::m_field_1544, 2 * iTotalNumberOfPathFiles * CPathFind_field_1544_numberOfElementsPerPathFile);
	g_StructAllocator.Allocate(CPathFind::m_dwTotalNumNodesInSearchList);
	g_StructAllocator.Allocate(CPathFind::m_interiorAreaIDarray, iNumberOfPathInteriorSlots);
	g_StructAllocator.Allocate(CPathFind::m_dwNumForbiddenAreas);
	g_StructAllocator.Allocate(CPathFind::m_aForbiddenAreas, iTotalNumberOfPathFiles);
	g_StructAllocator.Allocate(CPathFind::m_bForbiddenForScriptedCarsEnabled);
	g_StructAllocator.Allocate(CPathFind::m_fForbiddenForScrCarsX1);
	g_StructAllocator.Allocate(CPathFind::m_fForbiddenForScrCarsX2);
	g_StructAllocator.Allocate(CPathFind::m_fForbiddenForScrCarsY1);
	g_StructAllocator.Allocate(CPathFind::m_fForbiddenForScrCarsY2);

	#ifdef ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA
	if (CPatch::IsInitialized() && !CPatch::IsDebugModeActive())
	{
		g_StructAllocator.Allocate(CPathFind::m_pPathNodesStandard, iTotalNumberOfPathIndicesIncludingInterior);
		g_StructAllocator.Allocate(CPathFind::m_pNaviNodesStandard, iTotalNumberOfPathIndicesIncludingInterior);
	}
	#endif

	g_StructAllocator.Allocate(CPathFind::endOfStructure);
}

// Patches paths
void MapLimits::PatchPaths()
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();
	
	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
	this->PatchPaths_GTA_SA_PC_1_0_HOODLUM();
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	this->PatchPaths_GTA_SA_2_0_ANDROID_ARM32();
	#endif

	CPatch::LeaveThisLevel();
}

namespace Game_GTASA
{
	extern "C"
	{
		// Function to debug paths
		void DebugPaths()
		{
			MAKE_VAR_GAME_VERSION();
			MapLimits* pMapLimits = &g_mapLimits;

			if (!pNaviNodePositions)
			{
				pNaviNodePositions = new CVector*[pMapLimits->iTotalNumberOfPathIndicesIncludingInterior];
				memset(pNaviNodePositions, NULL, pMapLimits->iTotalNumberOfPathIndicesIncludingInterior * sizeof(CVector*));
			}

			CVector pos; // = { 2494.2505, -1682.1038, 13.3384 };
			CVector dir = { 0 };

			static const CRGBA pathPedNodeColor = { 255, 0, 255, 255 };
			static const CRGBA pathVehicleNodeColor = { 0, 0, 255, 255 };

			static const CRGBA pathPedLineColor = { 255, 128, 0, 255 };
			static const CRGBA pathVehicleLineColor = { 38, 127, 0, 255 };

			static const CRGBA naviNodeColor = { 38, 127, 0, 255 };
			static const CRGBA naviLineColor = { 1, 254, 7, 255 };
			static const CRGBA naviLineDirectionColor = { 0, 0, 0, 255 };
			
			/*
			#if FALSE
			{
				CCoronas::RegisterCorona(83,
					NULL,
					255, 0, 0,
					255,
					pos,
					1.0,
					500.0,
					CORONATYPE_RING_B,
					false, false, false, NULL,
					0.0,
					false,
					1.5,
					false,
					15.0,
					false,
					false
					);

				return;
			}
			#endif
			*/

			CVector playerPos = FindPlayerCoors(-1);

			// printf_MessageBox("player %.3f %.3f %.3f", playerPos.x, playerPos.y, playerPos.z);
			bool bPathsPatchEnabled = pMapLimits->ms_bPathsPatchEnabled;
			CPathFind_extended* ThePaths = pMapLimits->ThePaths.gta_sa;

			unsigned int coronaID = 200;

			float maxNodeDrawnDistance = 350.0;

			#ifdef IS_PLATFORM_ANDROID_ARM32
			maxNodeDrawnDistance = 45.0;
			#endif

			double distance;

			// path nodes
			for (unsigned int i = 0; i < pMapLimits->iTotalNumberOfPathIndicesIncludingInterior; i++)
			{
				if (ThePaths->m_pPathNodes.extended(ThePaths)[i])
				{
					unsigned int numberOfNodesForThisFile = ThePaths->m_dwNumNodes(ThePaths)[i];
					unsigned int numberOfVehicleNodesForThisFile = ThePaths->m_dwNumVehicleNodes(ThePaths)[i];

					for (unsigned int j = 0; j < numberOfNodesForThisFile; j++)
					{
						if (bPathsPatchEnabled)
						{
							CPathNode_extended_latest* pNode = &ThePaths->m_pPathNodes.extended(ThePaths)[i][j];
							pNode->GetPosition(pos);
						}
						else
						{
							CPathNode* pNode = &ThePaths->m_pPathNodes.standard(ThePaths)[i][j];
							pNode->GetPosition(pos);
						}

						distance = sqrt(
							(playerPos.x - pos.x) * (playerPos.x - pos.x)
							+ (playerPos.y - pos.y) * (playerPos.y - pos.y)
							+ (playerPos.z - pos.z) * (playerPos.z - pos.z)
						);

						if (distance < maxNodeDrawnDistance)
						{
							const CRGBA* pColor;

							if (j < numberOfVehicleNodesForThisFile)
								pColor = &pathVehicleNodeColor;
							else
								pColor = &pathPedNodeColor;

							// CPointLights::AddLight(0, pos, dir, 10.0, 1.0, 0, 0, true, false, NULL);

							CCoronas::RegisterCorona(coronaID++,
								NULL,
								pColor->red, pColor->green, pColor->blue, pColor->alpha,
								pos,
								1.0,
								3000.0,
								CORONATYPE_REFLECTION,
								false, false, false, NULL,
								0.0,
								false,
								1.5,
								false,
								15.0,
								false,
								false
							);
						}
					}
				}
			}

			// navi nodes
			bool bNeedToUpdateNaviNodePositions = (*CTimer::m_snTimeInMilliseconds - TimeOfLastNaviNodeUpdate) > 5000;

			/*
			if (bNeedToUpdateNaviNodePositions)
			{
				static int x = 0;
				OutputFormattedDebugString("update positions: %d", x++);
			}
			*/

			if (bNeedToUpdateNaviNodePositions)
				TimeOfLastNaviNodeUpdate = *CTimer::m_snTimeInMilliseconds;

			for (unsigned int i = 0; i < pMapLimits->iTotalNumberOfPathIndicesIncludingInterior; i++)
			{
				if (ThePaths->m_pNaviNodes.extended(ThePaths)[i])
				{
					unsigned int numberOfNaviNodesForThisFile = ThePaths->m_dwNumVehicleNodes(ThePaths)[i];

					bool bThereAreNoNaviNodePositionsForThisFile = false;

					if (!pNaviNodePositions[i])
					{
						pNaviNodePositions[i] = new CVector[numberOfNaviNodesForThisFile];
						bThereAreNoNaviNodePositionsForThisFile = true;
					}

					if (bNeedToUpdateNaviNodePositions || bThereAreNoNaviNodePositionsForThisFile)
					{
						for (unsigned int j = 0; j < numberOfNaviNodesForThisFile; j++)
						{
							if (bPathsPatchEnabled)
							{
								CCarPathLink_extended_latest* pNode = &ThePaths->m_pNaviNodes.extended(ThePaths)[i][j];
								pos.x = (float)pNode->CoorsExtended.x / PATH_COORD_MULTIPLIER;
								pos.y = (float)pNode->CoorsExtended.y / PATH_COORD_MULTIPLIER;
							}
							else
							{
								CCarPathLink* pNode = &ThePaths->m_pNaviNodes.standard(ThePaths)[i][j];

								pos.x = (float)pNode->Coors.x / PATH_COORD_MULTIPLIER;
								pos.y = (float)pNode->Coors.y / PATH_COORD_MULTIPLIER;
							}

							// CWorld::FindGroundZForCoord
							pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);

							pNaviNodePositions[i][j] = pos;
						}
					}

					for (unsigned int j = 0; j < numberOfNaviNodesForThisFile; j++)
					{
						pos = pNaviNodePositions[i][j];
						distance = sqrt(
							(playerPos.x - pos.x) * (playerPos.x - pos.x)
							+ (playerPos.y - pos.y) * (playerPos.y - pos.y)
							+ (playerPos.z - pos.z) * (playerPos.z - pos.z)
						);

						if (
							distance < maxNodeDrawnDistance
							)
						{
							const CRGBA* pColor = &naviNodeColor;

							// CPointLights::AddLight(0, pos, dir, 10.0, 1.0, 0, 0, true, false, NULL);
							CCoronas::RegisterCorona(coronaID++,
								NULL,
								pColor->red, pColor->green, pColor->blue, pColor->alpha,
								pos,
								1.0,
								3000.0,
								CORONATYPE_REFLECTION,
								false, false, false, NULL,
								0.0,
								false,
								1.5,
								false,
								15.0,
								false,
								false
							);
						}
					}
				}
			}

			// OutputFormattedDebugString("number of coronas: %d", *(unsigned int*)g_mCalc.GetCurrentVAbyPreferedVA(0xA25B40));
		}
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CGame__Process_53C05C()
	{
		__asm
		{
			call DebugPaths;

			push returnHere;

			push 0x73A360;	// CWeapon::UpdateWeapons
			retn;

		returnHere:
			push 0x53C061;
			retn;
		}
	}
	#endif

	extern "C"
	{
		uintptr_t Address_CWeapon__UpdateWeapons = 0;
		uintptr_t Address_CCutsceneMgr__ms_running = 0;
		uintptr_t Address_CGame__Process_3F4118 = 0;
	}

	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
	TARGET_THUMB NAKED void patch_CGame__Process_3F410E()
	{
		__asm
		(
			".thumb\n"
			ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(Address_CWeapon__UpdateWeapons)

			"BLX DebugPaths\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CCutsceneMgr__ms_running)

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CGame__Process_3F4118)
			);
	}
	#endif
}

// Applies path debugging
void MapLimits::ApplyPathDebugging()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
	using namespace Game_GTASA;

	CPatch::RedirectCode(0x53C05C, &patch_CGame__Process_53C05C);
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
	using namespace Game_GTASA;

	Address_CWeapon__UpdateWeapons = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN7CWeapon13UpdateWeaponsEv"
	);

	Address_CCutsceneMgr__ms_running = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZN12CCutsceneMgr10ms_runningE"
	);

	/////////////

	Address_CGame__Process_3F4118 = (uintptr_t)g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3F4118));

	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3F410E), (void*)&patch_CGame__Process_3F410E);
	}
	#endif
	else
	return;

	CGenericLogStorage::SaveFormattedTextLn("Path debugging enabled.");
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_CTrain__InitTrains_6F7521()
	{
		__asm
		{
			mov edx, eax;
			imul edx, SIZE CTrainNodeExtended;
			movzx   eax, word ptr[ebx + edx + CTrainNode::RailDistance];

			push 0x6F7529;
			retn;
		}
	}

	NAKED void patch_CTrain__GetRailDistanceCoordinates_6F5A27()
	{
		__asm
		{
			mov eax, edx;
			imul eax, SIZE CTrainNodeExtended;
			movzx eax, [eax + ebp + CTrainNode::RailDistance];

			push 0x6F5A2F;
			retn;
		}
	}

	NAKED void patch_CTrain__GetRailDistanceCoordinates_6F5A78()
	{
		__asm
		{
			mov eax, edx;
			imul eax, SIZE CTrainNodeExtended;
			lea     eax, [ebp + eax];

			push 0x6F5A7F;
			retn;
		}
	}

	NAKED void patch_CTrain__GetRailDistanceCoordinates_6F5A9C()
	{
		__asm
		{
			imul ecx, SIZE CTrainNodeExtended;

			#ifdef CTRAIN_NODE_USE_EXPOS
			mov   edx, [ebp + ecx + CTrainNodeExtended::exPos + CompressedVector_extended::x];
			#else
			movsx   edx, word ptr[ebp + ecx + CTrainNode::Pos + CompressedVector::x];
			#endif

			mov eax, ecx;

			push 0x6F5AA4;
			retn;
		}
	}

	NAKED void patch_CTrain__GetRailDistanceCoordinates_6F5AB2()
	{
		__asm
		{
			mov eax, ecx;

			#ifdef CTRAIN_NODE_USE_EXPOS
			mov   edx, [ebp + ecx + CTrainNodeExtended::exPos + CompressedVector_extended::y];
			#else
			movsx   edx, word ptr[ebp + ecx + CTrainNode::Pos + CompressedVector::y];
			#endif

			push 0x6F5ABA;
			retn;
		}
	}

	NAKED void patch_CTrain__RecalcOnRailDistance_6F6D40()
	{
		__asm
		{
			mov edi, edx;
			imul edi, SIZE CTrainNodeExtended;

			push 0x6F6D45;
			retn;
		}
	}

	NAKED void patch_CTrain__RecalcOnRailDistance_6F6F7D()
	{
		__asm
		{
			mov edi, ebx;
			imul edi, SIZE CTrainNodeExtended;
			movzx   edi, word ptr[eax + edi + CTrainNode::RailDistance];

			imul edx, SIZE CTrainNodeExtended;
			movzx   eax, word ptr[eax + edx + CTrainNode::RailDistance];

			push 0x6F6F8D;
			retn;
		}
	}

	NAKED void patch_CTrain__CreateTrain_6F75BB()
	{
		__asm
		{
			imul eax, SIZE CTrainNodeExtended;
			movzx   eax, word ptr[edx + eax + CTrainNode::RailDistance];

			push 0x6F75C3;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessRandomTrains_6F7B8F()
	{
		__asm
		{
			mov eax, edx;
			imul eax, SIZE CTrainNodeExtended;
			add eax, edi;

			push 0x6F7B95;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessRandomTrains_6F7C53()
	{
		__asm
		{
			mov ebx, edx;

			mov edx, eax;
			imul edx, SIZE CTrainNodeExtended;

			push 0x6F7C58;
			retn;

		}
	}

	NAKED void patch_CTrain__ProcessRandomTrains_6F7C64()
	{
		__asm
		{
			lea     eax, [ecx + edx];

			#ifdef CTRAIN_NODE_USE_EXPOS
			mov   edx, [eax + CTrainNodeExtended::exPos + CompressedVector_extended::x];
			#else
			movsx   edx, word ptr[eax + CTrainNode::Pos + CompressedVector::x];
			#endif

			push 0x6F7C6A;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessRandomTrains_6F7DC9()
	{
		__asm
		{
			imul ecx, SIZE CTrainNodeExtended;
			lea eax, [edx + ecx];

			#ifdef CTRAIN_NODE_USE_EXPOS
			mov   ecx, [eax + CTrainNodeExtended::exPos + CompressedVector_extended::x];
			#else
			movsx   ecx, word ptr[eax + CTrainNode::Pos + CompressedVector::x];
			#endif

			push 0x6F7DCF;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessRandomTrains_6F7F1C()
	{
		__asm
		{
			mov eax, edx;
			imul eax, SIZE CTrainNodeExtended;

			#ifdef CTRAIN_NODE_USE_EXPOS
			mov   ebp, [ebx + eax + CTrainNodeExtended::exPos + CompressedVector_extended::x];
			#else
			movsx   ebp, word ptr[ebx + eax + CTrainNode::Pos + CompressedVector::x];
			#endif

			lea     eax, [ebx + eax];

			push 0x6F7F26;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessRandomTrains_6F8011()
	{
		__asm
		{
			imul edx, SIZE CTrainNodeExtended;

			#ifdef CTRAIN_NODE_USE_EXPOS
			mov   ecx, [eax + edx + CTrainNodeExtended::exPos + CompressedVector_extended::x];
			#else
			movsx   ecx, word ptr[eax + edx + CTrainNode::Pos + CompressedVector::x];
			#endif

			add eax, edx;

			push 0x6F801B;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessRandomTrains_6F80CD()
	{
		__asm
		{
			mov eax, edx;
			imul eax, SIZE CTrainNodeExtended;

			#ifdef CTRAIN_NODE_USE_EXPOS
			mov   edi, [esi + eax + CTrainNodeExtended::exPos + CompressedVector_extended::x];
			#else
			movsx   edi, word ptr[esi + eax + CTrainNode::Pos + CompressedVector::x];
			#endif

			add eax, esi;

			push 0x6F80D7;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessControl_6F8D1B()
	{
		__asm
		{
			imul eax, SIZE CTrainNodeExtended;
			lea     ebp, [ecx + eax];

			push 0x6F8D21;
			retn;
		}
	}

	NAKED  void patch_CTrain__ProcessControl_6F8D2D()
	{
		__asm
		{
			push eax;
			mov ecx, ebx;
			imul ecx, SIZE CTrainNodeExtended;
			mov ebx, [esp + 0x90 - 0x70];
			lea eax, [esp + 0x90 - 0xC];
			push eax;
			lea     ecx, [ebx + ecx];

			push 0x6F8D40;
			retn;
		}
	}

	NAKED  void patch_CTrain__ProcessControl_6F8D5A()
	{
		__asm
		{
			mov ecx, edi;
			imul ecx, SIZE CTrainNodeExtended;
			push eax;
			add ecx, ebx;

			push 0x6F8D61;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessControl_6F8FF8()
	{
		__asm
		{
			mov eax, ecx;
			imul eax, SIZE CTrainNodeExtended;
			movzx   eax, word ptr[ebx + eax + CTrainNode::RailDistance];

			push 0x6F9000;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessControl_6F901E()
	{
		__asm
		{
			imul eax, SIZE CTrainNodeExtended;
			movzx   eax, word ptr[ebx + eax + CTrainNode::RailDistance];

			push 0x6F9026;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessControl_6F9064()
	{
		__asm
		{
			mov ecx, eax;
			imul ecx, SIZE CTrainNodeExtended;

			movzx eax, dx;

			imul eax, SIZE CTrainNodeExtended;
			lea ebp, [ebx + eax];
			movzx   eax, word ptr[ebp + CTrainNode::RailDistance];

			mov[esp + 0x8C - 0x64], eax;
			movzx   eax, word ptr[ebx + ecx + CTrainNode::RailDistance];
			fild dword ptr[esp + 0x8C - 0x64];
			add ecx, ebx;

			push 0x6F9084;
			retn;

		}
	}

	NAKED void patch_CTrain__ProcessControl_6F9174()
	{
		__asm
		{
			mov eax, ecx;
			imul eax, SIZE CTrainNodeExtended;

			movzx   eax, word ptr[ebx + eax + CTrainNode::RailDistance];

			push 0x6F917C;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessControl_6F91E1()
	{
		__asm
		{
			mov eax, ecx;
			imul eax, SIZE CTrainNodeExtended;
			movzx   eax, word ptr[ebx + eax + CTrainNode::RailDistance];

			push 0x6F91E9;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessControl_6F920A()
	{
		__asm
		{
			imul eax, SIZE CTrainNodeExtended;
			movzx   eax, word ptr[ebx + eax + CTrainNode::RailDistance];

			push 0x6F9212;
			retn;
		}
	}


	NAKED void patch_CTrain__ProcessControl_6F921F()
	{
		__asm
		{
			imul eax, SIZE CTrainNodeExtended;
			movzx   eax, word ptr[ebx + eax + CTrainNode::RailDistance];

			push 0x6F9227;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessControl_6F925A()
	{
		__asm
		{
			mov ecx, eax;
			imul ecx, SIZE CTrainNodeExtended;
			movzx eax, dx;
			mov edx, eax;
			imul edx, SIZE CTrainNodeExtended;
			movzx   eax, word ptr[ebx + edx + CTrainNode::RailDistance];
			lea     ebp, [ebx + edx];
			lea     edi, [ebx + ecx];

			push 0x6F926E;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessControl_6F95DF()
	{
		__asm
		{
			mov eax, ecx;
			imul eax, SIZE CTrainNodeExtended;
			movzx   eax, word ptr[ebx + eax + CTrainNode::RailDistance];

			push 0x6F95E7;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessControl_6F960E()
	{
		__asm
		{
			imul eax, SIZE CTrainNodeExtended;
			movzx   eax, word ptr[ebx + eax + CTrainNode::RailDistance];

			push 0x6F9616;
			retn;
		}
	}

	NAKED void patch_CTrain__ReadAndInterpretTrackFile_6F569E()
	{
		__asm
		{
			mov eax, esi;
			imul eax, SIZE CTrainNodeExtended;

			push 0x6F56A3;
			retn;
		}
	}

	NAKED void patch_CTrain__ReadAndInterpretTrackFile_6F583B()
	{
		__asm
		{

			mov eax, edx;
			imul eax, SIZE CTrainNodeExtended;

			add eax, esi;

			push 0x6F5841;
			retn;
		}
	}

	NAKED void patch_CTrain__ReadAndInterpretTrackFile_6F584C()
	{
		__asm
		{
			#ifdef CTRAIN_NODE_USE_EXPOS
			mov   edx, [edi + esi - SIZE CTrainNodeExtended + CTrainNodeExtended::exPos + CompressedVector_extended::x];
			#else
			movsx   edx, word ptr[edi + esi - SIZE CTrainNodeExtended + CTrainNode::Pos + CompressedVector::x];
			#endif

			push 0x6F5851;
			retn;
		}
	}


	#ifdef CTRAIN_NODE_USE_EXPOS
	NAKED void patch_CTrain__ReadAndInterpretTrackFile_6F5744()
	{
		__asm
		{
			mov[esi + ecx + CTrainNode::Pos + CompressedVector::x], ax;
			mov[esi + ecx + CTrainNodeExtended::exPos + CompressedVector_extended::x], eax;
			fld[esp + 0x40 - 0x2C];

			push 0x6F574C;
			retn;
		}
	}

	NAKED void patch_CTrain__ReadAndInterpretTrackFile_6F5759()
	{
		__asm
		{
			mov[esi + edx + CTrainNode::Pos + CompressedVector::y], ax;
			mov[esi + edx + CTrainNodeExtended::exPos + CompressedVector_extended::y], eax;

			fld[esp + 0x40 - 0x28];

			push 0x6F5762;
			retn;
		}
	}

	NAKED void patch_CTrain__ReadAndInterpretTrackFile_6F576F()
	{
		__asm
		{
			mov[esi + ecx + CTrainNode::Pos + CompressedVector::z], ax;
			mov[esi + ecx + CTrainNodeExtended::exPos + CompressedVector_extended::z], eax;

			push 0x6F5774;
			retn;
		}
	}
	#endif


	// For debugging
	void* CTrain__InitTrains_pTrackNodes;

	void* pExtendedTrackNodes[4] = { 0 };


	NAKED void patch_CTrain__ReadAndInterpretTrackFile_debugging_6F569E()
	{
		__asm
		{
			mov eax, esi;
			imul eax, SIZE CTrainNode;

			push 0x6F56A3;
			retn;
		}
	}

	NAKED void patch_CTrain__ReadAndInterpretTrackFile_debugging_6F583B()
	{
		__asm
		{

			mov eax, edx;
			imul eax, SIZE CTrainNode;

			add eax, esi;

			push 0x6F5841;
			retn;
		}
	}

	NAKED void patch_CTrain__ReadAndInterpretTrackFile_debugging_6F584C()
	{
		__asm
		{
			movsx   edx, word ptr[edi + esi - SIZE CTrainNode + CTrainNode::Pos + CompressedVector::x];

			push 0x6F5851;
			retn;
		}
	}

	NAKED void __cdecl patch_6F7440()
	{
		__asm
		{
			push ecx;
			mov eax, CTrain__InitTrains_pTrackNodes;
			mov eax, [eax];

			push 0x6F7446;
			retn;
		}
	}

	NAKED void patch_CTrain__CreateTrain_debugging_6F75BB()
	{
		__asm
		{
			imul eax, SIZE CTrainNode;
			movzx   eax, word ptr[edx + eax + CTrainNode::RailDistance];

			push 0x6F75C3;
			retn;
		}
	}

	NAKED void patch_CTrain__InitTrains_debugging_6F7521()
	{
		__asm
		{
			mov edx, eax;
			imul edx, SIZE CTrainNode;
			movzx   eax, word ptr[ebx + edx + CTrainNode::RailDistance];

			push 0x6F7529;
			retn;
		}
	}

	void Perform_CTrain__InitTrains_defaultSize()
	{
		using namespace Game_GTASA;
		void** pTrackNodes = g_mapLimits.pTrackNodes.ptr;
		CPatch::PatchPointer(0x6F7466 + 1, pTrackNodes);	// push    offset pTrackNodes	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F7478 + 2, pTrackNodes + 1);	// cmp     ds:pTrackNodes+4, ebx	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F748C + 1, pTrackNodes + 1);	// push    (offset pTrackNodes+4)	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F749E + 2, pTrackNodes + 2);	// cmp     ds:pTrackNodes+8, ebx	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F74B2 + 1, pTrackNodes + 2);	// push    (offset pTrackNodes+8)	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F74C4 + 2, pTrackNodes + 3);	// cmp     ds:pTrackNodes+0Ch, ebx	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F74D8 + 1, pTrackNodes + 3);	// push    (offset pTrackNodes+0Ch); float	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F74EA + 2, pTrackNodes);	// mov     ebx, ds:pTrackNodes	; _ZN6CTrain10InitTrainsEv

		// CTrain::FindClosestTrackNode		
		CPatch::PatchPointer(0x6F6C03 + 3, pTrackNodes);	// mov     eax, ds:pTrackNodes[esi*4]	; _ZN6CTrain20FindClosestTrackNodeE7CVectorPi
		CPatch::PatchUINT8(0x6F6C9B + 2, sizeof(CTrainNode));	// add     edx, size CTrainNode

		CPatch::RedirectCode(0x6F569E, &patch_CTrain__ReadAndInterpretTrackFile_debugging_6F569E);
		CPatch::PatchUINT8(0x6F56C2 + 1, sizeof(CTrainNode));	// push 0xA
		CPatch::PatchUINT8(0x6F57C8 + 2, sizeof(CTrainNode));	// add     esi, size CTrainNode
		CPatch::PatchUINT8(0x6F5837 + 2, sizeof(CTrainNode));	// add edi, 0xA
		CPatch::RedirectCode(0x6F583B, &patch_CTrain__ReadAndInterpretTrackFile_debugging_6F583B);
		CPatch::RedirectCode(0x6F584C, &patch_CTrain__ReadAndInterpretTrackFile_debugging_6F584C);

		// CTrain::CreateTrain
		CPatch::RedirectCode(0x6F75BB, &patch_CTrain__CreateTrain_debugging_6F75BB);
		CPatch::PatchPointer(0x6F75B4 + 3, pTrackNodes);	// mov     edx, ds:pTrackNodes[ecx*4]	; CTrain__CreateTrain

		// CTrain::InitTrains
		CPatch::RedirectCode(0x6F7521, &patch_CTrain__InitTrains_debugging_6F7521);

		CTrain__InitTrains_pTrackNodes = (void*)0xC38024;
		patch_6F7440();	// CTrain::InitTrains
	}

	void Perform_CTrain__InitTrains_extendedSize()
	{
		CPatch::PatchPointer(0x6F7466 + 1, pExtendedTrackNodes);	// push    offset pTrackNodes	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F7478 + 2, pExtendedTrackNodes + 1);	// cmp     ds:pTrackNodes+4, ebx	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F748C + 1, pExtendedTrackNodes + 1);	// push    (offset pTrackNodes+4)	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F749E + 2, pExtendedTrackNodes + 2);	// cmp     ds:pTrackNodes+8, ebx	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F74B2 + 1, pExtendedTrackNodes + 2);	// push    (offset pTrackNodes+8)	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F74C4 + 2, pExtendedTrackNodes + 3);	// cmp     ds:pTrackNodes+0Ch, ebx	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F74D8 + 1, pExtendedTrackNodes + 3);	// push    (offset pTrackNodes+0Ch); float	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F74EA + 2, pExtendedTrackNodes);	// mov     ebx, ds:pTrackNodes	; _ZN6CTrain10InitTrainsEv

		// CTrain::FindClosestTrackNode		
		CPatch::PatchPointer(0x6F6C03 + 3, pExtendedTrackNodes);	// mov     eax, ds:pTrackNodes[esi*4]	; _ZN6CTrain20FindClosestTrackNodeE7CVectorPi
		CPatch::PatchUINT8(0x6F6C9B + 2, sizeof(CTrainNodeExtended));	// add     edx, size CTrainNode		

		// CTrain::ReadAndInterpretTrackFile
		CPatch::RedirectCode(0x6F569E, &patch_CTrain__ReadAndInterpretTrackFile_6F569E);
		CPatch::PatchUINT8(0x6F56C2 + 1, sizeof(CTrainNodeExtended));	// push 0xA
		CPatch::PatchUINT8(0x6F57C8 + 2, sizeof(CTrainNodeExtended));	// add     esi, size CTrainNode
		CPatch::PatchUINT8(0x6F5837 + 2, sizeof(CTrainNodeExtended));	// add edi, 0xA
		CPatch::RedirectCode(0x6F583B, &patch_CTrain__ReadAndInterpretTrackFile_6F583B);
		CPatch::RedirectCode(0x6F584C, &patch_CTrain__ReadAndInterpretTrackFile_6F584C);

		// CTrain::CreateTrain			
		CPatch::RedirectCode(0x6F75BB, patch_CTrain__CreateTrain_6F75BB);
		CPatch::PatchPointer(0x6F75B4 + 3, pExtendedTrackNodes);	// mov     edx, ds:pTrackNodes[ecx*4]	; CTrain__CreateTrain		

		/*
		CPatch::RedirectCode(0x6F75BB, &patch_CTrain__CreateTrain_debugging_6F75BB);
		CPatch::PatchPointer(0x6F75B4 + 3, pTrackNodes);	// mov     edx, ds:pTrackNodes[ecx*4]	; CTrain__CreateTrain
		*/

		// CTrain::InitTrains
		CPatch::RedirectCode(0x6F7521, &patch_CTrain__InitTrains_6F7521);

		CTrain__InitTrains_pTrackNodes = pExtendedTrackNodes;
		patch_6F7440();	// CTrain::InitTrains
	}

	void Perform_CTrain__InitTrains()
	{
		#if TRUE
		{
			Perform_CTrain__InitTrains_defaultSize();
			Perform_CTrain__InitTrains_extendedSize();
		}
		#else
		{
			Perform_CTrain__InitTrains_extendedSize();
			Perform_CTrain__InitTrains_defaultSize();
		}
		#endif
	}
}
#endif

// Patches tracks.dat coordinate limit
void MapLimits::PatchTracksDatCoordinateLimit()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();

	MAKE_DEAD_IF();

	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
	using namespace Game_GTASA;

	// Patch the size of CTrainNode
	#if TRUE
	{
		CPatch::EnterNewLevelAndDisableDebugState();

		// CTrain::InitTrains
		CPatch::RedirectCode(0x6F7521, &patch_CTrain__InitTrains_6F7521);

		CPatch::RedirectCode(0x6F5A27, &patch_CTrain__GetRailDistanceCoordinates_6F5A27);
		CPatch::RedirectCode(0x6F5A78, &patch_CTrain__GetRailDistanceCoordinates_6F5A78);
		CPatch::RedirectCode(0x6F5A9C, &patch_CTrain__GetRailDistanceCoordinates_6F5A9C);
		CPatch::RedirectCode(0x6F5AB2, &patch_CTrain__GetRailDistanceCoordinates_6F5AB2);

		// CTrain::FindClosestTrackNode
		CPatch::PatchUINT8(0x6F6C9B + 2, sizeof(CTrainNodeExtended));	// add     edx, size CTrainNode

		// CTrain::RecalcOnRailDistance
		CPatch::RedirectCode(0x6F6D40, &patch_CTrain__RecalcOnRailDistance_6F6D40);
		CPatch::RedirectCode(0x6F6F7D, &patch_CTrain__RecalcOnRailDistance_6F6F7D);
		CPatch::PatchUINT8(0x6F6F56 + 2, sizeof(CTrainNodeExtended));	// add     edx, size CTrainNode					

		CPatch::RedirectCode(0x6F75BB, patch_CTrain__CreateTrain_6F75BB);


		CPatch::RedirectCode(0x6F7B8F, &patch_CTrain__ProcessRandomTrains_6F7B8F);
		CPatch::RedirectCode(0x6F7C53, &patch_CTrain__ProcessRandomTrains_6F7C53);
		CPatch::RedirectCode(0x6F7C64, &patch_CTrain__ProcessRandomTrains_6F7C64);
		CPatch::PatchMemoryData(0x6F7DC0, "\x8b\xca\x90", 3);
		CPatch::RedirectCode(0x6F7DC9, &patch_CTrain__ProcessRandomTrains_6F7DC9);
		CPatch::RedirectCode(0x6F7F1C, &patch_CTrain__ProcessRandomTrains_6F7F1C);
		CPatch::RedirectCode(0x6F8011, &patch_CTrain__ProcessRandomTrains_6F8011);
		CPatch::RedirectCode(0x6F80CD, &patch_CTrain__ProcessRandomTrains_6F80CD);


		CPatch::RedirectCode(0x6F8D1B, &patch_CTrain__ProcessControl_6F8D1B);
		CPatch::RedirectCode(0x6F8D2D, &patch_CTrain__ProcessControl_6F8D2D);
		CPatch::RedirectCode(0x6F8D5A, &patch_CTrain__ProcessControl_6F8D5A);
		CPatch::RedirectCode(0x6F8FF8, &patch_CTrain__ProcessControl_6F8FF8);
		CPatch::RedirectCode(0x6F901E, &patch_CTrain__ProcessControl_6F901E);
		CPatch::RedirectCode(0x6F9064, &patch_CTrain__ProcessControl_6F9064);
		CPatch::RedirectCode(0x6F9174, &patch_CTrain__ProcessControl_6F9174);
		CPatch::RedirectCode(0x6F91E1, &patch_CTrain__ProcessControl_6F91E1);
		CPatch::RedirectCode(0x6F920A, &patch_CTrain__ProcessControl_6F920A);
		CPatch::RedirectCode(0x6F921F, &patch_CTrain__ProcessControl_6F921F);
		CPatch::RedirectCode(0x6F925A, &patch_CTrain__ProcessControl_6F925A);
		CPatch::RedirectCode(0x6F95DF, &patch_CTrain__ProcessControl_6F95DF);
		CPatch::RedirectCode(0x6F960E, &patch_CTrain__ProcessControl_6F960E);

		// CTrain::FindCoorsFromPositionOnTrack
		CPatch::PatchUINT8(0x6F5A69 + 2, sizeof(CTrainNodeExtended));	// add     ebx, size CTrainNode

		// CTrain::ReadAndInterpretTrackFile
		CPatch::RedirectCode(0x6F569E, &patch_CTrain__ReadAndInterpretTrackFile_6F569E);
		CPatch::PatchUINT8(0x6F56C2 + 1, sizeof(CTrainNodeExtended));	// push 0xA
		CPatch::PatchUINT8(0x6F57C8 + 2, sizeof(CTrainNodeExtended));	// add     esi, size CTrainNode
		CPatch::PatchUINT8(0x6F5837 + 2, sizeof(CTrainNodeExtended));	// add edi, 0xA
		CPatch::RedirectCode(0x6F583B, &patch_CTrain__ReadAndInterpretTrackFile_6F583B);
		CPatch::RedirectCode(0x6F584C, &patch_CTrain__ReadAndInterpretTrackFile_6F584C);

		// Debugging
		#if FALSE
		{
			CPatch::RedirectCode(0x6F7440, &Perform_CTrain__InitTrains);

			CPatch::PatchPointer(0x6F59FB + 3, pExtendedTrackNodes);	// mov     ebp, ds:pTrackNodes[eax*4]	; CTrain__GetRailDistanceCoordinates				

			CPatch::PatchPointer(0x6F6D08 + 2, pExtendedTrackNodes);	// mov     eax, ds:pTrackNodes[ecx]	; CTrain__RecalcOnRailDistance
			CPatch::PatchPointer(0x6F6EAE + 3, pExtendedTrackNodes);	// mov     ecx, ds:pTrackNodes[ecx*4]	; CTrain__RecalcOnRailDistance
			CPatch::PatchPointer(0x6F6F77 + 2, pExtendedTrackNodes);	// mov     eax, ds:pTrackNodes[ecx]	; CTrain__RecalcOnRailDistance

			CPatch::PatchPointer(0x6F75B4 + 3, pExtendedTrackNodes);	// mov     edx, ds:pTrackNodes[ecx*4]	; CTrain__CreateTrain

			CPatch::PatchPointer(0x6F7B70 + 3, pExtendedTrackNodes);	// mov     edi, ds:pTrackNodes[esi*4]	; CTrain__ProcessRandomTrains
			CPatch::PatchPointer(0x6F7C5D + 3, pExtendedTrackNodes);	// mov     ecx, ds:pTrackNodes[eax*4]	; CTrain__ProcessRandomTrains
			CPatch::PatchPointer(0x6F7DC3 + 2, pExtendedTrackNodes);	// mov     edx, ds:pTrackNodes[esi]	; CTrain__ProcessRandomTrains
			CPatch::PatchPointer(0x6F7EE6 + 3, pExtendedTrackNodes);	// mov     ebx, ds:pTrackNodes[esi*4]	; CTrain__ProcessRandomTrains
			CPatch::PatchPointer(0x6F8005 + 2, pExtendedTrackNodes);	// mov     eax, ds:pTrackNodes[esi]	; CTrain__ProcessRandomTrains
			CPatch::PatchPointer(0x6F8099 + 3, pExtendedTrackNodes);	// mov     esi, ds:pTrackNodes[ecx*4]	; CTrain__ProcessRandomTrains

			CPatch::PatchPointer(0x6F871A + 2, pExtendedTrackNodes);	// mov     ecx, ds:pTrackNodes[eax]	; _ZN6CTrain14ProcessControlEv

		}
		#endif


		CPatch::LeaveThisLevel();
	}
	#endif

	// Automatic patch
	#ifdef CTRAIN_NODE_USE_EXPOS
	{
		CCodeMover::SetVariable("CTRAIN_NODE_EXPOS_OFFSET", offsetof(CTrainNodeExtended, exPos));

		// Apply the automatic patch
		#if TRUE
		{
			// Count of active addresses: 49
			CCodeMover::FixOnAddress(0x6F5392, 7, "\x01\x01\x89\x01\x01\x46\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x01\x95\x53\x6F\x00\x02\x03\x96\x53\x6F\x00\x00", 0x6F5399);	// line 1, 0x6F5380 - sub_6F5380 : mov     [esi], ax
			CCodeMover::FixOnAddress(0x6F53B2, 5, "\x01\x01\x89\x01\x01\x46\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x01\xB6\x53\x6F\x00\x00", 0x6F53B7);	// line 2, 0x6F53A0 - sub_6F53A0 : mov     [esi+2], ax
			CCodeMover::FixOnAddress(0x6F53D2, 5, "\x01\x01\x89\x01\x01\x46\x0c\x01\x01\x08\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x01\xD6\x53\x6F\x00\x00", 0x6F53D7);	// line 3, 0x6F53C0 - sub_6F53C0 : mov     [esi+4], ax
			CCodeMover::FixOnAddress(0x6F53E1, 7, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\xE4\x53\x6F\x00\x00", 0x6F53E8);	// line 4, 0x6F53E0 - sub_6F53E0 : movsx   eax, word ptr [ecx]
			CCodeMover::FixOnAddress(0x6F5401, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\x05\x54\x6F\x00\x00", 0x6F5409);	// line 5, 0x6F5400 - sub_6F5400 : movsx   eax, word ptr [ecx+2]
			CCodeMover::FixOnAddress(0x6F5421, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x08\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\x25\x54\x6F\x00\x00", 0x6F5429);	// line 6, 0x6F5420 - sub_6F5420 : movsx   eax, word ptr [ecx+4]
			CCodeMover::FixOnAddress(0x6F5441, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x08\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x51\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x00", 0x6F5449);	// line 7, 0x6F5440 - sub_6F5440 : movsx   eax, word ptr [ecx+4]
			CCodeMover::FixOnAddress(0x6F544D, 7, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\x50\x54\x6F\x00\x00", 0x6F5454);	// line 8, 0x6F5440 - sub_6F5440 : movsx   eax, word ptr [ecx]
			CCodeMover::FixOnAddress(0x6F5744, 8, "\x01\x01\x89\x01\x02\x44\x0E\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\x48\x57\x6F\x00\x00", 0x6F574C);	// line 9, 0x6F55D0 - sub_6F55D0 : mov     [esi+ecx], ax
			CCodeMover::FixOnAddress(0x6F5759, 5, "\x01\x01\x89\x01\x02\x44\x16\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x00", 0x6F575E);	// line 10, 0x6F55D0 - sub_6F55D0 : mov     [esi+edx+2], ax
			CCodeMover::FixOnAddress(0x6F576F, 5, "\x01\x01\x89\x01\x02\x44\x0E\x0c\x01\x01\x08\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x00", 0x6F5774);	// line 11, 0x6F55D0 - sub_6F55D0 : mov     [esi+ecx+4], ax
			CCodeMover::FixOnAddress(0x6F581D, 5, "\x01\x01\x8B\x01\x02\x44\x37\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x00", 0x6F5822);	// line 12, 0x6F55D0 - sub_6F55D0 : movsx   eax, word ptr [edi+esi+2]
			CCodeMover::FixOnAddress(0x6F5841, 7, "\x01\x01\x8B\x01\x01\x50\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x40\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x00", 0x6F5848);	// line 13, 0x6F55D0 - sub_6F55D0 : movsx   edx, word ptr [eax+2]
			CCodeMover::FixOnAddress(0x6F5A7F, 7, "\x01\x01\x8B\x01\x01\x50\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\x82\x5A\x6F\x00\x00", 0x6F5A86);	// line 14, 0x6F59E0 - CTrain__GetRailDistanceCoordinates : movsx   edx, word ptr [eax]
			CCodeMover::FixOnAddress(0x6F5A86, 8, "\x01\x01\x8B\x01\x01\x50\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\x8A\x5A\x6F\x00\x00", 0x6F5A8E);	// line 15, 0x6F59E0 - CTrain__GetRailDistanceCoordinates : movsx   edx, word ptr [eax+2]
			CCodeMover::FixOnAddress(0x6F5A8E, 10, "\x01\x01\x8B\x01\x01\x40\x0c\x01\x01\x08\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x06\x92\x5A\x6F\x00\x00", 0x6F5A98);	// line 16, 0x6F59E0 - CTrain__GetRailDistanceCoordinates : movsx   eax, word ptr [eax+4]
			CCodeMover::FixOnAddress(0x6F5AC2, 10, "\x01\x01\x8B\x01\x01\x50\x0c\x01\x01\x08\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x06\xC6\x5A\x6F\x00\x00", 0x6F5ACC);	// line 17, 0x6F59E0 - CTrain__GetRailDistanceCoordinates : movsx   edx, word ptr [eax+4]
			CCodeMover::FixOnAddress(0x6F5F95, 7, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x00", 0x6F5F9C);	// line 18, 0x6F5F80 - sub_6F5F80 : movsx   eax, word ptr [esi]
			CCodeMover::FixOnAddress(0x6F5F9C, 8, "\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x08\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\xA0\x5F\x6F\x00\x00", 0x6F5FA4);	// line 19, 0x6F5F80 - sub_6F5F80 : movsx   edx, word ptr [esi+4]
			CCodeMover::FixOnAddress(0x6F6C0A, 6, "\x01\x01\x8B\x01\x02\x6C\x10\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x02\x0E\x6C\x6F\x00\x00", 0x6F6C10);	// line 20, 0x6F6BD0 - _ZN6CTrain20FindClosestTrackNodeE7CVectorPi : movsx   ebp, word ptr [eax+edx]
			CCodeMover::FixOnAddress(0x6F6C14, 8, "\x01\x01\x8B\x01\x01\x68\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\x18\x6C\x6F\x00\x00", 0x6F6C1C);	// line 21, 0x6F6BD0 - _ZN6CTrain20FindClosestTrackNodeE7CVectorPi : movsx   ebp, word ptr [eax+2]
			CCodeMover::FixOnAddress(0x6F6C1C, 10, "\x01\x01\x8B\x01\x01\x40\x0c\x01\x01\x08\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x06\x20\x6C\x6F\x00\x00", 0x6F6C26);	// line 22, 0x6F6BD0 - _ZN6CTrain20FindClosestTrackNodeE7CVectorPi : movsx   eax, word ptr [eax+4]
			CCodeMover::FixOnAddress(0x6F6D12, 6, "\x01\x01\x8B\x01\x02\x7C\x01\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x02\x16\x6D\x6F\x00\x00", 0x6F6D18);	// line 23, 0x6F6CC0 - CTrain__RecalcOnRailDistance : movsx   edi, word ptr [ecx+eax]
			CCodeMover::FixOnAddress(0x6F6D1C, 8, "\x01\x01\x8B\x01\x01\x79\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\x20\x6D\x6F\x00\x00", 0x6F6D24);	// line 24, 0x6F6CC0 - CTrain__RecalcOnRailDistance : movsx   edi, word ptr [ecx+2]
			CCodeMover::FixOnAddress(0x6F6D45, 9, "\x01\x01\x8B\x01\x02\x6C\x07\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x02\x44\x07\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x00", 0x6F6D4E);	// line 25, 0x6F6CC0 - CTrain__RecalcOnRailDistance : movsx   ebp, word ptr [edi+eax]
			CCodeMover::FixOnAddress(0x6F7B95, 7, "\x01\x01\x8B\x01\x01\x78\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x40\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x00", 0x6F7B9C);	// line 26, 0x6F7900 - CTrain__ProcessRandomTrains : movsx   edi, word ptr [eax]
			CCodeMover::FixOnAddress(0x6F7C6A, 8, "\x01\x01\x8B\x01\x01\x40\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\x6E\x7C\x6F\x00\x00", 0x6F7C72);	// line 27, 0x6F7900 - CTrain__ProcessRandomTrains : movsx   eax, word ptr [eax+2]
			CCodeMover::FixOnAddress(0x6F7DCF, 8, "\x01\x01\x8B\x01\x01\x50\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x40\x0c\x01\x01\x08\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x00", 0x6F7DD7);	// line 28, 0x6F7900 - CTrain__ProcessRandomTrains : movsx   edx, word ptr [eax+2]
			CCodeMover::FixOnAddress(0x6F7F26, 8, "\x01\x01\x8B\x01\x01\x40\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\x2A\x7F\x6F\x00\x00", 0x6F7F2E);	// line 29, 0x6F7900 - CTrain__ProcessRandomTrains : movsx   eax, word ptr [eax+2]
			CCodeMover::FixOnAddress(0x6F801B, 8, "\x01\x01\x8B\x01\x01\x50\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\x1F\x80\x6F\x00\x00", 0x6F8023);	// line 30, 0x6F7900 - CTrain__ProcessRandomTrains : movsx   edx, word ptr [eax+2]
			CCodeMover::FixOnAddress(0x6F80D7, 8, "\x01\x01\x8B\x01\x01\x40\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\xDB\x80\x6F\x00\x00", 0x6F80DF);	// line 31, 0x6F7900 - CTrain__ProcessRandomTrains : movsx   eax, word ptr [eax+2]
			CCodeMover::FixOnAddress(0x6F90B1, 6, "\x01\x01\x8B\x01\x01\x45\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x02\xB5\x90\x6F\x00\x00", 0x6F90B7);	// line 32, 0x6F86A0 - _ZN6CTrain14ProcessControlEv : movsx   eax, word ptr [ebp+0]
			CCodeMover::FixOnAddress(0x6F90BD, 5, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x02\xC0\x90\x6F\x00\x00", 0x6F90C2);	// line 33, 0x6F86A0 - _ZN6CTrain14ProcessControlEv : movsx   eax, word ptr [ecx]
			CCodeMover::FixOnAddress(0x6F90D2, 10, "\x01\x01\x8B\x01\x01\x45\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x06\xD6\x90\x6F\x00\x00", 0x6F90DC);	// line 34, 0x6F86A0 - _ZN6CTrain14ProcessControlEv : movsx   eax, word ptr [ebp+2]
			CCodeMover::FixOnAddress(0x6F90E6, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x49\x0c\x01\x01\x08\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x00", 0x6F90EE);	// line 35, 0x6F86A0 - _ZN6CTrain14ProcessControlEv : movsx   eax, word ptr [ecx+2]
			CCodeMover::FixOnAddress(0x6F9104, 10, "\x01\x01\x8B\x01\x01\x45\x0c\x01\x01\x08\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x06\x08\x91\x6F\x00\x00", 0x6F910E);	// line 36, 0x6F86A0 - _ZN6CTrain14ProcessControlEv : movsx   eax, word ptr [ebp+4]
			CCodeMover::FixOnAddress(0x6F92A3, 6, "\x01\x01\x8B\x01\x01\x55\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x02\xA7\x92\x6F\x00\x00", 0x6F92A9);	// line 37, 0x6F86A0 - _ZN6CTrain14ProcessControlEv : movsx   edx, word ptr [ebp+0]
			CCodeMover::FixOnAddress(0x6F92A9, 7, "\x01\x01\x8B\x01\x01\x47\x0c\x01\x01\x00\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x01\x01\x8B\x01\x01\x4F\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x00", 0x6F92B0);	// line 38, 0x6F86A0 - _ZN6CTrain14ProcessControlEv : movsx   eax, word ptr [edi]
			CCodeMover::FixOnAddress(0x6F92B6, 8, "\x01\x01\x8B\x01\x01\x55\x0c\x01\x01\x04\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x04\xBA\x92\x6F\x00\x00", 0x6F92BE);	// line 39, 0x6F86A0 - _ZN6CTrain14ProcessControlEv : movsx   edx, word ptr [ebp+2]
			CCodeMover::FixOnAddress(0x6F92D4, 10, "\x01\x01\x8B\x01\x01\x47\x0c\x01\x01\x08\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x06\xD8\x92\x6F\x00\x00", 0x6F92DE);	// line 40, 0x6F86A0 - _ZN6CTrain14ProcessControlEv : movsx   eax, word ptr [edi+4]
			CCodeMover::FixOnAddress(0x6F92E8, 10, "\x01\x01\x8B\x01\x01\x4D\x0c\x01\x01\x08\x02""CTRAIN_NODE_EXPOS_OFFSET\x00\x02\x06\xEC\x92\x6F\x00\x00", 0x6F92F2);	// line 41, 0x6F86A0 - _ZN6CTrain14ProcessControlEv : movsx   ecx, word ptr [ebp+4]
		}
		#endif

		// Debugging
		#if FALSE
		{
			CPatch::RedirectCode(0x6F5744, &patch_CTrain__ReadAndInterpretTrackFile_6F5744);
			CPatch::RedirectCode(0x6F5759, &patch_CTrain__ReadAndInterpretTrackFile_6F5759);
			CPatch::RedirectCode(0x6F576F, &patch_CTrain__ReadAndInterpretTrackFile_6F576F);
		}
		#endif

		// Delete variable of automatic patch
		CCodeMover::DeleteVariable("CTRAIN_NODE_EXPOS_OFFSET");
	}
	#endif
	}
	#endif

	CPatch::LeaveThisLevel();
}

// Patches tracks.dat file size limit
void MapLimits::PatchTracksDatFileSizeLimit()
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
	// Patch the limit
		{
			CPatch::PatchUINT32(0x6F55FA + 1, MapLimits::ms_tracksDatFileSizeLimit);	// push    46384
			CPatch::PatchUINT32(0x6F560F + 1, MapLimits::ms_tracksDatFileSizeLimit);	// push    46384           ; bifSize
		}
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
	{
	// Patch the limit
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x94A2B6 + 1), MapLimits::ms_tracksDatFileSizeLimit);	// push    76384
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x94A2C7 + 1), MapLimits::ms_tracksDatFileSizeLimit);  // push    76384
		}
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
	// Patch the limit
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xA4C476 + 1), MapLimits::ms_tracksDatFileSizeLimit);	// push    76384
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xA4C487 + 1), MapLimits::ms_tracksDatFileSizeLimit);  // push    76384
		}
	}
	#endif

	CPatch::LeaveThisLevel();
}

unsigned int CurrentNumberOfTrainStations = 0;

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_CTrain__GetDistanceToNextStation_6F5C52()
	{
		__asm
		{
			add     esi, 4;

			mov eax, CurrentNumberOfTrainStations;
			shl eax, 2;
			add eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_mapLimits, MapLimits, StationDist);
			cmp esi, eax;

			push 0x6F5C5B;
			retn;
		}
	}

	NAKED void patch_CTrain__InitTrains_6F753A()
	{
		__asm
		{
			mov eax, CurrentNumberOfTrainStations;
			imul eax, SIZE CVector;
			add eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_mapLimits, MapLimits, CTrain__aStationCoors);

			cmp esi, eax;

			push 0x6F7540;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessRandomTrains_6F7930()
	{
		__asm
		{
			mov esi, ASM_ACCESS_LIMIT_VAR_32_BIT(g_mapLimits, MapLimits, CTrain__aStationCoors);
			xor ebx, ebx;

			push 0x6F7935;
			retn;
		}
	}

	NAKED void patch_CTrain__ProcessRandomTrains_6F7972()
	{
		__asm
		{
			add esi, SIZE CVector;

			inc ebx;
			cmp ebx, CurrentNumberOfTrainStations;

			push 0x6F797B;
			retn;
		}
	}

	NAKED void patch_CTrain__GetNextStationInfo_6F5F15()
	{
		__asm
		{
			cmp ecx, CurrentNumberOfTrainStations;
			jl loc_6F5F02;

			push 0x6F5F21;
			retn;

		loc_6F5F02:
			push 0x6F5F02;
			retn;
		}
	}

	NAKED void patch__GetNextStationInfo_6F5F1C()
	{
		__asm
		{
			cmp ecx, CurrentNumberOfTrainStations;
			jl loc_6F5F23;

			push 0x6F5F21;
			retn;

		loc_6F5F23:
			push 0x6F5F23;
			retn;
		}
	}

	NAKED void patch__GetNextStationInfo_6F5F2C()
	{
		__asm
		{
			jns     loc_6F5F31;
			add ecx, CurrentNumberOfTrainStations;

		loc_6F5F31:
			push 0x6F5F31;
			retn;
		}
	}

	NAKED void patch__GetNextStationInfo_6F5F53()
	{
		__asm
		{
			test    ecx, ecx;
			jge     loc_6F5F5A;
			add ecx, CurrentNumberOfTrainStations;

		loc_6F5F5A:
			cmp ecx, CurrentNumberOfTrainStations;
			jl loc_6F5F61;
			xor ecx, ecx;

		loc_6F5F61:
			push 0x6F5F61;
			retn;
		}
	}

	NAKED void patch_CTrain__ReadAndInterpretTrackFile_6F5794()
	{
		__asm
		{
			mov eax, [CurrentNumberOfTrainStations];
			imul eax, SIZE CVector;
			add eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_mapLimits, MapLimits, CTrain__aStationCoors);

			inc[CurrentNumberOfTrainStations];

			mov[esp + 40h - 0x18], edx;
			push 0x6F579C;
			retn;
		}
	}

	NAKED void patch_CTrain__Shutdown_6F58F7()
	{
		__asm
		{
			mov CurrentNumberOfTrainStations, 0;
			retn;
		}
	}
}
#endif

// Patches max number of track stations
void MapLimits::PatchMaxNumberOfTrackStations()
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();		

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
	using namespace Game_GTASA;

	// Allocate memory
	if (CPatch::IsDebugModeActive())
		ms_MaxNumberOfTrackStations = 6;
	else if (ms_MaxNumberOfTrackStations > 6)
	{
		CTrain__aStationCoors.ptr = new CVector[ms_MaxNumberOfTrackStations];
		memset(CTrain__aStationCoors.ptr, NULL, ms_MaxNumberOfTrackStations * sizeof(CVector));
		CTrain__aStationCoors.bIsAllocated.Set(true);

		StationDist.ptr = new float[ms_MaxNumberOfTrackStations];
		memset(StationDist.ptr, NULL, ms_MaxNumberOfTrackStations * sizeof(float));
		StationDist.bIsAllocated.Set(true);
	}

	// Patch pointers to StationDist
	#if TRUE
	{
		CPatch::PatchPointer(0x6F5BE7 + 1, StationDist.ptr);	// mov     esi, offset StationDist	; CTrain__GetDistanceToNextStation
		CPatch::PatchPointer(0x6F5F02 + 3, StationDist.ptr);	// fld     ds:StationDist[ecx*4]	; sub_6F5F00
		CPatch::PatchPointer(0x6F5F35 + 3, StationDist.ptr);	// fsub    ds:StationDist[ecx*4]	; sub_6F5F00
		CPatch::PatchPointer(0x6F5F6B + 3, StationDist.ptr);	// mov     ecx, ds:StationDist[ecx*4]	; sub_6F5F00
		CPatch::PatchPointer(0x6F74F0 + 1, StationDist.ptr);	// mov     edi, offset StationDist	; sub_6F7446			
	}
	#endif

	// Patch pointer to CTrain::aStationCoors
	#if TRUE
	{
		CPatch::PatchPointer(0x6F56E6 + 4, CTrain__aStationCoors.ptr);	// mov     [esp+40h+var_24], offset _ZN6CTrain13aStationCoorsE; CTrain::aStationCoors	; _ZN6CTrain25ReadAndInterpretTrackFileEPcPP10CTrainNodePiPfi
		CPatch::PatchPointer(0x6F72B1 + 3, CTrain__aStationCoors.ptr);	// lea     edx, _ZN6CTrain13aStationCoorsE.x[ecx*4]; CTrain::aStationCoors	; sub_6F7260
		CPatch::PatchPointer(0x6F735D + 3, CTrain__aStationCoors.ptr);	// lea     eax, _ZN6CTrain13aStationCoorsE.x[edx*4]; CTrain::aStationCoors	; sub_6F72F0
		CPatch::PatchPointer(0x6F73D7 + 3, CTrain__aStationCoors.ptr);	// lea     edi, _ZN6CTrain13aStationCoorsE.x[eax*4]; CTrain::aStationCoors	; sub_6F72F0
		CPatch::PatchPointer(0x6F74F5 + 1, CTrain__aStationCoors.ptr);	// mov     esi, offset _ZN6CTrain13aStationCoorsE; CTrain::aStationCoors	; sub_6F7446
		CPatch::PatchPointer(0x6F7930 + 1, CTrain__aStationCoors.ptr);	// mov     esi, offset _ZN6CTrain13aStationCoorsE; CTrain::aStationCoors	; CTrain__ProcessRandomTrains
	}
	#endif


	// Code
	#if TRUE
	{
		CPatch::RedirectCode(0x6F5C52, &patch_CTrain__GetDistanceToNextStation_6F5C52);

		CPatch::RedirectCode(0x6F753A, &patch_CTrain__InitTrains_6F753A);
		CPatch::RedirectCode(0x6F7930, &patch_CTrain__ProcessRandomTrains_6F7930);
		CPatch::RedirectCode(0x6F7972, &patch_CTrain__ProcessRandomTrains_6F7972);

		CPatch::RedirectCode(0x6F5F15, &patch_CTrain__GetNextStationInfo_6F5F15);
		CPatch::RedirectCode(0x6F5F1C, &patch__GetNextStationInfo_6F5F1C);
		CPatch::RedirectCode(0x6F5F2C, &patch__GetNextStationInfo_6F5F2C);
		CPatch::RedirectCode(0x6F5F53, &patch__GetNextStationInfo_6F5F53);

		CPatch::NOPinstructions(0x6F56E6, 8);
		CPatch::RedirectCode(0x6F5794, &patch_CTrain__ReadAndInterpretTrackFile_6F5794);
		CPatch::NOPinstructions(0x6F57B9, 4);

		CPatch::RedirectCode(0x6F58F7, &patch_CTrain__Shutdown_6F58F7);
	}
	#endif
	}
	#endif

	CPatch::LeaveThisLevel();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	// Reads track files
	static void ReadTrackFiles()
	{
		char path[MAX_PATH];

		MapLimits* pMapLimits = &g_mapLimits;

		for (unsigned int trackID = 0; trackID < pMapLimits->ms_NumberOfTracksDatFiles; trackID++)
		{
			if (pMapLimits->pTrackNodes.ptr[trackID])
				continue;

			sprintf(path, "data\\paths\\%s", TrackFilenameLoader.m_vecTrackFilenames[trackID].c_str());

			// CTrain::ReadAndInterpretTrackFile
			((void(__cdecl*)(
				const char *filename,
				void **data,
				unsigned int* lineCount,
				float *RailDistance,
				int TrackID))
				0x6F55D0)
				(
					path,
					&pMapLimits->pTrackNodes.ptr[trackID],
					&pMapLimits->NumTrackNodes.ptr[trackID],
					&pMapLimits->TrainTrackDistance.ptr[trackID],
					trackID
					);
		}
	}

	NAKED void patch_CTrain__InitTrains_6F7459()
	{
		__asm
		{
			call ReadTrackFiles;

			push 0x6F74EA;
			retn;
		}
	}
}
#endif

// Patches number of tracks.dat files
void MapLimits::PatchNumberOfTracksDatFiles()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
	using namespace Game_GTASA;

	auto filenamePath = g_LimitAdjuster.GetPathToFlaFileFromRootDirectory("data\\Paths\\gtasa_tracks_config.dat");

	TrackFilenameLoader.Load(filenamePath.c_str());

	ms_NumberOfTracksDatFiles = TrackFilenameLoader.m_vecTrackFilenames.size();

	// Allocate memory
	#if TRUE
	if (this->ms_NumberOfTracksDatFiles > 4)
	{
		pTrackNodes.ptr = new void*[ms_NumberOfTracksDatFiles];
		memset(pTrackNodes.ptr, NULL, ms_NumberOfTracksDatFiles * sizeof(void*));
		pTrackNodes.bIsAllocated.Set(true);

		TrainTrackDistance.ptr = new float[ms_NumberOfTracksDatFiles];
		memset(TrainTrackDistance.ptr, NULL, ms_NumberOfTracksDatFiles * sizeof(float));
		TrainTrackDistance.bIsAllocated.Set(true);

		NumTrackNodes.ptr = new unsigned int[ms_NumberOfTracksDatFiles];
		memset(NumTrackNodes.ptr, NULL, ms_NumberOfTracksDatFiles * sizeof(unsigned int));
		NumTrackNodes.bIsAllocated.Set(true);
	}
	#endif

	// Patch pointers to pTrackNodes
	#if TRUE
	{
		CPatch::PatchPointer(0x6F58D1 + 1, pTrackNodes.ptr);	// mov     esi, offset pTrackNodes	; _ZN6CTrain8ShutdownEv
		CPatch::PatchPointer(0x6F58EE + 2, pTrackNodes.ptr + ms_NumberOfTracksDatFiles);	// cmp     esi, offset StationDist	; _ZN6CTrain8ShutdownEv
		CPatch::PatchPointer(0x6F59FB + 3, pTrackNodes.ptr);	// mov     ebp, ds:pTrackNodes[eax*4]	; CTrain__GetRailDistanceCoordinates
		CPatch::PatchPointer(0x6F6C03 + 3, pTrackNodes.ptr);	// mov     eax, ds:pTrackNodes[esi*4]	; _ZN6CTrain20FindClosestTrackNodeE7CVectorPi
		CPatch::PatchPointer(0x6F6D08 + 2, pTrackNodes.ptr);	// mov     eax, ds:pTrackNodes[ecx]	; CTrain__RecalcOnRailDistance
		CPatch::PatchPointer(0x6F6EAE + 3, pTrackNodes.ptr);	// mov     ecx, ds:pTrackNodes[ecx*4]	; CTrain__RecalcOnRailDistance
		CPatch::PatchPointer(0x6F6F77 + 2, pTrackNodes.ptr);	// mov     eax, ds:pTrackNodes[ecx]	; CTrain__RecalcOnRailDistance
		CPatch::PatchPointer(0x6F7441 + 1, pTrackNodes.ptr);	// mov     eax, ds:pTrackNodes	; 
		CPatch::PatchPointer(0x6F7466 + 1, pTrackNodes.ptr);	// push    offset pTrackNodes	; sub_6F7446
		CPatch::PatchPointer(0x6F7478 + 2, pTrackNodes.ptr + 1);	// cmp     ds:pTrackNodes+4, ebx	; sub_6F7446
		CPatch::PatchPointer(0x6F748C + 1, pTrackNodes.ptr + 1);	// push    (offset pTrackNodes+4)	; sub_6F7446
		CPatch::PatchPointer(0x6F749E + 2, pTrackNodes.ptr + 2);	// cmp     ds:pTrackNodes+8, ebx	; sub_6F7446
		CPatch::PatchPointer(0x6F74B2 + 1, pTrackNodes.ptr + 2);	// push    (offset pTrackNodes+8)	; sub_6F7446
		CPatch::PatchPointer(0x6F74C4 + 2, pTrackNodes.ptr + 3);	// cmp     ds:pTrackNodes+0Ch, ebx	; sub_6F7446
		CPatch::PatchPointer(0x6F74D8 + 1, pTrackNodes.ptr + 3);	// push    (offset pTrackNodes+0Ch); float	; sub_6F7446
		CPatch::PatchPointer(0x6F74EA + 2, pTrackNodes.ptr);	// mov     ebx, ds:pTrackNodes	; sub_6F7446
		CPatch::PatchPointer(0x6F75B4 + 3, pTrackNodes.ptr);	// mov     edx, ds:pTrackNodes[ecx*4]	; CTrain__CreateTrain
		CPatch::PatchPointer(0x6F7B70 + 3, pTrackNodes.ptr);	// mov     edi, ds:pTrackNodes[esi*4]	; CTrain__ProcessRandomTrains
		CPatch::PatchPointer(0x6F7C5D + 3, pTrackNodes.ptr);	// mov     ecx, ds:pTrackNodes[eax*4]	; CTrain__ProcessRandomTrains
		CPatch::PatchPointer(0x6F7DC3 + 2, pTrackNodes.ptr);	// mov     edx, ds:pTrackNodes[esi]	; CTrain__ProcessRandomTrains
		CPatch::PatchPointer(0x6F7EE6 + 3, pTrackNodes.ptr);	// mov     ebx, ds:pTrackNodes[esi*4]	; CTrain__ProcessRandomTrains
		CPatch::PatchPointer(0x6F8005 + 2, pTrackNodes.ptr);	// mov     eax, ds:pTrackNodes[esi]	; CTrain__ProcessRandomTrains
		CPatch::PatchPointer(0x6F8099 + 3, pTrackNodes.ptr);	// mov     esi, ds:pTrackNodes[ecx*4]	; CTrain__ProcessRandomTrains
		CPatch::PatchPointer(0x6F871A + 2, pTrackNodes.ptr);	// mov     ecx, ds:pTrackNodes[eax]	; _ZN6CTrain14ProcessControlEv
	}
	#endif

	// Patch pointers to NumTrackNodes
	#if TRUE
	{
		CPatch::PatchPointer(0x6F59E8 + 3, NumTrackNodes.ptr);	// mov     edi, ds:NumTrackNodes[eax*4]	; CTrain__GetRailDistanceCoordinates
		CPatch::PatchPointer(0x6F6BF0 + 3, NumTrackNodes.ptr);	// mov     eax, ds:NumTrackNodes[esi*4]	; _ZN6CTrain20FindClosestTrackNodeE7CVectorPi
		CPatch::PatchPointer(0x6F6C93 + 3, NumTrackNodes.ptr);	// mov     eax, ds:NumTrackNodes[esi*4]	; _ZN6CTrain20FindClosestTrackNodeE7CVectorPi
		CPatch::PatchPointer(0x6F6CCE + 3, NumTrackNodes.ptr);	// mov     ecx, ds:NumTrackNodes[eax*4]	; CTrain__RecalcOnRailDistance
		CPatch::PatchPointer(0x6F6D02 + 2, NumTrackNodes.ptr);	// idiv    ds:NumTrackNodes[ecx]	; CTrain__RecalcOnRailDistance
		CPatch::PatchPointer(0x6F6F4F + 3, NumTrackNodes.ptr);	// mov     ecx, ds:NumTrackNodes[eax*4]	; CTrain__RecalcOnRailDistance
		CPatch::PatchPointer(0x6F7461 + 1, NumTrackNodes.ptr);	// push    offset NumTrackNodes	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F7487 + 1, NumTrackNodes.ptr + 1);	// push    (offset NumTrackNodes+4)	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F74AD + 1, NumTrackNodes.ptr + 2);	// push    (offset NumTrackNodes+8)	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F74D3 + 1, NumTrackNodes.ptr + 3);	// push    (offset NumTrackNodes+0Ch); float	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F7DB4 + 2, NumTrackNodes.ptr);	// idiv    ds:NumTrackNodes[esi]	; CTrain__ProcessRandomTrains
		CPatch::PatchPointer(0x6F7F02 + 3, NumTrackNodes.ptr);	// add     edx, ds:NumTrackNodes[esi*4]	; CTrain__ProcessRandomTrains
		CPatch::PatchPointer(0x6F7F0F + 3, NumTrackNodes.ptr);	// idiv    ds:NumTrackNodes[esi*4]	; CTrain__ProcessRandomTrains
		CPatch::PatchPointer(0x6F7FFF + 2, NumTrackNodes.ptr);	// idiv    ds:NumTrackNodes[esi]	; CTrain__ProcessRandomTrains
		CPatch::PatchPointer(0x6F80B3 + 3, NumTrackNodes.ptr);	// add     edx, ds:NumTrackNodes[ecx*4]	; CTrain__ProcessRandomTrains
		CPatch::PatchPointer(0x6F80C0 + 3, NumTrackNodes.ptr);	// idiv    ds:NumTrackNodes[ecx*4]	; CTrain__ProcessRandomTrains
		CPatch::PatchPointer(0x6F8720 + 3, NumTrackNodes.ptr);	// mov     ax, word ptr ds:NumTrackNodes[eax]	; _ZN6CTrain14ProcessControlEv
	}
	#endif

	// Patch pointers to TrainTrackDistance
	#if TRUE
	{
		CPatch::PatchPointer(0x6F5BC2 + 2, TrainTrackDistance.ptr);	// fld     ds:TrainTrackDistance	; CTrain__GetDistanceToNextStation
		CPatch::PatchPointer(0x6F5BD7 + 2, TrainTrackDistance.ptr);	// fld     ds:TrainTrackDistance	; CTrain__GetDistanceToNextStation
		CPatch::PatchPointer(0x6F5C13 + 2, TrainTrackDistance.ptr);	// fsub    ds:TrainTrackDistance	; CTrain__GetDistanceToNextStation
		CPatch::PatchPointer(0x6F5C30 + 2, TrainTrackDistance.ptr);	// fadd    ds:TrainTrackDistance	; CTrain__GetDistanceToNextStation
		CPatch::PatchPointer(0x6F6FE6 + 2, TrainTrackDistance.ptr);	// fadd    ds:TrainTrackDistance[ecx]	; CTrain__RecalcOnRailDistance
		CPatch::PatchPointer(0x6F745C + 1, TrainTrackDistance.ptr);	// push    offset TrainTrackDistance	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F7482 + 1, TrainTrackDistance.ptr + 1);	// push    (offset TrainTrackDistance+4)	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F74A8 + 1, TrainTrackDistance.ptr + 2);	// push    (offset TrainTrackDistance+8)	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F74CE + 1, TrainTrackDistance.ptr + 3);	// push    (offset TrainTrackDistance+0Ch); float	; _ZN6CTrain10InitTrainsEv
		CPatch::PatchPointer(0x6F8710 + 2, TrainTrackDistance.ptr);	// mov     ecx, ds:TrainTrackDistance[eax]	; _ZN6CTrain14ProcessControlEv
	}
	#endif

	// Patch number of tracks.dat files
	#if TRUE
	{
		CPatch::PatchUINT8(0x6F6CA7 + 2, ms_NumberOfTracksDatFiles);	// cmp     esi, 4
	}
	#endif

	CPatch::RedirectCode(0x6F7459, &patch_CTrain__InitTrains_6F7459);
	}
	#endif

	CPatch::LeaveThisLevel();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_CCarCtrl__GenerateOneRandomCar_431244()
	{
		__asm
		{
			mov eax, edi;
			fadd dword ptr[esp + 54h];

			push 0x43124B;
			retn;
		}
	}

	NAKED void fpCCarPathLink__OneWayLaneOffset()
	{
		__asm
		{
			push    ecx;
			mov     al, [ecx + 0Bh];
			mov     dl, al;

			push 0x44DB06;
			retn;
		}
	}

	class CCarPathLink_changed
	{
	public:
		float OneWayLaneOffset()
		{
			return -((float(__thiscall*)(CCarPathLink_changed*)) &fpCCarPathLink__OneWayLaneOffset)(this);
		}
	};

	const float fMinusOne = -1.0;

	NAKED void patch_CCarCtrl__ClipTargetOrientationToLink_4228A3()
	{
		__asm
		{
			fld dword ptr[esp + 20h];
			fmul dword ptr[fMinusOne];

			mov     eax, [edi + 14h];

			push 0x4228AA;
			retn;
		}
	}
}
#endif

// Makes a traffic left-sided
void MapLimits::PatchLeftSidedTraffic()
{
	return;

	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
	{
	using namespace Game_GTASA;
	CPatch::EnterNewLevelAndDisableDebugState();

	CPatch::RedirectMethod(0x44DB00, &CCarPathLink_changed::OneWayLaneOffset);
	CPatch::RedirectCode(0x4228A3, &patch_CCarCtrl__ClipTargetOrientationToLink_4228A3);

	/*
	// CCarCtrl::UpdateCarOnRails
	CPatch::PatchUINT16(0x436915, 0xC1DE);
	CPatch::PatchUINT16(0x43693A, 0xE9DE);
	CPatch::PatchUINT16(0x4368B0, 0xE9DE);
	CPatch::PatchUINT16(0x436894, 0xC1DE);

	// CCarCtrl::GenerateOneRandomCar
	CPatch::PatchUINT32(0x43126E, 0x182464D8);
	CPatch::RedirectCode(0x431244, &patch_CCarCtrl__GenerateOneRandomCar_431244);
	CPatch::PatchUINT32(0x4314F9, 0x142464D8);
	CPatch::PatchUINT32(0x4314E8, 0x502444D8);
	*/

	CPatch::LeaveThisLevel();
	}
	#endif
}

// Returns true if world map size is increased.
bool MapLimits::IsWorldMapSizeIncreased()
{
	return this->ms_worldMapSize > 6000;
}

// Enables tracks.dat coordinate limit patch
void MapLimits::EnableTracksDatCoordinateLimitPatch(bool enabled)
{
	MAKE_VAR_GAME_VERSION();

	if (!CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		return;

	this->ms_bTracksDatCoordinateLimitPatchEnabled = enabled;

	if (enabled)
		CGenericLogStorage::SaveFormattedTextLn("Tracks*.dat coordinate limit patch enabled.");
}

// Returns true if path map size is supported for game version
bool MapLimits::IsPathMapSizePatchSupportedForGameVersion(Game::eGameVersion gameVersion)
{
	return gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A;
}

// Enables paths limit patch
void MapLimits::EnablePathsLimitPatch(bool enabled)
{
	MAKE_VAR_GAME_VERSION();

	if (IsPathMapSizePatchSupportedForGameVersion(gameVersion))
		this->ms_bPathsPatchEnabled = enabled;
}

// Enables path debugging
void MapLimits::EnablePathDebugging(bool enabled)
{
	this->ms_bPathDebuggingEnabled = enabled;
}

// Sets tracks.dat file size limit
void MapLimits::SetTracksDatFileSizeLimit(unsigned int fileSizeLimit)
{
	MAKE_VAR_GAME_VERSION();

	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
		this->ms_tracksDatFileSizeLimit = fileSizeLimit;
		this->ms_bTracksDatFileSizeLimitSet = true;

		CGenericLogStorage::SaveFormattedTextLn(
			"Tracks.dat file size limit set to %d",
			fileSizeLimit
		);
	}
}

// Sets max number of track stations
void MapLimits::SetMaxNumberOfTrackStations(unsigned int maxNumberOfTrackStations)
{
	MAKE_VAR_GAME_VERSION();

	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		this->ms_bMaxNumberOfTrainStationsLimitSet = true;
		this->ms_MaxNumberOfTrackStations = maxNumberOfTrackStations;

		CGenericLogStorage::SaveFormattedTextLn(
			"Max number of track stations set to %d",
			maxNumberOfTrackStations
		);
	}
}

// Enables track config loader
void MapLimits::EnableTrackConfigLoader(bool enabled)
{
	MAKE_VAR_GAME_VERSION();

	if (!CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		return;

	this->ms_bNumberOfTracksDatFilesSet = enabled;

	if (enabled)
		CGenericLogStorage::SaveTextLn(
			"Track config loader enabled."
		);
}

// Returns true if paths map size is supported for game version
bool MapLimits::IsPathsMapSizePatchSupportedForGameVersion(Game::eGameVersion gameVersion)
{
	return gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A;
}

// Sets paths map size, returns true if successful
void MapLimits::SetPathsMapSize(unsigned int pathsMapSize)
{
	MAKE_VAR_GAME_VERSION();

	if (IsPathMapSizePatchSupportedForGameVersion(gameVersion))
	{
		using namespace Game_GTASA;

		if (pathsMapSize == 6000)
			return;

		if (!this->ms_bPathsPatchEnabled)
			throw f92_runtime_error(
				"Modified limit of ([MAP LIMITS] -> Paths map size) requires path patch to be applied.\n"
				"Please change [MAP LIMITS] -> Apply paths limit patch appropriately."
			);

		// validate
		if (!ValidateMapSizeOrShowMessage(pathsMapSize, "Paths"))
			return;

		this->ms_pathsMapSize = pathsMapSize;

		int numberOfPathFilesPerDimension = pathsMapSize / this->ms_pathBlockSize;
		int totalNumberOfPathFiles = numberOfPathFilesPerDimension * numberOfPathFilesPerDimension;

		if (totalNumberOfPathFiles == 64 || g_fileIDlimits.IsIDlimitsPatchEnabled())
			g_fileIDlimits.SetFileIDlimit(FILE_TYPE_DAT, totalNumberOfPathFiles);
		else
			throw f92_runtime_error(
				"Changed limit of ([MAP LIMITS] -> Paths map size) requires ID limits to be hacked because of different number of DAT files.\n"
				"Please change [ID LIMITS] -> Apply ID limit patch appropriately."
			);
	}
}

// Sets Renderware map size
void MapLimits::SetRenderwareWorldMapSize(unsigned int rwWorldMapSize)
{
	MAKE_VAR_GAME_VERSION();

	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		this->ms_rwWorldMapSize = rwWorldMapSize;
		this->ms_bRwWorldMapSizeLimitSet = true;

		CGenericLogStorage::SaveFormattedTextLn(
			"Renderware world map size set to %d x %d",
			rwWorldMapSize,
			rwWorldMapSize
		);
	}
}

// Returns true if radar map size is supported for game version
bool MapLimits::IsRadarMapSizePatchSupportedForGameVersion(Game::eGameVersion gameVersion)
{
	return CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86;
}

// Radar map size
void MapLimits::SetRadarSize(unsigned int radarMapSize)
{
	MAKE_VAR_GAME_VERSION();

	if (IsRadarMapSizePatchSupportedForGameVersion(gameVersion))
	{
		this->ms_radarMapSize = radarMapSize;
		this->ms_bRadarLimitSet = true;

		CGenericLogStorage::SaveFormattedTextLn(
			"Radar map size set to %d x %d",
			radarMapSize,
			radarMapSize
		);
	}
}

// Enables frontent map different
void MapLimits::EnableFrontendMapDifferent(bool enabled)
{
	MAKE_VAR_GAME_VERSION();

	if (!CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		return;

	this->ms_bIsFrontentMapDifferent = enabled;

	if (enabled)
		CGenericLogStorage::SaveFormattedTextLn("Frontend map different patch enabled.");
}

// Returns true if water map size is supported for game version
bool MapLimits::IsWaterMapSizePatchSupportedForGameVersion(Game::eGameVersion gameVersion)
{
	return CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A;
}

// Sets water map size
void MapLimits::SetWaterMapSize(unsigned int waterMapSize)
{
	MAKE_VAR_GAME_VERSION();

	if (this->IsWaterMapSizePatchSupportedForGameVersion(gameVersion))
	{
		this->ms_waterMapSize = waterMapSize;
		this->ms_bWaterLimitSet = true;

		CGenericLogStorage::SaveFormattedTextLn(
			"Water map size set to %d x %d",
			waterMapSize,
			waterMapSize
		);
	}
}

// Returns true if world map size is supported for game version
bool MapLimits::IsWorldMapSizePatchSupportedForGameVersion(eGameVersion gameVersion)
{
	return gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86

		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A;
}

// Map bound limit
void MapLimits::SetWorldMapSize(unsigned int worldMapSize)
{
	MAKE_VAR_GAME_VERSION();

	if (IsWorldMapSizePatchSupportedForGameVersion(gameVersion))
	{
		this->ms_worldMapSize = worldMapSize;
		this->ms_bWorldSectorLimitSet = true;

		CGenericLogStorage::SaveFormattedTextLn(
			"World map size set to %d x %d",
			worldMapSize,
			worldMapSize
		);
	}
}

// World sector size, affects 
void MapLimits::SetWorldSectorSize(unsigned int sectorSize)
{
	MAKE_VAR_GAME_VERSION();

	if (IsWorldMapSizePatchSupportedForGameVersion(gameVersion))
	{
		this->ms_worldSectorSize = sectorSize;
		this->ms_bWorldSectorLimitSet = true;

		CGenericLogStorage::SaveFormattedTextLn(
			"World sector size set to %d x %d",
			sectorSize,
			sectorSize
		);
	}
}

// World LOD sector size
void MapLimits::SetLODSectorSize(unsigned int LODsectorSize)
{
	MAKE_VAR_GAME_VERSION();

	if (IsWorldMapSizePatchSupportedForGameVersion(gameVersion))
	{
		this->ms_worldLODsectorSize = LODsectorSize;
		this->ms_bWorldSectorLimitSet = true;

		CGenericLogStorage::SaveFormattedTextLn(
			"World LOD sector size set to %d x %d",
			LODsectorSize,
			LODsectorSize
		);
	}
}

// Initialize
void MapLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	// Radar texture array reallocated?
	this->ms_bRadarTextureArrayReallocated = false;

	// Is path debugging enabled
	this->ms_bPathDebuggingEnabled = false;

	// Is tracks.dat coordinate patch enabled
	this->ms_bTracksDatCoordinateLimitPatchEnabled = false;

	// Is tracks.dat file size limit set
	this->ms_bTracksDatFileSizeLimitSet = false;

	// Is max number of track stations limit set
	this->ms_bMaxNumberOfTrainStationsLimitSet = false;

	// Is number of tracks.dat files set
	this->ms_bNumberOfTracksDatFilesSet = false;

	// Is paths patch enabled
	this->ms_bPathsPatchEnabled = false;

	// Is frontend map different
	this->ms_bIsFrontentMapDifferent = false;

	// Has radar limit been set
	this->ms_bRadarLimitSet = false;

	// Has water limit been set
	this->ms_bWaterLimitSet = false;

	// Has world sector limit been set
	this->ms_bWorldSectorLimitSet = false;

	// Has world map size limit been set?
	this->ms_bRwWorldMapSizeLimitSet = false;

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		using namespace Game_GTASA;

		// Tracks.dat file size limit
		this->ms_tracksDatFileSizeLimit = 46384;

		// Tracks.dat stations
		this->ms_MaxNumberOfTrackStations = 6;

		// Number of tracks.dat files
		this->ms_NumberOfTracksDatFiles = 4;

		// Paths map size
		this->ms_pathsMapSize = 6000;

		// Path block size
		this->ms_pathBlockSize = 750;

		// Renderware world map size
		this->ms_rwWorldMapSize = 20000;

		// Radar map size
		this->ms_radarMapSize = 6000;

		// Water map size
		this->ms_waterMapSize = 6000;

		// Map bound limit
		this->ms_worldMapSize = 6000;

		// Water block size
		this->ms_waterBlockSize = 500;

		// World sector size
		this->ms_worldSectorSize = 50;

		// World LOD sector size
		this->ms_worldLODsectorSize = 200;

		////////////////////////////////////////////////

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				// Water quads and triangles in each block
				this->CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr = (int16_t*)0xC21B70;

				// World sector array
				this->CWorld__ms_aSectors.gta_sa = (CSector*)0xB7D0B8;

				// World repeat sector array
				this->CWorld__ms_aRepeatSectors.gta_sa = (CRepeatSector*)0xB992B8;

				// World LOD sector array
				this->CWorld__ms_aLodPtrLists.gta_sa = (Game_GTA::CPtrNodeSingleLink**)0xB99EB8;

				// Path finder
				ThePaths.gta_sa = (CPathFind_extended*)0x96F050;

				this->ToBeStreamed.ptr = (bool*)0x96EFD0;
				this->ToBeStreamedForScript.ptr = (bool*)0x96EF90;

				this->DontWanderGiven.ptr = (uint8_t*)0x96EC40;
				this->XCoorGiven.ptr = (float*)0x96EE80;
				this->YCoorGiven.ptr = (float*)0x96ED80;
				this->ZCoorGiven.ptr = (float*)0x96EC80;
				this->ConnectsToGiven.ptr = (uint8_t*)0x96EAC0;

				Address_CPathFind_MarkRegionsForCoors = 0x44DB60;

				Address_CPathFind_SwitchRoadsOffInAreaForOneRegion = 0x452820;

				NumTempExternalNodes = (uint32_t*)0x96F030;
			}
			#elif defined(IS_PLATFORM_ANDROID_ARM32)
			{
				// Water quads and triangles in each block
				this->CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr = (int16_t*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN11CWaterLevel30m_QuadsAndTrianglesInEachBlockE"
				);

				// World sector array
				this->CWorld__ms_aSectors.gta_sa = (CSector*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN6CWorld11ms_aSectorsE"
				);

				// World repeat sector array
				this->CWorld__ms_aRepeatSectors.gta_sa = (CRepeatSector*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN6CWorld17ms_aRepeatSectorsE"
				);

				// World LOD sector array
				this->CWorld__ms_aLodPtrLists.gta_sa = (Game_GTA::CPtrNodeSingleLink**)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN6CWorld15ms_aLodPtrListsE"
				);

				// Path finder
				ThePaths.gta_sa = (CPathFind_extended*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"ThePaths"
				);

				this->ToBeStreamed.ptr = (bool*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"ToBeStreamed"
				);
				this->ToBeStreamedForScript.ptr = (bool*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"ToBeStreamedForScript"
				);

				this->DontWanderGiven.ptr = (uint8_t*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"DontWanderGiven"
				);
				this->XCoorGiven.ptr = (float*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"XCoorGiven"
				);
				this->YCoorGiven.ptr = (float*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"YCoorGiven"
				);
				this->ZCoorGiven.ptr = (float*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"ZCoorGiven"
				);
				this->ConnectsToGiven.ptr = (uint8_t*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"ConnectsToGiven"
				);

				Address_CPathFind_MarkRegionsForCoors = (uintptr_t)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN9CPathFind19MarkRegionsForCoorsE7CVectorf"
				);

				Address_CPathFind_SwitchRoadsOffInAreaForOneRegion = (uintptr_t)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN9CPathFind32SwitchRoadsOffInAreaForOneRegionEffffffbbib"
				);

				NumTempExternalNodes = (uint32_t*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"NumTempExternalNodes"
				);
			}
			#endif
		}

		// Set CPathFind offsets
		this->AllocateCPathFind(64, 8, 16);

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			// Radar texture IDs
			this->gRadarTextures.ptr = (int*)0xBA8478;

			// Station distances
			this->StationDist.ptr = (float*)0xC38034;

			// Station coordinates
			this->CTrain__aStationCoors.ptr = (CVector*)0x8D48F8;

			// pTrackNodes
			this->pTrackNodes.ptr = (void**)0xC38024;

			// TrainTrackDistance
			this->TrainTrackDistance.ptr = (float*)0xC37FEC;

			// TrainTrackNodeCount
			this->NumTrackNodes.ptr = (unsigned int*)0xC38014;
			#endif
		}
	}
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
	{
		using namespace Game_GTAIV;

		// Water block size
		this->ms_waterBlockSize = 500;

		/////////

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			{
				gRadarTextures.ptr = (int*)g_mCalc.GetCurrentVAbyPreferedVA(0x1724428);
				CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr = (int16_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x15B7480);
				CWorld__ms_aSectors.gta_iv = (CSector*)g_mCalc.GetCurrentVAbyPreferedVA(0x11A8568);
				CWorld__ms_aRepeatSectors.gta_iv = (CRepeatSector*)g_mCalc.GetCurrentVAbyPreferedVA(0x11A7160);
				CWorld__ms_aLodPtrLists.gta_iv = (void**)g_mCalc.GetCurrentVAbyPreferedVA(0x11D2870);
				CWorld__ms_aSectorObjectCount.ptr = (uint8_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x11A37C0);
				CWorld__ms_aSectorFlags.ptr = (uint16_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x1685DF8);
				CWorld__ms_class_1136170.gta_iv = (CClass_1136170*)g_mCalc.GetCurrentVAbyPreferedVA(0x1136170);
			}
			else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				gRadarTextures.ptr = (int*)g_mCalc.GetCurrentVAbyPreferedVA(0x1792ED8);
			}
			#endif
		}
	}
	else if (CGameVersion::IsAny_GTA_V(gameVersion))
	{
		// Path block size
		this->ms_pathBlockSize = 512;
	}
}

// Shutdown
void MapLimits::Shutdown()
{
	MAKE_VAR_GAME_VERSION();

	if (CWaterLevel__m_QuadsAndTrianglesInEachBlock.bIsAllocated.Get())
		delete[] CWaterLevel__m_QuadsAndTrianglesInEachBlock.ptr;

	if (CWorld__ms_aSectorObjectCount.bIsAllocated.Get())
		delete[] CWorld__ms_aSectorObjectCount.ptr;

	if (CWorld__ms_aSectorFlags.bIsAllocated.Get())
		delete[] CWorld__ms_aSectorFlags.ptr;

	if (gRadarTextures.bIsAllocated.Get())
		delete[] gRadarTextures.ptr;

	if (ToBeStreamed.bIsAllocated.Get())
		delete[] ToBeStreamed.ptr;

	if (ToBeStreamedForScript.bIsAllocated.Get())
		delete[] ToBeStreamedForScript.ptr;

	if (DontWanderGiven.bIsAllocated.Get())
		delete[] DontWanderGiven.ptr;

	if (XCoorGiven.bIsAllocated.Get())
		delete[] XCoorGiven.ptr;

	if (YCoorGiven.bIsAllocated.Get())
		delete[] YCoorGiven.ptr;

	if (ZCoorGiven.bIsAllocated.Get())
		delete[] ZCoorGiven.ptr;

	if (ConnectsToGiven.bIsAllocated.Get())
		delete[] ConnectsToGiven.ptr;

	if (StationDist.bIsAllocated.Get())
		delete[] StationDist.ptr;

	if (CTrain__aStationCoors.bIsAllocated.Get())
		delete[] CTrain__aStationCoors.ptr;

	if (pTrackNodes.bIsAllocated.Get())
		delete[] pTrackNodes.ptr;

	if (TrainTrackDistance.bIsAllocated.Get())
		delete[] TrainTrackDistance.ptr;

	if (NumTrackNodes.bIsAllocated.Get())
		delete[] NumTrackNodes.ptr;

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		if (CWorld__ms_aSectors.bIsAllocated.Get())
			delete[] CWorld__ms_aSectors.gta_sa;

		if (CWorld__ms_aRepeatSectors.bIsAllocated.Get())
			delete[] CWorld__ms_aRepeatSectors.gta_sa;

		if (CWorld__ms_aLodPtrLists.bIsAllocated.Get())
			delete[] CWorld__ms_aLodPtrLists.gta_sa;

		if (ThePaths.bIsAllocated.Get())
			delete ThePaths.gta_sa;
	}
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
	{
		if (CWorld__ms_aSectors.bIsAllocated.Get())
			delete[] CWorld__ms_aSectors.gta_iv;

		if (CWorld__ms_aRepeatSectors.bIsAllocated.Get())
			delete[] CWorld__ms_aRepeatSectors.gta_iv;

		if (CWorld__ms_aLodPtrLists.bIsAllocated.Get())
			delete[] CWorld__ms_aLodPtrLists.gta_iv;

		if (CWorld__ms_class_1136170.bIsAllocated.Get())
			delete[] CWorld__ms_class_1136170.gta_iv;
	}

	if (pNaviNodePositions)
	{
		for (unsigned int i = 0; i < iTotalNumberOfPathIndicesIncludingInterior; i++)
			delete[] pNaviNodePositions[i];

		delete[] pNaviNodePositions;
	}
}
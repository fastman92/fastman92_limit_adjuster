/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "IslandLimits.h"

#include "FileIDlimit.h"

#include "../Core/CPatch.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/CStreaming.h"

using namespace Game;

IslandLimits g_islandLimits;

// Initializes
bool IslandLimits::EnableIslandLimits(int iNumberOfIslands)
{
	MAKE_VAR_GAME_VERSION();

	if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
	{
		this->ms_iNumberOfIslands = iNumberOfIslands;
		this->ms_CopPedIDsPerIsland = new uint32_t[iNumberOfIslands + 1];
		this->ms_CopCarIDsPerIsland = new uint32_t[iNumberOfIslands + 1];

		this->ms_AmbulanceVehicleIDsPerIsland = new uint32_t[iNumberOfIslands];
		this->ms_AmbulanceVehicleIDsPerIsland[0] = -1;

		this->ms_MedicPedIDsPerIsland = new uint32_t[iNumberOfIslands];
		this->ms_MedicPedIDsPerIsland[0] = -1;

		this->ms_FireEngineVehicleIDsPerIsland = new uint32_t[iNumberOfIslands];
		this->ms_FireEngineVehicleIDsPerIsland[0] = -1;

		this->ms_FiremanPedIDsPerIsland = new uint32_t[iNumberOfIslands];
		this->ms_FiremanPedIDsPerIsland[0] = -1;

		this->ms_CabDriverNumberOfPedIDsPerIsland = new uint32_t[iNumberOfIslands];
		memset(this->ms_CabDriverNumberOfPedIDsPerIsland, NULL, iNumberOfIslands * sizeof(uint32_t));

		this->ms_CabDriverPedIDsPerIsland
			= new uint32_t[iNumberOfIslands * this->ms_maxNumberOfCabDriversPerIsland];

		memset(
			this->ms_CabDriverPedIDsPerIsland,
			0xFFFFFFFF,
			iNumberOfIslands * this->ms_maxNumberOfCabDriversPerIsland * sizeof(uint32_t)
		);

		this->ms_ItemPriceMultipliersPerIsland = new float[iNumberOfIslands];
		return true;
	}
	else
		return false;
}

// Sets cop ped ID for level
void IslandLimits::SetCopPedID(int level, int copPedID)
{
	this->ms_CopPedIDsPerIsland[level] = copPedID;
}

// Sets cop car ID for level
void IslandLimits::SetCopCarID(int level, int copCarID)
{
	this->ms_CopCarIDsPerIsland[level] = copCarID;
}

// Sets cop bike ID
void IslandLimits::SetCopBikeID(int copBikeID)
{
	this->ms_CopCarIDsPerIsland[this->ms_iNumberOfIslands] = copBikeID;
}

// Sets cop bike driver ID
void IslandLimits::SetCopBikeDriverID(int copBikePedID)
{
	this->ms_CopPedIDsPerIsland[this->ms_iNumberOfIslands] = copBikePedID;
}
		
// Sets ambulance car ID for level
void IslandLimits::SetAmbulanceID(int level, int ambulanceID)
{
	this->ms_AmbulanceVehicleIDsPerIsland[level] = ambulanceID;
}

// Sets medic ped ID for level
void IslandLimits::SetMedicID(int level, int medicID)
{
	this->ms_MedicPedIDsPerIsland[level] = medicID;
}

// Sets fire engine ID for level
void IslandLimits::SetFireEngineID(int level, int fireEngineID)
{
	this->ms_FireEngineVehicleIDsPerIsland[level] = fireEngineID;
}

// Sets fireman ID for level
void IslandLimits::SetFiremanEngineID(int level, int firemanID)
{
	this->ms_FiremanPedIDsPerIsland[level] = firemanID;
}

// Sets number of cab drivers for level
void IslandLimits::SetNumberOfCabDriversForLevel(int level, unsigned int numberOfCabDrivers)
{
	this->ms_CabDriverNumberOfPedIDsPerIsland[level] = numberOfCabDrivers;
}

// Sets cab driver ID for level
void IslandLimits::SetCabDriverID(int level, int place, int cabDriverID)
{
	this->ms_CabDriverPedIDsPerIsland[level * ms_maxNumberOfCabDriversPerIsland + place] = cabDriverID;
}

// Sets item price multiplier for level
void IslandLimits::SetItemPriceMultiplier(int level, float multiplier)
{
	this->ms_ItemPriceMultipliersPerIsland[level] = multiplier;
}


#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA_PC_HOODLUM
{
	using namespace Game_GTASA;
	NAKED void patch_CStreaming__StreamCopModels_156C1AA()
	{
		__asm
		{
			mov edi, ASM_ACCESS_LIMIT_VAR_32_BIT(g_islandLimits, IslandLimits, ms_iNumberOfIslands);

			push 0x156C1F8;
			retn;
		}
	}

	bool __cdecl ReloadModelsForLevel(bool reload, uint32_t* pedIDarray, uint32_t* carIDarray)
	{
		tFileTypeBaseID txdBaseID = g_fileIDlimits.GetBaseID(FILE_TYPE_TXD);

		unsigned int numberOfIslands = g_islandLimits.ms_iNumberOfIslands;

		for (unsigned int i = 1; i < numberOfIslands; i++)
		{
			// set ped deletable
			uint32_t pedModelID = pedIDarray[i];
			CStreaming::SetModelIsDeletable(pedModelID);
			uint32_t pedTXDfileID = g_fileIDlimits.CModelInfo__ms_modelInfoPtrs.gta_sa[pedModelID]->m_wTxdIndex
				+ txdBaseID;

			CStreaming::SetModelIsDeletable(pedTXDfileID);

			// set car deletable
			uint32_t carModelID = carIDarray[i];

			CStreaming::SetModelIsDeletable(carModelID);
			uint32_t carTXDfileID = g_fileIDlimits.CModelInfo__ms_modelInfoPtrs.gta_sa[carModelID]->m_wTxdIndex
				+ txdBaseID;

			CStreaming::SetModelIsDeletable(carTXDfileID);
		}

		///////////
		uint32_t CurrLevel = *(uint32_t*)0xBA6718;

		if (reload)
		{
			uint32_t pedModelID = pedIDarray[CurrLevel];
			uint32_t carModelID = carIDarray[CurrLevel];

			if (pedModelID != 0xFFFFFFFF && carModelID != 0xFFFFFFFF)
			{
				CStreaming::RequestModel(pedModelID, 8);
				CStreaming::RequestModel(carModelID, 8);

				if (g_fileIDlimits.CStreaming__ms_aInfoForModel.gta_sa[pedModelID].uiLoadFlag == 1
					&& g_fileIDlimits.CStreaming__ms_aInfoForModel.gta_sa[carModelID].uiLoadFlag == 1
					)
					return true;
			}
		}

		return false;
	}

	bool __cdecl CStreaming__ReloadMedicModels(bool reload)
	{
		return ReloadModelsForLevel(
			reload,
			g_islandLimits.ms_MedicPedIDsPerIsland,
			g_islandLimits.ms_AmbulanceVehicleIDsPerIsland
		);
	}

	bool __cdecl CStreaming__ReloadFireModels(bool reload)
	{
		return ReloadModelsForLevel(
			reload,
			g_islandLimits.ms_FiremanPedIDsPerIsland,
			g_islandLimits.ms_FireEngineVehicleIDsPerIsland
		);
	}

	unsigned int __cdecl CStreaming__GetDefaultCabDriverModel()
	{
		unsigned int lastDriverID = g_islandLimits.ms_CabDriverPedIDsPerIsland[CStreaming::LastSelectedCabDriver];

		if (lastDriverID == 0xFFFFFFFF || !g_fileIDlimits.CStreaming__ms_aInfoForModel.gta_sa[lastDriverID].uiLoadFlag)
		{
			int currLevel = *(int*)0xBA6718;

			unsigned int numberOfCabDrivers = g_islandLimits.ms_CabDriverNumberOfPedIDsPerIsland[currLevel];

			if (numberOfCabDrivers > 0)
			{
				CStreaming::LastSelectedCabDriver = currLevel * IslandLimits::ms_maxNumberOfCabDriversPerIsland
					+ rand() % numberOfCabDrivers;

				return g_islandLimits.ms_CabDriverPedIDsPerIsland[CStreaming::LastSelectedCabDriver];
			}
			else
			{
				if (lastDriverID == 0xFFFFFFFF)
				{
					for (unsigned int levelID = 0; levelID < g_islandLimits.ms_iNumberOfIslands; levelID++)
					{
						numberOfCabDrivers = g_islandLimits.ms_CabDriverNumberOfPedIDsPerIsland[levelID];

						if (numberOfCabDrivers > 0)
						{
							CStreaming::LastSelectedCabDriver = levelID * IslandLimits::ms_maxNumberOfCabDriversPerIsland;
							return g_islandLimits.ms_CabDriverPedIDsPerIsland[CStreaming::LastSelectedCabDriver];
						}
					}
				}
			}
		}

		return lastDriverID;
	}

	unsigned int __cdecl CStreaming__GetDefaultCabDriverModel_debug()
	{
		unsigned int result = CStreaming__GetDefaultCabDriverModel();

		OutputFormattedDebugString("0x407D50, cab driver ID: %d", result);

		return result;
	}
}
#endif

void WriteIDsToLog(const char* pattern, uint32_t* pIDarray)
{
	CGenericLogStorage::SaveTextLn("");

	for (unsigned int levelID = 0; levelID < g_islandLimits.ms_iNumberOfIslands; levelID++)
		CGenericLogStorage::SaveFormattedTextLn(
		pattern,
		levelID,
		pIDarray[levelID]
		);
}

// Print to log
void IslandLimits::PrintToLog()
{
	CGenericLogStorage::SaveFormattedTextLn("Level limit is enabled\n");

	CGenericLogStorage::SaveFormattedTextLn("Number of levels = %d", this->ms_iNumberOfIslands);

	// Cop car IDs for levels
	for (unsigned int levelID = 0; levelID < this->ms_iNumberOfIslands; levelID++)
		CGenericLogStorage::SaveFormattedTextLn(
			"Cop car level %d = %d",
			levelID,
			this->ms_CopCarIDsPerIsland[levelID]
		);

	CGenericLogStorage::SaveFormattedTextLn(
		"Cop bike = %d",
		this->ms_CopCarIDsPerIsland[this->ms_iNumberOfIslands]
		);

	// Cop ped IDs for levels
	CGenericLogStorage::SaveTextLn("");

	for (unsigned int levelID = 0; levelID < this->ms_iNumberOfIslands; levelID++)
		CGenericLogStorage::SaveFormattedTextLn(
		"Cop ped level %d = %d",
		levelID,
		this->ms_CopPedIDsPerIsland[levelID]
		);

	CGenericLogStorage::SaveFormattedTextLn(
		"Cop ped bike = %d",
		this->ms_CopPedIDsPerIsland[this->ms_iNumberOfIslands]
		);
		
	// Ambulance IDs for levels
	WriteIDsToLog("Ambulance level  %d = %d", this->ms_AmbulanceVehicleIDsPerIsland);

	// Medic IDs for levels
	WriteIDsToLog("Medic level %d = %d", this->ms_MedicPedIDsPerIsland);

	// Fire engine IDs for levels
	WriteIDsToLog("Fire engine level %d = %d", this->ms_FireEngineVehicleIDsPerIsland);

	// Fireman IDs for levels
	WriteIDsToLog("Fireman level %d = %d", this->ms_FiremanPedIDsPerIsland);

	// Cab driver IDs for levels
	CGenericLogStorage::SaveTextLn("");

	for (unsigned int levelID = 0; levelID < this->ms_iNumberOfIslands; levelID++)
	{
		uint32_t numberOfCabDrivers = this->ms_CabDriverNumberOfPedIDsPerIsland[levelID];

		CGenericLogStorage::SaveFormattedTextLn(
			"Number of cab drivers for level %d = %d",
			levelID,
			numberOfCabDrivers
			);

		for (unsigned int place = 0; place < numberOfCabDrivers; place++)
		{
			CGenericLogStorage::SaveFormattedTextLn(
				"Cab driver level %d place %d = %d",
				levelID,
				place,
				IslandLimits::ms_CabDriverPedIDsPerIsland[levelID * this->ms_maxNumberOfCabDriversPerIsland + place]
				);
		}

	}

	CGenericLogStorage::WriteLineSeparator();
}

// Commits changes
void IslandLimits::CommitChanges()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevelAndDisableDebugState();
		
	////////////////////////////////////

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
	{
		using namespace Game_GTASA_PC_HOODLUM;

		// cop car IDs
		if (this->ms_iNumberOfIslands > 4)
		{
			CPatch::PatchPointer(0x407C7C + 1, ms_CopCarIDsPerIsland + ms_iNumberOfIslands);	// mov     eax, dword_8A5A9C
			CPatch::PatchPointer(0x407C8D + 3, ms_CopCarIDsPerIsland);	// mov     eax, ds:_copCarModelIds[ecx*4]	; sub_407C50
			CPatch::PatchPointer(0x407CE3 + 3, ms_CopCarIDsPerIsland);	// mov     ecx, ds:_copCarModelIds[eax*4]	; sub_407C50
			CPatch::PatchPointer(0x407D01 + 3, ms_CopCarIDsPerIsland);	// mov     eax, ds:_copCarModelIds[eax*4]	; sub_407C50
			CPatch::PatchPointer(0x156C213 + 3, ms_CopCarIDsPerIsland);	// mov     eax, ds:_copCarModelIds[edi*4]	; sub_156C100
			CPatch::PatchPointer(0x156C261 + 3, ms_CopCarIDsPerIsland);	// mov     edx, ds:_copCarModelIds[esi*4]	; sub_156C100
			CPatch::PatchPointer(0x156C26E + 3, ms_CopCarIDsPerIsland);	// mov     eax, ds:_copCarModelIds[esi*4]	; sub_156C100
			CPatch::PatchPointer(0x156C2A4 + 3, ms_CopCarIDsPerIsland);	// mov     ecx, ds:_copCarModelIds[edi*4]	; sub_156C100
		}
		else
		{
			CPatch::PatchMemoryData(
				0x8A5A8C,
				this->ms_CopCarIDsPerIsland,
				(this->ms_iNumberOfIslands + 1) * sizeof(uint32_t)
			);
		}

		CPatch::PatchUINT32(0x407CB5 + 1, this->ms_iNumberOfIslands + 1);	// mov     edx, 5
		CPatch::PatchUINT32(0x407CBC + 1, this->ms_iNumberOfIslands);	// mov     edx, 4

		CPatch::RedirectCode(0x156C1AA, &patch_CStreaming__StreamCopModels_156C1AA);
		CPatch::PatchUINT8(0x156C22E + 2, this->ms_iNumberOfIslands);	// cmp     edi, 4
		CPatch::PatchUINT8(0x156C290 + 2, this->ms_iNumberOfIslands);	// cmp     esi, 4

		////////////////////////////////////
		// cop ped IDs
		if (this->ms_iNumberOfIslands > 4)
		{
			CPatch::PatchPointer(0x407C6B + 1, ms_CopPedIDsPerIsland + ms_iNumberOfIslands);	// mov     eax, ds:_copModelByTown+10h	; sub_407C50
			CPatch::PatchPointer(0x407C94 + 3, ms_CopPedIDsPerIsland);	// mov     ecx, ds:_copModelByTown[ecx*4]	; sub_407C50
			CPatch::PatchPointer(0x407CD0 + 3, ms_CopPedIDsPerIsland);	// mov     ecx, ds:_copModelByTown[eax*4]	; sub_407C50
			CPatch::PatchPointer(0x156C1F8 + 3, ms_CopPedIDsPerIsland);	// mov     eax, ds:_copModelByTown[edi*4]	; sub_156C100
			CPatch::PatchPointer(0x156C233 + 3, ms_CopPedIDsPerIsland);	// mov     ecx, ds:_copModelByTown[esi*4]	; sub_156C100
			CPatch::PatchPointer(0x156C240 + 3, ms_CopPedIDsPerIsland);	// mov     edx, ds:_copModelByTown[esi*4]	; sub_156C100
			CPatch::PatchPointer(0x156C295 + 3, ms_CopPedIDsPerIsland);	// mov     eax, ds:_copModelByTown[edi*4]	; sub_156C100
			CPatch::PatchPointer(0x156C9E5 + 3, ms_CopPedIDsPerIsland);	// mov     eax, ds:_copModelByTown[eax*4]	; sub_156C9E0
			CPatch::PatchPointer(0x156CA00 + 3, ms_CopPedIDsPerIsland);	// mov     eax, ds:_copModelByTown[ecx*4]	; sub_156C9E0
			CPatch::PatchPointer(0x156CA1E + 3, ms_CopPedIDsPerIsland);	// mov     eax, ds:_copModelByTown[ecx*4]	; sub_156C9E0
		}
		else
		{
			CPatch::PatchMemoryData(
				0x8A5AA0,
				IslandLimits::ms_CopPedIDsPerIsland,
				(IslandLimits::ms_iNumberOfIslands + 1) * sizeof(uint32_t)
			);
		}

		CPatch::PatchUINT8(0x156CA14 + 2, this->ms_iNumberOfIslands);	// cmp     ecx, 4		

		////////////////////////////////////		
		// ambulance IDs
		if (IslandLimits::ms_iNumberOfIslands > 4)
		{
			CPatch::PatchPointer(0x40A31F + 1, ms_AmbulanceVehicleIDsPerIsland);	// mov     eax, ds:_ambulanceByTown+4	; sub_40A2A0
			CPatch::PatchPointer(0x40A32A + 2, ms_AmbulanceVehicleIDsPerIsland);	// mov     ecx, ds:_ambulanceByTown+4	; sub_40A2A0
			CPatch::PatchPointer(0x40A346 + 2, ms_AmbulanceVehicleIDsPerIsland);	// mov     ecx, ds:_ambulanceByTown+8	; sub_40A2A0
			CPatch::PatchPointer(0x40A352 + 2, ms_AmbulanceVehicleIDsPerIsland);	// mov     edx, ds:_ambulanceByTown+8	; sub_40A2A0
			CPatch::PatchPointer(0x40A36F + 2, ms_AmbulanceVehicleIDsPerIsland);	// mov     edx, ds:_ambulanceByTown+0Ch	; sub_40A2A0
			CPatch::PatchPointer(0x40A37B + 1, ms_AmbulanceVehicleIDsPerIsland);	// mov     eax, ds:_ambulanceByTown+0Ch	; sub_40A2A0
			CPatch::PatchPointer(0x40A3BD + 3, ms_AmbulanceVehicleIDsPerIsland);	// mov     ecx, ds:_ambulanceByTown[edi*4]	; sub_40A2A0
			CPatch::PatchPointer(0x40A3C4 + 3, ms_AmbulanceVehicleIDsPerIsland);	// lea     edi, _ambulanceByTown[edi*4]	; sub_40A2A0
			CPatch::PatchPointer(0x15674B5 + 3, ms_AmbulanceVehicleIDsPerIsland);	// mov     eax, ds:_ambulanceByTown[eax*4]	; sub_15674B0
		}
		else
		{
			CPatch::PatchMemoryData(
				0x8A5AB4,
				IslandLimits::ms_AmbulanceVehicleIDsPerIsland,
				IslandLimits::ms_iNumberOfIslands * sizeof(uint32_t)
			);
		}

		// medic IDs
		if (IslandLimits::ms_iNumberOfIslands > 4)
		{
			CPatch::PatchPointer(0x40A2A0 + 1, ms_MedicPedIDsPerIsland);	// mov     eax, ds:_medicModelsByTown+4	; sub_40A2A0
			CPatch::PatchPointer(0x40A2B2 + 2, ms_MedicPedIDsPerIsland);	// mov     ecx, ds:_medicModelsByTown+4	; sub_40A2A0
			CPatch::PatchPointer(0x40A2CE + 2, ms_MedicPedIDsPerIsland);	// mov     ecx, ds:_medicModelsByTown+8	; sub_40A2A0
			CPatch::PatchPointer(0x40A2DA + 2, ms_MedicPedIDsPerIsland);	// mov     edx, ds:_medicModelsByTown+8	; sub_40A2A0
			CPatch::PatchPointer(0x40A2F7 + 2, ms_MedicPedIDsPerIsland);	// mov     edx, ds:_medicModelsByTown+0Ch	; sub_40A2A0
			CPatch::PatchPointer(0x40A303 + 1, ms_MedicPedIDsPerIsland);	// mov     eax, ds:_medicModelsByTown+0Ch	; sub_40A2A0
			CPatch::PatchPointer(0x40A3A6 + 3, ms_MedicPedIDsPerIsland);	// mov     eax, ds:_medicModelsByTown[edi*4]	; sub_40A2A0
			CPatch::PatchPointer(0x40A3AE + 3, ms_MedicPedIDsPerIsland);	// lea     esi, _medicModelsByTown[edi*4]	; sub_40A2A0
			CPatch::PatchPointer(0x1563A55 + 3, ms_MedicPedIDsPerIsland);	// mov     eax, ds:_medicModelsByTown[eax*4]	; sub_1563A50
		}
		else
		{
			CPatch::PatchMemoryData(
				0x8A5AC4,
				IslandLimits::ms_MedicPedIDsPerIsland,
				IslandLimits::ms_iNumberOfIslands * sizeof(uint32_t)
			);
		}

		CPatch::RedirectCode(0x40A2A0, &CStreaming__ReloadMedicModels);

		////////////////////////////////////
		// fire engine IDs
		if (IslandLimits::ms_iNumberOfIslands > 4)
		{
			CPatch::PatchPointer(0x156CE85 + 3, ms_FireEngineVehicleIDsPerIsland);	// mov     eax, ds:_firetruckModelsByTown[eax*4]	; sub_156CE80
			CPatch::PatchPointer(0x15702AF + 1, ms_FireEngineVehicleIDsPerIsland);	// mov     eax, ds:_firetruckModelsByTown+4	; sub_1570230
			CPatch::PatchPointer(0x15702BA + 2, ms_FireEngineVehicleIDsPerIsland);	// mov     ecx, ds:_firetruckModelsByTown+4	; sub_1570230
			CPatch::PatchPointer(0x15702D6 + 2, ms_FireEngineVehicleIDsPerIsland);	// mov     ecx, ds:_firetruckModelsByTown+8	; sub_1570230
			CPatch::PatchPointer(0x15702E2 + 2, ms_FireEngineVehicleIDsPerIsland);	// mov     edx, ds:_firetruckModelsByTown+8	; sub_1570230
			CPatch::PatchPointer(0x15702FF + 2, ms_FireEngineVehicleIDsPerIsland);	// mov     edx, ds:_firetruckModelsByTown+0Ch	; sub_1570230
			CPatch::PatchPointer(0x157030B + 1, ms_FireEngineVehicleIDsPerIsland);	// mov     eax, ds:_firetruckModelsByTown+0Ch	; sub_1570230
			CPatch::PatchPointer(0x157038F + 3, ms_FireEngineVehicleIDsPerIsland);	// mov     ecx, ds:_firetruckModelsByTown[edi*4]	; sub_1570230
			CPatch::PatchPointer(0x1570396 + 3, ms_FireEngineVehicleIDsPerIsland);	// lea     edi, _firetruckModelsByTown[edi*4]	; sub_1570230
		}
		else
		{
			CPatch::PatchMemoryData(
				0x8A5AD4,
				IslandLimits::ms_FireEngineVehicleIDsPerIsland,
				IslandLimits::ms_iNumberOfIslands * sizeof(uint32_t)
			);
		}

		CPatch::RedirectCode(0x40A400, &CStreaming__ReloadFireModels);

		////////////////////////////////////
		// fire engine IDs
		if (IslandLimits::ms_iNumberOfIslands > 4)
		{
			CPatch::PatchPointer(0x156CD75 + 3, ms_FiremanPedIDsPerIsland);	// mov     eax, _firemanModelsByTown[eax*4]
		}
		else
		{
			CPatch::PatchMemoryData(
				0x8A5AE4,
				IslandLimits::ms_FiremanPedIDsPerIsland,
				IslandLimits::ms_iNumberOfIslands * sizeof(uint32_t)
			);
		}

		// cab driver IDs
		CPatch::RedirectCode(0x407D50, &CStreaming__GetDefaultCabDriverModel);

		////////////////////////////////////
		// item price multipliers
		if (IslandLimits::ms_iNumberOfIslands > 4)
		{
			CPatch::PatchPointer(0x49AD86 + 3, ms_ItemPriceMultipliersPerIsland);	// fmul    _itemPriceMultiplyerByTown[ecx*4]
		}
		else
		{
			CPatch::PatchMemoryData(
				0x8A6204,
				IslandLimits::ms_ItemPriceMultipliersPerIsland,
				IslandLimits::ms_iNumberOfIslands * sizeof(float)
			);
		}
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}
	
	CPatch::LeaveThisLevel();

	PrintToLog();
}

// Initialize
void IslandLimits::Initialise()
{
	this->ms_iNumberOfIslands = 0;

	this->ms_CopPedIDsPerIsland = NULL;
	this->ms_CopCarIDsPerIsland = NULL;
	this->ms_AmbulanceVehicleIDsPerIsland = NULL;
	this->ms_MedicPedIDsPerIsland = NULL;
	this->ms_FireEngineVehicleIDsPerIsland = NULL;
	this->ms_FiremanPedIDsPerIsland = NULL;
	this->ms_CabDriverPedIDsPerIsland = NULL;
	this->ms_CabDriverNumberOfPedIDsPerIsland = NULL;
	this->ms_ItemPriceMultipliersPerIsland = NULL;
}

// Shutdown
void IslandLimits::Shutdown()
{
	delete[] this->ms_CopPedIDsPerIsland;
	delete[] this->ms_CopCarIDsPerIsland;
	delete[] this->ms_AmbulanceVehicleIDsPerIsland;
	delete[] this->ms_MedicPedIDsPerIsland;
	delete[] this->ms_FireEngineVehicleIDsPerIsland;
	delete[] this->ms_FiremanPedIDsPerIsland;
	delete[] this->ms_CabDriverPedIDsPerIsland;
	delete[] this->ms_CabDriverNumberOfPedIDsPerIsland;
	delete[] this->ms_ItemPriceMultipliersPerIsland;
}
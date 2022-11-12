#include "TrainTypeCarriagesLoader.h"

#include "../Core/CCodeMover.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/CModelInfo.h"

#include <Array\countof.h>
#include <fileIO.h>
#include <IMG\IMGstructures.h>
#include <MultiPlatformSupport/PlatformGeneralisation.h>
#include <StrLexStuff.h>

using namespace Game;

CTrainTypeCarriagesLoader g_trainTypeCarriageLoader;

// Loads train type carriages
void CTrainTypeCarriagesLoader::LoadTrainTypeCarriages()
{
	if (bTrainTypeCarriagesLoaded)
		return;

	FILE* fp = fopen(g_LimitAdjuster.GetPathToFlaFileFromRootDirectory(this->m_filePath).c_str(), "r");

	if (!fp)
	{
		printf_MessageBox("Unable to load %s", this->m_filePath);
		g_LimitAdjuster.TerminateProcess();
	}
	
	char line[1024];

	while (LoadLineWithoutCommas(line, sizeof(line), fp))
	{
		char* iLine = FindFirstNonWhiteCharacter(line);

		if (!iLine[0] || iLine[0] == '#')
			continue;

		unsigned int typeID = (unsigned int)ReadIntegerNum(iLine, &iLine);

		if (typeID >= ms_numberOfTypeIDs)
		{
			printf_MessageBox(
				"Train carriage loader: type ID %d exceeds the limit of %d IDs.",
				typeID,
				ms_numberOfTypeIDs
				);

			continue;
		}

		int32_t* pTypeCarriageList = &TrainTypeCarriages.ptr[typeID * (ms_maxNumberOfVehiclesForType + 1)];

		char vehicleName[IMG_FASTMAN92_GTASA_MAX_FILENAME_LENGTH + 1];

		unsigned int index = 0;

		while (ReadIdentifier(vehicleName, sizeof(vehicleName), iLine, &iLine))
		{
			if (index >= ms_maxNumberOfVehiclesForType)
			{
				printf_MessageBox(
					"Train carriage loader: type ID %d, limit of number of vehicles per types exceeded.",
					typeID
					);

				break;
			}

			int modelID;

			if (!this->GetModelID(vehicleName, &modelID))
				break;

			pTypeCarriageList[index] = modelID;

			index++;
		}

		pTypeCarriageList[index] = this->m_undefinedModelID;
	}

	fclose(fp);

	bTrainTypeCarriagesLoaded = true;
}

// Sets undefined model ID
void CTrainTypeCarriagesLoader::SetUndefinedModelID(int modelID)
{
	this->m_undefinedModelID = modelID;
}

// Sets max number of vehicles for type
void CTrainTypeCarriagesLoader::SetMaxNumberOfVehicleForType(unsigned int newValue)
{
	this->ms_maxNumberOfVehiclesForType = newValue;
}

// Set number of type IDs
void CTrainTypeCarriagesLoader::SetNumberOfTypeIDs(unsigned int newValue)
{
	this->ms_numberOfTypeIDs = newValue;
}

// Sets filename
void CTrainTypeCarriagesLoader::SetFilename(const char* filename)
{
	strncpy(this->m_filePath, filename, _countof(this->m_filePath));
}

// Initializes
void CTrainTypeCarriagesLoader::Initialise()
{
	MAKE_VAR_GAME_VERSION();
	this->bTrainTypeCarriagesLoaded = false;

	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		this->SetFilename("data\\gtasa_trainTypeCarriages.dat");
		this->SetUndefinedModelID(0);
		this->ms_maxNumberOfVehiclesForType = 15;
		this->ms_numberOfTypeIDs = 16;
		#ifdef IS_PLATFORM_WIN_X86
		this->TrainTypeCarriages.ptr = (int32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x8D44F8);
		#endif
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
		this->SetFilename("common\\data\\gtaiv_trainTypeCarriages.dat");
		this->SetUndefinedModelID(-1);
		this->ms_maxNumberOfVehiclesForType = 15;
		this->ms_numberOfTypeIDs = 16;

		#ifdef IS_PLATFORM_WIN_X86
		if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			this->TrainTypeCarriages.ptr = (int32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x15BD508);
		else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			this->TrainTypeCarriages.ptr = (int32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x1405488);
		#endif
	}
}

// Shutdown
void CTrainTypeCarriagesLoader::Shutdown()
{
	if (TrainTypeCarriages.bIsAllocated.Get())
		delete[] TrainTypeCarriages.ptr;
}

// Prints to log
void CTrainTypeCarriagesLoader::PrintToLog()
{
	CGenericLogStorage::SaveFormattedTextLn(
		"Train type carriages loader is enabled. ms_numberOfTypeIDs = %d, ms_maxNumberOfVehiclesForType = %d.",
		ms_numberOfTypeIDs,
		ms_maxNumberOfVehiclesForType
		);

	CGenericLogStorage::WriteLineSeparator();
}

// Returns model ID by name
bool CTrainTypeCarriagesLoader::GetModelID(const char* modelName, int* pModelID)
{
	CBaseModelInfo_generic* pModelInfo = CModelInfo::GetModelInfo(modelName, pModelID);

	if (pModelInfo)
		return true;
	else
	{
		printf_MessageBox("Train carriage loader: model with name %s does not exist.", modelName);
		return false;
	}
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_CTrain__InitTrains_6F7446()
	{
		__asm
		{			
			mov ecx, ASM_GET_OFFSET_OF_FLA_MODULE(g_trainTypeCarriageLoader);
			call CTrainTypeCarriagesLoader::LoadTrainTypeCarriages;

			//////////////

			push ebx;
			xor     ebx, ebx;
			cmp eax, ebx;

			push 0x6F744B;
			retn;
		}
	}

	unsigned int sizeOfIDsInOneType;
	int32_t* ourTrainTypeCarriages;

	NAKED void patch_CTrain__CreateMissionTrain_6F75C7()
	{
		__asm
		{
			mov     eax, [esp + 6Ch + 0x14];
			imul eax, sizeOfIDsInOneType;

			push 0x6F75D1;
			retn;
		}
	}

	NAKED void patch_CTrain__DoTrainGenerationAndRemoval_6F7B10()
	{
		__asm
		{
			mov esi, ecx;
			imul esi, sizeOfIDsInOneType;

			push 0x6F7B15;
			retn;
		}
	}

	NAKED void patch_CTrain__DoTrainGenerationAndRemoval_6F7D29()
	{
		__asm
		{
			imul ecx, sizeOfIDsInOneType;
			add ecx, ourTrainTypeCarriages;

			push 0x6F7D32;
			retn;
		}
	}
}

namespace Game_GTAIV
{
	unsigned int Address_949232;

	NAKED void patch_9491C8()
	{
		__asm
		{
			mov ecx, ASM_GET_OFFSET_OF_FLA_MODULE(g_trainTypeCarriageLoader);
			call CTrainTypeCarriagesLoader::LoadTrainTypeCarriages;

			jmp Address_949232;
		}
	}
}
#endif

// Checks if loader is implemented for specified game version
bool CTrainTypeCarriagesLoader::IsLoaderImplementedForThisGameVersion(Game::eGameVersion gameVersion)
{
	return CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86;
}

// Applies loader
void CTrainTypeCarriagesLoader::ApplyLoader()
{
	MAKE_VAR_GAME_VERSION();

	if (!this->IsLoaderImplementedForThisGameVersion(gameVersion))
		return;
	
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

#ifdef IS_PLATFORM_WIN_X86
	unsigned int TotalNumberOfElements = (ms_maxNumberOfVehiclesForType + 1) * ms_numberOfTypeIDs;

	// Allocate memory
	if (ms_maxNumberOfVehiclesForType != 15 || ms_numberOfTypeIDs > 16)
	{
		TrainTypeCarriages.ptr = new __int32[TotalNumberOfElements];
		memset(TrainTypeCarriages.ptr, NULL, TotalNumberOfElements * sizeof(__int32));
		TrainTypeCarriages.bIsAllocated.Set(true);
	}

	// Set variables for automatic patch
	#if TRUE
	{
		CCodeMover::SetVariable("SIZEOF_IDS_IN_ONE_TYPE", (ms_maxNumberOfVehiclesForType + 1) * sizeof(__int32));
	}
	#endif

	// version specific code
	if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		// Patch pointer to TrainTypeCarriages
		#if TRUE
		{
			CPatch::PatchPointer(0x6F75D5 + 1, TrainTypeCarriages.ptr);	// add     eax, offset TrainTypeCarriages	; _ZN6CTrain18CreateMissionTrainE7CVectorbjPPS_S2_iib
			CPatch::PatchPointer(0x6F7B15 + 2, TrainTypeCarriages.ptr);	// add     esi, offset TrainTypeCarriages	; _ZN6CTrain27DoTrainGenerationAndRemovalEv
			CPatch::PatchPointer(0x6F7D2C + 2, TrainTypeCarriages.ptr);	// add     ecx, offset TrainTypeCarriages	; _ZN6CTrain27DoTrainGenerationAndRemovalEv
		}
		#endif
		
		// Size of IDs in one type
		#if TRUE
		{
			sizeOfIDsInOneType = (ms_maxNumberOfVehiclesForType + 1) * sizeof(__int32);
			ourTrainTypeCarriages = this->TrainTypeCarriages.ptr;

			CPatch::RedirectCode(0x6F75C7, &patch_CTrain__CreateMissionTrain_6F75C7);
			CPatch::RedirectCode(0x6F7B10, &patch_CTrain__DoTrainGenerationAndRemoval_6F7B10);
			CPatch::RedirectCode(0x6F7D29, &patch_CTrain__DoTrainGenerationAndRemoval_6F7D29);
		}
		#endif

		CPatch::RedirectCode(0x6F7446, &patch_CTrain__InitTrains_6F7446);
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
	{
		using namespace Game_GTAIV;

		// Patch pointers to TrainTypeCarriages
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9491B3 + 1), TrainTypeCarriages.ptr);	// mov     edi, offset TrainTypeCarriages	; sub_9491A0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9491F1 + 2), TrainTypeCarriages.ptr);	// mov     ss:TrainTypeCarriages[ebp], eax	; sub_9491A0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x94C1CB + 1), TrainTypeCarriages.ptr);	// add     eax, offset TrainTypeCarriages	; sub_94C140
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x94C7DC + 2), TrainTypeCarriages.ptr);	// add     esi, offset TrainTypeCarriages	; _ZN6CTrain27DoTrainGenerationAndRemovalEv
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x94C980 + 2), TrainTypeCarriages.ptr);	// add     edi, offset TrainTypeCarriages	; _ZN6CTrain27DoTrainGenerationAndRemovalEv
		}
		#endif

		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x9491AE + 1), TotalNumberOfElements);		

		Address_949232 = g_mCalc.GetCurrentVAbyPreferedVA(0x949232);
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x9491C8), &patch_9491C8);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 3
			CCodeMover::FixOnAddressRel(0x94C1C8, 8, "\x0e\x00\x02""SIZEOF_IDS_IN_ONE_TYPE\x00\x02\x05\xCB\xC1\x94\x00\x00", 0x94C1D0);	// line 1, 0x94C140 - sub_94C140 : shl     eax, 6
			CCodeMover::FixOnAddressRel(0x94C7D9, 9, "\x0e\x06\x02""SIZEOF_IDS_IN_ONE_TYPE\x00\x02\x06\xDC\xC7\x94\x00\x00", 0x94C7E2);	// line 2, 0x94C4F0 - _ZN6CTrain27DoTrainGenerationAndRemovalEv : shl     esi, 6
			CCodeMover::FixOnAddressRel(0x94C97D, 9, "\x0e\x07\x02""SIZEOF_IDS_IN_ONE_TYPE\x00\x02\x06\x80\xC9\x94\x00\x00", 0x94C986);	// line 3, 0x94C4F0 - _ZN6CTrain27DoTrainGenerationAndRemovalEv : shl     edi, 6
		}
		#endif
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
		using namespace Game_GTAIV;

		// Patch pointers to TrainTypeCarriages
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA4B3A3 + 1), TrainTypeCarriages.ptr);	// mov     edi, offset TrainTypeCarriages	; sub_A4B390
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA4B3E1 + 2), TrainTypeCarriages.ptr);	// mov     ss:TrainTypeCarriages[ebp], eax	; sub_A4B390
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA4E37B + 1), TrainTypeCarriages.ptr);	// add     eax, offset TrainTypeCarriages	; sub_A4E2F0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA4E98C + 2), TrainTypeCarriages.ptr);	// add     esi, offset TrainTypeCarriages	; sub_A4E6A0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA4EB30 + 2), TrainTypeCarriages.ptr);	// add     edi, offset TrainTypeCarriages	; sub_A4E6A0
		}
		#endif

		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xA4B39E + 1), TotalNumberOfElements);

		Address_949232 = g_mCalc.GetCurrentVAbyPreferedVA(0xA4B422);
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xA4B3B8), &patch_9491C8);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 3
			CCodeMover::FixOnAddressRel(0xA4E378, 8, "\x0e\x00\x02""SIZEOF_IDS_IN_ONE_TYPE\x00\x13\x05\x7B\xE3\x64\x00\x00", 0xA4E380);	// line 1, 0xA4E2F0 - sub_A4E2F0 : shl     eax, 6
			CCodeMover::FixOnAddressRel(0xA4E989, 9, "\x0e\x06\x02""SIZEOF_IDS_IN_ONE_TYPE\x00\x13\x06\x8C\xE9\x64\x00\x00", 0xA4E992);	// line 2, 0xA4E6A0 - sub_A4E6A0 : shl     esi, 6
			CCodeMover::FixOnAddressRel(0xA4EB2D, 9, "\x0e\x07\x02""SIZEOF_IDS_IN_ONE_TYPE\x00\x13\x06\x30\xEB\x64\x00\x00", 0xA4EB36);	// line 3, 0xA4E6A0 - sub_A4E6A0 : shl     edi, 6
		}
		#endif
	}

	// Unset variables of automatic patch
	#if TRUE
	{
		CCodeMover::DeleteVariable("SIZEOF_IDS_IN_ONE_TYPE");
	}
	#endif

	this->PrintToLog();	
#endif

	CPatch::LeaveThisLevel();
}
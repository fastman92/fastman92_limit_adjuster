/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

/*
MODEL_LIB_STREET10 = 3892,
Debugged application message: Registering a file ID 2000081, filename: levelmap_1.col

flora.col : cvetoc1, IMG: DATA\MAPS\real\real.IMG 
levelmap_1.col : lib_street10 IMG: data\maps\leveldes\levelmap.img 
*/

#pragma warning (disable : 4733 )

#include "ErrorReporting.h"
#include "FileIDlimit.h"
#include "IMGlimits.h"

#include "../Core/CPatch.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/CEntity.h"

#include <map>

using namespace Game;

ErrorReporting g_errorReporting;

void printf_Error(bool bTerminateGame, const char* format, ...)
{
#ifdef IS_PLATFORM_WIN
	va_list vl;
	va_start(vl, format);

	char buffer[4096];

	int l = _vsnprintf_s(buffer, _countof(buffer), _TRUNCATE, format, vl);

	CGenericLogStorage::SaveTextLn(buffer);

	printf_MessageBox(buffer);

	va_end(vl);
#endif

	if (bTerminateGame)
		g_LimitAdjuster.TerminateProcess();
}

void ErrorStreamHandlesLimitExceeded()
{
	printf_Error(false, "'Max number of stream handles', limit exceeded.");
}

#ifdef IS_ARCHITECTURE_32_BIT
namespace Game_GTASA
{
	bool IsModelIDvalidForCarGenerator(int32_t modelID)
	{
		if (modelID == -1)
			return true;

		if (modelID < -1)
			return false;

		auto numberOfModels = g_fileIDlimits.GetFileIDcurrentLimit(GENERAL_FILE_TYPE_MODEL_ARCHIVE);

		if (modelID > numberOfModels)
			return false;

		using namespace Game_GTASA;

		if (CBaseModelInfo* pModelInfo
			= g_fileIDlimits.CModelInfo__ms_modelInfoPtrs.gta_sa[modelID])
		{
			return ((uint8_t(__thiscall*)(CBaseModelInfo *)) *(void**)((char*)pModelInfo->vmt + 0x10))(pModelInfo) == 6;
		}
		else
			return false;
	}

	void __cdecl printError_invalidCarGeneratorModelID(float x, float y, float z, float angle, int32_t modelId)
	{
		printf_Error(
			false,
			"Car generator with invalid model ID getting registered.\n"
			"Model ID does not exist or is not vehicle. \n\n"
			"Car generator:\n"
			"position: %g %g %g\n"
			"angle: %g\n"
			"model ID: %d",

			x, y, z,
			angle,
			modelId
		);
	}
}
#endif

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	void __cdecl printError_5380C3(unsigned int ID)
	{
		printf_Error(
			false,
			"Error 0x5380C3, trying to load object instance with undefined ID: %d",
			ID
		);
	};

	NAKED void patch_CFileLoader__LoadObjectInstance_5380C3()
	{
		__asm
		{

			push eax;
			call printError_5380C3;
			add esp, 0x4;

			pop edi;
			pop esi;
			xor eax, eax;
			pop ebp;
			mov ecx, [esp + 0x30 - 0xC];
			mov dword ptr fs : [0], ecx;
			add esp, 0x30;
			retn;
		}
	}

	void __cdecl printError_534134(CEntity* pEntity)
	{
		printf_Error(
			true,
			"Error 0x534134, model ID %d does not have loaded collision.",
			pEntity->GetModelID()
		);
	}

	NAKED void patch_CEntity__GetBoundRect_534134()
	{
		__asm
		{
			test eax, eax;
			jz m_pColModelIsZero;

		goBack:
			mov edx, [eax];
			mov[esp + 0x10], edx;

			push 53413Ah;
			retn;

		m_pColModelIsZero:
			push eax;
			push ecx;

			push esi;
			call printError_534134;
			add esp, 4;

			pop ecx;
			pop eax;

			jmp goBack;
		}
	}

	void __cdecl printError_6F31D5(float x, float y, float z, float angle, uint32_t modelId)
	{
		printf_Error(
			false,
			"Can't add a unused car generator, limit exceeded.\n\n"
			"Car generator:\n"
			"position: %g %g %g\n"
			"angle: %g\n"
			"model ID: %d",

			x, y, z,
			angle,
			modelId
		);
	}

	NAKED void patch_CTheCarGenerators__CreateCarGenerator_6F31D5()
	{
		__asm
		{
			// ESP: 0x4
			push ecx;	// modelID

			// ESP: -0x8
			mov ecx, [esp + 0x8 + 0x10];	// angle
			push ecx;

			// ESP: -0xC
			mov ecx, [esp + 0xC + 0xC];	// z
			push ecx;

			// ESP: -0x10
			mov ecx, [esp + 0x10 + 0x8];	// y
			push ecx;

			// ESP: -0x14
			mov ecx, [esp + 0x14 + 4];	// x
			push ecx;

			// ESP: -0x18
			call printError_6F31D5;
			add esp, 5 * 4;

			or eax, -1;
			pop esi;
			retn;
		}
	}

	NAKED void patch_CCarGenerator__Setup_6F2E9E()
	{
		__asm
		{
			mov     eax, [esp + 4 + 0x14];

			push eax;
			call IsModelIDvalidForCarGenerator;
			add esp, 4;
			
			test al, al;
			jnz doReturn;

			// ESP: 0x4
			mov     ecx, [esp + 4 + 0x14];
			push ecx;	// modelID

			// ESP: -0x8
			mov ecx, [esp + 0x8 + 0x10];	// angle
			push ecx;

			// ESP: -0xC
			mov ecx, [esp + 0xC + 0xC];	// z
			push ecx;

			// ESP: -0x10
			mov ecx, [esp + 0x10 + 0x8];	// y
			push ecx;

			// ESP: -0x14
			mov ecx, [esp + 0x14 + 4];	// x
			push ecx;

			// ESP: -0x18
			call printError_invalidCarGeneratorModelID;
			add esp, 5 * 4;

			doReturn:
			mov     ax, [esp + 4 + 0x14];
			push 0x6F2EA3;
			retn;
		}
	}
}

static DWORD CStreaming_IMG_archiveExpectedFilePosition;
static bool CStreaming_IMG_archive_isFirstFile;
static bool CStreaming_IMG_archive_checkIfArchiveIsRebuilt;

namespace Game_GTASA
{
	// GTA_ERROR_IMG_ARCHIVE_NEEDS_REBUILDING
	NAKED void patch_CStreaming__LoadCdDirectory_5B61BD()
	{
		__asm
		{
			mov byte ptr[offset CStreaming_IMG_archive_isFirstFile], 1;
			mov dword ptr[offset CStreaming_IMG_archiveExpectedFilePosition], 0xFFFFFFFF;

			cmp dword ptr[esp + 0x60 + 4], ebx;
			je disableChecking;
			mov CStreaming_IMG_archive_checkIfArchiveIsRebuilt, 1;
			jmp goBack;

		disableChecking:

			mov CStreaming_IMG_archive_checkIfArchiveIsRebuilt, 0;

			// go back
		goBack:
			mov		eax, [esp + 60h - 38h];
			add		esp, 18h;
			push	5B61C4h;
			retn;
		}
	}

	// Prints error, archive needs rebuilding
	void printError_archiveNeedsRebuilding(
		const char* IMGpath,
		const char* fileEntryName,
		uint32_t positionInSectors,
		uint32_t expectedPositionInSectors
	)
	{
		printf_Error(
			false,
			"IMG archive needs rebuilding!\n\n"
			"IMG path: %s\n\n"
			"File entry:\n"
			"Name: %s\n"
			"Real position: 0x%X\n"
			"Expected position: 0x%X",

			IMGpath,
			fileEntryName,
			positionInSectors * IMG_ARCHIVE_SECTOR_SIZE,
			expectedPositionInSectors * IMG_ARCHIVE_SECTOR_SIZE
		);
	}

	// IMG archive needs rebuilding
	void __cdecl printError_5B61E6(const CStreamingFile* pIMGdescriptor, const CDirectoryEntry* pFileEntry)
	{
		printError_archiveNeedsRebuilding(
			pIMGdescriptor->m_name,
			pFileEntry->Name,
			pFileEntry->PositionInSectors,
			CStreaming_IMG_archiveExpectedFilePosition
		);
	}

	NAKED void patch_CStreaming__LoadCdDirectory_5B61E6()
	{
		__asm
		{
			// movzx ecx, word ptr[esp+58h-20h+0];	// position in blocks

			// cmp ecx, [CStreaming_IMG_archiveExpectedFilePosition];

			cmp CStreaming_IMG_archive_checkIfArchiveIsRebuilt, 0;
			jz goBack;

			cmp	CStreaming_IMG_archive_isFirstFile, 0;
			jnz updateExpectedPosition;

			mov eax, [esp + 58h - 20h + 0];	// position in blocks
			cmp CStreaming_IMG_archiveExpectedFilePosition, eax;
			jz updateExpectedPosition;

			lea ecx, [esp + 58h - 20h];
			push ecx;

			mov eax, [esp + 5Ch + 4];
			push eax;

			call printError_5B61E6;

			add esp, 8;

			mov CStreaming_IMG_archive_checkIfArchiveIsRebuilt, 0;

		updateExpectedPosition:
			mov ecx, [esp + 58h - 20h + 0];	// position in blocks
			movzx eax, word ptr[esp + 58h - 20h + 4];	// streaming size in blocks
			add ecx, eax;
			mov CStreaming_IMG_archiveExpectedFilePosition, ecx;
			mov CStreaming_IMG_archive_isFirstFile, 0;

			// go back
			push 5B61EBh;
			retn;

		goBack:
			movzx eax, word ptr[esp + 58h - 20h + 4];	// streaming size in blocks
			push 5B61EBh;
			retn;
		}
	}

	void __cdecl printError_modelHasCollisionAlreadySetUp(CBaseModelInfo* pModelInfo)
	{
		__int32 modelID = g_fileIDlimits.FindModelIDbyModelInfo(pModelInfo);

		if (g_fileIDlimits.IsSpecialModelID(modelID))
			return;

		if (modelID != UNDEFINED_FILE_ID_INT32)
			printf_Error(false, "Model ID %d has collision already set up!", modelID);
		else
			printf_Error(false, "Model of which ID cannot be found has collision already set up!");
	}

	NAKED void patch_CBaseModelInfo__SetColModel_4C4BD0()
	{
		__asm
		{
			cmp[ecx + CBaseModelInfo::m_pColModel], 0;
			jz defaultThing;

			push ecx;
			push edx;

			push ecx;
			call printError_modelHasCollisionAlreadySetUp;
			add esp, 4;

			pop edx;
			pop ecx;

		defaultThing:
			test    dl, dl;
			mov[ecx + CBaseModelInfo::m_pColModel], esi;

			push 0x4C4BD5;
			retn;
		}
	}

	bool IsFileInfoSetUp(int32_t ID)
	{
		if (ID >= 0)
		{
			unsigned int BlockOffsetWithStreamHandle;
			unsigned int BlockCount;

			CStreamingInfo* fileInfo = &g_fileIDlimits.CStreaming__ms_aInfoForModel.gta_sa[ID];

			return fileInfo->GetCdPosnAndSize
			(
				BlockOffsetWithStreamHandle,
				BlockCount
			);
		}

		return false;
	}

	// Returns true if if file info should be set up 
	bool ShouldFileInfoBeSetUp(__int32 ID)
	{
		if (ID >= 374 && ID <= 383)
			return false;		

		if (ID >= g_fileIDlimits.GetBaseID(FILE_TYPE_TXD)
			&& ID <= g_fileIDlimits.GetLastIDforType(FILE_TYPE_TXD)
			)
		{
			int TXDindex = ID - g_fileIDlimits.GetBaseID(FILE_TYPE_TXD);
			TxdDef* pDef = ACCESS_DEF(g_fileIDlimits.CTxdStore__pTxdPool.gta_sa)->GetAt(TXDindex);

			if (pDef)
				return pDef->hash != 0xdb3ae563	// VEHICLE
				&& pDef->hash != 0x56f5a036;	// GENERIC	
		}

		return true;
	}

	void __cdecl printError_CStreaming__RequestModel_4087EA(__int32 ID)
	{
		if (ShouldFileInfoBeSetUp(ID) && !IsFileInfoSetUp(ID))
			printf_Error(
				false, "Error 0x4087EA, file with undefined ID requested: %d",
				ID
			);
	}

	NAKED void patch_CStreaming__RequestModel_4087EA()
	{
		__asm
		{
			push ebp;
			call printError_CStreaming__RequestModel_4087EA;
			add esp, 4;

			push esi;
			push edi;
			lea     edi, [ebp + ebp * 4 + 0];

			push 0x4087F0;
			retn;
		}
	}

	// Look for duplicate model hashes
	void LookForDuplicates()
	{
		std::map<uint32_t, std::vector<unsigned int>> mapOfHashes;

		unsigned int countOfModels = g_fileIDlimits.GetFileIDcurrentLimit(FILE_TYPE_DFF);

		for (unsigned int ID = 0; ID < countOfModels; ID++)
		{
			CBaseModelInfo* pModelInfo = g_fileIDlimits.CModelInfo__ms_modelInfoPtrs.gta_sa[ID];

			if (pModelInfo && pModelInfo->m_dwKey)
				mapOfHashes[pModelInfo->m_dwKey].push_back(ID);
		}

		for (std::map<uint32_t, std::vector<unsigned int>>::iterator it = mapOfHashes.begin(); it != mapOfHashes.end(); ++it)
		{
			unsigned int hash = it->first;
			unsigned int countOfIDs = it->second.size();

			if (countOfIDs > 1)
			{
				std::string strIDs;

				for (unsigned int ID : it->second)
				{
					char strID[20];
					_itoa(ID, strID, 10);

					strIDs += strID;
					strIDs += ", ";
				}

				printf_Error(
					false, "Error, model hash 0x%X is declared on multiple IDs: %s",
					hash,
					strIDs.c_str()
				);
			}
		}
	}

	NAKED void patch_CFileLoader__LoadLevel_5B924E()
	{
		__asm
		{
			call LookForDuplicates;


			push 0x869B30;

			push 0x5B9253;
			retn;
		}
	}

	// stream handles limit exceeded
	uintptr_t Address_CdStreamOpen_loop;
	static uintptr_t Address_CdStreamOpen_setLastError;

	NAKED void patch_CdStreamOpen_ID_check()
	{
		__asm
		{
			cmp     esi, 32;
			jl      CdStreamOpen_loop;

			call ErrorStreamHandlesLimitExceeded;

			jmp[Address_CdStreamOpen_setLastError];

		CdStreamOpen_loop:
			jmp Address_CdStreamOpen_loop;
		}
	}
}
#endif


// Initializes
void ErrorReporting::Initialise()
{
	memset(ErrorReporting::m_bErrorEnabled, false, GTA_ERROR_MAX);
}

// Shutdown
void ErrorReporting::Shutdown()
{
}

// Switches error state
void ErrorReporting::SwitchErrorEnabled(eErrorType type, bool bEnable)
{
	this->m_bErrorEnabled[type] = bEnable;
}

// Returns true if error is enabled.
bool ErrorReporting::IsErrorEnabled(eErrorType type)
{
	return this->m_bErrorEnabled[type];
}

// Applies patch of error reporting
void ErrorReporting::ApplyHook()
{
	MAKE_VAR_GAME_VERSION();	

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		CGenericLogStorage::SaveFormattedTextLn("Error reporting going to be applied.");
		
		if (IsErrorEnabled(GTA_ERROR_ATTEMPT_TO_LOAD_OBJECT_INSTANCE_WITH_UNDEFINED_ID))
		{
			CPatch::RedirectCode(0x5380C3, &patch_CFileLoader__LoadObjectInstance_5380C3);

			CGenericLogStorage::SaveFormattedTextLn("GTA_ERROR_ATTEMPT_TO_LOAD_OBJECT_INSTANCE_WITH_UNDEFINED_ID enabled.");
		}

		if (IsErrorEnabled(GTA_ERROR_MODEL_DOES_NOT_HAVE_COLLISION_LOADED))
		{
			CPatch::RedirectCode(0x534134, &patch_CEntity__GetBoundRect_534134);

			CGenericLogStorage::SaveFormattedTextLn("GTA_ERROR_MODEL_DOES_NOT_HAVE_COLLISION_LOADED enabled.");
		}

		if (IsErrorEnabled(GTA_ERROR_MODEL_HAS_COLLISION_ALREADY_SET_UP))
		{
			CPatch::RedirectCode(0x4C4BD0, &patch_CBaseModelInfo__SetColModel_4C4BD0);

			CGenericLogStorage::SaveFormattedTextLn("GTA_ERROR_MODEL_HAS_COLLISION_ALREADY_SET_UP enabled.");
		}

		if (IsErrorEnabled(GTA_ERROR_CAR_GENERATOR_LIMIT_EXCEEDED))
		{
			CPatch::RedirectCode(0x6F31D5, &patch_CTheCarGenerators__CreateCarGenerator_6F31D5);

			// debug
			// CPatch::RedirectCodeOneByte(0x6F31BE, 0x6F31D5);

			CGenericLogStorage::SaveFormattedTextLn("GTA_ERROR_CAR_GENERATOR_LIMIT_EXCEEDED enabled.");
		}

		if (IsErrorEnabled(GTA_ERROR_CAR_GENERATOR_WITH_INVALID_MODEL_ID_IS_GETTING_REGISTERED))
		{
			CPatch::RedirectCode(0x6F2E9E, &patch_CCarGenerator__Setup_6F2E9E);
			CGenericLogStorage::SaveFormattedTextLn("GTA_ERROR_CAR_GENERATOR_WITH_INVALID_MODEL_ID_IS_GETTING_REGISTERED enabled.");
		}

		if (IsErrorEnabled(GTA_ERROR_IMG_ARCHIVE_NEEDS_REBUILDING))
		{
			CPatch::RedirectCode(0x5B61BD, &patch_CStreaming__LoadCdDirectory_5B61BD);
			CPatch::RedirectCode(0x5B61E6, &patch_CStreaming__LoadCdDirectory_5B61E6);

			CGenericLogStorage::SaveFormattedTextLn("GTA_ERROR_IMG_ARCHIVE_NEEDS_REBUILDING enabled.");
		}

		if (IsErrorEnabled(GTA_ERROR_REQUESTED_FILE_DOES_NOT_EXIST))
		{
			CPatch::RedirectCode(0x4087EA, &patch_CStreaming__RequestModel_4087EA);

			// debug
			// CPatch::RedirectCodeOneByte(0x6F31BE, 0x6F31D5);

			CGenericLogStorage::SaveFormattedTextLn("GTA_ERROR_REQUESTED_FILE_DOES_NOT_EXIST enabled.");
		}

		if (IsErrorEnabled(GTA_ERROR_MODEL_NAME_IS_DECLARED_ON_MULTIPLE_IDS))
		{
			CPatch::RedirectCode(0x5B924E, &patch_CFileLoader__LoadLevel_5B924E);
			CGenericLogStorage::SaveFormattedTextLn("GTA_ERROR_MODEL_NAME_IS_DECLARED_ON_MULTIPLE_IDS enabled.");
		}

		if (IsErrorEnabled(GTA_ERROR_STREAM_HANDLES_LIMIT_EXCEEDED))
		{
			Address_CdStreamOpen_loop = GetAddressToCdStreamOpen_loop();
			Address_CdStreamOpen_setLastError = GetAddress_CdStreamOpen_setLastError();

			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
				CPatch::RedirectCode(0x406813, &patch_CdStreamOpen_ID_check);
			else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
				CPatch::RedirectCode(0x1564AF3, &patch_CdStreamOpen_ID_check);

			CGenericLogStorage::SaveFormattedTextLn("GTA_ERROR_STREAM_HANDLES_LIMIT_EXCEEDED enabled.");
		}
	}
	else
		return;
#endif

	CGenericLogStorage::SaveFormattedTextLn("Error reporting is applied now.");
	CGenericLogStorage::WriteLineSeparator();
}
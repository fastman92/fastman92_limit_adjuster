/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CStreamingDebug.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/StringFunctions.h"
#include "FileIDlimit.h"
#include "../Core/LimitAdjuster.h"
#include "../GameStructures/CStreaming.h"
#include "../GameStructures/Renderware.h"
#include "../GameStructures/RwStream.h"
#include <vector>



#ifdef IS_PLATFORM_WIN_X86
#include <MinHook\include\MinHook.h>

namespace Game_GTASA
{
	

	// Cheat hash keys
	char* CCheat__m_CheatString = (char*)0x969110;

	bool TestCheatString(const char* str)
	{
		int l = strlen(str);

		if (!l)
			return false;

		const char* iStr = str + l - 1;
		const char* iCheatStr = CCheat__m_CheatString;

		do
		{
			if (*iStr != *iCheatStr)
				return false;

			iStr--;
			iCheatStr++;
		} while (iStr >= str);

		*CCheat__m_CheatString = NULL;

		return true;
	}

	void (__cdecl* fpCTheScripts__Process)() = (void(__cdecl*)())0x46A000;	

	void __cdecl CStreamingDebug::Detoured_CTheScripts__Process()
	{
		CStreamingDebug::ProcessDebugging();

		return fpCTheScripts__Process();
	}

	void(__cdecl* fpCStreaming__RequestModel)(int dwModelId, int flags);

	bool bIsMemoryTestNow = false;

	// Detoured_CStreaming::RequestModel
	void CStreamingDebug::Detoured_CStreaming__RequestModel(int dwModelId, int flags)
	{
		if (bIsMemoryTestNow)
		{
			eFileType type = g_fileIDlimits.GetFileIDtype(dwModelId);
			const char* sType = CFileTypeInfo::GetEnumNameByMember(type);
			
			int index = dwModelId - g_fileIDlimits.GetBaseID(type);

			CGenericLogStorage::SaveFormattedTextLn(
				"RequestModel, file ID: %d File type: %s Index: %d",
				dwModelId, sType, index
				);		
		}

		fpCStreaming__RequestModel(dwModelId, flags);
	}

	CStreamingInfo *CStreaming__ms_pStartLoadedList = (CStreamingInfo*)0x8E4C60;
	CStreamingInfo *CStreaming__ms_pEndLoadedList = (CStreamingInfo*)0x8E4C5C;

	NAKED void ReturnTrue()
	{
		__asm
		{
			mov al, 1;
			retn;
		}
	}

	NAKED void NOP_CStreaming__ConvertBufferToObject()
	{
		__asm
		{
			mov al, 1;
			retn;
		}
	}

	NAKED void NOP_CStreaming__ConvertBufferToObject_DFF()
	{
		__asm
		{
			mov     byte ptr[esp + 30h + 4], al;
			
			push 0x40C81B;
			retn;
		}
	}

	NAKED void CStreaming__AddToLoadedVehiclesList()
	{
		__asm
		{
			mov al, 1;
			retn;
		}
	}

	NAKED void patch_74B4D6()
	{
		__asm
		{

			mov eax, esi;

			pop edi;
			pop esi;
			pop ebp;
			pop ebx;
			add esp, 44h;
			retn;			
		}
	}

	NAKED void patch_74D23E()
	{
		__asm
		{
			mov eax, esi;

			pop     edi;
			pop     esi;
			pop     ebp;
			pop     ebx;
			add     esp, 3Ch;
			retn;
		}
	}




	std::vector<RpAtomic*> ms_LivingRpAtomicObjects;

//	std::vector<RpHAnimHierarchy*> ms_LivingRpAtomicObjects;

	bool IsMatrixValid(RwMatrix* pMatrix)
	{
		float maxValue = 400000.0;
		float minValue = -maxValue;

		return
			pMatrix->at.x >= minValue && pMatrix->at.x <= maxValue
			&& pMatrix->at.y >= minValue && pMatrix->at.y <= maxValue
			&& pMatrix->at.z >= minValue && pMatrix->at.y <= maxValue

			&& pMatrix->right.x >= minValue && pMatrix->right.x <= maxValue
			&& pMatrix->right.y >= minValue && pMatrix->right.y <= maxValue
			&& pMatrix->right.z >= minValue && pMatrix->right.y <= maxValue

			&& pMatrix->top.x >= minValue && pMatrix->top.x <= maxValue
			&& pMatrix->top.y >= minValue && pMatrix->top.y <= maxValue
			&& pMatrix->top.z >= minValue && pMatrix->top.y <= maxValue

			&& pMatrix->pos.x >= minValue && pMatrix->pos.x <= maxValue
			&& pMatrix->pos.y >= minValue && pMatrix->pos.y <= maxValue
			&& pMatrix->pos.z >= minValue && pMatrix->pos.y <= maxValue;
	}

	int lastIDofClump = -1;

	void CheckMatrix(RwMatrix* pMatrix, RwMatrix* pMatrixUnaligned, uint32_t additionalPtr = NULL)
	{
		if (!IsMatrixValid(pMatrix))
		{
			printf_MessageBox(
				"Matrix pointer: 0x%X\n"
				"Matrix pointer unaligned: 0x%X\n\n"
				"Additional info: 0x%X\n"
				"Right: %.3f %.3f %.3f\n"
				"Top: %.3f %.3f %.3f\n"
				"At: %.3f %.3f %.3f\n"
				"Pos: %.3f %.3f %.3f\n"

				"\nNumber of living RpAtomic objects: %d\n"
				"Last ID loaded: %d"

				,

				pMatrix,
				pMatrixUnaligned,
				additionalPtr,

				pMatrix->right.x,
				pMatrix->right.y,
				pMatrix->right.z,

				pMatrix->top.x,
				pMatrix->top.y,
				pMatrix->top.z,

				pMatrix->at.x,
				pMatrix->at.y,
				pMatrix->at.z,

				pMatrix->pos.x,
				pMatrix->pos.y,
				pMatrix->pos.z,

				ms_LivingRpAtomicObjects.size(),
				lastIDofClump

				);
		}
	}

	void __cdecl ValidateMatricesOfSkinPluginData(RpHAnimHierarchy* pAtomicSkinPluginData, uint32_t additionalPtr = NULL)
	{
		uint32_t count = pAtomicSkinPluginData->numNodes;
		RwMatrix* pMatrixArray = pAtomicSkinPluginData->pMatrixArray;

		if (!pMatrixArray)
			return;

		for (unsigned int i = 0; i < count; i++)
			CheckMatrix(pMatrixArray + i, pAtomicSkinPluginData->pMatrixArrayUnaligned, additionalPtr);
	}
	
	void GetCountAndSkinMatricesOfRpAtomic(
		RpAtomic* pAtomic,
		uint32_t& count,
		RwMatrix*& pArray
		)
	{
		uint32_t atomicSkinOffset = *(uint32_t*)0xC978A4;
		RpHAnimHierarchy* pSkinPluginData = *(RpHAnimHierarchy**)((char*)pAtomic + atomicSkinOffset);

		if (pSkinPluginData && (uint32_t)pSkinPluginData != 0xFFFFFFFF)
		{
			count = pSkinPluginData->numNodes;
			pArray = pSkinPluginData->pMatrixArray;
		}
		else
		{
			count = 0;
			pArray = NULL;
		}
	}


	void __cdecl ValidateMatricesOfRpAtomic(RpAtomic *pAtomic, uint32_t additionalPtr = NULL)
	{
		uint32_t atomicSkinOffset = *(uint32_t*)0xC978A4;
		RpHAnimHierarchy* pSkinPluginData = *(RpHAnimHierarchy**)((char*)pAtomic + atomicSkinOffset);

		if (pSkinPluginData)
			ValidateMatricesOfSkinPluginData(pSkinPluginData, additionalPtr);
	}

	void __cdecl ValidateMatricesOfRxPipelineNodeParam(RxPipelineNodeParam *pNodeParam, uint32_t additionalPtr = NULL)
	{
		ValidateMatricesOfRpAtomic((RpAtomic *)pNodeParam->dataParam, additionalPtr);
	}

	RpHAnimHierarchy *__cdecl RpSkinGeometryGetSkin(RpClump *clump)
	{
		return ((RpHAnimHierarchy *(__cdecl*) (RpClump *clump))0x734B10)(clump);
	}

	RpHAnimHierarchy* GetRpHanimHierarchyOfRpClump(RpClump* pClump)
	{


		
		RpAtomic* firstAtomic = ((RpAtomic *(__cdecl*)(RpClump *clump))0x734820)(pClump);


		// if (!firstAtomic)
		// 	return NULL;
			
		if (!pClump->object.parent)
			return NULL;

		return RpSkinGeometryGetSkin(pClump);
	}
	

	void __cdecl AddLivingRpAtomic(RpAtomic* pAtomic)
	{
		
		// if (ms_LivingRpAtomicObjects.size() == 0)
		//	printf_MessageBox("Creating first RpAtomic: 0x%X", pAtomic);

		/*
		unsigned AtomicID = 0;

		for (RpAtomic* ptr : ms_LivingRpAtomicObjects)
		{
			uint32_t countOfMatrices;
			RwMatrix* pMatrixArray;

			GetCountAndSkinMatricesOfRpAtomic(
				ptr,
				countOfMatrices,
				pMatrixArray
				);

			if (pMatrixArray)
			{
				// CGenericLogStorage::SaveFormattedTextLn("count: %d pMatrixArray: 0x%X", countOfMatrices, pMatrixArray);
				// CGenericLogStorage::SaveWorkBuffer();

				for (unsigned int i = 0; i < countOfMatrices; i++)
					CheckMatrix(pMatrixArray + i, (uint32_t)ptr);
			}

			AtomicID++;
		}
		*/
		

		ms_LivingRpAtomicObjects.push_back(pAtomic);
	}

	bool __cdecl DoesLivingRpAtomicExist(RpAtomic* pAtomic)
	{
		return std::find(
			ms_LivingRpAtomicObjects.begin(),
			ms_LivingRpAtomicObjects.end(),
			pAtomic
			) != ms_LivingRpAtomicObjects.end();
	}

	void __cdecl RemoveLivingRpAtomic(RpAtomic* pAtomic)
	{
		


		auto it = std::find(
			ms_LivingRpAtomicObjects.begin(),
			ms_LivingRpAtomicObjects.end(),
			pAtomic
			);

		// if(it == ms_LivingRpAtomicObjects.begin())
			// printf_MessageBox("Destroying RpAtomic: 0x%X", pAtomic);

		ms_LivingRpAtomicObjects.erase(it);
	}

	void __cdecl RpHAnimHierarchyIsBeingCreated(RpHAnimHierarchy* pHierarchy)
	{
		printf_MessageBox("RpHAnimHierarchyIsBeingCreated");

		if (pHierarchy->numNodes)
			memset(pHierarchy->pMatrixArray, 0x65, pHierarchy->numNodes * sizeof(RwMatrix));
		

		// memset(pHierarchy, 0x65, sizeof(RpHAnimHierarchy));
	}

	NAKED void patch_7C4D21()
	{
		__asm
		{
			push esi;
			call RpHAnimHierarchyIsBeingCreated;
			add esp, 4;

			mov eax, esi;
			pop edi;
			pop esi;
			pop ebx;
			retn;
		}
	}

	void delete_8213AE_debug(void* ptr)
	{
		memset(ptr, 0x49, 200);
		((void(__cdecl*)(void* ptr))0x8213AE)(ptr);
	}

	class CMemoryRestorer
	{
	public:
		std::vector<tMemoryRestorerEntry> m_Entries;
		 
		// Adds memory entry
		void AddMemoryEntry(void* ptr, int iSize)
		{
			tMemoryRestorerEntry entry;
			entry.iSize = iSize;
			memcpy(entry.data, ptr, iSize);
			entry.ptr = ptr;

			this->m_Entries.push_back(entry);
		}

		// Restores all entries
		void RestoreAllEntries()
		{
			for (tMemoryRestorerEntry& entry : this->m_Entries)
				CPatch::PatchMemoryData((uintptr_t)entry.ptr, entry.data, entry.iSize);
			
			m_Entries.clear();
		}
	};

	CMemoryRestorer memoryRestorer;

	void DisableAllRWpluginsInList(RwPluginRegistry *pRegistry)
	{
		RwPluginRegEntry *pEntry = pRegistry->firstRegEntry;

		while (pEntry)
		{
			memoryRestorer.AddMemoryEntry(&pEntry->pluginID, sizeof(pEntry->pluginID));

			pEntry->pluginID = 0xCABAFDED;

			pEntry = pEntry->nextRegEntry;
		}
	}

	void ErrorHappened()
	{
		printf_MessageBox("error happened!");
	}

	NAKED void patch_74D293()
	{
		__asm
		{
			add esp, 0Ch;

			cmp     eax, edi;
			jnz     loc_74D522;

			push 0x74D29E;
			retn;

		loc_74D522:
			call ErrorHappened;

			push 0x74D522;
			retn;
		}
	}

	RpClump* RpClumpStreamRead_debug(RwStream *stream)
	{
		CPatch::EnterNewLevel();
		CPatch::GetPointerToSettings()->bPatchForbiddenCheck = false;
		//////////

		if(0)
		{			
			const uintptr_t toBeDisabledArray[] =
			{
				0x8E2270,	// _frameTKList
				0x8D624C,	// _atomicTKList
				0x8D628C,   // _geometryTKList
				0x8D62A4,	// _materialTKList
				0x8D62D0,	// _worldTKList
				0x8D6264,   // _clumpTKList
				0x8D736C,   // _sectorTKList

				0x8D62F8,   // _lightTKList
				0x8E23CC,	// _textureTKList
				0x8E222C    // _cameraTKList
			};

			/*
			for(uintptr_t pRegistry : toBeDisabledArray)
				DisableAllRWpluginsInList((RwPluginRegistry*)pRegistry);

				*/
			
			// memoryRestorer.AddMemoryEntry((void*)0x74B4D6, 5);
			// CPatch::RedirectCode(0x74B4D6, &patch_74B4D6);



			memoryRestorer.AddMemoryEntry((void*)0x74B7D2, 5);
			CPatch::RedirectCode(0x74B7D2, &patch_74B4D6);

			memoryRestorer.AddMemoryEntry((void*)0x74B7D0, 2);
			CPatch::NOPinstructions(0x74B7D0, 2);

			// geometry function
			memoryRestorer.AddMemoryEntry((void*)0x74D23E, 5);
			// CPatch::RedirectCode(0x74D23E, &patch_74D23E);

			// memoryRestorer.AddMemoryEntry((void*)0x74D296, 5);
			// CPatch::RedirectCode(0x74D296, &patch_74D23E);	// bug?

			// memoryRestorer.AddMemoryEntry((void*)0x74D293, 5);
			// CPatch::RedirectCode(0x74D293, &patch_74D293);

			memoryRestorer.AddMemoryEntry((void*)0x74D28E, 5);
			// CPatch::NOPinstructions(0x74D28E, 5);

			// memoryRestorer.AddMemoryEntry((void*)0x74D29E, 5);
			// CPatch::RedirectCode(0x74D29E, &patch_74D23E);

			// memoryRestorer.AddMemoryEntry((void*)0x74D29E, 0x74D2B8 - 0x74D29E);
			// CPatch::NOPinstructions(0x74D29E, 0x74D2B8 - 0x74D29E);
			// CPatch::NOPinstructions(0x74D2B5, 3);

			// memoryRestorer.AddMemoryEntry((void*)0x74D522, 5);
			// CPatch::RedirectCode(0x74D522, &patch_74D23E);

			// memoryRestorer.AddMemoryEntry((void*)0x74D2A5, 5);
			// CPatch::RedirectCode(0x74D2A5, &patch_74D23E);

			memoryRestorer.AddMemoryEntry((void*)0x74D2B8, 5);
			CPatch::RedirectCode(0x74D2B8, &patch_74D23E);

			memoryRestorer.AddMemoryEntry((void*)0x74D2DD, 5);
			CPatch::RedirectCode(0x74D2DD, &patch_74D23E);

			memoryRestorer.AddMemoryEntry((void*)0x74D333, 5);
			CPatch::RedirectCode(0x74D333, &patch_74D23E);

			// printf_MessageBox("wfasd");
		}
		
		//////////////////////////////////////////////////////
		RpClump* result;

	

		result = ((RpClump* (__cdecl*)(RwStream* stream))0x74B420)(stream);	// RpClumpStreamRead

		if(0)
		{
			result->atomicList.link.prev = (RwFrame *)&result->atomicList;
			result->atomicList.link.next = (RwFrame *)&result->atomicList.link.next;
			result->lightList.link.prev = (RwFrame *)&result->lightList;
			result->object.type = 2;
			result->lightList.link.next = (RwFrame *)&result->lightList.link.next;
			result->object.subType = 0;
			result->object.flags = 0;
			result->object.privateFlags = 0;
			result->object.parent = 0;
			result->cameraList.link.next = (RwFrame *)&result->cameraList.link.next;
			result->cameraList.link.prev = (RwFrame *)&result->cameraList;
			result->inWorldLink.prev = 0;
			result->inWorldLink.next = 0;
		}
		

		{
			// result->atomicList.link.prev = (RwFrame *)&result->atomicList;
			// result->atomicList.link.next = (RwFrame *)&result->atomicList.link.next;
			// result->lightList.link.prev = (RwFrame *)&result->lightList;
			// result->object.type = 2;
			// result->lightList.link.next = (RwFrame *)&result->lightList.link.next;
			// result->object.subType = 0;
			// result->object.flags = 0;
			// result->object.privateFlags = 0;
			// result->object.parent = 0;
			// result->cameraList.link.next = (RwFrame *)&result->cameraList.link.next;
			// result->cameraList.link.prev = (RwFrame *)&result->cameraList;
			// result->inWorldLink.prev = 0;
			// result->inWorldLink.next = 0;
		}
		// result->callback = (int)ClumpCallBack;

		// result = NULL;
		//////////////////////////////////////////////////////

		memoryRestorer.RestoreAllEntries();

		//////////


		CPatch::LeaveThisLevel();

		return result;
	}

	struct RpAtomicSavedInfo
	{
		RpAtomic* pAtomic;


	};

	// Processes debugging
	void CStreamingDebug::ProcessDebugging()
	{
		int startID = 300;
		int endID = 11000;

		if (TestCheatString("LIMIT"))
		{
			for (int ID = startID; ID < endID; ID++)
			{
				if (((bool(__cdecl*)(int index))0x407800)(ID))	// does model exist
					CStreaming::RequestModel(ID, 12);
			}

			CStreaming::LoadAllRequestedModels(false);
			return;


			bIsMemoryTestNow = true;

			// CPatch::RedirectFunction(0x40C6B0, &NOP_CStreaming__ConvertBufferToObject);
			// CPatch::RedirectCode(0x40C89C, 0x40CABC);

			// NOP loading functions
			{
				CPatch::RedirectCode(0x4106E2, 0x410723);	// NOP CColStore::LoadCol

				// CAnimManager::LoadAnimFile
				{
					CPatch::RedirectCode(0x4D522C, 0x4D5591);
					CPatch::RedirectCode(0x4D4935, 0x4D5591);
					CPatch::NOPinstructions(0x40CA84, 5);
				}

				// CStreamedScripts::LoadStreamedScript2
				CPatch::RedirectCode(0x47085F, 0x470882);

				// CPathFind::LoadPathFindData
				CPatch::PatchBYTE(0x4529F0, 0xC3);

				// CIplStore::LoadIpl
				CPatch::RedirectCode(0x406098, 0x406348);

				// DFF
				{
					// CPatch::RedirectCode(0x40C77E, &NOP_CStreaming__ConvertBufferToObject_DFF);

					// CPatch::RedirectFunction(0x5371F0, &ReturnTrue);	// CFileLoader::LoadAtomicFile

					#if TRUE
					{
						// CPatch::NOPinstructions(0x53724C, 5);
						CPatch::NOPinstructions(0x53725A, 7);
					}
					#endif

					// CPatch::PatchBYTE(0x537150, 0xC3);	// CFileLoader::SetRelatedModelInfoCB

					CPatch::RedirectCode(0x537197, 0x5371B2);
					// CPatch::NOPinstructions(0x5371BD, 5);
					// CPatch::NOPinstructions(0x5371C4, 5);
					// CPatch::PutOnAddressRelative4byteAddressToAddress(0x537231 + 1, (uintptr_t)&RpClumpStreamRead_debug);
					// CPatch::PutOnAddressRelative4byteAddressToAddress(0x537231 + 1, (uintptr_t)&RpClumpStreamRead_debug);

					CPatch::RedirectFunction(0x408000, &CStreaming__AddToLoadedVehiclesList);
				}

				// CPatch::RedirectCode(0x40C77E, 0x40C81B);
			}

			////////
			

			std::vector<RpAtomicSavedInfo> savedRpAtomicInfos;

//			uint32_t countOfMatrices;
//			RwMatrix* pMatrixArray;

			#if FALSE
			for (RpAtomic* ptr : ms_LivingRpAtomicObjects)
			{
				RpAtomicSavedInfo info;
				info.pAtomic = ptr;



				GetCountAndSkinMatricesOfRpAtomic(
					info.pAtomic,
					countOfMatrices,
					pMatrixArray
					);

				if (pMatrixArray)
				{
					for (unsigned int i = 0; i < countOfMatrices; i++)
						CheckMatrix(pMatrixArray + i);
				}
				
												
				savedRpAtomicInfos.push_back(info);
			}
			#endif

			printf_MessageBox("Models will be loaded now!");
			

			#if FALSE
			{
				for (RpAtomicSavedInfo& info : savedRpAtomicInfos)
				{
					if (!DoesLivingRpAtomicExist(info.pAtomic))
						printf_MessageBox("RpAtomic is dead: 0x%X", info.pAtomic);
					else
					{

						GetCountAndSkinMatricesOfRpAtomic(
							info.pAtomic,
							countOfMatrices,
							pMatrixArray
							);

						if (pMatrixArray)
						{
							for (unsigned int i = 0; i < countOfMatrices; i++)
								CheckMatrix(pMatrixArray + i);
						}

						// ValidateMatricesOfRpAtomic(info.pAtomic);
					}

				}
			}
			#endif

			CGenericLogStorage::SaveWorkBuffer();

			CPatch::PatchBYTE(0x40E170, 0xC3);	// NOP CStreaming::ProcessLoadingChannel

			bIsMemoryTestNow = false;
			/*

			tFileTypeBaseID loadedStart = FileIDlimit::GetBaseID(FILE_TYPE_LOADED_START);
			tFileTypeBaseID loadedEnd = FileIDlimit::GetLastIDforType(FILE_TYPE_LOADED_START);
			FileIDlimit_base* pManager = pLimitAdjuster->GetPointerToIDlimitManager();

			tFileTypeBaseID fileID;
			
			int countInLoadedList = 0;
			
			fileID = pManager->GetFileInfoNext(loadedStart);					

			while (fileID != loadedEnd)
			{
				countInLoadedList++;

				fileID = pManager->GetFileInfoNext(fileID);
			}

			int countInStreamingArray = 0;
			tFileTypeBaseID countOfIDs = FileIDlimit::GetCountOfAllFileIDs();

			for (fileID = 0; fileID <= countOfIDs; fileID++)
			{
				CStreamingInfo* pInfo = &FileIDlimit::CStreaming__ms_aInfoForModel[fileID];
				
				if (pInfo->uiLoadFlag == 1)
					countInStreamingArray++;
			}

			printf_MessageBox(
				"countInLoadedList: %d\n"
				"countInStreamingArray: %d\n"
				"difference: %d",
				countInLoadedList,
				countInStreamingArray,
				abs(countInLoadedList- countInStreamingArray)
				);
				*/
		}
	}

	// Print models loaded
	void CStreamingDebug::PrintModelsLoaded()
	{
		CGenericLogStorage::SaveFormattedTextLn(
			"File 1261 refCount: 0x%X",
			&g_fileIDlimits.CModelInfo__ms_modelInfoPtrs.gta_sa[1261]->m_wUsageCount
			);

		CGenericLogStorage::WriteLineSeparator();
		CGenericLogStorage::SaveTextLn("Printing models loaded");

		for (int fileID = 0; fileID != g_fileIDlimits.GetCountOfAllFileIDs(); fileID++)
		{
			eFileType type = g_fileIDlimits.GetFileIDtype(fileID);
			const char* sType = CFileTypeInfo::GetEnumNameByMember(type);
			int index = fileID - g_fileIDlimits.GetBaseID(type);

			if (g_fileIDlimits.CStreaming__ms_aInfoForModel.gta_sa[fileID].uiLoadFlag == 1)
			{
				CGenericLogStorage::SaveFormattedText(
					"File ID: %d File type: %s Index: %d",
					fileID, sType, index
					);

				if (type == FILE_TYPE_DFF)
				{
					CBaseModelInfo* pModelInfo = g_fileIDlimits.CModelInfo__ms_modelInfoPtrs.gta_sa[fileID];
					CGenericLogStorage::SaveFormattedText(
						" refCount: %d pointer to refCount: 0x%X",
						pModelInfo->m_wUsageCount,
						&pModelInfo->m_wUsageCount
						);
				}

				CGenericLogStorage::SaveTextLn("");
			}


		}

		CGenericLogStorage::SaveWorkBuffer();
	}

	
	/*
	NAKED void patch_5E77E3()
	{
		__asm
		{
			mov 

			push 0x5E7808;
			retn;
		}
	}
	*/

	RwMatrix *__cdecl RwMatrixMultiply(RwMatrix *out, RwMatrix *in1, RwMatrix *in2)
	{
		return
			((RwMatrix *(__cdecl*)(RwMatrix *out, RwMatrix *in1, RwMatrix *in2))
				0x7F18B0)
			(out, in1, in2);
	}

	void __cdecl multiplyShaderMatrix(
		RwMatrix* pOut,

		RwMatrix* pFirst,
		RwMatrix* pSecond,

		RwMatrix* pInversedWorldMatrix
		)
	{
		RwMatrix temp;

		CheckMatrix(pSecond, NULL);

		RwMatrixMultiply(&temp, pFirst, pSecond);
		RwMatrixMultiply(pOut, &temp, pInversedWorldMatrix);

		

		/*
		pOut->at.x = NAN;
		pOut->at.y = NAN;
		pOut->at.z = NAN;
		

		pOut->pos.x = NAN;
		pOut->pos.y = NAN;
		pOut->pos.z = NAN;

		
		pOut->right.x = NAN;
		pOut->right.y = NAN;
		pOut->right.z = NAN;
		
		pOut->top.x = NAN;
		pOut->top.y = NAN;
		pOut->top.z = NAN;
		*/
		/*
		pOut->pos.x = -0.296;
		pOut->pos.y = -0.037;
		pOut->pos.z = 0.013;

		pOut->at.x = 0.473;
		pOut->at.y = 0.048;
		pOut->at.z = -0.880;

		// 0.075 0.996 -0.043
		pOut->right.x = 0.075;
		pOut->right.y = 0.996;
		pOut->right.z = -0.043;
		*/


		/*
		CGenericLogStorage::SaveFormattedTextLn(
			"Top: %.3f %.3f %.3f",
			pOut->top.x,
			pOut->top.y,
			pOut->top.z
			);
			


		CGenericLogStorage::SaveWorkBuffer();
		*/
		// memset(pOut, 0xFF, sizeof(RwMatrix));
	}

	NAKED void patch_7C7AEE()
	{
		__asm
		{
			// ESP: -0xD4
			lea edx, [esp + 0xD4 - 0x40];	// inverseWorldMatrix
			push edx;

			// ESP: -0xD8
			lea     edx, [ebx + eax];
			push edx;

			// ESP: -0xDC
			push ebx;

			// ESP: -0xE0
			lea edx, [esp + 0xE0 - 0xC0];
			push edx;

			// ESP: -0xE4

			call multiplyShaderMatrix;

			sub esp, 8;

			// add esp, 4 * 4;

			push 0x7C7B14;
			retn;
		}
	}

	NAKED void patch_7C7A0A()
	{
		__asm
		{
			push eax;

			push 0x7C7A0A;
			push edi;
			call ValidateMatricesOfSkinPluginData;
			add esp, 8;

			pop eax;

			mov     edx, [edi + 8];
			test    ah, 40h;


			push 0x7C7A10;
			retn;
		}
	}
	
	NAKED void patch_7C7B90()
	{
		__asm
		{
			sub     esp, 20h;
			mov     edx, [esp + 20h + 8];

			push 0x7C7B90;
			push edx;
			call ValidateMatricesOfRxPipelineNodeParam;
			add esp, 8;





			mov     edx, [esp + 20h + 8];
			mov edx, [edx];

			push edx;
			call WorkaroundValidateMatricesOfRpAtomic;
			add esp, 4;





			mov     edx, [esp + 20h + 8];

			push 0x7C7B97;
			retn;
		}
	}

	static NAKED void patch_7491C0()
	{
		__asm
		{
			push esi;
			mov esi, [esp + 8];
			
			push 0x7491C0;
			push esi;
			call ValidateMatricesOfRpAtomic;
			add esp, 8;			

			push 0x7491C5;
			retn;
		}
	}

	NAKED void patch_749D14()
	{
		__asm
		{
			push esi;
			call AddLivingRpAtomic;
			add esp, 4;

			mov eax, esi;
			pop esi;
			pop ebx;
			retn;
		}
	}

	NAKED void patch_749E37()
	{
		__asm
		{
			push esi;
			call RemoveLivingRpAtomic;
			add esp, 4;

			mov     eax, 1;
			pop edi;
			pop esi;
			retn;
		}
	}

	NAKED void patch_74BD37()
	{
		__asm
		{
			push esi;
			call RemoveLivingRpAtomic;
			add esp, 4;

			mov eax, esi;
			pop edi;
			pop esi;
			retn;
		}
	}

	NAKED void patch_749717()
	{
		__asm
		{
			push esi;
			call RemoveLivingRpAtomic;
			add esp, 4;

			mov eax, esi;
			pop edi;
			pop esi;
			retn;
		}
	}

	NAKED void patch_4C507B()
	{
		__asm
		{
			push 0x4C507B;
			push ebx;
			call ValidateMatricesOfSkinPluginData;
			add esp, 8;

			push esi;
			mov[esp + 1Ch + 1Ch], ebx

			push 0x4C5080;
			retn;
		}
	}

	void __cdecl ValidateMatricesOfRpClump(RpClump* pClump, uint32_t additionalPtr = NULL)
	{
		RpHAnimHierarchy* pHierarchy = GetRpHanimHierarchyOfRpClump(pClump);

		if (pHierarchy)
			ValidateMatricesOfSkinPluginData(pHierarchy, additionalPtr);
	}

	NAKED void patch_40C80A()
	{
		__asm
		{
			call dword ptr[eax + 10h];

			mov lastIDofClump, esi;

			push esi;
			push edi;

			push 0x40C80F;
			retn;
		}
	}

	NAKED void patch_5373C7()
	{
		__asm
		{
			push 0x5373C7;
			push    edi;
			call ValidateMatricesOfRpClump;
			add esp, 8;

			mov     eax, [esi];
			push    edi;
			mov     ecx, esi;

			push 0x5373CC;
			retn;
		}
	}

	NAKED void patch_74B59C()
	{
		__asm
		{
			push ecx;
			push edi;
			mov eax, 0x807970;
			call eax;

			push eax;

			push 0x74B59C;
			push esi;
			call ValidateMatricesOfRpClump;
			add esp, 8;

			pop eax;

			push 0x74B5A3;
			retn;
		}
	}

	NAKED void patch_74BC88()
	{
		__asm
		{
			push 0x74BC88;
			push esi;
			call ValidateMatricesOfRpClump;
			add esp, 8;

			mov     eax, esi;
			pop     edi;
			pop     esi;
			pop     ebp;
			pop     ebx;
			add     esp, 44h;
			retn;
		}
	}

	NAKED void patch_74B661()
	{
		__asm
		{
			push 0x74B661;
			push esi;
			call ValidateMatricesOfRpClump;
			add esp, 8;

			mov eax, 0x7ED2D0;
			call eax;

			push 0x74B666;
			retn;
		}
	}

	void __cdecl RwMalloc_debug(const void* ptr, const void* returnAddress)
	{
		CGenericLogStorage::SaveFormattedTextLn("RwMalloc: 0x%X return: 0x%X", ptr, returnAddress);
		CGenericLogStorage::SaveWorkBuffer();
	}

	NAKED void patch_72F42A()
	{
		__asm
		{
			add esp, 4;

			push eax;

			mov ecx, [esp + 4];	// return address
			push ecx;

			push eax;

			call RwMalloc_debug;
			add esp, 8;
			
			pop eax;
			
			retn;
		}
	}


	void* __cdecl AllocateMatrices(size_t size)
	{
		return new char[size*3];

		// return matriceAllocator.Allocate(size);
	}

	void __cdecl DeallocateMatrices(void* ptr)
	{
		delete[] ptr;

		/// matriceAllocator.Deallocate(ptr);
	}


	NAKED void patch_7C4B3F()
	{
		__asm
		{
			call AllocateMatrices;
			push 0x7C4B45;
			retn;
		}
	}

	NAKED void patch_7C4C87()
	{
		__asm
		{
			call AllocateMatrices;
			push 0x7C4C87;
			retn;
		}
	}

	NAKED void patch_7C47C5()
	{
		__asm
		{
			// call DeallocateMatrices;

			push 0x7C47CB;
			retn;
		}
	}

	// Applies streaming debug
	void CStreamingDebug::ApplyStreamingDebug()
	{
		MH_CreateHook((void*)0x46A000, &Detoured_CTheScripts__Process, (void**)&fpCTheScripts__Process);
		MH_EnableHook((void*)0x46A000);

		MH_CreateHook((void*)0x4087E0, &Detoured_CStreaming__RequestModel, (void**)&fpCStreaming__RequestModel);
		MH_EnableHook((void*)0x4087E0);

		// CPatch::RedirectFunction(0x74B420, &RpClumpStreamRead_debug2);

		CPatch::RedirectCode(0x53C674, &PrintModelsLoaded);
		
		{
			CPatch::EnterNewLevel();
			CPatch::GetPointerToSettings()->bPatchForbiddenCheck = false;

			/*
			int newLimitSmall = 16399*4;
			int newLimitBig = 262422*4;

			CPatch::PatchDWORD(0x7C6931 + 1, newLimitBig);
			CPatch::PatchDWORD(0x7C694C + 1, newLimitBig);
			CPatch::PatchDWORD(0x7C6951 + 1, newLimitSmall);
			CPatch::PatchDWORD(0x7C6963 + 1, newLimitSmall / 4);
			CPatch::NOPinstructions(0x7C6972, 3);
			*/

			CPatch::RedirectCode(0x7C7AEE, &patch_7C7AEE);
			
			
			CPatch::RedirectCode(0x7C7A0A, &patch_7C7A0A);

			CPatch::RedirectCode(0x7C7B90, &patch_7C7B90);
			// CPatch::RedirectCode(0x7491C0, &patch_7491C0);
			


			// Keep track of living RpAtomic objects
			/*
			{
				CPatch::RedirectCode(0x749D14, &patch_749D14);
				CPatch::RedirectCode(0x749E37, &patch_749E37);
				CPatch::RedirectCode(0x74BD37, &patch_74BD37);
				CPatch::RedirectCode(0x749717, &patch_749717);
			}
			*/


			CPatch::PutOnAddressRelative4byteAddressToAddress(
				0x5B2BEB + 1,
				(uintptr_t)&delete_8213AE_debug
				);

			
			// CPatch::RedirectCode(0x7C4D21, &patch_7C4D21);

			// CPatch::RedirectCode(0x4C507B, &patch_4C507B);
			CPatch::RedirectCode(0x40C80A, &patch_40C80A);
			// CPatch::RedirectCode(0x5373C7, &patch_5373C7);
			CPatch::RedirectCode(0x74B59C, &patch_74B59C);
			CPatch::RedirectCode(0x74BC88, &patch_74BC88);
			CPatch::RedirectCode(0x74B661, &patch_74B661);
			

			// CPatch::RedirectCode(0x72F42A, &patch_72F42A);

			// RpHAnimHierarchy pool
			#if FALSE
			{
				CPatch::RedirectCode(0x7C4B3F, &patch_7C4B3F);
				CPatch::RedirectCode(0x7C4C87, &patch_7C4C87);
				CPatch::RedirectCode(0x7C47C5, &patch_7C47C5);
			}
			#endif
			
			CPatch::LeaveThisLevel();		
		}

		CGenericLogStorage::SaveTextLn("Streaming debugging is enabled");
		CGenericLogStorage::WriteLineSeparator();
	}
}

#endif
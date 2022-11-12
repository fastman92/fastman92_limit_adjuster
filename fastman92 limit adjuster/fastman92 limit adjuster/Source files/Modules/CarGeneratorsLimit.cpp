/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CarGeneratorsLimit.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/CGenericGameStorage.h"

#include "FileIDlimit.h"
#include "MapLimits.h"
#include "SaveOfVariableLength.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

using namespace Game;

CarGeneratorLimit g_carGeneratorLimits;

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_CCarGenerator__DoInternalProcessing_6F3733()
	{
		//CTheCarGenerators::GetCarGeneratorIDfromPointer
		__asm
		{
			push eax;	// pCarGenerator
			call CTheCarGenerators::GetCarGeneratorIDfromPointer;
			add esp, 4;

			lea ecx, [esp + 24h];	// [esp+8Ch+a4.z]
			push ecx;

			push eax;	// car generator ID

			// Go back
			mov eax, 0x6F3741;
			jmp eax;
		}
	}

	void NAKED patch_CCarGenerator__DoInternalProcessing_6F352E()
	{	
		__asm
		{
			mov     ax, [edi];		// get model ID from car generator

			cmp		ax, 0xFFFF;			// is random ID?
			je		ProcessRandomID;

			mov ecx, 0x6F35F9;		// @processPositiveID
			jmp ecx;

		ProcessRandomID:
			mov     ax, [edi + CCarGenerator_extended::lastRandomizedID];

			cmp		ax, 0xFFFF;			// is undefined ID?
			je ProcessRandomUndefinedID;

			movzx eax, ax;

			mov ecx, 0x6F3543;	//  lea     ecx, [eax+eax*4]
			jmp ecx;

		ProcessRandomUndefinedID:
			mov ecx, 0x6F355F;	// @ProcessNegativeNotSetID
			jmp ecx;
		}
	}

	void NAKED patch_CCarGenerator__DoInternalProcessing_6F35C4()
	{
		__asm
		{
			mov     edx, ebp;

			/////
			mov[edi + CCarGenerator_extended::lastRandomizedID], dx;

			// go back
			mov eax, 0x6F35CB;
			jmp eax;

		}
	}

	NAKED void patch_CCarGenerator__DoInternalProcessing__6F3696()
	{
		__asm
		{
			mov		eax, [edi + CCarGenerator_extended::exPos + CVector::x];
			mov		ecx, [edi + CCarGenerator_extended::exPos + CVector::y];

			mov		[esp + 0x8C - 0x5C], eax;		// a1.x
			mov		[esp + 0x8C - 0x5C + 4], ecx;	// a1.y

			fld[edi + CCarGenerator_extended::exPos + CVector::z];	// load Z

			// go back
			mov eax, 0x6F36D4;
			jmp eax;		
		}
	}

	NAKED void patch_CCarGenerator__DoInternalProcessing___6F3A74()
	{
		__asm
		{
			fld[edi + CCarGenerator_extended::exPos + CVector::z];
			fst		[esp + 8Ch - 0x74];

			// go back
			mov		eax, 0x6F3A8A;
			jmp		eax;
		}
	}

	void NAKED patch_CCarGenerator__DoInternalProcessing___6F3A97()
	{
		__asm
		{
			mov		eax, [edi + CCarGenerator_extended::exPos + CVector::x];
			mov		edx, [edi + CCarGenerator_extended::exPos + CVector::y];
			sub		esp, 8;
			mov		[esp + 0], eax;
			mov		[esp + 4], edx;

			mov		eax, 0x6F3AC5;
			jmp		eax;
		}
	}

	void NAKED patch_CCarGenerator__DoInternalProcessing___6F3AFC()
	{
		__asm
		{
			mov		eax, [edi + CCarGenerator_extended::exPos + CVector::x];
			mov		ecx, [edi + CCarGenerator_extended::exPos + CVector::y];

			sub     esp, 0Ch;
			fstp[esp + 8];	//angle

			mov[esp + 0], eax;	// pos x
			mov[esp + 4], ecx;	// pos y

			// go back
			mov ecx, esi;

			mov eax, 0x6F3B30;
			jmp eax;
		}
	}

	void NAKED patch_CCarGenerator__Setup__6F2E50()
	{
		__asm
		{
			push esi;
			mov     esi, ecx;

			// go back
			mov eax, 0x6F2E88;
			jmp eax;
		}
	}

	void NAKED patch_CCarGenerator__Setup__6F2F1E()
	{	
		__asm
		{
			mov     ax, [esp + 4 + 0x34];	// iplFile
			inc     edx;
			mov[esi + CCarGenerator_extended::time], edx;
			mov[esi + CCarGenerator_extended::enabled], 0;
			mov[esi + CCarGenerator_extended::exIplFile], ax;
			mov[esi + CCarGenerator_extended::allocated], 1;

			mov word ptr[esi + CCarGenerator_extended::lastRandomizedID], 0xFFFF;

			// Position
			mov	eax, [esp + 4 + 4];	// X
			mov[esi + CCarGenerator_extended::exPos + CVector::x], eax;

			mov	eax, [esp + 4 + 8];	// Y
			mov[esi + CCarGenerator_extended::exPos + CVector::y], eax;

			mov	eax, [esp + 4 + 0xC];	// X
			mov[esi + CCarGenerator_extended::exPos + CVector::z], eax;

			pop esi;
			retn 38h;
		}
	}

	void NAKED patch_CCarGenerator__CheckIfWithinRangeOfAnyPlayers_6F2FE8()
	{
		__asm
		{
			cmp		ax, 0xFFFF;
			je ModelIsRandom;

			// ModelIsNotRandom:
			movzx   edx, ax;

			// go to code (mov     eax, _ZN10CModelInfo16ms_modelInfoPtrsE[edx*4])
			push 0x6F2FF1;
			retn;

		ModelIsRandom:
			// go to code (fld     _camera.field_F4)
			push 0x6F30B5;
			retn;
		}
	}

	void NAKED patch_CCarGenerator__CheckIfWithinRangeOfAnyPlayers_6F2F54()
	{
		__asm
		{
			add		esp, 4;
			xor		bl, bl;

			// esp: -0x2C

			//// pos X
			mov		ecx, [esi + CCarGenerator_extended::exPos + CVector::x];
			mov		[esp + 0x2C - 0x18], ecx;	// carGenPosX

			fld[eax + CVector::x];
			fsub	[esp + 0x2C - 0x18];	// carGenPosX
			fstp	[esp + 0x2C - 0x1C];	// diffX

			//// pos Y
			mov		ecx, [esi + CCarGenerator_extended::exPos + CVector::y];
			mov		[esp + 0x2C - 0x14], ecx;	// carGenPosY

			fld		[eax + CVector::y];
			fsub	[esp + 0x2C - 0x14];	// carGenPosY
			fstp	[esp + 0x2C - 0x20];	// diffY
	
		
			// pos Z
			mov		ecx, [esi + CCarGenerator_extended::exPos + CVector::z];
			mov		[esp + 0x2C - 0x10], ecx;	// carGenPosZ


			// go back
			mov ecx, 0x6F2FB0;
			jmp ecx;
		}
	}


	NAKED void patch_CCarGenerator__CheckIfWithinRangeOfAnyPlayers_6F304A()
	{
		__asm
		{
			mov		edx, [esi + CCarGenerator_extended::exPos + CVector::x];
			mov		eax, [esi + CCarGenerator_extended::exPos + CVector::y];
			mov		ecx, [esi + CCarGenerator_extended::exPos + CVector::z];

			push	0;
			sub		esp, 0xC;

			mov[esp + CVector::x], edx;
			mov[esp + CVector::y], eax;
			mov[esp + CVector::z], ecx;

			// go back
			mov eax, 0x6F30A7;
			jmp eax;
		}
	}

	NAKED void patch_CCarGenerator__CheckIfWithinRangeOfAnyPlayers_6F3101()
	{
		__asm
		{
			fld	[esi + CCarGenerator_extended::exPos + CVector::z];

			// go back
			mov ecx, 0x6F3109;
			jmp ecx;
		}
	}

	NAKED void patch_CCarGenerator__CheckForBlockage_6F330E()
	{
		__asm
		{
			mov		eax, [ebp + CCarGenerator_extended::exPos + CVector::x];
			mov		ecx, [ebp + CCarGenerator_extended::exPos + CVector::y];
			mov		edx, [ebp + CCarGenerator_extended::exPos + CVector::z];

			mov[esp + 0x48 - 0x2C + CVector::x], eax;
			mov[esp + 0x48 - 0x2C + CVector::y], ecx;
			mov[esp + 0x48 - 0x2C + CVector::z], edx;

			push    0;		// a11
			push    0;		// a10
			push    1;		// a9
			push	1;		// a8
			push	0;		// a7

			lea     eax, [esp + 5Ch - 0x20];
			push	eax;	// a6

			mov edx, [esp + 0x60 - 0x38];	// radius
		
			push	8;		// a5

			lea ecx, [esp + 0x64 - 0x38];	// &radius

			push    ecx;	// a4

			push    1;		// a3

			push	edx;	// a2

			lea		eax, [esp + 0x70 - 0x2C];
			push	eax;

			// go back
			mov eax, 0x6F3372;
			jmp eax;
		}
	}

	static const float flt_858C48 = 0.125;

	NAKED void patch_CCarGenerator__CheckForBlockage_6F33CB()
	{
		__asm
		{
			fld dword ptr[ebp + CCarGenerator_extended::exPos + CVector::z];

			// go back
			mov esi, 0x6F33DD;
			jmp esi;
		}
	}

	NAKED void patch_CCarGenerator__CheckForBlockage__6F3449()
	{
		__asm
		{
			fld[ebp + CCarGenerator_extended::exPos + CVector::z];

			// go back
			push 0x6F345B;
			retn;
		}
	}

	static __int32 magicIDforCarGenerators = -1;

	NAKED void patch_CTheCarGenerators__Save_5D38EB()
	{
		__asm
		{
			mov[esp + 0x8], edx;	// _countOfCarGenerators from -0x4

			// Count of car generators, magic ID
			// -0xC
			push 4;
			push offset magicIDforCarGenerators;
			call CGenericGameStorage::SaveDataToWorkBuffer;

			// Process counter
			// -0x14
			push 1;
			push ASM_ACCESS_LIMIT_VAR_32_BIT(g_carGeneratorLimits, CarGeneratorLimit, CTheCarGenerators__ProcessCounter);
			call CGenericGameStorage::SaveDataToWorkBuffer;

			// GenerateEvenIfPlayerIsCloseCounter
			// -0x1C
			push 1;
			push ASM_ACCESS_LIMIT_VAR_32_BIT(g_carGeneratorLimits, CarGeneratorLimit, CTheCarGenerators__GenerateEvenIfPlayerIsCloseCounter);
			call CGenericGameStorage::SaveDataToWorkBuffer;
		
			// Real count of car generators
			// -0x24
			lea eax, [esp + 0x20];	// _countOfCarGenerators from -0x4
			push 4;
			push eax;
			call CGenericGameStorage::SaveDataToWorkBuffer;

			add esp, 0x20;

			// go back
			mov eax, 0x5D3916;
			jmp eax;
		}
	}

	void __cdecl SaveLoadGeneratorsExtended()
	{
		__int32 countOfCarGeneratorsSaved = 0;

		CCarGenerator_extended* ptr
			= (CCarGenerator_extended*)g_carGeneratorLimits.CTheCarGenerators__CarGeneratorArray.ptr;

		int limit = g_carGeneratorLimits.iCarGenerators;

		for (uint16_t i = 0; i < limit; i++)
		{
			if (ptr->allocated && !ptr->exIplFile)
				countOfCarGeneratorsSaved++;

			ptr++;
		}

		// printf_MessageBox("Saving, count of saved generators: %d", countOfCarGeneratorsSaved);

		CGenericGameStorage::SaveDataToWorkBuffer(&magicIDforCarGenerators, 4u);	
		CGenericGameStorage::SaveDataToWorkBuffer(g_carGeneratorLimits.CTheCarGenerators__ProcessCounter, 1u);
		CGenericGameStorage::SaveDataToWorkBuffer(g_carGeneratorLimits.CTheCarGenerators__GenerateEvenIfPlayerIsCloseCounter, 1u);
		CGenericGameStorage::SaveDataToWorkBuffer(&countOfCarGeneratorsSaved, 4u);

		ptr = (CCarGenerator_extended*)g_carGeneratorLimits.CTheCarGenerators__CarGeneratorArray.ptr;

		for (uint16_t i = 0; i < limit; i++)
		{
			if (ptr->allocated && !ptr->exIplFile)
			{
				CGenericGameStorage::SaveDataToWorkBuffer(&i, 2);

				CGenericGameStorage::SaveDataToWorkBuffer(ptr, sizeof(CCarGenerator_extended));
			}

			ptr++;
		}
	}

	NAKED void patch_CTheCarGenerators__Save_5D38C3()
	{
		__asm
		{
			call SaveLoadGeneratorsExtended;
		
			// go back
			mov eax, 0x5D396F;
			jmp eax;
		}
	}

	void CheckModelID(uint16_t saveArrayIndex, uint16_t carGenIndex, uint16_t ID)
	{
		if (ID >= g_fileIDlimits.GetBaseID(FILE_TYPE_TXD))
			printf_MessageBox(
			"Car generator with save index %d and game index %d has model ID or randomized ID of %d and exceeds the DFF ID limit.",
			saveArrayIndex,
			carGenIndex,
			ID
			);
	}

	void CheckSignedID(uint16_t saveArrayIndex, uint16_t carGenIndex, uint16_t ID)
	{
		if (ID >= 32768)
		{
			printf_MessageBox(
				"Car generator with save index %d and game index %d has model ID or randomized ID of %d and exceeds the signed DFF range.",
				saveArrayIndex,
				carGenIndex,
				ID
				);
		}
	}

	void LoadCarGenerators()
	{
		CGenericGameStorage::LoadDataFromWorkBuffer(
			g_carGeneratorLimits.CTheCarGenerators__NumOfCarGenerators, 4u
		);

		CGenericGameStorage::LoadDataFromWorkBuffer(
			g_carGeneratorLimits.CTheCarGenerators__ProcessCounter, 1u
		);

		CGenericGameStorage::LoadDataFromWorkBuffer(
			g_carGeneratorLimits.CTheCarGenerators__GenerateEvenIfPlayerIsCloseCounter,
			1u);

		uint16_t saveArrayIndex = 0;
		uint16_t carGenIndex;

		if (*g_carGeneratorLimits.CTheCarGenerators__NumOfCarGenerators > 0)	// is signed format in savefile?
		{
			do
			{
				CGenericGameStorage::LoadDataFromWorkBuffer(&carGenIndex, 2u);

				if (carGenIndex >= g_carGeneratorLimits.iCarGenerators)
					continue;
			
				if (g_carGeneratorLimits.bIsCarGeneratorFormatExtended)
				{
					CCarGenerator_extended* ptr = ((CCarGenerator_extended*)(
						g_carGeneratorLimits.CTheCarGenerators__CarGeneratorArray.ptr))
						+ carGenIndex;

					CGenericGameStorage::LoadDataFromWorkBuffer(ptr, sizeof(CCarGenerator));

					/*
					if (ptr->iplFile)
						printf_MessageBox(
						"Car generator with save index %d and game index %d has IPL ID: %d !",
						saveArrayIndex,
						carGenIndex,
						ptr -> iplFile
						);
					*/
					
					if ((int16_t)ptr->modelID == -1)
					{
						// printf_MessageBox("random modelID %d", (int16_t)ptr->modelID);
						ptr->modelID = 0xFFFF;
						ptr->lastRandomizedID = 0xFFFF;
					}					
					else if(((int16_t) ptr->modelID) < 0)
					{
						//printf_MessageBox("lower than zero %d carGenIndex: %d", (int16_t)ptr->modelID, carGenIndex);

						ptr->lastRandomizedID = -(int16_t)ptr->modelID;
						ptr->modelID = 0xFFFF;

						CheckModelID(saveArrayIndex, carGenIndex, ptr->lastRandomizedID);
					}
					else
					{
						CheckModelID(saveArrayIndex, carGenIndex, ptr->modelID);

						ptr->lastRandomizedID = 0xFFFF;
					}

					ptr->exIplFile = ptr->iplFile;

					ptr->exPos.x = (float)ptr->pos.x / CTheCarGenerators::COORD_INT_MULTIPLIER;
					ptr->exPos.y = (float)ptr->pos.y / CTheCarGenerators::COORD_INT_MULTIPLIER;
					ptr->exPos.z = (float)ptr->pos.z / CTheCarGenerators::COORD_INT_MULTIPLIER;

					// printf_MessageBox("carGenIndex: %d coords: %f %f %f", carGenIndex, ptr->pos.x, ptr->pos.y, ptr->pos.z);


				}
				else
				{
					// When game model ID is signed.
					CCarGenerator* ptr = ((CCarGenerator*)(
						g_carGeneratorLimits.CTheCarGenerators__CarGeneratorArray.ptr)) + carGenIndex;

					CGenericGameStorage::LoadDataFromWorkBuffer(ptr, sizeof(CCarGenerator));

					if ((int16_t)ptr -> modelID >= 0)
						CheckModelID(saveArrayIndex, carGenIndex, ptr->modelID);
					else if ((int16_t)ptr->modelID != -1)
						CheckModelID(saveArrayIndex, carGenIndex, -(int16_t)ptr->modelID);					
				}
			

			} while (++saveArrayIndex < *g_carGeneratorLimits.CTheCarGenerators__NumOfCarGenerators);
		}
		else if (*g_carGeneratorLimits.CTheCarGenerators__NumOfCarGenerators == magicIDforCarGenerators)		// extended format?
		{
			CGenericGameStorage::LoadDataFromWorkBuffer(
				g_carGeneratorLimits.CTheCarGenerators__NumOfCarGenerators, 4u
			);

			// printf_MessageBox("extended format! number of car generators: %d", CTheCarGenerators::NumOfCarGenerators);

			if (*g_carGeneratorLimits.CTheCarGenerators__NumOfCarGenerators > 0)
			{
				do
				{
					CGenericGameStorage::LoadDataFromWorkBuffer(&carGenIndex, 2u);

					if (carGenIndex >= g_carGeneratorLimits.iCarGenerators)
						continue;

					if (g_carGeneratorLimits.bIsCarGeneratorFormatExtended)
					{
						CCarGenerator_extended* ptr = ((CCarGenerator_extended*)(
							g_carGeneratorLimits.CTheCarGenerators__CarGeneratorArray.ptr)) + carGenIndex;

						CGenericGameStorage::LoadDataFromWorkBuffer(ptr, sizeof(CCarGenerator_extended));

						// printf_MessageBox("model ID: %d\n", ptr->modelID);

						if (ptr->modelID != 0xFFFF)
							CheckModelID(saveArrayIndex, carGenIndex, ptr->modelID);
						else if (ptr->lastRandomizedID != 0xFFFF)
							CheckModelID(saveArrayIndex, carGenIndex, ptr->lastRandomizedID);
					}
					else
					{
						// When game model ID is signed.
						CCarGenerator* ptr = ((CCarGenerator*)(
							g_carGeneratorLimits.CTheCarGenerators__CarGeneratorArray.ptr)) + carGenIndex;

						CCarGenerator_extended tmp;

						CGenericGameStorage::LoadDataFromWorkBuffer(&tmp, sizeof(CCarGenerator_extended));

						memcpy(ptr, &tmp, sizeof(CCarGenerator));

						if (ptr->modelID == 0xFFFF)	// is random ID?
						{
							if (tmp.lastRandomizedID == 0xFFFF)
							{
								if (tmp.lastRandomizedID >= 32768)
									printf_MessageBox(
										"Car generator with save index %d and game index %d has randomized ID of %d and exceeds the int16_t ID range.",
										saveArrayIndex,
										carGenIndex,
										tmp.lastRandomizedID
									);


								ptr->modelID = -(int16_t)tmp.lastRandomizedID;
							}
							else
								ptr->modelID = (int16_t)-1;
						}
						else
						{
							if (ptr->modelID >= 32768)
								printf_MessageBox(
									"Car generator with save index %d and game index %d has model ID of %d and exceeds the int16_t ID range.",
									saveArrayIndex,
									carGenIndex,
									tmp.lastRandomizedID
								);
						}

						ptr->iplFile = (uint8_t)tmp.exIplFile;

						ptr->pos.x = (int16_t)(tmp.exPos.x * CTheCarGenerators::COORD_INT_MULTIPLIER);
						ptr->pos.y = (int16_t)(tmp.exPos.y * CTheCarGenerators::COORD_INT_MULTIPLIER);
						ptr->pos.z = (int16_t)(tmp.exPos.z * CTheCarGenerators::COORD_INT_MULTIPLIER);
					}

				} while (++saveArrayIndex < *g_carGeneratorLimits.CTheCarGenerators__NumOfCarGenerators);
			}
		}

		// printf_MessageBox("NumOfCarGenerators: %d", CTheCarGenerators::NumOfCarGenerators);
	}

	NAKED void patch_CTheCarGenerators__Load_5D39B8()
	{
		__asm
		{
			call LoadCarGenerators;

			// go back
			mov eax, 0x5D3A2E;
			jmp eax;
		}
	}

	// Returns car generator ID
	uint16_t CTheCarGenerators::GetCarGeneratorIDfromPointer(void* pCarGenerator)
	{
		return ((int)pCarGenerator - (int)g_carGeneratorLimits.CTheCarGenerators__CarGeneratorArray.ptr) / sizeof(CCarGenerator_extended);
	}

	// Removes car generators with specified IPL file ID
	void __cdecl CTheCarGenerators::RemoveCarGenerators(uint16_t iplFile)
	{
		int numberOfGenerators = *g_carGeneratorLimits.CTheCarGenerators__NumOfCarGenerators;

		CCarGenerator_extended* ptr = (CCarGenerator_extended*)
			g_carGeneratorLimits.CTheCarGenerators__CarGeneratorArray.ptr;

		for (int i = 0; i < g_carGeneratorLimits.iCarGenerators; i++)
		{
			if (ptr->exIplFile == iplFile)
			{
				ptr->allocated = false;
				ptr->exIplFile = false;
				numberOfGenerators--;
			}
			ptr++;
		}

		*g_carGeneratorLimits.CTheCarGenerators__NumOfCarGenerators = numberOfGenerators;
	}
}
#endif

// Checks if extended format is neccessary.
bool CarGeneratorLimit::IsFormatExtendedNeccessary()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		return g_fileIDlimits.GetBaseID(FILE_TYPE_TXD) >= 32768
			||
			g_fileIDlimits.GetFileIDcurrentLimit(FILE_TYPE_IPL) > 256
			|| g_mapLimits.IsWorldMapSizeIncreased();
	}
#endif
	
	return false;
}

// Patches number of process counter passes
// Function must be executed when limit of car generators isn't going to be patched anymore.
void CarGeneratorLimit::PatchNumberOfProcessCounterPasses(int8_t counterPasses)
{
	CPatch::EnterNewLevel();
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		if (CPatch::IsDebugModeActive())
			counterPasses = 4;

		// Counter passes
		CPatch::PatchUINT8(0x6F3F67 + 1, counterPasses);	// cmp     al, 4

		CPatch::PatchUINT32(0x6F3F9E + 2, CCarGenerator_size * counterPasses);	// add     esi, 80h
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of number of process counter passes for car generators to %d", counterPasses);
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

// Patches car generator limit
void CarGeneratorLimit::PatchCarGeneratorsLimit(int iCarGenerators, bool bUseExtendedFormat)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		CCarGenerator_size = sizeof(CCarGenerator);

		bIsCarGeneratorFormatExtended = bUseExtendedFormat;

		bool bShouldFileSaveBeOfVariadicLength = false;

		if (!CPatch::IsDebugModeActive())
		{
			if (bIsCarGeneratorFormatExtended)
			{
				CTheCarGenerators__CarGeneratorArray.ptr = new CCarGenerator_extended[iCarGenerators];
				CCarGenerator_size = sizeof(CCarGenerator_extended);

				memset(CTheCarGenerators__CarGeneratorArray.ptr, 0, iCarGenerators * CCarGenerator_size);
				CTheCarGenerators__CarGeneratorArray.bIsAllocated.Set(true);

				if (iCarGenerators * sizeof(CCarGenerator_extended) > 500 * sizeof(CCarGenerator))
					bShouldFileSaveBeOfVariadicLength = true;
			}
			else
				if (iCarGenerators > 500)
				{
					CTheCarGenerators__CarGeneratorArray.ptr = new CCarGenerator[iCarGenerators];
					memset(CTheCarGenerators__CarGeneratorArray.ptr, 0, iCarGenerators * sizeof(CCarGenerator));
					CTheCarGenerators__CarGeneratorArray.bIsAllocated.Set(true);
					bShouldFileSaveBeOfVariadicLength = true;
				}
		}
		else
		{
			iCarGenerators = 500;
			CTheCarGenerators__CarGeneratorArray.ptr = (CCarGenerator*)0xC27AD0;

			bIsCarGeneratorFormatExtended = false;
		}
	
		this->iCarGenerators = iCarGenerators;

		unsigned int pCarGeneratorArray = (unsigned int)CTheCarGenerators__CarGeneratorArray.ptr;

		// Patch pointers
		#if TRUE
		{		
			CPatch::PatchPointer(0x479D68 + 1, CTheCarGenerators__CarGeneratorArray.ptr);	// add     eax, offset _ZN17CTheCarGenerators17CarGeneratorArrayE; CTheCarGenerators::CarGeneratorArray
			CPatch::PatchPointer(0x47BA4B + 1, CTheCarGenerators__CarGeneratorArray.ptr);	// add     eax, offset _ZN17CTheCarGenerators17CarGeneratorArrayE; CTheCarGenerators::CarGeneratorArray
			CPatch::PatchPointer(0x47C247 + 2, CTheCarGenerators__CarGeneratorArray.ptr);	// add     ecx, offset _ZN17CTheCarGenerators17CarGeneratorArrayE; CTheCarGenerators::CarGeneratorArray
			CPatch::PatchPointer(0x537A04 + 2, CTheCarGenerators__CarGeneratorArray.ptr);	// add     ecx, offset _ZN17CTheCarGenerators17CarGeneratorArrayE; CTheCarGenerators::CarGeneratorArray
			CPatch::PatchPointer(0x5D38CE + 1, &((CCarGenerator*)(CTheCarGenerators__CarGeneratorArray.ptr))->allocated);	// mov     eax, offset _ZN17CTheCarGenerators17CarGeneratorArrayE.allocated
			CPatch::PatchPointer(0x5D3926 + 2, &((CCarGenerator*)CTheCarGenerators__CarGeneratorArray.ptr)->iplFile);	// mov     dl, ds:_ZN17CTheCarGenerators17CarGeneratorArrayE.iplFile[eax]
			CPatch::PatchPointer(0x5D3930 + 2, &((CCarGenerator*)CTheCarGenerators__CarGeneratorArray.ptr)->allocated);	// mov     dl, ds:_ZN17CTheCarGenerators17CarGeneratorArrayE.allocated[eax]
			CPatch::PatchPointer(0x5D394E + 2, CTheCarGenerators__CarGeneratorArray.ptr);	// add     edx, offset _ZN17CTheCarGenerators17CarGeneratorArrayE; CTheCarGenerators::CarGeneratorArray
			CPatch::PatchPointer(0x5D3A10 + 2, CTheCarGenerators__CarGeneratorArray.ptr);	// add     ecx, offset _ZN17CTheCarGenerators17CarGeneratorArrayE; CTheCarGenerators::CarGeneratorArray

			CPatch::PatchPointer(0x6F31C0 + 1, &((CCarGenerator*)CTheCarGenerators__CarGeneratorArray.ptr)->allocated);	// mov     eax, offset _ZN17CTheCarGenerators17CarGeneratorArrayE.allocated
			CPatch::PatchPointer(0x6F31CE + 1, &((CCarGenerator*)((int)CTheCarGenerators__CarGeneratorArray.ptr + iCarGenerators * CCarGenerator_size))->allocated);	// cmp     eax, (offset dword_C2B96C+1)
			CPatch::PatchPointer(0x6F3221 + 2, CTheCarGenerators__CarGeneratorArray.ptr);	// add     ecx, offset _ZN17CTheCarGenerators17CarGeneratorArrayE; CTheCarGenerators::CarGeneratorArray

			CPatch::PatchPointer(0x6F324A + 1, &((CCarGenerator*) CTheCarGenerators__CarGeneratorArray.ptr)->iplFile);	// mov     eax, offset _ZN17CTheCarGenerators17CarGeneratorArrayE.iplFile
			CPatch::PatchPointer(0x6F325F + 1, &((CCarGenerator*)((int)CTheCarGenerators__CarGeneratorArray.ptr + iCarGenerators * CCarGenerator_size))->iplFile);	// cmp     eax, offset dword_C2B96C

			CPatch::PatchPointer(0x6F32A1 + 1, &((CCarGenerator*) CTheCarGenerators__CarGeneratorArray.ptr)->allocated);	// mov     eax, offset _ZN17CTheCarGenerators17CarGeneratorArrayE.allocated
			CPatch::PatchPointer(0x6F32AB + 1, &((CCarGenerator*)((int)CTheCarGenerators__CarGeneratorArray.ptr + iCarGenerators * CCarGenerator_size))->allocated);	// cmp     eax, (offset dword_C2B96C+1)
			// CPatch::PatchPointer(0x6F3733 + 1, CTheCarGenerators::CarGeneratorArray.ptr);	// sub     eax, offset _ZN17CTheCarGenerators17CarGeneratorArrayE; CTheCarGenerators::CarGeneratorArray
			CPatch::PatchPointer(0x6F3F86 + 2, CTheCarGenerators__CarGeneratorArray.ptr);	// add     esi, offset _ZN17CTheCarGenerators17CarGeneratorArrayE; CTheCarGenerators::CarGeneratorArray
			CPatch::PatchPointer(0x6F3FA4 + 2, (CCarGenerator*)((int)CTheCarGenerators__CarGeneratorArray.ptr + iCarGenerators * CCarGenerator_size));	// cmp     esi, offset flt_C2B950
		}
		#endif

		// Patch count of car generators
		#if TRUE
		{
			CPatch::PatchUINT16(0x5D3A04 + 2, iCarGenerators);	// cmp     ax, 1F4h
		
			CPatch::PatchUINT32(0x5D38C5 + 1, iCarGenerators);	// mov     ecx, 500
			CPatch::PatchUINT16(0x5D3964 + 3, iCarGenerators);	// cmp     cx, 1F4h

			CPatch::PatchUINT32(0x6F3F7B + 2, iCarGenerators);	// cmp     esi, 500		
		}
		#endif

		// Make model ID unsigned
		if (bIsCarGeneratorFormatExtended)
		{
			// .text:00479D60     CTheCarGenerators__GetCarGenerator
			FixShlInstruction(0x479D65, "\x6b\xc0");	//  shl     eax, 5

			// _opcode_handler_25
			FixShlInstruction(0x47BA48, "\x6b\xc0");	//  shl     eax, 5

			// opcode_handler_03
			FixShlInstruction(0x47C244, "\x6b\xc9");	// shl     ecx, 5

			// 537990     _addIplCars
			FixShlInstruction(0x537A01, "\x6b\xc9");		// shl     ecx, 5

			// .text:005D38C0; CTheCarGenerators::Save(void)
			// .text:005D38C0     _ZN17CTheCarGenerators4SaveEv proc near
			CPatch::PatchUINT8(0x5D38E5 + 2, CCarGenerator_size);

			CPatch::RedirectCode(0x5D38EB, &patch_CTheCarGenerators__Save_5D38EB);
			CPatch::PatchUINT8(0x5D3913 + 2, 0x18 + 0x8);

			FixShlInstruction(0x5D3923, "\x6b\xc0");	// shl     eax, 5
			FixShlInstruction(0x5D394B, "\x6b\xd2");	// shl     edx, 5
			CPatch::PatchUINT8(0x5D3954 + 1, CCarGenerator_size);

			CPatch::RedirectCode(0x5D38C3, &patch_CTheCarGenerators__Save_5D38C3);

			CGenericLogStorage::SaveFormattedTextLn("Format of new savefiles will be different: patch for car generators with CCarGenerator_extended structure is applied!");

			// 6F31A0     _addParkedGenerator
			CPatch::PatchUINT8(0x6F31CA + 2, CCarGenerator_size);	// add     eax, 20h
			FixShlInstruction(0x6F321E, "\x6b\xc9");  // shl     ecx, 5

			// 6F3240     CTheCarGenerators::RemoveCarGenerators
			CPatch::RedirectFunction(0x6F3240, &CTheCarGenerators::RemoveCarGenerators);

			// CPatch::PatchUINT8(0x6F325C + 2, CCarGenerator_size);	// add     eax, 20h

			// .text:006F3270; CTheCarGenerators::Init(void)
			// .text:006F3270     _ZN17CTheCarGenerators4InitEv proc near
			CPatch::PatchUINT8(0x6F32A8 + 2, CCarGenerator_size);	// add     eax, 20h

			// .text:006F34D0; CCarGenerator::DoInternalProcessing(void)
			// .text:006F34D0     _ZN13CCarGenerator20DoInternalProcessingEv proc near
			{
				CPatch::RedirectCode(0x6F352E, &patch_CCarGenerator__DoInternalProcessing_6F352E);
				CPatch::NOPinstructions(0x6F3533, 0x10);

				CPatch::PatchUINT16(0x6F35F9, 0xB70F);		// CHANGE movsx eax,ax INTO movzx eax,ax

				CPatch::PatchUINT16(0x6F354E, 0xCA01);	// CHANGE sub edx,ecx INTO add edx,ecx

				CPatch::PatchUINT16(0x6F3555, 0x9090);	// CHANGE neg eax INTO nop

				///////////////////
				CPatch::NOPinstructions(0x6F35C4, 7);
				CPatch::RedirectCode(0x6F35C4, &patch_CCarGenerator__DoInternalProcessing_6F35C4);

				// Calculates ID of from pointer to car generator
				CPatch::RedirectCode(0x6F3733, &patch_CCarGenerator__DoInternalProcessing_6F3733);

				//////
				#if TRUE
				{
					CPatch::RedirectCode(0x6F3696, &patch_CCarGenerator__DoInternalProcessing__6F3696);
					CPatch::RedirectCode(0x6F3A74, &patch_CCarGenerator__DoInternalProcessing___6F3A74);
					CPatch::RedirectCode(0x6F3A97, &patch_CCarGenerator__DoInternalProcessing___6F3A97);
					CPatch::RedirectCode(0x6F3AFC, &patch_CCarGenerator__DoInternalProcessing___6F3AFC);
				}
				#endif
			}

			// .text:006F2E50; void __thiscall CCarGenerator::Setup(CCarGenerator *this, float x, float y, float z, float angle, int16_t modelId, int16_t color1, int16_t color2, char a9, char alarm, char doorLock, int16_t a12, int16_t a13, char a14, char a15)
			// .text:006F2E50     _ZN13CCarGenerator5SetupEffffisshhhtthh
			CPatch::RedirectFunction(0x6F2E50, patch_CCarGenerator__Setup__6F2E50);

			// CPatch::NOPinstructions(0x6F2E50, 4);
			CPatch::RedirectCode(0x6F2F1E, &patch_CCarGenerator__Setup__6F2F1E);
			// CPatch::RedirectCode(0x6F2E55, 0x6F2E88);
			CPatch::NOPinstructions(0x6F2E92, 4);

			// CCarGenerator::CheckIfWithinRangeOfAnyPlayers
			{
				CPatch::NOPinstructions(0x6F2FE8, 9);
				CPatch::RedirectCode(0x6F2FE8, &patch_CCarGenerator__CheckIfWithinRangeOfAnyPlayers_6F2FE8);	// ID check

				CPatch::RedirectCode(0x6F2F54, &patch_CCarGenerator__CheckIfWithinRangeOfAnyPlayers_6F2F54);			
				CPatch::RedirectCode(0x6F304A, &patch_CCarGenerator__CheckIfWithinRangeOfAnyPlayers_6F304A);
				CPatch::RedirectCode(0x6F3101, &patch_CCarGenerator__CheckIfWithinRangeOfAnyPlayers_6F3101);
				CPatch::NOPinstructions(0x6F310F, 10);
			}

			// .text:006F3F40; void __cdecl CTheCarGenerators::Process()
			// .text:006F3F40     _ZN17CTheCarGenerators7ProcessEv proc near
			FixShlInstruction(0x6F3F83, "\x6b\xf6");	// shl     esi, 5

			CPatch::PatchUINT32(0x6F3F9E + 2, CCarGenerator_size * 4);	// add     esi, 80h

			// .text:006F32E0; char __thiscall CCarGenerator::CheckForBlockage(CCarGenerator *this, int a2)
			// .text:006F32E0     _ZN13CCarGenerator16CheckForBlockageEi proc near
			#if TRUE
			{
				CPatch::RedirectCode(0x6F330E, &patch_CCarGenerator__CheckForBlockage_6F330E);
				CPatch::RedirectCode(0x6F33CB, &patch_CCarGenerator__CheckForBlockage_6F33CB);
				CPatch::RedirectCode(0x6F3449, &patch_CCarGenerator__CheckForBlockage__6F3449);
			}
			#endif
		}
	
		CPatch::LeaveThisLevel();
	
		if (bShouldFileSaveBeOfVariadicLength)
			g_SaveOfVariableLength.MakeSaveOfVariableLength();
	}
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CGenericLogStorage::SaveFormattedTextLn("Modified limit Car generators to: %d Is CCarGenerator_extended structure used: %d", iCarGenerators, bIsCarGeneratorFormatExtended);
	CGenericLogStorage::WriteLineSeparator();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void CTheCarGenerators__CreateCarGenerator_patch_6F31A9()
	{
		__asm
		{
			cmp		ecx, 10;
			jge goodID;

			or eax, -1;
			retn;

		goodID:
			// go back
			mov		eax, 0x6F31BD;
			jmp		eax;
		}
	}
}
#endif

// Accepts any ID for car generator
void CarGeneratorLimit::AcceptAnyIDforCarGenerator()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		CPatch::EnterNewLevelAndDisableDebugState();

		// CPatch::RedirectCode(0x6F31A4, 0x6F31BD);
		CPatch::RedirectCode(0x6F31A9, &CTheCarGenerators__CreateCarGenerator_patch_6F31A9);

		// fix HOODLUM function
		CPatch::PatchMemoryData(0x4185C0, "\xa1\xd0\x89\x96\x00", 5);

		CGenericLogStorage::SaveFormattedTextLn("Applied patch to make car generator accept any vehicle ID that meets a condition (ID == -1 || ID >= 10).");
		CGenericLogStorage::WriteLineSeparator();
		CPatch::LeaveThisLevel();
	}
#endif
}

// Patches a function that loads car generators from savefile.
void CarGeneratorLimit::PatchCarGeneratorSaveBlockLoadingFunction()
{
	if (!bIsSaveBlockLoadingFunctionPatched)
	{
		MAKE_VAR_GAME_VERSION();
		MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
		else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			using namespace Game_GTASA;
			CPatch::RedirectCode(0x5D39B8, &patch_CTheCarGenerators__Load_5D39B8);
			bIsSaveBlockLoadingFunctionPatched = true;
		}
#endif
	}
}

// Initialize
void CarGeneratorLimit::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		this->iCarGenerators = 500;
		this->bIsSaveBlockLoadingFunctionPatched = false;

		this->CCarGenerator_size = sizeof(CCarGenerator);
		this->bIsCarGeneratorFormatExtended = false;

		#ifdef IS_PLATFORM_WIN_X86
		// Number of car generators.
		CTheCarGenerators__NumOfCarGenerators = (int*)0xC279D4;

		// Process counter
		CTheCarGenerators__ProcessCounter = (uint8_t*)0xC279D1;

		// GenerateEvenIfPlayerIsCloseCounter
		CTheCarGenerators__GenerateEvenIfPlayerIsCloseCounter = (char*)0xC279D0;

		CTheCarGenerators__CarGeneratorArray.ptr = (CCarGenerator*)0xC27AD0;
		#endif
	}
}

// Shutdown
void CarGeneratorLimit::Shutdown()
{
	if (CTheCarGenerators__CarGeneratorArray.bIsAllocated.Get())
		delete[] CTheCarGenerators__CarGeneratorArray.ptr;
}

// Fixes shl size of car generator
void CarGeneratorLimit::FixShlInstruction(uint32_t dwAddress, const char* data)
{
	CPatch::PatchUINT16(dwAddress, *(uint16_t*)data);
	CPatch::PatchUINT8(dwAddress + 2, CCarGenerator_size);
}
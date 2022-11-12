/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

// IDEsectionLimits.cpp
#include "IDEsectionLimits.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/LimitAdjuster.h"

#include "../Core/FormattedOutput.h"
#include "../Core/MemoryAllocation.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

using namespace Game;

IDEsectionLimits g_IDEsectionLimits;

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
uintptr_t Address_CBaseModelInfo__CBaseModelInfo = 0;

uintptr_t Address_IDE_cars_store_construct_goBack = 0;
uint32_t IDE_cars_store_size = 0;

static TARGET_THUMB NAKED void patch_IDE_cars_store_construct_count()
{
	__asm volatile (
		".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R4, IDE_cars_store_size)
		"ADD R4, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_IDE_cars_store_construct_goBack)
	);
}

// Initialises store, calls constructors
static void InitialiseStoreFindConstructorByName(
	const char* constructorName,
	Game_GTA_old::CStore* pStore,
	unsigned int numberOfElements,
	unsigned int elementSize)
{
	uintptr_t constructorMethod = (uintptr_t)
		Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game,
		constructorName
		);

	// Call constructors
	for (unsigned int i = 0; i < numberOfElements; i++)
		g_memoryCall.Method<void>(constructorMethod, (char*)pStore->array + i * elementSize);
}

// Initialises store, calls constructors
static void InitialiseStoreCBaseModelInfo(
	Game_GTA_old::CStore* pStore,
	unsigned int numberOfElements,
	unsigned int elementSize,
	void (*func)(char* pObject)
)
{
	for (unsigned int i = 0; i < numberOfElements; i++)
	{
		char* pObject = (char*)pStore->array + i * elementSize;

		// CBaseModelInfo::CBaseModelInfo
		g_memoryCall.Method<void>(Address_CBaseModelInfo__CBaseModelInfo, pObject);

		// Custom constructing code
		func(pObject);
	}
}
#endif

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTAVC
{
	static NAKED void patch_CModelInfo__AddVehicleModel_55F5D0()
	{
		__asm
		{
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_IDEsectionLimits, IDEsectionLimits, IDE_cars_store);
			mov ecx, [ecx + Game_GTA_old::CStore::count];

			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_IDEsectionLimits, IDEsectionLimits, VehicleModelsLimit);

			cmp ecx, eax;

			push    ebx;
			mov     ebx, [esp + 4 + 4];

			jl      loc_55F5EC;

			push eax;

			ASM_JMP_STATIC_ADDRESS(0x55F5E0);

		loc_55F5EC:
			ASM_JMP_STATIC_ADDRESS(0x55F5EC);
		}
	}

	static NAKED void patch_VehicleModels_constructor_55FFB6()
	{
		__asm
		{
			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_IDEsectionLimits, IDEsectionLimits, VehicleModelsLimit);
			push eax;		// count

			push    174h; // sizeof(CVehicleModelInfo)

			ASM_JMP_STATIC_ADDRESS(0x55FFBD);
		}
	}

	static NAKED void patch_VehicleModels_destructor_560156()
	{
		__asm
		{
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_IDEsectionLimits, IDEsectionLimits, VehicleModelsLimit);
			push ecx;		// count

			push    174h; // sizeof(CVehicleModelInfo)

			ASM_JMP_STATIC_ADDRESS(0x56015D);
		}
	}
}
#endif

// IDE: cars(212)
void IDEsectionLimits::SetVehicleModels(unsigned int iVehicleModels)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iVehicleModels = this->VehicleModelsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
	{
		using namespace Game_GTA_old;
		using namespace Game_GTAVC;

		if (iVehicleModels > this->VehicleModelsLimit)
		{
			unsigned int structSize = sizeof(uint32_t) + iVehicleModels * 0x174;
			IDE_cars_store.gta_vc = (CStore*)new_in_app_space char[structSize];
			memset(IDE_cars_store.gta_vc, NULL, structSize);
			IDE_cars_store.bIsAllocated.Set(true);
		}

		// Patch references
		CPatch::PatchPointer(0x55F5D0 + 2, &IDE_cars_store.gta_vc->count);	// cmp     ds:dword_752A88, 6Eh	; sub_55F5D0
		CPatch::PatchPointer(0x55F5EC + 1, &IDE_cars_store.gta_vc->count);	// mov     eax, ds:dword_752A88	; sub_55F5D0
		CPatch::PatchPointer(0x55F5F1 + 2, &IDE_cars_store.gta_vc->count);	// inc     ds:dword_752A88	; sub_55F5D0
		CPatch::PatchPointer(0x55F5FD + 1, &IDE_cars_store.gta_vc->count);	// add     eax, offset dword_752A88	; sub_55F5D0
		CPatch::PatchPointer(0x55F917 + 2, &IDE_cars_store.gta_vc->count);	// cmp     ds:dword_752A88, 0	; sub_55F820
		CPatch::PatchPointer(0x55F920 + 1, &IDE_cars_store.gta_vc->count);	// mov     edi, offset dword_752A88	; sub_55F820
		CPatch::PatchPointer(0x55F939 + 2, &IDE_cars_store.gta_vc->count);	// cmp     esi, ds:dword_752A88	; sub_55F820
		CPatch::PatchPointer(0x55F9D6 + 2, &IDE_cars_store.gta_vc->count);	// mov     ds:dword_752A88, 0	; sub_55F820
		CPatch::PatchPointer(0x55FB60 + 2, &IDE_cars_store.gta_vc->count);	// mov     ds:dword_752A88, 0	; sub_55FA40
		CPatch::PatchPointer(0x55FFC7 + 1, &IDE_cars_store.gta_vc->array);	// push    offset byte_752A8C; object	; sub_55FEC0
		CPatch::PatchPointer(0x55FFD4 + 2, &IDE_cars_store.gta_vc->count);	// mov     ds:dword_752A88, 0	; sub_55FEC0
		CPatch::PatchPointer(0x55FFE8 + 1, &IDE_cars_store.gta_vc->count);	// push    offset dword_752A88; objects	; sub_55FEC0

		// Count
		CPatch::RedirectCode(0x55F5D0, &patch_CModelInfo__AddVehicleModel_55F5D0);
		CPatch::RedirectCode(0x55FFB6, &patch_VehicleModels_constructor_55FFB6);
		CPatch::RedirectCode(0x560156, &patch_VehicleModels_destructor_560156);
	}
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTA_old;

		if (iVehicleModels > this->VehicleModelsLimit)
		{
			unsigned int structSize = sizeof(uint32_t) + iVehicleModels * 0x308;
			IDE_cars_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_cars_store.gta_sa, NULL, structSize);
			IDE_cars_store.bIsAllocated.Set(true);
		}

		// Patch references

		// Data references to count of CStore (.data:00B1F650)
		CPatch::PatchPointer(0x4C64EC + 1, &IDE_cars_store.gta_sa->count);	// mov     eax, ds:dword_B1F650
		CPatch::PatchPointer(0x4C6507 + 1, &IDE_cars_store.gta_sa->count);	// mov     eax, ds:dword_B1F650
		CPatch::PatchPointer(0x4C6602 + 2, &IDE_cars_store.gta_sa->count);	// mov     ds:dword_B1F650, ebp
		CPatch::PatchPointer(0x4C6770 + 1, &IDE_cars_store.gta_sa->count);	// mov     eax, ds:dword_B1F650
		CPatch::PatchPointer(0x4C6785 + 1, &IDE_cars_store.gta_sa->count);	// mov     ds:dword_B1F650, eax
		CPatch::PatchPointer(0x4C6851 + 2, &IDE_cars_store.gta_sa->count);	// mov     ds:dword_B1F650, edi
		CPatch::PatchPointer(0x84BCD0 + 1, &IDE_cars_store.gta_sa->count);	// mov     ecx, offset dword_B1F650
		CPatch::PatchPointer(0x8562A0 + 1, &IDE_cars_store.gta_sa->count);	// mov     ecx, offset dword_B1F650

		// Data references to array of CStore (.data:00B1F654)
		CPatch::PatchPointer(0x4C64F7 + 1, &IDE_cars_store.gta_sa->array);	// mov     edi, offset unk_B1F654
		CPatch::PatchPointer(0x4C677E + 2, &IDE_cars_store.gta_sa->array);	// add     esi, offset unk_B1F654

		//// Count of objects ////

		// ModelCarsData__constructor
		CPatch::PatchUINT32(0x4C5F5B + 1, iVehicleModels);

		// ModelCarsData__destructor
		CPatch::PatchUINT32(0x4C6375 + 1, iVehicleModels);
	}
	#elif defined(IS_PLATFORM_WIN_X64)
	else if (gameVersion == GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14718_WIN_X64)
	{
		using namespace Game_GTA_old;

		unsigned int singleElementSize = 0x6C8;

		if (iVehicleModels > this->VehicleModelsLimit)
		{
			unsigned int structSize = sizeof(uint32_t) + iVehicleModels * singleElementSize;
			IDE_cars_store.gta_sa = (CStore*)new_in_app_space char[structSize];

			memset(IDE_cars_store.gta_sa, NULL, structSize);
			IDE_cars_store.bIsAllocated.Set(true);
		}

		// Patch references
		CPatch::PatchRelative32bitReference(g_mCalc.GetCurrentVAbyPreferedVA(0x1405D3D6D + 3), 0, &IDE_cars_store.gta_sa->count);	// mov     cs:dword_1454290A0, r8d
		CPatch::PatchRelative32bitReference(g_mCalc.GetCurrentVAbyPreferedVA(0x140FB16D2 + 3), 0, &IDE_cars_store.gta_sa->count);	// movsxd  rcx, cs:dword_1454290A0
		CPatch::PatchRelative32bitReference(g_mCalc.GetCurrentVAbyPreferedVA(0x140FB16F0 + 2), 0, &IDE_cars_store.gta_sa->count);	// mov     cs:dword_1454290A0, ecx
		CPatch::PatchRelative32bitReference(g_mCalc.GetCurrentVAbyPreferedVA(0x14108D94D + 2), 0, &IDE_cars_store.gta_sa->count);	// mov     cs:dword_1454290A0, eax
		CPatch::PatchRelative32bitReference(g_mCalc.GetCurrentVAbyPreferedVA(0x14108DCDB + 2), 0, &IDE_cars_store.gta_sa->count);	// cmp     cs:dword_1454290A0, ebx
		CPatch::PatchRelative32bitReference(g_mCalc.GetCurrentVAbyPreferedVA(0x14108DD04 + 2), 0, &IDE_cars_store.gta_sa->count);	// cmp     ebx, cs:dword_1454290A0
		CPatch::PatchRelative32bitReference(g_mCalc.GetCurrentVAbyPreferedVA(0x14108DE5D + 2), 0, &IDE_cars_store.gta_sa->count);	// mov     cs:dword_1454290A0, ebp
		CPatch::PatchRelative32bitReference(g_mCalc.GetCurrentVAbyPreferedVA(0x140FB16D9 + 3), 0, &IDE_cars_store.gta_sa->array);	// lea     rax, unk_1454290A8
		CPatch::PatchRelative32bitReference(g_mCalc.GetCurrentVAbyPreferedVA(0x14108DCE3 + 3), 0, &IDE_cars_store.gta_sa->array);	// lea     rdi, unk_1454290A8
		CPatch::PatchRelative32bitReference(g_mCalc.GetCurrentVAbyPreferedVA(0x1405D3CD3 + 3), 0, (char*)&IDE_cars_store.gta_sa->array + 0x54);	// lea     rax, unk_1454290FC
		CPatch::PatchRelative32bitReference(g_mCalc.GetCurrentVAbyPreferedVA(0x143D72009 + 3), 0, (char*)&IDE_cars_store.gta_sa->array + iVehicleModels * singleElementSize);	// lea     rbx, unk_145482E48

		//// Count of objects ////

		// ModelCarsData__constructor
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x1405D3CDA + 1), iVehicleModels);

		// ModelCarsData__destructor
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x143D72004 + 1), iVehicleModels);

	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if(gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTA_old;

		if (iVehicleModels > this->VehicleModelsLimit)
		{
			unsigned int elementSize = 0x3A8;
			IDE_cars_store_size = sizeof(uint32_t) + iVehicleModels * elementSize;
			IDE_cars_store.gta_sa = (CStore*)new_in_app_space char[IDE_cars_store_size];
			memset(IDE_cars_store.gta_sa, NULL, IDE_cars_store_size);
			IDE_cars_store.bIsAllocated.Set(true);

			InitialiseStoreFindConstructorByName("_ZN17CVehicleModelInfoC2Ev", IDE_cars_store.gta_sa, iVehicleModels, elementSize);
		}
		
		// Patch references
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A408C), (char*)&IDE_cars_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3F9C));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A4090), (char*)&IDE_cars_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3FB8));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x3859AC), (char*)&IDE_cars_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x3857A2));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CFC), (char*)&IDE_cars_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385B8C));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D00), (char*)&IDE_cars_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385B9A));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D04), (char*)&IDE_cars_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385B9E));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D3C), (char*)&IDE_cars_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385C8C));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x3860BC), (char*)&IDE_cars_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x38609C));
		
		// Alter constructor, which is not executed
		Address_IDE_cars_store_construct_goBack = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1A3F98));

		CPatch::RedirectCodeEx(
			INSTRUCTION_SET_THUMB,
			g_mCalc.GetCurrentVAbyPreferedVA(0x1A3F90),
			(void*)&patch_IDE_cars_store_construct_count
		);
	}
	#endif
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion) && IDE_cars_store.gta_iv)
	{
		using namespace Game_GTAIV;

		IDE_cars_store.gta_iv->nSize = iVehicleModels;

		if (iVehicleModels > this->VehicleModelsLimit)
		{
			this->vehicleFieldsOffsets.gta_iv = new_in_app_space CVehicleFieldInfo[iVehicleModels * this->numberOfFieldsPerVehicle];
			this->vehicleFieldsOffsets.bIsAllocated.Set(true);
		}

		MAKE_DEAD_IF();
		#ifdef IS_PLATFORM_WIN_X86
		else if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86)
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x83E927 + 1), vehicleFieldsOffsets.gta_iv);	// add     eax, offset vehicleFieldsOffsets	; sub_83E900
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x84435F + 1), vehicleFieldsOffsets.gta_iv);	// add     eax, offset vehicleFieldsOffsets	; sub_8441D0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBDBB53 + 2), vehicleFieldsOffsets.gta_iv);	// add     edi, offset vehicleFieldsOffsets	; sub_BDBAB0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCD6732 + 1), vehicleFieldsOffsets.gta_iv);	// mov     esi, offset vehicleFieldsOffsets	; sub_CD6730
		}
		else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9D67D7 + 1), vehicleFieldsOffsets.gta_iv);	// add     eax, offset vehicleFieldsOffsets	; sub_9D67B0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9DC16F + 1), vehicleFieldsOffsets.gta_iv);	// add     eax, offset vehicleFieldsOffsets	; readVehsOff
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xC8D5C3 + 2), vehicleFieldsOffsets.gta_iv);	// add     edi, offset vehicleFieldsOffsets	; sub_C8D520			
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD41492 + 1), vehicleFieldsOffsets.gta_iv);	// mov     esi, offset vehicleFieldsOffsets	; sub_D41490
		}		
		else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA79A37 + 1), vehicleFieldsOffsets.gta_iv);	// add     eax, offset vehicleFieldsOffsets	; sub_A79A10
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA7F3CF + 1), vehicleFieldsOffsets.gta_iv);	// add     eax, offset vehicleFieldsOffsets	; sub_A7F240
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xC98CA3 + 2), vehicleFieldsOffsets.gta_iv);	// add     edi, offset vehicleFieldsOffsets	; sub_C98C00			
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD62722 + 1), vehicleFieldsOffsets.gta_iv);	// mov     esi, offset vehicleFieldsOffsets	; sub_D62720
		}
		else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E6F17 + 1), vehicleFieldsOffsets.gta_iv);	// add     eax, offset vehicleFieldsOffsets	; sub_9E6EF0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EC89F + 1), vehicleFieldsOffsets.gta_iv);	// add     eax, offset vehicleFieldsOffsets	; sub_9EC710
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCB1643 + 2), vehicleFieldsOffsets.gta_iv);	// add     edi, offset vehicleFieldsOffsets	; sub_CB15A0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD3CD02 + 1), vehicleFieldsOffsets.gta_iv);	// mov     esi, offset vehicleFieldsOffsets	; sub_D3CD00
		}
		#endif
	}
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}
	
	this->VehicleModelsLimit = iVehicleModels;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IDE:cars section to %d", iVehicleModels);
	CGenericLogStorage::WriteLineSeparator();
}

// IDE: peds(278)
void IDEsectionLimits::SetPedModels(unsigned int iPedModels)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPedModels = this->PedModelsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
	{
		using namespace Game_GTA_old;
		using namespace Game_GTAVC;

		using namespace Game_GTA_old;

		if (iPedModels > this->PedModelsLimit)
		{
			unsigned int structSize = sizeof(uint32_t) + iPedModels * 0x48;
			IDE_peds_store.gta_vc = (CStore*)new_in_app_space char[structSize];
			memset(IDE_peds_store.gta_vc, NULL, structSize);
			IDE_peds_store.bIsAllocated.Set(true);
		}

		// Patch references
		CPatch::PatchPointer(0x55F580 + 2, &IDE_peds_store.gta_sa->count);	// cmp     ds:dword_75CA70, 82h	; sub_55F580
		CPatch::PatchPointer(0x55F5A2 + 1, &IDE_peds_store.gta_sa->count);	// mov     eax, ds:dword_75CA70	; sub_55F580
		CPatch::PatchPointer(0x55F5AA + 1, &IDE_peds_store.gta_sa->count);	// add     eax, offset dword_75CA70	; sub_55F580
		CPatch::PatchPointer(0x55F5B2 + 2, &IDE_peds_store.gta_sa->count);	// inc     ds:dword_75CA70	; sub_55F580
		CPatch::PatchPointer(0x55F94F + 2, &IDE_peds_store.gta_sa->count);	// cmp     ds:dword_75CA70, 0	; sub_55F820
		CPatch::PatchPointer(0x55F958 + 1, &IDE_peds_store.gta_sa->count);	// mov     esi, offset dword_75CA70	; sub_55F820
		CPatch::PatchPointer(0x55F971 + 2, &IDE_peds_store.gta_sa->count);	// cmp     edi, ds:dword_75CA70	; sub_55F820
		CPatch::PatchPointer(0x55F9C2 + 2, &IDE_peds_store.gta_sa->count);	// mov     ds:dword_75CA70, 0	; sub_55F820
		CPatch::PatchPointer(0x55FB4B + 2, &IDE_peds_store.gta_sa->count);	// mov     ds:dword_75CA70, 0	; sub_55FA40
		CPatch::PatchPointer(0x560006 + 1, &IDE_peds_store.gta_sa->array);	// push    offset unk_75CA74	; sub_55FEC0
		CPatch::PatchPointer(0x560013 + 2, &IDE_peds_store.gta_sa->count);	// mov     ds:dword_75CA70, 0	; sub_55FEC0
		CPatch::PatchPointer(0x560027 + 1, &IDE_peds_store.gta_sa->count);	// push    offset dword_75CA70	; sub_55FEC0

		//// Count of objects ////

		// CModelInfo::AddPedModel
		CPatch::PatchUINT32(0x55F580 + 6, iPedModels);
		CPatch::PatchUINT32(0x55F591 + 1, iPedModels);

		// CPedsModels__constructor
		CPatch::PatchUINT32(0x55FFF5 + 1, iPedModels);

		// CModelPeds__destructor
		CPatch::PatchUINT32(0x5600C6 + 1, iPedModels);
	}
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTA_old;

		if (iPedModels > this->PedModelsLimit)
		{
			unsigned int structSize = sizeof(uint32_t) + iPedModels * 0x44;
			IDE_peds_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_peds_store.gta_sa, NULL, structSize);
			IDE_peds_store.bIsAllocated.Set(true);
		}

		// Patch references

		// Data references to count of CStore (.data:00B478F8)
		CPatch::PatchPointer(0x4C6517 + 1, &IDE_peds_store.gta_sa->count);	// mov     eax, ds:dword_B478F8
		CPatch::PatchPointer(0x4C652E + 1, &IDE_peds_store.gta_sa->count);	// mov     eax, ds:dword_B478F8
		CPatch::PatchPointer(0x4C6608 + 2, &IDE_peds_store.gta_sa->count);	// mov     ds:dword_B478F8, ebp
		CPatch::PatchPointer(0x4C67A0 + 1, &IDE_peds_store.gta_sa->count);	// mov     eax, ds:dword_B478F8
		CPatch::PatchPointer(0x4C67B2 + 1, &IDE_peds_store.gta_sa->count);	// mov     ds:dword_B478F8, eax
		CPatch::PatchPointer(0x4C6857 + 2, &IDE_peds_store.gta_sa->count);	// mov     ds:dword_B478F8, edi
		CPatch::PatchPointer(0x84BCF0 + 1, &IDE_peds_store.gta_sa->count);	// mov     ecx, offset dword_B478F8
		CPatch::PatchPointer(0x8562B0 + 1, &IDE_peds_store.gta_sa->count);	// mov     ecx, offset dword_B478F8

		// Data references to array of CStore (.data:00B478FC)
		CPatch::PatchPointer(0x4C6522 + 1, &IDE_peds_store.gta_sa->array);	// mov     edi, offset unk_B478FC
		CPatch::PatchPointer(0x4C67AB + 2, &IDE_peds_store.gta_sa->array);	// add     esi, offset unk_B478FC

		//// Count of objects ////
		// CPedsModels__constructor
		CPatch::PatchUINT32(0x4C67DB + 1, iPedModels);

		// CModelPeds__destructor
		CPatch::PatchUINT32(0x4C6395 + 1, iPedModels);
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTA_old;

		if (iPedModels > this->PedModelsLimit)
		{
			unsigned int elementSize = 0x5C;
			unsigned int structSize = sizeof(uint32_t) + iPedModels * elementSize;
			IDE_peds_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_peds_store.gta_sa, NULL, structSize);
			IDE_peds_store.bIsAllocated.Set(true);

			// Initialise
			InitialiseStoreCBaseModelInfo(IDE_peds_store.gta_sa, iPedModels, elementSize,
				[](char* pObject)
			{
				uintptr_t Address_vtable = g_mCalc.GetCurrentVAbyPreferedVA(0x667668);

				*(int32_t*)(pObject + 0x4C) = 0;
				*(uintptr_t*)(pObject) = Address_vtable;
			}
			);
		}				

		// Patch references
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A409C), (char*)&IDE_peds_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3FCC));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A40A4), (char*)&IDE_peds_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3FD0));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A40A8), (char*)&IDE_peds_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3FF6));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x3859B0), (char*)&IDE_peds_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x3857AA));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D08), (char*)&IDE_peds_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385BB6));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D0C), (char*)&IDE_peds_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385BC4));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D10), (char*)&IDE_peds_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385BC8));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D40), (char*)&IDE_peds_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385C92));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x3860F4), (char*)&IDE_peds_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x3860D2));
	}
	#endif
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion) && IDE_peds_store.gta_iv)
		IDE_peds_store.gta_iv->nSize = iPedModels;
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->PedModelsLimit = iPedModels;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IDE:peds section to %d", iPedModels);
	CGenericLogStorage::WriteLineSeparator();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED int ModelHierData__constructor()
	{

		__asm
		{
			push esi;

			push 0x4C5750;	// offset $CModelHier__destructor
			push 0x4C56F0;	// offset $CModelHier__constructor
			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_IDEsectionLimits, IDEsectionLimits, HierObjectsLimit);
			push eax;		// count
			mov esi, ecx;

			push 24h;		// size
			lea     eax, [esi + 4];
			push    eax;	// objects

			mov eax, 0x821D30;	// __vector_constructor
			call eax;

			mov     dword ptr[esi], 0;
			mov     eax, esi;

			pop esi;
			retn;
		}
	}

	NAKED void ModelHierData__destructor()
	{
		__asm
		{
			push 0x4C5750;		// offset $CModelHier__destructor

			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_IDEsectionLimits, IDEsectionLimits, HierObjectsLimit);
			push eax;			// count

			push 24h;			// size

			add     ecx, 4;
			push ecx;

			mov eax, 0x821E02;	// __vector_destructor
			call eax;
			retn;
		}
	}
}
#endif

// IDE: hier(92)
void IDEsectionLimits::SetHierObjects(unsigned int iHierObjects)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iHierObjects = this->HierObjectsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86	
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTA_old;
		using namespace Game_GTASA;

		if (iHierObjects > this->HierObjectsLimit)
		{
			unsigned int structSize = sizeof(uint32_t) + iHierObjects * 0x24;
			IDE_hier_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_hier_store.gta_sa, NULL, structSize);
			IDE_hier_store.bIsAllocated.Set(true);
		}

		// Patch references

		// Data references to count of CStore (.data:00B1E958)
		CPatch::PatchPointer(0x4C64C8 + 1, &IDE_hier_store.gta_sa->count);	// mov     eax, ds:dword_B1E958
		CPatch::PatchPointer(0x4C64DF + 1, &IDE_hier_store.gta_sa->count);	// mov     eax, ds:dword_B1E958
		CPatch::PatchPointer(0x4C65FC + 2, &IDE_hier_store.gta_sa->count);	// mov     ds:dword_B1E958, ebp
		CPatch::PatchPointer(0x4C6740 + 1, &IDE_hier_store.gta_sa->count);	// mov     eax, ds:dword_B1E958
		CPatch::PatchPointer(0x4C6751 + 1, &IDE_hier_store.gta_sa->count);	// mov     ds:dword_B1E958, eax
		CPatch::PatchPointer(0x4C684B + 2, &IDE_hier_store.gta_sa->count);	// mov     ds:dword_B1E958, edi
		CPatch::PatchPointer(0x84BCB0 + 1, &IDE_hier_store.gta_sa->count);	// mov     ecx, offset dword_B1E958
		CPatch::PatchPointer(0x856290 + 1, &IDE_hier_store.gta_sa->count);	// mov     ecx, offset dword_B1E958

		// Data references to array of CStore (.data:00B1E95C)
		CPatch::PatchPointer(0x4C64D3 + 1, &IDE_hier_store.gta_sa->array);	// mov     edi, offset unk_B1E95C
		CPatch::PatchPointer(0x4C674A + 3, &IDE_hier_store.gta_sa->array);	// lea     esi, unk_B1E95C[esi*4]

		//// Count of objects ////
		// ModelHierData__constructor
		CPatch::RedirectFunction(0x4C5EF0, &ModelHierData__constructor);

		// $ModelHierData__destructor
		CPatch::RedirectFunction(0x4C5900, &ModelHierData__destructor);
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTA_old;

		if (iHierObjects > this->HierObjectsLimit)
		{
			unsigned int elementSize = 0x3C;
			unsigned int structSize = sizeof(uint32_t) + iHierObjects * elementSize;
			IDE_hier_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_hier_store.gta_sa, NULL, structSize);
			IDE_hier_store.bIsAllocated.Set(true);

			// Initialise
			InitialiseStoreCBaseModelInfo(IDE_hier_store.gta_sa, iHierObjects, elementSize,
				[](char* pObject)
			{
				uintptr_t Address_vtable = g_mCalc.GetCurrentVAbyPreferedVA(0x667534);

				*(uintptr_t*)(pObject) = Address_vtable;
			});
		}

		// Patch references
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A4078), (char*)&IDE_hier_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3F66));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A4080), (char*)&IDE_hier_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3F86));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x3859A4), (char*)&IDE_hier_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x3857B2));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CF0), (char*)&IDE_hier_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385B62));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CF4), (char*)&IDE_hier_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385B70));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CF8), (char*)&IDE_hier_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385B74));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D34), (char*)&IDE_hier_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385C86));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x386084), (char*)&IDE_hier_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x386060));
	}
	#endif
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion) && IDE_hier_store.gta_iv)
		IDE_hier_store.gta_iv->nSize = iHierObjects;
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}
	
	this->HierObjectsLimit = iHierObjects;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IDE:hier section to %d", iHierObjects);
	CGenericLogStorage::WriteLineSeparator();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED int ModelWeapData__constructor()
	{
		__asm
		{
			push esi;

			push 0x4C5790;	// offset $CModelWeap__destructor
			push 0x4C5760;	// offset $CModelWeap__constructor
			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_IDEsectionLimits, IDEsectionLimits, WeaponModelsLimit);
			push eax;		// count
			mov esi, ecx;

			push 28h;		// size
			lea     eax, [esi + 4];
			push    eax;	// objects

			mov eax, 0x821D30;	// __vector_constructor
			call eax;

			mov     dword ptr[esi], 0;
			mov     eax, esi;

			pop esi;
			retn;
		}
	}

	NAKED void ModelWeapData__destructor()
	{
		__asm
		{
			push 0x4C5790;		// offset $CModelWeap__destructor

			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_IDEsectionLimits, IDEsectionLimits, WeaponModelsLimit);
			push eax;			// count

			push 28h;			// size

			add     ecx, 4;
			push ecx;

			mov eax, 0x821E02;	// __vector_destructor
			call eax;
			retn;
		}
	}
}
#endif

// IDE: weap(51)
void IDEsectionLimits::SetWeaponModels(unsigned int iWeaponModels)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iWeaponModels = this->WeaponModelsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86	
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTA_old;
		using namespace Game_GTASA;

		if (iWeaponModels > this->WeaponModelsLimit)
		{
			unsigned int structSize = sizeof(uint32_t) + iWeaponModels * 0x28;
			IDE_weap_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_weap_store.gta_sa, NULL, structSize);
			IDE_weap_store.bIsAllocated.Set(true);
		}

		// Patch references

		// Data references to count of CStore (.data:00B1E158)
		CPatch::PatchPointer(0x4C64A4 + 1, &IDE_weap_store.gta_sa->count);	// mov     eax, ds:dword_B1E158
		CPatch::PatchPointer(0x4C64BB + 1, &IDE_weap_store.gta_sa->count);	// mov     eax, ds:dword_B1E158
		CPatch::PatchPointer(0x4C65F6 + 2, &IDE_weap_store.gta_sa->count);	// mov     ds:dword_B1E158, ebp
		CPatch::PatchPointer(0x4C6710 + 1, &IDE_weap_store.gta_sa->count);	// mov     eax, ds:dword_B1E158
		CPatch::PatchPointer(0x4C6721 + 1, &IDE_weap_store.gta_sa->count);	// mov     ds:dword_B1E158, eax
		CPatch::PatchPointer(0x4C6845 + 2, &IDE_weap_store.gta_sa->count);	// mov     ds:dword_B1E158, edi
		CPatch::PatchPointer(0x84BC90 + 1, &IDE_weap_store.gta_sa->count);	// mov     ecx, offset dword_B1E158
		CPatch::PatchPointer(0x856280 + 1, &IDE_weap_store.gta_sa->count);	// mov     ecx, offset dword_B1E158

		// Data references to array of CStore (.data:00B1E15C)
		CPatch::PatchPointer(0x4C64AF + 1, &IDE_weap_store.gta_sa->array);	// mov     edi, offset unk_B1E15C
		CPatch::PatchPointer(0x4C671A + 3, &IDE_weap_store.gta_sa->array);	// lea     esi, unk_B1E15C[esi*8]

		//// Count of objects ////
		// ModelWeapData__constructor
		CPatch::RedirectFunction(0x4C5E90, &ModelWeapData__constructor);

		// $CWeapModels__destructor
		CPatch::RedirectFunction(0x4C58E0, &ModelWeapData__destructor);
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTA_old;

		if (iWeaponModels > this->WeaponModelsLimit)
		{
			unsigned int elementSize = 0x40;
			unsigned int structSize = sizeof(uint32_t) + iWeaponModels * elementSize;
			IDE_weap_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_weap_store.gta_sa, NULL, structSize);
			IDE_weap_store.bIsAllocated.Set(true);

			// Initialise
			InitialiseStoreCBaseModelInfo(IDE_weap_store.gta_sa, iWeaponModels, elementSize,
				[](char* pObject)
			{
				uintptr_t Address_vtable = g_mCalc.GetCurrentVAbyPreferedVA(0x667708);

				*(uintptr_t*)(pObject) = Address_vtable;
			}
			);
		}
		 
		// Patch references
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A4064), (char*)&IDE_weap_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3F2A));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A406C), (char*)&IDE_weap_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3F50));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x3859A0), (char*)&IDE_weap_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x3857AE));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CE4), (char*)&IDE_weap_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385B38));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CE8), (char*)&IDE_weap_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385B46));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CEC), (char*)&IDE_weap_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385B4A));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D30), (char*)&IDE_weap_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385C82));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x38604C), (char*)&IDE_weap_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x38602C));
	}
	#endif
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion) && IDE_weap_store.gta_iv)
		IDE_weap_store.gta_iv->nSize = iWeaponModels;
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->WeaponModelsLimit = iWeaponModels;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IDE:weap section to %d", iWeaponModels);
	CGenericLogStorage::WriteLineSeparator();
}

// IDE: objs:type1(14000)
void IDEsectionLimits::SetIDEobjsType1(unsigned int iObjectsType1)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iObjectsType1 = this->ObjectsType1Limit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTA_old;

		if (iObjectsType1 > this->ObjectsType1Limit)
		{
			unsigned int structSize = sizeof(uint32_t) + iObjectsType1 * 0x20;
			IDE_objsType1_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_objsType1_store.gta_sa, NULL, structSize);
			IDE_objsType1_store.bIsAllocated.Set(true);
		}

		// Patch references

		// Data references to count of CStore (.data:00AAE950)
		CPatch::PatchPointer(0x4C63E0 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     eax, ds:dword_AAE950
		CPatch::PatchPointer(0x4C63FD + 1, &IDE_objsType1_store.gta_sa->count);	// mov     eax, ds:dword_AAE950
		CPatch::PatchPointer(0x4C65D8 + 2, &IDE_objsType1_store.gta_sa->count);	// mov     ds:dword_AAE950, ebp
		CPatch::PatchPointer(0x4C6620 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     eax, ds:dword_AAE950
		CPatch::PatchPointer(0x4C6632 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     ds:dword_AAE950, eax
		CPatch::PatchPointer(0x4C6863 + 2, &IDE_objsType1_store.gta_sa->count);	// mov     ds:dword_AAE950, 1
		CPatch::PatchPointer(0x4C6899 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     eax, ds:dword_AAE950
		CPatch::PatchPointer(0x4C68B4 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     ds:dword_AAE950, eax
		CPatch::PatchPointer(0x4C68E7 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     eax, ds:dword_AAE950
		CPatch::PatchPointer(0x4C68F8 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     ds:dword_AAE950, eax
		CPatch::PatchPointer(0x4C6926 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     eax, ds:dword_AAE950
		CPatch::PatchPointer(0x4C6937 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     ds:dword_AAE950, eax
		CPatch::PatchPointer(0x4C6965 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     eax, ds:dword_AAE950
		CPatch::PatchPointer(0x4C6976 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     ds:dword_AAE950, eax
		CPatch::PatchPointer(0x4C69A4 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     eax, ds:dword_AAE950
		CPatch::PatchPointer(0x4C69B5 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     ds:dword_AAE950, eax
		CPatch::PatchPointer(0x4C69E3 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     eax, ds:dword_AAE950
		CPatch::PatchPointer(0x4C69F4 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     ds:dword_AAE950, eax
		CPatch::PatchPointer(0x4C6A22 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     eax, ds:dword_AAE950
		CPatch::PatchPointer(0x4C6A33 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     ds:dword_AAE950, eax
		CPatch::PatchPointer(0x84BBF0 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     ecx, offset dword_AAE950
		CPatch::PatchPointer(0x856230 + 1, &IDE_objsType1_store.gta_sa->count);	// mov     ecx, offset dword_AAE950

		// Data references to array of CStore (.data:00AAE954)
		CPatch::PatchPointer(0x4C63F1 + 1, &IDE_objsType1_store.gta_sa->array);	// mov     edi, offset dword_AAE954
		CPatch::PatchPointer(0x4C662B + 2, &IDE_objsType1_store.gta_sa->array);	// add     esi, offset dword_AAE954
		CPatch::PatchPointer(0x4C6821 + 1, &IDE_objsType1_store.gta_sa->array);	// mov     eax, ds:dword_AAE954
		CPatch::PatchPointer(0x4C6828 + 1, &IDE_objsType1_store.gta_sa->array);	// mov     ecx, offset dword_AAE954
		CPatch::PatchPointer(0x4C6876 + 1, &IDE_objsType1_store.gta_sa->array);	// mov     ecx, offset dword_AAE954
		CPatch::PatchPointer(0x4C687B + 6, &IDE_objsType1_store.gta_sa->array);	// mov     ds:_modelPtrs+5D8h, offset dword_AAE954; jumptable 014A8B4E case 3
		CPatch::PatchPointer(0x4C688F + 1, &IDE_objsType1_store.gta_sa->array);	// mov     ecx, offset dword_AAE954
		CPatch::PatchPointer(0x4C68A3 + 2, &IDE_objsType1_store.gta_sa->array);	// add     esi, offset dword_AAE954
		CPatch::PatchPointer(0x4C68F1 + 2, &IDE_objsType1_store.gta_sa->array);	// add     esi, offset dword_AAE954
		CPatch::PatchPointer(0x4C6930 + 2, &IDE_objsType1_store.gta_sa->array);	// add     esi, offset dword_AAE954
		CPatch::PatchPointer(0x4C696F + 2, &IDE_objsType1_store.gta_sa->array);	// add     esi, offset dword_AAE954
		CPatch::PatchPointer(0x4C69AE + 2, &IDE_objsType1_store.gta_sa->array);	// add     esi, offset dword_AAE954
		CPatch::PatchPointer(0x4C69ED + 2, &IDE_objsType1_store.gta_sa->array);	// add     esi, offset dword_AAE954
		CPatch::PatchPointer(0x4C6A2C + 2, &IDE_objsType1_store.gta_sa->array);	// add     esi, offset dword_AAE954

		//// Count of objects ////
		// ModelObjsData__constructor
		CPatch::PatchUINT32(0x4C5CBB + 1, iObjectsType1);

		// $ModelObjsData__destructor
		CPatch::PatchUINT32(0x4C5845 + 1, iObjectsType1);
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTA_old;

		if (iObjectsType1 > this->PedModelsLimit)
		{
			unsigned int elementSize = 56;
			unsigned int structSize = sizeof(uint32_t) + iObjectsType1 * elementSize;
			IDE_objsType1_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_objsType1_store.gta_sa, NULL, structSize);
			IDE_objsType1_store.bIsAllocated.Set(true);

			// Initialise
			InitialiseStoreCBaseModelInfo(IDE_objsType1_store.gta_sa, iObjectsType1, elementSize,
				[](char* pObject)
			{
				uintptr_t Address_vtable = g_mCalc.GetCurrentVAbyPreferedVA(0x667454);

				*(uintptr_t*)(pObject) = Address_vtable;
			}
			);
		}

		// Patch references
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A400C), (char*)&IDE_objsType1_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3E26));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A4014), (char*)&IDE_objsType1_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3E46));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x3859B4), (char*)&IDE_objsType1_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x38579C));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385A18), (char*)&IDE_objsType1_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x3859F4));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CA8), (char*)&IDE_objsType1_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385A66));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CAC), (char*)&IDE_objsType1_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385A74));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CB0), (char*)&IDE_objsType1_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385A78));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D24), (char*)&IDE_objsType1_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385C6E));
	}
	#endif
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion) &&  IDE_objsType1_store.gta_iv)
		IDE_objsType1_store.gta_iv->nSize = iObjectsType1;
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ObjectsType1Limit = iObjectsType1;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IDE:objs:type1 section to %d", iObjectsType1);
	CGenericLogStorage::WriteLineSeparator();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED int ModelIDEobjsType2__constructor()
	{
		__asm
		{
			push esi;

			push 0x4C55D0;	// offset $CModelObjs2c__destructor
			push 0x4C55A0;	// offset $CModelWeap__constructor

			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_IDEsectionLimits, IDEsectionLimits, ObjectsType2Limit);
			push eax;		// count

			mov esi, ecx;

			push 24h;		// size
			lea     eax, [esi + 4];
			push    eax;	// objects

			mov eax, 0x821D30;	// __vector_constructor
			call eax;

			mov     dword ptr[esi], 0;
			mov     eax, esi;

			pop esi;
			retn;
		}
	}

	NAKED void ModelIDEobjsType2__destructor()
	{
		__asm
		{
			push 0x4C55D0;	// offset $CModelObjs2c__destructor

			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_IDEsectionLimits, IDEsectionLimits, ObjectsType2Limit);
			push eax;			// count

			push 24h;			// size

			add     ecx, 4;
			push ecx;

			mov eax, 0x821E02;	// __vector_destructor
			call eax;
			retn;
		}
	}
}
#endif

// IDE: objs:type2(70)
void IDEsectionLimits::SetIDEobjsType2(unsigned int iObjectsType2)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iObjectsType2 = this->ObjectsType2Limit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTA_old;
		using namespace Game_GTASA;

		if (iObjectsType2 > this->ObjectsType2Limit)
		{
			unsigned int structSize = sizeof(uint32_t) + iObjectsType2 * 0x24;
			IDE_objsType2_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_objsType2_store.gta_sa, NULL, structSize);
			IDE_objsType2_store.bIsAllocated.Set(true);
		}

		// Patch references

		// Data references to count of CStore (.data:00B1BF58)
		CPatch::PatchPointer(0x4C640A + 1, &IDE_objsType2_store.gta_sa->count);	// mov     eax, ds:dword_B1BF58
		CPatch::PatchPointer(0x4C6427 + 1, &IDE_objsType2_store.gta_sa->count);	// mov     eax, ds:dword_B1BF58
		CPatch::PatchPointer(0x4C65DE + 2, &IDE_objsType2_store.gta_sa->count);	// mov     ds:dword_B1BF58, ebp
		CPatch::PatchPointer(0x4C6650 + 1, &IDE_objsType2_store.gta_sa->count);	// mov     eax, ds:dword_B1BF58
		CPatch::PatchPointer(0x4C6661 + 1, &IDE_objsType2_store.gta_sa->count);	// mov     ds:dword_B1BF58, eax
		CPatch::PatchPointer(0x4C682D + 2, &IDE_objsType2_store.gta_sa->count);	// mov     ds:dword_B1BF58, edi
		CPatch::PatchPointer(0x84BC10 + 1, &IDE_objsType2_store.gta_sa->count);	// mov     ecx, offset dword_B1BF58
		CPatch::PatchPointer(0x856240 + 1, &IDE_objsType2_store.gta_sa->count);	// mov     ecx, offset dword_B1BF58

		// Data references to array of CStore (.data:00B1BF5C)
		CPatch::PatchPointer(0x4C6415 + 1, &IDE_objsType2_store.gta_sa->array);	// mov     edi, offset unk_B1BF5C
		CPatch::PatchPointer(0x4C665A + 3, &IDE_objsType2_store.gta_sa->array);	// lea     esi, unk_B1BF5C[esi*4]

		//// Count of objects ////
		// ModelWeapData__constructor
		CPatch::RedirectFunction(0x4C5D10, &ModelIDEobjsType2__constructor);

		// $CWeapModels__destructor
		CPatch::RedirectFunction(0x4C5860, &ModelIDEobjsType2__destructor);
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTA_old;

		if (iObjectsType2 > this->ObjectsType2Limit)
		{
			unsigned int elementSize = 60;
			unsigned int structSize = sizeof(uint32_t) + iObjectsType2 * elementSize;
			IDE_objsType2_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_objsType2_store.gta_sa, NULL, structSize);
			IDE_objsType2_store.bIsAllocated.Set(true);

			// Initialise
			InitialiseStoreCBaseModelInfo(IDE_objsType2_store.gta_sa, iObjectsType2, elementSize,
				[](char* pObject)
			{
				uintptr_t Address_vtable = g_mCalc.GetCurrentVAbyPreferedVA(0x6674A0);

				*(uintptr_t*)(pObject) = Address_vtable;
			});
		}

		// Patch references
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A4020), (char*)&IDE_objsType2_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3E5C));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A4028), (char*)&IDE_objsType2_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3E80));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x3859A8), (char*)&IDE_objsType2_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385798));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CB4), (char*)&IDE_objsType2_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385A90));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CB8), (char*)&IDE_objsType2_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385A9E));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CBC), (char*)&IDE_objsType2_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385AA2));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D20), (char*)&IDE_objsType2_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385C6C));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385F74), (char*)&IDE_objsType2_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385F50));
	}
	#endif
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion) && IDE_objsType2_store.gta_iv)
		IDE_objsType2_store.gta_iv->nSize = iObjectsType2;
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	ObjectsType2Limit = iObjectsType2;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IDE:objs:type2 section to %d", iObjectsType2);
	CGenericLogStorage::WriteLineSeparator();
}

// IDE: tobj(169)
void IDEsectionLimits::SetTimedObjects(unsigned int iTimedObjects)
{
	MAKE_VAR_GAME_VERSION();
	
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iTimedObjects = this->TimedObjectsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86	
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTA_old;

		if (iTimedObjects > this->TimedObjectsLimit)
		{
			unsigned int structSize = sizeof(uint32_t) + iTimedObjects * 0x24;
			IDE_tobj_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_tobj_store.gta_sa, NULL, structSize);
			IDE_tobj_store.bIsAllocated.Set(true);
		}

		// Patch references

		// Data references to count of CStore (.data:00B1C960)
		CPatch::PatchPointer(0x4C6458 + 1, &IDE_tobj_store.gta_sa->count);	// mov     eax, ds:dword_B1C960
		CPatch::PatchPointer(0x4C646F + 1, &IDE_tobj_store.gta_sa->count);	// mov     eax, ds:dword_B1C960
		CPatch::PatchPointer(0x4C65EA + 2, &IDE_tobj_store.gta_sa->count);	// mov     ds:dword_B1C960, ebp
		CPatch::PatchPointer(0x4C66B0 + 1, &IDE_tobj_store.gta_sa->count);	// mov     eax, ds:dword_B1C960
		CPatch::PatchPointer(0x4C66C1 + 1, &IDE_tobj_store.gta_sa->count);	// mov     ds:dword_B1C960, eax
		CPatch::PatchPointer(0x4C6839 + 2, &IDE_tobj_store.gta_sa->count);	// mov     ds:dword_B1C960, edi
		CPatch::PatchPointer(0x84BC50 + 1, &IDE_tobj_store.gta_sa->count);	// mov     ecx, offset dword_B1C960
		CPatch::PatchPointer(0x856260 + 1, &IDE_tobj_store.gta_sa->count);	// mov     ecx, offset dword_B1C960

		// Data references to array of CStore (.data:00B1C964)
		CPatch::PatchPointer(0x4C6463 + 1, &IDE_tobj_store.gta_sa->array);	// mov     edi, offset unk_B1C964
		CPatch::PatchPointer(0x4C66BA + 3, &IDE_tobj_store.gta_sa->array);	// lea     esi, unk_B1C964[esi*4]

		//// Count of objects ////
		// ModelTobjData__constructor
		CPatch::PatchUINT32(0x4C5DDB + 1, iTimedObjects);

		// $ModelTobjData__destructor
		CPatch::PatchUINT32(0x4C58A5 + 1, iTimedObjects);
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTA_old;

		if (iTimedObjects > this->TimedObjectsLimit)
		{
			unsigned elementSize = 0x3C;
			unsigned int structSize = sizeof(uint32_t) + iTimedObjects * elementSize;
			IDE_tobj_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_tobj_store.gta_sa, NULL, structSize);
			IDE_tobj_store.bIsAllocated.Set(true);

			// Initialise
			InitialiseStoreCBaseModelInfo(IDE_tobj_store.gta_sa, iTimedObjects, elementSize,
				[](char* pObject)
			{
				uintptr_t Address_vtable = g_mCalc.GetCurrentVAbyPreferedVA(0x6675D0);

				*(uintptr_t*)(pObject) = Address_vtable;

				*(int16_t*)(pObject + 0x3A) = -1;
			});	
		}

		// Patch references
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A4040), (char*)&IDE_tobj_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3EBE));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A4048), (char*)&IDE_tobj_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3EC2));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A404C), (char*)&IDE_tobj_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A3EEE));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385994), (char*)&IDE_tobj_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x38578C));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CCC), (char*)&IDE_tobj_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385AE4));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CD0), (char*)&IDE_tobj_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385AF2));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385CD4), (char*)&IDE_tobj_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385AF6));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D28), (char*)&IDE_tobj_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385C7A));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385FE4), (char*)&IDE_tobj_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385FC0));
	}
	#endif
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion) && IDE_tobj_store.gta_iv)
		IDE_tobj_store.gta_iv->nSize = iTimedObjects;
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	TimedObjectsLimit = iTimedObjects;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IDE:tobj section to %d", iTimedObjects);
	CGenericLogStorage::WriteLineSeparator();
}

// IDE: 2dfx(100)
void IDEsectionLimits::Set2DFX(unsigned int i2DFX)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		i2DFX = this->_2dfxLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86	
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTA_old;

		if (i2DFX > this->_2dfxLimit)
		{
			unsigned int structSize = sizeof(uint32_t) + i2DFX * 64;
			IDE_2dfx_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_2dfx_store.gta_sa, NULL, structSize);
			IDE_2dfx_store.bIsAllocated.Set(true);
		}
		
		// Data references to count of CStore (.data:00B1C960)
		#if TRUE
		{
			CPatch::PatchPointer(0x4C5A60 + 1, &IDE_2dfx_store.gta_sa->count);	// mov     eax, offset dword_B4C2D8	; sub_4C5A60
			CPatch::PatchPointer(0x4C63B1 + 2, &IDE_2dfx_store.gta_sa->count);	// mov     ds:dword_B4C2D8, 0	; 
			CPatch::PatchPointer(0x4C653B + 1, &IDE_2dfx_store.gta_sa->count);	// mov     eax, ds:dword_B4C2D8	; sub_4C63E0
			CPatch::PatchPointer(0x4C654A + 1, (char*)IDE_2dfx_store.gta_sa->array + 0x34 );	// mov     esi, offset unk_B4C310	; sub_4C63E0
			CPatch::PatchPointer(0x4C65C5 + 1, &IDE_2dfx_store.gta_sa->count);	// mov     eax, ds:dword_B4C2D8	; sub_4C63E0
			CPatch::PatchPointer(0x4C660E + 2, &IDE_2dfx_store.gta_sa->count);	// mov     ds:dword_B4C2D8, ebp	; sub_4C63E0
			CPatch::PatchPointer(0x4C685D + 2, &IDE_2dfx_store.gta_sa->count);	// mov     ds:dword_B4C2D8, edi	; _ZN10CModelInfo10InitialiseEv
		}

		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTA_old;

		if (i2DFX > this->_2dfxLimit)
		{
			unsigned int structSize = sizeof(uint32_t) + i2DFX * 64;
			IDE_2dfx_store.gta_sa = (CStore*)new_in_app_space char[structSize];
			memset(IDE_2dfx_store.gta_sa, NULL, structSize);
			IDE_2dfx_store.bIsAllocated.Set(true);
		}

		// Patch references
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x1A40B4), (char*)&IDE_2dfx_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x1A4004));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x3859B8), (char*)&IDE_2dfx_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x3857B8));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385A50), (char*)&IDE_2dfx_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385A38));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D14), (char*)&IDE_2dfx_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385BE0));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D18), (char*)&IDE_2dfx_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385BF4));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D1C), (char*)&IDE_2dfx_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385BFA));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x385D44), (char*)&IDE_2dfx_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x385C98));
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x386104), (char*)&IDE_2dfx_store.gta_sa->count - g_mCalc.GetCurrentVAbyPreferedVA(0x386102));
	}
	#endif
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion) && IDE_2dfx_store.gta_iv)
		IDE_2dfx_store.gta_iv->nSize = i2DFX;
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	_2dfxLimit = i2DFX;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of IDE:2DFX section to %d", i2DFX);
	CGenericLogStorage::WriteLineSeparator();
}

// Initialize
void IDEsectionLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();	

	if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
	{
		using namespace Game_GTA_old;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			// Array definitions
			#ifdef IS_PLATFORM_WIN_X86
			this->IDE_cars_store.gta_vc = (CStore*)g_mCalc.GetCurrentVAbyPreferedVA(0x752A88);
			this->IDE_peds_store.gta_vc = (CStore*)g_mCalc.GetCurrentVAbyPreferedVA(0x75CA70);
			#endif
		}

		// Count definitions
		this->VehicleModelsLimit = 110;
		this->PedModelsLimit = 130;
	}
	else if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		using namespace Game_GTA_old;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			
			// Array definitions
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				this->IDE_cars_store.gta_sa = (CStore*)0xB1F650;
				this->IDE_peds_store.gta_sa = (CStore*)0xB478F8;
				this->IDE_hier_store.gta_sa = (CStore*)0xB1E958;
				this->IDE_weap_store.gta_sa = (CStore*)0xB1E158;
				this->IDE_objsType1_store.gta_sa = (CStore*)0xAAE950;
				this->IDE_objsType2_store.gta_sa = (CStore*)0xB1BF58;
				this->IDE_tobj_store.gta_sa = (CStore*)0xB1C960;
				this->IDE_2dfx_store.gta_sa = (CStore*)0xB4C2D8;
			}
			#elif defined(IS_PLATFORM_WIN_X64)
			if(gameVersion == GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14718_WIN_X64)
				this->IDE_cars_store.gta_sa = (CStore*)g_mCalc.GetCurrentVAbyPreferedVA(0x1454290A0);
			#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
			Address_CBaseModelInfo__CBaseModelInfo = (uintptr_t)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN14CBaseModelInfoC2Ev"
			);

			if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				this->IDE_cars_store.gta_sa = (CStore*)g_mCalc.GetCurrentVAbyPreferedVA(0x8E58A4);
				this->IDE_peds_store.gta_sa = (CStore*)g_mCalc.GetCurrentVAbyPreferedVA(0x915FC8);
				this->IDE_hier_store.gta_sa = (CStore*)g_mCalc.GetCurrentVAbyPreferedVA(0x8E4310);
				this->IDE_weap_store.gta_sa = (CStore*)g_mCalc.GetCurrentVAbyPreferedVA(0x8E364C);
				this->IDE_objsType1_store.gta_sa = (CStore*)g_mCalc.GetCurrentVAbyPreferedVA(0x820738);
				this->IDE_objsType2_store.gta_sa = (CStore*)g_mCalc.GetCurrentVAbyPreferedVA(0x8DFDBC);
				this->IDE_tobj_store.gta_sa = (CStore*)g_mCalc.GetCurrentVAbyPreferedVA(0x8E0E68);
				this->IDE_2dfx_store.gta_sa = (CStore*)g_mCalc.GetCurrentVAbyPreferedVA(0x91C3B4);
			}
			#endif
		}

		// Count definitions
		this->VehicleModelsLimit = 212;
		this->PedModelsLimit = 278;
		this->HierObjectsLimit = 92;
		this->WeaponModelsLimit = 51;
		this->ObjectsType1Limit = 14000;
		this->ObjectsType2Limit = 70;
		this->TimedObjectsLimit = 169;
		this->_2dfxLimit = 100;
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86)
	{
		using namespace Game_GTAIV;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			// Array definitions
			#ifdef IS_PLATFORM_WIN_X86
			this->IDE_cars_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xEAA59C);
			this->IDE_peds_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xEAA5A8);
			this->IDE_weap_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xEAA590);
			this->IDE_objsType1_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xEAA56C);
			this->IDE_objsType2_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xEAA578);
			this->IDE_tobj_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xEAA584);
			#endif
		}

		// Count declarations
		this->VehicleModelsLimit = 150;
		this->PedModelsLimit = 500;
		this->WeaponModelsLimit = 100;
		this->ObjectsType1Limit = 28000;
		this->ObjectsType2Limit = 550;
		this->TimedObjectsLimit = 1800;

		/////
		this->numberOfFieldsPerVehicle = 20;
		this->vehicleFieldsOffsets.gta_iv = (CVehicleFieldInfo*)g_mCalc.GetCurrentVAbyPreferedVA(0x1063560);
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
	{
		using namespace Game_GTAIV;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			// Array definitions
			#ifdef IS_PLATFORM_WIN_X86
			this->IDE_cars_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF2C14C);
			this->IDE_peds_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF2C158);
			this->IDE_weap_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF2C140);
			this->IDE_objsType1_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF2C11C);
			this->IDE_objsType2_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF2C128);
			this->IDE_tobj_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF2C134);
			#endif
		}

		// Count declarations
		this->VehicleModelsLimit = 205;
		this->PedModelsLimit = 585;
		this->WeaponModelsLimit = 100;
		this->ObjectsType1Limit = 28000;
		this->ObjectsType2Limit = 550;
		this->TimedObjectsLimit = 1800;

		/////
		this->numberOfFieldsPerVehicle = 20;
		this->vehicleFieldsOffsets.gta_iv = (CVehicleFieldInfo*)g_mCalc.GetCurrentVAbyPreferedVA(0x16193C0);
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
		using namespace Game_GTAIV;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			// Array definitions
			#ifdef IS_PLATFORM_WIN_X86
			this->IDE_cars_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF3E8E8);
			this->IDE_peds_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF3E8F4);
			this->IDE_weap_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF3E8DC);
			this->IDE_objsType1_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF3E8B8);
			this->IDE_objsType2_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF3E8C4);
			this->IDE_tobj_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF3E8D0);
			#endif
		}

		// Count declarations
		this->VehicleModelsLimit = 205;
		this->PedModelsLimit = 585;
		this->WeaponModelsLimit = 100;
		this->ObjectsType1Limit = 28000;
		this->ObjectsType2Limit = 550;
		this->TimedObjectsLimit = 1800;

		/////
		this->numberOfFieldsPerVehicle = 20;
		this->vehicleFieldsOffsets.gta_iv = (CVehicleFieldInfo*)g_mCalc.GetCurrentVAbyPreferedVA(0x1440C30);
	}
	else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
	{
		using namespace Game_GTAIV;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			// Array definitions
			#ifdef IS_PLATFORM_WIN_X86
			this->IDE_cars_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF27F94);
			this->IDE_peds_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF27FA0);
			this->IDE_weap_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF27F88);
			this->IDE_objsType1_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF27F64);
			this->IDE_objsType2_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF27F70);
			this->IDE_tobj_store.gta_iv = (CDataStore*)g_mCalc.GetCurrentVAbyPreferedVA(0xF27F7C);
			#endif
		}

		// Count declarations
		this->VehicleModelsLimit = 205;
		this->PedModelsLimit = 585;
		this->WeaponModelsLimit = 100;
		this->ObjectsType1Limit = 28000;
		this->ObjectsType2Limit = 550;
		this->TimedObjectsLimit = 1800;

		/////
		this->numberOfFieldsPerVehicle = 20;
		this->vehicleFieldsOffsets.gta_iv = (CVehicleFieldInfo*)g_mCalc.GetCurrentVAbyPreferedVA(0x15A1600);
	}
	else
	{
		this->IDE_cars_store.generic = 0;
		this->IDE_peds_store.generic = 0;
		this->IDE_hier_store.generic = 0;
		this->IDE_weap_store.generic = 0;
		this->IDE_objsType1_store.generic = 0;
		this->IDE_objsType2_store.generic = 0;
		this->IDE_tobj_store.generic = 0;
		this->IDE_2dfx_store.generic = 0;
	}
}

// Shutdown
void IDEsectionLimits::Shutdown()
{
	MAKE_VAR_GAME_VERSION();
	
	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		if (IDE_cars_store.bIsAllocated.Get())
			delete_in_app_space_array(IDE_cars_store.gta_sa);

		if (IDE_peds_store.bIsAllocated.Get())
			delete_in_app_space_array(IDE_peds_store.gta_sa);

		if (IDE_hier_store.bIsAllocated.Get())
			delete_in_app_space_array(IDE_hier_store.gta_sa);

		if (IDE_weap_store.bIsAllocated.Get())
			delete_in_app_space_array(IDE_weap_store.gta_sa);

		if (IDE_objsType1_store.bIsAllocated.Get())
			delete_in_app_space_array(IDE_objsType1_store.gta_sa);

		if (IDE_objsType2_store.bIsAllocated.Get())
			delete_in_app_space_array(IDE_objsType2_store.gta_sa);

		if (IDE_tobj_store.bIsAllocated.Get())
			delete_in_app_space_array(IDE_tobj_store.gta_sa);

		if (IDE_2dfx_store.bIsAllocated.Get())
			delete_in_app_space_array(IDE_2dfx_store.gta_sa);
	}
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
	{
		if (vehicleFieldsOffsets.bIsAllocated.Get())
			delete_in_app_space_array(vehicleFieldsOffsets.gta_iv);
	}
}
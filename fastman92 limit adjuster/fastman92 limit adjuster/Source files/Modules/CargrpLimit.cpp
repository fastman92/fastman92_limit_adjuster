/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CargrpLimit.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>
#include <string>

using namespace Game;

CargrpLimit g_cargrpLimits;

///////////// CLoadedCarGroup /////////////

// Copies data from different loaded car group.
void __thiscall CLoadedCarGroup::CopyFromDifferentLoadedCarGroup(CLoadedCarGroup* source)
{
	memcpy(this, source, g_cargrpLimits.CPopulation__m_iCarsPerGroup * sizeof(uint16_t));
}

// Adds a member
void __thiscall CLoadedCarGroup::AddMember(uint16_t vehicleID)
{
	unsigned int i = 0;

	while (this->m_carArray[i] != 0xFFFF)
	{
		i++;

		if (i >= g_cargrpLimits.CPopulation__m_iCarsPerGroup)
			return;
	}

	this->m_carArray[i] = vehicleID;
}

// Returns member with specified index
int __thiscall CLoadedCarGroup::GetMember(int index)
{
	return this->m_carArray[index];
}

// Counts members
int __thiscall CLoadedCarGroup::CountMembers()
{
	unsigned int i = 0;

	do
	{
		if (this->m_carArray[i] == 0xFFFF)
			break;

		i++;
	} while (i < g_cargrpLimits.CPopulation__m_iCarsPerGroup);

	return i;
}

// Removes a member
void CLoadedCarGroup::RemoveMember(uint16_t vehicleID)
{
	int16_t carsPerGroup = (int16_t)g_cargrpLimits.CPopulation__m_iCarsPerGroup;

	int index = 0;

	while (this->m_carArray[index] != vehicleID)
	{
		index++;

		if (index >= carsPerGroup)
			break;
	}

	int16_t lastIndex = carsPerGroup - 1;

	// Move following elements
	while (index < lastIndex)
	{
		this->m_carArray[index] = this->m_carArray[index + 1];
		index++;
	}

	this->m_carArray[lastIndex] = 0xFFFF;
}

// Clears loaded group
void __thiscall CLoadedCarGroup::Clear()
{
	memset(this, -1, g_cargrpLimits.CPopulation__m_iCarsPerGroup * sizeof(uint16_t));
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	/////////////////////////////////////////////////////////////
	enum ePopulationCarGroup
	{
		CAR_POPCYCLE_GROUP_WORKERS,
		CAR_POPCYCLE_GROUP_BUSINESS,
		CAR_POPCYCLE_GROUP_CLUBBERS,
		CAR_POPCYCLE_GROUP_FARMERS,
		CAR_POPCYCLE_GROUP_BEACHFOLK,
		CAR_POPCYCLE_GROUP_PARKFOLK,
		CAR_POPCYCLE_GROUP_CASUAL_RICH,
		CAR_POPCYCLE_GROUP_CASUAL_AVERAGE,
		CAR_POPCYCLE_GROUP_CASUAL_POOR,
		CAR_POPCYCLE_GROUP_PROSTITUTES,
		CAR_POPCYCLE_GROUP_CRIMINALS,
		CAR_POPCYCLE_GROUP_GOLFERS,
		CAR_POPCYCLE_GROUP_SERVANTS,
		CAR_POPCYCLE_GROUP_AIRCREW,
		CAR_POPCYCLE_GROUP_ENTERTAINERS,
		CAR_POPCYCLE_GROUP_OUT_OF_TOWN_FACTORY,
		CAR_POPCYCLE_GROUP_DESERT_FOLK,
		CAR_POPCYCLE_GROUP_AIRCREW_RUNWAY,
		CAR_GANG1_BALLAS_BLACK,
		CAR_GANG2_FAMILIES_PLAYER_BLACK,
		CAR_GANG3_LSV_MEX,
		CAR_GANG4_SFR_MEX,
		CAR_GANG5_DNB_VIETS,
		CAR_GANG6_ITALIAN_MAFIA,
		CAR_GANG7_TRIAD,
		CAR_GANG8_VLA_MEX,
		CAR_GANG9_UNUSED,
		CAR_GANG10_UNUSED,
		CAR_Dealers,
		CAR_Boats,
		CAR_Cheat1_shit_cars,
		CAR_Cheat2_fast_cars,
		CAR_Cheat3_ninja,
		CAR_Cheat4_funhouse,
	};

	// Returns pointer to end of loaded gang cars array
	uint16_t* CPopulation::GetPointerToEndOfLoadedGangsCarsArray()
	{
		return g_cargrpLimits.CPopulation__m_LoadedGangCars.ptr->m_carArray
			+ CPopulation::m_iNumberOfGangCarGroups * g_cargrpLimits.CPopulation__m_iCarsPerGroup;
	}

	// Returns pointer to specified car group
	uint16_t* CPopulation::GetPointerToCarGroup(int group)
	{
		return &g_cargrpLimits.CPopulation__m_CarGroups.ptr[group * g_cargrpLimits.CPopulation__m_iCarsPerGroup];
	}

	// Returns number of cars in group
	int16_t __cdecl CPopulation::GetNumberOfCarsInGroup(int group)
	{
		return g_cargrpLimits.CPopulation__m_nNumCarsInGroup.ptr[group];
	}

	// Returns vehicle ID from car group
	int __cdecl CPopulation::GetVehicleIDFromCarGroup(int group, int index)
	{
		return g_cargrpLimits.CPopulation__m_CarGroups.ptr[group * g_cargrpLimits.CPopulation__m_iCarsPerGroup + index];
	}

	// Returns true if value on index to car group array is unused
	bool __cdecl CPopulation::IsCarGroupIndexUnused(int group, int index)
	{
		return GetVehicleIDFromCarGroup(group, index) == UNUSED_INDEX_VALUE;
	}

	// Sets vehicle ID in car group.
	void __cdecl CPopulation::SetVehicleIDinCarGroup(int group, int index, WORD vehID)
	{
		GetPointerToCarGroup(group)[index] = vehID;
	}

	// Sets car group index unused.
	void __cdecl CPopulation::SetCarGroupIndexUnused(int groupID, int index)
	{
		GetPointerToCarGroup(groupID)[index] = UNUSED_INDEX_VALUE;
	}

	// Checks if vehicle ID is in group
	bool __cdecl CPopCycle::IsCarInGroup(int group, uint16_t VehicleID)
	{
		int numberOfCarsInGroup = CPopulation::GetNumberOfCarsInGroup(group);

		if (numberOfCarsInGroup <= 0)
			return false;

		uint16_t* pCarGroup = CPopulation::GetPointerToCarGroup(group);

		for (int i = 0; i < numberOfCarsInGroup; i++)
		{
			if (pCarGroup[i] == VehicleID)
				return true;
		}

		return false;
	}

	NAKED void patch_CLoadedCarGroup__PickRandomCar()
	{
		__asm
		{
			// esp = 0

			sub esp, 3Ch;
			push ebp;

			// esp = -40h
			mov edx, ecx;

			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_cargrpLimits, CargrpLimit, ms_BufferFromStack1);
			mov[esp + 10h], eax;	// store pointer to buffer

			////// -----
			mov[esp + 08h], edx;


			// -----------
			push edx;
			call CLoadedCarGroup::CountMembers;
			mov ebp, eax;
			pop edx;

			// go back
			mov eax, 0x611C6E;
			jmp eax;
		};
	}

	NAKED void patch_CLoadedCarGroup__PickRandomCar_611C8D()
	{
		__asm
		{
			push edx;	// save EDX register

			mov ecx, [esp + 20h];	// carGroup
			call CLoadedCarGroup::Clear;

			pop edx;	// restore EDX register

			xor esi, esi;
			test ebp, ebp;

			// go back
			push 611CA3h;
			ret;
		}
	}

	NAKED void patch_CLoadedCarGroup__PickRandomCar_611D5B()
	{
		__asm
		{
			mov esi, [esp + 1Ch];	// [esp+4Ch+carGroup.m_carArray]
			movsx esi, word ptr[esi];

			// go back
			push 611D60h;
			ret;
		}
	}

	NAKED void patch_CStreaming__RemoveLoadedVehicle()
	{
		__asm
		{
			sub esp, 30h;

			push ebx;
			push esi;

			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_cargrpLimits, CargrpLimit, ms_BufferFromStack1);
			mov[esp + 8], ecx;

			// go back
			push 40C025h;
			ret;
		}
	}

	NAKED void patch_CStreaming__ReclassifyLoadedCars()
	{
		__asm
		{
			// esp = 0
			sub esp, 60h;
			push esi;
			push edi;

			// esp = -0x68

			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_cargrpLimits, CargrpLimit, ms_BufferFromStack1);	// copyOfAppropriateLoadedCars
			mov[esp + 8], ecx;

			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_cargrpLimits, CargrpLimit, ms_BufferFromStack2);	// copyOfInAppropriateLoadedCars
			mov[esp + 0x38], ecx;

			// esp = -0x68

			// call functions
			push ASM_ACCESS_LIMIT_VAR_32_BIT(g_cargrpLimits, CargrpLimit, CPopulation__m_AppropriateLoadedCars);
			mov ecx, [esp + 0xC];		// [esp + ms_BufferFromStack1]
			call CLoadedCarGroup::CopyFromDifferentLoadedCarGroup;

			push ASM_ACCESS_LIMIT_VAR_32_BIT(g_cargrpLimits, CargrpLimit, CPopulation__m_InAppropriateLoadedCars);
			mov ecx, [esp + 0x3C];		// [esp + ms_BufferFromStack2]
			call CLoadedCarGroup::CopyFromDifferentLoadedCarGroup;

			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_cargrpLimits, CargrpLimit, CPopulation__m_AppropriateLoadedCars);
			call CLoadedCarGroup::Clear;

			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_cargrpLimits, CargrpLimit, CPopulation__m_InAppropriateLoadedCars);
			call CLoadedCarGroup::Clear;

			// go back
			push 40AFDDh;
			ret;
		}
	}

	NAKED void patch_CStreaming__StreamZoneModels_Gangs()
	{
		__asm
		{
			sub esp, 50h;
			push esi;

			// esp = -0x54

			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_cargrpLimits, CargrpLimit, ms_BufferFromStack1);

			mov[esp + 0x24], ecx;

			xor esi, esi;

			// go back
			push 0x40AA1B;
			ret;
		}
	}

	NAKED void patch_CLoadedCarGroup__PickLeastUsedModel_611EA4()
	{
		__asm
		{
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_cargrpLimits, CargrpLimit, CPopulation__m_iCarsPerGroup);
		xLoop:
			cmp     word ptr[edx + eax * 2], 0;
			jl      goBack;
			inc     edi;
			inc     eax;
			cmp     eax, ecx;
			jl      xLoop;

		goBack:
			mov ecx, 611EB2h;
			jmp ecx;
		}
	}

	NAKED void patch_CLoadedCarGroup__SortBasedOnUsage()
	{
		__asm
		{
			sub esp, 8;

			mov[esp], ecx; // save ECX register

			call CLoadedCarGroup::CountMembers;
			mov edx, eax;
			mov ecx, [esp];	// restore ECX register

			// go back
			mov eax, 0x611E25;
			jmp eax;
		}
	}

	NAKED void patch_CStreaming__AddToLoadedVehiclesList_HOODLUM_0156638D()
	{
		__asm
		{
			add esi, 2;
			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_cargrpLimits, CargrpLimit, CPopulation__m_iCarsPerGroup);
			shl eax, 1;
			add edi, eax;

			// go back
			mov eax, 0x1566393;
			jmp eax;
		}
	}
}
#endif

// Cargrp cars per group
void CargrpLimit::SetCargrpLimit(int iCarGroups, int iCarsPerGroup)
{
	MAKE_VAR_GAME_VERSION();

	if (gameVersion != GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		return;

	#ifdef IS_PLATFORM_WIN_X86
	using namespace Game_GTASA;

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	uint32_t memoryAddress;

	ms_BufferFromStack1 = (CLoadedCarGroup*)new uint16_t[iCarsPerGroup];
	ms_BufferFromStack2 = (CLoadedCarGroup*)new uint16_t[iCarsPerGroup];

	if (!CPatch::IsDebugModeActive() && (iCarsPerGroup > 23 || iCarGroups > 34))
	{
		CPopulation__m_iNumberOfCarGroups = iCarGroups;
		CPopulation__m_iCarsPerGroup = iCarsPerGroup;
		CPopulation__m_fCarsPerGroup = (float)iCarsPerGroup;

		CPopulation__m_CarGroups.ptr = new uint16_t[iCarGroups * iCarsPerGroup];
		memset(CPopulation__m_CarGroups.ptr, NULL, iCarGroups * iCarsPerGroup * sizeof(uint16_t));
		CPopulation__m_CarGroups.bIsAllocated.Set(true);

		CPopulation__m_nNumCarsInGroup.ptr = new int16_t[iCarGroups];
		memset(CPopulation__m_nNumCarsInGroup.ptr, NULL, iCarGroups * sizeof(int16_t));
		CPopulation__m_nNumCarsInGroup.bIsAllocated.Set(true);

		// CPopulation::ms_vehiclesLoaded
		CPopulation__ms_vehiclesLoaded.ptr = (CLoadedCarGroup*)new uint16_t[iCarsPerGroup];
		memset(CPopulation__ms_vehiclesLoaded.ptr, NULL, iCarsPerGroup * sizeof(uint16_t));
		CPopulation__ms_vehiclesLoaded.bIsAllocated.Set(true);

		// CPopulation::m_LoadedBoats
		CPopulation__m_LoadedBoats.ptr = (CLoadedCarGroup*)new uint16_t[iCarsPerGroup];
		memset(CPopulation__m_LoadedBoats.ptr, NULL, iCarsPerGroup * sizeof(uint16_t));
		CPopulation__m_LoadedBoats.bIsAllocated.Set(true);

		// CPopulation::m_InAppropriateLoadedCars
		CPopulation__m_InAppropriateLoadedCars.ptr = (CLoadedCarGroup*)new uint16_t[iCarsPerGroup];
		memset(CPopulation__m_InAppropriateLoadedCars.ptr, NULL, iCarsPerGroup * sizeof(uint16_t));
		CPopulation__m_InAppropriateLoadedCars.bIsAllocated.Set(true);

		// CPopulation::m_AppropriateLoadedCars
		CPopulation__m_AppropriateLoadedCars.ptr = (CLoadedCarGroup*)new uint16_t[iCarsPerGroup];
		memset(CPopulation__m_AppropriateLoadedCars.ptr, NULL, iCarsPerGroup * sizeof(uint16_t));
		CPopulation__m_AppropriateLoadedCars.bIsAllocated.Set(true);

		// CPopulation::m_LoadedGangCars
		CPopulation__m_LoadedGangCars.ptr = (CLoadedCarGroup*)new uint16_t[CPopulation::m_iNumberOfGangCarGroups * iCarsPerGroup];
		memset(CPopulation__m_LoadedGangCars.ptr, NULL, CPopulation::m_iNumberOfGangCarGroups * iCarsPerGroup * sizeof(uint16_t));
		CPopulation__m_LoadedGangCars.bIsAllocated.Set(true);
	}

	if (CPopulation__m_iCarsPerGroup > 63)
		throw f92_runtime_error("Currently, cargrp.dat cars per group limit can't be more than 63.");		

	/// CLoadedCarGroup
	void(CLoadedCarGroup::* _PtrCLoadedCarGroup_AddMember)(uint16_t vehicleID) = &CLoadedCarGroup::AddMember;
	void*& PtrCLoadedCarGroup_AddMember = (void*&)_PtrCLoadedCarGroup_AddMember;

	void(CLoadedCarGroup::* _PtrCLoadedCarGroup_Clear)() = &CLoadedCarGroup::Clear;
	void*& PtrCLoadedCarGroup_Clear = (void*&)_PtrCLoadedCarGroup_Clear;

	void(CLoadedCarGroup::* _PtrCLoadedCarGroup_CopyFromDifferentLoadedCarGroup)(CLoadedCarGroup*) = &CLoadedCarGroup::CopyFromDifferentLoadedCarGroup;
	void*& PtrCLoadedCarGroup_CopyFromDifferentLoadedCarGroup = (void*&)_PtrCLoadedCarGroup_CopyFromDifferentLoadedCarGroup;

	int(CLoadedCarGroup::* _PtrCLoadedCarGroup_CountMembers)() = &CLoadedCarGroup::CountMembers;
	void*& PtrCLoadedCarGroup_CountMembers = (void*&)_PtrCLoadedCarGroup_CountMembers;

	void(CLoadedCarGroup::* _PtrCLoadedCarGroup_RemoveMember)(uint16_t vehicleID) = &CLoadedCarGroup::RemoveMember;
	void*& PtrCLoadedCarGroup_RemoveMember = (void*&)_PtrCLoadedCarGroup_RemoveMember;

	CPatch::RedirectFunction(0x611BB0, PtrCLoadedCarGroup_AddMember);
	CPatch::RedirectFunction(0x611C30, PtrCLoadedCarGroup_CountMembers);
	CPatch::RedirectFunction(0x611B90, PtrCLoadedCarGroup_Clear);

	// .text:00611C50; CLoadedCarGroup::PickRandomCar(bool, bool)
	// .text:00611C50     _ZN15CLoadedCarGroup13PickRandomCarEbb proc near	
	CPatch::RedirectFunction(0x611C50, &patch_CLoadedCarGroup__PickRandomCar);

	CPatch::RedirectFunction(0x611C8D, &patch_CLoadedCarGroup__PickRandomCar_611C8D);

	CPatch::RedirectFunction(0x611D5B, patch_CLoadedCarGroup__PickRandomCar_611D5B);

	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT8(0x611CA9, 0x8B);		// change lea into mov
	CPatch::PatchUINT8(0x611D74, 0x8B);		// change lea into mov
	CPatch::LeaveThisLevel();

	// .text:00611E90; CLoadedCarGroup::PickLeastUsedModel(int)
	// .text:00611E90     _ZN15CLoadedCarGroup18PickLeastUsedModelEi proc near
	CPatch::RedirectFunction(0x611EA4, &patch_CLoadedCarGroup__PickLeastUsedModel_611EA4);

	// .text:00611BD0; void __thiscall CLoadedCarGroup__RemoveMember(void *this, int vehicleID)
	// .text:00611BD0     _ZN15CLoadedCarGroup12RemoveMemberEi	
	CPatch::RedirectFunction(0x611BD0, PtrCLoadedCarGroup_RemoveMember);
	/*
	CPatch::PatchUINT8(0x611BE9 + 2, (BYTE)CPopulation::m_iCarsPerGroup);
	CPatch::PatchUINT8(0x611BF2 + 2, (BYTE)CPopulation::m_iCarsPerGroup - 1);
	CPatch::PatchUINT32(0x611BFB + 1, CPopulation::m_iCarsPerGroup - 1);
	CPatch::PatchUINT8(0x611C09 + 3, (BYTE)(CPopulation::m_iCarsPerGroup - 1) * sizeof(int16_t));
	*/

	// .text:00611E10; void __thiscall CLoadedCarGroup__SortBasedOnUsage(CLoadedCarGroup *this)
	// .text:00611E10     _ZN15CLoadedCarGroup16SortBasedOnUsageEv proc near
	CPatch::RedirectFunction(0x611E10, &patch_CLoadedCarGroup__SortBasedOnUsage);

	/////////////////////////////////// DIFFERENT STUFF ///////////////////////////////////

	// .text:00406EE0     ; int __cdecl CPopulation__GetVehicleIDFromCarGroup(int group, int index)
	// .text:00406EE0     CPopulation__GetVehicleIDFromCarGroup proc near
	CPatch::RedirectFunction(0x406EE0, &CPopulation::GetVehicleIDFromCarGroup);

	// .text:00406F00; char __cdecl CPopulation__IsCarGroupIndexUnused(int group, int index)
	// .text:00406F00     CPopulation__IsCarGroupIndexUnused proc near
	CPatch::RedirectFunction(0x406F00, &CPopulation::IsCarGroupIndexUnused);

	// .text:00406F50; char __cdecl CPopCycle__IsCarInGroup(int group, int VehicleID)
	// .text:00406F50     _ZN9CPopCycle12IsCarInGroupEii proc near
	CPatch::RedirectFunction(0x406F50, &CPopCycle::IsCarInGroup);


	///////////// CStreaming /////////////'
	////////////             ////////////

	// .text:00408000; CStreaming::AddToLoadedVehiclesList(int)
	// .text:00408000     _ZN10CStreaming23AddToLoadedVehiclesListEi proc near
	CPatch::PatchPointer(0x1566300 + 3, &CPopulation__m_nNumCarsInGroup.ptr[CAR_Boats]);
	CPatch::PatchPointer(0x1566310 + 4, CPopulation::GetPointerToCarGroup(CAR_Boats));

	CPatch::PatchPointer(0x156632C + 1, CPopulation__m_AppropriateLoadedCars.ptr);

	CPatch::EnterNewLevelAndDisableDebugState();

	CPatch::PatchUINT8(0x1566333, 0xB9);	// mov ecx, offset _ZN11CPopulation25m_InAppropriateLoadedCarsE
	CPatch::PatchPointer(0x1566333 + 1, CPopulation__m_InAppropriateLoadedCars.ptr);

	CPatch::PatchUINT16(0x1566333 + 5, 0x13EB);	// jmp 0156634D
	CPatch::LeaveThisLevel();

	// Problem here!

	CPatch::PatchPointer(0x1566353 + 1, &CPopulation__m_nNumCarsInGroup.ptr[CAR_GANG1_BALLAS_BLACK]);
	CPatch::PatchPointer(0x1566363 + 2, CPopulation::GetPointerToCarGroup(CAR_GANG1_BALLAS_BLACK));
	CPatch::PatchPointer(0x156637A + 1, CPopulation__m_LoadedBoats.ptr);
	CPatch::PatchPointer(0x1566382 + 2, CPopulation__m_LoadedGangCars.ptr);

	CPatch::RedirectFunction(0x156638D, &patch_CStreaming__AddToLoadedVehiclesList_HOODLUM_0156638D);

	CPatch::PatchPointer(0x156639C + 1, CPopulation__ms_vehiclesLoaded.ptr);
	CPatch::PatchPointer(0x1566393 + 2, &CPopulation__m_nNumCarsInGroup.ptr[CAR_Dealers]);

	// .text:0040AA10; void __cdecl CStreaming__StreamZoneModels_Gangs(RwV3D *unused_and_unknown)
	// .text:0040AA10     _ZN10CStreaming22StreamZoneModels_GangsERK7CVector proc near
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::RedirectFunction(0x40AA15, &patch_CStreaming__StreamZoneModels_Gangs);

	memoryAddress = 0x40AD1C;
	CPatch::PatchUINT8(memoryAddress, 0x56);	// push esi
	memoryAddress += 1;
	CPatch::PatchUINT32(memoryAddress, 0x34244C8B);		// mov ecx, [esp + 34h];  ; copyOfGangLoadedCars
	memoryAddress += 4;
	CPatch::PutCallFunction(memoryAddress, PtrCLoadedCarGroup_CopyFromDifferentLoadedCarGroup);	// call CLoadedGroup::CopyFromDifferentLoadedCarGroup

	CPatch::PatchUINT16(0x40AD26, 0x09EB);	// jmp 0040AD26
	CPatch::PatchUINT32(0x40AD31, 0x30244C8B);

	CPatch::PatchUINT8(0x40AF39, 0x8B);		// change lea into mov	
	CPatch::LeaveThisLevel();

	CPatch::PatchPointer(0x40AAFB + 4, CPopulation__m_LoadedGangCars.ptr);
	CPatch::PatchPointer(0x40ACCA + 4, &CPopulation__m_nNumCarsInGroup.ptr[CAR_GANG1_BALLAS_BLACK]);
	CPatch::PatchPointer(0x40ACE0 + 4, CPopulation::GetPointerToCarGroup(CAR_GANG1_BALLAS_BLACK));

	CPatch::PatchPointer(0x40AD50 + 1, CPopulation__m_AppropriateLoadedCars.ptr);
	CPatch::PatchPointer(0x40AD71 + 1, CPopulation__m_AppropriateLoadedCars.ptr);
	CPatch::PatchPointer(0x40AD84 + 1, CPopulation__m_AppropriateLoadedCars.ptr);
	CPatch::PatchPointer(0x40AD9C + 1, CPopulation::GetPointerToCarGroup(CAR_GANG1_BALLAS_BLACK));
	CPatch::PatchUINT32(0x40ADB7 + 1, CPopulation__m_iCarsPerGroup);
	CPatch::PatchUINT8(0x40ADDB + 2, (BYTE)CPopulation__m_iCarsPerGroup * sizeof(WORD));

	CPatch::PatchPointer(0x40ADDF + 2, CPopulation::GetPointerToCarGroup(CAR_Dealers));
	CPatch::PatchUINT8(0x40AF62 + 2, (BYTE)CPopulation__m_iCarsPerGroup);
	CPatch::PatchUINT8(0x40AF65 + 2, (BYTE)CPopulation__m_iCarsPerGroup * sizeof(WORD));

	// .text:00421900; int __cdecl CCarCtrl__ChooseCarModelToLoad(int group)
	// .text:00421900     _ZN8CCarCtrl20ChooseCarModelToLoadEi proc near
	CPatch::PatchUINT8(0x42190E + 2, (BYTE)CPopulation__m_iCarsPerGroup);
	CPatch::PatchPointer(0x421911 + 4, CPopulation__m_nNumCarsInGroup.ptr);
	CPatch::PatchPointer(0x421944 + 4, CPopulation__m_CarGroups.ptr);

	// .text:00424CE0; signed int __cdecl CCarCtrl__ChooseModel(int *out)
	// .text:00424CE0     _ZN8CCarCtrl11ChooseModelEPi proc near
	CPatch::PatchPointer(0x424D84 + 3, CPopulation::GetPointerToCarGroup(CAR_Dealers));

	CPatch::PatchPointer(0x424E41 + 1, CPopulation__m_AppropriateLoadedCars.ptr);
	CPatch::PatchUINT8(0x424F20 + 2, (BYTE)CPopulation__m_iCarsPerGroup);

	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchPointer(0x424F40 + 2, &CPopulation__m_fCarsPerGroup);
	CPatch::LeaveThisLevel();

	CPatch::PatchPointer(0x424F4E + 4, CPopulation::GetPointerToCarGroup(CAR_GANG1_BALLAS_BLACK));
	CPatch::PatchPointer(0x424F5B + 4, CPopulation::GetPointerToCarGroup(CAR_GANG1_BALLAS_BLACK));

	// .text:005B9F70; void __cdecl CPopulation__SetVehicleIDinCarGroup(int group, int index, WORD vehID)
	// .text:005B9F70     CPopulation__SetVehicleIDinCarGroup proc near
	CPatch::RedirectFunction(0x5B9F70, &CPopulation::SetVehicleIDinCarGroup);

	// .text:005B9F90; void __cdecl CPopulation__SetCarGroupIndexUnused(int groupID, int index)
	// .text:005B9F90     CPopulation__SetCarGroupIndexUnused proc near
	CPatch::RedirectFunction(0x5B9F90, &CPopulation::SetCarGroupIndexUnused);

	// .text:00406F40; int16_t __cdecl CPopulation__GetNumberOfCarsInGroup(int group)
	// .text:00406F40     CPopulation__GetNumberOfCarsInGroup proc near
	CPatch::PatchPointer(0x406F44 + 4, CPopulation__m_nNumCarsInGroup.ptr);

	// .text:005B9FD0; void __cdecl CPopulation__SetCarGroupSize(int group, int16_t newSize)
	// .text:005B9FD0     CPopulation__SetCarGroupSize proc near
	CPatch::PatchPointer(0x5B9FD9 + 4, CPopulation__m_nNumCarsInGroup.ptr);

	// .text:005BD1A0; CPopulation::LoadCarGroups(void)
	// .text:005BD1A0     _ZN11CPopulation13LoadCarGroupsEv proc near
	CPatch::PatchPointer(0x5BD1F8 + 4, CPopulation__m_nNumCarsInGroup.ptr);
	CPatch::PatchPointer(0x5BD2C9 + 4, CPopulation__m_CarGroups.ptr);
	CPatch::PatchUINT8(0x5BD2D3 + 2, (BYTE)CPopulation__m_iCarsPerGroup);
	CPatch::PatchUINT8(0x5BD2E2 + 2, (BYTE)CPopulation__m_iCarsPerGroup);
	CPatch::PatchUINT32(0x5BD2F5 + 1, CPopulation__m_iCarsPerGroup);
	CPatch::PatchPointer(0x5BD2FE + 3, CPopulation__m_CarGroups.ptr);
	CPatch::PatchUINT8(0x5BD31C + 2, (BYTE)CPopulation__m_iCarsPerGroup);

	// .text:0040B700; CStreaming::StreamVehiclesAndPeds(void)
	// .text:0040B700     _ZN10CStreaming21StreamVehiclesAndPedsEv proc near
	CPatch::PatchPointer(0x40B996 + 1, CPopulation__ms_vehiclesLoaded.ptr);

	// .text:0040CFD0; CStreaming::RemoveLeastUsedModel(unsigned int)
	// .text:0040CFD0     _ZN10CStreaming20RemoveLeastUsedModelEj proc near
	CPatch::PatchPointer(0x40D18A + 1, CPopulation__ms_vehiclesLoaded.ptr);
	CPatch::PatchPointer(0x40D1D6 + 1, CPopulation__ms_vehiclesLoaded.ptr);
	CPatch::PatchPointer(0x40D1EE + 1, CPopulation__ms_vehiclesLoaded.ptr);
	CPatch::PatchPointer(0x40D214 + 1, CPopulation__ms_vehiclesLoaded.ptr);
	CPatch::PatchPointer(0x40D22C + 1, CPopulation__ms_vehiclesLoaded.ptr);

	// .text:0040E170; char __cdecl CStreaming__ProcessLoadingChannel(uint32_t streamNum)
	// .text:0040E170     _ZN10CStreaming21ProcessLoadingChannelEi proc near
	CPatch::PatchPointer(0x40E217 + 1, CPopulation__ms_vehiclesLoaded.ptr);

	// .text:005B8AD0; void __cdecl CStreaming__Init2()
	// .text:005B8AD0     _ZN10CStreaming5Init2Ev proc near
	CPatch::PatchPointer(0x5B8D98 + 1, CPopulation__ms_vehiclesLoaded.ptr);

	// .text:0040C020; CStreaming::RemoveLoadedVehicle(void)
	// .text:0040C020     _ZN10CStreaming19RemoveLoadedVehicleEv proc near
	CPatch::PatchPointer(0x40C025 + 1, CPopulation__m_InAppropriateLoadedCars.ptr);
	CPatch::PatchPointer(0x40C041 + 1, CPopulation__m_InAppropriateLoadedCars.ptr);
	CPatch::PatchPointer(0x40C074 + 1, CPopulation__m_InAppropriateLoadedCars.ptr);

	CPatch::PatchPointer(0x40C093 + 1, CPopulation__m_LoadedBoats.ptr);
	CPatch::PatchPointer(0x40C0A1 + 1, CPopulation__m_LoadedBoats.ptr);
	CPatch::PatchPointer(0x40C0B2 + 1, CPopulation__m_LoadedBoats.ptr);
	CPatch::PatchPointer(0x40C0E5 + 1, CPopulation__m_LoadedBoats.ptr);
	CPatch::PatchPointer(0x40C0FA + 1, CPopulation__m_AppropriateLoadedCars.ptr);

	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::RedirectFunction(0x40C020, &patch_CStreaming__RemoveLoadedVehicle);

	memoryAddress = 0x40C0F5;
	CPatch::PatchUINT8(memoryAddress, 0x68);		// push		offset _ZN11CPopulation23m_AppropriateLoadedCarsE
	CPatch::PatchPointer(memoryAddress + 1, CPopulation__m_AppropriateLoadedCars.ptr);

	CPatch::PatchUINT32(memoryAddress + 5, 0x10244C8B); // mov ecx, [esp+40h+pBuffer]	

	CPatch::PutCallFunction(memoryAddress + 9, PtrCLoadedCarGroup_CopyFromDifferentLoadedCarGroup);

	CPatch::NOPinstructions(memoryAddress + 14, 2);

	CPatch::PatchUINT8(0x40C105, 0x8B);		// change lea into mov

	CPatch::NOPinstructions(0x40C109, 2);

	CPatch::PatchUINT8(0x40C110, 0x8B);		// change lea into mov

	CPatch::PatchUINT8(0x40C121, 0x8B);		// change lea into mov

	CPatch::PatchUINT8(0x40C14F, 0x8B);		// change lea into mov

	CPatch::LeaveThisLevel();

	// .text:004212E0; CCarCtrl::Init(void)
	// .text:004212E0     _ZN8CCarCtrl4InitEv proc near
	CPatch::PatchPointer(0x42135E + 1, CPopulation__m_LoadedGangCars.ptr);
	CPatch::PatchUINT8(0x421377 + 2, (uint8_t)CPopulation__m_iCarsPerGroup * sizeof(uint16_t));
	CPatch::PatchPointer(0x42137A + 2, CPopulation::GetPointerToEndOfLoadedGangsCarsArray());
	CPatch::PatchPointer(0x421382 + 1, CPopulation__m_AppropriateLoadedCars.ptr);
	CPatch::PatchPointer(0x42138C + 1, CPopulation__m_InAppropriateLoadedCars.ptr);
	CPatch::PatchPointer(0x421397 + 1, CPopulation__m_LoadedBoats.ptr);

	// .text:004213B0; CCarCtrl::ReInit(void)
	// .text:004213B0     _ZN8CCarCtrl6ReInitEv proc near
	CPatch::PatchPointer(0x4213FD + 1, CPopulation__m_LoadedGangCars.ptr);
	CPatch::PatchUINT8(0x421409 + 2, (BYTE)CPopulation__m_iCarsPerGroup * sizeof(uint16_t));
	CPatch::PatchPointer(0x42140C + 2, CPopulation::GetPointerToEndOfLoadedGangsCarsArray());
	CPatch::PatchPointer(0x421414 + 1, CPopulation__m_AppropriateLoadedCars.ptr);
	CPatch::PatchPointer(0x42141E + 1, CPopulation__m_InAppropriateLoadedCars.ptr);
	CPatch::PatchPointer(0x421428 + 1, CPopulation__m_LoadedBoats.ptr);

	// .text:004080F0; void __cdecl CStreaming__RemoveCarModel(int vehicleID)
	// .text:004080F0     _ZN10CStreaming14RemoveCarModelEi
	CPatch::PatchPointer(0x156C0A7 + 1, CPopulation__m_AppropriateLoadedCars.ptr);
	CPatch::PatchPointer(0x156C0B2 + 1, CPopulation__m_InAppropriateLoadedCars.ptr);
	CPatch::PatchPointer(0x156C0BD + 1, CPopulation__m_LoadedBoats.ptr);
	CPatch::PatchPointer(0x156C0C7 + 1, CPopulation__m_LoadedGangCars.ptr);
	CPatch::PatchUINT8(0x156C0D7 + 2, (uint8_t)CPopulation__m_iCarsPerGroup * sizeof(uint16_t));
	CPatch::PatchPointer(0x156C0DA + 2, CPopulation::GetPointerToEndOfLoadedGangsCarsArray());
	CPatch::PatchPointer(0x156C0E3 + 1, CPopulation__ms_vehiclesLoaded.ptr);

	// .text:00421970; CCarCtrl::ChooseBoatModel(void)
	// .text:00421970     _ZN8CCarCtrl15ChooseBoatModelEv
	CPatch::PatchPointer(0x421972 + 1, CPopulation__m_LoadedBoats.ptr);

	// .text:00430050; CCarCtrl::GenerateOneRandomCar(void)
	// .text:00430050     _ZN8CCarCtrl20GenerateOneRandomCarEv
	CPatch::PatchPointer(0x43051B + 1, CPopulation__m_LoadedBoats.ptr);

	// .text:0040AFA0; CStreaming::ReclassifyLoadedCars(void)
	// .text:0040AFA0     _ZN10CStreaming20ReclassifyLoadedCarsEv
	CPatch::EnterNewLevelAndDisableDebugState();

	CPatch::RedirectFunction(0x40AFA0, &patch_CStreaming__ReclassifyLoadedCars);
	CPatch::PatchUINT8(0x40AFDD, 0x8B);		// change lea into mov
	CPatch::PatchUINT8(0x40AFF1, 0x8B);		// change lea into mov
	CPatch::PatchUINT8(0x40B019, 0x8B);		// change lea into mov
	CPatch::PatchUINT8(0x40B027, 0x8B);		// change lea into mov
	CPatch::PatchUINT8(0x40B037, 0x8B);		// change lea into mov
	CPatch::PatchUINT8(0x40B05F, 0x8B);		// change lea into mov	
	CPatch::LeaveThisLevel();

	CPatch::PatchPointer(0x40B008 + 1, CPopulation__m_AppropriateLoadedCars.ptr);
	CPatch::PatchPointer(0x40B00F + 1, CPopulation__m_InAppropriateLoadedCars.ptr);

	CPatch::PatchPointer(0x40B04E + 1, CPopulation__m_AppropriateLoadedCars.ptr);
	CPatch::PatchPointer(0x40B055 + 1, CPopulation__m_InAppropriateLoadedCars.ptr);

	///// SCM command: 0x09B2 - GET_RANDOM_CAR_MODEL_IN_MEMORY /////
	CPatch::PatchPointer(0x4794B3 + 1, CPopulation__m_AppropriateLoadedCars.ptr);

	///// SCM command: 0x03C5 - CREATE_RANDOM_CAR_FOR_CAR_PARK /////
	CPatch::PatchPointer(0x484D22 + 1, CPopulation__m_AppropriateLoadedCars.ptr);

	// .text:006144B0; CPopulation::PickRiotRoadBlockCar(void)
	// .text:006144B0     _ZN11CPopulation20PickRiotRoadBlockCarEv
	CPatch::PatchUINT8(0x6144F1 + 2, (BYTE)CPopulation__m_iCarsPerGroup * sizeof(WORD));
	CPatch::PatchPointer(0x6144F4 + 2, CPopulation__m_LoadedGangCars.ptr);
	CPatch::PatchPointer(0x614512 + 3, CPopulation__m_AppropriateLoadedCars.ptr);
	CPatch::PatchUINT8(0x614537 + 2, (BYTE)CPopulation__m_iCarsPerGroup * sizeof(WORD));
	CPatch::PatchPointer(0x614542 + 3, CPopulation__m_InAppropriateLoadedCars.ptr);
	CPatch::PatchUINT8(0x614567 + 2, (BYTE)CPopulation__m_iCarsPerGroup * sizeof(WORD));

	// .text:006F34D0; CCarGenerator::DoInternalProcessing(void)
	// .text:006F34D0     _ZN13CCarGenerator20DoInternalProcessingEv proc near
	CPatch::PatchPointer(0x6F357E + 1, CPopulation__m_AppropriateLoadedCars.ptr);

	// .text:0040B650; void __cdecl CStreaming__StreamVehiclesAndPeds_Always(RwV3D *a1)
	// .text:0040B650     _ZN10CStreaming28StreamVehiclesAndPeds_AlwaysERK7CVector proc near
	CPatch::PatchPointer(0x40B6A0 + 1, CPopulation__m_AppropriateLoadedCars.ptr);

	// .text:0040B4F0; CStreaming::StreamOneNewCar(void)
	// .text:0040B4F0     _ZN10CStreaming15StreamOneNewCarEv proc near
	CPatch::PatchPointer(0x1563BBB + 1, CPopulation__m_LoadedBoats.ptr);	// 40B56A normally
	CPatch::PatchPointer(0x1563BE3 + 1, CPopulation__m_LoadedBoats.ptr);

	// .text:00614490; CCarCtrl::ChooseGangCarModel(int)
	// .text:00614490     _ZN8CCarCtrl18ChooseGangCarModelEi proc near
	CPatch::PatchUINT8(0x614494 + 2, (BYTE)CPopulation__m_iCarsPerGroup * sizeof(WORD));
	CPatch::PatchPointer(0x407805 + 2, CPopulation__m_LoadedGangCars.ptr);


	///// DEBUG /////
	#if FALSE
	{
		// Disable _ZN10CStreaming22StreamZoneModels_GangsERK7CVector
		CPatch::PatchUINT8(0x40AA10, 0xC3);

		// Disable _ZN10CStreaming21StreamVehiclesAndPedsEv
		CPatch::PatchUINT8(0x40B700, 0xC3);

		// Disable _ZN10CStreaming28StreamVehiclesAndPeds_AlwaysERK7CVector
		CPatch::PatchUINT8(0x40B650, 0xC3);

		// Disable CStreaming::Update
		CPatch::PatchUINT8(0x40E670, 0xC3);

		// Disable _ZN17CTheCarGenerators7ProcessEv
		CPatch::PatchUINT8(0x6F3F40, 0xC3);

		// Disable CCarCtrl__GenerateRandomCars
		CPatch::PatchUINT8(0x4341C0, 0xC3);

		// Disable CCarCtrl::ChooseModel
		CPatch::PatchUINT8(0x424CE0, 0xC3);

		// Disable CRoadBlocks::GenerateRoadBlocks
		CPatch::PatchUINT8(0x4629E0, 0xC3);

		// Disable CStreaming::AddToLoadedVehiclesList
		CPatch::PatchUINT8(0x408000, 0xC3);

		// Disable part in CCarCtrl::Init
		static const char data[] = "\x5e\x5a\x83\xc4\x04\xc3";
		CPatch::PatchMemoryData(0x421370, data, sizeof(data) - 1);

		// Disable aprt in CCarCtrl::ReInit
		// CPatch::PatchUINT16(0x4213FD, 0xC35E);
		// CPatch::RedirectCode(0x4213FD, 0x421414);
		CPatch::PatchPointer(0x42140C + 2, CPopulation__m_LoadedGangCars + 5 * CPopulation__m_iCarsPerGroup);

		// Disable part in CStreaming::ProcessLoadingChannel
		CPatch::RedirectCode(0x40E217, 0x40E232);
	}
	#endif	

	/////////////// FINISH ///////////////
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of cargrp.dat, number of groups: %d number of members per group to: %d",
		CPopulation__m_iNumberOfCarGroups,
		CPopulation__m_iCarsPerGroup
	);

	CGenericLogStorage::WriteLineSeparator();
	#endif
}

// Initialize
void CargrpLimit::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	ms_BufferFromStack1 = NULL;
	ms_BufferFromStack2 = NULL;

	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		#ifdef IS_PLATFORM_WIN_X86
		CPopulation__m_CarGroups.ptr = (uint16_t*)0xC0ED38;
		#endif
		CPopulation__m_iNumberOfCarGroups = 34;
		CPopulation__m_iCarsPerGroup = 23;
		CPopulation__m_fCarsPerGroup = (float)CPopulation__m_iCarsPerGroup;

		#ifdef IS_PLATFORM_WIN_X86
		CPopulation__m_nNumCarsInGroup.ptr = (int16_t*)0xC0EC78;

		CPopulation__ms_vehiclesLoaded.ptr = (CLoadedCarGroup*)0x8E4C24;
		CPopulation__m_LoadedBoats.ptr = (CLoadedCarGroup*)0xC0E998;
		CPopulation__m_InAppropriateLoadedCars.ptr = (CLoadedCarGroup*)0xC0E9C8;
		CPopulation__m_AppropriateLoadedCars.ptr = (CLoadedCarGroup*)0xC0E9F8;
		CPopulation__m_LoadedGangCars.ptr = (CLoadedCarGroup*)0xC0EA28;
		#endif
	}
}

// Shutdown
void CargrpLimit::Shutdown()
{
	delete ms_BufferFromStack1;
	delete ms_BufferFromStack2;

	if (CPopulation__m_CarGroups.bIsAllocated.Get())
		delete[] CPopulation__m_CarGroups.ptr;

	if (CPopulation__m_nNumCarsInGroup.bIsAllocated.Get())
		delete[] CPopulation__m_nNumCarsInGroup.ptr;

	if (CPopulation__ms_vehiclesLoaded.bIsAllocated.Get())
		delete CPopulation__ms_vehiclesLoaded.ptr;

	if (CPopulation__m_LoadedBoats.bIsAllocated.Get())
		delete CPopulation__m_LoadedBoats.ptr;

	if (CPopulation__m_InAppropriateLoadedCars.bIsAllocated.Get())
		delete CPopulation__m_InAppropriateLoadedCars.ptr;

	if (CPopulation__m_AppropriateLoadedCars.bIsAllocated.Get())
		delete CPopulation__m_AppropriateLoadedCars.ptr;

	if (CPopulation__m_LoadedGangCars.bIsAllocated.Get())
		delete CPopulation__m_LoadedGangCars.ptr;
}
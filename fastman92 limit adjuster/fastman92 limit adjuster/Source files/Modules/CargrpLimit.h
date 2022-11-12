/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"
#include <stdint.h>


#pragma warning( push )
#pragma warning( disable : 4200 )
class CLoadedCarGroup	// size varies.
{
public:
	uint16_t m_carArray[];

	// Copies data from different loaded car group.
	void __thiscall CopyFromDifferentLoadedCarGroup(CLoadedCarGroup* source);

	// Returns member with specified index
	int __thiscall GetMember(int index);

	// Adds a member
	void __thiscall AddMember(uint16_t vehicleID);

	// Counts members
	int __thiscall CountMembers();

	// Removes a member
	void __thiscall RemoveMember(uint16_t vehicleID);

	// Clears loaded group
	void __thiscall Clear();
};
#pragma warning( pop )

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	class CPopulation
	{
	public:
		static const int m_iNumberOfGangCarGroups = 11;

		static const uint16_t UNUSED_INDEX_VALUE = 2000;

		// Returns pointer to end of loaded gang cars array
		static uint16_t* GetPointerToEndOfLoadedGangsCarsArray();

		// Returns pointer to specified car group
		static uint16_t* GetPointerToCarGroup(int group);

		// Returns number of cars in group
		static int16_t __cdecl GetNumberOfCarsInGroup(int group);

		// Returns vehicle ID from car group
		static int __cdecl GetVehicleIDFromCarGroup(int group, int index);

		// Returns true if value on index to car group array is unused
		static bool __cdecl IsCarGroupIndexUnused(int group, int index);

		// Sets vehicle ID in car group.
		static void __cdecl SetVehicleIDinCarGroup(int group, int index, uint16_t vehID);

		// Sets car group index unused.
		static void __cdecl SetCarGroupIndexUnused(int groupID, int index);
	};

	class CPopCycle
	{
	public:
		// Checks if vehicle ID is in group
		static bool __cdecl IsCarInGroup(int group, uint16_t VehicleID);
	};
}
#endif

class CargrpLimit : public CLimitAdjusterModule
{
public:
	struct {
		uint16_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CPopulation__m_CarGroups;

	uint32_t CPopulation__m_iNumberOfCarGroups;
	uint32_t CPopulation__m_iCarsPerGroup;
	float CPopulation__m_fCarsPerGroup;

	struct {
		int16_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CPopulation__m_nNumCarsInGroup;

	CLoadedCarGroup* ms_BufferFromStack1;
	CLoadedCarGroup* ms_BufferFromStack2;

	struct {
		CLoadedCarGroup* ptr;
		DEFINE_IS_ALLOCATED();
	} CPopulation__ms_vehiclesLoaded;

	struct {
		CLoadedCarGroup* ptr;
		DEFINE_IS_ALLOCATED();
	} CPopulation__m_LoadedBoats;

	struct {
		CLoadedCarGroup* ptr;
		DEFINE_IS_ALLOCATED();
	} CPopulation__m_InAppropriateLoadedCars;

	struct {
		CLoadedCarGroup* ptr;
		DEFINE_IS_ALLOCATED();
	} CPopulation__m_AppropriateLoadedCars;

	struct {
		CLoadedCarGroup* ptr;
		DEFINE_IS_ALLOCATED();
	} CPopulation__m_LoadedGangCars;

	// Cargrp cars per group
	void SetCargrpLimit(int iCarGroups, int iCarsPerGroup);

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();
};

extern CargrpLimit g_cargrpLimits;
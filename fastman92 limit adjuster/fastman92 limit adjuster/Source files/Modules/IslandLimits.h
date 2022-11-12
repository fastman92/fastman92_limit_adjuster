/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"
#include <stdint.h>

class IslandLimits : public CLimitAdjusterModule
{
public:
	unsigned int ms_iNumberOfIslands;

	static const int ms_maxNumberOfCabDriversPerIsland = 16;

	uint32_t* ms_CopPedIDsPerIsland;
	uint32_t* ms_CopCarIDsPerIsland;
	uint32_t* ms_AmbulanceVehicleIDsPerIsland;
	uint32_t* ms_MedicPedIDsPerIsland;
	uint32_t* ms_FireEngineVehicleIDsPerIsland;
	uint32_t* ms_FiremanPedIDsPerIsland;

	uint32_t* ms_CabDriverPedIDsPerIsland;
	uint32_t* ms_CabDriverNumberOfPedIDsPerIsland;
	float* ms_ItemPriceMultipliersPerIsland;

	// Initializes
	bool EnableIslandLimits(int iNumberOfIslands);

	// Sets cop ped ID for level
	void SetCopPedID(int level, int copPedID);

	// Sets cop car ID for level
	void SetCopCarID(int level, int copCarID);

	// Sets cop bike ID
	void SetCopBikeID(int copBikeID);

	// Sets cop bike driver ID
	void SetCopBikeDriverID(int copBikePedID);

	// Sets ambulance car ID for level
	void SetAmbulanceID(int level, int ambulanceID);

	// Sets medic ped ID for level
	void SetMedicID(int level, int medicID);

	// Sets fire engine ID for level
	void SetFireEngineID(int level, int fireEngineID);

	// Sets fireman ID for level
	void SetFiremanEngineID(int level, int firemanID);

	// Sets number of cab drivers for level
	void SetNumberOfCabDriversForLevel(int level, unsigned int numberOfCabDrivers);
		
	// Sets cab driver ID for level
	void SetCabDriverID(int level, int place, int cabDriverID);

	// Sets item price multiplier for level
	void SetItemPriceMultiplier(int level, float multiplier);
		
	// Print to log
	void PrintToLog();

	// Commits changes
	void CommitChanges();

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();
};

extern IslandLimits g_islandLimits;
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"
#include <set>

// template for list of IDs
class CListOfIDs
{
public:
	// unsigned int Count;
	std::set<int> Array;

	// Initializes
	void Init()
	{
		this->Array.clear();
	}

	// Adds new ID
	void AddNewID(int ID)
	{
		this->Array.emplace(ID);
	}

	// Checks if ID is in list
	bool IsIDinList(int ID)
	{
		for (unsigned int element : this->Array)
			if (element == ID)
				return true;

		return false;
	}

	// Returns count of IDs
	unsigned int GetCount()
	{
		return this->Array.size();
	}
};

class VehicleSpecialFeatures : public CLimitAdjusterModule
{
private:
	// hydras
	CListOfIDs ms_HydraVehicles;

	// ZR350 vehicles
	CListOfIDs ms_Zr350vehicles;
		
	// Returns true if vehicle is considered hydra
	bool IsHydra(int ID);

public:
	// Initialize
	virtual void Initialise() {}

	// Shutdown
	virtual void Shutdown() {}

	// Commits changes
	void CommitChanges();

	// Prints to log
	void PrintLogInfo();

	// Adds ID
	void AddHydra(int ID);

	// Adds ZR350 ID
	void AddZR350(int ID);
};

extern VehicleSpecialFeatures g_vehicleSpecialFeatures;
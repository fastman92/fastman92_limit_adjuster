/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

class SpecialLimits : public CLimitAdjusterModule
{
public:
	bool ms_bMakeHelicoptersLandOnWaterWhenCarsOnWaterCheatEnabled;
	bool ms_bDisablePlaneSpeedLimit;
	bool ms_bDisableRadarRotation;
	bool ms_bPaintjobsWorkOnAnyID;
	bool ms_bFixStreamingMemoryBug;
	bool ms_bFixKeyboardMakingBadMouseMovement;
	bool ms_bFixCheatsTypedByKeyboardNotWorking;
	bool ms_bAlterFileLoadingOrder;
	bool ms_bRemoveRequirementForLodDFFtoHoldNativePLGdata;
	bool ms_bMakeLoadingOfFilesFromRootDirectoryPossible;
	bool ms_bFixHALCrashingOnDevicesWithAndroid11AndHigher;
	bool ms_bDisableCINFOandMINFOLoading;

	// Make helicopters land on water when cars on water cheat enabled
	void MakeHelicoptersLandOnWater();

	// Disables 270 km\h plane speed limit.
	void DisablePlaneSpeedLimit();

	// Disables radar rotation
	void DisableRadarRotation();

	// Makes paintjobs for work for any ID
	void MakePaintjobsWorkForAnyID();

	// Enables loading text
	void EnableLoadingText();

	// Fixes installfolder problem, which fixes the following error:
	// the downloadable content required for this autoload is not available.
	void FixInstallFolderProblem();

	// Fixes keyboard making bad mouse movement
	void FixKeyboardMakingBadMouseMovement();

	// Fixes cheats typed from keyboard not working
	void FixCheatsTypedFromKeyboardNotWorking();

	// Alters file loading order
	void AlterFileLoadingOrder();

	// Removes a requirement for LOD DFF to hold native PLG data
	void RemoveRequirementForLodDFFtoHoldNativePLGdata();

	// Makes loading of files from root directory possible
	void MakeLoadingOfFilesFromRootDirectoryPossible();

	// Fix HAL crashing on devices with Android 11 and higher
	void FixHALCrashingOnDevicesWithAndroid11AndHigher();

	// Disable CINFO.BIN and MINFO.BIN loading
	void DisableCINFOandMINFOLoading();

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown() {};
};

extern SpecialLimits g_specialLimits;
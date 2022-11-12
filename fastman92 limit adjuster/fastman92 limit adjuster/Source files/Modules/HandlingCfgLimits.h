/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
// #define HANDLING_CFG_DEBUG

#include "../Core\CLimitAdjusterModule.h"

#include "../GameStructures/Rockstar Games/CAnimGroup.h"
#include "../GameStructures/Rockstar Games/tHandlingData.h"
#include "../GameStructures/Rockstar Games/HandlingExtendedStructs.h"

#define HANDLING_CFG_CHECK_ARRAY_BOUNDS

class HandlingCfgLimits : public CLimitAdjusterModule
{
public:
	static const tLimitDefinitionNonStatic ms_listOfLimits[5];

	bool bIs_cHandlingDataMgr_extended;

	// Limit values
	unsigned int ms_iStandardLinesLimit;
	bool ms_bStandardLinesLimitSet;

	unsigned int ms_iBikeLinesLimit;
	bool ms_bBikeLinesLimitSet;

	unsigned int ms_iFlyingLinesLimit;
	bool ms_bFlyingLinesLimitSet;

	unsigned int ms_iBoatLinesLimit;
	bool ms_bBoatLinesLimitSet;

	unsigned int ms_iAnimationGroupLinesLimit;
	bool ms_bAnimationGroupLinesLimitSet;

	struct {
		cHandlingDataMgr* ptr;
		DEFINE_IS_ALLOCATED();
	} mod_HandlingManager;

	struct {
		union {
			Game_GTASA::CAnimGroup* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CVehicleAnimGroupData__m_vehicleAnimGroups;

	/////////////////
	struct {
		union {
			Game_GTAIV::tHandlingData* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} g_handling;
	
	struct {
		union {
			Game_GTAIV::tBikeHandlingData* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} g_handlingBike;

	struct {
		union {
			Game_GTAIV::tFlyingHandlingData* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} g_handlingFlying;

	struct {
		union {
			Game_GTAIV::tBoatHandlingData* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} g_handlingBoat;

	//// offsets ////
	/*
	unsigned int ms_aStandardHandling_offset;
	unsigned int ms_aBikeHandling_offset;
	unsigned int ms_aFlyingHandling_offset;
	unsigned int ms_aBoatHandling_offset;

	unsigned int ms_sizeof_cHandlingDataMgr_extended;
	*/

	// sizes
	uint32_t m_sizeof_tHandlingData;
	uint32_t m_sizeof_tBikeHandlingData;
	uint32_t m_sizeof_tFlyingHandlingData;
	uint32_t m_sizeof_tBoatHandlingData;
	uint32_t m_sizeof_CAnimGroup;

	// Returns pointer to mod_HandlingManager
	cHandlingDataMgr* Get_mod_HandlingManager();

	// Returns true if handling.cfg is hacked.
	bool IsHandlingCfgLimitHacked();

	// Sets standard limit
	void SetStandardLinesLimit(unsigned int iStandardLines);

	// Sets bike limit
	void SetBikeLinesLimit(unsigned int iBikeLines);

	// Sets flying limit
	void SetFlyingLinesLimit(unsigned int iFlyingLines);

	// Sets boat limit
	void SetBoatLinesLimit(unsigned int iBoatLines);

	// Sets animation group limit
	void SetAnimationGroupLinesLimit(unsigned int iAnimationGroups);

	#ifdef IS_PLATFORM_WIN_X86
	// Patches handling.cfg limit
	void PatchHandlingCfgLimit_GTA_VC_PC_1_0();

	// Patches handling.cfg limit
	void PatchHandlingCfgLimit_GTA_SA_1_0_US_WIN_X86();

	// Patches handling.cfg limit
	void PatchHandlingCfgLimit_GTA_IV_1_0_4_0();

	// Patches handling.cfg limit
	void PatchHandlingCfgLimit_GTA_IV_1_0_7_0();

	// Patches handling.cfg limit
	void PatchHandlingCfgLimit_GTA_IV_1_0_8_0();

	// Patches handling.cfg limit
	void PatchHandlingCfgLimit_GTA_EFLC_1_1_2_0();
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	// Patches handling.cfg limit
	void PatchHandlingCfgLimit_GTA_SA_2_0_ANDROID_ARM32();
	#endif

	// Patches handling.cfg limit
	void PatchHandlingCfgLimit_GTA_SA();

	// Patches handling.cfg limit
	void PatchHandlingCfgLimit_GTA_IV();

	// Patches handling.cfg limit
	void PatchHandlingCfgLimit();

	// Set up dynamic structures
	void SetUpDynamicStructures(bool bExtendedPossible = false);

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();
};

extern HandlingCfgLimits g_handlingCfgLimits;
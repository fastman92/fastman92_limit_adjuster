/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CompressedVector.h"
#include "CRGBA.h"
#include "CBox.h"
#include "CompressedBox.h"
#include "../Core\CLimitAdjusterModule.h"
#include "../GameStructures/Rockstar Games/CPool.h"
#include <stdint.h>

namespace Game_GTASA
{
	class CZone
	{
	public:
		char name[8];
		char text[8];
		CompressedVector pos1;
		CompressedVector pos2;
		int16_t ZoneInfoIndex;
		char type;
		char level;
	};

	class CZoneInfo
	{
	public:
		char GangDensity[10];
		char DrugDealerCounter;
		CRGBA ZoneRGBA;
		char Flags1;
		char Flags2;
	};

	VALIDATE_SIZE(CZone, 0x20);
	VALIDATE_SIZE(CZoneInfo, 0x11);

	class COccluder
	{
	public:
		int16_t midX;
		int16_t midY;
		int16_t midZ;
		int16_t widthY;
		int16_t widthX;
		int16_t height;
		char rotation;
		char rotation2;
		char rotation3;
		char field_F;
		int16_t flags;
	};

	VALIDATE_SIZE(COccluder, 0x12);

	class COccluderExtended : public COccluder
	{
	public:
		int32_t exMidX;
		int32_t exMidY;
		int32_t exMidZ;
		int32_t exWidthY;
		int32_t exWidthX;
		int32_t exHeight;
	};

	static_assert(
		sizeof(COccluderExtended) % 2 == 0,
		"Size of COccluderExtended must be a multiply of 2."
		);

	struct CTimecycleBox
	{
		CBox m_box;
		int16_t m_farClip;
		char field_1A;
		int m_interiorCycleAndWeather;
		int field_20;
		int field_24;
	};

	VALIDATE_SIZE(CTimecycleBox, 0x28);

	struct CZoneDef
	{
		int16_t x;
		int16_t y;
		int16_t field_4;
		int16_t Ywidth;
		int16_t Xwidth;
		int16_t field_A;
		int16_t Zbottom;
		int16_t Ztop;
	};

	VALIDATE_SIZE(CZoneDef, 0x10);

	struct CCullZoneReflection : public CZoneDef
	{
		int cm;
		char vx;
		char vy;
		char vz;
		char flags;
	};

	VALIDATE_SIZE(CCullZoneReflection, 0x18);

	struct CCullZone : CZoneDef
	{
		int16_t flags;
	};

	VALIDATE_SIZE(CCullZone, 0x12);

	struct tAudioZoneBox
	{
		char m_Name[8];
		int16_t m_ID;
		int16_t m_Flags;
		CompressedBox m_Box;
	};

	VALIDATE_SIZE(tAudioZoneBox, 0x18);

	struct tAudioZoneBoxExtended : public tAudioZoneBox
	{
		CompressedBox_extended m_exBox;
	};

	struct tAudioZoneSphere
	{
		char m_Name[8];
		int16_t m_ID;
		int16_t m_Flags;
		CVector m_Pos;
		float m_Radius;
	};

	VALIDATE_SIZE(tAudioZoneSphere, 0x1C);

	class CPickup
	{
	public:
		int field_0;
		class CObject* pObject;
		int field_8;
		int regenerationTime;
		CompressedVector pos;
		int16_t field_16;
		int16_t wModelID;
		int16_t wGeneration;
		uint8_t nbPickupType;
		char flags;
		char field_1E;
		char field_1F;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CPickup, 0x20);

	class CPickup_extended : public CPickup
	{
	public:
		CompressedVector_extended exPos;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CPickup_extended, 0x2C);

	class CEntryExit
	{
	public:
		char unk[0x3C];
	};

	VALIDATE_SIZE(CEntryExit, 0x3C);
}

class IPLsectionLimits : public CLimitAdjusterModule
{
public:
	const float PICKUP_COORD_MULTIPLIER = 8.0;

	// Buildings limit
	unsigned int BuildingsLimit;

	// Dummies
	unsigned int DummiesLimit;

	// AnimatedBuildings
	unsigned int AnimatedBuildingsLimit;

	// IPL entries of file.
	struct {
		void** ptr;
		DEFINE_IS_ALLOCATED();
	} IPLentriesOfFile;

	// Current limit of IPL entries per file.
	unsigned int IPLentriesPerFileLimit;

	// IPL entity index array.
	struct {
		void*** ptr;
		DEFINE_IS_ALLOCATED();
	} IPLentityIndexArray;

	// Current limit of IPL entity index array
	unsigned int IPLentityIndexArrayLimit;

	// Current limit of Map zones
	unsigned int MapZonesLimit;

	// Current limit of Navigation zones.
	unsigned int NavigationZonesLimit;

	// COccluder structure coordinate extension coordinate limit hack enabled
	bool bCOccluderCoordLimitHackEnabled;

	// Current limit of interior occluders
	unsigned int InteriorOccludersLimit;
	bool bInteriorOccludersLimitSet;

	// Current limit of occluders
	unsigned int OccludersLimit;
	bool bOccludersLimitSet;
	
	// Current limit of timecyc boxes
	unsigned int TcycLimit;

	// Current limit of CULL mirror attribute zones
	unsigned int CullMirrorAttributeZonesLimit;

	// Current limit of CULL tunnel attribute zones
	unsigned int CullTunnelAttributeZonesLimit;

	// Current limit of CULL attribute zones
	unsigned int CullAttributeZonesLimit;

	// Stunt jumps limit
	unsigned int StuntJumpsLimit;

	// Entry exits limit
	unsigned int EntryExitsLimit;

	// Audio spheres limit
	unsigned int AudioZoneSpheresLimit;

	// Audio boxes coordinate limit hack enabled
	bool bAudioZonesBoxesCoordLimitHackEnabled;

	// Audio boxes limit
	unsigned int AudioZoneBoxesLimit;

	// Audio boxes limit set?
	bool bAudioZoneBoxesLimitSet;

	// Garage limit
	unsigned int GarageLimit;

	// Pickup patch enabled?
	bool bPickupPatchEnabled;

	// Pickups limit
	unsigned int PickupsLimit;

	// Pickups collected limit
	unsigned int PickupsCollectedLimit;

	////////////////

	// Map zones
	struct {
		union {
			Game_GTASA::CZone* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CTheZones__MapZoneArray;

	// Navigation zones
	struct {
		union {
			Game_GTASA::CZone* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CTheZones__NavigationZoneArray;

	// Zone info array
	struct {
		union {
			Game_GTASA::CZoneInfo* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CTheZones__ZoneInfoArray;

	// Interior occluders
	struct {
		union {
			void* ptr;
			Game_GTASA::COccluder* gta_sa;
			Game_GTASA::COccluderExtended* gta_sa_extended;
		};
		DEFINE_IS_ALLOCATED();
	} COcclusion__aInteriorOccluders;

	// Occluders
	struct {
		union {
			void* ptr;
			Game_GTASA::COccluder* gta_sa;
			Game_GTASA::COccluderExtended* gta_sa_extended;
		};
		DEFINE_IS_ALLOCATED();
	} COcclusion__aOccluders;

	// Timecycle boxes
	struct {
		union {
			Game_GTASA::CTimecycleBox* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CTimeCycle__m_aBoxes;

	// CULL mirror attribute zones
	struct {
		union {
			Game_GTASA::CCullZoneReflection* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CCullZones__aMirrorAttributeZones;

	// CULL tunnel attribute zones
	struct {
		union {
			Game_GTASA::CCullZone* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CCullZones__aTunnelAttributeZones;

	// CULL attribute zones
	struct {
		union {
			Game_GTASA::CCullZone* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CCullZones__aAttributeZones;

	// Audio zone boxes
	struct {
		void* ptr;
		DEFINE_IS_ALLOCATED();
	} CAudioZones__m_aBoxes;

	// Audio zone spheres
	struct {
		union {
			Game_GTASA::tAudioZoneSphere* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CAudioZones__m_aSpheres;

	// Pickups
	struct {
		union {
			Game_GTASA::CPickup_extended* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CPickups__aPickUps;

	// Pickups collected
	struct {
		uint32_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CPickups__aPickUpsCollected;

	// CEntryExitManager::mp_poolEntryExits pool
	struct {
		union {
			CPool_GTASA<Game_GTASA::CEntryExit>** gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CEntryExitManager__mp_poolEntryExits;

	// IPL : inst section, buildings
	void SetIplBuildings(unsigned int iBuildings);

	// IPL : inst section, animated buildings
	void SetIplAnimatedBuildings(unsigned int iBuildings);

	// IPL : inst section, dummies
	void SetIplDummies(unsigned int iDummies);

	// IPL: inst per file
	void SetInstLimitPerFile(unsigned int iInstPerFile);

	// IPL: entity index array (40)
	void SetEntityIndexArray(unsigned int iEntityIndexArrayLimit);

	// IPL: map zones
	void SetMapZones(unsigned int iMapZones);

	// IPL: navigation zones
	void SetNavigationZones(unsigned int iNavigationZones);

	// IPL: COccluder structure coordinate extension
	void SetCOccluderCoordinateLimitHack(bool bCOccluderLimitHack);

	// IPL: interior occluders
	void SetInteriorOccluders(unsigned int iInteriorOccluders);

	// IPL: occluders
	void SetOccluders(unsigned int iOccluders);

	// IPL: tcyc
	void SetTcyc(unsigned int iTcycEntries);

	// IPL: cull mirror attribute zones
	void SetCullMirrorAttributeZones(unsigned int iCullMirrorAttributeZones);

	// IPL: cull tunnel attribute zones
	void SetCullTunnelAttributeZones(unsigned int iCullTunnelAttributeZones);

	// IPL: cull attribute zones
	void SetCullAttributeZones(unsigned int iCullAttributeZones);

	// IPL: jump
	void SetStuntJumps(unsigned int iStuntJumps);

	// IPL: enex
	void SetEntryExits(unsigned int iEntryExits);

	// IPL: auzo, boxes coordinate limit
	void SetAudioZoneBoxesCoordinateLimitHack(bool bAudioZoneBoxesCoordLimitHack);

	// IPL: auzo, boxes
	void SetAudioZoneBoxes(unsigned int iAudioZonesBoxes);

	// IPL: auzo, spheres
	void SetAudioZoneSpheres(unsigned int iAudioZoneSpheres);

	// Enables pickup patch
	void EnablePickupPatch(bool bEnable);

	// IPL: pick
	void SetPickups(unsigned int iPickups);

	// IPL: pickup collectives
	void SetPickupCollected(unsigned int iPickupCollected);

	// Applies enabled limits
	void ApplyEnabledLimits();

	// Patches loading functions
	void PatchSaveBlockLoadingFunctions();

	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown();

private:
	// Patches interior occluders
	void PatchInteriorOccluders();

	// Patches occluders
	void PatchOccluders();

	// Patch COccluder coordinate limit
	void PatchCOccluderCoordinateLimit();

	// Patches audio zone boxes
	void PatchAudioZoneBoxes();
	
	// Patches pickups
	void PatchPickups();
};

extern IPLsectionLimits g_IPLsectionlimits;
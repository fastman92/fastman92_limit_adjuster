/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#pragma once
#include "../Core/CLimitAdjusterModule.h"
#include <CVector.h>

namespace Game_GTA_old
{
	#pragma warning( push )
	#pragma warning( disable : 4200 )
		class CStore
		{
		public:
			unsigned int count;
			alignas(void*) char array[];
		};
	#pragma warning( pop )
}

// GTA IV
namespace Game_GTAIV
{
	struct CDataStore
	{
		int nSize;
		int nAllocated;
		int pData;
	};

	// Author: fastman92
	enum eVehicleField
	{
		VEHICLE_PART_BOOT_OPEN,	// 0
		VEHICLE_PART_BONNET_FWD,	// 1
		VEHICLE_PART_BONNET_BWD,	// 2
		VEHICLE_PART_CINEY_WHEEL,	// 3
		VEHICLE_PART_CINEY_UNDER,	// 4
		VEHICLE_PART_CINEY_MISC_1,	// 5
		VEHICLE_PART_CINEY_MISC_2,	// 6
		VEHICLE_PART_JACKED,	// 7
		VEHICLE_PART_BUSTED,	// 8
		VEHICLE_PART_CARPHONE,	// 9
		VEHICLE_PART_BONNET_L,	// 10
		// author of the enum: fastman92
		VEHICLE_PART_BONNET_R,	// 11
		VEHICLE_PART_CINEY_WHEEL_2,	// 12
		VEHICLE_PART_CINEY_BACK,	// 13
		VEHICLE_PART_BUMPER,	// 14
		VEHICLE_PART_AIM_FR,	// 15
		VEHICLE_PART_CINEY_FAR_1,	// 16
		VEHICLE_PART_CINEY_FAR_2,	// 17
		VEHICLE_PART_CINEY_FAR_3,	// 18
		VEHICLE_PART_CINEY_FAR_4,	// 19
	};

	// structure used in relation to file vehOff.csv
	struct CVehicleFieldInfo
	{
		CVector m_vPos;
		int field_C;
		CVector m_vRot;
		float m_fFOV;
	};
}

class IDEsectionLimits : public CLimitAdjusterModule
{
public:
	// Array declarations
	struct {
		union {
			void* generic;
			Game_GTA_old::CStore* gta_vc;
			Game_GTA_old::CStore* gta_sa;
			Game_GTAIV::CDataStore* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} IDE_cars_store;

	struct {
		union {
			void* generic;
			Game_GTA_old::CStore* gta_vc;
			Game_GTA_old::CStore* gta_sa;
			Game_GTAIV::CDataStore* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} IDE_peds_store;

	struct {
		union {
			void* generic;
			Game_GTA_old::CStore* gta_sa;
			Game_GTAIV::CDataStore* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} IDE_hier_store;

	struct {
		union {
			void* generic;
			Game_GTA_old::CStore* gta_sa;
			Game_GTAIV::CDataStore* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} IDE_weap_store;

	struct {
		union {
			void* generic;
			Game_GTA_old::CStore* gta_sa;
			Game_GTAIV::CDataStore* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} IDE_objsType1_store;

	struct {
		union {
			void* generic;
			Game_GTA_old::CStore* gta_sa;
			Game_GTAIV::CDataStore* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} IDE_objsType2_store;

	struct {
		union {
			void* generic;
			Game_GTA_old::CStore* gta_sa;
			Game_GTAIV::CDataStore* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} IDE_tobj_store;

	struct {
		union {
			void* generic;
			Game_GTA_old::CStore* gta_sa;
			Game_GTAIV::CDataStore* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} IDE_2dfx_store;

	// Count declarations
	unsigned int VehicleModelsLimit;
	unsigned int PedModelsLimit;
	unsigned int HierObjectsLimit;
	unsigned int WeaponModelsLimit;
	unsigned int ObjectsType1Limit;
	unsigned int ObjectsType2Limit;
	unsigned int TimedObjectsLimit;
	unsigned int _2dfxLimit;

	// number of fields per vehicle
	unsigned int numberOfFieldsPerVehicle;

	// vehicleFieldsOffsets
	struct {
		union {
			Game_GTAIV::CVehicleFieldInfo* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} vehicleFieldsOffsets;

	// IDE: cars(212)
	void SetVehicleModels(unsigned int iVehicleModels);

	// IDE: peds(278)
	void SetPedModels(unsigned int iPedModels);

	// IDE: hier(92)
	void SetHierObjects(unsigned int iHierObjects);

	// IDE: weap(51)
	void SetWeaponModels(unsigned int iWeaponModels);

	// IDE: objs:type1(14000)
	void SetIDEobjsType1(unsigned int iObjectsType1);

	// IDE: objs:type2(70)
	void SetIDEobjsType2(unsigned int iObjectsType2);

	// IDE: tobj(169)
	void SetTimedObjects(unsigned int iTimedObjects);

	// IDE: 2dfx(100)
	void Set2DFX(unsigned int i2DFX);

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();
};

extern IDEsectionLimits g_IDEsectionLimits;
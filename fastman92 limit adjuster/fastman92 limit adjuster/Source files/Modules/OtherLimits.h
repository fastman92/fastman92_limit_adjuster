/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#include "IPLsectionLimits.h"

#include "../Core\CLimitAdjusterModule.h"

#include "../GameStructures/Rockstar Games/CRegisteredCorona.h"
#include "../GameStructures/Rockstar Games/CReference.h"

#include <Assertions.h>
#include <CRGBA.h>
#include <CVector.h>

namespace Game_GTASA
{
	struct CCoverPoint
	{
		char gap[28];
	};

	VALIDATE_SIZE(CCoverPoint, 28);

	struct CObjectInfo
	{
	  int fMass;
	  int fTurnMass;
	  int fAirResistance;
	  int fElasticity;
	  int fBuoyancyConstant;
	  int fUprootLimit;
	  int fColDamageMultiplier;
	  char colDamageEffect;
	  char specialColResponseCase;
	  char cameraAvoidObject;
	  char causesExplosion;
	  char fxType;
	  char field_21;
	  char field_22;
	  char field_23;
	  CVector fxOffset;
	  int field_30;
	  int field_34;
	  CVector breakVelocity;
	  int fBreakVelocityRand;
	  int fSmashMultiplier;
	  int sparksOnImpact;
	};

	VALIDATE_SIZE(CObjectInfo, 0x50);

	// radar trace
	struct CMarker
	{
		int Color;
		int EntityHandle;
		CVector Pos;
		int16_t _Index;
		int _SphereRadius;
		int16_t Size;

		union
		{
			int entryExitID;
			CEntryExit* pEntryExit;
		};

		char Icon;
		char _Flag;
		char _RadarMode_or_EntityType;
		char field_27;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CMarker, 0x28);

	// CSetPiece
	// dkluin may wonder how it's made
	template <typename T> class CSetPiece_forDifferentType
	{
	public:
		int m_nLastGenerationTime;
		CompressedBox2D_templateForSingleType<NoWrapper, T> m_nAreaCorner;
		CompressedBox2D_templateForSingleType<NoWrapper, T> m_nSpawnBox;
		CompressedBox2D_templateForSingleType<NoWrapper, T> m_nTargetBox;
		uint8_t m_nType;
	};

	typedef CSetPiece_forDifferentType<int16_t> CSetPiece;
	typedef CSetPiece_forDifferentType<int32_t> CSetPiece_extended;

	VALIDATE_SIZE(CSetPiece, 0x20);
	VALIDATE_SIZE(CSetPiece_extended, 0x38);
}

class OtherLimits : public CLimitAdjusterModule
{
public:
	// array of references
	struct {
		union {
			CReference* gta_sa;
		};

		DEFINE_IS_ALLOCATED();
	} CReferences__aRefs;

	// References
	int ms_iReferencesLimit;

	// Cover points
	struct {
		union {
			Game_GTASA::CCoverPoint* gta_sa;
		};

		DEFINE_IS_ALLOCATED();
	} CCover__m_aPoints;

	// Cover point limit
	int ms_iCoverPointLimit;

	// Number of plate textures
	int ms_iNumberOfPlateTextures;

	// Plateback textures
	struct {
		void** ptr;
		DEFINE_IS_ALLOCATED();
	} CustomCarPlateMgr__pPlatebackTexTab;

	// Coronas
	struct {
		union {
			Game_GTASA::CRegisteredCorona* gta_sa;
		};

		DEFINE_IS_ALLOCATED();
	} CCoronas__aCoronas;

	// Coronas limit
	int ms_iCoronasLimit;

	// Max size of single collision
	int ms_maxSizeOfSingleCollision;

	// COL file read buffer
	struct {
		char* ptr;
		DEFINE_IS_ALLOCATED();
	} ms_pColfileReadBuffer;

	// Object info entry limit
	int ms_iObjectInfoLimit;

	// Object info array
	struct {
		union {
			Game_GTASA::CObjectInfo* gta_sa;
		};

		DEFINE_IS_ALLOCATED();
	} CObjectData__ms_aObjectInfo;

	// Vehicle colors limit
	int ms_iVehicleColorsLimit;
	bool bIsVehicleColorIDextended;

	// Vehicle colors array
	struct {
		union
		{
			CRGBA* gta_sa;
			CBGRA* gta_iv;
		};

		DEFINE_IS_ALLOCATED();
	} CVehicleModelInfo__ms_vehicleColourTable;

	// Police scanner prefix table
	struct {
		uint32_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CVehicleModelInfo__ms_policeScannerPrefixTable;

	// Police scanner colour table
	struct {
		uint32_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CVehicleModelInfo__ms_policeScannerColourTable;

	// LOD distance
	float LODdistance;

	// Radar traces limit
	int ms_iRadarTracesLimit;

	// Radar traces array
	struct {
		union {
			Game_GTASA::CMarker* gta_sa;
		};

		DEFINE_IS_ALLOCATED();
	} CRadar__ms_RadarTrace;

	// Radar map legend list
	struct {
		int16_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CRadar__MapLegendList;

	// Max number of particles active
	int ms_iMaxNumberOfParticlesActive;

	// Set pieces
	unsigned int ms_iSetPiecesLimit;
	bool bSetPiecesCoordinatePatchEnabled;

	struct {
		union {
			void* generic;
			Game_GTASA::CSetPiece* gta_sa_standard;
			Game_GTASA::CSetPiece_extended* gta_sa_extended;
		};
		DEFINE_IS_ALLOCATED();
	} CSetPieces__aSetPieces;

	// Sets the max number of vehicle color
	void SetVehicleColors(int iVehicleColors);

	// Sets the max number of references
	void SetReferences(int iNumberOfReferences);

	// Sets the cover points
	void SetCoverPoints(int iCoverPoints);

	// Sets the coronas
	void SetCoronaLimit(int iCoronaLimit);

	// Sets object info limit
	void SetObjectInfoEntries(int iObjectInfoLimit);

	// Sets the max size of single collision
	void SetMaxSizeOfSingleCollision(int iSizeOfSingleCollision);

	// Sets the LOD distance limit
	void SetLODdistanceLimit(float LODdistance);

	// Sets the radar traces limit
	void SetRadarTracesLimit(int iRadarTraces);

	// Sets number of plate textures
	void SetNumberOfPlateTextures(int iPlateTextures);

	// Sets max number of particles active
	void SetMaxNumberOfParticlesActive(int iMaxNumberOfParticlesActive);
	
	// Sets max number of set pieces
	void SetMaxNumberOfSetPieces(unsigned int iSetPieces, bool bCoordinateHack);

	// Patches loading functions
	void PatchSaveBlockLoadingFunctions();

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();
};

extern OtherLimits g_otherLimits;
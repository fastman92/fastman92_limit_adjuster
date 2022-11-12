/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

#include <CVector.h>
#include <CBox.h>
#include <CBox2D.h>

#include <DynamicTypes/DynamicStructure.h>

#include <stdint.h>

// GTA San Andreas
namespace Game_GTASA
{
	struct CStoredShadow
	{
		CVector Pos;
		CBox2D RotBox;
		float zDistance;
		float Scale;
		void *pTexture;
		void *pShadowData;
		int16_t Intensity;
		char Type;
		char ColorRed;
		char ColorGreen;
		char ColorBlue;
		int16_t Flags;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CStoredShadow, 0x34);

	struct CPolyBunch
	{
		char gap_0[84];
		CPolyBunch *pNext;
		char gap_58[12];
		int field_64;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CPolyBunch, 0x68);

	struct CStaticShadow
	{
		char gap_0[4];
		int field_4;
		int TimeCreated;
		int field_C;
		int field_10;
		int field_14;
		int field_18;
		int field_1C;
		int field_20;
		int field_24;
		int field_28;
		int field_2C;
		int field_30;
		char field_34;
		char field_35;
		char field_36;
		char field_37;
		char field_38;
		char field_39;
		char field_3A;
		char field_3B;
		char field_3C;
		char field_3D;
		char gap_3E[1];
		char field_3F;
	};

	VALIDATE_SIZE(CStaticShadow, 0x40);

	struct CPermanentShadow
	{
		CVector Pos;
		CBox Box;
		int TimeCreated;
		int field_28;
		int field_2C;
		int16_t field_30;
		char field_32;
		char field_33;
		char field_34;
		char field_35;
		char gap_36[1];
		char field_37;
	};

	VALIDATE_SIZE(CPermanentShadow, 0x38);

	class CShadowCamera
	{
	private:
		void* m_rwCamera;
		void* m_rwCameraFB;
	};
	
#define MAKE_CRealTimeShadowManager(structName, macro) \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, bool>), m_initialized); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, bool>), field_1); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, void*[]>), m_realTimeShadowPool); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, CShadowCamera>), m_camera1); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, CShadowCamera>), m_camera2); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tDynamicStructEnd>), endOfStructure);
	
	class CRealTimeShadowManager : public CDynamicStructure
	{
	public:
		MAKE_CRealTimeShadowManager(CRealTimeShadowManager, STRUCTURE_STATIC_MEMBER_DECLARATION);
	};
}

class ShadowLimits : public CLimitAdjusterModule
{
public:
	unsigned int ms_ShadowsStoredLimit;
	unsigned int ms_PolyBunchesLimit;
	unsigned int ms_StaticShadowsLimit;
	unsigned int ms_PermanentShadowsLimit;
	unsigned int ms_RealTimeShadowsLimit;

	struct {
		union {
			Game_GTASA::CStoredShadow* gta_sa;
		};

		DEFINE_IS_ALLOCATED();
	} CShadows__asShadowsStored;

	struct {
		union {
			Game_GTASA::CPolyBunch* gta_sa;
		};

		DEFINE_IS_ALLOCATED();
	} CShadows__aPolyBunches;

	struct {
		union {
			Game_GTASA::CStaticShadow* gta_sa;
		};

		DEFINE_IS_ALLOCATED();
	} CShadows__aStaticShadows;

	struct {
		union {
			Game_GTASA::CPermanentShadow* gta_sa;
		};

		DEFINE_IS_ALLOCATED();
	} CShadows__aPermanentShadows;

	struct {
		union {
			Game_GTASA::CRealTimeShadowManager* gta_sa;
		};

		DEFINE_IS_ALLOCATED();
	} g_realTimeShadowMan;

	// Sets shadows stored
	void SetShadowStored(unsigned int iShadowStoredLimit);

	// Sets poly bunches
	void SetPolyBunches(unsigned int iPolyBunchesLimit);

	// Sets shadows
	void SetStaticShadows(unsigned int iStaticShadows);

	// Sets permament shadows
	void SetPermanentShadows(unsigned int iPernamentShadows);

	// Sets real time shadows
	void SetRealTimeShadows(unsigned int iRealTimeShadows);

private:
	// Allocates CRealTimeShadowManager
	void Allocate_CRealTimeShadowManager();

public:

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();
};

extern ShadowLimits g_shadowLimits;
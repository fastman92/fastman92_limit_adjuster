/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "cTransmission.h"
#include "eVehicleFlags.h"

#include <CVector.h>

// GTA III
namespace Game_GTAIII
{
	enum eVehicleLightsSize : unsigned char {
		LIGHTS_LONG,
		LIGHTS_SMALL,
		LIGHTS_BIG,
		LIGHTS_TALL
	};

	struct tHandlingData {
		int m_dwVehicleId;
		float m_fMass; // 1.0 to 50000.0
		float field_8;
		float m_fTurnMass;
		CVector m_vDimensions; // 0.0 > x > 20.0
		CVector m_vCentreOfMass; // -10.0 > x > 10.0
		int m_nPercentSubmerged; // 10 to 120
		float m_fBuoyancyConstant;
		float m_fTractionMultiplier; // 0.5 to 2.0
		cTransmission m_transmissionData;
		float m_fBrakeBias; // 0.0 > x > 1.0
		bool m_bABS;
		char field_9D;
		char field_9E;
		char field_9F;
		float m_fSteeringLock; // 10.0 to 40.0
		float m_fTractionLoss; // 0.0 > x > 1.0
		float m_fTractionBias; // 0.0 > x > 1.0
		int field_AC;
		float m_fSuspensionForceLevel;   // not [L/M/H]
		float m_fSuspensionDampingLevel; // not [L/M/H]
		float m_fSuspensionUpperLimit;
		float m_fSuspensionLowerLimit;
		float m_fSuspensionBiasBetweenFrontAndRear;
		float m_fCollisionDamageMultiplier; // 0.2 to 5.0
		union {
			eVehicleFlags m_nVehicleFlags;
			struct {
				unsigned int m_b1gBoost : 1;
				unsigned int m_b2gBoost : 1;
				unsigned int m_bRevBonnet : 1;
				unsigned int m_bHangingBoot : 1;
				unsigned int m_bNoDoors : 1;
				unsigned int m_bIsVan : 1;
				unsigned int m_bIsBus : 1;
				unsigned int m_bIsLow : 1;
				unsigned int m_bDblExhaust : 1;
				unsigned int m_bTailgateBoot : 1;
				unsigned int m_bNoswingBoot : 1;
				unsigned int m_bNonplayerStabiliser : 1;
				unsigned int m_bNeutralHandling : 1;
				unsigned int m_bHasNoRoof : 1;
				unsigned int m_bIsBig : 1;
				unsigned int m_bHalogenLights : 1;
			};
		};
		float m_fSeatOffsetDistance; // ped seat position offset towards centre of car
		unsigned int m_nMonetaryValue; // 1 to 100000
		eVehicleLightsSize m_nFrontLights;
		eVehicleLightsSize m_nRearLights;
		short field_D6;
	};

	VALIDATE_SIZE(tHandlingData, 0xD8);
}

// GTA Vice City
namespace Game_GTAVC
{
	enum eVehicleLightsSize : unsigned char
	{
		LIGHTS_LONG,
		LIGHTS_SMALL,
		LIGHTS_BIG,
		LIGHTS_TALL
	};

	struct tHandlingData {
		int m_dwVehicleId;
		float fMass;
		float fMassInverted;
		float fTurnMass;
		CVector m_vDimensions;
		CVector m_vecCentreOfMass;
		int nPercentSubmerged;
		float fBuoyancyForce;
		float fTractionMultiplier;
		cTransmission m_transmissionData;
		float fBrakeDeceleration;
		float fBrakeBias;
		unsigned char bABS;
		char pad[3];
		float fSteeringLock;
		float fTractionLoss;
		float fTractionBias;
		float fABS;
		float fSuspensionForceLevel;
		float fSuspensionDampingLevel;
		float fSuspUpperLimit;
		float fSuspLowerLimit;
		float fSuspBias;
		float fSuspAntiDiveMultiplier;
		float fCollisionDamageMultiplier;
		unsigned int uFlags;
		float fSeatOffsetDistance;
		int nMonetaryValue;
		eVehicleLightsSize bFrontLights;
		eVehicleLightsSize bRearLights;
	};

	VALIDATE_SIZE(tHandlingData, 0xDC);

	struct tBoatHandlingData {
		int m_dwVehicleId;
		float   m_fThrustY;
		float   m_fThrustZ;
		float   m_fThrustAppZ;
		float   m_fAqPlaneForce;
		float   m_fAqPlaneLimit;
		float   m_fAqPlaneOffset;
		float   m_fWaveAudioMult;
		float   m_fLookLRBehindCamHeight;
		CVector m_vMoveRes;
		CVector m_vTurnRes;
	};

	VALIDATE_SIZE(tBoatHandlingData, 0x3C);

	struct tBikeHandlingData {
		int m_dwVehicleId;
		float   m_fLeanFwdCOM;
		float   m_fLeanFwdForce;
		float   m_fLeanBakCOM;
		float   m_fLeanBakForce;
		float   m_fMaxLean;
		float   m_fFullAnimLean;
		float   m_fDesLean;
		float   m_fSpeedSteer;
		float   m_fSlipSteer;
		float   m_fNoPlayerCOMz;
		float   m_fWheelieAng;
		float   m_fStoppieAng;
		float   m_fWheelieSteer;
		float   m_fWheelieStabMult;
		float   m_fStoppieStabMult;
	};

	VALIDATE_SIZE(tBikeHandlingData, 0x40);

	struct tFlyingHandlingData {
		int m_dwVehicleId;
		float fThrust;
		float fThrustFallOff;
		float fYaw;
		float fYawStab;
		float fSideSlip;
		float fRoll;
		float fRollStab;
		float fPitch;
		float fPitchStab;
		float fFormLift;
		float fAttackLift;
		float fMoveRes;
		CVector vecTurnRes;
		CVector vecSpeedRes;
	};

	VALIDATE_SIZE(tFlyingHandlingData, 0x4C);
}

// GTA San Andreas
namespace Game_GTASA
{
	enum eVehicleLightsSize : unsigned char {
		LIGHTS_LONG,
		LIGHTS_SMALL,
		LIGHTS_BIG,
		LIGHTS_TALL
	};

	struct tHandlingData
	{
		int index;
		float         m_fMass; // 1.0 to 50000.0
		int field_8;
		float         m_fTurnMass;
		float         m_fDragMult;
		CVector       m_vecCentreOfMass; // x, y, z - 1.0 to 50000.0
		unsigned char m_nPercentSubmerged; // 10 to 120 (> 100% vehicle sinks)
		float         m_fBuoyancyConstant;
		float         m_fTractionMultiplier; // 0.5 to 2.0
		cTransmission m_transmissionData;
		float         m_fBrakeDeceleration; // 0.1 to 10.0
		float         m_fBrakeBias; // 0.0 > x > 1.0
		char          m_bABS; // 0/1
		char field_9D;
		char field_9E;
		char field_9F;
		float         m_fSteeringLock; // 10.0 to 40.0
		float         m_fTractionLoss;
		float         m_fTractionBias;
		float         m_fSuspensionForceLevel; // not [L/M/H]
		float         m_fSuspensionDampingLevel; // not [L/M/H]
		float         m_fSuspensionHighSpdComDamp; // often zero - 200.0 or more for bouncy vehicles
		float         m_fSuspensionUpperLimit;
		float         m_fSuspensionLowerLimit;
		float         m_fSuspensionBiasBetweenFrontAndRear;
		float         m_fSuspensionAntiDiveMultiplier;
		float         m_fCollisionDamageMultiplier; // 0.2 to 5.0
		unsigned int modelFlags;
		unsigned int handlingFlags;
		float              m_fSeatOffsetDistance; // // ped seat position offset towards centre of car
		unsigned int       m_nMonetaryValue; // 1 to 100000
		unsigned char m_nFrontLights;
		unsigned char m_nRearLights;
		unsigned char      m_nAnimGroup;
	};

	VALIDATE_SIZE(tHandlingData, 0xE0);

	struct tBoatHandlingData
	{
		int index;
		int thrustY;
		int thrustZ;
		int thrustAppZ;
		int aqPlaneForce;
		int aqPlaneLimit;
		int aqPlaneOffset;
		int waveAudioMult;
		int look_L_R_BehindCamHeight;
		CVector moveRes;
		CVector turnRes;
	};

	VALIDATE_SIZE(tBoatHandlingData, 0x3C);

	struct tFlyingHandlingData
	{
		int index;
		int thrust;
		int thrustFallOff;
		int yaw;
		int yawStab;
		int sideSlip;
		int roll;
		int rollStab;
		int pitch;
		int pitchStab;
		int formLift;
		int attackLift;
		int gearUpR;
		int gearDownL;
		int windMult;
		int moveRes;
		CVector turnRes;
		CVector speedRes;
	};

	VALIDATE_SIZE(tFlyingHandlingData, 0x58);

	struct tBikeHandlingData
	{
		int index;
		int leanFwdCOM;
		int leanFwdForce;
		int leanBakCOM;
		int leanBakForce;
		float maxLean;
		float fullAnimLean;
		int desLean;
		int speedSteer;
		int slipSteer;
		int noPlayerCOMz;
		float wheelieAng;
		float stoppieAng;
		int wheelieSteer;
		int wheelieStabMult;
		int stoppieStabMult;
	};

	VALIDATE_SIZE(tBikeHandlingData, 0x40);
}

// GTA IV
namespace Game_GTAIV
{
	struct tBikeHandlingData;
	struct tBoatHandlingData;
	struct tFlyingHandlingData;

	struct tHandlingData
	{
		char m_pszId[16];
		int m_fMass;
		int m_fDragMult;
		int field_18;
		int field_1C;
		CVector m_centreOfMass;
		int field_2C;
		int m_nPercentSubmerged;
		int field_34;
		int m_fDriveFront;
		int m_fDriveRear;
		int m_nDriveGears;
		int m_fDriveForce;
		int m_fDriveInertia;
		int field_4C;
		int m_fV;
		int field_54[8];
		int m_fBrakeForce;
		int m_fBrakeFront;
		int m_fBrakeRear;
		int m_fSteeringLock;
		int m_fTractionCurveMax;
		int field_88;
		int m_fTractionCurveMin;
		int field_90;
		int m_fTractionCurveLateral;
		int field_98;
		int m_fTractionCurveLongitudinal;
		int field_A0;
		int m_fTractionSpringDeltaMax;
		int field_A8;
		int m_fTractionFront;
		int m_fTractionRear;
		int m_fSuspensionForce;
		int m_fSuspensionCompDamp;
		int m_fSuspensionReboundDamp;
		int m_fSuspensionUpperLimit;
		int m_fSuspensionLowerLimit;
		int m_fSuspensionRaise;
		int m_fSuspensionFront;
		int m_fSuspensionrear;
		int m_fCollisionDamageMult;
		int m_fWeaponDamageMult;
		int m_fDeformationDamageMult;
		int m_fEngineDamageMult;
		int m_fSeatOffsetDist;
		int m_nMonetaryValue;
		int m_dwModelFlags;
		int m_dwHandlingFlags;
		char field_F4;
		char field_F5[3];
		tBikeHandlingData* m_pBikeHandling;
		tFlyingHandlingData* m_pFlyingHandling;
		tBoatHandlingData* m_pBoatHandling;
		int field_104;
		int field_108;
		int field_10C;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(tHandlingData, 0x110);

	struct tBoatHandlingData
	{
		int m_fBBoxFwd;
		int m_fBBoxBack;
		int m_fBboxSide;
		int m_fSampleTop;
		int m_fSampleBottom;
		int m_fAqPlaneForce;
		int m_fAqPlaneWfMult;
		int m_fAqPlaneWfCap;
		int m_fAqPlaneWfApp;
		int m_fRudderF;
		int m_fRudderOSet;
		int m_fWaveAudioMult;
		int m_fMoveResXY;
		int m_fMoveResZUp;
		int m_fMoveResZDown;
		int field_3C;
		CVector m_fTurnRes;
		int field_4C;
		int m_fLook_L_R_BehindCamHeight;
		int field_54;
		int field_58[32];
		int field_D8;
		int field_DC;
	};

	VALIDATE_SIZE(tBoatHandlingData, 0xE0);

	struct tFlyingHandlingData
	{
		int m_fThrust;
		int m_fThrustFallOff;
		int m_fThrustVec;
		int m_fYaw;
		int m_fYawStab;
		int m_fRoll;
		int m_fSideSlip;
		int m_fPitch;
		int m_fRollStab;
		int m_fFormLift;
		int m_fPitchStab;
		int m_fGearUpR;
		int m_fAttackLift;
		int m_fWindMult;
		int m_fGearDownL;
		int m_fMoveRes;
		CVector field_40;
		int field_4C;
		CVector field_50;
		int field_5C;
	};

	VALIDATE_SIZE(tFlyingHandlingData, 0x60);

	struct tBikeHandlingData
	{
		int m_fLeanFwdCOM;
		int m_fLeanFwdForce;
		int m_fLeanBakCOM;
		int m_fLeanBackForce;
		int m_fMaxLean;
		int m_fFullAnimLean;
		int field_18;
		int m_fDesLean;
		int m_fStickLean;
		int m_fBrakeStabil;
		int m_fInAirSteer;
		int m_fWheelieAng;
		int m_fStoppieAng;
		int m_fWheelieSteer;
		int m_fWheelieStabMult;
		int m_fStoppieStabMult;
	};

	VALIDATE_SIZE(tBikeHandlingData, 0x40);
}
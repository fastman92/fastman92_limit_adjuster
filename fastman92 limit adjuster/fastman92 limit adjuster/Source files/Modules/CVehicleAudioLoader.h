/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assertions.h>
#include "../Core/CLimitAdjusterModule.h"
#include "../GameStructures/Rockstar Games/CVehicle.h"
#include <IMG\IMGstructures.h>
#include "../Core/eGameVersion.h"
#include <string>
#include <vector>

struct tVehicleAudioSettings_base {};

namespace Game_GTA_old
{
	struct cVehicleParams
	{
		int field_0;
		char field_4;
		int field_8;
		int field_C;
		int field_10;
		unsigned int VehicleAudioID;
	};

	VALIDATE_SIZE(cVehicleParams, 0x18);

	struct tVehicleAudioSettings : tVehicleAudioSettings_base
	{
		int m_engineFarSample;
		int m_engineNearSample;
		int m_hornSample;
		int m_hornFrequency;
		int m_sirenSample;
		int m_sirenFrequency;
		int m_DoorSound;
	};

	VALIDATE_SIZE(tVehicleAudioSettings, 28);

	struct tVehicleAudioSettings_extended : public tVehicleAudioSettings
	{
		bool hasAirBrakes;
		bool usesRevWarning;
		// bool usesSiren;
		unsigned char sirenOption;
		bool usesPoliceRadio;
		bool usesTaxiRadio;
	};
}

namespace Game_GTASA
{
	struct cVehicleParams
	{
		int field_0;
		int field_4;
		char field_8;
		int field_C;
		CVehicle *pVehicle;
		int field_14;
		int VehicleAudioID;
		int field_1C;
		int16_t field_20;
		int16_t field_22;
		int field_24;
		char field_28;
		int field_2C;
		int field_30;
		int field_34;
		char field_38;
		char field_39;
		int field_3C;
		float field_40;
		int16_t field_44;
		char field_46;
		char field_47;
		int field_48;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(cVehicleParams, 0x4C);

// #define tVehicleAudioSettings_gap_fields_should_be_defined

	struct tVehicleAudioSettings : tVehicleAudioSettings_base
	{
		int8_t VehicleType;
	#ifdef tVehicleAudioSettings_gap_fields_should_be_defined
		char gap_1[1];
	#endif
		int16_t EngineOnSound;
		int16_t EngineOffSound;
		char field_6;
	#ifdef tVehicleAudioSettings_gap_fields_should_be_defined
		char gap_7[1];
	#endif
		float field_8;
		float field_C;
		int8_t HornTon;
	#ifdef tVehicleAudioSettings_gap_fields_should_be_defined
		char gap_11[3];
	#endif
		float HornHigh;
		int8_t DoorSound;
		int8_t field_19;
		int8_t RadioNum;
		int8_t RadioType;
		int8_t vehicleTypeForAudio;
	#ifdef tVehicleAudioSettings_gap_fields_should_be_defined
		char gap_1D[3];
	#endif
		float increaseTheVolume;
	};

	VALIDATE_SIZE(tVehicleAudioSettings, 0x24);

	struct tVehicleAudioSettings_sscanf
	{
		char modelName[IMG_FASTMAN92_GTASA_MAX_FILENAME_LENGTH + 1];
		int VehicleType;
		int EngineOnSound;
		int EngineOffSound;
		int field_6;
		float field_8;
		float field_C;
		int HornTon;
		float HornHigh;
		int DoorSound;
		int field_19;
		int RadioNum;
		int RadioType;
		int vehicleTypeForAudio;
		float increaseTheVolume;
	};
}

namespace Game_GTAIV
{
	#pragma pack(push, 1)
	struct tVehicleAudioSettingsBase
	{
		char structType;
		int field_1;
		int flags;
		char gap_9[1];	// zero
	};
	#pragma pack(pop)

	VALIDATE_SIZE(tVehicleAudioSettingsBase, 10);

	#pragma pack(push, 1)
	struct tVehicleAudioSettingsCarBike : public tVehicleAudioSettingsBase
	{
		int32_t floatAsInt_A;
		int32_t floatAsInt_E;
		uint32_t engineLowSound;
		uint32_t engineHighSound;
		uint32_t exhaustLowSound;
		uint32_t exhaustHighSound;
		uint32_t revsOffSound;
		float field_26;
		float field_2A;
		int32_t floatAsInt_2E;
		int32_t floatAsInt_32;
		float field_36;
		float field_3A;
		int floatAsInt_3E;
		int floatAsInt_42;
		float field_46;
		float field_4A;
		int32_t floatAsInt_4E;
		int32_t floatAsInt_52;
		float field_56;
		float field_5A;
		int32_t floatAsInt_5E;
		int32_t floatAsInt_62;
		int32_t floatAsInt_66;
		float field_6A;
		float field_6E;
		int32_t floatAsInt_72;
		int32_t floatAsInt_76;
		uint32_t engineWaveShape;
		int32_t floatAsInt_7E;
		uint32_t exhaustWaveShape;
		int32_t floatAsInt_86;
		int32_t floatAsInt_multiplier1200_8A;
		int32_t floatAsInt_multiplier1200_8E;
		uint32_t engineIdleLoopSound;
		uint32_t exhaustIdleLoopSound;
		int32_t floatAsInt_multiplier1200_9A;
		int32_t floatAsInt_multiplier1200_9E;
		int32_t transmissionSound;
		int32_t floatAsInt_A6;
		int32_t floatAsInt_AA;
		uint32_t sound_AE;
		int32_t floatAsInt_B2;
		int32_t floatAsInt_B6;
		uint32_t exhaustPopSound;
		uint32_t airIntakeSound;
		int32_t floatAsInt_multiplier1200_C2;
		int32_t floatAsInt_multiplier1200_C6;
		uint32_t dumpValveSound;
		uint32_t startSound;
		uint32_t hornSound;
		uint32_t openSound;
		uint32_t closeSound;
		uint32_t trunkOpenSound;
		uint32_t trunkCloseSound;
		float field_E6;
		uint32_t suspensionUpSound;
		uint32_t suspensionDownSound;
		float field_F2;
		float field_F6;
		uint32_t policeScannerManufacturerSound;
		uint32_t policeScannerModelSound;
		uint32_t policeScannerVehicleCategorySound;
		uint32_t gearTransmissionSound;
		int32_t floatAsInt_multiplier1200_10A;
		int32_t floatAsInt_multiplier1200_10E;
		int32_t floatAsInt_multiplier1200_112;
		int32_t floatAsInt_116;
		int field_11A;
		int32_t floatAsInt_11E;
		int32_t floatAsInt_122;
		int32_t floatAsInt_126;
		uint32_t jumpLandSound;
		int field_12E;
		int field_132;
		uint32_t ignitionSound;
		uint32_t engineShutDownSound;
		char field_13E;
		char field_13F;
		uint8_t field_140;
		uint8_t field_141;
		uint32_t indicatorVehicleOn;
		uint32_t indicatorVehicleOff;
		uint32_t engineCoolingFan;
		uint32_t handbrakeSound_14E;
		uint32_t sound_152;
		uint32_t sound_156;
		uint32_t handbrakeSound_15A;
		char field_15E;
		int8_t field_15F;
		uint8_t field_160;
		char gap_161[3];
	};
	#pragma pack(pop)

	VALIDATE_SIZE(tVehicleAudioSettingsCarBike, 0x164);

	#pragma pack(push, 1)
	struct tVehicleAudioSettingsHeli : public tVehicleAudioSettingsBase
	{
		uint32_t rotorSound;
		uint32_t rearRotorSound;
		uint32_t exHaustSound;
		uint32_t bankSound;
		uint32_t internalCabinToneSound;
		float field_1E;
		uint32_t bankAngleVolumeSound;
		uint32_t bankThrottleVolumeSound;
		uint32_t bankThrottlePitchCurveSound;
		uint32_t rotorThrottleVolumeSound;
		uint32_t rotorThrottlePitchCurveSound;
		uint32_t rotorThrottleGapSound;
		uint32_t rearRotorThrottleVolumeSound;
		uint32_t exhaustThrottleVolumeSound;
		uint32_t exhaustThrottlePitchCurveSound;
		uint16_t field_46;
		uint16_t field_48;
		int16_t floatAsInt_4A;
		uint16_t field_4C;
		uint16_t field_4E;
		int16_t floatAsInt_50;
		uint16_t field_52;
		uint16_t field_54;
		int16_t floatAsInt_56;
		float field_58;
		float field_5C;
		uint32_t throttleResonance1Sound;
		float field_64;
		float field_68;
		uint32_t throttleResonance2Sound;
		uint32_t bankingResonanceCurveSound;
		uint32_t rotorVolumeStartupCurveSound;
		uint32_t bladeVolumeStartupCurveSound;
		uint32_t rotorPitchStartupCurveSound;
		uint32_t rearRotorVolumeStartupCurveSound;
		uint32_t exhaustVolumeStartupCurveSound;
		uint32_t rotorGapStartupCurveSound;
		uint32_t shotStartSound;
		uint16_t field_90;
		uint16_t field_92;
		int16_t floatAsInt_94;
		uint16_t field_96;
		uint16_t field_98;
		int16_t floatAsInt_9A;
		uint32_t policeScannerManufacturerSound;
		uint32_t policeScannerModelSound;
		uint32_t policeScannerVehicleCategorySound;
		uint8_t field_A8;
		uint8_t field_A9;
		uint32_t doorOpenSound;
		uint32_t doorCloseSound;
		uint32_t doorLimitSound;
		uint32_t damageLoopSound;
		char padding_BA;
	};
	#pragma pack(pop)

	VALIDATE_SIZE(tVehicleAudioSettingsHeli, 0xBB);

	#pragma pack(push, 1)
	struct tVehicleAudioSettingsBoat : public tVehicleAudioSettingsBase
	{
		uint32_t engineLoopSound;
		uint32_t engineVolumeSound;
		uint32_t enginePitchSound_12;
		uint32_t engine2loopSound;
		uint32_t engine2volumeSound;
		uint32_t enginePitchSound_1E;
		uint32_t lowResonanceLoopSound;
		uint32_t resonanceVolumeSound;
		uint32_t enginePitchSound_2A;
		uint32_t idleLoopSound;
		uint32_t idleResonanceVolumeSound;
		uint32_t enginePitchSound_36;
		uint32_t waterTurbulanceSound;
		uint32_t waterTurbulanceVolumeSound;
		uint32_t field_42;
		float field_46;
		float field_4A;
		int32_t floatAsInt_4E;
		int32_t floatAsInt_52;
		float field_56;
		float field_5A;
		int32_t floatAsInt_5E;
		int32_t floatAsInt_62;
		float field_66;
		float field_6A;
		int32_t floatAsInt_6E;
		int32_t floatAsInt_72;
		float field_76;
		float field_7A;
		int32_t floatAsInt_7E;
		int32_t floatAsInt_82;
		int32_t floatAsInt_86;
		float field_8A;
		float field_8E;
		int32_t floatAsInt_92;
		int32_t floatAsInt_96;
		uint32_t linearRise_9A;
		int field_9E;
		uint32_t linearRise_A2;
		int field_A6;
		uint32_t policeScannerManufacturerSound;
		uint32_t policeScannerModelSound;
		uint32_t policeScannerVehicleCategorySound;
		uint8_t field_B6;
		char field_B7;
		uint32_t hornSound;
		uint32_t materialSound;
		uint32_t ignitionSound;
		uint32_t shutDownSound;
		char field_C8;
	};
	#pragma pack(pop)

	VALIDATE_SIZE(tVehicleAudioSettingsBoat, 0xC9);

	struct tVehicleAudioSettings : tVehicleAudioSettings_base
	{
		union
		{
			tVehicleAudioSettingsCarBike carBike;
			tVehicleAudioSettingsHeli heli;
			tVehicleAudioSettingsBoat boat;
		};
	};
};

class CVehicleAudioLoader;

typedef void (CVehicleAudioLoader::* tOneSettingInLineAudioConfigFileFunction)(const char* line, bool bModelMustExist);

class CVehicleAudioLoader : public CLimitAdjusterModule
{
private:	
	// Vector of vehicle audio entries
	union {
		void* generic;
		std::vector<Game_GTA_old::tVehicleAudioSettings_extended>* gta_old;	// old games like GTA III and GTA VC
		std::vector<Game_GTASA::tVehicleAudioSettings>* gta_sa;	// GTA SA
		std::vector<Game_GTAIV::tVehicleAudioSettings>* gta_iv;	// GTA IV, GTA EFLC
	} ms_VehicleAudioEntries;

	bool ms_bVehicleAudioLoaderEnabled;
	bool ms_bEnableDumpingDefaultSettings;
	
	std::string ms_AudioSettingsPath;

	// Checks if game version is GTA SA
	static bool IsGameVersionUsingOldFormat(Game::eGameVersion gameVersion);

	// Set vehicle audio settings
	void SetVehicleAudioSettings_GTA_SA(const Game_GTASA::tVehicleAudioSettings_sscanf* pScanfSettings);
	
public:
	// Loads vehicle audio settings for GTA SA
	void LoadVehicleAudioSettings_configFile(const char* filename, bool bModelMustExist, tOneSettingInLineAudioConfigFileFunction func);

	// Loads vehicle audio settings for GTA old
	void LoadVehicleAudioSettings_GTA_old(const char* line, bool bModelMustExist);

	// Loads vehicle audio settings for GTA SA
	void LoadVehicleAudioSettings_GTA_SA(const char* line, bool bModelMustExist);

#if IS_PLATFORM_WIN_X86
	// Loads vehicle audio settings for GTA IV or EFLC
	void LoadVehicleAudioSettings_GTA_IV_EFLC(const char* filename, bool bModelMustExist);
#endif

	// Loads vehicle audio settings
	void LoadVehicleAudioSettings();

	// Does something with pointer the vehicle audio settings
	template<typename tClassWithFunction, typename Tresult> Tresult TouchTheVehicleAudioSettings(Tresult defaultReturn);

	// Unloads vehicle audio settings
	void UnloadVehicleAudioSettings();

	// Returns pointer to vehicle audio settings by ID
	tVehicleAudioSettings_base* GetVehicleAudioSettingsByID(int vehicleAudioID);

	// Enables/disable vehicle audio loader
	void EnableVehicleAudioLoader(bool bEnable);

	// Enables/disables dumping default vehicle audio settings
	void EnableDumpingDefaultSettings(bool bEnable);

	// Applies vehicle audio loader
	void ApplyVehicleAudioLoaderIfEnabled();

	// Sets vehicle audio settings path
	void SetVehicleAudioSettingsPath(const char* path);

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();
};

extern CVehicleAudioLoader g_vehicleAudioLoader;
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CVehicleAudioLoader.h"

#include "CHashStringLoader.h"
#include "FileIDlimit.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/CFileMgr.h"
#include "../GameStructures/Rockstar Games/eModelID.h"
#include "../GameStructures/Rockstar Games/functions.h"

#include <Array\countof.h>

using namespace Game;

#pragma warning(disable: 4244)

CVehicleAudioLoader g_vehicleAudioLoader;

void DoubleToStr(double num, char* out)
{
	if ((int)num == num)
		sprintf(out, "%g.0", num);
	else
		sprintf(out, "%g", num);
}

std::string DoubleToStr(double num)
{
	char buffer[64];

	if ((int)num == num)
		sprintf(buffer, "%g.0", num);
	else
		sprintf(buffer, "%g", num);

	return std::string(buffer);
}

// Checks if memory holds zeros
bool CompareMemWithZeroes(const void* ptr, size_t numberOfBytes)
{
	char* cPtr = (char*)ptr;

	for (unsigned int i = 0; i < numberOfBytes; i++)
		if (cPtr[i] != 0)
			return false;

	return true;
}

// Checks if game version is GTA SA
bool CVehicleAudioLoader::IsGameVersionUsingOldFormat(eGameVersion gameVersion)
{
	return CGameVersion::IsAny_GTA_VC(gameVersion);
}

// Set vehicle audio settings
void CVehicleAudioLoader::SetVehicleAudioSettings_GTA_SA(const Game_GTASA::tVehicleAudioSettings_sscanf* pScanfSettings)
{
	using namespace Game_GTASA;

	int modelID;

	CBaseModelInfo_generic* pModelInfo = CModelInfo::GetModelInfo(pScanfSettings->modelName, &modelID);

	if (!pModelInfo)
	{
		printf_MessageBox("gtasa_vehicleAudioSettings.cfg: model with name %s does not exist.", pScanfSettings->modelName);
		return;
	}

	CBaseModelInfo_extension* pModelExtInfo = g_fileIDlimits.AllocateModelInfoExtensionItemIfNeccessary(modelID);

	int32_t vehicleAudioID = this->ms_VehicleAudioEntries.gta_sa->size();

	pModelExtInfo->VehicleAudioID = vehicleAudioID;

	tVehicleAudioSettings_DefinitiveEdition audioSettings;
	memset(&audioSettings, NULL, sizeof(audioSettings));

	audioSettings.VehicleAudioType = pScanfSettings->VehicleAudioType;
	audioSettings.PlayerBank = pScanfSettings->PlayerBank;
	audioSettings.DummyBank = pScanfSettings->DummyBank;
	audioSettings.BassSetting = pScanfSettings->BassSetting;
	audioSettings.BassFactor = pScanfSettings->BassFactor;
	audioSettings.EnginePitch = pScanfSettings->EnginePitch;
	audioSettings.HornType = pScanfSettings->HornType;
	audioSettings.HornPitch = pScanfSettings->HornPitch;
	audioSettings.DoorType = pScanfSettings->DoorType;
	audioSettings.EngineUpgrade = pScanfSettings->EngineUpgrade;
	audioSettings.RadioStation = pScanfSettings->RadioStation;
	audioSettings.RadioType = pScanfSettings->RadioType;
	audioSettings.VehicleAudioTypeForName = pScanfSettings->VehicleAudioTypeForName;
	audioSettings.EngineVolumeOffset = pScanfSettings->EngineVolumeOffset;
	audioSettings.UnknownValueAddedInGTA_DE = 0;

	this->ms_VehicleAudioEntries.gta_sa->push_back(audioSettings);

	// Debug code
	#if FALSE
	{
		const tVehicleAudioSettings* pDefaultData = (const tVehicleAudioSettings*)0x0860AF0 + modelID - 400;

		if (memcmp(pDefaultData, &audioSettings, sizeof(tVehicleAudioSettings)))
		{
			printf_MessageBox("Wrong audio data for model ID: %d default: 0x%X new: 0x%X",
				modelID,
				pDefaultData,
				&audioSettings
				);
		}
	}
	#endif
}

// Does something with pointer the vehicle audio settings
template<typename tClassWithFunction, typename Tresult>
Tresult CVehicleAudioLoader::TouchTheVehicleAudioSettings(Tresult defaultReturn)
{
	MAKE_VAR_GAME_VERSION();

	if (this->IsGameVersionUsingOldFormat(gameVersion))
		return tClassWithFunction::doStuff(this->ms_VehicleAudioEntries.gta_old);
	else if (CGameVersion::IsAny_GTA_SA(gameVersion))
		return tClassWithFunction::doStuff(this->ms_VehicleAudioEntries.gta_sa);
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
		return tClassWithFunction::doStuff(this->ms_VehicleAudioEntries.gta_iv);
	else
		return defaultReturn;
}

class ClearVehicleAudioSettings
{
public:
	template <class T> static bool doStuff(T* pVehicleAudioSettings)
 	{
		pVehicleAudioSettings->clear();
		return true;
	}
};

// Unloads vehicle audio settings
void CVehicleAudioLoader::UnloadVehicleAudioSettings()
{
	int countOfModels = g_fileIDlimits.GetFileIDcurrentLimit(GENERAL_FILE_TYPE_MODEL_ARCHIVE);

	for (int i = 0; i < countOfModels; i++)
	{
		CBaseModelInfo_extension* pExtension = g_fileIDlimits.CModelInfo__ms_modelInfoExtensionPtrs[i];

		if (pExtension)
			pExtension->VehicleAudioID = UNDEFINED_AUDIO_ID;
	}

	this->TouchTheVehicleAudioSettings<ClearVehicleAudioSettings, bool>(true);
}


struct tModelIDnameDef
{
	int ID;
	const char* name;
};

// Returns audio settings for vehicle
uint32_t __cdecl GetAudioSettingsIDByVehicleModelID(int modelID)
{
	// return modelID - 130;

	CBaseModelInfo_extension* pModelInfoExt = g_fileIDlimits.CModelInfo__ms_modelInfoExtensionPtrs[modelID];

	if (pModelInfoExt)
		return pModelInfoExt->VehicleAudioID;
	else
		return UNDEFINED_AUDIO_ID;
}

// Returns audio settings for vehicle
tVehicleAudioSettings_base* __cdecl GetAudioSettingsForVehicleModelID(int modelID)
{
	CBaseModelInfo_extension* pModelInfoExt = g_fileIDlimits.CModelInfo__ms_modelInfoExtensionPtrs[modelID];

	if (pModelInfoExt && pModelInfoExt->VehicleAudioID != UNDEFINED_AUDIO_ID)
		return g_vehicleAudioLoader
		.GetVehicleAudioSettingsByID
		(pModelInfoExt->VehicleAudioID);
	else
		return NULL;
}

// Returns audio settings for vehicle
tVehicleAudioSettings_base* __cdecl GetAudioSettingsByAudioID(int audioID)
{
	// return (tVehicleAudioSettings_base*)(0x6AD1A0 + 28 * audioID);

	return g_vehicleAudioLoader.GetVehicleAudioSettingsByID(audioID);
}
/*
namespace details
{
	class cGetVehicleAudioSettingsByID
	{
	public:
		template <class T> static tVehicleAudioSettings_base* doStuff(T* pVehicleAudioSettings)
		{
			return return &(*pVehicleAudioSettings)[vehicleAudioID];
		}
	};
}
*/

// Returns pointer to vehicle audio settings by ID
tVehicleAudioSettings_base* CVehicleAudioLoader::GetVehicleAudioSettingsByID(int vehicleAudioID)
{
	MAKE_VAR_GAME_VERSION();

	if (this->IsGameVersionUsingOldFormat(gameVersion))
		return &(*this->ms_VehicleAudioEntries.gta_old)[vehicleAudioID];
	else if(CGameVersion::IsAny_GTA_SA(gameVersion))
		return &(*this->ms_VehicleAudioEntries.gta_sa)[vehicleAudioID];
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
		return &(*this->ms_VehicleAudioEntries.gta_iv)[vehicleAudioID];
	else
		return NULL;
}

// Enables/disabled vehicle audio loader
void CVehicleAudioLoader::EnableVehicleAudioLoader(bool bEnable)
{
	this->ms_bVehicleAudioLoaderEnabled = bEnable;
		
	if (bEnable)
	{
		g_fileIDlimits.EnableModelInfoExtensionArray();
		this->SetVehicleAudioSettingsPath(NULL);
	}
}

// Enables/disables dumping default vehicle audio settings
void CVehicleAudioLoader::EnableDumpingDefaultSettings(bool bEnable)
{
	this->ms_bEnableDumpingDefaultSettings = bEnable;
}

////////////////////////////////////////
extern "C"
{
	// Runs the loading of audio settings
	void run_LoadVehicleAudioSettings()
	{
		g_vehicleAudioLoader.LoadVehicleAudioSettings();
	}
}

// Version specific stuff
namespace Game_GTA_old
{
	bool* CTheScripts__bPlayerHasMetDebbieHarry = 0;

	class CVehicle_audioExt : public CVehicle_generic
	{
	public:
		bool UsesSiren()
		{			
			return ((tVehicleAudioSettings_extended*)GetAudioSettingsForVehicleModelID
			(
				this->GetModelID()
			))->sirenOption != 0;
		}
	};

	class cMusicManager_audioExt
	{
	public:
		bool UsesPoliceRadio(CVehicle_generic* pVehicle)
		{
			return ((tVehicleAudioSettings_extended*)GetAudioSettingsForVehicleModelID
				(
					pVehicle->GetModelID()
				))->usesPoliceRadio;
		}

		bool UsesTaxiRadio(CVehicle_generic* pVehicle)
		{
			return *CTheScripts__bPlayerHasMetDebbieHarry &&
				((tVehicleAudioSettings_extended*)GetAudioSettingsForVehicleModelID
			(
				pVehicle->GetModelID()
			))->usesTaxiRadio;
		}
	};

	class cAudioManager_audioExt
	{
	public:
		bool HasAirBrakes(unsigned int audioID)
		{
			return ((tVehicleAudioSettings_extended*)GetAudioSettingsByAudioID
				(
					audioID
				))->hasAirBrakes;
		}

		bool UsesReverseWarning(unsigned int audioID)
		{
			return ((tVehicleAudioSettings_extended*)GetAudioSettingsByAudioID
				(
					audioID
				))->usesRevWarning;
		}
	};
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTAVC
{
	using namespace Game_GTA_old;

	uintptr_t Address_cAudioManager__ProcessVehicle_setAudioID_pointToReturn = 0;

	// stack pointer: -0x34
	NAKED void patch_cAudioManager__ProcessVehicle_setAudioID()
	{
		__asm
		{
			movzx   eax, word ptr[ebp + 5Ch];	// model ID

			push eax;
			call GetAudioSettingsIDByVehicleModelID;
			add esp, 4;
			
			cmp eax, UNDEFINED_AUDIO_ID;
			je soundIsNotDefined;

			mov[esp + 34h - 0x28 + cVehicleParams::VehicleAudioID], eax;

			mov     ecx, [esp + 34h - 0x28 + cVehicleParams::field_C];
			jmp Address_cAudioManager__ProcessVehicle_setAudioID_pointToReturn;

		soundIsNotDefined:
			fcompp;
			add     esp, 28h;
			fstp    st;
			pop     ebp;
			pop     esi;
			pop     ebx;
			retn 4;
		}
	}

	////////////

	// original: movzx   eax, byte ptr _ZL16aVehicleSettings.m_DoorSound[edx*4]
	uintptr_t Address_cAudioManager__ProcessVehicleOneShots_0_pointToReturn = 0;

	NAKED void patch_cAudioManager__ProcessVehicleOneShots_0()
	{
		__asm
		{
			push ecx;
			call GetAudioSettingsByAudioID;
			add esp, 4;

			add     bl, 75h;

			movzx   eax, byte ptr[eax + tVehicleAudioSettings::m_DoorSound];

			jmp Address_cAudioManager__ProcessVehicleOneShots_0_pointToReturn;
		}
	}

	// movzx   eax, byte ptr _ZL16aVehicleSettings.m_DoorSound[edx*4]
	uintptr_t Address_cAudioManager__ProcessVehicleOneShots_1_pointToReturn = 0;

	NAKED void patch_cAudioManager__ProcessVehicleOneShots_1()
	{
		__asm
		{
			push ecx;
			call GetAudioSettingsByAudioID;
			add esp, 4;

			add     bl, 7Ah;

			movzx   eax, byte ptr[eax + tVehicleAudioSettings::m_DoorSound];

			jmp Address_cAudioManager__ProcessVehicleOneShots_1_pointToReturn;
		}
	}

	// original: mov     eax, _ZL16aVehicleSettings.m_sirenSample[edi*4]
	uintptr_t Address_cAudioManager__ProcessVehicleSirenOrAlarm_0_pointToReturn = 0;

	NAKED void patch_cAudioManager__ProcessVehicleSirenOrAlarm_0()
	{
		__asm
		{
			push ecx;
			call GetAudioSettingsByAudioID;
			add esp, 4;

			mov   eax, [eax + tVehicleAudioSettings::m_sirenSample];

			jmp Address_cAudioManager__ProcessVehicleSirenOrAlarm_0_pointToReturn;
		}
	}

	// original: mov     eax, _ZL16aVehicleSettings.m_sirenFrequency[ebp*4]
	uintptr_t Address_cAudioManager__ProcessVehicleSirenOrAlarm_1_pointToReturn = 0;

	NAKED void patch_cAudioManager__ProcessVehicleSirenOrAlarm_1()
	{
		__asm
		{
			push edx;
			call GetAudioSettingsByAudioID;
			add esp, 4;

			mov   eax, [eax + tVehicleAudioSettings::m_sirenFrequency];

			jmp Address_cAudioManager__ProcessVehicleSirenOrAlarm_1_pointToReturn;
		}
	}

	// original: mov     eax, _ZL16aVehicleSettings.m_hornSample[edi*4]
	uintptr_t Address_cAudioManager__ProcessVehicleSirenOrAlarm_2_pointToReturn = 0;

	NAKED void patch_cAudioManager__ProcessVehicleSirenOrAlarm_2()
	{
		__asm
		{
			push ecx;
			call GetAudioSettingsByAudioID;
			add esp, 4;

			mov   eax, [eax + tVehicleAudioSettings::m_hornSample];

			jmp Address_cAudioManager__ProcessVehicleSirenOrAlarm_2_pointToReturn;
		}
	}

	// original: mov     eax, _ZL16aVehicleSettings.m_hornFrequency[ecx*4]
	uintptr_t Address_cAudioManager__ProcessVehicleSirenOrAlarm_3_pointToReturn = 0;

	NAKED void patch_cAudioManager__ProcessVehicleSirenOrAlarm_3()
	{
		__asm
		{
			push edx;
			call GetAudioSettingsByAudioID;
			add esp, 4;

			mov   eax, [eax + tVehicleAudioSettings::m_hornFrequency];

			jmp Address_cAudioManager__ProcessVehicleSirenOrAlarm_3_pointToReturn;
		}
	}

	// original: mov     eax, _ZL16aVehicleSettings.m_hornSample[esi*4]
	uintptr_t Address_cAudioManager__ProcessVehicleHorn_0_pointToReturn = 0;

	NAKED void patch_cAudioManager__ProcessVehicleHorn_0()
	{
		__asm
		{
			push ecx;
			call GetAudioSettingsByAudioID;
			add esp, 4;

			mov   eax, [eax + tVehicleAudioSettings::m_hornSample];

			jmp Address_cAudioManager__ProcessVehicleHorn_0_pointToReturn;
		}
	}

	// original: mov     eax, _ZL16aVehicleSettings.m_hornFrequency[ecx*4]
	uintptr_t Address_cAudioManager__ProcessVehicleHorn_1_pointToReturn = 0;

	NAKED void patch_cAudioManager__ProcessVehicleHorn_1()
	{
		__asm
		{
			push edx;
			call GetAudioSettingsByAudioID;
			add esp, 4;

			mov   eax, [eax + tVehicleAudioSettings::m_hornFrequency];

			jmp Address_cAudioManager__ProcessVehicleHorn_1_pointToReturn;
		}
	}

	// original: mov     al, byte ptr _ZL16aVehicleSettings.m_engineNearSample[ebx*4]
	uintptr_t Address_cAudioManager__ProcessPlayersVehicleEngine_0_pointToReturn = 0;

	NAKED void patch_cAudioManager__ProcessPlayersVehicleEngine_0()
	{
		__asm
		{
			push eax;
			call GetAudioSettingsByAudioID;
			add esp, 4;

			xor     edx, edx;

			mov   al, [eax + tVehicleAudioSettings::m_engineNearSample];

			jmp Address_cAudioManager__ProcessPlayersVehicleEngine_0_pointToReturn;
		}
	}

	// original: movzx   eax, byte ptr _ZL16aVehicleSettings.m_engineNearSample[ebp*4]
	uintptr_t Address_cAudioManager__ProcessVehicleEngine_0_pointToReturn = 0;

	NAKED void patch_cAudioManager__ProcessVehicleEngine_0()
	{
		__asm
		{
			push esi;
			call GetAudioSettingsByAudioID;
			add esp, 4;

			movzx   eax, byte ptr[eax + tVehicleAudioSettings::m_engineNearSample];

			jmp Address_cAudioManager__ProcessVehicleEngine_0_pointToReturn;
		}
	}

	// original: mov     eax, _ZL16aVehicleSettings.m_engineFarSample[edx*4]
	uintptr_t Address_cAudioManager__ProcessVehicleEngine_1_pointToReturn = 0;

	NAKED void patch_cAudioManager__ProcessVehicleEngine_1()
	{
		__asm
		{
			push ecx;
			call GetAudioSettingsByAudioID;
			add esp, 4;

			mov eax, [eax + tVehicleAudioSettings::m_engineFarSample];

			jmp Address_cAudioManager__ProcessVehicleEngine_1_pointToReturn;
		}
	}

	// original: movzx   eax, byte ptr _ZL16aVehicleSettings.m_engineNearSample[ebp*4]
	uintptr_t Address_cAudioManager__ProcessVehicleEngine_2_pointToReturn = 0;

	NAKED void patch_cAudioManager__ProcessVehicleEngine_2()
	{
		__asm
		{
			push esi;
			call GetAudioSettingsByAudioID;
			add esp, 4;

			movzx   eax, byte ptr[eax + tVehicleAudioSettings::m_engineNearSample];

			jmp Address_cAudioManager__ProcessVehicleEngine_2_pointToReturn;
		}
	}

	// mov     eax, _ZL16aVehicleSettings.m_engineFarSample[edx*4]
	uintptr_t Address_cAudioManager__ProcessVehicleEngine_3_pointToReturn = 0;

	NAKED void patch_cAudioManager__ProcessVehicleEngine_3()
	{
		__asm
		{
			push ecx;
			call GetAudioSettingsByAudioID;
			add esp, 4;

			mov eax, [eax + tVehicleAudioSettings::m_engineFarSample];

			jmp Address_cAudioManager__ProcessVehicleEngine_3_pointToReturn;
		}
	}

	using namespace Game_GTA_old;

	NAKED void patch_cMusicManager__GetCarTuning_5FA48C()
	{
		__asm
		{
			push ebx;
			mov ecx, [esp + 0Ch - 8];
			call cMusicManager_audioExt::UsesPoliceRadio;

			test al, al;
			jnz usingPoliceRadio;

			push ebx;
			mov ecx, [esp + 0Ch - 8];
			call cMusicManager_audioExt::UsesTaxiRadio;

			test al, al;
			jnz usingTaxiRadio;

			push 0x5FA511;
			retn;

		usingPoliceRadio:
			push 0x5FA4D9;
			retn;

		usingTaxiRadio:
			push 0x5FA50A;
			retn;
		}
	}

	NAKED void patch_cMusicManager__ServiceGameMode_5FB722()
	{
		__asm
		{
			push esi;
			mov ecx, ebp;
			call cMusicManager_audioExt::UsesPoliceRadio;

			test al, al;
			jnz usingPoliceRadio;

			push esi;
			mov ecx, ebp;
			call cMusicManager_audioExt::UsesTaxiRadio;

			test al, al;
			jnz usingTaxiRadio;

			push 0x5FB78D;
			retn;

		usingPoliceRadio:
			push 0x5FB7CC;
			retn;

		usingTaxiRadio:
			push 0x5FB7CC;
			retn;
		}
	}

	NAKED void patch_cMusicManager__ServiceGameMode_5FB7EF()
	{
		__asm
		{
			push esi;
			mov ecx, ebp;
			call cMusicManager_audioExt::UsesPoliceRadio;

			test al, al;
			jnz usingIt;

			push esi;
			mov ecx, ebp;
			call cMusicManager_audioExt::UsesTaxiRadio;

			push 0x5FB856;
			retn;

		usingIt:
			push 0x5FB88F;
			retn;
		}
	}

	NAKED void patch_cMusicManager__ServiceGameMode_5FB972()
	{
		__asm
		{
		}
	}

	NAKED void patch_cAudioManager__ProcessVehicle_5F56CB()
	{
		__asm
		{
			push ecx;
			mov ecx, ebx;
			call cAudioManager_audioExt::UsesReverseWarning;

			push 0x5F56F4;
			retn;
		}
	}

	NAKED void patch_cAudioManager__ProcessVehicle_5F5708()
	{
		__asm
		{
			push edx;
			mov ecx, ebx;
			call cAudioManager_audioExt::HasAirBrakes;

			push 0x5F5722;
			retn;
		}
	}
}
#endif

namespace Game_GTAIII
{
	const char* aDefaultListOfVehicleModelNames[] =
	{
		"landstal",	// 90
		"idaho",	// 91
		"stinger",	// 92
		"linerun",	// 93
		"peren",	// 94
		"sentinel",	// 95
		"patriot",	// 96
		"firetruk",	// 97
		"trash",	// 98
		"stretch",	// 99
		"manana",	// 100
		"infernus",	// 101
		"blista",	// 102
		"pony",	// 103
		"mule",	// 104
		"cheetah",	// 105
		"ambulan",	// 106
		"fbicar",	// 107
		"moonbeam",	// 108
		"esperant",	// 109
		"taxi",	// 110
		"kuruma",	// 111
		"bobcat",	// 112
		"mrwhoop",	// 113
		"bfinject",	// 114
		"corpse",	// 115
		"police",	// 116
		"enforcer",	// 117
		"securica",	// 118
		"banshee",	// 119
		"predator",	// 120
		"bus",	// 121
		"rhino",	// 122
		"barracks",	// 123
		"train",	// 124
		"chopper",	// 125
		"dodo",	// 126
		"coach",	// 127
		"cabbie",	// 128
		"stallion",	// 129
		"rumpo",	// 130
		"rcbandit",	// 131
		"bellyup",	// 132
		"mrwongs",	// 133
		"mafia",	// 134
		"yardie",	// 135
		"yakuza",	// 136
		"diablos",	// 137
		"columb",	// 138
		"hoods",	// 139
		"airtrain",	// 140
		"deaddodo",	// 141
		"speeder",	// 142
		"reefer",	// 143
		"panlant",	// 144
		"flatbed",	// 145
		"yankee",	// 146
		"escape",	// 147
		"borgnine",	// 148
		"toyz",	// 149
		"ghost",	// 150
	};
}

namespace Game_GTAVC
{
	const char* aDefaultListOfVehicleModelNames[] =
	{
		"landstal",	// 130
		"idaho",	// 131
		"stinger",	// 132
		"linerun",	// 133
		"peren",	// 134
		"sentinel",	// 135
		"rio",	// 136
		"firetruk",	// 137
		"trash",	// 138
		"stretch",	// 139
		"manana",	// 140
		"infernus",	// 141
		"voodoo",	// 142
		"pony",	// 143
		"mule",	// 144
		"cheetah",	// 145
		"ambulan",	// 146
		"fbicar",	// 147
		"moonbeam",	// 148
		"esperant",	// 149
		"taxi",	// 150
		"washing",	// 151
		"bobcat",	// 152
		"mrwhoop",	// 153
		"bfinject",	// 154
		"hunter",	// 155
		"police",	// 156
		"enforcer",	// 157
		"securica",	// 158
		"banshee",	// 159
		"predator",	// 160
		"bus",	// 161
		"rhino",	// 162
		"barracks",	// 163
		"cuban",	// 164
		"chopper",	// 165
		"angel",	// 166
		"coach",	// 167
		"cabbie",	// 168
		"stallion",	// 169
		"rumpo",	// 170
		"rcbandit",	// 171
		"romero",	// 172
		"packer",	// 173
		"sentxs",	// 174
		"admiral",	// 175
		"squalo",	// 176
		"seaspar",	// 177
		"pizzaboy",	// 178
		"gangbur",	// 179
		"airtrain",	// 180
		"deaddodo",	// 181
		"speeder",	// 182
		"reefer",	// 183
		"tropic",	// 184
		"flatbed",	// 185
		"yankee",	// 186
		"caddy",	// 187
		"zebra",	// 188
		"topfun",	// 189
		"skimmer",	// 190
		"pcj600",	// 191
		"faggio",	// 192
		"freeway",	// 193
		"rcbaron",	// 194
		"rcraider",	// 195
		"glendale",	// 196
		"oceanic",	// 197
		"sanchez",	// 198
		"sparrow",	// 199
		"patriot",	// 200
		"lovefist",	// 201
		"coastg",	// 202
		"dinghy",	// 203
		"hermes",	// 204
		"sabre",	// 205
		"sabretur",	// 206
		"pheonix",	// 207
		"walton",	// 208
		"regina",	// 209
		"comet",	// 210
		"deluxo",	// 211
		"burrito",	// 212
		"spand",	// 213
		"marquis",	// 214
		"baggage",	// 215
		"kaufman",	// 216
		"maverick",	// 217
		"vcnmav",	// 218
		"rancher",	// 219
		"fbiranch",	// 220
		"virgo",	// 221
		"greenwoo",	// 222
		"jetmax",	// 223
		"hotring",	// 224
		"sandking",	// 225
		"blistac",	// 226
		"polmav",	// 227
		"boxville",	// 228
		"benson",	// 229
		"mesa",	// 230
		"rcgoblin",	// 231
		"hotrina",	// 232
		"hotrinb",	// 233
		"bloodra",	// 234
		"bloodrb",	// 235
		"vicechee",	// 236
	};
}

namespace Game_GTA_old
{
	typedef bool(*tAudioIDcheck)(unsigned int audioID);
	typedef bool(*tModelIDcheck)(int modelID);

	tAudioIDcheck HasAirBrakes = 0;
	tAudioIDcheck UsesReverseWarning = 0;
	tModelIDcheck UsesSiren = 0;
	tAudioIDcheck UsesSirenSwitching = 0;
	tModelIDcheck UsesPoliceRadio = 0;
	tModelIDcheck UsesTaxiRadio = 0;

	int firstModelID;

	// Dumps default audio settings
	void DumpDefaultAudioSettings()
	{
		MAKE_VAR_GAME_VERSION();
		CGenericLogStorage::SaveTextLn("Default audio settings:");

		typedef bool(*tAudioIDcheck)(int audioID);
		typedef bool(*tModelIDcheck)(int modelID);
		
		const char** pListOfVehicleModelNames = 0;
		const tVehicleAudioSettings* pVehicleAudioSettings = 0;
		unsigned int countOfVehicles = 0;
		
		if(gameVersion == GAME_VERSION_GTA_III_1_0_WIN_X86)
		{
			using namespace Game_GTAIII;
			firstModelID = 130;
			pVehicleAudioSettings = (const tVehicleAudioSettings*)g_mCalc.GetCurrentVAbyPreferedVA(0x606204);

			pListOfVehicleModelNames = aDefaultListOfVehicleModelNames;
			countOfVehicles = _countof(aDefaultListOfVehicleModelNames);

		}
		else if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
		{
			using namespace Game_GTAVC;

			firstModelID = 130;
			pVehicleAudioSettings = (const tVehicleAudioSettings*)g_mCalc.GetCurrentVAbyPreferedVA(0x6AD1A0);

			pListOfVehicleModelNames = aDefaultListOfVehicleModelNames;
			countOfVehicles = _countof(aDefaultListOfVehicleModelNames);

			HasAirBrakes = [](unsigned int audioID)
			{
				switch (audioID)
				{
				case 3u:
				case 7u:
				case 8u:
				case 31u:
				case 33u:
				case 37u:
				case 43u:
				case 55u:
					return true;
				default:
					return false;
				}
			};

			UsesReverseWarning = [](unsigned int audioID)
			{
				return audioID == 3
					|| audioID - 7 <= 1
					|| audioID == 31
					|| audioID == 37
					|| audioID == 43
					|| audioID == 55;
			};

			UsesSiren = [](int modelID)->bool
			{
				if (modelID > MODEL_ENFORCER)
				{
					if (modelID == MODEL_FBIRANCH || modelID == MODEL_VICECHEE || modelID == MODEL_PREDATOR)
						return 1;
				}
				else
				{
					if (modelID >= MODEL_POLICE)
						return 1;
					if (modelID > MODEL_FBICAR)
					{
						if (modelID == MODEL_MRWHOOP)
							return 1;
					}
					else if (modelID >= MODEL_AMBULAN || modelID == MODEL_FIRETRUK)
					{
						return 1;
					}
				}
				return 0;
			};

			UsesSirenSwitching = [](unsigned int audioID)->bool
			{
				if (audioID == 7 || audioID == 23)
					return false;
				else
					return UsesSiren(firstModelID + audioID);
			};

			UsesPoliceRadio = [](int modelID)->bool
			{
				if (modelID > MODEL_BARRACKS)
				{
					if (modelID == MODEL_VCNMAV || modelID == MODEL_POLMAV || modelID == MODEL_COASTG)
						return 1;

					return UsesSiren(modelID) != 0;
				}
				if (modelID >= MODEL_RHINO)
					return 1;

				if (modelID != MODEL_MRWHOOP && modelID != MODEL_HUNTER)
					return UsesSiren(modelID) != 0;

				return 0;
			};

			UsesTaxiRadio = [](int modelID)
			{
				return modelID == MODEL_KAUFMAN;
			};
		}
		
		for (unsigned int audioID = 0; audioID < countOfVehicles; audioID++)
		{
			const tVehicleAudioSettings* pSettings = pVehicleAudioSettings + audioID;
			int modelID = audioID + firstModelID;
			unsigned int sirenOption;
			
			if (UsesSirenSwitching(audioID))
				sirenOption = 2;
			else if (UsesSiren(modelID))
				sirenOption = 1;
			else
				sirenOption = 0;

			CGenericLogStorage::SaveFormattedTextLn(
				"%-43s %-6d %-6d %-12d %-9d %-13d %-10d %-11d %-13d %-12d %-10d %-16d %d",

				//audioID,
				pListOfVehicleModelNames[audioID],


				pSettings->m_engineFarSample,
				pSettings->m_engineNearSample,
				pSettings->m_hornSample,
				pSettings->m_hornFrequency,
				pSettings->m_sirenSample,
				pSettings->m_sirenFrequency,
				pSettings->m_DoorSound,

				HasAirBrakes(audioID),
				UsesReverseWarning(audioID),
				sirenOption,
				UsesPoliceRadio(modelID),

				UsesTaxiRadio(modelID)
				);
		}

	CGenericLogStorage::WriteLineSeparator();
	}
}

namespace Game_GTASA
{
	const char* aDefaultListOfVehicleModelNames[] =
	{
		"landstal",	// 400
		"bravura",	// 401
		"buffalo",	// 402
		"linerun",	// 403
		"peren",	// 404
		"sentinel",	// 405
		"dumper",	// 406
		"firetruk",	// 407
		"trash",	// 408
		"stretch",	// 409
		"manana",	// 410
		"infernus",	// 411
		"voodoo",	// 412
		"pony",	// 413
		"mule",	// 414
		"cheetah",	// 415
		"ambulan",	// 416
		"leviathn",	// 417
		"moonbeam",	// 418
		"esperant",	// 419
		"taxi",	// 420
		"washing",	// 421
		"bobcat",	// 422
		"mrwhoop",	// 423
		"bfinject",	// 424
		"hunter",	// 425
		"premier",	// 426
		"enforcer",	// 427
		"securica",	// 428
		"banshee",	// 429
		"predator",	// 430
		"bus",	// 431
		"rhino",	// 432
		"barracks",	// 433
		"hotknife",	// 434
		"artict1",	// 435
		"previon",	// 436
		"coach",	// 437
		"cabbie",	// 438
		"stallion",	// 439
		"rumpo",	// 440
		"rcbandit",	// 441
		"romero",	// 442
		"packer",	// 443
		"monster",	// 444
		"admiral",	// 445
		"squalo",	// 446
		"seaspar",	// 447
		"pizzaboy",	// 448
		"tram",	// 449
		"artict2",	// 450
		"turismo",	// 451
		"speeder",	// 452
		"reefer",	// 453
		"tropic",	// 454
		"flatbed",	// 455
		"yankee",	// 456
		"caddy",	// 457
		"solair",	// 458
		"topfun",	// 459
		"skimmer",	// 460
		"pcj600",	// 461
		"faggio",	// 462
		"freeway",	// 463
		"rcbaron",	// 464
		"rcraider",	// 465
		"glendale",	// 466
		"oceanic",	// 467
		"sanchez",	// 468
		"sparrow",	// 469
		"patriot",	// 470
		"quad",	// 471
		"coastg",	// 472
		"dinghy",	// 473
		"hermes",	// 474
		"sabre",	// 475
		"rustler",	// 476
		"zr350",	// 477
		"walton",	// 478
		"regina",	// 479
		"comet",	// 480
		"bmx",	// 481
		"burrito",	// 482
		"camper",	// 483
		"marquis",	// 484
		"baggage",	// 485
		"dozer",	// 486
		"maverick",	// 487
		"vcnmav",	// 488
		"rancher",	// 489
		"fbiranch",	// 490
		"virgo",	// 491
		"greenwoo",	// 492
		"jetmax",	// 493
		"hotring",	// 494
		"sandking",	// 495
		"blistac",	// 496
		"polmav",	// 497
		"boxville",	// 498
		"benson",	// 499
		"mesa",	// 500
		"rcgoblin",	// 501
		"hotrina",	// 502
		"hotrinb",	// 503
		"bloodra",	// 504
		"rnchlure",	// 505
		"supergt",	// 506
		"elegant",	// 507
		"journey",	// 508
		"bike",	// 509
		"mtbike",	// 510
		"beagle",	// 511
		"cropdust",	// 512
		"stunt",	// 513
		"petro",	// 514
		"rdtrain",	// 515
		"nebula",	// 516
		"majestic",	// 517
		"buccanee",	// 518
		"shamal",	// 519
		"hydra",	// 520
		"fcr900",	// 521
		"nrg500",	// 522
		"copbike",	// 523
		"cement",	// 524
		"towtruck",	// 525
		"fortune",	// 526
		"cadrona",	// 527
		"fbitruck",	// 528
		"willard",	// 529
		"forklift",	// 530
		"tractor",	// 531
		"combine",	// 532
		"feltzer",	// 533
		"remingtn",	// 534
		"slamvan",	// 535
		"blade",	// 536
		"freight",	// 537
		"streak",	// 538
		"vortex",	// 539
		"vincent",	// 540
		"bullet",	// 541
		"clover",	// 542
		"sadler",	// 543
		"firela",	// 544
		"hustler",	// 545
		"intruder",	// 546
		"primo",	// 547
		"cargobob",	// 548
		"tampa",	// 549
		"sunrise",	// 550
		"merit",	// 551
		"utility",	// 552
		"nevada",	// 553
		"yosemite",	// 554
		"windsor",	// 555
		"monstera",	// 556
		"monsterb",	// 557
		"uranus",	// 558
		"jester",	// 559
		"sultan",	// 560
		"stratum",	// 561
		"elegy",	// 562
		"raindanc",	// 563
		"rctiger",	// 564
		"flash",	// 565
		"tahoma",	// 566
		"savanna",	// 567
		"bandito",	// 568
		"freiflat",	// 569
		"streakc",	// 570
		"kart",	// 571
		"mower",	// 572
		"duneride",	// 573
		"sweeper",	// 574
		"broadway",	// 575
		"tornado",	// 576
		"at400",	// 577
		"dft30",	// 578
		"huntley",	// 579
		"stafford",	// 580
		"bf400",	// 581
		"newsvan",	// 582
		"tug",	// 583
		"petrotr",	// 584
		"emperor",	// 585
		"wayfarer",	// 586
		"euros",	// 587
		"hotdog",	// 588
		"club",	// 589
		"freibox",	// 590
		"artict3",	// 591
		"androm",	// 592
		"dodo",	// 593
		"rccam",	// 594
		"launch",	// 595
		"copcarla",	// 596
		"copcarsf",	// 597
		"copcarvg",	// 598
		"copcarru",	// 599
		"picador",	// 600
		"swatvan",	// 601
		"alpha",	// 602
		"phoenix",	// 603
		"glenshit",	// 604
		"sadlshit",	// 605
		"bagboxa",	// 606
		"bagboxb",	// 607
		"tugstair",	// 608
		"boxburg",	// 609
		"farmtr1",	// 610
		"utiltr1",	// 611
		"busx3gl",	// 612
		"bagx3gl",	// 613
	};

	// Dumps default audio settings
	void DumpDefaultAudioSettings()
	{
		MAKE_VAR_GAME_VERSION();
		CGenericLogStorage::SaveTextLn("Default audio settings:");

		MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		const tVehicleAudioSettings* pVehicleAudioSettings = (const tVehicleAudioSettings*)0x860AF0;

		for (int ID = 400; ID <= 611; ID++)
		{
		#ifdef tVehicleAudioSettings_gap_fields_should_be_defined
			if (!CompareMemWithZeroes(pVehicleAudioSettings->gap_1, sizeof(pVehicleAudioSettings->gap_1))
				|| !CompareMemWithZeroes(pVehicleAudioSettings->gap_7, sizeof(pVehicleAudioSettings->gap_7))
				|| !CompareMemWithZeroes(pVehicleAudioSettings->gap_11, sizeof(pVehicleAudioSettings->gap_11))
				|| !CompareMemWithZeroes(pVehicleAudioSettings->gap_1D, sizeof(pVehicleAudioSettings->gap_1D))

				)
			{
				printf_MessageBox("Some vehicle audio value is not NULL!");
			}
		#endif


			char BassFactor[32];
			char EnginePitch[32];
			char HornPitch[32];
			char EngineVolumeOffset[32];

			DoubleToStr(pVehicleAudioSettings->BassFactor, BassFactor);
			DoubleToStr(pVehicleAudioSettings->EnginePitch, EnginePitch);
			DoubleToStr(pVehicleAudioSettings->HornPitch, HornPitch);
			DoubleToStr(pVehicleAudioSettings->EngineVolumeOffset, EngineVolumeOffset);

			CGenericLogStorage::SaveFormattedTextLn(
				"%-43s %-13d %-6d %-6d %-9d %-12s %-12s %-9d %-12s %-11d %-10d %-10d %-11d %-17d %s",
				aDefaultListOfVehicleModelNames[ID - 400],

				pVehicleAudioSettings->VehicleAudioType,
				pVehicleAudioSettings->PlayerBank,
				pVehicleAudioSettings->DummyBank,

				pVehicleAudioSettings->BassSetting,
				BassFactor,
				EnginePitch,

				pVehicleAudioSettings->HornType,
				HornPitch,
				pVehicleAudioSettings->DoorType,
				pVehicleAudioSettings->EngineUpgrade,

				pVehicleAudioSettings->RadioStation,
				pVehicleAudioSettings->RadioType,

				pVehicleAudioSettings->VehicleAudioTypeForName,
				EngineVolumeOffset

			);

			// pVehicleAudioSettings = (char*)(pVehicleAudioSettings;
		}
	}
#endif

	CGenericLogStorage::WriteLineSeparator();
	}

	class CAEVehicleAudioEntity
	{
	public:
		// Returns vehicle audio settings
		tVehicleAudioSettings GetVehicleAudioSettings(uint32_t modelID)
		{
			/*
			return ((tVehicleAudioSettings (__thiscall*)
				(CAEVehicleAudioEntity*, uint16_t ID))0x4F5C10)
				(this, ID);
				*/

			CBaseModelInfo_extension* pModelInfoExt = g_fileIDlimits.CModelInfo__ms_modelInfoExtensionPtrs[modelID];

			tVehicleAudioSettings audioSettings;

			if (pModelInfoExt && pModelInfoExt->VehicleAudioID != UNDEFINED_AUDIO_ID)
			{
				const tVehicleAudioSettings* ptr = (const tVehicleAudioSettings*)g_vehicleAudioLoader.GetVehicleAudioSettingsByID(pModelInfoExt->VehicleAudioID);

				audioSettings = *ptr;
			}
			else
				memset(&audioSettings, NULL, sizeof(tVehicleAudioSettings));

			return audioSettings;
		}
	};
	
	extern "C"
	{
		uintptr_t Address_CAEVehicleAudioEntity__Initialise_goBack;
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CAEVehicleAudioEntity__Initialise_4F77B4()
	{
		__asm
		{
			mov ecx, edx;
			call CEntity::GetModelID;

			push eax;	// model ID
			lea     ecx, [ebp + 80h];
			push ecx;	// destination

			mov ecx, ebp;	// this
			call CAEVehicleAudioEntity::GetVehicleAudioSettings;
			mov     ecx, [esp + 0x10 + 4];

			push Address_CAEVehicleAudioEntity__Initialise_goBack;
			retn;
		}
	}

	NAKED void patch_run_LoadVehicleAudioSettings()
	{
		__asm
		{
			mov     fs:[0], ecx;
			add     esp, 10h;
			jmp run_LoadVehicleAudioSettings;
		}
	}
	#endif

	// GTA SA 2.0
	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
	extern "C"
	{
		uintptr_t Address_CVehicleModelInfo__SetupCommonData_loop;

		TARGET_THUMB NAKED void patch_CVehicleModelInfo__SetupCommonData_468C00()
		{
			__asm volatile(
				".thumb\n"
				"BNE             1f\n"
				"ldr fp, [sp], #4\n"
				"POP             {R4-R7,LR}\n"
				"B run_LoadVehicleAudioSettings\n"

				"1:\n"
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVehicleModelInfo__SetupCommonData_loop)
			);
		}

		auto Address_CEntity__GetModelID = &CEntity::GetModelID;
		auto Address_CAEVehicleAudioEntity__GetVehicleAudioSettings = &CAEVehicleAudioEntity::GetVehicleAudioSettings;

		TARGET_THUMB NAKED void patch_CAEVehicleAudioEntity__Initialise_3AC71E()
		{
			__asm volatile(
				".thumb\n"
				"MOV R0, R5\n"
				ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R1, Address_CEntity__GetModelID)
				"BLX R1\n"

				"MOV R2, R0\n"	// model ID
				"MOV R1, R4\n" // this
				"ADD.W           R0, R4, #0x80\n"	// destination: this + 0x80
				ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R3, Address_CAEVehicleAudioEntity__GetVehicleAudioSettings)
				"BLX R3\n"

				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CAEVehicleAudioEntity__Initialise_goBack)
				);
		}
	}
	#endif
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTAIV
{
	struct tVehicleModelDescriptor
	{
		const char* modelName;
		const char* gameName;
	};

	tVehicleModelDescriptor aDefaultListOfVehicles[] =
	{
		// GTA IV
		{ "admiral", "ADMIRAL" },
		{ "airtug", "AIRTUG" },
		{ "ambulance", "AMBULAN" },
		{ "banshee", "BANSHEE" },
		{ "benson", "BENSON" },
		{ "biff", "BIFF" },
		{ "blista", "BLISTA" },
		{ "bobcat", "BOBCAT" },
		{ "boxville", "BOXVLE" },
		{ "buccaneer", "BUCCNEER" },
		{ "burrito", "BURRITO" },
		{ "burrito2", "BURRITO2" },
		{ "bus", "BUS" },
		{ "cabby", "CABBY" },
		{ "cavalcade", "CAVCADE" },
		{ "chavos", "CHAV" },
		{ "cognoscenti", "COGNONTI" },
		{ "comet", "COMET" },
		{ "coquette", "COQUETTE" },
		{ "df8", "DF8" },
		{ "dilettante", "DILANTE" },
		{ "dukes", "DUKES" },
		{ "e109", "CONTENDER" },
		{ "emperor", "EMPEROR" },
		{ "emperor2", "EMPEROR2" },
		{ "esperanto", "ESPERNTO" },
		{ "faction", "FACTION" },
		{ "fbi", "FBI" },
		{ "feltzer", "FELTZER" },
		{ "feroci", "FEROCI" },
		{ "feroci2", "FEROCI2" },
		{ "firetruk", "FIRETRUK" },
		{ "flatbed", "FLATBED" },
		{ "fortune", "FORTUNE" },
		{ "forklift", "FORK" },
		{ "futo", "FUTO" },
		{ "fxt", "FXT" },
		{ "habanero", "HABANRO" },
		{ "hakumai", "HAKUMAI" },
		{ "huntley", "HUNT" },
		{ "infernus", "INFERNUS" },
		{ "ingot", "INGOT" },
		{ "intruder", "INTRUD" },
		{ "landstalker", "LANSTALK" },
		{ "lokus", "LOKUS" },
		{ "manana", "MANANA" },
		{ "marbella", "MARBELLA" },
		{ "merit", "MERIT" },
		{ "minivan", "MINVAN" },
		{ "moonbeam", "MOONB" },
		{ "mrtasty", "MRTASTY" },
		{ "mule", "MULE" },
		{ "noose", "NOOSE" },
		{ "nstockade", "NSTOCK" },
		{ "oracle", "ORACLE" },
		{ "packer", "PACKER" },
		{ "patriot", "PATRIOT" },
		{ "perennial", "PEREN" },
		{ "perennial2", "PEREN2" },
		{ "peyote", "PEYOTE" },
		{ "phantom", "PHANTOM" },
		{ "pinnacle", "PINCLE" },
		{ "pmp600", "PMP600" },
		{ "police", "POLICE" },
		{ "police2", "POLICE2" },
		{ "polpatriot", "POLPAT" },
		{ "pony", "PONY" },
		{ "premier", "PREMIER" },
		{ "pres", "PRES" },
		{ "primo", "PRIMO" },
		{ "pstockade", "PSTOCK" },
		{ "rancher", "RANCHER" },
		{ "rebla", "REBLA" },
		{ "ripley", "RIPLEY" },
		{ "romero", "ROMERO" },
		{ "rom", "ALBANY" },
		{ "ruiner", "RUINER" },
		{ "sabre", "SABRE" },
		{ "sabre2", "SABRE2" },
		{ "sabregt", "SABREGT" },
		{ "schafter", "SCHAFTER" },
		{ "sentinel", "SENTINEL" },
		{ "solair", "SOLAIR" },
		{ "speedo", "SPEEDO" },
		{ "stalion", "STALION" },
		{ "steed", "STEED" },
		{ "stockade", "STOCK" },
		{ "stratum", "STRATUM" },
		{ "stretch", "STRETCH" },
		{ "sultan", "SULTAN" },
		{ "sultanrs", "SULTANRS" },
		{ "supergt", "SUPER" },
		{ "taxi", "TAXI" },
		{ "taxi2", "TAXI2" },
		{ "trash", "TRUSH" },
		{ "turismo", "TURISMO" },
		{ "uranus", "URANUS" },
		{ "vigero", "VIGERO" },
		{ "vigero2", "VIGERO2" },
		{ "vincent", "VINCENT" },
		{ "virgo", "VIRGO" },
		{ "voodoo", "VOODOO" },
		{ "washington", "WASHINGTON" },
		{ "willard", "WILARD" },
		{ "yankee", "YANKEE" },
		{ "bobber", "BOBBER" },
		{ "faggio", "FAGGIO" },
		{ "hellfury", "HELLFURY" },
		{ "nrg900", "NRG900" },
		{ "pcj", "PCJ" },
		{ "sanchez", "SANCHEZ" },
		{ "zombieb", "ZOMB" },
		{ "annihilator", "ANNHIL" },
		{ "maverick", "MAVERICK" },
		{ "polmav", "POLMAV" },
		{ "tourmav", "TOURMAV" },
		{ "dinghy", "DINGHY" },
		{ "jetmax", "JETMAX" },
		{ "marquis", "MARQUI" },
		{ "predator", "PREDTOR" },
		{ "reefer", "REEFER" },
		{ "squalo", "SQUALO" },
		{ "tuga", "RUSTBOAT" },
		{ "tropic", "TROPIC" },
		{ "cablecar", "CABLECAR" },
		{ "subway_lo", "SUBWAY" },
		{ "subway_hi", "SUBWAY2" },

		// GTA the ballad of gay Tony
		{ "slamvan", "SLAMVAN" },
		{ "caddy", "CADDY" },
		{ "apc", "APC" },
		{ "superd", "SUPERD" },
		{ "superd2", "SUPERD2" },
		{ "serrano", "SERRANO" },
		{ "serrano2", "SERRANO" },
		{ "buffalo", "BUFFALO" },
		{ "avan", "AVAN" },
		{ "schafter2", "SCHAFTE2" },
		{ "schafter3", "SCHAFTE3" },
		{ "bullet", "BULLET" },
		{ "tampa", "TAMPA" },
		{ "cavalcade2", "CAVCADE" },
		{ "f620", "F620" },
		{ "limo2", "LIMO2" },
		{ "police3", "POLICE3" },
		{ "policew", "POLICE3" },
		{ "police4", "POLICE4" },
		{ "policeb", "POLICEB" },
		{ "hexer", "HEXER" },
		{ "faggio2", "FAGGIO" },
		{ "bati2", "BATI2" },
		{ "vader", "VADER" },
		{ "akuma", "AKUMA" },
		{ "hakuchou", "HAKUCH" },
		{ "double", "DOUBLE" },
		{ "buzzard", "BUZZARD" },
		{ "swift", "SWIFT" },
		{ "skylift", "SKYLIFT" },
		{ "smuggler", "SMUGGLER" },
		{ "floater", "FLOATER" },
		{ "blade", "BLADE" },

		// GTA The Lost and Damned

		{ "gburrito", "GBURRITO" },
		{ "slamvan", "SLAMVAN" },
		{ "towtruck", "TOWTRUCK" },
		{ "packer2", "PACKER" },
		{ "pbus", "PBUS" },
		{ "yankee2", "YANKEE2" },
		{ "rhapsody", "RHAPSODY" },
		{ "regina", "REGINA" },
		{ "tampa", "TAMPA" },
		{ "angel", "ANGEL" },
		{ "bati", "BATI" },
		{ "bati2", "BATI2" },
		{ "daemon", "DAEMON" },
		{ "diabolus", "DIABO" },
		{ "double", "DOUBLE" },
		{ "double2", "DOUBLE2" },
		{ "hakuchou", "HAKUCH" },
		{ "hakuchou2", "HAKUCH2" },
		{ "hexer", "HEXER" },
		{ "innovation", "INNOV" },
		{ "lycan", "LYCAN" },
		{ "nightblade", "NIGHTBL" },
		{ "revenant", "REVENANT" },
		{ "wayfarer", "WAYFAR" },
		{ "wolfsbane", "WOLFS" }
	};

	// known sound hashes
	CHashStringLoader defaultSoundNameContainer(GTAIV_crc32FromLowerCaseString);

	enum eListOfSounds
	{
		SOUND_LIST_SOUNDS,
		SOUND_LIST_CURVES,
		SOUND_LIST_CATEGORIES,
		SOUND_LIST_GAME,
		SOUND_LIST_EFFECTS,

		SOUND_LIST_COUNT,
		SOUND_LIST_FIRST = SOUND_LIST_SOUNDS
	};

	DEFINE_ENUM_OPERATORS(eListOfSounds);

	/* FASTMAN92_TIP: search for "noloadingtune" string in EXE if you want to find the sound container pointers.
		to find EFFECTS, search for C7 46 30 01 00 00 00 89  56 2C 89 4E 24 bytes
		to find CATEGORIES search for "DEFAULT_HELI"

		Creating a list of audio banks:
		get some string from the audio DAT file, like a string, which names the audio bank in SOUNDS.DAT15
		Use hex editor to look at that file.
		
		Run the game, load it and search for the same string in memory.
		The list of strings naming the audio banks separated by NULL character will be available.	
		*/

	uint32_t SoundContainerPtrs_GTA_IV_1_0_4_0[SOUND_LIST_COUNT] =
	{
		0xFC088C,	// SOUND_LIST_SOUNDS
		0xFC0684,	// SOUND_LIST_CURVES
		0xFC0620,	// SOUND_LIST_CATEGORIES
		0xFC08E8 ,	// SOUND_LIST_GAME
		0xFC0754	// SOUND_LIST_EFFECTS
	};

	uint32_t SoundContainerPtrs_GTA_IV_1_0_7_0[SOUND_LIST_COUNT] =
	{
		0x1716F18,	// SOUND_LIST_SOUNDS
		0x1716D04,	// SOUND_LIST_CURVES
		0x1716CA0,	// SOUND_LIST_CATEGORIES
		0x1716CA0 + 0x2D4,	// SOUND_LIST_GAME
		0x1716dd4	// SOUND_LIST_EFFECTS
	};

	uint32_t SoundContainerPtrs_GTA_IV_1_0_8_0[SOUND_LIST_COUNT] =
	{
		0x10F1BE8,	// SOUND_LIST_SOUNDS
		0x10F19D4,	// SOUND_LIST_CURVES
		0x10F1970,	// SOUND_LIST_CATEGORIES
		0x10F1C44,	// SOUND_LIST_GAME
		0x10F1AA4	// SOUND_LIST_EFFECTS
	};

	uint32_t SoundContainerPtrsGTA_EFLC_1_1_2_0[SOUND_LIST_COUNT] =
	{
		0x104A968,	// SOUND_LIST_SOUNDS
		0x104A754,	// SOUND_LIST_CURVES
		0x104A6F0,	// SOUND_LIST_CATEGORIES
		0x104A9C4,	// SOUND_LIST_GAME
		0x104A824	// SOUND_LIST_EFFECTS
	};

	uint32_t* SoundContainerPtrs = NULL;

	uint32_t Address_CSoundContainer_GetAudioSettingsByName;
	uint32_t Address_CSoundContainer_GetAudioSettingsByHash;

	class CSoundContainer
	{
	public:
		char gap[60];
		uint32_t countOfAudioBanks;
		uint32_t* pAudioBankStringHashes;


		// structure here is incomplete

		// Returns pointer to audio settings
		const tVehicleAudioSettings* GetAudioSettingsByName(const char* name)
		{
			return ((const tVehicleAudioSettings* (__thiscall*)
				(CSoundContainer*, const char* name)) Address_CSoundContainer_GetAudioSettingsByName)
				(this, name);
		};

		// Returns pointer to audio settings
		const tVehicleAudioSettings* GetAudioSettingsByHash(uint32_t hash)
		{
			return ((const tVehicleAudioSettings* (__thiscall*)
				(CSoundContainer*, uint32_t hash)) Address_CSoundContainer_GetAudioSettingsByHash)
				(this, hash);
		}
	};

	// 0x0E38FCF16 - NULL_SOUND

	// Iterates audio settings of single type
	void IterateAudioSettingsOfSingleType(int type, void(*func)(const char* modelName, const tVehicleAudioSettings* pVehAudioSettings))
	{
		CSoundContainer* pSoundContainer = (CSoundContainer*)g_mCalc.GetCurrentVAbyPreferedVA(SoundContainerPtrs[SOUND_LIST_GAME]);
		char gameName[9];

		for (const tVehicleModelDescriptor* pVehModel = aDefaultListOfVehicles;
			pVehModel != aDefaultListOfVehicles + _countof(aDefaultListOfVehicles);
			pVehModel++)
		{
			strncpy(gameName, pVehModel->gameName, sizeof(gameName));
			gameName[sizeof(gameName) - 1] = 0;

			const tVehicleAudioSettings* pVehAudioSettings = pSoundContainer->GetAudioSettingsByName(gameName);

			if (pVehAudioSettings && ((tVehicleAudioSettingsBase*)pVehAudioSettings)->structType == type)
				func(pVehModel->modelName, pVehAudioSettings);
		}
	}

	static CSoundContainer* GetSoundContainerPtr(eListOfSounds soundList)
	{
		return (CSoundContainer*)g_mCalc.GetCurrentVAbyPreferedVA(SoundContainerPtrs[soundList]);
	}

	// Returns hash string
	std::string GetHashString(uint32_t hash)
	{
		if (hash == 0)
			return "NULL";
		else if (const char* pStr = defaultSoundNameContainer.FindStringByHash(hash))
			return pStr;
		else
		{
			char buffer[32];
			sprintf(buffer, "HASH_%08X", hash);
			return std::string(buffer);
		}
	}

	/// dumping functions

	// Dumps model name
	void DumpModelName(const char* modelName)
	{
		CGenericLogStorage::SaveFormattedTextLn("[%s]", modelName);

		// CGenericLogStorage::SaveFormattedText("%-43s ", modelName);
	}

	// Dumps int value
	void DumpInt(const char* fieldName, int num)
	{
		CGenericLogStorage::SaveFormattedTextLn("%s = %d", fieldName, num);

		/*
		if(bIsLast)
			CGenericLogStorage::SaveFormattedText("%-9d", num);
		else
			CGenericLogStorage::SaveFormattedText("%-9d ", num);
			*/
	}

	// Dumps hex int value
	void DumpHexInt(const char* fieldName, int num)
	{
		CGenericLogStorage::SaveFormattedTextLn("%s = 0x%X ", fieldName, num);
		/*
		CGenericLogStorage::SaveFormattedText("0x%-8X ", num);
		*/
	}

	// Dumps float value
	void DumpFloat(const char* fieldName, float num)
	{
		char buffer[64];

		if ((int)num == num)
			sprintf(buffer, "%g.0", num);
		else
			sprintf(buffer, "%g", num);

		CGenericLogStorage::SaveFormattedTextLn("%s = %s", fieldName, buffer);

		// CGenericLogStorage::SaveFormattedText("%-12s ", buffer);
	}

	// Dumps hash
	void DumpHash(const char* fieldName, uint32_t hash)
	{
		std::string str = GetHashString(hash);
		CGenericLogStorage::SaveFormattedTextLn("%s = %s", fieldName, str.c_str());
	}

	uint32_t* pGameEpisodeNum = NULL;

	// Dumps default audio settings
	void DumpDefaultAudioSettings()
	{
		MAKE_VAR_GAME_VERSION();

		CGenericLogStorage::SaveTextLn("Default audio settings:");

		if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			defaultSoundNameContainer.LoadFromFile("GTA_IV_audioHashNameList.txt");
		else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
		{
			if (*pGameEpisodeNum == 1)
				defaultSoundNameContainer.LoadFromFile("GTA_TLAD_audioHashNameList.txt");
			else if (*pGameEpisodeNum == 2)
				defaultSoundNameContainer.LoadFromFile("GTA_TBoGT_audioHashNameList.txt");

		}

		/*
		SetCurrentDirectoryA(CLimitAdjusterMain::StorageRootDirectory);

		FILE* fp = fopen("AudioDump.bin", "wb");
		*/
	#if TRUE
		{
			struct tSoundDescriptor
			{
				char name[128];
				const tVehicleAudioSettings* pAudioSettings;
			};

			std::vector<tSoundDescriptor> memPtrs;

			CSoundContainer* pSoundContainer = (CSoundContainer*)g_mCalc.GetCurrentVAbyPreferedVA(
				SoundContainerPtrs[SOUND_LIST_GAME]
			);

			char gameName[9];

			for (tVehicleModelDescriptor* pVehModel = aDefaultListOfVehicles;
				pVehModel != aDefaultListOfVehicles + _countof(aDefaultListOfVehicles);
				pVehModel++)
			{
				strncpy(gameName, pVehModel->gameName, sizeof(gameName));
				gameName[sizeof(gameName) - 1] = NULL;

				const tVehicleAudioSettings* pVehAudioSettings = pSoundContainer->GetAudioSettingsByName(gameName);

				if (!pVehAudioSettings)
					continue;

				tSoundDescriptor soundDescriptor;
				strcpy(soundDescriptor.name, gameName);
				soundDescriptor.pAudioSettings = pVehAudioSettings;

				memPtrs.push_back(soundDescriptor);

				char modelName[24] = { 0 };

				strncpy(modelName, pVehModel->modelName, sizeof(modelName));
			}

			std::sort(memPtrs.begin(), memPtrs.end(),
				[](const tSoundDescriptor& a, const tSoundDescriptor& b)
			{
				return a.pAudioSettings < b.pAudioSettings;
			});

			const tVehicleAudioSettings* previousPtr;

			for (std::vector<tSoundDescriptor>::iterator it = memPtrs.begin(); it != memPtrs.end(); it++)
			{
				if (it != memPtrs.begin())
				{
					CGenericLogStorage::SaveFormattedTextLn("diff: 0x%X",
						(uintptr_t)it->pAudioSettings - (uintptr_t)previousPtr);
				}

				CGenericLogStorage::SaveFormattedTextLn("name: %s ptr: 0x%X", it->name, it->pAudioSettings);

				previousPtr = it->pAudioSettings;
			}
		}
	#endif


	#if TRUE
		// car, bikes
		IterateAudioSettingsOfSingleType(0,
			[](const char* modelName, const tVehicleAudioSettings* pVehAudioSettings)
		{
			const tVehicleAudioSettingsCarBike* pSettings = &pVehAudioSettings->carBike;

			CGenericLogStorage::SaveTextLn("");
			DumpModelName(modelName);
			DumpInt("structType", pSettings->structType);
			DumpInt("field_1", pSettings->field_1);
			DumpHexInt("flags", pSettings->flags);

			DumpFloat("floatAsInt_A", (float)pSettings->floatAsInt_A / 100.0);
			DumpFloat("floatAsInt_E", (float)pSettings->floatAsInt_E / 100.0);
			DumpHash("engineLowSound", pSettings->engineLowSound);
			DumpHash("engineHighSound", pSettings->engineHighSound);
			DumpHash("exhaustLowSound", pSettings->exhaustLowSound);
			DumpHash("exhaustHighSound", pSettings->exhaustHighSound);
			DumpHash("revsOffSound", pSettings->revsOffSound);

			DumpFloat("field_26", pSettings->field_26);
			DumpFloat("field_2A", pSettings->field_2A);
			DumpFloat("floatAsInt_2E", (float)pSettings->floatAsInt_2E / 100.0);
			DumpFloat("floatAsInt_32", (float)pSettings->floatAsInt_32 / 100.0);
			DumpFloat("field_36", pSettings->field_36);
			DumpFloat("field_3A", pSettings->field_3A);
			DumpFloat("floatAsInt_3E", (float)pSettings->floatAsInt_3E / 100.0);
			DumpFloat("floatAsInt_42", (float)pSettings->floatAsInt_42 / 100.0);
			DumpFloat("field_46", pSettings->field_46);
			DumpFloat("field_4A", pSettings->field_4A);

			DumpFloat("floatAsInt_4E", (float)pSettings->floatAsInt_4E / 100.0);
			DumpFloat("floatAsInt_52", (float)pSettings->floatAsInt_52 / 100.0);
			DumpFloat("field_56", pSettings->field_56);
			DumpFloat("field_5A", pSettings->field_5A);
			DumpFloat("floatAsInt_5E", (float)pSettings->floatAsInt_5E / 100.0);
			DumpFloat("floatAsInt_62", (float)pSettings->floatAsInt_62 / 100.0);
			DumpFloat("floatAsInt_66", (float)pSettings->floatAsInt_66 / 100.0);
			DumpFloat("field_6A", pSettings->field_6A);
			DumpFloat("field_6E", pSettings->field_6E);
			DumpFloat("floatAsInt_72", (float)pSettings->floatAsInt_72 / 100.0);
			DumpFloat("floatAsInt_76", (float)pSettings->floatAsInt_76 / 100.0);
			DumpHash("engineWaveShape", pSettings->engineWaveShape);

			DumpFloat("floatAsInt_7E", (float)pSettings->floatAsInt_7E / 100.0);
			DumpHash("exhaustWaveShape", pSettings->exhaustWaveShape);
			DumpFloat("floatAsInt_86", (float)pSettings->floatAsInt_86 / 100.0);
			DumpFloat("floatAsInt_multiplier1200_8A", (float)pSettings->floatAsInt_multiplier1200_8A / 1200.0);
			DumpFloat("floatAsInt_multiplier1200_8E", (float)pSettings->floatAsInt_multiplier1200_8E / 1200.0);
			DumpHash("engineIdleLoopSound", pSettings->engineIdleLoopSound);
			DumpHash("exhaustIdleLoopSound", pSettings->exhaustIdleLoopSound);
			DumpFloat("floatAsInt_multiplier1200_9A", (float)pSettings->floatAsInt_multiplier1200_9A / 1200.0);
			DumpFloat("floatAsInt_multiplier1200_9E", (float)pSettings->floatAsInt_multiplier1200_9E / 1200.0);
			DumpHash("transmissionSound", pSettings->transmissionSound);
			DumpFloat("floatAsInt_A6", (float)(pSettings->floatAsInt_A6 / 100.0));
			DumpFloat("floatAsInt_AA", (float)pSettings->floatAsInt_AA / 100.0);
			DumpHash("sound_AE", pSettings->sound_AE);
			DumpFloat("floatAsInt_B2", (float)pSettings->floatAsInt_B2 / 100.0);
			DumpFloat("floatAsInt_B6", (float)pSettings->floatAsInt_B6 / 100.0);

			DumpHash("exhaustPopSound", pSettings->exhaustPopSound);
			DumpHash("airIntakeSound", pSettings->airIntakeSound);
			DumpFloat("floatAsInt_multiplier1200_C2", (float)pSettings->floatAsInt_multiplier1200_C2 / 1200);
			DumpFloat("floatAsInt_multiplier1200_C6", (float)pSettings->floatAsInt_multiplier1200_C6 / 1200.0);
			DumpHash("dumpValveSound", pSettings->dumpValveSound);
			DumpHash("startSound", pSettings->startSound);
			DumpHash("hornSound", pSettings->hornSound);
			DumpHash("openSound", pSettings->openSound);
			DumpHash("closeSound", pSettings->closeSound);
			DumpHash("trunkOpenSound", pSettings->trunkOpenSound);
			DumpHash("trunkCloseSound", pSettings->trunkCloseSound);
			DumpFloat("field_E6", pSettings->field_E6);
			DumpHash("suspensionUpSound", pSettings->suspensionUpSound);
			DumpHash("suspensionDownSound", pSettings->suspensionDownSound);
			DumpFloat("field_F2", pSettings->field_F2);
			DumpFloat("field_F6", pSettings->field_F6);

			DumpHash("policeScannerManufacturerSound", pSettings->policeScannerManufacturerSound);
			DumpHash("policeScannerModelSound", pSettings->policeScannerModelSound);
			DumpHash("policeScannerVehicleCategorySound", pSettings->policeScannerVehicleCategorySound);
			DumpHash("gearTransmissionSound", pSettings->gearTransmissionSound);
			DumpFloat("floatAsInt_multiplier1200_10A", (float)pSettings->floatAsInt_multiplier1200_10A / 1200.0);
			DumpFloat("floatAsInt_multiplier1200_10E", (float)pSettings->floatAsInt_multiplier1200_10E / 1200.0);
			DumpFloat("floatAsInt_multiplier1200_112", (float)pSettings->floatAsInt_multiplier1200_112 / 1200.0);
			DumpFloat("floatAsInt_116", (float)pSettings->floatAsInt_116 / 100.0);
			DumpInt("field_11A", pSettings->field_11A);

			DumpFloat("floatAsInt_11E", (float)pSettings->floatAsInt_11E / 100.0);
			DumpFloat("floatAsInt_122", (float)pSettings->floatAsInt_122 / 100.0);
			DumpFloat("floatAsInt_126", (float)pSettings->floatAsInt_126 / 100.0);
			DumpHash("jumpLandSound", pSettings->jumpLandSound);
			DumpInt("field_12E", pSettings->field_12E);
			DumpInt("field_132", pSettings->field_132);
			DumpHash("ignitionSound", pSettings->ignitionSound);
			DumpHash("engineShutDownSound", pSettings->engineShutDownSound);
			DumpInt("field_13E", pSettings->field_13E);
			DumpInt("field_13F", pSettings->field_13F);
			DumpInt("field_140", pSettings->field_140);
			DumpInt("field_141", pSettings->field_141);
			DumpHash("indicatorVehicleOn", pSettings->indicatorVehicleOn);
			DumpHash("indicatorVehicleOff", pSettings->indicatorVehicleOff);
			DumpHash("engineCoolingFan", pSettings->engineCoolingFan);
			DumpHash("handbrakeSound_14E", pSettings->handbrakeSound_14E);
			DumpHash("sound_152", pSettings->sound_152);
			DumpHash("sound_156", pSettings->sound_156);
			DumpHash("handbrakeSound_15A", pSettings->handbrakeSound_15A);
			DumpInt("field_15E", pSettings->field_15E);
			DumpInt("field_15F", pSettings->field_15F);
			DumpInt("field_160", pSettings->field_160);
		}
		);
	#endif

	#if TRUE

		// helicopters
		IterateAudioSettingsOfSingleType(4,
			[](const char* modelName, const tVehicleAudioSettings* pVehAudioSettings)
		{
			const tVehicleAudioSettingsHeli* pSettings = &pVehAudioSettings->heli;

			CGenericLogStorage::SaveTextLn("");
			DumpModelName(modelName);
			DumpInt("structType", pSettings->structType);
			DumpInt("field_1", pSettings->field_1);
			DumpHexInt("flags", pSettings->flags);

			/////////////
			DumpHash("rotorSound", pSettings->rotorSound);
			DumpHash("rearRotorSound", pSettings->rearRotorSound);
			DumpHash("exHaustSound", pSettings->exHaustSound);
			DumpHash("bankSound", pSettings->bankSound);
			DumpHash("internalCabinToneSound", pSettings->internalCabinToneSound);
			DumpFloat("field_1E", pSettings->field_1E);
			DumpHash("bankAngleVolumeSound", pSettings->bankAngleVolumeSound);
			DumpHash("bankThrottleVolumeSound", pSettings->bankThrottleVolumeSound);
			DumpHash("bankThrottlePitchCurveSound", pSettings->bankThrottlePitchCurveSound);
			DumpHash("rotorThrottleVolumeSound", pSettings->rotorThrottleVolumeSound);
			DumpHash("rotorThrottlePitchCurveSound", pSettings->rotorThrottlePitchCurveSound);
			DumpHash("rotorThrottleGapSound", pSettings->rotorThrottleGapSound);
			DumpHash("rearRotorThrottleVolumeSound", pSettings->rearRotorThrottleVolumeSound);
			DumpHash("exhaustThrottleVolumeSound", pSettings->exhaustThrottleVolumeSound);
			DumpHash("exhaustThrottlePitchCurveSound", pSettings->exhaustThrottlePitchCurveSound);
			DumpInt("field_46", pSettings->field_46);
			DumpInt("field_48", pSettings->field_48);
			DumpFloat("floatAsInt_4A", (float)pSettings->floatAsInt_4A / 100.0);
			DumpInt("field_4C", pSettings->field_4C);
			DumpInt("field_4E", pSettings->field_4E);
			DumpFloat("floatAsInt_50", (float)pSettings->floatAsInt_50 / 100.0);
			DumpInt("field_52", pSettings->field_52);
			DumpInt("field_54", pSettings->field_54);
			DumpFloat("floatAsInt_56", (float)pSettings->floatAsInt_56 / 100.0);
			DumpFloat("field_58", pSettings->field_58);
			DumpFloat("field_5C", pSettings->field_5C);
			DumpHash("throttleResonance1Sound", pSettings->throttleResonance1Sound);
			DumpFloat("field_64", pSettings->field_64);
			DumpFloat("field_68", pSettings->field_68);
			DumpHash("throttleResonance2Sound", pSettings->throttleResonance2Sound);
			DumpHash("bankingResonanceCurveSound", pSettings->bankingResonanceCurveSound);
			DumpHash("rotorVolumeStartupCurveSound", pSettings->rotorVolumeStartupCurveSound);
			DumpHash("bladeVolumeStartupCurveSound", pSettings->bladeVolumeStartupCurveSound);
			DumpHash("rotorPitchStartupCurveSound", pSettings->rotorPitchStartupCurveSound);
			DumpHash("rearRotorVolumeStartupCurveSound", pSettings->rearRotorVolumeStartupCurveSound);
			DumpHash("exhaustVolumeStartupCurveSound", pSettings->exhaustVolumeStartupCurveSound);
			DumpHash("rotorGapStartupCurveSound", pSettings->rotorGapStartupCurveSound);
			DumpHash("shotStartSound", pSettings->shotStartSound);
			DumpInt("field_90", pSettings->field_90);
			DumpInt("field_92", pSettings->field_92);
			DumpFloat("floatAsInt_94", (float)pSettings->floatAsInt_94 / 100.0);
			DumpInt("field_96", pSettings->field_96);
			DumpInt("field_98", pSettings->field_98);
			DumpFloat("floatAsInt_9A", pSettings->floatAsInt_9A / 100.0);
			DumpHash("policeScannerManufacturerSound", pSettings->policeScannerManufacturerSound);
			DumpHash("policeScannerModelSound", pSettings->policeScannerModelSound);
			DumpHash("policeScannerVehicleCategorySound", pSettings->policeScannerVehicleCategorySound);
			DumpInt("field_A8", pSettings->field_A8);
			DumpInt("field_A9", pSettings->field_A9);
			DumpHash("doorOpenSound", pSettings->doorOpenSound);
			DumpHash("doorCloseSound", pSettings->doorCloseSound);
			DumpHash("doorLimitSound", pSettings->doorLimitSound);
			DumpHash("damageLoopSound", pSettings->damageLoopSound);
		});
	#endif


	#if TRUE
		// boats
		IterateAudioSettingsOfSingleType(7,
			[](const char* modelName, const tVehicleAudioSettings* pVehAudioSettings)
		{
			const tVehicleAudioSettingsBoat* pSettings = &pVehAudioSettings->boat;

			CGenericLogStorage::SaveTextLn("");
			DumpModelName(modelName);
			DumpInt("structType", pSettings->structType);
			DumpInt("field_1", pSettings->field_1);
			DumpHexInt("flags", pSettings->flags);

			/////////////
			DumpHash("engineLoopSound", pSettings->engineLoopSound);
			DumpHash("engineVolumeSound", pSettings->engineVolumeSound);
			DumpHash("enginePitchSound_12", pSettings->enginePitchSound_12);
			DumpHash("engine2loopSound", pSettings->engine2loopSound);
			DumpHash("engine2volumeSound", pSettings->engine2volumeSound);
			DumpHash("enginePitchSound_1E", pSettings->enginePitchSound_1E);
			DumpHash("lowResonanceLoopSound", pSettings->lowResonanceLoopSound);
			DumpHash("resonanceVolumeSound", pSettings->resonanceVolumeSound);
			DumpHash("enginePitchSound_2A", pSettings->enginePitchSound_2A);
			DumpHash("idleLoopSound", pSettings->idleLoopSound);
			DumpHash("idleResonanceVolumeSound", pSettings->idleResonanceVolumeSound);
			DumpHash("enginePitchSound_36", pSettings->enginePitchSound_36);
			DumpHash("waterTurbulanceSound", pSettings->waterTurbulanceSound);
			DumpHash("waterTurbulanceVolumeSound", pSettings->waterTurbulanceVolumeSound);
			DumpHexInt("field_42", pSettings->field_42);
			DumpFloat("field_46", pSettings->field_46);
			DumpFloat("field_4A", pSettings->field_4A);
			DumpFloat("floatAsInt_4E", (float)pSettings->floatAsInt_4E / 100.0);
			DumpFloat("floatAsInt_52", (float)pSettings->floatAsInt_52 / 100.0);
			DumpFloat("field_56", pSettings->field_56);
			DumpFloat("field_5A", pSettings->field_5A);
			DumpFloat("floatAsInt_5E", (float)pSettings->floatAsInt_5E / 100.0);
			DumpFloat("floatAsInt_62", (float)pSettings->floatAsInt_62 / 100.0);
			DumpFloat("field_66", pSettings->field_66);
			DumpFloat("field_6A", pSettings->field_6A);
			DumpFloat("floatAsInt_6E", (float)pSettings->floatAsInt_6E / 100.0);
			DumpFloat("floatAsInt_72", (float)pSettings->floatAsInt_72 / 100.0);
			DumpFloat("field_76", pSettings->field_76);
			DumpFloat("field_7A", pSettings->field_7A);
			DumpFloat("floatAsInt_7E", (float)pSettings->floatAsInt_7E / 100.0);
			DumpFloat("floatAsInt_82", (float)pSettings->floatAsInt_82 / 100.0);
			DumpFloat("floatAsInt_86", (float)pSettings->floatAsInt_86 / 100.0);
			DumpFloat("field_8A", pSettings->field_8A);
			DumpFloat("field_8E", pSettings->field_8E);
			DumpFloat("floatAsInt_92", (float)pSettings->floatAsInt_92 / 100.0);
			DumpFloat("floatAsInt_96", (float)pSettings->floatAsInt_96 / 100.0);
			DumpHash("linearRise_9A", pSettings->linearRise_9A);
			DumpInt("field_9E", pSettings->field_9E);
			DumpHash("linearRise_A2", pSettings->linearRise_A2);
			DumpInt("field_A6", pSettings->field_A6);
			DumpHash("policeScannerManufacturerSound", pSettings->policeScannerManufacturerSound);
			DumpHash("policeScannerModelSound", pSettings->policeScannerModelSound);
			DumpHash("policeScannerVehicleCategorySound", pSettings->policeScannerVehicleCategorySound);
			DumpInt("field_B6", pSettings->field_B6);
			DumpInt("field_B7", pSettings->field_B7);
			DumpHash("hornSound", pSettings->hornSound);
			DumpHash("materialSound", pSettings->materialSound);
			DumpHash("ignitionSound", pSettings->ignitionSound);
			DumpHash("shutDownSound", pSettings->shutDownSound);
			DumpInt("field_C8", pSettings->field_C8);

		});
	#endif


		printf_MessageBox("Vehicle audio properties, list dumped\n");

		g_LimitAdjuster.TerminateProcess();
	}

	class CAudioIniReader : public CIniReader
	{
	private:
		// Checks if sound exist
		static void CheckIfSoundExists(
			const char* lpAppName,
			const char* lpKeyName,
			eListOfSounds soundList,
			uint32_t hash
		)
		{
			CSoundContainer* pSoundContainer = GetSoundContainerPtr(soundList);

			if (!pSoundContainer->GetAudioSettingsByHash(hash))
				printf_MessageBox("gtaiv_vehicleAudioSettings.ini: sound with specified name does not exist.\n"
					"[%s] -> %s",
					lpAppName,
					lpKeyName
				);

		}

	public:
		// Returns hash
		uint32_t GetHash(const char* lpAppName, const char* lpKeyName, eListOfSounds soundList)
		{
			char soundName[128];

			this->GetString(lpAppName, lpKeyName, NULL, soundName, sizeof(soundName));

			if (!strcmp(soundName, "NULL"))
				return 0;
			else if (!memcmp(soundName, "HASH_", 5))
				return strtol(soundName + 5, NULL, 16);
			else
			{
				uint32_t hash = GTAIV_crc32FromLowerCaseString(soundName);
				CheckIfSoundExists(lpAppName, lpKeyName, soundList, hash);
				return hash;
			}
		}
	};

	// Checks sound list
	void __cdecl CheckSoundList(const CSoundContainer* pSoundContainer)
	{
		for (eListOfSounds soundList = SOUND_LIST_FIRST; soundList != SOUND_LIST_COUNT; soundList++)
			if (pSoundContainer == GetSoundContainerPtr(soundList))
				return;

		printf_MessageBox("Sound container not found: 0x%X", pSoundContainer);
	}

	uint32_t Address_CE3777;

	NAKED void patch_GetAudioEntryByHash_CE3770()
	{
		__asm
		{
			push ecx;

			push ecx;
			call CheckSoundList;
			add esp, 4;

			pop ecx;

			push ecx;
			push ebx;
			mov     ebx, [esp + 8 + 4];
			push esi;
			jmp Address_CE3777;
		}
	}

	void* CVehicleModelInfo__CVehicleStructure__m_pInfoPool;

	// GTA IV
	NAKED void patch_LoadVehicleAudioSettings()
	{
		__asm
		{
			mov ecx, CVehicleModelInfo__CVehicleStructure__m_pInfoPool;
			mov[ecx], eax;
			mov ecx, ASM_GET_OFFSET_OF_FLA_MODULE(g_vehicleAudioLoader);
			call CVehicleAudioLoader::LoadVehicleAudioSettings;
			retn;
		}
	}

	NAKED void patch_dumpDefaultAudioSettings()
	{
		__asm
		{
			mov ecx, CVehicleModelInfo__CVehicleStructure__m_pInfoPool;
			mov[ecx], eax;

			call DumpDefaultAudioSettings;

			retn;
		}
	}

	// GTA IV
	// GTA EFLC
	uint32_t Address_GetAudioSettingsForVehicle_pointToReturn = 0;

	NAKED void patch_in_GetAudioSettingsForVehicle()
	{
		__asm
		{
			mov     eax, [ecx + 820h];
			movzx   ecx, word ptr[eax + 2Eh];

			push ecx;
			call GetAudioSettingsForVehicleModelID;
			add esp, 4;

			jmp Address_GetAudioSettingsForVehicle_pointToReturn;
		}
	}

	uint32_t Address_GetAudioSettingsForHelicopter_pointToReturn = 0;
	NAKED void patch_in_GetAudioSettingsForHelicopter()
	{
		__asm
		{
			mov     eax, [ecx + 820h];
			movzx   ecx, word ptr[eax + 2Eh];

			push ecx;
			call GetAudioSettingsForVehicleModelID;
			add esp, 4;

			jmp Address_GetAudioSettingsForHelicopter_pointToReturn;
		}
	}

	uint32_t Address_GetAudioSettingsForBoat_pointToReturn = NULL;

	NAKED void patch_in_GetAudioSettingsForBoat()
	{
		__asm
		{
			mov     eax, [ecx + 250h];
			movzx   ecx, word ptr[eax + 2Eh];

			push ecx;
			call GetAudioSettingsForVehicleModelID;
			add esp, 4;

			jmp Address_GetAudioSettingsForBoat_pointToReturn;
		}
	}
}
#endif

// Sets vehicle audio settings path
void CVehicleAudioLoader::SetVehicleAudioSettingsPath(const char* path)
{
	MAKE_VAR_GAME_VERSION();

	if (path)
		CVehicleAudioLoader::ms_AudioSettingsPath = path;
	else
	{
		if (this->IsGameVersionUsingOldFormat(gameVersion))
			this->ms_AudioSettingsPath = "data\\vehicleAudioSettings.cfg";
		else if(CGameVersion::IsAny_GTA_SA(gameVersion))
			this->ms_AudioSettingsPath = "data\\gtasa_vehicleAudioSettings.cfg";
		else if(CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
			this->ms_AudioSettingsPath = "pc\\audio\\Config\\gtaiv_vehicleAudioSettings.ini";
	}
}

// Initialize
void CVehicleAudioLoader::Initialise()
{
	MAKE_VAR_GAME_VERSION();
	this->ms_bVehicleAudioLoaderEnabled = false;
	this->ms_bEnableDumpingDefaultSettings = false;
	this->ms_VehicleAudioEntries.generic = nullptr;
}

class DeleteVehicleAudioSettings
{
public:
	template <class T> static bool doStuff(T* pVehicleAudioSettings)
	{
		delete pVehicleAudioSettings;
		return true;
	}
};

// Shutdown
void CVehicleAudioLoader::Shutdown()
{
	this->TouchTheVehicleAudioSettings<DeleteVehicleAudioSettings, bool>(true);
}

// Loads vehicle audio settings for GTA SA
void CVehicleAudioLoader::LoadVehicleAudioSettings_configFile(const char* filename, bool bModelMustExist, tOneSettingInLineAudioConfigFileFunction func)
{
	using namespace Game_GTASA;

	CVehicleAudioLoader::UnloadVehicleAudioSettings();

	FILESTREAM fp = CFileMgr::OpenFile(filename, "r");

	if (!fp)
	{
		printf_MessageBox("Unable to load %s", filename);
		g_LimitAdjuster.TerminateProcess();
	}	
	
	char line[512];
	
	while (CFileMgr::ReadLine(fp, line, sizeof(line)))
	{		
		if (strncmp(line, ";the end", 8) == 0)
			break;

		if (!line[0] || line[0] == ';')
			continue;

		(this->*func)(line, bModelMustExist);
	}

	CFileMgr::CloseFile(fp);
}

// Loads vehicle audio settings for GTA old
void CVehicleAudioLoader::LoadVehicleAudioSettings_GTA_old(const char* line, bool bModelMustExist)
{
	using namespace Game_GTA_old;

	char modelName[IMG_FASTMAN92_GTASA_MAX_FILENAME_LENGTH + 1];

	int hasAirBrakes;
	int usesRevWarning;
	int sirenOption;
	int usesPoliceRadio;
	int usesTaxiRadio;

	tVehicleAudioSettings_extended settings;
	memset(&settings, NULL, sizeof(settings));

	sscanf(
		line,
		"%s %d %d %d %d %d %d %d %d %d %d %d %d",
		modelName,
		&settings.m_engineFarSample,
		&settings.m_engineNearSample,
		&settings.m_hornSample,
		&settings.m_hornFrequency,
		&settings.m_sirenSample,
		&settings.m_sirenFrequency,
		&settings.m_DoorSound,

		&hasAirBrakes,
		&usesRevWarning,
		&sirenOption,
		&usesPoliceRadio,
		&usesTaxiRadio
	);

	settings.hasAirBrakes = hasAirBrakes != 0;
	settings.usesRevWarning = UsesReverseWarning != 0;
	settings.sirenOption = sirenOption;
	settings.usesPoliceRadio = usesPoliceRadio != 0;
	settings.usesTaxiRadio = usesTaxiRadio != 0;

	int modelID;

	CBaseModelInfo_generic* pModelInfo = CModelInfo::GetModelInfo(modelName, &modelID);

	if (!pModelInfo)
	{
		printf_MessageBox(
			"vehicle audio config file.cfg: model with name %s does not exist.",
			modelName);

		return;
	}

	CBaseModelInfo_extension* pModelExtInfo = g_fileIDlimits.AllocateModelInfoExtensionItemIfNeccessary(modelID);

	int vehicleAudioID = this->ms_VehicleAudioEntries.gta_old->size();

	pModelExtInfo->VehicleAudioID = vehicleAudioID;

	this->ms_VehicleAudioEntries.gta_old->push_back(settings);
}

// Loads vehicle audio settings for GTA SA
void CVehicleAudioLoader::LoadVehicleAudioSettings_GTA_SA(const char* line, bool bModelMustExist)
{
	using namespace Game_GTASA;

	tVehicleAudioSettings_sscanf audioSettings;

	sscanf(line, "%s %d %d %d %d %f %f %d %f %d %d %d %d %d %f",
		audioSettings.modelName,
		&audioSettings.VehicleAudioType,
		&audioSettings.PlayerBank,
		&audioSettings.DummyBank,
		&audioSettings.BassSetting,
		&audioSettings.BassFactor,
		&audioSettings.EnginePitch,
		&audioSettings.HornType,
		&audioSettings.HornPitch,
		&audioSettings.DoorType,
		&audioSettings.EngineUpgrade,
		&audioSettings.RadioStation,
		&audioSettings.RadioType,
		&audioSettings.VehicleAudioTypeForName,
		&audioSettings.EngineVolumeOffset
	);

	this->SetVehicleAudioSettings_GTA_SA(&audioSettings);
}

#if IS_PLATFORM_WIN_X86
// Loads vehicle audio settings
void CVehicleAudioLoader::LoadVehicleAudioSettings_GTA_IV_EFLC(const char* filename, bool bModelMustExist)
{
	using namespace Game_GTAIV;
	CAudioIniReader config;

	if (!config.Open(filename))
		return;

	char sectionNames[32768];

	config.GetSectionNames(sectionNames, sizeof(sectionNames));

	char* pModelName = sectionNames;

	while (*pModelName)
	{
		int modelID;
		CBaseModelInfo* pModelInfo = CModelInfo::GetModelInfo(pModelName, &modelID);

		if (pModelInfo)
		{
			CBaseModelInfo_extension* pModelExtInfo = g_fileIDlimits.AllocateModelInfoExtensionItemIfNeccessary(modelID);
			
			int vehicleAudioID = CVehicleAudioLoader::ms_VehicleAudioEntries.gta_iv->size();

			pModelExtInfo->VehicleAudioID = vehicleAudioID;

			tVehicleAudioSettings audioSettings;
			memset(&audioSettings, NULL, sizeof(audioSettings));

			//////////////////////

			int structType = config.GetInt(pModelName, "structType");

			if (structType == 0)	// car / bike
			{
				tVehicleAudioSettingsCarBike* pSettings = &audioSettings.carBike;
				pSettings->structType = structType;
				pSettings->field_1 = config.GetInt(pModelName, "field_1");
				pSettings->flags = config.GetInt(pModelName, "flags");
				pSettings->floatAsInt_A = (int)(config.GetFloat(pModelName, "floatAsInt_A") * 100);
				pSettings->floatAsInt_E = (int)(config.GetFloat(pModelName, "floatAsInt_E") * 100);
				pSettings->engineLowSound = config.GetHash(pModelName, "engineLowSound", SOUND_LIST_SOUNDS);
				pSettings->engineHighSound = config.GetHash(pModelName, "engineHighSound", SOUND_LIST_SOUNDS);
				pSettings->exhaustLowSound = config.GetHash(pModelName, "exhaustLowSound", SOUND_LIST_SOUNDS);
				pSettings->exhaustHighSound = config.GetHash(pModelName, "exhaustHighSound", SOUND_LIST_SOUNDS);
				pSettings->revsOffSound = config.GetHash(pModelName, "revsOffSound", SOUND_LIST_SOUNDS);
				pSettings->field_26 = config.GetFloat(pModelName, "field_26");
				pSettings->field_2A = config.GetFloat(pModelName, "field_2A");
				pSettings->floatAsInt_2E = (int)(config.GetFloat(pModelName, "floatAsInt_2E") * 100);
				pSettings->floatAsInt_32 = (int)(config.GetFloat(pModelName, "floatAsInt_32") * 100);
				pSettings->field_36 = config.GetFloat(pModelName, "field_36");
				pSettings->field_3A = config.GetFloat(pModelName, "field_3A");
				pSettings->floatAsInt_3E = (int)(config.GetFloat(pModelName, "floatAsInt_3E") * 100);
				pSettings->floatAsInt_42 = (int)(config.GetFloat(pModelName, "floatAsInt_42") * 100);
				pSettings->field_46 = config.GetFloat(pModelName, "field_46");
				pSettings->field_4A = config.GetFloat(pModelName, "field_4A");
				pSettings->floatAsInt_4E = (int)(config.GetFloat(pModelName, "floatAsInt_4E") * 100);
				pSettings->floatAsInt_52 = (int)(config.GetFloat(pModelName, "floatAsInt_52") * 100);
				pSettings->field_56 = config.GetFloat(pModelName, "field_56");
				pSettings->field_5A = config.GetFloat(pModelName, "field_5A");
				pSettings->floatAsInt_5E = (int)(config.GetFloat(pModelName, "floatAsInt_5E") * 100);
				pSettings->floatAsInt_62 = (int)(config.GetFloat(pModelName, "floatAsInt_62") * 100);
				pSettings->floatAsInt_66 = (int)(config.GetFloat(pModelName, "floatAsInt_66") * 100);
				pSettings->field_6A = config.GetFloat(pModelName, "field_6A");
				pSettings->field_6E = config.GetFloat(pModelName, "field_6E");
				pSettings->floatAsInt_72 = (int)(config.GetFloat(pModelName, "floatAsInt_72") * 100);
				pSettings->floatAsInt_76 = (int)(config.GetFloat(pModelName, "floatAsInt_76") * 100);
				pSettings->engineWaveShape = config.GetHash(pModelName, "engineWaveShape", SOUND_LIST_CURVES);
				pSettings->floatAsInt_7E = (int)(config.GetFloat(pModelName, "floatAsInt_7E") * 100);
				pSettings->exhaustWaveShape = config.GetHash(pModelName, "exhaustWaveShape", SOUND_LIST_CURVES);
				pSettings->floatAsInt_86 = (int)(config.GetFloat(pModelName, "floatAsInt_86") * 100);
				pSettings->floatAsInt_multiplier1200_8A = (int)(config.GetFloat(pModelName, "floatAsInt_multiplier1200_8A") * 1200);
				pSettings->floatAsInt_multiplier1200_8E = (int)(config.GetFloat(pModelName, "floatAsInt_multiplier1200_8E") * 1200);
				pSettings->engineIdleLoopSound = config.GetHash(pModelName, "engineIdleLoopSound", SOUND_LIST_SOUNDS);
				pSettings->exhaustIdleLoopSound = config.GetHash(pModelName, "exhaustIdleLoopSound", SOUND_LIST_SOUNDS);
				pSettings->floatAsInt_multiplier1200_9A = (int)(config.GetFloat(pModelName, "floatAsInt_multiplier1200_9A") * 1200);
				pSettings->floatAsInt_multiplier1200_9E = (int)(config.GetFloat(pModelName, "floatAsInt_multiplier1200_9E") * 1200);
				pSettings->transmissionSound = config.GetHash(pModelName, "transmissionSound", SOUND_LIST_SOUNDS);
				pSettings->floatAsInt_A6 = (int)(config.GetFloat(pModelName, "floatAsInt_A6") * 100);
				pSettings->floatAsInt_AA = (int)(config.GetFloat(pModelName, "floatAsInt_AA") * 100);
				pSettings->sound_AE = config.GetHash(pModelName, "sound_AE", SOUND_LIST_SOUNDS);
				pSettings->floatAsInt_B2 = (int)(config.GetFloat(pModelName, "floatAsInt_B2") * 100);
				pSettings->floatAsInt_B6 = (int)(config.GetFloat(pModelName, "floatAsInt_B6") * 100);
				pSettings->exhaustPopSound = config.GetHash(pModelName, "exhaustPopSound", SOUND_LIST_SOUNDS);
				pSettings->airIntakeSound = config.GetHash(pModelName, "airIntakeSound", SOUND_LIST_SOUNDS);
				pSettings->floatAsInt_multiplier1200_C2 = (int)(config.GetFloat(pModelName, "floatAsInt_multiplier1200_C2") * 1200);
				pSettings->floatAsInt_multiplier1200_C6 = (int)(config.GetFloat(pModelName, "floatAsInt_multiplier1200_C6") * 1200);
				pSettings->dumpValveSound = config.GetHash(pModelName, "dumpValveSound", SOUND_LIST_SOUNDS);
				pSettings->startSound = config.GetHash(pModelName, "startSound", SOUND_LIST_SOUNDS);
				pSettings->hornSound = config.GetHash(pModelName, "hornSound", SOUND_LIST_SOUNDS);
				pSettings->openSound = config.GetHash(pModelName, "openSound", SOUND_LIST_SOUNDS);
				pSettings->closeSound = config.GetHash(pModelName, "closeSound", SOUND_LIST_SOUNDS);
				pSettings->trunkOpenSound = config.GetHash(pModelName, "trunkOpenSound", SOUND_LIST_SOUNDS);
				pSettings->trunkCloseSound = config.GetHash(pModelName, "trunkCloseSound", SOUND_LIST_SOUNDS);
				pSettings->field_E6 = config.GetFloat(pModelName, "field_E6");
				pSettings->suspensionUpSound = config.GetHash(pModelName, "suspensionUpSound", SOUND_LIST_SOUNDS);
				pSettings->suspensionDownSound = config.GetHash(pModelName, "suspensionDownSound", SOUND_LIST_SOUNDS);
				pSettings->field_F2 = config.GetFloat(pModelName, "field_F2");
				pSettings->field_F6 = config.GetFloat(pModelName, "field_F6");
				pSettings->policeScannerManufacturerSound = config.GetHash(pModelName, "policeScannerManufacturerSound", SOUND_LIST_SOUNDS);
				pSettings->policeScannerModelSound = config.GetHash(pModelName, "policeScannerModelSound", SOUND_LIST_SOUNDS);
				pSettings->policeScannerVehicleCategorySound = config.GetHash(pModelName, "policeScannerVehicleCategorySound", SOUND_LIST_SOUNDS);
				pSettings->gearTransmissionSound = config.GetHash(pModelName, "gearTransmissionSound", SOUND_LIST_SOUNDS);
				pSettings->floatAsInt_multiplier1200_10A = (int)(config.GetFloat(pModelName, "floatAsInt_multiplier1200_10A") * 1200);
				pSettings->floatAsInt_multiplier1200_10E = (int)(config.GetFloat(pModelName, "floatAsInt_multiplier1200_10E") * 1200);
				pSettings->floatAsInt_multiplier1200_112 = (int)(config.GetFloat(pModelName, "floatAsInt_multiplier1200_112") * 1200);
				pSettings->floatAsInt_116 = (int)(config.GetFloat(pModelName, "floatAsInt_116") * 100);
				pSettings->field_11A = config.GetInt(pModelName, "field_11A");
				pSettings->floatAsInt_11E = (int)(config.GetFloat(pModelName, "floatAsInt_11E") * 100);
				pSettings->floatAsInt_122 = (int)(config.GetFloat(pModelName, "floatAsInt_122") * 100);
				pSettings->floatAsInt_126 = (int)(config.GetFloat(pModelName, "floatAsInt_126") * 100);
				pSettings->jumpLandSound = config.GetHash(pModelName, "jumpLandSound", SOUND_LIST_SOUNDS);
				pSettings->field_12E = config.GetInt(pModelName, "field_12E");
				pSettings->field_132 = config.GetInt(pModelName, "field_132");
				pSettings->ignitionSound = config.GetHash(pModelName, "ignitionSound", SOUND_LIST_SOUNDS);
				pSettings->engineShutDownSound = config.GetHash(pModelName, "engineShutDownSound", SOUND_LIST_SOUNDS);
				pSettings->field_13E = config.GetInt(pModelName, "field_13E");
				pSettings->field_13F = config.GetInt(pModelName, "field_13F");
				pSettings->field_140 = config.GetInt(pModelName, "field_140");
				pSettings->field_141 = config.GetInt(pModelName, "field_141");
				pSettings->indicatorVehicleOn = config.GetHash(pModelName, "indicatorVehicleOn", SOUND_LIST_SOUNDS);
				pSettings->indicatorVehicleOff = config.GetHash(pModelName, "indicatorVehicleOff", SOUND_LIST_SOUNDS);
				pSettings->engineCoolingFan = config.GetHash(pModelName, "engineCoolingFan", SOUND_LIST_SOUNDS);
				pSettings->handbrakeSound_14E = config.GetHash(pModelName, "handbrakeSound_14E", SOUND_LIST_SOUNDS);
				pSettings->sound_152 = config.GetHash(pModelName, "sound_152", SOUND_LIST_SOUNDS);
				pSettings->sound_156 = config.GetHash(pModelName, "sound_156", SOUND_LIST_SOUNDS);
				pSettings->handbrakeSound_15A = config.GetHash(pModelName, "handbrakeSound_15A", SOUND_LIST_SOUNDS);
				pSettings->field_15E = config.GetInt(pModelName, "field_15E");
				pSettings->field_15F = config.GetInt(pModelName, "field_15F");
				pSettings->field_160 = config.GetInt(pModelName, "field_160");
			}
			else if (structType == 4)	// bikes
			{
				tVehicleAudioSettingsHeli* pSettings = &audioSettings.heli;
				pSettings->structType = structType;
				pSettings->field_1 = config.GetInt(pModelName, "field_1");
				pSettings->flags = config.GetInt(pModelName, "flags");
				pSettings->rotorSound = config.GetHash(pModelName, "rotorSound", SOUND_LIST_SOUNDS);
				pSettings->rearRotorSound = config.GetHash(pModelName, "rearRotorSound", SOUND_LIST_SOUNDS);
				pSettings->exHaustSound = config.GetHash(pModelName, "exHaustSound", SOUND_LIST_SOUNDS);
				pSettings->bankSound = config.GetHash(pModelName, "bankSound", SOUND_LIST_SOUNDS);
				pSettings->internalCabinToneSound = config.GetHash(pModelName, "internalCabinToneSound", SOUND_LIST_SOUNDS);
				pSettings->field_1E = config.GetFloat(pModelName, "field_1E");
				pSettings->bankAngleVolumeSound = config.GetHash(pModelName, "bankAngleVolumeSound", SOUND_LIST_CURVES);
				pSettings->bankThrottleVolumeSound = config.GetHash(pModelName, "bankThrottleVolumeSound", SOUND_LIST_CURVES);
				pSettings->bankThrottlePitchCurveSound = config.GetHash(pModelName, "bankThrottlePitchCurveSound", SOUND_LIST_CURVES);
				pSettings->rotorThrottleVolumeSound = config.GetHash(pModelName, "rotorThrottleVolumeSound", SOUND_LIST_CURVES);
				pSettings->rotorThrottlePitchCurveSound = config.GetHash(pModelName, "rotorThrottlePitchCurveSound", SOUND_LIST_CURVES);
				pSettings->rotorThrottleGapSound = config.GetHash(pModelName, "rotorThrottleGapSound", SOUND_LIST_CURVES);
				pSettings->rearRotorThrottleVolumeSound = config.GetHash(pModelName, "rearRotorThrottleVolumeSound", SOUND_LIST_CURVES);
				pSettings->exhaustThrottleVolumeSound = config.GetHash(pModelName, "exhaustThrottleVolumeSound", SOUND_LIST_CURVES);
				pSettings->exhaustThrottlePitchCurveSound = config.GetHash(pModelName, "exhaustThrottlePitchCurveSound", SOUND_LIST_CURVES);
				pSettings->field_46 = config.GetInt(pModelName, "field_46");
				pSettings->field_48 = config.GetInt(pModelName, "field_48");
				pSettings->floatAsInt_4A = (int)(config.GetFloat(pModelName, "floatAsInt_4A") * 100);
				pSettings->field_4C = config.GetInt(pModelName, "field_4C");
				pSettings->field_4E = config.GetInt(pModelName, "field_4E");
				pSettings->floatAsInt_50 = (int)(config.GetFloat(pModelName, "floatAsInt_50") * 100);
				pSettings->field_52 = config.GetInt(pModelName, "field_52");
				pSettings->field_54 = config.GetInt(pModelName, "field_54");
				pSettings->floatAsInt_56 = (int)(config.GetFloat(pModelName, "floatAsInt_56") * 100);
				pSettings->field_58 = config.GetFloat(pModelName, "field_58");
				pSettings->field_5C = config.GetFloat(pModelName, "field_5C");
				pSettings->throttleResonance1Sound = config.GetHash(pModelName, "throttleResonance1Sound", SOUND_LIST_CURVES);
				pSettings->field_64 = config.GetFloat(pModelName, "field_64");
				pSettings->field_68 = config.GetFloat(pModelName, "field_68");
				pSettings->throttleResonance2Sound = config.GetHash(pModelName, "throttleResonance2Sound", SOUND_LIST_CURVES);
				pSettings->bankingResonanceCurveSound = config.GetHash(pModelName, "bankingResonanceCurveSound", SOUND_LIST_CURVES);
				pSettings->rotorVolumeStartupCurveSound = config.GetHash(pModelName, "rotorVolumeStartupCurveSound", SOUND_LIST_CURVES);
				pSettings->bladeVolumeStartupCurveSound = config.GetHash(pModelName, "bladeVolumeStartupCurveSound", SOUND_LIST_CURVES);
				pSettings->rotorPitchStartupCurveSound = config.GetHash(pModelName, "rotorPitchStartupCurveSound", SOUND_LIST_CURVES);
				pSettings->rearRotorVolumeStartupCurveSound = config.GetHash(pModelName, "rearRotorVolumeStartupCurveSound", SOUND_LIST_CURVES);
				pSettings->exhaustVolumeStartupCurveSound = config.GetHash(pModelName, "exhaustVolumeStartupCurveSound", SOUND_LIST_CURVES);
				pSettings->rotorGapStartupCurveSound = config.GetHash(pModelName, "rotorGapStartupCurveSound", SOUND_LIST_CURVES);
				pSettings->shotStartSound = config.GetHash(pModelName, "shotStartSound", SOUND_LIST_SOUNDS);
				pSettings->field_90 = config.GetInt(pModelName, "field_90", SOUND_LIST_SOUNDS);
				pSettings->field_92 = config.GetInt(pModelName, "field_92", SOUND_LIST_SOUNDS);
				pSettings->floatAsInt_94 = (int)(config.GetFloat(pModelName, "floatAsInt_94") * 100);
				pSettings->field_96 = config.GetInt(pModelName, "field_96");
				pSettings->field_98 = config.GetInt(pModelName, "field_98");
				pSettings->floatAsInt_9A = config.GetInt(pModelName, "floatAsInt_9A") * 100;
				pSettings->policeScannerManufacturerSound = config.GetHash(pModelName, "policeScannerManufacturerSound", SOUND_LIST_SOUNDS);
				pSettings->policeScannerModelSound = config.GetHash(pModelName, "policeScannerModelSound", SOUND_LIST_SOUNDS);
				pSettings->policeScannerVehicleCategorySound = config.GetHash(pModelName, "policeScannerVehicleCategorySound", SOUND_LIST_SOUNDS);
				pSettings->field_A8 = config.GetInt(pModelName, "field_A8");
				pSettings->field_A9 = config.GetInt(pModelName, "field_A9");
				pSettings->doorOpenSound = config.GetHash(pModelName, "doorOpenSound", SOUND_LIST_SOUNDS);
				pSettings->doorCloseSound = config.GetHash(pModelName, "doorCloseSound", SOUND_LIST_SOUNDS);
				pSettings->doorLimitSound = config.GetHash(pModelName, "doorLimitSound", SOUND_LIST_SOUNDS);
				pSettings->damageLoopSound = config.GetHash(pModelName, "damageLoopSound", SOUND_LIST_SOUNDS);
			}
			else if (structType == 7)	// boats
			{
				tVehicleAudioSettingsBoat* pSettings = &audioSettings.boat;
				pSettings->structType = structType;
				pSettings->field_1 = config.GetInt(pModelName, "field_1");
				pSettings->flags = config.GetInt(pModelName, "flags");

				pSettings->engineLoopSound = config.GetHash(pModelName, "engineLoopSound", SOUND_LIST_SOUNDS);
				pSettings->engineVolumeSound = config.GetHash(pModelName, "engineVolumeSound", SOUND_LIST_CURVES);
				pSettings->enginePitchSound_12 = config.GetHash(pModelName, "enginePitchSound_12", SOUND_LIST_CURVES);
				pSettings->engine2loopSound = config.GetHash(pModelName, "engine2loopSound", SOUND_LIST_SOUNDS);
				pSettings->engine2volumeSound = config.GetHash(pModelName, "engine2volumeSound", SOUND_LIST_CURVES);
				pSettings->enginePitchSound_1E = config.GetHash(pModelName, "enginePitchSound_1E", SOUND_LIST_CURVES);
				pSettings->lowResonanceLoopSound = config.GetHash(pModelName, "lowResonanceLoopSound", SOUND_LIST_SOUNDS);
				pSettings->resonanceVolumeSound = config.GetHash(pModelName, "resonanceVolumeSound", SOUND_LIST_CURVES);
				pSettings->enginePitchSound_2A = config.GetHash(pModelName, "enginePitchSound_2A", SOUND_LIST_CURVES);
				pSettings->idleLoopSound = config.GetHash(pModelName, "idleLoopSound", SOUND_LIST_SOUNDS);
				pSettings->idleResonanceVolumeSound = config.GetHash(pModelName, "idleResonanceVolumeSound", SOUND_LIST_CURVES);
				pSettings->enginePitchSound_36 = config.GetHash(pModelName, "enginePitchSound_36", SOUND_LIST_CURVES);
				pSettings->waterTurbulanceSound = config.GetHash(pModelName, "waterTurbulanceSound", SOUND_LIST_SOUNDS);
				pSettings->waterTurbulanceVolumeSound = config.GetHash(pModelName, "waterTurbulanceVolumeSound", SOUND_LIST_CURVES);
				pSettings->field_42 = config.GetInt(pModelName, "field_42");
				pSettings->field_46 = config.GetFloat(pModelName, "field_46");
				pSettings->field_4A = config.GetFloat(pModelName, "field_4A");
				pSettings->floatAsInt_4E = (int)(config.GetFloat(pModelName, "floatAsInt_4E") * 100);
				pSettings->floatAsInt_52 = (int)(config.GetFloat(pModelName, "floatAsInt_52") * 100);
				pSettings->field_56 = config.GetFloat(pModelName, "field_56");
				pSettings->field_5A = config.GetFloat(pModelName, "field_5A");
				pSettings->floatAsInt_5E = (int)(config.GetFloat(pModelName, "floatAsInt_5E") * 100);
				pSettings->floatAsInt_62 = (int)(config.GetFloat(pModelName, "floatAsInt_62") * 100);
				pSettings->field_66 = config.GetFloat(pModelName, "field_66");
				pSettings->field_6A = config.GetFloat(pModelName, "field_6A");
				pSettings->floatAsInt_6E = (int)(config.GetFloat(pModelName, "floatAsInt_6E") * 100);
				pSettings->floatAsInt_72 = (int)(config.GetFloat(pModelName, "floatAsInt_72") * 100);
				pSettings->field_76 = config.GetFloat(pModelName, "field_76");
				pSettings->field_7A = config.GetFloat(pModelName, "field_7A");
				pSettings->floatAsInt_7E = (int)(config.GetFloat(pModelName, "floatAsInt_7E") * 100);
				pSettings->floatAsInt_82 = (int)(config.GetFloat(pModelName, "floatAsInt_82") * 100);
				pSettings->floatAsInt_86 = (int)(config.GetFloat(pModelName, "floatAsInt_86") * 100);
				pSettings->field_8A = config.GetFloat(pModelName, "field_8A");
				pSettings->field_8E = config.GetFloat(pModelName, "field_8E");
				pSettings->floatAsInt_92 = (int)(config.GetFloat(pModelName, "floatAsInt_92") * 100);
				pSettings->floatAsInt_96 = (int)(config.GetFloat(pModelName, "floatAsInt_96") * 100);
				pSettings->linearRise_9A = config.GetHash(pModelName, "linearRise_9A", SOUND_LIST_CURVES);
				pSettings->field_9E = config.GetInt(pModelName, "field_9E");
				pSettings->linearRise_A2 = config.GetHash(pModelName, "linearRise_A2", SOUND_LIST_CURVES);
				pSettings->field_A6 = config.GetInt(pModelName, "field_A6");
				pSettings->policeScannerManufacturerSound = config.GetHash(pModelName, "policeScannerManufacturerSound", SOUND_LIST_SOUNDS);
				pSettings->policeScannerModelSound = config.GetHash(pModelName, "policeScannerModelSound", SOUND_LIST_SOUNDS);
				pSettings->policeScannerVehicleCategorySound = config.GetHash(pModelName, "policeScannerVehicleCategorySound", SOUND_LIST_SOUNDS);
				pSettings->field_B6 = config.GetInt(pModelName, "field_B6");
				pSettings->field_B7 = config.GetInt(pModelName, "field_B7");
				pSettings->hornSound = config.GetHash(pModelName, "hornSound", SOUND_LIST_SOUNDS);
				pSettings->materialSound = config.GetHash(pModelName, "materialSound", SOUND_LIST_GAME);
				pSettings->ignitionSound = config.GetHash(pModelName, "ignitionSound", SOUND_LIST_SOUNDS);
				pSettings->shutDownSound = config.GetHash(pModelName, "shutDownSound", SOUND_LIST_SOUNDS);
				pSettings->field_C8 = config.GetInt(pModelName, "field_C8");
			}
			else
				printf_MessageBox(
					"gtaiv_vehicleAudioSettings.cfg: model with name %s has structType %d which is unknown.",
					pModelName,
					structType
				);


			/////////////////////

			this->ms_VehicleAudioEntries.gta_iv->push_back(audioSettings);

			// printf_MessageBox("model name: %s ID: %d extInfo: 0x%X", pModelName, modelID, pModelExtInfo);
		}
		else
		{
			if (bModelMustExist)
			{
				printf_MessageBox(
					"gtaiv_vehicleAudioSettings.ini: model with name %s does not exist.",
					pModelName
				);

				return;
			}
		}

		// go to next model name
		do
			pModelName++;
		while (*pModelName);

		pModelName++;
	}
	
	config.Close();

#if FALSE
	{
		FILE* fp = fopen("dinghyNew.bin", "wb");
		int modelID;
		CBaseModelInfo* pModelInfo = CModelInfo::GetModelInfo("dinghy", &modelID);

		tVehicleAudioSettingsHeli* ptr
			= &GetAudioSettingsForVehicle(modelID)->heli;



		fwrite(ptr, sizeof(tVehicleAudioSettingsBoat), 1, fp);

		fclose(fp);
	}
#endif
}
#endif

// Loads vehicle audio settings
void CVehicleAudioLoader::LoadVehicleAudioSettings()
{
	MAKE_VAR_GAME_VERSION();

	if (!ms_bVehicleAudioLoaderEnabled)
		return;

	std::string AudioSettingsPath =
		g_LimitAdjuster.GetPathToFlaFileFromRootDirectory(this->ms_AudioSettingsPath.c_str());

	if (this->IsGameVersionUsingOldFormat(gameVersion))
	{
		this->LoadVehicleAudioSettings_configFile(
			AudioSettingsPath.c_str(),
			true,
			&CVehicleAudioLoader::LoadVehicleAudioSettings_GTA_old
		);
	}
	else if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		this->LoadVehicleAudioSettings_configFile(
			AudioSettingsPath.c_str(),
			true,
			&CVehicleAudioLoader::LoadVehicleAudioSettings_GTA_SA
		);
	}
#if IS_PLATFORM_WIN_X86
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
	{
		using namespace Game_GTAIV;
		this->UnloadVehicleAudioSettings();

		this->LoadVehicleAudioSettings_GTA_IV_EFLC(
			AudioSettingsPath.c_str(),
			true
		);
		
		auto filenamePath = g_LimitAdjuster.GetPathToFlaFileFromRootDirectory("pc\\audio\\config\\addedVehicleAudioSettings.ini");

		this->LoadVehicleAudioSettings_GTA_IV_EFLC(
			filenamePath.c_str(),
			true);
		
		if (pGameEpisodeNum)
		{
			const char* filename = nullptr;
			bool bNotGTA_EFLC = !CGameVersion::IsAny_GTA_EFLC(gameVersion);			

			if (*pGameEpisodeNum == 1)
			{
				if (bNotGTA_EFLC)
					filename = "DLC\\TLAD\\content\\pc\\audio\\config\\TLAD_vehicleAudioSettings.ini";
				else
					filename = "TLAD\\pc\\audio\\config\\TLAD_vehicleAudioSettings.ini";
			}
			else if (*pGameEpisodeNum == 2)
			{
				if (bNotGTA_EFLC)
					filename = "DLC\\TBoGT\\content\\pc\\audio\\config\\TBoGT_vehicleAudioSettings.ini";
				else
					filename = "TBoGT\\pc\\audio\\config\\TBoGT_vehicleAudioSettings.ini";
			}

			if (filename)
			{
				auto filenamePath = g_LimitAdjuster.GetPathToFlaFileFromRootDirectory(filename);
				this->LoadVehicleAudioSettings_GTA_IV_EFLC(filenamePath.c_str(), true);
			}
		}
	}
#endif
}

// Applies vehicle audio loader
void CVehicleAudioLoader::ApplyVehicleAudioLoaderIfEnabled()
{
	MAKE_VAR_GAME_VERSION();	

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
	{	
		if (!this->ms_bVehicleAudioLoaderEnabled)
			return;

		using namespace Game_GTAVC;

		// DumpDefaultAudioSettings();
		// g_LimitAdjuster.TerminateProcess();

		this->ms_VehicleAudioEntries.gta_old = new std::vector<tVehicleAudioSettings_extended>;

		CTheScripts__bPlayerHasMetDebbieHarry = (bool*)0xA10B7F;

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5F527A), &patch_cAudioManager__ProcessVehicle_setAudioID);
		Address_cAudioManager__ProcessVehicle_setAudioID_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5F528B);

		/////////////
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5EEA10), &patch_cAudioManager__ProcessVehicleOneShots_0);
		Address_cAudioManager__ProcessVehicleOneShots_0_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5EEA24);

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5EEAF6), &patch_cAudioManager__ProcessVehicleOneShots_1);
		Address_cAudioManager__ProcessVehicleOneShots_1_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5EEB0A);

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5F0420), &patch_cAudioManager__ProcessVehicleSirenOrAlarm_0);
		Address_cAudioManager__ProcessVehicleSirenOrAlarm_0_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5F0430);

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5F0436), &patch_cAudioManager__ProcessVehicleSirenOrAlarm_1);
		Address_cAudioManager__ProcessVehicleSirenOrAlarm_1_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5F0446);

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5F044B), &patch_cAudioManager__ProcessVehicleSirenOrAlarm_2);
		Address_cAudioManager__ProcessVehicleSirenOrAlarm_2_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5F045B);

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5F0461), &patch_cAudioManager__ProcessVehicleSirenOrAlarm_3);
		Address_cAudioManager__ProcessVehicleSirenOrAlarm_3_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5F0471);

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5F06BC), &patch_cAudioManager__ProcessVehicleHorn_0);
		Address_cAudioManager__ProcessVehicleHorn_0_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5F06CC);

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5F06E1), &patch_cAudioManager__ProcessVehicleHorn_1);
		Address_cAudioManager__ProcessVehicleHorn_1_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5F06F1);

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5F142A), &patch_cAudioManager__ProcessPlayersVehicleEngine_0);
		Address_cAudioManager__ProcessPlayersVehicleEngine_0_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5F143C);

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5F279C), &patch_cAudioManager__ProcessVehicleEngine_0);
		Address_cAudioManager__ProcessVehicleEngine_0_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5F27AD);

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5F27F5), &patch_cAudioManager__ProcessVehicleEngine_1);
		Address_cAudioManager__ProcessVehicleEngine_1_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5F2805);

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5F2820), &patch_cAudioManager__ProcessVehicleEngine_2);
		Address_cAudioManager__ProcessVehicleEngine_2_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5F2831);

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x5F2876), &patch_cAudioManager__ProcessVehicleEngine_3);
		Address_cAudioManager__ProcessVehicleEngine_3_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x5F2886);
				
		////////////////////////////////

		CPatch::RedirectMethod(0x5B8520, &CVehicle_audioExt::UsesSiren);

		CPatch::RedirectCode(0x5FA48C, &patch_cMusicManager__GetCarTuning_5FA48C);

		CPatch::RedirectCode(0x5FB722, &patch_cMusicManager__ServiceGameMode_5FB722);
		CPatch::RedirectCode(0x5FB7EF, &patch_cMusicManager__ServiceGameMode_5FB7EF);

		CPatch::RedirectCode(0x5F56CB, &patch_cAudioManager__ProcessVehicle_5F56CB);
		CPatch::RedirectCode(0x5F5708, &patch_cAudioManager__ProcessVehicle_5F5708);

		////////////////////////////////


		CPatch::RedirectCode(0x579081, &run_LoadVehicleAudioSettings);

		CGenericLogStorage::SaveTextLn("Vehicle audio loader is enabled");
		CGenericLogStorage::WriteLineSeparator();
	}
	else if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion) || CGameVersion::Is_GTA_SA_1_0_1_EU_WIN_X86(gameVersion))
	{
		if (!this->ms_bVehicleAudioLoaderEnabled)
			return;

		using namespace Game_GTASA;
		this->ms_VehicleAudioEntries.gta_sa = new std::vector<tVehicleAudioSettings_DefinitiveEdition>;

		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			CPatch::RedirectCode(0x5B9010, &run_LoadVehicleAudioSettings);
			
			CPatch::RedirectCode(0x4F77B4, &patch_CAEVehicleAudioEntity__Initialise_4F77B4);
			Address_CAEVehicleAudioEntity__Initialise_goBack = 0x4F77DA;
			CPatch::NOPinstructions(0x4F77EF, 1);

			CPatch::RedirectMethod(0x4F5C10, &CAEVehicleAudioEntity::GetVehicleAudioSettings);			
		}
		else if (CGameVersion::Is_GTA_SA_1_0_1_EU_WIN_X86(gameVersion))
		{			
			CPatch::RedirectCode(0x14D2D33, &patch_run_LoadVehicleAudioSettings);
			
			CPatch::RedirectCode(0x4F7C14, &patch_CAEVehicleAudioEntity__Initialise_4F77B4);
			Address_CAEVehicleAudioEntity__Initialise_goBack = 0x4F7C3A;
			CPatch::NOPinstructions(0x4F7C4F, 1);

			CPatch::RedirectMethod(0x4F6070, &CAEVehicleAudioEntity::GetVehicleAudioSettings);		
		}

		CGenericLogStorage::SaveTextLn("Vehicle audio loader is enabled");
		CGenericLogStorage::WriteLineSeparator();
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
	{
		using namespace Game_GTAIV;

		if(this->ms_bVehicleAudioLoaderEnabled)
			this->ms_VehicleAudioEntries.gta_iv = new std::vector<tVehicleAudioSettings>;

		// CVehicleModelInfo__CVehicleStructure__m_pInfoPool and sound containers
		if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86)
		{
			CVehicleModelInfo__CVehicleStructure__m_pInfoPool = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x1469164);

			SoundContainerPtrs = SoundContainerPtrs_GTA_IV_1_0_4_0;
			Address_CSoundContainer_GetAudioSettingsByName = g_mCalc.GetCurrentVAbyPreferedVA(0x789EA0);
			Address_CSoundContainer_GetAudioSettingsByHash = g_mCalc.GetCurrentVAbyPreferedVA(0x7899B0);
		}
		else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		{
			CVehicleModelInfo__CVehicleStructure__m_pInfoPool = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x16D6594);
			pGameEpisodeNum = (uint32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x10F8078);

			SoundContainerPtrs = SoundContainerPtrs_GTA_IV_1_0_7_0;
			Address_CSoundContainer_GetAudioSettingsByName = g_mCalc.GetCurrentVAbyPreferedVA(0xCE3C80);
			Address_CSoundContainer_GetAudioSettingsByHash = g_mCalc.GetCurrentVAbyPreferedVA(0xCE3770);
		}
		else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		{
			CVehicleModelInfo__CVehicleStructure__m_pInfoPool = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x1401BCC);
			pGameEpisodeNum = (uint32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x112D788);

			SoundContainerPtrs = SoundContainerPtrs_GTA_IV_1_0_8_0;
			Address_CSoundContainer_GetAudioSettingsByName = g_mCalc.GetCurrentVAbyPreferedVA(0x7AC160);
			Address_CSoundContainer_GetAudioSettingsByHash = g_mCalc.GetCurrentVAbyPreferedVA(0x7ABC70);
		}
		else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
		{
			CVehicleModelInfo__CVehicleStructure__m_pInfoPool = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0x1606B44);
			pGameEpisodeNum = (uint32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x10619D8);

			SoundContainerPtrs = SoundContainerPtrsGTA_EFLC_1_1_2_0;
			Address_CSoundContainer_GetAudioSettingsByName = g_mCalc.GetCurrentVAbyPreferedVA(0x7AAF50);
			Address_CSoundContainer_GetAudioSettingsByHash = g_mCalc.GetCurrentVAbyPreferedVA(0x7AAA40);
		}

		// when vehicle audio loader enabled
		if (this->ms_bVehicleAudioLoaderEnabled)
		{
			// Register CVehicleAudioLoader::LoadVehicleAudioSettings
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86)
			{
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xA717A9), &patch_LoadVehicleAudioSettings);

				// code for getting the settings of car/bikes
				Address_GetAudioSettingsForVehicle_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x8FB770);
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x8FB760), &patch_in_GetAudioSettingsForVehicle);

				// code for getting the settings of helicopters
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x8FBD0A), &patch_in_GetAudioSettingsForHelicopter);
				Address_GetAudioSettingsForHelicopter_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x8FBD1A);

				// code for getting the settings of boats
				CPatch::NOPinstructions(g_mCalc.GetCurrentVAbyPreferedVA(0xC60905), 5);
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xC60912), &patch_in_GetAudioSettingsForBoat);
				Address_GetAudioSettingsForBoat_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0xC6091D);
			}
			// Register CVehicleAudioLoader::LoadVehicleAudioSettings
			else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			{
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xBEA879), &patch_LoadVehicleAudioSettings);

				// code for getting the settings of car/bikes
				Address_GetAudioSettingsForVehicle_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0xAEC510);
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xAEC500), &patch_in_GetAudioSettingsForVehicle);

				// code for getting the settings of helicopters
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xAECAAA), &patch_in_GetAudioSettingsForHelicopter);
				Address_GetAudioSettingsForHelicopter_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0xAECABA);

				// code for getting the settings of boats
				CPatch::NOPinstructions(g_mCalc.GetCurrentVAbyPreferedVA(0xCCF785), 5);
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xCCF792), &patch_in_GetAudioSettingsForBoat);
				Address_GetAudioSettingsForBoat_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0xCCF79D);
			}
			else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xA4A2B9), &patch_LoadVehicleAudioSettings);

				// code for getting the settings of car/bikes				
				Address_GetAudioSettingsForVehicle_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x826420);
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x826410), &patch_in_GetAudioSettingsForVehicle);

				// code for getting the settings of helicopters
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x8269BA), &patch_in_GetAudioSettingsForHelicopter);
				Address_GetAudioSettingsForHelicopter_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0x8269CA);

				// code for getting the settings of boats
				CPatch::NOPinstructions(g_mCalc.GetCurrentVAbyPreferedVA(0xA583E5), 5);
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xA583F2), &patch_in_GetAudioSettingsForBoat);
				Address_GetAudioSettingsForBoat_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0xA583FD);				
			}
			else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
			{
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xB53B99), &patch_LoadVehicleAudioSettings);

				// code for getting the settings of car/bikes
				Address_GetAudioSettingsForVehicle_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0xB1A350);
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xB1A340), &patch_in_GetAudioSettingsForVehicle);

				// code for getting the settings of helicopters
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xB1A8EA), &patch_in_GetAudioSettingsForHelicopter);
				Address_GetAudioSettingsForHelicopter_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0xB1A8FA);

				// code for getting the settings of boats
				CPatch::NOPinstructions(g_mCalc.GetCurrentVAbyPreferedVA(0xB3F4B5), 5);
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xB3F4C2), &patch_in_GetAudioSettingsForBoat);
				Address_GetAudioSettingsForBoat_pointToReturn = g_mCalc.GetCurrentVAbyPreferedVA(0xB3F4CD);
			}

			/*
			
			*/
			// Debugging
			/*
			Address_CE3777 = g_mCalc.GetCurrentVAbyPreferedVA(0xCE3777);

			CPatch::RedirectCode(
			g_mCalc.GetCurrentVAbyPreferedVA(0xCE3770),
			&patch_GetAudioEntryByHash_CE3770
			);
			*/

			CGenericLogStorage::SaveTextLn("Vehicle audio loader is enabled");
			CGenericLogStorage::WriteLineSeparator();
		}

		if (this->ms_bEnableDumpingDefaultSettings)
		{
			if(gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86)
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xA717A9), &patch_dumpDefaultAudioSettings);
			else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xBEA879), &patch_dumpDefaultAudioSettings);
			else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xA4A2B9), &patch_dumpDefaultAudioSettings);
			else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
				CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xB53B99), &patch_dumpDefaultAudioSettings);

			CGenericLogStorage::SaveTextLn("Dumping default vehicle audio settings is enabled");
			CGenericLogStorage::WriteLineSeparator();
		}
	}
#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		if (!this->ms_bVehicleAudioLoaderEnabled)
			return;

		using namespace Game_GTASA;
		this->ms_VehicleAudioEntries.gta_sa = new std::vector<tVehicleAudioSettings_DefinitiveEdition>;

		if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		{
			Address_CVehicleModelInfo__SetupCommonData_loop = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x468BE2));

			CPatch::RedirectCodeEx(
				INSTRUCTION_SET_THUMB,
				g_mCalc.GetCurrentVAbyPreferedVA(0x468C00),
				(void*)&patch_CVehicleModelInfo__SetupCommonData_468C00
			);

			////
			Address_CAEVehicleAudioEntity__Initialise_goBack = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3AC750));

			CPatch::RedirectCodeEx(
				INSTRUCTION_SET_THUMB,
				g_mCalc.GetCurrentVAbyPreferedVA(0x3AC71E),
				(void*)&patch_CAEVehicleAudioEntity__Initialise_3AC71E
			);

			// CPatch::RedirectCode(0x4F77B4, &patch_CAEVehicleAudioEntity__Initialise_4F77B4);
			// Address_CAEVehicleAudioEntity__Initialise_goBack = 0x4F77DA;
			/// CPatch::NOPinstructions(0x4F77EF, 1);

			uintptr_t pGetVehicleAudioSettings = (uintptr_t)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN21CAEVehicleAudioEntity23GetVehicleAudioSettingsEs"
			);

			CPatch::RedirectMethod(
				pGetVehicleAudioSettings,
				&CAEVehicleAudioEntity::GetVehicleAudioSettings);
		}
		
		CGenericLogStorage::SaveTextLn("Vehicle audio loader is enabled");
		CGenericLogStorage::WriteLineSeparator();
	}
#endif
	else
		return;
}

bool someFunction2(unsigned int ID)
{
	return ID == 3
	|| ID - 8 <= 3
	|| ID == 31;
};

bool someFunction3(unsigned int value)
{
	return value - 24 >= 0xFFFFFFFB;
}
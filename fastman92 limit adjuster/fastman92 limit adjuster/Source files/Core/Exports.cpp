/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "../ForOtherProjects/FLA_required/Exports.h"

#include "../Core/ProjectConstants.h"
#include "../Core/LimitAdjuster.h"

#include "../Modules/CVehicleAudioLoader.h"
#include "../Modules/FileTypeManager.h"
#include "../Modules/OtherLimits.h"
#include "../Modules/IMGlimits.h"
#include "../Modules/ShadowLimits.h"
#include "../Modules/WeaponLimits.h"

#include "../Core/FormattedOutput.h"

using namespace Game;

extern bool CLEOloadingImplemented;

extern "C" {

	// Count of file IDs
	F92_LA_API int32_t F92_LA_CONVENTION GetNumberOfFileIDs()
	{
		return g_fileIDlimits.GetNumberOfFileIDs();
	}

	// Returns model info, prev file ID
	F92_LA_API int32_t F92_LA_CONVENTION GetFileInfoPrevFileID(int32_t fileID)
	{
		return g_fileIDlimits.GetFileInfoPrev(fileID);
	}

	// Returns model info, next file ID
	F92_LA_API int32_t F92_LA_CONVENTION GetFileInfoNextFileID(int32_t fileID)
	{
		return g_fileIDlimits.GetFileInfoNext(fileID);
	}

	// Returns model info, next on CD file ID
	F92_LA_API int32_t F92_LA_CONVENTION GetFileInfoNextOnCDfileID(int32_t fileID)
	{
		return g_fileIDlimits.GetFileInfoNextOnCD(fileID);
	}

	// Sets file info, Prev file ID 
	F92_LA_API void F92_LA_CONVENTION SetFileInfoPrevFileID(int32_t fileID, int32_t newValue)
	{
		g_fileIDlimits.SetFileInfoPrev(fileID, newValue);
	}

	// Sets file info, Next file ID
	F92_LA_API void F92_LA_CONVENTION SetFileInfoNextFileID(int32_t fileID, int32_t newValue)
	{
		g_fileIDlimits.SetFileInfoNext(fileID, newValue);
	}

	// Sets file info, NextOnCd file ID
	F92_LA_API void F92_LA_CONVENTION SetFileInfoNextOnCDfileID(int32_t fileID, int32_t newValue)
	{
		g_fileIDlimits.SetFileInfoNextOnCD(fileID, newValue);
	}

	// Returns true if handling of enhanced IMG archives is enabled
	F92_LA_API bool F92_LA_CONVENTION IsHandlingOfEnhancedIMGarchivesEnabled()
	{
		return g_IMGlimits.bHandlingOfNewEnhancedFormatOfImgArchivesEnabled;
	}

#ifdef IS_PLATFORM_WIN_X86
	// Loads CD directory in GTA SA. Works only if enhanced IMG archives are enabled!
	F92_LA_API void F92_LA_CONVENTION LoadCdDirectoryInGTASA(
		const tImgDescriptorInGTASA *pIMGdescriptor,
		int imgId,
		tGTASAimgLoadingCall* pLoadingCall
			)
	{
		MAKE_VAR_GAME_VERSION();

		if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		{
			Game_GTASA::tGTASAimgLoadingCallPriv loadingCallPriv = { 0 };
			loadingCallPriv.pBasicLoadingCall = pLoadingCall;
			
			Game_GTASA::CStreamingAddition::LoadCdDirectoryAdvanced(pIMGdescriptor, imgId, loadingCallPriv);
		}
	}

	// Sets CdStreamStream Release Channel function
	F92_LA_API void cdecl SetCdStreamReleaseChannelfUsedByTheFLA(void(__cdecl*func)(void* pStream))
	{
		Game_GTASA::CStreamingAddition::ReleaseChannel = func;
	}
#endif

	// Sets vehicle audio settings path
	F92_LA_API void F92_LA_CONVENTION SetVehicleAudioSettingsPath(const char* filename)
	{
		g_vehicleAudioLoader.SetVehicleAudioSettingsPath(filename);
	}

	// Loads vehicle audio settings
	F92_LA_API void F92_LA_CONVENTION LoadVehicleAudioSettings()
	{
		g_vehicleAudioLoader.LoadVehicleAudioSettings();
	}

	// Do Mod loader action
	F92_LA_API void F92_LA_CONVENTION DoModLoaderAction(int action){}

	// Returns weapon parent type
	F92_LA_API int F92_LA_CONVENTION GetWeaponHighestParentType(int weaponType)
	{
		if (g_weaponLimits.WeaponTypes)
			return CWeaponInfo_generic::GetWeaponHighestParentType(weaponType);
		else
			return -1;
	}

	// Returns weapon name
	// Can only return a name, if weapon limits are enabled and weapon config DAT got loaded.
	F92_LA_API const char* F92_LA_CONVENTION GetWeaponName(int weaponType)
	{
		const WeaponLimits* pWeaponLimits = &g_weaponLimits;

		if (pWeaponLimits->WeaponTypes
			&& weaponType >= 0
			&& (unsigned int)weaponType < pWeaponLimits->NumberOfWeaponTypes)
			return CWeaponInfo_generic::GetWeaponTypeInfo(weaponType)->Name;
		else
			return 0;
	}

	// Returns the count of weapon infos
	F92_LA_API unsigned int F92_LA_CONVENTION GetCountOfWeaponInfos()
	{
		return g_weaponLimits.CountOfWeaponInfos;
	}

	// Returns the number of possible weapon types
	F92_LA_API unsigned int F92_LA_CONVENTION GetNumberOfWeaponTypes()
	{
		return g_weaponLimits.NumberOfWeaponTypes;
	}

	// Returns project version
	F92_LA_API const char* F92_LA_CONVENTION GetProjectVersion()
	{
		return PROJECT_VERSION_ONLY;
	}

	// Returns offset of CRealTimeShadowManager::m_realTimeShadowPool
	F92_LA_API unsigned int GetOffset_CRealTimeShadowManager_m_realTimeShadowPool()
	{
		using namespace Game_GTASA;
		return CRealTimeShadowManager::m_realTimeShadowPool.GetOffset();
	}

	// Returns true if CLEO loading is implemented by the FLA
	F92_LA_API bool F92_LA_CONVENTION IsCLEOloadingImplementedByTheFLA()
	{
		return CLEOloadingImplemented;
	}
}
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
// Project: fastman92 limit adjuster

// Please set up appropriate macros depending on platform for your project.

#pragma once
#include "../Common/common.h"
#include <MultiPlatformSupport/PlatformGeneralisation.h>
#include <stdint.h>

#undef F92_LA_API
#ifdef FASTMAN92_LIMIT_ADJUSTER
	#define F92_LA_API DLL_EXPORT
#else
	#define F92_LA_API DLL_IMPORT
#endif

extern "C" {
	struct tImgDescriptorInGTASA
	{
		char m_name[40];
		char m_bRegister;
		int m_lsn;
	};

	// GTA SA IMG loading call
	struct tGTASAimgLoadingCall
	{
		uint32_t dwSize;	// structure size

		//////////////////
		// first version of structure

		// pointer passed to functions below
		void* pUserData;

		// When ReadEntry != NULL, then IMG archive won't opened and caller is responsible for opening/closing if neccessary.
		// ReadEntry will be used to get each next entry.
		bool(* ReadEntry)(class tImgFastman92GTASAdirectoryEntry* pEntry, void* pUserData);

		// Function that's executed to find out if special entry should be added or not.
		bool(* OnSpecialEntry)(class tImgFastman92GTASAdirectoryEntry* pEntry, void* pUserData);

		// Function that's executed after CStreamingInfo::GetCdPosnAndSize, can prevent registering the entry.
		bool(* OnEntry)(
			class tImgFastman92GTASAdirectoryEntry* pEntry,
			void* pStreamingInfo,
			bool isFileSizeSetUp,
			void* pUserData
			);

		//////////////////////////////////////////////////////////////////////////////

		// size = 20
		//////////////////
	};
	
	// Count of file IDs
	F92_LA_API  int32_t F92_LA_CONVENTION GetNumberOfFileIDs();

	// Returns model info, prev file ID
	F92_LA_API int32_t F92_LA_CONVENTION GetFileInfoPrevFileID(int32_t fileID);

	// Returns model info, next file ID
	F92_LA_API int32_t F92_LA_CONVENTION GetFileInfoNextFileID(int32_t fileID);

	// Returns model info, next on CD file ID
	F92_LA_API int32_t F92_LA_CONVENTION  GetFileInfoNextOnCDfileID(int32_t fileID);

	// Sets file info, Prev file ID 
	F92_LA_API void F92_LA_CONVENTION SetFileInfoPrevFileID(int32_t fileID, int32_t newValue);
	
	// Sets file info, Next file ID
	F92_LA_API void F92_LA_CONVENTION SetFileInfoNextFileID(int32_t fileID, int32_t newValue);

	// Sets file info, NextOnCd file ID
	F92_LA_API void F92_LA_CONVENTION SetFileInfoNextOnCDfileID(int32_t fileID, int32_t newValue);

	// Returns true if handling of enhanced IMG archives is enabled
	F92_LA_API bool F92_LA_CONVENTION IsHandlingOfEnhancedIMGarchivesEnabled();
	
#ifdef IS_PLATFORM_WIN_X86
	// Loads CD directory in GTA SA. Works only if enhanced IMG archives are enabled!
	F92_LA_API void F92_LA_CONVENTION LoadCdDirectoryInGTASA(
			const tImgDescriptorInGTASA *pIMGdescriptor,
			int imgId,
			tGTASAimgLoadingCall* pLoadingCall
		);

	// Sets CdStreamStream Release Channel function
	// SilentPatch uses it.
	F92_LA_API void cdecl SetCdStreamReleaseChannelfUsedByTheFLA(void(__cdecl*func)(void* pStream));
#endif

	// Sets vehicle audio settings path
	F92_LA_API void F92_LA_CONVENTION SetVehicleAudioSettingsPath(const char* filename = 0);

	// Loads vehicle audio settings with path
	F92_LA_API void F92_LA_CONVENTION LoadVehicleAudioSettings();

	// Do Mod loader action
	F92_LA_API void F92_LA_CONVENTION DoModLoaderAction(int action);

	// Returns weapon parent type
	F92_LA_API int F92_LA_CONVENTION GetWeaponHighestParentType(int weaponType);

	// Returns weapon name
	// Can only return a name, if weapon limits are enabled and weapon config DAT got loaded.
	F92_LA_API const char* F92_LA_CONVENTION GetWeaponName(int weaponType);

	// Returns the count of weapon infos
	F92_LA_API unsigned int F92_LA_CONVENTION GetCountOfWeaponInfos();

	// Returns the number of possible weapon types
	F92_LA_API unsigned int F92_LA_CONVENTION GetNumberOfWeaponTypes();

	// Returns project version
	F92_LA_API const char* F92_LA_CONVENTION GetProjectVersion();

	// extended ID

	// Tells if DFF/TXD 32-bit IDs are enabled.
	F92_LA_API bool F92_LA_CONVENTION AreDifficultIDsExtended();

	F92_LA_API int32_t F92_LA_CONVENTION GetExtendedIDfrom16bitBefore(const void* basicPtr);
	F92_LA_API void F92_LA_CONVENTION SetExtendedIDfrom16bitBefore(void* basicPtr, int32_t ID);

	F92_LA_API int32_t F92_LA_CONVENTION GetExtendedIDfrom8bitBefore(const void* basicPtr);
	F92_LA_API void F92_LA_CONVENTION SetExtendedIDfrom8bitBefore(void* basicPtr, int32_t ID);
	/////////

	// Returns true if vehicles colour IDs extended.
	F92_LA_API bool F92_LA_CONVENTION AreVehicleColourIDsExtended();

	// Returns offset of CRealTimeShadowManager::m_realTimeShadowPool
	F92_LA_API unsigned int GetOffset_CRealTimeShadowManager_m_realTimeShadowPool();

	// Returns true if CLEO loading is implemented by the FLA
	F92_LA_API bool F92_LA_CONVENTION IsCLEOloadingImplementedByTheFLA();
}
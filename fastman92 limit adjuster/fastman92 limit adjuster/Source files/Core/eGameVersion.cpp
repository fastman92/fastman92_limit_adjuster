/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "eGameVersion.h"

#include <enumMemberNamePair.h>

namespace Game
{
#define CREATE_GAME_VERSION__PLATFORM_CASE(game_version, platform) case GAME_VERSION_##game_version##_##platform: return GAME_PLATFORM_##platform;

	// Returns a platform identifier
	eGamePlatform CGameVersion::GetPlatform(eGameVersion gameVersion)
	{
		switch (gameVersion)
		{
			MAKE_GAME_VERSION_LIST(CREATE_GAME_VERSION__PLATFORM_CASE)
		default:
			return GAME_PLATFORM_UNDEFINED;
		}
	}

	// Checks if game series is GTA
	bool CGameVersion::IsGameSeries_GTA(eGameVersion gameVersion)
	{
		return IsAny_GTA_III(gameVersion)
			|| IsAny_GTA_VC(gameVersion)
			|| IsAny_GTA_SA(gameVersion)
			|| IsAny_GTA_LCS(gameVersion)
			|| IsAny_GTA_VCS(gameVersion)
			|| IsAny_GTA_IV_or_EFLC(gameVersion)
			|| IsAny_GTA_V(gameVersion)
			|| IsAny_GTA_VI(gameVersion);
	}

	// Checks if game series is Bully
	bool CGameVersion::IsGameSeries_Bully(eGameVersion gameVersion)
	{
		return IsAny_Bully_SE(gameVersion);
	}

	// Checks if game series is GTA or Bully
	bool CGameVersion::IsGameSeries_GTA_or_Bully(eGameVersion gameVersion)
	{
		return IsGameSeries_GTA(gameVersion)
			|| IsGameSeries_Bully(gameVersion);
	}

	// Checks if game version is Bully SE
	bool CGameVersion::IsAny_Bully_SE(eGameVersion gameVersion)
	{
		return IsAny_Bully_SE_classic_for_Windows(gameVersion)
			|| gameVersion == GAME_VERSION_BULLY_AE_1_0_0_18_ANDROID_ARMEABI_V7A;
	}

	// Checks if game version is Bully SE VC classic for Windows
	bool CGameVersion::IsAny_Bully_SE_classic_for_Windows(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86;
	}

	// Checks if game version is GTA III
	bool CGameVersion::IsAny_GTA_III(eGameVersion gameVersion)
	{
		return IsAny_GTA_III_Renderware(gameVersion) || IsAny_GTA_III_UnrealEngine(gameVersion);
	}

	// Checks if game version is GTA III classic for Windows
	bool CGameVersion::IsAny_GTA_III_classic_for_Windows(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_III_1_0_WIN_X86;
	}

	// Checks if game version is GTA III with Renderware Engine
	bool CGameVersion::IsAny_GTA_III_Renderware(eGameVersion gameVersion)
	{
		return IsAny_GTA_III_classic_for_Windows(gameVersion)
			|| Is_GTA_III_Android_Renderware(gameVersion);
	}

	// Checks if game version is GTA SA with Unreal Engine
	bool CGameVersion::IsAny_GTA_III_UnrealEngine(eGameVersion gameVersion)
	{
		return false;
	}

	// Checks if it's GTA III for Android by War Drums
	bool CGameVersion::Is_GTA_III_Android_Renderware(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_III_1_0_ANDROID_ARMEABI
			|| gameVersion == GAME_VERSION_GTA_III_1_8_ANDROID_ARMEABI_V7A
			|| gameVersion == GAME_VERSION_GTA_III_1_9_ANDROID_ARMEABI_V7A
			|| gameVersion == GAME_VERSION_GTA_III_1_9_ANDROID_ARM64_V8A;
	}

	/*
	// Checks if game version is GTA III 1.8 or 1.9 on ANDROID_ARM32, they both have the same executable library
	bool CGameVersion::Is_GTA_III_1_8_or_1_9_ANDROID_ARMEABI_V7A(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_III_1_8_ANDROID_ARMEABI_V7A
			|| gameVersion == GAME_VERSION_GTA_III_1_9_ANDROID_ARMEABI_V7A;
	}
	*/

	// Checks if game version is GTA VC
	bool CGameVersion::IsAny_GTA_VC(eGameVersion gameVersion)
	{
		return IsAny_GTA_VC_Renderware(gameVersion) || IsAny_GTA_VC_UnrealEngine(gameVersion);
	}

	// Checks if game version is GTA VC classic for Windows
	bool CGameVersion::IsAny_GTA_VC_classic_for_Windows(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86;
	}

	// Checks if game version is GTA VC with Renderware Engine
	bool CGameVersion::IsAny_GTA_VC_Renderware(eGameVersion gameVersion)
	{
		return IsAny_GTA_VC_classic_for_Windows(gameVersion)
			|| Is_GTA_VC_Android_Renderware(gameVersion);
	}

	// Checks if game version is GTA SA with Unreal Engine
	bool CGameVersion::IsAny_GTA_VC_UnrealEngine(eGameVersion gameVersion)
	{
		return false;
	}

	// Checks if it's GTA VC for Android by War Drums
	bool CGameVersion::Is_GTA_VC_Android_Renderware(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_VC_1_09_ANDROID_ARMEABI_V7A
			|| gameVersion == GAME_VERSION_GTA_VC_1_10_ANDROID_ARMEABI_V7A
			|| gameVersion == GAME_VERSION_GTA_VC_1_10_ANDROID_ARM64_V8A
			|| gameVersion == GAME_VERSION_GTA_VC_1_12_ANDROID_ARMEABI_V7A
			|| gameVersion == GAME_VERSION_GTA_VC_1_12_ANDROID_ARM64_V8A;
	}

	// Checks if game version is GTA SA
	bool CGameVersion::IsAny_GTA_SA(eGameVersion gameVersion)
	{
		return IsAny_GTA_SA_Renderware(gameVersion) || IsAny_GTA_SA_UnrealEngine(gameVersion);
	}

	// Checks if game version is GTA SA classic for Windows
	bool CGameVersion::IsAny_GTA_SA_classic_for_Windows(eGameVersion gameVersion)
	{
		return Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
			|| Is_GTA_SA_1_0_1_EU_WIN_X86(gameVersion);
	}

	// Checks if game version is GTA SA with Renderware Engine
	bool CGameVersion::IsAny_GTA_SA_Renderware(eGameVersion gameVersion)
	{
		return IsAny_GTA_SA_classic_for_Windows(gameVersion)
			|| Is_GTA_SA_Android_Renderware(gameVersion);
	}

	// Checks if game version is GTA SA with Unreal Engine
	bool CGameVersion::IsAny_GTA_SA_UnrealEngine(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_TRILOGY_SA_ANY_WIN_X64
			|| gameVersion == GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14388_WIN_X64
			|| gameVersion == GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14718_WIN_X64
			|| gameVersion == GAME_VERSION_GTA_TRILOGY_SA_1_0_17_37984884_WIN_X64
			|| gameVersion == GAME_VERSION_GTA_SA_DE_ROCKSTAR_1_72_42919648_ANDROID_ARM64_V8A;
	}

	// Checks if it's GTA SA for Android by War Drums
	bool CGameVersion::Is_GTA_SA_Android_Renderware(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A
			|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
			|| gameVersion == GAME_VERSION_GTA_SA_GER_2_09_ANDROID_ARMEABI_V7A

			|| gameVersion == GAME_VERSION_GTA_SA_2_10_ANDROID_ARMEABI_V7A
			|| gameVersion == GAME_VERSION_GTA_SA_2_10_ANDROID_ARM64_V8A

			|| gameVersion == GAME_VERSION_GTA_SA_2_11_32_ANDROID_ARM64_V8A
			|| gameVersion == GAME_VERSION_GTA_SA_2_11_32_ANDROID_X64;
	}

	// Checks if game version is GTA SA 1.0,
	bool CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
			|| gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86;
	}

	// Checks if game version is GTA SA 1.1 on WIN_X86 platform
	bool CGameVersion::Is_GTA_SA_1_0_1_EU_WIN_X86(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_SA_1_0_1_EURO_NO_CD_FIXED_EXE_WIN_X86;
	}

	// Checks if game version is GTA LCS
	bool CGameVersion::IsAny_GTA_LCS(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_LCS_2_4_ANDROID_ARMEABI_V7A
			|| gameVersion == GAME_VERSION_GTA_LCS_2_4_235_ANDROID_ARM64_V8A;
	}

	// GTA Vice City Stories
	bool CGameVersion::IsAny_GTA_VCS(eGameVersion gameVersion)
	{
		return false;
	}

	// Checks if game version is GTA CTW
	bool CGameVersion::IsAny_GTA_CTW(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_CTW_1_04_ANDROID_ARMEABI_V7A;
	}

	// Checks if game version is any GTA IV or GTA EFLC
	bool CGameVersion::IsAny_GTA_IV_or_EFLC(eGameVersion gameVersion)
	{
		return IsAny_GTA_IV_WIN_X86(gameVersion)
			|| IsAny_GTA_EFLC_WIN_X86(gameVersion);
	}

	// Checks if game version is any GTA IV
	bool CGameVersion::IsAny_GTA_IV(eGameVersion gameVersion)
	{
		return IsAny_GTA_IV_WIN_X86(gameVersion);
	}

	// Checks if game version is any GTA IV
	bool CGameVersion::IsAny_GTA_EFLC(eGameVersion gameVersion)
	{
		return IsAny_GTA_EFLC_WIN_X86(gameVersion);
	}

	// Checks if game version is any GTA IV on PC
	bool CGameVersion::IsAny_GTA_IV_WIN_X86(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
			|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
			|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86;
	}

	// Checks if game version is any GTA EFLC on PC
	bool CGameVersion::IsAny_GTA_EFLC_WIN_X86(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86
			|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_3_0_WIN_X86;
	}

	// Checks if game version is any GTA V on PC
	bool CGameVersion::IsAny_GTA_V(eGameVersion gameVersion)
	{
		return IsAny_GTA_V_WIN_X64(gameVersion);
	}

	// Checks if game version is any GTA EFLC on PC
	bool CGameVersion::IsAny_GTA_V_WIN_X64(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_V_ANY_WIN_X64
			|| gameVersion == GAME_VERSION_GTA_V_1_0_323_1_WIN_X64
			|| gameVersion == GAME_VERSION_GTA_V_1_0_335_2_WIN_X64
			|| gameVersion == GAME_VERSION_GTA_V_1_0_350_2_WIN_X64;
	}

	////// GTA VI            ///////
	// Checks if game version is any GTA VI
	bool CGameVersion::IsAny_GTA_VI(eGameVersion gameVersion)
	{
		return IsAny_GTA_VI_PC(gameVersion);
	}

	bool CGameVersion::IsAny_GTA_VI_PC(eGameVersion gameVersion)
	{
		return false;
	}

	//////////////////

	// SCM support
	bool CGameVersion::IsAny_withSCMsupport(eGameVersion gameVersion)
	{
		return IsAny_GTA_III(gameVersion)
			|| IsAny_GTA_VC(gameVersion)
			|| IsAny_GTA_SA(gameVersion)
			|| IsAny_GTA_LCS(gameVersion)
			|| IsAny_GTA_VCS(gameVersion);
	}

	//////////////////

#define STR_EXPAND(str) #str
#define DEFINE_GAME_VERSION__MEMBER_NAME(game_version, platform) { GAME_VERSION_##game_version##_##platform, STR_EXPAND(game_version##_##platform)},

	static const enumMemberNamePair<eGameVersion> GameVersionEnumMemberNames[] =
	{
		{GAME_VERSION_UNDEFINED, "UNDEFINED"},
		MAKE_GAME_VERSION_LIST(DEFINE_GAME_VERSION__MEMBER_NAME)
	};

	// Finds name by game enum member
	const char* CGameVersion::GetPlatformEnumNameByMember(eGameVersion game)
	{
		return getNameByEnumMemberFromArray(GameVersionEnumMemberNames, game);
	}

#define DEFINE_GAME_VERSION__MEMBER_NAME_NO_PLATFORM_NAME(game_version, platform) { GAME_VERSION_##game_version##_##platform, STR_EXPAND(game_version)},

	static const enumMemberNamePair<eGameVersion> GameVersionEnumMemberNamesNoPlatform[] =
	{
		{GAME_VERSION_UNDEFINED, "UNDEFINED"},
		MAKE_GAME_VERSION_LIST(DEFINE_GAME_VERSION__MEMBER_NAME_NO_PLATFORM_NAME)
	};

	// Finds name by game enum member, without platform name
	const char* CGameVersion::GetGameNameByMemberWithoutPlatformName(eGameVersion game)
	{
		return getNameByEnumMemberFromArray(GameVersionEnumMemberNamesNoPlatform, game);
	}
}
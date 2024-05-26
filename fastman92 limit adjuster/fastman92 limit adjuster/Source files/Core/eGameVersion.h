/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <eGame.h>

/* The priority of possible questions
	1. Is game series X (e.g GTA)
	2. Is game subseries Y (e.g GTA IV/EFLC)
	3. Is game Z (e.g GTA SA)
	4. Is game Z with specific version on specific platform (e.g GTA SA 1.0 on WIN_X86 platform)
*/

namespace Game
{
#define MAKE_GAME_VERSION_LIST(formatMacro) \
\
/* //////////////////////////////// */ \
/* /////////// WIN_X86 //////////// */ \
/* //////////////////////////////// */ \
/* GTA III */ \
formatMacro(GTA_III_1_0, WIN_X86) \
/* GTA VC */ \
formatMacro(GTA_VC_1_0, WIN_X86) \
/* GTA SA */ \
formatMacro(GTA_SA_1_0_US_HOODLUM, WIN_X86) \
formatMacro(GTA_SA_1_0_US_COMPACT, WIN_X86) \
formatMacro(GTA_SA_1_0_1_EURO_NO_CD_FIXED_EXE, WIN_X86) \
/* GTA IV */ \
formatMacro(GTA_IV_1_0_4_0, WIN_X86) \
formatMacro(GTA_IV_1_0_7_0, WIN_X86) \
formatMacro(GTA_IV_1_0_8_0, WIN_X86) \
/* GTA ELFC */ \
formatMacro(GTA_EFLC_1_1_2_0, WIN_X86) \
formatMacro(GTA_EFLC_1_1_3_0, WIN_X86) \
/* Bully SE */ \
formatMacro(BULLY_SE_1_2, WIN_X86) \
/* //////////////////////////////// */ \
/* /////////// WIN_X64 //////////// */ \
/* //////////////////////////////// */ \
/* GTA SA */ \
formatMacro(GTA_TRILOGY_SA_1_0_0_14388, WIN_X64) \
formatMacro(GTA_TRILOGY_SA_1_0_0_14718, WIN_X64) \
formatMacro(GTA_TRILOGY_SA_1_0_17_37984884, WIN_X64) \
formatMacro(GTA_TRILOGY_SA_ANY, WIN_X64) \
/* GTA V */ \
formatMacro(GTA_V_1_0_323_1, WIN_X64) \
formatMacro(GTA_V_1_0_335_2, WIN_X64) \
formatMacro(GTA_V_1_0_350_2, WIN_X64) /* update 5 */ \
formatMacro(GTA_V_ANY, WIN_X64) \
/* //////////////////////////////// */ \
/* ////// ANDROID_ARMEABI_V7A ///// */ \
/* //////////////////////////////// */ \
/* GTA III */ \
formatMacro(GTA_III_1_0, ANDROID_ARMEABI) \
formatMacro(GTA_III_1_8, ANDROID_ARMEABI_V7A) \
formatMacro(GTA_III_1_9, ANDROID_ARMEABI_V7A) \
/* GTA VC */ \
formatMacro(GTA_VC_1_09, ANDROID_ARMEABI_V7A) \
formatMacro(GTA_VC_1_10, ANDROID_ARMEABI_V7A) \
formatMacro(GTA_VC_1_12, ANDROID_ARMEABI_V7A) \
/* GTA SA */ \
formatMacro(GTA_SA_1_08, ANDROID_ARMEABI_V7A) \
formatMacro(GTA_SA_2_00, ANDROID_ARMEABI_V7A) \
formatMacro(GTA_SA_2_10, ANDROID_ARMEABI_V7A) \
formatMacro(GTA_SA_GER_2_09, ANDROID_ARMEABI_V7A) \
/* GTA LCS */ \
formatMacro(GTA_LCS_2_4, ANDROID_ARMEABI_V7A) \
/* GTA CTW */ \
formatMacro(GTA_CTW_1_04, ANDROID_ARMEABI_V7A) \
/* Bully AE */ \
formatMacro(BULLY_AE_1_0_0_18, ANDROID_ARMEABI_V7A) \
/* //////////////////////////////// */ \
/* ////// ANDROID_ARM64_V8A /////// */ \
/* //////////////////////////////// */ \
formatMacro(GTA_III_1_9, ANDROID_ARM64_V8A) \
formatMacro(GTA_VC_1_10, ANDROID_ARM64_V8A) \
formatMacro(GTA_VC_1_12, ANDROID_ARM64_V8A) \
formatMacro(GTA_SA_2_10, ANDROID_ARM64_V8A) \
formatMacro(GTA_SA_2_11_32, ANDROID_ARM64_V8A) \
formatMacro(GTA_SA_DE_ROCKSTAR_1_72_42919648, ANDROID_ARM64_V8A) \
formatMacro(GTA_SA_DE_ROCKSTAR_1_86_44544238, ANDROID_ARM64_V8A) \
/* GTA LCS */ \
formatMacro(GTA_LCS_2_4_235, ANDROID_ARM64_V8A) \
/* //////////////////////////////// */ \
/* ////// ANDROID_X64       /////// */ \
/* //////////////////////////////// */ \
formatMacro(GTA_SA_2_11_32, ANDROID_X64) \
/* ////////////////////// */ \
/* //////// PS2 ///////// */ \
/* ////////////////////// */ \
formatMacro(GTA_SA_1_0, PS2) \
formatMacro(GTA_VCS_1_0, PS2)



#define PUT_GAME_VERSION_MEMBER_FROM_LIST(game_version, platform) GAME_VERSION_##game_version##_##platform,

	// Game versions
	enum eGameVersion
	{
		GAME_VERSION_UNDEFINED,
		MAKE_GAME_VERSION_LIST(PUT_GAME_VERSION_MEMBER_FROM_LIST)
	};

	class CGameVersion
	{
	public:
		// Returns a platform identifier
		static eGamePlatform GetPlatform(eGameVersion gameVersion);

		// Checks if game series is GTA
		static bool IsGameSeries_GTA(eGameVersion gameVersion);

		// Checks if game series is Bully
		static bool IsGameSeries_Bully(eGameVersion gameVersion);

		// Checks if game series is GTA or Bully
		static bool IsGameSeries_GTA_or_Bully(eGameVersion gameVersion);
		 
		///////////////////////////////////////////////////
		
		/////// Bully Scolarship Edition ///////
		// Checks if game version is Bully SE
		static bool IsAny_Bully_SE(eGameVersion gameVersion);

		// Checks if game version is Bully SE VC classic for Windows
		static bool IsAny_Bully_SE_classic_for_Windows(eGameVersion gameVersion);

		// Checks if game version is GTA III
		static bool IsAny_GTA_III(eGameVersion gameVersion);

		// Checks if game version is GTA III classic for Windows
		static bool IsAny_GTA_III_classic_for_Windows(eGameVersion gameVersion);

		// Checks if game version is GTA III with Renderware Engine
		static bool IsAny_GTA_III_Renderware(eGameVersion gameVersion);

		// Checks if game version is GTA SA with Unreal Engine
		static bool IsAny_GTA_III_UnrealEngine(eGameVersion gameVersion);

		// Checks if it's GTA III for Android by War Drums
		static bool Is_GTA_III_Android_Renderware(eGameVersion gameVersion);

		/*
		// Checks if game version is GTA III 1.8 or 1.9 on ANDROID_ARM32, they both have the same executable library
		static bool Is_GTA_III_1_8_or_1_9_ANDROID_ARMEABI_V7A(eGameVersion gameVersion);
		*/

		/////// GTA Vice City ///////
		// Checks if game version is GTA VC
		static bool IsAny_GTA_VC(eGameVersion gameVersion);

		// Checks if game version is GTA VC classic for Windows
		static bool IsAny_GTA_VC_classic_for_Windows(eGameVersion gameVersion);

		// Checks if game version is GTA VC with Renderware Engine
		static bool IsAny_GTA_VC_Renderware(eGameVersion gameVersion);

		// Checks if game version is GTA SA with Renderware Engine
		static bool IsAny_GTA_VC_UnrealEngine(eGameVersion gameVersion);

		// Checks if it's GTA VC for Android by War Drums
		static bool Is_GTA_VC_Android_Renderware(eGameVersion gameVersion);

		/////// GTA San Andreas ///////

		// Checks if game version is GTA SA
		static bool IsAny_GTA_SA(eGameVersion gameVersion);

		// Checks if game version is GTA SA classic for Windows
		static bool IsAny_GTA_SA_classic_for_Windows(eGameVersion gameVersion);

		// Checks if game version is GTA SA with Renderware Engine
		static bool IsAny_GTA_SA_Renderware(eGameVersion gameVersion);

		// Checks if game version is GTA SA with Unreal Engine
		static bool IsAny_GTA_SA_UnrealEngine(eGameVersion gameVersion);

		// Checks if it's GTA SA for Android by War Drums
		static bool Is_GTA_SA_Android_Renderware(eGameVersion gameVersion);

		// Checks if game version is GTA SA 1.0
		static bool Is_GTA_SA_1_0_US_WIN_X86(eGameVersion gameVersion);

		// Checks if game version is GTA SA 1.1 on WIN_X86 platform
		static bool Is_GTA_SA_1_0_1_EU_WIN_X86(eGameVersion gameVersion);

		// GTA Liberty City Stories

		// Checks if game version is GTA LCS
		static bool IsAny_GTA_LCS(eGameVersion gameVersion);

		// GTA Vice City Stories
		static bool IsAny_GTA_VCS(eGameVersion gameVersion);

		// Checks if game version is GTA CTW
		static bool IsAny_GTA_CTW(eGameVersion gameVersion);

		/////// GTA IV, GTA EFLC ///////
		// Checks if game version is any GTA IV or GTA EFLC
		static bool IsAny_GTA_IV_or_EFLC(eGameVersion gameVersion);

		// Checks if game version is any GTA IV
		static bool IsAny_GTA_IV(eGameVersion gameVersion);

		// Checks if game version is any GTA IV
		static bool IsAny_GTA_EFLC(eGameVersion gameVersion);

		// Checks if game version is any GTA IV on PC
		static bool IsAny_GTA_IV_WIN_X86(eGameVersion gameVersion);

		// Checks if game version is any GTA EFLC on PC
		static bool IsAny_GTA_EFLC_WIN_X86(eGameVersion gameVersion);

		/////// GTA V            ///////

		// Checks if game version is any GTA V
		static bool IsAny_GTA_V(eGameVersion gameVersion);

		// Checks if game version is any GTA V on PC
		static bool IsAny_GTA_V_WIN_X64(eGameVersion gameVersion);


		////// GTA VI            ///////
		// Checks if game version is any GTA VI
		static bool IsAny_GTA_VI(eGameVersion gameVersion);

		// Checks if game version is any GTA VI on PC
		static bool IsAny_GTA_VI_PC(eGameVersion gameVersion);

		//////////////////

		// SCM support
		static bool IsAny_withSCMsupport(eGameVersion gameVersion);

		//////////////////

		// Finds name by game enum member
		static const char* GetPlatformEnumNameByMember(eGameVersion game);

		// Finds name by game enum member, without platform name
		static const char* GetGameNameByMemberWithoutPlatformName(eGameVersion game);
	};
}
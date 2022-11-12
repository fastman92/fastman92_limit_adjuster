/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "LimitAdjuster.h"

#include "CGenericLogStorage.h"
#include "CUserInterface.h"
#include "FormattedOutput.h"

#include "Configuration/Configuration.h"
#include "Configuration/CSVfile.h"
#include "Configuration/XMLexcelFile.h"

#include "../GameStructures/Rockstar Games/CCamera.h"
#include "../GameStructures/Rockstar Games/CCoronas.h"
#include "../GameStructures/Rockstar Games/CFileMgr.h"
#include "../GameStructures/Rockstar Games/CGenericGameStorage.h"
#include "../GameStructures/Rockstar Games/CEntity.h"
#include "../GameStructures/Rockstar Games/CFont.h"
#include "../GameStructures/Rockstar Games/CKeyGen.h"
#include "../GameStructures/Rockstar Games/CMemoryMgr.h"
#include "../GameStructures/Rockstar Games/CModelInfo.h"
#include "../GameStructures/Rockstar Games/CPad.h"
#include "../GameStructures/Rockstar Games/CRunningScript.h"
#include "../GameStructures/Rockstar Games/CStreaming.h"
#include "../GameStructures/Rockstar Games/CText.h"
#include "../GameStructures/Rockstar Games/CTimer.h"
#include "../GameStructures/Rockstar Games/CWorld.h"
#include "../GameStructures/Rockstar Games/GameSystem.h"
#include "../GameStructures/Rockstar Games/functions.h"
#include "../GameStructures/Rockstar Games/Renderware.h"
#include "../GameStructures/Rockstar Games/RwStream.h"

#include "../Modules/BringBackTextureArchives.h"
#include "../Modules/CarGeneratorsLimit.h"
#include "../Modules/CargrpLimit.h"
#include "../Modules/CEasterEggs.h"
#include "../Modules/Credits.h"
#include "../Modules/CheatStringLoader.h"
#include "../Modules/COnlineContent.h"
#include "../Modules/CoordinateMover.h"
#include "../Modules/CStreamingDebug.h"
#include "../Modules/CTest.h"
#include "../Modules/CThePluginPatches.h"
#include "../Modules/CVehicleAudioLoader.h"
#include "../Modules/Debugging.h"
#include "../Modules/DebugOutput.h"
#include "../Modules/Directory limits.h"
#include "../Modules/DynamicLimits.h"
#include "../Modules/ErrorReporting.h"
#include "../Modules/ExecutableCode.h"
#include "../Modules/FileLoader_LoadLevel_hooks.h"
#include "../Modules/FileIDlimit.h"
#include "../Modules/FXTloader.h"
#include "../Modules/GameText.h"
#include "../Modules/GlobalExceptionHandler.h"
#include "../Modules/HandlingCfgLimits.h"
#include "../Modules/IslandLimits.h"
#include "../Modules/IMGlimits.h"
#include "../Modules/InlinedCodeRemoving.h"
#include "../Modules/IDEsectionLimits.h"
#include "../Modules/IPLsectionLimits.h"
#include "../Modules/LoadingScreenFontHooks.h"
#include "../Modules/MapLimits.h"
#include "../Modules/ModelSpecialFeatures.h"
#include "../Modules/Options.h"
#include "../Modules/OtherLimits.h"
#include "../Modules/NotApropIDrangeLoader.h"
#include "../Modules/PedgrpLimit.h"
#include "../Modules/ProcessEntryPointCodeExecution.h"
#include "../Modules/RadarBlipSpriteFilenameLoader.h"
#include "../Modules/RendererLimits.h"
#include "../Modules/Restarts.h"
#include "../Modules/RoadBloxBetterLoader.h"
#include "../Modules/SaveOfVariableLength.h"
#include "../Modules/SCMlimits.h"
#include "../Modules/ShadowLimits.h"
#include "../Modules/StructureExtension.h"
#include "../Modules/SpecialLimits.h"
#include "../Modules/StreamingLimits.h"
#include "../Modules/TrainTypeCarriagesLoader.h"
#include "../Modules/WeaponLimits.h"
#include "../Modules/VehicleSpecialFeatures.h"
#include "../Modules/VisibilityLimits.h"
#include "../Modules/WaterLimits.h"
#include "../Modules/WindowedMode.h"

#include "../../../fastman92 plugin loader/ForOtherProjects/Exports.h"

#include <fileIO.h>
#include "GTASA_CRC32.h"

#include <Array\countof.h>
#include <CRGBA.h>
#include <eGame.h>
#include <Exception\exception.h>
#include <MemoryAccess\CMemoryAccessWithinCurrentProcess.h>

#ifdef IS_PLATFORM_ANDROID
#include <jni.h>
#include <sys\stat.h> 
#include <unistd.h>

#include <ELF\ELF_manager.h>
#endif

#ifdef IS_PLATFORM_WIN

#if defined(IS_ARCHITECTURE_X86) || defined(IS_ARCHITECTURE_X64)
#include <MinHook\include\MinHook.h>
#endif

#include <commctrl.h>
#include <Shlwapi.h>

#include "../resources\Resource.h"
#endif

#include "ProjectConstants.h"

using namespace Game;
using namespace std;

static const bool bUseDevelopmentIni = PROJECT_USE_DEVELOPMENT_INI;

static const char* LIMIT_ADJUSTER_LOG_FILENAME = "fastman92limitAdjuster.log";

static char cTmp[1024];
static int nTmp;
static bool bTmp;
static double dTmp;

static CLimitAdjusterModule* LimitAdjusterPtrs[] =
{
	&g_BringBackTextureArchives,
	&g_carGeneratorLimits,
	&g_cargrpLimits,
	&g_CCamera_varInitialisation,
	&g_CCoronas_varInitialisation,
	&g_Credits,
	&g_CEasterEggs,
	&g_CEntity_varInitialisation,
	&g_CFileMgr_varInitialization,
	&g_CFont_varInitialisation,
	&g_CGenericGameStorage_VarInitialisation,
	&g_cheatStringLoader,
	&g_CEntity_VarInitialisation,
	&g_CKeygen_varInitialization,
	&g_CMemoryMgr_varInitialisation,
	&g_CModelInfo_varInitialisation,
	&g_coordinateMover,
	&g_CPad_varInitialisation,	
	&g_CStreaming_varInitialisation,
	&g_CText_VarInitialisation,
	&g_CTimer_varInitialisation,
	&g_CWorld_varInitialisation,
	&g_debugging,
	&g_debugOutput,
	&g_directoryLimits,
	&g_dynamicLimits,
	&g_errorReporting,
	&g_executableCode,
	&g_fileIDlimits,
	&g_functions_varInitialisation,
	&g_FxtLoader,
	&g_CSystem_varInitialisation,
	&g_GameText,
	&g_GlobalExceptionHandler,
	&g_InlinedCodeRemoving,
	&g_handlingCfgLimits,
	&g_IDEsectionLimits,
	&g_IMGlimits,
	&g_IPLsectionlimits,
	&g_islandLimits,
	&g_LoadingScreenFontHooks,
	&g_loadLevelHooks,
	&g_mapLimits,
	&g_modelSpecialFeatures,
	&g_notApropIDrangeLoader,
	&g_OnlineContent,
	&g_options,
	&g_otherLimits,
	&g_pedGrpLimits,
	&g_pluginPatches,
	&g_ProcessEntryPointCodeExecution,
	&g_RadarBlipSpriteFilenameLoader,
	&g_Renderware_varInitialisation,
	&g_RwStream_varInitialisation,
	&g_rendererLimits,
	&g_Restarts,
	&g_roadBloxBetterLoader,
	&g_SaveOfVariableLength,
	&g_shadowLimits,
	&g_SCMlimits,
	&g_specialLimits,
	&g_streamingLimits,
	&g_structureExtension,
	&g_trainTypeCarriageLoader,
	&g_waterLimits,
	&g_weaponLimits,
	&g_windowedMode,
	&g_vehicleAudioLoader,
	&g_vehicleSpecialFeatures,
	&g_visibilityLimits,
};

#if defined(IS_PLATFORM_WIN_X86) || defined(IS_PLATFORM_WIN_X64)
NAKED void crashTheGame()
{
	__asm
	{
		xor eax, eax;
		xor ebx, ebx;
		xor ecx, ecx;
		xor edx, edx;
		xor esi, esi;
		xor edi, edi;
		xor ebp, ebp;
		xor esp, esp;

		#ifdef IS_PLATFORM_WIN_X86
		jmp eax;
		#elif defined(IS_PLATFORM_WIN_X64)
		jmp rax;
		#endif
	}
}
#else
// Does nothing
void crashTheGame() {}
#endif

// Sets model IDs for levels
void SetModelIDsForLevels(const char* keyNamePattern, void (IslandLimits::* func)(int level, int ambulanceID), bool setLevel0)
{
	char keyName[32];

	for (unsigned int i = !setLevel0; i < g_islandLimits.ms_iNumberOfIslands; i++)
	{
		sprintf(keyName, keyNamePattern, i);

		(g_islandLimits.*func)(i, g_LimitAdjuster.INIreader.GetInt("LEVEL LIMITS", keyName));
	}
}

// Sets model IDs for vehicle special features
void SetModelIDsForVehSpecialFeatures(const char* countKeyName, const char* keyNamePattern, void (VehicleSpecialFeatures::*func)(int ID))
{
	unsigned int count = g_LimitAdjuster.INIreader.GetInt("VEHICLE SPECIAL FEATURES", countKeyName);

	char keyName[32];

	for (unsigned int i = 1; i <= count; i++)
	{
		sprintf(keyName, keyNamePattern, i);

		(g_vehicleSpecialFeatures.*func)(
			g_LimitAdjuster.INIreader.GetInt("VEHICLE SPECIAL FEATURES", keyName));
	}
}

// Processes FLA action
void CLimitAdjuster::ProcessFLAaction(eFLA_actionToDo action, void* pData)
{
	try
	{
		if (action == eFLA_actionToDo::Start)
			this->StartLimitAdjuster((const tLimitAdjusterStartParams*)pData);
		else if (action == eFLA_actionToDo::Process)
			this->Process();
		else if (action == eFLA_actionToDo::Stop)
			this->StopLimitAdjuster();
	}
	catch (f92_runtime_error& error)
	{
		const char* errorStr = error.what();
		CGenericLogStorage::SaveTextLn(errorStr);
		printf_MessageBox("%s", errorStr);
		
		this->TerminateProcess();
	}
}

// Processes an error of being unable to detect the game
void CLimitAdjuster::ProcessUnableToDetectTheGame()
{
	CGenericLogStorage::SaveFormattedTextLn("Unable to detect the game!");

#ifdef IS_PLATFORM_WIN_X86
	throw f92_runtime_error(
		"%s requires one of the following EXE files:\n"
		"\n1. GTA III v1.0 EXE:\n"
		"   EXE size:  2 383 872 bytes"

		"\n2. GTA Vice City v1.0 EXE:\n"
		"   EXE size:  3 088 896 bytes"

		"\n3. GTA San Andreas v1.0 [US] HOODLUM No-CD Fixed EXE:\n"
		"   EXE size:  14 383 616 bytes"

		"\n4. GTA San Andreas v1.0 [US] Compact EXE:\n"
		"   EXE size:  5 189 632  bytes"

		"\n5. GTA San Andreas v1.01 [EURO] No-CD Fixed EXE:\n"
		"   EXE size:  15 806 464 bytes"

		"\n6. GTA IV v1.0.4.0 EXE:\n"
		"   EXE size:  13 822 600 bytes"

		"\n7. GTA IV v1.0.7.0 EXE:\n"
		"   EXE size:  15 505 792 bytes"
		
		"\n8. GTA IV v1.0.8.0 EXE:\n"
		"   EXE size:  15 628 696 bytes"

		"\n9. GTA EFLC v1.1.2.0 EXE:\n"
		"   EXE size:  14 948 736 bytes"

		"\n10. GTA EFLC v1.1.3.0 EXE:\n"
		"   EXE size:  15 075 784 bytes"

		"\n11. Bully Scholarship Edition 1.20 crack:\n"
		"   EXE size:  8 204 288 bytes"

		, PROJECT_NAME
		);
#elif defined(IS_PLATFORM_WIN_X64)
	throw f92_runtime_error(
		"%s requires one of the following EXE files:\n"
		"1. GTA SA Definitive Edition 1.0.0.14718  EXE:\n"
		"   EXE size:  87 614 464 bytes\n"
		"   EXE size:  87 617 840 bytes"

		"\n2. GTA V EXE:\n"
		"   EXE size:  does not matter"

		, PROJECT_NAME
	);
#elif defined(IS_PLATFORM_ANDROID)
	throw f92_runtime_error(
		"%s requires one of the following games:\n"

		"\n1. GTA III 1.8:\n"
		"   SO library identifier: \"GTA_III|1.9|arm64-v8a\""

		"\n2. GTA Vice City 1.09:\n"
		"   SO library identifier: \"GTA_VC|1.09|armeabi-v7a\""

		"\n3. GTA San Andreas 1.08:\n"
		"   SO library identifier: \"GTA_SA|1.08|armeabi-v7a\""

		"\n4. GTA San Andreas 2.00:\n"
		"   SO library identifier: \"GTA_SA|2.00|armeabi-v7a\""

		"\n5. GTA San Andreas GER 2.09:\n"
		"   SO library identifier: \"GTA_SA_GER|2.09|armeabi-v7a\""

		"\n6. GTA Liberty City Stories 2.4:\n"
		"   SO library identifier: \"GTA_LCS|2.4|armeabi-v7a\""

		"\n7. GTA Chinatown Wars 1.04:\n"
		"   SO library identifier: \"TA_CTW|1.04|armeabi-v7a\""

		"\n8. Bully Scholarship Edition 1.0.0.18:\n"
		"   SO library identifier: \"Bully_AE|1.0.0.18|armeabi-v7a\""

		, PROJECT_NAME
	);
#endif
}

// Starts limit adjuster
void CLimitAdjuster::StartLimitAdjuster(const tLimitAdjusterStartParams* pLimitAdjusterStartParams)
{
	this->bIsAdditionalJavaCodeLoaded = false;
	this->bIsGameMemorySetUp = false;
	this->bDelayedProcessingOfLimits = false;
	this->bDynamicImageBase = true;
	this->bIsMultiplayerRunning = false;

	this->PackageName[0] = 0;

	this->FLA_release_directory[0] = 0;
	this->InitialDirectory[0] = 0;
	this->StorageRootDirectory[0] = 0;	
	this->StorageRootBase[0] = 0;
	this->CacheDirectory[0] = 0;

	#ifdef IS_PLATFORM_WIN
	this->exeFilesize = 0;
	this->EXEfilePath[0] = 0;
	this->EXEfilename = 0;
	#endif

	srand((unsigned int)time(NULL));

	// Initialise a log storage
	CGenericLogStorage::Initialise();
	CGenericLogStorage::OpenFileForTextWriting(LIMIT_ADJUSTER_LOG_FILENAME);
	
	CGenericLogStorage::SaveFormattedText("Starting %s", PROJECT_FULL_NAME);

#if FLA_CUSTOMIZATION != 0
	CGenericLogStorage::SaveFormattedTextLn("FLA_CUSTOMIZATION = %d", FLA_CUSTOMIZATION);
#endif
	
	CGenericLogStorage::SaveFormattedTextLn("Website: http://fastman92.com");
	CGenericLogStorage::WriteNewLine();
	
	/////
	// Set up the launch time
	{
		this->launchTimeDayPart = eDayPart::DAY_PART_UNDEFINED;
		this->launchTimeRetrieved = false;

		time_t rawtime;
		struct tm * ptm;
		time(&rawtime);

		bool bUTCtimeRetrieved = false;

		if ((ptm = gmtime(&rawtime)))
		{
			memcpy(&this->launchTimeUTC, ptm, sizeof(tm));
			bUTCtimeRetrieved = true;
		}

		bool blocalTimeRetrieved = false;

		if ((ptm = localtime(&rawtime)))
		{
			memcpy(&this->launchTimeLocal, ptm, sizeof(tm));
			blocalTimeRetrieved = true;
		}

		this->launchTimeRetrieved = bUTCtimeRetrieved && blocalTimeRetrieved;

		if (this->launchTimeRetrieved)
		{
			if (this->launchTimeLocal.tm_hour >= 22 || this->launchTimeLocal.tm_hour < 5)
				this->launchTimeDayPart = eDayPart::DAY_PART_NIGHT;
			else
				this->launchTimeDayPart = eDayPart::DAY_PART_DAY;
		}
	}

	if (this->launchTimeRetrieved)
	{
		CGenericLogStorage::SaveFormattedTextLn("Launch time: %d-%d-%d %d:%02d:%02d (UTC), %02d:%02d (local)",
			this->launchTimeUTC.tm_mday,
			this->launchTimeUTC.tm_mon + 1,
			this->launchTimeUTC.tm_year + 1900,
			this->launchTimeUTC.tm_hour,
			this->launchTimeUTC.tm_min,
			this->launchTimeUTC.tm_sec,

			this->launchTimeLocal.tm_hour,
			this->launchTimeLocal.tm_min
		);

		if (this->launchTimeDayPart == eDayPart::DAY_PART_NIGHT)
			CGenericLogStorage::SaveFormattedTextLn("Launched during the night.");
		else if (this->launchTimeDayPart == eDayPart::DAY_PART_DAY)
			CGenericLogStorage::SaveFormattedTextLn("Launched during the day.");

		CGenericLogStorage::WriteNewLine();
	}

	CGenericLogStorage::SaveFormattedTextLn("Solution platform: " TOSTRING(SOLUTION_PLATFORM));

	#ifdef TARGET_ARCH_ABI
	CGenericLogStorage::SaveFormattedTextLn("Platform ABI: " TOSTRING(TARGET_ARCH_ABI));
	#endif
	
	this->gameDetectedStr[0] = 0;
	
	#ifdef IS_PLATFORM_ANDROID
	this->jvm = pLimitAdjusterStartParams->jvm;
	this->second_param_reserved = pLimitAdjusterStartParams->second_param_reserved;

	// get path to application library directory
	{
		int index_of_last_slash = 0;

		for (unsigned int i = 0; pLimitAdjusterStartParams->pluginLibraryPath[i]; i++)
		{
			char c = pLimitAdjusterStartParams->pluginLibraryPath[i];

			if (c == '/' || c == '\\')
				index_of_last_slash = i;
		}

		memcpy(this->ApplicationLibraryDirectory, pLimitAdjusterStartParams->pluginLibraryPath, index_of_last_slash);
		this->ApplicationLibraryDirectory[index_of_last_slash] = 0;
	}
	#endif
	
	/////////////////////////////////////////////////

	// Set up module handles
	this->SetUpNativeCodeModuleHandles(pLimitAdjusterStartParams);

	#ifdef IS_PLATFORM_WIN
	// check the .exe
	GetModuleFileNameW(NULL, EXEfilePath, _countof(EXEfilePath));

	this->EXEfilename = PathFindFileNameW(EXEfilePath);
	
	__int64 filesize = GetFileSize(EXEfilePath);

	/// Initialize memory scanner
	g_mScanner.SetMemoryAccessor(&g_memoryAccessWithinCurrentProcess);
	g_mScanner.AddModuleSectionsToSearchList(this->hModule_of_game.windows);

	// Set the path to release directory
	GetEnvironmentVariableA("FASTMAN92_LIMIT_ADJUSTER_RELEASE_DIRECTORY",
		FLA_release_directory,
		_countof(FLA_release_directory)
	);

	// Initialize MinHook
	#if defined(IS_ARCHITECTURE_X86) || defined(IS_ARCHITECTURE_X64)
	MH_Initialize();
	#endif

	// Set EXE size
	this->exeFilesize = filesize;	
	#endif
	
	// Generate documentation files
	this->GenerateDocumentationFiles();

	// Get current application's base address
	uintptr_t currentVA = (uintptr_t)pLimitAdjusterStartParams->applicationLibBaseAddress;

	///////////////////////////////////	
#if FLA_CUSTOMIZATION == 1
	#ifdef IS_PLATFORM_WIN_X86
		this->SetGameInfo(0x400000, currentVA, GAME_VERSION_GTA_SA_1_0_HOODLUM_WIN_X86, "GTA SA 1.0 HOODLUM", true);
	#else
		return this->ProcessUnableToDetectTheGame();
	#endif
#elif FLA_CUSTOMIZATION == 2
	#ifdef IS_PLATFORM_WIN_X86
	this->SetGameInfo(0x400000, currentVA, GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86, "GTA IV 1.0.7.0", true);
	#else
		return this->ProcessUnableToDetectTheGame();
	#endif
#else
	#ifdef IS_PLATFORM_WIN
		this->bDelayedProcessingOfLimits = false;

		MAKE_DEAD_IF();	
		#ifdef IS_PLATFORM_WIN_X86
		else if(filesize == 2383872)
			this->SetGameInfo(0x400000, currentVA, GAME_VERSION_GTA_III_1_0_WIN_X86, "GTA III 1.0", true);
		else if (filesize == 3088896)
			this->SetGameInfo(0x400000, currentVA, GAME_VERSION_GTA_VC_1_0_WIN_X86, "GTA VC 1.0", true);
		else if (filesize == 14383616)
			this->SetGameInfo(0x400000, currentVA, GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86, "GTA SA 1.0 US HOODLUM", true);
		else if(filesize == 5189632)
			this->SetGameInfo(0x400000, currentVA, GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86, "GTA SA 1.0 US Compact", true);
		else if (filesize == 15806464)
			this->SetGameInfo(0x400000, currentVA, GAME_VERSION_GTA_SA_1_0_1_EURO_NO_CD_FIXED_EXE_WIN_X86, "GTA SA 1.01 EURO No-CD Fixed EXE", true);
		else if (filesize == 13822600)
			this->SetGameInfo(0x400000, currentVA, GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86, "GTA IV 1.0.4.0", true);
		else if (filesize == 15505792)
			this->SetGameInfo(0x400000, currentVA, GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86, "GTA IV 1.0.7.0", true);
		else if (filesize == 15628696)
			this->SetGameInfo(0x400000, currentVA, GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86, "GTA IV 1.0.8.0", true);
		else if (filesize == 14948736)
			this->SetGameInfo(0x400000, currentVA, GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86, "GTA EFLC 1.1.2.0", true);
		else if(filesize == 15075784)
			this->SetGameInfo(0x400000, currentVA, GAME_VERSION_GTA_EFLC_1_1_3_0_WIN_X86, "GTA EFLC 1.1.3.0", true);
		else if (filesize == 8204288)
			this->SetGameInfo(0x400000, currentVA, GAME_VERSION_BULLY_SE_1_2_WIN_X86, "Bully Scholarschip Edition", true);
		#elif defined(IS_PLATFORM_WIN_X64)
		/*
		else if (filesize == 87562240)
			this->SetGameInfo(0x140000000, currentVA, GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14388_WIN_X64, "GTA SA Definitive Edition 1.0.0.14388", true);
			*/
		else if (filesize == 87614464 || filesize == 87617840)
			this->SetGameInfo(0x140000000, currentVA, GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14718_WIN_X64, "GTA SA Definitive Edition 1.0.0.14718", true);
		else if (filesize == 51248008)
			this->SetGameInfo(0x140000000, currentVA, GAME_VERSION_GTA_V_1_0_323_1_WIN_X64, "GTA V 1.0.323.1", true);
		else if (filesize == 51338632)
			this->SetGameInfo(0x140000000, currentVA, GAME_VERSION_GTA_V_1_0_335_2_WIN_X64, "GTA V 1.0.335.2", true);
		else if (filesize == 51031432)
		this->SetGameInfo(0x140000000, currentVA, GAME_VERSION_GTA_V_1_0_350_2_WIN_X64, "GTA V 1.0.350.2", true);
		#endif
		else
		{
			MAKE_DEAD_IF();
			#if defined(IS_PLATFORM_WIN_X64)
			/*
			else if(
			this->TrySetGameInfoByFilename(
					L"SanAndreas.exe",
					"GTA SA Definitive Edition",
					0x140000000,
					currentVA,
					GAME_VERSION_GTA_TRILOGY_SA_ANY_WIN_X64					
				)
				);
				*/
			else if(this->TrySetGameInfoByFilename(
					L"GTA5.exe",
					"GTA V",
					0x140000000,
					currentVA,
					GAME_VERSION_GTA_V_ANY_WIN_X64					
				)
				);
			#endif
			else
				return this->ProcessUnableToDetectTheGame();
		}
	#elif defined(IS_PLATFORM_ANDROID)
		const char* appLibIdentifier = pLimitAdjusterStartParams->applicationLibIdentifier;

		if (!strcmp(appLibIdentifier, "Bully_AE|1.0.0.18|armeabi-v7a"))
			this->SetGameInfo(0, currentVA, GAME_VERSION_BULLY_AE_1_0_0_18_ANDROID_ARMEABI_V7A, "Bully Anniversary Edition 1.0.0.18");
		else if (!strcmp(appLibIdentifier, "GTA_III|1.8|armeabi-v7a"))
			this->SetGameInfo(0, currentVA, GAME_VERSION_GTA_III_1_8_ANDROID_ARMEABI_V7A, "GTA III 1.8");
		else if (!strcmp(appLibIdentifier, "GTA_III|1.9|armeabi-v7a"))
			this->SetGameInfo(0, currentVA, GAME_VERSION_GTA_III_1_9_ANDROID_ARMEABI_V7A, "GTA III 1.9");
		else if (!strcmp(appLibIdentifier, "GTA_III|1.9|arm64-v8a"))
			this->SetGameInfo(0, currentVA, GAME_VERSION_GTA_III_1_9_ANDROID_ARM64_V8A, "GTA III 1.9");
		else if (!strcmp(appLibIdentifier, "GTA_VC|1.09|armeabi-v7a"))
			this->SetGameInfo(0, currentVA, GAME_VERSION_GTA_VC_1_09_ANDROID_ARMEABI_V7A, "GTA VC 1.09");
		else if (!strcmp(appLibIdentifier, "GTA_SA|1.08|armeabi-v7a"))
			this->SetGameInfo(0, currentVA, GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A, "GTA SA 1.08");
		else if (!strcmp(appLibIdentifier, "GTA_SA|2.00|armeabi-v7a"))
			this->SetGameInfo(0, currentVA, GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A, "GTA SA 2.00");
		else if (!strcmp(appLibIdentifier, "GTA_SA_GER|2.09|armeabi-v7a"))
			this->SetGameInfo(0, currentVA, GAME_VERSION_GTA_SA_GER_2_09_ANDROID_ARMEABI_V7A, "GTA SA GER 2.09");
		else if (!strcmp(appLibIdentifier, "GTA_LCS|2.4|armeabi-v7a"))
			this->SetGameInfo(0, currentVA, GAME_VERSION_GTA_LCS_2_4_ANDROID_ARMEABI_V7A, "GTA LCS 2.4");
		else if (!strcmp(appLibIdentifier, "GTA_CTW|1.04|armeabi-v7a"))
			this->SetGameInfo(0, currentVA, GAME_VERSION_GTA_CTW_1_04_ANDROID_ARMEABI_V7A, "GTA CTW 1.04");
		else
			return this->ProcessUnableToDetectTheGame();

		OutputFormattedDebugString("Game detected: %s", this->gameDetectedStr);
	#endif
#endif

	#ifdef IS_PLATFORM_ANDROID
	{
			const void* pFunction = Library::GetSymbolAddress(&this->hModule_of_socialClub, "GetRockstarID");

			Dl_info info;
			dladdr(pFunction, &info);
			g_libSCAnd_mCalc.Initialize(0, (uintptr_t)info.dli_fbase);
	}
	#endif

	CGenericLogStorage::SaveFormattedTextLn("Game detected: %s", this->gameDetectedStr);

	if(this->bDynamicImageBase)
		CGenericLogStorage::SaveTextLn("Game uses dynamic image base? Yes");
	else
		CGenericLogStorage::SaveTextLn("Game uses dynamic image base? No");
		
	CGenericLogStorage::SaveFormattedTextLn("Game preferred image base: 0x%llX", (uint64_t)g_mCalc.GetPreferedModuleBase());
	CGenericLogStorage::SaveFormattedTextLn("Game current image base: 0x%llX", (uint64_t)g_mCalc.GetCurrentModuleBase());
	
	CGenericLogStorage::WriteNewLine();
	
	///////////////////////////////////
	
	this->Initialize();

	if(!this->bDelayedProcessingOfLimits)
		this->Process();
}

// Stops limit adjuster
void CLimitAdjuster::StopLimitAdjuster()
{
	this->Shutdown();

	CGenericLogStorage::SaveTextLn("Game closed.");
	CGenericLogStorage::CloseFile();
}

// Get filename for FLA library
const char* CLimitAdjuster::GetFLAlibraryFilename(Game::eGamePlatform platform)
{
	switch (platform)
	{
	case GAME_PLATFORM_WIN_X86:
		return "$fastman92limitAdjuster.asi";
	case GAME_PLATFORM_WIN_X64:
		return "$fastman92limitAdjusterX64.asi";
	case GAME_PLATFORM_ANDROID_ARMEABI_V7A:
		return "libplugin_fastman92limitAdjuster_ANDROID_ARM32.so";
	case GAME_PLATFORM_ANDROID_ARM64_V8A:
		return "libplugin_fastman92limitAdjuster_ANDROID_ARM64.so";
	case GAME_PLATFORM_ANDROID_X86:
		return "libplugin_fastman92limitAdjuster_ANDROID_X86.so";
	case GAME_PLATFORM_ANDROID_X64:
		return "libplugin_fastman92limitAdjuster_ANDROID_X64.so";
	default:
		break;
	}
	
	return nullptr;
}

// Is game memory set up?
bool CLimitAdjuster::IsGameVersionSetUpWithMemory()
{
	return this->bIsGameMemorySetUp;
}

// Get filename for game
const char* CLimitAdjuster::GetIniFilenameForGame(Game::eGameVersion gameVersion, bool devFilePossible)
{
	if (CGameVersion::IsAny_GTA_III(gameVersion))
	{
		if (devFilePossible && bUseDevelopmentIni)
			return "fastman92limitAdjuster_GTAIII_dev.ini";
		else
			return "fastman92limitAdjuster_GTAIII.ini";
	}
	else if (CGameVersion::IsAny_GTA_VC(gameVersion))
	{
		if (devFilePossible && bUseDevelopmentIni)
			return "fastman92limitAdjuster_GTAVC_dev.ini";
		else
			return "fastman92limitAdjuster_GTAVC.ini";
	}
	else if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		if (devFilePossible && bUseDevelopmentIni)
			return "fastman92limitAdjuster_GTASA_dev.ini";
		else
			return "fastman92limitAdjuster_GTASA.ini";
	}
	else if (CGameVersion::IsAny_GTA_LCS(gameVersion))
	{
		if (devFilePossible && bUseDevelopmentIni)
			return "fastman92limitAdjuster_GTALCS_dev.ini";
		else
			return "fastman92limitAdjuster_GTALCS.ini";
	}
	else if (CGameVersion::IsAny_GTA_VCS(gameVersion))
	{
		if (devFilePossible && bUseDevelopmentIni)
			return "fastman92limitAdjuster_GTAVCS_dev.ini";
		else
			return "fastman92limitAdjuster_GTAVCS.ini";
	}
	else if (CGameVersion::IsAny_GTA_CTW(gameVersion))
	{
		if (devFilePossible && bUseDevelopmentIni)
			return "fastman92limitAdjuster_GTACTW_dev.ini";
		else
			return "fastman92limitAdjuster_GTACTW.ini";
	}
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
	{
		if (devFilePossible && bUseDevelopmentIni)
			return "fastman92limitAdjuster_GTAIV_dev.ini";
		else
			return "fastman92limitAdjuster_GTAIV.ini";
	}
	else if (CGameVersion::IsAny_Bully_SE(gameVersion))
	{
		if (devFilePossible && bUseDevelopmentIni)
			return "fastman92limitAdjuster_BullyScholarship_dev.ini";
		else
			return "fastman92limitAdjuster_BullyScholarship.ini";
	}
	else if (CGameVersion::IsAny_GTA_V_WIN_X64(gameVersion))
	{
		if (devFilePossible && bUseDevelopmentIni)
			return "fastman92limitAdjuster_GTAV_dev.ini";
		else
			return "fastman92limitAdjuster_GTAV.ini";
	}
	else
		return nullptr;
}

// Get path to file from root directory
std::string CLimitAdjuster::GetPathToFlaFileFromRootDirectory(const char* filename)
{
	#if IS_PLATFORM_WIN
	if (PathIsRelativeA(filename))
	{
		std::string autoIDpath = std::string(this->StorageRootDirectory) + "\\AutoID3000\\fla\\" + filename;

		if (FileExistsA(autoIDpath.c_str()))
			return autoIDpath;
	}
	#endif

	return filename;
}

// Open INI file.
void CLimitAdjuster::OpenIniFile(const char* filename)
{
	bool bINIopened = INIreader.Open(filename);

	if (!bINIopened)
	{
		if (FileExistsA(filename))
			throw f92_runtime_error(
				"INI file %s exists, but could not be read. Click OK to close the game.",
				filename
			);

		printf_MessageBox(
			"INI file %s could not be read. It will be generated.",
			filename
		);

		if (!this->GenerateINIfile(filename))
			throw f92_runtime_error(
				"INI file %s could not be written. Click OK to close the game.",
				filename
			);

		bINIopened = INIreader.Open(filename);

		if (!bINIopened)
			throw f92_runtime_error(
				"Generated INI file %s could not be read. Click OK to close the game.",
				filename
			);
	}

	// Loop because of possibility to use a different INI
	while(true)
	{
		char authorStr[20];

		const char a[] = "\x52\x67\x67\x5c\x64\x68\xf7";

		char c;

		unsigned int d = 0;

		do
		{
			c = a[d] - (char)d + 15;
			authorStr[d] = c;

			d++;
		} while (d < sizeof(a));

		const char MAINencrypted[] = "\x3e\x33\x3c\x42\xf5";

		d = 0;
		char MAINstr[10];

		do
		{
			c = MAINencrypted[d] - (char)d + 15;
			MAINstr[d] = c;

			d++;
		} while (d < sizeof(MAINencrypted));

#if IS_PLATFORM_WIN
		INIreader.GetString(MAINstr, authorStr, NULL, cTmp, sizeof(cTmp));

		if (GTASA_CRC32_fromString(cTmp) != 0x01df2fb1)
		{
			const char msgEncrypted[] = "\x4a\x5f\x5d\x19\x6c\x60\x5d\x69\x1e\x60\x75\x75\x6a\x72\x76\x25\x75\x6d\x28\x75\x73\x78\x75\x81\x2e\x70\x74\x7b\x87\x86\x88\x7a\x88\x37\x81\x8c\x3a\x81\x7d\x90\x92\x8c\x81\x8f\x5b\x55\x52\x25";

			d = 0;
			char msgStr[100];

			do
			{
				c = msgEncrypted[d] - (char)d + 10;
				msgStr[d] = c;

				d++;
			} while (d < sizeof(msgEncrypted));

			printf_MessageBox(msgStr);
			crashTheGame();
		}
#endif

		// Possibility to make a different INI
		INIreader.GetString(MAINstr, "Use a different INI", NULL, cTmp, sizeof(cTmp));
		
#ifdef IS_PLATFORM_WIN
		char PathToDifferentINI[MAX_PATH];
		ExpandEnvironmentStringsA(cTmp, PathToDifferentINI, _countof(PathToDifferentINI));
#else
		const char* PathToDifferentINI = cTmp;
#endif
		
		if (cTmp[0])
		{
			INIreader.Close();
			INIreader.Open(PathToDifferentINI);
			
			continue;
		}

		break;
	}
}

namespace Configuration
{
	static const tConfigurationSectionEntry ConfigurationFuncArray_NO_NAME[] =
	{
		{
			"Plugin filename",
		BEGIN_FIELD_FUNCTION

			eGamePlatform platform = CGameVersion::GetPlatform(gameVersion);

			const char* filename = CLimitAdjuster::GetFLAlibraryFilename(platform);

			if (filename)
				pField->SetStrValue(filename, INI_FIELD_NONE, EXCEL_FIELD_STATE_SUPPORTED_ONLY_SHOW_VALUE);

			pField->SetComment("Filename of the FLA plugin.");
			END_FIELD_FUNCTION
		},

				{
			"INI filename",
		BEGIN_FIELD_FUNCTION

			const char* filename = CLimitAdjuster::GetIniFilenameForGame(gameVersion, false);

			if (filename)
				pField->SetStrValue(filename, INI_FIELD_NONE, EXCEL_FIELD_STATE_SUPPORTED_ONLY_SHOW_VALUE);
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_DYNAMIC_LIMITS[] =
	{
		{
			"ColModels",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_ColModelsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment("Number of different collisions that can be loaded.");
		END_FIELD_FUNCTION
		},

		{
			"VehicleStructs",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_3_0_WIN_X86

				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
				)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_VehicleStructsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

		pField->SetComment("Max number of vehicles with different IDs loaded.");
		END_FIELD_FUNCTION
		},

		{
			"rwObjectInstances",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_RwObjectInstancesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Matrices",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_MatricesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"PtrNode Singles",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_PtrNodeSinglesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"PtrNode Doubles",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86

				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_PtrNodeDoublesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"PtrNodes",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_PtrNodesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"EntryInfoNodes",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86
				
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_EntryInfoNodesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Peds",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_PedsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Vehicles",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_VehiclesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Objects",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_ObjectsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Tasks",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_TasksLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"CDummyTask",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_CDummyTaskLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Events",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_EventsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"PointRoute",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_PointRouteLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"PatrolRoute",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_PatrolRouteLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"InteriorInst",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_InteriorInstLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

			{
			"PortalInst",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_PortalInstLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
			},

			{
			"CAnimBlender",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_CAnimBlenderLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
			},

			{
			"CAtdNodeAnimChangePooledObject",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_CAtdNodeAnimChangePooledObjectLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
			},

		{
			"CAtdNodeAnimPlayer",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_CAtdNodeAnimPlayerLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"crFrameFilterBoneMask",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_crFrameFilterBoneMaskLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"crFrameFilterBoneAnalogue",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_crFrameFilterBoneAnalogueLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"crExpressionProcessor",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_crExpressionProcessorLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"crmtObserver",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_crmtObserverLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"NavMeshRoute",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_NavMeshRouteLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cam",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_CamLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"ExplosionType",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_ExplosionTypeLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"NodeRoute",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_NodeRouteLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"TaskAllocator",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_TaskAllocatorLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"PedIntelligence",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_PedIntelligenceLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"PedAttractors",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_PedAttractorsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"QuadTreeNodes",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_QuadTreeNodesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Collision links",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_CollisionLinksLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"CustomEnvMapPipeMatDataPool",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_CustomEnvMapPipeMatDataPoolLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"CustomEnvMapPipeAtmDataPool",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_CustomEnvMapPipeAtmDataPoolLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"CustomSpecMapPipeMaterialDataPool",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_CustomSpecMapPipeMaterialDataPoolLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Reach driver",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_ReachDriverLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Prop anim",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
			{
				pField->SetIntValue(
					g_dynamicLimits.ms_PropAnimLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_IPL[] =
	{
		{
			"Buildings",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_IPLsectionlimits.BuildingsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},
		
		{
			"Animated buildings",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_IPLsectionlimits.AnimatedBuildingsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Dummies",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86
				
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_IPLsectionlimits.DummiesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Inst entries per file",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_IPLsectionlimits.IPLentriesPerFileLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Entity index array",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_IPLsectionlimits.IPLentityIndexArrayLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Map zones",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_IPLsectionlimits.MapZonesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Navigation zones",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					g_IPLsectionlimits.NavigationZonesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"COccluder, apply coordinate limit patch",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_IPLsectionlimits.bCOccluderCoordLimitHackEnabled,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Interior occluders",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_IPLsectionlimits.InteriorOccludersLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Occluders",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_IPLsectionlimits.OccludersLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Timecycle modifiers",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_IPLsectionlimits.TcycLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"CULL mirror attribute zones",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_IPLsectionlimits.CullMirrorAttributeZonesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"CULL tunnel attribute zones",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_IPLsectionlimits.CullTunnelAttributeZonesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"CULL attribute zones",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_IPLsectionlimits.CullAttributeZonesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Stunt jumps",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_IPLsectionlimits.StuntJumpsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Entry exits",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_IPLsectionlimits.EntryExitsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Auzo zone boxes",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_IPLsectionlimits.AudioZoneBoxesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Auzo zone boxes, apply coordinate limit patch",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_IPLsectionlimits.bAudioZoneBoxesLimitSet,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Auzo zone spheres",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_IPLsectionlimits.AudioZoneSpheresLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Enable pickup limit patch",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					g_IPLsectionlimits.bPickupPatchEnabled,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Pickups",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					g_IPLsectionlimits.PickupsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Pickup collected",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					g_IPLsectionlimits.PickupsCollectedLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_IDE_LIMITS[] =
	{
		{
			"IDE Objects Type 1",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86
				)
			{
				pField->SetIntValue(
					g_IDEsectionLimits.ObjectsType1Limit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"IDE Objects Type 2",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86
				)
			{
				pField->SetIntValue(
					g_IDEsectionLimits.ObjectsType2Limit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Timed Objects",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86
				)
			{
				pField->SetIntValue(
					g_IDEsectionLimits.TimedObjectsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Hier Objects",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
				)
			{
				pField->SetIntValue(
					g_IDEsectionLimits.HierObjectsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment("Clump models");
		END_FIELD_FUNCTION
		},

		{
			"Vehicle Models",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86
				|| CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14718_WIN_X64
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86
				)
			{
				pField->SetIntValue(
					g_IDEsectionLimits.VehicleModelsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Ped Models",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86
				|| CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86
				)
			{
				pField->SetIntValue(
					g_IDEsectionLimits.PedModelsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Weapon Models",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86
				)
			{
				pField->SetIntValue(
					g_IDEsectionLimits.WeaponModelsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},


		{
			"2DFX Effects",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
				)
			{
				pField->SetIntValue(
					g_IDEsectionLimits._2dfxLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_MAP_LIMITS[] =
	{
		{
			"Apply tracks.dat coordinate limit patch",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_mapLimits.ms_bTracksDatCoordinateLimitPatchEnabled,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Tracks.dat file size limit",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				pField->SetIntValue(
					g_mapLimits.ms_tracksDatFileSizeLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Max number of track stations",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_mapLimits.ms_MaxNumberOfTrackStations,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Enable track config loader",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_mapLimits.ms_bNumberOfTracksDatFilesSet,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Apply paths limit patch",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					g_mapLimits.ms_bPathsPatchEnabled,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Enable path debugging",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_mapLimits.ms_bPathDebuggingEnabled,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment(
				"Make sure to increase 'OTHER LIMITS -> Coronas',"
				" because the path debugging registers a large number of coronas to be rendered."
			);
		END_FIELD_FUNCTION
		},

		{
			"Paths map size",
		BEGIN_FIELD_FUNCTION
			if (g_mapLimits.IsPathsMapSizePatchSupportedForGameVersion(gameVersion))
			{
				pField->SetIntValue(
					g_mapLimits.ms_pathsMapSize,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment("This option requires a new set of files if map size is changed!!!");
		END_FIELD_FUNCTION
		},

		{
			"Radar map size",
		BEGIN_FIELD_FUNCTION
			if (g_mapLimits.IsRadarMapSizePatchSupportedForGameVersion(gameVersion))
			{
				pField->SetIntValue(
					g_mapLimits.ms_radarMapSize,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment("This option requires a new set of files if map size is changed!!!");
		END_FIELD_FUNCTION
		},

		{
			"Enable frontend map different",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_mapLimits.ms_bIsFrontentMapDifferent,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Water map size",
		BEGIN_FIELD_FUNCTION
			if (g_mapLimits.IsWaterMapSizePatchSupportedForGameVersion(gameVersion))
			{
				pField->SetIntValue(
					g_mapLimits.ms_waterMapSize,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Renderware world map size",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_mapLimits.ms_rwWorldMapSize,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"World map size",
		BEGIN_FIELD_FUNCTION
			if (g_mapLimits.IsWorldMapSizePatchSupportedForGameVersion(gameVersion))
			{
				pField->SetIntValue(
					g_mapLimits.ms_worldMapSize,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"World sector size",
		BEGIN_FIELD_FUNCTION
			if (g_mapLimits.IsWorldMapSizePatchSupportedForGameVersion(gameVersion))
			{
				pField->SetIntValue(
					g_mapLimits.ms_worldSectorSize,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"World LOD sector size",
		BEGIN_FIELD_FUNCTION
			if (g_mapLimits.IsWorldMapSizePatchSupportedForGameVersion(gameVersion))
			{
				pField->SetIntValue(
					g_mapLimits.ms_worldLODsectorSize,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_LEVEL_LIMITS[] =
	{
		{
			"Number of levels",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					4,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment(
				"Level limits are enabled if you uncomment 'Number of levels'\n"
				"Currently it's only possible to put the default ped IDs for levels.\n"
				"Random IDs won't work for peds"
			);
		END_FIELD_FUNCTION
		},

		{
			"Cop car level 0",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					599,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cop car level 1",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					596,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cop car level 2",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					597,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cop car level 3",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					598,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cop bike",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					523,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cop ped level 0",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					283,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cop ped level 1",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					280,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cop ped level 2",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					281,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cop ped level 3",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					282,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cop ped bike",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					284,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Ambulance level 1",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					416,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Ambulance level 2",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					416,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Ambulance level 3",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					416,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Medic level 1",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					274,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Medic level 2",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					275,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Medic level 3",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					276,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Fire engine level 1",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					407,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Fire engine level 2",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					407,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Fire engine level 3",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					407,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Fireman level 1",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					277,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Fireman level 2",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					279,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Fireman level 3",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					278,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Number of cab drivers for level 0",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					0,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Number of cab drivers for level 1",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					2,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cab driver level 1 place 0",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					262,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cab driver level 1 place 1",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					261,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Number of cab drivers for level 2",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					2,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cab driver level 2 place 0",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					220,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cab driver level 2 place 1",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					234,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Number of cab drivers for level 3",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					2,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cab driver level 3 place 0",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					182,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cab driver level 3 place 1",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					206,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Item price multiplier 0",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetDoubleValue(
					1.0,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Item price multiplier 1",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetDoubleValue(
					1.0,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Item price multiplier 2",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetDoubleValue(
					1.0,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Item price multiplier 3",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetDoubleValue(
					1.2,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_VEHICLE_SPECIAL_FEATURES[] =
	{
		{
			"Enable special features",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					0,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Number of hydra vehicles",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					1,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Hydra 1",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					520,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Number of ZR350 vehicles",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					1,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"ZR350 1",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					477,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_RESTARTS[] =
	{
		{
			"Max number of hospital restarts",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					g_Restarts.HospitalRestartsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
			else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
			{
				pField->SetIntValue(
					g_Restarts.HospitalRestartsLimit,
					INI_FIELD_NONE,
					EXCEL_FIELD_STATE_NOT_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Max number of police restarts",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					g_Restarts.PoliceRestartsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
			else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
			{
				pField->SetIntValue(
					g_Restarts.PoliceRestartsLimit,
					INI_FIELD_NONE,
					EXCEL_FIELD_STATE_NOT_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_IMG_LIMITS[] =
	{
		{
			"Max number of IMG archives",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_IMGlimits.maxNumberOfIMGarchives,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Enable handling of new enhanced IMG archives",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_IMGlimits.bHandlingOfNewEnhancedFormatOfImgArchivesEnabled,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Increase the IMG archive size limit",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Enable handling of IMGLIST keyword",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					true,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_DIRECTORY_LIMITS[] =
	{
		{
			"Extra objects directory",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_directoryLimits.ms_iExtraObjectsDirLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cutscene directory",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_directoryLimits.ms_iCutsceneDirLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Clothes directory",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_directoryLimits.ms_iClothesDirLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_WATER_LIMITS[] =
	{
		{
			"Water triangles",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_waterLimits.WaterTrianglesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Water quads",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_waterLimits.WaterQuadsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Water quads and triangles list",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_waterLimits.WaterQuadsAndTrianglesListLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Water vertices",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_waterLimits.WaterVerticesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Blocks to be rendered outside world",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_waterLimits.BlocksToBeRenderedOutsideWorldLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_CAR_STREAMING[] =
	{
		{
			"Cargrp cars per group",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					g_cargrpLimits.CPopulation__m_iCarsPerGroup,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment(
				"Max number you can put is 63.\n"
				"Do not put more unless this 63 limit will be removed in the next version of limit adjuster.\n"
				"Remember to increase a limit of VehicleStructs appropriately!\n"
				"Otherwise the game will crash after few minutes of playing, because a limit of VehicleStructs will be exceeded."
			);
		END_FIELD_FUNCTION
		},

		{
			"Streaming_DesiredNumberOfVehiclesLoaded",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_streamingLimits.Streaming_DesiredNumberOfVehiclesLoaded,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Car generators",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_carGeneratorLimits.iCarGenerators,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Number of process counter passes for car generators",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					4,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Use extended format for car generators",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Accept any ID for car generator",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_PED_STREAMING[] =
	{
		{
			"Pedgrp peds per group",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					g_pedGrpLimits.m_iPedsPerGroup,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
			else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
			{
				pField->SetIntValue(
					g_pedGrpLimits.m_iPedsPerGroup,
					INI_FIELD_NONE,
					EXCEL_FIELD_STATE_NOT_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_STREAMING[] =
	{
		{
			"Memory available",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86
				|| CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| CGameVersion::Is_GTA_SA_1_0_1_EU_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_III_1_8_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_VC_1_09_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_streamingLimits.MemoryAvailable / 1024 / 1024,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Max number of stream handles",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_streamingLimits.iStreamHandlesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Number of requested models above which the game considers loading very busy",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_streamingLimits.NumberOfRequestedModelsWhenGameConsidersLoadingVeryBusy,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Minimum number of iterations in LoadAllRequestedModels",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_streamingLimits.MinimumNumberOfIterationsInLoadAllRequestedModels,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_RENDERER_LIMITS[] =
	{
		{
			"Invisible entity pointers",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_rendererLimits.ms_InvisibleEntityPtrsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Visible super LOD pointers",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_rendererLimits.ms_VisibleSuperLodPtrsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Visible LOD pointers",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_rendererLimits.ms_VisibleLodPtrsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Visible entity pointers",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_rendererLimits.ms_VisibleEntityPtrsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_VISIBILITY_LIMITS[] =
	{
		{
			"Alpha list limit",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_visibilityLimits.ms_alphaListLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Alpha boat atomic list limit",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_visibilityLimits.ms_alphaBoatAtomicListLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Alpha entity list limit",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_visibilityLimits.ms_alphaEntityListLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Alpha underwater entity list limit",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_visibilityLimits.ms_alphaUnderwaterEntityListLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Alpha really draw last list limit",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_visibilityLimits.ms_alphaReallyDrawLastListLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Weapon peds for PC limit",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_visibilityLimits.ms_weaponPedsForPCLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	template <typename enumType> void ProcessIDlimitField(CConfigurationField* pField, eFieldProcessMode fieldProcessMode, enumType fileType)
	{
		const tFileTypeInfo* pFileTypeInfo = g_fileIDlimits.GetFileTypeInfo(fileType);

		if (!pFileTypeInfo)
			return;

		// do not add file type of path nodes to .ini
		if (fieldProcessMode == FIELD_PROCESS_MODE_INI_FILE
			&& pFileTypeInfo->pFileTypeDescriptor->generalFileType == GENERAL_FILE_TYPE_PATH_NODES)
			return;

		tFileTypeBaseID defaultCount = g_fileIDlimits.GetFileIDdefaultLimit(fileType);

		if (defaultCount)
		{
			eFileType fileType = pFileTypeInfo->fileType;
			const char* fileTypeStr = CFileTypeInfo::GetEnumNameByMember(fileType);
			
			pField->SetINIkeyName(fileTypeStr);
			
			if (g_fileIDlimits.CanLimitBeChanged(fileType))
			{
				if (fieldProcessMode == FIELD_PROCESS_MODE_EXCEL)
				{
					char buffer[64];
					sprintf(buffer, "%d, max=%d", defaultCount, pFileTypeInfo->maxLimitValue);

					pField->SetStrValue(
						buffer,
						INI_FIELD_INACTIVE,
						EXCEL_FIELD_STATE_SUPPORTED
					);
				}
				else
					pField->SetIntValue(
						defaultCount,
						INI_FIELD_INACTIVE,
						EXCEL_FIELD_STATE_SUPPORTED
					);
			}
			else
			{
				pField->SetIntValue(
					defaultCount,
					INI_FIELD_NONE,
					EXCEL_FIELD_STATE_NOT_SUPPORTED
				);
			}
		}
	}

	static const tConfigurationSectionEntry ConfigurationFuncArray_ID_LIMITS[] =
	{

		{
			"Total count of files",
		BEGIN_FIELD_FUNCTION
			bool bCanIDlimitsBeModified = g_fileIDlimits.IsThereAnyIDlimitThatCanBeModified();

			auto maxCountOfFileIDs = g_fileIDlimits.GetMaxNumberOfFileIDs();

			eExcelFieldState excelFieldState;

			if (bCanIDlimitsBeModified)
				excelFieldState = EXCEL_FIELD_STATE_SUPPORTED_ONLY_SHOW_VALUE;
			else
				excelFieldState = EXCEL_FIELD_STATE_NOT_SUPPORTED_ONLY_SHOW_VALUE;

			if(maxCountOfFileIDs == 0)
				pField->SetStrValue(
					"",
					INI_FIELD_NONE,
					excelFieldState
				);
			else if(maxCountOfFileIDs >= INT_MAX)
				pField->SetStrValue(
					"unlimited",
					INI_FIELD_NONE,
					excelFieldState
				);
			else
				pField->SetIntValue(
					maxCountOfFileIDs,
					INI_FIELD_NONE,
					excelFieldState
				);
			
	END_FIELD_FUNCTION
		},

		{
			"Apply ID limit patch",
		BEGIN_FIELD_FUNCTION
			if (g_fileIDlimits.IsThereAnyIDlimitThatCanBeModified())
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
	END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_MODEL / FILE_TYPE_DFF / FILE_TYPE_NIF",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, GENERAL_FILE_TYPE_MODEL_ARCHIVE);
		END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_TXD / FILE_TYPE_NFT / FILE_TYPE_WTD",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, GENERAL_FILE_TYPE_TEXTURE_ARCHIVE);
		END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_COL",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, GENERAL_FILE_TYPE_COLLISION_ARCHIVE);
		END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_AGR",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, FILE_TYPE_AGR);
		END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_DAT / FILE_TYPE_NOD",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, GENERAL_FILE_TYPE_PATH_NODES);
		END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_IPL / FILE_TYPE_MAP_PLACEMENT / FILE_TYPE_IPB",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, GENERAL_FILE_TYPE_ITEM_PLACEMENT);
		END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_IFP / FILE_TYPE_WAD",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, GENERAL_FILE_TYPE_ANIMATION_ARCHIVE);
		END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_RRR",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, GENERAL_FILE_TYPE_CAR_RECORDING);
		END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_LIP",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, FILE_TYPE_LIP);
		END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_CAT",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, FILE_TYPE_CAT);
		END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_SCM",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, GENERAL_FILE_TYPE_SCM);
		END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_LUR",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, FILE_TYPE_LUR);
		END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_LOADED_START",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, FILE_TYPE_LOADED_START);
		END_FIELD_FUNCTION
		},

		{
			"FILE_TYPE_REQUESTED_START",
		BEGIN_FIELD_FUNCTION
			ProcessIDlimitField(pField, fieldProcessMode, FILE_TYPE_REQUESTED_START);
		END_FIELD_FUNCTION
		},

		{
			"Use file binary search by name",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment(
				"Binary search speeds up the time that it takes a game to find the ID of file, when searching for it by the name.\n"
				"This is really nice to have enabled when using milion models or more.\n"
				"Rockstar Games noticed how it's useful and implemented it later in GTA IV. Now possible in GTA SA."
			);
		END_FIELD_FUNCTION
		},

		{
			"Count of killable model IDs",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_fileIDlimits.CDarkel__CountOfKillableModelIDs,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment(
				"In game there's an array CDarkel::RegisteredKills and it stores the number of registered kills for model IDs.\n"
				"Model IDs that may be killed are vehicles/peds.\n"
				"Default value of 800, means that 0-799 is valid ID for ped/vehicle.\n\n"
				"As such, this value will affect the max possible ID for ped/vehicle."
			);
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	bool IsHandlingCfgPatchSupportedForGameVersion(eGameVersion gameVersion)
	{
		return gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86
			|| CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
			|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
			|| gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
			|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
			|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
			|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86;
	}

	void ProcessHandlingCfgLimitFieldAllGames(
		CConfigurationField* pField,
		eGameVersion gameVersion,
		unsigned int limit)
	{
		if (IsHandlingCfgPatchSupportedForGameVersion(gameVersion))
		{
			pField->SetIntValue(
				limit,
				INI_FIELD_INACTIVE,
				EXCEL_FIELD_STATE_SUPPORTED
			);
		}
	}

	static const tConfigurationSectionEntry ConfigurationFuncArray_HANDLING_CFG_LIMITS[] =
	{
		{
			"Apply handling.cfg patch",
		BEGIN_FIELD_FUNCTION
			ProcessHandlingCfgLimitFieldAllGames(
				pField,
				gameVersion,
				false
			);
		END_FIELD_FUNCTION
		},

		{
			"Number of standard lines",
		BEGIN_FIELD_FUNCTION
			ProcessHandlingCfgLimitFieldAllGames(
				pField,
				gameVersion,
				g_handlingCfgLimits.ms_iStandardLinesLimit
			);
		END_FIELD_FUNCTION
		},


		{
			"Number of bike lines",
		BEGIN_FIELD_FUNCTION
			ProcessHandlingCfgLimitFieldAllGames(
				pField,
				gameVersion,
				g_handlingCfgLimits.ms_iBikeLinesLimit
			);
		END_FIELD_FUNCTION
		},

		{
			"Number of flying lines",
		BEGIN_FIELD_FUNCTION
			ProcessHandlingCfgLimitFieldAllGames(
				pField,
				gameVersion,
				g_handlingCfgLimits.ms_iFlyingLinesLimit
			);
		END_FIELD_FUNCTION
		},

		{
			"Number of boat lines",
		BEGIN_FIELD_FUNCTION
			ProcessHandlingCfgLimitFieldAllGames(
				pField,
				gameVersion,
				g_handlingCfgLimits.ms_iBoatLinesLimit
			);
		END_FIELD_FUNCTION
		},

		{
			"Number of animation group lines",
		BEGIN_FIELD_FUNCTION
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			pField->SetIntValue(
				g_handlingCfgLimits.ms_iAnimationGroupLinesLimit,
				INI_FIELD_INACTIVE,
				EXCEL_FIELD_STATE_SUPPORTED
			);
		}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_SCM_LIMITS[] =
	{
		{
			"Max size of MAIN segment",
		BEGIN_FIELD_FUNCTION
			if (g_SCMlimits.ScriptSpaceLimitsCheckIfSupportedVersion(gameVersion))
			{
				pField->SetIntValue(
					g_SCMlimits.iMAINsegmentSize,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Max mission size",
		BEGIN_FIELD_FUNCTION
			if (g_SCMlimits.ScriptSpaceLimitsCheckIfSupportedVersion(gameVersion))
			{
				pField->SetIntValue(
					g_SCMlimits.iMissionSize,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Running scripts",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_SCMlimits.ms_iScriptsArrayLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Mission cleanup",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_SCMlimits.ms_iMissionCleanupLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Max number of used objects",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_SCMlimits.ms_iUsedObjectArrayLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Scripts for brains",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_SCMlimits.ms_iScriptsForBrainsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Switch jump table cases",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_SCMlimits.ms_iScriptJumpTableLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_OTHER_LIMITS[] =
	{
		{
			"Coronas",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_otherLimits.ms_iCoronasLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Collision size",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_otherLimits.ms_maxSizeOfSingleCollision,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Cover points",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_otherLimits.ms_iCoverPointLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"LOD distance",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetDoubleValue(
					g_otherLimits.LODdistance,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Max number of particles active",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_otherLimits.ms_iMaxNumberOfParticlesActive,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Object info entries",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					g_otherLimits.ms_iObjectInfoLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment(
				"Max number of object.dat entries.\n"
				"5 first entries of array are reserved for hardcoded purpose."
			);

		END_FIELD_FUNCTION
		},

		{
			"Radar traces",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_otherLimits.ms_iRadarTracesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"References",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_otherLimits.ms_iReferencesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Set pieces",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_otherLimits.ms_iSetPiecesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Set pieces, apply coordinate limit patch",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Vehicle colors",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
			{
				pField->SetIntValue(
					g_otherLimits.ms_iVehicleColorsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Number of plate textures",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_otherLimits.ms_iNumberOfPlateTextures,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_ROADBLOCK_LIMITS[] =
	{
		{
			"Apply roadblox.dat better loader",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment("Make it possible to use a roadblox.dat of variable size.");
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_SHADOW_LIMITS[] =
	{
		{
			"Shadows stored",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_shadowLimits.ms_ShadowsStoredLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Poly bunches",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_shadowLimits.ms_PolyBunchesLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Static shadows",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_shadowLimits.ms_StaticShadowsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Permanent shadows",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_shadowLimits.ms_PermanentShadowsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Real time shadows",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_shadowLimits.ms_RealTimeShadowsLimit,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_WEAPON_LIMITS[] =
	{
		{
			"Enable weapon type loader ",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Weapon type loader, number of type IDs",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_weaponLimits.NumberOfWeaponTypes,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Enable melee combo type loader",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Max number of melee combos",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_weaponLimits.MaxNumberOfCombos,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_SPECIAL[] =
	{
		{
			"Enable loading text",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_III_1_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_III_1_8_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Disable radar rotation",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Disable plane speed limit",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Make helicopters land on water when cars on water cheat enabled",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Make save of variable size",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Make paintjobs work for any ID",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Fix keyboard making bad mouse movement",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Fix cheats typed by keyboard not working",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Alter file loading order",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_III_1_8_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_VC_1_09_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_SA_GER_2_09_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_BULLY_AE_1_0_0_18_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					true,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment(
				"Alters the file loading loading.\n"
				"Files from game root directory will take a precedence over files from APK archive.\n"
				"Useful to edit handling.cfg for example."
			);
		END_FIELD_FUNCTION
		},

		{
			"Remove LOD DFF requirement to hold native data",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					true,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Fix crashes on newer systems",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_SA_GER_2_09_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_LCS_2_4_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_BULLY_AE_1_0_0_18_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_CTW_1_04_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					true,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

	{
			"Make loading of files from root directory possible",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_LCS_2_4_ANDROID_ARMEABI_V7A)
			{
				pField->SetIntValue(
					true,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment(
				"Makes loading of files from game root directory possible.\n"
				"Files should be placed at [STORAGE]/Android/data/[PACKAGE_NAME]/files"
			);
		END_FIELD_FUNCTION
	},

	{
			"Disable CINFO.BIN and MINFO.BIN loading",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
				|| gameVersion == GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14718_WIN_X64)
			{
				pField->SetIntValue(
					true,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
	},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_ERROR_REPORTING[] =
	{
		{
			"Enable error reporting",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					true,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Attempt to load object instance with undefined ID",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					true,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Car generator limit exceeded",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Car generator with invalid model ID is getting registered",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					true,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"IMG archive needs rebuilding",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					true,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Model does not have collision loaded",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					true,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Model has collision already set up",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Model name is declared on multiple IDs",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Requested file does not exist",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Stream handles limit exceeded",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					true,
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_DEBUG_OUTPUT[] =
	{
		{
			"Enable debug output",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14718_WIN_X64)
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

			pField->SetComment(
				"Enables debug output from sprintf and printf functions."
			);
		END_FIELD_FUNCTION
		},

		{
			"Enable logging of files loaded",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_DEBUGGING[] =
	{
		{
			"Copy info to pad 1 from pad 0",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};
	
	static const tConfigurationSectionEntry ConfigurationFuncArray_PLUGIN_PATCHES[] =
	{
		{
			"Enable plugin patches",
		BEGIN_FIELD_FUNCTION

		return;

		eGamePlatform platform = CGameVersion::GetPlatform(gameVersion);

			if (platform == GAME_PLATFORM_WIN_X86)
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
			END_FIELD_FUNCTION
		},

		{
			"Enable CLEO loading",
		BEGIN_FIELD_FUNCTION
		if (!IsCLEOloadingImplementedByTheFLA())
			return;

		eGamePlatform platform = CGameVersion::GetPlatform(gameVersion);

		if (platform == GAME_PLATFORM_ANDROID_ARMEABI_V7A)
		{
			pField->SetIntValue(
				true,
				INI_FIELD_ACTIVE,
				EXCEL_FIELD_STATE_SUPPORTED
			);
		}
		END_FIELD_FUNCTION
		},

		{
			"Enable CLEO patches",
		BEGIN_FIELD_FUNCTION
		if (!IsCLEOloadingImplementedByTheFLA())
			return;

		eGamePlatform platform = CGameVersion::GetPlatform(gameVersion);

		if (platform == GAME_PLATFORM_ANDROID_ARMEABI_V7A)
		{
			pField->SetIntValue(
				true,
				INI_FIELD_ACTIVE,
				EXCEL_FIELD_STATE_SUPPORTED
			);
		}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_ADDONS[] =
	{
		{
			"Enable cheat string loader",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Enable vehicle audio loader",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86
				|| CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
				|| CGameVersion::Is_GTA_SA_1_0_1_EU_WIN_X86(gameVersion)
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
				|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86

				|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
				)
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Enable FXT loader",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_3_0_WIN_X86
				|| CGameVersion::IsAny_GTA_V_WIN_X64(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Enable train type carriages loader",
		BEGIN_FIELD_FUNCTION

			if (g_trainTypeCarriageLoader.IsLoaderImplementedForThisGameVersion(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
			
		END_FIELD_FUNCTION
		},

		{
			"Train type carriage loader, max number of vehicles for type",
		BEGIN_FIELD_FUNCTION

			if (g_trainTypeCarriageLoader.IsLoaderImplementedForThisGameVersion(gameVersion))
			{
				pField->SetIntValue(
					g_trainTypeCarriageLoader.ms_maxNumberOfVehiclesForType,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

		END_FIELD_FUNCTION
		},

		{
			"Train type carriage loader, number of type IDs",
		BEGIN_FIELD_FUNCTION

			if (g_trainTypeCarriageLoader.IsLoaderImplementedForThisGameVersion(gameVersion))
			{
				pField->SetIntValue(
					g_trainTypeCarriageLoader.ms_numberOfTypeIDs,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}

		END_FIELD_FUNCTION
		},

		{
			"Enable radar blip sprite filename loader",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Radar blip sprite filename loader, number of type IDs",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				pField->SetIntValue(
					g_RadarBlipSpriteFilenameLoader.ms_numberOfTypeIDs,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Enable model special feature loader",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Enable not a prop ID range loader",
		BEGIN_FIELD_FUNCTION
			if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		SECTION_FIELD_EOF
	};

	static const tConfigurationSectionEntry ConfigurationFuncArray_MAIN[] =
	{
		{
			"author",
		BEGIN_FIELD_FUNCTION
			pField->SetStrValue(
					fieldProcessMode != FIELD_PROCESS_MODE_EXCEL ? "fastman92" : "",
					INI_FIELD_ACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED_ONLY_SHOW_VALUE
				);
			
		END_FIELD_FUNCTION
		},

		{
			"Disable FLA loading text",
		BEGIN_FIELD_FUNCTION
		if (gameVersion == GAME_VERSION_GTA_III_1_0_WIN_X86

		|| gameVersion == GAME_VERSION_GTA_III_1_8_ANDROID_ARMEABI_V7A

			|| gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86

			|| gameVersion == GAME_VERSION_GTA_VC_1_09_ANDROID_ARMEABI_V7A

			|| gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86

			|| CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
			|| gameVersion == GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A
			|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
			|| gameVersion == GAME_VERSION_GTA_SA_GER_2_09_ANDROID_ARMEABI_V7A
			)
		{
			pField->SetIntValue(
				false,
				INI_FIELD_INACTIVE,
				EXCEL_FIELD_STATE_SUPPORTED
			);
		}
		END_FIELD_FUNCTION
		},

		{
			"FLA main window disable code",
		BEGIN_FIELD_FUNCTION
		eGamePlatform platform = CGameVersion::GetPlatform(gameVersion);

		if (platform == GAME_PLATFORM_WIN_X86
			|| platform == GAME_PLATFORM_WIN_X64)
		{
			pField->SetStrValue(
				"",
				INI_FIELD_ACTIVE,
				EXCEL_FIELD_STATE_SUPPORTED_ONLY_SHOW_VALUE
			);
		}
		END_FIELD_FUNCTION
		},

		{
			"Game language",
		BEGIN_FIELD_FUNCTION
			if (CGameVersion::IsAny_GTA_V(gameVersion))
			{
				pField->SetIntValue(
					false,
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);
			}
		END_FIELD_FUNCTION
		},

		{
			"Register global exception handler",
		BEGIN_FIELD_FUNCTION
		eGamePlatform platform = CGameVersion::GetPlatform(gameVersion);

		if (GamePlatform::IsPlatformWindows(platform) || GamePlatform::IsPlatformAndroid(platform))
		{
			pField->SetIntValue(
				true,
				INI_FIELD_ACTIVE,
				EXCEL_FIELD_STATE_SUPPORTED
			);
		}

		pField->SetComment(
			"Crash exception handler\n"
			"You should leave it enabled or there will be no crash log.\n"
			"Please don't disable it unless you have a good reason."
		);

		END_FIELD_FUNCTION
		},

		{
			"Enable windowed mode",
		BEGIN_FIELD_FUNCTION
		if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
		{
			pField->SetIntValue(
				false,
				INI_FIELD_INACTIVE,
				EXCEL_FIELD_STATE_SUPPORTED
			);
		}
		END_FIELD_FUNCTION
		},

		{
			"Disable music on global exception handler",
		BEGIN_FIELD_FUNCTION
		eGamePlatform platform = CGameVersion::GetPlatform(gameVersion);

		if (GamePlatform::IsPlatformWindows(platform))			
		{
			pField->SetIntValue(
				false,
				INI_FIELD_INACTIVE,
				EXCEL_FIELD_STATE_SUPPORTED
			);
		}
		END_FIELD_FUNCTION
		},

		#ifdef SYSTEM_PROPERLY_IMPLEMENTED
			/*

		{
			"Disable online content",
		BEGIN_FIELD_FUNCTION
			pField->SetIntValue(
				true,
				INI_FIELD_INACTIVE,
				EXCEL_FIELD_STATE_SUPPORTED
			);

		END_FIELD_FUNCTION
		},
		*/

		{
			"Enable online content",
		BEGIN_FIELD_FUNCTION
			pField->SetIntValue(
				g_OnlineContent.IsOnlineContentEnabled(),
				INI_FIELD_ACTIVE,
				EXCEL_FIELD_STATE_SUPPORTED
			);

		END_FIELD_FUNCTION
		},

		#endif

		{
			"Use a different INI",
		BEGIN_FIELD_FUNCTION
			pField->SetStrValue(
					"",
					INI_FIELD_INACTIVE,
					EXCEL_FIELD_STATE_SUPPORTED
				);

		END_FIELD_FUNCTION
		}, 

		SECTION_FIELD_EOF
	};

////////////////////////////////

	static const tConfigurationSection ConfigurationSectionArray[] =
	{		
		{
			"",
			ConfigurationFuncArray_NO_NAME
		},

		{
			"DYNAMIC LIMITS",
			ConfigurationFuncArray_DYNAMIC_LIMITS
		},
		
		{
			"IPL",
			ConfigurationFuncArray_IPL
		},

		{
			"IDE LIMITS",
			ConfigurationFuncArray_IDE_LIMITS
		},

		{
			"MAP LIMITS",
			ConfigurationFuncArray_MAP_LIMITS
		},

		{
			"LEVEL LIMITS",
			ConfigurationFuncArray_LEVEL_LIMITS
		},

		{
			"VEHICLE SPECIAL FEATURES",
			ConfigurationFuncArray_VEHICLE_SPECIAL_FEATURES
		},

		{
			"RESTARTS",
			ConfigurationFuncArray_RESTARTS
		},

		{
			"IMG LIMITS",
			ConfigurationFuncArray_IMG_LIMITS
		},

		{
			"DIRECTORY LIMITS",
			ConfigurationFuncArray_DIRECTORY_LIMITS
		},

		{
			"WATER LIMITS",
			ConfigurationFuncArray_WATER_LIMITS
		},

		{
			"CAR STREAMING",
			ConfigurationFuncArray_CAR_STREAMING
		},

		{
			"PED STREAMING",
			ConfigurationFuncArray_PED_STREAMING
		},

		{
			"STREAMING",
			ConfigurationFuncArray_STREAMING
		},

		{
			"RENDERER LIMITS",
			ConfigurationFuncArray_RENDERER_LIMITS
		},

		{
			"VISIBILITY LIMITS",
			ConfigurationFuncArray_VISIBILITY_LIMITS
		},

		{
			"ID LIMITS",
			ConfigurationFuncArray_ID_LIMITS
		},

		{
			"HANDLING.CFG LIMITS",
			ConfigurationFuncArray_HANDLING_CFG_LIMITS
		},

		{
			"SCM LIMITS",
			ConfigurationFuncArray_SCM_LIMITS
		},

		{
			"OTHER LIMITS",
			ConfigurationFuncArray_OTHER_LIMITS
		},

		{
			"ROADBLOCK LIMITS",
			ConfigurationFuncArray_ROADBLOCK_LIMITS
		},

		{
			"SHADOW LIMITS",
			ConfigurationFuncArray_SHADOW_LIMITS
		},

		{
			"WEAPON LIMITS",
			ConfigurationFuncArray_WEAPON_LIMITS
		},

		{
			"SPECIAL",
			ConfigurationFuncArray_SPECIAL
		},

		{
			"ERROR REPORTING",
			ConfigurationFuncArray_ERROR_REPORTING
		},

		{
			"DEBUG OUTPUT",
			ConfigurationFuncArray_DEBUG_OUTPUT
		},

		{
			"DEBUGGING",
			ConfigurationFuncArray_DEBUGGING
		},

		{
			"PLUGIN PATCHES",
			ConfigurationFuncArray_PLUGIN_PATCHES
		},

		{
			"ADDONS",
			ConfigurationFuncArray_ADDONS
		},

		{
			"MAIN",
			ConfigurationFuncArray_MAIN
		},

		{ nullptr, nullptr }
	};
}

// Generates INI file
bool CLimitAdjuster::GenerateINIfile(const char* filename)
{
	//////
	g_OnlineContent.AskUserToEnableOnlineContent();
	//////

	FILE* fp = fopen(filename, "w");	

	if (!fp)
		return false;

	char* onlyFilename = GetFilenameFromPath(filename);

	using namespace Configuration;

	CConfigurationField field;
	char comment[sizeof(((CConfigurationField*)0)->comment) + 200];

	fprintf(fp, "; %s",
		onlyFilename
	);

	// Iterate over sections
	const tConfigurationSection* pSection = ConfigurationSectionArray;

	while (pSection->sectionName)
	{
		// Skip section with no name
		if (!pSection->sectionName[0])
		{
			pSection++;
			continue;
		}

		bool bSectionNameWritten = false;

		// Iterate over fields
		const tConfigurationSectionEntry* pFieldDescriptor = pSection->pFieldDescriptorArray;

		while (pFieldDescriptor->pFunc)
		{
			pFieldDescriptor->pFunc(&field, FIELD_PROCESS_MODE_INI_FILE);

			const char* pINIkey = pFieldDescriptor->key;

			// for few fields only, ID LIMITS come to mind
			if (field.INIkeyName[0])
				pINIkey = field.INIkeyName;
			
			// Replaces new lines in comment with ;
			{
				int i = 0;
				int j = 0;

				if (field.comment[i])
				{
					comment[j++] = ';';
					comment[j++] = ' ';

					while (field.comment[i])
					{
						if (field.comment[i] == '\n')
						{
							comment[j++] = '\n';
							comment[j++] = ';';
							comment[j++] = ' ';
						}
						else
							comment[j++] = field.comment[i];

						i++;
					}

					comment[j++] = '\n';
				}

				comment[j] = 0;		// NULL character
			}

			if (field.INIstate == INI_FIELD_ACTIVE || field.INIstate == INI_FIELD_INACTIVE)
			{
				// Write a section name
				// Only if there is at least one available INI field
				if (!bSectionNameWritten)
				{
					fprintf(fp, "\n\n[%s]", pSection->sectionName);
					bSectionNameWritten = true;
				}
				else
					fwrite("\n", 1, 1, fp);

				char commentCharStr[2];

				if (field.INIstate == INI_FIELD_INACTIVE)
				{
					commentCharStr[0] = '#';
					commentCharStr[1] = 0;
				}
				else
					commentCharStr[0] = 0;

				char valueStr[256];

				if (field.ValueToStr(valueStr))
				{
					fprintf(fp,
						"\n; %s (%s)\n"
						"%s"
						"%s%s = %s",
						pINIkey, valueStr,
						comment,
						commentCharStr, pINIkey, valueStr
					);
				}
			}

			pFieldDescriptor++;
		}

		pSection++;
	}

	fclose(fp);

	return true;
}

// Configuration
namespace Configuration
{
	static const eGameVersion WIN_X86_applicationList[] =
	{
		GAME_VERSION_GTA_III_1_0_WIN_X86,
		GAME_VERSION_GTA_VC_1_0_WIN_X86,
		GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86,
		GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86,
		GAME_VERSION_GTA_SA_1_0_1_EURO_NO_CD_FIXED_EXE_WIN_X86,
		GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86,
		GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86,
		GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86,
		GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86,
		GAME_VERSION_GTA_EFLC_1_1_3_0_WIN_X86,
		GAME_VERSION_BULLY_SE_1_2_WIN_X86,

		GAME_VERSION_UNDEFINED
	};

	static const eGameVersion WIN_X64_applicationList[] =
	{
		GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14718_WIN_X64,
		GAME_VERSION_GTA_V_ANY_WIN_X64,

		GAME_VERSION_UNDEFINED
	};

	static const eGameVersion ANDROID_ARMEABI_V7A_applicationList[] =
	{
		GAME_VERSION_GTA_III_1_8_ANDROID_ARMEABI_V7A,
		GAME_VERSION_GTA_VC_1_09_ANDROID_ARMEABI_V7A,
		GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A,
		GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A,
		GAME_VERSION_GTA_SA_GER_2_09_ANDROID_ARMEABI_V7A,
		GAME_VERSION_GTA_LCS_2_4_ANDROID_ARMEABI_V7A,
		GAME_VERSION_GTA_CTW_1_04_ANDROID_ARMEABI_V7A,
		GAME_VERSION_BULLY_AE_1_0_0_18_ANDROID_ARMEABI_V7A,

		GAME_VERSION_UNDEFINED
	};

	static const eGameVersion ANDROID_ARM64_V8A_applicationList[] =
	{
		GAME_VERSION_GTA_SA_2_10_ANDROID_ARM64_V8A,
		GAME_VERSION_UNDEFINED
	};
	
	#define PLATFORM_CONFIGURATION_ENTRY(platformName) { #platformName, platformName##_applicationList }

	const tPlatformConfiguration platformList[] =
	{
		PLATFORM_CONFIGURATION_ENTRY(WIN_X86),
		PLATFORM_CONFIGURATION_ENTRY(WIN_X64),
		PLATFORM_CONFIGURATION_ENTRY(ANDROID_ARMEABI_V7A),
		// PLATFORM_CONFIGURATION_ENTRY(ANDROID_ARM64_V8A),

		PLATFORM_CONFIGURATION_EOF
	};
}

// Generate documentation files
void CLimitAdjuster::GenerateDocumentationFiles()
{
	using namespace Configuration;
	
	
#ifdef IS_PLATFORM_WIN_X86
	// The environment variable above is set on author's computer only.
	// Users don't need to have an Excel file generated.
	if (!this->FLA_release_directory[0])
	{		
		CGenericLogStorage::SaveTextLn(
			"FASTMAN92_LIMIT_ADJUSTER_RELEASE_DIRECTORY is not defined. Documentation files will not be written."
		);

		return;
	}
	
	tDocumentationWorkbook FLAworkbook;
	Workbook::InitializeDocumentationWorkbook(
		this,		
		&FLAworkbook,
		platformList,
		ConfigurationSectionArray
		);

	// File path
	char filePath[MAX_PATH];

	// Excel file
	{
		sprintf(filePath, "%s\\documentation\\Documentation.xlsm", FLA_release_directory);

		if (!FileExistsA(filePath))
			Configuration::Formats::WriteXMLexcelFile(&FLAworkbook, filePath);
		else
			CGenericLogStorage::SaveFormattedTextLn(
				"Excel file path already exists and will not be generated again: %s",
				filePath
			);
	}

	/*
	// HTML file
	{
		sprintf(filePath, "%s\\documentation\\Documentation.html", FLA_release_directory);

		if (!FileExistsA(filePath))
			;// Configuration::Formats::WriteXMLexcelFile(&FLAworkbook, filePath);
		else
			CGenericLogStorage::SaveFormattedTextLn(
				"HTML file path already exists and will not be generated again: %s",
				filePath
			);
	}
	*/

	// CSV file
	{
		sprintf(filePath, "%s\\documentation\\Documentation.csv", FLA_release_directory);

		if (!FileExistsA(filePath))
			Configuration::Formats::WriteCSVfile(&FLAworkbook, filePath);
		else
			CGenericLogStorage::SaveFormattedTextLn(
				"CSV file path already exists and will not be generated again: %s",
				filePath
			);
	}

	// Deallocate all workbook data
	Workbook::ClearDocumentationWorkbook(&FLAworkbook);
#endif
}

// Android JNI functions
#if IS_PLATFORM_ANDROID
// Sets the path to external storage directory
static void GetExternalStorageDirectory(JNIEnv* env, char* strPath, size_t bufferSize)
{
	jclass classEnvironment = env->FindClass("android/os/Environment");
	jmethodID methodIDgetExternalStorageDirectory = env->GetStaticMethodID(classEnvironment, "getExternalStorageDirectory", "()Ljava/io/File;");
	jobject objectFile = env->CallStaticObjectMethod(classEnvironment, methodIDgetExternalStorageDirectory);
	
	jclass classFile = env->GetObjectClass(objectFile);
	jmethodID methodIDgetAbsolutePath = env->GetMethodID(classFile, "getAbsolutePath", "()Ljava/lang/String;");
	jstring stringPath = (jstring)env->CallObjectMethod(objectFile, methodIDgetAbsolutePath);
	
	if (stringPath)
	{
		const char* strPathValueStr = env->GetStringUTFChars(stringPath, NULL);

		strncpy(strPath, strPathValueStr, bufferSize);
		env->ReleaseStringUTFChars(stringPath, strPathValueStr);
	}
}
#endif

// Java: com.rockstargames.fastman92.limit_adjuster.Functions
static const unsigned char com_fastman92_limit_adjuster_Functions[] =

"\xCA\xFE\xBA\xBE\x00\x00\x00\x34\x00\x77\x0A\x00\x10\x00\x32\x07"
"\x00\x34\x0A\x00\x02\x00\x35\x0A\x00\x02\x00\x36\x0A\x00\x02\x00"
"\x37\x08\x00\x38\x12\x00\x00\x00\x3D\x0A\x00\x02\x00\x3E\x0A\x00"
"\x02\x00\x3F\x0A\x00\x33\x00\x40\x12\x00\x01\x00\x43\x0A\x00\x33"
"\x00\x44\x0A\x00\x33\x00\x45\x0A\x00\x46\x00\x47\x07\x00\x48\x07"
"\x00\x49\x01\x00\x06\x3C\x69\x6E\x69\x74\x3E\x01\x00\x03\x28\x29"
"\x56\x01\x00\x04\x43\x6F\x64\x65\x01\x00\x0F\x4C\x69\x6E\x65\x4E"
"\x75\x6D\x62\x65\x72\x54\x61\x62\x6C\x65\x01\x00\x12\x4C\x6F\x63"
"\x61\x6C\x56\x61\x72\x69\x61\x62\x6C\x65\x54\x61\x62\x6C\x65\x01"
"\x00\x04\x74\x68\x69\x73\x01\x00\x28\x4C\x63\x6F\x6D\x2F\x66\x61"
"\x73\x74\x6D\x61\x6E\x39\x32\x2F\x6C\x69\x6D\x69\x74\x5F\x61\x64"
"\x6A\x75\x73\x74\x65\x72\x2F\x46\x75\x6E\x63\x74\x69\x6F\x6E\x73"
"\x3B\x01\x00\x0A\x4D\x65\x73\x73\x61\x67\x65\x42\x6F\x78\x01\x00"
"\x3E\x28\x4C\x61\x6E\x64\x72\x6F\x69\x64\x2F\x61\x70\x70\x2F\x41"
"\x63\x74\x69\x76\x69\x74\x79\x3B\x4C\x6A\x61\x76\x61\x2F\x6C\x61"
"\x6E\x67\x2F\x53\x74\x72\x69\x6E\x67\x3B\x4C\x6A\x61\x76\x61\x2F"
"\x6C\x61\x6E\x67\x2F\x53\x74\x72\x69\x6E\x67\x3B\x5A\x29\x56\x01"
"\x00\x08\x61\x63\x74\x69\x76\x69\x74\x79\x01\x00\x16\x4C\x61\x6E"
"\x64\x72\x6F\x69\x64\x2F\x61\x70\x70\x2F\x41\x63\x74\x69\x76\x69"
"\x74\x79\x3B\x01\x00\x05\x74\x69\x74\x6C\x65\x01\x00\x12\x4C\x6A"
"\x61\x76\x61\x2F\x6C\x61\x6E\x67\x2F\x53\x74\x72\x69\x6E\x67\x3B"
"\x01\x00\x03\x6D\x73\x67\x01\x00\x0F\x62\x46\x69\x6E\x69\x73\x68"
"\x41\x63\x74\x69\x76\x69\x74\x79\x01\x00\x01\x5A\x01\x00\x07\x62"
"\x75\x69\x6C\x64\x65\x72\x01\x00\x07\x42\x75\x69\x6C\x64\x65\x72"
"\x01\x00\x0C\x49\x6E\x6E\x65\x72\x43\x6C\x61\x73\x73\x65\x73\x01"
"\x00\x21\x4C\x61\x6E\x64\x72\x6F\x69\x64\x2F\x61\x70\x70\x2F\x41"
"\x6C\x65\x72\x74\x44\x69\x61\x6C\x6F\x67\x24\x42\x75\x69\x6C\x64"
"\x65\x72\x3B\x01\x00\x0B\x61\x6C\x65\x72\x74\x44\x69\x61\x6C\x6F"
"\x67\x01\x00\x19\x4C\x61\x6E\x64\x72\x6F\x69\x64\x2F\x61\x70\x70"
"\x2F\x41\x6C\x65\x72\x74\x44\x69\x61\x6C\x6F\x67\x3B\x01\x00\x13"
"\x6C\x61\x6D\x62\x64\x61\x24\x4D\x65\x73\x73\x61\x67\x65\x42\x6F"
"\x78\x24\x31\x01\x00\x3B\x28\x5A\x4C\x61\x6E\x64\x72\x6F\x69\x64"
"\x2F\x61\x70\x70\x2F\x41\x63\x74\x69\x76\x69\x74\x79\x3B\x4C\x61"
"\x6E\x64\x72\x6F\x69\x64\x2F\x63\x6F\x6E\x74\x65\x6E\x74\x2F\x44"
"\x69\x61\x6C\x6F\x67\x49\x6E\x74\x65\x72\x66\x61\x63\x65\x3B\x29"
"\x56\x01\x00\x06\x64\x69\x61\x6C\x6F\x67\x01\x00\x21\x4C\x61\x6E"
"\x64\x72\x6F\x69\x64\x2F\x63\x6F\x6E\x74\x65\x6E\x74\x2F\x44\x69"
"\x61\x6C\x6F\x67\x49\x6E\x74\x65\x72\x66\x61\x63\x65\x3B\x01\x00"
"\x0D\x53\x74\x61\x63\x6B\x4D\x61\x70\x54\x61\x62\x6C\x65\x01\x00"
"\x13\x6C\x61\x6D\x62\x64\x61\x24\x4D\x65\x73\x73\x61\x67\x65\x42"
"\x6F\x78\x24\x30\x01\x00\x3C\x28\x5A\x4C\x61\x6E\x64\x72\x6F\x69"
"\x64\x2F\x61\x70\x70\x2F\x41\x63\x74\x69\x76\x69\x74\x79\x3B\x4C"
"\x61\x6E\x64\x72\x6F\x69\x64\x2F\x63\x6F\x6E\x74\x65\x6E\x74\x2F"
"\x44\x69\x61\x6C\x6F\x67\x49\x6E\x74\x65\x72\x66\x61\x63\x65\x3B"
"\x49\x29\x56\x01\x00\x05\x77\x68\x69\x63\x68\x01\x00\x01\x49\x01"
"\x00\x0A\x53\x6F\x75\x72\x63\x65\x46\x69\x6C\x65\x01\x00\x0E\x46"
"\x75\x6E\x63\x74\x69\x6F\x6E\x73\x2E\x6A\x61\x76\x61\x0C\x00\x11"
"\x00\x12\x07\x00\x4A\x01\x00\x1F\x61\x6E\x64\x72\x6F\x69\x64\x2F"
"\x61\x70\x70\x2F\x41\x6C\x65\x72\x74\x44\x69\x61\x6C\x6F\x67\x24"
"\x42\x75\x69\x6C\x64\x65\x72\x0C\x00\x11\x00\x4B\x0C\x00\x4C\x00"
"\x4D\x0C\x00\x4E\x00\x4D\x01\x00\x02\x4F\x4B\x01\x00\x10\x42\x6F"
"\x6F\x74\x73\x74\x72\x61\x70\x4D\x65\x74\x68\x6F\x64\x73\x0F\x06"
"\x00\x4F\x10\x00\x50\x0F\x06\x00\x51\x0C\x00\x52\x00\x55\x0C\x00"
"\x56\x00\x57\x0C\x00\x58\x00\x59\x0C\x00\x5A\x00\x5B\x10\x00\x5C"
"\x0F\x06\x00\x5D\x0C\x00\x5E\x00\x61\x0C\x00\x62\x00\x63\x0C\x00"
"\x64\x00\x12\x07\x00\x65\x0C\x00\x66\x00\x12\x01\x00\x26\x63\x6F"
"\x6D\x2F\x66\x61\x73\x74\x6D\x61\x6E\x39\x32\x2F\x6C\x69\x6D\x69"
"\x74\x5F\x61\x64\x6A\x75\x73\x74\x65\x72\x2F\x46\x75\x6E\x63\x74"
"\x69\x6F\x6E\x73\x01\x00\x10\x6A\x61\x76\x61\x2F\x6C\x61\x6E\x67"
"\x2F\x4F\x62\x6A\x65\x63\x74\x01\x00\x17\x61\x6E\x64\x72\x6F\x69"
"\x64\x2F\x61\x70\x70\x2F\x41\x6C\x65\x72\x74\x44\x69\x61\x6C\x6F"
"\x67\x01\x00\x1C\x28\x4C\x61\x6E\x64\x72\x6F\x69\x64\x2F\x63\x6F"
"\x6E\x74\x65\x6E\x74\x2F\x43\x6F\x6E\x74\x65\x78\x74\x3B\x29\x56"
"\x01\x00\x08\x73\x65\x74\x54\x69\x74\x6C\x65\x01\x00\x3B\x28\x4C"
"\x6A\x61\x76\x61\x2F\x6C\x61\x6E\x67\x2F\x43\x68\x61\x72\x53\x65"
"\x71\x75\x65\x6E\x63\x65\x3B\x29\x4C\x61\x6E\x64\x72\x6F\x69\x64"
"\x2F\x61\x70\x70\x2F\x41\x6C\x65\x72\x74\x44\x69\x61\x6C\x6F\x67"
"\x24\x42\x75\x69\x6C\x64\x65\x72\x3B\x01\x00\x0A\x73\x65\x74\x4D"
"\x65\x73\x73\x61\x67\x65\x0A\x00\x67\x00\x68\x01\x00\x25\x28\x4C"
"\x61\x6E\x64\x72\x6F\x69\x64\x2F\x63\x6F\x6E\x74\x65\x6E\x74\x2F"
"\x44\x69\x61\x6C\x6F\x67\x49\x6E\x74\x65\x72\x66\x61\x63\x65\x3B"
"\x49\x29\x56\x0A\x00\x0F\x00\x69\x01\x00\x07\x6F\x6E\x43\x6C\x69"
"\x63\x6B\x07\x00\x6B\x01\x00\x0F\x4F\x6E\x43\x6C\x69\x63\x6B\x4C"
"\x69\x73\x74\x65\x6E\x65\x72\x01\x00\x4A\x28\x5A\x4C\x61\x6E\x64"
"\x72\x6F\x69\x64\x2F\x61\x70\x70\x2F\x41\x63\x74\x69\x76\x69\x74"
"\x79\x3B\x29\x4C\x61\x6E\x64\x72\x6F\x69\x64\x2F\x63\x6F\x6E\x74"
"\x65\x6E\x74\x2F\x44\x69\x61\x6C\x6F\x67\x49\x6E\x74\x65\x72\x66"
"\x61\x63\x65\x24\x4F\x6E\x43\x6C\x69\x63\x6B\x4C\x69\x73\x74\x65"
"\x6E\x65\x72\x3B\x01\x00\x10\x73\x65\x74\x4E\x65\x75\x74\x72\x61"
"\x6C\x42\x75\x74\x74\x6F\x6E\x01\x00\x6C\x28\x4C\x6A\x61\x76\x61"
"\x2F\x6C\x61\x6E\x67\x2F\x43\x68\x61\x72\x53\x65\x71\x75\x65\x6E"
"\x63\x65\x3B\x4C\x61\x6E\x64\x72\x6F\x69\x64\x2F\x63\x6F\x6E\x74"
"\x65\x6E\x74\x2F\x44\x69\x61\x6C\x6F\x67\x49\x6E\x74\x65\x72\x66"
"\x61\x63\x65\x24\x4F\x6E\x43\x6C\x69\x63\x6B\x4C\x69\x73\x74\x65"
"\x6E\x65\x72\x3B\x29\x4C\x61\x6E\x64\x72\x6F\x69\x64\x2F\x61\x70"
"\x70\x2F\x41\x6C\x65\x72\x74\x44\x69\x61\x6C\x6F\x67\x24\x42\x75"
"\x69\x6C\x64\x65\x72\x3B\x01\x00\x06\x63\x72\x65\x61\x74\x65\x01"
"\x00\x1B\x28\x29\x4C\x61\x6E\x64\x72\x6F\x69\x64\x2F\x61\x70\x70"
"\x2F\x41\x6C\x65\x72\x74\x44\x69\x61\x6C\x6F\x67\x3B\x01\x00\x19"
"\x73\x65\x74\x43\x61\x6E\x63\x65\x6C\x65\x64\x4F\x6E\x54\x6F\x75"
"\x63\x68\x4F\x75\x74\x73\x69\x64\x65\x01\x00\x04\x28\x5A\x29\x56"
"\x01\x00\x24\x28\x4C\x61\x6E\x64\x72\x6F\x69\x64\x2F\x63\x6F\x6E"
"\x74\x65\x6E\x74\x2F\x44\x69\x61\x6C\x6F\x67\x49\x6E\x74\x65\x72"
"\x66\x61\x63\x65\x3B\x29\x56\x0A\x00\x0F\x00\x6C\x01\x00\x08\x6F"
"\x6E\x43\x61\x6E\x63\x65\x6C\x07\x00\x6D\x01\x00\x10\x4F\x6E\x43"
"\x61\x6E\x63\x65\x6C\x4C\x69\x73\x74\x65\x6E\x65\x72\x01\x00\x4B"
"\x28\x5A\x4C\x61\x6E\x64\x72\x6F\x69\x64\x2F\x61\x70\x70\x2F\x41"
"\x63\x74\x69\x76\x69\x74\x79\x3B\x29\x4C\x61\x6E\x64\x72\x6F\x69"
"\x64\x2F\x63\x6F\x6E\x74\x65\x6E\x74\x2F\x44\x69\x61\x6C\x6F\x67"
"\x49\x6E\x74\x65\x72\x66\x61\x63\x65\x24\x4F\x6E\x43\x61\x6E\x63"
"\x65\x6C\x4C\x69\x73\x74\x65\x6E\x65\x72\x3B\x01\x00\x13\x73\x65"
"\x74\x4F\x6E\x43\x61\x6E\x63\x65\x6C\x4C\x69\x73\x74\x65\x6E\x65"
"\x72\x01\x00\x35\x28\x4C\x61\x6E\x64\x72\x6F\x69\x64\x2F\x63\x6F"
"\x6E\x74\x65\x6E\x74\x2F\x44\x69\x61\x6C\x6F\x67\x49\x6E\x74\x65"
"\x72\x66\x61\x63\x65\x24\x4F\x6E\x43\x61\x6E\x63\x65\x6C\x4C\x69"
"\x73\x74\x65\x6E\x65\x72\x3B\x29\x56\x01\x00\x04\x73\x68\x6F\x77"
"\x01\x00\x14\x61\x6E\x64\x72\x6F\x69\x64\x2F\x61\x70\x70\x2F\x41"
"\x63\x74\x69\x76\x69\x74\x79\x01\x00\x06\x66\x69\x6E\x69\x73\x68"
"\x07\x00\x6E\x0C\x00\x6F\x00\x72\x0C\x00\x2C\x00\x2D\x07\x00\x73"
"\x01\x00\x2F\x61\x6E\x64\x72\x6F\x69\x64\x2F\x63\x6F\x6E\x74\x65"
"\x6E\x74\x2F\x44\x69\x61\x6C\x6F\x67\x49\x6E\x74\x65\x72\x66\x61"
"\x63\x65\x24\x4F\x6E\x43\x6C\x69\x63\x6B\x4C\x69\x73\x74\x65\x6E"
"\x65\x72\x0C\x00\x27\x00\x28\x01\x00\x30\x61\x6E\x64\x72\x6F\x69"
"\x64\x2F\x63\x6F\x6E\x74\x65\x6E\x74\x2F\x44\x69\x61\x6C\x6F\x67"
"\x49\x6E\x74\x65\x72\x66\x61\x63\x65\x24\x4F\x6E\x43\x61\x6E\x63"
"\x65\x6C\x4C\x69\x73\x74\x65\x6E\x65\x72\x01\x00\x22\x6A\x61\x76"
"\x61\x2F\x6C\x61\x6E\x67\x2F\x69\x6E\x76\x6F\x6B\x65\x2F\x4C\x61"
"\x6D\x62\x64\x61\x4D\x65\x74\x61\x66\x61\x63\x74\x6F\x72\x79\x01"
"\x00\x0B\x6D\x65\x74\x61\x66\x61\x63\x74\x6F\x72\x79\x07\x00\x75"
"\x01\x00\x06\x4C\x6F\x6F\x6B\x75\x70\x01\x00\xCC\x28\x4C\x6A\x61"
"\x76\x61\x2F\x6C\x61\x6E\x67\x2F\x69\x6E\x76\x6F\x6B\x65\x2F\x4D"
"\x65\x74\x68\x6F\x64\x48\x61\x6E\x64\x6C\x65\x73\x24\x4C\x6F\x6F"
"\x6B\x75\x70\x3B\x4C\x6A\x61\x76\x61\x2F\x6C\x61\x6E\x67\x2F\x53"
"\x74\x72\x69\x6E\x67\x3B\x4C\x6A\x61\x76\x61\x2F\x6C\x61\x6E\x67"
"\x2F\x69\x6E\x76\x6F\x6B\x65\x2F\x4D\x65\x74\x68\x6F\x64\x54\x79"
"\x70\x65\x3B\x4C\x6A\x61\x76\x61\x2F\x6C\x61\x6E\x67\x2F\x69\x6E"
"\x76\x6F\x6B\x65\x2F\x4D\x65\x74\x68\x6F\x64\x54\x79\x70\x65\x3B"
"\x4C\x6A\x61\x76\x61\x2F\x6C\x61\x6E\x67\x2F\x69\x6E\x76\x6F\x6B"
"\x65\x2F\x4D\x65\x74\x68\x6F\x64\x48\x61\x6E\x64\x6C\x65\x3B\x4C"
"\x6A\x61\x76\x61\x2F\x6C\x61\x6E\x67\x2F\x69\x6E\x76\x6F\x6B\x65"
"\x2F\x4D\x65\x74\x68\x6F\x64\x54\x79\x70\x65\x3B\x29\x4C\x6A\x61"
"\x76\x61\x2F\x6C\x61\x6E\x67\x2F\x69\x6E\x76\x6F\x6B\x65\x2F\x43"
"\x61\x6C\x6C\x53\x69\x74\x65\x3B\x01\x00\x1F\x61\x6E\x64\x72\x6F"
"\x69\x64\x2F\x63\x6F\x6E\x74\x65\x6E\x74\x2F\x44\x69\x61\x6C\x6F"
"\x67\x49\x6E\x74\x65\x72\x66\x61\x63\x65\x07\x00\x76\x01\x00\x25"
"\x6A\x61\x76\x61\x2F\x6C\x61\x6E\x67\x2F\x69\x6E\x76\x6F\x6B\x65"
"\x2F\x4D\x65\x74\x68\x6F\x64\x48\x61\x6E\x64\x6C\x65\x73\x24\x4C"
"\x6F\x6F\x6B\x75\x70\x01\x00\x1E\x6A\x61\x76\x61\x2F\x6C\x61\x6E"
"\x67\x2F\x69\x6E\x76\x6F\x6B\x65\x2F\x4D\x65\x74\x68\x6F\x64\x48"
"\x61\x6E\x64\x6C\x65\x73\x00\x21\x00\x0F\x00\x10\x00\x00\x00\x00"
"\x00\x04\x00\x01\x00\x11\x00\x12\x00\x01\x00\x13\x00\x00\x00\x2F"
"\x00\x01\x00\x01\x00\x00\x00\x05\x2A\xB7\x00\x01\xB1\x00\x00\x00"
"\x02\x00\x14\x00\x00\x00\x06\x00\x01\x00\x00\x00\x06\x00\x15\x00"
"\x00\x00\x0C\x00\x01\x00\x00\x00\x05\x00\x16\x00\x17\x00\x00\x00"
"\x09\x00\x18\x00\x19\x00\x01\x00\x13\x00\x00\x00\xC2\x00\x04\x00"
"\x06\x00\x00\x00\x46\xBB\x00\x02\x59\x2A\xB7\x00\x03\x3A\x04\x19"
"\x04\x2B\xB6\x00\x04\x57\x19\x04\x2C\xB6\x00\x05\x57\x19\x04\x12"
"\x06\x1D\x2A\xBA\x00\x07\x00\x00\xB6\x00\x08\x57\x19\x04\xB6\x00"
"\x09\x3A\x05\x19\x05\x04\xB6\x00\x0A\x19\x05\x1D\x2A\xBA\x00\x0B"
"\x00\x00\xB6\x00\x0C\x19\x05\xB6\x00\x0D\xB1\x00\x00\x00\x02\x00"
"\x14\x00\x00\x00\x26\x00\x09\x00\x00\x00\x09\x00\x0A\x00\x0B\x00"
"\x11\x00\x0D\x00\x18\x00\x0F\x00\x27\x00\x15\x00\x2E\x00\x17\x00"
"\x34\x00\x19\x00\x40\x00\x1E\x00\x45\x00\x1F\x00\x15\x00\x00\x00"
"\x3E\x00\x06\x00\x00\x00\x46\x00\x1A\x00\x1B\x00\x00\x00\x00\x00"
"\x46\x00\x1C\x00\x1D\x00\x01\x00\x00\x00\x46\x00\x1E\x00\x1D\x00"
"\x02\x00\x00\x00\x46\x00\x1F\x00\x20\x00\x03\x00\x0A\x00\x3C\x00"
"\x21\x00\x24\x00\x04\x00\x2E\x00\x18\x00\x25\x00\x26\x00\x05\x10"
"\x0A\x00\x27\x00\x28\x00\x01\x00\x13\x00\x00\x00\x58\x00\x01\x00"
"\x03\x00\x00\x00\x09\x1A\x99\x00\x07\x2B\xB6\x00\x0E\xB1\x00\x00"
"\x00\x03\x00\x14\x00\x00\x00\x0E\x00\x03\x00\x00\x00\x1A\x00\x04"
"\x00\x1B\x00\x08\x00\x1C\x00\x15\x00\x00\x00\x20\x00\x03\x00\x00"
"\x00\x09\x00\x1F\x00\x20\x00\x00\x00\x00\x00\x09\x00\x1A\x00\x1B"
"\x00\x01\x00\x00\x00\x09\x00\x29\x00\x2A\x00\x02\x00\x2B\x00\x00"
"\x00\x03\x00\x01\x08\x10\x0A\x00\x2C\x00\x2D\x00\x01\x00\x13\x00"
"\x00\x00\x62\x00\x01\x00\x04\x00\x00\x00\x09\x1A\x99\x00\x07\x2B"
"\xB6\x00\x0E\xB1\x00\x00\x00\x03\x00\x14\x00\x00\x00\x0E\x00\x03"
"\x00\x00\x00\x10\x00\x04\x00\x11\x00\x08\x00\x12\x00\x15\x00\x00"
"\x00\x2A\x00\x04\x00\x00\x00\x09\x00\x1F\x00\x20\x00\x00\x00\x00"
"\x00\x09\x00\x1A\x00\x1B\x00\x01\x00\x00\x00\x09\x00\x29\x00\x2A"
"\x00\x02\x00\x00\x00\x09\x00\x2E\x00\x2F\x00\x03\x00\x2B\x00\x00"
"\x00\x03\x00\x01\x08\x00\x03\x00\x30\x00\x00\x00\x02\x00\x31\x00"
"\x23\x00\x00\x00\x22\x00\x04\x00\x02\x00\x33\x00\x22\x00\x09\x00"
"\x53\x00\x6A\x00\x54\x06\x09\x00\x5F\x00\x6A\x00\x60\x06\x09\x00"
"\x70\x00\x74\x00\x71\x00\x19\x00\x39\x00\x00\x00\x16\x00\x02\x00"
"\x3A\x00\x03\x00\x3B\x00\x3C\x00\x3B\x00\x3A\x00\x03\x00\x41\x00"
"\x42\x00\x41";

// Loads additional java code
void CLimitAdjuster::LoadAdditionalJavaCode()
{
	// DefineClass is not supported on Android
	return;

	#if IS_PLATFORM_ANDROID
	auto class_loader = jniEnv->FindClass("java/lang/ClassLoader");

	auto get_system_loader =
		jniEnv->GetStaticMethodID(class_loader, "getSystemClassLoader",
			"()Ljava/lang/ClassLoader;");


	auto system_loader =
		jniEnv->CallStaticObjectMethod(class_loader, get_system_loader);


	jclass Functions = jniEnv->DefineClass("com/fastman92/limit_adjuster/Functions", system_loader, (const jbyte*)com_fastman92_limit_adjuster_Functions, sizeof(com_fastman92_limit_adjuster_Functions));	
	#endif

	/*
	#if IS_PLATFORM_ANDROID
	char DexCachePath[PATH_MAX];

	sprintf(DexCachePath, "%s/DEX", this->CacheDirectory);

	struct stat st;
	if (stat(DexCachePath, &st) != 0 || !(st.st_mode & S_IFDIR))
		if (!mkdir(DexCachePath, 0771))
			return;

	jstring DexCachePathJString = jniEnv->NewStringUTF(DexCachePath);
	jstring PathToAPKfileJString = jniEnv->NewStringUTF("/sdcard/fla.apk");

	jclass DexClassLoaderClassID = jniEnv->FindClass("dalvik/system/DexClassLoader");

	jclass activity_type = jniEnv->GetObjectClass(this->mainActivityDuringLaunch);

	jmethodID getClassLoader_methodID = jniEnv->GetMethodID(activity_type, "getClassLoader", "()Ljava/lang/ClassLoader;");
	jobject ClassLoader = jniEnv->CallObjectMethod(this->mainActivityDuringLaunch, getClassLoader_methodID);

	jmethodID DexClassLoader_constructor = jniEnv->GetMethodID(DexClassLoaderClassID, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/ClassLoader;)V");
	jobject DexClassLoader = jniEnv->NewObject(
		DexClassLoaderClassID, DexClassLoader_constructor,
		DexCachePathJString,
		DexCachePathJString,
		NULL,
		ClassLoader
	);

	jniEnv->DeleteLocalRef(DexCachePathJString);
	jniEnv->DeleteLocalRef(PathToAPKfileJString);

	/////////

	jmethodID DexClassLoader_LoadClassMethodID = jniEnv->GetMethodID(DexClassLoaderClassID, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

	jstring MessageBoxJString = jniEnv->NewStringUTF("com.fastman92.limitadjuster.MessageBox");
	jobject MessageBox = jniEnv->CallObjectMethod(DexClassLoader, DexClassLoader_LoadClassMethodID, MessageBoxJString);
		
	printf_MessageBox("Works far: %d", MessageBox);
	#endif
	*/
}

// Runs the code with exception handling
void RunCodeWithExceptionHandling();

// Processes limits
void CLimitAdjuster::Process()
{
	eGameVersion gameVersion = this->GetGameVersion();

	// Set informations about directories
	#ifdef IS_PLATFORM_WIN
	GetCurrentDirectoryA(sizeof(this->InitialDirectory), this->InitialDirectory);

	const char* relativePath = NULL;

	if(CGameVersion::IsAny_GTA_III_UnrealEngine(gameVersion))
		relativePath = "\\../../../Content\\OriginalData\\GTA3";
	else if(CGameVersion::IsAny_GTA_VC_UnrealEngine(gameVersion))
		relativePath = "\\../../../Content\\OriginalData\\ViceCity";
	else if (CGameVersion::IsAny_GTA_SA_UnrealEngine(gameVersion))
		relativePath = "\\../../../Content\\OriginalData\\GTASA";

	if (relativePath)
	{
		char tmpPath[FLA_MAX_PATH];

		strncpy(tmpPath, this->InitialDirectory, _countof(tmpPath));

		strncat(tmpPath, relativePath, _countof(tmpPath));

		GetFullPathNameA(tmpPath, _countof(this->StorageRootDirectory), this->StorageRootDirectory, NULL);
		
		// Set directory for the FLA
		if (!SetCurrentWorkingDirectory_OS_independent(this->StorageRootDirectory))
		{
			mkdir_p(this->StorageRootDirectory);

			if (!SetCurrentWorkingDirectory_OS_independent(this->StorageRootDirectory))
				throw f92_runtime_error("Unable to set working directory to %s", this->StorageRootDirectory);
		}
	}
	else
		strncpy(this->StorageRootDirectory, this->InitialDirectory, _countof(this->StorageRootDirectory));
	
	#elif defined IS_PLATFORM_ANDROID
	// Load additional Java code
	this->LoadAdditionalJavaCode();

	// Get main activity during launch
	this->mainActivityDuringLaunch = GetMainActivityDuringLaunch();

	// Get package name
	strncpy(this->PackageName, GetApplicationPackageName(), sizeof(this->PackageName));
	strncpy(this->OriginalPackageName, GetApplicationOriginalPackageName(), sizeof(this->OriginalPackageName));
	
	// Get directory paths
	strncpy(this->StorageRootBase, GetStorageRootBaseDirectoryPath(), sizeof(this->StorageRootBase));
	strncpy(this->StorageRootDirectory, GetStorageRootDirectoryPath(), sizeof(this->StorageRootDirectory));
	strncpy(this->InitialDirectory, GetInitialDirectoryPath(), sizeof(this->InitialDirectory));
	strncpy(this->CacheDirectory, GetCacheDirectoryPath(), sizeof(this->CacheDirectory));

	OutputFormattedDebugString("Package name: %s", g_LimitAdjuster.PackageName);
	OutputFormattedDebugString("Original package name: %s", g_LimitAdjuster.OriginalPackageName);

	// Set directory for the FLA
	SetCurrentWorkingDirectory_OS_independent(this->StorageRootDirectory);
	#endif

	// Open log file
	if(!CGenericLogStorage::IsFileOpen())
		CGenericLogStorage::OpenFileForTextWriting(LIMIT_ADJUSTER_LOG_FILENAME);

	#ifdef IS_PLATFORM_ANDROID
	CGenericLogStorage::SaveFormattedTextLn("Package name: %s", this->PackageName);
	#endif

	CGenericLogStorage::SaveFormattedTextLn(
		"Root base directory: %s\nRoot directory: %s\nInitial directory: %s",
		this->StorageRootBase,
		this->StorageRootDirectory,
		this->InitialDirectory
	);

	#ifdef IS_PLATFORM_ANDROID
	CGenericLogStorage::SaveFormattedTextLn(
		"Cache directory: %s",
		this->CacheDirectory
	);
	#endif

	const char* iniFilename = this->GetIniFilenameForGame(gameVersion);

	CGenericLogStorage::SaveFormattedTextLn("INI filename: %s", iniFilename);
	CGenericLogStorage::WriteNewLine();

	this->OpenIniFile(this->GetPathToFlaFileFromRootDirectory(iniFilename).c_str());

	// Set exception handler.
	if (
		INIreader.GetBool("MAIN", "Register global expection handler")	// there was a typo in versions before FLA 5.7
		|| INIreader.GetBool("MAIN", "Register global exception handler")
		)
	{
		GlobalExceptionHandler::DisableMusicPlaying(INIreader.GetBool("MAIN", "Disable music on global exception handler"));

		GlobalExceptionHandler::RegisterUnhandledExceptionHandler();
	}

#if 1
	/////////////////////

	// Online content
	#ifdef SYSTEM_PROPERLY_IMPLEMENTED
	{
		bool bEnable = !INIreader.GetBool("MAIN", "Disable online content", false)
			&& INIreader.GetBool("MAIN", "Enable online content", false);

		g_OnlineContent.EnableOnlineContent(bEnable);

		g_OnlineContent.Run();
	}
	#endif

	CGenericLogStorage::WriteLineSeparator();

	//////////////////////
	#if PROJECT_USE_DEVELOPMENT_INI
	// return g_executableCode.TryItOut();
	#endif

	/////////////////////
	if (INIreader.GetBool("MAIN", "Enable windowed mode"))
		g_windowedMode.ApplyWindowedMode();

	g_fileIDlimits.EnableIDlimitsPatch(INIreader.GetBool("ID LIMITS", "Apply ID limit patch", false));
	/////////////	

	// Map limits
	{
		g_mapLimits.InitChanges();

		if(true)
		{
			g_mapLimits.EnablePathsLimitPatch(INIreader.GetBool("MAP LIMITS", "Apply paths limit patch"));
			g_mapLimits.EnablePathDebugging(INIreader.GetBool("MAP LIMITS", "Enable path debugging"));
			
			if (INIreader.GetIntEx("MAP LIMITS", "Paths map size", &nTmp))
				g_mapLimits.SetPathsMapSize(nTmp);
		}
	}
	
	/////// ID LIMITS //////

	if(INIreader.GetBool("ADDONS", "Enable model special feature loader"))
		g_modelSpecialFeatures.EnableSpecialFeatures(true);

	this->ProcessIDlimits();
	
	// Car generators
	#if TRUE
	{
		int numberOfCarGenerators;

		bool isCarGeneratorLimitSetFromIni =
			INIreader.GetIntEx("CAR STREAMING", "Car generators", &numberOfCarGenerators, 500);		

		// extended format?
		bool isExtendedFormat = g_carGeneratorLimits.IsFormatExtendedNeccessary();

		if(!isExtendedFormat)
			isExtendedFormat = INIreader.GetBool("CAR STREAMING", "Use extended format for car generators");			

		// patch the limit
		if (isCarGeneratorLimitSetFromIni || isExtendedFormat)
			g_carGeneratorLimits.PatchCarGeneratorsLimit(numberOfCarGenerators, isExtendedFormat);

		// counter passes
		if (INIreader.GetIntEx("CAR STREAMING", "Number of process counter passes for car generators", &nTmp))
			g_carGeneratorLimits.PatchNumberOfProcessCounterPasses(nTmp);

		// Accept any ID for car generator
		if (INIreader.GetBool("CAR STREAMING", "Accept any ID for car generator"))
			g_carGeneratorLimits.AcceptAnyIDforCarGenerator();
	}
	#endif	

	///////////////////////////////////////////////////	

	////// save game loading functions //////

	// Patches a loading function, the savefile of any length may be considered as valid savefile.

	// IPL and model flags from savefile.
	g_fileIDlimits.PatchSaveBlockLoadingFunctions();

	// Car generators
	g_carGeneratorLimits.PatchCarGeneratorSaveBlockLoadingFunction();

	// IPL limits
	g_IPLsectionlimits.PatchSaveBlockLoadingFunctions();

	// Other limits
	g_otherLimits.PatchSaveBlockLoadingFunctions();

	// Save game of unlimited length		
	g_SaveOfVariableLength.PatchLoadingFunction();
	
	//////                             //////

	// Map limits
	#if TRUE
	{
		if (INIreader.GetBoolEx("MAP LIMITS", "Apply tracks.dat coordinate limit patch", &bTmp))
			g_mapLimits.EnableTracksDatCoordinateLimitPatch(bTmp);

		if (INIreader.GetIntEx("MAP LIMITS", "Tracks.dat file size limit", &nTmp))
			g_mapLimits.SetTracksDatFileSizeLimit(nTmp);

		if (INIreader.GetIntEx("MAP LIMITS", "Max number of track stations", &nTmp))
			g_mapLimits.SetMaxNumberOfTrackStations(nTmp);

		if (INIreader.GetBoolEx("MAP LIMITS", "Enable track config loader", &bTmp))
			g_mapLimits.EnableTrackConfigLoader(bTmp);
		
		if (INIreader.GetIntEx("MAP LIMITS", "Renderware world map size", &nTmp))
			g_mapLimits.SetRenderwareWorldMapSize(nTmp);

		if (INIreader.GetIntEx("MAP LIMITS", "Radar map size", &nTmp))
			g_mapLimits.SetRadarSize(nTmp);

		if (INIreader.GetBoolEx("MAP LIMITS", "Enable frontend map different", &bTmp))
			g_mapLimits.EnableFrontendMapDifferent(bTmp);

		if (INIreader.GetIntEx("MAP LIMITS", "Water map size", &nTmp))
			g_mapLimits.SetWaterMapSize(nTmp);

		if (INIreader.GetIntEx("MAP LIMITS", "World map size", &nTmp))
			g_mapLimits.SetWorldMapSize(nTmp);

		if (INIreader.GetIntEx("MAP LIMITS", "World sector size", &nTmp))
			g_mapLimits.SetWorldSectorSize(nTmp);

		if (INIreader.GetIntEx("MAP LIMITS", "World LOD sector size", &nTmp))
			g_mapLimits.SetLODSectorSize(nTmp);

		g_mapLimits.CommitChanges();
	}
	#endif

	// handling.cfg limits
	this->ProcessHandlingLimits();
	

	// DYNAMIC LIMITS
	this->ProcessDynamicLimits();	

	//////////////////////
	
	this->ProcessIPLlimits();
	this->ProcessIDElimits();
	
	//// IMG limits ////
	#if TRUE
	{			

		// Allow handling of new enhanced IMG archives
		if (INIreader.GetBool("IMG LIMITS", "Enable handling of new enhanced IMG archives"))
			g_IMGlimits.AllowHandlingOfNewEnhancedImgArchives();

		// Increase the IMG archive size limit
		if (INIreader.GetBool("IMG LIMITS", "Increase the IMG archive size limit"))
			g_IMGlimits.IncreaseTheIMGsizeLimit();

		if (INIreader.GetIntEx("IMG LIMITS", "Max number of IMG archives", &nTmp))
			g_IMGlimits.SetLimitOfIMGarchives(nTmp);

		if (INIreader.GetBool("IMG LIMITS", "Enable handling of IMGLIST keyword"))
			g_IMGlimits.EnableIMGlistKeyword();
	}
	#endif

	// DIRECTORY LIMITS
	#if TRUE
	{
		if (INIreader.GetIntEx("DIRECTORY LIMITS", "Extra objects directory", &nTmp))
			g_directoryLimits.SetExtraObjects(nTmp);
		
		if (INIreader.GetIntEx("DIRECTORY LIMITS", "Cutscene directory", &nTmp))
			g_directoryLimits.SetCutsceneDirLimit(nTmp);

		if (INIreader.GetIntEx("DIRECTORY LIMITS", "Clothes directory", &nTmp))
			g_directoryLimits.SetClothesDirLimit(nTmp);		

		g_directoryLimits.ApplyEnabledLimits();
	}
	#endif

	// [WATER LIMITS]
	#if TRUE
	{
		if (INIreader.GetIntEx("WATER LIMITS", "Water triangles", &nTmp))
			g_waterLimits.SetWaterTriangles(nTmp);

		if (INIreader.GetIntEx("WATER LIMITS", "Water quads", &nTmp))
			g_waterLimits.SetWaterQuads(nTmp);

		if (INIreader.GetIntEx("WATER LIMITS", "Water quads and triangles list", &nTmp))
			g_waterLimits.SetQuadsAndTrianglesList(nTmp);

		if (INIreader.GetIntEx("WATER LIMITS", "Water vertices", &nTmp))
			g_waterLimits.SetWaterVertices(nTmp);

		if (INIreader.GetIntEx("WATER LIMITS", "Blocks to be rendered outside world", &nTmp))
			g_waterLimits.SetBlocksToBeRenderedOutsideWorld(nTmp);
	}
	#endif	

	// Car streaming
	#if TRUE
	{
		// Cargrp cars per group
		if (INIreader.GetIntEx("CAR STREAMING", "Cargrp cars per group", &nTmp))
			g_cargrpLimits.SetCargrpLimit(34, nTmp);

		// Car streaming : DesiredNumberOfVehiclesLoaded
		if (INIreader.GetIntEx("CAR STREAMING", "Streaming_DesiredNumberOfVehiclesLoaded", &nTmp))
			g_streamingLimits.SetStreamingDesiredNumberOfVehiclesLoaded(nTmp);		
	}
	#endif

	// Ped streaming
	#if TRUE
	{
		// Peds ped group
		if (INIreader.GetIntEx("PED STREAMING", "Pedgrp peds per group", &nTmp))
			g_pedGrpLimits.SetPedsPerGroupLimit(nTmp);
	}
	#endif

	// STREAMING
	#if TRUE
	{
		// Memory available
		if (INIreader.GetIntEx("STREAMING", "Memory available", &nTmp))
			g_streamingLimits.SetMemoryAvailable(nTmp * 1024 * 1024);

		// Max number of stream handles
		if (INIreader.GetIntEx("STREAMING", "Max number of stream handles", &nTmp))
			g_streamingLimits.SetMaxNumberOfStreamHandles(nTmp);

		// Number of requested models above which the game considers loading very busy
		if (INIreader.GetIntEx("STREAMING", "Number of requested models above which the game considers loading very busy", &nTmp))
			g_streamingLimits.SetTheNumberOfRequestedModelsAboveWhichLoadingIsVeryBusy(nTmp);

		// Minimum number of iterations in LoadAllRequestedModels
		if (INIreader.GetIntEx("STREAMING", "Minimum number of iterations in LoadAllRequestedModels", &nTmp))
			g_streamingLimits.SetMinimumNumberOfIterationsInLoadAllRequestedModels(nTmp);
	}
	#endif	

	// SCM limits
	#if TRUE
	{
		if (INIreader.GetIntEx("SCM LIMITS", "Max size of MAIN segment", &nTmp))
			g_SCMlimits.SetMaxMAINsegmentSize(nTmp);

		if (INIreader.GetIntEx("SCM LIMITS", "Max mission size", &nTmp))
			g_SCMlimits.SetMaxMissionSize(nTmp);

		if (INIreader.GetIntEx("SCM LIMITS", "Running scripts", &nTmp))
			g_SCMlimits.SetScriptsArrayLimit(nTmp);

		if (INIreader.GetIntEx("SCM LIMITS", "Mission cleanup", &nTmp))
			g_SCMlimits.SetMissionCleanUpLimit(nTmp);

		if (INIreader.GetIntEx("SCM LIMITS", "Max number of used objects", &nTmp))
			g_SCMlimits.SetUsedObjectArrayLimit(nTmp);

		if (INIreader.GetIntEx("SCM LIMITS", "Switch jump table cases", &nTmp))
			g_SCMlimits.SetSwitchJumpTableLimit(nTmp);	
		
		if (INIreader.GetIntEx("SCM LIMITS", "Scripts for brains", &nTmp))
			g_SCMlimits.SetScriptsForBrainsLimit(nTmp);

		g_SCMlimits.PatchSCMlimits();	
	}
	#endif

	// RENDERER
	#if TRUE
	{
		if (INIreader.GetIntEx("RENDERER LIMITS", "Invisible entity pointers", &nTmp))
			g_rendererLimits.SetInvisibleEntityPtrs(nTmp);

		if (INIreader.GetIntEx("RENDERER LIMITS", "Visible super LOD pointers", &nTmp))
			g_rendererLimits.SetVisibleSuperLodPtrs(nTmp);		

		if (INIreader.GetIntEx("RENDERER LIMITS", "Visible LOD pointers", &nTmp))
			g_rendererLimits.SetVisibleLodPtrs(nTmp);		
	
		if (INIreader.GetIntEx("RENDERER LIMITS", "Visible entity pointers", &nTmp))
			g_rendererLimits.SetVisibleEntityPtrs(nTmp);		
	}
	#endif	

	// VISIBILITY
	#if TRUE
	{
		if (INIreader.GetIntEx("VISIBILITY LIMITS", "Alpha list limit", &nTmp))
			g_visibilityLimits.SetAlphaListLimit(nTmp);

		///////
		if (INIreader.GetIntEx("VISIBILITY LIMITS", "Alpha boat atomic list limit", &nTmp))
			g_visibilityLimits.SetAlphaBoatAtomicListLimit(nTmp);

		///////
		if (INIreader.GetIntEx("VISIBILITY LIMITS", "Alpha entity list limit", &nTmp))
			g_visibilityLimits.SetAlphaEntityListLimit(nTmp);

		///////
		if (INIreader.GetIntEx("VISIBILITY LIMITS", "Alpha underwater entity list limit", &nTmp))
			g_visibilityLimits.SetAlphaUnderwaterEntityListLimit(nTmp);

		///////
		if (INIreader.GetIntEx("VISIBILITY LIMITS", "Alpha really draw last list limit", &nTmp))
			g_visibilityLimits.SetAlphaReallyDrawLastListLimit(nTmp);

		if (INIreader.GetIntEx("VISIBILITY LIMITS", "Weapon peds for PC limit", &nTmp))
			g_visibilityLimits.SetWeaponPedsForPCLimit(nTmp);
	}
	#endif

	// OTHER LIMITS
	#if TRUE
	{
		if (INIreader.GetIntEx("OTHER LIMITS", "Collision size", &nTmp))
			g_otherLimits.SetMaxSizeOfSingleCollision(nTmp);

		if (INIreader.GetIntEx("OTHER LIMITS", "References", &nTmp))
			g_otherLimits.SetReferences(nTmp);

		if (INIreader.GetIntEx("OTHER LIMITS", "Cover points", &nTmp))
			g_otherLimits.SetCoverPoints(nTmp);

		if (INIreader.GetIntEx("OTHER LIMITS", "Coronas", &nTmp))
			g_otherLimits.SetCoronaLimit(nTmp);

		if (INIreader.GetIntEx("OTHER LIMITS", "Object info entries", &nTmp))
			g_otherLimits.SetObjectInfoEntries(nTmp);

		if (INIreader.GetIntEx("OTHER LIMITS", "Vehicle colors", &nTmp))
			g_otherLimits.SetVehicleColors(nTmp);	

		if (INIreader.GetDoubleEx("OTHER LIMITS", "LOD distance", &dTmp))
			g_otherLimits.SetLODdistanceLimit((float)dTmp);

		if (INIreader.GetIntEx("OTHER LIMITS", "Radar traces", &nTmp))
			g_otherLimits.SetRadarTracesLimit(nTmp);

		if (INIreader.GetIntEx("OTHER LIMITS", "Number of plate textures", &nTmp))
			g_otherLimits.SetNumberOfPlateTextures(nTmp);

		if (INIreader.GetIntEx("OTHER LIMITS", "Max number of particles active", &nTmp))
			g_otherLimits.SetMaxNumberOfParticlesActive(nTmp);

		// Set pieces
		{
			bool bCoordinateLimitHack = INIreader.GetBool(
				"OTHER LIMITS",
				"Set pieces, apply coordinate limit patch"
			);

			bool bSetPiecesLimitSet = INIreader.GetIntEx(
				"OTHER LIMITS",
				"Set pieces",
				&nTmp
			);

			if(bCoordinateLimitHack || bSetPiecesLimitSet)
				g_otherLimits.SetMaxNumberOfSetPieces(nTmp, bCoordinateLimitHack);
		}
	}
	#endif

	// SHADOW LIMITS
	#if TRUE
	{
		if (INIreader.GetIntEx("SHADOW LIMITS", "Shadows stored", &nTmp))
			g_shadowLimits.SetShadowStored(nTmp);

		if (INIreader.GetIntEx("SHADOW LIMITS", "Poly bunches", &nTmp))
			g_shadowLimits.SetPolyBunches(nTmp);

		if (INIreader.GetIntEx("SHADOW LIMITS", "Static shadows", &nTmp))
			g_shadowLimits.SetStaticShadows(nTmp);

		if (INIreader.GetIntEx("SHADOW LIMITS", "Permanent shadows", &nTmp))
			g_shadowLimits.SetPermanentShadows(nTmp);

		if (INIreader.GetIntEx("SHADOW LIMITS", "Real time shadows", &nTmp))
			g_shadowLimits.SetRealTimeShadows(nTmp);
	}
	#endif

	// VEHICLE SPECIAL FEATURES
	#if TRUE
	{
		if (INIreader.GetBool("VEHICLE SPECIAL FEATURES", "Enable special features"))
		{
			SetModelIDsForVehSpecialFeatures("Number of hydra vehicles", "Hydra %d", &VehicleSpecialFeatures::AddHydra);
			SetModelIDsForVehSpecialFeatures("Number of ZR350 vehicles", "ZR350 %d", &VehicleSpecialFeatures::AddZR350);

			g_vehicleSpecialFeatures.CommitChanges();
		}
	}
	#endif	

	// LEVEL LIMITS
	#if TRUE
	{
		int numberOfLevels;

		if (INIreader.GetIntEx("LEVEL LIMITS", "Number of levels", &numberOfLevels)
			&& g_islandLimits.EnableIslandLimits(numberOfLevels))
		{
			char keyName[64];

			// Set model IDs for levels
			g_islandLimits.SetCopBikeID(INIreader.GetInt("LEVEL LIMITS", "Cop bike"));
			g_islandLimits.SetCopBikeDriverID(INIreader.GetInt("LEVEL LIMITS", "Cop ped bike"));


			SetModelIDsForLevels("Cop car level %d", &IslandLimits::SetCopCarID, true);
			SetModelIDsForLevels("Cop ped level %d", &IslandLimits::SetCopPedID, true);
			SetModelIDsForLevels("Ambulance level %d", &IslandLimits::SetAmbulanceID, false);
			SetModelIDsForLevels("Medic level %d", &IslandLimits::SetMedicID, false);
			SetModelIDsForLevels("Fire engine level %d", &IslandLimits::SetFireEngineID, false);
			SetModelIDsForLevels("Fireman level %d", &IslandLimits::SetFiremanEngineID, false);

			// cab drivers IDs
			for (int levelID = 0; levelID < numberOfLevels; levelID++)
			{
				sprintf(keyName, "Number of cab drivers for level %d", levelID);

				unsigned int numberOfCabDriversForLevel = INIreader.GetInt("LEVEL LIMITS", keyName);

				g_islandLimits.SetNumberOfCabDriversForLevel(levelID, numberOfCabDriversForLevel);

				for (unsigned int place = 0; place < numberOfCabDriversForLevel; place++)
				{
					sprintf(keyName, "Cab driver level %d place %d", levelID, place);

					unsigned int driverID = INIreader.GetInt("LEVEL LIMITS", keyName);

					g_islandLimits.SetCabDriverID(levelID, place, driverID);
				}
			}

			// item price multipliers
			{
				char keyName[32];

				for (unsigned int i = 0; i < g_islandLimits.ms_iNumberOfIslands; i++)
				{
					sprintf(keyName, "Item price multiplier %d", i);

					g_islandLimits.SetItemPriceMultiplier(
						i,
						this->INIreader.GetFloat("LEVEL LIMITS", keyName)
						);
				}
			}

			g_islandLimits.CommitChanges();
		}
	}
	#endif	

	// RESTARTS
	#if TRUE
	{
		if (INIreader.GetIntEx("RESTARTS", "Max number of hospital restarts", &nTmp))
			g_Restarts.SetHospitalRestarts(nTmp);
		
		if (INIreader.GetIntEx("RESTARTS", "Max number of police restarts", &nTmp))
			g_Restarts.SetPoliceRestarts(nTmp);
	}
	#endif

	// SPECIAL
	#if TRUE
	{
		// SPECIAL : MakeHelicoptersLandOnWater
		if (INIreader.GetBool("SPECIAL", "Make helicopters land on water when cars on water cheat enabled"))
			g_specialLimits.MakeHelicoptersLandOnWater();

		// SPECIAL : Disable radar rotation
		if (INIreader.GetBool("SPECIAL", "Disable radar rotation"))
			g_specialLimits.DisableRadarRotation();

		// SPECIAL : Disable plane speed limit
		if (INIreader.GetBool("SPECIAL", "Disable plane speed limit"))
			g_specialLimits.DisablePlaneSpeedLimit();

		// SPECIAL : Enable coordinate mover
		if (INIreader.GetBool("SPECIAL", "Enable coordinate mover"))
			CoordinateMover::ApplyHook();

		// SPECIAL : Make save of variable size
		if (INIreader.GetBool("SPECIAL", "Make save of variable size"))
		{
			if(g_SaveOfVariableLength.MakeSaveOfVariableLength())
				CGenericLogStorage::WriteLineSeparator();
		}

		// SPECIAL : Make paintjobs work for any ID
		if (INIreader.GetBool("SPECIAL", "Make paintjobs work for any ID"))
			g_specialLimits.MakePaintjobsWorkForAnyID();

		// SPECIAL : Enable loading text
		if (INIreader.GetBool("SPECIAL", "Enable loading text"))
			g_specialLimits.EnableLoadingText();

		// SPECIAL : Fix installfolder problem
		if (INIreader.GetBool("SPECIAL", "Fix installfolder problem"))
			g_specialLimits.FixInstallFolderProblem();

		// SPECIAL : Fix keyboard making bad mouse movement
		if (INIreader.GetBool("SPECIAL", "Fix keyboard making bad mouse movement"))					
			g_specialLimits.FixKeyboardMakingBadMouseMovement();		

		// SPECIAL : Fix cheats typed by keyboard not working
		if (INIreader.GetBool("SPECIAL", "Fix cheats typed by keyboard not working"))
			g_specialLimits.FixCheatsTypedFromKeyboardNotWorking();

		// SPECIAL : Alter file loading order
		if (INIreader.GetBool("SPECIAL", "Alter file loading order", true))
			g_specialLimits.AlterFileLoadingOrder();

		// SPECIAL : Remove LOD DFF requirement to hold native data
		if (INIreader.GetBool("SPECIAL", "Remove LOD DFF requirement to hold native data"))
			g_specialLimits.RemoveRequirementForLodDFFtoHoldNativePLGdata();

		// SPECIAL : Make loading of files from root directory possible
		if (INIreader.GetBool("SPECIAL", "Make loading of files from root directory possible"))
			g_specialLimits.MakeLoadingOfFilesFromRootDirectoryPossible();

		// SPECIAL : Fix HAL crashing on devices with Android 11 and higher
		if (INIreader.GetBool("SPECIAL", "Fix HAL crashing on devices with Android 11 and higher", false)
			|| INIreader.GetBool("SPECIAL", "Fix crashes on newer systems", true))
			g_specialLimits.FixHALCrashingOnDevicesWithAndroid11AndHigher();

		// SPECIAL : Disable CINFO.BIN and MINFO.BIN loading
		if (INIreader.GetBool("SPECIAL", "Disable CINFO.BIN and MINFO.BIN loading", true))
			g_specialLimits.DisableCINFOandMINFOLoading();
	}
	#endif

	// ERROR REPORTING
	#if TRUE
	{
		if (INIreader.GetBool("ERROR REPORTING", "Enable error reporting"))
		{
			struct {
				const char* property;
				eErrorType errorType;
			} errorList[] =
			{
				{ "Attempt to load object instance with undefined ID", GTA_ERROR_ATTEMPT_TO_LOAD_OBJECT_INSTANCE_WITH_UNDEFINED_ID },
				{ "Car generator limit exceeded", GTA_ERROR_CAR_GENERATOR_LIMIT_EXCEEDED },
				{ "Car generator with invalid model ID is getting registered", GTA_ERROR_CAR_GENERATOR_WITH_INVALID_MODEL_ID_IS_GETTING_REGISTERED },
				{ "Model does not have collision loaded", GTA_ERROR_MODEL_DOES_NOT_HAVE_COLLISION_LOADED },
				{ "IMG archive needs rebuilding", GTA_ERROR_IMG_ARCHIVE_NEEDS_REBUILDING },
				{ "Model has collision already set up", GTA_ERROR_MODEL_HAS_COLLISION_ALREADY_SET_UP },
				{ "Requested file does not exist", GTA_ERROR_REQUESTED_FILE_DOES_NOT_EXIST },
				{ "Model name is declared on multiple IDs", GTA_ERROR_MODEL_NAME_IS_DECLARED_ON_MULTIPLE_IDS },
				{ "Stream handles limit exceeded", GTA_ERROR_STREAM_HANDLES_LIMIT_EXCEEDED }			
			};

			for (int i = 0; i < _countof(errorList); i++)
			{
				// printf_MessageBox("option: %s %s %d\n", handlingLimits[i].property, cTmp, atoi(cTmp));

				if (INIreader.GetBool("ERROR REPORTING", errorList[i].property))
					g_errorReporting.SwitchErrorEnabled(errorList[i].errorType, true);
			}

			g_errorReporting.ApplyHook();
		}
	}
	#endif

	// DEBUG OUTPUT
	#if TRUE
	{
		if (INIreader.GetBool("DEBUG OUTPUT", "Enable debug output"))
			g_debugOutput.EnableDebugOutput();

		if (INIreader.GetBool("DEBUG OUTPUT", "Enable logging of files loaded"))
			g_debugOutput.EnableLoggingOfFilesLoaded();

	#ifndef NDEBUG
		if (INIreader.GetBool("DEBUG OUTPUT", "Redirect game new and delete to the FLA"))
			g_debugOutput.RedirectGameNewAndDeleteToTheFLA();
	#endif
	}
	#endif

	// Weapon limits
	#if TRUE
	{
		if (INIreader.GetBool("WEAPON LIMITS", "Enable weapon type loader")
			&& g_weaponLimits.EnableWeaponTypeLoader(true))
		{
			if (INIreader.GetIntEx("WEAPON LIMITS", "Weapon type loader, number of type IDs", &nTmp))
				g_weaponLimits.SetNumberOfWeaponTypes(nTmp);
		}

		if (INIreader.GetBool("WEAPON LIMITS", "Enable melee combo type loader")
			&& g_weaponLimits.EnableMeleeComboTypeLoader(true))
		{
			if (INIreader.GetIntEx("WEAPON LIMITS", "Max number of melee combos", &nTmp))
				g_weaponLimits.SetMaxNumberOfMeleeCombos(nTmp);
		}

		g_weaponLimits.CommitChanges();
	}
	#endif		

	// Roadblox limits
	#if TRUE
	{
		if (g_mapLimits.ms_bPathsPatchEnabled
			||INIreader.GetBool("ROADBLOCK LIMITS", "Apply roadblox.dat better loader"
			))
			g_roadBloxBetterLoader.ApplyBetterLoader();
	}
	#endif

	// Addons
	#if TRUE
	{
		if (INIreader.GetBool("ADDONS", "Enable cheat string loader"))
			g_cheatStringLoader.LoadCheatStrings();

		if (INIreader.GetBool("ADDONS", "Enable radar blip sprite filename loader"))
		{
			if (INIreader.GetIntEx("ADDONS", "Radar blip sprite filename loader, number of type IDs", &nTmp))
				g_RadarBlipSpriteFilenameLoader.SetNumberOfTypeIDs(nTmp);

			g_RadarBlipSpriteFilenameLoader.LoadBlipSpriteFilenames();
		}

		g_vehicleAudioLoader.EnableVehicleAudioLoader(INIreader.GetBool("ADDONS", "Enable vehicle audio loader"));
		g_vehicleAudioLoader.EnableDumpingDefaultSettings(INIreader.GetBool("ADDONS", "Enable dumping default vehicle audio settings"));
		g_vehicleAudioLoader.ApplyVehicleAudioLoaderIfEnabled();

		// Train type carriage loader
		if (INIreader.GetBool("ADDONS", "Enable train type carriages loader"))
		{
			if (INIreader.GetIntEx("ADDONS", "Train type carriage loader, max number of vehicles for type", &nTmp))
				g_trainTypeCarriageLoader.SetMaxNumberOfVehicleForType(nTmp);

			if (INIreader.GetIntEx("ADDONS", "Train type carriage loader, number of type IDs", &nTmp))
				g_trainTypeCarriageLoader.SetNumberOfTypeIDs(nTmp);

			g_trainTypeCarriageLoader.ApplyLoader();
		}

		if (INIreader.GetBool("ADDONS", "Enable FXT loader"))
			g_FxtLoader.ApplyFXTloader();

		if (INIreader.GetBool("ADDONS", "Enable not a prop ID range loader"))
			g_notApropIDrangeLoader.LoadNotApropIDranges();
	}
	#endif

	// Language
	#if TRUE
	{
		INIreader.GetString("MAIN", "Game language", NULL, cTmp, _countof(cTmp));

		if (cTmp[0])
			g_options.SetLanguage(cTmp);
	}
	#endif

	// DEBUGGING
	#if TRUE
	{
		if (INIreader.GetBool("DEBUGGING", "Copy info to pad 1 from pad 0"))
			g_debugging.SetPad1actLikePad0();
	}
	#endif
	
	// Credits
	g_Credits.EnableCredits(INIreader.GetBool("MAIN", "Disable FLA loading text"));
	  
	//////////////
	g_fileIDlimits.AllocateNeccessaryArrays();
	
	g_loadLevelHooks.ApplyHook();
	g_structureExtension.ApplyHook();
	g_InlinedCodeRemoving.ApplyHook();
	g_LoadingScreenFontHooks.ApplyHook();
	
	// Patcher
#ifdef IS_PLATFORM_WIN_X86
	if (INIreader.GetBool("PLUGIN PATCHES", "Enable plugin patches"))
		g_pluginPatches.RegisterPatcher();
#endif

	// Deprecated
#if FALSE
	if (INIreader.GetBool("PLUGIN PATCHES", "Enable CLEO loading"))
		g_pluginPatches.DoCLEOloading(
			INIreader.GetBool(
				"PLUGIN PATCHES",
			"Enable CLEO patches")
		);
#endif

#if PROJECT_USE_DEVELOPMENT_INI
	CFastman92limitAdjuster::Init();

	CTest::Run();
#endif

	g_CEasterEggs.Run();
#endif

#ifdef IS_PLATFORM_WIN
	InitCommonControls();

	RunTheModules();
#endif

	g_ProcessEntryPointCodeExecution.ApplyHook();

	// Restore initial directory
	SetCurrentWorkingDirectory_OS_independent(this->InitialDirectory);

	CGenericLogStorage::SaveFormattedTextLn(
		"Number of memory changes made: %d",
		CPatch::GetNumberOfMemoryChanges()
	);

	CGenericLogStorage::WriteLineSeparator();

	// Flush log file
	CGenericLogStorage::SaveWorkBuffer();
}

// Processes IPL limits
void CLimitAdjuster::ProcessIPLlimits()
{
	// IPL: inst, buildings
	if (INIreader.GetIntEx("IPL", "Buildings", &nTmp))
		g_IPLsectionlimits.SetIplBuildings(nTmp);

	// IPL: inst, animated buildings
	if (INIreader.GetIntEx("IPL", "Animated buildings", &nTmp))
		g_IPLsectionlimits.SetIplAnimatedBuildings(nTmp);

	// IPL: inst, dummies
	if (INIreader.GetIntEx("IPL", "Dummies", &nTmp))
		g_IPLsectionlimits.SetIplDummies(nTmp);

	// IPL: inst entries per file
	if (INIreader.GetIntEx("IPL", "Inst entries per file", &nTmp))
		g_IPLsectionlimits.SetInstLimitPerFile(nTmp);

	// IPL: Entity index array
	if (INIreader.GetIntEx("IPL", "Entity index array", &nTmp))
		g_IPLsectionlimits.SetEntityIndexArray(nTmp);

	// IPL: map zones
	if (INIreader.GetIntEx("IPL", "Map zones", &nTmp))
		g_IPLsectionlimits.SetMapZones(nTmp);

	// IPL: navigation zones
	if (INIreader.GetIntEx("IPL", "Navigation zones", &nTmp))
		g_IPLsectionlimits.SetNavigationZones(nTmp);

	// IPL: COccluder structure coordinate extension
	if (INIreader.GetBoolEx("IPL", "COccluder, apply coordinate limit patch", &bTmp))
		g_IPLsectionlimits.SetCOccluderCoordinateLimitHack(bTmp);

	// IPL: occl for interiors
	if (INIreader.GetIntEx("IPL", "Interior occluders", &nTmp))
		g_IPLsectionlimits.SetInteriorOccluders(nTmp);

	// IPL: occl for map
	if (INIreader.GetIntEx("IPL", "Occluders", &nTmp))
		g_IPLsectionlimits.SetOccluders(nTmp);

	// IPL: tcyc 
	if (INIreader.GetIntEx("IPL", "Timecycle modifiers", &nTmp))
		g_IPLsectionlimits.SetTcyc(nTmp);

	// IPL: cull mirror attribute zones
	if (INIreader.GetIntEx("IPL", "CULL mirror attribute zones", &nTmp))
		g_IPLsectionlimits.SetCullMirrorAttributeZones(nTmp);

	// IPL: CULL tunnel attribute zones
	if (INIreader.GetIntEx("IPL", "CULL tunnel attribute zones", &nTmp))
		g_IPLsectionlimits.SetCullTunnelAttributeZones(nTmp);

	// IPL: CULL tunnel attribute zones
	if (INIreader.GetIntEx("IPL", "CULL attribute zones", &nTmp))
		g_IPLsectionlimits.SetCullAttributeZones(nTmp);

	// IPL: jump (256)
	if (INIreader.GetIntEx("IPL", "Stunt jumps", &nTmp))
		g_IPLsectionlimits.SetStuntJumps(nTmp);

	// IPL: enex (400)
	if (INIreader.GetIntEx("IPL", "Entry exits", &nTmp))
		g_IPLsectionlimits.SetEntryExits(nTmp);

	// IPL: auzo zone boxes
	if (INIreader.GetIntEx("IPL", "Auzo zone boxes", &nTmp))
		g_IPLsectionlimits.SetAudioZoneBoxes(nTmp);

	// IPL: auzo zone boxes
	if (INIreader.GetBoolEx("IPL", "Auzo zone boxes, apply coordinate limit patch", &bTmp))
		g_IPLsectionlimits.SetAudioZoneBoxesCoordinateLimitHack(bTmp);

	// IPL: auzo zone spheres
	if (INIreader.GetIntEx("IPL", "Auzo zone spheres", &nTmp))
		g_IPLsectionlimits.SetAudioZoneSpheres(nTmp);

	// IPL: pickups
	if (INIreader.GetBool("IPL", "Enable pickup limit patch"))
	{
		g_IPLsectionlimits.EnablePickupPatch(true);

		// IPL: pickups, coordinate limit will be hacked as well (620)
		if (INIreader.GetIntEx("IPL", "Pickups", &nTmp))
			g_IPLsectionlimits.SetPickups(nTmp);

		if (INIreader.GetIntEx("IPL", "Pickup collected", &nTmp))
			g_IPLsectionlimits.SetPickupCollected(nTmp);
	}

	g_IPLsectionlimits.ApplyEnabledLimits();
}

// Processes IDE limits
void CLimitAdjuster::ProcessIDElimits()
{
	// IDE: objs
	if (INIreader.GetIntEx("IDE LIMITS", "IDE Objects Type 1", &nTmp))
		g_IDEsectionLimits.SetIDEobjsType1(nTmp);

	// IDE: objs
	if (INIreader.GetIntEx("IDE LIMITS", "IDE Objects Type 2", &nTmp))
		g_IDEsectionLimits.SetIDEobjsType2(nTmp);

	// IDE: hier
	if (INIreader.GetIntEx("IDE LIMITS", "Hier Objects", &nTmp))
		g_IDEsectionLimits.SetHierObjects(nTmp);

	// IDE: tobjs
	if (INIreader.GetIntEx("IDE LIMITS", "Timed Objects", &nTmp))
		g_IDEsectionLimits.SetTimedObjects(nTmp);

	// IDE : cars
	if (INIreader.GetIntEx("IDE LIMITS", "Vehicle Models", &nTmp))
		g_IDEsectionLimits.SetVehicleModels(nTmp);

	// IDE : peds
	if (INIreader.GetIntEx("IDE LIMITS", "Ped Models", &nTmp))
		g_IDEsectionLimits.SetPedModels(nTmp);

	// IDE : weap
	if (INIreader.GetIntEx("IDE LIMITS", "Weapon Models", &nTmp))
		g_IDEsectionLimits.SetWeaponModels(nTmp);

	// IDE : 2dfx
	if (INIreader.GetIntEx("IDE LIMITS", "2DFX Effects", &nTmp))
		g_IDEsectionLimits.Set2DFX(nTmp);
}

// Processes handling limits
void CLimitAdjuster::ProcessHandlingLimits()
{
	if (INIreader.GetBool("HANDLING.CFG LIMITS", "Apply handling.cfg patch"))
	{
		const tLimitDefinitionNonStatic* handlingLimits = HandlingCfgLimits::ms_listOfLimits;

		for (int i = 0; i < _countof(HandlingCfgLimits::ms_listOfLimits); i++)
		{
			// printf_MessageBox("option: %s %s %d\n", handlingLimits[i].property, cTmp, atoi(cTmp));

			if (INIreader.GetIntEx("HANDLING.CFG LIMITS", handlingLimits[i].property, &nTmp))
				(g_handlingCfgLimits
					.*(g_handlingCfgLimits.ms_listOfLimits[i].method))(nTmp);
		}

		g_handlingCfgLimits.PatchHandlingCfgLimit();
	}
}

// Processes dynamic limits
void CLimitAdjuster::ProcessDynamicLimits()
{
	// CPatch::EnableDebugMode();
	
	for (int i = 0; i < DynamicLimits::ms_numberOfLimits; i++)
		if (INIreader.GetIntEx("DYNAMIC LIMITS", DynamicLimits::ms_listOfDynamicLimits[i].property, &nTmp))
			(g_dynamicLimits
				.*(g_dynamicLimits.ms_listOfDynamicLimits[i].method))(nTmp);
				
	g_dynamicLimits.ApplyEnabledLimits();
	// CPatch::DisableDebugMode();
}

// Processes ID limits
void CLimitAdjuster::ProcessIDlimits()
{
	if (g_fileIDlimits.IsIDlimitsPatchEnabled())
	{
		// Read possibly different values
		for (int i = 0; i < g_fileIDlimits.GetCountOfTypes(); i++)
		{
			eFileType type = g_fileIDlimits.GetFileTypeInfoByIndex(i)->fileType;
			const char* sType = CFileTypeInfo::GetEnumNameByMember(type);

			if (INIreader.GetIntEx("ID LIMITS", sType, &nTmp))
			{
				if (type == FILE_TYPE_DAT)
					throw f92_runtime_error(
						"FILE_TYPE_DAT is no longer valid entry for ID limits.\n"
						"If you need, set the ([MAP LIMITS] Paths map size) instead."
					);
				else
					g_fileIDlimits.SetFileIDlimit(type, nTmp, !PROJECT_USE_DEVELOPMENT_INI);
			}
		}

		g_fileIDlimits.PatchFileIDlimits();
	}

	// Count of killable model IDs
	if (INIreader.GetIntEx("ID LIMITS", "Count of killable model IDs", &nTmp))
		g_fileIDlimits.PatchCountOfKillableModelIDs(nTmp);

	// File binary search by name
	if (INIreader.GetBool("ID LIMITS", "Use file binary search by name"))
		g_fileIDlimits.PatchUseFileBinarySearchByName();
}

// Terminates game process
void CLimitAdjuster::TerminateProcess()
{
	CGenericLogStorage::SaveTextLn("Game terminated.");
	CGenericLogStorage::CloseFile();
	#ifdef IS_PLATFORM_WIN
	ExitProcess(NULL);
	#elif defined(IS_PLATFORM_ANDROID)
	terminate();
	#endif
}

// Returns game version
eGameVersion CLimitAdjuster::GetGameVersion() const
{
	return this->m_GameVersion;
}

// Initializes a limit adjuster
void CLimitAdjuster::Initialize()
{
	//////////////////////// directory
	#ifdef IS_PLATFORM_ANDROID
	this->jniEnv = 0;
	this->jvm->GetEnv((void **)&this->jniEnv, JNI_VERSION_1_4);
	#endif

	CPatch::Init();

	this->InitializeModules();

	/////////////////////
	eGameVersion gameVersion = this->GetGameVersion();

	#ifdef IS_PLATFORM_WIN
	// Set CPatch
	#if TRUE
	{
		tPatchLevelInfo* globalSettings = CPatch::GetPointerToSettings();
		globalSettings->bPatchForbiddenCheck = true;
		globalSettings->bDebugEnabled = GLOBAL_LIMIT_DEBUG;

		// List of forbidden memory ranges
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			CPatch::AddForbiddenMemoryRegion(0x4C9970, 0x4CDDE0);
			CPatch::AddForbiddenMemoryRegion(0x598000, 0x598010);
			CPatch::AddForbiddenMemoryRegion(0x5C26B0, 0x5D0240);
			CPatch::AddForbiddenMemoryRegion(0x748F20, 0x77F0BB);
			CPatch::AddForbiddenMemoryRegion(0x7C45E0, 0x7CF600);
			CPatch::AddForbiddenMemoryRegion(0x7EC760, 0x837170);
			CPatch::AddForbiddenMemoryRegion(0xCB1000, 0x1560930);
		}
	}
	#endif

	uintptr_t lastMovedExecuted = 0;

	if (PROJECT_IS_UNRELEASED_EDITION && CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		lastMovedExecuted = 0x8C813C;

	CCodeMover::Init(150000, lastMovedExecuted);
	#endif

	/////////////////////

	/*
	#ifdef IS_PLATFORM_ANDROID
	this->bDelayedProcessingOfLimits = true;
	#endif
	*/

	CGenericLogStorage::SaveFormattedTextLn("Number of FLA modules: %d", _countof(LimitAdjusterPtrs));

	if (this->bDelayedProcessingOfLimits)
		CGenericLogStorage::SaveTextLn("Delayed processing of limits? Yes");
	else
		CGenericLogStorage::SaveTextLn("Delayed processing of limits? No");

	CGenericLogStorage::WriteNewLine();
}

// Shuts down a limit adjuster classes
void CLimitAdjuster::Shutdown()
{
	this->ShutDownModules();

	CCodeMover::Shutdown();
}

// Initializes limit adjuster modules
void CLimitAdjuster::InitializeModules()
{
	for (int i = 0; i < _countof(LimitAdjusterPtrs); i++)
		LimitAdjusterPtrs[i]->Initialise();
}

// Shuts down limit adjuster modules
void CLimitAdjuster::ShutDownModules()
{
	for (int i = _countof(LimitAdjusterPtrs) - 1; i >= 0; i--)
		LimitAdjusterPtrs[i]->Shutdown();
}

// Set up native code module handles
void CLimitAdjuster::SetUpNativeCodeModuleHandles(const tLimitAdjusterStartParams* pLimitAdjusterStartParams)
{
	#ifdef IS_PLATFORM_WIN
	// Set up module handles
	this->hModule_of_the_FLA.windows = (HMODULE)pLimitAdjusterStartParams->pluginHandle;
	this->hModule_of_game.windows = (HMODULE)pLimitAdjusterStartParams->applicationLibHandle;
	memset(&this->hModule_of_socialClub, 0, sizeof(this->hModule_of_socialClub));
	#elif defined(IS_PLATFORM_ANDROID)
	// Set up module handles
	this->hModule_of_the_FLA.linux_os = pLimitAdjusterStartParams->pluginHandle;
	this->hModule_of_game.linux_os = pLimitAdjusterStartParams->applicationLibHandle;
	
	this->hModule_of_socialClub.linux_os = dlopen("libSCAnd.so", 4);	// 4 - RTLD_NOLOAD
	#endif
}

#ifdef IS_PLATFORM_ANDROID
// Attaches the thread to Java machine and returns JNIEnv* pointer
JNIEnv* CLimitAdjuster::GetCurrentThreadJNIEnv()
{
	return ::GetCurrentThreadJNIEnv();
}
#endif

// Try to sets game info by filename
bool CLimitAdjuster::TrySetGameInfoByFilename(
	const wchar_t* filename,
	const char* applicationName,
	uintptr_t preferedVA,
	uintptr_t currentVA,
	Game::eGameVersion gameVersion
)
{
	#if IS_PLATFORM_WIN
	if (!wcsicmp(this->EXEfilename, filename))
	{
		this->SetGameInfo(preferedVA, currentVA, gameVersion, gameDetectedStr, true);

		return true;
	}
	#endif

	return false;
}

// Sets game info by EXE/library filesize
bool CLimitAdjuster::TrySetGameInfoByEXEsize(
	unsigned int exeSize,
	const char* applicationName,
	uintptr_t preferedVA,
	uintptr_t currentVA,
	Game::eGameVersion gameVersion
)
{
	#if IS_PLATFORM_WIN
	if (exeSize == this->exeFilesize)
	{
		this->SetGameInfo(preferedVA, currentVA, gameVersion, gameDetectedStr, true);

		return true;
	}
	#endif

	return false;
}

// Sets game info
void CLimitAdjuster::SetGameInfo(
	uintptr_t preferedVA,
	uintptr_t currentVA,
	eGameVersion gameVersion,
	const char* gameDetectedStr,
	bool bAddExeSize
)
{
	this->m_GameVersion = gameVersion;
	g_mCalc.Initialize(preferedVA, currentVA);

	MAKE_DEAD_IF();
	#if defined(IS_PLATFORM_WIN)
	else if(bAddExeSize)
		sprintf(this->gameDetectedStr, "%s %d bytes", gameDetectedStr, (unsigned int)this->exeFilesize);
	#else
	else
		strcpy(this->gameDetectedStr, gameDetectedStr);
	#endif
		
	// Initalization without memory?
	if (currentVA == 0)
	{
		this->bIsGameMemorySetUp = false;
		return;
	}

	this->bIsGameMemorySetUp = true;

	#ifdef IS_PLATFORM_WIN
	PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)currentVA;	
	PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((uintptr_t)(dosHeader)+(dosHeader->e_lfanew));

	WORD DllCharacteristics = ntHeader->OptionalHeader.DllCharacteristics;

	this->bDynamicImageBase = (DllCharacteristics & IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE) != 0;
	#elif defined(IS_PLATFORM_ANDROID)
	this->bDynamicImageBase = false;

	const unsigned char* pElfIdent = (const unsigned char*)currentVA;
	
	eValueEncoding valueEncoding;

	unsigned char encodingInHeader = pElfIdent[EI_DATA];
	unsigned char Class = pElfIdent[EI_CLASS];

	if (encodingInHeader == ELFDATA2LSB)
		valueEncoding = VALUE_ENCODING_LITTLE_ENDIAN;
	else if (encodingInHeader == ELFDATA2MSB)
		valueEncoding = VALUE_ENCODING_BIG_ENDIAN;
	else
		return;

	ELF_format::CHeader header;

	if (Class == ELFCLASS32)
		ELF_format::ReadELFheader(header, *(const ELF_format::elf32_hdr_variedEncoding*)currentVA, valueEncoding);	
	else if (Class == ELFCLASS64)
		ELF_format::ReadELFheader(header, *(const ELF_format::elf64_hdr_variedEncoding*)currentVA, valueEncoding);
	else
		return;

	if (header.e_type & ET_REL)
		this->bDynamicImageBase = true;
	#endif
}

// Global variables
CLimitAdjuster g_LimitAdjuster;

CMemoryAddressCalculator g_mCalc;
CMemoryAddressCalculator g_libSCAnd_mCalc;
CMemoryScanner g_mScanner;
CDynamicEnumAllocator<int> g_EnumAllocator;
CDynamicStructAllocator g_StructAllocator;
CMemoryCall g_memoryCall;
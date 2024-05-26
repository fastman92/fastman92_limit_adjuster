/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#include "eGameVersion.h"

#include <DynamicTypes/DynamicEnumeration.h>
#include <DynamicTypes/DynamicStructure.h>

#include "../ForOtherProjects\FLA_not_required\Main.h"

#include <IniReader\CIniReader.h>
#include <MemoryAddressCalculator\CMemoryAddressCalculator.h>
#include <MemoryScanner\CMemoryScanner.h>
#include <MultiPlatformSupport/PlatformGeneralisation.h>

#include <Exception/exception.h>

#include "Configuration\Configuration.h"

#include "MemoryCall.h"

#include <time.h>

#ifdef IS_PLATFORM_ANDROID
#include <jni.h>
#endif

// Global variables
extern CMemoryAddressCalculator g_mCalc;
extern CMemoryAddressCalculator g_libSCAnd_mCalc;
extern CMemoryScanner g_mScanner;
extern CDynamicEnumAllocator<int> g_EnumAllocator;
extern CDynamicStructAllocator g_StructAllocator;
extern CMemoryCall g_memoryCall;

#ifdef IS_PLATFORM_ANDROID
#define LIBRARY_ADDRESS_BY_HANDLE(dlhandle) ((NULL == dlhandle) ? NULL : (void*)*(size_t const*)(dlhandle))
#endif

// Structure, which includes parameters used during the initialization of the FLA.
struct tLimitAdjusterStartParams
{
	#ifdef IS_PLATFORM_ANDROID
	JavaVM* jvm;
	void* second_param_reserved;
	// JNIEnv* env;
	
	const char* pluginLibraryPath;	// the FLA plugin path
	const char* applicationLibIdentifier;
	#endif

	void* pluginHandle;		// the FLA library handle
	void* applicationLibBaseAddress;	// game EXE base address
	void* applicationLibHandle;	// game EXE handle
};

enum class eDayPart
{
	DAY_PART_UNDEFINED,
	DAY_PART_DAY,
	DAY_PART_NIGHT,
};

enum class eFLA_actionToDo
{
	Start,
	Process,
	Stop
};

#define FLA_MAX_PATH 1024

class CLimitAdjuster
{
private:
	Game::eGameVersion m_GameVersion;

	bool bIsAdditionalJavaCodeLoaded;
	bool bIsGameMemorySetUp;
	 
public:
	CIniReader INIreader;

	// Launch time
	bool launchTimeRetrieved;
	struct tm launchTimeLocal;
	struct tm launchTimeUTC;

	// Is night time
	eDayPart launchTimeDayPart;

	// hModule of the FLA library
	tGenericLibraryModule hModule_of_the_FLA;

	// hModule of the social Club
	tGenericLibraryModule hModule_of_socialClub;

	// hModule of game library/EXE
	tGenericLibraryModule hModule_of_game;

#ifdef IS_PLATFORM_WIN
	uint64_t exeFilesize;
	wchar_t EXEfilePath[MAX_PATH];
	const wchar_t* EXEfilename;
#endif

#ifdef IS_PLATFORM_ANDROID
	JavaVM* jvm;
	void* second_param_reserved;
	JNIEnv* jniEnv;	// for main thread

	jobject mainActivityDuringLaunch;
#endif

	// Primary settings
	bool bDelayedProcessingOfLimits;
	bool bDynamicImageBase;
	bool bIsMultiplayerRunning;

	char gameDetectedStr[64];

	const Configuration::tPlatformConfiguration* pPlatformConfig;
	const Configuration::CGameDescription* pGameVersionDescription;

	// Package name
	char PackageName[128];
	char OriginalPackageName[128];

	// Directories
	char FLA_release_directory[FLA_MAX_PATH];	// release directory, used by author of the FLA

	char ApplicationLibraryDirectory[FLA_MAX_PATH];	// lib directory

	char InitialDirectory[FLA_MAX_PATH];	// EXE directory on Windows, slash on Android
	char StorageRootDirectory[FLA_MAX_PATH];	// EXE directory on Windows, STORAGE_ROOT on Android
	char StorageRootBase[FLA_MAX_PATH];	// Unset on Windows, STORAGE_ROOT_BASE on Android
	char CacheDirectory[FLA_MAX_PATH];	// Cache directory

public:
	// Processes FLA action
	void ProcessFLAaction(eFLA_actionToDo action, void* pData = 0);

	// Processes an error of being unable to detect the game
	void ProcessUnableToDetectTheGame();

	// Terminates game process
	static void TerminateProcess();

	// Returns game version
	Game::eGameVersion GetGameVersion() const;

	// Get filename for FLA library
	static const char* GetFLAlibraryFilename(Game::eGamePlatform platform);

	// Get filename for game
	static const char* GetIniFilenameForGame(Game::eGameVersion gameVersion, bool devFilePossible = true);

	// Is game memory set up?
	bool IsGameVersionSetUpWithMemory();

	// Attaches the thread to Java machine and returns JNIEnv* pointer
	#ifdef IS_PLATFORM_ANDROID
	JNIEnv* GetCurrentThreadJNIEnv();
	#endif

	// Get path to file from root directory
	std::string GetPathToFlaFileFromRootDirectory(const char* filename);

	// Flushes instruction cache
	void FlushInstructionCache();

private:
	// Starts limit adjuster
	void StartLimitAdjuster(const tLimitAdjusterStartParams* pLimitAdjusterStartParams);

	// Stops limit adjuster
	void StopLimitAdjuster();

	// Initializes a limit adjuster
	void Initialize();

	// Shutdowns a limit adjuster
	void Shutdown();

	// Initializes limit adjuster modules
	void InitializeModules();

	// Shuts down limit adjuster modules
	void ShutDownModules();

	// Manages error message
	void ManageErrorMessage(const char* msg);

	// For configuration workbook initialisation
	friend class Configuration::Workbook;

	// Set up native code module handles
	void SetUpNativeCodeModuleHandles(const tLimitAdjusterStartParams* pLimitAdjusterStartParams);

	// Try to sets game info by filename
	bool TrySetGameInfoByFilename(
		const wchar_t* filename,
		const char* applicationName,
		uintptr_t preferedVA,
		uintptr_t currentVA,
		Game::eGameVersion gameVersion
	);

	// Sets game info by EXE/library filesize
	bool TrySetGameInfoByEXEsize(
		unsigned int exeSize,
		const char* applicationName,
		uintptr_t preferedVA,
		uintptr_t currentVA,
		Game::eGameVersion gameVersion
	);

	// Sets game info
	void SetGameInfo(
		uintptr_t preferedVA,
		uintptr_t currentVA,
		Game::eGameVersion gameVersion,
		const char* gameDetectedStr,
		bool bAddExeSize = false
	);

	// Open INI file.
	void OpenIniFile(const char* filename);

	// Generates INI file
	bool GenerateINIfile(const char* filename);

	// Generate documentation files
	void GenerateDocumentationFiles();
	
	// Friend class
	friend class CApplicationInit;

	// Loads additional java code
	void LoadAdditionalJavaCode();

	// Processes limits
	void Process();

	// Processes IPL limits
	void ProcessIPLlimits();

	// Processes IDE limits
	void ProcessIDElimits();

	// Processes handling limits
	void ProcessHandlingLimits();

	// Processes dynamic limits
	void ProcessDynamicLimits();

	// Processes ID limits
	void ProcessIDlimits();
};

extern CLimitAdjuster g_LimitAdjuster;

#define MAKE_VAR_GAME_VERSION() const Game::eGameVersion gameVersion = g_LimitAdjuster.GetGameVersion(); gameVersion;

#include "UsefulMacros.h"
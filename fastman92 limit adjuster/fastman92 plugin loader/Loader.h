/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "ForOtherProjects/Exports.h"

#include <limits.h>
#include <jni.h>
#include <string>
#include <vector>

#define PATH_LIMIT 1024

enum class ePluginLoadingMode
{
	LOAD_UNDEFINED,
	LOAD_CLEO,
	LOAD_FLA_ONLY,
	LOAD_PLUGINS
};

struct CPluginDirectory
{
	std::string path;
	std::string copiedFromPath;
	ePluginLoadingMode loadingMode;

	CPluginDirectory(const char* path, const char* copiedFromPath, ePluginLoadingMode loadingMode)
	{
		this->path = path;

		if(copiedFromPath)
			this->copiedFromPath = copiedFromPath;

		this->loadingMode = loadingMode;
	}
};

class CLoadedPluginInfo
{
public:
	const CPluginDirectory* pDirectory;
	char filename[256];
	ePluginLoadingMode loadingMode;

	// tOnApplicationInit applicationInit;

	CLoadedPluginInfo()
	{
		this->pDirectory = 0;
		this->filename[0] = 0;
		this->loadingMode = ePluginLoadingMode::LOAD_UNDEFINED;
		// this->applicationInit = 0;
	}
};

class CPluginLoader
{
public:
	char ms_packageName[128];
	char ms_originalPackageName[128];

	char ms_InitialDirectory[PATH_LIMIT];	// EXE directory on Windows, slash on Android
	char ms_StorageRootDirectory[PATH_LIMIT];	// EXE directory on Windows, STORAGE_ROOT on Android
	char ms_StorageRootBaseDirectory[PATH_LIMIT];	// Unset on Windows, STORAGE_ROOT_BASE on Android
	char ms_PluginDirectory[PATH_LIMIT];	// Plugin directory, set on Android

	char ms_CacheDirectory[PATH_LIMIT];	// DEX cache directory

	static std::vector<CLoadedPluginInfo> ms_loadedPluginsArray;
	std::vector<CPluginDirectory> m_pluginDirectoryPaths;

	JavaVM* m_javaVm;
	void* m_reserved;
	JNIEnv* jniEnv;	// for main thread

	void* pluginLoaderHandle;
	const char* pTargetArchABI;

	char* TrampolineSpacePtr;
	unsigned int TrampolineSpaceSize;
	unsigned int TrampolinePosition;

	const char* pApplicationIdentifier;
	char ms_applicationIdentifierDeprecated[4];
	void* applicationLibHandle;
	void* m_baseAddressForApplicationLibrary;

	static jobject ms_mainActivityDuringLaunch;

	static bool bCLEOloaded;

	void* FLApluginHandle;

	// Constructor
	CPluginLoader();

	// Sets path by function from loader
	static void GetApplicationLibDirectoryPath(char* libPluginPath);

	// Initializes
	bool InitialiseLoading(
		JavaVM* javaVm,
		void* reserved,
		const void* someAddressFromApplicationLibrary
	);
	
	// Loads CLEO
	void LoadCLEO(const char* directory);

	// Does plugin loading
	void LoadPluginsInDirectory(
		const char* libPluginPath,
		ePluginLoadingMode loadingMode
	);

	// Prescans a directory
	void PrescanDirectory(
		const CPluginDirectory* pDirectory
	);

	// Loads plugins
	void FinishLoadingPlugins();

	// Checks if valid plugin name
	static bool CheckIfValidPluginFileName(const char* filename);

	// Checks if valid SO library name
	static bool CheckIfValidSOlibraryName(const char* filename);

	// Checks if plugin name with this name is already loaded
	bool IsPluginWithThisNameAlreadyLoaded(const char* filename);

	// Load plugins
	void LoadPlugins();

	// Initialises the directory paths
	void InitialiseDirectoryPaths(JNIEnv* jniEnv, jobject mainActivity);

	// Does application initialization stage
	void DoAppInitializationStage(JNIEnv* jniEnv, jobject mainActivity);
};

extern CPluginLoader g_Loader;
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#pragma once

#ifdef IS_PLATFORM_ANDROID
#include <jni.h>
#include <stdint.h>

#include <MultiPlatformSupport/PlatformGeneralisation.h>

#undef F92_LA_API
#ifdef FASTMAN92_PLUGIN_LOADER
#define F92_LA_API DLL_EXPORT
#else
#define F92_LA_API DLL_IMPORT
#endif

struct tPluginStartParams
{
	unsigned int structureSize;	// sizeof(tApplicationStartParams)
	///////

	JavaVM* jvm;	// Java virtual machine
	void* second_param_reserved;	// Reserved param (from Jni_OnLoad)
	
	void* pluginHandle;	// Plugin library handle
	const char* pluginLibraryPath;	// Plugin library path
	char applicationLibIdentifierDeprecated[4];	// Deprecated, application lib identifier, for example "SA20" - GTA SA 2.0, deprecated
	void* applicationLibBaseAddress;	// Application library image base address
	void* applicationLibHandle;	// Application library handle

	// Added with plugin loader from FLA 7.0
	const char* applicationLibIdentifierStr;
	void* pluginLoaderHandle;
	const char* pTargetArchABI;
};

// The type of function called on plugin loading.
typedef bool(*tOnPluginLoad)(
	tPluginStartParams* pPluginStartParams
	);

typedef bool(*tOnApplicationInit)();

typedef tOnPluginLoad tOnPluginLoadWhenAppIsInitialized;

// Type of Jni_OnLoad
typedef jint(*type_JNI_OnLoad)(JavaVM* aVm, void* aReserved);
typedef void(*type_JNI_OnUnload)(JavaVM* aVm, void* aReserved);

// Functions
extern "C"
{
	// Compares a library identifier to specified value, for example against "SA20"
	// Identifiers take 4 bytes. That's a FourCC ("four-character code").
	F92_LA_API bool TestLibIdentifier(const char* pIdentifier, const char* valueToTestAgainst);

	// Attaches the thread to Java machine and returns JNIEnv* pointer
	F92_LA_API JNIEnv* GetCurrentThreadJNIEnv();
	
	/*
		The functions below will only return values, when application initialization is done
		Use in function OnApplicationInit of your plugin.
	*/	
	// Returns application package name
	F92_LA_API const char* GetApplicationPackageName();

	// Returns original application package name
	F92_LA_API const char* GetApplicationOriginalPackageName();

	// Returns the pointer to initial directory
	F92_LA_API const char* GetInitialDirectoryPath();

	// Returns the pointer to root directory
	F92_LA_API const char* GetStorageRootDirectoryPath();

	// Returns the pointer to storage directory
	F92_LA_API const char* GetStorageRootBaseDirectoryPath();

	// Returns the pointer to cache directory
	F92_LA_API const char* GetCacheDirectoryPath();

	// Returns jobject of main activity during launch
	F92_LA_API jobject GetMainActivityDuringLaunch();
}
#endif
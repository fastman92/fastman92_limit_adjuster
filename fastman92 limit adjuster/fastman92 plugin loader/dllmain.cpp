/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

// dllmain.cpp : Defines the entry point for the DLL application.

#include "ForOtherProjects/Exports.h"
#include "Loader.h"
#include "Log.h"



#include "../fastman92 limit adjuster/Source files/ForOtherProjects/Common/common.h"

#include "../fastman92 limit adjuster/Source files/Core/ProjectConstants.h"

#include <Exception\exception.h>
#include <fileIO.h>
#include <MultiPlatformSupport/PlatformGeneralisation.h>

#include <pthread.h>

#ifdef IS_PLATFORM_WIN
#include <windows.h>
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif

#ifdef IS_PLATFORM_ANDROID
#include <jni.h>
#include <errno.h>

#include <string.h>
// #include <unistd.h>

#include <android/log.h>

#include <stdint.h>

#include <dirent.h>
#include <dlfcn.h>
#include <jni.h>
#include <link.h>
#include <stdio.h>
#include <limits.h>

bool strEndCompare(const char* str, const char* needle)
{
	int l_str = strlen(str);
	int l_needle = strlen(needle);

	if (l_needle > l_str)
		return false;

	return !memcmp(str + l_str - l_needle, needle, l_needle);
}

#ifdef IS_ARCHITECTURE_ARM32
jint NAKED JNIEXPORT ToAddIntoFile_JNI_OnLoad(JavaVM* javaVm, void* reserved)
{
	__asm volatile(
		".thumb\n"
		"mov r2, pc\n"

		"ldr r3, PluginLoader_JNI_OnLoad%=\n"
		"add r3, pc\n"
		"ldr r3, [r3]\n"
		"bx r3\n"

		".align 4\n"
		"PluginLoader_JNI_OnLoad%=:.word 0x65874327\n" // PluginLoader_JNI_OnLoad, offset: -4
		: :
		);
}

#elif IS_ARCHITECTURE_ARM64
unsigned int someValue;

jint NAKED JNIEXPORT ToAddIntoFile_JNI_OnLoad(JavaVM* javaVm, void* reserved)
{
	__asm volatile(
		"adrp x2, #0\n" \
		"ldr w3, PluginLoader_JNI_OnLoad\n"
		"add x3, x2, x3\n"
		"ldr x3, [x3]\n"

		"br x3\n"

		".align 4\n"
		"PluginLoader_JNI_OnLoad:.word 0x65874327\n" // PluginLoader_JNI_OnLoad, offset: -4
		);
}
#endif

extern "C"
{
	#if 0
	// This function will load the SO libraries
	void JNIEXPORT ProcessPluginLoading()
	{
		LOGI("Starting plugin loader, shared objects get loaded at the end of processing .init_array in the host library.");
		DoLoading();
	}
	#endif

	#if 0
	void JNIEXPORT ProcessSAMPloading(JavaVM* javaVm, void* reserved, unsigned int applicationIdentifier, void* baseAddressForApplicationLibrary)
	{
		g_Loader.GetApplicationLibDirectoryPath(libPluginPath);
		char path[PATH_MAX];
		sprintf(path, "%s/libsamp.so", libPluginPath);

		void* pluginHandle = dlopen(path, RTLD_GLOBAL | RTLD_LAZY);

		type_JNI_OnLoad pJni_OnLoad = (type_JNI_OnLoad)dlsym(pluginHandle, "JNI_OnLoad");

		if (pJni_OnLoad)
			pJni_OnLoad(javaVm, reserved);
	}
	#endif
	
	#if 1

	// This function will load the SO libraries
	jint JNIEXPORT PluginLoader_OnLoad(JavaVM* javaVm, void* reserved, const void* someAddressFromApplicationLibrary)
	{
		OutputFormattedDebugString("Starting plugin loader %s, %s", PROJECT_VERSION, TOSTRING(SOLUTION_PLATFORM));
		
		try
		{
			if (!g_Loader.InitialiseLoading(javaVm, reserved, someAddressFromApplicationLibrary))
				OutputFormattedDebugString("Failed to initialise.");
		}
		catch (f92_runtime_error& error)
		{
			const char* errorStr = error.what();
			OutputFormattedDebugString("%s", errorStr);
			return JNI_EVERSION;
		}

		// Call original JNI_OnLoad
		type_JNI_OnLoad pJni_OnLoad = (type_JNI_OnLoad)dlsym(g_Loader.applicationLibHandle, "Original_JNI_OnLoad");
		return pJni_OnLoad(javaVm, reserved);
	}
	#endif

	void JNIEXPORT PluginLoader_OnUnload(JavaVM *javaVm, void *reserved, void* someAddressFromApplicationLibrary)
	{
		OutputFormattedDebugString("Stopping plugin loader");

		// Call original JNI_OnLoad
		type_JNI_OnLoad pJni_OnUnload = (type_JNI_OnLoad)dlsym(g_Loader.applicationLibHandle, "Original_JNI_OnUnload");
		pJni_OnUnload(javaVm, reserved);
	}
}

// Exported functions
extern "C"
{
	// Compares a library identifier to specified value, for example against "SA20"
	// Identifiers take 4 bytes. That's a FourCC ("four-character code").
	F92_LA_API bool TestLibIdentifier(const char* pIdentifier, const char* valueToTestAgainst)
	{
		return pIdentifier[0] == valueToTestAgainst[0]
			&& pIdentifier[1] == valueToTestAgainst[1]
			&& pIdentifier[2] == valueToTestAgainst[2]
			&& pIdentifier[3] == valueToTestAgainst[3];
	}

	// Key to access JNIEnv* for current thread
	static pthread_key_t CurrentThreadJNIenvKey = 0;

	// Attaches the thread to Java machine and returns JNIEnv* pointer
	F92_LA_API JNIEnv* GetCurrentThreadJNIEnv()
	{
		JNIEnv* pJNIenv;

		if (CurrentThreadJNIenvKey)
		{
			pJNIenv = (JNIEnv*)pthread_getspecific(CurrentThreadJNIenvKey);

			if (pJNIenv)
				return pJNIenv;
		}
		else
			pthread_key_create(&CurrentThreadJNIenvKey, 0);

		// Need to attach the thread
		if (g_Loader.m_javaVm->AttachCurrentThread(&pJNIenv, NULL) == JNI_OK)
			pthread_setspecific(CurrentThreadJNIenvKey, pJNIenv);

		return pJNIenv;
	}

	// Returns application package name
	F92_LA_API const char* GetApplicationPackageName()
	{
		return g_Loader.ms_packageName;
	}

	// Returns original application package name
	F92_LA_API const char* GetApplicationOriginalPackageName()
	{
		return g_Loader.ms_originalPackageName;
	}

	// Returns the pointer to initial directory
	F92_LA_API const char* GetInitialDirectoryPath()
	{
		return g_Loader.ms_InitialDirectory;
	}

	// Returns the pointer to root directory
	F92_LA_API const char* GetStorageRootDirectoryPath()
	{
		return g_Loader.ms_StorageRootDirectory;
	}

	// Returns the pointer to storage directory
	F92_LA_API const char* GetStorageRootBaseDirectoryPath()
	{
		return g_Loader.ms_StorageRootBaseDirectory;
	}

	// Returns the pointer to cache directory
	F92_LA_API const char* GetCacheDirectoryPath()
	{
		return g_Loader.ms_CacheDirectory;
	}

	// Returns jobject of main activity during launch
	F92_LA_API jobject GetMainActivityDuringLaunch()
	{
		return g_Loader.ms_mainActivityDuringLaunch;
	}
}
#endif
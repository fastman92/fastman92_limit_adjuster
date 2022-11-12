/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

// dllmain.cpp : Defines the entry point for the DLL application.
#include "FormattedOutput.h"
#include "LimitAdjuster.h"
#include "MemoryAllocation.h"
#include "ProjectConstants.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

#include <string.h>

#ifdef IS_PLATFORM_ANDROID
#include <android/log.h>

#include <dlfcn.h>

#include "../../../fastman92 plugin loader/ForOtherProjects/Exports.h"
#endif

// Visual leak detector
#if defined(IS_PLATFORM_WIN) && !defined(NDEBUG)
#include <vld.h>
#endif

// Enable/disable the FLA

const bool bEnableTheFLA💥 = true;

// Enables the message box, works only if development INI is enabled.
const bool EnableDevMessageBox = false;

// Start params
tLimitAdjusterStartParams startParams;

// Windows platform
#ifdef IS_PLATFORM_WIN
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	if (!bEnableTheFLA💥)
		return TRUE;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			if (PROJECT_USE_DEVELOPMENT_INI && EnableDevMessageBox)
				printf_MessageBox("Stop before");

			memset(&startParams, NULL, sizeof(startParams));
			startParams.applicationLibHandle = (void*)GetModuleHandle(NULL);
			startParams.applicationLibBaseAddress = startParams.applicationLibHandle;
			startParams.pluginHandle = hModule;
			
			g_LimitAdjuster.ProcessFLAaction(eFLA_actionToDo::Start, &startParams);
			
			if (PROJECT_USE_DEVELOPMENT_INI && EnableDevMessageBox)
				printf_MessageBox("Stop after, process ID: %d Thread ID: %d",
					GetCurrentProcessId(),
					GetCurrentThreadId()
				);
			
			break;
		}
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		g_LimitAdjuster.ProcessFLAaction(eFLA_actionToDo::Stop);
		break;
	}

	return TRUE;
}
#endif

// Android platform
#ifdef IS_PLATFORM_ANDROID
extern "C"
{
	// refers to type: tOnPluginLoad
	// which is defined in the plugin loader
	bool JNIEXPORT OnPluginLoadWhenAppIsInitialized(
		tPluginStartParams* pPluginStartParams
	)
	{
		if (!bEnableTheFLA💥)
			return true;

		#ifdef PROJECT_USE_DEVELOPMENT_INI
		OutputFormattedDebugString("--------------------------------------");
		OutputFormattedDebugString("--------------------------------------");
		OutputFormattedDebugString("Starting %s", PROJECT_FULL_NAME);
		#endif

		memset(&startParams, NULL, sizeof(startParams));
		startParams.jvm = pPluginStartParams->jvm;
		startParams.second_param_reserved = pPluginStartParams->second_param_reserved;
		startParams.pluginHandle = pPluginStartParams->pluginHandle;
		startParams.pluginLibraryPath = pPluginStartParams->pluginLibraryPath;

		startParams.applicationLibIdentifier = pPluginStartParams->applicationLibIdentifierStr;
		startParams.applicationLibBaseAddress = pPluginStartParams->applicationLibBaseAddress;
		startParams.applicationLibHandle = pPluginStartParams->applicationLibHandle;
		
		g_LimitAdjuster.ProcessFLAaction(eFLA_actionToDo::Start, &startParams);

		/*
		LOGI("OnGameLibraryLoad! Path: %s Plugin handle: 0x%X Application base: 0x%X Identifier: 0x%08X",
			libraryPath,
			(unsigned int)pluginHandle,
			(unsigned int)applicationLibBaseAddress,
			applicationLibIdentifier
		);
		*/

		return true;
	}

	#if FALSE
	bool JNIEXPORT OnPluginUnload()
	{
		if (bEnableTheFLA💥)
			g_LimitAdjuster.ProcessFLAaction(eFLA_actionToDo::Stop);

		return true;
	}
	#endif
}
#endif
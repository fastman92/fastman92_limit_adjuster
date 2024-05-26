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

#include "../../../fastman92 plugin loader/ForOtherProjects/PluginLoaderExports.h"
#endif

// Visual leak detector
#if defined(IS_PLATFORM_WIN) && !defined(NDEBUG)
#include <vld.h>
#endif

// Enable/disable the FLArr

const bool bEnableTheFLA💥 = true;

// Enables the message box, works only if development INI is enabled.
const bool EnableDevMessageBox = true;

// Start params
tLimitAdjusterStartParams startParams;

// Windows platform
#ifdef IS_PLATFORM_WIN
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	/*
	if(1)
	{
		PVOID USBXHCI_base = hModule;
		PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)hModule;
		PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((uintptr_t)(dosHeader)+(dosHeader->e_lfanew));

		//Identify for valid PE file  
		if (ntHeader->Signature == IMAGE_NT_SIGNATURE)
		{
			
			PIMAGE_OPTIONAL_HEADER opHeader = &ntHeader->OptionalHeader;

			IMAGE_DATA_DIRECTORY ImportsDirectory = opHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];

			IMAGE_IMPORT_DESCRIPTOR* pImportDescriptor = (IMAGE_IMPORT_DESCRIPTOR*)((char*)USBXHCI_base + ImportsDirectory.VirtualAddress);

			
			while (pImportDescriptor->OriginalFirstThunk)
			{
				
				//LPCSTR LibraryName = (char*)USBXHCI_base + pImportDescriptor->Name;
				//printf_MessageBox("herhe: %s", LibraryName);

				PIMAGE_THUNK_DATA pOriginalFirstThunk = (PIMAGE_THUNK_DATA)((char*)USBXHCI_base + pImportDescriptor->OriginalFirstThunk);
				PIMAGE_THUNK_DATA pFirstThunk = (PIMAGE_THUNK_DATA)((char*)USBXHCI_base + pImportDescriptor->FirstThunk);

				PIMAGE_THUNK_DATA pOriginalThunk;
				PIMAGE_THUNK_DATA pThunk;

				unsigned int i = 0;

				while (1)
				{
					pOriginalThunk = pOriginalFirstThunk + i;
					pThunk = pFirstThunk + i;

					if (!pOriginalThunk->u1.AddressOfData)
						break;

					__asm
					{
					}

					PIMAGE_IMPORT_BY_NAME imageImportByName = (PIMAGE_IMPORT_BY_NAME)((char*)USBXHCI_base + pOriginalThunk->u1.AddressOfData);
					LPCSTR functionName = (LPCSTR)&imageImportByName->Name;
					PVOID* pFunctionAddress = (PVOID*)&pThunk->u1.Function;

					printf_MessageBox("function: %s ptr: 0x%X \r\n", functionName, *pFunctionAddress);

					i++;
				}

				pImportDescriptor++;
			}
		}
	}
	
	printf_MessageBox("Finished");
	ExitProcess(0);
	*/

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
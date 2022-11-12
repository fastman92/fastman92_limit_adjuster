/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

#ifdef IS_PLATFORM_WIN
#include <Windows.h>
#endif

enum ePlugin
{
	PLUGIN_UNDEFINED,

	PLUGIN_CLEO_LIBRARY,
	PLUGIN_IMVEHFT,
	PLUGIN_SA_LOD_LIGHTS_3_2,
	PLUGIN_SILENT_PATCH,
	PLUGIN_V_HUD_0_925_DK22PAC,
	
	PLUGIN_TEST
};

typedef void (*tPluginPatchFunc)(void* current_base_address);

// Struct with info needed to recognize a DLL plugin.
struct tPatchedPluginInfo
{
	ePlugin plugin;
	bool bEnablePatch;

	const wchar_t* filename;
	const unsigned int filesize;

	tPluginPatchFunc func;
};

class CThePluginPatches : public CLimitAdjusterModule
{
public:
	// Array to identify plugins
	static tPatchedPluginInfo PatchInfoArray[];

	//// PATCHING FUNCTIONS ////	

#ifdef IS_PLATFORM_WIN_X86
	static void Patch_V_HUD_DK22Pac_0_925(void* current_base_address);

	// Patch CLEO library 4.3.16
	static void Patch_CLEO_library_4_3_16(_In_  HINSTANCE hinstDLL);
	
	static void Patch_ImVehFt_2_2_1(_In_  HINSTANCE hinstDLL);

	static void Patch_SALodLights_3_2(_In_  HINSTANCE hinstDLL);

	static void Patch_SilentPatch_227840(void* current_base_address);

	static void Patch_TestBeforeApplicationStarts(_In_  HINSTANCE hinstDLL);
#endif
	////////////////////////////

	#ifdef IS_PLATFORM_WIN
	// Apply patches
	static void ApplyPatches(_In_  HINSTANCE hinstDLL);
	#endif

	// Registers patcher
	static void RegisterPatcher();

	// Do CLEO loading
	static void DoCLEOloading(bool bEnableCLEOpatch);

	// Initialize
	virtual void Initialise() {}

	// Shutdown
	virtual void Shutdown() {}
};

extern CThePluginPatches g_pluginPatches;
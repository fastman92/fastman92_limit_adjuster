/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CThePluginPatches.h"

CThePluginPatches g_pluginPatches;

#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/CPatch.h"
#include "../Core/LimitAdjuster.h"

#include "MapLimits.h"
#include "RadarBlipSpriteFilenameLoader.h"

#include <fileIO.h>

using namespace Game;

#ifdef IS_PLATFORM_WIN_X86
#include "FileIDlimit.h"
#include "HandlingCfgLimits.h"
#include "OtherLimits.h"

#include "../Core/ProjectConstants.h"

#include "../GameStructures/Rockstar Games/CModelInfo.h"

#include <MemoryAddressCalculator\CMemoryAddressCalculator.h>

#include <DllTricks\DllTricks.h>

#include <Windows.h>

#include "../detours/detours.h"
#pragma comment(lib, "Source files/detours/lib.X86/detours.lib")

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

/*
ntdll.dll:7795998C     callDllMain proc near
ntdll.dll:7795998C
ntdll.dll:7795998C     arg_0= dword ptr  8
ntdll.dll:7795998C     arg_4= dword ptr  0Ch
ntdll.dll:7795998C     arg_8= dword ptr  10h
ntdll.dll:7795998C     arg_C= dword ptr  14h
*/



typedef bool (WINAPI *tDllMain)(  _In_  HINSTANCE hinstDLL,
  _In_  DWORD fdwReason,
  _In_  LPVOID lpvReserved);

typedef bool (WINAPI *tCallDllMain)( tDllMain* pDllMain,
	_In_  HINSTANCE hinstDLL,
  _In_  DWORD fdwReason,
  _In_  LPVOID lpvReserved);

static bool (WINAPI *RealCallDllMain)( tDllMain* pDllMain,
	_In_  HINSTANCE hinstDLL,
  _In_  DWORD fdwReason,
  _In_  LPVOID lpvReserved);

// The root of patches
bool WINAPI DetouredCallDllMain( tDllMain* pDllMain,
	_In_  HINSTANCE hinstDLL,
  _In_  DWORD fdwReason,
  _In_  LPVOID lpvReserved)
{
	if(fdwReason == DLL_PROCESS_ATTACH)
		CThePluginPatches::ApplyPatches(hinstDLL);

	bool result = RealCallDllMain(pDllMain, hinstDLL, fdwReason, lpvReserved);

	return result;
}

// Array to identify plugins
tPatchedPluginInfo CThePluginPatches::PatchInfoArray[] =
{
	// {	ePlugin plugin, bEnablePatch, const char* filename, const unsigned int filesize, tPluginPatchFunc func
	
#ifdef IS_PLATFORM_WIN_X86
	{PLUGIN_V_HUD_0_925_DK22PAC, false, L"V_HUD_by_DK22Pac.asi", 354816, &Patch_V_HUD_DK22Pac_0_925},
	// {PLUGIN_CLEO_LIBRARY, false, L"CLEO.asi", 264704, &Patch_CLEO_library_4_3_16},
	// {PLUGIN_SA_LOD_LIGHTS_3_2, false, L"SALodLights.asi", 177664, &Patch_SALodLights_3_2},
#if PROJECT_USE_DEVELOPMENT_INI
	// { PLUGIN_SILENT_PATCH, false, L"SilentPatchSA.asi", 227840, &Patch_SilentPatch_227840 },
#endif
	
#endif


	// {PLUGIN_IMVEHFT, false, L"ImVehFt.asi", 247296, &Patch_ImVehFt_2_2_1},

	{PLUGIN_UNDEFINED, false, L"", 0, NULL}
};

// Apply patches
void CThePluginPatches::ApplyPatches(_In_  HINSTANCE hinstDLL)
{
	wchar_t fullPath[MAX_PATH];
	wchar_t* filename;

	GetModuleFileNameW(hinstDLL, fullPath, _countof(fullPath));
	filename = PathFindFileNameW(fullPath);
	
	for(unsigned i = 0; i < _countof(PatchInfoArray); i++)
	{
		tPatchedPluginInfo* pPatchInfo = &PatchInfoArray[i];
		
		if (pPatchInfo->bEnablePatch
			&& !_wcsicmp(pPatchInfo->filename, filename)
			&& GetFileSize(fullPath) == pPatchInfo->filesize
			)
		{
			pPatchInfo -> func(hinstDLL);
			CGenericLogStorage::SaveWorkBuffer();
		}
	}
}

// Registers patcher
void CThePluginPatches::RegisterPatcher()
{
//	printf_MessageBox("what calls DLL main: 0x%X", GetAddressToWhatCallsDllMain());

	RealCallDllMain = (tCallDllMain)CTheDllTricks::GetAddressToCallDllMain();

	if(!RealCallDllMain)
	{
		CGenericLogStorage::SaveFormattedTextLn("Can't find address of CallDllMain, CThePluginPatches won't work!"); 
		CGenericLogStorage::WriteLineSeparator();
		return;
	}

	// printf_MessageBox("Address of CallDllMain: 0x%X", RealCallDllMain);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	DetourAttach(&(PVOID&)RealCallDllMain, DetouredCallDllMain);
	
	DetourTransactionCommit();
		
	//////////// debug code ///////////
	for(unsigned i = 0; i < _countof(PatchInfoArray); i++)
	{
		tPatchedPluginInfo* pPatchInfo = &PatchInfoArray[i];
		pPatchInfo->bEnablePatch = true;
	}
	
	CGenericLogStorage::SaveTextLn("CThePluginPatches::RegisterPatcher executed.");
	CGenericLogStorage::WriteLineSeparator();
};

static HINSTANCE CLEO_4_3_16_imageBase;

/*
NAKED void patch_SCM_command_0AB7_23B68_handlingLimit()
{		
	__asm
	{
		mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_fileIDlimits, FileIDlimit, CModelInfo__ms_modelInfoPtrs);
		mov eax, [eax + ecx * 4];	// get a pointer to CModelCars

		movzx   ecx, word ptr[eax + 4Ah];	// [eax+CModelCars.handlingIndex]

		imul ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, m_sizeof_tHandlingData);
		add edx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, ms_aStandardHandling_offset);
		movzx eax, byte ptr	[ecx + edx + Game_GTASA::tHandlingData::transmissionData + Game_GTASA::cTransmission::m_nNumberOfGears]

		mov ecx, [CLEO_4_3_16_imageBase];
		add ecx, 0x23B76;
		jmp ecx;
	}
}
*/

class CPatchFind_Patch_V_HUD
{
public:
	// Marks region for coordinates
	void MarkRegionsForCoors(CVector pos, float radius)
	{
		memset(g_mapLimits.ToBeStreamed.ptr, 1, g_mapLimits.iTotalNumberOfPathIndices);
	}
};

static uint32_t TXD_BASE_ID;

// patch for 0x10016B12
static uintptr_t Address_sub_10016AD0_10016B19 = 0;

static NAKED void patch_sub_10016AD0_10016B12()
{
	__asm
	{
		mov ecx, dword ptr[TXD_BASE_ID];
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_sub_10016AD0_10016B19);
	}
}

static uintptr_t Address_sub_10016AD0_10016B38 = 0;

static NAKED void patch_sub_10016AD0_10016B31()
{
	__asm
	{
		mov ecx, dword ptr[TXD_BASE_ID];
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_sub_10016AD0_10016B38);
	}
}

void CThePluginPatches::Patch_V_HUD_DK22Pac_0_925(void* current_base_address)
{
	MAKE_VAR_GAME_VERSION();

	if (!CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		return;

	CMemoryAddressCalculator memCalc;
	memCalc.Initialize(0x10000000, (uintptr_t)current_base_address);

	CPatch::EnterNewLevel();

	// sub_1001C6B0
	CPatch::NOPinstructions(memCalc.GetCurrentVAbyPreferedVA(0x1001C6BF), 0x1001C6FB - 0x1001C6BF);
	CPatch::NOPinstructions(memCalc.GetCurrentVAbyPreferedVA(0x1001C6FF), 2);

	// sub_10016AD0
	CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x10016ADE + 1), g_mapLimits.gRadarTextures.ptr);

	unsigned int numberOfRadarTilesPerOneDimension = g_mapLimits.ms_radarMapSize / g_mapLimits.ms_radarBlockSize;
	const int totalNumberOfTiles = numberOfRadarTilesPerOneDimension * numberOfRadarTilesPerOneDimension;

	CPatch::PatchUINT8(memCalc.GetCurrentVAbyPreferedVA(0x10016B4F + 2), numberOfRadarTilesPerOneDimension);
	CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x10016B55 + 2), g_mapLimits.gRadarTextures.ptr + totalNumberOfTiles);

	TXD_BASE_ID = g_fileIDlimits.GetBaseID(GENERAL_FILE_TYPE_TEXTURE_ARCHIVE);

	Address_sub_10016AD0_10016B19 = memCalc.GetCurrentVAbyPreferedVA(0x10016B19);
	CPatch::RedirectCode(memCalc.GetCurrentVAbyPreferedVA(0x10016B12), &patch_sub_10016AD0_10016B12);

	Address_sub_10016AD0_10016B38 = memCalc.GetCurrentVAbyPreferedVA(0x10016B38);
	CPatch::RedirectCode(memCalc.GetCurrentVAbyPreferedVA(0x10016B31), &patch_sub_10016AD0_10016B31);

	// CPatchFind::MarkRegionsForCoors
	CPatch::RedirectMethod(g_mCalc.GetCurrentVAbyPreferedVA(0x44DB60), &CPatchFind_Patch_V_HUD::MarkRegionsForCoors);

	// sub_10016460
	CPatch::PatchPointer(
		memCalc.GetCurrentVAbyPreferedVA(0x100165F7 + 3),
		g_RadarBlipSpriteFilenameLoader.CRadar__RadarBlipSprites.gta_sa
	);

	// ThePaths
	{
		auto ThePaths = g_mapLimits.ThePaths.gta_sa;

		CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x1001D54C + 1), ThePaths);	// mov     ecx, 96F050h	; sub_1001D2E0
		CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x1001D5D4 + 1), ThePaths);	// mov     ecx, 96F050h	; sub_1001D2E0
		CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x1001D68D + 1), ThePaths);	// mov     ecx, 96F050h	; sub_1001D2E0
		CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x1001D709 + 1), ThePaths);	// mov     ecx, 96F050h	; sub_1001D2E0
		CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x1001D72B + 1), ThePaths);	// mov     ecx, 96F050h	; sub_1001D2E0
		CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x1001D96F + 1), ThePaths);	// mov     ecx, 96F050h	; sub_1001D7B0
		CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x1001D9F6 + 1), ThePaths);	// mov     ecx, 96F050h	; sub_1001D7B0
		CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x1001DA79 + 1), ThePaths);	// mov     ecx, 96F050h	; sub_1001D7B0
		CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x1001DAF5 + 1), ThePaths);	// mov     ecx, 96F050h	; sub_1001D7B0
		CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x1001DB17 + 1), ThePaths);	// mov     ecx, 96F050h	; sub_1001D7B0
	}

	// sub_10016A00
	auto CRadar__ms_RadarTrace = g_otherLimits.CRadar__ms_RadarTrace.gta_sa;

	CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x10016A12 + 3), &CRadar__ms_RadarTrace->_RadarMode_or_EntityType);	// mov     al, [esi+esi+0BA8716h]	; sub_10016A00
	CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x10016A2D + 2), &CRadar__ms_RadarTrace->Pos);	// lea     eax, [esi+0BA86F8h]	; sub_10016A00
	CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x10016A3E + 2), &CRadar__ms_RadarTrace->_Flag);	// mov     al, [esi+0BA8715h]	; sub_10016A00

	CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x10016A57 + 3), (char*)((uintptr_t)CRadar__ms_RadarTrace / 8));	// mov     al, [esi+0BA8715h]	; sub_10016A00

	CGenericLogStorage::SaveFormattedTextLn("CThePatches: GTA V HUD by DK22Pac v0.925 has been detected and patched!");

	CPatch::LeaveThisLevel();
}

// Patch CLEO library 4.3.16
void CThePluginPatches::Patch_CLEO_library_4_3_16(_In_  HINSTANCE hinstDLL)
{
	CPatch::EnterNewLevelAndDisableDebugState();

	/*
	DWORD imageBase = (DWORD)hinstDLL;
	CLEO_4_3_16_imageBase = hinstDLL;

	// Game_GTASA::FileIDlimit::CModelInfo__ms_modelInfoPtrs
	CPatch::PatchPointer(imageBase + 0x3D990, g_fileIDlimits.CModelInfo__ms_modelInfoPtrs.gta_sa);

	// GTA SA handling.cfg
	CPatch::PatchPointer(
		imageBase + 0x3D968,
		g_handlingCfgLimits.Get_mod_HandlingManager()
		);

	CPatch::RedirectCode(
		imageBase + 0x23B68,
		&patch_SCM_command_0AB7_23B68_handlingLimit
		);

	*/
	CGenericLogStorage::SaveFormattedTextLn("CThePatches: CLEO library 4.3.16 has been detected and patched!");

	CPatch::LeaveThisLevel();
}

// Apply patches for ImVehFt_2_2_1
void CThePluginPatches::Patch_ImVehFt_2_2_1(_In_  HINSTANCE hinstDLL)
{
	CPatch::EnterNewLevelAndDisableDebugState();

	DWORD imageBase = (DWORD)hinstDLL;

	Game_GTASA::CBaseModelInfo** CModelInfo__ms_modelInfoPtrs = g_fileIDlimits.CModelInfo__ms_modelInfoPtrs.gta_sa;

	CPatch::PatchPointer(imageBase + 0x1366 + 3, CModelInfo__ms_modelInfoPtrs);
	CPatch::PatchPointer(imageBase + 0x3418 + 3, CModelInfo__ms_modelInfoPtrs);
	CPatch::PatchPointer(imageBase + 0x3670 + 3, CModelInfo__ms_modelInfoPtrs);
	CPatch::PatchPointer(imageBase + 0x3759C, CModelInfo__ms_modelInfoPtrs);

	CGenericLogStorage::SaveFormattedTextLn("CThePatches: ImVehFt 2.2.1 has been detected and patched!");	

	CPatch::LeaveThisLevel();
}

NAKED void Patch_SALodLights_3_2_100051A9()
{
	__asm
	{
		mov     edi, eax;
		mov[esi + Game_GTASA::CBaseModelInfo::m_fDrawDistance], ecx;

		push 0x5B3F51;
		retn;
	}
}


NAKED void Patch_SALodLights_3_2_100051DF()
{
	__asm
	{
		mov[esi + Game_GTASA::CBaseModelInfo::m_fDrawDistance], edx;

		mov eax, 0x53CF30;
		call eax;

		push 0x5B3DB5;
		retn;
	}
}

void CThePluginPatches::Patch_SALodLights_3_2(_In_  HINSTANCE hinstDLL)
{
	CMemoryAddressCalculator memCalc;
	memCalc.Initialize(0x10000000, (uintptr_t)hinstDLL);
	
	CPatch::PatchUINT32(memCalc.GetCurrentVAbyPreferedVA(0x10006061 + 1), 0x5B3F4C);
	CPatch::PatchUINT32(memCalc.GetCurrentVAbyPreferedVA(0x10006066 + 2), memCalc.GetCurrentVAbyPreferedVA(0x10005198));
	CPatch::RedirectCode(memCalc.GetCurrentVAbyPreferedVA(0x100051A9), &Patch_SALodLights_3_2_100051A9);


	CPatch::PatchUINT32(memCalc.GetCurrentVAbyPreferedVA(0x10006115 + 2), memCalc.GetCurrentVAbyPreferedVA(0x100051C7));
	CPatch::RedirectCode(memCalc.GetCurrentVAbyPreferedVA(0x100051DF), &Patch_SALodLights_3_2_100051DF);
	CPatch::PatchPointer(memCalc.GetCurrentVAbyPreferedVA(0x10006123 + 2), (char*)0x5B3DAC);

	// printf_MessageBox("address: 0x%X", memCalc.GetCurrentVAbyPreferedVA(0x10006066));

	CGenericLogStorage::SaveFormattedTextLn("CThePatches: SALodLights 3.2 has been detected and patched!");
}

void CThePluginPatches::Patch_SilentPatch_227840(void* current_base_address)
{
	CMemoryAddressCalculator memCalc;
	memCalc.Initialize(0x10000000, (uintptr_t)current_base_address);
	
	if(g_otherLimits.bIsVehicleColorIDextended)
		CPatch::NOPinstructions(
			memCalc.GetCurrentVAbyPreferedVA(0x10009531),
			0x10009545 - 0x10009531
		);	// disable CObject::Render patch, which makes use of Vehicle colours
	
	/*
	CPatch::RedirectCode(
		memCalc.GetCurrentVAbyPreferedVA(0x1000AFC6),
		memCalc.GetCurrentVAbyPreferedVA(0x1000B0C1)
	);	// disable multisampling patch, which decreases the FPS		
	*/
	
	///////////////

#if FALSE
	/*
	CPatch::PatchUINT8(
	memCalc.GetCurrentVAbyPreferedVA(0x1000A4F0),
	0xC3
	);
	*/

	CPatch::NOPinstructions(
		memCalc.GetCurrentVAbyPreferedVA(0x1000A56F),
		3
	);	// disable executeInWinMain_HOODLUM patch


	{
		CPatch::RedirectCode(
			memCalc.GetCurrentVAbyPreferedVA(0x1000A4FE),
			memCalc.GetCurrentVAbyPreferedVA(0x1000A7F2)
		);

		CPatch::NOPinstructions(
			memCalc.GetCurrentVAbyPreferedVA(0x1000A7F5),
			6
		);
	}

	/*
	CPatch::RedirectCode(
		memCalc.GetCurrentVAbyPreferedVA(0x1000A7F5),
		memCalc.GetCurrentVAbyPreferedVA(0x1000B37F)
	);
	*/
	
	/*
	CPatch::RedirectCode(
		memCalc.GetCurrentVAbyPreferedVA(0x1000A7FB),
		
		memCalc.GetCurrentVAbyPreferedVA(0x1000B0C1)	// line 456

		// memCalc.GetCurrentVAbyPreferedVA(0x1000AFC6) // line 441
	);	// multisampling patches, TODO
	*/
	
	// end
	CPatch::RedirectCode(
		memCalc.GetCurrentVAbyPreferedVA(0x1000B382),
		memCalc.GetCurrentVAbyPreferedVA(0x1000B9BB)
	);
#endif

	CGenericLogStorage::SaveFormattedTextLn("CThePatches: SilentPatch with filesize 227840 has been detected and patched!");
}

void CThePluginPatches::Patch_TestBeforeApplicationStarts(_In_  HINSTANCE hinstDLL)
{
	const char* str = "New string!";

	DWORD imageBase = (DWORD)hinstDLL;
	CPatch::PatchPointer(imageBase + 0x11FEE + 1, (char*)str);

	CGenericLogStorage::SaveFormattedTextLn("CThePatches: TestBeforeApplicationStarts 1.0 has been detected and patched!");
}
#endif

#if IS_PLATFORM_ANDROID_ARM32
bool CLEOloadingImplemented = false;
#else
bool CLEOloadingImplemented = false;
#endif

// Game
enum class eCLEO_game : int
{
	GAME_GTA_III,
	GAME_GTA_VC,
	GAME_GTA_SA
};

// GTA III uses 2 digits
// GTA VC and GTA SA use 3 digits
enum class eCLEO_gameVersion : int
{
	GAME_VERSION_UNDEFINED,

	///////////////////////////
	// added by Alexander Blade
	
	GAME_VERSION_GTA_III_1_4,
	GAME_VERSION_GTA_VC_1_03,
	GAME_VERSION_GTA_SA_1_00,
	GAME_VERSION_GTA_SA_1_02 = 5,
	GAME_VERSION_GTA_SA_1_03,
	GAME_VERSION_GTA_SA_1_05,
	GAME_VERSION_GTA_SA_1_06,
	GAME_VERSION_GTA_SA_1_05_GER,
	GAME_VERSION_GTA_SA_1_07,
	GAME_VERSION_GTA_III_1_6,
	GAME_VERSION_GTA_VC_1_06,
	GAME_VERSION_GTA_SA_1_08,

	///////////////////////////
	// added by fastman92
	GAME_VERSION_GTA_III_1_8,
	GAME_VERSION_GTA_VC_1_07,
	GAME_VERSION_GTA_VC_1_09,
	GAME_VERSION_GTA_SA_2_00
};

static_assert((int)eCLEO_gameVersion::GAME_VERSION_GTA_III_1_8 == 14, "Wrong enum value");

#if IS_PLATFORM_ANDROID_ARMEABI_V7A
extern "C" {
	eCLEO_game* cleo_game;
	eCLEO_gameVersion* cleo_gameVersion;
	uintptr_t* cleo_gameLibBaseAddress;
	void** cleo_gameLibHandle;

	bool __cdecl IdentifyGameVersion()
	{
		*cleo_gameLibHandle = g_LimitAdjuster.hModule_of_game.linux_os;

		uintptr_t GetJavaJM_address = (uintptr_t)dlsym(*cleo_gameLibHandle, "GetJavaVM");

		uintptr_t crc32_address = (uintptr_t)dlsym(*cleo_gameLibHandle, "crc32");

		uintptr_t GxtCharToAscii_address = (uintptr_t)dlsym(*cleo_gameLibHandle, "_Z14GxtCharToAsciiPth");

		////
		bool found_GetJavaJM = GetJavaJM_address != 0;

		bool found_GetJavaJM_and_crc32 = found_GetJavaJM && crc32_address != 0;

		if (found_GetJavaJM_and_crc32)
		{
			if (crc32_address - GetJavaJM_address == 0x19586C)
			{
				*cleo_game = eCLEO_game::GAME_GTA_III;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_III_1_4;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 0x1AA901;
				return true;
			}
			else if (crc32_address - GetJavaJM_address == -0x5090C)
			{
				*cleo_game = eCLEO_game::GAME_GTA_VC;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_VC_1_03;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 0x3100D5;
				return true;
			}
			else if (crc32_address - GetJavaJM_address == 1559820)
			{
				*cleo_game = eCLEO_game::GAME_GTA_III;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_III_1_6;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 895573;
				return true;
			}
			else if (crc32_address - GetJavaJM_address == -356240)
			{
				*cleo_game = eCLEO_game::GAME_GTA_VC;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_VC_1_06;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 3131517;
				return true;
			}

			// added by the FLA
			else if (crc32_address - GetJavaJM_address == 0x1EF778)
			{
				*cleo_game = eCLEO_game::GAME_GTA_III;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_III_1_8;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 0x104269;
				return true;
			}
			else if (crc32_address - GetJavaJM_address == -0x5526C)
			{
				*cleo_game = eCLEO_game::GAME_GTA_VC;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_VC_1_09;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 0x31AF31;
				return true;
			}
		}

		bool found_GetJavaJM_and_GxtCharToAscii = found_GetJavaJM && GxtCharToAscii_address != 0;

		if (found_GetJavaJM_and_GxtCharToAscii)
		{
			if (GxtCharToAscii_address - GetJavaJM_address == 0x278EC8)
			{
				*cleo_game = eCLEO_game::GAME_GTA_SA;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_00;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 2199201;
				return true;
			}
			else if (GxtCharToAscii_address - GetJavaJM_address == 0x279020)
			{
				*cleo_game = eCLEO_game::GAME_GTA_SA;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_02;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 2199081;
				return true;
			}
			else if (GxtCharToAscii_address - GetJavaJM_address == 0x278E58)
			{
				*cleo_game = eCLEO_game::GAME_GTA_SA;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_03;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 2199001;
				return true;
			}
			else if (GxtCharToAscii_address - GetJavaJM_address == 0x27C784)
			{
				*cleo_game = eCLEO_game::GAME_GTA_SA;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_05;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 2180757;
				return true;
			}
			else if (GxtCharToAscii_address - GetJavaJM_address == 0x297BDC)
			{
				*cleo_game = eCLEO_game::GAME_GTA_SA;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_06;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 2347869;
				return true;
			}
			else if (GxtCharToAscii_address - GetJavaJM_address == 0x297C4C)
			{
				*cleo_game = eCLEO_game::GAME_GTA_SA;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_05_GER;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 2347917;
				return true;
			}
			else if (GxtCharToAscii_address - GetJavaJM_address == 0x297DE4)
			{
				*cleo_game = eCLEO_game::GAME_GTA_SA;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_07;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 2348541;
				return true;
			}
			else if (GxtCharToAscii_address - GetJavaJM_address == 0x297DF4)
			{
				*cleo_game = eCLEO_game::GAME_GTA_SA;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_08;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 0x23B3B5;
				return true;
			}
			// added by the FLA
			else if (GxtCharToAscii_address - GetJavaJM_address == 0x2DCEA8)
			{
				*cleo_game = eCLEO_game::GAME_GTA_SA;
				*cleo_gameVersion = eCLEO_gameVersion::GAME_VERSION_GTA_SA_2_00;
				*cleo_gameLibBaseAddress = GetJavaJM_address - 0x2707F1;
				return true;
			}
		}

		return *cleo_gameVersion != eCLEO_gameVersion::GAME_VERSION_UNDEFINED;
	}

	struct tGameVersionParams
	{
		uintptr_t callToCRunningScript__ProcessOneCommand_1;
		uintptr_t callToCRunningScript__ProcessOneCommand_2;
	};

	typedef void(*type_CLEO_log)(const char* format, ...);

	type_CLEO_log CLEO_log;

	void CLEO_selectGameVersion(tGameVersionParams* pParams)
	{
		memset(pParams, 0, sizeof(*pParams));

		switch (*cleo_gameVersion)
		{
		case eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_08:
			CLEO_log("GTASA v1.08");
			break;
		case eCLEO_gameVersion::GAME_VERSION_GTA_III_1_4:
			CLEO_log("GTA3 v1.4");
			pParams->callToCRunningScript__ProcessOneCommand_1 = *cleo_gameLibBaseAddress + 0x20BAD8;
			break;
		case eCLEO_gameVersion::GAME_VERSION_GTA_VC_1_03:
			CLEO_log("GTAVC v1.03");
			pParams->callToCRunningScript__ProcessOneCommand_1 = *cleo_gameLibBaseAddress + 0x105320;
			pParams->callToCRunningScript__ProcessOneCommand_2 = *cleo_gameLibBaseAddress + 0x10532A;			
			break;
		case eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_00:
			CLEO_log("GTASA v1.00");
			break;
		case eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_02:
			CLEO_log("GTASA v1.02");
			break;
		case eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_03:
			CLEO_log("GTASA v1.03");
			break;
		case eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_05:
			CLEO_log("GTASA v1.05");
			break;
		case eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_06:
			CLEO_log("GTASA v1.06");
			break;
		case eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_05_GER:
			CLEO_log("GTASA v1.0.5 GER");
			break;
		case eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_07:
			CLEO_log("GTASA v1.07");
			break;
		case eCLEO_gameVersion::GAME_VERSION_GTA_III_1_6:
			CLEO_log("GTA3 v1.6");
			pParams->callToCRunningScript__ProcessOneCommand_1 = *cleo_gameLibBaseAddress + 0x135314;
			break;
		case eCLEO_gameVersion::GAME_VERSION_GTA_VC_1_06:
			CLEO_log("GTAVC v1.06");
			pParams->callToCRunningScript__ProcessOneCommand_1 = *cleo_gameLibBaseAddress + 0x1061EC;
			pParams->callToCRunningScript__ProcessOneCommand_2 = *cleo_gameLibBaseAddress + 0x1061F6;			
			break;

			// added by the FLA
		case eCLEO_gameVersion::GAME_VERSION_GTA_SA_2_00:
			CLEO_log("GTASA v2.00");
			break;
			
		case eCLEO_gameVersion::GAME_VERSION_GTA_III_1_8:
			CLEO_log("GTA3 v1.8");
			pParams->callToCRunningScript__ProcessOneCommand_1 = *cleo_gameLibBaseAddress + 0x173660;
			break;

		case eCLEO_gameVersion::GAME_VERSION_GTA_VC_1_09:
			CLEO_log("GTAVC v1.09");
			pParams->callToCRunningScript__ProcessOneCommand_1 = *cleo_gameLibBaseAddress + 0x10FB54;
			pParams->callToCRunningScript__ProcessOneCommand_2 = *cleo_gameLibBaseAddress + 0x10FB5E;
			break;

		default:
			break;
		}
	}

	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
	uintptr_t Address_LoadCLEO_4724;

	TARGET_THUMB NAKED void Load_CLEO_46F2()
	{
		__asm volatile
		(
			".thumb\n"
			"LDR             R2, [R4]\n"
			"STR             R2, [SP,#0x30-0x1C]\n"
			"MOV R0, SP\n"
			"BLX CLEO_selectGameVersion\n"

			"LDR R6, [SP, %c[offset_tGameVersionParams_callToCRunningScript__ProcessOneCommand_1]]\n"
			"LDR R8, [SP, %c[offset_tGameVersionParams_callToCRunningScript__ProcessOneCommand_2]]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_LoadCLEO_4724)

			::

			[offset_tGameVersionParams_callToCRunningScript__ProcessOneCommand_1]
				"i" (offsetof(tGameVersionParams, callToCRunningScript__ProcessOneCommand_1)),

			[offset_tGameVersionParams_callToCRunningScript__ProcessOneCommand_2]
		"i" (offsetof(tGameVersionParams, callToCRunningScript__ProcessOneCommand_2))			
		);
	}
	#endif

	void(__cdecl* cleo_writeMemory)(
		uintptr_t funcAddress,
		const char* data,
		unsigned int dataSize,
		bool vp
		);

	void(__cdecl* cleo_createTrampoline)(
		uintptr_t sourceAddress,
		unsigned int dataSize,
		uintptr_t targetAddress,
		void** origFunc
		);

	uintptr_t cleo_alternative_ProcessOneCommand;
	void** cleo_orig_ProcessOneCommand;
	void* cleo_orig2_ProcessOneCommand;

	uintptr_t* cleo_CTheScripts_Init;
	uintptr_t* cleo_CTheScripts_ProcessOneCommand;

	unsigned int* CTheScripts__CommandsExecuted;

	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A

	DLL_EXPORT TARGET_THUMB NAKED void cleo_GTASA_2_0_orig_ProcessOneCommand()
	{
		__asm volatile
		(
			".thumb\n"
			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R1, CTheScripts__CommandsExecuted)
			
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(cleo_orig2_ProcessOneCommand)
			);
	}
	#endif

	void Load_CLEO_createBranchesFor_CTheScripts()
	{
		if (*cleo_gameVersion == eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_06
			|| *cleo_gameVersion == eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_05_GER
			|| *cleo_gameVersion == eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_07
			|| *cleo_gameVersion == eCLEO_gameVersion::GAME_VERSION_GTA_SA_1_08)
		{
			// CTheScripts::Init
			{
				char data[] =
				{
					0xC0, 0xEF, 0x50, 0x00,	//  VMOV.I32        Q8, #0
					0xDF, 0xF8, 0x20, 0x38	// LDR.W           R3, =(_GLOBAL_OFFSET_TABLE_ - ...)
				};

				cleo_writeMemory(*cleo_CTheScripts_Init - 1, data, sizeof(data), true);
			}

			// CTheScripts::ProcessOneCommand
			{
				char data[] =
				{
					0x2D, 0xE9, 0xF0, 0x4F,	// PUSH.W          {R4-R11,LR}
					0x2E, 0x4B // LDR             R3, =(_ZN11CTheScripts16CommandsExecutedE_ptr - ...)
				};

				cleo_writeMemory(*cleo_CTheScripts_ProcessOneCommand - 1, data, sizeof(data), true);
			}

			cleo_createTrampoline(
				*cleo_CTheScripts_ProcessOneCommand,
				4,
				cleo_alternative_ProcessOneCommand,
				cleo_orig_ProcessOneCommand
			);
		}
		else if (*cleo_gameVersion == eCLEO_gameVersion::GAME_VERSION_GTA_SA_2_00)
		{
			// CTheScripts::ProcessOneCommand
			{
				
				char data[] =
				{
					0x00, 0xBF,	// NOP
					0x00, 0xBF,	// NOP
					0x00, 0xBF,	// NOP
				};

				cleo_writeMemory(*cleo_CTheScripts_ProcessOneCommand - 1, data, sizeof(data), true);
			}		

			cleo_createTrampoline(
				*cleo_CTheScripts_ProcessOneCommand,
				4,
				cleo_alternative_ProcessOneCommand,
				&cleo_orig2_ProcessOneCommand
			);

			*cleo_orig_ProcessOneCommand = (void*)&cleo_GTASA_2_0_orig_ProcessOneCommand;
		}
	}

	uintptr_t Address_LoadCLEO_4A80;

	TARGET_THUMB NAKED void Load_CLEO_4A62()
	{
		__asm volatile
		(
			".thumb\n"
			"BLX Load_CLEO_createBranchesFor_CTheScripts\n"

			"1:\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_LoadCLEO_4A80)
			);
	}

	void* Address__CRunningScript_ProcessOneCommand;
	uintptr_t Address_CRunningScript_Process_return;

	TARGET_THUMB NAKED void CRunningScript__Process_Loop()
	{
		__asm volatile
		(
			".thumb\n"
			"1:"
			"MOV             R0, R4\n"	// this

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R1, Address__CRunningScript_ProcessOneCommand)
			"BLX R1\n"

			"CMP             R0, #0\n"

			"BEQ             1b\n"

			// exit
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CRunningScript_Process_return)
			);
	}
}
#endif

// Do CLEO loading
void CThePluginPatches::DoCLEOloading(bool bEnableCLEOpatch)
{
	MAKE_VAR_GAME_VERSION();

	{
		#if IS_PLATFORM_ANDROID_ARMEABI_V7A
		// Type of Jni_Onload
		typedef jint(*type_JNI_OnLoad)(JavaVM* aVm, void* aReserved);

		char path[PATH_MAX];

		sprintf(path, "%s/libcleo.so", g_LimitAdjuster.ApplicationLibraryDirectory);

		OutputFormattedDebugString("Trying to load CLEO: %s", path);
		CGenericLogStorage::SaveFormattedTextLn("Trying to load CLEO: %s", path);

		void* pluginHandle = dlopen(path, RTLD_GLOBAL | RTLD_LAZY);

		if (!pluginHandle)
			goto failedToLoadCLEO;

		type_JNI_OnLoad pJni_OnLoad = (type_JNI_OnLoad)dlsym(pluginHandle, "JNI_OnLoad");

		if (!pJni_OnLoad)
			goto failedToLoadCLEO;

		uintptr_t stub_jni_OnLoad = (uintptr_t)dlsym(pluginHandle, "stub_JNI_OnLoad");

		// Apply patches
		if (bEnableCLEOpatch && stub_jni_OnLoad)
		{
			CMemoryAddressCalculator memCalc;
			Dl_info info;
			const char* ver_str;

			auto pluginSize = GetFileSize(path);

			if (dladdr((const void*)pJni_OnLoad, &info))
			{
				memCalc.Initialize(0, (uintptr_t)info.dli_fbase);	// set image base

				uintptr_t stub_jni_OnLoad_prefered = memCalc.GetPreferedVAbyCurrentVA(stub_jni_OnLoad);

				if (pluginSize == 83232
					&& GET_CODE_START(stub_jni_OnLoad_prefered) == 0x7ED4)
				{
					ver_str = (const char*)memCalc.GetCurrentVAbyPreferedVA(0x120AC);

					if (!strcmp(ver_str, "CLEO ANDROID (24 Mar 2015)"))
					{
						///////
						cleo_game = (eCLEO_game*)memCalc.GetCurrentVAbyPreferedVA(0x15018);
						cleo_gameVersion = (eCLEO_gameVersion*)memCalc.GetCurrentVAbyPreferedVA(0x1502C);
						cleo_gameLibBaseAddress = (uintptr_t*)memCalc.GetCurrentVAbyPreferedVA(0x15030);
						cleo_gameLibHandle = (void**)memCalc.GetCurrentVAbyPreferedVA(0x15034);

						// IdentifyGameVersion
						CPatch::RedirectCodeEx(
							INSTRUCTION_SET_THUMB,
							memCalc.GetCurrentVAbyPreferedVA(0x4EAC),
							(void*)&IdentifyGameVersion
						);

						//////
						CLEO_log = (type_CLEO_log)memCalc.GetCurrentVAbyPreferedVA(
							ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x8280)
						);

						Address_LoadCLEO_4724 = memCalc.GetCurrentVAbyPreferedVA(
							ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x4724)
						);

						CPatch::RedirectCodeEx(
							INSTRUCTION_SET_THUMB,
							memCalc.GetCurrentVAbyPreferedVA(0x46F2),
							(void*)&Load_CLEO_46F2
						);

						///
						cleo_CTheScripts_Init = (uintptr_t*)memCalc.GetCurrentVAbyPreferedVA(0x15050);
						cleo_CTheScripts_ProcessOneCommand = (uintptr_t*)memCalc.GetCurrentVAbyPreferedVA(0x15054);

						cleo_writeMemory = (decltype(cleo_writeMemory))memCalc.GetCurrentVAbyPreferedVA(
							ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x8324)
						);

						cleo_createTrampoline = (decltype(cleo_createTrampoline))memCalc.GetCurrentVAbyPreferedVA(
							ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x80B4)
						);

						// NOP createTrampoline(dword_10E04, 4, (int)alternative_ProcessOneCommand, &dword_10E2C);
						CPatch::WriteDataToUnwritableMemory(
							(void*)memCalc.GetCurrentVAbyPreferedVA(0x4AB0),
							"\x00\xbf\x00\xbf",
							4,
							true
						);

						cleo_alternative_ProcessOneCommand = memCalc.GetCurrentVAbyPreferedVA(
							ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x7E40)
						);

						cleo_orig_ProcessOneCommand = (void**)memCalc.GetCurrentVAbyPreferedVA(0x1507C);

						CTheScripts__CommandsExecuted = (unsigned int*)dlsym(
							g_LimitAdjuster.hModule_of_game.linux_os,
							"_ZN11CTheScripts16CommandsExecutedE"
						);

						Address_LoadCLEO_4A80 = memCalc.GetCurrentVAbyPreferedVA(
							ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x4A80)
						);

						CPatch::RedirectCodeEx(
							INSTRUCTION_SET_THUMB,
							memCalc.GetCurrentVAbyPreferedVA(0x4A62),
							(void*)&Load_CLEO_4A62
						);

						/// CLEO log
						CPatch::RedirectCodeEx(
							INSTRUCTION_SET_THUMB,
							memCalc.GetCurrentVAbyPreferedVA(0x8280),
							(void*)&OutputFormattedDebugString
						);

						//////////////

						OutputFormattedDebugString("Found and patched: %s", ver_str);
						CGenericLogStorage::SaveFormattedTextLn("Found and patched: %s", ver_str);
					}
					else
					{
						OutputFormattedDebugString("Unknown CLEO version. Version string checked.");
						CGenericLogStorage::SaveFormattedTextLn("Unknown CLEO version. Version string checked.");
					}
				}
				else if (pluginSize == 83232
					&& GET_CODE_START(stub_jni_OnLoad_prefered) == 0x8084)
				{
					ver_str = (const char*)memCalc.GetCurrentVAbyPreferedVA(0x122B4);

					if (!strcmp(ver_str, "CLEO ANDROID (04 May 2016)"))
					{
						///////
						cleo_game = (eCLEO_game*)memCalc.GetCurrentVAbyPreferedVA(0x1501C);
						cleo_gameVersion = (eCLEO_gameVersion*)memCalc.GetCurrentVAbyPreferedVA(0x15020);
						cleo_gameLibBaseAddress = (uintptr_t*)memCalc.GetCurrentVAbyPreferedVA(0x15024);
						cleo_gameLibHandle = (void**)memCalc.GetCurrentVAbyPreferedVA(0x15018);

						// IdentifyGameVersion
						CPatch::RedirectCodeEx(
							INSTRUCTION_SET_THUMB,
							memCalc.GetCurrentVAbyPreferedVA(0x4650),
							(void*)&IdentifyGameVersion
						);

						//////
						CLEO_log = (type_CLEO_log)memCalc.GetCurrentVAbyPreferedVA(
							ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x8430)
						);

						Address_LoadCLEO_4724 = memCalc.GetCurrentVAbyPreferedVA(
							ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x4B9C)
						);

						CPatch::RedirectCodeEx(
							INSTRUCTION_SET_THUMB,
							memCalc.GetCurrentVAbyPreferedVA(0x4B6A),
							(void*)&Load_CLEO_46F2
						);

						///
						cleo_CTheScripts_Init = (uintptr_t*)memCalc.GetCurrentVAbyPreferedVA(0x15050);
						cleo_CTheScripts_ProcessOneCommand = (uintptr_t*)memCalc.GetCurrentVAbyPreferedVA(0x15054);

						cleo_writeMemory = (decltype(cleo_writeMemory))memCalc.GetCurrentVAbyPreferedVA(
							ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x84D4)
						);

						cleo_createTrampoline = (decltype(cleo_createTrampoline))memCalc.GetCurrentVAbyPreferedVA(
							ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x8264)
						);

						// NOP createTrampoline(dword_10E04, 4, (int)alternative_ProcessOneCommand, &dword_10E2C);
						CPatch::WriteDataToUnwritableMemory(
							(void*)memCalc.GetCurrentVAbyPreferedVA(0x4F28),
							"\x00\xbf\x00\xbf",
							4,
							true
						);

						cleo_alternative_ProcessOneCommand = memCalc.GetCurrentVAbyPreferedVA(
							ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x7FF0)
						);

						cleo_orig_ProcessOneCommand = (void**)memCalc.GetCurrentVAbyPreferedVA(0x1507C);

						CTheScripts__CommandsExecuted = (unsigned int*)dlsym(
							g_LimitAdjuster.hModule_of_game.linux_os,
							"_ZN11CTheScripts16CommandsExecutedE"
						);

						Address_LoadCLEO_4A80 = memCalc.GetCurrentVAbyPreferedVA(
							ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x4EF8)
						);

						CPatch::RedirectCodeEx(
							INSTRUCTION_SET_THUMB,
							memCalc.GetCurrentVAbyPreferedVA(0x4EDA),
							(void*)&Load_CLEO_4A62
						);

						/// CLEO log
						CPatch::RedirectCodeEx(
							INSTRUCTION_SET_THUMB,
							memCalc.GetCurrentVAbyPreferedVA(0x8430),
							(void*)&OutputFormattedDebugString
						);
					}
				}
				else
				{
					OutputFormattedDebugString("Unknown CLEO version. Filesize checked.");
					CGenericLogStorage::SaveFormattedTextLn("Unknown CLEO version. Filesize checked.");
				}
			}
			else
			{
				OutputFormattedDebugString("Can't get an information about CLEO library.");
				CGenericLogStorage::SaveFormattedTextLn("Can't get an information about CLEO library.");
			}

			// Remove CRunningScript::ProcessOneCommand inlining
			if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				Address__CRunningScript_ProcessOneCommand = (void*)dlsym(
					g_LimitAdjuster.hModule_of_game.linux_os,
					"_ZN14CRunningScript17ProcessOneCommandEv"
				);

				Address_CRunningScript_Process_return = g_mCalc.GetCurrentVAbyPreferedVA(
					ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32B3B2)
				);

				CPatch::RedirectCodeEx(
					INSTRUCTION_SET_THUMB,
					g_mCalc.GetCurrentVAbyPreferedVA(0x32B34E),
					(void*)&CRunningScript__Process_Loop
				);
			}
		}

		// Execute CLEO
		pJni_OnLoad(g_LimitAdjuster.jvm, g_LimitAdjuster.second_param_reserved);

		// Show message
		OutputFormattedDebugString("CLEO loaded.");
		CGenericLogStorage::SaveTextLn("CLEO loaded");
		#endif
	}

	return;

failedToLoadCLEO:
	{
		OutputFormattedDebugString("Failed to load CLEO.");
		CGenericLogStorage::SaveTextLn("Failed to load CLEO.");
		return;
	}
}
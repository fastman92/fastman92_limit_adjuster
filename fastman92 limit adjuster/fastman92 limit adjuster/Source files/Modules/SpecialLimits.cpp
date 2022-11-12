/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "SpecialLimits.h"

#include "FileIDlimit.h"
#include "LoadingScreenFontHooks.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/CEntity.h"
#include "../GameStructures/Rockstar Games/CFont.h"
#include "../GameStructures/Rockstar Games/functions.h"
#include "../GameStructures/Rockstar Games/GameSystem.h"

// #include <errno.h>
// #include <dirent.h>

#include <CRGBA.h>
#include <Array/countof.h>
#include <MultiPlatformSupport/PlatformGeneralisation.h>

using namespace Game;

SpecialLimits g_specialLimits;

class CCheats
{
	static bool** m_aCheatsActive;
};

bool** CCheats::m_aCheatsActive = (bool**)(0x407404 + 2);

static char* StorageRootBuffer;
static char* StorageBaseRootBuffer;

static uintptr_t Address_NvAPKOpen = 0;

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_CHeli__PreRender_6C5442()
	{
		__asm
		{
			mov ecx, esi;
			call CEntity::GetModelID;

			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_fileIDlimits, FileIDlimit, CModelInfo__ms_modelInfoPtrs);
			mov ebx, [eax * 4 + ecx];	// mov     ebx, _modelPtrs[eax*4]

			// hack
			mov eax, [CCheats::m_aCheatsActive];
			mov eax, [eax];
			mov al, [eax + 34];		// cars on water

			test al, al;
			jz goBack;

			mov     eax, [esi];		// vtable address
			mov     ecx, esi;
			call    dword ptr[eax + 114h];

		goBack:
			// go back
			push 6C544Dh;
			ret;
		}
	}
}
#endif

// Make helicopters land on water when cars on water cheat enabled
void SpecialLimits::MakeHelicoptersLandOnWater()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		CPatch::RedirectFunction(0x6C5442, &patch_CHeli__PreRender_6C5442);

		ms_bMakeHelicoptersLandOnWaterWhenCarsOnWaterCheatEnabled = true;
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CGenericLogStorage::SaveFormattedTextLn("SPECIAL: Make helicopters land on water when cars on water cheat enabled.");
	CGenericLogStorage::WriteLineSeparator();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_CVehicle__FlyingControl_6DADD7()
	{
		__asm
		{
			/*
				st(0) = pVelocity->x * pVelocity->x + pVelocity->y * pVelocity->y + pVelocity->z * pVelocity->z;
				st(1) = pVelocity->x;
				st(2) = pVelocity->y;
				st(3) = pVelocity->z;
			*/
			fstp    st;

			/*
				st(0) = pVelocity->x;
				st(1) = pVelocity->y;
				st(2) = pVelocity->z;
			*/
			fstp    st;

			/*
				st(0) = pVelocity->y;
				st(1) = pVelocity->z;
			*/
			fstp    st;

			/*
				st(0) = pVelocity->z;
			*/

			push 0x6DADDD;
			retn;
		}
	}
}
#endif

// Disables 270 km\h plane speed limit.
void SpecialLimits::DisablePlaneSpeedLimit()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		// CPatch::PatchUINT16(0x6DADE8, 0x60EB);
		CPatch::RedirectCode(0x6DADD7, &patch_CVehicle__FlyingControl_6DADD7);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	ms_bDisablePlaneSpeedLimit = true;

	CGenericLogStorage::SaveFormattedTextLn("SPECIAL: Plane speed limit disabled.");
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

// Disables radar rotation
void SpecialLimits::DisableRadarRotation()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		CPatch::EnterNewLevel();
		CPatch::DisableDebugMode();

		//CPatch::PatchUINT16(0x6DADE8, 0x60EB);
		CPatch::NOPinstructions(0x583670, 5);
		CPatch::NOPinstructions(0x583678, 4);
		this->ms_bDisableRadarRotation = true;

		CPatch::LeaveThisLevel();
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CGenericLogStorage::SaveFormattedTextLn("SPECIAL: Disable radar rotation applied.");
	CGenericLogStorage::WriteLineSeparator();	
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_4C93C2()
	{
		__asm
		{
			push NULL;
			lea ecx, [esp + 18h];
			push ecx;
			mov byte ptr[esp + esi + 1Ch], 00;
			call CModelInfo::GetModelInfo;
			mov     esi, eax;
			add esp, 20;

			push 0x4C93E0;
			retn;
		}
	}
}
#endif

// Makes paintjobs for work for any ID
void SpecialLimits::MakePaintjobsWorkForAnyID()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		CPatch::EnterNewLevelAndDisableDebugState();

		CPatch::RedirectCode(0x4C93C2, &patch_4C93C2);

		SpecialLimits::ms_bPaintjobsWorkOnAnyID = true;

		CPatch::LeaveThisLevel();
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CGenericLogStorage::SaveFormattedTextLn("SPECIAL: Make paintjobs work for any ID applied.");
	CGenericLogStorage::WriteLineSeparator();
}

namespace Game_GTAIII
{
	static void renderLoadingText(void* pCustomData)
	{
		unsigned int screenResolutionX = CGameSystem::ScreenGetWidth();
		unsigned int screenResolutionY = CGameSystem::ScreenGetHeight();

		// CFont::SetBackgroundOff
		CFont::SetBackgroundOff();

		//////
		float sizeX = (float)screenResolutionX / 640.0 * 0.5;
		float sizeY = (float)screenResolutionY / 480.0 * 0.5;

		// CFont::SetScale
		CFont::SetScale(sizeX, sizeY);

		// CFont::SetPropOn
		CFont::SetPropOn();
		
		// CFont::SetFontStyle
		CFont::SetFontStyle(0);

		// CFont::SetCentreSize
		CFont::SetCentreSize((float)screenResolutionX);

		// color
		{
			CRGBA color(235, 171, 52, 255);

			// CFont::SetColor
			CFont::SetColor(color);
		}

		float positionX = (float)screenResolutionX / 640.0 * 320.0;
		float positionY = (float)screenResolutionY / 448.0 * 20.0;

		// CFont::PrintString
		CFont::PrintString(
			positionX, positionY, &g_LoadingScreenFontHooks.loadingScreenText
			);
	}
}

// Enables loading text
void SpecialLimits::EnableLoadingText()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	else if (gameVersion == GAME_VERSION_GTA_III_1_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_III_1_8_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTAIII;
		g_LoadingScreenFontHooks.AddCallback(&renderLoadingText, nullptr);
	}
	else
		return;

	CGenericLogStorage::SaveFormattedTextLn("SPECIAL: Loading text enabled.");
	CGenericLogStorage::WriteLineSeparator();
}

namespace Game_GTAIV
{
	class CInstallFolderProblem
	{
	public:
		bool GetInstallFolder(char* pInstallFolder)
		{
			strncpy(pInstallFolder, g_LimitAdjuster.StorageRootDirectory, 260);
			return true;
		}
	};
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTAIV
{
	uintptr_t Address_7FE186 = 0;

	// Patch addresses comes from EFLC 1.0.2.0
	NAKED void patch_7FE0EC()
	{
		__asm
		{
			mov[esp + 23Ch - 234h], ecx;	// this
			mov[esp + 23Ch - 230h], eax;	// first argument on stack
			mov[esp + 23Ch + 220h], 0;
			jmp Address_7FE186;
		}
	}

	uintptr_t Address_7FE1BE = 0;
	uintptr_t Address_7FE50F = 0;	

	NAKED void patch_7FE190()
	{
		__asm
		{
			// allocated area for string
			add     esp, 4;

			mov esi, eax;

			mov[esp + 23Ch - 224h], esi;

			push eax;
			mov ecx, [esp + 23Ch - 234h];	// this
			call CInstallFolderProblem::GetInstallFolder;

			test al, al;
			jz loc_7FE50F;

			jmp Address_7FE1BE;


		loc_7FE50F:
			jmp Address_7FE50F;
		}
	}

	namespace Altered
	{
		LSTATUS
			APIENTRY
			RegOpenKeyExA(
				__in HKEY hKey,
				__in_opt LPCSTR lpSubKey,
				__in_opt DWORD ulOptions,
				__in REGSAM samDesired,
				__out PHKEY phkResult
			)
		{
			return ERROR_SUCCESS;
		}

		const void* pRegOpenKeyExA = &RegOpenKeyExA;

		LSTATUS
			APIENTRY
			RegQueryValueExA(
				__in HKEY hKey,
				__in_opt LPCSTR lpValueName,
				__reserved LPDWORD lpReserved,
				__out_opt LPDWORD lpType,
				__out_bcount_part_opt(*lpcbData, *lpcbData) __out_data_source(REGISTRY) LPBYTE lpData,
				__inout_opt LPDWORD lpcbData
			)
		{
			if (!strcmp(lpValueName, "InstallFolder"))
			{
				strncpy((char*)lpData, g_LimitAdjuster.StorageRootDirectory, *lpcbData);
				*lpcbData = strlen((char*)lpData) + 1;

				return ERROR_SUCCESS;
			}
			else
				return ERROR_FILE_NOT_FOUND;
		}

		const void* pRegQueryValueExA = &RegQueryValueExA;

		LSTATUS
			APIENTRY
			RegCloseKey(
				__in HKEY hKey
			)
		{
			return ERROR_SUCCESS;
		}

		const void* pRegCloseKey = &RegCloseKey;
	}
}
#endif

// Fixes installfolder problem, which fixes the following error:
// the downloadable content required for this autoload is not available.
void SpecialLimits::FixInstallFolderProblem()
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
	{
		using namespace Game_GTAIV;

		
		/*
		////// An old way of hacking InstallFolder //////

		CPatch::EnterNewLevelAndDisableDebugState();
		
		CPatch::RedirectMethod(g_mCalc.GetCurrentVAbyPreferedVA(0x8B3260), &CInstallFolderProblem::GetInstallFolder);

		////
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x7FE0EC), &patch_7FE0EC);
		Address_7FE186 = g_mCalc.GetCurrentVAbyPreferedVA(0x7FE186);

		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x7FE190), &patch_7FE190);
		Address_7FE1BE = g_mCalc.GetCurrentVAbyPreferedVA(0x7FE1BE);
		Address_7FE50F = g_mCalc.GetCurrentVAbyPreferedVA(0x7FE50F);

		CPatch::NOPinstructions(g_mCalc.GetCurrentVAbyPreferedVA(0x7FE1CA), 7);
		CPatch::LeaveThisLevel();
		*/

		/////////////

		CPatch::EnterNewLevelAndDisableDebugState();

		// next function
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7FE0EC + 2), &Altered::pRegOpenKeyExA);
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7FE1B0 + 2), &Altered::pRegQueryValueExA);
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7FE1CB + 2), &Altered::pRegCloseKey);
		
		// next function
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8B3264 + 2), &Altered::pRegOpenKeyExA);
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8B330D + 2), &Altered::pRegQueryValueExA);
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8B3322 + 2), &Altered::pRegCloseKey);

		CPatch::LeaveThisLevel();
	}
	else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_3_0_WIN_X86)
	{
		using namespace Game_GTAIV;

		CPatch::EnterNewLevelAndDisableDebugState();

		// next function
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x859F84 + 2), &Altered::pRegOpenKeyExA);
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x85A02D + 2), &Altered::pRegQueryValueExA);
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x85A042 + 2), &Altered::pRegCloseKey);

		CPatch::LeaveThisLevel();
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CGenericLogStorage::SaveFormattedTextLn("SPECIAL: Fix installfolder problem applied.");
	CGenericLogStorage::WriteLineSeparator();
}

// Initialize
void SpecialLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();
	this->ms_bMakeHelicoptersLandOnWaterWhenCarsOnWaterCheatEnabled = false;
	this->ms_bDisablePlaneSpeedLimit = false;
	this->ms_bDisableRadarRotation = false;
	this->ms_bPaintjobsWorkOnAnyID = false;
	this->ms_bFixStreamingMemoryBug = false;
	this->ms_bFixCheatsTypedByKeyboardNotWorking = false;
	this->ms_bFixKeyboardMakingBadMouseMovement = false;
	this->ms_bAlterFileLoadingOrder = false;
	this->ms_bRemoveRequirementForLodDFFtoHoldNativePLGdata = false;
	this->ms_bMakeLoadingOfFilesFromRootDirectoryPossible = false;

	if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
	{
		#ifdef IS_PLATFORM_ANDROID_ARM32
		{
			// Storage root buffer
			StorageRootBuffer = (char*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"StorageRootBuffer"
			);

			// Storage base root buffer
			StorageBaseRootBuffer = (char*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"StorageBaseRootBuffer"
			);

			// Asset manager open
			Address_NvAPKOpen = (uintptr_t)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_Z9NvAPKOpenPKc"
			);
		}
		#endif
	}
}

/*
namespace Game_GTAIV
{
	void __cdecl beforeStart()
	{
		printf_MessageBox("Please attach debugger now.");
	}

	// patch to show message box
	NAKED void patch_start()
	{
		__asm
		{
			call beforeStart;

			push 0xD0CE39;	// return location

			mov eax, 0xD1A1F7;	// sub_D1A1F7
			jmp eax;
		}
	}

	// Shows message box before process code gets executed.
	void SpecialLimits::ShowMessageBoxBeforeProcessCodeGetsExecuted()
	{
		CPatch::RedirectCode(0xD0D011, &patch_start);
	}
}
*/

// Fixes keyboard making bad mouse movement
void SpecialLimits::FixKeyboardMakingBadMouseMovement()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();
	
	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_ANDROID_ARM32
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{		
		// CPad::UpdatePads
		CPatch::RedirectCodeEx(
			INSTRUCTION_SET_THUMB,
			g_mCalc.GetCurrentVAbyPreferedVA(0x3F8B06),
			g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3F8B6E))
		);
		
		// CPatch::DisableFunctionByName("_ZN4CPad11UpdateMouseEv");
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_bFixKeyboardMakingBadMouseMovement = true;

	CGenericLogStorage::SaveFormattedTextLn("SPECIAL: Fix keyboard making bad mouse movement applied.");
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

// Fixes cheats typed from keyboard not working
void SpecialLimits::FixCheatsTypedFromKeyboardNotWorking()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_ANDROID_ARM32
	else if (gameVersion == GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A)
	{
		uint16_t* ptrArray = (uint16_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x56D234);
		uint16_t newArrayValues['z' - 'a' + 1];
		uint16_t defaultCase = 0x4A4;

		for (unsigned int i = 0; i < _countof(newArrayValues); i++)
			newArrayValues[i] = defaultCase;	// default case

		CPatch::PatchMemoryData(
			(uintptr_t)(ptrArray + 'a' - 0x22),	// 0x22 - base index of switch
			newArrayValues,
			sizeof(newArrayValues)
		);
	}
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		uint16_t* ptrArray = (uint16_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x5E5B40);
		uint16_t newArrayValues['z' - 'a' + 1];
		uint16_t defaultCase = 0x447;

		for (unsigned int i = 0; i < _countof(newArrayValues); i++)
			newArrayValues[i] = defaultCase;	// default case

		CPatch::PatchMemoryData(
			(uintptr_t)(ptrArray + 'a' - 0x22),	// 0x22 - base index of switch
			newArrayValues,
			sizeof(newArrayValues)
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_bFixCheatsTypedByKeyboardNotWorking = true;

	CGenericLogStorage::SaveFormattedTextLn("SPECIAL: Fix cheats typed by keyboard not working applied.");
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

enum eNvidiaFileHandleType
{
	NVIDIA_HANDLE_ASSET,
	NVIDIA_HANDLE_FILE,
};

struct tNvidiaFileHandle
{
	eNvidiaFileHandleType type;
	void* ptr;
};

extern "C"
{
	#define ALTER_NVFOPEN_FUNCTION

	#ifdef IS_PLATFORM_ANDROID
	// opens files from file system / APK archive

	// directoryPath can be NULL
	tNvidiaFileHandle* NvFOpen_replacement(const char* directoryPath, const char* filename, bool arg3, bool arg4)
	{
		static bool data_app_path_used = false;
		static char savedPathToSDcard[512];
		static int lenOfsavedPathToSDcard = -1;

		char filepath[516];
		tNvidiaFileHandle* pFileHandle = (tNvidiaFileHandle*)game_malloc(sizeof(tNvidiaFileHandle));

		if (!directoryPath)
		{
			if (filename[0] == '/')
			{
				if (strncmp(filename, "/data/app", 9) == 0)
				{
					data_app_path_used = true;
					strcpy(filepath, filename);
					// OutputFormattedDebugString("Filepath: %s 3", filepath);
				}
				else
				{
					/*
					if (lenOfsavedPathToSDcard == -1)
					{
						char* pSlash;

						if ((pSlash = strstr(StorageRootBuffer, "/Android"))
							|| (pSlash = strstr(StorageRootBuffer, "/android")))
						{
							lenOfsavedPathToSDcard = pSlash - StorageRootBuffer;
							strncpy(savedPathToSDcard, StorageRootBuffer, lenOfsavedPathToSDcard);
							savedPathToSDcard[lenOfsavedPathToSDcard] = 0;
						}
					}
					else
					{
						strcpy(savedPathToSDcard, StorageBaseRootBuffer);
						lenOfsavedPathToSDcard = strlen(savedPathToSDcard);
					}
					*/

					sprintf(filepath, "%s%s", StorageBaseRootBuffer, filename);
					// OutputFormattedDebugString("Filepath: %s 1", filepath);
				}
			}
			else
			{
				sprintf(filepath, "%s%s", StorageRootBuffer, filename);
				// OutputFormattedDebugString("Filepath: %s 2", filepath);
			}
			
		use_fopen:
			if (FILE* fp = game_fopen(filepath, "rb"))
			{
				pFileHandle->type = NVIDIA_HANDLE_FILE;
				pFileHandle->ptr = fp;
				return pFileHandle;
			}
			else
			{
				game_free(pFileHandle);
				return NULL;
			}
		}
		else
		{
			sprintf(filepath, "%s/%s%s", StorageRootBuffer, directoryPath, filename);
			// OutputFormattedDebugString("Filepath: %s %s %s 4", StorageRootBuffer, directoryPath, filename);

			if (data_app_path_used || !arg4 || arg3)
				goto use_fopen;	
		}

		#ifdef ALTER_NVFOPEN_FUNCTION
		
		// OutputFormattedDebugString("xFilepath: %s before", filepath);

		if (FILE* fp = game_fopen(filepath, "rb"))
		{
			// OutputFormattedDebugString("xFilepath: %s success", filepath);
			pFileHandle->type = NVIDIA_HANDLE_FILE;
			pFileHandle->ptr = fp;
			return pFileHandle;
		}

		// OutputFormattedDebugString("xFilepath: %s failed", filepath);
		#endif
		
		void* pAssetHandle = g_memoryCall.Function<void*>(Address_NvAPKOpen, filename);

		// OutputFormattedDebugString("directory: 0x%X filename: %s arg3: %d arg4: %d asset: 0x%X", directoryPath, filename, arg3, arg4, pAssetHandle);

		#ifndef ALTER_NVFOPEN_FUNCTION
		if (!pAssetHandle)
			goto use_fopen;
		#else
		if (!pAssetHandle)
		{
			game_free(pFileHandle);
			return NULL;
		}
		#endif
				
		pFileHandle->type = NVIDIA_HANDLE_ASSET;
		pFileHandle->ptr = pAssetHandle;
		return pFileHandle;
	}
	#endif
}

#ifdef IS_PLATFORM_ANDROID_ARM32
// patch for 0xFA37C
template<int stack_value> TARGET_THUMB NAKED void patch_NvFOpen_plus_4()
{
	__asm(
	".thumb\n"
		".thumb\n"

		"ADD SP, #%c[stack_value]\n"

		ASM_JUMP_TO_ADDRESS_OF_SYMBOL(NvFOpen_replacement)
		::[stack_value]"i"(stack_value)
		);
}
#endif

// Alters file loading order
void SpecialLimits::AlterFileLoadingOrder()
{
	#if 0
	{
		OutputFormattedDebugString(g_LimitAdjuster.StorageRootDirectory);

		char path[PATH_MAX];
		DIR* dir = opendir(g_LimitAdjuster.StorageRootDirectory);

		dirent* drnt;

		while ((drnt = readdir(dir)) != nullptr)
		{
			if (!strcmp(drnt->d_name, ".") || !strcmp(drnt->d_name, ".."))
				continue;

			sprintf(path, "%s%s", g_LimitAdjuster.StorageRootDirectory, drnt->d_name);

			FILE* testFile = fopen(path, "rb");

			if (testFile)
			{
				OutputFormattedDebugString("Test file opened: %s", drnt->d_name);
				fclose(testFile);
			}
			else
			{
				OutputFormattedDebugString("Test file unable to open %s, error: %s", drnt->d_name, strerror(errno));
			}
			// if (!strcmp(drnt->d_name, "libcleo.so"))
		}

		/*/

		*/
	}
	#endif
	//////////

	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_ANDROID_ARM32
	if (gameVersion == GAME_VERSION_GTA_III_1_8_ANDROID_ARMEABI_V7A)
	{
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0xFA37C),
			(void*)&patch_NvFOpen_plus_4<0x1C>
		);
	}
	else if (gameVersion == GAME_VERSION_GTA_VC_1_09_ANDROID_ARMEABI_V7A)
	{
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31AF48),
			(void*)&patch_NvFOpen_plus_4<0x24>
		);
	}
	else if (gameVersion == GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A)
	{
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x23B3E0),
			(void*)&patch_NvFOpen_plus_4<0x24>
		);
	}
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
		|| gameVersion == GAME_VERSION_GTA_SA_GER_2_09_ANDROID_ARMEABI_V7A)
	{
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x266E30),
			(void*)&patch_NvFOpen_plus_4<0x14>
		);
	}
	else if (gameVersion == GAME_VERSION_BULLY_AE_1_0_0_18_ANDROID_ARMEABI_V7A)
	{
		CPatch::RedirectFunction(
				(uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_Z7NvFOpenPKcS0_bb"),
				(void*)&NvFOpen_replacement
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_bAlterFileLoadingOrder = true;

	CGenericLogStorage::SaveFormattedTextLn("SPECIAL: Alter file loading order enabled.");
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

unsigned int GetBufferID_replacement(CEntity* pEntity)
{
	auto pRwObject = pEntity->m_pRwThing(pEntity).m_pRwObject;

	if (!pRwObject)
		return 0;

	RpAtomic* pAtomic;

	// is not atomic?
	if (pRwObject->type(pRwObject) != 1)
		pAtomic = GetFirstAtomic((RpClump*)pRwObject);
	else
		pAtomic = (RpAtomic*)pRwObject;

	////
	void* pGeometry = *(void**)((char*)pAtomic + 0x18);

	if (!pGeometry)
		return 0;

	void* pResEntry = *(void**)((char*)pGeometry + 0x5C);

	if (!pResEntry)
		return 0;
	
	unsigned int emuArray = *(unsigned int*)((char*)pResEntry + 0x38);
	
	if (!emuArray)
		return 0;

	return emu_ArraysGetID(emuArray);
}

int sortLODs_replacement(const void* ppEntityFirst, const void* ppEntitySecond)
{
	unsigned int ID_first = GetBufferID_replacement(*(CEntity**)ppEntityFirst);
	unsigned int ID_second = GetBufferID_replacement(*(CEntity**)ppEntitySecond);

	if (ID_first < ID_second)
		return 1;
	else if (ID_first > ID_second)
		return -1;
	else
		return 0;
}

// Removes a requirement for LOD DFF to hold native PLG data
void SpecialLimits::RemoveRequirementForLodDFFtoHoldNativePLGdata()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_ANDROID_ARM32
	else if (gameVersion == GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A
	|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		uintptr_t Address_SortLODs = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_Z8sortLODsPKvS0_"
		);

		CPatch::RedirectFunction(Address_SortLODs, (void*)&sortLODs_replacement);

		CPatch::RedirectFunction((uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_Z11GetBufferIDP7CEntity"
			), (void*)&GetBufferID_replacement
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_bRemoveRequirementForLodDFFtoHoldNativePLGdata = true;

	CGenericLogStorage::SaveFormattedTextLn("SPECIAL: Remove LOD DFF requirement to hold native data enabled.");
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

#ifdef IS_PLATFORM_ANDROID_ARM32
class Platform_replacement
{
public:
	static char bundleRoot[1024];

	static const char* GetBundleRoot()
	{
		return bundleRoot;
	}
};

char Platform_replacement::bundleRoot[1024];

// patch for 0x4EF334
extern "C"
{
	uintptr_t Address_LogicalFS_OpenBundleFile_4EF354_arm = 0;

	uintptr_t Address_LogicalFS_OpenBundleFile_4F14DC_arm = 0;

	uintptr_t Address_LogicalFS_OpenBundleFile_4F0010_arm = 0;

	void PrintFilenameToBeOpened(const char* filename)
	{
		OutputFormattedDebugString("Filename: %s", filename);
	}
}

static TARGET_ARM NAKED void patch_LogicalFS_OpenBundleFile_4EF334()
{
	__asm(
		".arm\n"

		// call to Platform::FileOpenOSFilePath
		"MOV R1, #0\n"
		"LDR R2, [R11,#-576]\n"
		"MOV R0, R4\n"
		"BL 1f\n"

		"CMP             R0, #0\n"
		"BNE 12f\n" // return, opened a file from disk

		// Call to WadArchive::OpenFile
		"LDR R0, [R8,#8]\n"

		"CMP R0, #0\n"
		"BEQ 11f\n"

		"MOV R1, R4\n"
		"MOV R2, #0\n"
		"BL 2f\n"

		"CMP             R0, #0\n"
		"BNE 10f\n" // return

		"11:\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_LogicalFS_OpenBundleFile_4EF354_arm)

		//////////

		"12:\n"

		// R0 is the result here

		/*
		"PUSH {R0, R1}\n"
		"MOV R0, R4\n"
		"BLX PrintFilenameToBeOpened\n"
		"POP {R0, R1}\n"
		*/

		"10:\n"
		"SUB SP, R11, #0x20\n"
		"LDMFD SP!, {R4-R11,PC}\n"

		// Branches
		"1:\n"	// _ZN8Platform18FileOpenOSFilePathEPKc8FileModei
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_LogicalFS_OpenBundleFile_4F14DC_arm)

		"2:\n"	// _ZN10WadArchive8OpenFileEPKc8FileMode
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_LogicalFS_OpenBundleFile_4F0010_arm)
		
		);
}

static FILE	*(**fopen_ptr)(const char * filename, const char *mode);

static FILE	*fopen_replacement(const char * filename, const char *mode)
{
	char path[PATH_MAX];
	char c = filename[0];

	// is it a relative path?
	if (c != '.' && c != '/' && c != '\\')
	{
		sprintf(path, "%s/%s", g_LimitAdjuster.StorageRootDirectory, filename);
		filename = path;
	}
	
	return (*fopen_ptr)(filename, mode);
}
#endif

// Makes loading of files from root directory possible
void SpecialLimits::MakeLoadingOfFilesFromRootDirectoryPossible()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_ANDROID_ARM32
	else if (gameVersion == GAME_VERSION_GTA_LCS_2_4_ANDROID_ARMEABI_V7A)
	{
		sprintf(Platform_replacement::bundleRoot, "%s/", g_LimitAdjuster.StorageRootDirectory);

		CPatch::RedirectFunction(
			(uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN8Platform13GetBundleRootEv"),
			(void*)&Platform_replacement::GetBundleRoot
		);

		// Changes
		Address_LogicalFS_OpenBundleFile_4EF354_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x4EF354));

		Address_LogicalFS_OpenBundleFile_4F14DC_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x4F14DC));

		Address_LogicalFS_OpenBundleFile_4F0010_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x4F0010));

		CPatch::RedirectCodeEx(INSTRUCTION_SET_ARM, g_mCalc.GetCurrentVAbyPreferedVA(0x4EF334),
			(void*)&patch_LogicalFS_OpenBundleFile_4EF334
		);

		// redirect fopen
		fopen_ptr = (decltype(fopen_ptr))g_mCalc.GetCurrentVAbyPreferedVA(0x74FAFC);

		CPatch::RedirectFunction((uintptr_t)g_mCalc.GetCurrentVAbyPreferedVA(0x10A038),
			(void*)&fopen_replacement);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_bMakeLoadingOfFilesFromRootDirectoryPossible = true;

	CGenericLogStorage::SaveFormattedTextLn("SPECIAL: Make loading of files from root directory possible enabled.");
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
extern "C"
{
	void increaseRefCountForView(void* view)
	{
		uintptr_t method = (uintptr_t)*(*(void***)view + 2);
		g_memoryCall.Method<void>(method, view);
	}

	void decreaseRefCountForView(void* view)
	{
		uintptr_t method = (uintptr_t)*(*(void***)view + 3);
		g_memoryCall.Method<void>(method, view);
	}
}

namespace Game_GTASA
{
	////// GTA SA 1.08 ///////
	// patch for 0xC75DC
	extern "C"
	{
		uintptr_t Address_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C75E8 = 0;
		uintptr_t Address_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C75E4_arm = 0;
	}

	static TARGET_ARM NAKED void patch_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C75DC()
	{
		__asm(
		".arm\n"
			"MOV R0, R4\n"
			"BLX increaseRefCountForView\n"

			"LDR R2, =("/* _ZTVN3hal13PasswordInputE_ptr */"0x1F5DFC - 0x1F57F4)\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R6, Address_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C75E8)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C75E4_arm)
			);
	}

	// patch for 0xC7638
	extern "C"
	{
		uintptr_t Address_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C7640_arm = 0;	// off_C7640
	}

	static TARGET_ARM NAKED void patch_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C7638()
	{
		__asm(
		".arm\n"
			"MOV R0, R4\n"
			"BLX decreaseRefCountForView\n"

			"MOV R0, R4\n"
			"POP {R4-R6,PC}\n"
			);
	}

	// patch for 0xC766C
	extern "C"
	{
		uintptr_t Address_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C7678 = 0;
		uintptr_t Address_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C7674_arm = 0;
	}

	static TARGET_ARM NAKED void patch_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C766C()
	{
		__asm(
		".arm\n"
			"MOV R0, R4\n"
			"BLX increaseRefCountForView\n"

			"LDR R2, =("/* _ZTVN3hal13PasswordInputE_ptr */"0x1F5DFC - 0x1F57F4)\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R5, Address_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C7678)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C7674_arm)
			);
	}

	// patch for 0xC76D0
	static TARGET_ARM NAKED void patch_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C76D0()
	{
		__asm(
		".arm\n"
			"MOV R0, R4\n"
			"BLX decreaseRefCountForView\n"

			"MOV R0, R4\n"
			"POP {R4-R6,PC}\n"
			);
	}

	////// GTA SA 2.0 ///////

	// patch for 0x1AB23A
	extern "C"
	{
		uintptr_t Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB244 = 0;
		uintptr_t Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB246 = 0;
		uintptr_t Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB244_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB23A()
	{
		__asm(
		".thumb\n"
			"MOV R0, R4\n"
			"BLX increaseRefCountForView\n"

			"LDR R0, =("/* _ZTVN3hal11staticCountINS_13PasswordInputEEE_ptr */"0x296F08 - 0x1AB244)\n"
			"LDR R1, =("/* _ZN3hal11staticCountINS_13PasswordInputEE14s_currentCountE_ptr */"0x296EB0 - 0x1AB246)\n"
			"LDR R2, =("/* _ZTVN3hal13PasswordInputE_ptr */"0x296E60 - 0x1AB248)\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB244)
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB246)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB244_thumb)
			);
	}

	// patch for 0x1AB2A0
	extern "C"
	{
		uintptr_t Address_gtasa_2_0_hal__PasswordInput__PasswordInput_4290C_arm = 0;	// j__Z8callVoidPKcS0_S0_P8_jobjectz
		uintptr_t Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB2A8_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB2A0()
	{
		__asm(
		".thumb\n"
			"BL 1f\n"

			"MOV R0, R4\n"
			"BLX decreaseRefCountForView\n"

			"MOV R0, R4\n"
			"ADD SP, SP, #8\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB2A8_thumb)

			// Branches
			"1:\n"	// j__Z8callVoidPKcS0_S0_P8_jobjectz
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_gtasa_2_0_hal__PasswordInput__PasswordInput_4290C_arm)
			);
	}

	/////////////
	// patch for 0x1AB324
	extern "C"
	{
		uintptr_t Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB32C_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB324()
	{
		__asm(
		".thumb\n"
			"MOV R0, R4\n"
			"BLX increaseRefCountForView\n"

			"LDR R0, =("/* _ZTVN3hal11staticCountINS_13PasswordInputEEE_ptr */"0x296F08 - 0x1AB330)\n"
			"CMP R5, #1\n"
			"LDR R1, =("/* _ZN3hal11staticCountINS_13PasswordInputEE14s_currentCountE_ptr */"0x296EB0 - 0x1AB332)\n"
			"LDR R2, =("/* _ZTVN3hal13PasswordInputE_ptr */"0x296E60 - 0x1AB334)\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB32C_thumb)
			);
	}

	// patch for 0x1AB358
	extern "C"
	{
		uintptr_t Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB396_thumb = 0;	// loc_1AB396
		uintptr_t Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB360_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB358()
	{
		__asm(
		".thumb\n"
			"STRD R0, R0, [R0,#0x10]\n"
			"BNE 1f\n"
			"MOVS R0, #4\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB360_thumb)

			// Branches
			"1:\n"	// loc_1AB396
			"MOV R0, R4\n"
			"BLX decreaseRefCountForView\n"

			"MOV R0, R4\n"
			"ADD SP, SP, #8\n"
			"POP {R4-R6,PC}\n"
			);
	}

	// patch for 0x1AB392
	extern "C"
	{
		uintptr_t Address_gtasa_2_0_hal__PasswordInput__PasswordInput_4290C_arm_ = 0;	// j__Z8callVoidPKcS0_S0_P8_jobjectz
		uintptr_t Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB39C_thumb = 0;	// off_1AB39C
	}

	static TARGET_THUMB NAKED void patch_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB392()
	{
		__asm(
		".thumb\n"
			"BL 1f\n"

			"MOV R0, R4\n"
			"BLX decreaseRefCountForView\n"

			"MOV R0, R4\n"
			"ADD SP, SP, #8\n"
			"POP {R4-R6,PC}\n"

			// Branches
			"1:\n"	// j__Z8callVoidPKcS0_S0_P8_jobjectz
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_gtasa_2_0_hal__PasswordInput__PasswordInput_4290C_arm_)
			);
	}
}

namespace Game_GTALCS
{
	// patch for 0x5361F8
	extern "C"
	{
		uintptr_t Address_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_536204 = 0;
		uintptr_t Address_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_536200_arm = 0;
	}

	static TARGET_ARM NAKED void patch_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_5361F8()
	{
		__asm(
		".arm\n"
			"MOV R0, R4\n"
			"BLX increaseRefCountForView\n"

			"LDR R2, =("/* _ZTVN3hal13PasswordInputE_ptr */"0x751974 - 0x74F810)\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R5, Address_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_536204)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_536200_arm)
			);
	}

	// patch for 0x536254
	static TARGET_ARM NAKED void patch_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_536254()
	{
		__asm(
		".arm\n"
			"MOV R0, R4\n"
			"BLX decreaseRefCountForView\n"

			"MOV R0, R4\n"
			"SUB SP, R11, #0x10\n"
			"POP {R4-R6,R11,PC}\n"
			);
	}

	///////////
	// patch for 0x5362C4
	extern "C"
	{
		uintptr_t Address_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_5362D0 = 0;
		uintptr_t Address_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_5362CC_arm = 0;
	}

	static TARGET_ARM NAKED void patch_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_5362C4()
	{
		__asm(
		".arm\n"
			"MOV R0, R4\n"
			"BLX increaseRefCountForView\n"

			"LDR R2, =("/* _ZTVN3hal13PasswordInputE_ptr */"0x751974 - 0x74F810)\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R5, Address_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_5362D0)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_5362CC_arm)
			);
	}

	static TARGET_ARM NAKED void patch_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_536320()
	{
		__asm(
		".arm\n"
			"MOV R0, R4\n"
			"BLX decreaseRefCountForView\n"

			"MOV R0, R4\n"
			"SUB SP, R11, #0x10\n"
			"POP {R4-R6,R11,PC}\n"
			);
	}

	static TARGET_ARM NAKED void patch_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_536334()
	{
		__asm(
		".arm\n"
			"MOV R0, R4\n"
			"BLX decreaseRefCountForView\n"

			"MOV R0, R4\n"
			"SUB SP, R11, #0x10\n"
			"POP {R4-R6,R11,PC}\n"
			);
	}
}

namespace Game_GTACTW
{
	extern "C"
	{
		// Align memory to 4096
		const char* GetAlignedTextureStreamMemoryPointer(const char* ptr)
		{
			return ptr + (0x1000 - ((uintptr_t)ptr & 0xFFF));
		}
	}

	// patch for 0x2EADF2
	extern "C"
	{
		uintptr_t Address_cTextureManager__Init_2EADFE = 0;
		uintptr_t Address_cTextureManager__Init_2EAE02_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_cTextureManager__Init_2EADF2()
	{
		__asm(
		".thumb\n"
			"BLX GetAlignedTextureStreamMemoryPointer\n"
			"MOV R1, R0\n"

			"LDR R2, =("/* gTextureStreamMemory_ptr */"0x89DBBC - 0x2EADFE)\n"
			
			"MOV R3, R0\n"
			"MOVS R5, #0\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_cTextureManager__Init_2EADFE)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cTextureManager__Init_2EAE02_thumb)
			);
	}
}

namespace Bully_SE
{
	// patch for 0x34857A
	extern "C"
	{
		uintptr_t Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_348580 = 0;
		uintptr_t Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_348584_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_34857A()
	{
		__asm(
		".thumb\n"
			"MOV R0, R4\n"
			"BLX increaseRefCountForView\n"

			"LDR R1, =("/* _ZTVN3hal13PasswordInputE_ptr */"0xB496AC - 0x34858A)\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R5, Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_348580)
			"LDR R5, [R5]\n"
			"LDR R2, =("/* _ZTVN3hal11staticCountINS_13PasswordInputEEE_ptr */"0xB4C7C4 - 0x348590)\n"
			"MOVS R0, #0\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_348584_thumb)
			);
	}

	// patch for 0x3485AC
	extern "C"
	{
		uintptr_t Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_348518_thumb = 0;	// _ZN3hal13PasswordInput10createViewEv
	}

	static TARGET_THUMB NAKED void patch_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_3485AC()
	{
		__asm(
		".thumb\n"
			"STR R1, [R5]\n"
			"BL 1f\n"

			"MOV R0, R4\n"
			"BLX decreaseRefCountForView\n"

			"MOV R0, R4\n"
			"POP {R4,R5,R7,PC}\n"
			
			// Branches
			"1:\n"	// _ZN3hal13PasswordInput10createViewEv
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_348518_thumb)
			);
	}

	////////
	// patch for 0x3485D6
	extern "C"
	{
		uintptr_t Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_3485E0 = 0;
		uintptr_t Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_3485E0_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_3485D6()
	{
		__asm(
		".thumb\n"
			"MOV R0, R4\n"
			"BLX increaseRefCountForView\n"

			"LDR R0, =("/* _ZN3hal11staticCountINS_13PasswordInputEE14s_currentCountE_ptr */"0xB493FC - 0x3485E0)\n"
			"MOVS R6, #0\n"
			"LDR R1, =("/* _ZTVN3hal13PasswordInputE_ptr */"0xB496AC - 0x3485E6)\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_3485E0)
			"LDR R0, [R0]\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_3485E0_thumb)
			);
	}

	// patch for 0x34860A
	extern "C"
	{
		uintptr_t Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_348518_thumb_ = 0;	// _ZN3hal13PasswordInput10createViewEv
	}

	static TARGET_THUMB NAKED void patch_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_34860A()
	{
		__asm(
		".thumb\n"
			"CBZ R5, 1f\n"
			"MOV R0, R4\n"
			"BL 2f\n"

			"1:\n"	// loc_348612
			"MOV R0, R4\n"
			"BLX decreaseRefCountForView\n"

			"MOV R0, R4\n"
			"POP {R3-R7,PC}\n"
			
			// Branches
			"2:\n"	// _ZN3hal13PasswordInput10createViewEv
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_348518_thumb_)
			);
	}
}
#endif

// Fix HAL crashing on devices with Android 11 and higher
void SpecialLimits::FixHALCrashingOnDevicesWithAndroid11AndHigher()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
	else if (gameVersion == GAME_VERSION_GTA_SA_1_08_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		Address_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C75E8 = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(0xC75E8);
		Address_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C75E4_arm = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0xC75E4));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_ARM, g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(0xC75DC),
			(void*)&patch_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C75DC
		);

		CPatch::RedirectCodeEx(INSTRUCTION_SET_ARM, g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(0xC7638),
			(void*)&patch_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C7638
		);

		///////

		Address_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C7678 = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(0xC7678);
		Address_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C7674_arm = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0xC7674));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_ARM, g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(0xC766C),
			(void*)&patch_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C766C
		);
		
		CPatch::RedirectCodeEx(INSTRUCTION_SET_ARM, g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(0xC76D0),
			(void*)&patch_gtasa_1_0_8_hal__PasswordInput__PasswordInput_C76D0
		);
	}
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A
		|| gameVersion == GAME_VERSION_GTA_SA_GER_2_09_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB244 = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(0x1AB244);
		Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB246 = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(0x1AB246);
		Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB244_thumb = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1AB244));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(0x1AB23A),
			(void*)&patch_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB23A
		);

		Address_gtasa_2_0_hal__PasswordInput__PasswordInput_4290C_arm = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x4290C));
		Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB2A8_thumb = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1AB2A8));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(0x1AB2A0),
			(void*)&patch_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB2A0
		);

		//////
		Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB32C_thumb = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1AB32C));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(0x1AB324),
			(void*)&patch_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB324
		);

		Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB396_thumb = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1AB396));
		Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB360_thumb = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1AB360));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(0x1AB358),
			(void*)&patch_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB358
		);

		Address_gtasa_2_0_hal__PasswordInput__PasswordInput_4290C_arm_ = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x4290C));
		Address_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB39C_thumb = g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1AB39C));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_libSCAnd_mCalc.GetCurrentVAbyPreferedVA(0x1AB392),
			(void*)&patch_gtasa_2_0_hal__PasswordInput__PasswordInput_1AB392
		);
	}
	else if (gameVersion == GAME_VERSION_GTA_LCS_2_4_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTALCS;

		Address_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_536204 = g_mCalc.GetCurrentVAbyPreferedVA(0x536204);
		Address_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_536200_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x536200));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_ARM, g_mCalc.GetCurrentVAbyPreferedVA(0x5361F8),
			(void*)&patch_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_5361F8
		);

		CPatch::RedirectCodeEx(INSTRUCTION_SET_ARM, g_mCalc.GetCurrentVAbyPreferedVA(0x536254),
			(void*)&patch_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_536254
		);

		//////

		Address_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_5362D0 = g_mCalc.GetCurrentVAbyPreferedVA(0x5362D0);
		Address_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_5362CC_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x5362CC));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_ARM, g_mCalc.GetCurrentVAbyPreferedVA(0x5362C4),
			(void*)&patch_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_5362C4
		);

		CPatch::RedirectCodeEx(INSTRUCTION_SET_ARM, g_mCalc.GetCurrentVAbyPreferedVA(0x536320),
			(void*)&patch_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_536320
		);

		CPatch::RedirectCodeEx(INSTRUCTION_SET_ARM, g_mCalc.GetCurrentVAbyPreferedVA(0x536334),
			(void*)&patch_GTA_LCS_2_4_hal__PasswordInput__PasswordInput_536334
		);
	}
	else if (gameVersion == GAME_VERSION_GTA_CTW_1_04_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTACTW;
		
		Address_cTextureManager__Init_2EADFE = g_mCalc.GetCurrentVAbyPreferedVA(0x2EADFE);
		Address_cTextureManager__Init_2EAE02_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2EAE02));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2EADF2),
			(void*)&patch_cTextureManager__Init_2EADF2
		);
	}
	else if (gameVersion == GAME_VERSION_BULLY_AE_1_0_0_18_ANDROID_ARMEABI_V7A)
	{
		using namespace Bully_SE;
		
		Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_348580 = g_mCalc.GetCurrentVAbyPreferedVA(0x348580);
		Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_348584_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x348584));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x34857A),
			(void*)&patch_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_34857A
		);

		Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_348518_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x348518));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3485AC),
			(void*)&patch_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_3485AC
		);

		////////
		Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_3485E0 = g_mCalc.GetCurrentVAbyPreferedVA(0x3485E0);
		Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_3485E0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3485E0));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3485D6),
			(void*)&patch_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_3485D6
		);

		Address_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_348518_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x348518));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x34860A),
			(void*)&patch_Bully_SE_1_0_0_18_hal__PasswordInput__PasswordInput_34860A
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_bFixHALCrashingOnDevicesWithAndroid11AndHigher = true;
	
	CGenericLogStorage::SaveFormattedTextLn("SPECIAL: Fix HAL crashing on devices with Android 11 and higher enabled.");
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

// Disable CINFO.BIN and MINFO.BIN loading
void SpecialLimits::DisableCINFOandMINFOLoading()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevelAndDisableDebugState();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_ANDROID_ARM32
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		// CINFO.BIN
		CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x465FD0), "\x4f\xf0\x00\x00", 4);	// MOV R0, #0

		// MINFO.BIN
		CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x3865BC), "\x4f\xf0\x00\x00", 4);	// MOV R0, #0
	}
	#elif defined(IS_PLATFORM_WIN_X64)
	else if (gameVersion == GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14718_WIN_X64)
	{
		CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x140FB8CF6), "\x31\xc0\x90\x90\x90", 5);	// xor eax, eax
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	ms_bDisableCINFOandMINFOLoading = true;

	CGenericLogStorage::SaveFormattedTextLn("SPECIAL: Disable CINFO.BIN and MINFO.BIN loading");
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}
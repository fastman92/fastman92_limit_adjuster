/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "StreamingLimits.h"
#include "CargrpLimit.h"
#include "ErrorReporting.h"

#include "../Core/CCodeMover.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

using namespace Game;

StreamingLimits g_streamingLimits;

// Returns address to CdStreamOpen loop
uintptr_t GetAddressToCdStreamOpen_loop()
{
	MAKE_VAR_GAME_VERSION();

	if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		return 0x1564A94;
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
		return 0x4067B4;
	else
		return 0;
}

uintptr_t GetAddress_CdStreamOpen_setLastError()
{
	MAKE_VAR_GAME_VERSION();

	if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		return 0x1564B31;
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
		return 0x406839;
	else
		return 0;
}

// Initialize
void StreamingLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (CGameVersion::IsAny_GTA_III(gameVersion))
	{
		// GTA III 1.8 for Android, highest value:
		this->MemoryAvailable = 104857600;
	}
	else if (CGameVersion::IsAny_GTA_VC(gameVersion))
	{
		eGamePlatform platform = CGameVersion::GetPlatform(gameVersion);

		if (platform == GAME_PLATFORM_ANDROID_ARMEABI_V7A)
			// Memory available
			this->MemoryAvailable = 36700160;
		else
			// Memory available
			this->MemoryAvailable = 47185920;
	}
	else if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		// Number of requested models when game considers loading very busy
		this->NumberOfRequestedModelsWhenGameConsidersLoadingVeryBusy = 5;

		// Minimum number of iterations in LoadAllRequestedModels
		this->MinimumNumberOfIterationsInLoadAllRequestedModels = 10;

		// Memory available
		this->MemoryAvailable = 52428800;

		// Streaming_DesiredNumberOfVehiclesLoaded
		this->Streaming_DesiredNumberOfVehiclesLoaded = 22;

		// Max number of stream handles
		this->iStreamHandlesLimit = 32;
		
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			// Stream handles array
			this->streamHandlesArray.ptr = (void**)0x8E4010;
		}
		#elif defined(IS_PLATFORM_ANDROID_ARM32)
		{
			// Stream handles array
			this->streamHandlesArray.ptr = (void**)g_mCalc.GetCurrentVAbyPreferedVA(0x70BE58);
		}
		#endif

		// Stream name item size
		this->streamNameItemSize = 64;

		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			// Stream name array
			this->streamNameArray.ptr = (char*)0x8E4098;
		}
		#elif defined(IS_PLATFORM_ANDROID)
		{
			if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				// Stream name array
				this->streamNameArray.ptr = (char*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"gCdImageNames"
				);
			}
		}
		#endif
	}
}

// Shutdown
void StreamingLimits::Shutdown()
{
	if (streamHandlesArray.bIsAllocated.Get())
		delete[] streamHandlesArray.ptr;

	if (streamNameArray.bIsAllocated.Get())
		delete[] streamNameArray.ptr;
}

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
uint32_t patchVar_MemoryAvailable;

// GTA III 1.8 for Android
// patch for 0x26BEE8
extern "C"
{
	uintptr_t Address_CStreaming__Init_26BEF4 = 0;
	uintptr_t Address_CStreaming__Init_26BEF2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_CStreaming__Init_26BEE8()
{
	__asm(
	".thumb\n"
		"LDR R4, =("/* _ZN10CStreaming19ms_disableStreamingE */"0x3679D0 - 0x26BEF4)\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R4, Address_CStreaming__Init_26BEF4)

		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, patchVar_MemoryAvailable)
		"STR R1, [R4,#("/* _ZN10CStreaming18ms_memoryAvailableE */"0x3679EC - 0x3679D0)]\n"

		"MOVS R3, #35\n"
		"LDR R0, =("/* aMemoryAllocate */"0x33B2FE - 0x26BEFA)\n"
		"CMP R2, #0\n"
		
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CStreaming__Init_26BEF2_thumb)
		);
}

// GTA VC 1.09 for Android
// patch for 0x2087E4
extern "C"
{
	uintptr_t Address_CStreaming__Init_2087EC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_CStreaming__Init_2087E4()
{
	__asm(
		".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, patchVar_MemoryAvailable)
		"LDR R3, [R6,R3]\n"
		"STR R2, [R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CStreaming__Init_2087EC_thumb)
		);
}

// patch for 0x208824
extern "C"
{
	uintptr_t Address_CStreaming__Init_20882C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_CStreaming__Init_208824()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, patchVar_MemoryAvailable)
		"MOVS R7, #0x19\n"
		"LDR R3, [R6,R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CStreaming__Init_20882C_thumb)
		);
}

uintptr_t Address_CStreaming__Init2_goBack;

TARGET_THUMB NAKED void patch_CStreaming__Init2_46BE08()
{
	__asm
	(
		".thumb\n"
		ASM_LOAD_ADDRESS_OF_SYMBOL(R1, patchVar_MemoryAvailable)
		"LDR R1, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CStreaming__Init2_goBack)
	);
}
#endif

// Sets a memory available
void StreamingLimits::SetMemoryAvailable(uint32_t memoryAvailableInBytes)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		memoryAvailableInBytes = this->MemoryAvailable;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
	{
		CPatch::PatchUINT32(0x410799 + 6, memoryAvailableInBytes);

		// Set up a variable
		CCodeMover::SetVariable("MEMORY_AVAILABLE_IN_MBS", memoryAvailableInBytes / (1024 * 1024));

		// Apply the automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddressRel(0x410788, 7, "\x01\x01\x68\x05\x04""MEMORY_AVAILABLE_IN_MBS\x00\x13\x05\x8A\x07\x01\x00\x00", 0x41078F);	// line 1, 0x4100A0 - _ZN10CStreaming4InitEv : push    45
		}
		#endif

		// Delete variable of automatic patch
		CCodeMover::DeleteVariable("MEMORY_AVAILABLE_IN_MBS");
	}
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x5B8E64 + 6, memoryAvailableInBytes);	
	else if (CGameVersion::Is_GTA_SA_1_0_1_EU_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x5B9644 + 6, memoryAvailableInBytes);
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_III_1_8_ANDROID_ARMEABI_V7A)
	{
		patchVar_MemoryAvailable = memoryAvailableInBytes;

		Address_CStreaming__Init_26BEF4 = g_mCalc.GetCurrentVAbyPreferedVA(0x26BEF4);
		Address_CStreaming__Init_26BEF2_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x26BEF2));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x26BEE8),
			(void*)&patch_CStreaming__Init_26BEE8
		);
	}
	else if (gameVersion == GAME_VERSION_GTA_VC_1_09_ANDROID_ARMEABI_V7A)
	{
		patchVar_MemoryAvailable = memoryAvailableInBytes;

		Address_CStreaming__Init_2087EC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2087EC));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2087E4),
			(void*)&patch_CStreaming__Init_2087E4
		);

		Address_CStreaming__Init_20882C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x20882C));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x208824),
			(void*)&patch_CStreaming__Init_208824
		);
	}
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		patchVar_MemoryAvailable = memoryAvailableInBytes;

		CPatch::RedirectCodeEx(
			INSTRUCTION_SET_THUMB,
			g_mCalc.GetCurrentVAbyPreferedVA(0x46BE08),
			(const void*)&patch_CStreaming__Init2_46BE08
		);

		Address_CStreaming__Init2_goBack = g_mCalc.GetCurrentVAbyPreferedVA(
			ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x46BE14)
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CPatch::LeaveThisLevel();

	this->MemoryAvailable = memoryAvailableInBytes;

	CGenericLogStorage::SaveFormattedTextLn(
		"Streaming memory available limit set to %lu bytes (%d MB)",
		memoryAvailableInBytes,
		memoryAvailableInBytes / (1024 * 1024)
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Streaming: desired number of vehicles loaded
void StreamingLimits::SetStreamingDesiredNumberOfVehiclesLoaded(int iDesiredNumVehiclesLoaded)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iDesiredNumVehiclesLoaded = this->Streaming_DesiredNumberOfVehiclesLoaded;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (CPatch::IsDebugModeActive())
			iDesiredNumVehiclesLoaded = 22;

		// check the cargrp limit
		if (iDesiredNumVehiclesLoaded >= (int)g_cargrpLimits.CPopulation__m_iCarsPerGroup)
			throw f92_runtime_error("Streaming_DesiredNumberOfVehiclesLoaded has to be lower than cargrp.dat cars per group limit.");

		// .text:005B8AD0; void __cdecl CStreaming__Init2()
		// .text:005B8AD0     _ZN10CStreaming5Init2Ev proc near
		CPatch::PatchUINT32(0x5B8E6E + 6, iDesiredNumVehiclesLoaded);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->Streaming_DesiredNumberOfVehiclesLoaded = iDesiredNumVehiclesLoaded;

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of Streaming_DesiredNumberOfVehiclesLoaded to: %d", iDesiredNumVehiclesLoaded);
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

void ErrorStreamHandlesLimitExceededCond()
{
	if(g_errorReporting.IsErrorEnabled(GTA_ERROR_STREAM_HANDLES_LIMIT_EXCEEDED))
		ErrorStreamHandlesLimitExceeded();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	static uintptr_t Address_CdStreamOpen_setLastError;

	NAKED void patch_CdStreamOpen_loop()
	{
		__asm
		{
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_streamingLimits, StreamingLimits, streamHandlesArray);
			mov edx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_streamingLimits, StreamingLimits, iStreamHandlesLimit);

		ourLoop:
			mov eax, [ecx + esi * 4];
			test eax, eax;
			jz setLastError;

			inc esi;

			cmp esi, edx;
			jl ourLoop;

			call ErrorStreamHandlesLimitExceededCond;

		setLastError:
			jmp[Address_CdStreamOpen_setLastError];
		}
	}
}
#endif

namespace Game_GTASA
{
	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
	extern "C"
	{
		uint32_t maxNumberOfStreamHandlesMinusOne;
	}

	// patch for 0x2C9CE0
	extern "C"
	{
		uintptr_t Address_CdStreamOpen_2C9CD8_thumb = 0;
		uintptr_t Address_CdStreamOpen_2C9CEA_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CdStreamOpen_2C9CE0()
	{
		__asm(
		".thumb\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, maxNumberOfStreamHandlesMinusOne)
			"MOV R0, R6\n"
			"BLT 1f\n"
			"B 2f\n"

			// Branches
			"1:\n"	// loc_2C9CD8
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CdStreamOpen_2C9CD8_thumb)
			"2:\n"	// loc_2C9CEA
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CdStreamOpen_2C9CEA_thumb)
			);
	}
	#endif
}

// Set max number of stream handles.
void StreamingLimits::SetMaxNumberOfStreamHandles(unsigned int iNumberOfStreamHandles)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iNumberOfStreamHandles = this->iStreamHandlesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
	{
		using namespace Game_GTASA;

		if (iNumberOfStreamHandles > this->iStreamHandlesLimit)
		{
			this->streamHandlesArray.ptr = new void*[iNumberOfStreamHandles];
			this->streamHandlesArray.bIsAllocated.Set(true);

			this->streamNameArray.ptr = new char[iNumberOfStreamHandles * this->streamNameItemSize];
			this->streamNameArray.bIsAllocated.Set(true);
		}

		// Patch count
		CPatch::PatchUINT32(0x406B74 + 1, iNumberOfStreamHandles);

		// Patch pointers to streamHandlesArray
		#if TRUE
		{
			CPatch::PatchPointer(0x4066D3 + 3, streamHandlesArray.ptr);	// mov     eax, ds:streamHandleArray[esi*4]	; sub_406690
			CPatch::PatchPointer(0x4066EA + 3, streamHandlesArray.ptr);	// mov     ds:streamHandleArray[esi*4], ebx	; sub_406690
			CPatch::PatchPointer(0x406734 + 3, streamHandlesArray.ptr);	// mov     eax, ds:streamHandleArray[esi*4]	; 
			CPatch::PatchPointer(0x406794 + 3, streamHandlesArray.ptr);	// mov     ds:streamHandleArray[edi*4], eax	; 			
			CPatch::PatchPointer(0x4068A8 + 3, streamHandlesArray.ptr);	// mov     eax, cdinfo.streamHandleArray[esi*4]	; CStreaming__CloseStreamByHandle
			CPatch::PatchPointer(0x4068BF + 3, streamHandlesArray.ptr);	// mov     eax, ds:streamHandleArray[esi*4]	; 
			CPatch::PatchPointer(0x4068CD + 3, streamHandlesArray.ptr);	// mov     ds:streamHandleArray[esi*4], 0	; 
			CPatch::PatchPointer(0x406B7B + 1, streamHandlesArray.ptr);	// mov     edi, offset streamHandleArray	; sub_406B70
			CPatch::PatchPointer(0x1564A94 + 3, streamHandlesArray.ptr);	// mov     eax, ds:streamHandleArray[esi*4]	; CStreaming__OpenStreamingFile
			CPatch::PatchPointer(0x1564AA3 + 3, streamHandlesArray.ptr + 1);	// mov     eax, ds:streamHandleArray+4[esi*4]	; CStreaming__OpenStreamingFile
			CPatch::PatchPointer(0x1564AAE + 3, streamHandlesArray.ptr + 2);	// mov     eax, ds:streamHandleArray+8[esi*4]	; CStreaming__OpenStreamingFile
			CPatch::PatchPointer(0x1564AB9 + 3, streamHandlesArray.ptr + 3);	// mov     eax, ds:streamHandleArray+0Ch[esi*4]	; CStreaming__OpenStreamingFile
			CPatch::PatchPointer(0x1564AC4 + 3, streamHandlesArray.ptr + 4);	// mov     eax, ds:streamHandleArray+10h[esi*4]	; CStreaming__OpenStreamingFile
			CPatch::PatchPointer(0x1564ACF + 3, streamHandlesArray.ptr + 5);	// mov     eax, ds:streamHandleArray+14h[esi*4]	; CStreaming__OpenStreamingFile
			CPatch::PatchPointer(0x1564ADA + 3, streamHandlesArray.ptr + 6);	// mov     eax, ds:streamHandleArray+18h[esi*4]	; CStreaming__OpenStreamingFile
			CPatch::PatchPointer(0x1564AE5 + 3, streamHandlesArray.ptr + 7);	// mov     eax, ds:streamHandleArray+1Ch[esi*4]	; CStreaming__OpenStreamingFile
			CPatch::PatchPointer(0x1564B71 + 3, streamHandlesArray.ptr);	// mov     cdinfo.streamHandleArray[esi*4], eax	; _Z12CdStreamOpenPKcb
			CPatch::PatchPointer(0x156C2E5 + 3, streamHandlesArray.ptr);	// mov     eax, ds:streamHandleArray[edx*4]	; sub_406A20
			CPatch::PatchPointer(0x15700D0 + 1, streamHandlesArray.ptr);	// mov     eax, ds:streamHandleArray	; 						
		}
		#endif
		
		Address_CdStreamOpen_setLastError = GetAddress_CdStreamOpen_setLastError();
		CPatch::RedirectCode(GetAddressToCdStreamOpen_loop(), &patch_CdStreamOpen_loop);

		// Patch pointers to streamNameArray
		#if TRUE
		{
			CPatch::PatchPointer(0x4066C6 + 1, streamNameArray.ptr);	// mov     edi, offset streamNameArray	; sub_406690
			CPatch::PatchPointer(0x40676B + 1, streamNameArray.ptr);	// mov     esi, offset streamNameArray	; 
			CPatch::PatchPointer(0x4068DB + 2, streamNameArray.ptr);	// mov     ds:streamNameArray[esi], 0	; 
			CPatch::PatchPointer(0x406B80 + 1, streamNameArray.ptr);	// mov     edx, offset streamNameArray	; sub_406B70
			CPatch::PatchPointer(0x1564B8A + 2, streamNameArray.ptr);	// lea     edx, streamNameArray[edx]	; CStreaming__OpenStreamingFile

			CPatch::PatchPointer(0x406B96 + 2, streamNameArray.ptr + iNumberOfStreamHandles * this->streamNameItemSize);
		}
		#endif
	}
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
	{
		using namespace Game_GTASA;

		if (iNumberOfStreamHandles > this->iStreamHandlesLimit)
		{
			this->streamHandlesArray.ptr = new void*[iNumberOfStreamHandles];
			this->streamHandlesArray.bIsAllocated.Set(true);

			this->streamNameArray.ptr = new char[iNumberOfStreamHandles * this->streamNameItemSize];
			this->streamNameArray.bIsAllocated.Set(true);
		}

		// Patch count
		CPatch::PatchUINT32(0x406B74 + 1, iNumberOfStreamHandles);

		// Patch pointers to streamHandlesArray
		#if TRUE
		{
			CPatch::PatchPointer(0x406360 + 1, streamHandlesArray.ptr);	// mov     eax, cdinfo.streamHandleArray	; GetGta3ImgSize
			CPatch::PatchPointer(0x4066D3 + 3, streamHandlesArray.ptr);	// mov     eax, cdinfo.streamHandleArray[esi*4]	; _Z20CdStreamRemoveImagesv
			CPatch::PatchPointer(0x4066EA + 3, streamHandlesArray.ptr);	// mov     cdinfo.streamHandleArray[esi*4], ebx	; _Z20CdStreamRemoveImagesv
			CPatch::PatchPointer(0x406734 + 3, streamHandlesArray.ptr);	// mov     eax, cdinfo.streamHandleArray[esi*4]	; CStreaming__CloseAllStreams
			CPatch::PatchPointer(0x406794 + 3, streamHandlesArray.ptr);	// mov     cdinfo.streamHandleArray[edi*4], eax	; CStreaming__OpenAllStreamsFromStreamNames
			CPatch::PatchPointer(0x4067B4 + 3, streamHandlesArray.ptr);	// mov     eax, cdinfo.streamHandleArray[esi*4]	; _Z12CdStreamOpenPKcb
			CPatch::PatchPointer(0x4067C3 + 3, streamHandlesArray.ptr + 1);	// mov     eax, cdinfo.streamHandleArray+4[esi*4]	; _Z12CdStreamOpenPKcb
			CPatch::PatchPointer(0x4067CE + 3, streamHandlesArray.ptr + 2);	// mov     eax, cdinfo.streamHandleArray+8[esi*4]	; _Z12CdStreamOpenPKcb
			CPatch::PatchPointer(0x4067D9 + 3, streamHandlesArray.ptr + 3);	// mov     eax, cdinfo.streamHandleArray+0Ch[esi*4]	; _Z12CdStreamOpenPKcb
			CPatch::PatchPointer(0x4067E4 + 3, streamHandlesArray.ptr + 4);	// mov     eax, cdinfo.streamHandleArray+10h[esi*4]	; _Z12CdStreamOpenPKcb
			CPatch::PatchPointer(0x4067EF + 3, streamHandlesArray.ptr + 5);	// mov     eax, cdinfo.streamHandleArray+14h[esi*4]	; _Z12CdStreamOpenPKcb
			CPatch::PatchPointer(0x4067FA + 3, streamHandlesArray.ptr + 6);	// mov     eax, cdinfo.streamHandleArray+18h[esi*4]	; _Z12CdStreamOpenPKcb
			CPatch::PatchPointer(0x406805 + 3, streamHandlesArray.ptr + 7);	// mov     eax, cdinfo.streamHandleArray+1Ch[esi*4]	; _Z12CdStreamOpenPKcb
			CPatch::PatchPointer(0x406867 + 3, streamHandlesArray.ptr);	// mov     cdinfo.streamHandleArray[esi*4], eax	; _Z12CdStreamOpenPKcb
			CPatch::PatchPointer(0x4068A8 + 3, streamHandlesArray.ptr);	// mov     eax, cdinfo.streamHandleArray[esi*4]	; CStreaming__CloseStreamByHandle
			CPatch::PatchPointer(0x4068BF + 3, streamHandlesArray.ptr);	// mov     eax, cdinfo.streamHandleArray[esi*4]	; CStreaming__CloseStreamByHandle
			CPatch::PatchPointer(0x4068CD + 3, streamHandlesArray.ptr);	// mov     cdinfo.streamHandleArray[esi*4], 0	; CStreaming__CloseStreamByHandle
			CPatch::PatchPointer(0x406A45 + 3, streamHandlesArray.ptr);	// mov     eax, cdinfo.streamHandleArray[edx*4]	; CdStreamRead
			CPatch::PatchPointer(0x406B7B + 1, streamHandlesArray.ptr);	// mov     edi, offset cdinfo.streamHandleArray	; _Z12CdStreamIniti
		}
		#endif

		Address_CdStreamOpen_setLastError = GetAddress_CdStreamOpen_setLastError();
		CPatch::RedirectCode(GetAddressToCdStreamOpen_loop(), &patch_CdStreamOpen_loop);

		// Patch pointers to streamNameArray
		#if TRUE
		{
			CPatch::PatchPointer(0x4066C6 + 1, streamNameArray.ptr);	// mov     edi, offset cdinfo.streamNameArray	; _Z20CdStreamRemoveImagesv
			CPatch::PatchPointer(0x40676B + 1, streamNameArray.ptr);	// mov     esi, offset cdinfo.streamNameArray	; CStreaming__OpenAllStreamsFromStreamNames
			CPatch::PatchPointer(0x406880 + 2, streamNameArray.ptr);	// lea     edx, cdinfo.streamNameArray[edx]	; _Z12CdStreamOpenPKcb
			CPatch::PatchPointer(0x4068DB + 2, streamNameArray.ptr);	// mov     cdinfo.streamNameArray[esi], 0	; CStreaming__CloseStreamByHandle
			CPatch::PatchPointer(0x406B80 + 1, streamNameArray.ptr);	// mov     edx, offset cdinfo.streamNameArray	; _Z12CdStreamIniti

			CPatch::PatchPointer(0x406B96 + 2, streamNameArray.ptr + iNumberOfStreamHandles * this->streamNameItemSize);
		}
		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if (iNumberOfStreamHandles > this->iStreamHandlesLimit)
		{
			this->streamHandlesArray.ptr = new void*[iNumberOfStreamHandles];
			this->streamHandlesArray.bIsAllocated.Set(true);

			this->streamNameArray.ptr = new char[iNumberOfStreamHandles * this->streamNameItemSize];
			this->streamNameArray.bIsAllocated.Set(true);
		}

		// Set variables
		Game_GTASA::maxNumberOfStreamHandlesMinusOne = iNumberOfStreamHandles - 1;

		// Patch pointers to streamHandlesArray
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x2C9A0C), (char*)streamHandlesArray.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x2C992C));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x2C9A24), (char*)streamHandlesArray.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x2C9A1E));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x2C9B64), (char*)streamHandlesArray.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x2C9AE6));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x2C9D20), (char*)streamHandlesArray.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x2C9CDA));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x2C9D24), (char*)streamHandlesArray.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x2C9CF6));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x2C9D5C), (char*)streamHandlesArray.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x2C9D3A));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x2C9D64), (char*)streamHandlesArray.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x2C9D4C));
		}

		// Patch pointers to streamNameArray
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x67993C), streamNameArray.ptr);

		// Changes
		Address_CdStreamOpen_2C9CD8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2C9CD8));
		Address_CdStreamOpen_2C9CEA_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2C9CEA));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2C9CE0),
			(void*)&patch_CdStreamOpen_2C9CE0
		);		
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->iStreamHandlesLimit = iNumberOfStreamHandles;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of 'Max number of stream handles' to: %d",
		iStreamHandlesLimit
	);

	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

// Sets the number of requested models when game considers loading very busy.
void StreamingLimits::SetTheNumberOfRequestedModelsAboveWhichLoadingIsVeryBusy(int iNumberOfRequestedModels)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iNumberOfRequestedModels = this->NumberOfRequestedModelsWhenGameConsidersLoadingVeryBusy;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
		CPatch::PatchUINT8(0x4076A9 + 6, iNumberOfRequestedModels);	// cmp     _ZN10CStreaming21ms_numModelsRequestedE, 5 ; CStreaming::ms_numModelsRequested
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		CPatch::PatchUINT8(0x156D7A9 + 6, iNumberOfRequestedModels);	// cmp     _ZN10CStreaming21ms_numModelsRequestedE, 5 ; CStreaming::ms_numModelsRequested
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->NumberOfRequestedModelsWhenGameConsidersLoadingVeryBusy = iNumberOfRequestedModels;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of 'Number of requested models above which the game considers loading very busy' to: %d",
		iNumberOfRequestedModels
		);

	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

// Sets the minimum number of iterations in LoadAllRequestedModels
void StreamingLimits::SetMinimumNumberOfIterationsInLoadAllRequestedModels(int minimumValue)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		minimumValue = this->MinimumNumberOfIterationsInLoadAllRequestedModels;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT8(0x40EA35 + 2, minimumValue);	// cmp     eax, 10
			CPatch::PatchUINT32(0x40EA38 + 1, minimumValue);	// mov     ebx, 10
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->MinimumNumberOfIterationsInLoadAllRequestedModels = minimumValue;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of 'Minimum number of iterations in LoadAllRequestedModels' to: %d",
		minimumValue
		);

	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}
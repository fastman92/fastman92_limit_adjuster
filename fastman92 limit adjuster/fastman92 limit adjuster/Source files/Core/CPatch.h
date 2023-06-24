/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "ProjectConstants.h"

#include "../../../fastman92 plugin loader/ForOtherProjects/Exports.h"

#include <Assembly\eInstructionSet.h>
#include <Assembly/UsefulMacros.h>

#include <stdint.h>
#include <vector>

////////////// Patching functions //////////////////

struct tChangedPointer
{
	void* ptr;
	size_t size;
	char oldData[128];
};

struct tForbiddenMemoryRegion
{
	char* start;
	char* end;
};

struct tPatchLevelInfo
{
	bool bDebugEnabled;
	bool bPatchForbiddenCheck;
	bool bDumpMemoryAddressesToLogFile;
};

/*
struct tChangedPointer
{
	void* ptr;
	size_t size;
	char oldData[128];
};
*/

class CPatch
{
public:
	static tPatchLevelInfo* ms_pLevelInfo;
	static tPatchLevelInfo ms_settingStack[32];
	static int ms_nLevelStackCount;

	static tForbiddenMemoryRegion ms_forbiddenMemoryRegionArray[16];
	static int ms_numOfForbiddenMemoryRegions;
	static unsigned int ms_numberOfMemoryChanges;

	static size_t sizeOfMemory;
	static uint32_t memoryPos;
	static uint8_t* pMemory;

	// vector of pointers altered
	static std::vector<tChangedPointer> m_ListOfPointersChanged;

	// Checks if address is not forbidden
	static void CheckIfNotForbiddenAddress(const void* dwAddress, uint32_t size);

	// Performs task for memory address
	static void DoTasksForMemoryAddress(void* dwAddress, int iSize);

	// Writes data to memory
	static void WriteDataToMemory(void* dwAddress, const void* bData, int iSize);

public:

	// Initializer
	static void Init();

	// Is initalized?
	static bool IsInitialized() {
		return ms_pLevelInfo != 0;
	}

	// Returns number of memory changes
	static unsigned int GetNumberOfMemoryChanges();

	// Adds a forbidden memory region
	static void AddForbiddenMemoryRegion(uintptr_t start, uintptr_t end);

	// Enables/disables dumping memory addresses to log file
	static void EnableDumpingMemoryAddressesToLogFile(bool bEnable);
	
	// Enters new level
	static void EnterNewLevel();

	// Leaves this level
	static void LeaveThisLevel();

	// Saves and disables patch debug state
	static void EnterNewLevelAndDisableDebugState();

	// Returns pointer to settings
	static tPatchLevelInfo* GetPointerToSettings();

	// Disables debug mode
	static void DisableDebugMode();
	
#if !(defined FASTMAN92_LIMIT_ADJUSTER) || (PROJECT_IS_UNRELEASED_EDITION)
	// Enables debug mode
	static void EnableDebugMode();
#endif

	// Checks if debug mode is active
	static bool IsDebugModeActive();

	// Patches memory data
	static void PatchMemoryData(uintptr_t dwAddress, const void* bData, int iSize);

	// Patches UINT8 value
	static void PatchUINT8(uintptr_t dwAddress, uint8_t to);

	// Patches UINT16 value
	static void PatchUINT16(uintptr_t dwAddress, uint16_t to);

	// Patches UINT32 value
	static void PatchUINT32(uintptr_t dwAddress, uint32_t to);

	// Patches pointer
	static void PatchPointer(uintptr_t dwAddress, const void* to);

	// Patches float value
	static void PatchFloat(uintptr_t dwAddress, float to);

	#ifdef IS_ARCHITECTURE_X86
	// Puts a call to function
	static void PutCallFunction(uintptr_t dwAddress, const void* to);
#endif


	#if defined(IS_ARCHITECTURE_ARM32)
	// NOP instructions
	static void NOPinstructions(eInstructionSet sourceInstructionSet, uintptr_t dwAddress, int iSize);
	#else
	// NOPs instruction (0x90)
	static void NOPinstructions(uintptr_t dwAddress, int iSize);
	#endif

	static unsigned int RedirectCodeEx(
		eInstructionSet sourceInstructionSet,
		uintptr_t dwAddress,
		uintptr_t to,
		uintptr_t reportedNumberOfBytesOverwritten = 0);

	static unsigned int RedirectCodeEx(
		eInstructionSet sourceInstructionSet,
		uintptr_t dwAddress,
		const void* to,
		uintptr_t reportedNumberOfBytesOverwritten = 0,
		bool doNotSaveRegister = false);

	#ifndef IS_ARCHITECTURE_ARM32
	static unsigned int RedirectCode(uintptr_t dwAddress, uintptr_t to, uintptr_t reportedNumberOfBytesOverwritten = 0);
	static unsigned int RedirectCode(uintptr_t dwAddress, void* to, uintptr_t reportedNumberOfBytesOverwritten = 0);

	// Redirects a method
	template<typename T> static void RedirectMethod(uintptr_t dwAddress, T method)
	{
		RedirectCode(dwAddress, GetMethodAsVoidPointer(method));
	}
	#else
	// Redirects a method
	template<typename T> static void RedirectMethod(uintptr_t methodJmpAddress, T method)
	{
		RedirectCodeEx(GET_INSTRUCTION_SET_FROM_ADDRESS(methodJmpAddress), GET_CODE_START(methodJmpAddress), GetMethodAsVoidPointer(method));
	}
	#endif

	static void RedirectFunction(uintptr_t functionJumpAddress, void* to);

	#if defined(IS_ARCHITECTURE_X86) || defined(IS_ARCHITECTURE_X64)
	// Redirects code, returns the number of bytes at specified location
	static void RedirectCodeOneByte(uintptr_t dwAddress, uintptr_t to);

	static void RedirectCodeOneByte(uintptr_t dwAddress, void* to);

	static void PatchRelative32bitReference(uintptr_t sourceAddress, unsigned int numberOfBytesToEndOfInstruction, uintptr_t destination);
	static void PatchRelative32bitReference(uintptr_t sourceAddress, unsigned int numberOfBytesToEndOfInstruction, const void* destination);

	static void PutOnAddressRelative4byteAddressToAddress(uintptr_t sourceAddress, uintptr_t destination);
	static void PutOnAddressRelative4byteAddressToAddress(uintptr_t sourceAddress, const void* destination);
	#endif

	#ifdef FASTMAN92_LIMIT_ADJUSTER
	// Makes a function return
	static void DisableFunctionByName(const char* name);
	#endif

	// Allocates a redirection, returns a pointer to the redirection code
	static const void* AllocRedirection(uintptr_t target, eInstructionSet instructionSet = CURRENT_PROCESSOR_INSTRUCTION_SET, eTrampolineRegister trampolineRegisterAction = TRAMPOLINE_REGISTER_DO_NOTHING);

private:
	// Allocates buffer memory
	static void AllocateBufferMemory();

	// Moves buffer ahead before writing the data
	static void* MoveBufferAhead(size_t size, size_t alignment);

	// Writes data to buffer
	static void* WriteDataToBuffer(const void* ptr, size_t size, size_t alignment);

public:
	// Checks if pointer wasn't changed before.
	static void ReportPointerIsGoingToBeChanged(void* dwAddress, size_t size);
};

/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPatch.h"
#include "CGenericLogStorage.h"
#include "FormattedOutput.h"
#include "MemoryAllocation.h"

#include <Exception/exception.h>

#ifdef FASTMAN92_LIMIT_ADJUSTER
#include "LimitAdjuster.h"
#endif

#ifdef IS_PLATFORM_ANDROID
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>
#endif

tPatchLevelInfo* CPatch::ms_pLevelInfo = NULL;
tPatchLevelInfo CPatch::ms_settingStack[32];
int CPatch::ms_nLevelStackCount;

tForbiddenMemoryRegion CPatch::ms_forbiddenMemoryRegionArray[16];
int CPatch::ms_numOfForbiddenMemoryRegions;
unsigned int CPatch::ms_numberOfMemoryChanges;

size_t CPatch::sizeOfMemory = 0;
uint32_t CPatch::memoryPos = 0;
uint8_t* CPatch::pMemory = NULL;

// vector of pointers altered
std::vector<tChangedPointer> CPatch::m_ListOfPointersChanged;

// Initializer
void CPatch::Init()
{
	CPatch::ms_pLevelInfo = &CPatch::ms_settingStack[CPatch::ms_nLevelStackCount++];

	CPatch::ms_pLevelInfo->bDebugEnabled = false;
	CPatch::ms_pLevelInfo->bPatchForbiddenCheck = false;
	CPatch::ms_pLevelInfo->bDumpMemoryAddressesToLogFile = false;

	//////////////

	CPatch::ms_pLevelInfo->bDebugEnabled = false;

	CPatch::ms_numOfForbiddenMemoryRegions = 0;
	CPatch::ms_numberOfMemoryChanges = 0;
	CPatch::m_ListOfPointersChanged.clear();

	/////////////
	CPatch::sizeOfMemory = 0;

#if defined(IS_PLATFORM_WIN_X64) // || defined(IS_PLATFORM_ANDROID_X64)
	CPatch::sizeOfMemory = 5 * 1024 * 1024;	// 5 MB
#endif

	if (CPatch::sizeOfMemory != 0)
		CPatch::AllocateBufferMemory();
}

// Returns number of memory changes
unsigned int CPatch::GetNumberOfMemoryChanges()
{
	return CPatch::ms_numberOfMemoryChanges;
}

// Adds a forbidden memory region
void CPatch::AddForbiddenMemoryRegion(uintptr_t start, uintptr_t end)
{
	tForbiddenMemoryRegion* pRegion = &CPatch::ms_forbiddenMemoryRegionArray[CPatch::ms_numOfForbiddenMemoryRegions++];
	pRegion -> start = (char*)start;
	pRegion -> end = (char*)end;
}

// Enables/disables dumping memory addresses to log file
void CPatch::EnableDumpingMemoryAddressesToLogFile(bool bEnable)
{
	CPatch::ms_pLevelInfo->bDumpMemoryAddressesToLogFile = bEnable;
}

// Enters new level
void CPatch::EnterNewLevel()
{
	tPatchLevelInfo* oldLevelInfo = CPatch::ms_pLevelInfo;

	CPatch::ms_pLevelInfo = &CPatch::ms_settingStack[CPatch::ms_nLevelStackCount++];
	memcpy(CPatch::ms_pLevelInfo, oldLevelInfo, sizeof(tPatchLevelInfo));
}

// Leaves this level
void CPatch::LeaveThisLevel()
{
	CPatch::ms_nLevelStackCount--;

	if(CPatch::ms_nLevelStackCount > 0)
		CPatch::ms_pLevelInfo = &CPatch::ms_settingStack[CPatch::ms_nLevelStackCount - 1];
	else
	{
		CPatch::ms_pLevelInfo = NULL;
		printf_MessageBox("CPatch level is NULL");
	}
}

// Saves and disables patch debug state
void CPatch::EnterNewLevelAndDisableDebugState()
{
	CPatch::EnterNewLevel();

	CPatch::ms_pLevelInfo->bDebugEnabled = false;
}

// Returns pointer to settings
tPatchLevelInfo* CPatch::GetPointerToSettings()
{
	return CPatch::ms_pLevelInfo;
}

// Disables debug mode
void CPatch::DisableDebugMode()
{
	CPatch::ms_pLevelInfo->bDebugEnabled = false;
}

#if !(defined FASTMAN92_LIMIT_ADJUSTER) || (PROJECT_IS_UNRELEASED_EDITION)
// Enables debug mode
void CPatch::EnableDebugMode()
{
	CPatch::ms_pLevelInfo->bDebugEnabled = true;
}
#endif

// Checks if debug mode is active
bool CPatch::IsDebugModeActive()
{
	return CPatch::ms_pLevelInfo->bDebugEnabled;
}

// Patches memory data
void CPatch::PatchMemoryData(uintptr_t dwAddress, const void* bData, int iSize, bool bMustBeExecutable)
{
	if (CPatch::ms_pLevelInfo->bDebugEnabled && memcmp((void*)dwAddress, bData, iSize))
		printf_MessageBox("PatchMemoryData, address %p has different data. Compared %d bytes", dwAddress, iSize);

	WriteDataToUnwritableMemory((void*)dwAddress, bData, iSize, bMustBeExecutable);
}

// Patches UINT8 value
void CPatch::PatchUINT8(uintptr_t dwAddress, uint8_t to)
{		
	if (CPatch::ms_pLevelInfo->bDebugEnabled && *(uint8_t*)dwAddress != to)
		printf_MessageBox("PatchUINT8, address %p has different UINT8 value.\nOld value: 0x%02X\nNew value: 0x%02X",
			dwAddress,
			*(uint8_t*)dwAddress,
			to
		);

	WriteDataToUnwritableMemory((void*)dwAddress, &to, sizeof(to), false);
}

// Patches UINT16 value
void CPatch::PatchUINT16(uintptr_t dwAddress, uint16_t to)
{
	if (CPatch::ms_pLevelInfo -> bDebugEnabled && *(uint16_t*)dwAddress != to)
		printf_MessageBox("PatchUINT16, address %p has different UINT16 value.\nOld value: 0x%04X\nNew value: 0x%04X",
		dwAddress,
		*(uint16_t*)dwAddress,
		to
		);

	WriteDataToUnwritableMemory((void*)dwAddress, &to, sizeof(to), false);
}

// Patches UINT32 value
void CPatch::PatchUINT32(uintptr_t dwAddress, uint32_t to)
{
	if (CPatch::ms_pLevelInfo->bDebugEnabled && *(uint32_t*)dwAddress != to)
		printf_MessageBox("PatchUINT32, address %p has different UINT32 value.\nOld value: 0x%X\nNew value: 0x%X",
			dwAddress,
			*(uint32_t*)dwAddress,
			to
		);

	WriteDataToUnwritableMemory((void*)dwAddress, &to, sizeof(to), false);
}

// Patches pointer
void CPatch::PatchPointer(uintptr_t dwAddress, const void* to)
{
	if (CPatch::ms_pLevelInfo->bDebugEnabled && *(void**)dwAddress != to)
		printf_MessageBox("PatchPointer, address %p has different void* value.\nOld value: %p\nNew value: %p",
		dwAddress,
		*(void**)dwAddress,
		to
		);

	WriteDataToUnwritableMemory((void*)dwAddress, &to, sizeof(to), false);
}

// Patches float value
void CPatch::PatchFloat(uintptr_t dwAddress, float to)
{
	if (CPatch::ms_pLevelInfo->bDebugEnabled && *(float*)dwAddress != to)
		printf_MessageBox("PatchFloat, address 0x%X has different float value.\nOld value: %f\nNew value: %f",
			dwAddress,
			*(float*)dwAddress,
			to
		);

	WriteDataToUnwritableMemory((void*)dwAddress, &to, sizeof(to), false);
}

#ifdef IS_ARCHITECTURE_X86
// Puts a call to function
void CPatch::PutCallFunction(uintptr_t dwAddress, const void* to)
{
	uint32_t movement = (uintptr_t)to - dwAddress - 5;

	EnterNewLevelAndDisableDebugState();

	PatchUINT8(dwAddress, 0xE8);		// call

	PatchUINT32(dwAddress + 1, movement);

	LeaveThisLevel();
}
#endif

// NOPs instruction (0x90)
#if defined(IS_ARCHITECTURE_ARM32)
// NOP instructions
void CPatch::NOPinstructions(eInstructionSet sourceInstructionSet, uintptr_t dwAddress, int iSize)
#else
// NOPs instruction (0x90)
void CPatch::NOPinstructions(uintptr_t dwAddress, int iSize)
#endif
{
	tMemoryPermissionChangeRequest request;
	request.lpAddress = (void*)dwAddress;
	request.dwSize = iSize;
	request.flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_EXECUTE_READWRITE);

	SetMemoryPermission(&request);

	if (!SetMemoryPermission(&request))
		throw f92_runtime_error("CPatch::NOPinstructions, unable to set R+W permission. Address = %p Error = %d", dwAddress, errno);

	#if defined(IS_ARCHITECTURE_X86) || defined(IS_ARCHITECTURE_X64)
	memset((void*)dwAddress, 0x90, iSize);
	#elif defined(IS_ARCHITECTURE_ARM32)
	if (sourceInstructionSet == INSTRUCTION_SET_THUMB)
	{
		for (int i = 0; i < iSize; i += 2)
		{
			*((unsigned char*)dwAddress + i + 0) = 0x00;
			*((unsigned char*)dwAddress + i + 1) = 0xBF;
		}
	}
	else if (sourceInstructionSet == INSTRUCTION_SET_ARM)
	{
		for (int i = 0; i < iSize; i += 4)
		{
			*((unsigned char*)dwAddress + i + 0) = 0x00;
			*((unsigned char*)dwAddress + i + 1) = 0xF0;
			*((unsigned char*)dwAddress + i + 2) = 0x20;
			*((unsigned char*)dwAddress + i + 3) = 0xE3;
		}
	}
	#elif defined(IS_ARCHITECTURE_ARM64)
	for (int i = 0; i < iSize; i += 4)
	{
		*(uint32_t*)dwAddress = 0xD503201F;
		*((unsigned char*)dwAddress + i + 0) = 0x1F;
		*((unsigned char*)dwAddress + i + 1) = 0x20;
		*((unsigned char*)dwAddress + i + 2) = 0x03;
		*((unsigned char*)dwAddress + i + 3) = 0xD5;
	}
	#endif

	// Restore old permission
	CPatch::RestoreOldExecuteReadPermission(&request, "CPatch::NOPinstructions", true);
}

unsigned int CPatch::RedirectCodeEx(
	eInstructionSet sourceInstructionSet,
	uintptr_t dwAddress,
	uintptr_t to,
	uintptr_t reportedNumberOfBytesOverwritten,
	eCodeRedirectOption options)
{
	return CPatch::RedirectCodeEx(sourceInstructionSet, dwAddress, (const void*)to, options);
}

unsigned int CPatch::RedirectCodeEx(
	eInstructionSet sourceInstructionSet,
	uintptr_t dwAddress,
	const void* to,
	uintptr_t reportedNumberOfBytesOverwritten,
	eCodeRedirectOption options)
{
	// Check options

	// Report an automated change
	if (reportedNumberOfBytesOverwritten)
		CPatch::ReportPointerIsGoingToBeChanged((void*)dwAddress, reportedNumberOfBytesOverwritten);

	unsigned int sizeOfData = 0;
	EnterNewLevelAndDisableDebugState();

	// Thumb trampoline may take 8 bytes (if address is aligned to value of 4) or 10 bytes.
	if (sourceInstructionSet == INSTRUCTION_SET_THUMB)
	{
		char code[12];

		if (dwAddress % 4 == 0)
		{
			*(uint32_t*)(code + 0) = 0xF000F8DF;	// // LDR.W             R0, [PC, #0]
			*(const void**)(code + 4) = to;	// pointer, where to jump
			sizeOfData = 8;
		}
		else
		{
			*(uint32_t*)(code + 0) = 0xBF00;	// NOP
			*(uint32_t*)(code + 2) = 0xF000F8DF;	// // LDR.W             R0, [PC, #0]
			
			*(const void**)(code + 6) = to;	// pointer, where to jump
			sizeOfData = 10;
		}

		CPatch::PatchMemoryData(dwAddress, code, sizeOfData, true);
	}
	else if (sourceInstructionSet == INSTRUCTION_SET_ARM)
	{
		char code[8];

		*(uint32_t*)(code + 0) = 0xE51FF004;	// // LDR             R0, [PC, #0]
		*(const void**)(code + 4) = to;	// pointer, where to jump
		sizeOfData = sizeof(code);
		CPatch::PatchMemoryData(dwAddress, code, sizeof(code), true);
	}
	else if (sourceInstructionSet == INSTRUCTION_SET_X86 || sourceInstructionSet == INSTRUCTION_SET_X64)
	{
		uint8_t data[5];

		intptr_t difference = (uintptr_t)to - dwAddress - 5;

		// WIN_X64 uses an external buffer to write a long code
		if (sourceInstructionSet == INSTRUCTION_SET_X64 && (difference < INT_MIN || difference > INT_MAX))
		{
			to = CPatch::AllocRedirection((uintptr_t)to, sourceInstructionSet);
			difference = (uintptr_t)to - dwAddress - 5;
		}

		data[0] = 0xE9;		// jmp
		*(uint32_t*)(data + 1) = difference;

		sizeOfData = 5;
		CPatch::PatchMemoryData(dwAddress, data, sizeOfData, true);

		// OutputFormattedDebugString("Difference: 0x%llX", difference);
	}
	else if (sourceInstructionSet == INSTRUCTION_SET_ARM64)
	{
		if (!(options & CODE_REDIRECT_NO_ALLOC_REDIRECTION))
		{
			uint32_t instruction;

			to = CPatch::AllocRedirection((uintptr_t)to, sourceInstructionSet,
				(options & CODE_REDIRECT_DO_NOT_SAVE_REGISTER) ? TRAMPOLINE_REGISTER_DO_NOTHING : TRAMPOLINE_REGISTER_SAVE_REGISTER
			);

			instruction = 0x14000000;

			intptr_t difference = ((uintptr_t)to - dwAddress) >> 2;

			if (difference < -(1 << 25) || difference > ((1 << 25) - 1))
				throw f92_runtime_error("CPatch::RedirectCodeEx unable to redirect the code from %p to %p difference: 0x%llX %d", dwAddress, to, difference, difference > ((2 << 25) - 1));

			instruction |= (difference) & ((2 << 26) - 1);
			sizeOfData = sizeof(instruction);

			CPatch::PatchMemoryData(dwAddress, &instruction, sizeOfData, true);
		}
		else
		{
			uint8_t code[20];

			uintptr_t target = (uintptr_t)to;

			*(uint32_t*)(code) = 0xD2800000 | 0x10 | ((target & 0xFFFF) << 5);	// movz x16, #(target & 0xFFFF)
			*(uint32_t*)(code + 4) = 0xF2A00000 | 0x10 | (((target >> 16) & 0xFFFF) << 5);	// movk x16, #((target >> 16) & 0xFFFF), lsl #16;
			*(uint32_t*)(code + 8) = 0xF2C00000 | 0x10 | (((target >> 32) & 0xFFFF) << 5);	// movk x16, #((target >> 32) & 0xFFFF), lsl #32;
			*(uint32_t*)(code + 12) = 0xF2E00000 | 0x10 | (((target >> 48) & 0xFFFF) << 5);	// movk x16, #((target >> 48) & 0xFFFF), lsl #48;
			*(uint32_t*)(code + 16) = 0xD61f0200;	// br X16

			sizeOfData = sizeof(code);

			CPatch::PatchMemoryData(dwAddress, &code, sizeOfData, true);
		}
	}

	CPatch::LeaveThisLevel();
	return sizeOfData;
}

#ifndef IS_ARCHITECTURE_ARM32
// Redirects code
unsigned int CPatch::RedirectCode(uintptr_t dwAddress, uintptr_t to, uintptr_t reportedNumberOfBytesOverwritten, eCodeRedirectOption options)
{
	return RedirectCode(dwAddress, (void*)to, reportedNumberOfBytesOverwritten, options);
}

unsigned int CPatch::RedirectCode(uintptr_t dwAddress, void* to, uintptr_t reportedNumberOfBytesOverwritten, eCodeRedirectOption options)
{
	return CPatch::RedirectCodeEx(
		CURRENT_PROCESSOR_INSTRUCTION_SET,
		dwAddress,
		to,
		reportedNumberOfBytesOverwritten,
		options
	);
}
#endif

unsigned int CPatch::RedirectFunction(uintptr_t functionJumpAddress, void* to, eCodeRedirectOption options)
{
	return CPatch::RedirectCodeEx(
		GET_INSTRUCTION_SET_FROM_ADDRESS(functionJumpAddress),
		GET_CODE_START(functionJumpAddress),
		to,
		0,
		(eCodeRedirectOption)(CODE_REDIRECT_DO_NOT_SAVE_REGISTER | options)
	);
}

#if defined(IS_ARCHITECTURE_X86) || defined(IS_ARCHITECTURE_X64)
void CPatch::RedirectCodeOneByte(uintptr_t dwAddress, uintptr_t to)
{
	RedirectCodeOneByte(dwAddress, (void*)to);
}

void CPatch::RedirectCodeOneByte(uintptr_t dwAddress, void* to)
{
	uint8_t movement = (uint8_t)((uintptr_t)to - dwAddress - 2);

	EnterNewLevelAndDisableDebugState();

	PatchUINT8(dwAddress, 0xEB);		// jmp

	PatchUINT8(dwAddress + 1, movement);

	LeaveThisLevel();
}

void CPatch::PatchRelative32bitReference(uintptr_t sourceAddress, unsigned int numberOfBytesToEndOfInstruction, uintptr_t destination)
{
	CPatch::PatchRelative32bitReference(sourceAddress, numberOfBytesToEndOfInstruction, (const void*)destination);
}

void CPatch::PatchRelative32bitReference(uintptr_t sourceAddress, unsigned int numberOfBytesToEndOfInstruction, const void* destination)
{
	uint32_t newOffset = (uint32_t)((uintptr_t)destination - sourceAddress - 4 - numberOfBytesToEndOfInstruction);

	if (CPatch::ms_pLevelInfo->bDebugEnabled)
	{
		uintptr_t oldDestination = ((uintptr_t)*(uint32_t*)sourceAddress) + sourceAddress + 4 + numberOfBytesToEndOfInstruction;

		if (oldDestination != (uintptr_t)destination)
			printf_MessageBox("PatchRelative32bitReference, address 0x%p has different offset value.\nOld value: 0x%p\nNew value: 0x%p",
				sourceAddress,
				oldDestination,
				destination
			);
	}

	CPatch::WriteDataToUnwritableMemory((void*)sourceAddress, &newOffset, sizeof(newOffset), true);
}

void CPatch::PutOnAddressRelative4byteAddressToAddress(uintptr_t sourceAddress, uintptr_t destination)
{
	uint32_t movement = (uint32_t)(destination - sourceAddress - 4);

	EnterNewLevelAndDisableDebugState();

	PatchUINT32(sourceAddress, movement);

	LeaveThisLevel();
}

void CPatch::PutOnAddressRelative4byteAddressToAddress(uintptr_t sourceAddress, const void* destination)
{
	CPatch::PutOnAddressRelative4byteAddressToAddress(sourceAddress, (uintptr_t)destination);
}
#endif

// Performs task for memory address
void CPatch::DoTasksForMemoryAddress(void* dwAddress, int iSize)
{
	CPatch::CheckIfNotForbiddenAddress(dwAddress, iSize);

#ifdef FASTMAN92_LIMIT_ADJUSTER
	if (CPatch::ms_pLevelInfo->bDumpMemoryAddressesToLogFile)
	{
		CGenericLogStorage::SaveFormattedTextLn(
			"Processor.ProcessPointer(0x%X); // data size: %d",
			dwAddress,
			iSize
		);
	}
#endif

	CPatch::ms_numberOfMemoryChanges++;
}

#ifdef FASTMAN92_LIMIT_ADJUSTER
// Makes a function return
void CPatch::DisableFunctionByName(const char* name)
{
	#ifdef IS_PLATFORM_ANDROID_ARM32
	uintptr_t address = (uintptr_t)dlsym(g_LimitAdjuster.hModule_of_game.linux_os, name);

	if (!address)
		return;

	EnterNewLevelAndDisableDebugState();

	if (address % 2)	// is THUMB?
	{
		address = address & (~1);
		CPatch::PatchUINT16(address, 0x4770);	// BX LR
	}

	CPatch::LeaveThisLevel();
	#endif
}
#endif

// #include <bits/stdc++.h>

// Writes data to memory
void CPatch::WriteDataToUnwritableMemory(void* dwAddress, const void* bData, int iSize, bool bMustBeExecutable)
{
	CPatch::DoTasksForMemoryAddress(dwAddress, iSize);	
	
	tMemoryPermissionChangeRequest request;
	request.lpAddress = dwAddress;
	request.dwSize = iSize;

	request.flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_EXECUTE_READWRITE);
	
#if 0 && FASTMAN92_LIMIT_ADJUSTER
	int pagesize = sysconf(_SC_PAGE_SIZE);

	char *start =
		(char *)(((uintptr_t)request.lpAddress) & ~(pagesize - 1));
	char *end =
		(char *)(((uintptr_t)request.lpAddress + request.dwSize + pagesize - 1) & ~(pagesize - 1));


	if (g_mCalc.GetCurrentVAbyPreferedVA(0x470000) >= (uintptr_t)start && g_mCalc.GetCurrentVAbyPreferedVA(0x470000) < (uintptr_t)end)
		OutputFormattedDebugString("here: %p", g_mCalc.GetPreferedVAbyCurrentVA((uintptr_t)request.lpAddress));
#endif

	if (!SetMemoryPermission(&request))
	{
		if (!bMustBeExecutable)
		{
			request.flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_READWRITE);

			if (!SetMemoryPermission(&request))
				throw f92_runtime_error("CPatch::WriteDataToMemory, unable to set R+W permission. Address = %p Error = %d", dwAddress, errno);
		}
		else
			throw f92_runtime_error("CPatch::WriteDataToMemory, unable to set R+W+X permission. Address = %p Error = %d", dwAddress, errno);
	}
	
	memcpy(dwAddress, bData, iSize);

	CPatch::RestoreOldExecuteReadPermission(&request, "CPatch::WriteDataToMemory", bMustBeExecutable);
}

// Restores old permission
void CPatch::RestoreOldExecuteReadPermission(tMemoryPermissionChangeRequest* pRequest, const char* functionName, bool bMustBeExecutable)
{
	// Restore old permission
	if (pRequest->bIsOldProtectSet)
		pRequest->flNewProtect = pRequest->lpflOldProtect;
	else
		pRequest->flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_EXECUTE_READ);

	if (!SetMemoryPermission(pRequest))
	{
		if (!bMustBeExecutable)
		{
			pRequest->flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_READWRITE);

			if (!SetMemoryPermission(pRequest))
				throw f92_runtime_error("%s, unable to set R+W permission again. Address = %p Error = %d", functionName, pRequest->lpAddress, errno);
		}
		else
			throw f92_runtime_error("%s, unable to set R+X permission again. Address = %p Error = %d", functionName, pRequest->lpAddress, errno);
	}
}

// Checks if address is not forbidden
void CPatch::CheckIfNotForbiddenAddress(const void* dwAddress, uint32_t size)
{
	if (!CPatch::ms_pLevelInfo->bPatchForbiddenCheck)
		return;

	for (int i = 0; i < CPatch::ms_numOfForbiddenMemoryRegions; i++)
	{
		tForbiddenMemoryRegion* pRegion = &CPatch::ms_forbiddenMemoryRegionArray[i];

		if (dwAddress >= pRegion->start && dwAddress < pRegion->end)
			printf_MessageBox("Forbidden address patched\ndwAddress = 0x%X\nsize = %d", dwAddress, size);
	}
}

// Allocates a redirection, returns a pointer to the redirection code
const void* CPatch::AllocRedirection(uintptr_t target, eInstructionSet instructionSet, eTrampolineRegister trampolineRegisterAction)
{
#if IS_PLATFORM_ANDROID
	return ::AllocRedirection(target, 0, trampolineRegisterAction);
#else
	if (instructionSet == INSTRUCTION_SET_X64)
	{
		uint8_t data[16];

		// WIN_X64 uses an external buffer to write a long code
		*(uint16_t*)data = 0x35FF;	// push TARGET_ADDRESS
		*(uint32_t*)(data + 2) = 2;
		*(uint8_t*)(data + 6) = 0xC3;	// retn
		*(uint8_t*)(data + 7) = 0x90;
		*(uint64_t*)(data + 8) = (uint64_t)target;

		return CPatch::WriteDataToBuffer(data, 16, 8);
	}
#endif

	return nullptr;
}

// Sets pointer
void CPatch::SetPointer(uintptr_t& variable, void* newPtr)
{
	if (CPatch::ms_pLevelInfo->bDebugEnabled && (void*)variable != newPtr)
		printf_MessageBox("SetPointer, address on variable has different void* value.\nOld value: %p\nNew value: %p",
			variable,
			newPtr
		);

	variable = (uintptr_t)newPtr;
}

// Allocates buffer memory
void CPatch::AllocateBufferMemory()
{
	CPatch::pMemory = 0;
	CPatch::memoryPos = 0;

	CPatch::pMemory = (uint8_t*)CMemoryAllocation::malloc_in_app_space(CPatch::sizeOfMemory);
}

// Moves buffer ahead before writing the data
void* CPatch::MoveBufferAhead(size_t size, size_t alignment)
{
	if (size > CPatch::sizeOfMemory)	// it can never be written as it would over maximum size of memory
		return NULL;

	// Align
	while (CPatch::memoryPos % alignment != 0)
		CPatch::memoryPos++;

	if (CPatch::memoryPos + size > CPatch::sizeOfMemory)
	{
		CPatch::AllocateBufferMemory();

		// Align
		while (CPatch::memoryPos % alignment != 0)
			CPatch::memoryPos++;

		if (CPatch::memoryPos + size > CPatch::sizeOfMemory)
			return NULL;
	}

	return CPatch::pMemory + CPatch::memoryPos;
}

// Writes data to buffer
void* CPatch::WriteDataToBuffer(const void* ptr, size_t size, size_t alignment)
{
	if (!CPatch::MoveBufferAhead(size, alignment))
		throw f92_runtime_error("CPatch::WriteDataToBuffer, no more space");

	memcpy(CPatch::pMemory + CPatch::memoryPos, ptr, size);
	void* retPtr = CPatch::pMemory + CPatch::memoryPos;
	CPatch::memoryPos += size;
	return retPtr;
}

// Checks if pointer wasn't changed before.
void CPatch::ReportPointerIsGoingToBeChanged(void* dwAddress, size_t size)
{
	#ifdef FASTMAN92_LIMIT_ADJUSTER

	#if PROJECT_USE_DEVELOPMENT_INI
	// verify if pointer wasn't already changed
	for (std::vector<tChangedPointer>::iterator it = m_ListOfPointersChanged.begin(); it != m_ListOfPointersChanged.end(); ++it)
	{
		if (((uintptr_t)dwAddress >= (uintptr_t)it->ptr && (uintptr_t)dwAddress < (uintptr_t)it->ptr + it->size)
			||
			((uintptr_t)dwAddress + size > (uintptr_t)it->ptr && (uintptr_t)dwAddress + size < (uintptr_t)it->ptr + it->size)
			)
		{			
			// printf_MessageBox("CPatch\nAddress 0x%lX had already been changed!", (uint64_t)dwAddress);

			CGenericLogStorage::SaveFormattedTextLn("CPatch, address %p has already been changed!", dwAddress);
			break;
		}
	}
	#endif

	// Add new pointer
	tChangedPointer changedPtrInfo;

	changedPtrInfo.ptr = dwAddress;
	changedPtrInfo.size = size;

	unsigned int sizeToCopy;

	if (size > sizeof(changedPtrInfo.oldData))
		sizeToCopy = sizeof(changedPtrInfo.oldData);
	else
		sizeToCopy = size;

	memcpy(changedPtrInfo.oldData, dwAddress, sizeToCopy);

	m_ListOfPointersChanged.push_back(changedPtrInfo);
	#endif
}
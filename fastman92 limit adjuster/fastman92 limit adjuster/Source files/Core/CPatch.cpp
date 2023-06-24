
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPatch.h"
#include "CGenericLogStorage.h"
#include "FormattedOutput.h"
#include "MemoryAllocation.h"

#include <MemoryPermission\MemoryPermission.h>

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
void CPatch::PatchMemoryData(uintptr_t dwAddress, const void* bData, int iSize)
{
	if (CPatch::ms_pLevelInfo->bDebugEnabled && memcmp((void*)dwAddress, bData, iSize))
		printf_MessageBox("PatchMemoryData, address %p has different data. Compared %d bytes", dwAddress, iSize);

	WriteDataToMemory((void*)dwAddress, bData, iSize);
}

// Patches UINT8 value
void CPatch::PatchUINT8(uintptr_t dwAddress, uint8_t to)
{		
	if (CPatch::ms_pLevelInfo -> bDebugEnabled && *(uint8_t*)dwAddress != to)
		printf_MessageBox("PatchUINT8, address %p has different UINT8 value.\nOld value: 0x%02X\nNew value: 0x%02X",
		dwAddress,
		*(uint8_t*)dwAddress,
		to
		);

	WriteDataToMemory((void*)dwAddress, &to, sizeof(to));
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

	WriteDataToMemory((void*)dwAddress, &to, sizeof(to));
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

	WriteDataToMemory((void*)dwAddress, &to, sizeof(to));
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

	WriteDataToMemory((void*)dwAddress, &to, sizeof(to));
}

// Patches float value
void CPatch::PatchFloat(uintptr_t dwAddress, float to)
{
	if (CPatch::ms_pLevelInfo -> bDebugEnabled && *(float*)dwAddress != to)
		printf_MessageBox("PatchFloat, address 0x%X has different float value.\nOld value: %f\nNew value: %f",
		dwAddress,
		*(float*)dwAddress,
		to
		);

	WriteDataToMemory((void*)dwAddress, &to, sizeof(to));
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
	#endif

	// Restore old permission
	if (request.bIsOldProtectSet)
	{
		request.flNewProtect = request.lpflOldProtect;
		SetMemoryPermission(&request);
	}
}

unsigned int CPatch::RedirectCodeEx(
	eInstructionSet sourceInstructionSet,
	uintptr_t dwAddress,
	uintptr_t to,
	uintptr_t reportedNumberOfBytesOverwritten)
{
	return CPatch::RedirectCodeEx(sourceInstructionSet, dwAddress, (const void*)to);
}

unsigned int CPatch::RedirectCodeEx(
	eInstructionSet sourceInstructionSet,
	uintptr_t dwAddress,
	const void* to,
	uintptr_t reportedNumberOfBytesOverwritten,
	bool doNotSaveRegister)
{
	// Report an automated change
	if (reportedNumberOfBytesOverwritten)
		CPatch::ReportPointerIsGoingToBeChanged((void*)dwAddress, reportedNumberOfBytesOverwritten);

	unsigned int sizeOfData = 0;
	EnterNewLevelAndDisableDebugState();

	// Thumb trampoline may take 8 bytes (if address is aligned to value of 4) or 10 bytes.
	if (sourceInstructionSet == INSTRUCTION_SET_THUMB)
	{
		char code[12];
		unsigned int sizeOfData = 0;

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

		CPatch::PatchMemoryData(dwAddress, code, sizeOfData);
	}
	else if (sourceInstructionSet == INSTRUCTION_SET_ARM)
	{
		char code[8];

		*(uint32_t*)(code + 0) = 0xE51FF004;	// // LDR             R0, [PC, #0]
		*(const void**)(code + 4) = to;	// pointer, where to jump
		CPatch::PatchMemoryData(dwAddress, code, sizeof(code));
	}
	else if (sourceInstructionSet == INSTRUCTION_SET_X86 || sourceInstructionSet == INSTRUCTION_SET_X64)
	{
		uint8_t data[16];

		// WIN_X64 uses an external buffer to write a long code
		if (sourceInstructionSet == INSTRUCTION_SET_X64)
			to = CPatch::AllocRedirection((uintptr_t)to, sourceInstructionSet);
		
		uintptr_t movement = (uintptr_t)to - dwAddress - 5;

		data[0] = 0xE9;		// jmp
		*(uint32_t*)(data + 1) = movement;

		sizeOfData = 5;
		CPatch::PatchMemoryData(dwAddress, data, sizeOfData);
	}
	else if (sourceInstructionSet == INSTRUCTION_SET_ARM64)
	{
		uint32_t instruction;
		to = CPatch::AllocRedirection((uintptr_t)to, sourceInstructionSet,
			doNotSaveRegister ? TRAMPOLINE_REGISTER_DO_NOTHING : TRAMPOLINE_REGISTER_SAVE_REGISTER
		);
		instruction = 0x14000000;
		instruction |= (((uintptr_t)to - dwAddress) >> 2) & ((2 << 26) - 1);

		CPatch::PatchMemoryData(dwAddress, &instruction, sizeof(instruction));
	}

	CPatch::LeaveThisLevel();
	return sizeOfData;
}

#ifndef IS_ARCHITECTURE_ARM32
// Redirects code
unsigned int CPatch::RedirectCode(uintptr_t dwAddress, uintptr_t to, uintptr_t reportedNumberOfBytesOverwritten)
{
	return RedirectCode(dwAddress, (void*)to, reportedNumberOfBytesOverwritten);
}

unsigned int CPatch::RedirectCode(uintptr_t dwAddress, void* to, uintptr_t reportedNumberOfBytesOverwritten)
{
	return CPatch::RedirectCodeEx(
		CURRENT_PROCESSOR_INSTRUCTION_SET,
		dwAddress,
		to,
		reportedNumberOfBytesOverwritten
	);
}
#endif

void CPatch::RedirectFunction(uintptr_t functionJumpAddress, void* to)
{
	CPatch::RedirectCodeEx(
		GET_INSTRUCTION_SET_FROM_ADDRESS(functionJumpAddress),
		GET_CODE_START(functionJumpAddress),
		to,
		0,
		true
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

	WriteDataToMemory((void*)sourceAddress, &newOffset, sizeof(newOffset));
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
void CPatch::WriteDataToMemory(void* dwAddress, const void* bData, int iSize)
{
	CPatch::DoTasksForMemoryAddress(dwAddress, iSize);	
	
	tMemoryPermissionChangeRequest request;
	request.lpAddress = dwAddress;
	request.dwSize = iSize;

	request.flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_READWRITE);

	if (!SetMemoryPermission(&request))
		throw f92_runtime_error("CPatch::WriteDataToMemory, unable to set R+W permission. Error = %d", errno);
	
	memcpy(dwAddress, bData, iSize);

	// Restore old permission
	if (request.bIsOldProtectSet)
	{
		request.flNewProtect = request.lpflOldProtect;

		if(!SetMemoryPermission(&request))
			throw f92_runtime_error("CPatch::WriteDataToMemory, unable to set previous permission again. Error = %d", errno);
	}
	else
	{
		request.flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_EXECUTE_READ);

		if(!SetMemoryPermission(&request))
			throw f92_runtime_error("CPatch::WriteDataToMemory, unable to set R+E permission again. Error = %d", errno);
	}
}

// Checks if address is not forbidden
void CPatch::CheckIfNotForbiddenAddress(const void* dwAddress, uint32_t size)
{
	if(!CPatch::ms_pLevelInfo -> bPatchForbiddenCheck)
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
	else if (instructionSet == INSTRUCTION_SET_ARM64)
	{
		#if IS_PLATFORM_ANDROID
		return ::AllocRedirection(target, 0, trampolineRegisterAction);
		#endif
	}

	return nullptr;
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
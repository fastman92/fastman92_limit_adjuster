/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "MemoryAllocation.h"

#include "FormattedOutput.h"

#include <stdint.h>
#ifdef IS_PLATFORM_WIN
#include <Windows.h>
#elif defined(IS_PLATFORM_ANDROID)
#include <unistd.h>
#endif

#include <list>

#include <stdio.h>

void* CMemoryAllocation::AllocateNearTheAddress(void* pAddress, uint32_t sizeToBeAllocated, uint32_t maxDifference)
{
#ifdef IS_PLATFORM_WIN
	LPVOID pMaxAddr = (char*)pAddress + maxDifference;
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	DWORD dwAllocationGranularity = si.dwAllocationGranularity;

	ULONG_PTR tryAddr = (ULONG_PTR)pAddress;

	// Round down to the next allocation granularity.
	tryAddr -= tryAddr % dwAllocationGranularity;

	// Start from the next allocation granularity multiply.
	tryAddr += dwAllocationGranularity;

	while (tryAddr <= (ULONG_PTR)pMaxAddr)
	{
		MEMORY_BASIC_INFORMATION mbi;
		if (VirtualQuery((LPVOID)tryAddr, &mbi, sizeof(MEMORY_BASIC_INFORMATION)) == 0)
			break;

		if (mbi.State == MEM_FREE &&  mbi.RegionSize >= sizeToBeAllocated)
			return VirtualAlloc(
				(void*)tryAddr, sizeToBeAllocated, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

		tryAddr = (ULONG_PTR)mbi.BaseAddress + mbi.RegionSize;

		// Round up to the next allocation granularity.
		tryAddr += dwAllocationGranularity - 1;
		tryAddr -= tryAddr % dwAllocationGranularity;
	}

	return NULL;
#elif defined(IS_PLATFORM_ANDROID)
	return NULL;	// disable the code

	pid_t processID = getpid();

	char procFilename[PATH_MAX];

	sprintf(procFilename, "/proc/self/mem", processID);


	FILE* fp = fopen(procFilename, "r");

	if (!fp)
		return NULL;

	char line[1024];
	line[0] = 0;

	OutputFormattedDebugString("Start of line reading: %d", processID);

	while (fgets(line, sizeof(line), fp))
	{

		// strcpy(line, "40088000-4008d000 r-xp 00000000 b3:13 5055       /system/bin/app\n");


		// /(ANDROID_LOG_INFO, PROJECT_NAME, "%s", line);	
	}

	fclose(fp);

	return NULL;
#else
	return NULL;
#endif
}

/*
struct tAllocatedPtr
{
	char* ptr;
	size_t sizeRequested;
	size_t sizeAllocated;
};

static std::list<tAllocatedPtr> AllocatedPtrsList;
*/

void* CMemoryAllocation::malloc_in_app_space(size_t size)
{
#ifdef IS_PLATFORM_WIN_X64
	return AllocateNearTheAddress((void*)g_mCalc.GetCurrentModuleBase(),
		size,
		500 * 1024 * 1024
	);

	/*
#elif defined(IS_PLATFORM_ANDROID)
	return AllocateNearTheAddress((void*)g_mCalc.GetCurrentModuleBase(),
		size,
		8 * 1024 * 1024
	);
	*/
#else
	return new char[size];
#endif
}

void CMemoryAllocation::free_in_app_space(void* ptr)
{
#ifdef IS_PLATFORM_WIN_X64
	// FASTMAN92_TODO
	VirtualFree(ptr, 0, MEM_RELEASE);
#else
	delete[] ptr;
#endif
}

void* operator new(size_t size, tMemoryInGameSpaceDummy*)
{	
	return CMemoryAllocation::malloc_in_app_space(size);
}

void* operator new[] (size_t size, tMemoryInGameSpaceDummy*)
{
	return CMemoryAllocation::malloc_in_app_space(size);
}

void operator delete(void* ptr, size_t, tMemoryInGameSpaceDummy*)
{
	return CMemoryAllocation::free_in_app_space(ptr);
}

void operator delete[](void* ptr, size_t, tMemoryInGameSpaceDummy*)
{
	return CMemoryAllocation::free_in_app_space(ptr);
}
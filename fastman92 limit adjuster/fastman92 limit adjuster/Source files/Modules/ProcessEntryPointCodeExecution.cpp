/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#include "ProcessEntryPointCodeExecution.h"

#include "../Core/CPatch.h"
#include "../Core/DynamicAssert.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include <Array\countof.h>

CProcessEntryPointCodeExecution g_ProcessEntryPointCodeExecution;

using namespace Game;

// Initialize
void CProcessEntryPointCodeExecution::Initialise()
{
	this->m_numberOfCallbacksRegistered = 0;
}

// Adds callback
void CProcessEntryPointCodeExecution::AddCallback(tProcessEntryPointFunction function, void* pCustomData)
{
	if (m_numberOfCallbacksRegistered >= _countof(this->m_callbackList))
		throw f92_runtime_error(
			"Too many elements into CProcessEntryPointCodeExecution function list"
		);

	tProcessEntryPointCallback* pCallback
		= &this->m_callbackList[this->m_numberOfCallbacksRegistered++];

	pCallback->funcPtr = function;
	pCallback->pCustomData = pCustomData;
}

// Original entry point of process
static void(*originalProcessEntryPoint) ();

// Number of bytes written to prolog
static unsigned int numberOfBytesWrittenToOriginalEntryPoint;
static char originalEntryPointPrologData[5];


// New process entry point
static void newProcessEntryPoint()
{
	printf_MessageBox("hedre");

	// Execute additional functions
	for (unsigned int i = 0; i < g_ProcessEntryPointCodeExecution.m_numberOfCallbacksRegistered; i++)
	{
		const tProcessEntryPointCallback* pCallback = &g_ProcessEntryPointCodeExecution.m_callbackList[i];
		pCallback->funcPtr(pCallback->pCustomData);
	}

	// Enter new patching level and disable a check of forbidden address
	CPatch::EnterNewLevel();
	
	CPatch::ms_pLevelInfo->bPatchForbiddenCheck = false;

	// Restore bytes from original entry point
	CPatch::PatchMemoryData(
		(uintptr_t)originalProcessEntryPoint,
		originalEntryPointPrologData,
		numberOfBytesWrittenToOriginalEntryPoint);
	
	// Leave a patching level
	CPatch::LeaveThisLevel();

	// Flush instruction cache
#if IS_PLATFORM_WIN
	FlushInstructionCache(GetCurrentProcess(), originalProcessEntryPoint, 5);
#endif

	// Execute original entry point
	originalProcessEntryPoint();
}

// Applies the patch
void CProcessEntryPointCodeExecution::ApplyHook()
{
	///////////////
	// It turns out that the FLA loads already after starting an entry point of process.
	// All the code here was written unneccessarily.
	return;

#if 0

	if (this->m_numberOfCallbacksRegistered == 0)
		return;

#if defined(IS_ARCHITECTURE_X86) || defined(IS_ARCHITECTURE_X64)
	PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)g_mCalc.GetPreferedModuleBase();
	PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((uintptr_t)(dosHeader)+(dosHeader->e_lfanew));

	uintptr_t moduleBaseAddress = g_mCalc.GetCurrentModuleBase();

	originalProcessEntryPoint = (void(*)())(ntHeader->OptionalHeader.AddressOfEntryPoint
		+ moduleBaseAddress);

	memcpy(originalEntryPointPrologData, originalProcessEntryPoint, sizeof(originalEntryPointPrologData));
	

	// Enter new patching level and disable a check of forbidden address
	CPatch::EnterNewLevel();

	CPatch::ms_pLevelInfo->bPatchForbiddenCheck = false;

	numberOfBytesWrittenToOriginalEntryPoint =
		CPatch::RedirectCode((uintptr_t)originalProcessEntryPoint, (void*)&newProcessEntryPoint);

	// Leave a patching level
	CPatch::LeaveThisLevel();

	FLA_dynamic_assert(
		numberOfBytesWrittenToOriginalEntryPoint == sizeof(originalEntryPointPrologData),
		"Process entry point stuff, the code needs to be updated."
		);

	/*
	CPatch::PatchUINT32(
		(uintptr_t)&ntHeader->OptionalHeader.AddressOfEntryPoint,
		(uintptr_t)&myEntryPoint - moduleBaseAddress
	);
	*/
#endif

#endif
}
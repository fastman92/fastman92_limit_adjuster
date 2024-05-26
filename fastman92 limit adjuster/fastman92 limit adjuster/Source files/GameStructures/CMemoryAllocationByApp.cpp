/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CMemoryAllocationByApp.h"

#include "../Core/LimitAdjuster.h"

CMemoryAllocationByApp g_memoryAllocationByApp;

static uintptr_t Address_new = 0;

void* operator new(size_t size, tMemoryAllocateByApp*)
{	
	return g_memoryCall.Function<void*>(Address_new, size);
}

static uintptr_t Address_new_array = 0;

void* operator new[] (size_t size, tMemoryAllocateByApp*)
{
	return g_memoryCall.Function<void*>(Address_new_array, size);
}

static uintptr_t Address_delete = 0;

void operator delete(void* ptr, size_t size, tMemoryAllocateByApp*)
{
	g_memoryCall.Function<void*>(Address_delete, ptr);
}

static uintptr_t Address_delete_array = 0;

void operator delete[](void* ptr, size_t size, tMemoryAllocateByApp*)
{
	g_memoryCall.Function<void*>(Address_delete_array, ptr);
}

// Inits function memory addresses
void CMemoryAllocationByApp::Initialise()
{
	if (!g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		return;

	MAKE_VAR_GAME_VERSION();

#if defined(IS_PLATFORM_ANDROID)
	Address_new = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_Znwm"
	);

	if(!Address_new)
		Address_new = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_Znwj"
		);

	///////
	Address_delete = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZdlPv"
	);

	if(!Address_delete)
		Address_delete = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZdlPv"
		);


	//////////
	Address_delete_array = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_ZdlPv"
	);

	if (!Address_delete_array)
		Address_delete = (uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZdaPv"
		);
#endif
}
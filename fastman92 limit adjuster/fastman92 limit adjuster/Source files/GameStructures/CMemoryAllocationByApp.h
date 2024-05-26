/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

#include <stdint.h>

class tMemoryAllocateByApp {};

void* operator new (size_t size, tMemoryAllocateByApp*);
void* operator new[](size_t size, tMemoryAllocateByApp*);

void operator delete(void*, size_t, tMemoryAllocateByApp*);
void operator delete[](void*, size_t, tMemoryAllocateByApp*);

#define new_by_app new((tMemoryAllocateByApp*)0)
#define delete_by_app_single(single) operator delete(single, sizeof(*single), (tMemoryAllocateByApp*)0)
#define delete_by_app_space_array(array) operator delete[](array, sizeof(*array), (tMemoryAllocateByApp*)0)

class CMemoryAllocationByApp : public CLimitAdjusterModule
{
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {};
};

extern CMemoryAllocationByApp g_memoryAllocationByApp;
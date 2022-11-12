/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#include "LimitAdjuster.h"

class tMemoryInGameSpaceDummy {};

void* operator new (size_t size, tMemoryInGameSpaceDummy*);
void* operator new[](size_t size, tMemoryInGameSpaceDummy*);

void operator delete(void*, size_t, tMemoryInGameSpaceDummy*);
void operator delete[](void*, size_t, tMemoryInGameSpaceDummy*);

#define new_in_app_space new((tMemoryInGameSpaceDummy*)0)
#define delete_in_app_space_single(single) operator delete(single, sizeof(*single), (tMemoryInGameSpaceDummy*)0)
#define delete_in_app_space_array(array) operator delete[](array, sizeof(*array), (tMemoryInGameSpaceDummy*)0)


class CMemoryAllocation
{
private:
	static void* AllocateNearTheAddress(void* pAddress, uint32_t sizeToBeAllocated, uint32_t maxDifference);

public:
	static void* malloc_in_app_space(size_t size);
	static void free_in_app_space(void* ptr);
};

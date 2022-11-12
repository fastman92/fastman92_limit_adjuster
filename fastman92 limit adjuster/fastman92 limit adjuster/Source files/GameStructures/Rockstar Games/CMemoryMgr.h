/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#pragma once
#include <Assertions.h>
#include <stdint.h>

#include "../../Core/CLimitAdjusterModule.h"

class CMemoryMgr
{
public:
	static void* Malloc(size_t size);
	static void Free(void* ptr);
};

class CMemoryMgr_varInitialisation : public CLimitAdjusterModule
{
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {};
};

extern CMemoryMgr_varInitialisation g_CMemoryMgr_varInitialisation;
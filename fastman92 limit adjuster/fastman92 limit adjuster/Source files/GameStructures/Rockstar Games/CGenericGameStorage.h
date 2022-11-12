/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../../Core/CLimitAdjusterModule.h"

#include <stdint.h>

class CGenericGameStorage
{
public:
	static char** ms_WorkBuffer;

	static unsigned int* ms_FilePos;
	static unsigned int* ms_WorkBufferSize;
	static unsigned int* ms_WorkBufferPos;

	// Checksum
	static uint32_t* ms_CheckSum;

	// Writes to save file
	static int SaveDataToWorkBuffer(const void *pSource, int Size);

	// Reads to save file
	static bool LoadDataFromWorkBuffer(void *ptr, unsigned int numOfBytes);
};

class CGenericGameStorage_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown() {}
};

extern CGenericGameStorage_VarInitialisation g_CGenericGameStorage_VarInitialisation;
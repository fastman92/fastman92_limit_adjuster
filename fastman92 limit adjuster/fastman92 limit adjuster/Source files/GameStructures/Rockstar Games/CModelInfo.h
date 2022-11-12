/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../../Core/CLimitAdjusterModule.h"
#include "CBaseModelInfo.h"

#include <Assertions.h>

#include <stdint.h>

class CModelInfo : public CLimitAdjusterModule
{
public:
	// Returns pointer to model info
	static CBaseModelInfo_generic * GetModelInfo(const char *modelName, int *pIndex);
};

class CModelInfo_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern CModelInfo_VarInitialisation g_CModelInfo_varInitialisation;
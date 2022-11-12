/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <stdint.h>

#include "../../Core/CLimitAdjusterModule.h"

class CKeyGen
{
public:
	// Returns hash of upper case key
	static uint32_t GetUppercaseKey(const char*);
};

class CKeygen_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern CKeygen_VarInitialisation g_CKeygen_varInitialization;
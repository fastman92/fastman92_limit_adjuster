/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../../Core/CLimitAdjusterModule.h"

class CText
{
public:
	// Returns the pointer to text
	// May return NULL
	const void* Get(const char* GXTkey);
};

class CText_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern CText_VarInitialisation g_CText_VarInitialisation;
extern CText* TheText;
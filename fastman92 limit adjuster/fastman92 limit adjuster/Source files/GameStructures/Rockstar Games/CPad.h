/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../../Core/CLimitAdjusterModule.h"

// typedef void CPad;
class CPad
{
public:
	// Returns a pointer to pad structure
	static CPad* GetPad(int padNumber);
};

class CPad_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern CPad_VarInitialisation g_CPad_varInitialisation;
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#include "../../Core/CLimitAdjusterModule.h"

class CWorld
{
public:
	// Finds ground Z for XY coordinates
	static float FindGroundZForCoord(float x, float y);
};

class CWorld_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern CWorld_VarInitialisation g_CWorld_varInitialisation;
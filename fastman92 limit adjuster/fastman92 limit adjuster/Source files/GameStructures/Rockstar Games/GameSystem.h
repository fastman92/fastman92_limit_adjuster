/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "../../Core/CLimitAdjusterModule.h"

class CGameSystem
{
public:
	static unsigned int ScreenGetWidth();
	static unsigned int ScreenGetHeight();
};

class CGameSystem_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern CGameSystem_VarInitialisation g_CSystem_varInitialisation;
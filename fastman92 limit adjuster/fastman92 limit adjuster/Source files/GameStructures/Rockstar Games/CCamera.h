/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#include "CEntity.h"

#include "../../Core/CLimitAdjusterModule.h"

class CCamera
{
public:
	void TakeControl(CEntity *, short, short, int);
};

extern CCamera* TheCamera;

class CCamera_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern CCamera_VarInitialisation g_CCamera_varInitialisation;
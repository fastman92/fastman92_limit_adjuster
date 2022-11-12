/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

class CoordinateMover : public CLimitAdjusterModule
{		
public:
	float m_fRelativePosX;
	float m_fRelativePosY;
	float m_fRelativePosZ;

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown() {}

	// Applies patch of coordinate mover.
	static void ApplyHook();
};

extern CoordinateMover g_coordinateMover;
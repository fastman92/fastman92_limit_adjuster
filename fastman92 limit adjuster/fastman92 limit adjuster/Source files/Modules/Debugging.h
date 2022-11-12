/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

class Debugging : public CLimitAdjusterModule
{
public:
	// Initialize
	virtual void Initialise() {}

	// Shutdown
	virtual void Shutdown() {}

	// Sets pad 1 to act like pad 0
	void SetPad1actLikePad0();
};

extern Debugging g_debugging;
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

class ExecutableCode : public CLimitAdjusterModule
{
public:
	// Initialize
	virtual void Initialise() {}

	// Shutdown
	virtual void Shutdown() {}

	// Give it a try
	void TryItOut();
};

extern ExecutableCode g_executableCode;
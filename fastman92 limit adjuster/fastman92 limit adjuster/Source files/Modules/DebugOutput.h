/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

class DebugOutput : public CLimitAdjusterModule
{
public:
	// Initialize
	virtual void Initialise() {}

	// Shutdown
	virtual void Shutdown() {};

	// Enables debug output
	void EnableDebugOutput();

	// Enables logging of files loaded
	void EnableLoggingOfFilesLoaded();

	// Redirects game new and delete to the FLA
	void RedirectGameNewAndDeleteToTheFLA();
};

extern DebugOutput g_debugOutput;
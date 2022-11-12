/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

class BringBackTextureArchives : public CLimitAdjusterModule
{
	// Initialize
	virtual void Initialise() {}

	// Shutdown
	virtual void Shutdown() {}
};

extern BringBackTextureArchives g_BringBackTextureArchives;
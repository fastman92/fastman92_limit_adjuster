/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

class Options : public  CLimitAdjusterModule
{
public:
	// Initialize
	virtual void Initialise() {}

	// Shutdown
	virtual void Shutdown() {};

	// Sets the language.
	void SetLanguage(const char* language);
};

extern Options g_options;
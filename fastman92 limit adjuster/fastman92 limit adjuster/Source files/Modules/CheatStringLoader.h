/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <stdint.h>
#include "../Core/CLimitAdjusterModule.h"

class CheatStringLoader : public CLimitAdjusterModule
{
public:
	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown(){}

	// Cheat hash keys
	uint32_t* CCheat__m_aCheatHashKeys;

	// Loads cheat strings
	void LoadCheatStrings();
};

extern CheatStringLoader g_cheatStringLoader;
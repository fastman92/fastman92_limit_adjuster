/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"
#include <vector>

struct tModelIDrange
{
	int lowestID;
	int highestID;
};

class NotApropIDrangeLoader : public CLimitAdjusterModule
{
public:
	// Checks if ID is not a prop
	bool IsModelUnique(int modelID);

	// Not a prop ID ranges
	std::vector<tModelIDrange> NotAPropIDranges;

	// Loads not a prop ID ranges
	void LoadNotApropIDranges();

	// Initialize
	virtual void Initialise() {};

	// Shutdown
	virtual void Shutdown() {};
};

extern NotApropIDrangeLoader g_notApropIDrangeLoader;
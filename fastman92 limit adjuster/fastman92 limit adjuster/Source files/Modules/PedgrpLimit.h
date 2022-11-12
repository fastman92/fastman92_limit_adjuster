/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"
#include <stdint.h>

class PedgrpLimit : public CLimitAdjusterModule
{
public:
	// Ped groups
	struct {
		uint16_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CPopulation__m_PedGroups;

	// Number of ped groups
	unsigned int m_iNumberOfPedGroups;

	// Number of peds per group
	unsigned int m_iPedsPerGroup;

	// Pedsgrp peds per group
	void SetPedsPerGroupLimit(unsigned int iPedsPerGroup);

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();
};

extern PedgrpLimit g_pedGrpLimits;
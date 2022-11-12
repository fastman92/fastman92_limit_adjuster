/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

class VisibilityLimits : public CLimitAdjusterModule
{
public:
	int CLinkList_CVisibilityPlugins__AlphaObjectInfo;
	int CLinkList_CVisibilityPlugins__WeaponPedInfo;

	int ms_alphaListLimit;
	int ms_alphaBoatAtomicListLimit;
	int ms_alphaEntityListLimit;
	int ms_alphaUnderwaterEntityListLimit;
	int ms_alphaReallyDrawLastListLimit;
	int ms_weaponPedsForPCLimit;

	// Sets alpha list limit
	void SetAlphaListLimit(int iAlphaListLimit);

	// Sets alpha boat atomic list limit
	void SetAlphaBoatAtomicListLimit(int iAlphaBoatAtomicListLimit);

	// Sets alpha entity list limit
	void SetAlphaEntityListLimit(int iAlphaEntityListLimit);

	// Sets alpha underwater entity list limit
	void SetAlphaUnderwaterEntityListLimit(int iAlphaUnderwaterEntityListLimit);

	// Sets alpha really draw last list limit
	void SetAlphaReallyDrawLastListLimit(int iAlphaReallyDrawLastListLimit);

	// Sets weapon peds for PC limit
	void SetWeaponPedsForPCLimit(int iWeaponPedsForPClimit);

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown() {};
};

extern VisibilityLimits g_visibilityLimits;
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

class DirectoryLimits : public CLimitAdjusterModule
{
public:
	// Extra objects dir limit
	int ms_iExtraObjectsDirLimit;

	// Cutscene directory limit
	int ms_iCutsceneDirLimit;

	// Clothes directory limit
	int ms_iClothesDirLimit;

	// Clothes directory limit enabled?
	int ms_bClothesDirLimitEnabled;

	// player IMG entries
	struct {
		char* ptr;
		DEFINE_IS_ALLOCATED();
	} playerImgEntries;

	// Sets the limit for extra objects directory
	void SetExtraObjects(int iExtraObjects);

	// Sets the limit for cutscene directory
	void SetCutsceneDirLimit(int iCutsceneDirLimit);

	// Sets the limit for clothes directory
	void SetClothesDirLimit(int iClothesDirLimit = -1);

	// Applies enabled limits
	void ApplyEnabledLimits();

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();

private:
	// Patches clothes dir limit
	void PatchClothesDirLimit();
};

extern DirectoryLimits g_directoryLimits;
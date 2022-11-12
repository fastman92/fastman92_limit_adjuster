/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#pragma once
#include "../Core/CLimitAdjusterModule.h"

class SaveOfVariableLength : public CLimitAdjusterModule
{
public:
	bool bIsSavingPatchApplied;
	bool bIsLoadingPatchApplied;
	
	// Patches a save function, the save file will have unlimited length.
	bool MakeSaveOfVariableLength();

	// Patches a loading function, the savefile of any length may be considered as valid savefile.
	void PatchLoadingFunction();

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown() {}
};

extern SaveOfVariableLength g_SaveOfVariableLength;
#pragma once

#include "../../Core/CLimitAdjusterModule.h"

#include "ZIPFile.h"	// Finds a file

// Creates ZIP storage
ZIPFile* ZIP_FileCreate(const char *path);

// Adds ZIP storage
bool ZIP_AddStorage(ZIPFile* toAdd);

class ZIP_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern ZIP_VarInitialisation g_ZIP_VarInitialisation;
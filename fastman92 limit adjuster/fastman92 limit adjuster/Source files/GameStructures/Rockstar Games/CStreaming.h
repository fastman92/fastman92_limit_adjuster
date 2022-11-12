/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#include "../../Core/CLimitAdjusterModule.h"

class CStreaming
{
public:
	// Last selected cab driver ID
	static unsigned int& LastSelectedCabDriver;

	// Adds image to list
	static void AddImageToList(const char* filename, bool bIsNotPlayerImg);

	// Load CD directory
	static void LoadCdDirectory(const char* filename, int imgID);

	// Requests model
	static void RequestModel(int dwModelId, int flags);

	// Removes file
	static void RemoveModel(
		int fileID
		);

	// Sets model deletable
	static void SetModelIsDeletable(int dwModelId);		

	// Loads all requested models
	static void LoadAllRequestedModels(bool bOnlyPriorityRequests);
};

class CStreaming_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern CStreaming_VarInitialisation g_CStreaming_varInitialisation;
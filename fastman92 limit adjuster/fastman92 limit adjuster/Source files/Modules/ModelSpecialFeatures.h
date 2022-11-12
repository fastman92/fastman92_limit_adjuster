/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

#include <map>

extern int32_t(__cdecl* GetModelIDforModelSpecialFeatures)(int32_t modelID);

class ModelSpecialFeatures : public CLimitAdjusterModule
{
private:
	bool bSpecialFeaturesEnabled;

	// <custom ID, standard ID>
	std::map<int32_t, int32_t> mapOfIds;

public:
	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();

	// Enables special features
	void EnableSpecialFeatures(bool bEnableSpecialFeatures);

	// Returns true if special features are enabled
	bool AreSpecialFeaturesEnabled();

	// Applies special features loader
	void ApplyLoader();

	// Returns standard model ID by custom model ID
	INLINE int32_t GetStandardModelIDbyCustomModelID(int32_t modelID);

	// Returns model ID by name
	static bool GetModelID(const char* modelName, int* pModelID);

	// Loads configuration
	void LoadConfiguration();
};

extern ModelSpecialFeatures g_modelSpecialFeatures;
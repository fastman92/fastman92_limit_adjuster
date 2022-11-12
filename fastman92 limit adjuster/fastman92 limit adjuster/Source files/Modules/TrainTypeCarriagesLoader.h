#pragma once
#include "../Core/CLimitAdjusterModule.h"

#include "../Core/eGameVersion.h"
#include <stdint.h>

class CTrainTypeCarriagesLoader : public CLimitAdjusterModule
{
public:
	// Max number of vehicle types for type
	unsigned int ms_maxNumberOfVehiclesForType;

	// Number of type IDs
	unsigned int ms_numberOfTypeIDs;

private:

	// Train type carriages loaded
	bool bTrainTypeCarriagesLoaded;

	// Filename
	char m_filePath[260];

	// Undefined model ID
	int m_undefinedModelID;

	// Loads train type carriages
	void LoadTrainTypeCarriages();

	// Sets undefined model ID
	void SetUndefinedModelID(int modelID);

public:

	// Train type carriages
	struct {
		int32_t* ptr;
		DEFINE_IS_ALLOCATED();
	} TrainTypeCarriages;

	// Sets max number of vehicles for type
	void SetMaxNumberOfVehicleForType(unsigned int newValue);

	// Set number of type IDs
	void SetNumberOfTypeIDs(unsigned int newValue);

	// Sets filename
	void SetFilename(const char* filename);

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();

	// Checks if loader is implemented for specified game version
	bool IsLoaderImplementedForThisGameVersion(Game::eGameVersion gameVersion);

	// Applies loader
	virtual void ApplyLoader();

private:
	// Prints to log
	void PrintToLog();

	// Returns model ID by name
	static bool GetModelID(const char* modelName, int* pModelID);
};

extern CTrainTypeCarriagesLoader g_trainTypeCarriageLoader;
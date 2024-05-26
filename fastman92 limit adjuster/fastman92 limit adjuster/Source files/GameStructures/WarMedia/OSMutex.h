#pragma once

#include "../../Core/CLimitAdjusterModule.h"

typedef void* OSMutex;

void OS_MutexObtain(OSMutex onMutex);
void OS_MutexRelease(OSMutex onMutex);

class OSMutex_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern OSMutex_VarInitialisation g_OSMutex_VarInitialisation;
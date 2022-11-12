#pragma once
#include "../Core/CLimitAdjusterModule.h"

class WindowedMode : public CLimitAdjusterModule
{
public:
	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown() {}

	// Applies loader
	void ApplyWindowedMode();
};

extern WindowedMode g_windowedMode;
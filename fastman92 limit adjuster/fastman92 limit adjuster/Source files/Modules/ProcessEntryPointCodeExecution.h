/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#include "../Core/CLimitAdjusterModule.h"

typedef void(*tProcessEntryPointFunction)(void* pCustomData);

struct tProcessEntryPointCallback
{
	tProcessEntryPointFunction funcPtr;
	void* pCustomData;
};

class CProcessEntryPointCodeExecution : public CLimitAdjusterModule
{
public:
	unsigned int m_numberOfCallbacksRegistered;
	tProcessEntryPointCallback m_callbackList[10];

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown() {}

	// Adds callback
	void AddCallback(tProcessEntryPointFunction function, void* pCustomData);

	// Applies the patch
	void ApplyHook();
};

extern CProcessEntryPointCodeExecution g_ProcessEntryPointCodeExecution;
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#include "../Core/CLimitAdjusterModule.h"

typedef void(*tLoadingScreenFontFunction)(void* pCustomData);

struct tLoadingScreenFontCallback
{
	tLoadingScreenFontFunction funcPtr;
	void* pCustomData;
};

class LoadingScreenFontHooks : public CLimitAdjusterModule
{
public:
	union {
		char Char[1024];
		unsigned short Unicode[1024];
	} loadingScreenText;

	unsigned int m_numberOfCallbacksRegistered;
	tLoadingScreenFontCallback m_callbackList[10];

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown() {}

	// Applies the patch
	void ApplyHook();

	// Adds callback
	void AddCallback(tLoadingScreenFontFunction function, void* pCustomData);
};

extern LoadingScreenFontHooks g_LoadingScreenFontHooks;
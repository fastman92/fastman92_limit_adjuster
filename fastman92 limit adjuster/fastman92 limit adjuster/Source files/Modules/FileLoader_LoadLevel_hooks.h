/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

struct tLoadLevelHook
{
	char keyword[16];
	bool (* function)(const char* line);
};

class LoadLevelHooks : public CLimitAdjusterModule
{
	// Checks list of keywords and calls function
	bool ProcessListOfKeywords(const char* line);

public:
	bool bIsHookActive;
	unsigned int ms_numberOfKeywordsRegistered;
	tLoadLevelHook ms_keywordList[10];

	// Initializes class
	void Initialise();

	// Shutdown
	virtual void Shutdown() {}

	// Applies hook if neccessary
	void ApplyHook();

	// Adds function handler
	void AddKeywordHandler(const char* keywordName, bool (* function)(const char* line));
};

extern LoadLevelHooks g_loadLevelHooks;
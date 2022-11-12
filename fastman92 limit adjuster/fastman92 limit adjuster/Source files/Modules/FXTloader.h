/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"
#include <map>
#include <string>

class CFXTloaderBase
{
public:
	// Max key length
	int m_MaxKeyLength;

	// Constructor
	CFXTloaderBase();

	// Sets max key length
	void SetMaxKeyLength(int keyLength);

	// Loads FXT files
	void LoadFXTfiles(const char* directory);

	// Adds FXT entry
	virtual void AddFXTentry(const char* key, const char* text) = 0;

	// Returns pointer to GXT entry
	virtual const void* GetFXTentryGen(const char* key) = 0;
};

class CFXTloaderUnicode : public CFXTloaderBase
{
protected:
	// Entry map
	std::map<std::string, std::wstring> m_FXTentryMap;

public:
	// Adds FXT entry
	virtual void AddFXTentry(const char* key, const char* text);

	// Returns pointer to GXT entry
	const wchar_t* GetFXTentry(const char* key);

	// Returns pointer to GXT entry
	const void* GetFXTentryGen(const char* key) { return this->GetFXTentry(key); }
};

class CFXTloaderASCII : public CFXTloaderBase
{
protected:
	// Entry map
	std::map<std::string, std::string> m_FXTentryMap;

public:
	// Adds FXT entry
	virtual void AddFXTentry(const char* key, const char* text);

	// Returns pointer to GXT entry
	const char* GetFXTentry(const char* key);

	// Returns pointer to GXT entry
	const void* GetFXTentryGen(const char* key) { return this->GetFXTentry(key); }
};

class FXTloader : public CLimitAdjusterModule
{
public:
	CFXTloaderASCII m_FXTloaderASCII;
	CFXTloaderUnicode m_FXTloaderUnicode;

	CFXTloaderBase* pUsedFXTloader;

	// Applies FXT loader
	void ApplyFXTloader();

	// Initialize
	virtual void Initialise() {}

	// Shutdown
	virtual void Shutdown() {}
};

extern FXTloader g_FxtLoader;
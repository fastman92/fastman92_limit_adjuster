/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/tHashPair.h"
#include <vector>

// GTA IV
class CHashStringLoader
{
	// pointer to hash function
	uint32_t(*hashFunc)(const char* str);

	// known sound hashes
	std::vector<tInt32HashPair> HashContainer;

public:
	// Constructor
	CHashStringLoader(uint32_t(*hashFunc)(const char* str));

	// Load from file
	bool LoadFromFile(const char* filename);

	// Finds a string by hash
	const char* FindStringByHash(uint32_t hash);
};
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CHashStringLoader.h"
#include <algorithm>
#include <Array\countof.h>

// Constructor
CHashStringLoader::CHashStringLoader(uint32_t(*hashFunc)(const char* str))
{
	this->hashFunc = hashFunc;
}

// Load from file
bool CHashStringLoader::LoadFromFile(const char* filename)
{
	FILE* fp = fopen(filename, "r");

	if (!fp)
		return false;


	char buffer[1024];

	while (fgets(buffer, sizeof(buffer), fp))
	{
		if (buffer[0] == '#' || buffer[0] == NULL)
			continue;

		int i = 0;

		while (buffer[i])
			i++;

		if (i > 0 && i < _countof(((tInt32HashPair*)0)->str))
		{
			i--;

			while (i >= 0 && buffer[i] == '\n' || buffer[i] == '\r')
				buffer[i--] = NULL;

			tInt32HashPair pair;

			strcpy(pair.str, buffer);
			pair.hash = this->hashFunc(pair.str);

			this->HashContainer.push_back(pair);
		}		
	}

	fclose(fp);

	std::sort(this->HashContainer.begin(), this->HashContainer.end(),
		[](const tInt32HashPair& a, const tInt32HashPair& b)
		{
			return a.hash < b.hash;
		}
	);

	return true;
}

template<typename Iter, typename T>
Iter SearchInSortedArray(Iter begin, Iter end, T value)
{

	Iter i = std::lower_bound(begin, end, value);

	if (i != end && *i == value)
		return i; // found in container
	else
		return end; // not found
}

// Finds a string by hash
const char* CHashStringLoader::FindStringByHash(uint32_t hash)
{
	/*
	std::vector<tInt32HashPair>::iterator it = std::lower_bound(this->HashContainer.begin(), this->HashContainer.end(),
		[](tInt32HashPair& a, tInt32HashPair& b)
		{
			return a.hash < b.hash;
		}
	);
	*/

	int count = this->HashContainer.size();

	if (count == 0)
		return NULL;

	int start = 0;
	int end = count;

	while (true)
	{
		if (start > end)
			return NULL;

		int middle = (start + end) / 2;

		uint32_t hashFromElement = this->HashContainer[middle].hash;

		if (hashFromElement == hash)
			return this->HashContainer[middle].str;
		
		if (hash > hashFromElement)
			start = middle + 1;
		else
			end = middle - 1;
	}

	return NULL;
}
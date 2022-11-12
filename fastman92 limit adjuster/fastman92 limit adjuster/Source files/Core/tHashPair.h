/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <stdint.h>

struct tInt32HashPair
{
	char str[128];
	uint32_t hash;
};


struct tInt32HashPairStrPtr
{
	const char* pStr;
	uint32_t hash;
};

static tInt32HashPairStrPtr MakeHash(const char* str)
{
	tInt32HashPairStrPtr pair;
	pair.pStr = str;

	return pair;
}
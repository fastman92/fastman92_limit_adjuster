/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <string>

template <class T> T GetObjectMadeOfString(const char* str)
{
	T result;
	strncpy((char*)&result, str, sizeof(T));
	return result;
};
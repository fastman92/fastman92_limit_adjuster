/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

template<typename T> void GetReversedString(const T* input, T* out)
{
	int len = 0;

	while (input[len])
		len++;

	for (int i = 0; i < len; i++)
		out[len - i - 1] = input[i];

	out[len] = NULL;
}
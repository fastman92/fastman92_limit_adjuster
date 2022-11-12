/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <stdint.h>

class CPUmath
{
public:

	// Returns division in components
	// Returns a representation like this: (x*0x4EC4EC4F)/2^36
	static void GetDivisionInComponents(int32_t num, int32_t* pMultiplier, int32_t* pPowerOfTwo);
};
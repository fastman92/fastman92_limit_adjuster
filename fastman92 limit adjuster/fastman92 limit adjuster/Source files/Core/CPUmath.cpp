/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPUmath.h"
// #include "CGenericLogStorage.h"
// #include "FormattedOutput.h"

// Returns division in components
void CPUmath::GetDivisionInComponents(int32_t num, int32_t* pMultiplier, int32_t* pPowerOfTwo)
{
	uint32_t multiplier = -1;
	int32_t powerOfTwo = -1;

	uint64_t bitValue = 0;
	double oldDividedNum = 0;

	for (int i = 0; i <= 63; i++)
	// int i = 37;
	{
		bitValue = (uint64_t)1 << i;

		int32_t rest = bitValue % num;

		if (rest)
			bitValue += num - rest;

		unsigned int newMultiplier = (int32_t)((uint64_t)bitValue / num);

		double newDividedNum = (double)((uint64_t)bitValue) / newMultiplier;
		
		if (newDividedNum <= num)
		{
			multiplier = newMultiplier;
			powerOfTwo = i;
			oldDividedNum = newDividedNum;
		}
		else
			break;

		/*
		////////////////
		__int64 bitValueAgain = (uint64_t)1 << i;
		// double dividedNum = (double)bitValue / newMultiplier;

		// __int32 rest = 

		// dividedValue = dividedValue * bitValue / 0;
		// double one = num * multiplier / bitValue;
		*/
		// CGenericLogStorage::SaveFormattedTextLn("bit %d: %lld multiplier: 0x%X dividedNum: %.10f", i, bitValue, newMultiplier, newDividedNum);
		
		
	}

	if (pMultiplier)
		*pMultiplier = multiplier;

	if (pPowerOfTwo)
		*pPowerOfTwo = powerOfTwo;
}
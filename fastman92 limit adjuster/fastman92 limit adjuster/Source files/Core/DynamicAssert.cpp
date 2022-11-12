/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "DynamicAssert.h"

#include "FormattedOutput.h"
#include "LimitAdjuster.h"

// FLA dynamic assert, throws an exception
void FLA_dynamic_assert(bool bCondition, const char* message)
{
	if (bCondition)
		return;
	
	throw f92_runtime_error("%s", message);
}
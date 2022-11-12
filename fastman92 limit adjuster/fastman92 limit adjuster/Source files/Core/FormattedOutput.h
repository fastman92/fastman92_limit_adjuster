/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#ifdef IS_PLATFORM_ANDROID
#include "ProjectConstants.h"

#include <android\log.h>
#endif

void printf_MessageBox(const char* format, ...);
void printf_MessageBox(const wchar_t * format, ...);

void OutputFormattedDebugString(const char* format, ...);
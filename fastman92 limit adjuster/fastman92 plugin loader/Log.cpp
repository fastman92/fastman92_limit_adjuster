/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#include "Log.h"

#include <limits.h>
#include <android/log.h>

static void OutputFormattedDebugStringVargs(const char* format, va_list args)
{
	char buffer[4096];

#ifdef IS_PLATFORM_WIN
	_vsnprintf_s(buffer, _countof(buffer), _countof(buffer) - 1, format, args);

	OutputDebugStringA(buffer);
	va_end(vl);
#elif defined(IS_PLATFORM_ANDROID)
	__android_log_vprint(ANDROID_LOG_INFO, "fastman92 plugin loader", format, args);
#endif
}

void printf_MessageBox(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	OutputFormattedDebugStringVargs(format, args);
}

void OutputFormattedDebugString(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	OutputFormattedDebugStringVargs(format, args);
}
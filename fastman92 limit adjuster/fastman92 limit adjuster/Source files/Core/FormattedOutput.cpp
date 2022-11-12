/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "FormattedOutput.h"
#include "ProjectConstants.h"

#ifdef IS_PLATFORM_WIN
#include <Windows.h>
#endif

#define UNICODE_TEXT(str) L#str

void printf_MessageBox(const char* format, ...)
{
	char buffer[4096];

#ifdef IS_PLATFORM_WIN
	va_list vl;
	va_start(vl, format);
	
	vsnprintf(buffer, _countof(buffer), format, vl);
	MessageBoxA(NULL, buffer, PROJECT_FULL_NAME, MB_OK);
	va_end(vl);
#elif defined(IS_PLATFORM_ANDROID)
	va_list args;
	va_start(args, format);
	__android_log_vprint(ANDROID_LOG_INFO, PROJECT_NAME, format, args);
	va_end(args);
#endif
}

void printf_MessageBox(const wchar_t * format, ...)
{
#ifdef IS_PLATFORM_WIN
	va_list vl;
	va_start(vl, format);

	wchar_t buffer[4096];

	vswprintf(buffer, _countof(buffer), format, vl);
	MessageBoxW(NULL, buffer, UNICODE_TEXT(TOSTRING(PROJECT_FULL_NAME)), MB_OK);
	va_end(vl);
#endif
}

void OutputFormattedDebugString(const char* format, ...)
{
	char buffer[4096];

	#ifdef IS_PLATFORM_WIN
	va_list vl;
	va_start(vl, format);

	vsnprintf(buffer, _countof(buffer), format, vl);

	OutputDebugStringA(buffer);
	va_end(vl);
	#elif defined(IS_PLATFORM_ANDROID)
	va_list args;
	va_start(args, format);
	__android_log_vprint(ANDROID_LOG_INFO, PROJECT_NAME, format, args);
	va_end(args);
	#endif
}
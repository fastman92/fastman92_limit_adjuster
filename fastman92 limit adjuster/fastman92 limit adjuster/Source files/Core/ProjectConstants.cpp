/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "ProjectConstants.h"

#include "ProjectConstantsGenerated.h"

#ifndef __PROJECT_NAME__
#define __PROJECT_NAME__ "fastman92 limit adjuster"
#endif

#if PROJECT_IS_UNRELEASED_EDITION
	#ifndef NDEBUG
		#define __PROJECT_VERSION_DATE_FIELD__2 "debug mode"
	#else
		#define __PROJECT_VERSION_DATE_FIELD__2 "release mode"
	#endif

	#define __PROJECT_VERSION_DATE_FIELD__  ", beta version, " __PROJECT_VERSION_DATE_FIELD__2 ", compilation time: " COMPILATION_DATE_UTC " " COMPILATION_TIME_UTC  " (UTC)"
#else
	#define __PROJECT_VERSION_DATE_FIELD__ ", compilation time: " COMPILATION_DATE_UTC " " COMPILATION_TIME_UTC " (UTC)"
#endif

#define __PROJECT_VERSION_ONLY__ TOSTRING(PROJECT_VERSION_ONLY_RAW)
#define __PROJECT_VERSION__ __PROJECT_VERSION_ONLY__ __PROJECT_VERSION_DATE_FIELD__
// #undef __PROJECT_VERSION_DATE_FIELD__

const char* PROJECT_NAME = __PROJECT_NAME__;
const char* PROJECT_VERSION_ONLY = __PROJECT_VERSION_ONLY__;
const char* PROJECT_VERSION = __PROJECT_VERSION__;
const char* PROJECT_FULL_NAME = __PROJECT_NAME__ " " __PROJECT_VERSION__;
const char* PROJECT_SIMPLE_NAME = __PROJECT_NAME__ " " __PROJECT_VERSION_ONLY__;

// static_assert(sizeof(PROJECT_VERSION_ONLY) > 1, "Project version unset!");
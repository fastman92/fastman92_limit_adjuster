/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../ForOtherProjects/Common/common.h"

#define PROJECT_IS_UNRELEASED_EDITION 1
#define PROJECT_USE_DEVELOPMENT_INI 1

#if !PROJECT_IS_UNRELEASED_EDITION && PROJECT_USE_DEVELOPMENT_INI
#error "Release edition should not use a development INI"
#endif

#if !PROJECT_IS_UNRELEASED_EDITION && !defined(NDEBUG)
#error "Release edition should not be compiled in debug mode"
#endif

#define GLOBAL_LIMIT_DEBUG FALSE

#if COMPILE_LITE_VERSION && PROJECT_IS_UNRELEASED_EDITION
#define MAKE_A_LITE_VERSION
#endif

#define DEPRECATED_CODE 0

// Extern variables
extern const char* PROJECT_NAME;
extern const char* PROJECT_VERSION_ONLY;
extern const char* PROJECT_VERSION;
extern const char* PROJECT_FULL_NAME;
extern const char* PROJECT_SIMPLE_NAME;
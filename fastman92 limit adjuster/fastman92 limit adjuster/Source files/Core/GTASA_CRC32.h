/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include <ctype.h>

unsigned long GTASA_CRC32_fromString(const char* string);

unsigned long GTASA_CRC32_fromUpCaseString(const char* string);

unsigned long GTASA_CRC32_fromBlock(const void* ptr, unsigned int len);
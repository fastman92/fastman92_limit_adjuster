/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#include <Assertions.h>

struct CollisionLink
{
	void* ptr;
	CollisionLink *next;
	CollisionLink *prev;
};

VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CollisionLink, 12);
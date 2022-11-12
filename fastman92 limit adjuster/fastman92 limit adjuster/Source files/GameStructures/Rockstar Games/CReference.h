/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#include <Assertions.h>

class CReference
{
public:
	CReference *m_pNext;
	class CEntity **m_pEntity;
};

VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CReference, 8);
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CEntity.h"

typedef CEntity CVehicle_generic;

namespace Game_GTASA
{
	typedef CVehicle_generic CVehicle;
}

class CVehicle_extension
{
public:
	uint32_t CurrentPathPointIndex;
	uint32_t NextPathPointIndex;
	uint32_t PrevPathPointIndex;

	CVehicle_extension()
	{
		this->CurrentPathPointIndex = -1;
		this->NextPathPointIndex = -1;
		this->PrevPathPointIndex = -1;
	}
};
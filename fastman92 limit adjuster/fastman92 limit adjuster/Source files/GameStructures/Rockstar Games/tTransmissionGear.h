/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "Assertions.h"

namespace Game_GTA
{
	struct tTransmissionGear {
		float m_fMaxVelocity;
		float m_fChangeUpVelocity;
		float m_fChangeDownVelocity;
	};

	VALIDATE_SIZE(tTransmissionGear, 0xC);
}
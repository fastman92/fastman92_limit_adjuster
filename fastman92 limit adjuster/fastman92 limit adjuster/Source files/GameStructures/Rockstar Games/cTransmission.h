/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "Assertions.h"
#include "tTransmissionGear.h"
#include <stdint.h>

namespace Game_GTAIII
{
	class cTransmission {
	public:
		Game_GTA::tTransmissionGear m_aGears[6];
		unsigned char   m_nDriveType; // F/R/4
		unsigned char   m_nEngineType; // P/D/E
		unsigned char   m_nNumberOfGears; // 1 to 6
		struct {
			unsigned char m_b1gBoost : 1;
			unsigned char m_b2gBoost : 1;
		} m_nHandlingFlags;
		float             m_fEngineAcceleration; // 0.1 to 10.0
		float             m_fMaxGearVelocity;
		float             m_fEngineInertia; // 0.0 to 50.0
		float             m_fMinGearVelocity;
		float             m_fCurrentGearVelocity;
		float field_60;
	};

	VALIDATE_SIZE(cTransmission, 0x64);
}

namespace Game_GTAVC
{
	class cTransmission
	{
	public:
		Game_GTA::tTransmissionGear m_aGears[6];
		unsigned char   m_nDriveType; // F/R/4
		unsigned char   m_nEngineType; // P/D/E
		unsigned char   m_nNumberOfGears; // 1 to 6
		unsigned char m_nHandlingFlags;
		float             m_fEngineAcceleration; // 0.1 to 10.0
		float             m_fMaxGearVelocity; // 5.0 to 150.0
		float              m_fEngineInertia; // 0.0 to 50.0
		float             m_fMinGearVelocity;
		float             m_fCurrentSpeed;
	};

	VALIDATE_SIZE(cTransmission, 0x60);
}

namespace Game_GTASA
{
	class cTransmission
	{
	public:
		Game_GTA::tTransmissionGear m_aGears[6];
		uint8_t   m_nDriveType; // F/R/4
		uint8_t   m_nEngineType; // P/D/E
		uint8_t   m_nNumberOfGears; // 1 to 6
		int8_t field_4B;
		uint32_t  m_dwHandlingFlags;
		float             m_fEngineAcceleration; // 0.1 to 10.0
		float             m_fEngineInertia; // 0.0 to 50.0
		float             m_fMaxGearVelocity; // 5.0 to 150.0
		int32_t field_5C;
		float             m_fMinGearVelocity;
		float             m_fCurrentSpeed;
	};

	VALIDATE_SIZE(cTransmission, 0x68);
}
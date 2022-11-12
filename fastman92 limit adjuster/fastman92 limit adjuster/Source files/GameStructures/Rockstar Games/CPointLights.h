/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CVector.h"
#include <Assertions.h>
#include <stdint.h>

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	struct tPointLight
	{
	public:
		CVector m_vPosn;
		CVector m_vDirection;
		float m_fRange;
		float m_fColorRed;
		float m_fColorGreen;
		float m_fColorBlue;
		class CEntity *m_pEntityToLight;
		uint8_t m_nType;
		uint8_t m_nFogType;
		uint8_t m_bGenerateShadows;
	};

	VALIDATE_SIZE(tPointLight, 0x30);

	class CPointLights
	{
	public:
		// static variables

		// num of registered lights in frame
		static uint32_t& NumLights;
		// lights array. Count: MAX_POINTLIGHTS (32)
		static tPointLight *aLights;

		// static functions
		static void AddLight(unsigned char lightType, CVector origin, CVector direction, float radius, float red, float green, float blue, unsigned char fogType, bool generateExtraShadows, CEntity* entityAffected);
	};
}
#endif
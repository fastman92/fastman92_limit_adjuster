/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "Assertions.h"
#include "CVector.h"
#include "CRGBA.h"
#include <stdint.h>


namespace Game_GTASA
{
	enum eCoronaType
	{
		CORONATYPE_SHINYSTAR,
		CORONATYPE_HEADLIGHT,
		CORONATYPE_MOON,
		CORONATYPE_REFLECTION,
		CORONATYPE_HEADLIGHTLINE,
		CORONATYPE_RING_B = 9
	};

	class CRegisteredCorona
	{
	public:
		CVector m_vPosn;
		uint32_t m_dwId;
		void *m_pTexture;
		float m_fSize;
		float m_fAngle; // left from III&VC
		float m_fFarClip;
		float m_fNearClip;
		float m_fHeightAboveGround;
		float m_fFadeSpeed;
		CRGBA m_Color;
		uint8_t m_nFadeState;
		uint8_t m_bRegisteredThisFrame;
		uint8_t m_nFlareType;
		uint8_t m_bUsesReflection;

		struct {
		uint8_t m_bCheckObstacles : 1;
		uint8_t m_bOffScreen : 1;
		uint8_t m_bJustCreated;
		uint8_t m_bFlashWhileFading : 1;
		uint8_t m_bOnlyFromBelow : 1;
		uint8_t m_bReflectionDelay : 1;
		uint8_t m_bDrawWithWhiteCore : 1;
		uint8_t m_bAttached : 1;
		} m_flags;

		void *m_pAttachedTo;

		void Update();
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CRegisteredCorona, 0x3C);
}
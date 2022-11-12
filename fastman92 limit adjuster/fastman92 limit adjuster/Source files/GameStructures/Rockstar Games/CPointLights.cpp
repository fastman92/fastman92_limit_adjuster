/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPointLights.h"

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	// Converted from cdecl void CPointLights::AddLight(uchar lightType,CVector origin,CVector direction,float radius,float red,float green,float blue,uchar fogType,bool generateExtraShadows,CEntity *entityAffected) 0x7000E0
	void CPointLights::AddLight(unsigned char lightType, CVector origin, CVector direction, float radius, float red, float green, float blue, unsigned char fogType, bool generateExtraShadows, CEntity* entityAffected)
	{
		((void(__cdecl *)(unsigned char, CVector, CVector, float, float, float, float, unsigned char, bool, CEntity*))0x7000E0)(lightType, origin, direction, radius, red, green, blue, fogType, generateExtraShadows, entityAffected);
	}
}
#endif
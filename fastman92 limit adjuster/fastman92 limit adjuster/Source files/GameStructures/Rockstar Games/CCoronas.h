/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CRegisteredCorona.h"
#include "CEntity.h"

class CCoronas
{
public:
	// Creates corona by texture
	static void RegisterCorona(unsigned int id, CEntity *attachTo, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const &posn, float radius, float farClip, struct RwTexture *texture, unsigned char flare, bool enableReflection, bool checkObstacles, int _param_not_used, float angle, bool longDistance, float nearClip, unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay);
	// Creates corona by type
	static void RegisterCorona(unsigned int id, CEntity *attachTo, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const &posn, float radius, float farClip, unsigned char coronaType, unsigned char flare, bool enableReflection, bool checkObstacles, int _param_not_used, float angle, bool longDistance, float nearClip, unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay);
};

class CCoronas_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern CCoronas_VarInitialisation g_CCoronas_varInitialisation;
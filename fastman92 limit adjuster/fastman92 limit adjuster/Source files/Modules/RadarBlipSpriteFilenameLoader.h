/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

#include <vector>

namespace Game_GTASA
{
	class CSprite2d
	{
	public:
		void *texture;
	};
}

class CRadarBlipSpriteInfoExtension
{
public:
	char GXTkey[16];
};

class RadarBlipSpriteFilenameLoader : public CLimitAdjusterModule
{
public:
	// Number of type IDs
	unsigned int ms_numberOfTypeIDs;

	// Radar blip sprite filenames
	struct {
		const char** ptr;
		DEFINE_IS_ALLOCATED();
	} RadarBlipSpriteFilenames;

	// Radar blip sprite info extension
	CRadarBlipSpriteInfoExtension* RadarBlipSpriteInfoExtension;

	std::vector<char*> RadarBlipSpriteFilenamesAllocated;

	// Radar blip sprites
	struct {
		union {
			Game_GTASA::CSprite2d* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CRadar__RadarBlipSprites;

	// Set number of type IDs
	void SetNumberOfTypeIDs(unsigned int newValue);

	// Loads blip sprite filenames
	void LoadBlipSpriteFilenames();

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();
};

extern RadarBlipSpriteFilenameLoader g_RadarBlipSpriteFilenameLoader;
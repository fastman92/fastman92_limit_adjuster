/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

#include <PathStructures.h>

namespace Game_GTASA
{
	struct CScriptRoadblock
	{
		CVector cornerA;
		CVector cornerB;
		char active;
		char field_19;
		char type;
		char field_1B;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CScriptRoadblock, 0x1C);

	class CRoadBlocks
	{
	public:
		// Number of road blocks
		static unsigned int* NumRoadBlocks;

		// Roadblox flags
		static char* InOrOut;

		// Roadblock nodes
		static CNodeAddress* RoadBlockNodes;

		// Generate dynamic road blocks?
		static bool* bGenerateDynamicRoadBlocks;

		// Max number of script blocks
		static unsigned int MaxNumberOfScriptBlocks;

		// Script roadblocks
		static CScriptRoadblock* ScriptRoadBlocks;

		// Inits
		static void Init();

		// Shut downs
		static void Shutdown();

		// Clears script road blocks
		static void ClearScriptRoadBlocks();
	};
}

class RoadBloxBetterLoader : public CLimitAdjusterModule
{
public:
	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown() {}

	// Applies better loader
	void ApplyBetterLoader();
};

extern RoadBloxBetterLoader g_roadBloxBetterLoader;
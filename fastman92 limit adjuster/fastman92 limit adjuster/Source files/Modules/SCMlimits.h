/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "Assertions.h"
#include "../GameStructures/Rockstar Games/CRunningScript.h"
#include "../Core\CLimitAdjusterModule.h"
#include "../Core\eGameVersion.h"

#include <stdint.h>

struct CMissionCleanupEntry
{
	char type;
	int handle;
};

VALIDATE_SIZE(CMissionCleanupEntry, 8);

namespace Game_GTASA
{
	struct CScriptRequestedModel
	{
		char szModelName[24];
		int dwModelIndex;
	};

	VALIDATE_SIZE(CScriptRequestedModel, 0x1C);

	struct tScriptSwitchCase
	{
		int when;
		int then;
	};

	VALIDATE_SIZE(tScriptSwitchCase, 8);

	struct CScriptTrigger
	{
		uint16_t SCM_script_index;
		char AttachType;
		char Type;
		int Status;
		int Radius;
		uint16_t modelID;
		uint16_t priority;
		int field_10;
	};

	VALIDATE_SIZE(CScriptTrigger, 0x14);

	typedef CScriptTrigger CScriptsForBrains;
};

class SCMlimits : public CLimitAdjusterModule
{
public:
	static bool ScriptSpaceLimitsCheckIfSupportedVersion(Game::eGameVersion gameVersion);

private:

	// Patches script space limits, should be executed when limits are set.
	void PatchScriptSpaceLimits();

	// Patches scripts array limits
	void PatchScriptsArrayLimit();

	// Patches mission cleanup limit
	void PatchMissionCleanUpLimit();

	// Patches used object array limit
	void PatchUsedObjectArrayLimit();

	// Patches switch jump table limit
	void PatchSwitchJumpTableLimit();

	// Patches the scripts for brains limit
	void PatchScriptsForBrainsLimit();

public:
	unsigned int iMAINsegmentSize;
	unsigned int iMissionSize;
	unsigned int defaultMAINsegmentSize;
	unsigned int defaultMissionSize;

	struct {
		uint8_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CTheScripts__ScriptSpace;

	bool ms_bMissionCleanUpLimitSet;
	unsigned int ms_iMissionCleanupLimit;
	struct {
		void* ptr;
		DEFINE_IS_ALLOCATED();
	} CTheScripts__MissionCleanUp;


	// Scripts array
	bool ms_bScriptsArrayLimitSet;
	unsigned int ms_iScriptsArrayLimit;
	struct {
		CDynamicStructMemberArrayAccess<CRunningScript> array;
		DEFINE_IS_ALLOCATED();
	} CTheScripts__ScriptsArray;

	// Used object array
	bool ms_bUsedObjectArrayLimitSet;
	unsigned int ms_iUsedObjectArrayLimit;
	struct {
		union {
			Game_GTASA::CScriptRequestedModel* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CTheScripts__UsedObjectArray;

	// Script jump table array
	bool ms_bScriptJumpTableLimitSet;
	unsigned int ms_iScriptJumpTableLimit;

	struct {
		union {
			Game_GTASA::tScriptSwitchCase* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CTheScripts__SwitchJumpTable;

	// Scripts for brains
	bool ms_bScriptsForBrainsLimitSet;
	unsigned int ms_iScriptsForBrainsLimit;

	struct {
		union {
			Game_GTASA::CScriptsForBrains* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CTheScripts__ScriptsForBrains;

	// Returns script space size
	unsigned int GetScriptSpaceSize();

	// Sets max size of main.scm
	void SetMaxMAINsegmentSize(int maxMAINsegmentSize);

	// Sets max size of mission
	void SetMaxMissionSize(int iMaxMissionSize);

	// Sets the limit for scripts array
	void SetScriptsArrayLimit(int iScriptsArrayLimit);

	// Sets the mission cleanup limit
	void SetMissionCleanUpLimit(int iMissionCleanUpLimit);

	// Sets the used object array limit
	void SetUsedObjectArrayLimit(int iUsedObjectArrayLimit);

	// Sets the switch jump table limit
	void SetSwitchJumpTableLimit(int iSwitchJumpTableLimit);

	// Sets the scripts for brains limit
	void SetScriptsForBrainsLimit(int iScriptsForBrainsLimit);

	// Patches script space limits, should be executed when limits are set.
	void PatchSCMlimits();

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();
};

extern SCMlimits g_SCMlimits;
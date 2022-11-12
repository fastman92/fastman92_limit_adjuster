/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"
#include <stdint.h>

void printf_Error(bool bTerminateGame, const char* format, ...);

enum eErrorType
{
	GTA_ERROR_ATTEMPT_TO_LOAD_OBJECT_INSTANCE_WITH_UNDEFINED_ID,
	GTA_ERROR_CAR_GENERATOR_LIMIT_EXCEEDED,
	GTA_ERROR_CAR_GENERATOR_WITH_INVALID_MODEL_ID_IS_GETTING_REGISTERED,
	GTA_ERROR_MODEL_DOES_NOT_HAVE_COLLISION_LOADED,
	GTA_ERROR_IMG_ARCHIVE_NEEDS_REBUILDING,
	GTA_ERROR_MODEL_HAS_COLLISION_ALREADY_SET_UP,

	GTA_ERROR_REQUESTED_FILE_DOES_NOT_EXIST,

	GTA_ERROR_MODEL_NAME_IS_DECLARED_ON_MULTIPLE_IDS,
	GTA_ERROR_STREAM_HANDLES_LIMIT_EXCEEDED,

	GTA_ERROR_MAX
};

void ErrorStreamHandlesLimitExceeded();

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	// Prints error, archive needs rebuilding
	void printError_archiveNeedsRebuilding(
		const char* IMGpath,
		const char* fileEntryName,
		uint32_t positionInSectors,
		uint32_t expectedPositionInSectors
	);
}
#endif

class ErrorReporting : public CLimitAdjusterModule
{
private:
	bool m_bErrorEnabled[GTA_ERROR_MAX];

public:
	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();

	// Switches error state
	void SwitchErrorEnabled(eErrorType type, bool bEnable);

	// Returns true if error is enabled.
	bool IsErrorEnabled(eErrorType type);

	// Applies patch of error reporting
	void ApplyHook();
};

extern ErrorReporting g_errorReporting;
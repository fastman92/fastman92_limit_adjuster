/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assertions.h>

// GTA San Andreas
namespace Game_GTASA
{
	struct CVehicleRecordingFileInfo
	{
		int number;
		int pData;
		int field_8;
		char usageCount;
	};

	VALIDATE_SIZE(CVehicleRecordingFileInfo, 0x10);
}

// GTA IV
namespace Game_GTAIV
{
	struct CVehicleRecordingFileInfo
	{
		int number;
		int pData;
		int field_8;
		char usageCount;
	};

	VALIDATE_SIZE(CVehicleRecordingFileInfo, 0x10);
}
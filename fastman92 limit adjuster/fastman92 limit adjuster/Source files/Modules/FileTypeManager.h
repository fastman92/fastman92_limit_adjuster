/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "IMGlimits.h"

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	// Loads CD directory item and returns file ID
	__int32 LoadCDdirectoryItem(
		const CDirectoryEntryExtended& entry,
		const tImgDescriptor *img,
		int imgId,
		const tGTASAimgLoadingCallPriv& loadingCallPriv
		);
	
	/*
	// Loads CD directory item and returns file ID
	__int32 LoadCDdirectoryItemOldFormat(const CDirectoryEntry& entry, int imgId);	
	*/
}
#endif
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <stdint.h>
#include "../../ForOtherProjects/Common/CValueExtension.h"
#include "../../ForOtherProjects/FLA_required/Exports.h"

typedef CValueExtensionNum<uint16_t, int32_t, GetExtendedIDfrom16bitBefore, SetExtendedIDfrom16bitBefore> CFileID;

union CFileIDex
{
	CFileID advanced;
	uint16_t raw;
};
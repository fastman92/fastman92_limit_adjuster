/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

namespace Configuration {
	struct tDocumentationWorkbook;

	namespace Formats
	{
#ifdef IS_PLATFORM_WIN_X86
		// Writes XML excel file
		bool WriteXMLexcelFile(tDocumentationWorkbook* pFLAworkbook, const char* filePath);
#endif
	}
}
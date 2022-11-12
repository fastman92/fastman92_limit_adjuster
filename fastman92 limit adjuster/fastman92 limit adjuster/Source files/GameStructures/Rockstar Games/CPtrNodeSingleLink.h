/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#pragma once
#include <Assertions.h>

namespace Game_BullyScholarschipEdition
{
	class CPtrNodeSingleLink
	{
	public:
		unsigned int type : 4;
		unsigned int itemID : 14;
		unsigned int nextLinkID : 14;	// has value 0x3FFF if unset
	};

	VALIDATE_SIZE(CPtrNodeSingleLink, 4);
}

namespace Game_GTA
{
	class CPtrNodeSingleLink
	{
	public:
		void* pItem;
		CPtrNodeSingleLink* pNext;
	};
}
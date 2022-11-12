/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CFileID.h"

class CCollisionFile_generic {};

// GTA San Andreas
namespace Game_GTASA
{
	class CCollisionFile : public CCollisionFile_generic
	{
	public:
		int field_0;
		int field_4;
		int field_8;
		int field_C;
		int field_10;
		int field_14;
		int field_18;
		int field_1C;
		int16_t field_20;
		CFileID m_wLowestModelID;
		CFileID m_wHighestModelID;
		int16_t nReferenceCount;
		char bFileLoaded;
		char field_29;
		char field_2A;
		char interiorCollision;
	};

	VALIDATE_SIZE(CCollisionFile, 0x2C);
}

class CCollisionFile_extension
{

};
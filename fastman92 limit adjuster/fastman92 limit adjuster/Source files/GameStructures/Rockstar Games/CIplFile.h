/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CFileID.h"

class CIplFile_generic {};

// GTA San Andreas
namespace Game_GTASA
{
	class CIplFile : CIplFile_generic
	{
	public:
		int field_0;
		int field_4;
		int field_8;
		int field_C;
		char name[16];
		int16_t field_20;
		CFileID m_usBuildingsBegin;
		CFileID m_usBuildingsEnd;
		CFileID m_usDummyBegin;
		CFileID m_usDummyEnd;
		int16_t instBlockID;
		char field_2C;
		char field_2D;
		char field_2E;
		char field_2F;
		char field_30;
		char field_31;
		char field_32;
		char field_33;
	};
}

// Extension
class CIplFile_extension
{
};
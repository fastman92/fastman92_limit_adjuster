/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#include "functions.h"

enum TextureDatabaseFormat
{
	TEXTURE_DATABASE_FORMAT_UNC,
	TEXTURE_DATABASE_FORMAT_DXT,
	TEXTURE_DATABASE_FORMAT_360,
	TEXTURE_DATABASE_FORMAT_PS3,
	TEXTURE_DATABASE_FORMAT_PVR,
	TEXTURE_DATABASE_FORMAT_ETC,

	TEXTURE_DATABASE_COUNT_OF_FORMATS
};

// Returns texture database format short name
const char* GetTextureDatabaseFormatShortName(TextureDatabaseFormat format);

template <typename T> class TDBArray
{
	unsigned int field_0;
	unsigned int field_4;
	void* field_8;

	T elements[TEXTURE_DATABASE_COUNT_OF_FORMATS];

	// Destructor
	~TDBArray()
	{
		this->field_4 = 0;

		if (this->field_8)
		{
			game_free(this->field_8);
			this->field_8 = 0;
		}

		this->field_0 = 0;
	}
};

class TextureListingContainer
{

};

class TextureDatabase
{
	int field_0;
	const char* DBname;	// memory must be deallocated by "free" function

	// Loads data file
	bool LoadDataFile(char const*, TDBArray<TextureListingContainer> &);

	// Loads Thumbs
	bool LoadThumbs(TextureDatabaseFormat format, bool a2);
};
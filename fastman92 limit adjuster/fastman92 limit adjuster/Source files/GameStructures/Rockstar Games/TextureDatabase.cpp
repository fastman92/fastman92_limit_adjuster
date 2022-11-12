/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "TextureDatabase.h"

// Returns texture database format short name
const char* GetTextureDatabaseFormatShortName(TextureDatabaseFormat format)
{
	if (format == TEXTURE_DATABASE_FORMAT_UNC)
		return "unc";
	else if (format == TEXTURE_DATABASE_FORMAT_DXT)
		return "dxt";
	else if (format == TEXTURE_DATABASE_FORMAT_360)
		return "360";
	else if (format == TEXTURE_DATABASE_FORMAT_PS3)
		return "ps3";
	else if (format == TEXTURE_DATABASE_FORMAT_PVR)
		return "pvr";
	else if (format == TEXTURE_DATABASE_FORMAT_ETC)
		return "pvr";
	else
		return NULL;
}

// Loads data file
bool TextureDatabase::LoadDataFile(char const*, TDBArray<TextureListingContainer> &)
{
	return false;
}

// Loads Thumbs
bool TextureDatabase::LoadThumbs(TextureDatabaseFormat format, bool a2)
{
	char path[256];

	const char* shortFormatName = GetTextureDatabaseFormatShortName(format);
	sprintf(path, "texdb/%s/%s.%s.tmb", this->DBname, this->DBname, shortFormatName);
	return false;
}
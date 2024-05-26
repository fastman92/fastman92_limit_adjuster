#pragma once

#include "../../Core/CLimitAdjusterModule.h"

#include "OSArray.h"
#include "OSFile.h"


class ZIPFile
{
	struct ZipEntry
	{
		unsigned int offset;
		unsigned int length;
		unsigned char *filename;
	};

	void* vtable;
	OSArray<ZIPFile::ZipEntry> entries;
	unsigned char filename[260];
	unsigned char *pooledName;

public:

	// Opens file from storage
	static OSFile OpenFromStorage(const char *filename, OSFileAccessType access);

	// Finds a file
	static int FindFromStorage(const char *filename, ZIPFile **inZip);
};

class ZIPFile_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern ZIPFile_VarInitialisation g_ZIPFile_VarInitialisation;
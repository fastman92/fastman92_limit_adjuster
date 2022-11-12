/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#include "../../Core/CLimitAdjusterModule.h"

#define FILESTREAM int

#define DIRNAMELENGTH 128

class CFileMgr
{
public:
	// variables
	// length: 128
	static char *ms_dirName;
	// length: 128
	static char *ms_rootDirName;
	// functions
	static void Initialise();
	static int ChangeDir(const char *path);
	static int SetDir(const char *path);
	static int SetDirMyDocuments();
	static int LoadFile(const char *path, unsigned char *buf, int size, const char *mode);
	static FILESTREAM OpenFile(const char *path, const char *mode);
	static FILESTREAM OpenFileForWriting(const char *path);
	static FILESTREAM OpenFileForAppending(const char *path);
	static int Read(FILESTREAM file, void *buf, int size);
	static int Write(FILESTREAM file, const void *buf, int size);
	static bool Seek(FILESTREAM file, int offset, int origin);
	// static bool Seek64(FILESTREAM file, __int64 offset, int origin);
	static bool ReadLine(FILESTREAM file, char *str, int num);
	static char* LoadLine(FILESTREAM file);
	static int CloseFile(FILESTREAM file);
	static int GetFileLength(FILESTREAM file);
	static int Tell(FILESTREAM file);
	static bool GetErrorReadWrite(FILESTREAM file);
};

class CFileMgr_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern CFileMgr_VarInitialisation g_CFileMgr_varInitialization;
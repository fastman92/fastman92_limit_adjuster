#pragma once
#include <stdio.h>

#include "../../Core/CLimitAdjusterModule.h"

#include <DynamicTypes/DynamicStructure.h>

#if IS_PLATFORM_ANDROID
extern uintptr_t Address_NvFOpen;

enum eNvidiaFileHandleType
{
	NVIDIA_HANDLE_ASSET,
	NVIDIA_HANDLE_FILE,
};

struct NvFileHandle
{
	eNvidiaFileHandleType type;
	void* ptr;
};

typedef void NvFile;

struct AndroidFile
{
	NvFile *readFileHandle;
	FILE *writeFileHandle;
	bool fileAsync;
	bool justCreated;
	unsigned char *readBuffer;
	int numReadBytes;
	AndroidFile *nextAsyncFile;
	int subLength;
	int subOffset;

	// Constructor
	AndroidFile();

	static AndroidFile** firstAsyncFile;
};
#endif

enum OSFileError
{
	OSFE_NoError = 0x0,
	OSFE_FileNotFound = 0x1,
	OSFE_EndOfFile = 0x2,
	OSFE_UnknownError = 0x3,
	OSFE_IOPending = 0x4,
	OSFE_IOStillInProgress = 0x5,
	OSFE_MAX = 0x6,
};

enum OSFileDataArea
{
	OSFDA_Storage_0 = 0x0,
	OSFDA_User_0 = 0x1,
	OSFDA_MAX_0 = 0x2,
};

typedef void *OSFile;

enum OSFileAccessType
{
	OSFAT_Read_0 = 0x0,
	OSFAT_Write_0 = 0x1,
	OSFAT_ReadWrite_0 = 0x2,
	OSFAT_ReadAsync_0 = 0x3,
	OSFAT_MAX_0 = 0x4,
};

#if IS_PLATFORM_ANDROID
OSFileError __fastcall OS_FileOpen_replacement(
	OSFileDataArea area,
	OSFile *intoFile,
	const char *filename,
	OSFileAccessType access);
#endif

class OSFile_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern OSFile_VarInitialisation g_OSFile_VarInitialisation;
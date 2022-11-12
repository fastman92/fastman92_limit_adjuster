/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#pragma once
#include <Assertions.h>
#include <stdint.h>

#include "../../Core/CLimitAdjusterModule.h"

#ifndef _IDA_EXPORT
typedef int(*rwCustomStreamFnClose) (void *data);
typedef unsigned int(*rwCustomStreamFnRead) (void *data, void *buffer, unsigned int length);
typedef int(*rwCustomStreamFnWrite) (void *data, const void *buffer, unsigned int length);
typedef int(*rwCustomStreamFnSkip) (void *data, unsigned int offset);
#endif

// RwStreamType
enum RwStreamType : uint32_t
{
	rwNASTREAM = 0,
	rwSTREAMFILE,
	rwSTREAMFILENAME,
	rwSTREAMMEMORY,
	rwSTREAMCUSTOM
};
// RwStreamAccessType
enum RwStreamAccessType : uint32_t
{
	rwNASTREAMACCESS = 0,
	rwSTREAMREAD,
	rwSTREAMWRITE,
	rwSTREAMAPPEND
};

// RwStreamMemory
struct RwStreamMemory
{
	void *pData;
	size_t length;
};

// RwStreamFile
union RwStreamFile
{
	void    *fpFile;
	const void    *constfpFile;
};
// RwStreamCustom
struct RwStreamCustom
{
#ifndef _IDA_EXPORT
	rwCustomStreamFnClose sfnclose;
	rwCustomStreamFnRead sfnread;
	rwCustomStreamFnWrite sfnwrite;
	rwCustomStreamFnSkip sfnskip;
#else
	int   sfnclose;
	int  sfnread;
	int   sfnwrite;
	int  sfnskip;
#endif
	void               *data;
};

// RwStreamUnion
union RwStreamUnion
{
	RwStreamMemory      memory;
	RwStreamFile        file;
	RwStreamCustom      custom;
};

struct RwStream
{
	RwStreamType type;
	RwStreamAccessType accessType;
	int position;
	int field_C;
	int field_10;
	int field_14;
	int field_18;
	int field_1C;
	int rwOwned;
};

VALIDATE_SIZE(RwStream, 0x24);

// Initializes RW stream
static RwStream* _rwStreamInitialize(
	RwStream* stream,
	bool bIsOwned,
	RwStreamType streamType,
	RwStreamAccessType accessType,
	const void *data
	)
{
	return ((RwStream *(*)
		(RwStream* stream,
		bool bIsOwned,
		RwStreamType streamType,
		RwStreamAccessType accessType,
		const void *data))0x7EC810)
		(stream, bIsOwned, streamType, accessType, data);
}

// Opens RW stream
static RwStream * RwStreamOpen(RwStreamType streamType,
RwStreamAccessType accessType, const void *data)
{
	return ((RwStream *(*)
		(RwStreamType streamType, RwStreamAccessType accessType, const void *data))0x7ECEF0)
		(streamType, accessType, data);
}

// Closes RW stream
static bool RwStreamClose(RwStream *stream, void *data)
{
	return ((bool (*)
		(RwStream *stream, void *data))0x7ECE20)
		(stream, data);
}

// Seeks forward
static void RwStreamSkip(RwStream *stream, unsigned int offset)
{
	((void(*)(RwStream *stream, unsigned int offset))0x7ECD00)(stream, offset);
}

int RwStreamRead(RwStream *stream, void *buffer, unsigned int length);

class RwStream_varInitialisation : public CLimitAdjusterModule
{
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {};
};

extern RwStream_varInitialisation g_RwStream_varInitialisation;
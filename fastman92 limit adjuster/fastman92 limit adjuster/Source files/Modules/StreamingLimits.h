/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assertions.h>
#include <stdint.h>

#include "../Core/CLimitAdjusterModule.h"

namespace Game_GTASA
{
	enum StreamStatus
	{
		STREAM_STATUS_IDLE = 0x0,
		STREAM_STATUS_READING = 0x1,
		STREAM_STATUS_FINISHING_BIGFILE = 0x2,
	};

	struct CStreamingChannel
	{
		int readbuf_id[16];
		int readbuf_offset[16];
		StreamStatus iStreamStatus;
		int iLoadingLevel;
		int iBlockOffset;
		int iBlockCount;
		int field_90_set_on_requeststream;
		int LastReadResult;
	};

	VALIDATE_SIZE(CStreamingChannel, 0x98);
}

// Returns address to CdStreamOpen loop
uintptr_t GetAddressToCdStreamOpen_loop();
uintptr_t GetAddress_CdStreamOpen_setLastError();

class StreamingLimits : public CLimitAdjusterModule
{
public:
	// Number of requested models when game considers loading very busy
	unsigned int NumberOfRequestedModelsWhenGameConsidersLoadingVeryBusy;

	// Minimum number of iterations in LoadAllRequestedModels
	unsigned int MinimumNumberOfIterationsInLoadAllRequestedModels;

	// Memory available in bytes
	unsigned int MemoryAvailable;

	// Streaming_DesiredNumberOfVehiclesLoaded
	unsigned int Streaming_DesiredNumberOfVehiclesLoaded;

	// Stream handles array
	struct {
		void** ptr;
		DEFINE_IS_ALLOCATED();
	} streamHandlesArray;

	// Stream name item size
	unsigned int streamNameItemSize;

	// Stream name array
	struct {
		char* ptr;
		DEFINE_IS_ALLOCATED();
	} streamNameArray;

	// Max number of stream handles
	unsigned int iStreamHandlesLimit;

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();

	// Sets a memory available
	void SetMemoryAvailable(uint32_t memoryAvailableInBytes);

	// Streaming: desired number of vehicles loaded
	void SetStreamingDesiredNumberOfVehiclesLoaded(int iDesiredNumVehiclesLoaded);

	// Set max number of stream handles.
	void SetMaxNumberOfStreamHandles(unsigned int iNumberOfStreamHandles);

	// Sets the number of requested models when game considers loading very busy.
	void SetTheNumberOfRequestedModelsAboveWhichLoadingIsVeryBusy(int iNumberOfRequestedModels);

	// Sets the minimum number of iterations in LoadAllRequestedModels
	void SetMinimumNumberOfIterationsInLoadAllRequestedModels(int minimumValue);
};

extern StreamingLimits g_streamingLimits;
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assertions.h>
#include "CFileID.h"
#include "../../ForOtherProjects/FLA_not_required/IDaccess.h"

// GTA III
namespace Game_GTAIII
{
	struct CStreamingInfo
	{
		CStreamingInfo *usNext;
		CStreamingInfo* usPrev;
		char uiLoadFlag;
		char ucFlags;
		uint16_t usNextOnCd;
		int iBlockOffset;
		int iBlockCount;

		//// Methods /////

		// Initializes CStreamingInfo
		void Init();
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CStreamingInfo, 0x14);
}

// GTA Vice City
namespace Game_GTAVC
{
	class CStreamingInfo
	{
	public:
	  CStreamingInfo *usNext;
	  CStreamingInfo *usPrev;
	  char uiLoadFlag;
	  char flags;
	  uint16_t usNextOnCd;
	  int FilePositionInBlocks;
	  int _unk_inCdImage;

	  //// Methods /////

	  // Initializes CStreamingInfo
	  void Init();
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CStreamingInfo, 0x14);
}

// GTA San Andreas
namespace Game_GTASA
{
	class CStreamingInfo
	{
	public:
		CFileIDex usNext;		// unused when 32-bit indices on
		CFileIDex usPrev;		// unused when 32-bit indices on
		CFileIDex usNextOnCd;	// unused when 32-bit indices on
		char ucFlags;
		uint8_t ucImgId;
		int iBlockOffset;		// m_OriginalSizeInSectors
		int iBlockCount;
		uint8_t uiLoadFlag;

		// Returns position and size of file
		bool GetCdPosnAndSize(unsigned int &outBlockOffsetWithStreamHandle, unsigned int &outBlockCount);

		// Sets position and size of file
		void SetCdPosnAndSize(unsigned int BlockOffset, unsigned int BlockCount);
	};

	VALIDATE_SIZE(CStreamingInfo, 0x14);
}

// Bully Scholarschip Edition
namespace Game_BullyScholarschipEdition
{
	struct CStreamingInfo
	{
		uint16_t usNext;
		uint16_t usPrev;
		uint8_t uiLoadFlag;
		char ucFlags;
		uint16_t usNextOnCd;
		int iBlockOffset;
		int iBlockCount;
	};

	VALIDATE_SIZE(CStreamingInfo, 0x10);
}

#define STORE_FILE_NAME_FIELD_IN_CSTREAMINGINFO_EXTENSION
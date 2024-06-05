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
		CStreamingInfo *m_nextIndex;
		CStreamingInfo* m_prevIndex;
		char m_status;
		char m_flags;
		uint16_t m_nextModelOnCd;
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
	  CStreamingInfo *m_nextIndex;
	  CStreamingInfo *m_prevIndex;
	  char m_status;
	  char flags;
	  uint16_t m_nextModelOnCd;
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
		CFileIDex m_nextIndex;		// unused when 32-bit indices on
		CFileIDex m_prevIndex;		// unused when 32-bit indices on
		CFileIDex m_nextModelOnCd;	// unused when 32-bit indices on
		char m_flags;
		uint8_t m_image;
		int iBlockOffset;		// m_OriginalSizeInSectors
		int iBlockCount;
		uint8_t m_status;

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
		uint16_t m_nextIndex;
		uint16_t m_prevIndex;
		uint8_t m_status;
		char m_flags;
		uint16_t m_nextModelOnCd;
		int iBlockOffset;
		int iBlockCount;
	};

	VALIDATE_SIZE(CStreamingInfo, 0x10);
}

#define STORE_FILE_NAME_FIELD_IN_CSTREAMINGINFO_EXTENSION
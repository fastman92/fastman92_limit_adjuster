/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assertions.h>
#include "CFileID.h"

struct CTimeInfo
{
	unsigned char m_nTimeOn;
	unsigned char m_nTimeOff;
	CFileID m_wOtherTimeModel;
};

VALIDATE_SIZE(CTimeInfo, 4);

class CBaseModelInfo_generic {};

// GTA III
namespace Game_GTAIII
{
	typedef CBaseModelInfo_generic CBaseModelInfo;
}

// GTA Vice City
namespace Game_GTAVC
{
	typedef CBaseModelInfo_generic CBaseModelInfo;
}

// GTA San Andreas
namespace Game_GTASA
{
	class CBaseModelInfo : public CBaseModelInfo_generic
	{
	public:
		struct BaseModelInfo_VTBL *vmt;
		int m_dwKey;
		int16_t m_wUsageCount;
		int16_t m_wTxdIndex;
		char field_C;
		char m_nbCount2dfx;
		int16_t m_w2dfxIndex;
		int16_t m_wObjectInfoIndex;
		int16_t m_wFlags;
		class CColModel *m_pColModel;
		int m_fDrawDistance;
		int m_pRwObject;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CBaseModelInfo, 0x20);
}

// GTA IV
namespace Game_GTAIV
{
	typedef CBaseModelInfo_generic CBaseModelInfo;
}

// Bully Scholarschip Edition
namespace Game_BullyScholarschipEdition
{
	typedef CBaseModelInfo_generic CBaseModelInfo;
}

#define UNDEFINED_AUDIO_ID -1

// extension
class CBaseModelInfo_extension
{
public:
	int32_t VehicleAudioID;

	// Initializes
	void Init()
	{
		this->VehicleAudioID = UNDEFINED_AUDIO_ID;
	}
};
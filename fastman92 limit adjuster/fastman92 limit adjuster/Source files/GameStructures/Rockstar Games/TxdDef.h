/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assertions.h>
#include <stdint.h>
#include "CFileID.h"

#include <DynamicTypes/DynamicStructure.h>

struct TxdDef_generic {};

// GTA San Andreas
namespace Game_GTASA
{
	struct TxdDef : public TxdDef_generic
	{
		void *dictionary;
		int16_t ref_counter;
		CFileID parent_index;
		uint32_t hash;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(TxdDef, 0xC);

	struct TxdDef_Android : public TxdDef
	{
		char TXDname[20];
		char TXDextension[20];
		bool field_34;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(TxdDef_Android, 0x38);
}

// GTA IV
namespace Game_GTAIV
{
	typedef void TxdDef;
}
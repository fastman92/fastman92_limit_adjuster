/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assertions.h>
#include "CBox.h"
#include "CSphere.h"
#include "IDstructures.h"

class CColModel_generic {};

namespace Game_GTASA
{
	// CColModel
	class CColModel : public CColModel_generic
	{
	public:
		CBox bbox;
		CSphere sphere;
		uint8_replacement COL_file_ID;
		char flags;
		char field_2A;
		char field_2B;
		struct ColDataHeader *m_pColData;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CColModel, 0x30);
}

// CColModel_extension
class CColModel_extension
{
public:
	CColModel_extension()
	{
		this->Init();
	}

	// Inits
	void Init()
	{
	}
};
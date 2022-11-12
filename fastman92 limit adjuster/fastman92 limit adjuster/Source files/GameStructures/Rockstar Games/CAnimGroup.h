/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assertions.h>
#include <stdint.h>

namespace Game_GTASA
{
	struct CAnimGroup
	{
	  char firstGroup;
	  char secondGroup;
	  int16_t field_2;
	  int field_4;
	  int field_8;
	  int field_C;
	  int field_10;
	  int field_14;
	  int field_18;
	  int field_1C;
	  int field_20[4];
	  int field_30[4];
	  int field_40;
	  int field_44;
	  int field_48;
	  int field_4C;
	  int field_50;
	  int field_54;
	  int field_58;
	  int field_5C;
	  int field_60;
	  int field_64;
	  int field_68;
	  int field_6C;
	  int field_70;
	  int field_74;
	  int field_78;
	  int field_7C;
	  int field_80;
	  int field_84;
	  int field_88;
	  int field_8C;
	  int field_90;
	};

	VALIDATE_SIZE(CAnimGroup, 0x94);
}
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

namespace Game_BullyScholarschipEdition
{
	enum eEntityType
	{
		ENTITY_TYPE_NOTHING,
		ENTITY_TYPE_BUILDING,	// building / threadable
		ENTITY_TYPE_VEHICLE,
		ENTITY_TYPE_PED,
		ENTITY_TYPE_OBJECT,	// object / projectile / cutscene object
		ENTITY_TYPE_DUMMY,
		ENTITY_TYPE_PROP_ANIM,
		ENTITY_TYPE_ACCESSORY,
	};
}

namespace Game_GTASA
{
	enum eEntityType
	{
		ENTITY_TYPE_NOTHING,
		ENTITY_TYPE_BUILDING,
		ENTITY_TYPE_VEHICLE,
		ENTITY_TYPE_PED,
		ENTITY_TYPE_OBJECT,
		ENTITY_TYPE_DUMMY,
		// ENTITY_TYPE_NOTINPOOLS
	};
}

namespace Game_GTAIV
{
	enum eEntityType
	{
		ENTITY_TYPE_NOTHING,
		ENTITY_TYPE_BUILDING,	// building or animated building
		ENTITY_TYPE_VEHICLE,
		ENTITY_TYPE_PED,
		ENTITY_TYPE_OBJECT,	// object / cutscene object

		ENTITY_TYPE_DUMMY_OBJECT,
		ENTITY_TYPE_DUMMY_PED,

		ENTITY_TYPE_PORTAL_INST,
		ENTITY_TYPE_INTERIOR_INST,

		ENTITY_TYPE_PARTICLE = 10,
	};
}
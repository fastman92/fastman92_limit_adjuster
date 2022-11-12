/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "Renderware.h"

#include "../../Core/LimitAdjuster.h"

#include "../../Core/FormattedOutput.h"

Renderware_VarInitialisation g_Renderware_varInitialisation;

MAKE_RwObject(RwObject, STRUCTURE_STATIC_MEMBER_DEFINITION);

// Initialize
void Renderware_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	// RwObject
	g_StructAllocator.InitPerStruct();

	g_StructAllocator.Allocate(RwObject::type);
	g_StructAllocator.Allocate(RwObject::subType);
	g_StructAllocator.Allocate(RwObject::flags);
	g_StructAllocator.Allocate(RwObject::privateFlags);
	g_StructAllocator.Allocate(RwObject::parent);

	g_StructAllocator.Allocate(RwObject::endOfStructure);
}
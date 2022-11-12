/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CFileID.h"
#include "CReference.h"

#include "../../Core\CLimitAdjusterModule.h"
#include "CReference.h"
#include "IDstructures.h"

#include "Renderware.h"

#include <DynamicTypes/DynamicStructure.h>
#include <stdint.h>

namespace details
{
	union u_RwObject
	{
		RwObject *m_pRwObject;
		RpClump *m_pRwClump;
		RpAtomic *m_pRwAtomic;
	};
}

union uLODinfoinEntity{
	int m_nLodIndex; // -1 - without LOD model
	CEntity *m_pLod;
};

union uTypeAndStateInEntity
{
	unsigned char m_nType : 3;
	unsigned char m_nState : 5;
};

#define MAKE_CEntity(structName, macro) \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, details::u_RwObject>), m_pRwThing); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, char[]>), m_nFlags); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint16_t>), m_wRandomSeed); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, CFileID>), m_wModelIndex); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, CReference*>), m_pReferences); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, void*>), m_pStreamingLink); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, short>), m_wScanCode); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint8_replacement>), m_nIplIndex); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint8_t>), m_nLevel); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint8_t>), m_nAreaCode); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uLODinfoinEntity>), m_LODinfo); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint8_t>), m_nNumLodChildren); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint8_t>), m_nNumLodChildrenRendered); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uTypeAndStateInEntity>), m_typeAndState); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tDynamicStructEnd>), endOfStructure);

class CEntity : public CDynamicStructure
{
public:
	MAKE_CEntity(CEntity, STRUCTURE_STATIC_MEMBER_DECLARATION);

	// Returns model ID
	uint32_t GetModelID() const;

	// Sets model ID
	void SetModelID(uint32_t modelID);
};

typedef CEntity CEntity_generic;

class CEntity_extension
{
public:
	// Constructor
	CEntity_extension();
};

class CEntity_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

typedef CEntity CObject_generic;
class CObject_extension {};

extern CEntity_VarInitialisation g_CEntity_varInitialisation;
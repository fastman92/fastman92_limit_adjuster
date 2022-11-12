/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CEntity.h"
#include "CFileID.h"

#include "../../Core/DynamicAssert.h"
#include "../../Core/LimitAdjuster.h"

#include "../../Core/FormattedOutput.h"

using namespace Game;

CEntity_VarInitialisation g_CEntity_varInitialisation;

MAKE_CEntity(CEntity, STRUCTURE_STATIC_MEMBER_DEFINITION);

// Constructor
CEntity_extension::CEntity_extension()
{

}

// Returns model ID
uint32_t CEntity::GetModelID() const
{
	return this->m_wModelIndex(this);
}

// Sets model ID
void CEntity::SetModelID(uint32_t modelID)
{
	this->m_wModelIndex(this) = modelID;
}

// Initialize
void CEntity_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	#ifdef IS_ARCHITECTURE_32_BIT
	else if (gameVersion == GAME_VERSION_GTA_III_1_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
	{
		g_StructAllocator.InitPerStruct();
		g_StructAllocator.SetTop(0x4C);
		g_StructAllocator.Allocate(CEntity::m_pRwThing);
		g_StructAllocator.Allocate(CEntity::m_typeAndState);
		g_StructAllocator.Allocate(CEntity::m_nFlags, 5);
		g_StructAllocator.SkipBytes(2);
		g_StructAllocator.Allocate(CEntity::m_wScanCode);
		g_StructAllocator.Allocate(CEntity::m_wRandomSeed);
		g_StructAllocator.Allocate(CEntity::m_wModelIndex);
		g_StructAllocator.Allocate(CEntity::m_nLevel);
		g_StructAllocator.Allocate(CEntity::m_nAreaCode);
		g_StructAllocator.Allocate(CEntity::m_pReferences);
		g_StructAllocator.Allocate(CEntity::endOfStructure);

		FLA_dynamic_assert(
			TypeDetails::SizeOf<CEntity>() == 0x64,
			"Size of CEntity is invalid!"
		);
	}
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion) || CGameVersion::Is_GTA_SA_1_0_1_EU_WIN_X86(gameVersion)
		|| CGameVersion::Is_GTA_SA_Android_Renderware(gameVersion))
	{
		g_StructAllocator.InitPerStruct();
		g_StructAllocator.SetTop(0x18);

		g_StructAllocator.Allocate(CEntity::m_pRwThing);
		g_StructAllocator.Allocate(CEntity::m_nFlags, 4);

		if (CGameVersion::Is_GTA_SA_Android_Renderware(gameVersion))
			g_StructAllocator.SkipBytes(4);

		g_StructAllocator.Allocate(CEntity::m_wRandomSeed);
		g_StructAllocator.Allocate(CEntity::m_wModelIndex);
		g_StructAllocator.Allocate(CEntity::m_pReferences);
		g_StructAllocator.Allocate(CEntity::m_pStreamingLink);
		g_StructAllocator.Allocate(CEntity::m_wScanCode);
		g_StructAllocator.Allocate(CEntity::m_nIplIndex);
		g_StructAllocator.Allocate(CEntity::m_nAreaCode);
		g_StructAllocator.Allocate(CEntity::m_LODinfo);
		g_StructAllocator.Allocate(CEntity::m_nNumLodChildren);
		g_StructAllocator.Allocate(CEntity::m_nNumLodChildrenRendered);
		g_StructAllocator.Allocate(CEntity::m_typeAndState);
		g_StructAllocator.Allocate(CEntity::endOfStructure);
		
		unsigned int expectedSize;

		if (CGameVersion::Is_GTA_SA_Android_Renderware(gameVersion))
			expectedSize = 0x3C;
		else
			expectedSize = 0x38;

		FLA_dynamic_assert(
			TypeDetails::SizeOf<CEntity>() == expectedSize,
			"Size of CEntity is invalid!"
			);
	}
	else if (CGameVersion::IsAny_GTA_LCS(gameVersion))
	{
		g_StructAllocator.InitPerStruct();
		g_StructAllocator.SetTop(0x58);

		g_StructAllocator.Allocate(CEntity::m_wModelIndex);
	}
	else if (CGameVersion::IsAny_GTA_VCS(gameVersion))
	{
		g_StructAllocator.InitPerStruct();
		g_StructAllocator.SetTop(0x56);

		g_StructAllocator.Allocate(CEntity::m_wModelIndex);
	}
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
	{
		g_StructAllocator.InitPerStruct();
		g_StructAllocator.SetTop(0x2E);
		
		g_StructAllocator.Allocate(CEntity::m_wModelIndex);

		g_StructAllocator.SkipBytes(0x44);
		g_StructAllocator.Allocate(CEntity::endOfStructure);
		
		FLA_dynamic_assert(
			TypeDetails::SizeOf<CEntity>() == 0x74,
			"Size of CEntity is invalid!"
		);
	}
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
	{
		g_StructAllocator.InitPerStruct();
		g_StructAllocator.SetTop(0x108);
		g_StructAllocator.Allocate(CEntity::m_typeAndState);
		g_StructAllocator.Allocate(CEntity::m_wScanCode);
		g_StructAllocator.Allocate(CEntity::m_wRandomSeed);
		g_StructAllocator.Allocate(CEntity::m_wModelIndex);
		g_StructAllocator.SkipBytes(0x10);	// I don't know what's there.
		g_StructAllocator.Allocate(CEntity::endOfStructure);

		FLA_dynamic_assert(
			TypeDetails::SizeOf<CEntity>() == 0x120,
			"Size of CEntity is invalid!"
		);
	}
	#endif
	else
		CEntity::m_wModelIndex.SetOffset(DYNAMIC_MEMBER_OFFSET_UNDEFINED);
}
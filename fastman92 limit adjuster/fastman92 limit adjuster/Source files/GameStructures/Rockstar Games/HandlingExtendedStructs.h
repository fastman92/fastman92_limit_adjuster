/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "Assertions.h"
#include "CAnimGroup.h"

#include <DynamicTypes/DynamicStructure.h>
#include <MultiPlatformSupport/PlatformGeneralisation.h>
#include "tHandlingData.h"

#define EXTENDED_cHandlingMgr_MAGIC_ID 0xFFFFFFFF

struct tIndexFirst
{
	unsigned int index;
};

struct tBikeHandlingData : tIndexFirst {};
struct tFlyingHandlingData : tIndexFirst {};
struct tBoatHandlingData : tIndexFirst {};

#define MAKE_tHandlingData_extended(structName, macro) \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, int>), index); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, char [15]>), handlingName); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, bool>), bIsStandardEntryAllocated); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tBikeHandlingData*>), pBikeHandling); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tFlyingHandlingData*>), pFlyingHandling); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tBoatHandlingData*>), pBoatHandling); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tDynamicStructEnd>), endOfStructure);
	
struct tHandlingData_extended : public CDynamicStructure
{
	union {
		Game_GTAIII::tHandlingData gta_iii;
		Game_GTAVC::tHandlingData gta_vc;
		Game_GTASA::tHandlingData gta_sa;
	}
	parent;

	MAKE_tHandlingData_extended(tHandlingData_extended, STRUCTURE_STATIC_MEMBER_DECLARATION);
};

#define MAKE_cHandlingDataMgr(structName, macro) \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, float>), field_0); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, float>), field_4); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, float>), field_8); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, float>), field_C); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, float>), field_10); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), cHandlingDataMgr_extended_magicID); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), sizeof_cHandlingDataMgr_header); \
/* current number of loaded entries */ \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, unsigned int>), numberOfVehicleLines); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, unsigned int>), numberOfBikeLines); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, unsigned int>), numberOfFlyingLines); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, unsigned int>), numberOfBoatLines); \
/* offsets */ \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_aStandardHandling_offset); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_aBikeHandling_offset); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_aFlyingHandling_offset); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_aBoatHandling_offset); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_pVehicleAnimGroups); \
/* sizes */ \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_sizeof_tHandlingData); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_sizeof_tBikeHandlingData); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_sizeof_tFlyingHandlingData); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_sizeof_tBoatHandlingData); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_sizeof_CAnimGroup); \
/* offsets */ \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_iStandardLinesLimit); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_iBikeLinesLimit); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_iFlyingLinesLimit); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_iBoatLinesLimit); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t>), m_iAnimationGroupLinesLimit); \
/* end of cHandlingDataMgr header */ \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tDynamicStructEnd>), endOfStructureHeader); \
/* arrays */ \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tHandlingData_extended[]>), m_standardEntryArray); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, char[]>), m_bikeEntryArray); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, char[]>), m_flyingEntryArray); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, char[]>), m_boatEntryArray); \
macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tDynamicStructEnd>), endOfStructure);

class cHandlingDataMgr : public CDynamicStructure
{
public:
	MAKE_cHandlingDataMgr(cHandlingDataMgr, STRUCTURE_STATIC_MEMBER_DECLARATION);

	// Initialized variables, used in cHandlingDataMgr::LoadHandlingData
	void InitVariables();

	// Returns handling ID by name
	int GetHandlingId(const char *handlingName);

	// Returns handling ID by name, creates if it doesn't exist.
	int GetHandlingIdAlways(const char *handlingName);

	// Returns handling ID by name
	int GetHandlingIdErrorIfNotFound(const char *handlingName);

	// Returns number of handling lines
	unsigned int GetNumberOfHandlingLines() { return this->numberOfVehicleLines(this); }

	// Coverts data to game units of all standard lines
	void ConvertDataToGameUnitsOfAllStandardLines();

	// Converts data to game units
	void __thiscall ConvertDataToGameUnits(tHandlingData_extended *handling);

	// Returns pointer to standard handling data
	tHandlingData_extended* __thiscall GetStandardPointer(uint16_t handlingID);
		
	// Returns pointer to flying handling data
	tBikeHandlingData* __thiscall GetBikePointer(uint16_t handlingID);

	// Returns pointer to flying handling data
	tFlyingHandlingData *__thiscall GetFlyingPointer(uint16_t handlingID);

	// Returns pointer to boat handling data
	tBoatHandlingData *__thiscall GetBoatPointer(uint16_t handlingID);

	/// Returns pointer always
	// Returns pointer to flying handling data
	tBikeHandlingData* __thiscall GetBikePointerAlways(uint16_t handlingID);

	// Returns pointer to flying handling data
	tFlyingHandlingData *__thiscall GetFlyingPointerAlways(uint16_t handlingID);

	// Returns pointer to boat handling data
	tBoatHandlingData *__thiscall GetBoatPointerAlways(uint16_t handlingID);
};
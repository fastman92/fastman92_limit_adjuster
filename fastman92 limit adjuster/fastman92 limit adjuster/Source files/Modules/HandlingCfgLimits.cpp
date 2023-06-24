/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "HandlingCfgLimits.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/CCodeMover.h"
#include "../Core/CPatch.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/eVehHandlingID.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

#include <string.h>

using namespace Game;

HandlingCfgLimits g_handlingCfgLimits;

const tLimitDefinitionNonStatic HandlingCfgLimits::ms_listOfLimits[5] =
{
	{ "Number of standard lines",  static_cast<tLimitMethodInt>(&HandlingCfgLimits::SetStandardLinesLimit) },
	{ "Number of bike lines",  static_cast<tLimitMethodInt>(&HandlingCfgLimits::SetBikeLinesLimit) },
	{ "Number of flying lines",  static_cast<tLimitMethodInt>(&HandlingCfgLimits::SetFlyingLinesLimit) },
	{ "Number of boat lines",  static_cast<tLimitMethodInt>(&HandlingCfgLimits::SetBoatLinesLimit) },
	{ "Number of animation group lines", static_cast<tLimitMethodInt>(&HandlingCfgLimits::SetAnimationGroupLinesLimit) }
};

// Initialized variables, used in cHandlingDataMgr::LoadHandlingData
void cHandlingDataMgr::InitVariables()
{
	// header
	this->cHandlingDataMgr_extended_magicID(this) = EXTENDED_cHandlingMgr_MAGIC_ID;
	this->sizeof_cHandlingDataMgr_header(this) = cHandlingDataMgr::endOfStructureHeader.GetOffset();

	this->numberOfVehicleLines(this) = 0;
	this->numberOfBikeLines(this) = 0;
	this->numberOfFlyingLines(this) = 0;
	this->numberOfBoatLines(this) = 0;

	// offsets
	this->m_aStandardHandling_offset(this) = this->m_standardEntryArray.GetOffset();
	this->m_aBikeHandling_offset(this) = this->m_bikeEntryArray.GetOffset();
	this->m_aFlyingHandling_offset(this) = this->m_flyingEntryArray.GetOffset();
	this->m_aBoatHandling_offset(this) = this->m_boatEntryArray.GetOffset();
	// this->m_pVehicleAnimGroups(this) = this->m_pVehicleAnimGroups();

	// sizes
	this->m_sizeof_tHandlingData(this) = g_handlingCfgLimits.m_sizeof_tHandlingData;
	this->m_sizeof_tBikeHandlingData(this) = g_handlingCfgLimits.m_sizeof_tBikeHandlingData;
	this->m_sizeof_tFlyingHandlingData(this) = g_handlingCfgLimits.m_sizeof_tFlyingHandlingData;
	this->m_sizeof_tBoatHandlingData(this) = g_handlingCfgLimits.m_sizeof_tBoatHandlingData;
	this->m_sizeof_CAnimGroup(this) = g_handlingCfgLimits.m_sizeof_CAnimGroup;

	// limits
	this->m_iStandardLinesLimit(this) = g_handlingCfgLimits.ms_iStandardLinesLimit;
	this->m_iBikeLinesLimit(this) = g_handlingCfgLimits.ms_iBikeLinesLimit;
	this->m_iFlyingLinesLimit(this) = g_handlingCfgLimits.ms_iFlyingLinesLimit;
	this->m_iBoatLinesLimit(this) = g_handlingCfgLimits.ms_iBoatLinesLimit;
	this->m_iAnimationGroupLinesLimit(this) = g_handlingCfgLimits.ms_iAnimationGroupLinesLimit;

	///////////////////////////

	// Make isStandardEntryAllocated = false for all standard lines.		
	for (unsigned int i = 0; i < this->m_iStandardLinesLimit(this); i++)
	{
		tHandlingData_extended* pStandardElement = &this->m_standardEntryArray.AtIndex(this, i);

		pStandardElement->bIsStandardEntryAllocated(pStandardElement) = false;

		pStandardElement->pBikeHandling(pStandardElement) = 0;
		pStandardElement->pFlyingHandling(pStandardElement) = 0;
		pStandardElement->pBoatHandling(pStandardElement) = 0;
	}
}

// Returns handling ID by name
int cHandlingDataMgr::GetHandlingId(const char *handlingName)
{
	for (unsigned int i = 0; i < this->numberOfVehicleLines(this); i++)
	{
		tHandlingData_extended* pStandardElement = &this->m_standardEntryArray.AtIndex(this, i);
		
		if (!_stricmp(pStandardElement->handlingName(pStandardElement),
			handlingName
			))
			return i;
	}

	return -1;
}

// Returns handling ID by name
int cHandlingDataMgr::GetHandlingIdErrorIfNotFound(const char *handlingName)
{
	int ID = this->GetHandlingId(handlingName);

	if (ID == -1)
	{
		printf_MessageBox(
			"Handling.cfg identifier name %s is assigned to vehicle, but cannot be found."
			, handlingName
		);
	}

	return ID;
}

// Returns handling ID by name, creates if it doesn't exist.
int cHandlingDataMgr::GetHandlingIdAlways(const char *handlingName)
{
	int ID = GetHandlingId(handlingName);
	
	if (ID == -1)
	{
		ID = this->numberOfVehicleLines(this)++;

	#ifdef HANDLING_CFG_CHECK_ARRAY_BOUNDS
		if ((unsigned int)ID >= g_handlingCfgLimits.ms_iStandardLinesLimit)
			printf_MessageBox("%s: handling.cfg limit of vehicles exceeded! New count: %d", __FUNCTION__, this->numberOfVehicleLines);
	#endif

		tHandlingData_extended* pStandardData = this->GetStandardPointer(ID);

		strncpy(
			pStandardData->handlingName(pStandardData),
			handlingName,
			TypeDetails::SizeOf(pStandardData->handlingName));
	}

	return ID;
}

// Converts data to game units of all standard lines
void cHandlingDataMgr::ConvertDataToGameUnitsOfAllStandardLines()
{
	for (unsigned int i = 0; i < this->numberOfVehicleLines(this); i++)
	{
		tHandlingData_extended* pStandardElement = &this->m_standardEntryArray.AtIndex(this, i);	

		if (pStandardElement->bIsStandardEntryAllocated(pStandardElement))
			this->ConvertDataToGameUnits(pStandardElement);
	}
}

static uintptr_t Address_cHandlingDataMgr__ConvertDataToGameUnits = 0;

// Converts data to game units
void __thiscall cHandlingDataMgr::ConvertDataToGameUnits(tHandlingData_extended *handling)
{
	return ((void(__thiscall *)(cHandlingDataMgr*, tHandlingData_extended *handling))Address_cHandlingDataMgr__ConvertDataToGameUnits)(this, handling);
}

// Returns pointer to standard handling data
tHandlingData_extended* __thiscall cHandlingDataMgr::GetStandardPointer(uint16_t handlingID)
{
	return &this->m_standardEntryArray.AtIndex(this, handlingID);
}

// Returns pointer to flying handling data
tBikeHandlingData* __thiscall cHandlingDataMgr::GetBikePointer(uint16_t handlingID)
{
	tHandlingData_extended* pStandardVehData = this->GetStandardPointer(handlingID);

	if (pStandardVehData->pBikeHandling(pStandardVehData))
		return pStandardVehData->pBikeHandling(pStandardVehData);
	else
		return (tBikeHandlingData*)this->m_bikeEntryArray(this);
}

// Returns pointer to flying handling data
tFlyingHandlingData* __thiscall cHandlingDataMgr::GetFlyingPointer(uint16_t handlingID)
{
	tHandlingData_extended* pStandardVehData = this->GetStandardPointer(handlingID);

	if (pStandardVehData->pFlyingHandling(pStandardVehData))
		return pStandardVehData->pFlyingHandling(pStandardVehData);
	else
		return (tFlyingHandlingData*)this->m_flyingEntryArray(this);
}

// Returns pointer to boat handling data
tBoatHandlingData *__thiscall cHandlingDataMgr::GetBoatPointer(uint16_t handlingID)
{
	tHandlingData_extended* pStandardVehData = this->GetStandardPointer(handlingID);

	if (pStandardVehData->pBoatHandling(pStandardVehData))
		return pStandardVehData->pBoatHandling(pStandardVehData);
	else
		return (tBoatHandlingData*)this->m_boatEntryArray(this);
}

// Returns pointer to bike handling data
tBikeHandlingData* __thiscall cHandlingDataMgr::GetBikePointerAlways(uint16_t handlingID)
{
	tHandlingData_extended* pStandardVehData = this->GetStandardPointer(handlingID);

	if (!pStandardVehData->pBikeHandling(pStandardVehData))
	{
		unsigned int idx = this->numberOfBikeLines(this)++;

	#ifdef HANDLING_CFG_CHECK_ARRAY_BOUNDS
		if (idx >= g_handlingCfgLimits.ms_iBikeLinesLimit)
			printf_MessageBox("%s: handling.cfg limit of bikes exceeded! New count: %d", __FUNCTION__, this->numberOfBikeLines);
	#endif

		tBikeHandlingData* ptr = (tBikeHandlingData*)
			(
				(char*)this->m_bikeEntryArray(this)
				+ idx * this->m_sizeof_tBikeHandlingData(this)
			);

		pStandardVehData->pBikeHandling(pStandardVehData) = ptr;
	}

	return pStandardVehData->pBikeHandling(pStandardVehData);
}
	
// Returns pointer to flying handling data
tFlyingHandlingData* __thiscall cHandlingDataMgr::GetFlyingPointerAlways(uint16_t handlingID)
{
	tHandlingData_extended* pStandardVehData = this->GetStandardPointer(handlingID);

	if (!pStandardVehData->pFlyingHandling(pStandardVehData))
	{
		unsigned int idx = this->numberOfFlyingLines(this)++;

	#ifdef HANDLING_CFG_CHECK_ARRAY_BOUNDS
		if (idx >= g_handlingCfgLimits.ms_iFlyingLinesLimit)
			printf_MessageBox("%s: handling.cfg limit of flying lines exceeded! New count: %d", __FUNCTION__, this->numberOfFlyingLines);
	#endif

		tFlyingHandlingData* ptr = (tFlyingHandlingData*)
			(
				(char*)this->m_flyingEntryArray(this)
				+ idx * this->m_sizeof_tFlyingHandlingData(this)
			);

		pStandardVehData->pFlyingHandling(pStandardVehData) = ptr;
	}

	return pStandardVehData->pFlyingHandling(pStandardVehData);
}
	
// Returns pointer to boat handling data
tBoatHandlingData *__thiscall cHandlingDataMgr::GetBoatPointerAlways(uint16_t handlingID)
{
	tHandlingData_extended* pStandardVehData = this->GetStandardPointer(handlingID);

	if (!pStandardVehData->pBoatHandling(pStandardVehData))
	{
		unsigned int idx = this->numberOfBoatLines(this)++;

	#ifdef HANDLING_CFG_CHECK_ARRAY_BOUNDS
		if (idx >= g_handlingCfgLimits.ms_iBoatLinesLimit)
			printf_MessageBox("%s: handling.cfg limit of boat lines exceeded! New count: %d", __FUNCTION__, this->numberOfBoatLines);
	#endif

		tBoatHandlingData* ptr = (tBoatHandlingData*)
			(
				(char*)this->m_boatEntryArray(this)
				+ idx * this->m_sizeof_tBoatHandlingData(this)
			);

		pStandardVehData->pBoatHandling(pStandardVehData) = ptr;
	}

	return pStandardVehData->pBoatHandling(pStandardVehData);
}

//////////////////////////////
// Returns pointer to mod_HandlingManager
cHandlingDataMgr* HandlingCfgLimits::Get_mod_HandlingManager()
{
	return mod_HandlingManager.ptr;
}

// Returns true if handling.cfg is hacked.
bool HandlingCfgLimits::IsHandlingCfgLimitHacked()
{
	return bIs_cHandlingDataMgr_extended;
}

// Sets standard limit
void HandlingCfgLimits::SetStandardLinesLimit(unsigned int iStandardLines)
{
	this->ms_iStandardLinesLimit = iStandardLines;
	this->ms_bStandardLinesLimitSet = true;
}

// Sets bike limit
void HandlingCfgLimits::SetBikeLinesLimit(unsigned int iBikeLines)
{
	this->ms_iBikeLinesLimit = iBikeLines;
	this->ms_bBikeLinesLimitSet = true;
}

// Sets flying limit
void HandlingCfgLimits::SetFlyingLinesLimit(unsigned int iFlyingLines)
{
	this->ms_iFlyingLinesLimit = iFlyingLines;
	this->ms_bFlyingLinesLimitSet = true;
}

// Sets boat limit
void HandlingCfgLimits::SetBoatLinesLimit(unsigned int iBoatLines)
{
	this->ms_iBoatLinesLimit = iBoatLines;
	this->ms_bBoatLinesLimitSet = true;
}

// Sets animation group limit
void HandlingCfgLimits::SetAnimationGroupLinesLimit(unsigned int iAnimationGroups)
{
	this->ms_iAnimationGroupLinesLimit = iAnimationGroups;
	this->ms_bAnimationGroupLinesLimitSet = true;
}

// common functions used in patches
extern "C"
{
	tHandlingData_extended* __cdecl LoadHandlingData_case_default_do(
		cHandlingDataMgr* pHandlingMgr,
		const char* handlingName
	)
	{
		unsigned int ID = pHandlingMgr->GetHandlingIdAlways(handlingName);

		tHandlingData_extended* pStandardVehData =
			pHandlingMgr->GetStandardPointer(ID);

		pStandardVehData->index(pStandardVehData) = ID;
		pStandardVehData->bIsStandardEntryAllocated(pStandardVehData) = true;
		return pStandardVehData;
	}

	::tBoatHandlingData * __cdecl LoadHandlingData_case_boat_do(
		cHandlingDataMgr* pHandlingMgr,
		const char* handlingName
	)
	{
		unsigned int standardID = pHandlingMgr->GetHandlingIdAlways(handlingName);
		::tBoatHandlingData * ptr = pHandlingMgr->GetBoatPointerAlways(standardID);

		ptr->index = standardID;
		return ptr;
	}

	::tBikeHandlingData * __cdecl LoadHandlingData_case_bike_do(
		cHandlingDataMgr* pHandlingMgr,
		const char* handlingName
	)
	{
		unsigned int standardID = pHandlingMgr->GetHandlingIdAlways(handlingName);
		::tBikeHandlingData * ptr = pHandlingMgr->GetBikePointerAlways(standardID);
		ptr->index = standardID;
		return ptr;
	}

	::tFlyingHandlingData * __cdecl LoadHandlingData_case_flying_do(
		cHandlingDataMgr* pHandlingMgr,
		const char* handlingName
	)
	{
		unsigned int standardID = pHandlingMgr->GetHandlingIdAlways(handlingName);
		::tFlyingHandlingData * ptr = pHandlingMgr->GetFlyingPointerAlways(standardID);
		ptr->index = standardID;
		return ptr;
	}

	bool IsBikeHandling(tHandlingData_extended* pStandardHandling)
	{
		return pStandardHandling->pBikeHandling(pStandardHandling) != 0;
	}

	bool IsRCbandit(tHandlingData_extended* pStandardHandling)
	{
		const char* pHandlingName = pStandardHandling->handlingName(pStandardHandling);

		return *(uint32_t*)pHandlingName == 'ABCR'
			&& *(uint32_t*)(pHandlingName + 4) == 'TIDN'
			&& *(uint8_t*)(pHandlingName + 8) == 0;
	}
}

///////////////////////////

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTAVC
{
	NAKED void patch_CAutomobile__CAutomobile_59E7D3()
	{
		__asm
		{
			push eax;
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, mod_HandlingManager);
			call cHandlingDataMgr::GetStandardPointer;

			mov     ecx, [esp + 0BCh - 0xB0];
			
			ASM_JMP_STATIC_ADDRESS(0x59E7E1);
		}
	}

	NAKED void patch_CBoat__CBoat_5A6553()
	{
		__asm
		{
			push ebx;
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, mod_HandlingManager);
			call cHandlingDataMgr::GetStandardPointer;

			mov     ecx, [esp + 14h - 0x10];
			mov[ecx + 0x120], eax;	// CBoat.__parent.pVehicleHandling

			mov     ax, bx;

			push 0x5A6571;
			retn;
		}
	}

	NAKED void patch_CBike__CBike_61585A()
	{
		__asm
		{
			push ebx;
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, mod_HandlingManager);
			call cHandlingDataMgr::GetStandardPointer;

			mov     ecx, [esp + 1Ch - 0x10];
			mov[ecx + 0x120], eax;	// CVehicle.pVehicleHandling

			push ebx;
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, mod_HandlingManager);
			call cHandlingDataMgr::GetBikePointer;

			mov     ecx, [esp + 1Ch - 0x10];
			mov[ecx + 0x324], eax;	// CBike.pBikeHandling

			push ebx;
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, mod_HandlingManager);
			ASM_JMP_STATIC_ADDRESS(0x61589B);
		}
	}

	NAKED void patch_cHandlingDataMgr__LoadHandlingData_5AAE20()
	{
		__asm
		{
			push ebx;
			push esi;
			push edi;
			push ebp;
			sub esp, 120h;

			mov[esp + 0x130 - 0x104], ecx;
			call cHandlingDataMgr::InitVariables;

			// go back
			ASM_JMP_STATIC_ADDRESS(0x5AAE2E);
		}
	}

	NAKED void patch_cHandlingDataMgr__LoadHandlingData_case_standard_5AB68C()
	{
		__asm
		{
			push eax;	// line
			push ecx; // this
			call LoadHandlingData_case_default_do;
			add esp, 8;
			mov ebx, eax;

			// go back
			ASM_JMP_STATIC_ADDRESS(0x5AB9B5);
		}
	}

	NAKED void patch_cHandlingDataMgr__LoadHandlingData_case_boat_5AB479()
	{
		__asm
		{
			push eax;	// line
			push     ecx; // this
			call LoadHandlingData_case_boat_do;
			add esp, 8;
			mov[esp + 130h - 0x120], eax;	// pointer to boat handling data

			// go back
			ASM_JMP_STATIC_ADDRESS(0x5AB61B);
		}
	}

	NAKED void patch_cHandlingDataMgr__LoadHandlingData_case_bike_5AAF59()
	{
		__asm
		{
			push eax;	// line
			push     ecx; // this
			call LoadHandlingData_case_bike_do;
			add esp, 8;
			mov [esp + 130h - 0x128], eax;	// pointer to bike handling data

			// go back
			ASM_JMP_STATIC_ADDRESS(0x5AB116)
		}
	}

	NAKED void patch_cHandlingDataMgr__LoadHandlingData_case_flying_5AB249()
	{
		__asm
		{
			push eax;	// line
			push     ecx; // this
			call LoadHandlingData_case_flying_do;
			add esp, 8;
			mov ebp, eax;	// pointer to flying handling data

			// go back
			ASM_JMP_STATIC_ADDRESS(0x5AB3F7);
		}
	}

	NAKED void patch_cHandlingDataMgr__LoadHandlingData_5AB9E7()
	{
		__asm
		{
			mov ecx, [esp + 0x130 - 0x104];	// this
			call cHandlingDataMgr::ConvertDataToGameUnitsOfAllStandardLines;

			add     esp, 120h;
			pop     ebp;
			pop     edi;
			pop     esi;
			pop     ebx;
			retn;
		}
	}

	NAKED void patch_cHandlingDataMgr__ConvertDataToGameUnits_5ABBFB()
	{
		__asm
		{
			push edx;

			push edx;
			call IsRCbandit;
			add esp, 4;

			pop edx;

			test al, al;
			jz notRCbandit;

			ASM_JMP_STATIC_ADDRESS(0x5ABC02);

		notRCbandit:
			push edx;

			push edx;
			call IsBikeHandling;
			add esp, 4;

			pop edx;

			test al, al;
			jz notBike;

			ASM_JMP_STATIC_ADDRESS(0x5ABC22);

		notBike:
			ASM_JMP_STATIC_ADDRESS(0x5ABC44);
		}
	}
}

// Patches handling.cfg limit
void HandlingCfgLimits::PatchHandlingCfgLimit_GTA_VC_PC_1_0()
{
	MAKE_VAR_GAME_VERSION();
	using namespace Game_GTAVC;

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
	{
		this->ms_iStandardLinesLimit = 106;
		this->ms_iBikeLinesLimit = 5;
		this->ms_iFlyingLinesLimit = 10;
		this->ms_iBoatLinesLimit = 11;
	}

	CGenericLogStorage::SaveFormattedTextLn("Enabling handling.cfg limit adjuster.\nNew limits:\n"
		"Number of standard lines = %d\n"
		"Number of bike lines = %d\n"
		"Number of flying lines = %d\n"
		"Number of boat lines = %d",

		ms_iStandardLinesLimit,
		ms_iBikeLinesLimit,
		ms_iFlyingLinesLimit,
		ms_iBoatLinesLimit
	);

	CGenericLogStorage::WriteLineSeparator();

	// Set up dynamic structures
	this->SetUpDynamicStructures(true);

	if (!CPatch::IsDebugModeActive())
	{
		bIs_cHandlingDataMgr_extended = true;

		this->m_sizeof_tHandlingData = TypeDetails::SizeOf<tHandlingData_extended>();

		mod_HandlingManager.ptr = (cHandlingDataMgr*)new char[
			TypeDetails::SizeOf<cHandlingDataMgr>()];

		memset(mod_HandlingManager.ptr, NULL, TypeDetails::SizeOf<cHandlingDataMgr>());

		mod_HandlingManager.bIsAllocated.Set(true);
	}

	/////////////////////////

	// sub_4843E5
	CPatch::PatchPointer(0x48447D + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager
	// sub_484B00
	CPatch::PatchPointer(0x484B98 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager

	// _ZN11CFileLoader17LoadVehicleObjectEPKc
	CPatch::PatchPointer(0x48C0D2 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager

	if (!CPatch::IsDebugModeActive())
	{
		auto _ptr = &cHandlingDataMgr::GetHandlingIdErrorIfNotFound;
		void*& ptr = (void*&)_ptr;

		CPatch::PutCallFunction(
			0x48C0DA,
			ptr
		);
	}

	// _ZN5CGame21InitialiseOnceAfterRWEv
	CPatch::PatchPointer(0x4A5034 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager; cHandlingDataMgr *

	// BiggerWheels
	{
		CPatch::PatchPointer(0x4AE58F + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_LANDSTAL].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fld     ds:mod_HandlingManager.vehicleHandling.TransmissionData.fEngineAcceleration
		CPatch::PatchPointer(0x4AE59B + 1, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BAGGAGE].parent.gta_vc.m_transmissionData);	// mov     ecx, (offset mod_HandlingManager.vehicleHandling+38ECh)
		CPatch::PatchPointer(0x4AE5A0 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_LANDSTAL].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fstp    ds:mod_HandlingManager.vehicleHandling.TransmissionData.fEngineAcceleration
		CPatch::PatchPointer(0x4AE5A6 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_PATRIOT].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fld     ds:mod_HandlingManager.vehicleHandling.TransmissionData.fEngineAcceleration+528h
		CPatch::PatchPointer(0x4AE5B2 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_PATRIOT].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fstp    ds:mod_HandlingManager.vehicleHandling.TransmissionData.fEngineAcceleration+528h
		CPatch::PatchPointer(0x4AE5B8 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BOBCAT].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fld     ds:mod_HandlingManager.vehicleHandling.TransmissionData.fEngineAcceleration+120Ch
		CPatch::PatchPointer(0x4AE5C4 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BOBCAT].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fstp    ds:mod_HandlingManager.vehicleHandling.TransmissionData.fEngineAcceleration+120Ch
		CPatch::PatchPointer(0x4AE5CA + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BFINJECT].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fld     dword ptr ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType+13C8h
		CPatch::PatchPointer(0x4AE5D6 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BFINJECT].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fstp    dword ptr ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType+13C8h
		CPatch::PatchPointer(0x4AE5DC + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_RANCHER].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fld     dword ptr ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType+3A74h
		CPatch::PatchPointer(0x4AE5E8 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_RANCHER].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fstp    dword ptr ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType+3A74h
		CPatch::PatchPointer(0x4AE5EE + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_DESPERAD].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fld     dword ptr ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType+4230h
		CPatch::PatchPointer(0x4AE5FA + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_DESPERAD].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fstp    dword ptr ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType+4230h
		CPatch::PatchPointer(0x4AE600 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_DELUXO].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fld     ds:mod_HandlingManager.vehicleHandling.TransmissionData.fEngineAcceleration+3624h
		CPatch::PatchPointer(0x4AE60C + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_DELUXO].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fstp    ds:mod_HandlingManager.vehicleHandling.TransmissionData.fEngineAcceleration+3624h
		CPatch::PatchPointer(0x4AE612 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BAGGAGE].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fld     ds:mod_HandlingManager.vehicleHandling.TransmissionData.fEngineAcceleration+38B8h
		CPatch::PatchPointer(0x4AE61E + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BAGGAGE].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fstp    ds:mod_HandlingManager.vehicleHandling.TransmissionData.fEngineAcceleration+38B8h
		CPatch::PatchPointer(0x4AE624 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BAGGAGE].parent.gta_vc.m_transmissionData.m_fMaxGearVelocity);	// fld     ds:mod_HandlingManager.vehicleHandling.TransmissionData.fMaxVelocity+38B8h
		CPatch::PatchPointer(0x4AE630 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BAGGAGE].parent.gta_vc.m_transmissionData.m_fMaxGearVelocity);	// fstp    ds:mod_HandlingManager.vehicleHandling.TransmissionData.fMaxVelocity+38B8h
		CPatch::PatchPointer(0x4AE63D + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_GOLFCART].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fld     dword ptr ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType+25D4h
		CPatch::PatchPointer(0x4AE649 + 1, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_GOLFCART].parent.gta_vc.m_transmissionData);	// mov     ecx, (offset mod_HandlingManager.vehicleHandling+2604h)
		CPatch::PatchPointer(0x4AE64E + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_GOLFCART].parent.gta_vc.m_transmissionData.m_fEngineAcceleration);	// fstp    dword ptr ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType+25D4h
		CPatch::PatchPointer(0x4AE654 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_GOLFCART].parent.gta_vc.m_transmissionData.m_fMaxGearVelocity);	// fld     ds:mod_HandlingManager.vehicleHandling.TransmissionData.fEngineAcceleration+25D4h
		CPatch::PatchPointer(0x4AE660 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_GOLFCART].parent.gta_vc.m_transmissionData.m_fMaxGearVelocity);	// fstp    ds:mod_HandlingManager.vehicleHandling.TransmissionData.fEngineAcceleration+25D4h
		CPatch::PatchPointer(0x4AE66B + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_STINGER].parent.gta_vc.fCollisionDamageMultiplier);	// fld     ds:mod_HandlingManager.vehicleHandling.fCollisionDamageMultiplier+1B8h
		CPatch::PatchPointer(0x4AE67E + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_STINGER].parent.gta_vc.fCollisionDamageMultiplier);	// fstp    ds:mod_HandlingManager.vehicleHandling.fCollisionDamageMultiplier+1B8h
		CPatch::PatchPointer(0x4AE684 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_STINGER].parent.gta_vc.fMass);	// fld     ds:mod_HandlingManager.vehicleHandling.fMass+1B8h
		CPatch::PatchPointer(0x4AE697 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_STINGER].parent.gta_vc.fMass);	// fstp    ds:mod_HandlingManager.vehicleHandling.fMass+1B8h
		CPatch::PatchPointer(0x4AE69D + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_STINGER].parent.gta_vc.fTurnMass);	// fld     ds:mod_HandlingManager.vehicleHandling.field_C+1B8h
		CPatch::PatchPointer(0x4AE6A9 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_STINGER].parent.gta_vc.fTurnMass);	// fstp    ds:mod_HandlingManager.vehicleHandling.field_C+1B8h
		CPatch::PatchPointer(0x4AE6AF + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BANSHEE].parent.gta_vc.fCollisionDamageMultiplier);	// fld     ds:mod_HandlingManager.vehicleHandling.fCollisionDamageMultiplier+1734h
		CPatch::PatchPointer(0x4AE6BB + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BANSHEE].parent.gta_vc.fCollisionDamageMultiplier);	// fstp    ds:mod_HandlingManager.vehicleHandling.fCollisionDamageMultiplier+1734h
		CPatch::PatchPointer(0x4AE6C1 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BANSHEE].parent.gta_vc.fMass);	// fld     ds:mod_HandlingManager.vehicleHandling.fMass+1734h
		CPatch::PatchPointer(0x4AE6CD + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BANSHEE].parent.gta_vc.fMass);	// fstp    ds:mod_HandlingManager.vehicleHandling.fMass+1734h
		CPatch::PatchPointer(0x4AE6D3 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BANSHEE].parent.gta_vc.fTurnMass);	// fld     ds:mod_HandlingManager.vehicleHandling.field_C+1734h
		CPatch::PatchPointer(0x4AE6DF + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_BANSHEE].parent.gta_vc.fTurnMass);	// fstp    ds:mod_HandlingManager.vehicleHandling.field_C+1734h
		CPatch::PatchPointer(0x4AE6E5 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_SABRETUR].parent.gta_vc.fCollisionDamageMultiplier);	// fld     ds:mod_HandlingManager.vehicleHandling.fCollisionDamageMultiplier+31D8h
		CPatch::PatchPointer(0x4AE6F1 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_SABRETUR].parent.gta_vc.fCollisionDamageMultiplier);	// fstp    ds:mod_HandlingManager.vehicleHandling.fCollisionDamageMultiplier+31D8h
		CPatch::PatchPointer(0x4AE6F7 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_SABRETUR].parent.gta_vc.fMass);	// fld     ds:mod_HandlingManager.vehicleHandling.fMass+31D8h
		CPatch::PatchPointer(0x4AE703 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_SABRETUR].parent.gta_vc.fMass);	// fstp    ds:mod_HandlingManager.vehicleHandling.fMass+31D8h
		CPatch::PatchPointer(0x4AE709 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_SABRETUR].parent.gta_vc.fTurnMass);	// fld     ds:mod_HandlingManager.vehicleHandling.field_C+31D8h
		CPatch::PatchPointer(0x4AE715 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_SABRETUR].parent.gta_vc.fTurnMass);	// fstp    ds:mod_HandlingManager.vehicleHandling.field_C+31D8h
		CPatch::PatchPointer(0x4AE71B + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_COMET].parent.gta_vc.fCollisionDamageMultiplier);	// fld     ds:mod_HandlingManager.vehicleHandling.fCollisionDamageMultiplier+3548h
		CPatch::PatchPointer(0x4AE727 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_COMET].parent.gta_vc.fCollisionDamageMultiplier);	// fstp    ds:mod_HandlingManager.vehicleHandling.fCollisionDamageMultiplier+3548h
		CPatch::PatchPointer(0x4AE72D + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_COMET].parent.gta_vc.fMass);	// fld     ds:mod_HandlingManager.vehicleHandling.fMass+3548h
		CPatch::PatchPointer(0x4AE739 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_COMET].parent.gta_vc.fMass);	// fstp    ds:mod_HandlingManager.vehicleHandling.fMass+3548h
		CPatch::PatchPointer(0x4AE73F + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_COMET].parent.gta_vc.fTurnMass);	// fld     ds:mod_HandlingManager.vehicleHandling.field_C+3548h
		CPatch::PatchPointer(0x4AE74B + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_COMET].parent.gta_vc.fTurnMass);	// fstp    ds:mod_HandlingManager.vehicleHandling.field_C+3548h
		CPatch::PatchPointer(0x4AE751 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_DELUXO].parent.gta_vc.fCollisionDamageMultiplier);	// fld     ds:mod_HandlingManager.vehicleHandling.fCollisionDamageMultiplier+3624h
		CPatch::PatchPointer(0x4AE75D + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_DELUXO].parent.gta_vc.fCollisionDamageMultiplier);	// fstp    ds:mod_HandlingManager.vehicleHandling.fCollisionDamageMultiplier+3624h
		CPatch::PatchPointer(0x4AE763 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_DELUXO].parent.gta_vc.fMass);	// fld     ds:mod_HandlingManager.vehicleHandling.fMass+3624h
		CPatch::PatchPointer(0x4AE76F + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_DELUXO].parent.gta_vc.fMass);	// fstp    ds:mod_HandlingManager.vehicleHandling.fMass+3624h
		CPatch::PatchPointer(0x4AE775 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_DELUXO].parent.gta_vc.fTurnMass);	// fld     ds:mod_HandlingManager.vehicleHandling.field_C+3624h
		CPatch::PatchPointer(0x4AE781 + 2, &mod_HandlingManager.ptr->m_standardEntryArray(mod_HandlingManager.ptr)[HANDLING_DELUXO].parent.gta_vc.fTurnMass);	// fstp    ds:mod_HandlingManager.vehicleHandling.field_C+3624h
	}

	// _ZN17CVehicleModelInfo24SetVehicleComponentFlagsEP7RwFramej
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x579E82, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchPointer(0x579E97 + 2, mod_HandlingManager.ptr);	// add     ebx, offset mod_HandlingManager

	CPatch::PatchUINT32(0x579E91 + 2, TypeDetails::SizeOf<tHandlingData_extended>());

	// sub_57A800
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x57A851, 0xB70F);	// make: movzx   eax, word ptr [ebx+46h]
		CPatch::PatchUINT16(0x57A855, 0xB70F);	// make: movzx   edx, ax
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x57A858 + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));
	
	CPatch::PatchPointer(0x57A85B + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.uFlags);	// mov     eax, ds:mod_HandlingManager.vehicleHandling.flags[edx*4]

	// _ZN11CAutomobile14ProcessControlEv
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x595EAE, 0xB70F);	// make: movzx   eax, word ptr [edx]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x595EB1 + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x595EB4 + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 52h
 
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x59621D, 0xB70F);	// make: movzx   eax, word ptr [edx]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x596220 + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x596223 + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 52h
	//////

	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x5965AA, 0xB70F);	// make: movzx   eax, word ptr [edx]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x5965AD + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x5965B0 + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 52h
	/////

	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x596684, 0xB70F);	// make: movzx   eax, word ptr [edx]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x596687 + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x59668A + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 52h

	/////
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x596844, 0xB70F);	// make: movzx   eax, word ptr [ecx]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x596847 + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x59684A + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 46h

	/////
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x59691E, 0xB70F);	// make: movzx   eax, word ptr [ebx]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x596921 + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x596924 + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 46h

	////
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x596B86, 0xB70F);	// make: movzx   eax, word ptr [edi]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x596B89 + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x596B8C + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 46h

	////
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x596DD9, 0xB70F);	// make: movzx   eax, word ptr [edx]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x596DDC + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x596DDF + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 46h

	////
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x596ED4, 0xB70F);	// make: movzx   eax, word ptr [edx]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x596ED7 + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x596EDA + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 46h

	////
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x596FC9, 0xB70F);	// make: movzx   eax, word ptr [esi]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x596FCC + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x596FCF + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 46h

	////
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x5970C2, 0xB70F);	// make: movzx   eax, word ptr [ecx]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x5970C5 + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x5970C8 + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 52h

	////
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x59742E, 0xB70F);	// make: movzx   eax, word ptr [ecx]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x597431 + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x597434 + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 52h

	/////
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x5977BA, 0xB70F);	// make: movzx   eax, word ptr [ecx]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x5977BD + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x5977C0 + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 52h

	////
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x597894, 0xB70F);	// make: movzx   eax, word ptr [ecx]
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT8(0x597897 + 2, TypeDetails::SizeOf<tHandlingData_extended>() / sizeof(uint32_t));
	
	CPatch::PatchPointer(0x59789A + 3, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_vc.m_transmissionData.m_nDriveType);	// cmp     ds:mod_HandlingManager.vehicleHandling.TransmissionData.nDriveType[eax*4], 52h

	// CAutomobile::constructor
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x59E7CB, 0xB70F);	// make: movzx   eax, bx
		CPatch::LeaveThisLevel();
	}

	CPatch::RedirectCode(0x59E7D3, &patch_CAutomobile__CAutomobile_59E7D3);

	CPatch::PatchPointer(0x59E7D9 + 1, mod_HandlingManager.ptr);	// add     eax, offset mod_HandlingManager
		
	CPatch::PatchPointer(0x59E7E7 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager

	// _ZN5CBoatC2Eih
	CPatch::PatchPointer(0x5A6560 + 2, mod_HandlingManager.ptr);	// add     ecx, offset mod_HandlingManager

	CPatch::RedirectCode(0x5A6553, &patch_CBoat__CBoat_5A6553);
	
	CPatch::PatchPointer(0x5A6571 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager

	CPatch::PatchPointer(0x5A657C + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager

	// _ZN16cHandlingDataMgrC2Ev
	CPatch::PatchUINT32(0x5ABDC3 + 1, TypeDetails::SizeOf<tHandlingData_extended>());

	CPatch::PatchPointer(0x5ABDCF + 1, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr));	// push    offset mod_HandlingManager.vehicleHandling; object

	CPatch::PatchPointer(0x5ABDE7 + 1, &mod_HandlingManager.ptr->m_flyingEntryArray.AtIndexZero(mod_HandlingManager.ptr));	// push    offset mod_HandlingManager.flyingHandling; object

	CPatch::PatchPointer(0x5ABDFF + 1, &mod_HandlingManager.ptr->m_boatEntryArray.AtIndexZero(mod_HandlingManager.ptr));	// push    offset mod_HandlingManager.boatHandling; object
	
	CPatch::PatchUINT32(0x5ABE09 + 1, TypeDetails::SizeOf<cHandlingDataMgr>() / sizeof(uint32_t));

	CPatch::PatchPointer(0x5ABE13 + 1, mod_HandlingManager.ptr);	// mov     edi, offset mod_HandlingManager

	// _ZN5CHeliC2Eih
	{
		CPatch::EnterNewLevelAndDisableDebugState();

		CPatch::PatchUINT16(0x5AF826, 0xB70F);	// make: movzx   eax, word ptr[ecx+CVehicleModel.handlingIndex]
		CPatch::PatchUINT16(0x5AF82A, 0xB70F);	// make: movzx   edx, ax
		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT32(0x5AF831 + 2, TypeDetails::SizeOf<tHandlingData_extended>());

	CPatch::PatchPointer(0x5AF837 + 2, mod_HandlingManager.ptr);	// add     edx, offset mod_HandlingManager

	// _ZN6CPlaneC2Eih
	CPatch::PatchPointer(0x5B2B97 + 2, mod_HandlingManager.ptr);	// add     edx, offset mod_HandlingManager

	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x5B2B86, 0xB70F);
		CPatch::PatchUINT16(0x5B2B8A, 0xB70F);

		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT32(0x5B2B91 + 2, TypeDetails::SizeOf<tHandlingData_extended>());

	// _ZN8CVehicle16ProcessBikeWheelER7CVectorS1_S1_S1_iffffcPfP11tWheelState17eBikeWheelSpecialt
	CPatch::PatchPointer(0x5B9AD2 + 2, &mod_HandlingManager.ptr->field_4(mod_HandlingManager.ptr));	// fmul    ds:mod_HandlingManager.field_4
	
	CPatch::PatchPointer(0x5B9B03 + 2, &mod_HandlingManager.ptr->field_4(mod_HandlingManager.ptr));	// fmul    ds:mod_HandlingManager.field_4
	
	CPatch::PatchPointer(0x5B9B25 + 2, &mod_HandlingManager.ptr->field_4(mod_HandlingManager.ptr));	// fmul    ds:mod_HandlingManager.field_4
	
	CPatch::PatchPointer(0x5B9B30 + 2, &mod_HandlingManager.ptr->field_4(mod_HandlingManager.ptr));	// fld     ds:mod_HandlingManager.field_4
	
	CPatch::PatchPointer(0x5BA392 + 2, &mod_HandlingManager.ptr->field_4(mod_HandlingManager.ptr));	// fmul    ds:mod_HandlingManager.field_4
	
	CPatch::PatchPointer(0x5BA3C3 + 2, &mod_HandlingManager.ptr->field_4(mod_HandlingManager.ptr));	// fmul    ds:mod_HandlingManager.field_4
	
	CPatch::PatchPointer(0x5BA3E5 + 2, &mod_HandlingManager.ptr->field_4(mod_HandlingManager.ptr));	// fmul    ds:mod_HandlingManager.field_4
	
	CPatch::PatchPointer(0x5BA3F0 + 2, &mod_HandlingManager.ptr->field_4(mod_HandlingManager.ptr));	// fld     ds:mod_HandlingManager.field_4

	// _ZN5CBikeC2Eih
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT16(0x6157C2, 0xB70F);

		CPatch::LeaveThisLevel();
	}

	CPatch::PatchUINT32(0x615865 + 2, TypeDetails::SizeOf<tHandlingData_extended>());

	if(!CPatch::IsDebugModeActive())
		CPatch::RedirectCode(0x61585A, &patch_CBike__CBike_61585A);

	CPatch::PatchPointer(0x615871 + 2, mod_HandlingManager.ptr);	// add     edx, offset mod_HandlingManager
	
	CPatch::PatchPointer(0x61587D + 2, mod_HandlingManager.ptr);	// add     ecx, offset mod_HandlingManager
	
	CPatch::PatchPointer(0x615890 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager

	// cHandlingDataMgr::GetFlyingPointer
	if (!CPatch::IsDebugModeActive())
		CPatch::RedirectMethod(0x5ABA70, &cHandlingDataMgr::GetFlyingPointer);

	// cHandlingDataMgr::GetBoatPointer
	if (!CPatch::IsDebugModeActive())
		CPatch::RedirectMethod(0x5ABA40, &cHandlingDataMgr::GetBoatPointer);

	// cHandlingDataMgr::LoadHandlingData
	if(!CPatch::IsDebugModeActive())
	{
		CPatch::RedirectCode(0x5AAE20, &patch_cHandlingDataMgr__LoadHandlingData_5AAE20);
		
		// cases
		CPatch::RedirectCode(0x5AB68C, &patch_cHandlingDataMgr__LoadHandlingData_case_standard_5AB68C);
		CPatch::RedirectCode(0x5AB479, &patch_cHandlingDataMgr__LoadHandlingData_case_boat_5AB479);
		CPatch::RedirectCode(0x5AAF59, &patch_cHandlingDataMgr__LoadHandlingData_case_bike_5AAF59);
		CPatch::RedirectCode(0x5AB249, &patch_cHandlingDataMgr__LoadHandlingData_case_flying_5AB249);
		
		// disable call to cHandlingDataMgr::ConvertDataToGameUnits
		CPatch::NOPinstructions(0x5AB9D2, 0x5AB9DC - 0x5AB9D2);

		// Make a call to cHandlingDataMgr::ConvertDataToGameUnitsOfAllStandardLines
		CPatch::RedirectCode(0x5AB9E7, &patch_cHandlingDataMgr__LoadHandlingData_5AB9E7);		

		// cHandlingDataMgr::ConvertDataToGameUnits
		// process RCBANDIT and bike handling lines
		CPatch::RedirectCode(0x5ABBFB, patch_cHandlingDataMgr__ConvertDataToGameUnits_5ABBFB);
	}
	
	/////////////////////////

	CPatch::LeaveThisLevel();
}
#endif

///////////////////////////
#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	//////////////////////////////////////////////////
	NAKED void patch_cHandlingDataMgr__LoadHandlingData_5BD830()
	{	
		__asm
		{
			sub     esp, 0FCh;
			push    ebp;
			push    esi;

			mov[esp + 1Ch], ecx;
			call cHandlingDataMgr::InitVariables;

			// go back
			ASM_JMP_STATIC_ADDRESS(0x5BD838);
		}
	}

	NAKED void patch_cHandlingDataMgr__LoadHandlingData_5BE468()
	{
		__asm
		{
			mov ecx,[esp + 0x104 - 0xE8];	// this
			call cHandlingDataMgr::ConvertDataToGameUnitsOfAllStandardLines;

			mov     edx, [esp+104h - 0xD8];
			push    edx             // ; FILE *

			// go back
			mov eax, 0x5BE46D;
			jmp eax;
		}
	}

	NAKED void patch_sub_8543D0()
	{	
		__asm
		{
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, mod_HandlingManager);
			mov eax, 0x6F5330;	// cHandlingDataMgr::cHandlingDataMgr
			jmp eax;
		}
	}

	NAKED void patch_CBike__CBike_6BF512()
	{	
		__asm
		{
			add     esp, 8;

			mov     edx, [esp + 2Ch + 8]; // mov     edx, [esp+2Ch+handIndex]
			push edx;
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, mod_HandlingManager);
			call cHandlingDataMgr::GetBikePointer;
			mov[esi + 0x63C], eax;	// CBike.pBikeHandling

			////////

			mov     edx, [esp + 2Ch + 8]; // mov     edx, [esp+2Ch+handIndex]
			push edx;
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, mod_HandlingManager);
			call cHandlingDataMgr::GetStandardPointer;
			mov[esi + 0x384], eax;	// CVehicle.pVehicleHandling
			mov ecx, eax;
			
			mov     edx, [esp + 2Ch + 8]; // mov     edx, [esp+2Ch+handIndex]

			// go back
			ASM_JMP_STATIC_ADDRESS(0x6BF53E);	// mov     eax, [ecx+tHandlingData.handlingFlags]
		}
	}

	NAKED void patch_CQuad__constructor_6CE3C6()
	{
		__asm
		{
			movzx   ecx, word ptr[ebp + 4Ah];	// [ebp+CVehicleModelInfo.handlingIndex]

			push ecx;
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, mod_HandlingManager);
			call cHandlingDataMgr::GetBikePointer;
			mov ecx, eax;

			// go back
			ASM_JMP_STATIC_ADDRESS(0x6CE3D3);
		}
	}

	NAKED void patch_cHandlingDataMgr__LoadHandlingData_case_standard_5BE1D3()
	{	
		__asm
		{
			push eax;	// line
			push edi; // this
			call LoadHandlingData_case_default_do;			
			add esp, 8;
			mov ebp, eax;
		
			// go back
			ASM_JMP_STATIC_ADDRESS(0x5BE430);
		}
	}

	NAKED void patch_cHandlingDataMgr__LoadHandlingData_case_boat_5BDBD8()
	{
		__asm
		{
			push eax;	// line
			push     edi; // this
			call LoadHandlingData_case_boat_do;
			add esp, 8;
			mov edi, eax;	// pointer to boat handling data

			// go back
			ASM_JMP_STATIC_ADDRESS(0x5BDCA0);
		}
	}

	NAKED void patch_cHandlingDataMgr__LoadHandlingData_case_bike_5BD8FC()
	{
		__asm
		{
			push eax;	// line
			push     edi; // this
			call LoadHandlingData_case_bike_do;
			add esp, 8;
			mov esi, eax;	// pointer to bike handling data

			// go back
			push 5BD9D2h;
			retn;
		}
	}

	NAKED void patch_cHandlingDataMgr__LoadHandlingData_case_flying_5BDA44()
	{
		__asm
		{
			push eax;	// line
			push     edi; // this
			call LoadHandlingData_case_flying_do;
			add esp, 8;
			mov esi, eax;	// pointer to flying handling data
			
			// go back
			push 5BDB6Eh;
			retn;
		}
	}

	NAKED void patch_cHandlingDataMgr__ConvertDataToGameUnits_6F515A()
	{
		__asm
		{
			
			push ecx;

			push ecx;
			call IsRCbandit;
			add esp, 4;

			pop ecx;
			
			test al, al;
			jz notRCbandit;

			push 6F5161h;
			retn;

	notRCbandit:
			push 6F5178h;
			retn;
		}
	}

	NAKED void patch_cHandlingDataMgr__ConvertDataToGameUnits_6F519E()
	{
		__asm
		{
			push ecx;

			push ecx;
			call IsBikeHandling;
			add esp, 4;

			pop ecx;

			test al, al;
			jz notBike;

			// bike
			push 0x6F51AC;
			retn;

	notBike:
			push 0x6F51CA;
			retn;
		}
	}
}

// Patches handling.cfg limit
void HandlingCfgLimits::PatchHandlingCfgLimit_GTA_SA_1_0_US_WIN_X86()
{
	MAKE_VAR_GAME_VERSION();
	using namespace Game_GTASA;

	// Patch pointers to mod_HandlingManager
	CPatch::EnterNewLevelAndDisableDebugState();
	if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
	{
		// char __thiscall CGarage::RightModTypeForThisGarage_HOODLUM(CGarage *this, CVehicle *veh)
		// change movzx   eax, byte ptr [edx+CModelCars.handlingIndex] INTO movzx   eax, word ptr [edx+CModelCars.handlingIndex]
		CPatch::PatchUINT16(0x1565273, 0xB70F);

		// .text:00447720; char __thiscall CGarage::RightModTypeForThisGarage(CGarage *this, CVehicle *veh)
		// .text:00447720     _ZN7CGarage25RightModTypeForThisGarageEP8CVehicle proc near
		CPatch::PatchUINT32(0x156527B + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// 	// imul    eax, 0E0h
		CPatch::PatchPointer(0x1565281 + 1, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr));
	}
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
	{
		// char __thiscall CGarage::RightModTypeForThisGarage_HOODLUM(CGarage *this, CVehicle *veh)
		// change movzx   eax, byte ptr [edx+CModelCars.handlingIndex] INTO movzx   eax, word ptr [edx+CModelCars.handlingIndex]
		CPatch::PatchUINT16(0x447733, 0xB70F);

		// .text:00447720; char __thiscall CGarage::RightModTypeForThisGarage(CGarage *this, CVehicle *veh)
		// .text:00447720     _ZN7CGarage25RightModTypeForThisGarageEP8CVehicle proc near
		CPatch::PatchUINT32(0x44773B + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// 	// imul    eax, 0E0h
		CPatch::PatchPointer(0x447741 + 1, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr));
	}
	CPatch::LeaveThisLevel();

	// opcode_096E
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x47850C, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x478510 + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// 	// imul    ecx, 0E0h
	CPatch::PatchPointer(0x478516 + 2, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_sa.handlingFlags);	// mov     edx, mod_HandlingManager.vehicleHandling.handlingFlags[ecx]

	// @@opcode_096F
	// change movzx   eax, byte ptr [edx+4Ah] INTO movzx   eax, word ptr [edx+4Ah]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x478559, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x47855D + 2, TypeDetails::SizeOf<tHandlingData_extended>()); // imul    eax, 0E0h
	CPatch::PatchPointer(0x478563 + 2, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_sa.handlingFlags);	// mov     ecx, mod_HandlingManager.vehicleHandling.handlingFlags[eax]

	// @@opcode_09E1
	// change movzx   edx, byte ptr [ecx+4Ah] INTO movzx   edx, word ptr [ecx+4Ah]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x47AEAA, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x47AEAE + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// imul    edx, 0E0h
	CPatch::PatchPointer(0x47AEB4 + 2, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_sa.m_nMonetaryValue);

	// CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors
	// change movzx   eax, byte ptr [edx+CModelCars.handlingIndex] INTO movzx   eax, word ptr [edx+CModelCars.handlingIndex]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x4C89BF, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x4C89C3 + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// imul    eax, 0E0h
	CPatch::PatchPointer(0x4C89CD + 1, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr)); // add     eax, offset mod_HandlingManager.vehicleHandling

	// void *__thiscall CVehicleModelInfo::PreprocessHierarchy(CModelCars *this)
	// change movzx   eax, byte ptr [edi+CModelCars.handlingIndex] INTO movzx   eax, word ptr [edi+CModelCars.handlingIndex]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x4C8E6F, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x4C8E76 + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// imul    eax, 0E0h
	CPatch::PatchPointer(0x4C8E7E + 1, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr)); // add     eax, offset mod_HandlingManager.vehicleHandling

	// char __thiscall CCam::GetBoatLook_L_R_HeightOffset(CCam *this, int a2)
	// change movsx   eax, byte ptr [ecx+CModelCars.handlingIndex] INTO movzx   eax, word ptr [ecx+CModelCars.handlingIndex]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x509CB5, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchPointer(0x509CBA + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager ; this

	// int __cdecl CFileLoader::LoadVehicleObject(const char *a1)
	CPatch::PatchPointer(0x5B7272 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager ; this

	if(!CPatch::IsDebugModeActive())
	{
		auto _ptr = &cHandlingDataMgr::GetHandlingIdErrorIfNotFound;
		void*& ptr = (void*&)_ptr;

		CPatch::PutCallFunction(
			0x5B7277,
			ptr
			);
	}

	// char __cdecl CGame::InitialiseCoreDataAfterRW()
	CPatch::PatchPointer(0x5BFA95 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager ; this
	CPatch::PutOnAddressRelative4byteAddressToAddress(0x5BFA9A + 1, 0x5BF3D0);	// CHANGE INTO call _ZN16cHandlingDataMgr10InitialiseEv

	// mov     mod_HandlingManager.field_xxx, ???
	CPatch::NOPinstructions(0x5BFAA4, 0x5BFAD6 - 0x5BFAA4);

	// sub_6A2F80
	// change movzx   ecx, byte ptr [edi+CModelCars.handlingIndex] INTO movzx   ecx, word ptr [edi+CModelCars.handlingIndex]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x6A2FC8, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x6A2FCC + 2, TypeDetails::SizeOf<tHandlingData_extended>()); // imul    ecx, 0E0h
	CPatch::PatchPointer(0x6A2FD2 + 2, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr));	// add     ecx, offset mod_HandlingManager.gta_sa.vehicleHandling

	// void __thiscall CAutomobile::ProcessCarWheelPair(int this, float a2, float a3, float f, int a5, int a6, float a7, float a8, float a9, char a10)
	CPatch::PatchPointer(0x6A4EEA + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager.gta_sa
	CPatch::PatchPointer(0x6A4F18 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager.gta_sa
	CPatch::PatchPointer(0x6A509F + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager.gta_sa

	// CAutomobile *__thiscall CAutomobile__constructor(void *this, int modelIndex, char a3, char a4)
	// change movsx   ecx, [ebp+CModelCars.handlingIndex] INTO movzx   ecx, [ebp+CModelCars.handlingIndex]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x6B0B29, 0xB70F);
	CPatch::LeaveThisLevel();

	// change movzx   eax, byte ptr [esp+0D0h+id] INTO movzx   eax, word ptr [esp+0D0h+id]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x6B0B97, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x6B0B9C + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// imul    eax, 0E0h
	CPatch::PatchPointer(0x6B0BA2 + 2, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr)); // lea     eax, mod_HandlingManager.gta_sa.vehicleHandling.index[eax]
	CPatch::PatchPointer(0x6B0BE1 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager.gta_sa ; this

	// int __thiscall CAutomobile__ProcessControl(CAutomobile *this)
	// change movsx   eax, word ptr [ecx+4Ah] INTO movzx   eax, word ptr [ecx+4Ah]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x6B218B, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchPointer(0x6B21A1 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager.gta_sa ; this

	// change movzx   edx, byte ptr [ecx] INTO movzx   edx, word ptr [ecx]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x6B2D1D, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x6B2D20 + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// imul    edx, 0E0h
	CPatch::PatchPointer(0x6B2D26 + 2, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_sa.m_transmissionData.m_nDriveType);	// cmp     mod_HandlingManager.gta_sa.vehicleHandling.transmissionData.nDriveType[edx], 'R'

	// change movzx   ecx, byte ptr [eax] INTO movzx   ecx, word ptr [eax]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x6B2D3F, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x6B2D42 + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// imul    ecx, 0E0h
	CPatch::PatchPointer(0x6B2D48 + 2, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr).parent.gta_sa.m_transmissionData.m_nDriveType);	// cmp     mod_HandlingManager.gta_sa.vehicleHandling.transmissionData.nDriveType[ecx], 'F'

	// CBike *__thiscall CBike__constructor(CBike *this, int model, char id)
	if (!CPatch::IsDebugModeActive())
		CPatch::RedirectCode(0x6BF512, &patch_CBike__CBike_6BF512);

	CPatch::PatchPointer(0x6BF545 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager.gta_sa ; this

	/*
	change this:
	.text:006CC3E7 0A4                 xor     ecx, ecx
	.text:006CC3E9 0A4                 mov     cl, [eax+4Ah]

	INTO

	movzx ecx,word ptr[eax+4A]	
	*/
	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::NOPinstructions(0x6CC3E7, 0x6CC3EC - 0x6CC3E7);
		CPatch::PatchUINT32(0x6CC3E7, 0x4A48B70F);
		CPatch::LeaveThisLevel();
	}

	// void __thiscall CPlane__m110(void *this)
	CPatch::PatchPointer(0x6CC3ED + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager.gta_sa ; this

	// CBike *__thiscall CQuad__constructor(int this, int a2, int a3)
	if (!CPatch::IsDebugModeActive())
	{
		CPatch::NOPinstructions(0x6CE3C6, 0x6CE3D3 - 0x6CE3C6);
		CPatch::RedirectCode(0x6CE3C6, &patch_CQuad__constructor_6CE3C6);
	}

	// CVehicle::ProcessWheel
	CPatch::PatchPointer(0x6D6E69 + 2, mod_HandlingManager.ptr->field_4.GetPtr(mod_HandlingManager.ptr));
	CPatch::PatchPointer(0x6D6EA8 + 2, mod_HandlingManager.ptr->field_4.GetPtr(mod_HandlingManager.ptr));

	// CVehicle::ProcessBikeWheel
	CPatch::PatchPointer(0x6D767F + 2, mod_HandlingManager.ptr->field_4.GetPtr(mod_HandlingManager.ptr));
	CPatch::PatchPointer(0x6D76AB + 2, mod_HandlingManager.ptr->field_4.GetPtr(mod_HandlingManager.ptr));
	CPatch::PatchPointer(0x6D76CD + 2, mod_HandlingManager.ptr->field_4.GetPtr(mod_HandlingManager.ptr));
	
	// sub_6F0D00
	// change movzx   eax, byte ptr [edx+CModelCars.handlingIndex] INTO movzx   eax, word ptr [edx+CModelCars.handlingIndex]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x6F0D4D, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x6F0D51 + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// imul    eax, 0E0h
	CPatch::PatchPointer(0x6F0D57 + 1, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr));

	// CBoat__constructor
	// change movzx eax,bl INTO movzx eax,bx
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x6F2A22, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x6F2A25 + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// imul    eax, 0E0h
	CPatch::PatchPointer(0x6F2A2B + 2, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr));	// lea     eax, mod_HandlingManager.gta_sa.vehicleHandling.index[eax]
	CPatch::PatchPointer(0x6F2A41 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager.gta_sa ; this
	CPatch::PatchPointer(0x6F2A52 + 1, mod_HandlingManager.ptr);	// mov     ecx, offset mod_HandlingManager.gta_sa ; this

	// CTrain::CTrain
	// change movzx   eax, byte ptr [ebp+CModelCars.handlingIndex] INTO movzx   eax, word ptr [ebp+CModelCars.handlingIndex]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x6F608B, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x6F608F + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// imul    eax, 0E0h
	CPatch::PatchPointer(0x6F6095 + 2, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr));

	// sub_8543D0 - initializes global variable mod_HandlingManager.gta_sa
	CPatch::RedirectFunction(0x8543D0, &patch_sub_8543D0);

	// CVehicleModelInfo::SetVehicleComponentFlags
	// change movzx   edi, byte ptr [ecx+CModelCars.handlingIndex] INTO movzx   edi, word ptr [ecx+CModelCars.handlingIndex]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x4C7C1B, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x4C7C1F + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// imul    edi, 0E0h

	CPatch::PatchPointer(0x4C7C25 + 2, &mod_HandlingManager.ptr->m_standardEntryArray.AtIndexZero(mod_HandlingManager.ptr));	// add     edi, offset mod_HandlingManager.gta_sa.vehicleHandling

	/////////////////////////////////////

	/// NO NEED TO PATCH:
	/*
	void __thiscall cHandlingDataMgr::ConvertDataToWorldUnits(cHandlingDataMgr *this, tHandlingData *handling)
	void __thiscall cHandlingDataMgr::ConvertDataToGameUnits(cHandlingDataMgr *this, tHandlingData *handling)
	void __thiscall cHandlingDataMgr::ConvertBikeDataToWorldUnits(cHandlingDataMgr *this, tBikeHandlingData *bikeHandling)
	void __thiscall cHandlingDataMgr::ConvertBikeDataToGameUnits(cHandlingDataMgr *this, tBikeHandlingData *bikeHandling)
	*/

	// char __thiscall cHandlingDataMgr::IsNotRearDriveVehicle(cHandlingDataMgr *this, uint8_t handlingID)
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x6A0480, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x6A0485 + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// imul    eax, 0E0h
	CPatch::PatchUINT32(0x6A048C + 3,
		this->mod_HandlingManager.ptr->m_standardEntryArray.GetOffset() + offsetof(tHandlingData, m_transmissionData) + offsetof(cTransmission, m_nDriveType)
		);

	// char __thiscall cHandlingDataMgr::IsNotFrontDriveVehicle(cHandlingDataMgr *this, uint8_t handlingID)
	// change movzx   eax, byte ptr [esp+handlingID] INTO movzx   eax, word ptr [esp+handlingID]
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchUINT16(0x6A04B0, 0xB70F);
	CPatch::LeaveThisLevel();

	CPatch::PatchUINT32(0x6A04B5 + 2, TypeDetails::SizeOf<tHandlingData_extended>());	// imul    eax, 0E0h
	CPatch::PatchUINT32(0x6A04BC + 3,
		this->mod_HandlingManager.ptr->m_standardEntryArray.GetOffset() + offsetof(tHandlingData, m_transmissionData) + offsetof(cTransmission, m_nDriveType)
		);

	// patch calls to cHandlingDataMgr::IsNotRearDriveVehicle
	// and cHandlingDataMgr::IsNotRearDriveVehicle
	{
		CPatch::EnterNewLevelAndDisableDebugState();

		// CAutomobile::ProcessCarWheelPair
		{
			CPatch::PatchUINT16(0x6A4EE7, 0x028B);

			CPatch::PatchUINT16(0x6A4F15, 0x118B);
			CPatch::PatchUINT16(0x6A509C, 0x088B);
		}

		CPatch::LeaveThisLevel();
	}
	
	if (!CPatch::IsDebugModeActive())
	{
		// tFlyingHandlingData *__thiscall cHandlingDataMgr::GetFlyingPointer(cHandlingDataMgr *this, uint8_t handlingID)
		CPatch::RedirectMethod(0x6F52D0, &cHandlingDataMgr::GetFlyingPointer);

		// tBoatHandlingData *__thiscall cHandlingDataMgr::GetBoatPointer(cHandlingDataMgr *this, uint8_t handlingID)
		CPatch::RedirectMethod(0x6F5300, &cHandlingDataMgr::GetBoatPointer);

		// void __thiscall cHandlingDataMgr::LoadHandlingData(cHandlingDataMgr *this)

		// initialization
		CPatch::RedirectCode(0x5BD830, &patch_cHandlingDataMgr__LoadHandlingData_5BD830);
		CPatch::NOPinstructions(0x5BD83D, 4);

		// disable call to cHandlingDataMgr::ConvertDataToGameUnits
		CPatch::NOPinstructions(0x5BE449, 0x5BE451 - 0x5BE449);

		// Make a call to cHandlingDataMgr::ConvertDataToGameUnitsOfAllStandardLines
		CPatch::RedirectCode(0x5BE468, &patch_cHandlingDataMgr__LoadHandlingData_5BE468);

		// cases
		CPatch::RedirectCode(0x5BE1D3, &patch_cHandlingDataMgr__LoadHandlingData_case_standard_5BE1D3);
		CPatch::RedirectCode(0x5BDBD8, &patch_cHandlingDataMgr__LoadHandlingData_case_boat_5BDBD8);
		CPatch::RedirectCode(0x5BD8FC, &patch_cHandlingDataMgr__LoadHandlingData_case_bike_5BD8FC);
		CPatch::RedirectCode(0x5BDA44, &patch_cHandlingDataMgr__LoadHandlingData_case_flying_5BDA44);

		// void __thiscall cHandlingDataMgr::ConvertDataToGameUnits(cHandlingDataMgr *this, tHandlingData *handling)
		CPatch::RedirectCode(0x6F515A, patch_cHandlingDataMgr__ConvertDataToGameUnits_6F515A);
		CPatch::RedirectCode(0x6F519E, patch_cHandlingDataMgr__ConvertDataToGameUnits_6F519E);
	}

	// void __thiscall cHandlingDataMgr::cHandlingDataMgr(cHandlingDataMgr *this)
	CPatch::PatchUINT32(0x6F5338 + 1, this->ms_iStandardLinesLimit);
	CPatch::PatchUINT32(0x6F5347 + 2, TypeDetails::SizeOf<tHandlingData_extended>());
	CPatch::PatchUINT32(0x6F5354 + 1, TypeDetails::SizeOf(*this->mod_HandlingManager.ptr) / sizeof(uint32_t));

	// int __thiscall cHandlingDataMgr::GetHandlingId(cHandlingDataMgr *this, const char *vehicleName)
	if(!CPatch::IsDebugModeActive())
		CPatch::RedirectMethod(0x6F4FD0, &cHandlingDataMgr::GetHandlingId);

	// Patch references to CVehicleAnimGroupData::m_vehicleAnimGroups
	#if TRUE
	{
		CPatch::PatchPointer(0x5BD4CF + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x5BE18D + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x639FCF + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x639FEA + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_8);	// mov     eax, ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_8[eax]
		CPatch::PatchPointer(0x63C883 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x642726 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x642CDB + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_8);	// mov     edx, ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_8[ecx]
		CPatch::PatchPointer(0x645615 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64563E + 1, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     eax, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64566A + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_8);	// mov     eax, ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_8[eax]
		CPatch::PatchPointer(0x64568A + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_8);	// mov     eax, ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_8[eax]
		CPatch::PatchPointer(0x6456AA + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_8);	// mov     eax, ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_8[eax]
		CPatch::PatchPointer(0x645FED + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64645D + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64664D + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64743B + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x6476CD + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64814C + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64836D + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x648ECC + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64ACA2 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64AE32 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64AEF9 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64B32C + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64B3FE + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64C3F7 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64CD20 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64D737 + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_8);	// mov     eax, ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_8[edx]
		CPatch::PatchPointer(0x64D803 + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_20);	// mov     eax, ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_20[eax]
		CPatch::PatchPointer(0x64D896 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64D9C7 + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_8);	// mov     edx, ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_8[ecx]
		CPatch::PatchPointer(0x64DA56 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64DAB5 + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_8);	// mov     dl, byte ptr ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_8[ecx]
		CPatch::PatchPointer(0x64E4C0 + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->firstGroup);	// lea     esi, _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.firstGroup[esi]; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64E4EA + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_8);	// mov     eax, ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_8[eax]
		CPatch::PatchPointer(0x64E7E8 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64EA3D + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64EB09 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64FCF3 + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_8);	// mov     edx, ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_8[edx]
		CPatch::PatchPointer(0x64FD18 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64FD36 + 1, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// mov     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x64FE4E + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// add     ecx, offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x65179B + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_8);	// mov     edx, ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_8[ecx]
		CPatch::PatchPointer(0x6517F3 + 2, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// lea     ebx, _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.firstGroup[eax]; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x6D09EA + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_8);	// mov     eax, ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_8[eax]
		CPatch::PatchPointer(0x6DF574 + 2, &CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa->field_8);	// mov     eax, ds:_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE.field_8[ecx]
		CPatch::PatchPointer(0x853E31 + 1, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// push    offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
		CPatch::PatchPointer(0x856A6C + 1, CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);	// push    offset _ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE; CVehicleAnimGroupData::m_vehicleAnimGroups
	}
	#endif
}
#endif

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
namespace Game_GTASA
{
	extern "C"
	{
		cHandlingDataMgr* mod_HandlingManager = 0;
		uint32_t cHandlingDataMgr__m_standardEntryArray_offset;
		uint32_t cHandlingDataMgr__m_standardEntryArray__transmissionData_offset = 0;
		uint32_t cHandlingDataMgr__m_standardEntryArray__transmissionData_end_offset = 0;
		uint32_t sizeof_cHandlingDataMgr = 0;
		uint32_t sizeof_tHandlingData = 0;

		uintptr_t Adddress_cHandlingDataMgr__cHandlingDataMgr = 0;
		uintptr_t Address_cHandlingDataMgr__GetHandlingIdErrorIfNotFound = 0;
		uintptr_t Address_cHandlingDataMgr__InitVariables = 0;
		uintptr_t Address_cHandlingDataMgr__ConvertDataToGameUnitsOfAllStandardLines = 0;
		uintptr_t Address_CGarage__RightModTypeForThisGarage = 0;
		uintptr_t Address_cHandlingDataMgr__GetBikePointer = 0;
	}

	///////
	extern "C"
	{
		uintptr_t Address_cHandlingDataMgr__cHandlingDataMgr_570C9C_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_cHandlingDataMgr__cHandlingDataMgr_570C94()
	{
		__asm(
		".thumb\n"
			"PUSH {R4,R5,R7,LR}\n"
			"ADD R7, SP, #8\n"
			"MOV R4, R0\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, cHandlingDataMgr__m_standardEntryArray__transmissionData_offset)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__cHandlingDataMgr_570C9C_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_cHandlingDataMgr__cHandlingDataMgr_570CAC_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_cHandlingDataMgr__cHandlingDataMgr_570CA2()
	{
		__asm(
		".thumb\n"
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, sizeof_tHandlingData)
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, cHandlingDataMgr__m_standardEntryArray__transmissionData_end_offset)
			"BNE 1f\n"
			"MOV R0, R4\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__cHandlingDataMgr_570CAC_thumb)

			"1:\n"	// loc_570C9C
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__cHandlingDataMgr_570C9C_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_sub_1A8050_1A8074_thumb = 0;
	}

	// ASM patches
	static TARGET_THUMB NAKED void patch_sub_1A8050_1A8050()
	{
		__asm(
		".thumb\n"
			"PUSH {R4,R5,R7,LR}\n"
			"ADD R7, SP, #8\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, mod_HandlingManager)
			ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(Adddress_cHandlingDataMgr__cHandlingDataMgr)
	
			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, mod_HandlingManager)
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, sizeof_cHandlingDataMgr)

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_sub_1A8050_1A8074_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_CFileLoader__LoadVehicleObject_199178_thumb = 0;
		uintptr_t Address_CFileLoader__LoadVehicleObject_469C58_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CFileLoader__LoadVehicleObject_469C50()
	{
		__asm(
		".thumb\n"
			ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__GetHandlingIdErrorIfNotFound)
			"STRH R0, [R4,#0x62]\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CFileLoader__LoadVehicleObject_469C58_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_cHandlingDataMgr__LoadHandlingData_4731E4_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_cHandlingDataMgr__LoadHandlingData_4731D8()
	{
		__asm(
		".thumb\n"
			"PUSH {R4-R7,LR}\n"
			"ADD R7, SP, #0xC\n"
			"PUSH {R8-R11}\n"
			"SUB SP, SP, #0x7C\n"

			"STR             R0, [SP,#0x98-0x38]\n"
			ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__InitVariables)

			"LDR             R0, [SP,#0x98-0x38]\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__LoadHandlingData_4731E4_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_cHandlingDataMgr__LoadHandlingData_473EF8_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_cHandlingDataMgr__LoadHandlingData_473EF0()
	{
		__asm(
		".thumb\n"
			"LDR             R0, [SP,#0x98-0x38]\n"	// this
			ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__ConvertDataToGameUnitsOfAllStandardLines)

			"MOV R0, R8\n"
			"ADD SP, SP, #0x7C\n"
			"POP {R8-R11}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__LoadHandlingData_473EF8_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_cHandlingDataMgr__LoadHandlingData_4735B6_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_cHandlingDataMgr__LoadHandlingData_standard_473318()
	{
		__asm(
			".thumb\n"
			"LDR             R0, [SP,#0x98-0x38]\n"	// this
			"MOV             R1, R3\n"	// line
			"BLX LoadHandlingData_case_default_do\n"
			"MOV R11, R0\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__LoadHandlingData_4735B6_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_cHandlingDataMgr__LoadHandlingData_473752_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_cHandlingDataMgr__LoadHandlingData_boat_473616()
	{
		__asm(
			".thumb\n"
			"LDR             R0, [SP,#0x98-0x38]\n"	// this
			"BLX LoadHandlingData_case_boat_do\n"
			"MOV R6, R0\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__LoadHandlingData_473752_thumb)
			);
	}
	
	extern "C"
	{
		uintptr_t Address_cHandlingDataMgr__LoadHandlingData_473C2E_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_cHandlingDataMgr__LoadHandlingData_bike_473ADC()
	{
		__asm(
			".thumb\n"
			"LDR             R0, [SP,#0x98-0x38]\n"	// this
			"BLX LoadHandlingData_case_bike_do\n"
			"MOV R9, R0\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__LoadHandlingData_473C2E_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_cHandlingDataMgr__LoadHandlingData_473A8A_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_cHandlingDataMgr__LoadHandlingData_flying_47389A()
	{
		__asm(
			".thumb\n"
			"LDR             R0, [SP,#0x98-0x38]\n"	// this
			"BLX LoadHandlingData_case_flying_do\n"
			"STR             R0, [SP,#0x98-0x34]\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__LoadHandlingData_473A8A_thumb)
			);
	}

	// Addresses
	extern "C"
	{
		uintptr_t Address_cHandlingDataMgr__ConvertDataToGameUnits_570D60_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_cHandlingDataMgr__ConvertDataToGameUnits_570D58()
	{		
		__asm(
			".thumb\n"
			"PUSH {R4, LR}\n"

			"VLDR S0, 1f\n"
			"VMOV.F32 S4, #1.0\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__ConvertDataToGameUnits_570D60_thumb)

			// data
			ASM_PUT_CONSTANT_FLOAT(1, 0.008)
			);
	}

	extern "C"
	{
		uintptr_t Address_cHandlingDataMgr__ConvertDataToGameUnits_570EE0_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_cHandlingDataMgr__ConvertDataToGameUnits_570ED8()
	{
		__asm(
		".thumb\n"			
			"VMUL.F32 S0, S0, S2\n"
			"VSTR S0, [R1,#0x7C]\n"

			"POP {R4, LR}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__ConvertDataToGameUnits_570EE0_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_cHandlingDataMgr__ConvertDataToGameUnits_570E6E_thumb = 0;
		uintptr_t Address_cHandlingDataMgr__ConvertDataToGameUnits_570E68_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_cHandlingDataMgr__ConvertDataToGameUnits_570E5E()
	{
		__asm(
			".thumb\n"
				
			"PUSH {R0, R1}\n"
			"MOV R0, R1\n"
			"BLX IsRCbandit\n"
			"CMP R0, #0\n"
			"POP {R0, R1}\n"

			"BEQ 1f\n"

			"VNEG.F32 S4, S2\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__ConvertDataToGameUnits_570E68_thumb)			

			"1:\n"	// loc_570E6E
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__ConvertDataToGameUnits_570E6E_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_cHandlingDataMgr__ConvertDataToGameUnits_570EB0_thumb = 0;
		uintptr_t Address_cHandlingDataMgr__ConvertDataToGameUnits_570E8C_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_cHandlingDataMgr__ConvertDataToGameUnits_570E7A()
	{
		__asm(
		".thumb\n"
			"PUSH {R0, R1}\n"

			"MOV R0, R1\n"
			"BLX IsBikeHandling\n"

			"CMP R0, #0\n"
			"POP {R0, R1}\n"

			"VMUL.F32 S2, S6, S2\n"
			"VSTR S2, [R1,#0x84]\n"
			"VSTR S6, [R1,#0x88]\n"
			
			"BEQ 1f\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__ConvertDataToGameUnits_570E8C_thumb)

			"1:\n"	// loc_570EB0
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__ConvertDataToGameUnits_570EB0_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_CGarage__Update_30EFB2_thumb = 0;
		uintptr_t Address_CGarage__Update_3102F2_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CGarage__Update_30EBD0()
	{
		__asm(
			".thumb\n"
			"MOV R1, R0\n"	// pVehicle
			"MOV R0, R4\n"	// this
			ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(Address_CGarage__RightModTypeForThisGarage)
			"CMP R0, #0\n"
			"BEQ 1f\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CGarage__Update_30EFB2_thumb)

			"1:\n"	// def_30EF8E
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CGarage__Update_3102F2_thumb)			
			);
	}

	extern "C"
	{
		uintptr_t Address_CGarage__Update_31034A_thumb = 0;
		uintptr_t Address_CGarage__Update_310334_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CGarage__Update_30F302()
	{
		__asm(
		".thumb\n"
			"MOV R1, R0\n"	// pVehicle
			"MOV R0, R4\n"	// this
			ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(Address_CGarage__RightModTypeForThisGarage)
			"CMP R0, #0\n"
			"BEQ 1f\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CGarage__Update_310334_thumb)

			"1:\n"	// loc_31034A
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CGarage__Update_31034A_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_CGarage__RightModTypeForThisGarage_312F48_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CGarage__RightModTypeForThisGarage_312F40()
	{
		__asm(
		".thumb\n"
			"LDRB R1, [R0,#0x4C]\n"
			"LDRH R0, [R2,#0x62]\n"	// handling index

			ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, sizeof_tHandlingData)
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, cHandlingDataMgr__m_standardEntryArray_offset)
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, mod_HandlingManager)

			"LDRB          R0, [R0,#0xD3]\n"	// &handlingFlags + 3

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CGarage__RightModTypeForThisGarage_312F48_thumb)
			);
	}

	/////// Macros ///////
	#define LOAD_HANDLING_POINTER_FROM_HANDLING_INDEX(reg) ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(reg, sizeof_tHandlingData) \
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(reg, cHandlingDataMgr__m_standardEntryArray_offset) \
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(reg, mod_HandlingManager)

	#define LOAD_HANDLING_POINTER_FROM_VEHICLE_MODEL_INFO(reg) "LDRH "#reg", ["#reg",#0x62]\n" /* handling index*/ \
		LOAD_HANDLING_POINTER_FROM_HANDLING_INDEX(reg)
	/////////////////////

	extern "C"
	{
		uintptr_t Address_CRunningScript__ProcessCommands2400To2499_33CAC4_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CRunningScript__ProcessCommands2400To2499_33CAB0()
	{
		__asm(
			".thumb\n"
			LOAD_HANDLING_POINTER_FROM_VEHICLE_MODEL_INFO(R0)
			"LDR.W           R0, [R0,#0xE4-0x14]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CRunningScript__ProcessCommands2400To2499_33CAC4_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_CRunningScript__ProcessCommands2400To2499_33CB1C_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CRunningScript__ProcessCommands2400To2499_33CB08()
	{
		__asm(
			".thumb\n"

			LOAD_HANDLING_POINTER_FROM_VEHICLE_MODEL_INFO(R0)
			"LDR.W           R0, [R0,#0xE4-0x14]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CRunningScript__ProcessCommands2400To2499_33CB1C_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_CRunningScript__ProcessCommands2500To2599_33F090_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CRunningScript__ProcessCommands2500To2599_33EE04()
	{
		__asm(
		".thumb\n"
			LOAD_HANDLING_POINTER_FROM_VEHICLE_MODEL_INFO(R1)
			"LDR.W           R1, [R1,#0xEC-0x14]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CRunningScript__ProcessCommands2500To2599_33F090_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_CVehicleModelInfo__PreprocessHierarchy_38745A_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CVehicleModelInfo__PreprocessHierarchy_387450()
	{
		__asm(
			".thumb\n"
			ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, sizeof_tHandlingData)

			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, cHandlingDataMgr__m_standardEntryArray_offset)
			"ADD R1, R2\n"
			"ADD R1, #%c[offset_modelFlags]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVehicleModelInfo__PreprocessHierarchy_38745A_thumb)

			::[offset_modelFlags]"i"(offsetof(tHandlingData, modelFlags))
			);
	}

	extern "C"
	{
		uintptr_t Address_CVehicleModelInfo__SetVehicleComponentFlags_3883C0_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CVehicleModelInfo__SetVehicleComponentFlags_3883AE()
	{
		__asm(
		".thumb\n"
			"MOV R0, R6\n"
			LOAD_HANDLING_POINTER_FROM_HANDLING_INDEX(R0)
			"LDR           R0, [R0,#%c[offset_modelFlags]]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVehicleModelInfo__SetVehicleComponentFlags_3883C0_thumb)

			::[offset_modelFlags]"i"(offsetof(tHandlingData, modelFlags))
			);
	}

	extern "C"
	{
		uintptr_t Address_CVehicleModelInfo__SetVehicleComponentFlags_38844A_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CVehicleModelInfo__SetVehicleComponentFlags_388438()
	{
		__asm(
		"	.thumb\n"
			"MOV R0, R6\n"
			LOAD_HANDLING_POINTER_FROM_HANDLING_INDEX(R0)
			"LDR           R0, [R0,#%c[offset_modelFlags]]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVehicleModelInfo__SetVehicleComponentFlags_38844A_thumb)

			::[offset_modelFlags]"i"(offsetof(tHandlingData, modelFlags))
			);
	}

	extern "C"
	{
		uintptr_t Address_CVehicleModelInfo__GetMaximumNumberOfPassengersFromNumberOfDoors_388F92_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CVehicleModelInfo__GetMaximumNumberOfPassengersFromNumberOfDoors_388F80()
	{
		__asm(
			".thumb\n"
			"MOV R1, LR\n"
			LOAD_HANDLING_POINTER_FROM_HANDLING_INDEX(R1)
			"LDRB R1, [R1,#%c[offset_modelFlags]+1]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVehicleModelInfo__GetMaximumNumberOfPassengersFromNumberOfDoors_388F92_thumb)

			::[offset_modelFlags]"i"(offsetof(tHandlingData, modelFlags))
			);
	}

	extern "C"
	{
		uintptr_t Address_CVehicleModelInfo__GetMaximumNumberOfPassengersFromNumberOfDoors_38901E_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CVehicleModelInfo__GetMaximumNumberOfPassengersFromNumberOfDoors_38900C()
	{
		__asm(
			".thumb\n"
			"MOV R1, LR\n"
			LOAD_HANDLING_POINTER_FROM_HANDLING_INDEX(R1)
			"LDRB R1, [R1,#%c[offset_modelFlags]+1]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVehicleModelInfo__GetMaximumNumberOfPassengersFromNumberOfDoors_38901E_thumb)

			::[offset_modelFlags]"i"(offsetof(tHandlingData, modelFlags))
			);
	}

	extern "C"
	{
		uintptr_t Address_CPad__GetHandBrake_3FA8E6 = 0;
		uintptr_t Address_CPad__GetHandBrake_3FA8F2_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPad__GetHandBrake_3FA8DE()
	{
		__asm(
		".thumb\n"
			"LDRH R0, [R0]\n"	// handling index

			LOAD_HANDLING_POINTER_FROM_HANDLING_INDEX(R0)

			"LDRB R0, [R0,#%c[offset_transmissionData_nDriveType]]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPad__GetHandBrake_3FA8F2_thumb)

			::[offset_transmissionData_nDriveType]"i"(offsetof(tHandlingData, m_transmissionData) + offsetof(cTransmission, m_nDriveType))
			);
	}

	extern "C"
	{
		uintptr_t Address_CAutomobile__CAutomobile_54E330_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CAutomobile__CAutomobile_54E314()
	{
		__asm(
			".thumb\n"
			"MOV R1, R5\n"
			LOAD_HANDLING_POINTER_FROM_HANDLING_INDEX(R1)

			"STR.W           R1, [R4,#0x388]\n"
			"LDR.W           R0, [R1,#%c[offset_handlingFlags]]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CAutomobile__CAutomobile_54E330_thumb)

				::[offset_handlingFlags]"i"(offsetof(tHandlingData, handlingFlags))
				);
	}

	extern "C"
	{
		uintptr_t Address_CAutomobile__ProcessCarWheelPair_556B06_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CAutomobile__ProcessCarWheelPair_556AF6()
	{
		__asm(
		".thumb\n"
			"VLDR S22, [R7,#0x10]\n"
			
			LOAD_HANDLING_POINTER_FROM_HANDLING_INDEX(R1)
			
			"LDRB R1, [R1,#%c[offset_transmissionData_nDriveType]]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CAutomobile__ProcessCarWheelPair_556B06_thumb)

			::[offset_transmissionData_nDriveType]"i"(offsetof(tHandlingData, m_transmissionData) + offsetof(cTransmission, m_nDriveType))
			);
	}

	extern "C"
	{
		uintptr_t Address_CAutomobile__ProcessCarWheelPair_556B74_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CAutomobile__ProcessCarWheelPair_556B64()
	{
		__asm(
		".thumb\n"
			"LDRB R0, [R0,#%c[offset_transmissionData_nDriveType]]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CAutomobile__ProcessCarWheelPair_556B74_thumb)

			::[offset_transmissionData_nDriveType]"i"(offsetof(tHandlingData, m_transmissionData) + offsetof(cTransmission, m_nDriveType))
			);
	}

	extern "C"
	{
		uintptr_t Address_CAutomobile__DebugCode_55CAEC = 0;
		uintptr_t Address_CAutomobile__DebugCode_55CB0E_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CAutomobile__DebugCode_55CAE2()
	{
		__asm(
			".thumb\n"
			"MOV R0, R5\n"

			LOAD_HANDLING_POINTER_FROM_VEHICLE_MODEL_INFO(R0)

			"VLDR S2, 1f\n"

			"LDR R1, [R0,#0x18-0x14]\n"
			"STR R1, [R4,#0x90-0x14]\n"
			"LDR R1, [R0,#0x20-0x14]\n"
			"STR R1, [R4,#0x94-0x14]\n"
			"LDR R1, [R0,#0x38-0x14]\n"
			"STR R1, [R4,#0xA4-0x14]\n"
			"VLDR S0, [R0,#0x24-0x14]\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CAutomobile__DebugCode_55CB0E_thumb)

			ASM_PUT_CONSTANT_FLOAT(1, 0.01)
			);
	}

	extern "C"
	{
		uintptr_t Address_CBike__CBike_56049E_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CBike__CBike_560472()
	{
		__asm(
			".thumb\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, mod_HandlingManager)
			"MOV             R1, R6\n"
			ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__GetBikePointer)

			"STR.W           R1, [R4,#0x650]\n"	// CAutomobile.pBikeHandling

			"MOV R2, R6\n" // handling index
			LOAD_HANDLING_POINTER_FROM_HANDLING_INDEX(R2)

			"STR.W           R2, [R4,#0x388]\n"	// CAutomobile.pStandardHandling

			"LDR.W           R1, [R2,#%c[offset_handlingFlags]]\n"
			"STR.W           R1, [R4,#0x390]\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, mod_HandlingManager)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CBike__CBike_56049E_thumb)
				::[offset_handlingFlags]"i"(offsetof(tHandlingData, handlingFlags))
				);
	}

	extern "C"
	{
		uintptr_t Address_CBoat__CBoat_56AF30_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CBoat__CBoat_56AF10()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R5, mod_HandlingManager)
			
			"MOV R1, R6\n"	// handling index
			ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, sizeof_tHandlingData)
			ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, cHandlingDataMgr__m_standardEntryArray_offset)
			"ADD R1, R5\n"
			"STR.W           R1, [R4,#0x388]\n"	// CVehicle.pVehicleHandling

			"LDR.W           R0, [R1,#%c[offset_handlingFlags]]\n"

			"MOV             R1, R6\n"	// handling ID

			"STR.W           R0, [R4,#0x390]\n"			

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CBoat__CBoat_56AF30_thumb)

			::[offset_handlingFlags]"i"(offsetof(tHandlingData, handlingFlags))		
			);
	}

	extern "C"
	{
		uintptr_t Address_CBoat__DebugCode_56BE36_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CBoat__DebugCode_56BE10()
	{
		__asm(
		".thumb\n"
			"MOV R2, R1\n"	// CVehicleModelInfo*
			LOAD_HANDLING_POINTER_FROM_VEHICLE_MODEL_INFO(R2)

			"ADDW R1, R4, #0x5E4\n"
			"VST1.32 {D16-D17}, [R1]\n"
			"ADDW R1, R4, #0x5D4\n"
			"VST1.32 {D16-D17}, [R1]\n"
			"ADDW R1, R4, #0x5C4\n"
			"VST1.32         {D16-D17}, [R1]\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CBoat__DebugCode_56BE36_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_CQuadBike__CQuadBike_57A1EA_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CQuadBike__CQuadBike_57A1D2()
	{
		__asm(
			".thumb\n"

			"VST1.32 {D16-D17}, [R3]\n"

			"MOVS R3, #2\n"
			"STR R3, [R4,#0x5A4]\n"
			
			"LDRH          R1, [R0,#0x62]\n"	// handling index
			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, mod_HandlingManager)
			ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(Address_cHandlingDataMgr__GetBikePointer)

			"LDR             R2, [R4]\n"	// restore this pointer

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CQuadBike__CQuadBike_57A1EA_thumb)
			);
	}

	extern "C"
	{
		uintptr_t Address_CTrain__CTrain_57C4FC_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CTrain__CTrain_57C4E4()
	{
		__asm(
			".thumb\n"
			"MOV R1, R9\n"
			LOAD_HANDLING_POINTER_FROM_VEHICLE_MODEL_INFO(R1)

			"STR R1, [R5,#0x388]\n"
			"LDR R0, [R1,#%c[offset_handlingFlags]]\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CTrain__CTrain_57C4FC_thumb)

				::[offset_handlingFlags]"i"(offsetof(tHandlingData, handlingFlags))
			);
	}
}

// Patches handling.cfg limit
void HandlingCfgLimits::PatchHandlingCfgLimit_GTA_SA_2_0_ANDROID_ARM32()
{
	// return;
	MAKE_VAR_GAME_VERSION();
	using namespace Game_GTASA;

	// Set variables
	Game_GTASA::mod_HandlingManager = mod_HandlingManager.ptr;

	cHandlingDataMgr__m_standardEntryArray_offset = cHandlingDataMgr::m_standardEntryArray.GetOffset();
	cHandlingDataMgr__m_standardEntryArray__transmissionData_offset = cHandlingDataMgr::m_standardEntryArray.GetOffset() + offsetof(tHandlingData, m_transmissionData);
	cHandlingDataMgr__m_standardEntryArray__transmissionData_end_offset =
		cHandlingDataMgr__m_standardEntryArray__transmissionData_offset + this->ms_iStandardLinesLimit * TypeDetails::SizeOf<tHandlingData_extended>();

	sizeof_cHandlingDataMgr = TypeDetails::SizeOf<cHandlingDataMgr>();
	sizeof_tHandlingData = TypeDetails::SizeOf<tHandlingData_extended>();

	Address_cHandlingDataMgr__GetBikePointer = (uintptr_t)GetMethodAsVoidPointer(&cHandlingDataMgr::GetBikePointer);
	
	// Patch pointer to mod_HandlingManager
	CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x6777C8), mod_HandlingManager.ptr);
	
	// Remove inlining of cHandlingDataMgr::Initialise
	{
		CPatch::EnterNewLevelAndDisableDebugState();	

		// bl _ZN16cHandlingDataMgr10InitialiseEv
		// bl #0xd4c
		CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x470014), "\x00\xf0\xa4\xfe", 4);

		CPatch::NOPinstructions(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x47001A), 0x470024 - 0x47001A);
		CPatch::NOPinstructions(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x470026), 0x47002E - 0x470026);
		CPatch::NOPinstructions(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x470030), 2);
		
		CPatch::LeaveThisLevel();
	}

	// cHandlingDataMgr::cHandlingDataMgr
	Address_cHandlingDataMgr__cHandlingDataMgr_570C9C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x570C9C));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x570C94),
		(void*)&patch_cHandlingDataMgr__cHandlingDataMgr_570C94
	);

	Address_cHandlingDataMgr__cHandlingDataMgr_570CAC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x570CAC));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x570CA2),
		(void*)&patch_cHandlingDataMgr__cHandlingDataMgr_570CA2
	);

	// global initializer for mod_HandlingManager
	Address_sub_1A8050_1A8074_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1A8074));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x1A8050),
		(void*)&patch_sub_1A8050_1A8050
	);

	// int __thiscall cHandlingDataMgr::GetHandlingId(cHandlingDataMgr *this, const char *vehicleName)
	if (!CPatch::IsDebugModeActive())
		CPatch::RedirectMethod(
			(uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN16cHandlingDataMgr13GetHandlingIdEPKc"),
			&cHandlingDataMgr::GetHandlingId
		);

	// int __cdecl CFileLoader::LoadVehicleObject(const char *line)
	if (!CPatch::IsDebugModeActive())
	{
		Address_cHandlingDataMgr__GetHandlingIdErrorIfNotFound = (uintptr_t)GetMethodAsVoidPointer(&cHandlingDataMgr::GetHandlingIdErrorIfNotFound);

		Address_CFileLoader__LoadVehicleObject_199178_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x199178));
		Address_CFileLoader__LoadVehicleObject_469C58_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x469C58));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x469C50),
			(void*)&patch_CFileLoader__LoadVehicleObject_469C50
		);
		
		// tFlyingHandlingData *__thiscall cHandlingDataMgr::GetFlyingPointer(cHandlingDataMgr *this, uint8_t handlingID)
		CPatch::RedirectMethod((uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN16cHandlingDataMgr16GetFlyingPointerEh"), &cHandlingDataMgr::GetFlyingPointer);

		// tBoatHandlingData *__thiscall cHandlingDataMgr::GetBoatPointer(cHandlingDataMgr *this, uint8_t handlingID)
		CPatch::RedirectMethod((uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN16cHandlingDataMgr14GetBoatPointerEh"), &cHandlingDataMgr::GetBoatPointer);

		// void __thiscall cHandlingDataMgr::LoadHandlingData(cHandlingDataMgr *this)

		// initialization
		Address_cHandlingDataMgr__InitVariables = (uintptr_t)GetMethodAsVoidPointer(&cHandlingDataMgr::InitVariables);

		Address_cHandlingDataMgr__LoadHandlingData_4731E4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x4731E4));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x4731D8),
			(void*)&patch_cHandlingDataMgr__LoadHandlingData_4731D8
		);		
		
		// disable call to cHandlingDataMgr::ConvertDataToGameUnits
		CPatch::NOPinstructions(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x4735C8), 0x4735D0 - 0x4735C8);
			
		// Make a call to cHandlingDataMgr::ConvertDataToGameUnitsOfAllStandardLines
		Address_cHandlingDataMgr__ConvertDataToGameUnitsOfAllStandardLines = (uintptr_t)GetMethodAsVoidPointer(&cHandlingDataMgr::ConvertDataToGameUnitsOfAllStandardLines);

		Address_cHandlingDataMgr__LoadHandlingData_473EF8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x473EF8));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x473EF0),
			(void*)&patch_cHandlingDataMgr__LoadHandlingData_473EF0
		);
				
		// cases
		Address_cHandlingDataMgr__LoadHandlingData_4735B6_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x4735B6));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x473318),
			(void*)&patch_cHandlingDataMgr__LoadHandlingData_standard_473318
		);		
		
		Address_cHandlingDataMgr__LoadHandlingData_473752_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x473752));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x473616),
			(void*)&patch_cHandlingDataMgr__LoadHandlingData_boat_473616
		);

		Address_cHandlingDataMgr__LoadHandlingData_473C2E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x473C2E));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x473ADC),
			(void*)&patch_cHandlingDataMgr__LoadHandlingData_bike_473ADC
		);

		Address_cHandlingDataMgr__LoadHandlingData_473A8A_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x473A8A));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x47389A),
			(void*)&patch_cHandlingDataMgr__LoadHandlingData_flying_47389A
		);
		
		// void __thiscall cHandlingDataMgr::ConvertDataToWorldUnits(cHandlingDataMgr *this, tHandlingData *handling)		
		Address_cHandlingDataMgr__ConvertDataToGameUnits_570D60_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x570D60));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x570D58),
			(void*)&patch_cHandlingDataMgr__ConvertDataToGameUnits_570D58
		);

		Address_cHandlingDataMgr__ConvertDataToGameUnits_570EE0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x570EE0));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x570ED8),
			(void*)&patch_cHandlingDataMgr__ConvertDataToGameUnits_570ED8
		);
		
		Address_cHandlingDataMgr__ConvertDataToGameUnits_570E6E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x570E6E));
		Address_cHandlingDataMgr__ConvertDataToGameUnits_570E68_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x570E68));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x570E5E),
			(void*)&patch_cHandlingDataMgr__ConvertDataToGameUnits_570E5E
		);		
				
		Address_cHandlingDataMgr__ConvertDataToGameUnits_570EB0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x570EB0));
		Address_cHandlingDataMgr__ConvertDataToGameUnits_570E8C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x570E8C));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x570E7A),
			(void*)&patch_cHandlingDataMgr__ConvertDataToGameUnits_570E7A
		);
	}

	// CGarage::Update
	Address_CGarage__RightModTypeForThisGarage = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game, "_ZN7CGarage25RightModTypeForThisGarageEP8CVehicle"
	);

	Address_CGarage__Update_30EFB2_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x30EFB2));
	Address_CGarage__Update_3102F2_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3102F2));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x30EBD0),
		(void*)&patch_CGarage__Update_30EBD0
	);

	Address_CGarage__Update_31034A_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31034A));
	Address_CGarage__Update_310334_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x310334));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x30F302),
		(void*)&patch_CGarage__Update_30F302
	);

	Address_CGarage__RightModTypeForThisGarage_312F48_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x312F48));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x312F40),
		(void*)&patch_CGarage__RightModTypeForThisGarage_312F40
	);

	{
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x312F54), "\x07\xe0", 2);	// B #0x12
		CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x312F72), "\x07\xe0", 2);	// B #0x12
		CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x312F92), "\x07\xe0", 2);	// B #0x12
		CPatch::LeaveThisLevel();
	}

	///// CRunningScript::ProcessCommands2400To2499
	// command 0x096E (IS_CAR_LOW_RIDER)
	Address_CRunningScript__ProcessCommands2400To2499_33CAC4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x33CAC4));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x33CAB0),
		(void*)&patch_CRunningScript__ProcessCommands2400To2499_33CAB0
	);

	// command 0x096F (IS_CAR_STREET_RACER)
	Address_CRunningScript__ProcessCommands2400To2499_33CB1C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x33CB1C));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x33CB08),
		(void*)&patch_CRunningScript__ProcessCommands2400To2499_33CB08
	);

	///// CRunningScript::ProcessCommands2500To2599
	// command 0x09E1 (GET_CAR_MODEL_VALUE)
	Address_CRunningScript__ProcessCommands2500To2599_33F090_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x33F090));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x33EE04),
		(void*)&patch_CRunningScript__ProcessCommands2500To2599_33EE04
	);

	// CVehicleModelInfo::PreprocessHierarchy
	Address_CVehicleModelInfo__PreprocessHierarchy_38745A_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x38745A));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x387450),
		(void*)&patch_CVehicleModelInfo__PreprocessHierarchy_387450
	);
	
	// CVehicleModelInfo::SetVehicleComponentFlags
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x38838C), "\xb0\xf8\x62\x60", 4);	// LDRH.W          R6, [R0,#0x62]
	CPatch::LeaveThisLevel();		

	Address_CVehicleModelInfo__SetVehicleComponentFlags_3883C0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3883C0));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3883AE),
		(void*)&patch_CVehicleModelInfo__SetVehicleComponentFlags_3883AE
	);
	
	Address_CVehicleModelInfo__SetVehicleComponentFlags_38844A_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x38844A));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x388438),
		(void*)&patch_CVehicleModelInfo__SetVehicleComponentFlags_388438
	);
	
	// CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors
	Address_CVehicleModelInfo__GetMaximumNumberOfPassengersFromNumberOfDoors_388F92_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x388F92));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x388F80),
		(void*)&patch_CVehicleModelInfo__GetMaximumNumberOfPassengersFromNumberOfDoors_388F80
	);

	Address_CVehicleModelInfo__GetMaximumNumberOfPassengersFromNumberOfDoors_38901E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x38901E));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x38900C),
		(void*)&patch_CVehicleModelInfo__GetMaximumNumberOfPassengersFromNumberOfDoors_38900C
	);
	
	// CCam::LookRight
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x3D1C0E), "\xb0\xf8\x62\x10", 4);	// LDRH.W          R1, [R0,#0x62]
	CPatch::LeaveThisLevel();

	// CCam::GetBoatLook_L_R_HeightOffset
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x3D21CE), "\xb0\xf8\x62\x10", 4);	// LDRH.W          R1, [R0,#0x62]
	CPatch::LeaveThisLevel();

	// CPad::GetHandBrake
	Address_CPad__GetHandBrake_3FA8F2_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3FA8F2));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3FA8DE),
		(void*)&patch_CPad__GetHandBrake_3FA8DE
	);

	// CAutomobile::CAutomobile
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x54E2E4), "\xbb\xf8\x62\x50", 4);	// LDRH.W          R5, [R11,#0x62]
	CPatch::LeaveThisLevel();
	
	Address_CAutomobile__CAutomobile_54E330_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x54E330));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x54E314),
		(void*)&patch_CAutomobile__CAutomobile_54E314
	);	
	
	// CAutomobile::ProcessControl
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x5546B2), "\xb0\xf8\x62\x10", 4);	// LDRH.W          R1, [R0,#0x62]
	CPatch::LeaveThisLevel();

	// CAutomobile::ProcessCarWheelPair
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x556AEA), "\x11\x88", 2);	// LDRB            R1, [R2]
	CPatch::LeaveThisLevel();
	
	Address_CAutomobile__ProcessCarWheelPair_556B06_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x556B06));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x556AF6),
		(void*)&patch_CAutomobile__ProcessCarWheelPair_556AF6
	);

	Address_CAutomobile__ProcessCarWheelPair_556B74_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x556B74));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x556B64),
		(void*)&patch_CAutomobile__ProcessCarWheelPair_556B64
	);

	// CAutomobile::DebugCode
	Address_CAutomobile__DebugCode_55CAEC = g_mCalc.GetCurrentVAbyPreferedVA(0x55CAEC);
	Address_CAutomobile__DebugCode_55CB0E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x55CB0E));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x55CAE2),
		(void*)&patch_CAutomobile__DebugCode_55CAE2
	);

	
	// CBike::CBike
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x560426), "\xb9\xf8\x62\x60", 4);	// LDRH.W          R6, [R9,#0x62]
	CPatch::LeaveThisLevel();

	if (!CPatch::IsDebugModeActive())
	{
		Address_CBike__CBike_56049E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x56049E));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x560472),
			(void*)&patch_CBike__CBike_560472
		);
	}
	
	// CBoat::CBoat
	CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x56AEBA), "\xb8\xf8\x62\x60", 4);
	
	
	Address_CBoat__CBoat_56AF30_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x56AF30));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x56AF10),
		(void*)&patch_CBoat__CBoat_56AF10
	);
	
	

	// CBoat::DebugCode
	Address_CBoat__DebugCode_56BE36_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x56BE36));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x56BE10),
		(void*)&patch_CBoat__DebugCode_56BE10
	);
	
	// CPlane::ProcessFlyingCarStuff
	CPatch::EnterNewLevelAndDisableDebugState();
	CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x577344), "\xb0\xf8\x62\x10", 4);
	CPatch::LeaveThisLevel();

	// CQuadBike::CQuadBike		
	Address_CQuadBike__CQuadBike_57A1EA_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x57A1EA));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x57A1D2),
		(void*)&patch_CQuadBike__CQuadBike_57A1D2
	);	

	// CTrain::CTrain
	Address_CTrain__CTrain_57C4FC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x57C4FC));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x57C4E4),
		(void*)&patch_CTrain__CTrain_57C4E4
	);	

	// Patch references to CVehicleAnimGroupData::m_vehicleAnimGroups
	#if TRUE
	{
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x67684C), CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa);
	}
	#endif
}
#endif

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTAIV
{
	// bike limit
	void* Address_GTAIV_1_0_4_0_BC2CBD = NULL;

	NAKED void patch__GTA_IV_1_0_4_0_BC2CB8()
	{
		__asm
		{
			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, ms_iBikeLinesLimit);
			cmp[esp + 3Ch - 0x28], eax;

			jmp Address_GTAIV_1_0_4_0_BC2CBD;
		}
	}

	// flying limit
	void* Address_GTAIV_1_0_4_0_BC2CE4 = NULL;

	NAKED void patch_GTA_IV_1_0_4_0_BC2CDF()
	{
		__asm
		{
			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, ms_iFlyingLinesLimit);
			cmp[esp + 3Ch - 0x20], eax;

			jmp Address_GTAIV_1_0_4_0_BC2CE4;
		}		
	}

	// boat limit
	void* Address_GTAIV_1_0_4_0_BC2D05;

	NAKED void patch_GTA_IV_1_0_4_0_BC2D00()
	{
		__asm
		{
			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_handlingCfgLimits, HandlingCfgLimits, ms_iBoatLinesLimit);
			cmp[esp + 3Ch - 0x24], eax;

			jmp Address_GTAIV_1_0_4_0_BC2D05;
		}
	}
}

// Patches handling.cfg limit
void HandlingCfgLimits::PatchHandlingCfgLimit_GTA_IV_1_0_4_0()
{
	using namespace Game_GTAIV;

	// standard lines
	if(this->ms_bStandardLinesLimitSet)
	{
		// allocate
		if (this->ms_iStandardLinesLimit > 160)
		{
			this->g_handling.gta_iv = new tHandlingData[this->ms_iStandardLinesLimit];
			this->g_handling.bIsAllocated.Set(true);
		}

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xCDDC56 + 1), ms_iStandardLinesLimit - 1);	// mov     esi, 159
		}
		#endif

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC23D0 + 1), &g_handling.gta_iv->m_pFlyingHandling);	// mov     eax, offset g_handling.m_pFlyingHandling	; __initHandling
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC23F1 + 1), &g_handling.gta_iv[ms_iStandardLinesLimit].m_pFlyingHandling);	// cmp     eax, (offset g_handlingBike.m_fStoppieStabMult+0C0h)	; __initHandling
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC2411 + 1), g_handling.gta_iv);	// mov     edi, offset g_handling	; ?getHandlingIndexById@CHandling@@QAAHPAD@Z
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC2468 + 1), g_handling.gta_iv);	// add     eax, offset g_handling	; ?getHandlingById@CHandling@@QAAPAVCHandling@@PAD@Z
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC248A + 1), g_handling.gta_iv);	// add     eax, offset g_handling	; ?getHandlingByIndex@CHandling@@QAAPAVCHandling@@H@Z
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC2BFD + 1), g_handling.gta_iv);	// add     eax, offset g_handling	; ?getHandlingIndexByIdAlways@CHandling@@QAAHPAD@Z
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC2D47 + 2), g_handling.gta_iv);	// lea     esi, g_handling.m_pszId[eax]	; cHandlingDataMgr::LoadHandlingData
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCDDC51 + 1), g_handling.gta_iv);	// mov     edx, offset g_handling	; init_handling
		}
		#endif
	}

	// bike lines
	if(this->ms_bBikeLinesLimitSet)
	{
		// Allocate
		if (this->ms_iBikeLinesLimit > 40)
		{
			this->g_handlingBike.gta_iv = new Game_GTAIV::tBikeHandlingData[this->ms_iBikeLinesLimit];
			this->g_handlingBike.bIsAllocated.Set(true);
		}

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xCDDC85 + 1), ms_iBikeLinesLimit - 1);	// mov     edx, 39 
		}
		#endif

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC23D5 + 1), g_handlingBike.gta_iv);	// mov     edx, offset g_handlingBike	; __initHandling
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC2C7C + 1), g_handlingBike.gta_iv);	// mov     ebp, offset g_handlingBike	; cHandlingDataMgr::LoadHandlingData
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCDDC80 + 1), g_handlingBike.gta_iv);	// mov     ecx, offset g_handlingBike	; init_handlingBike
		}
		#endif

		// Limit value
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xBC2CB8), &patch__GTA_IV_1_0_4_0_BC2CB8);
		Address_GTAIV_1_0_4_0_BC2CBD = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0xBC2CBD);
	}
	
	// flying lines
	if(this->ms_bFlyingLinesLimitSet)
	{
		// Allocate
		if (this->ms_iFlyingLinesLimit > 40)
		{
			this->g_handlingFlying.gta_iv = new Game_GTAIV::tFlyingHandlingData[this->ms_iFlyingLinesLimit];
			this->g_handlingFlying.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC23E3 + 2), g_handlingFlying.gta_iv);	// mov     dword ptr [eax], offset g_handlingFlying	; __initHandling
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC2C6F + 1), g_handlingFlying.gta_iv);	// mov     edx, offset g_handlingFlying	; cHandlingDataMgr::LoadHandlingData
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCDDCA0 + 1), g_handlingFlying.gta_iv);	// mov     ecx, offset g_handlingFlying	; init_handlingFlying
		}
		#endif

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xCDDCA5 + 1), ms_iFlyingLinesLimit - 1);	// mov     edx, 39
		}
		#endif

		// Limit value
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xBC2CDF), &patch_GTA_IV_1_0_4_0_BC2CDF);
		Address_GTAIV_1_0_4_0_BC2CE4 = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0xBC2CE4);
	}

	// boat lines
	if(this->ms_bBoatLinesLimitSet)
	{
		// Allocate
		if (this->ms_iBoatLinesLimit > 40)
		{
			this->g_handlingBoat.gta_iv = new Game_GTAIV::tBoatHandlingData[this->ms_iBoatLinesLimit];
			this->g_handlingBoat.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC23DA + 1), g_handlingBoat.gta_iv);	// mov     ecx, offset g_handlingBoat	; __initHandling
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC2C6A + 1), g_handlingBoat.gta_iv);	// mov     eax, offset g_handlingBoat	; cHandlingDataMgr::LoadHandlingData
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCDDCC0 + 1), g_handlingBoat.gta_iv);	// mov     ecx, offset g_handlingBoat	; init_handlingBoat
		}
		#endif

		// Patch values
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xCDDCC5 + 1), ms_iBoatLinesLimit - 1);	// mov     edx, 39

		// Limit value
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xBC2D00), &patch_GTA_IV_1_0_4_0_BC2D00);
		Address_GTAIV_1_0_4_0_BC2D05 = (void*)g_mCalc.GetCurrentVAbyPreferedVA(0xBC2D05);
	}
}

// Patches handling.cfg limit
void HandlingCfgLimits::PatchHandlingCfgLimit_GTA_IV_1_0_7_0()
{
	using namespace Game_GTAIV;

	// standard lines
	if(this->ms_bStandardLinesLimitSet)
	{
		// allocate
		if (this->ms_iStandardLinesLimit > 160)
		{
			this->g_handling.gta_iv = new tHandlingData[this->ms_iStandardLinesLimit];
			this->g_handling.bIsAllocated.Set(true);
		}

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD40EA6 + 1), ms_iStandardLinesLimit - 1);	// mov     esi, 159
		}
		#endif

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9718C0 + 1), &g_handling.gta_iv->m_pFlyingHandling);	// mov     eax, offset g_handling.m_pFlyingHandling	; sub_9718C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9718E1 + 1), &g_handling.gta_iv[ms_iStandardLinesLimit].m_pFlyingHandling);	// cmp     eax, (offset g_handlingBike.m_fStoppieStabMult+0C0h)	; sub_9718C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971906 + 1), &g_handling.gta_iv->m_pFlyingHandling);	// mov     eax, offset g_handling.m_pFlyingHandling	; sub_9718F0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971931 + 1), &g_handling.gta_iv[ms_iStandardLinesLimit].m_pFlyingHandling);	// cmp     eax, (offset g_handlingBike.m_fStoppieStabMult+0C0h)	; sub_9718F0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971951 + 1), g_handling.gta_iv);	// mov     edi, offset g_handling	; sub_971940
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9719A8 + 1), g_handling.gta_iv);	// add     eax, offset g_handling	; sub_971990
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9719CA + 1), g_handling.gta_iv);	// add     eax, offset g_handling	; sub_9719C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971C1D + 1), g_handling.gta_iv);	// add     eax, offset g_handling	; ?getHandlingIndexByIdAlways@CHandling@@QAAHPAD@Z
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971C5A + 2), &g_handling.gta_iv->m_pBikeHandling);	// cmp     g_handling.m_pBikeHandling[ecx], offset g_handlingBike	; sub_971C40
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971C64 + 2), &g_handling.gta_iv->m_pBikeHandling);	// lea     ecx, g_handling.m_pBikeHandling[ecx]	; sub_971C40
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971CBA + 2), &g_handling.gta_iv->m_pFlyingHandling);	// cmp     g_handling.m_pFlyingHandling[ecx], offset g_handlingFlying	; sub_971CA0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971CC4 + 2), &g_handling.gta_iv->m_pFlyingHandling);	// lea     edx, g_handling.m_pFlyingHandling[ecx]	; sub_971CA0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971D1A + 2), &g_handling.gta_iv->m_pBoatHandling);	// cmp     g_handling.m_pBoatHandling[ecx], offset g_handlingBoat	; sub_971D00
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971D24 + 2), &g_handling.gta_iv->m_pBoatHandling);	// lea     ecx, g_handling.m_pBoatHandling[ecx]	; sub_971D00
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971DFD + 2), &g_handling.gta_iv->m_pBikeHandling);	// mov     ecx, g_handling.m_pBikeHandling[eax]	; _ZN16cHandlingDataMgr16LoadHandlingDataEv
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971E03 + 2), &g_handling.gta_iv->m_pBikeHandling);	// lea     esi, g_handling.m_pBikeHandling[eax]	; _ZN16cHandlingDataMgr16LoadHandlingDataEv
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971E50 + 2), &g_handling.gta_iv->m_pFlyingHandling);	// mov     ecx, g_handling.m_pFlyingHandling[eax]	; _ZN16cHandlingDataMgr16LoadHandlingDataEv
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971E8F + 2), &g_handling.gta_iv->m_pBoatHandling);	// mov     ecx, g_handling.m_pBoatHandling[eax]	; _ZN16cHandlingDataMgr16LoadHandlingDataEv
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971EC4 + 2), &g_handling.gta_iv->m_pszId);	// lea     esi, g_handling.m_pszId[eax]	; _ZN16cHandlingDataMgr16LoadHandlingDataEv
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD40EA1 + 1), g_handling.gta_iv);	// mov     edx, offset g_handling	; sub_D40EA0
		}
		#endif
	}

	// bike lines
	if(this->ms_bBikeLinesLimitSet)
	{
		// Allocate
		if (this->ms_iBikeLinesLimit > 40)
		{
			this->g_handlingBike.gta_iv = new Game_GTAIV::tBikeHandlingData[this->ms_iBikeLinesLimit];
			this->g_handlingBike.bIsAllocated.Set(true);
		}

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD40ED5 + 1), ms_iBikeLinesLimit - 1);	// mov     edx, 39 
		}
		#endif

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9718C5 + 1), g_handlingBike.gta_iv);	// mov     edx, offset g_handlingBike	; sub_9718C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x97190B + 1), g_handlingBike.gta_iv);	// mov     edx, offset g_handlingBike	; sub_9718F0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971C5A + 6), g_handlingBike.gta_iv);	// cmp     g_handling.m_pBikeHandling[ecx], offset g_handlingBike	; sub_971C40
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971C7D + 2), g_handlingBike.gta_iv);	// add     esi, offset g_handlingBike	; sub_971C40
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD40ED0 + 1), g_handlingBike.gta_iv);	// mov     ecx, offset g_handlingBike	; sub_D40ED0
		}
		#endif

		// Define values for automatic patch
		CCodeMover::SetVariable("NUMBER_OF_HANDLING_BIKE_LINES", this->ms_iBikeLinesLimit);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddress(
					g_mCalc.GetCurrentVAbyPreferedVA(0x971C72),
					5,
					"\x01\x02\x81\xfa\x05\x04NUMBER_OF_HANDLING_BIKE_LINES\x00\x01\x02\x0F\x8D\x03\x90\x1c\x97\x00\x00",
					g_mCalc.GetCurrentVAbyPreferedVA(0x971C77)
				);	// line 1, 0x971C40 - sub_971C40 : cmp     edx, 28h ; '('
		}
		#endif

		CCodeMover::DeleteVariable("NUMBER_OF_HANDLING_BIKE_LINES");
	}
	
	// flying lines
	if(this->ms_bFlyingLinesLimitSet)
	{
		// Allocate
		if (this->ms_iFlyingLinesLimit > 40)
		{
			this->g_handlingFlying.gta_iv = new Game_GTAIV::tFlyingHandlingData[this->ms_iFlyingLinesLimit];
			this->g_handlingFlying.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9718D3 + 2), g_handlingFlying.gta_iv);	// mov     dword ptr [eax], offset g_handlingFlying	; sub_9718C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971923 + 2), g_handlingFlying.gta_iv);	// mov     dword ptr [eax], offset g_handlingFlying	; sub_9718F0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971CBA + 6), g_handlingFlying.gta_iv);	// cmp     g_handling.m_pFlyingHandling[ecx], offset g_handlingFlying	; sub_971CA0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971CDE + 2), g_handlingFlying.gta_iv);	// add     esi, offset g_handlingFlying	; sub_971CA0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD40EF0 + 1), g_handlingFlying.gta_iv);	// mov     ecx, offset g_handlingFlying	; sub_D40EF0
		}
		#endif

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD40EF5 + 1), ms_iFlyingLinesLimit - 1);	// mov     edx, 39
		}
		#endif

		// Define values for automatic patch
		CCodeMover::SetVariable("NUMBER_OF_HANDLING_FLYING_LINES", this->ms_iFlyingLinesLimit);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddress(
				g_mCalc.GetCurrentVAbyPreferedVA(0x971CD2),
				5,
				"\x01\x02\x81\xf9\x05\x04NUMBER_OF_HANDLING_FLYING_LINES\x00\x01\x02\x0F\x8D\x03\xf1\x1c\x97\x00\x00",
				g_mCalc.GetCurrentVAbyPreferedVA(0x971CD7)
				);	// line 1, 0x971CA0 - sub_971CA0 : cmp     ecx, 40
		}
		#endif

		CCodeMover::DeleteVariable("NUMBER_OF_HANDLING_FLYING_LINES");
	}

	// boat lines
	if(this->ms_bBoatLinesLimitSet)
	{
		// Allocate
		if (this->ms_iBoatLinesLimit > 40)
		{
			this->g_handlingBoat.gta_iv = new Game_GTAIV::tBoatHandlingData[this->ms_iBoatLinesLimit];
			this->g_handlingBoat.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9718CA + 1), g_handlingBoat.gta_iv);	// mov     ecx, offset g_handlingBoat	; sub_9718C0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971910 + 1), g_handlingBoat.gta_iv);	// mov     ecx, offset g_handlingBoat	; sub_9718F0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971D1A + 6), g_handlingBoat.gta_iv);	// cmp     g_handling.m_pBoatHandling[ecx], offset g_handlingBoat	; sub_971D00
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x971D40 + 2), g_handlingBoat.gta_iv);	// add     esi, offset g_handlingBoat	; sub_971D00
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD40F10 + 1), g_handlingBoat.gta_iv);	// mov     ecx, offset g_handlingBoat	; sub_D40F10
		}
		#endif

		// Patch values
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD40F15 + 1), ms_iBoatLinesLimit - 1);	// mov     edx, 39

		// Define variables for automatic patch
		CCodeMover::SetVariable("NUMBER_OF_HANDLING_BOAT_LINES", this->ms_iBoatLinesLimit);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddress(
				g_mCalc.GetCurrentVAbyPreferedVA(0x971D32),
				5,
				"\x01\x02\x81\xfa\x05\x04NUMBER_OF_HANDLING_BOAT_LINES\x00\x01\x02\x0F\x8D\x03\x53\x1d\x97\x00\x00",
				g_mCalc.GetCurrentVAbyPreferedVA(0x971D37)
				);	// line 1, 0x971D00 - sub_971D00 : cmp     edx, 28h ; '('
		}
		#endif

		// Delete variable
		CCodeMover::DeleteVariable("NUMBER_OF_HANDLING_BOAT_LINES");
	}
}

// Patches handling.cfg limit
void HandlingCfgLimits::PatchHandlingCfgLimit_GTA_IV_1_0_8_0()
{
	using namespace Game_GTAIV;	

	// standard lines
	if(this->ms_bStandardLinesLimitSet)
	{
		// allocate
		if (this->ms_iStandardLinesLimit > 160)
		{
			this->g_handling.gta_iv = new tHandlingData[this->ms_iStandardLinesLimit];
			this->g_handling.bIsAllocated.Set(true);
		}

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD63486 + 1), ms_iStandardLinesLimit - 1);	// mov     esi, 159
		}
		#endif

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2510 + 1), &g_handling.gta_iv->m_pFlyingHandling);	// mov     eax, offset g_handling.m_pFlyingHandling	; sub_BA2510
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2531 + 1), &g_handling.gta_iv[ms_iStandardLinesLimit].m_pFlyingHandling);	// cmp     eax, (offset g_handlingBike.m_fStoppieStabMult+0C0h)	; sub_BA2510
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2556 + 1), &g_handling.gta_iv->m_pFlyingHandling);	// mov     eax, offset g_handling.m_pFlyingHandling	; sub_BA2540
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2581 + 1), &g_handling.gta_iv[ms_iStandardLinesLimit].m_pFlyingHandling);	// cmp     eax, (offset g_handlingBike.m_fStoppieStabMult+0C0h)	; sub_BA2540
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA25A1 + 1), g_handling.gta_iv);	// mov     edi, offset g_handling	; sub_BA2590
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA25F8 + 1), g_handling.gta_iv);	// add     eax, offset g_handling	; sub_BA25E0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA261A + 1), g_handling.gta_iv);	// add     eax, offset g_handling	; sub_BA2610
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA286D + 1), g_handling.gta_iv);	// add     eax, offset g_handling	; sub_BA2840
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA28AA + 2), &g_handling.gta_iv->m_pBikeHandling);	// cmp     g_handling.m_pBikeHandling[ecx], offset g_handlingBike	; sub_BA2890
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA28B4 + 2), &g_handling.gta_iv->m_pBikeHandling);	// lea     ecx, g_handling.m_pBikeHandling[ecx]	; sub_BA2890
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA290A + 2), &g_handling.gta_iv->m_pFlyingHandling);	// cmp     g_handling.m_pFlyingHandling[ecx], offset g_handlingFlying	; sub_BA28F0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2914 + 2), &g_handling.gta_iv->m_pFlyingHandling);	// lea     edx, g_handling.m_pFlyingHandling[ecx]	; sub_BA28F0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA296A + 2), &g_handling.gta_iv->m_pBoatHandling);	// cmp     g_handling.m_pBoatHandling[ecx], offset g_handlingBoat	; sub_BA2950
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2974 + 2), &g_handling.gta_iv->m_pBoatHandling);	// lea     ecx, g_handling.m_pBoatHandling[ecx]	; sub_BA2950
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2A4D + 2), &g_handling.gta_iv->m_pBikeHandling);	// mov     ecx, g_handling.m_pBikeHandling[eax]	; sub_BA29B0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2A53 + 2), &g_handling.gta_iv->m_pBikeHandling);	// lea     esi, g_handling.m_pBikeHandling[eax]	; sub_BA29B0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2AA0 + 2), &g_handling.gta_iv->m_pFlyingHandling);	// mov     ecx, g_handling.m_pFlyingHandling[eax]	; sub_BA29B0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2ADF + 2), &g_handling.gta_iv->m_pBoatHandling);	// mov     ecx, g_handling.m_pBoatHandling[eax]	; sub_BA29B0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2B14 + 2), &g_handling.gta_iv->m_pszId);	// lea     esi, g_handling.m_pszId[eax]	; sub_BA29B0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD63481 + 1), g_handling.gta_iv);	// mov     edx, offset g_handling	; sub_D63480
		}
		#endif
	}

	// bike lines
	if(this->ms_bBikeLinesLimitSet)
	{
		// Allocate
		if (this->ms_iBikeLinesLimit > 40)
		{
			this->g_handlingBike.gta_iv = new Game_GTAIV::tBikeHandlingData[this->ms_iBikeLinesLimit];
			this->g_handlingBike.bIsAllocated.Set(true);
		}

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD634B5 + 1), ms_iBikeLinesLimit - 1);	// mov     edx, 39 
		}
		#endif

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2515 + 1), g_handlingBike.gta_iv);	// mov     edx, offset g_handlingBike	; sub_BA2510
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA255B + 1), g_handlingBike.gta_iv);	// mov     edx, offset g_handlingBike	; sub_BA2540
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA28AA + 6), g_handlingBike.gta_iv);	// cmp     g_handling.m_pBikeHandling[ecx], offset g_handlingBike	; sub_BA2890
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA28CD + 2), g_handlingBike.gta_iv);	// add     esi, offset g_handlingBike	; sub_BA2890
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD634B0 + 1), g_handlingBike.gta_iv);	// mov     ecx, offset g_handlingBike	; sub_D634B0
		}
		#endif

		// Define values for automatic patch
		CCodeMover::SetVariable("NUMBER_OF_HANDLING_BIKE_LINES", this->ms_iBikeLinesLimit);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddressRel(0xBA28C2,
				5,
				"\x01\x02\x81\xfa\x05\x04""NUMBER_OF_HANDLING_BIKE_LINES\x00\x01\x02\x0F\x8D\x15\xe0\x28\x7a\x00\x00",
				0xBA28C7);	// line 1, 0xBA2890 - sub_BA2890 : cmp     edx, 28h
		}
		#endif

		CCodeMover::DeleteVariable("NUMBER_OF_HANDLING_BIKE_LINES");
	}	

	// flying lines
	if(this->ms_bFlyingLinesLimitSet)
	{
		// Allocate
		if (this->ms_iFlyingLinesLimit > 40)
		{
			this->g_handlingFlying.gta_iv = new Game_GTAIV::tFlyingHandlingData[this->ms_iFlyingLinesLimit];
			this->g_handlingFlying.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2523 + 2), g_handlingFlying.gta_iv);	// mov     dword ptr [eax], offset g_handlingFlying	; sub_BA2510
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2573 + 2), g_handlingFlying.gta_iv);	// mov     dword ptr [eax], offset g_handlingFlying	; sub_BA2540
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA290A + 6), g_handlingFlying.gta_iv);	// cmp     g_handling.m_pFlyingHandling[ecx], offset g_handlingFlying	; sub_BA28F0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA292E + 2), g_handlingFlying.gta_iv);	// add     esi, offset g_handlingFlying	; sub_BA28F0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD634D0 + 1), g_handlingFlying.gta_iv);	// mov     ecx, offset g_handlingFlying	; sub_D634D0
		}
		#endif

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD634D5 + 1), ms_iFlyingLinesLimit - 1);	// mov     edx, 39
		}
		#endif

		// Define values for automatic patch
		CCodeMover::SetVariable("NUMBER_OF_HANDLING_FLYING_LINES", this->ms_iFlyingLinesLimit);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddressRel(
				0xBA2922,
				5,
				"\x01\x02\x81\xf9\x05\x04""NUMBER_OF_HANDLING_FLYING_LINES\x00\x01\x02\x0F\x8D\x15\x41\x29\x7a\x00\x00",
				0xBA2927);	// line 1, 0xBA28F0 - sub_BA28F0 : cmp     ecx, 40
		}
		#endif

		CCodeMover::DeleteVariable("NUMBER_OF_HANDLING_FLYING_LINES");
	}


	// boat lines
	if(this->ms_bBoatLinesLimitSet)
	{
		// Allocate
		if (this->ms_iBoatLinesLimit > 40)
		{
			this->g_handlingBoat.gta_iv = new Game_GTAIV::tBoatHandlingData[this->ms_iBoatLinesLimit];
			this->g_handlingBoat.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA251A + 1), g_handlingBoat.gta_iv);	// mov     ecx, offset g_handlingBoat	; sub_BA2510
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2560 + 1), g_handlingBoat.gta_iv);	// mov     ecx, offset g_handlingBoat	; sub_BA2540
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA296A + 6), g_handlingBoat.gta_iv);	// cmp     g_handling.m_pBoatHandling[ecx], offset g_handlingBoat	; sub_BA2950
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBA2990 + 2), g_handlingBoat.gta_iv);	// add     esi, offset g_handlingBoat	; sub_BA2950
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD634F0 + 1), g_handlingBoat.gta_iv);	// mov     ecx, offset g_handlingBoat	; sub_D634F0
		}
		#endif

		// Patch values
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD634F5 + 1), ms_iBoatLinesLimit - 1);	// mov     edx, 39

		// Define variables for automatic patch
		CCodeMover::SetVariable("NUMBER_OF_HANDLING_BOAT_LINES", this->ms_iBoatLinesLimit);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddressRel(
				0xBA2982,
				5,
				"\x01\x02\x81\xfa\x05\x04""NUMBER_OF_HANDLING_BOAT_LINES\x00\x01\x02\x0F\x8D\x15\xa3\x29\x7a\x00\x00",
				0xBA2987
			);	// line 1, 0xBA2950 - sub_BA2950 : cmp     edx, 28h
		}
		#endif

		// Delete variable
		CCodeMover::DeleteVariable("NUMBER_OF_HANDLING_BOAT_LINES");
	}
}

// Patches handling.cfg limit
void HandlingCfgLimits::PatchHandlingCfgLimit_GTA_EFLC_1_1_2_0()
{
	using namespace Game_GTAIV;	

	// standard lines
	if(this->ms_bStandardLinesLimitSet)
	{
		// allocate
		if (this->ms_iStandardLinesLimit > 160)
		{
			this->g_handling.gta_iv = new tHandlingData[this->ms_iStandardLinesLimit];
			this->g_handling.bIsAllocated.Set(true);
		}

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD39856 + 1), ms_iStandardLinesLimit - 1);	// mov     esi, 159
		}
		#endif

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBA20 + 1), &g_handling.gta_iv->m_pFlyingHandling);	// mov     eax, offset g_handling.m_pFlyingHandling	; sub_8DBA20
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBA41 + 1), &g_handling.gta_iv[ms_iStandardLinesLimit].m_pFlyingHandling);	// cmp     eax, (offset g_handlingBike.m_fStoppieStabMult+0C0h)	; sub_8DBA20
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBA66 + 1), &g_handling.gta_iv->m_pFlyingHandling);	// mov     eax, offset g_handling.m_pFlyingHandling	; sub_8DBA50
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBA91 + 1), &g_handling.gta_iv[ms_iStandardLinesLimit].m_pFlyingHandling);	// cmp     eax, (offset g_handlingBike.m_fStoppieStabMult+0C0h)	; sub_8DBA50
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBAB1 + 1), g_handling.gta_iv);	// mov     edi, offset g_handling	; sub_8DBAA0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBB08 + 1), g_handling.gta_iv);	// add     eax, offset g_handling	; sub_8DBAF0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBB2A + 1), g_handling.gta_iv);	// add     eax, offset g_handling	; sub_8DBB20
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBD7D + 1), g_handling.gta_iv);	// add     eax, offset g_handling	; sub_8DBD50
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBDBA + 2), &g_handling.gta_iv->m_pBikeHandling);	// cmp     g_handling.m_pBikeHandling[ecx], offset g_handlingBike	; sub_8DBDA0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBDC4 + 2), &g_handling.gta_iv->m_pBikeHandling);	// lea     ecx), g_handling.m_pBikeHandling[ecx]	; sub_8DBDA0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBE1A + 2), &g_handling.gta_iv->m_pFlyingHandling);	// cmp     g_handling.m_pFlyingHandling[ecx], offset g_handlingFlying	; sub_8DBE00
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBE24 + 2), &g_handling.gta_iv->m_pFlyingHandling);	// lea     edx), g_handling.m_pFlyingHandling[ecx]	; sub_8DBE00
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBE7A + 2), &g_handling.gta_iv->m_pBoatHandling);	// cmp     g_handling.m_pBoatHandling[ecx], offset g_handlingBoat	; sub_8DBE60
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBE84 + 2), &g_handling.gta_iv->m_pBoatHandling);	// lea     ecx), g_handling.m_pBoatHandling[ecx]	; sub_8DBE60
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBF5D + 2), &g_handling.gta_iv->m_pBikeHandling);	// mov     ecx), g_handling.m_pBikeHandling[eax]	; sub_8DBEC0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBF63 + 2), &g_handling.gta_iv->m_pBikeHandling);	// lea     esi), g_handling.m_pBikeHandling[eax]	; sub_8DBEC0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBFB0 + 2), &g_handling.gta_iv->m_pFlyingHandling);	// mov     ecx), g_handling.m_pFlyingHandling[eax]	; sub_8DBEC0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBFEF + 2), &g_handling.gta_iv->m_pBoatHandling);	// mov     ecx), g_handling.m_pBoatHandling[eax]	; sub_8DBEC0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DC024 + 2), &g_handling.gta_iv->m_pszId);	// lea     esi), g_handling.m_pszId[eax]	; sub_8DBEC0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD39851 + 1), g_handling.gta_iv);	// mov     edx, offset g_handling	; sub_D39850
		}
		#endif
	}

	// bike lines
	if(this->ms_bBikeLinesLimitSet)
	{
		// Allocate
		if (this->ms_iBikeLinesLimit > 40)
		{
			this->g_handlingBike.gta_iv = new Game_GTAIV::tBikeHandlingData[this->ms_iBikeLinesLimit];
			this->g_handlingBike.bIsAllocated.Set(true);
		}

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD39885 + 1), ms_iBikeLinesLimit - 1);	// mov     edx, 39 
		}
		#endif

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBA25 + 1), g_handlingBike.gta_iv);	// mov     edx, offset g_handlingBike	; sub_8DBA20
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBA6B + 1), g_handlingBike.gta_iv);	// mov     edx, offset g_handlingBike	; sub_8DBA50
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBDBA + 6), g_handlingBike.gta_iv);	// cmp     g_handling.m_pBikeHandling[ecx], offset g_handlingBike	; sub_8DBDA0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBDDD + 2), g_handlingBike.gta_iv);	// add     esi, offset g_handlingBike	; sub_8DBDA0
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD39880 + 1), g_handlingBike.gta_iv);	// mov     ecx, offset g_handlingBike	; sub_D39880
		}
		#endif

		// Define values for automatic patch
		CCodeMover::SetVariable("NUMBER_OF_HANDLING_BIKE_LINES", this->ms_iBikeLinesLimit);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddressRel(0x8DBDD2, 5, "\x01\x02\x81\xfa\x05\x04""NUMBER_OF_HANDLING_BIKE_LINES\x00\x01\x02\x0F\x8D\x15\xf0\xbd\x4d\x00\x00", 0x8DBDD7);	// line 1, 0x8DBDA0 - sub_8DBDA0 : cmp     edx, 40
		}
		#endif

		CCodeMover::DeleteVariable("NUMBER_OF_HANDLING_BIKE_LINES");
	}
	
	// flying lines
	if(this->ms_bFlyingLinesLimitSet)
	{
		// Allocate
		if (this->ms_iFlyingLinesLimit > 40)
		{
			this->g_handlingFlying.gta_iv = new Game_GTAIV::tFlyingHandlingData[this->ms_iFlyingLinesLimit];
			this->g_handlingFlying.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBA33 + 2), g_handlingFlying.gta_iv);	// mov     dword ptr [eax], offset g_handlingFlying	; sub_8DBA20
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBA83 + 2), g_handlingFlying.gta_iv);	// mov     dword ptr [eax], offset g_handlingFlying	; sub_8DBA50
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBE1A + 6), g_handlingFlying.gta_iv);	// cmp     g_handling.m_pFlyingHandling[ecx], offset g_handlingFlying	; sub_8DBE00
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBE3E + 2), g_handlingFlying.gta_iv);	// add     esi, offset g_handlingFlying	; sub_8DBE00
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD398A0 + 1), g_handlingFlying.gta_iv);	// mov     ecx, offset g_handlingFlying	; sub_D398A0
		}
		#endif

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD398A5 + 1), ms_iFlyingLinesLimit - 1);	// mov     edx, 39
		}
		#endif

		// Define values for automatic patch
		CCodeMover::SetVariable("NUMBER_OF_HANDLING_FLYING_LINES", this->ms_iFlyingLinesLimit);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddressRel(0x8DBE32, 5, "\x01\x02\x81\xf9\x05\x04""NUMBER_OF_HANDLING_FLYING_LINES\x00\x01\x02\x0F\x8D\x15\x51\xbe\x4d\x00\x00", 0x8DBE37);	// line 1, 0x8DBE00 - sub_8DBE00 : cmp     ecx, 40
		}
		#endif

		CCodeMover::DeleteVariable("NUMBER_OF_HANDLING_FLYING_LINES");
	}


	// boat lines
	if(this->ms_bBoatLinesLimitSet)
	{
		// Allocate
		if (this->ms_iBoatLinesLimit > 40)
		{
			this->g_handlingBoat.gta_iv = new Game_GTAIV::tBoatHandlingData[this->ms_iBoatLinesLimit];
			this->g_handlingBoat.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBA2A + 1), g_handlingBoat.gta_iv);	// mov     ecx, offset g_handlingBoat	; sub_8DBA20
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBA70 + 1), g_handlingBoat.gta_iv);	// mov     ecx, offset g_handlingBoat	; sub_8DBA50
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBE7A + 6), g_handlingBoat.gta_iv);	// cmp     g_handling.m_pBoatHandling[ecx], offset g_handlingBoat	; sub_8DBE60
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x8DBEA0 + 2), g_handlingBoat.gta_iv);	// add     esi, offset g_handlingBoat	; sub_8DBE60
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD398C0 + 1), g_handlingBoat.gta_iv);	// mov     ecx, offset g_handlingBoat	; sub_D398C0
		}
		#endif

		// Patch values
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD398C5 + 1), ms_iBoatLinesLimit - 1);	// mov     edx, 39

		// Define variables for automatic patch
		CCodeMover::SetVariable("NUMBER_OF_HANDLING_BOAT_LINES", this->ms_iBoatLinesLimit);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddressRel(0x8DBE92, 5, "\x01\x02\x81\xfa\x05\x04""NUMBER_OF_HANDLING_BOAT_LINES\x00\x01\x02\x0F\x8D\x15\xb3\xbe\x4d\x00\x00", 0x8DBE97);	// line 1, 0x8DBE60 - sub_8DBE60 : cmp     edx, 40
		}
		#endif

		// Delete variable
		CCodeMover::DeleteVariable("NUMBER_OF_HANDLING_BOAT_LINES");
	}
}
#endif

// Patches handling.cfg limit
void HandlingCfgLimits::PatchHandlingCfgLimit_GTA_SA()
{
	MAKE_VAR_GAME_VERSION();
	using namespace Game_GTASA;
		
	if (CPatch::IsDebugModeActive())
	{
		this->ms_iStandardLinesLimit = 210;
		this->ms_iBikeLinesLimit = 13;
		this->ms_iFlyingLinesLimit = 24;
		this->ms_iBoatLinesLimit = 12;
	}
	
	CGenericLogStorage::SaveFormattedTextLn("Enabling handling.cfg limit adjuster.\nNew limits:\n"
		"Number of standard lines = %d\n"
		"Number of bike lines = %d\n"
		"Number of flying lines = %d\n"
		"Number of boat lines = %d\n"
		"Number of animation group lines = %d\n",

		ms_iStandardLinesLimit,
		ms_iBikeLinesLimit,
		ms_iFlyingLinesLimit,
		ms_iBoatLinesLimit,
		ms_iAnimationGroupLinesLimit
		);
	
	// Set up dynamic structures
	this->SetUpDynamicStructures(true);

	if (!CPatch::IsDebugModeActive())
	{
		bIs_cHandlingDataMgr_extended = true;

		this->m_sizeof_tHandlingData = TypeDetails::SizeOf<tHandlingData_extended>();

		mod_HandlingManager.ptr = (cHandlingDataMgr*)new char[
			TypeDetails::SizeOf<cHandlingDataMgr>()];

		memset(mod_HandlingManager.ptr, NULL, TypeDetails::SizeOf<cHandlingDataMgr>());

		mod_HandlingManager.bIsAllocated.Set(true);

		if (ms_iAnimationGroupLinesLimit > 30)
		{
			CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa = new CAnimGroup[ms_iAnimationGroupLinesLimit];

			memset(CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa,
				NULL,
				ms_iAnimationGroupLinesLimit * sizeof(CAnimGroup)
			);

			CVehicleAnimGroupData__m_vehicleAnimGroups.bIsAllocated.Set(true);
		}
	}	

	CGenericLogStorage::SaveFormattedTextLn(
		"&mod_HandlingManager = 0x%X, sizeof(mod_HandlingManager) = 0x%X",
		mod_HandlingManager.ptr,
		TypeDetails::SizeOf<cHandlingDataMgr>()
	);

	CGenericLogStorage::WriteLineSeparator();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		this->PatchHandlingCfgLimit_GTA_SA_1_0_US_WIN_X86();
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if(gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		this->PatchHandlingCfgLimit_GTA_SA_2_0_ANDROID_ARM32();
	#endif
}

// Patches handling.cfg limit
void HandlingCfgLimits::PatchHandlingCfgLimit_GTA_IV()
{
	MAKE_VAR_GAME_VERSION();

	// if debug
	if (CPatch::IsDebugModeActive())
	{
		this->ms_iStandardLinesLimit = 160;
		this->ms_iBikeLinesLimit = 40;
		this->ms_iFlyingLinesLimit = 40;
		this->ms_iBoatLinesLimit = 40;
	}

	// Print to log
	#if TRUE
	{
		CGenericLogStorage::SaveFormattedTextLn("Enabling handling.cfg limit adjuster.\nNew limits:\n"
			"Number of standard lines = %d\n"
			"Number of bike lines = %d\n"
			"Number of flying lines = %d\n"
			"Number of boat lines = %d",

			ms_iStandardLinesLimit,
			ms_iBikeLinesLimit,
			ms_iFlyingLinesLimit,
			ms_iBoatLinesLimit
		);

		CGenericLogStorage::WriteLineSeparator();
	}
	#endif

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86)
		this->PatchHandlingCfgLimit_GTA_IV_1_0_4_0();
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		this->PatchHandlingCfgLimit_GTA_IV_1_0_7_0();
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		this->PatchHandlingCfgLimit_GTA_IV_1_0_8_0();
	else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
		this->PatchHandlingCfgLimit_GTA_EFLC_1_1_2_0();
	#endif
}

// Patches handling.cfg limit
void HandlingCfgLimits::PatchHandlingCfgLimit()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion) || gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		this->PatchHandlingCfgLimit_GTA_SA();
	#ifdef IS_PLATFORM_WIN_X86
	else if(gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
		this->PatchHandlingCfgLimit_GTA_VC_PC_1_0();
	#endif
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86
		)
		this->PatchHandlingCfgLimit_GTA_IV();

	CPatch::LeaveThisLevel();
}

// Set up dynamic structures
void HandlingCfgLimits::SetUpDynamicStructures(bool bExtendedPossible)
{
	MAKE_VAR_GAME_VERSION();

	bool bExtendStructures = bExtendedPossible && !CPatch::IsDebugModeActive();

	// Allocate tHandlingData
	g_StructAllocator.InitPerStruct();
	g_StructAllocator.Allocate(tHandlingData_extended::index);
	
	if(CGameVersion::IsAny_GTA_III(gameVersion))
		g_StructAllocator.SetTop(sizeof(tHandlingData_extended::parent.gta_iii));
	if (CGameVersion::IsAny_GTA_VC(gameVersion))
		g_StructAllocator.SetTop(sizeof(tHandlingData_extended::parent.gta_vc));
	else if (CGameVersion::IsAny_GTA_SA(gameVersion))
		g_StructAllocator.SetTop(sizeof(tHandlingData_extended::parent.gta_sa));
	
	g_StructAllocator.SetMaxAlignmentUsed(4);

	if (bExtendStructures)
	{
		g_StructAllocator.Allocate(tHandlingData_extended::handlingName);
		g_StructAllocator.Allocate(tHandlingData_extended::bIsStandardEntryAllocated);
		g_StructAllocator.Allocate(tHandlingData_extended::pBikeHandling);
		g_StructAllocator.Allocate(tHandlingData_extended::pFlyingHandling);
		g_StructAllocator.Allocate(tHandlingData_extended::pBoatHandling);
	}

	g_StructAllocator.Allocate(tHandlingData_extended::endOfStructure);

	this->m_sizeof_tHandlingData = TypeDetails::SizeOf<tHandlingData_extended>();
	
	// Allocate cHandlingDataMgr
	g_StructAllocator.InitPerStruct();
	g_StructAllocator.Allocate(cHandlingDataMgr::field_0);
	g_StructAllocator.Allocate(cHandlingDataMgr::field_4);
	g_StructAllocator.Allocate(cHandlingDataMgr::field_8);
	g_StructAllocator.Allocate(cHandlingDataMgr::field_C);
	g_StructAllocator.Allocate(cHandlingDataMgr::field_10);	

	if(bExtendStructures)
	{
		g_StructAllocator.Allocate(cHandlingDataMgr::cHandlingDataMgr_extended_magicID);
		g_StructAllocator.Allocate(cHandlingDataMgr::sizeof_cHandlingDataMgr_header);

		g_StructAllocator.Allocate(cHandlingDataMgr::numberOfVehicleLines);
		g_StructAllocator.Allocate(cHandlingDataMgr::numberOfBikeLines);
		g_StructAllocator.Allocate(cHandlingDataMgr::numberOfFlyingLines);
		g_StructAllocator.Allocate(cHandlingDataMgr::numberOfBoatLines);

		g_StructAllocator.Allocate(cHandlingDataMgr::m_aStandardHandling_offset);
		g_StructAllocator.Allocate(cHandlingDataMgr::m_aBikeHandling_offset);
		g_StructAllocator.Allocate(cHandlingDataMgr::m_aFlyingHandling_offset);
		g_StructAllocator.Allocate(cHandlingDataMgr::m_aBoatHandling_offset);
		g_StructAllocator.Allocate(cHandlingDataMgr::m_pVehicleAnimGroups);

		g_StructAllocator.Allocate(cHandlingDataMgr::m_sizeof_tHandlingData);
		g_StructAllocator.Allocate(cHandlingDataMgr::m_sizeof_tBikeHandlingData);
		g_StructAllocator.Allocate(cHandlingDataMgr::m_sizeof_tFlyingHandlingData);
		g_StructAllocator.Allocate(cHandlingDataMgr::m_sizeof_tBoatHandlingData);
		g_StructAllocator.Allocate(cHandlingDataMgr::m_sizeof_CAnimGroup);

		g_StructAllocator.Allocate(cHandlingDataMgr::m_iStandardLinesLimit);
		g_StructAllocator.Allocate(cHandlingDataMgr::m_iBikeLinesLimit);
		g_StructAllocator.Allocate(cHandlingDataMgr::m_iFlyingLinesLimit);
		g_StructAllocator.Allocate(cHandlingDataMgr::m_iBoatLinesLimit);
		g_StructAllocator.Allocate(cHandlingDataMgr::m_iAnimationGroupLinesLimit);
		g_StructAllocator.Allocate(cHandlingDataMgr::endOfStructureHeader);
	}

	g_StructAllocator.Allocate(
		cHandlingDataMgr::m_standardEntryArray,
		ms_iStandardLinesLimit
	);

	g_StructAllocator.Allocate(
		cHandlingDataMgr::m_bikeEntryArray,
		ms_iBikeLinesLimit * this->m_sizeof_tBikeHandlingData
	);

	g_StructAllocator.Allocate(
		cHandlingDataMgr::m_flyingEntryArray,
		ms_iFlyingLinesLimit * this->m_sizeof_tFlyingHandlingData
	);

	g_StructAllocator.Allocate(
		cHandlingDataMgr::m_boatEntryArray,
		ms_iBoatLinesLimit * this->m_sizeof_tBoatHandlingData
	);

	if (CGameVersion::IsAny_GTA_VC(gameVersion))
		g_StructAllocator.AllocateUnknownData<uint32_t>();

	g_StructAllocator.Allocate(cHandlingDataMgr::endOfStructure);
}

// Initialize
void HandlingCfgLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();
	this->bIs_cHandlingDataMgr_extended = false;	
	this->ms_bStandardLinesLimitSet = false;
	this->ms_bBikeLinesLimitSet = false;
	this->ms_bFlyingLinesLimitSet = false;
	this->ms_bBoatLinesLimitSet = false;
	this->ms_bAnimationGroupLinesLimitSet = false;

	this->ms_iAnimationGroupLinesLimit = 0;
	
	if (CGameVersion::IsAny_GTA_III(gameVersion))
	{
		/*
		// Limit values
		this->ms_iStandardLinesLimit = 106;
		this->ms_iBikeLinesLimit = 5;
		this->ms_iFlyingLinesLimit = 10;
		this->ms_iBoatLinesLimit = 11;

		this->mod_HandlingManager.ptr = (cHandlingDataMgr*)0x978E58;

		// sizes	
		this->m_sizeof_tHandlingData = sizeof(Game_GTAVC::tHandlingData);
		this->m_sizeof_tBikeHandlingData = sizeof(Game_GTAVC::tBikeHandlingData);
		this->m_sizeof_tFlyingHandlingData = sizeof(Game_GTAVC::tFlyingHandlingData);
		this->m_sizeof_tBoatHandlingData = sizeof(Game_GTAVC::tBoatHandlingData);

		this->SetUpDynamicStructures();
		*/
	}
	else if (CGameVersion::IsAny_GTA_VC(gameVersion))
	{
		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if(gameVersion == GAME_VERSION_GTA_VC_1_0_WIN_X86)
				Address_cHandlingDataMgr__ConvertDataToGameUnits = 0x5ABAA0;
			#elif defined(IS_PLATFORM_ANDROID)
			Address_cHandlingDataMgr__ConvertDataToGameUnits = (uintptr_t)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN16cHandlingDataMgr22ConvertDataToGameUnitsEP13tHandlingData"
			);
			#endif
		}

		// Limit values		
		this->ms_iStandardLinesLimit = 106;
		this->ms_iBikeLinesLimit = 5;
		this->ms_iFlyingLinesLimit = 10;
		this->ms_iBoatLinesLimit = 11;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
				this->mod_HandlingManager.ptr = (cHandlingDataMgr*)0x978E58;
			#endif
		}

		// sizes	
		this->m_sizeof_tHandlingData = sizeof(Game_GTAVC::tHandlingData);
		this->m_sizeof_tBikeHandlingData = sizeof(Game_GTAVC::tBikeHandlingData);
		this->m_sizeof_tFlyingHandlingData = sizeof(Game_GTAVC::tFlyingHandlingData);
		this->m_sizeof_tBoatHandlingData = sizeof(Game_GTAVC::tBoatHandlingData);

		this->SetUpDynamicStructures();
	}
	else if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
				Address_cHandlingDataMgr__ConvertDataToGameUnits = 0x6F5080;
			#elif defined(IS_PLATFORM_ANDROID)
			Address_cHandlingDataMgr__ConvertDataToGameUnits = (uintptr_t)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN16cHandlingDataMgr22ConvertDataToGameUnitsEP13tHandlingData"
			);
			#endif
		}

		// Limit values
		this->ms_iStandardLinesLimit = 210;
		this->ms_iBikeLinesLimit = 13;
		this->ms_iFlyingLinesLimit = 24;
		this->ms_iBoatLinesLimit = 12;
		this->ms_iAnimationGroupLinesLimit = 30;

		if(g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				this->mod_HandlingManager.ptr = (cHandlingDataMgr*)0xC2B9C8;
				this->CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa = (Game_GTASA::CAnimGroup*)0xC1CDC0;
			}
			#elif defined(IS_PLATFORM_WIN_X64)
			if (gameVersion == GAME_VERSION_GTA_TRILOGY_SA_1_0_0_14388_WIN_X64)
			{
				this->mod_HandlingManager.ptr = (cHandlingDataMgr*)g_mCalc.GetCurrentVAbyPreferedVA(0x1454ACEB0);
				///// this->CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa = (Game_GTASA::CAnimGroup*)0xC1CDC0;
			}
			#elif defined(IS_PLATFORM_ANDROID)
			this->mod_HandlingManager.ptr = (cHandlingDataMgr*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"mod_HandlingManager"
			);

			this->CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa = (Game_GTASA::CAnimGroup*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN21CVehicleAnimGroupData19m_vehicleAnimGroupsE"
			);
			#endif
		}

		// sizes	
		this->m_sizeof_tHandlingData = sizeof(Game_GTASA::tHandlingData);
		this->m_sizeof_tBikeHandlingData = sizeof(Game_GTASA::tBikeHandlingData);
		this->m_sizeof_tFlyingHandlingData = sizeof(Game_GTASA::tFlyingHandlingData);
		this->m_sizeof_tBoatHandlingData = sizeof(Game_GTASA::tBoatHandlingData);
		this->m_sizeof_CAnimGroup = sizeof(Game_GTASA::CAnimGroup);

		this->SetUpDynamicStructures();
	}
	else if (CGameVersion::IsAny_GTA_IV(gameVersion))
	{
		using namespace Game_GTAIV;

		this->ms_iStandardLinesLimit = 160;
		this->ms_iBikeLinesLimit = 40;
		this->ms_iFlyingLinesLimit = 40;
		this->ms_iBoatLinesLimit = 40;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86)
			{
				this->g_handling.gta_iv = (tHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x157ABB0);
				this->g_handlingBike.gta_iv = (Game_GTAIV::tBikeHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x15855B0);
				this->g_handlingFlying.gta_iv = (Game_GTAIV::tFlyingHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x1585FB0);
				this->g_handlingBoat.gta_iv = (Game_GTAIV::tBoatHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x1586EB0);
			}
			else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			{
				this->g_handling.gta_iv = (tHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x15E3BF0);
				this->g_handlingBike.gta_iv = (Game_GTAIV::tBikeHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x15EE5F0);
				this->g_handlingFlying.gta_iv = (Game_GTAIV::tFlyingHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x15EEFF0);
				this->g_handlingBoat.gta_iv = (Game_GTAIV::tBoatHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x15EFEF0);
			}
			else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				this->g_handling.gta_iv = (tHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x16773B0);
				this->g_handlingBike.gta_iv = (Game_GTAIV::tBikeHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x1681DB0);
				this->g_handlingFlying.gta_iv = (Game_GTAIV::tFlyingHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x16827B0);
				this->g_handlingBoat.gta_iv = (Game_GTAIV::tBoatHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x16836B0);
			}
			else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
			{
				this->g_handling.gta_iv = (tHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x11A5F00);
				this->g_handlingBike.gta_iv = (Game_GTAIV::tBikeHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x11B0900);
				this->g_handlingFlying.gta_iv = (Game_GTAIV::tFlyingHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x11B1300);
				this->g_handlingBoat.gta_iv = (Game_GTAIV::tBoatHandlingData*)g_mCalc.GetCurrentVAbyPreferedVA(0x11B2200);
			}
			#endif
		}
	}
}

// Shutdown
void HandlingCfgLimits::Shutdown()
{
	MAKE_VAR_GAME_VERSION();

	if (mod_HandlingManager.bIsAllocated.Get())
		delete mod_HandlingManager.ptr;

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		if (CVehicleAnimGroupData__m_vehicleAnimGroups.bIsAllocated.Get())
			delete[] CVehicleAnimGroupData__m_vehicleAnimGroups.gta_sa;
	}
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
	{
		if (g_handling.bIsAllocated.Get())
			delete[] g_handling.gta_iv;

		if (g_handlingBike.bIsAllocated.Get())
			delete[] g_handlingBike.gta_iv;

		if (g_handlingFlying.bIsAllocated.Get())
			delete[] g_handlingFlying.gta_iv;

		if (g_handlingBoat.bIsAllocated.Get())
			delete[] g_handlingBoat.gta_iv;
	}
}
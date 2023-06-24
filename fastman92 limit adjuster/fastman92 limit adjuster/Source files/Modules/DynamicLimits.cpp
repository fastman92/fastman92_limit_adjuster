/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "DynamicLimits.h"

#include "../Core/CPatch.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/CollisionLink.h"
#include "../GameStructures/Rockstar Games/CColModel.h"
#include "../GameStructures/Rockstar Games/CPtrNodeDoubleLink.h"
#include "../GameStructures/Rockstar Games/CPtrNodeSingleLink.h"

#include <Array\countof.h>

using namespace Game;

DynamicLimits g_dynamicLimits;

const tLimitDefinitionNonStatic DynamicLimits::ms_listOfDynamicLimits[] =
{	

	// { "", static_cast<tLimitMethodInt>(&DynamicLimits::) },
		
	{ "VehicleStructs", static_cast<tLimitMethodInt>(&DynamicLimits::SetVehicleStructs) },
	{ "rwObjectInstances", static_cast<tLimitMethodInt>(&DynamicLimits::SetRwObjectInstances) },	
	{ "Matrices", static_cast<tLimitMethodInt>(&DynamicLimits::SetMatrices) },	
	{ "PtrNode Singles", static_cast<tLimitMethodInt>(&DynamicLimits::SetPtrNodeSingles) },	
	{ "PtrNode Doubles", static_cast<tLimitMethodInt>(&DynamicLimits::SetPtrNodeDoubles) },
	{ "PtrNodes", static_cast<tLimitMethodInt>(&DynamicLimits::SetPtrNodes) },
	{ "EntryInfoNodes", static_cast<tLimitMethodInt>(&DynamicLimits::SetEntryInfoNodes) },
	{ "Vehicles", static_cast<tLimitMethodInt>(&DynamicLimits::SetVehicles) },	
	{ "Peds", static_cast<tLimitMethodInt>(&DynamicLimits::SetPeds) },
	{ "Objects", static_cast<tLimitMethodInt>(&DynamicLimits::SetObjects) },
	{ "Tasks", static_cast<tLimitMethodInt>(&DynamicLimits::SetTasks) },
	{ "CDummyTask", static_cast<tLimitMethodInt>(&DynamicLimits::SetCDummyTask) },
	{ "Events", static_cast<tLimitMethodInt>(&DynamicLimits::SetEvents) },
	{ "PointRoute", static_cast<tLimitMethodInt>(&DynamicLimits::SetPointRoute) },
	{ "PatrolRoute", static_cast<tLimitMethodInt>(&DynamicLimits::SetPatrolRoute) },
	{ "InteriorInst", static_cast<tLimitMethodInt>(&DynamicLimits::SetInteriorInst) },
	{ "PortalInst", static_cast<tLimitMethodInt>(&DynamicLimits::SetPortalInst) },
	{ "CAnimBlender", static_cast<tLimitMethodInt>(&DynamicLimits::SetCAnimBlender) },
	{ "CAtdNodeAnimChangePooledObject", static_cast<tLimitMethodInt>(&DynamicLimits::SetCAtdNodeAnimChangePooledObject) },
	{ "CAtdNodeAnimPlayer", static_cast<tLimitMethodInt>(&DynamicLimits::SetCAtdNodeAnimPlayer) },
	{ "crFrameFilterBoneMask", static_cast<tLimitMethodInt>(&DynamicLimits::SetcrFrameFilterBoneMask) },
	{ "crFrameFilterBoneAnalogue", static_cast<tLimitMethodInt>(&DynamicLimits::SetcrFrameFilterBoneAnalogue) },
	{ "crExpressionProcessor", static_cast<tLimitMethodInt>(&DynamicLimits::SetcrExpressionProcessor) },
	{ "crmtObserver", static_cast<tLimitMethodInt>(&DynamicLimits::SetcrmtObserver) },
	{ "NavMeshRoute", static_cast<tLimitMethodInt>(&DynamicLimits::SetNavMeshRoute) },
	{ "Cam", static_cast<tLimitMethodInt>(&DynamicLimits::SetCam) },
	{ "ExplosionType", static_cast<tLimitMethodInt>(&DynamicLimits::SetExplosionType) },
	{ "NodeRoute", static_cast<tLimitMethodInt>(&DynamicLimits::SetNodeRoute) },
	{ "TaskAllocator", static_cast<tLimitMethodInt>(&DynamicLimits::SetTaskAllocator) },
	{ "PedIntelligence", static_cast<tLimitMethodInt>(&DynamicLimits::SetPedIntelligence) },
	{ "PedAttractors", static_cast<tLimitMethodInt>(&DynamicLimits::SetPedAttractors) },
	{ "QuadTreeNodes", static_cast<tLimitMethodInt>(&DynamicLimits::SetQuadTreeNodes) },
	{ "Collision links", static_cast<tLimitMethodInt>(&DynamicLimits::SetCollisionLinks) },
	{ "ColModels", static_cast<tLimitMethodInt>(&DynamicLimits::SetColModels) },
	{ "CustomEnvMapPipeMatDataPool", static_cast<tLimitMethodInt>(&DynamicLimits::SetCustomEnvMapPipeMatDataPool) },
	{ "CustomEnvMapPipeAtmDataPool", static_cast<tLimitMethodInt>(&DynamicLimits::SetCustomEnvMapPipeAtmDataPool) },
	{ "CustomSpecMapPipeMaterialDataPool", static_cast<tLimitMethodInt>(&DynamicLimits::SetCustomSpecMapPipeMaterialDataPool) },
	{ "Reach driver", static_cast<tLimitMethodInt>(&DynamicLimits::SetReachDriver) },
	{ "Prop anim", static_cast<tLimitMethodInt>(&DynamicLimits::SetPropAnim) }
};

const int DynamicLimits::ms_numberOfLimits = _countof(DynamicLimits::ms_listOfDynamicLimits);

#ifdef IS_PLATFORM_ANDROID_ARM32
extern "C"
{
	uintptr_t Address_CPools__Initialise_18E9A8_arm = 0;
}
#endif

#ifdef IS_PLATFORM_WIN_X86
const char* strVehicleStruct = "VehicleStruct";
uintptr_t patch_vehicleStructs_push_goBack = 0;


static NAKED void patch_vehicleStructs_push()
{
	__asm
	{
		push strVehicleStruct;	// push "VehicleStruct"
		push ASM_ACCESS_LIMIT_VAR_32_BIT(g_dynamicLimits, DynamicLimits, ms_VehicleStructsLimit);

		// go back
		jmp[patch_vehicleStructs_push_goBack];
	}
}

namespace Game_GTASA_PC_HOODLUM
{
	static NAKED void patch_vehicleStructs_43A102()
	{
		__asm
		{
			cmp edi, ASM_ACCESS_LIMIT_VAR_32_BIT(g_dynamicLimits, DynamicLimits, ms_VehicleStructsLimit);
			jle goSpawn;

			push 0x43A107;
			retn;

		goSpawn:
			push 0x43A11B;
			retn;
		}
	}
}
#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
uintptr_t DynamicLimits_address_operator_new_array = 0;

namespace Game_GTASA_2_0
{
	extern "C"
	{
		uintptr_t Address_CVehicleModelInfo__SetupCommonData_goBack1 = 0;
	}

	static TARGET_THUMB NAKED void CVehicleModelInfo__SetupCommonData_468B7E()
	{
		__asm volatile(
		".thumb\n"
			ASM_LOAD_ADDRESS_OF_SYMBOL(R0, g_dynamicLimits)
			"LDR R0, [R0, #%c[offset_VehicleStructsLimit]]\n"

			"MOV           R1, #0x32C\n"
			"MULS            R0, R1\n"

			ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(DynamicLimits_address_operator_new_array)

			"STR             R0, [R4]\n"
			
			ASM_LOAD_ADDRESS_OF_SYMBOL(R0, g_dynamicLimits)
			"LDR R0, [R0, #%c[offset_VehicleStructsLimit]]\n"
			"MOV R5, R0\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVehicleModelInfo__SetupCommonData_goBack1)

			::[offset_VehicleStructsLimit]"i"(offsetof(DynamicLimits, ms_VehicleStructsLimit))
			);
	}

	extern "C"
	{
		uintptr_t Address_CVehicleModelInfo__SetupCommonData_goBack2 = 0;
	}

	static TARGET_THUMB NAKED void CVehicleModelInfo__SetupCommonData_468BC2()
	{
		__asm volatile(
			".thumb\n"
			"LDRB            R2, [R1,R0]\n"
			"AND.W           R2, R2, #0x80\n"
			"STRB            R2, [R1,R0]\n"
			"ADDS            R0, #1\n"
			"CMP             R0, R5\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVehicleModelInfo__SetupCommonData_goBack2)
			);
	}
}
#endif

// Vehicle structs
void DynamicLimits::SetVehicleStructs(unsigned int iVehicleStructs)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA_PC_HOODLUM;
		
		CPatch::RedirectCode(0x5B8FDE, &patch_vehicleStructs_push);
		patch_vehicleStructs_push_goBack = 0x5B8FE5;

		CPatch::RedirectCode(0x43A102, &patch_vehicleStructs_43A102);
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86)
	{
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xA7179B), &patch_vehicleStructs_push);
		patch_vehicleStructs_push_goBack = g_mCalc.GetCurrentVAbyPreferedVA(0xA717A2);
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
	{
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xBEA86B), &patch_vehicleStructs_push);
		patch_vehicleStructs_push_goBack = g_mCalc.GetCurrentVAbyPreferedVA(0xBEA872);
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xA4A2AB), &patch_vehicleStructs_push);
		patch_vehicleStructs_push_goBack = g_mCalc.GetCurrentVAbyPreferedVA(0xA4A2B2);
	}
	else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
	{
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xB53B8B), &patch_vehicleStructs_push);
		patch_vehicleStructs_push_goBack = g_mCalc.GetCurrentVAbyPreferedVA(0xB53B92);
	}
	else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_3_0_WIN_X86)
	{
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0xA14C6B), &patch_vehicleStructs_push);
		patch_vehicleStructs_push_goBack = g_mCalc.GetCurrentVAbyPreferedVA(0xA14C72); 
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA_2_0;

		Address_CVehicleModelInfo__SetupCommonData_goBack1 = g_mCalc.GetCurrentVAbyPreferedVA(
			ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x468B8C)
		);

		CPatch::RedirectCodeEx(
			INSTRUCTION_SET_THUMB,
			g_mCalc.GetCurrentVAbyPreferedVA(0x468B7E),
			(void*)&CVehicleModelInfo__SetupCommonData_468B7E
			);

		/////
		Address_CVehicleModelInfo__SetupCommonData_goBack2 = g_mCalc.GetCurrentVAbyPreferedVA(
			ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x468BCE)
		);

		CPatch::RedirectCodeEx(
			INSTRUCTION_SET_THUMB,
			g_mCalc.GetCurrentVAbyPreferedVA(0x468BC2),
			(void*)&CVehicleModelInfo__SetupCommonData_468BC2
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	DynamicLimits::ms_VehicleStructsLimit = iVehicleStructs;

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of DYNAMIC LIMITS: VehicleStructs to: %d", iVehicleStructs);
	CGenericLogStorage::WriteLineSeparator();
}

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
namespace Game_GTASA
{
	extern "C"
	{
		uint32_t PtrNodeSinglesLimit = 0;
		uint32_t PtrNodeSinglesLimitMultipliedBySizeOfCPtrNodeSingleLink = 0;
	}

	// patch for 0x40C8C0
	extern "C"
	{
		uintptr_t Address_CPools__Initialise_40C8D6_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPools__Initialise_40C8C0()
	{
		__asm(
			".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, PtrNodeSinglesLimitMultipliedBySizeOfCPtrNodeSingleLink)

			"BL 1f\n"
			"STR R0, [R4]\n"

			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, PtrNodeSinglesLimit)

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPools__Initialise_40C8D6_thumb)

			// Branches
			"1:\n"	// _Znaj
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPools__Initialise_18E9A8_arm)
			);
	}
}
#endif

// PtrNode Singles
void DynamicLimits::SetPtrNodeSingles(unsigned int iPtrNodeSingles)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPtrNodeSingles = this->ms_PtrNodeSinglesLimit;
	
	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x550F45 + 1, iPtrNodeSingles);	// push    70000
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xB534B5 + 1), iPtrNodeSingles);	// push    80000
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8DDAE5 + 1), iPtrNodeSingles);	// push    80000
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;
		using namespace Game_GTA;

		// Set variables
		Game_GTASA::PtrNodeSinglesLimit = iPtrNodeSingles;
		Game_GTASA::PtrNodeSinglesLimitMultipliedBySizeOfCPtrNodeSingleLink = iPtrNodeSingles * sizeof(CPtrNodeSingleLink);

		// Changes
		Address_CPools__Initialise_18E9A8_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18E9A8));
		Address_CPools__Initialise_40C8D6_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x40C8D6));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x40C8C0),
			(void*)&patch_CPools__Initialise_40C8C0
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_PtrNodeSinglesLimit = iPtrNodeSingles;	

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: PtrNode Singles to: %d",
		iPtrNodeSingles
	);
	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

#ifdef IS_PLATFORM_ANDROID_ARM32
namespace Game_GTASA
{
	extern "C"
	{
		uint32_t PtrNodeDoublesLimit = 0;
		uint32_t PtrNodeDoublesLimitMultipliedBySizeOfCPtrNodeDoubleLink = 0;
	}

	// patch for 0x40C92E
	extern "C"
	{
		uintptr_t Address_CPools__Initialise_40C944_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPools__Initialise_40C92E()
	{
		__asm(
			".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, PtrNodeDoublesLimitMultipliedBySizeOfCPtrNodeDoubleLink)

			"BL 1f\n"
			"STR R0, [R4]\n"

			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, PtrNodeDoublesLimit)
			"MOV R5, R0\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPools__Initialise_40C944_thumb)

			// Branches
			"1:\n"	// _Znaj
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPools__Initialise_18E9A8_arm)
			);
	}
}
#endif

// PtrNode Doubles
void DynamicLimits::SetPtrNodeDoubles(unsigned int iPtrNodeDoubles)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPtrNodeDoubles = this->ms_PtrNodeDoublesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x550F81 + 1, iPtrNodeDoubles);	// push    3200
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xB534F5 + 1), iPtrNodeDoubles);	// push    16000
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8DDB25 + 1), iPtrNodeDoubles);	// push    16000
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		// Set variables
		Game_GTASA::PtrNodeDoublesLimit = iPtrNodeDoubles;
		Game_GTASA::PtrNodeDoublesLimitMultipliedBySizeOfCPtrNodeDoubleLink = iPtrNodeDoubles * sizeof(CPtrNodeDoubleLink);

		// Changes
		Address_CPools__Initialise_18E9A8_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18E9A8));
		Address_CPools__Initialise_40C944_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x40C944));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x40C92E),
			(void*)&patch_CPools__Initialise_40C92E
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_PtrNodeDoublesLimit = iPtrNodeDoubles;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: PtrNode Doubles to: %d",
		iPtrNodeDoubles);
	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// PtrNode Singles
void DynamicLimits::SetPtrNodes(unsigned int iPtrNodes)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPtrNodes = this->ms_PtrNodesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
		CPatch::PatchUINT32(0x44D34C + 3, iPtrNodes);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_PtrNodesLimit = iPtrNodes;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of PtrNodes to: %d",
		iPtrNodes
	);
	CGenericLogStorage::WriteLineSeparator();		
}

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
namespace Game_GTASA
{
	extern "C"
	{
		uint32_t EntryInfoNodesLimit = 0;
		uint32_t EntryInfoNodesLimitMultipliedBySizeOfEntityNode = 0;
	}

	// patch for 0x40C99A
	extern "C"
	{
		uintptr_t Address_CPools__Initialise_40C9AC_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPools__Initialise_40C99A()
	{
		__asm(
			".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, EntryInfoNodesLimitMultipliedBySizeOfEntityNode)
			"BL 1f\n"
			"STR R0, [R4]\n"

			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, EntryInfoNodesLimit)
			"MOV R5, R0\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPools__Initialise_40C9AC_thumb)

			// Branches
			"1:\n"	// _Znaj
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPools__Initialise_18E9A8_arm)
			);
	}

	// patch for 0x40C9E8
	extern "C"
	{
		uintptr_t Address_CPools__Initialise_40C9F0_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPools__Initialise_40C9E8()
	{
		__asm(
			".thumb\n"
			"STRB R2, [R1,R0]\n"
			"ADDS R0, #1\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, EntryInfoNodesLimit)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPools__Initialise_40C9F0_thumb)
			);
	}
}
#endif

// EntryInfoNodes
void DynamicLimits::SetEntryInfoNodes(unsigned int iEntryInfoNodes)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iEntryInfoNodes = this->ms_EntryInfoNodesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x550FB9 + 1, iEntryInfoNodes);	// push    500
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xC796D5 + 1), iEntryInfoNodes);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xBA47C5 + 1), iEntryInfoNodes);
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
		CPatch::PatchUINT32(0x44D38A + 3, iEntryInfoNodes);	// push    500	
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		// Set variables
		Game_GTASA::EntryInfoNodesLimit = iEntryInfoNodes;
		Game_GTASA::EntryInfoNodesLimitMultipliedBySizeOfEntityNode = iEntryInfoNodes * 0x14;

		// Changes
		Address_CPools__Initialise_18E9A8_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18E9A8));
		Address_CPools__Initialise_40C9AC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x40C9AC));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x40C99A),
			(void*)&patch_CPools__Initialise_40C99A
		);

		Address_CPools__Initialise_40C9F0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x40C9F0));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x40C9E8),
			(void*)&patch_CPools__Initialise_40C9E8
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_EntryInfoNodesLimit = iEntryInfoNodes;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: EntryInfoNodes to: %d",
		iEntryInfoNodes
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Peds
void DynamicLimits::SetPeds(unsigned int iPeds)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPeds = this->ms_PedsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		if (iPeds > 140)
		{
			CReplay__m_PedPoolConversion.ptr = new int32_t[iPeds];
			CReplay__m_PedPoolConversion.bIsAllocated.Set(true);
		}

		// CPools::Initialise
		CPatch::PatchUINT32(0x550FF1 + 1, iPeds);	// push    140

		if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
		{
			// CReplay::InitialisePedPoolConversionTable
			CPatch::PatchUINT32(0x45EF2E + 1, iPeds);	// mov     ecx, 140
			CPatch::PatchUINT32(0x45EF62 + 2, iPeds);	// cmp     esi, 140
			CPatch::PatchUINT32(0x45EF7F + 2, iPeds);	// cmp     esi, 140
			CPatch::PatchUINT32(0x45EF8E + 2, iPeds * this->sizeof_CPed);	// cmp     ebx, 278320

			// CReplay::m_PedPoolConversion
			#if TRUE			
			{
				CPatch::PatchPointer(0x45C454 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     eax, _ZN7CReplay19m_PedPoolConversionE[eax*4]; CReplay::m_PedPoolConversion	; _ZN7CReplay19FindPoolIndexForPedEi
				CPatch::PatchPointer(0x45C474 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     edx, _ZN7CReplay19m_PedPoolConversionE[ecx*4]; CReplay::m_PedPoolConversion	; _ZN7CReplay24CanWeFindPoolIndexForPedEi
				CPatch::PatchPointer(0x45CEC9 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     eax, _ZN7CReplay19m_PedPoolConversionE[eax*4]; CReplay::m_PedPoolConversion	; _ZN7CReplay20DealWithNewPedPacketEP13CPacketNewPedbP20CPacketPlayerClothes
				CPatch::PatchPointer(0x45CF32 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     eax, _ZN7CReplay19m_PedPoolConversionE[edx*4]; CReplay::m_PedPoolConversion	; _ZN7CReplay20DealWithNewPedPacketEP13CPacketNewPedbP20CPacketPlayerClothes
				CPatch::PatchPointer(0x45CFA0 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     eax, _ZN7CReplay19m_PedPoolConversionE[eax*4]; CReplay::m_PedPoolConversion	; _ZN7CReplay20DealWithNewPedPacketEP13CPacketNewPedbP20CPacketPlayerClothes
				CPatch::PatchPointer(0x45D5B4 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     ecx, _ZN7CReplay19m_PedPoolConversionE[eax*4]; CReplay::m_PedPoolConversion	; _ZN7CReplay15CreatePlayerPedEv
				CPatch::PatchPointer(0x45EF33 + 1, CReplay__m_PedPoolConversion.ptr);	// mov     edi, offset _ZN7CReplay19m_PedPoolConversionE; CReplay::m_PedPoolConversion	; _ZN7CReplay32InitialisePedPoolConversionTableEv
				CPatch::PatchPointer(0x45EF77 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     _ZN7CReplay19m_PedPoolConversionE[esi*4], edi; CReplay::m_PedPoolConversion	; _ZN7CReplay32InitialisePedPoolConversionTableEv
				CPatch::PatchPointer(0x45FC78 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     eax, _ZN7CReplay19m_PedPoolConversionE[edx*4]; CReplay::m_PedPoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
				CPatch::PatchPointer(0x45FF4F + 3, CReplay__m_PedPoolConversion.ptr);	// mov     eax, _ZN7CReplay19m_PedPoolConversionE[ecx*4]; CReplay::m_PedPoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
			}
			#endif

		}
		else if(gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		{
			// CReplay::InitialisePedPoolConversionTable
			CPatch::PatchUINT32(0x156B3AE + 1, iPeds);	// mov     ecx, 140
			CPatch::PatchUINT32(0x156B3E2 + 2, iPeds);	// cmp     esi, 140
			CPatch::PatchUINT32(0x156B3FF + 2, iPeds);	// cmp     esi, 140
			CPatch::PatchUINT32(0x156B40E + 2, iPeds * this->sizeof_CPed);

			// CReplay::m_PedPoolConversion
			#if TRUE
			{
				CPatch::PatchPointer(0x45C454 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     eax, ds:_ZN7CReplay19m_PedPoolConversionE[eax*4]; CReplay::m_PedPoolConversion	; sub_45C450
				CPatch::PatchPointer(0x45C474 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     edx, ds:_ZN7CReplay19m_PedPoolConversionE[ecx*4]; CReplay::m_PedPoolConversion	; 
				CPatch::PatchPointer(0x45D5B4 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     ecx, ds:_ZN7CReplay19m_PedPoolConversionE[eax*4]; CReplay::m_PedPoolConversion	; sub_45D540
				CPatch::PatchPointer(0x45FC78 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     eax, ds:_ZN7CReplay19m_PedPoolConversionE[edx*4]; CReplay::m_PedPoolConversion	; sub_45F380
				CPatch::PatchPointer(0x45FF4F + 3, CReplay__m_PedPoolConversion.ptr);	// mov     eax, ds:_ZN7CReplay19m_PedPoolConversionE[ecx*4]; CReplay::m_PedPoolConversion	; sub_45F380
				CPatch::PatchPointer(0x156B3B3 + 1, CReplay__m_PedPoolConversion.ptr);	// mov     edi, offset _ZN7CReplay19m_PedPoolConversionE; CReplay::m_PedPoolConversion	; sub_156B3A0
				CPatch::PatchPointer(0x156B3F7 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     ds:_ZN7CReplay19m_PedPoolConversionE[esi*4], edi; CReplay::m_PedPoolConversion	; sub_156B3A0
				CPatch::PatchPointer(0x156ED99 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     eax, ds:_ZN7CReplay19m_PedPoolConversionE[eax*4]; CReplay::m_PedPoolConversion	; sub_45CEA0
				CPatch::PatchPointer(0x156EE13 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     eax, ds:_ZN7CReplay19m_PedPoolConversionE[edx*4]; CReplay::m_PedPoolConversion	; sub_45CEA0
				CPatch::PatchPointer(0x156EE81 + 3, CReplay__m_PedPoolConversion.ptr);	// mov     eax, ds:_ZN7CReplay19m_PedPoolConversionE[eax*4]; CReplay::m_PedPoolConversion	; sub_45CEA0
			}
			#endif
		}
	}
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
		CPatch::PatchUINT32(0x44D3F5 + 1, iPeds);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_PedsLimit = iPeds;

	if (iPeds > 256)
		CGenericLogStorage::SaveTextLn(
			"The replays may not work correctly if the limit"
			" of DYNAMIC LIMITS: Peds is higher than 256."
		);

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: Peds to: %d",
		iPeds
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Vehicles
void DynamicLimits::SetVehicles(unsigned int iVehicles)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iVehicles = this->ms_VehiclesLimit;

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		if (iVehicles > 110)
		{
			CReplay__m_VehiclePoolConversion.ptr = new int32_t[iVehicles];
			CReplay__m_VehiclePoolConversion.bIsAllocated.Set(true);
		}

		// CReplay::InitialiseVehiclePoolConversionTable
		CPatch::PatchUINT32(0x45EFAE + 1, iVehicles);	// mov     ecx, 110
		CPatch::PatchUINT32(0x45F003 + 2, iVehicles * this->sizeof_CVehicle);	// cmp     ebx, 284240

		// CReplay::m_VehiclePoolConversion
#if TRUE
		{
			// _ZN7CReplay16ProcessPedUpdateEP4CPedfP22CAddressInReplayBuffer
			CPatch::PatchPointer(0x45CB74 + 3, CReplay__m_VehiclePoolConversion.ptr - 1);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[eax*4-4]; CReplay::m_VehiclePoolConversion																			 
			CPatch::PatchPointer(0x45CE08 + 3, CReplay__m_VehiclePoolConversion.ptr - 1);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[edx*4-4]; CReplay::m_VehiclePoolConversion																			
			CPatch::PatchPointer(0x45CE60 + 3, CReplay__m_VehiclePoolConversion.ptr - 1);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[eax*4-4]; CReplay::m_VehiclePoolConversion

			CPatch::PatchPointer(0x45C464 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[eax*4]; CReplay::m_VehiclePoolConversion	; _sub_45C460
			CPatch::PatchPointer(0x45C494 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     edx, _ZN7CReplay23m_VehiclePoolConversionE[ecx*4]; CReplay::m_VehiclePoolConversion	; _sub_45C490
			CPatch::PatchPointer(0x45EFB3 + 1, CReplay__m_VehiclePoolConversion.ptr);	// mov     edi, offset _ZN7CReplay23m_VehiclePoolConversionE; CReplay::m_VehiclePoolConversion	; _ZN7CReplay36InitialiseVehiclePoolConversionTableEv
			CPatch::PatchPointer(0x45EFF4 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     _ZN7CReplay23m_VehiclePoolConversionE[esi*4], edi; CReplay::m_VehiclePoolConversion	; _ZN7CReplay36InitialiseVehiclePoolConversionTableEv
			CPatch::PatchPointer(0x45F3D5 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[ecx*4]; CReplay::m_VehiclePoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
			CPatch::PatchPointer(0x45F5F4 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[edx*4]; CReplay::m_VehiclePoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
			CPatch::PatchPointer(0x45F641 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[edx*4]; CReplay::m_VehiclePoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
			CPatch::PatchPointer(0x45F727 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[eax*4]; CReplay::m_VehiclePoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
			CPatch::PatchPointer(0x45F785 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[eax*4]; CReplay::m_VehiclePoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
			CPatch::PatchPointer(0x45F865 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[eax*4]; CReplay::m_VehiclePoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
			CPatch::PatchPointer(0x45F8B2 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[edx*4]; CReplay::m_VehiclePoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
			CPatch::PatchPointer(0x45F998 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[eax*4]; CReplay::m_VehiclePoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
			CPatch::PatchPointer(0x45F9E5 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[edx*4]; CReplay::m_VehiclePoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
			CPatch::PatchPointer(0x45FACB + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[eax*4]; CReplay::m_VehiclePoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
			CPatch::PatchPointer(0x45FB2C + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[ecx*4]; CReplay::m_VehiclePoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
			CPatch::PatchPointer(0x45FC12 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[eax*4]; CReplay::m_VehiclePoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
			CPatch::PatchPointer(0x45FF94 + 3, CReplay__m_VehiclePoolConversion.ptr);	// mov     eax, _ZN7CReplay23m_VehiclePoolConversionE[ecx*4]; CReplay::m_VehiclePoolConversion	; _ZN7CReplay30PlayBackThisFrameInterpolationEP22CAddressInReplayBufferfPj
		}
#endif

		// CPools::Initialise
		CCodeMover::SetVariable("VEHICLES_LIMIT", iVehicles);

#if TRUE
		// Count of active addresses: 2
		{
			CCodeMover::FixOnAddressRel(0x45EFE2, 5, "\x01\x02\x81\xfe\x05\x04""VEHICLES_LIMIT\x00\x01\x02\x0F\x84\x15\x0b\xf0\x05\x00\x00", 0x45EFE7);	// line 1, 0x45EFA0 - sub_45EFA0 : cmp     esi, 6Eh
			CCodeMover::FixOnAddressRel(0x551029, 9, "\x01\x01\x68\x05\x04""VEHICLES_LIMIT\x00\x13\x02\x2B\x10\x15\x00\x01\x01\xE8\x15\xc0\x04\x15\x00\x00", 0x551032);	// line 2, 0x550F10 - sub_550F10 : push    110
		}
#endif

		CCodeMover::DeleteVariable("VEHICLES_LIMIT");

		// There was a problem with reading an ID from SCM handle, because of an instruction for signed number being used.
		CPatch::EnterNewLevelAndDisableDebugState();
		{
			// CCarGenerator::Process
			CPatch::PatchMemoryData(0x6F3ED6, "\x0f\xb7\xc8", 3);
		}
		CPatch::LeaveThisLevel();
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x9D43B8 + 1), iVehicles);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8FE738 + 1), iVehicles);
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x44D3C8 + 3), iVehicles);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_VehiclesLimit = iVehicles;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: Vehicles to: %d",
		iVehicles
	);

	if (iVehicles > 256)
		CGenericLogStorage::SaveTextLn(
			"The replays may not work correctly if the limit"
			" of DYNAMIC LIMITS: Vehicles is higher than 256."
			" Car generators may also crash."
		);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Objects
void DynamicLimits::SetObjects(unsigned int iObjects)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iObjects = this->ms_ObjectsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x551096 + 1, iObjects);	// push    350
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8E3968 + 1), iObjects);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8ECD08 + 1), iObjects);
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
		CPatch::PatchUINT32(0x44D8BA + 3, iObjects);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	DynamicLimits::ms_ObjectsLimit = iObjects;	

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: Objects to: %d",
		iObjects
	);	

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Tasks
void DynamicLimits::SetTasks(unsigned int iTasks)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iTasks = this->ms_TasksLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x55113E + 1, iTasks);	// push    500
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xA28C68 + 1), iTasks);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xB031B8 + 1), iTasks);	
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	DynamicLimits::ms_TasksLimit = iTasks;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: Tasks to: %d",
		iTasks
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// CDummyTask
void DynamicLimits::SetCDummyTask(unsigned int iCDummyTask)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iCDummyTask = this->ms_CDummyTaskLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xC780D5 + 1), iCDummyTask);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xBBAEF5 + 1), iCDummyTask);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_CDummyTaskLimit = iCDummyTask;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: CDummyTask to: %d",
		iCDummyTask
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Events
void DynamicLimits::SetEvents(unsigned int iEvents)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iEvents = this->ms_EventsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x551176 + 1, iEvents);	// push    200
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x91C1C5 + 1), iEvents);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x9131D5 + 1), iEvents);	
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}	

	this->ms_EventsLimit = iEvents;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: Events to: %d",
		iEvents
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// PedIntelligence
void DynamicLimits::SetPedIntelligence(unsigned int iPedInteligence)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPedInteligence = this->ms_PedIntelligenceLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x551282 + 1, iPedInteligence);	// push    140
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	DynamicLimits::ms_PedIntelligenceLimit = iPedInteligence;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: PedIntelligence to: %d",
		iPedInteligence
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}


// Sets PointRoute
void DynamicLimits::SetPointRoute(unsigned int iPointRoute)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPointRoute = this->ms_PointRouteLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		CCodeMover::SetVariable("POINT_ROUTE_LIMIT", iPointRoute);
		CCodeMover::FixOnAddressRel(0x5511AE, 9, "\x01\x01\x68\x05\x04""POINT_ROUTE_LIMIT\x00\x02\x02\xB0\x11\x55\x00\x01\x01\xE8\x0F\x30\x0a\x55\x00\x00", 0x5511B7);	// line 1, 0x550F10 - _ZN6CPools10InitialiseEv : push    64
		CCodeMover::DeleteVariable("POINT_ROUTE_LIMIT");
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xC75D28 + 1), iPointRoute);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xC8AC08 + 1), iPointRoute);	
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_PointRouteLimit = iPointRoute;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: PointRoute to: %d",
		iPointRoute
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Sets PatrolRoute
void DynamicLimits::SetPatrolRoute(unsigned int iPatrolRoute)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPatrolRoute = this->ms_PatrolRouteLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
		)
	{
		CCodeMover::SetVariable("PATROL_ROUTE_LIMIT", iPatrolRoute);

		if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			CCodeMover::FixOnAddressRel(0x5511E3, 9, "\x01\x01\x68\x05\x04""PATROL_ROUTE_LIMIT\x00\x02\x02\xE5\x11\x55\x00\x01\x01\xE8\x0F\x00\x0b\x55\x00\x00", 0x5511EC);	// line 2, 0x550F10 - _ZN6CPools10InitialiseEv : push    32
		else if(gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			CCodeMover::FixOnAddressRel(0xC75DA8, 9, "\x01\x01\x68\x05\x04""PATROL_ROUTE_LIMIT\x00\x13\x02\xAA\x5D\x87\x00\x01\x01\xE8\x15\x10\x2f\x87\x00\x00", 0xC75DB1);	// line 1, 0xC75D90 - sub_C75D90 : push    32
		else if(gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			CCodeMover::FixOnAddressRel(0xC8AC88, 9, "\x01\x01\x68\x05\x04""PATROL_ROUTE_LIMIT\x00\x13\x02\x8A\xAC\x88\x00\x01\x01\xE8\x15\xb0\x3d\x3f\x00\x00", 0xC8AC91);	// line 1, 0xC8AC70 - sub_C8AC70 : push    32

		CCodeMover::DeleteVariable("PATROL_ROUTE_LIMIT");
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_PatrolRouteLimit = iPatrolRoute;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: PatrolRoute to: %d",
		iPatrolRoute
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Sets NodeRoute
void DynamicLimits::SetNodeRoute(unsigned int iNodeRoute)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();
	
	if (CPatch::IsDebugModeActive())
		iNodeRoute = this->ms_NodeRouteLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		CCodeMover::SetVariable("NODE_ROUTE_LIMIT", iNodeRoute);
		CCodeMover::FixOnAddressRel(0x551218, 9, "\x01\x01\x68\x05\x04""NODE_ROUTE_LIMIT\x00\x02\x02\x1A\x12\x55\x00\x01\x01\xE8\x0F\xd0\x0b\x55\x00\x00", 0x551221);	// line 3, 0x550F10 - _ZN6CPools10InitialiseEv : push    64
		CCodeMover::DeleteVariable("NODE_ROUTE_LIMIT");
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_NodeRouteLimit = iNodeRoute;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: NodeRoute to: %d",
		iNodeRoute
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}


// Sets TaskAllocator
void DynamicLimits::SetTaskAllocator(unsigned int iTaskAllocator)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iTaskAllocator = this->ms_TaskAllocatorLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		CCodeMover::SetVariable("TASK_ALLOCATOR_LIMIT", iTaskAllocator);
		CCodeMover::FixOnAddressRel(0x55124D, 9, "\x01\x01\x68\x05\x04""TASK_ALLOCATOR_LIMIT\x00\x02\x02\x4F\x12\x55\x00\x01\x01\xE8\x0F\xa0\x0c\x55\x00\x00", 0x551256);	// line 4, 0x550F10 - _ZN6CPools10InitialiseEv : push    10h
		CCodeMover::DeleteVariable("TASK_ALLOCATOR_LIMIT");
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_TaskAllocatorLimit = iTaskAllocator;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: TaskAllocator to: %d",
		iTaskAllocator
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}


// Sets PedAttractors
void DynamicLimits::SetPedAttractors(unsigned int iPedAttractors)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPedAttractors = this->ms_PedAttractorsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
		)
	{
		CCodeMover::SetVariable("PED_ATTRACTOR_LIMIT", iPedAttractors);

		if(CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			CCodeMover::FixOnAddressRel(0x5512BB, 9, "\x01\x01\x68\x05\x04""PED_ATTRACTOR_LIMIT\x00\x02\x02\xBD\x12\x55\x00\x01\x01\xE8\x0F\x40\x0e\x55\x00\x00", 0x5512C4);	// line 5, 0x550F10 - _ZN6CPools10InitialiseEv : push    64
		else if(gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			CCodeMover::FixOnAddressRel(0xCC1FB8, 9, "\x01\x01\x68\x05\x04""PED_ATTRACTOR_LIMIT\x00\x13\x02\xBA\x1F\x8C\x00\x01\x01\xE8\x15\x10\x2f\x87\x00\x00", 0xCC1FC1);	// line 1, 0xCC1FA0 - sub_CC1FA0 : push    64
		else if(gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			CCodeMover::FixOnAddressRel(0xCBF728, 9, "\x01\x01\x68\x05\x04""PED_ATTRACTOR_LIMIT\x00\x13\x02\x2A\xF7\x8B\x00\x01\x01\xE8\x15\xb0\x3d\x3f\x00\x00", 0xCBF731);	// line 1, 0xCBF710 - sub_CBF710 : push    64

		CCodeMover::DeleteVariable("PED_ATTRACTOR_LIMIT");
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	DynamicLimits::ms_PedAttractorsLimit = iPedAttractors;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: PedAttractors to: %d",
		iPedAttractors
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// QuadTreeNodes
void DynamicLimits::SetQuadTreeNodes(unsigned int iQuadTreeNodes)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iQuadTreeNodes = this->ms_QuadTreeNodesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x552C3E + 1, iQuadTreeNodes);	// push    400
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8DE195 + 1), iQuadTreeNodes);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xB6DF45 + 1), iQuadTreeNodes);	
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_QuadTreeNodesLimit = iQuadTreeNodes;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: QuadTreeNodes to: %d",
		iQuadTreeNodes
	);

	CGenericLogStorage::WriteLineSeparator();
}

// Collision links
void DynamicLimits::SetCollisionLinks(unsigned int iCollisionLinks)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iCollisionLinks = this->ms_CollisionLinksLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		#if TRUE
		{
			CPatch::PatchUINT32(0x416260 + 1, iCollisionLinks * sizeof(CollisionLink));	// push    600
			CPatch::PatchUINT32(0x41629B + 1, iCollisionLinks * sizeof(CollisionLink));	// mov     ecx, 600
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_CollisionLinksLimit = iCollisionLinks;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: Collision links to: %d",
		iCollisionLinks
	);

	CGenericLogStorage::WriteLineSeparator();
}

namespace Game_GTASA
{
	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
	extern "C"
	{
		uint32_t ColModelsLimit;
		uint32_t ColModelsLimitMultipliedBySizeOfCColModel;
	}

	// patch for 0x40CC28
	extern "C"
	{
		uintptr_t Address_CPools__Initialise_40CC3E_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPools__Initialise_40CC28()
	{
		__asm(
			".thumb\n"

			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, ColModelsLimitMultipliedBySizeOfCColModel)
			"BL 1f\n"
			"STR R0, [R4]\n"

			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, ColModelsLimit)
			"MOV R5, R0\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPools__Initialise_40CC3E_thumb)

			// Branches
			"1:\n"	// _Znaj
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPools__Initialise_18E9A8_arm)
			);
	}
	#endif
}

// Collision models
void DynamicLimits::SetColModels(unsigned int iColModels)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iColModels = this->ms_ColModelsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x551106 + 1, iColModels);	
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
		CPatch::PatchUINT32(0x44D83E + 3, iColModels);
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;
		Game_GTASA::ColModelsLimit = iColModels;
		ColModelsLimitMultipliedBySizeOfCColModel = iColModels * sizeof(CColModel);

		Address_CPools__Initialise_18E9A8_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18E9A8));
		Address_CPools__Initialise_40CC3E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x40CC3E));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x40CC28),
			(void*)&patch_CPools__Initialise_40CC28
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_ColModelsLimit = iColModels;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: ColModels to: %d",
		DynamicLimits::ms_ColModelsLimit
	);

	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

// Sets the CustomEnvMapPipeMatDataPool limit
void DynamicLimits::SetCustomEnvMapPipeMatDataPool(unsigned int iLimitValue)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iLimitValue = this->ms_CustomEnvMapPipeMatDataPoolLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x5DA08D + 1, iLimitValue);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_CustomEnvMapPipeMatDataPoolLimit = iLimitValue;

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of DYNAMIC MODELS: CustomEnvMapPipeMatDataPool to: %d", iLimitValue);
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

// Sets the CustomEnvMapPipeAtmDataPool limit
void DynamicLimits::SetCustomEnvMapPipeAtmDataPool(unsigned int iLimitValue)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iLimitValue = this->ms_CustomEnvMapPipeAtmDataPoolLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x5DA0C9 + 1, iLimitValue);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	DynamicLimits::ms_CustomEnvMapPipeAtmDataPoolLimit = iLimitValue;

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of DYNAMIC MODELS: CustomEnvMapPipeAtmDataPool to: %d", iLimitValue);
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

// Sets the CustomSpecMapPipeMaterialDataPool limit
void DynamicLimits::SetCustomSpecMapPipeMaterialDataPool(unsigned int iLimitValue)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iLimitValue = this->ms_CustomSpecMapPipeMaterialDataPoolLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x5DA105 + 1, iLimitValue);	
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_CustomSpecMapPipeMaterialDataPoolLimit = iLimitValue;

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of DYNAMIC MODELS: CustomSpecMapPipeMaterialDataPool to: %d", iLimitValue);
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
namespace Game_GTASA
{
	extern "C"
	{
		uint32_t rwObjectInstances_default_value_18000 = 0;
		uint32_t rwObjectInstances_default_value_1498 = 0;

		uint32_t rwObjectInstances_default_value_0x464C = 0;
		uint32_t rwObjectInstances_default_value_0x4648 = 0;
		uint32_t rwObjectInstances_default_value_0x4644 = 0;
		uint32_t rwObjectInstances_default_value_0x4640 = 0;
		uint32_t rwObjectInstances_default_value_0x4638 = 0;
		uint32_t rwObjectInstances_default_value_0x463C = 0;
		uint32_t rwObjectInstances_default_value_0x462C = 0;
	}

	// patch for 0x46BE20
	extern "C"
	{
		uintptr_t Address_CStreaming__Init2_18E9A8_arm = 0;
		uintptr_t Address_CStreaming__Init2_46BE36 = 0;
		uintptr_t Address_CStreaming__Init2_46BE78_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CStreaming__Init2_46BE20()
	{
		__asm(
			".thumb\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, rwObjectInstances_default_value_18000)
			"BL 1f\n"
			"LDR R1, =("/* _ZN10CStreaming20ms_rwObjectInstancesE_ptr */"0x67756C - 0x46BE36)\n"

			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R3, rwObjectInstances_default_value_0x464C)
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, rwObjectInstances_default_value_0x4648)
			
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_CStreaming__Init2_46BE36)
			"LDR R1, [R1]\n"
			"ADD R2, R1, #0xC\n"
			"STR R0, [R1,#0x30]\n"
			"STR R2, [R1,#8]\n"
			"ADD R2, R1, #0x24\n"
			"STR R2, [R0,R3]\n"

			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, rwObjectInstances_default_value_0x4644)
			
			"ADD R3, R1, #0x18\n"
			"STR R3, [R0,R6]\n"
			"ADD R2, R0\n"

			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, rwObjectInstances_default_value_0x4640)

			"STR R1, [R1,#0x10]\n"
			"STR R2, [R1,#0x28]\n"
			"STR R2, [R1,#0x20]\n"
			"STR R2, [R0,R6]\n"

			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, rwObjectInstances_default_value_0x4638)			

			"ADD R2, R0\n"
			"LDR R6, [R1,#0x20]\n"
			"STR R2, [R6,#4]\n"
			"MOV R6, #0x463C\n"
			"STR R3, [R0,R6]\n"

			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, rwObjectInstances_default_value_1498)			

			"LDR R3, =("/* _ZN10CStreaming20ms_rwObjectInstancesE_ptr */"0x67756C - 0x46BE7C)\n"
			"STR R2, [R1,#0x20]\n"
			
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, rwObjectInstances_default_value_0x462C)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CStreaming__Init2_46BE78_thumb)

			// Branches
			"1:\n"	// _Znaj
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CStreaming__Init2_18E9A8_arm)
			);
	}
}
#endif

// rwObjectInstances
void DynamicLimits::SetRwObjectInstances(unsigned int iRwObjectInstances)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iRwObjectInstances = this->ms_RwObjectInstancesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		const int elementSize = 0xC;

		CPatch::PatchUINT32(0x5B8E54 + 1, iRwObjectInstances * elementSize);
		CPatch::PatchUINT32(0x5B8EAF + 1, iRwObjectInstances * elementSize);
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if(gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		// Set variables
		const int elementSize = 0xC;
		
		// #define DUMP(name) OutputFormattedDebugString("%s, 0x%X or %d\n", #name, name, name)

		rwObjectInstances_default_value_18000 = iRwObjectInstances * elementSize;
		rwObjectInstances_default_value_1498 = iRwObjectInstances - 2;

		rwObjectInstances_default_value_0x464C = (iRwObjectInstances - 1) * elementSize + 8;
		rwObjectInstances_default_value_0x4648 = (iRwObjectInstances - 1) * elementSize + 4;
		rwObjectInstances_default_value_0x4644 = (iRwObjectInstances - 1) * elementSize;
		rwObjectInstances_default_value_0x4640 = (iRwObjectInstances - 2) * elementSize + 8;
		rwObjectInstances_default_value_0x4638 = (iRwObjectInstances - 2) * elementSize;
		rwObjectInstances_default_value_0x463C = (iRwObjectInstances - 2) * elementSize + 4;
		rwObjectInstances_default_value_0x462C = (iRwObjectInstances - 3) * elementSize;

		// Changes
		Address_CStreaming__Init2_18E9A8_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18E9A8));
		Address_CStreaming__Init2_46BE36 = g_mCalc.GetCurrentVAbyPreferedVA(0x46BE36);
		Address_CStreaming__Init2_46BE78_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x46BE78));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x46BE20),
			(void*)&patch_CStreaming__Init2_46BE20
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_RwObjectInstancesLimit = iRwObjectInstances;

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of DYNAMIC LIMITS: rwObjectInstances to: %d", iRwObjectInstances);
	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
namespace Game_GTASA
{
	extern "C"
	{
		uint32_t sizeofMatriceMultipliedByCountOfMatrices = 0;

		uint32_t numberOfMatrices = 0;
		uint32_t numberOfMatricesMinusTwo = 0;
	}

	// patch for 0x408AD4
	extern "C"
	{
		uintptr_t Address_CPlaceable__InitMatrixArray_18E9A8_arm = 0;
		uintptr_t Address_CPlaceable__InitMatrixArray_408AEA_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPlaceable__InitMatrixArray_408AD4()
	{
		__asm(
			".thumb\n"			
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, sizeofMatriceMultipliedByCountOfMatrices)
			"ADD R0, R5, #8\n"
			"BL 1f\n"
			"MOVS R1, #0x54\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, numberOfMatrices)
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPlaceable__InitMatrixArray_408AEA_thumb)

			// Branches
			"1:\n"	// _Znaj
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPlaceable__InitMatrixArray_18E9A8_arm)
			);
	}

	// patch for 0x408B66
	extern "C"
	{
		uintptr_t Address_CPlaceable__InitMatrixArray_408B70_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CPlaceable__InitMatrixArray_408B66()
	{
		__asm(
			".thumb\n"
			"STR LR, [R2,#0x1A0]\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, numberOfMatricesMinusTwo)
			"LDR R3, [R3]\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CPlaceable__InitMatrixArray_408B70_thumb)
			);
	}
}
#endif

// Matrices
void DynamicLimits::SetMatrices(unsigned int iMatrices)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iMatrices = this->ms_MatricesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		CPatch::PatchUINT32(0x54F3A0 + 1, iMatrices);
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		// Set variables
		const int elementSize = 0x54;

		sizeofMatriceMultipliedByCountOfMatrices = iMatrices * elementSize;
		numberOfMatrices = iMatrices;
		numberOfMatricesMinusTwo = iMatrices - 2;

		// Changes
		Address_CPlaceable__InitMatrixArray_18E9A8_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18E9A8));
		Address_CPlaceable__InitMatrixArray_408AEA_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x408AEA));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x408AD4),
			(void*)&patch_CPlaceable__InitMatrixArray_408AD4
		);

		Address_CPlaceable__InitMatrixArray_408B70_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x408B70));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x408B66),
			(void*)&patch_CPlaceable__InitMatrixArray_408B66
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_MatricesLimit = iMatrices;

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of DYNAMIC LIMITS: Matrices to: %d", iMatrices);
	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// InteriorInst
void DynamicLimits::SetInteriorInst(unsigned int iInteriorInst)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iInteriorInst = this->ms_InteriorInstLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xA3E6F8 + 1), iInteriorInst);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x9163D8 + 1), iInteriorInst);	
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_InteriorInstLimit = iInteriorInst;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: InteriorInst to: %d",
		iInteriorInst
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// PortalInst
void DynamicLimits::SetPortalInst(unsigned int iPortalInst)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPortalInst = this->ms_PortalInstLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xB59F98 + 1), iPortalInst);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xA66F08 + 1), iPortalInst);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_PortalInstLimit = iPortalInst;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: PortalInst to: %d",
		iPortalInst
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// CAnimBlender
void DynamicLimits::SetCAnimBlender(unsigned int iCAnimBlender)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iCAnimBlender = this->ms_CAnimBlenderLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x9ED948 + 1), iCAnimBlender);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8E1E48 + 1), iCAnimBlender);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_CAnimBlenderLimit = iCAnimBlender;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: CAnimBlender to: %d",
		iCAnimBlender
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// CAtdNodeAnimChangePooledObject
void DynamicLimits::SetCAtdNodeAnimChangePooledObject(unsigned int iCAtdNodeAnimChangePooledObject)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iCAtdNodeAnimChangePooledObject = this->ms_CAtdNodeAnimChangePooledObjectLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x9ED9C5 + 1), iCAtdNodeAnimChangePooledObject);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8E1EC5 + 1), iCAtdNodeAnimChangePooledObject);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_CAtdNodeAnimChangePooledObjectLimit = iCAtdNodeAnimChangePooledObject;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: CAtdNodeAnimChangePooledObject to: %d",
		iCAtdNodeAnimChangePooledObject
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// CAtdNodeAnimPlayer
void DynamicLimits::SetCAtdNodeAnimPlayer(unsigned int iCAtdNodeAnimPlayer)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iCAtdNodeAnimPlayer = this->ms_CAtdNodeAnimPlayerLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x9ED988 + 1), iCAtdNodeAnimPlayer);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8E1E88 + 1), iCAtdNodeAnimPlayer);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_CAtdNodeAnimPlayerLimit = iCAtdNodeAnimPlayer;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: CAtdNodeAnimPlayer to: %d",
		iCAtdNodeAnimPlayer
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// crFrameFilterBoneMask
void DynamicLimits::SetcrFrameFilterBoneMask(unsigned int icrFrameFilterBoneMask)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		icrFrameFilterBoneMask = this->ms_crFrameFilterBoneMaskLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x9EDA05 + 1), icrFrameFilterBoneMask);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8E1F05 + 1), icrFrameFilterBoneMask);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_crFrameFilterBoneMaskLimit = icrFrameFilterBoneMask;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: crFrameFilterBoneMask to: %d",
		icrFrameFilterBoneMask
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// crFrameFilterBoneAnalogue
void DynamicLimits::SetcrFrameFilterBoneAnalogue(unsigned int icrFrameFilterBoneAnalogue)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		icrFrameFilterBoneAnalogue = this->ms_crFrameFilterBoneAnalogueLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x9EDA45 + 1), icrFrameFilterBoneAnalogue);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8E1F45 + 1), icrFrameFilterBoneAnalogue);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_crFrameFilterBoneAnalogueLimit = icrFrameFilterBoneAnalogue;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: crFrameFilterBoneAnalogue to: %d",
		icrFrameFilterBoneAnalogue
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// crExpressionProcessor
void DynamicLimits::SetcrExpressionProcessor(unsigned int icrExpressionProcessor)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		icrExpressionProcessor = this->ms_crExpressionProcessorLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x9EDA85 + 1), icrExpressionProcessor);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8E1F85 + 1), icrExpressionProcessor);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_crExpressionProcessorLimit = icrExpressionProcessor;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: crExpressionProcessor to: %d",
		icrExpressionProcessor
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// crmtObserver
void DynamicLimits::SetcrmtObserver(unsigned int icrmtObserver)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		icrmtObserver = this->ms_crmtObserverLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x9EDAC5 + 1), icrmtObserver);
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x8E1FC5 + 1), icrmtObserver);	
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_crmtObserverLimit = icrmtObserver;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: crmtObserver to: %d",
		icrmtObserver
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// NavMeshRoute
void DynamicLimits::SetNavMeshRoute(unsigned int iNavMeshRoute)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iNavMeshRoute = this->ms_NavMeshRouteLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
		if (iNavMeshRoute > 255)
			throw f92_runtime_error("Currently, NavMeshRoute limit can't be more than 255.");

		if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0xC75D68 + 1), iNavMeshRoute);
		else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0xC8AC48 + 1), iNavMeshRoute);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_NavMeshRouteLimit = iNavMeshRoute;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: NavMeshRoute to: %d",
		iNavMeshRoute
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Cam
void DynamicLimits::SetCam(unsigned int iCam)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iCam = this->ms_CamLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
		if (iCam > 255)
			throw f92_runtime_error("Currently, Cam limit can't be more than 255.");

		if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0x9AD498 + 1), iCam);
		else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0x9DF078 + 1), iCam);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_CamLimit = iCam;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: Cam to: %d",
		iCam
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// ExplosionType
void DynamicLimits::SetExplosionType(unsigned int iExplosionType)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iExplosionType = this->ms_ExplosionTypeLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
		if (iExplosionType > 255)
			throw f92_runtime_error("Currently, ExplosionType limit can't be more than 255.");

		if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0xC75988 + 1), iExplosionType);
		else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			CPatch::PatchUINT8(g_mCalc.GetCurrentVAbyPreferedVA(0xC803D8 + 1), iExplosionType);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_ExplosionTypeLimit = iExplosionType;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: ExplosionType to: %d",
		iExplosionType
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Reach driver
void DynamicLimits::SetReachDriver(unsigned int iReachDriver)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iReachDriver = this->ms_ReachDriverLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x44D5CA + 1), iReachDriver);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_ReachDriverLimit = iReachDriver;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: Reach driver to: %d",
		iReachDriver
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Prop anim
void DynamicLimits::SetPropAnim(unsigned int iPropAnim)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPropAnim = this->ms_PropAnimLimit;

		MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
		CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0x44D74A + 3), iPropAnim);
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_PropAnimLimit = iPropAnim;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of DYNAMIC LIMITS: Prop anim to: %d",
		iPropAnim
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Initialize
void DynamicLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();
	
	this->sizeof_CPed = 0;
	this->sizeof_CVehicle = 0;

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		this->sizeof_CPed = 1988;
		this->sizeof_CVehicle = 2584;

		// Number of vehicle structs limit
		this->ms_VehicleStructsLimit = 50;

		// Number of collision models	 
		this->ms_ColModelsLimit = 10150;

		// Number of matrices
		if(CGameVersion::Is_GTA_SA_Android_Renderware(gameVersion))
			this->ms_RwObjectInstancesLimit = 1500;
		else
			this->ms_RwObjectInstancesLimit = 1000;

		// Number of matrices
		this->ms_MatricesLimit = 900;

		// Number of PtrNode Singles
		if (CGameVersion::Is_GTA_SA_Android_Renderware(gameVersion))
			this->ms_PtrNodeSinglesLimit = 75000;
		else
			this->ms_PtrNodeSinglesLimit = 70000;

		// Number of PtrNode Doubles;
		if (CGameVersion::Is_GTA_SA_Android_Renderware(gameVersion))
			this->ms_PtrNodeDoublesLimit = 6000;
		else
			this->ms_PtrNodeDoublesLimit = 3200;

		// Number of EntryInfoNodes
		this->ms_EntryInfoNodesLimit = 500;

		// Number of Peds
		this->ms_PedsLimit = 140;

		// Number of vehicles
		this->ms_VehiclesLimit = 110;

		// Number of objects
		this->ms_ObjectsLimit = 350;

		// Number of tasks
		this->ms_TasksLimit = 500;

		// Number of events
		this->ms_EventsLimit = 200;

		// Number of PointRoute
		this->ms_PointRouteLimit = 64;

		// Number of PatrolRoute
		this->ms_PatrolRouteLimit = 32;

		// Number of NodeRoute
		this->ms_NodeRouteLimit = 64;

		// Number of TaskAllocator
		this->ms_TaskAllocatorLimit = 16;

		// Number of PedIntelligence
		this->ms_PedIntelligenceLimit = 140;

		// Number of PedAttractors
		this->ms_PedAttractorsLimit = 64;

		// Number of QuadTreeNodes
		this->ms_QuadTreeNodesLimit = 400;

		// Number of collision links
		this->ms_CollisionLinksLimit = 50;

		// Limit of CustomEnvMapPipeMatDataPool
		this->ms_CustomEnvMapPipeMatDataPoolLimit = 4096;

		// Limit of CustomEnvMapPipeAtmDataPool
		this->ms_CustomEnvMapPipeAtmDataPoolLimit = 1024;

		// Limit of CustomSpecMapPipeMaterialDataPool
		this->ms_CustomSpecMapPipeMaterialDataPoolLimit = 4096;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				// COL model pool
				CPools__ms_pColModelPool.gtasa = (CPool_GTASA<Game_GTASA::CColModel>**)0xB744A4;

				// Vehicles pool
				CPools__ms_pVehiclePool.gtasa = (CPool_GTASA<Game_GTASA::CVehicle>**)0xB74494;

				// Replay pool conversions
				CReplay__m_PedPoolConversion.ptr = (int32_t*)0x97F838;
				CReplay__m_VehiclePoolConversion.ptr = (int32_t*)0x97F680;

				// Buildings pool
				CPools__ms_pBuildingPool.gta_sa = (CPool_GTASA<CBuilding_generic>**)0xB74498;

				// Dummy pool
				CPools__ms_pDummyPool.gta_sa = (CPool_GTASA<CDummy_generic>**)0xB744A0;
			}
			#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
			{
				DynamicLimits_address_operator_new_array = (uintptr_t)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_Znaj"
				);
			}
			#endif
		}
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
	{
		// Number of vehicle structs limit
		this->ms_VehicleStructsLimit = 50;

		// Number of PtrNode Singles
		this->ms_PtrNodeSinglesLimit = 80000;

		// Number of PtrNode Doubles;
		this->ms_PtrNodeDoublesLimit = 16000;

		// Number of EntryInfoNodes
		this->ms_EntryInfoNodesLimit = 16000;

		// Number of vehicles
		this->ms_VehiclesLimit = 140;

		// Number of objects
		this->ms_ObjectsLimit = 1300;

		// Number of InteriorInst
		this->ms_InteriorInstLimit = 1000;

		// Number of PortalInst
		this->ms_PortalInstLimit = 500;

		// Number of CAnimBlender
		this->ms_CAnimBlenderLimit = 300;

		// Number of CAtdNodeAnimChangePooledObject
		this->ms_CAtdNodeAnimChangePooledObjectLimit = 3000;

		// Number of CAtdNodeAnimPlayer
		this->ms_CAtdNodeAnimPlayerLimit = 1500;

		// Number of crFrameFilterBoneMask
		this->ms_crFrameFilterBoneMaskLimit = 1800;

		// Number of crFrameFilterBoneAnalogue
		this->ms_crFrameFilterBoneAnalogueLimit = 1500;

		// Number of crExpressionProcessor
		this->ms_crExpressionProcessorLimit = 1500;

		// Number of crmtObserver
		this->ms_crmtObserverLimit = 1500;

		// Number of tasks
		this->ms_TasksLimit = 1200;

		// Number of CDummyTask
		this->ms_CDummyTaskLimit = 300;

		// Number of events
		this->ms_EventsLimit = 300;

		// Number of PointRoute
		this->ms_PointRouteLimit = 256;

		// Number of PatrolRoute
		this->ms_PatrolRouteLimit = 32;

		// Number of PedAttractors
		this->ms_PedAttractorsLimit = 64;

		// Number of QuadTreeNodes
		this->ms_QuadTreeNodesLimit = 800;

		// Number of NavMeshRoute
		this->ms_NavMeshRouteLimit = 1;

		// Number of Cam
		this->ms_CamLimit = 60;

		// Number of ExplosionType
		this->ms_ExplosionTypeLimit = 16;
	}
	else if (gameVersion == GAME_VERSION_BULLY_SE_1_2_WIN_X86)
	{
		// Number of collision models	 
		this->ms_ColModelsLimit = 4150;

		// Number of EntryInfoNodes
		this->ms_EntryInfoNodesLimit = 2000;

		// Number of PtrNode
		this->ms_PtrNodesLimit = 15000;

		// Number of Peds
		this->ms_PedsLimit = 24;

		// Number of vehicles
		this->ms_VehiclesLimit = 15;

		// Number of objects
		this->ms_ObjectsLimit = 275;

		// Number of reach driver pool
		this->ms_ReachDriverLimit = 48;

		// Number of prop anim pool
		this->ms_PropAnimLimit = 220;
	}
}

// Shutdown
void DynamicLimits::Shutdown()
{
	if (CReplay__m_PedPoolConversion.bIsAllocated.Get())
		delete[] CReplay__m_PedPoolConversion.ptr;

	if (CReplay__m_VehiclePoolConversion.bIsAllocated.Get())
		delete[] CReplay__m_VehiclePoolConversion.ptr;
}

// Applies enabled limits
void DynamicLimits::ApplyEnabledLimits()
{
}
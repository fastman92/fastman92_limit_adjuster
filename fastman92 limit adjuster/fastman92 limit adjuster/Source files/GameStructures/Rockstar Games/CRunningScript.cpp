/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CRunningScript.h"

#include "../../Core/DynamicAssert.h"
#include "../../Core/LimitAdjuster.h"

using namespace Game;

MAKE_CRunningScript(CRunningScript, STRUCTURE_STATIC_MEMBER_DEFINITION);

CRunningScript_VarInitialisation g_CEntity_VarInitialisation;

// Initialize
void CRunningScript_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	unsigned int expectedStructureSize = 0;

	MAKE_DEAD_IF();
	#ifdef IS_ARCHITECTURE_32_BIT
	else if (CGameVersion::IsAny_GTA_III(gameVersion)
		|| CGameVersion::IsAny_GTA_VC(gameVersion))
	{
		g_StructAllocator.InitPerStruct();

		g_StructAllocator.Allocate(CRunningScript::m_pNext);
		g_StructAllocator.Allocate(CRunningScript::m_pPrev);
		g_StructAllocator.Allocate(CRunningScript::m_szName);
		g_StructAllocator.Allocate(CRunningScript::m_nIp);
		g_StructAllocator.Allocate(CRunningScript::m_apStack, 6);
		g_StructAllocator.Allocate(CRunningScript::m_nSP);
		g_StructAllocator.Allocate(CRunningScript::m_aLocalVars, 18);

		if (CGameVersion::IsAny_GTA_III(gameVersion))
		{
			g_StructAllocator.Allocate(CRunningScript::m_bCondResult);
			g_StructAllocator.Allocate(CRunningScript::m_bUseMissionCleanup);
			g_StructAllocator.Allocate(CRunningScript::m_bIsActive);
		}
		else
		{
			g_StructAllocator.Allocate(CRunningScript::m_bIsActive);
			g_StructAllocator.Allocate(CRunningScript::m_bCondResult);
			g_StructAllocator.Allocate(CRunningScript::m_bUseMissionCleanup);			
		}

		g_StructAllocator.Allocate(CRunningScript::m_bAwake);
		g_StructAllocator.Allocate(CRunningScript::m_nWakeTime);
		g_StructAllocator.Allocate(CRunningScript::m_nLogicalOp);
		g_StructAllocator.Allocate(CRunningScript::m_bNotFlag);
		g_StructAllocator.Allocate(CRunningScript::m_bWastedBustedCheck);
		g_StructAllocator.Allocate(CRunningScript::m_bWastedOrBusted);
		g_StructAllocator.Allocate(CRunningScript::m_bIsMission);
		g_StructAllocator.Allocate(CRunningScript::endOfStructure);		

		expectedStructureSize = 0x88;
	}
	else if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		g_StructAllocator.InitPerStruct();

		g_StructAllocator.Allocate(CRunningScript::m_pNext);
		g_StructAllocator.Allocate(CRunningScript::m_pPrev);
		g_StructAllocator.Allocate(CRunningScript::m_szName);
		g_StructAllocator.Allocate(CRunningScript::m_pBaseIP);
		g_StructAllocator.Allocate(CRunningScript::m_pCurrentIP);
		g_StructAllocator.Allocate(CRunningScript::m_apStack, 8);
		g_StructAllocator.Allocate(CRunningScript::m_nSP);
		
		g_StructAllocator.Allocate(CRunningScript::m_aLocalVars,
			#ifdef IS_PLATFORM_ANDROID
			42
			#else
			34
			#endif
		);

		g_StructAllocator.Allocate(CRunningScript::m_bIsActive);
		g_StructAllocator.Allocate(CRunningScript::m_bCondResult);
		g_StructAllocator.Allocate(CRunningScript::m_bUseMissionCleanup);
		g_StructAllocator.Allocate(CRunningScript::m_bIsExternal);
		g_StructAllocator.Allocate(CRunningScript::m_bTextBlockOverride);
		g_StructAllocator.Allocate(CRunningScript::m_nWakeTime);
		g_StructAllocator.Allocate(CRunningScript::m_nLogicalOp);
		g_StructAllocator.Allocate(CRunningScript::m_bNotFlag);
		g_StructAllocator.Allocate(CRunningScript::m_bWastedBustedCheck);
		g_StructAllocator.Allocate(CRunningScript::m_bWastedOrBusted);
		g_StructAllocator.Allocate(CRunningScript::m_pSceneSkipIP);

		g_StructAllocator.SetAlignment(1);
		g_StructAllocator.Allocate(CRunningScript::m_bIsMission);		
		g_StructAllocator.Allocate(CRunningScript::m_CLEO_scmFunction);
		g_StructAllocator.Allocate(CRunningScript::m_bCLEO_isCustom);
		g_StructAllocator.Allocate(CRunningScript::endOfStructure);

		#ifdef IS_PLATFORM_ANDROID
		expectedStructureSize = 0x100;
		#else
		expectedStructureSize = 0xE0;
		#endif
	}	
	else if (CGameVersion::IsAny_GTA_LCS(gameVersion))
	{
		g_StructAllocator.InitPerStruct();

		g_StructAllocator.Allocate(CRunningScript::m_pNext);
		g_StructAllocator.Allocate(CRunningScript::m_pPrev);
		g_StructAllocator.Allocate(CRunningScript::m_nScriptID);
		g_StructAllocator.SkipBytes(4);	// unknown 4 bytes
		g_StructAllocator.Allocate(CRunningScript::m_szName);
		g_StructAllocator.Allocate(CRunningScript::m_nIp);
		g_StructAllocator.Allocate(CRunningScript::m_apStack, 16);
		g_StructAllocator.Allocate(CRunningScript::m_nSP);
		g_StructAllocator.Allocate(CRunningScript::m_aLocalVars, 106);
		g_StructAllocator.Allocate(CRunningScript::m_nFirstLocalVarIndexForCurrentScope);
		g_StructAllocator.Allocate(CRunningScript::m_bIsActive);
		g_StructAllocator.Allocate(CRunningScript::m_bCondResult);
		g_StructAllocator.Allocate(CRunningScript::m_bUseMissionCleanup);
		g_StructAllocator.Allocate(CRunningScript::m_bAwake);
		g_StructAllocator.Allocate(CRunningScript::m_nWakeTime);
		g_StructAllocator.Allocate(CRunningScript::m_nLogicalOp);
		g_StructAllocator.Allocate(CRunningScript::m_bNotFlag);
		g_StructAllocator.Allocate(CRunningScript::m_bWastedBustedCheck);
		g_StructAllocator.Allocate(CRunningScript::m_bWastedOrBusted);
		g_StructAllocator.Allocate(CRunningScript::m_bIsMission);

		expectedStructureSize = 0x21C;

		g_StructAllocator.Allocate(CRunningScript::endOfStructure);
	}
	else if (CGameVersion::IsAny_GTA_VCS(gameVersion))
	{
		g_StructAllocator.InitPerStruct();

		g_StructAllocator.Allocate(CRunningScript::m_pNext);
		g_StructAllocator.Allocate(CRunningScript::m_pPrev);
		g_StructAllocator.Allocate(CRunningScript::m_nScriptID);
		g_StructAllocator.SkipBytes(4);	// unknown 4 bytes		
		g_StructAllocator.Allocate(CRunningScript::m_nIp);
		g_StructAllocator.Allocate(CRunningScript::m_apStack, 16);
		g_StructAllocator.Allocate(CRunningScript::m_aLocalVars, 106);
		g_StructAllocator.Allocate(CRunningScript::m_nFirstLocalVarIndexForCurrentScope);
		g_StructAllocator.Allocate(CRunningScript::m_nWakeTime);
		g_StructAllocator.Allocate(CRunningScript::m_nSP);
		g_StructAllocator.Allocate(CRunningScript::m_nLogicalOp);
		g_StructAllocator.Allocate(CRunningScript::m_bIsActive);
		g_StructAllocator.Allocate(CRunningScript::m_bCondResult);
		g_StructAllocator.Allocate(CRunningScript::m_bUseMissionCleanup);
		g_StructAllocator.Allocate(CRunningScript::m_bAwake);		
		g_StructAllocator.Allocate(CRunningScript::m_bNotFlag);
		g_StructAllocator.Allocate(CRunningScript::m_bWastedBustedCheck);
		g_StructAllocator.Allocate(CRunningScript::m_bWastedOrBusted);
		g_StructAllocator.Allocate(CRunningScript::m_szName);
		g_StructAllocator.Allocate(CRunningScript::m_bIsMission);

		expectedStructureSize = 0x218;

		g_StructAllocator.Allocate(CRunningScript::endOfStructure);
	}
	#endif
	
	if (expectedStructureSize != 0)
		FLA_dynamic_assert(
			TypeDetails::SizeOf<CRunningScript>() == expectedStructureSize,
			"Size of CRunningScript is invalid!"
		);
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
#if 0

	// Initializes member variables.
	void CRunningScript::Init()
	{
		((void (__thiscall*)(CRunningScript*)) FUNC_CRunningScript__Init )(this);	
	}

	// Processes one command
	char CRunningScript::ProcessOneCommand()
	{
		 return ((char (__thiscall*)(CRunningScript*)) FUNC_CRunningScript__ProcessOneCommand )(this);
	}

	// Reads array offset and value from array index variable.
	void CRunningScript::GetArrayOffsetAndValueOfIndexVariable(int16_t *pOffset, __int32 *pIdx)
	{
		((void (__thiscall*)(CRunningScript*, int16_t*, __int32*)) FUNC_CRunningScript__GetArrayOffsetAndValueOfIndexVariable )(this, pOffset, pIdx);	
	}

	// Returns offset of global variable
	int16_t CRunningScript::GetOffsetOfGlobalVariable()
	{
		return ((int16_t (__thiscall*)(CRunningScript*)) FUNC_CRunningScript__GetOffsetOfGlobalVariable )(this);
	}

	// Returns pointer to script variable of any type.
	tScriptVarValue* CRunningScript::GetPointerToScriptVariable(unsigned char variableType)
	{
		return ((tScriptVarValue* (__thiscall*)(CRunningScript*, unsigned char)) FUNC_CRunningScript__GetPointerToScriptVariable )(this, variableType);
	}

	// Returns condition result
	inline bool CRunningScript::GetConditionResult()
	{
		return this -> condResult;
	}

	// Returns pointer to local variable pointed by offset and array index as well as multiplier.
	void CRunningScript::GetPointerLocalVariableByArrayIndex(int16_t off, int16_t idx, unsigned char mul)
	{
		((void (__thiscall*)(CRunningScript*, int16_t, int16_t, unsigned char)) FUNC_CRunningScript__GetPointerLocalVariableByArrayIndex )(this, off, idx, mul);
	}

	// Collects parameters
	void CRunningScript::CollectParameters(int16_t count)
	{
		((void (__thiscall*)(CRunningScript*, int16_t)) FUNC_CRunningScript__CollectParameters )(this, count);
	}

	// Collects parameter and returns it.
	tScriptVarValue CRunningScript::CollectNextParameterWithoutIncreasingPC()
	{
		tScriptVarValue value;

		__asm
		{
			mov eax, FUNC_CRunningScript__CollectNextParameterWithoutIncreasingPC
			mov ecx, this
			call eax
			mov value, eax
		}
		return value;
	}

	// Collects string parameter
	void CRunningScript::CollectStringParameter(char *pBuffer, unsigned char nBufferLength)
	{
		((void (__thiscall*)(CRunningScript*, char *, unsigned char)) FUNC_CRunningScript__CollectStringParameter )(this, pBuffer, nBufferLength);
	}

	// Stores parameters
	void CRunningScript::StoreParameters(int16_t count)
	{
		((void (__thiscall*)(CRunningScript*, int16_t)) FUNC_CRunningScript__StoreParameters )(this, count);
	}

	// Collects parameters and puts them to local variables of new script
	void CRunningScript::CollectParametersToNewScript(CRunningScript* pNewScript)
	{
		((void (__thiscall*)(CRunningScript*, CRunningScript*)) FUNC_CRunningScript__CollectParametersToNewScript )(this, pNewScript);
	}

	// Sets instruction pointer, used in GOTO-like commands
	void CRunningScript::SetIntructionPointer(__int32 newIP)
	{
		((void (__thiscall*)(CRunningScript*, __int32)) FUNC_CRunningScript__SetIntructionPointer )(this, newIP);
	}

	// Updates comparement flag, used in conditional commands
	void CRunningScript::UpdateCompareFlag(bool state)
	{
		((void (__thiscall*)(CRunningScript*, bool)) FUNC_CRunningScript__UpdateCompareFlag )(this, state);
	}

	// Terminates a script
	void CRunningScript::TerminateThisScript()
	{
		((void (__thiscall*)(CRunningScript*)) FUNC_CRunningScript__TerminateThisScript )(this);
	}

	// Performs death arrest check
	void CRunningScript::DoDeatharrestCheck()
	{
		((void (__thiscall*)(CRunningScript*)) FUNC_CRunningScript__DoDeatharrestCheck )(this);
	}

	// Processes running script
	void CRunningScript::Process()
	{
		((void (__thiscall*)(CRunningScript*)) FUNC_CRunningScript__Process )(this);
	}

	// Adds script to list
	void CRunningScript::AddScriptToList(CRunningScript ** list)
	{
		((void (__thiscall*)(CRunningScript*, CRunningScript **)) FUNC_CRunningScript__AddScriptToList )(this, list);
	}

	// Removes script from list
	void CRunningScript::RemoveScriptFromList(CRunningScript ** list)
	{
		((void (__thiscall*)(CRunningScript*, CRunningScript **)) FUNC_CRunningScript__RemoveScriptFromList )(this, list);
	}

	// Returns state of pad button.
	short CRunningScript::GetPadState(unsigned short playerIndex, unsigned short buttonID)
	{
		return ((short (__thiscall*)(CRunningScript*, unsigned short, unsigned short)) FUNC_CRunningScript__GetPadState )(this, playerIndex, buttonID);
	}

	// Command handlers
	char CRunningScript::ProcessCommands_0To99(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_0To99 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_100To199(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_100To199 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_200To299(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_200To299 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_300To399(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_300To399 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_400To499(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_400To499 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_500To599(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_500To599 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_600To699(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_600To699 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_700To799(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_700To799 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_800To899(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_800To899 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_900To999(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_900To999 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_1000To1099(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_1000To1099 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_1100To1199(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_1100To1199 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_1200To1299(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_1200To1299 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_1300To1399(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_1300To1399 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_1400To1499(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_1400To1499 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_1500To1599(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_1500To1599 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_1600To1699(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_1600To1699 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_1700To1799(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_1700To1799 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_1800To1899(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_1800To1899 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_1900To1999(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_1900To1999 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_2000To2099(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_2000To2099 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_2100To2199(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_2100To2199 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_2200To2299(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_2200To2299 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_2300To2399(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_2300To2399 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_2400To2499(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_2400To2499 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_2500To2599(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_2500To2599 )(this, commandID);
	}

	char CRunningScript::ProcessCommands_2600To2699(eCommandName commandID)
	{
		return ((char (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ProcessCommands_2600To2699 )(this, commandID);
	}

	// Checks if damage ID is valid to expected damage weapon ID.
	bool CRunningScript::CheckDamagedWeaponType(int damageWeaponID, int expectedDamageWeaponID)
	{
		return ((bool (__cdecl*)(int, int)) FUNC_CRunningScript__CheckDamagedWeaponType )(damageWeaponID, expectedDamageWeaponID);
	}

	// Processes commands that check if car is in specified area.
	void CRunningScript::CarInAreaCheckCommand(eCommandName commandID)
	{
		((void (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__CarInAreaCheckCommand )(this, commandID);
	}

	// Processes commands that check if char is in specified area.
	void CRunningScript::CharInAreaCheckCommand(eCommandName commandID)
	{
		((void (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__CharInAreaCheckCommand )(this, commandID);
	}

	// Processes commands that locate a vehicle
	void CRunningScript::LocateCarCommand(eCommandName commandID)
	{
		((void (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__LocateCarCommand )(this, commandID);
	}

	// Processes commands where char locates car
	void CRunningScript::LocateCharCarCommand(eCommandName commandID)
	{
		((void (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__LocateCharCarCommand )(this, commandID);
	}

	// Processes commands where char locates another char
	void CRunningScript::LocateCharCharCommand(eCommandName commandID)
	{
		((void (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__LocateCharCharCommand )(this, commandID);
	}

	// Processes commands where char locates map point
	void CRunningScript::LocateCharCommand(eCommandName commandID)
	{
		((void (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__LocateCharCommand )(this, commandID);
	}

	// Processes commands where char locates object
	void CRunningScript::LocateCharObjectCommand(eCommandName commandID)
	{
		((void (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__LocateCharObjectCommand )(this, commandID);
	}

	// Processes commands where object locates map point
	void CRunningScript::LocateObjectCommand(eCommandName commandID)
	{
		((void (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__LocateObjectCommand )(this, commandID);
	}

	// Processes commands that check if object is in area
	void CRunningScript::ObjectInAreaCheckCommand(eCommandName commandID)
	{
		((void (__thiscall*)(CRunningScript*, eCommandName)) FUNC_CRunningScript__ObjectInAreaCheckCommand )(this, commandID);
	}

	// Checks if ped type conforms to valid ped types.
	bool CRunningScript::ThisIsAValidRandomPed(ePedType pedType, bool civilian, bool gang, bool criminal)
	{
		return ((bool (__thiscall*)(CRunningScript*, ePedType, bool, bool, bool)) FUNC_CRunningScript__ThisIsAValidRandomPed )(this, pedType, civilian, gang, criminal);
	}
#endif
}
#endif
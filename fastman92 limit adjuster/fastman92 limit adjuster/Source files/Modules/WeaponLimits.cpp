/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "WeaponLimits.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/CEntity.h"
#include "../GameStructures/Rockstar Games/CFileMgr.h"

#include "ErrorReporting.h"
#include "FileIDlimit.h"

#include <Array\countof.h>
#include <fileIO.h>
#include <StrLexStuff.h>

#pragma warning(disable:4733)

using namespace Game;

WeaponLimits g_weaponLimits;

static bool bBinocularVisionGoggles = false;

// Returns pointer to weapon type info
const tWeaponTypeInfo* GetWeaponTypeInfo(int weaponType)
{
	return g_weaponLimits.WeaponTypes + weaponType;
}

// Returns skill stat index
int __cdecl CWeaponInfo_generic::GetSkillStatIndex(signed int weaponType)
{
	tWeaponTypeInfo* pInfo = g_weaponLimits.WeaponTypes + weaponType;

	return pInfo->statIndex;
}

// Finds weapon type by name
int __cdecl CWeaponInfo_generic::FindWeaponType(const char *weaponName)
{
	for (unsigned int weaponType = 0; weaponType < g_weaponLimits.NumberOfWeaponTypes; weaponType++)
	{
		tWeaponTypeInfo* pInfo = g_weaponLimits.WeaponTypes + weaponType;

		if (pInfo->Subset == WEAPON_SUBSET_UNUSED)
			continue;

		if (!_stricmp(pInfo->Name, weaponName))
			return weaponType;
	}

	return -1;
}

// Finds first free weapon type
int CWeaponInfo_generic::FindFirstFreeWeaponType()
{
	for (unsigned int weaponType = 0; weaponType < g_weaponLimits.NumberOfWeaponTypes; weaponType++)
	{
		tWeaponTypeInfo* pInfo = g_weaponLimits.WeaponTypes + weaponType;

		if (pInfo->Subset == WEAPON_SUBSET_UNUSED)
			return weaponType;
	}

	return -1;
}

// Returns weapon info
CWeaponInfo_generic* __cdecl CWeaponInfo_generic::GetWeaponInfo(int weaponType, char skill)
{
	int index = GetWeaponInfoIndex(weaponType, skill);

	if (index != -1)
		return g_weaponLimits.aWeaponInfo.gta_sa + index;
	else
		return NULL;
}

// Returns weapon info
tWeaponTypeInfo* CWeaponInfo_generic::GetWeaponTypeInfo(int weaponType)
{
	return g_weaponLimits.WeaponTypes + weaponType;
}

// Is weapon type subset multiple skills
eWeaponSubsetType CWeaponInfo_generic::GetWeaponInfoSubset(int weaponType)
{
	return g_weaponLimits.WeaponTypes[weaponType].Subset;
}

// Returns true if it's user operated weapon
bool CWeaponInfo_generic::IsUserOperatedWeapon(int weaponType)
{
	if (weaponType < 0 || weaponType >= g_weaponLimits.NumberOfWeaponTypes)
		return false;

	eWeaponSubsetType subset = GetWeaponInfoSubset(weaponType);

	return subset == WEAPON_SUBSET_ONLY_STANDARD_SKILL || subset == WEAPON_SUBSET_MULTIPLE_SKILLS;
}

// Returns weapon parent type
int CWeaponInfo_generic::GetWeaponHighestParentType(int weaponType)
{
	if (weaponType >= g_weaponLimits.NumberOfWeaponTypes)
		return false;

	tWeaponTypeInfo* pInfo = g_weaponLimits.WeaponTypes + weaponType;

	if (pInfo->Subset == WEAPON_SUBSET_UNUSED)
		return weaponType;

	int resultID = weaponType;

	while (pInfo->ParentWeaponID >= 0)
	{
		resultID = pInfo->ParentWeaponID;
		pInfo = g_weaponLimits.WeaponTypes + resultID;
	}

	return resultID;
}

// Returns weapon parent type until fastman92 type
int CWeaponInfo_generic::GetWeaponParentTypeUntilFastman92(int weaponType)
{
	const WeaponLimits* pWeaponLimits = &g_weaponLimits;

	if (weaponType >= pWeaponLimits->NumberOfWeaponTypes)
		return false;

	tWeaponTypeInfo* pInfo = pWeaponLimits->WeaponTypes + weaponType;

	if (pInfo->Subset == WEAPON_SUBSET_UNUSED)
		return weaponType;

	int resultID = weaponType;

	while (pInfo->ParentWeaponID >= 0)
	{
		resultID = pInfo->ParentWeaponID;

		pInfo = pWeaponLimits->WeaponTypes + resultID;

		if (pInfo->bIsFastman92type)
			break;
	}

	return resultID;
}

// Returns true if weapon parent type is recursive
bool CWeaponInfo_generic::IsWeaponParentTypeRecursive(int weaponType)
{
	if (weaponType >= g_weaponLimits.NumberOfWeaponTypes)
		return false;

	tWeaponTypeInfo* pInfo = g_weaponLimits.WeaponTypes + weaponType;

	if (pInfo->Subset == WEAPON_SUBSET_UNUSED)
		return false;

	int resultID = weaponType;

	while (pInfo->ParentWeaponID >= 0)
	{
		resultID = pInfo->ParentWeaponID;

		if (resultID == weaponType)
			return true;

		pInfo = g_weaponLimits.WeaponTypes + resultID;
	}

	return false;
}

// Returns weapon info index
int CWeaponInfo_generic::GetWeaponInfoIndex(int weaponType, char skill)
{
	MAKE_VAR_GAME_VERSION();

	tWeaponTypeInfo* pInfo = g_weaponLimits.WeaponTypes + weaponType;

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		using namespace Game_GTASA;

		if (skill == WEAPONSKILL_POOR)
			return pInfo->PoorSkillindex;
		else if (skill == WEAPONSKILL_STD)
			return pInfo->StandardSkillIndex;
		else if (skill == WEAPONSKILL_PRO)
			return pInfo->ProffesionalSkillIndex;
		else if (skill == WEAPONSKILL_SPECIAL)
			return pInfo->SpecialSkillIndex;
	}

	return -1;
}

// Accesses weapon ID
unsigned int& CWeapon_generic::AccessWeaponID()
{
	MAKE_VAR_GAME_VERSION();

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
		return ((Game_GTASA::CWeapon*)this)->weaponType;
	else
		return *(unsigned int*)0;
}

// Can be used for second player?
bool __cdecl CWeapon_generic::CanBeUsedFor2Player(int weaponType)
{
	return g_weaponLimits.WeaponTypes[weaponType].bCanBeUsedForSecondPlayer;
}

// Has weapon ammo to be used?
bool CWeapon_generic::HasWeaponAmmoToBeUsed()
{
	bool bHasToBeUsed = g_weaponLimits.WeaponTypes
		[this->AccessWeaponID()].bHasWeaponAmmoToBeUsed;

	if (bHasToBeUsed)
		return true;
	else
	{
		MAKE_VAR_GAME_VERSION();

		if (CGameVersion::IsAny_GTA_SA(gameVersion))
			return ((Game_GTASA::CWeapon*)this)->ammoRemaining != 0;
		else
			return true;
	}
}

namespace Game_GTASA
{
	/*
	// Returns weapon info
	CWeaponInfo* __cdecl CWeaponInfo::GetWeaponInfoForLoading(int weaponType, char skill)
	{
		tWeaponTypeInfo* pInfo = g_weaponLimits.WeaponTypes + weaponType;

		if (pInfo->Subset != WEAPON_SUBSET_MULTIPLE_SKILLS && pInfo->Subset != WEAPON_SUBSET_ONLY_STANDARD_SKILL)
			return NULL;

		if (pInfo->Subset == WEAPON_SUBSET_ONLY_STANDARD_SKILL)
			skill = WEAPONSKILL_STD;

		return GetWeaponInfo(weaponType, skill);
	}
	*/

	// Finds weapon type by name, the weapon type must be found
	int __cdecl FindWeaponWithPossibleWarning(const char *weaponName)
	{
		int ID = CWeaponInfo::FindWeaponType(weaponName);

		if (ID < 0)
			printf_Error(true, "weapon.dat: %s wasn't defined in gtasa_weapon_config.dat", weaponName);

		return ID;
	}

	// Returns wepaon info index
	int GetWeaponInfoIndexWithPossibleError(int weaponType, char skill)
	{
		int weaponInfoIndex = CWeaponInfo::GetWeaponInfoIndex(weaponType, skill);

		if (weaponInfoIndex < 0)
			printf_Error(true, "weapon.dat error, weapon ID %d doesn't have place for skill %d defined.", weaponType, skill);

		return weaponInfoIndex;
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CWeaponInfo__LoadWeaponData_5BE75A()
	{
		__asm
		{
			push ecx;

			push WEAPONSKILL_STD;
			push ebx;
			call GetWeaponInfoIndexWithPossibleError;
			add esp, 8;

			mov edi, eax;
			imul    edi, size CWeaponInfo;

			push 0x5BE760;
			retn;
		}
	}

	NAKED void patch_CWeaponInfo__LoadWeaponData_5BE975()
	{
		__asm
		{
			mov[esp + 120h - 0xB0], ebx;

			push ebx;
			call CWeaponInfo::GetWeaponInfoSubset;
			add esp, 4;

			cmp al, WEAPON_SUBSET_ONLY_STANDARD_SKILL;
			jne TestForMultipleSkills;

			// when standard skill
			mov     edi, 1;
			mov[esp + 120h - 0xF4], edi;
			jmp GetWeaponInfo;

		TestForMultipleSkills:
			cmp al, WEAPON_SUBSET_MULTIPLE_SKILLS;
			jne LoadNextLine;

			mov edi, [esp + 120h - 0xF4];

		GetWeaponInfo:
			push edi;
			push ebx;
			call GetWeaponInfoIndexWithPossibleError;
			add esp, 8;

			mov[esp + 120h - 0x108], eax;

			push 0x5BE9C2;
			retn;

		LoadNextLine:
			push 0x5BEC50;
			retn;
		}

	}


	NAKED void patch_CWeapon__Fire_74245C()
	{
		__asm
		{
			mov     eax, [esi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			add     eax, -16;

			push 0x742461;
			retn;
		}
	}

	NAKED void patch_CWeapon__Fire_74286F()
	{
		__asm
		{
			mov     eax, [esi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			add     eax, -16;

			push 0x742874;
			retn;
		}
	}

	NAKED void patch_CWeapon__Fire_7428E1()
	{
		__asm
		{
			mov     eax, [esi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 40;

			jnz     loc_7428E9;

			push 0x7428E6;
			retn;

		loc_7428E9:
			push 0x7428E9;
			retn;
		}
	}

	NAKED void patch_CWeapon__Fire_7429B3()
	{
		__asm
		{
			mov     eax, [esi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 43;
			jnz     loc_7429C7;

			push 0x7429B8;
			retn;

		loc_7429C7:
			push 0x7429C7;
			retn;
		}
	}

	NAKED void patch_CWeapon__Fire_7429F2()
	{
		__asm
		{
			mov     esi, [esi];

			push esi;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov esi, eax;
			add esp, 4;

			test    esi, esi;
			jz      loc_7429FF;

			push 0x7429F8;
			retn;

		loc_7429FF:
			push 0x7429FF;
			retn;
		}
	}

	NAKED void patch_CWeapon__Fire_7427FE()
	{
		__asm
		{
			mov     eax, [esi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 23;

			jz      loc_74281F;

			push 0x742803;
			retn;

		loc_74281F:
			push 0x74281F;
			retn;
		}
	}

	NAKED void patch_CWeapon__Fire_74281F()
	{
		__asm
		{
			mov     eax, [esi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 39;
			jnz      loc_742867;

			mov     eax, [esi];
			push eax;
			call CWeaponInfo::GetWeaponTypeInfo;
			add esp, 4;
			mov eax, [eax + tWeaponTypeInfo::AssociatedWeaponID];

			push 1;
			push 1;
			push eax;
			mov ecx, edi;

			push part2;
			push 0x5E6080;	// CPed::GiveWeapon
			retn;

		part2:
			mov     eax, [esi];
			push eax;
			mov     ecx, edi;

			push part3;
			push 0x5DF200;	// CPed::GetWeaponSlot
			retn;

		part3:
			imul    eax, 1Ch;
			cmp dword ptr[eax + edi + 5ACh], 1;
			jg      loc_742867;

			mov     eax, [esi];
			push eax;
			call CWeaponInfo::GetWeaponTypeInfo;
			add esp, 4;
			mov eax, [eax + tWeaponTypeInfo::AssociatedWeaponID];

			push eax;
			mov     ecx, edi;

			push part4;
			push 0x5DF200;	// CPed::GetWeaponSlot
			retn;

		part4:
			imul    eax, 1Ch;
			mov[eax + edi + 0x5A4], 0;

			mov     eax, [esi];
			push eax;
			call CWeaponInfo::GetWeaponTypeInfo;
			add esp, 4;
			mov eax, [eax + tWeaponTypeInfo::AssociatedWeaponID];

			push eax;
			mov     ecx, edi;

			push 0x742862;
			retn;

		loc_742867:
			push 0x742867;
			retn;
		}
	}

	NAKED void patch_CWeapon__Fire_7427B0()
	{
		__asm
		{
			mov     eax, [esi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 43;

			jz      loc_7427D7;

			push 0x7427B5;
			retn;

		loc_7427D7:
			push 0x7427D7;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireInstantHit_73FC4E()
	{
		__asm
		{
			mov     ecx, [esi];

			push eax;

			push ecx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov ecx, eax;
			add esp, 4;

			pop eax;

			cmp     ecx, 25;

			push 0x73FC53;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireInstantHit_740C6C()
	{
		__asm
		{
			mov     ecx, [esp + 1B4h - 0x164];
			mov     eax, [ecx];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x740C72;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireInstantHit_740B71()
	{
		__asm
		{
			mov     ecx, [esp + 1B4h - 0x164];
			mov     eax, [ecx];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x740B77;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireInstantHit_740BEA()
	{
		__asm
		{
			mov     ecx, [esp + 1B4h - 0x164];
			mov     eax, [ecx];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 23;

			push 0x740BF1;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireInstantHit_740FBF()
	{
		__asm
		{
			mov     ecx, [esp + 1B4h - 0x164];
			mov     eax, [ecx];

			push edx;
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;
			pop edx;

			cmp     eax, 27;

			push 0x740FC6;
			retn;
		}
	}

	NAKED void patch_CWeapon__Update_73DBA5()
	{
		__asm
		{
			mov     eax, [esi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 27;

			push 0x73DBAA;
			retn;
		}
	}

	NAKED void patch_CWeapon__Update_73DC75()
	{
		__asm
		{
			mov     eax, [esi];

			push eax;
			call CWeaponInfo::IsUserOperatedWeapon;
			add esp, 4;

			test al, al;
			jz loc_73DE9C;

			push 0x73DC7E;
			retn;

		loc_73DE9C:
			push 0x73DE9C;
			retn;
		}
	}

	NAKED void patch_CWeapon__Update_73DEC0()
	{
		__asm
		{
			mov     eax, [esi];

			push ecx;
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;
			pop ecx;

			cmp eax, 18;
			jz      loc_73DB96;

			push 0x73DEC9;
			retn;

		loc_73DB96:
			push 0x73DB96;
			retn;
		}
	}

	NAKED void patch_CWeapon__Update_73DB89()
	{
		__asm
		{
			mov     eax, [esi];

			push ecx;
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;
			pop ecx;

			cmp eax, 18;
			jz      loc_73DB96;

			push 0x73DB8E;
			retn;


		loc_73DB96:
			push 0x73DB96;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireSniper_73AD10()
	{
		__asm
		{
			mov     eax, [ebp + 0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 23;

			push 0x73AD16;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireSniper_73ADD0()
	{
		__asm
		{
			mov     eax, [ebp + 0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 23;

			push 0x73ADD6;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireProjectile_741905()
	{
		__asm
		{
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 16;
			jz      loc_741935;

			cmp     eax, 39;
			jz      loc_741935;

			push 0x74190F;
			retn;

		loc_741935:
			push 0x741935;
			retn;
		}
	}


	void NAKED patch_CProjectileInfo__AddProjectile_737CAC()
	{
		__asm
		{
			mov     edi, [esp + 0C0h + 8];
			mov     ebp, [esp + 0C0h + 4];

			push edi;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			lea     eax, [eax - 10h];

			push 0x737CBD;
			retn;
		}
	}

	void NAKED patch_CProjectileInfo__AddProjectile_737E47()
	{
		__asm
		{
			push edi;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 39;
			jnz     loc_737E5A;

			push 0x737E4C;
			retn;

		loc_737E5A:
			push 0x737E5A;
			retn;
		}
	}

	void NAKED patch_CProjectileInfo__AddProjectile_737F64()
	{
		__asm
		{
			push edi;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 39;

			mov[esp + 0C0h - 0xA6], 5;

			push 0x737F6C;
			retn;
		}
	}

	void NAKED patch_CProjectileInfo__AddProjectile_738086()
	{
		__asm
		{
			push edi;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 19;
			jnz     loc_7380A5;

			push 0x73808B;
			retn;

		loc_7380A5:
			push 0x7380A5;
			retn;
		}
	}

	void NAKED patch_CProjectileInfo__AddProjectile_73839B()
	{
		__asm
		{
			push edi;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			lea     eax, [eax - 10h];
			cmp     eax, 42;

			push 0x7383A1;
			retn;
		}
	}

	void NAKED patch_CProjectileInfo__AddProjectile_73866A()
	{
		__asm
		{
			mov     eax, [eax + 8];
			mov[edx + 8], eax;

			mov ebx, [esp + 0xC8];

			push ecx;
			push ebx;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;
			pop ecx;

			cmp     eax, 19;
			jz      loc_7386DB;

			cmp     eax, 20;
			jz      loc_7386DB;

			cmp     eax, 17;
			jnz     loc_7386DB;

			push 0x738686;
			retn;

		loc_7386DB:
			push 0x7386DB;
			retn;
		}
	}

	void NAKED patch_CProjectileInfo__AddProjectile_738716()
	{
		__asm
		{
			push ebx;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 20;
			jnz     loc_738792;

			push 0x73871B;
			retn;

		loc_738792:
			push 0x738792;
			retn;

		}
	}

	NAKED void patch_CProjectileInfo__Update_738B97()
	{
		__asm
		{
			mov     eax, [ebx];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 39;
			push 0x738B9C;
			retn;
		}
	}

	NAKED void patch_CProjectileInfo__Update_738BFF()
	{
		__asm
		{
			mov     eax, [ebx];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 17;

			jnz     loc_738C63;

			push 0x738C04;
			retn;

		loc_738C63:
			push 0x738C63;
			retn;
		}
	}

	NAKED void patch_CProjectileInfo__Update_738C63()
	{
		__asm
		{
			mov     eax, [ebx];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 19;

			push 0x738C68;
			retn;
		}
	}

	NAKED void patch_CProjectileInfo__Update_738F31()
	{
		__asm
		{
			mov     eax, [ebx];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 39;
			jnz     loc_7390B9;

			push 0x738F3A;
			retn;

		loc_7390B9:
			push 0x7390B9;
			retn;
		}
	}

	NAKED void patch_CProjectileInfo__Update_738F99()
	{
		__asm
		{
			mov     eax, [ebx];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 19;

			push 0x738F9E;
			retn;
		}
	}

	NAKED void patch_CProjectileInfo__IsProjectileInRange_73988C()
	{
		__asm
		{
			mov     eax, [edi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 19;

			push 0x739891;
			retn;
		}
	}

	NAKED void patch_CProjectileInfo__RemoveProjectile_7388F5()
	{
		__asm
		{
			mov     eax, [ebp + 0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 16;

			push 0x7388FB;
			retn;
		}
	}

	NAKED void patch_CProjectileInfo__RemoveProjectile_738877()
	{
		__asm
		{
			mov eax, dword ptr[esi - 20h];

			mov     edi, [ebp + 0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 39;

			push 0x73887E;
			retn;
		}
	}

	NAKED void patch_CProjectileInfo_RemoveNotAdd_737C00()
	{
		__asm
		{
			mov     eax, [esp + 8];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 16;
			push 0x737C07;
			retn;
		}
	}

	NAKED void patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_685B45()
	{
		__asm
		{
			mov eax, [edx + esi + 0x5A0];

			push eax;
			call CWeaponInfo::GetWeaponParentTypeUntilFastman92;
			add esp, 4;

			cmp eax, WEAPONTYPE_BINOCULARS_TYPE;
			je processBinoculars;

			push 0x685B4C;
			retn;

		processBinoculars:

			// mov al, bBinocularVisionGoggles;
			// test al, al;
			// jz step3;

			push    0;
			push    0;
			push    7;
			mov ecx, 0xB6F028;	// TheCamera
			push step2;
			push 0x50BFB0;	// CCamera::SetNewPlayerWeaponMode
			retn;

		step2:
			push    12;
			mov     ecx, esi;

			push step3;
			push 0x5E4500;	// CPed::SetPedState
			retn;

		step3:
			push 0x687294;
			retn;

			// push 0x685AD0;
			// retn;
		}
	}

	NAKED void patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_685AEC()
	{
		__asm
		{
			mov     eax, [ecx + esi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponParentTypeUntilFastman92;
			add esp, 4;

			// cmp eax, WEAPONTYPE_BINOCULARS_TYPE;
			// jne doReturn;

			// mov eax, WEAPONTYPE_SNIPERRIFLE;

		doReturn:
			push 0x685AF3;
			retn;
		}
	}

	NAKED void patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_6861C6()
	{
		__asm
		{
			mov eax, [ecx + esi + 0x5A0];

			push ecx;
			push eax;
			call CWeaponInfo::GetWeaponParentTypeUntilFastman92;
			add esp, 4;
			pop ecx;

			cmp eax, WEAPONTYPE_BINOCULARS_TYPE;
			jne doReturn;

			push 0x6860AD;
			retn;

		doReturn:
			push 0x6861CD;
			retn;
		}
	}

	NAKED void patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_68649B()
	{
		__asm
		{
			mov ecx, [eax + 0x5A0];

			push eax;
			push ecx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov ecx, eax;
			add esp, 4;
			pop eax;

			push 0x6864A1;
			retn;
		}
	}

	NAKED void patch_CTaskSimplePlayerOnFoot__ProcessPed_68883F()
	{
		__asm
		{
			mov eax, [eax + esi + 0x5A0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 9;

			push 0x688847;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireAreaEffect_73EB52()
	{
		__asm
		{
			mov eax, [ebp + 0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 37;
			jnz     loc_73EC1C;

			push 0x73EB5C;
			retn;

		loc_73EC1C:
			push 0x73EC1C;
			retn;
		}
	}

	NAKED void patch_CWeapon__DoWeaponEffect_73E696()
	{
		__asm
		{
			mov     eax, [esi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 37;

			push edi;

			push 0x73E69C;
			retn;
		}
	}

	NAKED void patch_CDarkel__CheckDamagedWeaponType_43D9E9()
	{
		__asm
		{
			mov     ecx, [esp + 8];

			push eax;

			push ecx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov ecx, eax;
			add esp, 4;

			pop eax;

			cmp     ecx, 56;

			push 0x43D9F0;
			retn;
		}
	}

	NAKED void patch_CWeapon__DoBulletImpact_73BA19()
	{
		__asm
		{
			mov     eax, [ecx];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 25;

			push 0x73BA1E;
			retn;
		}
	}

	NAKED void patch_CWeapon__DoBulletImpact_73B71D()
	{
		__asm
		{
			mov     eax, [edx];

			push eax;
			call CWeaponInfo::GetSkillStatIndex;
			add esp, 4;

			test eax, eax;
			jl      loc_73B85B;

			push 0x73B731;
			retn;

		loc_73B85B:
			push 0x73B85B;
			retn;
		}
	}

	NAKED void patch_CWeapon__DoBulletImpact_73BF29()
	{
		__asm
		{
			mov     ebp, [ebp + 0];

			push ebp;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			lea     eax, [eax - 24];

			push 0x73BF2F;
			retn;
		}
	}

	NAKED void patch_CPed__GetWeaponSkill_5E3B60()
	{
		__asm
		{
			push esi;
			mov     esi, [esp + 8];
			push    edi;

			push ecx;
			push esi;
			call CWeaponInfo::GetSkillStatIndex;
			add esp, 4;
			pop ecx;

			test eax, eax;
			jl doReturn;

			push 0x5E3B78;
			retn;

		doReturn:
			push 0x5E3C03;
			retn;
		}
	}

	NAKED void patch_CPed__GetWeaponSkill_5E3BE7()
	{
		__asm
		{
			push eax;
			push ecx;

			push esi;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov esi, eax;
			add esp, 4;

			pop ecx;
			pop eax;

			cmp     esi, 22;
			jnz     loc_5E3BF8;

			push 0x5E3BEC;
			retn;

		loc_5E3BF8:
			push 0x5E3BF8;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireInstantHitFromCar2_73CBF1()
	{
		__asm
		{
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 23;
			jz      loc_73CBFF;

			push 0x73CBF6;
			retn;

		loc_73CBFF:
			push 0x73CBFF;
			retn;
		}
	}

	NAKED void patch_CWeapon__StopWeaponEffect_73B36A()
	{
		__asm
		{
			mov eax, [esi];
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 18;
			jz      loc_73B37B;

			push 0x73B36D;
			retn;

		loc_73B37B:
			push 0x73B37B;
			retn;
		}
	}

	NAKED void patch_CWeapon__AddGunshell_73A4D7()
	{
		__asm
		{
			mov     eax, [edi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 25;
			push 0x73A4DC;
			retn;
		}
	}

	NAKED void patch_CWeapon__GenerateDamageEvent_73A81E()
	{
		__asm
		{
			mov eax, [esp + 78h + 0xC];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x73A826;
			retn;
		}
	}

	NAKED void patch_CWeapon__GenerateDamageEvent_73A704()
	{
		__asm
		{
			push ebx;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 54;
			jnz     loc_73A7ED;

			push 0x73A70D;
			retn;

		loc_73A7ED:
			push 0x73A7ED;
			retn;
		}
	}

	NAKED void patch_CAEWeaponAudioEntity__WeaponReload_5036EB()
	{
		__asm
		{
			mov eax, [esp + 18h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			add eax, -16h;

			push 0x5036F2;
			retn;
		}
	}

	void patch_CAEGlobalWeaponAudioEntity__ProjectileFire_4DF074()
	{
		__asm
		{
			mov     eax, [esp + 10h + 4];

			push edx;
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;
			pop edx;

			cmp     eax, 19;
			push 0x4DF07B;
			retn;
		}
	}

	NAKED void patch_CAEWeaponAudioEntity__WeaponFire_504F8F()
	{
		__asm
		{
			mov     ecx, [esp + 4 + 4];

			push eax;

			push ecx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov ecx, eax;
			add esp, 4;

			pop eax;

			add     ecx, -16h

				push 0x504F96;
			retn;
		}
	}

	NAKED void patch_CPhysical__CanPhysicalBeDamaged_5448BB()
	{
		__asm
		{
			mov     edx, [esp + 4];

			push eax;
			push ecx;

			push edx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov edx, eax;
			add esp, 4;

			pop ecx;
			pop eax;

			cmp     edx, 36h; // switch 55 cases;

			push 0x5448C2;
			retn;
		}
	}


	NAKED void patch_CEventDamage__AffectsPed_4B35FF()
	{
		__asm
		{
			mov eax, dword ptr[esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 53;
			jnz    loc_4B3611;

			push 0x4B3605;
			retn;

		loc_4B3611:
			push 0x4B3611;
			retn;
		}
	}

	NAKED void patch_CEventDamage__AffectsPed_4B363E()
	{
		__asm
		{
			push eax;
			mov eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 16;
			pop eax;

			jl      loc_4B3668;

			push 0x4B3644;
			retn;

		loc_4B3668:
			push 0x4B3668;
			retn;
		}
	}

	NAKED void patch_CEventDamage__AffectsPed_4B368D()
	{
		__asm
		{
			mov     eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 18;
			push 0x4B3693;
			retn;
		}
	}

	NAKED void patch_CEventDamage__AffectsPed_4B36C4()
	{
		__asm
		{
			mov     eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 53;
			push 0x4B36CA;
			retn;
		}
	}

	NAKED void patch_CEventDamage__AffectsPed_4B36F4()
	{
		__asm
		{
			push ecx;
			call CWeaponInfo::IsUserOperatedWeapon;
			add esp, 4;

			test al, al;
			jz loc_4B371B;

			mov     ecx, [esi + 1Ch];
			
			push 1;
			push ecx;
			call CWeaponInfo::GetWeaponInfo;

			push 0x4B36FC;
			retn;

		loc_4B371B:
			push 0x4B371B;
			retn;
		}
	}

	NAKED void patch_CEventDamage__AffectsPed_4B3726()
	{
		__asm
		{
			mov eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 23;
			jnz     loc_4B375E;

			push 0x4B372C;
			retn;

		loc_4B375E:
			push 0x4B375E;
			retn;
		}
	}

	NAKED void patch_CEventDamage__AffectsPed_4B3869()
	{
		__asm
		{
			mov     eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 51;
			jnz     loc_4B35CE;

			push 0x4B3873;
			retn;

		loc_4B35CE:
			push 0x4B35CE;
			retn;
		}
	}

	NAKED void patch_CEventDamage__AffectsPed_4B3885()
	{
		__asm
		{
			setnz   bl;

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 54;
			push 0x4B388B;
			retn;
		}
	}

	NAKED void patch_CWeapon__GenerateDamageEvent_73A6EE()
	{
		__asm
		{
			push ebx;
			call CWeaponInfo::IsUserOperatedWeapon;
			add esp, 4;

			test al, al;
			jz loc_73A704;

			push 1;
			push ebx;
			call CWeaponInfo::GetWeaponInfo;

			push 0x73A6F6;
			retn;

		loc_73A704:
			push 0x73A704;
			retn;
		}
	}

	NAKED void patch_CAutomobile__dmgDrawCarCollidingParticles_6A6DE5()
	{
		__asm
		{
			mov     eax, [esp + 5Ch + 0xC];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			test    eax, eax;

			push 0x6A6DEB;
			retn;
		}
	}

	NAKED void patch_CAutomobile__VehicleDamage_6A7D67()
	{
		__asm
		{
			mov eax, [esp + 70h + 0x18];

			push eax;
			call CWeaponInfo::IsUserOperatedWeapon;
			add esp, 4;

			test al, al;
			jz loc_6A7D80;

			push 0x6A7D71;
			retn;

		loc_6A7D80:
			push 0x6A7D80;
			retn;
		}
	}

	NAKED void patch_CDarkel__RegisterKillByPlayer_43DDD2()
	{
		__asm
		{
			push edx;
			call CWeaponInfo::IsUserOperatedWeapon;
			mov edx, eax;
			add esp, 4;

			cmp     edx, 51;
			jz      loc_43DE05;

			push 0x43DDD7;
			retn;

		loc_43DE05:
			push 0x43DE05;
			retn;
		}
	}

	NAKED void patch_CPedDamageResponseCalculator__ComputeDamageResponse_4B5C35()
	{
		__asm
		{
			mov     eax, [esi + 0Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 4;

			push 0x4B5C3B;
			retn;
		}
	}

	NAKED void patch_CPedDamageResponseCalculator__AccountForPedDamageStats_4AD4A2()
	{
		__asm
		{
			mov     eax, [esi + 0Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 51;

			push 0x4AD4A8;
			retn;
		}
	}

	NAKED void patch_CPedDamageResponseCalculator__AccountForPedDamageStats_4AD517()
	{
		__asm
		{
			mov     eax, [esi + 0Ch];


			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 51;

			push 0x4AD51D;
			retn;
		}
	}

	NAKED void patch_CPedDamageResponseCalculator__AccountForPedArmour_4AD56F()
	{
		__asm
		{
			mov     eax, [esi + 0Ch];


			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 53;

			push 0x4AD575;
			retn;
		}
	}

	NAKED void patch_CPedDamageResponseCalculator__ComputeWillKillPed_4B322E()
	{
		__asm
		{
			mov     eax, [ebp + 0Ch];

			push eax;
			call CWeaponInfo::IsUserOperatedWeapon;
			add esp, 4;

			test al, al;
			jnz      loc_4B339C;

			push 0x4B3238;
			retn;

		loc_4B339C:
			push 0x4B339C;
			retn;
		}
	}

	NAKED void patch_CPedDamageResponseCalculator__ComputeWillKillPed_4B3260()
	{
		__asm
		{
			mov     eax, [ebp + 0Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, ebx;
			push 0x4B3265;
			retn;
		}
	}

	NAKED void patch_CPedDamageResponseCalculator__ComputeWillKillPed_4B3282()
	{
		__asm
		{
			mov     eax, [ebp + 0Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 54;
			jnz     loc_4B32E8;

		loc_4B32E8:
			push 0x4B32E8;
			retn;
		}
	}

	NAKED void patch_CPedDamageResponseCalculator__ComputeWillKillPed_4B3327()
	{
		__asm
		{
			mov eax, dword ptr[ebp + 0Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 53;

			jnz     loc_4B3349;

			push 0x4B332D;
			retn;

		loc_4B3349:
			push 0x4B3349;
			retn;
		}
	}

	NAKED void patch_CHud__DrawCrossHairs_58E1A7()
	{
		__asm
		{
			mov     eax, [edx + edi + 5A0h];

			push ecx;
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;
			pop ecx;

			push 0x58E1AE;
			retn;
		}
	}

	NAKED void patch_CHud__DrawCrossHairs_58E6F9()
	{
		__asm
		{
			mov     edx, [ecx + eax + 5A0h];

			push edx;
			call CWeaponInfo::GetWeaponParentTypeUntilFastman92;
			mov edx, eax;
			add esp, 4;

			cmp edx, WEAPONTYPE_BINOCULARS_TYPE;
			jne doReturn;

			mov edx, WEAPONTYPE_SNIPERRIFLE;

		doReturn:
			push 0x58E700;
			retn;
		}
	}

	NAKED void patch_CHud__DrawCrossHairs_58E6D1()
	{
		__asm
		{
			mov     ecx, [edx + eax + 5A0h];

			push ecx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov ecx, eax;
			add esp, 4;

			push 0x58E6D8;
			retn;
		}
	}

	NAKED void patch_CCam__Process_AimWeapon_521624()
	{
		__asm
		{
			mov     eax, [eax + edi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x52162B;
			retn;
		}
	}

	NAKED void patch_CCam__Process_AimWeapon_521BA1()
	{
		__asm
		{
			mov eax, dword ptr[edx + edi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 42;

			push 0x521BA9;
			retn;
		}
	}

	NAKED void patch_CCam__Process_AimWeapon_522BAA()
	{
		__asm
		{
			mov eax, dword ptr[eax + edi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 41;

			push 0x522BB2;
			retn;
		}
	}

	NAKED void patch_CHud__DrawWeaponAmmo_589407()
	{
		__asm
		{
			push eax;
			mov eax, dword ptr[eax + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 37;
			pop eax;

			jnz     loc_589461;

			push 0x589410;
			retn;

		loc_589461:
			push 0x589461;
			retn;
		}
	}

	NAKED void patch_CHud__DrawWeaponAmmo_589588()
	{
		__asm
		{
			mov     eax, [eax + edi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x58958F;
			retn;
		}
	}

	NAKED void patch_CHud__DrawWeaponAmmo_5895AE()
	{
		__asm
		{
			cmp     eax, 46;
			jz      loc_589642;

			push 1;

			movsx   eax, byte ptr[edi + 718h];
			imul    eax, 1Ch;
			mov     eax, [eax + edi + 5A0h];
			push eax;

			push 0x5895BA;
			retn;

		loc_589642:
			push 0x589642;
			retn;
		}
	}

	NAKED void patch_CPlayerPed__ProcessWeaponSwitch_60D9FA()
	{
		__asm
		{
			mov eax, dword ptr[eax + esi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 38;

			push 0x60DA02;
			retn;
		}
	}

	NAKED void patch_CPlayerPed__ProcessWeaponSwitch_60DA53()
	{
		__asm
		{
			push ecx;

			mov eax, dword ptr[edx + 5A0h];
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 40;
			jnz     loc_60DB5A;

			////////////

			mov eax, dword ptr[esi + 680h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 39;
			jnz     loc_60DB5A;

			pop ecx;

			push 0x60DA6D;
			retn;

		loc_60DB5A:
			pop ecx;

			push 0x60DB5A;
			retn;
		}
	}

	NAKED void CPlayerPed__KeepAreaAroundPlayerClear_60DE17()
	{
		__asm
		{
			mov eax, dword ptr[edx + edi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 41;
			jnz     loc_60DFF6;

			push 0x60DE25;
			retn;

		loc_60DFF6:
			push 0x60DFF6;
			retn;
		}
	}

	NAKED void patch_CPlayerPed__ProcessControl_60EBE2()
	{
		__asm
		{
			mov eax, [eax + esi + 0x5A0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 38;
			jnz     loc_60ED19;

			push 1;
			movsx eax, byte ptr[esi + 0x718];
			imul eax, 0x1C;

			mov eax, [eax + esi + 0x5A0];
			push eax;

			push 0x60EBF4;
			retn;

		loc_60ED19:
			push 0x60ED19;
			retn;
		}
	}

	NAKED void patch_CPlayerPed__ProcessControl_60ED23()
	{
		__asm
		{
			mov eax, [ecx + esi + 0x5A0];
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 9;
			jnz     loc_60ED4C;

			cmp eax, 16;
			jz      loc_60ED4C;

			push 0x60ED36;
			retn;


		loc_60ED4C:
			push 0x60ED4C;
			retn;
		}
	}

	NAKED void patch_CPlayerPed__ProcessControl_60F24D()
	{
		__asm
		{
			mov edi, [edx + esi + 0x5A0];

			push edi;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov edi, eax;
			add esp, 4;

			push 0x60F254;
			retn;
		}
	}

	NAKED void patch_Render2dStuff_53E2D2()
	{
		__asm
		{
			mov esi, [ecx + eax + 0x5A0];
			push esi;
			call CWeaponInfo::GetWeaponParentTypeUntilFastman92;
			mov esi, eax;
			add esp, 4;

			cmp esi, WEAPONTYPE_BINOCULARS_TYPE;
			jne doReturn;

			mov esi, WEAPONTYPE_SNIPERRIFLE;

		doReturn:
			push 0x53E2D9;
			retn;
		}
	}

	NAKED void patch_CDarkel__StartFrenzy_43D497()
	{
		__asm
		{
			add     edx, eax;

			push ecx;
			push edx;

			push eax;
			call CWeaponInfo::IsUserOperatedWeapon;
			add esp, 4;

			pop edx;
			pop ecx;

			test al, al;

			mov eax, 0x96A6E8;
			mov[eax], ecx;

			mov eax, 0x96A6E4;
			mov[eax], edx;

			jz loc_43D690;

			push 0x43D4AE;
			retn;

		loc_43D690:
			push 0x43D690;
			retn;

		}
	}

	NAKED void patch_CPed__AttachPedToEntity_5E7D98()
	{
		__asm
		{
			push ebx;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 43;
			jnz     loc_5E7DA5;

			push 0x5E7D9D;
			retn;

		loc_5E7DA5:
			push 0x5E7DA5;
			retn;
		}
	}

	NAKED void patch_CEventHandler__ComputeVehiclePotentialCollisionResponse_4C0ED2()
	{
		__asm
		{
			mov     eax, [edx + eax + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x4C0ED9;
			retn;
		}
	}

	NAKED void patch_Cam__Process_AimWeapon_521624()
	{
		__asm
		{
			mov     eax, [eax + edi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x52162B;
			retn;
		}
	}

	NAKED void patch_CRenderer__RenderFirstPersonVehicle_553D1C()
	{
		__asm
		{
			mov     edx, [ecx + eax + 5A0h];


			push edx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov edx, eax;
			add esp, 4;

			push 0x553D23;
			retn;
		}
	}

	NAKED void patch_CStats__BuildStatLine_55B3DD()
	{
		__asm
		{
			mov     eax, [ecx + eax + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x55B3E5;
			retn;
		}
	}

	NAKED void patch_CStats__BuildStatLine_55B427()
	{
		__asm
		{
			mov     ecx, [edx + eax + 5A0h];


			push ecx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov ecx, eax;
			add esp, 4;

			push 0x55B42E;
			retn;
		}
	}

	NAKED void patch_CMenuManager__InitForPause_576D89()
	{
		__asm
		{
			push eax;
			push ecx;

			mov     edi, [edx + eax + 5A0h];

			push edi;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov edi, eax;
			add esp, 4;

			pop ecx;
			pop eax;

			push 0x576D90;
			retn;
		}
	}

	NAKED void patch_CHud__DrawRadar_58A5B9()
	{
		__asm
		{
			mov     edx, [ecx + eax + 5A0h];

			push edx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov edx, eax;
			add esp, 4;

			push 0x58A5C0;
			retn;
		}
	}

	NAKED void patch_CHud__DrawCrossHairs_58E7B1()
	{
		__asm
		{
			mov     edx, [ecx + eax + 5A0h];

			push edx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov edx, eax;
			add esp, 4;

			push 0x58E7B8;
			retn;
		}
	}

	NAKED void patch_CPlayerPed__UpdateCameraWeaponModes_60983A()
	{
		__asm
		{
			mov     ecx, [eax + ecx + 5A0h];

			push ecx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov ecx, eax;
			add esp, 4;

			push 0x609841;
			retn;
		}
	}

	NAKED void patch_CPlayerPed__GetWeaponRadiusOnScreen_609D0E()
	{
		__asm
		{
			push eax;
			push edi;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov edi, eax;
			add esp, 4;
			pop eax;

			cmp     edi, 25;
			jz      loc_609D6F;

			push 0x609D13;
			retn;

		loc_609D6F:
			push 0x609D6F;
			retn;
		}
	}

	NAKED void patch_CTaskSimpleFight__FightHitPed_61CD5C()
	{
		__asm
		{
			mov     eax, [eax + esi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x61CD63;
			retn;
		}
	}

	NAKED void patch_CTaskSimpleFight__FightHitCar_61D101()
	{
		__asm
		{
			mov     eax, [ecx + edi + 5A0h];
			mov[esp + 7Ch + 4], eax;

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 9;

			push 0x61D112;
			retn;

		}
	}

	NAKED void patch_CTaskSimpleFight__ProcessPed_629C5F()
	{
		__asm
		{
			mov     eax, [ecx + ebx + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x629C66;
			retn;
		}
	}

	NAKED void patch_CTaskComplexPolicePursuit__SetWeapon_68BAF1()
	{
		__asm
		{
			mov     edx, [ecx + esi + 5A0h];

			push eax;
			push edx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov edx, eax;
			add esp, 4;
			pop eax;

			push 0x68BAF8;
			retn;
		}
	}

	NAKED void patch_CVisibilityPlugins__RenderWeaponPedsForPC_732FCB()
	{
		__asm
		{
			mov     eax, [ecx + ebx + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x732FD2;
			retn;
		}
	}

	NAKED void patch_CTaskSimplePlayHandSignalAnim__StartAnim_61AFD6()
	{
		__asm
		{
			mov     ecx, [eax + ebx + 5A0h];

			push ecx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov ecx, eax;
			add esp, 4;

			push 0x61AFDD;
			retn;
		}
	}

	NAKED void patch_CTaskSimpleFight__GetStrikeDamage_61C7AA()
	{
		__asm
		{
			mov     eax, [ecx + esi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x61C7B1;
			retn;
		}
	}

	NAKED void patch_CTaskSimpleFight__FightStrike_624143()
	{
		__asm
		{
			mov     eax, [ecx + edi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x62414A;
			retn;
		}
	}

	NAKED void patch_CPed__PreRenderAfterTest_5E6690()
	{
		__asm
		{
			push eax;
			mov eax, [ecx + ebp + 0x5A0];
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;
			cmp eax, 38;
			pop eax;

			push 0x5E6698;
			retn;
		}
	}

	NAKED void patch_CPed__ProcessControl_5E94E4()
	{
		__asm
		{
			mov eax, [eax + esi + 0x5A0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 9;

			push 0x5E94EC;
			retn;
		}
	}

	NAKED void patch_CPedIntelligence__GetUsingParachute_6011BC()
	{
		__asm
		{
			push eax;
			mov eax, [ecx + eax + 0x5A0];
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;
			cmp eax, 46;
			pop eax;

			push 0x6011C4;
			retn;
		}
	}

	NAKED void patch_CPlayerPed__Compute3rdPersonMouseTarget_60B94F()
	{
		__asm
		{
			mov eax, [eax + esi + 0x5A0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 23;

			push 0x60B957;
			retn;
		}
	}

	NAKED void patch_CTaskSimpleFight__FightHitCar_61D37A()
	{
		__asm
		{
			mov eax, [ecx + edi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 9;

			push 0x61D382;
			retn;
		}
	}

	NAKED void patch_CTaskSimpleFight__FightHitObj_61D587()
	{
		__asm
		{
			mov eax, [ecx + edi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 9;

			push 0x61D58F;
			retn;
		}
	}

	NAKED void CTaskSimpleThrowProjectile__StartAnim_625B0B()
	{
		__asm
		{
			mov eax, [eax + esi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 39;

			push 0x625B13;
			retn;
		}
	}

	NAKED void patch_CTaskSimpleFightCtrl__processPed_62A203()
	{
		__asm
		{
			mov eax, [ecx + edi + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, ebx;

			push 0x62A20A;
			retn;
		}
	}

	NAKED void patch_CTask_86E828__m18_641408()
	{
		__asm
		{
			mov eax, [ecx + ebx + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 46;

			push 0x641410;
			retn;
		}
	}

	NAKED void patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_685BBF()
	{
		__asm
		{
			mov eax, [edx + esi + 0x5A0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 36;

			push 0x685BC7;
			retn;
		}
	}

	NAKED void patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_685F25()
	{
		__asm
		{
			mov eax, [ecx + esi + 0x5A0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 9;

			push 0x685F2D;
			retn;
		}
	}

	NAKED void patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_686466()
	{
		__asm
		{
			mov eax, [eax + esi + 0x5A0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 42;

			push 0x68646E;
			retn;
		}
	}

	NAKED void patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_686B38()
	{
		__asm
		{
			mov eax, [eax + esi + 0x5A0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 23;

			push 0x686B40;
			retn;
		}
	}

	NAKED void patch_692662()
	{
		__asm
		{
			push eax;

			mov eax, [ecx + esi + 5A0h];
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;
			cmp eax, 41;
			pop eax;

			push 0x69266A;
			retn;
		}
	}

	NAKED void patch_CVisibilityPlugins__RenderWeaponPedsForPC_733041()
	{
		__asm
		{
			mov eax, [edx + ebx + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 46;

			push 0x733049;
			retn;
		}
	}

	NAKED void patch_CProjectileInfo__Update_738F68()
	{
		__asm
		{
			mov ecx, [eax + edi + 5A0h];

			push ecx;

			push ecx;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 40;

			pop ecx;

			jnz     loc_738F8D;
			push ecx;

			push 0x738F74;
			retn;

		loc_738F8D:
			push 0x738F8D;
			retn;
		}
	}

	NAKED void patch_CPed__CreateDeadPedWeaponPickups_459210()
	{
		__asm
		{
			mov     eax, [esi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			test eax, eax;
			jz      loc_4592FF;

			push 0x45921A;
			retn;

		loc_4592FF:
			push 0x4592FF;
			retn;
		}
	}

	NAKED void patch_CVehicle__InflictDamage_6D7DBA()
	{
		__asm
		{
			push ebx;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			lea eax, [eax - 16h];
			xor ebp, ebp;

			push 0x6D7DBF;
			retn;
		}
	}

	NAKED void patch_CVehicle__InflictDamage_6D7FF4()
	{
		__asm
		{
			push ebx;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 51
				jz      loc_6D801C
				cmp     eax, 16
				jz      loc_6D801C
				cmp     eax, 19
				jz      loc_6D801C
				cmp     eax, 20;
			jz      loc_6D801C;

			push 0x6D8008;
			retn;

		loc_6D801C:
			push 0x6D801C;
			retn;
		}
	}

	NAKED void patch_CVehicle__InflictDamage_6D8241()
	{
		__asm
		{
			push ebx;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 51;
			jnz     loc_6D8272;

			push 0x6D8246;
			retn;

		loc_6D8272:
			push 0x6D8272;
			retn;
		}
	}

	NAKED void patch_CEventDamage__ComputeDamageAnim_4B4023()
	{
		__asm
		{
			mov     eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 27;

			push 0x4B4029;
			retn;
		}
	}

	NAKED void patch_CEventDamage__ComputeDamageAnim_4B3FF6()
	{
		__asm
		{
			mov     ecx, [esi + 1Ch];


			push ecx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov ecx, eax;
			add esp, 4;

			test    ecx, ecx;
			push 0x4B3FFB;
			retn;
		}
	}

	NAKED void patch_CEventDamage__ComputeDamageAnim_4B4231()
	{
		__asm
		{
			mov     ecx, [esi + 1Ch];

			push ecx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov ecx, eax;
			add esp, 4;

			cmp     ecx, 9;

			push 0x4B4237;
			retn;
		}
	}

	NAKED void patch_CEventDamage__ComputeDamageAnim_4B4366()
	{
		__asm
		{
			mov     eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 22;

			push 0x4B436C;
			retn;
		}
	}

	NAKED void patch_CEventDamage__ComputeDamageAnim_4B446C()
	{
		__asm
		{
			mov eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 22;
			jl      loc_4B44AF;

			push 0x4B4472;
			retn;

		loc_4B44AF:
			push 0x4B44AF;
			retn;
		}
	}

	NAKED void patch_CEventDamage__ComputeDamageAnim_4B44AF()
	{
		__asm
		{
			mov     edx, [esi + 1Ch];

			push edx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov edx, eax;
			add esp, 4;

			cmp     edx, 22;

			push 0x4B44B5;
			retn;
		}
	}

	NAKED void patch_CEventDamage__ComputeDamageAnim_4B4405()
	{
		__asm
		{

			push eax;
			mov eax, dword ptr[esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 31;
			pop eax;

			jnz     loc_4B4430;

			push 0x4B440B;
			retn;

		loc_4B4430:
			push 0x4B4430;
			retn;
		}
	}

	NAKED void patch_CEventDamage__ComputeDeathAnim_4B3AE8()
	{
		__asm
		{
			mov eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 53;

			jz      loc_4B3EF6;

			push 0x4B3AF2;
			retn;

		loc_4B3EF6:
			push 0x4B3EF6;
			retn;
		}
	}


	NAKED void patch_CEventDamage__ComputeDeathAnim_4B3C33()
	{
		__asm
		{
			mov     eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 54; // switch 55 cases;

			push 0x4B3C39;
			retn;
		}
	}

	NAKED void patch_CEventDamage__ComputeDeathAnim_4B3E0E()
	{
		__asm
		{
			mov     eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			test eax, eax;

			push 0x4B3E13;
			retn;
		}
	}

	NAKED void patch_CEventDamage__ComputeHeadShot_4ADD67()
	{
		__asm
		{
			push ecx;
			push edx;

			mov     eax, [ecx + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 52; // switch 53 cases
			pop edx;
			pop ecx;

			push 0x4ADD6D;
			retn;
		}
	}

	NAKED void patch_CEventDamage__ComputeBodyPartToRemove_4ADC1E()
	{
		__asm
		{
			mov     eax, [ecx + 1Ch];

			push ecx;
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;
			pop ecx;

			cmp     eax, 51; // switch 52 cases;

			push 0x4ADC24;
			retn;
		}
	}

	NAKED void patch_CEventHandler__ComputeDamageResponse_4C0265()
	{
		__asm
		{
			push ebp;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			mov     byte ptr[esp + 68h - 0x4C], 0;

			cmp     eax, 49;

			push 0x4C026D;
			retn;
		}
	}

	NAKED void patch_CEventHandler__ComputeDamageResponse_4C03EC()
	{
		__asm
		{
			mov     eax, [esp + 68h + 4];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 41;

			push 0x4C03F3;
			retn;
		}
	}

	NAKED void patch_CEventHandler__ComputeDamageResponse_4C0B66()
	{
		__asm
		{
			push ebx;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 41;
			jz      loc_4C0B86;
			cmp     eax, 42;
			jz      loc_4C0B86;
			cmp     eax, 17;
			jz      loc_4C0B86;

		loc_4C0B86:
			push 0x4C0B86;
			retn;
		}
	}

	NAKED void patch_CEventHandler__ComputeDamageResponse_4C01AC()
	{
		__asm
		{
			mov[esp + 10h], ebx;

			pushf;
			push ebp;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;
			popf;

			mov[esp + 6Ch], eax;
			mov ebp, eax;

			push 0x4C01B4;
			retn;
		}
	}

	NAKED void patch_CEventHandler__ComputeDamageResponse_4C0A39()
	{
		__asm
		{
			mov     eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 22;

			push 0x4C0A3F;
			retn;
		}
	}

	NAKED void patch_CTaskSimpleProcessPlayerWeapon__m18_68595D()
	{
		__asm
		{
			mov     edi, [edi + 1Ch];

			push eax;
			call CWeaponInfo::IsUserOperatedWeapon;
			add esp, 4;

			test al, al;
			jnz loc_685997;

			push edi;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 52;
			jz      loc_685997;

			push 0x68596A;
			retn;

		loc_685997:
			push 0x685997;
			retn;
		}
	}

	NAKED void patch_CPickup__Update_457A33()
	{
		__asm
		{
			push edi;
			call CWeaponInfo::CWeaponInfo::GetWeaponParentTypeUntilFastman92;
			add esp, 4;

			cmp eax, WEAPONTYPE_JETPACK_TYPE;
			jz loc_457BDE;

			push edi;
			call CWeaponInfo::IsUserOperatedWeapon;
			add esp, 4;

			test al, al;
			jz loc_457BDE;

			push 0x457A44;
			retn;

		loc_457BDE:
			push 0x457BDE;
			retn;
		}
	}

	NAKED void patch_CPed__AddWeaponModel_5E5F7B()
	{
		__asm
		{
			mov eax, [ebx];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 18;

			jnz     loc_5E6005;

			// FASTMAN92_TODO

			push 0x5E5F8C;
			retn;

		loc_5E6005:
			push 0x5E6005;
			retn;
		}
	}

	NAKED void patch_CPed__ProcessControl_5E8D08()
	{
		__asm
		{
			mov eax, [ebx];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 18;

			jnz     loc_5E8DE6;

			push 0x5E8D11;
			retn;

		loc_5E8DE6:
			push 0x5E8DE6;
			retn;
		}
	}

	NAKED void patch_CPed__TakeOffGoggles_5E6031()
	{
		__asm
		{
			mov     eax, [edi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 45;
			jz      loc_5E603D;

			cmp     eax, 44;
			jnz     loc_5E6075;

			mov eax, [edi];

			push ebx;
			push 1;
			push eax;

			push 0x5E6041;
			retn;

		loc_5E603D:
			push 0x5E603D;
			retn;

		loc_5E6075:
			push 0x5E6075;
			retn;
		}
	}

	NAKED void patch_CPed__RemoveWeaponWhenEnteringVehicle_5E6384()
	{
		__asm
		{
			mov eax, [esi + 70Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 55;

			push 0x5E638B;
			retn;
		}
	}

	NAKED void patch_CPed__RemoveWeaponWhenEnteringVehicle_5E63B9()
	{
		__asm
		{
			mov     eax, [esi + 610h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			push 0x5E63BF;
			retn;
		}
	}

	NAKED void patch_CPed__RemoveWeaponWhenEnteringVehicle_5E63ED()
	{
		__asm
		{
			mov eax, [esi + 5F4h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 26;

			push 0x5E63F4;
			retn;
		}
	}

	NAKED void patch_CPed__RemoveWeaponWhenEnteringVehicle_5E6405()
	{
		__asm
		{
			mov eax, [esi + 5D8h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 22;

			push 0x5E640C;
			retn;
		}
	}

	NAKED void patch_CPed__RemoveWeaponWhenEnteringVehicle_5E641D()
	{
		__asm
		{
			mov eax, [esi + 70Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 55;

			push 0x5E6424;
			retn;
		}
	}

	NAKED void patch_CPed__PutOnGoggles_5E3B01()
	{
		__asm
		{
			mov     eax, [esi];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 45;
			jz      loc_5E3B0D;

			cmp     eax, 44;
			jnz     loc_5E3B59;

			mov eax, [esi];

			push ebx;
			push 1;
			push eax;

			push step2;
			push 0x743C60;
			retn;

		step2:
			mov     ebx, [eax + 0Ch];
			mov     eax, [esi];

			push eax;
			call CWeaponInfo::GetWeaponParentTypeUntilFastman92;
			add esp, 4;

			add     esp, 8;

			cmp eax, WEAPONTYPE_BINOCULARS_TYPE;
			jne step3;

			// BINOCULARS
			mov     ecx, edi;
			push offset bBinocularVisionGoggles;

			push 0x5E3B31;
			retn;

		step3:
			cmp     eax, 45;

			push 0x5E3B21;
			retn;

		loc_5E3B0D:
			push 0x5E3B0D;
			retn;

		loc_5E3B59:
			push 0x5E3B59;
			retn;
		}
	}

	NAKED void patch_CAEWeaponAudioEntity__ReportStealthKill_503B20()
	{
		__asm
		{
			mov eax, [esp + 4];

			push ecx;
			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;
			pop ecx;

			cmp eax, 4;

			push 0x503B25;
			retn;
		}
	}

	NAKED void patch_CAEPedAudioEntity__HandlePedHit_4E1ACB()
	{
		__asm
		{
			push eax;	// save register

			mov     edi, [edi];

			push edi;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov edi, eax;
			add esp, 4;

			pop eax;	// restore register

			cmp     edi, 45; // switch 46 cases;

			push 0x4E1AD0;
			retn;
		}
	}

	NAKED void patch_CAEPedAudioEntity__HandlePedSwing_4E1D5C()
	{
		__asm
		{
			push eax;
			mov     ecx, [edi];

			push ecx;
			call CWeaponInfo::GetWeaponHighestParentType;
			mov ecx, eax;
			add esp, 4;

			cmp     ecx, 45; // switch 46 cases;
			pop eax;

			push 0x4E1D61;
			retn;
		}
	}

	NAKED void patch_CEventDamage__AffectsPedGroup_4B38D4()
	{
		__asm
		{
			mov     edi, ecx;
			mov eax, [edi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 23;

			push 0x4B38DA;
			retn;
		}
	}

	NAKED void patch_CEventDamage__DoInformVehicleOccupants_4ADAF2()
	{
		__asm
		{
			mov eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 53;
			setnz   al;
			pop     esi;
			retn    4;
		}
	}

	NAKED void patch_CEventDamage__ReportCriminalEvent_4B3470()
	{
		__asm
		{
			add     esp, 4

			mov     eax, [esi + 1Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 9;

			push 0x4B3479;
			retn;
		}
	}

	NAKED void patch_CPedDamageResponseCalculator__ComputeWillForceDeath_4AD631()
	{
		__asm
		{
			mov     eax, [edi + 0Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			add     eax, -8;

			push 0x4AD637;
			retn;
		}
	}

	NAKED void patch_CPedDamageResponseCalculator__ComputeWillForceDeath_4AD6DF()
	{
		__asm
		{
			mov     eax, [edi + 0Ch];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 34;

			push 0x4AD6E5;
			retn;
		}
	}

	NAKED void patch_CAEPedWeaponAudioEntity__Service_4E6B22()
	{
		__asm
		{
			push eax;

			mov eax, [ecx];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 37;
			jnz     loc_4E6B31;

			pop eax;

			push 0x4E6B27;
			retn;

		loc_4E6B31:
			pop eax;
			push 0x4E6B31;
			retn;
		}
	}

	NAKED void patch_CPedIntelligence__ProcessAfterPreRender_601AAD()
	{
		__asm
		{
			push eax;
			push edx;

			mov     eax, [edx + eax + 5A0h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 18;

			pop edx;
			pop eax;

			push 0x601AB7;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireProjectile_741379()
	{
		__asm
		{
			push ecx;
			mov     ebx, [ecx];

			push ebx;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 35;

			pop ecx;

			push 0x74137E;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireProjectile_741607()
	{
		__asm
		{
			pushf;
			push ebx;
			call CWeaponInfo::GetWeaponTypeInfo;
			add esp, 4;
			mov ebx, [eax + tWeaponTypeInfo::AssociatedWeaponID];
			popf;

			mov[esp + 84h + 8], ebx;

			push 0x741610;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireProjectile_7416D9()
	{
		__asm
		{
			mov eax, [ecx];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 36;
			mov     ebp, [esi + 480h];

			push 0x7416E2;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireProjectile_7417BB()
	{
		__asm
		{
			mov     eax, [esp + 84h - 0x74];
			mov eax, [eax];

			push eax;
			call CWeaponInfo::GetWeaponTypeInfo;
			add esp, 4;
			mov ebx, [eax + tWeaponTypeInfo::AssociatedWeaponID];
			xor     ebp, ebp;

			push 0x7418C1;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireProjectile_741A1B()
	{
		__asm
		{
			push ebx;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 19;
			jnz     loc_741A2F;

			push 0x741A20;
			retn;

		loc_741A2F:
			push 0x741A2F;
			retn;
		}
	}

	NAKED void patch_CWeapon__FireProjectile_741AF4()
	{
		__asm
		{
			mov[ecx + 8], eax;

			mov     eax, [esp + 0x9C - 0x74];
			mov eax, [eax];

			push eax;
			call CWeaponInfo::GetWeaponTypeInfo;
			add esp, 4;
			mov eax, [eax + tWeaponTypeInfo::AssociatedWeaponID];
			push eax;

			push 0x741A52;
			retn;
		}
	}

	NAKED void patch_CShotInfo__Update_73A03E()
	{
		__asm
		{
			mov     eax, [esi - 18h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 41;

			push 0x73A044;
			retn;
		}
	}
	NAKED void patch_CShotInfo__Update_73A0D9()
	{
		__asm
		{
			mov     eax, [esi - 18h];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 41;

			push 0x73A0DF;
			retn;
		}
	}

	NAKED void patch_CBulletInfo__Update_736484()
	{
		__asm
		{
			mov eax, [edi - 4];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 37;
			jnz     loc_7364AF;

			push 0x73648A;
			retn;

		loc_7364AF:
			push 0x7364AF;
			retn;
		}
	}

	NAKED void patch_CBulletInfo__Update_7366C4()
	{
		_asm
		{
			mov eax, [edi - 4];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 34;
			jnz     loc_73675A;


			push 0x7366CE;
			retn;

		loc_73675A:
			push 0x73675A;
			retn;
		}
	}

	NAKED void patch_CBulletInfo__Update_73679F()
	{
		__asm
		{
			mov eax, [edi - 4];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 34;
			jnz     short loc_7367EB;

			mov     eax, ebx;
			mov     ecx, [eax];

			push 0x7367A5;
			retn;

		loc_7367EB:
			push 0x7367EB;
			retn;
		}
	}

	NAKED void patch_CPlayerPed__ProcessAnimGroups_609974()
	{
		__asm
		{
			__asm
			{
				mov     edi, [ebp + 24h];

				push edi;
				call CWeaponInfo::GetWeaponHighestParentType;
				mov edi, eax;
				add esp, 4;

				cmp     edi, 35;

				push 0x60997A;
				retn;
			}
		}
	}

	NAKED void patch_CPed__ClearWeapon_5E6305()
	{
		__asm
		{
			push edi;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp     eax, 44;
			jz      loc_5E630F;
			cmp     eax, 45;
			jnz     loc_5E6316;

			push 0x5E630F;
			retn;

		loc_5E630F:
			push 0x5E630F;
			retn;

		loc_5E6316:
			push 0x5E6316;
			retn;
		}
	}

	uintptr_t Address_CGarages__GivePlayerDetonator_ifEqual;
	uintptr_t Address_CGarages__GivePlayerDetonator_ifNotEqual;

	NAKED void patch_CGarages__GivePlayerDetonator_1569BD0()
	{
		__asm
		{
			mov eax, [esi + 0x70C];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 55;
			jz      loc_1569BE3;

			jmp Address_CGarages__GivePlayerDetonator_ifNotEqual;

		loc_1569BE3:
			jmp Address_CGarages__GivePlayerDetonator_ifEqual;
		}
	}

	NAKED void patch_CPed__AttachPedToEntity_5E7D34()
	{
		__asm
		{
			push eax;
			mov eax, [esi + 0x70C];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 55;
			pop eax;

			push 0x5E7D3B;
			retn;
		}
	}

	NAKED void patch_CDarkel__DealWithWeaponChangeAtEndOfFrenzy_43D7B6()
	{
		__asm
		{
			push edi;
			call CWeaponInfo::IsUserOperatedWeapon;
			add esp, 4;

			test al, al;
			jz loc_43D8F3;

			push 0x43D7BF;
			retn;

		loc_43D8F3:
			push 0x43D8F3;
			retn;
		}
	}

	NAKED void fpCWorld__SetPedsChoking(float posX, float posY, float posZ, float radius, void* playerPed, eWeaponType weaponType)
	{
		__asm
		{
			sub     esp, 24h;
			mov edx, 0xB74490;	// CPools::ms_pPedPool
			mov edx, [edx];

			push 0x565809;
			retn;
		}
	}

	void CWorld__SetPedsChoking(float posX, float posY, float posZ, float radius, void* playerPed)
	{
		fpCWorld__SetPedsChoking(posX, posY, posZ, radius, playerPed, WEAPONTYPE_TEARGAS);
	}

	NAKED void patch_CWorld__SetPedsChoking_5659C8()
	{
		__asm
		{
			push    eax;
			push    3;
			push    1;

			mov eax, [esp + 0x40 + 0x18];
			push    eax;

			push    ebx;
			push    esi;

			push 0x5659D1;
			retn;
		}	
	}

	const float float6 = 6.0;

	NAKED void patch_CProjectileInfo__Update_738C47()
	{
		__asm
		{
			mov edi, [ebx];
			push edi;
			mov     edi, [ebx + 4];
			mov     edx, [edx + 8];
			mov     ecx, [ecx + 4];
			push    edi;
			push    float6;
			push    edx;
			mov     edx, [eax];
			push    ecx;
			push    edx;
			call fpCWorld__SetPedsChoking;
			add esp, 18h;

			push 0x738C63;
			retn;
		}
	}

	NAKED void patch_CPlayerPed__FindSprayableBuilding_60C171()
	{
		__asm
		{
			mov eax, [ebp + 0];

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, 41;
			jnz     loc_60C19E;

			push 0x60C177;
			retn;

		loc_60C19E:
			push 0x60C19E;
			retn;
		}
	}

	void InitializeWeaponInfoExtension()
	{
		g_weaponLimits.NumberOfGunAimingOffsetsRegistered = 0;

		memset(
			g_weaponLimits.aWeaponInfoExtension,
			NULL,
			g_weaponLimits.CountOfWeaponInfos * sizeof(CWeaponInfoExtension)
		);
	}

	NAKED void patch_CWeaponInfo__LoadWeaponData_5BE670()
	{
		__asm
		{
			call InitializeWeaponInfoExtension;

			push ebp;
			mov ebp, esp;
			and     esp, 0FFFFFFF8h;

			push 0x5BE676;
			retn;
		}
	}

	void AssignGunAimingOffsets()
	{
		for (unsigned int i = 0; i < g_weaponLimits.CountOfWeaponInfos; i++)
		{
			const char* pAnimGrpName = g_weaponLimits.aWeaponInfoExtension[i].AnimGrpName;

			if (!pAnimGrpName[0])
				continue;

			for (unsigned int j = 0; j < g_weaponLimits.NumberOfGunAimingOffsetsRegistered; j++)
			{
				if (!strcmp(g_weaponLimits.CWeaponInfo__ms_aWeaponAimOffsetsExtension[j].name, pAnimGrpName))
				{
					g_weaponLimits.aWeaponInfo.gta_sa[i].m_nAimOffsetIndex = j;
					break;
				}
			}
		}
	}

	NAKED void patch_CWeaponInfo__LoadWeaponData_5BEC71()
	{
		__asm
		{
			pop ebx;
			mov     esp, ebp;
			pop     ebp;

			jmp AssignGunAimingOffsets;
		}
	}

	NAKED void patch_CWeaponInfo__LoadWeaponData_5BEC46()
	{
		__asm
		{
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_fileIDlimits, FileIDlimit, CModelInfo__ms_modelInfoPtrs);
			mov eax, [ecx + eax * 4];

			test eax, eax;
			jz goBack;

			mov[eax + 24h], ebx;

		goBack:
			push 0x5BEC50;
			retn;
		}
	}

	void RegisterWeaponInfoAnimGrp(int weaponInfoIndex, const char* animGrp)
	{
		//if(weaponInfoIndex == 42)
		//	printf_MessageBox("before weaponInfoIndex: %d pAnimGrpName: %s", weaponInfoIndex, animGrp);

		strcpy(g_weaponLimits.aWeaponInfoExtension[weaponInfoIndex].AnimGrpName, animGrp);
	}

	NAKED void patch_CWeaponInfo__LoadWeaponData_5BEAE2()
	{
		__asm
		{
			push edx;
			lea eax, [esp + 12Ch - 0x80];
			push eax;

			mov eax, [esp + 130h - 0x108];
			push eax;
			call RegisterWeaponInfoAnimGrp;
			add esp, 8;
			pop edx;

			fild[esp + 128h - 0x9C];

			push 0x5BEAE9;
			retn;
		}
	}

	NAKED void patch_CWeaponInfo__LoadWeaponData_5BE765()
	{
		__asm
		{
			push eax;

			lea  eax, [esp + 0x164 - 0x80];
			push eax;
			push ebx;
			call RegisterWeaponInfoAnimGrp;
			add esp, 8;

			pop eax;

			mov     edx, [esp + 160h - 0x110];
			mov     ecx, [esp + 160h - 0x104];

			push 0x5BE76D;
			retn;
		}
	}

	// Registers new weapon anim group
	int RegisterNewWeaponAnimGroup(const char* animGroupName)
	{
		if (g_weaponLimits.NumberOfGunAimingOffsetsRegistered
			< g_weaponLimits.GunAimingOffsetsLimit)
		{
			unsigned int index = g_weaponLimits.NumberOfGunAimingOffsetsRegistered++;

			CWeaponAimOffsetExtension* ptr = &g_weaponLimits.CWeaponInfo__ms_aWeaponAimOffsetsExtension[index];

			strcpy(ptr->name, animGroupName);
			return index;
		}
		else
			return -1;
	}

	NAKED void patch_CWeaponInfo__LoadWeaponData_5BECCA()
	{
		__asm
		{
			lea     ecx, [esp + 120h - 0x80];
			push ecx;
			call RegisterNewWeaponAnimGroup;
			mov edi, eax;
			add esp, 4;

			push 0x5BED1D;
			retn;
		}
	}

#define CTaskSimpleJetPack_MODEL_ID_OFFSET 0x70

	NAKED void patch_CTaskSimpleJetPack__CTaskSimpleJetPack_67B59E()
	{
		__asm
		{
			mov dword ptr[esi + CTaskSimpleJetPack_MODEL_ID_OFFSET], 370;
			mov     eax, esi;
			pop     esi;
			pop     ebx;
			mov     fs:[0], ecx;
			add     esp, 10h;
			retn    10h;
		}
	}

	NAKED void patch_CTaskSimpleJetPack__ProcessAnims_67B5C0()
	{
		__asm
		{
			mov eax, [ecx + CTaskSimpleJetPack_MODEL_ID_OFFSET];
			imul eax, SIZE CStreamingInfo;
			add eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_fileIDlimits, FileIDlimit, CStreaming__ms_aInfoForModel);

			cmp byte ptr[eax + CStreamingInfo::uiLoadFlag], 1;

			push    esi;
			mov     esi, ecx;

			jz      loc_67B5DD;

			mov eax, [ecx + CTaskSimpleJetPack_MODEL_ID_OFFSET];

			push 8;
			push eax;

			push 0x67B5D3;
			retn;

		loc_67B5DD:
			push 0x67B5DD;
			retn;

		}
	}

	NAKED void patch_CTaskSimpleJetPack__ProcessAnims_67B5E4()
	{

		__asm
		{
			push    edi;
			mov eax, [ecx + CTaskSimpleJetPack_MODEL_ID_OFFSET];
			shl eax, 2;
			add eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_fileIDlimits, FileIDlimit, CModelInfo__ms_modelInfoPtrs);
			mov edi, [eax];

			push 0x67B5EB;
			retn;
		}
	}

	NAKED void fpCPed__GiveWeapon()
	{
		__asm
		{
			push    ecx;
			push    ebx;
			mov ebx, [esp + 0Ch];

			push 0x5E6086;
			retn;
		}
	}

	class CTaskSimpleJetPack
	{
		char x[0x70 + 4];
	public:

		CTaskSimpleJetPack* Constructor(const CVector *pos, float a3, int a4, void *pEntity, int modelID)
		{
			int v5 = (int)this;

			((void(__thiscall*)(void*)) 0x61A390)(this);	// CTaskSimple::CTaskSimple

			*(DWORD *)v5 = 0x8705C4; // &_vt_CTaskSimpleJetpack;
			*(BYTE *)(v5 + 8) = 0;
			*(BYTE *)(v5 + 9) = 0;
			*(BYTE *)(v5 + 10) = 0;
			*(BYTE *)(v5 + 11) = 0;
			*(BYTE *)(v5 + 12) = 0;
			*(DWORD *)(v5 + 48) = 0;
			*(DWORD *)(v5 + 52) = 0;
			*(DWORD *)(v5 + 56) = 0;
			*(DWORD *)(v5 + 60) = 0;
			*(DWORD *)(v5 + 64) = 0;
			*(DWORD *)(v5 + 68) = 0;
			*(DWORD *)(v5 + 72) = 0;
			*(DWORD *)(v5 + 76) = 0;
			*(DWORD *)(v5 + 80) = 0;
			*(DWORD *)(v5 + 88) = a4;
			*(float *)(v5 + 84) = a3;
			*(DWORD *)(v5 + 92) = 0;
			*(void* *)(v5 + 96) = pEntity;
			*(BYTE *)(v5 + 13) = 0;
			*(BYTE *)(v5 + 14) = 0;
			*(DWORD *)(v5 + 16) = 0;
			*(DWORD *)(v5 + 20) = 0;
			*(DWORD *)(v5 + 24) = 0;
			*(DWORD *)(v5 + 28) = 0;
			*(DWORD *)(v5 + 32) = 0;
			*(DWORD *)(v5 + 36) = 0;
			*(DWORD *)(v5 + 40) = 0;
			*(DWORD *)(v5 + 44) = 0;

			if (pEntity)
				((void(__thiscall*)(void*, void**)) 0x571B70)(this, (void **)(v5 + 96));	// CEntity::RegisterReference

			if (pos)
				*(CVector *)(v5 + 72) = *pos;

			*(DWORD *)(v5 + 100) = 0;
			*(DWORD *)(v5 + 104) = 0;

			*(DWORD *)(v5 + CTaskSimpleJetPack_MODEL_ID_OFFSET) = modelID;
			return this;
		}
	};

	class CEventScriptCommand
	{
	public:
		int field_0;
		int field_4;
		char field_8;
		char gap_9[3];
		int field_C;
		int field_10;
		char field_14;
		char align[3];

		// Constructor
		CEventScriptCommand(int a2, void* pTask, bool a4)
		{
			((CEventScriptCommand*(__thiscall*)
				(CEventScriptCommand*, int a2, void* pTask, bool a4))
				0x4B0A00)
				(this, a2, pTask, a4);
		}

		// Destructor
		~CEventScriptCommand()
		{
			((void(__thiscall*)(CEventScriptCommand*)) 0x4B0A50)(this);
		}
	};

	// Patch for GiveWeapon
	class CPed
	{
	public:

		// Gives jetpack
		void GiveJetpack(int modelID)
		{
			this->RemoveJetpack();

			CTaskSimpleJetPack* pTask =
				((CTaskSimpleJetPack*(__cdecl*)(unsigned int)) 0x61A5A0)
				(sizeof(CTaskSimpleJetPack));

			if (pTask)
				pTask->Constructor(NULL, 10.0, 0, NULL, modelID);

			CEventScriptCommand command(3, pTask, 0);

			// CEventGroup::Add
			((void(__thiscall*)(void*, void*, bool)) 0x4AB420)(
				*(char**)((char*)this + 0x47C) + 0x68,
				&command,
				false
				);
		}

		// Remove jetpack
		void RemoveJetpack()
		{
			// CPedIntelligence::GetTaskJetPack
			CTaskSimpleJetPack* pTask =
				((CTaskSimpleJetPack*(__thiscall*)(void*))0x601110)
				(*(char**)((char*)this + 0x47C));

			if (pTask)
				((void(__thiscall*)(
					CTaskSimpleJetPack*,
					CPed* pPed,
					int a3,
					const void *pEvent
					)) *(void**)(*(char**)pTask + 0x18))	// CTaskSimpleJetPack::MakeAbortable
					(
						pTask,
						this,
						1,
						nullptr
						);
		}

		eWeaponSlot __thiscall GiveWeapon(int weaponType, unsigned int ammo, bool unk4)
		{
			int basicWeaponType = CWeaponInfo::GetWeaponParentTypeUntilFastman92(weaponType);

			if (basicWeaponType == WEAPONTYPE_JETPACK_TYPE)
			{
				const CWeaponInfo* pWeaponInfo = (const CWeaponInfo*)CWeaponInfo::GetWeaponInfo(weaponType, WEAPONSKILL_STD);

				this->GiveJetpack(pWeaponInfo->m_modelId);

				return (eWeaponSlot)*(__int8*)(this + 0x718);
			}
			else
				return ((eWeaponSlot(__thiscall*)(CPed*, int weaponType, unsigned int ammo, bool unk4)) &fpCPed__GiveWeapon)(this, weaponType, ammo, unk4);
		}
	};

	NAKED void patch_CTaskSimpleJetPack__DropJetPack_67B6C8()
	{
		__asm
		{
			mov eax, [esi + CTaskSimpleJetPack_MODEL_ID_OFFSET];
			push eax;

			push 0x67B6CD;
			retn;
		}
	}

	NAKED void patch_CTaskSimpleJetPack__Clone_67C6C3()
	{
		__asm
		{
			mov     ecx, [esi + CTaskSimpleJetPack_MODEL_ID_OFFSET];
			push ecx;

			mov     ecx, [esi + 60h];
			mov     edx, [esi + 58h];
			push    ecx;
			mov     ecx, [esi + 54h];
			push    edx;
			push    ecx;
			add     esi, 48h;
			push    esi;
			mov     ecx, eax;
			call CTaskSimpleJetPack::Constructor;

			push 0x67C6DA;
			retn;
		}
	}

	NAKED void patch_CHud__DrawWeaponIcon_58D917()
	{
		__asm
		{
			mov eax, [esp + 0x18 + 4];	// CPed*
			mov ecx, [eax + 0x47C];	// CPedIntelligence*

			push comeBackHereJetpackCheck;
			push 0x601110;	// CPedIntelligence::GetTaskJetPack
			retn;

		comeBackHereJetpackCheck:
			test eax, eax;
			jz noJetpack;

			mov     eax, [eax + CTaskSimpleJetPack_MODEL_ID_OFFSET];

			push 0x58D80B;
			retn;

		noJetpack:
			fild dword ptr[esp + 20h];
			fst dword ptr[esp + 08h];

			push 0x58D91F;
			retn;
		}
	}

	class CPickups
	{
	public:
		static const tPickupMessageInfo* GetWeaponModelEffectInfo(int modelID)
		{
			WeaponLimits* m_weaponLimits = &g_weaponLimits;

			if (modelID == *(unsigned short*)(0x8CD5C0))		// MI_PICKUP_BODYARMOUR
				return m_weaponLimits->aAaaa.ptr + 48;
			else if (modelID == *(unsigned short*)(0x8CD5C8))	// _miHealth
				return m_weaponLimits->aAaaa.ptr + 47;
			else if (modelID == *(unsigned short*)0x8CD5EC)		// _miPropertyFsale
				return m_weaponLimits->aAaaa.ptr + 47;
			else
			{
				if (modelID == -1)
					return 0;

				const CBaseModelInfo* pModelInfo = g_fileIDlimits.CModelInfo__ms_modelInfoPtrs.gta_sa[modelID];

				char modelType = ((char(__thiscall*)(
					const CBaseModelInfo*
					)) *(void**)(*(char**)pModelInfo + 0x10))	// GetModelType
					(
						pModelInfo
						);

				if (modelType != 4)
					return 0;

				int weaponType = *(int*)((char*)pModelInfo + 0x24);	// weaponType

				return &m_weaponLimits->WeaponTypes[weaponType].PickupMessageInfo;
			}
		}

		static int WeaponForModel(int modelID)
		{
			if (modelID == *(unsigned short*)(0x8CD5C0))		// MI_PICKUP_BODYARMOUR
				return 48;
			else if (modelID == *(unsigned short*)(0x8CD5C8))	// _miHealth
				return 47;
			else if (modelID == *(unsigned short*)0x8CD5EC)		// _miPropertyFsale
				return 47;
			else if (modelID == 370)
				return 47;
			else
			{
				if (modelID == -1)
					return 0;

				const CBaseModelInfo* pModelInfo = g_fileIDlimits.CModelInfo__ms_modelInfoPtrs.gta_sa[modelID];

				char modelType = ((char(__thiscall*)(
					const CBaseModelInfo*
					)) *(void**)(*(char**)pModelInfo + 0x10))	// GetModelType
					(
						pModelInfo
						);

				if (modelType != 4)
					return 0;

				return *(int*)((char*)pModelInfo + 0x24);	// weaponType
			}
		}
	};

	const float fOne = 1.0;

	NAKED void patch_CPickups__DoPickUpEffects_455ADA()
	{
		__asm
		{
			mov   eax, [esp + 3Ch + 4];
			mov     cl, byte ptr[eax + tPickupMessageInfo::red];
			fsubr   dword ptr[fOne];
			mov     dl, [eax + tPickupMessageInfo::green];
			mov     al, [eax + tPickupMessageInfo::blue];

			push 0x455AF5;
			retn;
		}
	}

	NAKED void patch_CEntity__PreRender_5361F5()
	{
		__asm
		{
			push eax;	// save EAX

			push eax;
			call CPickups::WeaponForModel;
			add esp, 4;

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

			cmp eax, WEAPONTYPE_ROCKET;
			je it_is_missile;

			cmp eax, WEAPONTYPE_ROCKET_HS;
			je it_is_missile;

			cmp eax, WEAPONTYPE_FREEFALL_BOMB;
			jne not_missile;

		it_is_missile:
			pop eax;	// restore EAX

			push 0x536200;
			retn;

		not_missile:
			pop eax;	// restore EAX

			push 0x5363B5;
			retn;
		}
	}

	NAKED void patch_CEntity__PreRender_53654B()
	{
		__asm
		{
			mov ecx, esi;
			call CEntity::GetModelID;

			push eax;
			call CPickups::WeaponForModel;
			add esp, 4;

			push eax;
			call CWeaponInfo::GetWeaponHighestParentType;
			add esp, 4;

		checkModel_grenade:
			cmp eax, WEAPONTYPE_GRENADE;
			jne checkModel_motolov;

			push 0x536559;
			retn;

		checkModel_motolov:
			cmp eax, WEAPONTYPE_MOLOTOV;
			jne defaultCode;
			push 0x536639;
			retn;

		defaultCode:
			push 0x8CD638;	// MI_BEACHBALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;

			push eax;
			mov ecx, esi;
			call CEntity::GetModelID;
			pop edx;

			cmp eax, edx;

			push 0x536797;
			retn;			
		}
	}

	NAKED void patch_CPed__AddGogglesModel_5E3ACB()
	{
		__asm
		{
			mov[esi + 500h], eax;

			test eax, eax;
			jz doReturn;

			mov     byte ptr[eax], 1;

		doReturn:
			push 0x5E3AD4;
			retn;
		}
	}

	NAKED void patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_686897()
	{
		__asm
		{
			movsx eax, byte ptr[esi + 0x718];	// CPed.m_bActiveWeapon
			imul eax, 0x1C;

			mov eax, [eax + esi + 0x5A0];

			push eax;
			call CWeaponInfo::GetWeaponParentTypeUntilFastman92;
			add esp, 4;

			cmp eax, WEAPONTYPE_BINOCULARS_TYPE;
			je step3;

			mov     ecx, ebp;

			push step2;
			push 0x540670;
			retn;

		step2:
			push 0x68689E;
			retn;

		step3:
			push 0x6868DF;
			retn;

		}
	}

	// Manually written patches
	namespace WeaponIDaccessPatches
	{
		static NAKED void patch_5429CC()
		{
			__asm
			{
				je other;

				// when != -1
				mov eax, 50;
				jmp goBack;

			other:
				// when -1
				mov eax, 53;

			goBack:
				push 0x5429D5;
				retn;
			}
		}

		static NAKED void patch_54809D()
		{
			__asm
			{
				je other;

				// when != -1
				mov edx, 50;
				jmp goBack;

			other:
				// when -1
				mov edx, 54;

			goBack:
				push 0x5480A7;
				retn;
			}
		}
	}

	// Automatically generated patches
	namespace WeaponIDaccessPatches
	{
		// Function: _opcode_handler_23
		// Original code:	movsx   eax, byte ptr [eax+148h]
		static NAKED void patch_47637A()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [eax + 148h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: _opcode_handler_23
		// Original code:	movsx   ecx, byte ptr [eax+148h]
		static NAKED void patch_476388()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [eax + 148h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				mov ecx, eax;
				pop edx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: _opcode_handler_23
		// Original code:	mov     byte ptr [eax+148h], 0FFh
		static NAKED void patch_4763DD()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push - 1;
				lea eax, [eax + 148h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_47FA30
		// Original code:	movsx   edx, byte ptr [eax+760h]
		static NAKED void patch_480E48()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [eax + 760h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				mov edx, eax;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_47FA30
		// Original code:	movsx   eax, byte ptr [eax+760h]
		static NAKED void patch_480E55()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [eax + 760h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_47FA30
		// Original code:	movsx   eax, byte ptr [eax+508h]
		static NAKED void patch_480EBE()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [eax + 508h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_47FA30
		// Original code:	movsx   ecx, byte ptr [eax+508h]
		static NAKED void patch_480ECC()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [eax + 508h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				mov ecx, eax;
				pop edx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_48A320
		// Original code:	mov     byte ptr [eax+760h], 0FFh
		static NAKED void patch_48A925()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push - 1;
				lea eax, [eax + 760h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_48A320
		// Original code:	mov     byte ptr [eax+508h], 0FFh
		static NAKED void patch_48A95E()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push - 1;
				lea eax, [eax + 508h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_4B5AC0
		// Original code:	mov     [edi+760h], al
		static NAKED void patch_4B5C78()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [edi + 760h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: _ZN9CPhysical21SetDamagedPieceRecordEfP7CEntityR9CColPointf
		// Original code:	cmp     byte ptr [esi+148h], 0FFh
		static NAKED void patch_5429C5()
		{
			__asm
			{
				push eax;
				push ecx;
				push edx;
				lea eax, [esi + 148h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				cmp eax, -1;
				pop edx;
				pop ecx;
				pop eax;
				retn;
			}
		}

		// Function: _ZN9CPhysical21SetDamagedPieceRecordEfP7CEntityR9CColPointf
		// Original code:	mov     [esi+148h], al
		static NAKED void patch_5429D5()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [esi + 148h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_547B80
		// Original code:	cmp     byte ptr [esi+148h], 0FFh
		static NAKED void patch_548096()
		{
			__asm
			{
				push eax;
				push ecx;
				push edx;
				lea eax, [esi + 148h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				cmp eax, -1;
				pop edx;
				pop ecx;
				pop eax;
				retn;
			}
		}

		// Function: sub_547B80
		// Original code:	mov     [esi+148h], dl
		static NAKED void patch_5480A7()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [esi + 148h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_59F840
		// Original code:	mov     byte ptr [esi+148h], 0FFh
		static NAKED void patch_59F991()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push - 1;
				lea eax, [esi + 148h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_40191E
		// Original code:	mov     [esi+148h], bl
		static NAKED void patch_5A0ED8()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ebx;
				lea eax, [esi + 148h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_5E8030
		// Original code:	mov     byte ptr [esi+760h], 0FFh
		static NAKED void patch_5E83F2()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push - 1;
				lea eax, [esi + 760h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_61D0B0
		// Original code:	mov     [esi+508h], al
		static NAKED void patch_61D35A()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [esi + 508h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_6A7650
		// Original code:	mov     byte ptr [esi+508h], 31h
		static NAKED void patch_6A7AE3()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push 49;
				lea eax, [esi + 508h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_6B8EC0
		// Original code:	mov     byte ptr [esi+508h], 31h
		static NAKED void patch_6B8F9E()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push 49;
				lea eax, [esi + 508h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_6D5F10
		// Original code:	mov     [esi+508h], al
		static NAKED void patch_6D60B9()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [esi + 508h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_6D7C97
		// Original code:	mov     [esi+508h], bl
		static NAKED void patch_6D8037()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ebx;
				lea eax, [esi + 508h];
				push eax;
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		static const tArrayItem ptrArray[] =
		{
		tArrayItem(0x47637A, &patch_47637A),	// _opcode_handler_23 : movsx   eax, byte ptr [eax+148h]
		tArrayItem(0x476388, &patch_476388),	// _opcode_handler_23 : movsx   ecx, byte ptr [eax+148h]
		tArrayItem(0x4763DD, &patch_4763DD),	// _opcode_handler_23 : mov     byte ptr [eax+148h], 0FFh
		tArrayItem(0x480E48, &patch_480E48),	// sub_47FA30 : movsx   edx, byte ptr [eax+760h]
		tArrayItem(0x480E55, &patch_480E55),	// sub_47FA30 : movsx   eax, byte ptr [eax+760h]
		tArrayItem(0x480EBE, &patch_480EBE),	// sub_47FA30 : movsx   eax, byte ptr [eax+508h]
		tArrayItem(0x480ECC, &patch_480ECC),	// sub_47FA30 : movsx   ecx, byte ptr [eax+508h]
		tArrayItem(0x48A925, &patch_48A925),	// sub_48A320 : mov     byte ptr [eax+760h], 0FFh
		tArrayItem(0x48A95E, &patch_48A95E),	// sub_48A320 : mov     byte ptr [eax+508h], 0FFh
		tArrayItem(0x4B5C78, &patch_4B5C78),	// sub_4B5AC0 : mov     [edi+760h], al
		tArrayItem(0x5429C5, &patch_5429C5),	// _ZN9CPhysical21SetDamagedPieceRecordEfP7CEntityR9CColPointf : cmp     byte ptr [esi+148h], 0FFh
		tArrayItem(0x5429D5, &patch_5429D5),	// _ZN9CPhysical21SetDamagedPieceRecordEfP7CEntityR9CColPointf : mov     [esi+148h], al
		tArrayItem(0x548096, &patch_548096),	// sub_547B80 : cmp     byte ptr [esi+148h], 0FFh
		tArrayItem(0x5480A7, &patch_5480A7),	// sub_547B80 : mov     [esi+148h], dl
		tArrayItem(0x59F991, &patch_59F991),	// sub_59F840 : mov     byte ptr [esi+148h], 0FFh
		tArrayItem(0x5A0ED8, &patch_5A0ED8),	// sub_40191E : mov     [esi+148h], bl
		tArrayItem(0x5E83F2, &patch_5E83F2),	// sub_5E8030 : mov     byte ptr [esi+760h], 0FFh
		tArrayItem(0x61D35A, &patch_61D35A),	// sub_61D0B0 : mov     [esi+508h], al
		tArrayItem(0x6A7AE3, &patch_6A7AE3),	// sub_6A7650 : mov     byte ptr [esi+508h], 31h
		tArrayItem(0x6B8F9E, &patch_6B8F9E),	// sub_6B8EC0 : mov     byte ptr [esi+508h], 31h
		tArrayItem(0x6D60B9, &patch_6D60B9),	// sub_6D5F10 : mov     [esi+508h], al
		tArrayItem(0x6D8037, &patch_6D8037),	// sub_6D7C97 : mov     [esi+508h], bl

		};
	}
	#endif

	void CPostEffects__ScriptResetForEffects_Init()
	{
		bBinocularVisionGoggles = false;
	}
}

// Register weapon type
tWeaponTypeInfo* RegisterWeaponType(int weaponType, const char* name, eWeaponSubsetType subset)
{
	tWeaponTypeInfo* pInfo = g_weaponLimits.WeaponTypes + weaponType;
	strncpy(pInfo->Name, name, sizeof(pInfo->Name));
	pInfo->Subset = subset;
	return pInfo;
}

// Enables weapon type loader
bool WeaponLimits::EnableWeaponTypeLoader(bool bEnable)
{
	MAKE_VAR_GAME_VERSION();

	if (bEnable)
	{
		if (!CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			bEnable = false;
	}

	this->bWeaponTypeLoaderEnabled = bEnable;
	return bEnable;
}

// Sets number of weapon types
void WeaponLimits::SetNumberOfWeaponTypes(int numberOfWeaponTypes)
{
	this->NumberOfWeaponTypes = numberOfWeaponTypes;
}

// Enables melee combo type loader
bool WeaponLimits::EnableMeleeComboTypeLoader(bool bEnable)
{
	MAKE_VAR_GAME_VERSION();

	if (bEnable)
	{
		if (!CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			bEnable = false;
	}

	this->bEnableMeleeComboTypeLoader = bEnable;
	return bEnable;
}

// Set combo limit
void WeaponLimits::SetMaxNumberOfMeleeCombos(int iValue)
{
	this->MaxNumberOfCombos = iValue;
}

// Commits changes
void WeaponLimits::CommitChanges()
{
	if (bWeaponTypeLoaderEnabled)
		this->ApplyWeaponTypeLoader();

	if (bEnableMeleeComboTypeLoader)
		this->ApplyMeleeComboTypeLoader();

	CGenericLogStorage::WriteLineSeparator();
}

// Initialize
void WeaponLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	this->NumberOfCustomWeaponTypes = 0;
	this->NumberOfWeaponTypes = 0;
	this->bWeaponTypeLoaderEnabled = false;
	this->bWeaponIDsizeExtended = false;
	this->bEnableMeleeComboTypeLoader = false;

	CTaskSimpleFight__m_aComboDataEx = NULL;

	CWeaponInfo__ms_aWeaponAimOffsetsExtension = NULL;

#ifdef WEAPON_TYPES_CONSTANT_LIMIT
	tWeaponTypeInfo WeaponLimits::WeaponTypes[WEAPON_TYPES_CONSTANT_LIMIT];
#else
	this->WeaponTypes = NULL;
#endif

	aWeaponInfoExtension = NULL;

	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		#ifdef IS_PLATFORM_WIN_X86
		AmmoForWeapon_OnStreet.ptr = (uint16_t*)0x8A5F50;
		aAaaa.ptr = (const tPickupMessageInfo*)0x8A5FB0;
		#endif
		
		this->NumberOfCustomWeaponTypes = 10;
		this->NumberOfWeaponTypes = 60 + this->NumberOfCustomWeaponTypes;

		#ifdef IS_PLATFORM_WIN_X86
		aWeaponInfo.gta_sa = (CWeaponInfo*)0xC8AAB8;
		#endif

		CountOfWeaponInfos = 0;
		
		NumberOfUnarmedComboTypes = 4;
		MaxNumberOfCombos = 17;
		MaxNumberOfCombosInArray = MaxNumberOfCombos - NumberOfUnarmedComboTypes;

		#ifdef IS_PLATFORM_WIN_X86
		CTaskSimpleFight__m_aComboData.gta_sa = (tComboData*)0xC170D0;
		#endif

		GunAimingOffsetsLimit = 22;
		NumberOfGunAimingOffsetsRegistered = 0;
	}
}

// Shutdown
void WeaponLimits::Shutdown()
{
	MAKE_VAR_GAME_VERSION();

	delete[] CTaskSimpleFight__m_aComboDataEx;
	delete[] CWeaponInfo__ms_aWeaponAimOffsetsExtension;
	delete[] this->WeaponTypes;
	delete[] aWeaponInfoExtension;

	if (AmmoForWeapon_OnStreet.bIsAllocated.Get())
		delete[] AmmoForWeapon_OnStreet.ptr;

	if (aAaaa.bIsAllocated.Get())
		delete[] aAaaa.ptr;

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		if (aWeaponInfo.bIsAllocated.Get())
			delete[] aWeaponInfo.gta_sa;

		if (CTaskSimpleFight__m_aComboData.bIsAllocated.Get())
			delete[] CTaskSimpleFight__m_aComboData.gta_sa;
	}
	
}

static void DoubleToStr(double num, char* out)
{
	if ((int)num == num)
		sprintf(out, "%g.0", num);
	else
		sprintf(out, "%g", num);
}

// // Applies a weapon type loader
void WeaponLimits::ApplyWeaponTypeLoader()
{
	MAKE_VAR_GAME_VERSION();

	if (!CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		return;

	#ifdef IS_PLATFORM_WIN_X86
	using namespace Game_GTASA;

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();
	
	if (CPatch::IsDebugModeActive())
		NumberOfWeaponTypes = 60 + this->NumberOfCustomWeaponTypes;

	if (NumberOfWeaponTypes < 60 + this->NumberOfCustomWeaponTypes)
		throw f92_runtime_error(
			"Number of weapon types cannot be lower than 70. Current value = %d",
			NumberOfWeaponTypes
			);

	#ifdef WEAPON_TYPES_CONSTANT_LIMIT
	if (NumberOfWeaponTypes > WEAPON_TYPES_CONSTANT_LIMIT)
	{
		printf_MessageBox(
			"Number of weapon types cannot be more than than %d. Current value = %d",
			WEAPON_TYPES_CONSTANT_LIMIT,
			NumberOfWeaponTypes
			);

		g_LimitAdjuster.TerminateProcess();
	}
	#else
	WeaponTypes = new tWeaponTypeInfo[NumberOfWeaponTypes];
	#endif

	// Initialize weapon type array
	for (unsigned int i = 0; i < NumberOfWeaponTypes; i++)
	{
		tWeaponTypeInfo* pInfo = WeaponTypes + i;
		pInfo->Name[0] = NULL;
		pInfo->bIsFastman92type = false;
		pInfo->Subset = WEAPON_SUBSET_UNUSED;
		pInfo->statIndex = -1;
		pInfo->PoorSkillindex = -1;
		pInfo->StandardSkillIndex = -1;
		pInfo->ProffesionalSkillIndex = -1;
		pInfo->SpecialSkillIndex = -1;
		pInfo->bCanBeUsedForSecondPlayer = true;
		pInfo->bHasWeaponAmmoToBeUsed = false;
		pInfo->ParentWeaponID = -1;
		pInfo->AmmoForWeapon_OnStreet = 0;
		pInfo->PickupMessageInfo = { 0 };
		pInfo->AssociatedWeaponID = -1;
	}

	// register reserved and fastman92 types
	#if TRUE
	{
		RegisterWeaponType(47, "LAST_WEAPONTYPE", WEAPON_SUBSET_RESERVED);
		RegisterWeaponType(48, "ARMOUR", WEAPON_SUBSET_RESERVED);
		RegisterWeaponType(49, "RAMMEDBYCAR", WEAPON_SUBSET_RESERVED);
		RegisterWeaponType(50, "RUNOVERBYCAR", WEAPON_SUBSET_RESERVED);
		RegisterWeaponType(51, "EXPLOSION", WEAPON_SUBSET_RESERVED);
		RegisterWeaponType(52, "UZI_DRIVEBY", WEAPON_SUBSET_RESERVED);
		RegisterWeaponType(53, "DROWNING", WEAPON_SUBSET_RESERVED);
		RegisterWeaponType(54, "FALL", WEAPON_SUBSET_RESERVED);
		RegisterWeaponType(55, "UNIDENTIFIED", WEAPON_SUBSET_RESERVED);
		RegisterWeaponType(56, "ANYMELEE", WEAPON_SUBSET_RESERVED);
		RegisterWeaponType(57, "ANYWEAPON", WEAPON_SUBSET_RESERVED);
		RegisterWeaponType(58, "FLARE", WEAPON_SUBSET_RESERVED);
		RegisterWeaponType(59, "TANK_GRENADE", WEAPON_SUBSET_RESERVED);

		{
			tWeaponTypeInfo* pInfo;

			// jetpack
			pInfo = RegisterWeaponType(WEAPONTYPE_JETPACK_TYPE, "JETPACK_TYPE", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
			pInfo->bIsFastman92type = true;
			pInfo->Subset = WEAPON_SUBSET_ONLY_STANDARD_SKILL;

			// binoculars
			pInfo = RegisterWeaponType(WEAPONTYPE_BINOCULARS_TYPE, "BINOCULARS_TYPE", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
			pInfo->bIsFastman92type = true;
			pInfo->Subset = WEAPON_SUBSET_ONLY_STANDARD_SKILL;
			pInfo->ParentWeaponID = WEAPONTYPE_NIGHTVISION;

			for (int weaponType = WEAPONTYPE_FASTMAN92_FIRST_NOT_MADE; weaponType <= WEAPONTYPE_FASTMAN92_LAST; weaponType++)
			{
				char typeName[128];
				sprintf(typeName, "LIMIT_ADJUSTER_TYPE_%d", weaponType);
				pInfo = RegisterWeaponType(weaponType, typeName, WEAPON_SUBSET_RESERVED);
				pInfo->bIsFastman92type = true;
			}
		}
	}
	#endif

	if(CPatch::IsDebugModeActive())
	{
		tWeaponTypeInfo* pInfo;

		pInfo = RegisterWeaponType(0, "UNARMED", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bHasWeaponAmmoToBeUsed = true;

		pInfo = RegisterWeaponType(1, "BRASSKNUCKLE", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bHasWeaponAmmoToBeUsed = true;

		pInfo = RegisterWeaponType(2, "GOLFCLUB", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bHasWeaponAmmoToBeUsed = true;

		pInfo = RegisterWeaponType(3, "NIGHTSTICK", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bHasWeaponAmmoToBeUsed = true;

		pInfo = RegisterWeaponType(4, "KNIFE", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bHasWeaponAmmoToBeUsed = true;

		pInfo = RegisterWeaponType(5, "BASEBALLBAT", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bHasWeaponAmmoToBeUsed = true;

		RegisterWeaponType(6, "SHOVEL", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(7, "POOLCUE", WEAPON_SUBSET_ONLY_STANDARD_SKILL);

		pInfo = RegisterWeaponType(8, "KATANA", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bHasWeaponAmmoToBeUsed = true;

		pInfo = RegisterWeaponType(9, "CHAINSAW", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bCanBeUsedForSecondPlayer = false;
		pInfo->bHasWeaponAmmoToBeUsed = true;

		pInfo = RegisterWeaponType(10, "DILDO1", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bHasWeaponAmmoToBeUsed = true;

		pInfo = RegisterWeaponType(11, "DILDO2", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bHasWeaponAmmoToBeUsed = true;

		pInfo = RegisterWeaponType(12, "VIBE1", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bHasWeaponAmmoToBeUsed = true;

		pInfo = RegisterWeaponType(13, "VIBE2", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bHasWeaponAmmoToBeUsed = true;

		pInfo = RegisterWeaponType(14, "FLOWERS", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bHasWeaponAmmoToBeUsed = true;

		RegisterWeaponType(15, "CANE", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(16, "GRENADE", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(17, "TEARGAS", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(18, "MOLOTOV", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(19, "ROCKET", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(20, "ROCKET_HS", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(21, "FREEFALL_BOMB", WEAPON_SUBSET_ONLY_STANDARD_SKILL);			

		pInfo = RegisterWeaponType(22, "PISTOL", WEAPON_SUBSET_MULTIPLE_SKILLS);
		pInfo->statIndex = 69;

		pInfo = RegisterWeaponType(23, "PISTOL_SILENCED", WEAPON_SUBSET_MULTIPLE_SKILLS);
		pInfo->statIndex = 70;

		pInfo = RegisterWeaponType(24, "DESERT_EAGLE", WEAPON_SUBSET_MULTIPLE_SKILLS);
		pInfo->statIndex = 71;

		pInfo = RegisterWeaponType(25, "SHOTGUN", WEAPON_SUBSET_MULTIPLE_SKILLS);
		pInfo->statIndex = 72;

		pInfo = RegisterWeaponType(26, "SAWNOFF", WEAPON_SUBSET_MULTIPLE_SKILLS);
		pInfo->statIndex = 73;

		pInfo = RegisterWeaponType(27, "SPAS12", WEAPON_SUBSET_MULTIPLE_SKILLS);
		pInfo->statIndex = 74;

		pInfo = RegisterWeaponType(28, "MICRO_UZI", WEAPON_SUBSET_MULTIPLE_SKILLS);
		pInfo->statIndex = 75;

		pInfo = RegisterWeaponType(29, "MP5", WEAPON_SUBSET_MULTIPLE_SKILLS);
		pInfo->statIndex = 76;

		pInfo = RegisterWeaponType(30, "AK47", WEAPON_SUBSET_MULTIPLE_SKILLS);
		pInfo->statIndex = 77;

		pInfo = RegisterWeaponType(31, "M4", WEAPON_SUBSET_MULTIPLE_SKILLS);
		pInfo->statIndex = 78;

		pInfo = RegisterWeaponType(32, "TEC9", WEAPON_SUBSET_MULTIPLE_SKILLS);
		pInfo->statIndex = 75;

		RegisterWeaponType(33, "COUNTRYRIFLE", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo = RegisterWeaponType(34, "SNIPERRIFLE", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bCanBeUsedForSecondPlayer = false;

		pInfo = RegisterWeaponType(35, "RLAUNCHER", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bCanBeUsedForSecondPlayer = false;

		RegisterWeaponType(36, "RLAUNCHER_HS", WEAPON_SUBSET_ONLY_STANDARD_SKILL);			

		RegisterWeaponType(37, "FTHROWER", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(38, "MINIGUN", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(39, "SATCHEL_CHARGE", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(40, "DETONATOR", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(41, "SPRAYCAN", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(42, "EXTINGUISHER", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(43, "CAMERA", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(44, "NIGHTVISION", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		RegisterWeaponType(45, "INFRARED", WEAPON_SUBSET_ONLY_STANDARD_SKILL);

		pInfo = RegisterWeaponType(46, "PARACHUTE", WEAPON_SUBSET_ONLY_STANDARD_SKILL);
		pInfo->bCanBeUsedForSecondPlayer = false;
		pInfo->bHasWeaponAmmoToBeUsed = true;

		WeaponTypes[CWeaponInfo::FindWeaponType("RLAUNCHER")].AssociatedWeaponID
			= CWeaponInfo::FindWeaponType("ROCKET");

		WeaponTypes[CWeaponInfo::FindWeaponType("RLAUNCHER_HS")].AssociatedWeaponID
			= CWeaponInfo::FindWeaponType("ROCKET_HS");

		// Set ammo for weapon
		for (unsigned int i = 0; i < NumberOfWeaponTypes; i++)
		{
			tWeaponTypeInfo* pInfo = WeaponTypes + i;

			if (pInfo->Subset != WEAPON_SUBSET_ONLY_STANDARD_SKILL
				&& pInfo->Subset != WEAPON_SUBSET_MULTIPLE_SKILLS)
				continue;

			pInfo->AmmoForWeapon_OnStreet = AmmoForWeapon_OnStreet.ptr[i];
			pInfo->PickupMessageInfo = aAaaa.ptr[i];
		}

		// print to log
		for (unsigned int i = 0; i < NumberOfWeaponTypes; i++)
		{
			const tWeaponTypeInfo* pInfo = WeaponTypes + i;

			if (pInfo->bIsFastman92type || (pInfo->Subset != WEAPON_SUBSET_ONLY_STANDARD_SKILL
				&& pInfo->Subset != WEAPON_SUBSET_MULTIPLE_SKILLS))
				continue;

			char float_4[32];

			DoubleToStr(pInfo->PickupMessageInfo.float_4, float_4);

			//%-43s %-13d 
			CGenericLogStorage::SaveFormattedTextLn(
				"%-5d %-35s %-10d %-26d %-23d %-23d %-4d %-4d  %-4d %-15s",
				i,
				pInfo->Name,
				pInfo->statIndex,
				pInfo->bCanBeUsedForSecondPlayer,
				pInfo->bHasWeaponAmmoToBeUsed,
				pInfo->AmmoForWeapon_OnStreet,

				pInfo->PickupMessageInfo.red,
				pInfo->PickupMessageInfo.green,
				pInfo->PickupMessageInfo.blue,
				float_4
				);
		}
	}
	else
		LoadWeaponTypes();

	{
		this->bWeaponIDsizeExtended = this->NumberOfWeaponTypes > 0xFF;
		CountOfWeaponInfos = 0;

		for (unsigned int i = 0; i < NumberOfWeaponTypes; i++)
		{
			if (!WeaponTypes[i].bIsFastman92type
				&& WeaponTypes[i].Subset == WEAPON_SUBSET_ONLY_STANDARD_SKILL
				|| WeaponTypes[i].Subset == WEAPON_SUBSET_MULTIPLE_SKILLS)
				WeaponTypes[i].StandardSkillIndex = CountOfWeaponInfos++;
		}
			
		for (unsigned int i = 0; i < NumberOfWeaponTypes; i++)
		{
			if (!WeaponTypes[i].bIsFastman92type && WeaponTypes[i].Subset == WEAPON_SUBSET_MULTIPLE_SKILLS)
				WeaponTypes[i].PoorSkillindex = CountOfWeaponInfos++;				
		}

		for (unsigned int i = 0; i < NumberOfWeaponTypes; i++)
		{
			if (!WeaponTypes[i].bIsFastman92type && WeaponTypes[i].Subset == WEAPON_SUBSET_MULTIPLE_SKILLS)
				WeaponTypes[i].ProffesionalSkillIndex = CountOfWeaponInfos++;
		}

		for (unsigned int i = 0; i < NumberOfWeaponTypes; i++)
		{
			if (!WeaponTypes[i].bIsFastman92type && WeaponTypes[i].Subset == WEAPON_SUBSET_MULTIPLE_SKILLS)
				WeaponTypes[i].SpecialSkillIndex = CountOfWeaponInfos++;
		}

		if (CountOfWeaponInfos > 80)
		{
			aWeaponInfo.gta_sa = new CWeaponInfo[CountOfWeaponInfos];
			aWeaponInfo.bIsAllocated.Set(true);
		}

		aWeaponInfoExtension = new CWeaponInfoExtension[CountOfWeaponInfos];
		memset(aWeaponInfoExtension, NULL, CountOfWeaponInfos * sizeof(CWeaponInfoExtension));

		CWeaponInfo__ms_aWeaponAimOffsetsExtension = new CWeaponAimOffsetExtension[GunAimingOffsetsLimit];		

		unsigned int maxUserWeaponID = 0;

		for (unsigned int i = 0; i < NumberOfWeaponTypes; i++)
		{
			const tWeaponTypeInfo* pInfo = WeaponTypes + i;

			if (!pInfo->bIsFastman92type &&
				(pInfo->Subset == WEAPON_SUBSET_ONLY_STANDARD_SKILL
				|| pInfo->Subset == WEAPON_SUBSET_MULTIPLE_SKILLS))
				maxUserWeaponID = i;
		}

		if (maxUserWeaponID >= 47)
		{
			AmmoForWeapon_OnStreet.ptr = new unsigned short[maxUserWeaponID + 1];
			AmmoForWeapon_OnStreet.bIsAllocated.Set(true);
		}

		// Initialize AmmoForWeapon_OnStreet array
		for (unsigned int i = 0; i <= maxUserWeaponID; i++)
		{
			const tWeaponTypeInfo* pInfo = WeaponTypes + i;

			if (pInfo->Subset == WEAPON_SUBSET_ONLY_STANDARD_SKILL
				|| pInfo->Subset == WEAPON_SUBSET_MULTIPLE_SKILLS)
				AmmoForWeapon_OnStreet.ptr[i] = pInfo->AmmoForWeapon_OnStreet;
			else
				AmmoForWeapon_OnStreet.ptr[i] = 0;
		}
	}	

	// Patch references to aWeaponInfo
	#if TRUE
	{
		CPatch::PatchPointer(0x5BE76D + 2, &aWeaponInfo.gta_sa->m_fTargetRange);	// mov     ds:aWeaponInfo.gta_sa.m_fTargetRange[edi], edx	; sub_5BE670
		CPatch::PatchPointer(0x5BE777 + 2, &aWeaponInfo.gta_sa->m_eFireType);	// mov     dword ptr ds:aWeaponInfo.gta_sa.m_eFireType[edi], eax	; sub_5BE670
		CPatch::PatchPointer(0x5BE781 + 2, &aWeaponInfo.gta_sa->m_modelId2);	// mov     ds:aWeaponInfo.gta_sa.m_modelId2[edi], edx	; sub_5BE670
		CPatch::PatchPointer(0x5BE787 + 2, &aWeaponInfo.gta_sa->m_fWeaponRange);	// mov     ds:aWeaponInfo.gta_sa.m_fWeaponRange[edi], eax	; sub_5BE670
		CPatch::PatchPointer(0x5BE791 + 2, &aWeaponInfo.gta_sa->m_modelId);	// mov     ds:aWeaponInfo.gta_sa.m_modelId[edi], ecx	; sub_5BE670
		CPatch::PatchPointer(0x5BE7A9 + 2, &aWeaponInfo.gta_sa->m_nWeaponSlot);	// mov     ds:aWeaponInfo.gta_sa.m_nWeaponSlot[edi], eax	; sub_5BE670
		CPatch::PatchPointer(0x5BE7AF + 2, &aWeaponInfo.gta_sa->m_nCombosAvailable);	// mov     ds:aWeaponInfo.gta_sa.m_nCombosAvailable[edi], cl	; sub_5BE670
		CPatch::PatchPointer(0x5BE7BC + 2, &aWeaponInfo.gta_sa->m_defaultCombo);	// mov     ds:aWeaponInfo.gta_sa.m_defaultCombo[edi], al	; sub_5BE670
		CPatch::PatchPointer(0x5BE7D3 + 2, &aWeaponInfo.gta_sa->m_nFlags);	// mov     ds:aWeaponInfo.gta_sa.m_nFlags[edi], eax	; sub_5BE670
		CPatch::PatchPointer(0x5BE84C + 2, &aWeaponInfo.gta_sa->m_animGroup);	// mov     ds:aWeaponInfo.gta_sa.m_animGroup[edi], ebp	; sub_5BE670
		CPatch::PatchPointer(0x5BE9E3 + 2, &aWeaponInfo.gta_sa->m_eFireType);	// mov     dword ptr ds:aWeaponInfo.gta_sa.m_eFireType[esi], eax	; sub_5BE670
		CPatch::PatchPointer(0x5BE9F3 + 2, &aWeaponInfo.gta_sa->m_fTargetRange);	// mov     ds:aWeaponInfo.gta_sa.m_fTargetRange[esi], edx	; sub_5BE670
		CPatch::PatchPointer(0x5BE9FD + 2, &aWeaponInfo.gta_sa->m_fWeaponRange);	// mov     ds:aWeaponInfo.gta_sa.m_fWeaponRange[esi], eax	; sub_5BE670
		CPatch::PatchPointer(0x5BEA03 + 2, &aWeaponInfo.gta_sa->m_animLoopStart);	// fstp    ds:aWeaponInfo.gta_sa.m_animLoopStart[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEA14 + 2, &aWeaponInfo.gta_sa->m_modelId);	// mov     ds:aWeaponInfo.gta_sa.m_modelId[esi], ecx	; sub_5BE670
		CPatch::PatchPointer(0x5BEA22 + 2, &aWeaponInfo.gta_sa->m_modelId2);	// mov     ds:aWeaponInfo.gta_sa.m_modelId2[esi], edx	; sub_5BE670
		CPatch::PatchPointer(0x5BEA33 + 2, &aWeaponInfo.gta_sa->m_nWeaponSlot);	// mov     ds:aWeaponInfo.gta_sa.m_nWeaponSlot[esi], eax	; sub_5BE670
		CPatch::PatchPointer(0x5BEA39 + 3, &aWeaponInfo.gta_sa->m_nAmmo);	// mov     ds:aWeaponInfo.gta_sa.m_nAmmo[esi], cx	; sub_5BE670
		CPatch::PatchPointer(0x5BEA40 + 2, &aWeaponInfo.gta_sa->m_animLoopEnd);	// fstp    ds:aWeaponInfo.gta_sa.m_animLoopEnd[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEA4E + 3, &aWeaponInfo.gta_sa->m_nDamage);	// mov     ds:aWeaponInfo.gta_sa.m_nDamage[esi], dx	; sub_5BE670
		CPatch::PatchPointer(0x5BEA59 + 2, &aWeaponInfo.gta_sa->m_vecFireOffset);	// lea     eax, aWeaponInfo.gta_sa.m_vecFireOffset.x[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEA6E + 2, &aWeaponInfo.gta_sa->m_animFireTime);	// fstp    ds:aWeaponInfo.gta_sa.m_animFireTime[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEA96 + 2, &aWeaponInfo.gta_sa->m_fMoveSpeed);	// mov     ds:aWeaponInfo.gta_sa.m_fMoveSpeed[esi], ecx	; sub_5BE670
		CPatch::PatchPointer(0x5BEAA0 + 2, &aWeaponInfo.gta_sa->m_nReqStatLevel);	// mov     ds:aWeaponInfo.gta_sa.m_nReqStatLevel[esi], edx	; sub_5BE670
		CPatch::PatchPointer(0x5BEAAA + 2, &aWeaponInfo.gta_sa->m_anim2LoopStart);	// fstp    ds:aWeaponInfo.gta_sa.m_anim2LoopStart[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEAB4 + 2, &aWeaponInfo.gta_sa->m_fAccuracy);	// mov     ds:aWeaponInfo.gta_sa.m_fAccuracy[esi], eax	; sub_5BE670
		CPatch::PatchPointer(0x5BEAC6 + 2, &aWeaponInfo.gta_sa->m_fRadius);	// mov     ds:aWeaponInfo.gta_sa.m_fRadius[esi], ecx	; sub_5BE670
		CPatch::PatchPointer(0x5BEACC + 2, &aWeaponInfo.gta_sa->m_nFlags);	// mov     ds:aWeaponInfo.gta_sa.m_nFlags[esi], edx	; sub_5BE670
		CPatch::PatchPointer(0x5BEAD6 + 2, &aWeaponInfo.gta_sa->m_anim2LoopEnd);	// fstp    ds:aWeaponInfo.gta_sa.m_anim2LoopEnd[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEADC + 2, &aWeaponInfo.gta_sa->m_fSpeed);	// mov     ds:aWeaponInfo.gta_sa.m_fSpeed[esi], eax	; sub_5BE670
		CPatch::PatchPointer(0x5BEB00 + 2, &aWeaponInfo.gta_sa->m_SkillLevel);	// mov     ds:aWeaponInfo.gta_sa.m_SkillLevel[esi], edi	; sub_5BE670
		CPatch::PatchPointer(0x5BEB06 + 2, &aWeaponInfo.gta_sa->m_fLifeSpan);	// mov     ds:aWeaponInfo.gta_sa.m_fLifeSpan[esi], edx	; sub_5BE670
		CPatch::PatchPointer(0x5BEB0C + 2, &aWeaponInfo.gta_sa->m_anim2FireTime);	// fstp    ds:aWeaponInfo.gta_sa.m_anim2FireTime[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEB12 + 2, &aWeaponInfo.gta_sa->m_fSpread);	// mov     ds:aWeaponInfo.gta_sa.m_fSpread[esi], eax	; sub_5BE670
		CPatch::PatchPointer(0x5BEB25 + 2, &aWeaponInfo.gta_sa->m_animBreakoutTime);	// fstp    ds:aWeaponInfo.gta_sa.m_animBreakoutTime[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEB8D + 2, &aWeaponInfo.gta_sa->m_animGroup);	// mov     ds:aWeaponInfo.gta_sa.m_animGroup[esi], ebp	; sub_5BE670
		CPatch::PatchPointer(0x5BEB93 + 2, &aWeaponInfo.gta_sa->m_animGroup);	// mov     eax, ds:aWeaponInfo.gta_sa.m_animGroup[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEBA7 + 3, &aWeaponInfo.gta_sa->m_nAimOffsetIndex);	// mov     ds:aWeaponInfo.gta_sa.m_nAimOffsetIndex[esi], ax	; sub_5BE670
		CPatch::PatchPointer(0x5BEBC0 + 2, &aWeaponInfo.gta_sa->m_animLoopEnd);	// fld     ds:aWeaponInfo.gta_sa.m_animLoopEnd[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEBC9 + 2, &aWeaponInfo.gta_sa->m_animLoopStart);	// fsub    ds:aWeaponInfo.gta_sa.m_animLoopStart[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEBEF + 2, &aWeaponInfo.gta_sa->m_animLoopStart);	// fadd    ds:aWeaponInfo.gta_sa.m_animLoopStart[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEBF5 + 2, &aWeaponInfo.gta_sa->m_animLoopEnd);	// fstp    ds:aWeaponInfo.gta_sa.m_animLoopEnd[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEBFB + 2, &aWeaponInfo.gta_sa->m_anim2LoopEnd);	// fld     ds:aWeaponInfo.gta_sa.m_anim2LoopEnd[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEC01 + 2, &aWeaponInfo.gta_sa->m_anim2LoopStart);	// fsub    ds:aWeaponInfo.gta_sa.m_anim2LoopStart[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEC2C + 2, &aWeaponInfo.gta_sa->m_anim2LoopStart);	// fadd    ds:aWeaponInfo.gta_sa.m_anim2LoopStart[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BEC32 + 2, &aWeaponInfo.gta_sa->m_anim2LoopEnd);	// fstp    ds:aWeaponInfo.gta_sa.m_anim2LoopEnd[esi]	; sub_5BE670
		CPatch::PatchPointer(0x5BF77D + 1, &aWeaponInfo.gta_sa->m_fTargetRange);	// mov     eax, offset aWeaponInfo.gta_sa.m_fTargetRange	; sub_5BF750
		CPatch::PatchPointer(0x5BF7F7 + 1, &aWeaponInfo.gta_sa[CountOfWeaponInfos].m_fTargetRange);	// cmp     eax, offset unk_C8CDBC	; sub_5BF750
		CPatch::PatchPointer(0x743C7A + 1, aWeaponInfo.gta_sa);	// add     eax, offset aWeaponInfo.gta_sa	; sub_743C60
		CPatch::PatchPointer(0x743C8F + 1, aWeaponInfo.gta_sa);	// add     eax, offset aWeaponInfo.gta_sa	; sub_743C60
		CPatch::PatchPointer(0x743CA7 + 1, aWeaponInfo.gta_sa);	// add     eax, offset aWeaponInfo.gta_sa	; sub_743C60
		CPatch::PatchPointer(0x743CBF + 1, aWeaponInfo.gta_sa);	// add     eax, offset aWeaponInfo.gta_sa	; sub_743C60
		CPatch::PatchPointer(0x855E1E + 1, aWeaponInfo.gta_sa);	// push    offset aWeaponInfo.gta_sa	; 
		CPatch::PatchPointer(0x856C69 + 1, aWeaponInfo.gta_sa);	// push    offset aWeaponInfo.gta_sa	; sub_856C60
	}
	#endif

	// Patch references to AmmoForWeapon_OnStreet
	#if TRUE
	{
		CPatch::PatchPointer(0x457E4F + 4, AmmoForWeapon_OnStreet.ptr);	// movzx   eax, ds:AmmoForWeapon_OnStreet[esi*2]	; sub_457410
		CPatch::PatchPointer(0x457FD5 + 4, AmmoForWeapon_OnStreet.ptr);	// movzx   eax, ds:AmmoForWeapon_OnStreet[esi*2]	; sub_457410
		CPatch::PatchPointer(0x45925B + 4, AmmoForWeapon_OnStreet.ptr);	// movzx   eax, ds:AmmoForWeapon_OnStreet[ecx*2]	; sub_4591D0
		CPatch::PatchPointer(0x4592B1 + 4, AmmoForWeapon_OnStreet.ptr);	// movzx   eax, ds:AmmoForWeapon_OnStreet[ecx*2]	; sub_4591D0

		if(gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
			CPatch::PatchPointer(0x156DB88 + 4, AmmoForWeapon_OnStreet.ptr);	// movzx   edx, ds:AmmoForWeapon_OnStreet[edi*2]	; sub_156DB40
		else if(gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
			CPatch::PatchPointer(0x454C28 + 4, AmmoForWeapon_OnStreet.ptr);	// movzx   edx, ds:AmmoForWeapon_OnStreet[edi*2]	; sub_156DB40
	}
	#endif

	// To do: count of weapon infos at 0x855E1E and 0x856C69

	// Weapon limit patches
	#if TRUE
	{
		// The basic patches
		{
			CPatch::RedirectCode(0x743D10, &CWeaponInfo::FindWeaponType);
			CPatch::RedirectFunction(0x743C60, &CWeaponInfo::GetWeaponInfo);
			CPatch::RedirectCode(0x5BE975, &patch_CWeaponInfo__LoadWeaponData_5BE975);
			CPatch::RedirectCode(0x5BE75A, &patch_CWeaponInfo__LoadWeaponData_5BE75A);
			CPatch::RedirectFunction(0x743CD0, &CWeaponInfo::GetSkillStatIndex);

			CPatch::RedirectCode(0x5BEC46, &patch_CWeaponInfo__LoadWeaponData_5BEC46);
			
			CPatch::RedirectCode(0x73A81E, &patch_CWeapon__GenerateDamageEvent_73A81E);
			CPatch::RedirectCode(0x73A704, &patch_CWeapon__GenerateDamageEvent_73A704);
			CPatch::RedirectCode(0x73A6EE, &patch_CWeapon__GenerateDamageEvent_73A6EE);
			
		}
		////////////////////////////////////////////////////////////////////////
			
#if 1
		/////////////////////// audio
		{
			CPatch::RedirectCode(0x5036EB, &patch_CAEWeaponAudioEntity__WeaponReload_5036EB);
			CPatch::RedirectCode(0x4DF074, &patch_CAEGlobalWeaponAudioEntity__ProjectileFire_4DF074);
			CPatch::RedirectCode(0x504F8F, &patch_CAEWeaponAudioEntity__WeaponFire_504F8F);
			CPatch::RedirectCode(0x503B20, &patch_CAEWeaponAudioEntity__ReportStealthKill_503B20);
			CPatch::RedirectCode(0x4E1ACB, &patch_CAEPedAudioEntity__HandlePedHit_4E1ACB);
			CPatch::RedirectCode(0x4E1D5C, &patch_CAEPedAudioEntity__HandlePedSwing_4E1D5C);
		}
		//////////////////////
#endif

#if 1
		CPatch::RedirectCode(0x74245C, &patch_CWeapon__Fire_74245C);
		CPatch::RedirectCode(0x7427B0, &patch_CWeapon__Fire_7427B0);
		CPatch::RedirectCode(0x7427FE, &patch_CWeapon__Fire_7427FE);
		CPatch::RedirectCode(0x74281F, &patch_CWeapon__Fire_74281F);
		CPatch::RedirectCode(0x74286F, &patch_CWeapon__Fire_74286F);
		CPatch::RedirectCode(0x7428E1, &patch_CWeapon__Fire_7428E1);
		CPatch::RedirectCode(0x7429B3, &patch_CWeapon__Fire_7429B3);
		CPatch::RedirectCode(0x7429F2, &patch_CWeapon__Fire_7429F2);
			
		CPatch::RedirectCode(0x73FC4E, &patch_CWeapon__FireInstantHit_73FC4E);			
		CPatch::RedirectCode(0x740B71, &patch_CWeapon__FireInstantHit_740B71);
		CPatch::RedirectCode(0x740BEA, &patch_CWeapon__FireInstantHit_740BEA);
		CPatch::RedirectCode(0x740C6C, &patch_CWeapon__FireInstantHit_740C6C);
		CPatch::RedirectCode(0x740FBF, &patch_CWeapon__FireInstantHit_740FBF);	

		CPatch::RedirectCode(0x73DBA5, &patch_CWeapon__Update_73DBA5);
		CPatch::RedirectCode(0x73DC75, &patch_CWeapon__Update_73DC75);
		CPatch::RedirectCode(0x73DEC0, &patch_CWeapon__Update_73DEC0);
		CPatch::RedirectCode(0x73DB89, &patch_CWeapon__Update_73DB89);
		
		CPatch::RedirectCode(0x73AD10, &patch_CWeapon__FireSniper_73AD10);
		CPatch::RedirectCode(0x73ADD0, &patch_CWeapon__FireSniper_73ADD0);
						
		CPatch::RedirectCode(0x737CAC, &patch_CProjectileInfo__AddProjectile_737CAC);
		CPatch::RedirectCode(0x737E47, &patch_CProjectileInfo__AddProjectile_737E47);
		CPatch::RedirectCode(0x737F64, &patch_CProjectileInfo__AddProjectile_737F64);
		CPatch::RedirectCode(0x738086, &patch_CProjectileInfo__AddProjectile_738086);
		CPatch::RedirectCode(0x73839B, &patch_CProjectileInfo__AddProjectile_73839B);
		CPatch::RedirectCode(0x73866A, &patch_CProjectileInfo__AddProjectile_73866A);
		CPatch::RedirectCode(0x738716, &patch_CProjectileInfo__AddProjectile_738716);

		CPatch::RedirectCode(0x738B97, &patch_CProjectileInfo__Update_738B97);
		CPatch::RedirectCode(0x738BFF, &patch_CProjectileInfo__Update_738BFF);
		CPatch::RedirectCode(0x738C63, &patch_CProjectileInfo__Update_738C63);
		CPatch::RedirectCode(0x738F31, &patch_CProjectileInfo__Update_738F31);
		CPatch::RedirectCode(0x738F99, &patch_CProjectileInfo__Update_738F99);
		
		CPatch::RedirectCode(0x73988C, &patch_CProjectileInfo__IsProjectileInRange_73988C);

		CPatch::RedirectCode(0x7388F5, &patch_CProjectileInfo__RemoveProjectile_7388F5);
			
		CPatch::RedirectCode(0x738877, &patch_CProjectileInfo__RemoveProjectile_738877);			

		CPatch::RedirectCode(0x737C00, &patch_CProjectileInfo_RemoveNotAdd_737C00);

		CPatch::RedirectFunction(0x73B240, &CWeapon::CanBeUsedFor2Player);

		CPatch::RedirectMethod(0x73B2A0, &CWeapon::HasWeaponAmmoToBeUsed);		
		
		CPatch::RedirectCode(0x685B45, &patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_685B45);			
		CPatch::RedirectCode(0x685AEC, &patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_685AEC);
		CPatch::RedirectCode(0x6861C6, &patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_6861C6);			
		CPatch::RedirectCode(0x68649B, &patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_68649B);		

		CPatch::RedirectCode(0x68883F, &patch_CTaskSimplePlayerOnFoot__ProcessPed_68883F);

		CPatch::RedirectCode(0x73EB52, &patch_CWeapon__FireAreaEffect_73EB52);		
			
		CPatch::RedirectCode(0x73E696, &patch_CWeapon__DoWeaponEffect_73E696);

		CPatch::RedirectCode(0x43D9E9, &patch_CDarkel__CheckDamagedWeaponType_43D9E9);

		CPatch::RedirectCode(0x73BA19, &patch_CWeapon__DoBulletImpact_73BA19);
		CPatch::RedirectCode(0x73B71D, &patch_CWeapon__DoBulletImpact_73B71D);
		CPatch::RedirectCode(0x73BF29, &patch_CWeapon__DoBulletImpact_73BF29);

		CPatch::RedirectCode(0x5E3B60, &patch_CPed__GetWeaponSkill_5E3B60);
		CPatch::RedirectCode(0x5E3BE7, &patch_CPed__GetWeaponSkill_5E3BE7);

		CPatch::RedirectCode(0x73CBF1, &patch_CWeapon__FireInstantHitFromCar2_73CBF1);
		CPatch::RedirectCode(0x73B36A, &patch_CWeapon__StopWeaponEffect_73B36A);

		CPatch::RedirectCode(0x73A4D7, patch_CWeapon__AddGunshell_73A4D7);
			
		CPatch::RedirectCode(0x5448BB, &patch_CPhysical__CanPhysicalBeDamaged_5448BB);
						
		CPatch::RedirectCode(0x4B35FF, &patch_CEventDamage__AffectsPed_4B35FF);
		CPatch::RedirectCode(0x4B363E, &patch_CEventDamage__AffectsPed_4B363E);
		CPatch::RedirectCode(0x4B368D, &patch_CEventDamage__AffectsPed_4B368D);
		CPatch::RedirectCode(0x4B36C4, &patch_CEventDamage__AffectsPed_4B36C4);
		CPatch::RedirectCode(0x4B36F4, &patch_CEventDamage__AffectsPed_4B36F4);
		CPatch::RedirectCode(0x4B3726, &patch_CEventDamage__AffectsPed_4B3726);
		CPatch::RedirectCode(0x4B3869, &patch_CEventDamage__AffectsPed_4B3869);
		CPatch::RedirectCode(0x4B3885, &patch_CEventDamage__AffectsPed_4B3885);

		CPatch::RedirectCode(0x6A6DE5, patch_CAutomobile__dmgDrawCarCollidingParticles_6A6DE5);

		CPatch::RedirectCode(0x6A7D67, &patch_CAutomobile__VehicleDamage_6A7D67);
		CPatch::RedirectCode(0x43DDD2, &patch_CDarkel__RegisterKillByPlayer_43DDD2);

		CPatch::RedirectCode(0x4B5C35, &patch_CPedDamageResponseCalculator__ComputeDamageResponse_4B5C35);

		CPatch::RedirectCode(0x4AD4A2, &patch_CPedDamageResponseCalculator__AccountForPedDamageStats_4AD4A2);
		CPatch::RedirectCode(0x4AD517, &patch_CPedDamageResponseCalculator__AccountForPedDamageStats_4AD517);
		CPatch::RedirectCode(0x4AD56F, &patch_CPedDamageResponseCalculator__AccountForPedArmour_4AD56F);
			
		CPatch::RedirectCode(0x4B322E, &patch_CPedDamageResponseCalculator__ComputeWillKillPed_4B322E);
		CPatch::RedirectCode(0x4B3260, &patch_CPedDamageResponseCalculator__ComputeWillKillPed_4B3260);
		CPatch::RedirectCode(0x4B3282, &patch_CPedDamageResponseCalculator__ComputeWillKillPed_4B3282);
		CPatch::RedirectCode(0x4B3327, &patch_CPedDamageResponseCalculator__ComputeWillKillPed_4B3327);

		CPatch::RedirectCode(0x58E1A7, &patch_CHud__DrawCrossHairs_58E1A7);
		CPatch::RedirectCode(0x58E6D1, &patch_CHud__DrawCrossHairs_58E6D1);
		CPatch::RedirectCode(0x58E6F9, &patch_CHud__DrawCrossHairs_58E6F9);

		CPatch::RedirectCode(0x521624, &patch_CCam__Process_AimWeapon_521624);
		CPatch::RedirectCode(0x521BA1, &patch_CCam__Process_AimWeapon_521BA1);
		CPatch::RedirectCode(0x522BAA, &patch_CCam__Process_AimWeapon_522BAA);

		CPatch::RedirectCode(0x589407, &patch_CHud__DrawWeaponAmmo_589407);
		CPatch::RedirectCode(0x589588, &patch_CHud__DrawWeaponAmmo_589588);
		CPatch::RedirectCode(0x5895AE, &patch_CHud__DrawWeaponAmmo_5895AE);

		CPatch::RedirectCode(0x60D9FA, &patch_CPlayerPed__ProcessWeaponSwitch_60D9FA);
		CPatch::RedirectCode(0x60DA53, &patch_CPlayerPed__ProcessWeaponSwitch_60DA53);

		CPatch::RedirectCode(0x60DE17, &CPlayerPed__KeepAreaAroundPlayerClear_60DE17);

		CPatch::RedirectCode(0x60EBE2, &patch_CPlayerPed__ProcessControl_60EBE2);
		CPatch::RedirectCode(0x60ED23, &patch_CPlayerPed__ProcessControl_60ED23);
		CPatch::RedirectCode(0x60F24D, &patch_CPlayerPed__ProcessControl_60F24D);

		CPatch::RedirectCode(0x53E2D2, &patch_Render2dStuff_53E2D2);		
	
		CPatch::RedirectCode(0x43D497, &patch_CDarkel__StartFrenzy_43D497);
		CPatch::RedirectCode(0x5E7D98, &patch_CPed__AttachPedToEntity_5E7D98);

		CPatch::RedirectCode(0x4C0ED2, &patch_CEventHandler__ComputeVehiclePotentialCollisionResponse_4C0ED2);

		CPatch::RedirectCode(0x521624, &patch_Cam__Process_AimWeapon_521624);		

		CPatch::RedirectCode(0x553D1C, &patch_CRenderer__RenderFirstPersonVehicle_553D1C);			

		CPatch::RedirectCode(0x55B3DD, &patch_CStats__BuildStatLine_55B3DD);
		CPatch::RedirectCode(0x55B427, &patch_CStats__BuildStatLine_55B427);

		CPatch::RedirectCode(0x576D89, &patch_CMenuManager__InitForPause_576D89);

		CPatch::RedirectCode(0x58A5B9, &patch_CHud__DrawRadar_58A5B9);

		CPatch::RedirectCode(0x58E7B1, &patch_CHud__DrawCrossHairs_58E7B1);

		CPatch::RedirectCode(0x60983A, &patch_CPlayerPed__UpdateCameraWeaponModes_60983A);
			
		CPatch::RedirectCode(0x609D0E, &patch_CPlayerPed__GetWeaponRadiusOnScreen_609D0E);

		CPatch::RedirectCode(0x61CD5C, &patch_CTaskSimpleFight__FightHitPed_61CD5C);

		CPatch::RedirectCode(0x61D101, &patch_CTaskSimpleFight__FightHitCar_61D101);

		CPatch::RedirectCode(0x629C5F, &patch_CTaskSimpleFight__ProcessPed_629C5F);

		CPatch::RedirectCode(0x68BAF1, &patch_CTaskComplexPolicePursuit__SetWeapon_68BAF1);

		CPatch::RedirectCode(0x732FCB, &patch_CVisibilityPlugins__RenderWeaponPedsForPC_732FCB);

		CPatch::RedirectCode(0x61AFD6, &patch_CTaskSimplePlayHandSignalAnim__StartAnim_61AFD6);
		
		CPatch::RedirectCode(0x61C7AA, &patch_CTaskSimpleFight__GetStrikeDamage_61C7AA);

		CPatch::RedirectCode(0x624143, &patch_CTaskSimpleFight__FightStrike_624143);

		CPatch::RedirectCode(0x5E6690, &patch_CPed__PreRenderAfterTest_5E6690);

		CPatch::RedirectCode(0x5E94E4, &patch_CPed__ProcessControl_5E94E4);

		CPatch::RedirectCode(0x6011BC, &patch_CPedIntelligence__GetUsingParachute_6011BC);

		CPatch::RedirectCode(0x60B94F, &patch_CPlayerPed__Compute3rdPersonMouseTarget_60B94F);

		CPatch::RedirectCode(0x61D37A, &patch_CTaskSimpleFight__FightHitCar_61D37A);

		CPatch::RedirectCode(0x61D587, &patch_CTaskSimpleFight__FightHitObj_61D587);

		CPatch::RedirectCode(0x625B0B, &CTaskSimpleThrowProjectile__StartAnim_625B0B);
			
		CPatch::RedirectCode(0x62A203, &patch_CTaskSimpleFightCtrl__processPed_62A203);

		CPatch::RedirectCode(0x641408, &patch_CTask_86E828__m18_641408);

		CPatch::RedirectCode(0x685BBF, &patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_685BBF);
		CPatch::RedirectCode(0x685F25, &patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_685F25);
		CPatch::RedirectCode(0x686466, &patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_686466);
		CPatch::RedirectCode(0x686B38, &patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_686B38);
		CPatch::RedirectCode(0x692662, &patch_692662);
	
		CPatch::RedirectCode(0x733041, &patch_CVisibilityPlugins__RenderWeaponPedsForPC_733041);

		CPatch::RedirectCode(0x738F68, &patch_CProjectileInfo__Update_738F68);

		CPatch::RedirectCode(0x459210, &patch_CPed__CreateDeadPedWeaponPickups_459210);

		CPatch::RedirectCode(0x6D7DBA, &patch_CVehicle__InflictDamage_6D7DBA);
		CPatch::RedirectCode(0x6D7FF4, &patch_CVehicle__InflictDamage_6D7FF4);
		CPatch::RedirectCode(0x6D8241, &patch_CVehicle__InflictDamage_6D8241);

		

		CPatch::RedirectCode(0x4B4023, &patch_CEventDamage__ComputeDamageAnim_4B4023);
		CPatch::RedirectCode(0x4B3FF6, &patch_CEventDamage__ComputeDamageAnim_4B3FF6);
		CPatch::RedirectCode(0x4B4231, &patch_CEventDamage__ComputeDamageAnim_4B4231);
		CPatch::RedirectCode(0x4B4366, &patch_CEventDamage__ComputeDamageAnim_4B4366);
		CPatch::RedirectCode(0x4B446C, &patch_CEventDamage__ComputeDamageAnim_4B446C);
		CPatch::RedirectCode(0x4B44AF, &patch_CEventDamage__ComputeDamageAnim_4B44AF);
		CPatch::RedirectCode(0x4B4405, &patch_CEventDamage__ComputeDamageAnim_4B4405);

		CPatch::RedirectCode(0x4B3AE8, &patch_CEventDamage__ComputeDeathAnim_4B3AE8);
		CPatch::RedirectCode(0x4B3C33, &patch_CEventDamage__ComputeDeathAnim_4B3C33);
		CPatch::RedirectCode(0x4B3E0E, &patch_CEventDamage__ComputeDeathAnim_4B3E0E);


		CPatch::RedirectCode(0x4ADD67, &patch_CEventDamage__ComputeHeadShot_4ADD67);

		CPatch::RedirectCode(0x4ADC1E, &patch_CEventDamage__ComputeBodyPartToRemove_4ADC1E);

		CPatch::RedirectCode(0x4C0265, &patch_CEventHandler__ComputeDamageResponse_4C0265);
		CPatch::RedirectCode(0x4C03EC, &patch_CEventHandler__ComputeDamageResponse_4C03EC);
		CPatch::RedirectCode(0x4C0B66, &patch_CEventHandler__ComputeDamageResponse_4C0B66);
		CPatch::RedirectCode(0x4C01AC, &patch_CEventHandler__ComputeDamageResponse_4C01AC);
		CPatch::RedirectCode(0x4C0A39, &patch_CEventHandler__ComputeDamageResponse_4C0A39);

		CPatch::RedirectCode(0x68595D, &patch_CTaskSimpleProcessPlayerWeapon__m18_68595D);

		CPatch::RedirectCode(0x457A33, &patch_CPickup__Update_457A33);	

		CPatch::RedirectCode(0x5E5F7B, &patch_CPed__AddWeaponModel_5E5F7B);

		CPatch::RedirectCode(0x5E8D08, &patch_CPed__ProcessControl_5E8D08);
			
		CPatch::RedirectCode(0x5E6031, &patch_CPed__TakeOffGoggles_5E6031);			
		CPatch::RedirectCode(0x5E3B01, &patch_CPed__PutOnGoggles_5E3B01);
			
		CPatch::RedirectCode(0x5E6384, &patch_CPed__RemoveWeaponWhenEnteringVehicle_5E6384);			
		CPatch::RedirectCode(0x5E63B9, &patch_CPed__RemoveWeaponWhenEnteringVehicle_5E63B9);
		CPatch::RedirectCode(0x5E63ED, &patch_CPed__RemoveWeaponWhenEnteringVehicle_5E63ED);
		CPatch::RedirectCode(0x5E6405, &patch_CPed__RemoveWeaponWhenEnteringVehicle_5E6405);


		CPatch::RedirectCode(0x4B38D4, &patch_CEventDamage__AffectsPedGroup_4B38D4);
		CPatch::RedirectCode(0x4ADAF2, &patch_CEventDamage__DoInformVehicleOccupants_4ADAF2);

		CPatch::RedirectCode(0x4B3470, &patch_CEventDamage__ReportCriminalEvent_4B3470);

		CPatch::RedirectCode(0x4AD631, &patch_CPedDamageResponseCalculator__ComputeWillForceDeath_4AD631);
		CPatch::RedirectCode(0x4AD6DF, &patch_CPedDamageResponseCalculator__ComputeWillForceDeath_4AD6DF);			

		CPatch::RedirectCode(0x4E6B22, &patch_CAEPedWeaponAudioEntity__Service_4E6B22);	

		CPatch::RedirectCode(0x601AAD, &patch_CPedIntelligence__ProcessAfterPreRender_601AAD);

			
		CPatch::RedirectCode(0x741905, &patch_CWeapon__FireProjectile_741905);
		CPatch::RedirectCode(0x741379, &patch_CWeapon__FireProjectile_741379);
		CPatch::PatchMemoryData(0x74138B, "\x83\xf8\x24", 3);

		CPatch::NOPinstructions(0x7415EB, 8);
		CPatch::RedirectCode(0x741607, &patch_CWeapon__FireProjectile_741607);

		CPatch::RedirectCode(0x7416D9, &patch_CWeapon__FireProjectile_7416D9);
		CPatch::RedirectCode(0x7417BB, &patch_CWeapon__FireProjectile_7417BB);			
		CPatch::RedirectCode(0x741A1B, &patch_CWeapon__FireProjectile_741A1B);
		CPatch::RedirectCode(0x741AF4, &patch_CWeapon__FireProjectile_741AF4);			

		CPatch::RedirectCode(0x73A03E, &patch_CShotInfo__Update_73A03E);
		CPatch::RedirectCode(0x73A0D9, &patch_CShotInfo__Update_73A0D9);

		CPatch::RedirectCode(0x736484, &patch_CBulletInfo__Update_736484);
		CPatch::RedirectCode(0x7366C4, &patch_CBulletInfo__Update_7366C4);
		CPatch::NOPinstructions(0x73677C, 4);
		CPatch::RedirectCode(0x73679F, &patch_CBulletInfo__Update_73679F);

		CPatch::RedirectCode(0x609974, &patch_CPlayerPed__ProcessAnimGroups_609974);

		CPatch::RedirectCode(0x5E6305, &patch_CPed__ClearWeapon_5E6305);			

		if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		{
			Address_CGarages__GivePlayerDetonator_ifEqual = 0x1569BE3;
			Address_CGarages__GivePlayerDetonator_ifNotEqual = 0x1569BD9;

			CPatch::RedirectCode(0x1569BD0, &patch_CGarages__GivePlayerDetonator_1569BD0);
		}
		else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
		{
			Address_CGarages__GivePlayerDetonator_ifEqual = 0x4486B3;
			Address_CGarages__GivePlayerDetonator_ifNotEqual = 0x4486A9;

			CPatch::RedirectCode(0x4486A0, &patch_CGarages__GivePlayerDetonator_1569BD0);
		}

		CPatch::RedirectCode(0x5E7D34, &patch_CPed__AttachPedToEntity_5E7D34);

		CPatch::RedirectCode(0x43D7B6, &patch_CDarkel__DealWithWeaponChangeAtEndOfFrenzy_43D7B6);

		CPatch::RedirectFunction(0x565800, &CWorld__SetPedsChoking);
		CPatch::RedirectCode(0x5659C8, &patch_CWorld__SetPedsChoking_5659C8);

		CPatch::RedirectCode(0x738C47, &patch_CProjectileInfo__Update_738C47);

		CPatch::RedirectCode(0x60C171, &patch_CPlayerPed__FindSprayableBuilding_60C171);
#endif
	}
	#endif
		

#if 1
	// Pickup fix
	#if TRUE
	{
		CPatch::EnterNewLevelAndDisableDebugState();

		CPatch::PatchPointer(0x45593B + 4, aAaaa.ptr + 47);
		CPatch::PatchPointer(0x45590C + 4, aAaaa.ptr + 53);
		CPatch::PatchPointer(0x4558A3 + 4, aAaaa.ptr + 48);

		CPatch::NOPinstructions(0x455ACF, 5);
		CPatch::RedirectCode(0x455ADA, &patch_CPickups__DoPickUpEffects_455ADA);
		CPatch::PutCallFunction(0x45592D, &CPickups::GetWeaponModelEffectInfo);

		CPatch::RedirectCode(0x5361F5, &patch_CEntity__PreRender_5361F5);
		CPatch::RedirectCode(0x53654B, &patch_CEntity__PreRender_53654B);		

		CPatch::LeaveThisLevel();
	}
	#endif
		
	// Jetpacks
	#if TRUE
	{
		CPatch::RedirectCode(0x67B59E, &patch_CTaskSimpleJetPack__CTaskSimpleJetPack_67B59E);
		CPatch::RedirectCode(0x67B5C0, &patch_CTaskSimpleJetPack__ProcessAnims_67B5C0);
		CPatch::RedirectCode(0x67B5E4, &patch_CTaskSimpleJetPack__ProcessAnims_67B5E4);

		CPatch::RedirectMethod(0x5E6080, &CPed::GiveWeapon);

		CPatch::RedirectCode(0x67B6C8, &patch_CTaskSimpleJetPack__DropJetPack_67B6C8);
		CPatch::RedirectCode(0x67C6C3, &patch_CTaskSimpleJetPack__Clone_67C6C3);

		CPatch::RedirectCode(0x58D917, &patch_CHud__DrawWeaponIcon_58D917);

		// Patch sizeof(CTaskSimpleJetPack)
		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT8(0x439631 + 1, sizeof(CTaskSimpleJetPack));
		CPatch::PatchUINT8(0x4566E9 + 1, sizeof(CTaskSimpleJetPack));
		CPatch::PatchUINT8(0x46C158 + 1, sizeof(CTaskSimpleJetPack));
		CPatch::PatchUINT8(0x67C6A7 + 1, sizeof(CTaskSimpleJetPack));
		CPatch::LeaveThisLevel();
	}
	#endif

	// Binoculars
	#if TRUE
	{
		CPatch::RedirectCode(0x5E3ACB, &patch_CPed__AddGogglesModel_5E3ACB);
		CPatch::RedirectCode(0x686897, &patch_CTaskSimplePlayerOnFoot__ProcessPlayerWeapon_686897);
		CPatch::RedirectCode(0x701112, &CPostEffects__ScriptResetForEffects_Init);
	}
	#endif

	// Gun aiming offset patches
	#if TRUE
	{
		CPatch::RedirectCode(0x5BE670, &patch_CWeaponInfo__LoadWeaponData_5BE670);
		CPatch::RedirectCode(0x5BEC71, &patch_CWeaponInfo__LoadWeaponData_5BEC71);
		CPatch::RedirectCode(0x5BEAE2, &patch_CWeaponInfo__LoadWeaponData_5BEAE2);
		CPatch::RedirectCode(0x5BE765, &patch_CWeaponInfo__LoadWeaponData_5BE765);


		CPatch::RedirectCode(0x5BECCA, &patch_CWeaponInfo__LoadWeaponData_5BECCA);
		CPatch::NOPinstructions(0x5BED25, 3);
	}
	#endif

	// Errors
	#if TRUE
	{
		CPatch::PutCallFunction(0x5BE74C, &FindWeaponWithPossibleWarning);
		CPatch::PutCallFunction(0x5BE968, &FindWeaponWithPossibleWarning);
	}
	#endif
#endif

	// Extend count of weapon infos
	{
		// Define variables for automatic patch
		CCodeMover::SetVariable("COUNT_OF_WEAPON_INFOS", CountOfWeaponInfos);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 2
			CCodeMover::FixOnAddressRel(0x855E1A, 9, "\x01\x01\x68\x05\x04""COUNT_OF_WEAPON_INFOS\x00\x02\x02\x1C\x5E\x85\x00\x02\x05\x1E\x5E\x85\x00\x00", 0x855E23);	// line 1, 0x855E10 - sub_855E10 : push    80              ; count
			CCodeMover::FixOnAddressRel(0x856C65, 9, "\x01\x01\x68\x05\x04""COUNT_OF_WEAPON_INFOS\x00\x02\x02\x67\x6C\x85\x00\x02\x05\x69\x6C\x85\x00\x00", 0x856C6E);	// line 2, 0x856C60 - sub_856C60 : push    80              ; count
		}
		#endif

		// Delete variables
		CCodeMover::DeleteVariable("COUNT_OF_WEAPON_INFOS");
	}

	// Extend the weapon ID
	if(this->bWeaponIDsizeExtended)
	{
		tVariableValue variable;
		variable.Array.pItems = WeaponIDaccessPatches::ptrArray;
		variable.Array.count = _countof(WeaponIDaccessPatches::ptrArray);
		CCodeMover::SetVariable("PATCH_PTR_ARRAY", variable);

		#if TRUE
		{
			// Count of active addresses: 22
			CCodeMover::FixOnAddressRel(0x47637A, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x7A\x63\x47\x00\x00", 0x476381);	// line 1, 0x4762D0 - _opcode_handler_23 : movsx   eax, byte ptr [eax+148h]
			CCodeMover::FixOnAddressRel(0x476388, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x88\x63\x47\x00\x00", 0x47638F);	// line 2, 0x4762D0 - _opcode_handler_23 : movsx   ecx, byte ptr [eax+148h]
			CCodeMover::FixOnAddressRel(0x4763DD, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xDD\x63\x47\x00\x00", 0x4763E4);	// line 3, 0x4762D0 - _opcode_handler_23 : mov     byte ptr [eax+148h], 0FFh
			CCodeMover::FixOnAddressRel(0x480E48, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x48\x0E\x48\x00\x00", 0x480E4F);	// line 4, 0x47FA30 - sub_47FA30 : movsx   edx, byte ptr [eax+760h]
			CCodeMover::FixOnAddressRel(0x480E55, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x55\x0E\x48\x00\x00", 0x480E5C);	// line 5, 0x47FA30 - sub_47FA30 : movsx   eax, byte ptr [eax+760h]
			CCodeMover::FixOnAddressRel(0x480EBE, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xBE\x0E\x48\x00\x00", 0x480EC5);	// line 6, 0x47FA30 - sub_47FA30 : movsx   eax, byte ptr [eax+508h]
			CCodeMover::FixOnAddressRel(0x480ECC, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xCC\x0E\x48\x00\x00", 0x480ED3);	// line 7, 0x47FA30 - sub_47FA30 : movsx   ecx, byte ptr [eax+508h]
			CCodeMover::FixOnAddressRel(0x48A925, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x25\xA9\x48\x00\x00", 0x48A92C);	// line 8, 0x48A320 - sub_48A320 : mov     byte ptr [eax+760h], 0FFh
			CCodeMover::FixOnAddressRel(0x48A95E, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x5E\xA9\x48\x00\x00", 0x48A965);	// line 9, 0x48A320 - sub_48A320 : mov     byte ptr [eax+508h], 0FFh
			CCodeMover::FixOnAddressRel(0x4B5C78, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x78\x5C\x4B\x00\x00", 0x4B5C7E);	// line 10, 0x4B5AC0 - sub_4B5AC0 : mov     [edi+760h], al
			CCodeMover::FixOnAddressRel(0x5429C5, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xC5\x29\x54\x00\x00", 0x5429CC);	// line 11, 0x5428C0 - _ZN9CPhysical21SetDamagedPieceRecordEfP7CEntityR9CColPointf : cmp     byte ptr [esi+148h], 0FFh
			CCodeMover::FixOnAddressRel(0x5429D5, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xD5\x29\x54\x00\x00", 0x5429DB);	// line 12, 0x5428C0 - _ZN9CPhysical21SetDamagedPieceRecordEfP7CEntityR9CColPointf : mov     [esi+148h], al
			CCodeMover::FixOnAddressRel(0x548096, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x96\x80\x54\x00\x00", 0x54809D);	// line 13, 0x547B80 - sub_547B80 : cmp     byte ptr [esi+148h], 0FFh
			CCodeMover::FixOnAddressRel(0x5480A7, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xA7\x80\x54\x00\x00", 0x5480AD);	// line 14, 0x547B80 - sub_547B80 : mov     [esi+148h], dl
			CCodeMover::FixOnAddressRel(0x59F991, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x91\xF9\x59\x00\x00", 0x59F998);	// line 15, 0x59F840 - sub_59F840 : mov     byte ptr [esi+148h], 0FFh
			CCodeMover::FixOnAddressRel(0x5A0ED8, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xD8\x0E\x5A\x00\x00", 0x5A0EDE);	// line 16, 0x40191E - sub_40191E : mov     [esi+148h], bl
			CCodeMover::FixOnAddressRel(0x5E83F2, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xF2\x83\x5E\x00\x00", 0x5E83F9);	// line 17, 0x5E8030 - sub_5E8030 : mov     byte ptr [esi+760h], 0FFh
			CCodeMover::FixOnAddressRel(0x61D35A, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x5A\xD3\x61\x00\x00", 0x61D360);	// line 18, 0x61D0B0 - sub_61D0B0 : mov     [esi+508h], al
			CCodeMover::FixOnAddressRel(0x6A7AE3, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE3\x7A\x6A\x00\x00", 0x6A7AEA);	// line 19, 0x6A7650 - sub_6A7650 : mov     byte ptr [esi+508h], 31h
			CCodeMover::FixOnAddressRel(0x6B8F9E, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x9E\x8F\x6B\x00\x00", 0x6B8FA5);	// line 20, 0x6B8EC0 - sub_6B8EC0 : mov     byte ptr [esi+508h], 31h
			CCodeMover::FixOnAddressRel(0x6D60B9, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xB9\x60\x6D\x00\x00", 0x6D60BF);	// line 21, 0x6D5F10 - sub_6D5F10 : mov     [esi+508h], al
			CCodeMover::FixOnAddressRel(0x6D8037, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x37\x80\x6D\x00\x00", 0x6D803D);	// line 22, 0x6D7C97 - sub_6D7C97 : mov     [esi+508h], bl
		}
		#endif

		CCodeMover::DeleteVariable("PATCH_PTR_ARRAY");

		// mov     al, [esi + CPedDamageResponseCalculator.weaponType]
		// INTO:
		// mov     eax, [esi + CPedDamageResponseCalculator.weaponType]
		CPatch::PatchMemoryData(0x4B5C75, "\x8b\x46\x0c", 3);

		CPatch::RedirectCode(0x5429CC, &WeaponIDaccessPatches::patch_5429CC);
		CPatch::RedirectCode(0x54809D, &WeaponIDaccessPatches::patch_54809D);

		CGenericLogStorage::SaveFormattedTextLn(
			"Number of weapon types over 255 and requires something more than uint8_t."
			" Applying weapon ID uint32_t patches."
		);
	}

	// Print to log
	CGenericLogStorage::SaveFormattedTextLn(
		"Weapon type loader is enabled. NumberOfWeaponTypes = %d.",
		NumberOfWeaponTypes
		);

	CPatch::LeaveThisLevel();
#endif
}

// Loads weapon types
void WeaponLimits::LoadWeaponTypes()
{
	MAKE_VAR_GAME_VERSION();

	if (!CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		return;

	using namespace Game_GTASA;

	const char* filename = "data\\gtasa_weapon_config.dat";

	FILE* fp = fopen(g_LimitAdjuster.GetPathToFlaFileFromRootDirectory(filename).c_str(), "r");

	if (!fp)
	{
		printf_MessageBox("Unable to load %s", filename);
		g_LimitAdjuster.TerminateProcess();
	}

	char line[512];

	int weaponTypeID;
	char weaponTypeName[32];
	int statIndex;
	int bCanBeUsedForSecondPlayer;
	int bHasWeaponAmmoToBeUsed;
	int varAmmoForWeapon_OnStreet;
	int PickupMsgColorRed;
	int PickupMsgColorGreen;
	int PickupMsgColorBlue;
	float PickupMsgUnk4;
	int parentWeaponTypeID;
	char parentWeaponTypeName[32];

	while (LoadLineWithoutCommas(line, sizeof(line), fp))
	{
		char* iLine = FindFirstNonWhiteCharacter(line);

		if (!iLine[0] || iLine[0] == '#')
			continue;

		if (iLine[0] == '!')
		{
			char sign[64];
			char command[32];

			sscanf(iLine, "%s %s", sign, command);

			if (!_stricmp(command, "SET_ASSOCIATED_WEAPON"))
			{
				char firstWeaponName[32];
				char secondWeaponName[32];

				sscanf(iLine, "%s %s %s %s", sign, command, firstWeaponName, secondWeaponName);

				int firstWeaponID = CWeaponInfo::FindWeaponType(firstWeaponName);

				if (firstWeaponID < 0)
				{
					printf_MessageBox("Weapon with name %s cannot be found.", firstWeaponName);
					continue;
				}

				int secondWeaponID = CWeaponInfo::FindWeaponType(secondWeaponName);

				if (secondWeaponID < 0)
				{
					printf_MessageBox("Weapon with name %s cannot be found.", secondWeaponName);
					continue;
				}

				WeaponTypes[firstWeaponID].AssociatedWeaponID = secondWeaponID;
			}
			else
				printf_MessageBox("Unknown weapon command: %s", command);
		}
		else
		{
			weaponTypeName[0] = 0;
			parentWeaponTypeName[0] = 0;

			sscanf(
				line,
				"%d %s %d %d %d %d %d %d %d %f %s",
				&weaponTypeID,
				weaponTypeName,
				&statIndex,
				&bCanBeUsedForSecondPlayer,
				&bHasWeaponAmmoToBeUsed,
				&varAmmoForWeapon_OnStreet,
				&PickupMsgColorRed,
				&PickupMsgColorGreen,
				&PickupMsgColorBlue,
				&PickupMsgUnk4,
				parentWeaponTypeName
				);

			if (!weaponTypeName[0])
				continue;

			if (weaponTypeID == -1)
				weaponTypeID = CWeaponInfo::FindFirstFreeWeaponType();

			if (weaponTypeID < 0 || weaponTypeID >= NumberOfWeaponTypes)
			{
				printf_MessageBox(
					"Weapon type ID must be less than than %d. Read value = %d",
					NumberOfWeaponTypes,
					weaponTypeID
					);

				g_LimitAdjuster.TerminateProcess();
			}

			tWeaponTypeInfo* pInfo = WeaponLimits::WeaponTypes + weaponTypeID;

			if (pInfo->Subset != WEAPON_SUBSET_UNUSED)
			{
				printf_MessageBox("Weapon ID %d is already registered.", weaponTypeID);
				continue;
			}

			if (statIndex >= 0)
				pInfo->Subset = WEAPON_SUBSET_MULTIPLE_SKILLS;
			else
				pInfo->Subset = WEAPON_SUBSET_ONLY_STANDARD_SKILL;

			pInfo->statIndex = statIndex;

			strncpy(pInfo->Name, weaponTypeName, _countof(pInfo->Name));

			pInfo->bCanBeUsedForSecondPlayer = bCanBeUsedForSecondPlayer != 0;
			pInfo->bHasWeaponAmmoToBeUsed = bHasWeaponAmmoToBeUsed != 0;

			pInfo->AmmoForWeapon_OnStreet = varAmmoForWeapon_OnStreet;

			pInfo->PickupMessageInfo.red = PickupMsgColorRed;
			pInfo->PickupMessageInfo.green = PickupMsgColorGreen;
			pInfo->PickupMessageInfo.blue = PickupMsgColorBlue;
			pInfo->PickupMessageInfo.float_4 = PickupMsgUnk4;

			if (parentWeaponTypeName[0])
			{
				parentWeaponTypeID = CWeaponInfo::FindWeaponType(parentWeaponTypeName);

				if (parentWeaponTypeID < 0)
				{
					printf_MessageBox("Weapon with name %s cannot be found.", parentWeaponTypeName);
					continue;
				}

				pInfo->ParentWeaponID = parentWeaponTypeID;

				if (CWeaponInfo::IsWeaponParentTypeRecursive(weaponTypeID))
				{
					printf_MessageBox("Weapon with name %s has recursive parent type.", weaponTypeName);
					continue;
				}
			}
			else
				pInfo->ParentWeaponID = -1;
		}
	}

	fclose(fp);
}

class CMeleeTypeInfo
{
public:
	// Returns melee parent type
	static int GetMeleeHighestParentType(int meleeType)
	{
		if (meleeType < g_weaponLimits.NumberOfUnarmedComboTypes
			|| meleeType >= g_weaponLimits.MaxNumberOfCombos)
			return meleeType;

		tComboDataEx* pInfo = g_weaponLimits.CTaskSimpleFight__m_aComboDataEx
			+ meleeType
			- g_weaponLimits.NumberOfUnarmedComboTypes;

		int resultID = meleeType;

		while (pInfo->parentID >= 0)
		{
			resultID = pInfo->parentID;

			pInfo = g_weaponLimits.CTaskSimpleFight__m_aComboDataEx
				+ resultID
				- g_weaponLimits.NumberOfUnarmedComboTypes;
		}

		return resultID;
	};

	// Finds melee type ID, specifying exact name
	static int FindMeleeTypeID_exactName(const char* name)
	{
		for (unsigned int i = 0; i < g_weaponLimits.MaxNumberOfCombosInArray; i++)
			if (!strcmp(g_weaponLimits.CTaskSimpleFight__m_aComboDataEx[i].name, name))
				return i + g_weaponLimits.NumberOfUnarmedComboTypes;

		return -1;
	}

	// Returns melee extra info by melee ID
	static tComboDataEx* GetMeleeExtraInfoByID(int meleeType)
	{
		return g_weaponLimits.CTaskSimpleFight__m_aComboDataEx
			+ meleeType
			- g_weaponLimits.NumberOfUnarmedComboTypes;
	}

	// Finds melee type ID for weapon DAT
	static int FindMeleeTypeIDforWeaponDAT(const char* name)
	{
		if (!strcmp(name, "UNARMED"))
			return 4;
		else
		{
			for (unsigned int i = 0; i < g_weaponLimits.MaxNumberOfCombosInArray; i++)
			{
				if (!strcmp(g_weaponLimits.CTaskSimpleFight__m_aComboDataEx[i].name, name))
					return i + g_weaponLimits.NumberOfUnarmedComboTypes;
			}

			return -1;
		}
	}
};

static unsigned int PISTOL_WHIP_ID = -1;

// Loads melee types
void WeaponLimits::LoadMeleeTypes()
{
	for (unsigned int i = 0; i < MaxNumberOfCombosInArray; i++)
	{
		CTaskSimpleFight__m_aComboDataEx[i].name[0] = 0;
		CTaskSimpleFight__m_aComboDataEx[i].parentID = -1;
	}

	const char* filename = "data\\gtasa_melee_config.dat";

	FILE* fp = fopen(g_LimitAdjuster.GetPathToFlaFileFromRootDirectory(filename).c_str(), "r");

	if (!fp)
	{
		printf_MessageBox("Unable to load %s", filename);
		g_LimitAdjuster.TerminateProcess();
	}

	char line[512];

	int meleeTypeID;
	char meleeTypeName[32];
	char parentMeleeTypeName[32];
	
	while (LoadLineWithoutCommas(line, sizeof(line), fp))
	{
		char* iLine = FindFirstNonWhiteCharacter(line);

		if (!iLine[0] || iLine[0] == '#')
			continue;

		meleeTypeName[0] = 0;
		parentMeleeTypeName[0] = 0;

		sscanf(
			line,
			"%d %s %s",
			&meleeTypeID,
			meleeTypeName,
			parentMeleeTypeName
			);

		if (!meleeTypeName[0])
			continue;

		if (meleeTypeID < 4 || meleeTypeID >= MaxNumberOfCombos)
		{
			printf_MessageBox(
				"Melee type ID must be higher or equal to 4 and lower than %d.",
				MaxNumberOfCombos,
				meleeTypeID,
				MaxNumberOfCombos
				);

			g_LimitAdjuster.TerminateProcess();
		}

		tComboDataEx* pInfo = CTaskSimpleFight__m_aComboDataEx + meleeTypeID - NumberOfUnarmedComboTypes;
			
		if (pInfo->name[0])
		{
			printf_MessageBox("Melee ID %d is already registered.", meleeTypeID);
			continue;
		}

		// Apply parent ID
		if (parentMeleeTypeName[0])
		{
			int parentID = CMeleeTypeInfo::FindMeleeTypeID_exactName(parentMeleeTypeName);

			if (parentID < 0)
			{
				printf_MessageBox(
					"Melee type with name %s cannot be found.",
					parentMeleeTypeName
				);
				continue;
			}

			pInfo->parentID = parentID;
		}
		else
			pInfo->parentID = -1;

		strncpy(pInfo->name, meleeTypeName, _countof(pInfo->name));
	}		

	fclose(fp);

	PISTOL_WHIP_ID = CMeleeTypeInfo::FindMeleeTypeID_exactName("PISTOL_WHIP");
	
	if (PISTOL_WHIP_ID == -1)
		printf_Error(true, "gtasa_weapon_config.dat: PISTOL_WHIP not found");
}

void InitializeMeleeNames()
{
	g_weaponLimits.LoadMeleeTypes();
}

int GetMeleeComboIDinLine(const char* line)
{
	char start[32];
	char comboName[32];

	// line example: START_COMBO	KNIFE
	sscanf(line, "%s %s", start, comboName);

	unsigned int ID = CMeleeTypeInfo::FindMeleeTypeID_exactName(comboName)
		- g_weaponLimits.NumberOfUnarmedComboTypes;
	
	/*
	Should be commented out, unless debugging.

	strncpy(
		g_weaponLimits.CTaskSimpleFight__m_aComboDataEx[ID].name,
		comboName,
		sizeof(g_weaponLimits.CTaskSimpleFight__m_aComboDataEx[ID].name)
		);
		*/

	return ID;
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_CTaskSimpleFight__LoadMeleeData_5BEDC0()
	{
		__asm
		{
			call InitializeMeleeNames;

			sub     esp, 80h;

			push 0x5BEDC6;
			retn;
		}
	}

	NAKED void patch_CTaskSimpleFight__LoadMeleeData_5BEFCE()
	{
		__asm
		{
			push esi;
			call GetMeleeComboIDinLine;
			add esp, 4;

			imul eax, SIZE tComboData;
			mov ebp, eax;

			mov[esp + 90h - 0x7E], 1;

			push 0x5BEFD3;
			retn;
		}
	}

	unsigned int CTaskSimpleFight__GetComboType(const char *name)
	{
		return CMeleeTypeInfo::FindMeleeTypeIDforWeaponDAT(name);
	}

	void SetVariablesAfterLoadingMeleeData(const char *name)
	{

	}

	NAKED void patch_CTaskSimpleFight__LoadMeleeData_40204B()
	{
		__asm
		{
			add     esp, 80h;
			jmp SetVariablesAfterLoadingMeleeData;
		}
	}

	NAKED void patch_CTaskSimpleUseGun__StartAnim_6251C0()
	{
		__asm
		{
			mov edx, PISTOL_WHIP_ID;
			sub edx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_weaponLimits, WeaponLimits, NumberOfUnarmedComboTypes);
			imul edx, SIZE tComboData;
			add edx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_weaponLimits, WeaponLimits, CTaskSimpleFight__m_aComboData);
			mov edx, [edx + tComboData::animGroupID];

			push 0x6251C6;
			retn;
		}
	}

	NAKED void patch_CTaskSimpleUseGun__ProcessPed_62A6BC()
	{
		__asm
		{
			mov edx, PISTOL_WHIP_ID;
			sub edx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_weaponLimits, WeaponLimits, NumberOfUnarmedComboTypes);
			imul edx, SIZE tComboData;
			add edx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_weaponLimits, WeaponLimits, CTaskSimpleFight__m_aComboData);
			fcomp   dword ptr[edx + tComboData::hitFlt + ebx * 4];

			fnstsw  ax;
			test    ah, 41h;
			jnz     loc_62A771;
			fld     dword ptr[ebp + 28h];
			fld     dword ptr[ebp + 20h];
			fsub    st, st(1);
			fcomp   dword ptr[edx + tComboData::hitFlt + ebx * 4];
			fnstsw  ax;
			fstp    st;
			test    cl, ah;
			jp      loc_62A771;

			movzx   eax, [edx + tComboData::hitlevel + ebx];

			push 0x62A6F0;
			retn;

		loc_62A771:
			push 0x62A771;
			retn;
		}
	}

	// melee ID checks
	static NAKED void patch_CTaskSimpleFight__BeHitWhileBlocking_61C6E1()
	{
		__asm
		{
			movzx     edx, byte ptr[esp + 8 + 0xC];

			push ecx;

			push edx;
			call CMeleeTypeInfo::GetMeleeHighestParentType;
			mov edx, eax;
			add esp, 4;
			
			pop ecx;

			cmp     dl, 8;

			// go back
			push 0x61C6E8;
			retn;
		}
	}

	// melee ID checks
	static NAKED void patch_CTaskSimpleFight__BeHitWhileBlocking_61C6F9()
	{
		__asm
		{
			movzx     eax, byte ptr[ecx + 24h];

			push edx;

			push eax;
			call CMeleeTypeInfo::GetMeleeHighestParentType;
			add esp, 4;

			pop edx;

			cmp     al, 8;

			// go back
			push 0x61C6FE;
			retn;
		}
	}

	static NAKED void patch_CTaskSimpleFight__FightHitPed_61CC77()
	{
		__asm
		{
			movzx eax, byte ptr[ebp + 24h];

			push eax;
			call CMeleeTypeInfo::GetMeleeHighestParentType;
			add esp, 4;

			cmp eax, 5;

			jnz     loc_61D092;

			push 0x61CC81;
			retn;

		loc_61D092:
			push 0x61D092;
			retn;
		}
	}

	static NAKED void patch_CTaskSimpleFight__FightHitPed_61CD84()
	{
		__asm
		{
			movzx     ecx, byte ptr[ebp + 24h];

			push ecx;
			call CMeleeTypeInfo::GetMeleeHighestParentType;
			mov ecx, eax;
			add esp, 4;

			cmp     cl, 5;

			push 0x61CD8A;
			retn;
		}
	}

	static NAKED void patch_CTaskSimpleFight__FightHitPed_61CE6C()
	{
		__asm
		{
			movzx eax, byte ptr[ebp + 24h];

			push eax;
			call CMeleeTypeInfo::GetMeleeHighestParentType;
			add esp, 4;

			cmp eax, 5;
			jnz     loc_61CEA4;

			push 0x61CE72;
			retn;

		loc_61CEA4:
			push 0x61CEA4;
			retn;
		}
	}

	static NAKED void patch_CTaskSimpleFight__FightHitPed_61CF0E()
	{
		__asm
		{
			movzx     eax, byte ptr[ebp + 24h];

			push eax;
			call CMeleeTypeInfo::GetMeleeHighestParentType;
			add esp, 4;

			cmp     al, 8;

			push 0x61CF13;
			retn;
		}
	}

	static NAKED void patch_CTaskSimpleFight__FightHitPed_61CFFB()
	{
		__asm
		{
			movzx     eax, byte ptr[ebp + 24h];

			push eax;
			call CMeleeTypeInfo::GetMeleeHighestParentType;
			add esp, 4;

			cmp     al, 8;

			push 0x61D000;
			retn;
		}
	}

	static NAKED void patch_CTaskSimpleFight__ProcessPed_629E44()
	{
		__asm
		{
			movzx eax, byte ptr[esi + 24h];

			push eax;
			call CMeleeTypeInfo::GetMeleeHighestParentType;
			add esp, 4;

			cmp eax, 5;

			jnz      loc_629E79;

			push 0x629E4A;
			retn;

		loc_629E79:
			push 0x629E79;
			retn;
		}
	}

	static NAKED void patch_CTaskSimpleFight__ProcessPed_629F66()
	{
		__asm
		{
			movzx eax, byte ptr[esi + 24h];			

			push eax;
			call CMeleeTypeInfo::GetMeleeHighestParentType;
			add esp, 4;

			cmp eax, 12;

			jnz     loc_629F93;

			push 0x629F6C;
			retn;

		loc_629F93:
			push 0x629F93;
			retn;
		}
	}

	static NAKED void patch_CTaskSimpleFightingControl__ProcessPed_62A33D()
	{
		__asm
		{
			movzx eax, byte ptr[ebp + 24h];

			push eax;
			call CMeleeTypeInfo::GetMeleeHighestParentType;
			add esp, 4;

			cmp eax, 1;

			jg      loc_62A354;

			push 0x62A343;
			retn;

		loc_62A354:
			push 0x62A354;
			retn;
		}
	}

	static NAKED void patch_CTaskSimpleFight__FightStrike_624664()
	{
		__asm
		{
			movzx eax, byte ptr[ebp + 24h];

			push eax;
			call CMeleeTypeInfo::GetMeleeHighestParentType;
			add esp, 4;

			cmp eax, 7;

			jnz     loc_6246AC;

			push 0x62466A;
			retn;

		loc_6246AC:
			push 0x6246AC;
			retn;
		}
	}
}
#endif

// Applies a melee combo type loader
void WeaponLimits::ApplyMeleeComboTypeLoader()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;		

		if (CPatch::IsDebugModeActive())
			MaxNumberOfCombos = 17;

		MaxNumberOfCombosInArray = MaxNumberOfCombos - NumberOfUnarmedComboTypes;

		// Allocate
		if (MaxNumberOfCombosInArray > 13)
		{
			CTaskSimpleFight__m_aComboData.gta_sa = new tComboData[MaxNumberOfCombosInArray];
			memset(CTaskSimpleFight__m_aComboData.gta_sa, 0, MaxNumberOfCombosInArray * sizeof(tComboData));
			CTaskSimpleFight__m_aComboData.bIsAllocated.Set(true);
		}

		CTaskSimpleFight__m_aComboDataEx = new tComboDataEx[MaxNumberOfCombosInArray];
		memset(CTaskSimpleFight__m_aComboDataEx, 0, MaxNumberOfCombosInArray * sizeof(tComboDataEx));

		// Patch references to CTaskSimpleFight::m_aComboData
		#if TRUE
		{
			CPatch::PatchPointer(0x4ABDB7 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     eax, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[eax]; CTaskSimpleFight::m_aComboData	; sub_4ABDA0
			CPatch::PatchPointer(0x4ABDDA + 3, &CTaskSimpleFight__m_aComboData.gta_sa->Flags);	// movzx   eax, word ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.Flags[eax]	; sub_4ABDC0
			CPatch::PatchPointer(0x4ABE11 + 3, &CTaskSimpleFight__m_aComboData.gta_sa->Flags);	// movzx   eax, word ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.Flags[eax]	; sub_4ABDF0
			CPatch::PatchPointer(0x4B434A + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     edx, ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID; CTaskSimpleFight::m_aComboData	; sub_4B3FC0
			CPatch::PatchPointer(0x5BEDCA + 1, &CTaskSimpleFight__m_aComboData.gta_sa->RANGES);	// mov     ecx, offset _ZN16CTaskSimpleFight12m_aComboDataE.RANGES	; sub_5BEDC0
			CPatch::PatchPointer(0x5BEE30 + 2, &CTaskSimpleFight__m_aComboData.gta_sa[MaxNumberOfCombosInArray].RANGES);	// cmp     ecx, offset flt_C177BC	; sub_5BEDC0
			CPatch::PatchPointer(0x5BF10C + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     dword ptr ss:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[ebp], edi; CTaskSimpleFight::m_aComboData	; sub_5BEDC0
			CPatch::PatchPointer(0x5BF130 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->RANGES);	// mov     ss:_ZN16CTaskSimpleFight12m_aComboDataE.RANGES[ebp], edx	; sub_5BEDC0
			CPatch::PatchPointer(0x5BF1DC + 2, &CTaskSimpleFight__m_aComboData.gta_sa->hitFlt);	// fstp    ds:_ZN16CTaskSimpleFight12m_aComboDataE.hitFlt[ecx]	; sub_5BEDC0
			CPatch::PatchPointer(0x5BF1F1 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->radius);	// mov     ds:_ZN16CTaskSimpleFight12m_aComboDataE.radius[ecx], edx	; sub_5BEDC0
			CPatch::PatchPointer(0x5BF1F7 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->chain);	// fstp    ds:_ZN16CTaskSimpleFight12m_aComboDataE.chain[ecx]	; sub_5BEDC0
			CPatch::PatchPointer(0x5BF206 + 3, &CTaskSimpleFight__m_aComboData.gta_sa->hitlevel);	// mov     ds:_ZN16CTaskSimpleFight12m_aComboDataE.hitlevel[esi+ebp], al	; sub_5BEDC0
			CPatch::PatchPointer(0x5BF212 + 3, &CTaskSimpleFight__m_aComboData.gta_sa->damage);	// mov     ds:_ZN16CTaskSimpleFight12m_aComboDataE.damage[esi+ebp], dl	; sub_5BEDC0
			CPatch::PatchPointer(0x5BF226 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->hit);	// mov     ds:_ZN16CTaskSimpleFight12m_aComboDataE.hit[ecx], edx	; sub_5BEDC0
			CPatch::PatchPointer(0x5BF241 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->altHit);	// mov     ds:_ZN16CTaskSimpleFight12m_aComboDataE.altHit[ecx], edx	; sub_5BEDC0
			CPatch::PatchPointer(0x5BF258 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->AGROUND_groundLoop);	// fstp    ss:_ZN16CTaskSimpleFight12m_aComboDataE.AGROUND_groundLoop[ebp]	; sub_5BEDC0
			CPatch::PatchPointer(0x5BF287 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->ABLOCK_hit);	// fstp    ss:_ZN16CTaskSimpleFight12m_aComboDataE.ABLOCK_hit[ebp]	; sub_5BEDC0
			CPatch::PatchPointer(0x5BF297 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->ABLOCK_chain);	// fstp    ss:_ZN16CTaskSimpleFight12m_aComboDataE.ABLOCK_chain[ebp]	; sub_5BEDC0
			CPatch::PatchPointer(0x5BF2B9 + 3, &CTaskSimpleFight__m_aComboData.gta_sa->Flags);	// mov     word ptr ss:_ZN16CTaskSimpleFight12m_aComboDataE.Flags[ebp], dx	; sub_5BEDC0
			CPatch::PatchPointer(0x609ABD + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     edi, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[ecx]; CTaskSimpleFight::m_aComboData	; sub_6098F0
			CPatch::PatchPointer(0x609B61 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     edi, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[edx]; CTaskSimpleFight::m_aComboData	; sub_6098F0
			CPatch::PatchPointer(0x61C1D7 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->RANGES);	// fld     ds:_ZN16CTaskSimpleFight12m_aComboDataE.RANGES[eax]	; 
			CPatch::PatchPointer(0x61C1E0 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->RANGES);	// fld     ds:_ZN16CTaskSimpleFight12m_aComboDataE.RANGES	; 
			CPatch::PatchPointer(0x61C647 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->RANGES);	// fld     ds:_ZN16CTaskSimpleFight12m_aComboDataE.RANGES[eax]	; 
			CPatch::PatchPointer(0x61C752 + 4, &CTaskSimpleFight__m_aComboData.gta_sa->damage);	// movzx   edx, ds:_ZN16CTaskSimpleFight12m_aComboDataE.damage[eax+ecx]	; sub_61C740
			CPatch::PatchPointer(0x61C8C4 + 2, (char*)(&CTaskSimpleFight__m_aComboData.gta_sa->Flags) + 1);	// test    byte ptr ds:(_ZN16CTaskSimpleFight12m_aComboDataE.Flags+1)[ecx], 4	; sub_61C7F0
			CPatch::PatchPointer(0x61C8DD + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     edx, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[esi]; CTaskSimpleFight::m_aComboData	; sub_61C7F0
			CPatch::PatchPointer(0x61C8E6 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// lea     esi, _ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[esi]; CTaskSimpleFight::m_aComboData	; sub_61C7F0
			CPatch::PatchPointer(0x61CC5A + 2, CTaskSimpleFight__m_aComboData.gta_sa);	// add     edi, offset _ZN16CTaskSimpleFight12m_aComboDataE; CTaskSimpleFight::m_aComboData	; sub_61CBA0
			CPatch::PatchPointer(0x61CCEB + 2, CTaskSimpleFight__m_aComboData.gta_sa);	// add     edi, offset _ZN16CTaskSimpleFight12m_aComboDataE; CTaskSimpleFight::m_aComboData	; sub_61CBA0
			CPatch::PatchPointer(0x61D71E + 2, &CTaskSimpleFight__m_aComboData.gta_sa->radius[3]);	// fadd    ds:(_ZN16CTaskSimpleFight12m_aComboDataE.radius+0Ch)[eax]	; sub_61D6F0
			CPatch::PatchPointer(0x620963 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     edx, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[ecx]; CTaskSimpleFight::m_aComboData	; sub_620910
			CPatch::PatchPointer(0x621145 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->RANGES);	// fld     ds:_ZN16CTaskSimpleFight12m_aComboDataE.RANGES[eax]	; sub_621100
			CPatch::PatchPointer(0x621150 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->RANGES);	// mov     edx, ds:_ZN16CTaskSimpleFight12m_aComboDataE.RANGES	; sub_621100
			CPatch::PatchPointer(0x623B83 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     eax, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[edx]; CTaskSimpleFight::m_aComboData	; sub_623B10
			CPatch::PatchPointer(0x623BCD + 2, &CTaskSimpleFight__m_aComboData.gta_sa->AGROUND_groundLoop);	// mov     eax, ds:_ZN16CTaskSimpleFight12m_aComboDataE.AGROUND_groundLoop[edx]	; sub_623B10
			CPatch::PatchPointer(0x623C8B + 2, (char*)(&CTaskSimpleFight__m_aComboData.gta_sa->Flags) + 1);	// test    byte ptr ds:(_ZN16CTaskSimpleFight12m_aComboDataE.Flags+1)[edi], 4	; sub_623B10
			CPatch::PatchPointer(0x623C9B + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     ecx, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[edi]; CTaskSimpleFight::m_aComboData	; sub_623B10
			CPatch::PatchPointer(0x623CDA + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     eax, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[edi]; CTaskSimpleFight::m_aComboData	; sub_623B10
			CPatch::PatchPointer(0x623D47 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     edx, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[ecx]; CTaskSimpleFight::m_aComboData	; sub_623B10
			CPatch::PatchPointer(0x623DC6 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     edx, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[ecx]; CTaskSimpleFight::m_aComboData	; sub_623B10
			CPatch::PatchPointer(0x623F0C + 2, (char*)(&CTaskSimpleFight__m_aComboData.gta_sa->Flags) + 1);	// test    byte ptr ds:(_ZN16CTaskSimpleFight12m_aComboDataE.Flags+1)[edx], 2	; sub_623B10
			CPatch::PatchPointer(0x623F2A + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     ecx, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[eax]; CTaskSimpleFight::m_aComboData	; sub_623B10
			CPatch::PatchPointer(0x624109 + 2, CTaskSimpleFight__m_aComboData.gta_sa);	// add     ebx, offset _ZN16CTaskSimpleFight12m_aComboDataE; CTaskSimpleFight::m_aComboData	; sub_6240B0
			CPatch::PatchPointer(0x624754 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->Flags);	// mov     bl, byte ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.Flags[ecx]	; sub_624710
			CPatch::PatchPointer(0x624A55 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->Flags);	// mov     bl, byte ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.Flags[ecx]	; sub_624A40
			CPatch::PatchPointer(0x6251C0 + 2, &CTaskSimpleFight__m_aComboData.gta_sa[12].animGroupID);	// mov     edx, ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID+660h	; sub_624F30
			CPatch::PatchPointer(0x629A7F + 2, (char*)(&CTaskSimpleFight__m_aComboData.gta_sa->Flags) + 1);	// test    byte ptr ds:(_ZN16CTaskSimpleFight12m_aComboDataE.Flags+1)[edi], 4	; sub_629920
			CPatch::PatchPointer(0x629A8C + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     edx, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[edi]; CTaskSimpleFight::m_aComboData	; sub_629920
			CPatch::PatchPointer(0x629ACA + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     ecx, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[edi]; CTaskSimpleFight::m_aComboData	; sub_629920
			CPatch::PatchPointer(0x629B58 + 2, &CTaskSimpleFight__m_aComboData.gta_sa->animGroupID);	// mov     edx, dword ptr ds:_ZN16CTaskSimpleFight12m_aComboDataE.animGroupID[ecx]; CTaskSimpleFight::m_aComboData	; sub_629920
			CPatch::PatchPointer(0x629C6C + 2, CTaskSimpleFight__m_aComboData.gta_sa);	// add     edi, offset _ZN16CTaskSimpleFight12m_aComboDataE; CTaskSimpleFight::m_aComboData	; sub_629920
			CPatch::PatchPointer(0x62A2CC + 2, &CTaskSimpleFight__m_aComboData.gta_sa->RANGES);	// fld     ds:_ZN16CTaskSimpleFight12m_aComboDataE.RANGES[eax]	; sub_62A0A0
			CPatch::PatchPointer(0x62A6BC + 3, &CTaskSimpleFight__m_aComboData.gta_sa[12].hitFlt);	// fcomp   ds:_ZN16CTaskSimpleFight12m_aComboDataE.hitFlt+660h[ebx*4]	; sub_62A380
			CPatch::PatchPointer(0x62A6D6 + 3, &CTaskSimpleFight__m_aComboData.gta_sa[12].hitFlt);	// fcomp   ds:_ZN16CTaskSimpleFight12m_aComboDataE.hitFlt+660h[ebx*4]	; sub_62A380
			CPatch::PatchPointer(0x62A6E9 + 3, &CTaskSimpleFight__m_aComboData.gta_sa[12].hitlevel);	// movzx   eax, ds:(_ZN16CTaskSimpleFight12m_aComboDataE.hitlevel+660h)[ebx]	; sub_62A380

			CPatch::PatchPointer(0x61D3B3 + 3, &CTaskSimpleFight__m_aComboData.gta_sa[-4].hit);
			CPatch::PatchPointer(0X61D5BD + 3, &CTaskSimpleFight__m_aComboData.gta_sa[-4].hit);
		}
		#endif

		// Manual patches
		#if TRUE
		{
			CPatch::RedirectCode(0x5BEDC0, &patch_CTaskSimpleFight__LoadMeleeData_5BEDC0);

			// different loading
			{
				CPatch::RedirectCode(0x5BEFCE, &patch_CTaskSimpleFight__LoadMeleeData_5BEFCE);
				/* useless CPatch::RedirectCode(0x40204B, &patch_CTaskSimpleFight__LoadMeleeData_40204B); */
				CPatch::NOPinstructions(0x5BF01B, 6);
			}

			CPatch::RedirectFunction(0x61DB30, &CTaskSimpleFight__GetComboType);
			
			// PISTOL_WHIP
			{
				CPatch::RedirectCode(0x6251C0, &patch_CTaskSimpleUseGun__StartAnim_6251C0);
				CPatch::RedirectCode(0x62A6BC, &patch_CTaskSimpleUseGun__ProcessPed_62A6BC);
			}

			// melee ID checks
			{
				CPatch::RedirectCode(0x61C6E1, &patch_CTaskSimpleFight__BeHitWhileBlocking_61C6E1);
				CPatch::RedirectCode(0x61C6F9, &patch_CTaskSimpleFight__BeHitWhileBlocking_61C6F9);

				CPatch::RedirectCode(0x61CC77, &patch_CTaskSimpleFight__FightHitPed_61CC77);
				CPatch::RedirectCode(0x61CD84, &patch_CTaskSimpleFight__FightHitPed_61CD84);
				CPatch::RedirectCode(0x61CE6C, &patch_CTaskSimpleFight__FightHitPed_61CE6C);
				CPatch::RedirectCode(0x61CF0E, &patch_CTaskSimpleFight__FightHitPed_61CF0E);
				CPatch::RedirectCode(0x61CFFB, &patch_CTaskSimpleFight__FightHitPed_61CFFB);

				CPatch::RedirectCode(0x629E44, &patch_CTaskSimpleFight__ProcessPed_629E44);
				CPatch::RedirectCode(0x629F66, &patch_CTaskSimpleFight__ProcessPed_629F66);

				CPatch::RedirectCode(0x62A33D, &patch_CTaskSimpleFightingControl__ProcessPed_62A33D);

				CPatch::RedirectCode(0x624664, &patch_CTaskSimpleFight__FightStrike_624664);
			}
		}
		#endif
	}
#endif

	// Print to log
	CGenericLogStorage::SaveFormattedTextLn(
		"Melee combo type loader is enabled. Max number of melee combos = %d.",
		MaxNumberOfCombos
		);

	CPatch::LeaveThisLevel();
}
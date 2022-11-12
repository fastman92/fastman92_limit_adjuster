/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"
#include <CVector.h>
#include <stdint.h>

/*
Logic analysis below

eWeaponType:
	malee weapons
		0, UNARMED
		1, BRASSKNUCKLE
		2, GOLFCLUB
		3, NIGHTSTICK
		4, KNIFE
		5, BASEBALLBAT
		6, SHOVEL
		7, POOLCUE
		8, KATANA
		9, CHAINSAW
		10, DILDO1
		11, DILDO2
		12, VIBE1
		13, VIBE2
		14, FLOWERS
		15, CANE
	end

	gun weapons
		16, GRENADE
		17, TEARGAS
		18, MOLOTOV
		19, ROCKET
		20, ROCKET_HS
		21, FREEFALL_BOMB

		weapons with 3 skills
			22, PISTOL
			23, PISTOL_SILENCED
			24, DESERT_EAGLE
			25, SHOTGUN
			26, SAWNOFF
			27, SPAS12
			28, MICRO_UZI
			29, MP5
			30, AK47
			31, M4
			32, TEC9
		end

		33, COUNTRYRIFLE
		34, SNIPERRIFLE
		35, RLAUNCHER
		36, RLAUNCHER_HS
		37, FTHROWER
		38, MINIGUN
		39, SATCHEL_CHARGE
		40, DETONATOR
		41, SPRAYCAN
		42, EXTINGUISHER
		43, CAMERA
		44, NIGHTVISION
		45, INFRARED
	end

	malee weapons
		46, PARACHUTE
	end

	47,
	48, ARMOUR


	--------------------
	WEAPONTYPE_RAMMEDBYCAR  = 49
	WEAPONTYPE_RUNOVERBYCAR  = 50
	WEAPONTYPE_EXPLOSION  = 51
	WEAPONTYPE_UZI_DRIVEBY  = 52
	WEAPONTYPE_DROWNING  = 53
	WEAPONTYPE_FALL  = 54
	WEAPONTYPE_UNIDENTIFIED  = 55
	WEAPONTYPE_ANYMELEE  = 56
	WEAPONTYPE_ANYWEAPON  = 57
	WEAPONTYPE_FLARE  = 58
	WEAPONTYPE_TANK_GRENADE  = 59
	--------------------


aWeaponInfo:
47 standard skill infoes
11 poor skill infoes
11 pro skill infoes
11 special skill infoes

CWeaponInfo *__cdecl CWeaponInfo::GetWeaponInfo(int weaponType, char skill)
{
	int16_t v2; // ax@1
	CWeaponInfo *result; // eax@2

	v2 = 47;
	if (skill)
	{
		if (skill == WEAPONSKILL_STD)
		{
			result = &aWeaponInfo[(int16_t)weaponType];
		}
		else if (skill == WEAPONSKILL_PRO)
		{
			result = &aWeaponInfo[(int16_t)(weaponType + 36)];
		}
		else
		{
			if (skill == WEAPONSKILL_SPECIAL)
				v2 = weaponType + 47;
			result = &aWeaponInfo[v2];
		}
	}
	else
	{
		result = &aWeaponInfo[(int16_t)(weaponType + 25)];// WEAPONSKILL_POOR
	}
	return result;
}


// to be changed: 
CWeaponInfo::GetSkillStatIndex
CPed::GetWeaponSkill
CWeaponInfo::GetWeaponInfo
*/

enum eWeaponSubsetType : int8_t
{
	WEAPON_SUBSET_UNUSED,

	WEAPON_SUBSET_RESERVED,

	WEAPON_SUBSET_ONLY_STANDARD_SKILL,
	WEAPON_SUBSET_MULTIPLE_SKILLS
};

struct tPickupMessageInfo
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	float float_4;
};

VALIDATE_SIZE(tPickupMessageInfo, 8);

/* Possible weapon link:
	   user type -> user type -> user type...)
	-> fastman92 type, bIsFastman92type = 1
	-> original type, 
*/

struct tWeaponTypeInfo
{
	char Name[32];
	bool bIsFastman92type;
	eWeaponSubsetType Subset;
	int statIndex;

	int PoorSkillindex;
	int StandardSkillIndex;
	int ProffesionalSkillIndex;
	int SpecialSkillIndex;

	int ParentWeaponID;
	bool bCanBeUsedForSecondPlayer;
	bool bHasWeaponAmmoToBeUsed;
	unsigned short AmmoForWeapon_OnStreet;

	tPickupMessageInfo PickupMessageInfo;

	int AssociatedWeaponID;
};

class CWeaponInfoExtension
{
public:
	char AnimGrpName[32];
};

struct CWeaponAimOffsetExtension
{
	char name[32];
};

struct tComboDataEx
{
	char name[32];
	int parentID;
};

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wignored-attributes"
#endif

class CWeaponInfo_generic
{
public:
	// Returns skill stat index
	static int __cdecl GetSkillStatIndex(signed int weaponType);

	// Finds weapon type by name
	static int __cdecl FindWeaponType(const char *weaponName);

	// Finds first free weapon type
	static int FindFirstFreeWeaponType();

	// Returns weapon info
	static CWeaponInfo_generic* GetWeaponInfo(int weaponType, char skill);

	// Returns weapon info
	static tWeaponTypeInfo* GetWeaponTypeInfo(int weaponType);

	// Returns weapon info index
	static int GetWeaponInfoIndex(int weaponType, char skill);

	// Is weapon type subset multiple skills
	static eWeaponSubsetType GetWeaponInfoSubset(int weaponType);

	// Returns true if it's user operated weapon
	static bool IsUserOperatedWeapon(int weaponType);

	// Returns weapon parent type
	static int GetWeaponHighestParentType(int weaponType);

	// Returns weapon parent type until fastman92 type
	static int GetWeaponParentTypeUntilFastman92(int weaponType);

	// Returns true if weapon parent type is recursive
	static bool IsWeaponParentTypeRecursive(int weaponType);
};

class CWeapon_generic
{
public:
	// Accesses weapon ID
	unsigned int& AccessWeaponID();

	// Can be used for second player?
	static bool __cdecl CanBeUsedFor2Player(int weaponType);

	// Has weapon ammo to be used?
	bool HasWeaponAmmoToBeUsed();
};

namespace Game_GTASA
{
	enum eFireType
	{
		FIRETYPE_MELEE = 0x0,
		FIRETYPE_INSTANT_HIT = 0x1,
		FIRETYPE_PROJECTILE = 0x2,
		FIRETYPE_AREA_EFFECT = 0x3,
		FIRETYPE_CAMERA = 0x4,
		FIRETYPE_USE = 0x5,
		FIRETYPE_LAST_FIRETYPE = 0x6,
	};

	enum eWeaponSlot
	{
		WEAPONSLOT_TYPE_UNARMED = 0x0,
		WEAPONSLOT_TYPE_MELEE = 0x1,
		WEAPONSLOT_TYPE_HANDGUN = 0x2,
		WEAPONSLOT_TYPE_SHOTGUN = 0x3,
		WEAPONSLOT_TYPE_SMG = 0x4,
		WEAPONSLOT_TYPE_MG = 0x5,
		WEAPONSLOT_TYPE_RIFLE = 0x6,
		WEAPONSLOT_TYPE_HEAVY = 0x7,
		WEAPONSLOT_TYPE_THROWN = 0x8,
		WEAPONSLOT_TYPE_SPECIAL = 0x9,
		WEAPONSLOT_TYPE_GIFT = 0xA,
		WEAPONSLOT_TYPE_PARACHUTE = 0xB,
		WEAPONSLOT_TYPE_DETONATOR = 0xC,
		WEAPONSLOT_MAX = 0xD,
	};

	enum eWeaponSkill
	{
		WEAPONSKILL_POOR = 0x0,
		WEAPONSKILL_STD = 0x1,
		WEAPONSKILL_PRO = 0x2,
		WEAPONSKILL_SPECIAL = 0x3,
		WEAPONSKILL_MAX_NUMBER = 0x4,
	};

	enum eWeaponType
	{
		WEAPONTYPE_UNARMED = 0,
		WEAPONTYPE_BRASSKNUCKLE = 1,
		WEAPONTYPE_GOLFCLUB = 2,
		WEAPONTYPE_NIGHTSTICK = 3,
		WEAPONTYPE_KNIFE = 4,
		WEAPONTYPE_BASEBALLBAT = 5,
		WEAPONTYPE_SHOVEL = 6,
		WEAPONTYPE_POOLCUE = 7,
		WEAPONTYPE_KATANA = 8,
		WEAPONTYPE_CHAINSAW = 9,
		WEAPONTYPE_DILDO1 = 10,
		WEAPONTYPE_DILDO2 = 11,
		WEAPONTYPE_VIBE1 = 12,
		WEAPONTYPE_VIBE2 = 13,
		WEAPONTYPE_FLOWERS = 14,
		WEAPONTYPE_CANE = 15,
		WEAPONTYPE_GRENADE = 16,
		WEAPONTYPE_TEARGAS = 17,
		WEAPONTYPE_MOLOTOV = 18,
		WEAPONTYPE_ROCKET = 19,
		WEAPONTYPE_ROCKET_HS = 20,
		WEAPONTYPE_FREEFALL_BOMB = 21,
		WEAPONTYPE_PISTOL = 22,
		WEAPONTYPE_PISTOL_SILENCED = 23,
		WEAPONTYPE_DESERT_EAGLE = 24,
		WEAPONTYPE_SHOTGUN = 25,
		WEAPONTYPE_SAWNOFF = 26,
		WEAPONTYPE_SPAS12 = 27,
		WEAPONTYPE_MICRO_UZI = 28,
		WEAPONTYPE_MP5 = 29,
		WEAPONTYPE_AK47 = 30,
		WEAPONTYPE_M4 = 31,
		WEAPONTYPE_TEC9 = 32,
		WEAPONTYPE_COUNTRYRIFLE = 33,
		WEAPONTYPE_SNIPERRIFLE = 34,
		WEAPONTYPE_RLAUNCHER = 35,
		WEAPONTYPE_RLAUNCHER_HS = 36,
		WEAPONTYPE_FTHROWER = 37,
		WEAPONTYPE_MINIGUN = 38,
		WEAPONTYPE_SATCHEL_CHARGE = 39,
		WEAPONTYPE_DETONATOR = 40,
		WEAPONTYPE_SPRAYCAN = 41,
		WEAPONTYPE_EXTINGUISHER = 42,
		WEAPONTYPE_CAMERA = 43,
		WEAPONTYPE_NIGHTVISION = 44,
		WEAPONTYPE_INFRARED = 45,
		WEAPONTYPE_PARACHUTE = 46,

		// fastman92 weapon types
		WEAPONTYPE_FASTMAN92_FIRST = 60,
		
		WEAPONTYPE_JETPACK_TYPE = WEAPONTYPE_FASTMAN92_FIRST,
		WEAPONTYPE_BINOCULARS_TYPE,

		WEAPONTYPE_FASTMAN92_FIRST_NOT_MADE,

		WEAPONTYPE_FASTMAN92_LAST = 69
	};

	class CWeaponInfo : public CWeaponInfo_generic
	{
	public:
		eFireType m_eFireType;
		float m_fTargetRange;
		float m_fWeaponRange;
		int m_modelId;
		int m_modelId2;
		eWeaponSlot m_nWeaponSlot;
		uint32_t m_nFlags;
		uint32_t m_animGroup;
		int16_t m_nAmmo;
		int16_t m_nDamage;
		CVector m_vecFireOffset;
		eWeaponSkill m_SkillLevel;
		int m_nReqStatLevel;
		float m_fAccuracy;
		float m_fMoveSpeed;
		float m_animLoopStart;
		float m_animLoopEnd;
		float m_animFireTime;
		float m_anim2LoopStart;
		float m_anim2LoopEnd;
		float m_anim2FireTime;
		float m_animBreakoutTime;
		float m_fSpeed;
		float m_fRadius;
		float m_fLifeSpan;
		float m_fSpread;
		int16_t m_nAimOffsetIndex;
		uint8_t m_defaultCombo;
		uint8_t m_nCombosAvailable;

		/*
		// Returns weapon info
		static CWeaponInfo* GetWeaponInfoForLoading(int weaponType, char skill);
		*/
	};

	class CWeapon : public CWeapon_generic
	{
	public:
		unsigned int weaponType;
		int state;
		int ammoInClip;
		int ammoRemaining;
		int field_10;
		char field_14;
		char field_15;
		char field_16;
		char field_17;
		int particle;
	};

	VALIDATE_SIZE(CWeapon, 0x1C);

	struct CWeaponAimOffset
	{
		float AimX;
		float AimZ;
		float DuckX;
		float DuckZ;
		int RLoadA;
		int16_t CrouchRLoadA;
		int16_t CrouchRLoadB;
	};

	VALIDATE_SIZE(CWeaponAimOffset, 0x18);

	struct tComboData
	{
		int animGroupID;
		int RANGES;
		float hitFlt[5];
		float chain[5];
		float radius[5];
		float AGROUND_groundLoop;
		float ABLOCK_hit;
		float ABLOCK_chain;
		char hitlevel[5];
		char damage[5];
		char gap_5A[2];
		int hit[5];
		int altHit[5];
		int Flags;
	};
	
	VALIDATE_SIZE(tComboData, 0x88);
}
// #define WEAPON_TYPES_CONSTANT_LIMIT 70

// GTA IV
namespace Game_GTAIV
{
	enum eFireType
	{
		FIRETYPE_MELEE = 0,
		FIRETYPE_INSTANT_HIT = 1,
		FIRETYPE_DELAYED_HIT = 2,
		FIRETYPE_PROJECTILE = 3,
		FIRETYPE_AREA_EFFECT = 4,
		FIRETYPE_CAMERA = 5,
		FIRETYPE_USE = 6,
		FIRETYPE_UNKNOWN = 7
	};

	enum eWeaponSlot
	{
		WEAPONSLOT_TYPE_UNARMED = 0,
		WEAPONSLOT_TYPE_MELEE = 1,
		WEAPONSLOT_TYPE_HANDGUN = 2,
		WEAPONSLOT_TYPE_SHOTGUN = 3,
		WEAPONSLOT_TYPE_SMG = 4,
		WEAPONSLOT_TYPE_RIFLE = 5,
		WEAPONSLOT_TYPE_SNIPER = 6,
		WEAPONSLOT_TYPE_HEAVY = 7,
		WEAPONSLOT_TYPE_THROWN = 8,
		WEAPONSLOT_TYPE_SPECIAL = 9,
		WEAPONSLOT_TYPE_PARACHUTE = 10,
		WEAPONSLOT_TYPE_UNKNOWN = 11
	};

	enum eWeaponDamageType
	{
		WEAPONDAMAGE_TYPE_NONE = 0,
		WEAPONDAMAGE_TYPE_MELEE = 1,
		WEAPONDAMAGE_TYPE_BULLET = 2,
		WEAPONDAMAGE_TYPE_EXPLOSIVE = 3,
		WEAPONDAMAGE_TYPE_FIRE = 4,
		WEAPONDAMAGE_TYPE_COLLISION = 5,
		WEAPONDAMAGE_TYPE_FALL = 6,
		WEAPONDAMAGE_TYPE_DROWN = 7,
		WEAPONDAMAGE_TYPE_UNKNOWN = 8
	};

	enum eWeaponGroupType
	{
		WEAPONGROUP_TYPE_PUNCH_KICK = 0,
		WEAPONGROUP_TYPE_MELEE_WOOD = 1,
		WEAPONGROUP_TYPE_MELEE_METAL = 2,
		WEAPONGROUP_TYPE_MELEE_SHARP = 3,
		WEAPONGROUP_TYPE_MELEE_GENERIC = 4,
		WEAPONGROUP_TYPE_PISTOL_SMALL = 5,
		WEAPONGROUP_TYPE_PISTOL_LARGE = 6,
		WEAPONGROUP_TYPE_PISTOL_SILENCED = 7,
		WEAPONGROUP_TYPE_SMG = 8,
		WEAPONGROUP_TYPE_SHOTGUN = 9,
		WEAPONGROUP_TYPE_RIFLE_ASSAULT = 10,
		WEAPONGROUP_TYPE_RIFLE_SNIPER = 11,
		WEAPONGROUP_TYPE_ROCKET = 12,
		WEAPONGROUP_TYPE_GRENADE = 13,
		WEAPONGROUP_TYPE_MOLOTOV = 14,
		WEAPONGROUP_TYPE_FIRE = 15,
		WEAPONGROUP_TYPE_EXPLOSION = 16,
		WEAPONGROUP_TYPE_UNKNOWN = 17
	};

	enum eProjectileType
	{
		PROJECTILE_TYPE_NONE = 0,
		PROJECTILE_TYPE_FUSE = 1,
		PROJECTILE_TYPE_IMPACT = 2,
		PROJECTILE_TYPE_ROCKET = 3,
		PROJECTILE_TYPE_STICKY = 4,
		PROJECTILE_TYPE_UNKNOWN = 5
	};

	enum eProjectileExplosionType
	{
		PROJECTILE_EXPLOSION_TYPE_GRENADE = 0,
		PROJECTILE_EXPLOSION_TYPE_MOLOTOV = 1,
		PROJECTILE_EXPLOSION_TYPE_ROCKET = 2,
		PROJECTILE_EXPLOSION_TYPE_HI_OCTANE = 3,
		PROJECTILE_EXPLOSION_TYPE_CAR = 4,
		PROJECTILE_EXPLOSION_TYPE_PLANE = 5,
		PROJECTILE_EXPLOSION_TYPE_PETROL_PUMP = 6,
		PROJECTILE_EXPLOSION_TYPE_BIKE = 7,
		PROJECTILE_EXPLOSION_TYPE_DIR_STEAM = 8,
		PROJECTILE_EXPLOSION_TYPE_DIR_FLAME = 9,
		PROJECTILE_EXPLOSION_TYPE_DIR_WATER_HYDRANT = 10,
		PROJECTILE_EXPLOSION_TYPE_DIR_GAS_CANISTER = 11,
		PROJECTILE_EXPLOSION_TYPE_BOAT = 12,
		PROJECTILE_EXPLOSION_TYPE_SHIP_DESTROY = 13,
		PROJECTILE_EXPLOSION_TYPE_TRUCK = 14,
		PROJECTILE_EXPLOSION_TYPE_EPISODIC_1 = 15,
		PROJECTILE_EXPLOSION_TYPE_EPISODIC_2 = 16,
		PROJECTILE_EXPLOSION_TYPE_EPISODIC_3 = 17,
		PROJECTILE_EXPLOSION_TYPE_EPISODIC_4 = 18,
		PROJECTILE_EXPLOSION_TYPE_EPISODIC_5 = 19,
		PROJECTILE_EXPLOSION_TYPE_EPISODIC_6 = 20,
		PROJECTILE_EXPLOSION_TYPE_EPISODIC_7 = 21,
		PROJECTILE_EXPLOSION_TYPE_EPISODIC_8 = 22,
		PROJECTILE_EXPLOSION_TYPE_EPISODIC_9 = 23,
		PROJECTILE_EXPLOSION_TYPE_EPISODIC_10 = 24,
		PROJECTILE_EXPLOSION_TYPE_UNKNOWN = 25
	};

	enum eWeaponType
	{
		WEAPONTYPE_UNARMED = 0,
		WEAPONTYPE_BASEBALLBAT = 1,
		WEAPONTYPE_POOLCUE = 2,
		WEAPONTYPE_KNIFE = 3,
		WEAPONTYPE_GRENADE = 4,
		WEAPONTYPE_MOLOTOV = 5,
		WEAPONTYPE_ROCKET = 6,
		WEAPONTYPE_PISTOL = 7,
		WEAPONTYPE_UNUSED0 = 8,
		WEAPONTYPE_DEAGLE = 9,
		WEAPONTYPE_SHOTGUN = 10,
		WEAPONTYPE_BARETTA = 11,
		WEAPONTYPE_MICRO_UZI = 12,
		WEAPONTYPE_MP5 = 13,
		WEAPONTYPE_AK47 = 14,
		WEAPONTYPE_M4 = 15,
		WEAPONTYPE_SNIPERRIFLE = 16,
		WEAPONTYPE_M40A1 = 17,
		WEAPONTYPE_RLAUNCHER = 18,
		WEAPONTYPE_FTHROWER = 19,
		WEAPONTYPE_MINIGUN = 20,
		WEAPONTYPE_EPISODIC_1 = 21,
		WEAPONTYPE_EPISODIC_2 = 22,
		WEAPONTYPE_EPISODIC_3 = 23,
		WEAPONTYPE_EPISODIC_4 = 24,
		WEAPONTYPE_EPISODIC_5 = 25,
		WEAPONTYPE_EPISODIC_6 = 26,
		WEAPONTYPE_EPISODIC_7 = 27,
		WEAPONTYPE_EPISODIC_8 = 28,
		WEAPONTYPE_EPISODIC_9 = 29,
		WEAPONTYPE_EPISODIC_10 = 30,
		WEAPONTYPE_EPISODIC_11 = 31,
		WEAPONTYPE_EPISODIC_12 = 32,
		WEAPONTYPE_EPISODIC_13 = 33,
		WEAPONTYPE_EPISODIC_14 = 34,
		WEAPONTYPE_EPISODIC_15 = 35,
		WEAPONTYPE_EPISODIC_16 = 36,
		WEAPONTYPE_EPISODIC_17 = 37,
		WEAPONTYPE_EPISODIC_18 = 38,
		WEAPONTYPE_EPISODIC_19 = 39,
		WEAPONTYPE_EPISODIC_20 = 40,
		WEAPONTYPE_EPISODIC_21 = 41,
		WEAPONTYPE_EPISODIC_22 = 42,
		WEAPONTYPE_EPISODIC_23 = 43,
		WEAPONTYPE_EPISODIC_24 = 44,
		WEAPONTYPE_CAMERA = 45,
		WEAPONTYPE_OBJECT = 46,
		WEAPONTYPE_WEAPONTYPE_LAST_WEAPONTYPE = 47,
		WEAPONTYPE_ARMOUR = 48,
		WEAPONTYPE_RAMMEDBYCAR = 49,
		WEAPONTYPE_RUNOVERBYCAR = 50,
		WEAPONTYPE_EXPLOSION = 51,
		WEAPONTYPE_UZI_DRIVEBY = 52,
		WEAPONTYPE_DROWNING = 53,
		WEAPONTYPE_FALL = 54,
		WEAPONTYPE_UNIDENTIFIED = 55,
		WEAPONTYPE_ANYMELEE = 56,
		WEAPONTYPE_ANYWEAPON = 57
	};


	struct CWeaponInfo
	{
		eWeaponType m_eWeaponType;
		int m_eWeaponSlot;
		int m_eFireType;
		eWeaponDamageType m_eWeaponDamageType;
		int m_eWeaponGroupType;
		float m_fTargetRange;
		float m_fWeaponRange;
		eWeaponType m_eStatWeaponID;
		uint32_t m_nFlags;
		int m_modelNameHash;
		int m_nAssetAnimGroup;
		float m_fAssetAnimFireRate;
		float m_fAssetAnimBlindFireRate;
		float m_fAccuracy;
		float m_fAccuracyFPS;
		char gap_3C[4];
		CVector m_vecAimingOffset;
		float field_4C;
		CVector m_vecAimingCrouchedOffset;
		float field_5C;
		float m_fAimingPitch;
		float m_fAimingReticuleStanding;
		float m_fAimingReticuleDucked;
		float m_fAimingReticuleScale;
		int m_nRumbleDuration;
		float m_fRumbleIntensity;
		int m_nPickupRegenTime;
		int field_7C;
		int16_t m_nPickupAmmoOnStreet;
		int16_t m_nDamageBase;
		int16_t m_nDamageFPS;
		int16_t m_nClipSize;
		int16_t m_nAmmoMax;
		char gap_8A[2];
		int m_nTimeBetweenShots;
		float m_fPhysicsForce;
		int m_nReloadTime;
		int m_ReloadFastTime;
		int m_nReloadCrouchTime;
		eProjectileType m_eProjectileType;
		int m_nProjectileFuseTime;
		eWeaponType m_eProjectileUnkWeaponType;
		int m_eProjectileExplosionType;
		CVector m_vecProjectileOffset;
		float field_BC;
		CVector m_vecProjectileRotOffset;
		float field_CC;
		float m_fExplodeImpactTreshHold;
		float m_fExplodeImpactWithVehicleTreshold;
		float m_fVehicleVelocity;
		int m_nAssetAnimMeleeGroup1;
		int m_nAssetAnimMeleeGroup2;
		int m_uEffectMuzzleHash;
		int m_uEffectShellHash;
		int m_uEffectTrailHash;
		float m_fDamagePlayerMod;
		float m_fNetworkPed;
		float m_fAccuracyTime;
		int m_nAimingPellets;
		int field_100;
		int field_104;
		int field_108;
		int field_10C;
	};

	VALIDATE_SIZE(CWeaponInfo, 0x110);
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

class WeaponLimits : public CLimitAdjusterModule
{
public:
	bool bWeaponTypeLoaderEnabled;

	bool bWeaponIDsizeExtended;
	unsigned int NumberOfCustomWeaponTypes;
	unsigned int NumberOfWeaponTypes;

#ifdef WEAPON_TYPES_CONSTANT_LIMIT
	tWeaponTypeInfo WeaponTypes[WEAPON_TYPES_CONSTANT_LIMIT];
#else
	tWeaponTypeInfo* WeaponTypes;
#endif

	struct {
		uint16_t* ptr;
		DEFINE_IS_ALLOCATED();
	} AmmoForWeapon_OnStreet;

	struct {
		const tPickupMessageInfo* ptr;
		DEFINE_IS_ALLOCATED();
	} aAaaa;

	struct {
		union {
			Game_GTASA::CWeaponInfo* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} aWeaponInfo;
	CWeaponInfoExtension* aWeaponInfoExtension;
	CWeaponAimOffsetExtension* CWeaponInfo__ms_aWeaponAimOffsetsExtension;
	unsigned int GunAimingOffsetsLimit;
	unsigned int NumberOfGunAimingOffsetsRegistered;
	unsigned int CountOfWeaponInfos;

	////////////
	bool bEnableMeleeComboTypeLoader;

	unsigned int NumberOfUnarmedComboTypes;
	unsigned int MaxNumberOfCombos;
	unsigned int MaxNumberOfCombosInArray;	// MaxNumberOfCombos - NumberOfUnarmedComboTypes

	struct {
		union {
			Game_GTASA::tComboData* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CTaskSimpleFight__m_aComboData;
	tComboDataEx* CTaskSimpleFight__m_aComboDataEx;

	// Enables weapon type loader
	bool EnableWeaponTypeLoader(bool bEnable);

	// Sets number of weapon types
	void SetNumberOfWeaponTypes(int numberOfWeaponTypes);

	// Enables melee combo type loader
	bool EnableMeleeComboTypeLoader(bool bEnable);

	// Set combo limit
	void SetMaxNumberOfMeleeCombos(int iValue);

	// Sets number of gun aiming offsets
	// void SetNumberOfGunAimingOffsets(

	// Commits changes
	void CommitChanges();

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();

private:
	// Applies a weapon type loader
	void ApplyWeaponTypeLoader();

	// Applies a melee combo type loader
	void ApplyMeleeComboTypeLoader();

	// Loads weapon types
	void LoadWeaponTypes();

	friend void InitializeMeleeNames();

	// Loads melee types
	void LoadMeleeTypes();
};

extern WeaponLimits g_weaponLimits;
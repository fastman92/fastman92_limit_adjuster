// Compilation time: 2 seconds 829 ms

// patch for 0x280298
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__Initialise_18E9A8_arm = 0;	// _Znaj
	uintptr_t Address_GTA_SA_2_00_CIplStore__Initialise_2802A0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__Initialise_280298()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_COUNT_multiplied_by_sizeof_IplDef)
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Initialise_2802A0_thumb)

		// Branches
		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Initialise_18E9A8_arm)
		);
}

// patch for 0x2802A2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__Initialise_2802AE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__Initialise_2802A2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_COUNT)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_IPL_COUNT)
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Initialise_2802AE_thumb)

		// Branches
		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Initialise_18E9A8_arm)
		);
}

// patch for 0x2802EA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__Initialise_2802D4_thumb = 0;	// loc_2802D4
	uintptr_t Address_GTA_SA_2_00_CIplStore__Initialise_2802F6 = 0;
	uintptr_t Address_GTA_SA_2_00_CIplStore__Initialise_2802F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__Initialise_2802EA()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_COUNT)
		"BNE 1f\n"
		"LDR R0, =("/* _ZN9CIplStore8ms_pPoolE_ptr */"0x6770B8 - 0x2802F6)\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CIplStore__Initialise_2802F6)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Initialise_2802F4_thumb)

		// Branches
		"1:\n"	// loc_2802D4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Initialise_2802D4_thumb)
		);
}

// patch for 0x280434
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__Shutdown_28043C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__Shutdown_280434()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IPL_BASE_ID_PLUS_ONE_then_multiplied_by_sizeof_CStreamingInfo_plus_m_flags)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Shutdown_28043C_thumb)
		);
}

// patch for 0x280440
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__Shutdown_280448_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__Shutdown_280440()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, FILE_TYPE_IPL_BASE_ID_PLUS_ONE)
		"LDR R0, [R0]\n"
		"ADDS R4, R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Shutdown_280448_thumb)
		);
}

// patch for 0x280470
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__Shutdown_28044E_thumb = 0;	// loc_28044E
	uintptr_t Address_GTA_SA_2_00_CIplStore__Shutdown_280478_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__Shutdown_280470()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_IPL_COUNT_MINUS_ONE)
		"BNE 1f\n"
		"LDR R0, =("/* _ZN9CIplStore8ms_pPoolE_ptr */"0x6770B8 - 0x28047E)\n"
		"MOVS R6, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Shutdown_280478_thumb)

		// Branches
		"1:\n"	// loc_28044E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Shutdown_28044E_thumb)
		);
}

// patch for 0x28051C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__Shutdown_2804A8_thumb = 0;	// loc_2804A8
	uintptr_t Address_GTA_SA_2_00_CIplStore__Shutdown_280556_thumb = 0;	// loc_280556
	uintptr_t Address_GTA_SA_2_00_CIplStore__Shutdown_280524_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__Shutdown_28051C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_IPL_COUNT)
		"BNE 1f\n"
		"CBZ R4, 2f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Shutdown_280524_thumb)

		// Branches
		"1:\n"	// loc_2804A8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Shutdown_2804A8_thumb)
		"2:\n"	// loc_280556
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Shutdown_280556_thumb)
		);
}

// patch for 0x2805FE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__RemoveAllIpls_280608_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__RemoveAllIpls_2805FE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IPL_BASE_ID_PLUS_ONE_then_multiplied_by_sizeof_CStreamingInfo_plus_m_flags)
		"MOVS R5, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__RemoveAllIpls_280608_thumb)
		);
}

// patch for 0x28060A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__RemoveAllIpls_280614_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__RemoveAllIpls_28060A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, FILE_TYPE_IPL_BASE_ID_PLUS_ONE)
		"LDR R0, [R0]\n"
		"ADDS R4, R0, R1\n"
		"LDR R0, =("/* _ZN9CIplStore8ms_pPoolE_ptr */"0x6770B8 - 0x280618)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__RemoveAllIpls_280614_thumb)
		);
}

// patch for 0x28063A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__RemoveAllIpls_280618_thumb = 0;	// loc_280618
	uintptr_t Address_GTA_SA_2_00_CIplStore__RemoveAllIpls_280644_thumb = 0;	// off_280644
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__RemoveAllIpls_28063A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_IPL_COUNT_MINUS_ONE)
		"BNE 1f\n"
		"POP {R8}\n"
		"POP {R4-R7,PC}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__RemoveAllIpls_280644_thumb)

		// Branches
		"1:\n"	// loc_280618
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__RemoveAllIpls_280618_thumb)
		);
}

// patch for 0x281536
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__SetupRelatedIpls_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CIplStore__SetupRelatedIpls_281542_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__SetupRelatedIpls_281536()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_BASE_ID)
		"ADD R0, R8\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__SetupRelatedIpls_281542_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__SetupRelatedIpls_192964_arm)
		);
}

// patch for 0x28164E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__RemoveRelatedIpls_281656 = 0;
	uintptr_t Address_GTA_SA_2_00_CIplStore__RemoveRelatedIpls_281658_thumb = 0;	// loc_281658
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__RemoveRelatedIpls_28164E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, FILE_TYPE_IPL_BASE_ID)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CIplStore__RemoveRelatedIpls_281656)
		"LDR R9, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__RemoveRelatedIpls_281658_thumb)
		);
}

// patch for 0x281A8C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__LoadIpls_281A94_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__LoadIpls_281A8C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R9, FILE_TYPE_IPL_BASE_ID_PLUS_ONE)
		"MOV R8, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__LoadIpls_281A94_thumb)
		);
}

// patch for 0x281AEE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__LoadIpls_281A9E_thumb = 0;	// loc_281A9E
	uintptr_t Address_GTA_SA_2_00_CIplStore__LoadIpls_281AFE_thumb = 0;	// loc_281AFE
	uintptr_t Address_GTA_SA_2_00_CIplStore__LoadIpls_281AF8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__LoadIpls_281AEE()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_IPL_COUNT_MINUS_ONE)
		"BNE 1f\n"
		"LDR R0, [SP,#0x38+"/* var_38 */"-0x38]\n"
		"CBNZ R0, 2f\n"
		"LDR R0, =("/* byte_6DFD9C */"0x6DFD9C - 0x281AFE)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__LoadIpls_281AF8_thumb)

		// Branches
		"1:\n"	// loc_281A9E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__LoadIpls_281A9E_thumb)
		"2:\n"	// loc_281AFE
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__LoadIpls_281AFE_thumb)
		);
}

// patch for 0x281BA0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281BA8 = 0;
	uintptr_t Address_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281BAA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281BA0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_IPL_BASE_ID_PLUS_ONE)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281BA8)
		"VLDR S18, 101f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281BAA_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, -190.0)
		);
}

// patch for 0x281BB4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281BBC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281BB4()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_BASE_ID_PLUS_ONE_then_multiplied_by_sizeof_CStreamingInfo_plus_m_status_then_minus_1312)
		"ADD R6, R0, #0x530\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281BBC_thumb)
		);
}

// patch for 0x281C7C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281C84_thumb = 0;	// loc_281C84
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281C7C()
{
	__asm(
	".thumb\n"
		"LDRD R3, R12, [SP,#0x38+"/* var_38 */"-0x38]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_IPL_BASE_ID_PLUS_ONE)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281C84_thumb)
		);
}

// patch for 0x281C90
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281BD0_thumb = 0;	// loc_281BD0
	uintptr_t Address_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281C98_thumb = 0;	// loc_281C98
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281C90()
{
	__asm(
	".thumb\n"
		"ADDS R6, #0x14\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, FILE_TYPE_IPL_COUNT_MINUS_ONE)
		"BNE 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281C98_thumb)

		// Branches
		"1:\n"	// loc_281BD0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__EnsureIplsAreInMemory_281BD0_thumb)
		);
}

// patch for 0x281CF6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__RequestIpls_281D00_thumb = 0;	// loc_281D00
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__RequestIpls_281CF6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R9, FILE_TYPE_IPL_BASE_ID_PLUS_ONE)
		"MOVS R4, #0\n"
		"LDR R11, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__RequestIpls_281D00_thumb)
		);
}

// patch for 0x281D88
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__RequestIpls_281D90_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__RequestIpls_281D88()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, FILE_TYPE_IPL_COUNT_MINUS_ONE)
		"BNE 1f\n"
		"VPOP {D8-D9}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__RequestIpls_281D90_thumb)

		// Branches
		"1:\n"	// loc_281D00
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__RequestIpls_281D00_thumb)
		);
}

// patch for 0x281E44
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281DC8_thumb = 0;	// loc_281DC8
	uintptr_t Address_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281E4C_thumb = 0;	// loc_281E4C
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281E44()
{
	__asm(
	".thumb\n"
		"ADDS R1, R4, #1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, FILE_TYPE_IPL_COUNT_MINUS_ONE)
		"BLT 1f\n"
		"MOVS R0, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281E4C_thumb)

		// Branches
		"1:\n"	// loc_281DC8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281DC8_thumb)
		);
}

// patch for 0x281E54
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281E5C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281E54()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, FILE_TYPE_IPL_COUNT_MINUS_ONE)
		"BGT 1f\n"
		"LDR R5, =("/* _ZN9CIplStore8ms_pPoolE_ptr */"0x6770B8 - 0x281E62)\n"
		"ADDS R6, R4, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281E5C_thumb)

		// Branches
		"1:\n"	// loc_281E4C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281E4C_thumb)
		);
}

// patch for 0x281E80
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281E64_thumb = 0;	// loc_281E64
	uintptr_t Address_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281E8A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281E80()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, FILE_TYPE_IPL_COUNT_MINUS_TWO)
		"BLE 1f\n"
		"MOVS R0, #0\n"
		"POP {R8}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281E8A_thumb)

		// Branches
		"1:\n"	// loc_281E64
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__HaveIplsLoaded_281E64_thumb)
		);
}

// patch for 0x281F6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__LoadAllRemainingIpls_281F74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__LoadAllRemainingIpls_281F6C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_BASE_ID_PLUS_ONE)
		"ADDS R6, R5, R0\n"
		"MOVS R1, #0x18\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__LoadAllRemainingIpls_281F74_thumb)
		);
}

// patch for 0x281F88
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__LoadAllRemainingIpls_281EC6_thumb = 0;	// loc_281EC6
	uintptr_t Address_GTA_SA_2_00_CIplStore__LoadAllRemainingIpls_281F90_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__LoadAllRemainingIpls_281F88()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, FILE_TYPE_IPL_COUNT_MINUS_ONE)
		"BNE 1f\n"
		"LDR R0, =("/* __stack_chk_guard_ptr */"0x676E44 - 0x281F96)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__LoadAllRemainingIpls_281F90_thumb)

		// Branches
		"1:\n"	// loc_281EC6
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__LoadAllRemainingIpls_281EC6_thumb)
		);
}

// patch for 0x281FD8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__RequestIplAndIgnore_281FE0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__RequestIplAndIgnore_281FD8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IPL_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__RequestIplAndIgnore_281FE0_thumb)
		);
}

// patch for 0x282010
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__RemoveIplAndIgnore_18CCAC_arm = 0;	// j__ZN10CStreaming11RemoveModelEi
	uintptr_t Address_GTA_SA_2_00_CIplStore__RemoveIplAndIgnore_28201A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__RemoveIplAndIgnore_282010()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IPL_BASE_ID)
		"ADD R0, R1\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__RemoveIplAndIgnore_28201A_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming11RemoveModelEi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__RemoveIplAndIgnore_18CCAC_arm)
		);
}

// patch for 0x2CF934
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ReInit_2CF93C = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__ReInit_2CF93E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ReInit_2CF934()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_DFF_LAST_ID)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CStreaming__ReInit_2CF93C)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_TXD_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ReInit_2CF93E_thumb)
		);
}

// patch for 0x2CF9F2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ReInit_2CFA00_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ReInit_2CF9F2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_TXD_BASE_ID)
		"MUL LR, R3, R5\n"
		"LDR R3, [SP,#0x38+"/* var_30 */"-0x30]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_DFF_LAST_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ReInit_2CFA00_thumb)
		);
}

// patch for 0x2CFA36
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ReInit_2CF97C_thumb = 0;	// loc_2CF97C
	uintptr_t Address_GTA_SA_2_00_CStreaming__ReInit_2CFA46_thumb = 0;	// loc_2CFA46
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ReInit_2CFA36()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_COUNT_OF_IDS)
		"ADDS R2, #1\n"
		"CMP R2, R0\n"
		"BNE 1f\n"
		"MOVS R4, #0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_SCM_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ReInit_2CFA46_thumb)

		// Branches
		"1:\n"	// loc_2CF97C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ReInit_2CF97C_thumb)
		);
}

// patch for 0x2CFF66
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveAllUnusedModels_2CFF6E = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveAllUnusedModels_2CFF70_thumb = 0;	// loc_2CFF70
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveAllUnusedModels_2CFF66()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_TXD_BASE_ID)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CStreaming__RemoveAllUnusedModels_2CFF6E)
		"LDR R9, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveAllUnusedModels_2CFF70_thumb)
		);
}

// patch for 0x2CFFB6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__SetMissionDoesntRequireModel_2CFFBE = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__SetMissionDoesntRequireModel_2CFFC0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__SetMissionDoesntRequireModel_2CFFB6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R9, FILE_TYPE_DFF_LAST_ID)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CStreaming__SetMissionDoesntRequireModel_2CFFBE)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, FILE_TYPE_TXD_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__SetMissionDoesntRequireModel_2CFFC0_thumb)
		);
}

// patch for 0x2D00E8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D024C_thumb = 0;	// loc_2D024C
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D00F2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveModel_2D00E8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_DFF_LAST_ID)
		"CMP R11, R0\n"
		"BGT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D00F2_thumb)

		// Branches
		"1:\n"	// loc_2D024C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D024C_thumb)
		);
}

// patch for 0x2D024C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0262_thumb = 0;	// loc_2D0262
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0258_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveModel_2D024C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_TXD_LAST_ID)
		"CMP R11, R0\n"
		"BGT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_TXD_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0258_thumb)

		// Branches
		"1:\n"	// loc_2D0262
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0262_thumb)
		);
}

// patch for 0x2D0262
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0278_thumb = 0;	// loc_2D0278
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D026E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveModel_2D0262()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_COL_LAST_ID)
		"CMP R11, R0\n"
		"BGT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_COL_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D026E_thumb)

		// Branches
		"1:\n"	// loc_2D0278
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0278_thumb)
		);
}

// patch for 0x2D0278
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D028E_thumb = 0;	// loc_2D028E
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0284_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveModel_2D0278()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_LAST_ID)
		"CMP R11, R0\n"
		"BGT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0284_thumb)

		// Branches
		"1:\n"	// loc_2D028E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D028E_thumb)
		);
}

// patch for 0x2D028E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D02AA_thumb = 0;	// loc_2D02AA
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D029C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveModel_2D028E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_DAT_LAST_ID)
		"CMP R11, R0\n"
		"BGT 1f\n"
		"LDR R0, =("/* ThePaths_ptr */"0x677378 - 0x2D02A4)\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_DAT_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D029C_thumb)

		// Branches
		"1:\n"	// loc_2D02AA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D02AA_thumb)
		);
}

// patch for 0x2D02AA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D02C0_thumb = 0;	// loc_2D02C0
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D02B6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveModel_2D02AA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_LAST_ID)
		"CMP R11, R0\n"
		"BGT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D02B6_thumb)

		// Branches
		"1:\n"	// loc_2D02C0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D02C0_thumb)
		);
}

// patch for 0x2D02C0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D02D6_thumb = 0;	// loc_2D02D6
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D02C8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveModel_2D02C0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_SCM_BASE_ID)
		"CMP R11, R0\n"
		"BLT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D02C8_thumb)

		// Branches
		"1:\n"	// loc_2D02D6
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D02D6_thumb)
		);
}

// patch for 0x2D03BC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D03CA_thumb = 0;	// loc_2D03CA
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D03C4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveModel_2D03BC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_DFF_LAST_ID)
		"CMP R11, R0\n"
		"BGT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D03C4_thumb)

		// Branches
		"1:\n"	// loc_2D03CA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D03CA_thumb)
		);
}

// patch for 0x2D03CA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D03E0_thumb = 0;	// loc_2D03E0
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D03D6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveModel_2D03CA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_TXD_LAST_ID)
		"CMP R11, R0\n"
		"BGT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_TXD_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D03D6_thumb)

		// Branches
		"1:\n"	// loc_2D03E0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D03E0_thumb)
		);
}

// patch for 0x2D03E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D03F6_thumb = 0;	// loc_2D03F6
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D03EC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveModel_2D03E0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_COL_LAST_ID)
		"CMP R11, R0\n"
		"BGT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_COL_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D03EC_thumb)

		// Branches
		"1:\n"	// loc_2D03F6
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D03F6_thumb)
		);
}

// patch for 0x2D03F6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D040C_thumb = 0;	// loc_2D040C
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0402_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveModel_2D03F6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_LAST_ID)
		"CMP R11, R0\n"
		"BGT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0402_thumb)

		// Branches
		"1:\n"	// loc_2D040C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D040C_thumb)
		);
}

// patch for 0x2D040C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0416_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveModel_2D040C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_BASE_ID)
		"SUB R0, R11, R0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_COUNT_MINUS_ONE)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0416_thumb)
		);
}

// patch for 0x2D041E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0434_thumb = 0;	// loc_2D0434
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0428_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveModel_2D041E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_SCM_BASE_ID)
		"CMP R11, R0\n"
		"BLT 1f\n"
		"LDR R2, =("/* _ZN11CTheScripts15StreamedScriptsE_ptr */"0x6761B8 - 0x2D0430)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0428_thumb)

		// Branches
		"1:\n"	// loc_2D0434
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveModel_2D0434_thumb)
		);
}

// patch for 0x2D24E8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ProcessLoadingChannel_2D2524_thumb = 0;	// loc_2D2524
	uintptr_t Address_GTA_SA_2_00_CStreaming__ProcessLoadingChannel_2D24F0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ProcessLoadingChannel_2D24E8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_DFF_LAST_ID)
		"CMP R6, R0\n"
		"BGT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ProcessLoadingChannel_2D24F0_thumb)

		// Branches
		"1:\n"	// loc_2D2524
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ProcessLoadingChannel_2D2524_thumb)
		);
}

// patch for 0x2D2524
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ProcessLoadingChannel_2D252E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ProcessLoadingChannel_2D2524()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_BASE_ID)
		"SUBS R0, R6, R0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_COUNT)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ProcessLoadingChannel_2D252E_thumb)
		);
}

// patch for 0x2D29FE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RequestModel_2D2A08_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RequestModel_2D29FE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_DFF_LAST_ID)
		"CMP R10, R0\n"
		"STRH R1, [R9]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RequestModel_2D2A08_thumb)
		);
}

// patch for 0x2D2A88
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RequestModel_2D2A90_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RequestModel_2D2A88()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_TXD_BASE_ID)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_TXD_COUNT_MINUS_ONE)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RequestModel_2D2A90_thumb)
		);
}

// patch for 0x2D2A9C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RequestModel_2D2AC4_thumb = 0;	// loc_2D2AC4
	uintptr_t Address_GTA_SA_2_00_CStreaming__RequestModel_2D2AA4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RequestModel_2D2A9C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_DFF_LAST_ID)
		"CMP R10, R0\n"
		"BGT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RequestModel_2D2AA4_thumb)

		// Branches
		"1:\n"	// loc_2D2AC4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RequestModel_2D2AC4_thumb)
		);
}

// patch for 0x2D2AB8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RequestModel_2D2AC0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RequestModel_2D2AB8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RequestModel_2D2AC0_thumb)
		);
}

// patch for 0x2D2FA0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3030_thumb = 0;	// loc_2D3030
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D2FA8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D2FA0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_DFF_LAST_ID)
		"CMP R4, R0\n"
		"BGT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D2FA8_thumb)

		// Branches
		"1:\n"	// loc_2D3030
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3030_thumb)
		);
}

// patch for 0x2D3030
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3038_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3030()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_COL_BASE_ID)
		"SUBS R0, R4, R0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_COL_COUNT_MINUS_ONE)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3038_thumb)
		);
}

// patch for 0x2D3056
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D314C_thumb = 0;	// loc_2D314C
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3060_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3056()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_BASE_ID)
		"SUBS R0, R4, R0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_COUNT_MINUS_ONE)
		"BHI 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3060_thumb)

		// Branches
		"1:\n"	// loc_2D314C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D314C_thumb)
		);
}

// patch for 0x2D314C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3154_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D314C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_DAT_BASE_ID)
		"SUBS R2, R4, R0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_DAT_COUNT_MINUS_ONE)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3154_thumb)
		);
}

// patch for 0x2D32A2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D32D8_thumb = 0;	// loc_2D32D8
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D32AC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D32A2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_BASE_ID)
		"SUBS R6, R4, R0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_IFP_COUNT_MINUS_ONE)
		"BHI 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D32AC_thumb)

		// Branches
		"1:\n"	// loc_2D32D8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D32D8_thumb)
		);
}

// patch for 0x2D32D8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D32E2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D32D8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_RRR_BASE_ID)
		"SUBS R1, R4, R0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_RRR_COUNT_MINUS_ONE)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D32E2_thumb)
		);
}

// patch for 0x2D32EE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D33AA_thumb = 0;	// loc_2D33AA
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D32F8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D32EE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_SCM_BASE_ID)
		"CMP R4, R0\n"
		"BLT 1f\n"
		"LDR R1, =("/* _ZN11CTheScripts15StreamedScriptsE_ptr */"0x6761B8 - 0x2D32FE)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D32F8_thumb)

		// Branches
		"1:\n"	// loc_2D33AA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D33AA_thumb)
		);
}

// patch for 0x2D3308
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_1962C0_arm = 0;	// j__Z13RwStreamCloseP8RwStreamPv
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3310_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3308()
{
	__asm(
	".thumb\n"
		"BL 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3310_thumb)

		// Branches
		"1:\n"	// j__Z13RwStreamCloseP8RwStreamPv
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_1962C0_arm)
		);
}

// patch for 0x2D3312
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D331E_thumb = 0;	// loc_2D331E
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D331C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3312()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_RRR_LAST_ID)
		"CMP R4, R0\n"
		"BGT 1f\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_IFP_COUNT_MINUS_ONE)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D331C_thumb)

		// Branches
		"1:\n"	// loc_2D331E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D331E_thumb)
		);
}

// patch for 0x2D33B2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3312_thumb = 0;	// loc_2D3312
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D33B2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_COL_BASE_ID)
		"CMP R4, R0\n"
		"BGE 1f\n"
		"B 2f\n"

		// Branches
		"1:\n"	// loc_2D3312
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D3312_thumb)
		"2:\n"	// loc_2D331E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ConvertBufferToObject_2D331E_thumb)
		);
}

// patch for 0x2D3542
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AreAnimsUsedByRequestedModels_2D354A = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__AreAnimsUsedByRequestedModels_2D354C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AreAnimsUsedByRequestedModels_2D3542()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, FILE_TYPE_TXD_BASE_ID_multiplied_by_sizeof_CStreamingInfo_minus_one)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CStreaming__AreAnimsUsedByRequestedModels_2D354A)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AreAnimsUsedByRequestedModels_2D354C_thumb)
		);
}

// patch for 0x2D35B0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AreAnimsUsedByRequestedModels_2D35B8 = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__AreAnimsUsedByRequestedModels_2D35B8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AreAnimsUsedByRequestedModels_2D35B0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R9, FILE_TYPE_DFF_LAST_ID)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CStreaming__AreAnimsUsedByRequestedModels_2D35B8)
		"LDR R5, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AreAnimsUsedByRequestedModels_2D35B8_thumb)
		);
}

// patch for 0x2D368C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D370E_thumb = 0;	// loc_2D370E
	uintptr_t Address_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D3694_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D368C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_DFF_LAST_ID)
		"CMP R4, R0\n"
		"BGT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D3694_thumb)

		// Branches
		"1:\n"	// loc_2D370E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D370E_thumb)
		);
}

// patch for 0x2D36F6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D376E_thumb = 0;	// loc_2D376E
	uintptr_t Address_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D3700_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D36F6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_DFF_LAST_ID)
		"CMP R4, R0\n"
		"BGT 1f\n"
		"LDR R0, =("/* _ZN10CModelInfo16ms_modelInfoPtrsE_ptr */"0x6796D4 - 0x2D3704)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D3700_thumb)

		// Branches
		"1:\n"	// loc_2D376E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D376E_thumb)
		);
}

// patch for 0x2D370E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D3732_thumb = 0;	// loc_2D3732
	uintptr_t Address_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D371A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D370E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_TXD_LAST_ID)
		"CMP R4, R0\n"
		"BGT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_TXD_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D371A_thumb)

		// Branches
		"1:\n"	// loc_2D3732
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__FinishLoadingLargeFile_2D3732_thumb)
		);
}

// patch for 0x2D3B12
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B1C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B12()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_TXD_BASE_ID_multiplied_by_sizeof_CStreamingInfo_minus_one)
		"CMP R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B1C_thumb)
		);
}

// patch for 0x2D3B2C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3BB4_thumb = 0;	// loc_2D3BB4
	uintptr_t Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B34_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B2C()
{
	__asm(
	".thumb\n"
		"BEQ 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B34_thumb)

		// Branches
		"1:\n"	// loc_2D3BB4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3BB4_thumb)
		);
}

// patch for 0x2D3B38
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B40_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B38()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_COL_BASE_ID_multiplied_by_sizeof_CStreamingInfo_minus_one)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B40_thumb)
		);
}

// patch for 0x2D3B52
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B5C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B52()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, negated_file_ID_offset_to_array_TxdDef_parent_index)
		"LDRH R0, [R0,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B5C_thumb)
		);
}

// patch for 0x2D3B64
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B6C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B64()
{
	__asm(
	".thumb\n"
		"SXTH R0, R0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_TXD_BASE_ID)
		"ADD R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B6C_thumb)
		);
}

// patch for 0x2D3B90
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B98_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B90()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, negated_FILE_TYPE_DAT_LAST_ID_multiplied_by_sizeof_CStreamingInfo_plus_one)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B98_thumb)
		);
}

// patch for 0x2D3B9A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3BA4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3B9A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_COUNT_plus_one_then_multiplied_by_sizeof_CStreamingInfo_then_minus_two)
		"CMP R0, R1\n"
		"BHI 1f\n"
		"LDR R0, [SP,#0x68+"/* var_34 */"-0x34]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3BA4_thumb)

		// Branches
		"1:\n"	// loc_2D3BB4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__GetNextFileOnCd_2D3BB4_thumb)
		);
}

// patch for 0x2D3FA2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D3FAE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RequestModelStream_2D3FA2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_BASE_ID)
		"ADD R5, R6, R6,LSL#2\n"
		"SUBS R0, R6, R0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_COUNT_MINUS_ONE)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D3FAE_thumb)
		);
}

// patch for 0x2D407E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D4086 = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D4088_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RequestModelStream_2D407E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_DFF_LAST_ID)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D4086)
		"STR R0, [SP,#0x70+"/* var_38 */"-0x38]\n"
		"LDR R0, =("/* _ZN10CStreaming16ms_aInfoForModelE_ptr */"0x677DD8 - 0x2D408C)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D4088_thumb)
		);
}

// patch for 0x2D4178
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D4180_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RequestModelStream_2D4178()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_DFF_LAST_ID)
		"MOV LR, #0xFFFF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D4180_thumb)
		);
}

// patch for 0x2D418C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D4194_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RequestModelStream_2D418C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID_multiplied_by_sizeof_CStreamingInfo_plus_m_status)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D4194_thumb)
		);
}

// patch for 0x2D41A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D41A8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RequestModelStream_2D41A0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_BASE_ID)
		"SUBS R0, R6, R0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_COUNT_MINUS_ONE)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D41A8_thumb)
		);
}

// patch for 0x2D4228
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D4232_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RequestModelStream_2D4228()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_DFF_LAST_ID)
		"MOV R12, R4\n"
		"IT EQ\n"
		"MOVEQ R0, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D4232_thumb)
		);
}

// patch for 0x2D42B4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D42BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RequestModelStream_2D42B4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_DFF_LAST_ID)
		"LDRH R0, [R0,#4]\n"
		"CMP R0, LR\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RequestModelStream_2D42BC_thumb)
		);
}

// patch for 0x2D4BFC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__LoadScene_2D4C04 = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__LoadScene_2D4C04_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__LoadScene_2D4BFC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_COUNT_OF_IDS)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CStreaming__LoadScene_2D4C04)
		"LDR R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__LoadScene_2D4C04_thumb)
		);
}

// patch for 0x2D504A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__ClearFlagForAll_2D5052 = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__ClearFlagForAll_2D5054_thumb = 0;	// loc_2D5054
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__ClearFlagForAll_2D504A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_COUNT_OF_IDS)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CStreaming__ClearFlagForAll_2D5052)
		"LDR R1, [R1]\n"
		"ADDS R1, #6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__ClearFlagForAll_2D5054_thumb)
		);
}

// patch for 0x2D54B4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D54BC = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D54C2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D54B4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_TXD_BASE_ID_multiplied_by_sizeof_CStreamingInfo_minus_one)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D54BC)
		"MOVT LR, #0xCCCC\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D54C2_thumb)
		);
}

// patch for 0x2D5538
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5540_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5538()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, negated_FILE_TYPE_DAT_LAST_ID_multiplied_by_sizeof_CStreamingInfo_plus_one)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_IFP_COUNT_plus_one_then_multiplied_by_sizeof_CStreamingInfo_then_minus_two)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5540_thumb)
		);
}

// patch for 0x2D5546
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5550_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5546()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_BASE_ID)
		"MOV R8, LR\n"
		"SUBS R0, R5, R0\n"
		"STR R0, [SP,#0x38+"/* var_34 */"-0x34]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5550_thumb)
		);
}

// patch for 0x2D5558
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5562_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5558()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_TXD_BASE_ID_multiplied_by_sizeof_CStreamingInfo_minus_one)
		"MOV R12, R9\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5562_thumb)
		);
}

// patch for 0x2D5570
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D557C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5570()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_TXD_BASE_ID_multiplied_by_sizeof_CStreamingInfo_minus_one)
		"MOV R2, R11\n"
		"MOV R12, R9\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D557C_thumb)
		);
}

// patch for 0x2D5586
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5590_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5586()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_RRR_LAST_ID_multiplied_by_sizeof_CStreamingInfo_then_plus_one)
		"MOV R2, R11\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5590_thumb)
		);
}

// patch for 0x2D5596
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D55A2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D5596()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, negated_file_ID_offset_to_array_to_CStreamedScriptInfo_status)
		"ADD R0, R0, R5,LSL#5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__RemoveLeastUsedModel_2D55A2_thumb)
		);
}

// patch for 0x2D8874
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__SetMissionDoesntRequireSpecialChar_2D887C = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__SetMissionDoesntRequireSpecialChar_2D887E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__SetMissionDoesntRequireSpecialChar_2D8874()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R9, FILE_TYPE_DFF_LAST_ID)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CStreaming__SetMissionDoesntRequireSpecialChar_2D887C)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, FILE_TYPE_TXD_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__SetMissionDoesntRequireSpecialChar_2D887E_thumb)
		);
}

// patch for 0x2E2074
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__Initialise_18E9A8_arm = 0;	// _Znaj
	uintptr_t Address_GTA_SA_2_00_CColStore__Initialise_2E207C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__Initialise_2E2074()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_COL_COUNT_multiplied_by_sizeof_CCollisionFile)
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__Initialise_2E207C_thumb)

		// Branches
		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__Initialise_18E9A8_arm)
		);
}

// patch for 0x2E207E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__Initialise_2E2088_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__Initialise_2E207E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_COL_COUNT)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_COL_COUNT)
		"BL 1f\n"
		"MOVS R1, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__Initialise_2E2088_thumb)

		// Branches
		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__Initialise_18E9A8_arm)
		);
}

// patch for 0x2E20C2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__Initialise_2E20AC_thumb = 0;	// loc_2E20AC
	uintptr_t Address_GTA_SA_2_00_CColStore__Initialise_2E20CC = 0;
	uintptr_t Address_GTA_SA_2_00_CColStore__Initialise_2E20CC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__Initialise_2E20C2()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_COL_COUNT)
		"BNE 1f\n"
		"LDR R0, =("/* _ZN9CColStore11ms_pColPoolE_ptr */"0x679660 - 0x2E20CC)\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CColStore__Initialise_2E20CC)
		"LDR R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__Initialise_2E20CC_thumb)

		// Branches
		"1:\n"	// loc_2E20AC
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__Initialise_2E20AC_thumb)
		);
}

// patch for 0x2E23BC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__Shutdown_2E23A0_thumb = 0;	// loc_2E23A0
	uintptr_t Address_GTA_SA_2_00_CColStore__Shutdown_2E23F8_thumb = 0;	// loc_2E23F8
	uintptr_t Address_GTA_SA_2_00_CColStore__Shutdown_2E23C4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__Shutdown_2E23BC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_COL_COUNT)
		"BNE 1f\n"
		"CBZ R4, 2f\n"
		"LDR R0, [R4,#8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__Shutdown_2E23C4_thumb)

		// Branches
		"1:\n"	// loc_2E23A0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__Shutdown_2E23A0_thumb)
		"2:\n"	// loc_2E23F8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__Shutdown_2E23F8_thumb)
		);
}

// patch for 0x2E2AA2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__LoadCollision_2E2AAC = 0;
	uintptr_t Address_GTA_SA_2_00_CColStore__LoadCollision_2E2AAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__LoadCollision_2E2AA2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, FILE_TYPE_COL_BASE_ID_PLUS_ONE)
		"MOVS R6, #0\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CColStore__LoadCollision_2E2AAC)
		"MOVS R4, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__LoadCollision_2E2AAC_thumb)
		);
}

// patch for 0x2E2B08
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__LoadCollision_2E2ACC_thumb = 0;	// loc_2E2ACC
	uintptr_t Address_GTA_SA_2_00_CColStore__LoadCollision_2E2B18_thumb = 0;	// loc_2E2B18
	uintptr_t Address_GTA_SA_2_00_CColStore__LoadCollision_2E2B10_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__LoadCollision_2E2B08()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_COL_COUNT_MINUS_ONE)
		"BNE 1f\n"
		"LDR R0, [SP,#0x30+"/* var_2C */"-0x2C]\n"
		"CBNZ R0, 2f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__LoadCollision_2E2B10_thumb)

		// Branches
		"1:\n"	// loc_2E2ACC
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__LoadCollision_2E2ACC_thumb)
		"2:\n"	// loc_2E2B18
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__LoadCollision_2E2B18_thumb)
		);
}

// patch for 0x2E2C94
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_2E2C9C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_2E2C94()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_COL_BASE_ID_PLUS_ONE)
		"MOV R9, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_2E2C9C_thumb)
		);
}

// patch for 0x2E2C9E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_2E2CA8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_2E2C9E()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_COL_BASE_ID_PLUS_ONE_then_multiplied_by_sizeof_CStreamingInfo_then_minus_308)
		"ADD R6, R0, #0x144\n"
		"LDR R0, =("/* _ZN9CColStore11ms_pColPoolE_ptr */"0x679660 - 0x2E2CAC)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_2E2CA8_thumb)
		);
}

// patch for 0x2E2D6A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_19F7D0_arm = 0;	// j__ZN6CTimer6ResumeEv
	uintptr_t Address_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_2E2D74_thumb = 0;	// loc_2E2D74
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_2E2D6A()
{
	__asm(
	".thumb\n"
		"BL 1f\n"
		"LDR R3, [SP,#0x40+"/* var_40 */"-0x40]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_COL_BASE_ID_PLUS_ONE)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_2E2D74_thumb)

		// Branches
		"1:\n"	// j__ZN6CTimer6ResumeEv
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_19F7D0_arm)
		);
}

// patch for 0x2E2D7C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_2E2D84_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_2E2D7C()
{
	__asm(
	".thumb\n"
		"ADDS R5, #0x2C\n"
		"ADDS R6, #0x14\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, FILE_TYPE_COL_COUNT_MINUS_ONE)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__EnsureCollisionIsInMemory_2E2D84_thumb)
		);
}

// patch for 0x2E2E58
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__RequestCollision_2E2E62_thumb = 0;	// loc_2E2E62
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__RequestCollision_2E2E58()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R9, FILE_TYPE_COL_BASE_ID_PLUS_ONE)
		"MOVS R4, #0\n"
		"LDR R11, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__RequestCollision_2E2E62_thumb)
		);
}

// patch for 0x2E2EEA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__RequestCollision_2E2EF4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__RequestCollision_2E2EEA()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, FILE_TYPE_COL_COUNT_MINUS_ONE)
		"BNE 1f\n"
		"ADD SP, SP, #8\n"
		"VPOP {D8-D9}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__RequestCollision_2E2EF4_thumb)

		// Branches
		"1:\n"	// loc_2E2E62
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__RequestCollision_2E2E62_thumb)
		);
}

// patch for 0x2E300C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E2F8E_thumb = 0;	// loc_2E2F8E
	uintptr_t Address_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E3014_thumb = 0;	// loc_2E3014
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E300C()
{
	__asm(
	".thumb\n"
		"ADDS R2, R3, #1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, FILE_TYPE_COL_COUNT_MINUS_ONE)
		"BLT 1f\n"
		"MOVS R0, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E3014_thumb)

		// Branches
		"1:\n"	// loc_2E2F8E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E2F8E_thumb)
		);
}

// patch for 0x2E301A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E3024_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E301A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, FILE_TYPE_COL_COUNT_MINUS_ONE)
		"MOV R0, #0\n"
		"BGT 1f\n"
		"LDR R0, =("/* _ZN9CColStore11ms_pColPoolE_ptr */"0x679660 - 0x2E302A)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E3024_thumb)

		// Branches
		"1:\n"	// loc_2E3014
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E3014_thumb)
		);
}

// patch for 0x2E3044
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E302A_thumb = 0;	// loc_2E302A
	uintptr_t Address_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E304C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E3044()
{
	__asm(
	".thumb\n"
		"ADDS R1, #0x2C\n"
		"MOVS R0, #0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, FILE_TYPE_COL_COUNT_MINUS_ONE)
		"BLT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E304C_thumb)

		// Branches
		"1:\n"	// loc_2E302A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__HasCollisionLoaded_2E302A_thumb)
		);
}

// patch for 0x2E3084
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__RemoveAllCollision_2E308C = 0;
	uintptr_t Address_GTA_SA_2_00_CColStore__RemoveAllCollision_2E3090_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__RemoveAllCollision_2E3084()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, FILE_TYPE_COL_BASE_ID_PLUS_ONE)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CColStore__RemoveAllCollision_2E308C)
		"LDR R0, [R0]\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_COL_BASE_ID_PLUS_ONE_then_multiplied_by_sizeof_CStreamingInfo_then_minus_308)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__RemoveAllCollision_2E3090_thumb)
		);
}

// patch for 0x2E30BC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__RemoveAllCollision_2E309A_thumb = 0;	// loc_2E309A
	uintptr_t Address_GTA_SA_2_00_CColStore__RemoveAllCollision_2E30C4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__RemoveAllCollision_2E30BC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_COL_COUNT_MINUS_ONE)
		"BNE 1f\n"
		"POP {R8}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__RemoveAllCollision_2E30C4_thumb)

		// Branches
		"1:\n"	// loc_2E309A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__RemoveAllCollision_2E309A_thumb)
		);
}

// patch for 0x2E30EC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__LoadAllBoundingBoxes_2E30F6 = 0;	// loc_2E30F6
	uintptr_t Address_GTA_SA_2_00_CColStore__LoadAllBoundingBoxes_2E30F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__LoadAllBoundingBoxes_2E30EC()
{
	__asm(
	".thumb\n"
		"MOVS R5, #0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, FILE_TYPE_COL_BASE_ID_PLUS_ONE)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CColStore__LoadAllBoundingBoxes_2E30F6)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__LoadAllBoundingBoxes_2E30F4_thumb)
		);
}

// patch for 0x2E311E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__LoadAllBoundingBoxes_2E30F6_thumb = 0;	// loc_2E30F6
	uintptr_t Address_GTA_SA_2_00_CColStore__LoadAllBoundingBoxes_2E3128_thumb = 0;	// off_2E3128
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__LoadAllBoundingBoxes_2E311E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_COL_COUNT_MINUS_ONE)
		"BNE 1f\n"
		"POP {R8}\n"
		"POP {R4-R7,PC}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__LoadAllBoundingBoxes_2E3128_thumb)

		// Branches
		"1:\n"	// loc_2E30F6
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__LoadAllBoundingBoxes_2E30F6_thumb)
		);
}

// patch for 0x2E3138
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__LoadAllCollision_2E3140 = 0;	// loc_2E3140
	uintptr_t Address_GTA_SA_2_00_CColStore__LoadAllCollision_2E3140_thumb = 0;	// loc_2E3140
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__LoadAllCollision_2E3138()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, FILE_TYPE_COL_BASE_ID_PLUS_ONE)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CColStore__LoadAllCollision_2E3140)
		"LDR R6, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__LoadAllCollision_2E3140_thumb)
		);
}

// patch for 0x2E3168
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__LoadAllCollision_2E3170_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__LoadAllCollision_2E3168()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_COL_COUNT_MINUS_ONE)
		"BNE 1f\n"
		"POP {R8}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__LoadAllCollision_2E3170_thumb)

		// Branches
		"1:\n"	// loc_2E3140
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__LoadAllCollision_2E3140_thumb)
		);
}

// patch for 0x2E3232
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColStore__BoundingBoxesPostProcess_2E31AE_thumb = 0;	// loc_2E31AE
	uintptr_t Address_GTA_SA_2_00_CColStore__BoundingBoxesPostProcess_2E323C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColStore__BoundingBoxesPostProcess_2E3232()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, FILE_TYPE_COL_COUNT)
		"BNE 1f\n"
		"ADD SP, SP, #0x28\n"
		"VPOP {D8-D9}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__BoundingBoxesPostProcess_2E323C_thumb)

		// Branches
		"1:\n"	// loc_2E31AE
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColStore__BoundingBoxesPostProcess_2E31AE_thumb)
		);
}

// patch for 0x319B1E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B28 = 0;
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B28_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319B1E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R10, FILE_TYPE_DAT_BASE_ID)
		"LDR R1, =("/* ToBeStreamedForScript_ptr */"0x678944 - 0x319B2C)\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B28)
		"LDR R2, [SP,#0x58+"/* var_54 */"-0x54]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B28_thumb)
		);
}

// patch for 0x319FA4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FA4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_DAT_BASE_ID)
		"MOVS R1, #0\n"
		"ADD R0, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FAC_thumb)
		);
}

// patch for 0x321B36
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicleRecording__InitAtStartOfGame_321B40 = 0;
	uintptr_t Address_GTA_SA_2_00_CVehicleRecording__InitAtStartOfGame_321B40_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicleRecording__InitAtStartOfGame_321B36()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_RRR_COUNT)
		"MOVS R2, #0\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CVehicleRecording__InitAtStartOfGame_321B40)
		"LDR R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicleRecording__InitAtStartOfGame_321B40_thumb)
		);
}

// patch for 0x321BA4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicleRecording__InitAtStartOfGame_321BAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicleRecording__InitAtStartOfGame_321BA4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_RRR_COUNT)
		"VST1.32 {D16-D17}, [R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicleRecording__InitAtStartOfGame_321BAC_thumb)
		);
}

// patch for 0x321C36
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicleRecording__Init_321C40_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicleRecording__Init_321C36()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_RRR_COUNT)
		"VST1.32 {D16-D17}, [R2]\n"
		"MOVS R2, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicleRecording__Init_321C40_thumb)
		);
}

// patch for 0x321C72
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicleRecording__ShutDown_321C7E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicleRecording__ShutDown_321C72()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, FILE_TYPE_RRR_BASE_ID)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_RRR_COUNT)
		"MOV R8, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicleRecording__ShutDown_321C7E_thumb)
		);
}

// patch for 0x321DFC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicleRecording__StartPlaybackRecordedCar_321E04_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicleRecording__StartPlaybackRecordedCar_321DFC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_RRR_BASE_ID)
		"MOVS R1, #0xC\n"
		"ADD R0, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicleRecording__StartPlaybackRecordedCar_321E04_thumb)
		);
}

// patch for 0x32204C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicleRecording__RequestRecordingFile_322054_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicleRecording__RequestRecordingFile_32204C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_RRR_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #0xC\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicleRecording__RequestRecordingFile_322054_thumb)
		);
}

// patch for 0x32240E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicleRecording__StopPlaybackRecordedCar_32241A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicleRecording__StopPlaybackRecordedCar_32240E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_RRR_BASE_ID)
		"STR R4, [R6,#4]\n"
		"ADD R0, R5\n"
		"POP {R11}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicleRecording__StopPlaybackRecordedCar_32241A_thumb)
		);
}

// patch for 0x32258A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicleRecording__StopPlaybackWithIndex_322596_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicleRecording__StopPlaybackWithIndex_32258A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_RRR_BASE_ID)
		"STR R6, [R4,#4]\n"
		"ADD R0, R5\n"
		"POP {R11}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicleRecording__StopPlaybackWithIndex_322596_thumb)
		);
}

// patch for 0x3234B6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicleRecording__SkipToEndAndStopPlaybackRecordedCar_3234C0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicleRecording__SkipToEndAndStopPlaybackRecordedCar_3234B6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_RRR_BASE_ID)
		"STR R4, [R6,#4]\n"
		"ADD R0, R5\n"
		"ADD SP, SP, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicleRecording__SkipToEndAndStopPlaybackRecordedCar_3234C0_thumb)
		);
}

// patch for 0x323A8C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicleRecording__SaveOrRetrieveDataForThisFrame_323A94_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicleRecording__SaveOrRetrieveDataForThisFrame_323A8C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_RRR_BASE_ID)
		"STR R9, [R6,#4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicleRecording__SaveOrRetrieveDataForThisFrame_323A94_thumb)
		);
}

// patch for 0x3242D0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicleRecording__RemoveRecordingFile_3242D8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicleRecording__RemoveRecordingFile_3242D0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_RRR_BASE_ID)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, FILE_TYPE_RRR_COUNT)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicleRecording__RemoveRecordingFile_3242D8_thumb)
		);
}

// patch for 0x32441A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicleRecording__RemoveAllRecordingsThatArentUsed_324426_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicleRecording__RemoveAllRecordingsThatArentUsed_32441A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, FILE_TYPE_RRR_BASE_ID)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_RRR_COUNT)
		"MOV R8, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicleRecording__RemoveAllRecordingsThatArentUsed_324426_thumb)
		);
}

// patch for 0x32F868
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CScriptsForBrains__StartOrRequestNewStreamedScriptBrain_32F870 = 0;
	uintptr_t Address_GTA_SA_2_00_CScriptsForBrains__StartOrRequestNewStreamedScriptBrain_32F872_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CScriptsForBrains__StartOrRequestNewStreamedScriptBrain_32F868()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_SCM_BASE_ID)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CScriptsForBrains__StartOrRequestNewStreamedScriptBrain_32F870)
		"LDRSH R1, [R4,R1,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CScriptsForBrains__StartOrRequestNewStreamedScriptBrain_32F872_thumb)
		);
}

// patch for 0x32FC16
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CScriptsForBrains__RequestAttractorScriptBrainWithThisName_32FC22 = 0;
	uintptr_t Address_GTA_SA_2_00_CScriptsForBrains__RequestAttractorScriptBrainWithThisName_32FC20_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CScriptsForBrains__RequestAttractorScriptBrainWithThisName_32FC16()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_SCM_BASE_ID)
		"LDRSH R1, [R4,#-0xC]\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CScriptsForBrains__RequestAttractorScriptBrainWithThisName_32FC22)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CScriptsForBrains__RequestAttractorScriptBrainWithThisName_32FC20_thumb)
		);
}

// patch for 0x32FCF8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CScriptsForBrains__HasAttractorScriptBrainWithThisNameLoaded_32FD00_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CScriptsForBrains__HasAttractorScriptBrainWithThisNameLoaded_32FCF8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_SCM_BASE_ID_multiplied_by_sizeof_CStreamingInfo_plus_uiLoadFlag)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CScriptsForBrains__HasAttractorScriptBrainWithThisNameLoaded_32FD00_thumb)
		);
}

// patch for 0x32FED2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTheScripts__ProcessWaitingForScriptBrainArray_32FEDC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTheScripts__ProcessWaitingForScriptBrainArray_32FED2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, FILE_TYPE_SCM_BASE_ID)
		"ADD R0, R3\n"
		"ADD R3, R0, R0,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__ProcessWaitingForScriptBrainArray_32FEDC_thumb)
		);
}

// patch for 0x32FF78
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTheScripts__ProcessWaitingForScriptBrainArray_32FF82_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTheScripts__ProcessWaitingForScriptBrainArray_32FF78()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, FILE_TYPE_SCM_BASE_ID)
		"ADD R0, R3\n"
		"ADD R3, R0, R0,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__ProcessWaitingForScriptBrainArray_32FF82_thumb)
		);
}

// patch for 0x32FFB8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTheScripts__ProcessWaitingForScriptBrainArray_32FFC2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTheScripts__ProcessWaitingForScriptBrainArray_32FFB8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, FILE_TYPE_SCM_BASE_ID)
		"ADD R0, R3\n"
		"ADD R3, R0, R0,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTheScripts__ProcessWaitingForScriptBrainArray_32FFC2_thumb)
		);
}

// patch for 0x33546A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreamedScripts__StartNewStreamedScript_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CStreamedScripts__StartNewStreamedScript_335476_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreamedScripts__StartNewStreamedScript_33546A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_SCM_BASE_ID)
		"MOVS R1, #0xC\n"
		"ADD R0, R4\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreamedScripts__StartNewStreamedScript_335476_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreamedScripts__StartNewStreamedScript_192964_arm)
		);
}

// patch for 0x33549C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreamedScripts__StartNewStreamedScript_191750_arm = 0;	// j__ZN10CStreaming28SetMissionDoesntRequireModelEi
	uintptr_t Address_GTA_SA_2_00_CStreamedScripts__StartNewStreamedScript_3354A6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreamedScripts__StartNewStreamedScript_33549C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_SCM_BASE_ID)
		"ADD R0, R4\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreamedScripts__StartNewStreamedScript_3354A6_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming28SetMissionDoesntRequireModelEi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreamedScripts__StartNewStreamedScript_191750_arm)
		);
}

// patch for 0x3354FC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreamedScripts__GetStreamedScriptWithThisStartAddress_335506_thumb = 0;	// loc_335506
	uintptr_t Address_GTA_SA_2_00_CStreamedScripts__GetStreamedScriptWithThisStartAddress_335504_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreamedScripts__GetStreamedScriptWithThisStartAddress_3354FC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R12, FILE_TYPE_SCM_COUNT_MINUS_ONE)
		"BHI 1f\n"
		"CMP LR, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreamedScripts__GetStreamedScriptWithThisStartAddress_335504_thumb)

		// Branches
		"1:\n"	// loc_335506
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreamedScripts__GetStreamedScriptWithThisStartAddress_335506_thumb)
		);
}

// patch for 0x339A90
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands2200To2299_339A98_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands2200To2299_339A90()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_SCM_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands2200To2299_339A98_thumb)
		);
}

// patch for 0x339AD2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands2200To2299_339ADC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands2200To2299_339AD2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_SCM_BASE_ID_multiplied_by_sizeof_CStreamingInfo_plus_uiLoadFlag)
		"LDRB R1, [R0,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands2200To2299_339ADC_thumb)
		);
}

// patch for 0x33B17A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands2300To2399_191750_arm = 0;	// j__ZN10CStreaming28SetMissionDoesntRequireModelEi
	uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands2300To2399_33B184_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands2300To2399_33B17A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_SCM_BASE_ID)
		"ADD R0, R1\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands2300To2399_33B184_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming28SetMissionDoesntRequireModelEi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands2300To2399_191750_arm)
		);
}

// patch for 0x33B1AA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands2300To2399_18CCAC_arm = 0;	// j__ZN10CStreaming11RemoveModelEi
	uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands2300To2399_33B1B4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands2300To2399_33B1AA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_SCM_BASE_ID)
		"ADD R0, R1\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands2300To2399_33B1B4_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming11RemoveModelEi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands2300To2399_18CCAC_arm)
		);
}

// patch for 0x35122A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands1200To1299_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands1200To1299_351236_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands1200To1299_35122A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R5\n"
		"MOVS R1, #4\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands1200To1299_351236_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands1200To1299_192964_arm)
		);
}

// patch for 0x351294
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands1200To1299_191750_arm = 0;	// j__ZN10CStreaming28SetMissionDoesntRequireModelEi
	uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands1200To1299_35129E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands1200To1299_351294()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R5\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands1200To1299_35129E_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming28SetMissionDoesntRequireModelEi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands1200To1299_191750_arm)
		);
}

// patch for 0x35FF88
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CShopping__LoadPrices_35FF90_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CShopping__LoadPrices_35FF88()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #0x1A\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CShopping__LoadPrices_35FF90_thumb)
		);
}

// patch for 0x384D52
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTimeInfo__FindOtherTimeModel_384D5A = 0;
	uintptr_t Address_GTA_SA_2_00_CTimeInfo__FindOtherTimeModel_384D5C_thumb = 0;	// loc_384D5C
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTimeInfo__FindOtherTimeModel_384D52()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R10, FILE_TYPE_DFF_LAST_ID)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CTimeInfo__FindOtherTimeModel_384D5A)
		"LDR R4, [R1]\n"
		"MOVS R1, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTimeInfo__FindOtherTimeModel_384D5C_thumb)
		);
}

// patch for 0x384D7C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTimeInfo__FindOtherTimeModel_384D84_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTimeInfo__FindOtherTimeModel_384D7C()
{
	__asm(
	".thumb\n"
		"BLT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_TXD_BASE_ID)
		"CMP R1, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTimeInfo__FindOtherTimeModel_384D84_thumb)

		// Branches
		"1:\n"	// loc_384D5C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTimeInfo__FindOtherTimeModel_384D5C_thumb)
		);
}

// patch for 0x385A2E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CModelInfo__ReInit2dEffects_385A36 = 0;
	uintptr_t Address_GTA_SA_2_00_CModelInfo__ReInit2dEffects_385A38 = 0;
	uintptr_t Address_GTA_SA_2_00_CModelInfo__ReInit2dEffects_385A38_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CModelInfo__ReInit2dEffects_385A2E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_TXD_BASE_ID)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CModelInfo__ReInit2dEffects_385A36)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CModelInfo__ReInit2dEffects_385A38)
		"LDR R4, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CModelInfo__ReInit2dEffects_385A38_thumb)
		);
}

// patch for 0x385D58
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CModelInfo__GetModelInfo_385D60 = 0;
	uintptr_t Address_GTA_SA_2_00_CModelInfo__GetModelInfo_385D60_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CModelInfo__GetModelInfo_385D58()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, FILE_TYPE_DFF_LAST_ID)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CModelInfo__GetModelInfo_385D60)
		"LDR R1, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CModelInfo__GetModelInfo_385D60_thumb)
		);
}

// patch for 0x385DF0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CModelInfo__GetModelInfoFromHashKey_385DF8 = 0;
	uintptr_t Address_GTA_SA_2_00_CModelInfo__GetModelInfoFromHashKey_385DFA_thumb = 0;	// loc_385DFA
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CModelInfo__GetModelInfoFromHashKey_385DF0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(LR, FILE_TYPE_DFF_LAST_ID)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CModelInfo__GetModelInfoFromHashKey_385DF8)
		"LDR R12, [R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CModelInfo__GetModelInfoFromHashKey_385DFA_thumb)
		);
}

// patch for 0x385E38
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CModelInfo__GetModelInfoUInt16_385E40 = 0;
	uintptr_t Address_GTA_SA_2_00_CModelInfo__GetModelInfoUInt16_385E40_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CModelInfo__GetModelInfoUInt16_385E38()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, FILE_TYPE_DFF_LAST_ID)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CModelInfo__GetModelInfoUInt16_385E40)
		"LDR R1, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CModelInfo__GetModelInfoUInt16_385E40_thumb)
		);
}

// patch for 0x3863A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CModelInfo__IsVehicleModelType_3863C4_thumb = 0;	// loc_3863C4
	uintptr_t Address_GTA_SA_2_00_CModelInfo__IsVehicleModelType_3863A8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CModelInfo__IsVehicleModelType_3863A0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_DFF_LAST_ID)
		"CMP R0, R1\n"
		"BGT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CModelInfo__IsVehicleModelType_3863A8_thumb)

		// Branches
		"1:\n"	// loc_3863C4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CModelInfo__IsVehicleModelType_3863C4_thumb)
		);
}

// patch for 0x38DC50
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAnimManager__Shutdown_38DC5E_thumb = 0;	// loc_38DC5E
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAnimManager__Shutdown_38DC50()
{
	__asm(
	".thumb\n"
		"PUSH {R4-R7,LR}\n"
		"ADD R7, SP, #0xC\n"
		"PUSH {R11}\n"
		"MOVS R4, #0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_IFP_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAnimManager__Shutdown_38DC5E_thumb)
		);
}

// patch for 0x38DC66
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAnimManager__Shutdown_38DC70 = 0;
	uintptr_t Address_GTA_SA_2_00_CAnimManager__Shutdown_38DC70_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAnimManager__Shutdown_38DC66()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, FILE_TYPE_IFP_COUNT)
		"BNE 1f\n"
		"LDR R0, =("/* _ZN12CAnimManager16ms_numAnimationsE_ptr */"0x677EF0 - 0x38DC70)\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CAnimManager__Shutdown_38DC70)
		"LDR R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAnimManager__Shutdown_38DC70_thumb)

		// Branches
		"1:\n"	// loc_38DC5E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAnimManager__Shutdown_38DC5E_thumb)
		);
}

// patch for 0x3EF4B2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CFileLoader__LoadCollisionFile_3EF4BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CFileLoader__LoadCollisionFile_3EF4B2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, FILE_TYPE_DFF_LAST_ID)
		"VLD1.8 {D16-D17}, [R2]\n"
		"ADDS R2, #0xE\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CFileLoader__LoadCollisionFile_3EF4BC_thumb)
		);
}

// patch for 0x448C80
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__Update_448C88_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__Update_448C80()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__Update_448C88_thumb)
		);
}

// patch for 0x449AA0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__ReferenceAnims_449AA8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__ReferenceAnims_449AA0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__ReferenceAnims_449AA8_thumb)
		);
}

// patch for 0x44A03C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__Setup_44A044_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__Setup_44A03C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__Setup_44A044_thumb)
		);
}

// patch for 0x4530CE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CObject___CObject_191750_arm = 0;	// j__ZN10CStreaming28SetMissionDoesntRequireModelEi
	uintptr_t Address_GTA_SA_2_00_CObject___CObject_4530D8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CObject___CObject_4530CE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_SCM_BASE_ID)
		"ADD R0, R1\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CObject___CObject_4530D8_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming28SetMissionDoesntRequireModelEi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CObject___CObject_191750_arm)
		);
}

// patch for 0x457F92
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CClothes__RequestMotionGroupAnims_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CClothes__RequestMotionGroupAnims_457F9E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CClothes__RequestMotionGroupAnims_457F92()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_IFP_BASE_ID)
		"ADDS R0, R4, R6\n"
		"MOVS R1, #0x12\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CClothes__RequestMotionGroupAnims_457F9E_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CClothes__RequestMotionGroupAnims_192964_arm)
		);
}

// patch for 0x457FBA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CClothes__RequestMotionGroupAnims_457FC4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CClothes__RequestMotionGroupAnims_457FBA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_IFP_BASE_ID)
		"VCMPE.F32 S18, S16\n"
		"ADD R0, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CClothes__RequestMotionGroupAnims_457FC4_thumb)
		);
}

// patch for 0x465F7E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColAccel__startCache_18E9A8_arm = 0;	// _Znaj
	uintptr_t Address_GTA_SA_2_00_CColAccel__startCache_4661B0 = 0;	// dword_4661B0
	uintptr_t Address_GTA_SA_2_00_CColAccel__startCache_465F88_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColAccel__startCache_465F7E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_COUNT_multiplied_by_sizeof_IplDef)
		"BL 1f\n"
		ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CColAccel__startCache_4661B0)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColAccel__startCache_465F88_thumb)

		// Branches
		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColAccel__startCache_18E9A8_arm)
		);
}

// patch for 0x465F92
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColAccel__startCache_465F8E_thumb = 0;	// loc_465F8E
	uintptr_t Address_GTA_SA_2_00_CColAccel__startCache_465F9C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColAccel__startCache_465F92()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IPL_COUNT_multiplied_by_sizeof_IplDef)
		"VST1.32 {D8-D9}, [R2]\n"
		"BNE 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColAccel__startCache_465F9C_thumb)

		// Branches
		"1:\n"	// loc_465F8E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColAccel__startCache_465F8E_thumb)
		);
}

// patch for 0x46610A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColAccel__startCache_466112 = 0;
	uintptr_t Address_GTA_SA_2_00_CColAccel__startCache_466114_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColAccel__startCache_46610A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_IPL_COUNT_multiplied_by_sizeof_IplDef)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CColAccel__startCache_466112)
		"LDR R0, [R0]\n"
		"LDR R1, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColAccel__startCache_466114_thumb)
		);
}

// patch for 0x4662A4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CColAccel__endCache_4662AC = 0;
	uintptr_t Address_GTA_SA_2_00_CColAccel__endCache_4662AC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CColAccel__endCache_4662A4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, FILE_TYPE_IPL_COUNT_multiplied_by_sizeof_IplDef)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CColAccel__endCache_4662AC)
		"LDR R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CColAccel__endCache_4662AC_thumb)
		);
}

// patch for 0x466B06
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CFileLoader__LoadLevel_18C748_arm = 0;	// j__ZN9CColStore20LoadAllBoundingBoxesEv
	uintptr_t Address_GTA_SA_2_00_CFileLoader__LoadLevel_466B10_thumb = 0;	// loc_466B10
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CFileLoader__LoadLevel_466B06()
{
	__asm(
	".thumb\n"
		"BL 1f\n"
		"LDR R4, [SP,#0x88+"/* var_84 */"-0x84]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_TXD_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CFileLoader__LoadLevel_466B10_thumb)

		// Branches
		"1:\n"	// j__ZN9CColStore20LoadAllBoundingBoxesEv
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CFileLoader__LoadLevel_18C748_arm)
		);
}

// patch for 0x46B960
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CFileLoader__LoadCollisionFileFirstTime_46B968_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CFileLoader__LoadCollisionFileFirstTime_46B960()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, FILE_TYPE_DFF_LAST_ID)
		"VLD1.8 {D16-D17}, [R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CFileLoader__LoadCollisionFileFirstTime_46B968_thumb)
		);
}

// patch for 0x46BAA0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__Init2_46BAA8 = 0;	// loc_46BAA8
	uintptr_t Address_GTA_SA_2_00_CStreaming__Init2_46BAA8_thumb = 0;	// loc_46BAA8
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__Init2_46BAA0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_COUNT_OF_IDS)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CStreaming__Init2_46BAA8)
		"LDR R4, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__Init2_46BAA8_thumb)
		);
}

// patch for 0x46BC04
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__Init2_46BC0C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__Init2_46BC04()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_TXD_BASE_ID)
		"MOV R8, #2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__Init2_46BC0C_thumb)
		);
}

// patch for 0x46BC3C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__Init2_46BC46_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__Init2_46BC3C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, FILE_TYPE_TXD_COUNT_multiplied_by_sizeof_TxdDef)
		"LDR R1, =("/* _ZN10CStreaming16ms_aInfoForModelE_ptr */"0x677DD8 - 0x46BC50)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__Init2_46BC46_thumb)
		);
}

// patch for 0x46C150
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C15A_thumb = 0;	// loc_46C15A
	uintptr_t Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_19CA38_arm = 0;	// j__ZN9CColStore10AddColSlotEPKc
	uintptr_t Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C15E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C150()
{
	__asm(
	".thumb\n"
		"BNE 1f\n"
		"MOV R0, R10\n"
		"BL 2f\n"
		"STR R0, [SP,#0x78+"/* var_28 */"-0x28]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_COL_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C15E_thumb)

		// Branches
		"1:\n"	// loc_46C15A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C15A_thumb)
		"2:\n"	// j__ZN9CColStore10AddColSlotEPKc
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_19CA38_arm)
		);
}

// patch for 0x46C1A2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C1F2_thumb = 0;	// loc_46C1F2
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C1A2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IPL_BASE_ID)
		"ADD R0, R1\n"
		"STR R0, [SP,#0x78+"/* var_28 */"-0x28]\n"
		"B 1f\n"

		// Branches
		"1:\n"	// loc_46C1F2
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C1F2_thumb)
		);
}

// patch for 0x46C1B8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C1E4_thumb = 0;	// loc_46C1E4
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C1B8()
{
	__asm(
	".thumb\n"
		"LDR R0, [SP,#0x78+"/* var_28 */"-0x28]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_DAT_BASE_ID)
		"B 1f\n"

		// Branches
		"1:\n"	// loc_46C1E4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C1E4_thumb)
		);
}

// patch for 0x46C1C0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_19D20C_arm = 0;	// j__ZN12CAnimManager17RegisterAnimBlockEPKc
	uintptr_t Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C1CA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C1C0()
{
	__asm(
	".thumb\n"
		"MOV R0, R10\n"
		"BL 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C1CA_thumb)

		// Branches
		"1:\n"	// j__ZN12CAnimManager17RegisterAnimBlockEPKc
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_19D20C_arm)
		);
}

// patch for 0x46C1CE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_19CD4C_arm = 0;	// j__ZN17CVehicleRecording21RegisterRecordingFileEPKc
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C1CE()
{
	__asm(
	".thumb\n"
		"BL 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_RRR_BASE_ID)
		"B 2f\n"

		// Branches
		"1:\n"	// j__ZN17CVehicleRecording21RegisterRecordingFileEPKc
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_19CD4C_arm)
		"2:\n"	// loc_46C1E4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C1E4_thumb)
		);
}

// patch for 0x46C1DC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_18D5CC_arm = 0;	// j__ZN16CStreamedScripts14RegisterScriptEPKc
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C1DC()
{
	__asm(
	".thumb\n"
		"BL 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_SCM_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_46C1E4_thumb)

		// Branches
		"1:\n"	// j__ZN16CStreamedScripts14RegisterScriptEPKc
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__LoadCdDirectory_18D5CC_arm)
		);
}

// patch for 0x487A1C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__Save_487A24_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__Save_487A1C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_COUNT_OF_IDS)
		"MOV R8, #0xFF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__Save_487A24_thumb)
		);
}

// patch for 0x487A6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__Load_487A74 = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__Load_487A74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__Load_487A6C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_COUNT_OF_IDS)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CStreaming__Load_487A74)
		"LDR R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__Load_487A74_thumb)
		);
}

// patch for 0x48B7E6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CScriptResourceManager__Load_48B7F0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CScriptResourceManager__Load_48B7E6()
{
	__asm(
	".thumb\n"
		"ADD R8, SP, #0x88+"/* var_78 */"-0x78\n"
		"MOVS R5, #0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R9, FILE_TYPE_IFP_BASE_ID)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CScriptResourceManager__Load_48B7F0_thumb)
		);
}

// patch for 0x48E39A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__Save_48E3A4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__Save_48E39A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IPL_COUNT)
		"STR R0, [R4]\n"
		"MOV R0, R4\n"
		"MOVS R1, #"/* byte_4 */"0x4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Save_48E3A4_thumb)
		);
}

// patch for 0x48E3EE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CIplStore__Save_48E3BC_thumb = 0;	// loc_48E3BC
	uintptr_t Address_GTA_SA_2_00_CIplStore__Save_48E3F8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CIplStore__Save_48E3EE()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, FILE_TYPE_IPL_COUNT)
		"BNE 1f\n"
		"MOVS R0, #1\n"
		"ADD SP, SP, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Save_48E3F8_thumb)

		// Branches
		"1:\n"	// loc_48E3BC
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CIplStore__Save_48E3BC_thumb)
		);
}

// patch for 0x49F662
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPed___CPed_191750_arm = 0;	// j__ZN10CStreaming28SetMissionDoesntRequireModelEi
	uintptr_t Address_GTA_SA_2_00_CPed___CPed_49F66C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPed___CPed_49F662()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_SCM_BASE_ID)
		"ADD R0, R1\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPed___CPed_49F66C_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming28SetMissionDoesntRequireModelEi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPed___CPed_191750_arm)
		);
}

// patch for 0x4C604C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlayerPed__ProcessAnimGroups_4C6054_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlayerPed__ProcessAnimGroups_4C604C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlayerPed__ProcessAnimGroups_4C6054_thumb)
		);
}

// patch for 0x4C6138
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlayerPed__ProcessAnimGroups_4C6140_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlayerPed__ProcessAnimGroups_4C6138()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlayerPed__ProcessAnimGroups_4C6140_thumb)
		);
}

// patch for 0x4D79AE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexPlayHandSignalAnim___CTaskComplexPlayHandSignalAnim_18CCAC_arm = 0;	// j__ZN10CStreaming11RemoveModelEi
	uintptr_t Address_GTA_SA_2_00_CTaskComplexPlayHandSignalAnim___CTaskComplexPlayHandSignalAnim_4D79B8_thumb = 0;	// loc_4D79B8
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexPlayHandSignalAnim___CTaskComplexPlayHandSignalAnim_4D79AE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexPlayHandSignalAnim___CTaskComplexPlayHandSignalAnim_4D79B8_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming11RemoveModelEi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexPlayHandSignalAnim___CTaskComplexPlayHandSignalAnim_18CCAC_arm)
		);
}

// patch for 0x4D7D0E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexPlayHandSignalAnim__ControlSubTask_4D7D18 = 0;
	uintptr_t Address_GTA_SA_2_00_CTaskComplexPlayHandSignalAnim__ControlSubTask_4D7D1A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexPlayHandSignalAnim__ControlSubTask_4D7D0E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R1, R0\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CTaskComplexPlayHandSignalAnim__ControlSubTask_4D7D18)
		"ADD R3, R1, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexPlayHandSignalAnim__ControlSubTask_4D7D1A_thumb)
		);
}

// patch for 0x4D9260
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskSimpleFight__GetAvailableComboSet_4D9268_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskSimpleFight__GetAvailableComboSet_4D9260()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimpleFight__GetAvailableComboSet_4D9268_thumb)
		);
}

// patch for 0x4E460A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskSimpleGangDriveBy__ManageAnim_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CTaskSimpleGangDriveBy__ManageAnim_4E4616_thumb = 0;	// loc_4E4616
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskSimpleGangDriveBy__ManageAnim_4E460A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimpleGangDriveBy__ManageAnim_4E4616_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimpleGangDriveBy__ManageAnim_192964_arm)
		);
}

// patch for 0x4ECA68
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexSitDownThenIdleThenStandUp__ControlSubTask_4ECA70_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexSitDownThenIdleThenStandUp__ControlSubTask_4ECA68()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexSitDownThenIdleThenStandUp__ControlSubTask_4ECA70_thumb)
		);
}

// patch for 0x4ED982
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexSunbathe__CreateFirstSubTask_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CTaskComplexSunbathe__CreateFirstSubTask_4ED98E_thumb = 0;	// loc_4ED98E
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexSunbathe__CreateFirstSubTask_4ED982()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexSunbathe__CreateFirstSubTask_4ED98E_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexSunbathe__CreateFirstSubTask_192964_arm)
		);
}

// patch for 0x4ED996
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexSunbathe__CreateFirstSubTask_4ED9A2_thumb = 0;	// loc_4ED9A2
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexSunbathe__CreateFirstSubTask_4ED996()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexSunbathe__CreateFirstSubTask_4ED9A2_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexSunbathe__CreateFirstSubTask_192964_arm)
		);
}

// patch for 0x4EDAF4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexSunbathe__ControlSubTask_4EDAFC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexSunbathe__ControlSubTask_4EDAF4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexSunbathe__ControlSubTask_4EDAFC_thumb)
		);
}

// patch for 0x4EDB6E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexSunbathe__ControlSubTask_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CTaskComplexSunbathe__ControlSubTask_4EDB7A_thumb = 0;	// loc_4EDB7A
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexSunbathe__ControlSubTask_4EDB6E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexSunbathe__ControlSubTask_4EDB7A_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexSunbathe__ControlSubTask_192964_arm)
		);
}

// patch for 0x5091DE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarEnterExit__SetAnimOffsetForEnterOrExitVehicle_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CCarEnterExit__SetAnimOffsetForEnterOrExitVehicle_5091EA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarEnterExit__SetAnimOffsetForEnterOrExitVehicle_5091DE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, FILE_TYPE_IFP_BASE_ID)
		"ADDS R0, R5, R6\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarEnterExit__SetAnimOffsetForEnterOrExitVehicle_5091EA_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarEnterExit__SetAnimOffsetForEnterOrExitVehicle_192964_arm)
		);
}

// patch for 0x5155B6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexGangLeader__ControlSubTask_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CTaskComplexGangLeader__ControlSubTask_5155C2_thumb = 0;	// loc_5155C2
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexGangLeader__ControlSubTask_5155B6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexGangLeader__ControlSubTask_5155C2_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexGangLeader__ControlSubTask_192964_arm)
		);
}

// patch for 0x516FF6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexGangFollower__ControlSubTask_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CTaskComplexGangFollower__ControlSubTask_517002_thumb = 0;	// loc_517002
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexGangFollower__ControlSubTask_516FF6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexGangFollower__ControlSubTask_517002_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexGangFollower__ControlSubTask_192964_arm)
		);
}

// patch for 0x518A6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskGangHassleVehicle__ControlSubTask_518A74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskGangHassleVehicle__ControlSubTask_518A6C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskGangHassleVehicle__ControlSubTask_518A74_thumb)
		);
}

// patch for 0x5196A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskGangHasslePed__ControlSubTask_5196B0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskGangHasslePed__ControlSubTask_5196A8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskGangHasslePed__ControlSubTask_5196B0_thumb)
		);
}

// patch for 0x519CA2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexStareAtPed__ControlSubTask_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CTaskComplexStareAtPed__ControlSubTask_519CAE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexStareAtPed__ControlSubTask_519CA2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexStareAtPed__ControlSubTask_519CAE_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexStareAtPed__ControlSubTask_192964_arm)
		);
}

// patch for 0x51A1FA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexSignalAtPed__ControlSubTask_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CTaskComplexSignalAtPed__ControlSubTask_51A206_thumb = 0;	// loc_51A206
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexSignalAtPed__ControlSubTask_51A1FA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexSignalAtPed__ControlSubTask_51A206_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexSignalAtPed__ControlSubTask_192964_arm)
		);
}

// patch for 0x51A8DE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskGoToVehicleAndLean__ControlSubTask_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CTaskGoToVehicleAndLean__ControlSubTask_51A8EA_thumb = 0;	// loc_51A8EA
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskGoToVehicleAndLean__ControlSubTask_51A8DE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskGoToVehicleAndLean__ControlSubTask_51A8EA_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskGoToVehicleAndLean__ControlSubTask_192964_arm)
		);
}

// patch for 0x51B382
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexGangJoinRespond__ControlSubTask_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CTaskComplexGangJoinRespond__ControlSubTask_51B38E_thumb = 0;	// loc_51B38E
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexGangJoinRespond__ControlSubTask_51B382()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexGangJoinRespond__ControlSubTask_51B38E_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexGangJoinRespond__ControlSubTask_192964_arm)
		);
}

// patch for 0x534AE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexPartner__StreamRequiredAnims_534AF0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexPartner__StreamRequiredAnims_534AE8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexPartner__StreamRequiredAnims_534AF0_thumb)
		);
}

// patch for 0x534CA6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexPartnerDeal__StreamRequiredAnims_534CB2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexPartnerDeal__StreamRequiredAnims_534CA6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"POP {R4,R5,R7,LR}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexPartnerDeal__StreamRequiredAnims_534CB2_thumb)
		);
}

// patch for 0x534EC6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexPartnerGreet__StreamRequiredAnims_534ED2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexPartnerGreet__StreamRequiredAnims_534EC6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"POP {R4,R5,R7,LR}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexPartnerGreet__StreamRequiredAnims_534ED2_thumb)
		);
}

// patch for 0x538D12
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskSimplePlayerOnFoot__PlayIdleAnimations_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CTaskSimplePlayerOnFoot__PlayIdleAnimations_538D1E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskSimplePlayerOnFoot__PlayIdleAnimations_538D12()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_BASE_ID)
		"MOVS R1, #2\n"
		"ADD R0, R6\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimplePlayerOnFoot__PlayIdleAnimations_538D1E_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimplePlayerOnFoot__PlayIdleAnimations_192964_arm)
		);
}

// patch for 0x538E4E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskSimplePlayerOnFoot__PlayIdleAnimations_19BC1C_arm = 0;	// j__ZN10CStreaming19SetModelIsDeletableEi
	uintptr_t Address_GTA_SA_2_00_CTaskSimplePlayerOnFoot__PlayIdleAnimations_538E58_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskSimplePlayerOnFoot__PlayIdleAnimations_538E4E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R6\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimplePlayerOnFoot__PlayIdleAnimations_538E58_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming19SetModelIsDeletableEi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimplePlayerOnFoot__PlayIdleAnimations_19BC1C_arm)
		);
}

// patch for 0x53B47E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskSimpleSwim__ProcessSwimAnims_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CTaskSimpleSwim__ProcessSwimAnims_53B48A_thumb = 0;	// loc_53B48A
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskSimpleSwim__ProcessSwimAnims_53B47E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimpleSwim__ProcessSwimAnims_53B48A_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimpleSwim__ProcessSwimAnims_192964_arm)
		);
}

// patch for 0x541E84
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskSimpleHoldEntity__StartAnim_541E8C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskSimpleHoldEntity__StartAnim_541E84()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimpleHoldEntity__StartAnim_541E8C_thumb)
		);
}

// patch for 0x542BEE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexGoPickUpEntity__ControlSubTask_192964_arm = 0;	// j__ZN10CStreaming12RequestModelEii
	uintptr_t Address_GTA_SA_2_00_CTaskComplexGoPickUpEntity__ControlSubTask_542BFA_thumb = 0;	// loc_542BFA
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexGoPickUpEntity__ControlSubTask_542BEE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, FILE_TYPE_IFP_BASE_ID)
		"ADD R0, R1\n"
		"MOVS R1, #8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexGoPickUpEntity__ControlSubTask_542BFA_thumb)

		// Branches
		"1:\n"	// j__ZN10CStreaming12RequestModelEii
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexGoPickUpEntity__ControlSubTask_192964_arm)
		);
}


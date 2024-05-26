// Compilation time: 0 seconds 454 ms

// patch for 0x427B34
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CAnimManager__Shutdown_427B38_arm64 = 0;	// loc_427B38
}

static NAKED void patch_GTA_SA_2_11_32_CAnimManager__Shutdown_427B34()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W20, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CAnimManager__Shutdown_427B38_arm64)
		);
}

// patch for 0x427B44
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CAnimManager__Shutdown_427B48_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CAnimManager__Shutdown_427B44()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W19, FILE_TYPE_IFP_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CAnimManager__Shutdown_427B48_arm64)
		);
}

// patch for 0x45F534
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__Initialise_45F538_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__Initialise_45F534()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W0, FILE_TYPE_IPL_COUNT_multiplied_by_sizeof_IplDef)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__Initialise_45F538_arm64)
		);
}

// patch for 0x45F768
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__Shutdown_45F770_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__Shutdown_45F768()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_IPL_BASE_ID_PLUS_ONE_then_multiplied_by_sizeof_CStreamingInfo_plus_ucFlags)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__Shutdown_45F770_arm64)
		);
}

// patch for 0x45F77C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__Shutdown_45F780_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__Shutdown_45F77C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W23, FILE_TYPE_IPL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__Shutdown_45F780_arm64)
		);
}

// patch for 0x45F8F8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__RemoveAllIpls_45F900_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__RemoveAllIpls_45F8F8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_IPL_BASE_ID_PLUS_ONE_then_multiplied_by_sizeof_CStreamingInfo_plus_ucFlags)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__RemoveAllIpls_45F900_arm64)
		);
}

// patch for 0x45F90C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__RemoveAllIpls_45F910_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__RemoveAllIpls_45F90C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W23, FILE_TYPE_IPL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__RemoveAllIpls_45F910_arm64)
		);
}

// patch for 0x460D98
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__SetupRelatedIpls_460D9C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__SetupRelatedIpls_460D98()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W28, FILE_TYPE_IPL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__SetupRelatedIpls_460D9C_arm64)
		);
}

// patch for 0x460F30
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__RemoveRelatedIpls_460F34_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__RemoveRelatedIpls_460F30()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W23, FILE_TYPE_IPL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__RemoveRelatedIpls_460F34_arm64)
		);
}

// patch for 0x4614A4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__LoadIpls_4614A8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__LoadIpls_4614A4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W24, FILE_TYPE_IPL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__LoadIpls_4614A8_arm64)
		);
}

// patch for 0x461624
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__EnsureIplsAreInMemory_461628_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__EnsureIplsAreInMemory_461624()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W28, FILE_TYPE_IPL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__EnsureIplsAreInMemory_461628_arm64)
		);
}

// patch for 0x461768
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__RequestIpls_46176C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__RequestIpls_461768()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W25, FILE_TYPE_IPL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__RequestIpls_46176C_arm64)
		);
}

// patch for 0x46186C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__HaveIplsLoaded_461870_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__HaveIplsLoaded_46186C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X8, FILE_TYPE_IPL_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__HaveIplsLoaded_461870_arm64)
		);
}

// patch for 0x461920
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__HaveIplsLoaded_461924_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__HaveIplsLoaded_461920()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IPL_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__HaveIplsLoaded_461924_arm64)
		);
}

// patch for 0x461948
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__HaveIplsLoaded_46194C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__HaveIplsLoaded_461948()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X8, FILE_TYPE_IPL_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__HaveIplsLoaded_46194C_arm64)
		);
}

// patch for 0x4619B8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__LoadAllRemainingIpls_4619BC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__LoadAllRemainingIpls_4619B8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W25, FILE_TYPE_IPL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__LoadAllRemainingIpls_4619BC_arm64)
		);
}

// patch for 0x461AF0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__RequestIplAndIgnore_461AF4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__RequestIplAndIgnore_461AF0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IPL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__RequestIplAndIgnore_461AF4_arm64)
		);
}

// patch for 0x461B50
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CIplStore__RemoveIplAndIgnore_461B54_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CIplStore__RemoveIplAndIgnore_461B50()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IPL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CIplStore__RemoveIplAndIgnore_461B54_arm64)
		);
}

// patch for 0x462A28
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ReInit_462A30_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ReInit_462A28()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W25, FILE_TYPE_DFF_LAST_ID)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W26, FILE_TYPE_TXD_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ReInit_462A30_arm64)
		);
}

// patch for 0x462A38
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ReInit_462A3C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ReInit_462A38()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_COUNT_OF_IDS)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ReInit_462A3C_arm64)
		);
}

// patch for 0x462B08
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ReInit_462B0C_arm64 = 0;	// loc_462B0C
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ReInit_462B08()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W20, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ReInit_462B0C_arm64)
		);
}

// patch for 0x463174
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__SetMissionDoesntRequireModel_46317C_arm64 = 0;	// loc_46317C
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__SetMissionDoesntRequireModel_463174()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W26, FILE_TYPE_DFF_LAST_ID)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W28, FILE_TYPE_TXD_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__SetMissionDoesntRequireModel_46317C_arm64)
		);
}

// patch for 0x46327C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463280_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_46327C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463280_arm64)
		);
}

// patch for 0x463430
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463434_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_463430()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_TXD_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463434_arm64)
		);
}

// patch for 0x46343C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463440_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_46343C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_TXD_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463440_arm64)
		);
}

// patch for 0x46344C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463450_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_46344C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_COL_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463450_arm64)
		);
}

// patch for 0x463458
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_46345C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_463458()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_COL_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_46345C_arm64)
		);
}

// patch for 0x463468
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_46346C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_463468()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IPL_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_46346C_arm64)
		);
}

// patch for 0x463474
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463478_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_463474()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IPL_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463478_arm64)
		);
}

// patch for 0x463498
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_46349C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_463498()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_DAT_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_46349C_arm64)
		);
}

// patch for 0x4634A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_4634AC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_4634A8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_4634AC_arm64)
		);
}

// patch for 0x4634B4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_4634B8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_4634B4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_4634B8_arm64)
		);
}

// patch for 0x4634C4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_4634C8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_4634C4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_4634C8_arm64)
		);
}

// patch for 0x4634D8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_4634DC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_4634D8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_SCM_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_4634DC_arm64)
		);
}

// patch for 0x46360C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463610_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_46360C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463610_arm64)
		);
}

// patch for 0x463620
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463624_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_463620()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_TXD_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463624_arm64)
		);
}

// patch for 0x46362C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463630_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_46362C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_TXD_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463630_arm64)
		);
}

// patch for 0x46363C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463640_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_46363C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_COL_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463640_arm64)
		);
}

// patch for 0x463648
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_46364C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_463648()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_COL_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_46364C_arm64)
		);
}

// patch for 0x463658
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_46365C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_463658()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IPL_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_46365C_arm64)
		);
}

// patch for 0x463664
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463668_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_463664()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IPL_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463668_arm64)
		);
}

// patch for 0x463674
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463678_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_463674()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463678_arm64)
		);
}

// patch for 0x46367C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463680_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_46367C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W0, FILE_TYPE_IFP_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463680_arm64)
		);
}

// patch for 0x46368C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463690_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_46368C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_463690_arm64)
		);
}

// patch for 0x4636A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveModel_4636A4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveModel_4636A0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_SCM_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveModel_4636A4_arm64)
		);
}

// patch for 0x465780
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ProcessLoadingChannel_465784_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ProcessLoadingChannel_465780()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ProcessLoadingChannel_465784_arm64)
		);
}

// patch for 0x465818
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ProcessLoadingChannel_46581C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ProcessLoadingChannel_465818()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IPL_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ProcessLoadingChannel_46581C_arm64)
		);
}

// patch for 0x465D94
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RequestModel_465D98_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RequestModel_465D94()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W12, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RequestModel_465D98_arm64)
		);
}

// patch for 0x465E70
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RequestModel_465E74_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RequestModel_465E70()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_TXD_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RequestModel_465E74_arm64)
		);
}

// patch for 0x465E8C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RequestModel_465E90_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RequestModel_465E8C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RequestModel_465E90_arm64)
		);
}

// patch for 0x465EB8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RequestModel_465EBC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RequestModel_465EB8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RequestModel_465EBC_arm64)
		);
}

// patch for 0x466480
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466484_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466480()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466484_arm64)
		);
}

// patch for 0x4665CC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4665D0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4665CC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_COL_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4665D0_arm64)
		);
}

// patch for 0x4665D4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4665D8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4665D4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W0, FILE_TYPE_COL_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4665D8_arm64)
		);
}

// patch for 0x4665F0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4665F4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4665F0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IPL_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4665F4_arm64)
		);
}

// patch for 0x4665F8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4665FC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4665F8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W0, FILE_TYPE_IPL_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4665FC_arm64)
		);
}

// patch for 0x4666A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4666A4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4666A0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_DAT_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4666A4_arm64)
		);
}

// patch for 0x4666A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4666AC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4666A8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W2, FILE_TYPE_DAT_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4666AC_arm64)
		);
}

// patch for 0x46680C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466810_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_46680C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466810_arm64)
		);
}

// patch for 0x466814
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466818_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466814()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W22, FILE_TYPE_IFP_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466818_arm64)
		);
}

// patch for 0x46685C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466860_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_46685C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W1, FILE_TYPE_RRR_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466860_arm64)
		);
}

// patch for 0x466874
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466878_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466874()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466878_arm64)
		);
}

// patch for 0x466888
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_46688C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_466888()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_SCM_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_46688C_arm64)
		);
}

// patch for 0x4668A4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4668A8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4668A4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4668A8_arm64)
		);
}

// patch for 0x4668AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4668B0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4668AC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_RRR_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4668B0_arm64)
		);
}

// patch for 0x4668B8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4668BC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4668B8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W22, FILE_TYPE_IFP_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4668BC_arm64)
		);
}

// patch for 0x4669B0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4669B4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4669B0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_COL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ConvertBufferToObject_4669B4_arm64)
		);
}

// patch for 0x466B6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__AreAnimsUsedByRequestedModels_466B70_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__AreAnimsUsedByRequestedModels_466B6C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W26, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__AreAnimsUsedByRequestedModels_466B70_arm64)
		);
}

// patch for 0x466BDC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__AreAnimsUsedByRequestedModels_466BE0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__AreAnimsUsedByRequestedModels_466BDC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W23, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__AreAnimsUsedByRequestedModels_466BE0_arm64)
		);
}

// patch for 0x466D04
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__FinishLoadingLargeFile_466D08_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__FinishLoadingLargeFile_466D04()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__FinishLoadingLargeFile_466D08_arm64)
		);
}

// patch for 0x466D88
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__FinishLoadingLargeFile_466D8C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__FinishLoadingLargeFile_466D88()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__FinishLoadingLargeFile_466D8C_arm64)
		);
}

// patch for 0x466DA8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__FinishLoadingLargeFile_466DAC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__FinishLoadingLargeFile_466DA8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_TXD_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__FinishLoadingLargeFile_466DAC_arm64)
		);
}

// patch for 0x466DB4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__FinishLoadingLargeFile_466DB8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__FinishLoadingLargeFile_466DB4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_TXD_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__FinishLoadingLargeFile_466DB8_arm64)
		);
}

// patch for 0x467208
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_46720C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_467208()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_46720C_arm64)
		);
}

// patch for 0x467280
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_467284_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_467280()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_467284_arm64)
		);
}

// patch for 0x46728C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_467290_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_46728C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_TXD_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_467290_arm64)
		);
}

// patch for 0x4672A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_4672A4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_4672A0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_TXD_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_4672A4_arm64)
		);
}

// patch for 0x4672C8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_4672CC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_4672C8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_4672CC_arm64)
		);
}

// patch for 0x4672D0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_4672D4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_4672D0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_4672D4_arm64)
		);
}

// patch for 0x467308
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_46730C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_467308()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_TXD_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__GetNextFileOnCd_46730C_arm64)
		);
}

// patch for 0x467740
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467744_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RequestModelStream_467740()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W21, FILE_TYPE_IFP_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467744_arm64)
		);
}

// patch for 0x467768
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_46776C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RequestModelStream_467768()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W0, FILE_TYPE_IFP_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_46776C_arm64)
		);
}

// patch for 0x467850
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467854_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RequestModelStream_467850()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W13, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467854_arm64)
		);
}

// patch for 0x467914
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467918_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RequestModelStream_467914()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W13, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467918_arm64)
		);
}

// patch for 0x46791C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467920_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RequestModelStream_46791C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467920_arm64)
		);
}

// patch for 0x46793C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467940_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RequestModelStream_46793C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467940_arm64)
		);
}

// patch for 0x467944
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467948_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RequestModelStream_467944()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467948_arm64)
		);
}

// patch for 0x467A00
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467A04_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RequestModelStream_467A00()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W13, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RequestModelStream_467A04_arm64)
		);
}

// patch for 0x4684D8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__LoadScene_4684DC_arm64 = 0;	// loc_4684DC
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__LoadScene_4684D8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_COUNT_OF_IDS)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__LoadScene_4684DC_arm64)
		);
}

// patch for 0x468944
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__ClearFlagForAll_468948_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__ClearFlagForAll_468944()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W10, FILE_TYPE_COUNT_OF_IDS)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__ClearFlagForAll_468948_arm64)
		);
}

// patch for 0x468FC8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_468FCC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_468FC8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W26, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_468FCC_arm64)
		);
}

// patch for 0x46902C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_469030_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_46902C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_469030_arm64)
		);
}

// patch for 0x469034
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_469038_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_469034()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W21, FILE_TYPE_IFP_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_469038_arm64)
		);
}

// patch for 0x469058
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_46905C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_469058()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_46905C_arm64)
		);
}

// patch for 0x46906C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_469070_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_46906C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_SCM_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__RemoveLeastUsedModel_469070_arm64)
		);
}

// patch for 0x46C690
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__SetMissionDoesntRequireSpecialChar_46C698_arm64 = 0;	// loc_46C698
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__SetMissionDoesntRequireSpecialChar_46C690()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W26, FILE_TYPE_DFF_LAST_ID)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W28, FILE_TYPE_TXD_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__SetMissionDoesntRequireSpecialChar_46C698_arm64)
		);
}

// patch for 0x476D4C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__Initialise_476D50_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__Initialise_476D4C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W0, FILE_TYPE_COL_COUNT_multiplied_by_sizeof_CCollisionFile)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__Initialise_476D50_arm64)
		);
}

// patch for 0x476D58
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__Initialise_476D5C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__Initialise_476D58()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W0, FILE_TYPE_COL_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__Initialise_476D5C_arm64)
		);
}

// patch for 0x476DC0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__Initialise_476DC4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__Initialise_476DC0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X8, FILE_TYPE_COL_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__Initialise_476DC4_arm64)
		);
}

// patch for 0x477104
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__Shutdown_477108_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__Shutdown_477104()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X19, FILE_TYPE_COL_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__Shutdown_477108_arm64)
		);
}

// patch for 0x477A80
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__LoadCollision_477A84_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__LoadCollision_477A80()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W24, FILE_TYPE_COL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__LoadCollision_477A84_arm64)
		);
}

// patch for 0x477A90
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__LoadCollision_477A94_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__LoadCollision_477A90()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X22, FILE_TYPE_COL_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__LoadCollision_477A94_arm64)
		);
}

// patch for 0x477CC4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__EnsureCollisionIsInMemory_477CCC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__EnsureCollisionIsInMemory_477CC4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_COL_BASE_ID_PLUS_ONE_then_multiplied_by_sizeof_CStreamingInfo_plus_uiLoadFlag)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__EnsureCollisionIsInMemory_477CCC_arm64)
		);
}

// patch for 0x477CDC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__EnsureCollisionIsInMemory_477CE0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__EnsureCollisionIsInMemory_477CDC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W10, FILE_TYPE_COL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__EnsureCollisionIsInMemory_477CE0_arm64)
		);
}

// patch for 0x477D00
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__EnsureCollisionIsInMemory_477D04_arm64 = 0;	// loc_477D04
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__EnsureCollisionIsInMemory_477D00()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W10, FILE_TYPE_COL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__EnsureCollisionIsInMemory_477D04_arm64)
		);
}

// patch for 0x477D10
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__EnsureCollisionIsInMemory_477D14_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__EnsureCollisionIsInMemory_477D10()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X24, FILE_TYPE_COL_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__EnsureCollisionIsInMemory_477D14_arm64)
		);
}

// patch for 0x477EA8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__RequestCollision_477EAC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__RequestCollision_477EA8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W26, FILE_TYPE_COL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__RequestCollision_477EAC_arm64)
		);
}

// patch for 0x477EB8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__RequestCollision_477EBC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__RequestCollision_477EB8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X21, FILE_TYPE_COL_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__RequestCollision_477EBC_arm64)
		);
}

// patch for 0x478048
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__HasCollisionLoaded_47804C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__HasCollisionLoaded_478048()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X10, FILE_TYPE_COL_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__HasCollisionLoaded_47804C_arm64)
		);
}

// patch for 0x478054
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__HasCollisionLoaded_478058_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__HasCollisionLoaded_478054()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X10, FILE_TYPE_COL_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__HasCollisionLoaded_478058_arm64)
		);
}

// patch for 0x4780F8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__HasCollisionLoaded_4780FC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__HasCollisionLoaded_4780F8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W10, FILE_TYPE_COL_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__HasCollisionLoaded_4780FC_arm64)
		);
}

// patch for 0x478130
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__HasCollisionLoaded_478134_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__HasCollisionLoaded_478130()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X10, FILE_TYPE_COL_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__HasCollisionLoaded_478134_arm64)
		);
}

// patch for 0x478188
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__RemoveAllCollision_478190_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__RemoveAllCollision_478188()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_COL_BASE_ID_PLUS_ONE_then_multiplied_by_sizeof_CStreamingInfo_plus_ucFlags)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__RemoveAllCollision_478190_arm64)
		);
}

// patch for 0x47819C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__RemoveAllCollision_4781A0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__RemoveAllCollision_47819C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W23, FILE_TYPE_COL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__RemoveAllCollision_4781A0_arm64)
		);
}

// patch for 0x4781AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__RemoveAllCollision_4781B0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__RemoveAllCollision_4781AC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X20, FILE_TYPE_COL_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__RemoveAllCollision_4781B0_arm64)
		);
}

// patch for 0x478240
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__LoadAllBoundingBoxes_478244_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__LoadAllBoundingBoxes_478240()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W23, FILE_TYPE_COL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__LoadAllBoundingBoxes_478244_arm64)
		);
}

// patch for 0x47824C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__LoadAllBoundingBoxes_478250_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__LoadAllBoundingBoxes_47824C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X21, FILE_TYPE_COL_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__LoadAllBoundingBoxes_478250_arm64)
		);
}

// patch for 0x4782D0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__LoadAllCollision_4782D4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__LoadAllCollision_4782D0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W23, FILE_TYPE_COL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__LoadAllCollision_4782D4_arm64)
		);
}

// patch for 0x4782DC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__LoadAllCollision_4782E0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__LoadAllCollision_4782DC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X21, FILE_TYPE_COL_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__LoadAllCollision_4782E0_arm64)
		);
}

// patch for 0x4783C8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColStore__BoundingBoxesPostProcess_4783CC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColStore__BoundingBoxesPostProcess_4783C8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X20, FILE_TYPE_COL_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColStore__BoundingBoxesPostProcess_4783CC_arm64)
		);
}

// patch for 0x4B4F80
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CPathFind__Shutdown_4B4F84_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CPathFind__Shutdown_4B4F80()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W28, FILE_TYPE_DAT_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CPathFind__Shutdown_4B4F84_arm64)
		);
}

// patch for 0x4B5650
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CPathFind__UpdateStreaming_4B5654_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CPathFind__UpdateStreaming_4B5650()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W21, FILE_TYPE_DAT_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CPathFind__UpdateStreaming_4B5654_arm64)
		);
}

// patch for 0x4B5ACC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CPathFind__LoadSceneForPathNodes_4B5AD0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CPathFind__LoadSceneForPathNodes_4B5ACC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W28, FILE_TYPE_DAT_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CPathFind__LoadSceneForPathNodes_4B5AD0_arm64)
		);
}

// patch for 0x4BEE0C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__InitAtStartOfGame_4BEE10_arm64 = 0;	// loc_4BEE10
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__InitAtStartOfGame_4BEE0C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_RRR_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__InitAtStartOfGame_4BEE10_arm64)
		);
}

// patch for 0x4BEE78
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__Init_4BEE7C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__Init_4BEE78()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_RRR_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__Init_4BEE7C_arm64)
		);
}

// patch for 0x4BEEB0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__ShutDown_4BEEB4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__ShutDown_4BEEB0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W21, FILE_TYPE_RRR_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__ShutDown_4BEEB4_arm64)
		);
}

// patch for 0x4BEEC0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__ShutDown_4BEEC4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__ShutDown_4BEEC0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X19, FILE_TYPE_RRR_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__ShutDown_4BEEC4_arm64)
		);
}

// patch for 0x4BF0A4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__StartPlaybackRecordedCar_4BF0A8_arm64 = 0;	// loc_4BF0A8
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__StartPlaybackRecordedCar_4BF0A4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W0, FILE_TYPE_RRR_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__StartPlaybackRecordedCar_4BF0A8_arm64)
		);
}

// patch for 0x4BF0C4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__StartPlaybackRecordedCar_4BF0C8_arm64 = 0;	// loc_4BF0C8
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__StartPlaybackRecordedCar_4BF0C4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W0, FILE_TYPE_RRR_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__StartPlaybackRecordedCar_4BF0C8_arm64)
		);
}

// patch for 0x4BF2F8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__RequestRecordingFile_4BF2FC_arm64 = 0;	// loc_4BF2FC
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__RequestRecordingFile_4BF2F8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W0, FILE_TYPE_RRR_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__RequestRecordingFile_4BF2FC_arm64)
		);
}

// patch for 0x4BF318
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__RequestRecordingFile_4BF31C_arm64 = 0;	// loc_4BF31C
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__RequestRecordingFile_4BF318()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W0, FILE_TYPE_RRR_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__RequestRecordingFile_4BF31C_arm64)
		);
}

// patch for 0x4BF660
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__StopPlaybackRecordedCar_4BF664_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__StopPlaybackRecordedCar_4BF660()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_RRR_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__StopPlaybackRecordedCar_4BF664_arm64)
		);
}

// patch for 0x4BF730
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__StopPlaybackWithIndex_4BF734_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__StopPlaybackWithIndex_4BF730()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_RRR_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__StopPlaybackWithIndex_4BF734_arm64)
		);
}

// patch for 0x4C02F4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__SkipToEndAndStopPlaybackRecordedCar_4C02F8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__SkipToEndAndStopPlaybackRecordedCar_4C02F4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_RRR_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__SkipToEndAndStopPlaybackRecordedCar_4C02F8_arm64)
		);
}

// patch for 0x4C05D0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__SaveOrRetrieveDataForThisFrame_4C05D4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__SaveOrRetrieveDataForThisFrame_4C05D0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_RRR_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__SaveOrRetrieveDataForThisFrame_4C05D4_arm64)
		);
}

// patch for 0x4C1008
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__RemoveRecordingFile_4C100C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__RemoveRecordingFile_4C1008()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W22, FILE_TYPE_RRR_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__RemoveRecordingFile_4C100C_arm64)
		);
}

// patch for 0x4C1014
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__RemoveRecordingFile_4C1018_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__RemoveRecordingFile_4C1014()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X20, FILE_TYPE_RRR_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__RemoveRecordingFile_4C1018_arm64)
		);
}

// patch for 0x4C11E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__RemoveAllRecordingsThatArentUsed_4C11E4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__RemoveAllRecordingsThatArentUsed_4C11E0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W21, FILE_TYPE_RRR_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__RemoveAllRecordingsThatArentUsed_4C11E4_arm64)
		);
}

// patch for 0x4C11F0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CVehicleRecording__RemoveAllRecordingsThatArentUsed_4C11F4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CVehicleRecording__RemoveAllRecordingsThatArentUsed_4C11F0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(X19, FILE_TYPE_RRR_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CVehicleRecording__RemoveAllRecordingsThatArentUsed_4C11F4_arm64)
		);
}

// patch for 0x4DD244
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CRunningScript__ProcessCommands1200To1299_4DD248_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CRunningScript__ProcessCommands1200To1299_4DD244()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CRunningScript__ProcessCommands1200To1299_4DD248_arm64)
		);
}

// patch for 0x4DD4A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CRunningScript__ProcessCommands1200To1299_4DD4A4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CRunningScript__ProcessCommands1200To1299_4DD4A0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CRunningScript__ProcessCommands1200To1299_4DD4A4_arm64)
		);
}

// patch for 0x4EE56C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CScriptsForBrains__StartOrRequestNewStreamedScriptBrain_4EE570_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CScriptsForBrains__StartOrRequestNewStreamedScriptBrain_4EE56C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W10, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CScriptsForBrains__StartOrRequestNewStreamedScriptBrain_4EE570_arm64)
		);
}

// patch for 0x4EEA9C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CScriptsForBrains__RequestAttractorScriptBrainWithThisName_4EEAA0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CScriptsForBrains__RequestAttractorScriptBrainWithThisName_4EEA9C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CScriptsForBrains__RequestAttractorScriptBrainWithThisName_4EEAA0_arm64)
		);
}

// patch for 0x4EEBE4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CScriptsForBrains__HasAttractorScriptBrainWithThisNameLoaded_4EEBEC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CScriptsForBrains__HasAttractorScriptBrainWithThisNameLoaded_4EEBE4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_SCM_BASE_ID_multiplied_by_sizeof_CStreamingInfo_plus_uiLoadFlag)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CScriptsForBrains__HasAttractorScriptBrainWithThisNameLoaded_4EEBEC_arm64)
		);
}

// patch for 0x4EEDAC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTheScripts__ProcessWaitingForScriptBrainArray_4EEDB0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTheScripts__ProcessWaitingForScriptBrainArray_4EEDAC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W24, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTheScripts__ProcessWaitingForScriptBrainArray_4EEDB0_arm64)
		);
}

// patch for 0x4F3BD4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreamedScripts__StartNewStreamedScript_4F3BD8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreamedScripts__StartNewStreamedScript_4F3BD4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreamedScripts__StartNewStreamedScript_4F3BD8_arm64)
		);
}

// patch for 0x4F3C2C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreamedScripts__StartNewStreamedScript_4F3C30_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreamedScripts__StartNewStreamedScript_4F3C2C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreamedScripts__StartNewStreamedScript_4F3C30_arm64)
		);
}

// patch for 0x4F3CD0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreamedScripts__GetStreamedScriptWithThisStartAddress_4F3CD4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreamedScripts__GetStreamedScriptWithThisStartAddress_4F3CD0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_SCM_COUNT_MINUS_ONE)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreamedScripts__GetStreamedScriptWithThisStartAddress_4F3CD4_arm64)
		);
}

// patch for 0x4F8BD0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CRunningScript__ProcessCommands2200To2299_4F8BD8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CRunningScript__ProcessCommands2200To2299_4F8BD0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_SCM_BASE_ID_multiplied_by_sizeof_CStreamingInfo_plus_uiLoadFlag)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CRunningScript__ProcessCommands2200To2299_4F8BD8_arm64)
		);
}

// patch for 0x4F90E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CRunningScript__ProcessCommands2200To2299_4F90E4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CRunningScript__ProcessCommands2200To2299_4F90E0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CRunningScript__ProcessCommands2200To2299_4F90E4_arm64)
		);
}

// patch for 0x4FAA9C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CRunningScript__ProcessCommands2300To2399_4FAAA0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CRunningScript__ProcessCommands2300To2399_4FAA9C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CRunningScript__ProcessCommands2300To2399_4FAAA0_arm64)
		);
}

// patch for 0x4FAAD8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CRunningScript__ProcessCommands2300To2399_4FAADC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CRunningScript__ProcessCommands2300To2399_4FAAD8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CRunningScript__ProcessCommands2300To2399_4FAADC_arm64)
		);
}

// patch for 0x503074
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CShopping__ShutdownForRestart_503078_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CShopping__ShutdownForRestart_503074()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CShopping__ShutdownForRestart_503078_arm64)
		);
}

// patch for 0x5030EC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CShopping__RemoveLoadedShop_5030F0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CShopping__RemoveLoadedShop_5030EC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CShopping__RemoveLoadedShop_5030F0_arm64)
		);
}

// patch for 0x5034E4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CShopping__LoadPrices_5034E8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CShopping__LoadPrices_5034E4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CShopping__LoadPrices_5034E8_arm64)
		);
}

// patch for 0x503864
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CShopping__LoadPrices_503868_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CShopping__LoadPrices_503864()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CShopping__LoadPrices_503868_arm64)
		);
}

// patch for 0x5038E4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CShopping__RemoveLoadedPrices_5038E8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CShopping__RemoveLoadedPrices_5038E4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CShopping__RemoveLoadedPrices_5038E8_arm64)
		);
}

// patch for 0x5D3360
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_InteriorGroup_c__ReferenceAnims_5D3364_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_InteriorGroup_c__ReferenceAnims_5D3360()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_InteriorGroup_c__ReferenceAnims_5D3364_arm64)
		);
}

// patch for 0x5DC6DC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTimeInfo__FindOtherTimeModel_5DC6E0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTimeInfo__FindOtherTimeModel_5DC6DC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W25, FILE_TYPE_TXD_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTimeInfo__FindOtherTimeModel_5DC6E0_arm64)
		);
}

// patch for 0x5DD9D4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CModelInfo__ReInit2dEffects_5DD9D8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CModelInfo__ReInit2dEffects_5DD9D4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W20, FILE_TYPE_TXD_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CModelInfo__ReInit2dEffects_5DD9D8_arm64)
		);
}

// patch for 0x5DDD84
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CModelInfo__GetModelInfo_5DDD88_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CModelInfo__GetModelInfo_5DDD84()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CModelInfo__GetModelInfo_5DDD88_arm64)
		);
}

// patch for 0x5DDE30
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CModelInfo__GetModelInfoFromHashKey_5DDE34_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CModelInfo__GetModelInfoFromHashKey_5DDE30()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W11, FILE_TYPE_TXD_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CModelInfo__GetModelInfoFromHashKey_5DDE34_arm64)
		);
}

// patch for 0x5DDE94
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CModelInfo__GetModelInfoUInt16_5DDE98_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CModelInfo__GetModelInfoUInt16_5DDE94()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CModelInfo__GetModelInfoUInt16_5DDE98_arm64)
		);
}

// patch for 0x5DE760
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CModelInfo__IsVehicleModelType_5DE764_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CModelInfo__IsVehicleModelType_5DE760()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_DFF_LAST_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CModelInfo__IsVehicleModelType_5DE764_arm64)
		);
}

// patch for 0x5E57C8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CObject___CObject_5E57CC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CObject___CObject_5E57C8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CObject___CObject_5E57CC_arm64)
		);
}

// patch for 0x5EB948
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CClothes__RequestMotionGroupAnims_5EB94C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CClothes__RequestMotionGroupAnims_5EB948()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CClothes__RequestMotionGroupAnims_5EB94C_arm64)
		);
}

// patch for 0x5EB984
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CClothes__RequestMotionGroupAnims_5EB988_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CClothes__RequestMotionGroupAnims_5EB984()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CClothes__RequestMotionGroupAnims_5EB988_arm64)
		);
}

// patch for 0x5EB9A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CClothes__RequestMotionGroupAnims_5EB9AC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CClothes__RequestMotionGroupAnims_5EB9A8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CClothes__RequestMotionGroupAnims_5EB9AC_arm64)
		);
}

// patch for 0x5FC1F4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CFileLoader__LoadLevel_5FC1F8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CFileLoader__LoadLevel_5FC1F4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W25, FILE_TYPE_TXD_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CFileLoader__LoadLevel_5FC1F8_arm64)
		);
}

// patch for 0x60150C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__Init2_601510_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__Init2_60150C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W21, FILE_TYPE_COUNT_OF_IDS)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__Init2_601510_arm64)
		);
}

// patch for 0x601688
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__Init2_60168C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__Init2_601688()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W24, FILE_TYPE_TXD_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__Init2_60168C_arm64)
		);
}

// patch for 0x601720
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__Init2_601724_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__Init2_601720()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W13, FILE_TYPE_TXD_COUNT)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__Init2_601724_arm64)
		);
}

// patch for 0x601D9C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601DA0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601D9C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_TXD_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601DA0_arm64)
		);
}

// patch for 0x601DC0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601DC4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601DC0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_COL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601DC4_arm64)
		);
}

// patch for 0x601E0C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E10_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E0C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IPL_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E10_arm64)
		);
}

// patch for 0x601E30
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E34_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E30()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_DAT_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E34_arm64)
		);
}

// patch for 0x601E44
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E48_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E44()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E48_arm64)
		);
}

// patch for 0x601E54
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E58_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E54()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_RRR_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E58_arm64)
		);
}

// patch for 0x601E6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E70_arm64 = 0;	// loc_601E70
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E6C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__LoadCdDirectory_601E70_arm64)
		);
}

// patch for 0x6028D4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColAccel__startCache_6028D8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColAccel__startCache_6028D4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W0, FILE_TYPE_IPL_COUNT_multiplied_by_sizeof_IplDef)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColAccel__startCache_6028D8_arm64)
		);
}

// patch for 0x602AEC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColAccel__startCache_602AF0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColAccel__startCache_602AEC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W2, FILE_TYPE_IPL_COUNT_multiplied_by_sizeof_IplDef)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColAccel__startCache_602AF0_arm64)
		);
}

// patch for 0x602CB4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CColAccel__endCache_602CB8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CColAccel__endCache_602CB4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W2, FILE_TYPE_IPL_COUNT_multiplied_by_sizeof_IplDef)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CColAccel__endCache_602CB8_arm64)
		);
}

// patch for 0x612BD4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__Save_612BD8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__Save_612BD4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W20, FILE_TYPE_COUNT_OF_IDS)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__Save_612BD8_arm64)
		);
}

// patch for 0x612C6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CStreaming__Load_612C70_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CStreaming__Load_612C6C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W21, FILE_TYPE_COUNT_OF_IDS)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CStreaming__Load_612C70_arm64)
		);
}

// patch for 0x617494
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CScriptResourceManager__Load_617498_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CScriptResourceManager__Load_617494()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W25, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CScriptResourceManager__Load_617498_arm64)
		);
}

// patch for 0x631490
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CPed___CPed_631494_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CPed___CPed_631490()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_SCM_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CPed___CPed_631494_arm64)
		);
}

// patch for 0x66392C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CPlayerPed__ProcessAnimGroups_663930_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CPlayerPed__ProcessAnimGroups_66392C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CPlayerPed__ProcessAnimGroups_663930_arm64)
		);
}

// patch for 0x6639E4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CPlayerPed__ProcessAnimGroups_6639E8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CPlayerPed__ProcessAnimGroups_6639E4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CPlayerPed__ProcessAnimGroups_6639E8_arm64)
		);
}

// patch for 0x6BA3E4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexPlayHandSignalAnim___CTaskComplexPlayHandSignalAnim_6BA3E8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexPlayHandSignalAnim___CTaskComplexPlayHandSignalAnim_6BA3E4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexPlayHandSignalAnim___CTaskComplexPlayHandSignalAnim_6BA3E8_arm64)
		);
}

// patch for 0x6BA45C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexPlayHandSignalAnim___CTaskComplexPlayHandSignalAnim_6BA460_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexPlayHandSignalAnim___CTaskComplexPlayHandSignalAnim_6BA45C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexPlayHandSignalAnim___CTaskComplexPlayHandSignalAnim_6BA460_arm64)
		);
}

// patch for 0x6BA8D8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexPlayHandSignalAnim__ControlSubTask_6BA8DC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexPlayHandSignalAnim__ControlSubTask_6BA8D8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexPlayHandSignalAnim__ControlSubTask_6BA8DC_arm64)
		);
}

// patch for 0x6BC1EC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskSimpleFight__GetAvailableComboSet_6BC1F0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskSimpleFight__GetAvailableComboSet_6BC1EC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskSimpleFight__GetAvailableComboSet_6BC1F0_arm64)
		);
}

// patch for 0x6CA2E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskSimpleGangDriveBy__ManageAnim_6CA2E4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskSimpleGangDriveBy__ManageAnim_6CA2E0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskSimpleGangDriveBy__ManageAnim_6CA2E4_arm64)
		);
}

// patch for 0x6D56A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexSitDownThenIdleThenStandUp__ControlSubTask_6D56AC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexSitDownThenIdleThenStandUp__ControlSubTask_6D56A8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexSitDownThenIdleThenStandUp__ControlSubTask_6D56AC_arm64)
		);
}

// patch for 0x6D6C74
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexSunbathe__CreateFirstSubTask_6D6C78_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexSunbathe__CreateFirstSubTask_6D6C74()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexSunbathe__CreateFirstSubTask_6D6C78_arm64)
		);
}

// patch for 0x6D6C94
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexSunbathe__CreateFirstSubTask_6D6C98_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexSunbathe__CreateFirstSubTask_6D6C94()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexSunbathe__CreateFirstSubTask_6D6C98_arm64)
		);
}

// patch for 0x6D6F04
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexSunbathe__ControlSubTask_6D6F08_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexSunbathe__ControlSubTask_6D6F04()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexSunbathe__ControlSubTask_6D6F08_arm64)
		);
}

// patch for 0x6D6F20
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexSunbathe__ControlSubTask_6D6F24_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexSunbathe__ControlSubTask_6D6F20()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexSunbathe__ControlSubTask_6D6F24_arm64)
		);
}

// patch for 0x6FEF2C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CCarEnterExit__SetAnimOffsetForEnterOrExitVehicle_6FEF30_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CCarEnterExit__SetAnimOffsetForEnterOrExitVehicle_6FEF2C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W22, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CCarEnterExit__SetAnimOffsetForEnterOrExitVehicle_6FEF30_arm64)
		);
}

// patch for 0x70FC30
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexGangLeader__ControlSubTask_70FC34_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexGangLeader__ControlSubTask_70FC30()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexGangLeader__ControlSubTask_70FC34_arm64)
		);
}

// patch for 0x71218C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexGangFollower__ControlSubTask_712190_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexGangFollower__ControlSubTask_71218C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexGangFollower__ControlSubTask_712190_arm64)
		);
}

// patch for 0x713F58
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskGangHassleVehicle__ControlSubTask_713F5C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskGangHassleVehicle__ControlSubTask_713F58()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskGangHassleVehicle__ControlSubTask_713F5C_arm64)
		);
}

// patch for 0x714F0C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskGangHasslePed__ControlSubTask_714F10_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskGangHasslePed__ControlSubTask_714F0C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskGangHasslePed__ControlSubTask_714F10_arm64)
		);
}

// patch for 0x715564
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexStareAtPed__ControlSubTask_715568_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexStareAtPed__ControlSubTask_715564()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexStareAtPed__ControlSubTask_715568_arm64)
		);
}

// patch for 0x715ED8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexSignalAtPed__ControlSubTask_715EDC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexSignalAtPed__ControlSubTask_715ED8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexSignalAtPed__ControlSubTask_715EDC_arm64)
		);
}

// patch for 0x716778
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskGoToVehicleAndLean__ControlSubTask_71677C_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskGoToVehicleAndLean__ControlSubTask_716778()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskGoToVehicleAndLean__ControlSubTask_71677C_arm64)
		);
}

// patch for 0x717620
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexGangJoinRespond__ControlSubTask_717624_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexGangJoinRespond__ControlSubTask_717620()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexGangJoinRespond__ControlSubTask_717624_arm64)
		);
}

// patch for 0x73A0CC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexPartner__StreamRequiredAnims_73A0D0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexPartner__StreamRequiredAnims_73A0CC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexPartner__StreamRequiredAnims_73A0D0_arm64)
		);
}

// patch for 0x73A2E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexPartnerDeal__StreamRequiredAnims_73A2E4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexPartnerDeal__StreamRequiredAnims_73A2E0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexPartnerDeal__StreamRequiredAnims_73A2E4_arm64)
		);
}

// patch for 0x73A5DC
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexPartnerGreet__StreamRequiredAnims_73A5E0_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexPartnerGreet__StreamRequiredAnims_73A5DC()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexPartnerGreet__StreamRequiredAnims_73A5E0_arm64)
		);
}

// patch for 0x73F644
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskSimplePlayerOnFoot__PlayIdleAnimations_73F648_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskSimplePlayerOnFoot__PlayIdleAnimations_73F644()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskSimplePlayerOnFoot__PlayIdleAnimations_73F648_arm64)
		);
}

// patch for 0x73F6E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskSimplePlayerOnFoot__PlayIdleAnimations_73F6E4_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskSimplePlayerOnFoot__PlayIdleAnimations_73F6E0()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskSimplePlayerOnFoot__PlayIdleAnimations_73F6E4_arm64)
		);
}

// patch for 0x7423C8
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskSimpleSwim__ProcessSwimAnims_7423CC_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskSimpleSwim__ProcessSwimAnims_7423C8()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskSimpleSwim__ProcessSwimAnims_7423CC_arm64)
		);
}

// patch for 0x74B20C
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskSimpleHoldEntity__StartAnim_74B210_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskSimpleHoldEntity__StartAnim_74B20C()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskSimpleHoldEntity__StartAnim_74B210_arm64)
		);
}

// patch for 0x74C3E4
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CTaskComplexGoPickUpEntity__ControlSubTask_74C3E8_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CTaskComplexGoPickUpEntity__ControlSubTask_74C3E4()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W8, FILE_TYPE_IFP_BASE_ID)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CTaskComplexGoPickUpEntity__ControlSubTask_74C3E8_arm64)
		);
}

// patch for 0x785724
extern "C"
{
	uintptr_t Address_GTA_SA_2_11_32_CPlane__IsAlreadyFlying_785728_arm64 = 0;
}

static NAKED void patch_GTA_SA_2_11_32_CPlane__IsAlreadyFlying_785724()
{
	__asm(
	RESTORE_TRAMPOLINE_REGISTER()
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(W9, FILE_TYPE_TXD_BASE_ID_NEGATED)

		SAVE_TRAMPOLINE_REGISTER()
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_11_32_CPlane__IsAlreadyFlying_785728_arm64)
		);
}


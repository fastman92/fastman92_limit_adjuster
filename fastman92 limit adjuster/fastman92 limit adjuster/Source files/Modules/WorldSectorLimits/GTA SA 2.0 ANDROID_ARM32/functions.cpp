// Compilation time: 40 seconds 78 ms

// patch for 0x1A6140
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_sub_1A6138_1A614A = 0;	// loc_1A614A
	uintptr_t Address_GTA_SA_2_00_sub_1A6138_1A6148_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_sub_1A6138_1A6140()
{
	__asm(
	".thumb\n"
		"LDR R0, =("/* _ZN6CWorld11ms_aSectorsE_ptr */"0x676734 - 0x1A614A)\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R4, TotalNumberOfWorldSectorsMultipliedBySizeOfCSector)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_sub_1A6138_1A614A)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_sub_1A6138_1A6148_thumb)
		);
}

// patch for 0x1A61A4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_sub_1A61A0_1A61AE = 0;	// loc_1A61AE
	uintptr_t Address_GTA_SA_2_00_sub_1A61A0_1A61AC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_sub_1A61A0_1A61A4()
{
	__asm(
	".thumb\n"
		"LDR R0, =("/* _ZN6CWorld15ms_aLodPtrListsE_ptr */"0x67738C - 0x1A61AE)\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R4, TotalNumberOfWorldLODsectorsMultipliedBySizeOfLODsector)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_sub_1A61A0_1A61AE)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_sub_1A61A0_1A61AC_thumb)
		);
}

// patch for 0x1A6234
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_sub_1A61C0_191C70_arm = 0;	// __aeabi_memclr4
	uintptr_t Address_GTA_SA_2_00_sub_1A61C0_1A623C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_sub_1A61C0_1A6234()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, TotalNumberOfWorldSectorsMultipliedBySizeOfCSector)
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_sub_1A61C0_1A623C_thumb)

		// Branches
		"1:\n"	// __aeabi_memclr4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_sub_1A61C0_191C70_arm)
		);
}

// patch for 0x2CDE2E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDE3E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDE2E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"VADD.F32 S6, S2, S0\n"
		"VLDR S4, [R4,#4]\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDE3E_thumb)
		);
}

// patch for 0x2CDEAA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDEB6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDEAA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VCVT.S32.F32 S0, S0\n"
		"LDRH R0, [R0]\n"
		"VCVT.S32.F32 S6, S16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDEB6_thumb)
		);
}

// patch for 0x2CDEC6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDED4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDEC6()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R2\n"
		"STR R1, [SP,#0x70+"/* var_70 */"-0x70]\n"
		"VMOV R1, S6\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDED4_thumb)
		);
}

// patch for 0x2CDF68
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDF70_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDF68()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDF70_thumb)
		);
}

// patch for 0x2CDF74
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDF7C_thumb = 0;	// loc_2CDF7C
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDF74()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"STR R0, [SP,#0x70+"/* var_50 */"-0x50]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDF7C_thumb)
		);
}

// patch for 0x2CDF7C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDF84_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDF7C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlantMgr___ColEntityCache_Update_2CDF84_thumb)
		);
}

// patch for 0x2CFDE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteAllRwObjects_2CFDF0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteAllRwObjects_2CFDE8()
{
	__asm(
	".thumb\n"
		"MOV R0, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R6, R9, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteAllRwObjects_2CFDF0_thumb)
		);
}

// patch for 0x2CFE5E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteAllRwObjects_2CFDE8_thumb = 0;	// loc_2CFDE8
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteAllRwObjects_2CFE6A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteAllRwObjects_2CFE5E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimension)
		"BNE 1f\n"
		"ADD R9, R9, #1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteAllRwObjects_2CFE6A_thumb)

		// Branches
		"1:\n"	// loc_2CFDE8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteAllRwObjects_2CFDE8_thumb)
		);
}

// patch for 0x2D08B4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D08BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D08B4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S30, fWorldSectorSize)
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S17, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D08BC_thumb)
		);
}

// patch for 0x2D0962
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D096C = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D096E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D0962()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VCVT.S32.F32 S26, S19\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D096C)
		"VCVT.S32.F32 S28, S28\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D096E_thumb)
		);
}

// patch for 0x2D0990
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D0998_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D0990()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R5\n"
		"STR R1, [SP,#0xB8+"/* var_A4 */"-0xA4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D0998_thumb)
		);
}

// patch for 0x2D099C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D09A6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D099C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R5, R1\n"
		"VMOV R1, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D09A6_thumb)
		);
}

// patch for 0x2D0A36
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D0A46_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D0A36()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R1\n"
		"LDR R2, [SP,#0xB8+"/* var_9C */"-0x9C]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D0A46_thumb)
		);
}

// patch for 0x2D0A5C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D0A64_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D0A5C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iNumberOfWorldSectorsPerDimensionMinusOne)
		"ORR R4, R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D0A64_thumb)
		);
}

// patch for 0x2D0A6E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D0A78_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D0A6E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R11\n"
		"LDR R2, [SP,#0xB8+"/* var_68 */"-0x68]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AddModelsToRequestList_2D0A78_thumb)
		);
}

// patch for 0x2D0BA8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0BB0 = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0BB6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0BA8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S8, fNumberOfWorldLODsectorsPerDimensionHalf)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0BB0)
		"VLDR S2, [R5,#4]\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S4, fWorldLODsectorSize)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0BB6_thumb)
		);
}

// patch for 0x2D0BBA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0BC4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0BBA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R9, iNumberOfWorldLODsectorsPerDimensionMinusOne)
		"MOVS R2, #0\n"
		"VLDR S16, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0BC4_thumb)
		);
}

// patch for 0x2D0C14
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0C1C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0C14()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldLODsectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R9\n"
		"STR R1, [SP,#0x70+"/* var_50 */"-0x50]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0C1C_thumb)
		);
}

// patch for 0x2D0C20
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0C2A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0C20()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldLODsectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R9, R1\n"
		"VMOV R1, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0C2A_thumb)
		);
}

// patch for 0x2D0C5E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0C68 = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0C6A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0C5E()
{
	__asm(
	".thumb\n"
		"MOV R1, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldLODsectorsPerDimension)
		"LDR R2, [SP,#0x70+"/* var_54 */"-0x54]\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0C68)
		"ADD R1, R2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__AddLodsToRequestList_2D0C6A_thumb)
		);
}

// patch for 0x2D2BA6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2BB0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2BA6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"LDR R1, [R1]\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2BB0_thumb)
		);
}

// patch for 0x2D2C1A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2C24_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2C1A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VMOV S2, R5\n"
		"VCVT.S32.F32 S6, S24\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2C24_thumb)
		);
}

// patch for 0x2D2C40
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2C48_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2C40()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2C48_thumb)
		);
}

// patch for 0x2D2CA4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2CAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2CA4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2CAC_thumb)
		);
}

// patch for 0x2D2CAE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2CB8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2CAE()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"STR R0, [SP,#0x70+"/* var_50 */"-0x50]\n"
		"LSLS R0, R1, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2CB8_thumb)
		);
}

// patch for 0x2D2CBC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2CC6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2CBC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__InstanceLoadedModels_2D2CC6_thumb)
		);
}

// patch for 0x2D50E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsAfterDeath_2D50EC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsAfterDeath_2D50E0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"VLDR S0, [R0]\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S20, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsAfterDeath_2D50EC_thumb)
		);
}

// patch for 0x2D5186
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsAfterDeath_2D5190_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsAfterDeath_2D5186()
{
	__asm(
	".thumb\n"
		"MOV R0, R8\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R9, R6, R0\n"
		"LDR R0, [SP,#0x48+"/* var_3C */"-0x3C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsAfterDeath_2D5190_thumb)
		);
}

// patch for 0x2D5202
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsAfterDeath_2D5162_thumb = 0;	// loc_2D5162
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsAfterDeath_2D520C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsAfterDeath_2D5202()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimension)
		"BNE 1f\n"
		"ADDS R6, #1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsAfterDeath_2D520C_thumb)

		// Branches
		"1:\n"	// loc_2D5162
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsAfterDeath_2D5162_thumb)
		);
}

// patch for 0x2D5C9A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5CA2 = 0;
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5CA4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5C9A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5CA2)
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S20, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5CA4_thumb)
		);
}

// patch for 0x2D5CE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5CF2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5CE8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VLDR S18, [R1]\n"
		"ADD R1, R6, #0x90C\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5CF2_thumb)
		);
}

// patch for 0x2D5D24
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5D2E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5D24()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOV R10, #0\n"
		"IT GE\n"
		"MOVGE R0, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5D2E_thumb)
		);
}

// patch for 0x2D5D5C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5D66_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5D5C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VCMPE.F32 S18, #0.0\n"
		"IT GE\n"
		"MOVGE R0, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5D66_thumb)
		);
}

// patch for 0x2D5D96
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5DA0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5D96()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R10, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R10, R5\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5DA0_thumb)
		);
}

// patch for 0x2D5DC8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5DD0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5DC8()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R6, R5\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5DD0_thumb)
		);
}

// patch for 0x2D5E18
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5E26_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5E18()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R10, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOV R0, #1\n"
		"BLT 500f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R10, iNumberOfWorldSectorsPerDimensionMinusOne)
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5E26_thumb)
		);
}

// patch for 0x2D5E56
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5E64_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5E56()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOV R0, #1\n"
		"BLT 500f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimensionMinusOne)
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5E64_thumb)
		);
}

// patch for 0x2D5E9E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5EAA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5E9E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		"AND R5, R10, #0xF\n"
		"IT GE\n"
		"MOVGE R6, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5EAA_thumb)
		);
}

// patch for 0x2D5EB2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5EBE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5EB2()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R11\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5EBE_thumb)
		);
}

// patch for 0x2D5EC0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5EC8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5EC0()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R9, R6, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5EC8_thumb)
		);
}

// patch for 0x2D5F5A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5F6E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5F5A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		"LDR R11, [SP,#0x60+"/* var_48 */"-0x48]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"MOV R9, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5F6E_thumb)
		);
}

// patch for 0x2D5F72
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5F7E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5F72()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R11\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5F7E_thumb)
		);
}

// patch for 0x2D5FFE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6008_thumb = 0;	// loc_2D6008
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D5FFE()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iNumberOfWorldSectorsPerDimensionMinusOne)
		"BLT 500f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R11, iNumberOfWorldSectorsPerDimensionMinusOne)
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6008_thumb)
		);
}

// patch for 0x2D603C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6048_thumb = 0;	// loc_2D6048
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D603C()
{
	__asm(
	".thumb\n"
		"IT LE\n"
		"MOVLE R8, #0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		"BLT 500f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6048_thumb)
		);
}

// patch for 0x2D60BC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D60C4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D60BC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D60C4_thumb)
		);
}

// patch for 0x2D60C6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D60D2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D60C6()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"MOV R11, R0\n"
		"MOV R0, R8,LSL#4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D60D2_thumb)
		);
}

// patch for 0x2D60D6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D60E0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D60D6()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D60E0_thumb)
		);
}

// patch for 0x2D6174
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6180_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6174()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"CMP R1, #0\n"
		"MOV R0, R1\n"
		"IT LE\n"
		"MOVLE R0, #0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6180_thumb)
		);
}

// patch for 0x2D6186
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6190_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6186()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"MOV R11, R0\n"
		"LSLS R0, R1, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6190_thumb)
		);
}

// patch for 0x2D6194
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D619E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6194()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D619E_thumb)
		);
}

// patch for 0x2D622C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6236_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D622C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iNumberOfWorldSectorsPerDimensionMinusOne)
		"AND R9, R10, #0xF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6236_thumb)
		);
}

// patch for 0x2D6240
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D624A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6240()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D624A_thumb)
		);
}

// patch for 0x2D624C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6254_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D624C()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R5, R11, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6254_thumb)
		);
}

// patch for 0x2D632C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6334_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D632C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"CMP R0, #0\n"
		"AND R5, R0, #0xF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6334_thumb)
		);
}

// patch for 0x2D633A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6344_thumb = 0;	// loc_2D6344
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D633A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R6, R1\n"
		"LDRD R8, R11, [SP,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6344_thumb)
		);
}

// patch for 0x2D6344
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D634C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6344()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D634C_thumb)
		);
}

// patch for 0x2D6352
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D635E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D6352()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R10, R6, R0\n"
		"ADD R0, R9, R10,LSL#3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CStreaming__DeleteRwObjectsBehindCamera_2D635E_thumb)
		);
}

// patch for 0x2DE98E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCollision__CheckCameraCollisionBuildings_2DE998_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCollision__CheckCameraCollisionBuildings_2DE98E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R3\n"
		"CMP R1, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCollision__CheckCameraCollisionBuildings_2DE998_thumb)
		);
}

// patch for 0x2DE99E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCollision__CheckCameraCollisionBuildings_2DE9A4 = 0;
	uintptr_t Address_GTA_SA_2_00_CCollision__CheckCameraCollisionBuildings_2DE9AA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCollision__CheckCameraCollisionBuildings_2DE99E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CCollision__CheckCameraCollisionBuildings_2DE9A4)
		"IT GE\n"
		"MOVGE R1, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCollision__CheckCameraCollisionBuildings_2DE9AA_thumb)
		);
}

// patch for 0x2DE9AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCollision__CheckCameraCollisionBuildings_2DE9B6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCollision__CheckCameraCollisionBuildings_2DE9AC()
{
	__asm(
	".thumb\n"
		"ADD R0, R0, R1\n"
		"MOVS R1, #0\n"
		"LDR R9, [R2,R0,LSL#3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCollision__CheckCameraCollisionBuildings_2DE9B6_thumb)
		);
}

// patch for 0x2DF83A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCollision__BuildCacheOfCameraCollision_2DF846_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCollision__BuildCacheOfCameraCollision_2DF83A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fWorldSectorSize)
		"VDIV.F32 S0, S22, S24\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCollision__BuildCacheOfCameraCollision_2DF846_thumb)
		);
}

// patch for 0x2DF8E6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCollision__BuildCacheOfCameraCollision_2DF8F0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCollision__BuildCacheOfCameraCollision_2DF8E6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		"STR R4, [SP,#0xA8+"/* var_94 */"-0x94]\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R3, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCollision__BuildCacheOfCameraCollision_2DF8F0_thumb)
		);
}

// patch for 0x2DF8FA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCollision__BuildCacheOfCameraCollision_2DF906_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCollision__BuildCacheOfCameraCollision_2DF8FA()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R5, R2\n"
		"STR R5, [R1]\n"
		"MOV R1, #0xFFFF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCollision__BuildCacheOfCameraCollision_2DF906_thumb)
		);
}

// patch for 0x2ED7DE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED7E8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED7DE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fWorldSectorSize)
		"ADD R1, R0, #0x30\n"
		"CMP R0, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED7E8_thumb)
		);
}

// patch for 0x2ED7EC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED7F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED7EC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S26, fNumberOfWorldSectorsPerDimensionHalf)
		"VLDR S2, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED7F4_thumb)
		);
}

// patch for 0x2ED868
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED870_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED868()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VCVT.S32.F32 S0, S0\n"
		"LDRH R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED870_thumb)
		);
}

// patch for 0x2ED880
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED888_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED880()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R2\n"
		"STR R1, [SP,#0x90+"/* var_74 */"-0x74]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED888_thumb)
		);
}

// patch for 0x2ED88C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED896_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED88C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R2, R1\n"
		"VMOV R1, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindMaximumSpeedForThisCarInTraffic_2ED896_thumb)
		);
}

// patch for 0x2EE336
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__ScanForPedDanger_2EE340_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__ScanForPedDanger_2EE336()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fWorldSectorSize)
		"ADD R0, R1, #0x30\n"
		"CMP R1, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__ScanForPedDanger_2EE340_thumb)
		);
}

// patch for 0x2EE344
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__ScanForPedDanger_2EE34C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__ScanForPedDanger_2EE344()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S26, fNumberOfWorldSectorsPerDimensionHalf)
		"VLDR S2, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__ScanForPedDanger_2EE34C_thumb)
		);
}

// patch for 0x2EE3C4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__ScanForPedDanger_2EE3CE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__ScanForPedDanger_2EE3C4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VCVT.S32.F32 S0, S0\n"
		"LDRH R1, [R5,#0x3DF]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__ScanForPedDanger_2EE3CE_thumb)
		);
}

// patch for 0x2EE3DE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__ScanForPedDanger_2EE3EC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__ScanForPedDanger_2EE3DE()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R4\n"
		"STR R1, [SP,#0x88+"/* var_68 */"-0x68]\n"
		"VMOV R1, S0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__ScanForPedDanger_2EE3EC_thumb)
		);
}

// patch for 0x2EE5C4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SlowCarDownForOtherCar_2EE5CC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SlowCarDownForOtherCar_2EE5C4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fNumberOfWorldSectorsPerDimensionHalf)
		"VLDR S24, [R11,#0x48]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SlowCarDownForOtherCar_2EE5CC_thumb)
		);
}

// patch for 0x2EEEEC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindAngleToWeaveThroughTraffic_2EEEF6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindAngleToWeaveThroughTraffic_2EEEEC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"MOV R8, R3\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S26, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindAngleToWeaveThroughTraffic_2EEEF6_thumb)
		);
}

// patch for 0x2EEF96
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindAngleToWeaveThroughTraffic_2EEFA0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindAngleToWeaveThroughTraffic_2EEF96()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VMOV S16, R9\n"
		"LDR R1, [R1]\n"
		"LDRH R1, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindAngleToWeaveThroughTraffic_2EEFA0_thumb)
		);
}

// patch for 0x2EEFBC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindAngleToWeaveThroughTraffic_2EEFC4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindAngleToWeaveThroughTraffic_2EEFBC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"STR R0, [SP,#0xB8+"/* var_9C */"-0x9C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindAngleToWeaveThroughTraffic_2EEFC4_thumb)
		);
}

// patch for 0x2EEFC8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindAngleToWeaveThroughTraffic_2EEFD2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindAngleToWeaveThroughTraffic_2EEFC8()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R2, R0\n"
		"VMOV R0, S6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindAngleToWeaveThroughTraffic_2EEFD2_thumb)
		);
}

// patch for 0x31B720
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPedPath__CalcPedRoute_31B72C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPedPath__CalcPedRoute_31B720()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S26, fWorldSectorSize)
		"VDIV.F32 S0, S20, S26\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S20, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPedPath__CalcPedRoute_31B72C_thumb)
		);
}

// patch for 0x31B796
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPedPath__CalcPedRoute_31B7A2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPedPath__CalcPedRoute_31B796()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VCVT.S32.F32 S2, S2\n"
		"VMOV R0, S6\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPedPath__CalcPedRoute_31B7A2_thumb)
		);
}

// patch for 0x31B7AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPedPath__CalcPedRoute_31B7B4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPedPath__CalcPedRoute_31B7AC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R1, R0\n"
		"MOVS R0, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPedPath__CalcPedRoute_31B7B4_thumb)
		);
}

// patch for 0x3444B4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands500To599_3444BE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands500To599_3444B4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S2, fWorldMapMaxCoord)
		"LDR R0, =("/* ScriptParams_ptr */"0x676F7C - 0x3444C6)\n"
		"VADD.F32 S4, S18, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands500To599_3444BE_thumb)
		);
}

// patch for 0x3ED8C2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Add_3ED8D2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Add_3ED8C2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S6, fWorldMapMaxCoord)
		"VLDR S2, [R1,#8]\n"
		"VCMPE.F32 S16, S6\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fWorldMapMaxCoordMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Add_3ED8D2_thumb)
		);
}

// patch for 0x3ED8E2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Add_3ED8EE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Add_3ED8E2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S8, fWorldMapMinCoord)
		"VMAX.F32 D10, D2, D4\n"
		"VMAX.F32 D0, D0, D4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Add_3ED8EE_thumb)
		);
}

// patch for 0x3ED908
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Add_3ED910_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Add_3ED908()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Add_3ED910_thumb)
		);
}

// patch for 0x3ED9C8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Add_3ED9D2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Add_3ED9C8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"CMP R1, #0\n"
		"IT GT\n"
		"MOVGT R0, R1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Add_3ED9D2_thumb)
		);
}

// patch for 0x3ED9DA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Add_3ED9E6_thumb = 0;	// loc_3ED9E6
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Add_3ED9DA()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"MOV R4, R0\n"
		"LSLS R0, R1, #4\n"
		"UXTB R11, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Add_3ED9E6_thumb)
		);
}

// patch for 0x3EDA14
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Add_3EDA1E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Add_3EDA14()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Add_3EDA1E_thumb)
		);
}

// patch for 0x3EDA80
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Add_3EDA88_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Add_3EDA80()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Add_3EDA88_thumb)
		);
}

// patch for 0x3EDACE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Add_3EDADA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Add_3EDACE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S2, fWorldLODsectorSize)
		"VDIV.F32 S4, S16, S2\n"
		"VDIV.F32 S6, S18, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Add_3EDADA_thumb)
		);
}

// patch for 0x3EDAE2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Add_3EDAEE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Add_3EDAE2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S2, fNumberOfWorldLODsectorsPerDimensionHalf)
		"VADD.F32 S4, S4, S2\n"
		"VADD.F32 S6, S6, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Add_3EDAEE_thumb)
		);
}

// patch for 0x3EDB1C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Add_3EDB24 = 0;
	uintptr_t Address_GTA_SA_2_00_CEntity__Add_3EDB28_thumb = 0;	// loc_3EDB28
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Add_3EDB1C()
{
	__asm(
	".thumb\n"
		"MOV R1, R10\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, NumberOfWorldLODSectorsPerDimensionMultipliedByListSize)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CEntity__Add_3EDB24)
		"LDR R0, [R0]\n"
		"ADD R6, R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Add_3EDB28_thumb)
		);
}

// patch for 0x3EDBB8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Remove_3EDBC0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Remove_3EDBB8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S6, fWorldMapMaxCoord)
		"VLDR S2, [SP,#0x78+"/* var_50 */"-0x50]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Remove_3EDBC0_thumb)
		);
}

// patch for 0x3EDBC4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Remove_3EDBCC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Remove_3EDBC4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fWorldMapMaxCoordMinusOne)
		"VMRS APSR_nzcv, FPSCR\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Remove_3EDBCC_thumb)
		);
}

// patch for 0x3EDBE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Remove_3EDBF2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Remove_3EDBE8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S2, fWorldMapMinCoord)
		"LDRB R0, [R4,#0x1D]\n"
		"VMAX.F32 D10, D2, D1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Remove_3EDBF2_thumb)
		);
}

// patch for 0x3EDBFC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Remove_3EDC04_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Remove_3EDBFC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Remove_3EDC04_thumb)
		);
}

// patch for 0x3EDCC8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Remove_3EDCD8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Remove_3EDCC8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"MOV R9, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Remove_3EDCD8_thumb)
		);
}

// patch for 0x3EDD2A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Remove_3EDD36_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Remove_3EDD2A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		"ADD R1, R0, R9\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Remove_3EDD36_thumb)
		);
}

// patch for 0x3EDDA6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Remove_3EDDB0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Remove_3EDDA6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		"LDR R1, [SP,#0x78+"/* var_6C */"-0x6C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Remove_3EDDB0_thumb)
		);
}

// patch for 0x3EDE06
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Remove_3EDE12_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Remove_3EDE06()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S2, fWorldLODsectorSize)
		"VDIV.F32 S4, S16, S2\n"
		"VDIV.F32 S6, S18, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Remove_3EDE12_thumb)
		);
}

// patch for 0x3EDE1A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Remove_3EDE26_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Remove_3EDE1A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S2, fNumberOfWorldLODsectorsPerDimensionHalf)
		"VADD.F32 S4, S4, S2\n"
		"VADD.F32 S6, S6, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Remove_3EDE26_thumb)
		);
}

// patch for 0x3EDE6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__Remove_3EDE74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__Remove_3EDE6C()
{
	__asm(
	".thumb\n"
		"MOV R0, R10\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldLODsectorsPerDimension)
		"MOV R8, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__Remove_3EDE74_thumb)
		);
}

// patch for 0x3EDF34
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntity__LivesInThisNonOverlapSector_3EDF40_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntity__LivesInThisNonOverlapSector_3EDF34()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		"VADD.F32 S0, S0, S2\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntity__LivesInThisNonOverlapSector_3EDF40_thumb)
		);
}

// patch for 0x3FCE10
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPhysical__Add_3FCE1C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPhysical__Add_3FCE10()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"VLDR S0, [SP,#0x78+"/* var_58 */"-0x58]\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPhysical__Add_3FCE1C_thumb)
		);
}

// patch for 0x3FD084
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPhysical__RemoveAndAdd_3FD090_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPhysical__RemoveAndAdd_3FD084()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"VLDR S0, [SP,#0x78+"/* var_58 */"-0x58]\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPhysical__RemoveAndAdd_3FD090_thumb)
		);
}

// patch for 0x3FF6A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPhysical__CheckCollision_3FF6B4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPhysical__CheckCollision_3FF6A8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"VLDR S0, [SP,#0x50+"/* var_50 */"-0x50]\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPhysical__CheckCollision_3FF6B4_thumb)
		);
}

// patch for 0x3FF832
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPhysical__ProcessCollisionSectorList_3FF83E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPhysical__ProcessCollisionSectorList_3FF832()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOV R3, #0\n"
		"IT GE\n"
		"MOVGE R1, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPhysical__ProcessCollisionSectorList_3FF83E_thumb)
		);
}

// patch for 0x3FF848
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPhysical__ProcessCollisionSectorList_3FF852_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPhysical__ProcessCollisionSectorList_3FF848()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VMOV.F32 S21, #3.0\n"
		"IT GE\n"
		"MOVGE R3, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPhysical__ProcessCollisionSectorList_3FF852_thumb)
		);
}

// patch for 0x3FF854
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPhysical__ProcessCollisionSectorList_3FF85C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPhysical__ProcessCollisionSectorList_3FF854()
{
	__asm(
	".thumb\n"
		"MOV R2, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimension)
		"LDR R3, =("/* _ZN6CWorld11ms_aSectorsE_ptr */"0x676734 - 0x3FF866)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPhysical__ProcessCollisionSectorList_3FF85C_thumb)
		);
}

// patch for 0x3FF864
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPhysical__ProcessCollisionSectorList_3FF86C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPhysical__ProcessCollisionSectorList_3FF864()
{
	__asm(
	".thumb\n"
		"ADD R1, R1, R2\n"
		"VMOV.F32 S19, #20.0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPhysical__ProcessCollisionSectorList_3FF86C_thumb)
		);
}

// patch for 0x4011FA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPhysical__ProcessShift_401202 = 0;
	uintptr_t Address_GTA_SA_2_00_CPhysical__ProcessShift_401204_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPhysical__ProcessShift_4011FA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CPhysical__ProcessShift_401202)
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPhysical__ProcessShift_401204_thumb)
		);
}

// patch for 0x4014E6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPhysical__ProcessShiftSectorList_4014F2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPhysical__ProcessShiftSectorList_4014E6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOV R3, #0\n"
		"IT GE\n"
		"MOVGE R1, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPhysical__ProcessShiftSectorList_4014F2_thumb)
		);
}

// patch for 0x4014FE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPhysical__ProcessShiftSectorList_401508_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPhysical__ProcessShiftSectorList_4014FE()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VLDR S26, 101f\n"
		"IT GE\n"
		"MOVGE R3, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPhysical__ProcessShiftSectorList_401508_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, 0.0)
		);
}

// patch for 0x40150A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPhysical__ProcessShiftSectorList_401514_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPhysical__ProcessShiftSectorList_40150A()
{
	__asm(
	".thumb\n"
		"MOV R2, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimension)
		"LDR R3, =("/* _ZN6CWorld11ms_aSectorsE_ptr */"0x676734 - 0x40151C)\n"
		"LDR R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPhysical__ProcessShiftSectorList_401514_thumb)
		);
}

// patch for 0x40151A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPhysical__ProcessShiftSectorList_401526_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPhysical__ProcessShiftSectorList_40151A()
{
	__asm(
	".thumb\n"
		"ADD R1, R1, R2\n"
		"VMOV.F32 S18, S26\n"
		"VLDR S28, 101f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPhysical__ProcessShiftSectorList_401526_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, 0.1)
		);
}

// patch for 0x40A572
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlayerInfo__Process_40A57C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlayerInfo__Process_40A572()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fNumberOfWorldSectorsPerDimensionHalf)
		"LDR R1, [R0,#0x14]\n"
		"ADD R2, R1, #0x30\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlayerInfo__Process_40A57C_thumb)
		);
}

// patch for 0x40B05E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlayerInfo__FindObjectToSteal_40B06A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlayerInfo__FindObjectToSteal_40B05E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fNumberOfWorldSectorsPerDimensionHalf)
		"VMOV.I32 D16, #0x3F000000\n"
		"VLDR D17, [R1,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlayerInfo__FindObjectToSteal_40B06A_thumb)
		);
}

// patch for 0x40B0F2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlayerInfo__FindObjectToSteal_40B0FC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlayerInfo__FindObjectToSteal_40B0F2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R9, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VMOV R11, S20\n"
		"MOVS R5, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlayerInfo__FindObjectToSteal_40B0FC_thumb)
		);
}

// patch for 0x40B112
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlayerInfo__FindObjectToSteal_40B11C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlayerInfo__FindObjectToSteal_40B112()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R4, R9\n"
		"VCVT.S32.F32 S0, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlayerInfo__FindObjectToSteal_40B11C_thumb)
		);
}

// patch for 0x40B12C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlayerInfo__FindObjectToSteal_40B136_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlayerInfo__FindObjectToSteal_40B12C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R9, R0\n"
		"VMOV R0, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlayerInfo__FindObjectToSteal_40B136_thumb)
		);
}

// patch for 0x40F1E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanWorld_40F1EA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanWorld_40F1E0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S0, fWorldSectorSize)
		"MOVS R1, #0\n"
		"VLDR S2, [SP,#0xF0+"/* var_C8 */"-0xC8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanWorld_40F1EA_thumb)
		);
}

// patch for 0x40F20A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanWorld_40F216_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanWorld_40F20A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S5, fNumberOfWorldSectorsPerDimensionHalf)
		"VLDR S4, [SP,#0xF0+"/* var_C4 */"-0xC4]\n"
		"VADD.F32 S6, S6, S5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanWorld_40F216_thumb)
		);
}

// patch for 0x40F2A2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanWorld_40F2AC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanWorld_40F2A2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S0, fWorldLODsectorSize)
		"MOVS R1, #5\n"
		"VLDR S2, [SP,#0xF0+"/* var_C8 */"-0xC8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanWorld_40F2AC_thumb)
		);
}

// patch for 0x40F300
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanWorld_40F308_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanWorld_40F300()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S5, fNumberOfWorldLODsectorsPerDimensionHalf)
		"VADD.F32 S2, S2, S5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanWorld_40F308_thumb)
		);
}

// patch for 0x40F748
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ConstructRenderList_40F750_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ConstructRenderList_40F748()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S4, fWorldSectorSize)
		"ADD R1, R0, #0x30\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ConstructRenderList_40F750_thumb)
		);
}

// patch for 0x4108E8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_4108F0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_4108E8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S4, fWorldSectorSize)
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S6, fWorldSectorSizeHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_4108F0_thumb)
		);
}

// patch for 0x410938
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_410940_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_410938()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S6, fWorldSectorSizeDoubledThenSquared)
		"VCMPE.F32 S4, S6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_410940_thumb)
		);
}

// patch for 0x41099C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_4109A2 = 0;
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_4109A4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_41099C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CRenderer__ScanSectorList_4109A2)
		"BGT 500f\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_4109A4_thumb)
		);
}

// patch for 0x4109DC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_4109E6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_4109DC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"STR R0, [R2,#0xC]\n"
		"MOV R0, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_4109E6_thumb)
		);
}

// patch for 0x4109EA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_4109F8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_4109EA()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R4, R1\n"
		"CMP R5, #0\n"
		"IT GT\n"
		"MOVGT R0, R5\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_4109F8_thumb)
		);
}

// patch for 0x4109FC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_410A04_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_4109FC()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R0, R4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_410A04_thumb)
		);
}

// patch for 0x410D6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410F5A_thumb = 0;	// locret_410F5A
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410D76_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410D6C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldLODsectorsPerDimensionMinusOne)
		"BGT 500f\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldLODsectorsPerDimensionMinusOne)
		"500:\n"	// past the IT block
		"BGT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410D76_thumb)

		// Branches
		"1:\n"	// locret_410F5A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410F5A_thumb)
		);
}

// patch for 0x410D90
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410D98_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410D90()
{
	__asm(
	".thumb\n"
		"MOV R2, R1\n"
		ASM_SUB_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldLODsectorsPerDimensionHalf)
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S4, fWorldLODsectorSize)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410D98_thumb)
		);
}

// patch for 0x410D9A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410DA6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410D9A()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldLODsectorsPerDimension)
		"VMOV S0, R2\n"
		"MOV R2, R0\n"
		ASM_SUB_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldLODsectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410DA6_thumb)
		);
}

// patch for 0x410DA8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410DB0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410DA8()
{
	__asm(
	".thumb\n"
		"ADD R0, R0, R1\n"
		"VMOV S2, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410DB0_thumb)
		);
}

// patch for 0x410DD4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410DDC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410DD4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S4, fWorldSectorSizeHalf)
		"VADD.F32 S0, S0, S4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410DDC_thumb)
		);
}

// patch for 0x410DF8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410E00_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410DF8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S6, fWorldLODsectorSizeTimesSquareRootOfTwoThenSquared)
		"VCMPE.F32 S4, S6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanBigBuildingList_410E00_thumb)
		);
}

// patch for 0x4116F8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_RequestModels_411700_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_RequestModels_4116F8()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R10, iNumberOfWorldSectorsPerDimensionMinusOne)
		"BGT 500f\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_RequestModels_411700_thumb)
		);
}

// patch for 0x411718
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_RequestModels_411720_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_RequestModels_411718()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOV R2, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_RequestModels_411720_thumb)
		);
}

// patch for 0x41172E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_RequestModels_411738_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_RequestModels_41172E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"AND R0, R0, #0xF\n"
		"IT GE\n"
		"MOVGE R2, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_RequestModels_411738_thumb)
		);
}

// patch for 0x41173A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_RequestModels_411746_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_RequestModels_41173A()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimension)
		"STR R0, [SP,#0x28+"/* var_20 */"-0x20]\n"
		"LDR R1, [R1]\n"
		"ADD R2, R3, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_RequestModels_411746_thumb)
		);
}

// patch for 0x411C5A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__RequestObjectsInFrustum_411C64_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__RequestObjectsInFrustum_411C5A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S0, fWorldSectorSize)
		"MOVS R1, #3\n"
		"VLDR S2, [SP,#0xD8+"/* var_B4 */"-0xB4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__RequestObjectsInFrustum_411C64_thumb)
		);
}

// patch for 0x411C98
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__RequestObjectsInFrustum_411CA0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__RequestObjectsInFrustum_411C98()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S12, fNumberOfWorldSectorsPerDimensionHalf)
		"VADD.F32 S2, S2, S12\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__RequestObjectsInFrustum_411CA0_thumb)
		);
}

// patch for 0x411D16
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D1C = 0;
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D20_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D16()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D1C)
		"BGT 500f\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"500:\n"	// past the IT block
		"LDR R4, [R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D20_thumb)
		);
}

// patch for 0x411D60
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D6A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D60()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		"STR R3, [R4,#0xC]\n"
		"MOV R3, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D6A_thumb)
		);
}

// patch for 0x411D6E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D7C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D6E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R5\n"
		"CMP R1, #0\n"
		"IT GT\n"
		"MOVGT R3, R1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D7C_thumb)
		);
}

// patch for 0x411D80
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D88_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D80()
{
	__asm(
	".thumb\n"
		"MOV R1, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimension)
		"ADD R0, R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModels_411D88_thumb)
		);
}

// patch for 0x411FD0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModelsVisible_411FD6 = 0;
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModelsVisible_411FD8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_ListModelsVisible_411FD0()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModelsVisible_411FD6)
		"BGT 500f\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModelsVisible_411FD8_thumb)
		);
}

// patch for 0x412016
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModelsVisible_412020_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_ListModelsVisible_412016()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LE\n"
		"MOVLE R0, R2\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModelsVisible_412020_thumb)
		);
}

// patch for 0x41202A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModelsVisible_412038_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__ScanSectorList_ListModelsVisible_41202A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R2, R3\n"
		"MOV R1, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimension)
		"ADD R0, R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__ScanSectorList_ListModelsVisible_412038_thumb)
		);
}

// patch for 0x41223E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__GetObjectsInFrustum_412248_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__GetObjectsInFrustum_41223E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S0, fWorldSectorSize)
		"CMP R5, #0\n"
		"VLDR S2, [SP,#0xD0+"/* var_B0 */"-0xB0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__GetObjectsInFrustum_412248_thumb)
		);
}

// patch for 0x41227C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRenderer__GetObjectsInFrustum_412284_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRenderer__GetObjectsInFrustum_41227C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S12, fNumberOfWorldSectorsPerDimensionHalf)
		"VADD.F32 S2, S2, S12\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRenderer__GetObjectsInFrustum_412284_thumb)
		);
}

// patch for 0x4201B6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTimeCycle__CalcColoursForPoint_4201C2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTimeCycle__CalcColoursForPoint_4201B6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S2, fWorldMapMinCoord)
		"VMOV S4, R3\n"
		"VCMPE.F32 S4, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTimeCycle__CalcColoursForPoint_4201C2_thumb)
		);
}

// patch for 0x4201CE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTimeCycle__CalcColoursForPoint_4201DA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTimeCycle__CalcColoursForPoint_4201CE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S6, fWorldMapMaxCoord)
		"VCMPE.F32 S4, S6\n"
		"VMRS APSR_nzcv, FPSCR\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTimeCycle__CalcColoursForPoint_4201DA_thumb)
		);
}

// patch for 0x4201FC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTimeCycle__CalcColoursForPoint_420204_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTimeCycle__CalcColoursForPoint_4201FC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S6, fWorldMapMaxCoord)
		"VCMPE.F32 S4, S6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTimeCycle__CalcColoursForPoint_420204_thumb)
		);
}

// patch for 0x422ECC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_422E8E_thumb = 0;	// loc_422E8E
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_422ED4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ShutDown_422ECC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iTotalNumberOfWorldLODsectors)
		"BNE 1f\n"
		"LDR R0, =("/* _ZN6CWorld17ms_aRepeatSectorsE_ptr */"0x6771E4 - 0x422EDC)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ShutDown_422ED4_thumb)

		// Branches
		"1:\n"	// loc_422E8E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ShutDown_422E8E_thumb)
		);
}

// patch for 0x423058
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_422FC8_thumb = 0;	// loc_422FC8
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_423060_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ShutDown_423058()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iTotalNumberOfWorldSectors)
		"BNE 1f\n"
		"LDR R0, =("/* _ZN6CWorld11ms_aSectorsE_ptr */"0x676734 - 0x423070)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ShutDown_423060_thumb)

		// Branches
		"1:\n"	// loc_422FC8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ShutDown_422FC8_thumb)
		);
}

// patch for 0x42306E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_423078_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ShutDown_42306E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, iNegativeTotalNumberOfWorldSectors)
		"MOVT R10, #0x8888\n"
		"LDR R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ShutDown_423078_thumb)
		);
}

// patch for 0x42308C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_4230B8_thumb = 0;	// loc_4230B8
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_423096_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ShutDown_42308C()
{
	__asm(
	".thumb\n"
		"MOV R8, R5\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R8, iTotalNumberOfWorldSectors)
		"CBZ R0, 1f\n"
		"SMMLA R0, R10, R8, R8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ShutDown_423096_thumb)

		// Branches
		"1:\n"	// loc_4230B8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ShutDown_4230B8_thumb)
		);
}

// patch for 0x4230A2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_4230AC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ShutDown_4230A2()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"LSRS R3, R3, #6\n"
		"SUB R2, R8, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ShutDown_4230AC_thumb)
		);
}

// patch for 0x4230CC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_4230D6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ShutDown_4230CC()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"LSRS R3, R3, #6\n"
		"SUB R2, R8, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ShutDown_4230D6_thumb)
		);
}

// patch for 0x42313A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_423144_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ShutDown_42313A()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"LSRS R3, R3, #6\n"
		"SUB R2, R6, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ShutDown_423144_thumb)
		);
}

// patch for 0x42316C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_423176 = 0;
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_423178_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ShutDown_42316C()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"LSRS R3, R3, #6\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CWorld__ShutDown_423176)
		"SUB R2, R6, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ShutDown_423178_thumb)
		);
}

// patch for 0x42319E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_4231A8 = 0;
	uintptr_t Address_GTA_SA_2_00_CWorld__ShutDown_4231AA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ShutDown_42319E()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"LSRS R3, R3, #6\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CWorld__ShutDown_4231A8)
		"SUB R2, R6, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ShutDown_4231AA_thumb)
		);
}

// patch for 0x423450
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423458 = 0;
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42345A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423450()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423458)
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42345A_thumb)
		);
}

// patch for 0x423508
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423510_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423508()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOV R0, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423510_thumb)
		);
}

// patch for 0x42351A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423528_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42351A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R8, R1, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423528_thumb)
		);
}

// patch for 0x42360E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423618_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42360E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iNumberOfWorldSectorsPerDimensionMinusOne)
		"AND R11, R11, #0xF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423618_thumb)
		);
}

// patch for 0x42366E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42367E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42366E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R10, R9, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42367E_thumb)
		);
}

// patch for 0x42374C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423754_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42374C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423754_thumb)
		);
}

// patch for 0x423756
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423762_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423756()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"MOV R5, R0\n"
		"MOV R0, R6,LSL#4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423762_thumb)
		);
}

// patch for 0x4237B4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4237BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4237B4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4237BC_thumb)
		);
}

// patch for 0x4238BC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4238CC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4238BC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R10, R9, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4238CC_thumb)
		);
}

// patch for 0x4239D4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4239DC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4239D4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GT\n"
		"MOVGT R8, R11\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4239DC_thumb)
		);
}

// patch for 0x4239E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4239E8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4239E0()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOV R5, R6,LSL#4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4239E8_thumb)
		);
}

// patch for 0x423A48
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423A58_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423A48()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R10, R8, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423A58_thumb)
		);
}

// patch for 0x423B58
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423B60_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423B58()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423B60_thumb)
		);
}

// patch for 0x423C50
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423C58_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423C50()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GT\n"
		"MOVGT R8, R11\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423C58_thumb)
		);
}

// patch for 0x423C5C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423C64_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423C5C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOV R5, R6,LSL#4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423C64_thumb)
		);
}

// patch for 0x423CC4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423CD4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423CC4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R10, R8, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423CD4_thumb)
		);
}

// patch for 0x423DD2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423DE2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423DD2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R10, R8, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423DE2_thumb)
		);
}

// patch for 0x423EA6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423EB0 = 0;
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423EB0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423EA6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		"ADD R10, SP, #0xB8+"/* var_70 */"-0x70\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423EB0)
		"LDR R1, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423EB0_thumb)
		);
}

// patch for 0x423F60
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423F68_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423F60()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iNumberOfWorldSectorsPerDimensionMinusOne)
		"AND R1, R11, #0xF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423F68_thumb)
		);
}

// patch for 0x423F8C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423F9A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423F8C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R8, R9, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423F9A_thumb)
		);
}

// patch for 0x424048
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423F78_thumb = 0;	// loc_423F78
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424050_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424048()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		"CMP R5, R2\n"
		"MOV R5, R0\n"
		"BLT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424050_thumb)

		// Branches
		"1:\n"	// loc_423F78
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_423F78_thumb)
		);
}

// patch for 0x424066
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424074_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424066()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R8, R9, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424074_thumb)
		);
}

// patch for 0x424120
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424128_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424120()
{
	__asm(
	".thumb\n"
		"SUBS R4, #0x10\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		"CMP R5, R2\n"
		"MOV R5, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424128_thumb)
		);
}

// patch for 0x42413E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424148_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42413E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		"AND R9, R1, #0xF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424148_thumb)
		);
}

// patch for 0x4241A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4241AE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4241A0()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R8\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R4, R5, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4241AE_thumb)
		);
}

// patch for 0x424330
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424340_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424330()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R10, R8, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424340_thumb)
		);
}

// patch for 0x424404
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42440E = 0;
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42440C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424404()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		"ADD R10, SP, #0xB8+"/* var_70 */"-0x70\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42440E)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42440C_thumb)
		);
}

// patch for 0x4244BE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4244CA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4244BE()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iNumberOfWorldSectorsPerDimensionMinusOne)
		"AND R1, R11, #0xF\n"
		"IT GE\n"
		"MOVGE R9, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4244CA_thumb)
		);
}

// patch for 0x4244EA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4244F8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4244EA()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R8, R9, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4244F8_thumb)
		);
}

// patch for 0x4245A6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4244D6_thumb = 0;	// loc_4244D6
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424688_thumb = 0;	// loc_424688
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4245A6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		"CMP R5, R2\n"
		"MOV R5, R0\n"
		"BLT 1f\n"
		"B 2f\n"

		// Branches
		"1:\n"	// loc_4244D6
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4244D6_thumb)
		"2:\n"	// loc_424688
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424688_thumb)
		);
}

// patch for 0x4245C4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4245D2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4245C4()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R8, R9, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4245D2_thumb)
		);
}

// patch for 0x424680
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4245B0_thumb = 0;	// loc_4245B0
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424680()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		"CMP R5, R2\n"
		"MOV R5, R0\n"
		"BGT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424688_thumb)

		// Branches
		"1:\n"	// loc_4245B0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4245B0_thumb)
		);
}

// patch for 0x42469C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4246A6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42469C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		"AND R9, R1, #0xF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4246A6_thumb)
		);
}

// patch for 0x4246F4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424702_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4246F4()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R8\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R4, R5, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424702_thumb)
		);
}

// patch for 0x4247FA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424808_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_4247FA()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R8\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R4, R5, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424808_thumb)
		);
}

// patch for 0x424900
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42490E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_424900()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R8\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R4, R5, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__GetIsLineOfSightClear_42490E_thumb)
		);
}

// patch for 0x424B84
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424B8C = 0;
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424B8E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424B84()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424B8C)
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424B8E_thumb)
		);
}

// patch for 0x424C46
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424C4E = 0;
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424C50_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424C46()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424C4E)
		"LDR R6, =("/* _ZN6CWorld11ms_aSectorsE_ptr */"0x676734 - 0x424C58)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424C50_thumb)
		);
}

// patch for 0x424C80
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424C8A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424C80()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOV R0, #0\n"
		"IT GE\n"
		"MOVGE R2, R4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424C8A_thumb)
		);
}

// patch for 0x424C94
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424CA2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424C94()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R0, R2, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424CA2_thumb)
		);
}

// patch for 0x424CDA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424CE6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424CDA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R4, R1\n"
		"MOV R5, R10,LSL#4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424CE6_thumb)
		);
}

// patch for 0x424D1C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424D24_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424D1C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424D24_thumb)
		);
}

// patch for 0x424D5E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424D6A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424D5E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_84 */"-0x84]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424D6A_thumb)
		);
}

// patch for 0x424D6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424D74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424D6C()
{
	__asm(
	".thumb\n"
		"ADD R0, R4, R0\n"
		"ADD R0, R2, R0,LSL#3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424D74_thumb)
		);
}

// patch for 0x424D9E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424DAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424D9E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"MOV R2, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424DAC_thumb)
		);
}

// patch for 0x424DAE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424DB8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424DAE()
{
	__asm(
	".thumb\n"
		"MOV R6, R0\n"
		"MOV R0, R10,LSL#4\n"
		"UXTB R4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424DB8_thumb)
		);
}

// patch for 0x424DF0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424DF8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424DF0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424DF8_thumb)
		);
}

// patch for 0x424E1E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424E28_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424E1E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		"LDR R1, [SP,#0xD0+"/* var_88 */"-0x88]\n"
		"ADD R0, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424E28_thumb)
		);
}

// patch for 0x424E84
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424E8C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424E84()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424E8C_thumb)
		);
}

// patch for 0x424EC6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424ED2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424EC6()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_84 */"-0x84]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424ED2_thumb)
		);
}

// patch for 0x424ED4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424EDC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424ED4()
{
	__asm(
	".thumb\n"
		"ADD R0, R4, R0\n"
		"ADD R0, R2, R0,LSL#3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424EDC_thumb)
		);
}

// patch for 0x424F4A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424F58_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424F4A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GT\n"
		"MOVGT R4, R5\n"
		"VCVT.S32.F32 S0, S0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424F58_thumb)
		);
}

// patch for 0x424FA0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424FA8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424FA0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424FA8_thumb)
		);
}

// patch for 0x424FE2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424FEE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424FE2()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_84 */"-0x84]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424FEE_thumb)
		);
}

// patch for 0x424FF0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424FF8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_424FF0()
{
	__asm(
	".thumb\n"
		"ADD R0, R4, R0\n"
		"ADD R0, R2, R0,LSL#3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_424FF8_thumb)
		);
}

// patch for 0x425040
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425048_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_425040()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425048_thumb)
		);
}

// patch for 0x42506E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425078_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_42506E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		"LDR R1, [SP,#0xD0+"/* var_84 */"-0x84]\n"
		"ADD R0, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425078_thumb)
		);
}

// patch for 0x4250D6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4250E4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4250D6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GT\n"
		"MOVGT R4, R5\n"
		"VCVT.S32.F32 S0, S0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4250E4_thumb)
		);
}

// patch for 0x42512E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425138_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_42512E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"MOV R3, R6\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425138_thumb)
		);
}

// patch for 0x425172
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425182_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_425172()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_84 */"-0x84]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R0, R4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425182_thumb)
		);
}

// patch for 0x4251CC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4251D4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4251CC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4251D4_thumb)
		);
}

// patch for 0x42520E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42521A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_42520E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_84 */"-0x84]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42521A_thumb)
		);
}

// patch for 0x42521C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425224_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_42521C()
{
	__asm(
	".thumb\n"
		"ADD R0, R4, R0\n"
		"ADD R0, R2, R0,LSL#3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425224_thumb)
		);
}

// patch for 0x425248
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425252 = 0;
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425250_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_425248()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R2, =("/* _ZN6CWorld17ms_aRepeatSectorsE_ptr */"0x6771E4 - 0x425254)\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425252)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425250_thumb)
		);
}

// patch for 0x4252C0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4252C8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4252C0()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R9, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4252C8_thumb)
		);
}

// patch for 0x4252EE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4252F8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4252EE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		"ADD R0, SP, #0xD0+"/* var_54 */"-0x54\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4252F8_thumb)
		);
}

// patch for 0x425330
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42533C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_425330()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_84 */"-0x84]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42533C_thumb)
		);
}

// patch for 0x42533E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425348_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_42533E()
{
	__asm(
	".thumb\n"
		"ADD R0, R9, R0\n"
		"ADD R0, R2, R0,LSL#3\n"
		"MOV R2, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425348_thumb)
		);
}

// patch for 0x425374
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42537C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_425374()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42537C_thumb)
		);
}

// patch for 0x4253B6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4253C2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4253B6()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_8C */"-0x8C]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4253C2_thumb)
		);
}

// patch for 0x4253C4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4253CC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4253C4()
{
	__asm(
	".thumb\n"
		"ADD R0, R9, R0\n"
		"ADD R0, R2, R0,LSL#3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4253CC_thumb)
		);
}

// patch for 0x4253E2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42526E_thumb = 0;	// loc_42526E
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4253EE_thumb = 0;	// loc_4253EE
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4253E2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R1, [SP,#0xD0+"/* var_98 */"-0x98]\n"
		"ADDS R0, R6, #1\n"
		"CMP R0, R1\n"
		"BNE 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4253EE_thumb)

		// Branches
		"1:\n"	// loc_42526E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42526E_thumb)
		);
}

// patch for 0x4253F6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425402_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4253F6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		"AND R9, R1, #0xF\n"
		"IT GE\n"
		"MOVGE R4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425402_thumb)
		);
}

// patch for 0x42543E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425448_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_42543E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		"ADD R0, SP, #0xD0+"/* var_54 */"-0x54\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425448_thumb)
		);
}

// patch for 0x425480
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42548C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_425480()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_84 */"-0x84]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42548C_thumb)
		);
}

// patch for 0x42548E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425498_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_42548E()
{
	__asm(
	".thumb\n"
		"ADD R0, R4, R0\n"
		"ADD R0, R2, R0,LSL#3\n"
		"MOV R2, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425498_thumb)
		);
}

// patch for 0x4254E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4254E8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4254E0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"MOV R3, R11\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4254E8_thumb)
		);
}

// patch for 0x425524
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425534_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_425524()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_84 */"-0x84]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"ADD R0, R4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425534_thumb)
		);
}

// patch for 0x42555C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425564_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_42555C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R2, =("/* _ZN6CWorld17ms_aRepeatSectorsE_ptr */"0x6771E4 - 0x42556A)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425564_thumb)
		);
}

// patch for 0x4255CE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4255D8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4255CE()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R4, R8\n"
		"AND R8, R5, #0xF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4255D8_thumb)
		);
}

// patch for 0x4255FE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425608_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4255FE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		"ADD R0, SP, #0xD0+"/* var_54 */"-0x54\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425608_thumb)
		);
}

// patch for 0x425640
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42564C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_425640()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_84 */"-0x84]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42564C_thumb)
		);
}

// patch for 0x42564E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425658_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_42564E()
{
	__asm(
	".thumb\n"
		"ADD R0, R4, R0\n"
		"ADD R0, R2, R0,LSL#3\n"
		"MOV R2, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425658_thumb)
		);
}

// patch for 0x425686
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425690_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_425686()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		"ADD R0, SP, #0xD0+"/* var_54 */"-0x54\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425690_thumb)
		);
}

// patch for 0x4256C8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4256D4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4256C8()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_8C */"-0x8C]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4256D4_thumb)
		);
}

// patch for 0x4256D6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4256E0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4256D6()
{
	__asm(
	".thumb\n"
		"ADD R0, R4, R0\n"
		"ADD R0, R2, R0,LSL#3\n"
		"MOV R2, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4256E0_thumb)
		);
}

// patch for 0x4256F6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425700_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4256F6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R1, [SP,#0xD0+"/* var_98 */"-0x98]\n"
		"SUBS R0, R6, #1\n"
		"CMP R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425700_thumb)
		);
}

// patch for 0x42570C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425714_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_42570C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		"AND R6, R1, #0xF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425714_thumb)
		);
}

// patch for 0x425752
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42575C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_425752()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		"ADD R0, SP, #0xD0+"/* var_54 */"-0x54\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42575C_thumb)
		);
}

// patch for 0x425794
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4257A0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_425794()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_84 */"-0x84]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4257A0_thumb)
		);
}

// patch for 0x4257A2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4257AC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4257A2()
{
	__asm(
	".thumb\n"
		"ADD R0, R4, R0\n"
		"ADD R0, R2, R0,LSL#3\n"
		"MOV R2, R9\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4257AC_thumb)
		);
}

// patch for 0x4257EE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4257F8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4257EE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		"ADD R0, SP, #0xD0+"/* var_54 */"-0x54\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4257F8_thumb)
		);
}

// patch for 0x425830
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42583C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_425830()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_84 */"-0x84]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_42583C_thumb)
		);
}

// patch for 0x42583E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425848_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_42583E()
{
	__asm(
	".thumb\n"
		"ADD R0, R4, R0\n"
		"ADD R0, R2, R0,LSL#3\n"
		"MOV R2, R11\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425848_thumb)
		);
}

// patch for 0x42588A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425894_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_42588A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDR R0, [R7,#"/* arg_1C */"0x24]\n"
		"STR R0, [SP,#0xD0+"/* var_AC */"-0xAC]\n"
		"ADD R0, SP, #0xD0+"/* var_54 */"-0x54\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_425894_thumb)
		);
}

// patch for 0x4258CC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4258D8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4258CC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R2\n"
		"LDR R2, [SP,#0xD0+"/* var_84 */"-0x84]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4258D8_thumb)
		);
}

// patch for 0x4258DA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4258E4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessLineOfSight_4258DA()
{
	__asm(
	".thumb\n"
		"ADD R0, R4, R0\n"
		"ADD R0, R2, R0,LSL#3\n"
		"MOV R2, R9\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessLineOfSight_4258E4_thumb)
		);
}

// patch for 0x4261FC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessVerticalLine_426208_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessVerticalLine_4261FC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"VDIV.F32 S0, S18, S16\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessVerticalLine_426208_thumb)
		);
}

// patch for 0x426272
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessVerticalLine_426280_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessVerticalLine_426272()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"ADD R3, R3, R3,LSL#1\n"
		"ADD R1, R1, R3,LSL#2\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessVerticalLine_426280_thumb)
		);
}

// patch for 0x42628A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessVerticalLine_426298_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessVerticalLine_42628A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R6, R3\n"
		"MOV R3, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimension)
		"ADD R0, R0, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessVerticalLine_426298_thumb)
		);
}

// patch for 0x426422
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessVerticalLine_FillGlobeColPoints_42642E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessVerticalLine_FillGlobeColPoints_426422()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"VDIV.F32 S0, S18, S16\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessVerticalLine_FillGlobeColPoints_42642E_thumb)
		);
}

// patch for 0x426494
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessVerticalLine_FillGlobeColPoints_4264A2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessVerticalLine_FillGlobeColPoints_426494()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"ADD R3, R3, R3,LSL#1\n"
		"ADD R1, R1, R3,LSL#2\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessVerticalLine_FillGlobeColPoints_4264A2_thumb)
		);
}

// patch for 0x4264AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ProcessVerticalLine_FillGlobeColPoints_4264BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ProcessVerticalLine_FillGlobeColPoints_4264AC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R11, R3\n"
		"MOV R3, R11\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimension)
		"ADD R0, R0, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ProcessVerticalLine_FillGlobeColPoints_4264BC_thumb)
		);
}

// patch for 0x426894
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__TriggerExplosion_4268A2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__TriggerExplosion_426894()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		"MOV R11, R3\n"
		"VSUB.F32 S0, S16, S20\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__TriggerExplosion_4268A2_thumb)
		);
}

// patch for 0x427522
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__CastShadow_42752E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__CastShadow_427522()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"VMOV S0, R0\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__CastShadow_42752E_thumb)
		);
}

// patch for 0x42759C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__CastShadow_4275A4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__CastShadow_42759C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R11, iNumberOfWorldSectorsPerDimension)
		"VCVT.S32.F32 S0, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__CastShadow_4275A4_thumb)
		);
}

// patch for 0x4275C2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__CastShadow_4275CC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__CastShadow_4275C2()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimension)
		"IT GE\n"
		"MOVGE R8, R11\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__CastShadow_4275CC_thumb)
		);
}

// patch for 0x42760C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__CastShadow_427614_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__CastShadow_42760C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R10, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__CastShadow_427614_thumb)
		);
}

// patch for 0x427618
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__CastShadow_427620_thumb = 0;	// loc_427620
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__CastShadow_427618()
{
	__asm(
	".thumb\n"
		"MOV R3, R9\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__CastShadow_427620_thumb)
		);
}

// patch for 0x427620
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__CastShadow_42762A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__CastShadow_427620()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R6, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__CastShadow_42762A_thumb)
		);
}

// patch for 0x42843C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__ClearScanCodes_42841A_thumb = 0;	// loc_42841A
	uintptr_t Address_GTA_SA_2_00_CWorld__ClearScanCodes_428444_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__ClearScanCodes_42843C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iTotalNumberOfWorldSectors)
		"BNE 1f\n"
		"LDR R1, =("/* _ZN6CWorld17ms_aRepeatSectorsE_ptr */"0x6771E4 - 0x42844A)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ClearScanCodes_428444_thumb)

		// Branches
		"1:\n"	// loc_42841A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__ClearScanCodes_42841A_thumb)
		);
}

// patch for 0x42859C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsInRange_4285AA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsInRange_42859C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		"MOV R5, R2\n"
		"VSUB.F32 S0, S18, S16\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsInRange_4285AA_thumb)
		);
}

// patch for 0x4286DA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsInRange_4286E4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsInRange_4286DA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"CMP R1, #0\n"
		"IT GT\n"
		"MOVGT R0, R1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsInRange_4286E4_thumb)
		);
}

// patch for 0x4286E8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsInRange_4286F0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsInRange_4286E8()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"STR R0, [SP,#0x88+"/* var_64 */"-0x64]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsInRange_4286F0_thumb)
		);
}

// patch for 0x42870A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsInRange_428714_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsInRange_42870A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R2, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsInRange_428714_thumb)
		);
}

// patch for 0x428B18
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsOfTypeInRange_428B26_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsOfTypeInRange_428B18()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		"MOV R8, R3\n"
		"VSUB.F32 S0, S18, S16\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsOfTypeInRange_428B26_thumb)
		);
}

// patch for 0x428C64
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsOfTypeInRange_428C6E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsOfTypeInRange_428C64()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"CMP R1, #0\n"
		"IT GT\n"
		"MOVGT R0, R1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsOfTypeInRange_428C6E_thumb)
		);
}

// patch for 0x428C72
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsOfTypeInRange_428C7C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsOfTypeInRange_428C72()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"STR R0, [SP,#0x90+"/* var_68 */"-0x68]\n"
		"LSLS R0, R1, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsOfTypeInRange_428C7C_thumb)
		);
}

// patch for 0x428C96
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsOfTypeInRange_428CA0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsOfTypeInRange_428C96()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOV R4, R9\n"
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsOfTypeInRange_428CA0_thumb)
		);
}

// patch for 0x4290D8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindLodOfTypeInRange_4290E2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindLodOfTypeInRange_4290D8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S8, fWorldLODsectorSize)
		"MOV R4, R3\n"
		"VADD.F32 S4, S2, S16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindLodOfTypeInRange_4290E2_thumb)
		);
}

// patch for 0x42910C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindLodOfTypeInRange_429114_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindLodOfTypeInRange_42910C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S8, fNumberOfWorldLODsectorsPerDimensionHalf)
		"VADD.F32 S4, S4, S8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindLodOfTypeInRange_429114_thumb)
		);
}

// patch for 0x429192
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindLodOfTypeInRange_42919C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindLodOfTypeInRange_429192()
{
	__asm(
	".thumb\n"
		"LDR R9, [SP,#0x50+"/* var_4C */"-0x4C]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldLODsectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindLodOfTypeInRange_42919C_thumb)
		);
}

// patch for 0x429294
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsKindaColliding_4292A2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsKindaColliding_429294()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		"MOV R9, R2\n"
		"VSUB.F32 S0, S18, S16\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsKindaColliding_4292A2_thumb)
		);
}

// patch for 0x429410
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsKindaColliding_42941A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsKindaColliding_429410()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"CMP R1, #0\n"
		"IT GT\n"
		"MOVGT R0, R1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsKindaColliding_42941A_thumb)
		);
}

// patch for 0x42941E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsKindaColliding_429428_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsKindaColliding_42941E()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"STR R0, [SP,#0xB8+"/* var_94 */"-0x94]\n"
		"LSLS R0, R1, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsKindaColliding_429428_thumb)
		);
}

// patch for 0x429442
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsKindaColliding_42944C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsKindaColliding_429442()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOV R6, R10\n"
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsKindaColliding_42944C_thumb)
		);
}

// patch for 0x429900
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_42990A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_429900()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"MOV R8, R2\n"
		"VLDR S0, [R4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_42990A_thumb)
		);
}

// patch for 0x42990C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_429914_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_42990C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S20, fNumberOfWorldSectorsPerDimensionHalf)
		"VDIV.F32 S0, S0, S16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_429914_thumb)
		);
}

// patch for 0x429A00
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_429A0A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_429A00()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"CMP R1, #0\n"
		"IT GT\n"
		"MOVGT R0, R1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_429A0A_thumb)
		);
}

// patch for 0x429A12
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_429A1C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_429A12()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"STR R0, [SP,#0x78+"/* var_4C */"-0x4C]\n"
		"LSLS R0, R1, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_429A1C_thumb)
		);
}

// patch for 0x429A2C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_429A34_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_429A2C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"AND R5, R10, #0xF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingCube_429A34_thumb)
		);
}

// patch for 0x429C44
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingAngledCollisionBox_429C50_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsIntersectingAngledCollisionBox_429C44()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"VMOV S0, R3\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingAngledCollisionBox_429C50_thumb)
		);
}

// patch for 0x429D48
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingAngledCollisionBox_429D52_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsIntersectingAngledCollisionBox_429D48()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"CMP R1, #0\n"
		"IT GT\n"
		"MOVGT R0, R1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingAngledCollisionBox_429D52_thumb)
		);
}

// patch for 0x429D5A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingAngledCollisionBox_429D64_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsIntersectingAngledCollisionBox_429D5A()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"STR R0, [SP,#0x68+"/* var_38 */"-0x38]\n"
		"LSLS R0, R1, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingAngledCollisionBox_429D64_thumb)
		);
}

// patch for 0x429D74
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingAngledCollisionBox_429D7C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindObjectsIntersectingAngledCollisionBox_429D74()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"AND R4, R10, #0xF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindObjectsIntersectingAngledCollisionBox_429D7C_thumb)
		);
}

// patch for 0x429F96
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindMissionEntitiesIntersectingCube_429FA4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindMissionEntitiesIntersectingCube_429F96()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"MOV R6, R1\n"
		"VLDR S0, [R4]\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S20, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindMissionEntitiesIntersectingCube_429FA4_thumb)
		);
}

// patch for 0x42A294
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindNearestObjectOfType_42A2A2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindNearestObjectOfType_42A294()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		"MOV R9, R3\n"
		"VSUB.F32 S0, S18, S16\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindNearestObjectOfType_42A2A2_thumb)
		);
}

// patch for 0x42A39E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindNearestObjectOfType_42A3AC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindNearestObjectOfType_42A39E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R2, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindNearestObjectOfType_42A3AC_thumb)
		);
}

// patch for 0x42A3C0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindNearestObjectOfType_42A3C8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindNearestObjectOfType_42A3C0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GT\n"
		"MOVGT R2, LR\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindNearestObjectOfType_42A3C8_thumb)
		);
}

// patch for 0x42A3CC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__FindNearestObjectOfType_42A3D4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__FindNearestObjectOfType_42A3CC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R2, R3\n"
		"LDR R3, [SP,#0x78+"/* var_54 */"-0x54]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__FindNearestObjectOfType_42A3D4_thumb)
		);
}

// patch for 0x42AE4C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__TestSphereAgainstWorld_42AE58_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__TestSphereAgainstWorld_42AE4C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S20, fWorldSectorSize)
		"VMOV S18, R0\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__TestSphereAgainstWorld_42AE58_thumb)
		);
}

// patch for 0x42AF50
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__TestSphereAgainstWorld_42AF5A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__TestSphereAgainstWorld_42AF50()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GT\n"
		"MOVGT R0, R1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__TestSphereAgainstWorld_42AF5A_thumb)
		);
}

// patch for 0x42AF62
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__TestSphereAgainstWorld_42AF6C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__TestSphereAgainstWorld_42AF62()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"STR R0, [SP,#0x80+"/* var_4C */"-0x4C]\n"
		"LSLS R0, R1, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__TestSphereAgainstWorld_42AF6C_thumb)
		);
}

// patch for 0x42AF7C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__TestSphereAgainstWorld_42AF84_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__TestSphereAgainstWorld_42AF7C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__TestSphereAgainstWorld_42AF84_thumb)
		);
}

// patch for 0x42BC06
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__RemoveStaticObjects_42BB76_thumb = 0;	// loc_42BB76
	uintptr_t Address_GTA_SA_2_00_CWorld__RemoveStaticObjects_42BC12_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__RemoveStaticObjects_42BC06()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iTotalNumberOfWorldSectors)
		"BNE 1f\n"
		"LDR R0, =("/* _ZN6CWorld17ms_aRepeatSectorsE_ptr */"0x6771E4 - 0x42BC16)\n"
		"MOV R9, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__RemoveStaticObjects_42BC12_thumb)

		// Branches
		"1:\n"	// loc_42BB76
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__RemoveStaticObjects_42BB76_thumb)
		);
}

// patch for 0x42BCE4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__TestForUnusedModels_42BCEE_thumb = 0;	// loc_42BCEE
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__TestForUnusedModels_42BCE4()
{
	__asm(
	".thumb\n"
		"MOV R1, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimension)
		"MOVS R2, #0\n"
		"MOV R9, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__TestForUnusedModels_42BCEE_thumb)
		);
}

// patch for 0x42BD46
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__TestForUnusedModels_42BD52_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__TestForUnusedModels_42BD46()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimension)
		"BNE 1f\n"
		"ADD R12, R12, #1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R12, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__TestForUnusedModels_42BD52_thumb)

		// Branches
		"1:\n"	// loc_42BCEE
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__TestForUnusedModels_42BCEE_thumb)
		);
}

// patch for 0x42C438
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__CallOffChaseForArea_42C444_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__CallOffChaseForArea_42C438()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S26, fWorldSectorSize)
		"VMOV S2, R0\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S28, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__CallOffChaseForArea_42C444_thumb)
		);
}

// patch for 0x4ACA08
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACA10_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACA08()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		"VLDR S20, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACA10_thumb)
		);
}

// patch for 0x4ACA72
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACA7E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACA72()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VMOV S2, R6\n"
		"MOVS R2, #0\n"
		"VCVT.S32.F32 S6, S26\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACA7E_thumb)
		);
}

// patch for 0x4ACA9A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACAA4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACA9A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACAA4_thumb)
		);
}

// patch for 0x4ACAD4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACADC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACAD4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACADC_thumb)
		);
}

// patch for 0x4ACAE0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACAE8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACAE0()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"MOV R8, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACAE8_thumb)
		);
}

// patch for 0x4ACAEE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACAFA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACAEE()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R10, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPedDebugVisualiser__VisualiseNearbyAttractors_4ACAFA_thumb)
		);
}

// patch for 0x4BA76A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntityScanner__ScanForEntitiesInRange_4BA776_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntityScanner__ScanForEntitiesInRange_4BA76A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		"VSUB.F32 S0, S18, S16\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntityScanner__ScanForEntitiesInRange_4BA776_thumb)
		);
}

// patch for 0x4BA7BA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntityScanner__ScanForEntitiesInRange_4BA7C6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntityScanner__ScanForEntitiesInRange_4BA7BA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOVS R1, #0\n"
		"VCVT.S32.F32 S0, S0\n"
		"VMOV R0, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntityScanner__ScanForEntitiesInRange_4BA7C6_thumb)
		);
}

// patch for 0x4BA7CA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntityScanner__ScanForEntitiesInRange_4BA7D6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntityScanner__ScanForEntitiesInRange_4BA7CA()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R5\n"
		"STR R0, [SP,#0x140+"/* var_11C */"-0x11C]\n"
		"VCVT.S32.F32 S0, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntityScanner__ScanForEntitiesInRange_4BA7D6_thumb)
		);
}

// patch for 0x4BA820
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CEntityScanner__ScanForEntitiesInRange_4BA82A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CEntityScanner__ScanForEntitiesInRange_4BA820()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R5, R1\n"
		"MOV R1, #0xFFFF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CEntityScanner__ScanForEntitiesInRange_4BA82A_thumb)
		);
}

// patch for 0x4BB064
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB070_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB064()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		"STRD R2, R2, [R4,#0x7C]\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB070_thumb)
		);
}

// patch for 0x4BB10C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB116_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB10C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VCVT.S32.F32 S4, S16\n"
		"VCVT.S32.F32 S6, S20\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB116_thumb)
		);
}

// patch for 0x4BB12E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB13A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB12E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB13A_thumb)
		);
}

// patch for 0x4BB172
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB186_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB172()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R1\n"
		"LDR R10, [SP,#0x90+"/* var_7C */"-0x7C]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"MOV R9, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB186_thumb)
		);
}

// patch for 0x4BB18A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB196_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB18A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R10, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAttractorScanner__ScanForAttractorsInRange_4BB196_thumb)
		);
}

// patch for 0x4C1F7C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CInterestingEvents__ScanForNearbyEntities_4C1F84_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CInterestingEvents__ScanForNearbyEntities_4C1F7C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CInterestingEvents__ScanForNearbyEntities_4C1F84_thumb)
		);
}

// patch for 0x4C1FEC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CInterestingEvents__ScanForNearbyEntities_4C1FF4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CInterestingEvents__ScanForNearbyEntities_4C1FEC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VCVT.S32.F32 S0, S0\n"
		"LDRH R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CInterestingEvents__ScanForNearbyEntities_4C1FF4_thumb)
		);
}

// patch for 0x4C2004
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CInterestingEvents__ScanForNearbyEntities_4C200C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CInterestingEvents__ScanForNearbyEntities_4C2004()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R2\n"
		"STR R1, [SP,#0x78+"/* var_78 */"-0x78]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CInterestingEvents__ScanForNearbyEntities_4C200C_thumb)
		);
}

// patch for 0x4C2010
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CInterestingEvents__ScanForNearbyEntities_4C201A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CInterestingEvents__ScanForNearbyEntities_4C2010()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R2, R1\n"
		"VMOV R1, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CInterestingEvents__ScanForNearbyEntities_4C201A_thumb)
		);
}

// patch for 0x4CEA08
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPopulation__TestSafeForRealObject_4CEA10_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPopulation__TestSafeForRealObject_4CEA08()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S26, fNumberOfWorldSectorsPerDimensionHalf)
		"VDIV.F32 S0, S0, S24\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPopulation__TestSafeForRealObject_4CEA10_thumb)
		);
}

// patch for 0x4CEA6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPopulation__TestSafeForRealObject_4CEA72 = 0;
	uintptr_t Address_GTA_SA_2_00_CPopulation__TestSafeForRealObject_4CEA74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPopulation__TestSafeForRealObject_4CEA6C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimension)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CPopulation__TestSafeForRealObject_4CEA72)
		"VCVT.S32.F32 S6, S28\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPopulation__TestSafeForRealObject_4CEA74_thumb)
		);
}

// patch for 0x4CEA92
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPopulation__TestSafeForRealObject_4CEA9E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPopulation__TestSafeForRealObject_4CEA92()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimension)
		"IT GE\n"
		"MOVGE R4, R2\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimension)
		"IT LT\n"
		"MOVLT R2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPopulation__TestSafeForRealObject_4CEA9E_thumb)
		);
}

// patch for 0x4D5376
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCover__Update_4D5382_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCover__Update_4D5376()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		"VADD.F32 S2, S16, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCover__Update_4D5382_thumb)
		);
}

// patch for 0x4D5414
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCover__Update_4D541C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCover__Update_4D5414()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		"CMP R0, #0\n"
		"IT GT\n"
		"MOVGT R4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCover__Update_4D541C_thumb)
		);
}

// patch for 0x4D5424
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCover__Update_4D542C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCover__Update_4D5424()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R5\n"
		"STR R0, [SP,#0x98+"/* var_74 */"-0x74]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCover__Update_4D542C_thumb)
		);
}

// patch for 0x4D5430
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCover__Update_4D543A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCover__Update_4D5430()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R5, R0\n"
		"MOV R0, #0xFFFF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCover__Update_4D543A_thumb)
		);
}

// patch for 0x4D548A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCover__Update_4D549A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCover__Update_4D548A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R1\n"
		"LDR R5, [SP,#0x98+"/* var_80 */"-0x80]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCover__Update_4D549A_thumb)
		);
}

// patch for 0x4D549C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCover__Update_4D54A6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCover__Update_4D549C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCover__Update_4D54A6_thumb)
		);
}

// patch for 0x52F7C2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskSimpleClimb__ScanToGrab_52F7CE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskSimpleClimb__ScanToGrab_52F7C2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		"VSUB.F32 S0, S16, S20\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimpleClimb__ScanToGrab_52F7CE_thumb)
		);
}

// patch for 0x52F8F2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskSimpleClimb__ScanToGrab_52F902_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskSimpleClimb__ScanToGrab_52F8F2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"MOV R9, R2\n"
		"IT GE\n"
		"MOVGE R0, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimpleClimb__ScanToGrab_52F902_thumb)
		);
}

// patch for 0x52F912
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskSimpleClimb__ScanToGrab_52F91C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskSimpleClimb__ScanToGrab_52F912()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"STR R0, [SP,#0x108+"/* var_104 */"-0x104]\n"
		"MOV R3, R8\n"
		"LDR R0, [R7,#"/* arg_4 */"0xC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimpleClimb__ScanToGrab_52F91C_thumb)
		);
}

// patch for 0x52F92E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskSimpleClimb__ScanToGrab_52F938_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskSimpleClimb__ScanToGrab_52F92E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R1\n"
		"LDR R1, [SP,#0x108+"/* var_BC */"-0xBC]\n"
		"LDR R6, [SP,#0x108+"/* var_AC */"-0xAC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskSimpleClimb__ScanToGrab_52F938_thumb)
		);
}

// patch for 0x558A2E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__RcbanditCheckHitWheels_558A3E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__RcbanditCheckHitWheels_558A2E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"VLDR S2, [R1]\n"
		"VLDR S4, [R1,#4]\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__RcbanditCheckHitWheels_558A3E_thumb)
		);
}

// patch for 0x558AAE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__RcbanditCheckHitWheels_558AB8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__RcbanditCheckHitWheels_558AAE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R11, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VCVT.S32.F32 S0, S0\n"
		"LDRH R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__RcbanditCheckHitWheels_558AB8_thumb)
		);
}

// patch for 0x558AD2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__RcbanditCheckHitWheels_558ADE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__RcbanditCheckHitWheels_558AD2()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R6, R11\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R11, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__RcbanditCheckHitWheels_558ADE_thumb)
		);
}

// patch for 0x55DB80
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPed__DeadPedMakesTyresBloody_55DB88_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPed__DeadPedMakesTyresBloody_55DB80()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"ADD R1, R0, #0x30\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPed__DeadPedMakesTyresBloody_55DB88_thumb)
		);
}

// patch for 0x55DB8E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPed__DeadPedMakesTyresBloody_55DB9A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPed__DeadPedMakesTyresBloody_55DB8E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWorldSectorsPerDimensionHalf)
		"VLDR S2, [R1]\n"
		"VLDR S4, [R1,#4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPed__DeadPedMakesTyresBloody_55DB9A_thumb)
		);
}

// patch for 0x55DC1C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPed__DeadPedMakesTyresBloody_55DC26_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPed__DeadPedMakesTyresBloody_55DC1C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VCVT.S32.F32 S2, S2\n"
		"VMOV R1, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPed__DeadPedMakesTyresBloody_55DC26_thumb)
		);
}

// patch for 0x55DC2A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPed__DeadPedMakesTyresBloody_55DC38_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPed__DeadPedMakesTyresBloody_55DC2A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R5\n"
		"STR R1, [SP,#0x50+"/* var_4C */"-0x4C]\n"
		"VMOV R1, S6\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPed__DeadPedMakesTyresBloody_55DC38_thumb)
		);
}

// patch for 0x57ED0C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57ED18_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57ED0C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"VMOV S2, R0\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57ED18_thumb)
		);
}

// patch for 0x57ED88
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57ED92 = 0;
	uintptr_t Address_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57ED90_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57ED88()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VCVT.S32.F32 S0, S0\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57ED92)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57ED90_thumb)
		);
}

// patch for 0x57EDA0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57EDA8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57EDA0()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R2\n"
		"STR R1, [SP,#0x88+"/* var_88 */"-0x88]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57EDA8_thumb)
		);
}

// patch for 0x57EDAC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57EDB6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57EDAC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R2, R1\n"
		"VMOV R1, S6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_MarkSurroundingEntitiesForCollisionWithTrain_57EDB6_thumb)
		);
}

// patch for 0x587C28
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicle__DoBladeCollision_587C34_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicle__DoBladeCollision_587C28()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fWorldSectorSize)
		"VSUB.F32 S0, S18, S16\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicle__DoBladeCollision_587C34_thumb)
		);
}

// patch for 0x587CA4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicle__DoBladeCollision_587CAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicle__DoBladeCollision_587CA4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimension)
		"VCVT.S32.F32 S0, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicle__DoBladeCollision_587CAC_thumb)
		);
}

// patch for 0x587CBA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicle__DoBladeCollision_587CC8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicle__DoBladeCollision_587CBA()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimension)
		"IT GE\n"
		"MOVGE R1, R8\n"
		"STR R1, [SP,#0xA0+"/* var_94 */"-0x94]\n"
		"VMOV R1, S0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicle__DoBladeCollision_587CC8_thumb)
		);
}

// patch for 0x587D32
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicle__DoBladeCollision_587D44_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicle__DoBladeCollision_587D32()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R1\n"
		"LDR R9, [SP,#0xA0+"/* var_90 */"-0x90]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicle__DoBladeCollision_587D44_thumb)
		);
}

// patch for 0x587D4C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CVehicle__DoBladeCollision_587D54_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CVehicle__DoBladeCollision_587D4C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CVehicle__DoBladeCollision_587D54_thumb)
		);
}

// patch for 0x59BCF0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BCF8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BCF0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S20, fWorldSectorSize)
		"VLDR S16, [R4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BCF8_thumb)
		);
}

// patch for 0x59BCFA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BD04_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BCFA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fNumberOfWorldSectorsPerDimensionHalf)
		"MOV R9, R2\n"
		"VDIV.F32 S0, S16, S20\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BD04_thumb)
		);
}

// patch for 0x59BD1E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BDB0_thumb = 0;	// loc_59BDB0
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BD2A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BD1E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"BHI 1f\n"
		"VLDR S18, [R4,#4]\n"
		"VDIV.F32 S0, S18, S20\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BD2A_thumb)

		// Branches
		"1:\n"	// loc_59BDB0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BDB0_thumb)
		);
}

// patch for 0x59BD44
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BDB2_thumb = 0;	// loc_59BDB2
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BD4C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BD44()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"BHI 1f\n"
		"VLDR S2, 101f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BD4C_thumb)

		// Branches
		"1:\n"	// loc_59BDB2
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__GetGroundLevel_WS_59BDB2_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, 0.0)
		);
}

// patch for 0x59BDD4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__IsLocationOutOfWorldBounds_WS_59BDE2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__IsLocationOutOfWorldBounds_WS_59BDD4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		"MOV R4, R1\n"
		"VLDR S0, [R0]\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S20, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__IsLocationOutOfWorldBounds_WS_59BDE2_thumb)
		);
}

// patch for 0x5AD0A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD0AC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD0A0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S20, fWorldSectorSize)
		"VMOV S16, R0\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S22, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD0AC_thumb)
		);
}

// patch for 0x5AD116
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD11C = 0;
	uintptr_t Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD122_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD116()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD11C)
		"VMOV S2, R4\n"
		"VCVT.S32.F32 S6, S6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD122_thumb)
		);
}

// patch for 0x5AD144
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD14C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD144()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R4, R2\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD14C_thumb)
		);
}

// patch for 0x5AD1CC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD1D6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD1CC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD1D6_thumb)
		);
}

// patch for 0x5AD1D8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD1E0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD1D8()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"STR R0, [SP,#0x88+"/* var_64 */"-0x64]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD1E0_thumb)
		);
}

// patch for 0x5AD1EC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD1F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD1EC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimensionMinusOne)
		"ORR R0, R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD1F4_thumb)
		);
}

// patch for 0x5AD1FE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD208_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD1FE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R1, R8\n"
		"LDR R6, [R0,#8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGlass__HasGlassBeenShatteredAtCoors_5AD208_thumb)
		);
}

// patch for 0x5B900C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B9014 = 0;
	uintptr_t Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B9016_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B900C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S24, fWorldSectorSize)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B9014)
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S26, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B9016_thumb)
		);
}

// patch for 0x5B90C6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B90D0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B90C6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R10, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VCVT.S32.F32 S4, S26\n"
		"MOVS R1, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B90D0_thumb)
		);
}

// patch for 0x5B90D8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B90E0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B90D8()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R0, R10\n"
		"STR R0, [SP,#0xD0+"/* var_94 */"-0x94]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B90E0_thumb)
		);
}

// patch for 0x5B90E4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B90EE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B90E4()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R10, R0\n"
		"VMOV R0, S6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B90EE_thumb)
		);
}

// patch for 0x5B9186
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B9198_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B9186()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R1\n"
		"LDR R8, [SP,#0xD0+"/* var_90 */"-0x90]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B9198_thumb)
		);
}

// patch for 0x5B91A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B91A8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B91A0()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R8, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VLDR S0, [LR]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B91A8_thumb)
		);
}

// patch for 0x5B91E6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B91F2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B91E6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"VSTR S16, [SP,#0xD0+"/* var_D0 */"-0xD0]\n"
		"IT LT\n"
		"MOVLT R0, R8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CShadows__GeneratePolysForStaticShadow_5B91F2_thumb)
		);
}

// patch for 0x5BA7F4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CShadows__RenderStoredShadows_5BA7FC = 0;
	uintptr_t Address_GTA_SA_2_00_CShadows__RenderStoredShadows_5BA800_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CShadows__RenderStoredShadows_5BA7F4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWorldSectorSize)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CShadows__RenderStoredShadows_5BA7FC)
		"LDR R2, [R2]\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWorldSectorsPerDimensionHalf)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CShadows__RenderStoredShadows_5BA800_thumb)
		);
}

// patch for 0x5BAA22
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CShadows__RenderStoredShadows_5BAA2E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CShadows__RenderStoredShadows_5BAA22()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"LDRH R0, [R0]\n"
		"VCVT.S32.F32 S0, S0\n"
		"VCVT.S32.F32 S6, S28\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CShadows__RenderStoredShadows_5BAA2E_thumb)
		);
}

// patch for 0x5BAA32
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CShadows__RenderStoredShadows_5BAA40_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CShadows__RenderStoredShadows_5BAA32()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R2, R1\n"
		"STR R2, [SP,#0x150+"/* var_B0 */"-0xB0]\n"
		"VMOV R2, S0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CShadows__RenderStoredShadows_5BAA40_thumb)
		);
}

// patch for 0x5BAB1E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CShadows__RenderStoredShadows_5BAB2E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CShadows__RenderStoredShadows_5BAB1E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimension)
		"MOV R8, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CShadows__RenderStoredShadows_5BAB2E_thumb)
		);
}

// patch for 0x5BAB32
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CShadows__RenderStoredShadows_5BAB3E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CShadows__RenderStoredShadows_5BAB32()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iNumberOfWorldSectorsPerDimensionMinusOne)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWorldSectorsPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R11\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CShadows__RenderStoredShadows_5BAB3E_thumb)
		);
}

// patch for 0x5D709E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CBulletInfo__Update_5D70A8 = 0;
	uintptr_t Address_GTA_SA_2_00_CBulletInfo__Update_5D70A8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CBulletInfo__Update_5D709E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fWorldMapMinCoord)
		"LDR R0, [R0]\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R6, Address_GTA_SA_2_00_CBulletInfo__Update_5D70A8)
		"STR R0, [SP,#0x140+"/* var_C4 */"-0xC4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CBulletInfo__Update_5D70A8_thumb)
		);
}

// patch for 0x5D70AE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CBulletInfo__Update_5D70B6 = 0;
	uintptr_t Address_GTA_SA_2_00_CBulletInfo__Update_5D70B8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CBulletInfo__Update_5D70AE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S20, fWorldMapMaxCoord)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CBulletInfo__Update_5D70B6)
		"VLDR S26, 101f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CBulletInfo__Update_5D70B8_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, 180.0)
		);
}


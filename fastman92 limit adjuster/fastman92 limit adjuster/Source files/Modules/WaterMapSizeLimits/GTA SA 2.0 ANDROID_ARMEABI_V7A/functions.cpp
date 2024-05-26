// Compilation time: 2 seconds 711 ms

// patch for 0x5932FE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__WaterLevelInitialise_593308_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__WaterLevelInitialise_5932FE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, iTotalNumberOfWaterBlocksMultipliedBySizeOfBlock)
		"STR R4, [R6]\n"
		"STR R4, [R2]\n"
		"STR R4, [R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__WaterLevelInitialise_593308_thumb)
		);
}

// patch for 0x593CB4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593CBC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593CB4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S0, fWaterMapMinCoord)
		"VLDR S2, 101f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593CBC_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, 500.0)
		);
}

// patch for 0x593DA2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593DAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593DA2()
{
	__asm(
	".thumb\n"
		"MOV R2, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWaterBlocksPerDimensionMultipliedBySizeOfBlock)
		"LDR R0, [SP,#0x68+"/* var_50 */"-0x50]\n"
		"ADD R2, R0, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593DAC_thumb)
		);
}

// patch for 0x593EA8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593EB2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593EA8()
{
	__asm(
	".thumb\n"
		"MOV R2, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWaterBlocksPerDimensionMultipliedBySizeOfBlock)
		"LDR R0, [SP,#0x68+"/* var_60 */"-0x60]\n"
		"ADD R2, R0, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593EB2_thumb)
		);
}

// patch for 0x593FC8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593D7C_thumb = 0;	// loc_593D7C
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593FD0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593FC8()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWaterBlocksPerDimension)
		"BNE 1f\n"
		"LDR R1, [SP,#0x68+"/* var_40 */"-0x40]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593FD0_thumb)

		// Branches
		"1:\n"	// loc_593D7C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593D7C_thumb)
		);
}

// patch for 0x593FD2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593D60_thumb = 0;	// loc_593D60
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593FDE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593FD2()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWaterBlocksPerDimension)
		"BNE 1f\n"
		"ADD SP, SP, #0x4C\n"
		"POP {R8-R11}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593FDE_thumb)

		// Branches
		"1:\n"	// loc_593D60
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__FillQuadsAndTrianglesList_593D60_thumb)
		);
}

// patch for 0x594314
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__AddToQuadsAndTrianglesList_59431C = 0;
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__AddToQuadsAndTrianglesList_594322_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__AddToQuadsAndTrianglesList_594314()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWaterBlocksPerDimensionMultipliedBySizeOfBlock)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R12, Address_GTA_SA_2_00_CWaterLevel__AddToQuadsAndTrianglesList_59431C)
		"LDR R12, [R12]\n"
		"ADD R0, R12, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__AddToQuadsAndTrianglesList_594322_thumb)
		);
}

// patch for 0x5943C2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__MarkQuadsAndPolysToBeRendered_5943CA = 0;
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__MarkQuadsAndPolysToBeRendered_5943CE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__MarkQuadsAndPolysToBeRendered_5943C2()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWaterBlocksPerDimensionMultipliedBySizeOfBlock)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CWaterLevel__MarkQuadsAndPolysToBeRendered_5943CA)
		"LDR R3, [R3]\n"
		"ADD R0, R3, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__MarkQuadsAndPolysToBeRendered_5943CE_thumb)
		);
}

// patch for 0x5958AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__GetWaterLevelNoWaves_5958B6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__GetWaterLevelNoWaves_5958AC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S18, fNumberOfWaterBlocksPerDimensionHalf)
		"MOV R8, R2\n"
		"VDIV.F32 S0, S0, S16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__GetWaterLevelNoWaves_5958B6_thumb)
		);
}

// patch for 0x5958F6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__GetWaterLevelNoWaves_595900_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__GetWaterLevelNoWaves_5958F6()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWaterBlocksPerDimensionMinusOne)
		"BHI 500f\n"
		"VMOV R1, S0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWaterBlocksPerDimension)
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__GetWaterLevelNoWaves_595900_thumb)
		);
}

// patch for 0x595928
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__GetWaterLevelNoWaves_595930 = 0;
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__GetWaterLevelNoWaves_595934_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__GetWaterLevelNoWaves_595928()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWaterBlocksPerDimensionMultipliedBySizeOfBlock)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CWaterLevel__GetWaterLevelNoWaves_595930)
		"LDR R2, [R2]\n"
		"ADD R0, R2, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__GetWaterLevelNoWaves_595934_thumb)
		);
}

// patch for 0x5960C6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__TestLineAgainstWater_5960D2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__TestLineAgainstWater_5960C6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S10, fNumberOfWaterBlocksPerDimensionHalf)
		"VADD.F32 S12, S12, S10\n"
		"VADD.F32 S9, S9, S10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__TestLineAgainstWater_5960D2_thumb)
		);
}

// patch for 0x596218
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__TestLineAgainstWater_596222_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__TestLineAgainstWater_596218()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfWaterBlocksPerDimensionMinusOne)
		"MOV R10, R0\n"
		"BHI 500f\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R10, iNumberOfWaterBlocksPerDimension)
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__TestLineAgainstWater_596222_thumb)
		);
}

// patch for 0x596248
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__TestLineAgainstWater_596252_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__TestLineAgainstWater_596248()
{
	__asm(
	".thumb\n"
		"MOV R0, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWaterBlocksPerDimensionMultipliedBySizeOfBlock)
		"LDR R1, [SP,#0x88+"/* var_4C */"-0x4C]\n"
		"ADD R0, R1, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__TestLineAgainstWater_596252_thumb)
		);
}

// patch for 0x5966A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__ScanThroughBlocks_5966B0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__ScanThroughBlocks_5966A8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S5, fNumberOfWaterBlocksPerDimensionHalf)
		"VLDR S2, [SP,#0x70+"/* var_44 */"-0x44]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__ScanThroughBlocks_5966B0_thumb)
		);
}

// patch for 0x596774
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__FindNearestWaterAndItsFlow_59677C = 0;
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__FindNearestWaterAndItsFlow_59677C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__FindNearestWaterAndItsFlow_596774()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S4, fWaterMapMaxCoord)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CWaterLevel__FindNearestWaterAndItsFlow_59677C)
		"LDR R1, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__FindNearestWaterAndItsFlow_59677C_thumb)
		);
}

// patch for 0x59679C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__FindNearestWaterAndItsFlow_5967A4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__FindNearestWaterAndItsFlow_59679C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S6, fWaterMapMinCoord)
		"VCMPE.F32 S2, S6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__FindNearestWaterAndItsFlow_5967A4_thumb)
		);
}

// patch for 0x596CB4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__RenderSeaBedSegment_596CBC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__RenderSeaBedSegment_596CB4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S12, fWaterMapMinCoord)
		"VMOV S8, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__RenderSeaBedSegment_596CBC_thumb)
		);
}

// patch for 0x596E6E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__RenderDetailedSeaBedSegment_596E7A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__RenderDetailedSeaBedSegment_596E6E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S5, fWaterMapMinCoord)
		"MOVT R12, #0xFF50\n"
		"MOVT R9, #0xC28C\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__RenderDetailedSeaBedSegment_596E7A_thumb)
		);
}

// patch for 0x597228
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__RenderWater_597232_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__RenderWater_597228()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWaterBlocksPerDimensionMinusOne)
		"VLDR D17, [R1]\n"
		"BGT 500f\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWaterBlocksPerDimensionMinusOne)
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__RenderWater_597232_thumb)
		);
}

// patch for 0x59727C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__RenderWater_5972BC_thumb = 0;	// loc_5972BC
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__RenderWater_597286_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__RenderWater_59727C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWaterBlocksPerDimensionMinusOne)
		"BNE 1f\n"
		"MOVS R0, #1\n"
		"VMOV.F32 S2, S24\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__RenderWater_597286_thumb)

		// Branches
		"1:\n"	// loc_5972BC
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__RenderWater_5972BC_thumb)
		);
}

// patch for 0x5972CA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__RenderWater_597AAC = 0;	// dword_597AAC
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__RenderWater_5972D4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__RenderWater_5972CA()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWaterBlocksPerDimensionMinusOne)
		ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CWaterLevel__RenderWater_597AAC)
		"MOV R9, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__RenderWater_5972D4_thumb)
		);
}

// patch for 0x597330
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__RenderWater_5973B2_thumb = 0;	// loc_5973B2
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__RenderWater_597338_thumb = 0;	// loc_597338
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__RenderWater_597330()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWaterBlocksPerDimensionMinusOne)
		"VMOV.F32 S27, S25\n"
		"BNE 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__RenderWater_597338_thumb)

		// Branches
		"1:\n"	// loc_5973B2
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__RenderWater_5973B2_thumb)
		);
}

// patch for 0x597918
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__RenderWater_597920 = 0;
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__RenderWater_597920_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__RenderWater_597918()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S16, fWaterMapMinCoord)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CWaterLevel__RenderWater_597920)
		"LDR R3, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__RenderWater_597920_thumb)
		);
}

// patch for 0x597934
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__RenderWater_5979F4_thumb = 0;	// loc_5979F4
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__RenderWater_59793C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__RenderWater_597934()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfWaterBlocksPerDimensionMinusOne)
		"BHI 500f\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWaterBlocksPerDimension)
		"500:\n"	// past the IT block
		"BCC 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__RenderWater_59793C_thumb)

		// Branches
		"1:\n"	// loc_5979F4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__RenderWater_5979F4_thumb)
		);
}

// patch for 0x598642
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__BlockHit_59866A_thumb = 0;	// loc_59866A
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__BlockHit_59864C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__BlockHit_598642()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfWaterBlocksPerDimensionMinusOne)
		"MOV R5, R0\n"
		"BGT 500f\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfWaterBlocksPerDimensionMinusOne)
		"500:\n"	// past the IT block
		"BGT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__BlockHit_59864C_thumb)

		// Branches
		"1:\n"	// loc_59866A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__BlockHit_59866A_thumb)
		);
}

// patch for 0x59866E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__BlockHit_598678_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__BlockHit_59866E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfWaterBlocksPerDimensionMinusThree)
		"MOV R0, #0\n"
		"IT HI\n"
		"MOVHI R0, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__BlockHit_598678_thumb)
		);
}

// patch for 0x59867A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__BlockHit_5986B0_thumb = 0;	// locret_5986B0
	uintptr_t Address_GTA_SA_2_00_CWaterLevel__BlockHit_598684_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWaterLevel__BlockHit_59867A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfWaterBlocksPerDimensionMinusThree)
		"IT HI\n"
		"MOVHI R1, #1\n"
		"ORRS R0, R1\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__BlockHit_598684_thumb)

		// Branches
		"1:\n"	// locret_5986B0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWaterLevel__BlockHit_5986B0_thumb)
		);
}


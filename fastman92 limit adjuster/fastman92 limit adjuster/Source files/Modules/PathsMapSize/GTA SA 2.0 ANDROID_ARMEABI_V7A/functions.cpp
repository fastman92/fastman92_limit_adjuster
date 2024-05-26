// Compilation time: 7 seconds 337 ms

// patch for 0x2E3542
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E354C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3542()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x14\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"LDR R2, [R2]\n"
		"VSTR S4, [R4,#0x38]\n"
		"LSRS R1, R0, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E354C_thumb)
		);
}

// patch for 0x2E3550
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E37C0_thumb = 0;	// loc_2E37C0
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E355A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3550()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E355A_thumb)

		// Branches
		"1:\n"	// loc_2E37C0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E37C0_thumb)
		);
}

// patch for 0x2E355C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3562 = 0;
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3564_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E355C()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x16\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3562)
		"LDR R6, [R3]\n"
		"LSRS R3, R2, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3564_thumb)
		);
}

// patch for 0x2E3568
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3572_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3568()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R6,R0]\n"
		"POP {R0, R1}\n"
		"CMP R6, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3572_thumb)

		// Branches
		"1:\n"	// loc_2E37C0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E37C0_thumb)
		);
}

// patch for 0x2E3574
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E357C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3574()
{
	__asm(
	".thumb\n"
		"BFC R2, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E357C_thumb)
		);
}

// patch for 0x2E3582
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E358C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3582()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"STR R2, [SP,#0x88+"/* var_5C */"-0x5C]\n"
		"MOV R11, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R11, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E358C_thumb)
		);
}

// patch for 0x2E358E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E359A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E358E()
{
	__asm(
	".thumb\n"
		"MOV R10, R6\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R10, Offset_CPathFind__m_pNaviNodes)
		"LDR R3, [R10,R3,LSL#2]\n"
		"LDR R9, [R10,R1,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E359A_thumb)
		);
}

// patch for 0x2E35DA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E35E4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E35DA()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x16\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R1, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E35E4_thumb)
		);
}

// patch for 0x2E35EC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E35F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E35EC()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"ADD R0, R1, R0,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E35F4_thumb)
		);
}

// patch for 0x2E35F8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3600_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E35F8()
{
	__asm(
	".thumb\n"
		"MOV R1, R11,LSL#1\n"
		"ADD R1, 0x10\n"
		"LDR R1, [R9,R1]\n"
		"VMOV S4, R8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3600_thumb)
		);
}

// patch for 0x2E3610
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3618_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3610()
{
	__asm(
	".thumb\n"
		"LDR R1, [R5,#0x14]\n"
		"VMOV S2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E3618_thumb)
		);
}

// patch for 0x2E36BA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E36C6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E36BA()
{
	__asm(
	".thumb\n"
		"LDR R1, [R3,#0x14]\n"
		"LDRD R6, R2, [SP,#0x88+"/* var_60 */"-0x60]\n"
		"VMUL.F32 S8, S12, S5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E36C6_thumb)
		);
}

// patch for 0x2E36CA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E36D6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E36CA()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, R2,LSL#1\n"
		"ADD R0, 0x10\n"
		"LDR R2, [R6,R0]\n"
		"POP {R0, R1}\n"
		"VMOV S0, R1\n"
		"VCVT.F32.S32 S0, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutoPilot__ModifySpeed_2E36D6_thumb)
		);
}

// patch for 0x2E7942
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7A1A_thumb = 0;	// loc_2E7A1A
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E794E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7942()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		"MOV R12, R2,LSR#16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E794E_thumb)

		// Branches
		"1:\n"	// loc_2E7A1A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7A1A_thumb)
		);
}

// patch for 0x2E7952
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E795E = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E795C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7952()
{
	__asm(
	".thumb\n"
		"MOV R2, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E795E)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E795C_thumb)
		);
}

// patch for 0x2E796C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7976_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E796C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviLinks)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"LDR R2, [R3,R2,LSL#2]\n"
		"LSRS R3, R2, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7976_thumb)
		);
}

// patch for 0x2E797A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E798A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E797A()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R6,R0]\n"
		"POP {R0, R1}\n"
		"CMP R6, #0\n"
		"BEQ 1f\n"
		"LDR R6, =("/* ThePaths_ptr */"0x677378 - 0x2E798E)\n"
		"BFC R2, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E798A_thumb)

		// Branches
		"1:\n"	// loc_2E7A1A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7A1A_thumb)
		);
}

// patch for 0x2E7992
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E799E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7992()
{
	__asm(
	".thumb\n"
		"MOV R6, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCCarPathLinkDividedBy2)
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"ADD R2, R3, R6,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E799E_thumb)
		);
}

// patch for 0x2E79B4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E79BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E79B4()
{
	__asm(
	".thumb\n"
		"MOV R1, R6,LSL#1\n"
		"ADD R1, 0x10\n"
		"LDR R1, [R3,R1]\n"
		"VMOV.F32 S0, #0.125\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E79BC_thumb)
		);
}

// patch for 0x2E79C4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E79CC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E79C4()
{
	__asm(
	".thumb\n"
		"LDR R1, [R2,#0x14]\n"
		"VMOV S4, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E79CC_thumb)
		);
}

// patch for 0x2E79FE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7A08_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E79FE()
{
	__asm(
	".thumb\n"
		"MOV R1, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R0, R0, R1,LSL#2\n"
		"LDRH R0, [R0,#0x18]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7A08_thumb)
		);
}

// patch for 0x2E7AAE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E8034_thumb = 0;	// loc_2E8034
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7ABA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7AAE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R0,R1]\n"
		"MOVS R0, #0\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7ABA_thumb)

		// Branches
		"1:\n"	// loc_2E8034
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E8034_thumb)
		);
}

// patch for 0x2E7BDA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E8032_thumb = 0;	// loc_2E8032
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7BE4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7BDA()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7BE4_thumb)

		// Branches
		"1:\n"	// loc_2E8032
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E8032_thumb)
		);
}

// patch for 0x2E7BE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7BF2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7BE8()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"MOV R5, R2\n"
		"ADD R9, R0, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7BF2_thumb)
		);
}

// patch for 0x2E7C44
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7C50_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7C44()
{
	__asm(
	".thumb\n"
		"MOV R1, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviLinks)
		"STR R1, [SP,#0x148+"/* var_E8 */"-0xE8]\n"
		"LDR R1, [SP,#0x148+"/* var_FC */"-0xFC]\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7C50_thumb)
		);
}

// patch for 0x2E7C84
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7CD2_thumb = 0;	// loc_2E7CD2
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7C8C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7C84()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CBZ R0, 1f\n"
		"LDR R3, [SP,#0x148+"/* var_E8 */"-0xE8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7C8C_thumb)

		// Branches
		"1:\n"	// loc_2E7CD2
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7CD2_thumb)
		);
}

// patch for 0x2E7C8E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7C98_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7C8E()
{
	__asm(
	".thumb\n"
		"LDR R2, [R3,R2,LSL#2]\n"
		"UBFX R2, R2, #16, #16\n"
		"LDR R3, [SP,#0x148+"/* var_EC */"-0xEC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7C98_thumb)
		);
}

// patch for 0x2E7C9C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7CA6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7C9C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CBZ R2, 1f\n"
		"MOV R2, R12,LSR#16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7CA6_thumb)

		// Branches
		"1:\n"	// loc_2E7CD2
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7CD2_thumb)
		);
}

// patch for 0x2E7CDA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7CE6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7CDA()
{
	__asm(
	".thumb\n"
		"MOV R1, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R4, R0, R1,LSL#2\n"
		"ADD R4, R4, #8\n"
		"LDR R0, [R4,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7CE6_thumb)
		);
}

// patch for 0x2E7CE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7CF0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7CE8()
{
	__asm(
	".thumb\n"
		"ADD R3, R3, #2\n"
		"LDR R1, [R3,#0x16]\n"
		"VMOV S0, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7CF0_thumb)
		);
}

// patch for 0x2E7CFE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7D08_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7CFE()
{
	__asm(
	".thumb\n"
		"ADD R5, R5, #8\n"
		"LDR R0, [R5,#0x14]\n"
		"MOV R11, R5\n"
		"VMOV S4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7D08_thumb)
		);
}

// patch for 0x2E7D0C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7D14_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7D0C()
{
	__asm(
	".thumb\n"
		"ADD R11, R11, #2\n"
		"LDR R0, [R11,#0x16]\n"
		"VMOV S4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7D14_thumb)
		);
}

// patch for 0x2E7DBC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7DC4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7DBC()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x18\n"
		"LDR R0, [LR,R0]\n"
		"VABS.F32 S21, S8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7DC4_thumb)
		);
}

// patch for 0x2E7DDA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7DE6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7DDA()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x18\n"
		"LDR R0, [R2,R0]\n"
		"VMUL.F32 S4, S21, S4\n"
		"VMOV S12, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7DE6_thumb)
		);
}

// patch for 0x2E7EA4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7EB0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7EA4()
{
	__asm(
	".thumb\n"
		"MOV R1, 0x16\n"
		"LDR R1, [R11,R1]\n"
		"VABS.F32 S29, S0\n"
		"MOV R0, 0x16\n"
		"LDR R0, [R3,R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7EB0_thumb)
		);
}

// patch for 0x2E7EC6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7ED2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7EC6()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x14\n"
		"LDR R0, [R4,R0]\n"
		"VCVT.F32.S32 S4, S4\n"
		"MOV R1, 0x14\n"
		"LDR R1, [R5,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7ED2_thumb)
		);
}

// patch for 0x2E7EE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7EF0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7EE8()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x18\n"
		"LDR R0, [LR,R0]\n"
		"VMUL.F32 S0, S0, S19\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7EF0_thumb)
		);
}

// patch for 0x2E7F00
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7F08_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7F00()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x18\n"
		"LDR R0, [R2,R0]\n"
		"VMUL.F32 S8, S8, S19\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7F08_thumb)
		);
}

// patch for 0x2E7F76
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7F86_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7F76()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R4\n"
		"VLD1.64 {Q9}, [R0]\n"
		"POP {R0, R1}\n"
		"MOV R0, 0x18\n"
		"LDR R0, [R2,R0]\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R5\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7F86_thumb)
		);
}

// patch for 0x2E7F8A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7F96_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7F8A()
{
	__asm(
	".thumb\n"
		"VCVT.F32.S32 D18, D18\n"
		"MOV R1, 0x18\n"
		"LDR R1, [LR,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7F96_thumb)
		);
}

// patch for 0x2E7FDC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7FEA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7FDC()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R5\n"
		"VLD1.64 {Q9}, [R0]\n"
		"POP {R0, R1}\n"
		"LDR R3, [SP,#0x148+"/* var_110 */"-0x110]\n"
		"CMP R8, #28\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R4\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E7FEA_thumb)
		);
}

// patch for 0x2E7FF4



// patch for 0x2E8094
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E809E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E8094()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R0,R3]\n"
		"MOV R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E809E_thumb)
		);
}

// patch for 0x2E80AA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E80B6 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E80B4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E80AA()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LDR R2, [R9]\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E80B6)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E80B4_thumb)
		);
}

// patch for 0x2E80C2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E80CC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E80C2()
{
	__asm(
	".thumb\n"
		"MOV R2, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R6,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E80CC_thumb)
		);
}

// patch for 0x2E8144
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E814E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E8144()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R0,R3]\n"
		"MOV R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E814E_thumb)
		);
}

// patch for 0x2E815C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E8164 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E8166_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E815C()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R6, Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E8164)
		"ADD R1, R3, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E8166_thumb)
		);
}

// patch for 0x2E8172
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E817E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E8172()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"ADD R1, R3, R1,LSL#2\n"
		"BIC R3, R0, #0xFF000000\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateCarCreationCoors2_2E817E_thumb)
		);
}

// patch for 0x2E8820
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E882A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8820()
{
	__asm(
	".thumb\n"
		"MOV R11, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R11, Offset_CPathFind__m_pPathNodes)
		"MOV R0, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E882A_thumb)
		);
}

// patch for 0x2E883A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8846_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E883A()
{
	__asm(
	".thumb\n"
		"MOV R1, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LDRB R0, [R0,#0x1A]\n"
		"ADD R1, R2, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8846_thumb)
		);
}

// patch for 0x2E885E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E886A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E885E()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"UXTH R0, R0\n"
		"LDR R0, [R11,R0,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E886A_thumb)
		);
}

// patch for 0x2E8888
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8890_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8888()
{
	__asm(
	".thumb\n"
		"MOV R6, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		"MOVS R5, #0\n"
		"LDR R0, [R4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8890_thumb)
		);
}

// patch for 0x2E897C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8984_thumb = 0;	// loc_2E8984
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E897C()
{
	__asm(
	".thumb\n"
		"MOVS R0, #0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pNodeLinks)
		"LDR R5, [R1,R5]\n"
		"MOVS R1, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8984_thumb)
		);
}

// patch for 0x2E89CA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E89D6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E89CA()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviLinks)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"LDR R6, [R2,R1,LSL#2]\n"
		"UBFX R1, R6, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E89D6_thumb)
		);
}

// patch for 0x2E89DE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E89EA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E89DE()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E89EA_thumb)
		);
}

// patch for 0x2E8CC4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8CCC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8CC4()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"STR R6, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R6, [R11,#0x3AA]\n"
		"ADD R10, R2, R0,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8CCC_thumb)
		);
}

// patch for 0x2E8D7E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8D8A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8D7E()
{
	__asm(
	".thumb\n"
		"LDR R3, [R1,#0x1C]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"LDR R1, [R1,#0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8D8A_thumb)
		);
}

// patch for 0x2E8D96
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8DA2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8D96()
{
	__asm(
	".thumb\n"
		"LDR R2, [R0,#0x1C]\n"
		"LDR R0, [R0,#0x20]\n"
		"VMOV S4, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8DA2_thumb)
		);
}

// patch for 0x2E8E70
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8E78_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8E70()
{
	__asm(
	".thumb\n"
		"MOV R1, R8\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8E78_thumb)
		);
}

// patch for 0x2E8EA2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EAE_thumb = 0;	// loc_2E8EAE
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EA2()
{
	__asm(
	".thumb\n"
		"ADD R0, R0, R9,LSL#2\n"
		"MOV R10, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R10, Offset_CPathFind__m_pNaviLinks)
		"MOV R4, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pPathNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EAE_thumb)
		);
}

// patch for 0x2E8EB4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EBC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EB4()
{
	__asm(
	".thumb\n"
		"MOV R2, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"ADD R6, R1, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EBC_thumb)
		);
}

// patch for 0x2E8ED2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EDC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8ED2()
{
	__asm(
	".thumb\n"
		"LDR R0, [R2,R0,LSL#2]\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		"CMP R0, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EDC_thumb)
		);
}

// patch for 0x2E8EE0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EE8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EE0()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [SP,#0x0]\n"
		"STR R1, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R0, [R11,#0x3A8]\n"
		"UBFX R0, R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EE8_thumb)
		);
}

// patch for 0x2E8EF0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8F34_thumb = 0;	// loc_2E8F34
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EF8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EF0()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CBZ R0, 1f\n"
		"LDR R0, =("/* ThePaths_ptr */"0x677378 - 0x2E8EFE)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8EF8_thumb)

		// Branches
		"1:\n"	// loc_2E8F34
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8F34_thumb)
		);
}

// patch for 0x2E8F06
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8F18_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8F06()
{
	__asm(
	".thumb\n"
		"MOV R2, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"ADD R0, R0, R9,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8F18_thumb)
		);
}

// patch for 0x2E8F72
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8F7E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8F72()
{
	__asm(
	".thumb\n"
		"UXTH R6, R2\n"
		"MOV R0, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8F7E_thumb)
		);
}

// patch for 0x2E8F8C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8F9A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8F8C()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LDR R2, [R0,#0x1C]\n"
		"LDR R3, [R0,#0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8F9A_thumb)
		);
}

// patch for 0x2E8F9E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8FAA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8F9E()
{
	__asm(
	".thumb\n"
		"LDR R0, [R0,#0x24]\n"
		"VMOV S4, R2\n"
		"LDR R6, [R1,#0x1C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8FAA_thumb)
		);
}

// patch for 0x2E8FAE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8FBA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8FAE()
{
	__asm(
	".thumb\n"
		"LDR R5, [R1,#0x20]\n"
		"LDR R1, [R1,#0x24]\n"
		"VCVT.F32.S32 S0, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E8FBA_thumb)
		);
}

// patch for 0x2E908A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9096_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E908A()
{
	__asm(
	".thumb\n"
		"MOV R6, R1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R11,#0x398]\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R12, [R0]\n"
		"STR R12, [SP,#0x10]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9096_thumb)
		);
}

// patch for 0x2E909E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90A8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E909E()
{
	__asm(
	".thumb\n"
		"LDR R5, [R6,R0,LSL#2]\n"
		"MOV R3, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90A8_thumb)
		);
}

// patch for 0x2E90AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90BA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90AC()
{
	__asm(
	".thumb\n"
		"UBFX R5, R12, #16, #16\n"
		"ADDS R3, #8\n"
		"ADD R1, R1, R5,LSL#2\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R3\n"
		"VLD1.64 {Q10}, [R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90BA_thumb)
		);
}

// patch for 0x2E90BC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90CC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90BC()
{
	__asm(
	".thumb\n"
		"BFC R3, #16, #16\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCCarPathLinkDividedBy2)
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90CC_thumb)
		);
}

// patch for 0x2E90D0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90DA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90D0()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		"MOV R0, R3,LSL#1\n"
		"ADD R0, 0x10\n"
		"ADD R0, R1\n"
		"VLD1.64 {Q9}, [R0]\n"
		"POP {R0, R2}\n"
		"UXTH R3, R2\n"
		"LDR R3, [R6,R3,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90DA_thumb)
		);
}

// patch for 0x2E90E2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90F2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90E2()
{
	__asm(
	".thumb\n"
		"LSRS R1, R2, #0x10\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90F2_thumb)
		);
}

// patch for 0x2E90FC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9104_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E90FC()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R1\n"
		"VLD1.64 {Q10}, [R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9104_thumb)
		);
}

// patch for 0x2E914C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9154 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9158_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E914C()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9154)
		"LDR R2, [R2]\n"
		"UBFX R3, R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9158_thumb)
		);
}

// patch for 0x2E915E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E916E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E915E()
{
	__asm(
	".thumb\n"
		"BFC R3, #16, #16\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCCarPathLinkDividedBy2)
		"MOV R6, R3,LSL#1\n"
		"ADD R6, 0x10\n"
		"LDR R6, [R2,R6]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E916E_thumb)
		);
}

// patch for 0x2E9172
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E917E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9172()
{
	__asm(
	".thumb\n"
		"LDR R2, [R2,#0x14]\n"
		"VMOV S6, R6\n"
		"VMOV S4, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E917E_thumb)
		);
}

// patch for 0x2E92A4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92AC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92A4()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R12, [R0]\n"
		"STR R12, [SP,#0x10]\n"
		"POP {R0-R3,R12,LR}\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92AC_thumb)
		);
}

// patch for 0x2E92B0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92B0()
{
	__asm(
	".thumb\n"
		"UBFX R5, R12, #16, #16\n"
		"ADD R6, R3, R6,LSL#2\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pNaviNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92BC_thumb)
		);
}

// patch for 0x2E92C2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92CE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92C2()
{
	__asm(
	".thumb\n"
		"UBFX R4, R0, #16, #16\n"
		"BFC R1, #16, #16\n"
		"LDR R3, [R3,R4,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92CE_thumb)
		);
}

// patch for 0x2E92D0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92DE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92D0()
{
	__asm(
	".thumb\n"
		"MOV R2, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R6,R0]\n"
		"POP {R0, R1}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92DE_thumb)
		);
}

// patch for 0x2E92E4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92EC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92E4()
{
	__asm(
	".thumb\n"
		"BFC R4, #16, #16\n"
		"MOV R6, R1,LSL#1\n"
		"ADD R6, 0x10\n"
		"LDR R6, [R3,R6]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92EC_thumb)
		);
}

// patch for 0x2E92F0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9300_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E92F0()
{
	__asm(
	".thumb\n"
		"LDR R3, [R2,#0x1C]\n"
		"LDR R1, [R1,#0x14]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCCarPathLinkDividedBy2)
		"LDR R2, [R2,#0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9300_thumb)
		);
}

// patch for 0x2E931C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9324_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E931C()
{
	__asm(
	".thumb\n"
		"MOV R1, R4,LSL#1\n"
		"ADD R1, 0x10\n"
		"LDR R1, [R5,R1]\n"
		"VCVT.F32.S32 S4, S4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9324_thumb)
		);
}

// patch for 0x2E9328
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9330_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9328()
{
	__asm(
	".thumb\n"
		"LDR R2, [R2,#0x14]\n"
		"VMOV S10, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9330_thumb)
		);
}

// patch for 0x2E93B0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E93B8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E93B0()
{
	__asm(
	".thumb\n"
		"UBFX R2, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E93B8_thumb)
		);
}

// patch for 0x2E93BA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E93CE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E93BA()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"LDR R6, [R1]\n"
		"MOV R1, R12\n"
		"BFC R1, #16, #16\n"
		"MOV R8, R6\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R8, Offset_CPathFind__m_pNaviNodes)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E93CE_thumb)
		);
}

// patch for 0x2E93D2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E93DC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E93D2()
{
	__asm(
	".thumb\n"
		"UBFX R3, R12, #16, #16\n"
		"LDR R5, [SP,#0x158+"/* var_100 */"-0x100]\n"
		"LDR R3, [R8,R3,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E93DC_thumb)
		);
}

// patch for 0x2E9418
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9424_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9418()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R1, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9424_thumb)
		);
}

// patch for 0x2E9428
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9430_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9428()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"ADD R0, R1, R0,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9430_thumb)
		);
}

// patch for 0x2E943C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9446_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E943C()
{
	__asm(
	".thumb\n"
		"MOV R3, R6\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"STR R3, [SP,#0x158+"/* var_108 */"-0x108]\n"
		"VMOV.F32 S2, #1.0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9446_thumb)
		);
}

// patch for 0x2E9464
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E946E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9464()
{
	__asm(
	".thumb\n"
		"MOV R1, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"VMOV.F32 S4, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E946E_thumb)
		);
}

// patch for 0x2E94F8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9504_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E94F8()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R1, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9504_thumb)
		);
}

// patch for 0x2E950C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9514_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E950C()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"MOV R2, R0,LSL#1\n"
		"ADD R2, 0x10\n"
		"LDR R2, [R1,R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9514_thumb)
		);
}

// patch for 0x2E9518
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9520_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9518()
{
	__asm(
	".thumb\n"
		"LDR R1, [R0,#0x14]\n"
		"VMOV S8, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9520_thumb)
		);
}

// patch for 0x2E9574
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9580_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9574()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R9\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R2, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9580_thumb)
		);
}

// patch for 0x2E9584
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E958C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9584()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"MOV R3, R1,LSL#1\n"
		"ADD R3, 0x10\n"
		"LDR R3, [R2,R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E958C_thumb)
		);
}

// patch for 0x2E9590
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9598_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9590()
{
	__asm(
	".thumb\n"
		"LDR R2, [R1,#0x14]\n"
		"VMOV S6, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9598_thumb)
		);
}

// patch for 0x2E96CE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E96DA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E96CE()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R9\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R2, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E96DA_thumb)
		);
}

// patch for 0x2E96DE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E96EE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E96DE()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"MOV R3, R1,LSL#1\n"
		"ADD R3, 0x10\n"
		"LDR R3, [R2,R3]\n"
		"ADD R1, R2, R1,LSL#1\n"
		"LDR R1, [R1,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E96EE_thumb)
		);
}

// patch for 0x2E9718
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9724_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9718()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R9\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R2, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9724_thumb)
		);
}

// patch for 0x2E9728
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9730_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9728()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"MOV R3, R1,LSL#1\n"
		"ADD R3, 0x10\n"
		"LDR R3, [R2,R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9730_thumb)
		);
}

// patch for 0x2E9736
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9740_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9736()
{
	__asm(
	".thumb\n"
		"LDR R1, [R1,#0x14]\n"
		"VMOV S8, R3\n"
		"ADD R3, SP, #0x158+"/* var_E8 */"-0xE8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9740_thumb)
		);
}

// patch for 0x2E97C6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E97D0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E97C6()
{
	__asm(
	".thumb\n"
		"MOV R0, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R0, R1, R0,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E97D0_thumb)
		);
}

// patch for 0x2E97D4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E97E2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E97D4()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LDR R3, [R0,#0x1C]\n"
		"LDR R5, [R0,#0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E97E2_thumb)
		);
}

// patch for 0x2E97E6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E97F2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E97E6()
{
	__asm(
	".thumb\n"
		"LDR R0, [R0,#0x24]\n"
		"VMOV S4, R3\n"
		"LDR R2, [R1,#0x1C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E97F2_thumb)
		);
}

// patch for 0x2E97F6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9802_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E97F6()
{
	__asm(
	".thumb\n"
		"LDR R4, [R1,#0x20]\n"
		"VMOV S8, R0\n"
		"LDR R1, [R1,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneRandomCar_2E9802_thumb)
		);
}

// patch for 0x2EA718
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB338_thumb = 0;	// loc_2EB338
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA722_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA718()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R10,R0]\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA722_thumb)

		// Branches
		"1:\n"	// loc_2EB338
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB338_thumb)
		);
}

// patch for 0x2EA738
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA742_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA738()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R9,R1]\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA742_thumb)

		// Branches
		"1:\n"	// loc_2EB338
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB338_thumb)
		);
}

// patch for 0x2EA746
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA74E = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA750_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA746()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA74E)
		"LDR R3, [R2]\n"
		"LSRS R2, R0, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA750_thumb)
		);
}

// patch for 0x2EA754
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA75E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA754()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"CMP R3, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA75E_thumb)

		// Branches
		"1:\n"	// loc_2EB338
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB338_thumb)
		);
}

// patch for 0x2EA768
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA772 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA774_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA768()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA772)
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA774_thumb)
		);
}

// patch for 0x2EA77A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA784_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA77A()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"LDRH R1, [R1,#0x18]\n"
		"AND R1, R1, #0xF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA784_thumb)
		);
}

// patch for 0x2EA78C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA794_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA78C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"ADD R2, R1, R0,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA794_thumb)
		);
}

// patch for 0x2EA8AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA8B6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA8AC()
{
	__asm(
	".thumb\n"
		"MOV R1, R10\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"STR R1, [SP,#0xE8+"/* var_DC */"-0xDC]\n"
		"MOV R1, R9\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA8B6_thumb)
		);
}

// patch for 0x2EA8D8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA8E0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA8D8()
{
	__asm(
	".thumb\n"
		"MOV R2, R1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pNaviLinks)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA8E0_thumb)
		);
}

// patch for 0x2EA968
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA972_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA968()
{
	__asm(
	".thumb\n"
		"MOV R10, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R10, SizeOfCPathNodeDividedBy4)
		"LDR R1, [SP,#0xE8+"/* var_98 */"-0x98]\n"
		"ADD R0, R0, R10,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA972_thumb)
		);
}

// patch for 0x2EA98C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAA76_thumb = 0;	// loc_2EAA76
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA994_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA98C()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA994_thumb)

		// Branches
		"1:\n"	// loc_2EAA76
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAA76_thumb)
		);
}

// patch for 0x2EA9B6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA9C6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA9B6()
{
	__asm(
	".thumb\n"
		"LDR R5, [R1,R0,LSL#2]\n"
		"LDR R1, [SP,#0xE8+"/* var_B0 */"-0xB0]\n"
		"LSRS R0, R5, #16\n"
		"ADD R1, R1, R0,LSL#2\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA9C6_thumb)
		);
}

// patch for 0x2EA9E8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA9F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA9E8()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pNaviNodes)
		"LDR R2, [R0,R2]\n"
		"MOV R12, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R12, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EA9F4_thumb)
		);
}

// patch for 0x2EAA26
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAA30_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAA26()
{
	__asm(
	".thumb\n"
		"UBFX R6, R5, #16, #16\n"
		"LDR R4, [SP,#0xE8+"/* var_D0 */"-0xD0]\n"
		"LDRH R1, [R1,#0xB]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAA30_thumb)
		);
}

// patch for 0x2EAA36
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAA40_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAA36()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R6, [R6,R0]\n"
		"POP {R0, R1}\n"
		"LSLS R1, R1, #0x10\n"
		"ADD R6, R6, R12,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAA40_thumb)
		);
}

// patch for 0x2EAA9A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAAA4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAA9A()
{
	__asm(
	".thumb\n"
		"MOV R1, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviLinks)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"STR R0, [SP,#0xE8+"/* var_98 */"-0x98]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAAA4_thumb)
		);
}

// patch for 0x2EAB38
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAC02_thumb = 0;	// loc_2EAC02
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAB40_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAB38()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAB40_thumb)

		// Branches
		"1:\n"	// loc_2EAC02
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAC02_thumb)
		);
}

// patch for 0x2EAB60
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAB68_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAB60()
{
	__asm(
	".thumb\n"
		"LDR R5, [R1,R0,LSL#2]\n"
		"LDR R1, [SP,#0xE8+"/* var_A4 */"-0xA4]\n"
		"LSRS R0, R5, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAB68_thumb)
		);
}

// patch for 0x2EAB6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAB74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAB6C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAB74_thumb)

		// Branches
		"1:\n"	// loc_2EAC02
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAC02_thumb)
		);
}

// patch for 0x2EAB7E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAB8A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAB7E()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAB8A_thumb)
		);
}

// patch for 0x2EABD6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EABE0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EABD6()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EABE0_thumb)
		);
}

// patch for 0x2EABF2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EABFC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EABF2()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R0, R0, R1,LSL#2\n"
		"LDRH R0, [R0,#0x18]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EABFC_thumb)
		);
}

// patch for 0x2EAC2C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAC34_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAC2C()
{
	__asm(
	".thumb\n"
		"MOV R1, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviLinks)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAC34_thumb)
		);
}

// patch for 0x2EACC0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAD4C_thumb = 0;	// loc_2EAD4C
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EACC8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EACC0()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EACC8_thumb)

		// Branches
		"1:\n"	// loc_2EAD4C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAD4C_thumb)
		);
}

// patch for 0x2EACE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EACF0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EACE8()
{
	__asm(
	".thumb\n"
		"LDR R5, [R1,R0,LSL#2]\n"
		"LDR R1, [SP,#0xE8+"/* var_A4 */"-0xA4]\n"
		"LSRS R0, R5, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EACF0_thumb)
		);
}

// patch for 0x2EACF4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EACFC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EACF4()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CBZ R1, 1f\n"
		"LDR R1, [SP,#0xE8+"/* var_B0 */"-0xB0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EACFC_thumb)

		// Branches
		"1:\n"	// loc_2EAD4C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAD4C_thumb)
		);
}

// patch for 0x2EAD04
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAD10_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAD04()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAD10_thumb)
		);
}

// patch for 0x2EAD5C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAD64_thumb = 0;	// loc_2EAD64
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAD5C()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R5, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STR R1, [R0,#0x398]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAD64_thumb)
		);
}

// patch for 0x2EADD0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EADDA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EADD0()
{
	__asm(
	".thumb\n"
		"MOV R1, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EADDA_thumb)
		);
}

// patch for 0x2EAE94
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAE9E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAE94()
{
	__asm(
	".thumb\n"
		"MOV R1, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAE9E_thumb)
		);
}

// patch for 0x2EAEE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAEF6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAEE8()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R3, [R0]\n"
		"STR R3, [SP,#0xC]\n"
		"POP {R0-R3,R12,LR}\n"
		"MOV R2, R8\n"
		"LDRB R6, [R11,#0x3B9]\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R10, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAEF6_thumb)
		);
}

// patch for 0x2EAF06
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF14_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF06()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AC\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [SP,#0xC]\n"
		"STR R1, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R3, [R11,#0x3AC]\n"
		"ADDS R3, R4, R5\n"
		"STRB R6, [R11,#0x3B8]\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"STR R10, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R10, [R11,#0x3A8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF14_thumb)
		);
}

// patch for 0x2EAF1C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF24_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF1C()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [SP,#0x8]\n"
		"STR R1, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R2, [R11,#0x3AA]\n"
		"STR R3, [R11,#0x3A0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF24_thumb)
		);
}

// patch for 0x2EAF36
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF40 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF42_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF36()
{
	__asm(
	".thumb\n"
		"MOV R9, R2,LSR#16\n"
		"MOVS R3, #0xFF\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF40)
		"STRB R3, [R11,#0x3BA]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF42_thumb)
		);
}

// patch for 0x2EAF48
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFCC_thumb = 0;	// loc_2EAFCC
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF52_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF48()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CBZ R0, 1f\n"
		"LDR R0, =("/* ThePaths_ptr */"0x677378 - 0x2EAF5C)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF52_thumb)

		// Branches
		"1:\n"	// loc_2EAFCC
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFCC_thumb)
		);
}

// patch for 0x2EAF54
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF5C = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF5E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF54()
{
	__asm(
	".thumb\n"
		"BFC R3, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF5C)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF5E_thumb)
		);
}

// patch for 0x2EAF64
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF6C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF64()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"ADD R0, R0, R3,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF6C_thumb)
		);
}

// patch for 0x2EAF8A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF96 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF94_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF8A()
{
	__asm(
	".thumb\n"
		"MOV R9, R2,LSR#16\n"
		"MOV R8, #1\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF96)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF94_thumb)
		);
}

// patch for 0x2EAF9E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFD0_thumb = 0;	// loc_2EAFD0
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFA8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAF9E()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CBZ R0, 1f\n"
		"LDR R0, =("/* ThePaths_ptr */"0x677378 - 0x2EAFB2)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFA8_thumb)

		// Branches
		"1:\n"	// loc_2EAFD0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFD0_thumb)
		);
}

// patch for 0x2EAFAA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFB2 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFB4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFAA()
{
	__asm(
	".thumb\n"
		"BFC R3, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFB2)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFB4_thumb)
		);
}

// patch for 0x2EAFBA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFC6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFBA()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"ADD R0, R0, R3,LSL#1\n"
		"LDRH R0, [R0,#0xB]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFC6_thumb)
		);
}

// patch for 0x2EAFE4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFEE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFE4()
{
	__asm(
	".thumb\n"
		"BFC R12, #16, #16\n"
		"LDR R0, [R0]\n"
		"LSRS R2, R4, #0x10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFEE_thumb)
		);
}

// patch for 0x2EAFF0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFF8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFF0()
{
	__asm(
	".thumb\n"
		"MOV R3, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFF8_thumb)
		);
}

// patch for 0x2EAFFA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB006_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EAFFA()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R1, [R3,R1,LSL#2]\n"
		"LDR R5, [R3,R5,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB006_thumb)
		);
}

// patch for 0x2EB00C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB01A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB00C()
{
	__asm(
	".thumb\n"
		"LDR R4, [R1,#0x1C]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"LDR R1, [R1,#0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB01A_thumb)
		);
}

// patch for 0x2EB02A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB03A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB02A()
{
	__asm(
	".thumb\n"
		"LDR R3, [R2,#0x1C]\n"
		"LDR R2, [R2,#0x20]\n"
		"VMOV S4, R3\n"
		"MOV R3, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB03A_thumb)
		);
}

// patch for 0x2EB052
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB05E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB052()
{
	__asm(
	".thumb\n"
		"UBFX R2, R10, #16, #16\n"
		"ADD R1, R1, R3,LSL#1\n"
		"BFC R10, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB05E_thumb)
		);
}

// patch for 0x2EB07E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB08A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB07E()
{
	__asm(
	".thumb\n"
		"MOV R2, R10\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"VCVT.F32.S32 S22, S8\n"
		"ADD R0, R0, R2,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB08A_thumb)
		);
}

// patch for 0x2EB15A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB166_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB15A()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMUL.F32 S0, S24, S20\n"
		"LDRSB R5, [R11,#0x3BB]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB166_thumb)
		);
}

// patch for 0x2EB170
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB184_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB170()
{
	__asm(
	".thumb\n"
		"UBFX R2, R1, #16, #16\n"
		"VMUL.F32 S6, S28, S20\n"
		"BFC R1, #16, #16\n"
		"MOV R4, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pNaviNodes)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB184_thumb)
		);
}

// patch for 0x2EB1AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB1BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB1AC()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"LDRSB R5, [R11,#0x3BC]\n"
		"UBFX R1, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB1BC_thumb)
		);
}

// patch for 0x2EB1C0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB1C8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB1C0()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"ADD R0, R1, R0,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB1C8_thumb)
		);
}

// patch for 0x2EB1D0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB1D8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB1D0()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMOV S10, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB1D8_thumb)
		);
}

// patch for 0x2EB1E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB1E8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB1E0()
{
	__asm(
	".thumb\n"
		"UBFX R2, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB1E8_thumb)
		);
}

// patch for 0x2EB1F0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB200_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB1F0()
{
	__asm(
	".thumb\n"
		"MOV R3, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCCarPathLinkDividedBy2)
		"ADD R1, R2, R3,LSL#1\n"
		"PUSH {R0, R1}\n"
		"MOV R0, R3,LSL#1\n"
		"ADD R0, 0x10\n"
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"LDR R6, [R1,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB200_thumb)
		);
}

// patch for 0x2EB240
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB250_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB240()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMUL.F32 S0, S6, S0\n"
		"UBFX R3, R2, #16, #16\n"
		"BFC R2, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB250_thumb)
		);
}

// patch for 0x2EB254
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB264_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB254()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"ADD R6, R3, R2,LSL#1\n"
		"PUSH {R0, R1}\n"
		"MOV R0, R2,LSL#1\n"
		"ADD R0, 0x10\n"
		"LDR R2, [R3,R0]\n"
		"POP {R0, R1}\n"
		"LDR R5, [R6,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeRandomly_2EB264_thumb)
		);
}

// patch for 0x2EB4E6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__CreatePoliceChase_2EB4F0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__CreatePoliceChase_2EB4E6()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__CreatePoliceChase_2EB4F0_thumb)
		);
}

// patch for 0x2EB4F6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__CreatePoliceChase_2EB502_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__CreatePoliceChase_2EB4F6()
{
	__asm(
	".thumb\n"
		"LDR R1, [R0,#0x1C]\n"
		"LDR R2, [R0,#0x20]\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__CreatePoliceChase_2EB502_thumb)
		);
}

// patch for 0x2EC044
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC056_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC044()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"STR R4, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R4, [R11,#0x3A8]\n"
		"MOVS R6, #0\n"
		"STRH R4, [R11,#0x398]\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AC\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"STR R4, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R4, [R11,#0x3AC]\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"STR R4, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R4, [R11,#0x3AA]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC056_thumb)
		);
}

// patch for 0x2EC0A2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC0B6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC0A2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R2,R3]\n"
		"CMP R3, #0\n"
		"BEQ 500f\n"
		"LSR R6, R0, #0x10\n"
		"MOV R2, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"ADD R2, R3, R2,LSL#2\n"
		"LDRH R3, [R2,#0x18]\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC0B6_thumb)
		);
}

// patch for 0x2EC0E6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC0F0 = 0;	// loc_2EC0F0
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC0F0_thumb = 0;	// loc_2EC0F0
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC0E6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pNodeLinks)
		"LDR R2, [R0,R2]\n"
		"LDR R0, =("/* ThePaths_ptr */"0x677378 - 0x2EC0F0)\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC0F0)
		"LDR R5, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC0F0_thumb)
		);
}

// patch for 0x2EC0FC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC104_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC0FC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, Offset_CPathFind__m_pPathNodes)
		"LDR R12, [R0,R12]\n"
		"CMP R12, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC104_thumb)
		);
}

// patch for 0x2EC10A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC11A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC10A()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R10\n"
		"VLD1.64 {Q10}, [R0]\n"
		"POP {R0, R1}\n"
		"MOV R0, LR\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC11A_thumb)
		);
}

// patch for 0x2EC124
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC12C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC124()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x14\n"
		"ADD R1, R0\n"
		"VLD1.64 {Q9}, [R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC12C_thumb)
		);
}

// patch for 0x2EC178
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC180_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC178()
{
	__asm(
	".thumb\n"
		"MOV R3, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		"VMOV.F32 S2, #1.0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC180_thumb)
		);
}

// patch for 0x2EC182
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC18C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC182()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R10\n"
		"VLD1.64 {Q9}, [R0]\n"
		"POP {R0, R1}\n"
		"LDR R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC18C_thumb)
		);
}

// patch for 0x2EC198
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC1A0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC198()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"ADD R0, R0, R3,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC1A0_thumb)
		);
}

// patch for 0x2EC1A6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC1B2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC1A6()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x14\n"
		"ADD R1, R0\n"
		"VLD1.64 {Q10}, [R1]\n"
		"POP {R1, R2}\n"
		"LDR R0, [R11,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__JoinCarWithRoadSystem_2EC1B2_thumb)
		);
}

// patch for 0x2ECC2A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC34_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC2A()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		"MOV R1, #0xFFFF\n"
		"CMP R2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC34_thumb)
		);
}

// patch for 0x2ECC3A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC42 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC4A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC3A()
{
	__asm(
	".thumb\n"
		"UBFX R2, R2, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC42)
		"LDR R3, [R3]\n"
		"ADD R2, R3, R2,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC4A_thumb)
		);
}

// patch for 0x2ECC4C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC54_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC4C()
{
	__asm(
	".thumb\n"
		"BEQ 500f\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		"CMP R2, R1\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC54_thumb)
		);
}

// patch for 0x2ECC5A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC62 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC6A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC5A()
{
	__asm(
	".thumb\n"
		"UBFX R2, R2, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC62)
		"LDR R3, [R3]\n"
		"ADD R2, R3, R2,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC6A_thumb)
		);
}

// patch for 0x2ECC82
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC90_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC82()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"ITT NE\n"
		"LDRHNE R2, [R4,#0x398]\n"
		"CMPNE R2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECC90_thumb)
		);
}

// patch for 0x2ECCA0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECCB0_thumb = 0;	// loc_2ECCB0
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECCAA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECCA0()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CBZ R1, 1f\n"
		"LDRH R1, [R4,#0x3DF]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECCAA_thumb)

		// Branches
		"1:\n"	// loc_2ECCB0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECCB0_thumb)
		);
}

// patch for 0x2ECD42
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECD4E = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECD4C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECD42()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R3, [R0]\n"
		"STR R3, [SP,#0xC]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECD4E)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECD4C_thumb)
		);
}

// patch for 0x2ECD4E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECD68_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECD4E()
{
	__asm(
	".thumb\n"
		"UBFX R6, R2, #16, #16\n"
		"LDR R0, [R0]\n"
		"UBFX R5, R3, #16, #16\n"
		"BFC R3, #16, #16\n"
		"MOV R9, R1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R9, Offset_CPathFind__m_pNaviNodes)
		"BFC R2, #16, #16\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECD68_thumb)
		);
}

// patch for 0x2ECD82
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECD8C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECD82()
{
	__asm(
	".thumb\n"
		"MOV R1, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"LDR R2, [R4,#0x3A0]\n"
		"STR R2, [SP,#0xC0+"/* var_98 */"-0x98]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECD8C_thumb)
		);
}

// patch for 0x2ECDB4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECDC0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECDB4()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R1, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECDC0_thumb)
		);
}

// patch for 0x2ECDC4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECDCC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECDC4()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"ADD R0, R1, R0,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECDCC_thumb)
		);
}

// patch for 0x2ECDF0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECDF8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECDF0()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMOV S3, R11\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECDF8_thumb)
		);
}

// patch for 0x2ECE16
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECE20_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECE16()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMOV S0, R2\n"
		"ADD R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECE20_thumb)
		);
}

// patch for 0x2ECEDA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECEE6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECEDA()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R1, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECEE6_thumb)
		);
}

// patch for 0x2ECEEA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECEFA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECEEA()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"MOV R2, R0,LSL#1\n"
		"ADD R2, 0x10\n"
		"LDR R2, [R1,R2]\n"
		"ADD R0, R1, R0,LSL#1\n"
		"LDR R0, [R0,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECEFA_thumb)
		);
}

// patch for 0x2ECF82
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECF8E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECF82()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R1, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECF8E_thumb)
		);
}

// patch for 0x2ECF92
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECFA2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECF92()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"MOV R2, R0,LSL#1\n"
		"ADD R2, 0x10\n"
		"LDR R2, [R1,R2]\n"
		"ADD R0, R1, R0,LSL#1\n"
		"LDR R0, [R0,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ECFA2_thumb)
		);
}

// patch for 0x2ED032
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ED03C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ED032()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"CMP R1, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__UpdateCarOnRails_2ED03C_thumb)
		);
}

// patch for 0x2ED08C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED094_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED08C()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		"MOV R1, #0xFFFF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED094_thumb)
		);
}

// patch for 0x2ED09A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0A2 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0AA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED09A()
{
	__asm(
	".thumb\n"
		"UBFX R2, R2, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0A2)
		"LDR R3, [R3]\n"
		"ADD R2, R3, R2,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0AA_thumb)
		);
}

// patch for 0x2ED0AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0B4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0AC()
{
	__asm(
	".thumb\n"
		"BEQ 500f\n"
		"PUSH {R0-R3,R12,LR}\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		"CMP R2, R1\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0B4_thumb)
		);
}

// patch for 0x2ED0B8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0C0 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0C0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0B8()
{
	__asm(
	".thumb\n"
		"UBFX R2, R2, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0C0)
		"LDR R3, [R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0C0_thumb)
		);
}

// patch for 0x2ED0C4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0D2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0C4()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"ITT NE\n"
		"LDRHNE R2, [R0,#0x394]\n"
		"CMPNE R2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0D2_thumb)
		);
}

// patch for 0x2ED0E2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0F0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0E2()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"ITT NE\n"
		"LDRHNE R2, [R0,#0x398]\n"
		"CMPNE R2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED0F0_thumb)
		);
}

// patch for 0x2ED100
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED10C_thumb = 0;	// loc_2ED10C
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED100()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CMP R1, #0\n"
		"ITT NE\n"
		"MOVNE R0, #0\n"
		"BXNE LR\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__StopCarIfNodesAreInvalid_2ED10C_thumb)
		);
}

// patch for 0x2ED22E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeAccordingStrategy_2ED238_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeAccordingStrategy_2ED22E()
{
	__asm(
	".thumb\n"
		"MOV R1, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R0,R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeAccordingStrategy_2ED238_thumb)
		);
}

// patch for 0x2ED246
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeAccordingStrategy_2ED252_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeAccordingStrategy_2ED246()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"LDRSB R3, [R4,#0x3BE]\n"
		"ADD R0, R0, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeAccordingStrategy_2ED252_thumb)
		);
}

// patch for 0x2EFA34
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFA3C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFA34()
{
	__asm(
	".thumb\n"
		"MOV R6, R11\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		"ORR R0, R0, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFA3C_thumb)
		);
}

// patch for 0x2EFA68
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFA70_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFA68()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R8,R3]\n"
		"ADD R3, R3, R6,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFA70_thumb)
		);
}

// patch for 0x2EFA76
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFA80_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFA76()
{
	__asm(
	".thumb\n"
		"LDR R5, [R3,#0x1C]\n"
		"LDR R4, [R3,#0x20]\n"
		"LDR R6, [R6]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFA80_thumb)
		);
}

// patch for 0x2EFA84
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFA8C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFA84()
{
	__asm(
	".thumb\n"
		"LDR R3, [R3,#0x24]\n"
		"VMOV S4, R4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFA8C_thumb)
		);
}

// patch for 0x2EFB62
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFB6C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFB62()
{
	__asm(
	".thumb\n"
		"MOV R3, R8\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"STR R3, [SP,#0xD8+"/* var_7C */"-0x7C]\n"
		"UXTH R1, R1\n"
		"CMP R1, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFB6C_thumb)
		);
}

// patch for 0x2EFB9E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFBAC_thumb = 0;	// loc_2EFBAC
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFB9E()
{
	__asm(
	".thumb\n"
		"ADD R1, R2, R1,LSL#2\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"B 1f\n"

		// Branches
		"1:\n"	// loc_2EFBAC
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFBAC_thumb)
		);
}

// patch for 0x2EFBFA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFC08_thumb = 0;	// loc_2EFC08
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFBFA()
{
	__asm(
	".thumb\n"
		"ADD R1, R2, R1,LSL#2\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"B 1f\n"

		// Branches
		"1:\n"	// loc_2EFC08
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFC08_thumb)
		);
}

// patch for 0x2EFC9A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFCA6 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFCA4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFC9A()
{
	__asm(
	".thumb\n"
		"MOV R6, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pNodeLinks)
		"VLDR S26, 101f\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFCA6)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFCA4_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, -3.1416)
		);
}

// patch for 0x2EFCEC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFDAA_thumb = 0;	// loc_2EFDAA
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFCF4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFCEC()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFCF4_thumb)

		// Branches
		"1:\n"	// loc_2EFDAA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFDAA_thumb)
		);
}

// patch for 0x2EFCF8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFD00_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFCF8()
{
	__asm(
	".thumb\n"
		"MOV R2, R9\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFD00_thumb)
		);
}

// patch for 0x2EFD04
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFD14_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFD04()
{
	__asm(
	".thumb\n"
		"LDR R2, [R1,#0x1C]\n"
		"LDR R1, [R1,#0x20]\n"
		"LDR R3, [R0,#0x1C]\n"
		"LDR R0, [R0,#0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFD14_thumb)
		);
}

// patch for 0x2EFDFC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE04_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFDFC()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R9\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STR R5, [SP,#0xD8+"/* var_88 */"-0x88]\n"
		"ADD R2, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE04_thumb)
		);
}

// patch for 0x2EFE10
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE18_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE10()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R9\n"
		"ADD R0, R0, #0x3AC\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [SP,#0x0]\n"
		"STR R1, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R0, [R9,#0x3AC]\n"
		"LDRB LR, [R9,#0x3BC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE18_thumb)
		);
}

// patch for 0x2EFE24
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE30_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE24()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R9\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRB LR, [R9,#0x3BB]\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R9\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [SP,#0x4]\n"
		"STR R1, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R1, [R9,#0x3A8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE30_thumb)
		);
}

// patch for 0x2EFE58
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE64_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE58()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviLinks)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"LDR R2, [R0,R2,LSL#2]\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R9\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [SP,#0x8]\n"
		"STR R1, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R2, [R9,#0x3AA]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE64_thumb)
		);
}

// patch for 0x2EFE68
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE6E = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE76_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE68()
{
	__asm(
	".thumb\n"
		"LSRS R3, R1, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE6E)
		"LDR R0, [R0]\n"
		"ADD R0, R0, R3,LSL#2\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE76_thumb)
		);
}

// patch for 0x2EFE80
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE86 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE8E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE80()
{
	__asm(
	".thumb\n"
		"LSRS R6, R2, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE86)
		"LDR R0, [R0]\n"
		"ADD R0, R0, R6,LSL#2\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFE8E_thumb)
		);
}

// patch for 0x2EFEA4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEB0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEA4()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"ITT NE\n"
		"UXTHNE R5, R4\n"
		"CMPNE R5, R10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEB0_thumb)
		);
}

// patch for 0x2EFEBC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEF8_thumb = 0;	// loc_2EFEF8
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEC4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEBC()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CBZ R0, 1f\n"
		"LDR R0, [SP,#0xD8+"/* var_8C */"-0x8C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEC4_thumb)

		// Branches
		"1:\n"	// loc_2EFEF8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEF8_thumb)
		);
}

// patch for 0x2EFED6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEE2 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEE0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFED6()
{
	__asm(
	".thumb\n"
		"BFC R2, #16, #16\n"
		"STRB R5, [R9,#0x3BA]\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEE2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEE0_thumb)
		);
}

// patch for 0x2EFEE6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEF2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEE6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pNaviNodes)
		"LDR R5, [R0,R5]\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"ADD R0, R5, R0,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFEF2_thumb)
		);
}

// patch for 0x2EFF18
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF20_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF18()
{
	__asm(
	".thumb\n"
		"BFC R2, #16, #16\n"
		"STRB R5, [R9,#0x3BA]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF20_thumb)
		);
}

// patch for 0x2EFF28
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF30_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF28()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pNaviNodes)
		"LDR R5, [R0,R5]\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF30_thumb)
		);
}

// patch for 0x2EFF3C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF44_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF3C()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF44_thumb)
		);
}

// patch for 0x2EFF4A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF54_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF4A()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, R2,LSL#1\n"
		"ADD R0, 0x10\n"
		"ADD R0, R5\n"
		"VLD1.64 {Q9}, [R0]\n"
		"POP {R0, R1}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"LDR R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF54_thumb)
		);
}

// patch for 0x2EFF60
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF6C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF60()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF6C_thumb)
		);
}

// patch for 0x2EFF70
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF80_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF70()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		"MOV R2, R1,LSL#1\n"
		"ADD R2, 0x10\n"
		"ADD R2, R0\n"
		"VLD1.64 {Q9}, [R2]\n"
		"POP {R2, R3}\n"
		"STR R0, [SP,#0xD8+"/* var_6C */"-0x6C]\n"
		"ADD R0, SP, #0xD8+"/* var_6C */"-0x6C\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2EFF80_thumb)
		);
}

// patch for 0x2F0030
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2F0038 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2F0048_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2F0030()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R9\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2F0038)
		"LDR R0, [R0]\n"
		"UBFX R2, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		"MOV R4, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pNaviNodes)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2F0048_thumb)
		);
}

// patch for 0x2F0054
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2F0060_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2F0054()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R9\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R1, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2F0060_thumb)
		);
}

// patch for 0x2F0064
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2F006C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2F0064()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"ADD R0, R1, R0,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToChaseCar_2F006C_thumb)
		);
}

// patch for 0x2F0156
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0162_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0156()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"LDRD R3, R6, [R10,#0x3A0]\n"
		"LDRH R5, [R10,#0x394]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0162_thumb)
		);
}

// patch for 0x2F016A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0176_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F016A()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R9, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"LDR R8, [R12]\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3AC\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [SP,#0x4]\n"
		"STR R1, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R1, [R10,#0x3AC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0176_thumb)
		);
}

// patch for 0x2F018C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0194_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F018C()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"STR R9, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R9, [R10,#0x3A8]\n"
		"STRB R12, [R10,#0x3B9]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0194_thumb)
		);
}

// patch for 0x2F0198
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F01A0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0198()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"LDR R1, [R0,R1]\n"
		"LSRS R0, R2, #0x10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F01A0_thumb)
		);
}

// patch for 0x2F01A4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F01B0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F01A4()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R2, R8, R11,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F01B0_thumb)
		);
}

// patch for 0x2F01E4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F01F0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F01E4()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviLinks)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"LDR R5, [R1,R5,LSL#2]\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"STR R5, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R5, [R10,#0x3AA]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F01F0_thumb)
		);
}

// patch for 0x2F020C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0214 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0216_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F020C()
{
	__asm(
	".thumb\n"
		"UBFX R1, R5, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0214)
		"BFC R5, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0216_thumb)
		);
}

// patch for 0x2F0220
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0228_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0220()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pNaviNodes)
		"LDR R6, [R0,R6]\n"
		"MOV R0, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0228_thumb)
		);
}

// patch for 0x2F0304
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F030C = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F030E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0304()
{
	__asm(
	".thumb\n"
		"UBFX R1, R5, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F030C)
		"BFC R5, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F030E_thumb)
		);
}

// patch for 0x2F0318
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0320_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0318()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pNaviNodes)
		"LDR R6, [R0,R6]\n"
		"MOV R0, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0320_thumb)
		);
}

// patch for 0x2F0328
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0330_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0328()
{
	__asm(
	".thumb\n"
		"MOV R1, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"LDR R0, =("/* ThePaths_ptr */"0x677378 - 0x2F033C)\n"
		"ADD R4, SP, #0xC0+"/* var_78 */"-0x78\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0330_thumb)
		);
}

// patch for 0x2F0334
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F033C = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F033E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0334()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R3}\n"
		"MOV R0, R1,LSL#1\n"
		"ADD R0, 0x10\n"
		"ADD R0, R6\n"
		"VLD1.64 {Q9}, [R0]\n"
		"POP {R0, R3}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F033C)
		"ADD R1, R6, R1,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F033E_thumb)
		);
}

// patch for 0x2F0342
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0352_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0342()
{
	__asm(
	".thumb\n"
		"UBFX R2, R9, #16, #16\n"
		"BFC R9, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0352_thumb)
		);
}

// patch for 0x2F035C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0364_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F035C()
{
	__asm(
	".thumb\n"
		"MOV R2, R9\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"LDRSB R1, [R1,#8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0364_thumb)
		);
}

// patch for 0x2F0368
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0370_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0368()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"VMOV S0, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0370_thumb)
		);
}

// patch for 0x2F037C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0384_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F037C()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R3}\n"
		"MOV R1, R2,LSL#1\n"
		"ADD R1, 0x10\n"
		"ADD R1, R0\n"
		"VLD1.64 {Q10}, [R1]\n"
		"POP {R1, R3}\n"
		"VMUL.F32 D18, D18, D16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0384_thumb)
		);
}

// patch for 0x2F038A



// patch for 0x2F045E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0466 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0468_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F045E()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0466)
		"LDRSB R4, [R10,#0x3BB]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0468_thumb)
		);
}

// patch for 0x2F046C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F047C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F046C()
{
	__asm(
	".thumb\n"
		"UBFX R0, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		"MOV R6, R8\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pNaviNodes)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F047C_thumb)
		);
}

// patch for 0x2F0494
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04A4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0494()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"LDRSB R5, [R10,#0x3BC]\n"
		"UBFX R1, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04A4_thumb)
		);
}

// patch for 0x2F04A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04B0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04A8()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"ADD R0, R1, R0,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04B0_thumb)
		);
}

// patch for 0x2F04B8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04C0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04B8()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMOV.F32 S4, #0.125\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04C0_thumb)
		);
}

// patch for 0x2F04CE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04DA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04CE()
{
	__asm(
	".thumb\n"
		"UBFX R2, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		"VMUL.F32 S2, S28, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04DA_thumb)
		);
}

// patch for 0x2F04DE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04EE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04DE()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"MOV R3, R1,LSL#1\n"
		"ADD R3, 0x10\n"
		"LDR R3, [R2,R3]\n"
		"ADD R1, R2, R1,LSL#1\n"
		"LDR R2, [R1,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F04EE_thumb)
		);
}

// patch for 0x2F052C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F053C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F052C()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMUL.F32 S0, S8, S0\n"
		"UBFX R2, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F053C_thumb)
		);
}

// patch for 0x2F0540
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0550_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0540()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"ADD R3, R2, R0,LSL#1\n"
		"PUSH {R1, R3}\n"
		"MOV R1, R0,LSL#1\n"
		"ADD R1, 0x10\n"
		"LDR R0, [R2,R1]\n"
		"POP {R1, R3}\n"
		"LDR R6, [R3,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F0550_thumb)
		);
}

// patch for 0x2F062E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F06A8_thumb = 0;	// loc_2F06A8
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F063E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F062E()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CBZ R1, 1f\n"
		"LSRS R2, R0, #0x10\n"
		"MOVS R5, #0\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F063E_thumb)

		// Branches
		"1:\n"	// loc_2F06A8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeToFollowPath_2F06A8_thumb)
		);
}

// patch for 0x2F0706
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0AE2_thumb = 0;	// loc_2F0AE2
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0710_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0706()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0710_thumb)

		// Branches
		"1:\n"	// loc_2F0AE2
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0AE2_thumb)
		);
}

// patch for 0x2F0726
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0730 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0730_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0726()
{
	__asm(
	".thumb\n"
		"MOV R4, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0730)
		"UXTH R2, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0730_thumb)
		);
}

// patch for 0x2F0736
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0742_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0736()
{
	__asm(
	".thumb\n"
		"MOV R2, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R1,R5]\n"
		"ADD R6, R0, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0742_thumb)
		);
}

// patch for 0x2F0892
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F089E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0892()
{
	__asm(
	".thumb\n"
		"MOV R0, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"LDR R3, [R6,#0x1C]\n"
		"LDR R4, [R6,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F089E_thumb)
		);
}

// patch for 0x2F08A6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F08B2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F08A6()
{
	__asm(
	".thumb\n"
		"LDR R5, [R6,#0x20]\n"
		"VMOV S8, R3\n"
		"LDR R1, [R0,#0x1C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F08B2_thumb)
		);
}

// patch for 0x2F08B6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F08C2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F08B6()
{
	__asm(
	".thumb\n"
		"LDR R2, [R0,#0x20]\n"
		"VMOV S4, R5\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F08C2_thumb)
		);
}

// patch for 0x2F0918
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0920_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0918()
{
	__asm(
	".thumb\n"
		"LDR R0, [R6,#0x1C]\n"
		"LDR R1, [R6,#0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0920_thumb)
		);
}

// patch for 0x2F0A50
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0A58_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0A50()
{
	__asm(
	".thumb\n"
		"LDR R0, [R6,#0x1C]\n"
		"VMOV.F32 S4, #0.125\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0A58_thumb)
		);
}

// patch for 0x2F0A64
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0A72_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0A64()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x20\n"
		"ADD R1, R6\n"
		"VLD1.64 {Q8}, [R1]\n"
		"POP {R1, R2}\n"
		"STR R0, [SP,#0x60+"/* var_40 */"-0x40]\n"
		"ADD R0, R5, #0x30\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0A72_thumb)
		);
}

// patch for 0x2F0A78



// patch for 0x2F0B36
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0B42_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0B36()
{
	__asm(
	".thumb\n"
		"LDR R0, [R6,#0x1C]\n"
		"VMOV.F32 S0, #0.125\n"
		"LDR R1, [R6,#0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0B42_thumb)
		);
}

// patch for 0x2F0B44
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0B4E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0B44()
{
	__asm(
	".thumb\n"
		"LDR R2, [R6,#0x24]\n"
		"ADD R3, SP, #0x60+"/* var_30 */"-0x30\n"
		"VMOV S4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__IsThisAnAppropriateNode_2F0B4E_thumb)
		);
}

// patch for 0x2F0CD2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D94_thumb = 0;	// loc_2F0D94
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0CDC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0CD2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(LR, Offset_CPathFind__m_pPathNodes)
		"LDR LR, [R6,LR]\n"
		"CMP LR, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0CDC_thumb)

		// Branches
		"1:\n"	// loc_2F0D94
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D94_thumb)
		);
}

// patch for 0x2F0CE6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0CF0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0CE6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R6,R5]\n"
		"CMP R5, #0\n"
		"BEQ 1f\n"
		"LDR R6, =("/* ThePaths_ptr */"0x677378 - 0x2F0CF4)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0CF0_thumb)

		// Branches
		"1:\n"	// loc_2F0D94
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D94_thumb)
		);
}

// patch for 0x2F0CF8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D00_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0CF8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, Offset_CPathFind__m_pPathNodes)
		"LDR R12, [R6,R12]\n"
		"CMP R12, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D00_thumb)
		);
}

// patch for 0x2F0D04
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D12_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D04()
{
	__asm(
	".thumb\n"
		"MOV R1, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LSRS R4, R0, #0x10\n"
		"MOV R0, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D12_thumb)
		);
}

// patch for 0x2F0D18
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D20_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D18()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x14\n"
		"ADD R1, R0\n"
		"VLD1.64 {Q9}, [R1]\n"
		"POP {R1, R2}\n"
		"ADD R0, R5, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D20_thumb)
		);
}

// patch for 0x2F0D22
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D32_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D22()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x14\n"
		"ADD R1, R0\n"
		"VLD1.64 {Q10}, [R1]\n"
		"POP {R1, R2}\n"
		"VMOV.I32 D16, #0x3E000000\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D32_thumb)
		);
}

// patch for 0x2F0D5E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D68_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D5E()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R0, R12, R0,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D68_thumb)
		);
}

// patch for 0x2F0D6A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D76_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D6A()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x14\n"
		"ADD R1, R0\n"
		"VLD1.64 {Q9}, [R1]\n"
		"POP {R1, R2}\n"
		"VCVT.F32.S32 D18, D18\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindPathDirection_2F0D76_thumb)
		);
}

// patch for 0x2F0E3E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1838_thumb = 0;	// loc_2F1838
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E48_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E3E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R11,R1]\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E48_thumb)

		// Branches
		"1:\n"	// loc_2F1838
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1838_thumb)
		);
}

// patch for 0x2F0E5E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E68_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E5E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R10,R1]\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E68_thumb)

		// Branches
		"1:\n"	// loc_2F1838
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1838_thumb)
		);
}

// patch for 0x2F0E6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E74 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E76_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E6C()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R6, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E74)
		"LDR R3, [R2]\n"
		"LSRS R2, R6, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E76_thumb)
		);
}

// patch for 0x2F0E7A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E84_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E7A()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"CMP R3, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E84_thumb)

		// Branches
		"1:\n"	// loc_2F1838
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1838_thumb)
		);
}

// patch for 0x2F0E8A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E94_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E8A()
{
	__asm(
	".thumb\n"
		"LDR R3, =("/* ThePaths_ptr */"0x677378 - 0x2F0E9A)\n"
		"MOV R4, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E94_thumb)
		);
}

// patch for 0x2F0E98
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0EA0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0E98()
{
	__asm(
	".thumb\n"
		"BFC R6, #16, #16\n"
		"ADD R1, R1, R4,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0EA0_thumb)
		);
}

// patch for 0x2F0EA6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0EB0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0EA6()
{
	__asm(
	".thumb\n"
		"MOV R0, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"LDRH R1, [R1,#0x18]\n"
		"AND R5, R1, #0xF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0EB0_thumb)
		);
}

// patch for 0x2F0EB6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0EC0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0EB6()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"ADD R0, R1, R0,LSL#1\n"
		"LDRH R1, [R0,#4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0EC0_thumb)
		);
}

// patch for 0x2F0F1C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0F26_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0F1C()
{
	__asm(
	".thumb\n"
		"MOV R1, R11\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"STR R1, [SP,#0xE0+"/* var_D4 */"-0xD4]\n"
		"MOV R1, R10\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0F26_thumb)
		);
}

// patch for 0x2F0F4C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0F54_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0F4C()
{
	__asm(
	".thumb\n"
		"MOV R2, R1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pNaviLinks)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0F54_thumb)
		);
}

// patch for 0x2F0FE0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0FEA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0FE0()
{
	__asm(
	".thumb\n"
		"MOV R9, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R9, SizeOfCPathNodeDividedBy4)
		"LDR R1, [SP,#0xE0+"/* var_94 */"-0x94]\n"
		"ADD R0, R0, R9,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F0FEA_thumb)
		);
}

// patch for 0x2F1002
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F10F2_thumb = 0;	// loc_2F10F2
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F100C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1002()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		"LDR R0, [SP,#0xE0+"/* var_80 */"-0x80]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F100C_thumb)

		// Branches
		"1:\n"	// loc_2F10F2
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F10F2_thumb)
		);
}

// patch for 0x2F102E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F103E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F102E()
{
	__asm(
	".thumb\n"
		"LDR R6, [R1,R0,LSL#2]\n"
		"LDR R1, [SP,#0xE0+"/* var_AC */"-0xAC]\n"
		"LSRS R0, R6, #16\n"
		"ADD R1, R1, R0,LSL#2\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F103E_thumb)
		);
}

// patch for 0x2F1060
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F106C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1060()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pNaviNodes)
		"LDR R2, [R0,R2]\n"
		"MOV LR, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(LR, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F106C_thumb)
		);
}

// patch for 0x2F10A4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F10AE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F10A4()
{
	__asm(
	".thumb\n"
		"UBFX R4, R6, #16, #16\n"
		"LDR R5, [SP,#0xE0+"/* var_CC */"-0xCC]\n"
		"LDRH R1, [R1,#0xB]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F10AE_thumb)
		);
}

// patch for 0x2F10B6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F10C0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F10B6()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R4, [R4,R0]\n"
		"POP {R0, R1}\n"
		"LSLS R1, R1, #0x10\n"
		"ADD R5, R4, LR,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F10C0_thumb)
		);
}

// patch for 0x2F111A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1124_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F111A()
{
	__asm(
	".thumb\n"
		"MOV R11, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R11, Offset_CPathFind__m_pNaviLinks)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"STR R0, [SP,#0xE0+"/* var_94 */"-0x94]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1124_thumb)
		);
}

// patch for 0x2F11B0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1276_thumb = 0;	// loc_2F1276
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F11B8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F11B0()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F11B8_thumb)

		// Branches
		"1:\n"	// loc_2F1276
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1276_thumb)
		);
}

// patch for 0x2F11D8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F11E0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F11D8()
{
	__asm(
	".thumb\n"
		"LDR R5, [R1,R0,LSL#2]\n"
		"LDR R1, [SP,#0xE0+"/* var_A0 */"-0xA0]\n"
		"LSRS R0, R5, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F11E0_thumb)
		);
}

// patch for 0x2F11E4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F11EC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F11E4()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F11EC_thumb)

		// Branches
		"1:\n"	// loc_2F1276
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1276_thumb)
		);
}

// patch for 0x2F11F6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1202_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F11F6()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1202_thumb)
		);
}

// patch for 0x2F124A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1254_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F124A()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1254_thumb)
		);
}

// patch for 0x2F1266
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1270_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1266()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R0, R0, R1,LSL#2\n"
		"LDRH R0, [R0,#0x18]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1270_thumb)
		);
}

// patch for 0x2F12A2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F12AC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F12A2()
{
	__asm(
	".thumb\n"
		"MOV R11, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R11, Offset_CPathFind__m_pNaviLinks)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"STR R0, [SP,#0xE0+"/* var_94 */"-0x94]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F12AC_thumb)
		);
}

// patch for 0x2F132E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F13B8_thumb = 0;	// loc_2F13B8
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F133A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F132E()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		"LDR R1, [R4,#0x394]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F133A_thumb)

		// Branches
		"1:\n"	// loc_2F13B8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F13B8_thumb)
		);
}

// patch for 0x2F1356
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1366_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1356()
{
	__asm(
	".thumb\n"
		"LDR R5, [R1,R0,LSL#2]\n"
		"LDR R1, [SP,#0xE0+"/* var_A0 */"-0xA0]\n"
		"LSRS R0, R5, #16\n"
		"ADD R1, R1, R0,LSL#2\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1366_thumb)
		);
}

// patch for 0x2F1372
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F137E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1372()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F137E_thumb)
		);
}

// patch for 0x2F13C6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F13D0_thumb = 0;	// loc_2F13D0
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F13C6()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R5, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STR R0, [R4,#0x398]\n"
		"MOV R3, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F13D0_thumb)
		);
}

// patch for 0x2F13DC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F13E4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F13DC()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R6, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R10, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F13E4_thumb)
		);
}

// patch for 0x2F13F8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1404_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F13F8()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R2\n"
		"ADD R0, R0, #0x3AC\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"STR R6, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R6, [R2,#0x3AC]\n"
		"LDR R2, [SP,#0xE0+"/* var_80 */"-0x80]\n"
		"ADD R0, R1\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R2\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"STR R10, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R10, [R2,#0x3A8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1404_thumb)
		);
}

// patch for 0x2F1412
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F141E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1412()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R12\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"STR R5, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R5, [R12,#0x3AA]\n"
		"STRB R4, [R12,#0x3BB]\n"
		"STR R0, [R12,#0x3A0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F141E_thumb)
		);
}

// patch for 0x2F1430
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F143A = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1438_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1430()
{
	__asm(
	".thumb\n"
		"MOV R9, R5,LSR#16\n"
		"MOVS R1, #0xFF\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F143A)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1438_thumb)
		);
}

// patch for 0x2F1442
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14C6_thumb = 0;	// loc_2F14C6
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F144C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1442()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CBZ R0, 1f\n"
		"LDR R0, =("/* ThePaths_ptr */"0x677378 - 0x2F1456)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F144C_thumb)

		// Branches
		"1:\n"	// loc_2F14C6
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14C6_thumb)
		);
}

// patch for 0x2F144E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1456 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1458_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F144E()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1456)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1458_thumb)
		);
}

// patch for 0x2F145E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F146A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F145E()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"ADD R0, R0, R1,LSL#1\n"
		"LDRH R0, [R0,#0xB]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F146A_thumb)
		);
}

// patch for 0x2F1484
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F148C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1484()
{
	__asm(
	".thumb\n"
		"MOV R9, R5,LSR#16\n"
		"MOV R8, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F148C_thumb)
		);
}

// patch for 0x2F1498
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14CA_thumb = 0;	// loc_2F14CA
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14A2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1498()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CBZ R0, 1f\n"
		"LDR R0, =("/* ThePaths_ptr */"0x677378 - 0x2F14AC)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14A2_thumb)

		// Branches
		"1:\n"	// loc_2F14CA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14CA_thumb)
		);
}

// patch for 0x2F14A4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14AC = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14AE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14A4()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14AC)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14AE_thumb)
		);
}

// patch for 0x2F14B4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14B4()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"ADD R0, R0, R1,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14BC_thumb)
		);
}

// patch for 0x2F14DE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14E8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14DE()
{
	__asm(
	".thumb\n"
		"BFC R11, #16, #16\n"
		"LDR R5, [R0]\n"
		"LSRS R0, R4, #0x10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14E8_thumb)
		);
}

// patch for 0x2F14EA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14EA()
{
	__asm(
	".thumb\n"
		"MOV R6, R5\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pPathNodes)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"UXTH R2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F14F4_thumb)
		);
}

// patch for 0x2F1502
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F150C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1502()
{
	__asm(
	".thumb\n"
		"MOV R1, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LDR R3, [R0,#0x1C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F150C_thumb)
		);
}

// patch for 0x2F1510
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1518_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1510()
{
	__asm(
	".thumb\n"
		"LDR R0, [R0,#0x20]\n"
		"LDR R2, [R1,#0x1C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1518_thumb)
		);
}

// patch for 0x2F151C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F152C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F151C()
{
	__asm(
	".thumb\n"
		"LDR R1, [R1,#0x20]\n"
		"VMOV S2, R0\n"
		"MOV R0, R5\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"MOV R3, R11\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F152C_thumb)
		);
}

// patch for 0x2F154C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1558_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F154C()
{
	__asm(
	".thumb\n"
		"UBFX R2, R10, #16, #16\n"
		"ADD R1, R1, R3,LSL#1\n"
		"BFC R10, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1558_thumb)
		);
}

// patch for 0x2F1578
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1580_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1578()
{
	__asm(
	".thumb\n"
		"MOV R2, R10\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"VCVT.F32.S32 S22, S8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1580_thumb)
		);
}

// patch for 0x2F165A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1666_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F165A()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMUL.F32 S0, S24, S20\n"
		"LDRSB R4, [R8,#0x3BB]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1666_thumb)
		);
}

// patch for 0x2F1670
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1684_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1670()
{
	__asm(
	".thumb\n"
		"UBFX R2, R1, #16, #16\n"
		"VMUL.F32 S6, S28, S20\n"
		"BFC R1, #16, #16\n"
		"MOV R5, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pNaviNodes)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1684_thumb)
		);
}

// patch for 0x2F16AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F16BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F16AC()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R8\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"LDRSB R6, [R8,#0x3BC]\n"
		"UBFX R1, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F16BC_thumb)
		);
}

// patch for 0x2F16C0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F16C8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F16C0()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"ADD R0, R1, R0,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F16C8_thumb)
		);
}

// patch for 0x2F16D0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F16D8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F16D0()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R8\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMOV S10, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F16D8_thumb)
		);
}

// patch for 0x2F16E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F16E8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F16E0()
{
	__asm(
	".thumb\n"
		"UBFX R2, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F16E8_thumb)
		);
}

// patch for 0x2F16F0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1700_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F16F0()
{
	__asm(
	".thumb\n"
		"MOV R3, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCCarPathLinkDividedBy2)
		"ADD R1, R2, R3,LSL#1\n"
		"PUSH {R0, R1}\n"
		"MOV R0, R3,LSL#1\n"
		"ADD R0, 0x10\n"
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"LDR R4, [R1,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1700_thumb)
		);
}

// patch for 0x2F1740
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1750_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1740()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R8\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMUL.F32 S0, S6, S0\n"
		"UBFX R3, R2, #16, #16\n"
		"BFC R2, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1750_thumb)
		);
}

// patch for 0x2F1754
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1764_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1754()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"ADD R6, R3, R2,LSL#1\n"
		"PUSH {R0, R1}\n"
		"MOV R0, R2,LSL#1\n"
		"ADD R0, 0x10\n"
		"LDR R2, [R3,R0]\n"
		"POP {R0, R1}\n"
		"LDR R5, [R6,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__PickNextNodeForPlayer_2F1764_thumb)
		);
}

// patch for 0x2F1A06
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F19F0_thumb = 0;	// loc_2F19F0
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A12_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A06()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"BEQ 1f\n"
		"LDR R12, =("/* ThePaths_ptr */"0x677378 - 0x2F1A1A)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A12_thumb)

		// Branches
		"1:\n"	// loc_2F19F0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F19F0_thumb)
		);
}

// patch for 0x2F1A24
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A2C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A24()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, Offset_CPathFind__m_pPathNodes)
		"LDR R12, [R3,R12]\n"
		"CMP R12, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A2C_thumb)
		);
}

// patch for 0x2F1A34
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A3C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A34()
{
	__asm(
	".thumb\n"
		"MOV R1, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LSLS R4, R4, #3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A3C_thumb)
		);
}

// patch for 0x2F1A48
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A54_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A48()
{
	__asm(
	".thumb\n"
		"LDR R2, [R1,#0x1C]\n"
		"LDR R3, [R1,#0x20]\n"
		"LDR R1, [R1,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A54_thumb)
		);
}

// patch for 0x2F1A68
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A68()
{
	__asm(
	".thumb\n"
		"LDR R3, [R2,#0x1C]\n"
		"LDR R4, [R2,#0x20]\n"
		"LDR R2, [R2,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindGhostRoadHeight_2F1A74_thumb)
		);
}

// patch for 0x2F3A14
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A1C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A14()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"MOV R6, #0xFFFF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A1C_thumb)
		);
}

// patch for 0x2F3A2C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A36_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A2C()
{
	__asm(
	".thumb\n"
		"LSRS R1, R0, #16\n"
		"ADD R2, R2, R1,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A36_thumb)
		);
}

// patch for 0x2F3A38
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A40_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A38()
{
	__asm(
	".thumb\n"
		"BEQ 500f\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		"CMP R2, R6\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A40_thumb)
		);
}

// patch for 0x2F3A46
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A4E = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A56_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A46()
{
	__asm(
	".thumb\n"
		"MOV LR, R2,LSR#16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A4E)
		"LDR R5, [R3]\n"
		"ADD R5, R5, LR,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R5,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A56_thumb)
		);
}

// patch for 0x2F3A74
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A82_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A74()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"CMP R3, #0\n"
		"ITT NE\n"
		"LDRHNE R3, [R4,#0x398]\n"
		"CMPNE R3, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A82_thumb)
		);
}

// patch for 0x2F3A94
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3AC8_thumb = 0;	// loc_2F3AC8
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A9C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A94()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"CBZ R3, 1f\n"
		"LDR R3, [R4,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A9C_thumb)

		// Branches
		"1:\n"	// loc_2F3AC8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3AC8_thumb)
		);
}

// patch for 0x2F3AEA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3AF6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3AEA()
{
	__asm(
	".thumb\n"
		"BFC R0, #16, #16\n"
		"LDRSB R5, [R4,#0x3B9]\n"
		"BFC R2, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3AF6_thumb)
		);
}

// patch for 0x2F3B00
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B0A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B00()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"STR R3, [SP,#0xB0+"/* var_78 */"-0x78]\n"
		"VMOV S0, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B0A_thumb)
		);
}

// patch for 0x2F3B16
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B22_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B16()
{
	__asm(
	".thumb\n"
		"MOV R9, R3\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R9, Offset_CPathFind__m_pNaviNodes)
		"VCVT.F32.S32 S16, S0\n"
		"LDR R1, [R9,R1,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B22_thumb)
		);
}

// patch for 0x2F3B2A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B36_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B2A()
{
	__asm(
	".thumb\n"
		"MOV R1, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"LDRSB R2, [R0,#9]\n"
		"ADD R1, R3, R1,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B36_thumb)
		);
}

// patch for 0x2F3B62
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B6E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B62()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"VCVT.F32.S32 S30, S24\n"
		"LDRSB R2, [R4,#0x3BC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B6E_thumb)
		);
}

// patch for 0x2F3B88
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B90_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B88()
{
	__asm(
	".thumb\n"
		"UBFX R0, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3B90_thumb)
		);
}

// patch for 0x2F3BA0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3BA8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3BA0()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"VMUL.F32 S18, S18, S24\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3BA8_thumb)
		);
}

// patch for 0x2F3BB8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3BC0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3BB8()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R12, [R0]\n"
		"STR R12, [SP,#0x10]\n"
		"POP {R0-R3,R12,LR}\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3BC0_thumb)
		);
}

// patch for 0x2F3BCE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3BDA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3BCE()
{
	__asm(
	".thumb\n"
		"UBFX R1, R12, #16, #16\n"
		"BFC R0, #16, #16\n"
		"UBFX R3, R2, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3BDA_thumb)
		);
}

// patch for 0x2F3BE2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3BEE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3BE2()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"LDR R5, [R4,#0x5A4]\n"
		"VMOV.F32 S16, #0.125\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3BEE_thumb)
		);
}

// patch for 0x2F3BF2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3C00_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3BF2()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		"MOV R2, R0,LSL#1\n"
		"ADD R2, 0x10\n"
		"LDR R0, [R1,R2]\n"
		"POP {R2, R3}\n"
		"MOV R1, R2\n"
		"VMUL.F32 S0, S0, S27\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3C00_thumb)
		);
}

// patch for 0x2F3C06
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3C12_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3C06()
{
	__asm(
	".thumb\n"
		"LDR R6, [R6,#0x14]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"VMOV S6, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3C12_thumb)
		);
}

// patch for 0x2F3C16
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3C20_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3C16()
{
	__asm(
	".thumb\n"
		"MOV R0, R1,LSL#1\n"
		"ADD R0, 0x10\n"
		"LDR R0, [R3,R0]\n"
		"IT EQ\n"
		"VMOVEQ.F32 S17, S4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3C20_thumb)
		);
}

// patch for 0x2F3C36
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3C42_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3C36()
{
	__asm(
	".thumb\n"
		"LDR R1, [R1,#0x14]\n"
		"VMOV S4, R0\n"
		"ADD R6, R4, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3C42_thumb)
		);
}

// patch for 0x2F3E20
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E28 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E2A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E20()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E28)
		"LDR R2, [R1]\n"
		"LSRS R1, R0, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E2A_thumb)
		);
}

// patch for 0x2F3E2E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F4422_thumb = 0;	// loc_2F4422
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E38_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E2E()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E38_thumb)

		// Branches
		"1:\n"	// loc_2F4422
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F4422_thumb)
		);
}

// patch for 0x2F3E3C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E44 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E48_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E3C()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R3, [R0]\n"
		"STR R3, [SP,#0xC]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E44)
		"LDR R2, [R2]\n"
		"UBFX R3, R3, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E48_thumb)
		);
}

// patch for 0x2F3E4C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E56_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E4C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E56_thumb)

		// Branches
		"1:\n"	// loc_2F4422
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F4422_thumb)
		);
}

// patch for 0x2F3E5A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E66 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E68_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E5A()
{
	__asm(
	".thumb\n"
		"BFC R0, #16, #16\n"
		"LDRSB R5, [R4,#0x3BB]\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E66)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E68_thumb)
		);
}

// patch for 0x2F3E6A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E76_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E6A()
{
	__asm(
	".thumb\n"
		"MOV R9, R2\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R9, Offset_CPathFind__m_pNaviNodes)
		"LDR R1, [R9,R1,LSL#2]\n"
		"ADD R0, R1, R0,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E76_thumb)
		);
}

// patch for 0x2F3E86
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E94_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E86()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R12, [R0]\n"
		"STR R12, [SP,#0x10]\n"
		"POP {R0-R3,R12,LR}\n"
		"MOV R1, R12\n"
		"UBFX R0, R12, #16, #16\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E94_thumb)
		);
}

// patch for 0x2F3E98
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3EA0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3E98()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"VADD.F32 S0, S2, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3EA0_thumb)
		);
}

// patch for 0x2F3EA4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3EAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3EA4()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		"MOV R2, R1,LSL#1\n"
		"ADD R2, 0x10\n"
		"LDR R0, [R0,R2]\n"
		"POP {R2, R3}\n"
		"LDR R3, [R2,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3EAC_thumb)
		);
}

// patch for 0x2F3EEC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3EF8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3EEC()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R3, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3EF8_thumb)
		);
}

// patch for 0x2F3F04
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3F0C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3F04()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"ADD R0, R3, R0,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3F0C_thumb)
		);
}

// patch for 0x2F3F8C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3F94_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3F8C()
{
	__asm(
	".thumb\n"
		"UBFX R2, R12, #16, #16\n"
		"BFC R12, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3F94_thumb)
		);
}

// patch for 0x2F3FB0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3FB8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3FB0()
{
	__asm(
	".thumb\n"
		"MOV R2, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3FB8_thumb)
		);
}

// patch for 0x2F3FBC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3FC4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3FBC()
{
	__asm(
	".thumb\n"
		"MOV R3, R2,LSL#1\n"
		"ADD R3, 0x10\n"
		"LDR R3, [R0,R3]\n"
		"ADD R0, R0, R2,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3FC4_thumb)
		);
}

// patch for 0x2F3FCC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3FD4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3FCC()
{
	__asm(
	".thumb\n"
		"LDR R0, [R0,#0x14]\n"
		"VMOV S2, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3FD4_thumb)
		);
}

// patch for 0x2F41A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41B0 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41B2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41A8()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41B0)
		"LDRSB R5, [R4,#0x3BB]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41B2_thumb)
		);
}

// patch for 0x2F41B4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41C4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41B4()
{
	__asm(
	".thumb\n"
		"UBFX R2, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		"MOV R6, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pNaviNodes)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41C4_thumb)
		);
}

// patch for 0x2F41DC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41E8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41DC()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R0, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41E8_thumb)
		);
}

// patch for 0x2F41EC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41FA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41EC()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"MOV R6, R9\n"
		"VADD.F32 S0, S2, S0\n"
		"MOV R2, R1,LSL#1\n"
		"ADD R2, 0x10\n"
		"LDR R2, [R0,R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F41FA_thumb)
		);
}

// patch for 0x2F4208
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F4210_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F4208()
{
	__asm(
	".thumb\n"
		"LDR R0, [R0,#0x14]\n"
		"VMUL.F32 S0, S0, S27\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F4210_thumb)
		);
}

// patch for 0x2F467C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F474E_thumb = 0;	// loc_2F474E
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4684_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F467C()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"CMP R0, R6\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4684_thumb)

		// Branches
		"1:\n"	// loc_2F474E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F474E_thumb)
		);
}

// patch for 0x2F4688
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4690 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4690_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4688()
{
	__asm(
	".thumb\n"
		"MOV R12, R0,LSR#16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4690)
		"LDR R1, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4690_thumb)
		);
}

// patch for 0x2F4694
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F46A2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4694()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CMP R1, #0\n"
		"BEQ 500f\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R10, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"CMP R10, R6\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F46A2_thumb)
		);
}

// patch for 0x2F46A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F46B0 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F46B0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F46A8()
{
	__asm(
	".thumb\n"
		"MOV LR, R10,LSR#16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F46B0)
		"LDR R1, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F46B0_thumb)
		);
}

// patch for 0x2F46B4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F46C6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F46B4()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CMP R1, #0\n"
		"ITTT NE\n"
		"ADDNE R9, R4, #0x394\n"
		"LDRHNE R1, [R9]\n"
		"CMPNE R1, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F46C6_thumb)
		);
}

// patch for 0x2F46DC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F46EA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F46DC()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CMP R1, #0\n"
		"ITT NE\n"
		"LDRHNE R1, [R4,#0x398]\n"
		"CMPNE R1, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F46EA_thumb)
		);
}

// patch for 0x2F4700
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F470A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4700()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CBZ R1, 1f\n"
		"STR R8, [SP,#0x120+"/* var_C4 */"-0xC4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F470A_thumb)

		// Branches
		"1:\n"	// loc_2F474E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F474E_thumb)
		);
}

// patch for 0x2F478C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4794_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F478C()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		"VMOV.F32 S16, #0.125\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4794_thumb)
		);
}

// patch for 0x2F479A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47A4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F479A()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"LDR R5, [R5]\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pNaviNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47A4_thumb)
		);
}

// patch for 0x2F47AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47B4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47AC()
{
	__asm(
	".thumb\n"
		"MOV R5, R1,LSL#1\n"
		"ADD R5, 0x10\n"
		"LDR R5, [R3,R5]\n"
		"ADD R1, R3, R1,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47B4_thumb)
		);
}

// patch for 0x2F47B6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47C2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47B6()
{
	__asm(
	".thumb\n"
		"LDR R1, [R1,#0x14]\n"
		"BFC R3, #16, #16\n"
		"VMOV S2, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47C2_thumb)
		);
}

// patch for 0x2F47C6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47D6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47C6()
{
	__asm(
	".thumb\n"
		"MOV R1, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"VCVT.F32.S32 S0, S0\n"
		"VCVT.F32.S32 S2, S2\n"
		"MOV R3, R1,LSL#1\n"
		"ADD R3, 0x10\n"
		"LDR R3, [R6,R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47D6_thumb)
		);
}

// patch for 0x2F47DA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47E6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47DA()
{
	__asm(
	".thumb\n"
		"LDR R1, [R1,#0x14]\n"
		"VMOV S4, R1\n"
		"ADD R1, R4, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F47E6_thumb)
		);
}

// patch for 0x2F497A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4984_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F497A()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"LDR R5, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4984_thumb)
		);
}

// patch for 0x2F4994
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F49A0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4994()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AC\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [SP,#0x8]\n"
		"STR R1, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R2, [R4,#0x3AC]\n"
		"ADD R2, R5, R12,LSL#2\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [SP,#0x0]\n"
		"STR R1, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R0, [R4,#0x3A8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F49A0_thumb)
		);
}

// patch for 0x2F49A6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F49B8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F49A6()
{
	__asm(
	".thumb\n"
		"STRB R8, [R4,#0x3B9]\n"
		"STRB R1, [R4,#0x3BB]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F49B8_thumb)
		);
}

// patch for 0x2F49CE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F49D8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F49CE()
{
	__asm(
	".thumb\n"
		"LDRH R1, [R4,#0x398]\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"LSLS R2, R2, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F49D8_thumb)
		);
}

// patch for 0x2F49FC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4A08_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F49FC()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviLinks)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"LDR R10, [R3,R2,LSL#1]\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"STR R10, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R10, [R4,#0x3AA]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4A08_thumb)
		);
}

// patch for 0x2F4B60
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4B68_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4B60()
{
	__asm(
	".thumb\n"
		"STR R0, [R9,R6,LSL#2]\n"
		"UXTH R0, R4\n"
		"CMP R0, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4B68_thumb)
		);
}

// patch for 0x2F4B7E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4B88_thumb = 0;	// loc_2F4B88
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4B7E()
{
	__asm(
	".thumb\n"
		"ADD R0, R3, R6,LSL#2\n"
		"STR R1, [R9,R6,LSL#2]\n"
		"STRH R1, [R0,#8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4B88_thumb)
		);
}

// patch for 0x2F4C70
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4C78_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4C70()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"LDRD R9, R4, [SP,#0x120+"/* var_E0 */"-0xE0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4C78_thumb)
		);
}

// patch for 0x2F4C80
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4C88 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4C8C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4C80()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4C88)
		"LDR R0, [R0]\n"
		"UBFX R2, R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4C8C_thumb)
		);
}

// patch for 0x2F4C92
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CA2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4C92()
{
	__asm(
	".thumb\n"
		"BFC R2, #16, #16\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"MOV R3, R2,LSL#1\n"
		"ADD R3, 0x10\n"
		"LDR R3, [R0,R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CA2_thumb)
		);
}

// patch for 0x2F4CA6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CB0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CA6()
{
	__asm(
	".thumb\n"
		"LDR R0, [R0,#0x14]\n"
		"VMOV S2, R3\n"
		"ADD R3, SP, #0x120+"/* var_70 */"-0x70\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CB0_thumb)
		);
}

// patch for 0x2F4CCE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_19E228_arm = 0;	// j__ZN8CCarCtrl27ClipTargetOrientationToLinkEP8CVehicle12CLinkAddressaPfff
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CDA_thumb = 0;	// loc_2F4CDA
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CCE()
{
	__asm(
	".thumb\n"
		"VSTR S0, [SP,#0x120+"/* var_11C */"-0x11C]\n"
		"BL 1f\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R5, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CDA_thumb)

		// Branches
		"1:\n"	// j__ZN8CCarCtrl27ClipTargetOrientationToLinkEP8CVehicle12CLinkAddressaPfff
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_19E228_arm)
		);
}

// patch for 0x2F4CDE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CEA = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CE8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CDE()
{
	__asm(
	".thumb\n"
		"UBFX R1, R5, #16, #16\n"
		"VMOV.I32 D18, #0x3E000000\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CEA)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CE8_thumb)
		);
}

// patch for 0x2F4CF4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4D04_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4CF4()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"PUSH {R2, R3}\n"
		"MOV R2, R1,LSL#1\n"
		"ADD R2, 0x10\n"
		"ADD R2, R0\n"
		"VLD1.64 {Q8}, [R2]\n"
		"POP {R2, R3}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4D04_thumb)
		);
}

// patch for 0x2F4D08



// patch for 0x2F4D12



// patch for 0x2F4D82
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4D8C = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4D8C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4D82()
{
	__asm(
	".thumb\n"
		"UBFX R1, R6, #16, #16\n"
		"ADD R3, SP, #0x120+"/* var_70 */"-0x70\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4D8C)
		"LDR R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4D8C_thumb)
		);
}

// patch for 0x2F4D92
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4DA2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4D92()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"MOV R2, R1,LSL#1\n"
		"ADD R2, 0x10\n"
		"LDR R2, [R0,R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4DA2_thumb)
		);
}

// patch for 0x2F4DA8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4DB0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4DA8()
{
	__asm(
	".thumb\n"
		"LDR R0, [R0,#0x14]\n"
		"VMOV S2, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4DB0_thumb)
		);
}

// patch for 0x2F4DE6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4DEE = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4DF2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4DE6()
{
	__asm(
	".thumb\n"
		"UBFX R2, R0, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4DEE)
		"LDR R1, [R1]\n"
		"ADD R1, R1, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4DF2_thumb)
		);
}

// patch for 0x2F4DF4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E04_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4DF4()
{
	__asm(
	".thumb\n"
		"BFC R2, #16, #16\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"MOV R3, R2,LSL#1\n"
		"ADD R3, 0x10\n"
		"LDR R3, [R1,R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E04_thumb)
		);
}

// patch for 0x2F4E08
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E10_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E08()
{
	__asm(
	".thumb\n"
		"LDR R1, [R1,#0x14]\n"
		"VMOV S2, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E10_thumb)
		);
}

// patch for 0x2F4E56
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E5E = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E62_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E56()
{
	__asm(
	".thumb\n"
		"UBFX R2, R0, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E5E)
		"LDR R1, [R1]\n"
		"ADD R1, R1, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E62_thumb)
		);
}

// patch for 0x2F4E64
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E64()
{
	__asm(
	".thumb\n"
		"BFC R2, #16, #16\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"MOV R3, R2,LSL#1\n"
		"ADD R3, 0x10\n"
		"LDR R3, [R1,R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E74_thumb)
		);
}

// patch for 0x2F4E78
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E80_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E78()
{
	__asm(
	".thumb\n"
		"LDR R1, [R1,#0x14]\n"
		"VMOV S2, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4E80_thumb)
		);
}

// patch for 0x2F4EC6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4ECE = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4ED2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4EC6()
{
	__asm(
	".thumb\n"
		"UBFX R2, R0, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4ECE)
		"LDR R1, [R1]\n"
		"ADD R1, R1, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4ED2_thumb)
		);
}

// patch for 0x2F4ED4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4EE4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4ED4()
{
	__asm(
	".thumb\n"
		"BFC R2, #16, #16\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"MOV R3, R2,LSL#1\n"
		"ADD R3, 0x10\n"
		"LDR R3, [R1,R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4EE4_thumb)
		);
}

// patch for 0x2F4EE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4EF0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4EE8()
{
	__asm(
	".thumb\n"
		"LDR R1, [R1,#0x14]\n"
		"VMOV S2, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4EF0_thumb)
		);
}

// patch for 0x2F4F26
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F2E = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F36_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F26()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F2E)
		"LDR R0, [R0]\n"
		"UBFX R2, R1, #16, #16\n"
		"MOV R5, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pNaviNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F36_thumb)
		);
}

// patch for 0x2F4F3C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F48_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F3C()
{
	__asm(
	".thumb\n"
		"BFC R2, #16, #16\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"MOV R3, R2,LSL#1\n"
		"ADD R3, 0x10\n"
		"LDR R3, [R0,R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F48_thumb)
		);
}

// patch for 0x2F4F4C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F54_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F4C()
{
	__asm(
	".thumb\n"
		"LDR R0, [R0,#0x14]\n"
		"VMOV S2, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F54_thumb)
		);
}

// patch for 0x2F4F7C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F88_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F7C()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMOV.F32 S4, #5.0\n"
		"UBFX R0, R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F88_thumb)
		);
}

// patch for 0x2F4F8A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F9A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F8A()
{
	__asm(
	".thumb\n"
		"BFC R2, #16, #16\n"
		"LDR R0, [R5,R0,LSL#2]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"PUSH {R1, R3}\n"
		"MOV R1, R2,LSL#1\n"
		"ADD R1, 0x10\n"
		"ADD R1, R0\n"
		"VLD1.64 {Q8}, [R1]\n"
		"POP {R1, R3}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4F9A_thumb)
		);
}

// patch for 0x2F4F9E



// patch for 0x2F5018
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F5020_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F5018()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMUL.F32 S10, S2, S1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F5020_thumb)
		);
}

// patch for 0x2F5026
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F5030_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F5026()
{
	__asm(
	".thumb\n"
		"UBFX R3, R2, #16, #16\n"
		"LDR R0, [R0]\n"
		"BFC R2, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F5030_thumb)
		);
}

// patch for 0x2F5034
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F5040_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F5034()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"VSUB.F32 S4, S4, S2\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F5040_thumb)
		);
}

// patch for 0x2F5044
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F504C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F5044()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R3}\n"
		"MOV R1, R2,LSL#1\n"
		"ADD R1, 0x10\n"
		"LDR R0, [R0,R1]\n"
		"POP {R1, R3}\n"
		"LDR R3, [R3,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F504C_thumb)
		);
}

// patch for 0x2F50B8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50C0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50B8()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R10\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMOV.F32 S6, #1.0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50C0_thumb)
		);
}

// patch for 0x2F50C4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50CE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50C4()
{
	__asm(
	".thumb\n"
		"UBFX R2, R1, #16, #16\n"
		"LDR R0, [R0]\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50CE_thumb)
		);
}

// patch for 0x2F50D2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50DE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50D2()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"VDIV.F32 S2, S2, S4\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50DE_thumb)
		);
}

// patch for 0x2F50E2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50EE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50E2()
{
	__asm(
	".thumb\n"
		"LDR R2, [R2,#0x14]\n"
		"VMOV S4, R2\n"
		"VSUB.F32 S6, S6, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50EE_thumb)
		);
}

// patch for 0x2F50F2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50FE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50F2()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		"MOV R2, R1,LSL#1\n"
		"ADD R2, 0x10\n"
		"LDR R0, [R0,R2]\n"
		"POP {R2, R3}\n"
		"VMUL.F32 S10, S2, S1\n"
		"VMUL.F32 S0, S2, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F50FE_thumb)
		);
}

// patch for 0x2F6C2C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6D1A_thumb = 0;	// loc_2F6D1A
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C34_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C2C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R0,R1]\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C34_thumb)

		// Branches
		"1:\n"	// loc_2F6D1A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6D1A_thumb)
		);
}

// patch for 0x2F6C44
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C4C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C44()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C4C_thumb)

		// Branches
		"1:\n"	// loc_2F6D1A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6D1A_thumb)
		);
}

// patch for 0x2F6C56
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C60_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C56()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"VMOV.F32 S0, #0.125\n"
		"LSRS R3, R3, #0x10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C60_thumb)
		);
}

// patch for 0x2F6C68
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C72_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C68()
{
	__asm(
	".thumb\n"
		"ADD R2, R2, #8\n"
		"LDR R1, [R2,#0x14]\n"
		"STR R2, [SP,#0x68+"/* var_54 */"-0x54]\n"
		"VMOV S2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C72_thumb)
		);
}

// patch for 0x2F6C76
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C80_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C76()
{
	__asm(
	".thumb\n"
		"ADD R2, R2, #2\n"
		"LDR R1, [R2,#0x16]\n"
		"STR R2, [SP,#0x68+"/* var_58 */"-0x58]\n"
		"MOV R2, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6C80_thumb)
		);
}

// patch for 0x2F6CA2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6CAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6CA2()
{
	__asm(
	".thumb\n"
		"ADD R11, R11, #0xA\n"
		"LDR R0, [R11,#0x16]\n"
		"MOV R9, R11\n"
		"VMOV S2, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6CAC_thumb)
		);
}

// patch for 0x2F6CB0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6CB8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6CB0()
{
	__asm(
	".thumb\n"
		"ADD R9, R9, #-2\n"
		"LDR R0, [R9,#0x14]\n"
		"VMOV S4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6CB8_thumb)
		);
}

// patch for 0x2F6D2E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6D3A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6D2E()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R10, R4, #4\n"
		"ADD R0, R1, R0,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6D3A_thumb)
		);
}

// patch for 0x2F6D56
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6D60_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6D56()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x14\n"
		"LDR R0, [R9,R0]\n"
		"MOV R6, R1\n"
		"MOV R1, 0x16\n"
		"LDR R1, [R11,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6D60_thumb)
		);
}

// patch for 0x2F6DA4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6DAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6DA4()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x16\n"
		"LDR R0, [R6,R0]\n"
		"MOV R1, 0x14\n"
		"LDR R1, [R8,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkPerpendicular_2F6DAC_thumb)
		);
}

// patch for 0x2F6EE4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6FC4_thumb = 0;	// loc_2F6FC4
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6EEC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6EE4()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6EEC_thumb)

		// Branches
		"1:\n"	// loc_2F6FC4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6FC4_thumb)
		);
}

// patch for 0x2F6EFC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F04_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6EFC()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"CMP R3, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F04_thumb)

		// Branches
		"1:\n"	// loc_2F6FC4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6FC4_thumb)
		);
}

// patch for 0x2F6F12
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F1C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F12()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LSRS R2, R2, #0x10\n"
		"VMOV.F32 S0, #0.125\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F1C_thumb)
		);
}

// patch for 0x2F6F20
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F30_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F20()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R0, R3, R0,LSL#2\n"
		"ADD R6, R6, #8\n"
		"LDR R3, [R6,#0x14]\n"
		"LDR R1, [R0,#0x1C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F30_thumb)
		);
}

// patch for 0x2F6F34
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F3C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F34()
{
	__asm(
	".thumb\n"
		"LDR R2, [R0,#0x20]\n"
		"LDR R12, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F3C_thumb)
		);
}

// patch for 0x2F6F40
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F48_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F40()
{
	__asm(
	".thumb\n"
		"LDR R3, [R6,#0x18]\n"
		"LDR R0, [R6,#0x1C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6F48_thumb)
		);
}

// patch for 0x2F6FA6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6FB2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6FA6()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R6\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R1}\n"
		"VCVT.F32.S32 D16, D16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6FB2_thumb)
		);
}

// patch for 0x2F6FD8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6FE0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6FD8()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R0, R0, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6FE0_thumb)
		);
}

// patch for 0x2F6FE2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6FEE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6FE2()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x14\n"
		"ADD R1, R0\n"
		"VLD1.64 {Q8}, [R1]\n"
		"POP {R1, R2}\n"
		"VCVT.F32.S32 D16, D16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerAICarParkParallel_2F6FEE_thumb)
		);
}

// patch for 0x2F778A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7792 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7796_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F778A()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7792)
		"LDR R5, [R7,#"/* arg_0 */"0x8]\n"
		"LDR R2, [R2]\n"
		"LSRS R4, R0, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7796_thumb)
		);
}

// patch for 0x2F779A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7A02_thumb = 0;	// loc_2F7A02
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77A4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F779A()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77A4_thumb)

		// Branches
		"1:\n"	// loc_2F7A02
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7A02_thumb)
		);
}

// patch for 0x2F77A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77B0 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77B2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77A8()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77B0)
		"LDR R6, [R3]\n"
		"LSRS R3, R2, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77B2_thumb)
		);
}

// patch for 0x2F77B6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77C0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77B6()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R6,R0]\n"
		"POP {R0, R1}\n"
		"CMP R6, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77C0_thumb)

		// Branches
		"1:\n"	// loc_2F7A02
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7A02_thumb)
		);
}

// patch for 0x2F77C2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77CE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77C2()
{
	__asm(
	".thumb\n"
		"BFC R0, #16, #16\n"
		"LDR R5, =("/* ThePaths_ptr */"0x677378 - 0x2F77DA)\n"
		"BFC R2, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77CE_thumb)
		);
}

// patch for 0x2F77D2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77DA = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77DC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77D2()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R5, Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77DA)
		"LDRSB R6, [R11,#0x3BB]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77DC_thumb)
		);
}

// patch for 0x2F77EA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77F6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77EA()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pNaviNodes)
		"VMOV S0, R6\n"
		"VCVT.F32.S32 S16, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F77F6_thumb)
		);
}

// patch for 0x2F7802
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F780E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7802()
{
	__asm(
	".thumb\n"
		"MOV R1, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"LDRSB R2, [R0,#9]\n"
		"ADD R1, R3, R1,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F780E_thumb)
		);
}

// patch for 0x2F783A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7846_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F783A()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"VCVT.F32.S32 S30, S24\n"
		"LDRSB R2, [R11,#0x3BC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7846_thumb)
		);
}

// patch for 0x2F7862
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F786E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7862()
{
	__asm(
	".thumb\n"
		"UBFX R0, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		"VMUL.F32 S18, S18, S24\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F786E_thumb)
		);
}

// patch for 0x2F787A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7886_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F787A()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"ADD R0, R0, R1,LSL#1\n"
		"VMUL.F32 S17, S0, S27\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7886_thumb)
		);
}

// patch for 0x2F788E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F789A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F788E()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R6, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R2, [R0]\n"
		"STR R2, [SP,#0x8]\n"
		"POP {R0-R3,R12,LR}\n"
		"VMUL.F32 S18, S18, S20\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F789A_thumb)
		);
}

// patch for 0x2F78A4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78B0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78A4()
{
	__asm(
	".thumb\n"
		"UBFX R1, R6, #16, #16\n"
		"BFC R0, #16, #16\n"
		"UBFX R3, R2, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78B0_thumb)
		);
}

// patch for 0x2F78B8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78C0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78B8()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"LDR R3, [R5,R3,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78C0_thumb)
		);
}

// patch for 0x2F78C8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78D6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78C8()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		"MOV R2, R0,LSL#1\n"
		"ADD R2, 0x10\n"
		"LDR R0, [R1,R2]\n"
		"POP {R2, R3}\n"
		"MOV R1, R2\n"
		"VMUL.F32 S0, S0, S27\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78D6_thumb)
		);
}

// patch for 0x2F78DA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78E6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78DA()
{
	__asm(
	".thumb\n"
		"LDR R5, [R5,#0x14]\n"
		"VMUL.F32 S20, S22, S20\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78E6_thumb)
		);
}

// patch for 0x2F78EC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78F6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78EC()
{
	__asm(
	".thumb\n"
		"MOV R0, R1,LSL#1\n"
		"ADD R0, 0x10\n"
		"LDR R0, [R3,R0]\n"
		"IT EQ\n"
		"VMOVEQ.F32 S17, S4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F78F6_thumb)
		);
}

// patch for 0x2F790C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7914_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F790C()
{
	__asm(
	".thumb\n"
		"LDR R1, [R1,#0x14]\n"
		"VMOV S4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7914_thumb)
		);
}

// patch for 0x2F7B0C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B14 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B16_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B0C()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B14)
		"LDR R2, [R1]\n"
		"LSRS R1, R0, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B16_thumb)
		);
}

// patch for 0x2F7B1A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F802C_thumb = 0;	// loc_2F802C
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B24_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B1A()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B24_thumb)

		// Branches
		"1:\n"	// loc_2F802C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F802C_thumb)
		);
}

// patch for 0x2F7B28
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B30 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B34_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B28()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R3, [R0]\n"
		"STR R3, [SP,#0xC]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B30)
		"LDR R2, [R2]\n"
		"UBFX R3, R3, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B34_thumb)
		);
}

// patch for 0x2F7B38
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B42_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B38()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B42_thumb)

		// Branches
		"1:\n"	// loc_2F802C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F802C_thumb)
		);
}

// patch for 0x2F7B46
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B52 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B54_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B46()
{
	__asm(
	".thumb\n"
		"BFC R0, #16, #16\n"
		"LDRSB R6, [R11,#0x3BB]\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B52)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B54_thumb)
		);
}

// patch for 0x2F7B56
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B62_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B56()
{
	__asm(
	".thumb\n"
		"MOV R5, R2\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pNaviNodes)
		"LDR R1, [R5,R1,LSL#2]\n"
		"ADD R0, R1, R0,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B62_thumb)
		);
}

// patch for 0x2F7B72
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B80_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B72()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R6, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"MOV R1, R6\n"
		"UBFX R0, R6, #16, #16\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B80_thumb)
		);
}

// patch for 0x2F7B84
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B8C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B84()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"VADD.F32 S0, S2, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B8C_thumb)
		);
}

// patch for 0x2F7B90
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B98_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B90()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		"MOV R2, R1,LSL#1\n"
		"ADD R2, 0x10\n"
		"LDR R0, [R0,R2]\n"
		"POP {R2, R3}\n"
		"LDR R3, [R2,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7B98_thumb)
		);
}

// patch for 0x2F7BDA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7BE6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7BDA()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R3, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7BE6_thumb)
		);
}

// patch for 0x2F7BF2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7BFE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7BF2()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"ADD R0, R3, R0,LSL#1\n"
		"LDRSB R3, [R2,#8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7BFE_thumb)
		);
}

// patch for 0x2F7C7A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7C86_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7C7A()
{
	__asm(
	".thumb\n"
		"UBFX R2, R6, #16, #16\n"
		"BFC R6, #16, #16\n"
		"VMUL.F32 S6, S17, S20\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7C86_thumb)
		);
}

// patch for 0x2F7C9E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7CAE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7C9E()
{
	__asm(
	".thumb\n"
		"MOV R2, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"VMUL.F32 S4, S4, S12\n"
		"MOV R3, R2,LSL#1\n"
		"ADD R3, 0x10\n"
		"LDR R3, [R0,R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7CAE_thumb)
		);
}

// patch for 0x2F7CBA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7CC4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7CBA()
{
	__asm(
	".thumb\n"
		"LDR R0, [R0,#0x14]\n"
		"VMOV S2, R0\n"
		"MOV R0, R4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7CC4_thumb)
		);
}

// patch for 0x2F7E96
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7E9E = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7EA0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7E96()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7E9E)
		"LDRSB R5, [R11,#0x3BB]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7EA0_thumb)
		);
}

// patch for 0x2F7EA2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7EB2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7EA2()
{
	__asm(
	".thumb\n"
		"UBFX R2, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		"MOV R6, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pNaviNodes)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7EB2_thumb)
		);
}

// patch for 0x2F7ECA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7ED6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7ECA()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R11\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"UBFX R0, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7ED6_thumb)
		);
}

// patch for 0x2F7EDA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7EE6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7EDA()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"VADD.F32 S0, S2, S0\n"
		"MOV R2, R1,LSL#1\n"
		"ADD R2, 0x10\n"
		"LDR R2, [R0,R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7EE6_thumb)
		);
}

// patch for 0x2F7EF4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7EFC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7EF4()
{
	__asm(
	".thumb\n"
		"LDR R0, [R0,#0x14]\n"
		"VMUL.F32 S0, S0, S27\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__SteerPlayerWhilstCruising_2F7EFC_thumb)
		);
}

// patch for 0x2F83A4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83B0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83A4()
{
	__asm(
	".thumb\n"
		"UBFX R0, R1, #16, #16\n"
		"ADD R5, R5, R0,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R5,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83B0_thumb)
		);
}

// patch for 0x2F83BE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83CA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83BE()
{
	__asm(
	".thumb\n"
		"UBFX R5, R2, #16, #16\n"
		"ADD R4, R4, R5,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [R4,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83CA_thumb)
		);
}

// patch for 0x2F83D4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83DE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83D4()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		"STR R6, [SP,#0x98+"/* var_7C */"-0x7C]\n"
		"VMOV.I32 D18, #0x3E000000\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83DE_thumb)
		);
}

// patch for 0x2F83E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83E8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83E0()
{
	__asm(
	".thumb\n"
		"MOV R12, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R12, SizeOfCCarPathLinkDividedBy2)
		"ADD R6, R11, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83E8_thumb)
		);
}

// patch for 0x2F83F0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83FC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83F0()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pNaviNodes)
		"LDR LR, [R4,R0,LSL#2]\n"
		"PUSH {R1, R2}\n"
		"MOV R1, R12,LSL#1\n"
		"ADD R1, 0x10\n"
		"ADD R1, LR\n"
		"VLD1.64 {Q8}, [R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F83FC_thumb)
		);
}

// patch for 0x2F8400



// patch for 0x2F840A



// patch for 0x2F8446
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F8452_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F8446()
{
	__asm(
	".thumb\n"
		"BFC R2, #16, #16\n"
		"LDR R4, [R7,#"/* arg_8 */"0x10]\n"
		"STR R6, [SP,#0x98+"/* var_84 */"-0x84]\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F8452_thumb)
		);
}

// patch for 0x2F846A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F8470 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F8478_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F846A()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x10\n"
		"ADD R0, R5\n"
		"VLD1.64 {Q9}, [R0]\n"
		"POP {R0, R1}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F8470)
		"STR R2, [SP,#0x98+"/* var_6C */"-0x6C]\n"
		"UBFX R2, R3, #16, #16\n"
		"BFC R3, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F8478_thumb)
		);
}

// patch for 0x2F847A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F848E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F847A()
{
	__asm(
	".thumb\n"
		"ADD R1, R1, R2,LSL#2\n"
		"MOV R2, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F848E_thumb)
		);
}

// patch for 0x2F849C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F84A4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F849C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R4}\n"
		"MOV R0, R2,LSL#1\n"
		"ADD R0, 0x10\n"
		"ADD R0, R1\n"
		"VLD1.64 {Q10}, [R0]\n"
		"POP {R0, R4}\n"
		"STR R3, [SP,#0x98+"/* var_68 */"-0x68]\n"
		"ADD R3, SP, #0x98+"/* var_68 */"-0x68\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F84A4_thumb)
		);
}

// patch for 0x2F84A8



// patch for 0x2F84E4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F84EA = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F84F2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F84E4()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x10\n"
		"ADD R0, R5\n"
		"VLD1.64 {Q10}, [R0]\n"
		"POP {R0, R1}\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F84EA)
		"STR R3, [SP,#0x98+"/* var_74 */"-0x74]\n"
		"UBFX R3, R0, #16, #16\n"
		"BFC R0, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F84F2_thumb)
		);
}

// patch for 0x2F84F4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F84FE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F84F4()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		"LDR R1, [R7,#"/* arg_10 */"0x18]\n"
		"ADD R2, R2, R3,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F84FE_thumb)
		);
}

// patch for 0x2F8500
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F8508_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F8500()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F8508_thumb)
		);
}

// patch for 0x2F850A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F8514_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F850A()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R3}\n"
		"MOV R1, R0,LSL#1\n"
		"ADD R1, 0x10\n"
		"ADD R1, R2\n"
		"VLD1.64 {Q9}, [R1]\n"
		"POP {R1, R3}\n"
		"STR R5, [SP,#0x98+"/* var_70 */"-0x70]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F8514_thumb)
		);
}

// patch for 0x2F8518



// patch for 0x2F8570
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F857A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F8570()
{
	__asm(
	".thumb\n"
		"MOV R4, 0x10\n"
		"LDR R4, [R5,R4]\n"
		"STR R5, [SP,#0x98+"/* var_80 */"-0x80]\n"
		"LDR R5, [R5,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__DealWithBend_Racing_2F857A_thumb)
		);
}

// patch for 0x2F8B5C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8B64 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8B64_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8B5C()
{
	__asm(
	".thumb\n"
		"UBFX R3, R1, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8B64)
		"MOV R9, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8B64_thumb)
		);
}

// patch for 0x2F8B6A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8DF0_thumb = 0;	// loc_2F8DF0
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8B74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8B6A()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8B74_thumb)

		// Branches
		"1:\n"	// loc_2F8DF0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8DF0_thumb)
		);
}

// patch for 0x2F8B80
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8B88_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8B80()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		"CMP R0, #0\n"
		"MOV R2, R11\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8B88_thumb)
		);
}

// patch for 0x2F8B96
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8BA2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8B96()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"VLDR S0, [R2]\n"
		"VSUB.F32 S2, S16, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8BA2_thumb)
		);
}

// patch for 0x2F8BB8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8BC0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8BB8()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"ADD R6, R3, R1,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__ClipTargetOrientationToLink_2F8BC0_thumb)
		);
}

// patch for 0x2F8E28
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindPercDependingOnDistToLink_2F8E30_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindPercDependingOnDistToLink_2F8E28()
{
	__asm(
	".thumb\n"
		"UBFX R3, R1, #16, #16\n"
		"BFC R1, #16, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindPercDependingOnDistToLink_2F8E30_thumb)
		);
}

// patch for 0x2F8E3A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindPercDependingOnDistToLink_2F8E4C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindPercDependingOnDistToLink_2F8E3A()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		"LDR R2, [R2]\n"
		"ADD R2, R2, R3,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"PUSH {R0, R3}\n"
		"MOV R0, R1,LSL#1\n"
		"ADD R0, 0x10\n"
		"ADD R0, R2\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R3}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindPercDependingOnDistToLink_2F8E4C_thumb)
		);
}

// patch for 0x2F8E50



// patch for 0x2F8E5C



// patch for 0x2FAE2C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FAE34_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FAE2C()
{
	__asm(
	".thumb\n"
		"MOV R6, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		"UXTH R0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FAE34_thumb)
		);
}

// patch for 0x2FAE3C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FAE44_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FAE3C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pNodeLinks)
		"LDR R3, [R2,R3]\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FAE44_thumb)
		);
}

// patch for 0x2FAFB6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FAFC2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FAFB6()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviLinks)
		"LDR R6, [R6,R0]\n"
		"POP {R0, R1}\n"
		"LDR R2, [R6,R2,LSL#2]\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [SP,#0x8]\n"
		"STR R1, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R2, [R4,#0x3AA]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FAFC2_thumb)
		);
}

// patch for 0x2FAFFA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB004_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FAFFA()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"MOV R6, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB004_thumb)
		);
}

// patch for 0x2FB016
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB022 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB020_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB016()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"MOV R10, #0\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R6, Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB022)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB020_thumb)
		);
}

// patch for 0x2FB064
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB06E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB064()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"UXTH R3, R0\n"
		"LDRH R5, [R4,#0x398]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB06E_thumb)
		);
}

// patch for 0x2FB07A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB084_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB07A()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"ADD R1, R6\n"
		"LDR R1, [R2,R1,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB084_thumb)
		);
}

// patch for 0x2FB098
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB16A_thumb = 0;	// loc_2FB16A
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB0A0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB098()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB0A0_thumb)

		// Branches
		"1:\n"	// loc_2FB16A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB16A_thumb)
		);
}

// patch for 0x2FB0A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB0B2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB0A8()
{
	__asm(
	".thumb\n"
		"MOV R0, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB0B2_thumb)
		);
}

// patch for 0x2FB0B6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB0C2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB0B6()
{
	__asm(
	".thumb\n"
		"LDR R3, [R0,#0x1C]\n"
		"LDR R5, [R0,#0x20]\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB0C2_thumb)
		);
}

// patch for 0x2FB0D4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB0DE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB0D4()
{
	__asm(
	".thumb\n"
		"VCVT.F32.S32 S2, S2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB0DE_thumb)
		);
}

// patch for 0x2FB0FE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB10A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB0FE()
{
	__asm(
	".thumb\n"
		"LDR R1, [R0,#0x1C]\n"
		"LDR R2, [R0,#0x20]\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB10A_thumb)
		);
}

// patch for 0x2FB174
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB17E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB174()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"MOV R3, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB17E_thumb)
		);
}

// patch for 0x2FB190
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB198_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB190()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"CMP R10, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB198_thumb)
		);
}

// patch for 0x2FB1B2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1B2()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviLinks)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"ADD R1, R2, R1,LSL#2\n"
		"LDR R2, =("/* ThePaths_ptr */"0x677378 - 0x2FB1C6)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1BC_thumb)
		);
}

// patch for 0x2FB1BE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1C6 = 0;
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1CC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1BE()
{
	__asm(
	".thumb\n"
		"LDR R1, [R1]\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1C6)
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [SP,#0x4]\n"
		"STR R1, [R0]\n"
		"POP {R0-R3,R12,LR}\n"
		"STRH R1, [R4,#0x3A8]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1CC_thumb)
		);
}

// patch for 0x2FB1D4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1DC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1D4()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"ADD R2, R2, R3,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1DC_thumb)
		);
}

// patch for 0x2FB1E6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1F2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1E6()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"ADD R1, R10, R2\n"
		"LDRH R2, [R0,R1,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindLinksToGoWithTheseNodes_2FB1F2_thumb)
		);
}

// patch for 0x2FB2FA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB304_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB2FA()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB304_thumb)
		);
}

// patch for 0x2FB410
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB418_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB410()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"STR R6, [R0,#0x18]\n"
		"LDR R0, [R5,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB418_thumb)
		);
}

// patch for 0x2FB448
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB450_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB448()
{
	__asm(
	".thumb\n"
		"MOV R0, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"MOVS R4, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB450_thumb)
		);
}

// patch for 0x2FB456
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB460_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB456()
{
	__asm(
	".thumb\n"
		"MOV R2, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB460_thumb)
		);
}

// patch for 0x2FB472
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB47E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB472()
{
	__asm(
	".thumb\n"
		"LDR R0, [R0,#0x24]\n"
		"MOVT R1, #0x447A\n"
		"VMOV S6, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__GenerateOneEmergencyServicesCar_2FB47E_thumb)
		);
}

// patch for 0x2FBB64
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBB6E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBB64()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"VMRS APSR_nzcv, FPSCR\n"
		"VCMPE.F32 S16, S4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBB6E_thumb)
		);
}

// patch for 0x2FBB7C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBB86_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBB7C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R2, R0\n"
		"VMRS APSR_nzcv, FPSCR\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBB86_thumb)
		);
}

// patch for 0x2FBBA4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBBAE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBBA4()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R3, R0\n"
		"VMRS APSR_nzcv, FPSCR\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBBAE_thumb)
		);
}

// patch for 0x2FBC2A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC38_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC2A()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimension)
		"ADD R4, R8, R1\n"
		"POP {R1, R2}\n"
		"LDR R0, [SP,#0xF8+"/* var_D8 */"-0xD8]\n"
		"ADD R0, R0, R4,LSL#2\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R0,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC38_thumb)
		);
}

// patch for 0x2FBC40
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC48_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC40()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_dwNumVehicleNodes)
		"ADD R2, R2, R4,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC48_thumb)
		);
}

// patch for 0x2FBC50
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC58_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC50()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"STR R0, [SP,#0xF8+"/* var_D0 */"-0xD0]\n"
		"ADDS R0, R2, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC58_thumb)
		);
}

// patch for 0x2FBC64
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC6C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC64()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pNodeLinks)
		"STR R2, [SP,#0xF8+"/* var_9C */"-0x9C]\n"
		"MOVS R2, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC6C_thumb)
		);
}

// patch for 0x2FBC8E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC9C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC8E()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"ADD R1, R1, R2,LSL#2\n"
		"MOV R8, R1\n"
		"PUSH {R0, R1}\n"
		"ADD R8, R8, #0xA\n"
		"MOV R0, 0x16\n"
		"ADD R0, R8\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC9C_thumb)
		);
}

// patch for 0x2FBC9E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBCAA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBC9E()
{
	__asm(
	".thumb\n"
		"ADD R5, R5, #-2\n"
		"LDR R3, [R5,#0x14]\n"
		"VMOV S0, R3\n"
		"VCVT.F32.S32 S0, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBCAA_thumb)
		);
}

// patch for 0x2FBCAE



// patch for 0x2FBD2A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBEDA_thumb = 0;	// loc_2FBEDA
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD38_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD2A()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		"MOV R2, 0x16\n"
		"LDR R2, [R8,R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD38_thumb)

		// Branches
		"1:\n"	// loc_2FBEDA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBEDA_thumb)
		);
}

// patch for 0x2FBD3A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD44_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD3A()
{
	__asm(
	".thumb\n"
		"MOV R3, 0x14\n"
		"LDR R3, [R5,R3]\n"
		"CMP R0, #0\n"
		"VMOV S0, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD44_thumb)
		);
}

// patch for 0x2FBD4E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD5A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD4E()
{
	__asm(
	".thumb\n"
		"MOV R2, 0x18\n"
		"LDR R2, [R6,R2]\n"
		"VCVT.F32.S32 S2, S2\n"
		"VMOV S4, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD5A_thumb)
		);
}

// patch for 0x2FBD68
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD68()
{
	__asm(
	".thumb\n"
		"VMUL.F32 S2, S2, S16\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD74_thumb)
		);
}

// patch for 0x2FBD8C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD98_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD8C()
{
	__asm(
	".thumb\n"
		"LDR R1, [R5,#0x1C]\n"
		"LDR R2, [R5,#0x20]\n"
		"LDR R3, [R5,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBD98_thumb)
		);
}

// patch for 0x2FBDFA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBE08_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBDFA()
{
	__asm(
	".thumb\n"
		"MOV R3, 0x16\n"
		"LDR R3, [R8,R3]\n"
		"MOV R10, R0\n"
		"LDR R0, [R5,#0x1C]\n"
		"LDR R1, [R5,#0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBE08_thumb)
		);
}

// patch for 0x2FBE0C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBE16_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBE0C()
{
	__asm(
	".thumb\n"
		"LDR R2, [R5,#0x24]\n"
		"MOV R5, R4\n"
		"VMOV S6, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBE16_thumb)
		);
}

// patch for 0x2FBE1A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBE24_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBE1A()
{
	__asm(
	".thumb\n"
		"MOV R3, 0x14\n"
		"LDR R3, [R5,R3]\n"
		"VMOV S2, R1\n"
		"ADD R0, SP, #0xF8+"/* var_8C */"-0x8C\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBE24_thumb)
		);
}

// patch for 0x2FBE34
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBE3C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBE34()
{
	__asm(
	".thumb\n"
		"MOV R1, 0x18\n"
		"LDR R1, [R6,R1]\n"
		"VCVT.F32.S32 S6, S6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarCtrl__FindNodesThisCarIsNearestTo_2FBE3C_thumb)
		);
}

// patch for 0x30D83C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CGangWars__CreateDefendingGroup_30D846_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGangWars__CreateDefendingGroup_30D83C()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGangWars__CreateDefendingGroup_30D846_thumb)
		);
}

// patch for 0x30D84E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CGangWars__CreateDefendingGroup_30D858_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGangWars__CreateDefendingGroup_30D84E()
{
	__asm(
	".thumb\n"
		"LDR R4, [R0,#0x24]\n"
		"ADD R0, SP, #0xC8+"/* var_78 */"-0x78\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R1\n"
		"VLD1.64 {Q4}, [R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGangWars__CreateDefendingGroup_30D858_thumb)
		);
}

// patch for 0x30D85C



// patch for 0x30DCA6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CGangWars__CreateDefendingGroup_30DCB0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGangWars__CreateDefendingGroup_30DCA6()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGangWars__CreateDefendingGroup_30DCB0_thumb)
		);
}

// patch for 0x30DCB8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CGangWars__CreateDefendingGroup_30DCC2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGangWars__CreateDefendingGroup_30DCB8()
{
	__asm(
	".thumb\n"
		"LDR R5, [R0,#0x24]\n"
		"ADD R0, SP, #0xC8+"/* var_78 */"-0x78\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R1\n"
		"VLD1.64 {Q7}, [R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGangWars__CreateDefendingGroup_30DCC2_thumb)
		);
}

// patch for 0x30DCC6



// patch for 0x315256
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Init_315260_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Init_315256()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_bForbiddenForScriptedCarsEnabled)
		"STRB R1, [R0,R2]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_dwNumForbiddenAreas)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Init_315260_thumb)
		);
}

// patch for 0x31526C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Init_315288_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Init_31526C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"STR R1, [R3,R0]\n"
		"POP {R0, R2}\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"STR R1, [R3,R0]\n"
		"POP {R0, R2}\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"STR R1, [R3,R0]\n"
		"POP {R0, R2}\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pLinkLengths)
		"STR R1, [R3,R0]\n"
		"POP {R0, R2}\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathIntersections)
		"STR R1, [R3,R0]\n"
		"POP {R0, R2}\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviLinks)
		"STR R1, [R3,R0]\n"
		"POP {R0, R2}\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_field_EA4)
		"STR R1, [R3,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Init_315288_thumb)
		);
}

// patch for 0x31528A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Init_315298_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Init_31528A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_interiorAreaIDarray_index_7)
		"MOV R2, #0xFFFF\n"
		"MOVT R2, #0xFFFF\n"
		"STR R2, [R0,R1]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_interiorAreaIDarray_index_6)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Init_315298_thumb)
		);
}

// patch for 0x31529A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Init_3152A4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Init_31529A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_interiorAreaIDarray_index_5)
		"STR R2, [R0,R1]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_interiorAreaIDarray_index_4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Init_3152A4_thumb)
		);
}

// patch for 0x3152A6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Init_3152B0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Init_3152A6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_interiorAreaIDarray_index_3)
		"STR R2, [R0,R1]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_interiorAreaIDarray_index_2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Init_3152B0_thumb)
		);
}

// patch for 0x3152B2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Init_3152BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Init_3152B2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_interiorAreaIDarray_index_1)
		"STR R2, [R0,R1]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_interiorAreaIDarray_index_0)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Init_3152BC_thumb)
		);
}

// patch for 0x3152C4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReInit_3152D0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__ReInit_3152C4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_dwNumForbiddenAreas)
		"MOVS R2, #0\n"
		"STR R2, [R0,R1]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_bForbiddenForScriptedCarsEnabled)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReInit_3152D0_thumb)
		);
}

// patch for 0x3152D4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReleaseRequestedNodes_3152DC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__ReleaseRequestedNodes_3152D4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_bForbiddenForScriptedCarsEnabled)
		"MOVS R2, #0\n"
		"STRB R2, [R0,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReleaseRequestedNodes_3152DC_thumb)
		);
}

// patch for 0x31535C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315364_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_31535C()
{
	__asm(
	".thumb\n"
		"MOV R8, R11\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R8, Offset_CPathFind__m_dwNumNodes)
		"MOV R0, R6\n"
		"MOVS R2, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315364_thumb)
		);
}

// patch for 0x31536A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315374_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_31536A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_dwNumVehicleNodes)
		"ADD R1, R11, R0\n"
		"MOV R0, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315374_thumb)
		);
}

// patch for 0x31537A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315384_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_31537A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_dwNumPedNodes)
		"ADD R1, R11, R0\n"
		"MOV R0, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315384_thumb)
		);
}

// patch for 0x31538A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315394_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_31538A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_dwNumCarPathLinks)
		"ADD R4, R11, R0\n"
		"MOV R0, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315394_thumb)
		);
}

// patch for 0x31539C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3153A4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_31539C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_dwNumAddresses)
		"ADD R5, R11, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3153A4_thumb)
		);
}

// patch for 0x3153AE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3153D6_thumb = 0;	// loc_3153D6
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3153B8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_3153AE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_dwNumNodes)
		"LDR R0, [R11,R0]\n"
		"CBZ R0, 1f\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3153B8_thumb)

		// Branches
		"1:\n"	// loc_3153D6
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3153D6_thumb)
		);
}

// patch for 0x3153C0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3153CC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_3153C0()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"STR R1, [R11,R0]\n"
		"POP {R0, R2}\n"
		"LDR R0, [R8]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3153CC_thumb)
		);
}

// patch for 0x3153D6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_19CF5C_arm = 0;	// j__ZN10CMemoryMgr6MallocEj
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3153E0_thumb = 0;	// loc_3153E0
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_3153D6()
{
	__asm(
	".thumb\n"
		"MOVS R0, #0x1C\n"
		"BL 1f\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"STR R0, [R11,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3153E0_thumb)

		// Branches
		"1:\n"	// j__ZN10CMemoryMgr6MallocEj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_19CF5C_arm)
		);
}

// patch for 0x3153F0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3153FA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_3153F0()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"STR R1, [R11,R0]\n"
		"POP {R0, R2}\n"
		"LDR R0, [R4]\n"
		"RSB R0, R0, R0,LSL#3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3153FA_thumb)
		);
}

// patch for 0x31541A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31542A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_31541A()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"STR R0, [R11,R1]\n"
		"POP {R1, R2}\n"
		"LDR R0, [R5]\n"
		"LSLS R0, R0, #1\n"
		"BL 1f\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviLinks)
		"STR R0, [R11,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31542A_thumb)

		// Branches
		"1:\n"	// j__ZN10CMemoryMgr6MallocEj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_19CF5C_arm)
		);
}

// patch for 0x315432
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315442_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_315432()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pLinkLengths)
		"STR R0, [R11,R1]\n"
		"POP {R1, R2}\n"
		"LDR R0, [R5]\n"
		"ADDS R0, #0xC0\n"
		"BL 1f\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathIntersections)
		"STR R0, [R11,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315442_thumb)

		// Branches
		"1:\n"	// j__ZN10CMemoryMgr6MallocEj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_19CF5C_arm)
		);
}

// patch for 0x315444
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31544C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_315444()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"LDR R1, [R11,R1]\n"
		"ADD R2, R4, R0,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31544C_thumb)
		);
}

// patch for 0x315454
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31545C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_315454()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviLinks)
		"LDR R1, [R11,R1]\n"
		"LSLS R2, R0, #1\n"
		"MOV R0, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31545C_thumb)
		);
}

// patch for 0x315462
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31546C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_315462()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pLinkLengths)
		"LDR R1, [R11,R1]\n"
		"ADD R2, R0, #0xC0\n"
		"MOV R0, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31546C_thumb)
		);
}

// patch for 0x315472
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31547C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_315472()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathIntersections)
		"LDR R1, [R11,R1]\n"
		"ADD R2, R0, #0xC0\n"
		"MOV R0, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31547C_thumb)
		);
}

// patch for 0x315484
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315494_thumb = 0;	// loc_315494
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_315484()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviLinks)
		"STR R0, [R11,R1]\n"
		"POP {R1, R2}\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"STR R0, [R11,R1]\n"
		"POP {R1, R2}\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pLinkLengths)
		"STR R0, [R11,R1]\n"
		"POP {R1, R2}\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathIntersections)
		"STR R0, [R11,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315494_thumb)
		);
}

// patch for 0x31549C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3154A4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_31549C()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R11, Offset_CPathFind__m_pPathNodes)
		"MOVS R1, #0\n"
		"MOVS R2, #0x18\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3154A4_thumb)
		);
}

// patch for 0x3154C8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3154D0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_3154C8()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNode)
		"STRB R3, [R6,#2]\n"
		"LDR R0, [R8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3154D0_thumb)
		);
}

// patch for 0x3154D6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31553C_thumb = 0;	// loc_31553C
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3154E0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_3154D6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_dwNumForbiddenAreas)
		"LDR R1, [R0,R2]\n"
		"CMP R1, #1\n"
		"BLT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_3154E0_thumb)

		// Branches
		"1:\n"	// loc_31553C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31553C_thumb)
		);
}

// patch for 0x315544
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31554C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_315544()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_1024)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_field_1544)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_31554C_thumb)
		);
}

// patch for 0x31555C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315566_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_31555C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_1036)
		"ADD R1, R0\n"
		"VST1.32 {D16-D17}, [R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315566_thumb)
		);
}

// patch for 0x31556A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315578_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_31556A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_8)
		"ADD R1, R0\n"
		"VST1.32 {D16-D17}, [R1]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_1032)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315578_thumb)
		);
}

// patch for 0x31557E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315588_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadPathFindData_31557E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_12)
		"ADD R0, R1\n"
		"VST1.32 {D16-D17}, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadPathFindData_315588_thumb)
		);
}

// patch for 0x3155A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_3156F6_thumb = 0;	// loc_3156F6
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_3155B6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_3155A8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R12,R0]\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_dwNumVehicleNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_3155B6_thumb)

		// Branches
		"1:\n"	// loc_3156F6
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_3156F6_thumb)
		);
}

// patch for 0x3155BC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_3155C6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_3155BC()
{
	__asm(
	".thumb\n"
		"BNE 500f\n"
		"LDR R5, [R6]\n"
		"MOV R6, R12\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_dwNumNodes)
		"B 501f\n"
		"500:\n"	// else in IT block
		"MOV R5, #0\n"
		"501:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_3155C6_thumb)
		);
}

// patch for 0x3155D8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_3155E0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_3155D8()
{
	__asm(
	".thumb\n"
		"MOV R4, R12\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pPathNodes)
		"VMOV S22, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_3155E0_thumb)
		);
}

// patch for 0x315602
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_315612_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_315602()
{
	__asm(
	".thumb\n"
		"MOV R1, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R1, R0, R1,LSL#2\n"
		"LDR R0, [R1,#0x1C]\n"
		"LDR R6, [R1,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_315612_thumb)
		);
}

// patch for 0x31563A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_315646_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_31563A()
{
	__asm(
	".thumb\n"
		"LDR R0, [R1,#0x20]\n"
		"VMOV S2, R0\n"
		"VCVT.F32.S32 S2, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInAreaForOneRegion_315646_thumb)
		);
}

// patch for 0x315710
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UnLoadPathFindData_193D34_arm = 0;	// j__ZN10CMemoryMgr4FreeEPv
	uintptr_t Address_GTA_SA_2_00_CPathFind__UnLoadPathFindData_315720_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UnLoadPathFindData_315710()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R4,R0]\n"
		"CMP R0, #0\n"
		"IT NE\n"
		"BLNE 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R4,R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnLoadPathFindData_315720_thumb)

		// Branches
		"1:\n"	// j__ZN10CMemoryMgr4FreeEPv
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnLoadPathFindData_193D34_arm)
		);
}

// patch for 0x315728
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UnLoadPathFindData_315738_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UnLoadPathFindData_315728()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R0, [R4,R0]\n"
		"CMP R0, #0\n"
		"IT NE\n"
		"BLNE 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviLinks)
		"LDR R0, [R4,R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnLoadPathFindData_315738_thumb)

		// Branches
		"1:\n"	// j__ZN10CMemoryMgr4FreeEPv
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnLoadPathFindData_193D34_arm)
		);
}

// patch for 0x315740
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UnLoadPathFindData_315750_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UnLoadPathFindData_315740()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pLinkLengths)
		"LDR R0, [R4,R0]\n"
		"MOV R10, R4\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R10, Offset_CPathFind__m_pPathNodes)
		"MOV R6, R4\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pNaviNodes)
		"MOV R8, R4\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R8, Offset_CPathFind__m_pNodeLinks)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnLoadPathFindData_315750_thumb)
		);
}

// patch for 0x315752
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UnLoadPathFindData_315768_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UnLoadPathFindData_315752()
{
	__asm(
	".thumb\n"
		"MOV R9, R4\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R9, Offset_CPathFind__m_pNaviLinks)
		"MOV R5, R4\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pLinkLengths)
		"IT NE\n"
		"BLNE 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathIntersections)
		"LDR R0, [R4,R0]\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pPathIntersections)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnLoadPathFindData_315768_thumb)

		// Branches
		"1:\n"	// j__ZN10CMemoryMgr4FreeEPv
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnLoadPathFindData_193D34_arm)
		);
}

// patch for 0x31585C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315866_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_31585C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, Offset_CPathFind__m_dwTotalNumNodesInSearchList)
		"MOVS R4, #0\n"
		"STRD R2, R3, [SP,#0x70+"/* var_30 */"-0x30]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315866_thumb)
		);
}

// patch for 0x315886
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_3158B0_thumb = 0;	// loc_3158B0
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315890_thumb = 0;	// loc_315890
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315886()
{
	__asm(
	".thumb\n"
		"ADD R1, R0, R1,LSL#2\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CBNZ R1, 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315890_thumb)

		// Branches
		"1:\n"	// loc_3158B0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_3158B0_thumb)
		);
}

// patch for 0x3158CC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_3158D4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_3158CC()
{
	__asm(
	".thumb\n"
		"ADD R1, R2, R1,LSL#2\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_3158D4_thumb)
		);
}

// patch for 0x315938
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315940_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315938()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"MOV R3, R4\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315940_thumb)
		);
}

// patch for 0x31594C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315954_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_31594C()
{
	__asm(
	".thumb\n"
		"MOV R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"LDRH R1, [R11,#0x28]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315954_thumb)
		);
}

// patch for 0x315958
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315C06_thumb = 0;	// loc_315C06
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315960_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315958()
{
	__asm(
	".thumb\n"
		"LDRH R0, [R2,#0x28]\n"
		"CMP R0, R1\n"
		"BNE 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315960_thumb)

		// Branches
		"1:\n"	// loc_315C06
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315C06_thumb)
		);
}

// patch for 0x315A1A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315A24_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315A1A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"LDR R1, [R0,R1]\n"
		"LDR R1, [R1,R8,LSL#2]\n"
		"UXTH R3, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315A24_thumb)
		);
}

// patch for 0x315A28
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315B5A_thumb = 0;	// loc_315B5A
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315A32_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315A28()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R2,R5]\n"
		"CMP R5, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315A32_thumb)

		// Branches
		"1:\n"	// loc_315B5A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315B5A_thumb)
		);
}

// patch for 0x315A3C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315A48_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315A3C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pNaviLinks)
		"LDR R2, [R0,R2]\n"
		"MOV R6, R4\n"
		"LDR R2, [R2,R8,LSL#2]\n"
		"LSRS R4, R2, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315A48_thumb)
		);
}

// patch for 0x315A4C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315A7A_thumb = 0;	// loc_315A7A
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315A5E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315A4C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R4,R6]\n"
		"CBZ R6, 1f\n"
		"BFC R2, #16, #16\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R4, [R4,R0]\n"
		"POP {R0, R1}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315A5E_thumb)

		// Branches
		"1:\n"	// loc_315A7A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315A7A_thumb)
		);
}

// patch for 0x315AA2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315AB2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315AA2()
{
	__asm(
	".thumb\n"
		"BNE 500f\n"
		"MOV R1, LR\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R5, R5, R1,LSL#2\n"
		"LDRH R1, [R5,#0x18]\n"
		"EOR R1, R1, R12\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315AB2_thumb)
		);
}

// patch for 0x315ABE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315AC8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315ABE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pLinkLengths)
		"LDR R3, [R0,R3]\n"
		"MOV R0, R5\n"
		"LDRSH R2, [R10,#0xE]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315AC8_thumb)
		);
}

// patch for 0x315BF0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315BFC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315BF0()
{
	__asm(
	".thumb\n"
		"MOV R2, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315BFC_thumb)
		);
}

// patch for 0x315C8C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315C94_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315C8C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"LDR R1, [R6,R1]\n"
		"LDR R5, [R1,R3,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315C94_thumb)
		);
}

// patch for 0x315C9A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315CE4_thumb = 0;	// loc_315CE4
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315CAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315C9A()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CBZ R1, 1f\n"
		"MOV R12, R5,LSR#16\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pLinkLengths)
		"LDR R6, [R6,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315CAC_thumb)

		// Branches
		"1:\n"	// loc_315CE4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315CE4_thumb)
		);
}

// patch for 0x315CB0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315CBA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315CB0()
{
	__asm(
	".thumb\n"
		"MOV R2, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"LDRB R3, [R6,R3]\n"
		"ADD R2, R1, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315CBA_thumb)
		);
}

// patch for 0x315CD0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315CD8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315CD0()
{
	__asm(
	".thumb\n"
		"MOV R2, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"ADD R11, R1, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315CD8_thumb)
		);
}

// patch for 0x315D18
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__DoPathSearch_315D24_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__DoPathSearch_315D18()
{
	__asm(
	".thumb\n"
		"MOV R2, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__DoPathSearch_315D24_thumb)
		);
}

// patch for 0x315D56
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315D62_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315D56()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S2, fPathsMapMaxCoord)
		"VMOV S18, R6\n"
		"VSTR S0, [SP,#0x98+"/* var_40 */"-0x40]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315D62_thumb)
		);
}

// patch for 0x315D80
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315D88_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315D80()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R11, iNumberOfPathFilesPerDimensionMinusOne)
		"STRH R1, [SP,#0x98+"/* var_3C */"-0x3C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315D88_thumb)
		);
}

// patch for 0x315DA0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315DAA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315DA0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimensionMinusOne)
		"STR R8, [SP,#0x98+"/* var_7C */"-0x7C]\n"
		"VCVT.S32.F32 S0, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315DAA_thumb)
		);
}

// patch for 0x315DD0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315DDA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315DD0()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R11, R9\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315DDA_thumb)
		);
}

// patch for 0x315DE0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315DE8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315DE0()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		"MOV R0, R11\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimension)
		"ORR R1, R5, R0\n"
		"POP {R0, R2}\n"
		"UXTH R2, R1\n"
		"ADD R1, SP, #0x98+"/* var_3C */"-0x3C\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315DE8_thumb)
		);
}

// patch for 0x315DF8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315E00_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315DF8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S8, fPathsMapMinCoord)
		"VMOV S0, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315E00_thumb)
		);
}

// patch for 0x315E76
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315E82_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315E76()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionNegated)
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R0, iNumberOfPathFilesPerDimension)
		"MVN R2, R9\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315E82_thumb)
		);
}

// patch for 0x315E86
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315E98_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315E86()
{
	__asm(
	".thumb\n"
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R2, iNumberOfPathFilesPerDimension)
		"IT GT\n"
		"MOVGT R1, R2\n"
		"MVNS R2, R0\n"
		"PUSH {R0, R3}\n"
		"MOV R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimension)
		"SUB R5, R2, R0\n"
		"POP {R0, R3}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionTimes2Plus1Negated)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315E98_thumb)
		);
}

// patch for 0x315E9E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315EA8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315E9E()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R3}\n"
		"MOV R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimension)
		"SUB R2, R2, R0\n"
		"POP {R0, R3}\n"
		"STR R2, [SP,#0x98+"/* var_58 */"-0x58]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionTimes2Negated)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315EA8_thumb)
		);
}

// patch for 0x315EB2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315EBC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315EB2()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R3}\n"
		"MOV R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimension)
		"SUB R2, R2, R0\n"
		"POP {R0, R3}\n"
		"STR R2, [SP,#0x98+"/* var_5C */"-0x5C]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionTimes2Plus2Negated)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315EBC_thumb)
		);
}

// patch for 0x315EBE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315EC8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315EBE()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		"MOV R2, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimension)
		"SUB R0, R0, R2\n"
		"POP {R2, R3}\n"
		"STR R0, [SP,#0x98+"/* var_60 */"-0x60]\n"
		"MOV R0, #0xFFFD\n"
		"MOVT R0, #0xFFFF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315EC8_thumb)
		);
}

// patch for 0x315ED6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315F26_thumb = 0;	// loc_315F26
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315EE2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315ED6()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"STR R0, [SP,#0x98+"/* var_6C */"-0x6C]\n"
		"BHI 1f\n"
		"LDR R0, [SP,#0x98+"/* var_50 */"-0x50]\n"
		"ADD R4, R0, R11\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315EE2_thumb)

		// Branches
		"1:\n"	// loc_315F26
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315F26_thumb)
		);
}

// patch for 0x315F30
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315F7E_thumb = 0;	// loc_315F7E
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315F38_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315F30()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionMinusOne)
		"MOV R0, R1\n"
		"STR R0, [SP,#0x98+"/* var_70 */"-0x70]\n"
		"BHI 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315F38_thumb)

		// Branches
		"1:\n"	// loc_315F7E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315F7E_thumb)
		);
}

// patch for 0x315F80
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315FD0_thumb = 0;	// loc_315FD0
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315F88_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315F80()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iNumberOfPathFilesPerDimensionMinusOne)
		"BHI 1f\n"
		"LDR R0, [SP,#0x98+"/* var_6C */"-0x6C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315F88_thumb)

		// Branches
		"1:\n"	// loc_315FD0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315FD0_thumb)
		);
}

// patch for 0x315F94
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315FC4_thumb = 0;	// loc_315FC4
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315F9C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315F94()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimension)
		"BCS 1f\n"
		"LDR R0, [SP,#0x98+"/* var_4C */"-0x4C]\n"
		"ADD R1, SP, #0x98+"/* var_3C */"-0x3C\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315F9C_thumb)

		// Branches
		"1:\n"	// loc_315FC4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315FC4_thumb)
		);
}

// patch for 0x315FDA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316026_thumb = 0;	// loc_316026
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315FE4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315FDA()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"BHI 1f\n"
		"LDR R0, [SP,#0x98+"/* var_6C */"-0x6C]\n"
		"LDR R1, [SP,#0x98+"/* var_70 */"-0x70]\n"
		"ADDS R0, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315FE4_thumb)

		// Branches
		"1:\n"	// loc_316026
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316026_thumb)
		);
}

// patch for 0x315FEE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316020_thumb = 0;	// loc_316020
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315FF8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315FEE()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimension)
		"BCS 1f\n"
		"LDR R0, [SP,#0x98+"/* var_4C */"-0x4C]\n"
		"ADD R1, SP, #0x98+"/* var_3C */"-0x3C\n"
		"STR R0, [SP,#0x98+"/* var_98 */"-0x98]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_315FF8_thumb)

		// Branches
		"1:\n"	// loc_316020
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316020_thumb)
		);
}

// patch for 0x31603A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316044_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_31603A()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimensionMinusOne)
		"SUB R9, R9, #1\n"
		"ADD R10, R10, #2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316044_thumb)
		);
}

// patch for 0x31604C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316054_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_31604C()
{
	__asm(
	".thumb\n"
		ASM_SUB_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"STR R0, [SP,#0x98+"/* var_5C */"-0x5C]\n"
		"LDR R0, [SP,#0x98+"/* var_54 */"-0x54]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316054_thumb)
		);
}

// patch for 0x31605C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316066_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_31605C()
{
	__asm(
	".thumb\n"
		ASM_SUB_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionPlus1)
		"STR R0, [SP,#0x98+"/* var_60 */"-0x60]\n"
		"ADD R0, R6, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316066_thumb)
		);
}

// patch for 0x316080
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316088_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316080()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, iTotalNumberOfPathFiles)
		"STR R10, [SP,#0x98+"/* var_98 */"-0x98]\n"
		"MOV R3, R4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316088_thumb)
		);
}

// patch for 0x3160C0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_3160C8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_3160C0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, iTotalNumberOfPathFiles_plus_65)
		"STRD R0, R9, [SP,#0x98+"/* var_8C */"-0x8C]\n"
		"MOVS R0, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_3160C8_thumb)
		);
}

// patch for 0x3160F0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_3160FA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_3160F0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, iTotalNumberOfPathFiles_plus_66)
		"LDR R0, [R7,#"/* arg_8 */"0x10]\n"
		"MOV R3, R4\n"
		"STM R1, {R0,R8,R9}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_3160FA_thumb)
		);
}

// patch for 0x316110
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_31611A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316110()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, iTotalNumberOfPathFiles_plus_67)
		"STR R11, [SP,#0x98+"/* var_90 */"-0x90]\n"
		"ADD R11, SP, #0x98+"/* var_40 */"-0x40\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_31611A_thumb)
		);
}

// patch for 0x31613A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316146_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_31613A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, iTotalNumberOfPathFiles_plus_68)
		"STRD R10, R5, [SP,#0x98+"/* var_98 */"-0x98]\n"
		"MOV R3, R4\n"
		"STRD R9, R11, [SP,#0x98+"/* var_90 */"-0x90]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316146_thumb)
		);
}

// patch for 0x316164
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_31616C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316164()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, iTotalNumberOfPathFiles_plus_69)
		"LDR R11, [R7,#"/* arg_8 */"0x10]\n"
		"MOV R3, R4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_31616C_thumb)
		);
}

// patch for 0x316196
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_3161A0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_316196()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, iTotalNumberOfPathFiles_plus_70)
		"LDR R0, [R7,#"/* arg_10 */"0x18]\n"
		"MOV R3, R4\n"
		"STRD R0, R8, [SP,#0x98+"/* var_84 */"-0x84]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_3161A0_thumb)
		);
}

// patch for 0x3161BA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_3161C4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_3161BA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, iTotalNumberOfPathFiles_plus_71)
		"LDR R0, [R7,#"/* arg_10 */"0x18]\n"
		"MOV R3, R4\n"
		"STRD R0, R8, [SP,#0x98+"/* var_84 */"-0x84]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoors_3161C4_thumb)
		);
}

// patch for 0x316208
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddNodeToList_316210_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddNodeToList_316208()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_dwTotalNumNodesInSearchList)
		"LDR R2, [R0,R1]\n"
		"ADDS R2, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddNodeToList_316210_thumb)
		);
}

// patch for 0x316224
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveNodeFromList_31622C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveNodeFromList_316224()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_dwTotalNumNodesInSearchList)
		"LDR R2, [R0,R1]\n"
		"SUBS R2, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveNodeFromList_31622C_thumb)
		);
}

// patch for 0x316250
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveBadStartNode_316258_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveBadStartNode_316250()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, Offset_CPathFind__m_pPathNodes)
		"LDR R8, [R4,R8]\n"
		"CMP R8, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveBadStartNode_316258_thumb)
		);
}

// patch for 0x316262
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveBadStartNode_3162F2_thumb = 0;	// loc_3162F2
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveBadStartNode_316272_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveBadStartNode_316262()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		"LSRS R4, R5, #0x10\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveBadStartNode_316272_thumb)

		// Branches
		"1:\n"	// loc_3162F2
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveBadStartNode_3162F2_thumb)
		);
}

// patch for 0x316274
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveBadStartNode_31627E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveBadStartNode_316274()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R5, SizeOfCPathNodeDividedBy4)
		"ADD R0, R0, R5,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveBadStartNode_31627E_thumb)
		);
}

// patch for 0x316280
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveBadStartNode_316288_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveBadStartNode_316280()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x14\n"
		"ADD R1, R0\n"
		"VLD1.64 {Q9}, [R1]\n"
		"POP {R1, R2}\n"
		"ADD R0, R8, R4,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveBadStartNode_316288_thumb)
		);
}

// patch for 0x31628A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveBadStartNode_316296_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveBadStartNode_31628A()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x14\n"
		"ADD R1, R0\n"
		"VLD1.64 {Q8}, [R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveBadStartNode_316296_thumb)
		);
}

// patch for 0x316306
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316310_thumb = 0;	// loc_316310
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316306()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(LR, Offset_CPathFind__m_dwNumVehicleNodes)
		"MOV.W R12, #0x28\n"
		"MOVS R4, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316310_thumb)
		);
}

// patch for 0x316322
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31632E_thumb = 0;	// loc_31632E
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316322()
{
	__asm(
	".thumb\n"
		"ADD R2, R0, R4,LSL#2\n"
		"LDR R9, [R2,LR]\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_dwNumNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31632E_thumb)
		);
}

// patch for 0x316336
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316346_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316336()
{
	__asm(
	".thumb\n"
		"MOV R3, R9\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		"ADD R5, R0, R4,LSL#2\n"
		"SUB R2, R10, R9\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316346_thumb)
		);
}

// patch for 0x31634E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31634A_thumb = 0;	// loc_31634A
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316358_thumb = 0;	// loc_316358
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31634E()
{
	__asm(
	".thumb\n"
		"STRH          R8, [R6,R3]\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNode)
		"BNE 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316358_thumb)

		// Branches
		"1:\n"	// loc_31634A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31634A_thumb)
		);
}

// patch for 0x31635A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316366_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31635A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iTotalNumberOfPathFiles)
		"BNE 1f\n"
		"MOV R12, #0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(LR, Offset_CPathFind__m_dwNumVehicleNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316366_thumb)

		// Branches
		"1:\n"	// loc_316310
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316310_thumb)
		);
}

// patch for 0x31636E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316378_thumb = 0;	// loc_316378
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31636E()
{
	__asm(
	".thumb\n"
		"MOV R12, #0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(LR, Offset_CPathFind__m_dwNumVehicleNodes)
		"LDR R4, [SP,#0x24+"/* var_24 */"-0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316378_thumb)
		);
}

// patch for 0x31638E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31639A_thumb = 0;	// loc_31639A
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31638E()
{
	__asm(
	".thumb\n"
		"ADD R2, R0, R6,LSL#2\n"
		"LDR R9, [R2,LR]\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_dwNumNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31639A_thumb)
		);
}

// patch for 0x3163A6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163B2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163A6()
{
	__asm(
	".thumb\n"
		"MOV R3, R9\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"ADD R5, R2, R3,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163B2_thumb)
		);
}

// patch for 0x3163B4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163CA_thumb = 0;	// loc_3163CA
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163B4()
{
	__asm(
	".thumb\n"
		"LDRH R3, [R5,#0x28]\n"
		"CBZ R3, 1f\n"
		"ADDS R2, #1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, SizeOfCPathNode)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163BC_thumb)

		// Branches
		"1:\n"	// loc_3163CA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163CA_thumb)
		);
}

// patch for 0x3163C0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31637C_thumb = 0;	// loc_31637C
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163C8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163C0()
{
	__asm(
	".thumb\n"
		"ADDS R2, R6, #1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iTotalNumberOfPathFilesMinusTwo)
		"MOV R6, R2\n"
		"BLE 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163C8_thumb)

		// Branches
		"1:\n"	// loc_31637C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31637C_thumb)
		);
}

// patch for 0x3163CC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163D4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163CC()
{
	__asm(
	".thumb\n"
		"STRH R4, [R5,#0x28]\n"
		"STR R12, [R5]\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_3163D4_thumb)

		// Branches
		"1:\n"	// loc_316378
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316378_thumb)
		);
}

// patch for 0x31642A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316434_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31642A()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"LDR R2, [R2,R4,LSL#2]\n"
		"UXTH R4, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316434_thumb)
		);
}

// patch for 0x31643A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316444_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31643A()
{
	__asm(
	".thumb\n"
		"MOV R2, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [R4,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316444_thumb)
		);
}

// patch for 0x31644A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316466_thumb = 0;	// loc_316466
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316454_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountFloodFillGroups_31644A()
{
	__asm(
	".thumb\n"
		"LDRH R3, [R4,#0x28]\n"
		"ADD R4, #0x17\n"
		"CBNZ R3, 1f\n"
		"STRH R11, [R4, #0x11]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316454_thumb)

		// Branches
		"1:\n"	// loc_316466
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountFloodFillGroups_316466_thumb)
		);
}

// patch for 0x316484
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CheckGrid_31648C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CheckGrid_316484()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, Offset_CPathFind__m_dwNumVehicleNodes)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(LR, Offset_CPathFind__m_dwNumPedNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CheckGrid_31648C_thumb)
		);
}

// patch for 0x3164E8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316860_thumb = 0;	// loc_316860
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3164F6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3164E8()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		"MOV R6, LR\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3164F6_thumb)

		// Branches
		"1:\n"	// loc_316860
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316860_thumb)
		);
}

// patch for 0x31650A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316516_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_31650A()
{
	__asm(
	".thumb\n"
		"LDR LR, [R0,#0x1C]\n"
		"LDR R6, [R0,#0x20]\n"
		"LDR R5, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316516_thumb)
		);
}

// patch for 0x3165C6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3167E2_thumb = 0;	// loc_3167E2
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3165D2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3165C6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R9, Offset_CPathFind__m_pPathNodes)
		"LDR R9, [R0,R9]\n"
		"CMP R9, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3165D2_thumb)

		// Branches
		"1:\n"	// loc_3167E2
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3167E2_thumb)
		);
}

// patch for 0x316602
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_31660C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316602()
{
	__asm(
	".thumb\n"
		"MOV R1, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R1, R9, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_31660C_thumb)
		);
}

// patch for 0x31662A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316634_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_31662A()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"VMOV.I32 D16, #0x3E000000\n"
		"MOVS R6, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316634_thumb)
		);
}

// patch for 0x316656
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316662_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316656()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"LDR R8, [R0,R5,LSL#2]\n"
		"UXTH R0, R8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316662_thumb)
		);
}

// patch for 0x316666
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3167AA_thumb = 0;	// loc_3167AA
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316670_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316666()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R0,R6]\n"
		"CMP R6, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316670_thumb)

		// Branches
		"1:\n"	// loc_3167AA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3167AA_thumb)
		);
}

// patch for 0x31667A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316684_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_31667A()
{
	__asm(
	".thumb\n"
		"MOV R0, R9\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R0, R6, R0,LSL#2\n"
		"LDRH R0, [R0,#0x18]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316684_thumb)
		);
}

// patch for 0x316690
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316698_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316690()
{
	__asm(
	".thumb\n"
		"MOV R0, R9\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R0, R6, R0,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316698_thumb)
		);
}

// patch for 0x3166A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3166A8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3166A0()
{
	__asm(
	".thumb\n"
		"MOV R0, R9\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R1}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R10\n"
		"VLD1.64 {Q10}, [R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3166A8_thumb)
		);
}

// patch for 0x3166AE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3166BE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3166AE()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x14\n"
		"ADD R1, R0\n"
		"VLD1.64 {Q9}, [R1]\n"
		"POP {R1, R2}\n"
		"VCVT.F32.S32 D17, D20\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_3166BE_thumb)
		);
}

// patch for 0x316818
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_31682E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316818()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 500f\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R0, R0, R1,LSL#2\n"
		"LDRH R1, [R0,#0x18]\n"
		"ANDS R1, R1, #0xF\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_31682E_thumb)
		);
}

// patch for 0x31683E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316848_thumb = 0;	// loc_316848
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_31683E()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"ADD R0, R2, R0,LSL#2\n"
		"MOVS R2, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316848_thumb)
		);
}

// patch for 0x316852
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_31686C_thumb = 0;	// loc_31686C
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_31685C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNextNodeWandering_316852()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R6,R0]\n"
		"POP {R0, R1}\n"
		"CBNZ R6, 1f\n"
		"ADDS R2, #1\n"
		"CMP R2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_31685C_thumb)

		// Branches
		"1:\n"	// loc_31686C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNextNodeWandering_31686C_thumb)
		);
}

// patch for 0x316890
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316898_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316890()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S0, fPathsMapMaxCoord)
		"VMOV S17, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316898_thumb)
		);
}

// patch for 0x3168D4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_3168DE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_3168D4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"VMOV.F32 S21, #0.125\n"
		"VMOV.F32 S23, #1.0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_3168DE_thumb)
		);
}

// patch for 0x316928
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316930_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316928()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R0\n"
		"CMP R2, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316930_thumb)
		);
}

// patch for 0x316934
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316942_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316934()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R2, R0\n"
		"PUSH {R3, R4}\n"
		"MOV R3, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfPathFilesPerDimension)
		"ORR R0, R2, R3\n"
		"POP {R3, R4}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_dwNumVehicleNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316942_thumb)
		);
}

// patch for 0x31694A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316954_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_31694A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_dwNumPedNodes)
		"MOV R11, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R11, Offset_CPathFind__m_pPathIntersections)
		"ADD R1, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316954_thumb)
		);
}

// patch for 0x316956
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316960_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316956()
{
	__asm(
	".thumb\n"
		"MOV R1, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"STR R1, [SP,#0xD8+"/* var_88 */"-0x88]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316960_thumb)
		);
}

// patch for 0x3169DC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_3169E6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_3169DC()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LDR R0, [R0]\n"
		"ADD R0, R0, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_3169E6_thumb)
		);
}

// patch for 0x3169EA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_3169F6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_3169EA()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R6\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R1}\n"
		"VCVT.F32.S32 D16, D16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_3169F6_thumb)
		);
}

// patch for 0x316A66
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316DAC_thumb = 0;	// loc_316DAC
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316A72_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316A66()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFilesNegatedCNodeAddressMask)
		"ANDS R0, R1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFilesMinusOne)
		"BHI 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316A72_thumb)

		// Branches
		"1:\n"	// loc_316DAC
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316DAC_thumb)
		);
}

// patch for 0x316A78
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316A82_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316A78()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316A82_thumb)

		// Branches
		"1:\n"	// loc_316DAC
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316DAC_thumb)
		);
}

// patch for 0x316A8C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316A94_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316A8C()
{
	__asm(
	".thumb\n"
		"MOV R2, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"ADD R2, R0, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316A94_thumb)
		);
}

// patch for 0x316AB4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316ABC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316AB4()
{
	__asm(
	".thumb\n"
		"MOV R2, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"ADD R2, R0, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316ABC_thumb)
		);
}

// patch for 0x316AD4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316ADC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316AD4()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R0, R0, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316ADC_thumb)
		);
}

// patch for 0x316AEA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316AF6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316AEA()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R1\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R2}\n"
		"VCVT.F32.S32 D16, D16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316AF6_thumb)
		);
}

// patch for 0x316B8E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316B9A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316B8E()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x16\n"
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"VMOV S0, R0\n"
		"VCVT.F32.S32 S0, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316B9A_thumb)
		);
}

// patch for 0x316B9E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316BAA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316B9E()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x16\n"
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x14\n"
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"VMOV S2, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316BAA_thumb)
		);
}

// patch for 0x316BB2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316BBE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316BB2()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x14\n"
		"LDR R0, [R6,R0]\n"
		"VCVT.F32.S32 S6, S6\n"
		"VMUL.F32 S0, S0, S21\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316BBE_thumb)
		);
}

// patch for 0x316BD2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316BDE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316BD2()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x18\n"
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"VMUL.F32 S0, S4, S0\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x18\n"
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_316BDE_thumb)
		);
}

// patch for 0x316E14
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindRegionForCoors_316E1C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindRegionForCoors_316E14()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S0, fPathsMapMaxCoord)
		"VMOV S2, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindRegionForCoors_316E1C_thumb)
		);
}

// patch for 0x316E2E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindRegionForCoors_316E38_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindRegionForCoors_316E2E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"VDIV.F32 S2, S2, S6\n"
		"VDIV.F32 S0, S0, S6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindRegionForCoors_316E38_thumb)
		);
}

// patch for 0x316E4E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindRegionForCoors_316E64_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindRegionForCoors_316E4E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R2, R0\n"
		"CMP R3, #0\n"
		"IT GT\n"
		"MOVGT R1, R3\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R0\n"
		"PUSH {R3, R4}\n"
		"MOV R3, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfPathFilesPerDimension)
		"ORR R0, R1, R3\n"
		"POP {R3, R4}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindRegionForCoors_316E64_thumb)
		);
}

// patch for 0x316E80
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316E88_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316E80()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S0, fPathsMapMaxCoord)
		"VMOV S17, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316E88_thumb)
		);
}

// patch for 0x316E98
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316EA2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316E98()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, iNumberOfPathFilesPerDimensionMinusOne)
		"VMOV.F32 S20, #0.125\n"
		"VLDR S22, 101f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316EA2_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, 900.0)
		);
}

// patch for 0x316EDC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316EE4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316EDC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R1, R3\n"
		"CMP R2, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316EE4_thumb)
		);
}

// patch for 0x316EE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316EF4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316EE8()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R2, R3\n"
		"STR R0, [SP,#0x90+"/* var_88 */"-0x88]\n"
		"PUSH {R0, R3}\n"
		"MOV R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimension)
		"ORR R1, R2, R0\n"
		"POP {R0, R3}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316EF4_thumb)
		);
}

// patch for 0x316EF8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F04_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316EF8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_dwNumVehicleNodes)
		"ADD R1, R0\n"
		"STR R1, [SP,#0x90+"/* var_8C */"-0x8C]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_dwNumPedNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F04_thumb)
		);
}

// patch for 0x316F08
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F10_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F08()
{
	__asm(
	".thumb\n"
		"MOV R1, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F10_thumb)
		);
}

// patch for 0x316F3E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F48_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F3E()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LDR R0, [R0]\n"
		"ADD R0, R0, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F48_thumb)
		);
}

// patch for 0x316F4A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F56_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F4A()
{
	__asm(
	".thumb\n"
		"ADD R11, R11, #0xC\n"
		"LDR R1, [R11,#0x18]\n"
		"VMOV S0, R1\n"
		"VCVT.F32.S32 S0, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F56_thumb)
		);
}

// patch for 0x316F6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F6C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R1\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316F74_thumb)
		);
}

// patch for 0x316FBE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_3170EE_thumb = 0;	// loc_3170EE
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316FCA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316FBE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, iTotalNumberOfPathFilesNegatedCNodeAddressMask)
		"ANDS R1, R0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iTotalNumberOfPathFilesMinusOne)
		"BHI 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316FCA_thumb)

		// Branches
		"1:\n"	// loc_3170EE
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_3170EE_thumb)
		);
}

// patch for 0x316FD2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316FDC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316FD2()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316FDC_thumb)

		// Branches
		"1:\n"	// loc_3170EE
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_3170EE_thumb)
		);
}

// patch for 0x316FE2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316FEC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316FE2()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R0, R1, R0,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_316FEC_thumb)
		);
}

// patch for 0x317016
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_317026_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_317016()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x18\n"
		"LDR R0, [R6,R0]\n"
		"VMOV S2, R0\n"
		"VCVT.F32.S32 S2, S2\n"
		"MOV R0, 0x18\n"
		"LDR R0, [R11,R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_317026_thumb)
		);
}

// patch for 0x31702C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_317038_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_31702C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x14\n"
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"VCVT.F32.S32 S4, S4\n"
		"MOV R0, 0x14\n"
		"LDR R0, [R8,R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_317038_thumb)
		);
}

// patch for 0x317044
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_31704C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_317044()
{
	__asm(
	".thumb\n"
		"MOV R1, 0x16\n"
		"LDR R1, [R10,R1]\n"
		"VCVT.F32.S32 S8, S8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_31704C_thumb)
		);
}

// patch for 0x317056
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_317062_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_317056()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x16\n"
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"VMUL.F32 S4, S4, S20\n"
		"VCVT.F32.S32 S10, S10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__GeneratePedCreationCoors_Interior_317062_thumb)
		);
}

// patch for 0x3171E0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_3171EA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcRoadDensity_3171E0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R10, Offset_CPathFind__m_pPathNodes)
		"LDR R10, [R1,R10]\n"
		"STR R2, [SP,#0x24+"/* var_24 */"-0x24]\n"
		"CMP R10, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_3171EA_thumb)
		);
}

// patch for 0x3171EE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_3171FA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcRoadDensity_3171EE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_dwNumVehicleNodes)
		"LDR R9, [R1,R3]\n"
		"CMP R9, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_3171FA_thumb)
		);
}

// patch for 0x3171FE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_317208_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcRoadDensity_3171FE()
{
	__asm(
	".thumb\n"
		"MOV R11, R1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R11, Offset_CPathFind__m_pNaviLinks)
		"MOVS R5, #0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_317208_thumb)
		);
}

// patch for 0x31720A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_317216_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcRoadDensity_31720A()
{
	__asm(
	".thumb\n"
		"MOV R1, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R2, R10, R1,LSL#2\n"
		"LDR R1, [R2,#0x1C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_317216_thumb)
		);
}

// patch for 0x317234
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_31723C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcRoadDensity_317234()
{
	__asm(
	".thumb\n"
		"LDR R1, [R2,#0x20]\n"
		"VMOV S12, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_31723C_thumb)
		);
}

// patch for 0x317266
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_317272_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcRoadDensity_317266()
{
	__asm(
	".thumb\n"
		"MOV R8, R2,LSL#2\n"
		"ADD LR, R3, R2,LSL#2\n"
		"BIC R2, R1, #0xFF000000\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_317272_thumb)
		);
}

// patch for 0x31727E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_31731C_thumb = 0;	// loc_31731C
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_31728E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcRoadDensity_31727E()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [R4,R0]\n"
		"POP {R0, R1}\n"
		"CMP R4, #0\n"
		"BEQ 1f\n"
		"LSRS R6, R1, #0x10\n"
		"MOV R1, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_31728E_thumb)

		// Branches
		"1:\n"	// loc_31731C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_31731C_thumb)
		);
}

// patch for 0x317292
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_31729E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcRoadDensity_317292()
{
	__asm(
	".thumb\n"
		"LDR R6, [R1,#0x1C]\n"
		"LDR R1, [R1,#0x20]\n"
		"VMOV S1, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_31729E_thumb)
		);
}

// patch for 0x3172B0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_3172BE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcRoadDensity_3172B0()
{
	__asm(
	".thumb\n"
		"LDR R1, [R1,R3,LSL#2]\n"
		"LSRS R6, R1, #16\n"
		"ADD R12, R0, R6,LSL#2\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [R12,R4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_3172BE_thumb)
		);
}

// patch for 0x3172C4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_3172D4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcRoadDensity_3172C4()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		"VMUL.F32 S1, S1, S6\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pNaviNodes)
		"LDR R6, [R12,R6]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_3172D4_thumb)
		);
}

// patch for 0x31732E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_3171DC_thumb = 0;	// loc_3171DC
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_317338_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcRoadDensity_31732E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iTotalNumberOfPathFiles)
		"BNE 1f\n"
		"VLDR S2, 101f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_317338_thumb)

		// Branches
		"1:\n"	// loc_3171DC
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcRoadDensity_3171DC_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, 2500.0)
		);
}

// patch for 0x3173A2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_3173AC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_3173A2()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"LDR R1, [R1,R2,LSL#2]\n"
		"UXTH R2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_3173AC_thumb)
		);
}

// patch for 0x3173B0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_31745A_thumb = 0;	// loc_31745A
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_3173C4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_3173B0()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"BEQ 1f\n"
		"LDR R0, [R4,#0x1C]\n"
		"LDR R3, [R4,#0x20]\n"
		"LDR R5, [R4,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_3173C4_thumb)

		// Branches
		"1:\n"	// loc_31745A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_31745A_thumb)
		);
}

// patch for 0x3173CE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_3173D8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_3173CE()
{
	__asm(
	".thumb\n"
		"VMOV S4, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_3173D8_thumb)
		);
}

// patch for 0x317400
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_31740C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_317400()
{
	__asm(
	".thumb\n"
		"LDR R1, [R0,#0x1C]\n"
		"LDR R2, [R0,#0x20]\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CalcDistToAnyConnectingLinks_31740C_thumb)
		);
}

// patch for 0x31749C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_3175EA_thumb = 0;	// loc_3175EA
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_3174A6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_31749C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R1,R0]\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_3174A6_thumb)

		// Branches
		"1:\n"	// loc_3175EA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_3175EA_thumb)
		);
}

// patch for 0x3174B0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_3174B8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_3174B0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_dwNumVehicleNodes)
		"MOVS R5, #0\n"
		"ADD R2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_3174B8_thumb)
		);
}

// patch for 0x3174BA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_3174C4_thumb = 0;	// loc_3174C4
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_3174BA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_dwNumVehicleNodes)
		"LDR R5, [R1,R2]\n"
		"MOV R2, R1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_dwNumNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_3174C4_thumb)
		);
}

// patch for 0x3174DC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_3174E8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_3174DC()
{
	__asm(
	".thumb\n"
		"MOV R10, R1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R10, Offset_CPathFind__m_pPathNodes)
		"LDRD R9, R4, [R7,#"/* anonymous1 */"0x14]\n"
		"MOV R1, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_3174E8_thumb)
		);
}

// patch for 0x317508
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_317510_thumb = 0;	// loc_317510
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_317508()
{
	__asm(
	".thumb\n"
		"ADDS R5, #1\n"
		"LDR R0, [R10]\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNode)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_317510_thumb)
		);
}

// patch for 0x31753C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_317548_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_31753C()
{
	__asm(
	".thumb\n"
		"LDR R0, [R1,#0x1C]\n"
		"LDR R2, [R1,#0x20]\n"
		"LDR R3, [R1,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestInRegion_317548_thumb)
		);
}

// patch for 0x317600
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindXRegionForCoors_317608_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindXRegionForCoors_317600()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S0, fPathsMapMaxCoord)
		"VMOV S2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindXRegionForCoors_317608_thumb)
		);
}

// patch for 0x31761E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindXRegionForCoors_317628_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindXRegionForCoors_31761E()
{
	__asm(
	".thumb\n"
		"IT LE\n"
		"MOVLE R0, #0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"BLT 500f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindXRegionForCoors_317628_thumb)
		);
}

// patch for 0x317634
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindYRegionForCoors_31763C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindYRegionForCoors_317634()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S0, fPathsMapMaxCoord)
		"VMOV S2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindYRegionForCoors_31763C_thumb)
		);
}

// patch for 0x317652
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindYRegionForCoors_31765C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindYRegionForCoors_317652()
{
	__asm(
	".thumb\n"
		"IT LE\n"
		"MOVLE R0, #0\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"BLT 500f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindYRegionForCoors_31765C_thumb)
		);
}

// patch for 0x317678
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindXCoorsForRegion_317680_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindXCoorsForRegion_317678()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S2, fPathsMapMinCoord)
		"VADD.F32 S0, S0, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindXCoorsForRegion_317680_thumb)
		);
}

// patch for 0x3176A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindYCoorsForRegion_3176A8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindYCoorsForRegion_3176A0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S2, fPathsMapMinCoord)
		"VADD.F32 S0, S0, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindYCoorsForRegion_3176A8_thumb)
		);
}

// patch for 0x3176D2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_3176DC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_3176D2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R10, Offset_CPathFind__m_dwNumVehicleNodes)
		"STR R2, [SP,#0x50+"/* var_2C */"-0x2C]\n"
		"STRD R3, R1, [SP,#0x50+"/* var_34 */"-0x34]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_3176DC_thumb)
		);
}

// patch for 0x3176E2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_317752_thumb = 0;	// loc_317752
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_3176EC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_3176E2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R2,R6]\n"
		"CBZ R6, 1f\n"
		"CMP R9, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_3176EC_thumb)

		// Branches
		"1:\n"	// loc_317752
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_317752_thumb)
		);
}

// patch for 0x3176FC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_317704_thumb = 0;	// loc_317704
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_3176FC()
{
	__asm(
	".thumb\n"
		"LDR R0, [R2,R10]\n"
		"MOV R3, R2\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_dwNumNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_317704_thumb)
		);
}

// patch for 0x31770C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_317714_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_31770C()
{
	__asm(
	".thumb\n"
		"MOV R5, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R5, SizeOfCPathNodeDividedBy4)
		"ADD R6, R6, R5,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_317714_thumb)
		);
}

// patch for 0x317728
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_317730_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_317728()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathNode_index_1_m_dwFlags)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pPathNodes)
		"SUBS R6, R4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_317730_thumb)
		);
}

// patch for 0x317748
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_317750_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_317748()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, SizeOfCPathNode)
		"STRB LR, [R12,#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_317750_thumb)
		);
}

// patch for 0x317754
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_3176DE_thumb = 0;	// loc_3176DE
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_31775C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_317754()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iTotalNumberOfPathFilesIncludingInterior)
		"BNE 1f\n"
		"LDR R0, [R7,#"/* arg_10 */"0x18]\n"
		"LDR R6, [SP,#0x50+"/* var_34 */"-0x34]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_31775C_thumb)

		// Branches
		"1:\n"	// loc_3176DE
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_3176DE_thumb)
		);
}

// patch for 0x3177A2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_3177AC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_3177A2()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNthNodeClosestToCoors_3177AC_thumb)
		);
}

// patch for 0x317828
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317830_thumb = 0;	// loc_317830
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317828()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, Offset_CPathFind__m_dwNumVehicleNodes)
		"STR R3, [SP,#0x50+"/* var_30 */"-0x30]\n"
		"STR R0, [SP,#0x50+"/* var_34 */"-0x34]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317830_thumb)
		);
}

// patch for 0x317834
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317872_thumb = 0;	// loc_317872
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_31783E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317834()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R2,R6]\n"
		"CBZ R6, 1f\n"
		"LDR R3, [R2,R12]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_31783E_thumb)

		// Branches
		"1:\n"	// loc_317872
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317872_thumb)
		);
}

// patch for 0x317850
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317858_thumb = 0;	// loc_317858
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317850()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pPathNodes)
		"SUBS R3, #1\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathNode_index_1_m_dwFlags)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317858_thumb)
		);
}

// patch for 0x317868
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317870_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317868()
{
	__asm(
	".thumb\n"
		"STRH R1, [R5,R6]\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNode)
		"STRB R0, [R4,#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317870_thumb)
		);
}

// patch for 0x317876
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317880_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317876()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(LR, iTotalNumberOfPathFilesIncludingInterior)
		"BNE 1f\n"
		"MOV R0, #0x23FE\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317880_thumb)

		// Branches
		"1:\n"	// loc_317830
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317830_thumb)
		);
}

// patch for 0x3178C8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_3178D2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_3178C8()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_3178D2_thumb)
		);
}

// patch for 0x317920
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_31792C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317920()
{
	__asm(
	".thumb\n"
		"MOVS R6, #0\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_31792C_thumb)
		);
}

// patch for 0x317986
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317990_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317986()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317990_thumb)
		);
}

// patch for 0x3179D8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_3179E2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_3179D8()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_3179E2_thumb)
		);
}

// patch for 0x317A0E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A1A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A0E()
{
	__asm(
	".thumb\n"
		"MOV LR, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(LR, SizeOfCPathNodeDividedBy4)
		"LDR R0, [SP,#0x50+"/* var_28 */"-0x28]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R3,R5]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A1A_thumb)
		);
}

// patch for 0x317A28
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A32 = 0;
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A30_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A28()
{
	__asm(
	".thumb\n"
		"MOV R12, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R12, SizeOfCPathNodeDividedBy4)
		"LSRS R6, R0, #0x10\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A32)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A30_thumb)
		);
}

// patch for 0x317A3E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A4A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A3E()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"ADD R5, R2, R4,LSL#2\n"
		"BIC R4, R3, #0xFF000000\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A4A_thumb)
		);
}

// patch for 0x317A8E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A98_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A8E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R1,R6]\n"
		"ADD R1, R6, LR,LSL#2\n"
		"LDRH R1, [R1,#0x18]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317A98_thumb)
		);
}

// patch for 0x317AB6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317AC0_thumb = 0;	// loc_317AC0
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317AB6()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"ADD R1, R1, R6,LSL#2\n"
		"MOVS R6, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317AC0_thumb)
		);
}

// patch for 0x317AE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317AF0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317AE8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R1,R5]\n"
		"ADD R1, R5, LR,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317AF0_thumb)
		);
}

// patch for 0x317B0E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317B1A_thumb = 0;	// loc_317B1A
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317B0E()
{
	__asm(
	".thumb\n"
		"ADD R1, R1, R8,LSL#2\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"ADD R5, R1, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Find2NodesForCarCreation_317B1A_thumb)
		);
}

// patch for 0x317B70
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317B7A_thumb = 0;	// loc_317B7A
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317B70()
{
	__asm(
	".thumb\n"
		"STRD R3, R1, [SP,#0x50+"/* var_34 */"-0x34]\n"
		"MOVS R1, #0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_dwNumVehicleNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317B7A_thumb)
		);
}

// patch for 0x317B7E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317BF4_thumb = 0;	// loc_317BF4
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317B88_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317B7E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R5,R6]\n"
		"CBZ R6, 1f\n"
		"CMP R12, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317B88_thumb)

		// Branches
		"1:\n"	// loc_317BF4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317BF4_thumb)
		);
}

// patch for 0x317BA4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317BAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317BA4()
{
	__asm(
	".thumb\n"
		"MOV R2, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"ADD R6, R6, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317BAC_thumb)
		);
}

// patch for 0x317BC0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317BC8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317BC0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathNode_index_1_m_dwFlags)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		"SUBS R6, R4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317BC8_thumb)
		);
}

// patch for 0x317BE2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317BCC_thumb = 0;	// loc_317BCC
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317BE2()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNode)
		"STRB R11, [LR,#2]\n"
		"BNE 1f\n"
		"LDR R12, [R7,#"/* arg_0 */"0x8]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_dwNumVehicleNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317BF4_thumb)

		// Branches
		"1:\n"	// loc_317BCC
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317BCC_thumb)
		);
}

// patch for 0x317BF6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317C00_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317BF6()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iTotalNumberOfPathFilesIncludingInterior)
		"BNE 1f\n"
		"LDR R0, [R7,#"/* arg_4 */"0xC]\n"
		"LDR R4, [SP,#0x50+"/* var_34 */"-0x34]\n"
		"CMP R0, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317C00_thumb)

		// Branches
		"1:\n"	// loc_317B7A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317B7A_thumb)
		);
}

// patch for 0x317C44
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317C52_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317C44()
{
	__asm(
	".thumb\n"
		"SUB R11, R11, #1\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesClosestToCoors_317C52_thumb)
		);
}

// patch for 0x317C8A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__These2NodesAreAdjacent_317C98_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__These2NodesAreAdjacent_317C8A()
{
	__asm(
	".thumb\n"
		"MOV R0, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R3, R3, R5,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__These2NodesAreAdjacent_317C98_thumb)
		);
}

// patch for 0x317CA6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__These2NodesAreAdjacent_317CB0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__These2NodesAreAdjacent_317CA6()
{
	__asm(
	".thumb\n"
		"MOV R1, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"MOV R12, R2,LSR#16\n"
		"UXTH R2, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__These2NodesAreAdjacent_317CB0_thumb)
		);
}

// patch for 0x317CC4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__These2NodesAreAdjacent_317CCC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__These2NodesAreAdjacent_317CC4()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"ADD R1, R0, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__These2NodesAreAdjacent_317CCC_thumb)
		);
}

// patch for 0x317D30
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317E1E_thumb = 0;	// loc_317E1E
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D38_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D30()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R5,R0]\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D38_thumb)

		// Branches
		"1:\n"	// loc_317E1E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317E1E_thumb)
		);
}

// patch for 0x317D40
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D48_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D40()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_dwNumVehicleNodes)
		"MOV R12, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D48_thumb)
		);
}

// patch for 0x317D4C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D58_thumb = 0;	// loc_317D58
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D4C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_dwNumVehicleNodes)
		"LDR R12, [R5,R3]\n"
		"MOV R3, R5\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_dwNumNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D58_thumb)
		);
}

// patch for 0x317D60
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D68_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D60()
{
	__asm(
	".thumb\n"
		"MOV R3, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		"MOV R10, R5\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R10, Offset_CPathFind__m_pPathNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D68_thumb)
		);
}

// patch for 0x317D7A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D8E_thumb = 0;	// loc_317D8E
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D84_thumb = 0;	// loc_317D84
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D7A()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R11, SizeOfCPathNode)
		"CMP LR, #1\n"
		"BNE 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D84_thumb)

		// Branches
		"1:\n"	// loc_317D8E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D8E_thumb)
		);
}

// patch for 0x317DB0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317DB8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317DB0()
{
	__asm(
	".thumb\n"
		"LDR R3, [R0,#0x1C]\n"
		"VMOV S4, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317DB8_thumb)
		);
}

// patch for 0x317DBC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317DC4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317DBC()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x20\n"
		"ADD R1, R0\n"
		"VLD1.64 {Q9}, [R1]\n"
		"POP {R1, R2}\n"
		"STR R0, [SP,#0x2C+"/* var_20 */"-0x20]\n"
		"ADD R0, SP, #0x2C+"/* var_20 */"-0x20\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317DC4_thumb)
		);
}

// patch for 0x317DC8



// patch for 0x317E1E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D28_thumb = 0;	// loc_317D28
	uintptr_t Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317E2A_thumb = 0;	// loc_317E2A
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317E1E()
{
	__asm(
	".thumb\n"
		"ADD R0, R9, #1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iTotalNumberOfPathFiles_plus_71)
		"BLT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317E2A_thumb)

		// Branches
		"1:\n"	// loc_317D28
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RecordNodesInCircle_317D28_thumb)
		);
}

// patch for 0x317E94
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317E9C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317E94()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, Offset_CPathFind__m_dwNumVehicleNodes)
		"VMOV S8, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317E9C_thumb)
		);
}

// patch for 0x317EA4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317F96_thumb = 0;	// loc_317F96
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317EAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317EA4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [R6,R4]\n"
		"CMP R4, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317EAC_thumb)

		// Branches
		"1:\n"	// loc_317F96
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317F96_thumb)
		);
}

// patch for 0x317ED0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317ED8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317ED0()
{
	__asm(
	".thumb\n"
		"MOV R6, R9\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		"ADD R4, R4, R6,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317ED8_thumb)
		);
}

// patch for 0x317EDE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317EEA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317EDE()
{
	__asm(
	".thumb\n"
		"MOV R3, 0x14\n"
		"LDR R3, [R6,R3]\n"
		"LDR R2, [R6,#0x18]\n"
		"LDR R1, [R6,#0x1C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317EEA_thumb)
		);
}

// patch for 0x317F9A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317EA0_thumb = 0;	// loc_317EA0
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317FA6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317F9A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iTotalNumberOfPathFilesIncludingInterior)
		"BNE 1f\n"
		"PKHBT R0, LR, R10,LSL#16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317FA6_thumb)

		// Branches
		"1:\n"	// loc_317EA0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeClosestToCoorsFavourDirection_317EA0_thumb)
		);
}

// patch for 0x318006
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3181A4_thumb = 0;	// loc_3181A4
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318012_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318006()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R11, Offset_CPathFind__m_pPathNodes)
		"LDR R11, [R1,R11]\n"
		"CMP R11, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318012_thumb)

		// Branches
		"1:\n"	// loc_3181A4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3181A4_thumb)
		);
}

// patch for 0x318018
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318022_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318018()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_dwNumVehicleNodes)
		"ADDS R5, R1, R6\n"
		"MOV R9, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318022_thumb)
		);
}

// patch for 0x318024
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_31802C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318024()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_dwNumVehicleNodes)
		"MOV R5, R1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_dwNumNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_31802C_thumb)
		);
}

// patch for 0x31803A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318044_thumb = 0;	// loc_318044
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_31803A()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"STR R3, [SP,#0x60+"/* var_48 */"-0x48]\n"
		"STRD R9, R1, [SP,#0x60+"/* var_60 */"-0x60]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318044_thumb)
		);
}

// patch for 0x318044
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_31804C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318044()
{
	__asm(
	".thumb\n"
		"MOV R1, R9\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R1, R11, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_31804C_thumb)
		);
}

// patch for 0x318070
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_31807A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318070()
{
	__asm(
	".thumb\n"
		"LDR R5, [R1,#0x1C]\n"
		"ADD R3, SP, #0x60+"/* var_40 */"-0x40\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x20\n"
		"ADD R0, R1\n"
		"VLD1.64 {Q9}, [R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_31807A_thumb)
		);
}

// patch for 0x318084



// patch for 0x3180EC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_31818A_thumb = 0;	// loc_31818A
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3180F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3180EC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R6,R5]\n"
		"CMP R5, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3180F4_thumb)

		// Branches
		"1:\n"	// loc_31818A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_31818A_thumb)
		);
}

// patch for 0x3180F8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318100_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3180F8()
{
	__asm(
	".thumb\n"
		"MOV R6, LR\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318100_thumb)
		);
}

// patch for 0x318124
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318130_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318124()
{
	__asm(
	".thumb\n"
		"MOV R3, LR\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		"ADD R3, R5, R3,LSL#2\n"
		"LDR R5, [R3,#0x1C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318130_thumb)
		);
}

// patch for 0x318138
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318148_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318138()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x20\n"
		"ADD R0, R3\n"
		"VLD1.64 {Q9}, [R0]\n"
		"POP {R0, R1}\n"
		"STR R3, [SP,#0x60+"/* var_44 */"-0x44]\n"
		"ADD R3, SP, #0x60+"/* var_44 */"-0x44\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318148_thumb)
		);
}

// patch for 0x3181A6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318002_thumb = 0;	// loc_318002
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3181B0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3181A6()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iTotalNumberOfPathFilesIncludingInterior)
		"BNE 1f\n"
		"VCMPE.F32 S8, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3181B0_thumb)

		// Branches
		"1:\n"	// loc_318002
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318002_thumb)
		);
}

// patch for 0x3181B8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3181C0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3181B8()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R7,#"/* arg_4 */"0xC]\n"
		"LDR R5, [SP,#0x60+"/* var_4C */"-0x4C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3181C0_thumb)
		);
}

// patch for 0x3181CC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3181D4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3181CC()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LDR R4, [SP,#0x60+"/* var_50 */"-0x50]\n"
		"UXTH R2, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3181D4_thumb)
		);
}

// patch for 0x3181EA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318202_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_3181EA()
{
	__asm(
	".thumb\n"
		"MOV R1, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R1, R3, R1,LSL#2\n"
		"LDR R3, [R0,#0x1C]\n"
		"LDR R0, [R0,#0x20]\n"
		"LDR R2, [R1,#0x1C]\n"
		"LDR R1, [R1,#0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodePairClosestToCoors_318202_thumb)
		);
}

// patch for 0x3182BA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_3183F8_thumb = 0;	// loc_3183F8
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_3182C4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_3182BA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R8,R2]\n"
		"CMP R2, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_3182C4_thumb)

		// Branches
		"1:\n"	// loc_3183F8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_3183F8_thumb)
		);
}

// patch for 0x3182C8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_3182D0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_3182C8()
{
	__asm(
	".thumb\n"
		"MOV R1, R9\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD LR, R2, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_3182D0_thumb)
		);
}

// patch for 0x3182F6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318300_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_3182F6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pNaviLinks)
		"LDR R6, [R8,R6]\n"
		"MOVS R4, #0\n"
		"ADD R5, R6, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318300_thumb)
		);
}

// patch for 0x318306
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318314_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318306()
{
	__asm(
	".thumb\n"
		"LDR R2, [R5,R4,LSL#2]\n"
		"LSRS R1, R2, #16\n"
		"ADD R1, R0, R1,LSL#2\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R1,R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318314_thumb)
		);
}

// patch for 0x318316
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318322_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318316()
{
	__asm(
	".thumb\n"
		"BFC R2, #16, #16\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318322_thumb)
		);
}

// patch for 0x318354
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_31835C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318354()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"LDR R1, [R8,R1]\n"
		"SXTAH R2, R4, R12\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_31835C_thumb)
		);
}

// patch for 0x318366
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318370_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318366()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		"LSRS R2, R1, #0x10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318370_thumb)

		// Branches
		"1:\n"	// loc_3183F8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_3183F8_thumb)
		);
}

// patch for 0x318374
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_31837E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318374()
{
	__asm(
	".thumb\n"
		"MOV R1, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LDR R2, [LR,#0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_31837E_thumb)
		);
}

// patch for 0x318382
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318392_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318382()
{
	__asm(
	".thumb\n"
		"LDR R1, [LR,#0x1C]\n"
		"LDR R3, [R0,#0x1C]\n"
		"VMOV S2, R2\n"
		"LDR R0, [R0,#0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeOrientationForCarPlacement_318392_thumb)
		);
}

// patch for 0x31844E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__ThisNodeWillLeadIntoADeadEnd_318458_thumb = 0;	// loc_318458
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__ThisNodeWillLeadIntoADeadEnd_31844E()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R4, [R4,R0]\n"
		"POP {R0, R1}\n"
		"ADD R9, R4, R5,LSL#2\n"
		"MOVS R5, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ThisNodeWillLeadIntoADeadEnd_318458_thumb)
		);
}

// patch for 0x318462
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__ThisNodeWillLeadIntoADeadEnd_318498_thumb = 0;	// loc_318498
	uintptr_t Address_GTA_SA_2_00_CPathFind__ThisNodeWillLeadIntoADeadEnd_318474_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__ThisNodeWillLeadIntoADeadEnd_318462()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"CBZ R3, 1f\n"
		"MOV R11, R6,LSR#16\n"
		"MOV R4, R11\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ThisNodeWillLeadIntoADeadEnd_318474_thumb)

		// Branches
		"1:\n"	// loc_318498
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ThisNodeWillLeadIntoADeadEnd_318498_thumb)
		);
}

// patch for 0x31847C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__ThisNodeWillLeadIntoADeadEnd_318484_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__ThisNodeWillLeadIntoADeadEnd_31847C()
{
	__asm(
	".thumb\n"
		"MOV R4, R11\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		"ADD R3, R3, R4,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ThisNodeWillLeadIntoADeadEnd_318484_thumb)
		);
}

// patch for 0x318520
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_3184F6_thumb = 0;	// loc_3184F6
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31852E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318520()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iTotalNumberOfPathFiles)
		"BNE 1f\n"
		"LDR R9, [SP,#0x80+"/* var_54 */"-0x54]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_dwNumForbiddenAreas)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31852E_thumb)

		// Branches
		"1:\n"	// loc_3184F6
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_3184F6_thumb)
		);
}

// patch for 0x318538
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318542_thumb = 0;	// loc_318542
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318538()
{
	__asm(
	".thumb\n"
		"MOVS R2, #0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_aForbiddenAreas)
		"MOV R6, #0x35B4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318542_thumb)
		);
}

// patch for 0x318542
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31854E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318542()
{
	__asm(
	".thumb\n"
		"MOV R5, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R5, SizeOfCPathNodeDividedBy4)
		"ADD R12, R9, R5,LSL#2\n"
		"ADD LR, R12, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31854E_thumb)
		);
}

// patch for 0x3185F8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31867C_thumb = 0;	// loc_31867C
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318600_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_3185F8()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iTotalNumberOfPathFilesMinusOne)
		"BGT 1f\n"
		"CMP R8, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318600_thumb)

		// Branches
		"1:\n"	// loc_31867C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31867C_thumb)
		);
}

// patch for 0x318602
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31860C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318602()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_aForbiddenAreas)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R2, R9\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31860C_thumb)
		);
}

// patch for 0x318616
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318622_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318616()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R1, R2, R1,LSL#2\n"
		"VSTR S24, [R1,#4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318622_thumb)
		);
}

// patch for 0x318624
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31862C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318624()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R1, R2, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31862C_thumb)
		);
}

// patch for 0x318632
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31863E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318632()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R1, R2, R1,LSL#2\n"
		"VSTR S20, [R1,#0xC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31863E_thumb)
		);
}

// patch for 0x318640
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318648_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318640()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R1, R2, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318648_thumb)
		);
}

// patch for 0x31864E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31865A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31864E()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R1, R2, R1,LSL#2\n"
		"VSTR S16, [R1,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31865A_thumb)
		);
}

// patch for 0x31865C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318664_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31865C()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R1, R2, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318664_thumb)
		);
}

// patch for 0x31866A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318676_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_31866A()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R1, R2, R1,LSL#2\n"
		"STRB R10, [R1,#0x19]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchRoadsOffInArea_318676_thumb)
		);
}

// patch for 0x31868A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TidyUpNodeSwitchesAfterMission_318696_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TidyUpNodeSwitchesAfterMission_31868A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_dwNumForbiddenAreas)
		"LDR R2, [R0,R1]\n"
		"CMP R2, #0x36\n"
		"IT GE\n"
		"MOVGE R2, #0x36\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TidyUpNodeSwitchesAfterMission_318696_thumb)
		);
}

// patch for 0x31875E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_31876A_thumb = 0;	// loc_31876A
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_31875E()
{
	__asm(
	".thumb\n"
		"ADD R3, R0, R3,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"ADD R5, R3, R6,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_31876A_thumb)
		);
}

// patch for 0x318772
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318798_thumb = 0;	// loc_318798
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318780_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318772()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"CBZ R3, 1f\n"
		"LSRS R2, R6, #0x10\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318780_thumb)

		// Branches
		"1:\n"	// loc_318798
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318798_thumb)
		);
}

// patch for 0x3187C0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_3187C8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_3187C0()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"LDR R4, [R2,R3,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_3187C8_thumb)
		);
}

// patch for 0x3187CE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_31888C_thumb = 0;	// loc_31888C
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_3187E2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_3187CE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R2,R5]\n"
		"CMP R5, #0\n"
		"BEQ 1f\n"
		"MOV LR, R4,LSR#16\n"
		"MOV R2, LR\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_3187E2_thumb)

		// Branches
		"1:\n"	// loc_31888C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_31888C_thumb)
		);
}

// patch for 0x318818
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318820_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318818()
{
	__asm(
	".thumb\n"
		"MOV R2, LR\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"BIC LR, R12, #0xFF000000\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318820_thumb)
		);
}

// patch for 0x318830
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318838_thumb = 0;	// loc_318838
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318830()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"ADD R4, R3, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318838_thumb)
		);
}

// patch for 0x318840
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318864_thumb = 0;	// loc_318864
	uintptr_t Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_31884E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318840()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R2,R3]\n"
		"CBZ R3, 1f\n"
		"LSRS R2, R6, #0x10\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_31884E_thumb)

		// Branches
		"1:\n"	// loc_318864
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SwitchOffNodeAndNeighbours_318864_thumb)
		);
}

// patch for 0x3188C0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountNeighboursToBeSwitchedOff_3188C8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountNeighboursToBeSwitchedOff_3188C0()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"ADD LR, R3, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountNeighboursToBeSwitchedOff_3188C8_thumb)
		);
}

// patch for 0x3188DA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountNeighboursToBeSwitchedOff_3188FE_thumb = 0;	// loc_3188FE
	uintptr_t Address_GTA_SA_2_00_CPathFind__CountNeighboursToBeSwitchedOff_3188E8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CountNeighboursToBeSwitchedOff_3188DA()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R5,R0]\n"
		"POP {R0, R1}\n"
		"CBZ R5, 1f\n"
		"LSRS R6, R4, #0x10\n"
		"MOV R4, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountNeighboursToBeSwitchedOff_3188E8_thumb)

		// Branches
		"1:\n"	// loc_3188FE
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CountNeighboursToBeSwitchedOff_3188FE_thumb)
		);
}

// patch for 0x318946
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__MarkRoadNodeAsDontWander_318950_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__MarkRoadNodeAsDontWander_318946()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__MarkRoadNodeAsDontWander_318950_thumb)
		);
}

// patch for 0x31896A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_318976_thumb = 0;	// loc_318976
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_31896A()
{
	__asm(
	".thumb\n"
		"PUSH {R8,R9,R11}\n"
		"MOV LR, #0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, Offset_CPathFind__m_dwNumVehicleNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_318976_thumb)
		);
}

// patch for 0x31897A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_3189C4_thumb = 0;	// loc_3189C4
	uintptr_t Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_318984_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_31897A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R1,R2]\n"
		"CBZ R2, 1f\n"
		"LDR R3, [R1,R12]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_318984_thumb)

		// Branches
		"1:\n"	// loc_3189C4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_3189C4_thumb)
		);
}

// patch for 0x31899C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_3189A6_thumb = 0;	// loc_3189A6
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_31899C()
{
	__asm(
	".thumb\n"
		"BLT 1f\n"
		"MOV R9, R1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R9, Offset_CPathFind__m_pPathNodes)
		"MOVS R1, #1\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathNode_index_1_m_dwFlags)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_3189A6_thumb)

		// Branches
		"1:\n"	// loc_3189C4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_3189C4_thumb)
		);
}

// patch for 0x3189B8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_3189C0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_3189B8()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNode)
		"STRB R2, [R3,#2]\n"
		"LDR R2, [R8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_3189C0_thumb)
		);
}

// patch for 0x3189C8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_3189D2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_3189C8()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(LR, iTotalNumberOfPathFiles)
		"BNE 1f\n"
		"POP {R8,R9,R11}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_3189D2_thumb)

		// Branches
		"1:\n"	// loc_318976
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UnMarkAllRoadNodesAsDontWander_318976_thumb)
		);
}

// patch for 0x3189E8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_318A4A_thumb = 0;	// loc_318A4A
	uintptr_t Address_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_3189F0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_3189E8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [R12,R4]\n"
		"CBZ R4, 1f\n"
		"UXTH R3, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_3189F0_thumb)

		// Branches
		"1:\n"	// loc_318A4A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_318A4A_thumb)
		);
}

// patch for 0x3189F4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_318A08_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_3189F4()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 500f\n"
		"LSR R0, R1, #0x10\n"
		"MOV R1, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R1, R4, R1,LSL#2\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_318A08_thumb)
		);
}

// patch for 0x318A12
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_318A1E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_318A12()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"MOV LR, R2,LSR#16\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pNodeLinks)
		"LDR R2, [R12,R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_318A1E_thumb)
		);
}

// patch for 0x318A52
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_318A5C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_318A52()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathIntersections)
		"LDR R0, [R12,R0]\n"
		"LDRB R0, [R0,R5]\n"
		"UBFX R0, R0, #1, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TestForPedTrafficLight_318A5C_thumb)
		);
}

// patch for 0x318A8C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318C0C_thumb = 0;	// loc_318C0C
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318A96_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318A8C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318A96_thumb)

		// Branches
		"1:\n"	// loc_318C0C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318C0C_thumb)
		);
}

// patch for 0x318AA4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318AAE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318AA4()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R6,R0]\n"
		"POP {R0, R1}\n"
		"CMP R6, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318AAE_thumb)

		// Branches
		"1:\n"	// loc_318C0C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318C0C_thumb)
		);
}

// patch for 0x318AB0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318ABA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318AB0()
{
	__asm(
	".thumb\n"
		"MOV R3, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		"ADD R3, R1, R3,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318ABA_thumb)
		);
}

// patch for 0x318AC4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318ACC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318AC4()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		"BIC R4, R4, #0xFF000000\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318ACC_thumb)
		);
}

// patch for 0x318ADE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318AEA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318ADE()
{
	__asm(
	".thumb\n"
		"MOV LR, R6\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(LR, Offset_CPathFind__m_pNaviLinks)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pNodeLinks)
		"LDR R3, [R6,R3]\n"
		"MOV R9, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318AEA_thumb)
		);
}

// patch for 0x318B1A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B28_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B1A()
{
	__asm(
	".thumb\n"
		"LDR R1, [R1,R5,LSL#2]\n"
		"LSRS R6, R1, #16\n"
		"ADD R2, R10, R6,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B28_thumb)
		);
}

// patch for 0x318B2E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B3A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B2E()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B3A_thumb)
		);
}

// patch for 0x318B66
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B7A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B66()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"BEQ 500f\n"
		"LSR R5, R3, #0x10\n"
		"MOV R3, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		"ADD R3, R2, R3,LSL#2\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B7A_thumb)
		);
}

// patch for 0x318B86
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B92 = 0;
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B90_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B86()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R5, SizeOfCPathNodeDividedBy4)
		"BIC R4, R6, #0xFF000000\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B92)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318B90_thumb)
		);
}

// patch for 0x318BA0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318BAC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318BA0()
{
	__asm(
	".thumb\n"
		"MOV R8, R3\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R8, Offset_CPathFind__m_pNaviLinks)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"LDR R1, [R3,R1]\n"
		"MOV R9, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318BAC_thumb)
		);
}

// patch for 0x318BDC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318BEA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318BDC()
{
	__asm(
	".thumb\n"
		"LDR R2, [R2,R5,LSL#2]\n"
		"LSRS R3, R2, #16\n"
		"ADD R6, R10, R3,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R6, [R6,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318BEA_thumb)
		);
}

// patch for 0x318BF0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318BFC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318BF0()
{
	__asm(
	".thumb\n"
		"BFC R2, #16, #16\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CAutomobile__HasCarStoppedBecauseOfLight_318BFC_thumb)
		);
}

// patch for 0x318C4E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TestCrossesRoad_318CB0_thumb = 0;	// loc_318CB0
	uintptr_t Address_GTA_SA_2_00_CPathFind__TestCrossesRoad_318C5E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TestCrossesRoad_318C4E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [R12,R4]\n"
		"CBZ R4, 1f\n"
		"UXTH R3, R2\n"
		"ADD R0, R0, R3,LSL#2\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TestCrossesRoad_318C5E_thumb)

		// Branches
		"1:\n"	// loc_318CB0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TestCrossesRoad_318CB0_thumb)
		);
}

// patch for 0x318C60
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TestCrossesRoad_318C6E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TestCrossesRoad_318C60()
{
	__asm(
	".thumb\n"
		"BEQ 500f\n"
		"LSR R0, R1, #0x10\n"
		"MOV R1, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R1, R4, R1,LSL#2\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TestCrossesRoad_318C6E_thumb)
		);
}

// patch for 0x318C78
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TestCrossesRoad_318C84_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TestCrossesRoad_318C78()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"MOV LR, R2,LSR#16\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pNodeLinks)
		"LDR R2, [R12,R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TestCrossesRoad_318C84_thumb)
		);
}

// patch for 0x318CB8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TestCrossesRoad_318CC2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TestCrossesRoad_318CB8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathIntersections)
		"LDR R0, [R12,R0]\n"
		"LDRB R0, [R0,R5]\n"
		"AND R0, R0, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TestCrossesRoad_318CC2_thumb)
		);
}

// patch for 0x318CE6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindStartPointOfRegion_318CF2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindStartPointOfRegion_318CE6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S4, fPathsMapMinCoord)
		"VADD.F32 S0, S0, S4\n"
		"VADD.F32 S2, S2, S4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindStartPointOfRegion_318CF2_thumb)
		);
}

// patch for 0x318D22
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D2E_thumb = 0;	// loc_318D2E
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D22()
{
	__asm(
	".thumb\n"
		"VMOV S6, R1\n"
		"MOV LR, R6,LSL#10\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, Offset_CPathFind__m_dwNumCarPathLinks)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D2E_thumb)
		);
}

// patch for 0x318D32
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318DB4_thumb = 0;	// loc_318DB4
	uintptr_t Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D3C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D32()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R3,R1]\n"
		"CBZ R1, 1f\n"
		"LDR R1, [R3,R12]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D3C_thumb)

		// Branches
		"1:\n"	// loc_318DB4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318DB4_thumb)
		);
}

// patch for 0x318D44
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D4C_thumb = 0;	// loc_318D4C
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D44()
{
	__asm(
	".thumb\n"
		"MOV R4, R3\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pNaviNodes)
		"MOVS R5, #0\n"
		"MOVS R6, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D4C_thumb)
		);
}

// patch for 0x318D4E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D58_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D4E()
{
	__asm(
	".thumb\n"
		"MOV R2, R5\n"
		"ADD R2, 0x10\n"
		"LDR R2, [R3,R2]\n"
		"VMOV S10, R2\n"
		"VCVT.F32.S32 S10, S10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D58_thumb)
		);
}

// patch for 0x318D72
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D7E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D72()
{
	__asm(
	".thumb\n"
		"LDR R2, [R3,#0x14]\n"
		"VMOV S10, R2\n"
		"VCVT.F32.S32 S10, S10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D7E_thumb)
		);
}

// patch for 0x318DAC
extern "C"
{
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318DAC()
{
	__asm(
	".thumb\n"
		"ADDS R6, #1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, SizeOfCCarPathLink)
		"CMP R6, R1\n"
		"BLT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318DB4_thumb)

		// Branches
		"1:\n"	// loc_318D4C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D4C_thumb)
		);
}

// patch for 0x318DB8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318DC2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318DB8()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iTotalNumberOfPathFiles)
		"BNE 1f\n"
		"POP {R8,R9,R11}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318DC2_thumb)

		// Branches
		"1:\n"	// loc_318D2E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__SetLinksBridgeLights_318D2E_thumb)
		);
}

// patch for 0x318DD6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318DE2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318DD6()
{
	__asm(
	".thumb\n"
		"BEQ 500f\n"
		"ADD LR, R1, R12,LSL#2\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [LR,R4]\n"
		"CMP R4, #0\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318DE2_thumb)
		);
}

// patch for 0x318DFC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E08_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318DFC()
{
	__asm(
	".thumb\n"
		"BEQ 500f\n"
		"MOV R4, LR\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pPathNodes)
		"MOV R5, #1\n"
		"STRB R5, [R3]\n"
		"LDR R4, [R4]\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E08_thumb)
		);
}

// patch for 0x318E0A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E14_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E0A()
{
	__asm(
	".thumb\n"
		"MOV R2, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"ADD R2, R4, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E14_thumb)
		);
}

// patch for 0x318E1A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E24_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E1A()
{
	__asm(
	".thumb\n"
		"MOV R5, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R5, SizeOfCPathNodeDividedBy4)
		"ADD R3, R4, R5,LSL#2\n"
		"LDRH R4, [R3,#0x18]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E24_thumb)
		);
}

// patch for 0x318E2A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E32 = 0;
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E3A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E2A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pNodeLinks)
		"LDR R2, [LR,R2]\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R4, Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E32)
		"LDR R4, [R4]\n"
		"ADD R4, R4, R12,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [R4,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E3A_thumb)
		);
}

// patch for 0x318E4C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318EF2_thumb = 0;	// loc_318EF2
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E54_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E4C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E54_thumb)

		// Branches
		"1:\n"	// loc_318EF2
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318EF2_thumb)
		);
}

// patch for 0x318E56
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E60_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E56()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"ADD R5, R3, #8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E60_thumb)
		);
}

// patch for 0x318E64
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E72_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E64()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R5\n"
		"VLD1.64 {Q9}, [R0]\n"
		"POP {R0, R1}\n"
		"ADDS R1, #8\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R1\n"
		"VLD1.64 {Q9}, [R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318E72_thumb)
		);
}

// patch for 0x318E7A



// patch for 0x318ECC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318ED4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318ECC()
{
	__asm(
	".thumb\n"
		"MOV R1, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"VMOV.F32 S0, #0.125\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318ED4_thumb)
		);
}

// patch for 0x318ED8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318EE4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318ED8()
{
	__asm(
	".thumb\n"
		"LDR R2, [R1,#0x1C]\n"
		"LDR R3, [R1,#0x20]\n"
		"LDR R1, [R1,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318EE4_thumb)
		);
}

// patch for 0x318EF2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318F02_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318EF2()
{
	__asm(
	".thumb\n"
		"LDR R1, [R3,#0x1C]\n"
		"VMOV.F32 S0, #0.125\n"
		"LDR R2, [R3,#0x20]\n"
		"LDR R3, [R3,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318F02_thumb)
		);
}

// patch for 0x318F3C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318F44_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318F3C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x18\n"
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"VMOV S12, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318F44_thumb)
		);
}

// patch for 0x318FBE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318FCA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318FBE()
{
	__asm(
	".thumb\n"
		"BEQ 500f\n"
		"ADD R6, R1, R6,LSL#2\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R6,R5]\n"
		"CMP R5, #0\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318FCA_thumb)
		);
}

// patch for 0x318FD2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_31916A_thumb = 0;	// loc_31916A
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318FDC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318FD2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R12,R1]\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318FDC_thumb)

		// Branches
		"1:\n"	// loc_31916A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_31916A_thumb)
		);
}

// patch for 0x318FE4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318FF4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318FE4()
{
	__asm(
	".thumb\n"
		"BEQ 500f\n"
		"MOV R0, R6\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"MOV R1, R12\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"MOV R6, #1\n"
		"STRB R6, [LR]\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_318FF4_thumb)
		);
}

// patch for 0x319000
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_31900E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319000()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"LSRS R2, R3, #0x10\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_31900E_thumb)
		);
}

// patch for 0x31901A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319026_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_31901A()
{
	__asm(
	".thumb\n"
		"ADD R8, R8, #8\n"
		"LDR R0, [R8,#0x14]\n"
		"ADD R6, R6, #8\n"
		"LDR R1, [R6,#0x14]\n"
		"ADD R10, R10, #0xA\n"
		"LDR R2, [R10,#0x16]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319026_thumb)
		);
}

// patch for 0x319040
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319048_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319040()
{
	__asm(
	".thumb\n"
		"ADD R11, R11, #2\n"
		"LDR R0, [R11,#0x16]\n"
		"VMOV S6, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319048_thumb)
		);
}

// patch for 0x319098
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_3190A0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319098()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x14\n"
		"LDR R0, [R8,R0]\n"
		"MOV R1, 0x14\n"
		"LDR R1, [R6,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_3190A0_thumb)
		);
}

// patch for 0x3190C0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_3190C8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_3190C0()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x16\n"
		"LDR R0, [R10,R0]\n"
		"MOV R1, 0x16\n"
		"LDR R1, [R11,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_3190C8_thumb)
		);
}

// patch for 0x319100
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319108_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319100()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x16\n"
		"LDR R0, [R10,R0]\n"
		"MOV R1, 0x14\n"
		"LDR R1, [R8,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319108_thumb)
		);
}

// patch for 0x319118
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319120_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319118()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x18\n"
		"LDR R0, [R9,R0]\n"
		"VMUL.F32 S0, S0, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319120_thumb)
		);
}

// patch for 0x31918C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319194_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_31918C()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x16\n"
		"LDR R0, [R10,R0]\n"
		"MOV R1, 0x14\n"
		"LDR R1, [R8,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_319194_thumb)
		);
}

// patch for 0x3191A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_3191A8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_3191A0()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x18\n"
		"LDR R0, [R9,R0]\n"
		"VCVT.F32.S32 S2, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindNodeCoorsForScript_3191A8_thumb)
		);
}

// patch for 0x31928A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Shutdown_319204_thumb = 0;	// loc_319204
	uintptr_t Address_GTA_SA_2_00_CPathFind__Shutdown_319294_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Shutdown_31928A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimension)
		"BNE 1f\n"
		"ADD SP, SP, #4\n"
		"POP {R8-R11}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Shutdown_319294_thumb)

		// Branches
		"1:\n"	// loc_319204
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Shutdown_319204_thumb)
		);
}

// patch for 0x3192B8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForWandering_3192C0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForWandering_3192B8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, Offset_CPathFind__m_pPathNodes)
		"LDR R12, [R1,R12]\n"
		"CMP R12, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForWandering_3192C0_thumb)
		);
}

// patch for 0x3192C8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForWandering_3192D2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForWandering_3192C8()
{
	__asm(
	".thumb\n"
		"VLDR S10, 101f\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForWandering_3192D2_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, 0.00775)
		);
}

// patch for 0x3192D8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForWandering_3192E4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForWandering_3192D8()
{
	__asm(
	".thumb\n"
		"LDR R12, [R1,#0x1C]\n"
		"LDR R3, [R1,#0x20]\n"
		"LDR LR, [R1,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForWandering_3192E4_thumb)
		);
}

// patch for 0x31937C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForCoors_319390_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForCoors_31937C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, Offset_CPathFind__m_pPathNodes)
		"LDR R12, [R4,R12]\n"
		"CMP R12, #0\n"
		"BEQ 500f\n"
		"ADD R0, R0, LR,LSL#2\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"500:\n"	// past the IT block
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForCoors_319390_thumb)
		);
}

// patch for 0x319398
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForCoors_3193A0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForCoors_319398()
{
	__asm(
	".thumb\n"
		"MOV R1, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LSRS R5, R2, #0x10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForCoors_3193A0_thumb)
		);
}

// patch for 0x3193A2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForCoors_3193AC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForCoors_3193A2()
{
	__asm(
	".thumb\n"
		"MOV R2, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"ADD R1, R12, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__TakeWidthIntoAccountForCoors_3193AC_thumb)
		);
}

// patch for 0x319484
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_31948C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_319484()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S8, fPathsMapMaxCoord)
		"VSUB.F32 S4, S2, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_31948C_thumb)
		);
}

// patch for 0x319492
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_31949C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_319492()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"VADD.F32 S10, S6, S0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R9, iNumberOfPathFilesPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_31949C_thumb)
		);
}

// patch for 0x3194EC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_3194F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_3194EC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R10, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R10, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_3194F4_thumb)
		);
}

// patch for 0x3194FA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_319508_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_3194FA()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R9, R2\n"
		"CMP R4, #0\n"
		"IT LE\n"
		"MOVLE R4, R1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_319508_thumb)
		);
}

// patch for 0x319512
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_31956E_thumb = 0;	// loc_31956E
	uintptr_t Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_31951C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_319512()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R1\n"
		"CMP R0, R4\n"
		"BGT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_31951C_thumb)

		// Branches
		"1:\n"	// loc_31956E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_31956E_thumb)
		);
}

// patch for 0x31952C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_319534_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_31952C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimensionNegated)
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R2, iNumberOfPathFilesPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_319534_thumb)
		);
}

// patch for 0x31953A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_319544_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_31953A()
{
	__asm(
	".thumb\n"
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R1, iNumberOfPathFilesPerDimension)
		"ADD R2, R6\n"
		"IT GT\n"
		"MOVGT R5, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_319544_thumb)
		);
}

// patch for 0x31954E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_319558_thumb = 0;	// loc_319558
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_31954E()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		"MOV R2, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimension)
		"ADD R0, R1, R2\n"
		"POP {R2, R3}\n"
		"SUBS R6, R2, R5\n"
		"ADD R5, R0, R9\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__MarkRegionsForCoors_319558_thumb)
		);
}

// patch for 0x319648
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319652_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319648()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"VLDR S4, [SP,#0x58+"/* var_48 */"-0x48]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R9, iNumberOfPathFilesPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319652_thumb)
		);
}

// patch for 0x31965E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_31966A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_31965E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S10, fPathsMapMaxCoord)
		"VADD.F32 S2, S2, S8\n"
		"VADD.F32 S8, S4, S8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_31966A_thumb)
		);
}

// patch for 0x3196B6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3196C0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_3196B6()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R10, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R10, R0\n"
		"CMP R2, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3196C0_thumb)
		);
}

// patch for 0x3196C4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3196CC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_3196C4()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R9, R2\n"
		"CMP R4, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3196CC_thumb)
		);
}

// patch for 0x3196D0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3196D8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_3196D0()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R4, R0\n"
		"CMP R3, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3196D8_thumb)
		);
}

// patch for 0x3196DC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3196E4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_3196DC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R1\n"
		"CMP R0, R4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3196E4_thumb)
		);
}

// patch for 0x3196F8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319700_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_3196F8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimensionNegated)
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R2, iNumberOfPathFilesPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319700_thumb)
		);
}

// patch for 0x319706
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319710_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319706()
{
	__asm(
	".thumb\n"
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R1, iNumberOfPathFilesPerDimension)
		"ADD R2, R6\n"
		"IT GT\n"
		"MOVGT R5, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319710_thumb)
		);
}

// patch for 0x31971A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319724_thumb = 0;	// loc_319724
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_31971A()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		"MOV R2, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimension)
		"ADD R0, R1, R2\n"
		"POP {R2, R3}\n"
		"SUBS R6, R2, R5\n"
		"ADD R5, R0, R9\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319724_thumb)
		);
}

// patch for 0x319754
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_31975C = 0;
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319762_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319754()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R10, iNumberOfPathFilesPerDimensionMinusOne)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CPathFind__UpdateStreaming_31975C)
		"VLDR S8, 101f\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S10, fPathsMapMaxCoord)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319762_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, 300.0)
		);
}

// patch for 0x31976A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319774_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_31976A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"VADD.F32 S6, S2, S0\n"
		"VADD.F32 S2, S2, S8\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319774_thumb)
		);
}

// patch for 0x3197C8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3197D0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_3197C8()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R11, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3197D0_thumb)
		);
}

// patch for 0x3197D6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3197E4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_3197D6()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R10, R1\n"
		"CMP R4, #0\n"
		"IT LE\n"
		"MOVLE R4, R8\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3197E4_thumb)
		);
}

// patch for 0x3197EE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_31984A_thumb = 0;	// loc_31984A
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3197F8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_3197EE()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R2\n"
		"CMP R0, R4\n"
		"BGT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3197F8_thumb)

		// Branches
		"1:\n"	// loc_31984A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_31984A_thumb)
		);
}

// patch for 0x319806
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319812 = 0;
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319810_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319806()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimensionNegated)
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R1, iNumberOfPathFilesPerDimension)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319812)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319810_thumb)
		);
}

// patch for 0x31981C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319824_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_31981C()
{
	__asm(
	".thumb\n"
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R1, iNumberOfPathFilesPerDimension)
		"MOV R2, #0xFFFE\n"
		"MOVT R2, #0xFFFF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319824_thumb)
		);
}

// patch for 0x31982C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319834_thumb = 0;	// loc_319834
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_31982C()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		"MOV R2, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimension)
		"ADD R0, R1, R2\n"
		"POP {R2, R3}\n"
		"ADD R5, R0, R10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319834_thumb)
		);
}

// patch for 0x319872
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_31987C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319872()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S20, fPathsMapMaxCoord)
		"VLDR S22, 101f\n"
		"LDR R0, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_31987C_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, 750.0)
		);
}

// patch for 0x31988E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319898_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_31988E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R11, iNumberOfPathFilesPerDimensionMinusOne)
		"ADD R2, R1, #0x30\n"
		"CMP R1, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319898_thumb)
		);
}

// patch for 0x31989C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3198A6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_31989C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionMinusOne)
		"VLDR S0, [R2]\n"
		"VLDR S2, [R2,#4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3198A6_thumb)
		);
}

// patch for 0x3198FC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319904_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_3198FC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R8, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R8, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319904_thumb)
		);
}

// patch for 0x31990A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319914_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_31990A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R11, R2\n"
		"CMP R10, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319914_thumb)
		);
}

// patch for 0x319918
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319920_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319918()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R10, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R10, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319920_thumb)
		);
}

// patch for 0x31992A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319934_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_31992A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, iNumberOfPathFilesPerDimensionMinusOne)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R3, R1\n"
		"CMP R3, R10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319934_thumb)
		);
}

// patch for 0x319940
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319948_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319940()
{
	__asm(
	".thumb\n"
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R2, iNumberOfPathFilesPerDimension)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimensionNegated)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319948_thumb)
		);
}

// patch for 0x319962
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_31996E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319962()
{
	__asm(
	".thumb\n"
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R2, iNumberOfPathFilesPerDimension)
		"IT LE\n"
		"MOVLE R2, R4\n"
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R1, iNumberOfPathFilesPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_31996E_thumb)
		);
}

// patch for 0x319978
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319982_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319978()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		"MOV R2, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimension)
		"SUB R0, R0, R2\n"
		"POP {R2, R3}\n"
		"ADD R0, R2\n"
		"MOV R4, R0\n"
		ASM_SUB_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimensionPlus1)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319982_thumb)
		);
}

// patch for 0x3199A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_31998A_thumb = 0;	// loc_31998A
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3199EA_thumb = 0;	// loc_3199EA
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_3199A0()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimension)
		"CMP R9, R10\n"
		"BLT 1f\n"
		"B 2f\n"

		// Branches
		"1:\n"	// loc_31998A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_31998A_thumb)
		"2:\n"	// loc_3199EA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3199EA_thumb)
		);
}

// patch for 0x3199F0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3199F8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_3199F0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_bForbiddenForScriptedCarsEnabled)
		"LDRB R0, [R1,R0]\n"
		"CMP R0, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_3199F8_thumb)
		);
}

// patch for 0x3199FE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319A0A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_3199FE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_fForbiddenForScrCarsX1)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_fForbiddenForScrCarsY2)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_fForbiddenForScrCarsY1)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319A0A_thumb)
		);
}

// patch for 0x319A0C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319A16_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319A0C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S0, fPathsMapMaxCoord)
		"ADD R0, R3\n"
		"VLDR S10, 101f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319A16_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, 750.0)
		);
}

// patch for 0x319A1A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319A24_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319A1A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_fForbiddenForScrCarsX2)
		"ADD R1, R3\n"
		"VLDR S8, [R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319A24_thumb)
		);
}

// patch for 0x319A28
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319A34_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319A28()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"VLDR S4, [R1]\n"
		"ADDS R1, R3, R2\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R10, iNumberOfPathFilesPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319A34_thumb)
		);
}

// patch for 0x319A7E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319A88_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319A7E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R9, R0\n"
		"CMP R2, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319A88_thumb)
		);
}

// patch for 0x319A8C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319A96_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319A8C()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R10, R2\n"
		"CMP R11, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319A96_thumb)
		);
}

// patch for 0x319A9A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AA4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319A9A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R11, R0\n"
		"CMP R3, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AA4_thumb)
		);
}

// patch for 0x319AA8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AB0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319AA8()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R1\n"
		"CMP R0, R11\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AB0_thumb)
		);
}

// patch for 0x319AC0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AC8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319AC0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimensionNegated)
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R2, iNumberOfPathFilesPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AC8_thumb)
		);
}

// patch for 0x319ACE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AD6 = 0;
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AD8 = 0;
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AD8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319ACE()
{
	__asm(
	".thumb\n"
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R1, iNumberOfPathFilesPerDimension)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AD6)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R6, Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AD8)
		"ADD R2, R5\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AD8_thumb)
		);
}

// patch for 0x319AEA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AF6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319AEA()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R3}\n"
		"MOV R1, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimension)
		"ADD R2, R2, R1\n"
		"POP {R1, R3}\n"
		"PUSH {R2, R3}\n"
		"MOV R2, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimension)
		"ADD R0, R1, R2\n"
		"POP {R2, R3}\n"
		"ADD R6, R2, R10\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AF6_thumb)
		);
}

// patch for 0x319B14
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AFA_thumb = 0;	// loc_319AFA
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B1C_thumb = 0;	// loc_319B1C
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319B14()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iNumberOfPathFilesPerDimension)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimension)
		"CMP R5, R11\n"
		"BLT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B1C_thumb)

		// Branches
		"1:\n"	// loc_319AFA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319AFA_thumb)
		);
}

// patch for 0x319B2C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B34_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319B2C()
{
	__asm(
	".thumb\n"
		"MOV R8, R2\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R8, Offset_CPathFind__m_pPathNodes)
		"LDR R11, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B34_thumb)
		);
}

// patch for 0x319B68
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B70_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319B68()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iNumberOfPathFilesPerDimension_multiplied_by_sizeof_CNodeAddress)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimension)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B70_thumb)
		);
}

// patch for 0x319B74
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B7E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319B74()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R11, iNumberOfPathFilesPerDimension)
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iNumberOfPathFilesPerDimension)
		"ADD R8, R8, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B7E_thumb)
		);
}

// patch for 0x319B80
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B36_thumb = 0;	// loc_319B36
	uintptr_t Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B88_thumb = 0;	// loc_319B88
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__UpdateStreaming_319B80()
{
	__asm(
	".thumb\n"
		"ADD R10, R10, #1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimension)
		"BNE 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B88_thumb)

		// Branches
		"1:\n"	// loc_319B36
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__UpdateStreaming_319B36_thumb)
		);
}

// patch for 0x319BE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__MakeRequestForNodesToBeLoaded_319BF0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__MakeRequestForNodesToBeLoaded_319BE8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, Offset_CPathFind__m_fForbiddenForScrCarsX1)
		"VLDR S0, [SP,#"/* arg_0 */"0x0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__MakeRequestForNodesToBeLoaded_319BF0_thumb)
		);
}

// patch for 0x319BF4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__MakeRequestForNodesToBeLoaded_319C02_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__MakeRequestForNodesToBeLoaded_319BF4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, Offset_CPathFind__m_bForbiddenForScriptedCarsEnabled)
		"MOVS R1, #1\n"
		"STRB R1, [R0,R12]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_fForbiddenForScrCarsX2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__MakeRequestForNodesToBeLoaded_319C02_thumb)
		);
}

// patch for 0x319C04
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__MakeRequestForNodesToBeLoaded_319C0E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__MakeRequestForNodesToBeLoaded_319C04()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_fForbiddenForScrCarsY1)
		"STR R3, [R0,R1]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_fForbiddenForScrCarsY2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__MakeRequestForNodesToBeLoaded_319C0E_thumb)
		);
}

// patch for 0x319C20
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319C28_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319C20()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_fForbiddenForScrCarsX1)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_fForbiddenForScrCarsY2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319C28_thumb)
		);
}

// patch for 0x319C2A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319C34_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319C2A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_fForbiddenForScrCarsX2)
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S0, fPathsMapMaxCoord)
		"ADD R1, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319C34_thumb)
		);
}

// patch for 0x319C38
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319C42_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319C38()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_fForbiddenForScrCarsY1)
		"ADD R2, R0\n"
		"VLDR S8, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319C42_thumb)
		);
}

// patch for 0x319C52
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319C60_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319C52()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionMinusOne)
		"VLDR S6, [R2]\n"
		"VADD.F32 S4, S4, S0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, iNumberOfPathFilesPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319C60_thumb)
		);
}

// patch for 0x319C9E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CA8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319C9E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R2, R1\n"
		"CMP LR, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CA8_thumb)
		);
}

// patch for 0x319CAC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CB4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CAC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(LR, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE LR, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CB4_thumb)
		);
}

// patch for 0x319CBA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CC8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CBA()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R12, R4\n"
		"CMP R5, #0\n"
		"IT GT\n"
		"MOVGT R3, R5\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfPathFilesPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CC8_thumb)
		);
}

// patch for 0x319CDA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CE6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CDA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimensionNegated)
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R4, iNumberOfPathFilesPerDimension)
		"MVN R3, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CE6_thumb)
		);
}

// patch for 0x319CEA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CF6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CEA()
{
	__asm(
	".thumb\n"
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R3, iNumberOfPathFilesPerDimension)
		"IT GT\n"
		"MOVGT R5, R3\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes_divided_by_sizeOf_CNodeAddress_minus_NumberOfPathFilesPerDimension_minus_2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CF6_thumb)
		);
}

// patch for 0x319CF8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319D00_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319CF8()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimension)
		"SUB R3, R3, R0\n"
		"POP {R0, R1}\n"
		"ADD R0, R0, R3,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319D00_thumb)
		);
}

// patch for 0x319D14
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319D10_thumb = 0;	// loc_319D10
	uintptr_t Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319D1C_thumb = 0;	// loc_319D1C
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319D14()
{
	__asm(
	".thumb\n"
		"ADDS R4, #1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimension_multiplied_by_sizeof_CNodeAddress)
		"CMP R4, R2\n"
		"BLT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319D1C_thumb)

		// Branches
		"1:\n"	// loc_319D10
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__HaveRequestedNodesBeenLoaded_319D10_thumb)
		);
}

// patch for 0x319D40
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319D48_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319D40()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S0, fPathsMapMaxCoord)
		"VMOV S4, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319D48_thumb)
		);
}

// patch for 0x319D62
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319D6C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319D62()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionMinusOne)
		"VADD.F32 S4, S4, S0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, iNumberOfPathFilesPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319D6C_thumb)
		);
}

// patch for 0x319D96
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DA0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319D96()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionMinusOne)
		"VCVT.S32.F32 S0, S0\n"
		"IT GE\n"
		"MOVGE R1, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DA0_thumb)
		);
}

// patch for 0x319DB4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DBC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DB4()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(LR, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE LR, R2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DBC_thumb)
		);
}

// patch for 0x319DC2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DD0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DC2()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R12, R4\n"
		"CMP R5, #0\n"
		"IT GT\n"
		"MOVGT R3, R5\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iNumberOfPathFilesPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DD0_thumb)
		);
}

// patch for 0x319DE2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DEE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DE2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimensionNegated)
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R4, iNumberOfPathFilesPerDimension)
		"MVN R3, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DEE_thumb)
		);
}

// patch for 0x319DF2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DFE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DF2()
{
	__asm(
	".thumb\n"
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R3, iNumberOfPathFilesPerDimension)
		"IT GT\n"
		"MOVGT R5, R3\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes_divided_by_sizeOf_CNodeAddress_minus_NumberOfPathFilesPerDimension_minus_2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319DFE_thumb)
		);
}

// patch for 0x319E00
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319E08_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319E00()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimension)
		"SUB R3, R3, R0\n"
		"POP {R0, R1}\n"
		"ADD R0, R0, R3,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319E08_thumb)
		);
}

// patch for 0x319E1C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319E18_thumb = 0;	// loc_319E18
	uintptr_t Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319E24_thumb = 0;	// loc_319E24
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319E1C()
{
	__asm(
	".thumb\n"
		"ADDS R5, #1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimension_multiplied_by_sizeof_CNodeAddress)
		"CMP R5, R1\n"
		"BLT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319E24_thumb)

		// Branches
		"1:\n"	// loc_319E18
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AreNodesLoadedForArea_319E18_thumb)
		);
}

// patch for 0x319E5E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319E68_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319E5E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(S10, fPathsMapMaxCoord)
		"VADD.F32 S2, S2, S6\n"
		"LDR R0, =("/* ToBeStreamed_ptr */"0x67899C - 0x319E7C)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319E68_thumb)
		);
}

// patch for 0x319E6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319E74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319E6C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R9, iNumberOfPathFilesPerDimensionMinusOne)
		"VADD.F32 S0, S8, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319E74_thumb)
		);
}

// patch for 0x319EC2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319ECC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319EC2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iNumberOfPathFilesPerDimensionMinusOne)
		"VCVT.S32.F32 S6, S6\n"
		"VCVT.S32.F32 S0, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319ECC_thumb)
		);
}

// patch for 0x319EE4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319EEC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319EE4()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R10, iNumberOfPathFilesPerDimensionMinusOne)
		"IT GE\n"
		"MOVGE R10, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319EEC_thumb)
		);
}

// patch for 0x319EF2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F00_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319EF2()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R9, R2\n"
		"CMP R4, #0\n"
		"IT LE\n"
		"MOVLE R4, R1\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimensionMinusOne)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F00_thumb)
		);
}

// patch for 0x319F0A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F66_thumb = 0;	// loc_319F66
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F14_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F0A()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimensionMinusOne)
		"IT LT\n"
		"MOVLT R0, R1\n"
		"CMP R0, R4\n"
		"BGT 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F14_thumb)

		// Branches
		"1:\n"	// loc_319F66
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F66_thumb)
		);
}

// patch for 0x319F24
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F2C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F24()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimensionNegated)
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R2, iNumberOfPathFilesPerDimension)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F2C_thumb)
		);
}

// patch for 0x319F32
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F3C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F32()
{
	__asm(
	".thumb\n"
		ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL("CMN", R1, iNumberOfPathFilesPerDimension)
		"ADD R2, R6\n"
		"IT GT\n"
		"MOVGT R5, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F3C_thumb)
		);
}

// patch for 0x319F46
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F50_thumb = 0;	// loc_319F50
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F46()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		"MOV R2, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, iNumberOfPathFilesPerDimension)
		"ADD R0, R1, R2\n"
		"POP {R2, R3}\n"
		"SUBS R6, R2, R5\n"
		"ADD R5, R0, R9\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F50_thumb)
		);
}

// patch for 0x319F6E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F76 = 0;
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F78_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F6E()
{
	__asm(
	".thumb\n"
		"MOV R4, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimensionMinusOne)
		"LDR R0, =("/* ToBeStreamed_ptr */"0x67899C - 0x319F76)\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F76)
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x20+"/* var_20 */"-0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F78_thumb)
		);
}

// patch for 0x319FB2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FC6_thumb = 0;	// loc_319FC6
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FBE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FB2()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimension)
		"ADD R0, R0, R1\n"
		"POP {R1, R2}\n"
		"LDRB R0, [R0,#1]\n"
		"CBZ R0, 1f\n"
		"MOV R0, #0x63AF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FBE_thumb)

		// Branches
		"1:\n"	// loc_319FC6
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FC6_thumb)
		);
}

// patch for 0x319FC6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FDA_thumb = 0;	// loc_319FDA
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FD2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FC6()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimension)
		"ADD R0, R9, R1\n"
		"POP {R1, R2}\n"
		"LDRB R0, [R0,#2]\n"
		"CBZ R0, 1f\n"
		"MOV R0, #0x63B7\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FD2_thumb)

		// Branches
		"1:\n"	// loc_319FDA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FDA_thumb)
		);
}

// patch for 0x319FDA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FEE_thumb = 0;	// loc_319FEE
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FE6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FDA()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimension)
		"ADD R0, R10, R1\n"
		"POP {R1, R2}\n"
		"LDRB R0, [R0,#3]\n"
		"CBZ R0, 1f\n"
		"MOV R0, #0x63BF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FE6_thumb)

		// Branches
		"1:\n"	// loc_319FEE
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FEE_thumb)
		);
}

// patch for 0x319FEE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A002_thumb = 0;	// loc_31A002
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FFA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FEE()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimension)
		"ADD R0, R11, R1\n"
		"POP {R1, R2}\n"
		"LDRB R0, [R0,#4]\n"
		"CBZ R0, 1f\n"
		"MOV R0, #0x63C7\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319FFA_thumb)

		// Branches
		"1:\n"	// loc_31A002
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A002_thumb)
		);
}

// patch for 0x31A002
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A016_thumb = 0;	// loc_31A016
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A00E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A002()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimension)
		"ADD R0, R6, R1\n"
		"POP {R1, R2}\n"
		"LDRB R0, [R0,#5]\n"
		"CBZ R0, 1f\n"
		"MOV R0, #0x63CF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A00E_thumb)

		// Branches
		"1:\n"	// loc_31A016
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A016_thumb)
		);
}

// patch for 0x31A016
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A02A_thumb = 0;	// loc_31A02A
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A022_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A016()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iNumberOfPathFilesPerDimension)
		"ADD R0, R8, R1\n"
		"POP {R1, R2}\n"
		"LDRB R0, [R0,#6]\n"
		"CBZ R0, 1f\n"
		"MOV R0, #0x63D7\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A022_thumb)

		// Branches
		"1:\n"	// loc_31A02A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A02A_thumb)
		);
}

// patch for 0x31A03C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F9E_thumb = 0;	// loc_319F9E
	uintptr_t Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A044_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A03C()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, iNumberOfPathFilesPerDimension)
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R5, iNumberOfPathFilesPerDimension)
		"BNE 1f\n"
		"ADD SP, SP, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_31A044_thumb)

		// Branches
		"1:\n"	// loc_319F9E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__LoadSceneForPathNodes_319F9E_thumb)
		);
}

// patch for 0x31A090
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__IsWaterNodeNearby_31A09A_thumb = 0;	// loc_31A09A
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__IsWaterNodeNearby_31A090()
{
	__asm(
	".thumb\n"
		"MOVS R1, #0\n"
		"VMOV S2, R2\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, Offset_CPathFind__m_dwNumVehicleNodes)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__IsWaterNodeNearby_31A09A_thumb)
		);
}

// patch for 0x31A0A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__IsWaterNodeNearby_31A102_thumb = 0;	// loc_31A102
	uintptr_t Address_GTA_SA_2_00_CPathFind__IsWaterNodeNearby_31A0AA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__IsWaterNodeNearby_31A0A0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R2,R1]\n"
		"CBZ R1, 1f\n"
		"LDR R3, [R2,R12]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__IsWaterNodeNearby_31A0AA_thumb)

		// Branches
		"1:\n"	// loc_31A102
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__IsWaterNodeNearby_31A102_thumb)
		);
}

// patch for 0x31A106
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__IsWaterNodeNearby_31A110_thumb = 0;	// loc_31A110
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__IsWaterNodeNearby_31A106()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(LR, iTotalNumberOfPathFilesMinusOne)
		"BLT 1f\n"
		"MOVS R0, #0\n"
		"POP {R4,R5,R7,PC}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__IsWaterNodeNearby_31A110_thumb)

		// Branches
		"1:\n"	// loc_31A09A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__IsWaterNodeNearby_31A09A_thumb)
		);
}

// patch for 0x31A13C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__StartNewInterior_31A144_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__StartNewInterior_31A13C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_interiorAreaIDarray_index_0)
		"ADD R0, R2\n"
		"STRB R1, [R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__StartNewInterior_31A144_thumb)
		);
}

// patch for 0x31A200
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddNodeToNewInterior_31A208_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddNodeToNewInterior_31A200()
{
	__asm(
	".thumb\n"
		"MOV R0, R1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles)
		"PKHBT R0, R0, R6,LSL#16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddNodeToNewInterior_31A208_thumb)
		);
}

// patch for 0x31A4DC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A4E4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A4DC()
{
	__asm(
	".thumb\n"
		"MOV LR, R4\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(LR, iTotalNumberOfPathFiles)
		"LDR R4, [R12]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A4E4_thumb)
		);
}

// patch for 0x31A4E8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A4F0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A4E8()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R6, [R6,R0]\n"
		"POP {R0, R1}\n"
		"STRH R2, [R6,R4,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A4F0_thumb)
		);
}

// patch for 0x31A4F6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A502_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A4F6()
{
	__asm(
	".thumb\n"
		"MOV R4, R5\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pPathNodes)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		"LDR R2, [R4,R2,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A502_thumb)
		);
}

// patch for 0x31A506
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A51E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A506()
{
	__asm(
	".thumb\n"
		"MOV R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R2, R2, R3,LSL#2\n"
		"ADD R3, R4, R0,LSL#2\n"
		"LDR R1, [R2,#0x1C]\n"
		"LDR R4, [R3,#0x1C]\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x20\n"
		"ADD R0, R2\n"
		"VLD1.64 {Q9}, [R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A51E_thumb)
		);
}

// patch for 0x31A532
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A53C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A532()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x20\n"
		"ADD R0, R3\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R2}\n"
		"STR R1, [SP,#0x18+"/* var_18 */"-0x18]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A53C_thumb)
		);
}

// patch for 0x31A53E



// patch for 0x31A5B8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A5C4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A5B8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pLinkLengths)
		"LDR R6, [R2,R6]\n"
		"STRB R1, [R6,R3]\n"
		"MOVS R6, #0\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathIntersections)
		"LDR R1, [R2,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A5C4_thumb)
		);
}

// patch for 0x31A5CA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A5D6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A5CA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R2,R1]\n"
		"ADD R0, R1, R0,LSL#2\n"
		"LDRH R1, [R0,#0x18]!\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_SetOneAdjacentNodeForThisNode_31A5D6_thumb)
		);
}

// patch for 0x31A662
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A672_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A662()
{
	__asm(
	".thumb\n"
		"MOV R2, R6\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"ADD R2, R3, R2,LSL#2\n"
		"LDRH R2, [R2,#0x28]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A672_thumb)
		);
}

// patch for 0x31A684
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A690_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A684()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R1, R10, R1,LSL#2\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_interiorAreaIDarray_index_0)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A690_thumb)
		);
}

// patch for 0x31A6B0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A6BC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A6B0()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iTotalNumberOfPathFiles)
		"STR R1, [SP,#0x58+"/* var_28 */"-0x28]\n"
		"ADD R1, R10, R1,LSL#2\n"
		"PUSH {R2, R3}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pPathNodes)
		"STR R0, [R1,R2]\n"
		"POP {R2, R3}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A6BC_thumb)
		);
}

// patch for 0x31A6CC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A6D4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A6CC()
{
	__asm(
	".thumb\n"
		"MOV R3, R1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"LDR R1, =("/* XCoorGiven_ptr */"0x6778FC - 0x31A6E2)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A6D4_thumb)
		);
}

// patch for 0x31A700
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A70A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A700()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, SizeOfCPathNode)
		"ADD R11, R11, #4\n"
		"ADD LR, LR, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A70A_thumb)
		);
}

// patch for 0x31A73A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A746_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A73A()
{
	__asm(
	".thumb\n"
		"STR R2, [R0,#0x8]\n"
		"VMOV R2, S6\n"
		"STR R2, [R0,#0x4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A746_thumb)
		);
}

// patch for 0x31A74A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A756_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A74A()
{
	__asm(
	".thumb\n"
		"STR R2, [R0,#0xC]\n"
		"LDR R0, [R3]\n"
		"ADD R0, R5\n"
		"STRH R10, [R0,#-4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A756_thumb)
		);
}

// patch for 0x31A76C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A774_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A76C()
{
	__asm(
	".thumb\n"
		"STRH R1, [R0,#0x10]\n"
		"LDR R0, [R3]\n"
		"LDRH R2, [R0,R5]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31A774_thumb)
		);
}

// patch for 0x31AA04
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_19CF5C_arm = 0;	// j__ZN10CMemoryMgr6MallocEj
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AA0E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AA04()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pNodeLinks_index_TotalNumberOfPathFile)
		"STR R0, [R1,R2]\n"
		"POP {R2, R3}\n"
		"MOV R0, R8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AA0E_thumb)

		// Branches
		"1:\n"	// j__ZN10CMemoryMgr6MallocEj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_19CF5C_arm)
		);
}

// patch for 0x31AA14
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AA1E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AA14()
{
	__asm(
	".thumb\n"
		"PUSH {R2, R3}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pLinkLengths_index_TotalNumberOfPathFile)
		"STR R0, [R1,R2]\n"
		"POP {R2, R3}\n"
		"MOV R0, R8\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AA1E_thumb)

		// Branches
		"1:\n"	// j__ZN10CMemoryMgr6MallocEj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_19CF5C_arm)
		);
}

// patch for 0x31AA2A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AA34_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AA2A()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__pPathIntersections_index_TotalNumberOfPathFile)
		"STR R0, [R3,R1]\n"
		"POP {R1, R2}\n"
		"LDR R0, [R2]\n"
		"MOVS R2, #0\n"
		"STR R2, [SP,#0x58+"/* var_20 */"-0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AA34_thumb)
		);
}

// patch for 0x31AA90
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AA98_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AA90()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, SizeOfCPathNode)
		"LDR R2, [SP,#0x58+"/* var_20 */"-0x20]\n"
		"ADD R11, R11, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AA98_thumb)
		);
}

// patch for 0x31AAA0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AAA8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AAA0()
{
	__asm(
	".thumb\n"
		"MOV R0, R1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles)
		"ADD R3, R10, R0,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AAA8_thumb)
		);
}

// patch for 0x31AAAC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AAB6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AAAC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [R3,R4]\n"
		"STRH R2, [R4,R5]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R3,R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AAB6_thumb)
		);
}

// patch for 0x31AAEE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_1A10B4_arm = 0;	// j__Z29SetOneAdjacentNodeForThisNodeiaiiiRi
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AAFA_thumb = 0;	// loc_31AAFA
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AAEE()
{
	__asm(
	".thumb\n"
		"STRD R0, R9, [SP,#0x58+"/* var_58 */"-0x58]\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles)
		"MOV R2, R0\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AAFA_thumb)

		// Branches
		"1:\n"	// j__Z29SetOneAdjacentNodeForThisNodeiaiiiRi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_1A10B4_arm)
		);
}

// patch for 0x31AB0A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB16_thumb = 0;	// loc_31AB16
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB0A()
{
	__asm(
	".thumb\n"
		"STRD R0, R9, [SP,#0x58+"/* var_58 */"-0x58]\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles)
		"MOV R2, R0\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB16_thumb)

		// Branches
		"1:\n"	// j__Z29SetOneAdjacentNodeForThisNodeiaiiiRi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_1A10B4_arm)
		);
}

// patch for 0x31AB26
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB32_thumb = 0;	// loc_31AB32
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB26()
{
	__asm(
	".thumb\n"
		"STRD R0, R9, [SP,#0x58+"/* var_58 */"-0x58]\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles)
		"MOV R2, R0\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB32_thumb)

		// Branches
		"1:\n"	// j__Z29SetOneAdjacentNodeForThisNodeiaiiiRi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_1A10B4_arm)
		);
}

// patch for 0x31AB42
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB4E_thumb = 0;	// loc_31AB4E
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB42()
{
	__asm(
	".thumb\n"
		"STRD R0, R9, [SP,#0x58+"/* var_58 */"-0x58]\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles)
		"MOV R2, R0\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB4E_thumb)

		// Branches
		"1:\n"	// j__Z29SetOneAdjacentNodeForThisNodeiaiiiRi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_1A10B4_arm)
		);
}

// patch for 0x31AB5E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB6A_thumb = 0;	// loc_31AB6A
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB5E()
{
	__asm(
	".thumb\n"
		"STRD R0, R9, [SP,#0x58+"/* var_58 */"-0x58]\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles)
		"MOV R2, R0\n"
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB6A_thumb)

		// Branches
		"1:\n"	// j__Z29SetOneAdjacentNodeForThisNodeiaiiiRi
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_1A10B4_arm)
		);
}

// patch for 0x31AB8C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB94_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB8C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks_index_TotalNumberOfPathFile)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"STRH R9, [R1,R0,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB94_thumb)
		);
}

// patch for 0x31AB9C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31ABA4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AB9C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_dwNumVehicleNodes_index_TotalNumberOfPathFile)
		"LDR R1, =("/* NumNodesGiven_ptr */"0x679F30 - 0x31ABAC)\n"
		"MOVS R5, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31ABA4_thumb)
		);
}

// patch for 0x31ABBC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31ABC6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31ABBC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_dwNumNodes_index_TotalNumberOfPathFile)
		"STR R1, [R3,R6]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_dwNumPedNodes_index_TotalNumberOfPathFile)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31ABC6_thumb)
		);
}

// patch for 0x31ABC8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31ABD2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31ABC8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_dwNumCarPathLinks_index_TotalNumberOfPathFile)
		"STR R5, [R3,R1]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_dwNumAddresses_index_TotalNumberOfPathFile)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31ABD2_thumb)
		);
}

// patch for 0x31AC06
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AC10_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AC06()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles)
		"LDR R5, [R9,R4,LSL#2]\n"
		"LDR R8, [SP,#0x58+"/* var_2C */"-0x2C]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__CompleteNewInterior_31AC10_thumb)
		);
}

// patch for 0x31AD1A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AD2C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AD1A()
{
	__asm(
	".thumb\n"
		"MOV R6, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_dwNumAddresses)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R12, Offset_CPathFind__m_pPathNodes)
		"LDR R12, [LR,R12]\n"
		"MOV R10, LR\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R10, Offset_CPathFind__m_pNodeLinks)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AD2C_thumb)
		);
}

// patch for 0x31AD56
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AD60_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AD56()
{
	__asm(
	".thumb\n"
		"MOV R2, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		"SUBS R1, #0xC\n"
		"ADD R11, R12, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AD60_thumb)
		);
}

// patch for 0x31AD70
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AD78_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AD70()
{
	__asm(
	".thumb\n"
		"MOV R5, LR\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathIntersections)
		"MOV R1, LR\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pLinkLengths)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AD78_thumb)
		);
}

// patch for 0x31ADBA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE7A_thumb = 0;	// loc_31AE7A
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31ADC8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31ADBA()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R9, iTotalNumberOfPathFilesMinusOne)
		"BHI 1f\n"
		"ADD R0, R0, R9,LSL#6\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31ADC8_thumb)

		// Branches
		"1:\n"	// loc_31AE7A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE7A_thumb)
		);
}

// patch for 0x31ADD2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE88_thumb = 0;	// loc_31AE88
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31ADE0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31ADD2()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_1)
		"LDR R2, [R0,R1]\n"
		"CMP R2, #0\n"
		"BLT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31ADE0_thumb)

		// Branches
		"1:\n"	// loc_31AE88
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE88_thumb)
		);
}

// patch for 0x31ADE6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE94_thumb = 0;	// loc_31AE94
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31ADF4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31ADE6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_3)
		"LDR R2, [R0,R1]\n"
		"CMP R2, #0\n"
		"BLT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31ADF4_thumb)

		// Branches
		"1:\n"	// loc_31AE94
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE94_thumb)
		);
}

// patch for 0x31ADFA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEA0_thumb = 0;	// loc_31AEA0
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE08_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31ADFA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_5)
		"LDR R2, [R0,R1]\n"
		"CMP R2, #0\n"
		"BLT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_6)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE08_thumb)

		// Branches
		"1:\n"	// loc_31AEA0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEA0_thumb)
		);
}

// patch for 0x31AE0E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEAC_thumb = 0;	// loc_31AEAC
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE1C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE0E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_7)
		"LDR R1, [R0,R1]\n"
		"CMP R1, #0\n"
		"BLT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_8)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE1C_thumb)

		// Branches
		"1:\n"	// loc_31AEAC
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEAC_thumb)
		);
}

// patch for 0x31AE22
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEBA_thumb = 0;	// loc_31AEBA
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE30_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE22()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_9)
		"LDR R2, [R0,R1]\n"
		"CMP R2, #0\n"
		"BLT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_10)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE30_thumb)

		// Branches
		"1:\n"	// loc_31AEBA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEBA_thumb)
		);
}

// patch for 0x31AE36
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEC6_thumb = 0;	// loc_31AEC6
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE44_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE36()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_11)
		"LDR R2, [R0,R1]\n"
		"CMP R2, #0\n"
		"BLT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_12)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE44_thumb)

		// Branches
		"1:\n"	// loc_31AEC6
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEC6_thumb)
		);
}

// patch for 0x31AE4A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AED2_thumb = 0;	// loc_31AED2
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE58_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE4A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_13)
		"LDR R2, [R0,R1]\n"
		"CMP R2, #0\n"
		"BLT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_14)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE58_thumb)

		// Branches
		"1:\n"	// loc_31AED2
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AED2_thumb)
		);
}

// patch for 0x31AE6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE6C()
{
	__asm(
	".thumb\n"
		"MOV R0, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R0, R12, R0,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AE74_thumb)
		);
}

// patch for 0x31AEAC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEE4_thumb = 0;	// loc_31AEE4
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEAC()
{
	__asm(
	".thumb\n"
		"MOV R2, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_field_1544_index_7)
		"MOVS R6, #7\n"
		"B 1f\n"

		// Branches
		"1:\n"	// loc_31AEE4
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEE4_thumb)
		);
}

// patch for 0x31AEEC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEF4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEEC()
{
	__asm(
	".thumb\n"
		"STR R1, [R2]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_field_1544_index_1024)
		"LDR R6, [SP,#0x28+"/* var_20 */"-0x20]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AEF4_thumb)
		);
}

// patch for 0x31AF0E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AF18_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AF0E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pLinkLengths)
		"LDR R1, [LR,R1]\n"
		"AND R0, R0, #0xF\n"
		"ADD R0, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AF18_thumb)
		);
}

// patch for 0x31AF20
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AF28_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AF20()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathIntersections)
		"LDR R1, [LR,R1]\n"
		"AND R0, R0, #0xF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AF28_thumb)
		);
}

// patch for 0x31AF60
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AF68_thumb = 0;	// loc_31AF68
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31AF60()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_interiorAreaIDarray_index_0)
		"MOVS R6, #0\n"
		"STR R1, [SP,#0x78+"/* var_74 */"-0x74]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AF68_thumb)
		);
}

// patch for 0x31AF7C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AF84_thumb = 0;	// loc_31AF84
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31AF7C()
{
	__asm(
	".thumb\n"
		"MOV R0, R6\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles)
		"MOVS R1, #0\n"
		"STR R6, [SP,#0x78+"/* var_70 */"-0x70]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AF84_thumb)
		);
}

// patch for 0x31AF8A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B2C8_thumb = 0;	// loc_31B2C8
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AF9C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31AF8A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R4,R1]\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_dwNumVehicleNodes)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_dwNumNodes)
		"LDR R3, [R4,R3]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AF9C_thumb)

		// Branches
		"1:\n"	// loc_31B2C8
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B2C8_thumb)
		);
}

// patch for 0x31AFA6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AFB2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31AFA6()
{
	__asm(
	".thumb\n"
		"MOV LR, R4\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(LR, Offset_CPathFind__m_pPathNodes)
		"MOV R8, R4\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R8, Offset_CPathFind__m_dwNumNodes)
		"MOV R11, R4\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R11, Offset_CPathFind__m_pNodeLinks)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AFB2_thumb)
		);
}

// patch for 0x31AFB6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AFC2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31AFB6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1038)
		"ADD R3, R6\n"
		"STR R3, [SP,#0x78+"/* var_68 */"-0x68]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1037)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AFC2_thumb)
		);
}

// patch for 0x31AFC8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AFD4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31AFC8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1036)
		"ADD R3, R6\n"
		"STR R3, [SP,#0x78+"/* var_60 */"-0x60]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1035)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AFD4_thumb)
		);
}

// patch for 0x31AFD8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AFE4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31AFD8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1034)
		"ADD R3, R6\n"
		"STR R3, [SP,#0x78+"/* var_58 */"-0x58]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1033)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AFE4_thumb)
		);
}

// patch for 0x31AFE8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AFF4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31AFE8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1032)
		"ADD R3, R6\n"
		"STR R3, [SP,#0x78+"/* var_50 */"-0x50]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1031)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AFF4_thumb)
		);
}

// patch for 0x31AFF8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B004_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31AFF8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1030)
		"ADD R3, R6\n"
		"STR R3, [SP,#0x78+"/* var_48 */"-0x48]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1029)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B004_thumb)
		);
}

// patch for 0x31B008
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B014_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B008()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1028)
		"ADD R3, R6\n"
		"STR R3, [SP,#0x78+"/* var_40 */"-0x40]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1027)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B014_thumb)
		);
}

// patch for 0x31B018
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B024_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B018()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1026)
		"ADD R3, R6\n"
		"STR R3, [SP,#0x78+"/* var_38 */"-0x38]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1025)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B024_thumb)
		);
}

// patch for 0x31B028
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B034_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B028()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1024)
		"ADD R3, R6\n"
		"STR R3, [SP,#0x78+"/* var_2C */"-0x2C]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_dwNumAddresses)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B034_thumb)
		);
}

// patch for 0x31B038
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B042_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B038()
{
	__asm(
	".thumb\n"
		"MOV R3, R6\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_field_1544_index_1039)
		"STR R3, [SP,#0x78+"/* var_6C */"-0x6C]\n"
		"STRD R10, R8, [SP,#0x78+"/* var_24 */"-0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B042_thumb)
		);
}

// patch for 0x31B048
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B050_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B048()
{
	__asm(
	".thumb\n"
		"MOV R3, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		"ADD R9, R1, R3,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B050_thumb)
		);
}

// patch for 0x31B0A6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B0B2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B0A6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pNodeLinks_index_1)
		"LDR R3, [R1,R3]\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"STR R3, [R1,R0]\n"
		"POP {R0, R2}\n"
		"LDRB R1, [R9,#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B0B2_thumb)
		);
}

// patch for 0x31B0D4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B0DC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B0D4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_pNodeLinks_index_1)
		"LDR R6, [R1,R6]\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"STR R6, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B0DC_thumb)
		);
}

// patch for 0x31B10E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B118_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B10E()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, iTotalNumberOfPathFilesMinusOne)
		"MOV R3, #0\n"
		"IT HI\n"
		"MOVHI R3, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B118_thumb)
		);
}

// patch for 0x31B2A6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B2B0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B2A6()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_field_1544)
		"ADD R1, R3, R1,LSL#2\n"
		"LDR R3, [R1,R6]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B2B0_thumb)
		);
}

// patch for 0x31B2CC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B2DA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B2CC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R1, iTotalNumberOfPathFiles)
		"BNE 1f\n"
		"ADD R4, R5, R0,LSL#2\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R4,R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B2DA_thumb)

		// Branches
		"1:\n"	// loc_31AF84
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31AF84_thumb)
		);
}

// patch for 0x31B2DE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B2E8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B2DE()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R0, [R4,R0]\n"
		"MOVS R6, #0\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"STR R6, [R4,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B2E8_thumb)
		);
}

// patch for 0x31B2EC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B2F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B2EC()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pLinkLengths)
		"LDR R0, [R4,R0]\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"STR R6, [R4,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B2F4_thumb)
		);
}

// patch for 0x31B2F8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B300_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B2F8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathIntersections)
		"LDR R0, [R4,R0]\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pLinkLengths)
		"STR R6, [R4,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B300_thumb)
		);
}

// patch for 0x31B304
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B30C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B304()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_dwNumVehicleNodes)
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_interiorAreaIDarray_index_0)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B30C_thumb)
		);
}

// patch for 0x31B30E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B318_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B30E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_dwNumPedNodes)
		"STR R6, [R4,R0]\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_dwNumCarPathLinks)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B318_thumb)
		);
}

// patch for 0x31B31A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B328_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__RemoveInterior_31B31A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_dwNumAddresses)
		"STR R6, [R4,R0]\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_dwNumNodes)
		"STR R6, [R4,R0]\n"
		"POP {R0, R1}\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathIntersections)
		"STR R6, [R4,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__RemoveInterior_31B328_thumb)
		);
}

// patch for 0x31B33C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B34A_thumb = 0;	// loc_31B34A
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B348_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B33C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_interiorAreaIDarray_index_0)
		"LDR R3, [R0,R3]\n"
		"CMP R3, R1\n"
		"BNE 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B348_thumb)

		// Branches
		"1:\n"	// loc_31B34A
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B34A_thumb)
		);
}

// patch for 0x31B34A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B358_thumb = 0;	// loc_31B358
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B356_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B34A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_interiorAreaIDarray_index_1)
		"LDR R3, [R0,R3]\n"
		"CMP R3, R1\n"
		"BNE 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles_plus_65)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B356_thumb)

		// Branches
		"1:\n"	// loc_31B358
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B358_thumb)
		);
}

// patch for 0x31B358
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B366_thumb = 0;	// loc_31B366
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B364_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B358()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_interiorAreaIDarray_index_2)
		"LDR R3, [R0,R3]\n"
		"CMP R3, R1\n"
		"BNE 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles_plus_66)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B364_thumb)

		// Branches
		"1:\n"	// loc_31B366
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B366_thumb)
		);
}

// patch for 0x31B366
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B374_thumb = 0;	// loc_31B374
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B372_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B366()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_interiorAreaIDarray_index_3)
		"LDR R3, [R0,R3]\n"
		"CMP R3, R1\n"
		"BNE 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles_plus_67)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B372_thumb)

		// Branches
		"1:\n"	// loc_31B374
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B374_thumb)
		);
}

// patch for 0x31B374
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B382_thumb = 0;	// loc_31B382
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B380_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B374()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_interiorAreaIDarray_index_4)
		"LDR R3, [R0,R3]\n"
		"CMP R3, R1\n"
		"BNE 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles_plus_68)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B380_thumb)

		// Branches
		"1:\n"	// loc_31B382
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B382_thumb)
		);
}

// patch for 0x31B382
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B390_thumb = 0;	// loc_31B390
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B38E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B382()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_interiorAreaIDarray_index_5)
		"LDR R3, [R0,R3]\n"
		"CMP R3, R1\n"
		"BNE 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles_plus_69)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B38E_thumb)

		// Branches
		"1:\n"	// loc_31B390
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B390_thumb)
		);
}

// patch for 0x31B390
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B39E_thumb = 0;	// loc_31B39E
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B39C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B390()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_interiorAreaIDarray_index_6)
		"LDR R3, [R0,R3]\n"
		"CMP R3, R1\n"
		"BNE 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles_plus_70)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B39C_thumb)

		// Branches
		"1:\n"	// loc_31B39E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B39E_thumb)
		);
}

// patch for 0x31B39E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B3B4_thumb = 0;	// loc_31B3B4
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B39E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_interiorAreaIDarray_index_7)
		"LDR R0, [R0,R3]\n"
		"CMP R0, R1\n"
		"ITTTT NE\n"
		"MOVNE R0, #0xFFFF\n"
		"MOVNE R1, #0\n"
		"ORRNE R0, R1\n"
		"BXNE LR\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, iTotalNumberOfPathFiles_plus_71)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__ReturnInteriorNodeIndex_31B3B4_thumb)
		);
}

// patch for 0x31B3CA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B430_thumb = 0;	// locret_31B430
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B3D4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B3CA()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R0,R3]\n"
		"MOV R0, #0xFFFF\n"
		"CBZ R3, 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B3D4_thumb)

		// Branches
		"1:\n"	// locret_31B430
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B430_thumb)
		);
}

// patch for 0x31B3DA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B3E4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B3DA()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R3, [R3,R0]\n"
		"POP {R0, R1}\n"
		"CMP R3, #0\n"
		"IT EQ\n"
		"POPEQ {R4,R6,R7,PC}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B3E4_thumb)
		);
}

// patch for 0x31B3EC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B3F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B3EC()
{
	__asm(
	".thumb\n"
		"MOV R1, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"LDR R2, [R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B3F4_thumb)
		);
}

// patch for 0x31B3F8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B400_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B3F8()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(LR, Offset_CPathFind__m_pPathNodes)
		"LDR LR, [R2,LR]\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNodeLinks)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B400_thumb)
		);
}

// patch for 0x31B426
extern "C"
{
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B426()
{
	__asm(
	".thumb\n"
		"ADD R0, R0, R12,LSL#2\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviLinks)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"LDR R0, [R0,R1,LSL#1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindLinkBetweenNodes_31B430_thumb)
		);
}

// patch for 0x31B46A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B476_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B46A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, Offset_CPathFind__m_dwNumVehicleNodes)
		"MOV R9, #0xF00000\n"
		"MOV R12, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B476_thumb)
		);
}

// patch for 0x31B480
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B54E_thumb = 0;	// loc_31B54E
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B488_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B480()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R4,R5]\n"
		"CMP R5, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B488_thumb)

		// Branches
		"1:\n"	// loc_31B54E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B54E_thumb)
		);
}

// patch for 0x31B492
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B4A2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B492()
{
	__asm(
	".thumb\n"
		"LDR R2, [R5,#0x10]\n"
		"VMOV S11, R2\n"
		"VCVT.F32.S32 S11, S11\n"
		"MOV R2, 0x18\n"
		"LDR R2, [R5,R2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B4A2_thumb)
		);
}

// patch for 0x31B4C2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B4CE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B4C2()
{
	__asm(
	".thumb\n"
		"LDR R2, [R5,#0x14]\n"
		"VMOV S13, R2\n"
		"VCVT.F32.S32 S13, S13\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B4CE_thumb)
		);
}

// patch for 0x31B550
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B47C_thumb = 0;	// loc_31B47C
	uintptr_t Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B55A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B550()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, iTotalNumberOfPathFiles)
		"BNE 1f\n"
		"LDR R1, =("/* dword_7AF318 */"0x7AF318 - 0x31B560)\n"
		"ADD R2, LR, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B55A_thumb)

		// Branches
		"1:\n"	// loc_31B47C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__FindParkingNodeInArea_31B47C_thumb)
		);
}

// patch for 0x3251DA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3251C0_thumb = 0;	// loc_3251C0
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3251EE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3251DA()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CMP R1, #0\n"
		"BEQ 1f\n"
		"LSRS R3, R0, #0x10\n"
		"MOV R2, 0x18\n"
		"LDR R2, [R6,R2]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3251EE_thumb)

		// Branches
		"1:\n"	// loc_3251C0
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3251C0_thumb)
		);
}

// patch for 0x3251FA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325206_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3251FA()
{
	__asm(
	".thumb\n"
		"ADD R10, R10, #8\n"
		"LDR R1, [R10,#0x14]\n"
		"VMOV S2, R1\n"
		"VCVT.F32.S32 S2, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325206_thumb)
		);
}

// patch for 0x32522E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32523A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32522E()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x16\n"
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x16\n"
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"VMOV S0, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32523A_thumb)
		);
}

// patch for 0x3252C2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3252CC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3252C2()
{
	__asm(
	".thumb\n"
		"MOV R1, 0x14\n"
		"LDR R1, [R6,R1]\n"
		"ADD R3, SP, #0x1D0+"/* var_158 */"-0x158\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x16\n"
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3252CC_thumb)
		);
}

// patch for 0x3252DE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3252EA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3252DE()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x14\n"
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"VMOV S4, R0\n"
		"VMUL.F32 S0, S0, S22\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3252EA_thumb)
		);
}

// patch for 0x32530E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32531A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32530E()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x16\n"
		"LDR R0, [R8,R0]\n"
		"MOV R1, 0x14\n"
		"LDR R1, [R10,R1]\n"
		"VMOV S0, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32531A_thumb)
		);
}

// patch for 0x325326
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325330_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325326()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x18\n"
		"LDR R0, [R2,R0]\n"
		"VCVT.F32.S32 S2, S2\n"
		"ADD R2, SP, #0x1D0+"/* var_154 */"-0x154\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325330_thumb)
		);
}

// patch for 0x32537E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32538A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32537E()
{
	__asm(
	".thumb\n"
		"MOV R1, 0x16\n"
		"LDR R1, [R8,R1]\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x16\n"
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"VMOV S2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32538A_thumb)
		);
}

// patch for 0x325392
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32539E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325392()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x14\n"
		"LDR R0, [R6,R0]\n"
		"VCVT.F32.S32 S2, S2\n"
		"MOV R1, 0x14\n"
		"LDR R1, [R10,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32539E_thumb)
		);
}

// patch for 0x3253B0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3253B8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3253B0()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x18\n"
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"VCVT.F32.S32 S6, S6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3253B8_thumb)
		);
}

// patch for 0x3253C4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3253CC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3253C4()
{
	__asm(
	".thumb\n"
		"MOV R1, 0x18\n"
		"LDR R1, [R4,R1]\n"
		"VMUL.F32 S4, S4, S22\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3253CC_thumb)
		);
}

// patch for 0x325400
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32540C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325400()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x14\n"
		"LDR R0, [R10,R0]\n"
		"VMUL.F32 S0, S23, S19\n"
		"MOV R1, 0x16\n"
		"LDR R1, [R8,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32540C_thumb)
		);
}

// patch for 0x32541C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325424_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32541C()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x18\n"
		"LDR R0, [R4,R0]\n"
		"MOV R1, 0x14\n"
		"LDR R1, [R6,R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325424_thumb)
		);
}

// patch for 0x325452
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32545E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325452()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x18\n"
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"VMUL.F32 S4, S4, S22\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x16\n"
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32545E_thumb)
		);
}

// patch for 0x3254EA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3254F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3254EA()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x14\n"
		"LDR R0, [R6,R0]\n"
		"MOVS R6, #0\n"
		"VLDR S0, [SP,#0x1D0+"/* var_64 */"-0x64]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3254F4_thumb)
		);
}

// patch for 0x325502
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32550E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325502()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x16\n"
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"VMOV S4, R0\n"
		"VMUL.F32 S2, S2, S22\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32550E_thumb)
		);
}

// patch for 0x325514
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32551C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325514()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		"MOV R1, 0x18\n"
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"VMOV S6, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32551C_thumb)
		);
}

// patch for 0x325588
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325590_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325588()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, Offset_CPathFind__m_pPathNodes)
		"LDR R8, [R0,R8]\n"
		"CMP R8, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325590_thumb)
		);
}

// patch for 0x3255A2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3255B0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3255A2()
{
	__asm(
	".thumb\n"
		"MOV R0, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R6, R8, R0,LSL#2\n"
		"ADD R6, R6, #8\n"
		"LDR R0, [R6,#0x14]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3255B0_thumb)
		);
}

// patch for 0x3255EE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3255FA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3255EE()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x16\n"
		"LDR R0, [R11,R0]\n"
		"VMOV S0, R0\n"
		"VCVT.F32.S32 S0, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3255FA_thumb)
		);
}

// patch for 0x325674
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32567C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325674()
{
	__asm(
	".thumb\n"
		"MOV R0, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R10, R6, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32567C_thumb)
		);
}

// patch for 0x325698
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3256A0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325698()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x14\n"
		"LDR R0, [R6,R0]\n"
		"VMUL.F32 S2, S2, S19\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3256A0_thumb)
		);
}

// patch for 0x3256AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3256B4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3256AC()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x18\n"
		"LDR R0, [R10,R0]\n"
		"VADD.F32 S23, S25, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3256B4_thumb)
		);
}

// patch for 0x3256C2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3256CE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3256C2()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x16\n"
		"LDR R0, [R4,R0]\n"
		"VMOV S4, R0\n"
		"VMUL.F32 S2, S2, S22\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3256CE_thumb)
		);
}

// patch for 0x325732
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325742_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325732()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x14\n"
		"LDR R0, [R6,R0]\n"
		"VMOV S0, R0\n"
		"VCVT.F32.S32 S0, S0\n"
		"MOV R0, 0x16\n"
		"LDR R0, [R4,R0]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325742_thumb)
		);
}

// patch for 0x32574A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325756_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32574A()
{
	__asm(
	".thumb\n"
		"MOV R0, 0x18\n"
		"LDR R0, [R10,R0]\n"
		"VLDR S4, [SP,#0x1D0+"/* var_104 */"-0x104]\n"
		"VLDR S6, [SP,#0x1D0+"/* var_100 */"-0x100]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325756_thumb)
		);
}

// patch for 0x3257EA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3257F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3257EA()
{
	__asm(
	".thumb\n"
		"MOV R4, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		"ADD R5, R1, R4,LSL#2\n"
		"LDRB R0, [R5,#0x18]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3257F4_thumb)
		);
}

// patch for 0x325946
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_32594C = 0;
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325952_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325946()
{
	__asm(
	".thumb\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_32594C)
		"MOV R6, R5\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		"MOVT R4, #3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325952_thumb)
		);
}

// patch for 0x325958
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325960_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325958()
{
	__asm(
	".thumb\n"
		"MOV R5, R3\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [R5,R0]\n"
		"ADD R0, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325960_thumb)
		);
}

// patch for 0x325964
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325972_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325964()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviLinks)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"LDRSH R4, [R3,#0x10]\n"
		"LDR R3, [R0,R4,LSL#2]\n"
		"LSRS R6, R3, #16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325972_thumb)
		);
}

// patch for 0x325980
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325986 = 0;
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_32598A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325980()
{
	__asm(
	".thumb\n"
		"LDR R4, [R0,#4]\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R5, Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325986)
		"LDR R0, [R5]\n"
		"MOV R12, R4,LSR#16\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_32598A_thumb)
		);
}

// patch for 0x32598E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325A74_thumb = 0;	// loc_325A74
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325998_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_32598E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R0,R5]\n"
		"MOVS R0, #0\n"
		"CMP R5, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325998_thumb)

		// Branches
		"1:\n"	// loc_325A74
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325A74_thumb)
		);
}

// patch for 0x32599A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_3259A6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_32599A()
{
	__asm(
	".thumb\n"
		"BFC R4, #16, #16\n"
		"BFC R3, #16, #16\n"
		"VMOV.F32 S0, #5.0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_3259A6_thumb)
		);
}

// patch for 0x3259A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_3259B0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_3259A8()
{
	__asm(
	".thumb\n"
		"MOV R8, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R8, SizeOfCCarPathLinkDividedBy2)
		"MOV R11, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R11, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_3259B0_thumb)
		);
}

// patch for 0x3259B2
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_3259BE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_3259B2()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pNaviNodes)
		"LDR LR, [R5,R12,LSL#2]\n"
		"LDR R10, [R5,R6,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_3259BE_thumb)
		);
}

// patch for 0x325A12
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325A1E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325A12()
{
	__asm(
	".thumb\n"
		"MOV R1, R11,LSL#1\n"
		"ADD R1, 0x10\n"
		"LDR R1, [R10,R1]\n"
		"MOV R3, R8,LSL#1\n"
		"ADD R3, 0x10\n"
		"LDR R3, [LR,R3]\n"
		"VMOV S2, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325A1E_thumb)
		);
}

// patch for 0x325A2A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325A36_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325A2A()
{
	__asm(
	".thumb\n"
		"LDR R1, [R4,#0x14]\n"
		"LDR R3, [R12,#0x14]\n"
		"VMOV S6, R1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GetRoadBlockNodeInfo_325A36_thumb)
		);
}

// patch for 0x34619E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands700To799_3461A8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands700To799_34619E()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands700To799_3461A8_thumb)
		);
}

// patch for 0x3461AC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CRunningScript__ProcessCommands700To799_3461B8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRunningScript__ProcessCommands700To799_3461AC()
{
	__asm(
	".thumb\n"
		"LDR R1, [R0,#0x1C]\n"
		"LDR R2, [R0,#0x20]\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRunningScript__ProcessCommands700To799_3461B8_thumb)
		);
}

// patch for 0x362434
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36243C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362434()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"MOV R8, #0xFFFF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36243C_thumb)
		);
}

// patch for 0x36244A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362454_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36244A()
{
	__asm(
	".thumb\n"
		"LSRS R1, R0, #16\n"
		"ADD R2, R2, R1,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362454_thumb)
		);
}

// patch for 0x36245E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362466 = 0;
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362468_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36245E()
{
	__asm(
	".thumb\n"
		"BFC R0, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362466)
		"MOV R10, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R10, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362468_thumb)
		);
}

// patch for 0x36246E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362478_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36246E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R9, Offset_CPathFind__m_pNaviNodes)
		"LDR R9, [R1,R9]\n"
		"ADD R11, R9, R10,LSL#1\n"
		"MOV R6, R11\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362478_thumb)
		);
}

// patch for 0x3624BA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3624C6_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3624BA()
{
	__asm(
	".thumb\n"
		"MOV R0, R10,LSL#1\n"
		"ADD R0, 0x10\n"
		"LDR R0, [R9,R0]\n"
		"VMOV.F32 S0, #0.125\n"
		"VLDR S6, 101f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3624C6_thumb)

		// Data
		ASM_PUT_CONSTANT_FLOAT(101, 0.01)
		);
}

// patch for 0x3624CE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3624DA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3624CE()
{
	__asm(
	".thumb\n"
		"LDR R0, [R11,#0x14]\n"
		"VMOV S4, R0\n"
		"VCVT.F32.S32 S4, S4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3624DA_thumb)
		);
}

// patch for 0x3625EA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362790_thumb = 0;	// loc_362790
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3625F4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3625EA()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"CMP R0, R8\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3625F4_thumb)

		// Branches
		"1:\n"	// loc_362790
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362790_thumb)
		);
}

// patch for 0x3625FA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362604_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3625FA()
{
	__asm(
	".thumb\n"
		"LSRS R1, R0, #16\n"
		"ADD R2, R2, R1,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362604_thumb)
		);
}

// patch for 0x36260C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362614 = 0;
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362616_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36260C()
{
	__asm(
	".thumb\n"
		"BFC R0, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362614)
		"MOV R10, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R10, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362616_thumb)
		);
}

// patch for 0x36261C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362624_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36261C()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R9, Offset_CPathFind__m_pNaviNodes)
		"LDR R9, [R1,R9]\n"
		"ADD R11, R9, R10,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362624_thumb)
		);
}

// patch for 0x362668
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362670_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362668()
{
	__asm(
	".thumb\n"
		"MOV R0, R10,LSL#1\n"
		"ADD R0, 0x10\n"
		"LDR R0, [R9,R0]\n"
		"VMOV.F32 S0, #0.125\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362670_thumb)
		);
}

// patch for 0x36267C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362684_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36267C()
{
	__asm(
	".thumb\n"
		"LDR R0, [R11,#0x14]\n"
		"VMOV S4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362684_thumb)
		);
}

// patch for 0x362790
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36292E_thumb = 0;	// loc_36292E
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36279A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362790()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AC\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"CMP R0, R8\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36279A_thumb)

		// Branches
		"1:\n"	// loc_36292E
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36292E_thumb)
		);
}

// patch for 0x3627A0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3627AA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3627A0()
{
	__asm(
	".thumb\n"
		"LSRS R1, R0, #16\n"
		"ADD R2, R2, R1,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3627AA_thumb)
		);
}

// patch for 0x3627C0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3627C8 = 0;
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3627CA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3627C0()
{
	__asm(
	".thumb\n"
		"BFC R0, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3627C8)
		"MOV R9, R0\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R9, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3627CA_thumb)
		);
}

// patch for 0x3627D0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3627D8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3627D0()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R8, Offset_CPathFind__m_pNaviNodes)
		"LDR R8, [R1,R8]\n"
		"ADD R10, R8, R9,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_3627D8_thumb)
		);
}

// patch for 0x362824
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36282C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362824()
{
	__asm(
	".thumb\n"
		"MOV R0, R9,LSL#1\n"
		"ADD R0, 0x10\n"
		"LDR R0, [R8,R0]\n"
		"VMOV.F32 S0, #0.125\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_36282C_thumb)
		);
}

// patch for 0x362838
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362840_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362838()
{
	__asm(
	".thumb\n"
		"LDR R0, [R10,#0x14]\n"
		"VMOV S4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForLight_362840_thumb)
		);
}

// patch for 0x3637B8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637C0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637B8()
{
	__asm(
	".thumb\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3AA\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R0, [R0]\n"
		"STR R0, [SP,#0x0]\n"
		"POP {R0-R3,R12,LR}\n"
		"MOV R3, #0xFFFF\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637C0_thumb)
		);
}

// patch for 0x3637C6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637CC = 0;
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637D4_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637C6()
{
	__asm(
	".thumb\n"
		"LSRS R2, R0, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637CC)
		"LDR R1, [R1]\n"
		"ADD R1, R1, R2,LSL#2\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637D4_thumb)
		);
}

// patch for 0x3637D6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_363836_thumb = 0;	// loc_363836
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637E0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637D6()
{
	__asm(
	".thumb\n"
		"BEQ 500f\n"
		"PUSH {R0-R3,R12,LR}\n"
		"MOV R0, R4\n"
		"ADD R0, R0, #0x3A8\n"
		"BLX GetExtDataPtrForCLinkAddress_extension\n"
		"LDR R1, [R0]\n"
		"STR R1, [SP,#0x4]\n"
		"POP {R0-R3,R12,LR}\n"
		"CMP R1, R3\n"
		"500:\n"	// past the IT block
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637E0_thumb)

		// Branches
		"1:\n"	// loc_363836
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_363836_thumb)
		);
}

// patch for 0x3637E6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637F0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637E6()
{
	__asm(
	".thumb\n"
		"LSRS R3, R1, #16\n"
		"ADD R4, R4, R3,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [R4,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637F0_thumb)
		);
}

// patch for 0x3637F4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637FC = 0;
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637FE_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637F4()
{
	__asm(
	".thumb\n"
		"BFC R0, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R4, Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637FC)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_3637FE_thumb)
		);
}

// patch for 0x363804
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_36380C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_363804()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pNaviNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"ADD R0, R2, R0,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_36380C_thumb)
		);
}

// patch for 0x363814
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_36381C = 0;
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_36381E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_363814()
{
	__asm(
	".thumb\n"
		"BFC R1, #16, #16\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_36381C)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCCarPathLinkDividedBy2)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_36381E_thumb)
		);
}

// patch for 0x363824
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_36382C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_363824()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNaviNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"ADD R0, R0, R1,LSL#1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTrafficLights__ShouldCarStopForBridge_36382C_thumb)
		);
}

// patch for 0x40928E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlayerInfo__Process_40929A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlayerInfo__Process_40928E()
{
	__asm(
	".thumb\n"
		"MOV R2, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R2, Offset_CPathFind__m_pPathNodes)
		"VLDR S4, [R2]\n"
		"VCMP.F32 S4, S0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlayerInfo__Process_40929A_thumb)
		);
}

// patch for 0x40930C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPlayerInfo__Process_409314_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPlayerInfo__Process_40930C()
{
	__asm(
	".thumb\n"
		"MOV R1, R0\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"VLDR S2, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPlayerInfo__Process_409314_thumb)
		);
}

// patch for 0x428114
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__RemoveFallenPeds_42811E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__RemoveFallenPeds_428114()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__RemoveFallenPeds_42811E_thumb)
		);
}

// patch for 0x428122
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__RemoveFallenPeds_42812E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__RemoveFallenPeds_428122()
{
	__asm(
	".thumb\n"
		"LDR R1, [R0,#0x1C]\n"
		"LDR R2, [R0,#0x20]\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__RemoveFallenPeds_42812E_thumb)
		);
}

// patch for 0x4282E8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__RemoveFallenCars_4282F2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__RemoveFallenCars_4282E8()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__RemoveFallenCars_4282F2_thumb)
		);
}

// patch for 0x4282F6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CWorld__RemoveFallenCars_428302_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CWorld__RemoveFallenCars_4282F6()
{
	__asm(
	".thumb\n"
		"LDR R1, [R0,#0x1C]\n"
		"LDR R2, [R0,#0x20]\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CWorld__RemoveFallenCars_428302_thumb)
		);
}

// patch for 0x449152
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449162_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449152()
{
	__asm(
	".thumb\n"
		"MOV R6, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		"ADD R3, R3, R1,LSL#2\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [R3,R4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449162_thumb)
		);
}

// patch for 0x449166
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449172_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449166()
{
	__asm(
	".thumb\n"
		"LDR R4, [R6,#0x1C]\n"
		"LDR R1, [R6,#0x20]\n"
		"LDR R6, [R6,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449172_thumb)
		);
}

// patch for 0x4491A8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_4491B0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_4491A8()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"MOV R6, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_4491B0_thumb)
		);
}

// patch for 0x4491BA
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_4491CA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_4491BA()
{
	__asm(
	".thumb\n"
		"LDR R6, [R3,#0x1C]\n"
		"VMOV S0, R6\n"
		"VCVT.F32.S32 S0, S0\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x20\n"
		"ADD R0, R3\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_4491CA_thumb)
		);
}

// patch for 0x4491D2



// patch for 0x44932E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_44933A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_44932E()
{
	__asm(
	".thumb\n"
		"MOV R6, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		"MOV R11, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_44933A_thumb)
		);
}

// patch for 0x44933E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449352_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_44933E()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R4, Offset_CPathFind__m_pPathNodes)
		"LDR R4, [R3,R4]\n"
		"ADD R6, R4, R6,LSL#2\n"
		"LDR R4, [R6,#0x1C]\n"
		"LDR R1, [R6,#0x20]\n"
		"LDR R6, [R6,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449352_thumb)
		);
}

// patch for 0x449388
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449390_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449388()
{
	__asm(
	".thumb\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"MOV R6, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R6, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449390_thumb)
		);
}

// patch for 0x44939A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_4493AA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_44939A()
{
	__asm(
	".thumb\n"
		"LDR R6, [R3,#0x1C]\n"
		"VMOV S0, R6\n"
		"VCVT.F32.S32 S0, S0\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x20\n"
		"ADD R0, R3\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_4493AA_thumb)
		);
}

// patch for 0x4493B2



// patch for 0x449518
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449520_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449518()
{
	__asm(
	".thumb\n"
		"MOV R4, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449520_thumb)
		);
}

// patch for 0x449526
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_44953A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449526()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [LR,R1]\n"
		"ADD R1, R1, R4,LSL#2\n"
		"LDR R4, [R1,#0x1C]\n"
		"LDR R3, [R1,#0x20]\n"
		"LDR R1, [R1,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_44953A_thumb)
		);
}

// patch for 0x449576
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449582_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449576()
{
	__asm(
	".thumb\n"
		"MOV R3, LR\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"MOV R4, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		"ADD R1, R9, #0x568\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449582_thumb)
		);
}

// patch for 0x449588
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449590_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449588()
{
	__asm(
	".thumb\n"
		"LDR R4, [R3,#0x1C]\n"
		"VMOV S0, R4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449590_thumb)
		);
}

// patch for 0x449594
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_44959C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449594()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x20\n"
		"ADD R0, R3\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R1}\n"
		"STR R3, [SP,#0x230+"/* var_178 */"-0x178]\n"
		"ADD R3, SP, #0x230+"/* var_178 */"-0x178\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_44959C_thumb)
		);
}

// patch for 0x4495A0



// patch for 0x449704
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_44970C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449704()
{
	__asm(
	".thumb\n"
		"MOV R4, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_44970C_thumb)
		);
}

// patch for 0x449710
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449724_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449710()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [LR,R1]\n"
		"ADD R1, R1, R4,LSL#2\n"
		"LDR R4, [R1,#0x1C]\n"
		"LDR R3, [R1,#0x20]\n"
		"LDR R1, [R1,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449724_thumb)
		);
}

// patch for 0x449766
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449772_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449766()
{
	__asm(
	".thumb\n"
		"MOV R3, LR\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R3, Offset_CPathFind__m_pPathNodes)
		"MOV R4, R12\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		"ADD R1, R9, #0x588\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449772_thumb)
		);
}

// patch for 0x449778
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449780_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449778()
{
	__asm(
	".thumb\n"
		"LDR R4, [R3,#0x1C]\n"
		"VMOV S0, R4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449780_thumb)
		);
}

// patch for 0x449784
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_44978C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_InteriorGroup_c__SetupPaths_449784()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		"MOV R0, 0x20\n"
		"ADD R0, R3\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R1}\n"
		"STR R3, [SP,#0x230+"/* var_17C */"-0x17C]\n"
		"ADD R3, SP, #0x230+"/* var_17C */"-0x17C\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_InteriorGroup_c__SetupPaths_44978C_thumb)
		);
}

// patch for 0x449790



// patch for 0x48CEE4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Save_48CEEC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Save_48CEE4()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_dwNumForbiddenAreas)
		"MOV R5, R0\n"
		"LDR R0, [R4,R6]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Save_48CEEC_thumb)
		);
}

// patch for 0x48CF02
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Save_48CF0C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Save_48CF02()
{
	__asm(
	".thumb\n"
		"ADD R8, R4, R6\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_aForbiddenAreas)
		"ADDS R6, R4, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Save_48CF0C_thumb)
		);
}

// patch for 0x48CF5A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Load_48CF64_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Load_48CF5A()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R6, Offset_CPathFind__m_dwNumForbiddenAreas)
		"ADDS R4, R5, R6\n"
		"MOVS R1, #4\n"
		"MOV R0, R4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Load_48CF64_thumb)
		);
}

// patch for 0x48CF6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPathFind__Load_48CF88_thumb = 0;	// loc_48CF88
	uintptr_t Address_GTA_SA_2_00_CPathFind__Load_48CF74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPathFind__Load_48CF6C()
{
	__asm(
	".thumb\n"
		"BLT 1f\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_aForbiddenAreas)
		"ADD R5, R0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Load_48CF74_thumb)

		// Branches
		"1:\n"	// loc_48CF88
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPathFind__Load_48CF88_thumb)
		);
}

// patch for 0x4A04FC
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A0506 = 0;
	uintptr_t Address_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A0508_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A04FC()
{
	__asm(
	".thumb\n"
		"VMOV.F32 S0, #0.125\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R2, Address_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A0506)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A0508_thumb)
		);
}

// patch for 0x4A050E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A0522_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A050E()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"ADD R2, R2, R3,LSL#2\n"
		"LDR R3, [R2,#0x1C]\n"
		"LDR R6, [R2,#0x20]\n"
		"LDR R2, [R2,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A0522_thumb)
		);
}

// patch for 0x4A0574
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A057E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A0574()
{
	__asm(
	".thumb\n"
		"MOV R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A057E_thumb)
		);
}

// patch for 0x4A0582
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A058E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A0582()
{
	__asm(
	".thumb\n"
		"LDR R3, [R0,#0x1C]\n"
		"LDR R0, [R0,#0x20]\n"
		"VMOV S4, R3\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A058E_thumb)
		);
}

// patch for 0x4A05EE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A05FA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A05EE()
{
	__asm(
	".thumb\n"
		"MOV R0, R1\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R0, R2, R0,LSL#2\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPed__PositionPedOutOfCollision_4A05FA_thumb)
		);
}

// patch for 0x4CCF62
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPopulation__AddToPopulation_4CCF6E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPopulation__AddToPopulation_4CCF62()
{
	__asm(
	".thumb\n"
		"UXTH R3, R1\n"
		ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPopulation__AddToPopulation_4CCF6E_thumb)
		);
}

// patch for 0x4CCF7C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPopulation__AddToPopulation_4CCF84_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPopulation__AddToPopulation_4CCF7C()
{
	__asm(
	".thumb\n"
		"LDRB R3, [R3,#0x1A]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPopulation__AddToPopulation_4CCF84_thumb)
		);
}

// patch for 0x4CCFA0
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPopulation__AddToPopulation_4CCFAA_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPopulation__AddToPopulation_4CCFA0()
{
	__asm(
	".thumb\n"
		"MOV R1, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"ADD R0, R0, R1,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPopulation__AddToPopulation_4CCFAA_thumb)
		);
}

// patch for 0x4D0300
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPopulation__CreateWaitingCoppers_4D030A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPopulation__CreateWaitingCoppers_4D0300()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPopulation__CreateWaitingCoppers_4D030A_thumb)
		);
}

// patch for 0x4D030E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CPopulation__CreateWaitingCoppers_4D031A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CPopulation__CreateWaitingCoppers_4D030E()
{
	__asm(
	".thumb\n"
		"LDR R1, [R0,#0x1C]\n"
		"LDR R2, [R0,#0x20]\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CPopulation__CreateWaitingCoppers_4D031A_thumb)
		);
}

// patch for 0x515AFE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexGangLeader__ControlSubTask_515B0A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexGangLeader__ControlSubTask_515AFE()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R0, R8, R0,LSL#2\n"
		"LDR R0, [R0,#0x5A4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexGangLeader__ControlSubTask_515B0A_thumb)
		);
}

// patch for 0x51F7EE
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F8FC_thumb = 0;	// loc_51F8FC
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F7F8_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F7EE()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F7F8_thumb)

		// Branches
		"1:\n"	// loc_51F8FC
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F8FC_thumb)
		);
}

// patch for 0x51F802
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F80C_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F802()
{
	__asm(
	".thumb\n"
		"VLDR D2, [R5]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F80C_thumb)
		);
}

// patch for 0x51F81A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F826_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F81A()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R1\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R2}\n"
		"VMUL.F32 S2, S2, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F826_thumb)
		);
}

// patch for 0x51F87E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F888_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F87E()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CBZ R2, 1f\n"
		"VLDR S0, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F888_thumb)

		// Branches
		"1:\n"	// loc_51F8FC
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F8FC_thumb)
		);
}

// patch for 0x51F88E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F898_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F88E()
{
	__asm(
	".thumb\n"
		"VLDR D2, [R5]\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F898_thumb)
		);
}

// patch for 0x51F8A6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F8B2_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F8A6()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		"MOV R0, 0x14\n"
		"ADD R0, R1\n"
		"VLD1.64 {Q8}, [R0]\n"
		"POP {R0, R2}\n"
		"VMUL.F32 S2, S2, S2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F8B2_thumb)
		);
}

// patch for 0x51F936
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51FB92_thumb = 0;	// loc_51FB92
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F940_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F936()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CMP R0, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F940_thumb)

		// Branches
		"1:\n"	// loc_51FB92
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51FB92_thumb)
		);
}

// patch for 0x51F968
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F972_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F968()
{
	__asm(
	".thumb\n"
		"MOV R1, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R1, SizeOfCPathNodeDividedBy4)
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F972_thumb)
		);
}

// patch for 0x51F976
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F982_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F976()
{
	__asm(
	".thumb\n"
		"LDR R1, [R0,#0x1C]\n"
		"LDR R2, [R0,#0x20]\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51F982_thumb)
		);
}

// patch for 0x51FA3A
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51FA88_thumb = 0;	// loc_51FA88
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51FA48_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51FA3A()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"CBZ R1, 1f\n"
		"LSRS R2, R0, #0x10\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51FA48_thumb)

		// Branches
		"1:\n"	// loc_51FA88
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51FA88_thumb)
		);
}

// patch for 0x51FA4C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51FA58_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51FA4C()
{
	__asm(
	".thumb\n"
		"LDR R1, [R0,#0x1C]\n"
		"LDR R2, [R0,#0x20]\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputePathNodes_51FA58_thumb)
		);
}

// patch for 0x51FC58
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputeRoute_51FCBA_thumb = 0;	// loc_51FCBA
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputeRoute_51FC60_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputeRoute_51FC58()
{
	__asm(
	".thumb\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R5, Offset_CPathFind__m_pPathNodes)
		"LDR R5, [R1,R5]\n"
		"CBZ R5, 1f\n"
		"LDR R1, [R0,#0x30]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputeRoute_51FC60_thumb)

		// Branches
		"1:\n"	// loc_51FCBA
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputeRoute_51FCBA_thumb)
		);
}

// patch for 0x51FC6C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputeRoute_51FC74_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputeRoute_51FC6C()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R4, SizeOfCPathNodeDividedBy4)
		"ADD R3, R1, R3,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputeRoute_51FC74_thumb)
		);
}

// patch for 0x51FC78
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputeRoute_51FC84_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputeRoute_51FC78()
{
	__asm(
	".thumb\n"
		"LDR R5, [R4,#0x1C]\n"
		"LDR R6, [R4,#0x20]\n"
		"LDR R4, [R4,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexFollowNodeRoute__ComputeRoute_51FC84_thumb)
		);
}

// patch for 0x52184C
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexWander__UpdateDir_521880_thumb = 0;	// loc_521880
	uintptr_t Address_GTA_SA_2_00_CTaskComplexWander__UpdateDir_52185A_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexWander__UpdateDir_52184C()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CBZ R2, 1f\n"
		"LSRS R3, R0, #0x10\n"
		"MOV R0, R3\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexWander__UpdateDir_52185A_thumb)

		// Branches
		"1:\n"	// loc_521880
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexWander__UpdateDir_521880_thumb)
		);
}

// patch for 0x521A46
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521AD2_thumb = 0;	// loc_521AD2
	uintptr_t Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521A50_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521A46()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"BEQ 1f\n"
		"LDR R2, =("/* ThePaths_ptr */"0x677378 - 0x521A5A)\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521A50_thumb)

		// Branches
		"1:\n"	// loc_521AD2
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521AD2_thumb)
		);
}

// patch for 0x521A5E
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521A76_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521A5E()
{
	__asm(
	".thumb\n"
		"MOV R3, R4\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"ADD R2, R2, R3,LSL#2\n"
		"LDR R3, [R2,#0x1C]\n"
		"LDR R4, [R2,#0x20]\n"
		"LDR R2, [R2,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521A76_thumb)
		);
}

// patch for 0x521AE4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521B70_thumb = 0;	// loc_521B70
	uintptr_t Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521AEC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521AE4()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		"CMP R2, #0\n"
		"BEQ 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521AEC_thumb)

		// Branches
		"1:\n"	// loc_521B70
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521B70_thumb)
		);
}

// patch for 0x521AF8
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521B04_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521AF8()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"ADD R2, R2, R3,LSL#2\n"
		"PUSH {R0, R1}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R2, [R2,R0]\n"
		"POP {R0, R1}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521B04_thumb)
		);
}

// patch for 0x521B08
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521B14_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521B08()
{
	__asm(
	".thumb\n"
		"LDR R2, [R0,#0x1C]\n"
		"LDR R3, [R0,#0x20]\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskComplexWanderGang__GetDistanceSqToNode_521B14_thumb)
		);
}

// patch for 0x529686
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskInteriorGoToInfo__CreateFirstSubTask_529690_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskInteriorGoToInfo__CreateFirstSubTask_529686()
{
	__asm(
	".thumb\n"
		"MOV R0, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R0, SizeOfCPathNodeDividedBy4)
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskInteriorGoToInfo__CreateFirstSubTask_529690_thumb)
		);
}

// patch for 0x529694
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CTaskInteriorGoToInfo__CreateFirstSubTask_5296A0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CTaskInteriorGoToInfo__CreateFirstSubTask_529694()
{
	__asm(
	".thumb\n"
		"LDR R1, [R0,#0x1C]\n"
		"LDR R2, [R0,#0x20]\n"
		"LDR R0, [R0,#0x24]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CTaskInteriorGoToInfo__CreateFirstSubTask_5296A0_thumb)
		);
}

// patch for 0x56D9E6
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56D9EC = 0;
	uintptr_t Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56D9F0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56D9E6()
{
	__asm(
	".thumb\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56D9EC)
		"MOV R3, R2\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R3, SizeOfCPathNodeDividedBy4)
		"LDR R1, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56D9F0_thumb)
		);
}

// patch for 0x56D9F4
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56D9FC_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56D9F4()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R0, Offset_CPathFind__m_pPathNodes)
		"LDR R1, [R1,R0]\n"
		"POP {R0, R2}\n"
		"ADD R3, R1, R3,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56D9FC_thumb)
		);
}

// patch for 0x56DA04
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56DA0C = 0;
	uintptr_t Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56DA0E_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56DA04()
{
	__asm(
	".thumb\n"
		ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(R2, SizeOfCPathNodeDividedBy4)
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R3, Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56DA0C)
		"ADD R1, R1, R2,LSL#2\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56DA0E_thumb)
		);
}

// patch for 0x56DA18
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56DA20_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56DA18()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pNodeLinks)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"LDR R11, [R0,R1,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56DA20_thumb)
		);
}

// patch for 0x56DA28
extern "C"
{
	uintptr_t Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56DA9C_thumb = 0;	// loc_56DA9C
	uintptr_t Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56DA30_thumb = 0;
}

static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56DA28()
{
	__asm(
	".thumb\n"
		"PUSH {R1, R2}\n"
		ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(R1, Offset_CPathFind__m_pPathNodes)
		"LDR R0, [R0,R1]\n"
		"POP {R1, R2}\n"
		"CBZ R0, 1f\n"
		"MOV R0, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56DA30_thumb)

		// Branches
		"1:\n"	// loc_56DA9C
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCarGenerator__DoInternalProcessing_56DA9C_thumb)
		);
}


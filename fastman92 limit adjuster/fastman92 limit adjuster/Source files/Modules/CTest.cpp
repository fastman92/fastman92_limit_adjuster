/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CTest.h"

#include "../Core/CCodeMover.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"
#include "../Core/ProjectConstants.h"

#include "../GameStructures/Rockstar Games/CEntity.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>
#include <DynamicTypes/DynamicStructure.h>
#include <CVector2D.h>

#include <Assertions.h>

#include <stdint.h>
#include <stdio.h>

using namespace Game;

#ifdef IS_PLATFORM_WIN_X86
static void splashFix()
{
	int32_t* CLoadingScreen__m_currDisplayedSplash = (int32_t*)0x8D093C;

	if (*CLoadingScreen__m_currDisplayedSplash < 6)
		++*CLoadingScreen__m_currDisplayedSplash;
	else
		*CLoadingScreen__m_currDisplayedSplash = 1;
}

DLL_EXPORT NAKED void patch_renderSomethingLoading_590ADE()
{
	__asm
	{
		call splashFix;

		push 0x590AE4;
		retn;
	}
}
#endif

static NAKED void test()
{

}

#if 0
struct CDynamicThirdLevel : public CDynamicStructure
{
	static CDynamicStructMember<CDynamicThirdLevel, short> a;
	static CDynamicStructMember<CDynamicThirdLevel, short> b;
	static CDynamicStructMember<CDynamicThirdLevel, tDynamicStructEnd> endOfStructure;

	DYNAMIC_STRUCT_GET_ANOTHER(CDynamicThirdLevel);	
};

CDynamicStructMember<CDynamicThirdLevel, short> CDynamicThirdLevel::a;
CDynamicStructMember<CDynamicThirdLevel, short> CDynamicThirdLevel::b;
CDynamicStructMember<CDynamicThirdLevel, tDynamicStructEnd> CDynamicThirdLevel::endOfStructure;

struct CDynamicVector : public CDynamicStructure
{
	static CDynamicStructMember<CDynamicVector, float> x;
	static CDynamicStructMember<CDynamicVector, float> y;
	static CDynamicStructMember<CDynamicVector, float> z;
	static CDynamicStructMember<CDynamicVector, CDynamicThirdLevel> hard;
	static CDynamicStructMember<CDynamicVector, CDynamicThirdLevel> very_hard;
	static CDynamicStructMember<CDynamicVector, CDynamicThirdLevel[]> sample_array;
	static CDynamicStructMember<CDynamicVector, CDynamicThirdLevel[]> sample_next;
	static CDynamicStructMember<CDynamicVector, tDynamicStructEnd> endOfStructure;
};


CDynamicStructMember<CDynamicVector, float> CDynamicVector::x;	// 0x0
CDynamicStructMember<CDynamicVector, float> CDynamicVector::y;	// 0x4
CDynamicStructMember<CDynamicVector, float> CDynamicVector::z;	// 0x8
CDynamicStructMember<CDynamicVector, CDynamicThirdLevel> CDynamicVector::hard;	// 0xC
CDynamicStructMember<CDynamicVector, CDynamicThirdLevel> CDynamicVector::very_hard;	// 0x10
CDynamicStructMember<CDynamicVector, CDynamicThirdLevel[]> CDynamicVector::sample_array;	// 0x14
CDynamicStructMember<CDynamicVector, CDynamicThirdLevel[]> CDynamicVector::sample_next;		// 0x1C
CDynamicStructMember<CDynamicVector, tDynamicStructEnd> CDynamicVector::endOfStructure;		// 0x24

struct CDynamicBox : public CDynamicStructure
{
	static CDynamicStructMember<CDynamicBox, CDynamicVector> inf;
	static CDynamicStructMember<CDynamicBox, CDynamicVector> sup;
	static CDynamicStructMember<CDynamicBox, tDynamicStructEnd> endOfStructure;
};

CDynamicStructMember<CDynamicBox, CDynamicVector> CDynamicBox::inf;
CDynamicStructMember<CDynamicBox, CDynamicVector> CDynamicBox::sup;
CDynamicStructMember<CDynamicBox, tDynamicStructEnd> CDynamicBox::endOfStructure;
#endif

template <typename T> class CDynamicArray
{
public:
	char bytes[];

	T & operator[](size_t index) {
		return *(T*)&bytes[index * TypeDetails::SizeOf<T>()];
	}

	const T & operator[](size_t index) const {
		return *(const T*)&bytes[index * TypeDetails::SizeOf<T>()];
	}
};

void** pTimeCycle = nullptr;

uintptr_t Address_CTimeCycle_UpdateTimeCycleEditor = 0;

void CallUpdateTimeCycleEditor()
{
	((void(__thiscall *)(void*))Address_CTimeCycle_UpdateTimeCycleEditor)(*pTimeCycle);
}

#ifdef IS_PLATFORM_ANDROID_ARM32
// patch for 0x3EB8DC
extern "C"
{
	uintptr_t Address_CEntity__CreateRwObject_3EB8E0 = 0;
	uintptr_t Address_CEntity__CreateRwObject_3EB8E4_thumb = 0;
}

extern "C"
{
	uint32_t breakpoint_model_ID = 3778;
}

static TARGET_THUMB NAKED void patch_CEntity__CreateRwObject_3EB8DC()
{
	__asm(
	".thumb\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, breakpoint_model_ID)
		"BNE 10f\n"

		"NOP\n"
		"NOP\n"

		"10:\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R1, Address_CEntity__CreateRwObject_3EB8E0)
		"LDR R1, [R1]\n"
		"LDR R9, [R1,R2,LSL#2]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CEntity__CreateRwObject_3EB8E4_thumb)
		);
}

// patch for 0x40FCB8
extern "C"
{
	NOINLINE void VerifyPointer(const char* purpose, CEntity* pEntity)
	{
		uint32_t modelID = pEntity->GetModelID();

		if (modelID == 3778)
		{
			char* pRwObject = (char*)CEntity::m_pRwThing(pEntity).m_pRwObject;

			char type = *(char*)pRwObject;			
			
			if(type != 1)
				pRwObject = g_memoryCall.Function<char*>(g_mCalc.GetCurrentVAbyPreferedVA(0x1901E4), pRwObject);

			char* pGeometry = *(char**)((char*)pRwObject + 0x18);

			char geometry_flag = (*(char*)(pGeometry + 0xB)) & 1;

			uint32_t geometry_flags = *(uint32_t*)(pGeometry + 0x8);

			char* pRepEntry = *(char**)(pGeometry + 0x5C);

			char* field_38 = (char*)0xFFFFFFFF;

			if(pRepEntry)
				field_38 = *(char**)(pRepEntry + 0x38);

			// char* pRepEntry = *(char**)(pGeometry + 0x5C);

			// char* field_38 = *(char**)(pRepEntry + 0x38);


			OutputFormattedDebugString(
				"%s model %d type: %d pEntity: 0x%X pRwObject: 0x%X geometry: 0x%X rep entry: 0x%X field_38: 0x%X geometry flag: %d geometry flags: 0x%X",
				purpose, modelID, type, pEntity, pRwObject, pGeometry, pRepEntry, field_38, geometry_flag, geometry_flags
			);
		}
	}

	void VerifyPointersBeingSorted(CEntity** pFirstEntity, CEntity** pSecondEntity)
	{
		VerifyPointer("sortLODs_first", *pFirstEntity);
		VerifyPointer("sortLODs_second", *pSecondEntity);
	}
}

extern "C"
{
	uintptr_t Address_sortLODs_40FCC0_thumb = 0;
}

static TARGET_THUMB NAKED void patch_sortLODs_40FCB8()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1, R2, LR}\n"
		"BLX VerifyPointersBeingSorted\n"
		"POP {R0, R1, R2, LR}\n"

		"PUSH {R4,R5,R7,LR}\n"
		"ADD R7, SP, #8\n"
		"LDR R0, [R0]\n"
		"LDR R5, [R1]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_sortLODs_40FCC0_thumb)
		);
}

// patch for 0x3EB912
extern "C"
{
	uintptr_t Address_CEntity__CreateRwObject_3EB91C_thumb = 0;

	void VerifyPointersCreateRwObject(CEntity* pEntity)
	{
		VerifyPointer("CreateRwObject", pEntity);
	}
}

static TARGET_THUMB NAKED void patch_CEntity__CreateRwObject_3EB912()
{
	__asm(
	".thumb\n"
		"PUSH {R0, R1}\n"

		"LDRSH.W         R0, [R4,#0x26]\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, breakpoint_model_ID)
		"BNE 10f\n"

		"NOP\n"
		"NOP\n"

		"10:\n"

		"MOV R0, R4\n"
		"BLX VerifyPointersCreateRwObject\n"
		"POP {R0, R1}\n"

		"LDRB R1, [R4,#0x3A]\n"
		"AND R1, R1, #7\n"
		"CMP R1, #1\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CEntity__CreateRwObject_3EB91C_thumb)
		);
}

// patch for 0x5D69C6
extern "C"
{
	uintptr_t Address_CVisibilityPlugins__RenderEntity_1971E8_arm = 0;
	uintptr_t Address_CVisibilityPlugins__RenderEntity_18F864_arm = 0;
	uintptr_t Address_CVisibilityPlugins__RenderEntity_5D69D0_thumb = 0;
}

extern "C"
{
	void beforeRendering(CEntity* pEntity)
	{
		VerifyPointer("before rendering", pEntity);
		// OutputFormattedDebugString("before rendering %d", breakpoint_model_ID);
	}

	void afterRendering(CEntity* pEntity)
	{
		VerifyPointer("after rendering", pEntity);
		// OutputFormattedDebugString("after rendering %d", breakpoint_model_ID);
	}
}

static TARGET_THUMB NAKED void patch_CVisibilityPlugins__RenderEntity_5D69C6()
{
	__asm(
	".thumb\n"

		"LDRSH.W         R0, [R4,#0x26]\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, breakpoint_model_ID)
		"BNE 10f\n"

		"MOV R0, R4\n"
		"BLX beforeRendering\n"

		"10:\n"

		"MOV R0, R6\n"

		"BL 1f\n"

		"LDRSH.W         R0, [R4,#0x26]\n"
		ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, breakpoint_model_ID)
		"BNE 10f\n"

		"MOV R0, R4\n"
		"BLX afterRendering\n"

		"10:\n"

		"BL 2f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVisibilityPlugins__RenderEntity_5D69D0_thumb)

		// Branches
		"1:\n"	// j__Z27AtomicDefaultRenderCallBackP8RpAtomic
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVisibilityPlugins__RenderEntity_1971E8_arm)
		"2:\n"	// j__Z24emu_DisableAlphaModulatev
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CVisibilityPlugins__RenderEntity_18F864_arm)
		);
}

static TARGET_THUMB NAKED void patch_TextureDatabaseRuntime__Load_1EA9E4()
{
	__asm(
	".thumb\n"
		"MOV R0, R8\n"
		"MOV R1, R9\n"
		"BLX showTextureType\n"

		"MOV R0, R4\n"
		"MOVS R1, #1\n"
		"MOVS R2, #0\n"
		"STR R9, [R4,#0x74]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_TextureDatabaseRuntime__Load_1EA9EE_thumb)
		);
}


// patch for 0x1EAA1A
extern "C"
{
	uintptr_t Address_TextureDatabaseRuntime__Load_191F84_arm = 0;
	uintptr_t Address_TextureDatabaseRuntime__Load_1EAA24_thumb = 0;
}

static TARGET_THUMB NAKED void patch_TextureDatabaseRuntime__Load_1EAA1A()
{
	__asm(
	".thumb\n"
		"MOV R0, R4\n"

		"CMP R9, #0\n"
		"ITE EQ\n"
		"MOVEQ R1, #1\n"
		"MOVNE R1, #0\n"

		"BL 1f\n"
		"LDR R0, [R4,#0x18]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_TextureDatabaseRuntime__Load_1EAA24_thumb)

		// Branches
		"1:\n"	// j__ZN22TextureDatabaseRuntime11SortEntriesEb
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_TextureDatabaseRuntime__Load_191F84_arm)
		);
}



// patch for 0x325E80
extern "C"
{
	uintptr_t Address_CAnimViewer__Initialise_453698_arm = 0;
	uintptr_t Address_CAnimViewer__Initialise_456AEC_arm = 0;
	uintptr_t Address_CAnimViewer__Initialise_325E88_arm = 0;
	uintptr_t Address_InitModelIndices = 0;


	void moreInitialization()
	{
		// CTheZones::Init
		uintptr_t Address_CTheZones__Init = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN9CTheZones4InitEv");
		g_memoryCall.Function<void>(Address_CTheZones__Init, *(void**)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "gpTheZones"));

	}
}

static TARGET_ARM NAKED void patch_CAnimViewer__Initialise_325E80()
{
	__asm(
	".arm\n"
		"BLX moreInitialization\n"
		ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(Address_InitModelIndices)

		"BL 1f\n"
		"BL 2f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CAnimViewer__Initialise_325E88_arm)

		// Branches
		"1:\n"	// _ZN10CModelInfo10InitialiseEv
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CAnimViewer__Initialise_453698_arm)
		"2:\n"	// _ZN9CParticle10InitialiseEv
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CAnimViewer__Initialise_456AEC_arm)
		);
}

uintptr_t Address_CAnimViewer__Initialise_325E98_arm = 0;

// patch for 0x325D98
extern "C"
{
	uintptr_t Address_CAnimViewer__Initialise_325DB0 = 0;
	uintptr_t Address_CAnimViewer__Initialise_483518_arm = 0;
	uintptr_t Address_CAnimViewer__Initialise_325DC0 = 0;
	uintptr_t Address_CAnimViewer__Initialise_325DC8 = 0;
	uintptr_t Address_CAnimViewer__Initialise_325DC8_arm = 0;
}

// patch for 0x35208C
static TARGET_ARM NAKED void patch_CGame__Initialise_35208C()
{
	__asm(
		".arm\n"
		"BL 1f\n"

		"MOV             R0, #1\n"
		"SUB             SP, R11, #0x20\n"
		"LDMFD           SP!, {R4-R11,PC}\n"

		"1:\n"
		
		"STMFD SP!, {R4-R11,LR}\n"
		"ADD R11, SP, #0x20\n"
		"SUB SP, SP, #0x94\n"
		
		"LDR R4, =("/* dword_9E0360 */"0x9E0360 - 0x325DC0)\n"
		
		"LDR R5, =("/* _GLOBAL_OFFSET_TABLE_ */"0x74F810 - 0x325DC8)\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R4, Address_CAnimViewer__Initialise_325DC0)
		"MOV R7, #0x1324\n"
		ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R5, Address_CAnimViewer__Initialise_325DC8)
		"MOV R6, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CAnimViewer__Initialise_325E98_arm)
		);
}

// patch for 0x2E853E
extern "C"
{
	uintptr_t Address_CCarCtrl__GenerateOneRandomCar_2E997E_thumb = 0;
	uintptr_t Address_CCarCtrl__GenerateOneRandomCar_2E854A_thumb = 0;
}

extern "C"
{
	void showMultipliers(float s0, float s22)
	{
		OutputFormattedDebugString("max: %f current: %f num mission cars: %d",
			s0,
			s22,
			*(int*)g_mCalc.GetCurrentVAbyPreferedVA(0x796770)
		);
	}
}

static TARGET_THUMB NAKED void patch_CCarCtrl__GenerateOneRandomCar_2E853E()
{
	__asm(
	".thumb\n"
		"VCMPE.F32 S0, S22\n"
		"VMRS APSR_nzcv, FPSCR\n"
		"BLE 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CCarCtrl__GenerateOneRandomCar_2E854A_thumb)

		// Branches
		"1:\n"	// loc_2E997E
		"VMOV R0, S0\n"
		"VMOV R1, S22\n"
		"BLX showMultipliers\n"

		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CCarCtrl__GenerateOneRandomCar_2E997E_thumb)
		);
}
#endif

// Runs test
void CTest::Run()
{
	if (!PROJECT_USE_DEVELOPMENT_INI)
		return;

	MAKE_VAR_GAME_VERSION();

	#ifdef IS_PLATFORM_ANDROID_ARM32

	if (false)
	{
		CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x46F52A), 0x2200);

		// Changes
		Address_TextureDatabaseRuntime__Load_191F84_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x191F84));
		Address_TextureDatabaseRuntime__Load_1EAA24_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x1EAA24));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x1EAA1A),
			(void*)&patch_TextureDatabaseRuntime__Load_1EAA1A
		);



		// Changes
		Address_CEntity__CreateRwObject_3EB8E0 = g_mCalc.GetCurrentVAbyPreferedVA(0x3EB8E0);
		Address_CEntity__CreateRwObject_3EB8E4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3EB8E4));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3EB8DC),
			(void*)&patch_CEntity__CreateRwObject_3EB8DC
		);

		// Changes
		Address_sortLODs_40FCC0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x40FCC0));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x40FCB8),
			(void*)&patch_sortLODs_40FCB8
		);

		Address_CVisibilityPlugins__RenderEntity_1971E8_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x1971E8));
		Address_CVisibilityPlugins__RenderEntity_18F864_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18F864));
		Address_CVisibilityPlugins__RenderEntity_5D69D0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5D69D0));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5D69C6),
			(void*)&patch_CVisibilityPlugins__RenderEntity_5D69C6
		);

		////
		Address_CEntity__CreateRwObject_3EB91C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3EB91C));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3EB912),
			(void*)&patch_CEntity__CreateRwObject_3EB912
		);
	}

	if(false)
	{


		///////



		/*

		uintptr_t Address_GameStart = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_Z9GameStartv");
		uintptr_t Address_TheModelViewer = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_Z14TheModelViewerv");

		CPatch::RedirectFunction(Address_GameStart, (void*)Address_TheModelViewer);

		// Changes
		Address_InitModelIndices = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_Z16InitModelIndicesv");

		Address_CAnimViewer__Initialise_453698_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x453698));
		Address_CAnimViewer__Initialise_456AEC_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x456AEC));
		Address_CAnimViewer__Initialise_325E88_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x325E88));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_ARM, g_mCalc.GetCurrentVAbyPreferedVA(0x325E80),
			(void*)&patch_CAnimViewer__Initialise_325E80
		);
		*/

		uintptr_t Address_TheModelViewerCore = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_Z18TheModelViewerCorev");
		uintptr_t Address_CGame__Process = (uintptr_t)Library::GetSymbolAddress(&g_LimitAdjuster.hModule_of_game, "_ZN5CGame7ProcessEf");

		CPatch::RedirectFunction(Address_CGame__Process, (void*)Address_TheModelViewerCore);

		// Changes
		Address_CAnimViewer__Initialise_325DB0 = g_mCalc.GetCurrentVAbyPreferedVA(0x325DB0);
		Address_CAnimViewer__Initialise_483518_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x483518));
		Address_CAnimViewer__Initialise_325DC0 = g_mCalc.GetCurrentVAbyPreferedVA(0x325DC0);
		Address_CAnimViewer__Initialise_325DC8 = g_mCalc.GetCurrentVAbyPreferedVA(0x325DC8);
		Address_CAnimViewer__Initialise_325DC8_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x325DC8));

		CPatch::RedirectCodeEx(INSTRUCTION_SET_ARM, g_mCalc.GetCurrentVAbyPreferedVA(0x35208C),
			(void*)&patch_CGame__Initialise_35208C
		);

		CPatch::NOPinstructions(INSTRUCTION_SET_ARM, g_mCalc.GetCurrentVAbyPreferedVA(0x351FAC), 4);

		// CPatch::NOPinstructions(INSTRUCTION_SET_ARM, g_mCalc.GetCurrentVAbyPreferedVA(0x352230), 8);

		Address_CAnimViewer__Initialise_325E98_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x325F08));
	}

	/*
	Address_CCarCtrl__GenerateOneRandomCar_2E997E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2E997E));
	Address_CCarCtrl__GenerateOneRandomCar_2E854A_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2E854A));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2E853E),
		(void*)&patch_CCarCtrl__GenerateOneRandomCar_2E853E
	);
	*/
	#endif

	/*
	{
		pTimeCycle = (void**)dlsym(g_LimitAdjuster.hModule_of_game.linux_os, "pTimeCycle");
		void* first = dlsym(g_LimitAdjuster.hModule_of_game.linux_os, "_ZN6CRopes6UpdateEv");
		Address_CTimeCycle_UpdateTimeCycleEditor = (uintptr_t)dlsym(g_LimitAdjuster.hModule_of_game.linux_os, "_ZN10CTimeCycle21UpdateTimeCycleEditorEv");

		CPatch::RedirectCodeEx(INSTRUCTION_SET_ARM, (uintptr_t)first, (void*)&CallUpdateTimeCycleEditor);

		OutputFormattedDebugString("first: 0x%X second: 0x%X third: 0x%X",
			first,
			Address_CTimeCycle_UpdateTimeCycleEditor,
			pTimeCycle);
	}
	*/

#if 0
	g_StructAllocator.InitPerStruct();
	g_StructAllocator.Allocate(CDynamicThirdLevel::a);
	g_StructAllocator.Allocate(CDynamicThirdLevel::b);
	g_StructAllocator.Allocate(CDynamicThirdLevel::endOfStructure);
	
	g_StructAllocator.InitPerStruct();
	g_StructAllocator.Allocate(CDynamicVector::x);
	g_StructAllocator.Allocate(CDynamicVector::y);
	g_StructAllocator.Allocate(CDynamicVector::z);
	g_StructAllocator.Allocate(CDynamicVector::hard);
	g_StructAllocator.Allocate(CDynamicVector::very_hard);
	g_StructAllocator.Allocate(CDynamicVector::sample_array, 2);
	g_StructAllocator.Allocate(CDynamicVector::sample_next, 2);
	g_StructAllocator.Allocate(CDynamicVector::endOfStructure);

	g_StructAllocator.InitPerStruct();
	g_StructAllocator.Allocate(CDynamicBox::inf);
	g_StructAllocator.Allocate(CDynamicBox::sup);
	g_StructAllocator.Allocate(CDynamicBox::endOfStructure);

	char dataForBox[100];
	CDynamicBox& box = *(CDynamicBox*)dataForBox;
	box.sup(&box).x(box.sup.GetPtr(&box)) = 5.3;
	
	{
		{
			auto pBox = &box;
			auto pVector = pBox->sup.GetPtr(pBox);
			auto pThirdLevel = pVector->hard.GetPtr(pVector);
			pThirdLevel->a(pThirdLevel) = 5;

			// printf_MessageBox("pointer: 0x%X", &pThirdLevel->a(pThirdLevel));
		}

		{
			short value = box.sup(&box).hard().a();

			void* ptr = &box.sup(&box).hard().a();

			/*
			printf_MessageBox(
				"addresses: 0x%X 0x%X | 0x%X value: %d",
				&box,
				ptr,
				SuperAccessLastBasePtr,
				value
			);
			*/			
		}
		/*
		CDynamicArray<CDynamicVector>* vectorArray =
			(CDynamicArray<CDynamicVector>*)new char[TypeDetails<CDynamicVector>::SizeOf()];

			*/

		CDynamicVector* pVector =
			(CDynamicVector*)new char[TypeDetails<CDynamicVector>::SizeOf()];

		pVector->sample_next.Access(pVector)[0].a() = 631;
	pVector->sample_next.Access(pVector)->GetAnother(1).a() = 247;

				
	printf_MessageBox("value: %d", pVector->sample_next.Access(pVector)->GetAnother(0).a());
	}

	g_LimitAdjuster.TerminateProcess();
#endif


	// CPatch::RedirectCode(0x408865, &patch_408865);
	/*
	uint32_t hash = Game_GTAIV::GTAIV_crc32FromUpcaseString("PLAYER");


	printf_MessageBox("hash: 0x%X\n", hash);
	*/


	// g_LimitAdjuster.TerminateProcess();
	/*
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();
	CPatch::PatchRelative32bitReference(0x14019082F + 2, 1, 0x140000666);
	CPatch::LeaveThisLevel();

	// Count of active addresses: 1
	CCodeMover::FixOnAddressRel(0x14019082F, 7, "\x14\x07\x2F\x08\x19\x00\x02\x00", 0x140190836);	// line 1, 0x1401907E0 - sub_1401907E0 : mov     cs:byte_141DB8BA0, 0
	*/

	#ifdef IS_PLATFORM_WIN_X86	
	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		// heat haze FX
		if (PROJECT_USE_DEVELOPMENT_INI)
			CPatch::RedirectCode(0x701A5B, 0x701E79);

		if (PROJECT_IS_UNRELEASED_EDITION)
			CPatch::RedirectCode(0x590ADE, &patch_renderSomethingLoading_590ADE);

		// loading, draw percentage
		CPatch::PatchUINT8(0x590477 + 1, true);
	}
	#elif defined(IS_PLATFORM_ANDROID_ARM32)
	if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		// loading, draw percentage
		CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x43B4B2), 0x2501);
		CPatch::PatchFloat(g_mCalc.GetCurrentVAbyPreferedVA(0x5CA1D8), 20.0);

		// OutputFormattedDebugString("result: %d", division(60));
		// TXD compression 0 for "gta3"
		// CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x46F52A), 0x2200);

		// CPatch::PatchUINT16(g_mCalc.GetCurrentVAbyPreferedVA(0x1E88E4), 0x23);
	}
	#endif

	return;

	tMemoryScanRequest request;
	memset(&request, NULL, sizeof(request));
	request.searchType = MEMORY_SCAN_REQUEST_FUNCTION;
	request.maxCountOfIterations = UINT32_MAX;
	request.minNumberOfBytesNeeded = 4;
	request.ptrAlignment = 1;

	tMemoryScanExtraConditionData extraCondition;
	extraCondition.findCondition = MEMORY_FIND_CONDITION_FLOAT;
	extraCondition.func.funcPtr = [](tMemoryScanControl& control, void* pCustomData)
	{
		CGenericLogStorage::SaveFormattedTextLn("address found: 0x%llX", (uint64_t)control.ptr);

		return true;
	};
	extraCondition.func.pCustomData = NULL;

	// extraCondition.dataToFind.relative4byteAddress.low = 0x141DB8BA0;
	// extraCondition.dataToFind.relative4byteAddress.high = 0x141DB8BA0;

	extraCondition.dataToFind.floatValue.low = 1.0;
	extraCondition.dataToFind.floatValue.high = 1.0;

	request.data.func.funcPtr = &MemoryScanExtraConditionFunc;
	request.data.func.pCustomData = &extraCondition;

	g_mScanner.ProcessSingleRequest(request);

	g_LimitAdjuster.TerminateProcess();
}
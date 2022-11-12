/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "RoadBloxBetterLoader.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/CFileMgr.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

using namespace Game;

RoadBloxBetterLoader g_roadBloxBetterLoader;

namespace Game_GTASA
{
	// Number of road blocks
	unsigned int* CRoadBlocks::NumRoadBlocks;

	// Roadblox flags
	char* CRoadBlocks::InOrOut = NULL;

	// Roadblock nodes
	CNodeAddress* CRoadBlocks::RoadBlockNodes = NULL;

	// Generate dynamic road blocks?
	bool* CRoadBlocks::bGenerateDynamicRoadBlocks;

	// Script roadblocks
	CScriptRoadblock* CRoadBlocks::ScriptRoadBlocks;

	// Max number of script blocks
	unsigned int CRoadBlocks::MaxNumberOfScriptBlocks = 16;

	// Addresses
	extern "C"
	{
		auto Address_CRoadBlocks__Shutdown = &CRoadBlocks::Shutdown;
		auto Address_CRoadBlocks__NumRoadBlocks = &CRoadBlocks::NumRoadBlocks;
		auto Address_CRoadBlocks__InOrOut = &CRoadBlocks::InOrOut;
		auto Address_CRoadBlocks__RoadBlockNodes = &CRoadBlocks::RoadBlockNodes;
		auto Address_CRoadBlocks__bGenerateDynamicRoadBlocks = &CRoadBlocks::bGenerateDynamicRoadBlocks;
		auto Address_CRoadBlocks__ScriptRoadBlocks = &CRoadBlocks::ScriptRoadBlocks;
		auto Address_CRoadBlocks__MaxNumberOfScriptBlocks = &CRoadBlocks::MaxNumberOfScriptBlocks;
	}

	// Inits
	void CRoadBlocks::Init()
	{
		CRoadBlocks::Shutdown();

		///////////////////////////////
		
		*CRoadBlocks::bGenerateDynamicRoadBlocks = false;

		FILESTREAM fp = CFileMgr::OpenFile(
			g_LimitAdjuster.GetPathToFlaFileFromRootDirectory("data\\paths\\roadblox.dat").c_str(),
			"rb");;

		CFileMgr::Read(fp, CRoadBlocks::NumRoadBlocks, sizeof(*CRoadBlocks::NumRoadBlocks));

		CRoadBlocks::InOrOut = new char[*CRoadBlocks::NumRoadBlocks];
		memset(CRoadBlocks::InOrOut, false, *CRoadBlocks::NumRoadBlocks);

		CRoadBlocks::RoadBlockNodes = new CNodeAddress[*CRoadBlocks::NumRoadBlocks];
		CFileMgr::Read(fp, CRoadBlocks::RoadBlockNodes, *CRoadBlocks::NumRoadBlocks * sizeof(CNodeAddress));

		CFileMgr::CloseFile(fp);

		CRoadBlocks::ClearScriptRoadBlocks();
	}

	// Shut downs
	void CRoadBlocks::Shutdown()
	{
		if (CRoadBlocks::InOrOut)
		{
			delete[] CRoadBlocks::InOrOut;
			CRoadBlocks::InOrOut = NULL;
		}

		if (CRoadBlocks::RoadBlockNodes)
		{
			delete[] CRoadBlocks::RoadBlockNodes;
			CRoadBlocks::RoadBlockNodes = NULL;
		}
	}

	// Clears script road blocks
	void CRoadBlocks::ClearScriptRoadBlocks()
	{
		for (unsigned int i = 0; i < CRoadBlocks::MaxNumberOfScriptBlocks; i++)
			CRoadBlocks::ScriptRoadBlocks[i].active = false;
	}

	// flags
	extern "C" void SetRoadBlockFlags()
	{
		memset(CRoadBlocks::InOrOut, 1, *CRoadBlocks::NumRoadBlocks);
	}

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CRoadBlocks__GenerateRoadBlocks_462A5C()
	{
		__asm
		{
			call SetRoadBlockFlags;

			push 0x462A6E;
			retn;
		}
	}
	#elif defined(IS_PLATFORM_ANDROID_ARM32)
	// patch for 0x32507A
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325084 = 0;
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_18B35C_arm = 0;	// __aeabi_memset
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325088_thumb = 0;	// loc_325088
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32507A()
	{
		__asm(
		".thumb\n"
			"BLX SetRoadBlockFlags\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325088_thumb)
			);
	}

	// patch for 0x32511C
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325124 = 0;
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32512E = 0;
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325138 = 0;
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325142 = 0;
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32514C = 0;
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325156 = 0;
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325160 = 0;
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32516A = 0;
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325178 = 0;
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325182 = 0;
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32518C = 0;
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32518C_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32511C()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CRoadBlocks__InOrOut)	// &CRoadBlocks::InOrOut
			"LDR R0, [R0]\n"	// CRoadBlocks::InOrOut
			"STR R0, [SP,#0x1D0+"/* var_180 */"-0x180]\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CRoadBlocks__InOrOut)	// &CRoadBlocks::InOrOut
			"LDR R0, [R0]\n"	// CRoadBlocks::InOrOut
			"STR R0, [SP,#0x1D0+"/* var_18C */"-0x18C]\n"

			"LDR R0, =("/* _ZN11CRoadBlocks13NumRoadBlocksE_ptr */"0x679350 - 0x325138)\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325138)
			"LDR R0, [R0]\n"
			"STR R0, [SP,#0x1D0+"/* var_198 */"-0x198]\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CRoadBlocks__RoadBlockNodes)	// &CRoadBlocks::RoadBlockNodes
			"LDR R0, [R0]\n"	// CRoadBlocks::RoadBlockNodes
			"STR R0, [SP,#0x1D0+"/* var_19C */"-0x19C]\n"

			"LDR R0, =("/* _ZN11CRoadBlocks13NumRoadBlocksE_ptr */"0x679350 - 0x32514C)\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32514C)
			"LDR R0, [R0]\n"
			"STR R0, [SP,#0x1D0+"/* var_188 */"-0x188]\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CRoadBlocks__InOrOut)	// &CRoadBlocks::InOrOut
			"LDR R0, [R0]\n"	// CRoadBlocks::InOrOut
			"STR R0, [SP,#0x1D0+"/* var_190 */"-0x190]\n"

			"LDR R0, =("/* ThePaths_ptr */"0x677378 - 0x325160)\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325160)
			"LDR R0, [R0]\n"
			"STR R0, [SP,#0x1D0+"/* var_194 */"-0x194]\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CRoadBlocks__InOrOut)	// &CRoadBlocks::InOrOut
			"LDR R0, [R0]\n"	// CRoadBlocks::InOrOut
			"STR R0, [SP,#0x1D0+"/* var_1A0 */"-0x1A0]\n"

			"LDR R0, [R1]\n"
			"STR R0, [SP,#0x1D0+"/* var_1A4 */"-0x1A4]\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CRoadBlocks__InOrOut)	// &CRoadBlocks::InOrOut
			"LDR R0, [R0]\n"	// CRoadBlocks::InOrOut
			"STR R0, [SP,#0x1D0+"/* var_184 */"-0x184]\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CRoadBlocks__InOrOut)	// &CRoadBlocks::InOrOut
			"LDR R0, [R0]\n"	// CRoadBlocks::InOrOut
			"STR R0, [SP,#0x1D0+"/* var_17C */"-0x17C]\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CRoadBlocks__InOrOut)	// &CRoadBlocks::InOrOut
			"LDR R0, [R0]\n"	// CRoadBlocks::InOrOut
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32518C_thumb)
			);
	}
	#endif

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CRoadBlocks__GenerateRoadBlocks_462A77()
	{
		__asm
		{
			mov eax, CRoadBlocks::NumRoadBlocks;
			mov eax, [eax];
			imul ecx, eax;

			mov     eax, ecx;
			cdq;
			and edx, 0Fh;
			add     eax, edx;
			mov     ebp, eax;

			mov edx, CRoadBlocks::NumRoadBlocks;
			mov edx, [edx];

			lea     eax, [ecx + edx];

			push 0x462A8D;
			retn;
		}
	}
	#elif defined(IS_PLATFORM_ANDROID_ARM32)
	// patch for 0x32508C
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325094_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32508C()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R3, Address_CRoadBlocks__NumRoadBlocks) // &CRoadBlocks__NumRoadBlocks
			"LDR R3, [R3]\n" // CRoadBlocks::NumRoadBlocks
			"LDR R3, [R3]\n" // *CRoadBlocks::NumRoadBlocks

			"LDR R1, =("/* _ZN11CRoadBlocks13NumRoadBlocksE_ptr */"0x679350 - 0x32509E)\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325094_thumb)
			);
	}
	#endif

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CRoadBlocks__GenerateRoadBlocks_462BC1()
	{

		__asm
		{
			mov ecx, CRoadBlocks::InOrOut;
			mov al, [ebp + ecx];
			test    al, al;
			jnz     loc_4632E2;

			push - 1;
			mov[ebp + ecx], 1;

			push 0x462BD8;
			retn;

		loc_4632E2:
			push 0x4632E2;
			retn;
		}
	}

	NAKED void patch_CRoadBlocks__GenerateRoadBlocks_462EE3()
	{
		__asm
		{
			mov ecx, CRoadBlocks::InOrOut;
			mov cl, [ebx + ecx];

			push 0x462EE9;
			retn;
		}
	}

	NAKED void patch_CRoadBlocks__GenerateRoadBlocks_4631EC()
	{
		__asm
		{
			mov ecx, CRoadBlocks::InOrOut;
			mov byte ptr[ebx + ecx], 1;

			push 0x4631F3;
			retn;
		}
	}

	NAKED void patch_CRoadBlocks__GenerateRoadBlocks_4632DB()
	{
		__asm
		{
			mov ecx, CRoadBlocks::InOrOut;
			mov byte ptr[ebp + ecx], 0;

			push 0x4632E2;
			retn;
		}
	}
	#endif

	//////////////////
	
	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CRoadBlocks__GenerateRoadBlocks_462ABD()
	{
		__asm
		{
			mov ecx, CRoadBlocks::RoadBlockNodes;
			mov edi, [ebp * 4 + ecx];

			push 0x462AC4;
			retn;
		}
	}
	#endif



	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CGame__Shutdown_53CAF1()
	{
		__asm
		{
			pop     edi;
			pop esi;

			call CRoadBlocks::Shutdown;
			mov al, 1;
			retn;
		}
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	// patch for 0x3F39B0
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CGame__Shutdown_18A40C_arm = 0;	// j__Z20CdStreamRemoveImagesv
		uintptr_t Address_GTA_SA_2_00_CGame__Shutdown_3F39B8_thumb = 0;	// off_3F39B8
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGame__Shutdown_3F39B0()
	{
		__asm(
		".thumb\n"
			"BL 1f\n"
			
			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CRoadBlocks__Shutdown)
			"BLX R0\n"

			"MOVS R0, #1\n"
			"POP {R4,R6,R7,PC}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGame__Shutdown_3F39B8_thumb)

			// Branches
			"1:\n"	// j__Z20CdStreamRemoveImagesv
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGame__Shutdown_18A40C_arm)
			);
	}

	// patch for 0x3F3D14
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CGame__ShutDownForRestart_3F3D1A = 0;
		uintptr_t Address_GTA_SA_2_00_CGame__ShutDownForRestart_3F3D1E_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CGame__ShutDownForRestart_3F3D14()
	{
		__asm(
		".thumb\n"
			"LDR R0, =("/* _ZN8CVehicle24ms_forceVehicleLightsOffE_ptr */"0x679D90 - 0x3F3D1A)\n"
			ASM_ADD_ADDRESS_STORED_ON_SYMBOL(R0, Address_GTA_SA_2_00_CGame__ShutDownForRestart_3F3D1A)
			"LDR R0, [R0]\n"
			"STRB R4, [R0]\n"

			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CRoadBlocks__Shutdown)
			"BLX R0\n"

			"POP {R4,R6,R7,PC}\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CGame__ShutDownForRestart_3F3D1E_thumb)
			);
	}

	// road block nodes
	// patch for 0x3250E8
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3250F0_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3250E8()
	{
		__asm(
		".thumb\n"
			ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, Address_CRoadBlocks__RoadBlockNodes) // &CRoadBlocks::RoadBlockNodes
			"LDR R0, [R0]\n"	// CRoadBlocks::RoadBlockNodes
			
			"VMOV.F32 S30, #1.0\n"
			"STR R0, [SP,#0x1D0+"/* var_168 */"-0x168]\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3250F0_thumb)
			);
		}
	#endif

	#ifdef IS_PLATFORM_WIN_X86
	NAKED void patch_CRoadBlocks__GenerateRoadBlocks_462ED2()
	{
		__asm
		{
			mov ecx, CRoadBlocks::RoadBlockNodes;
			mov eax, [ebx * 4 + ecx];

			push 0x462ED9;
			retn;
		}
	}

	// patch for 0x53C66C
	static NAKED void patch_CGame__ShutDownForRestart_53C66C()
	{
		__asm
		{
			push eax;
			mov eax, 0xC1CC18;
			mov byte ptr[eax], 0;

			call CRoadBlocks::Shutdown;
			pop eax;
			pop esi;
			retn;
		}
	}
	#endif
}

// Initialize
void RoadBloxBetterLoader::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
	{
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			using namespace Game_GTASA;

			// Number of road blocks
			CRoadBlocks::NumRoadBlocks = (unsigned int*)0xA43580;
			
			// Generate dynamic road blocks?
			CRoadBlocks::bGenerateDynamicRoadBlocks = (bool*)0xA43584;

			// Script roadblocks
			CRoadBlocks::ScriptRoadBlocks = (CScriptRoadblock*)0xA43AB8;
		}
		#elif defined(IS_PLATFORM_ANDROID_ARM32)
		{
			using namespace Game_GTASA;

			// Number of road blocks
			CRoadBlocks::NumRoadBlocks = (unsigned int*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN11CRoadBlocks13NumRoadBlocksE"
			);

			// Generate dynamic road blocks?
			CRoadBlocks::bGenerateDynamicRoadBlocks = (bool*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN11CRoadBlocks26bGenerateDynamicRoadBlocksE"
			);

			// Script roadblocks
			CRoadBlocks::ScriptRoadBlocks = (CScriptRoadblock*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN11CRoadBlocks17aScriptRoadBlocksE"
			);
		}
		#endif
	}
}

// Applies better loader
void RoadBloxBetterLoader::ApplyBetterLoader()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		CPatch::EnterNewLevel();

		CPatch::RedirectFunction(0x461100, &CRoadBlocks::Init);

		CPatch::RedirectCode(0x462A77, &patch_CRoadBlocks__GenerateRoadBlocks_462A77);

		// flags
		CPatch::RedirectCode(0x462A5C, &patch_CRoadBlocks__GenerateRoadBlocks_462A5C);
		CPatch::RedirectCode(0x462BC1, &patch_CRoadBlocks__GenerateRoadBlocks_462BC1);
		CPatch::RedirectCode(0x462EE3, &patch_CRoadBlocks__GenerateRoadBlocks_462EE3);
		CPatch::RedirectCode(0x4631EC, &patch_CRoadBlocks__GenerateRoadBlocks_4631EC);
		CPatch::RedirectCode(0x4632DB, &patch_CRoadBlocks__GenerateRoadBlocks_4632DB);
		
		// road block nodes
		CPatch::RedirectCode(0x462ABD, &patch_CRoadBlocks__GenerateRoadBlocks_462ABD);
		CPatch::RedirectCode(0x462ED2, &patch_CRoadBlocks__GenerateRoadBlocks_462ED2);

		CPatch::EnterNewLevelAndDisableDebugState();
		CPatch::PatchUINT8(0x84A640, 0xC3);	// CRoadBlocks::RoadBlockNodes destructor
		CPatch::LeaveThisLevel();

		// shutdown
		CPatch::RedirectCode(0x53CAF1, &patch_CGame__Shutdown_53CAF1);

		// shutdown for restart
		CPatch::RedirectCode(g_mCalc.GetCurrentVAbyPreferedVA(0x53C66C), &patch_CGame__ShutDownForRestart_53C66C);
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		CPatch::RedirectFunction((uintptr_t)Library::GetSymbolAddress(
			&g_LimitAdjuster.hModule_of_game,
			"_ZN11CRoadBlocks4InitEv"
		), (void*)&CRoadBlocks::Init);

		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325094_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x325094));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32508C),
			(void*)&patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32508C
		);

		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325084 = g_mCalc.GetCurrentVAbyPreferedVA(0x325084);
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_18B35C_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18B35C));
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325088_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x325088));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32507A),
			(void*)&patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32507A
		);

		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325124 = g_mCalc.GetCurrentVAbyPreferedVA(0x325124);
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32512E = g_mCalc.GetCurrentVAbyPreferedVA(0x32512E);
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325138 = g_mCalc.GetCurrentVAbyPreferedVA(0x325138);
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325142 = g_mCalc.GetCurrentVAbyPreferedVA(0x325142);
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32514C = g_mCalc.GetCurrentVAbyPreferedVA(0x32514C);
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325156 = g_mCalc.GetCurrentVAbyPreferedVA(0x325156);
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325160 = g_mCalc.GetCurrentVAbyPreferedVA(0x325160);
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32516A = g_mCalc.GetCurrentVAbyPreferedVA(0x32516A);
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325178 = g_mCalc.GetCurrentVAbyPreferedVA(0x325178);
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_325182 = g_mCalc.GetCurrentVAbyPreferedVA(0x325182);
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32518C = g_mCalc.GetCurrentVAbyPreferedVA(0x32518C);
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32518C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32518C));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x32511C),
			(void*)&patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_32511C
		);

		// shutdown
		Address_GTA_SA_2_00_CGame__Shutdown_18A40C_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x18A40C));
		Address_GTA_SA_2_00_CGame__Shutdown_3F39B8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3F39B8));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3F39B0),
			(void*)&patch_GTA_SA_2_00_CGame__Shutdown_3F39B0
		);

		// shutdown for restart
		Address_GTA_SA_2_00_CGame__ShutDownForRestart_3F3D1A = g_mCalc.GetCurrentVAbyPreferedVA(0x3F3D1A);
		Address_GTA_SA_2_00_CGame__ShutDownForRestart_3F3D1E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3F3D1E));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3F3D14),
			(void*)&patch_GTA_SA_2_00_CGame__ShutDownForRestart_3F3D14
		);

		// destructor
		CPatch::PatchMemoryData(g_mCalc.GetCurrentVAbyPreferedVA(0x1A3708), "\x70\x47", 2); // BX LR

		// road blox nodes
		Address_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3250F0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3250F0));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3250E8),
			(void*)&patch_GTA_SA_2_00_CRoadBlocks__GenerateRoadBlocks_3250E8
		);
	}
	#endif
	else
		return;

	CGenericLogStorage::SaveFormattedTextLn(
		"Roadblox.dat better loader is enabled."
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}
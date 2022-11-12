/*
* Copyright (C) 2014-2017  fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#ifdef IS_PLATFORM_WIN_X86
namespace IDaccessPatches
{
	// Function: sub_454AE0
	// Original code:	movzx   ecx, ds:MI_PICKUP_BODYARMOUR
	static NAKED void patch_401527()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5C0;	// MI_PICKUP_BODYARMOUR
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_734570
	// Original code:	movzx   ecx, ds:MI_GRASSHOUSE
	static NAKED void patch_401D56()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6F4;	// MI_GRASSHOUSE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_403EC0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_403EC8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_403EC0
	// Original code:	mov     [esi+22h], dx
	static NAKED void patch_403EE8()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_403EC0
	// Original code:	mov     [esi+22h], ax
	static NAKED void patch_403EF5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 22h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN9CIplStore9RemoveIplEi
	// Original code:	movsx   edi, word ptr [ebx+22h]
	static NAKED void patch_404B4A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN9CIplStore9RemoveIplEi
	// Original code:	movsx   edx, word ptr [ebx+24h]
	static NAKED void patch_404B5D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebx + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN9CIplStore9RemoveIplEi
	// Original code:	movsx   edx, word ptr [ebx+24h]
	static NAKED void patch_404BA8()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebx + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN9CIplStore9RemoveIplEi
	// Original code:	movsx   edi, word ptr [ebx+26h]
	static NAKED void patch_404C0F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ebx + 26h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN9CIplStore9RemoveIplEi
	// Original code:	movsx   ecx, word ptr [ebx+28h]
	static NAKED void patch_404C13()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebx + 28h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN9CIplStore9RemoveIplEi
	// Original code:	movsx   eax, word ptr [ebx+28h]
	static NAKED void patch_404C4E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 28h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   ecx, ds:MI_SINGLESTREETLIGHTS1
	static NAKED void patch_4058EE()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD518;	// MI_SINGLESTREETLIGHTS1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_405C00
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_405CDB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_405C00
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_405E4C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     word ptr [esi+22h], 495
	static NAKED void patch_40649C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 495;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     word ptr [esi+22h], 495
	static NAKED void patch_40649C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 495;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CADD0
	// Original code:	cmp     word ptr [esi+22h], 208h
	static NAKED void patch_406AF1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CADD0
	// Original code:	cmp     word ptr [esi+22h], 208h
	static NAKED void patch_406AF1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D0C00
	// Original code:	mov     ax, [esi+598h]
	static NAKED void patch_407645()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 598h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D4290
	// Original code:	cmp     dx, 476
	static NAKED void patch_407A15_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push edx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 476;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D4290
	// Original code:	cmp     dx, 476
	static NAKED void patch_407A15_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, dx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 476;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_644470
	// Original code:	movzx   ecx, ds:MI_GANG_SMOKE
	static NAKED void patch_407F90()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD72C;	// MI_GANG_SMOKE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4083A0
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_4083A0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: CStreaming__RequestModel
	// Original code:	movsx   ecx, word ptr [ebp+0Ah]
	static NAKED void patch_40890A()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebp + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_408CB0
	// Original code:	movsx   eax, word ptr [eax+0Ah]
	static NAKED void patch_408D28()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_408CB0
	// Original code:	movsx   edx, word ptr [ecx+0Ah]
	static NAKED void patch_408D5A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: CStreaming__GetNextFileOnCd
	// Original code:	movsx   eax, word ptr [ecx+0Ah]
	static NAKED void patch_408EC7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: CStreaming__GetNextFileOnCd
	// Original code:	movsx   eax, word ptr [eax+6]
	static NAKED void patch_408F6E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 6];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4093B0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_4093F0()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4093B0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_40940B()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_409430
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_40948B()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4095C0
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_4095F5()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4095C0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_40962B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_409760
	// Original code:	movsx   edi, word ptr [esi+22h]
	static NAKED void patch_4097AF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_409760
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_4098A2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_409940
	// Original code:	movsx   edi, word ptr [esi+22h]
	static NAKED void patch_409971()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4099E0
	// Original code:	movsx   edi, word ptr [esi+22h]
	static NAKED void patch_409A32()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_409C70
	// Original code:	movsx   edx, word ptr [ecx+0Ah]
	static NAKED void patch_409C7B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_409C90
	// Original code:	movsx   esi, word ptr [ecx+0Ah]
	static NAKED void patch_409CFC()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_409D10
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_409DC1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_409D10
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_409E2D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_409D10
	// Original code:	movsx   esi, word ptr [edx+0Ah]
	static NAKED void patch_409F1D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS
	static NAKED void patch_40A0BF()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD4F4;	// MI_TRAFFICLIGHTS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40A2A0
	// Original code:	movsx   eax, word ptr [edx+0Ah]
	static NAKED void patch_40A2BF()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_40A2A0
	// Original code:	movsx   ecx, word ptr [eax+0Ah]
	static NAKED void patch_40A2E7()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40A2A0
	// Original code:	movsx   edx, word ptr [ecx+0Ah]
	static NAKED void patch_40A30F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40A2A0
	// Original code:	movsx   eax, word ptr [edx+0Ah]
	static NAKED void patch_40A337()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_40A2A0
	// Original code:	movsx   ecx, word ptr [eax+0Ah]
	static NAKED void patch_40A35F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40A2A0
	// Original code:	movsx   edx, word ptr [ecx+0Ah]
	static NAKED void patch_40A387()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40A560
	// Original code:	movsx   eax, word ptr [edx+0Ah]
	static NAKED void patch_40A5B9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_40A560
	// Original code:	movsx   edx, word ptr [ecx+0Ah]
	static NAKED void patch_40A738()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40A560
	// Original code:	movsx   esi, word ptr [edx+0Ah]
	static NAKED void patch_40A8EC()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40AA10
	// Original code:	movsx   edx, word ptr [edx+0Ah]
	static NAKED void patch_40AC23()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40AA10
	// Original code:	movsx   esi, word ptr [eax+0Ah]
	static NAKED void patch_40AE92()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40B700
	// Original code:	movzx   edx, ds:MI_HARVESTERBODYPART1
	static NAKED void patch_40B9D1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6E4;	// MI_HARVESTERBODYPART1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40B700
	// Original code:	movzx   eax, ds:MI_HARVESTERBODYPART2
	static NAKED void patch_40B9E0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD6E8;	// MI_HARVESTERBODYPART2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_40B700
	// Original code:	movzx   ecx, ds:MI_HARVESTERBODYPART3
	static NAKED void patch_40B9EF()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6EC;	// MI_HARVESTERBODYPART3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40B700
	// Original code:	movzx   edx, ds:MI_HARVESTERBODYPART4
	static NAKED void patch_40B9FE()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6F0;	// MI_HARVESTERBODYPART4
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40B700
	// Original code:	movzx   eax, ds:MI_HARVESTERBODYPART1
	static NAKED void patch_40BA28()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD6E4;	// MI_HARVESTERBODYPART1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_40B700
	// Original code:	movzx   ecx, ds:MI_HARVESTERBODYPART2
	static NAKED void patch_40BA35()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6E8;	// MI_HARVESTERBODYPART2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40B700
	// Original code:	movzx   edx, ds:MI_HARVESTERBODYPART3
	static NAKED void patch_40BA42()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6EC;	// MI_HARVESTERBODYPART3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40B700
	// Original code:	movzx   eax, ds:MI_HARVESTERBODYPART4
	static NAKED void patch_40BA4F()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD6F0;	// MI_HARVESTERBODYPART4
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_40BAA0
	// Original code:	movsx   edx, word ptr [edx+0Ah]
	static NAKED void patch_40BB29()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40BE60
	// Original code:	lea     eax, [esi-57h]
	static NAKED void patch_40BE72()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push esi;
			call GetModelIDforModelSpecialFeatures;
			mov esi, eax;
			add esp, 4;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40BE60
	// Original code:	movsx   edx, word ptr [ecx+0Ah]
	static NAKED void patch_40BEE4()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40C270
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_40C2B2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_40C270
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_40C423()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40C450
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_40C48A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_40C450
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_40C500()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: CStreaming__ConvertBufferToObject
	// Original code:	movsx   ecx, word ptr [ebp+0Ah]
	static NAKED void patch_40C70D()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebp + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: CStreaming__ConvertBufferToObject
	// Original code:	movsx   eax, word ptr [ebp+0Ah]
	static NAKED void patch_40C76E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: CStreaming__ConvertBufferToObject
	// Original code:	movsx   ecx, word ptr [ebp+0Ah]
	static NAKED void patch_40C824()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebp + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: CStreaming__ConvertBufferToObject
	// Original code:	movsx   eax, word ptr [eax+6]
	static NAKED void patch_40C8CE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 6];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: CStreaming__RequestModelStream
	// Original code:	movsx   eax, word ptr [edi+0Ah]
	static NAKED void patch_40CD93()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_40E170
	// Original code:	movsx   ecx, word ptr [eax+0Ah]
	static NAKED void patch_40E242()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_41A820
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_41A8DA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_41A990
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_41AA45()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_41A990
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_41AA75()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_41AB20
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_41AB94()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4011EF
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_41C0A6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4011EF
	// Original code:	add     eax, 0FFFFFE55h
	static NAKED void patch_41C0AA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_41D660
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_41D77A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_403C48
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_41DEE1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403C48
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_41DEE1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403C48
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_41E24C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403C48
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_41E24C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403C48
	// Original code:	cmp     [esi+22h], di
	static NAKED void patch_41F2A7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push edi;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403C48
	// Original code:	cmp     [esi+22h], di
	static NAKED void patch_41F2A7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx edi, di;
			push edi;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403C48
	// Original code:	cmp     [esi+22h], di
	static NAKED void patch_41F34D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push edi;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403C48
	// Original code:	cmp     [esi+22h], di
	static NAKED void patch_41F34D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx edi, di;
			push edi;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4217C0
	// Original code:	movzx   edx, ds:MI_GANG_SMOKE
	static NAKED void patch_4217F4()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD72C;	// MI_GANG_SMOKE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4217C0
	// Original code:	movsx   esi, word ptr [esi+22h]
	static NAKED void patch_421860()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4217C0
	// Original code:	movzx   eax, ds:MI_GANG_SMOKE
	static NAKED void patch_4218D8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD72C;	// MI_GANG_SMOKE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_421FE0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_421FE4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_421FE0
	// Original code:	add     eax, 0FFFFFE6Dh
	static NAKED void patch_421FE8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_424F80
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_4250A6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_424F80
	// Original code:	cmp     ax, 416
	static NAKED void patch_4250AA_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 416;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_424F80
	// Original code:	cmp     ax, 416
	static NAKED void patch_4250AA_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 416;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_424F80
	// Original code:	cmp     ax, 407
	static NAKED void patch_4250B0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 407;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_424F80
	// Original code:	cmp     ax, 407
	static NAKED void patch_4250B0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 407;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_425440
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_425463()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_425440
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_425502()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_425B30
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_425B7E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_425B30
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_425B9D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_425F70
	// Original code:	movsx   edx, word ptr [edx+22h]
	static NAKED void patch_425F9D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_425F70
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_425FA5()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_426220
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_4262A8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_426220
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_4262C5()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_426350
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_42647A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426350
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_4264EC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426350
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_426555()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426350
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_4265BC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426350
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_426638()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426350
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_4266B2()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426350
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_42671B()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426350
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_426785()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426350
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_4267EC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426350
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_4267FB()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426970
	// Original code:	movsx   edx, word ptr [ebx+22h]
	static NAKED void patch_426A2A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426BC0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS
	static NAKED void patch_426BC0()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD4F4;	// MI_TRAFFICLIGHTS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426BC0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_426BCF()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_426BC0
	// Original code:	movzx   edx, ds:MI_SINGLESTREETLIGHTS1
	static NAKED void patch_426BEC()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD518;	// MI_SINGLESTREETLIGHTS1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426BC0
	// Original code:	movzx   ecx, ds:MI_SINGLESTREETLIGHTS2
	static NAKED void patch_426C01()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD51C;	// MI_SINGLESTREETLIGHTS2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426BC0
	// Original code:	movzx   edx, ds:MI_SINGLESTREETLIGHTS3
	static NAKED void patch_426C16()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD520;	// MI_SINGLESTREETLIGHTS3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426BC0
	// Original code:	movzx   ecx, ds:MI_DOUBLESTREETLIGHTS
	static NAKED void patch_426C33()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD524;	// MI_DOUBLESTREETLIGHTS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426BC0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_426D69()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_426EF0
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_426F94_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_426EF0
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_426F94_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_427740
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_427790_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_427740
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_427790_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_428DE0
	// Original code:	cmp     word ptr [esi+22h], 1AEh
	static NAKED void patch_429051_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_428DE0
	// Original code:	cmp     word ptr [esi+22h], 1AEh
	static NAKED void patch_429051_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_42B7D7
	// Original code:	lea     eax, [ebx-197h]
	static NAKED void patch_42BBC8()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ebx;
			call GetModelIDforModelSpecialFeatures;
			mov ebx, eax;
			add esp, 4;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_42C2B0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_42C489()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_42C740
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_42C793()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_42C740
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_42C7D0()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_42D4F0
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_42D52A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_42D4F0
	// Original code:	movzx   ecx, ds:MI_ROADWORKBARRIER1
	static NAKED void patch_42D52E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD57C;	// MI_ROADWORKBARRIER1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_42D4F0
	// Original code:	movzx   edx, ds:MI_ROADBLOCKFUCKEDCAR1
	static NAKED void patch_42D539()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD580;	// MI_ROADBLOCKFUCKEDCAR1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_42D4F0
	// Original code:	movzx   ecx, ds:MI_ROADBLOCKFUCKEDCAR2
	static NAKED void patch_42D544()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD584;	// MI_ROADBLOCKFUCKEDCAR2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_42DAB0
	// Original code:	cmp     word ptr [edi+22h], 21Bh
	static NAKED void patch_42DB2E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_42DAB0
	// Original code:	cmp     word ptr [edi+22h], 21Bh
	static NAKED void patch_42DB2E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_42DAB0
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_42DB7D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_42DAB0
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_42DC26()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_42DAB0
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_42DD30()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_42DAB0
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_42DD93()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_42DAB0
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_42DDE9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_42DE80
	// Original code:	movsx   eax, word ptr [ecx+ebp+10h]
	static NAKED void patch_42E223()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + ebp + 10h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_42DE80
	// Original code:	movsx   eax, word ptr [ecx+ebp+10h]
	static NAKED void patch_42E255()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + ebp + 10h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_42DE80
	// Original code:	movsx   ecx, word ptr [eax+ebp+10h]
	static NAKED void patch_42E384()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + ebp + 10h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_42DE80
	// Original code:	movsx   ecx, word ptr [eax+ebp+10h]
	static NAKED void patch_42E3B2()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + ebp + 10h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_42EC90
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_42EC9E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_42FC40
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_42FE50_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_42FC40
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_42FE50_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_42FC40
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_42FF0B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_42FC40
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_42FF0B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_43072E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	movsx   edx, cx
	static NAKED void patch_430732()
	{
		__asm
		{
			mov edx, ecx;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     cx, 446
	static NAKED void patch_430778_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 446;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     cx, 446
	static NAKED void patch_430778_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 446;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     cx, 452
	static NAKED void patch_43077F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 452;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     cx, 452
	static NAKED void patch_43077F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 452;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     cx, 493
	static NAKED void patch_430786_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 493;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     cx, 493
	static NAKED void patch_430786_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 493;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     word ptr [esi+22h], 1A7h
	static NAKED void patch_4308A1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 423;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     word ptr [esi+22h], 1A7h
	static NAKED void patch_4308A1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 423;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_430943()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_43181F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	movzx   eax, ds:MI_HYDRAULICS
	static NAKED void patch_43198E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD76C;	// MI_HYDRAULICS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     word ptr [esi+22h], 1E4h
	static NAKED void patch_431A99_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 484;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     word ptr [esi+22h], 1E4h
	static NAKED void patch_431A99_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 484;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_431B42()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_431BC7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_431BEB()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 531
	static NAKED void patch_431BF2_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 531
	static NAKED void patch_431BF2_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 532
	static NAKED void patch_431BF8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 532
	static NAKED void patch_431BF8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     word ptr [esi+22h], 1C9h
	static NAKED void patch_431C57_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     word ptr [esi+22h], 1C9h
	static NAKED void patch_431C57_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_431D89()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 463
	static NAKED void patch_431D8D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 463;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 463
	static NAKED void patch_431D8D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 463;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 461
	static NAKED void patch_431D93_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 461;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 461
	static NAKED void patch_431D93_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 461;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 521
	static NAKED void patch_431D99_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 521;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 521
	static NAKED void patch_431D99_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 521;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 522
	static NAKED void patch_431D9F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 522;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 522
	static NAKED void patch_431D9F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 522;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 581
	static NAKED void patch_431DA5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 581;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 581
	static NAKED void patch_431DA5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 581;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 586
	static NAKED void patch_431DAB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 586;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	cmp     ax, 586
	static NAKED void patch_431DAB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 586;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_431F00()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_403AEE
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_431F0A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_435830
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_435A81_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_435830
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_435A81_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_436A90
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_436B2D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_436A90
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_436B3B()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_436A90
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_437727()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_436A90
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_437736()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_436A90
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_437792()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_436A90
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_4377A1()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_436A90
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_4377E2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_436A90
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_4377F1()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_436A90
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_43783D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_436A90
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_43784C()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_437C20
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_4382A4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_437C20
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_4382A4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_439880
	// Original code:	mov     ax, ds:MI_PICKUP_ADRENALINE
	static NAKED void patch_439896()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD5BC;	// MI_PICKUP_ADRENALINE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _spawnCarAtPlayerLocation
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_43A341()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_43A710
	// Original code:	mov     ax, [esi+0Ah]
	static NAKED void patch_43A72E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_43B0F0
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_43B3DF()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_43DCD0
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_43DE61()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_43DF20
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_43DF50()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_43DF20
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_43DFAA_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_43DF20
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_43DFAA_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_443B00
	// Original code:	mov     cx, [esi+0Ch]
	static NAKED void patch_443B90()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_444810
	// Original code:	mov     ax, ds:MI_PICKUP_HEALTH
	static NAKED void patch_445049()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD5C8;	// MI_PICKUP_HEALTH
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_444810
	// Original code:	mov     ax, ds:MI_PICKUP_BODYARMOUR
	static NAKED void patch_445051()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD5C0;	// MI_PICKUP_BODYARMOUR
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_444810
	// Original code:	movzx   edx, ds:MI_PICKUP_BODYARMOUR
	static NAKED void patch_445064()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5C0;	// MI_PICKUP_BODYARMOUR
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_444810
	// Original code:	movzx   edx, ds:MI_PICKUP_HEALTH
	static NAKED void patch_445075()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5C8;	// MI_PICKUP_HEALTH
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4453D0
	// Original code:	mov     ax, ds:MI_PICKUP_HEALTH
	static NAKED void patch_445AD0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD5C8;	// MI_PICKUP_HEALTH
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4453D0
	// Original code:	mov     ax, ds:MI_PICKUP_BODYARMOUR
	static NAKED void patch_445AD8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD5C0;	// MI_PICKUP_BODYARMOUR
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_448EE0
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_448EE8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_449760
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_449766()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_44A4D0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_44A522()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_44AA50
	// Original code:	cmp     word ptr [eax+22h], 23Bh
	static NAKED void patch_44AADB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 571;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_44AA50
	// Original code:	cmp     word ptr [eax+22h], 23Bh
	static NAKED void patch_44AADB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 571;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_44AA50
	// Original code:	cmp     word ptr [edi+22h], 1A7h
	static NAKED void patch_44AB2A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 423;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_44AA50
	// Original code:	cmp     word ptr [edi+22h], 1A7h
	static NAKED void patch_44AB2A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 423;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_44AA50
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_44B110()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_453060
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_453169()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_453060
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_4531AA()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_453060
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_4531E0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_453060
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_45321C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_453370
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_453486()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_453370
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_4534C7()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_453370
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_4534FD()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_453370
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_453539()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_454245
	// Original code:	movsx   ebx, word ptr [eax+22h]
	static NAKED void patch_45426B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebx, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_454245
	// Original code:	movzx   ebp, ds:MI_PHONEBOOTH1
	static NAKED void patch_45426F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD560;	// MI_PHONEBOOTH1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_454AE0
	// Original code:	movzx   edx, ds:MI_PICKUP_HEALTH
	static NAKED void patch_454AEF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5C8;	// MI_PICKUP_HEALTH
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_454AE0
	// Original code:	movzx   ecx, ds:MI_PICKUP_ADRENALINE
	static NAKED void patch_454AFA()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5BC;	// MI_PICKUP_ADRENALINE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_454D20
	// Original code:	mov     ax, [esi+18h]
	static NAKED void patch_454D33()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 18h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_454D20
	// Original code:	cmp     ax, ds:MI_PICKUP_KILLFRENZY
	static NAKED void patch_454D37_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5D4;	// MI_PICKUP_KILLFRENZY
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_454D20
	// Original code:	cmp     ax, ds:MI_PICKUP_KILLFRENZY
	static NAKED void patch_454D37_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			mov eax, 0x8CD5D4;	// MI_PICKUP_KILLFRENZY
			movzx eax, word ptr[eax];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_454D20
	// Original code:	mov     cx, [esi+18h]
	static NAKED void patch_454D7F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 18h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_454D20
	// Original code:	cmp     cx, ds:MI_PICKUP_2P_KILLFRENZY
	static NAKED void patch_454D83_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			push 0x8CD5F4;	// MI_PICKUP_2P_KILLFRENZY
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_454D20
	// Original code:	cmp     cx, ds:MI_PICKUP_2P_KILLFRENZY
	static NAKED void patch_454D83_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			mov eax, 0x8CD5F4;	// MI_PICKUP_2P_KILLFRENZY
			movzx eax, word ptr[eax];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   ecx, ds:MI_PICKUP_CAMERA
	static NAKED void patch_455731()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5D8;	// MI_PICKUP_CAMERA
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_455738()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_455885()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   edx, ds:MI_PICKUP_ADRENALINE
	static NAKED void patch_455889()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5BC;	// MI_PICKUP_ADRENALINE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   ecx, ds:MI_PICKUP_BODYARMOUR
	static NAKED void patch_455898()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5C0;	// MI_PICKUP_BODYARMOUR
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   edx, ds:MI_PICKUP_BRIBE
	static NAKED void patch_4558B0()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5D0;	// MI_PICKUP_BRIBE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   ecx, ds:MI_PICKUP_INFO
	static NAKED void patch_4558BF()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5C4;	// MI_PICKUP_INFO
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   edx, ds:MI_PICKUP_KILLFRENZY
	static NAKED void patch_4558CA()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5D4;	// MI_PICKUP_KILLFRENZY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   ecx, ds:MI_PICKUP_HEALTH
	static NAKED void patch_4558D5()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5C8;	// MI_PICKUP_HEALTH
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   edx, ds:MI_PICKUP_BONUS
	static NAKED void patch_4558E0()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5CC;	// MI_PICKUP_BONUS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   ecx, ds:MI_PICKUP_PROPERTY
	static NAKED void patch_4558EB()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5E8;	// MI_PICKUP_PROPERTY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   edx, ds:MI_PICKUP_PROPERTY_FORSALE
	static NAKED void patch_4558F6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5EC;	// MI_PICKUP_PROPERTY_FORSALE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   ecx, ds:MI_PICKUP_REVENUE
	static NAKED void patch_455901()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5E0;	// MI_PICKUP_REVENUE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   edx, ds:MI_PICKUP_SAVEGAME
	static NAKED void patch_455916()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5E4;	// MI_PICKUP_SAVEGAME
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   ecx, ds:MI_PICKUP_CLOTHES
	static NAKED void patch_455921()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5F0;	// MI_PICKUP_CLOTHES
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_455AB8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   ecx, ds:MI_PICKUP_PROPERTY
	static NAKED void patch_455B49()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5E8;	// MI_PICKUP_PROPERTY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_455B59()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movzx   ecx, ds:MI_PICKUP_PROPERTY_FORSALE
	static NAKED void patch_455B9B()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5EC;	// MI_PICKUP_PROPERTY_FORSALE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_455C07()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	movsx   eax, cx
	static NAKED void patch_455C0B()
	{
		__asm
		{
			mov eax, ecx;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	cmp     cx, 362
	static NAKED void patch_455C8F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 362;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_455720
	// Original code:	cmp     cx, 362
	static NAKED void patch_455C8F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 362;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_ADRENALINE
	static NAKED void patch_45653A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			push 0x8CD5BC;	// MI_PICKUP_ADRENALINE
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_ADRENALINE
	static NAKED void patch_45653A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			mov eax, 0x8CD5BC;	// MI_PICKUP_ADRENALINE
			movzx eax, word ptr[eax];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_BODYARMOUR
	static NAKED void patch_45658D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			push 0x8CD5C0;	// MI_PICKUP_BODYARMOUR
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_BODYARMOUR
	static NAKED void patch_45658D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			mov eax, 0x8CD5C0;	// MI_PICKUP_BODYARMOUR
			movzx eax, word ptr[eax];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_INFO
	static NAKED void patch_4565D7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			push 0x8CD5C4;	// MI_PICKUP_INFO
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_INFO
	static NAKED void patch_4565D7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			mov eax, 0x8CD5C4;	// MI_PICKUP_INFO
			movzx eax, word ptr[eax];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_HEALTH
	static NAKED void patch_4565E4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			push 0x8CD5C8;	// MI_PICKUP_HEALTH
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_HEALTH
	static NAKED void patch_4565E4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			mov eax, 0x8CD5C8;	// MI_PICKUP_HEALTH
			movzx eax, word ptr[eax];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_BONUS
	static NAKED void patch_45664F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			push 0x8CD5CC;	// MI_PICKUP_BONUS
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_BONUS
	static NAKED void patch_45664F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			mov eax, 0x8CD5CC;	// MI_PICKUP_BONUS
			movzx eax, word ptr[eax];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_BRIBE
	static NAKED void patch_456658_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			push 0x8CD5D0;	// MI_PICKUP_BRIBE
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_BRIBE
	static NAKED void patch_456658_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			mov eax, 0x8CD5D0;	// MI_PICKUP_BRIBE
			movzx eax, word ptr[eax];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_KILLFRENZY
	static NAKED void patch_4566D5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			push 0x8CD5D4;	// MI_PICKUP_KILLFRENZY
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_PICKUP_KILLFRENZY
	static NAKED void patch_4566D5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			mov eax, 0x8CD5D4;	// MI_PICKUP_KILLFRENZY
			movzx eax, word ptr[eax];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, 370
	static NAKED void patch_4566DE_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 370;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, 370
	static NAKED void patch_4566DE_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 370;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_OYSTER
	static NAKED void patch_456783_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			push 0x8CD750;	// MI_OYSTER
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_OYSTER
	static NAKED void patch_456783_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			mov eax, 0x8CD750;	// MI_OYSTER
			movzx eax, word ptr[eax];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_HORSESHOE
	static NAKED void patch_4567A4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			push 0x8CD754;	// MI_HORSESHOE
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_401F0F
	// Original code:	cmp     cx, ds:MI_HORSESHOE
	static NAKED void patch_4567A4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			mov eax, 0x8CD754;	// MI_HORSESHOE
			movzx eax, word ptr[eax];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4567E0
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_4568C5()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4567E0
	// Original code:	movzx   edx, ds:MI_OYSTER
	static NAKED void patch_4568C9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD750;	// MI_OYSTER
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4567E0
	// Original code:	mov     ax, [edi+18h]
	static NAKED void patch_456997()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 18h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4567E0
	// Original code:	cmp     ax, ds:MI_PICKUP_BONUS
	static NAKED void patch_45699B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5CC;	// MI_PICKUP_BONUS
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4567E0
	// Original code:	cmp     ax, ds:MI_PICKUP_BONUS
	static NAKED void patch_45699B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			mov eax, 0x8CD5CC;	// MI_PICKUP_BONUS
			movzx eax, word ptr[eax];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4567E0
	// Original code:	cmp     ax, ds:MI_PICKUP_CLOTHES
	static NAKED void patch_4569B1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5F0;	// MI_PICKUP_CLOTHES
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4567E0
	// Original code:	cmp     ax, ds:MI_PICKUP_CLOTHES
	static NAKED void patch_4569B1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			mov eax, 0x8CD5F0;	// MI_PICKUP_CLOTHES
			movzx eax, word ptr[eax];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_457606()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   ecx, ds:MI_PICKUP_BRIBE
	static NAKED void patch_45760A()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5D0;	// MI_PICKUP_BRIBE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   ecx, ds:MI_PICKUP_CAMERA
	static NAKED void patch_4577AE()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5D8;	// MI_PICKUP_CAMERA
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   edx, ds:MI_PICKUP_SAVEGAME
	static NAKED void patch_4577C3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5E4;	// MI_PICKUP_SAVEGAME
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   ecx, ds:MI_PICKUP_2P_KILLFRENZY
	static NAKED void patch_4577CE()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5F4;	// MI_PICKUP_2P_KILLFRENZY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   edx, ds:MI_PICKUP_2P_COOP
	static NAKED void patch_4577D9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5F8;	// MI_PICKUP_2P_COOP
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	cmp     [edx+22h], bx
	static NAKED void patch_4579AC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	cmp     [edx+22h], bx
	static NAKED void patch_4579AC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ebx, bx;
			push ebx;
			movzx eax, word ptr[edx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_457A24()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movsx   edx, word ptr [edx+22h]
	static NAKED void patch_457A95()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movsx   ecx, word ptr [ecx+22h]
	static NAKED void patch_457BF1()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   edx, ds:MI_PICKUP_BODYARMOUR
	static NAKED void patch_457BF5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5C0;	// MI_PICKUP_BODYARMOUR
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   edx, ds:MI_PICKUP_HEALTH
	static NAKED void patch_457C39()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5C8;	// MI_PICKUP_HEALTH
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   edx, ds:MI_PICKUP_BRIBE
	static NAKED void patch_457C76()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5D0;	// MI_PICKUP_BRIBE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   edx, ds:MI_PICKUP_KILLFRENZY
	static NAKED void patch_457CE3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5D4;	// MI_PICKUP_KILLFRENZY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_457CEF()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	cmp     [eax+22h], bx
	static NAKED void patch_457D27_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	cmp     [eax+22h], bx
	static NAKED void patch_457D27_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ebx, bx;
			push ebx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_457D7C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   ecx, ds:MI_PICKUP_PROPERTY
	static NAKED void patch_457D80()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5E8;	// MI_PICKUP_PROPERTY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   edx, ds:MI_PICKUP_PROPERTY_FORSALE
	static NAKED void patch_457D8B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5EC;	// MI_PICKUP_PROPERTY_FORSALE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_457DB6()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	mov     cx, [eax+22h]
	static NAKED void patch_457DEC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_457EBC()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   eax, ds:MI_PICKUP_BRIBE
	static NAKED void patch_457EC0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD5D0;	// MI_PICKUP_BRIBE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_457EDD()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   ecx, ds:MI_PICKUP_CAMERA
	static NAKED void patch_457EE1()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5D8;	// MI_PICKUP_CAMERA
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	mov     dx, [ecx+22h]
	static NAKED void patch_457F8B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_458011()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_457410
	// Original code:	movzx   ecx, ds:MI_PICKUP_SAVEGAME
	static NAKED void patch_458015()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5E4;	// MI_PICKUP_SAVEGAME
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_458970
	// Original code:	movzx   edx, ds:MI_MONEY
	static NAKED void patch_458A3B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD59C;	// MI_MONEY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_45B4D0
	// Original code:	mov     dx, [edi+0Ch]
	static NAKED void patch_45B665()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_45B730
	// Original code:	mov     ax, [edi+22h]
	static NAKED void patch_45B8A9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_45B730
	// Original code:	cmp     word ptr [edi+22h], 1B0h
	static NAKED void patch_45B91A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_45B730
	// Original code:	cmp     word ptr [edi+22h], 1B0h
	static NAKED void patch_45B91A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_45BA90
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_45BC34_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_45BA90
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_45BC34_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_45E300
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_45E746()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_461170
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_46130F()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_461170
	// Original code:	add     eax, 0FFFFFE55h
	static NAKED void patch_461313()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4619C7
	// Original code:	movzx   edx, ds:MI_ROADBLOCKFUCKEDCAR1
	static NAKED void patch_46212D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD580;	// MI_ROADBLOCKFUCKEDCAR1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4619C7
	// Original code:	movzx   ebp, ds:MI_ROADWORKBARRIER1
	static NAKED void patch_4624EE()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD57C;	// MI_ROADWORKBARRIER1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_464F50
	// Original code:	add     ecx, 0FFFFFEE8h ; switch 8 cases 
	static NAKED void patch_464F56()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			mov ecx, eax;
			add esp, 4;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_465680
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_46579E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_469390
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_46963E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_46A760
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_46A76F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_46A930
	// Original code:	mov     [ecx+0Ch], dx
	static NAKED void patch_46A985()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [ecx + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_46B270
	// Original code:	movsx   ecx, word ptr [esi]
	static NAKED void patch_46B27D()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_46CD80
	// Original code:	movsx   eax, word ptr [edi+eax*4]
	static NAKED void patch_46CE3E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + eax * 4];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_46D050
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_46E094()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_46D050
	// Original code:	cmp     word ptr [esi+22h], 208h
	static NAKED void patch_46E434_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_46D050
	// Original code:	cmp     word ptr [esi+22h], 208h
	static NAKED void patch_46E434_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_46FF20
	// Original code:	mov     cx, [esi+0Ch]
	static NAKED void patch_46FF86()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_46FF20
	// Original code:	cmp     cx, [ebp+22h]
	static NAKED void patch_46FF8A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_472310
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_472D1F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_472310
	// Original code:	movzx   edx, ds:MI_HYDRAULICS
	static NAKED void patch_4732D6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD76C;	// MI_HYDRAULICS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_472310
	// Original code:	movzx   eax, ds:MI_HYDRAULICS
	static NAKED void patch_4732EA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD76C;	// MI_HYDRAULICS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_474900
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_474AA9()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_474D49
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_475D8D()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _opcode_handler_23
	// Original code:	movzx   edi, ds:MI_OYSTER
	static NAKED void patch_4778E6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD750;	// MI_OYSTER
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _opcode_handler_23
	// Original code:	movzx   edi, ds:MI_HORSESHOE
	static NAKED void patch_4778F4()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD754;	// MI_HORSESHOE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _opcode_handler_23
	// Original code:	movzx   edi, ds:MI_PICKUP_CAMERA
	static NAKED void patch_477902()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD5D8;	// MI_PICKUP_CAMERA
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_478000
	// Original code:	movsx   edx, word ptr [eax+0Ah]
	static NAKED void patch_478207()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_478000
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_478501()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_478000
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_47854E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_478000
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_47863E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_478000
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_4788D3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_478000
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_4789F9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_478000
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_4798B4()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_478000
	// Original code:	cmp     word ptr [edi+22h], 1AEh
	static NAKED void patch_479A35_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_478000
	// Original code:	cmp     word ptr [edi+22h], 1AEh
	static NAKED void patch_479A35_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_47A760
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_47AA31()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_47C100
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_47C142()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_47FA30
	// Original code:	cmp     word ptr [ecx+22h], 21Bh
	static NAKED void patch_47FA95_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_47FA30
	// Original code:	cmp     word ptr [ecx+22h], 21Bh
	static NAKED void patch_47FA95_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_47FA30
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_47FDBC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_47FA30
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_47FDF8()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_47FA30
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_47FE4E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_47FA30
	// Original code:	movzx   eax, ds:MI_MONEY
	static NAKED void patch_4805F2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD59C;	// MI_MONEY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_47FA30
	// Original code:	movzx   ecx, ds:MI_MONEY
	static NAKED void patch_480635()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD59C;	// MI_MONEY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_47FA30
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_480933()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_481300
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_48158D()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_481300
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_481E25()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_481300
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_48229B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_481300
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_48255C()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_481300
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_4829D2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_486B00
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_486B19()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_489500
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_489FD2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_48A320
	// Original code:	movzx   ecx, ds:MI_PICKUP_REVENUE
	static NAKED void patch_48B224()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5E0;	// MI_PICKUP_REVENUE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_48CDD0
	// Original code:	movzx   edx, ds:MI_PICKUP_PROPERTY
	static NAKED void patch_48CE94()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5E8;	// MI_PICKUP_PROPERTY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_48CDD0
	// Original code:	movzx   ecx, ds:MI_PICKUP_PROPERTY_FORSALE
	static NAKED void patch_48CF81()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5EC;	// MI_PICKUP_PROPERTY_FORSALE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_48CDD0
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_48D2EC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_48CDD0
	// Original code:	cmp     word ptr [eax+22h], 1AEh
	static NAKED void patch_48DA90_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_48CDD0
	// Original code:	cmp     word ptr [eax+22h], 1AEh
	static NAKED void patch_48DA90_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_490DB0
	// Original code:	mov     ax, [eax+22h]
	static NAKED void patch_4912CC()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_490DB0
	// Original code:	cmp     ax, 420
	static NAKED void patch_4912D0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 420;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_490DB0
	// Original code:	cmp     ax, 420
	static NAKED void patch_4912D0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 420;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_490DB0
	// Original code:	cmp     ax, 438
	static NAKED void patch_4912D6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 438;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_490DB0
	// Original code:	cmp     ax, 438
	static NAKED void patch_4912D6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 438;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_492E10
	// Original code:	movsx   eax, word ptr [ecx+eax*2+2D6h]
	static NAKED void patch_492E14()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + eax * 2 + 2D6h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_49485A
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_49485F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_496E00
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_49835A()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_496E00
	// Original code:	movsx   ecx, word ptr [edx+eax*2+2D6h]
	static NAKED void patch_49836A()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edx + eax * 2 + 2D6h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_496E00
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_4986F7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4998A0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_499A0C()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49B0E0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_49B0F5()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_49B3C0
	// Original code:	mov     ax, [ebx]
	static NAKED void patch_49B3E0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_49B3C0
	// Original code:	cmp     ax, 0FFFFh
	static NAKED void patch_49B3E3_1()
	{
		__asm
		{
			cmp eax, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: sub_49B3C0
	// Original code:	mov     cx, [edi]
	static NAKED void patch_49B3F4()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49B3C0
	// Original code:	mov     [ebx], cx
	static NAKED void patch_49B3F7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [ebx];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49B3C0
	// Original code:	mov     ax, [edi]
	static NAKED void patch_49B3FA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_49B3C0
	// Original code:	cmp     ax, 0FFFFh
	static NAKED void patch_49B3FD_1()
	{
		__asm
		{
			cmp eax, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: sub_49B3C0
	// Original code:	movsx   edx, ax
	static NAKED void patch_49B403()
	{
		__asm
		{
			mov edx, eax;
			retn;
		}
	}

	// Function: sub_49B3C0
	// Original code:	mov     ax, [edi]
	static NAKED void patch_49B435()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_49CCE0
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_49CCE4()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49D5A0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS
	static NAKED void patch_49D5A0()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD4F4;	// MI_TRAFFICLIGHTS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49D5A0
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_VERTICAL
	static NAKED void patch_49D5AF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD4F8;	// MI_TRAFFICLIGHTS_VERTICAL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49D5A0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_MIAMI
	static NAKED void patch_49D5BA()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD4FC;	// MI_TRAFFICLIGHTS_MIAMI
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49D5A0
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_VEGAS
	static NAKED void patch_49D5C5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD500;	// MI_TRAFFICLIGHTS_VEGAS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49D5A0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_TWOVERTICAL
	static NAKED void patch_49D5D0()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD504;	// MI_TRAFFICLIGHTS_TWOVERTICAL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49D5A0
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_3
	static NAKED void patch_49D5DB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD508;	// MI_TRAFFICLIGHTS_3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49D5A0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_4
	static NAKED void patch_49D5E6()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD50C;	// MI_TRAFFICLIGHTS_4
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49D5A0
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_GAY
	static NAKED void patch_49D5F1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD514;	// MI_TRAFFICLIGHTS_GAY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49D5A0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_5
	static NAKED void patch_49D5FC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD510;	// MI_TRAFFICLIGHTS_5
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49DAB0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_49DB06()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_49DAB0
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_3
	static NAKED void patch_49DB0A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD508;	// MI_TRAFFICLIGHTS_3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49DAB0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_4
	static NAKED void patch_49DB15()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD50C;	// MI_TRAFFICLIGHTS_4
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49DAB0
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_5
	static NAKED void patch_49DB20()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD510;	// MI_TRAFFICLIGHTS_5
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49DAB0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_GAY
	static NAKED void patch_49DB2B()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD514;	// MI_TRAFFICLIGHTS_GAY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49DAB0
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_MIAMI
	static NAKED void patch_49DB36()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD4FC;	// MI_TRAFFICLIGHTS_MIAMI
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49DAB0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_49DB79()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49DAB0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_49E018()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_49DAB0
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_4
	static NAKED void patch_49E01C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD50C;	// MI_TRAFFICLIGHTS_4
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49DAB0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_GAY
	static NAKED void patch_49E02B()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD514;	// MI_TRAFFICLIGHTS_GAY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49DAB0
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_5
	static NAKED void patch_49E03A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD510;	// MI_TRAFFICLIGHTS_5
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49DAB0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS
	static NAKED void patch_49E0E1()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD4F4;	// MI_TRAFFICLIGHTS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49FB30
	// Original code:	mov     al, [esi+22h]
	static NAKED void patch_49FBBC()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_49FB30
	// Original code:	mov     cl, [esi+22h]
	static NAKED void patch_49FBDE()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_49FF20
	// Original code:	mov     al, [esi+22h]
	static NAKED void patch_49FFC7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_49FF20
	// Original code:	mov     cl, [esi+22h]
	static NAKED void patch_49FFE9()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4A0170
	// Original code:	mov     al, [esi+22h]
	static NAKED void patch_4A0217()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4A0170
	// Original code:	mov     cl, [esi+22h]
	static NAKED void patch_4A0239()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4A03C0
	// Original code:	mov     al, [esi+22h]
	static NAKED void patch_4A0467()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4A03C0
	// Original code:	mov     cl, [esi+22h]
	static NAKED void patch_4A0489()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4A0610
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_4A0686()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4A0610
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_4A06B9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4A09C0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_4A0A36()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4A09C0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_4A0A69()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4AC840
	// Original code:	mov     [esi+0Ch], ax
	static NAKED void patch_4AC876()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4AC990
	// Original code:	mov     [esi+0Ch], ax
	static NAKED void patch_4AC9C5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4ACCF0
	// Original code:	mov     [esi+0Ch], ax
	static NAKED void patch_4ACD26()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4ACF00
	// Original code:	mov     [esi+0Ch], ax
	static NAKED void patch_4ACF36()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4AF460
	// Original code:	movsx   edx, word ptr [ecx+22h]
	static NAKED void patch_4AF464()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4AF4B0
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_4AF558()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B2580
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_4B25AB()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B2580
	// Original code:	movzx   ecx, ds:MI_ESCALATORSTEP
	static NAKED void patch_4B25AF()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD674;	// MI_ESCALATORSTEP
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4B2580
	// Original code:	movzx   edx, ds:MI_ESCALATORSTEP8
	static NAKED void patch_4B25BA()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD678;	// MI_ESCALATORSTEP8
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4B3120
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_4B3138()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B4950
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_4B49AF()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B6BC0
	// Original code:	mov     dx, [esi+0Ch]
	static NAKED void patch_4B6C0C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4B6C40
	// Original code:	movsx   ecx, word ptr [esi+32h]
	static NAKED void patch_4B6C74()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 32h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4B6C40
	// Original code:	movsx   edx, word ptr [esi+30h]
	static NAKED void patch_4B6C78()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 30h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4B6C40
	// Original code:	mov     cx, [esi+0Ch]
	static NAKED void patch_4B6C8F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4B6CC0
	// Original code:	movsx   ecx, word ptr [esi+0Eh]
	static NAKED void patch_4B6CF4()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4B6CC0
	// Original code:	mov     dx, [esi+0Ch]
	static NAKED void patch_4B6D0A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4B6D40
	// Original code:	movsx   ecx, word ptr [esi+0Eh]
	static NAKED void patch_4B6D74()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4B6D40
	// Original code:	mov     dx, [esi+0Ch]
	static NAKED void patch_4B6D8A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4B7EF0
	// Original code:	movsx   eax, word ptr [ecx+10h]
	static NAKED void patch_4B7EF0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 10h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B7F80
	// Original code:	movsx   eax, word ptr [ecx+30h]
	static NAKED void patch_4B7F80()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 30h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B7FA0
	// Original code:	movsx   eax, word ptr [ecx+32h]
	static NAKED void patch_4B7FA0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 32h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B7FC0
	// Original code:	movsx   eax, word ptr [ecx+0Eh]
	static NAKED void patch_4B7FC0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B7FF0
	// Original code:	movsx   eax, word ptr [ecx+0Eh]
	static NAKED void patch_4B7FF0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B8CE0
	// Original code:	movsx   ebx, word ptr [edi+30h]
	static NAKED void patch_4B8D97()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 30h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebx, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4B8CE0
	// Original code:	movsx   edi, word ptr [edi+32h]
	static NAKED void patch_4B8D9B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 32h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4B92B0
	// Original code:	movsx   edi, word ptr [ecx+0Eh]
	static NAKED void patch_4B92E4()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4B9470
	// Original code:	movsx   eax, word ptr [ebx+0Eh]
	static NAKED void patch_4B95CC()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B99F0
	// Original code:	movsx   eax, word ptr [eax+0Eh]
	static NAKED void patch_4B9A14()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B9BE0
	// Original code:	movsx   eax, word ptr [esi+0Eh]
	static NAKED void patch_4B9C15()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B9C90
	// Original code:	movsx   eax, word ptr [eax+0Eh]
	static NAKED void patch_4B9CB8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B9D40
	// Original code:	movsx   eax, word ptr [esi+0Eh]
	static NAKED void patch_4B9D6A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4B9DD0
	// Original code:	movsx   eax, word ptr [esi+0Eh]
	static NAKED void patch_4B9DEA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4BA990
	// Original code:	movsx   eax, word ptr [eax+0Eh]
	static NAKED void patch_4BA9A9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4BAA30
	// Original code:	movsx   eax, word ptr [eax+0Eh]
	static NAKED void patch_4BAA49()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4BAAD0
	// Original code:	movsx   eax, word ptr [eax+0Eh]
	static NAKED void patch_4BAAE9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4BAC10
	// Original code:	movsx   eax, word ptr [eax+0Eh]
	static NAKED void patch_4BAC29()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4BB2E0
	// Original code:	movsx   eax, word ptr [ecx+0Eh]
	static NAKED void patch_4BB3A1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4BB800
	// Original code:	movsx   eax, word ptr [eax+0Eh]
	static NAKED void patch_4BB819()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4BBCD0
	// Original code:	movsx   eax, word ptr [esi+0Eh]
	static NAKED void patch_4BBD18()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4BBE30
	// Original code:	movsx   edi, word ptr [ecx+0Eh]
	static NAKED void patch_4BBE50()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4BBFB0
	// Original code:	movsx   eax, word ptr [eax+0Eh]
	static NAKED void patch_4BBFC9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4BC050
	// Original code:	movsx   ecx, word ptr [eax+0Eh]
	static NAKED void patch_4BC072()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4BC230
	// Original code:	movsx   eax, word ptr [eax+0Eh]
	static NAKED void patch_4BC258()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4BC600
	// Original code:	movsx   ecx, word ptr [ebp+10h]
	static NAKED void patch_4BC6DE()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebp + 10h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4BC710
	// Original code:	movsx   eax, word ptr [ebx+0Eh]
	static NAKED void patch_4BC73C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4BCC30
	// Original code:	movsx   edi, word ptr [esi+0Eh]
	static NAKED void patch_4BCCF8()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4BDB80
	// Original code:	movsx   eax, word ptr [ebx+30h]
	static NAKED void patch_4BDC46()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 30h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4BDB80
	// Original code:	movsx   ebx, word ptr [ebx+32h]
	static NAKED void patch_4BDC4A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ebx + 32h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebx, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4BE7D0
	// Original code:	movsx   esi, word ptr [ebp+30h]
	static NAKED void patch_4BE891()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ebp + 30h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4BF2B0
	// Original code:	movsx   eax, word ptr [esi+0Eh]
	static NAKED void patch_4BF307()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4BF9B0
	// Original code:	movsx   eax, word ptr [edi+0Eh]
	static NAKED void patch_4BF9CC()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C0170
	// Original code:	movsx   eax, word ptr [ecx+2Ch]
	static NAKED void patch_4C0925()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C0170
	// Original code:	movsx   ecx, word ptr [ecx+0Eh]
	static NAKED void patch_4C0929()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ecx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4C0BD0
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_4C0C0F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4C1590
	// Original code:	movsx   eax, word ptr [ebx+0Eh]
	static NAKED void patch_4C1674()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C19A0
	// Original code:	movsx   eax, word ptr [edi+0Eh]
	static NAKED void patch_4C19CF()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C2610
	// Original code:	movsx   eax, word ptr [edi+0Eh]
	static NAKED void patch_4C2663()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C2840
	// Original code:	movsx   eax, word ptr [ebx+0Eh]
	static NAKED void patch_4C2975()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C2FC0
	// Original code:	movsx   eax, word ptr [edi+0Eh]
	static NAKED void patch_4C2FFD()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C3430
	// Original code:	movsx   eax, word ptr [ecx+0Eh]
	static NAKED void patch_4C3459()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C35F0
	// Original code:	movsx   eax, word ptr [edi+0Eh]
	static NAKED void patch_4C364E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C47E0
	// Original code:	mov     [ebp+2], di
	static NAKED void patch_4C488E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edi;
			lea eax, [ebp + 2];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4C4A30
	// Original code:	movsx   eax, word ptr [ecx+2]
	static NAKED void patch_4C4A30()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 2];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C4A60
	// Original code:	mov     word ptr [eax+0Ah], 0FFFFh
	static NAKED void patch_4C4A6E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push UNDEFINED_FILE_ID_INT32;
			lea eax, [eax + 0Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4C4B10
	// Original code:	mov     [ecx+0Ah], dx
	static NAKED void patch_4C4B19()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [ecx + 0Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN14CBaseModelInfo16SetTexDictionaryEPKcS1_
	// Original code:	cmp     ax, 0FFFFh
	static NAKED void patch_4C4B51_1()
	{
		__asm
		{
			cmp eax, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: _ZN14CBaseModelInfo16SetTexDictionaryEPKcS1_
	// Original code:	mov     [esi+0Ah], ax
	static NAKED void patch_4C4B55()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 0Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4C4B80
	// Original code:	movsx   eax, word ptr [ecx+0Ah]
	static NAKED void patch_4C4B80()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C4B90
	// Original code:	movsx   eax, word ptr [ecx+0Ah]
	static NAKED void patch_4C4B90()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C4BA0
	// Original code:	movsx   eax, word ptr [ecx+0Ah]
	static NAKED void patch_4C4BA0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C4BB0
	// Original code:	movsx   eax, word ptr [ecx+0Ah]
	static NAKED void patch_4C4BB0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN14CBaseModelInfo11SetColModelEP9CColModelb
	// Original code:	movsx   eax, word ptr [eax+2]
	static NAKED void patch_4C4BE4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 2];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4C4D50
	// Original code:	mov     [esi+0Ah], ax
	static NAKED void patch_4C4D92()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 0Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4C8500
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_4C85D2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4C86B0
	// Original code:	cmp     word ptr [ecx], 0FFFFh
	static NAKED void patch_4C86B8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			cmp eax, UNDEFINED_FILE_ID_INT32;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4C86B0
	// Original code:	cmp     word ptr [ecx], 0FFFFh
	static NAKED void patch_4C86C9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			cmp eax, UNDEFINED_FILE_ID_INT32;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4C86D0
	// Original code:	cmp     word ptr [edx], 0FFFFh
	static NAKED void patch_4C86D8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edx];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			cmp eax, UNDEFINED_FILE_ID_INT32;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4C86D0
	// Original code:	cmp     word ptr [edx], 0FFFFh
	static NAKED void patch_4C86E9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edx];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			cmp eax, UNDEFINED_FILE_ID_INT32;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4C86D0
	// Original code:	mov     [ecx+eax*2+2FAh], dx
	static NAKED void patch_4C86F4()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [ecx + eax * 2 + 2FAh];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4CE220
	// Original code:	mov     cx, [esi+0Ch]
	static NAKED void patch_4CE351()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4CE3B0
	// Original code:	mov     cx, [esi+0Ch]
	static NAKED void patch_4CE560()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4CE5C0
	// Original code:	mov     dx, [esi+0Ch]
	static NAKED void patch_4CE68D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4CE6E0
	// Original code:	mov     cx, [esi+0Ch]
	static NAKED void patch_4CE7AC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4CE940
	// Original code:	mov     [eax+0Ah], cx
	static NAKED void patch_4CE955()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [eax + 0Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4CEE40
	// Original code:	mov     cx, [ebp+0Ch]
	static NAKED void patch_4CEE4E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebp + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4CEE40
	// Original code:	mov     [ebx+0Ch], cx
	static NAKED void patch_4CEE52()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [ebx + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4CEEC0
	// Original code:	mov     [esi+0Ch], cx
	static NAKED void patch_4CEED2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [esi + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4CEEC0
	// Original code:	mov     dx, [edi+0Ah]
	static NAKED void patch_4CEED6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4CEF60
	// Original code:	mov     [esi+0Ah], ax
	static NAKED void patch_4CEF74()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 0Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4CFB70
	// Original code:	mov     [ecx+0Ah], ax
	static NAKED void patch_4CFB7E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [ecx + 0Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_506ED0
	// Original code:	mov     ax, [ebx+22h]
	static NAKED void patch_4DAB71()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_506ED0
	// Original code:	cmp     ax, 344
	static NAKED void patch_4DAB75_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 344;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_506ED0
	// Original code:	cmp     ax, 344
	static NAKED void patch_4DAB75_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 344;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_506ED0
	// Original code:	movzx   ecx, ds:MI_GRASSHOUSE
	static NAKED void patch_4DAB82()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6F4;	// MI_GRASSHOUSE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_4DBB40()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	cmp     ax, 344
	static NAKED void patch_4DBB44_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 344;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	cmp     ax, 344
	static NAKED void patch_4DBB44_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 344;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	cmp     ax, 363
	static NAKED void patch_4DBB5F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 363;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	cmp     ax, 363
	static NAKED void patch_4DBB5F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 363;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	cmp     ax, 342
	static NAKED void patch_4DBB7A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 342;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	cmp     ax, 342
	static NAKED void patch_4DBB7A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 342;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	cmp     ax, 364
	static NAKED void patch_4DBB84_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 364;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	cmp     ax, 364
	static NAKED void patch_4DBB84_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 364;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	cmp     ax, 343
	static NAKED void patch_4DBB8E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 343;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	cmp     ax, 343
	static NAKED void patch_4DBB8E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 343;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	movzx   edx, ds:MI_BASKETBALL
	static NAKED void patch_4DBB98()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD774;	// MI_BASKETBALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	movzx   ecx, ds:MI_PUNCHBAG
	static NAKED void patch_4DBBB8()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD77C;	// MI_PUNCHBAG
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	movzx   edx, ds:MI_GRASSHOUSE
	static NAKED void patch_4DBBD2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6F4;	// MI_GRASSHOUSE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_506EB0
	// Original code:	movzx   ecx, ds:MI_IMY_GRAY_CRATE
	static NAKED void patch_4DBBEC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD780;	// MI_IMY_GRAY_CRATE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4E3350
	// Original code:	mov     [ecx+0Ch], dx
	static NAKED void patch_4E335E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [ecx + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4E68D0
	// Original code:	movsx   edi, word ptr [ecx+22h]
	static NAKED void patch_4E692E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4F51F0
	// Original code:	cmp     word ptr [eax+22h], 1C9h
	static NAKED void patch_4F51F6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F51F0
	// Original code:	cmp     word ptr [eax+22h], 1C9h
	static NAKED void patch_4F51F6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F5310
	// Original code:	cmp     word ptr [eax+22h], 1C9h
	static NAKED void patch_4F5316_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F5310
	// Original code:	cmp     word ptr [eax+22h], 1C9h
	static NAKED void patch_4F5316_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F55C0
	// Original code:	mov     [esi+14Ah], ax
	static NAKED void patch_4F5645()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 14Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4F5700
	// Original code:	mov     [esi+14Ah], di
	static NAKED void patch_4F5A1B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edi;
			lea eax, [esi + 14Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4F5C40
	// Original code:	mov     ax, [eax+22h]
	static NAKED void patch_4F5C43()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4F5C40
	// Original code:	cmp     ax, 487
	static NAKED void patch_4F5C47_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 487;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F5C40
	// Original code:	cmp     ax, 487
	static NAKED void patch_4F5C47_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 487;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F5C40
	// Original code:	cmp     ax, 488
	static NAKED void patch_4F5C4D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 488;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F5C40
	// Original code:	cmp     ax, 488
	static NAKED void patch_4F5C4D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 488;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F5D00
	// Original code:	cmp     word ptr [edx+22h], 1C9h
	static NAKED void patch_4F5D35_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F5D00
	// Original code:	cmp     word ptr [edx+22h], 1C9h
	static NAKED void patch_4F5D35_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F62A0
	// Original code:	cmp     word ptr [eax+22h], 1A7h
	static NAKED void patch_4F62E4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 423;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F62A0
	// Original code:	cmp     word ptr [eax+22h], 1A7h
	static NAKED void patch_4F62E4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 423;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F7670
	// Original code:	mov     [ebp+14Ah], si
	static NAKED void patch_4F76FC()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push esi;
			lea eax, [ebp + 14Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4F7670
	// Original code:	mov     ax, [edx+22h]
	static NAKED void patch_4F77B4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4F7670
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_4F7814()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4F7670
	// Original code:	add     eax, 0FFFFFE40h ; switch 136 cases 
	static NAKED void patch_4F7818()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4F8070
	// Original code:	cmp     word ptr [edx+22h], 1C9h
	static NAKED void patch_4F8213_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F8070
	// Original code:	cmp     word ptr [edx+22h], 1C9h
	static NAKED void patch_4F8213_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F8940
	// Original code:	cmp     word ptr [ecx+22h], 1C9h
	static NAKED void patch_4F8972_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F8940
	// Original code:	cmp     word ptr [ecx+22h], 1C9h
	static NAKED void patch_4F8972_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F8B00
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_4F8B47()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4F8B00
	// Original code:	add     eax, 0FFFFFE4Dh
	static NAKED void patch_4F8B4B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4F99D0
	// Original code:	cmp     word ptr [ecx+22h], 1A7h
	static NAKED void patch_4F9CBC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 423;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4F99D0
	// Original code:	cmp     word ptr [ecx+22h], 1A7h
	static NAKED void patch_4F9CBC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 423;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	mov     ax, [ecx+22h]
	static NAKED void patch_4FB26B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	cmp     ax, 443
	static NAKED void patch_4FB26F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	cmp     ax, 443
	static NAKED void patch_4FB26F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	cmp     ax, 486
	static NAKED void patch_4FB275_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	cmp     ax, 486
	static NAKED void patch_4FB275_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	cmp     ax, 406
	static NAKED void patch_4FB27B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	cmp     ax, 406
	static NAKED void patch_4FB27B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	cmp     ax, 524
	static NAKED void patch_4FB281_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	cmp     ax, 524
	static NAKED void patch_4FB281_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	cmp     ax, 592
	static NAKED void patch_4FB287_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	cmp     ax, 592
	static NAKED void patch_4FB287_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	cmp     ax, 530
	static NAKED void patch_4FB28D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	cmp     ax, 530
	static NAKED void patch_4FB28D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_4FB343()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4FB260
	// Original code:	add     eax, 0FFFFFE6Ah
	static NAKED void patch_4FB347()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4FB6C0
	// Original code:	mov     [esi+14Ah], cx
	static NAKED void patch_4FB864()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [esi + 14Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4FF900
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_4FF980()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4FF900
	// Original code:	add     eax, 0FFFFFDF9h
	static NAKED void patch_4FF984()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_501650
	// Original code:	movsx   eax, word ptr [esi+0B4h]
	static NAKED void patch_5018C7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 0B4h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_501AB0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_501AB9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_501AB0
	// Original code:	add     eax, 0FFFFFE4Dh
	static NAKED void patch_501ABD()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_501C50
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_501C73()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_501C50
	// Original code:	add     eax, 0FFFFFDF9h
	static NAKED void patch_501C77()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_501E10
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_501E82()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_501E10
	// Original code:	cmp     word ptr [eax+22h], 214h
	static NAKED void patch_502222_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_501E10
	// Original code:	cmp     word ptr [eax+22h], 214h
	static NAKED void patch_502222_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   edx, ds:MI_SINGLESTREETLIGHTS2
	static NAKED void patch_509A43()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD51C;	// MI_SINGLESTREETLIGHTS2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   ecx, ds:MI_SINGLESTREETLIGHTS3
	static NAKED void patch_509A52()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD520;	// MI_SINGLESTREETLIGHTS3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   edx, ds:MI_BOLLARDLIGHT
	static NAKED void patch_509A5D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5FC;	// MI_BOLLARDLIGHT
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   ecx, ds:MI_MLAMPPOST
	static NAKED void patch_509A68()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD614;	// MI_MLAMPPOST
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   edx, ds:MI_STREETLAMP1
	static NAKED void patch_509A73()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD528;	// MI_STREETLAMP1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   ecx, ds:MI_STREETLAMP2
	static NAKED void patch_509A7E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD52C;	// MI_STREETLAMP2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   edx, ds:MI_TELPOLE02
	static NAKED void patch_509A89()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD620;	// MI_TELPOLE02
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_MIAMI
	static NAKED void patch_509A94()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD4FC;	// MI_TRAFFICLIGHTS_MIAMI
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_TWOVERTICAL
	static NAKED void patch_509A9F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD504;	// MI_TRAFFICLIGHTS_TWOVERTICAL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_3
	static NAKED void patch_509AAA()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD508;	// MI_TRAFFICLIGHTS_3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_4
	static NAKED void patch_509AB5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD50C;	// MI_TRAFFICLIGHTS_4
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_GAY
	static NAKED void patch_509AC0()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD514;	// MI_TRAFFICLIGHTS_GAY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_509A30
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_5
	static NAKED void patch_509ACB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD510;	// MI_TRAFFICLIGHTS_5
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_50A480
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_50A48B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_50A480
	// Original code:	movsx   ebx, word ptr [edi+22h]
	static NAKED void patch_50A4A8()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebx, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_50D590
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_50D597()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_512110
	// Original code:	cmp     word ptr [ecx+22h], 1AEh
	static NAKED void patch_512570_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_512110
	// Original code:	cmp     word ptr [ecx+22h], 1AEh
	static NAKED void patch_512570_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_513510
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_51359A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_513510
	// Original code:	movsx   edx, word ptr [ebp+22h]
	static NAKED void patch_51362C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_514B80
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_514C7C()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5161A0
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_516240()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_516B20
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_516E0A()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_517130
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_5172EE()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_517EA0
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_5180EB()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_51B126
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_51B316()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_51B850
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_51BB37()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_51B850
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_51BBB7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_51B850
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_51BE02()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_51D100
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_51D22B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_409B61
	// Original code:	cmp     word ptr [edx+22h], 1CCh
	static NAKED void patch_51D864_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_409B61
	// Original code:	cmp     word ptr [edx+22h], 1CCh
	static NAKED void patch_51D864_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_409B61
	// Original code:	cmp     word ptr [eax+22h], 1B0h
	static NAKED void patch_51D870_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_409B61
	// Original code:	cmp     word ptr [eax+22h], 1B0h
	static NAKED void patch_51D870_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_409B61
	// Original code:	cmp     word ptr [edx+22h], 1CCh
	static NAKED void patch_51D92B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_409B61
	// Original code:	cmp     word ptr [edx+22h], 1CCh
	static NAKED void patch_51D92B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_409B61
	// Original code:	cmp     word ptr [ecx+22h], 1CCh
	static NAKED void patch_51DA60_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_409B61
	// Original code:	cmp     word ptr [ecx+22h], 1CCh
	static NAKED void patch_51DA60_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_409B61
	// Original code:	cmp     word ptr [eax+22h], 1CCh
	static NAKED void patch_51DCFC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_409B61
	// Original code:	cmp     word ptr [eax+22h], 1CCh
	static NAKED void patch_51DCFC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_409B61
	// Original code:	cmp     word ptr [eax+22h], 1CCh
	static NAKED void patch_51DE84_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_409B61
	// Original code:	cmp     word ptr [eax+22h], 1CCh
	static NAKED void patch_51DE84_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4014E2
	// Original code:	cmp     word ptr [eax+22h], 1CCh
	static NAKED void patch_51E5AC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4014E2
	// Original code:	cmp     word ptr [eax+22h], 1CCh
	static NAKED void patch_51E5AC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4014E2
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_51E5B8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4014E2
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_51E5B8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4014E2
	// Original code:	cmp     word ptr [ecx+22h], 1CCh
	static NAKED void patch_51E773_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4014E2
	// Original code:	cmp     word ptr [ecx+22h], 1CCh
	static NAKED void patch_51E773_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4014E2
	// Original code:	cmp     word ptr [eax+22h], 1CCh
	static NAKED void patch_51E937_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4014E2
	// Original code:	cmp     word ptr [eax+22h], 1CCh
	static NAKED void patch_51E937_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4014E2
	// Original code:	cmp     word ptr [edx+22h], 1CCh
	static NAKED void patch_51EF39_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4014E2
	// Original code:	cmp     word ptr [edx+22h], 1CCh
	static NAKED void patch_51EF39_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4014E2
	// Original code:	cmp     word ptr [ecx+22h], 1CCh
	static NAKED void patch_51F15B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4014E2
	// Original code:	cmp     word ptr [ecx+22h], 1CCh
	static NAKED void patch_51F15B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_520190
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_520225()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_520190
	// Original code:	movsx   edx, word ptr [eax]
	static NAKED void patch_520249()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_520190
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_520282()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_520190
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_52034B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	mov     ax, [edi+22h]
	static NAKED void patch_524624()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 1B9h
	static NAKED void patch_524628_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 1B9h
	static NAKED void patch_524628_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 464
	static NAKED void patch_524632_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 464
	static NAKED void patch_524632_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 564
	static NAKED void patch_52463C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 564
	static NAKED void patch_52463C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 252h
	static NAKED void patch_524642_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 594;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 252h
	static NAKED void patch_524642_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 594;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 1D1h
	static NAKED void patch_524648_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 1D1h
	static NAKED void patch_524648_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 1F5h
	static NAKED void patch_52464E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 1F5h
	static NAKED void patch_52464E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 208h
	static NAKED void patch_524679_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 208h
	static NAKED void patch_524679_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 21Bh
	static NAKED void patch_52469A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 21Bh
	static NAKED void patch_52469A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	mov     ax, [edi+22h]
	static NAKED void patch_525462()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 443
	static NAKED void patch_525466_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 443
	static NAKED void patch_525466_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 486
	static NAKED void patch_5254C0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 486
	static NAKED void patch_5254C0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 406
	static NAKED void patch_5254C6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 406
	static NAKED void patch_5254C6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 524
	static NAKED void patch_5254CC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 524
	static NAKED void patch_5254CC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 592
	static NAKED void patch_5254D2_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 592
	static NAKED void patch_5254D2_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 520
	static NAKED void patch_5254D8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 520
	static NAKED void patch_5254D8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 525
	static NAKED void patch_5254DE_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 525
	static NAKED void patch_5254DE_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 530
	static NAKED void patch_5254E4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 530
	static NAKED void patch_5254E4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 531
	static NAKED void patch_5254EA_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 531
	static NAKED void patch_5254EA_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 564
	static NAKED void patch_5254F0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5245BD
	// Original code:	cmp     ax, 564
	static NAKED void patch_5254F0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_526FC0
	// Original code:	cmp     word ptr [eax+22h], 208h
	static NAKED void patch_527058_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_526FC0
	// Original code:	cmp     word ptr [eax+22h], 208h
	static NAKED void patch_527058_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_527FA0
	// Original code:	cmp     word ptr [ecx+22h], 1CCh
	static NAKED void patch_528294_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_527FA0
	// Original code:	cmp     word ptr [ecx+22h], 1CCh
	static NAKED void patch_528294_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_527FA0
	// Original code:	mov     bp, [eax+0Ah]
	static NAKED void patch_52852B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_527FA0
	// Original code:	mov     bp, [ebp+0Ah]
	static NAKED void patch_52939C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ebp + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_527FA0
	// Original code:	mov     bp, [ecx+0Ah]
	static NAKED void patch_529705()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_527FA0
	// Original code:	cmp     word ptr [eax+22h], 1A7h
	static NAKED void patch_52AE34_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 423;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_527FA0
	// Original code:	cmp     word ptr [eax+22h], 1A7h
	static NAKED void patch_52AE34_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 423;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_532A50
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_532A54()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532A90
	// Original code:	mov     word ptr [esi+22h], 0FFFFh
	static NAKED void patch_532AB0()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push UNDEFINED_FILE_ID_INT32;
			lea eax, [esi + 22h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	mov     si, [edi+22h]
	static NAKED void patch_532B74()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movsx   eax, si
	static NAKED void patch_532B78()
	{
		__asm
		{
			mov eax, esi;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   edx, ds:MI_COLLECTABLE1
	static NAKED void patch_532BB9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD598;	// MI_COLLECTABLE1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   ecx, ds:MI_MONEY
	static NAKED void patch_532BC8()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD59C;	// MI_MONEY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   edx, ds:MI_CARMINE
	static NAKED void patch_532BD7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5A0;	// MI_CARMINE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   ecx, ds:MI_NAUTICALMINE
	static NAKED void patch_532BE6()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5A4;	// MI_NAUTICALMINE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   edx, ds:MI_BRIEFCASE
	static NAKED void patch_532BF5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5AC;	// MI_BRIEFCASE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	cmp     si, 345
	static NAKED void patch_532C04_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push esi;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 345;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	cmp     si, 345
	static NAKED void patch_532C04_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, si;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 345;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	cmp     si, 342
	static NAKED void patch_532C0F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push esi;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 342;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	cmp     si, 342
	static NAKED void patch_532C0F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, si;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 342;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	cmp     si, 344
	static NAKED void patch_532C1A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push esi;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 344;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	cmp     si, 344
	static NAKED void patch_532C1A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, si;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 344;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   ecx, ds:MI_BEACHBALL
	static NAKED void patch_532C25()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD638;	// MI_BEACHBALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   edx, ds:MI_MAGNOCRANE_HOOK
	static NAKED void patch_532C34()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6E0;	// MI_MAGNOCRANE_HOOK
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   ecx, ds:MI_WRECKING_BALL
	static NAKED void patch_532C43()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD71C;	// MI_WRECKING_BALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   edx, ds:MI_CRANE_MAGNET
	static NAKED void patch_532C52()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD700;	// MI_CRANE_MAGNET
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   ecx, ds:MI_MINI_MAGNET
	static NAKED void patch_532C61()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD740;	// MI_MINI_MAGNET
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   edx, ds:MI_CRANE_HARNESS
	static NAKED void patch_532C70()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6FC;	// MI_CRANE_HARNESS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   ecx, ds:MI_WINDSOCK
	static NAKED void patch_532C7F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD718;	// MI_WINDSOCK
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   edx, ds:MI_FLARE
	static NAKED void patch_532C8E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD75C;	// MI_FLARE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_532CC0()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_532CD1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   edx, ds:MI_SINGLESTREETLIGHTS1
	static NAKED void patch_532CD5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD518;	// MI_SINGLESTREETLIGHTS1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   ecx, ds:MI_SINGLESTREETLIGHTS2
	static NAKED void patch_532CE0()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD51C;	// MI_SINGLESTREETLIGHTS2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   edx, ds:MI_SINGLESTREETLIGHTS3
	static NAKED void patch_532CEB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD520;	// MI_SINGLESTREETLIGHTS3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532B70
	// Original code:	movzx   ecx, ds:MI_DOUBLESTREETLIGHTS
	static NAKED void patch_532CF6()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD524;	// MI_DOUBLESTREETLIGHTS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_532D40
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_532D40()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_533150
	// Original code:	movsx   ecx, word ptr [ecx+22h]
	static NAKED void patch_53315E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_533240
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_533243()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_533380
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_533384()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_533410
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_533416()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_533700
	// Original code:	mov     [esi+22h], ax
	static NAKED void patch_53370F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 22h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_533790
	// Original code:	movsx   eax, word ptr [ebp+22h]
	static NAKED void patch_53379D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_533790
	// Original code:	mov     cx, [esi+24h]
	static NAKED void patch_53383E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_533790
	// Original code:	mov     dx, [esi+24h]
	static NAKED void patch_53384A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_533790
	// Original code:	mov     cx, [esi+24h]
	static NAKED void patch_533865()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_533790
	// Original code:	movsx   ecx, word ptr [esi+2Ch]
	static NAKED void patch_533A46()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CEntity14DestroyEffectsEv
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_533BF6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_533D30
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_533D41()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_533ED0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_533F2C()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_533ED0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_533F82()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_533FB0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_533FBA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_533FB0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_533FD4()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_534030
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_53409A()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_534030
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_5340D3()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: CEntity__GetBoundRect
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_534126()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_534250
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_534250()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_534290
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_534290()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5342B0
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_5342B6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CEntity6RenderEv
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_534340()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CEntity6RenderEv
	// Original code:	movzx   ecx, ds:MI_JELLYFISH
	static NAKED void patch_534344()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD644;	// MI_JELLYFISH
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CEntity6RenderEv
	// Original code:	movzx   edx, ds:MI_JELLYFISH01
	static NAKED void patch_534357()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD648;	// MI_JELLYFISH01
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CEntity6RenderEv
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5343B7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CEntity6RenderEv
	// Original code:	movzx   ecx, ds:MI_JELLYFISH
	static NAKED void patch_5343BB()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD644;	// MI_JELLYFISH
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CEntity6RenderEv
	// Original code:	movzx   edx, ds:MI_JELLYFISH01
	static NAKED void patch_5343C6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD648;	// MI_JELLYFISH01
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5343F0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5343F6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5343F0
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_534419()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5343F0
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_534437()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5343F0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_534442()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZNK7CEntity13GetIsTouchingERK7CVectorf
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5344B6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZNK7CEntity13GetIsTouchingERK7CVectorf
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_5344D4()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_534540
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_534546()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_534540
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_534564()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5345D0
	// Original code:	movsx   eax, word ptr [ebp+22h]
	static NAKED void patch_5345EE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_534E90
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_534FAF()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535300
	// Original code:	movsx   ecx, word ptr [ecx+22h]
	static NAKED void patch_535322()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535450
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5354C1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_535FAB()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_536174()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_COLLECTABLE1
	static NAKED void patch_536178()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD598;	// MI_COLLECTABLE1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movsx   eax, cx
	static NAKED void patch_53617F()
	{
		__asm
		{
			mov eax, ecx;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_MONEY
	static NAKED void patch_5361B2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD59C;	// MI_MONEY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_CARMINE
	static NAKED void patch_5361C8()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5A0;	// MI_CARMINE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_NAUTICALMINE
	static NAKED void patch_5361D7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5A4;	// MI_NAUTICALMINE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_BRIEFCASE
	static NAKED void patch_5361E6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD5AC;	// MI_BRIEFCASE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	cmp     cx, 345
	static NAKED void patch_5361F5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 345;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	cmp     cx, 345
	static NAKED void patch_5361F5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 345;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   ecx, ds:MI_FLARE
	static NAKED void patch_5363B5()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD75C;	// MI_FLARE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_53654B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	cmp     ax, 342
	static NAKED void patch_53654F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 342;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	cmp     ax, 342
	static NAKED void patch_53654F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 342;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	cmp     ax, 344
	static NAKED void patch_53662F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 344;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	cmp     ax, 344
	static NAKED void patch_53662F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 344;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_BEACHBALL
	static NAKED void patch_53678B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD638;	// MI_BEACHBALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   ecx, ds:MI_MAGNOCRANE_HOOK
	static NAKED void patch_536853()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6E0;	// MI_MAGNOCRANE_HOOK
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_WRECKING_BALL
	static NAKED void patch_53685E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD71C;	// MI_WRECKING_BALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   ecx, ds:MI_CRANE_MAGNET
	static NAKED void patch_536869()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD700;	// MI_CRANE_MAGNET
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_MINI_MAGNET
	static NAKED void patch_536874()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD740;	// MI_MINI_MAGNET
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   ecx, ds:MI_CRANE_HARNESS
	static NAKED void patch_53687F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6FC;	// MI_CRANE_HARNESS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_WINDSOCK
	static NAKED void patch_53688A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD718;	// MI_WINDSOCK
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_536977()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_VERTICAL
	static NAKED void patch_5369B8()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD4F8;	// MI_TRAFFICLIGHTS_VERTICAL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_MIAMI
	static NAKED void patch_5369C7()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD4FC;	// MI_TRAFFICLIGHTS_MIAMI
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_TWOVERTICAL
	static NAKED void patch_536A01()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD504;	// MI_TRAFFICLIGHTS_TWOVERTICAL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_3
	static NAKED void patch_536A3B()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD508;	// MI_TRAFFICLIGHTS_3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_4
	static NAKED void patch_536A46()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD50C;	// MI_TRAFFICLIGHTS_4
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_GAY
	static NAKED void patch_536A51()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD514;	// MI_TRAFFICLIGHTS_GAY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_5
	static NAKED void patch_536A5C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD510;	// MI_TRAFFICLIGHTS_5
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   ecx, ds:MI_SINGLESTREETLIGHTS1
	static NAKED void patch_536A7B()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD518;	// MI_SINGLESTREETLIGHTS1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_SINGLESTREETLIGHTS2
	static NAKED void patch_536AAF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD51C;	// MI_SINGLESTREETLIGHTS2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   ecx, ds:MI_SINGLESTREETLIGHTS3
	static NAKED void patch_536AE3()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD520;	// MI_SINGLESTREETLIGHTS3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   edx, ds:MI_DOUBLESTREETLIGHTS
	static NAKED void patch_536B1A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD524;	// MI_DOUBLESTREETLIGHTS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_535FA0
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_VEGAS
	static NAKED void patch_536B4E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD500;	// MI_TRAFFICLIGHTS_VEGAS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_536BE0
	// Original code:	movsx   ecx, word ptr [ecx+22h]
	static NAKED void patch_536C07()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5372D0
	// Original code:	cmp     ebp, 1FCh
	static NAKED void patch_5373CF_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebp;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 508;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5372D0
	// Original code:	cmp     ebp, 1FCh
	static NAKED void patch_5373CF_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebp;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 508;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_537A80
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_537A95()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_537A9A
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_537AA1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_537AB0
	// Original code:	movsx   eax, word ptr [eax+24h]
	static NAKED void patch_537AC5()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_537AB0
	// Original code:	movsx   eax, word ptr [eax+24h]
	static NAKED void patch_537AD1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_538090
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_538120()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_538090
	// Original code:	movzx   ecx, ds:MI_TRAINCROSSING
	static NAKED void patch_53835F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6B4;	// MI_TRAINCROSSING
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_538090
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_5383B7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_538440
	// Original code:	movsx   ecx, word ptr [ecx+24h]
	static NAKED void patch_538550()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ecx + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_538440
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_538554()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_53A570
	// Original code:	cmp     word ptr [eax+22h], 197h
	static NAKED void patch_53A637_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 407;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_53A570
	// Original code:	cmp     word ptr [eax+22h], 197h
	static NAKED void patch_53A637_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 407;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_53A570
	// Original code:	movsx   edx, word ptr [ecx+22h]
	static NAKED void patch_53A709()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_53A570
	// Original code:	cmp     word ptr [edi+22h], 197h
	static NAKED void patch_53A926_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 407;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_53A570
	// Original code:	cmp     word ptr [edi+22h], 197h
	static NAKED void patch_53A926_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 407;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_53C440
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_53C445()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN9CPhysical21SetDamagedPieceRecordEfP7CEntityR9CColPointf
	// Original code:	movsx   eax, word ptr [ebp+22h]
	static NAKED void patch_5429AB()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN9CPhysical21SetDamagedPieceRecordEfP7CEntityR9CColPointf
	// Original code:	movzx   ecx, ds:MI_POOL_CUE_BALL
	static NAKED void patch_5429AF()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD778;	// MI_POOL_CUE_BALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5449B0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_5449C0()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_546670
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_54667C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_546D00
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_546D24()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4067D8
	// Original code:	cmp     word ptr [ecx+22h], 212h
	static NAKED void patch_5470BF_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4067D8
	// Original code:	cmp     word ptr [ecx+22h], 212h
	static NAKED void patch_5470BF_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4067D8
	// Original code:	mov     cx, [edi+22h]
	static NAKED void patch_54742F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4067D8
	// Original code:	cmp     cx, 406
	static NAKED void patch_547433_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4067D8
	// Original code:	cmp     cx, 406
	static NAKED void patch_547433_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4067D8
	// Original code:	cmp     cx, 530
	static NAKED void patch_54743A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4067D8
	// Original code:	cmp     cx, 530
	static NAKED void patch_54743A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4067D8
	// Original code:	cmp     cx, 406
	static NAKED void patch_547497_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4067D8
	// Original code:	cmp     cx, 406
	static NAKED void patch_547497_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4067D8
	// Original code:	cmp     cx, 530
	static NAKED void patch_5474E4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4067D8
	// Original code:	cmp     cx, 530
	static NAKED void patch_5474E4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4067D8
	// Original code:	cmp     word ptr [esi+22h], 16Bh
	static NAKED void patch_54771D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 363;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4067D8
	// Original code:	cmp     word ptr [esi+22h], 16Bh
	static NAKED void patch_54771D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 363;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_547B80
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_547FD7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5483D0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5483E3()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_548680
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_548F45()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_548680
	// Original code:	movzx   ecx, ds:MI_FIRE_HYDRANT
	static NAKED void patch_548F49()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD594;	// MI_FIRE_HYDRANT
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_548680
	// Original code:	movzx   edx, ds:MI_PARKINGMETER
	static NAKED void patch_548F87()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD548;	// MI_PARKINGMETER
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_548680
	// Original code:	movzx   ecx, ds:MI_PARKINGMETER2
	static NAKED void patch_548F92()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD54C;	// MI_PARKINGMETER2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_54A2C6
	// Original code:	movsx   eax, word ptr [ebp+22h]
	static NAKED void patch_54A82B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_54A2C6
	// Original code:	movzx   ecx, ds:MI_FIRE_HYDRANT
	static NAKED void patch_54A82F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD594;	// MI_FIRE_HYDRANT
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_54A2C6
	// Original code:	movzx   edx, ds:MI_PARKINGMETER
	static NAKED void patch_54A92D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD548;	// MI_PARKINGMETER
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_54A2C6
	// Original code:	movzx   ecx, ds:MI_PARKINGMETER2
	static NAKED void patch_54A938()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD54C;	// MI_PARKINGMETER2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_54BA60
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_54BA91()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_54BA60
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_54C6BE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_54BA60
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_54C813()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_54BA60
	// Original code:	cmp     word ptr [esi+22h], 1B9h
	static NAKED void patch_54CB44_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_54BA60
	// Original code:	cmp     word ptr [esi+22h], 1B9h
	static NAKED void patch_54CB44_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_54CFF0
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_54D02C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_4022FC
	// Original code:	cmp     word ptr [edi+22h], 212h
	static NAKED void patch_54D70D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_4022FC
	// Original code:	cmp     word ptr [edi+22h], 212h
	static NAKED void patch_54D70D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_550080
	// Original code:	movsx   ecx, word ptr [ebx+22h]
	static NAKED void patch_55010F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_564360
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_5519C5()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5534B0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5534B5()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_553770
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_5537EC()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_553770
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_55381E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_553770
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_553891()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_553A10
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_553A60()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_553AA0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_553B10()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_554238()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_55432A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     ax, 432
	static NAKED void patch_55432E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     ax, 432
	static NAKED void patch_55432E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     ax, 437
	static NAKED void patch_554334_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 437;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     ax, 437
	static NAKED void patch_554334_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 437;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     ax, 453
	static NAKED void patch_554362_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 453;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     ax, 453
	static NAKED void patch_554362_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 453;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     ax, 454
	static NAKED void patch_554368_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 454;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     ax, 454
	static NAKED void patch_554368_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 454;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     ax, 430
	static NAKED void patch_55436E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     ax, 430
	static NAKED void patch_55436E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     ax, 460
	static NAKED void patch_554374_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     ax, 460
	static NAKED void patch_554374_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     word ptr [esi+22h], 0
	static NAKED void patch_5543A5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 0;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     word ptr [esi+22h], 0
	static NAKED void patch_5543A5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 0;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	movsx   ebx, word ptr [eax+2]
	static NAKED void patch_554443()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 2];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebx, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     word ptr [esi+22h], 0
	static NAKED void patch_5544F7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 0;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554230
	// Original code:	cmp     word ptr [esi+22h], 0
	static NAKED void patch_5544F7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 0;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_554650
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_55465E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_554650
	// Original code:	movsx   ebp, word ptr [eax+2]
	static NAKED void patch_554699()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 2];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_554840
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_554978()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_554840
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5549B9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_554840
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5549EF()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_554B10
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_554C15()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_554EB0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_554ED3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_554EB0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_554F32()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_555680
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5556C4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_556070
	// Original code:	movzx   ebp, ds:MI_CRANE_MAGNET; jumptable 005560B0 cases 0,3,5,6
	static NAKED void patch_5560B7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD700;	// MI_CRANE_MAGNET
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_556070
	// Original code:	movzx   ebp, ds:MI_CRANE_HARNESS; jumptable 005560B0 case 1
	static NAKED void patch_5560C0()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD6FC;	// MI_CRANE_HARNESS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_556070
	// Original code:	movzx   ebp, ds:MI_WRECKING_BALL; jumptable 005560B0 case 4
	static NAKED void patch_5560C9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD71C;	// MI_WRECKING_BALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_556070
	// Original code:	movzx   ebp, ds:MI_MINI_MAGNET; jumptable 005560B0 case 2
	static NAKED void patch_5560D2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD740;	// MI_MINI_MAGNET
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_556760
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_556764()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5569C0
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_5569F3()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_557659()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edx, ds:MI_OBJECTFORMAGNOCRANE1
	static NAKED void patch_55765D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6C8;	// MI_OBJECTFORMAGNOCRANE1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   ecx, ds:MI_OBJECTFORMAGNOCRANE2
	static NAKED void patch_557668()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6CC;	// MI_OBJECTFORMAGNOCRANE2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edx, ds:MI_OBJECTFORMAGNOCRANE3
	static NAKED void patch_557673()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6D0;	// MI_OBJECTFORMAGNOCRANE3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   ecx, ds:MI_OBJECTFORMAGNOCRANE5
	static NAKED void patch_55767E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6D8;	// MI_OBJECTFORMAGNOCRANE5
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	cmp     word ptr [esi+22h], 1ACh
	static NAKED void patch_557BDB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 428;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	cmp     word ptr [esi+22h], 1ACh
	static NAKED void patch_557BDB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 428;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_558160()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_5583B3()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	cmp     ax, 473
	static NAKED void patch_5583B7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 473;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	cmp     ax, 473
	static NAKED void patch_5583B7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 473;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	cmp     ax, 539
	static NAKED void patch_5583BD_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	cmp     ax, 539
	static NAKED void patch_5583BD_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	cmp     word ptr [esi+22h], 234h
	static NAKED void patch_5583E9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	cmp     word ptr [esi+22h], 234h
	static NAKED void patch_5583E9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_558402()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_5584C6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_558684()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5587D0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_OBJECTFORMAGNOCRANE1
	static NAKED void patch_5587D4()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD6C8;	// MI_OBJECTFORMAGNOCRANE1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_OBJECTFORMAGNOCRANE2
	static NAKED void patch_5587E3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD6CC;	// MI_OBJECTFORMAGNOCRANE2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_OBJECTFORMAGNOCRANE3
	static NAKED void patch_5587F2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD6D0;	// MI_OBJECTFORMAGNOCRANE3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_OBJECTFORMAGNOCRANE4
	static NAKED void patch_558801()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD6D4;	// MI_OBJECTFORMAGNOCRANE4
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_OBJECTFORMAGNOCRANE5
	static NAKED void patch_558810()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD6D8;	// MI_OBJECTFORMAGNOCRANE5
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_558827()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_OBJECTFORBUILDINGSITECRANE1
	static NAKED void patch_55882B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD6DC;	// MI_OBJECTFORBUILDINGSITECRANE1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_558842()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_QUARY_ROCK1
	static NAKED void patch_558846()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD704;	// MI_QUARY_ROCK1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_QUARY_ROCK2
	static NAKED void patch_558851()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD708;	// MI_QUARY_ROCK2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_QUARY_ROCK3
	static NAKED void patch_55885C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD70C;	// MI_QUARY_ROCK3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_DEAD_TIED_COP
	static NAKED void patch_558867()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD714;	// MI_DEAD_TIED_COP
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_558884()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_WONG_DISH
	static NAKED void patch_558888()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD724;	// MI_WONG_DISH
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_55889B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_KMB_ROCK
	static NAKED void patch_55889F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD734;	// MI_KMB_ROCK
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5588B2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_KMB_PLANK
	static NAKED void patch_5588B6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD738;	// MI_KMB_PLANK
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5588CD()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edi, ds:MI_KMB_BOMB
	static NAKED void patch_5588D1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD73C;	// MI_KMB_BOMB
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   ecx, ds:MI_OBJECTFORMAGNOCRANE1
	static NAKED void patch_558920()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6C8;	// MI_OBJECTFORMAGNOCRANE1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_55892B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edx, ds:MI_OBJECTFORMAGNOCRANE2
	static NAKED void patch_55893C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6CC;	// MI_OBJECTFORMAGNOCRANE2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   ecx, ds:MI_OBJECTFORMAGNOCRANE3
	static NAKED void patch_558947()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6D0;	// MI_OBJECTFORMAGNOCRANE3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movzx   edx, ds:MI_OBJECTFORMAGNOCRANE5
	static NAKED void patch_558952()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6D8;	// MI_OBJECTFORMAGNOCRANE5
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_5589D2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_558A5C()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_557530
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_558B4A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_55A785
	// Original code:	movsx   edi, word ptr [ebx]
	static NAKED void patch_55A81D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ebx];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_55BF20
	// Original code:	movsx   ecx, word ptr [ecx+22h]
	static NAKED void patch_55C00D()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5625F0
	// Original code:	cmp     word ptr [esi+22h], 1F1h
	static NAKED void patch_5626D1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 497;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5625F0
	// Original code:	cmp     word ptr [esi+22h], 1F1h
	static NAKED void patch_5626D1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 497;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5635C0
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_56360D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_563950
	// Original code:	mov     cx, [edx+22h]
	static NAKED void patch_563990()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5639D0
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_5639F2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_563F40
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_563F45()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_565000
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_565086()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5650E0
	// Original code:	movsx   esi, word ptr [edx+22h]
	static NAKED void patch_565126()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_565200
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_565262()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_565300
	// Original code:	movsx   esi, word ptr [ecx+22h]
	static NAKED void patch_56537A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_565450
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_565487()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_566147
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5662CE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_566420
	// Original code:	movsx   edi, word ptr [eax+22h]
	static NAKED void patch_566463()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_566510
	// Original code:	movsx   ecx, word ptr [ecx+22h]
	static NAKED void patch_56659F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_566510
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_5665CF()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_566EE0
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_567097()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_566EE0
	// Original code:	movsx   eax, word ptr [ebp+0]
	static NAKED void patch_567195()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 0];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_566EE0
	// Original code:	movsx   eax, word ptr [ebp+0]
	static NAKED void patch_567276()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 0];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_567750
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_567868()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_567750
	// Original code:	movzx   ecx, ds:MI_FENCE
	static NAKED void patch_56786C()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD600;	// MI_FENCE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_567750
	// Original code:	movzx   edx, ds:MI_FENCE2
	static NAKED void patch_567877()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD604;	// MI_FENCE2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_567750
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5678CA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_567750
	// Original code:	movzx   ecx, ds:MI_FIRE_HYDRANT
	static NAKED void patch_5678CE()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD594;	// MI_FIRE_HYDRANT
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_567750
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_567928()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_567750
	// Original code:	movzx   edx, ds:MI_ATM
	static NAKED void patch_56792C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD710;	// MI_ATM
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_567750
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5683C9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   eax, ds:MI_PARKINGMETER
	static NAKED void patch_569850()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD548;	// MI_PARKINGMETER
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movsx   edi, word ptr [esi+22h]
	static NAKED void patch_569861()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   ecx, ds:MI_PHONEBOOTH1
	static NAKED void patch_56986D()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD560;	// MI_PHONEBOOTH1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   edx, ds:MI_WASTEBIN
	static NAKED void patch_56987C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD564;	// MI_WASTEBIN
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   eax, ds:MI_BIN
	static NAKED void patch_56988B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD568;	// MI_BIN
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   ecx, ds:MI_POSTBOX1
	static NAKED void patch_56989A()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD56C;	// MI_POSTBOX1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   edx, ds:MI_NEWSSTAND
	static NAKED void patch_5698A9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD570;	// MI_NEWSSTAND
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   eax, ds:MI_TRAFFICCONE
	static NAKED void patch_5698B8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD574;	// MI_TRAFFICCONE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   ecx, ds:MI_DUMP1
	static NAKED void patch_5698C7()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD578;	// MI_DUMP1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   edx, ds:MI_ROADWORKBARRIER1
	static NAKED void patch_5698D6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD57C;	// MI_ROADWORKBARRIER1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   eax, ds:MI_ROADBLOCKFUCKEDCAR1
	static NAKED void patch_5698E5()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD580;	// MI_ROADBLOCKFUCKEDCAR1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   ecx, ds:MI_ROADBLOCKFUCKEDCAR2
	static NAKED void patch_5698F4()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD584;	// MI_ROADBLOCKFUCKEDCAR2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   edx, ds:MI_BUSSIGN1
	static NAKED void patch_569903()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD588;	// MI_BUSSIGN1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   eax, ds:MI_NOPARKINGSIGN1
	static NAKED void patch_569912()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD58C;	// MI_NOPARKINGSIGN1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   ecx, ds:MI_PHONESIGN
	static NAKED void patch_569921()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD590;	// MI_PHONESIGN
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   edx, ds:MI_FIRE_HYDRANT
	static NAKED void patch_569930()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD594;	// MI_FIRE_HYDRANT
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   eax, ds:MI_BOLLARDLIGHT
	static NAKED void patch_56993F()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD5FC;	// MI_BOLLARDLIGHT
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   ecx, ds:MI_PARKTABLE
	static NAKED void patch_56994E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD60C;	// MI_PARKTABLE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   edx, ds:MI_PARKINGMETER2
	static NAKED void patch_56995D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD54C;	// MI_PARKINGMETER2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   eax, ds:MI_TELPOLE02
	static NAKED void patch_56996C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD620;	// MI_TELPOLE02
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   ecx, ds:MI_PARKBENCH
	static NAKED void patch_56997B()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD628;	// MI_PARKBENCH
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   edx, ds:MI_BARRIER1
	static NAKED void patch_56998A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD618;	// MI_BARRIER1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   eax, ds:MI_SINGLESTREETLIGHTS1
	static NAKED void patch_5699AF()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD518;	// MI_SINGLESTREETLIGHTS1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   ecx, ds:MI_SINGLESTREETLIGHTS2
	static NAKED void patch_5699BA()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD51C;	// MI_SINGLESTREETLIGHTS2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   edx, ds:MI_SINGLESTREETLIGHTS3
	static NAKED void patch_5699C5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD520;	// MI_SINGLESTREETLIGHTS3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   eax, ds:MI_TRAFFICLIGHTS_MIAMI
	static NAKED void patch_5699D0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD4FC;	// MI_TRAFFICLIGHTS_MIAMI
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_VEGAS
	static NAKED void patch_5699DB()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD500;	// MI_TRAFFICLIGHTS_VEGAS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_TWOVERTICAL
	static NAKED void patch_5699E6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD504;	// MI_TRAFFICLIGHTS_TWOVERTICAL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   eax, ds:MI_TRAFFICLIGHTS_3
	static NAKED void patch_5699F1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD508;	// MI_TRAFFICLIGHTS_3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   ecx, ds:MI_TRAFFICLIGHTS_4
	static NAKED void patch_5699FC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD50C;	// MI_TRAFFICLIGHTS_4
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_5
	static NAKED void patch_569A07()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD510;	// MI_TRAFFICLIGHTS_5
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   eax, ds:MI_MLAMPPOST
	static NAKED void patch_569A12()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD614;	// MI_MLAMPPOST
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   ecx, ds:MI_STREETLAMP1
	static NAKED void patch_569A1D()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD528;	// MI_STREETLAMP1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   edx, ds:MI_STREETLAMP2
	static NAKED void patch_569A28()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD52C;	// MI_STREETLAMP2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movsx   eax, word ptr [ecx]
	static NAKED void patch_569B09()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_569BAF()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_569CB7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movzx   ecx, ds:MI_BUOY
	static NAKED void patch_569D17()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD608;	// MI_BUOY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_569D1E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_569850
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_569DBF()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_56F4E0
	// Original code:	cmp     word ptr [esi+22h], 241h
	static NAKED void patch_56F5F9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F4E0
	// Original code:	cmp     word ptr [esi+22h], 241h
	static NAKED void patch_56F5F9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	mov     dx, [ecx+22h]
	static NAKED void patch_56F92D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     dx, 420
	static NAKED void patch_56F931_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push edx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 420;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     dx, 420
	static NAKED void patch_56F931_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, dx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 420;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     dx, 438
	static NAKED void patch_56F938_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push edx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 438;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     dx, 438
	static NAKED void patch_56F938_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, dx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 438;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_570349()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	mov     ax, [ebx+22h]
	static NAKED void patch_5707FD()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     ax, 460
	static NAKED void patch_570801_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     ax, 460
	static NAKED void patch_570801_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     ax, 539
	static NAKED void patch_570807_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     ax, 539
	static NAKED void patch_570807_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     ax, 447
	static NAKED void patch_57080D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     ax, 447
	static NAKED void patch_57080D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     ax, 417
	static NAKED void patch_570813_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     ax, 417
	static NAKED void patch_570813_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     word ptr [ecx+22h], 1C9h
	static NAKED void patch_570F72_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_56F8D0
	// Original code:	cmp     word ptr [ecx+22h], 1C9h
	static NAKED void patch_570F72_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 457;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_571EA0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_571EA6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5720A0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_57206B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_585BF0
	// Original code:	cmp     word ptr [ebx+22h], 229h
	static NAKED void patch_585D3E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 553;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_585BF0
	// Original code:	cmp     word ptr [ebx+22h], 229h
	static NAKED void patch_585D3E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ebx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 553;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_585BF0
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_585EC3()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_586880
	// Original code:	cmp     word ptr [eax+22h], 21Bh
	static NAKED void patch_5869FF_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_586880
	// Original code:	cmp     word ptr [eax+22h], 21Bh
	static NAKED void patch_5869FF_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_586B00
	// Original code:	cmp     word ptr [eax+22h], 21Bh
	static NAKED void patch_586B77_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_586B00
	// Original code:	cmp     word ptr [eax+22h], 21Bh
	static NAKED void patch_586B77_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_587D20
	// Original code:	cmp     word ptr [eax+22h], 21Bh
	static NAKED void patch_587D66_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_587D20
	// Original code:	cmp     word ptr [eax+22h], 21Bh
	static NAKED void patch_587D66_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_588050
	// Original code:	cmp     [eax+22h], bx
	static NAKED void patch_588573_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_588050
	// Original code:	cmp     [eax+22h], bx
	static NAKED void patch_588573_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ebx, bx;
			push ebx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_58A330
	// Original code:	cmp     word ptr [eax+22h], 21Bh
	static NAKED void patch_58A3D7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_58A330
	// Original code:	cmp     word ptr [eax+22h], 21Bh
	static NAKED void patch_58A3D7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_58A330
	// Original code:	cmp     word ptr [eax+22h], 21Bh
	static NAKED void patch_58A5A0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_58A330
	// Original code:	cmp     word ptr [eax+22h], 21Bh
	static NAKED void patch_58A5A0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_58D7D0
	// Original code:	movsx   ecx, word ptr [eax+0Ah]
	static NAKED void patch_58D812()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_58E020
	// Original code:	cmp     word ptr [eax+22h], 208h
	static NAKED void patch_58E09F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_58E020
	// Original code:	cmp     word ptr [eax+22h], 208h
	static NAKED void patch_58E09F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_58E020
	// Original code:	cmp     word ptr [eax+22h], 1A9h
	static NAKED void patch_58E0B3_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 425;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_58E020
	// Original code:	cmp     word ptr [eax+22h], 1A9h
	static NAKED void patch_58E0B3_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 425;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_58E020
	// Original code:	movsx   ecx, word ptr [eax+0Ah]
	static NAKED void patch_58E85C()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_590FD0
	// Original code:	movsx   eax, word ptr [eax+0Ah]
	static NAKED void patch_59101E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_590FD0
	// Original code:	movsx   eax, word ptr [ecx+0Ah]
	static NAKED void patch_591094()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_591F90
	// Original code:	movzx   edx, ds:MI_MONEY
	static NAKED void patch_5920D8()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD59C;	// MI_MONEY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN10Interior_c14PlaceFurnitureEP11Furniture_ciifiiPiS2_h
	// Original code:	movzx   ecx, word ptr [edi+8]
	static NAKED void patch_592F69()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 8];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN10Interior_c14PlaceFurnitureEP11Furniture_ciifiiPiS2_h
	// Original code:	mov     [esi+0Ch], cx
	static NAKED void patch_592FC6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [esi + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN10Interior_c11PlaceObjectEhP11Furniture_cffff
	// Original code:	movzx   eax, word ptr [ebp+8]
	static NAKED void patch_593504()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 8];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN10Interior_c11PlaceObjectEhP11Furniture_cffff
	// Original code:	movzx   edx, word ptr [ebp+8]
	static NAKED void patch_593693()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebp + 8];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN10Interior_c11PlaceObjectEhP11Furniture_cffff
	// Original code:	mov     [esi+0Ch], ax
	static NAKED void patch_593701()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN10Interior_c11PlaceObjectEhP11Furniture_cffff
	// Original code:	movzx   edx, word ptr [ecx+8]
	static NAKED void patch_593766()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 8];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN10Interior_c11PlaceObjectEhP11Furniture_cffff
	// Original code:	movzx   eax, word ptr [edx+8]
	static NAKED void patch_593832()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 8];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN10Interior_c11PlaceObjectEhP11Furniture_cffff
	// Original code:	movzx   ecx, word ptr [eax+8]
	static NAKED void patch_5938AA()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 8];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_595380
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_59538C()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_598430
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_598438()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_598690
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_5986A1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_598D80
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_598DF3()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_599BB0
	// Original code:	mov     dx, [ebp+0Ah]
	static NAKED void patch_599BF5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebp + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_599BB0
	// Original code:	mov     dx, [ebp+0Ah]
	static NAKED void patch_599C41()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebp + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_599BB0
	// Original code:	mov     ax, [ebp+0Ah]
	static NAKED void patch_599C68()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_59E750
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_59E7F3()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59E750
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_59E822()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59EA20
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_59EA4D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_59EEB7
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_59EF33()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59EEB7
	// Original code:	movsx   eax, word ptr [ecx+0Ah]
	static NAKED void patch_59EF3E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_59F050
	// Original code:	movzx   ecx, ds:MI_CRANE_MAGNET
	static NAKED void patch_59F050()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD700;	// MI_CRANE_MAGNET
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F050
	// Original code:	movzx   edx, ds:MI_CRANE_HARNESS
	static NAKED void patch_59F05F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6FC;	// MI_CRANE_HARNESS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F050
	// Original code:	movzx   ecx, ds:MI_MINI_MAGNET
	static NAKED void patch_59F06A()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD740;	// MI_MINI_MAGNET
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F050
	// Original code:	movzx   edx, ds:MI_WRECKING_BALL
	static NAKED void patch_59F075()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD71C;	// MI_WRECKING_BALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F180
	// Original code:	mov     ax, [esi+14Ah]
	static NAKED void patch_59F191()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 14Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_59F180
	// Original code:	cmp     ax, 0FFFFh
	static NAKED void patch_59F198_1()
	{
		__asm
		{
			cmp eax, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: sub_59F330
	// Original code:	mov     [ecx+14Ah], ax
	static NAKED void patch_59F334()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [ecx + 14Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject15SetRemapTextureEP9RwTexturePKc
	// Original code:	mov     [ecx+16Ah], ax
	static NAKED void patch_59F361()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [ecx + 16Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F660
	// Original code:	movsx   eax, word ptr [esi+168h]
	static NAKED void patch_59F69A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 168h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_59F660
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_59F6EE()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F660
	// Original code:	mov     ax, [esi+14Ah]
	static NAKED void patch_59F73A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 14Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_59F660
	// Original code:	cmp     ax, 0FFFFh
	static NAKED void patch_59F744_1()
	{
		__asm
		{
			cmp eax, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: sub_59F660
	// Original code:	movsx   edx, ax
	static NAKED void patch_59F74A()
	{
		__asm
		{
			mov edx, eax;
			retn;
		}
	}

	// Function: sub_59F660
	// Original code:	mov     ax, [esi+16Ah]
	static NAKED void patch_59F759()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 16Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_59F660
	// Original code:	cmp     ax, 0FFFFh
	static NAKED void patch_59F760_1()
	{
		__asm
		{
			cmp eax, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: sub_59F660
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_59F793()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F660
	// Original code:	movzx   edx, ds:MI_TRAINCROSSING1
	static NAKED void patch_59F797()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6B8;	// MI_TRAINCROSSING1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_59F87E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	cmp     cx, 0FFFFh
	static NAKED void patch_59F88C_1()
	{
		__asm
		{
			cmp ecx, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movsx   eax, cx
	static NAKED void patch_59F89C()
	{
		__asm
		{
			mov eax, ecx;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_59F8A6()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_59F8DC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_59F947()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	mov     word ptr [esi+14Ah], 0FFFFh
	static NAKED void patch_59F981()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push UNDEFINED_FILE_ID_INT32;
			lea eax, [esi + 14Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   edx, ds:MI_BUOY
	static NAKED void patch_59F99E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD608;	// MI_BUOY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movsx   ecx, ax
	static NAKED void patch_59F9A5()
	{
		__asm
		{
			mov ecx, eax;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	cmp     ax, 0FFFFh
	static NAKED void patch_59F9B3_1()
	{
		__asm
		{
			cmp eax, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_59F9D0()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_MIAMI
	static NAKED void patch_59F9D4()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD4FC;	// MI_TRAFFICLIGHTS_MIAMI
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movsx   eax, cx
	static NAKED void patch_59F9DB()
	{
		__asm
		{
			mov eax, ecx;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   edx, ds:MI_MLAMPPOST
	static NAKED void patch_59F9E6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD614;	// MI_MLAMPPOST
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   edx, ds:MI_SINGLESTREETLIGHTS1
	static NAKED void patch_59F9F5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD518;	// MI_SINGLESTREETLIGHTS1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   edx, ds:MI_SINGLESTREETLIGHTS2
	static NAKED void patch_59FA00()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD51C;	// MI_SINGLESTREETLIGHTS2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   edx, ds:MI_SINGLESTREETLIGHTS3
	static NAKED void patch_59FA0B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD520;	// MI_SINGLESTREETLIGHTS3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   edx, ds:MI_DOUBLESTREETLIGHTS
	static NAKED void patch_59FA16()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD524;	// MI_DOUBLESTREETLIGHTS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_TWOVERTICAL
	static NAKED void patch_59FA21()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD504;	// MI_TRAFFICLIGHTS_TWOVERTICAL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   edx, ds:MI_TRAFFICLIGHTS_VEGAS
	static NAKED void patch_59FA2C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD500;	// MI_TRAFFICLIGHTS_VEGAS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	cmp     cx, 0FFFFh
	static NAKED void patch_59FA37_1()
	{
		__asm
		{
			cmp ecx, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_59FA4F()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_59FA9C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	mov     word ptr [esi+16Ah], 0FFFFh
	static NAKED void patch_59FAA4()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push UNDEFINED_FILE_ID_INT32;
			lea eax, [esi + 16Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   ecx, ds:MI_SAMSITE
	static NAKED void patch_59FABC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6AC;	// MI_SAMSITE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   edx, ds:MI_SAMSITE2
	static NAKED void patch_59FAC7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6B0;	// MI_SAMSITE2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   ecx, ds:MI_TRAINCROSSING
	static NAKED void patch_59FAD2()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6B4;	// MI_TRAINCROSSING
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   edx, ds:MI_TRAINCROSSING1
	static NAKED void patch_59FADD()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6B8;	// MI_TRAINCROSSING1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   ecx, ds:MI_MAGNOCRANE
	static NAKED void patch_59FAE8()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6BC;	// MI_MAGNOCRANE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   edx, ds:MI_CRANETROLLEY
	static NAKED void patch_59FAF3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6C0;	// MI_CRANETROLLEY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59F840
	// Original code:	movzx   ecx, ds:MI_QUARRYCRANE_ARM
	static NAKED void patch_59FAFE()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6C4;	// MI_QUARRYCRANE_ARM
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_59FB50
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_59FB56()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	mov     ax, [edi+22h]
	static NAKED void patch_5A0016()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	cmp     ax, 374
	static NAKED void patch_5A001A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 374;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	cmp     ax, 374
	static NAKED void patch_5A001A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 374;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	cmp     ax, 381
	static NAKED void patch_5A0020_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 381;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	cmp     ax, 381
	static NAKED void patch_5A0020_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 381;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_5A0052()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	cmp     ax, 406
	static NAKED void patch_5A0056_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	cmp     ax, 406
	static NAKED void patch_5A0056_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	cmp     ax, 486
	static NAKED void patch_5A0060_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	cmp     ax, 486
	static NAKED void patch_5A0060_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	cmp     ax, 530
	static NAKED void patch_5A006A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	cmp     ax, 530
	static NAKED void patch_5A006A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	cmp     word ptr [edi+22h], 156h
	static NAKED void patch_5A01B1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 342;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_59FEE0
	// Original code:	cmp     word ptr [edi+22h], 156h
	static NAKED void patch_5A01B1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 342;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5A02E0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_5A049E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5A02E0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_5A06CD()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject29ProcessTrainCrossingBehaviourEv
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_5A0C08()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject29ProcessTrainCrossingBehaviourEv
	// Original code:	movzx   eax, ds:MI_TRAINCROSSING1
	static NAKED void patch_5A0C0C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD6B8;	// MI_TRAINCROSSING1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject29ProcessTrainCrossingBehaviourEv
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_5A0CBD()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject29ProcessTrainCrossingBehaviourEv
	// Original code:	movzx   edx, ds:MI_TRAINCROSSING1
	static NAKED void patch_5A0CC1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6B8;	// MI_TRAINCROSSING1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40191E
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_5A0E5E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_40191E
	// Original code:	movzx   eax, ds:MI_IMY_SHASH_WALL
	static NAKED void patch_5A0E62()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD748;	// MI_IMY_SHASH_WALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_40191E
	// Original code:	cmp     word ptr [eax+22h], 259h
	static NAKED void patch_5A0EAF_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 601;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_40191E
	// Original code:	cmp     word ptr [eax+22h], 259h
	static NAKED void patch_5A0EAF_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 601;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_40191E
	// Original code:	cmp     word ptr [edi+22h], 212h
	static NAKED void patch_5A0EBF_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_40191E
	// Original code:	cmp     word ptr [edi+22h], 212h
	static NAKED void patch_5A0EBF_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5A1580
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5A1586()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5A1580
	// Original code:	movzx   ecx, ds:MI_GRASSPLANT
	static NAKED void patch_5A158A()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6F8;	// MI_GRASSPLANT
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5A1580
	// Original code:	movzx   edx, ds:MI_GRASSHOUSE
	static NAKED void patch_5A1595()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6F4;	// MI_GRASSHOUSE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5A1580
	// Original code:	movzx   eax, ds:MI_GRASSPLANT
	static NAKED void patch_5A1605()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD6F8;	// MI_GRASSPLANT
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5A1580
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_5A160C()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5A1B60
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_5A1B70()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5A1B60
	// Original code:	movzx   ecx, ds:MI_FIRE_HYDRANT
	static NAKED void patch_5A1B74()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD594;	// MI_FIRE_HYDRANT
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5A1B60
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_5A1BB1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5A1DF0
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_5A1E1D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5A2130
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5A2138()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5A2130
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5A219C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5A2130
	// Original code:	mov     cx, [eax+22h]
	static NAKED void patch_5A21C9()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5A2130
	// Original code:	cmp     cx, 406
	static NAKED void patch_5A21CD_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5A2130
	// Original code:	cmp     cx, 406
	static NAKED void patch_5A21CD_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5A2130
	// Original code:	cmp     cx, 530
	static NAKED void patch_5A21D4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5A2130
	// Original code:	cmp     cx, 530
	static NAKED void patch_5A21D4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5A2130
	// Original code:	movzx   eax, ds:MI_BUOY
	static NAKED void patch_5A25D5()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD608;	// MI_BUOY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5A2130
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_5A25DC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5A2130
	// Original code:	movzx   ecx, ds:MI_RCBOMB
	static NAKED void patch_5A2644()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD634;	// MI_RCBOMB
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5A2130
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_5A264B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_5A29A8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movzx   ecx, ds:MI_SAMSITE
	static NAKED void patch_5A29AC()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6AC;	// MI_SAMSITE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movzx   edx, ds:MI_SAMSITE2
	static NAKED void patch_5A29B7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6B0;	// MI_SAMSITE2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_5A29C9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movzx   ecx, ds:MI_TRAINCROSSING
	static NAKED void patch_5A29CD()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6B4;	// MI_TRAINCROSSING
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movzx   edx, ds:MI_TRAINCROSSING1
	static NAKED void patch_5A29D8()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6B8;	// MI_TRAINCROSSING1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_5A29EA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movzx   ecx, ds:MI_MAGNOCRANE
	static NAKED void patch_5A29EE()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6BC;	// MI_MAGNOCRANE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movzx   edx, ds:MI_CRANETROLLEY
	static NAKED void patch_5A29F9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6C0;	// MI_CRANETROLLEY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movzx   ecx, ds:MI_QUARRYCRANE_ARM
	static NAKED void patch_5A2A04()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6C4;	// MI_QUARRYCRANE_ARM
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_5A2A77()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movzx   edx, ds:MI_MAGNOCRANE
	static NAKED void patch_5A2A7B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6BC;	// MI_MAGNOCRANE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movzx   ecx, ds:MI_CRANETROLLEY
	static NAKED void patch_5A2AB9()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6C0;	// MI_CRANETROLLEY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN7CObject19ProcessControlLogicEv
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_5A2B67()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5A75B0
	// Original code:	mov     ax, [esi+edi*2+0Ah]
	static NAKED void patch_5A762E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + edi * 2 + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5A75B0
	// Original code:	mov     [esi+edi*2+0Ah], dx
	static NAKED void patch_5A767F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [esi + edi * 2 + 0Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5A81E0
	// Original code:	movsx   eax, word ptr [esi+0Ah]
	static NAKED void patch_5A81F2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5A82C0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_5A8340()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4D5D00
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_5B18A7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5B2E60
	// Original code:	mov     [eax+24h], cx
	static NAKED void patch_5B2EAC()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [eax + 24h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5B2E60
	// Original code:	mov     [eax+22h], dx
	static NAKED void patch_5B2EB4()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5B3040
	// Original code:	movsx   ebp, word ptr [edx+22h]
	static NAKED void patch_5B3062()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5B3040
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_5B306F()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5B51E0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5B5266()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5B51E0
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_5B5295()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5B51E0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_5B5299()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5B6DD0
	// Original code:	mov     [eax+6], cx
	static NAKED void patch_5B6DEA()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [eax + 6];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5B6DD0
	// Original code:	mov     [eax+6], cx
	static NAKED void patch_5B6DFC()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [eax + 6];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5B6F30
	// Original code:	movsx   eax, word ptr [ebp+0Ah]
	static NAKED void patch_5B6FFD()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5B6F30
	// Original code:	mov     [eax+6], si
	static NAKED void patch_5B701C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push esi;
			lea eax, [eax + 6];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5B75E0
	// Original code:	mov     [ecx+6], ax
	static NAKED void patch_5B7650()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [ecx + 6];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5B75E0
	// Original code:	mov     [ecx+6], ax
	static NAKED void patch_5B7661()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [ecx + 6];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5B7670
	// Original code:	mov     [esi+24h], ax
	static NAKED void patch_5B77F7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 24h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5B7670
	// Original code:	mov     [esi+24h], dx
	static NAKED void patch_5B79DD()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [esi + 24h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TRAFFICLIGHTS, ax
	static NAKED void patch_5BCA15()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD4F4;	// MI_TRAFFICLIGHTS
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TRAFFICLIGHTS_VERTICAL, ax
	static NAKED void patch_5BCA1B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD4F8;	// MI_TRAFFICLIGHTS_VERTICAL
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TRAFFICLIGHTS_MIAMI, ax
	static NAKED void patch_5BCA21()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD4FC;	// MI_TRAFFICLIGHTS_MIAMI
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TRAFFICLIGHTS_VEGAS, ax
	static NAKED void patch_5BCA27()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD500;	// MI_TRAFFICLIGHTS_VEGAS
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TRAFFICLIGHTS_TWOVERTICAL, ax
	static NAKED void patch_5BCA2D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD504;	// MI_TRAFFICLIGHTS_TWOVERTICAL
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_SINGLESTREETLIGHTS1, ax
	static NAKED void patch_5BCA33()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD518;	// MI_SINGLESTREETLIGHTS1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_SINGLESTREETLIGHTS2, ax
	static NAKED void patch_5BCA39()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD51C;	// MI_SINGLESTREETLIGHTS2
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_SINGLESTREETLIGHTS3, ax
	static NAKED void patch_5BCA3F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD520;	// MI_SINGLESTREETLIGHTS3
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_DOUBLESTREETLIGHTS, ax
	static NAKED void patch_5BCA45()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD524;	// MI_DOUBLESTREETLIGHTS
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_STREETLAMP1, ax
	static NAKED void patch_5BCA4B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD528;	// MI_STREETLAMP1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_STREETLAMP2, ax
	static NAKED void patch_5BCA51()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD52C;	// MI_STREETLAMP2
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MODELID_CRANE_1, ax
	static NAKED void patch_5BCA57()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD530;	// MODELID_CRANE_1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MODELID_CRANE_2, ax
	static NAKED void patch_5BCA5D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD534;	// MODELID_CRANE_2
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MODELID_CRANE_3, ax
	static NAKED void patch_5BCA63()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD538;	// MODELID_CRANE_3
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MODELID_CRANE_4, ax
	static NAKED void patch_5BCA69()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD53C;	// MODELID_CRANE_4
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MODELID_CRANE_5, ax
	static NAKED void patch_5BCA6F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD540;	// MODELID_CRANE_5
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MODELID_CRANE_6, ax
	static NAKED void patch_5BCA75()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD544;	// MODELID_CRANE_6
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PARKINGMETER, ax
	static NAKED void patch_5BCA7B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD548;	// MI_PARKINGMETER
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PARKINGMETER2, ax
	static NAKED void patch_5BCA81()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD54C;	// MI_PARKINGMETER2
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_MALLFAN, ax
	static NAKED void patch_5BCA87()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD550;	// MI_MALLFAN
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_HOTELFAN_NIGHT, ax
	static NAKED void patch_5BCA8D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD554;	// MI_HOTELFAN_NIGHT
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_HOTELFAN_DAY, ax
	static NAKED void patch_5BCA93()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD558;	// MI_HOTELFAN_DAY
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_HOTROOMFAN, ax
	static NAKED void patch_5BCA99()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD55C;	// MI_HOTROOMFAN
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PHONEBOOTH1, ax
	static NAKED void patch_5BCA9F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD560;	// MI_PHONEBOOTH1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_WASTEBIN, ax
	static NAKED void patch_5BCAA5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD564;	// MI_WASTEBIN
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_BIN, ax
	static NAKED void patch_5BCAAB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD568;	// MI_BIN
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_POSTBOX1, ax
	static NAKED void patch_5BCAB1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD56C;	// MI_POSTBOX1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_NEWSSTAND, ax
	static NAKED void patch_5BCAB7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD570;	// MI_NEWSSTAND
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TRAFFICCONE, ax
	static NAKED void patch_5BCABD()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD574;	// MI_TRAFFICCONE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_DUMP1, ax
	static NAKED void patch_5BCAC3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD578;	// MI_DUMP1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_ROADWORKBARRIER1, ax
	static NAKED void patch_5BCAC9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD57C;	// MI_ROADWORKBARRIER1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_ROADBLOCKFUCKEDCAR1, ax
	static NAKED void patch_5BCACF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD580;	// MI_ROADBLOCKFUCKEDCAR1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_ROADBLOCKFUCKEDCAR2, ax
	static NAKED void patch_5BCAD5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD584;	// MI_ROADBLOCKFUCKEDCAR2
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_BUSSIGN1, ax
	static NAKED void patch_5BCADB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD588;	// MI_BUSSIGN1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_NOPARKINGSIGN1, ax
	static NAKED void patch_5BCAE1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD58C;	// MI_NOPARKINGSIGN1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PHONESIGN, ax
	static NAKED void patch_5BCAE7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD590;	// MI_PHONESIGN
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_FIRE_HYDRANT, ax
	static NAKED void patch_5BCAED()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD594;	// MI_FIRE_HYDRANT
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_COLLECTABLE1, ax
	static NAKED void patch_5BCAF3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD598;	// MI_COLLECTABLE1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_MONEY, ax
	static NAKED void patch_5BCAF9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD59C;	// MI_MONEY
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_CARMINE, ax
	static NAKED void patch_5BCAFF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5A0;	// MI_CARMINE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_NAUTICALMINE, ax
	static NAKED void patch_5BCB05()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5A4;	// MI_NAUTICALMINE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TELLY, ax
	static NAKED void patch_5BCB0B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5A8;	// MI_TELLY
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_BRIEFCASE, ax
	static NAKED void patch_5BCB11()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5AC;	// MI_BRIEFCASE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_GLASS1, ax
	static NAKED void patch_5BCB17()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5B0;	// MI_GLASS1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_GLASS8, ax
	static NAKED void patch_5BCB1D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5B4;	// MI_GLASS8
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_EXPLODINGBARREL, ax
	static NAKED void patch_5BCB23()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5B8;	// MI_EXPLODINGBARREL
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_ADRENALINE, ax
	static NAKED void patch_5BCB29()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5BC;	// MI_PICKUP_ADRENALINE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_BODYARMOUR, ax
	static NAKED void patch_5BCB2F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5C0;	// MI_PICKUP_BODYARMOUR
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_INFO, ax
	static NAKED void patch_5BCB35()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5C4;	// MI_PICKUP_INFO
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_HEALTH, ax
	static NAKED void patch_5BCB3B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5C8;	// MI_PICKUP_HEALTH
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_PROPERTY, ax
	static NAKED void patch_5BCB41()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5E8;	// MI_PICKUP_PROPERTY
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_PROPERTY_FORSALE, ax
	static NAKED void patch_5BCB47()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5EC;	// MI_PICKUP_PROPERTY_FORSALE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_BONUS, ax
	static NAKED void patch_5BCB4D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5CC;	// MI_PICKUP_BONUS
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_BRIBE, ax
	static NAKED void patch_5BCB53()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5D0;	// MI_PICKUP_BRIBE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_KILLFRENZY, ax
	static NAKED void patch_5BCB59()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5D4;	// MI_PICKUP_KILLFRENZY
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_CAMERA, ax
	static NAKED void patch_5BCB5F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5D8;	// MI_PICKUP_CAMERA
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_PARACHUTE, ax
	static NAKED void patch_5BCB65()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5DC;	// MI_PICKUP_PARACHUTE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_REVENUE, ax
	static NAKED void patch_5BCB6B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5E0;	// MI_PICKUP_REVENUE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_SAVEGAME, ax
	static NAKED void patch_5BCB71()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5E4;	// MI_PICKUP_SAVEGAME
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_CLOTHES, ax
	static NAKED void patch_5BCB77()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5F0;	// MI_PICKUP_CLOTHES
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_2P_KILLFRENZY, ax
	static NAKED void patch_5BCB7D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5F4;	// MI_PICKUP_2P_KILLFRENZY
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PICKUP_2P_COOP, ax
	static NAKED void patch_5BCB83()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5F8;	// MI_PICKUP_2P_COOP
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_BOLLARDLIGHT, ax
	static NAKED void patch_5BCB89()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD5FC;	// MI_BOLLARDLIGHT
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PARACHUTE_BACKPACK, ax
	static NAKED void patch_5BCB8F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD74C;	// MI_PARACHUTE_BACKPACK
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_OYSTER, ax
	static NAKED void patch_5BCB95()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD750;	// MI_OYSTER
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_HORSESHOE, ax
	static NAKED void patch_5BCB9B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD754;	// MI_HORSESHOE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_LAMPPOST1, ax
	static NAKED void patch_5BCBA1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD610;	// MI_LAMPPOST1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_MLAMPPOST, ax
	static NAKED void patch_5BCBA7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD614;	// MI_MLAMPPOST
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_BARRIER1, ax
	static NAKED void patch_5BCBAD()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD618;	// MI_BARRIER1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_LITTLEHA_POLICE, ax
	static NAKED void patch_5BCBB3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD61C;	// MI_LITTLEHA_POLICE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TELPOLE02, ax
	static NAKED void patch_5BCBB9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD620;	// MI_TELPOLE02
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TRAFFICLIGHT01, ax
	static NAKED void patch_5BCBBF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD624;	// MI_TRAFFICLIGHT01
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PARKBENCH, ax
	static NAKED void patch_5BCBC5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD628;	// MI_PARKBENCH
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_LIGHTBEAM, ax
	static NAKED void patch_5BCBCB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD62C;	// MI_LIGHTBEAM
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_AIRPORTRADAR, ax
	static NAKED void patch_5BCBD1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD630;	// MI_AIRPORTRADAR
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_RCBOMB, ax
	static NAKED void patch_5BCBD7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD634;	// MI_RCBOMB
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_BEACHBALL, ax
	static NAKED void patch_5BCBDD()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD638;	// MI_BEACHBALL
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_SANDCASTLE1, ax
	static NAKED void patch_5BCBE3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD63C;	// MI_SANDCASTLE1
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_SANDCASTLE2, ax
	static NAKED void patch_5BCBE9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD640;	// MI_SANDCASTLE2
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_JELLYFISH, ax
	static NAKED void patch_5BCBEF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD644;	// MI_JELLYFISH
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_JELLYFISH01, ax
	static NAKED void patch_5BCBF5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD648;	// MI_JELLYFISH01
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_FISH1SINGLE, ax
	static NAKED void patch_5BCBFB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD64C;	// MI_FISH1SINGLE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_FISH1S, ax
	static NAKED void patch_5BCC01()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD650;	// MI_FISH1S
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_FISH2SINGLE, ax
	static NAKED void patch_5BCC07()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD654;	// MI_FISH2SINGLE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_FISH2S, ax
	static NAKED void patch_5BCC0D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD658;	// MI_FISH2S
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_FISH3SINGLE, ax
	static NAKED void patch_5BCC13()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD65C;	// MI_FISH3SINGLE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_FISH3S, ax
	static NAKED void patch_5BCC19()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD660;	// MI_FISH3S
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TURTLE, ax
	static NAKED void patch_5BCC1F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD664;	// MI_TURTLE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_DOLPHIN, ax
	static NAKED void patch_5BCC25()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD668;	// MI_DOLPHIN
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_SHARK, ax
	static NAKED void patch_5BCC2B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD66C;	// MI_SHARK
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_SUBMARINE, ax
	static NAKED void patch_5BCC31()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD670;	// MI_SUBMARINE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_ESCALATORSTEP, ax
	static NAKED void patch_5BCC37()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD674;	// MI_ESCALATORSTEP
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_ESCALATORSTEP8, ax
	static NAKED void patch_5BCC3D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD678;	// MI_ESCALATORSTEP8
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_LOUNGE_WOOD_UP, ax
	static NAKED void patch_5BCC43()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD67C;	// MI_LOUNGE_WOOD_UP
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_LOUNGE_TOWEL_UP, ax
	static NAKED void patch_5BCC49()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD680;	// MI_LOUNGE_TOWEL_UP
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_LOUNGE_WOOD_DN, ax
	static NAKED void patch_5BCC4F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD684;	// MI_LOUNGE_WOOD_DN
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_LOTION, ax
	static NAKED void patch_5BCC55()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD688;	// MI_LOTION
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_BEACHTOWEL01, ax
	static NAKED void patch_5BCC5B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD68C;	// MI_BEACHTOWEL01
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_BEACHTOWEL02, ax
	static NAKED void patch_5BCC61()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD690;	// MI_BEACHTOWEL02
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_BEACHTOWEL03, ax
	static NAKED void patch_5BCC67()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD694;	// MI_BEACHTOWEL03
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_BEACHTOWEL04, ax
	static NAKED void patch_5BCC6D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD698;	// MI_BEACHTOWEL04
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_BLIMP_NIGHT, ax
	static NAKED void patch_5BCC73()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD69C;	// MI_BLIMP_NIGHT
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_BLIMP_DAY, ax
	static NAKED void patch_5BCC79()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD6A0;	// MI_BLIMP_DAY
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_YT_MAIN_BODY, ax
	static NAKED void patch_5BCC7F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD6A4;	// MI_YT_MAIN_BODY
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_YT_MAIN_BODY2, ax
	static NAKED void patch_5BCC85()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD6A8;	// MI_YT_MAIN_BODY2
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TRAFFICLIGHTS_3, ax
	static NAKED void patch_5BCC8B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD508;	// MI_TRAFFICLIGHTS_3
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TRAFFICLIGHTS_4, ax
	static NAKED void patch_5BCC91()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD50C;	// MI_TRAFFICLIGHTS_4
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TRAFFICLIGHTS_5, ax
	static NAKED void patch_5BCC97()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD510;	// MI_TRAFFICLIGHTS_5
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_TRAFFICLIGHTS_GAY, ax
	static NAKED void patch_5BCC9D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD514;	// MI_TRAFFICLIGHTS_GAY
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_IMY_SHASH_WALL, ax
	static NAKED void patch_5BCCA3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD748;	// MI_IMY_SHASH_WALL
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_HYDRAULICS, ax
	static NAKED void patch_5BCCA9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD76C;	// MI_HYDRAULICS
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_STEREO_UPGRADE, ax
	static NAKED void patch_5BCCAF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD770;	// MI_STEREO_UPGRADE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_BASKETBALL, ax
	static NAKED void patch_5BCCB5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD774;	// MI_BASKETBALL
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_POOL_CUE_BALL, ax
	static NAKED void patch_5BCCBB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD778;	// MI_POOL_CUE_BALL
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_PUNCHBAG, ax
	static NAKED void patch_5BCCC1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD77C;	// MI_PUNCHBAG
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _Z16InitModelIndicesv
	// Original code:	mov     ds:MI_IMY_GRAY_CRATE, ax
	static NAKED void patch_5BCCC7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			push 0x8CD780;	// MI_IMY_GRAY_CRATE
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN19FurnitureSubGroup_c12AddFurnitureEtshhh
	// Original code:	mov     [esi+8], ax
	static NAKED void patch_5C00F9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 8];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN19FurnitureSubGroup_c12AddFurnitureEtshhh
	// Original code:	mov     [esi+0Ah], cx
	static NAKED void patch_5C00FD()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [esi + 0Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN19FurnitureSubGroup_c12AddFurnitureEtshhh
	// Original code:	movzx   edx, ax
	static NAKED void patch_5C0108()
	{
		__asm
		{
			mov edx, eax;
			retn;
		}
	}

	// Function: sub_5D24B0
	// Original code:	mov     [ecx+26h], ax
	static NAKED void patch_5D2555()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [ecx + 26h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5D2560
	// Original code:	mov     cx, [ecx+26h]
	static NAKED void patch_5D260C()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ecx + 26h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5D4800
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5D48EF()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5D4940
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_5D49C7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5D4B40
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5D4BDE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5DC510
	// Original code:	movsx   edx, word ptr [ebx+22h]
	static NAKED void patch_5DC7F3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5DCD80
	// Original code:	movsx   edx, word ptr [esi+1Ah]
	static NAKED void patch_5DCE9C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 1Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5DCD80
	// Original code:	movsx   eax, word ptr [esi+18h]
	static NAKED void patch_5DCEA0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 18h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5DF340
	// Original code:	mov     [esi+50Ah], ax
	static NAKED void patch_5DF380()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 50Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5DF910
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_5DF941()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5DF910
	// Original code:	cmp     word ptr [ecx+22h], 214h
	static NAKED void patch_5DFA9C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5DF910
	// Original code:	cmp     word ptr [ecx+22h], 214h
	static NAKED void patch_5DFA9C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5DFD90
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5DFD93()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5DFDF0
	// Original code:	cmp     word ptr [edi+22h], 220h
	static NAKED void patch_5DFE3D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 544;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5DFDF0
	// Original code:	cmp     word ptr [edi+22h], 220h
	static NAKED void patch_5DFE3D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 544;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5E00F0
	// Original code:	movsx   edi, word ptr [esi+22h]
	static NAKED void patch_5E00F6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5E0130
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5E0133()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5E2530
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5E255B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5E3C30
	// Original code:	cmp     word ptr [ecx+22h], 156h
	static NAKED void patch_5E3D42_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 342;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5E3C30
	// Original code:	cmp     word ptr [ecx+22h], 156h
	static NAKED void patch_5E3D42_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 342;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5E3C30
	// Original code:	mov     ax, [ecx+22h]
	static NAKED void patch_5E3DE1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5E3C30
	// Original code:	cmp     ax, 564
	static NAKED void patch_5E3DEB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5E3C30
	// Original code:	cmp     ax, 564
	static NAKED void patch_5E3DEB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5E3C30
	// Original code:	cmp     ax, 594
	static NAKED void patch_5E3DF1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 594;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5E3C30
	// Original code:	cmp     ax, 594
	static NAKED void patch_5E3DF1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 594;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5E4880
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_5E48AE()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5E4880
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_5E490E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5E4880
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_5E4921()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5E57F0
	// Original code:	movsx   ecx, word ptr [eax+2Ch]
	static NAKED void patch_5E5815()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5E65A0
	// Original code:	cmp     word ptr [ebp+22h], 0
	static NAKED void patch_5E6908_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 0;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5E65A0
	// Original code:	cmp     word ptr [ebp+22h], 0
	static NAKED void patch_5E6908_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ebp + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 0;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5E65A0
	// Original code:	movsx   ecx, word ptr [ebp+22h]
	static NAKED void patch_5E72EE()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5E7CB0
	// Original code:	cmp     word ptr [ebp+22h], 152h
	static NAKED void patch_5E7DA5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 338;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5E7CB0
	// Original code:	cmp     word ptr [ebp+22h], 152h
	static NAKED void patch_5E7DA5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ebp + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 338;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_5E8030
	// Original code:	mov     [esi+50Ah], bx
	static NAKED void patch_5E8469()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ebx;
			lea eax, [esi + 50Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5E8627
	// Original code:	movsx   eax, word ptr [esi+794h]
	static NAKED void patch_5E8663()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 794h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5E8CD0
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_5E8EF5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5E8CD0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_5E8F00()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_403AA0
	// Original code:	movsx   ecx, word ptr [ebx+22h]
	static NAKED void patch_5F201B()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5F2F00
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_5F2F1C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5F32D0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_5F3367()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5F3880
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_5F38AE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5F3970
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_5F39BD()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5F3DD0
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_5F571A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5F3DD0
	// Original code:	movsx   ecx, word ptr [edx+22h]
	static NAKED void patch_5F572C()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5F6950
	// Original code:	movzx   eax, ds:MI_GANG_SMOKE
	static NAKED void patch_5F6979()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD72C;	// MI_GANG_SMOKE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5F6950
	// Original code:	movzx   eax, ds:MI_GANG_DRINK
	static NAKED void patch_5F6987()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD728;	// MI_GANG_DRINK
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5F8900
	// Original code:	movsx   edx, word ptr [eax+0Eh]
	static NAKED void patch_5F8922()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5FB2D0
	// Original code:	movsx   ebp, word ptr [eax+0Eh]
	static NAKED void patch_5FB2D6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5FB390
	// Original code:	movsx   ebp, word ptr [eax+0Eh]
	static NAKED void patch_5FB396()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5FBB90
	// Original code:	movsx   ebp, word ptr [ebx+0Eh]
	static NAKED void patch_5FBB99()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ebx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5FBCB0
	// Original code:	movsx   ecx, word ptr [ecx+0Eh]
	static NAKED void patch_5FBCB7()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ecx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5FBD10
	// Original code:	movsx   eax, word ptr [ebp+0Eh]
	static NAKED void patch_5FBD8D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5FBDF0
	// Original code:	movsx   edx, word ptr [esi+0Eh]
	static NAKED void patch_5FBE09()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5FBE70
	// Original code:	movsx   edx, word ptr [ecx+0Eh]
	static NAKED void patch_5FBE8B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5FBF50
	// Original code:	movsx   ecx, word ptr [eax+0Eh]
	static NAKED void patch_5FBF55()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5FC070
	// Original code:	movsx   edx, word ptr [esi+0Eh]
	static NAKED void patch_5FC091()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5FD860
	// Original code:	movsx   eax, word ptr [ecx+6Ch]
	static NAKED void patch_5FD866()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 6Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5FD890
	// Original code:	movsx   eax, word ptr [ecx+6Ch]
	static NAKED void patch_5FD896()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 6Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5FDE20
	// Original code:	movsx   eax, word ptr [eax+6Ch]
	static NAKED void patch_5FDE5C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 6Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5FEDA0
	// Original code:	movsx   eax, word ptr [esi+32h]
	static NAKED void patch_5FEDD4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 32h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5FEDA0
	// Original code:	movsx   ecx, word ptr [esi+30h]
	static NAKED void patch_5FEDDB()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 30h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5FEDA0
	// Original code:	mov     dx, [esi+0Ch]
	static NAKED void patch_5FEDEA()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5FEEA0
	// Original code:	movsx   eax, word ptr [esi+32h]
	static NAKED void patch_5FEED4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 32h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_5FEEA0
	// Original code:	movsx   ecx, word ptr [esi+30h]
	static NAKED void patch_5FEEDB()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 30h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5FEEA0
	// Original code:	mov     dx, [esi+0Ch]
	static NAKED void patch_5FEEEA()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_5FF980
	// Original code:	mov     [eax+0Ch], cx
	static NAKED void patch_5FF984()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [eax + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6002F0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_60038C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_602C00
	// Original code:	mov     di, [ebp+0Ch]
	static NAKED void patch_602CE8()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ebp + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_602C00
	// Original code:	mov     [ebp+0Ch], di
	static NAKED void patch_602D3B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edi;
			lea eax, [ebp + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6034B0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_603505()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_603570
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_603676()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_605420
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_605470()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6060A0
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_606439()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_606890
	// Original code:	movsx   eax, word ptr [ebp+22h]
	static NAKED void patch_606A51()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_607E30
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_6080BC()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_607E30
	// Original code:	movzx   ecx, ds:MI_ESCALATORSTEP
	static NAKED void patch_6080C0()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD674;	// MI_ESCALATORSTEP
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_607E30
	// Original code:	movzx   edx, ds:MI_ESCALATORSTEP8
	static NAKED void patch_6080CB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD678;	// MI_ESCALATORSTEP8
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6098F0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_609A28()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_60B460
	// Original code:	movsx   edx, word ptr [edi+20h]
	static NAKED void patch_60B4E1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 20h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_610310
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_610379()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_610ED0
	// Original code:	movzx   ecx, ds:MI_SAMSITE
	static NAKED void patch_610ED0()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6AC;	// MI_SAMSITE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_610ED0
	// Original code:	movzx   edx, ds:MI_SAMSITE2
	static NAKED void patch_610EDF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6B0;	// MI_SAMSITE2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6110E0
	// Original code:	lea     eax, [edi-0Ch]
	static NAKED void patch_61115A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edi;
			call GetModelIDforModelSpecialFeatures;
			mov edi, eax;
			add esp, 4;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6110E0
	// Original code:	lea     eax, [edi-57h]
	static NAKED void patch_6111D8()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edi;
			call GetModelIDforModelSpecialFeatures;
			mov edi, eax;
			add esp, 4;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6110E0
	// Original code:	lea     eax, [edi-1Bh]
	static NAKED void patch_61121E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edi;
			call GetModelIDforModelSpecialFeatures;
			mov edi, eax;
			add esp, 4;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6117F0
	// Original code:	add     eax, 0FFFFFE67h
	static NAKED void patch_6117F4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_611900
	// Original code:	add     eax, 0FFFFFE67h
	static NAKED void patch_611904()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6119D0
	// Original code:	add     eax, 0FFFFFE67h
	static NAKED void patch_6119D4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_612320
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_61234D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6123A0
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_6123AB()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6123A0
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_612596()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_612CD0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_612EE6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_613260
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_613269()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_613260
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_613363()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_613260
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_613377()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_613260
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_61338B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_613260
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_61339F()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_613A00
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_613A36()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_613A00
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_613A68()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_613A00
	// Original code:	add     eax, 0FFFFFE69h
	static NAKED void patch_613A6C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_614580
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6145D9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_614580
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_614605()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_614580
	// Original code:	movzx   ecx, ds:MI_BUOY
	static NAKED void patch_614609()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD608;	// MI_BUOY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_614670
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6146A9()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_614670
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6146D1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_614720
	// Original code:	movzx   ecx, ds:MI_TELLY
	static NAKED void patch_615846()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD5A8;	// MI_TELLY
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_615DC0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_615E1E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_615DC0
	// Original code:	movzx   ecx, ds:MI_ROADWORKBARRIER1
	static NAKED void patch_615E22()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD57C;	// MI_ROADWORKBARRIER1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_615DC0
	// Original code:	movzx   edx, ds:MI_ROADBLOCKFUCKEDCAR1
	static NAKED void patch_615E31()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD580;	// MI_ROADBLOCKFUCKEDCAR1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_615DC0
	// Original code:	movzx   ecx, ds:MI_ROADBLOCKFUCKEDCAR2
	static NAKED void patch_615E40()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD584;	// MI_ROADBLOCKFUCKEDCAR2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_615DC0
	// Original code:	movzx   edx, ds:MI_BEACHBALL
	static NAKED void patch_615E4F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD638;	// MI_BEACHBALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_615DC0
	// Original code:	movzx   ecx, ds:MI_BEACHTOWEL01
	static NAKED void patch_615E5E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD68C;	// MI_BEACHTOWEL01
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_615DC0
	// Original code:	movzx   edx, ds:MI_BEACHTOWEL04
	static NAKED void patch_615E69()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD698;	// MI_BEACHTOWEL04
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_615DC0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_615F9C()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_615DC0
	// Original code:	movzx   eax, ds:MI_SAMSITE
	static NAKED void patch_615FA0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD6AC;	// MI_SAMSITE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_615DC0
	// Original code:	movzx   edx, ds:MI_SAMSITE2
	static NAKED void patch_615FAB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6B0;	// MI_SAMSITE2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_616000
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_616041()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_616000
	// Original code:	movzx   ecx, ds:MI_SAMSITE
	static NAKED void patch_616048()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6AC;	// MI_SAMSITE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_616000
	// Original code:	movzx   ecx, ds:MI_SAMSITE2
	static NAKED void patch_61606B()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6B0;	// MI_SAMSITE2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_616A40
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_616A99()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_616A40
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_616AA7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_616A40
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_616AE4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_616A40
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_616AEF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_617050
	// Original code:	movsx   esi, word ptr [ecx]
	static NAKED void patch_617060()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_617490
	// Original code:	movsx   edi, word ptr [eax]
	static NAKED void patch_6174A1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [eax];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_617530
	// Original code:	movsx   esi, word ptr [eax]
	static NAKED void patch_617550()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [eax];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6184B0
	// Original code:	movsx   ecx, word ptr [esi+2Ch]
	static NAKED void patch_6184C1()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_61B4C0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_61B4C4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_61B4F0
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_61B529()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6240B0
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_624287()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6240B0
	// Original code:	movsx   edx, word ptr [ebp+22h]
	static NAKED void patch_624393()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6240B0
	// Original code:	movsx   edi, word ptr [eax]
	static NAKED void patch_6243B6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [eax];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_625270
	// Original code:	movsx   eax, di
	static NAKED void patch_6255AE()
	{
		__asm
		{
			mov eax, edi;
			retn;
		}
	}

	// Function: sub_625270
	// Original code:	movsx   ecx, word ptr [esi+2Ch]
	static NAKED void patch_6255C4()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_625270
	// Original code:	movsx   ecx, word ptr [esi+2Ch]
	static NAKED void patch_6255E2()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_627B20
	// Original code:	movsx   edx, word ptr [ecx+2Ch]
	static NAKED void patch_627BB0()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_627B20
	// Original code:	movsx   ecx, word ptr [eax+20h]
	static NAKED void patch_627C32()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 20h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_627CC0
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_627D27()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6289F0
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_628A37()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_629080
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_6291B7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_629920
	// Original code:	movsx   edx, ax
	static NAKED void patch_629C35()
	{
		__asm
		{
			mov edx, eax;
			retn;
		}
	}

	// Function: sub_629920
	// Original code:	movsx   edx, ax
	static NAKED void patch_629FB7()
	{
		__asm
		{
			mov edx, eax;
			retn;
		}
	}

	// Function: sub_629920
	// Original code:	movsx   ecx, ax
	static NAKED void patch_629FE3()
	{
		__asm
		{
			mov ecx, eax;
			retn;
		}
	}

	// Function: sub_62D3B0
	// Original code:	movsx   eax, word ptr [ecx+2Ch]
	static NAKED void patch_62D6AC()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_62D3B0
	// Original code:	movsx   edx, word ptr [ecx+2Ch]
	static NAKED void patch_62D6C5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_62D3B0
	// Original code:	movsx   edx, word ptr [ecx+2Ch]
	static NAKED void patch_62D706()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_62F520
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_62F535()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_62F520
	// Original code:	movzx   edx, ds:MI_ESCALATORSTEP
	static NAKED void patch_62F539()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD674;	// MI_ESCALATORSTEP
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_62F520
	// Original code:	movzx   edx, ds:MI_ESCALATORSTEP8
	static NAKED void patch_62F544()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD678;	// MI_ESCALATORSTEP8
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6339C0
	// Original code:	mov     [esi+18h], dx
	static NAKED void patch_6339F5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [esi + 18h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_633B00
	// Original code:	movsx   ecx, word ptr [esi+16h]
	static NAKED void patch_633B5F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 16h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_633B00
	// Original code:	movsx   ecx, word ptr [esi+18h]
	static NAKED void patch_633B7D()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 18h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_633BD0
	// Original code:	movsx   ecx, word ptr [esi+16h]
	static NAKED void patch_633BF7()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 16h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_633BD0
	// Original code:	movsx   eax, word ptr [esi+18h]
	static NAKED void patch_633C1A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 18h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_633FC0
	// Original code:	movsx   eax, word ptr [esi+18h]
	static NAKED void patch_63400A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 18h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_634150
	// Original code:	mov     [esi+18h], ax
	static NAKED void patch_634195()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 18h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6342F0
	// Original code:	movsx   edx, word ptr [esi+18h]
	static NAKED void patch_63433E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 18h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_634740
	// Original code:	movsx   ecx, word ptr [ebp+22h]
	static NAKED void patch_634795()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_635200
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_63522D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_639CB0
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_639CF5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_640730
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_64087A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6408D0
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_640B37()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_642390
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_642429()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_642AE0
	// Original code:	movsx   edx, word ptr [ecx+22h]
	static NAKED void patch_642C3D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6432A0
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_6432BB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6432A0
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_643350()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_643A60
	// Original code:	mov     cx, [eax+22h]
	static NAKED void patch_643BE5()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_643A60
	// Original code:	cmp     cx, 460
	static NAKED void patch_643BE9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_643A60
	// Original code:	cmp     cx, 460
	static NAKED void patch_643BE9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_643A60
	// Original code:	cmp     cx, 539
	static NAKED void patch_643BF0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_643A60
	// Original code:	cmp     cx, 539
	static NAKED void patch_643BF0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_643A60
	// Original code:	cmp     cx, 447
	static NAKED void patch_643BF7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_643A60
	// Original code:	cmp     cx, 447
	static NAKED void patch_643BF7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_643A60
	// Original code:	cmp     cx, 417
	static NAKED void patch_643BFE_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_643A60
	// Original code:	cmp     cx, 417
	static NAKED void patch_643BFE_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_644470
	// Original code:	cmp     word ptr [eax+22h], 213h
	static NAKED void patch_64467D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_644470
	// Original code:	cmp     word ptr [eax+22h], 213h
	static NAKED void patch_64467D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_644470
	// Original code:	cmp     word ptr [eax+22h], 23Ah
	static NAKED void patch_64475D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 570;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_644470
	// Original code:	cmp     word ptr [eax+22h], 23Ah
	static NAKED void patch_64475D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 570;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_644470
	// Original code:	movsx   edx, word ptr [ebp+2Ch]
	static NAKED void patch_64493E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebp + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_644470
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_644B02()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_649160
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_649169()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_64B950
	// Original code:	cmp     word ptr [eax+22h], 1AFh
	static NAKED void patch_64BCB3_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 431;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_64B950
	// Original code:	cmp     word ptr [eax+22h], 1AFh
	static NAKED void patch_64BCB3_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 431;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_64CF40
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_64D049()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_64D710
	// Original code:	movsx   eax, word ptr [edi+2Ch]
	static NAKED void patch_64D889()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_64D710
	// Original code:	movsx   edx, word ptr [edx+2Ch]
	static NAKED void patch_64D8AA()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_64D9A0
	// Original code:	movsx   eax, word ptr [ecx+2Ch]
	static NAKED void patch_64DA3A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_64D9A0
	// Original code:	movsx   edx, word ptr [edx+2Ch]
	static NAKED void patch_64DA6A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_64DC70
	// Original code:	movsx   eax, word ptr [eax+2Ch]
	static NAKED void patch_64DD40()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_64E740
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_64E74A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_64FC10
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_64FC1B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_64FC10
	// Original code:	movsx   eax, word ptr [ebx+2Ch]
	static NAKED void patch_64FC68()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6504DA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	cmp     word ptr [eax+22h], 260h
	static NAKED void patch_650868_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 608;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	cmp     word ptr [eax+22h], 260h
	static NAKED void patch_650868_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 608;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	cmp     word ptr [esi+22h], 241h
	static NAKED void patch_650870_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	cmp     word ptr [esi+22h], 241h
	static NAKED void patch_650870_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	mov     si, [esi+22h]
	static NAKED void patch_6508ED()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	cmp     si, 460
	static NAKED void patch_6508F1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push esi;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	cmp     si, 460
	static NAKED void patch_6508F1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, si;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	cmp     si, 539
	static NAKED void patch_6508F8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push esi;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	cmp     si, 539
	static NAKED void patch_6508F8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, si;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	cmp     si, 447
	static NAKED void patch_6508FF_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push esi;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	cmp     si, 447
	static NAKED void patch_6508FF_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, si;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	cmp     si, 417
	static NAKED void patch_650906_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push esi;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6504C0
	// Original code:	cmp     si, 417
	static NAKED void patch_650906_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, si;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6509B0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6509B8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_650BB0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_650E05()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_651210
	// Original code:	cmp     word ptr [edi+22h], 241h
	static NAKED void patch_651233_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_651210
	// Original code:	cmp     word ptr [edi+22h], 241h
	static NAKED void patch_651233_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_651210
	// Original code:	movsx   ecx, word ptr [esi]
	static NAKED void patch_651342()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_651210
	// Original code:	movsx   edx, word ptr [esi]
	static NAKED void patch_65134D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6513A0
	// Original code:	movsx   edi, word ptr [ebp+2Ch]
	static NAKED void patch_6514D1()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ebp + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6513A0
	// Original code:	cmp     word ptr [esi+22h], 241h
	static NAKED void patch_6515DD_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6513A0
	// Original code:	cmp     word ptr [esi+22h], 241h
	static NAKED void patch_6515DD_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6513A0
	// Original code:	cmp     word ptr [esi+22h], 241h
	static NAKED void patch_651634_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6513A0
	// Original code:	cmp     word ptr [esi+22h], 241h
	static NAKED void patch_651634_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6513A0
	// Original code:	cmp     word ptr [esi+22h], 241h
	static NAKED void patch_651722_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6513A0
	// Original code:	cmp     word ptr [esi+22h], 241h
	static NAKED void patch_651722_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6564A0
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_65656F()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_402333
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_65D356()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_65E6F0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_65E6F4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_65E710
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_65E714()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_65E730
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_65E73C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_65E730
	// Original code:	movzx   ecx, ds:MI_GANG_DRINK
	static NAKED void patch_65E740()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD728;	// MI_GANG_DRINK
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_65E730
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_65E75B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_65E730
	// Original code:	movzx   ecx, ds:MI_GANG_SMOKE
	static NAKED void patch_65E786()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD72C;	// MI_GANG_SMOKE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_661160
	// Original code:	movsx   ecx, word ptr [edx+2Ch]
	static NAKED void patch_661164()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_662370
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_66271C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_662370
	// Original code:	movzx   ecx, ds:MI_GANG_DRINK
	static NAKED void patch_662720()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD728;	// MI_GANG_DRINK
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_662370
	// Original code:	movzx   edx, ds:MI_GANG_SMOKE
	static NAKED void patch_66273C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD72C;	// MI_GANG_SMOKE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_662370
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_6627FF()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_662370
	// Original code:	movzx   ecx, ds:MI_GANG_DRINK
	static NAKED void patch_662803()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD728;	// MI_GANG_DRINK
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_662370
	// Original code:	movzx   edx, ds:MI_GANG_SMOKE
	static NAKED void patch_66281B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD72C;	// MI_GANG_SMOKE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_662A10
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_663199()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_662A10
	// Original code:	movzx   edx, ds:MI_GANG_DRINK
	static NAKED void patch_66319D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD728;	// MI_GANG_DRINK
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_662A10
	// Original code:	movzx   ecx, ds:MI_GANG_SMOKE
	static NAKED void patch_6631D5()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD72C;	// MI_GANG_SMOKE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6641A0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_6641B1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_664770
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_664776()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_664BA0
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_664BEE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6669D0
	// Original code:	mov     ax, [esi+28h]
	static NAKED void patch_666EF7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 28h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_669D50
	// Original code:	mov     dx, [ecx+18h]
	static NAKED void patch_669D54()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 18h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_669FF0
	// Original code:	mov     cx, [esi+18h]
	static NAKED void patch_66A070()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 18h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_66F450
	// Original code:	mov     [esi+18h], ax
	static NAKED void patch_66F47C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 18h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_66F4C0
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_66F4CD()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_66F5C0
	// Original code:	mov     [esi+18h], ax
	static NAKED void patch_66F5E6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 18h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_66F6C0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_66F908()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_66F6C0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_66F97C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_66F6C0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_66F9EF()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_66F6C0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_66FA63()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_66F6C0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_66FAD7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_66F6C0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_66FB4B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_66F6C0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_66FBBF()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_66F6C0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_66FC33()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_670A70
	// Original code:	movsx   ebx, word ptr [esi+12h]
	static NAKED void patch_670A89()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 12h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebx, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_670A70
	// Original code:	movsx   edx, word ptr [esi+0Ch]
	static NAKED void patch_670AAD()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_670B00
	// Original code:	movsx   edx, word ptr [esi+12h]
	static NAKED void patch_670B71()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 12h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_670B00
	// Original code:	movsx   ecx, word ptr [esi+10h]
	static NAKED void patch_670B89()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 10h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_670B00
	// Original code:	movsx   eax, word ptr [esi+12h]
	static NAKED void patch_670BA8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 12h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_670B00
	// Original code:	movsx   eax, word ptr [esi+0Ch]
	static NAKED void patch_670C44()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_670B00
	// Original code:	movsx   edx, word ptr [esi+12h]
	static NAKED void patch_670C8E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 12h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_670B00
	// Original code:	movsx   edx, word ptr [esi+10h]
	static NAKED void patch_670C9E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 10h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_670B00
	// Original code:	movsx   eax, word ptr [esi+12h]
	static NAKED void patch_670CFE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 12h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_670B00
	// Original code:	movsx   edx, word ptr [esi+10h]
	static NAKED void patch_670D54()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 10h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_670D80
	// Original code:	movsx   eax, word ptr [ebx+12h]
	static NAKED void patch_670DC0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 12h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_674930
	// Original code:	mov     [esi+0Ch], ax
	static NAKED void patch_674979()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_674BB0
	// Original code:	movsx   ecx, word ptr [esi+0Ch]
	static NAKED void patch_674BEA()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_674BB0
	// Original code:	movsx   ecx, word ptr [esi+10h]
	static NAKED void patch_674BF3()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 10h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_674C30
	// Original code:	mov     [esi+18h], ax
	static NAKED void patch_674C84()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 18h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_675DD0
	// Original code:	movsx   ecx, word ptr [edx+2Ch]
	static NAKED void patch_675DD4()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_675FC0
	// Original code:	movsx   ecx, word ptr [edx+2Ch]
	static NAKED void patch_675FC8()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_676190
	// Original code:	movsx   ecx, word ptr [edx+2Ch]
	static NAKED void patch_676194()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6772E0
	// Original code:	movsx   edx, word ptr [ecx+2Ch]
	static NAKED void patch_6775AF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6772E0
	// Original code:	movsx   ecx, word ptr [eax+2Ch]
	static NAKED void patch_6775F9()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_677F10
	// Original code:	mov     [ecx+0Ch], ax
	static NAKED void patch_677F12()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [ecx + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_67A117
	// Original code:	mov     [esi+28h], bx
	static NAKED void patch_67A198()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ebx;
			lea eax, [esi + 28h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_67A390
	// Original code:	movsx   eax, word ptr [eax+2Ch]
	static NAKED void patch_67A3D4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_67C770
	// Original code:	movsx   edx, word ptr [ecx+22h]
	static NAKED void patch_67C82B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_67C770
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_67C836()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_67D590
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_67D5C2()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_67D590
	// Original code:	movsx   ebp, word ptr [esi]
	static NAKED void patch_67D70D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_67D590
	// Original code:	movsx   edi, word ptr [esi]
	static NAKED void patch_67D777()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_67DE15
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_67DFC6()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_680DC0
	// Original code:	mov     ax, [esi+28h]
	static NAKED void patch_681334()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 28h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_680DC0
	// Original code:	movsx   eax, word ptr [ecx+2Ch]
	static NAKED void patch_6813CD()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_682CB7
	// Original code:	mov     [esi+18h], dx
	static NAKED void patch_682CFE()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [esi + 18h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_682DA0
	// Original code:	mov     cx, [esi+18h]
	static NAKED void patch_682DD8()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 18h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_682E20
	// Original code:	mov     ax, [esi+18h]
	static NAKED void patch_682E4F()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 18h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_682E20
	// Original code:	movsx   eax, word ptr [esi+18h]
	static NAKED void patch_682E7F()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 18h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_688930
	// Original code:	mov     [esi+0Ah], bx
	static NAKED void patch_68899C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ebx;
			lea eax, [esi + 0Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_688A90
	// Original code:	movsx   eax, word ptr [esi+0Ah]
	static NAKED void patch_688B47()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_688A90
	// Original code:	mov     ax, [esi+0Ah]
	static NAKED void patch_689356()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_688A90
	// Original code:	mov     di, [esi+0Ah]   ; jumptable 00688B54 default case
	static NAKED void patch_6894A0()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_689640
	// Original code:	mov     [esi+0Ah], bp
	static NAKED void patch_6898A7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ebp;
			lea eax, [esi + 0Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6899F0
	// Original code:	movsx   eax, word ptr [edi+0Ah]
	static NAKED void patch_689BC1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6899F0
	// Original code:	mov     di, [edi+0Ah]
	static NAKED void patch_68A193()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_68A1D0
	// Original code:	movsx   eax, word ptr [edi+0Ah]
	static NAKED void patch_68A1DB()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_68AA70
	// Original code:	mov     ax, [esi+0Ah]
	static NAKED void patch_68ABB2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_68D911
	// Original code:	movsx   ecx, word ptr [edx+22h]
	static NAKED void patch_68D9F1()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_68DC60
	// Original code:	mov     dx, [eax+22h]
	static NAKED void patch_68DE62()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_692550
	// Original code:	movsx   ecx, word ptr [ecx+2Ch]
	static NAKED void patch_692562()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ecx + 2Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_692680
	// Original code:	mov     [esi+0Ch], dx
	static NAKED void patch_6926BF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [esi + 0Ch];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_693610
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_693686()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_695090
	// Original code:	movsx   eax, word ptr [esi+1Ch]
	static NAKED void patch_695564()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 1Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6958F0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_695988()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_695E40
	// Original code:	movsx   ecx, word ptr [esi+1Ch]
	static NAKED void patch_695F5F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 1Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_696940
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_6969C1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_696940
	// Original code:	movsx   ecx, word ptr [edi+22h]
	static NAKED void patch_696AEF()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_699120
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_69912A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_699230
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_69925A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_699570
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6995E8()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_699570
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6996FD()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_69A770
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_69A77A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_69B860
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_69B905()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A07A0
	// Original code:	movsx   eax, word ptr [ebp+22h]
	static NAKED void patch_6A07A6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	mov     cx, [edi+22h]
	static NAKED void patch_6A1480()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 443
	static NAKED void patch_6A1486_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 443
	static NAKED void patch_6A1486_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 486
	static NAKED void patch_6A1491_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 486
	static NAKED void patch_6A1491_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 406
	static NAKED void patch_6A1498_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 406
	static NAKED void patch_6A1498_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 524
	static NAKED void patch_6A149F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 524
	static NAKED void patch_6A149F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 592
	static NAKED void patch_6A14A6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 592
	static NAKED void patch_6A14A6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 530
	static NAKED void patch_6A14AD_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 530
	static NAKED void patch_6A14AD_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 443
	static NAKED void patch_6A14ED_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 443
	static NAKED void patch_6A14ED_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 486
	static NAKED void patch_6A14F4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 486
	static NAKED void patch_6A14F4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 406
	static NAKED void patch_6A14FB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 406
	static NAKED void patch_6A14FB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 524
	static NAKED void patch_6A1502_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 524
	static NAKED void patch_6A1502_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 592
	static NAKED void patch_6A1509_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 592
	static NAKED void patch_6A1509_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 544
	static NAKED void patch_6A1510_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 544;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 544
	static NAKED void patch_6A1510_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 544;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 530
	static NAKED void patch_6A1517_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     cx, 530
	static NAKED void patch_6A1517_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	mov     ax, [edi+22h]
	static NAKED void patch_6A155C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 524
	static NAKED void patch_6A1560_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 524
	static NAKED void patch_6A1560_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 544
	static NAKED void patch_6A156A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 544;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 544
	static NAKED void patch_6A156A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 544;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	movsx   ecx, ax
	static NAKED void patch_6A1574()
	{
		__asm
		{
			mov ecx, eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     word ptr [edi+22h], 212h
	static NAKED void patch_6A1648_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     word ptr [edi+22h], 212h
	static NAKED void patch_6A1648_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	mov     ax, [edi+22h]
	static NAKED void patch_6A173B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 486
	static NAKED void patch_6A173F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 486
	static NAKED void patch_6A173F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 406
	static NAKED void patch_6A179C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 406
	static NAKED void patch_6A179C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 592
	static NAKED void patch_6A17EF_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 592
	static NAKED void patch_6A17EF_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 443
	static NAKED void patch_6A1845_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 443
	static NAKED void patch_6A1845_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 530
	static NAKED void patch_6A186D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1460
	// Original code:	cmp     ax, 530
	static NAKED void patch_6A186D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1ED0
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_6A1F69()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A1ED0
	// Original code:	cmp     cx, 406
	static NAKED void patch_6A1F6D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1ED0
	// Original code:	cmp     cx, 406
	static NAKED void patch_6A1F6D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1ED0
	// Original code:	cmp     cx, 443
	static NAKED void patch_6A1F88_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1ED0
	// Original code:	cmp     cx, 443
	static NAKED void patch_6A1F88_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1ED0
	// Original code:	cmp     cx, 486
	static NAKED void patch_6A1FB6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1ED0
	// Original code:	cmp     cx, 486
	static NAKED void patch_6A1FB6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1ED0
	// Original code:	cmp     cx, 592
	static NAKED void patch_6A1FD1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1ED0
	// Original code:	cmp     cx, 592
	static NAKED void patch_6A1FD1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1ED0
	// Original code:	cmp     cx, 530
	static NAKED void patch_6A2002_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A1ED0
	// Original code:	cmp     cx, 530
	static NAKED void patch_6A2002_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2150
	// Original code:	mov     ax, [ecx+22h]
	static NAKED void patch_6A2162()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A2150
	// Original code:	cmp     ax, 406
	static NAKED void patch_6A2166_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2150
	// Original code:	cmp     ax, 406
	static NAKED void patch_6A2166_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2150
	// Original code:	cmp     ax, 443
	static NAKED void patch_6A218A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2150
	// Original code:	cmp     ax, 443
	static NAKED void patch_6A218A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2150
	// Original code:	cmp     ax, 486
	static NAKED void patch_6A21A4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2150
	// Original code:	cmp     ax, 486
	static NAKED void patch_6A21A4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2150
	// Original code:	cmp     ax, 592
	static NAKED void patch_6A21C8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2150
	// Original code:	cmp     ax, 592
	static NAKED void patch_6A21C8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2150
	// Original code:	cmp     ax, 530
	static NAKED void patch_6A21EC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2150
	// Original code:	cmp     ax, 530
	static NAKED void patch_6A21EC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2350
	// Original code:	mov     ax, [ecx+22h]
	static NAKED void patch_6A2350()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A2350
	// Original code:	cmp     ax, 480
	static NAKED void patch_6A2354_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 480;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2350
	// Original code:	cmp     ax, 480
	static NAKED void patch_6A2354_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 480;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2350
	// Original code:	cmp     ax, 439
	static NAKED void patch_6A236E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 439;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2350
	// Original code:	cmp     ax, 439
	static NAKED void patch_6A236E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 439;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2530
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_6A26BE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A2530
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_6A278E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A27F0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6A286D()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A27F0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_6A2932()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A2B10
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6A2C29_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2B10
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6A2C29_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2B10
	// Original code:	cmp     ax, 441
	static NAKED void patch_6A2E9F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2B10
	// Original code:	cmp     ax, 441
	static NAKED void patch_6A2E9F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2B10
	// Original code:	cmp     ax, 0FFFEh
	static NAKED void patch_6A2EA5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2B10
	// Original code:	cmp     ax, 0FFFEh
	static NAKED void patch_6A2EA5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2B10
	// Original code:	cmp     ax, 432
	static NAKED void patch_6A2EAB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2B10
	// Original code:	cmp     ax, 432
	static NAKED void patch_6A2EAB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A2F80
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6A2F84()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A3060
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_6A307B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A3060
	// Original code:	mov     cx, [ebx+22h]
	static NAKED void patch_6A3093()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A3060
	// Original code:	cmp     cx, 531
	static NAKED void patch_6A3097_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A3060
	// Original code:	cmp     cx, 531
	static NAKED void patch_6A3097_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A3060
	// Original code:	cmp     cx, 532
	static NAKED void patch_6A30A9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A3060
	// Original code:	cmp     cx, 532
	static NAKED void patch_6A30A9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A3060
	// Original code:	cmp     cx, 571
	static NAKED void patch_6A30B4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 571;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A3060
	// Original code:	cmp     cx, 571
	static NAKED void patch_6A30B4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 571;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A32B0
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6A32B7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A32B0
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6A32B7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A3670
	// Original code:	movsx   edx, word ptr [eax]
	static NAKED void patch_6A36B0()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A3BD0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6A3BD7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A40F0
	// Original code:	movsx   edx, bp
	static NAKED void patch_6A4345()
	{
		__asm
		{
			mov edx, ebp;
			retn;
		}
	}

	// Function: sub_6A4520
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6A4523()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A47F0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6A47FE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A47F0
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6A4913_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A47F0
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6A4913_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A4AF0
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6A4BAA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A4AF0
	// Original code:	cmp     ax, 441
	static NAKED void patch_6A4BAE_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A4AF0
	// Original code:	cmp     ax, 441
	static NAKED void patch_6A4BAE_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A4AF0
	// Original code:	cmp     ax, 432
	static NAKED void patch_6A4BB8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A4AF0
	// Original code:	cmp     ax, 432
	static NAKED void patch_6A4BB8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A4AF0
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6A4DFE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A4AF0
	// Original code:	cmp     ax, 441
	static NAKED void patch_6A4E02_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A4AF0
	// Original code:	cmp     ax, 441
	static NAKED void patch_6A4E02_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A4AF0
	// Original code:	cmp     ax, 432
	static NAKED void patch_6A4E0C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A4AF0
	// Original code:	cmp     ax, 432
	static NAKED void patch_6A4E0C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_403871
	// Original code:	cmp     eax, 208h
	static NAKED void patch_6A53BA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A6090
	// Original code:	mov     si, [ecx+22h]
	static NAKED void patch_6A6097()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A6090
	// Original code:	movsx   eax, si
	static NAKED void patch_6A609B()
	{
		__asm
		{
			mov eax, esi;
			retn;
		}
	}

	// Function: sub_6A6090
	// Original code:	cmp     si, 571
	static NAKED void patch_6A6128_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push esi;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 571;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A6090
	// Original code:	cmp     si, 571
	static NAKED void patch_6A6128_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, si;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 571;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A65D0
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_6A65D9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A65D0
	// Original code:	cmp     word ptr [edi+22h], 1B0h
	static NAKED void patch_6A6602_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A65D0
	// Original code:	cmp     word ptr [edi+22h], 1B0h
	static NAKED void patch_6A6602_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A65D0
	// Original code:	cmp     word ptr [edi+22h], 1B9h
	static NAKED void patch_6A68B6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A65D0
	// Original code:	cmp     word ptr [edi+22h], 1B9h
	static NAKED void patch_6A68B6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A65D0
	// Original code:	movsx   ecx, ax
	static NAKED void patch_6A68D5()
	{
		__asm
		{
			mov ecx, eax;
			retn;
		}
	}

	// Function: sub_6A65D0
	// Original code:	cmp     word ptr [edi+22h], 23Bh
	static NAKED void patch_6A6903_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 571;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A65D0
	// Original code:	cmp     word ptr [edi+22h], 23Bh
	static NAKED void patch_6A6903_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 571;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A65D0
	// Original code:	movsx   eax, word ptr [esi]
	static NAKED void patch_6A698A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A65D0
	// Original code:	cmp     word ptr [edi+22h], 1B0h
	static NAKED void patch_6A6995_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A65D0
	// Original code:	cmp     word ptr [edi+22h], 1B0h
	static NAKED void patch_6A6995_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_6A7174()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6A720B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 464
	static NAKED void patch_6A7211_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 464
	static NAKED void patch_6A7211_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 465
	static NAKED void patch_6A7217_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 465
	static NAKED void patch_6A7217_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 501
	static NAKED void patch_6A721D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 501
	static NAKED void patch_6A721D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 441
	static NAKED void patch_6A7223_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 441
	static NAKED void patch_6A7223_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 564
	static NAKED void patch_6A7229_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 564
	static NAKED void patch_6A7229_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6A7463()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 464
	static NAKED void patch_6A7467_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 464
	static NAKED void patch_6A7467_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 465
	static NAKED void patch_6A7471_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 465
	static NAKED void patch_6A7471_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 501
	static NAKED void patch_6A747B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 501
	static NAKED void patch_6A747B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 441
	static NAKED void patch_6A7485_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 441
	static NAKED void patch_6A7485_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 564
	static NAKED void patch_6A748F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7090
	// Original code:	cmp     ax, 564
	static NAKED void patch_6A748F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_6A8052()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     cx, 428
	static NAKED void patch_6A8056_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 428;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     cx, 428
	static NAKED void patch_6A8056_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 428;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     cx, 465
	static NAKED void patch_6A808F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     cx, 465
	static NAKED void patch_6A808F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     cx, 501
	static NAKED void patch_6A8096_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     cx, 501
	static NAKED void patch_6A8096_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     cx, 564
	static NAKED void patch_6A809D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     cx, 564
	static NAKED void patch_6A809D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     word ptr [ebp+22h], 1B0h
	static NAKED void patch_6A80BC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     word ptr [ebp+22h], 1B0h
	static NAKED void patch_6A80BC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ebp + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     word ptr [eax+22h], 1B0h
	static NAKED void patch_6A8380_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     word ptr [eax+22h], 1B0h
	static NAKED void patch_6A8380_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     word ptr [esi+22h], 1A8h
	static NAKED void patch_6A845E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 424;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A7650
	// Original code:	cmp     word ptr [esi+22h], 1A8h
	static NAKED void patch_6A845E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 424;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_406044
	// Original code:	movsx   ecx, word ptr [ebx+22h]
	static NAKED void patch_6A874D()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_406044
	// Original code:	movsx   eax, word ptr [ebx+598h]
	static NAKED void patch_6A8823()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 598h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_406044
	// Original code:	movsx   ecx, word ptr [ebp+22h]
	static NAKED void patch_6A8B6A()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6A8D4E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6A8D4E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6A8DE2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	cmp     ax, 447
	static NAKED void patch_6A8DE6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	cmp     ax, 447
	static NAKED void patch_6A8DE6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	cmp     ax, 417
	static NAKED void patch_6A8DF0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	cmp     ax, 417
	static NAKED void patch_6A8DF0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_6A8F18()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	cmp     cx, 447
	static NAKED void patch_6A8F1C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	cmp     cx, 447
	static NAKED void patch_6A8F1C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	cmp     cx, 417
	static NAKED void patch_6A8F23_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	cmp     cx, 417
	static NAKED void patch_6A8F23_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	cmp     cx, 539
	static NAKED void patch_6A8F70_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A8C00
	// Original code:	cmp     cx, 539
	static NAKED void patch_6A8F70_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6A9680
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6A98A0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6A9680
	// Original code:	movzx   edx, ds:MI_GRASSHOUSE
	static NAKED void patch_6A98A4()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6F4;	// MI_GRASSHOUSE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A9680
	// Original code:	movzx   edx, ds:MI_GRASSPLANT
	static NAKED void patch_6A98AF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6F8;	// MI_GRASSPLANT
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A9680
	// Original code:	movzx   esi, ds:MI_HARVESTERBODYPART2; jumptable 006A9A87 cases 1,3
	static NAKED void patch_6A9A8E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD6E8;	// MI_HARVESTERBODYPART2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A9680
	// Original code:	movzx   esi, ds:MI_HARVESTERBODYPART3; jumptable 006A9A87 case 2
	static NAKED void patch_6A9A97()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD6EC;	// MI_HARVESTERBODYPART3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A9680
	// Original code:	movzx   esi, ds:MI_HARVESTERBODYPART4; jumptable 006A9A87 case 5
	static NAKED void patch_6A9AA0()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD6F0;	// MI_HARVESTERBODYPART4
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6A9680
	// Original code:	movzx   esi, ds:MI_HARVESTERBODYPART1; jumptable 006A9A87 cases 0,6
	static NAKED void patch_6A9AA9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD6E4;	// MI_HARVESTERBODYPART1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6AA291
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6AA2DE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6AA291
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_6AA515()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6AA291
	// Original code:	cmp     cx, 532
	static NAKED void patch_6AA519_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AA291
	// Original code:	cmp     cx, 532
	static NAKED void patch_6AA519_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AA291
	// Original code:	cmp     cx, 513
	static NAKED void patch_6AA594_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 513;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AA291
	// Original code:	cmp     cx, 513
	static NAKED void patch_6AA594_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 513;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AA291
	// Original code:	cmp     cx, 571
	static NAKED void patch_6AA651_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 571;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AA291
	// Original code:	cmp     cx, 571
	static NAKED void patch_6AA651_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 571;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AA291
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6AA72D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AA291
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6AA72D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6AADE6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 0FFFEh
	static NAKED void patch_6AADEA_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 0FFFEh
	static NAKED void patch_6AADEA_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 539
	static NAKED void patch_6AAE25_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 539
	static NAKED void patch_6AAE25_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 441
	static NAKED void patch_6AAE2F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 441
	static NAKED void patch_6AAE2F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6AB350()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	lea     edi, [eax-197h]
	static NAKED void patch_6AB354()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	mov     ax, [esi+22h]   ; jumptable 006AB36D default case
	static NAKED void patch_6ABC71()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 441
	static NAKED void patch_6ABC75_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 441
	static NAKED void patch_6ABC75_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 0FFFEh
	static NAKED void patch_6ABC7B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 0FFFEh
	static NAKED void patch_6ABC7B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 432
	static NAKED void patch_6ABC81_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 432
	static NAKED void patch_6ABC81_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6ABC9D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 532
	static NAKED void patch_6ABCA1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 532
	static NAKED void patch_6ABCA1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 471
	static NAKED void patch_6ABCA7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 471;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 471
	static NAKED void patch_6ABCA7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 471;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6ABD0B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 432
	static NAKED void patch_6ABD0F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 432
	static NAKED void patch_6ABD0F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	movsx   ecx, ax
	static NAKED void patch_6ABD13()
	{
		__asm
		{
			mov ecx, eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6ABFC8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6ABFC8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6AC025_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6AC025_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	movsx   edx, ax
	static NAKED void patch_6AC0C9()
	{
		__asm
		{
			mov edx, eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     [esi+22h], di
	static NAKED void patch_6AC0E7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push edi;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     [esi+22h], di
	static NAKED void patch_6AC0E7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx edi, di;
			push edi;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     [esi+22h], di
	static NAKED void patch_6AC1C5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push edi;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     [esi+22h], di
	static NAKED void patch_6AC1C5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx edi, di;
			push edi;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6AC297()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 424
	static NAKED void patch_6AC29F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 424;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 424
	static NAKED void patch_6AC29F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 424;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 486
	static NAKED void patch_6AC40C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 486
	static NAKED void patch_6AC40C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 524
	static NAKED void patch_6AC43B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 524
	static NAKED void patch_6AC43B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 443
	static NAKED void patch_6AC4D9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 443
	static NAKED void patch_6AC4D9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 525
	static NAKED void patch_6AC507_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 525
	static NAKED void patch_6AC507_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 531
	static NAKED void patch_6AC6D9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 531
	static NAKED void patch_6AC6D9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 530
	static NAKED void patch_6AC71C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 530
	static NAKED void patch_6AC71C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 532
	static NAKED void patch_6AC7AB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 532
	static NAKED void patch_6AC7AB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 568
	static NAKED void patch_6ACA37_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 568;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 568
	static NAKED void patch_6ACA37_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 568;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 434
	static NAKED void patch_6ACA41_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 434;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 434
	static NAKED void patch_6ACA41_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 434;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 432
	static NAKED void patch_6ACA4B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 432
	static NAKED void patch_6ACA4B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 601
	static NAKED void patch_6ACA51_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 601;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 601
	static NAKED void patch_6ACA51_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 601;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 407
	static NAKED void patch_6ACA57_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 407;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 407
	static NAKED void patch_6ACA57_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 407;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 477
	static NAKED void patch_6ACA8D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 477;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_408C8C
	// Original code:	cmp     ax, 477
	static NAKED void patch_6ACA8D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 477;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6ACE70
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6ACEE1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6ACE70
	// Original code:	cmp     ax, 432
	static NAKED void patch_6ACEE7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6ACE70
	// Original code:	cmp     ax, 432
	static NAKED void patch_6ACEE7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6ACE70
	// Original code:	cmp     ax, 0FFFEh
	static NAKED void patch_6ACFAD_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6ACE70
	// Original code:	cmp     ax, 0FFFEh
	static NAKED void patch_6ACFAD_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6ACE70
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6AD23E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6ACE70
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6AD23E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6ACE70
	// Original code:	cmp     word ptr [esi+22h], 212h
	static NAKED void patch_6AD378_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6ACE70
	// Original code:	cmp     word ptr [esi+22h], 212h
	static NAKED void patch_6AD378_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AD690
	// Original code:	cmp     word ptr [esi+22h], 0FFFEh
	static NAKED void patch_6ADA46_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AD690
	// Original code:	cmp     word ptr [esi+22h], 0FFFEh
	static NAKED void patch_6ADA46_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AE0D0
	// Original code:	movsx   edx, word ptr [ebx+22h]; jumptable 006AE280 case 0
	static NAKED void patch_6AE287()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6AE0D0
	// Original code:	movsx   ecx, word ptr [ebx+22h]; jumptable 006AE280 case 1
	static NAKED void patch_6AE2CA()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6AE0D0
	// Original code:	movsx   eax, word ptr [ebx+22h]; jumptable 006AE280 case 2
	static NAKED void patch_6AE2FE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6AE0D0
	// Original code:	movsx   eax, word ptr [ebx+22h]; jumptable 006AE280 case 3
	static NAKED void patch_6AE32E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6AE0D0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6AE5D1()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6AE0D0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6AE60A()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6AE850
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6AE859()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6AE850
	// Original code:	cmp     ax, 564
	static NAKED void patch_6AE85D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AE850
	// Original code:	cmp     ax, 564
	static NAKED void patch_6AE85D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AE850
	// Original code:	cmp     ax, 432
	static NAKED void patch_6AE9C9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AE850
	// Original code:	cmp     ax, 432
	static NAKED void patch_6AE9C9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF110
	// Original code:	cmp     word ptr [eax+22h], 1B0h
	static NAKED void patch_6AF173_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF110
	// Original code:	cmp     word ptr [eax+22h], 1B0h
	static NAKED void patch_6AF173_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF1D0
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6AF1E6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	mov     ax, [ecx+22h]
	static NAKED void patch_6AF250()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 525
	static NAKED void patch_6AF257_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 525
	static NAKED void patch_6AF257_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 531
	static NAKED void patch_6AF262_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 531
	static NAKED void patch_6AF262_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 514
	static NAKED void patch_6AF26C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 514;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 514
	static NAKED void patch_6AF26C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 514;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 515
	static NAKED void patch_6AF272_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 515;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 515
	static NAKED void patch_6AF272_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 515;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 403
	static NAKED void patch_6AF278_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 403;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 403
	static NAKED void patch_6AF278_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 403;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 591
	static NAKED void patch_6AF27E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 591;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 591
	static NAKED void patch_6AF27E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 591;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 552
	static NAKED void patch_6AF284_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 552;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 552
	static NAKED void patch_6AF284_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 552;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     word ptr [edx+22h], 263h
	static NAKED void patch_6AF292_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 611;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     word ptr [edx+22h], 263h
	static NAKED void patch_6AF292_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 611;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 485
	static NAKED void patch_6AF29A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 485;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 485
	static NAKED void patch_6AF29A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 485;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 583
	static NAKED void patch_6AF2A0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 583;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 583
	static NAKED void patch_6AF2A0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 583;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 606
	static NAKED void patch_6AF2A6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 606;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 606
	static NAKED void patch_6AF2A6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 606;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 607
	static NAKED void patch_6AF2AC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 607;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 607
	static NAKED void patch_6AF2AC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 607;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	mov     ax, [edx+22h]
	static NAKED void patch_6AF2B6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 606
	static NAKED void patch_6AF2BA_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 606;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 606
	static NAKED void patch_6AF2BA_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 606;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 607
	static NAKED void patch_6AF2C0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 607;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 607
	static NAKED void patch_6AF2C0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 607;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 608
	static NAKED void patch_6AF2C6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 608;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 608
	static NAKED void patch_6AF2C6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 608;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	movsx   edx, word ptr [ecx+22h]
	static NAKED void patch_6AF31C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 531
	static NAKED void patch_6AF341_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     ax, 531
	static NAKED void patch_6AF341_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     word ptr [eax+22h], 262h
	static NAKED void patch_6AF35E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 610;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	cmp     word ptr [eax+22h], 262h
	static NAKED void patch_6AF35E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 610;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AF250
	// Original code:	movsx   edx, word ptr [ecx+22h]
	static NAKED void patch_6AF37A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6AFB10
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6AFB44_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AFB10
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6AFB44_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AFB10
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6AFFEA_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AFB10
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6AFFEA_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AFB10
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6B0017_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AFB10
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6B0017_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AFB10
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6B0298_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AFB10
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6B0298_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6AFB10
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_6B0577()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6B0690
	// Original code:	mov     di, [esi+22h]
	static NAKED void patch_6B078E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6B0690
	// Original code:	cmp     di, 501
	static NAKED void patch_6B0798_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push edi;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0690
	// Original code:	cmp     di, 501
	static NAKED void patch_6B0798_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, di;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0690
	// Original code:	cmp     di, 465
	static NAKED void patch_6B079F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push edi;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0690
	// Original code:	cmp     di, 465
	static NAKED void patch_6B079F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, di;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0690
	// Original code:	cmp     di, 520
	static NAKED void patch_6B0842_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push edi;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0690
	// Original code:	cmp     di, 520
	static NAKED void patch_6B0842_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, di;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	movzx   ecx, ds:MI_HYDRAULICS
	static NAKED void patch_6B0BCD()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD76C;	// MI_HYDRAULICS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6B0CF0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6B0CF0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6B0EE2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 525
	static NAKED void patch_6B0EE6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 525
	static NAKED void patch_6B0EE6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 531
	static NAKED void patch_6B0F0F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 531
	static NAKED void patch_6B0F0F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6B0F47()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 598
	static NAKED void patch_6B0F51_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 598;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 598
	static NAKED void patch_6B0F51_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 598;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 419
	static NAKED void patch_6B0F5E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 419;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 419
	static NAKED void patch_6B0F5E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 419;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 409
	static NAKED void patch_6B0F64_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 409;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 409
	static NAKED void patch_6B0F64_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 409;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     word ptr [esi+22h], 220h
	static NAKED void patch_6B0FA8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 544;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     word ptr [esi+22h], 220h
	static NAKED void patch_6B0FA8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 544;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6B11D5()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 0FFFEh
	static NAKED void patch_6B11D9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 0FFFEh
	static NAKED void patch_6B11D9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     word ptr [esi+22h], 0FFFEh
	static NAKED void patch_6B1227_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     word ptr [esi+22h], 0FFFEh
	static NAKED void patch_6B1227_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, UNKNOWN_MODEL_ID_MINUS_2;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 432
	static NAKED void patch_6B12D6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B0A97
	// Original code:	cmp     ax, 432
	static NAKED void patch_6B12D6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1350
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6B1382()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6B1350
	// Original code:	movsx   edx, ax
	static NAKED void patch_6B13D9()
	{
		__asm
		{
			mov edx, eax;
			retn;
		}
	}

	// Function: sub_6B1480
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6B14B2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B1480
	// Original code:	movsx   edx, ax
	static NAKED void patch_6B1509()
	{
		__asm
		{
			mov edx, eax;
			retn;
		}
	}

	// Function: sub_6B1600
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_6B16A3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6B1600
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_6B16EB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6B19A2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 420
	static NAKED void patch_6B19A6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 420;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 420
	static NAKED void patch_6B19A6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 420;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 438
	static NAKED void patch_6B19AC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 438;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 438
	static NAKED void patch_6B19AC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 438;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_6B1E26()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     cx, 447
	static NAKED void patch_6B1E2A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     cx, 447
	static NAKED void patch_6B1E2A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     cx, 417
	static NAKED void patch_6B1E31_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     cx, 417
	static NAKED void patch_6B1E31_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     cx, 539
	static NAKED void patch_6B1E59_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     cx, 539
	static NAKED void patch_6B1E59_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6B1F4B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 407
	static NAKED void patch_6B1F4F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 407;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 407
	static NAKED void patch_6B1F4F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 407;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 601
	static NAKED void patch_6B1F55_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 601;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 601
	static NAKED void patch_6B1F55_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 601;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6B1F77()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 432
	static NAKED void patch_6B1F7B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 432
	static NAKED void patch_6B1F7B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 564
	static NAKED void patch_6B1F85_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 564
	static NAKED void patch_6B1F85_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 443
	static NAKED void patch_6B1F8F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 443
	static NAKED void patch_6B1F8F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 443;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 486
	static NAKED void patch_6B1F95_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 486
	static NAKED void patch_6B1F95_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 406
	static NAKED void patch_6B1F9B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 406
	static NAKED void patch_6B1F9B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 524
	static NAKED void patch_6B1FA1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 524
	static NAKED void patch_6B1FA1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 524;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 592
	static NAKED void patch_6B1FA7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 592
	static NAKED void patch_6B1FA7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 530
	static NAKED void patch_6B1FAD_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 530
	static NAKED void patch_6B1FAD_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 525
	static NAKED void patch_6B1FB3_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 525
	static NAKED void patch_6B1FB3_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 531
	static NAKED void patch_6B1FB9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     ax, 531
	static NAKED void patch_6B1FB9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6B217D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6B217D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6B2239_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6B2239_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6B284B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6B284B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6B2B93_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6B2B93_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 1A7h
	static NAKED void patch_6B2BD4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 423;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 1A7h
	static NAKED void patch_6B2BD4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 423;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6B356A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6B356A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 214h
	static NAKED void patch_6B36C5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 214h
	static NAKED void patch_6B36C5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6B36D4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B1880
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6B36D4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3780
	// Original code:	cmp     word ptr [esi+22h], 1E8h
	static NAKED void patch_6B3808_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 488;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3780
	// Original code:	cmp     word ptr [esi+22h], 1E8h
	static NAKED void patch_6B3808_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 488;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3780
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6B385D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B3780
	// Original code:	cmp     ax, 564
	static NAKED void patch_6B3861_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3780
	// Original code:	cmp     ax, 564
	static NAKED void patch_6B3861_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3780
	// Original code:	cmp     ax, 441
	static NAKED void patch_6B386B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3780
	// Original code:	cmp     ax, 441
	static NAKED void patch_6B386B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3780
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6B3B3D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B3780
	// Original code:	cmp     ax, 564
	static NAKED void patch_6B3B43_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3780
	// Original code:	cmp     ax, 564
	static NAKED void patch_6B3B43_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3780
	// Original code:	cmp     ax, 441
	static NAKED void patch_6B3B4D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3780
	// Original code:	cmp     ax, 441
	static NAKED void patch_6B3B4D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3BB0
	// Original code:	cmp     word ptr [esi+22h], 1E8h; jumptable 006B3BE6 default case
	static NAKED void patch_6B3BF9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 488;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3BB0
	// Original code:	cmp     word ptr [esi+22h], 1E8h; jumptable 006B3BE6 default case
	static NAKED void patch_6B3BF9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 488;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3BB0
	// Original code:	cmp     word ptr [esi+22h], 1B9h
	static NAKED void patch_6B3C61_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3BB0
	// Original code:	cmp     word ptr [esi+22h], 1B9h
	static NAKED void patch_6B3C61_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3F70
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_6B3F79()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B3F70
	// Original code:	mov     bp, [ebx+22h]
	static NAKED void patch_6B3FFF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebp, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6B3F70
	// Original code:	cmp     bp, 441
	static NAKED void patch_6B4003_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebp;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3F70
	// Original code:	cmp     bp, 441
	static NAKED void patch_6B4003_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, bp;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B3F70
	// Original code:	movsx   edx, bp
	static NAKED void patch_6B40FD()
	{
		__asm
		{
			mov edx, ebp;
			retn;
		}
	}

	// Function: sub_6B4410
	// Original code:	mov     ax, [ebx+22h]
	static NAKED void patch_6B44AA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B4410
	// Original code:	cmp     ax, 525
	static NAKED void patch_6B44AE_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4410
	// Original code:	cmp     ax, 525
	static NAKED void patch_6B44AE_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4410
	// Original code:	cmp     ax, 531
	static NAKED void patch_6B44E4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4410
	// Original code:	cmp     ax, 531
	static NAKED void patch_6B44E4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     word ptr [esi+22h], 1B9h
	static NAKED void patch_6B4964_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     word ptr [esi+22h], 1B9h
	static NAKED void patch_6B4964_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6B4ADB()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     ax, 420
	static NAKED void patch_6B4ADF_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 420;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     ax, 420
	static NAKED void patch_6B4ADF_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 420;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     ax, 438
	static NAKED void patch_6B4AE9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 438;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     ax, 438
	static NAKED void patch_6B4AE9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 438;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     word ptr [esi+22h], 1B9h
	static NAKED void patch_6B4BF0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     word ptr [esi+22h], 1B9h
	static NAKED void patch_6B4BF0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_6B4CE8()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     cx, 539
	static NAKED void patch_6B4CEC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     cx, 539
	static NAKED void patch_6B4CEC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     cx, 601
	static NAKED void patch_6B4CF8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 601;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     cx, 601
	static NAKED void patch_6B4CF8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 601;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     cx, 432
	static NAKED void patch_6B4CFF_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     cx, 432
	static NAKED void patch_6B4CFF_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6B539C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     ax, 441
	static NAKED void patch_6B53A0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     ax, 441
	static NAKED void patch_6B53A0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     ax, 495
	static NAKED void patch_6B53AA_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 495;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     ax, 495
	static NAKED void patch_6B53AA_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 495;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     ax, 424
	static NAKED void patch_6B53B4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 424;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B4800
	// Original code:	cmp     ax, 424
	static NAKED void patch_6B53B4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 424;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B5990
	// Original code:	movsx   ecx, word ptr [ecx+22h]
	static NAKED void patch_6B59C2()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6B5A10
	// Original code:	cmp     word ptr [edi+22h], 1D4h
	static NAKED void patch_6B5BC2_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 468;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B5A10
	// Original code:	cmp     word ptr [edi+22h], 1D4h
	static NAKED void patch_6B5BC2_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 468;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B67E0
	// Original code:	movsx   ecx, word ptr [ebx+22h]
	static NAKED void patch_6B67E6()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6B6950
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6B695E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B6950
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6B6C86_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B6950
	// Original code:	cmp     word ptr [esi+22h], 1B0h
	static NAKED void patch_6B6C86_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 432;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B7F90
	// Original code:	mov     cx, [ebx+22h]
	static NAKED void patch_6B8043()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6B7F90
	// Original code:	movsx   edx, cx
	static NAKED void patch_6B8049()
	{
		__asm
		{
			mov edx, ecx;
			retn;
		}
	}

	// Function: sub_6B7F90
	// Original code:	cmp     cx, 510
	static NAKED void patch_6B80AB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 510;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B7F90
	// Original code:	cmp     cx, 510
	static NAKED void patch_6B80AB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 510;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B7F90
	// Original code:	cmp     cx, 509
	static NAKED void patch_6B80D4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 509;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B7F90
	// Original code:	cmp     cx, 509
	static NAKED void patch_6B80D4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 509;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6B89B0
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_6B89B6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B89B0
	// Original code:	movsx   eax, word ptr [esi]
	static NAKED void patch_6B8E9A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6B9250
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6B9276()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6B9250
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6BBC72()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6BC930
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6BC938()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6BD090
	// Original code:	cmp     word ptr [esi+22h], 20Bh
	static NAKED void patch_6BD40F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 523;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6BD090
	// Original code:	cmp     word ptr [esi+22h], 20Bh
	static NAKED void patch_6BD40F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 523;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6BD090
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_6BD67C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6BDEA0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6BE005()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6BF437
	// Original code:	movsx   edx, word ptr [ebp+4Ah]
	static NAKED void patch_6BF491()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebp + 4Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6BFA30
	// Original code:	cmp     word ptr [esi+22h], 1FEh
	static NAKED void patch_6BFA86_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 510;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6BFA30
	// Original code:	cmp     word ptr [esi+22h], 1FEh
	static NAKED void patch_6BFA86_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 510;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6BFA30
	// Original code:	cmp     word ptr [esi+22h], 1FEh
	static NAKED void patch_6BFAC3_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 510;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6BFA30
	// Original code:	cmp     word ptr [esi+22h], 1FEh
	static NAKED void patch_6BFAC3_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 510;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6BFB50
	// Original code:	cmp     word ptr [esi+22h], 1FEh
	static NAKED void patch_6BFCFC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 510;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6BFB50
	// Original code:	cmp     word ptr [esi+22h], 1FEh
	static NAKED void patch_6BFCFC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 510;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C0810
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_6C0B38()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6C1470
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6C1478()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C1470
	// Original code:	cmp     word ptr [esi+22h], 1D4h
	static NAKED void patch_6C1575_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 468;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C1470
	// Original code:	cmp     word ptr [esi+22h], 1D4h
	static NAKED void patch_6C1575_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 468;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C2B90
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_6C2C08()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C2B90
	// Original code:	add     eax, 0FFFFFE42h
	static NAKED void patch_6C2C0C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C2B90
	// Original code:	mov     ax, [edi+22h]
	static NAKED void patch_6C2D33()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C2B90
	// Original code:	cmp     ax, 417
	static NAKED void patch_6C2D37_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C2B90
	// Original code:	cmp     ax, 417
	static NAKED void patch_6C2D37_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C2B90
	// Original code:	cmp     ax, 460
	static NAKED void patch_6C2D60_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C2B90
	// Original code:	cmp     ax, 460
	static NAKED void patch_6C2D60_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C3030
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_6C318E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C3030
	// Original code:	add     eax, 0FFFFFE42h
	static NAKED void patch_6C3192()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C4400
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6C440A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6C4F13()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C4F17_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C4F17_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C4F1D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C4F1D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6C4F66()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 447
	static NAKED void patch_6C4F6A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 447
	static NAKED void patch_6C4F6A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 417
	static NAKED void patch_6C4F70_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 417
	static NAKED void patch_6C4F70_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6C50B3()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C50B7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C50B7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C50C5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C50C5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 469
	static NAKED void patch_6C50CB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 469;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 469
	static NAKED void patch_6C50CB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 469;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 447
	static NAKED void patch_6C50D1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 447
	static NAKED void patch_6C50D1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 425
	static NAKED void patch_6C50D7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 425;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 425
	static NAKED void patch_6C50D7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 425;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6C5200()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C5204_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C5204_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C520E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C4E60
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C520E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6C5442()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6C55E4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C55E8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C55E8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C55EE_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C55EE_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_6C5605()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     cx, 469
	static NAKED void patch_6C5609_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 469;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     cx, 469
	static NAKED void patch_6C5609_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 469;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     cx, 447
	static NAKED void patch_6C5610_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     cx, 447
	static NAKED void patch_6C5610_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     cx, 487
	static NAKED void patch_6C5617_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 487;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     cx, 487
	static NAKED void patch_6C5617_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 487;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     cx, 488
	static NAKED void patch_6C561E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 488;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     cx, 488
	static NAKED void patch_6C561E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 488;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     cx, 497
	static NAKED void patch_6C5625_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 497;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     cx, 497
	static NAKED void patch_6C5625_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 497;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     cx, 417
	static NAKED void patch_6C568A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C5420
	// Original code:	cmp     cx, 417
	static NAKED void patch_6C568A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 417;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6C6D54()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C6D58_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C6D58_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C6D5E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C6D5E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     word ptr [esi+22h], 1E8h
	static NAKED void patch_6C6DEC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 488;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     word ptr [esi+22h], 1E8h
	static NAKED void patch_6C6DEC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 488;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6C6E51()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C6E55_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C6E55_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C6E5F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C6E5F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6C6FD8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C6FDF_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     ax, 465
	static NAKED void patch_6C6FDF_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 465;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C6FE5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C6D30
	// Original code:	cmp     ax, 501
	static NAKED void patch_6C6FE5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 501;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C7050
	// Original code:	cmp     word ptr [esi+22h], 1F1h
	static NAKED void patch_6C7172_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 497;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C7050
	// Original code:	cmp     word ptr [esi+22h], 1F1h
	static NAKED void patch_6C7172_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 497;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C79A0
	// Original code:	cmp     [eax+22h], cx
	static NAKED void patch_6C79D5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C79A0
	// Original code:	cmp     [eax+22h], cx
	static NAKED void patch_6C79D5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C79A0
	// Original code:	cmp     [eax+22h], cx
	static NAKED void patch_6C79FE_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C79A0
	// Original code:	cmp     [eax+22h], cx
	static NAKED void patch_6C79FE_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C79A0
	// Original code:	cmp     [edx+22h], cx
	static NAKED void patch_6C7A65_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C79A0
	// Original code:	cmp     [edx+22h], cx
	static NAKED void patch_6C7A65_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			movzx eax, word ptr[edx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C79A0
	// Original code:	cmp     [edx+22h], cx
	static NAKED void patch_6C7A7B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C79A0
	// Original code:	cmp     [edx+22h], cx
	static NAKED void patch_6C7A7B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ecx, cx;
			push ecx;
			movzx eax, word ptr[edx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C7DE0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6C7E7F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6C7DE0
	// Original code:	cmp     word ptr [esi+22h], 196h
	static NAKED void patch_6C7F30_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C7DE0
	// Original code:	cmp     word ptr [esi+22h], 196h
	static NAKED void patch_6C7F30_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C7FB0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6C7FB8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C8E20
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6C8E54_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C8E20
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6C8E54_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C8E20
	// Original code:	cmp     word ptr [esi+22h], 208h
	static NAKED void patch_6C9101_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C8E20
	// Original code:	cmp     word ptr [esi+22h], 208h
	static NAKED void patch_6C9101_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C9260
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6C926D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C9260
	// Original code:	cmp     ax, 512
	static NAKED void patch_6C9271_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 512;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C9260
	// Original code:	cmp     ax, 512
	static NAKED void patch_6C9271_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 512;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C9260
	// Original code:	cmp     ax, 513
	static NAKED void patch_6C9277_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 513;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C9260
	// Original code:	cmp     ax, 513
	static NAKED void patch_6C9277_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 513;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C9260
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6C92EC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C9260
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6C92EC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C9260
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6C934D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C9260
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6C934D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6C94D1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6C94FB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6C94FB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     word ptr [esi+22h], 250h
	static NAKED void patch_6C95B8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     word ptr [esi+22h], 250h
	static NAKED void patch_6C95B8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     word ptr [esi+22h], 208h
	static NAKED void patch_6C968E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     word ptr [esi+22h], 208h
	static NAKED void patch_6C968E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6C97E6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6C97E6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6C9D7E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	add     eax, 0FFFFFE24h
	static NAKED void patch_6C9D82()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	mov     ax, [esi+22h]   ; jumptable 006C9DAA default case
	static NAKED void patch_6C9EE3()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 592
	static NAKED void patch_6C9EE7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 592
	static NAKED void patch_6C9EE7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 520
	static NAKED void patch_6C9F1C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 520
	static NAKED void patch_6C9F1C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 539
	static NAKED void patch_6CA2E9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 539
	static NAKED void patch_6CA2E9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6CA70E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 539
	static NAKED void patch_6CA716_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 539
	static NAKED void patch_6CA716_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 577
	static NAKED void patch_6CA727_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 577
	static NAKED void patch_6CA727_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 592
	static NAKED void patch_6CA72D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 592
	static NAKED void patch_6CA72D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6CA750()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 539
	static NAKED void patch_6CA754_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 539
	static NAKED void patch_6CA754_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 464
	static NAKED void patch_6CA75E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 464
	static NAKED void patch_6CA75E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6CA945()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 512
	static NAKED void patch_6CA949_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 512;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 512
	static NAKED void patch_6CA949_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 512;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 513
	static NAKED void patch_6CA9DB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 513;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     ax, 513
	static NAKED void patch_6CA9DB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 513;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6CAA93_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6C94A0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6CAA93_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CACB0
	// Original code:	cmp     word ptr [esi+22h], 201h
	static NAKED void patch_6CACF0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 513;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CACB0
	// Original code:	cmp     word ptr [esi+22h], 201h
	static NAKED void patch_6CACF0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 513;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CADD0
	// Original code:	cmp     [esi+22h], bp
	static NAKED void patch_6CB176_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebp;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CADD0
	// Original code:	cmp     [esi+22h], bp
	static NAKED void patch_6CB176_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ebp, bp;
			push ebp;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CADD0
	// Original code:	cmp     [esi+22h], bp
	static NAKED void patch_6CB281_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebp;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CADD0
	// Original code:	cmp     [esi+22h], bp
	static NAKED void patch_6CB281_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ebp, bp;
			push ebp;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CADD0
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6CB38E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CADD0
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6CB38E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CB7C0
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6CB977_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CB7C0
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6CB977_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CB7C0
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6CC20F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CB7C0
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6CC20F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CB7C0
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_6CC318()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6CB7C0
	// Original code:	cmp     cx, 464
	static NAKED void patch_6CC31C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CB7C0
	// Original code:	cmp     cx, 464
	static NAKED void patch_6CC31C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CB7C0
	// Original code:	cmp     cx, 520
	static NAKED void patch_6CC3B1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CB7C0
	// Original code:	cmp     cx, 520
	static NAKED void patch_6CC3B1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, cx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CC4B0
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6CC4C4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CC4B0
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6CC4C4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CCCF0
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6CCD15_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CCCF0
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6CCD15_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CCCF0
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6CCE99_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CCCF0
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6CCE99_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CCCF0
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6CD023_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CCCF0
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6CD023_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CD2F0
	// Original code:	cmp     word ptr [eax+22h], 241h
	static NAKED void patch_6CD8B4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CD2F0
	// Original code:	cmp     word ptr [eax+22h], 241h
	static NAKED void patch_6CD8B4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 577;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CD2F0
	// Original code:	cmp     word ptr [eax+22h], 250h
	static NAKED void patch_6CD8CB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CD2F0
	// Original code:	cmp     word ptr [eax+22h], 250h
	static NAKED void patch_6CD8CB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 592;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CEAD0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6CEAF1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6CEEA0
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6CEEA0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6CEEA0
	// Original code:	cmp     word ptr [eax+22h], 20Dh
	static NAKED void patch_6CEED5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CEEA0
	// Original code:	cmp     word ptr [eax+22h], 20Dh
	static NAKED void patch_6CEED5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CF030
	// Original code:	cmp     word ptr [edi+22h], 262h
	static NAKED void patch_6CF055_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 610;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CF030
	// Original code:	cmp     word ptr [edi+22h], 262h
	static NAKED void patch_6CF055_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 610;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CF1A0
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_6CF1A6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6CFAC0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6CFAE1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6CFAC0
	// Original code:	cmp     word ptr [esi+22h], 262h
	static NAKED void patch_6CFC41_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 610;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CFAC0
	// Original code:	cmp     word ptr [esi+22h], 262h
	static NAKED void patch_6CFC41_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 610;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CFD60
	// Original code:	mov     ax, [ecx+22h]
	static NAKED void patch_6CFD6B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6CFD60
	// Original code:	cmp     ax, 606
	static NAKED void patch_6CFD6F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 606;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CFD60
	// Original code:	cmp     ax, 606
	static NAKED void patch_6CFD6F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 606;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CFD60
	// Original code:	cmp     ax, 607
	static NAKED void patch_6CFD75_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 607;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CFD60
	// Original code:	cmp     ax, 607
	static NAKED void patch_6CFD75_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 607;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6CFD60
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6CFD8E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D03A7
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6D03ED()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D03A7
	// Original code:	cmp     ax, 606
	static NAKED void patch_6D03F1_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 606;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D03A7
	// Original code:	cmp     ax, 606
	static NAKED void patch_6D03F1_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 606;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D03A7
	// Original code:	cmp     ax, 607
	static NAKED void patch_6D040F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 607;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D03A7
	// Original code:	cmp     ax, 607
	static NAKED void patch_6D040F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 607;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D0AC0
	// Original code:	movsx   eax, word ptr [ecx+eax*2+2FAh]
	static NAKED void patch_6D0AC5()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + eax * 2 + 2FAh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0B70
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_6D0B73()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0B70
	// Original code:	mov     dx, [edi+ecx*2+2FAh]
	static NAKED void patch_6D0B93()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + ecx * 2 + 2FAh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0B70
	// Original code:	cmp     dx, [ebx+598h]
	static NAKED void patch_6D0B9B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [ebx + 598h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D0BC0
	// Original code:	movsx   eax, word ptr [esi+598h]
	static NAKED void patch_6D0BC3()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 598h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0BC0
	// Original code:	mov     [esi+598h], di
	static NAKED void patch_6D0BEB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edi;
			lea eax, [esi + 598h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0BC0
	// Original code:	mov     [esi+59Ah], di
	static NAKED void patch_6D0BF2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edi;
			lea eax, [esi + 59Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0C00
	// Original code:	cmp     ax, 0FFFFh
	static NAKED void patch_6D0C13_1()
	{
		__asm
		{
			cmp eax, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: sub_6D0C00
	// Original code:	mov     word ptr [esi+598h], 0FFFFh
	static NAKED void patch_6D0C2F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push UNDEFINED_FILE_ID_INT32;
			lea eax, [esi + 598h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0C00
	// Original code:	mov     word ptr [esi+59Ah], 0FFFFh
	static NAKED void patch_6D0C38()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push UNDEFINED_FILE_ID_INT32;
			lea eax, [esi + 59Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0C00
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6D0C45()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0C00
	// Original code:	movsx   edx, ax
	static NAKED void patch_6D0C49()
	{
		__asm
		{
			mov edx, eax;
			retn;
		}
	}

	// Function: sub_6D0C00
	// Original code:	movsx   edi, word ptr [eax+edx*2+2FAh]
	static NAKED void patch_6D0C54()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + edx * 2 + 2FAh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0C00
	// Original code:	movsx   eax, word ptr [esi+598h]
	static NAKED void patch_6D0C5C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 598h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0C00
	// Original code:	mov     [esi+598h], di
	static NAKED void patch_6D0C7F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edi;
			lea eax, [esi + 598h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0C00
	// Original code:	mov     [esi+59Ah], di
	static NAKED void patch_6D0C86()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edi;
			lea eax, [esi + 59Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0E20
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_6D0E45()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D0E60
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6D0E72()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D16A0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6D16EE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D16A0
	// Original code:	add     eax, 0FFFFFE60h
	static NAKED void patch_6D16FB()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D1950
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_6D199F()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D1AA0
	// Original code:	mov     ax, [edi+22h]
	static NAKED void patch_6D1ABA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D1AA0
	// Original code:	cmp     ax, 420
	static NAKED void patch_6D1AC0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 420;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D1AA0
	// Original code:	cmp     ax, 420
	static NAKED void patch_6D1AC0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 420;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D1AA0
	// Original code:	cmp     ax, 438
	static NAKED void patch_6D1AC6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 438;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D1AA0
	// Original code:	cmp     ax, 438
	static NAKED void patch_6D1AC6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 438;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D1AA0
	// Original code:	cmp     ax, 409
	static NAKED void patch_6D1AD0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 409;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D1AA0
	// Original code:	cmp     ax, 409
	static NAKED void patch_6D1AD0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 409;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D1AA0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6D1B15()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D1AA0
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_6D1B64()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D1AA0
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_6D1BA0()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D1C00
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_6D1C16()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D1C60
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_6D1C6A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D22F0
	// Original code:	movsx   ecx, word ptr [ecx+22h]
	static NAKED void patch_6D2311()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D2370
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6D2370()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D2370
	// Original code:	add     eax, 0FFFFFE55h
	static NAKED void patch_6D2374()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D2740
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6D274C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D2740
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6D274C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D2A80
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6D2AFE()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D30E0
	// Original code:	movzx   ecx, ds:MI_NITRO_BOTTLE_LARGE
	static NAKED void patch_6D3198()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD764;	// MI_NITRO_BOTTLE_LARGE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D30E0
	// Original code:	movzx   edx, ds:MI_NITRO_BOTTLE_DOUBLE
	static NAKED void patch_6D31B3()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD768;	// MI_NITRO_BOTTLE_DOUBLE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D30E0
	// Original code:	movzx   eax, ds:MI_NITRO_BOTTLE_SMALL
	static NAKED void patch_6D31CF()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD760;	// MI_NITRO_BOTTLE_SMALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D30E0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6D31E8()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D3210
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6D32DB()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D3650
	// Original code:	movzx   eax, ds:MI_STEREO_UPGRADE
	static NAKED void patch_6D36AC()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD770;	// MI_STEREO_UPGRADE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D3650
	// Original code:	movzx   eax, ds:MI_HYDRAULICS
	static NAKED void patch_6D36C7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD76C;	// MI_HYDRAULICS
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D3650
	// Original code:	movzx   eax, ds:MI_NITRO_BOTTLE_SMALL
	static NAKED void patch_6D36E2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push 0x8CD760;	// MI_NITRO_BOTTLE_SMALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_408121
	// Original code:	movsx   edx, word ptr [ebx+22h]
	static NAKED void patch_6D396D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D39E0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6D3A1D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D3E00
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6D3E00()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D3E00
	// Original code:	add     eax, 0FFFFFE57h
	static NAKED void patch_6D3E04()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D3F30
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6D3F30()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D3F30
	// Original code:	add     eax, 0FFFFFE57h
	static NAKED void patch_6D3F34()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D40E0
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6D4125()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D40E0
	// Original code:	add     eax, 0FFFFFE57h
	static NAKED void patch_6D4129()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D4290
	// Original code:	mov     dx, [ecx+22h]
	static NAKED void patch_6D4293()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D4290
	// Original code:	movsx   ecx, dx
	static NAKED void patch_6D4297()
	{
		__asm
		{
			mov ecx, edx;
			retn;
		}
	}

	// Function: sub_6D4290
	// Original code:	lea     eax, [ecx-425]
	static NAKED void patch_6D42FE()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			mov ecx, eax;
			add esp, 4;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN8CVehicle26GetPlaneOrdnanceRateOfFireE13eOrdnanceType
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6D45D5()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN8CVehicle26GetPlaneOrdnanceRateOfFireE13eOrdnanceType
	// Original code:	add     eax, 0FFFFFE57h
	static NAKED void patch_6D45D9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D46E0
	// Original code:	movsx   edi, word ptr [ecx+22h]
	static NAKED void patch_6D46E5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D46E0
	// Original code:	lea     eax, [edi-1A9h]
	static NAKED void patch_6D474B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edi;
			call GetModelIDforModelSpecialFeatures;
			mov edi, eax;
			add esp, 4;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D4900
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6D4900()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D4900
	// Original code:	add     eax, 0FFFFFE57h
	static NAKED void patch_6D4904()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D4D30
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6D4D5E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D4D30
	// Original code:	add     eax, 0FFFFFE57h
	static NAKED void patch_6D4D62()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D5110
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6D514F()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D5110
	// Original code:	sub     eax, 425
	static NAKED void patch_6D5153()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D5400
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6D542D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D5E20
	// Original code:	mov     [esi+18h], dx
	static NAKED void patch_6D5E3D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [esi + 18h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D5F10
	// Original code:	mov     [esi+59Ah], ax
	static NAKED void patch_6D61B4()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 59Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D5F10
	// Original code:	mov     [esi+598h], ax
	static NAKED void patch_6D61BB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [esi + 598h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D63F0
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6D63F0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D6410
	// Original code:	mov     ax, [esi+598h]
	static NAKED void patch_6D6413()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 598h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D6410
	// Original code:	mov     word ptr [esi+598h], 0FFFFh
	static NAKED void patch_6D6437()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push UNDEFINED_FILE_ID_INT32;
			lea eax, [esi + 598h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D6410
	// Original code:	mov     word ptr [esi+59Ah], 0FFFFh
	static NAKED void patch_6D6440()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push UNDEFINED_FILE_ID_INT32;
			lea eax, [esi + 59Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D6480
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6D6499()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D6480
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6D64D0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D64F0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6D64F3()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D64F0
	// Original code:	movsx   eax, word ptr [esi+598h]
	static NAKED void patch_6D654F()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 598h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D64F0
	// Original code:	mov     cx, [esi+59Ah]
	static NAKED void patch_6D6569()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 59Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D64F0
	// Original code:	movsx   edx, cx
	static NAKED void patch_6D6570()
	{
		__asm
		{
			mov edx, ecx;
			retn;
		}
	}

	// Function: sub_6D64F0
	// Original code:	mov     [esi+598h], cx
	static NAKED void patch_6D6574()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [esi + 598h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D64F0
	// Original code:	mov     word ptr [esi+59Ah], 0FFFFh
	static NAKED void patch_6D657B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push UNDEFINED_FILE_ID_INT32;
			lea eax, [esi + 59Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D64F0
	// Original code:	movsx   eax, word ptr [esi+598h]
	static NAKED void patch_6D6589()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 598h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	mov     ax, [edi+22h]
	static NAKED void patch_6D6781()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 374
	static NAKED void patch_6D6785_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 374;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 374
	static NAKED void patch_6D6785_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 374;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 381
	static NAKED void patch_6D678B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 381;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 381
	static NAKED void patch_6D678B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 381;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6D67B7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 406
	static NAKED void patch_6D67BB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 406
	static NAKED void patch_6D67BB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 406;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 486
	static NAKED void patch_6D67C5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 486
	static NAKED void patch_6D67C5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 486;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 530
	static NAKED void patch_6D67CF_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 530
	static NAKED void patch_6D67CF_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	mov     ax, [edi+22h]
	static NAKED void patch_6D6966()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 441
	static NAKED void patch_6D696A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 441
	static NAKED void patch_6D696A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 564
	static NAKED void patch_6D6970_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 564
	static NAKED void patch_6D6970_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 594
	static NAKED void patch_6D6976_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 594;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 594
	static NAKED void patch_6D6976_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 594;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6D697C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 441
	static NAKED void patch_6D6980_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 441
	static NAKED void patch_6D6980_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 564
	static NAKED void patch_6D6986_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 564
	static NAKED void patch_6D6986_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 594
	static NAKED void patch_6D698C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 594;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6640
	// Original code:	cmp     ax, 594
	static NAKED void patch_6D698C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 594;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: CVehicle__SetModelIndex
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6D6A7B()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: CVehicle__SetModelIndex
	// Original code:	lea     eax, [ecx-1B9h]
	static NAKED void patch_6D6A85()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			mov ecx, eax;
			add esp, 4;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: CVehicle__SetModelIndex
	// Original code:	lea     eax, [ecx-1DCh] ; switch 101 cases 
	static NAKED void patch_6D6AB9()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push ecx;
			call GetModelIDforModelSpecialFeatures;
			mov ecx, eax;
			add esp, 4;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D6C00
	// Original code:	cmp     word ptr [ebx+22h], 1B9h
	static NAKED void patch_6D6EC0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D6C00
	// Original code:	cmp     word ptr [ebx+22h], 1B9h
	static NAKED void patch_6D6EC0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ebx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D73B0
	// Original code:	cmp     word ptr [edi+22h], 1B9h
	static NAKED void patch_6D76DD_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D73B0
	// Original code:	cmp     word ptr [edi+22h], 1B9h
	static NAKED void patch_6D76DD_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D7C97
	// Original code:	cmp     word ptr [esi+22h], 20Bh
	static NAKED void patch_6D7E11_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 523;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D7C97
	// Original code:	cmp     word ptr [esi+22h], 20Bh
	static NAKED void patch_6D7E11_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 523;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D7C97
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6D7ED1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D8470
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6D8470()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D8470
	// Original code:	add     eax, 0FFFFFE69h
	static NAKED void patch_6D8474()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	mov     bx, [esi+22h]
	static NAKED void patch_6D8E18()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebx, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	cmp     bx, 539
	static NAKED void patch_6D8E1C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	cmp     bx, 539
	static NAKED void patch_6D8E1C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, bx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	cmp     bx, 460
	static NAKED void patch_6D8E43_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	cmp     bx, 460
	static NAKED void patch_6D8E43_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, bx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	mov     bx, [esi+22h]
	static NAKED void patch_6D8EFE()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebx, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	cmp     bx, 539
	static NAKED void patch_6D8F09_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	cmp     bx, 539
	static NAKED void patch_6D8F09_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, bx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	cmp     bx, 520
	static NAKED void patch_6D8FDA_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebx;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	cmp     bx, 520
	static NAKED void patch_6D8FDA_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, bx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6D9233_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	cmp     word ptr [esi+22h], 21Bh
	static NAKED void patch_6D9233_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	cmp     word ptr [esi+22h], 208h
	static NAKED void patch_6D9C04_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6D85F6
	// Original code:	cmp     word ptr [esi+22h], 208h
	static NAKED void patch_6D9C04_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DAF2D
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_6DB16A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6DAF2D
	// Original code:	cmp     word ptr [edi+22h], 159h
	static NAKED void patch_6DB437_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 345;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DAF2D
	// Original code:	cmp     word ptr [edi+22h], 159h
	static NAKED void patch_6DB437_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 345;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DBCE0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6DBF0A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DBCE0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6DBF0A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DBCE0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6DC00B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DBCE0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6DC00B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DBCE0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6DC21B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DBCE0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6DC21B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DBCE0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6DC621_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DBCE0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6DC621_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DBCE0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6DCD63_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DBCE0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6DCD63_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DD130
	// Original code:	cmp     [esi+22h], di
	static NAKED void patch_6DD21D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push edi;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DD130
	// Original code:	cmp     [esi+22h], di
	static NAKED void patch_6DD21D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx edi, di;
			push edi;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DD130
	// Original code:	cmp     [esi+22h], di
	static NAKED void patch_6DD40C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push edi;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DD130
	// Original code:	cmp     [esi+22h], di
	static NAKED void patch_6DD40C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx edi, di;
			push edi;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE240
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6DE2E5()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6DE240
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6DE374()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6DE240
	// Original code:	cmp     ax, 521
	static NAKED void patch_6DE378_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 521;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE240
	// Original code:	cmp     ax, 521
	static NAKED void patch_6DE378_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 521;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE240
	// Original code:	cmp     ax, 522
	static NAKED void patch_6DE38A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 522;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE240
	// Original code:	cmp     ax, 522
	static NAKED void patch_6DE38A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 522;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE240
	// Original code:	cmp     ax, 581
	static NAKED void patch_6DE3BD_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 581;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE240
	// Original code:	cmp     ax, 581
	static NAKED void patch_6DE3BD_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 581;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE886
	// Original code:	cmp     word ptr [esi+22h], 1D7h
	static NAKED void patch_6DEC4A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 471;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE886
	// Original code:	cmp     word ptr [esi+22h], 1D7h
	static NAKED void patch_6DEC4A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 471;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE886
	// Original code:	cmp     word ptr [esi+22h], 1D7h
	static NAKED void patch_6DEEA3_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 471;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE886
	// Original code:	cmp     word ptr [esi+22h], 1D7h
	static NAKED void patch_6DEEA3_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 471;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE886
	// Original code:	cmp     word ptr [esi+22h], 1D7h
	static NAKED void patch_6DF0E3_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 471;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE886
	// Original code:	cmp     word ptr [esi+22h], 1D7h
	static NAKED void patch_6DF0E3_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 471;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE886
	// Original code:	cmp     word ptr [esi+22h], 1D7h
	static NAKED void patch_6DF316_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 471;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DE886
	// Original code:	cmp     word ptr [esi+22h], 1D7h
	static NAKED void patch_6DF316_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 471;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DF3D0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6DF451()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6DF930
	// Original code:	movsx   ebx, ax
	static NAKED void patch_6DF967()
	{
		__asm
		{
			mov ebx, eax;
			retn;
		}
	}

	// Function: sub_6DF930
	// Original code:	movsx   edx, word ptr [eax]
	static NAKED void patch_6DFA08()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6DFA20
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_6DFA2B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6DFA20
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_6DFB44()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6DFB70
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6DFB86()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6DFBE0
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6DFBF6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6DFC50
	// Original code:	mov     ax, [ebx+22h]
	static NAKED void patch_6DFDB2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6DFC50
	// Original code:	cmp     ax, 525
	static NAKED void patch_6DFDB6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DFC50
	// Original code:	cmp     ax, 525
	static NAKED void patch_6DFDB6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DFC50
	// Original code:	cmp     ax, 531
	static NAKED void patch_6DFDBC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6DFC50
	// Original code:	cmp     ax, 531
	static NAKED void patch_6DFDBC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E0050
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6E00D0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6E0050
	// Original code:	cmp     ax, 525
	static NAKED void patch_6E00D4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E0050
	// Original code:	cmp     ax, 525
	static NAKED void patch_6E00D4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 525;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E0050
	// Original code:	cmp     ax, 531
	static NAKED void patch_6E00FA_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E0050
	// Original code:	cmp     ax, 531
	static NAKED void patch_6E00FA_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E0A50
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6E0A5E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6E0A50
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E0C3B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E0A50
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E0C3B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E0A50
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E0CAC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E0A50
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E0CAC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E0A50
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E0D42_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E0A50
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E0D42_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E0E20
	// Original code:	movsx   eax, word ptr [edi+22h]
	static NAKED void patch_6E0E29()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6E0E20
	// Original code:	cmp     word ptr [edi+22h], 212h
	static NAKED void patch_6E0FF8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E0E20
	// Original code:	cmp     word ptr [edi+22h], 212h
	static NAKED void patch_6E0FF8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 530;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1440
	// Original code:	mov     si, [ecx+22h]
	static NAKED void patch_6E1444()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6E1440
	// Original code:	movsx   eax, si
	static NAKED void patch_6E1448()
	{
		__asm
		{
			mov eax, esi;
			retn;
		}
	}

	// Function: sub_6E1440
	// Original code:	cmp     si, 471
	static NAKED void patch_6E153D_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push esi;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 471;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1440
	// Original code:	cmp     si, 471
	static NAKED void patch_6E153D_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, si;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 471;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1600
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_6E1603()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6E1720
	// Original code:	cmp     word ptr [ecx+22h], 214h
	static NAKED void patch_6E1766_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1720
	// Original code:	cmp     word ptr [ecx+22h], 214h
	static NAKED void patch_6E1766_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1780
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6E1786()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6E1780
	// Original code:	cmp     ax, 439
	static NAKED void patch_6E178A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 439;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1780
	// Original code:	cmp     ax, 439
	static NAKED void patch_6E178A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 439;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1780
	// Original code:	cmp     ax, 475
	static NAKED void patch_6E1795_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 475;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1780
	// Original code:	cmp     ax, 475
	static NAKED void patch_6E1795_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 475;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1780
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6E17B5()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6E1780
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E194F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1780
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E194F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1DDh
	static NAKED void patch_6E1C17_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 477;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1DDh
	static NAKED void patch_6E1C17_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 477;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_6E1F31()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E20D6_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E20D6_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E214B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E214B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E21E0_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E21E0_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6E22C2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E2475_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E2475_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E24EA_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E24EA_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E257F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E1A60
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6E257F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E3290
	// Original code:	movsx   ebp, ax
	static NAKED void patch_6E32D6()
	{
		__asm
		{
			mov ebp, eax;
			retn;
		}
	}

	// Function: sub_6E3290
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_6E330E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6E3290
	// Original code:	movzx   edx, ds:MI_OFFROAD_WHEEL
	static NAKED void patch_6E334A()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD758;	// MI_OFFROAD_WHEEL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6E3290
	// Original code:	movsx   edi, cx
	static NAKED void patch_6E33D7()
	{
		__asm
		{
			mov edi, ecx;
			retn;
		}
	}

	// Function: sub_6E3440
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6E3457()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6E3440
	// Original code:	add     eax, 0FFFFFE57h
	static NAKED void patch_6E345B()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6E3440
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6E3794_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E3440
	// Original code:	cmp     word ptr [esi+22h], 1D0h
	static NAKED void patch_6E3794_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E3950
	// Original code:	cmp     word ptr [esi+22h], 208h
	static NAKED void patch_6E39B8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E3950
	// Original code:	cmp     word ptr [esi+22h], 208h
	static NAKED void patch_6E39B8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 520;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6E4160
	// Original code:	movzx   ecx, word ptr [edx]
	static NAKED void patch_6E4266()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edx];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6EABA0
	// Original code:	mov     si, ds:MI_BEACHBALL
	static NAKED void patch_6EABDC()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD638;	// MI_BEACHBALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6EABA0
	// Original code:	mov     si, ds:MI_BEACHBALL; jumptable 006EAC6F case 0
	static NAKED void patch_6EAC76()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD638;	// MI_BEACHBALL
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6EABA0
	// Original code:	mov     si, ds:MI_LOUNGE_WOOD_UP; jumptable 006EAC6F case 1
	static NAKED void patch_6EAC84()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD67C;	// MI_LOUNGE_WOOD_UP
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6EABA0
	// Original code:	mov     si, ds:MI_LOUNGE_TOWEL_UP; jumptable 006EAC6F case 2
	static NAKED void patch_6EAC92()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD680;	// MI_LOUNGE_TOWEL_UP
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6EABA0
	// Original code:	mov     si, ds:MI_LOUNGE_WOOD_DN; jumptable 006EAC6F case 3
	static NAKED void patch_6EACA0()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD684;	// MI_LOUNGE_WOOD_DN
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6EABA0
	// Original code:	mov     si, ds:MI_LOTION; jumptable 006EAC6F case 5
	static NAKED void patch_6EACAE()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD688;	// MI_LOTION
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6EABA0
	// Original code:	mov     si, ds:MI_BEACHTOWEL01; jumptable 006EAC6F case 6
	static NAKED void patch_6EACB7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD68C;	// MI_BEACHTOWEL01
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6EABA0
	// Original code:	mov     si, ds:MI_BEACHTOWEL02; jumptable 006EAC6F case 7
	static NAKED void patch_6EACC0()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD690;	// MI_BEACHTOWEL02
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6EABA0
	// Original code:	mov     si, ds:MI_BEACHTOWEL03; jumptable 006EAC6F case 8
	static NAKED void patch_6EACC9()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD694;	// MI_BEACHTOWEL03
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6EABA0
	// Original code:	mov     si, ds:MI_BEACHTOWEL04; jumptable 006EAC6F case 9
	static NAKED void patch_6EACD2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0x8CD698;	// MI_BEACHTOWEL04
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6ED9A0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6EDA0C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6ED9A0
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6EDA0C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F0210
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6F0234_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F0210
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6F0234_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F0210
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6F028D()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6F0210
	// Original code:	add     eax, 0FFFFFE52h
	static NAKED void patch_6F0291()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6F0210
	// Original code:	cmp     word ptr [esi+22h], 1D8h
	static NAKED void patch_6F07E9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 472;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F0210
	// Original code:	cmp     word ptr [esi+22h], 1D8h
	static NAKED void patch_6F07E9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 472;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F0D00
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6F0D42()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6F1180
	// Original code:	cmp     word ptr [esi+22h], 1E4h
	static NAKED void patch_6F13A4_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 484;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1180
	// Original code:	cmp     word ptr [esi+22h], 1E4h
	static NAKED void patch_6F13A4_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 484;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1180
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6F1487()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6F1180
	// Original code:	cmp     ax, 430
	static NAKED void patch_6F148B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1180
	// Original code:	cmp     ax, 430
	static NAKED void patch_6F148B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1180
	// Original code:	cmp     ax, 453
	static NAKED void patch_6F1491_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 453;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1180
	// Original code:	cmp     ax, 453
	static NAKED void patch_6F1491_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 453;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1180
	// Original code:	cmp     ax, 454
	static NAKED void patch_6F1497_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 454;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1180
	// Original code:	cmp     ax, 454
	static NAKED void patch_6F1497_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 454;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1770
	// Original code:	cmp     word ptr [esi+22h], 1AEh
	static NAKED void patch_6F1801_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1770
	// Original code:	cmp     word ptr [esi+22h], 1AEh
	static NAKED void patch_6F1801_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1770
	// Original code:	cmp     word ptr [esi+22h], 1AEh
	static NAKED void patch_6F18AD_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1770
	// Original code:	cmp     word ptr [esi+22h], 1AEh
	static NAKED void patch_6F18AD_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 430;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1770
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6F1A8A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1770
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6F1A8A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1770
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6F1D86()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6F1770
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6F1F5B_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F1770
	// Original code:	cmp     word ptr [esi+22h], 1CCh
	static NAKED void patch_6F1F5B_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 460;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F21B0
	// Original code:	movsx   ecx, word ptr [ebx+22h]
	static NAKED void patch_6F2340()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6F2947
	// Original code:	cmp     word ptr [esi+22h], 1E4h
	static NAKED void patch_6F2B7E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 484;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F2947
	// Original code:	cmp     word ptr [esi+22h], 1E4h
	static NAKED void patch_6F2B7E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 484;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F32E0
	// Original code:	movsx   edx, word ptr [ecx+22h]
	static NAKED void patch_6F3394()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN13CCarGenerator20DoInternalProcessingEv
	// Original code:	cmp     ax, 0FFFFh
	static NAKED void patch_6F353A_1()
	{
		__asm
		{
			cmp eax, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: _ZN13CCarGenerator20DoInternalProcessingEv
	// Original code:	cmp     ax, 588
	static NAKED void patch_6F361C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 588;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: _ZN13CCarGenerator20DoInternalProcessingEv
	// Original code:	cmp     ax, 588
	static NAKED void patch_6F361C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 588;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: _ZN13CCarGenerator20DoInternalProcessingEv
	// Original code:	mov     ax, [esi+22h]
	static NAKED void patch_6F3B94()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN13CCarGenerator20DoInternalProcessingEv
	// Original code:	cmp     ax, 531
	static NAKED void patch_6F3B98_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: _ZN13CCarGenerator20DoInternalProcessingEv
	// Original code:	cmp     ax, 531
	static NAKED void patch_6F3B98_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 531;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: _ZN13CCarGenerator20DoInternalProcessingEv
	// Original code:	cmp     ax, 532
	static NAKED void patch_6F3B9E_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: _ZN13CCarGenerator20DoInternalProcessingEv
	// Original code:	cmp     ax, 532
	static NAKED void patch_6F3B9E_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 532;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F4047
	// Original code:	cmp     word ptr [edi+22h], 544
	static NAKED void patch_6F4399_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 544;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F4047
	// Original code:	cmp     word ptr [edi+22h], 544
	static NAKED void patch_6F4399_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 544;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F5570
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6F5582_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F5570
	// Original code:	cmp     word ptr [esi+22h], 1C1h
	static NAKED void patch_6F5582_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F5CF0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6F5D2E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6F5CF0
	// Original code:	movzx   edx, ds:MI_OBJECTFORMAGNOCRANE1
	static NAKED void patch_6F5D32()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6C8;	// MI_OBJECTFORMAGNOCRANE1
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6F5CF0
	// Original code:	movzx   ecx, ds:MI_OBJECTFORMAGNOCRANE2
	static NAKED void patch_6F5D3D()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD6CC;	// MI_OBJECTFORMAGNOCRANE2
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6F5CF0
	// Original code:	movzx   edx, ds:MI_OBJECTFORMAGNOCRANE3
	static NAKED void patch_6F5D48()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD6D0;	// MI_OBJECTFORMAGNOCRANE3
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6F6030
	// Original code:	cmp     word ptr [esi+22h], 23Ah
	static NAKED void patch_6F60D9_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 570;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F6030
	// Original code:	cmp     word ptr [esi+22h], 23Ah
	static NAKED void patch_6F60D9_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 570;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F6370
	// Original code:	cmp     word ptr [edi+22h], 23Ah
	static NAKED void patch_6F6576_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 570;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6F6370
	// Original code:	cmp     word ptr [edi+22h], 23Ah
	static NAKED void patch_6F6576_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[edi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 570;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: CTrain__RecalcOnRailDistance
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_6F6F8D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: CTrain__CreateTrain
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6F7731()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: CTrain__CreateTrain
	// Original code:	movsx   edx, word ptr [edi+22h]
	static NAKED void patch_6F775D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: CTrain__CreateTrain
	// Original code:	cmp     word ptr [eax+22h], 1C1h
	static NAKED void patch_6F785F_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: CTrain__CreateTrain
	// Original code:	cmp     word ptr [eax+22h], 1C1h
	static NAKED void patch_6F785F_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 449;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: CTrain__CreateTrain
	// Original code:	cmp     [ecx+22h], si
	static NAKED void patch_6F78A3_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push esi;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: CTrain__CreateTrain
	// Original code:	cmp     [ecx+22h], si
	static NAKED void patch_6F78A3_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx esi, si;
			push esi;
			movzx eax, word ptr[ecx + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: _ZN6CTrain14ProcessControlEv
	// Original code:	cmp     word ptr [esi+22h], 23Ah
	static NAKED void patch_6F8E8A_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 570;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: _ZN6CTrain14ProcessControlEv
	// Original code:	cmp     word ptr [esi+22h], 23Ah
	static NAKED void patch_6F8E8A_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 570;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: _ZN6CTrain14ProcessControlEv
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_6F9118()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN6CTrain14ProcessControlEv
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_6F937C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _ZN6CTrain14ProcessControlEv
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_6F994F()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6FAEC0
	// Original code:	movsx   ecx, word ptr [esi+0Eh]
	static NAKED void patch_6FB59D()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 0Eh];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_6FC7A0
	// Original code:	movsx   eax, word ptr [ebp+22h]
	static NAKED void patch_6FC801()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_6FC7A0
	// Original code:	cmp     word ptr [ebp+22h], 1D0h
	static NAKED void patch_6FCF42_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_6FC7A0
	// Original code:	cmp     word ptr [ebp+22h], 1D0h
	static NAKED void patch_6FCF42_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ebp + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 464;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_707FA0
	// Original code:	cmp     word ptr [esi+22h], 1B9h
	static NAKED void patch_707FC8_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_707FA0
	// Original code:	cmp     word ptr [esi+22h], 1B9h
	static NAKED void patch_707FC8_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 441;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_7086B0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_7086E5()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_70A040
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_70A064()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_70A470
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_70A57F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_70A630
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_70A735()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_70A7E0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_70A8BE()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_70BDA0
	// Original code:	movsx   ebx, word ptr [edi+22h]
	static NAKED void patch_70BF09()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ebx, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_70BDA0
	// Original code:	fstp    st
	static NAKED void patch_70BF0D()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ebx;
			call GetModelIDforModelSpecialFeatures;
			mov ebx, eax;
			add esp, 4;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_711760
	// Original code:	movsx   eax, word ptr [ebx+22h]
	static NAKED void patch_711BD6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_711760
	// Original code:	movsx   edx, word ptr [ebx+22h]
	static NAKED void patch_711CF2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ebx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_717970
	// Original code:	movzx   edx, ds:MI_ESCALATORSTEP
	static NAKED void patch_7179DC()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD674;	// MI_ESCALATORSTEP
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_717D30
	// Original code:	movzx   ecx, ds:MI_ESCALATORSTEP
	static NAKED void patch_717E33()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD674;	// MI_ESCALATORSTEP
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_717D30
	// Original code:	movzx   ecx, ds:MI_ESCALATORSTEP8
	static NAKED void patch_717ED2()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD678;	// MI_ESCALATORSTEP8
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_71AFC0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_71AFF0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_71BC40
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_71BC60()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_71C0D0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_71C0E5()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_71CF50
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_71CFF4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_71CF50
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_71D02E()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_71FAE0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_71FB40()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_71FAE0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_71FB80()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_71FAE0
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_71FC96()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_71FAE0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_71FD43()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_71FAE0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_71FE05()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_71FAE0
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_71FED6()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_71FAE0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_71FFBE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_725C00
	// Original code:	mov     dx, [esi+0Ch]
	static NAKED void patch_725DD6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_725C00
	// Original code:	mov     dx, [esi+0Ch]
	static NAKED void patch_725ECB()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_725C00
	// Original code:	mov     ax, [esi+0Ch]
	static NAKED void patch_725F98()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_725C00
	// Original code:	mov     dx, [esi+0Ch]
	static NAKED void patch_725FFA()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 0Ch];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_729B60
	// Original code:	cmp     [esi+22h], bx
	static NAKED void patch_729BEC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_729B60
	// Original code:	cmp     [esi+22h], bx
	static NAKED void patch_729BEC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ebx, bx;
			push ebx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_729B60
	// Original code:	cmp     [esi+22h], bx
	static NAKED void patch_729DC5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_729B60
	// Original code:	cmp     [esi+22h], bx
	static NAKED void patch_729DC5_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ebx, bx;
			push ebx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_729B60
	// Original code:	cmp     [esi+22h], bx
	static NAKED void patch_72A08C_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_729B60
	// Original code:	cmp     [esi+22h], bx
	static NAKED void patch_72A08C_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ebx, bx;
			push ebx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_729B60
	// Original code:	cmp     [esi+22h], bx
	static NAKED void patch_72A1CC_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ebx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 12;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_729B60
	// Original code:	cmp     [esi+22h], bx
	static NAKED void patch_72A1CC_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx ebx, bx;
			push ebx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, [esp - 4];
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_7316D0
	// Original code:	movsx   eax, word ptr [eax*2+0C88004h]
	static NAKED void patch_7316D4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax * 2 + 0C88004h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: CTxdStore__AddTxdSlot
	// Original code:	mov     word ptr [esi+6], 0FFFFh
	static NAKED void patch_731C9F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push UNDEFINED_FILE_ID_INT32;
			lea eax, [esi + 6];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_731D50
	// Original code:	mov     ax, [ecx+6]
	static NAKED void patch_731D70()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 6];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_731D50
	// Original code:	cmp     ax, 0FFFFh
	static NAKED void patch_731D74_1()
	{
		__asm
		{
			cmp eax, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: sub_731D50
	// Original code:	movsx   eax, word ptr [ecx+6]
	static NAKED void patch_731D9C()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 6];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: CTxdStore__RemoveTxd
	// Original code:	mov     ax, [esi+6]
	static NAKED void patch_731ED4()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 6];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: CTxdStore__RemoveTxd
	// Original code:	cmp     ax, 0FFFFh
	static NAKED void patch_731ED8_1()
	{
		__asm
		{
			cmp eax, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: sub_731F20
	// Original code:	mov     word ptr [esi+6], 0FFFFh
	static NAKED void patch_731F9E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push UNDEFINED_FILE_ID_INT32;
			lea eax, [esi + 6];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_731F20
	// Original code:	mov     [edi], dx
	static NAKED void patch_731FC4()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [edi];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_732170
	// Original code:	mov     si, [ecx+edx]
	static NAKED void patch_73217F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [ecx + edx];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_732170
	// Original code:	mov     [ecx+eax], si
	static NAKED void patch_732183()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push esi;
			lea eax, [ecx + eax];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_732230
	// Original code:	mov     [edx+ecx], ax
	static NAKED void patch_73223F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push eax;
			lea eax, [edx + ecx];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_732250
	// Original code:	movsx   eax, word ptr [ecx+eax]
	static NAKED void patch_73225A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + eax];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_732260
	// Original code:	mov     ax, [ecx+eax]
	static NAKED void patch_73226A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + eax];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_732260
	// Original code:	cmp     ax, 0FFFFh
	static NAKED void patch_73226E_1()
	{
		__asm
		{
			cmp eax, UNDEFINED_FILE_ID_INT32;
			retn;
		}
	}

	// Function: sub_732260
	// Original code:	movsx   edx, ax
	static NAKED void patch_732277()
	{
		__asm
		{
			mov edx, eax;
			retn;
		}
	}

	// Function: sub_732B40
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_732B50()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_734570
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_73457C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_7360D0
	// Original code:	movsx   eax, word ptr [edi+24h]
	static NAKED void patch_7362F7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_7360D0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_7366B6()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_736A50
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_736F14()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_737C87
	// Original code:	cmp     word ptr [ebp+22h], 195h
	static NAKED void patch_737EBB_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [ebp + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 405;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_737C87
	// Original code:	cmp     word ptr [ebp+22h], 195h
	static NAKED void patch_737EBB_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[ebp + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 405;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_737C87
	// Original code:	movzx   edx, ds:MI_FLARE; jumptable 00737CE6 case 42
	static NAKED void patch_738303()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push 0x8CD75C;	// MI_FLARE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_737C87
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_738405()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_737C87
	// Original code:	movzx   ecx, ds:MI_FLARE
	static NAKED void patch_738532()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			push 0x8CD75C;	// MI_FLARE
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_738B20
	// Original code:	cmp     word ptr [eax+22h], 159h
	static NAKED void patch_7390AD_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 345;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_738B20
	// Original code:	cmp     word ptr [eax+22h], 159h
	static NAKED void patch_7390AD_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[eax + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 345;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_73B550
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_73B999()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_73B550
	// Original code:	movsx   edx, word ptr [esi+22h]
	static NAKED void patch_73C062()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_73D1E0
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_73D5CC()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_73EC40
	// Original code:	movsx   ecx, word ptr [esi+22h]
	static NAKED void patch_73EC59()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_73FB10
	// Original code:	mov     ax, [edi+22h]
	static NAKED void patch_7408E3()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_73FB10
	// Original code:	cmp     ax, 447
	static NAKED void patch_7408E7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_73FB10
	// Original code:	cmp     ax, 447
	static NAKED void patch_7408E7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 447;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_73FB10
	// Original code:	cmp     ax, 469
	static NAKED void patch_7408ED_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 469;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_73FB10
	// Original code:	cmp     ax, 469
	static NAKED void patch_7408ED_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 469;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_73FB10
	// Original code:	cmp     ax, 564
	static NAKED void patch_7408F3_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_73FB10
	// Original code:	cmp     ax, 564
	static NAKED void patch_7408F3_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, ax;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 564;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_73FB10
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_741034()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4106D0
	// Original code:	mov     cx, [esi+22h]
	static NAKED void patch_15613C1()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_4106D0
	// Original code:	cmp     cx, [esi+24h]
	static NAKED void patch_15613C5_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [esi + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 8;
			cmp[esp - 4], eax;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_1561650
	// Original code:	movsx   eax, word ptr [esi+ecx*4]
	static NAKED void patch_156166A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + ecx * 4];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_1562000
	// Original code:	movsx   edx, ax
	static NAKED void patch_1562016()
	{
		__asm
		{
			mov edx, eax;
			retn;
		}
	}

	// Function: sub_15629D0
	// Original code:	movsx   edx, word ptr [edx+0Ah]
	static NAKED void patch_1562A3C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_15629D0
	// Original code:	movsx   esi, word ptr [edx+0Ah]
	static NAKED void patch_1562B9B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov esi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_1563290
	// Original code:	mov     word ptr [esi+22h], 32767
	static NAKED void patch_15632CF()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push MAX_FILE_ID_INT32;
			lea eax, [esi + 22h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_1563290
	// Original code:	mov     word ptr [esi+24h], -32768
	static NAKED void patch_15632D5()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push 0;
			lea eax, [esi + 24h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_1563730
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_156377A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_1563730
	// Original code:	movsx   eax, word ptr [ecx+24h]
	static NAKED void patch_1563786()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_1563730
	// Original code:	movsx   eax, word ptr [ecx+26h]
	static NAKED void patch_15637C2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 26h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_1563730
	// Original code:	movsx   eax, word ptr [ecx+28h]
	static NAKED void patch_15637CE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 28h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_1563A40
	// Original code:	movsx   eax, word ptr [ecx+22h]
	static NAKED void patch_1563A40()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [ecx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_1564E90
	// Original code:	movsx   edi, word ptr [esi+22h]
	static NAKED void patch_1564EB2()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edi, eax;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_1564E90
	// Original code:	movsx   edx, word ptr [esi+24h]
	static NAKED void patch_1564EB6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [esi + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_1564E90
	// Original code:	movsx   eax, word ptr [esi+24h]
	static NAKED void patch_1564EEB()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_1565260
	// Original code:	movsx   eax, word ptr [eax+22h]
	static NAKED void patch_1565268()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_409A90
	// Original code:	movsx   edx, word ptr [ecx+0Ah]
	static NAKED void patch_1566514()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_409A90
	// Original code:	movsx   eax, word ptr [eax+6]
	static NAKED void patch_1566544()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 6];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_409A90
	// Original code:	movsx   eax, word ptr [edx+0Ah]
	static NAKED void patch_1566591()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_409A90
	// Original code:	movsx   edx, word ptr [ecx+0Ah]
	static NAKED void patch_15665D0()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_1567170
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_1567191()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_15691D0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_15691DA()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_15691D0
	// Original code:	movsx   edx, word ptr [ecx]
	static NAKED void patch_156929F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_156A260
	// Original code:	movsx   edx, word ptr [eax+22h]
	static NAKED void patch_156A27E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_156A260
	// Original code:	movsx   edx, word ptr [eax+24h]
	static NAKED void patch_156A28E()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [eax + 24h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_42F870
	// Original code:	cmp     word ptr [esi+22h], 539
	static NAKED void patch_156A4D7_1()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 8;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_42F870
	// Original code:	cmp     word ptr [esi+22h], 539
	static NAKED void patch_156A4D7_2()
	{
		__asm
		{
			push eax;
			push ecx;
			push edx;
			movzx eax, word ptr[esi + 22h];
			push eax;
			call GetModelIDforModelSpecialFeatures;
			add esp, 4;
			cmp eax, 539;
			pop edx;
			pop ecx;
			pop eax;
			retn;
		}
	}

	// Function: sub_156A8C0
	// Original code:	movsx   eax, word ptr [edi+esi+2]
	static NAKED void patch_156A8F0()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edi + esi + 2];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_156A8C0
	// Original code:	movsx   ecx, word ptr [edi+esi+1Ah]
	static NAKED void patch_156A8FA()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [edi + esi + 1Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_156A8C0
	// Original code:	movsx   edx, word ptr [edi+esi+1Ah]
	static NAKED void patch_156A904()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [edi + esi + 1Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_156B1C0
	// Original code:	movsx   eax, word ptr [esi+22h]
	static NAKED void patch_156B1D9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_156B890
	// Original code:	mov     word ptr [eax+14Ah], 0FFFFh
	static NAKED void patch_156B8D7()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push UNDEFINED_FILE_ID_INT32;
			lea eax, [eax + 14Ah];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_156C100
	// Original code:	movsx   ecx, word ptr [eax+0Ah]
	static NAKED void patch_156C24E()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_156C100
	// Original code:	movsx   edx, word ptr [ecx+0Ah]
	static NAKED void patch_156C27C()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _allocIplFile
	// Original code:	mov     [eax+24h], cx
	static NAKED void patch_156C494()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [eax + 24h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _allocIplFile
	// Original code:	mov     [eax+28h], cx
	static NAKED void patch_156C498()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push ecx;
			lea eax, [eax + 28h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _allocIplFile
	// Original code:	mov     [eax+22h], dx
	static NAKED void patch_156C4B6()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: _allocIplFile
	// Original code:	mov     [eax+26h], dx
	static NAKED void patch_156C4BA()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			push edx;
			push edx;
			lea eax, [eax + 26h];
			push eax;
			call SetExtendedIDfrom16bitBefore;
			add esp, 8;
			pop edx;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_156CA30
	// Original code:	movsx   eax, word ptr [edx+0Ah]
	static NAKED void patch_156CA64()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_156CA30
	// Original code:	movsx   eax, word ptr [edx+0Ah]
	static NAKED void patch_156CAA9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_156CED0
	// Original code:	movsx   eax, word ptr [edx+22h]
	static NAKED void patch_156CEF1()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: _ZN17CScriptsForBrains60MarkAttractorScriptBrainWithThisNameAsNoLongerNeeded_HOODLUMEPKc
	// Original code:	movsx   ecx, word ptr [esi+ecx*4]
	static NAKED void patch_156D95A()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + ecx * 4];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_46AA80
	// Original code:	movsx   eax, word ptr [esi+ecx*4]
	static NAKED void patch_156D99A()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + ecx * 4];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_46AA80
	// Original code:	movsx   eax, word ptr [esi]
	static NAKED void patch_156D9CE()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_156DB40
	// Original code:	movsx   ecx, word ptr [eax+22h]
	static NAKED void patch_156DB46()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 22h];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_45CEA0
	// Original code:	movsx   eax, word ptr [esi+2]
	static NAKED void patch_156EDC9()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 2];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_45CEA0
	// Original code:	movsx   eax, word ptr [esi+2]
	static NAKED void patch_156EDF3()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [esi + 2];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_45CEA0
	// Original code:	movsx   ecx, word ptr [esi+2]
	static NAKED void patch_156EEE1()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [esi + 2];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_15700A0
	// Original code:	movsx   eax, word ptr [eax+6]
	static NAKED void patch_15700B5()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 6];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_15700A0
	// Original code:	movsx   eax, word ptr [eax+6]
	static NAKED void patch_15700C2()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [eax + 6];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_1570230
	// Original code:	movsx   eax, word ptr [edx+0Ah]
	static NAKED void patch_157024F()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_1570230
	// Original code:	movsx   ecx, word ptr [eax+0Ah]
	static NAKED void patch_1570277()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_1570230
	// Original code:	movsx   edx, word ptr [ecx+0Ah]
	static NAKED void patch_157029F()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_1570230
	// Original code:	movsx   eax, word ptr [edx+0Ah]
	static NAKED void patch_15702C7()
	{
		__asm
		{
			pushfd;
			push ecx;
			push edx;
			lea eax, [edx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			pop edx;
			pop ecx;
			popfd;
			retn;
		}
	}

	// Function: sub_1570230
	// Original code:	movsx   ecx, word ptr [eax+0Ah]
	static NAKED void patch_15702EF()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_1570230
	// Original code:	movsx   edx, word ptr [ecx+0Ah]
	static NAKED void patch_1570317()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_15703E0
	// Original code:	movsx   edx, word ptr [ecx+0Ah]
	static NAKED void patch_157040B()
	{
		__asm
		{
			pushfd;
			push eax;
			push ecx;
			lea eax, [ecx + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov edx, eax;
			pop ecx;
			pop eax;
			popfd;
			retn;
		}
	}

	// Function: sub_15703E0
	// Original code:	movsx   ecx, word ptr [eax+0Ah]
	static NAKED void patch_1570464()
	{
		__asm
		{
			pushfd;
			push eax;
			push edx;
			lea eax, [eax + 0Ah];
			push eax;
			call GetExtendedIDfrom16bitBefore;
			add esp, 4;
			mov ecx, eax;
			pop edx;
			pop eax;
			popfd;
			retn;
		}
	}

}
#endif


#ifdef IS_PLATFORM_WIN_X86
namespace IDaccessPatches
{
	static const tArrayItem ptrArray[] =
	{
	tArrayItem(0x401527, &patch_401527),	// sub_454AE0 : movzx   ecx, ds:MI_PICKUP_BODYARMOUR
	tArrayItem(0x401D56, &patch_401D56),	// sub_734570 : movzx   ecx, ds:MI_GRASSHOUSE
	tArrayItem(0x403EC8, &patch_403EC8),	// sub_403EC0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x403EE8, &patch_403EE8),	// sub_403EC0 : mov     [esi+22h], dx
	tArrayItem(0x403EF5, &patch_403EF5),	// sub_403EC0 : mov     [esi+22h], ax
	tArrayItem(0x404B4A, &patch_404B4A),	// _ZN9CIplStore9RemoveIplEi : movsx   edi, word ptr [ebx+22h]
	tArrayItem(0x404B5D, &patch_404B5D),	// _ZN9CIplStore9RemoveIplEi : movsx   edx, word ptr [ebx+24h]
	tArrayItem(0x404BA8, &patch_404BA8),	// _ZN9CIplStore9RemoveIplEi : movsx   edx, word ptr [ebx+24h]
	tArrayItem(0x404C0F, &patch_404C0F),	// _ZN9CIplStore9RemoveIplEi : movsx   edi, word ptr [ebx+26h]
	tArrayItem(0x404C13, &patch_404C13),	// _ZN9CIplStore9RemoveIplEi : movsx   ecx, word ptr [ebx+28h]
	tArrayItem(0x404C4E, &patch_404C4E),	// _ZN9CIplStore9RemoveIplEi : movsx   eax, word ptr [ebx+28h]
	tArrayItem(0x4058EE, &patch_4058EE),	// sub_509A30 : movzx   ecx, ds:MI_SINGLESTREETLIGHTS1
	tArrayItem(0x405CDB, &patch_405CDB),	// sub_405C00 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x405E4C, &patch_405E4C),	// sub_405C00 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x40649C | (1 << 29), &patch_40649C_1),	// sub_408C8C : cmp     word ptr [esi+22h], 495
	tArrayItem(0x40649C | (2 << 29), &patch_40649C_2),	// sub_408C8C : cmp     word ptr [esi+22h], 495
	tArrayItem(0x406AF1 | (1 << 29), &patch_406AF1_1),	// sub_6CADD0 : cmp     word ptr [esi+22h], 208h
	tArrayItem(0x406AF1 | (2 << 29), &patch_406AF1_2),	// sub_6CADD0 : cmp     word ptr [esi+22h], 208h
	tArrayItem(0x407645, &patch_407645),	// sub_6D0C00 : mov     ax, [esi+598h]
	tArrayItem(0x407A15 | (1 << 29), &patch_407A15_1),	// sub_6D4290 : cmp     dx, 476
	tArrayItem(0x407A15 | (2 << 29), &patch_407A15_2),	// sub_6D4290 : cmp     dx, 476
	tArrayItem(0x407F90, &patch_407F90),	// sub_644470 : movzx   ecx, ds:MI_GANG_SMOKE
	tArrayItem(0x4083A0, &patch_4083A0),	// sub_4083A0 : movsx   eax, word ptr [ecx+22h]
	tArrayItem(0x40890A, &patch_40890A),	// CStreaming__RequestModel : movsx   ecx, word ptr [ebp+0Ah]
	tArrayItem(0x408D28, &patch_408D28),	// sub_408CB0 : movsx   eax, word ptr [eax+0Ah]
	tArrayItem(0x408D5A, &patch_408D5A),	// sub_408CB0 : movsx   edx, word ptr [ecx+0Ah]
	tArrayItem(0x408EC7, &patch_408EC7),	// CStreaming__GetNextFileOnCd : movsx   eax, word ptr [ecx+0Ah]
	tArrayItem(0x408F6E, &patch_408F6E),	// CStreaming__GetNextFileOnCd : movsx   eax, word ptr [eax+6]
	tArrayItem(0x4093F0, &patch_4093F0),	// sub_4093B0 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x40940B, &patch_40940B),	// sub_4093B0 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x40948B, &patch_40948B),	// sub_409430 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x4095F5, &patch_4095F5),	// sub_4095C0 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x40962B, &patch_40962B),	// sub_4095C0 : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x4097AF, &patch_4097AF),	// sub_409760 : movsx   edi, word ptr [esi+22h]
	tArrayItem(0x4098A2, &patch_4098A2),	// sub_409760 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x409971, &patch_409971),	// sub_409940 : movsx   edi, word ptr [esi+22h]
	tArrayItem(0x409A32, &patch_409A32),	// sub_4099E0 : movsx   edi, word ptr [esi+22h]
	tArrayItem(0x409C7B, &patch_409C7B),	// sub_409C70 : movsx   edx, word ptr [ecx+0Ah]
	tArrayItem(0x409CFC, &patch_409CFC),	// sub_409C90 : movsx   esi, word ptr [ecx+0Ah]
	tArrayItem(0x409DC1, &patch_409DC1),	// sub_409D10 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x409E2D, &patch_409E2D),	// sub_409D10 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x409F1D, &patch_409F1D),	// sub_409D10 : movsx   esi, word ptr [edx+0Ah]
	tArrayItem(0x40A0BF, &patch_40A0BF),	// sub_535FA0 : movzx   ecx, ds:MI_TRAFFICLIGHTS
	tArrayItem(0x40A2BF, &patch_40A2BF),	// sub_40A2A0 : movsx   eax, word ptr [edx+0Ah]
	tArrayItem(0x40A2E7, &patch_40A2E7),	// sub_40A2A0 : movsx   ecx, word ptr [eax+0Ah]
	tArrayItem(0x40A30F, &patch_40A30F),	// sub_40A2A0 : movsx   edx, word ptr [ecx+0Ah]
	tArrayItem(0x40A337, &patch_40A337),	// sub_40A2A0 : movsx   eax, word ptr [edx+0Ah]
	tArrayItem(0x40A35F, &patch_40A35F),	// sub_40A2A0 : movsx   ecx, word ptr [eax+0Ah]
	tArrayItem(0x40A387, &patch_40A387),	// sub_40A2A0 : movsx   edx, word ptr [ecx+0Ah]
	tArrayItem(0x40A5B9, &patch_40A5B9),	// sub_40A560 : movsx   eax, word ptr [edx+0Ah]
	tArrayItem(0x40A738, &patch_40A738),	// sub_40A560 : movsx   edx, word ptr [ecx+0Ah]
	tArrayItem(0x40A8EC, &patch_40A8EC),	// sub_40A560 : movsx   esi, word ptr [edx+0Ah]
	tArrayItem(0x40AC23, &patch_40AC23),	// sub_40AA10 : movsx   edx, word ptr [edx+0Ah]
	tArrayItem(0x40AE92, &patch_40AE92),	// sub_40AA10 : movsx   esi, word ptr [eax+0Ah]
	tArrayItem(0x40B9D1, &patch_40B9D1),	// sub_40B700 : movzx   edx, ds:MI_HARVESTERBODYPART1
	tArrayItem(0x40B9E0, &patch_40B9E0),	// sub_40B700 : movzx   eax, ds:MI_HARVESTERBODYPART2
	tArrayItem(0x40B9EF, &patch_40B9EF),	// sub_40B700 : movzx   ecx, ds:MI_HARVESTERBODYPART3
	tArrayItem(0x40B9FE, &patch_40B9FE),	// sub_40B700 : movzx   edx, ds:MI_HARVESTERBODYPART4
	tArrayItem(0x40BA28, &patch_40BA28),	// sub_40B700 : movzx   eax, ds:MI_HARVESTERBODYPART1
	tArrayItem(0x40BA35, &patch_40BA35),	// sub_40B700 : movzx   ecx, ds:MI_HARVESTERBODYPART2
	tArrayItem(0x40BA42, &patch_40BA42),	// sub_40B700 : movzx   edx, ds:MI_HARVESTERBODYPART3
	tArrayItem(0x40BA4F, &patch_40BA4F),	// sub_40B700 : movzx   eax, ds:MI_HARVESTERBODYPART4
	tArrayItem(0x40BB29, &patch_40BB29),	// sub_40BAA0 : movsx   edx, word ptr [edx+0Ah]
	tArrayItem(0x40BE72, &patch_40BE72),	// sub_40BE60 : lea     eax, [esi-57h]
	tArrayItem(0x40BEE4, &patch_40BEE4),	// sub_40BE60 : movsx   edx, word ptr [ecx+0Ah]
	tArrayItem(0x40C2B2, &patch_40C2B2),	// sub_40C270 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x40C423, &patch_40C423),	// sub_40C270 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x40C48A, &patch_40C48A),	// sub_40C450 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x40C500, &patch_40C500),	// sub_40C450 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x40C70D, &patch_40C70D),	// CStreaming__ConvertBufferToObject : movsx   ecx, word ptr [ebp+0Ah]
	tArrayItem(0x40C76E, &patch_40C76E),	// CStreaming__ConvertBufferToObject : movsx   eax, word ptr [ebp+0Ah]
	tArrayItem(0x40C824, &patch_40C824),	// CStreaming__ConvertBufferToObject : movsx   ecx, word ptr [ebp+0Ah]
	tArrayItem(0x40C8CE, &patch_40C8CE),	// CStreaming__ConvertBufferToObject : movsx   eax, word ptr [eax+6]
	tArrayItem(0x40CD93, &patch_40CD93),	// CStreaming__RequestModelStream : movsx   eax, word ptr [edi+0Ah]
	tArrayItem(0x40E242, &patch_40E242),	// sub_40E170 : movsx   ecx, word ptr [eax+0Ah]
	tArrayItem(0x41A8DA, &patch_41A8DA),	// sub_41A820 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x41AA45, &patch_41AA45),	// sub_41A990 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x41AA75, &patch_41AA75),	// sub_41A990 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x41AB94, &patch_41AB94),	// sub_41AB20 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x41C0A6, &patch_41C0A6),	// sub_4011EF : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x41C0AA, &patch_41C0AA),	// sub_4011EF : add     eax, 0FFFFFE55h
	tArrayItem(0x41D77A, &patch_41D77A),	// sub_41D660 : movsx   eax, word ptr [ecx+22h]
	tArrayItem(0x41DEE1 | (1 << 29), &patch_41DEE1_1),	// sub_403C48 : cmp     word ptr [esi+22h], 1B0h
	tArrayItem(0x41DEE1 | (2 << 29), &patch_41DEE1_2),	// sub_403C48 : cmp     word ptr [esi+22h], 1B0h
	tArrayItem(0x41E24C | (1 << 29), &patch_41E24C_1),	// sub_403C48 : cmp     word ptr [esi+22h], 1B0h
	tArrayItem(0x41E24C | (2 << 29), &patch_41E24C_2),	// sub_403C48 : cmp     word ptr [esi+22h], 1B0h
	tArrayItem(0x41F2A7 | (1 << 29), &patch_41F2A7_1),	// sub_403C48 : cmp     [esi+22h], di
	tArrayItem(0x41F2A7 | (2 << 29), &patch_41F2A7_2),	// sub_403C48 : cmp     [esi+22h], di
	tArrayItem(0x41F34D | (1 << 29), &patch_41F34D_1),	// sub_403C48 : cmp     [esi+22h], di
	tArrayItem(0x41F34D | (2 << 29), &patch_41F34D_2),	// sub_403C48 : cmp     [esi+22h], di
	tArrayItem(0x4217F4, &patch_4217F4),	// sub_4217C0 : movzx   edx, ds:MI_GANG_SMOKE
	tArrayItem(0x421860, &patch_421860),	// sub_4217C0 : movsx   esi, word ptr [esi+22h]
	tArrayItem(0x4218D8, &patch_4218D8),	// sub_4217C0 : movzx   eax, ds:MI_GANG_SMOKE
	tArrayItem(0x421FE4, &patch_421FE4),	// sub_421FE0 : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x421FE8, &patch_421FE8),	// sub_421FE0 : add     eax, 0FFFFFE6Dh
	tArrayItem(0x4250A6, &patch_4250A6),	// sub_424F80 : mov     ax, [esi+22h]
	tArrayItem(0x4250AA | (1 << 29), &patch_4250AA_1),	// sub_424F80 : cmp     ax, 416
	tArrayItem(0x4250AA | (2 << 29), &patch_4250AA_2),	// sub_424F80 : cmp     ax, 416
	tArrayItem(0x4250B0 | (1 << 29), &patch_4250B0_1),	// sub_424F80 : cmp     ax, 407
	tArrayItem(0x4250B0 | (2 << 29), &patch_4250B0_2),	// sub_424F80 : cmp     ax, 407
	tArrayItem(0x425463, &patch_425463),	// sub_425440 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x425502, &patch_425502),	// sub_425440 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x425B7E, &patch_425B7E),	// sub_425B30 : movsx   eax, word ptr [edx+22h]
	tArrayItem(0x425B9D, &patch_425B9D),	// sub_425B30 : movsx   edx, word ptr [edi+22h]
	tArrayItem(0x425F9D, &patch_425F9D),	// sub_425F70 : movsx   edx, word ptr [edx+22h]
	tArrayItem(0x425FA5, &patch_425FA5),	// sub_425F70 : movsx   eax, word ptr [ecx+22h]
	tArrayItem(0x4262A8, &patch_4262A8),	// sub_426220 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x4262C5, &patch_4262C5),	// sub_426220 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x42647A, &patch_42647A),	// sub_426350 : movsx   edx, word ptr [edi+22h]
	tArrayItem(0x4264EC, &patch_4264EC),	// sub_426350 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x426555, &patch_426555),	// sub_426350 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x4265BC, &patch_4265BC),	// sub_426350 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x426638, &patch_426638),	// sub_426350 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x4266B2, &patch_4266B2),	// sub_426350 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x42671B, &patch_42671B),	// sub_426350 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x426785, &patch_426785),	// sub_426350 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x4267EC, &patch_4267EC),	// sub_426350 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x4267FB, &patch_4267FB),	// sub_426350 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x426A2A, &patch_426A2A),	// sub_426970 : movsx   edx, word ptr [ebx+22h]
	tArrayItem(0x426BC0, &patch_426BC0),	// sub_426BC0 : movzx   ecx, ds:MI_TRAFFICLIGHTS
	tArrayItem(0x426BCF, &patch_426BCF),	// sub_426BC0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x426BEC, &patch_426BEC),	// sub_426BC0 : movzx   edx, ds:MI_SINGLESTREETLIGHTS1
	tArrayItem(0x426C01, &patch_426C01),	// sub_426BC0 : movzx   ecx, ds:MI_SINGLESTREETLIGHTS2
	tArrayItem(0x426C16, &patch_426C16),	// sub_426BC0 : movzx   edx, ds:MI_SINGLESTREETLIGHTS3
	tArrayItem(0x426C33, &patch_426C33),	// sub_426BC0 : movzx   ecx, ds:MI_DOUBLESTREETLIGHTS
	tArrayItem(0x426D69, &patch_426D69),	// sub_426BC0 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x426F94 | (1 << 29), &patch_426F94_1),	// sub_426EF0 : cmp     word ptr [esi+22h], 21Bh
	tArrayItem(0x426F94 | (2 << 29), &patch_426F94_2),	// sub_426EF0 : cmp     word ptr [esi+22h], 21Bh
	tArrayItem(0x427790 | (1 << 29), &patch_427790_1),	// sub_427740 : cmp     word ptr [esi+22h], 21Bh
	tArrayItem(0x427790 | (2 << 29), &patch_427790_2),	// sub_427740 : cmp     word ptr [esi+22h], 21Bh
	tArrayItem(0x429051 | (1 << 29), &patch_429051_1),	// sub_428DE0 : cmp     word ptr [esi+22h], 1AEh
	tArrayItem(0x429051 | (2 << 29), &patch_429051_2),	// sub_428DE0 : cmp     word ptr [esi+22h], 1AEh
	tArrayItem(0x42BBC8, &patch_42BBC8),	// sub_42B7D7 : lea     eax, [ebx-197h]
	tArrayItem(0x42C489, &patch_42C489),	// sub_42C2B0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x42C793, &patch_42C793),	// sub_42C740 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x42C7D0, &patch_42C7D0),	// sub_42C740 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x42D52A, &patch_42D52A),	// sub_42D4F0 : movsx   eax, word ptr [ebx+22h]
	tArrayItem(0x42D52E, &patch_42D52E),	// sub_42D4F0 : movzx   ecx, ds:MI_ROADWORKBARRIER1
	tArrayItem(0x42D539, &patch_42D539),	// sub_42D4F0 : movzx   edx, ds:MI_ROADBLOCKFUCKEDCAR1
	tArrayItem(0x42D544, &patch_42D544),	// sub_42D4F0 : movzx   ecx, ds:MI_ROADBLOCKFUCKEDCAR2
	tArrayItem(0x42DB2E | (1 << 29), &patch_42DB2E_1),	// sub_42DAB0 : cmp     word ptr [edi+22h], 21Bh
	tArrayItem(0x42DB2E | (2 << 29), &patch_42DB2E_2),	// sub_42DAB0 : cmp     word ptr [edi+22h], 21Bh
	tArrayItem(0x42DB7D, &patch_42DB7D),	// sub_42DAB0 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x42DC26, &patch_42DC26),	// sub_42DAB0 : movsx   edx, word ptr [edi+22h]
	tArrayItem(0x42DD30, &patch_42DD30),	// sub_42DAB0 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x42DD93, &patch_42DD93),	// sub_42DAB0 : movsx   edx, word ptr [edi+22h]
	tArrayItem(0x42DDE9, &patch_42DDE9),	// sub_42DAB0 : movsx   edx, word ptr [edi+22h]
	tArrayItem(0x42E223, &patch_42E223),	// sub_42DE80 : movsx   eax, word ptr [ecx+ebp+10h]
	tArrayItem(0x42E255, &patch_42E255),	// sub_42DE80 : movsx   eax, word ptr [ecx+ebp+10h]
	tArrayItem(0x42E384, &patch_42E384),	// sub_42DE80 : movsx   ecx, word ptr [eax+ebp+10h]
	tArrayItem(0x42E3B2, &patch_42E3B2),	// sub_42DE80 : movsx   ecx, word ptr [eax+ebp+10h]
	tArrayItem(0x42EC9E, &patch_42EC9E),	// sub_42EC90 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x42FE50 | (1 << 29), &patch_42FE50_1),	// sub_42FC40 : cmp     word ptr [esi+22h], 21Bh
	tArrayItem(0x42FE50 | (2 << 29), &patch_42FE50_2),	// sub_42FC40 : cmp     word ptr [esi+22h], 21Bh
	tArrayItem(0x42FF0B | (1 << 29), &patch_42FF0B_1),	// sub_42FC40 : cmp     word ptr [esi+22h], 21Bh
	tArrayItem(0x42FF0B | (2 << 29), &patch_42FF0B_2),	// sub_42FC40 : cmp     word ptr [esi+22h], 21Bh
	tArrayItem(0x43072E, &patch_43072E),	// sub_403AEE : mov     cx, [esi+22h]
	tArrayItem(0x430732, &patch_430732),	// sub_403AEE : movsx   edx, cx
	tArrayItem(0x430778 | (1 << 29), &patch_430778_1),	// sub_403AEE : cmp     cx, 446
	tArrayItem(0x430778 | (2 << 29), &patch_430778_2),	// sub_403AEE : cmp     cx, 446
	tArrayItem(0x43077F | (1 << 29), &patch_43077F_1),	// sub_403AEE : cmp     cx, 452
	tArrayItem(0x43077F | (2 << 29), &patch_43077F_2),	// sub_403AEE : cmp     cx, 452
	tArrayItem(0x430786 | (1 << 29), &patch_430786_1),	// sub_403AEE : cmp     cx, 493
	tArrayItem(0x430786 | (2 << 29), &patch_430786_2),	// sub_403AEE : cmp     cx, 493
	tArrayItem(0x4308A1 | (1 << 29), &patch_4308A1_1),	// sub_403AEE : cmp     word ptr [esi+22h], 1A7h
	tArrayItem(0x4308A1 | (2 << 29), &patch_4308A1_2),	// sub_403AEE : cmp     word ptr [esi+22h], 1A7h
	tArrayItem(0x430943, &patch_430943),	// sub_403AEE : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x43181F, &patch_43181F),	// sub_403AEE : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x43198E, &patch_43198E),	// sub_403AEE : movzx   eax, ds:MI_HYDRAULICS
	tArrayItem(0x431A99 | (1 << 29), &patch_431A99_1),	// sub_403AEE : cmp     word ptr [esi+22h], 1E4h
	tArrayItem(0x431A99 | (2 << 29), &patch_431A99_2),	// sub_403AEE : cmp     word ptr [esi+22h], 1E4h
	tArrayItem(0x431B42, &patch_431B42),	// sub_403AEE : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x431BC7, &patch_431BC7),	// sub_403AEE : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x431BEB, &patch_431BEB),	// sub_403AEE : mov     ax, [esi+22h]
	tArrayItem(0x431BF2 | (1 << 29), &patch_431BF2_1),	// sub_403AEE : cmp     ax, 531
	tArrayItem(0x431BF2 | (2 << 29), &patch_431BF2_2),	// sub_403AEE : cmp     ax, 531
	tArrayItem(0x431BF8 | (1 << 29), &patch_431BF8_1),	// sub_403AEE : cmp     ax, 532
	tArrayItem(0x431BF8 | (2 << 29), &patch_431BF8_2),	// sub_403AEE : cmp     ax, 532
	tArrayItem(0x431C57 | (1 << 29), &patch_431C57_1),	// sub_403AEE : cmp     word ptr [esi+22h], 1C9h
	tArrayItem(0x431C57 | (2 << 29), &patch_431C57_2),	// sub_403AEE : cmp     word ptr [esi+22h], 1C9h
	tArrayItem(0x431D89, &patch_431D89),	// sub_403AEE : mov     ax, [esi+22h]
	tArrayItem(0x431D8D | (1 << 29), &patch_431D8D_1),	// sub_403AEE : cmp     ax, 463
	tArrayItem(0x431D8D | (2 << 29), &patch_431D8D_2),	// sub_403AEE : cmp     ax, 463
	tArrayItem(0x431D93 | (1 << 29), &patch_431D93_1),	// sub_403AEE : cmp     ax, 461
	tArrayItem(0x431D93 | (2 << 29), &patch_431D93_2),	// sub_403AEE : cmp     ax, 461
	tArrayItem(0x431D99 | (1 << 29), &patch_431D99_1),	// sub_403AEE : cmp     ax, 521
	tArrayItem(0x431D99 | (2 << 29), &patch_431D99_2),	// sub_403AEE : cmp     ax, 521
	tArrayItem(0x431D9F | (1 << 29), &patch_431D9F_1),	// sub_403AEE : cmp     ax, 522
	tArrayItem(0x431D9F | (2 << 29), &patch_431D9F_2),	// sub_403AEE : cmp     ax, 522
	tArrayItem(0x431DA5 | (1 << 29), &patch_431DA5_1),	// sub_403AEE : cmp     ax, 581
	tArrayItem(0x431DA5 | (2 << 29), &patch_431DA5_2),	// sub_403AEE : cmp     ax, 581
	tArrayItem(0x431DAB | (1 << 29), &patch_431DAB_1),	// sub_403AEE : cmp     ax, 586
	tArrayItem(0x431DAB | (2 << 29), &patch_431DAB_2),	// sub_403AEE : cmp     ax, 586
	tArrayItem(0x431F00, &patch_431F00),	// sub_403AEE : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x431F0A, &patch_431F0A),	// sub_403AEE : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x435A81 | (1 << 29), &patch_435A81_1),	// sub_435830 : cmp     word ptr [esi+22h], 21Bh
	tArrayItem(0x435A81 | (2 << 29), &patch_435A81_2),	// sub_435830 : cmp     word ptr [esi+22h], 21Bh
	tArrayItem(0x436B2D, &patch_436B2D),	// sub_436A90 : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x436B3B, &patch_436B3B),	// sub_436A90 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x437727, &patch_437727),	// sub_436A90 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x437736, &patch_437736),	// sub_436A90 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x437792, &patch_437792),	// sub_436A90 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x4377A1, &patch_4377A1),	// sub_436A90 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x4377E2, &patch_4377E2),	// sub_436A90 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x4377F1, &patch_4377F1),	// sub_436A90 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x43783D, &patch_43783D),	// sub_436A90 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x43784C, &patch_43784C),	// sub_436A90 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x4382A4 | (1 << 29), &patch_4382A4_1),	// sub_437C20 : cmp     word ptr [esi+22h], 21Bh
	tArrayItem(0x4382A4 | (2 << 29), &patch_4382A4_2),	// sub_437C20 : cmp     word ptr [esi+22h], 21Bh
	tArrayItem(0x439896, &patch_439896),	// sub_439880 : mov     ax, ds:MI_PICKUP_ADRENALINE
	tArrayItem(0x43A341, &patch_43A341),	// _spawnCarAtPlayerLocation : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x43A72E, &patch_43A72E),	// sub_43A710 : mov     ax, [esi+0Ah]
	tArrayItem(0x43B3DF, &patch_43B3DF),	// sub_43B0F0 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x43DE61, &patch_43DE61),	// sub_43DCD0 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x43DF50, &patch_43DF50),	// sub_43DF20 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x43DFAA | (1 << 29), &patch_43DFAA_1),	// sub_43DF20 : cmp     word ptr [esi+22h], 1B0h
	tArrayItem(0x43DFAA | (2 << 29), &patch_43DFAA_2),	// sub_43DF20 : cmp     word ptr [esi+22h], 1B0h
	tArrayItem(0x443B90, &patch_443B90),	// sub_443B00 : mov     cx, [esi+0Ch]
	tArrayItem(0x445049, &patch_445049),	// sub_444810 : mov     ax, ds:MI_PICKUP_HEALTH
	tArrayItem(0x445051, &patch_445051),	// sub_444810 : mov     ax, ds:MI_PICKUP_BODYARMOUR
	tArrayItem(0x445064, &patch_445064),	// sub_444810 : movzx   edx, ds:MI_PICKUP_BODYARMOUR
	tArrayItem(0x445075, &patch_445075),	// sub_444810 : movzx   edx, ds:MI_PICKUP_HEALTH
	tArrayItem(0x445AD0, &patch_445AD0),	// sub_4453D0 : mov     ax, ds:MI_PICKUP_HEALTH
	tArrayItem(0x445AD8, &patch_445AD8),	// sub_4453D0 : mov     ax, ds:MI_PICKUP_BODYARMOUR
	tArrayItem(0x448EE8, &patch_448EE8),	// sub_448EE0 : movsx   eax, word ptr [ebx+22h]
	tArrayItem(0x449766, &patch_449766),	// sub_449760 : mov     ax, [esi+22h]
	tArrayItem(0x44A522, &patch_44A522),	// sub_44A4D0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x44AADB | (1 << 29), &patch_44AADB_1),	// sub_44AA50 : cmp     word ptr [eax+22h], 23Bh
	tArrayItem(0x44AADB | (2 << 29), &patch_44AADB_2),	// sub_44AA50 : cmp     word ptr [eax+22h], 23Bh
	tArrayItem(0x44AB2A | (1 << 29), &patch_44AB2A_1),	// sub_44AA50 : cmp     word ptr [edi+22h], 1A7h
	tArrayItem(0x44AB2A | (2 << 29), &patch_44AB2A_2),	// sub_44AA50 : cmp     word ptr [edi+22h], 1A7h
	tArrayItem(0x44B110, &patch_44B110),	// sub_44AA50 : movsx   edx, word ptr [edi+22h]
	tArrayItem(0x453169, &patch_453169),	// sub_453060 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x4531AA, &patch_4531AA),	// sub_453060 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x4531E0, &patch_4531E0),	// sub_453060 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x45321C, &patch_45321C),	// sub_453060 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x453486, &patch_453486),	// sub_453370 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x4534C7, &patch_4534C7),	// sub_453370 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x4534FD, &patch_4534FD),	// sub_453370 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x453539, &patch_453539),	// sub_453370 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x45426B, &patch_45426B),	// sub_454245 : movsx   ebx, word ptr [eax+22h]
	tArrayItem(0x45426F, &patch_45426F),	// sub_454245 : movzx   ebp, ds:MI_PHONEBOOTH1
	tArrayItem(0x454AEF, &patch_454AEF),	// sub_454AE0 : movzx   edx, ds:MI_PICKUP_HEALTH
	tArrayItem(0x454AFA, &patch_454AFA),	// sub_454AE0 : movzx   ecx, ds:MI_PICKUP_ADRENALINE
	tArrayItem(0x454D33, &patch_454D33),	// sub_454D20 : mov     ax, [esi+18h]
	tArrayItem(0x454D37 | (1 << 29), &patch_454D37_1),	// sub_454D20 : cmp     ax, ds:MI_PICKUP_KILLFRENZY
	tArrayItem(0x454D37 | (2 << 29), &patch_454D37_2),	// sub_454D20 : cmp     ax, ds:MI_PICKUP_KILLFRENZY
	tArrayItem(0x454D7F, &patch_454D7F),	// sub_454D20 : mov     cx, [esi+18h]
	tArrayItem(0x454D83 | (1 << 29), &patch_454D83_1),	// sub_454D20 : cmp     cx, ds:MI_PICKUP_2P_KILLFRENZY
	tArrayItem(0x454D83 | (2 << 29), &patch_454D83_2),	// sub_454D20 : cmp     cx, ds:MI_PICKUP_2P_KILLFRENZY
	tArrayItem(0x455731, &patch_455731),	// sub_455720 : movzx   ecx, ds:MI_PICKUP_CAMERA
	tArrayItem(0x455738, &patch_455738),	// sub_455720 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x455885, &patch_455885),	// sub_455720 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x455889, &patch_455889),	// sub_455720 : movzx   edx, ds:MI_PICKUP_ADRENALINE
	tArrayItem(0x455898, &patch_455898),	// sub_455720 : movzx   ecx, ds:MI_PICKUP_BODYARMOUR
	tArrayItem(0x4558B0, &patch_4558B0),	// sub_455720 : movzx   edx, ds:MI_PICKUP_BRIBE
	tArrayItem(0x4558BF, &patch_4558BF),	// sub_455720 : movzx   ecx, ds:MI_PICKUP_INFO
	tArrayItem(0x4558CA, &patch_4558CA),	// sub_455720 : movzx   edx, ds:MI_PICKUP_KILLFRENZY
	tArrayItem(0x4558D5, &patch_4558D5),	// sub_455720 : movzx   ecx, ds:MI_PICKUP_HEALTH
	tArrayItem(0x4558E0, &patch_4558E0),	// sub_455720 : movzx   edx, ds:MI_PICKUP_BONUS
	tArrayItem(0x4558EB, &patch_4558EB),	// sub_455720 : movzx   ecx, ds:MI_PICKUP_PROPERTY
	tArrayItem(0x4558F6, &patch_4558F6),	// sub_455720 : movzx   edx, ds:MI_PICKUP_PROPERTY_FORSALE
	tArrayItem(0x455901, &patch_455901),	// sub_455720 : movzx   ecx, ds:MI_PICKUP_REVENUE
	tArrayItem(0x455916, &patch_455916),	// sub_455720 : movzx   edx, ds:MI_PICKUP_SAVEGAME
	tArrayItem(0x455921, &patch_455921),	// sub_455720 : movzx   ecx, ds:MI_PICKUP_CLOTHES
	tArrayItem(0x455AB8, &patch_455AB8),	// sub_455720 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x455B49, &patch_455B49),	// sub_455720 : movzx   ecx, ds:MI_PICKUP_PROPERTY
	tArrayItem(0x455B59, &patch_455B59),	// sub_455720 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x455B9B, &patch_455B9B),	// sub_455720 : movzx   ecx, ds:MI_PICKUP_PROPERTY_FORSALE
	tArrayItem(0x455C07, &patch_455C07),	// sub_455720 : mov     cx, [esi+22h]
	tArrayItem(0x455C0B, &patch_455C0B),	// sub_455720 : movsx   eax, cx
	tArrayItem(0x455C8F | (1 << 29), &patch_455C8F_1),	// sub_455720 : cmp     cx, 362
	tArrayItem(0x455C8F | (2 << 29), &patch_455C8F_2),	// sub_455720 : cmp     cx, 362
	tArrayItem(0x45653A | (1 << 29), &patch_45653A_1),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_ADRENALINE
	tArrayItem(0x45653A | (2 << 29), &patch_45653A_2),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_ADRENALINE
	tArrayItem(0x45658D | (1 << 29), &patch_45658D_1),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_BODYARMOUR
	tArrayItem(0x45658D | (2 << 29), &patch_45658D_2),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_BODYARMOUR
	tArrayItem(0x4565D7 | (1 << 29), &patch_4565D7_1),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_INFO
	tArrayItem(0x4565D7 | (2 << 29), &patch_4565D7_2),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_INFO
	tArrayItem(0x4565E4 | (1 << 29), &patch_4565E4_1),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_HEALTH
	tArrayItem(0x4565E4 | (2 << 29), &patch_4565E4_2),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_HEALTH
	tArrayItem(0x45664F | (1 << 29), &patch_45664F_1),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_BONUS
	tArrayItem(0x45664F | (2 << 29), &patch_45664F_2),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_BONUS
	tArrayItem(0x456658 | (1 << 29), &patch_456658_1),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_BRIBE
	tArrayItem(0x456658 | (2 << 29), &patch_456658_2),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_BRIBE
	tArrayItem(0x4566D5 | (1 << 29), &patch_4566D5_1),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_KILLFRENZY
	tArrayItem(0x4566D5 | (2 << 29), &patch_4566D5_2),	// sub_401F0F : cmp     cx, ds:MI_PICKUP_KILLFRENZY
	tArrayItem(0x4566DE | (1 << 29), &patch_4566DE_1),	// sub_401F0F : cmp     cx, 370
	tArrayItem(0x4566DE | (2 << 29), &patch_4566DE_2),	// sub_401F0F : cmp     cx, 370
	tArrayItem(0x456783 | (1 << 29), &patch_456783_1),	// sub_401F0F : cmp     cx, ds:MI_OYSTER
	tArrayItem(0x456783 | (2 << 29), &patch_456783_2),	// sub_401F0F : cmp     cx, ds:MI_OYSTER
	tArrayItem(0x4567A4 | (1 << 29), &patch_4567A4_1),	// sub_401F0F : cmp     cx, ds:MI_HORSESHOE
	tArrayItem(0x4567A4 | (2 << 29), &patch_4567A4_2),	// sub_401F0F : cmp     cx, ds:MI_HORSESHOE
	tArrayItem(0x4568C5, &patch_4568C5),	// sub_4567E0 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x4568C9, &patch_4568C9),	// sub_4567E0 : movzx   edx, ds:MI_OYSTER
	tArrayItem(0x456997, &patch_456997),	// sub_4567E0 : mov     ax, [edi+18h]
	tArrayItem(0x45699B | (1 << 29), &patch_45699B_1),	// sub_4567E0 : cmp     ax, ds:MI_PICKUP_BONUS
	tArrayItem(0x45699B | (2 << 29), &patch_45699B_2),	// sub_4567E0 : cmp     ax, ds:MI_PICKUP_BONUS
	tArrayItem(0x4569B1 | (1 << 29), &patch_4569B1_1),	// sub_4567E0 : cmp     ax, ds:MI_PICKUP_CLOTHES
	tArrayItem(0x4569B1 | (2 << 29), &patch_4569B1_2),	// sub_4567E0 : cmp     ax, ds:MI_PICKUP_CLOTHES
	tArrayItem(0x457606, &patch_457606),	// sub_457410 : movsx   eax, word ptr [edx+22h]
	tArrayItem(0x45760A, &patch_45760A),	// sub_457410 : movzx   ecx, ds:MI_PICKUP_BRIBE
	tArrayItem(0x4577AE, &patch_4577AE),	// sub_457410 : movzx   ecx, ds:MI_PICKUP_CAMERA
	tArrayItem(0x4577C3, &patch_4577C3),	// sub_457410 : movzx   edx, ds:MI_PICKUP_SAVEGAME
	tArrayItem(0x4577CE, &patch_4577CE),	// sub_457410 : movzx   ecx, ds:MI_PICKUP_2P_KILLFRENZY
	tArrayItem(0x4577D9, &patch_4577D9),	// sub_457410 : movzx   edx, ds:MI_PICKUP_2P_COOP
	tArrayItem(0x4579AC | (1 << 29), &patch_4579AC_1),	// sub_457410 : cmp     [edx+22h], bx
	tArrayItem(0x4579AC | (2 << 29), &patch_4579AC_2),	// sub_457410 : cmp     [edx+22h], bx
	tArrayItem(0x457A24, &patch_457A24),	// sub_457410 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x457A95, &patch_457A95),	// sub_457410 : movsx   edx, word ptr [edx+22h]
	tArrayItem(0x457BF1, &patch_457BF1),	// sub_457410 : movsx   ecx, word ptr [ecx+22h]
	tArrayItem(0x457BF5, &patch_457BF5),	// sub_457410 : movzx   edx, ds:MI_PICKUP_BODYARMOUR
	tArrayItem(0x457C39, &patch_457C39),	// sub_457410 : movzx   edx, ds:MI_PICKUP_HEALTH
	tArrayItem(0x457C76, &patch_457C76),	// sub_457410 : movzx   edx, ds:MI_PICKUP_BRIBE
	tArrayItem(0x457CE3, &patch_457CE3),	// sub_457410 : movzx   edx, ds:MI_PICKUP_KILLFRENZY
	tArrayItem(0x457CEF, &patch_457CEF),	// sub_457410 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x457D27 | (1 << 29), &patch_457D27_1),	// sub_457410 : cmp     [eax+22h], bx
	tArrayItem(0x457D27 | (2 << 29), &patch_457D27_2),	// sub_457410 : cmp     [eax+22h], bx
	tArrayItem(0x457D7C, &patch_457D7C),	// sub_457410 : movsx   eax, word ptr [edx+22h]
	tArrayItem(0x457D80, &patch_457D80),	// sub_457410 : movzx   ecx, ds:MI_PICKUP_PROPERTY
	tArrayItem(0x457D8B, &patch_457D8B),	// sub_457410 : movzx   edx, ds:MI_PICKUP_PROPERTY_FORSALE
	tArrayItem(0x457DB6, &patch_457DB6),	// sub_457410 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x457DEC, &patch_457DEC),	// sub_457410 : mov     cx, [eax+22h]
	tArrayItem(0x457EBC, &patch_457EBC),	// sub_457410 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x457EC0, &patch_457EC0),	// sub_457410 : movzx   eax, ds:MI_PICKUP_BRIBE
	tArrayItem(0x457EDD, &patch_457EDD),	// sub_457410 : movsx   eax, word ptr [edx+22h]
	tArrayItem(0x457EE1, &patch_457EE1),	// sub_457410 : movzx   ecx, ds:MI_PICKUP_CAMERA
	tArrayItem(0x457F8B, &patch_457F8B),	// sub_457410 : mov     dx, [ecx+22h]
	tArrayItem(0x458011, &patch_458011),	// sub_457410 : movsx   eax, word ptr [edx+22h]
	tArrayItem(0x458015, &patch_458015),	// sub_457410 : movzx   ecx, ds:MI_PICKUP_SAVEGAME
	tArrayItem(0x458A3B, &patch_458A3B),	// sub_458970 : movzx   edx, ds:MI_MONEY
	tArrayItem(0x45B665, &patch_45B665),	// sub_45B4D0 : mov     dx, [edi+0Ch]
	tArrayItem(0x45B8A9, &patch_45B8A9),	// sub_45B730 : mov     ax, [edi+22h]
	tArrayItem(0x45B91A | (1 << 29), &patch_45B91A_1),	// sub_45B730 : cmp     word ptr [edi+22h], 1B0h
	tArrayItem(0x45B91A | (2 << 29), &patch_45B91A_2),	// sub_45B730 : cmp     word ptr [edi+22h], 1B0h
	tArrayItem(0x45BC34 | (1 << 29), &patch_45BC34_1),	// sub_45BA90 : cmp     word ptr [esi+22h], 1B0h
	tArrayItem(0x45BC34 | (2 << 29), &patch_45BC34_2),	// sub_45BA90 : cmp     word ptr [esi+22h], 1B0h
	tArrayItem(0x45E746, &patch_45E746),	// sub_45E300 : mov     cx, [esi+22h]
	tArrayItem(0x46130F, &patch_46130F),	// sub_461170 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x461313, &patch_461313),	// sub_461170 : add     eax, 0FFFFFE55h
	tArrayItem(0x46212D, &patch_46212D),	// sub_4619C7 : movzx   edx, ds:MI_ROADBLOCKFUCKEDCAR1
	tArrayItem(0x4624EE, &patch_4624EE),	// sub_4619C7 : movzx   ebp, ds:MI_ROADWORKBARRIER1
	tArrayItem(0x464F56, &patch_464F56),	// sub_464F50 : add     ecx, 0FFFFFEE8h ; switch 8 cases 
	tArrayItem(0x46579E, &patch_46579E),	// sub_465680 : movsx   edx, word ptr [edi+22h]
	tArrayItem(0x46963E, &patch_46963E),	// sub_469390 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x46A76F, &patch_46A76F),	// sub_46A760 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x46A985, &patch_46A985),	// sub_46A930 : mov     [ecx+0Ch], dx
	tArrayItem(0x46B27D, &patch_46B27D),	// sub_46B270 : movsx   ecx, word ptr [esi]
	tArrayItem(0x46CE3E, &patch_46CE3E),	// sub_46CD80 : movsx   eax, word ptr [edi+eax*4]
	tArrayItem(0x46E094, &patch_46E094),	// sub_46D050 : movsx   edx, word ptr [edi+22h]
	tArrayItem(0x46E434 | (1 << 29), &patch_46E434_1),	// sub_46D050 : cmp     word ptr [esi+22h], 208h
	tArrayItem(0x46E434 | (2 << 29), &patch_46E434_2),	// sub_46D050 : cmp     word ptr [esi+22h], 208h
	tArrayItem(0x46FF86, &patch_46FF86),	// sub_46FF20 : mov     cx, [esi+0Ch]
	tArrayItem(0x46FF8A | (1 << 29), &patch_46FF8A_1),	// sub_46FF20 : cmp     cx, [ebp+22h]
	tArrayItem(0x472D1F, &patch_472D1F),	// sub_472310 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x4732D6, &patch_4732D6),	// sub_472310 : movzx   edx, ds:MI_HYDRAULICS
	tArrayItem(0x4732EA, &patch_4732EA),	// sub_472310 : movzx   eax, ds:MI_HYDRAULICS
	tArrayItem(0x474AA9, &patch_474AA9),	// sub_474900 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x475D8D, &patch_475D8D),	// sub_474D49 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x4778E6, &patch_4778E6),	// _opcode_handler_23 : movzx   edi, ds:MI_OYSTER
	tArrayItem(0x4778F4, &patch_4778F4),	// _opcode_handler_23 : movzx   edi, ds:MI_HORSESHOE
	tArrayItem(0x477902, &patch_477902),	// _opcode_handler_23 : movzx   edi, ds:MI_PICKUP_CAMERA
	tArrayItem(0x478207, &patch_478207),	// sub_478000 : movsx   edx, word ptr [eax+0Ah]
	tArrayItem(0x478501, &patch_478501),	// sub_478000 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x47854E, &patch_47854E),	// sub_478000 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x47863E, &patch_47863E),	// sub_478000 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x4788D3, &patch_4788D3),	// sub_478000 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x4789F9, &patch_4789F9),	// sub_478000 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x4798B4, &patch_4798B4),	// sub_478000 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x479A35 | (1 << 29), &patch_479A35_1),	// sub_478000 : cmp     word ptr [edi+22h], 1AEh
	tArrayItem(0x479A35 | (2 << 29), &patch_479A35_2),	// sub_478000 : cmp     word ptr [edi+22h], 1AEh
	tArrayItem(0x47AA31, &patch_47AA31),	// sub_47A760 : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x47C142, &patch_47C142),	// sub_47C100 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x47FA95 | (1 << 29), &patch_47FA95_1),	// sub_47FA30 : cmp     word ptr [ecx+22h], 21Bh
	tArrayItem(0x47FA95 | (2 << 29), &patch_47FA95_2),	// sub_47FA30 : cmp     word ptr [ecx+22h], 21Bh
	tArrayItem(0x47FDBC, &patch_47FDBC),	// sub_47FA30 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x47FDF8, &patch_47FDF8),	// sub_47FA30 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x47FE4E, &patch_47FE4E),	// sub_47FA30 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x4805F2, &patch_4805F2),	// sub_47FA30 : movzx   eax, ds:MI_MONEY
	tArrayItem(0x480635, &patch_480635),	// sub_47FA30 : movzx   ecx, ds:MI_MONEY
	tArrayItem(0x480933, &patch_480933),	// sub_47FA30 : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x48158D, &patch_48158D),	// sub_481300 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x481E25, &patch_481E25),	// sub_481300 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x48229B, &patch_48229B),	// sub_481300 : movsx   edx, word ptr [edi+22h]
	tArrayItem(0x48255C, &patch_48255C),	// sub_481300 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x4829D2, &patch_4829D2),	// sub_481300 : movsx   edx, word ptr [edi+22h]
	tArrayItem(0x486B19, &patch_486B19),	// sub_486B00 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x489FD2, &patch_489FD2),	// sub_489500 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x48B224, &patch_48B224),	// sub_48A320 : movzx   ecx, ds:MI_PICKUP_REVENUE
	tArrayItem(0x48CE94, &patch_48CE94),	// sub_48CDD0 : movzx   edx, ds:MI_PICKUP_PROPERTY
	tArrayItem(0x48CF81, &patch_48CF81),	// sub_48CDD0 : movzx   ecx, ds:MI_PICKUP_PROPERTY_FORSALE
	tArrayItem(0x48D2EC, &patch_48D2EC),	// sub_48CDD0 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x48DA90 | (1 << 29), &patch_48DA90_1),	// sub_48CDD0 : cmp     word ptr [eax+22h], 1AEh
	tArrayItem(0x48DA90 | (2 << 29), &patch_48DA90_2),	// sub_48CDD0 : cmp     word ptr [eax+22h], 1AEh
	tArrayItem(0x4912CC, &patch_4912CC),	// sub_490DB0 : mov     ax, [eax+22h]
	tArrayItem(0x4912D0 | (1 << 29), &patch_4912D0_1),	// sub_490DB0 : cmp     ax, 420
	tArrayItem(0x4912D0 | (2 << 29), &patch_4912D0_2),	// sub_490DB0 : cmp     ax, 420
	tArrayItem(0x4912D6 | (1 << 29), &patch_4912D6_1),	// sub_490DB0 : cmp     ax, 438
	tArrayItem(0x4912D6 | (2 << 29), &patch_4912D6_2),	// sub_490DB0 : cmp     ax, 438
	tArrayItem(0x492E14, &patch_492E14),	// sub_492E10 : movsx   eax, word ptr [ecx+eax*2+2D6h]
	tArrayItem(0x49485F, &patch_49485F),	// sub_49485A : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x49835A, &patch_49835A),	// sub_496E00 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x49836A, &patch_49836A),	// sub_496E00 : movsx   ecx, word ptr [edx+eax*2+2D6h]
	tArrayItem(0x4986F7, &patch_4986F7),	// sub_496E00 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x499A0C, &patch_499A0C),	// sub_4998A0 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x49B0F5, &patch_49B0F5),	// sub_49B0E0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x49B3E0, &patch_49B3E0),	// sub_49B3C0 : mov     ax, [ebx]
	tArrayItem(0x49B3E3 | (1 << 29), &patch_49B3E3_1),	// sub_49B3C0 : cmp     ax, 0FFFFh
	tArrayItem(0x49B3F4, &patch_49B3F4),	// sub_49B3C0 : mov     cx, [edi]
	tArrayItem(0x49B3F7, &patch_49B3F7),	// sub_49B3C0 : mov     [ebx], cx
	tArrayItem(0x49B3FA, &patch_49B3FA),	// sub_49B3C0 : mov     ax, [edi]
	tArrayItem(0x49B3FD | (1 << 29), &patch_49B3FD_1),	// sub_49B3C0 : cmp     ax, 0FFFFh
	tArrayItem(0x49B403, &patch_49B403),	// sub_49B3C0 : movsx   edx, ax
	tArrayItem(0x49B435, &patch_49B435),	// sub_49B3C0 : mov     ax, [edi]
	tArrayItem(0x49CCE4, &patch_49CCE4),	// sub_49CCE0 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x49D5A0, &patch_49D5A0),	// sub_49D5A0 : movzx   ecx, ds:MI_TRAFFICLIGHTS
	tArrayItem(0x49D5AF, &patch_49D5AF),	// sub_49D5A0 : movzx   edx, ds:MI_TRAFFICLIGHTS_VERTICAL
	tArrayItem(0x49D5BA, &patch_49D5BA),	// sub_49D5A0 : movzx   ecx, ds:MI_TRAFFICLIGHTS_MIAMI
	tArrayItem(0x49D5C5, &patch_49D5C5),	// sub_49D5A0 : movzx   edx, ds:MI_TRAFFICLIGHTS_VEGAS
	tArrayItem(0x49D5D0, &patch_49D5D0),	// sub_49D5A0 : movzx   ecx, ds:MI_TRAFFICLIGHTS_TWOVERTICAL
	tArrayItem(0x49D5DB, &patch_49D5DB),	// sub_49D5A0 : movzx   edx, ds:MI_TRAFFICLIGHTS_3
	tArrayItem(0x49D5E6, &patch_49D5E6),	// sub_49D5A0 : movzx   ecx, ds:MI_TRAFFICLIGHTS_4
	tArrayItem(0x49D5F1, &patch_49D5F1),	// sub_49D5A0 : movzx   edx, ds:MI_TRAFFICLIGHTS_GAY
	tArrayItem(0x49D5FC, &patch_49D5FC),	// sub_49D5A0 : movzx   ecx, ds:MI_TRAFFICLIGHTS_5
	tArrayItem(0x49DB06, &patch_49DB06),	// sub_49DAB0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x49DB0A, &patch_49DB0A),	// sub_49DAB0 : movzx   edx, ds:MI_TRAFFICLIGHTS_3
	tArrayItem(0x49DB15, &patch_49DB15),	// sub_49DAB0 : movzx   ecx, ds:MI_TRAFFICLIGHTS_4
	tArrayItem(0x49DB20, &patch_49DB20),	// sub_49DAB0 : movzx   edx, ds:MI_TRAFFICLIGHTS_5
	tArrayItem(0x49DB2B, &patch_49DB2B),	// sub_49DAB0 : movzx   ecx, ds:MI_TRAFFICLIGHTS_GAY
	tArrayItem(0x49DB36, &patch_49DB36),	// sub_49DAB0 : movzx   edx, ds:MI_TRAFFICLIGHTS_MIAMI
	tArrayItem(0x49DB79, &patch_49DB79),	// sub_49DAB0 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x49E018, &patch_49E018),	// sub_49DAB0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x49E01C, &patch_49E01C),	// sub_49DAB0 : movzx   edx, ds:MI_TRAFFICLIGHTS_4
	tArrayItem(0x49E02B, &patch_49E02B),	// sub_49DAB0 : movzx   ecx, ds:MI_TRAFFICLIGHTS_GAY
	tArrayItem(0x49E03A, &patch_49E03A),	// sub_49DAB0 : movzx   edx, ds:MI_TRAFFICLIGHTS_5
	tArrayItem(0x49E0E1, &patch_49E0E1),	// sub_49DAB0 : movzx   ecx, ds:MI_TRAFFICLIGHTS
	tArrayItem(0x49FBBC, &patch_49FBBC),	// sub_49FB30 : mov     al, [esi+22h]
	tArrayItem(0x49FBDE, &patch_49FBDE),	// sub_49FB30 : mov     cl, [esi+22h]
	tArrayItem(0x49FFC7, &patch_49FFC7),	// sub_49FF20 : mov     al, [esi+22h]
	tArrayItem(0x49FFE9, &patch_49FFE9),	// sub_49FF20 : mov     cl, [esi+22h]
	tArrayItem(0x4A0217, &patch_4A0217),	// sub_4A0170 : mov     al, [esi+22h]
	tArrayItem(0x4A0239, &patch_4A0239),	// sub_4A0170 : mov     cl, [esi+22h]
	tArrayItem(0x4A0467, &patch_4A0467),	// sub_4A03C0 : mov     al, [esi+22h]
	tArrayItem(0x4A0489, &patch_4A0489),	// sub_4A03C0 : mov     cl, [esi+22h]
	tArrayItem(0x4A0686, &patch_4A0686),	// sub_4A0610 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x4A06B9, &patch_4A06B9),	// sub_4A0610 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x4A0A36, &patch_4A0A36),	// sub_4A09C0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x4A0A69, &patch_4A0A69),	// sub_4A09C0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x4AC876, &patch_4AC876),	// sub_4AC840 : mov     [esi+0Ch], ax
	tArrayItem(0x4AC9C5, &patch_4AC9C5),	// sub_4AC990 : mov     [esi+0Ch], ax
	tArrayItem(0x4ACD26, &patch_4ACD26),	// sub_4ACCF0 : mov     [esi+0Ch], ax
	tArrayItem(0x4ACF36, &patch_4ACF36),	// sub_4ACF00 : mov     [esi+0Ch], ax
	tArrayItem(0x4AF464, &patch_4AF464),	// sub_4AF460 : movsx   edx, word ptr [ecx+22h]
	tArrayItem(0x4AF558, &patch_4AF558),	// sub_4AF4B0 : movsx   eax, word ptr [ebx+22h]
	tArrayItem(0x4B25AB, &patch_4B25AB),	// sub_4B2580 : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x4B25AF, &patch_4B25AF),	// sub_4B2580 : movzx   ecx, ds:MI_ESCALATORSTEP
	tArrayItem(0x4B25BA, &patch_4B25BA),	// sub_4B2580 : movzx   edx, ds:MI_ESCALATORSTEP8
	tArrayItem(0x4B3138, &patch_4B3138),	// sub_4B3120 : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x4B49AF, &patch_4B49AF),	// sub_4B4950 : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x4B6C0C, &patch_4B6C0C),	// sub_4B6BC0 : mov     dx, [esi+0Ch]
	tArrayItem(0x4B6C74, &patch_4B6C74),	// sub_4B6C40 : movsx   ecx, word ptr [esi+32h]
	tArrayItem(0x4B6C78, &patch_4B6C78),	// sub_4B6C40 : movsx   edx, word ptr [esi+30h]
	tArrayItem(0x4B6C8F, &patch_4B6C8F),	// sub_4B6C40 : mov     cx, [esi+0Ch]
	tArrayItem(0x4B6CF4, &patch_4B6CF4),	// sub_4B6CC0 : movsx   ecx, word ptr [esi+0Eh]
	tArrayItem(0x4B6D0A, &patch_4B6D0A),	// sub_4B6CC0 : mov     dx, [esi+0Ch]
	tArrayItem(0x4B6D74, &patch_4B6D74),	// sub_4B6D40 : movsx   ecx, word ptr [esi+0Eh]
	tArrayItem(0x4B6D8A, &patch_4B6D8A),	// sub_4B6D40 : mov     dx, [esi+0Ch]
	tArrayItem(0x4B7EF0, &patch_4B7EF0),	// sub_4B7EF0 : movsx   eax, word ptr [ecx+10h]
	tArrayItem(0x4B7F80, &patch_4B7F80),	// sub_4B7F80 : movsx   eax, word ptr [ecx+30h]
	tArrayItem(0x4B7FA0, &patch_4B7FA0),	// sub_4B7FA0 : movsx   eax, word ptr [ecx+32h]
	tArrayItem(0x4B7FC0, &patch_4B7FC0),	// sub_4B7FC0 : movsx   eax, word ptr [ecx+0Eh]
	tArrayItem(0x4B7FF0, &patch_4B7FF0),	// sub_4B7FF0 : movsx   eax, word ptr [ecx+0Eh]
	tArrayItem(0x4B8D97, &patch_4B8D97),	// sub_4B8CE0 : movsx   ebx, word ptr [edi+30h]
	tArrayItem(0x4B8D9B, &patch_4B8D9B),	// sub_4B8CE0 : movsx   edi, word ptr [edi+32h]
	tArrayItem(0x4B92E4, &patch_4B92E4),	// sub_4B92B0 : movsx   edi, word ptr [ecx+0Eh]
	tArrayItem(0x4B95CC, &patch_4B95CC),	// sub_4B9470 : movsx   eax, word ptr [ebx+0Eh]
	tArrayItem(0x4B9A14, &patch_4B9A14),	// sub_4B99F0 : movsx   eax, word ptr [eax+0Eh]
	tArrayItem(0x4B9C15, &patch_4B9C15),	// sub_4B9BE0 : movsx   eax, word ptr [esi+0Eh]
	tArrayItem(0x4B9CB8, &patch_4B9CB8),	// sub_4B9C90 : movsx   eax, word ptr [eax+0Eh]
	tArrayItem(0x4B9D6A, &patch_4B9D6A),	// sub_4B9D40 : movsx   eax, word ptr [esi+0Eh]
	tArrayItem(0x4B9DEA, &patch_4B9DEA),	// sub_4B9DD0 : movsx   eax, word ptr [esi+0Eh]
	tArrayItem(0x4BA9A9, &patch_4BA9A9),	// sub_4BA990 : movsx   eax, word ptr [eax+0Eh]
	tArrayItem(0x4BAA49, &patch_4BAA49),	// sub_4BAA30 : movsx   eax, word ptr [eax+0Eh]
	tArrayItem(0x4BAAE9, &patch_4BAAE9),	// sub_4BAAD0 : movsx   eax, word ptr [eax+0Eh]
	tArrayItem(0x4BAC29, &patch_4BAC29),	// sub_4BAC10 : movsx   eax, word ptr [eax+0Eh]
	tArrayItem(0x4BB3A1, &patch_4BB3A1),	// sub_4BB2E0 : movsx   eax, word ptr [ecx+0Eh]
	tArrayItem(0x4BB819, &patch_4BB819),	// sub_4BB800 : movsx   eax, word ptr [eax+0Eh]
	tArrayItem(0x4BBD18, &patch_4BBD18),	// sub_4BBCD0 : movsx   eax, word ptr [esi+0Eh]
	tArrayItem(0x4BBE50, &patch_4BBE50),	// sub_4BBE30 : movsx   edi, word ptr [ecx+0Eh]
	tArrayItem(0x4BBFC9, &patch_4BBFC9),	// sub_4BBFB0 : movsx   eax, word ptr [eax+0Eh]
	tArrayItem(0x4BC072, &patch_4BC072),	// sub_4BC050 : movsx   ecx, word ptr [eax+0Eh]
	tArrayItem(0x4BC258, &patch_4BC258),	// sub_4BC230 : movsx   eax, word ptr [eax+0Eh]
	tArrayItem(0x4BC6DE, &patch_4BC6DE),	// sub_4BC600 : movsx   ecx, word ptr [ebp+10h]
	tArrayItem(0x4BC73C, &patch_4BC73C),	// sub_4BC710 : movsx   eax, word ptr [ebx+0Eh]
	tArrayItem(0x4BCCF8, &patch_4BCCF8),	// sub_4BCC30 : movsx   edi, word ptr [esi+0Eh]
	tArrayItem(0x4BDC46, &patch_4BDC46),	// sub_4BDB80 : movsx   eax, word ptr [ebx+30h]
	tArrayItem(0x4BDC4A, &patch_4BDC4A),	// sub_4BDB80 : movsx   ebx, word ptr [ebx+32h]
	tArrayItem(0x4BE891, &patch_4BE891),	// sub_4BE7D0 : movsx   esi, word ptr [ebp+30h]
	tArrayItem(0x4BF307, &patch_4BF307),	// sub_4BF2B0 : movsx   eax, word ptr [esi+0Eh]
	tArrayItem(0x4BF9CC, &patch_4BF9CC),	// sub_4BF9B0 : movsx   eax, word ptr [edi+0Eh]
	tArrayItem(0x4C0925, &patch_4C0925),	// sub_4C0170 : movsx   eax, word ptr [ecx+2Ch]
	tArrayItem(0x4C0929, &patch_4C0929),	// sub_4C0170 : movsx   ecx, word ptr [ecx+0Eh]
	tArrayItem(0x4C0C0F, &patch_4C0C0F),	// sub_4C0BD0 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x4C1674, &patch_4C1674),	// sub_4C1590 : movsx   eax, word ptr [ebx+0Eh]
	tArrayItem(0x4C19CF, &patch_4C19CF),	// sub_4C19A0 : movsx   eax, word ptr [edi+0Eh]
	tArrayItem(0x4C2663, &patch_4C2663),	// sub_4C2610 : movsx   eax, word ptr [edi+0Eh]
	tArrayItem(0x4C2975, &patch_4C2975),	// sub_4C2840 : movsx   eax, word ptr [ebx+0Eh]
	tArrayItem(0x4C2FFD, &patch_4C2FFD),	// sub_4C2FC0 : movsx   eax, word ptr [edi+0Eh]
	tArrayItem(0x4C3459, &patch_4C3459),	// sub_4C3430 : movsx   eax, word ptr [ecx+0Eh]
	tArrayItem(0x4C364E, &patch_4C364E),	// sub_4C35F0 : movsx   eax, word ptr [edi+0Eh]
	tArrayItem(0x4C488E, &patch_4C488E),	// sub_4C47E0 : mov     [ebp+2], di
	tArrayItem(0x4C4A30, &patch_4C4A30),	// sub_4C4A30 : movsx   eax, word ptr [ecx+2]
	tArrayItem(0x4C4A6E, &patch_4C4A6E),	// sub_4C4A60 : mov     word ptr [eax+0Ah], 0FFFFh
	tArrayItem(0x4C4B19, &patch_4C4B19),	// sub_4C4B10 : mov     [ecx+0Ah], dx
	tArrayItem(0x4C4B51 | (1 << 29), &patch_4C4B51_1),	// _ZN14CBaseModelInfo16SetTexDictionaryEPKcS1_ : cmp     ax, 0FFFFh
	tArrayItem(0x4C4B55, &patch_4C4B55),	// _ZN14CBaseModelInfo16SetTexDictionaryEPKcS1_ : mov     [esi+0Ah], ax
	tArrayItem(0x4C4B80, &patch_4C4B80),	// sub_4C4B80 : movsx   eax, word ptr [ecx+0Ah]
	tArrayItem(0x4C4B90, &patch_4C4B90),	// sub_4C4B90 : movsx   eax, word ptr [ecx+0Ah]
	tArrayItem(0x4C4BA0, &patch_4C4BA0),	// sub_4C4BA0 : movsx   eax, word ptr [ecx+0Ah]
	tArrayItem(0x4C4BB0, &patch_4C4BB0),	// sub_4C4BB0 : movsx   eax, word ptr [ecx+0Ah]
	tArrayItem(0x4C4BE4, &patch_4C4BE4),	// _ZN14CBaseModelInfo11SetColModelEP9CColModelb : movsx   eax, word ptr [eax+2]
	tArrayItem(0x4C4D92, &patch_4C4D92),	// sub_4C4D50 : mov     [esi+0Ah], ax
	tArrayItem(0x4C85D2, &patch_4C85D2),	// sub_4C8500 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x4C86B8 | (1 << 29), &patch_4C86B8_1),	// sub_4C86B0 : cmp     word ptr [ecx], 0FFFFh
	tArrayItem(0x4C86C9 | (1 << 29), &patch_4C86C9_1),	// sub_4C86B0 : cmp     word ptr [ecx], 0FFFFh
	tArrayItem(0x4C86D8 | (1 << 29), &patch_4C86D8_1),	// sub_4C86D0 : cmp     word ptr [edx], 0FFFFh
	tArrayItem(0x4C86E9 | (1 << 29), &patch_4C86E9_1),	// sub_4C86D0 : cmp     word ptr [edx], 0FFFFh
	tArrayItem(0x4C86F4, &patch_4C86F4),	// sub_4C86D0 : mov     [ecx+eax*2+2FAh], dx
	tArrayItem(0x4CE351, &patch_4CE351),	// sub_4CE220 : mov     cx, [esi+0Ch]
	tArrayItem(0x4CE560, &patch_4CE560),	// sub_4CE3B0 : mov     cx, [esi+0Ch]
	tArrayItem(0x4CE68D, &patch_4CE68D),	// sub_4CE5C0 : mov     dx, [esi+0Ch]
	tArrayItem(0x4CE7AC, &patch_4CE7AC),	// sub_4CE6E0 : mov     cx, [esi+0Ch]
	tArrayItem(0x4CE955, &patch_4CE955),	// sub_4CE940 : mov     [eax+0Ah], cx
	tArrayItem(0x4CEE4E, &patch_4CEE4E),	// sub_4CEE40 : mov     cx, [ebp+0Ch]
	tArrayItem(0x4CEE52, &patch_4CEE52),	// sub_4CEE40 : mov     [ebx+0Ch], cx
	tArrayItem(0x4CEED2, &patch_4CEED2),	// sub_4CEEC0 : mov     [esi+0Ch], cx
	tArrayItem(0x4CEED6, &patch_4CEED6),	// sub_4CEEC0 : mov     dx, [edi+0Ah]
	tArrayItem(0x4CEF74, &patch_4CEF74),	// sub_4CEF60 : mov     [esi+0Ah], ax
	tArrayItem(0x4CFB7E, &patch_4CFB7E),	// sub_4CFB70 : mov     [ecx+0Ah], ax
	tArrayItem(0x4DAB71, &patch_4DAB71),	// sub_506ED0 : mov     ax, [ebx+22h]
	tArrayItem(0x4DAB75 | (1 << 29), &patch_4DAB75_1),	// sub_506ED0 : cmp     ax, 344
	tArrayItem(0x4DAB75 | (2 << 29), &patch_4DAB75_2),	// sub_506ED0 : cmp     ax, 344
	tArrayItem(0x4DAB82, &patch_4DAB82),	// sub_506ED0 : movzx   ecx, ds:MI_GRASSHOUSE
	tArrayItem(0x4DBB40, &patch_4DBB40),	// sub_506EB0 : mov     ax, [esi+22h]
	tArrayItem(0x4DBB44 | (1 << 29), &patch_4DBB44_1),	// sub_506EB0 : cmp     ax, 344
	tArrayItem(0x4DBB44 | (2 << 29), &patch_4DBB44_2),	// sub_506EB0 : cmp     ax, 344
	tArrayItem(0x4DBB5F | (1 << 29), &patch_4DBB5F_1),	// sub_506EB0 : cmp     ax, 363
	tArrayItem(0x4DBB5F | (2 << 29), &patch_4DBB5F_2),	// sub_506EB0 : cmp     ax, 363
	tArrayItem(0x4DBB7A | (1 << 29), &patch_4DBB7A_1),	// sub_506EB0 : cmp     ax, 342
	tArrayItem(0x4DBB7A | (2 << 29), &patch_4DBB7A_2),	// sub_506EB0 : cmp     ax, 342
	tArrayItem(0x4DBB84 | (1 << 29), &patch_4DBB84_1),	// sub_506EB0 : cmp     ax, 364
	tArrayItem(0x4DBB84 | (2 << 29), &patch_4DBB84_2),	// sub_506EB0 : cmp     ax, 364
	tArrayItem(0x4DBB8E | (1 << 29), &patch_4DBB8E_1),	// sub_506EB0 : cmp     ax, 343
	tArrayItem(0x4DBB8E | (2 << 29), &patch_4DBB8E_2),	// sub_506EB0 : cmp     ax, 343
	tArrayItem(0x4DBB98, &patch_4DBB98),	// sub_506EB0 : movzx   edx, ds:MI_BASKETBALL
	tArrayItem(0x4DBBB8, &patch_4DBBB8),	// sub_506EB0 : movzx   ecx, ds:MI_PUNCHBAG
	tArrayItem(0x4DBBD2, &patch_4DBBD2),	// sub_506EB0 : movzx   edx, ds:MI_GRASSHOUSE
	tArrayItem(0x4DBBEC, &patch_4DBBEC),	// sub_506EB0 : movzx   ecx, ds:MI_IMY_GRAY_CRATE
	tArrayItem(0x4E335E, &patch_4E335E),	// sub_4E3350 : mov     [ecx+0Ch], dx
	tArrayItem(0x4E692E, &patch_4E692E),	// sub_4E68D0 : movsx   edi, word ptr [ecx+22h]
	tArrayItem(0x4F51F6 | (1 << 29), &patch_4F51F6_1),	// sub_4F51F0 : cmp     word ptr [eax+22h], 1C9h
	tArrayItem(0x4F51F6 | (2 << 29), &patch_4F51F6_2),	// sub_4F51F0 : cmp     word ptr [eax+22h], 1C9h
	tArrayItem(0x4F5316 | (1 << 29), &patch_4F5316_1),	// sub_4F5310 : cmp     word ptr [eax+22h], 1C9h
	tArrayItem(0x4F5316 | (2 << 29), &patch_4F5316_2),	// sub_4F5310 : cmp     word ptr [eax+22h], 1C9h
	tArrayItem(0x4F5645, &patch_4F5645),	// sub_4F55C0 : mov     [esi+14Ah], ax
	tArrayItem(0x4F5A1B, &patch_4F5A1B),	// sub_4F5700 : mov     [esi+14Ah], di
	tArrayItem(0x4F5C43, &patch_4F5C43),	// sub_4F5C40 : mov     ax, [eax+22h]
	tArrayItem(0x4F5C47 | (1 << 29), &patch_4F5C47_1),	// sub_4F5C40 : cmp     ax, 487
	tArrayItem(0x4F5C47 | (2 << 29), &patch_4F5C47_2),	// sub_4F5C40 : cmp     ax, 487
	tArrayItem(0x4F5C4D | (1 << 29), &patch_4F5C4D_1),	// sub_4F5C40 : cmp     ax, 488
	tArrayItem(0x4F5C4D | (2 << 29), &patch_4F5C4D_2),	// sub_4F5C40 : cmp     ax, 488
	tArrayItem(0x4F5D35 | (1 << 29), &patch_4F5D35_1),	// sub_4F5D00 : cmp     word ptr [edx+22h], 1C9h
	tArrayItem(0x4F5D35 | (2 << 29), &patch_4F5D35_2),	// sub_4F5D00 : cmp     word ptr [edx+22h], 1C9h
	tArrayItem(0x4F62E4 | (1 << 29), &patch_4F62E4_1),	// sub_4F62A0 : cmp     word ptr [eax+22h], 1A7h
	tArrayItem(0x4F62E4 | (2 << 29), &patch_4F62E4_2),	// sub_4F62A0 : cmp     word ptr [eax+22h], 1A7h
	tArrayItem(0x4F76FC, &patch_4F76FC),	// sub_4F7670 : mov     [ebp+14Ah], si
	tArrayItem(0x4F77B4, &patch_4F77B4),	// sub_4F7670 : mov     ax, [edx+22h]
	tArrayItem(0x4F7814, &patch_4F7814),	// sub_4F7670 : movsx   eax, word ptr [edx+22h]
	tArrayItem(0x4F7818, &patch_4F7818),	// sub_4F7670 : add     eax, 0FFFFFE40h ; switch 136 cases 
	tArrayItem(0x4F8213 | (1 << 29), &patch_4F8213_1),	// sub_4F8070 : cmp     word ptr [edx+22h], 1C9h
	tArrayItem(0x4F8213 | (2 << 29), &patch_4F8213_2),	// sub_4F8070 : cmp     word ptr [edx+22h], 1C9h
	tArrayItem(0x4F8972 | (1 << 29), &patch_4F8972_1),	// sub_4F8940 : cmp     word ptr [ecx+22h], 1C9h
	tArrayItem(0x4F8972 | (2 << 29), &patch_4F8972_2),	// sub_4F8940 : cmp     word ptr [ecx+22h], 1C9h
	tArrayItem(0x4F8B47, &patch_4F8B47),	// sub_4F8B00 : movsx   eax, word ptr [ebx+22h]
	tArrayItem(0x4F8B4B, &patch_4F8B4B),	// sub_4F8B00 : add     eax, 0FFFFFE4Dh
	tArrayItem(0x4F9CBC | (1 << 29), &patch_4F9CBC_1),	// sub_4F99D0 : cmp     word ptr [ecx+22h], 1A7h
	tArrayItem(0x4F9CBC | (2 << 29), &patch_4F9CBC_2),	// sub_4F99D0 : cmp     word ptr [ecx+22h], 1A7h
	tArrayItem(0x4FB26B, &patch_4FB26B),	// sub_4FB260 : mov     ax, [ecx+22h]
	tArrayItem(0x4FB26F | (1 << 29), &patch_4FB26F_1),	// sub_4FB260 : cmp     ax, 443
	tArrayItem(0x4FB26F | (2 << 29), &patch_4FB26F_2),	// sub_4FB260 : cmp     ax, 443
	tArrayItem(0x4FB275 | (1 << 29), &patch_4FB275_1),	// sub_4FB260 : cmp     ax, 486
	tArrayItem(0x4FB275 | (2 << 29), &patch_4FB275_2),	// sub_4FB260 : cmp     ax, 486
	tArrayItem(0x4FB27B | (1 << 29), &patch_4FB27B_1),	// sub_4FB260 : cmp     ax, 406
	tArrayItem(0x4FB27B | (2 << 29), &patch_4FB27B_2),	// sub_4FB260 : cmp     ax, 406
	tArrayItem(0x4FB281 | (1 << 29), &patch_4FB281_1),	// sub_4FB260 : cmp     ax, 524
	tArrayItem(0x4FB281 | (2 << 29), &patch_4FB281_2),	// sub_4FB260 : cmp     ax, 524
	tArrayItem(0x4FB287 | (1 << 29), &patch_4FB287_1),	// sub_4FB260 : cmp     ax, 592
	tArrayItem(0x4FB287 | (2 << 29), &patch_4FB287_2),	// sub_4FB260 : cmp     ax, 592
	tArrayItem(0x4FB28D | (1 << 29), &patch_4FB28D_1),	// sub_4FB260 : cmp     ax, 530
	tArrayItem(0x4FB28D | (2 << 29), &patch_4FB28D_2),	// sub_4FB260 : cmp     ax, 530
	tArrayItem(0x4FB343, &patch_4FB343),	// sub_4FB260 : movsx   eax, word ptr [edx+22h]
	tArrayItem(0x4FB347, &patch_4FB347),	// sub_4FB260 : add     eax, 0FFFFFE6Ah
	tArrayItem(0x4FB864, &patch_4FB864),	// sub_4FB6C0 : mov     [esi+14Ah], cx
	tArrayItem(0x4FF980, &patch_4FF980),	// sub_4FF900 : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x4FF984, &patch_4FF984),	// sub_4FF900 : add     eax, 0FFFFFDF9h
	tArrayItem(0x5018C7, &patch_5018C7),	// sub_501650 : movsx   eax, word ptr [esi+0B4h]
	tArrayItem(0x501AB9, &patch_501AB9),	// sub_501AB0 : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x501ABD, &patch_501ABD),	// sub_501AB0 : add     eax, 0FFFFFE4Dh
	tArrayItem(0x501C73, &patch_501C73),	// sub_501C50 : movsx   eax, word ptr [edx+22h]
	tArrayItem(0x501C77, &patch_501C77),	// sub_501C50 : add     eax, 0FFFFFDF9h
	tArrayItem(0x501E82, &patch_501E82),	// sub_501E10 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x502222 | (1 << 29), &patch_502222_1),	// sub_501E10 : cmp     word ptr [eax+22h], 214h
	tArrayItem(0x502222 | (2 << 29), &patch_502222_2),	// sub_501E10 : cmp     word ptr [eax+22h], 214h
	tArrayItem(0x509A43, &patch_509A43),	// sub_509A30 : movzx   edx, ds:MI_SINGLESTREETLIGHTS2
	tArrayItem(0x509A52, &patch_509A52),	// sub_509A30 : movzx   ecx, ds:MI_SINGLESTREETLIGHTS3
	tArrayItem(0x509A5D, &patch_509A5D),	// sub_509A30 : movzx   edx, ds:MI_BOLLARDLIGHT
	tArrayItem(0x509A68, &patch_509A68),	// sub_509A30 : movzx   ecx, ds:MI_MLAMPPOST
	tArrayItem(0x509A73, &patch_509A73),	// sub_509A30 : movzx   edx, ds:MI_STREETLAMP1
	tArrayItem(0x509A7E, &patch_509A7E),	// sub_509A30 : movzx   ecx, ds:MI_STREETLAMP2
	tArrayItem(0x509A89, &patch_509A89),	// sub_509A30 : movzx   edx, ds:MI_TELPOLE02
	tArrayItem(0x509A94, &patch_509A94),	// sub_509A30 : movzx   ecx, ds:MI_TRAFFICLIGHTS_MIAMI
	tArrayItem(0x509A9F, &patch_509A9F),	// sub_509A30 : movzx   edx, ds:MI_TRAFFICLIGHTS_TWOVERTICAL
	tArrayItem(0x509AAA, &patch_509AAA),	// sub_509A30 : movzx   ecx, ds:MI_TRAFFICLIGHTS_3
	tArrayItem(0x509AB5, &patch_509AB5),	// sub_509A30 : movzx   edx, ds:MI_TRAFFICLIGHTS_4
	tArrayItem(0x509AC0, &patch_509AC0),	// sub_509A30 : movzx   ecx, ds:MI_TRAFFICLIGHTS_GAY
	tArrayItem(0x509ACB, &patch_509ACB),	// sub_509A30 : movzx   edx, ds:MI_TRAFFICLIGHTS_5
	tArrayItem(0x50A48B, &patch_50A48B),	// sub_50A480 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x50A4A8, &patch_50A4A8),	// sub_50A480 : movsx   ebx, word ptr [edi+22h]
	tArrayItem(0x50D597, &patch_50D597),	// sub_50D590 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x512570 | (1 << 29), &patch_512570_1),	// sub_512110 : cmp     word ptr [ecx+22h], 1AEh
	tArrayItem(0x512570 | (2 << 29), &patch_512570_2),	// sub_512110 : cmp     word ptr [ecx+22h], 1AEh
	tArrayItem(0x51359A, &patch_51359A),	// sub_513510 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x51362C, &patch_51362C),	// sub_513510 : movsx   edx, word ptr [ebp+22h]
	tArrayItem(0x514C7C, &patch_514C7C),	// sub_514B80 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x516240, &patch_516240),	// sub_5161A0 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x516E0A, &patch_516E0A),	// sub_516B20 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x5172EE, &patch_5172EE),	// sub_517130 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x5180EB, &patch_5180EB),	// sub_517EA0 : movsx   eax, word ptr [ecx+22h]
	tArrayItem(0x51B316, &patch_51B316),	// sub_51B126 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x51BB37, &patch_51BB37),	// sub_51B850 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x51BBB7, &patch_51BBB7),	// sub_51B850 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x51BE02, &patch_51BE02),	// sub_51B850 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x51D22B, &patch_51D22B),	// sub_51D100 : movsx   edx, word ptr [edi+22h]
	tArrayItem(0x51D864 | (1 << 29), &patch_51D864_1),	// sub_409B61 : cmp     word ptr [edx+22h], 1CCh
	tArrayItem(0x51D864 | (2 << 29), &patch_51D864_2),	// sub_409B61 : cmp     word ptr [edx+22h], 1CCh
	tArrayItem(0x51D870 | (1 << 29), &patch_51D870_1),	// sub_409B61 : cmp     word ptr [eax+22h], 1B0h
	tArrayItem(0x51D870 | (2 << 29), &patch_51D870_2),	// sub_409B61 : cmp     word ptr [eax+22h], 1B0h
	tArrayItem(0x51D92B | (1 << 29), &patch_51D92B_1),	// sub_409B61 : cmp     word ptr [edx+22h], 1CCh
	tArrayItem(0x51D92B | (2 << 29), &patch_51D92B_2),	// sub_409B61 : cmp     word ptr [edx+22h], 1CCh
	tArrayItem(0x51DA60 | (1 << 29), &patch_51DA60_1),	// sub_409B61 : cmp     word ptr [ecx+22h], 1CCh
	tArrayItem(0x51DA60 | (2 << 29), &patch_51DA60_2),	// sub_409B61 : cmp     word ptr [ecx+22h], 1CCh
	tArrayItem(0x51DCFC | (1 << 29), &patch_51DCFC_1),	// sub_409B61 : cmp     word ptr [eax+22h], 1CCh
	tArrayItem(0x51DCFC | (2 << 29), &patch_51DCFC_2),	// sub_409B61 : cmp     word ptr [eax+22h], 1CCh
	tArrayItem(0x51DE84 | (1 << 29), &patch_51DE84_1),	// sub_409B61 : cmp     word ptr [eax+22h], 1CCh
	tArrayItem(0x51DE84 | (2 << 29), &patch_51DE84_2),	// sub_409B61 : cmp     word ptr [eax+22h], 1CCh
	tArrayItem(0x51E5AC | (1 << 29), &patch_51E5AC_1),	// sub_4014E2 : cmp     word ptr [eax+22h], 1CCh
	tArrayItem(0x51E5AC | (2 << 29), &patch_51E5AC_2),	// sub_4014E2 : cmp     word ptr [eax+22h], 1CCh
	tArrayItem(0x51E5B8 | (1 << 29), &patch_51E5B8_1),	// sub_4014E2 : cmp     word ptr [esi+22h], 1B0h
	tArrayItem(0x51E5B8 | (2 << 29), &patch_51E5B8_2),	// sub_4014E2 : cmp     word ptr [esi+22h], 1B0h
	tArrayItem(0x51E773 | (1 << 29), &patch_51E773_1),	// sub_4014E2 : cmp     word ptr [ecx+22h], 1CCh
	tArrayItem(0x51E773 | (2 << 29), &patch_51E773_2),	// sub_4014E2 : cmp     word ptr [ecx+22h], 1CCh
	tArrayItem(0x51E937 | (1 << 29), &patch_51E937_1),	// sub_4014E2 : cmp     word ptr [eax+22h], 1CCh
	tArrayItem(0x51E937 | (2 << 29), &patch_51E937_2),	// sub_4014E2 : cmp     word ptr [eax+22h], 1CCh
	tArrayItem(0x51EF39 | (1 << 29), &patch_51EF39_1),	// sub_4014E2 : cmp     word ptr [edx+22h], 1CCh
	tArrayItem(0x51EF39 | (2 << 29), &patch_51EF39_2),	// sub_4014E2 : cmp     word ptr [edx+22h], 1CCh
	tArrayItem(0x51F15B | (1 << 29), &patch_51F15B_1),	// sub_4014E2 : cmp     word ptr [ecx+22h], 1CCh
	tArrayItem(0x51F15B | (2 << 29), &patch_51F15B_2),	// sub_4014E2 : cmp     word ptr [ecx+22h], 1CCh
	tArrayItem(0x520225, &patch_520225),	// sub_520190 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x520249, &patch_520249),	// sub_520190 : movsx   edx, word ptr [eax]
	tArrayItem(0x520282, &patch_520282),	// sub_520190 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x52034B, &patch_52034B),	// sub_520190 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x524624, &patch_524624),	// sub_5245BD : mov     ax, [edi+22h]
	tArrayItem(0x524628 | (1 << 29), &patch_524628_1),	// sub_5245BD : cmp     ax, 1B9h
	tArrayItem(0x524628 | (2 << 29), &patch_524628_2),	// sub_5245BD : cmp     ax, 1B9h
	tArrayItem(0x524632 | (1 << 29), &patch_524632_1),	// sub_5245BD : cmp     ax, 464
	tArrayItem(0x524632 | (2 << 29), &patch_524632_2),	// sub_5245BD : cmp     ax, 464
	tArrayItem(0x52463C | (1 << 29), &patch_52463C_1),	// sub_5245BD : cmp     ax, 564
	tArrayItem(0x52463C | (2 << 29), &patch_52463C_2),	// sub_5245BD : cmp     ax, 564
	tArrayItem(0x524642 | (1 << 29), &patch_524642_1),	// sub_5245BD : cmp     ax, 252h
	tArrayItem(0x524642 | (2 << 29), &patch_524642_2),	// sub_5245BD : cmp     ax, 252h
	tArrayItem(0x524648 | (1 << 29), &patch_524648_1),	// sub_5245BD : cmp     ax, 1D1h
	tArrayItem(0x524648 | (2 << 29), &patch_524648_2),	// sub_5245BD : cmp     ax, 1D1h
	tArrayItem(0x52464E | (1 << 29), &patch_52464E_1),	// sub_5245BD : cmp     ax, 1F5h
	tArrayItem(0x52464E | (2 << 29), &patch_52464E_2),	// sub_5245BD : cmp     ax, 1F5h
	tArrayItem(0x524679 | (1 << 29), &patch_524679_1),	// sub_5245BD : cmp     ax, 208h
	tArrayItem(0x524679 | (2 << 29), &patch_524679_2),	// sub_5245BD : cmp     ax, 208h
	tArrayItem(0x52469A | (1 << 29), &patch_52469A_1),	// sub_5245BD : cmp     ax, 21Bh
	tArrayItem(0x52469A | (2 << 29), &patch_52469A_2),	// sub_5245BD : cmp     ax, 21Bh
	tArrayItem(0x525462, &patch_525462),	// sub_5245BD : mov     ax, [edi+22h]
	tArrayItem(0x525466 | (1 << 29), &patch_525466_1),	// sub_5245BD : cmp     ax, 443
	tArrayItem(0x525466 | (2 << 29), &patch_525466_2),	// sub_5245BD : cmp     ax, 443
	tArrayItem(0x5254C0 | (1 << 29), &patch_5254C0_1),	// sub_5245BD : cmp     ax, 486
	tArrayItem(0x5254C0 | (2 << 29), &patch_5254C0_2),	// sub_5245BD : cmp     ax, 486
	tArrayItem(0x5254C6 | (1 << 29), &patch_5254C6_1),	// sub_5245BD : cmp     ax, 406
	tArrayItem(0x5254C6 | (2 << 29), &patch_5254C6_2),	// sub_5245BD : cmp     ax, 406
	tArrayItem(0x5254CC | (1 << 29), &patch_5254CC_1),	// sub_5245BD : cmp     ax, 524
	tArrayItem(0x5254CC | (2 << 29), &patch_5254CC_2),	// sub_5245BD : cmp     ax, 524
	tArrayItem(0x5254D2 | (1 << 29), &patch_5254D2_1),	// sub_5245BD : cmp     ax, 592
	tArrayItem(0x5254D2 | (2 << 29), &patch_5254D2_2),	// sub_5245BD : cmp     ax, 592
	tArrayItem(0x5254D8 | (1 << 29), &patch_5254D8_1),	// sub_5245BD : cmp     ax, 520
	tArrayItem(0x5254D8 | (2 << 29), &patch_5254D8_2),	// sub_5245BD : cmp     ax, 520
	tArrayItem(0x5254DE | (1 << 29), &patch_5254DE_1),	// sub_5245BD : cmp     ax, 525
	tArrayItem(0x5254DE | (2 << 29), &patch_5254DE_2),	// sub_5245BD : cmp     ax, 525
	tArrayItem(0x5254E4 | (1 << 29), &patch_5254E4_1),	// sub_5245BD : cmp     ax, 530
	tArrayItem(0x5254E4 | (2 << 29), &patch_5254E4_2),	// sub_5245BD : cmp     ax, 530
	tArrayItem(0x5254EA | (1 << 29), &patch_5254EA_1),	// sub_5245BD : cmp     ax, 531
	tArrayItem(0x5254EA | (2 << 29), &patch_5254EA_2),	// sub_5245BD : cmp     ax, 531
	tArrayItem(0x5254F0 | (1 << 29), &patch_5254F0_1),	// sub_5245BD : cmp     ax, 564
	tArrayItem(0x5254F0 | (2 << 29), &patch_5254F0_2),	// sub_5245BD : cmp     ax, 564
	tArrayItem(0x527058 | (1 << 29), &patch_527058_1),	// sub_526FC0 : cmp     word ptr [eax+22h], 208h
	tArrayItem(0x527058 | (2 << 29), &patch_527058_2),	// sub_526FC0 : cmp     word ptr [eax+22h], 208h
	tArrayItem(0x528294 | (1 << 29), &patch_528294_1),	// sub_527FA0 : cmp     word ptr [ecx+22h], 1CCh
	tArrayItem(0x528294 | (2 << 29), &patch_528294_2),	// sub_527FA0 : cmp     word ptr [ecx+22h], 1CCh
	tArrayItem(0x52852B, &patch_52852B),	// sub_527FA0 : mov     bp, [eax+0Ah]
	tArrayItem(0x52939C, &patch_52939C),	// sub_527FA0 : mov     bp, [ebp+0Ah]
	tArrayItem(0x529705, &patch_529705),	// sub_527FA0 : mov     bp, [ecx+0Ah]
	tArrayItem(0x52AE34 | (1 << 29), &patch_52AE34_1),	// sub_527FA0 : cmp     word ptr [eax+22h], 1A7h
	tArrayItem(0x52AE34 | (2 << 29), &patch_52AE34_2),	// sub_527FA0 : cmp     word ptr [eax+22h], 1A7h
	tArrayItem(0x532A54, &patch_532A54),	// sub_532A50 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x532AB0, &patch_532AB0),	// sub_532A90 : mov     word ptr [esi+22h], 0FFFFh
	tArrayItem(0x532B74, &patch_532B74),	// sub_532B70 : mov     si, [edi+22h]
	tArrayItem(0x532B78, &patch_532B78),	// sub_532B70 : movsx   eax, si
	tArrayItem(0x532BB9, &patch_532BB9),	// sub_532B70 : movzx   edx, ds:MI_COLLECTABLE1
	tArrayItem(0x532BC8, &patch_532BC8),	// sub_532B70 : movzx   ecx, ds:MI_MONEY
	tArrayItem(0x532BD7, &patch_532BD7),	// sub_532B70 : movzx   edx, ds:MI_CARMINE
	tArrayItem(0x532BE6, &patch_532BE6),	// sub_532B70 : movzx   ecx, ds:MI_NAUTICALMINE
	tArrayItem(0x532BF5, &patch_532BF5),	// sub_532B70 : movzx   edx, ds:MI_BRIEFCASE
	tArrayItem(0x532C04 | (1 << 29), &patch_532C04_1),	// sub_532B70 : cmp     si, 345
	tArrayItem(0x532C04 | (2 << 29), &patch_532C04_2),	// sub_532B70 : cmp     si, 345
	tArrayItem(0x532C0F | (1 << 29), &patch_532C0F_1),	// sub_532B70 : cmp     si, 342
	tArrayItem(0x532C0F | (2 << 29), &patch_532C0F_2),	// sub_532B70 : cmp     si, 342
	tArrayItem(0x532C1A | (1 << 29), &patch_532C1A_1),	// sub_532B70 : cmp     si, 344
	tArrayItem(0x532C1A | (2 << 29), &patch_532C1A_2),	// sub_532B70 : cmp     si, 344
	tArrayItem(0x532C25, &patch_532C25),	// sub_532B70 : movzx   ecx, ds:MI_BEACHBALL
	tArrayItem(0x532C34, &patch_532C34),	// sub_532B70 : movzx   edx, ds:MI_MAGNOCRANE_HOOK
	tArrayItem(0x532C43, &patch_532C43),	// sub_532B70 : movzx   ecx, ds:MI_WRECKING_BALL
	tArrayItem(0x532C52, &patch_532C52),	// sub_532B70 : movzx   edx, ds:MI_CRANE_MAGNET
	tArrayItem(0x532C61, &patch_532C61),	// sub_532B70 : movzx   ecx, ds:MI_MINI_MAGNET
	tArrayItem(0x532C70, &patch_532C70),	// sub_532B70 : movzx   edx, ds:MI_CRANE_HARNESS
	tArrayItem(0x532C7F, &patch_532C7F),	// sub_532B70 : movzx   ecx, ds:MI_WINDSOCK
	tArrayItem(0x532C8E, &patch_532C8E),	// sub_532B70 : movzx   edx, ds:MI_FLARE
	tArrayItem(0x532CC0, &patch_532CC0),	// sub_532B70 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x532CD1, &patch_532CD1),	// sub_532B70 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x532CD5, &patch_532CD5),	// sub_532B70 : movzx   edx, ds:MI_SINGLESTREETLIGHTS1
	tArrayItem(0x532CE0, &patch_532CE0),	// sub_532B70 : movzx   ecx, ds:MI_SINGLESTREETLIGHTS2
	tArrayItem(0x532CEB, &patch_532CEB),	// sub_532B70 : movzx   edx, ds:MI_SINGLESTREETLIGHTS3
	tArrayItem(0x532CF6, &patch_532CF6),	// sub_532B70 : movzx   ecx, ds:MI_DOUBLESTREETLIGHTS
	tArrayItem(0x532D40, &patch_532D40),	// sub_532D40 : movsx   eax, word ptr [ecx+22h]
	tArrayItem(0x53315E, &patch_53315E),	// sub_533150 : movsx   ecx, word ptr [ecx+22h]
	tArrayItem(0x533243, &patch_533243),	// sub_533240 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x533384, &patch_533384),	// sub_533380 : movsx   eax, word ptr [ebx+22h]
	tArrayItem(0x533416, &patch_533416),	// sub_533410 : movsx   eax, word ptr [ecx+22h]
	tArrayItem(0x53370F, &patch_53370F),	// sub_533700 : mov     [esi+22h], ax
	tArrayItem(0x53379D, &patch_53379D),	// sub_533790 : movsx   eax, word ptr [ebp+22h]
	tArrayItem(0x53383E, &patch_53383E),	// sub_533790 : mov     cx, [esi+24h]
	tArrayItem(0x53384A, &patch_53384A),	// sub_533790 : mov     dx, [esi+24h]
	tArrayItem(0x533865, &patch_533865),	// sub_533790 : mov     cx, [esi+24h]
	tArrayItem(0x533A46, &patch_533A46),	// sub_533790 : movsx   ecx, word ptr [esi+2Ch]
	tArrayItem(0x533BF6, &patch_533BF6),	// _ZN7CEntity14DestroyEffectsEv : movsx   eax, word ptr [ebx+22h]
	tArrayItem(0x533D41, &patch_533D41),	// sub_533D30 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x533F2C, &patch_533F2C),	// sub_533ED0 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x533F82, &patch_533F82),	// sub_533ED0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x533FBA, &patch_533FBA),	// sub_533FB0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x533FD4, &patch_533FD4),	// sub_533FB0 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x53409A, &patch_53409A),	// sub_534030 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x5340D3, &patch_5340D3),	// sub_534030 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x534126, &patch_534126),	// CEntity__GetBoundRect : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x534250, &patch_534250),	// sub_534250 : movsx   eax, word ptr [ecx+22h]
	tArrayItem(0x534290, &patch_534290),	// sub_534290 : movsx   eax, word ptr [ecx+22h]
	tArrayItem(0x5342B6, &patch_5342B6),	// sub_5342B0 : movsx   eax, word ptr [ecx+22h]
	tArrayItem(0x534340, &patch_534340),	// _ZN7CEntity6RenderEv : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x534344, &patch_534344),	// _ZN7CEntity6RenderEv : movzx   ecx, ds:MI_JELLYFISH
	tArrayItem(0x534357, &patch_534357),	// _ZN7CEntity6RenderEv : movzx   edx, ds:MI_JELLYFISH01
	tArrayItem(0x5343B7, &patch_5343B7),	// _ZN7CEntity6RenderEv : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x5343BB, &patch_5343BB),	// _ZN7CEntity6RenderEv : movzx   ecx, ds:MI_JELLYFISH
	tArrayItem(0x5343C6, &patch_5343C6),	// _ZN7CEntity6RenderEv : movzx   edx, ds:MI_JELLYFISH01
	tArrayItem(0x5343F6, &patch_5343F6),	// sub_5343F0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x534419, &patch_534419),	// sub_5343F0 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x534437, &patch_534437),	// sub_5343F0 : movsx   edx, word ptr [edi+22h]
	tArrayItem(0x534442, &patch_534442),	// sub_5343F0 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x5344B6, &patch_5344B6),	// _ZNK7CEntity13GetIsTouchingERK7CVectorf : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x5344D4, &patch_5344D4),	// _ZNK7CEntity13GetIsTouchingERK7CVectorf : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x534546, &patch_534546),	// sub_534540 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x534564, &patch_534564),	// sub_534540 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x5345EE, &patch_5345EE),	// sub_5345D0 : movsx   eax, word ptr [ebp+22h]
	tArrayItem(0x534FAF, &patch_534FAF),	// sub_534E90 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x535322, &patch_535322),	// sub_535300 : movsx   ecx, word ptr [ecx+22h]
	tArrayItem(0x5354C1, &patch_5354C1),	// sub_535450 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x535FAB, &patch_535FAB),	// sub_535FA0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x536174, &patch_536174),	// sub_535FA0 : mov     cx, [esi+22h]
	tArrayItem(0x536178, &patch_536178),	// sub_535FA0 : movzx   edx, ds:MI_COLLECTABLE1
	tArrayItem(0x53617F, &patch_53617F),	// sub_535FA0 : movsx   eax, cx
	tArrayItem(0x5361B2, &patch_5361B2),	// sub_535FA0 : movzx   edx, ds:MI_MONEY
	tArrayItem(0x5361C8, &patch_5361C8),	// sub_535FA0 : movzx   edx, ds:MI_CARMINE
	tArrayItem(0x5361D7, &patch_5361D7),	// sub_535FA0 : movzx   edx, ds:MI_NAUTICALMINE
	tArrayItem(0x5361E6, &patch_5361E6),	// sub_535FA0 : movzx   edx, ds:MI_BRIEFCASE
	tArrayItem(0x5361F5 | (1 << 29), &patch_5361F5_1),	// sub_535FA0 : cmp     cx, 345
	tArrayItem(0x5361F5 | (2 << 29), &patch_5361F5_2),	// sub_535FA0 : cmp     cx, 345
	tArrayItem(0x5363B5, &patch_5363B5),	// sub_535FA0 : movzx   ecx, ds:MI_FLARE
	tArrayItem(0x53654B, &patch_53654B),	// sub_535FA0 : mov     ax, [esi+22h]
	tArrayItem(0x53654F | (1 << 29), &patch_53654F_1),	// sub_535FA0 : cmp     ax, 342
	tArrayItem(0x53654F | (2 << 29), &patch_53654F_2),	// sub_535FA0 : cmp     ax, 342
	tArrayItem(0x53662F | (1 << 29), &patch_53662F_1),	// sub_535FA0 : cmp     ax, 344
	tArrayItem(0x53662F | (2 << 29), &patch_53662F_2),	// sub_535FA0 : cmp     ax, 344
	tArrayItem(0x53678B, &patch_53678B),	// sub_535FA0 : movzx   edx, ds:MI_BEACHBALL
	tArrayItem(0x536853, &patch_536853),	// sub_535FA0 : movzx   ecx, ds:MI_MAGNOCRANE_HOOK
	tArrayItem(0x53685E, &patch_53685E),	// sub_535FA0 : movzx   edx, ds:MI_WRECKING_BALL
	tArrayItem(0x536869, &patch_536869),	// sub_535FA0 : movzx   ecx, ds:MI_CRANE_MAGNET
	tArrayItem(0x536874, &patch_536874),	// sub_535FA0 : movzx   edx, ds:MI_MINI_MAGNET
	tArrayItem(0x53687F, &patch_53687F),	// sub_535FA0 : movzx   ecx, ds:MI_CRANE_HARNESS
	tArrayItem(0x53688A, &patch_53688A),	// sub_535FA0 : movzx   edx, ds:MI_WINDSOCK
	tArrayItem(0x536977, &patch_536977),	// sub_535FA0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x5369B8, &patch_5369B8),	// sub_535FA0 : movzx   edx, ds:MI_TRAFFICLIGHTS_VERTICAL
	tArrayItem(0x5369C7, &patch_5369C7),	// sub_535FA0 : movzx   ecx, ds:MI_TRAFFICLIGHTS_MIAMI
	tArrayItem(0x536A01, &patch_536A01),	// sub_535FA0 : movzx   edx, ds:MI_TRAFFICLIGHTS_TWOVERTICAL
	tArrayItem(0x536A3B, &patch_536A3B),	// sub_535FA0 : movzx   ecx, ds:MI_TRAFFICLIGHTS_3
	tArrayItem(0x536A46, &patch_536A46),	// sub_535FA0 : movzx   edx, ds:MI_TRAFFICLIGHTS_4
	tArrayItem(0x536A51, &patch_536A51),	// sub_535FA0 : movzx   ecx, ds:MI_TRAFFICLIGHTS_GAY
	tArrayItem(0x536A5C, &patch_536A5C),	// sub_535FA0 : movzx   edx, ds:MI_TRAFFICLIGHTS_5
	tArrayItem(0x536A7B, &patch_536A7B),	// sub_535FA0 : movzx   ecx, ds:MI_SINGLESTREETLIGHTS1
	tArrayItem(0x536AAF, &patch_536AAF),	// sub_535FA0 : movzx   edx, ds:MI_SINGLESTREETLIGHTS2
	tArrayItem(0x536AE3, &patch_536AE3),	// sub_535FA0 : movzx   ecx, ds:MI_SINGLESTREETLIGHTS3
	tArrayItem(0x536B1A, &patch_536B1A),	// sub_535FA0 : movzx   edx, ds:MI_DOUBLESTREETLIGHTS
	tArrayItem(0x536B4E, &patch_536B4E),	// sub_535FA0 : movzx   ecx, ds:MI_TRAFFICLIGHTS_VEGAS
	tArrayItem(0x536C07, &patch_536C07),	// sub_536BE0 : movsx   ecx, word ptr [ecx+22h]
	tArrayItem(0x5373CF | (1 << 29), &patch_5373CF_1),	// sub_5372D0 : cmp     ebp, 1FCh
	tArrayItem(0x5373CF | (2 << 29), &patch_5373CF_2),	// sub_5372D0 : cmp     ebp, 1FCh
	tArrayItem(0x537A95, &patch_537A95),	// sub_537A80 : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x537AA1, &patch_537AA1),	// sub_537A9A : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x537AC5, &patch_537AC5),	// sub_537AB0 : movsx   eax, word ptr [eax+24h]
	tArrayItem(0x537AD1, &patch_537AD1),	// sub_537AB0 : movsx   eax, word ptr [eax+24h]
	tArrayItem(0x538120, &patch_538120),	// sub_538090 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x53835F, &patch_53835F),	// sub_538090 : movzx   ecx, ds:MI_TRAINCROSSING
	tArrayItem(0x5383B7, &patch_5383B7),	// sub_538090 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x538550, &patch_538550),	// sub_538440 : movsx   ecx, word ptr [ecx+24h]
	tArrayItem(0x538554, &patch_538554),	// sub_538440 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x53A637 | (1 << 29), &patch_53A637_1),	// sub_53A570 : cmp     word ptr [eax+22h], 197h
	tArrayItem(0x53A637 | (2 << 29), &patch_53A637_2),	// sub_53A570 : cmp     word ptr [eax+22h], 197h
	tArrayItem(0x53A709, &patch_53A709),	// sub_53A570 : movsx   edx, word ptr [ecx+22h]
	tArrayItem(0x53A926 | (1 << 29), &patch_53A926_1),	// sub_53A570 : cmp     word ptr [edi+22h], 197h
	tArrayItem(0x53A926 | (2 << 29), &patch_53A926_2),	// sub_53A570 : cmp     word ptr [edi+22h], 197h
	tArrayItem(0x53C445, &patch_53C445),	// sub_53C440 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x5429AB, &patch_5429AB),	// _ZN9CPhysical21SetDamagedPieceRecordEfP7CEntityR9CColPointf : movsx   eax, word ptr [ebp+22h]
	tArrayItem(0x5429AF, &patch_5429AF),	// _ZN9CPhysical21SetDamagedPieceRecordEfP7CEntityR9CColPointf : movzx   ecx, ds:MI_POOL_CUE_BALL
	tArrayItem(0x5449C0, &patch_5449C0),	// sub_5449B0 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x54667C, &patch_54667C),	// sub_546670 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x546D24, &patch_546D24),	// sub_546D00 : movsx   ecx, word ptr [edi+22h]
	tArrayItem(0x5470BF | (1 << 29), &patch_5470BF_1),	// sub_4067D8 : cmp     word ptr [ecx+22h], 212h
	tArrayItem(0x5470BF | (2 << 29), &patch_5470BF_2),	// sub_4067D8 : cmp     word ptr [ecx+22h], 212h
	tArrayItem(0x54742F, &patch_54742F),	// sub_4067D8 : mov     cx, [edi+22h]
	tArrayItem(0x547433 | (1 << 29), &patch_547433_1),	// sub_4067D8 : cmp     cx, 406
	tArrayItem(0x547433 | (2 << 29), &patch_547433_2),	// sub_4067D8 : cmp     cx, 406
	tArrayItem(0x54743A | (1 << 29), &patch_54743A_1),	// sub_4067D8 : cmp     cx, 530
	tArrayItem(0x54743A | (2 << 29), &patch_54743A_2),	// sub_4067D8 : cmp     cx, 530
	tArrayItem(0x547497 | (1 << 29), &patch_547497_1),	// sub_4067D8 : cmp     cx, 406
	tArrayItem(0x547497 | (2 << 29), &patch_547497_2),	// sub_4067D8 : cmp     cx, 406
	tArrayItem(0x5474E4 | (1 << 29), &patch_5474E4_1),	// sub_4067D8 : cmp     cx, 530
	tArrayItem(0x5474E4 | (2 << 29), &patch_5474E4_2),	// sub_4067D8 : cmp     cx, 530
	tArrayItem(0x54771D | (1 << 29), &patch_54771D_1),	// sub_4067D8 : cmp     word ptr [esi+22h], 16Bh
	tArrayItem(0x54771D | (2 << 29), &patch_54771D_2),	// sub_4067D8 : cmp     word ptr [esi+22h], 16Bh
	tArrayItem(0x547FD7, &patch_547FD7),	// sub_547B80 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x5483E3, &patch_5483E3),	// sub_5483D0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x548F45, &patch_548F45),	// sub_548680 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x548F49, &patch_548F49),	// sub_548680 : movzx   ecx, ds:MI_FIRE_HYDRANT
	tArrayItem(0x548F87, &patch_548F87),	// sub_548680 : movzx   edx, ds:MI_PARKINGMETER
	tArrayItem(0x548F92, &patch_548F92),	// sub_548680 : movzx   ecx, ds:MI_PARKINGMETER2
	tArrayItem(0x54A82B, &patch_54A82B),	// sub_54A2C6 : movsx   eax, word ptr [ebp+22h]
	tArrayItem(0x54A82F, &patch_54A82F),	// sub_54A2C6 : movzx   ecx, ds:MI_FIRE_HYDRANT
	tArrayItem(0x54A92D, &patch_54A92D),	// sub_54A2C6 : movzx   edx, ds:MI_PARKINGMETER
	tArrayItem(0x54A938, &patch_54A938),	// sub_54A2C6 : movzx   ecx, ds:MI_PARKINGMETER2
	tArrayItem(0x54BA91, &patch_54BA91),	// sub_54BA60 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x54C6BE, &patch_54C6BE),	// sub_54BA60 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x54C813, &patch_54C813),	// sub_54BA60 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x54CB44 | (1 << 29), &patch_54CB44_1),	// sub_54BA60 : cmp     word ptr [esi+22h], 1B9h
	tArrayItem(0x54CB44 | (2 << 29), &patch_54CB44_2),	// sub_54BA60 : cmp     word ptr [esi+22h], 1B9h
	tArrayItem(0x54D02C, &patch_54D02C),	// sub_54CFF0 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x54D70D | (1 << 29), &patch_54D70D_1),	// sub_4022FC : cmp     word ptr [edi+22h], 212h
	tArrayItem(0x54D70D | (2 << 29), &patch_54D70D_2),	// sub_4022FC : cmp     word ptr [edi+22h], 212h
	tArrayItem(0x55010F, &patch_55010F),	// sub_550080 : movsx   ecx, word ptr [ebx+22h]
	tArrayItem(0x5519C5, &patch_5519C5),	// sub_564360 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x5534B5, &patch_5534B5),	// sub_5534B0 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x5537EC, &patch_5537EC),	// sub_553770 : movsx   edx, word ptr [eax+22h]
	tArrayItem(0x55381E, &patch_55381E),	// sub_553770 : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x553891, &patch_553891),	// sub_553770 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x553A60, &patch_553A60),	// sub_553A10 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x553B10, &patch_553B10),	// sub_553AA0 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x554238, &patch_554238),	// sub_554230 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x55432A, &patch_55432A),	// sub_554230 : mov     ax, [esi+22h]
	tArrayItem(0x55432E | (1 << 29), &patch_55432E_1),	// sub_554230 : cmp     ax, 432
	tArrayItem(0x55432E | (2 << 29), &patch_55432E_2),	// sub_554230 : cmp     ax, 432
	tArrayItem(0x554334 | (1 << 29), &patch_554334_1),	// sub_554230 : cmp     ax, 437
	tArrayItem(0x554334 | (2 << 29), &patch_554334_2),	// sub_554230 : cmp     ax, 437
	tArrayItem(0x554362 | (1 << 29), &patch_554362_1),	// sub_554230 : cmp     ax, 453
	tArrayItem(0x554362 | (2 << 29), &patch_554362_2),	// sub_554230 : cmp     ax, 453
	tArrayItem(0x554368 | (1 << 29), &patch_554368_1),	// sub_554230 : cmp     ax, 454
	tArrayItem(0x554368 | (2 << 29), &patch_554368_2),	// sub_554230 : cmp     ax, 454
	tArrayItem(0x55436E | (1 << 29), &patch_55436E_1),	// sub_554230 : cmp     ax, 430
	tArrayItem(0x55436E | (2 << 29), &patch_55436E_2),	// sub_554230 : cmp     ax, 430
	tArrayItem(0x554374 | (1 << 29), &patch_554374_1),	// sub_554230 : cmp     ax, 460
	tArrayItem(0x554374 | (2 << 29), &patch_554374_2),	// sub_554230 : cmp     ax, 460
	tArrayItem(0x5543A5 | (1 << 29), &patch_5543A5_1),	// sub_554230 : cmp     word ptr [esi+22h], 0
	tArrayItem(0x5543A5 | (2 << 29), &patch_5543A5_2),	// sub_554230 : cmp     word ptr [esi+22h], 0
	tArrayItem(0x554443, &patch_554443),	// sub_554230 : movsx   ebx, word ptr [eax+2]
	tArrayItem(0x5544F7 | (1 << 29), &patch_5544F7_1),	// sub_554230 : cmp     word ptr [esi+22h], 0
	tArrayItem(0x5544F7 | (2 << 29), &patch_5544F7_2),	// sub_554230 : cmp     word ptr [esi+22h], 0
	tArrayItem(0x55465E, &patch_55465E),	// sub_554650 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x554699, &patch_554699),	// sub_554650 : movsx   ebp, word ptr [eax+2]
	tArrayItem(0x554978, &patch_554978),	// sub_554840 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x5549B9, &patch_5549B9),	// sub_554840 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x5549EF, &patch_5549EF),	// sub_554840 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x554C15, &patch_554C15),	// sub_554B10 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x554ED3, &patch_554ED3),	// sub_554EB0 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x554F32, &patch_554F32),	// sub_554EB0 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x5556C4, &patch_5556C4),	// sub_555680 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x5560B7, &patch_5560B7),	// sub_556070 : movzx   ebp, ds:MI_CRANE_MAGNET; jumptable 005560B0 cases 0,3,5,6
	tArrayItem(0x5560C0, &patch_5560C0),	// sub_556070 : movzx   ebp, ds:MI_CRANE_HARNESS; jumptable 005560B0 case 1
	tArrayItem(0x5560C9, &patch_5560C9),	// sub_556070 : movzx   ebp, ds:MI_WRECKING_BALL; jumptable 005560B0 case 4
	tArrayItem(0x5560D2, &patch_5560D2),	// sub_556070 : movzx   ebp, ds:MI_MINI_MAGNET; jumptable 005560B0 case 2
	tArrayItem(0x556764, &patch_556764),	// sub_556760 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x5569F3, &patch_5569F3),	// sub_5569C0 : movsx   eax, word ptr [edi+22h]
	tArrayItem(0x557659, &patch_557659),	// sub_557530 : movsx   eax, word ptr [eax+22h]
	tArrayItem(0x55765D, &patch_55765D),	// sub_557530 : movzx   edx, ds:MI_OBJECTFORMAGNOCRANE1
	tArrayItem(0x557668, &patch_557668),	// sub_557530 : movzx   ecx, ds:MI_OBJECTFORMAGNOCRANE2
	tArrayItem(0x557673, &patch_557673),	// sub_557530 : movzx   edx, ds:MI_OBJECTFORMAGNOCRANE3
	tArrayItem(0x55767E, &patch_55767E),	// sub_557530 : movzx   ecx, ds:MI_OBJECTFORMAGNOCRANE5
	tArrayItem(0x557BDB | (1 << 29), &patch_557BDB_1),	// sub_557530 : cmp     word ptr [esi+22h], 1ACh
	tArrayItem(0x557BDB | (2 << 29), &patch_557BDB_2),	// sub_557530 : cmp     word ptr [esi+22h], 1ACh
	tArrayItem(0x558160, &patch_558160),	// sub_557530 : movsx   ecx, word ptr [eax+22h]
	tArrayItem(0x5583B3, &patch_5583B3),	// sub_557530 : mov     ax, [esi+22h]
	tArrayItem(0x5583B7 | (1 << 29), &patch_5583B7_1),	// sub_557530 : cmp     ax, 473
	tArrayItem(0x5583B7 | (2 << 29), &patch_5583B7_2),	// sub_557530 : cmp     ax, 473
	tArrayItem(0x5583BD | (1 << 29), &patch_5583BD_1),	// sub_557530 : cmp     ax, 539
	tArrayItem(0x5583BD | (2 << 29), &patch_5583BD_2),	// sub_557530 : cmp     ax, 539
	tArrayItem(0x5583E9 | (1 << 29), &patch_5583E9_1),	// sub_557530 : cmp     word ptr [esi+22h], 234h
	tArrayItem(0x5583E9 | (2 << 29), &patch_5583E9_2),	// sub_557530 : cmp     word ptr [esi+22h], 234h
	tArrayItem(0x558402, &patch_558402),	// sub_557530 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x5584C6, &patch_5584C6),	// sub_557530 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x558684, &patch_558684),	// sub_557530 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x5587D0, &patch_5587D0),	// sub_557530 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x5587D4, &patch_5587D4),	// sub_557530 : movzx   edi, ds:MI_OBJECTFORMAGNOCRANE1
	tArrayItem(0x5587E3, &patch_5587E3),	// sub_557530 : movzx   edi, ds:MI_OBJECTFORMAGNOCRANE2
	tArrayItem(0x5587F2, &patch_5587F2),	// sub_557530 : movzx   edi, ds:MI_OBJECTFORMAGNOCRANE3
	tArrayItem(0x558801, &patch_558801),	// sub_557530 : movzx   edi, ds:MI_OBJECTFORMAGNOCRANE4
	tArrayItem(0x558810, &patch_558810),	// sub_557530 : movzx   edi, ds:MI_OBJECTFORMAGNOCRANE5
	tArrayItem(0x558827, &patch_558827),	// sub_557530 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x55882B, &patch_55882B),	// sub_557530 : movzx   edi, ds:MI_OBJECTFORBUILDINGSITECRANE1
	tArrayItem(0x558842, &patch_558842),	// sub_557530 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x558846, &patch_558846),	// sub_557530 : movzx   edi, ds:MI_QUARY_ROCK1
	tArrayItem(0x558851, &patch_558851),	// sub_557530 : movzx   edi, ds:MI_QUARY_ROCK2
	tArrayItem(0x55885C, &patch_55885C),	// sub_557530 : movzx   edi, ds:MI_QUARY_ROCK3
	tArrayItem(0x558867, &patch_558867),	// sub_557530 : movzx   edi, ds:MI_DEAD_TIED_COP
	tArrayItem(0x558884, &patch_558884),	// sub_557530 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x558888, &patch_558888),	// sub_557530 : movzx   edi, ds:MI_WONG_DISH
	tArrayItem(0x55889B, &patch_55889B),	// sub_557530 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x55889F, &patch_55889F),	// sub_557530 : movzx   edi, ds:MI_KMB_ROCK
	tArrayItem(0x5588B2, &patch_5588B2),	// sub_557530 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x5588B6, &patch_5588B6),	// sub_557530 : movzx   edi, ds:MI_KMB_PLANK
	tArrayItem(0x5588CD, &patch_5588CD),	// sub_557530 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x5588D1, &patch_5588D1),	// sub_557530 : movzx   edi, ds:MI_KMB_BOMB
	tArrayItem(0x558920, &patch_558920),	// sub_557530 : movzx   ecx, ds:MI_OBJECTFORMAGNOCRANE1
	tArrayItem(0x55892B, &patch_55892B),	// sub_557530 : movsx   eax, word ptr [esi+22h]
	tArrayItem(0x55893C, &patch_55893C),	// sub_557530 : movzx   edx, ds:MI_OBJECTFORMAGNOCRANE2
	tArrayItem(0x558947, &patch_558947),	// sub_557530 : movzx   ecx, ds:MI_OBJECTFORMAGNOCRANE3
	tArrayItem(0x558952, &patch_558952),	// sub_557530 : movzx   edx, ds:MI_OBJECTFORMAGNOCRANE5
	tArrayItem(0x5589D2, &patch_5589D2),	// sub_557530 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x558A5C, &patch_558A5C),	// sub_557530 : movsx   ecx, word ptr [esi+22h]
	tArrayItem(0x558B4A, &patch_558B4A),	// sub_557530 : movsx   edx, word ptr [esi+22h]
	tArrayItem(0x55A81D, &patch_55A81D),	// sub_55A785 : movsx   edi, word ptr [ebx]
	tArrayItem(0x55C00D, &patch_55C00D),	// sub_55BF20 : movsx   ecx, word ptr [ecx+22h]
	tArrayItem(0x5626D1 | (1 << 29), &patch_5626D1_1),	// sub_5625F0 : cmp     word ptr [esi+22h], 1F1h
	tArrayItem(0x5626D1 | (2 << 29), &patch_5626D1_2),	// sub_5625F0 : cmp     word ptr [esi+22h], 1F1h
	tArrayItem(0x56360D, &patch_56360D),	// sub_5635C0 : movsx   eax, word ptr [ecx+22h]
	tArrayItem(0x563990, &patch_563990),	// sub_563950 : mov     cx, [edx+22h]

	};
}
#endif
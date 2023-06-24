/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "OtherLimits.h"

#include "FileIDlimit.h"
#include "IPLsectionLimits.h"
#include "SaveOfVariableLength.h"
#include "StructureExtension.h"

#include "../Core/CPatch.h"
#include "../Core/CCodeMover.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/GetObjectMadeOfString.h"
#include "../Core/LimitAdjuster.h"

#include "../GameStructures/Rockstar Games/CGenericGameStorage.h"
#include "../GameStructures/Rockstar Games/CEntity.h"
#include "../GameStructures/Rockstar Games/IDstructures.h"

using namespace Game;

OtherLimits g_otherLimits;

namespace Game_GTASA
{
	class CVehicleModelInfoDkluin
	{
		// Chooses vehicle colour, using direct references to int values
		void ChooseVehicleColour(
			int& PrimaryColor,
			int& SecondaryColor,
			int& TertiaryColor,
			int& QuaternaryColor,
			int32_t a5
		)
		{
			((void(__thiscall*)
				(CVehicleModelInfoDkluin*, int&, int&, int&, int&, int)
				)0x4C8500)(
					this,
					PrimaryColor,
					SecondaryColor,
					TertiaryColor,
					QuaternaryColor,
					a5
					);

			if (!g_otherLimits.bIsVehicleColorIDextended)
			{
				if (PrimaryColor == 0xFF)
					PrimaryColor = -1;

				if (SecondaryColor == 0xFF)
					SecondaryColor = -1;

				if (TertiaryColor == 0xFF)
					TertiaryColor = -1;

				if (QuaternaryColor == 0xFF)
					QuaternaryColor = -1;
			}
		}

		// Chooses vehicle colour, using uint8_replacement
		void ChooseVehicleColour(
			uint8_replacement& PrimaryColor,
			uint8_replacement& SecondaryColor,
			uint8_replacement& TertiaryColor,
			uint8_replacement& QuaternaryColor,
			int32_t a5)
		{
			int32_t xPrimaryColor;
			int32_t xSecondaryColor;
			int32_t xTertiaryColor;
			int32_t xQuaternaryColor;
				
			this->ChooseVehicleColour(
				xPrimaryColor,
				xSecondaryColor,
				xTertiaryColor,
				xQuaternaryColor,
				a5
			);

			PrimaryColor = xPrimaryColor;
			SecondaryColor = xSecondaryColor;
			TertiaryColor = xQuaternaryColor;
			QuaternaryColor = xQuaternaryColor;
		}
	};

	#ifdef IS_PLATFORM_WIN_X86
	class CVehicleModelInfo_x36324
	{
	public:		
		void CVehicleModelInfo__SetVehicleColour(int32_t PrimaryColor, int32_t SecondaryColor, int32_t TertiaryColor, int32_t QuaternaryColor)
		{
			*(uint8_replacement*)0xB4E3F0 = PrimaryColor;
			*(uint8_replacement*)0xB4E3F1 = SecondaryColor;
			*(uint8_replacement*)0xB4E3F2 = TertiaryColor;
			*(uint8_replacement*)0xB4E3F3 = QuaternaryColor;
		}

		void ChooseVehicleColourFindReplacementPtrs(
			uint8_t& PrimaryColor,
			uint8_t& SecondaryColor,
			uint8_t& TertiaryColor,
			uint8_t& QuaternaryColor,
			int)
		{
			CStructureExtensionContainer<void, int32_t>* pContainer
				= &g_structureExtension.m_ID_extensionFrom8bit;

			// CVehicleModelInfo::ChooseVehicleColour
			((void(__thiscall*)
				(CVehicleModelInfo_x36324*, int&, int&, int&, int&, int)
				)0x4C8500)(
					this,
					*(int*)pContainer->GetPointerToExtendedData(&PrimaryColor),
					*(int*)pContainer->GetPointerToExtendedData(&SecondaryColor),
					*(int*)pContainer->GetPointerToExtendedData(&TertiaryColor),
					*(int*)pContainer->GetPointerToExtendedData(&QuaternaryColor),
					1
					);
		}
	};

	bool ChangeVehicleColourIfNeccessary(CVehicle_generic* pVehicle) // (class CVehicleModelInfo* pModelInfo)
	{
		class CVehicleModelInfo* pModelInfo = (class CVehicleModelInfo*)
			g_fileIDlimits.CModelInfo__ms_modelInfoPtrs.generic[pVehicle->GetModelID()];
		//////

		int32_t PrimaryColor;
		int32_t SecondaryColor;
		int32_t TertiaryColor;
		int32_t QuaternaryColor;

		// CVehicleModelInfo::ChooseVehicleColour
		((void(__thiscall*)
				(CVehicleModelInfo*, int&, int&, int&, int&, int)
			)0x4C8500)(
				pModelInfo,
				PrimaryColor,
				SecondaryColor,
				TertiaryColor,
				QuaternaryColor,
				1
			);

		if (
			*(uint8_replacement*)((char*)pVehicle + 0x434) != PrimaryColor
			|| *(uint8_replacement*)((char*)pVehicle + 0x435) != SecondaryColor
			|| *(uint8_replacement*)((char*)pVehicle + 0x436) != TertiaryColor
			|| *(uint8_replacement*)((char*)pVehicle + 0x437) != QuaternaryColor
			)
		{
			*(uint8_replacement*)((char*)pVehicle + 0x434) = PrimaryColor;
			*(uint8_replacement*)((char*)pVehicle + 0x435) = SecondaryColor;
			*(uint8_replacement*)((char*)pVehicle + 0x436) = TertiaryColor;
			*(uint8_replacement*)((char*)pVehicle + 0x437) = QuaternaryColor;
			
			return true;
		}
		else
			return false;
	}

	NAKED void patch_CGarage__Update_44B104()
	{
		__asm
		{
			push edi;
			call ChangeVehicleColourIfNeccessary;
			add esp, 4;

			mov bl, al;
			
			push 0x44B180;
			retn;
		}
	}

	NAKED void patch_CMenuSystem__GetCarColourFromGrid_5822C1()
	{
		__asm
		{
			movzx     eax, byte ptr[ecx + edx];
			cmp al, -1;
			jne doReturn;
			mov eax, -1;

		doReturn:
			retn;
		}
	}

	namespace VehicleColorIDpatches
	{
		// Function: sub_4C84B0
		// Original code:	mov     ds:TertiaryColor, bl
		static NAKED void patch_406000()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ebx;
				push 0xB4E3F2;	// TertiaryColor
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_403AEE
		// Original code:	mov     byte ptr [esi+434h], 0
		static NAKED void patch_43088C()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push 0;
				lea eax, [esi + 434h];
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

		// Function: sub_403AEE
		// Original code:	mov     byte ptr [esi+435h], 0
		static NAKED void patch_430893()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push 0;
				lea eax, [esi + 435h];
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

		// Function: sub_447E40
		// Original code:	mov     cl, [edi+32h]
		static NAKED void patch_4482A2()
		{
			__asm
			{
				movzx ecx, byte ptr[edi + 32h];
				cmp cl, -1;
				jne doReturn;
				mov ecx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_447E40
		// Original code:	mov     [esi+434h], cl
		static NAKED void patch_4482A5()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ecx;
				lea eax, [esi + 434h];
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

		// Function: sub_447E40
		// Original code:	mov     dl, [edi+33h]
		static NAKED void patch_4482AB()
		{
			__asm
			{
				movzx edx, byte ptr[edi + 33h];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_447E40
		// Original code:	mov     [esi+435h], dl
		static NAKED void patch_4482AE()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [esi + 435h];
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

		// Function: sub_447E40
		// Original code:	mov     al, [edi+34h]
		static NAKED void patch_4482B4()
		{
			__asm
			{
				movzx eax, byte ptr[edi + 34h];
				cmp al, -1;
				jne doReturn;
				mov eax, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_447E40
		// Original code:	mov     [esi+436h], al
		static NAKED void patch_4482B7()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [esi + 436h];
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

		// Function: sub_447E40
		// Original code:	mov     cl, [edi+35h]
		static NAKED void patch_4482C3()
		{
			__asm
			{
				movzx ecx, byte ptr[edi + 35h];
				cmp cl, -1;
				jne doReturn;
				mov ecx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_447E40
		// Original code:	mov     [esi+437h], cl
		static NAKED void patch_4482CF()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ecx;
				lea eax, [esi + 437h];
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

		// Function: sub_449760
		// Original code:	mov     cl, [esi+434h]
		static NAKED void patch_4497EA()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [esi + 434h];
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

		// Function: sub_449760
		// Original code:	mov     dl, [esi+435h]
		static NAKED void patch_4497F3()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [esi + 435h];
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

		// Function: sub_449760
		// Original code:	mov     al, [esi+436h]
		static NAKED void patch_4497FC()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [esi + 436h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_449760
		// Original code:	mov     cl, [esi+437h]
		static NAKED void patch_449805()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [esi + 437h];
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

		// Function: sub_44AA50
		// Original code:	movzx   edx, byte ptr [edi+434h]
		static NAKED void patch_44B1B7()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [edi + 434h];
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

		// Function: sub_45B730
		// Original code:	mov     cl, [edi+434h]
		static NAKED void patch_45B8B1()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [edi + 434h];
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

		// Function: sub_45B730
		// Original code:	mov     dl, [edi+435h]
		static NAKED void patch_45B8BA()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [edi + 435h];
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

		// Function: sub_45F380
		// Original code:	mov     dl, [esi+2Dh]
		static NAKED void patch_45F5B2()
		{
			__asm
			{
				movzx edx, byte ptr[esi + 2Dh];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_45F380
		// Original code:	mov     [ebp+434h], dl
		static NAKED void patch_45F5B5()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [ebp + 434h];
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

		// Function: sub_45F380
		// Original code:	mov     al, [esi+2Eh]
		static NAKED void patch_45F5BB()
		{
			__asm
			{
				movzx eax, byte ptr[esi + 2Eh];
				cmp al, -1;
				jne doReturn;
				mov eax, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_45F380
		// Original code:	mov     [ebp+435h], al
		static NAKED void patch_45F5BE()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [ebp + 435h];
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

		// Function: sub_45F380
		// Original code:	mov     cl, [esi+2Dh]
		static NAKED void patch_45F6F5()
		{
			__asm
			{
				movzx ecx, byte ptr[esi + 2Dh];
				cmp cl, -1;
				jne doReturn;
				mov ecx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_45F380
		// Original code:	mov     [edi+434h], cl
		static NAKED void patch_45F6F8()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ecx;
				lea eax, [edi + 434h];
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

		// Function: sub_45F380
		// Original code:	mov     dl, [esi+2Eh]
		static NAKED void patch_45F6FE()
		{
			__asm
			{
				movzx edx, byte ptr[esi + 2Eh];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_45F380
		// Original code:	mov     [edi+435h], dl
		static NAKED void patch_45F702()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [edi + 435h];
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

		// Function: sub_45F380
		// Original code:	mov     cl, [esi+2Dh]
		static NAKED void patch_45F833()
		{
			__asm
			{
				movzx ecx, byte ptr[esi + 2Dh];
				cmp cl, -1;
				jne doReturn;
				mov ecx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_45F380
		// Original code:	mov     [edi+434h], cl
		static NAKED void patch_45F836()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ecx;
				lea eax, [edi + 434h];
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

		// Function: sub_45F380
		// Original code:	mov     dl, [esi+2Eh]
		static NAKED void patch_45F83C()
		{
			__asm
			{
				movzx edx, byte ptr[esi + 2Eh];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_45F380
		// Original code:	mov     [edi+435h], dl
		static NAKED void patch_45F840()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [edi + 435h];
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

		// Function: sub_45F380
		// Original code:	mov     cl, [esi+2Dh]
		static NAKED void patch_45F966()
		{
			__asm
			{
				movzx ecx, byte ptr[esi + 2Dh];
				cmp cl, -1;
				jne doReturn;
				mov ecx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_45F380
		// Original code:	mov     [edi+434h], cl
		static NAKED void patch_45F969()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ecx;
				lea eax, [edi + 434h];
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

		// Function: sub_45F380
		// Original code:	mov     dl, [esi+2Eh]
		static NAKED void patch_45F96F()
		{
			__asm
			{
				movzx edx, byte ptr[esi + 2Eh];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_45F380
		// Original code:	mov     [edi+435h], dl
		static NAKED void patch_45F973()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [edi + 435h];
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

		// Function: sub_45F380
		// Original code:	mov     cl, [esi+2Dh]
		static NAKED void patch_45FA99()
		{
			__asm
			{
				movzx ecx, byte ptr[esi + 2Dh];
				cmp cl, -1;
				jne doReturn;
				mov ecx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_45F380
		// Original code:	mov     [edi+434h], cl
		static NAKED void patch_45FA9C()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ecx;
				lea eax, [edi + 434h];
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

		// Function: sub_45F380
		// Original code:	mov     dl, [esi+2Eh]
		static NAKED void patch_45FAA2()
		{
			__asm
			{
				movzx edx, byte ptr[esi + 2Eh];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_45F380
		// Original code:	mov     [edi+435h], dl
		static NAKED void patch_45FAA6()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [edi + 435h];
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

		// Function: sub_45F380
		// Original code:	mov     cl, [esi+2Dh]
		static NAKED void patch_45FBE0()
		{
			__asm
			{
				movzx ecx, byte ptr[esi + 2Dh];
				cmp cl, -1;
				jne doReturn;
				mov ecx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_45F380
		// Original code:	mov     [edi+434h], cl
		static NAKED void patch_45FBE3()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ecx;
				lea eax, [edi + 434h];
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

		// Function: sub_45F380
		// Original code:	mov     dl, [esi+2Eh]
		static NAKED void patch_45FBE9()
		{
			__asm
			{
				movzx edx, byte ptr[esi + 2Eh];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_45F380
		// Original code:	mov     [edi+435h], dl
		static NAKED void patch_45FBED()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [edi + 435h];
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

		// Function: sub_47A760
		// Original code:	mov     [eax+436h], cl
		static NAKED void patch_47B91A()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ecx;
				lea eax, [eax + 436h];
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

		// Function: sub_47A760
		// Original code:	mov     [eax+437h], dl
		static NAKED void patch_47B926()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [eax + 437h];
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

		// Function: sub_47A760
		// Original code:	movzx   ecx, byte ptr [eax+436h]
		static NAKED void patch_47B94D()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [eax + 436h];
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

		// Function: sub_47A760
		// Original code:	movzx   edx, byte ptr [eax+437h]
		static NAKED void patch_47B95A()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [eax + 437h];
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

		// Function: sub_47A760
		// Original code:	mov     [esi+434h], al
		static NAKED void patch_47BD68()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [esi + 434h];
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

		// Function: sub_47A760
		// Original code:	mov     [esi+435h], al
		static NAKED void patch_47BD75()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [esi + 435h];
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

		// Function: sub_47E090
		// Original code:	mov     [eax+434h], cl
		static NAKED void patch_47EAB8()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ecx;
				lea eax, [eax + 434h];
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

		// Function: sub_47E090
		// Original code:	mov     [eax+435h], dl
		static NAKED void patch_47EAC4()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [eax + 435h];
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

		// Function: sub_489500
		// Original code:	movzx   ecx, byte ptr [eax+434h]
		static NAKED void patch_489659()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [eax + 434h];
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

		// Function: sub_489500
		// Original code:	movzx   edx, byte ptr [eax+435h]
		static NAKED void patch_489666()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [eax + 435h];
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

		// Function: sub_4C8220
		// Original code:	movzx   esi, ds:PrimaryColor
		static NAKED void patch_4C833F()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push 0xB4E3F0;	// PrimaryColor
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				mov esi, eax;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_4C8220
		// Original code:	movzx   esi, ds:SecondaryColor
		static NAKED void patch_4C8350()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push 0xB4E3F1;	// SecondaryColor
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				mov esi, eax;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_4C8220
		// Original code:	movzx   esi, ds:TertiaryColor
		static NAKED void patch_4C8361()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push 0xB4E3F2;	// TertiaryColor
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				mov esi, eax;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_4C8220
		// Original code:	movzx   esi, ds:QuaternaryColor
		static NAKED void patch_4C8372()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push 0xB4E3F3;	// QuaternaryColor
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				mov esi, eax;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_4C8490
		// Original code:	mov     al, 0FFh
		static NAKED void patch_4C8490()
		{
			__asm
			{
				mov eax, -1;
				retn;
			}
		}

		// Function: sub_4C8490
		// Original code:	mov     [ecx+2D2h], al
		static NAKED void patch_4C8492()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [ecx + 2D2h];
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

		// Function: sub_4C8490
		// Original code:	mov     [ecx+2D3h], al
		static NAKED void patch_4C8498()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [ecx + 2D3h];
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

		// Function: sub_4C8490
		// Original code:	mov     [ecx+2D4h], al
		static NAKED void patch_4C849E()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [ecx + 2D4h];
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

		// Function: sub_4C8490
		// Original code:	mov     [ecx+2D5h], al
		static NAKED void patch_4C84A4()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [ecx + 2D5h];
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

		// Function: sub_4C84B0
		// Original code:	mov     ds:PrimaryColor, al
		static NAKED void patch_4C84C7()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				push 0xB4E3F0;	// PrimaryColor
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_4C84B0
		// Original code:	mov     ds:QuaternaryColor, bl
		static NAKED void patch_4C84CC()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ebx;
				push 0xB4E3F3;	// QuaternaryColor
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_4C84B0
		// Original code:	mov     ds:SecondaryColor, dl
		static NAKED void patch_4C84D2()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				push 0xB4E3F1;	// SecondaryColor
				call SetExtendedIDfrom8bitBefore;
				add esp, 8;
				pop edx;
				pop ecx;
				pop eax;
				popfd;
				retn;
			}
		}

		// Function: sub_4C84B0
		// Original code:	mov     [ecx+2D2h], al
		static NAKED void patch_4C84D8()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [ecx + 2D2h];
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

		// Function: sub_4C84B0
		// Original code:	mov     [ecx+2D5h], bl
		static NAKED void patch_4C84E2()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ebx;
				lea eax, [ecx + 2D5h];
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

		// Function: sub_4C84B0
		// Original code:	mov     [ecx+2D3h], dl
		static NAKED void patch_4C84E8()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [ecx + 2D3h];
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

		// Function: sub_4C84B0
		// Original code:	mov     [ecx+2D4h], al
		static NAKED void patch_4C84EE()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [ecx + 2D4h];
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

		// Function: sub_4C8500
		// Original code:	mov     byte ptr [eax], 7Eh
		static NAKED void patch_4C8537()
		{
			__asm
			{
				mov[eax], 126;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     byte ptr [ecx], 7Eh
		static NAKED void patch_4C853F()
		{
			__asm
			{
				mov[ecx], 126;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     byte ptr [edx], 7Eh
		static NAKED void patch_4C8543()
		{
			__asm
			{
				mov[edx], 126;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     byte ptr [eax], 7Eh
		static NAKED void patch_4C8546()
		{
			__asm
			{
				mov[eax], 126;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     al, [edx+esi+2B0h]
		static NAKED void patch_4C8573()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [edx + esi + 2B0h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     [edi], al
		static NAKED void patch_4C857A()
		{
			__asm
			{
				mov[edi], eax;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     dl, [ecx+esi+2B8h]
		static NAKED void patch_4C8583()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [ecx + esi + 2B8h];
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

		// Function: sub_4C8500
		// Original code:	mov     [ebx], dl
		static NAKED void patch_4C858A()
		{
			__asm
			{
				mov[ebx], edx;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     cl, [eax+esi+2C0h]
		static NAKED void patch_4C8593()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [eax + esi + 2C0h];
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

		// Function: sub_4C8500
		// Original code:	mov     [ebp+0], cl
		static NAKED void patch_4C859A()
		{
			__asm
			{
				mov[ebp + 0], ecx;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     al, [edx+esi+2C8h]
		static NAKED void patch_4C85A4()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [edx + esi + 2C8h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     [ecx], al
		static NAKED void patch_4C85AF()
		{
			__asm
			{
				mov[ecx], eax;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     cl, [eax+434h]
		static NAKED void patch_4C85E3()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [eax + 434h];
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

		// Function: sub_4C8500
		// Original code:	cmp     cl, [edi]
		static NAKED void patch_4C85E9()
		{
			__asm
			{
				cmp ecx, [edi];
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     dl, [eax+435h]
		static NAKED void patch_4C85F1()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [eax + 435h];
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

		// Function: sub_4C8500
		// Original code:	cmp     dl, [ebx]
		static NAKED void patch_4C85F7()
		{
			__asm
			{
				cmp edx, [ebx];
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     cl, [eax+436h]
		static NAKED void patch_4C85FF()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [eax + 436h];
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

		// Function: sub_4C8500
		// Original code:	cmp     cl, [ebp+0]
		static NAKED void patch_4C8605()
		{
			__asm
			{
				cmp ecx, [ebp + 0];
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     dl, [eax+437h]
		static NAKED void patch_4C860E()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [eax + 437h];
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

		// Function: sub_4C8500
		// Original code:	cmp     dl, [eax]
		static NAKED void patch_4C8618()
		{
			__asm
			{
				cmp edx, [eax];
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     al, [edx+esi+2B0h]
		static NAKED void patch_4C863A()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [edx + esi + 2B0h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     [edi], al
		static NAKED void patch_4C8641()
		{
			__asm
			{
				mov[edi], eax;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     dl, [ecx+esi+2B8h]
		static NAKED void patch_4C864A()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [ecx + esi + 2B8h];
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

		// Function: sub_4C8500
		// Original code:	mov     [ebx], dl
		static NAKED void patch_4C8651()
		{
			__asm
			{
				mov[ebx], edx;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     cl, [eax+esi+2C0h]
		static NAKED void patch_4C865A()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [eax + esi + 2C0h];
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

		// Function: sub_4C8500
		// Original code:	mov     [ebp+0], cl
		static NAKED void patch_4C8661()
		{
			__asm
			{
				mov[ebp + 0], ecx;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     al, [edx+esi+2C8h]
		static NAKED void patch_4C866B()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [edx + esi + 2C8h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     [ecx], al
		static NAKED void patch_4C8679()
		{
			__asm
			{
				mov[ecx], eax;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     byte ptr [edx], 0
		static NAKED void patch_4C868B()
		{
			__asm
			{
				mov[edx], 0;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     byte ptr [eax], 0
		static NAKED void patch_4C8692()
		{
			__asm
			{
				mov[eax], 0;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     byte ptr [ecx], 0
		static NAKED void patch_4C8695()
		{
			__asm
			{
				mov[ecx], 0;
				retn;
			}
		}

		// Function: sub_4C8500
		// Original code:	mov     byte ptr [edx], 0
		static NAKED void patch_4C8698()
		{
			__asm
			{
				mov[edx], 0;
				retn;
			}
		}

		// Function: sub_4C95C0
		// Original code:	mov     [esi+2D2h], al
		static NAKED void patch_4C9648()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [esi + 2D2h];
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

		// Function: sub_4C95C0
		// Original code:	mov     [esi+2D3h], al
		static NAKED void patch_4C964E()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [esi + 2D3h];
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

		// Function: sub_4C95C0
		// Original code:	mov     [esi+2D4h], al
		static NAKED void patch_4C9654()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [esi + 2D4h];
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

		// Function: sub_4C95C0
		// Original code:	mov     [esi+2D5h], al
		static NAKED void patch_4C965A()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [esi + 2D5h];
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

		// Function: sub_4E71E0
		// Original code:	mov     al, [edi+434h]
		static NAKED void patch_4E74E9()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [edi + 434h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_4E71E0
		// Original code:	test    al, al
		static NAKED void patch_4E74EF()
		{
			__asm
			{
				test eax, eax;
				retn;
			}
		}

		// Function: sub_59F180
		// Original code:	mov     al, [esi+14Fh]
		static NAKED void patch_59F1C3()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [esi + 14Fh];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_59F180
		// Original code:	mov     dl, [esi+14Eh]
		static NAKED void patch_59F1CB()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [esi + 14Eh];
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

		// Function: sub_59F180
		// Original code:	mov     al, [esi+14Dh]
		static NAKED void patch_59F1D4()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [esi + 14Dh];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_59F180
		// Original code:	mov     dl, [esi+14Ch]
		static NAKED void patch_59F1DD()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [esi + 14Ch];
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

		// Function: sub_59F840
		// Original code:	mov     byte ptr [esi+14Dh], 0
		static NAKED void patch_59F973()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push 0;
				lea eax, [esi + 14Dh];
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
		// Original code:	mov     byte ptr [esi+14Ch], 0
		static NAKED void patch_59F97A()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push 0;
				lea eax, [esi + 14Ch];
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

		// Function: sub_5B6890
		// Original code:	mov     dl, [ecx-4]
		static NAKED void patch_5B6B50()
		{
			__asm
			{
				movzx edx, byte ptr[ecx - 4];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_5B6890
		// Original code:	mov     [eax-8], dl
		static NAKED void patch_5B6B53()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [eax - 8];
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

		// Function: sub_5B6890
		// Original code:	mov     dl, [ecx]
		static NAKED void patch_5B6B56()
		{
			__asm
			{
				movzx edx, byte ptr[ecx];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_5B6890
		// Original code:	mov     [eax], dl
		static NAKED void patch_5B6B58()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [eax];
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

		// Function: sub_5B6890
		// Original code:	mov     [eax+8], bl
		static NAKED void patch_5B6B5A()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ebx;
				lea eax, [eax + 8];
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

		// Function: sub_5B6890
		// Original code:	mov     [eax+10h], bl
		static NAKED void patch_5B6B5D()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ebx;
				lea eax, [eax + 10h];
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

		// Function: sub_5B6890
		// Original code:	mov     dl, [ecx-4]
		static NAKED void patch_5B6CD8()
		{
			__asm
			{
				movzx edx, byte ptr[ecx - 4];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_5B6890
		// Original code:	mov     [eax-8], dl
		static NAKED void patch_5B6CDB()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [eax - 8];
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

		// Function: sub_5B6890
		// Original code:	mov     dl, [ecx]
		static NAKED void patch_5B6CDE()
		{
			__asm
			{
				movzx edx, byte ptr[ecx];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_5B6890
		// Original code:	mov     [eax], dl
		static NAKED void patch_5B6CE0()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [eax];
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

		// Function: sub_5B6890
		// Original code:	mov     dl, [ecx+4]
		static NAKED void patch_5B6CE2()
		{
			__asm
			{
				movzx edx, byte ptr[ecx + 4];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_5B6890
		// Original code:	mov     [eax+8], dl
		static NAKED void patch_5B6CE5()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [eax + 8];
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

		// Function: sub_5B6890
		// Original code:	mov     dl, [ecx+8]
		static NAKED void patch_5B6CE8()
		{
			__asm
			{
				movzx edx, byte ptr[ecx + 8];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_5B6890
		// Original code:	mov     [eax+10h], dl
		static NAKED void patch_5B6CEB()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [eax + 10h];
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

		// Function: sub_5D2330
		// Original code:	mov     cl, [edi+434h]
		static NAKED void patch_5D2341()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [edi + 434h];
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

		// Function: sub_5D2330
		// Original code:	mov     dl, [edi+435h]
		static NAKED void patch_5D234A()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [edi + 435h];
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

		// Function: sub_5D2330
		// Original code:	mov     al, [edi+436h]
		static NAKED void patch_5D2353()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [edi + 436h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_5D2330
		// Original code:	mov     cl, [edi+437h]
		static NAKED void patch_5D235C()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [edi + 437h];
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

		// Function: sub_5D23B0
		// Original code:	mov     al, [esi+49h]
		static NAKED void patch_5D23C0()
		{
			__asm
			{
				movzx eax, byte ptr[esi + 49h];
				cmp al, -1;
				jne doReturn;
				mov eax, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_5D23B0
		// Original code:	mov     [edi+434h], al
		static NAKED void patch_5D23C3()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [edi + 434h];
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

		// Function: sub_5D23B0
		// Original code:	mov     cl, [esi+4Ah]
		static NAKED void patch_5D23C9()
		{
			__asm
			{
				movzx ecx, byte ptr[esi + 4Ah];
				cmp cl, -1;
				jne doReturn;
				mov ecx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_5D23B0
		// Original code:	mov     [edi+435h], cl
		static NAKED void patch_5D23CC()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ecx;
				lea eax, [edi + 435h];
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

		// Function: sub_5D23B0
		// Original code:	mov     dl, [esi+4Bh]
		static NAKED void patch_5D23D2()
		{
			__asm
			{
				movzx edx, byte ptr[esi + 4Bh];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_5D23B0
		// Original code:	mov     [edi+436h], dl
		static NAKED void patch_5D23D5()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [edi + 436h];
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

		// Function: sub_5D23B0
		// Original code:	mov     al, [esi+4Ch]
		static NAKED void patch_5D23DB()
		{
			__asm
			{
				movzx eax, byte ptr[esi + 4Ch];
				cmp al, -1;
				jne doReturn;
				mov eax, -1;
			doReturn:
				retn;
			}
		}

		// Function: sub_5D23B0
		// Original code:	mov     [edi+437h], al
		static NAKED void patch_5D23DE()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [edi + 437h];
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

		// Function: sub_6A6DC0
		// Original code:	movzx   eax, byte ptr [edi+434h]
		static NAKED void patch_6A6FF0()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [edi + 434h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_406044
		// Original code:	mov     cl, [ebx+434h]
		static NAKED void patch_6A880B()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [ebx + 434h];
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

		// Function: sub_406044
		// Original code:	mov     [ebp+14Ch], cl
		static NAKED void patch_6A8811()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push ecx;
				lea eax, [ebp + 14Ch];
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

		// Function: sub_406044
		// Original code:	mov     dl, [ebx+435h]
		static NAKED void patch_6A8817()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [ebx + 435h];
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

		// Function: sub_406044
		// Original code:	mov     [ebp+14Dh], dl
		static NAKED void patch_6A881D()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [ebp + 14Dh];
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

		// Function: sub_6C4400
		// Original code:	mov     al, [esi+437h]
		static NAKED void patch_6C441D()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [esi + 437h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_6C4400
		// Original code:	mov     dl, [esi+436h]
		static NAKED void patch_6C442B()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [esi + 436h];
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

		// Function: sub_6C4400
		// Original code:	mov     al, [esi+435h]
		static NAKED void patch_6C4435()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [esi + 435h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_6C4400
		// Original code:	mov     dl, [esi+434h]
		static NAKED void patch_6C443E()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [esi + 434h];
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

		// Function: sub_6D64F0
		// Original code:	mov     byte ptr [esi+434h], 1
		static NAKED void patch_6D65C9()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push 1;
				lea eax, [esi + 434h];
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

		// Function: sub_6D64F0
		// Original code:	mov     dl, [esi+437h]
		static NAKED void patch_6D65ED()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [esi + 437h];
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

		// Function: sub_6D64F0
		// Original code:	mov     al, [esi+436h]
		static NAKED void patch_6D65F5()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [esi + 436h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: sub_6D64F0
		// Original code:	mov     cl, [esi+435h]
		static NAKED void patch_6D65FD()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [esi + 435h];
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

		// Function: sub_6D64F0
		// Original code:	mov     dl, [esi+434h]
		static NAKED void patch_6D6606()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				lea eax, [esi + 434h];
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

		// Function: _ZN13CCarGenerator20DoInternalProcessingEv
		// Original code:	mov     al, [edi+2]
		static NAKED void patch_6F3DB6()
		{
			__asm
			{
				movzx eax, byte ptr[edi + 2];
				cmp al, -1;
				jne doReturn;
				mov eax, -1;
			doReturn:
				retn;
			}
		}

		// Function: _ZN13CCarGenerator20DoInternalProcessingEv
		// Original code:	mov     [esi+434h], al
		static NAKED void patch_6F3DC3()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push eax;
				lea eax, [esi + 434h];
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

		// Function: _ZN13CCarGenerator20DoInternalProcessingEv
		// Original code:	mov     dl, [edi+3]
		static NAKED void patch_6F3DC9()
		{
			__asm
			{
				movzx edx, byte ptr[edi + 3];
				cmp dl, -1;
				jne doReturn;
				mov edx, -1;
			doReturn:
				retn;
			}
		}

		// Function: _ZN13CCarGenerator20DoInternalProcessingEv
		// Original code:	mov     [esi+435h], dl
		static NAKED void patch_6F3DCC()
		{
			__asm
			{
				pushfd;
				push eax;
				push ecx;
				push edx;
				push edx;
				lea eax, [esi + 435h];
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

		// Function: _ZN13CCarGenerator20DoInternalProcessingEv
		// Original code:	mov     al, [esi+434h]
		static NAKED void patch_6F3DDA()
		{
			__asm
			{
				pushfd;
				push ecx;
				push edx;
				lea eax, [esi + 434h];
				push eax;
				call GetExtendedIDfrom8bitBefore;
				add esp, 4;
				pop edx;
				pop ecx;
				popfd;
				retn;
			}
		}

		// Function: _ZN13CCarGenerator20DoInternalProcessingEv
		// Original code:	mov     cl, [esi+435h]
		static NAKED void patch_6F3DE3()
		{
			__asm
			{
				pushfd;
				push eax;
				push edx;
				lea eax, [esi + 435h];
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

	}

	namespace VehicleColorIDpatches
	{
		static const tArrayItem ptrArray[] =
		{
			tArrayItem(0x406000, &patch_406000),	// sub_4C84B0 : mov     ds:TertiaryColor, bl
			tArrayItem(0x43088C, &patch_43088C),	// sub_403AEE : mov     byte ptr [esi+434h], 0
			tArrayItem(0x430893, &patch_430893),	// sub_403AEE : mov     byte ptr [esi+435h], 0
			tArrayItem(0x4482A2, &patch_4482A2),	// sub_447E40 : mov     cl, [edi+32h]
			tArrayItem(0x4482A5, &patch_4482A5),	// sub_447E40 : mov     [esi+434h], cl
			tArrayItem(0x4482AB, &patch_4482AB),	// sub_447E40 : mov     dl, [edi+33h]
			tArrayItem(0x4482AE, &patch_4482AE),	// sub_447E40 : mov     [esi+435h], dl
			tArrayItem(0x4482B4, &patch_4482B4),	// sub_447E40 : mov     al, [edi+34h]
			tArrayItem(0x4482B7, &patch_4482B7),	// sub_447E40 : mov     [esi+436h], al
			tArrayItem(0x4482C3, &patch_4482C3),	// sub_447E40 : mov     cl, [edi+35h]
			tArrayItem(0x4482CF, &patch_4482CF),	// sub_447E40 : mov     [esi+437h], cl
			tArrayItem(0x4497EA, &patch_4497EA),	// sub_449760 : mov     cl, [esi+434h]
			tArrayItem(0x4497F3, &patch_4497F3),	// sub_449760 : mov     dl, [esi+435h]
			tArrayItem(0x4497FC, &patch_4497FC),	// sub_449760 : mov     al, [esi+436h]
			tArrayItem(0x449805, &patch_449805),	// sub_449760 : mov     cl, [esi+437h]
			tArrayItem(0x44B1B7, &patch_44B1B7),	// sub_44AA50 : movzx   edx, byte ptr [edi+434h]
			tArrayItem(0x45B8B1, &patch_45B8B1),	// sub_45B730 : mov     cl, [edi+434h]
			tArrayItem(0x45B8BA, &patch_45B8BA),	// sub_45B730 : mov     dl, [edi+435h]
			tArrayItem(0x45F5B2, &patch_45F5B2),	// sub_45F380 : mov     dl, [esi+2Dh]
			tArrayItem(0x45F5B5, &patch_45F5B5),	// sub_45F380 : mov     [ebp+434h], dl
			tArrayItem(0x45F5BB, &patch_45F5BB),	// sub_45F380 : mov     al, [esi+2Eh]
			tArrayItem(0x45F5BE, &patch_45F5BE),	// sub_45F380 : mov     [ebp+435h], al
			tArrayItem(0x45F6F5, &patch_45F6F5),	// sub_45F380 : mov     cl, [esi+2Dh]
			tArrayItem(0x45F6F8, &patch_45F6F8),	// sub_45F380 : mov     [edi+434h], cl
			tArrayItem(0x45F6FE, &patch_45F6FE),	// sub_45F380 : mov     dl, [esi+2Eh]
			tArrayItem(0x45F702, &patch_45F702),	// sub_45F380 : mov     [edi+435h], dl
			tArrayItem(0x45F833, &patch_45F833),	// sub_45F380 : mov     cl, [esi+2Dh]
			tArrayItem(0x45F836, &patch_45F836),	// sub_45F380 : mov     [edi+434h], cl
			tArrayItem(0x45F83C, &patch_45F83C),	// sub_45F380 : mov     dl, [esi+2Eh]
			tArrayItem(0x45F840, &patch_45F840),	// sub_45F380 : mov     [edi+435h], dl
			tArrayItem(0x45F966, &patch_45F966),	// sub_45F380 : mov     cl, [esi+2Dh]
			tArrayItem(0x45F969, &patch_45F969),	// sub_45F380 : mov     [edi+434h], cl
			tArrayItem(0x45F96F, &patch_45F96F),	// sub_45F380 : mov     dl, [esi+2Eh]
			tArrayItem(0x45F973, &patch_45F973),	// sub_45F380 : mov     [edi+435h], dl
			tArrayItem(0x45FA99, &patch_45FA99),	// sub_45F380 : mov     cl, [esi+2Dh]
			tArrayItem(0x45FA9C, &patch_45FA9C),	// sub_45F380 : mov     [edi+434h], cl
			tArrayItem(0x45FAA2, &patch_45FAA2),	// sub_45F380 : mov     dl, [esi+2Eh]
			tArrayItem(0x45FAA6, &patch_45FAA6),	// sub_45F380 : mov     [edi+435h], dl
			tArrayItem(0x45FBE0, &patch_45FBE0),	// sub_45F380 : mov     cl, [esi+2Dh]
			tArrayItem(0x45FBE3, &patch_45FBE3),	// sub_45F380 : mov     [edi+434h], cl
			tArrayItem(0x45FBE9, &patch_45FBE9),	// sub_45F380 : mov     dl, [esi+2Eh]
			tArrayItem(0x45FBED, &patch_45FBED),	// sub_45F380 : mov     [edi+435h], dl
			tArrayItem(0x47B91A, &patch_47B91A),	// sub_47A760 : mov     [eax+436h], cl
			tArrayItem(0x47B926, &patch_47B926),	// sub_47A760 : mov     [eax+437h], dl
			tArrayItem(0x47B94D, &patch_47B94D),	// sub_47A760 : movzx   ecx, byte ptr [eax+436h]
			tArrayItem(0x47B95A, &patch_47B95A),	// sub_47A760 : movzx   edx, byte ptr [eax+437h]
			tArrayItem(0x47BD68, &patch_47BD68),	// sub_47A760 : mov     [esi+434h], al
			tArrayItem(0x47BD75, &patch_47BD75),	// sub_47A760 : mov     [esi+435h], al
			tArrayItem(0x47EAB8, &patch_47EAB8),	// sub_47E090 : mov     [eax+434h], cl
			tArrayItem(0x47EAC4, &patch_47EAC4),	// sub_47E090 : mov     [eax+435h], dl
			tArrayItem(0x489659, &patch_489659),	// sub_489500 : movzx   ecx, byte ptr [eax+434h]
			tArrayItem(0x489666, &patch_489666),	// sub_489500 : movzx   edx, byte ptr [eax+435h]
			tArrayItem(0x4C833F, &patch_4C833F),	// sub_4C8220 : movzx   esi, ds:PrimaryColor
			tArrayItem(0x4C8350, &patch_4C8350),	// sub_4C8220 : movzx   esi, ds:SecondaryColor
			tArrayItem(0x4C8361, &patch_4C8361),	// sub_4C8220 : movzx   esi, ds:TertiaryColor
			tArrayItem(0x4C8372, &patch_4C8372),	// sub_4C8220 : movzx   esi, ds:QuaternaryColor
			tArrayItem(0x4C8490, &patch_4C8490),	// sub_4C8490 : mov     al, 0FFh
			tArrayItem(0x4C8492, &patch_4C8492),	// sub_4C8490 : mov     [ecx+2D2h], al
			tArrayItem(0x4C8498, &patch_4C8498),	// sub_4C8490 : mov     [ecx+2D3h], al
			tArrayItem(0x4C849E, &patch_4C849E),	// sub_4C8490 : mov     [ecx+2D4h], al
			tArrayItem(0x4C84A4, &patch_4C84A4),	// sub_4C8490 : mov     [ecx+2D5h], al
			tArrayItem(0x4C84C7, &patch_4C84C7),	// sub_4C84B0 : mov     ds:PrimaryColor, al
			tArrayItem(0x4C84CC, &patch_4C84CC),	// sub_4C84B0 : mov     ds:QuaternaryColor, bl
			tArrayItem(0x4C84D2, &patch_4C84D2),	// sub_4C84B0 : mov     ds:SecondaryColor, dl
			tArrayItem(0x4C84D8, &patch_4C84D8),	// sub_4C84B0 : mov     [ecx+2D2h], al
			tArrayItem(0x4C84E2, &patch_4C84E2),	// sub_4C84B0 : mov     [ecx+2D5h], bl
			tArrayItem(0x4C84E8, &patch_4C84E8),	// sub_4C84B0 : mov     [ecx+2D3h], dl
			tArrayItem(0x4C84EE, &patch_4C84EE),	// sub_4C84B0 : mov     [ecx+2D4h], al
			tArrayItem(0x4C8537, &patch_4C8537),	// sub_4C8500 : mov     byte ptr [eax], 7Eh
			tArrayItem(0x4C853F, &patch_4C853F),	// sub_4C8500 : mov     byte ptr [ecx], 7Eh
			tArrayItem(0x4C8543, &patch_4C8543),	// sub_4C8500 : mov     byte ptr [edx], 7Eh
			tArrayItem(0x4C8546, &patch_4C8546),	// sub_4C8500 : mov     byte ptr [eax], 7Eh
			tArrayItem(0x4C8573, &patch_4C8573),	// sub_4C8500 : mov     al, [edx+esi+2B0h]
			tArrayItem(0x4C857A, &patch_4C857A),	// sub_4C8500 : mov     [edi], al
			tArrayItem(0x4C8583, &patch_4C8583),	// sub_4C8500 : mov     dl, [ecx+esi+2B8h]
			tArrayItem(0x4C858A, &patch_4C858A),	// sub_4C8500 : mov     [ebx], dl
			tArrayItem(0x4C8593, &patch_4C8593),	// sub_4C8500 : mov     cl, [eax+esi+2C0h]
			tArrayItem(0x4C859A, &patch_4C859A),	// sub_4C8500 : mov     [ebp+0], cl
			tArrayItem(0x4C85A4, &patch_4C85A4),	// sub_4C8500 : mov     al, [edx+esi+2C8h]
			tArrayItem(0x4C85AF, &patch_4C85AF),	// sub_4C8500 : mov     [ecx], al
			tArrayItem(0x4C85E3, &patch_4C85E3),	// sub_4C8500 : mov     cl, [eax+434h]
			tArrayItem(0x4C85E9, &patch_4C85E9),	// sub_4C8500 : cmp     cl, [edi]
			tArrayItem(0x4C85F1, &patch_4C85F1),	// sub_4C8500 : mov     dl, [eax+435h]
			tArrayItem(0x4C85F7, &patch_4C85F7),	// sub_4C8500 : cmp     dl, [ebx]
			tArrayItem(0x4C85FF, &patch_4C85FF),	// sub_4C8500 : mov     cl, [eax+436h]
			tArrayItem(0x4C8605, &patch_4C8605),	// sub_4C8500 : cmp     cl, [ebp+0]
			tArrayItem(0x4C860E, &patch_4C860E),	// sub_4C8500 : mov     dl, [eax+437h]
			tArrayItem(0x4C8618, &patch_4C8618),	// sub_4C8500 : cmp     dl, [eax]
			tArrayItem(0x4C863A, &patch_4C863A),	// sub_4C8500 : mov     al, [edx+esi+2B0h]
			tArrayItem(0x4C8641, &patch_4C8641),	// sub_4C8500 : mov     [edi], al
			tArrayItem(0x4C864A, &patch_4C864A),	// sub_4C8500 : mov     dl, [ecx+esi+2B8h]
			tArrayItem(0x4C8651, &patch_4C8651),	// sub_4C8500 : mov     [ebx], dl
			tArrayItem(0x4C865A, &patch_4C865A),	// sub_4C8500 : mov     cl, [eax+esi+2C0h]
			tArrayItem(0x4C8661, &patch_4C8661),	// sub_4C8500 : mov     [ebp+0], cl
			tArrayItem(0x4C866B, &patch_4C866B),	// sub_4C8500 : mov     al, [edx+esi+2C8h]
			tArrayItem(0x4C8679, &patch_4C8679),	// sub_4C8500 : mov     [ecx], al
			tArrayItem(0x4C868B, &patch_4C868B),	// sub_4C8500 : mov     byte ptr [edx], 0
			tArrayItem(0x4C8692, &patch_4C8692),	// sub_4C8500 : mov     byte ptr [eax], 0
			tArrayItem(0x4C8695, &patch_4C8695),	// sub_4C8500 : mov     byte ptr [ecx], 0
			tArrayItem(0x4C8698, &patch_4C8698),	// sub_4C8500 : mov     byte ptr [edx], 0
			tArrayItem(0x4C9648, &patch_4C9648),	// sub_4C95C0 : mov     [esi+2D2h], al
			tArrayItem(0x4C964E, &patch_4C964E),	// sub_4C95C0 : mov     [esi+2D3h], al
			tArrayItem(0x4C9654, &patch_4C9654),	// sub_4C95C0 : mov     [esi+2D4h], al
			tArrayItem(0x4C965A, &patch_4C965A),	// sub_4C95C0 : mov     [esi+2D5h], al
			tArrayItem(0x4E74E9, &patch_4E74E9),	// sub_4E71E0 : mov     al, [edi+434h]
			tArrayItem(0x4E74EF, &patch_4E74EF),	// sub_4E71E0 : test    al, al
			tArrayItem(0x59F1C3, &patch_59F1C3),	// sub_59F180 : mov     al, [esi+14Fh]
			tArrayItem(0x59F1CB, &patch_59F1CB),	// sub_59F180 : mov     dl, [esi+14Eh]
			tArrayItem(0x59F1D4, &patch_59F1D4),	// sub_59F180 : mov     al, [esi+14Dh]
			tArrayItem(0x59F1DD, &patch_59F1DD),	// sub_59F180 : mov     dl, [esi+14Ch]
			tArrayItem(0x59F973, &patch_59F973),	// sub_59F840 : mov     byte ptr [esi+14Dh], 0
			tArrayItem(0x59F97A, &patch_59F97A),	// sub_59F840 : mov     byte ptr [esi+14Ch], 0
			tArrayItem(0x5B6B50, &patch_5B6B50),	// sub_5B6890 : mov     dl, [ecx-4]
			tArrayItem(0x5B6B53, &patch_5B6B53),	// sub_5B6890 : mov     [eax-8], dl
			tArrayItem(0x5B6B56, &patch_5B6B56),	// sub_5B6890 : mov     dl, [ecx]
			tArrayItem(0x5B6B58, &patch_5B6B58),	// sub_5B6890 : mov     [eax], dl
			tArrayItem(0x5B6B5A, &patch_5B6B5A),	// sub_5B6890 : mov     [eax+8], bl
			tArrayItem(0x5B6B5D, &patch_5B6B5D),	// sub_5B6890 : mov     [eax+10h], bl
			tArrayItem(0x5B6CD8, &patch_5B6CD8),	// sub_5B6890 : mov     dl, [ecx-4]
			tArrayItem(0x5B6CDB, &patch_5B6CDB),	// sub_5B6890 : mov     [eax-8], dl
			tArrayItem(0x5B6CDE, &patch_5B6CDE),	// sub_5B6890 : mov     dl, [ecx]
			tArrayItem(0x5B6CE0, &patch_5B6CE0),	// sub_5B6890 : mov     [eax], dl
			tArrayItem(0x5B6CE2, &patch_5B6CE2),	// sub_5B6890 : mov     dl, [ecx+4]
			tArrayItem(0x5B6CE5, &patch_5B6CE5),	// sub_5B6890 : mov     [eax+8], dl
			tArrayItem(0x5B6CE8, &patch_5B6CE8),	// sub_5B6890 : mov     dl, [ecx+8]
			tArrayItem(0x5B6CEB, &patch_5B6CEB),	// sub_5B6890 : mov     [eax+10h], dl
			tArrayItem(0x5D2341, &patch_5D2341),	// sub_5D2330 : mov     cl, [edi+434h]
			tArrayItem(0x5D234A, &patch_5D234A),	// sub_5D2330 : mov     dl, [edi+435h]
			tArrayItem(0x5D2353, &patch_5D2353),	// sub_5D2330 : mov     al, [edi+436h]
			tArrayItem(0x5D235C, &patch_5D235C),	// sub_5D2330 : mov     cl, [edi+437h]
			tArrayItem(0x5D23C0, &patch_5D23C0),	// sub_5D23B0 : mov     al, [esi+49h]
			tArrayItem(0x5D23C3, &patch_5D23C3),	// sub_5D23B0 : mov     [edi+434h], al
			tArrayItem(0x5D23C9, &patch_5D23C9),	// sub_5D23B0 : mov     cl, [esi+4Ah]
			tArrayItem(0x5D23CC, &patch_5D23CC),	// sub_5D23B0 : mov     [edi+435h], cl
			tArrayItem(0x5D23D2, &patch_5D23D2),	// sub_5D23B0 : mov     dl, [esi+4Bh]
			tArrayItem(0x5D23D5, &patch_5D23D5),	// sub_5D23B0 : mov     [edi+436h], dl
			tArrayItem(0x5D23DB, &patch_5D23DB),	// sub_5D23B0 : mov     al, [esi+4Ch]
			tArrayItem(0x5D23DE, &patch_5D23DE),	// sub_5D23B0 : mov     [edi+437h], al
			tArrayItem(0x6A6FF0, &patch_6A6FF0),	// sub_6A6DC0 : movzx   eax, byte ptr [edi+434h]
			tArrayItem(0x6A880B, &patch_6A880B),	// sub_406044 : mov     cl, [ebx+434h]
			tArrayItem(0x6A8811, &patch_6A8811),	// sub_406044 : mov     [ebp+14Ch], cl
			tArrayItem(0x6A8817, &patch_6A8817),	// sub_406044 : mov     dl, [ebx+435h]
			tArrayItem(0x6A881D, &patch_6A881D),	// sub_406044 : mov     [ebp+14Dh], dl
			tArrayItem(0x6C441D, &patch_6C441D),	// sub_6C4400 : mov     al, [esi+437h]
			tArrayItem(0x6C442B, &patch_6C442B),	// sub_6C4400 : mov     dl, [esi+436h]
			tArrayItem(0x6C4435, &patch_6C4435),	// sub_6C4400 : mov     al, [esi+435h]
			tArrayItem(0x6C443E, &patch_6C443E),	// sub_6C4400 : mov     dl, [esi+434h]
			tArrayItem(0x6D65C9, &patch_6D65C9),	// sub_6D64F0 : mov     byte ptr [esi+434h], 1
			tArrayItem(0x6D65ED, &patch_6D65ED),	// sub_6D64F0 : mov     dl, [esi+437h]
			tArrayItem(0x6D65F5, &patch_6D65F5),	// sub_6D64F0 : mov     al, [esi+436h]
			tArrayItem(0x6D65FD, &patch_6D65FD),	// sub_6D64F0 : mov     cl, [esi+435h]
			tArrayItem(0x6D6606, &patch_6D6606),	// sub_6D64F0 : mov     dl, [esi+434h]
			tArrayItem(0x6F3DB6, &patch_6F3DB6),	// _ZN13CCarGenerator20DoInternalProcessingEv : mov     al, [edi+2]
			tArrayItem(0x6F3DC3, &patch_6F3DC3),	// _ZN13CCarGenerator20DoInternalProcessingEv : mov     [esi+434h], al
			tArrayItem(0x6F3DC9, &patch_6F3DC9),	// _ZN13CCarGenerator20DoInternalProcessingEv : mov     dl, [edi+3]
			tArrayItem(0x6F3DCC, &patch_6F3DCC),	// _ZN13CCarGenerator20DoInternalProcessingEv : mov     [esi+435h], dl
			tArrayItem(0x6F3DDA, &patch_6F3DDA),	// _ZN13CCarGenerator20DoInternalProcessingEv : mov     al, [esi+434h]
			tArrayItem(0x6F3DE3, &patch_6F3DE3),	// _ZN13CCarGenerator20DoInternalProcessingEv : mov     cl, [esi+435h]

		};
	}
	#endif
}

// Sets the max number of vehicle color
void OtherLimits::SetVehicleColors(int iVehicleColors)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iVehicleColors = this->ms_iVehicleColorsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		bool bIsHOODLUM = gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86;

		if (iVehicleColors > this->ms_iVehicleColorsLimit)
		{
			CVehicleModelInfo__ms_vehicleColourTable.gta_sa = new CRGBA[iVehicleColors];
			CVehicleModelInfo__ms_vehicleColourTable.bIsAllocated.Set(true);
		}

		// Patch references
		#if TRUE
		{
			CPatch::PatchPointer(0x447094 + 3, CVehicleModelInfo__ms_vehicleColourTable.gta_sa);	// lea     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE.red[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_447090
			CPatch::PatchPointer(0x44B1BE + 3, CVehicleModelInfo__ms_vehicleColourTable.gta_sa);	// mov     eax, dword ptr ds:_ZN17CVehicleModelInfo21ms_vehicleColourTableE.red[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_44AA50
			CPatch::PatchPointer(0x4C838D + 3, CVehicleModelInfo__ms_vehicleColourTable.gta_sa);	// mov     cl, ds:_ZN17CVehicleModelInfo21ms_vehicleColourTableE.red[esi*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_4C8220
			CPatch::PatchPointer(0x4C8396 + 3, &CVehicleModelInfo__ms_vehicleColourTable.gta_sa->green);	// mov     dl, ds:_ZN17CVehicleModelInfo21ms_vehicleColourTableE.green[esi*4]	; sub_4C8220
			CPatch::PatchPointer(0x4C83A0 + 3, &CVehicleModelInfo__ms_vehicleColourTable.gta_sa->blue);	// mov     cl, ds:_ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[esi*4]	; sub_4C8220
			CPatch::PatchPointer(0x5817C9 + 3, CVehicleModelInfo__ms_vehicleColourTable.gta_sa);	// mov     edi, dword ptr ds:_ZN17CVehicleModelInfo21ms_vehicleColourTableE.red[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_5816E0
			CPatch::PatchPointer(0x582173 + 3, CVehicleModelInfo__ms_vehicleColourTable.gta_sa);	// mov     eax, dword ptr ds:_ZN17CVehicleModelInfo21ms_vehicleColourTableE.red[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_5820E0
			CPatch::PatchPointer(0x5B68D4 + 4, &CVehicleModelInfo__ms_vehicleColourTable.gta_sa->green);	// mov     [esp+4E4h+var_4D4], offset _ZN17CVehicleModelInfo21ms_vehicleColourTableE.green	; sub_5B6890
			CPatch::PatchPointer(0x6A6FF7 + 3, CVehicleModelInfo__ms_vehicleColourTable.gta_sa);	// mov     ecx, dword ptr ds:_ZN17CVehicleModelInfo21ms_vehicleColourTableE.red[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_6A6DC0
		}
		#endif

		this->bIsVehicleColorIDextended = iVehicleColors > 0xFF;

		if (this->bIsVehicleColorIDextended)
		{
			CPatch::RedirectMethod(0x4C84B0, &CVehicleModelInfo_x36324::CVehicleModelInfo__SetVehicleColour);
			CPatch::RedirectCode(0x44B104, &patch_CGarage__Update_44B104);

			// CRunningScript::ProcessCommands2500To2599
			{
				CPatch::PatchUINT8(0x47B914, 0x8B);	// mov full register
				CPatch::PatchUINT8(0x47B920, 0x8B);	// mov full register
			}

			// CMenuSystem::GetCarColourFromGrid
			CPatch::RedirectCode(0x5822C1, &patch_CMenuSystem__GetCarColourFromGrid_5822C1);

			// CRunningScript::ProcessCommands500To599
			{
				CPatch::PatchUINT8(0x47EAB2, 0x8B);	// mov full register
				CPatch::PatchUINT8(0x47EABE, 0x8B);	// mov full register
			}

			// references to CVehicleModelInfo::ChooseVehicleColour	
			{
				void* ChooseVehicleColourFindReplacementPtrs = GetMethodAsVoidPointer(&CVehicleModelInfo_x36324::ChooseVehicleColourFindReplacementPtrs);

				// CCarCtrl::GenerateOneRandomCar
				CPatch::PutCallFunction(0x431BE0, ChooseVehicleColourFindReplacementPtrs);

				// CAutomobile::CAutomobile
				CPatch::PutCallFunction(0x6B0C2E, ChooseVehicleColourFindReplacementPtrs);

				// CBike::CBike
				CPatch::PutCallFunction(0x6BF587, ChooseVehicleColourFindReplacementPtrs);

				// CBoat::CBoat
				CPatch::PutCallFunction(0x6F2A88, ChooseVehicleColourFindReplacementPtrs);

				// CTrain::CTrain
				CPatch::PutCallFunction(0x6F6212, ChooseVehicleColourFindReplacementPtrs);
			}			

			// Automatic patch
			tVariableValue variable;
			variable.Array.pItems = VehicleColorIDpatches::ptrArray;
			variable.Array.count = _countof(VehicleColorIDpatches::ptrArray);
			CCodeMover::SetVariable("PATCH_PTR_ARRAY", variable);

			#if TRUE
			{
				// Count of active addresses: 158
				CCodeMover::FixOnAddressRel(
					bIsHOODLUM ? 0x406000 : 0x4C84BD,
					6,
					"\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x00\x60\x40\x00\x08\x00",
					0x4C84C3);	// line 1, 0x4C84B0 - sub_4C84B0 : mov     ds:TertiaryColor, bl

				CCodeMover::FixOnAddressRel(0x43088C, 14, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x8C\x08\x43\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x93\x08\x43\x00\x08\x00", 0x43089A);	// line 2, 0x403AEE - sub_403AEE : mov     byte ptr [esi+434h], 0
				CCodeMover::FixOnAddressRel(0x4482A2, 27, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xA2\x82\x44\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xA5\x82\x44\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xAB\x82\x44\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xAE\x82\x44\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xB4\x82\x44\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xB7\x82\x44\x00\x08\x00", 0x4482BD);	// line 3, 0x447E40 - sub_447E40 : mov     cl, [edi+32h]
				CCodeMover::FixOnAddressRel(0x4482C3, 5, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xC3\x82\x44\x00\x13\x02\xC6\x82\x04\x00\x00", 0x4482C8);	// line 4, 0x447E40 - sub_447E40 : mov     cl, [edi+35h]
				CCodeMover::FixOnAddressRel(0x4482CF, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xCF\x82\x44\x00\x08\x00", 0x4482D5);	// line 5, 0x447E40 - sub_447E40 : mov     [esi+437h], cl
				CCodeMover::FixOnAddressRel(0x4497EA, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xEA\x97\x44\x00\x08\x00", 0x4497F0);	// line 6, 0x449760 - sub_449760 : mov     cl, [esi+434h]
				CCodeMover::FixOnAddressRel(0x4497F3, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xF3\x97\x44\x00\x08\x00", 0x4497F9);	// line 7, 0x449760 - sub_449760 : mov     dl, [esi+435h]
				CCodeMover::FixOnAddressRel(0x4497FC, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xFC\x97\x44\x00\x08\x00", 0x449802);	// line 8, 0x449760 - sub_449760 : mov     al, [esi+436h]
				CCodeMover::FixOnAddressRel(0x449805, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x05\x98\x44\x00\x08\x00", 0x44980B);	// line 9, 0x449760 - sub_449760 : mov     cl, [esi+437h]
				CCodeMover::FixOnAddressRel(0x44B1B7, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xB7\xB1\x44\x00\x08\x00", 0x44B1BE);	// line 10, 0x44AA50 - sub_44AA50 : movzx   edx, byte ptr [edi+434h]
				CCodeMover::FixOnAddressRel(0x45B8B1, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xB1\xB8\x45\x00\x08\x00", 0x45B8B7);	// line 11, 0x45B730 - sub_45B730 : mov     cl, [edi+434h]
				CCodeMover::FixOnAddressRel(0x45B8BA, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xBA\xB8\x45\x00\x08\x00", 0x45B8C0);	// line 12, 0x45B730 - sub_45B730 : mov     dl, [edi+435h]
				CCodeMover::FixOnAddressRel(0x45F5B2, 18, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xB2\xF5\x45\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xB5\xF5\x45\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xBB\xF5\x45\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xBE\xF5\x45\x00\x08\x00", 0x45F5C4);	// line 13, 0x45F380 - sub_45F380 : mov     dl, [esi+2Dh]
				CCodeMover::FixOnAddressRel(0x45F6F5, 12, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xF5\xF6\x45\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xF8\xF6\x45\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xFE\xF6\x45\x00\x00", 0x45F701);	// line 14, 0x45F380 - sub_45F380 : mov     cl, [esi+2Dh]
				CCodeMover::FixOnAddressRel(0x45F702, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x02\xF7\x45\x00\x08\x00", 0x45F708);	// line 15, 0x45F380 - sub_45F380 : mov     [edi+435h], dl
				CCodeMover::FixOnAddressRel(0x45F833, 12, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x33\xF8\x45\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x36\xF8\x45\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x3C\xF8\x45\x00\x00", 0x45F83F);	// line 16, 0x45F380 - sub_45F380 : mov     cl, [esi+2Dh]
				CCodeMover::FixOnAddressRel(0x45F840, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x40\xF8\x45\x00\x08\x00", 0x45F846);	// line 17, 0x45F380 - sub_45F380 : mov     [edi+435h], dl
				CCodeMover::FixOnAddressRel(0x45F966, 12, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x66\xF9\x45\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x69\xF9\x45\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x6F\xF9\x45\x00\x00", 0x45F972);	// line 18, 0x45F380 - sub_45F380 : mov     cl, [esi+2Dh]
				CCodeMover::FixOnAddressRel(0x45F973, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x73\xF9\x45\x00\x08\x00", 0x45F979);	// line 19, 0x45F380 - sub_45F380 : mov     [edi+435h], dl
				CCodeMover::FixOnAddressRel(0x45FA99, 12, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x99\xFA\x45\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x9C\xFA\x45\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xA2\xFA\x45\x00\x00", 0x45FAA5);	// line 20, 0x45F380 - sub_45F380 : mov     cl, [esi+2Dh]
				CCodeMover::FixOnAddressRel(0x45FAA6, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xA6\xFA\x45\x00\x08\x00", 0x45FAAC);	// line 21, 0x45F380 - sub_45F380 : mov     [edi+435h], dl
				CCodeMover::FixOnAddressRel(0x45FBE0, 12, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE0\xFB\x45\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE3\xFB\x45\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE9\xFB\x45\x00\x00", 0x45FBEC);	// line 22, 0x45F380 - sub_45F380 : mov     cl, [esi+2Dh]
				CCodeMover::FixOnAddressRel(0x45FBED, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xED\xFB\x45\x00\x08\x00", 0x45FBF3);	// line 23, 0x45F380 - sub_45F380 : mov     [edi+435h], dl
				CCodeMover::FixOnAddressRel(0x47B91A, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x1A\xB9\x47\x00\x08\x00", 0x47B920);	// line 24, 0x47A760 - sub_47A760 : mov     [eax+436h], cl
				CCodeMover::FixOnAddressRel(0x47B926, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x26\xB9\x47\x00\x08\x00", 0x47B92C);	// line 25, 0x47A760 - sub_47A760 : mov     [eax+437h], dl
				CCodeMover::FixOnAddressRel(0x47B94D, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x4D\xB9\x47\x00\x08\x00", 0x47B954);	// line 26, 0x47A760 - sub_47A760 : movzx   ecx, byte ptr [eax+436h]
				CCodeMover::FixOnAddressRel(0x47B95A, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x5A\xB9\x47\x00\x08\x00", 0x47B961);	// line 27, 0x47A760 - sub_47A760 : movzx   edx, byte ptr [eax+437h]
				CCodeMover::FixOnAddressRel(0x47BD68, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x68\xBD\x47\x00\x08\x00", 0x47BD6E);	// line 28, 0x47A760 - sub_47A760 : mov     [esi+434h], al
				CCodeMover::FixOnAddressRel(0x47BD75, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x75\xBD\x47\x00\x08\x00", 0x47BD7B);	// line 29, 0x47A760 - sub_47A760 : mov     [esi+435h], al
				CCodeMover::FixOnAddressRel(0x47EAB8, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xB8\xEA\x47\x00\x08\x00", 0x47EABE);	// line 30, 0x47E090 - sub_47E090 : mov     [eax+434h], cl
				CCodeMover::FixOnAddressRel(0x47EAC4, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xC4\xEA\x47\x00\x08\x00", 0x47EACA);	// line 31, 0x47E090 - sub_47E090 : mov     [eax+435h], dl
				CCodeMover::FixOnAddressRel(0x489659, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x59\x96\x48\x00\x08\x00", 0x489660);	// line 32, 0x489500 - sub_489500 : movzx   ecx, byte ptr [eax+434h]
				CCodeMover::FixOnAddressRel(0x489666, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x66\x96\x48\x00\x08\x00", 0x48966D);	// line 33, 0x489500 - sub_489500 : movzx   edx, byte ptr [eax+435h]
				CCodeMover::FixOnAddressRel(0x4C833F, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x3F\x83\x4C\x00\x08\x00", 0x4C8346);	// line 34, 0x4C8220 - sub_4C8220 : movzx   esi, ds:PrimaryColor
				CCodeMover::FixOnAddressRel(0x4C8350, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x50\x83\x4C\x00\x08\x00", 0x4C8357);	// line 35, 0x4C8220 - sub_4C8220 : movzx   esi, ds:SecondaryColor
				CCodeMover::FixOnAddressRel(0x4C8361, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x61\x83\x4C\x00\x08\x00", 0x4C8368);	// line 36, 0x4C8220 - sub_4C8220 : movzx   esi, ds:TertiaryColor
				CCodeMover::FixOnAddressRel(0x4C8372, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x72\x83\x4C\x00\x08\x00", 0x4C8379);	// line 37, 0x4C8220 - sub_4C8220 : movzx   esi, ds:QuaternaryColor
				CCodeMover::FixOnAddressRel(0x4C8490, 26, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x90\x84\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x92\x84\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x98\x84\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x9E\x84\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xA4\x84\x4C\x00\x08\x00", 0x4C84AA);	// line 38, 0x4C8490 - sub_4C8490 : mov     al, 0FFh
				CCodeMover::FixOnAddressRel(0x4C84C7, 23, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xC7\x84\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xCC\x84\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xD2\x84\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xD8\x84\x4C\x00\x08\x00", 0x4C84DE);	// line 39, 0x4C84B0 - sub_4C84B0 : mov     ds:PrimaryColor, al
				CCodeMover::FixOnAddressRel(0x4C84E2, 18, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE2\x84\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE8\x84\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xEE\x84\x4C\x00\x08\x00", 0x4C84F4);	// line 40, 0x4C84B0 - sub_4C84B0 : mov     [ecx+2D5h], bl
				CCodeMover::FixOnAddressRel(0x4C8537, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x37\x85\x4C\x00\x13\x04\x3A\x85\x0C\x00\x00", 0x4C853E);	// line 41, 0x4C8500 - sub_4C8500 : mov     byte ptr [eax], 7Eh
				CCodeMover::FixOnAddressRel(0x4C853F, 10, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x3F\x85\x4C\x00\x13\x01\x42\x85\x0C\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x43\x85\x4C\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x46\x85\x4C\x00\x00", 0x4C8549);	// line 42, 0x4C8500 - sub_4C8500 : mov     byte ptr [ecx], 7Eh
				CCodeMover::FixOnAddressRel(0x4C8573, 9, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x73\x85\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x7A\x85\x4C\x00\x00", 0x4C857C);	// line 43, 0x4C8500 - sub_4C8500 : mov     al, [edx+esi+2B0h]
				CCodeMover::FixOnAddressRel(0x4C8583, 9, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x83\x85\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x8A\x85\x4C\x00\x00", 0x4C858C);	// line 44, 0x4C8500 - sub_4C8500 : mov     dl, [ecx+esi+2B8h]
				CCodeMover::FixOnAddressRel(0x4C8593, 10, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x93\x85\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x9A\x85\x4C\x00\x00", 0x4C859D);	// line 45, 0x4C8500 - sub_4C8500 : mov     cl, [eax+esi+2C0h]
				CCodeMover::FixOnAddressRel(0x4C85A4, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xA4\x85\x4C\x00\x08\x00", 0x4C85AB);	// line 46, 0x4C8500 - sub_4C8500 : mov     al, [edx+esi+2C8h]
				CCodeMover::FixOnAddressRel(0x4C85AF, 9, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xAF\x85\x4C\x00\x13\x07\xB1\x85\x0C\x00\x00", 0x4C85B8);	// line 47, 0x4C8500 - sub_4C8500 : mov     [ecx], al
				CCodeMover::FixOnAddressRel(0x4C85E3, 8, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE3\x85\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE9\x85\x4C\x00\x00", 0x4C85EB);	// line 48, 0x4C8500 - sub_4C8500 : mov     cl, [eax+434h]
				CCodeMover::FixOnAddressRel(0x4C85F1, 8, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xF1\x85\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xF7\x85\x4C\x00\x00", 0x4C85F9);	// line 49, 0x4C8500 - sub_4C8500 : mov     dl, [eax+435h]
				CCodeMover::FixOnAddressRel(0x4C85FF, 9, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xFF\x85\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x05\x86\x4C\x00\x00", 0x4C8608);	// line 50, 0x4C8500 - sub_4C8500 : mov     cl, [eax+436h]
				CCodeMover::FixOnAddressRel(0x4C860E, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x0E\x86\x4C\x00\x08\x00", 0x4C8614);	// line 51, 0x4C8500 - sub_4C8500 : mov     dl, [eax+437h]
				CCodeMover::FixOnAddressRel(0x4C8618, 11, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x18\x86\x4C\x00\x01\x02\x0F\x85\x15\x9b\x86\x0c\x00\x13\x07\x1C\x86\x0C\x00\x00", 0x4C8623);	// line 52, 0x4C8500 - sub_4C8500 : cmp     dl, [eax]
				CCodeMover::FixOnAddressRel(0x4C863A, 9, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x3A\x86\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x41\x86\x4C\x00\x00", 0x4C8643);	// line 53, 0x4C8500 - sub_4C8500 : mov     al, [edx+esi+2B0h]
				CCodeMover::FixOnAddressRel(0x4C864A, 9, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x4A\x86\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x51\x86\x4C\x00\x00", 0x4C8653);	// line 54, 0x4C8500 - sub_4C8500 : mov     dl, [ecx+esi+2B8h]
				CCodeMover::FixOnAddressRel(0x4C865A, 10, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x5A\x86\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x61\x86\x4C\x00\x00", 0x4C8664);	// line 55, 0x4C8500 - sub_4C8500 : mov     cl, [eax+esi+2C0h]
				CCodeMover::FixOnAddressRel(0x4C866B, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x6B\x86\x4C\x00\x08\x00", 0x4C8672);	// line 56, 0x4C8500 - sub_4C8500 : mov     al, [edx+esi+2C8h]
				CCodeMover::FixOnAddressRel(0x4C8679, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x79\x86\x4C\x00\x13\x01\x7B\x86\x0C\x00\x13\x03\x7C\x86\x0C\x00\x00", 0x4C867F);	// line 57, 0x4C8500 - sub_4C8500 : mov     [ecx], al
				CCodeMover::FixOnAddressRel(0x4C868B, 16, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x8B\x86\x4C\x00\x13\x04\x8E\x86\x0C\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x92\x86\x4C\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x95\x86\x4C\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x98\x86\x4C\x00\x00", 0x4C869B);	// line 58, 0x4C8500 - sub_4C8500 : mov     byte ptr [edx], 0
				CCodeMover::FixOnAddressRel(0x4C9648, 24, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x48\x96\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x4E\x96\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x54\x96\x4C\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x5A\x96\x4C\x00\x08\x00", 0x4C9660);	// line 59, 0x4C95C0 - sub_4C95C0 : mov     [esi+2D2h], al
				CCodeMover::FixOnAddressRel(0x4E74E9, 8, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE9\x74\x4E\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xEF\x74\x4E\x00\x08\x00", 0x4E74F1);	// line 60, 0x4E71E0 - sub_4E71E0 : mov     al, [edi+434h]
				CCodeMover::FixOnAddressRel(0x59F1C3, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xC3\xF1\x59\x00\x08\x00", 0x59F1C9);	// line 61, 0x59F180 - sub_59F180 : mov     al, [esi+14Fh]
				CCodeMover::FixOnAddressRel(0x59F1CB, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xCB\xF1\x59\x00\x08\x00", 0x59F1D1);	// line 62, 0x59F180 - sub_59F180 : mov     dl, [esi+14Eh]
				CCodeMover::FixOnAddressRel(0x59F1D4, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xD4\xF1\x59\x00\x08\x00", 0x59F1DA);	// line 63, 0x59F180 - sub_59F180 : mov     al, [esi+14Dh]
				CCodeMover::FixOnAddressRel(0x59F1DD, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xDD\xF1\x59\x00\x08\x00", 0x59F1E3);	// line 64, 0x59F180 - sub_59F180 : mov     dl, [esi+14Ch]
				CCodeMover::FixOnAddressRel(0x59F973, 14, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x73\xF9\x59\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x7A\xF9\x59\x00\x08\x00", 0x59F981);	// line 65, 0x59F840 - sub_59F840 : mov     byte ptr [esi+14Dh], 0
				CCodeMover::FixOnAddressRel(0x5B6B50, 16, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x50\x6B\x5B\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x53\x6B\x5B\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x56\x6B\x5B\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x58\x6B\x5B\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x5A\x6B\x5B\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x5D\x6B\x5B\x00\x08\x00", 0x5B6B60);	// line 66, 0x5B6890 - sub_5B6890 : mov     dl, [ecx-4]
				CCodeMover::FixOnAddressRel(0x5B6CD8, 22, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xD8\x6C\x5B\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xDB\x6C\x5B\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xDE\x6C\x5B\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE0\x6C\x5B\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE2\x6C\x5B\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE5\x6C\x5B\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE8\x6C\x5B\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xEB\x6C\x5B\x00\x08\x00", 0x5B6CEE);	// line 67, 0x5B6890 - sub_5B6890 : mov     dl, [ecx-4]
				CCodeMover::FixOnAddressRel(0x5D2341, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x41\x23\x5D\x00\x08\x00", 0x5D2347);	// line 68, 0x5D2330 - sub_5D2330 : mov     cl, [edi+434h]
				CCodeMover::FixOnAddressRel(0x5D234A, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x4A\x23\x5D\x00\x08\x00", 0x5D2350);	// line 69, 0x5D2330 - sub_5D2330 : mov     dl, [edi+435h]
				CCodeMover::FixOnAddressRel(0x5D2353, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x53\x23\x5D\x00\x08\x00", 0x5D2359);	// line 70, 0x5D2330 - sub_5D2330 : mov     al, [edi+436h]
				CCodeMover::FixOnAddressRel(0x5D235C, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x5C\x23\x5D\x00\x08\x00", 0x5D2362);	// line 71, 0x5D2330 - sub_5D2330 : mov     cl, [edi+437h]
				CCodeMover::FixOnAddressRel(0x5D23C0, 36, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xC0\x23\x5D\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xC3\x23\x5D\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xC9\x23\x5D\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xCC\x23\x5D\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xD2\x23\x5D\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xD5\x23\x5D\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xDB\x23\x5D\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xDE\x23\x5D\x00\x08\x00", 0x5D23E4);	// line 72, 0x5D23B0 - sub_5D23B0 : mov     al, [esi+49h]
				CCodeMover::FixOnAddressRel(0x6A6FF0, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xF0\x6F\x6A\x00\x08\x00", 0x6A6FF7);	// line 73, 0x6A6DC0 - sub_6A6DC0 : movzx   eax, byte ptr [edi+434h]
				CCodeMover::FixOnAddressRel(0x6A880B, 24, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x0B\x88\x6A\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x11\x88\x6A\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x17\x88\x6A\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x1D\x88\x6A\x00\x08\x00", 0x6A8823);	// line 74, 0x406044 - sub_406044 : mov     cl, [ebx+434h]
				CCodeMover::FixOnAddressRel(0x6C441D, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x1D\x44\x6C\x00\x08\x00", 0x6C4423);	// line 75, 0x6C4400 - sub_6C4400 : mov     al, [esi+437h]
				CCodeMover::FixOnAddressRel(0x6C442B, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x2B\x44\x6C\x00\x08\x00", 0x6C4431);	// line 76, 0x6C4400 - sub_6C4400 : mov     dl, [esi+436h]
				CCodeMover::FixOnAddressRel(0x6C4435, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x35\x44\x6C\x00\x08\x00", 0x6C443B);	// line 77, 0x6C4400 - sub_6C4400 : mov     al, [esi+435h]
				CCodeMover::FixOnAddressRel(0x6C443E, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x3E\x44\x6C\x00\x08\x00", 0x6C4444);	// line 78, 0x6C4400 - sub_6C4400 : mov     dl, [esi+434h]
				CCodeMover::FixOnAddressRel(0x6D65C9, 7, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xC9\x65\x6D\x00\x08\x00", 0x6D65D0);	// line 79, 0x6D64F0 - sub_6D64F0 : mov     byte ptr [esi+434h], 1
				CCodeMover::FixOnAddressRel(0x6D65ED, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xED\x65\x6D\x00\x08\x00", 0x6D65F3);	// line 80, 0x6D64F0 - sub_6D64F0 : mov     dl, [esi+437h]
				CCodeMover::FixOnAddressRel(0x6D65F5, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xF5\x65\x6D\x00\x08\x00", 0x6D65FB);	// line 81, 0x6D64F0 - sub_6D64F0 : mov     al, [esi+436h]
				CCodeMover::FixOnAddressRel(0x6D65FD, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xFD\x65\x6D\x00\x08\x00", 0x6D6603);	// line 82, 0x6D64F0 - sub_6D64F0 : mov     cl, [esi+435h]
				CCodeMover::FixOnAddressRel(0x6D6606, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\x06\x66\x6D\x00\x08\x00", 0x6D660C);	// line 83, 0x6D64F0 - sub_6D64F0 : mov     dl, [esi+434h]
				CCodeMover::FixOnAddressRel(0x6F3DB6, 5, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xB6\x3D\x6F\x00\x13\x02\xB9\x3D\x2F\x00\x00", 0x6F3DBB);	// line 84, 0x6F34D0 - _ZN13CCarGenerator20DoInternalProcessingEv : mov     al, [edi+2]
				CCodeMover::FixOnAddressRel(0x6F3DC3, 15, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xC3\x3D\x6F\x00\x08\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xC9\x3D\x6F\x00\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xCC\x3D\x6F\x00\x08\x00", 0x6F3DD2);	// line 85, 0x6F34D0 - _ZN13CCarGenerator20DoInternalProcessingEv : mov     [esi+434h], al
				CCodeMover::FixOnAddressRel(0x6F3DDA, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xDA\x3D\x6F\x00\x08\x00", 0x6F3DE0);	// line 86, 0x6F34D0 - _ZN13CCarGenerator20DoInternalProcessingEv : mov     al, [esi+434h]
				CCodeMover::FixOnAddressRel(0x6F3DE3, 6, "\x01\x01\xe8\x0B\x04""PATCH_PTR_ARRAY\x00\xE3\x3D\x6F\x00\x08\x00", 0x6F3DE9);	// line 87, 0x6F34D0 - _ZN13CCarGenerator20DoInternalProcessingEv : mov     cl, [esi+435h]
			}
			#endif

			CCodeMover::DeleteVariable("PATCH_PTR_ARRAY");

			CGenericLogStorage::SaveFormattedTextLn(
				"Vehicle colours limit is over 255 and requires something more than uint8_t."
				" Applying colour ID uint32_t patches."
			);
		}
	}
	else if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86
		|| gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
	{
		if (iVehicleColors > this->ms_iVehicleColorsLimit)
		{
			CVehicleModelInfo__ms_vehicleColourTable.gta_iv = new CBGRA[iVehicleColors];
			CVehicleModelInfo__ms_vehicleColourTable.bIsAllocated.Set(true);

			CVehicleModelInfo__ms_policeScannerPrefixTable.ptr = new uint32_t[iVehicleColors];
			CVehicleModelInfo__ms_policeScannerPrefixTable.bIsAllocated.Set(true);

			CVehicleModelInfo__ms_policeScannerColourTable.ptr = new uint32_t[iVehicleColors];
			CVehicleModelInfo__ms_policeScannerColourTable.bIsAllocated.Set(true);
		}

		if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86)
		{
			// Patch references to CVehicleModelInfo::ms_vehicleColourTable
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x92FF15 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_92FE90
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9323C0 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_9322C0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9336F4 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_9335D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x95303B + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_952EF0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x99548B + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_995350
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA6E12D + 2), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, ss:_ZN17CVehicleModelInfo21ms_vehicleColourTableE[ebp]; CVehicleModelInfo::ms_vehicleColourTable	; sub_A6DF00
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA6E164 + 2), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     ss:_ZN17CVehicleModelInfo21ms_vehicleColourTableE[ebp], edx; CVehicleModelInfo::ms_vehicleColourTable	; sub_A6DF00
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA6E16A + 2), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// or      ss:_ZN17CVehicleModelInfo21ms_vehicleColourTableE[ebp], 0FF000000h; CVehicleModelInfo::ms_vehicleColourTable	; sub_A6DF00
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBAF97 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_BBAEF0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBBD33 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_BBBC20
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBFEE8 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_BBFEA0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBFEEF + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     ecx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_BBFEA0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBFF01 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_BBFEA0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBBFF13 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_BBFEA0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC008A + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_BBFEA0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC0098 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     ecx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_BBFEA0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC00AA + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_BBFEA0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBC00BC + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_BBFEA0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBE2F7D + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_BE2DD0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCDB169 + 1), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edi, offset _ZN17CVehicleModelInfo21ms_vehicleColourTableE; CVehicleModelInfo::ms_vehicleColourTable	; sub_CDB160
			}
			#endif

			// Patch pointers to CVehicleModelInfo::ms_policeScannerPrefixTable
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA6E1C2 + 2), CVehicleModelInfo__ms_policeScannerPrefixTable.ptr);	// mov     ss:_ZN17CVehicleModelInfo27ms_policeScannerPrefixTableE[ebp], eax; CVehicleModelInfo::ms_policeScannerPrefixTable	; sub_A6DF00
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA6E1CA + 2), CVehicleModelInfo__ms_policeScannerPrefixTable.ptr);	// mov     ss:_ZN17CVehicleModelInfo27ms_policeScannerPrefixTableE[ebp], ebx; CVehicleModelInfo::ms_policeScannerPrefixTable	; sub_A6DF00
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA807B2 + 3), CVehicleModelInfo__ms_policeScannerPrefixTable.ptr);	// mov     ecx, _ZN17CVehicleModelInfo27ms_policeScannerPrefixTableE[eax*4]; CVehicleModelInfo::ms_policeScannerPrefixTable	; sub_A807A0
			}
			#endif

			// Patch pointers to CVehicleModelInfo::ms_policeScannerColourTable
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA6E20A + 2), CVehicleModelInfo__ms_policeScannerColourTable.ptr);	// mov     ss:_ZN17CVehicleModelInfo27ms_policeScannerColourTableE[ebp], eax; CVehicleModelInfo::ms_policeScannerColourTable	; sub_A6DF00
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA6E218 + 2), CVehicleModelInfo__ms_policeScannerColourTable.ptr);	// mov     ss:_ZN17CVehicleModelInfo27ms_policeScannerColourTableE[ebp], ebx; CVehicleModelInfo::ms_policeScannerColourTable	; sub_A6DF00
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA807BB + 3), CVehicleModelInfo__ms_policeScannerColourTable.ptr);	// mov     edx, _ZN17CVehicleModelInfo27ms_policeScannerColourTableE[eax*4]; CVehicleModelInfo::ms_policeScannerColourTable	; sub_A807A0
			}
			#endif

			// Patch values
			#if TRUE
			{
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xCDB161 + 1), iVehicleColors);	// mov     ecx, 196	; sub_D45880
			}
			#endif
		}
		else if(gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
		{
			// Patch references to CVehicleModelInfo::ms_vehicleColourTable
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x92E1DB + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_92E0A0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB0E845 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B0E7C0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB10DC0 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B10CC0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB12174 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B12050
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB1D9CB + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B1D880
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBE71D3 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[esi+esi]; CVehicleModelInfo::ms_vehicleColourTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBE720D + 2), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     _ZN17CVehicleModelInfo21ms_vehicleColourTableE[esi], edx; CVehicleModelInfo::ms_vehicleColourTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBE7213 + 2), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// or      _ZN17CVehicleModelInfo21ms_vehicleColourTableE[esi], 0FF000000h; CVehicleModelInfo::ms_vehicleColourTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xC4AE1D + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_C4AC70
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xC7B6C7 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_C7B620
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xC7C463 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_C7C350
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCBA668 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CBA620
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCBA66F + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     ecx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CBA620
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCBA681 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CBA620
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCBA693 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CBA620
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCBA80A + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CBA620
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCBA818 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     ecx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CBA620
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCBA82A + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CBA620
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCBA83C + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CBA620
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD45889 + 1), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edi, offset _ZN17CVehicleModelInfo21ms_vehicleColourTableE; CVehicleModelInfo::ms_vehicleColourTable	; sub_D45880
			}
			#endif

			// Patch pointers to CVehicleModelInfo::ms_policeScannerPrefixTable
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA433F2 + 3), CVehicleModelInfo__ms_policeScannerPrefixTable.ptr);	// mov     ecx, _ZN17CVehicleModelInfo27ms_policeScannerPrefixTableE[eax*4]; CVehicleModelInfo::ms_policeScannerPrefixTable	; sub_A433E0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBE7270 + 2), CVehicleModelInfo__ms_policeScannerPrefixTable.ptr);	// mov     _ZN17CVehicleModelInfo27ms_policeScannerPrefixTableE[esi], eax; CVehicleModelInfo::ms_policeScannerPrefixTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBE7278 + 2), CVehicleModelInfo__ms_policeScannerPrefixTable.ptr);	// mov     _ZN17CVehicleModelInfo27ms_policeScannerPrefixTableE[esi], ebx; CVehicleModelInfo::ms_policeScannerPrefixTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
			}
			#endif

			// Patch pointers to CVehicleModelInfo::ms_policeScannerColourTable
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA433FB + 3), CVehicleModelInfo__ms_policeScannerColourTable.ptr);	// mov     edx, _ZN17CVehicleModelInfo27ms_policeScannerColourTableE[eax*4]; CVehicleModelInfo::ms_policeScannerColourTable	; sub_A433E0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBE72BE + 3), CVehicleModelInfo__ms_policeScannerColourTable.ptr);	// mov     _ZN17CVehicleModelInfo27ms_policeScannerColourTableE[ecx*4], eax; CVehicleModelInfo::ms_policeScannerColourTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBE72C7 + 2), CVehicleModelInfo__ms_policeScannerColourTable.ptr);	// mov     _ZN17CVehicleModelInfo27ms_policeScannerColourTableE[esi], ebx; CVehicleModelInfo::ms_policeScannerColourTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
			}
			#endif

			// Patch values
			#if TRUE
			{
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xBE7179 + 6), iVehicleColors);	// cmp     numberOfCarColours, 196	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xBE72CD + 6), iVehicleColors-1);	// cmp     numberOfCarColours, 195	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD45881 + 1), iVehicleColors);	// mov     ecx, 196	; sub_D45880
			}
			#endif
		}
		else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
		{
			// Patch references to CVehicleModelInfo::ms_vehicleColourTable
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9E9C25 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_9E9BA0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9EC170 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_9EC070
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9ED594 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_9ED470
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA01A5B + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_A01910
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA46C13 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[esi+esi]; CVehicleModelInfo::ms_vehicleColourTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA46C4D + 2), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[esi], edx; CVehicleModelInfo::ms_vehicleColourTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA46C53 + 2), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// or      dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[esi], 0FF000000h; CVehicleModelInfo::ms_vehicleColourTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAAC29B + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_AAC160
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAB81F7 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_AB8150
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xAB8F93 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_AB8E80
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB977F8 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B977B0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB977FF + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     ecx, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B977B0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB97811 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B977B0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB97823 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B977B0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB9799A + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B977B0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB979A8 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     ecx, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B977B0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB979BA + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B977B0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB979CC + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B977B0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xC8BD8D + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, dword ptr _ZN17CVehicleModelInfo21ms_vehicleColourTableE.blue[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_C8BBE0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD61FB9 + 1), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edi, offset _ZN17CVehicleModelInfo21ms_vehicleColourTableE; CVehicleModelInfo::ms_vehicleColourTable	; sub_D61FB0
			}
			#endif

			// Patch pointers to CVehicleModelInfo::ms_policeScannerPrefixTable
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7FCE82 + 3), CVehicleModelInfo__ms_policeScannerPrefixTable.ptr);	// mov     ecx, _ZN17CVehicleModelInfo27ms_policeScannerPrefixTableE[eax*4]; CVehicleModelInfo::ms_policeScannerPrefixTable	; sub_7FCE70
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA46CB0 + 2), CVehicleModelInfo__ms_policeScannerPrefixTable.ptr);	// mov     _ZN17CVehicleModelInfo27ms_policeScannerPrefixTableE[esi], eax; CVehicleModelInfo::ms_policeScannerPrefixTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA46CB8 + 2), CVehicleModelInfo__ms_policeScannerPrefixTable.ptr);	// mov     _ZN17CVehicleModelInfo27ms_policeScannerPrefixTableE[esi], ebx; CVehicleModelInfo::ms_policeScannerPrefixTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
			}
			#endif

			// Patch pointers to CVehicleModelInfo::ms_policeScannerColourTable
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x7FCE8B + 3), CVehicleModelInfo__ms_policeScannerColourTable.ptr);	// mov     edx, _ZN17CVehicleModelInfo27ms_policeScannerColourTableE[eax*4]; CVehicleModelInfo::ms_policeScannerColourTable	; sub_7FCE70
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA46CFE + 3), CVehicleModelInfo__ms_policeScannerColourTable.ptr);	// mov     _ZN17CVehicleModelInfo27ms_policeScannerColourTableE[ecx*4], eax; CVehicleModelInfo::ms_policeScannerColourTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA46D07 + 2), CVehicleModelInfo__ms_policeScannerColourTable.ptr);	// mov     _ZN17CVehicleModelInfo27ms_policeScannerColourTableE[esi], ebx; CVehicleModelInfo::ms_policeScannerColourTable	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
			}
			#endif

			// Patch values
			#if TRUE
			{
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xA46BB9 + 6), iVehicleColors);	// cmp     numberOfCarColours, 196	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xA46D0D + 6), iVehicleColors-1);	// cmp     numberOfCarColours, 195	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD61FB1 + 1), iVehicleColors);	// mov     ecx, 196	; sub_D45880
			}
			#endif
		}
		else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
		{
			// Patch references to CVehicleModelInfo::ms_vehicleColourTable
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x9797FB + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_9796C0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB35557 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B354B0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB362F3 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B361E0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB504F3 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[esi+esi]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B502D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB5052D + 2), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     _ZN17CVehicleModelInfo21ms_vehicleColourTableE[esi], edx; CVehicleModelInfo::ms_vehicleColourTable	; sub_B502D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB50533 + 2), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// or      _ZN17CVehicleModelInfo21ms_vehicleColourTableE[esi], 0FF000000h; CVehicleModelInfo::ms_vehicleColourTable	; sub_B502D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB9BDD5 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B9BD50
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB9E310 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B9E210
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB9F6C4 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_B9F5A0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xBAAD4B + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_BAAC00
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCA16FD + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CA1550
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCE1B78 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CE1B30
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCE1B7F + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     ecx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CE1B30
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCE1B91 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CE1B30
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCE1BA3 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CE1B30
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCE1D1A + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CE1B30
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCE1D28 + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     ecx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[eax*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CE1B30
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCE1D3A + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     eax, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[edx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CE1B30
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xCE1D4C + 3), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edx, _ZN17CVehicleModelInfo21ms_vehicleColourTableE[ecx*4]; CVehicleModelInfo::ms_vehicleColourTable	; sub_CE1B30
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xD40199 + 1), CVehicleModelInfo__ms_vehicleColourTable.gta_iv);	// mov     edi, offset _ZN17CVehicleModelInfo21ms_vehicleColourTableE; CVehicleModelInfo::ms_vehicleColourTable	; sub_D40190
			}
			#endif

			// Patch pointers to CVehicleModelInfo::ms_policeScannerPrefixTable
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA6F5B2 + 3), CVehicleModelInfo__ms_policeScannerPrefixTable.ptr);	// mov     ecx, _ZN17CVehicleModelInfo27ms_policeScannerPrefixTableE[eax*4]; CVehicleModelInfo::ms_policeScannerPrefixTable	; sub_A6F5A0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB50590 + 2), CVehicleModelInfo__ms_policeScannerPrefixTable.ptr);	// mov     _ZN17CVehicleModelInfo27ms_policeScannerPrefixTableE[esi], eax; CVehicleModelInfo::ms_policeScannerPrefixTable	; sub_B502D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB50598 + 2), CVehicleModelInfo__ms_policeScannerPrefixTable.ptr);	// mov     _ZN17CVehicleModelInfo27ms_policeScannerPrefixTableE[esi], ebx; CVehicleModelInfo::ms_policeScannerPrefixTable	; sub_B502D0
			}
			#endif

			// Patch pointers to CVehicleModelInfo::ms_policeScannerColourTable
			#if TRUE
			{
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xA6F5BB + 3), CVehicleModelInfo__ms_policeScannerColourTable.ptr);	// mov     edx, _ZN17CVehicleModelInfo27ms_policeScannerColourTableE[eax*4]; CVehicleModelInfo::ms_policeScannerColourTable	; sub_A6F5A0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB505DE + 3), CVehicleModelInfo__ms_policeScannerColourTable.ptr);	// mov     _ZN17CVehicleModelInfo27ms_policeScannerColourTableE[ecx*4], eax; CVehicleModelInfo::ms_policeScannerColourTable	; sub_B502D0
				CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0xB505E7 + 2), CVehicleModelInfo__ms_policeScannerColourTable.ptr);	// mov     _ZN17CVehicleModelInfo27ms_policeScannerColourTableE[esi], ebx; CVehicleModelInfo::ms_policeScannerColourTable	; sub_B502D0
			}
			#endif

			// Patch values
			#if TRUE
			{
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xB50499 + 6), iVehicleColors);	// cmp     numberOfCarColours, 196	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xB505ED + 6), iVehicleColors - 1);	// cmp     numberOfCarColours, 195	; _ZN17CVehicleModelInfo18LoadVehicleColoursEv
				CPatch::PatchUINT32(g_mCalc.GetCurrentVAbyPreferedVA(0xD40191 + 1), iVehicleColors);	// mov     ecx, 196	; sub_D45880
			}
			#endif
		}
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_iVehicleColorsLimit = iVehicleColors;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of OTHER LIMITS: Vehicle colors to: %d",
		iVehicleColors
		);
	CGenericLogStorage::WriteLineSeparator();
}

unsigned int ReferencesLimit;

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
namespace Game_GTASA_2_0
{
	// patch for 0x40E7D4
	extern "C"
	{
		uintptr_t Address_GTA_SA_2_00_CReferences__Init_40E7DE_thumb = 0;	// loc_40E7DE
	}

	static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CReferences__Init_40E7D4()
	{
		__asm(
		".thumb\n"
			"LDR R1, [R1]\n"
			"STR R1, [R0]\n"
			"ADDS R0, R1, #4\n"
			ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R1, ReferencesLimit)
			
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CReferences__Init_40E7DE_thumb)
			);
	}
}
#endif

// Sets the max number of references
void OtherLimits::SetReferences(int iNumberOfReferences)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iNumberOfReferences = this->ms_iReferencesLimit;

	MAKE_DEAD_IF();
	
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if (iNumberOfReferences > this->ms_iReferencesLimit)
		{
			CReferences__aRefs.gta_sa = new CReference[iNumberOfReferences];
			CReferences__aRefs.bIsAllocated.Set(true);
		}
	
		MAKE_DEAD_IF();
		#ifdef IS_PLATFORM_WIN_X86
		else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			// Patch
			#if TRUE
			{
				CPatch::PatchPointer(0x5719B0 + 1, CReferences__aRefs.gta_sa);	// mov     eax, offset _ZN11CReferences5aRefsE ; CReferences::aRefs
				CPatch::PatchUINT32(0x5719BA + 1, iNumberOfReferences);	// mov     edx, 3000
				CPatch::PatchPointer(0x5719D1 + 2, CReferences__aRefs.gta_sa + iNumberOfReferences - 1);	// mov     _ZN11CReferences5aRefsE.m_pNext+5DB8h, 0
			}
			#endif
		}
		#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
		else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		{
			using namespace Game_GTASA_2_0;

			::ReferencesLimit = iNumberOfReferences;

			// Patch pointers
			#if TRUE
			{
					CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x679020), CReferences__aRefs.gta_sa);	// DCD _ZN11CReferences5aRefsE; CReferences::aRefs
			}
			#endif

			Address_GTA_SA_2_00_CReferences__Init_40E7DE_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x40E7DE));
			CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x40E7D4),
				(void*)&patch_GTA_SA_2_00_CReferences__Init_40E7D4
			);
		}
		#endif
	}
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_iReferencesLimit = iNumberOfReferences;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of OTHER LIMITS: References to: %d",
		iNumberOfReferences
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets the cover points
void OtherLimits::SetCoverPoints(int iCoverPoints)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iCoverPoints = this->ms_iCoverPointLimit;

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86	
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (iCoverPoints > this->ms_iCoverPointLimit)
		{
			CCover__m_aPoints.gta_sa = new CCoverPoint[iCoverPoints];
			CCover__m_aPoints.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x698724 + 1, CCover__m_aPoints.gta_sa);	// mov     eax, offset _ZN6CCover9m_aPointsE; CCover::m_aPoints	; sub_698710
			CPatch::PatchPointer(0x698736 + 1, CCover__m_aPoints.gta_sa + iCoverPoints);	// cmp     eax, offset _ZN6CCover26m_ListOfProcessedBuildingsE; CCover::m_ListOfProcessedBuildings	; sub_698710
			CPatch::PatchPointer(0x698746 + 1, (char*)CCover__m_aPoints.gta_sa + 0x10);	// mov     esi, (offset _ZN6CCover9m_aPointsE.gap+10h)	; sub_698740
			CPatch::PatchPointer(0x69877F + 2, (char*)(CCover__m_aPoints.gta_sa + iCoverPoints) + 0x10);	// cmp     esi, offset unk_C1A2C8	; sub_698740
			CPatch::PatchPointer(0x698F4C + 1, (char*)CCover__m_aPoints.gta_sa +0xC);	// mov     edx, (offset _ZN6CCover9m_aPointsE.gap+0Ch)	; sub_698F30
			CPatch::PatchPointer(0x69906B + 2, (char*)(CCover__m_aPoints.gta_sa + iCoverPoints) + 0xC);	// cmp     edx, offset unk_C1A2C4	; sub_698F30
			CPatch::PatchPointer(0x699077 + 1, CCover__m_aPoints.gta_sa);	// mov     al, ds:_ZN6CCover9m_aPointsE.gap; CCover::m_aPoints	; sub_698F30
			CPatch::PatchPointer(0x699082 + 1, CCover__m_aPoints.gta_sa);	// mov     eax, offset _ZN6CCover9m_aPointsE; CCover::m_aPoints	; sub_698F30
			CPatch::PatchPointer(0x6990A1 + 2, CCover__m_aPoints.gta_sa);	// mov     byte ptr ds:_ZN6CCover9m_aPointsE.gap[esi], cl; CCover::m_aPoints	; sub_698F30
			CPatch::PatchPointer(0x6990A7 + 2, (char*)CCover__m_aPoints.gta_sa +2);	// mov     ds:(_ZN6CCover9m_aPointsE.gap+2)[esi], dl	; sub_698F30
			CPatch::PatchPointer(0x6990B3 + 2, (char*)CCover__m_aPoints.gta_sa +1);	// mov     ds:(_ZN6CCover9m_aPointsE.gap+1)[esi], al	; sub_698F30
			CPatch::PatchPointer(0x6990BB + 2, (char*)CCover__m_aPoints.gta_sa +0x14);	// mov     dword ptr ds:(_ZN6CCover9m_aPointsE.gap+14h)[esi], ecx	; sub_698F30
			CPatch::PatchPointer(0x6990C4 + 2, (char*)CCover__m_aPoints.gta_sa +0x10);	// lea     eax, (_ZN6CCover9m_aPointsE.gap+10h)[esi]	; sub_698F30
			CPatch::PatchPointer(0x6990CA + 2, (char*)CCover__m_aPoints.gta_sa +0x18);	// mov     dword ptr ds:(_ZN6CCover9m_aPointsE.gap+18h)[esi], ecx	; sub_698F30
			CPatch::PatchPointer(0x6990FB + 2, (char*)CCover__m_aPoints.gta_sa +4);	// lea     eax, (_ZN6CCover9m_aPointsE.gap+4)[esi]	; sub_698F30
			CPatch::PatchPointer(0x6992D2 + 1, (char*)CCover__m_aPoints.gta_sa +0x14);	// mov     esi, (offset _ZN6CCover9m_aPointsE.gap+14h)	; sub_6992B0
			CPatch::PatchPointer(0x6994FE + 2, (char*)(CCover__m_aPoints.gta_sa + iCoverPoints) + 0x14);	// cmp     esi, offset unk_C1A2CC	; sub_6992B0
			CPatch::PatchPointer(0x69951C + 2, CCover__m_aPoints.gta_sa);	// lea     edi, _ZN6CCover9m_aPointsE.gap[edi]; CCover::m_aPoints	; sub_6992B0
			CPatch::PatchPointer(0x6997FA + 1, CCover__m_aPoints.gta_sa);	// mov     esi, offset _ZN6CCover9m_aPointsE; CCover::m_aPoints	; sub_6997E0
			CPatch::PatchPointer(0x699895 + 2, CCover__m_aPoints.gta_sa + iCoverPoints);	// cmp     esi, offset _ZN6CCover26m_ListOfProcessedBuildingsE; CCover::m_ListOfProcessedBuildings	; sub_6997E0
		}
		#endif

		// Define variables for automatic patch
		#if TRUE
		{
			CCodeMover::SetVariable("NUMBER_OF_COVER_POINTS", iCoverPoints);
		}
		#endif

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddress(0x698F38, 9, "\x01\x01\x3d\x05\x04NUMBER_OF_COVER_POINTS\x00\x01\x02\x0F\x8D\x03\x1b\x91\x69\x00\x00", 0x698F41);	// line 1, 0x698F30 - sub_698F30 : cmp     eax, 64h
		}
		#endif

		// Undefine variable of automatic patch
		CCodeMover::DeleteVariable("NUMBER_OF_COVER_POINTS");
	}
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_iCoverPointLimit = iCoverPoints;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of OTHER LIMITS: Cover points to: %d",
		iCoverPoints
		);
	CGenericLogStorage::WriteLineSeparator();
}

namespace Game_GTASA
{
	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
	extern "C"
	{
		uint32_t sizeOf_aCoronas = 0;
		uint32_t maxNumberOfCoronas = 0;
		uintptr_t Address_CCoronas__Init_5A3830;

		// patch for 0x5A2314
		extern "C"
		{
			uintptr_t Address_GTA_SA_2_00_CCoronas__Update_5A2304_thumb = 0;	// loc_5A2304
			uintptr_t Address_GTA_SA_2_00_CCoronas__Update_5A231E_thumb = 0;
		}

		static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCoronas__Update_5A2314()
		{
			__asm(
			".thumb\n"
				ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R4, sizeOf_aCoronas)
				"BNE 1f\n"
				"POP {R8}\n"
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__Update_5A231E_thumb)

				// Branches
				"1:\n"	// loc_5A2304
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__Update_5A2304_thumb)
				);
		}

		// patch for 0x5A2B06
		extern "C"
		{
			uintptr_t Address_GTA_SA_2_00_CCoronas__Render_5A24E2_thumb = 0;	// loc_5A24E2
			uintptr_t Address_GTA_SA_2_00_CCoronas__Render_191554_arm = 0;	// j__ZN7CSprite17FlushSpriteBufferEv
			uintptr_t Address_GTA_SA_2_00_CCoronas__Render_5A2B12_thumb = 0;
		}

		static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCoronas__Render_5A2B06()
		{
			__asm(
			".thumb\n"
				ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R10, maxNumberOfCoronas)
				"BNE 1f\n"
				"BL 2f\n"
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__Render_5A2B12_thumb)

				// Branches
				"1:\n"	// loc_5A24E2
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__Render_5A24E2_thumb)
				"2:\n"	// j__ZN7CSprite17FlushSpriteBufferEv
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__Render_191554_arm)
				);
		}

		// patch for 0x5A2F24
		extern "C"
		{
			uintptr_t Address_GTA_SA_2_00_CCoronas__RenderReflections_5A2CB2_thumb = 0;	// loc_5A2CB2
			uintptr_t Address_GTA_SA_2_00_CCoronas__RenderReflections_5A2F2C_thumb = 0;
		}

		static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCoronas__RenderReflections_5A2F24()
		{
			__asm(
			".thumb\n"
				ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R8, sizeOf_aCoronas)
				"BNE 1f\n"
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__RenderReflections_5A2F2C_thumb)

				// Branches
				"1:\n"	// loc_5A2CB2
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__RenderReflections_5A2CB2_thumb)
				);
		}

		// patch for 0x5A2F76
		extern "C"
		{
			uintptr_t Address_GTA_SA_2_00_CCoronas__RenderReflections_5A2F82_thumb = 0;
		}

		static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCoronas__RenderReflections_5A2F76()
		{
			__asm(
			".thumb\n"
				ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, sizeOf_aCoronas)
				"LDRB R3, [R2,#0x36]\n"
				"AND R3, R3, #0xFB\n"
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__RenderReflections_5A2F82_thumb)
				);
		}

		// patch for 0x5A382A
		extern "C"
		{
			uintptr_t Address_GTA_SA_2_00_CCoronas__Init_5A3826_thumb = 0;	// loc_5A3826
			uintptr_t Address_GTA_SA_2_00_CCoronas__Init_5A3834_thumb = 0;
		}

		static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCoronas__Init_5A382A()
		{
			__asm(
			".thumb\n"
				ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R2, sizeOf_aCoronas)
				"STR R0, [R3,#0xC]\n"
				"BNE 1f\n"
				"LDR R0, =("/* _ZN8CCoronas10NumCoronasE_ptr */"0x676890 - 0x5A383A)\n"
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__Init_5A3834_thumb)

				// Branches
				"1:\n"	// loc_5A3826
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__Init_5A3826_thumb)
				);
		}

		// patch for 0x5A3B5A
		extern "C"
		{
			uintptr_t Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B44_thumb = 0;	// loc_5A3B44
			uintptr_t Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B90_thumb = 0;	// loc_5A3B90
			uintptr_t Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3CE0_thumb = 0;	// loc_5A3CE0
			uintptr_t Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B66_thumb = 0;
		}

		static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B5A()
		{
			__asm(
			".thumb\n"
				ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R3, maxNumberOfCoronas)
				"BCC 1f\n"
				"BNE 2f\n"
				"CMP R1, #0\n"
				"BEQ 3f\n"
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B66_thumb)

				// Branches
				"1:\n"	// loc_5A3B44
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B44_thumb)
				"2:\n"	// loc_5A3B90
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B90_thumb)
				"3:\n"	// loc_5A3CE0
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3CE0_thumb)
				);
		}

		// patch for 0x5A3B82
		extern "C"
		{
			uintptr_t Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B76_thumb = 0;	// loc_5A3B76
			uintptr_t Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3BC8_thumb = 0;	// loc_5A3BC8
			uintptr_t Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B8C_thumb = 0;
		}

		static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B82()
		{
			__asm(
			".thumb\n"
				"UXTH R6, LR\n"
				ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R6, maxNumberOfCoronas)
				"BCC 1f\n"
				"BNE 2f\n"
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B8C_thumb)

				// Branches
				"1:\n"	// loc_5A3B76
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B76_thumb)
				"2:\n"	// loc_5A3BC8
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3BC8_thumb)
				);
		}

		// patch for 0x5A3D94
		extern "C"
		{
			uintptr_t Address_GTA_SA_2_00_CCoronas__UpdateCoronaCoors_5A3D82_thumb = 0;	// loc_5A3D82
			uintptr_t Address_GTA_SA_2_00_CCoronas__UpdateCoronaCoors_5A3D9E_thumb = 0;
		}

		static TARGET_THUMB NAKED void patch_GTA_SA_2_00_CCoronas__UpdateCoronaCoors_5A3D94()
		{
			__asm(
			".thumb\n"
				ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R12, maxNumberOfCoronas)
				"BCC 1f\n"
				"IT EQ\n"
				"POPEQ {R4,R6,R7,PC}\n"
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__UpdateCoronaCoors_5A3D9E_thumb)

				// Branches
				"1:\n"	// loc_5A3D82
				ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_GTA_SA_2_00_CCoronas__UpdateCoronaCoors_5A3D82_thumb)
				);
		}
	}
	#endif
}

// Sets the coronas
void OtherLimits::SetCoronaLimit(int iCoronaLimit)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iCoronaLimit = this->ms_iCoronasLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86	
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (iCoronaLimit > this->ms_iCoronasLimit)
		{
			CCoronas__aCoronas.gta_sa = new CRegisteredCorona[iCoronaLimit];
			CCoronas__aCoronas.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x6FAACE + 1, &CCoronas__aCoronas.gta_sa->m_dwId);	// mov     eax, offset _ZN8CCoronas8aCoronasE.m_dwId	; sub_6FAA70
			CPatch::PatchPointer(0x6FAE9F + 1, CCoronas__aCoronas.gta_sa);	// mov     esi, offset _ZN8CCoronas8aCoronasE; CCoronas::aCoronas	; sub_6FADF0
			CPatch::PatchPointer(0x6FAEB5 + 2, CCoronas__aCoronas.gta_sa + iCoronaLimit);	// cmp     esi, offset dword_C3EF58	; sub_6FADF0
			CPatch::PatchPointer(0x6FAF41 + 1, &CCoronas__aCoronas.gta_sa->m_pAttachedTo);	// mov     edi, offset _ZN8CCoronas8aCoronasE.m_pAttachedTo	; sub_6FAEC0
			CPatch::PatchPointer(0x6FB647 + 1, (char*)&CCoronas__aCoronas.gta_sa->m_flags + 2);	// mov     eax, offset _ZN8CCoronas8aCoronasE._bf36	; sub_6FB630
			CPatch::PatchPointer(0x6FB656 + 1, (char*)&CCoronas__aCoronas.gta_sa[iCoronaLimit].m_flags + 2);	// cmp     eax, (offset dword_C3EF8C+2)	; sub_6FB630
			CPatch::PatchPointer(0x6FB6CE + 1, &CCoronas__aCoronas.gta_sa->m_nFadeState);	// mov     esi, offset _ZN8CCoronas8aCoronasE.m_nFadeState	; sub_6FB630
			CPatch::PatchPointer(0x6FB9B6 + 2, (char*)&CCoronas__aCoronas.gta_sa[iCoronaLimit].m_nFadeState);	// cmp     esi, offset dword_C3EF88	; sub_6FB630
			CPatch::PatchPointer(0x6FC2E6 + 2, &CCoronas__aCoronas.gta_sa->m_dwId);	// cmp     ds:_ZN8CCoronas8aCoronasE.m_dwId[edx], esi	; sub_6FC180
			CPatch::PatchPointer(0x6FC316 + 2, &CCoronas__aCoronas.gta_sa->m_dwId);	// mov     edi, ds:_ZN8CCoronas8aCoronasE.m_dwId[eax]	; sub_6FC180
			CPatch::PatchPointer(0x6FC33F + 2, &CCoronas__aCoronas.gta_sa->m_nFadeState);	// mov     ds:_ZN8CCoronas8aCoronasE.m_nFadeState[ecx], 0	; sub_6FC180
			CPatch::PatchPointer(0x6FC348 + 2, &CCoronas__aCoronas.gta_sa->m_nFadeState);	// mov     ds:_ZN8CCoronas8aCoronasE.m_nFadeState[ecx], 0FFh	; sub_6FC180
			CPatch::PatchPointer(0x6FC34F + 2, (char*)&CCoronas__aCoronas.gta_sa->m_flags);	// or      ds:_ZN8CCoronas8aCoronasE._bf34[ecx], 2	; sub_6FC180
			CPatch::PatchPointer(0x6FC356 + 2, (char*)&CCoronas__aCoronas.gta_sa->m_flags + 2);	// and     ds:_ZN8CCoronas8aCoronasE._bf36[ecx], 0FBh	; sub_6FC180
			CPatch::PatchPointer(0x6FC363 + 2, (char*)&CCoronas__aCoronas.gta_sa->m_flags + 1);	// mov     ds:_ZN8CCoronas8aCoronasE.m_bJustCreated[ecx], dl	; sub_6FC180
			CPatch::PatchPointer(0x6FC369 + 2, &CCoronas__aCoronas.gta_sa->m_dwId);	// mov     ds:_ZN8CCoronas8aCoronasE.m_dwId[ecx], esi	; sub_6FC180
			CPatch::PatchPointer(0x6FC378 + 2, &CCoronas__aCoronas.gta_sa->m_Color.red);	// mov     byte ptr ds:_ZN8CCoronas8aCoronasE.m_Color.red[ecx], al	; sub_6FC180
			CPatch::PatchPointer(0x6FC382 + 2, &CCoronas__aCoronas.gta_sa->m_Color.green);	// mov     ds:_ZN8CCoronas8aCoronasE.m_Color.green[ecx], al	; sub_6FC180
			CPatch::PatchPointer(0x6FC38C + 2, &CCoronas__aCoronas.gta_sa->m_Color.blue);	// mov     ds:_ZN8CCoronas8aCoronasE.m_Color.blue[ecx], al	; sub_6FC180
			CPatch::PatchPointer(0x6FC396 + 2, &CCoronas__aCoronas.gta_sa->m_Color.alpha);	// mov     ds:_ZN8CCoronas8aCoronasE.m_Color.alpha[ecx], al	; sub_6FC180
			CPatch::PatchPointer(0x6FC39F + 2, &CCoronas__aCoronas.gta_sa->m_vPosn);	// lea     eax, _ZN8CCoronas8aCoronasE.m_vPosn.x[ecx]; CCoronas::aCoronas	; sub_6FC180
			CPatch::PatchPointer(0x6FC3B7 + 2, &CCoronas__aCoronas.gta_sa->m_fSize);	// mov     ds:_ZN8CCoronas8aCoronasE.m_fSize[ecx], eax	; sub_6FC180
			CPatch::PatchPointer(0x6FC3C1 + 2, &CCoronas__aCoronas.gta_sa->m_fAngle);	// mov     ds:_ZN8CCoronas8aCoronasE.m_fAngle[ecx], eax	; sub_6FC180
			CPatch::PatchPointer(0x6FC3CB + 2, &CCoronas__aCoronas.gta_sa->m_fFarClip);	// mov     ds:_ZN8CCoronas8aCoronasE.m_fFarClip[ecx], eax	; sub_6FC180
			CPatch::PatchPointer(0x6FC3D5 + 2, &CCoronas__aCoronas.gta_sa->m_pTexture);	// mov     ds:_ZN8CCoronas8aCoronasE.m_pTexture[ecx], eax	; sub_6FC180
			CPatch::PatchPointer(0x6FC3DF + 2, &CCoronas__aCoronas.gta_sa->m_nFlareType);	// mov     ds:_ZN8CCoronas8aCoronasE.m_nFlareType[ecx], al	; sub_6FC180
			CPatch::PatchPointer(0x6FC3E9 + 2, &CCoronas__aCoronas.gta_sa->m_bUsesReflection);	// mov     ds:_ZN8CCoronas8aCoronasE.m_bUsesReflection[ecx], al	; sub_6FC180
			CPatch::PatchPointer(0x6FC3EF + 2, (char*)&CCoronas__aCoronas.gta_sa->m_flags);	// mov     al, ds:_ZN8CCoronas8aCoronasE._bf34[ecx]	; sub_6FC180
			CPatch::PatchPointer(0x6FC3F9 + 2, &CCoronas__aCoronas.gta_sa->m_bRegisteredThisFrame);	// mov     ds:_ZN8CCoronas8aCoronasE.m_bRegisteredThisFrame[ecx], dl	; sub_6FC180
			CPatch::PatchPointer(0x6FC401 + 2, (char*)&CCoronas__aCoronas.gta_sa->m_flags);	// xor     ds:_ZN8CCoronas8aCoronasE._bf34[ecx], al	; sub_6FC180
			CPatch::PatchPointer(0x6FC40B + 2, &CCoronas__aCoronas.gta_sa->m_fNearClip);	// mov     ds:_ZN8CCoronas8aCoronasE.m_fNearClip[ecx], eax	; sub_6FC180
			CPatch::PatchPointer(0x6FC415 + 2, &CCoronas__aCoronas.gta_sa->m_fFadeSpeed);	// mov     ds:_ZN8CCoronas8aCoronasE.m_fFadeSpeed[ecx], eax	; sub_6FC180
			CPatch::PatchPointer(0x6FC430 + 2, (char*)&CCoronas__aCoronas.gta_sa->m_flags + 2);	// mov     dl, ds:_ZN8CCoronas8aCoronasE._bf36[ecx]	; sub_6FC180
			CPatch::PatchPointer(0x6FC448 + 2, (char*)&CCoronas__aCoronas.gta_sa->m_flags + 2);	// mov     ds:_ZN8CCoronas8aCoronasE._bf36[ecx], al	; sub_6FC180
			CPatch::PatchPointer(0x6FC452 + 2, (char*)&CCoronas__aCoronas.gta_sa->m_flags + 2);	// mov     ds:_ZN8CCoronas8aCoronasE._bf36[ecx], al	; sub_6FC180
			CPatch::PatchPointer(0x6FC458 + 2, &CCoronas__aCoronas.gta_sa->m_pAttachedTo);	// lea     eax, _ZN8CCoronas8aCoronasE.m_pAttachedTo[ecx]	; sub_6FC180
			CPatch::PatchPointer(0x6FC476 + 2, &CCoronas__aCoronas.gta_sa->m_nFadeState);	// cmp     ds:_ZN8CCoronas8aCoronasE.m_nFadeState[ecx], 0	; sub_6FC180
			CPatch::PatchPointer(0x6FC494 + 2, &CCoronas__aCoronas.gta_sa->m_dwId);	// mov     ds:_ZN8CCoronas8aCoronasE.m_dwId[ecx], 0	; sub_6FC180
			CPatch::PatchPointer(0x6FC4AA + 2, (char*)&CCoronas__aCoronas.gta_sa->m_flags + 2);	// mov     ds:_ZN8CCoronas8aCoronasE._bf36[ecx], al	; sub_6FC180
			CPatch::PatchPointer(0x6FC4B0 + 2, &CCoronas__aCoronas.gta_sa->m_pAttachedTo);	// mov     ds:_ZN8CCoronas8aCoronasE.m_pAttachedTo[ecx], 0	; sub_6FC180
			CPatch::PatchPointer(0x6FC536 + 2, &CCoronas__aCoronas.gta_sa->m_dwId);	// cmp     ds:_ZN8CCoronas8aCoronasE.m_dwId[esi], edx	; sub_4038C2
			CPatch::PatchPointer(0x6FC553 + 2, &CCoronas__aCoronas.gta_sa->m_vPosn);	// lea     edx, _ZN8CCoronas8aCoronasE.m_vPosn.x[eax]; CCoronas::aCoronas	; sub_4038C2
			CPatch::PatchPointer(0x6FC56B + 2, &CCoronas__aCoronas.gta_sa->m_fAngle);	// mov     ds:_ZN8CCoronas8aCoronasE.m_fAngle[eax], edx	; sub_4038C2
		}
		#endif

		// Patch values
		#if TRUE
		{
			CPatch::PatchUINT32(0x6FAF46 + 4, iCoronaLimit);	// CCoronas::Render
		}
		#endif

		// Define variables for automatic patch
		#if TRUE
		{
			CCodeMover::SetVariable("NUMBER_OF_CORONAS", iCoronaLimit);
		}
		#endif

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 7
			CCodeMover::FixOnAddress(0x6FAAD3, 5, "\x01\x01\xb9\x05\x04NUMBER_OF_CORONAS\x00\x00", 0x6FAAD8);	// line 1, 0x6FAA70 - sub_6FAA70 : mov     ecx, 40h
			CCodeMover::FixOnAddress(0x6FC2EF, 6, "\x01\x03\x66\x81\xf9\x05\x02NUMBER_OF_CORONAS\x00\x01\x02\x0F\x82\x03\xe0\xc2\x6f\x00\x00", 0x6FC2F5);	// line 2, 0x6FC180 - sub_6FC180 : cmp     cx, 40h
			CCodeMover::FixOnAddress(0x6FC2F5, 6, "\x01\x03\x66\x81\xf9\x05\x02NUMBER_OF_CORONAS\x00\x02\x02\xF9\xC2\x6F\x00\x00", 0x6FC2FB);	// line 3, 0x6FC180 - sub_6FC180 : cmp     cx, 40h
			CCodeMover::FixOnAddress(0x6FC321, 6, "\x01\x03\x66\x81\xf9\x05\x02NUMBER_OF_CORONAS\x00\x01\x02\x0F\x82\x03\x10\xc3\x6f\x00\x00", 0x6FC327);	// line 4, 0x6FC180 - sub_6FC180 : cmp     cx, 40h
			CCodeMover::FixOnAddress(0x6FC327, 10, "\x01\x03\x66\x81\xf9\x05\x02NUMBER_OF_CORONAS\x00\x01\x02\x0F\x84\x03\xba\xc4\x6f\x00\x00", 0x6FC331);	// line 5, 0x6FC180 - sub_6FC180 : cmp     cx, 40h
			CCodeMover::FixOnAddress(0x6FC53F, 6, "\x01\x02\x66\x3d\x05\x02NUMBER_OF_CORONAS\x00\x01\x02\x0F\x82\x03\x30\xc5\x6f\x00\x00", 0x6FC545);	// line 6, 0x4038C2 - sub_4038C2 : cmp     ax, 40h
			CCodeMover::FixOnAddress(0x6FC545, 6, "\x01\x02\x66\x3d\x05\x02NUMBER_OF_CORONAS\x00\x01\x02\x0F\x84\x03\x71\xc5\x6f\x00\x00", 0x6FC54B);	// line 7, 0x4038C2 - sub_4038C2 : cmp     ax, 40h
		}
		#endif

		// Delete variables of automatic patch
		#if TRUE
		{
			CCodeMover::DeleteVariable("NUMBER_OF_CORONAS");
		}
		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if(gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if (iCoronaLimit > this->ms_iCoronasLimit)
		{
			CCoronas__aCoronas.gta_sa = new CRegisteredCorona[iCoronaLimit];
			CCoronas__aCoronas.bIsAllocated.Set(true);
		}

		maxNumberOfCoronas = iCoronaLimit;
		sizeOf_aCoronas = iCoronaLimit * sizeof(CRegisteredCorona);

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x676C44), CCoronas__aCoronas.gta_sa);
		}
		#endif

		// Count or size of array
		Address_GTA_SA_2_00_CCoronas__Update_5A2304_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A2304));
		Address_GTA_SA_2_00_CCoronas__Update_5A231E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A231E));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5A2314),
			(void*)&patch_GTA_SA_2_00_CCoronas__Update_5A2314, 10
		);

		Address_GTA_SA_2_00_CCoronas__Render_5A24E2_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A24E2));
		Address_GTA_SA_2_00_CCoronas__Render_191554_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x191554));
		Address_GTA_SA_2_00_CCoronas__Render_5A2B12_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A2B12));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5A2B06),
			(void*)&patch_GTA_SA_2_00_CCoronas__Render_5A2B06, 12
		);

		Address_GTA_SA_2_00_CCoronas__RenderReflections_5A2CB2_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A2CB2));
		Address_GTA_SA_2_00_CCoronas__RenderReflections_5A2F2C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A2F2C));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5A2F24),
			(void*)&patch_GTA_SA_2_00_CCoronas__RenderReflections_5A2F24, 8
		);

		Address_GTA_SA_2_00_CCoronas__RenderReflections_5A2F82_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A2F82));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5A2F76),
			(void*)&patch_GTA_SA_2_00_CCoronas__RenderReflections_5A2F76, 12
		);

		Address_GTA_SA_2_00_CCoronas__Init_5A3826_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A3826));
		Address_GTA_SA_2_00_CCoronas__Init_5A3834_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A3834));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5A382A),
			(void*)&patch_GTA_SA_2_00_CCoronas__Init_5A382A, 10
		);

		Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B44_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A3B44));
		Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B90_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A3B90));
		Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3CE0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A3CE0));
		Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B66_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A3B66));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5A3B5A),
			(void*)&patch_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B5A, 12
		);

		Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B76_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A3B76));
		Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3BC8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A3BC8));
		Address_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B8C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A3B8C));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5A3B82),
			(void*)&patch_GTA_SA_2_00_CCoronas__RegisterCorona_5A3B82, 10
		);

		Address_GTA_SA_2_00_CCoronas__UpdateCoronaCoors_5A3D82_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A3D82));
		Address_GTA_SA_2_00_CCoronas__UpdateCoronaCoors_5A3D9E_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5A3D9E));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5A3D94),
			(void*)&patch_GTA_SA_2_00_CCoronas__UpdateCoronaCoors_5A3D94, 10
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_iCoronasLimit = iCoronaLimit;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of OTHER LIMITS: Coronas to: %d",
		iCoronaLimit
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets object info limit
void OtherLimits::SetObjectInfoEntries(int iObjectInfoLimit)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iObjectInfoLimit = this->ms_iObjectInfoLimit;

	MAKE_DEAD_IF();
	#if defined(IS_PLATFORM_WIN_X86) || defined(IS_PLATFORM_ANDROID_ARM32)
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if (iObjectInfoLimit > this->ms_iObjectInfoLimit)
		{
			CObjectData__ms_aObjectInfo.gta_sa = new CObjectInfo[iObjectInfoLimit];
			memset(CObjectData__ms_aObjectInfo.gta_sa, NULL, iObjectInfoLimit * sizeof(CObjectInfo));
			CObjectData__ms_aObjectInfo.bIsAllocated.Set(true);
		}
		else if (iObjectInfoLimit < 5)
			throw f92_runtime_error(
				"[OTHER LIMITS] Object info entries = %d\n"
				"The number of entries must be at least 5, because 5 first entries of array are reserved for hardcoded purpose.\n",

				iObjectInfoLimit
			);

		MAKE_DEAD_IF();
		#ifdef IS_PLATFORM_WIN_X86
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			// Patch pointers
			#if TRUE
			{
				CPatch::PatchPointer(0x59F857 + 6, CObjectData__ms_aObjectInfo.gta_sa);	// mov     dword ptr [esi+160h], offset _ZN11CObjectData14ms_aObjectInfoE; CObjectData::ms_aObjectInfo	; sub_59F840
				CPatch::PatchPointer(0x5A2D28 + 2, CObjectData__ms_aObjectInfo.gta_sa);	// add     edx, offset _ZN11CObjectData14ms_aObjectInfoE; CObjectData::ms_aObjectInfo	; sub_5A2D00
				CPatch::PatchPointer(0x5A2E44 + 6, CObjectData__ms_aObjectInfo.gta_sa);	// mov     dword ptr [eax+160h], offset _ZN11CObjectData14ms_aObjectInfoE; CObjectData::ms_aObjectInfo	; sub_5A2D00
				CPatch::PatchPointer(0x5B5369 + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].fMass);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.fMass, 47C34F80h; CObjectData::ms_aObjectInfo	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B5373 + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].fTurnMass);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.fTurnMass, 47C34F80h	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B537D + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].fAirResistance);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.fAirResistance, 3F7D70A4h	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B5387 + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].fElasticity);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.fElasticity, 3DCCCCCDh	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B5391 + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].fBuoyancyConstant);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.fBuoyancyConstant, 44C7FF7Eh	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B539B + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].fUprootLimit);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.fUprootLimit, 0	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B53A5 + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].fColDamageMultiplier);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.fColDamageMultiplier, 3F800000h	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B53AF + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].colDamageEffect);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.colDamageEffect, 0	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B53B6 + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].specialColResponseCase);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.specialColResponseCase, 0	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B53BD + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].cameraAvoidObject);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.cameraAvoidObject, 2	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B53C9 + 1, &CObjectData__ms_aObjectInfo.gta_sa[0]);	// mov     esi, offset _ZN11CObjectData14ms_aObjectInfoE; CObjectData::ms_aObjectInfo	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B53CE + 1, &CObjectData__ms_aObjectInfo.gta_sa[1]);	// mov     edi, (offset _ZN11CObjectData14ms_aObjectInfoE.fMass+50h)	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B53D5 + 2, &CObjectData__ms_aObjectInfo.gta_sa[1].cameraAvoidObject);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.cameraAvoidObject+50h, 0	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B53E1 + 1, &CObjectData__ms_aObjectInfo.gta_sa[0]);	// mov     esi, offset _ZN11CObjectData14ms_aObjectInfoE; CObjectData::ms_aObjectInfo	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B53E6 + 1, &CObjectData__ms_aObjectInfo.gta_sa[2]);	// mov     edi, (offset _ZN11CObjectData14ms_aObjectInfoE.fMass+0A0h)	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B53EF + 1, &CObjectData__ms_aObjectInfo.gta_sa[2].specialColResponseCase);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.specialColResponseCase+0A0h, al	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B53F9 + 1, &CObjectData__ms_aObjectInfo.gta_sa[0]);	// mov     esi, offset _ZN11CObjectData14ms_aObjectInfoE; CObjectData::ms_aObjectInfo	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B53FE + 1, &CObjectData__ms_aObjectInfo.gta_sa[3]);	// mov     edi, (offset _ZN11CObjectData14ms_aObjectInfoE.fMass+0F0h)	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B5405 + 1, &CObjectData__ms_aObjectInfo.gta_sa[3].specialColResponseCase);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.specialColResponseCase+0F0h, al	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B540A + 2, &CObjectData__ms_aObjectInfo.gta_sa[3].cameraAvoidObject);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.cameraAvoidObject+0F0h, 0	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B5416 + 1, &CObjectData__ms_aObjectInfo.gta_sa[0]);	// mov     esi, offset _ZN11CObjectData14ms_aObjectInfoE; CObjectData::ms_aObjectInfo	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B541B + 1, &CObjectData__ms_aObjectInfo.gta_sa[4]);	// mov     edi, (offset _ZN11CObjectData14ms_aObjectInfoE.fMass+140h)	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B542C + 2, &CObjectData__ms_aObjectInfo.gta_sa[4].specialColResponseCase);	// mov     ds:_ZN11CObjectData14ms_aObjectInfoE.specialColResponseCase+140h, bl	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B5466 + 1, &CObjectData__ms_aObjectInfo.gta_sa[5]);	// mov     esi, (offset _ZN11CObjectData14ms_aObjectInfoE.fMass+190h)	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B5587 + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].fMass);	// fcomp   ds:_ZN11CObjectData14ms_aObjectInfoE.fMass; CObjectData::ms_aObjectInfo	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B5596 + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].fColDamageMultiplier);	// fcomp   ds:_ZN11CObjectData14ms_aObjectInfoE.fColDamageMultiplier	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B55A6 + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].colDamageEffect);	// cmp     dl, ds:_ZN11CObjectData14ms_aObjectInfoE.colDamageEffect	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B55B1 + 2, &CObjectData__ms_aObjectInfo.gta_sa[0].specialColResponseCase);	// mov     cl, ds:_ZN11CObjectData14ms_aObjectInfoE.specialColResponseCase	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B55BB + 2, &CObjectData__ms_aObjectInfo.gta_sa[2].specialColResponseCase);	// cmp     al, ds:_ZN11CObjectData14ms_aObjectInfoE.specialColResponseCase+0A0h	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x5B5608 + 1, &CObjectData__ms_aObjectInfo.gta_sa[0].fTurnMass);	// mov     ecx, offset _ZN11CObjectData14ms_aObjectInfoE.fTurnMass	; _ZN11CObjectData10InitialiseEPcb
				CPatch::PatchPointer(0x73860C + 6, &CObjectData__ms_aObjectInfo.gta_sa[4]);	// mov     dword ptr [eax+160h], (offset _ZN11CObjectData14ms_aObjectInfoE.fMass+140h)	; sub_737C87
			}
			#endif

			// Set limit value, will be used by MTA
			{
				CPatch::EnterNewLevelAndDisableDebugState();
				CPatch::PatchUINT32(0x59FB4C, iObjectInfoLimit);
				CPatch::LeaveThisLevel();

			}
		}
		#elif defined(IS_PLATFORM_ANDROID_ARM32)
		if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		{
			// Patch pointer
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x6774A8), CObjectData__ms_aObjectInfo.gta_sa);
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	//////

	this->ms_iObjectInfoLimit = iObjectInfoLimit;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of OTHER LIMITS: Object info entries to: %d",
		iObjectInfoLimit
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets the max size of single collision
void OtherLimits::SetMaxSizeOfSingleCollision(int iSizeOfSingleCollision)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iSizeOfSingleCollision = this->ms_maxSizeOfSingleCollision;

	MAKE_DEAD_IF();
	#if defined(IS_PLATFORM_WIN_X86) || defined(IS_PLATFORM_ANDROID_ARM32)
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion)
		|| gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if (iSizeOfSingleCollision > this->ms_maxSizeOfSingleCollision)
		{
			ms_pColfileReadBuffer.ptr = new char[iSizeOfSingleCollision];
			memset(ms_pColfileReadBuffer.ptr, NULL, iSizeOfSingleCollision);
			ms_pColfileReadBuffer.bIsAllocated.Set(true);
		}	

		#if defined(IS_PLATFORM_WIN_X86)
		if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
		{
			// Patch pointers to ms_pColfileReadBuffer
			#if TRUE
			{
				CPatch::PatchPointer(0x5B4EEE + 1, ms_pColfileReadBuffer.ptr);	// push    offset _colfileReadBuffer; buf	; _ZN11CFileLoader17LoadCollisionFileEPKch
				CPatch::PatchPointer(0x5B4F7E + 1, ms_pColfileReadBuffer.ptr);	// push    offset _colfileReadBuffer; data	; _ZN11CFileLoader17LoadCollisionFileEPKch
				CPatch::PatchPointer(0x5B4F9B + 1, ms_pColfileReadBuffer.ptr);	// push    offset _colfileReadBuffer	; _ZN11CFileLoader17LoadCollisionFileEPKch
				CPatch::PatchPointer(0x5B4FB0 + 1, ms_pColfileReadBuffer.ptr);	// push    offset _colfileReadBuffer	; _ZN11CFileLoader17LoadCollisionFileEPKch
			}
			#endif

			// Patch pointers to PC_Scratch, where we have a limit of 16384 bytes
			#if TRUE
			CPatch::EnterNewLevelAndDisableDebugState();

			CPatch::NOPinstructions(0x41B1E7, 5);	// call to CMemoryMgr::LockScratchPad
			CPatch::NOPinstructions(0x41B2CB, 5);	// call to CMemoryMgr::ReleaseScratchPad

			{
				CPatch::PatchPointer(0x41B1F5 + 1, ms_pColfileReadBuffer.ptr);	// push    offset PC_Scratch; buffer	; CCollisionPlugin__read
				CPatch::PatchPointer(0x41B227 + 1, ms_pColfileReadBuffer.ptr);	// mov     eax, dword ptr PC_Scratch; read buffer	; CCollisionPlugin__read
				CPatch::PatchPointer(0x41B268 + 1, ms_pColfileReadBuffer.ptr);	// push    offset PC_Scratch; read buffer	; CCollisionPlugin__read
				CPatch::PatchPointer(0x41B26F + 2, ms_pColfileReadBuffer.ptr + 4);	// mov     edx, dword ptr PC_Scratch+4; read buffer	; CCollisionPlugin__read
				CPatch::PatchPointer(0x41B279 + 1, ms_pColfileReadBuffer.ptr + 0x20);	// push    (offset PC_Scratch+20h); data	; CCollisionPlugin__read
				CPatch::PatchPointer(0x41B288 + 1, ms_pColfileReadBuffer.ptr + 4);	// mov     eax, dword ptr PC_Scratch+4; read buffer	; CCollisionPlugin__read
				CPatch::PatchPointer(0x41B291 + 1, ms_pColfileReadBuffer.ptr + 0x20);	// push    (offset PC_Scratch+20h); a1	; CCollisionPlugin__read
				CPatch::PatchPointer(0x41B2A0 + 1, ms_pColfileReadBuffer.ptr + 0x20);	// push    (offset PC_Scratch+20h); read buffer	; CCollisionPlugin__read
			}

			CPatch::LeaveThisLevel();
			#endif
		}
		#elif defined(IS_PLATFORM_ANDROID_ARM32)
		if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
		{
			// Patch pointers
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x467050), ms_pColfileReadBuffer.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x466F3A));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x467058), ms_pColfileReadBuffer.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x46701A));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x46705C), ms_pColfileReadBuffer.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x466FF4));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x467060), ms_pColfileReadBuffer.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x467008));
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x467064), ms_pColfileReadBuffer.ptr - g_mCalc.GetCurrentVAbyPreferedVA(0x466FC0));
		}

		#endif		
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_maxSizeOfSingleCollision = iSizeOfSingleCollision;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of OTHER LIMITS: Collision size to: %d",
		iSizeOfSingleCollision
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets the LOD distance limit
void OtherLimits::SetLODdistanceLimit(float LODdistance)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		LODdistance = this->LODdistance;

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86	
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		float* pNewLodValue;

		if (CPatch::IsDebugModeActive())
		{
			pNewLodValue = (float*)0x858FD8;
			LODdistance = 300.0;
		}
		else
			pNewLodValue = &this->LODdistance;

		// Patch references
		#if TRUE
		{
			CPatch::PatchPointer(0x5545E6 + 2, pNewLodValue);	// fcomp   ds:flt_858FD8	; sub_554230
			CPatch::PatchPointer(0x554600 + 2, pNewLodValue);	// fld     ds:flt_858FD8	; sub_554230
			CPatch::PatchPointer(0x55462A + 2, pNewLodValue);	// fsub    ds:flt_858FD8	; sub_554230
			CPatch::PatchPointer(0x555172 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer9ScanWorldEv
			CPatch::PatchPointer(0x555198 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer9ScanWorldEv
			CPatch::PatchPointer(0x5551BB + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer9ScanWorldEv
			CPatch::PatchPointer(0x55522E + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer9ScanWorldEv
			CPatch::PatchPointer(0x555238 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer9ScanWorldEv
			CPatch::PatchPointer(0x555242 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer9ScanWorldEv
			CPatch::PatchPointer(0x5552F4 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer9ScanWorldEv
			CPatch::PatchPointer(0x5552FE + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer9ScanWorldEv
			CPatch::PatchPointer(0x555308 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer9ScanWorldEv
			CPatch::PatchPointer(0x555362 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer9ScanWorldEv
			CPatch::PatchPointer(0x55537A + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer9ScanWorldEv
			CPatch::PatchPointer(0x555388 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer9ScanWorldEv
			CPatch::PatchPointer(0x555A95 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer23RequestObjectsInFrustumEP11RwMatrixTagi
			CPatch::PatchPointer(0x555AA3 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer23RequestObjectsInFrustumEP11RwMatrixTagi
			CPatch::PatchPointer(0x555AB1 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer23RequestObjectsInFrustumEP11RwMatrixTagi
			CPatch::PatchPointer(0x555AFB + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer23RequestObjectsInFrustumEP11RwMatrixTagi
			CPatch::PatchPointer(0x555B05 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer23RequestObjectsInFrustumEP11RwMatrixTagi
			CPatch::PatchPointer(0x555B1C + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer23RequestObjectsInFrustumEP11RwMatrixTagi
			CPatch::PatchPointer(0x555B2A + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer23RequestObjectsInFrustumEP11RwMatrixTagi
			CPatch::PatchPointer(0x555B38 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer23RequestObjectsInFrustumEP11RwMatrixTagi
			CPatch::PatchPointer(0x555B82 + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer23RequestObjectsInFrustumEP11RwMatrixTagi
			CPatch::PatchPointer(0x555B8C + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer23RequestObjectsInFrustumEP11RwMatrixTagi
			CPatch::PatchPointer(0x555B9A + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; _ZN9CRenderer23RequestObjectsInFrustumEP11RwMatrixTagi
			CPatch::PatchPointer(0x56799C + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; sub_567750
			CPatch::PatchPointer(0x56845D + 2, pNewLodValue);	// fmul    ds:flt_858FD8	; sub_567750
			CPatch::PatchPointer(0x5B3098 + 2, pNewLodValue);	// fcomp   ds:flt_858FD8	; _ZN9CColAccel12addIPLEntityEPP7CEntityii
			CPatch::PatchPointer(0x5B527A + 2, pNewLodValue);	// fcomp   ds:flt_858FD8	; __linkLods
			CPatch::PatchPointer(0x65E324 + 2, pNewLodValue);	// fcomp   ds:flt_858FD8	; CTask_86F8FC__m2C
			CPatch::PatchPointer(0x71BE74 + 2, pNewLodValue);	// fcomp   ds:flt_858FD8	; sub_71BC40
		}
		#endif
	}
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->LODdistance = LODdistance;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of OTHER LIMITS: LOD distance to: %f",
		LODdistance
		);
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	CMarker firstFastman92marker = GetObjectMadeOfString<CMarker>("fastman92_markers");

	// Returns actual blip array index
	int CRadar__GetActualBlipArrayIndex(int markerHandle)
	{
		return ((int(__cdecl*)(int))0x582870)(markerHandle);
	}

	// Returns true if blip exist
	bool DoesBlipExist(int markerIndex)
	{
		return (g_otherLimits.CRadar__ms_RadarTrace.gta_sa[markerIndex]._Flag & 2) != 0;
	}

	// Returns true if blip exist
	bool DoesBlipExistForSaving(int markerIndex)
	{
		CMarker* pMarker = &g_otherLimits.CRadar__ms_RadarTrace.gta_sa[markerIndex];
		int v2 = (pMarker->_RadarMode_or_EntityType >> 2) & 0xF;

		return (pMarker->_Flag & 2)
			&& (v2 == 4 || v2 == 5);
	}

	// Returns count of active markers
	unsigned int GetCountOfActiveMarkersForSaving()
	{
		unsigned int numberOfActiveMarkers = 0;

		for (int i = 0; i <g_otherLimits.ms_iRadarTracesLimit; i++)
			if (DoesBlipExistForSaving(i))
				numberOfActiveMarkers++;

		return numberOfActiveMarkers;
	}

	bool CRadar__Save()
	{
		OtherLimits* m_otherLimits = &g_otherLimits;

		CPool_GTASA<Game_GTASA::CEntryExit>* CEntryExitManager__mp_poolEntryExits
			= ACCESS_DEF(
				g_IPLsectionlimits.CEntryExitManager__mp_poolEntryExits.gta_sa
			);

		CGenericGameStorage::SaveDataToWorkBuffer(&firstFastman92marker, sizeof(firstFastman92marker));

		// Get count of active markers
		WORD numberOfActiveMarkers = GetCountOfActiveMarkersForSaving();
		CGenericGameStorage::SaveDataToWorkBuffer(&numberOfActiveMarkers, sizeof(WORD));

		for (WORD i = 0; i < m_otherLimits->ms_iRadarTracesLimit; i++)
		{
			if (!DoesBlipExistForSaving(i))
				continue;

			CGenericGameStorage::SaveDataToWorkBuffer(&i, sizeof(WORD));

			CMarker* pMarker = &m_otherLimits->CRadar__ms_RadarTrace.gta_sa[i];

			CEntryExit* saveEntryExit = pMarker->pEntryExit;

			if (pMarker->pEntryExit)
			{
				int entryExitID =
					CEntryExitManager__mp_poolEntryExits->GetIndex(
						pMarker->pEntryExit
					);

				if (entryExitID < CEntryExitManager__mp_poolEntryExits->m_nSize
					&& !CEntryExitManager__mp_poolEntryExits->IsFreeSlotAtIndex(entryExitID)
					)
					pMarker->entryExitID = entryExitID + 1;
			}

			CGenericGameStorage::SaveDataToWorkBuffer(&m_otherLimits->CRadar__ms_RadarTrace.gta_sa[i], sizeof(CMarker));

			pMarker->pEntryExit = saveEntryExit;

		}

		return true;
	}

	// Fixes loaded marker
	void FixLoadedMarker(CMarker* pMarker)
	{
		if (pMarker->entryExitID)
		{
			unsigned int entryExitID = pMarker->entryExitID - 1;

			CPool_GTASA<Game_GTASA::CEntryExit>* CEntryExitManager__mp_poolEntryExits
				= ACCESS_DEF(
					g_IPLsectionlimits.CEntryExitManager__mp_poolEntryExits.gta_sa
				);

			pMarker->pEntryExit = CEntryExitManager__mp_poolEntryExits->GetAt(entryExitID);
		}
	}

	bool CRadar__Load()
	{
		OtherLimits* m_otherLimits = &g_otherLimits;

		CMarker firstMarker;
		CGenericGameStorage::LoadDataFromWorkBuffer(&firstMarker, sizeof(CMarker));

		if (!memcmp(&firstMarker, &firstFastman92marker, sizeof(CMarker)))
		{
			WORD numberOfMarkersInSave;

			CGenericGameStorage::LoadDataFromWorkBuffer(&numberOfMarkersInSave, sizeof(WORD));

			CMarker uselessMarker;

			for (unsigned int i = 0; i < numberOfMarkersInSave; i++)
			{
				WORD markerID;
				CGenericGameStorage::LoadDataFromWorkBuffer(&markerID, sizeof(WORD));

				CMarker* pMarker = &m_otherLimits->CRadar__ms_RadarTrace.gta_sa[markerID];

				if (markerID < g_IPLsectionlimits.PickupsLimit)
				{
					CGenericGameStorage::LoadDataFromWorkBuffer(pMarker, sizeof(CMarker));
					FixLoadedMarker(pMarker);
				}
				else
				{
					printf_MessageBox(
						"Marker ID = %d, but current marker limit = %d\nDiscarding a pickup.",
						markerID,
						m_otherLimits->ms_iRadarTracesLimit
						);

					CGenericGameStorage::LoadDataFromWorkBuffer(&uselessMarker, sizeof(CMarker));
				}
			}
		}
		else
		{
			// Standard marker format
			if (m_otherLimits->ms_iRadarTracesLimit < 175)
			{
				printf_MessageBox("Selected savefile has standard marker section and requires a marker limit to be 175 or higher.");
				return false;
			}

			memcpy(&m_otherLimits->CRadar__ms_RadarTrace.gta_sa[0], &firstMarker, sizeof(CMarker));
			FixLoadedMarker(&m_otherLimits->CRadar__ms_RadarTrace.gta_sa[0]);

			for (int i = 1; i < 175; i++)
			{
				CMarker* pMarker = &m_otherLimits->CRadar__ms_RadarTrace.gta_sa[i];

				CGenericGameStorage::LoadDataFromWorkBuffer(pMarker, sizeof(CMarker));
				FixLoadedMarker(pMarker);
			}
		}

		return true;

		// unsigned int countOfActiveMarkers = GetCountOfActiveMarkers();
		// printf_MessageBox("number of active markers: %d", countOfActiveMarkers);
	}

	void InitMapLegendList()
	{
		OtherLimits* m_otherLimits = &g_otherLimits;
		memset(m_otherLimits->CRadar__MapLegendList.ptr, NULL, m_otherLimits->ms_iRadarTracesLimit * sizeof(int16_t));
	}

	NAKED void patch_CRadar__InitFrontEndMap_585968()
	{
		__asm
		{
			call InitMapLegendList;

			push 0x585978;
			retn;
		}
	}
}
#endif

// Sets the radar traces limit
void OtherLimits::SetRadarTracesLimit(int iRadarTraces)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iRadarTraces = this->ms_iRadarTracesLimit;

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86	
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (iRadarTraces > this->ms_iRadarTracesLimit)
		{
			CRadar__ms_RadarTrace.gta_sa = new CMarker[iRadarTraces];
			CRadar__ms_RadarTrace.bIsAllocated.Set(true);

			CRadar__MapLegendList.ptr = new int16_t[iRadarTraces];
			CRadar__MapLegendList.bIsAllocated.Set(true);
		}	

		unsigned int sizeof_RadarTracesArray = iRadarTraces * sizeof(CMarker);

		// Patch pointers to CRadar::ms_RadarTrace
		#if TRUE
		{
			if(gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
				CPatch::PatchPointer(0x58713D + 2, CRadar__ms_RadarTrace.gta_sa);	// mov     edx, dword ptr ds:_ZN6CRadar13ms_RadarTraceE.Color[edi]; CRadar::ms_RadarTrace	; sub_587000
			else if(gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
				CPatch::PatchPointer(0x405B03 + 2, CRadar__ms_RadarTrace.gta_sa);	// mov     edx, dword ptr ds:_ZN6CRadar13ms_RadarTraceE.Color[edi]; CRadar::ms_RadarTrace	; sub_587000

			CPatch::PatchPointer(0x582829 + 4, &CRadar__ms_RadarTrace.gta_sa->_Index);	// mov     cx, ds:_ZN6CRadar13ms_RadarTraceE._Index[eax*8]	; 
			CPatch::PatchPointer(0x582839 + 4, &CRadar__ms_RadarTrace.gta_sa->_Index);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Index[eax*8], cx	; 
			CPatch::PatchPointer(0x58284A + 4, &CRadar__ms_RadarTrace.gta_sa->_Index);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Index[eax*8], 1	; 
			CPatch::PatchPointer(0x582854 + 4, &CRadar__ms_RadarTrace.gta_sa->_Index);	// movzx   eax, ds:_ZN6CRadar13ms_RadarTraceE._Index[eax*8]	; 
			CPatch::PatchPointer(0x582889 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     cx, ds:_ZN6CRadar13ms_RadarTraceE._Index[edx]	; 
			CPatch::PatchPointer(0x582892 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// test    ds:_ZN6CRadar13ms_RadarTraceE._Flag[edx], 2	; 
			CPatch::PatchPointer(0x583820 + 1, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     al, ds:_ZN6CRadar13ms_RadarTraceE._Flag	; sub_583820
			CPatch::PatchPointer(0x58383E + 2, &(CRadar__ms_RadarTrace.gta_sa+1)->_Flag);	// mov     bl, ds:(_ZN6CRadar13ms_RadarTraceE._Flag+28h)[eax]	; sub_583820
			CPatch::PatchPointer(0x583863 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     bl, ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[eax]	; sub_583820
			CPatch::PatchPointer(0x583869 + 2, &CRadar__ms_RadarTrace.gta_sa->Pos);	// lea     ecx, _ZN6CRadar13ms_RadarTraceE.Pos.x[eax]	; sub_583820
			CPatch::PatchPointer(0x583897 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[eax], cl	; sub_583820
			CPatch::PatchPointer(0x58389F + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// mov     cx, ds:_ZN6CRadar13ms_RadarTraceE._Index[eax]	; sub_583820
			CPatch::PatchPointer(0x5838B0 + 2, CRadar__ms_RadarTrace.gta_sa);	// mov     dword ptr ds:_ZN6CRadar13ms_RadarTraceE.Color[eax], 8; CRadar::ms_RadarTrace	; sub_583820
			CPatch::PatchPointer(0x5838BA + 2, &CRadar__ms_RadarTrace.gta_sa->_SphereRadius);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._SphereRadius[eax], 3F800000h	; sub_583820
			CPatch::PatchPointer(0x5838C4 + 2, &CRadar__ms_RadarTrace.gta_sa->EntityHandle);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.EntityHandle[eax], edx	; sub_583820
			CPatch::PatchPointer(0x5838CA + 3, &CRadar__ms_RadarTrace.gta_sa->Size);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.Size[eax], di	; sub_583820
			CPatch::PatchPointer(0x5838D1 + 2, &CRadar__ms_RadarTrace.gta_sa->Icon);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.Icon[eax], dl	; sub_583820
			CPatch::PatchPointer(0x5838D7 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Flag[eax], 3	; sub_583820
			CPatch::PatchPointer(0x5838DE + 2, &CRadar__ms_RadarTrace.gta_sa->pEntryExit);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.field_20[eax], edx	; sub_583820
			CPatch::PatchPointer(0x5838E7 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Index[eax], cx	; sub_583820
			CPatch::PatchPointer(0x5838FA + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Index[eax], di	; sub_583820
			CPatch::PatchPointer(0x583972 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     si, ds:_ZN6CRadar13ms_RadarTraceE._Index[edx]	; sub_583920
			CPatch::PatchPointer(0x58397B + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// test    ds:_ZN6CRadar13ms_RadarTraceE._Flag[edx], 2	; sub_583920
			CPatch::PatchPointer(0x58398A + 3, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     dl, ds:_ZN6CRadar13ms_RadarTraceE._Flag[ecx*8]	; sub_583920
			CPatch::PatchPointer(0x583995 + 3, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Flag[ecx*8], dl	; sub_583920
			CPatch::PatchPointer(0x5839A0 + 1, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     al, ds:_ZN6CRadar13ms_RadarTraceE._Flag	; sub_5839A0
			CPatch::PatchPointer(0x5839BB + 2, &(CRadar__ms_RadarTrace.gta_sa+1)->_Flag);	// mov     cl, ds:(_ZN6CRadar13ms_RadarTraceE._Flag+28h)[eax]	; sub_5839A0
			CPatch::PatchPointer(0x5839E1 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     bl, ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[eax]	; sub_5839A0
			CPatch::PatchPointer(0x5839F6 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[eax], bl	; sub_5839A0
			CPatch::PatchPointer(0x583A05 + 2, CRadar__ms_RadarTrace.gta_sa);	// mov     dword ptr ds:_ZN6CRadar13ms_RadarTraceE.Color[eax], 1; CRadar::ms_RadarTrace	; sub_5839A0
			CPatch::PatchPointer(0x583A11 + 2, CRadar__ms_RadarTrace.gta_sa);	// mov     dword ptr ds:_ZN6CRadar13ms_RadarTraceE.Color[eax], 7; CRadar::ms_RadarTrace	; sub_5839A0
			CPatch::PatchPointer(0x583A23 + 2, &CRadar__ms_RadarTrace.gta_sa->EntityHandle);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.EntityHandle[eax], edx	; sub_5839A0
			CPatch::PatchPointer(0x583A34 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// mov     cx, ds:_ZN6CRadar13ms_RadarTraceE._Index[eax]	; sub_5839A0
			CPatch::PatchPointer(0x583A40 + 2, &CRadar__ms_RadarTrace.gta_sa->_SphereRadius);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._SphereRadius[eax], 3F800000h	; sub_5839A0
			CPatch::PatchPointer(0x583A4A + 3, &CRadar__ms_RadarTrace.gta_sa->Size);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.Size[eax], 1	; sub_5839A0
			CPatch::PatchPointer(0x583A53 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[eax], dl	; sub_5839A0
			CPatch::PatchPointer(0x583A59 + 2, &CRadar__ms_RadarTrace.gta_sa->Icon);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.Icon[eax], 0	; sub_5839A0
			CPatch::PatchPointer(0x583A60 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Flag[eax], 3	; sub_5839A0
			CPatch::PatchPointer(0x583A67 + 2, &CRadar__ms_RadarTrace.gta_sa->pEntryExit);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.field_20[eax], 0	; sub_5839A0
			CPatch::PatchPointer(0x583A75 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Index[eax], cx	; sub_5839A0
			CPatch::PatchPointer(0x583A86 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Index[eax], 1	; sub_5839A0
			CPatch::PatchPointer(0x583A8F + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// movzx   eax, ds:_ZN6CRadar13ms_RadarTraceE._Index[eax]	; sub_5839A0
			CPatch::PatchPointer(0x583AC9 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     cx, ds:_ZN6CRadar13ms_RadarTraceE._Index[edx]	; sub_583AB0
			CPatch::PatchPointer(0x583AD2 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// test    ds:_ZN6CRadar13ms_RadarTraceE._Flag[edx], 2	; sub_583AB0
			CPatch::PatchPointer(0x583AE4 + 2, CRadar__ms_RadarTrace.gta_sa);	// mov     dword ptr ds:_ZN6CRadar13ms_RadarTraceE.Color[edx], eax; CRadar::ms_RadarTrace	; sub_583AB0
			CPatch::PatchPointer(0x583B03 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// test    ds:_ZN6CRadar13ms_RadarTraceE._Flag[eax], 4	; sub_583AF0
			CPatch::PatchPointer(0x583B15 + 2, &CRadar__ms_RadarTrace.gta_sa->Pos.y);	// mov     ecx, ds:_ZN6CRadar13ms_RadarTraceE.Pos.y[eax]	; sub_583AF0
			CPatch::PatchPointer(0x583B1B + 2, &CRadar__ms_RadarTrace.gta_sa->Pos.x);	// mov     edx, dword ptr ds:_ZN6CRadar13ms_RadarTraceE.Pos.x[eax]	; sub_583AF0
			CPatch::PatchPointer(0x583C8A + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     dx, ds:_ZN6CRadar13ms_RadarTraceE._Index[eax]	; 
			CPatch::PatchPointer(0x583C93 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// test    ds:_ZN6CRadar13ms_RadarTraceE._Flag[eax], 2	; 
			CPatch::PatchPointer(0x583CAE + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// and     ds:_ZN6CRadar13ms_RadarTraceE._Flag[eax], 0FEh	; 
			CPatch::PatchPointer(0x583CB6 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// or      ds:_ZN6CRadar13ms_RadarTraceE._Flag[eax], cl	; 
			CPatch::PatchPointer(0x583CD9 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     cx, ds:_ZN6CRadar13ms_RadarTraceE._Index[edx]	; sub_583CC0
			CPatch::PatchPointer(0x583CE2 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// test    ds:_ZN6CRadar13ms_RadarTraceE._Flag[edx], 2	; sub_583CC0
			CPatch::PatchPointer(0x583D09 + 4, &CRadar__ms_RadarTrace.gta_sa->Size);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.Size[eax*8], cx	; sub_583CC0
			CPatch::PatchPointer(0x583D39 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     dx, ds:_ZN6CRadar13ms_RadarTraceE._Index[ecx]	; sub_583D20
			CPatch::PatchPointer(0x583D42 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// test    ds:_ZN6CRadar13ms_RadarTraceE._Flag[ecx], 2	; sub_583D20
			CPatch::PatchPointer(0x583D50 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     al, ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[ecx]	; sub_583D20
			CPatch::PatchPointer(0x583D5A + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     dl, ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[ecx]	; sub_583D20
			CPatch::PatchPointer(0x583D64 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[ecx], dl	; sub_583D20
			CPatch::PatchPointer(0x583D89 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     cx, ds:_ZN6CRadar13ms_RadarTraceE._Index[edx]	; sub_583D70
			CPatch::PatchPointer(0x583D92 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// test    ds:_ZN6CRadar13ms_RadarTraceE._Flag[edx], 2	; sub_583D70
			CPatch::PatchPointer(0x583DA4 + 2, &CRadar__ms_RadarTrace.gta_sa->Icon);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.Icon[edx], al	; sub_583D70
			CPatch::PatchPointer(0x583DC9 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     dx, ds:_ZN6CRadar13ms_RadarTraceE._Index[ecx]	; sub_583DB0
			CPatch::PatchPointer(0x583DD2 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     dl, ds:_ZN6CRadar13ms_RadarTraceE._Flag[ecx]	; sub_583DB0
			CPatch::PatchPointer(0x583DEF + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Flag[ecx], dl	; sub_583DB0
			CPatch::PatchPointer(0x583E19 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     dx, ds:_ZN6CRadar13ms_RadarTraceE._Index[ecx]	; 
			CPatch::PatchPointer(0x583E22 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     dl, ds:_ZN6CRadar13ms_RadarTraceE._Flag[ecx]	; 
			CPatch::PatchPointer(0x583E3F + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Flag[ecx], dl	; 
			CPatch::PatchPointer(0x583E6A + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     dx, ds:_ZN6CRadar13ms_RadarTraceE._Index[eax]	; sub_583E50
			CPatch::PatchPointer(0x583E73 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     dl, ds:_ZN6CRadar13ms_RadarTraceE._Flag[eax]	; sub_583E50
			CPatch::PatchPointer(0x583E83 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     cl, ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[eax]	; sub_583E50
			CPatch::PatchPointer(0x583EA2 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Flag[eax], dl	; sub_583E50
			CPatch::PatchPointer(0x583EC9 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     dx, ds:_ZN6CRadar13ms_RadarTraceE._Index[ecx]	; sub_583EB0
			CPatch::PatchPointer(0x583ED2 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     dl, ds:_ZN6CRadar13ms_RadarTraceE._Flag[ecx]	; sub_583EB0
			CPatch::PatchPointer(0x583EEF + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Flag[ecx], dl	; sub_583EB0
			CPatch::PatchPointer(0x583F19 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     cx, ds:_ZN6CRadar13ms_RadarTraceE._Index[edx]	; sub_583F00
			CPatch::PatchPointer(0x583F22 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// test    ds:_ZN6CRadar13ms_RadarTraceE._Flag[edx], 2	; sub_583F00
			CPatch::PatchPointer(0x583F34 + 2, &CRadar__ms_RadarTrace.gta_sa->pEntryExit);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.field_20[edx], eax	; sub_583F00
			CPatch::PatchPointer(0x585A16 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     dl, ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[eax]	; sub_5859F0
			CPatch::PatchPointer(0x585A2F + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     bl, ds:_ZN6CRadar13ms_RadarTraceE._Flag[eax]; jumptable 00585A28 cases 0,1	; sub_5859F0
			CPatch::PatchPointer(0x585A9F + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     cl, ds:_ZN6CRadar13ms_RadarTraceE._Flag[eax]	; sub_5859F0
			CPatch::PatchPointer(0x585AA5 + 2, CRadar__ms_RadarTrace.gta_sa);	// mov     eax, dword ptr ds:_ZN6CRadar13ms_RadarTraceE.Color[eax]; CRadar::ms_RadarTrace	; sub_5859F0
			CPatch::PatchPointer(0x585BFD + 1, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     edi, offset _ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType	; sub_585BF0
			CPatch::PatchPointer(0x586D6D + 3, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     al, ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[esi*8]	; sub_586D60
			CPatch::PatchPointer(0x586D74 + 3, CRadar__ms_RadarTrace.gta_sa);	// lea     esi, _ZN6CRadar13ms_RadarTraceE.Color[esi*8]; CRadar::ms_RadarTrace	; sub_586D60
			CPatch::PatchPointer(0x587013 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     al, ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[edi]	; sub_587000
			CPatch::PatchPointer(0x58703C + 2, &CRadar__ms_RadarTrace.gta_sa->EntityHandle);	// mov     eax, ds:_ZN6CRadar13ms_RadarTraceE.EntityHandle[edi]; jumptable 00587035 case 0	; sub_587000
			CPatch::PatchPointer(0x58706F + 2, &CRadar__ms_RadarTrace.gta_sa->EntityHandle);	// mov     ecx, ds:_ZN6CRadar13ms_RadarTraceE.EntityHandle[edi]; jumptable 00587035 case 1	; sub_587000
			CPatch::PatchPointer(0x58709C + 2, &CRadar__ms_RadarTrace.gta_sa->EntityHandle);	// mov     edx, ds:_ZN6CRadar13ms_RadarTraceE.EntityHandle[edi]; jumptable 00587035 case 2	; sub_587000
			CPatch::PatchPointer(0x5870B0 + 2, &CRadar__ms_RadarTrace.gta_sa->EntityHandle);	// mov     eax, ds:_ZN6CRadar13ms_RadarTraceE.EntityHandle[edi]; jumptable 00587035 case 5	; sub_587000
			CPatch::PatchPointer(0x5870F6 + 2, &CRadar__ms_RadarTrace.gta_sa->EntityHandle);	// mov     ecx, ds:_ZN6CRadar13ms_RadarTraceE.EntityHandle[edi]; jumptable 00587035 case 6	; sub_587000
			CPatch::PatchPointer(0x587145 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     al, ds:_ZN6CRadar13ms_RadarTraceE._Flag[edi]	; sub_587000
			CPatch::PatchPointer(0x587167 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     al, ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[edi]	; sub_587000
			CPatch::PatchPointer(0x587183 + 2, &CRadar__ms_RadarTrace.gta_sa->_SphereRadius);	// mov     eax, ds:_ZN6CRadar13ms_RadarTraceE._SphereRadius[edi]	; sub_587000
			CPatch::PatchPointer(0x5871CB + 2, &CRadar__ms_RadarTrace.gta_sa->_SphereRadius);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._SphereRadius[edi], 40A00000h	; sub_587000
			CPatch::PatchPointer(0x5871D5 + 2, &CRadar__ms_RadarTrace.gta_sa->pEntryExit);	// mov     ecx, ds:_ZN6CRadar13ms_RadarTraceE.field_20[edi]	; sub_587000
			CPatch::PatchPointer(0x5871E9 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     al, ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[edi]	; sub_587000
			CPatch::PatchPointer(0x587239 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     al, ds:_ZN6CRadar13ms_RadarTraceE._Flag[edi]	; sub_587000
			CPatch::PatchPointer(0x587285 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     al, ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[edi]	; sub_587000
			CPatch::PatchPointer(0x5872AC + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// test    ds:_ZN6CRadar13ms_RadarTraceE._Flag[edi], 10h	; sub_587000
			CPatch::PatchPointer(0x587346 + 3, &CRadar__ms_RadarTrace.gta_sa->Size);	// movsx   eax, ds:_ZN6CRadar13ms_RadarTraceE.Size[edi]	; sub_587000
			CPatch::PatchPointer(0x5874D6 + 2, &CRadar__ms_RadarTrace.gta_sa->Pos);	// lea     ecx, _ZN6CRadar13ms_RadarTraceE.Pos.x[edi]	; sub_587000
			CPatch::PatchPointer(0x587649 + 3, &CRadar__ms_RadarTrace.gta_sa->Size);	// movsx   edx, ds:_ZN6CRadar13ms_RadarTraceE.Size[edi]	; sub_587000
			CPatch::PatchPointer(0x587796 + 2, &CRadar__ms_RadarTrace.gta_sa->Icon);	// mov     al, ds:_ZN6CRadar13ms_RadarTraceE.Icon[edi]	; sub_587000
			CPatch::PatchPointer(0x587959 + 2, &CRadar__ms_RadarTrace.gta_sa->Pos);	// lea     edx, _ZN6CRadar13ms_RadarTraceE.Pos.x[edi]	; sub_587000
			CPatch::PatchPointer(0x587B59 + 3, &CRadar__ms_RadarTrace.gta_sa->Size);	// movsx   edx, ds:_ZN6CRadar13ms_RadarTraceE.Size[edi]	; sub_587000
			CPatch::PatchPointer(0x587BC1 + 4, &CRadar__ms_RadarTrace.gta_sa->Icon);	// movsx   ax, ds:_ZN6CRadar13ms_RadarTraceE.Icon[edi]	; sub_587000
			CPatch::PatchPointer(0x587C2C + 3, &CRadar__ms_RadarTrace.gta_sa->Size);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.Size[eax], cx	; sub_587C10
			CPatch::PatchPointer(0x587C33 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Flag[eax], cl	; sub_587C10
			CPatch::PatchPointer(0x587C39 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     cl, ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[eax]	; sub_587C10
			CPatch::PatchPointer(0x587C42 + 2, &CRadar__ms_RadarTrace.gta_sa->_SphereRadius);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._SphereRadius[eax], 3F800000h	; sub_587C10
			CPatch::PatchPointer(0x587C4C + 2, &CRadar__ms_RadarTrace.gta_sa->pEntryExit);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.field_20[eax], edx	; sub_587C10
			CPatch::PatchPointer(0x587C52 + 2, &CRadar__ms_RadarTrace.gta_sa->Icon);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.Icon[eax], dl	; sub_587C10
			CPatch::PatchPointer(0x587C58 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[eax], cl	; sub_587C10
			CPatch::PatchPointer(0x587C72 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     cl, ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[eax]	; sub_587C60
			CPatch::PatchPointer(0x587C86 + 2, &CRadar__ms_RadarTrace.gta_sa->EntityHandle);	// cmp     ds:_ZN6CRadar13ms_RadarTraceE.EntityHandle[eax], ebp	; sub_587C60
			CPatch::PatchPointer(0x587C9E + 2, &CRadar__ms_RadarTrace.gta_sa->_SphereRadius);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._SphereRadius[eax], 3F800000h	; sub_587C60
			CPatch::PatchPointer(0x587CA8 + 3, &CRadar__ms_RadarTrace.gta_sa->Size);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.Size[eax], dx	; sub_587C60
			CPatch::PatchPointer(0x587CAF + 2, &CRadar__ms_RadarTrace.gta_sa->pEntryExit);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.field_20[eax], ebx	; sub_587C60
			CPatch::PatchPointer(0x587CB5 + 2, &CRadar__ms_RadarTrace.gta_sa->Icon);	// mov     ds:_ZN6CRadar13ms_RadarTraceE.Icon[eax], bl	; sub_587C60
			CPatch::PatchPointer(0x587CBB + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._Flag[eax], dl	; sub_587C60
			CPatch::PatchPointer(0x587CC1 + 2, &CRadar__ms_RadarTrace.gta_sa->_RadarMode_or_EntityType);	// mov     ds:_ZN6CRadar13ms_RadarTraceE._RadarMode_or_EntityType[eax], cl	; sub_587C60
			CPatch::PatchPointer(0x587CF9 + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     cx, ds:_ZN6CRadar13ms_RadarTraceE._Index[edx]	; sub_587CE0
			CPatch::PatchPointer(0x587D02 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// test    ds:_ZN6CRadar13ms_RadarTraceE._Flag[edx], 2	; sub_587CE0
			CPatch::PatchPointer(0x587F7E + 3, &CRadar__ms_RadarTrace.gta_sa->_Index);	// cmp     dx, ds:_ZN6CRadar13ms_RadarTraceE._Index[eax]	; sub_587D20
			CPatch::PatchPointer(0x587F87 + 2, &CRadar__ms_RadarTrace.gta_sa->_Flag);	// test    ds:_ZN6CRadar13ms_RadarTraceE._Flag[eax], 2	; sub_587D20
			CPatch::PatchPointer(0x587FC2 + 1, &CRadar__ms_RadarTrace.gta_sa->Size);	// mov     eax, offset _ZN6CRadar13ms_RadarTraceE.Size	; sub_587FB0
			CPatch::PatchPointer(0x587FD1 + 1, &CRadar__ms_RadarTrace.gta_sa->Size);	// cmp     eax, offset _ZN6CRadar13ms_RadarTraceE.Size	; sub_587FB0
			CPatch::PatchPointer(0x588306 + 1, &CRadar__ms_RadarTrace.gta_sa->Icon);	// mov     edi, offset _ZN6CRadar13ms_RadarTraceE.Icon	; sub_588050
			CPatch::PatchPointer(0x5883A4 + 1, &CRadar__ms_RadarTrace.gta_sa->Icon);	// mov     edi, offset _ZN6CRadar13ms_RadarTraceE.Icon	; sub_588050
			CPatch::PatchPointer(0x5D53C8 + 1, &CRadar__ms_RadarTrace.gta_sa->pEntryExit);	// mov     esi, offset _ZN6CRadar13ms_RadarTraceE.field_20	; sub_5D53C0
			CPatch::PatchPointer(0x5D5867 + 1, &CRadar__ms_RadarTrace.gta_sa->pEntryExit);	// mov     esi, offset _ZN6CRadar13ms_RadarTraceE.field_20	; sub_5D5860

			CPatch::PatchPointer(0x585FAA + 2, &(CRadar__ms_RadarTrace.gta_sa+iRadarTraces)->_RadarMode_or_EntityType);	// cmp     edi, offset unk_BAA26E	; sub_585BF0
			CPatch::PatchPointer(0x587FD8 + 1, &(CRadar__ms_RadarTrace.gta_sa + iRadarTraces)->Size);	// cmp     eax, offset unk_BAA264	; sub_587FB0
			CPatch::PatchPointer(0x587FF9 + 1, &(CRadar__ms_RadarTrace.gta_sa + iRadarTraces)->Size);	// cmp     eax, offset unk_BAA264	; sub_587FB0
			CPatch::PatchPointer(0x588388 + 2, &(CRadar__ms_RadarTrace.gta_sa + iRadarTraces)->Icon);	// cmp     edi, offset unk_BAA26C	; sub_588050
			CPatch::PatchPointer(0x58841D + 2, &(CRadar__ms_RadarTrace.gta_sa + iRadarTraces)->Icon);	// cmp     edi, offset unk_BAA26C	; sub_588050

		}
		#endif

		// Patch pointers to CRadar::MapLegendList
		#if TRUE
		{
			CPatch::PatchPointer(0x5761E0 + 4, CRadar__MapLegendList.ptr);	// movsx   edx, ds:_ZN6CRadar13MapLegendListE[esi*2]; CRadar::MapLegendList	; sub_575130
			CPatch::PatchPointer(0x584A65 + 4, CRadar__MapLegendList.ptr);	// mov     ds:_ZN6CRadar13MapLegendListE[edx*2], 3; CRadar::MapLegendList	; sub_584960
			CPatch::PatchPointer(0x58596F + 1, CRadar__MapLegendList.ptr);	// mov     edi, offset _ZN6CRadar13MapLegendListE; CRadar::MapLegendList	; sub_585960
			CPatch::PatchPointer(0x585A52 + 1, CRadar__MapLegendList.ptr);	// mov     eax, offset _ZN6CRadar13MapLegendListE; CRadar::MapLegendList	; sub_5859F0
			CPatch::PatchPointer(0x585A8D + 4, CRadar__MapLegendList.ptr);	// mov     ds:_ZN6CRadar13MapLegendListE[edx*2], di; CRadar::MapLegendList	; sub_5859F0
		}
		#endif

		// Patch count of array (175)
		#if TRUE
		{
			CPatch::PatchUINT32(0x58384C + 2, iRadarTraces);	// cmp     esi, 175	; sub_583820
			CPatch::PatchUINT32(0x5839CA + 2, iRadarTraces);	// cmp     esi, 175	; sub_5839A0
			CPatch::PatchUINT32(0x585A57 + 1, iRadarTraces);	// mov     esi, 175	; sub_5859F0
			CPatch::PatchUINT32(0x587C1A + 1, iRadarTraces);	// cmp     eax, 175	; sub_587C10
			CPatch::PatchUINT32(0x5D53CD + 1, iRadarTraces);	// mov     edi, 175	; sub_5D53C0
			CPatch::PatchUINT32(0x5D586C + 4, iRadarTraces);	// mov     [esp+18h+var_4], 175	; sub_5D5860
		}
		#endif

		// Patch size of array (7000)
		#if TRUE
		{
			CPatch::PatchUINT32(0x583833 + 1, sizeof_RadarTracesArray);	// cmp     eax, 7000	; sub_583820
			CPatch::PatchUINT32(0x5839B0 + 1, sizeof_RadarTracesArray);	// cmp     eax, 1B58h	; sub_5839A0
			CPatch::PatchUINT32(0x587C94 + 1, sizeof_RadarTracesArray);	// cmp     eax, 1B58h	; sub_587C60
			CPatch::PatchUINT32(0x587CCA + 1, sizeof_RadarTracesArray);	// cmp     eax, 1B58h	; sub_587C60
		}
		#endif

		// Redirect save function
		g_SaveOfVariableLength.MakeSaveOfVariableLength();

		CGenericLogStorage::SaveFormattedTextLn(
			"Format of new savefiles will be different: patch for radar traces is applied.\n");

		CPatch::RedirectFunction(0x5D5860, &CRadar__Save);
		CPatch::RedirectCode(0x585968, &patch_CRadar__InitFrontEndMap_585968);
	}
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_iRadarTracesLimit = iRadarTraces;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of OTHER LIMITS: Radar traces to: %d",
		iRadarTraces
		);
	CGenericLogStorage::WriteLineSeparator();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	// Opens RW stream
	static void *__cdecl RwTextureRead(const char *name, const char *maskName)
	{
		return ((void *(__cdecl*)
			(const char *name, const char *maskName))0x7F3AC0)
			(name, maskName);
	}

	void LoadPlateBackTextures()
	{
		OtherLimits* m_otherLimits = &g_otherLimits;
		char textureName[32];

		for (int i = 0; i < m_otherLimits->ms_iNumberOfPlateTextures; i++)
		{
			sprintf(textureName, "plateback%d", i + 1);

			void* pTexture = RwTextureRead(textureName, NULL);
			
			if(pTexture)
			{			
				*((__int8*)pTexture + 0x50) = 1;
				*((__int8*)pTexture + 0x51) = 51;
			}
			
			m_otherLimits->CustomCarPlateMgr__pPlatebackTexTab.ptr[i] = pTexture;
		}
	}

	NAKED void patch_CCustomCarPlateMgr__Initialise_6FD53A()
	{
		__asm
		{
			add esp, 0x10;
			call LoadPlateBackTextures;

			// go back
			push 0x6FD57B;
			retn;
		}
	}


	NAKED void patch_CCustomCarPlateMgr__SetupMaterialPlatebackTexture_6FDE58()
	{
		__asm
		{
			mov eax, 0x6FD7A0;	// CCustomCarPlateMgr::GetMapRegionPlateDesign
			call eax;

			// go back
			push 0x6FDE78;
			retn;
		}
	}

	NAKED void patch_CCustomCarPlateMgr__CreatePlateTexture_6FDEAB()
	{
		__asm
		{
			mov eax, 0x6FD7A0;	// CCustomCarPlateMgr::GetMapRegionPlateDesign
			call eax;
			mov ebx, eax;

			push 0x6FDECB;
			retn;
		}
	}
}
#endif

// Sets number of plate textures
void OtherLimits::SetNumberOfPlateTextures(int iPlateTextures)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPlateTextures = this->ms_iNumberOfPlateTextures;

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (iPlateTextures > this->ms_iNumberOfPlateTextures)
		{
			CustomCarPlateMgr__pPlatebackTexTab.ptr = new void*[iPlateTextures];
			CustomCarPlateMgr__pPlatebackTexTab.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x6FD54D + 1, CustomCarPlateMgr__pPlatebackTexTab.ptr);	// mov     ds:_ZN18CCustomCarPlateMgr16pPlatebackTexTabE, eax; CCustomCarPlateMgr::pPlatebackTexTab	; sub_6FD500
			CPatch::PatchPointer(0x6FD565 + 1, CustomCarPlateMgr__pPlatebackTexTab.ptr + 1);	// mov     ds:_ZN18CCustomCarPlateMgr16pPlatebackTexTabE+4, eax	; sub_6FD500
			CPatch::PatchPointer(0x6FD576 + 1, CustomCarPlateMgr__pPlatebackTexTab.ptr + 2);	// mov     ds:_ZN18CCustomCarPlateMgr16pPlatebackTexTabE+8, eax	; sub_6FD500
			CPatch::PatchPointer(0x6FD755 + 1, CustomCarPlateMgr__pPlatebackTexTab.ptr);	// mov     esi, offset _ZN18CCustomCarPlateMgr16pPlatebackTexTabE; CCustomCarPlateMgr::pPlatebackTexTab	; sub_6FD720
			CPatch::PatchPointer(0x6FD778 + 2, CustomCarPlateMgr__pPlatebackTexTab.ptr + iPlateTextures);	// cmp     esi, offset dword_C3EF6C	; sub_6FD720
			CPatch::PatchPointer(0x6FDE7B + 3, CustomCarPlateMgr__pPlatebackTexTab.ptr);	// mov     ecx, ds:_ZN18CCustomCarPlateMgr16pPlatebackTexTabE[eax*4]; CCustomCarPlateMgr::pPlatebackTexTab	; sub_6FDE50
		}
		#endif

		// Functions
		{
			CPatch::NOPinstructions(0x6FD52B, 2);
			CPatch::NOPinstructions(0x6FD530, 5);
			CPatch::RedirectCode(0x6FD53A, &patch_CCustomCarPlateMgr__Initialise_6FD53A);

			CPatch::EnterNewLevelAndDisableDebugState();
			CPatch::PatchUINT8(0x6FD591 + 2, 12);	// add     esp, 34h
			CPatch::LeaveThisLevel();

			CPatch::RedirectCode(0x6FDE58, &patch_CCustomCarPlateMgr__SetupMaterialPlatebackTexture_6FDE58);
			CPatch::RedirectCode(0x6FDEAB, &patch_CCustomCarPlateMgr__CreatePlateTexture_6FDEAB);
		}
	}
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_iNumberOfPlateTextures = iPlateTextures;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of OTHER LIMITS: Number of plate textures: %d",
		iPlateTextures
		);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets max number of particles active
void OtherLimits::SetMaxNumberOfParticlesActive(int iMaxNumberOfParticlesActive)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iMaxNumberOfParticlesActive = this->ms_iMaxNumberOfParticlesActive;

	MAKE_DEAD_IF();

#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		const int sizeof_element = 60;
		const int sizeof_allElements = sizeof_element * iMaxNumberOfParticlesActive;

		// Fx_c::Init
		#if TRUE
		{
			CPatch::PatchUINT32(0x4A992D + 1, sizeof_allElements + 4);	// push    60004

			CPatch::PatchUINT32(0x4A9950 + 1, iMaxNumberOfParticlesActive);	// push    1000            ; count

			CPatch::PatchUINT32(0x4A995B + 2, iMaxNumberOfParticlesActive);	// mov     dword ptr [eax], 1000

			CPatch::PatchUINT32(0x4A9988 + 2, sizeof_allElements);	// cmp     esi, 60000
		}
		#endif

		// FxManager_c::UnloadFxProject
		#if TRUE
		{
			CPatch::PatchUINT32(0x4A9B2F + 1, sizeof_allElements + 4);	// push    60004

			CPatch::PatchUINT32(0x4A9B56 + 1, iMaxNumberOfParticlesActive);	// push    1000            ; count

			CPatch::PatchUINT32(0x4A9B61 + 2, iMaxNumberOfParticlesActive);	// mov     dword ptr [eax], 1000

			CPatch::PatchUINT32(0x4A9B90 + 2, sizeof_allElements);	// cmp     esi, 60000
		}
		#endif
	}
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_iMaxNumberOfParticlesActive = iMaxNumberOfParticlesActive;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of OTHER LIMITS: Max number of particles active: %d",
		iMaxNumberOfParticlesActive
	);
	CGenericLogStorage::WriteLineSeparator();
}

// Patches pointer to CSetPieces::aSetPieces
template<typename T>
void SetMaxNumberOfSetPiecesPatchPointersToIs_GTA_SA_1_0_PC(
	eGameVersion gameVersion,
	T* CSetPieces__aSetPieces
)
{
	CPatch::PatchPointer(0x499525 + 2, &CSetPieces__aSetPieces->m_nType);	// mov     _ZN10CSetPieces10aSetPiecesE.m_nType[esi], al	; _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_
	CPatch::PatchPointer(0x499566 + 3, &CSetPieces__aSetPieces->m_nAreaCorner.m_vInf.x);	// mov     word ptr _ZN10CSetPieces10aSetPiecesE.m_nAreaCorner.m_vInf.x[esi], ax	; _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_
	CPatch::PatchPointer(0x49957A + 3, &CSetPieces__aSetPieces->m_nAreaCorner.m_vInf.y);	// mov     _ZN10CSetPieces10aSetPiecesE.m_nAreaCorner.m_vInf.y[esi], ax	; _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_
	CPatch::PatchPointer(0x4995BC + 3, &CSetPieces__aSetPieces->m_nAreaCorner.m_vSup.x);	// mov     word ptr _ZN10CSetPieces10aSetPiecesE.m_nAreaCorner.m_vSup.x[esi], ax	; _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_
	CPatch::PatchPointer(0x4995D2 + 3, &CSetPieces__aSetPieces->m_nAreaCorner.m_vSup.y);	// mov     _ZN10CSetPieces10aSetPiecesE.m_nAreaCorner.m_vSup.y[esi], ax	; _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_
	CPatch::PatchPointer(0x4995E8 + 3, &CSetPieces__aSetPieces->m_nSpawnBox.m_vInf.x);	// mov     word ptr _ZN10CSetPieces10aSetPiecesE.m_nSpawnBox.m_vInf.x[esi], ax	; _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_
	CPatch::PatchPointer(0x4995FE + 3, &CSetPieces__aSetPieces->m_nSpawnBox.m_vInf.y);	// mov     _ZN10CSetPieces10aSetPiecesE.m_nSpawnBox.m_vInf.y[esi], ax	; _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_
	CPatch::PatchPointer(0x499614 + 3, &CSetPieces__aSetPieces->m_nTargetBox.m_vInf.x);	// mov     word ptr _ZN10CSetPieces10aSetPiecesE.m_nTargetBox.m_vInf.x[esi], ax	; _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_
	CPatch::PatchPointer(0x49962A + 3, &CSetPieces__aSetPieces->m_nTargetBox.m_vInf.y);	// mov     _ZN10CSetPieces10aSetPiecesE.m_nTargetBox.m_vInf.y[esi], ax	; _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_
	CPatch::PatchPointer(0x499640 + 3, &CSetPieces__aSetPieces->m_nSpawnBox.m_vSup.x);	// mov     word ptr _ZN10CSetPieces10aSetPiecesE.m_nSpawnBox.m_vSup.x[esi], ax	; _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_
	CPatch::PatchPointer(0x499656 + 3, &CSetPieces__aSetPieces->m_nSpawnBox.m_vSup.y);	// mov     _ZN10CSetPieces10aSetPiecesE.m_nSpawnBox.m_vSup.y[esi], ax	; _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_
	CPatch::PatchPointer(0x49966C + 3, &CSetPieces__aSetPieces->m_nTargetBox.m_vSup.x);	// mov     word ptr _ZN10CSetPieces10aSetPiecesE.m_nTargetBox.m_vSup.x[esi], ax	; _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_
	CPatch::PatchPointer(0x499679 + 3, &CSetPieces__aSetPieces->m_nTargetBox.m_vSup.y);	// mov     _ZN10CSetPieces10aSetPiecesE.m_nTargetBox.m_vSup.y[esi], ax	; _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_
	CPatch::PatchPointer(0x5D3C81 + 1, CSetPieces__aSetPieces);	// push    offset _ZN10CSetPieces10aSetPiecesE; pSource	; _ZN10CSetPieces4SaveEv
	CPatch::PatchPointer(0x5D3CB1 + 1, CSetPieces__aSetPieces);	// push    offset _ZN10CSetPieces10aSetPiecesE; ptr	; _ZN10CSetPieces4LoadEv
	CPatch::PatchPointer(0x84B1C0 + 1, CSetPieces__aSetPieces);	// mov     eax, offset _ZN10CSetPieces10aSetPiecesE;
}


namespace Game_GTASA
{
#ifdef IS_PLATFORM_WIN_X86
	unsigned int sizeof_CSetPiece;

	void* CSetPieces__Update_pointToReturn;

	NAKED void patch_CSetPieces__Update_49AA37()
	{
		__asm
		{
			mov     edi, esi;
			imul edi, sizeof_CSetPiece;
			add edi, ASM_ACCESS_LIMIT_VAR_32_BIT(g_otherLimits, OtherLimits, CSetPieces__aSetPieces);
			jmp CSetPieces__Update_pointToReturn;
		}
	}

	template<typename T> NAKED void patch_CSetPiece__Update_499B57()
	{
		_asm
		{
			movzx   eax, byte ptr[esi + T::m_nType];
			dec eax;

			push 0x499B5C;
			retn;
		}
	}

	template<typename T> NAKED void patch_CSetPiece__Update_499C25()
	{
		__asm
		{
			mov al, [esi + T::m_nType];
			mov     bl, 8;

			push 0x499C2A;
			retn;
		}
	}

	template<typename T> NAKED void patch_CSetPiece__Update_499CD3()
	{
		__asm
		{
			mov al, [esi + T::m_nType];
			add esp, 4;

			push 0x499CD9;
			retn;
		}
	}
#endif

	void SetCompressedBox2DextendedByStandard(
		CompressedBox2D_extended* pExtended,
		CompressedBox2D* pStandard
	)
	{
		pExtended->m_vInf.x = pStandard->m_vInf.x;
		pExtended->m_vInf.y = pStandard->m_vInf.y;

		pExtended->m_vSup.x = pExtended->m_vSup.x;
		pExtended->m_vSup.y = pExtended->m_vSup.y;
	}

	bool CSetPieces__Load_CheckLimit(		
		unsigned NumSetPiecesInSaveFile,
		unsigned NumSetPiecesLimit
	)
	{
		if (NumSetPiecesInSaveFile > NumSetPiecesLimit)
		{
			printf_MessageBox(
				"Selected savefile has %d set pieces. Current limit (%d) is too low.",
				NumSetPiecesInSaveFile,
				NumSetPiecesLimit
			);
			return false;
		}
		else		
			return true;
	}

	const unsigned int NUM_SET_PIECES_FASTMAN92_EXTENDED_FORMAT = 0xFFFFFFFF;
	const unsigned int NUM_SET_PIECES_FASTMAN92_NOT_EXTENDED_FORMAT = 0xFFFFFFFE;

	static unsigned int* CSetPieces__NumSetPieces = (unsigned int*)0xA957FC;

	// CSetPieces::Load replacement
	bool CSetPieces__Load()
	{		
		unsigned int NumSetPieces;

		CGenericGameStorage::LoadDataFromWorkBuffer(&NumSetPieces, sizeof(NumSetPieces));

		if (NumSetPieces == NUM_SET_PIECES_FASTMAN92_EXTENDED_FORMAT)	// fastman92, extended format?
		{
			if (!g_otherLimits.bSetPiecesCoordinatePatchEnabled)
			{
				printf_MessageBox("Selected savefile requires set pieces coordinate patch enabled.");
				return false;
			}

			CGenericGameStorage::LoadDataFromWorkBuffer(&NumSetPieces, sizeof(NumSetPieces));

			if (!CSetPieces__Load_CheckLimit(NumSetPieces, g_otherLimits.ms_iSetPiecesLimit))
				return false;

			*CSetPieces__NumSetPieces = NumSetPieces;

			CGenericGameStorage::LoadDataFromWorkBuffer(
				g_otherLimits.CSetPieces__aSetPieces.gta_sa_extended,
				NumSetPieces * sizeof(CSetPiece_extended));
		}
		else
		{
			bool bIsFastman92_not_extended_format = NumSetPieces == NUM_SET_PIECES_FASTMAN92_NOT_EXTENDED_FORMAT;

			if(bIsFastman92_not_extended_format)
				CGenericGameStorage::LoadDataFromWorkBuffer(&NumSetPieces, sizeof(NumSetPieces));

			if (!CSetPieces__Load_CheckLimit(NumSetPieces, g_otherLimits.ms_iSetPiecesLimit))
				return false;

			*CSetPieces__NumSetPieces = NumSetPieces;

			CSetPiece setPiece;

			if (g_otherLimits.bSetPiecesCoordinatePatchEnabled)
			{
				for (unsigned int i = 0; i < NumSetPieces; i++)
				{
					CGenericGameStorage::LoadDataFromWorkBuffer(
						&setPiece,
						sizeof(CSetPiece));

					CSetPiece_extended* pSetPiece =
						g_otherLimits.CSetPieces__aSetPieces.gta_sa_extended + i;

					// convert
					pSetPiece->m_nLastGenerationTime = setPiece.m_nLastGenerationTime;
					SetCompressedBox2DextendedByStandard(&pSetPiece->m_nAreaCorner, &setPiece.m_nAreaCorner);
					SetCompressedBox2DextendedByStandard(&pSetPiece->m_nSpawnBox, &setPiece.m_nSpawnBox);
					SetCompressedBox2DextendedByStandard(&pSetPiece->m_nTargetBox, &setPiece.m_nTargetBox);
					pSetPiece->m_nType = setPiece.m_nType;
				}
			}
			else
			{
				CGenericGameStorage::LoadDataFromWorkBuffer(
					g_otherLimits.CSetPieces__aSetPieces.gta_sa_standard,
					NumSetPieces * sizeof(CSetPiece));
			}

			if (!bIsFastman92_not_extended_format)
			{
				unsigned int numberOfRemainingEmptyPieces = 210 - NumSetPieces;

				for (unsigned int i = 0; i < numberOfRemainingEmptyPieces; i++)
					CGenericGameStorage::LoadDataFromWorkBuffer(
						&setPiece,
						sizeof(CSetPiece));
			}
		}

		return true;
	}

	// Patches pointer to CSetPieces::aSetPieces
	template<typename T>
	void CSetPieces__Save_DoTheJob(
		unsigned int format,
		T* CSetPieces__aSetPieces
	)
	{
		CGenericGameStorage::SaveDataToWorkBuffer(
			&format,
			sizeof(format));

		CGenericGameStorage::SaveDataToWorkBuffer(
			CSetPieces__NumSetPieces,
			sizeof(CSetPieces__NumSetPieces));

		CGenericGameStorage::SaveDataToWorkBuffer(
			g_otherLimits.CSetPieces__aSetPieces.gta_sa_extended,
			*CSetPieces__NumSetPieces * sizeof(T));
	}

	// CSetPieces::Save replacement
	bool CSetPieces__Save()
	{
		if (g_otherLimits.bSetPiecesCoordinatePatchEnabled)
			CSetPieces__Save_DoTheJob(
				NUM_SET_PIECES_FASTMAN92_EXTENDED_FORMAT,
				g_otherLimits.CSetPieces__aSetPieces.gta_sa_extended
			);
		else
			CSetPieces__Save_DoTheJob(
				NUM_SET_PIECES_FASTMAN92_NOT_EXTENDED_FORMAT,
				g_otherLimits.CSetPieces__aSetPieces.gta_sa_standard
			);

		return true;
	}
}


// Sets max number of set pieces
// requested by dkluin
void OtherLimits::SetMaxNumberOfSetPieces(unsigned int iSetPieces, bool bCoordinateHack)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
	{
		iSetPieces = this->ms_iSetPiecesLimit;
		bCoordinateHack = false;
	}
	
	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		if (iSetPieces > this->ms_iSetPiecesLimit || bCoordinateHack)
		{
			if (bCoordinateHack)
				CSetPieces__aSetPieces.gta_sa_extended = new CSetPiece_extended[iSetPieces];
			else
				CSetPieces__aSetPieces.gta_sa_standard = new CSetPiece[iSetPieces];

			CSetPieces__aSetPieces.bIsAllocated.Set(true);
			
			///////////
			g_SaveOfVariableLength.MakeSaveOfVariableLength();

			CPatch::RedirectFunction(0x5D3C70, &CSetPieces__Save);

			CGenericLogStorage::SaveFormattedTextLn(
				"Format of new savefiles will be different: patch for set pieces is applied.\n");
		}

		// Patch pointers to CSetPieces::aSetPieces
		if (bCoordinateHack)
			SetMaxNumberOfSetPiecesPatchPointersToIs_GTA_SA_1_0_PC(
				gameVersion,
				CSetPieces__aSetPieces.gta_sa_extended
			);
		else
			SetMaxNumberOfSetPiecesPatchPointersToIs_GTA_SA_1_0_PC(
				gameVersion,
				CSetPieces__aSetPieces.gta_sa_standard
			);
		
		// Patch count (210)
		#if TRUE
		{
			// CSetPieces::aSetPieces constructor
			CPatch::PatchUINT32(0x84B1C5 + 1, iSetPieces);	// mov     ecx, 210

			// CSetPieces::AddOne
			CPatch::PatchUINT32(0x499507 + 2, iSetPieces);	// cmp     edi, 210
		}
		#endif

		// Patch size of CSetPiece
		sizeof_CSetPiece = bCoordinateHack
			? sizeof(CSetPiece_extended) : sizeof(CSetPiece);

		#if TRUE
		{
			// CSetPieces::aSetPieces constructor
			CPatch::PatchUINT8(0x84B1D5 + 2, sizeof_CSetPiece);
		}
		#endif

		// CSetPieces::Update
		if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_COMPACT_WIN_X86)
		{
			CSetPieces__Update_pointToReturn = (void*)0x49AA42;
			CPatch::RedirectCode(0x49AA37, &patch_CSetPieces__Update_49AA37);

			CPatch::PatchUINT8(0x49AA5C + 2, sizeof_CSetPiece);
		}
		else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
		{
			CSetPieces__Update_pointToReturn = (void*)0x1569CA2;
			CPatch::RedirectCode(0x1569C87, &patch_CSetPieces__Update_49AA37);

			CPatch::PatchUINT8(0x1569CBC + 2, sizeof_CSetPiece);
		}

		// Patch size of CSetPiece
		CCodeMover::SetVariable("SIZEOF_CSETPIECE", sizeof_CSetPiece);

		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddressRel(0x499522, 9, "\x0e\x06\x02""SIZEOF_CSETPIECE\x00\x13\x06\x25\x95\x09\x00\x00", 0x49952B);	// line 1, 0x499500 - _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_ : shl     esi, 5
		}
		#endif		

		// If coordinate patch enabled
		if (bCoordinateHack)
		{
			// Patch offset of m_nType
			#if TRUE
			{
				CPatch::RedirectCode(
					0x499B57,
					&patch_CSetPiece__Update_499B57<CSetPiece_extended>
				);

				CPatch::RedirectCode(
					0x499C25,
					&patch_CSetPiece__Update_499C25<CSetPiece_extended>
				);
				
				CPatch::RedirectCode(
					0x499CD3,
					&patch_CSetPiece__Update_499CD3<CSetPiece_extended>
				);
			}
			#endif

			// Set variables for automatic patch
			#if TRUE
			{
				CCodeMover::SetVariable("CSETPIECE_AREA_CORNER_OFFSET", offsetof(CSetPiece_extended, m_nAreaCorner));

				CCodeMover::SetVariable(
					"ASETPIECES_AREA_CORNER_PTR",
					&CSetPieces__aSetPieces.gta_sa_extended->m_nAreaCorner
				);

				//////

				CCodeMover::SetVariable("CSETPIECE_SPAWN_BOX_OFFSET", offsetof(CSetPiece_extended, m_nSpawnBox));

				CCodeMover::SetVariable(
					"ASETPIECES_SPAWN_BOX_PTR",
					&CSetPieces__aSetPieces.gta_sa_extended->m_nSpawnBox
				);
				
				/////

				CCodeMover::SetVariable("CSETPIECE_TARGET_BOX_OFFSET", offsetof(CSetPiece_extended, m_nTargetBox));

				CCodeMover::SetVariable(
					"ASETPIECES_TARGET_BOX_PTR",
					&CSetPieces__aSetPieces.gta_sa_extended->m_nTargetBox
				);
			}
			#endif

			// Apply automatic patch
			#if TRUE
			{
				// Count of active addresses: 52
				CCodeMover::FixOnAddressRel(0x499566, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x00\x00\x00\x00\x02""ASETPIECES_AREA_CORNER_PTR\x00\x00", 0x49956D);	// line 1, 0x499500 - _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_ : mov     word ptr _ZN10CSetPieces10aSetPiecesE.m_nAreaCorner.m_vInf.x[esi], ax
				CCodeMover::FixOnAddressRel(0x49957A, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x04\x00\x00\x00\x02""ASETPIECES_AREA_CORNER_PTR\x00\x00", 0x499581);	// line 2, 0x499500 - _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_ : mov     _ZN10CSetPieces10aSetPiecesE.m_nAreaCorner.m_vInf.y[esi], ax
				CCodeMover::FixOnAddressRel(0x4995BC, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x08\x00\x00\x00\x02""ASETPIECES_AREA_CORNER_PTR\x00\x00", 0x4995C3);	// line 3, 0x499500 - _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_ : mov     word ptr _ZN10CSetPieces10aSetPiecesE.m_nAreaCorner.m_vSup.x[esi], ax
				CCodeMover::FixOnAddressRel(0x4995D2, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x0C\x00\x00\x00\x02""ASETPIECES_AREA_CORNER_PTR\x00\x00", 0x4995D9);	// line 4, 0x499500 - _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_ : mov     _ZN10CSetPieces10aSetPiecesE.m_nAreaCorner.m_vSup.y[esi], ax
				CCodeMover::FixOnAddressRel(0x4995E8, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x00\x00\x00\x00\x02""ASETPIECES_SPAWN_BOX_PTR\x00\x00", 0x4995EF);	// line 5, 0x499500 - _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_ : mov     word ptr _ZN10CSetPieces10aSetPiecesE.m_nSpawnBox.m_vInf.x[esi], ax
				CCodeMover::FixOnAddressRel(0x4995FE, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x04\x00\x00\x00\x02""ASETPIECES_SPAWN_BOX_PTR\x00\x00", 0x499605);	// line 6, 0x499500 - _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_ : mov     _ZN10CSetPieces10aSetPiecesE.m_nSpawnBox.m_vInf.y[esi], ax
				CCodeMover::FixOnAddressRel(0x499614, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x00\x00\x00\x00\x02""ASETPIECES_TARGET_BOX_PTR\x00\x00", 0x49961B);	// line 7, 0x499500 - _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_ : mov     word ptr _ZN10CSetPieces10aSetPiecesE.m_nTargetBox.m_vInf.x[esi], ax
				CCodeMover::FixOnAddressRel(0x49962A, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x04\x00\x00\x00\x02""ASETPIECES_TARGET_BOX_PTR\x00\x00", 0x499631);	// line 8, 0x499500 - _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_ : mov     _ZN10CSetPieces10aSetPiecesE.m_nTargetBox.m_vInf.y[esi], ax
				CCodeMover::FixOnAddressRel(0x499640, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x08\x00\x00\x00\x02""ASETPIECES_SPAWN_BOX_PTR\x00\x00", 0x499647);	// line 9, 0x499500 - _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_ : mov     word ptr _ZN10CSetPieces10aSetPiecesE.m_nSpawnBox.m_vSup.x[esi], ax
				CCodeMover::FixOnAddressRel(0x499656, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x0C\x00\x00\x00\x02""ASETPIECES_SPAWN_BOX_PTR\x00\x00", 0x49965D);	// line 10, 0x499500 - _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_ : mov     _ZN10CSetPieces10aSetPiecesE.m_nSpawnBox.m_vSup.y[esi], ax
				CCodeMover::FixOnAddressRel(0x49966C, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x08\x00\x00\x00\x02""ASETPIECES_TARGET_BOX_PTR\x00\x00", 0x499673);	// line 11, 0x499500 - _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_ : mov     word ptr _ZN10CSetPieces10aSetPiecesE.m_nTargetBox.m_vSup.x[esi], ax
				CCodeMover::FixOnAddressRel(0x499679, 7, "\x01\x01\x89\x01\x01\x86\x0d\x01\x04\x0C\x00\x00\x00\x02""ASETPIECES_TARGET_BOX_PTR\x00\x00", 0x499680);	// line 12, 0x499500 - _ZN10CSetPieces6AddOneEh9CVector2DS0_S0_S0_S0_S0_ : mov     _ZN10CSetPieces10aSetPiecesE.m_nTargetBox.m_vSup.y[esi], ax
				CCodeMover::FixOnAddressRel(0x4997A1, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x04\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x49\x0c\x01\x01\x00\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x00", 0x4997A9);	// line 13, 0x4997A0 - CSetPiece::GetSpawnBoxInf : movsx   eax, [ecx+CSetPiece.m_nSpawnBox.m_vInf.y]
				CCodeMover::FixOnAddressRel(0x4997E1, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x0c\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x49\x0c\x01\x01\x08\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x00", 0x4997E9);	// line 14, 0x4997E0 - CSetPiece::GetSpawnBoxSup : movsx   eax, [ecx+CSetPiece.m_nSpawnBox.m_vSup.y]
				CCodeMover::FixOnAddressRel(0x499821, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x04\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x49\x0c\x01\x01\x00\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x00", 0x499829);	// line 15, 0x499820 - CSetPiece::GetTargetBoxInf : movsx   eax, [ecx+CSetPiece.m_nTargetBox.m_vInf.y]
				CCodeMover::FixOnAddressRel(0x499861, 8, "\x01\x01\x8B\x01\x01\x41\x0c\x01\x01\x0c\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x49\x0c\x01\x01\x08\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x00", 0x499869);	// line 16, 0x499860 - CSetPiece::GetTargetBoxSup : movsx   eax, [ecx+CSetPiece.m_nTargetBox.m_vSup.y]
				CCodeMover::FixOnAddressRel(0x499AD0, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x00\x02""CSETPIECE_AREA_CORNER_OFFSET\x00\x13\x04\xD4\x9A\x09\x00\x00", 0x499AD8);	// line 17, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   ecx, [esi+CSetPiece.m_nAreaCorner.m_vInf.x]
				CCodeMover::FixOnAddressRel(0x499AF4, 8, "\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x08\x02""CSETPIECE_AREA_CORNER_OFFSET\x00\x13\x04\xF8\x9A\x09\x00\x00", 0x499AFC);	// line 18, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   edx, [esi+CSetPiece.m_nAreaCorner.m_vSup.x]
				CCodeMover::FixOnAddressRel(0x499B15, 8, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x04\x02""CSETPIECE_AREA_CORNER_OFFSET\x00\x13\x04\x19\x9B\x09\x00\x00", 0x499B1D);	// line 19, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   eax, [esi+CSetPiece.m_nAreaCorner.m_vInf.y]
				CCodeMover::FixOnAddressRel(0x499B36, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x0c\x02""CSETPIECE_AREA_CORNER_OFFSET\x00\x13\x04\x3A\x9B\x09\x00\x00", 0x499B3E);	// line 20, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   ecx, [esi+CSetPiece.m_nAreaCorner.m_vSup.y]
				CCodeMover::FixOnAddressRel(0x499C68, 8, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x00\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x04\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x00", 0x499C70);	// line 21, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   eax, [esi+CSetPiece.m_nTargetBox.m_vInf.x]
				CCodeMover::FixOnAddressRel(0x499D17, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x08\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x0c\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x00", 0x499D1F);	// line 22, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   ecx, [esi+CSetPiece.m_nTargetBox.m_vSup.x]
				CCodeMover::FixOnAddressRel(0x499DE1, 8, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x00\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x04\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x00", 0x499DE9);	// line 23, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   eax, [esi+CSetPiece.m_nSpawnBox.m_vInf.x]
				CCodeMover::FixOnAddressRel(0x499F49, 8, "\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x00\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x04\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x00", 0x499F51);	// line 24, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   edx, [esi+CSetPiece.m_nSpawnBox.m_vInf.x]
				CCodeMover::FixOnAddressRel(0x49A07F, 8, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x04\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x00\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x00", 0x49A087);	// line 25, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   eax, [esi+CSetPiece.m_nTargetBox.m_vInf.y]
				CCodeMover::FixOnAddressRel(0x49A0F0, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x04\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x00\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x00", 0x49A0F8);	// line 26, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   ecx, [esi+CSetPiece.m_nTargetBox.m_vInf.y]
				CCodeMover::FixOnAddressRel(0x49A1CF, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x04\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x00\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x00", 0x49A1D7);	// line 27, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   ecx, [esi+CSetPiece.m_nTargetBox.m_vInf.y]
				CCodeMover::FixOnAddressRel(0x49A246, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x04\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x00\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x00", 0x49A24E);	// line 28, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   ecx, [esi+CSetPiece.m_nTargetBox.m_vInf.y]
				CCodeMover::FixOnAddressRel(0x49A31D, 8, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x0c\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x08\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x00", 0x49A325);	// line 29, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   eax, [esi+CSetPiece.m_nTargetBox.m_vSup.y]
				CCodeMover::FixOnAddressRel(0x49A391, 8, "\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x04\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x00\x02""CSETPIECE_TARGET_BOX_OFFSET\x00\x00", 0x49A399);	// line 30, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   ecx, [esi+CSetPiece.m_nTargetBox.m_vInf.y]
				CCodeMover::FixOnAddressRel(0x49A4AC, 8, "\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x00\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x4E\x0c\x01\x01\x04\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x00", 0x49A4B4);	// line 31, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   eax, [esi+CSetPiece.m_nSpawnBox.m_vInf.x]
				CCodeMover::FixOnAddressRel(0x49A5FB, 8, "\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x08\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x0c\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x00", 0x49A603);	// line 32, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   edx, [esi+CSetPiece.m_nSpawnBox.m_vSup.x]
				CCodeMover::FixOnAddressRel(0x49A725, 8, "\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x00\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x04\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x00", 0x49A72D);	// line 33, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   edx, [esi+CSetPiece.m_nSpawnBox.m_vInf.x]
				CCodeMover::FixOnAddressRel(0x49A86E, 8, "\x01\x01\x8B\x01\x01\x56\x0c\x01\x01\x08\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x01\x01\x8B\x01\x01\x46\x0c\x01\x01\x0c\x02""CSETPIECE_SPAWN_BOX_OFFSET\x00\x00", 0x49A876);	// line 34, 0x499A80 - _ZN9CSetPiece6UpdateEv : movsx   edx, [esi+CSetPiece.m_nSpawnBox.m_vSup.x]
			}
			#endif

			// Unset variables of automatic patch
			#if TRUE
			{
				CCodeMover::DeleteVariable("CSETPIECE_AREA_CORNER_OFFSET");
				CCodeMover::DeleteVariable("ASETPIECES_AREA_CORNER_PTR");

				CCodeMover::DeleteVariable("CSETPIECE_SPAWN_BOX_OFFSET");
				CCodeMover::DeleteVariable("ASETPIECES_SPAWN_BOX_PTR");

				CCodeMover::DeleteVariable("CSETPIECE_TARGET_BOX_OFFSET");
				CCodeMover::DeleteVariable("ASETPIECES_TARGET_BOX_PTR");
			}
			#endif
		}

		CCodeMover::DeleteVariable("SIZEOF_CSETPIECE");
	}
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_iSetPiecesLimit = iSetPieces;
	this->bSetPiecesCoordinatePatchEnabled = bCoordinateHack;
	
	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of OTHER LIMITS: Set pieces active: %d"
		" bCoordinateHack: %d",
		iSetPieces, bCoordinateHack
	);
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

// Patches loading functions
void OtherLimits::PatchSaveBlockLoadingFunctions()
{
	MAKE_VAR_GAME_VERSION();
	
	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86	
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		CPatch::RedirectFunction(0x5D53C0, &CRadar__Load);

		CPatch::RedirectFunction(0x5D3CA0, &CSetPieces__Load);
	}
#endif
}

// Initialize
void OtherLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	this->bIsVehicleColorIDextended = false;

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		using namespace Game_GTASA;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				// array of references
				this->CReferences__aRefs.gta_sa = (CReference*)0xB9B9A8;
			}
			#elif defined(IS_PLATFORM_ANDROID)
			// array of references
			this->CReferences__aRefs.gta_sa = (CReference*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN11CReferences5aRefsE"
			);
			#endif
		}
		

		// References
		this->ms_iReferencesLimit = 3000;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				// Cover points
				this->CCover__m_aPoints.gta_sa = (CCoverPoint*)0xC197C8;				
			}
			#endif
		}

		// Cover point limit
		this->ms_iCoverPointLimit = 100;

		// Number of plate textures
		this->ms_iNumberOfPlateTextures = 3;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				// Plateback textures
				this->CustomCarPlateMgr__pPlatebackTexTab.ptr = (void**)0xC3EF60;

				// Coronas
				this->CCoronas__aCoronas.gta_sa = (CRegisteredCorona*)0xC3E058;
			}
			#elif defined(IS_PLATFORM_ANDROID)
			this->CCoronas__aCoronas.gta_sa = (CRegisteredCorona*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN8CCoronas8aCoronasE"
			);
			#endif
		}

		// Coronas limit
		this->ms_iCoronasLimit = 64;

		// Max size of single collision
		this->ms_maxSizeOfSingleCollision = 32768;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				// COL file read buffer
				this->ms_pColfileReadBuffer.ptr = (char*)0xBC40D8;				
			}
			#elif defined(IS_PLATFORM_ANDROID_ARM32)
			if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
			{
				// COL file read buffer
				this->ms_pColfileReadBuffer.ptr = (char*)g_mCalc.GetCurrentVAbyPreferedVA(0x9B2280);
			}
			#endif
		}

		// Object info entry limit
		this->ms_iObjectInfoLimit = 160;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				// Object info array
				this->CObjectData__ms_aObjectInfo.gta_sa = (CObjectInfo*)0xBB4A90;
			}
			#elif defined(IS_PLATFORM_ANDROID)
			// Object info array
			this->CObjectData__ms_aObjectInfo.gta_sa = (CObjectInfo*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN11CObjectData14ms_aObjectInfoE"
			);
			#endif
		}

		// Vehicle colors limit
		this->ms_iVehicleColorsLimit = 128;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				// Vehicle colors array
				this->CVehicleModelInfo__ms_vehicleColourTable.gta_sa = (CRGBA*)0xB4E480;
			}
			#elif defined(IS_PLATFORM_ANDROID)
			// Vehicle colors array
			this->CVehicleModelInfo__ms_vehicleColourTable.gta_sa = (CRGBA*)Library::GetSymbolAddress(
				&g_LimitAdjuster.hModule_of_game,
				"_ZN17CVehicleModelInfo21ms_vehicleColourTableE"
			);
			#endif
		}

		// LOD distance
		this->LODdistance = 300.0;

		// Radar traces limit
		this->ms_iRadarTracesLimit = 175;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				// Radar traces array
				this->CRadar__ms_RadarTrace.gta_sa = (CMarker*)0xBA86F0;

				// Radar map legend list
				this->CRadar__MapLegendList.ptr = (int16_t*)0xBA8318;
			}
			#endif
		}

		// Max number of particles active
		this->ms_iMaxNumberOfParticlesActive = 1000;

		// Set pieces
		this->ms_iSetPiecesLimit = 210;
		this->bSetPiecesCoordinatePatchEnabled = false;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
				this->CSetPieces__aSetPieces.gta_sa_standard = (CSetPiece*)0xA95818;
			#endif
		}
	}
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
	{
		// Vehicle colors limit
		this->ms_iVehicleColorsLimit = 196;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (gameVersion == GAME_VERSION_GTA_IV_1_0_4_0_WIN_X86)
			{
				// Vehicle colors array
				this->CVehicleModelInfo__ms_vehicleColourTable.gta_iv = (CBGRA*)g_mCalc.GetCurrentVAbyPreferedVA(0x1469170);

				// Police scanner prefix table
				this->CVehicleModelInfo__ms_policeScannerPrefixTable.ptr = (uint32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x1468E50);

				// Police scanner colour table
				this->CVehicleModelInfo__ms_policeScannerColourTable.ptr = (uint32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x1468B40);
			}
			else if (gameVersion == GAME_VERSION_GTA_IV_1_0_7_0_WIN_X86)
			{
				// Vehicle colors array
				this->CVehicleModelInfo__ms_vehicleColourTable.gta_iv = (CBGRA*)g_mCalc.GetCurrentVAbyPreferedVA(0x16D65A8);

				// Police scanner prefix table
				this->CVehicleModelInfo__ms_policeScannerPrefixTable.ptr = (uint32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x16D6280);

				// Police scanner colour table
				this->CVehicleModelInfo__ms_policeScannerColourTable.ptr = (uint32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x16D5F70);				
			}
			else if (gameVersion == GAME_VERSION_GTA_IV_1_0_8_0_WIN_X86)
			{
				// Vehicle colors array
				this->CVehicleModelInfo__ms_vehicleColourTable.gta_iv = (CBGRA*)g_mCalc.GetCurrentVAbyPreferedVA(0x1401BE0);

				// Police scanner prefix table
				this->CVehicleModelInfo__ms_policeScannerPrefixTable.ptr = (uint32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x14018B8);

				// Police scanner colour table
				this->CVehicleModelInfo__ms_policeScannerColourTable.ptr = (uint32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x14015A8);
			}
			else if (gameVersion == GAME_VERSION_GTA_EFLC_1_1_2_0_WIN_X86)
			{
				// Vehicle colors array
				this->CVehicleModelInfo__ms_vehicleColourTable.gta_iv = (CBGRA*)g_mCalc.GetCurrentVAbyPreferedVA(0x1606B58);

				// Police scanner prefix table
				this->CVehicleModelInfo__ms_policeScannerPrefixTable.ptr = (uint32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x1606830);

				// Police scanner colour table
				this->CVehicleModelInfo__ms_policeScannerColourTable.ptr = (uint32_t*)g_mCalc.GetCurrentVAbyPreferedVA(0x1606520);				
			}
			#endif
		}
	}
}

// Shutdown
void OtherLimits::Shutdown()
{
	MAKE_VAR_GAME_VERSION();

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		if (CReferences__aRefs.bIsAllocated.Get())
			delete[] CReferences__aRefs.gta_sa;

		if (CCover__m_aPoints.bIsAllocated.Get())
			delete[] CCover__m_aPoints.gta_sa;
		
		if (CCoronas__aCoronas.bIsAllocated.Get())
			delete[] CCoronas__aCoronas.gta_sa;

		if (CObjectData__ms_aObjectInfo.bIsAllocated.Get())
			delete[] CObjectData__ms_aObjectInfo.gta_sa;

		if (CVehicleModelInfo__ms_vehicleColourTable.bIsAllocated.Get())
			delete[] CVehicleModelInfo__ms_vehicleColourTable.gta_sa;

		if (CRadar__ms_RadarTrace.bIsAllocated.Get())
			delete[] CRadar__ms_RadarTrace.gta_sa;
	}
	else if (CGameVersion::IsAny_GTA_IV_or_EFLC(gameVersion))
	{
		if (CVehicleModelInfo__ms_vehicleColourTable.bIsAllocated.Get())
			delete[] CVehicleModelInfo__ms_vehicleColourTable.gta_iv;
	}

	if (CustomCarPlateMgr__pPlatebackTexTab.bIsAllocated.Get())
		delete[] CustomCarPlateMgr__pPlatebackTexTab.ptr;

	if (ms_pColfileReadBuffer.bIsAllocated.Get())
		delete[] ms_pColfileReadBuffer.ptr;

	if (CRadar__MapLegendList.bIsAllocated.Get())
		delete[] CRadar__MapLegendList.ptr;

	if (CVehicleModelInfo__ms_policeScannerPrefixTable.bIsAllocated.Get())
		delete[] CVehicleModelInfo__ms_policeScannerPrefixTable.ptr;

	if (CVehicleModelInfo__ms_policeScannerColourTable.bIsAllocated.Get())
		delete[] CVehicleModelInfo__ms_policeScannerColourTable.ptr;

	if (CSetPieces__aSetPieces.bIsAllocated.Get())
		delete[] CSetPieces__aSetPieces.generic;
}
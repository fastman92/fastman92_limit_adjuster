/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "ShadowLimits.h"
#include "../Core/CPatch.h"
#include "../Core/CCodeMover.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

#include <MultiPlatformSupport/PlatformGeneralisation.h>

using namespace Game;

ShadowLimits g_shadowLimits;

// GTA San Andreas
namespace Game_GTASA
{
	MAKE_CRealTimeShadowManager(CRealTimeShadowManager, STRUCTURE_STATIC_MEMBER_DEFINITION);
}

// Sets shadows stored
void ShadowLimits::SetShadowStored(unsigned int iShadowStoredLimit)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iShadowStoredLimit = this->ms_ShadowsStoredLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		// Allocate if neccessary
		if (iShadowStoredLimit > this->ms_ShadowsStoredLimit)
		{
			CShadows__asShadowsStored.gta_sa = new CStoredShadow[iShadowStoredLimit];
			memset(CShadows__asShadowsStored.gta_sa, NULL, iShadowStoredLimit * sizeof(CStoredShadow));
			CShadows__asShadowsStored.bIsAllocated.Set(true);
		}		

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x7073B0 + 1, CShadows__asShadowsStored.gta_sa);	// add     eax, offset _ZN8CShadows15asShadowsStoredE; CShadows::asShadowsStored	; sub_707390
			CPatch::PatchPointer(0x70A9EE + 1, &CShadows__asShadowsStored.gta_sa->Flags);	// mov     eax, offset _ZN8CShadows15asShadowsStoredE.Flags	; sub_70A960
			CPatch::PatchPointer(0x70AA10 + 2, &CShadows__asShadowsStored.gta_sa->Flags);	// mov     al, byte ptr ss:_ZN8CShadows15asShadowsStoredE.Flags[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70AA18 + 2, &CShadows__asShadowsStored.gta_sa->pTexture);	// lea     esi, _ZN8CShadows15asShadowsStoredE.pTexture[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B0EF + 3, &CShadows__asShadowsStored.gta_sa->Intensity);	// movsx   ecx, ss:_ZN8CShadows15asShadowsStoredE.Intensity[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B166 + 3, &CShadows__asShadowsStored.gta_sa->ColorBlue);	// movzx   ecx, ss:_ZN8CShadows15asShadowsStoredE.ColorBlue[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B17A + 3, &CShadows__asShadowsStored.gta_sa->ColorGreen);	// movzx   eax, ss:_ZN8CShadows15asShadowsStoredE.ColorGreen[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B18D + 2, &CShadows__asShadowsStored.gta_sa->ColorRed);	// mov     dl, ss:_ZN8CShadows15asShadowsStoredE.ColorRed[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B23A + 3, &CShadows__asShadowsStored.gta_sa->Intensity);	// movsx   eax, ss:_ZN8CShadows15asShadowsStoredE.Intensity[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B2B1 + 3, &CShadows__asShadowsStored.gta_sa->ColorGreen);	// movzx   edx, ss:_ZN8CShadows15asShadowsStoredE.ColorGreen[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B2C2 + 3, &CShadows__asShadowsStored.gta_sa->ColorBlue);	// movzx   eax, ss:_ZN8CShadows15asShadowsStoredE.ColorBlue[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B2D1 + 2, &CShadows__asShadowsStored.gta_sa->ColorRed);	// mov     cl, ss:_ZN8CShadows15asShadowsStoredE.ColorRed[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B38E + 3, &CShadows__asShadowsStored.gta_sa->Intensity);	// movsx   edx, ss:_ZN8CShadows15asShadowsStoredE.Intensity[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B404 + 3, &CShadows__asShadowsStored.gta_sa->ColorGreen);	// movzx   edx, ss:_ZN8CShadows15asShadowsStoredE.ColorGreen[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B40F + 2, &CShadows__asShadowsStored.gta_sa->ColorRed);	// mov     cl, ss:_ZN8CShadows15asShadowsStoredE.ColorRed[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B424 + 3, &CShadows__asShadowsStored.gta_sa->ColorBlue);	// movzx   eax, ss:_ZN8CShadows15asShadowsStoredE.ColorBlue[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B4EA + 3, &CShadows__asShadowsStored.gta_sa->Intensity);	// movsx   edx, ss:_ZN8CShadows15asShadowsStoredE.Intensity[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B569 + 3, &CShadows__asShadowsStored.gta_sa->ColorGreen);	// movzx   edx, ss:_ZN8CShadows15asShadowsStoredE.ColorGreen[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B578 + 3, &CShadows__asShadowsStored.gta_sa->ColorBlue);	// movzx   eax, ss:_ZN8CShadows15asShadowsStoredE.ColorBlue[ebp]	; sub_70A960
			CPatch::PatchPointer(0x70B594 + 2, &CShadows__asShadowsStored.gta_sa->ColorRed);	// mov     cl, ss:_ZN8CShadows15asShadowsStoredE.ColorRed[ebp]	; sub_70A960
		}
		#endif

		// Define variable for automatic patch
		CCodeMover::SetVariable("SHADOW_STORED_LIMIT", iShadowStoredLimit);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddressRel(0x707398, 10, "\x01\x03\x66\x81\xfe\x05\x02""SHADOW_STORED_LIMIT\x00\x01\x02\x0F\x83\x0F\x49\x74\x70\x00\x00", 0x7073A2);	// line 1, 0x707390 - _ZN8CShadows23StoreShadowToBeRenderedEhP9RwTextureP7CVectorffffshhhfbfP15CRealTimeShadowb : cmp     si, 30h
		}
		#endif

		// Delete a variable
		CCodeMover::DeleteVariable("SHADOW_STORED_LIMIT");
	}
	#elif defined(IS_PLATFORM_ANDROID_ARM32)

	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_ShadowsStoredLimit = iShadowStoredLimit;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of SHADOW LIMITS: Permanent shadows to: %d",
		iShadowStoredLimit
		);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Sets poly bunches
void ShadowLimits::SetPolyBunches(unsigned int iPolyBunchesLimit)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPolyBunchesLimit = this->ms_PolyBunchesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		// Allocate if neccessary
		if (iPolyBunchesLimit > this->ms_PolyBunchesLimit)
		{
			CShadows__aPolyBunches.gta_sa = new CPolyBunch[iPolyBunchesLimit];
			CShadows__aPolyBunches.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x706E8F + 6, CShadows__aPolyBunches.gta_sa);	// mov     _ZN8CShadows15pEmptyBunchListE, offset _ZN8CShadows12aPolyBunchesE; CShadows::pEmptyBunchList	; _ZN8CShadows4InitEv
			CPatch::PatchPointer(0x706E99 + 1, &CShadows__aPolyBunches.gta_sa->pNext);	// mov     eax, offset _ZN8CShadows12aPolyBunchesE.pNext	; _ZN8CShadows4InitEv
			CPatch::PatchPointer(0x706EA8 + 1, &CShadows__aPolyBunches.gta_sa[iPolyBunchesLimit - 1].pNext);	// cmp     eax, (offset _ZN8CShadows12aPolyBunchesE.pNext+91D8h)	; _ZN8CShadows4InitEv
			CPatch::PatchPointer(0x706EAF + 2, &CShadows__aPolyBunches.gta_sa[iPolyBunchesLimit - 1].pNext);	// mov     _ZN8CShadows12aPolyBunchesE.pNext+91D8h, ebx	; _ZN8CShadows4InitEv
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_PolyBunchesLimit = iPolyBunchesLimit;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of SHADOW LIMITS: Poly bunches to: %d",
		iPolyBunchesLimit
		);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Sets static shadows
void ShadowLimits::SetStaticShadows(unsigned int iStaticShadows)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iStaticShadows = this->ms_StaticShadowsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		// Allocate if neccessary
		if (iStaticShadows = this->ms_StaticShadowsLimit)
		{
			CShadows__aStaticShadows.gta_sa = new CStaticShadow[iStaticShadows];
			memset(CShadows__aStaticShadows.gta_sa, NULL, iStaticShadows * sizeof(CStaticShadow));
			CShadows__aStaticShadows.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x706E7A + 1, &CShadows__aStaticShadows.gta_sa->field_4);	// mov     eax, offset _ZN8CShadows14aStaticShadowsE.field_4	; _ZN8CShadows4InitEv
			CPatch::PatchPointer(0x706E88 + 1, &CShadows__aStaticShadows.gta_sa[iStaticShadows].field_4);	// cmp     eax, offset _ZN8CShadows17aPermanentShadowsE.Pos.y	; _ZN8CShadows4InitEv
			CPatch::PatchPointer(0x707F41 + 1, &CShadows__aStaticShadows.gta_sa->field_4);	// mov     ecx, offset _ZN8CShadows14aStaticShadowsE.field_4	; _ZN8CShadows19UpdateStaticShadowsEv
			CPatch::PatchPointer(0x707F96 + 2, &CShadows__aStaticShadows.gta_sa[iStaticShadows].field_4);	// cmp     ecx, offset _ZN8CShadows17aPermanentShadowsE.Pos.y	; _ZN8CShadows19UpdateStaticShadowsEv
			CPatch::PatchPointer(0x708361 + 1, &CShadows__aStaticShadows.gta_sa->field_3B);	// mov     eax, offset _ZN8CShadows14aStaticShadowsE.field_3B	; _ZN8CShadows19RenderStaticShadowsEb
			CPatch::PatchPointer(0x708376 + 1, &CShadows__aStaticShadows.gta_sa[iStaticShadows].field_3B);	// cmp     eax, (offset _ZN8CShadows17aPermanentShadowsE.Pos.z+33h)	; _ZN8CShadows19RenderStaticShadowsEb
			CPatch::PatchPointer(0x70837D + 1, &CShadows__aStaticShadows.gta_sa->field_36);	// mov     edi, offset _ZN8CShadows14aStaticShadowsE.field_36	; _ZN8CShadows19RenderStaticShadowsEb
			CPatch::PatchPointer(0x7083BC + 2, &CShadows__aStaticShadows.gta_sa[iStaticShadows].field_36);	// cmp     edi, (offset _ZN8CShadows17aPermanentShadowsE+36h)	; _ZN8CShadows19RenderStaticShadowsEb
			CPatch::PatchPointer(0x708614 + 2, &CShadows__aStaticShadows.gta_sa[iStaticShadows].field_4);	// cmp     ebp, offset _ZN8CShadows17aPermanentShadowsE.Pos.y	; _ZN8CShadows19RenderStaticShadowsEb
			CPatch::PatchPointer(0x70866E + 2, &CShadows__aStaticShadows.gta_sa[iStaticShadows].field_36);	// cmp     edi, (offset _ZN8CShadows17aPermanentShadowsE+36h)	; _ZN8CShadows19RenderStaticShadowsEb
			CPatch::PatchPointer(0x70B73E + 2, &CShadows__aStaticShadows.gta_sa->field_C);	// lea     eax, _ZN8CShadows14aStaticShadowsE.field_C[esi]	; _ZN8CShadows28GeneratePolysForStaticShadowEs
			CPatch::PatchPointer(0x70B746 + 2, &CShadows__aStaticShadows.gta_sa->field_20);	// fld     _ZN8CShadows14aStaticShadowsE.field_20[esi]	; _ZN8CShadows28GeneratePolysForStaticShadowEs
			CPatch::PatchPointer(0x70B751 + 2, &CShadows__aStaticShadows.gta_sa->field_18);	// fld     _ZN8CShadows14aStaticShadowsE.field_18[esi]	; _ZN8CShadows28GeneratePolysForStaticShadowEs
			CPatch::PatchPointer(0x70B76B + 2, &CShadows__aStaticShadows.gta_sa->field_24);	// fld     _ZN8CShadows14aStaticShadowsE.field_24[esi]	; _ZN8CShadows28GeneratePolysForStaticShadowEs
			CPatch::PatchPointer(0x70B77A + 2, &CShadows__aStaticShadows.gta_sa->field_1C);	// fld     _ZN8CShadows14aStaticShadowsE.field_1C[esi]	; _ZN8CShadows28GeneratePolysForStaticShadowEs
			CPatch::PatchPointer(0x70B931 + 2, &CShadows__aStaticShadows.gta_sa->field_3D);	// lea     ebx, _ZN8CShadows14aStaticShadowsE.field_3D[esi]	; _ZN8CShadows28GeneratePolysForStaticShadowEs
			CPatch::PatchPointer(0x70B937 + 2, &CShadows__aStaticShadows.gta_sa->field_4);	// lea     ebp, _ZN8CShadows14aStaticShadowsE.field_4[esi]	; _ZN8CShadows28GeneratePolysForStaticShadowEs
			CPatch::PatchPointer(0x70B966 + 2, &CShadows__aStaticShadows.gta_sa->field_2C);	// mov     edx, _ZN8CShadows14aStaticShadowsE.field_2C[esi]	; _ZN8CShadows28GeneratePolysForStaticShadowEs
			CPatch::PatchPointer(0x70B974 + 2, &CShadows__aStaticShadows.gta_sa->field_28);	// mov     edx, _ZN8CShadows14aStaticShadowsE.field_28[esi]	; _ZN8CShadows28GeneratePolysForStaticShadowEs
			CPatch::PatchPointer(0x70B97B + 2, &CShadows__aStaticShadows.gta_sa->field_24);	// mov     edx, _ZN8CShadows14aStaticShadowsE.field_24[esi]	; _ZN8CShadows28GeneratePolysForStaticShadowEs
			CPatch::PatchPointer(0x70B98A + 2, &CShadows__aStaticShadows.gta_sa->field_20);	// mov     edx, _ZN8CShadows14aStaticShadowsE.field_20[esi]	; _ZN8CShadows28GeneratePolysForStaticShadowEs
			CPatch::PatchPointer(0x70B991 + 2, &CShadows__aStaticShadows.gta_sa->field_1C);	// mov     edx, _ZN8CShadows14aStaticShadowsE.field_1C[esi]	; _ZN8CShadows28GeneratePolysForStaticShadowEs
			CPatch::PatchPointer(0x70B998 + 2, &CShadows__aStaticShadows.gta_sa->field_18);	// mov     edx, _ZN8CShadows14aStaticShadowsE.field_18[esi]	; _ZN8CShadows28GeneratePolysForStaticShadowEs
			CPatch::PatchPointer(0x70BB26 + 2, CShadows__aStaticShadows.gta_sa);	// cmp     ebx, dword ptr _ZN8CShadows14aStaticShadowsE[eax]; CShadows::aStaticShadows	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BB2E + 2, &CShadows__aStaticShadows.gta_sa->field_4);	// mov     ecx, _ZN8CShadows14aStaticShadowsE.field_4[eax]	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BB56 + 2, &CShadows__aStaticShadows.gta_sa->field_4);	// mov     eax, _ZN8CShadows14aStaticShadowsE.field_4[ecx]	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BB84 + 2, &CShadows__aStaticShadows.gta_sa->field_36);	// mov     _ZN8CShadows14aStaticShadowsE.field_36[esi], dl	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BB8E + 2, &CShadows__aStaticShadows.gta_sa->field_30);	// mov     _ZN8CShadows14aStaticShadowsE.field_30[esi], eax	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BB98 + 3, &CShadows__aStaticShadows.gta_sa->field_34);	// mov     word ptr _ZN8CShadows14aStaticShadowsE.field_34[esi], cx	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BBA3 + 2, &CShadows__aStaticShadows.gta_sa->field_37);	// mov     _ZN8CShadows14aStaticShadowsE.field_37[esi], dl	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BBAD + 2, &CShadows__aStaticShadows.gta_sa->field_38);	// mov     _ZN8CShadows14aStaticShadowsE.field_38[esi], al	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BBB7 + 2, &CShadows__aStaticShadows.gta_sa->field_39);	// mov     _ZN8CShadows14aStaticShadowsE.field_39[esi], cl	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BBBD + 2, &CShadows__aStaticShadows.gta_sa->field_28);	// mov     _ZN8CShadows14aStaticShadowsE.field_28[esi], edx	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BBC3 + 2, &CShadows__aStaticShadows.gta_sa->field_2C);	// mov     _ZN8CShadows14aStaticShadowsE.field_2C[esi], eax	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BBC9 + 2, CShadows__aStaticShadows.gta_sa);	// mov     dword ptr _ZN8CShadows14aStaticShadowsE[esi], ebx; CShadows::aStaticShadows	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BBD2 + 2, &CShadows__aStaticShadows.gta_sa->field_C);	// lea     ecx, _ZN8CShadows14aStaticShadowsE.field_C[esi]	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BBF2 + 2, &CShadows__aStaticShadows.gta_sa->field_18);	// mov     _ZN8CShadows14aStaticShadowsE.field_18[esi], eax	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BBFC + 2, &CShadows__aStaticShadows.gta_sa->field_1C);	// mov     _ZN8CShadows14aStaticShadowsE.field_1C[esi], ecx	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BC06 + 2, &CShadows__aStaticShadows.gta_sa->field_20);	// mov     _ZN8CShadows14aStaticShadowsE.field_20[esi], edx	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BC13 + 2, &CShadows__aStaticShadows.gta_sa->field_24);	// mov     _ZN8CShadows14aStaticShadowsE.field_24[esi], eax	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BC19 + 2, &CShadows__aStaticShadows.gta_sa->field_3A);	// mov     _ZN8CShadows14aStaticShadowsE.field_3A[esi], 1	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BC20 + 2, &CShadows__aStaticShadows.gta_sa->field_3C);	// mov     _ZN8CShadows14aStaticShadowsE.field_3C[esi], cl	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BC26 + 2, &CShadows__aStaticShadows.gta_sa->TimeCreated);	// mov     _ZN8CShadows14aStaticShadowsE.TimeCreated[esi], edx	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BC31 + 2, &CShadows__aStaticShadows.gta_sa->field_4);	// mov     eax, _ZN8CShadows14aStaticShadowsE.field_4[esi]	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BC5C + 2, &CShadows__aStaticShadows.gta_sa->field_C);	// fsub    _ZN8CShadows14aStaticShadowsE.field_C[ecx]	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BC72 + 2, &CShadows__aStaticShadows.gta_sa->field_10);	// fsub    _ZN8CShadows14aStaticShadowsE.field_10[ecx]	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BC99 + 2, &CShadows__aStaticShadows.gta_sa->field_10);	// fsub    _ZN8CShadows14aStaticShadowsE.field_10[ecx]	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BCB1 + 2, &CShadows__aStaticShadows.gta_sa->field_14);	// fsub    _ZN8CShadows14aStaticShadowsE.field_14[ecx]	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BCCA + 2, &CShadows__aStaticShadows.gta_sa->field_18);	// fcomp   _ZN8CShadows14aStaticShadowsE.field_18[ecx]	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BCDB + 2, &CShadows__aStaticShadows.gta_sa->field_1C);	// fcomp   _ZN8CShadows14aStaticShadowsE.field_1C[ecx]	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BCEC + 2, &CShadows__aStaticShadows.gta_sa->field_20);	// fcomp   _ZN8CShadows14aStaticShadowsE.field_20[ecx]	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BCFD + 2, &CShadows__aStaticShadows.gta_sa->field_24);	// fcomp   _ZN8CShadows14aStaticShadowsE.field_24[ecx]	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BD0A + 2, CShadows__aStaticShadows.gta_sa);	// lea     ecx, _ZN8CShadows14aStaticShadowsE[ecx]; this	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BD24 + 2, &CShadows__aStaticShadows.gta_sa->field_30);	// mov     _ZN8CShadows14aStaticShadowsE.field_30[ecx], eax	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BD2E + 2, &CShadows__aStaticShadows.gta_sa->field_36);	// mov     _ZN8CShadows14aStaticShadowsE.field_36[ecx], dl	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BD39 + 2, &CShadows__aStaticShadows.gta_sa->field_37);	// mov     _ZN8CShadows14aStaticShadowsE.field_37[ecx], al	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BD43 + 3, &CShadows__aStaticShadows.gta_sa->field_34);	// mov     word ptr _ZN8CShadows14aStaticShadowsE.field_34[ecx], dx	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BD4E + 2, &CShadows__aStaticShadows.gta_sa->field_39);	// mov     _ZN8CShadows14aStaticShadowsE.field_39[ecx], al	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BD59 + 2, &CShadows__aStaticShadows.gta_sa->field_38);	// mov     _ZN8CShadows14aStaticShadowsE.field_38[ecx], dl	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BD63 + 2, &CShadows__aStaticShadows.gta_sa->field_2C);	// mov     _ZN8CShadows14aStaticShadowsE.field_2C[ecx], eax	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BD6F + 2, &CShadows__aStaticShadows.gta_sa->field_28);	// mov     _ZN8CShadows14aStaticShadowsE.field_28[ecx], edx	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BD7A + 2, &CShadows__aStaticShadows.gta_sa->TimeCreated);	// mov     _ZN8CShadows14aStaticShadowsE.TimeCreated[ecx], eax	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BD80 + 2, &CShadows__aStaticShadows.gta_sa->field_3A);	// mov     _ZN8CShadows14aStaticShadowsE.field_3A[ecx], 1	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
			CPatch::PatchPointer(0x70BD87 + 2, &CShadows__aStaticShadows.gta_sa->field_3C);	// mov     _ZN8CShadows14aStaticShadowsE.field_3C[ecx], dl	; _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf
		}
		#endif

		// Define variable for automatic patch
		CCodeMover::SetVariable("STATIC_SHADOWS_LIMIT", iStaticShadows);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 5
			CCodeMover::FixOnAddressRel(0x70BB3D, 6, "\x01\x03\x66\x81\xff\x05\x02""STATIC_SHADOWS_LIMIT\x00\x01\x02\x0F\x8C\x0F\x20\xbb\x70\x00\x00", 0x70BB43);	// line 2, 0x70BA00 - _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf : cmp     di, 30h
			CCodeMover::FixOnAddressRel(0x70BB61, 6, "\x01\x03\x66\x81\xff\x05\x02""STATIC_SHADOWS_LIMIT\x00\x01\x02\x0F\x8C\x0F\x50\xbb\x70\x00\x00", 0x70BB67);	// line 3, 0x70BA00 - _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf : cmp     di, 30h
			CCodeMover::FixOnAddressRel(0x70BB67, 10, "\x01\x03\x66\x81\xff\x05\x02""STATIC_SHADOWS_LIMIT\x00\x01\x02\x0F\x84\x0F\x6f\xba\x70\x00\x00", 0x70BB71);	// line 4, 0x70BA00 - _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf : cmp     di, 30h
			CCodeMover::FixOnAddressRel(0x70BC49, 10, "\x01\x03\x66\x81\xff\x05\x02""STATIC_SHADOWS_LIMIT\x00\x01\x02\x0F\x8D\x0F\x43\xbb\x70\x00\x00", 0x70BC53);	// line 5, 0x70BA00 - _ZN8CShadows17StoreStaticShadowEjhP9RwTextureP7CVectorffffshhhfffbf : cmp     di, 48
		}
		#endif
		
		// Delete a variable
		CCodeMover::DeleteVariable("STATIC_SHADOWS_LIMIT");
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_StaticShadowsLimit = iStaticShadows;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of SHADOW LIMITS: Static shadows to: %d",
		iStaticShadows
		);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Sets permanent shadows
void ShadowLimits::SetPermanentShadows(unsigned int iPermanentShadows)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPermanentShadows = this->ms_PermanentShadowsLimit;
	
	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		
		// Allocate if neccessary
		if (iPermanentShadows > this->ms_PermanentShadowsLimit)
		{	
			if (iPermanentShadows % 8 != 0)
				throw f92_runtime_error("Permanent shadows limit should be a multiply of 8.\n%d shadows isn't a multiply of 8!",
					iPermanentShadows
					);

			CShadows__aPermanentShadows.gta_sa = new CPermanentShadow[iPermanentShadows];
			memset(CShadows__aPermanentShadows.gta_sa, NULL, iPermanentShadows * sizeof(CPermanentShadow));
			CShadows__aPermanentShadows.bIsAllocated.Set(true);
		}		
		
		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x706EB5 + 1, &CShadows__aPermanentShadows.gta_sa->field_32);	// mov     eax, offset _ZN8CShadows17aPermanentShadowsE.field_32	; _ZN8CShadows4InitEv
			CPatch::PatchPointer(0x706EC5 + 1, &CShadows__aPermanentShadows.gta_sa[iPermanentShadows].field_32);	// cmp     eax, (offset dword_C4B6E0+2)	; _ZN8CShadows4InitEv
			CPatch::PatchPointer(0x706F64 + 1, &CShadows__aPermanentShadows.gta_sa[1].field_32);	// mov     eax, (offset _ZN8CShadows17aPermanentShadowsE.field_32+38h)	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x706FBA + 1, &CShadows__aPermanentShadows.gta_sa[iPermanentShadows + 1].field_32);	// cmp     eax, (offset flt_C4B718+2)	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x706FF3 + 1, &CShadows__aPermanentShadows.gta_sa->Box);	// mov     edx, offset _ZN8CShadows17aPermanentShadowsE.Box	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x7072DF + 2, &CShadows__aPermanentShadows.gta_sa->field_32);	// mov     _ZN8CShadows17aPermanentShadowsE.field_32[eax], cl	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x7072E5 + 2, &CShadows__aPermanentShadows.gta_sa->field_2C);	// mov     _ZN8CShadows17aPermanentShadowsE.field_2C[eax], edx	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x7072F1 + 2, &CShadows__aPermanentShadows.gta_sa->Pos);	// lea     ecx, _ZN8CShadows17aPermanentShadowsE.Pos.x[eax]; CShadows::aPermanentShadows	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x70730D + 2, &CShadows__aPermanentShadows.gta_sa->Box.m_vInf.x);	// mov     dword ptr _ZN8CShadows17aPermanentShadowsE.Box.m_vInf.x[eax], ecx	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x707317 + 2, &CShadows__aPermanentShadows.gta_sa->Box.m_vInf.y);	// mov     _ZN8CShadows17aPermanentShadowsE.Box.m_vInf.y[eax], edx	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x707321 + 2, &CShadows__aPermanentShadows.gta_sa->Box.m_vInf.z);	// mov     _ZN8CShadows17aPermanentShadowsE.Box.m_vInf.z[eax], ecx	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x70732C + 2, &CShadows__aPermanentShadows.gta_sa->Box.m_vSup.x);	// mov     dword ptr _ZN8CShadows17aPermanentShadowsE.Box.m_vSup.x[eax], edx	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x707336 + 3, &CShadows__aPermanentShadows.gta_sa->field_30);	// mov     _ZN8CShadows17aPermanentShadowsE.field_30[eax], cx	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x707341 + 2, &CShadows__aPermanentShadows.gta_sa->field_33);	// mov     _ZN8CShadows17aPermanentShadowsE.field_33[eax], dl	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x70734B + 2, &CShadows__aPermanentShadows.gta_sa->field_34);	// mov     _ZN8CShadows17aPermanentShadowsE.field_34[eax], cl	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x707355 + 2, &CShadows__aPermanentShadows.gta_sa->field_35);	// mov     _ZN8CShadows17aPermanentShadowsE.field_35[eax], dl	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x70735F + 2, &CShadows__aPermanentShadows.gta_sa->Box.m_vSup.y);	// mov     _ZN8CShadows17aPermanentShadowsE.Box.m_vSup.y[eax], ecx	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x707369 + 2, &CShadows__aPermanentShadows.gta_sa->field_28);	// mov     _ZN8CShadows17aPermanentShadowsE.field_28[eax], edx	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x707375 + 2, &CShadows__aPermanentShadows.gta_sa->Box.m_vSup.z);	// mov     _ZN8CShadows17aPermanentShadowsE.Box.m_vSup.z[eax], ecx	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x70737B + 2, &CShadows__aPermanentShadows.gta_sa->TimeCreated);	// mov     _ZN8CShadows17aPermanentShadowsE.TimeCreated[eax], edx	; _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf
			CPatch::PatchPointer(0x7074F0 + 1, &CShadows__aPermanentShadows.gta_sa->Pos.y);	// mov     ecx, offset _ZN8CShadows17aPermanentShadowsE.Pos.y	; _ZN8CShadows15RemoveOilInAreaEffff
			CPatch::PatchPointer(0x70753E + 2, &CShadows__aPermanentShadows.gta_sa[iPermanentShadows].Pos.y);	// cmp     ecx, offset unk_C4B6B4	; _ZN8CShadows15RemoveOilInAreaEffff
			CPatch::PatchPointer(0x7075AF + 1, &CShadows__aPermanentShadows.gta_sa->field_32);	// mov     esi, offset _ZN8CShadows17aPermanentShadowsE.field_32	; _ZN8CShadows20GunShotSetsOilOnFireEPK7CVectorS2_
			CPatch::PatchPointer(0x707613 + 2, &CShadows__aPermanentShadows.gta_sa[iPermanentShadows].field_32);	// cmp     esi, (offset dword_C4B6E0+2)	; _ZN8CShadows20GunShotSetsOilOnFireEPK7CVectorS2_
			CPatch::PatchPointer(0x707631 + 2, &CShadows__aPermanentShadows.gta_sa->field_32);	// mov     _ZN8CShadows17aPermanentShadowsE.field_32[eax], 5	; _ZN8CShadows20GunShotSetsOilOnFireEPK7CVectorS2_
			CPatch::PatchPointer(0x70763D + 2, &CShadows__aPermanentShadows.gta_sa->Pos);	// lea     eax, _ZN8CShadows17aPermanentShadowsE.Pos.x[eax]; CShadows::aPermanentShadows	; _ZN8CShadows20GunShotSetsOilOnFireEPK7CVectorS2_
			CPatch::PatchPointer(0x707770 + 1, &CShadows__aPermanentShadows.gta_sa->field_32);	// mov     eax, offset _ZN8CShadows17aPermanentShadowsE.field_32	; _ZN8CShadows13TidyUpShadowsEv
			CPatch::PatchPointer(0x70777B + 1, &CShadows__aPermanentShadows.gta_sa[iPermanentShadows].field_32);	// cmp     eax, (offset dword_C4B6E0+2)	; _ZN8CShadows13TidyUpShadowsEv
			CPatch::PatchPointer(0x70C957 + 1, &CShadows__aPermanentShadows.gta_sa->field_28);	// mov     esi, offset _ZN8CShadows17aPermanentShadowsE.field_28	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CA84 + 2, &CShadows__aPermanentShadows.gta_sa[iPermanentShadows].field_28);	// cmp     esi, offset unk_C4B6D8	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CAB0 + 2, &CShadows__aPermanentShadows.gta_sa->field_32);	// cmp     _ZN8CShadows17aPermanentShadowsE.field_32[edi], 5	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CAC5 + 2, &CShadows__aPermanentShadows.gta_sa->field_32);	// mov     _ZN8CShadows17aPermanentShadowsE.field_32[edi], 6	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CACC + 2, &CShadows__aPermanentShadows.gta_sa->TimeCreated);	// mov     _ZN8CShadows17aPermanentShadowsE.TimeCreated[edi], eax	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CAD2 + 2, &CShadows__aPermanentShadows.gta_sa->field_28);	// mov     _ZN8CShadows17aPermanentShadowsE.field_28[edi], ebx	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CAE2 + 1, &CShadows__aPermanentShadows.gta_sa->field_32);	// mov     ecx, offset _ZN8CShadows17aPermanentShadowsE.field_32	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CAF1 + 2, &CShadows__aPermanentShadows.gta_sa->Pos.x);	// fld     dword ptr _ZN8CShadows17aPermanentShadowsE.Pos.x[edi]; CShadows::aPermanentShadows	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CAFA + 2, &CShadows__aPermanentShadows.gta_sa->Pos.y);	// fld     _ZN8CShadows17aPermanentShadowsE.Pos.y[edi]	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CB03 + 2, &CShadows__aPermanentShadows.gta_sa->Pos.z);	// fld     _ZN8CShadows17aPermanentShadowsE.Pos.z[edi]	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CB3D + 2, &CShadows__aPermanentShadows.gta_sa[iPermanentShadows].field_32);	// cmp     ecx, (offset dword_C4B6E0+2)	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CB5E + 2, &CShadows__aPermanentShadows.gta_sa->Pos);	// lea     ebp, _ZN8CShadows17aPermanentShadowsE.Pos.x[esi]; CShadows::aPermanentShadows	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CB80 + 2, &CShadows__aPermanentShadows.gta_sa->field_32);	// mov     _ZN8CShadows17aPermanentShadowsE.field_32[esi], 7	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CB8C + 1, &CShadows__aPermanentShadows.gta_sa->field_32);	// mov     ecx, offset _ZN8CShadows17aPermanentShadowsE.field_32	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CB94 + 2, &CShadows__aPermanentShadows.gta_sa->Pos.x);	// fsub    dword ptr _ZN8CShadows17aPermanentShadowsE.Pos.x[edi]; CShadows::aPermanentShadows	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CB9A + 2, &CShadows__aPermanentShadows.gta_sa->Pos.y);	// fld     _ZN8CShadows17aPermanentShadowsE.Pos.y[esi]	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CBA3 + 2, &CShadows__aPermanentShadows.gta_sa->Pos.y);	// fsub    _ZN8CShadows17aPermanentShadowsE.Pos.y[edi]	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CBBB + 2, &CShadows__aPermanentShadows.gta_sa->Pos.x);	// fld     dword ptr _ZN8CShadows17aPermanentShadowsE.Pos.x[edi]; CShadows::aPermanentShadows	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CBC4 + 2, &CShadows__aPermanentShadows.gta_sa->Pos.y);	// fld     _ZN8CShadows17aPermanentShadowsE.Pos.y[edi]	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CBCD + 2, &CShadows__aPermanentShadows.gta_sa->Pos.z);	// fld     _ZN8CShadows17aPermanentShadowsE.Pos.z[edi]	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CBFE + 2, &CShadows__aPermanentShadows.gta_sa->Pos.y);	// fsub    _ZN8CShadows17aPermanentShadowsE.Pos.y[edi]	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CC09 + 2, &CShadows__aPermanentShadows.gta_sa->Pos.x);	// fsub    dword ptr _ZN8CShadows17aPermanentShadowsE.Pos.x[edi]; CShadows::aPermanentShadows	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CC2C + 2, &CShadows__aPermanentShadows.gta_sa[iPermanentShadows].field_32);	// cmp     ecx, (offset dword_C4B6E0+2)	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CC50 + 2, &CShadows__aPermanentShadows.gta_sa->Pos);	// lea     edx, _ZN8CShadows17aPermanentShadowsE.Pos.x[eax]; CShadows::aPermanentShadows	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CC5D + 2, &CShadows__aPermanentShadows.gta_sa->field_32);	// mov     _ZN8CShadows17aPermanentShadowsE.field_32[eax], 7	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CC90 + 1, &CShadows__aPermanentShadows.gta_sa->field_32);	// mov     eax, offset _ZN8CShadows17aPermanentShadowsE.field_32	; _ZN8CShadows22UpdatePermanentShadowsEv
			CPatch::PatchPointer(0x70CCA0 + 1, &CShadows__aPermanentShadows.gta_sa[iPermanentShadows].field_32);	// cmp     eax, (offset dword_C4B6E0+2)	; _ZN8CShadows22UpdatePermanentShadowsEv
		}
		#endif

		// Define variable for automatic patch
		CCodeMover::SetVariable("PERMAMENT_SHADOWS_LIMIT", iPermanentShadows);

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 3
			CCodeMover::FixOnAddressRel(0x706FE2, 9, "\x01\x02\x81\xff\x05\x04""PERMAMENT_SHADOWS_LIMIT\x00\x01\x02\x0F\x8C\x0F\xd2\x72\x70\x00\x00", 0x706FEB);	// line 1, 0x706F60 - _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf : cmp     edi, 30h
			CCodeMover::FixOnAddressRel(0x7072C0, 9, "\x01\x01\x3d\x05\x04""PERMAMENT_SHADOWS_LIMIT\x00\x01\x02\x0F\x8C\x0F\xf8\x6f\x70\x00\x00", 0x7072C9);	// line 2, 0x706F60 - _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf : cmp     eax, 30h
			CCodeMover::FixOnAddressRel(0x7072C9, 9, "\x01\x02\x81\xff\x05\x04""PERMAMENT_SHADOWS_LIMIT\x00\x01\x02\x0F\x8D\x0F\x81\x73\x70\x00\x00", 0x7072D2);	// line 3, 0x706F60 - _ZN8CShadows18AddPermanentShadowEhP9RwTextureP7CVectorffffshhhfjf : cmp     edi, 30h
		}
		#endif

		// Delete a variable
		CCodeMover::DeleteVariable("PERMAMENT_SHADOWS_LIMIT");
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->ms_PermanentShadowsLimit = iPermanentShadows;

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of SHADOW LIMITS: Permanent shadows to: %d",
		iPermanentShadows
		);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	NAKED void patch_CRealTimeShadowManager__CRealTimeShadowManager_706786()
	{
		__asm
		{
			mov eax, dword ptr[offset CRealTimeShadowManager::m_realTimeShadowPool + CDynamicStructMemberBase::offset];

			lea     edi, [edx + eax];
			mov ecx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_shadowLimits, ShadowLimits, ms_RealTimeShadowsLimit);

			xor     eax, eax;

			ASM_JMP_STATIC_ADDRESS(0x70678E)
		}
	}

	NAKED void patch_CRealTimeShadowManager__Exit_706A6C()
	{
		__asm
		{
			mov eax, dword ptr[offset CRealTimeShadowManager::m_realTimeShadowPool + CDynamicStructMemberBase::offset];
			lea     esi, [ebp + eax];

			mov ebx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_shadowLimits, ShadowLimits, ms_RealTimeShadowsLimit);

			ASM_JMP_STATIC_ADDRESS(0x706A74)
		}
	}

	NAKED void patch_CRealTimeShadowManager__GetRealTimeShadow_7069F7()
	{
		__asm
		{
			mov eax, dword ptr[offset CRealTimeShadowManager::m_realTimeShadowPool + CDynamicStructMemberBase::offset];
			mov     esi, [ecx + eax];

			push 0x706A3B;
			retn;
		}
	}

	NAKED void patch_CRealTimeShadowManager__GetRealTimeShadow_7069FC()
	{
		__asm
		{
			mov eax, dword ptr[offset CRealTimeShadowManager::m_realTimeShadowPool + CDynamicStructMemberBase::offset];
			lea     eax, [ecx + eax];
			mov edx, ASM_ACCESS_LIMIT_VAR_32_BIT(g_shadowLimits, ShadowLimits, ms_RealTimeShadowsLimit);

		doLoop:
			mov ecx, [eax];

			cmp dword ptr[ecx], 0;
			jne incrementLoop;

			mov esi, ecx;

		incrementLoop:
			add eax, 4;
			dec edx;
			jnz doLoop;

			///////////
			push 0x706A3B;
			retn;
		}
	}

	NAKED void patch_CRealTimeShadowManager__Init_7067CE()
	{
		__asm
		{
			mov eax, dword ptr[offset CRealTimeShadowManager::m_realTimeShadowPool + CDynamicStructMemberBase::offset];
			lea     esi, [edi + eax];
			mov ebp, ASM_ACCESS_LIMIT_VAR_32_BIT(g_shadowLimits, ShadowLimits, ms_RealTimeShadowsLimit);

			push 0x7067D6;
			retn;
		}
	}

	NAKED void patch_CRealTimeShadowManager__ReInit_70687B()
	{
		__asm
		{
			mov eax, dword ptr[offset CRealTimeShadowManager::m_realTimeShadowPool + CDynamicStructMemberBase::offset];
			lea     edi, [ecx + eax];
			mov eax, ASM_ACCESS_LIMIT_VAR_32_BIT(g_shadowLimits, ShadowLimits, ms_RealTimeShadowsLimit);
			mov[esp + 18h - 8], eax;
			xor     ebp, ebp;

			push 0x706888;
			retn;
		}
	}

	NAKED void patch_CRealTimeShadowManager__Update_706ACC()
	{
		__asm
		{
			mov eax, dword ptr[offset CRealTimeShadowManager::m_realTimeShadowPool + CDynamicStructMemberBase::offset];
			lea     esi, [edi + eax];
			mov[esp + 14h - 4], esi;
			mov ebp, ASM_ACCESS_LIMIT_VAR_32_BIT(g_shadowLimits, ShadowLimits, ms_RealTimeShadowsLimit);
			
			push 0x706AE0;
			retn;
		}
	}
}
#endif

// Sets real time shadows
void ShadowLimits::SetRealTimeShadows(unsigned int iRealTimeShadows)
{
	MAKE_VAR_GAME_VERSION();

	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iRealTimeShadows = this->ms_RealTimeShadowsLimit;

	unsigned int defaultRealTimeShadowsLimit = this->ms_RealTimeShadowsLimit;
	defaultRealTimeShadowsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		
		this->ms_RealTimeShadowsLimit = iRealTimeShadows;
		this->Allocate_CRealTimeShadowManager();

		if (iRealTimeShadows > defaultRealTimeShadowsLimit)
		{
			g_realTimeShadowMan.gta_sa = (CRealTimeShadowManager*)new char[
				CRealTimeShadowManager::endOfStructure.GetOffset()
			];

			memset(
				g_realTimeShadowMan.gta_sa,
				NULL,
				CRealTimeShadowManager::endOfStructure.GetOffset()
			);

			g_realTimeShadowMan.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x45D411 + 1, g_realTimeShadowMan.gta_sa);	// mov     ecx, offset g_realTimeShadowMan	; _ZN7CReplay38EmptyPedsAndVehiclePools_NoDestructorsEv
			CPatch::PatchPointer(0x53BE62 + 1, g_realTimeShadowMan.gta_sa);	// mov     ecx, offset g_realTimeShadowMan; this	; _ZN5CGame25ReInitGameObjectVariablesEv
			CPatch::PatchPointer(0x53C63E + 1, g_realTimeShadowMan.gta_sa);	// mov     ecx, offset g_realTimeShadowMan	; _ZN5CGame18ShutDownForRestartEv
			CPatch::PatchPointer(0x53C9E4 + 1, g_realTimeShadowMan.gta_sa);	// mov     ecx, offset g_realTimeShadowMan	; _ZN5CGame8ShutdownEv
			CPatch::PatchPointer(0x53EA08 + 1, g_realTimeShadowMan.gta_sa);	// mov     ecx, offset g_realTimeShadowMan	; _Z4IdlePvb
			CPatch::PatchPointer(0x542486 + 1, g_realTimeShadowMan.gta_sa);	// mov     ecx, offset g_realTimeShadowMan	; ??1CPhysical@@UAE@XZ
			CPatch::PatchPointer(0x5B1F37 + 1, g_realTimeShadowMan.gta_sa);	// mov     ecx, offset g_realTimeShadowMan	; _ZN15CCutsceneObject9PreRenderEv
			CPatch::PatchPointer(0x5BA12B + 1, &g_realTimeShadowMan.gta_sa->m_initialized(g_realTimeShadowMan.gta_sa));	// mov     al, g_realTimeShadowMan.m_initialized	; _D3DDeviceRestoreCallback
			CPatch::PatchPointer(0x5BA136 + 1, &g_realTimeShadowMan.gta_sa->field_1(g_realTimeShadowMan.gta_sa));	// mov     g_realTimeShadowMan.field_1, al	; _D3DDeviceRestoreCallback
			CPatch::PatchPointer(0x5BA477 + 1, g_realTimeShadowMan.gta_sa);	// mov     ecx, offset g_realTimeShadowMan; this	; _ZN5CGame5Init3EPKc
			CPatch::PatchPointer(0x5E68A3 + 1, g_realTimeShadowMan.gta_sa);	// mov     ecx, offset g_realTimeShadowMan	; _ZN4CPed18PreRenderAfterTestEv
			CPatch::PatchPointer(0x706695 + 1, &g_realTimeShadowMan.gta_sa->m_camera1(g_realTimeShadowMan.gta_sa));	// mov     ecx, offset g_realTimeShadowMan.m_camera1	; sub_706600
			CPatch::PatchPointer(0x7066A7 + 1, &g_realTimeShadowMan.gta_sa->m_camera2(g_realTimeShadowMan.gta_sa));	// mov     ecx, offset g_realTimeShadowMan.m_camera2	; sub_706600
			CPatch::PatchPointer(0x854980 + 1, g_realTimeShadowMan.gta_sa);	// mov     ecx, offset g_realTimeShadowMan	; sub_854980
			CPatch::PatchPointer(0x856AD0 + 1, g_realTimeShadowMan.gta_sa);	// mov     ecx, offset g_realTimeShadowMan	; unknown_libname_208
		}
		#endif

		// Patch count (16)
		#if TRUE
		{
			// CRealTimeShadowManager::CRealTimeShadowManager
			CPatch::PatchUINT32(0x706789 + 1, iRealTimeShadows);	// mov     ecx, 16

			// CRealTimeShadowManager::Exit
			CPatch::PatchUINT32(0x706A6F + 1, iRealTimeShadows);	// mov     ebx, 16

			// CRealTimeShadowManager::Init
			CPatch::PatchUINT32(0x7067D1 + 1, iRealTimeShadows);	// mov     ebp, 16

			// CRealTimeShadowManager::ReInit
			CPatch::PatchUINT32(0x70687E + 4, iRealTimeShadows);	// mov     [esp+18h+var_8], 16

			// CRealTimeShadowManager::Update
			CPatch::PatchUINT32(0x706AD3 + 1, iRealTimeShadows);	// mov     ebp, 16
			CPatch::PatchUINT32(0x706B7F + 1, iRealTimeShadows);	// mov     ecx, 16
		}
		#endif

		// offsets to m_realTimeShadowPool
		#if TRUE
		{
			CPatch::RedirectCode(0x706786, &patch_CRealTimeShadowManager__CRealTimeShadowManager_706786);

			CPatch::RedirectCode(0x706A6C, &patch_CRealTimeShadowManager__Exit_706A6C);

			CPatch::RedirectCode(0x7069F7, &patch_CRealTimeShadowManager__GetRealTimeShadow_7069F7);
			CPatch::RedirectCode(0x7069FC, &patch_CRealTimeShadowManager__GetRealTimeShadow_7069FC);

			CPatch::RedirectCode(0x7067CE, &patch_CRealTimeShadowManager__Init_7067CE);

			CPatch::RedirectCode(0x70687B, &patch_CRealTimeShadowManager__ReInit_70687B);
			
			CPatch::RedirectCode(0x706ACC, &patch_CRealTimeShadowManager__Update_706ACC);
		}
		#endif
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of SHADOW LIMITS: Real time shadows to: %d",
		iRealTimeShadows
	);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Allocates CRealTimeShadowManager
void ShadowLimits::Allocate_CRealTimeShadowManager()
{
	MAKE_VAR_GAME_VERSION();

	MAKE_DEAD_IF();
	else if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		using namespace Game_GTASA;
		g_StructAllocator.InitPerStruct();
		g_StructAllocator.Allocate(CRealTimeShadowManager::m_initialized);
		g_StructAllocator.Allocate(CRealTimeShadowManager::field_1);
		g_StructAllocator.Allocate(CRealTimeShadowManager::m_realTimeShadowPool, 16);
		g_StructAllocator.Allocate(CRealTimeShadowManager::m_camera1);
		g_StructAllocator.Allocate(CRealTimeShadowManager::m_camera2);

		if (this->ms_RealTimeShadowsLimit > 16)
			g_StructAllocator.Allocate(
				CRealTimeShadowManager::m_realTimeShadowPool,
				this->ms_RealTimeShadowsLimit
			);

		g_StructAllocator.Allocate(CRealTimeShadowManager::endOfStructure);
	}
}

// Initialize
void ShadowLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;
		this->ms_ShadowsStoredLimit = 48;
		this->ms_PolyBunchesLimit = 360;
		this->ms_StaticShadowsLimit = 48;
		this->ms_PermanentShadowsLimit = 48;
		this->ms_RealTimeShadowsLimit = 16;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			this->CShadows__asShadowsStored.gta_sa = (CStoredShadow*)0xC40430;
			this->CShadows__aPolyBunches.gta_sa = (CPolyBunch*)0xC40DF0;
			this->CShadows__aStaticShadows.gta_sa = (CStaticShadow*)0xC4A030;
			this->CShadows__aPermanentShadows.gta_sa = (CPermanentShadow*)0xC4AC30;
			this->g_realTimeShadowMan.gta_sa = (CRealTimeShadowManager*)0xC40350;
			#endif
		}

		this->Allocate_CRealTimeShadowManager();
	}
}

// Shutdown
void ShadowLimits::Shutdown()
{
	MAKE_VAR_GAME_VERSION();

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		if (CShadows__asShadowsStored.bIsAllocated.Get())
			delete[] CShadows__asShadowsStored.gta_sa;

		if (CShadows__aPolyBunches.bIsAllocated.Get())
			delete[] CShadows__aPolyBunches.gta_sa;

		if (CShadows__aStaticShadows.bIsAllocated.Get())
			delete[] CShadows__aStaticShadows.gta_sa;

		if (CShadows__aPermanentShadows.bIsAllocated.Get())
			delete[] CShadows__aPermanentShadows.gta_sa;

		if (g_realTimeShadowMan.bIsAllocated.Get())
			delete[] g_realTimeShadowMan.gta_sa;
	}
}
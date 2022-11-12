/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "WaterLimits.h"

#include "../Core/CCodeMover.h"
#include "../Core/CPatch.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/LimitAdjuster.h"

using namespace Game;

WaterLimits g_waterLimits;

// Sets water quads
void WaterLimits::SetWaterQuads(unsigned int iNumberOfWaterQuads)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iNumberOfWaterQuads = this->WaterQuadsLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (iNumberOfWaterQuads > this->WaterQuadsLimit)
		{
			CWaterLevel__m_aQuads.gta_sa = new CWaterQuad[iNumberOfWaterQuads];
			CWaterLevel__m_aQuads.bIsAllocated.Set(true);
		}

		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x6E5846 + 3, &CWaterLevel__m_aQuads.gta_sa -> m_flags);	// mov     dx, _ZN11CWaterLevel8m_aQuadsE.m_flags[ecx]	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E5856 + 3, CWaterLevel__m_aQuads.gta_sa);	// movsx   eax, word ptr _ZN11CWaterLevel8m_aQuadsE.field_0[ecx]; CWaterLevel::m_aQuads	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E5887 + 3, &CWaterLevel__m_aQuads.gta_sa -> m_flags);	// mov     _ZN11CWaterLevel8m_aQuadsE.m_flags[ecx], dx	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E5976 + 3, &CWaterLevel__m_aQuads.gta_sa -> m_flags);	// mov     dx, _ZN11CWaterLevel8m_aQuadsE.m_flags[ecx]	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E5982 + 3, CWaterLevel__m_aQuads.gta_sa);	// movsx   eax, word ptr _ZN11CWaterLevel8m_aQuadsE.field_0[ecx]; CWaterLevel::m_aQuads	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E59AD + 3, &CWaterLevel__m_aQuads.gta_sa -> m_flags);	// mov     _ZN11CWaterLevel8m_aQuadsE.m_flags[ecx], dx	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E63C5 + 3, CWaterLevel__m_aQuads.gta_sa);	// lea     edx, _ZN11CWaterLevel8m_aQuadsE.field_0[edx*2]; CWaterLevel::m_aQuads	; _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_
			CPatch::PatchPointer(0x6E6528 + 3, CWaterLevel__m_aQuads.gta_sa);	// lea     edx, _ZN11CWaterLevel8m_aQuadsE.field_0[edx*2]; CWaterLevel::m_aQuads	; _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_
			CPatch::PatchPointer(0x6E7B87 + 1, CWaterLevel__m_aQuads.gta_sa);	// mov     esi, offset _ZN11CWaterLevel8m_aQuadsE; CWaterLevel::m_aQuads	; _ZN11CWaterLevel25FillQuadsAndTrianglesListEv
			CPatch::PatchPointer(0x6E8167 + 3, CWaterLevel__m_aQuads.gta_sa);	// mov     word ptr _ZN11CWaterLevel8m_aQuadsE.field_0[eax], si; CWaterLevel::m_aQuads	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E816E + 3, &CWaterLevel__m_aQuads.gta_sa -> field_2);	// mov     _ZN11CWaterLevel8m_aQuadsE.field_2[eax], di	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E8175 + 3, &CWaterLevel__m_aQuads.gta_sa -> field_4);	// mov     _ZN11CWaterLevel8m_aQuadsE.field_4[eax], cx	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E817C + 3, &CWaterLevel__m_aQuads.gta_sa -> field_6);	// mov     _ZN11CWaterLevel8m_aQuadsE.field_6[eax], dx	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E8183 + 2, &CWaterLevel__m_aQuads.gta_sa -> m_flags);	// and     byte ptr _ZN11CWaterLevel8m_aQuadsE.m_flags[eax], 0FEh	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E8196 + 3, &CWaterLevel__m_aQuads.gta_sa -> m_flags);	// mov     cx, _ZN11CWaterLevel8m_aQuadsE.m_flags[eax]	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E81AA + 3, &CWaterLevel__m_aQuads.gta_sa -> m_flags);	// mov     _ZN11CWaterLevel8m_aQuadsE.m_flags[eax], cx	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E81B3 + 2, &CWaterLevel__m_aQuads.gta_sa -> m_flags);	// or      byte ptr _ZN11CWaterLevel8m_aQuadsE.m_flags[eax], 4	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E81C9 + 2, &CWaterLevel__m_aQuads.gta_sa -> m_flags);	// and     byte ptr _ZN11CWaterLevel8m_aQuadsE.m_flags[eax], 0FBh	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E8632 + 3, CWaterLevel__m_aQuads.gta_sa);	// lea     ecx, _ZN11CWaterLevel8m_aQuadsE.field_0[eax*2]; CWaterLevel::m_aQuads	; _ZN11CWaterLevel20GetWaterLevelNoWavesEfffPfS0_S0_
			CPatch::PatchPointer(0x6E8706 + 3, CWaterLevel__m_aQuads.gta_sa);	// lea     ecx, _ZN11CWaterLevel8m_aQuadsE.field_0[eax*2]; CWaterLevel::m_aQuads	; _ZN11CWaterLevel20GetWaterLevelNoWavesEfffPfS0_S0_
			CPatch::PatchPointer(0x6E9E1C + 1, CWaterLevel__m_aQuads.gta_sa);	// mov     edi, offset _ZN11CWaterLevel8m_aQuadsE; CWaterLevel::m_aQuads	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EFCCE + 1, &CWaterLevel__m_aQuads.gta_sa -> field_4);	// mov     esi, offset _ZN11CWaterLevel8m_aQuadsE.field_4	; _ZN11CWaterLevel11RenderWaterEv
		}
		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if (iNumberOfWaterQuads > this->WaterQuadsLimit)
		{
			CWaterLevel__m_aQuads.gta_sa = new CWaterQuad[iNumberOfWaterQuads];
			CWaterLevel__m_aQuads.bIsAllocated.Set(true);
		}

		// Patch pointer
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x679620), CWaterLevel__m_aQuads.gta_sa);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	WaterLimits::WaterQuadsLimit = iNumberOfWaterQuads;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of WATER LIMITS -> Water quads to: %d",
		iNumberOfWaterQuads);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets water triangles
void WaterLimits::SetWaterTriangles(unsigned int iNumberOfWaterTriangles)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iNumberOfWaterTriangles = this->WaterTrianglesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (iNumberOfWaterTriangles > this->WaterTrianglesLimit)
		{
			CWaterLevel__m_aTriangles.gta_sa = new CWaterTriangle[iNumberOfWaterTriangles];
			CWaterLevel__m_aTriangles.bIsAllocated.Set(true);
		}
		
		// Patch addresses
		#if TRUE
		{
			CPatch::PatchPointer(0x6E589A + 3, &CWaterLevel__m_aTriangles.gta_sa -> field_6);	// mov     cx, word ptr _ZN11CWaterLevel12m_aTrianglesE.field_6[edx]	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E58AA + 3, CWaterLevel__m_aTriangles.gta_sa);	// movsx   eax, word ptr _ZN11CWaterLevel12m_aTrianglesE.field_0[edx]; CWaterLevel::m_aTriangles	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E58DB + 3, &CWaterLevel__m_aTriangles.gta_sa -> field_6);	// mov     word ptr _ZN11CWaterLevel12m_aTrianglesE.field_6[edx], cx	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E592C + 3, &CWaterLevel__m_aTriangles.gta_sa -> field_6);	// mov     cx, word ptr _ZN11CWaterLevel12m_aTrianglesE.field_6[esi]	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E5938 + 3, CWaterLevel__m_aTriangles.gta_sa);	// movsx   eax, word ptr _ZN11CWaterLevel12m_aTrianglesE.field_0[esi]; CWaterLevel::m_aTriangles	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E5963 + 3, &CWaterLevel__m_aTriangles.gta_sa -> field_6);	// mov     word ptr _ZN11CWaterLevel12m_aTrianglesE.field_6[esi], cx	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E7C40 + 4, CWaterLevel__m_aTriangles.gta_sa);	// movsx   eax, _ZN11CWaterLevel12m_aTrianglesE.field_0[esi*8]; CWaterLevel::m_aTriangles	; _ZN11CWaterLevel25FillQuadsAndTrianglesListEv
			CPatch::PatchPointer(0x6E7C60 + 4, &CWaterLevel__m_aTriangles.gta_sa -> field_2);	// movsx   ecx, _ZN11CWaterLevel12m_aTrianglesE.field_2[esi*8]	; _ZN11CWaterLevel25FillQuadsAndTrianglesListEv
			CPatch::PatchPointer(0x6E7C7B + 4, &CWaterLevel__m_aTriangles.gta_sa -> field_4);	// movsx   ecx, _ZN11CWaterLevel12m_aTrianglesE.field_4[esi*8]	; _ZN11CWaterLevel25FillQuadsAndTrianglesListEv
			CPatch::PatchPointer(0x6E7E7B + 4, CWaterLevel__m_aTriangles.gta_sa);	// mov     _ZN11CWaterLevel12m_aTrianglesE.field_0[esi*8], cx; CWaterLevel::m_aTriangles	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7E87 + 4, &CWaterLevel__m_aTriangles.gta_sa -> field_2);	// mov     _ZN11CWaterLevel12m_aTrianglesE.field_2[esi*8], dx	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7E8F + 4, &CWaterLevel__m_aTriangles.gta_sa -> field_4);	// mov     _ZN11CWaterLevel12m_aTrianglesE.field_4[esi*8], ax	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7E97 + 3, &CWaterLevel__m_aTriangles.gta_sa -> field_6);	// and     _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8], 0FEh	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7EA4 + 4, &CWaterLevel__m_aTriangles.gta_sa -> field_6);	// mov     ax, word ptr _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8]	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7EB9 + 4, &CWaterLevel__m_aTriangles.gta_sa -> field_6);	// mov     word ptr _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8], ax	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7EC3 + 3, &CWaterLevel__m_aTriangles.gta_sa -> field_6);	// or      _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8], 4	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7ED7 + 3, &CWaterLevel__m_aTriangles.gta_sa -> field_6);	// and     _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8], 0FBh	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E8670 + 3, CWaterLevel__m_aTriangles.gta_sa);	// lea     edx, _ZN11CWaterLevel12m_aTrianglesE.field_0[eax*8]; CWaterLevel::m_aTriangles	; _ZN11CWaterLevel20GetWaterLevelNoWavesEfffPfS0_S0_
			CPatch::PatchPointer(0x6E86E1 + 3, CWaterLevel__m_aTriangles.gta_sa);	// lea     eax, _ZN11CWaterLevel12m_aTrianglesE.field_0[eax*8]; CWaterLevel::m_aTriangles	; _ZN11CWaterLevel20GetWaterLevelNoWavesEfffPfS0_S0_
			CPatch::PatchPointer(0x6EFBD0 + 3, &CWaterLevel__m_aTriangles.gta_sa -> field_6);	// test    _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8], 1	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFBDE + 4, &CWaterLevel__m_aTriangles.gta_sa -> field_4);	// movsx   eax, _ZN11CWaterLevel12m_aTrianglesE.field_4[esi*8]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFBE6 + 4, &CWaterLevel__m_aTriangles.gta_sa -> field_2);	// movsx   ecx, _ZN11CWaterLevel12m_aTrianglesE.field_2[esi*8]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFC23 + 4, CWaterLevel__m_aTriangles.gta_sa);	// movsx   edx, _ZN11CWaterLevel12m_aTrianglesE.field_0[esi*8]; CWaterLevel::m_aTriangles	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFCA0 + 3, &CWaterLevel__m_aTriangles.gta_sa -> field_6);	// and     _ZN11CWaterLevel12m_aTrianglesE.field_6[esi*8], 0FEh	; _ZN11CWaterLevel11RenderWaterEv
		}
		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID)
	else if(gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if (iNumberOfWaterTriangles > this->WaterTrianglesLimit)
		{
			CWaterLevel__m_aTriangles.gta_sa = new CWaterTriangle[iNumberOfWaterTriangles];
			CWaterLevel__m_aTriangles.bIsAllocated.Set(true);
		}

		// Patch address
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x676054), CWaterLevel__m_aTriangles.gta_sa);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->WaterTrianglesLimit = iNumberOfWaterTriangles;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of WATER LIMITS -> Water triangles to: %d",
		iNumberOfWaterTriangles);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets quads and triangles list
void WaterLimits::SetQuadsAndTrianglesList(unsigned int iNumberOfQuadsAndTrianglesList)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iNumberOfQuadsAndTrianglesList = this->WaterQuadsAndTrianglesListLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		if (iNumberOfQuadsAndTrianglesList > this->WaterQuadsAndTrianglesListLimit)
		{
			CWaterLevel__m_QuadsAndTrianglesList.ptr = new int16_t[iNumberOfQuadsAndTrianglesList];
			CWaterLevel__m_QuadsAndTrianglesList.bIsAllocated.Set(true);
		}
	
		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x6E57A6 + 4, CWaterLevel__m_QuadsAndTrianglesList.ptr);	// mov     _ZN11CWaterLevel23m_QuadsAndTrianglesListE[eax*2], cx; CWaterLevel::m_QuadsAndTrianglesList	; _ZN11CWaterLevel26AddToQuadsAndTrianglesListEiiij
			CPatch::PatchPointer(0x6E57AE + 4, CWaterLevel__m_QuadsAndTrianglesList.ptr+1);	// mov     (_ZN11CWaterLevel23m_QuadsAndTrianglesListE+2)[eax*2], 0	; _ZN11CWaterLevel26AddToQuadsAndTrianglesListEiiij
			CPatch::PatchPointer(0x6E57C4 + 4, CWaterLevel__m_QuadsAndTrianglesList.ptr+1);	// mov     _ZN11CWaterLevel23m_QuadsAndTrianglesListE+2[eax*2], dx	; _ZN11CWaterLevel26AddToQuadsAndTrianglesListEiiij
			CPatch::PatchPointer(0x6E57DA + 4, CWaterLevel__m_QuadsAndTrianglesList.ptr+2);	// mov     _ZN11CWaterLevel23m_QuadsAndTrianglesListE+4[eax*2], dx	; _ZN11CWaterLevel26AddToQuadsAndTrianglesListEiiij
			CPatch::PatchPointer(0x6E57E4 + 4, CWaterLevel__m_QuadsAndTrianglesList.ptr+3);	// mov     _ZN11CWaterLevel23m_QuadsAndTrianglesListE+6[eax*2], 0	; _ZN11CWaterLevel26AddToQuadsAndTrianglesListEiiij
			CPatch::PatchPointer(0x6E58EF + 3, CWaterLevel__m_QuadsAndTrianglesList.ptr+1);	// lea     ecx, (_ZN11CWaterLevel23m_QuadsAndTrianglesListE+2)[eax*2]	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E6384 + 3, (char*)CWaterLevel__m_QuadsAndTrianglesList.ptr+3);	// test    byte ptr _ZN11CWaterLevel23m_QuadsAndTrianglesListE+3[eax*2], 0C0h	; _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_
			CPatch::PatchPointer(0x6E638C + 3, CWaterLevel__m_QuadsAndTrianglesList.ptr+1);	// lea     eax, (_ZN11CWaterLevel23m_QuadsAndTrianglesListE+2)[eax*2]	; _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_
			CPatch::PatchPointer(0x6E8696 + 3, (char*)CWaterLevel__m_QuadsAndTrianglesList.ptr+3);	// test    byte ptr _ZN11CWaterLevel23m_QuadsAndTrianglesListE+3[eax*2], 0C0h	; _ZN11CWaterLevel20GetWaterLevelNoWavesEfffPfS0_S0_
			CPatch::PatchPointer(0x6E869E + 3, CWaterLevel__m_QuadsAndTrianglesList.ptr+1);	// lea     eax, (_ZN11CWaterLevel23m_QuadsAndTrianglesListE+2)[eax*2]	; _ZN11CWaterLevel20GetWaterLevelNoWavesEfffPfS0_S0_
		}
		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		if (iNumberOfQuadsAndTrianglesList > this->WaterQuadsAndTrianglesListLimit)
		{
			CWaterLevel__m_QuadsAndTrianglesList.ptr = new int16_t[iNumberOfQuadsAndTrianglesList];
			CWaterLevel__m_QuadsAndTrianglesList.bIsAllocated.Set(true);
		}

		// Patch pointer
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x678E14), CWaterLevel__m_QuadsAndTrianglesList.ptr);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->WaterQuadsAndTrianglesListLimit = iNumberOfQuadsAndTrianglesList;

	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of WATER LIMITS -> Water quads and triangles list triangles to: %d",
		iNumberOfQuadsAndTrianglesList);
	CGenericLogStorage::WriteLineSeparator();
}

// Sets the water vertices
void WaterLimits::SetWaterVertices(unsigned int iNumberOfWaterVertices)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iNumberOfWaterVertices = this->WaterVerticesLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		using namespace Game_GTASA;

		if (iNumberOfWaterVertices > this->WaterVerticesLimit)
		{
			CWaterLevel__m_aVertices.gta_sa = new CWaterVertice[iNumberOfWaterVertices];
			CWaterLevel__m_aVertices.bIsAllocated.Set(true);
		}
	
		// Patch pointers
		#if TRUE
		{
			CPatch::PatchPointer(0x6E5860 + 3, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fld     _ZN11CWaterLevel11m_aVerticesE.posZ[eax*4]	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E58B4 + 3, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fld     _ZN11CWaterLevel11m_aVerticesE.posZ[eax*4]	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E5942 + 3, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fld     _ZN11CWaterLevel11m_aVerticesE.posZ[edx*4]	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E598C + 3, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fld     _ZN11CWaterLevel11m_aVerticesE.posZ[eax*4]	; _ZN11CWaterLevel29MarkQuadsAndPolysToBeRenderedEiib
			CPatch::PatchPointer(0x6E5B35 + 1, &CWaterLevel__m_aVertices.gta_sa -> posY);	// mov     edx, offset _ZN11CWaterLevel11m_aVerticesE.posY	; _ZN11CWaterLevel19AddWaterLevelVertexEii7CRenPar
			CPatch::PatchPointer(0x6E5B6B + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// mov     word ptr _ZN11CWaterLevel11m_aVerticesE.posX[eax], bx; CWaterLevel::m_aVertices	; _ZN11CWaterLevel19AddWaterLevelVertexEii7CRenPar
			CPatch::PatchPointer(0x6E5B72 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// mov     _ZN11CWaterLevel11m_aVerticesE.posY[eax], di	; _ZN11CWaterLevel19AddWaterLevelVertexEii7CRenPar
			CPatch::PatchPointer(0x6E5B79 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// lea     edx, _ZN11CWaterLevel11m_aVerticesE.posZ[eax]	; _ZN11CWaterLevel19AddWaterLevelVertexEii7CRenPar
			CPatch::PatchPointer(0x6E5BC0 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5BF4 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   ebp, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edi]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5C12 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[edx]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5C42 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   ebx, _ZN11CWaterLevel11m_aVerticesE.posY[esi]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5CA7 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fld     _ZN11CWaterLevel11m_aVerticesE.posZ[esi]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5CB1 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[edx]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5CB9 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fld     _ZN11CWaterLevel11m_aVerticesE.posZ[edi]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5CC5 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[edx]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5CD1 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fadd    _ZN11CWaterLevel11m_aVerticesE.posZ[edx]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5CEC + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5CFA + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5D03 + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5D0A + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5D17 + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fadd    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5D2D + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5D3B + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5D44 + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5D4B + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5D58 + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fadd    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5D81 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fld     _ZN11CWaterLevel11m_aVerticesE.posZ[esi]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5D8B + 3, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5D94 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fld     _ZN11CWaterLevel11m_aVerticesE.posZ[edi]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5DA0 + 3, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5DAB + 3, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fadd    _ZN11CWaterLevel11m_aVerticesE.posZ[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5DC8 + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5DD6 + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5DDF + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5DE6 + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5DF1 + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fadd    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5E08 + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5E16 + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5E1F + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5E26 + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5E31 + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fadd    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]	; _ZN11CWaterLevel23TestQuadToGetWaterLevelEP10CWaterQuadfffPfS2_S2_
			CPatch::PatchPointer(0x6E5EA0 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E5ED4 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   ebp, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ebx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E5EF9 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// mov     ax, _ZN11CWaterLevel11m_aVerticesE.posY[edx]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E5F03 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// mov     di, _ZN11CWaterLevel11m_aVerticesE.posY[esi]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E5F81 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// mov     ax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E5F88 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// cmp     ax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[esi]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E5FC2 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fld     _ZN11CWaterLevel11m_aVerticesE.posZ[esi]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E5FCE + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[edx]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E5FDC + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fld     _ZN11CWaterLevel11m_aVerticesE.posZ[ebx]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E5FE2 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[edx]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E5FEE + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fadd    _ZN11CWaterLevel11m_aVerticesE.posZ[edx]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E6009 + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E6017 + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E6022 + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E6029 + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E6036 + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fadd    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E604C + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E605A + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E6065 + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E606C + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E6079 + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fadd    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E60AC + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fld     _ZN11CWaterLevel11m_aVerticesE.posZ[esi]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E60B8 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[ebx]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E60C2 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fld     _ZN11CWaterLevel11m_aVerticesE.posZ[edx]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E60C8 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fsub    _ZN11CWaterLevel11m_aVerticesE.posZ[ebx]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E60D2 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// fadd    _ZN11CWaterLevel11m_aVerticesE.posZ[ebx]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E60ED + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E60FB + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E6104 + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fld     _ZN11CWaterLevel11m_aVerticesE.tU[edx*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E610B + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E6118 + 3, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fadd    _ZN11CWaterLevel11m_aVerticesE.tU[eax*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E612E + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E613C + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E6145 + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fld     _ZN11CWaterLevel11m_aVerticesE.tV[edx*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E614C + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fsub    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E6159 + 3, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fadd    _ZN11CWaterLevel11m_aVerticesE.tV[eax*4]	; _ZN11CWaterLevel27TestTriangleToGetWaterLevelEP14CWaterTrianglefffPfS2_S2_
			CPatch::PatchPointer(0x6E6484 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_
			CPatch::PatchPointer(0x6E64A3 + 4, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posX[eax*4]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_
			CPatch::PatchPointer(0x6E64BC + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]	; _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_
			CPatch::PatchPointer(0x6E64DC + 4, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[edx*4]	; _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_
			CPatch::PatchPointer(0x6E65E1 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_
			CPatch::PatchPointer(0x6E6604 + 4, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posX[eax*4]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_
			CPatch::PatchPointer(0x6E6621 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]	; _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_
			CPatch::PatchPointer(0x6E6645 + 4, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[edx*4]	; _ZN11CWaterLevel20TestLineAgainstWaterE7CVectorS0_PS0_
			CPatch::PatchPointer(0x6E7B97 + 4, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posX[eax*4]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel25FillQuadsAndTrianglesListEv
			CPatch::PatchPointer(0x6E7BB9 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   edx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel25FillQuadsAndTrianglesListEv
			CPatch::PatchPointer(0x6E7BD8 + 4, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   edx, _ZN11CWaterLevel11m_aVerticesE.posY[eax*4]	; _ZN11CWaterLevel25FillQuadsAndTrianglesListEv
			CPatch::PatchPointer(0x6E7BF3 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]	; _ZN11CWaterLevel25FillQuadsAndTrianglesListEv
			CPatch::PatchPointer(0x6E7C4E + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   ecx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[eax]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel25FillQuadsAndTrianglesListEv
			CPatch::PatchPointer(0x6E7C55 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[eax]	; _ZN11CWaterLevel25FillQuadsAndTrianglesListEv
			CPatch::PatchPointer(0x6E7C6F + 4, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posX[edx*4]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel25FillQuadsAndTrianglesListEv
			CPatch::PatchPointer(0x6E7C8A + 4, &CWaterLevel__m_aVertices.gta_sa -> posY);	// mov     cx, _ZN11CWaterLevel11m_aVerticesE.posY[edx*4]	; _ZN11CWaterLevel25FillQuadsAndTrianglesListEv
			CPatch::PatchPointer(0x6E7DF5 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// mov     bx, _ZN11CWaterLevel11m_aVerticesE.posY[edx]	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7E05 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// cmp     bx, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7E0E + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// mov     dx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7E15 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// cmp     dx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7E2E + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// cmp     bx, ss:_ZN11CWaterLevel11m_aVerticesE.posY[ebp]	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7E37 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// mov     cx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7E3E + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// cmp     cx, word ptr ss:_ZN11CWaterLevel11m_aVerticesE.posX[ebp]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7E57 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// mov     dx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E7E5E + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// cmp     dx, word ptr ss:_ZN11CWaterLevel11m_aVerticesE.posX[ebp]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel21AddWaterLevelTriangleEii7CRenPariiS0_iiS0_j
			CPatch::PatchPointer(0x6E8019 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// mov     ax, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E8026 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// mov     bx, _ZN11CWaterLevel11m_aVerticesE.posY[edx]	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E8047 + 4, &CWaterLevel__m_aVertices.gta_sa -> posY);	// mov     bp, _ZN11CWaterLevel11m_aVerticesE.posY[eax*4]	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E805D + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[eax]	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E8078 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// mov     ax, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E8085 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[eax]	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E8097 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// cmp     _ZN11CWaterLevel11m_aVerticesE.posY[ecx], bx	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E80BC + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// cmp     _ZN11CWaterLevel11m_aVerticesE.posY[edx], bx	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E80D5 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// cmp     _ZN11CWaterLevel11m_aVerticesE.posY[edx], bx	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E80F9 + 4, &CWaterLevel__m_aVertices.gta_sa -> posY);	// cmp     _ZN11CWaterLevel11m_aVerticesE.posY[edx*4], bx	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E8118 + 4, &CWaterLevel__m_aVertices.gta_sa -> posX);	// mov     dx, _ZN11CWaterLevel11m_aVerticesE.posX[ecx*4]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E8123 + 4, &CWaterLevel__m_aVertices.gta_sa -> posX);	// cmp     dx, _ZN11CWaterLevel11m_aVerticesE.posX[eax*4]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E813F + 4, &CWaterLevel__m_aVertices.gta_sa -> posX);	// mov     bx, _ZN11CWaterLevel11m_aVerticesE.posX[ebx*4]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E814A + 4, &CWaterLevel__m_aVertices.gta_sa -> posX);	// cmp     bx, _ZN11CWaterLevel11m_aVerticesE.posX[eax*4]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel17AddWaterLevelQuadEii7CRenPariiS0_iiS0_iiS0_j
			CPatch::PatchPointer(0x6E9E2C + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ebx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6E9E5F + 4, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   edx, _ZN11CWaterLevel11m_aVerticesE.posX[ecx*4]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6E9E8A + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[ebx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6E9EBD + 4, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   edx, _ZN11CWaterLevel11m_aVerticesE.posY[ecx*4]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6E9F07 + 2, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fld     _ZN11CWaterLevel11m_aVerticesE.tU[ebx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6E9F1E + 2, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fld     _ZN11CWaterLevel11m_aVerticesE.tV[ebx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6E9F3F + 2, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fld     _ZN11CWaterLevel11m_aVerticesE.tU[ecx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6E9F52 + 2, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fld     _ZN11CWaterLevel11m_aVerticesE.tV[ecx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6E9F6F + 2, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fld     _ZN11CWaterLevel11m_aVerticesE.tU[ecx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6E9F82 + 2, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fld     _ZN11CWaterLevel11m_aVerticesE.tV[ecx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6E9F9F + 2, &CWaterLevel__m_aVertices.gta_sa -> tU);	// fld     _ZN11CWaterLevel11m_aVerticesE.tU[ecx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6E9FB2 + 2, &CWaterLevel__m_aVertices.gta_sa -> tV);	// fld     _ZN11CWaterLevel11m_aVerticesE.tV[ecx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6E9FC5 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// mov     eax, _ZN11CWaterLevel11m_aVerticesE.posZ[ebx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6E9FFC + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   edx, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EA007 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EA03A + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[edx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EA049 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EA07C + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[esi]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EA08B + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[esi]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EA0EB + 3, &CWaterLevel__m_aVertices.gta_sa -> field_10);	// movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.field_10[ebx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EA0F2 + 3, &CWaterLevel__m_aVertices.gta_sa -> field_11);	// movsx   edx, _ZN11CWaterLevel11m_aVerticesE.field_11[ebx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EA146 + 3, &CWaterLevel__m_aVertices.gta_sa -> field_10);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.field_10[ecx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EA14D + 3, &CWaterLevel__m_aVertices.gta_sa -> field_11);	// movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.field_11[ecx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EA190 + 3, &CWaterLevel__m_aVertices.gta_sa -> field_10);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.field_10[edx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EA197 + 3, &CWaterLevel__m_aVertices.gta_sa -> field_11);	// movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.field_11[edx]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EA1C8 + 3, &CWaterLevel__m_aVertices.gta_sa -> field_10);	// movsx   edx, _ZN11CWaterLevel11m_aVerticesE.field_10[esi]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EA1CF + 3, &CWaterLevel__m_aVertices.gta_sa -> field_11);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.field_11[esi]	; _ZN11CWaterLevel26FindNearestWaterAndItsFlowEv
			CPatch::PatchPointer(0x6EFBF4 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// lea     edi, _ZN11CWaterLevel11m_aVerticesE.posZ[eax]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFC15 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   edi, _ZN11CWaterLevel11m_aVerticesE.posY[eax]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFC1C + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[eax]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFC33 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// lea     eax, _ZN11CWaterLevel11m_aVerticesE.posZ[ecx]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFC54 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   eax, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFC5B + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   ecx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[ecx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFC6A + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// lea     eax, _ZN11CWaterLevel11m_aVerticesE.posZ[edx]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFC8B + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posY[edx]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFC92 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   edx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFD8D + 3, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// lea     edi, _ZN11CWaterLevel11m_aVerticesE.posZ[edi*4]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFDC0 + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// lea     edi, _ZN11CWaterLevel11m_aVerticesE.posZ[ecx]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFDC8 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posY[ecx]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFDEE + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// lea     edi, _ZN11CWaterLevel11m_aVerticesE.posZ[edx]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFDF6 + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   edx, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[edx]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFE1C + 2, &CWaterLevel__m_aVertices.gta_sa -> posZ);	// lea     edi, _ZN11CWaterLevel11m_aVerticesE.posZ[eax]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFE27 + 3, &CWaterLevel__m_aVertices.gta_sa -> posY);	// movsx   ecx, _ZN11CWaterLevel11m_aVerticesE.posY[eax]	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFE2E + 3, &CWaterLevel__m_aVertices.gta_sa -> posX);	// movsx   eax, word ptr _ZN11CWaterLevel11m_aVerticesE.posX[eax]; CWaterLevel::m_aVertices	; _ZN11CWaterLevel11RenderWaterEv
		}
		#endif
	}
	#elif defined(IS_PLATFORM_ANDROID)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if (iNumberOfWaterVertices > this->WaterVerticesLimit)
		{
			CWaterLevel__m_aVertices.gta_sa = new CWaterVertice[iNumberOfWaterVertices];
			CWaterLevel__m_aVertices.bIsAllocated.Set(true);
		}

		// Patch pointer
		CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x678980), CWaterLevel__m_aVertices.gta_sa);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->WaterVerticesLimit = iNumberOfWaterVertices;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of WATER LIMITS -> Water vertices to: %d",
		iNumberOfWaterVertices);
	CGenericLogStorage::WriteLineSeparator();
}

#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
namespace Game_GTASA
{
	
	extern "C"
	{
		unsigned int BlocksToBeRenderedOutsideWorldLimitMinusOne = 0;
	}

	// patch for 0x59868C
	extern "C"
	{
		uintptr_t Address_CWaterLevel__BlockHit_598694_thumb = 0;
	}

	static TARGET_THUMB NAKED void patch_CWaterLevel__BlockHit_59868C()
	{
		__asm(
		".thumb\n"
			ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(R0, BlocksToBeRenderedOutsideWorldLimitMinusOne)
			"IT GT\n"
			"POPGT {R4,R5,R7,PC}\n"
			"LDR R1, =("/* _ZN11CWaterLevel33m_BlocksToBeRenderedOutsideWorldXE_ptr */"0x6777C4 - 0x59869C)\n"
			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(Address_CWaterLevel__BlockHit_598694_thumb)
			);
	}
}
#endif

// Sets the blocks to be rendered outside world
void WaterLimits::SetBlocksToBeRenderedOutsideWorld(unsigned int iNumberOfBlocks)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iNumberOfBlocks = this->BlocksToBeRenderedOutsideWorldLimit;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		if (iNumberOfBlocks > this->BlocksToBeRenderedOutsideWorldLimit)
		{
			CWaterLevel__m_BlocksToBeRenderedOutsideWorldX.ptr = new int16_t[iNumberOfBlocks];
			CWaterLevel__m_BlocksToBeRenderedOutsideWorldX.bIsAllocated.Set(true);

			CWaterLevel__m_BlocksToBeRenderedOutsideWorldY.ptr = new int16_t[iNumberOfBlocks];
			CWaterLevel__m_BlocksToBeRenderedOutsideWorldY.bIsAllocated.Set(true);
		}

		// Patch pointers to CWaterLevel::m_BlocksToBeRenderedOutsideWorldX
		#if TRUE
		{
			CPatch::PatchPointer(0x6E6CF6 + 4, CWaterLevel__m_BlocksToBeRenderedOutsideWorldX.ptr);	// mov     _ZN11CWaterLevel33m_BlocksToBeRenderedOutsideWorldXE[eax*2], di; CWaterLevel::m_BlocksToBeRenderedOutsideWorldX	; _ZN11CWaterLevel8BlockHitEii
			CPatch::PatchPointer(0x6EF6E8 + 4, CWaterLevel__m_BlocksToBeRenderedOutsideWorldX.ptr);	// movsx   edi, _ZN11CWaterLevel33m_BlocksToBeRenderedOutsideWorldXE[ebp*2]; CWaterLevel::m_BlocksToBeRenderedOutsideWorldX	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFE95 + 4, CWaterLevel__m_BlocksToBeRenderedOutsideWorldX.ptr);	// mov     ax, _ZN11CWaterLevel33m_BlocksToBeRenderedOutsideWorldXE[edi*2]; CWaterLevel::m_BlocksToBeRenderedOutsideWorldX	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFEAF + 4, CWaterLevel__m_BlocksToBeRenderedOutsideWorldX.ptr);	// movsx   eax, _ZN11CWaterLevel33m_BlocksToBeRenderedOutsideWorldXE[edi*2]; CWaterLevel::m_BlocksToBeRenderedOutsideWorldX	; _ZN11CWaterLevel11RenderWaterEv
		}
		#endif

		// Patch pointers to CWaterLevel::m_BlocksToBeRenderedOutsideWorldY
		#if TRUE
		{
			CPatch::PatchPointer(0x6E6CEE + 4, CWaterLevel__m_BlocksToBeRenderedOutsideWorldY.ptr);	// mov     _ZN11CWaterLevel33m_BlocksToBeRenderedOutsideWorldYE[eax*2], si; CWaterLevel::m_BlocksToBeRenderedOutsideWorldY	; _ZN11CWaterLevel8BlockHitEii
			CPatch::PatchPointer(0x6EF6E0 + 4, CWaterLevel__m_BlocksToBeRenderedOutsideWorldY.ptr);	// movsx   esi, _ZN11CWaterLevel33m_BlocksToBeRenderedOutsideWorldYE[ebp*2]; CWaterLevel::m_BlocksToBeRenderedOutsideWorldY	; _ZN11CWaterLevel11RenderWaterEv
			CPatch::PatchPointer(0x6EFE82 + 4, CWaterLevel__m_BlocksToBeRenderedOutsideWorldY.ptr);	// mov     cx, _ZN11CWaterLevel33m_BlocksToBeRenderedOutsideWorldYE[edi*2]; CWaterLevel::m_BlocksToBeRenderedOutsideWorldY	; _ZN11CWaterLevel11RenderWaterEv
		}
		#endif
		
		// Define variables for automatic patch
		#if TRUE
		{
			CCodeMover::SetVariable("NUMBER_OF_BLOCKS", iNumberOfBlocks);
		}
		#endif

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 1
			CCodeMover::FixOnAddressRel(0x6E6CE9, 5, "\x01\x01\x3d\x05\x04""NUMBER_OF_BLOCKS\x00\x01\x02\x0F\x8D\x15\x04\x6d\x2e\x00\x00", 0x6E6CEE);	// line 1, 0x6E6CA0 - _ZN11CWaterLevel8BlockHitEii : cmp     eax, 70
		}
		#endif

		// Undefine variable of automatic patch
		CCodeMover::DeleteVariable("NUMBER_OF_BLOCKS");
	}
	#elif defined(IS_PLATFORM_ANDROID_ARMEABI_V7A)
	else if (gameVersion == GAME_VERSION_GTA_SA_2_00_ANDROID_ARMEABI_V7A)
	{
		using namespace Game_GTASA;

		if (iNumberOfBlocks > this->BlocksToBeRenderedOutsideWorldLimit)
		{
			CWaterLevel__m_BlocksToBeRenderedOutsideWorldX.ptr = new int16_t[iNumberOfBlocks];
			CWaterLevel__m_BlocksToBeRenderedOutsideWorldX.bIsAllocated.Set(true);

			CWaterLevel__m_BlocksToBeRenderedOutsideWorldY.ptr = new int16_t[iNumberOfBlocks];
			CWaterLevel__m_BlocksToBeRenderedOutsideWorldY.bIsAllocated.Set(true);
		}

		// Set variables
		BlocksToBeRenderedOutsideWorldLimitMinusOne = iNumberOfBlocks - 1;

		// Patch pointers
		{
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x6777C4), CWaterLevel__m_BlocksToBeRenderedOutsideWorldX.ptr);
			CPatch::PatchPointer(g_mCalc.GetCurrentVAbyPreferedVA(0x678A84), CWaterLevel__m_BlocksToBeRenderedOutsideWorldY.ptr);
		}

		// Changes
		Address_CWaterLevel__BlockHit_598694_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x598694));
		CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x59868C),
			(void*)&patch_CWaterLevel__BlockHit_59868C, 8
		);
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->BlocksToBeRenderedOutsideWorldLimit = iNumberOfBlocks;
	CPatch::LeaveThisLevel();

	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of WATER LIMITS -> Blocks to be rendered outside world to: %d",
		iNumberOfBlocks);
	CGenericLogStorage::WriteLineSeparator();
}

// Initialize
void WaterLimits::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		using namespace Game_GTASA;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				// Water triangles
				this->CWaterLevel__m_aTriangles.gta_sa = (CWaterTriangle*)0xC22854;

				// Water quads
				this->CWaterLevel__m_aQuads.gta_sa = (CWaterQuad*)0xC21C90;

				// Quads and triangles list
				this->CWaterLevel__m_QuadsAndTrianglesList.ptr = (int16_t*)0xC215F6;

				// Water vertices
				this->CWaterLevel__m_aVertices.gta_sa = (CWaterVertice*)0xC22910;

				// Blocks to be rendered outside world
				this->CWaterLevel__m_BlocksToBeRenderedOutsideWorldX.ptr = (int16_t*)0xC214D0;
				this->CWaterLevel__m_BlocksToBeRenderedOutsideWorldY.ptr = (int16_t*)0xC21560;
			}
			#elif defined(IS_PLATFORM_ANDROID_ARM32)
			{
				// Water triangles
				this->CWaterLevel__m_aTriangles.gta_sa = (CWaterTriangle*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN11CWaterLevel12m_aTrianglesE"
				);;

				// Water quads
				this->CWaterLevel__m_aQuads.gta_sa = (CWaterQuad*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN11CWaterLevel8m_aQuadsE"
				);

				// Quads and triangles list
				this->CWaterLevel__m_QuadsAndTrianglesList.ptr = (int16_t*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN11CWaterLevel23m_QuadsAndTrianglesListE"
				);

				// Water vertices
				this->CWaterLevel__m_aVertices.gta_sa = (CWaterVertice*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN11CWaterLevel11m_aVerticesE"
				);

				// Blocks to be rendered outside world
				this->CWaterLevel__m_BlocksToBeRenderedOutsideWorldX.ptr = (int16_t*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN11CWaterLevel33m_BlocksToBeRenderedOutsideWorldXE"
				);
				this->CWaterLevel__m_BlocksToBeRenderedOutsideWorldY.ptr = (int16_t*)Library::GetSymbolAddress(
					&g_LimitAdjuster.hModule_of_game,
					"_ZN11CWaterLevel33m_BlocksToBeRenderedOutsideWorldYE"
				);
			}
			#endif
		}

		// Water quads limit
		this->WaterQuadsLimit = 301;

		// Water triangles limit
		this->WaterTrianglesLimit = 6;

		// Water quads and triangles list limit
		this->WaterQuadsAndTrianglesListLimit = 701;

		// Water vertices limit
		this->WaterVerticesLimit = 1021;

		// Blocks to be rendered outside world limit
		this->BlocksToBeRenderedOutsideWorldLimit = 70;
	}
}

// Shutdown
void WaterLimits::Shutdown()
{
	MAKE_VAR_GAME_VERSION();

	if (CWaterLevel__m_QuadsAndTrianglesList.bIsAllocated.Get())
		delete[] CWaterLevel__m_QuadsAndTrianglesList.ptr;

	if (CWaterLevel__m_BlocksToBeRenderedOutsideWorldX.bIsAllocated.Get())
		delete[] CWaterLevel__m_BlocksToBeRenderedOutsideWorldX.ptr;

	if (CWaterLevel__m_BlocksToBeRenderedOutsideWorldY.bIsAllocated.Get())
		delete[] CWaterLevel__m_BlocksToBeRenderedOutsideWorldY.ptr;

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		if(CWaterLevel__m_aTriangles.bIsAllocated.Get())
			delete[] CWaterLevel__m_aTriangles.gta_sa;

		if (CWaterLevel__m_aQuads.bIsAllocated.Get())
			delete[] CWaterLevel__m_aQuads.gta_sa;

		if (CWaterLevel__m_aVertices.bIsAllocated.Get())
			delete[] CWaterLevel__m_aVertices.gta_sa;
	}
}
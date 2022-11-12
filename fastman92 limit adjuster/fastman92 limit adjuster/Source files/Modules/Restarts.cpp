/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "Restarts.h"

#include "../Core/CGenericLogStorage.h"
#include "../Core/CPatch.h"
#include "../Core/LimitAdjuster.h"
#include "StructureExtension.h"

using namespace Game;

Restarts g_Restarts;

// Sets hospital restart locations
void Restarts::SetHospitalRestarts(int iHospitalRestarts)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iHospitalRestarts = this->HospitalRestartsLimit;

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
	{
		if (iHospitalRestarts > this->HospitalRestartsLimit)
		{
			CRestart__HospitalRestartPoints.ptr = new CVector[iHospitalRestarts];
			CRestart__HospitalRestartPoints.bIsAllocated.Set(true);

			CRestart__HospitalRestartHeadings.ptr = new float[iHospitalRestarts];
			CRestart__HospitalRestartHeadings.bIsAllocated.Set(true);

			CRestart__HospitalRestartWhenToUse.ptr = new int[iHospitalRestarts];
			CRestart__HospitalRestartWhenToUse.bIsAllocated.Set(true);
		}		

		// Patch references to CRestart::HospitalRestartPoints
		#if TRUE
		{
			CPatch::PatchPointer(0x460749 + 3, CRestart__HospitalRestartPoints.ptr);	// lea     edx, _ZN8CRestart21HospitalRestartPointsE.x[edx*4]; CRestart::HospitalRestartPoints	; sub_460730
			CPatch::PatchPointer(0x46098F + 3, CRestart__HospitalRestartPoints.ptr);	// fsub    ds:_ZN8CRestart21HospitalRestartPointsE.x[eax*4]; CRestart::HospitalRestartPoints	; sub_460850
			CPatch::PatchPointer(0x460996 + 3, CRestart__HospitalRestartPoints.ptr);	// lea     eax, _ZN8CRestart21HospitalRestartPointsE.x[eax*4]; CRestart::HospitalRestartPoints	; sub_460850
			CPatch::PatchPointer(0x460A16 + 3, CRestart__HospitalRestartPoints.ptr);	// lea     ecx, _ZN8CRestart21HospitalRestartPointsE.x[edx*4]; CRestart::HospitalRestartPoints	; sub_460850
			CPatch::PatchPointer(0x5D3646 + 3, CRestart__HospitalRestartPoints.ptr);	// lea     ecx, _ZN8CRestart21HospitalRestartPointsE.x[eax*4]; CRestart::HospitalRestartPoints	; sub_5D3620
			CPatch::PatchPointer(0x5D3797 + 3, CRestart__HospitalRestartPoints.ptr);	// lea     ecx, _ZN8CRestart21HospitalRestartPointsE.x[eax*4]; CRestart::HospitalRestartPoints	; sub_5D3770
			CPatch::PatchPointer(0x1565918 + 1, CRestart__HospitalRestartPoints.ptr);	// mov     edx, offset _ZN8CRestart21HospitalRestartPointsE; CRestart::HospitalRestartPoints	; _ZN8CRestart10InitialiseEv
		}
		#endif

		// Patch references to CRestart::HospitalRestartHeadings
		#if TRUE
		{
			CPatch::PatchPointer(0x460762 + 3, CRestart__HospitalRestartHeadings.ptr);	// fstp    ds:_ZN8CRestart23HospitalRestartHeadingsE[eax*4]; CRestart::HospitalRestartHeadings	; sub_460730
			CPatch::PatchPointer(0x460A31 + 3, CRestart__HospitalRestartHeadings.ptr);	// mov     edx, ds:_ZN8CRestart23HospitalRestartHeadingsE[eax*4]; CRestart::HospitalRestartHeadings	; sub_460850
			CPatch::PatchPointer(0x5D3655 + 3, CRestart__HospitalRestartHeadings.ptr);	// lea     edx, _ZN8CRestart23HospitalRestartHeadingsE[esi*4]; CRestart::HospitalRestartHeadings	; sub_5D3620
			CPatch::PatchPointer(0x5D37A6 + 3, CRestart__HospitalRestartHeadings.ptr);	// lea     edx, _ZN8CRestart23HospitalRestartHeadingsE[esi*4]; CRestart::HospitalRestartHeadings	; sub_5D3770
			CPatch::PatchPointer(0x15658ED + 1, CRestart__HospitalRestartHeadings.ptr);	// mov     edi, offset _ZN8CRestart23HospitalRestartHeadingsE; CRestart::HospitalRestartHeadings	; _ZN8CRestart10InitialiseEv
		}
		#endif

		// Patch references to CRestart::HospitalRestartWhenToUse
		#if TRUE
		{
			CPatch::PatchPointer(0x46076C + 3, CRestart__HospitalRestartWhenToUse.ptr);	// mov     ds:_ZN8CRestart24HospitalRestartWhenToUseE[eax*4], edx; CRestart::HospitalRestartWhenToUse	; sub_460730
			CPatch::PatchPointer(0x460968 + 3, CRestart__HospitalRestartWhenToUse.ptr);	// fild    ds:_ZN8CRestart24HospitalRestartWhenToUseE[esi*4]; CRestart::HospitalRestartWhenToUse	; sub_460850
			CPatch::PatchPointer(0x5D3664 + 3, CRestart__HospitalRestartWhenToUse.ptr);	// lea     eax, _ZN8CRestart24HospitalRestartWhenToUseE[esi*4]; CRestart::HospitalRestartWhenToUse	; sub_5D3620
			CPatch::PatchPointer(0x5D37B5 + 3, CRestart__HospitalRestartWhenToUse.ptr);	// lea     eax, _ZN8CRestart24HospitalRestartWhenToUseE[esi*4]; CRestart::HospitalRestartWhenToUse	; sub_5D3770
		}
		#endif

		// Patch the number of elements / size
		#if TRUE
		{
			CPatch::PatchUINT32(0x15658E8 + 1, iHospitalRestarts);	// mov     ecx, 10
			CPatch::PatchUINT32(0x156591D + 1, iHospitalRestarts);	// mov     eax, 10
		}
		#endif
	}
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->HospitalRestartsLimit = iHospitalRestarts;
	
	CGenericLogStorage::SaveFormattedTextLn("Modified limit of hospital restarts to: %d", iHospitalRestarts);
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

// Sets police restart locations
void Restarts::SetPoliceRestarts(int iPoliceRestarts)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPoliceRestarts = this->PoliceRestartsLimit;

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
	{
		if (iPoliceRestarts > this->PoliceRestartsLimit)
		{
			CRestart__PoliceRestartPoints.ptr = new CVector[iPoliceRestarts];
			CRestart__PoliceRestartPoints.bIsAllocated.Set(true);

			CRestart__PoliceRestartHeadings.ptr = new float[iPoliceRestarts];
			CRestart__PoliceRestartHeadings.bIsAllocated.Set(true);

			CRestart__PoliceRestartWhenToUse.ptr = new int[iPoliceRestarts];
			CRestart__PoliceRestartWhenToUse.bIsAllocated.Set(true);
		}		

		// Patch references to CRestart::PoliceRestartPoints
		#if TRUE
		{
			CPatch::PatchPointer(0x460799 + 3, CRestart__PoliceRestartPoints.ptr);	// lea     edx, _ZN8CRestart19PoliceRestartPointsE.x[edx*4]; CRestart::PoliceRestartPoints	; _ZN8CRestart21AddPoliceRestartPointERK7CVectorfi
			CPatch::PatchPointer(0x460B8F + 3, CRestart__PoliceRestartPoints.ptr);	// fsub    ds:_ZN8CRestart19PoliceRestartPointsE.x[eax*4]; CRestart::PoliceRestartPoints	; _ZN8CRestart29FindClosestPoliceRestartPointE7CVectorPS0_Pf
			CPatch::PatchPointer(0x460B96 + 3, CRestart__PoliceRestartPoints.ptr);	// lea     eax, _ZN8CRestart19PoliceRestartPointsE.x[eax*4]; CRestart::PoliceRestartPoints	; _ZN8CRestart29FindClosestPoliceRestartPointE7CVectorPS0_Pf
			CPatch::PatchPointer(0x460C16 + 3, CRestart__PoliceRestartPoints.ptr);	// lea     ecx, _ZN8CRestart19PoliceRestartPointsE.x[edx*4]; CRestart::PoliceRestartPoints	; _ZN8CRestart29FindClosestPoliceRestartPointE7CVectorPS0_Pf
			CPatch::PatchPointer(0x5D36A6 + 3, CRestart__PoliceRestartPoints.ptr);	// lea     edx, _ZN8CRestart19PoliceRestartPointsE.x[ecx*4]; CRestart::PoliceRestartPoints	; sub_5D3620
			CPatch::PatchPointer(0x5D37F6 + 3, CRestart__PoliceRestartPoints.ptr);	// lea     edx, _ZN8CRestart19PoliceRestartPointsE.x[ecx*4]; CRestart::PoliceRestartPoints	; sub_5D3770
			CPatch::PatchPointer(0x1565964 + 1, CRestart__PoliceRestartPoints.ptr);	// mov     edx, offset _ZN8CRestart19PoliceRestartPointsE; CRestart::PoliceRestartPoints	; _ZN8CRestart10InitialiseEv
		}
		#endif

		// Patch references to CRestart::PoliceRestartHeadings
		#if TRUE
		{
			CPatch::PatchPointer(0x4607B2 + 3, CRestart__PoliceRestartHeadings.ptr);	// fstp    ds:_ZN8CRestart21PoliceRestartHeadingsE[eax*4]; CRestart::PoliceRestartHeadings	; _ZN8CRestart21AddPoliceRestartPointERK7CVectorfi
			CPatch::PatchPointer(0x460C31 + 3, CRestart__PoliceRestartHeadings.ptr);	// mov     edx, ds:_ZN8CRestart21PoliceRestartHeadingsE[eax*4]; CRestart::PoliceRestartHeadings	; _ZN8CRestart29FindClosestPoliceRestartPointE7CVectorPS0_Pf
			CPatch::PatchPointer(0x5D36B5 + 3, CRestart__PoliceRestartHeadings.ptr);	// lea     eax, _ZN8CRestart21PoliceRestartHeadingsE[esi*4]; CRestart::PoliceRestartHeadings	; sub_5D3620
			CPatch::PatchPointer(0x5D3805 + 3, CRestart__PoliceRestartHeadings.ptr);	// lea     eax, _ZN8CRestart21PoliceRestartHeadingsE[esi*4]; CRestart::PoliceRestartHeadings	; sub_5D3770
			CPatch::PatchPointer(0x1565939 + 1, CRestart__PoliceRestartHeadings.ptr);	// mov     edi, offset _ZN8CRestart21PoliceRestartHeadingsE; CRestart::PoliceRestartHeadings	; _ZN8CRestart10InitialiseEv
		}
		#endif

		// Patch references to CRestart::PoliceRestartWhenToUse
		#if TRUE
		{
			CPatch::PatchPointer(0x4607BC + 3, CRestart__PoliceRestartWhenToUse.ptr);	// mov     ds:_ZN8CRestart22PoliceRestartWhenToUseE[eax*4], edx; CRestart::PoliceRestartWhenToUse	; _ZN8CRestart21AddPoliceRestartPointERK7CVectorfi
			CPatch::PatchPointer(0x460B68 + 3, CRestart__PoliceRestartWhenToUse.ptr);	// fild    ds:_ZN8CRestart22PoliceRestartWhenToUseE[esi*4]; CRestart::PoliceRestartWhenToUse	; _ZN8CRestart29FindClosestPoliceRestartPointE7CVectorPS0_Pf
			CPatch::PatchPointer(0x5D36C4 + 3, CRestart__PoliceRestartWhenToUse.ptr);	// lea     ecx, _ZN8CRestart22PoliceRestartWhenToUseE[esi*4]; CRestart::PoliceRestartWhenToUse	; sub_5D3620
			CPatch::PatchPointer(0x5D3814 + 3, CRestart__PoliceRestartWhenToUse.ptr);	// lea     ecx, _ZN8CRestart22PoliceRestartWhenToUseE[esi*4]; CRestart::PoliceRestartWhenToUse	; sub_5D3770
		}
		#endif

		// Patch the number of elements / size
		#if TRUE
		{
			CPatch::PatchUINT32(0x1565934 + 1, iPoliceRestarts);	// mov     ecx, 10
			CPatch::PatchUINT32(0x1565969 + 1, iPoliceRestarts);	// mov     eax, 10
		}
		#endif
	}
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	this->HospitalRestartsLimit = iPoliceRestarts;

	CGenericLogStorage::SaveFormattedTextLn("Modified limit of police restarts to: %d", iPoliceRestarts);
	CGenericLogStorage::WriteLineSeparator();

	CPatch::LeaveThisLevel();
}

// Initializes class
void Restarts::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (CGameVersion::IsAny_GTA_SA(gameVersion))
	{
		this->HospitalRestartsLimit = 10;
		this->PoliceRestartsLimit = 10;

		if (g_LimitAdjuster.IsGameVersionSetUpWithMemory())
		{
			#ifdef IS_PLATFORM_WIN_X86
			if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
			{
				this->CRestart__HospitalRestartPoints.ptr = (CVector*)0xA43318;
				this->CRestart__HospitalRestartHeadings.ptr = (float*)0xA432E8;
				this->CRestart__HospitalRestartWhenToUse.ptr = (int*)0xA432C0;

				this->CRestart__PoliceRestartPoints.ptr = (CVector*)0xA43390;
				this->CRestart__PoliceRestartHeadings.ptr = (float*)0xA43298;
				this->CRestart__PoliceRestartWhenToUse.ptr = (int*)0xA43270;
			}
			#endif
		}
	}
}

// Shutdown
void Restarts::Shutdown()
{
	// hospital restart
	if (CRestart__HospitalRestartPoints.bIsAllocated.Get())
		delete[] CRestart__HospitalRestartPoints.ptr;

	if (CRestart__HospitalRestartHeadings.bIsAllocated.Get())
		delete[] CRestart__HospitalRestartHeadings.ptr;
	
	if (CRestart__HospitalRestartWhenToUse.bIsAllocated.Get())
		delete[] CRestart__HospitalRestartWhenToUse.ptr;

	// police restart
	if (CRestart__PoliceRestartPoints.bIsAllocated.Get())
		delete[] CRestart__PoliceRestartPoints.ptr;

	if (CRestart__PoliceRestartHeadings.bIsAllocated.Get())
		delete[] CRestart__PoliceRestartHeadings.ptr;

	if (CRestart__PoliceRestartWhenToUse.bIsAllocated.Get())
		delete[] CRestart__PoliceRestartWhenToUse.ptr;
}
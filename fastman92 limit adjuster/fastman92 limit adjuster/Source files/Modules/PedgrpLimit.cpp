/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "PedgrpLimit.h"
#include "../Core/CPatch.h"
#include "../Core/CCodeMover.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/LimitAdjuster.h"

using namespace Game;

PedgrpLimit g_pedGrpLimits;

// Pedsgrp peds per group
void PedgrpLimit::SetPedsPerGroupLimit(unsigned int iPedsPerGroup)
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevel();
	// CPatch::EnableDebugMode();

	if (CPatch::IsDebugModeActive())
		iPedsPerGroup = this->m_iPedsPerGroup;

	MAKE_DEAD_IF();
	#ifdef IS_PLATFORM_WIN_X86
	else if(gameVersion == GAME_VERSION_GTA_SA_1_0_US_HOODLUM_WIN_X86)
	{
		// Allocate if neccessary
		if (iPedsPerGroup > this->m_iPedsPerGroup)
		{
			CPopulation__m_PedGroups.ptr = new uint16_t[m_iNumberOfPedGroups * iPedsPerGroup];
			memset(CPopulation__m_PedGroups.ptr, NULL, m_iNumberOfPedGroups * iPedsPerGroup * sizeof(uint16_t));
			CPopulation__m_PedGroups.bIsAllocated.Set(true);
		}

		this->m_iPedsPerGroup = iPedsPerGroup;

		// Patch pointers to CPopulation::m_PedGroups
		#if TRUE
		{
			CPatch::PatchPointer(0x406ECF + 4, CPopulation__m_PedGroups.ptr);	// cmp     ds:_ZN11CPopulation11m_PedGroupsE[eax*2], 7D0h; CPopulation::m_PedGroups	; 
			CPatch::PatchPointer(0x40A82A + 4, CPopulation__m_PedGroups.ptr);	// movzx   esi, ds:_ZN11CPopulation11m_PedGroupsE[edx*2]; CPopulation::m_PedGroups	; sub_40A560
			CPatch::PatchPointer(0x40A8DD + 4, CPopulation__m_PedGroups.ptr);	// movzx   ecx, ds:_ZN11CPopulation11m_PedGroupsE[eax*2]; CPopulation::m_PedGroups	; sub_40A560
			CPatch::PatchPointer(0x40A9B9 + 4, CPopulation__m_PedGroups.ptr);	// movzx   ecx, ds:_ZN11CPopulation11m_PedGroupsE[eax*2]; CPopulation::m_PedGroups	; sub_40A560
			CPatch::PatchPointer(0x40AB41 + 4, CPopulation__m_PedGroups.ptr);	// movzx   edx, ds:_ZN11CPopulation11m_PedGroupsE[edx*2]; CPopulation::m_PedGroups	; sub_40AA10
			CPatch::PatchPointer(0x40AB69 + 4, CPopulation__m_PedGroups.ptr);	// movzx   eax, ds:_ZN11CPopulation11m_PedGroupsE[edx*2]; CPopulation::m_PedGroups	; sub_40AA10
			CPatch::PatchPointer(0x40ABB7 + 4, CPopulation__m_PedGroups.ptr);	// movzx   esi, ds:_ZN11CPopulation11m_PedGroupsE[eax*2]; CPopulation::m_PedGroups	; sub_40AA10
			CPatch::PatchPointer(0x40AC14 + 4, CPopulation__m_PedGroups.ptr);	// movzx   ecx, ds:_ZN11CPopulation11m_PedGroupsE[eax*2]; CPopulation::m_PedGroups	; sub_40AA10
			CPatch::PatchPointer(0x40B909 + 4, CPopulation__m_PedGroups.ptr);	// movzx   ecx, ds:_ZN11CPopulation11m_PedGroupsE[eax*2]; CPopulation::m_PedGroups	; sub_40B700
			CPatch::PatchPointer(0x40B91E + 4, CPopulation__m_PedGroups.ptr);	// movzx   esi, ds:_ZN11CPopulation11m_PedGroupsE[eax*2]; CPopulation::m_PedGroups	; sub_40B700
			CPatch::PatchPointer(0x40BC37 + 4, CPopulation__m_PedGroups.ptr);	// movzx   edi, ds:_ZN11CPopulation11m_PedGroupsE[edx*2]; CPopulation::m_PedGroups	; sub_40BBB0
			CPatch::PatchPointer(0x40BC90 + 4, CPopulation__m_PedGroups.ptr);	// movzx   esi, ds:_ZN11CPopulation11m_PedGroupsE[ecx*2]; CPopulation::m_PedGroups	; sub_40BBB0
			CPatch::PatchPointer(0x40BD3E + 4, CPopulation__m_PedGroups.ptr);	// movzx   esi, ds:_ZN11CPopulation11m_PedGroupsE[edx*2]; CPopulation::m_PedGroups	; sub_40BBB0
			CPatch::PatchPointer(0x40BD48 + 4, CPopulation__m_PedGroups.ptr);	// movzx   edi, ds:_ZN11CPopulation11m_PedGroupsE[ecx*2]; CPopulation::m_PedGroups	; sub_40BBB0
			CPatch::PatchPointer(0x4439F0 + 1, CPopulation__m_PedGroups.ptr);	// add     eax, offset _ZN11CPopulation11m_PedGroupsE; CPopulation::m_PedGroups	; sub_4439D0
			CPatch::PatchPointer(0x443A5B + 4, CPopulation__m_PedGroups.ptr);	// movzx   eax, ds:_ZN11CPopulation11m_PedGroupsE[ecx*2]; CPopulation::m_PedGroups	; sub_443A20
			CPatch::PatchPointer(0x4448D8 + 3, CPopulation__m_PedGroups.ptr);	// movzx   eax, ds:_ZN11CPopulation11m_PedGroupsE[edx]; CPopulation::m_PedGroups	; 
			CPatch::PatchPointer(0x44540C + 3, CPopulation__m_PedGroups.ptr);	// movzx   edx, ds:_ZN11CPopulation11m_PedGroupsE[ecx]; CPopulation::m_PedGroups	; sub_4453D0
			CPatch::PatchPointer(0x5B9F42 + 4, CPopulation__m_PedGroups.ptr);	// mov     ds:_ZN11CPopulation11m_PedGroupsE[eax*2], cx; CPopulation::m_PedGroups	; 
			CPatch::PatchPointer(0x5B9F5D + 4, CPopulation__m_PedGroups.ptr);	// mov     ds:_ZN11CPopulation11m_PedGroupsE[eax*2], 7D0h; CPopulation::m_PedGroups	; 
			CPatch::PatchPointer(0x5BD105 + 4, CPopulation__m_PedGroups.ptr);	// mov     ds:_ZN11CPopulation11m_PedGroupsE[ecx*2], dx; CPopulation::m_PedGroups	; sub_5BCFE0
			CPatch::PatchPointer(0x5BD13E + 3, CPopulation__m_PedGroups.ptr);	// lea     edi, _ZN11CPopulation11m_PedGroupsE[edi*2]; CPopulation::m_PedGroups	; sub_5BCFE0
			CPatch::PatchPointer(0x5DE60B + 4, CPopulation__m_PedGroups.ptr);	// movzx   ecx, ds:_ZN11CPopulation11m_PedGroupsE[ecx*2]; CPopulation::m_PedGroups	; sub_5DE5A0
			CPatch::PatchPointer(0x5DE64D + 4, CPopulation__m_PedGroups.ptr);	// movzx   eax, ds:_ZN11CPopulation11m_PedGroupsE[ecx*2]; CPopulation::m_PedGroups	; sub_5DE5A0
			CPatch::PatchPointer(0x5DE66D + 3, CPopulation__m_PedGroups.ptr);	// movzx   eax, ds:_ZN11CPopulation11m_PedGroupsE[ecx]; CPopulation::m_PedGroups	; sub_5DE5A0
			CPatch::PatchPointer(0x60FECB + 4, CPopulation__m_PedGroups.ptr);	// movzx   eax, ds:_ZN11CPopulation11m_PedGroupsE[eax*2]; CPopulation::m_PedGroups	; sub_60FBD0
			CPatch::PatchPointer(0x610092 + 4, CPopulation__m_PedGroups.ptr);	// movzx   eax, ds:_ZN11CPopulation11m_PedGroupsE[eax*2]; CPopulation::m_PedGroups	; sub_60FFD0
			CPatch::PatchPointer(0x6101D8 + 1, CPopulation__m_PedGroups.ptr);	// add     eax, offset _ZN11CPopulation11m_PedGroupsE; CPopulation::m_PedGroups	; sub_610150
			CPatch::PatchPointer(0x610243 + 1, CPopulation__m_PedGroups.ptr);	// add     eax, offset _ZN11CPopulation11m_PedGroupsE; CPopulation::m_PedGroups	; sub_610210
			CPatch::PatchPointer(0x1560E3D + 4, CPopulation__m_PedGroups.ptr);	// movzx   eax, ds:_ZN11CPopulation11m_PedGroupsE[eax*2]; CPopulation::m_PedGroups	; sub_1560E20
			CPatch::PatchPointer(0x1562AD4 + 4, CPopulation__m_PedGroups.ptr);	// mov     ax, ds:_ZN11CPopulation11m_PedGroupsE[ecx*2]; CPopulation::m_PedGroups	; sub_15629D0
			CPatch::PatchPointer(0x1562B8C + 4, CPopulation__m_PedGroups.ptr);	// movzx   ecx, ds:_ZN11CPopulation11m_PedGroupsE[eax*2]; CPopulation::m_PedGroups	; sub_15629D0
		}
		#endif

		// Patch the values
		#if TRUE
		{
			CPatch::PatchUINT32(0x40A67D + 1, iPedsPerGroup);
			CPatch::PatchUINT32(0x5BD135 + 1, iPedsPerGroup);
		}
		#endif


		// Define variable for automatic patch
		CCodeMover::SetVariable("NUMBER_OF_PEDGRP_PEDS_PER_GROUP", iPedsPerGroup);
		CCodeMover::SetVariable("SIZE_OF_ONE_PED_GROUP", iPedsPerGroup * sizeof(uint16_t));

		// Apply automatic patch
		#if TRUE
		{
			// Count of active addresses: 32
			CCodeMover::FixOnAddressRel(0x406EC8, 5, "\x01\x02\x69\xc0\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\xCB\x6E\x40\x00\x00", 0x406ECD);	// line 1, 0x406EB0 - sub_406EB0 : imul    eax, 15h
			CCodeMover::FixOnAddressRel(0x40A825, 5, "\x01\x02\x69\xd2\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\x28\xA8\x40\x00\x00", 0x40A82A);	// line 2, 0x40A560 - sub_40A560 : imul    edx, 15h
			CCodeMover::FixOnAddressRel(0x40A8D8, 5, "\x01\x02\x69\xc0\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\xDB\xA8\x40\x00\x00", 0x40A8DD);	// line 3, 0x40A560 - sub_40A560 : imul    eax, 15h
			CCodeMover::FixOnAddressRel(0x40A9B4, 5, "\x01\x02\x69\xc0\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\xB7\xA9\x40\x00\x00", 0x40A9B9);	// line 4, 0x40A560 - sub_40A560 : imul    eax, 15h
			CCodeMover::FixOnAddressRel(0x40AB32, 8, "\x01\x02\x69\xc9\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x05\x35\xAB\x40\x00\x00", 0x40AB3A);	// line 5, 0x40AA10 - sub_40AA10 : imul    ecx, 15h
			CCodeMover::FixOnAddressRel(0x40AB5E, 5, "\x01\x02\x69\xc9\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x01\x61\xAB\x40\x00\x02\x01\x62\xAB\x40\x00\x00", 0x40AB63);	// line 6, 0x40AA10 - sub_40AA10 : imul    ecx, 15h
			CCodeMover::FixOnAddressRel(0x40ABB2, 5, "\x01\x02\x69\xc0\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\xB5\xAB\x40\x00\x00", 0x40ABB7);	// line 7, 0x40AA10 - sub_40AA10 : imul    eax, 15h
			CCodeMover::FixOnAddressRel(0x40AC0F, 5, "\x01\x02\x69\xc0\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\x12\xAC\x40\x00\x00", 0x40AC14);	// line 8, 0x40AA10 - sub_40AA10 : imul    eax, 15h
			CCodeMover::FixOnAddressRel(0x40B900, 5, "\x01\x02\x69\xc0\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\x03\xB9\x40\x00\x00", 0x40B905);	// line 9, 0x40B700 - sub_40B700 : imul    eax, 15h
			CCodeMover::FixOnAddressRel(0x40BC30, 5, "\x01\x02\x69\xc9\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\x33\xBC\x40\x00\x00", 0x40BC35);	// line 10, 0x40BBB0 - sub_40BBB0 : imul    ecx, 15h
			CCodeMover::FixOnAddressRel(0x40BC89, 5, "\x01\x02\x69\xc9\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\x8C\xBC\x40\x00\x00", 0x40BC8E);	// line 11, 0x40BBB0 - sub_40BBB0 : imul    ecx, 15h
			CCodeMover::FixOnAddressRel(0x40BD36, 6, "\x01\x02\x69\xd2\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x01\x02\x69\xc9\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x00", 0x40BD3C);	// line 12, 0x40BBB0 - sub_40BBB0 : imul    edx, 15h
			CCodeMover::FixOnAddressRel(0x4439ED, 8, "\x01\x02\x69\xc0\x05\x04""SIZE_OF_ONE_PED_GROUP\x00\x02\x05\xF0\x39\x44\x00\x00", 0x4439F5);	// line 13, 0x4439D0 - sub_4439D0 : imul    eax, 2Ah
			CCodeMover::FixOnAddressRel(0x443A53, 6, "\x01\x02\x69\xc9\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x01\x56\x3A\x44\x00\x02\x02\x57\x3A\x44\x00\x00", 0x443A59);	// line 14, 0x443A20 - sub_443A20 : imul    ecx, 15h
			CCodeMover::FixOnAddressRel(0x4448D5, 10, "\x01\x02\x69\xd2\x05\x04""SIZE_OF_ONE_PED_GROUP\x00\x02\x07\xD8\x48\x44\x00\x00", 0x4448DF);	// line 15, 0x444810 - sub_444810 : imul    edx, 2Ah
			CCodeMover::FixOnAddressRel(0x445409, 10, "\x01\x02\x69\xc9\x05\x04""SIZE_OF_ONE_PED_GROUP\x00\x02\x07\x0C\x54\x44\x00\x00", 0x445413);	// line 16, 0x4453D0 - sub_4453D0 : imul    ecx, 42
			CCodeMover::FixOnAddressRel(0x5B9F38, 5, "\x01\x02\x69\xc0\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\x3B\x9F\x5B\x00\x00", 0x5B9F3D);	// line 17, 0x5B9F30 - sub_5B9F30 : imul    eax, 21
			CCodeMover::FixOnAddressRel(0x5B9F58, 5, "\x01\x02\x69\xc0\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\x5B\x9F\x5B\x00\x00", 0x5B9F5D);	// line 18, 0x5B9F50 - sub_5B9F50 : imul    eax, 21
			CCodeMover::FixOnAddressRel(0x5BD10F, 5, "\x01\x02\x81\xfd\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\x12\xD1\x5B\x00\x00", 0x5BD114);	// line 19, 0x5BCFE0 - readPedgrpDat : cmp     ebp, 21
			CCodeMover::FixOnAddressRel(0x5BD122, 7, "\x01\x02\x81\xfb\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x04\x25\xD1\x5B\x00\x00", 0x5BD129);	// line 20, 0x5BCFE0 - readPedgrpDat : cmp     ebx, 21
			CCodeMover::FixOnAddressRel(0x5BD15C, 7, "\x01\x01\x05\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x04\x5F\xD1\x5B\x00\x00", 0x5BD163);	// line 21, 0x5BCFE0 - readPedgrpDat : add     eax, 15h
			CCodeMover::FixOnAddressRel(0x5DE606, 5, "\x01\x02\x69\xc9\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\x09\xE6\x5D\x00\x00", 0x5DE60B);	// line 22, 0x5DE5A0 - sub_5DE5A0 : imul    ecx, 15h
			CCodeMover::FixOnAddressRel(0x5DE647, 6, "\x01\x02\x69\xc9\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x01\x4A\xE6\x5D\x00\x02\x02\x4B\xE6\x5D\x00\x00", 0x5DE64D);	// line 23, 0x5DE5A0 - sub_5DE5A0 : imul    ecx, 15h
			CCodeMover::FixOnAddressRel(0x5DE66A, 10, "\x01\x02\x69\xc9\x05\x04""SIZE_OF_ONE_PED_GROUP\x00\x02\x07\x6D\xE6\x5D\x00\x00", 0x5DE674);	// line 24, 0x5DE5A0 - sub_5DE5A0 : imul    ecx, 42
			CCodeMover::FixOnAddressRel(0x60FEC6, 5, "\x01\x02\x69\xc0\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\xC9\xFE\x60\x00\x00", 0x60FECB);	// line 25, 0x60FBD0 - sub_60FBD0 : imul    eax, 21
			CCodeMover::FixOnAddressRel(0x61008D, 5, "\x01\x02\x69\xc0\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\x90\x00\x61\x00\x00", 0x610092);	// line 26, 0x60FFD0 - sub_60FFD0 : imul    eax, 21
			CCodeMover::FixOnAddressRel(0x6101D5, 8, "\x01\x02\x69\xc0\x05\x04""SIZE_OF_ONE_PED_GROUP\x00\x02\x05\xD8\x01\x61\x00\x00", 0x6101DD);	// line 27, 0x610150 - sub_610150 : imul    eax, 42
			CCodeMover::FixOnAddressRel(0x610240, 8, "\x01\x02\x69\xc0\x05\x04""SIZE_OF_ONE_PED_GROUP\x00\x02\x05\x43\x02\x61\x00\x00", 0x610248);	// line 28, 0x610210 - sub_610210 : imul    eax, 42
			CCodeMover::FixOnAddressRel(0x1560E38, 5, "\x01\x02\x69\xc0\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\x3B\x0E\x56\x01\x00", 0x1560E3D);	// line 29, 0x1560E20 - sub_1560E20 : imul    eax, 15h
			CCodeMover::FixOnAddressRel(0x1562ACF, 5, "\x01\x02\x69\xc9\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\xD2\x2A\x56\x01\x00", 0x1562AD4);	// line 30, 0x15629D0 - sub_15629D0 : imul    ecx, 15h
			CCodeMover::FixOnAddressRel(0x1562B87, 5, "\x01\x02\x69\xc0\x05\x04""NUMBER_OF_PEDGRP_PEDS_PER_GROUP\x00\x02\x02\x8A\x2B\x56\x01\x00", 0x1562B8C);	// line 31, 0x15629D0 - sub_15629D0 : imul    eax, 15h
		}
		#endif

		// Delete a variable
		CCodeMover::DeleteVariable("NUMBER_OF_PEDGRP_PEDS_PER_GROUP");
		CCodeMover::DeleteVariable("SIZE_OF_ONE_PED_GROUP");	
	}
	#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	/////////////// FINISH ///////////////
	CGenericLogStorage::SaveFormattedTextLn(
		"Modified limit of PED STREAMING: Pedgrp peds per group to: %d",
		iPedsPerGroup
		);

	CGenericLogStorage::WriteLineSeparator();
	CPatch::LeaveThisLevel();
}

// Initialize
void PedgrpLimit::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		#ifdef IS_PLATFORM_WIN_X86
		// Ped groups
		this->CPopulation__m_PedGroups.ptr = (uint16_t*)0xC0F358;
		#endif

		// Number of ped groups
		this->m_iNumberOfPedGroups = 57;

		// Number of peds per group
		this->m_iPedsPerGroup = 21;
	}
}

// Shutdown
void PedgrpLimit::Shutdown()
{
	if (CPopulation__m_PedGroups.bIsAllocated.Get())
		delete[] CPopulation__m_PedGroups.ptr;
}
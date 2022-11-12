/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CSceneEdit.h"

#include "CCamera.h"
#include "CFileMgr.h"
#include "CPad.h"

#include <string.h>

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTAIII
{
	// variables
	bool CSceneEdit::m_bEditOn;
	bool CSceneEdit::m_bRecording;
	bool CSceneEdit::m_bDrawGotoArrow;
	CVector CSceneEdit::m_vecCameraPosition;
	CVector CSceneEdit::m_vecCurrentPosition;
	CVector CSceneEdit::m_vecGotoPosition;
	bool CSceneEdit::m_bCommandActive;
	int16_t CSceneEdit::m_nCurrentCommand;
	int16_t CSceneEdit::m_nCurrentActor;
	int CSceneEdit::m_nNumActors;
	int16_t CSceneEdit::m_nCurrentVehicle;
	int16_t CSceneEdit::m_nNumVehicles;
	void** CSceneEdit::m_pCommand;
	void* CSceneEdit::m_Command;
	bool CSceneEdit::m_bActorSelected;
	bool CSceneEdit::m_bActor2Selected;
	bool CSceneEdit::m_bVehicleSelected;
	int16_t CSceneEdit::m_nActor;
	int16_t CSceneEdit::m_nActor2;
	CPed* CSceneEdit::pActors[5];
	int16_t CSceneEdit::m_nVehicle;
	int16_t CSceneEdit::m_nVehicle2;
	CVehicle_generic* CSceneEdit::pVehicles[5];
	int16_t CSceneEdit::m_nWeaponType;
	char CSceneEdit::Movie[720];
	int16_t CSceneEdit::m_nNumMovieCommands;
	int16_t CSceneEdit::m_nCurrentMovieCommand;
	int16_t CSceneEdit::m_nArrows;
	int CSceneEdit::m_nPedmodelId;
	int CSceneEdit::m_nVehiclemodelId;
	CVector CSceneEdit::m_vecCamHeading;
	bool CSceneEdit::m_bCameraFollowActor;

	// Performs initialization
	void CSceneEdit::Initialise()
	{
		CSceneEdit::m_bRecording = 1;
		CSceneEdit::m_bCommandActive = 0;
		CSceneEdit::m_bEditOn = 0;
		*((char*)TheCamera + *(int8_t*)((char*)TheCamera + 118) * 420 + 430) = 1;

		CSceneEdit::m_nVehicle2 = -1;
		CSceneEdit::m_nPedmodelId = 7;
		CSceneEdit::m_nVehiclemodelId = 101;
		CSceneEdit::m_nCurrentCommand = 1;

		CSceneEdit::m_vecCamHeading = *(CVector*)((char*)TheCamera + *(int8_t*)((char*)TheCamera + 118) * 420 + 0x2E4);

		CSceneEdit::m_nNumMovieCommands = 0;
		CSceneEdit::m_nVehicle = -1;
		CSceneEdit::m_nNumActors = 0;
		CSceneEdit::m_nNumVehicles = 0;

		memset(CSceneEdit::pActors, 0, sizeof(CSceneEdit::pActors));
		memset(CSceneEdit::pVehicles, 0, sizeof(CSceneEdit::pVehicles));

		CSceneEdit::m_nActor = -1;
		CSceneEdit::m_nActor2 = -1;
		CSceneEdit::m_bCameraFollowActor = 0;
		CSceneEdit::m_bDrawGotoArrow = 0;
		memset(&CSceneEdit::m_vecGotoPosition, 0, sizeof(CSceneEdit::m_vecGotoPosition));
	}

	// Performs reinitialisation
	void CSceneEdit::ReInitialise()
	{
		// FASTMAN92_TODO
	}

	// Shuts down
	void CSceneEdit::Shutdown()
	{

	}

	// Loads movie
	void CSceneEdit::LoadMovie()
	{
		CSceneEdit::ReInitialise();
		CFileMgr::SetDir("DATA");
		FILESTREAM fp = CFileMgr::OpenFile("movie.dat", "r");
		CFileMgr::Read(fp, CSceneEdit::Movie, sizeof(CSceneEdit::Movie));
		CFileMgr::Read(fp, &CSceneEdit::m_nNumMovieCommands, 2);
		CFileMgr::CloseFile(fp);
		CFileMgr::SetDir("");
		CSceneEdit::m_bCommandActive = 0;
	}

	// Saves movie
	void CSceneEdit::SaveMovie()
	{
		CFileMgr::SetDir("DATA");
		FILESTREAM fp = CFileMgr::OpenFileForWriting("movie.dat");

		if (fp)
		{
			CFileMgr::Write(fp, CSceneEdit::Movie, sizeof(CSceneEdit::Movie));

			CFileMgr::Write(fp,
				&CSceneEdit::m_nNumMovieCommands,
				sizeof(CSceneEdit::m_nNumMovieCommands)
			);

			CFileMgr::CloseFile(fp);
		}

		CFileMgr::SetDir("");
		CSceneEdit::m_bCommandActive = 0;		
	}


	// Plays
	void CSceneEdit::PlayBack()
	{
		// FASTMAN92_TODO
	}

	// Processs command
	void CSceneEdit::ProcessCommand()
	{
		// FASTMAN92_TODO
	}

	// Updates
	void CSceneEdit::Update()
	{
		if (!CSceneEdit::m_bEditOn)
			return;

		if (CSceneEdit::m_bRecording)
			CSceneEdit::ProcessCommand();
		else
		{
			if (CSceneEdit::m_bCameraFollowActor && CSceneEdit::m_nActor != -1)
			{
				CPed* pPed = CSceneEdit::pActors[CSceneEdit::m_nActor];
				
				if (*((bool*)pPed + 0x314))	// m_bInVehicle
				{
					CVehicle_generic* pVehicle = *(CVehicle_generic**)((char*)pPed + 0x310);
					TheCamera->TakeControl(pVehicle, 3, 2, 1);
				}
				else
					TheCamera->TakeControl(pPed, 4, 2, 1);
			}
			CSceneEdit::PlayBack();
		}
	}

	// Clears variables for a new command
	void CSceneEdit::ClearForNewCommand()
	{
		CSceneEdit::m_nActor = -1;
		CSceneEdit::m_nActor2 = -1;
		CSceneEdit::m_bDrawGotoArrow = 0;
		CSceneEdit::m_nVehicle = -1;
		CSceneEdit::m_bActorSelected = 0;
		CSceneEdit::m_bActor2Selected = 0;
		CSceneEdit::m_bVehicleSelected = 0;
	}

	// Selects a weapon
	bool CSceneEdit::SelectWeapon()
	{
		if (!CSceneEdit::m_nWeaponType)
		{
			CSceneEdit::m_nWeaponType = 2;
			return false;
		}

		CPad* pPad = CPad::GetPad(1);

		if (*(int16_t *)((char*)pPad + 8) && !*(int16_t *)((char*)pPad + 58))
		{
			if (++CSceneEdit::m_nWeaponType > 11)
				CSceneEdit::m_nWeaponType = 1;
		}

		// FASTMAN92_TODO
		return false;
	}
}
#endif
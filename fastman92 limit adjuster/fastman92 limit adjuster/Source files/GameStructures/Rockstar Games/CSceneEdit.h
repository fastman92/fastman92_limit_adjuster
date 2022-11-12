/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPed.h"
#include "CVehicle.h"

#include <CVector.h>

#include <stdint.h>

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTAIII
{
	// CSceneEdit
	class CSceneEdit
	{
		// variables
		static bool m_bEditOn;
		static bool m_bRecording;
		static bool m_bDrawGotoArrow;
		static CVector m_vecCameraPosition;
		static CVector m_vecCurrentPosition;
		static CVector m_vecGotoPosition;
		static bool m_bCommandActive;
		static int16_t m_nCurrentCommand;
		static int16_t m_nCurrentActor;
		static int m_nNumActors;
		static int16_t m_nCurrentVehicle;
		static int16_t m_nNumVehicles;
		static void** m_pCommand;
		static void* m_Command;
		static bool m_bActorSelected;
		static bool m_bActor2Selected;
		static bool m_bVehicleSelected;
		static int16_t m_nActor;
		static int16_t m_nActor2;
		static CPed* pActors[5];
		static int16_t m_nVehicle;
		static int16_t m_nVehicle2;
		static CVehicle_generic* pVehicles[5];
		static int16_t m_nWeaponType;
		static char Movie[720];
		static int16_t m_nNumMovieCommands;
		static int16_t m_nCurrentMovieCommand;
		static int16_t m_nArrows;
		static int m_nPedmodelId;
		static int m_nVehiclemodelId;
		static CVector m_vecCamHeading;
		static bool m_bCameraFollowActor;

	public:
		// Performs initialization
		void Initialise();

		// Performs reinitialisation
		void ReInitialise();

		// Shuts down
		void Shutdown();

		// Loads movie
		void LoadMovie();

		// Saves movie
		void SaveMovie();

		// Draws a scene editor stuff
		void Draw();

		// Initialises a playback
		void InitPlayBack();

		// Plays
		void PlayBack();

		// Processs command
		void ProcessCommand();

		// Updates
		void Update();


		/////
		// Clears variables for a new command
		void ClearForNewCommand();

		// Selects an actor
		bool SelectActor();

		// Selects an actor 2
		bool SelectActor2();

		// Selects a vehicle
		bool SelectVehicle();

		// Selects a weapon
		bool SelectWeapon();

	};
}
#endif
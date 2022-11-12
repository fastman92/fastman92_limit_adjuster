/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <CVector.h>
#include "../Core/CLimitAdjusterModule.h"

class Restarts : public CLimitAdjusterModule
{
public:
	int HospitalRestartsLimit;
	int PoliceRestartsLimit;		

	struct {
		CVector* ptr;
		DEFINE_IS_ALLOCATED();
	} CRestart__HospitalRestartPoints;

	struct {
		float* ptr;
		DEFINE_IS_ALLOCATED();
	} CRestart__HospitalRestartHeadings;

	struct {
		int* ptr;
		DEFINE_IS_ALLOCATED();
	} CRestart__HospitalRestartWhenToUse;

	struct {
		CVector* ptr;
		DEFINE_IS_ALLOCATED();
	} CRestart__PoliceRestartPoints;

	struct {
		float* ptr;
		DEFINE_IS_ALLOCATED();
	} CRestart__PoliceRestartHeadings;

	struct {
		int* ptr;
		DEFINE_IS_ALLOCATED();
	} CRestart__PoliceRestartWhenToUse;

	// Sets hospital restart locations
	void SetHospitalRestarts(int iHospitalRestarts);

	// Sets police restart locations
	void SetPoliceRestarts(int iPoliceRestarts);

	// Initializes class
	void Initialise();

	// Shutdown
	virtual void Shutdown();
};

extern Restarts g_Restarts;
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <CompressedVector.h>
#include <CVector.h>
#include "../Core/CLimitAdjusterModule.h"
#include <stdint.h>

namespace Game_GTASA
{
	class CCarGenerator
	{
	public:
		uint16_t modelID;
		char color1;
		char color2;
		CompressedVector pos;
		char angle;
		char alarm;
		char doorLock;
		char RelatedToPlayerOwned;
		int16_t field_E;
		int16_t moneyValue;
		int16_t field_12;
		int time;
		int16_t field_18;
		int16_t enabled;
		uint8_t iplFile;
		char allocated;
		int16_t field_1E;
	};

	VALIDATE_SIZE(CCarGenerator, 0x20);

	class CCarGenerator_extended : public CCarGenerator
	{
	public:
		uint16_t lastRandomizedID;
		uint16_t exIplFile;
		CVector exPos;

		//// version of 0x30 bytes /////
	};

	VALIDATE_SIZE(CCarGenerator_extended, 0x30);

	class CTheCarGenerators
	{
	public:
		static const int COORD_INT_MULTIPLIER = 8;

		// Returns car generator ID
		static uint16_t __cdecl GetCarGeneratorIDfromPointer(void* pCarGenerator);

		// Removes car generators with specified IPL file ID
		static void __cdecl RemoveCarGenerators(uint16_t iplFile);
	};
}

class CarGeneratorLimit : public CLimitAdjusterModule
{
public:	
	uint32_t CCarGenerator_size;

	bool bIsCarGeneratorFormatExtended;

	// current limit of car generators
	int iCarGenerators;

	bool bIsSaveBlockLoadingFunctionPatched;

	// Number of car generators.
	int* CTheCarGenerators__NumOfCarGenerators;

	// Process counter
	uint8_t* CTheCarGenerators__ProcessCounter;

	// GenerateEvenIfPlayerIsCloseCounter
	char* CTheCarGenerators__GenerateEvenIfPlayerIsCloseCounter;

	// Array of car generators
	struct {
		void* ptr;
		DEFINE_IS_ALLOCATED();
	} CTheCarGenerators__CarGeneratorArray;

	// Checks if extended format is neccessary.
	bool IsFormatExtendedNeccessary();

	// Patches number of process counter passes
	// Function must be executed when limit of car generators isn't going to be patched anymore.
	void PatchNumberOfProcessCounterPasses(int8_t counterPasses = 4);

	// Patches car generator limit
	void PatchCarGeneratorsLimit(int iCarGenerators = 500, bool bUseExtendedFormat = false);

	// Accepts any ID for car generator
	void AcceptAnyIDforCarGenerator();
	
	// Patches a function that loads car generators from savefile.
	void PatchCarGeneratorSaveBlockLoadingFunction();

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();

private:
	// Fixes shl size of car generator
	void FixShlInstruction(uint32_t dwAddress, const char* data);
};

extern CarGeneratorLimit g_carGeneratorLimits;
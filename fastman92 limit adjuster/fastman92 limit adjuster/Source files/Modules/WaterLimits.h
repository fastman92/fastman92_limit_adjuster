/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "Assertions.h"
#include "../Core/CLimitAdjusterModule.h"
#include <stdint.h>

namespace Game_GTASA
{
	struct CWaterVertice
	{
	  int16_t posX;
	  int16_t posY;
	  float posZ;
	  int tU;
	  int tV;
	  char field_10;
	  char field_11;
	  char gap_12[1];
	  char field_13;
	};

	VALIDATE_SIZE(CWaterVertice, 0x14);

	struct CWaterQuad
	{
	  int16_t field_0;
	  int16_t field_2;
	  int16_t field_4;
	  int16_t field_6;
	  int16_t m_flags;
	};

	VALIDATE_SIZE(CWaterQuad, 0xA);

	struct CWaterTriangle
	{
	  int16_t field_0;
	  int16_t field_2;
	  int16_t field_4;
	  uint16_t field_6;
	};

	VALIDATE_SIZE(CWaterTriangle, 8);
};

class WaterLimits : public CLimitAdjusterModule
{
public:
	// Water triangles
	struct {
		union {
			Game_GTASA::CWaterTriangle* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CWaterLevel__m_aTriangles;

	// Water quads
	struct {
		union {
			Game_GTASA::CWaterQuad* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CWaterLevel__m_aQuads;

	// Quads and triangles list
	struct {
		int16_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CWaterLevel__m_QuadsAndTrianglesList;

	// Water vertices
	struct {
		union {
			Game_GTASA::CWaterVertice* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} CWaterLevel__m_aVertices;

	// Blocks to be rendered outside world
	struct {
		int16_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CWaterLevel__m_BlocksToBeRenderedOutsideWorldX;

	struct {
		int16_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CWaterLevel__m_BlocksToBeRenderedOutsideWorldY;

	// Water quads limit
	unsigned int WaterQuadsLimit;

	// Water triangles limit
	unsigned int WaterTrianglesLimit;

	// Water quads and triangles list limit
	unsigned int WaterQuadsAndTrianglesListLimit;

	// Water vertices limit
	unsigned int WaterVerticesLimit;

	// Blocks to be rendered outside world limit
	unsigned int BlocksToBeRenderedOutsideWorldLimit;

	// Sets water quads
	void SetWaterQuads(unsigned int iNumberOfWaterQuads);

	// Sets water triangles
	void SetWaterTriangles(unsigned int iNumberOfWaterTriangles);

	// Sets quads and triangles list
	void SetQuadsAndTrianglesList(unsigned int iNumberOfQuadsAndTrianglesList);

	// Sets the water vertices
	void SetWaterVertices(unsigned int iNumberOfWaterVertices);

	// Sets the blocks to be rendered outside world
	void SetBlocksToBeRenderedOutsideWorld(unsigned int iNumberOfBlocks);

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();
};

extern WaterLimits g_waterLimits;
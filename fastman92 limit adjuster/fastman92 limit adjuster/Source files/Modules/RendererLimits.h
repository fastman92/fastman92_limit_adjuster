/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"

class RendererLimits : public CLimitAdjusterModule
{
public:
	int ms_InvisibleEntityPtrsLimit;
	int ms_VisibleSuperLodPtrsLimit;
	int ms_VisibleLodPtrsLimit;
	int ms_VisibleEntityPtrsLimit;

	struct {
		void** ptr;
		DEFINE_IS_ALLOCATED();
	} CRenderer__ms_aInVisibleEntityPtrs;

	struct {
		void** ptr;
		DEFINE_IS_ALLOCATED();
	} CRenderer__ms_aVisibleSuperLodPtrs;

	struct {
		void** ptr;
		DEFINE_IS_ALLOCATED();
	} CRenderer__ms_aVisibleLodPtrs;

	struct {
		void** ptr;
		DEFINE_IS_ALLOCATED();
	} CRenderer__ms_aVisibleEntityPtrs;

	// Sets the invisible entity pointers
	void SetInvisibleEntityPtrs(int iInvisibleEntityPtrs);

	// Sets the visible super LOD pointers
	void SetVisibleSuperLodPtrs(int iVisibleSuperLodPtrs);

	// Sets the visible LOD pointers
	void SetVisibleLodPtrs(int iVisibleLodPtrs);

	// Sets the visible entity pointers
	void SetVisibleEntityPtrs(int iVisibleEntityPtrs);

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();
};

extern RendererLimits g_rendererLimits;
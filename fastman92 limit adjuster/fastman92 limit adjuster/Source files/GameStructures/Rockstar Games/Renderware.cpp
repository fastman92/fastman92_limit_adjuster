/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "Renderware.h"

#include "../../Core/LimitAdjuster.h"

#include "../../Core/FormattedOutput.h"

Renderware_VarInitialisation g_Renderware_varInitialisation;

MAKE_RwObject(RwObject, STRUCTURE_STATIC_MEMBER_DEFINITION);
MAKE_RxPipeline(RxPipeline, STRUCTURE_STATIC_MEMBER_DEFINITION);
MAKE_RwGlobals(RwGlobals, STRUCTURE_STATIC_MEMBER_DEFINITION);

RwGlobals** RwEngineInstance;

RwInt32(*_rwerror)(RwInt32 code, ...);

static uintptr_t Address_RwErrorSet = 0;
void RwErrorSet(RwError* pError)
{
	return g_memoryCall.Function<void>(Address_RwErrorSet, pError);
}

// Initialize
void Renderware_VarInitialisation::Initialise()
{
	MAKE_VAR_GAME_VERSION();

	// RwObject
	{
		g_StructAllocator.InitPerStruct();

		g_StructAllocator.Allocate(RwObject::type);
		g_StructAllocator.Allocate(RwObject::subType);
		g_StructAllocator.Allocate(RwObject::flags);
		g_StructAllocator.Allocate(RwObject::privateFlags);
		g_StructAllocator.Allocate(RwObject::parent);

		g_StructAllocator.Allocate(RwObject::endOfStructure);
	}

	// RxPipeline
	{
		g_StructAllocator.InitPerStruct();

		g_StructAllocator.Allocate(RxPipeline::locked);
		g_StructAllocator.Allocate(RxPipeline::numNodes);
		g_StructAllocator.Allocate(RxPipeline::nodes);
		g_StructAllocator.Allocate(RxPipeline::packetNumClusterSlots);
		g_StructAllocator.Allocate(RxPipeline::embeddedPacketState);
		g_StructAllocator.Allocate(RxPipeline::embeddedPacket);
		g_StructAllocator.Allocate(RxPipeline::numInputRequirements);
		g_StructAllocator.Allocate(RxPipeline::numInputRequirements);
		g_StructAllocator.Allocate(RxPipeline::inputRequirements);
		g_StructAllocator.Allocate(RxPipeline::superBlock);
		g_StructAllocator.Allocate(RxPipeline::superBlockSize);
		g_StructAllocator.Allocate(RxPipeline::entryPoint);
		g_StructAllocator.Allocate(RxPipeline::pluginId);
		g_StructAllocator.Allocate(RxPipeline::pluginData);

		g_StructAllocator.Allocate(RxPipeline::endOfStructure);
	}

	// RwGlobals
	{
		g_StructAllocator.InitPerStruct();

		g_StructAllocator.Allocate(RwGlobals::curCamera);
		g_StructAllocator.Allocate(RwGlobals::curWorld);
		g_StructAllocator.Allocate(RwGlobals::renderFrame);
		g_StructAllocator.Allocate(RwGlobals::lightFrame);
		g_StructAllocator.Allocate(RwGlobals::pad, 2);
		g_StructAllocator.Allocate(RwGlobals::dOpenDevice);
		g_StructAllocator.Allocate(RwGlobals::stdFunc, 29);
		g_StructAllocator.Allocate(RwGlobals::dirtyFrameList);
		g_StructAllocator.Allocate(RwGlobals::fileFuncs, 11);
		g_StructAllocator.Allocate(RwGlobals::stringFuncs, 15);
		g_StructAllocator.Allocate(RwGlobals::memoryFuncs);
		g_StructAllocator.Allocate(RwGlobals::memoryAlloc);
		g_StructAllocator.Allocate(RwGlobals::memoryFree);
		g_StructAllocator.Allocate(RwGlobals::metrics);
		g_StructAllocator.Allocate(RwGlobals::engineStatus);
		g_StructAllocator.Allocate(RwGlobals::resArenaInitSize);

		g_StructAllocator.Allocate(RwGlobals::endOfStructure);
	}

	#if IS_PLATFORM_ANDROID
	_rwerror = (decltype(_rwerror))Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_Z8_rwerroriz"
	);

	Address_RwErrorSet = (uintptr_t)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"_Z10RwErrorSetP7RwError"
	);

	RwEngineInstance = (RwGlobals**)Library::GetSymbolAddress(
		&g_LimitAdjuster.hModule_of_game,
		"RwEngineInstance"
	);
	#endif
}
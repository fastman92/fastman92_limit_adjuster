/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assertions.h>
#include "RwV3D.h"

#include "../../Core\CLimitAdjusterModule.h"

#include <DynamicTypes/DynamicStructure.h>

typedef long RwFixed;
typedef int  RwInt32;
typedef unsigned int RwUInt32;
typedef short RwInt16;
typedef unsigned short RwUInt16;
typedef unsigned char RwUInt8;
typedef signed char RwInt8;

#define MAKE_RwObject(structName, macro) \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt8>), type); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt8>), subType); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt8>), flags); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt8>), privateFlags); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, void*>), parent); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tDynamicStructEnd>), endOfStructure);

struct RwObject : public CDynamicStructure
{
	MAKE_RwObject(RwObject, STRUCTURE_STATIC_MEMBER_DECLARATION);
};

struct RpClump : public CDynamicStructure {};
struct RpAtomic : public CDynamicStructure {};

namespace Game_GTASA
{
	struct RwPluginRegEntry
	{
		int offset;
		int sizeOfStruct;
		int pluginID;
		int readCB;
		int writeCB;
		int getSizeCB;
		int alwaysCB;
		int rightsCB;
		int constructCB;
		int destructCB;
		int copyCB;
		int errStrCB;
		RwPluginRegEntry *nextRegEntry;
		int prevregEntry;
		int parentRegistry;
	};

	struct RwPluginRegistry
	{
		int sizeOfStruct;
		int origSizeOfStruct;
		int maxSizeOfStruct;
		int staticAlloc;
		RwPluginRegEntry *firstRegEntry;
		int lastRegEntry;
	};

	struct RwFrame;

	struct RwLLLink
	{
		RwFrame *next;
		RwFrame* prev;
	};

	struct RwLinkList
	{
		RwLLLink link;
	};

	struct RwMatrix
	{
		RwV3D right;
		int flags;
		RwV3D top;
		int pad1;
		RwV3D at;
		int pad2;
		RwV3D pos;
		int pad3;
	};

	VALIDATE_SIZE(RwMatrix, 0x40);

	struct RwObject
	{
		char type;
		char subType;
		char flags;
		char privateFlags;
		RwFrame *parent;
	};

	struct RwFrame
	{
		RwObject object;
		RwLLLink inDirtyListLink;
		RwMatrix modelling;
		RwMatrix ltm;
		RwLinkList objectList;
		RwFrame *child;
		RwFrame *next;
		RwFrame *root;
	};

	struct RxPipelineNodeParam
	{
		int dataParam;
		int heap;
	};

	struct tMemoryRestorerEntry
	{
		void* ptr;
		int iSize;
		char data[128];
	};

	struct RpAtomic;

	struct RpHAnimHierarchy
	{
		int flags;
		int numNodes;
		RwMatrix* pMatrixArray;
		RwMatrix* pMatrixArrayUnaligned;
		int pNodeInfo;
		int parentFrame;
		int parentHierarchy;
		int rootParentOffset;
		int currentAnim;
	};
}

struct RwBBox
{
  RwV3D sup;
  RwV3D inf;
};

class Renderware_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern Renderware_VarInitialisation g_Renderware_varInitialisation;
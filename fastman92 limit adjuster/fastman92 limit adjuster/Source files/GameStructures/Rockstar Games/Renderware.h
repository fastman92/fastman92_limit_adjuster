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
typedef RwInt32 RwBool;
typedef float RwReal;

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

/**
 * \ingroup rwcoregeneric
 * \struct RxPipelineNode
 * Structure describing a pipeline Node;
 * that is an \ref RxNodeDefinition in the context
 * of a specific \ref RxPipeline.
 */
struct RxPipelineNode
{
	struct RxNodeDefinition   *nodeDef;            /**< Node definition reference */
	RwUInt32            numOutputs;         /**< Output count */
	RwUInt32           *outputs;            /**< Output array, indexing the pipeline's array of pipeline nodes */
	struct RxPipelineCluster **slotClusterRefs;    /**< For packets passing through this node, SlotClusterRefs[n]
											 * identifies the cluster to be found at index n in the packet's
											 * Clusters[] array. These assignments are determined at pipeline
											 * Unlock() time and are good for the life of the pipeline. */
	RwUInt32           *slotsContinue;      /**< Cluster persistence table for the node's outputs */
	void               *privateData;        /**< Pointer to the pipeline Node's private data */
	RwUInt32           *inputToClusterSlot; /**< LUT to locate clusters of interest in packets passing through this pipeline Node */
	struct RxPipelineNodeTopSortData *topSortData; /**< Internal Use */
	void               *initializationData; /**< Used by the pipeline node initialisation
											 * function in setting up the Private data. */
	RwUInt32        initializationDataSize; /**< Present so that if the node is cloned
											 * we can copy the initialisation data. */
};

typedef int rxEmbeddedPacketState;
struct RxPipelineRequiresCluster;
struct RxPacket;

#define MAKE_RxPipeline(structName, macro) \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwBool>), locked); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt32>), numNodes); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RxPipelineNode*>), nodes); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt32>), packetNumClusterSlots); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, rxEmbeddedPacketState>), embeddedPacketState); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RxPacket*>), embeddedPacket); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt32>), numInputRequirements); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RxPipelineRequiresCluster*>), inputRequirements); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, void*>), superBlock); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt32>), superBlockSize); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt32>), entryPoint); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt32>), pluginId); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt32>), pluginData); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tDynamicStructEnd>), endOfStructure);

struct RxPipeline : public CDynamicStructure
{
	MAKE_RxPipeline(RxPipeline, STRUCTURE_STATIC_MEMBER_DECLARATION);
};


struct RwLLLink
{
	RwLLLink *next;
	RwLLLink *prev;
};

// RwLinkList
struct RwLinkList
{
	RwLLLink link;
};

// RwFreeList
struct RwFreeList
{
	unsigned int   entrySize;
	unsigned int   entriesPerBlock;
	unsigned int   heapSize;
	unsigned int   alignment;
	RwLinkList     blockList;
	unsigned int   flags;
	RwLLLink       link;
};

typedef int(*RwStandardFunc)(void *pOut, void *pInOut, int nI);

typedef void       *(*RwMemoryAllocFn)    (RwFreeList * fl, unsigned int hint);
typedef RwFreeList *(*RwMemoryFreeFn)     (RwFreeList * fl, void *pData);

/**
 * \ingroup memoryfileinterface
 * \struct RwMemoryFunctions
 * This type represents the memory functions used
 * by RenderWare. By default, the standard ANSI functions are used. The
 * application may install an alternative interface providing that it is ANSI
 * compliant (in RenderWare Graphics see API function RwEngineInit):
 */
struct RwMemoryFunctions
{
	/* c.f.
	 * Program Files/Microsoft Visual Studio/VC98/Include/MALLOC.H
	 */
	void *(*rwmalloc)(size_t size);                   /**< rwmalloc   malloc */
	void(*rwfree)(void *mem);                       /**< rwfree     free */
	void *(*rwrealloc)(void *mem, size_t newSize);    /**< rwrealloc  realloc */
	void *(*rwcalloc)(size_t numObj, size_t sizeObj); /**< calloc     calloc */
};

// RwDevice
struct RwDevice
{
	RwReal gammaCorrection;
	void* fpSystem;
	RwReal zBufferNear;
	RwReal zBufferFar;
	void* fpRenderStateSet;
	void* fpRenderStateGet;
	void* fpIm2DRenderLine;
	void* fpIm2DRenderTriangle;
	void* fpIm2DRenderPrimitive;
	void* fpIm2DRenderIndexedPrimitive;
	void* fpIm3DRenderLine;
	void* fpIm3DRenderTriangle;
	void* fpIm3DRenderPrimitive;
	void* fpIm3DRenderIndexedPrimitive;
};


// RwGlobals
#define MAKE_RwGlobals(structName, macro) \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, void*>), curCamera); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, void*>), curWorld); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt16>), renderFrame); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt16>), lightFrame); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt16[]>), pad); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwDevice>), dOpenDevice); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwStandardFunc[]>), stdFunc); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwLinkList>), dirtyFrameList); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, void*[]>), fileFuncs); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, void*[]>), stringFuncs); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwMemoryFunctions>), memoryFuncs); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwMemoryAllocFn>), memoryAlloc); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwMemoryFreeFn>), memoryFree); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, int>), engineStatus); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, void*>), metrics); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, RwUInt32>), resArenaInitSize); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tDynamicStructEnd>), endOfStructure);

struct RwGlobals : public CDynamicStructure
{
	MAKE_RwGlobals(RwGlobals, STRUCTURE_STATIC_MEMBER_DECLARATION);
};

/**
 * \ingroup rwerror
 * \struct RwError
 * This type represents a RenderWare error specified by the
 * ID of the plugin that the error was issued from (pluginID) and the error
 * code itself (errorCode) (see API function \ref RwErrorGet).
 * \param pluginID The ID of the plugin that issued the error.
 * \param errorCode A value representing the error code.
 */
struct RwError
{
	RwInt32     pluginID;  /**< Internal Use */
	RwInt32     errorCode; /**< Internal Use */
};

#define RWECODE(a,b) a,

extern RwInt32 (*_rwerror)(RwInt32 code, ...);
void RwErrorSet(RwError* pError);

extern RwGlobals** RwEngineInstance;

class Renderware_VarInitialisation : public CLimitAdjusterModule
{
public:
	// Initialize
	void Initialise();

	// Shutdown
	void Shutdown() {}
};

extern Renderware_VarInitialisation g_Renderware_varInitialisation;
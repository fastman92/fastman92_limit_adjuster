/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assertions.h>

#include "../Core/CLimitAdjusterModule.h"

#include "../GameStructures/Rockstar Games/CPool.h"
#include "../GameStructures/Rockstar Games/CSphere.h"
#include "../GameStructures/Rockstar Games/CVehicle.h"

#include "FileIDlimit.h"
#include <MultiPlatformSupport/PlatformGeneralisation.h>
#include <stdint.h>

class CBuilding_generic {};
class CDummy_generic {};

class DynamicLimits : public CLimitAdjusterModule
{
public:
	static const tLimitDefinitionNonStatic ms_listOfDynamicLimits[];
	static const int ms_numberOfLimits;

	// Number of vehicle structs limit
	unsigned int ms_VehicleStructsLimit;

	// Number of collision models	 
	unsigned int ms_ColModelsLimit;

	// Number of matrices
	unsigned int ms_RwObjectInstancesLimit;

	// Number of matrices
	unsigned int ms_MatricesLimit;

	// Number of PtrNode Singles
	unsigned int ms_PtrNodeSinglesLimit;

	// Number of PtrNode Doubles;
	unsigned int ms_PtrNodeDoublesLimit;

	// Number of PtrNode
	unsigned int ms_PtrNodesLimit;

	// Number of EntryInfoNodes
	unsigned int ms_EntryInfoNodesLimit;

	// Number of Peds
	unsigned int ms_PedsLimit;

	// Number of vehicles
	unsigned int ms_VehiclesLimit;

	// Number of objects
	unsigned int ms_ObjectsLimit;

	// Number of tasks
	unsigned int ms_TasksLimit;

	// Number of events
	unsigned int ms_EventsLimit;

	// Number of PointRoute
	unsigned int ms_PointRouteLimit;

	// Number of PatrolRoute
	unsigned int ms_PatrolRouteLimit;

	// Number of NodeRoute
	unsigned int ms_NodeRouteLimit;

	// Number of TaskAllocator
	unsigned int ms_TaskAllocatorLimit;

	// Number of PedIntelligence
	unsigned int ms_PedIntelligenceLimit;

	// Number of PedAttractors
	unsigned int ms_PedAttractorsLimit;

	// Number of QuadTreeNodes
	unsigned int ms_QuadTreeNodesLimit;

	// Number of collision links
	unsigned int ms_CollisionLinksLimit;

	// Limit of CustomEnvMapPipeMatDataPool
	unsigned int ms_CustomEnvMapPipeMatDataPoolLimit;

	// Limit of CustomEnvMapPipeAtmDataPool
	unsigned int ms_CustomEnvMapPipeAtmDataPoolLimit;

	// Limit of CustomSpecMapPipeMaterialDataPool
	unsigned int ms_CustomSpecMapPipeMaterialDataPoolLimit;

	// Number of InteriorInst
	unsigned int ms_InteriorInstLimit;

	// Number of PortalInst
	unsigned int ms_PortalInstLimit;

	// Number of CAnimBlender
	unsigned int ms_CAnimBlenderLimit;

	// Number of CAtdNodeAnimChangePooledObject
	unsigned int ms_CAtdNodeAnimChangePooledObjectLimit;

	// Number of CAtdNodeAnimPlayer
	unsigned int ms_CAtdNodeAnimPlayerLimit;

	// Number of crFrameFilterBoneMask
	unsigned int ms_crFrameFilterBoneMaskLimit;

	// Number of crFrameFilterBoneAnalogue
	unsigned int ms_crFrameFilterBoneAnalogueLimit;

	// Number of crExpressionProcessor
	unsigned int ms_crExpressionProcessorLimit;

	// Number of crmtObserver
	unsigned int ms_crmtObserverLimit;

	// Number of CDummyTask
	unsigned int ms_CDummyTaskLimit;

	// Number of NavMeshRoute
	unsigned int ms_NavMeshRouteLimit;

	// Number of Cam
	unsigned int ms_CamLimit;

	// Number of ExplosionType
	unsigned int ms_ExplosionTypeLimit;

	// Number of reach driver pool
	unsigned int ms_ReachDriverLimit;

	// Number of prop anim pool
	unsigned int ms_PropAnimLimit;

	// Buildings pool
	union {
		CPool_GTASA<CBuilding_generic>** gta_sa;
	} CPools__ms_pBuildingPool;

	// Dummy pool
	union {
		CPool_GTASA<CDummy_generic>** gta_sa;
	} CPools__ms_pDummyPool;

	// COL model pool
	union
	{
		#ifdef IS_ARCHITECTURE_32_BIT
		CPool_GTASA<Game_GTASA::CColModel>** gtasa;
		#endif
	} CPools__ms_pColModelPool;
	
	// Vehicles pool
	union
	{
	#ifdef IS_ARCHITECTURE_32_BIT
		CPool_GTASA<Game_GTASA::CVehicle>** gtasa;
	#endif
	} CPools__ms_pVehiclePool;

	size_t sizeof_CVehicle;
	size_t sizeof_CPed;

	// Replay pool conversions
	struct {
		int32_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CReplay__m_PedPoolConversion;

	struct {
		int32_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CReplay__m_VehiclePoolConversion;

	// Vehicle structs
	void SetVehicleStructs(unsigned int iVehicleStructs);

	// PtrNode Singles
	void SetPtrNodeSingles(unsigned int iPtrNodeSingles);

	// PtrNode Doubles
	void SetPtrNodeDoubles(unsigned int iPtrNodeDoubles);

	// PtrNodes
	void SetPtrNodes(unsigned int iPtrNodes);

	// EntryInfoNodes
	void SetEntryInfoNodes(unsigned int iEntryInfoNodes);

	// Peds
	void SetPeds(unsigned int iPeds);

	// Vehicles
	void SetVehicles(unsigned int iVehicles);

	// Objects
	void SetObjects(unsigned int iObjects);

	// Tasks
	void SetTasks(unsigned int iTasks);

	// CDummyTask
	void SetCDummyTask(unsigned int iCDummyTask);

	// Events
	void SetEvents(unsigned int iEvents);

	// PedIntelligence
	void SetPedIntelligence(unsigned int iPedInteligence);

	// Sets PointRoute
	void SetPointRoute(unsigned int iPointRoute);

	// Sets PatrolRoute
	void SetPatrolRoute(unsigned int iPatrolRoute);

	// Sets NodeRoute
	void SetNodeRoute(unsigned int iNodeRoute);

	// Sets TaskAllocator
	void SetTaskAllocator(unsigned int iTaskAllocator);

	// Sets PedAttractors
	void SetPedAttractors(unsigned int iPedAttractors);

	// QuadTreeNodes
	void SetQuadTreeNodes(unsigned int iQuadTreeNodes);

	// Collision links
	void SetCollisionLinks(unsigned int iCollisionLinks);

	// Collision models
	void SetColModels(unsigned int iColModels);

	// Sets the CustomEnvMapPipeMatDataPool limit
	void SetCustomEnvMapPipeMatDataPool(unsigned int iLimitValue);

	// Sets the CustomEnvMapPipeAtmDataPool limit
	void SetCustomEnvMapPipeAtmDataPool(unsigned int iLimitValue);

	// Sets the CustomSpecMapPipeMaterialDataPool limit
	void SetCustomSpecMapPipeMaterialDataPool(unsigned int iLimitValue);

	// rwObjectInstances
	void SetRwObjectInstances(unsigned int iRwObjectInstances);

	// Matrices
	void SetMatrices(unsigned int iMatrices);

	// InteriorInst
	void SetInteriorInst(unsigned int iInteriorInst);

	// PortalInst
	void SetPortalInst(unsigned int iPortalInst);

	// CAnimBlender
	void SetCAnimBlender(unsigned int iCAnimBlender);

	// CAtdNodeAnimChangePooledObject
	void SetCAtdNodeAnimChangePooledObject(unsigned int iCAtdNodeAnimChangePooledObject);

	// CAtdNodeAnimPlayer
	void SetCAtdNodeAnimPlayer(unsigned int iCAtdNodeAnimPlayer);

	// crFrameFilterBoneMask
	void SetcrFrameFilterBoneMask(unsigned int icrFrameFilterBoneMask);

	// crFrameFilterBoneAnalogue
	void SetcrFrameFilterBoneAnalogue(unsigned int icrFrameFilterBoneAnalogue);

	// crExpressionProcessor
	void SetcrExpressionProcessor(unsigned int icrExpressionProcessor);

	// crmtObserver
	void SetcrmtObserver(unsigned int icrmtObserver);

	// NavMeshRoute
	void SetNavMeshRoute(unsigned int iNavMeshRoute);
	
	// Cam
	void SetCam(unsigned int iCam);

	// ExplosionType
	void SetExplosionType(unsigned int iExplosionType);

	// Reach driver
	void SetReachDriver(unsigned int iReachDriver);

	// Prop anim
	void SetPropAnim(unsigned int iPropAnim);
	
	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();

	// Applies enabled limits
	void ApplyEnabledLimits();
};

extern DynamicLimits g_dynamicLimits;
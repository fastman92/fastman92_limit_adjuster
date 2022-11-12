/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../Core/CLimitAdjusterModule.h"
#include "../Core/eGameVersion.h"
#include "../Core/ProjectConstants.h"

#include "../GameStructures/Rockstar Games/CPtrNodeDoubleLink.h"
#include "../GameStructures/Rockstar Games/CPtrNodeSingleLink.h"
#include "../GameStructures/Rockstar Games/RwStream.h"

#include <CompressedVector.h>
#include <EnumOperators.h>
#include <PathStructures.h>
#include <DynamicTypes/DynamicStructure.h>

#include <string>
#include <vector>

class CTrackFilenameLoader
{
public:
	std::vector<std::string> m_vecTrackFilenames;
	
	// Loads data
	void Load(const char* filename);
};

// Track filename loader
extern CTrackFilenameLoader TrackFilenameLoader;

// Bully Scholarship Edition
namespace Game_BullyScholarschipEdition
{
	struct CSector
	{
		CPtrNodeSingleLink *buildingList;
		CPtrNodeSingleLink *objectList;
		CPtrNodeSingleLink *vehicleList;
		CPtrNodeSingleLink *pedList;
		CPtrNodeSingleLink *dummyList;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CSector, 0x14);
}

// GTA San Andreas
namespace Game_GTASA
{
	struct CSector
	{
		Game_GTA::CPtrNodeSingleLink *buildingList;
		Game_GTA::CPtrNodeSingleLink *dummyList;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CSector, 8);
	
	struct CRepeatSector
	{
		CPtrNodeDoubleLink *vehicleList;
		CPtrNodeDoubleLink *pedList;
		CPtrNodeDoubleLink *objectList;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CRepeatSector, 0xC);

	struct CTrainNode
	{
		CompressedVector Pos;
		uint16_t RailDistance;
		char field_8;
		char field_9;
	};

	VALIDATE_SIZE(CTrainNode, 0xA);

#define CTRAIN_NODE_USE_EXPOS

	struct CTrainNodeExtended : public CTrainNode
	{
		CompressedVector_extended exPos;
	};

	typedef CPathNode_fastman92_version_4 CPathNode_extended_latest;
	typedef CCarPathLink_fastman92_version_4 CCarPathLink_extended_latest;
	
	namespace details
	{
		template <
			class structName, class standardType, class extendedType
		>
			union UpathExtensionArray
		{
			CDynamicStructMember < structName, standardType > standard;
			CDynamicStructMember < structName, extendedType > extended;

			// Returns offset
			uint32_t GetOffset() const
			{
				return extended.GetOffset();
			}
		};
	}

#if PROJECT_IS_UNRELEASED_EDITION

// enable debugging functionality by standard data?
// #define ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA

#endif


#ifdef ADD_DEBUGGING_FUNCTIONALITY_BY_STANDARD_DATA
	#define MAKE_GTA_SA_CPATH_FIND_STANDARD_DATA_PART(structName, macro) \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, CPathNode*[]>), m_pPathNodesStandard); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, CCarPathLink*[]>), m_pNaviNodesStandard);
#else
	#define MAKE_GTA_SA_CPATH_FIND_STANDARD_DATA_PART(structName, macro)
#endif


#define MAKE_GTA_SA_CPATH_FIND(structName, macro) \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, CNodeAddress>), m_info); \
	macro(structName, SINGLE_ARG(details::UpathExtensionArray<structName, CPathNode*[], CPathNode_extended_latest*[]>), m_apNodesSearchLists); \
	macro(structName, SINGLE_ARG(details::UpathExtensionArray<structName, CPathNode*[], CPathNode_extended_latest*[]>), m_pPathNodes); \
	macro(structName, SINGLE_ARG(details::UpathExtensionArray<structName, CCarPathLink*[], CCarPathLink_extended_latest*[]>), m_pNaviNodes); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, CNodeAddress*[]>), m_pNodeLinks); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint8_t*[]>), m_pLinkLengths); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, CPathIntersectionInfo* []>), m_pPathIntersections); \
	macro(structName, SINGLE_ARG(details::UpathExtensionArray<structName, CLinkAddress *[], CLinkAddress_extended *[]>), m_pNaviLinks); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, void*[]>), m_field_EA4); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t[]>), m_dwNumNodes); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t[]>), m_dwNumVehicleNodes); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t[]>), m_dwNumPedNodes); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t[]>), m_dwNumCarPathLinks); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, uint32_t[]>), m_dwNumAddresses); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, int[]>), m_field_1544); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, unsigned int>), m_dwTotalNumNodesInSearchList); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, unsigned int[]>), m_interiorAreaIDarray); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, unsigned int>), m_dwNumForbiddenAreas); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, CForbiddenArea[]>), m_aForbiddenAreas); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, bool>), m_bForbiddenForScriptedCarsEnabled); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, float>), m_fForbiddenForScrCarsX1); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, float>), m_fForbiddenForScrCarsX2); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, float>), m_fForbiddenForScrCarsY1); \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, float>), m_fForbiddenForScrCarsY2); \
	MAKE_GTA_SA_CPATH_FIND_STANDARD_DATA_PART(structName, macro) \
	macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tDynamicStructEnd>), endOfStructure);

	// path stuff
	// CPathFind
	class CPathFind : public CDynamicStructure
	{
	public:
		MAKE_GTA_SA_CPATH_FIND(CPathFind, STRUCTURE_STATIC_MEMBER_DECLARATION);
	};

	// New CPathFind
	class CPathFind_extended : public CPathFind
	{
	public:
		//////////////////////////////////

		// Initializes a structure
		void Init();

		// Shutdown
		void Shutdown();

		// Loads path file.
		void __thiscall LoadPathFindData(RwStream *stream, int index);

		#if 0
		// Loads path file.
		void __thiscall LoadPathFindDataDebug(RwStream *stream, int index);
		#endif

		// Unloads path file
		void __thiscall UnLoadPathFindData(int index);

		// Loads scene for path nodes
		void LoadSceneForPathNodes(CVector pos);

		// Marks region for coordinates
		void MarkRegionsForCoors(CVector pos, float radius);

		// Returns interior node index
		CNodeAddress ReturnInteriorNodeIndex(unsigned int InteriorID, int nodeIndex);

		// Checks grid
		void CheckGrid();

		// Switches roads off in area for one region.
		void __thiscall SwitchRoadsOffInAreaForOneRegion(
			float x1, float x2,
			float y1, float y2,
			float z1, float z2,
			bool bEnable,
			char type,
			int index,
			char a11
		);

		// Post process path node
		void PostProcessPathNode(CPathNode_extended_latest* node, ePathType pathType);

		// Post process navi node
		void PostProcessNaviNode(CCarPathLink_extended_latest* pathLink);

		//////////////////////
	};
}

// GTA IV
namespace Game_GTAIV
{
	struct CSector
	{
		Game_GTA::CPtrNodeSingleLink * buildingList;
		Game_GTA::CPtrNodeSingleLink * dummyList;
		int16_t lowestID;
		int16_t highestID;
	};

	struct CRepeatSector
	{
		CPtrNodeDoubleLink* vehicleList;
		CPtrNodeDoubleLink* pedList;
		CPtrNodeDoubleLink* objectList;
		CPtrNodeDoubleLink* portalInstList;
		CPtrNodeDoubleLink* interiorInstList;
	};

	enum eClass_1136170_offset
	{
		Offset_class_1136170__field_0,
		Offset_class_1136170__field_4,
		Offset_class_1136170__field_8,
		Offset_class_1136170__field_E108,
		Offset_class_1136170__field_E2E8,
		Offset_class_1136170__field_E4C8,
		Offset_class_1136170__field_E4CC,
		Offset_class_1136170__field_E4D0,
		Offset_class_1136170__field_E4D4,
		Offset_class_1136170__endOfStructure,

		Offset_class_1136170__enumCount,
		Offset_class_1136170__firstEnumMember = Offset_class_1136170__field_0
	};

	DEFINE_ENUM_OPERATORS(eClass_1136170_offset);

	class CClass_1136170
	{
	public:
		static uint32_t MemberOffsetArray[Offset_class_1136170__enumCount];

		// Returns pointer to member
		void* GetPointerToMember(eClass_1136170_offset member)
		{
			return (void*)((char*)(this) + this->MemberOffsetArray[member]);
		}

		//////////////////////
	};
}

// GTA V
namespace Game_GTAV
{

}

class MapLimits : public CLimitAdjusterModule
{
private:
#ifdef IS_PLATFORM_WIN_X86
	// Patches radar size
	void PatchRadarSize_GTA_SA_PC_1_0();

	// Patches radar size
	void PatchRadarSize_GTA_IV_or_EFLC();
#endif

	// Patches radar size
	void PatchRadarSize();

#ifdef IS_PLATFORM_WIN_X86
	// Patch frontend map to be different
	void PatchFrontendMapDifferent_GTA_SA_PC_1_0();
#endif

	// Patch frontend map to be different
	void PatchFrontendMapDifferent();

#ifdef IS_PLATFORM_WIN_X86
	// Patches radar textures pointers
	void PatchReferencesToRadarTextures_GTA_SA_PC_1_0();
#endif

	// Patches radar textures pointers
	void PatchReferencesToRadarTextures();

	// Do initializing work for water map size patching
	bool PatchWaterMapSize_DoInitialisingWork();

	#ifdef IS_PLATFORM_WIN_X86
	// Patches water map size
	void PatchWaterMapSize_GTA_SA_PC_1_0_HOODLUM();

	// Patches water map size
	void PatchWaterMapSize_GTA_IV_1_0_7_0();
	#endif

	#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
	// Patches water map size
	void PatchWaterMapSize_GTA_SA_2_0_ANDROID_ARM32();
	#endif

	// Patches water map size
	void PatchWaterMapSize();

	// Does the initialising work for patching the world sectors
	bool PatchWorldSectors_DoInitialisingWork();

	#ifdef IS_PLATFORM_WIN_X86
	// Patches world sectors
	void PatchWorldSectors_GTA_SA_PC_1_0_HOODLUM();

	// Patches world sectors
	void PatchWorldSectors_GTA_IV_1_0_7_0();
	#endif

	#ifdef IS_PLATFORM_ANDROID_ARM32
	// Patches world sectors
	void PatchWorldSectors_GTA_SA_2_0_ANDROID_ARM32();
	#endif

	// Patches world sectors
	void PatchWorldSectors_GTA_SA();

	// Patches world sectors
	void PatchWorldSectors();

	// Patches Renderware world map size limit
	void PatchRwWorldMapSize();
	
	// Allocates CPathFind
	void AllocateCPathFind(
		unsigned int iTotalNumberOfPathFiles,
		unsigned int iNumberOfPathInteriorSlots,
		unsigned int CPathFind_field_1544_numberOfElementsPerPathFile
	);

	// Does the initialising work for patching the paths map size
	bool PatchPaths_DoInitialisingWork();

	#ifdef IS_PLATFORM_WIN_X86
	// Patches paths
	void PatchPaths_GTA_SA_PC_1_0_HOODLUM();
	#endif

	#ifdef IS_PLATFORM_ANDROID_ARM32
	// Patches paths
	void PatchPaths_GTA_SA_2_0_ANDROID_ARM32();
	#endif

	// Patches paths
	void PatchPaths();

	// Applies path debugging
	void ApplyPathDebugging();

	// Patches tracks.dat coordinate limit
	void PatchTracksDatCoordinateLimit();

	// Patches tracks.dat file size limit
	void PatchTracksDatFileSizeLimit();

	// Patches max number of track stations
	void PatchMaxNumberOfTrackStations();

	// Patches number of tracks.dat files
	void PatchNumberOfTracksDatFiles();

	// Makes a traffic left-sided
	void PatchLeftSidedTraffic();

	// Radar texture array reallocated?
	bool ms_bRadarTextureArrayReallocated;

public:
	// Is path debugging enabled
	bool ms_bPathDebuggingEnabled;

	// Is tracks.dat coordinate patch enabled
	bool ms_bTracksDatCoordinateLimitPatchEnabled;

	// Is tracks.dat file size limit set
	bool ms_bTracksDatFileSizeLimitSet;

	// Is max number of track stations limit set
	bool ms_bMaxNumberOfTrainStationsLimitSet;

	// Is number of tracks.dat files set
	bool ms_bNumberOfTracksDatFilesSet;

	// Is paths patch enabled
	bool ms_bPathsPatchEnabled;

	// Is frontend map different
	bool ms_bIsFrontentMapDifferent;

	// Has radar limit been set
	bool ms_bRadarLimitSet;

	// Has water limit been set
	bool ms_bWaterLimitSet;

	// Has world sector limit been set
	bool ms_bWorldSectorLimitSet;

	// Has world map size limit been set?
	bool ms_bRwWorldMapSizeLimitSet;

	// Tracks.dat file size limit
	unsigned int ms_tracksDatFileSizeLimit;

	// Tracks.dat stations
	unsigned int ms_MaxNumberOfTrackStations;

	// Number of tracks.dat files
	unsigned int ms_NumberOfTracksDatFiles;

	// Paths map size
	unsigned int ms_pathsMapSize;

	// Renderware world map size
	unsigned int ms_rwWorldMapSize;

	// Radar map size
	unsigned int ms_radarMapSize;

	// Water map size
	unsigned int ms_waterMapSize;

	// Map bound limit
	unsigned int ms_worldMapSize;

	// World sector size
	unsigned int ms_worldSectorSize;
		
	// World LOD sector size
	unsigned int ms_worldLODsectorSize;

	// Path block size
	unsigned int ms_pathBlockSize;

	// Number of path indices
	unsigned int iTotalNumberOfPathIndices;

	// Number of path interior slots
	unsigned int iNumberOfPathInteriorSlots;

	// Number of path indices including interior
	unsigned int iTotalNumberOfPathIndicesIncludingInterior;

	// Radar block size
	static const unsigned int ms_radarBlockSize = 500;

	// Water block size
	unsigned int ms_waterBlockSize;
		
	// Zone revealed block size
	static const unsigned int ms_zoneRevealedBlockSize = 600;

	////////////////////////////////////////////////

	// Water quads and triangles in each block
	struct {
		int16_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CWaterLevel__m_QuadsAndTrianglesInEachBlock;

	// World sector array
	struct {
		union {
			Game_GTASA::CSector* gta_sa;
			Game_GTAIV::CSector* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} CWorld__ms_aSectors;

	// World sector object count
	struct {
		uint8_t* ptr;
		DEFINE_IS_ALLOCATED();
	} CWorld__ms_aSectorObjectCount;

	// World sector flags
	struct {
		uint16_t* ptr;
		DEFINE_IS_ALLOCATED();
	}CWorld__ms_aSectorFlags;

	// World sector class 0x1136170
	struct {
		union {
			Game_GTAIV::CClass_1136170* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} CWorld__ms_class_1136170;

	// World repeat sector array
	struct {
		union {
			Game_GTASA::CRepeatSector* gta_sa;
			Game_GTAIV::CRepeatSector* gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} CWorld__ms_aRepeatSectors;

	// World LOD sector array
	struct {
		union {
			Game_GTA::CPtrNodeSingleLink** gta_sa;
			void** gta_iv;
		};
		DEFINE_IS_ALLOCATED();
	} CWorld__ms_aLodPtrLists;

	// Path finder
	struct {
		union {
			Game_GTASA::CPathFind_extended* gta_sa;
		};
		DEFINE_IS_ALLOCATED();
	} ThePaths;
	
	struct {
		bool* ptr;
		DEFINE_IS_ALLOCATED();
	} ToBeStreamed;

	struct {
		bool* ptr;
		DEFINE_IS_ALLOCATED();
	} ToBeStreamedForScript;

	struct {
		uint8_t* ptr;
		DEFINE_IS_ALLOCATED();
	} DontWanderGiven;

	struct {
		float* ptr;
		DEFINE_IS_ALLOCATED();
	} XCoorGiven;

	struct {
		float* ptr;
		DEFINE_IS_ALLOCATED();
	} YCoorGiven;

	struct {
		float* ptr;
		DEFINE_IS_ALLOCATED();
	} ZCoorGiven;

	struct {
		uint8_t* ptr;
		DEFINE_IS_ALLOCATED();
	} ConnectsToGiven;
		 
	// Radar texture IDs
	struct {
		int* ptr;
		DEFINE_IS_ALLOCATED();
	} gRadarTextures;

	// Station distances
	struct {
		float* ptr;
		DEFINE_IS_ALLOCATED();
	} StationDist;

	// Station coordinates
	struct {
		CVector* ptr;
		DEFINE_IS_ALLOCATED();
	} CTrain__aStationCoors;

	// pTrackNodes
	struct {
		void** ptr;
		DEFINE_IS_ALLOCATED();
	} pTrackNodes;

	// TrainTrackDistance
	struct {
		float* ptr;
		DEFINE_IS_ALLOCATED();
	} TrainTrackDistance;

	// TrainTrackNodeCount
	struct {
		unsigned int* ptr;
		DEFINE_IS_ALLOCATED();
	} NumTrackNodes;

	// Checks contraints
	void CheckConstraints();

	// Initializes map changes
	void InitChanges();

	// Commits changes
	void CommitChanges();

	// Initialize
	virtual void Initialise();

	// Shutdown
	virtual void Shutdown();

	// Returns true if world map size is increased.
	bool IsWorldMapSizeIncreased();

	// Enables tracks.dat coordinate limit patch
	void EnableTracksDatCoordinateLimitPatch(bool enabled);

	// Returns true if path map size is supported for game version
	static bool IsPathMapSizePatchSupportedForGameVersion(Game::eGameVersion gameVersion);

	// Enables paths limit patch
	void EnablePathsLimitPatch(bool enabled);

	// Enables path debugging
	void EnablePathDebugging(bool enabled);
		
	// Sets tracks.dat file size limit
	void SetTracksDatFileSizeLimit(unsigned int fileSizeLimit);

	// Sets max number of track stations
	void SetMaxNumberOfTrackStations(unsigned int maxNumberOfTrackStations);

	// Enables track config loader
	void EnableTrackConfigLoader(bool enabled);

	// Returns true if paths map size is supported for game version
	static bool IsPathsMapSizePatchSupportedForGameVersion(Game::eGameVersion gameVersion);

	// Sets paths map size, returns true if successful
	void SetPathsMapSize(unsigned int pathsMapSize);

	// Sets Renderware map size
	void SetRenderwareWorldMapSize(unsigned int rwWorldMapSize);

	// Returns true if radar map size is supported for game version
	static bool IsRadarMapSizePatchSupportedForGameVersion(Game::eGameVersion gameVersion);

	// Sets radar map size
	void SetRadarSize(unsigned int radarMapSize);

	// Enables frontent map different
	void EnableFrontendMapDifferent(bool enabled);

	// Returns true if water map size is supported for game version
	static bool IsWaterMapSizePatchSupportedForGameVersion(Game::eGameVersion gameVersion);

	// Sets water map size
	void SetWaterMapSize(unsigned int waterMapSize);

	// Returns true if world map size is supported for game version
	static bool IsWorldMapSizePatchSupportedForGameVersion(Game::eGameVersion gameVersion);

	// Map bound limit
	void SetWorldMapSize(unsigned int worldMapSize);

	// World sector size, affects 
	void SetWorldSectorSize(unsigned int sectorSize);

	// World LOD sector size
	void SetLODSectorSize(unsigned int LODsectorSize);
};

extern MapLimits g_mapLimits;
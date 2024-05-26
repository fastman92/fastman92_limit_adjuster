#if 0
Address_CGame__Process_3F3FB8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3F3FB8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3F3FB0),
(void*)&debugging_CGame__Process_3F3FB0, 8
);
#endif

#if 0
{
	Address_CPathFind__FindNodeClosestToCoors_315D48_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315D48));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x315D40),
	(void*)&debugging_CPathFind__FindNodeClosestToCoors_315D40, 8
	);

	Address_CPathFind__FindNodeClosestInRegion_317488_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317488));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317480),
	(void*)&debugging_CPathFind__FindNodeClosestInRegion_317480, 8
	);

	Address_CPathFind__FindNthNodeClosestToCoors_3176C0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3176C0));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3176B8),
	(void*)&debugging_CPathFind__FindNthNodeClosestToCoors_3176B8, 8
	);

	Address_CPathFind__Find2NodesForCarCreation_317804_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317804));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3177FC),
	(void*)&debugging_CPathFind__Find2NodesForCarCreation_3177FC, 8
	);

	Address_CPathFind__RecordNodesClosestToCoors_317B58_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317B58));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317B50),
	(void*)&debugging_CPathFind__RecordNodesClosestToCoors_317B50, 8
	);

	Address_CPathFind__CalcDistToAnyConnectingLinks_31735C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31735C));
	CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317354),
	(void*)&debugging_CPathFind__CalcDistToAnyConnectingLinks_317354, 8
	);
}


Address_CPathFind__Init_315252 = g_mCalc.GetCurrentVAbyPreferedVA(0x315252);
Address_CPathFind__Init_315254_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315254));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31524C),
(void*)&debugging_CPathFind__Init_31524C, 8
);

Address_CPathFind__LoadPathFindData_3152E8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3152E8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3152E0),
(void*)&debugging_CPathFind__LoadPathFindData_3152E0, 8
);

Address_CPathFind__LoadPathFindData_315350_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315350));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x315348),
(void*)&debugging_CPathFind__LoadPathFindData_315348, 8
);

Address_CPathFind__UnLoadPathFindData_31570C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31570C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x315704),
(void*)&debugging_CPathFind__UnLoadPathFindData_315704, 8
);

Address_CPathFind__ComputeRoute_315794_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315794));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31578C),
(void*)&debugging_CPathFind__ComputeRoute_31578C, 8
);

Address_CPathFind__DoPathSearch_315850_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x315850));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x315848),
(void*)&debugging_CPathFind__DoPathSearch_315848, 8
);

Address_CPathFind__AddNodeToList_3161E8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3161E8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3161DE),
(void*)&debugging_CPathFind__AddNodeToList_3161DE, 10
);

Address_CPathFind__RemoveNodeFromList_31621C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31621C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x316214),
(void*)&debugging_CPathFind__RemoveNodeFromList_316214, 8
);

Address_CPathFind__RemoveBadStartNode_316238_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x316238));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x316230),
(void*)&debugging_CPathFind__RemoveBadStartNode_316230, 8
);

Address_CPathFind__CountFloodFillGroups_316300_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x316300));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3162F8),
(void*)&debugging_CPathFind__CountFloodFillGroups_3162F8, 8
);

Address_CPathFind__FindNextNodeWandering_3164BC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3164BC));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3164B4),
(void*)&debugging_CPathFind__FindNextNodeWandering_3164B4, 8
);

Address_CPathFind__GeneratePedCreationCoors_316888_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x316888));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x316880),
(void*)&debugging_CPathFind__GeneratePedCreationCoors_316880, 8
);

Address_CPathFind__GeneratePedCreationCoors_Interior_316E78_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x316E78));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x316E70),
(void*)&debugging_CPathFind__GeneratePedCreationCoors_Interior_316E70, 8
);

Address_CPathFind__TestCoorsCloseness_317138_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317138));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317130),
(void*)&debugging_CPathFind__TestCoorsCloseness_317130, 8
);


Address_CPathFind__CalcRoadDensity_3171C4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3171C4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3171BC),
(void*)&debugging_CPathFind__CalcRoadDensity_3171BC, 8
);

Address_CPathFind__FindXCoorsForRegion_317670_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317670));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317668),
(void*)&debugging_CPathFind__FindXCoorsForRegion_317668, 8
);

Address_CPathFind__FindYCoorsForRegion_317698_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317698));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317690),
(void*)&debugging_CPathFind__FindYCoorsForRegion_317690, 8
);

Address_CPathFind__These2NodesAreAdjacent_317C84_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317C84));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317C7C),
(void*)&debugging_CPathFind__These2NodesAreAdjacent_317C7C, 8
);

Address_CPathFind__RecordNodesInCircle_317D00_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317D00));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317CF8),
(void*)&debugging_CPathFind__RecordNodesInCircle_317CF8, 8
);

Address_CPathFind__FindNodeClosestToCoorsFavourDirection_317E3C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317E3C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317E34),
(void*)&debugging_CPathFind__FindNodeClosestToCoorsFavourDirection_317E34, 8
);

Address_CPathFind__FindNodePairClosestToCoors_317FB8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x317FB8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x317FB0),
(void*)&debugging_CPathFind__FindNodePairClosestToCoors_317FB0, 8
);

Address_CPathFind__FindNodeOrientationForCarPlacement_3182AC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3182AC));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3182A4),
(void*)&debugging_CPathFind__FindNodeOrientationForCarPlacement_3182A4, 8
);

Address_CPathFind__ThisNodeWillLeadIntoADeadEnd_318428_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x318428));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x318420),
(void*)&debugging_CPathFind__ThisNodeWillLeadIntoADeadEnd_318420, 8
);

Address_CPathFind__SwitchRoadsOffInArea_3184C4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3184C4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3184BC),
(void*)&debugging_CPathFind__SwitchRoadsOffInArea_3184BC, 8
);

Address_CPathFind__SwitchPedRoadsOffInArea_3186A4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3186A4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31869A),
(void*)&debugging_CPathFind__SwitchPedRoadsOffInArea_31869A, 10
);

Address_CPathFind__ThisNodeHasToBeSwitchedOff_3186DA_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3186DA));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3186CE),
(void*)&debugging_CPathFind__ThisNodeHasToBeSwitchedOff_3186CE, 12
);

Address_CPathFind__TestForPedTrafficLight_3189E4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3189E4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3189DA),
(void*)&debugging_CPathFind__TestForPedTrafficLight_3189DA, 10
);

Address_CPathFind__TestCrossesRoad_318C48_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x318C48));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x318C40),
(void*)&debugging_CPathFind__TestCrossesRoad_318C40, 8
);


Address_CPathFind__FindStartPointOfRegion_318CD0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x318CD0));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x318CC8),
(void*)&debugging_CPathFind__FindStartPointOfRegion_318CC8, 8
);

Address_CPathFind__SetLinksBridgeLights_318D0C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x318D0C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x318D04),
(void*)&debugging_CPathFind__SetLinksBridgeLights_318D04, 8
);

Address_CPathFind__FindNodeCoorsForScript_318DCC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x318DCC));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x318DC4),
(void*)&debugging_CPathFind__FindNodeCoorsForScript_318DC4, 8
);

Address_CPathFind__FindNodeCoorsForScript_318FA0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x318FA0));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x318F98),
(void*)&debugging_CPathFind__FindNodeCoorsForScript_318F98, 8
);

Address_CPathFind__TakeWidthIntoAccountForWandering_3192A0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3192A0));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x319298),
(void*)&debugging_CPathFind__TakeWidthIntoAccountForWandering_319298, 8
);

Address_CPathFind__TakeWidthIntoAccountForCoors_319368_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319368));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x319360),
(void*)&debugging_CPathFind__TakeWidthIntoAccountForCoors_319360, 8
);

Address_CPathFind__MarkRegionsForCoors_319478_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319478));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x319470),
(void*)&debugging_CPathFind__MarkRegionsForCoors_319470, 8
);

Address_CPathFind__SetPathsNeededAtPosition_319588_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319588));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x319580),
(void*)&debugging_CPathFind__SetPathsNeededAtPosition_319580, 8
);

Address_CPathFind__UpdateStreaming_3195AC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3195AC));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3195A4),
(void*)&debugging_CPathFind__UpdateStreaming_3195A4, 8
);

Address_CPathFind__HaveRequestedNodesBeenLoaded_319C20_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319C20));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x319C18),
(void*)&debugging_CPathFind__HaveRequestedNodesBeenLoaded_319C18, 8
);

Address_CPathFind__AreNodesLoadedForArea_319D40_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x319D40));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x319D38),
(void*)&debugging_CPathFind__AreNodesLoadedForArea_319D38, 8
);

Address_CPathFind__StartNewInterior_31A11C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31A11C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31A114),
(void*)&debugging_CPathFind__StartNewInterior_31A114, 8
);

Address_CPathFind__AddNodeToNewInterior_31A180_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31A180));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31A178),
(void*)&debugging_CPathFind__AddNodeToNewInterior_31A178, 8
);

Address_CPathFind__AddInteriorLink_31A236_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31A236));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31A22C),
(void*)&debugging_CPathFind__AddInteriorLink_31A22C, 10
);

Address_CPathFind__AddInteriorLinkToExternalNode_31A2A4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31A2A4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31A29C),
(void*)&debugging_CPathFind__AddInteriorLinkToExternalNode_31A29C, 8
);

Address_CPathFind__RemoveInteriorLinks_31A2DE = g_mCalc.GetCurrentVAbyPreferedVA(0x31A2DE);
Address_CPathFind__RemoveInteriorLinks_31A2DC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31A2DC));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31A2D4),
(void*)&debugging_CPathFind__RemoveInteriorLinks_31A2D4, 8
);

Address_CPathFind__FindNearestExteriorNodeToInteriorNode_31A380_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31A380));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31A378),
(void*)&debugging_CPathFind__FindNearestExteriorNodeToInteriorNode_31A378, 8
);

Address_CPathFind__CompleteNewInterior_31A614_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31A614));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31A60C),
(void*)&debugging_CPathFind__CompleteNewInterior_31A60C, 8
);

Address_CPathFind__AddDynamicLinkBetween2Nodes_31ACEC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31ACEC));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31ACE4),
(void*)&debugging_CPathFind__AddDynamicLinkBetween2Nodes_31ACE4, 8
);

Address_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AD10_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31AD10));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31AD06),
(void*)&debugging_CPathFind__AddDynamicLinkBetween2Nodes_For1Node_31AD06, 10
);

Address_CPathFind__RemoveInterior_31AF5C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31AF5C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31AF54),
(void*)&debugging_CPathFind__RemoveInterior_31AF54, 8
);

Address_CPathFind__FindLinkBetweenNodes_31B3C4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31B3C4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31B3BC),
(void*)&debugging_CPathFind__FindLinkBetweenNodes_31B3BC, 8
);

Address_CPathFind__FindParkingNodeInArea_31B444_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31B444));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31B43C),
(void*)&debugging_CPathFind__FindParkingNodeInArea_31B43C, 8
);

Address_CPathFind__Save_48CEDC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x48CEDC));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x48CED4),
(void*)&debugging_CPathFind__Save_48CED4, 8
);

Address_CPathFind__Load_48CF58_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x48CF58));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x48CF50),
(void*)&debugging_CPathFind__Load_48CF50, 8
);

Address_CStreaming__RemoveModel_2D00C0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2D00C0));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2D00B8),
(void*)&debugging_CStreaming__RemoveModel_2D00B8, 8
);

Address_CStreaming__Update_2D04F0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2D04F0));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2D04E8),
(void*)&debugging_CStreaming__Update_2D04E8, 8
);

Address_CStreaming__ConvertBufferToObject_2D2F68_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2D2F68));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2D2F60),
(void*)&debugging_CStreaming__ConvertBufferToObject_2D2F60, 8
);

Address_CStreaming__LoadScene_2D4998_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2D4998));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2D4990),
(void*)&debugging_CStreaming__LoadScene_2D4990, 8
);

Address_CAutoPilot__ModifySpeed_2E350C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2E350C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2E3504),
(void*)&debugging_CAutoPilot__ModifySpeed_2E3504, 8
);

Address_CCarCtrl__GenerateCarCreationCoors2_2E7768_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2E7768));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2E7760),
(void*)&debugging_CCarCtrl__GenerateCarCreationCoors2_2E7760, 8
);

Address_CCarCtrl__GenerateOneRandomCar_2E8424_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2E8424));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2E841C),
(void*)&debugging_CCarCtrl__GenerateOneRandomCar_2E841C, 8
);

Address_CCarCtrl__PickNextNodeRandomly_2EA6EC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2EA6EC));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2EA6E4),
(void*)&debugging_CCarCtrl__PickNextNodeRandomly_2EA6E4, 8
);

Address_CCarCtrl__CreatePoliceChase_2EB43C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2EB43C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2EB434),
(void*)&debugging_CCarCtrl__CreatePoliceChase_2EB434, 8
);

Address_CCarCtrl__JoinCarWithRoadSystem_2EC03C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2EC03C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2EC034),
(void*)&debugging_CCarCtrl__JoinCarWithRoadSystem_2EC034, 8
);

Address_CCarCtrl__UpdateCarOnRails_2ECC1C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2ECC1C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2ECC14),
(void*)&debugging_CCarCtrl__UpdateCarOnRails_2ECC14, 8
);

Address_CCarCtrl__StopCarIfNodesAreInvalid_2ED094_thumb_ = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2ED094));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2ED08C),
(void*)&debugging_CCarCtrl__StopCarIfNodesAreInvalid_2ED08C, 8
);

Address_CCarCtrl__PickNextNodeAccordingStrategy_2ED218_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2ED218));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2ED210),
(void*)&debugging_CCarCtrl__PickNextNodeAccordingStrategy_2ED210, 8
);

Address_CCarCtrl__PickNextNodeToChaseCar_2EF9D8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2EF9D8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2EF9D0),
(void*)&debugging_CCarCtrl__PickNextNodeToChaseCar_2EF9D0, 8
);

Address_CCarCtrl__PickNextNodeToFollowPath_2F0100_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F0100));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F00F8),
(void*)&debugging_CCarCtrl__PickNextNodeToFollowPath_2F00F8, 8
);

Address_CCarCtrl__IsThisAnAppropriateNode_2F06F4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F06F4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F06EC),
(void*)&debugging_CCarCtrl__IsThisAnAppropriateNode_2F06EC, 8
);

Address_CCarCtrl__FindPathDirection_2F0CA8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F0CA8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F0CA0),
(void*)&debugging_CCarCtrl__FindPathDirection_2F0CA0, 8
);

Address_CCarCtrl__PickNextNodeForPlayer_2F0E20_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F0E20));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F0E18),
(void*)&debugging_CCarCtrl__PickNextNodeForPlayer_2F0E18, 8
);

Address_CCarCtrl__FindGhostRoadHeight_2F19DC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F19DC));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F19D4),
(void*)&debugging_CCarCtrl__FindGhostRoadHeight_2F19D4, 8
);

Address_CCarCtrl__JoinCarWithRoadSystemGotoCoors_2F1BC4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F1BC4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F1BBC),
(void*)&debugging_CCarCtrl__JoinCarWithRoadSystemGotoCoors_2F1BBC, 8
);

Address_CCarCtrl__SteerAICarWithPhysics_2F1CE8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F1CE8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F1CE0),
(void*)&debugging_CCarCtrl__SteerAICarWithPhysics_2F1CE0, 8
);

Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A08_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F3A08));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F3A00),
(void*)&debugging_CCarCtrl__SteerAICarWithPhysicsFollowPath_2F3A00, 8
);

Address_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4660_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F4660));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F4658),
(void*)&debugging_CCarCtrl__SteerAICarWithPhysicsFollowPath_Racing_2F4658, 8
);

Address_CCarCtrl__SteerAICarParkPerpendicular_2F6C0C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F6C0C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F6C04),
(void*)&debugging_CCarCtrl__SteerAICarParkPerpendicular_2F6C04, 8
);

Address_CCarCtrl__SteerAICarParkParallel_2F6EC4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F6EC4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F6EBC),
(void*)&debugging_CCarCtrl__SteerAICarParkParallel_2F6EBC, 8
);

Address_CCarCtrl__SteerPlayerWhilstCruising_2F7744_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F7744));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F773C),
(void*)&debugging_CCarCtrl__SteerPlayerWhilstCruising_2F773C, 8
);

Address_CCarCtrl__DealWithBend_Racing_2F8350_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F8350));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F8348),
(void*)&debugging_CCarCtrl__DealWithBend_Racing_2F8348, 8
);

Address_CCarCtrl__ClipTargetOrientationToLink_2F8B50_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F8B50));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F8B48),
(void*)&debugging_CCarCtrl__ClipTargetOrientationToLink_2F8B48, 8
);

Address_CCarCtrl__FindPercDependingOnDistToLink_2F8E2C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2F8E2C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2F8E24),
(void*)&debugging_CCarCtrl__FindPercDependingOnDistToLink_2F8E24, 8
);

Address_CCarCtrl__FindLinksToGoWithTheseNodes_2FAE04_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2FAE04));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2FADFC),
(void*)&debugging_CCarCtrl__FindLinksToGoWithTheseNodes_2FADFC, 8
);

Address_CCarCtrl__GenerateOneEmergencyServicesCar_2FB260_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2FB260));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2FB258),
(void*)&debugging_CCarCtrl__GenerateOneEmergencyServicesCar_2FB258, 8
);

Address_CCarCtrl__ReconsiderRoute_2FB788_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2FB788));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2FB780),
(void*)&debugging_CCarCtrl__ReconsiderRoute_2FB780, 8
);

Address_CCarCtrl__FindNodesThisCarIsNearestTo_2FBAD0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x2FBAD0));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x2FBAC8),
(void*)&debugging_CCarCtrl__FindNodesThisCarIsNearestTo_2FBAC8, 8
);

Address_CEntryExit__TransitionFinished_3051E8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3051E8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3051E0),
(void*)&debugging_CEntryExit__TransitionFinished_3051E0, 8
);

Address_CGangWars__CreateAttackWave_30C888_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x30C888));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x30C880),
(void*)&debugging_CGangWars__CreateAttackWave_30C880, 8
);

Address_CGangWars__CreateDefendingGroup_30D740_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x30D740));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x30D738),
(void*)&debugging_CGangWars__CreateDefendingGroup_30D738, 8
);

Address_CAutomobile__HasCarStoppedBecauseOfLight_318A6C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x318A6C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x318A64),
(void*)&debugging_CAutomobile__HasCarStoppedBecauseOfLight_318A64, 8
);

Address_SetOneAdjacentNodeForThisNode_31A4C8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x31A4C8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x31A4C0),
(void*)&debugging_SetOneAdjacentNodeForThisNode_31A4C0, 8
);

// good
Address_CRoadBlocks__GenerateRoadBlocks_325038_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x325038));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x325030),
(void*)&debugging_CRoadBlocks__GenerateRoadBlocks_325030, 8
);

Address_CRoadBlocks__GetRoadBlockNodeInfo_32593C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32593C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x325934),
(void*)&debugging_CRoadBlocks__GetRoadBlockNodeInfo_325934, 8
);

Address_CMissionCleanup__Process_32766C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x32766C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x327664),
(void*)&debugging_CMissionCleanup__Process_327664, 8
);

Address_CStuckCarCheck__Process_328778_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x328778));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x328770),
(void*)&debugging_CStuckCarCheck__Process_328770, 8
);

Address_CRunningScript__ProcessCommands2000To2099_335760_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x335760));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x335758),
(void*)&debugging_CRunningScript__ProcessCommands2000To2099_335758, 8
);

Address_CRunningScript__ProcessCommands2300To2399_33AD74_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x33AD74));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x33AD6C),
(void*)&debugging_CRunningScript__ProcessCommands2300To2399_33AD6C, 8
);

Address_CRunningScript__ProcessCommands2400To2499_33C6A4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x33C6A4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x33C69C),
(void*)&debugging_CRunningScript__ProcessCommands2400To2499_33C69C, 8
);

Address_CRunningScript__ProcessCommands400To499_342D34_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x342D34));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x342D2C),
(void*)&debugging_CRunningScript__ProcessCommands400To499_342D2C, 8
);

Address_CRunningScript__ProcessCommands500To599_3439E0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3439E0));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3439D8),
(void*)&debugging_CRunningScript__ProcessCommands500To599_3439D8, 8
);

Address_CRunningScript__ProcessCommands700To799_344F2C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x344F2C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x344F24),
(void*)&debugging_CRunningScript__ProcessCommands700To799_344F24, 8
);

Address_CRunningScript__ProcessCommands900To999_3485A4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3485A4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x34859C),
(void*)&debugging_CRunningScript__ProcessCommands900To999_34859C, 8
);
// good

Address_CRunningScript__ProcessCommands1200To1299_350770_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x350770));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x350768),
(void*)&debugging_CRunningScript__ProcessCommands1200To1299_350768, 8
);

Address_CRunningScript__ProcessCommands1500To1599_3553F4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3553F4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3553EC),
(void*)&debugging_CRunningScript__ProcessCommands1500To1599_3553EC, 8
);

Address_CRunningScript__ProcessCommands1700To1799_35B0E8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x35B0E8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x35B0E0),
(void*)&debugging_CRunningScript__ProcessCommands1700To1799_35B0E0, 8
);

Address_CTrafficLights__ShouldCarStopForLight_362418_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x362418));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x362410),
(void*)&debugging_CTrafficLights__ShouldCarStopForLight_362410, 8
);

Address_CTrafficLights__ShouldCarStopForBridge_194C4C_arm = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_ARM_ADDRESS_FOR_JUMP(0x194C4C));
Address_CTrafficLights__ShouldCarStopForBridge_3637AA_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3637AA));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3637A0),
(void*)&debugging_CTrafficLights__ShouldCarStopForBridge_3637A0, 10
);

Address_CGame__FinalShutdown_3F3726 = g_mCalc.GetCurrentVAbyPreferedVA(0x3F3726);
Address_CGame__FinalShutdown_3F3724_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3F3724));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3F371C),
(void*)&debugging_CGame__FinalShutdown_3F371C, 8
);

Address_CGame__ReInitGameObjectVariables_3F3A1E = g_mCalc.GetCurrentVAbyPreferedVA(0x3F3A1E);
Address_CGame__ReInitGameObjectVariables_3F3A1C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x3F3A1C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x3F3A14),
(void*)&debugging_CGame__ReInitGameObjectVariables_3F3A14, 8
);

Address_CPlayerInfo__Process_409094_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x409094));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x40908C),
(void*)&debugging_CPlayerInfo__Process_40908C, 8
);

Address_CWorld__RemoveFallenPeds_428020_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x428020));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x428018),
(void*)&debugging_CWorld__RemoveFallenPeds_428018, 8
);

Address_CWorld__RemoveFallenCars_4281F4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x4281F4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x4281EC),
(void*)&debugging_CWorld__RemoveFallenCars_4281EC, 8
);

Address_InteriorGroup_c__Exit_44898C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x44898C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x448984),
(void*)&debugging_InteriorGroup_c__Exit_448984, 8
);

Address_InteriorGroup_c__SetupPaths_448CF8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x448CF8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x448CF0),
(void*)&debugging_InteriorGroup_c__SetupPaths_448CF0, 8
);

Address_InteriorGroup_c__ArePathsLoaded_44A0D8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x44A0D8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x44A0D0),
(void*)&debugging_InteriorGroup_c__ArePathsLoaded_44A0D0, 8
);

Address_CObject___CObject_4530A0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x4530A0));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x453098),
(void*)&debugging_CObject___CObject_453098, 8
);

Address_CObject__ProcessTrainCrossingBehaviour_454868_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x454868));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x454860),
(void*)&debugging_CObject__ProcessTrainCrossingBehaviour_454860, 8
);

Address_CFileLoader__LoadPedPathNode_46A090_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x46A090));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x46A088),
(void*)&debugging_CFileLoader__LoadPedPathNode_46A088, 8
);

Address_CFileLoader__LoadCarPathNode_46A20C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x46A20C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x46A204),
(void*)&debugging_CFileLoader__LoadCarPathNode_46A204, 8
);

Address_CFileLoader__ReloadPaths_46AB80_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x46AB80));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x46AB78),
(void*)&debugging_CFileLoader__ReloadPaths_46AB78, 8
);

Address_CGame__Init1_471D04_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x471D04));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x471CFC),
(void*)&debugging_CGame__Init1_471CFC, 8
);

Address_CGame__Init2_472EC0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x472EC0));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x472EB8),
(void*)&debugging_CGame__Init2_472EB8, 8
);

Address_CGenericGameStorage__GenericSave_48255C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x48255C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x482554),
(void*)&debugging_CGenericGameStorage__GenericSave_482554, 8
);

Address_CGenericGameStorage__GenericLoad_482BB0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x482BB0));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x482BA8),
(void*)&debugging_CGenericGameStorage__GenericLoad_482BA8, 8
);

Address_CPed__PositionPedOutOfCollision_49FD08_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x49FD08));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x49FD00),
(void*)&debugging_CPed__PositionPedOutOfCollision_49FD00, 8
);

Address_CPopulation__AddToPopulation_4CCAA0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x4CCAA0));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x4CCA98),
(void*)&debugging_CPopulation__AddToPopulation_4CCA98, 8
);

Address_CPopulation__CreateWaitingCoppers_4D01E0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x4D01E0));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x4D01D8),
(void*)&debugging_CPopulation__CreateWaitingCoppers_4D01D8, 8
);

Address_CPopulation__PopulateInterior_4D10F8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x4D10F8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x4D10F0),
(void*)&debugging_CPopulation__PopulateInterior_4D10F0, 8
);

Address_CTaskSimpleCreateCarAndGetIn__ProcessPed_5063DC_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5063DC));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5063D4),
(void*)&debugging_CTaskSimpleCreateCarAndGetIn__ProcessPed_5063D4, 8
);

Address_CTaskComplexGangLeader__ControlSubTask_5154F0_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5154F0));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5154E8),
(void*)&debugging_CTaskComplexGangLeader__ControlSubTask_5154E8, 8
);

Address_CTaskComplexFollowNodeRoute__ComputePathNodes_51F6A8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x51F6A8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x51F6A0),
(void*)&debugging_CTaskComplexFollowNodeRoute__ComputePathNodes_51F6A0, 8
);

Address_CTaskComplexFollowNodeRoute__ComputeRoute_51FC28_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x51FC28));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x51FC20),
(void*)&debugging_CTaskComplexFollowNodeRoute__ComputeRoute_51FC20, 8
);

Address_CTaskComplexWander__CreateSubTask_520D18_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x520D18));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x520D10),
(void*)&debugging_CTaskComplexWander__CreateSubTask_520D10, 8
);

Address_CTaskComplexWander__CreateNextSubTask_520F14_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x520F14));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x520F0C),
(void*)&debugging_CTaskComplexWander__CreateNextSubTask_520F0C, 8
);

Address_CTaskComplexWander__ComputeTargetPos_52133C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x52133C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x521334),
(void*)&debugging_CTaskComplexWander__ComputeTargetPos_521334, 8
);

Address_CTaskComplexWander__ComputeTargetHeading_5213A8_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5213A8));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5213A0),
(void*)&debugging_CTaskComplexWander__ComputeTargetHeading_5213A0, 8
);

Address_CTaskComplexWander__ControlSubTask_521400_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x521400));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5213F8),
(void*)&debugging_CTaskComplexWander__ControlSubTask_5213F8, 8
);

Address_CTaskComplexWander__ScanForBlockedNode_521678_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x521678));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x521670),
(void*)&debugging_CTaskComplexWander__ScanForBlockedNode_521670, 8
);

Address_CTaskComplexWander__UpdateDir_521834_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x521834));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x52182C),
(void*)&debugging_CTaskComplexWander__UpdateDir_52182C, 8
);

Address_CTaskComplexWander__UpdatePathNodes_521920_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x521920));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x521918),
(void*)&debugging_CTaskComplexWander__UpdatePathNodes_521918, 8
);

Address_CTaskComplexWanderGang__GetDistanceSqToNode_521A24_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x521A24));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x521A1C),
(void*)&debugging_CTaskComplexWanderGang__GetDistanceSqToNode_521A1C, 8
);

Address_CTaskComplexWanderStandard__LookForGangMembers_5231F4_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x5231F4));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x5231EC),
(void*)&debugging_CTaskComplexWanderStandard__LookForGangMembers_5231EC, 8
);

Address_CTaskInteriorGoToInfo__CreateFirstSubTask_52962C_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x52962C));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x529624),
(void*)&debugging_CTaskInteriorGoToInfo__CreateFirstSubTask_529624, 8
);

Address_CCarGenerator__DoInternalProcessing_56D530_thumb = g_mCalc.GetCurrentVAbyPreferedVA(ASM_GET_THUMB_ADDRESS_FOR_JUMP(0x56D530));
CPatch::RedirectCodeEx(INSTRUCTION_SET_THUMB, g_mCalc.GetCurrentVAbyPreferedVA(0x56D528),
(void*)&debugging_CCarGenerator__DoInternalProcessing_56D528, 8
);
#endif
///////////////////////////////////////////
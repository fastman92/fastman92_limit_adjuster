/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "VehicleSpecialFeatures.h"

#include "FileIDlimit.h"
#include "ModelSpecialFeatures.h"

#include "../Core/CCodeMover.h"
#include "../Core/CGenericLogStorage.h"
#include "../Core/FormattedOutput.h"
#include "../Core/LimitAdjuster.h"

using namespace Game;

VehicleSpecialFeatures g_vehicleSpecialFeatures;

/*
// Checks if parent ID 
static bool CheckParentID(uint32_t actualModel, uint32_t cmpParentModelID)
{
	return actualModel == cmpParentModelID;
}
*/

static uint32_t GetModelParentID()
{
	return 0;
}

// Returns true if vehicle is considered hydra
bool VehicleSpecialFeatures::IsHydra(int ID)
{
	return VehicleSpecialFeatures::ms_HydraVehicles.IsIDinList(ID);
}
	
// Commits changes
void VehicleSpecialFeatures::CommitChanges()
{
	MAKE_VAR_GAME_VERSION();
	CPatch::EnterNewLevelAndDisableDebugState();
	
	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		if (g_fileIDlimits.bAreDifficultFileTypesInt32)
			throw f92_runtime_error(
				"Currently vehicle special features are incompatible with 32-bit DFF/TXD IDs.\n"
				"You can't have both enabled at the same time."
			);

		if (g_modelSpecialFeatures.AreSpecialFeaturesEnabled())
			throw f92_runtime_error(
				"Vehicle special features are incompatible with model special features.\n"
				"You can't have both enabled at the same time."
			);

		// Hydras
		#if TRUE
		{
			// Patch IDs
			#if TRUE
			{
				// 0x406AF1
				#if TRUE
				{
					CCodeMover::StartCode(0x6CB4F3, 6);

					for (WORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x66\x81\x7e\x22", 4);
						CCodeMover::WriteData(&modelID, sizeof(WORD));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6CB4FF);
					}

					CCodeMover::FinishCode(0x6CB5EA);
				}
				#endif

				// 0x46E434
				#if TRUE
				{
					CCodeMover::StartCode(0x46E434, 6 + 6);

					for (WORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x66\x81\x7e\x22", 4);
						CCodeMover::WriteData(&modelID, sizeof(WORD));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x46E440);
					}

				CCodeMover::FinishCode(0x46EBD4);
				}
				#endif

				// 0x5254D8
				#if TRUE
				{
					CCodeMover::StartCode(0x5254D8, 0);

					for (WORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x66\x3d", 2);
						CCodeMover::WriteData(&modelID, sizeof(WORD));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x52551E);
					}

					CCodeMover::FinishCode(0x5254DE);
				}
				#endif
			
				// 0x527058
				#if TRUE
				{
					CCodeMover::StartCode(0x527058);

					for (WORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x66\x81\x78\x22", 4);
						CCodeMover::WriteData(&modelID, sizeof(WORD));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x52706A);
					}

					CCodeMover::FinishCode(0x527060);
				}
				#endif
			
				// 0x58E09F
				#if TRUE
				{
					CCodeMover::StartCode(0x58E09F);

					for (WORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x66\x81\x78\x22", 4);
						CCodeMover::WriteData(&modelID, sizeof(WORD));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x58E0BB);
					}

					CCodeMover::FinishCode(0x58E0A7);
				}
				#endif

				// 0x6A53BA
				#if TRUE
				{
					CCodeMover::StartCode(0x6A53BA);
					
					for (__int32 modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);
						CCodeMover::WriteData(&modelID, sizeof(__int32));

						CCodeMover::WriteData("\x0f\x84", 2);	// je
						CCodeMover::Write32bitRelativeAddress(0x6A5477);
					}

					CCodeMover::FinishCode(0x6A53C5);
				}
				#endif

				// 0x6B0842
				#if TRUE
				{
					CCodeMover::StartCode(0x6B0842);

					CCodeMover::WriteData((void*)0x6B0847, 8);

					for (WORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x66\x81\xff", 3);
						CCodeMover::WriteData(&modelID, sizeof(WORD));

						CCodeMover::WriteData("\x0f\x84", 2);	// je
						CCodeMover::Write32bitRelativeAddress(0x6B0851);
					}

					CCodeMover::FinishCode(0x6B0859);
				}
				#endif

				// 0x6C8F10
				#if TRUE
				{
					CCodeMover::StartCode(0x6C8F2B);

					for (__int32 modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x81\xff", 2);
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);	// je
						CCodeMover::Write32bitRelativeAddress(0x6C9053);
					}

					CCodeMover::FinishCode(0x6C8F31);

					CPatch::NOPinstructions(0x6C8F10, 6);
				}
				#endif

				// 0x6C9101
				#if TRUE
				{
					CPatch::NOPinstructions(0x6C9101, 6);

					CCodeMover::StartCode(0x6C910D);

					CCodeMover::WriteData((void*)0x6C910D, 3);

					for (WORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x66\x81\x7e\x22", 4);
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);	// je
						CCodeMover::Write32bitRelativeAddress(0x6C9112);
					}

					CCodeMover::FinishCode(0x6C9120);
				}
				#endif

				// 0x6C968E
				#if TRUE
				{
					CCodeMover::StartCode(0x6C968E);

					for (WORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x66\x81\x7e\x22", 4);
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);	// je
						CCodeMover::Write32bitRelativeAddress(0x6C9696);
					}

					CCodeMover::FinishCode(0x6C969B);
				}
				#endif

				// 0x6C9F1C
				#if TRUE
				{
					CCodeMover::StartCode(0x6C9F1C);

					for (WORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x66\x3d", 2);
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);	// je
						CCodeMover::Write32bitRelativeAddress(0x6C9F26);
					}

					CCodeMover::FinishCode(0x6CA2E9);
				}
				#endif

				// 0x6CC3B1
				#if TRUE
				{
					CCodeMover::StartCode(0x6CC3B1);

					for (WORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x66\x81\xf9", 3);
						CCodeMover::WriteData(&modelID, sizeof(modelID));


						CCodeMover::WriteData("\x0f\x84", 2);	// je
						CCodeMover::Write32bitRelativeAddress(0x6CC3BC);
					}

					CCodeMover::FinishCode(0x6CC461);
				}
				#endif

				// 0x6CD78B
				#if TRUE
				{
					CCodeMover::StartCode(0x6CD792);

					for (uint32_t modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						DWORD address = 0xC1CAD8;

						CCodeMover::WriteData("\x81\x3d", 2);
						CCodeMover::WriteData(&address, sizeof(address));
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);	// je
						CCodeMover::Write32bitRelativeAddress(0x6CD7A5);
					}

					CCodeMover::FinishCode(0x6CD79A);
				}
				#endif

				// 0x6D8FDA
				#if TRUE
				{
					CPatch::NOPinstructions(0x6D8FDA, 5);
					CCodeMover::StartCode(0x6D8FF9);

					for (WORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x66\x81\xfb", 3);
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);	// je
						CCodeMover::Write32bitRelativeAddress(0x6D8FFF);
					}

					CCodeMover::FinishCode(0x6D9084);
				}
				#endif

				// 0x6D9C04
				#if TRUE
				{
					CCodeMover::StartCode(0x6D9C04);

					for (WORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x66\x81\x7e\x22", 4);
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);	// je
						CCodeMover::Write32bitRelativeAddress(0x6D9C10);
					}

					CCodeMover::FinishCode(0x6D9C95);
				}
				#endif

				// 0x6E39B8
				#if TRUE
				{
					CPatch::NOPinstructions(0x6E39B8, 6);

					CCodeMover::StartCode(0x6E39C0);
					CCodeMover::WriteData((void*)0x6E39C0, 5);

					for (WORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x66\x81\x7e\x22", 4);
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);	// je
						CCodeMover::Write32bitRelativeAddress(0x6E39C7);
					}

					CCodeMover::FinishCode(0x6D9C95);
				}
				#endif

				// 0x6D514F
				#if TRUE
				{
					CCodeMover::StartCode(0x6D514F);

					CCodeMover::WriteData("\x0f\xb7\x46\x22", 4);	// movzx   eax, word ptr [esi+22h]

					uint32_t additional_IDs[] = {
						425, 576
					};

					for (uint32_t modelID : additional_IDs)
					{
						CCodeMover::WriteData("\x3d", 1);
						CCodeMover::WriteData(&modelID, sizeof(uint32_t));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6D5168);
					}


					for (uint32_t modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);
						CCodeMover::WriteData(&modelID, sizeof(uint32_t));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6D5168);
					}

					CCodeMover::FinishCode(0x6D53E9);
				}
				#endif
			}
			#endif

			// Patch switches
			#if TRUE
			{
				
				// 0x501C89
				#if TRUE
				{
					CPatch::PatchUINT8(0x501DB8 + 1, 1);	// disable 520 in switch table

					CCodeMover::StartCode(0x501C73);

					CCodeMover::WriteData("\x53", 1);	// push ebx
					CCodeMover::WriteData("\x0f\xb7\x42\x22", 4);	// movzx   eax, word ptr [edx+22h]


					for (uint32_t modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x501C90);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -519;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));

					CCodeMover::FinishCode(0x501C7C);

					CPatch::NOPinstructions(0x501C7F, 1);	// push ebx
				}
				#endif
				
				// 0x4FF9BD
				#if TRUE
				{
					CPatch::PatchUINT8(0x4FFD6C + 1, 1);	// disable 520 in switch table

					CCodeMover::StartCode(0x4FF980);

					CCodeMover::WriteData("\x0f\xb7\x40\x22", 4);	// movzx   eax, word ptr [edx+22h]

					for (uint32_t modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x4FF9BD);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -519;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));

					CCodeMover::FinishCode(0x4FF989);
				}
				#endif

				// 0x6C9D7E
				#if TRUE
				{
					CPatch::PatchUINT8(0x6CAAF8 + 520 - 476, 5);	// disable 520 in switch table

					CCodeMover::StartCode(0x6C9D7E);

					CCodeMover::WriteData("\x0f\xb7\x46\x22", 4);	// movzx eax,word ptr [esi+22]

					for (uint32_t modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6C9DED);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -476;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));
					CCodeMover::FinishCode(0x6C9D87);
				}
				#endif
				
				// 0x6D4D5E
				#if TRUE
				{
					CPatch::PatchUINT8(0x6CAAF8 + 520 - 425, 5);	// disable 520 in switch table

					CCodeMover::StartCode(0x6D4D5E);

					CCodeMover::WriteData("\x0f\xb7\x46\x22", 4);	// movzx eax,word ptr [esi+22]

					CCodeMover::WriteData("\x53\x57", 2);

					for (DWORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6D4DD8);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -425;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));

					CCodeMover::FinishCode(0x6D4D67);

					CPatch::PutOnAddressRelative4byteAddressToAddress(0x6D4D6C + 2, 0x6D5053);

					CPatch::NOPinstructions(0x6D4D79, 2);
				}
				#endif

				// 0x6E3457
				#if TRUE
				{
					CPatch::PatchUINT8(0x6E3804 + 520 - 425, 5);	// disable 520 in switch table

					CCodeMover::StartCode(0x6E3457);

					CCodeMover::WriteData((void*)0x6E3460, 3);		// add esp, 8
					CPatch::NOPinstructions(0x6E3460, 3);

					CCodeMover::WriteData("\x0f\xb7\x46\x22", 4);	// movzx eax,word ptr [esi+22]

					for (DWORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6E34ED);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -425;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));

					CCodeMover::FinishCode(0x6E3463);
				}
				#endif
				

				
				// 0x6D4900
				#if TRUE
				{
					CPatch::PatchUINT8(0x6D4A2C + 520 - 425, 5);	// disable 520 in switch table

					CCodeMover::StartCode(0x6D4900);

					CCodeMover::WriteData("\x0f\xb7\x41\x22", 4);	// movsx   eax, word ptr [ecx+22h]

					for (DWORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{						
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6D4984);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -425;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));

					CCodeMover::FinishCode(0x6D4909);
				}
				#endif										

				// 0x6D3E00
				#if TRUE
				{
					CPatch::PatchUINT8(0x6D3E98 + 520 - 425, 10);	// disable 520 in switch table

					CCodeMover::StartCode(0x6D3E00);

					CCodeMover::WriteData("\x0f\xb7\x41\x22", 4);	// movzx eax,word ptr [ecx+22]


					for (DWORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6D3E33);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -425;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));

					CCodeMover::FinishCode(0x6D3E09);
				}
				#endif

				// 0x6D3F30
				#if TRUE
				{
					CPatch::PatchUINT8(0x6D3F74 + 520 - 425, 3);	// disable 520 in switch table

					CCodeMover::StartCode(0x6D3F30);

					CCodeMover::WriteData("\x0f\xb7\x41\x22", 4);	// movzx eax,word ptr [ecx+22]

					for (DWORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6D3F5A);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -425;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));

					CCodeMover::FinishCode(0x6D3F39);
				}
				#endif

				// 0x6D4125
				#if TRUE
				{
					CPatch::PatchUINT8(0x6D41F0 + 520 - 425, 6);	// disable 520 in switch table

					CCodeMover::StartCode(0x6D4125);

					CCodeMover::WriteData("\x0f\xb7\x41\x22", 4);	// movzx eax,word ptr [ecx+22]

					for (DWORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6D4175);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -425;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));

					CCodeMover::FinishCode(0x6D412E);
				}
				#endif

				// 0x6D45D5
				#if TRUE
				{
					CPatch::PatchUINT8(0x6D4678 + 520 - 425, 3);	// disable 520 in switch table

					CCodeMover::StartCode(0x6D45D5);

					CCodeMover::WriteData("\x0f\xb7\x41\x22", 4);	// movzx eax,word ptr [ecx+22]

					for (DWORD modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6D4623);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -425;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));

					CCodeMover::FinishCode(0x6D45DE);
				}
				#endif

				// 0x47E0CA
				#if TRUE
				{
					CPatch::PatchUINT8(0x47F304 + 520 - 500, 45);	// disable 520 in switch table

					CCodeMover::StartCode(0x47E0B3);

					CCodeMover::WriteData("\x57", 1);	// push edi

					CCodeMover::WriteData("\x8b\xc1", 2);	// mov eax, ecx

					for (uint32_t modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x47E385);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -500;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));

					CCodeMover::FinishCode(0x47E0B9);

					CPatch::NOPinstructions(0x47E0BC, 1);	// push edi
				}
				#endif


				// 0x6D4316
				#if TRUE
				{
					CPatch::PatchUINT8(0x6D44EC + 520 - 425, 9);	// disable 520 in switch table

					CCodeMover::StartCode(0x6D42FE);

					CCodeMover::WriteData("\x8b\xc1", 2);	// mov eax, ecx

					for (uint32_t modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6D43CB);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -425;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));

					CCodeMover::FinishCode(0x6D4304);
				}
			#endif

				// 0x6D4763
			#if TRUE
				{
					CPatch::PatchUINT8(0x6D4864 + 520 - 425, 6);	// disable 520 in switch table

					CCodeMover::StartCode(0x6D474B);

					CCodeMover::WriteData("\x8b\xc7", 2);	// mov eax, edi

					for (uint32_t modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6D47AF);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -425;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));

					CCodeMover::FinishCode(0x6D4751);
				}
				#endif

				// 0x6D6ACB
				#if TRUE
				{
					CPatch::PatchUINT8(0x6D6B8C + 520 - 476, 3);	// disable 520 in switch table

					CCodeMover::StartCode(0x6D6AB9);

					CCodeMover::WriteData("\x8b\xc1", 2);	// mov eax, ecx

					for (uint32_t modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
					{
						CCodeMover::WriteData("\x3d", 1);	// cmp eax, number
						CCodeMover::WriteData(&modelID, sizeof(modelID));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6D6AEA);
					}

					CCodeMover::WriteData("\x05", 1);	// add eax, number
					__int32 switchBase = -476;
					CCodeMover::WriteData(&switchBase, sizeof(switchBase));

					CCodeMover::FinishCode(0x6D6ABF);
				}
				#endif


			}
			#endif
		}
		#endif

		// ZR350 vehicles
		#if TRUE
		{
			// Patch IDs
			#if TRUE
			{
				// 0x6ACA8D
				#if TRUE
				{
					CCodeMover::StartCode(0x6ACA8D);

					for (WORD modelID : VehicleSpecialFeatures::ms_Zr350vehicles.Array)
					{
						CCodeMover::WriteData("\x66\x3d", 2);
						CCodeMover::WriteData(&modelID, sizeof(WORD));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6ACA97);
					}

					CCodeMover::FinishCode(0x6ACBC7);				
				}
				#endif

				// 0x6E1C17
				#if TRUE
				{
					CCodeMover::StartCode(0x6E1C17);

					for (WORD modelID : VehicleSpecialFeatures::ms_Zr350vehicles.Array)
					{
						CCodeMover::WriteData("\x66\x81\x7e\x22", 4);
						CCodeMover::WriteData(&modelID, sizeof(WORD));

						CCodeMover::WriteData("\x0f\x84", 2);		// je
						CCodeMover::Write32bitRelativeAddress(0x6E1C23);
					}

					CCodeMover::FinishCode(0x6E1CCE);
				}
				#endif
			}	
			#endif
		}
		#endif
	}
#endif
	else
	{
		CPatch::LeaveThisLevel();
		return;
	}

	CPatch::LeaveThisLevel();

	VehicleSpecialFeatures::PrintLogInfo();
}

// Prints to log
void VehicleSpecialFeatures::PrintLogInfo()
{
	MAKE_VAR_GAME_VERSION();
	CGenericLogStorage::SaveTextLn("Vehicle special features are enabled");

	MAKE_DEAD_IF();
#ifdef IS_PLATFORM_WIN_X86
	else if (CGameVersion::Is_GTA_SA_1_0_US_WIN_X86(gameVersion))
	{
		// Hydras
		CGenericLogStorage::SaveFormattedTextLn(
			"Number of hydra vehicles = %d",
			VehicleSpecialFeatures::ms_HydraVehicles.GetCount()
		);

		unsigned int i = 0;

		for (int modelID : VehicleSpecialFeatures::ms_HydraVehicles.Array)
			CGenericLogStorage::SaveFormattedTextLn(
				"Hydra %d = %d",
				i++,
				modelID
			);

		// ZR350
		CGenericLogStorage::SaveFormattedTextLn(
			"Number of ZR350 vehicles = %d",
			VehicleSpecialFeatures::ms_HydraVehicles.GetCount()
		);

		i = 0;

		for (int modelID : VehicleSpecialFeatures::ms_Zr350vehicles.Array)
			CGenericLogStorage::SaveFormattedTextLn(
				"ZR350 %d = %d",
				i++,
				modelID
			);
	}
#endif

	CGenericLogStorage::WriteLineSeparator();
}

// Adds ID
void VehicleSpecialFeatures::AddHydra(int ID)
{
	this->ms_HydraVehicles.AddNewID(ID);
}

// Adds ZR350 ID
void VehicleSpecialFeatures::AddZR350(int ID)
{
	VehicleSpecialFeatures::ms_Zr350vehicles.AddNewID(ID);
}
/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "FileTypeManager.h"

#include "../Core/FormattedOutput.h"

#include <Packing\GTAdataPacking.h>

using namespace GTAdataPacking;

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	// Loads CD directory item and returns file ID
	__int32 __cdecl LoadCDdirectoryItem(
		const CDirectoryEntryExtended& entry,
		const tImgDescriptor *img,
		int imgId,
		const tGTASAimgLoadingCallPriv& loadingCallPriv
		)
	{		
		// return UNDEFINED_FILE_ID_INT32;

		const tGTASAimgLoadingCall* pBasicLoadingCall = loadingCallPriv.pBasicLoadingCall;

		CDirectoryEntryExtended xEntry = entry;

		char* pDot = strchr(xEntry.Name, '.');

		if (!pDot)
			return UNDEFINED_FILE_ID_INT32;

		*pDot = NULL;

		const char* pExtension = pDot + 1;

		if (strlen(pExtension) < 3)
			return UNDEFINED_FILE_ID_INT32;

		const char* name = xEntry.Name;

		__int32 fileIndex;

		const FileIDlimit* pFileIDlimits = &g_fileIDlimits;

		if (!_memicmp(pExtension, "IMG", 3))
		{
			uint32_t fileFlags = entry.Flags;

			GTAdataPacking::eCompressionTypeInGTASAfastman92IMGarchive compressionType
				= (GTAdataPacking::eCompressionTypeInGTASAfastman92IMGarchive)(fileFlags & 0xF);
			GTAdataPacking::eEncryptionTypeInGTASAfastman92IMGarchive encryptionType
				= (GTAdataPacking::eEncryptionTypeInGTASAfastman92IMGarchive)((fileFlags >> 4) & 0xF);

			if (compressionType != IMG_FASTMAN92_GTASA_COMPRESSION_TYPE_NONE
				|| encryptionType != IMG_FASTMAN92_GTASA_ENCRYPTION_TYPE_NONE)
			{
				printf_MessageBox("IMG archive %s\n%s file cannot be compressed or encrypted.", name, entry.Name);

				return UNDEFINED_FILE_ID_INT32;
			}

			tGTASAimgLoadingCallPriv newLoadingCallPriv = loadingCallPriv;

			newLoadingCallPriv.BaseAddOffsetInSectors += entry.PositionInSectors;

			newLoadingCallPriv.IMGarchiveName += "\\";
			newLoadingCallPriv.IMGarchiveName += entry.Name;

			CStreamingAddition::LoadCdDirectoryAdvanced(img, imgId, newLoadingCallPriv);

			return UNDEFINED_FILE_ID_INT32;
		}
		else if (!_memicmp(pExtension, "DFF", 3))
		{
			if (!CModelInfo::GetModelInfo(name, &fileIndex))
			{
				if (!pBasicLoadingCall->OnSpecialEntry || pBasicLoadingCall->OnSpecialEntry(&xEntry, pBasicLoadingCall->pUserData))
				{
					xEntry.PositionInSectors |= imgId << 24;

					// CDirectoryEntry convertedEntry;
					// convertedEntry.SetDataBasedOnExtendedEntry(xEntry);

					/*
					printf_MessageBox(
					"entry details\n"
					"name: %s\n"
					"pos: 0x%X\n"
					"size priority2: %d\n"
					"size priority1: %d\n"
					,
					convertedEntry.Filename,
					(int)(entry.PositionInSectors & 0xFFFFFF)  * IMG_ARCHIVE_SECTOR_SIZE,
					(int)convertedEntry.sizePriority2 * IMG_ARCHIVE_SECTOR_SIZE,
					(int)convertedEntry.sizePriority1 * IMG_ARCHIVE_SECTOR_SIZE
					);
					*/

					// OnSpecialEntry(&xEntry, )

					CStreamingAddition::ms_pExtraObjectsDir->AddItem(xEntry);
				}

				return UNDEFINED_FILE_ID_INT32;
			}
			else
				return fileIndex;
		}		
		else if (!_memicmp(pExtension, "TXD", 3))
		{
			// CGenericLogStorage::SaveFormattedTextLn("TXD name: %s", name);

			int TXDslot =
				((int(__cdecl *)(const char *))0x731850)(
				name
				);		// CTxdStore::FindTxdSlot

			if (TXDslot == -1)
			{
				TXDslot = ((int(__cdecl *)(const char *))0x731C80)(
					name
					);		// CTxdStore::AddTxdSlot

				((void(__cdecl *)(const char *, int))0x4C9360)(
					name,
					TXDslot
					);		// set paintjobs for vehicle model.
			}

			// printf_MessageBox("returned file ID: %d", TXDslot + FileIDlimit::GetBaseID(FILE_TYPE_TXD));

			return TXDslot + g_fileIDlimits.GetBaseID(FILE_TYPE_TXD);
		}				
		else if (!_memicmp(pExtension, "COL", 3))
		{			
			int COLslot =
				((int(__cdecl *)(const char *))0x410390)(
					name
				);		// CColStore::FindColSlot			

			if (COLslot == -1)
				COLslot = ((int(__cdecl *)(const char *))0x411140)(
					name
				);		// CColStore::AddColSlot
			
			return COLslot + g_fileIDlimits.GetBaseID(FILE_TYPE_COL);
			
		}		
		else if (!_memicmp(pExtension, "IPL", 3))
		{
			int IPLslot =
				((int(__cdecl *)(const char *))0x404AC0)(
					name
				);		// CIplStore::FindIplSlot

			if (IPLslot == -1)
				IPLslot = ((int(__cdecl *)(const char *))0x405AC0)(
					name
				);		// CIplStore::AddIplSlot

			return IPLslot + g_fileIDlimits.GetBaseID(FILE_TYPE_IPL);
		}
		else if (!_memicmp(pExtension, "DAT", 3))
		{
			if (!strncmp(name, "nodes", 5))
			{
				int DATslot = 0xCCCCCCCC;
				sscanf(name + 5, "%d", &DATslot);

				return DATslot + g_fileIDlimits.GetBaseID(FILE_TYPE_DAT);
			}
		}
		else if (!_memicmp(pExtension, "IFP", 3))
		{
			int IFPslot = ((int(__cdecl *)(const char *))0x4D3E50)(
					name
				);		// CAnimManager::RegisterAnimBlock

			return IFPslot + g_fileIDlimits.GetBaseID(FILE_TYPE_IFP);
		}
		if (!_memicmp(pExtension, "RRR", 3))
		{
			int RRRslot = ((int(__cdecl *)(const char *))0x459F80)(
					name
				);		// CVehicleRecording::RegisterRecordingFile

			return RRRslot + g_fileIDlimits.GetBaseID(FILE_TYPE_RRR);
		}
		else if (!_memicmp(pExtension, "SCM", 3))
		{
			int SCMslot = ((int(__thiscall *)(char*, const char *))0x4706C0)(
				g_fileIDlimits.CTheScripts__StreamedScripts.ptr,
					name
				);		// CStreamedScripts::RegisterScript

			return SCMslot + g_fileIDlimits.GetBaseID(FILE_TYPE_SCM);
		}
		

		// printf_MessageBox("filename: %s unknown extension: %s", entry.Filename, pExtension);
		return UNDEFINED_FILE_ID_INT32;			
	}

	/*
	// Loads CD directory item and returns file ID
	__int32 LoadCDdirectoryItemOldFormat(const CDirectoryEntry& entry, int imgId)
	{
		CDirectoryEntryExtended exEntry;
		exEntry.SetDataBasedOnStandardEntry(entry);
		
		tGTASAimgLoadingCall loadingCall = { 0 };
		return LoadCDdirectoryItem(exEntry, imgId, loadingCall);
	}
	*/
}
#endif
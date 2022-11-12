/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "Configuration.h"
#include "../eGameVersion.h"
#include "../ProjectConstants.h"
#include "../CGenericLogStorage.h"

#include "../FormattedOutput.h"
#include "../LimitAdjuster.h"
#include <StrLexStuff.h>

using namespace Game;

namespace Configuration {
	class tDocumentationWorkbook;

	namespace Formats
	{
		// Writes HTML file
		bool WriteHTMLfile(tDocumentationWorkbook* pFLAworkbook, const char* filePath)
		{
			CLimitAdjuster* pLimitAdjuster = pFLAworkbook->pLimitAdjuster;

#if 0

			FILE* fp = fopen(filePath, "w");

			if (!fp)
			{
				CGenericLogStorage::SaveFormattedTextLn(
					"HTML file could not be created: %s",
					filePath
				);				

				return false;
			}

			// Add sheet Features
#if TRUE
			{
				lxw_worksheet* worksheet = workbook_add_worksheet(workbook, "Features");

				// Set the zoom value
				worksheet_set_zoom(worksheet, SHEET_ZOOM_VALUE);

				worksheet_merge_range(worksheet,
					0, 0,
					0, 2,
					PROJECT_NAME,
					merge_format_for_project_name
				);

				worksheet_write_string(worksheet, 1, 0, "Section", second_row_left_side_format);
				worksheet_write_string(worksheet, 1, 1, "Name", second_row_left_side_format);
				worksheet_write_string(worksheet, 1, 2, "Comment", second_row_left_side_format);

				// Write entries
				unsigned int sectionID = 0;

				char sectionPointer[32];

				unsigned int row_id = 2;

				// Iterate over sections
				for (unsigned sectionID = 0; sectionID < pFLAworkbook->numberOfSections; sectionID++)
				{
					const tConfigurationSectionProcessed* pSection = pFLAworkbook->pSectionArray + sectionID;

					// Create section formula
					sprintf(sectionPointer, "=SectionNames!$A$%d", sectionID + 2);

					for (unsigned int sectionEntryID = 0;
						sectionEntryID < pSection->countOfEntries;
						sectionEntryID++)
					{
						tConfigurationSectionEntryProcessed* pSectionEntry = pSection->pEntryArray + sectionEntryID;

						// Section name
						worksheet_write_formula(worksheet, row_id, 0, sectionPointer, other_text_format);

						// Field name
						worksheet_write_string(worksheet, row_id, 1, pSectionEntry->key, other_text_format);

						// Comment
						if (pSectionEntry->comment[0])
						{
							worksheet_write_string(
								worksheet,
								row_id,
								2,
								pSectionEntry->comment,
								other_text_wrap_format
							);
						}
						else if (other_text_wrap_format)
							worksheet_write_blank(
								worksheet,
								row_id,
								2,
								other_text_format
							);

						// Values per each configuration
						for (unsigned int fieldID = 0;
							fieldID < pFLAworkbook->numberOfAllGamesInAllPlatforms;
							fieldID++)
						{
							CConfigurationField* pField = pSectionEntry->pEntryArray + fieldID;

							char cellText[256];

							int l;

							unsigned int formatID = 1;

							if (pField->ExcelState == EXCEL_FIELD_STATE_SUPPORTED)
							{
								strcpy(cellText, "Supported");
								formatID = 2;
							}
							else if (pField->ExcelState == EXCEL_FIELD_STATE_NOT_SUPPORTED)
							{
								strcpy(cellText, "Not supported");
								formatID = 1;
							}
							else if (pField->ExcelState == EXCEL_FIELD_STATE_SUPPORTED_ONLY_SHOW_VALUE)
							{
								formatID = 2;
								cellText[0] = 0;
							}
							else
							{
								worksheet_write_blank(
									worksheet,
									row_id,
									3 + fieldID,
									field_unsupported_format
								);

								continue;
							}

							l = strlen(cellText);

							char valueStr[256];

							if (pField->ValueToStr(valueStr))
								sprintf(cellText + l, l != 0 ? " (%s)" : "%s", valueStr);

							// Check if there is new line
							lxw_format* format = NULL;

							if (formatID == 2)
							{
								format = StrContainsNewLine(cellText)
									? field_supported_wrap_format
									: field_supported_format;
							}
							else if (formatID == 1)
								format = StrContainsNewLine(cellText)
								? field_unsupported_wrap_format
								: field_unsupported_format;

							worksheet_write_string(worksheet, row_id, 3 + fieldID, cellText, format);
						}

						row_id++;
					}
				}

				// Write game names
				unsigned int gameColumn = 0;

				for (int i = 0; i < pFLAworkbook->countOfPlatforms; i++)
				{
					const tPlatformConfiguration* pPlatformConfiguration = pFLAworkbook->pPlatformList + i;
					const eGameVersion* pGameVersion = pPlatformConfiguration->pGameList;
					auto& formatInfo = topRightSideFormats[i % numberOfTopRightSideFormats];

					unsigned int startColumnForCurrentPlatform = gameColumn;

					while (*pGameVersion != GAME_VERSION_UNDEFINED)
					{
						eGameVersion game = *pGameVersion;
						const char* gameVersionName = pFLAworkbook->gameNamesInAllPlatforms[gameColumn];

						// Write game name
						worksheet_write_string(
							worksheet,
							1, gameColumn + 3,
							gameVersionName,
							formatInfo.game_name_format
						);

						gameColumn++;
						pGameVersion++;
					}

					unsigned int lastColumnForCurrentPlatform = gameColumn - 1;

					// Write platform name
					if (lastColumnForCurrentPlatform != startColumnForCurrentPlatform)
						worksheet_merge_range(worksheet,
							0, startColumnForCurrentPlatform + 3,
							0, lastColumnForCurrentPlatform + 3,
							pPlatformConfiguration->platformName,
							formatInfo.platform_name_format
						);
					else
						worksheet_write_string(worksheet,
							0,
							startColumnForCurrentPlatform + 3,
							pPlatformConfiguration->platformName,
							formatInfo.platform_name_format
						);

				}

				// Freeze panes
				worksheet_freeze_panes(worksheet, 2, 3);
			}
#endif

			// Add sheet SectionNames
#if TRUE
			{
				lxw_worksheet* worksheet = workbook_add_worksheet(workbook, "SectionNames");

				// Set the zoom value
				worksheet_set_zoom(worksheet, SHEET_ZOOM_VALUE);

				worksheet_write_string(worksheet, 0, 0, "Section names", bold_format);

				unsigned int row_id = 1;

				// Iterate over sections
				for (unsigned sectionID = 0; sectionID < pFLAworkbook->numberOfSections; sectionID++)
				{
					tConfigurationSectionProcessed* pSection = pFLAworkbook->pSectionArray + sectionID;

					if (pSection->sectionName[0])
						worksheet_write_string(worksheet, row_id, 0, pSection->sectionName, NULL);
					else
						worksheet_write_formula(worksheet, row_id, 0, "=\"\"", NULL);

					row_id++;
				}
			}
#endif

			/*
			// Add sheet SupportOptions
			#if TRUE
			{
				lxw_worksheet* worksheet = workbook_add_worksheet(workbook, "SupportOptions");

				worksheet_write_string(worksheet, 0, 0, "Support possibilities", bold_format);
				worksheet_write_formula(worksheet, 1, 0, "=\"\"", NULL);
				worksheet_write_string(worksheet, 2, 0, "Supported", NULL);
			}
			#endif
			*/

			/*
			// Add sheet Informations
#if TRUE
			{
				lxw_worksheet* worksheet = workbook_add_worksheet(workbook, "Informations");

				worksheet_write_string(worksheet, 0, 0, "Project name", bold_format);
				worksheet_write_string(worksheet, 1, 0, PROJECT_NAME, NULL);

				worksheet_write_string(worksheet, 0, 1, "Version", bold_format);
				worksheet_write_string(worksheet, 1, 1, PROJECT_VERSION_ONLY, NULL);

				worksheet_write_string(worksheet, 0, 2, "Author", bold_format);
				worksheet_write_string(worksheet, 1, 2, "fastman92", NULL);

				worksheet_write_string(worksheet, 0, 3, "Website", bold_format);
				worksheet_write_url(worksheet, 1, 3, "http://fastman92.com", url_format);

				worksheet_write_string(worksheet, 0, 4, "E-mail", bold_format);
				worksheet_write_url(worksheet, 1, 4, "fastman92@gmail.com", url_format);

				// Write the date, when Excel file got generated

				// Add an Excel date format.
				lxw_format *date_format = workbook_add_format(workbook);
				format_set_num_format(date_format, "[$-x-sysdate]dddd, mmmm dd, yyyy");

				SYSTEMTIME timeOnSystem;
				GetSystemTime(&timeOnSystem);

				lxw_datetime timeOnExcelWriter;
				timeOnExcelWriter.day = timeOnSystem.wDay;
				timeOnExcelWriter.month = timeOnSystem.wMonth;
				timeOnExcelWriter.year = timeOnSystem.wYear;
				timeOnExcelWriter.hour = timeOnSystem.wHour;
				timeOnExcelWriter.min = timeOnSystem.wMinute;
				timeOnExcelWriter.sec = timeOnSystem.wSecond;

				worksheet_write_string(worksheet, 0, 5, "Excel file date created, UTC time", bold_format);
				worksheet_write_datetime(worksheet, 1, 5, &timeOnExcelWriter, date_format);
			}
#endif
			*/


			// Close file
			fclose(fp);

			CGenericLogStorage::SaveFormattedTextLn(
				"HTML file was created: %s",
				filePath
			);
			
			return true;
#endif
			return false;
		}
	}
}
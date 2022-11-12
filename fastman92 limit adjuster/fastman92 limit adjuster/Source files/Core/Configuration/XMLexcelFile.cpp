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
#include "../../resources/resource.h"

#include <StrLexStuff.h>

// xlsxwriter library used to write Documentation.xlsx
#ifdef IS_PLATFORM_WIN_X86
#include <xlsxwriter.h>
#endif

using namespace Game;

namespace Configuration {
	struct tDocumentationWorkbook;

	namespace Formats
	{
		#ifdef IS_PLATFORM_WIN_X86
		// Returns LXW color
		static lxw_color_t get_lxw_color(unsigned char red, unsigned green, unsigned blue)
		{
			return (red << 16) // red,
				| (green << 8)	// green
				| (blue);	// blue;
		}

		void SetStandardFieldFormat(lxw_format * format)
		{
			format_set_align(format, LXW_ALIGN_VERTICAL_TOP);
		}

		void SetExcelFieldSupportedFormat(lxw_format * format)
		{
			format_set_font_color(
				format,
				get_lxw_color(0, 97, 0)
			);

			format_set_bg_color(
				format,
				get_lxw_color(198, 239, 206)
			);

			SetStandardFieldFormat(format);
		}

		void SetExcelFieldUnsupportedFormat(lxw_format * format)
		{
			format_set_font_color(
				format,
				get_lxw_color(156, 0, 6)
			);

			format_set_bg_color(
				format,
				get_lxw_color(255, 199, 206)
			);

			SetStandardFieldFormat(format);
		}		

		void SetExcelFieldLeftSideFormat(lxw_format * format)
		{
			format_set_bg_color(
				format,
				get_lxw_color(220, 230, 241)
			);

			SetStandardFieldFormat(format);
		}

		void SetExcelPlatformNameFormat(lxw_format* format)
		{
			format_set_align(format, LXW_ALIGN_CENTER);
			format_set_align(format, LXW_ALIGN_VERTICAL_CENTER);
			format_set_underline(format, LXW_UNDERLINE_SINGLE);
			format_set_font_size(format, 18);
		}

		void SetExcelGameNameFormat(lxw_format* format, int secondRowFontSize)
		{
			format_set_font_size(format, secondRowFontSize);
			SetStandardFieldFormat(format);
		}

		/////////////////

		// Writes XML excel file
		bool WriteXMLexcelFile(tDocumentationWorkbook* pFLAworkbook, const char* filePath)
		{
			CLimitAdjuster* pLimitAdjuster = pFLAworkbook->pLimitAdjuster;

			const unsigned int SHEET_ZOOM_VALUE = 85;

			lxw_workbook* workbook = workbook_new(filePath);

			if (!workbook)
			{				
				CGenericLogStorage::SaveFormattedTextLn(
					"Excel file could not be created: %s",
					filePath
				);				

				return false;
			}

			/* Add some cell formats for the hyperlinks. */
			lxw_format *url_format = workbook_add_format(workbook);

			/* Create the standard url link format. */
			format_set_underline(url_format, LXW_UNDERLINE_SINGLE);
			format_set_font_color(url_format, LXW_COLOR_BLUE);

			// Bold format
			lxw_format *bold_format = workbook_add_format(workbook);
			format_set_bold(bold_format);

			//////////
			const int secondRowFontSize = 14;

			// Second row left side format
			lxw_format* second_row_left_side_format = workbook_add_format(workbook);

			format_set_align(second_row_left_side_format, LXW_ALIGN_VERTICAL_TOP);

			format_set_font_size(second_row_left_side_format, secondRowFontSize);

			format_set_bg_color(second_row_left_side_format, get_lxw_color(184, 204, 228));

			// Wrap format
			lxw_format *wrap_format = workbook_add_format(workbook);
			format_set_text_wrap(wrap_format);

			// Left side field format
			lxw_format *other_text_format = workbook_add_format(workbook);
			SetExcelFieldLeftSideFormat(other_text_format);

			lxw_format *other_text_wrap_format = workbook_add_format(workbook);
			SetExcelFieldLeftSideFormat(other_text_wrap_format);

			format_set_text_wrap(other_text_wrap_format);

			// Right side top
			struct tRightSideTopFormats
			{
				lxw_format* platform_name_format;
				lxw_format* game_name_format;
			} topRightSideFormats[2];

			unsigned int numberOfTopRightSideFormats = _countof(topRightSideFormats);

			// Set topRightSideFormats
			{
				lxw_format *format;

				// Platform name format
				format = workbook_add_format(workbook);
				SetExcelPlatformNameFormat(format);
				format_set_bg_color(format, get_lxw_color(75, 172, 198));
				topRightSideFormats[0].platform_name_format = format;

				// Game name format
				format = workbook_add_format(workbook);
				SetExcelGameNameFormat(format, secondRowFontSize);
				format_set_bg_color(format, get_lxw_color(183, 222, 232));
				topRightSideFormats[0].game_name_format = format;

				// Platform name format
				format = workbook_add_format(workbook);
				SetExcelPlatformNameFormat(format);
				format_set_bg_color(format, get_lxw_color(128, 100, 162));
				topRightSideFormats[1].platform_name_format = format;

				// Game name format
				format = workbook_add_format(workbook);
				SetExcelGameNameFormat(format, secondRowFontSize);
				format_set_bg_color(format, get_lxw_color(204, 192, 218));
				topRightSideFormats[1].game_name_format = format;
			}

			// Merge format
			lxw_format    *merge_format_for_project_name = workbook_add_format(workbook);

			/* Configure a format for the merged range. */
			format_set_align(merge_format_for_project_name, LXW_ALIGN_CENTER);
			format_set_align(merge_format_for_project_name, LXW_ALIGN_VERTICAL_CENTER);

			format_set_bg_color(
				merge_format_for_project_name,
				get_lxw_color(79, 129, 189)
			);

			format_set_font_color(
				merge_format_for_project_name,
				LXW_COLOR_WHITE
			);

			format_set_font_size(merge_format_for_project_name, 24);

			// Field supported format
			lxw_format *field_supported_format = workbook_add_format(workbook);
			SetExcelFieldSupportedFormat(field_supported_format);

			lxw_format *field_supported_wrap_format = workbook_add_format(workbook);
			SetExcelFieldSupportedFormat(field_supported_format);
			format_set_text_wrap(field_supported_wrap_format);

			// Field unsupported format
			lxw_format *field_unsupported_format = workbook_add_format(workbook);
			SetExcelFieldUnsupportedFormat(field_unsupported_format);

			lxw_format *field_unsupported_wrap_format = workbook_add_format(workbook);
			SetExcelFieldUnsupportedFormat(field_unsupported_format);
			format_set_text_wrap(field_unsupported_wrap_format);

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

				// Write game names
				unsigned int gameColumn = 0;

				for (unsigned int i = 0; i < pFLAworkbook->countOfPlatforms; i++)
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
							else if (pField->ExcelState == EXCEL_FIELD_STATE_NOT_SUPPORTED_ONLY_SHOW_VALUE)
							{
								formatID = 1;
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

				/* Add an Excel date format. */
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

			// Add sheet Internal
#if TRUE
			{
				lxw_worksheet* worksheet = workbook_add_worksheet(workbook, "Internal");

				worksheet_write_string(worksheet, 0, 0, "Auto-fit done?", bold_format);
				worksheet_write_boolean(worksheet, 0, 1, false, NULL);
			}
#endif

			// Add macroes
			char szMacroTempFileName[MAX_PATH];

#if TRUE
			{
				// Get pointer and size to resource 
				HRSRC hRes = FindResource(
					pFLAworkbook->pLimitAdjuster->hModule_of_the_FLA.windows,
					MAKEINTRESOURCE(DOCUMENTATION_MACRO_FILE),
					RT_RCDATA
				);

				HGLOBAL hMem = LoadResource(pFLAworkbook->pLimitAdjuster->hModule_of_the_FLA.windows, hRes);

				void* pMem = LockResource(hMem);
				DWORD size = SizeofResource(pFLAworkbook->pLimitAdjuster->hModule_of_the_FLA.windows, hRes);

				char lpTempPathBuffer[MAX_PATH];
				DWORD dwRetVal = 0;
				UINT uRetVal = 0;

				//  Gets the temp path env string (no guarantee it's a valid path).
				dwRetVal = GetTempPathA(MAX_PATH,          // length of the buffer
					lpTempPathBuffer); // buffer for path

				if (dwRetVal == 0)
					throw f92_runtime_error("Unable to retrieve temp path for extraction of Excel macros.");

				//  Generates a temporary file name. 
				uRetVal = GetTempFileNameA(lpTempPathBuffer, // directory for tmp files
					"DocumentationMacroes",     // temp file name prefix 
					0,                // create unique name 
					szMacroTempFileName);  // buffer for name

				if (uRetVal == 0)
					throw f92_runtime_error("GetTempFileName failed for extraction of Excel macros.");

				// Write temporary file with macroes
				FILE* fp = fopen(szMacroTempFileName, "wb");

				if (!fp)
					throw f92_runtime_error("Unable to write temporary file for extraction of Excel macros.");

				fwrite(pMem, size, 1, fp);

				fclose(fp);

				UnlockResource(hMem);
			}
#endif

			/* Add a macro that will execute when the file is opened. */
			workbook_add_vba_project(workbook, szMacroTempFileName);

			// Close workbook
			workbook_close(workbook);

			// Remove temporary file
			remove(szMacroTempFileName);			

			CGenericLogStorage::SaveFormattedTextLn(
				"Excel file was created: %s",
				filePath
			);

			return true;
		}
#endif
	}
}
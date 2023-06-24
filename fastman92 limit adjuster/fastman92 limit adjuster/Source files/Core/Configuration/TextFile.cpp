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

	namespace Formats
	{
		// Writes text file
		bool WriteTextFile(tDocumentationWorkbook* pFLAworkbook, const char* filePath)
		{
			FILE* fp = fopen(filePath, "w");

			if (!fp)
			{
				CGenericLogStorage::SaveFormattedTextLn(
					"Text file could not be created: %s",
					filePath
				);				

				return false;
			}

			// Write game names
			unsigned int gameColumn = 0;

			for (unsigned int i = 0; i < pFLAworkbook->countOfPlatforms; i++)
			{
				const tPlatformConfiguration* pPlatformConfiguration = pFLAworkbook->pPlatformList + i;
				const CGameDescription* pGameList = pPlatformConfiguration->pGameList;

				unsigned countOfGameVersionsInPlatform = pPlatformConfiguration->GetCountOfGamesInList();

				fprintf(fp, "Solution platform: %s\n", pPlatformConfiguration->solutionPlatformName);

				std::string descriptionAboutGamesInPlatform = pPlatformConfiguration->GetTextDescriptionAboutGames(true);
				std::string descriptionAboutGamesInPlatformReady;

				for (char c : descriptionAboutGamesInPlatform)
				{
					if (c == '\n')
						descriptionAboutGamesInPlatformReady += "\n\t\t";
					else
						descriptionAboutGamesInPlatformReady += c;
				}

				fprintf(fp, "%s\n", descriptionAboutGamesInPlatformReady.c_str());

				/*
				for (unsigned int gameVersionInPlatformIndex = 0; pGameList[gameVersionInPlatformIndex].gameVersion != GAME_VERSION_UNDEFINED; gameVersionInPlatformIndex++)
				{
					unsigned int curGameIndex = gameColumn + gameVersionInPlatformIndex;
					auto pGameDescription = pFLAworkbook->gamesInAllPlatforms[curGameIndex];
					
					fprintf(fp, "\t%d. %s:\n", gameVersionInPlatformIndex + 1, pGameDescription->humanReadableName);
					//pPlatformConfig->G.c_str()
					//fprintf(fp, "\n");
				}
				*/
				

				gameColumn += countOfGameVersionsInPlatform;
			}

			/*

			// Add sheet Features
			#if TRUE
			{
				char comment[sizeof(((CConfigurationField*)0)->comment) + 200];

				static const char file_beginning[] = "Section,Name,Comment,";
				fwrite(file_beginning, sizeof(file_beginning) - 1, 1, fp);

				// Write entries
				unsigned int sectionID = 0;



				// Iterate over sections
				for (unsigned sectionID = 0; sectionID < pFLAworkbook->numberOfSections; sectionID++)
				{
					const tConfigurationSectionProcessed* pSection = pFLAworkbook->pSectionArray + sectionID;		

					for (unsigned int sectionEntryID = 0;
						sectionEntryID < pSection->countOfEntries;
						sectionEntryID++)
					{
						tConfigurationSectionEntryProcessed* pSectionEntry = pSection->pEntryArray + sectionEntryID;

						// Section name
						fprintf(fp, "%s,", pSection->sectionName);

						// Section entry name
						fprintf(fp, "\"%s\",", pSectionEntry->key);

						// Comment
						std::string commentPreparedForCSV = duplicateQuoteMarks<char, std::string>(pSectionEntry->comment, '"');
						fprintf(fp, "\"%s\",", commentPreparedForCSV.c_str());
						
						// Values per each configuration
						for (unsigned int fieldID = 0;
							fieldID < pFLAworkbook->numberOfAllGamesInAllPlatforms;
							fieldID++)
						{
							CConfigurationField* pField = pSectionEntry->pEntryArray + fieldID;

							char cellText[256];

							int l;

							if (pField->ExcelState == EXCEL_FIELD_STATE_SUPPORTED)
								strcpy(cellText, "Supported");
							else if (pField->ExcelState == EXCEL_FIELD_STATE_NOT_SUPPORTED)
								strcpy(cellText, "Not supported");							
							else
								cellText[0] = 0;

							l = strlen(cellText);

							char valueStr[256];

							if (pField->ValueToStr(valueStr))
								sprintf(cellText + l, l != 0 ? " (%s)" : "%s", valueStr);

							std::string cellTextPreparedForCSV = duplicateQuoteMarks<char, std::string>(cellText, '"');

							fprintf(fp, fieldID != gameColumnLast ? "\"%s\"," : "\"%s\"", cellTextPreparedForCSV.c_str());
						}

						fwrite("\n", 1, 1, fp);
					}
				}

				

			}
			#endif
			*/



			// Close file
			fclose(fp);

			CGenericLogStorage::SaveFormattedTextLn(
				"CSV file was created: %s",
				filePath
			);
			
			return true;
		}
	}
}
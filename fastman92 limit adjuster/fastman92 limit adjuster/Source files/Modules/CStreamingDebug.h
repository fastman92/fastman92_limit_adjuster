/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#ifdef IS_PLATFORM_WIN_X86
namespace Game_GTASA
{
	class CStreamingDebug
	{
	private:
		// Processes debugging
		static void ProcessDebugging();

		// Print models loaded
		static void PrintModelsLoaded();

		// Detoured CTheScripts::Process()
		static void __cdecl Detoured_CTheScripts__Process();

		// Detoured_CStreaming::RequestModel
		static void Detoured_CStreaming__RequestModel(int dwModelId, int flags);
	public:
		


		// Applies streaming debug
		static void ApplyStreamingDebug();

	};
}
#endif
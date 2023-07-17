/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#include "Loader.h"

#include "Log.h"
#include "ForOtherProjects/PluginLoaderExports.h"

#include <Exception\exception.h>
#include <MemoryAddressCalculator/CMemoryAddressCalculator.h>
#include <MultiPlatformSupport/PlatformGeneralisation.h>
#include <MemoryPermission\MemoryPermission.h>

#include "../fastman92 limit adjuster/Source files/Core/CPatch.h"
#include "../fastman92 limit adjuster/Source files/Core/UsefulMacros.h"
#include "../fastman92 limit adjuster/Source files/ForOtherProjects/Common/common.h"


#include <string.h>

#include <android/log.h>
#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <limits.h>
#include <sys\stat.h> 
#include <stdexcept>
#include <unistd.h>

#include <Array/countof.h>
#include <fileIO.h>

std::vector<CLoadedPluginInfo> CPluginLoader::ms_loadedPluginsArray;

jobject CPluginLoader::ms_mainActivityDuringLaunch = 0;

bool CPluginLoader::bCLEOloaded = false;

#ifdef IS_PLATFORM_ANDROID

#if 0
extern "C" int JNIEXPORT  __attribute__((section("bar"))) myFunction()
{
	return 1;
}


static char myVar[] = "my string to be changed";

void mprotect_test()
{
	tMemoryPermissionChangeRequest request; \
	// request.lpAddress = &myVar;
	// request.lpAddress = (void*)&myFunction;
	request.lpAddress = g_Loader.TrampolineSpacePtr;
	

	request.dwSize = 4;

	
	
	request.flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_READWRITE);
	bool result = SetMemoryPermission(&request);

	*(int*)request.lpAddress = 5;

	request.flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_EXECUTE_READ);
	result = SetMemoryPermission(&request);

	if (result)
		OutputFormattedDebugString("mprotect worked\n");
	else
		OutputFormattedDebugString("mprotect did not work\n");


	request.flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_READWRITE);
	result = SetMemoryPermission(&request);
}
#endif

// Sets the path to external storage directory
static void GetPackageName(JNIEnv* env, jobject context, char* strPath, size_t bufferSize)
{
	jclass android_content_Context = env->GetObjectClass(context);
	jmethodID midGetPackageName = env->GetMethodID(android_content_Context, "getPackageName", "()Ljava/lang/String;");
	jstring packageName = (jstring)env->CallObjectMethod(context, midGetPackageName);

	if (packageName)
	{
		const char* packageNameStr = env->GetStringUTFChars(packageName, NULL);
		strncpy(strPath, packageNameStr, bufferSize);

		env->ReleaseStringUTFChars(packageName, packageNameStr);
	}
}

// Sets the path to external storage directory
static void GetExternalStorageDirectory(JNIEnv* env, char* strPath, size_t bufferSize)
{
	jclass classEnvironment = env->FindClass("android/os/Environment");
	jmethodID methodIDgetExternalStorageDirectory = env->GetStaticMethodID(classEnvironment, "getExternalStorageDirectory", "()Ljava/io/File;");
	jobject objectFile = env->CallStaticObjectMethod(classEnvironment, methodIDgetExternalStorageDirectory);

	jclass classFile = env->GetObjectClass(objectFile);
	jmethodID methodIDgetAbsolutePath = env->GetMethodID(classFile, "getAbsolutePath", "()Ljava/lang/String;");
	jstring stringPath = (jstring)env->CallObjectMethod(objectFile, methodIDgetAbsolutePath);

	if (stringPath)
	{
		const char* strPathValueStr = env->GetStringUTFChars(stringPath, NULL);

		strncpy(strPath, strPathValueStr, bufferSize);
		env->ReleaseStringUTFChars(stringPath, strPathValueStr);
	}
}

// Sets the path to DEX cache directory
static void GetCacheDirectory(JNIEnv* env, jobject context, char* strPath, size_t bufferSize)
{
	jobject objectFile;
	bool bReadFromF92launcher = false;
	jmethodID midGetCacheDir;

	jclass classF92launcherSettings = env->FindClass("com/fastman92/main_activity_launcher/Settings");

	if (classF92launcherSettings)
	{
		midGetCacheDir = env->GetStaticMethodID(classF92launcherSettings, "getCacheDir", "(Landroid/content/Context;)Ljava/io/File;");

		if (midGetCacheDir)
		{
			objectFile = env->CallStaticObjectMethod(classF92launcherSettings, midGetCacheDir, context);
			bReadFromF92launcher = true;
		}
	}

	if (!bReadFromF92launcher)
	{
		if (env->ExceptionCheck())
			env->ExceptionClear();

		jclass android_content_Context = env->GetObjectClass(context);

		midGetCacheDir = env->GetMethodID(android_content_Context, "getCacheDir", "()Ljava/io/File;");
		objectFile = (jstring)env->CallObjectMethod(context, midGetCacheDir);
	}

	jclass classFile = env->GetObjectClass(objectFile);

	jmethodID methodIDgetAbsolutePath = env->GetMethodID(classFile, "getAbsolutePath", "()Ljava/lang/String;");
	jstring stringPath = (jstring)env->CallObjectMethod(objectFile, methodIDgetAbsolutePath);

	if (stringPath)
	{
		const char* strPathValueStr = env->GetStringUTFChars(stringPath, NULL);

		strncpy(strPath, strPathValueStr, bufferSize);
		env->ReleaseStringUTFChars(stringPath, strPathValueStr);
	}
}

// Sets the path to external files directory
static void GetExternalFilesDirectory(JNIEnv* env, jobject context, char* strPath, size_t bufferSize)
{
	jobject objectFile;
	bool bReadFromF92launcher = false;
	jmethodID methodIDgetExternalFilesDir;

	jclass classF92launcherSettings = env->FindClass("com/fastman92/main_activity_launcher/Settings");

	if (classF92launcherSettings)
	{
		methodIDgetExternalFilesDir = env->GetStaticMethodID(classF92launcherSettings, "getExternalFilesDir", "(Landroid/content/Context;)Ljava/io/File;");
		
		if (methodIDgetExternalFilesDir)
		{
			objectFile = env->CallStaticObjectMethod(classF92launcherSettings, methodIDgetExternalFilesDir, context);
			bReadFromF92launcher = true;
		}
	}

	if (!bReadFromF92launcher)
	{
		if (env->ExceptionCheck())
			env->ExceptionClear();

		jclass android_content_Context = env->GetObjectClass(context);

		methodIDgetExternalFilesDir = env->GetMethodID(android_content_Context, "getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;");

		objectFile = (jstring)env->CallObjectMethod(context, methodIDgetExternalFilesDir, nullptr);
	}
		
	jclass classFile = env->GetObjectClass(objectFile);

	jmethodID methodIDgetAbsolutePath = env->GetMethodID(classFile, "getAbsolutePath", "()Ljava/lang/String;");
	jstring stringPath = (jstring)env->CallObjectMethod(objectFile, methodIDgetAbsolutePath);

	if (stringPath)
	{
		const char* strPathValueStr = env->GetStringUTFChars(stringPath, NULL);

		strncpy(strPath, strPathValueStr, bufferSize);
		env->ReleaseStringUTFChars(stringPath, strPathValueStr);
	}
}

uintptr_t pOriginal_GTAActivity_initTouchSense = 0;

class CPluginLoaderHelper
{
public:

	////////////////////////////
	typedef jboolean(*type_NvEventQueueActivity_init_ptr)(JNIEnv* env, jobject GTAactivity, jboolean paramBoolean);
	static type_NvEventQueueActivity_init_ptr original_NvEventQueueActivity_init;

	// from com.nvidia.devtech.NvEventQueueActivity
	static jboolean NvEventQueueActivity_init(JNIEnv* env, jobject GTAactivity, jboolean paramBoolean)
	{
		jboolean bResult = original_NvEventQueueActivity_init(env, GTAactivity, paramBoolean);
		
		g_Loader.DoAppInitializationStage(env, GTAactivity);

		return bResult;
	}

	////////////////////////////
	// typedef void(*type_GTAActivity_initTouchSense_ptr)(JNIEnv* env, jobject GTAactivity, jobject paramContext);
	// static type_GTAActivity_initTouchSense_ptr original_GTAActivity_initTouchSense;
	#ifdef IS_PLATFORM_ANDROID_ARM32
	static TARGET_ARM NAKED void original_GTAActivity_initTouchSense(JNIEnv* env, jobject GTAactivity, jobject paramContext)
	{
		__asm
		(
			".arm\n"
			"STMFD           SP!, {R3-R6,R11,LR}\n"
			"ADD             R11, SP, #0x14\n"

			ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(pOriginal_GTAActivity_initTouchSense)
			);
	}

	// from com.rockstargames.gtalcs.GTAActivity
	static void GTAActivity_initTouchSense(JNIEnv* env, jobject GTAactivity, jobject paramContext)
	{
		original_GTAActivity_initTouchSense(env, GTAactivity, paramContext);
		
		g_Loader.DoAppInitializationStage(env, GTAactivity);
	}
	#endif
	////////////////////////////////
};

CPluginLoaderHelper::type_NvEventQueueActivity_init_ptr CPluginLoaderHelper::original_NvEventQueueActivity_init = nullptr;

static void ReplacePointerToNvEventQueueActivity_init(uintptr_t pInit)
{
	CPluginLoaderHelper::original_NvEventQueueActivity_init =
		*(CPluginLoaderHelper::type_NvEventQueueActivity_init_ptr*)pInit;

	tMemoryPermissionChangeRequest request;
	request.lpAddress = (void*)pInit;
	request.dwSize = sizeof(void*);

	request.flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_READWRITE);

	if (!SetMemoryPermission(&request))
		throw f92_runtime_error("ReplacePointerToNvEventQueueActivity_init, unable to set R+W permission. Error = %d", errno);

	*(void**)pInit = (void*)&CPluginLoaderHelper::NvEventQueueActivity_init;

	request.flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_READONLY);

	if (!SetMemoryPermission(&request))
		throw f92_runtime_error("ReplacePointerToNvEventQueueActivity_init, unable to set R permission. Error = %d", errno);

	OutputFormattedDebugString("Pointer to com.nvidia.devtech.NvEventQueueActivity.init replaced on 0x%llX%.",
		(uint64_t)pInit
	);
}
#endif

// Constructor
CPluginLoader::CPluginLoader()
{
	this->ms_originalPackageName[0] = 0;
	this->ms_packageName[0] = 0;
	this->FLApluginHandle = nullptr;
	this->pTargetArchABI = TOSTRING(TARGET_ARCH_ABI);

	this->TrampolineSpacePtr = 0;
	this->TrampolineSpaceSize = 0;
	this->TrampolinePosition = 0;
}

// Sets path by function from loader
void CPluginLoader::GetApplicationLibDirectoryPath(char* libPluginPath)
{
	Dl_info info;
	int info_result = dladdr((const void*)&GetApplicationLibDirectoryPath, &info);

	// remove a filename
	int index_of_last_slash = 0;

	for (unsigned int i = 0; info.dli_fname[i]; i++)
	{
		char c = info.dli_fname[i];

		if (c == '/' || c == '\\')
			index_of_last_slash = i;
	}

	memcpy(libPluginPath, info.dli_fname, index_of_last_slash);
	libPluginPath[index_of_last_slash] = 0;
}

static int someVariable;



// Initializes
bool CPluginLoader::InitialiseLoading(
	JavaVM* javaVm,
	void* reserved,
	const void* someAddressFromApplicationLibrary
)
{
	CMemoryAddressCalculator memCalc;

	{
		// Find out handle and base address of application library
		Dl_info applicationModuleInfo;

		if (!dladdr(someAddressFromApplicationLibrary, &applicationModuleInfo))
		{
			throw f92_runtime_error("Can't get an information about application library.");
			return false;
		}

		this->m_baseAddressForApplicationLibrary = applicationModuleInfo.dli_fbase;

		
		memCalc.Initialize(0, (uintptr_t)this->m_baseAddressForApplicationLibrary);

		const char* applicationModuleFilename = GetFilenameFromPath(applicationModuleInfo.dli_fname);

		this->applicationLibHandle = dlopen(applicationModuleFilename, 4);	// 4 - RTLD_NOLOAD
	}

	{
		// Find out handle and base address of plugin loader
		Dl_info pluginLoaderModuleInfo;

		if (!dladdr(&someVariable, &pluginLoaderModuleInfo))
		{
			throw f92_runtime_error("Can't get an information about application library.");
			return false;
		}

		const char* filename = GetFilenameFromPath(pluginLoaderModuleInfo.dli_fname);

		this->pluginLoaderHandle = dlopen(filename, 4);	// 4 - RTLD_NOLOAD
	}

	/////
	// Init array
	#if 0
	{
		void(**InitArrayPointer)() = (void(**)())dlsym(this->applicationLibHandle, "InitArray");

		uint32_t* pInitArrayCount = (uint32_t*)dlsym(this->applicationLibHandle, "InitArrayCount");

		for (uint32_t i = 0; i < *pInitArrayCount; i++)
		{
			if(InitArrayPointer[i])
				InitArrayPointer[i]();
		}
	}
	#endif
	/////

	this->ms_loadedPluginsArray.clear();

	this->m_javaVm = javaVm;
	this->m_reserved = reserved;


	const char* pApplicationIdentifierDeprecated = (const char*)dlsym(this->applicationLibHandle, "ApplicationIdentifierForPluginLoaderDeprecated");

	memcpy(this->ms_applicationIdentifierDeprecated, pApplicationIdentifierDeprecated, sizeof(this->ms_applicationIdentifierDeprecated));

	this->pApplicationIdentifier = (const char*)dlsym(this->applicationLibHandle, "ApplicationIdentifierForPluginLoader");

	this->TrampolineSpacePtr = (char*)dlsym(this->applicationLibHandle, "TrampolineSpace");
	this->TrampolineSpaceSize = *(uint32_t*)dlsym(this->applicationLibHandle, "TrampolineSpaceSize");

	if (!CPatch::IsInitialized())
		CPatch::Init();

	// Add path from APK and load libcleo.so
	{
		char libPluginPath[PATH_MAX];
		this->GetApplicationLibDirectoryPath(libPluginPath);

		this->m_pluginDirectoryPaths.push_back(CPluginDirectory(libPluginPath, 0, ePluginLoadingMode::LOAD_FLA_ONLY));

		this->LoadCLEO(libPluginPath);
	}

	// Replace JNI init function
	{
		MAKE_DEAD_IF();
		#ifdef IS_PLATFORM_ANDROID_ARMEABI_V7A
		else if (!strcmp(this->pApplicationIdentifier, "Bully_AE|1.0.0.18|armeabi-v7a"))	// Bully Scholarship Edition 1.0.0.18
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0xB72FC0)
			);
		}
		else if (!strcmp(this->pApplicationIdentifier, "GTA_III|1.8|armeabi-v7a"))	// GTA III 1.8
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0x351A48)
			);
		}
	
		else if (!strcmp(this->pApplicationIdentifier, "GTA_III|1.9|armeabi-v7a"))	// GTA III 1.9, ANDROID_ARM32
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0x351A58)
			);
		}
		else if (!strcmp(this->pApplicationIdentifier, "GTA_VC|1.09|armeabi-v7a"))	// GTA VC 1.09
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0x3D20D8)
			);
		}
		else if (!strcmp(this->pApplicationIdentifier, "GTA_VC|1.10|armeabi-v7a"))
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0x436248)
			);
		}
		else if (!strcmp(this->pApplicationIdentifier, "GTA_VC|1.12|armeabi-v7a"))
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0x436248)
			);
		}
		else if (!strcmp(this->pApplicationIdentifier, "GTA_SA|1.08|armeabi-v7a"))
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0x5DDC60)
			);
		}
		else if (!strcmp(this->pApplicationIdentifier, "GTA_SA|2.00|armeabi-v7a") // GTA SA 2.00
			|| !strcmp(this->pApplicationIdentifier, "GTA_SA_GER|2.09|armeabi-v7a")	// // GTA SA GER 2.09
		)
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0x661E48)
			);
		}
		else if (!strcmp(this->pApplicationIdentifier, "GTA_SA|2.10|armeabi-v7a"))	// GTA SA 2.10
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0x661E38)
			);
		}
		else if (!strcmp(this->pApplicationIdentifier, "GTA_CTW|1.04|armeabi-v7a"))	// GTA CTW 1.04
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0x891E28)
			);
		}
		else if (!strcmp(this->pApplicationIdentifier, "GTA_LCS|2.4|armeabi-v7a"))	// GTA LCS 2.4
		{
			pOriginal_GTAActivity_initTouchSense = memCalc.GetCurrentVAbyPreferedVA(0x248A50);

			uintptr_t Address_GTAActivity_initTouchSense = memCalc.GetCurrentVAbyPreferedVA(0x248A48);

			CPatch::RedirectCodeEx(
				INSTRUCTION_SET_ARM,
				Address_GTAActivity_initTouchSense,
				(const void*)&CPluginLoaderHelper::GTAActivity_initTouchSense
			);

			OutputFormattedDebugString(
				"Function Java_com_rockstargames_gtalcs_GTAActivity_initTouchSense (0x%llX) redirected.",
				(uint64_t)Address_GTAActivity_initTouchSense
			);
		}
		#elif defined(IS_PLATFORM_ANDROID_ARM64_V8A)
		else if (!strcmp(this->pApplicationIdentifier, "GTA_III|1.9|arm64-v8a"))
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0x45EEE8)
			);
		}
		else if (!strcmp(this->pApplicationIdentifier, "GTA_VC|1.10|arm64-v8a"))
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0x569BF8)
			);
		}
		else if (!strcmp(this->pApplicationIdentifier, "GTA_VC|1.12|arm64-v8a"))
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0x56DBE8)
			);
		}
		else if (!strcmp(this->pApplicationIdentifier, "GTA_SA|2.10|arm64-v8a"))	// GTA SA 2.10
		{
			ReplacePointerToNvEventQueueActivity_init(
				memCalc.GetCurrentVAbyPreferedVA(0x824BF8)
			);
		}
		#endif
		else
		{
			throw f92_runtime_error("Missing code for initialisation of plugin loader for the current application version");
			return false;
		}

		return true;
	}
}

// Loads CLEO
void CPluginLoader::LoadCLEO(const char* directory)
{
	void* pluginHandle;
	
	char path[PATH_MAX];
	sprintf(path, "%s/libcleo.so", directory);
	
	bool bCanLoadCleo = true;
	
	if (bCanLoadCleo)
	{
		OutputFormattedDebugString("Trying to load CLEO: %s", path);

		pluginHandle = dlopen(path, RTLD_GLOBAL | RTLD_LAZY);

		if (pluginHandle)
		{
			type_JNI_OnLoad pJni_OnLoad = (type_JNI_OnLoad)dlsym(pluginHandle, "JNI_OnLoad");

			if (pJni_OnLoad)
				pJni_OnLoad(this->m_javaVm, this->m_reserved);
		}
		else
			OutputFormattedDebugString("Could not load CLEO.");
	}
	else
		OutputFormattedDebugString("CLEO should not be loaded by plugin loader.");
}

// Prescans a directory
void CPluginLoader::PrescanDirectory(
	const CPluginDirectory* pDirectory
)
{
	////////////////////////////
	char path[PATH_MAX];
	void *pluginHandle = nullptr;
	
	DIR* dir = opendir(pDirectory->path.c_str());

	dirent* drnt;

	while ((drnt = readdir(dir)) != nullptr)
	{
		CLoadedPluginInfo pluginInfo;

		if (this->IsPluginWithThisNameAlreadyLoaded(drnt->d_name))
			continue;

		if (!CheckIfValidPluginFileName(drnt->d_name))
			continue;

		if (pDirectory->loadingMode == ePluginLoadingMode::LOAD_FLA_ONLY)
		{
			if (strcmp(drnt->d_name, FLA_FILENAME))
				continue;
		}

		pluginInfo.loadingMode = ePluginLoadingMode::LOAD_PLUGINS;		

		pluginInfo.pDirectory = pDirectory;
		strncpy(pluginInfo.filename, drnt->d_name, sizeof(pluginInfo.filename));

		//////

		this->ms_loadedPluginsArray.push_back(pluginInfo);
	}

	closedir(dir);
}

// Loads plugins
void CPluginLoader::FinishLoadingPlugins()
{
	char path[PATH_MAX];
	void* pluginHandle;

	// startParams
	tPluginStartParams startParams;
	memset(&startParams, 0, sizeof(startParams));
	startParams.structureSize = sizeof(tPluginStartParams);
	startParams.jvm = this->m_javaVm;
	startParams.second_param_reserved = this->m_reserved;
	startParams.applicationLibIdentifierStr = this->pApplicationIdentifier;
	memcpy(startParams.applicationLibIdentifierDeprecated, this->ms_applicationIdentifierDeprecated, sizeof(startParams.applicationLibIdentifierDeprecated));
	startParams.applicationLibBaseAddress = this->m_baseAddressForApplicationLibrary;

	startParams.pTargetArchABI = this->pTargetArchABI;
	startParams.pluginLoaderHandle = this->pluginLoaderHandle;

	///////

	for (CLoadedPluginInfo& pluginInfo : this->ms_loadedPluginsArray)
	{
		sprintf(path, "%s/%s", pluginInfo.pDirectory->path.c_str(), pluginInfo.filename);

		if (pluginInfo.loadingMode == ePluginLoadingMode::LOAD_PLUGINS
			|| pluginInfo.loadingMode == ePluginLoadingMode::LOAD_FLA_ONLY)
		{
			OutputFormattedDebugString("Loading %s", path);

			pluginHandle = dlopen(path, RTLD_GLOBAL | RTLD_LAZY);
			
			if (pluginInfo.loadingMode == ePluginLoadingMode::LOAD_FLA_ONLY)
			{
				OutputFormattedDebugString("The FLA was just loaded.");
				FLApluginHandle = pluginHandle;
			}

			OutputFormattedDebugString("Handle of shared object: 0x%llX", (uint64_t)pluginHandle);

			// OnPluginLoad
			tOnPluginLoad pOnPluginLoad = (tOnPluginLoad)dlsym(pluginHandle, "OnPluginLoad");

			// OnApplicationInit
			tOnApplicationInit pOnApplicationInit = (tOnApplicationInit)dlsym(pluginHandle, "OnApplicationInit");

			// OnApplicationInitEx
			tOnPluginLoadWhenAppIsInitialized pOnPluginLoadWhenAppIsInitialized =
				(tOnPluginLoadWhenAppIsInitialized)dlsym(pluginHandle, "OnPluginLoadWhenAppIsInitialized");

			////
			startParams.pluginHandle = pluginHandle;
			startParams.pluginLibraryPath = path;
			startParams.applicationLibHandle = this->applicationLibHandle;

			// Call OnApplicationInitEx
			if (pOnPluginLoadWhenAppIsInitialized)
			{
				if (pOnPluginLoad || pOnApplicationInit)
					OutputFormattedDebugString("Found OnApplicationInitEx and old OnPluginLoad/OnApplicationInit) in %s. This is wrong.", pluginInfo.filename);
				else
				{
					OutputFormattedDebugString("Found OnApplicationInitEx in %s", pluginInfo.filename);

					pOnPluginLoadWhenAppIsInitialized(
						&startParams
					);					
				}
			}
			else
			{
				if (!pOnPluginLoad && !pOnApplicationInit)
					OutputFormattedDebugString("Can't find OnApplicationInitEx in %s. Can't find OnPluginLoad/OnApplicationInit as well.", pluginInfo.filename);
				else
				{
					// Call OnPluginLoad
					if (pOnPluginLoad)
					{
						OutputFormattedDebugString("Found OnPluginLoad in %s", pluginInfo.filename);

						pOnPluginLoad(
							&startParams
						);
					}

					// Call OnApplicationInit
					if (pOnApplicationInit)
					{
						OutputFormattedDebugString("Found OnApplicationInit in %s", pluginInfo.filename);

						pOnApplicationInit();
					}
				}
			}
		}
	}

	// Set R+X permissions for trampoline space
	if (this->TrampolineSpacePtr)
	{
		tMemoryPermissionChangeRequest request;
		request.lpAddress = this->TrampolineSpacePtr;
		request.dwSize = this->TrampolineSpaceSize;

		// request.lpAddress = new char[request.dwSize];

		request.flNewProtect = GetNativeNewProtect(F92_MEM_PAGE_EXECUTE_READ);

		bool result = SetMemoryPermission(&request);

		if (!SetMemoryPermission(&request))
			throw f92_runtime_error("TrampolineSpace, unable to set E+R permission again. Address: 0x%llX Error = %d",
			(uint64_t)request.lpAddress, errno
			);
	}
}

static jobject getGlobalContext(JNIEnv *env)
{
	jclass activityThread = env->FindClass("android/app/ActivityThread");
	jmethodID currentActivityThread = env->GetStaticMethodID(activityThread, "currentActivityThread", "()Landroid/app/ActivityThread;");
	jobject at = env->CallStaticObjectMethod(activityThread, currentActivityThread);

	jmethodID getApplication = env->GetMethodID(activityThread, "getApplication", "()Landroid/app/Application;");
	jobject context = env->CallObjectMethod(at, getApplication);
	return context;
}

void remove_dir(const char *path, bool removeThisDir = true)
{
	struct dirent *entry = NULL;
	DIR *dir = NULL;
	dir = opendir(path);

	if (dir)
	{
		while ((entry = readdir(dir)))
		{
			DIR *sub_dir = NULL;
			FILE *file = NULL;
			char abs_path[PATH_MAX];

			if ((*(entry->d_name) != '.') || ((strlen(entry->d_name) > 1) && (entry->d_name[1] != '.')))
			{
				sprintf(abs_path, "%s/%s", path, entry->d_name);
				if ((sub_dir = opendir(abs_path)))
				{
					closedir(sub_dir);
					remove_dir(abs_path, true);
				}
				else
				{
					if ((file = fopen(abs_path, "r")))
					{
						fclose(file);
						remove(abs_path);
					}
				}
			}
		}
	}

	if (removeThisDir)
		remove(path);
}

// Checks if plugin name with this name is already loaded
bool CPluginLoader::IsPluginWithThisNameAlreadyLoaded(const char* filename)
{
	for (CLoadedPluginInfo& info : this->ms_loadedPluginsArray)
		if (!strcmp(info.filename, filename))
			return true;
	
	return false;
}

// Checks if valid plugin name
bool CPluginLoader::CheckIfValidPluginFileName(const char* filename)
{
	int l = strlen(filename);

	if (l < 12)
		return false;

	return !memcmp(filename, "libplugin", 9)
		&& !memcmp(filename + l - 3, ".so", 3);
}

// Checks if valid SO library name
bool CPluginLoader::CheckIfValidSOlibraryName(const char* filename)
{
	int l = strlen(filename);

	if (l < 3)
		return false;

	return !memcmp(filename + l - 3, ".so", 3);
}

// Load plugins
void CPluginLoader::LoadPlugins()
{
	// Load from Android/Android_unprotected directory
	{
		jobject context = getGlobalContext(jniEnv);

		jclass android_content_Context = jniEnv->GetObjectClass(context);
		jmethodID midGetDir = jniEnv->GetMethodID(android_content_Context, "getDir", "(Ljava/lang/String;I)Ljava/io/File;");

		jobject f92pluginsStr = jniEnv->NewStringUTF("f92plugins");

		jobject pluginsDir = jniEnv->CallObjectMethod(context, midGetDir, f92pluginsStr, false);

		jniEnv->DeleteLocalRef(f92pluginsStr);

		/////
		jclass classFile = jniEnv->GetObjectClass(pluginsDir);
		jmethodID methodIDgetAbsolutePath = jniEnv->GetMethodID(classFile, "getAbsolutePath", "()Ljava/lang/String;");
		jstring stringPath = (jstring)jniEnv->CallObjectMethod(pluginsDir, methodIDgetAbsolutePath);

		const char* pluginsPathStr = 0;

		if (stringPath)
		{
			pluginsPathStr = jniEnv->GetStringUTFChars(stringPath, NULL);

			this->m_pluginDirectoryPaths.push_back(CPluginDirectory(pluginsPathStr, this->ms_PluginDirectory, ePluginLoadingMode::LOAD_PLUGINS));

			////////
			remove_dir(pluginsPathStr, false);
			
			// Copy files to pluginsPathStr
			if (DIR* dir = opendir(this->ms_PluginDirectory))
			{
				struct dirent *entry = NULL;

				while ((entry = readdir(dir)))
				{
					if (CheckIfValidSOlibraryName(entry->d_name))
					{
						char sourcePath[PATH_MAX];
						char destinationPath[PATH_MAX];
						sprintf(sourcePath, "%s/%s", this->ms_PluginDirectory, entry->d_name);
						sprintf(destinationPath, "%s/%s", pluginsPathStr, entry->d_name);

						FILE* sourceFp = fopen(sourcePath, "rb");

						if (!sourceFp)
							throw f92_runtime_error("Unable to open for reading: %s", sourcePath);

						FILE* destinationFp = fopen(destinationPath, "wb");

						if (!destinationFp)
							throw f92_runtime_error("Unable to open for writing: %s", destinationFp);

						fseek(sourceFp, 0, SEEK_END);
						auto size = ftell(sourceFp);
						fseek(sourceFp, 0, SEEK_SET);
						
						char* pContents = new char[size];

						fread(pContents, size, 1, sourceFp);
						fwrite(pContents, size, 1, destinationFp);

						delete[] pContents;

						fclose(sourceFp);
						fclose(destinationFp);
					}
				}
			}
			else
				throw f92_runtime_error("Unable to open directory %s", this->ms_PluginDirectory);

			////////
			jniEnv->ReleaseStringUTFChars(stringPath, pluginsPathStr);
		}
	}

	// Load plugins in directories
	for (auto it = this->m_pluginDirectoryPaths.rbegin();
		it != this->m_pluginDirectoryPaths.rend();
		it++)
	{
		CPluginDirectory* pDirectory = &*it;

		if(!pDirectory->copiedFromPath.size())
			OutputFormattedDebugString("Scanning directory: %s\n", pDirectory->path.c_str());
		else
			OutputFormattedDebugString("Scanning directory: %s (copied from: %s)\n", pDirectory->path.c_str(), pDirectory->copiedFromPath.c_str());

		this->PrescanDirectory(pDirectory);
	}

	this->FinishLoadingPlugins();
}

// Initialises the directory paths
void CPluginLoader::InitialiseDirectoryPaths(JNIEnv* jniEnv, jobject mainActivity)
{
	bool bPathsInitialized = false;
	jclass NvUtilClass = jniEnv->FindClass("com/nvidia/devtech/NvUtil");

	if (NvUtilClass)
	{
		jmethodID g_hasAppLocalValue = jniEnv->GetMethodID(NvUtilClass, "hasAppLocalValue", "(Ljava/lang/String;)Z");
		jmethodID g_getAppLocalValue = jniEnv->GetMethodID(NvUtilClass, "getAppLocalValue", "(Ljava/lang/String;)Ljava/lang/String;");
		jmethodID g_setAppLocalValue = jniEnv->GetMethodID(NvUtilClass, "setAppLocalValue", "(Ljava/lang/String;Ljava/lang/String;)V");
		jmethodID g_getParameter = jniEnv->GetMethodID(NvUtilClass, "getParameter", "(Ljava/lang/String;)Ljava/lang/String;");

		jmethodID getInstance = jniEnv->GetStaticMethodID(NvUtilClass, "getInstance", "()Lcom/nvidia/devtech/NvUtil;");

		if (!getInstance)
			throw f92_runtime_error("Cannot find com.nvidia.devtech.NvUtil.getInstance static method.");

		jobject g_globalThiz = jniEnv->CallStaticObjectMethod(NvUtilClass, getInstance);

		if (!g_globalThiz)
			throw f92_runtime_error("Function com.nvidia.devtech.NvUtil.getInstance() returned null.");

		/////////////////
		jstring keyName;
		jstring keyValue;

		// STORAGE_ROOT
		keyName = jniEnv->NewStringUTF("STORAGE_ROOT");
		keyValue = (jstring)jniEnv->CallObjectMethod(
			g_globalThiz,
			g_getAppLocalValue,
			keyName
		);

		jniEnv->DeleteLocalRef(keyName);

		if (keyValue)
		{
			const char* keyValueStr = jniEnv->GetStringUTFChars(keyValue, NULL);
			strncpy(CPluginLoader::ms_StorageRootDirectory, keyValueStr, _countof(CPluginLoader::ms_StorageRootDirectory));
			jniEnv->ReleaseStringUTFChars(keyValue, keyValueStr);
		}

		// STORAGE_ROOT_BASE
		keyName = jniEnv->NewStringUTF("STORAGE_ROOT_BASE");
		keyValue = (jstring)jniEnv->CallObjectMethod(
			g_globalThiz,
			g_getAppLocalValue,
			keyName
		);

		jniEnv->DeleteLocalRef(keyName);

		if (keyValue)
		{
			const char* keyValueStr = jniEnv->GetStringUTFChars(keyValue, NULL);
			strncpy(CPluginLoader::ms_StorageRootBaseDirectory, keyValueStr, _countof(CPluginLoader::ms_StorageRootBaseDirectory));
			jniEnv->ReleaseStringUTFChars(keyValue, keyValueStr);
		}

		bPathsInitialized = true;
	}
	
	// default
	if (jniEnv->ExceptionCheck())
		jniEnv->ExceptionClear();

	if (!bPathsInitialized)
	{
		GetExternalStorageDirectory(jniEnv, CPluginLoader::ms_StorageRootBaseDirectory, sizeof(CPluginLoader::ms_StorageRootBaseDirectory));
		GetExternalFilesDirectory(jniEnv, mainActivity, CPluginLoader::ms_StorageRootDirectory, sizeof(CPluginLoader::ms_StorageRootDirectory));
	}

	// Plugin directory
	sprintf(this->ms_PluginDirectory, "%s/f92plugins/%s", this->ms_StorageRootDirectory, this->pTargetArchABI);

}

// Does application initialization stage
void CPluginLoader::DoAppInitializationStage(JNIEnv* jniEnv, jobject mainActivity)
{
	this->jniEnv = jniEnv;
	ms_mainActivityDuringLaunch = mainActivity;

	//////
	GetPackageName(jniEnv,
		mainActivity,
		CPluginLoader::ms_packageName,
		sizeof(CPluginLoader::ms_packageName)
	);

	// CPluginLoader::ms_originalPackageName
	bool bReadFromF92launcher = false;
	jfieldID fieldIDoriginalPackageName;

	jclass classF92launcherSettings = jniEnv->FindClass("com/fastman92/main_activity_launcher/Settings");

	if (classF92launcherSettings)
	{
		fieldIDoriginalPackageName = jniEnv->GetStaticFieldID(classF92launcherSettings, "originalPackageName", "Ljava/lang/String;");

		if (fieldIDoriginalPackageName)
		{
			jstring packageName = (jstring)jniEnv->GetStaticObjectField(classF92launcherSettings, fieldIDoriginalPackageName);

			if (packageName)
			{
				const char* packageNameStr = jniEnv->GetStringUTFChars(packageName, NULL);

				strncpy(CPluginLoader::ms_originalPackageName, packageNameStr, sizeof(CPluginLoader::ms_originalPackageName));

				jniEnv->ReleaseStringUTFChars(packageName, packageNameStr);

				bReadFromF92launcher = true;
			}
		}
	}

	if (!bReadFromF92launcher)
	{
		if (jniEnv->ExceptionCheck())
			jniEnv->ExceptionClear();

		strcpy(CPluginLoader::ms_originalPackageName, CPluginLoader::ms_packageName);
	}
	//////

	GetCacheDirectory(jniEnv,
		mainActivity,
		CPluginLoader::ms_CacheDirectory,
		sizeof(CPluginLoader::ms_CacheDirectory)
	);

	/////////////
	
	try
	{
		CPluginLoader::InitialiseDirectoryPaths(jniEnv, mainActivity);

		getcwd(CPluginLoader::ms_InitialDirectory, sizeof(CPluginLoader::ms_InitialDirectory));

		////
		OutputFormattedDebugString(
			"Root base directory: %s Root directory: %s Initial directory: %s",
			CPluginLoader::ms_StorageRootBaseDirectory,
			CPluginLoader::ms_StorageRootDirectory,
			CPluginLoader::ms_InitialDirectory
		);

		{
			struct stat st;

			// Create root directory if it does not exist (GTA LCS mostly)
			if (stat(this->ms_StorageRootDirectory, &st) != 0 || !(st.st_mode & S_IFDIR))
			{
				int mkdir_result = mkdir_p(CPluginLoader::ms_StorageRootDirectory, 0771);

				if (mkdir_result != 0)
					throw f92_runtime_error("An error while creating storage root directory.");
				else
					OutputFormattedDebugString("Created storage directory");
			}

			// Create plugin directory if it does not exist
			if (stat(this->ms_PluginDirectory, &st) != 0 || !(st.st_mode & S_IFDIR))
			{
				int mkdir_result = mkdir_p(this->ms_PluginDirectory, 0771);

				if (mkdir_result != 0)
					throw f92_runtime_error("An error while creating plugin directory.");
				else
					OutputFormattedDebugString("Created plugin directory");
			}
		}

		// Set current working directory
		if (!SetCurrentWorkingDirectory_OS_independent(CPluginLoader::ms_StorageRootDirectory))
			throw f92_runtime_error("An error while setting the current working directory to game root directory.");

		// Load plugins
		this->LoadPlugins();
	}
	catch (f92_runtime_error& e)
	{
		OutputFormattedDebugString("%s", e.what());
		return;
	}
}

CPluginLoader g_Loader;
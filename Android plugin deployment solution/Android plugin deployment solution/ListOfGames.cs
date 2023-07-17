using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace Android_plugin_deployment_solution
{
    public class PlatformDescription
    {
        public string name;
        public string platformABI;
        public string dexOptLibDir;
        public string IDAdebugServerName;
        public int IDAdebugServerPort;

        public PlatformDescription(string name, string platformABI, string dexOptLibDir, string IDAdebugServerName, int IDAdebugServerPort)
        {
            this.name = name;
            this.platformABI = platformABI;
            this.dexOptLibDir = dexOptLibDir;
            this.IDAdebugServerName = IDAdebugServerName;
            this.IDAdebugServerPort = IDAdebugServerPort;
        }
    }


    public static class ListOfPlatforms
    {
        public const int debuggingPortBase = 23946;

        public static PlatformDescription[] PlatformDescriptionArray = new PlatformDescription[] {
            new PlatformDescription("ANDROID_ARMEABI", "armeabi", "arm", "android_server", debuggingPortBase),
            new PlatformDescription("ANDROID_ARMEABI_V7A", "armeabi-v7a", "arm", "android_server", debuggingPortBase),
            new PlatformDescription("ANDROID_ARM64_V8A", "arm64-v8a", "arm64", "android_server64", debuggingPortBase + 1),

            new PlatformDescription("ANDROID_X86", "x86", "x86", "android_x86_server", debuggingPortBase + 2),
            new PlatformDescription("ANDROID_X64", "x86_64", "x64", "android_x64_server",debuggingPortBase + 3)
        };
    }

    public class GameVersionDescription
    {
        public string name;
        public string packageName;
        public string identifierFourCCdeprecated;
        public string identifier;
        public string libraryFilename;
        public string platformName;
        public bool bCLEOavailable;
        public bool bPubliclyAvailable; // plugin loader working?
        public bool bFLAavailable;  // FLA working?
        public string[] OBB_list;

        public GameVersionDescription(
            string name,
            string packageName,
            string identifierFourCCdeprecated,
            string identifier,
            string libraryFilename,
            string platformName,
            bool bCLEOavailable,
            bool bPubliclyAvailable,
            bool bFLAavailable,
            string[] OBB_list
            )
        {
            this.name = name;
            this.packageName = packageName;
            this.identifier = identifier;
            this.identifierFourCCdeprecated = identifierFourCCdeprecated;
            this.libraryFilename = libraryFilename;
            this.platformName = platformName;
            this.bCLEOavailable = bCLEOavailable;
            this.bPubliclyAvailable = bPubliclyAvailable;
            this.bFLAavailable = bFLAavailable;
            this.OBB_list = OBB_list;
        }
    }

    public class GameDescription
    {
        public string gameName;
        public string activityName;
        public string remoteFilesSubDirectory;
        public string devIniFilename;
        public GameVersionDescription[] supportedVersions;

        public GameDescription(
            string directory,   // game name            
            string activityName,
            string remoteFilesSubDirectory,
            string devIniFilename,
            GameVersionDescription[] supportedVersions
            )
        {
            this.gameName = directory;
            this.activityName = activityName;
            this.remoteFilesSubDirectory = remoteFilesSubDirectory;
            this.devIniFilename = devIniFilename;

            if (supportedVersions != null)
                this.supportedVersions = supportedVersions;
            else
                this.supportedVersions = new GameVersionDescription[] { };
        }
    }

    public static class ListOfGames
    {
        public static string[] OBB_GTA_III = {
            "main.5.com.rockstar.gta3.obb"
        };

        public static string[] OBB_GTA_VC = {
            "main.11.com.rockstargames.gtavc.obb"
        };

        public static string[] OBB_GTA_SA = {
            "main.8.com.rockstargames.gtasa.obb",
            "patch.8.com.rockstargames.gtasa.obb"
        };

        public static string[] OBB_GTA_SA_GER = {
            "main.6.com.rockstargames.gtasager.obb",
            "patch.6.com.rockstargames.gtasager.obb"
        };

        public static string[] OBB_GTA_LCS = {
            "main.17.com.rockstargames.gtalcs.obb",
            "patch.15.com.rockstargames.gtalcs.obb"
        };

        public static string[] OBB_GTA_CTW = {
            "main.4.com.rockstargames.gtactw.obb"
        };

        public static string[] OBB_BullySE = {
            "main.11.com.rockstargames.bully.obb",
            "patch.11.com.rockstargames.bully.obb"
        };

        public static GameDescription[] GameDescriptionArray = new GameDescription[] {
             new GameDescription(
                "Bully Scholarship Edition",        
                ".bully",
                "",
                "fastman92limitAdjuster_BullyScholarship_dev.ini",
                new GameVersionDescription[]
                {
                    new GameVersionDescription(
                        "1.0.0.18",  // name
                        "com.rockstargames.bully",  // packageName
                        "BL18", // identifierFourCCdeprecated
                        "Bully_AE|1.0.0.18", // identifier
                        "libBully.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        false,  // bCLEOavailable
                        true,  // bPubliclyAvailable
                        true,  // bFLAavailable
                        OBB_BullySE
                        )
                }

                ),

            new GameDescription(
                "GTA III",
                
                ".GTA3",
                "GTA3",
                "fastman92limitAdjuster_GTAIII_dev.ini",
                new GameVersionDescription[]
                {
                    new GameVersionDescription(
                        "1.0",  // name
                        "com.rockstar.gta3",    // packageName
                        "G_10", // identifierFourCCdeprecated
                        "GTA_III|1.0",  // identifier
                        "libNative.so", // libraryFilename
                        "ANDROID_ARMEABI",    // platformName
                        false,  // bCLEOavailable
                        false,  // bPubliclyAvailable
                        false,  // bFLAavailable
                        OBB_GTA_III
                        ),
                    new GameVersionDescription(
                        "1.6",  // name
                        "com.rockstar.gta3",    // packageName
                        "G_16", // identifierFourCCdeprecated
                        "GTA_III|1.6",  // identifier
                        "libR1.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        true,     // bCLEOavailable
                        false,  // bPubliclyAvailable
                        false,  // bFLAavailable
                        OBB_GTA_III
                        ),
                    new GameVersionDescription(
                        "1.8",  // name
                        "com.rockstar.gta3",    // packageName
                        "G_18", // identifierFourCCdeprecated
                        "GTA_III|1.8",  // identifier
                        "libR1.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        true,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        true,     // bFLAavailable
                        OBB_GTA_III
                        ),
                    new GameVersionDescription(
                        "1.9",  // name
                        "com.rockstar.gta3",    // packageName
                        "G_19", // identifierFourCCdeprecated
                        "GTA_III|1.9",  // name
                        "libR1.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        false,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        false,     // bFLAavailable
                        OBB_GTA_III
                        ),
                    new GameVersionDescription(
                        "1.9",  // name
                        "com.rockstar.gta3",    // packageName
                        "GX19", // identifierFourCCdeprecated
                        "GTA_III|1.9",  // name
                        "libR1.so", // libraryFilename
                        "ANDROID_ARM64_V8A",    // platformName
                        false,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        false,     // bFLAavailable
                        OBB_GTA_III
                        )
                }
                ),

            new GameDescription(
                "GTA Vice City",
                ".GTAVC",
                "",
                "fastman92limitAdjuster_GTAVC_dev.ini",
                new GameVersionDescription[]
                {
                    new GameVersionDescription(
                        "1.09", // name
                        "com.rockstargames.gtavc",  // packageName
                        "VC19", // identifierFourCCdeprecated
                        "GTA_VC|1.09", // identifier
                        "libGTAVC.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        true,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        true,     // bFLAavailable
                        OBB_GTA_VC
                        ),

                    new GameVersionDescription(
                        "1.10", // name
                        "com.rockstargames.gtavc",  // packageName
                        "VC19", // identifierFourCCdeprecated
                        "GTA_VC|1.10", // identifier
                        "libGTAVC.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        false,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        false,     // bFLAavailable
                        OBB_GTA_VC
                        ),

                    new GameVersionDescription(
                        "1.10", // name
                        "com.rockstargames.gtavc",  // packageName
                        "VC19", // identifierFourCCdeprecated
                        "GTA_VC|1.10", // identifier
                        "libGTAVC.so", // libraryFilename
                        "ANDROID_ARM64_V8A",    // platformName
                        false,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        false,     // bFLAavailable
                        OBB_GTA_VC
                        ),

                    new GameVersionDescription(
                        "1.12", // name
                        "com.rockstargames.gtavc",  // packageName
                        "VC19", // identifierFourCCdeprecated
                        "GTA_VC|1.12", // identifier
                        "libGTAVC.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        false,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        false,     // bFLAavailable
                        OBB_GTA_VC
                        ),

                    new GameVersionDescription(
                        "1.12", // name
                        "com.rockstargames.gtavc",  // packageName
                        "VC19", // identifierFourCCdeprecated
                        "GTA_VC|1.12", // identifier
                        "libGTAVC.so", // libraryFilename
                        "ANDROID_ARM64_V8A",    // platformName
                        false,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        false,     // bFLAavailable
                        OBB_GTA_VC
                        )
                }
                ),

            new GameDescription(
                "GTA San Andreas",
                ".GTASA",
                "",
                "fastman92limitAdjuster_GTASA_dev.ini",
                new GameVersionDescription[]
                {
                    new GameVersionDescription(
                        "1.08", // name
                        "com.rockstargames.gtasa", // packagName
                        "SA18", // identifierFourCCdeprecated
                        "GTA_SA|1.08", // identifier
                        "libGTASA.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        true,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        true,     // bFLAavailable
                        OBB_GTA_SA
                        ),
                    
                     new GameVersionDescription(
                        "1.08 SAMP", // name
                        "com.rockstargames.gtasa_1_08_samp", // packageName
                        "SA18", // identifierFourCCdeprecated
                        "GTA_SA|1.08", // identifier
                        "libGTASA.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        true,     // bCLEOavailable
                        false,     // bPubliclyAvailable
                        true,      // bFLAavailable
                        OBB_GTA_SA
                        ),

                      new GameVersionDescription(
                        "2.09 German",  // name
                        "com.rockstargames.gtasager", // packageName
                        "SG29", // identifierFourCCdeprecated
                        "GTA_SA_GER|2.09",   // identifier
                        "libGTASA.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        true,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        true,     // bFLAavailable
                        OBB_GTA_SA_GER
                        ),

                    new GameVersionDescription(
                        "2.00",  // name
                        "com.rockstargames.gtasa", // packageName
                        "SA20", // identifierFourCCdeprecated
                        "GTA_SA|2.00",  // identifier
                        "libGTASA.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        true,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        true,     // bFLAavailable
                        OBB_GTA_SA
                        ),

                    new GameVersionDescription(
                        "2.10",  // name
                        "com.rockstargames.gtasa", // packageName
                        null, // identifierFourCCdeprecated
                        "GTA_SA|2.10",  // identifier
                        "libGTASA.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        false,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        true,     // bFLAavailable
                        OBB_GTA_SA
                        ),

                    new GameVersionDescription(
                        "2.10",  // name
                        "com.rockstargames.gtasa", // packageName
                        null, // identifierFourCCdeprecated
                        "GTA_SA|2.10",  // identifier
                        "libGTASA.so", // libraryFilename
                        "ANDROID_ARM64_V8A",    // platformName
                        false,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        true,     // bFLAavailable
                        OBB_GTA_SA
                        ),

                    new GameVersionDescription(
                        "2.11.32",  // name
                        "com.rockstargames.gtasa", // packageName
                        null, // identifierFourCCdeprecated
                        "GTA_SA|2.11.32",  // identifier
                        "libGame.so", // libraryFilename
                        "ANDROID_ARM64_V8A",    // platformName
                        false,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        true,     // bFLAavailable
                        OBB_GTA_SA
                        ),

                }  

                ),

            new GameDescription(
                "GTA Liberty City Stories",
                ".BootGameActivity",
                "",
                "fastman92limitAdjuster_GTALCS_dev.ini",
                new GameVersionDescription[]
                {
                    new GameVersionDescription(
                        "2.4",  // name
                        "com.rockstargames.gtalcs", // packageName
                        "LC24", // identifierFourCCdeprecated
                        "GTA_LCS|2.4",  // identifier
                        "libGTALcs.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        true,     // bCLEOavailable
                        true,     // bPubliclyAvailable
                        true,     // bFLAavailable
                        OBB_GTA_LCS
                        )
                }
                ),

            new GameDescription(
                "GTA Chinatown Wars",
                ".BootGameActivity",
                "",
                "fastman92limitAdjuster_GTACTW_dev.ini",
                new GameVersionDescription[]
                {
                    new GameVersionDescription(
                        "1.04",  // name
                        "com.rockstargames.gtactw", // packageName
                        "CT14", // identifierFourCCdeprecated
                        "GTA_CTW|1.04", // identifier
                        "libCTW.so", // libraryFilename
                        "ANDROID_ARMEABI_V7A",    // platformName
                        false,    // bCLEOavailable
                        true,     // bPubliclyAvailable
                        true,     // bFLAavailable
                        OBB_GTA_CTW
                        )
                }
                )
        };
   };
}

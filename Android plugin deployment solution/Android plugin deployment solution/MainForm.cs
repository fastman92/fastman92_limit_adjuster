using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;
using System.Threading;

using IniParser;
using IniParser.Model;

namespace Android_plugin_deployment_solution
{
    enum eVersionToRun
    {
        VERSION_TO_RUN_NONE,
        VERSION_TO_RUN_DEBUG,
        VERSION_TO_RUN_RELEASE
    };

    // [DllImport("kernel32.dll")]
    // static extern bool AttachConsole(int dwProcessId);

    public partial class MainForm : Form
    {
        public string ScriptContent;

        // Game and game version
        List<GameDescription> GameDescriptionArray = new List<GameDescription>();

        public GameDescription gameDescription = null;
        public GameVersionDescription gameVersionDescription = null;
        public PlatformDescription platformDescription;

        // Android device hostname
        public string AndroidDeviceHostname = "my_device";

        ////////////// Paths //////////////
        private string devPath;

        public string adbEXEpath = "adb";

        private string PluginLoaderInstallerPath;
        private string fastman92DebugOutputPath;
        private string fastman92DebugOutputAdditionalStrings = String.Empty;

        public string Android_dir = "Android"; // "Android_unprotected";

        public string releaseOrDebugDirectory;
        public string CLEOdirectoryPath;

        public string tempDirectory;
        public string toolsDirectory;
        private string screenshotDirectory;

        // working directory
        private string WorkingDirectoryPath;

        // for current game
        public string PackageNameToRun;
        public string AndroidDATAdirectory;
        private string UserDirectoryForCurrentGame;
        private string UserDirectoryForCurrentGameAccessFromComputer;

        public string FilesDirectoryForCurrentGame;
        public string FilesDirectoryForCurrentGameArchitectureSpecific;
        public string ApplicationDirectoryOnAndroidDevice;

        //////////////////////////////////

        // enable developer options?
        private bool bEnableDeveloperOptions;

        // exit script immediately
        private bool bHasExitScriptImmediatelyEverBeenSet = false;

        // Declare our worker thread
        private Thread workerThread = null;

        public MainForm()
        {
            InitializeComponent();
        }

        private Process CreateCmdProcess()
        {
            Process p = new Process();

            // set start info
            p.StartInfo = new ProcessStartInfo("cmd.exe")
            {
                RedirectStandardInput = true,
                // RedirectStandardOutput = true,
                UseShellExecute = false
            };
            // event handlers for output & error
            // p.BeginOutputReadLine();
            p.OutputDataReceived += p_OutputDataReceived;
            p.ErrorDataReceived += p_ErrorDataReceived;

            return p;
        }

        private void fastman92_logcat_button_Click(object sender, EventArgs e)
        {
            /*
            try
            {
                using (Process p = this.CreateCmdProcess())
                {
                    // start process
                    p.Start();

                    // send command to its input
                    p.StandardInput.WriteLine("\"" + this.adbEXEpath + "\"" + " logcat -c");
                    p.StandardInput.WriteLine("(" + "\"" + this.adbEXEpath + "\"" + " logcat & echo fastman92 debug end of output!) | " + "\"" + this.fastman92DebugOutputPath + "\" \"\"");
                    p.StandardInput.WriteLine("pause");
                }
            }
            catch (Exception) { }
            */

            this.ScriptContent = String.Empty;

            // this.ScriptContent += "@echo off" + Environment.NewLine;
            this.ScriptContent += ":loop" + Environment.NewLine;

            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " logcat -c" + Environment.NewLine;

            // this.ScriptContent += "cls" + Environment.NewLine;

            this.ScriptContent += "(" + "\"" + this.adbEXEpath + "\"" + " logcat & echo fastman92 debug end of output!) | " + "\""
                + this.fastman92DebugOutputPath + "\" " + this.fastman92DebugOutputAdditionalStrings + Environment.NewLine;

            this.ScriptContent += "echo." + Environment.NewLine;

            this.ScriptContent += "goto loop" + Environment.NewLine;
            
            this.RunScript();
        }

        static void p_ErrorDataReceived(object sender, DataReceivedEventArgs e)
        {
            Process p = sender as Process;
            if (p == null)
                return;
            Console.WriteLine(e.Data);
        }

        static void p_OutputDataReceived(object sender, DataReceivedEventArgs e)
        {
            Process p = sender as Process;
            if (p == null)
                return;
            Console.WriteLine(e.Data);
        }

        private void RefreshInformations()
        {
            string informations = String.Empty;

            informations += "Path to plugin loader installer EXE: "
                + this.PluginLoaderInstallerPath;

            informations += Environment.NewLine + "Path to fastman92 output EXE: " + this.fastman92DebugOutputPath;

            informations += Environment.NewLine + Environment.NewLine + "Path to the libraries: " + this.releaseOrDebugDirectory;

            informations += Environment.NewLine + Environment.NewLine + "Package name: " + this.PackageNameToRun;

            if (this.gameVersionDescription != null)
                informations += ", application library name: " + this.gameVersionDescription.libraryFilename;

            informations += Environment.NewLine + "Directory for current game on COMPUTER: " + this.FilesDirectoryForCurrentGame;
            informations += Environment.NewLine + "Internal directory for current game on ANDROID device: " + this.ApplicationDirectoryOnAndroidDevice;
            informations += Environment.NewLine + "External file directory for current game on ANDROID device: " + this.UserDirectoryForCurrentGame;

            this.InformationTextBox.Text = informations;

            if (this.platformDescription != null)
                this.PortLabel.Text = "Port " + this.platformDescription.IDAdebugServerPort;
            else
                this.PortLabel.Text = "Port undefined";

        }

        private void SetReleaseOrDebugDirectory()
        {
            if (this.gameVersionComboBox.SelectedIndex >= 0)
            {
                GameDescription gameDescription = GameDescriptionArray[this.gameComboBox.SelectedIndex];
                GameVersionDescription versionDescription = gameDescription.supportedVersions[this.gameVersionComboBox.SelectedIndex];

                if (!string.IsNullOrEmpty(devPath))
                {
                    this.releaseOrDebugDirectory = devPath + "\\fastman92 limit adjuster\\Output";

                    if (useDebugLibraryCheckBox.Checked)
                        this.releaseOrDebugDirectory += "\\Debug";
                    else
                        this.releaseOrDebugDirectory += "\\Release";

                    this.releaseOrDebugDirectory += "\\" + versionDescription.platformName;

                    // CLEO directory
                    if (versionDescription.platformName == "ANDROID_ARMEABI_V7A")
                        this.CLEOdirectoryPath = devPath + "\\Neccessary files\\LibCleo for ANDROID_ARMEABI_V7A games\\04 Apr 2021";
                    else
                        this.CLEOdirectoryPath = String.Empty;
                }
                else
                {
                    this.releaseOrDebugDirectory = this.WorkingDirectoryPath
                     + "\\files\\libraries\\ANDROID\\" + platformDescription.platformABI;

                    this.CLEOdirectoryPath = this.releaseOrDebugDirectory;
                }
            }
            else
            {
                this.releaseOrDebugDirectory = String.Empty;
                this.CLEOdirectoryPath = String.Empty;
            }
        }

        // Sets paths for current game version
        private void SetPathsForCurrentGameVersion()
        {
            // Set package name
            if (gameVersionDescription != null)
            {
                this.PackageNameToRun = gameVersionDescription.packageName;
                this.AndroidDATAdirectory = gameVersionDescription.packageName;

                if (this.developmentPackageNamesCheckbox.Checked)
                {
                    if (this.PackageNameToRun == "com.rockstargames.bully" && gameVersionDescription.name == "1.0.0.18")
                        this.PackageNameToRun = "com.rockstargames.bully_1_0_0_18";
                    else if (this.PackageNameToRun == "com.rockstar.gta3" && gameVersionDescription.name == "1.6")
                        this.PackageNameToRun = "com.rockstar.gta3_ver_1_6";
                    else if (this.PackageNameToRun == "com.rockstar.gta3" && gameVersionDescription.name == "1.8")
                        this.PackageNameToRun = "com.rockstar.gta3_ver_1_8";
                    else if (this.PackageNameToRun == "com.rockstar.gta3" && gameVersionDescription.name == "1.9" && gameVersionDescription.platformName == "ANDROID_ARMEABI_V7A")
                        this.PackageNameToRun = "com.rockstar.gta3_ver_1_9_arm32";

                    else if (this.PackageNameToRun == "com.rockstar.gta3" && gameVersionDescription.name == "1.9" && gameVersionDescription.platformName == "ANDROID_ARM64_V8A")
                        this.PackageNameToRun = "com.rockstar.gta3_ver_1_9_arm64";
                    else if (this.PackageNameToRun == "com.rockstargames.gtavc" && gameVersionDescription.name == "1.09")
                        this.PackageNameToRun = "com.rockstargames.gtavc_1_09";

                    else if (this.PackageNameToRun == "com.rockstargames.gtavc" && gameVersionDescription.name == "1.10" && gameVersionDescription.platformName == "ANDROID_ARMEABI_V7A")
                        this.PackageNameToRun = "com.rockstargames.gtavc_1_10_arm32";
                    else if (this.PackageNameToRun == "com.rockstargames.gtavc" && gameVersionDescription.name == "1.10" && gameVersionDescription.platformName == "ANDROID_ARM64_V8A")
                        this.PackageNameToRun = "com.rockstargames.gtavc_1_10_arm64";

                    else if (this.PackageNameToRun == "com.rockstargames.gtavc" && gameVersionDescription.name == "1.12" && gameVersionDescription.platformName == "ANDROID_ARMEABI_V7A")
                        this.PackageNameToRun = "com.rockstargames.gtavc_1_12_arm32";
                    else if (this.PackageNameToRun == "com.rockstargames.gtavc" && gameVersionDescription.name == "1.12" && gameVersionDescription.platformName == "ANDROID_ARM64_V8A")
                        this.PackageNameToRun = "com.rockstargames.gtavc_1_12_arm64";

                    else if (this.PackageNameToRun == "com.rockstargames.gtasa" && gameVersionDescription.name == "1.08")
                        this.PackageNameToRun = "com.rockstargames.gtasa_1_08";
                    else if (this.PackageNameToRun == "com.rockstargames.gtasa" && gameVersionDescription.name == "2.00")
                        this.PackageNameToRun = "com.rockstargames.gtasa_2_0";
                    else if (this.PackageNameToRun == "com.rockstargames.gtasager" && gameVersionDescription.name == "2.09 German")
                    {
                        this.PackageNameToRun = "com.rockstargames.gtasager_2_09";
                        this.AndroidDATAdirectory = "com.rockstargames.gtasa_2_0";
                    }

                    else if (this.PackageNameToRun == "com.rockstargames.gtasa" && gameVersionDescription.name == "2.10" && gameVersionDescription.platformName == "ANDROID_ARMEABI_V7A")
                        this.PackageNameToRun = "com.rockstargames.gtasa_2_10_arm32";
                    else if (this.PackageNameToRun == "com.rockstargames.gtasa" && gameVersionDescription.name == "2.10" && gameVersionDescription.platformName == "ANDROID_ARM64_V8A")
                        this.PackageNameToRun = "com.rockstargames.gtasa_2_10_arm64";

                    else if (this.PackageNameToRun == "com.rockstargames.gtalcs" && gameVersionDescription.name == "2.4")
                        this.PackageNameToRun = "com.rockstargames.gtalcs_2_4";
                    else if (this.PackageNameToRun == "com.rockstargames.gtactw" && gameVersionDescription.name == "1.04")
                        this.PackageNameToRun = "com.rockstargames.gtactw_1_04";
                }

                
            }

            // Files directory for current game
            if (gameVersionDescription != null)
            {
                FilesDirectoryForCurrentGame = this.WorkingDirectoryPath
                    + "\\deployment\\" + gameDescription.gameName + "\\" + gameVersionDescription.name;
                FilesDirectoryForCurrentGameArchitectureSpecific = FilesDirectoryForCurrentGame + Path.DirectorySeparatorChar + gameVersionDescription.platformName;
            }
            else
            {
                FilesDirectoryForCurrentGame = String.Empty;
                FilesDirectoryForCurrentGameArchitectureSpecific = String.Empty;
            }

            // External directory
            if (gameVersionDescription != null)
            {
                UserDirectoryForCurrentGame = "/sdcard/" + Android_dir + "/data/"
                    + this.AndroidDATAdirectory + "/files";

                if (!string.IsNullOrEmpty(gameDescription.remoteFilesSubDirectory))
                    UserDirectoryForCurrentGame += "/" + gameDescription.remoteFilesSubDirectory;

                ///////////////
                UserDirectoryForCurrentGameAccessFromComputer = "\\\\" + this.AndroidDeviceHostname + "\\Root\\sdcard\\" + Android_dir + "\\data\\"
                    + this.AndroidDATAdirectory + "\\files";

                if (!string.IsNullOrEmpty(gameDescription.remoteFilesSubDirectory))
                    UserDirectoryForCurrentGameAccessFromComputer += "\\" + gameDescription.remoteFilesSubDirectory;
            }
            else
            {
                UserDirectoryForCurrentGame = String.Empty;
                UserDirectoryForCurrentGameAccessFromComputer = String.Empty;
            }

            ApplicationDirectoryOnAndroidDevice = "/data/data/" + PackageNameToRun;

            this.SetReleaseOrDebugDirectory();
        }

        private void DeleteUnneccessaryFiles()
        {
            try
            {
                Directory.Delete(@"\\?\" + this.tempDirectory, true);
            }
            catch (Exception) { }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Set the title
            this.Text = "Android plugin deployment solution for the FLA " + fastman92_limit_adjuster.version;
            this.FLAinformationLabel.Text = "Built for fastman92 limit adjuster " + fastman92_limit_adjuster.version;

            //////////////
            this.tempDirectory = Application.StartupPath + "\\tmp";
            this.toolsDirectory = Application.StartupPath + "\\tools";
            this.screenshotDirectory = Application.StartupPath + "\\screenshots";

            this.DeleteUnneccessaryFiles();

            ///////////////
            // Set up the development path
            {
                string[] args = Environment.GetCommandLineArgs();

                if (!File.Exists(Application.StartupPath + Path.DirectorySeparatorChar + "FILES_DIRECTORY")
               &&
               !(args.Length >= 2 && args[1] == "/no_development_options")
               )
                    this.devPath = Environment.GetEnvironmentVariable("FASTMAN92_LIMIT_ADJUSTER_DEVELOPMENT_PATH");
                else
                    this.devPath = String.Empty;
            }

            this.bEnableDeveloperOptions = !string.IsNullOrEmpty(devPath);

            this.enableDeveloperOptionsButton.Enabled = !this.bEnableDeveloperOptions;

            this.useDebugLibraryCheckBox.Enabled = !string.IsNullOrEmpty(devPath);

            this.exitImmediatelyCheckBox.Checked = !string.IsNullOrEmpty(devPath);

            this.bHasExitScriptImmediatelyEverBeenSet = false;

            this.apkUsingAndroidUnprotected.Checked = !string.IsNullOrEmpty(devPath);
            // this.apkUsingAndroidUnprotected.Checked = !string.IsNullOrEmpty(devPath);

            this.developmentPackageNamesCheckbox.Checked = !string.IsNullOrEmpty(devPath);

            this.SetOtherButtons();

            // Read configuration
            {
                var parser = new FileIniDataParser();
                IniData data = parser.ReadFile("AndroidPluginDeploymentSolution_configuration.ini");

                ////
                string valueFromINI = data["MAIN"]["Android device hostname"];

                if (!string.IsNullOrEmpty(devPath))
                    this.AndroidDeviceHostname = "pocox3pro";
                else if (!String.IsNullOrEmpty(valueFromINI))
                    this.AndroidDeviceHostname = valueFromINI;
                else
                    this.AndroidDeviceHostname = "my_device";

                ////
                valueFromINI = data["MAIN"]["Path to ADB executable"];

                if (!string.IsNullOrEmpty(devPath) || String.IsNullOrEmpty(valueFromINI))
                    this.adbEXEpath = "adb.exe";
                else
                    this.adbEXEpath = valueFromINI;

                ////
                valueFromINI = data["MAIN"]["Monitor debug output additional strings"];

                if (!string.IsNullOrEmpty(valueFromINI))
                    this.fastman92DebugOutputAdditionalStrings = valueFromINI;
                else
                    this.fastman92DebugOutputAdditionalStrings = String.Empty;

                parser = null;
            }

            ///// List of games
            GameDescriptionArray.Clear();

            foreach (GameDescription testedGameDescription in ListOfGames.GameDescriptionArray)
            {
                // Is application running on author's computer?
                if (!String.IsNullOrEmpty(this.devPath))
                    GameDescriptionArray.Add(testedGameDescription);
                else
                {
                    int numberOfSupportedVersions = 0;

                    // Count the numbers of versions publicly available
                    foreach (GameVersionDescription testedVersionDescription in testedGameDescription.supportedVersions)
                    {
                        if (testedVersionDescription.bPubliclyAvailable)
                            numberOfSupportedVersions++;
                    }

                    // Copy these versions
                    if (numberOfSupportedVersions != 0)
                    {
                        GameVersionDescription[] publicSupportedVersions = new GameVersionDescription[numberOfSupportedVersions];

                        byte versionIndex = 0;

                        foreach (GameVersionDescription testedVersionDescription in testedGameDescription.supportedVersions)
                        {
                            if (testedVersionDescription.bPubliclyAvailable)
                                publicSupportedVersions[versionIndex++] = testedVersionDescription;
                        }

                        GameDescription publicGameDescription =
                            new GameDescription(
                                    testedGameDescription.gameName,   // game name
                                    testedGameDescription.activityName,
                                    testedGameDescription.remoteFilesSubDirectory,
                                    testedGameDescription.devIniFilename,
                                    publicSupportedVersions
                                );

                        GameDescriptionArray.Add(publicGameDescription);
                    }
                }
            }

            string PluginLoaderInstallerDir;

            // set PluginLoaderInstallerPath
            if (!string.IsNullOrEmpty(devPath))
                PluginLoaderInstallerDir = devPath + "\\Plugin Loader Installer\\Release";
            else
                PluginLoaderInstallerDir = Application.StartupPath;

            this.fastman92DebugOutputPath = PluginLoaderInstallerDir + "\\fastman92debugOutput.exe";
            this.PluginLoaderInstallerPath = PluginLoaderInstallerDir + "\\PluginLoaderInstaller.exe";

            //////////////////////////////////////
            foreach (GameDescription game in GameDescriptionArray)
                this.gameComboBox.Items.Add(game.gameName);

            this.gameComboBox.SelectedIndex = 0;

            this.directoryPathTextBox.Text = System.Environment.CurrentDirectory;

            ////

            {
                //this.gameComboBox.SelectedIndex = 2;
                // this.gameVersionComboBox.SelectedIndex = 1;
            }

            if (!string.IsNullOrEmpty(devPath))
            {
                string filePath = devPath + "\\LoadSettings\\VersionToRun.txt";
                eVersionToRun versionToRun = (eVersionToRun)Int32.Parse(File.ReadAllText(filePath));

                this.useDebugLibraryCheckBox.Checked = versionToRun == eVersionToRun.VERSION_TO_RUN_DEBUG;
            }
        }

        private void Form1_Closed(object sender, FormClosedEventArgs e)
        {
            this.DeleteUnneccessaryFiles();
        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void gameComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.gameVersionComboBox.Items.Clear();

            // fill game version combo box
            if (this.gameComboBox.SelectedIndex >= 0)
            {
                this.gameDescription = GameDescriptionArray[this.gameComboBox.SelectedIndex];

                foreach (GameVersionDescription gameVersion in this.gameDescription.supportedVersions)
                {
                    string str = gameVersion.name + " (" +
                        GetVersionIdentifierStr(gameVersion) + ")";

                    this.gameVersionComboBox.Items.Add(str);
                }

            }
            else
                this.gameDescription = null;

            this.SetButtonsWhichRequireGame();

            this.gameVersionComboBox.ResetText();

            if (this.gameVersionComboBox.Items.Count > 0)
                this.gameVersionComboBox.SelectedIndex = this.gameVersionComboBox.Items.Count - 1;
            else
                this.gameVersionComboBox_SelectedIndexChanged(sender, e);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.openFileDialog1.Dialog.FileName = this.directoryPathTextBox.Text;

            if (this.openFileDialog1.ShowDialog() == DialogResult.OK)
                this.directoryPathTextBox.Text = this.openFileDialog1.SelectedPath;
        }

        private void writeGetPathToLibraryDir()
        {
            this.ScriptContent += "for /f \"delims=\" %%a in ('\"" + this.adbEXEpath + "\"\" \"\"shell dumpsys package " + this.PackageNameToRun + " ^| grep legacyNativeLibraryDir ^| cut -d'=' -f2-\"') do @set NATIVE_LIB_DIR=%%a/" + platformDescription.dexOptLibDir + Environment.NewLine;
        }

        private void writeRunGameCommand(bool bDebugMode = false, bool bWaitForLaunchToComplete = false)
        {
            // this.writeRunGameCommandHelper(false, bDebugMode, bWaitForLaunchToComplete);
            // this.writeRunGameCommandHelper(true, bDebugMode, bWaitForLaunchToComplete);

            this.ScriptContent += "for /f \"delims=\" %%a in ('\"" + this.adbEXEpath + "\"\" \"\"shell cmd package resolve-activity --brief " + this.PackageNameToRun + " ^| tail -n 1\"') do @set TO_START=%%a"
                    + Environment.NewLine;

            string str = "\"" + this.adbEXEpath + "\"" + " shell am start";

            str += " -S";   // force stop the target app before starting the activity

            if (bDebugMode)
                str += " -D";

            if (bWaitForLaunchToComplete)
                str += " -W";

            str += " -n "
                + "%TO_START%";

            // send command to its input
            this.ScriptContent += str + Environment.NewLine;
        }

        private void writeRunGameCommandHelper(bool bUseCustomLauncher, bool bDebugMode = false, bool bWaitForLaunchToComplete = false)
        {
            string str = "\"" + this.adbEXEpath + "\"" + " shell am start";

            str += " -S";   // force stop the target app before starting the activity

            if (bDebugMode)
                str += " -D";

            if (bWaitForLaunchToComplete)
                str += " -W";

            str += " -n "
                + PackageNameToRun + "/";

            // Activity name
            if (bUseCustomLauncher)
                str += "com.fastman92.main_activity_launcher.MainActivity";
            else
            {
                // Write fully qualified activity name if neccessary
                // This is for game versions, where package name is altered on author's device.
                if (!String.IsNullOrEmpty(gameDescription.activityName)
                    && gameDescription.activityName[0] == '.'
                    && gameVersionDescription.packageName != this.PackageNameToRun
                    )
                    str += gameVersionDescription.packageName;

                str += gameDescription.activityName;                
            }

            // send command to its input
            this.ScriptContent += str + Environment.NewLine;
        }

        public void writeEndToCommandPrompt()
        {
            if (!this.exitImmediatelyCheckBox.Checked)
                this.ScriptContent += "pause" + Environment.NewLine;
        }

        private void RunScriptWorkerOperation()
        {
            string batchFilePath = this.tempDirectory + "\\" + DateTime.Now.ToString("hh.mm.ss.ffffff") + ".bat";

            Directory.CreateDirectory(this.tempDirectory);

            try
            {
                File.WriteAllText(batchFilePath,
                    "ping 172.0.1.2 -n 1 -w 200 > nul" + Environment.NewLine +
                    this.ScriptContent
                    );
            }
            catch (Exception)
            {
                MessageBox.Show("Unable to write the script file! Command will not be executed.");
            }

            // MessageBox.Show(this.ScriptContent);

            Process p = new Process();

            // set start info
            p.StartInfo = new ProcessStartInfo("cmd.exe")
            {
                // RedirectStandardInput = true,
                // RedirectStandardOutput = true,
                UseShellExecute = false,
                Arguments = "/c " + "\"" + batchFilePath + "\""
            };
            // event handlers for output & error
            // p.BeginOutputReadLine();
            // p.OutputDataReceived += p_OutputDataReceived;
            // p.ErrorDataReceived += p_ErrorDataReceived;

            p.Start();

            p.WaitForExit();

            try
            {
                File.Delete(batchFilePath);
            }
            catch (Exception) { }
        }

        public void RunScript(bool bAsynchronous = true)
        {
            if (bAsynchronous)
            {
                // Initialise and start worker thread
                this.workerThread = new Thread(new ThreadStart(this.RunScriptWorkerOperation));
                this.workerThread.Start();
            }
            else
                this.RunScriptWorkerOperation();
        }

        private void runGameButton_Click(object sender, EventArgs e)
        {
            this.ScriptContent = String.Empty;

            // this.writeStopGameCommand();
            this.writeRunGameCommand();

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void runGameForDebuggingButton_Click(object sender, EventArgs e)
        {
            this.ScriptContent = String.Empty;

            // this.writeStopGameCommand();
            this.writeRunGameCommand(true);

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void writeStopGameCommand()
        {
            this.ScriptContent += "\"" + this.adbEXEpath + "\" shell am force-stop " + PackageNameToRun + Environment.NewLine;
        }

        private void stopGameButton_Click(object sender, EventArgs e)
        {
            this.ScriptContent = String.Empty;
            this.writeStopGameCommand();

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void startIDAserverButton_Click(object sender, EventArgs e)
        {
            this.ScriptContent = String.Empty;

            string IDAdebugServerName = this.platformDescription.IDAdebugServerName;
            int IDAdebugServerPort = this.platformDescription.IDAdebugServerPort;

            this.ScriptContent += "for /f \"delims=\" %%a in ('\"" + this.adbEXEpath + "\" shell pidof " + IDAdebugServerName + "') do @set pid=%%a"
                + Environment.NewLine;

            this.ScriptContent += "echo PID=%pid%" + Environment.NewLine;

            this.ScriptContent += "IF NOT \"%pid%\" == \"\" (" + Environment.NewLine;

            this.ScriptContent += "echo Killing IDA Server process, whose ID is %pid%" + Environment.NewLine;
            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " shell \"su -c 'kill -9 %pid%'\"" + Environment.NewLine;

            this.ScriptContent += ")" + Environment.NewLine;

            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " shell \"su -c './data/bin/" + IDAdebugServerName + " -p"
                + IDAdebugServerPort + "'\"" + Environment.NewLine;
            this.ScriptContent += "pause";

            this.RunScript();
        }

        private void SetAdditionalFileButtonsEnabledState()
        {
            bool bButtonsEnabled = this.gameComboBox.SelectedIndex >= 0 && this.additionalSOfileTextBox.Text.Length > 0;

            this.updateAdditionalFileButton.Enabled = bButtonsEnabled;
            this.updateAdditionalFileAndRunButton.Enabled = bButtonsEnabled;
            this.deleteAdditionalFileButton.Enabled = bButtonsEnabled;
            this.clearAddtionalFilenameButton.Enabled = bButtonsEnabled;
        }

        private void SetButtonsWhichRequireGame()
        {
            bool bButtonsEnabled = this.gameComboBox.SelectedIndex >= 0;

            this.openExternalDirectoryButton.Enabled = bButtonsEnabled;
            this.externalDirectoryButton.Enabled = bButtonsEnabled;
            this.pullGameLibraryFileToPCbutton.Enabled = bButtonsEnabled;
            this.stopGameButton.Enabled = bButtonsEnabled && this.bEnableDeveloperOptions;
            this.detectGameVersionButton.Enabled = bButtonsEnabled;
            this.updateAdditionalFileButton.Enabled = bButtonsEnabled;
            this.additionalSOfileTextBox.Enabled = bButtonsEnabled;
            this.SetAdditionalFileButtonsEnabledState();
        }

        private void SetButtonsWhichRequireGameVersion()
        {
            bool bButtonsEnabled = this.gameVersionComboBox.SelectedIndex >= 0;

            this.runGameButton.Enabled = bButtonsEnabled;
            this.runGameForDebuggingButton.Enabled = bButtonsEnabled && this.bEnableDeveloperOptions;
            this.runGameForDebuggingAndContinueButton.Enabled = bButtonsEnabled && this.bEnableDeveloperOptions;
            this.forceContinueButton.Enabled = bButtonsEnabled && this.bEnableDeveloperOptions;

            this.startIDAserverButton.Enabled = bButtonsEnabled && this.bEnableDeveloperOptions;
            this.applyPluginLoaderInstallerButton.Enabled = bButtonsEnabled && this.bEnableDeveloperOptions;
            this.updateLibrariesButton.Enabled = bButtonsEnabled;
            this.updateLibrariesAndRunButton.Enabled = bButtonsEnabled && this.bEnableDeveloperOptions;
            this.updateTheFLAandRunButton.Enabled = bButtonsEnabled && this.bEnableDeveloperOptions;
            this.updateTheFLAandRunForDebuggingButton.Enabled = bButtonsEnabled && this.bEnableDeveloperOptions;
            this.updateTheFLAbutton.Enabled = bButtonsEnabled && this.bEnableDeveloperOptions;
            this.createModifiedAPKbutton.Enabled = bButtonsEnabled;
            this.extractGameDataButton.Enabled = false;

            if (!this.gameVersionDescription.bCLEOavailable)
                this.includeLibCLEOcheckBox.Checked = false;

            this.includeTheFLApluginCheckBox.Checked = this.gameVersionDescription.bFLAavailable;
        }

        private void SetOtherButtons()
        {
            this.wakeUpScreenButton.Enabled = this.bEnableDeveloperOptions && !string.IsNullOrEmpty(devPath);

            this.start_strcpy_button.Enabled = this.bEnableDeveloperOptions && !string.IsNullOrEmpty(devPath);
        }

        PlatformDescription GetPlatformDescriptionByName(string platformName)
        {
            // find platform info
            foreach (PlatformDescription platformDescription in ListOfPlatforms.PlatformDescriptionArray)
                if (platformDescription.name == platformName)
                    return platformDescription;

            return null;
        }

        string GetVersionIdentifierStr(GameVersionDescription gameVersion)
        {
            PlatformDescription platformDescription = this.GetPlatformDescriptionByName(gameVersion.platformName);

            return gameVersion.identifier + "|" + platformDescription.platformABI;
        }

    private void gameVersionComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.platformDescription = null;

            if (this.gameVersionComboBox.SelectedIndex >= 0)
            {
                this.gameVersionDescription = this.gameDescription.supportedVersions[this.gameVersionComboBox.SelectedIndex];

                this.platformDescription = this.GetPlatformDescriptionByName(this.gameVersionDescription.platformName);
            }
            else
                this.gameVersionDescription = null;

            this.SetButtonsWhichRequireGameVersion();
            this.SetPathsForCurrentGameVersion();
            this.RefreshInformations();
        }

        // Writes a command to apply plugin loader
        public void writeApplyPluginLoader()
        {
            string libraryFilename = this.gameVersionDescription.libraryFilename;

            string originalLibFile = FilesDirectoryForCurrentGameArchitectureSpecific + "\\original_lib\\" + libraryFilename;
            string modifiedLibFile = FilesDirectoryForCurrentGameArchitectureSpecific + "\\modified_lib\\" + libraryFilename;
            this.EvaluatePath(modifiedLibFile);

            this.ScriptContent += "del /F /S \"" + modifiedLibFile + "\"" + Environment.NewLine;

            /////////

            this.ScriptContent += "\"" + this.PluginLoaderInstallerPath + "\"";

            this.ScriptContent += " /input_filename \"" + originalLibFile + "\"";
            this.ScriptContent += " /output_filename \"" + modifiedLibFile + "\"";
            this.ScriptContent += " /lib_loader_filename \"" + this.GetPluginLoaderFilename() + "\"";
            this.ScriptContent += " /application_loader_identifier \"" + this.GetVersionIdentifierStr(this.gameVersionDescription) + "\"";

            if(!String.IsNullOrEmpty(this.gameVersionDescription.identifierFourCCdeprecated))
                this.ScriptContent += " /application_loader_identifier_deprecated \"" + this.gameVersionDescription.identifierFourCCdeprecated + "\"";

            this.ScriptContent += Environment.NewLine;

            /////////

            this.ScriptContent += "IF NOT EXIST \"" + modifiedLibFile + "\" (" + Environment.NewLine
                + "echo Modified game library has not been generated successfully. Probably because an input original file was invalid." + Environment.NewLine
                + "pause" + Environment.NewLine
                + "exit" + Environment.NewLine
                + ")" + Environment.NewLine;
        }

        private void applyPluginLoaderInstallerButton_Click(object sender, EventArgs e)
        {
            if (!VerifyIfFilesExistForThePurposeOfWritingAllLibraries())
                return;

            this.ScriptContent = String.Empty;

            this.writeApplyPluginLoader();

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        public String EvaluatePath(String path)
        {
            try
            {
                String folder = Path.GetDirectoryName(path);

                if (!Directory.Exists(folder))
                {

                    // Try to create the directory.
                    DirectoryInfo di = Directory.CreateDirectory(folder);

                }
            }
            catch (IOException ioex)
            {
                MessageBox.Show("problem");
                Console.WriteLine(ioex.Message);
                return "";
            }
            return path;
        }

        private void pullGameLibraryFileToPCbutton_Click(object sender, EventArgs e)
        {
            GetOriginalGameLibForm getOriginalGameLib = new GetOriginalGameLibForm(this);
            getOriginalGameLib.ShowDialog();
        }

        private void WriteRemoveFile(string remotePath)
        {
            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " shell \"su -c 'rm " + remotePath + "'\"" + Environment.NewLine;
        }

        private void WriteReplaceLibrary(string localPath, string remotePath, bool TryMkdir = false)
        {
            var pos = remotePath.LastIndexOf('/');
            
            string remoteDirectory = remotePath.Substring(0, pos);

            // Let's check if it will help to resolve the problem of native libraries being restored by Android.
            string owner = "root";  // default: system
            string permission = "555";  // default: 755

            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " shell \"su -c 'rm /data/local/tmp/update.so'\"" + Environment.NewLine;
            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " shell \"su -c 'rm " + remotePath + "'\"" + Environment.NewLine;
            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " push -p \"" + localPath + "\" \"/data/local/tmp/update.so\"" + Environment.NewLine;
            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " shell \"su -c 'chmod " + permission + " /data/local/tmp/update.so'\"" + Environment.NewLine;
            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " shell \"su -c 'chown " + owner + " /data/local/tmp/update.so'\"" + Environment.NewLine;
            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " shell \"su -c 'chown :" + owner + " /data/local/tmp/update.so'\"" + Environment.NewLine;

            if(TryMkdir)
                this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " shell \"su -c 'mkdir -p `dirname " + remotePath + "`'\"" + Environment.NewLine;

            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " shell \"su -c 'cp -p /data/local/tmp/update.so " + remotePath + "'\"" + Environment.NewLine;
        }

        public string GetRemotePathToPluginDir()
        {
            return this.UserDirectoryForCurrentGame + "/f92plugins/" + platformDescription.platformABI;
        }
        
        // Updates the FLA file
        private void writeUpdateTheFLA()
        {
            // update the FLA library file
            string libraryFilename = gameVersionDescription.libraryFilename;

            string remotePathToPluginDir = GetRemotePathToPluginDir();

            string filename;

            filename = GetFastman92LimitAdjusterLibFilename();

            this.WriteReplaceLibrary(
                releaseOrDebugDirectory + "\\" + filename,
                remotePathToPluginDir + "/" + filename, true);

            // Update dev INI file
            if (!string.IsNullOrEmpty(devPath))
            {
                string localPath = devPath + "\\fastman92 limit adjuster\\Dev INI files\\" + gameDescription.devIniFilename;
                string remotePath = this.UserDirectoryForCurrentGame + "/" + gameDescription.devIniFilename;

                this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " push -p \"" + localPath + "\" \"" + remotePath + "\"" + Environment.NewLine;
            }
        }

        // Get list of additional SO filenames
        public string[] GetListOfAdditionalSOfilenames()
        {
            string[] listOfNames = this.additionalSOfileTextBox.Text.Split(new char[] { ' ' },
                StringSplitOptions.RemoveEmptyEntries);

            return listOfNames;
        }

        // Updates an additional file
        private void writeUpdateAdditionalFiles()
        {
            if (!string.IsNullOrEmpty(this.additionalSOfileTextBox.Text))
            {
                string remotePathToPluginDir = GetRemotePathToPluginDir();

                string[] listOfNames = this.GetListOfAdditionalSOfilenames();

                foreach (string filename in listOfNames)
                {
                    this.WriteReplaceLibrary(
                        releaseOrDebugDirectory + "\\" + filename,
                        remotePathToPluginDir + "/" + filename, true);
                }
            }
        }

        public string GetFastman92LimitAdjusterLibFilename()
        {
            return "libplugin_fastman92limitAdjuster.so";
        }

        public string GetPluginLoaderFilename()
        {
            return "libFastman92pluginLoader.so";
        }

        public bool VerifyThatAllAdditionalFilesExist()
        {
            string[] listOfNames = this.GetListOfAdditionalSOfilenames();

            foreach (string filename in listOfNames)
            {
                string testedFilePath = releaseOrDebugDirectory + "\\" + filename;

                if (!File.Exists(testedFilePath))
                {
                    MessageBox.Show("Additional file that you have specified " + testedFilePath + " does not exist!");
                    return false;
                }
            }

            return true;
        }

        public bool VerifyIfTheFLAlibraryExists()
        {
            // update the FLA library file
            string path = releaseOrDebugDirectory + "\\" + GetFastman92LimitAdjusterLibFilename();

            if (!File.Exists(path))
            {
                MessageBox.Show("The FLA library " + path + " does not exist!");
                return false;
            }

            return true;
        }

        public bool VerifyIfFilesExistForThePurposeOfWritingAllLibraries()
        {
            if (this.includeTheFLApluginCheckBox.Checked && !VerifyIfTheFLAlibraryExists())
                return false;

            string originalLibFile = this.FilesDirectoryForCurrentGameArchitectureSpecific + "\\original_lib\\"
             + this.gameVersionDescription.libraryFilename;

            if (!File.Exists(originalLibFile))
            {
                MessageBox.Show("Original library file does not exist: " + originalLibFile
                    + Environment.NewLine + Environment.NewLine + "You have likely forgotten the step of importing game library file to PC."
                    + Environment.NewLine + "Use button \"Import game library to PC\" first");

                return false;
            }

            return VerifyThatAllAdditionalFilesExist();
        }

        // Updates all libraries
        private void writeUpdateLibraries()
        {
            string libraryFilename = gameVersionDescription.libraryFilename;

            string filename;

            // Store path to library dir into variable
            this.writeGetPathToLibraryDir();

            // Apply plugin loader for the game's library
            this.writeApplyPluginLoader();

            // update the FLA
            if (this.includeTheFLApluginCheckBox.Checked)
                this.writeUpdateTheFLA();

            // update plugin loader
            filename = GetPluginLoaderFilename();

            this.WriteReplaceLibrary(
                releaseOrDebugDirectory + "\\" + filename,
                "%NATIVE_LIB_DIR%/" + filename);

            // update CLEO
            if (this.includeLibCLEOcheckBox.Checked && !string.IsNullOrEmpty(CLEOdirectoryPath))
            {
                filename = "libcleo.so";

                this.WriteReplaceLibrary(
                    CLEOdirectoryPath + "\\" + filename,
                    "%NATIVE_LIB_DIR%/" + filename);
            }

            // update additional files
            this.writeUpdateAdditionalFiles();

            // update the game library
            string modifiedLibFile = FilesDirectoryForCurrentGameArchitectureSpecific + "\\modified_lib\\" + libraryFilename;

            this.WriteReplaceLibrary(
                modifiedLibFile,
                "%NATIVE_LIB_DIR%/" + libraryFilename
                );
        }

        private void updateLibrariesButton_Click(object sender, EventArgs e)
        {
            if (!VerifyIfFilesExistForThePurposeOfWritingAllLibraries())
                return;

            this.ScriptContent = String.Empty;

            this.writeStopGameCommand();
            this.writeUpdateLibraries();

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void useDebugLibraryCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            this.SetReleaseOrDebugDirectory();
            this.RefreshInformations();
        }

        private void updateLibrariesAndRunButton_Click(object sender, EventArgs e)
        {
            if (!VerifyIfFilesExistForThePurposeOfWritingAllLibraries())
                return;

            this.ScriptContent = String.Empty;

            this.writeStopGameCommand();
            this.writeUpdateLibraries();
            this.writeRunGameCommand();

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void wakeUpScreenButton_Click(object sender, EventArgs e)
        {
            this.ScriptContent = String.Empty;

            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " shell input keyevent KEYCODE_POWER"
                + " && " + "\"" + this.adbEXEpath + "\"" + " shell input swipe 200 500 200 0"
                + " && " + "\"" + this.adbEXEpath + "\"" + " shell input text 7128" + Environment.NewLine;

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void WriteForceContinue()
        {
            this.ScriptContent += "setlocal" + Environment.NewLine;

            this.ScriptContent += "for /f \"delims=\" %%a in ('\"" + this.adbEXEpath + "\" shell pidof " + PackageNameToRun + "') do @set pid=%%a"
                + Environment.NewLine;

            this.ScriptContent += "echo PID=%pid%" + Environment.NewLine;

            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " forward tcp:23915 jdwp:%pid%"
                + Environment.NewLine + Environment.NewLine;

            this.ScriptContent += "set VALUE=CurrentVersion" + Environment.NewLine + Environment.NewLine;

            this.ScriptContent += "set KEY=\"HKLM\\SOFTWARE\\JavaSoft\\JDK\""
                + Environment.NewLine;

            this.ScriptContent += "reg query %KEY% /v %VALUE% 2>nul && goto JDKisInstalled"
                + Environment.NewLine + Environment.NewLine;

            this.ScriptContent += "set KEY=\"HKLM\\SOFTWARE\\JavaSoft\\Java Development Kit\""
                + Environment.NewLine;

            this.ScriptContent += "reg query %KEY% /v %VALUE% 2>nul && goto JDKisInstalled"
                + Environment.NewLine + Environment.NewLine;

            this.ScriptContent += "echo JDK not installed, path to JDK could not be read from registry." + Environment.NewLine + "pause" + Environment.NewLine + Environment.NewLine;

            this.ScriptContent += ":JDKisInstalled" + Environment.NewLine;

            this.ScriptContent += "set JDK_VERSION=" + Environment.NewLine
                + "for /f \"tokens=2,*\" %%a in ('reg query %KEY% /v %VALUE% ^| findstr %VALUE%') do ("
                + Environment.NewLine + "set JDK_VERSION=%%b" + Environment.NewLine
                + ")" + Environment.NewLine + Environment.NewLine;

            this.ScriptContent += "set JDK_HOME=" + Environment.NewLine +
                "for /f \"tokens=2,*\" %%a in ('reg query %KEY%\\%JDK_VERSION% /v JavaHome ^| findstr JavaHome') do ("
                + Environment.NewLine + "\tset JDK_HOME=%%b" + Environment.NewLine +
                ")" + Environment.NewLine + Environment.NewLine;

            this.ScriptContent += "echo exit | \"%JDK_HOME%\\bin\\jdb.exe\" -connect com.sun.jdi.SocketAttach:hostname=localhost,port=23915"
                + Environment.NewLine;
        }

        private void forceContinueButton_Click(object sender, EventArgs e)
        {
            if (!VerifyJDBpathIsSet())
                return;

            this.ScriptContent = String.Empty;

            this.WriteForceContinue();
            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void updateTheFLAandRunButton_Click(object sender, EventArgs e)
        {
            if (!this.VerifyIfTheFLAlibraryExists())
                return;

            this.ScriptContent = String.Empty;

            this.writeStopGameCommand();
            this.writeUpdateTheFLA();
            this.writeRunGameCommand();

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void updateTheFLAbutton_Click(object sender, EventArgs e)
        {
            if (!this.VerifyIfTheFLAlibraryExists())
                return;

            this.ScriptContent = String.Empty;

            this.writeStopGameCommand();
            this.writeUpdateTheFLA();

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void detectGameVersionButton_Click(object sender, EventArgs e)
        {
            this.ScriptContent = String.Empty;

            this.ScriptContent += "@echo off" + Environment.NewLine;
            this.ScriptContent += "echo Details about package " + PackageNameToRun + Environment.NewLine; ;
            this.ScriptContent += "\"" + this.adbEXEpath + "\"" + " shell \"dumpsys package " + PackageNameToRun + " | grep version\"" + Environment.NewLine;
            this.ScriptContent += "pause";

            this.RunScript();
        }

        private void directoryPathTextBox_TextChanged(object sender, EventArgs e)
        {
            this.WorkingDirectoryPath = this.directoryPathTextBox.Text;
            this.SetPathsForCurrentGameVersion();
            this.RefreshInformations();
        }

        private void updateTheFLAandRunForDebuggingButton_Click(object sender, EventArgs e)
        {
            this.ScriptContent = String.Empty;

            this.writeStopGameCommand();
            this.writeUpdateTheFLA();
            this.writeRunGameCommand(true);

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void enableDeveloperOptionsButton_Click(object sender, EventArgs e)
        {
            this.bEnableDeveloperOptions = true;
            this.enableDeveloperOptionsButton.Enabled = !this.bEnableDeveloperOptions;

            if (!this.bHasExitScriptImmediatelyEverBeenSet)
                this.exitImmediatelyCheckBox.Checked = true;

            this.SetButtonsWhichRequireGame();
            this.SetButtonsWhichRequireGameVersion();

            this.SetOtherButtons();
        }

        private void start_strcpy_button_Click(object sender, EventArgs e)
        {
            string pathToEXE = this.devPath + "\\Neccessary files\\Scrcpy\\scrcpy.exe";

            try
            {
                Process p = new Process();

                // set start info
                p.StartInfo = new ProcessStartInfo(pathToEXE);
                p.Start();
            }
            catch (Exception err)
            {
                MessageBox.Show("Trying to run an application: " + pathToEXE
                    + Environment.NewLine + "Exception: " + err.Message);
            }
        }

        private bool VerifyJDBpathIsSet()
        {
            return true;
        }

        private void runGameForDebuggingAndContinueButton_Click(object sender, EventArgs e)
        {
            if (!VerifyJDBpathIsSet())
                return;

            this.ScriptContent = String.Empty;

            this.writeStopGameCommand();
            this.writeRunGameCommand(true, true);
            this.WriteForceContinue();

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void openExternalDirectoryButton_Click(object sender, EventArgs e)
        {
            try
            {
                Process.Start(this.UserDirectoryForCurrentGameAccessFromComputer);
            }
            catch (Win32Exception win32Exception)
            {
                MessageBox.Show("Error: " + win32Exception.Message
                    + "\n\nThe following directory was supposed to be opened:\n"
                    + this.UserDirectoryForCurrentGameAccessFromComputer);
            }
        }

        private void updateAdditionalFileButton_Click(object sender, EventArgs e)
        {
            if (!this.VerifyThatAllAdditionalFilesExist())
                return;

            this.ScriptContent = String.Empty;
            this.writeStopGameCommand();
            this.writeUpdateAdditionalFiles();

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void updateAdditionalFileAndRunButton_Click(object sender, EventArgs e)
        {
            if (!this.VerifyThatAllAdditionalFilesExist())
                return;

            this.ScriptContent = String.Empty;
            this.writeStopGameCommand();
            this.writeUpdateAdditionalFiles();
            this.writeRunGameCommand();

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void additionalSOfileTextBox_TextChanged(object sender, EventArgs e)
        {
            this.SetAdditionalFileButtonsEnabledState();
        }

        private void deleteAdditionalFileButton_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(this.additionalSOfileTextBox.Text))
            {
                string remotePathToPluginDir = GetRemotePathToPluginDir();

                this.ScriptContent = String.Empty;


                this.writeStopGameCommand();

                // Store path to library dir into variable
                this.writeGetPathToLibraryDir();

                string[] listOfNames = this.GetListOfAdditionalSOfilenames();

                foreach (string filename in listOfNames)
                {
                    this.WriteRemoveFile(
                    remotePathToPluginDir + "/" + filename);
                }

                this.writeEndToCommandPrompt();
                this.RunScript();
            }
        }

        private void clearAddtionalFilenameButton_Click(object sender, EventArgs e)
        {
            this.additionalSOfileTextBox.Text = String.Empty;
        }

        private void takeScreenshotButton_Click(object sender, EventArgs e)
        {
            this.ScriptContent = String.Empty;

            this.ScriptContent += "\"" + this.adbEXEpath + "\" shell screencap -p /data/local/tmp/screenshot.png" + Environment.NewLine;

            Directory.CreateDirectory(this.screenshotDirectory);

            // Figure out screenshot name
            string screenshotName;

            {
                int i = 0;

                while (true)
                {
                    string possibleName = "screenshot_" + i + ".png";

                    if (!File.Exists(this.screenshotDirectory + Path.DirectorySeparatorChar + possibleName))
                    {
                        screenshotName = possibleName;
                        break;
                    }
                    else
                        i++;
                }
            }

            this.ScriptContent += "\"" + this.adbEXEpath + "\" pull /data/local/tmp/screenshot.png "
                + "\"" + this.screenshotDirectory + "\\" + screenshotName + "\"" + Environment.NewLine;

            this.ScriptContent += "\"" + this.adbEXEpath + "\" shell rm /data/local/tmp/screenshot.png" + Environment.NewLine;

            this.writeEndToCommandPrompt();
            this.RunScript();
        }

        private void label7_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("http://fastman92.com");
        }

        private void seeScreenshotsButton_Click(object sender, EventArgs e)
        {
            Directory.CreateDirectory(this.screenshotDirectory);

            try
            {
                Process.Start(this.screenshotDirectory);
            }
            catch (Win32Exception win32Exception)
            {
                MessageBox.Show("Error: " + win32Exception.Message);
            }
        }

        private void helpButton_Click(object sender, EventArgs e)
        {
            HelpForm help = new HelpForm();
            help.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Process p = new Process();

            // set start info
            p.StartInfo = new ProcessStartInfo("cmd.exe");

            p.Start();
        }

        private void InformationTextBox_Click(object sender, EventArgs e)
        {

        }

        private void exitImmediatelyCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            this.bHasExitScriptImmediatelyEverBeenSet = true;
        }

        private void includeLibCLEOcheckBox_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void updateModifiedAPKbutton_Click(object sender, EventArgs e)
        {
            if (this.VerifyIfFilesExistForThePurposeOfWritingAllLibraries())
                new CreateModifiedAPKform(this).ShowDialog();
        }

        private void SetAndroidDirectory()
        {
            this.Android_dir = this.apkUsingAndroidUnprotected.Checked ? "Android_unprotected" : "Android";
        }

        private void apkUsingAndroidUnprotected_CheckedChanged(object sender, EventArgs e)
        {
            this.SetAndroidDirectory();
            this.SetPathsForCurrentGameVersion();
            this.RefreshInformations();
        }

        private void externalDirectoryButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show("This will open the following directory in explorer: \n"
                + this.UserDirectoryForCurrentGameAccessFromComputer
                + "\n\nUse LAN Drive Server on the Android device");
        }

        private void developmentPackageNamesCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            this.SetPathsForCurrentGameVersion();
            this.RefreshInformations();
        }
    }
}
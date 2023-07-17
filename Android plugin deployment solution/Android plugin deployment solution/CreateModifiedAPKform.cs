using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Threading;
using fastman92;
using System.Diagnostics;

namespace Android_plugin_deployment_solution
{
    public partial class CreateModifiedAPKform : Form
    {
        private ProcessNoWindow process = new ProcessNoWindow();
        private MainForm mainForm = null;
        
        private bool includeTheFLApluginCheckBoxChecked;

        private bool bLoadedAPKS;

        private void OnOutputDataReceived(object sender, DataReceivedEventArgs e)
        {
            if (e.Data == null)
                return;


            if (sender != process.process)
                return;

            this.WriteToLog(Environment.NewLine + e.Data);
        }

        public CreateModifiedAPKform(MainForm mainForm)
        {
            this.mainForm = mainForm;
            this.includeTheFLApluginCheckBoxChecked = mainForm.includeTheFLApluginCheckBox.Checked;

            process.Init(OnOutputDataReceived);

            InitializeComponent();
        }

        private void UpdateInformations()
        {
            this.InformationTextBox.Text = String.Empty;
            
            this.InformationTextBox.Text += "Selected game is " + mainForm.gameDescription.gameName + Environment.NewLine;
            this.InformationTextBox.Text += "Selected game version is " + mainForm.gameVersionDescription.name + Environment.NewLine + Environment.NewLine;

            if (this.originalAPKfilePath.Text != String.Empty)
                this.InformationTextBox.Text += "The original APK package " + this.originalAPKfilePath.Text + " will be read." + Environment.NewLine;

            if(this.newAPKpath.Text != String.Empty)
                this.InformationTextBox.Text += "New APK package " + this.newAPKpath.Text + " should be created and signed with test key." + Environment.NewLine;

            

            if (this.originalAPKfilePath.Text != String.Empty
             && this.newAPKpath.Text != String.Empty)
            {
                this.InformationTextBox.Text += Environment.NewLine + "The new APK package will contain the following library files:";
                this.InformationTextBox.Text += Environment.NewLine + "- modified game library: " + mainForm.gameVersionDescription.libraryFilename;
                this.InformationTextBox.Text += Environment.NewLine + "- fastman92 plugin loader: " + mainForm.GetPluginLoaderFilename();

                if (includeTheFLApluginCheckBoxChecked)
                    this.InformationTextBox.Text += Environment.NewLine + "- fastman92 limit adjuster: " + mainForm.GetFastman92LimitAdjusterLibFilename();

                if (mainForm.includeLibCLEOcheckBox.Checked)
                    this.InformationTextBox.Text += Environment.NewLine + "- CLEO library: libcleo.so";

                /*
                if (!string.IsNullOrEmpty(mainForm.additionalSOfileTextBox.Text))
                {
                    string[] listOfNames = mainForm.GetListOfAdditionalSOfilenames();

                    foreach (string filename in listOfNames)
                        this.InformationTextBox.Text += Environment.NewLine + "- additional library: " + filename;                    
                }
                */

                this.InformationTextBox.Text += Environment.NewLine + "- other libraries from the package";

                this.InformationTextBox.Text += Environment.NewLine + Environment.NewLine
                    + "Plugins (like the FLA) can be put in the following directory on the Android device: "
                    + mainForm.GetRemotePathToPluginDir();
            }
        }

        private void CreateModifiedAPKform_Load(object sender, EventArgs e)
        {
            string libDirectoryOnPC = mainForm.FilesDirectoryForCurrentGame + "\\original_lib";
            string BaseAPKpath = libDirectoryOnPC + Path.DirectorySeparatorChar + "base.apk";

            if (File.Exists(BaseAPKpath))
            {
                originalAPKfilePath.Text = BaseAPKpath;
                originalAPKfilePath.SelectionStart = originalAPKfilePath.Text.Length;
                originalAPKfilePath.SelectionLength = 0;
            }

            this.UpdateInformations();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (this.saveFileDialog1.ShowDialog() == DialogResult.OK)
                this.newAPKpath.Text = this.saveFileDialog1.FileName;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (this.openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                this.originalAPKfilePath.Text = this.openFileDialog1.FileName;

                this.bLoadedAPKS = Path.GetExtension(this.originalAPKfilePath.Text).ToLower() == ".apks";

                this.label4.Text = "CREATE NEW APK";

                if (this.bLoadedAPKS)
                {
                    this.label4.Text += "S";
                    this.saveFileDialog1.Filter = "APKS archive|*.apks|All files|*.*";
                }
                else
                    this.saveFileDialog1.Filter = "APK archive|*.apk|All files|*.*";
            }
        }

        public void WriteToLog(String str)
        {
            BeginInvoke((Action)(() =>
            {
                this.InformationTextBox.AppendText(str);
            }));
        }

        private void WriteExceptionToLog(Exception e)
        {
            this.WriteToLog(Environment.NewLine + "Exception: " + e.Message);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.button3.Enabled = false;
            

            new Thread(() =>
            {
                try
                {
                    this.WriteToLog(Environment.NewLine + Environment.NewLine);

                    string gameLibFilename = mainForm.gameVersionDescription.libraryFilename;

                    string unalignedAPKpath = this.mainForm.tempDirectory + Path.DirectorySeparatorChar + "unaligned.apk";
                    string unpackedAPKSdirectory = this.mainForm.tempDirectory + Path.DirectorySeparatorChar + "unpackedAPKs";
                    string inputAPKpath = this.originalAPKfilePath.Text;
                    string gameLibPathInZip = "lib/" + mainForm.platformDescription.platformABI + "/" + gameLibFilename;
                    string modifiedLibDir = mainForm.FilesDirectoryForCurrentGameArchitectureSpecific + Path.DirectorySeparatorChar + "modified_lib";


                    string tempAPKdirPath = mainForm.tempDirectory + "\\apk";

                    string newAPKpath = this.newAPKpath.Text;

                    List<string> APKpaths = new List<string>();


                    // Delete directories

                    try
                    {
                        Directory.Delete(@"\\?\" + tempAPKdirPath, true);
                    }
                    catch (Exception) { }

                    ///////

                    if (this.bLoadedAPKS)
                    {
                        this.WriteToLog("Current step: unpacking APKS archive" + Environment.NewLine + Environment.NewLine);

                        // System.IO.Compression.ZipFile.ExtractToDirectory(inputAPKpath, unpackedAPKSdirectory);

                        this.WriteToLog("Current step: searching which APK package has got application's library." + Environment.NewLine + Environment.NewLine);

                        bool bLibraryFound = false;

                        foreach (var APKfilePath in Directory.GetFiles(unpackedAPKSdirectory))
                        {
                            if (Path.GetExtension(APKfilePath).ToLower() != ".apk")
                                continue;

                            APKpaths.Add(APKfilePath);

                            using (System.IO.Compression.ZipArchive archive = System.IO.Compression.ZipFile.OpenRead(APKfilePath))
                            {
                                var entry = archive.GetEntry(gameLibPathInZip);

                                if (entry != null)
                                {
                                    bLibraryFound = true;
                                    inputAPKpath = APKfilePath;
                                    break;
                                }
                            }
                        }

                        if (!bLibraryFound)
                            throw new FileNotFoundException("File " + gameLibPathInZip + " not found in any of APK files from APKS archive.");

                        newAPKpath = inputAPKpath;

                        this.WriteToLog("Application library found in " + inputAPKpath + Environment.NewLine + Environment.NewLine);
                    }
                    else
                        APKpaths.Add(inputAPKpath);

                    System.IO.Compression.ZipFile.ExtractToDirectory(inputAPKpath, tempAPKdirPath);


                    if (!File.Exists(tempAPKdirPath + Path.DirectorySeparatorChar + gameLibPathInZip))
                        throw new FileNotFoundException("File " + gameLibPathInZip + " not found.");


                    string fullLibDirPath = tempAPKdirPath + Path.DirectorySeparatorChar + "lib" + Path.DirectorySeparatorChar + mainForm.platformDescription.platformABI;


                    mainForm.ScriptContent = String.Empty;
                    this.mainForm.writeApplyPluginLoader();
                    mainForm.RunScript();

                    // Copy files
                    {
                        // Copy game library
                        File.Copy(modifiedLibDir + Path.DirectorySeparatorChar + gameLibFilename, fullLibDirPath + Path.DirectorySeparatorChar + gameLibFilename, true);

                        // Copy the FLA
                        if (includeTheFLApluginCheckBoxChecked)
                        {
                            string filename = mainForm.GetFastman92LimitAdjusterLibFilename();

                            File.Copy(mainForm.releaseOrDebugDirectory + Path.DirectorySeparatorChar + filename, fullLibDirPath + Path.DirectorySeparatorChar + filename, true);
                        }

                        // Copy the plugin loader
                        {
                            string filename = mainForm.GetPluginLoaderFilename();

                            File.Copy(mainForm.releaseOrDebugDirectory + Path.DirectorySeparatorChar + filename, fullLibDirPath + Path.DirectorySeparatorChar + filename, true);
                        }

                        // Copy CLEO
                        if (mainForm.includeLibCLEOcheckBox.Checked)
                        {
                            string filename = "libcleo.so";

                            File.Copy(mainForm.CLEOdirectoryPath + Path.DirectorySeparatorChar + filename, fullLibDirPath + Path.DirectorySeparatorChar + filename, true);
                        }

                        // Additional files
                        /*
                        if (!string.IsNullOrEmpty(mainForm.additionalSOfileTextBox.Text))
                        {
                            string[] listOfNames = mainForm.GetListOfAdditionalSOfilenames();

                            foreach (string filename in listOfNames)
                                File.Copy(mainForm.releaseOrDebugDirectory + Path.DirectorySeparatorChar + filename, fullLibDirPath + Path.DirectorySeparatorChar + filename, true);
                        }
                        */
                    }

                    // Create modified APK archive
                    this.WriteToLog("Creating new unaligned APK archive." + Environment.NewLine);

                    if (File.Exists(unalignedAPKpath))
                        File.Delete(unalignedAPKpath);

                    System.IO.Compression.ZipFile.CreateFromDirectory(tempAPKdirPath, unalignedAPKpath);

                    // Align archive
                    String ZIPalignPath = mainForm.toolsDirectory + Path.DirectorySeparatorChar + "zipalign" + Path.DirectorySeparatorChar + "zipalign.exe";

                    string arguments = "-p -f -v 4 \"" + unalignedAPKpath + "\" \"" + newAPKpath + "\"";
                    
                    this.WriteToLog("Creating new aligned APK package." + Environment.NewLine
                + "\"" + ZIPalignPath + "\" " + arguments + Environment.NewLine);

                    process.StartAndWaitForExit(ZIPalignPath, arguments);

                    // Sign new APK archives
                    this.WriteToLog(Environment.NewLine);

                    String SignAPKdirectory = mainForm.toolsDirectory + Path.DirectorySeparatorChar + "apksigner";
                    String SignAPKjar = SignAPKdirectory + Path.DirectorySeparatorChar + "apksigner.jar";

                    foreach(var APKpath in APKpaths)
                    {
                        arguments = "-jar \"" + SignAPKjar + "\" sign --cert \"" + SignAPKdirectory + Path.DirectorySeparatorChar + "key" + Path.DirectorySeparatorChar + "key.x509.pem\" --key \"" + SignAPKdirectory + Path.DirectorySeparatorChar + "key" + Path.DirectorySeparatorChar + "key.pk8\" \"" + APKpath + "\"";

                        this.WriteToLog("Sign APK package " + APKpath + Environment.NewLine
                        + "java.exe " + arguments + Environment.NewLine + Environment.NewLine);

                        process.StartAndWaitForExit("java.exe", arguments);
                    }

                                        // Create APKS
                    if (this.bLoadedAPKS)
                    {
                        this.WriteToLog("Starting to create APKS archive. This can take few minutes." + Environment.NewLine);

                        if (File.Exists(this.newAPKpath.Text))
                            File.Delete(this.newAPKpath.Text);

                        System.IO.Compression.ZipFile.CreateFromDirectory(unpackedAPKSdirectory, this.newAPKpath.Text);

                        this.WriteToLog("Finished creating APKS archive." + Environment.NewLine);
                    }

                    this.WriteToLog(Environment.NewLine + Environment.NewLine + "<<< Everything is done. If everything was done corrrectly, then you can install the new package. >>>");

                    this.button3.Enabled = true;
                }
                catch (Exception exception)
                {
                    this.WriteExceptionToLog(exception);
                }

                this.button3.Enabled = true;

            }).Start();


            {
                if (true)
                    return;

                string gameLibFilename = mainForm.gameVersionDescription.libraryFilename;

                mainForm.ScriptContent = String.Empty;

                string tempAPKdirPath = mainForm.tempDirectory + "\\apk";

                string originalAPKfullPath = Path.GetFullPath(this.originalAPKfilePath.Text);

                string unalignedAPKpath = mainForm.tempDirectory + Path.DirectorySeparatorChar + "unaligned.apk";
                string alignedAPKpath = mainForm.tempDirectory + Path.DirectorySeparatorChar + "aligned.apk";
                string outputAPKpath = Path.GetFullPath(this.newAPKpath.Text);

                //////////

                mainForm.ScriptContent += "rd /s /q \"" + tempAPKdirPath + "\"" + Environment.NewLine;

                /*
                try
                {
                    Directory.Delete(tempAPKdirPath, true);
                }
                catch (Exception) { }
                */

                        mainForm.ScriptContent += "del /F /S \"" + unalignedAPKpath + "\"" + Environment.NewLine;

                /*
                try
                {
                    File.Delete(unalignedAPKpath);
                }
                catch (Exception) { }
                */
                //////


                mainForm.ScriptContent += "\"" + mainForm.toolsDirectory + Path.DirectorySeparatorChar + "7za" + Path.DirectorySeparatorChar + "7za.exe\"" +
                    " x \"" + originalAPKfullPath + "\" -o\"" + tempAPKdirPath + "\"" + Environment.NewLine;

                {
                    string testedDirPath = tempAPKdirPath + Path.DirectorySeparatorChar + "lib" + Path.DirectorySeparatorChar + mainForm.platformDescription.platformABI;
                    string testedLibraryFilePath = testedDirPath + Path.DirectorySeparatorChar + gameLibFilename;

                    mainForm.ScriptContent += "IF EXIST \"" + testedLibraryFilePath + "\" SET newLibraryDir=\""
                        + testedDirPath +
                        "\"" + Environment.NewLine;
                }

                mainForm.ScriptContent += "IF NOT DEFINED newLibraryDir (" + Environment.NewLine
                    + "ECHO Game library not found in the directory of extracted APK archive!" + Environment.NewLine
                    + "pause" + Environment.NewLine
                    + "exit" + Environment.NewLine
                    + ")" + Environment.NewLine;

                mainForm.ScriptContent += "echo New APK library directory: %newLibraryDir%" + Environment.NewLine;

                mainForm.writeApplyPluginLoader();

                string modifiedLibDir = mainForm.FilesDirectoryForCurrentGameArchitectureSpecific + Path.DirectorySeparatorChar + "modified_lib";

                // Copy files
                {
                    // Copy game library
                    mainForm.ScriptContent += "robocopy \"" + modifiedLibDir + " \" %newLibraryDir% " + gameLibFilename
                        + Environment.NewLine;

                    // Copy the FLA
                    if (includeTheFLApluginCheckBoxChecked)
                    {
                        string filename = mainForm.GetFastman92LimitAdjusterLibFilename();

                        mainForm.ScriptContent += "robocopy \"" + mainForm.releaseOrDebugDirectory + " \" %newLibraryDir% " + filename
                            + Environment.NewLine;
                    }

                    // Copy the plugin loader
                    {
                        string filename = mainForm.GetPluginLoaderFilename();

                        mainForm.ScriptContent += "robocopy \"" + mainForm.releaseOrDebugDirectory + " \" %newLibraryDir% " + filename
                            + Environment.NewLine;
                    }

                    // Copy CLEO                
                    if (mainForm.includeLibCLEOcheckBox.Checked)
                    {
                        string filename = "libcleo.so";

                        mainForm.ScriptContent += "robocopy \"" + mainForm.CLEOdirectoryPath + " \" %newLibraryDir% " + filename
                            + Environment.NewLine;
                    }

                    // Additional file
                    /*
                    if (!string.IsNullOrEmpty(mainForm.additionalSOfileTextBox.Text))
                    {
                        string[] listOfNames = mainForm.GetListOfAdditionalSOfilenames();

                        foreach (string filename in listOfNames)
                            mainForm.ScriptContent += "robocopy \"" + mainForm.releaseOrDebugDirectory + " \" %newLibraryDir% " + filename
                            + Environment.NewLine;
                    }
                    */
                }

                // Create APK
                mainForm.ScriptContent += "echo Creating APK archive" + Environment.NewLine;
                mainForm.ScriptContent += "\"" + mainForm.toolsDirectory + Path.DirectorySeparatorChar + "7za" + Path.DirectorySeparatorChar + "7za.exe\"" +
                    " a -tzip \"" + unalignedAPKpath + "\" \"" + tempAPKdirPath + "\\*\"" + Environment.NewLine;

                // Zip Align
                String ZIPalignPath = mainForm.toolsDirectory + Path.DirectorySeparatorChar + "zipalign" + Path.DirectorySeparatorChar + "zipalign.exe";

                string arguments = "-p -f -v 4 \"" + unalignedAPKpath + "\" \"" + alignedAPKpath + "\"";
                mainForm.ScriptContent += "\"" + ZIPalignPath + "\" " + arguments + Environment.NewLine;

                // Signing the APK
                String SignAPKdirectory = mainForm.toolsDirectory + Path.DirectorySeparatorChar + "apksigner";
                String SignAPKjar = SignAPKdirectory + Path.DirectorySeparatorChar + "apksigner.jar";
                arguments = "-jar \"" + SignAPKjar + "\" sign --cert \"" + SignAPKdirectory + Path.DirectorySeparatorChar + "key" + Path.DirectorySeparatorChar + "key.x509.pem\" --key \"" + SignAPKdirectory + Path.DirectorySeparatorChar + "key" + Path.DirectorySeparatorChar + "key.pk8\" --out \"" + outputAPKpath + "\" \"" + alignedAPKpath + "\"";
                mainForm.ScriptContent += "java " + arguments + Environment.NewLine;

                mainForm.ScriptContent += "pause";
                mainForm.RunScript();
            }
        }

        void pathsUpdatedEvent()
        {
            this.button3.Enabled = originalAPKfilePath.Text.Length > 0 && newAPKpath.Text.Length > 0;
            this.UpdateInformations();
        }

        private void newAPKpath_TextChanged(object sender, EventArgs e)
        {
            this.pathsUpdatedEvent();
        }

        private void originalAPKfilePath_TextChanged(object sender, EventArgs e)
        {
            this.pathsUpdatedEvent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Android_plugin_deployment_solution
{
    public partial class CreateModifiedAPKform : Form
    {
        private MainForm mainForm = null;

        private bool includeTheFLApluginCheckBoxChecked;

        public CreateModifiedAPKform(MainForm mainForm)
        {
            this.mainForm = mainForm;
            this.includeTheFLApluginCheckBoxChecked = mainForm.includeTheFLApluginCheckBox.Checked;

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
                this.originalAPKfilePath.Text = this.openFileDialog1.FileName;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            mainForm.ScriptContent = String.Empty;

            ///////////
            string gameLibFilename = mainForm.gameVersionDescription.libraryFilename;

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
                " x \"" + originalAPKfullPath  + "\" -o\"" + tempAPKdirPath + "\"" + Environment.NewLine;

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

            string modifiedLibDir = mainForm.FilesDirectoryForCurrentGame + Path.DirectorySeparatorChar + "modified_lib";

            // Copy files
            {
                // Copy game library
                mainForm.ScriptContent += "robocopy \"" + modifiedLibDir + " \" %newLibraryDir% " + gameLibFilename
                    + Environment.NewLine;

                // Copy the FLA
                if(includeTheFLApluginCheckBoxChecked)
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

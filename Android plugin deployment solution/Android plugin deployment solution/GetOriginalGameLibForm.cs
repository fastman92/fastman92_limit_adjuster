using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.IO.Compression;
using System.Text;
using System.Windows.Forms;

namespace Android_plugin_deployment_solution
{
    public partial class GetOriginalGameLibForm : Form
    {
        private MainForm mainForm = null;

        private string libraryFilename = null;

        public GetOriginalGameLibForm(MainForm mainForm)
        {
            this.mainForm = mainForm;
            InitializeComponent();   
        }

        private void GetOriginalGameLibForm_Load(object sender, EventArgs e)
        {
            this.libraryFilename = this.mainForm.gameVersionDescription.libraryFilename;
            this.nameOfFileNeededLabel.Text = libraryFilename;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show(
                "APDS will take a game library file from the Android device. "
                + " Use this option if an original file for current game version is still installed on the device. You should not import the file, which is already modified by APDS."
                + " Choose yes to confirm.", "Confirm mainForm action",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.None,
                MessageBoxDefaultButton.Button2) == DialogResult.Yes)
            {
                mainForm.ScriptContent = String.Empty;

                GameDescription gameDescription = mainForm.gameDescription;
                GameVersionDescription versionDescription = mainForm.gameVersionDescription;
                
                string libraryFilename = versionDescription.libraryFilename;

                string pathToLibOnAndroidDevice = mainForm.ApplicationDirectoryOnAndroidDevice
                    + "/lib/" + libraryFilename;

                string libDirectoryOnPC = mainForm.FilesDirectoryForCurrentGame + Path.DirectorySeparatorChar + "original_lib";

                string libFilePathOnPC = libDirectoryOnPC + Path.DirectorySeparatorChar + libraryFilename;

                if(File.Exists(libFilePathOnPC))
                {
                    MessageBox.Show("Error: "
                        + Environment.NewLine
                        + "File \"" + libFilePathOnPC + "\" already exists. Please be extra cautious."
                        + Environment.NewLine + Environment.NewLine +
                        "The original library file for current game version is already imported. No need to do it again."                        
                        );
                                                
                    return;
                }
                
                // Write the script
                mainForm.EvaluatePath(libDirectoryOnPC + Path.DirectorySeparatorChar);

                mainForm.ScriptContent += "\"" + mainForm.adbEXEpath + "\"" + " shell \"rm /data/local/tmp/"
                    + libraryFilename + "\"" + Environment.NewLine;

                mainForm.ScriptContent += "\"" + mainForm.adbEXEpath + "\"" + " shell \"su -c 'cp -p " + pathToLibOnAndroidDevice +
                    " /data/local/tmp/" + libraryFilename + "'\""
                    + Environment.NewLine;
                
                mainForm.ScriptContent += "\"" + mainForm.adbEXEpath + "\"" + " pull \"/data/local/tmp/"
                    + libraryFilename + "\" \""
            + libDirectoryOnPC + "\"" + Environment.NewLine;

                mainForm.ScriptContent += "\"" + mainForm.adbEXEpath + "\"" + " shell \"rm /data/local/tmp/"
                    + libraryFilename + "\"" + Environment.NewLine;

                mainForm.writeEndToCommandPrompt();
                mainForm.RunScript();

                MessageBox.Show("Operation finished. Click OK to close.");
                this.Close();
            }
        }

        private void extractGameSOfromAPKfile(string APKfilePath)
        {
            GameDescription gameDescription = mainForm.gameDescription;
            GameVersionDescription versionDescription = mainForm.gameVersionDescription;

            string libraryFilename = versionDescription.libraryFilename;

            string pathToLibOnAndroidDevice = mainForm.ApplicationDirectoryOnAndroidDevice
                + "/lib/" + libraryFilename;

            string libDirectoryOnPC = mainForm.FilesDirectoryForCurrentGameArchitectureSpecific + Path.DirectorySeparatorChar + "original_lib";
            mainForm.EvaluatePath(libDirectoryOnPC + Path.DirectorySeparatorChar);

            string libFilePathOnPC = libDirectoryOnPC + Path.DirectorySeparatorChar + libraryFilename;

            bool extractedFilename = false;
            string checkedPath = "lib/" + mainForm.platformDescription.platformABI + "/" + libraryFilename;

            using (System.IO.Compression.ZipArchive archive = System.IO.Compression.ZipFile.OpenRead(APKfilePath))
            {
                var entry = archive.GetEntry(checkedPath);

                if (entry != null)
                {
                    entry.ExtractToFile(libFilePathOnPC, true);
                    extractedFilename = true;
                }
            }

            if (extractedFilename)
                MessageBox.Show(
                    "File extracted: " + checkedPath
                     + Environment.NewLine + "Operation finished. Click OK to close.");
            else
                MessageBox.Show("Error: unable to extract the SO library from APK archive!");

            this.Close();
        }

        private void getSOlibraryFromAPKfile_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() != DialogResult.OK)
                return;
            
            string APKfilePath = openFileDialog1.FileName;

            if(!File.Exists(APKfilePath))
            {
                MessageBox.Show("APK file " +  APKfilePath + " does not exist!");
                return;
            }

            this.extractGameSOfromAPKfile(APKfilePath);            
        }

        private void getSOlibraryFromAPKfileOnDeviceButton_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show(
            "APDS will import the installed APK package from your device and extract game library file from this APK package."
            + " Use this option if an original APK package for current game version is still installed on the device. You should not import the file from APK package, which is already modified by APDS."
            + " Choose yes to confirm.", "Confirm mainForm action",
            MessageBoxButtons.YesNo,
            MessageBoxIcon.None,
            MessageBoxDefaultButton.Button2) != DialogResult.Yes)
                return;

            mainForm.ScriptContent = String.Empty;

            string libDirectoryOnPC = mainForm.FilesDirectoryForCurrentGameArchitectureSpecific + Path.DirectorySeparatorChar + "original_lib";
            mainForm.EvaluatePath(libDirectoryOnPC + Path.DirectorySeparatorChar);
            string BaseAPKpath = libDirectoryOnPC + Path.DirectorySeparatorChar + "base.apk";

            try
            {
                File.Delete(BaseAPKpath);
            }
            catch (Exception) { }

            mainForm.ScriptContent += "setlocal" + Environment.NewLine;

            mainForm.ScriptContent += "for /f \"delims=\" %%a in ('\"" + mainForm.adbEXEpath + "\" shell pm path " + mainForm.PackageNameToRun + "') do @set apk_path=%%a"
                + Environment.NewLine;
            
            mainForm.ScriptContent += "IF NOT %apk_path:~0,8%==package: (" + Environment.NewLine
                + "ECHO Unable to retrieve a path to APK archive" + Environment.NewLine
                + "pause" + Environment.NewLine
                + "exit" + Environment.NewLine
                + ")" + Environment.NewLine;

            mainForm.ScriptContent += "set apk_path=%apk_path:~8%" + Environment.NewLine;

            mainForm.ScriptContent += "echo %apk_path%" + Environment.NewLine;

            mainForm.ScriptContent += "\"" + mainForm.adbEXEpath + "\"" + " pull \"%apk_path%\" \""
            + BaseAPKpath + "\"" + Environment.NewLine;
            
            mainForm.RunScript(false);

            if (!File.Exists(BaseAPKpath))
            {
                MessageBox.Show("APK file " + BaseAPKpath + " does not exist!");
                return;
            }

            this.extractGameSOfromAPKfile(BaseAPKpath);            
        }
    }
}

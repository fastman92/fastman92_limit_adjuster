namespace Android_plugin_deployment_solution
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.label1 = new System.Windows.Forms.Label();
            this.fastman92_logcat_button = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.gameVersionComboBox = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.gameComboBox = new System.Windows.Forms.ComboBox();
            this.directoryPathTextBox = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.applyPluginLoaderInstallerButton = new System.Windows.Forms.Button();
            this.updateLibrariesAndRunButton = new System.Windows.Forms.Button();
            this.updateLibrariesButton = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.runGameButton = new System.Windows.Forms.Button();
            this.stopGameButton = new System.Windows.Forms.Button();
            this.runGameForDebuggingButton = new System.Windows.Forms.Button();
            this.pullGameLibraryFileToPCbutton = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.exitImmediatelyCheckBox = new System.Windows.Forms.CheckBox();
            this.startIDAserverButton = new System.Windows.Forms.Button();
            this.InformationTextBox = new System.Windows.Forms.TextBox();
            this.useDebugLibraryCheckBox = new System.Windows.Forms.CheckBox();
            this.wakeUpScreenButton = new System.Windows.Forms.Button();
            this.forceContinueButton = new System.Windows.Forms.Button();
            this.updateTheFLAandRunButton = new System.Windows.Forms.Button();
            this.updateTheFLAbutton = new System.Windows.Forms.Button();
            this.detectGameVersionButton = new System.Windows.Forms.Button();
            this.updateTheFLAandRunForDebuggingButton = new System.Windows.Forms.Button();
            this.enableDeveloperOptionsButton = new System.Windows.Forms.Button();
            this.start_strcpy_button = new System.Windows.Forms.Button();
            this.runGameForDebuggingAndContinueButton = new System.Windows.Forms.Button();
            this.openExternalDirectoryButton = new System.Windows.Forms.Button();
            this.includeLibCLEOcheckBox = new System.Windows.Forms.CheckBox();
            this.additionalSOfileTextBox = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.updateAdditionalFileButton = new System.Windows.Forms.Button();
            this.deleteAdditionalFileButton = new System.Windows.Forms.Button();
            this.clearAddtionalFilenameButton = new System.Windows.Forms.Button();
            this.takeScreenshotButton = new System.Windows.Forms.Button();
            this.seeScreenshotsButton = new System.Windows.Forms.Button();
            this.helpButton = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.FLAinformationLabel = new System.Windows.Forms.Label();
            this.createModifiedAPKbutton = new System.Windows.Forms.Button();
            this.includeTheFLApluginCheckBox = new System.Windows.Forms.CheckBox();
            this.updateAdditionalFileAndRunButton = new System.Windows.Forms.Button();
            this.PortLabel = new System.Windows.Forms.Label();
            this.extractGameDataButton = new System.Windows.Forms.Button();
            this.apkUsingAndroidUnprotected = new System.Windows.Forms.CheckBox();
            this.externalDirectoryButton = new System.Windows.Forms.Button();
            this.developmentPackageNamesCheckbox = new System.Windows.Forms.CheckBox();
            this.openFileDialog1 = new dnGREP.FileFolderDialog();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(84, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Select an option";
            // 
            // fastman92_logcat_button
            // 
            this.fastman92_logcat_button.Location = new System.Drawing.Point(6, 53);
            this.fastman92_logcat_button.Name = "fastman92_logcat_button";
            this.fastman92_logcat_button.Size = new System.Drawing.Size(97, 23);
            this.fastman92_logcat_button.TabIndex = 2;
            this.fastman92_logcat_button.Text = "fastman92 logcat";
            this.fastman92_logcat_button.UseVisualStyleBackColor = true;
            this.fastman92_logcat_button.Click += new System.EventHandler(this.fastman92_logcat_button_Click);
            // 
            // label2
            // 
            this.label2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label2.Location = new System.Drawing.Point(109, 7);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(10, 245);
            this.label2.TabIndex = 7;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(140, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(84, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "Select the game";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(140, 48);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(103, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Select game version";
            // 
            // gameVersionComboBox
            // 
            this.gameVersionComboBox.FormattingEnabled = true;
            this.gameVersionComboBox.Location = new System.Drawing.Point(143, 64);
            this.gameVersionComboBox.Name = "gameVersionComboBox";
            this.gameVersionComboBox.Size = new System.Drawing.Size(150, 21);
            this.gameVersionComboBox.TabIndex = 14;
            this.gameVersionComboBox.SelectedIndexChanged += new System.EventHandler(this.gameVersionComboBox_SelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(144, 88);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(120, 13);
            this.label5.TabIndex = 19;
            this.label5.Text = "Select working directory";
            // 
            // gameComboBox
            // 
            this.gameComboBox.FormattingEnabled = true;
            this.gameComboBox.Location = new System.Drawing.Point(143, 24);
            this.gameComboBox.Name = "gameComboBox";
            this.gameComboBox.Size = new System.Drawing.Size(150, 21);
            this.gameComboBox.TabIndex = 12;
            this.gameComboBox.SelectedIndexChanged += new System.EventHandler(this.gameComboBox_SelectedIndexChanged);
            // 
            // directoryPathTextBox
            // 
            this.directoryPathTextBox.Location = new System.Drawing.Point(143, 104);
            this.directoryPathTextBox.Name = "directoryPathTextBox";
            this.directoryPathTextBox.Size = new System.Drawing.Size(422, 20);
            this.directoryPathTextBox.TabIndex = 20;
            this.directoryPathTextBox.TextChanged += new System.EventHandler(this.directoryPathTextBox_TextChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(571, 104);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(97, 20);
            this.button1.TabIndex = 21;
            this.button1.Text = "Select";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // applyPluginLoaderInstallerButton
            // 
            this.applyPluginLoaderInstallerButton.Enabled = false;
            this.applyPluginLoaderInstallerButton.Location = new System.Drawing.Point(143, 143);
            this.applyPluginLoaderInstallerButton.Name = "applyPluginLoaderInstallerButton";
            this.applyPluginLoaderInstallerButton.Size = new System.Drawing.Size(150, 23);
            this.applyPluginLoaderInstallerButton.TabIndex = 23;
            this.applyPluginLoaderInstallerButton.Text = "Apply plugin loader installer";
            this.applyPluginLoaderInstallerButton.UseVisualStyleBackColor = true;
            this.applyPluginLoaderInstallerButton.Click += new System.EventHandler(this.applyPluginLoaderInstallerButton_Click);
            // 
            // updateLibrariesAndRunButton
            // 
            this.updateLibrariesAndRunButton.Enabled = false;
            this.updateLibrariesAndRunButton.Location = new System.Drawing.Point(519, 143);
            this.updateLibrariesAndRunButton.Name = "updateLibrariesAndRunButton";
            this.updateLibrariesAndRunButton.Size = new System.Drawing.Size(150, 23);
            this.updateLibrariesAndRunButton.TabIndex = 43;
            this.updateLibrariesAndRunButton.Text = "Update libraries and run";
            this.updateLibrariesAndRunButton.UseVisualStyleBackColor = true;
            this.updateLibrariesAndRunButton.Click += new System.EventHandler(this.updateLibrariesAndRunButton_Click);
            // 
            // updateLibrariesButton
            // 
            this.updateLibrariesButton.Enabled = false;
            this.updateLibrariesButton.Location = new System.Drawing.Point(518, 172);
            this.updateLibrariesButton.Name = "updateLibrariesButton";
            this.updateLibrariesButton.Size = new System.Drawing.Size(150, 23);
            this.updateLibrariesButton.TabIndex = 44;
            this.updateLibrariesButton.Text = "Update libraries";
            this.updateLibrariesButton.UseVisualStyleBackColor = true;
            this.updateLibrariesButton.Click += new System.EventHandler(this.updateLibrariesButton_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(144, 127);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(84, 13);
            this.label6.TabIndex = 22;
            this.label6.Text = "Select an action";
            // 
            // runGameButton
            // 
            this.runGameButton.Enabled = false;
            this.runGameButton.Location = new System.Drawing.Point(332, 143);
            this.runGameButton.Name = "runGameButton";
            this.runGameButton.Size = new System.Drawing.Size(150, 23);
            this.runGameButton.TabIndex = 35;
            this.runGameButton.Text = "Run game";
            this.runGameButton.UseVisualStyleBackColor = true;
            this.runGameButton.Click += new System.EventHandler(this.runGameButton_Click);
            // 
            // stopGameButton
            // 
            this.stopGameButton.Enabled = false;
            this.stopGameButton.Location = new System.Drawing.Point(332, 275);
            this.stopGameButton.Name = "stopGameButton";
            this.stopGameButton.Size = new System.Drawing.Size(150, 23);
            this.stopGameButton.TabIndex = 39;
            this.stopGameButton.Text = "Stop game";
            this.stopGameButton.UseVisualStyleBackColor = true;
            this.stopGameButton.Click += new System.EventHandler(this.stopGameButton_Click);
            // 
            // runGameForDebuggingButton
            // 
            this.runGameForDebuggingButton.Enabled = false;
            this.runGameForDebuggingButton.Location = new System.Drawing.Point(332, 172);
            this.runGameForDebuggingButton.Name = "runGameForDebuggingButton";
            this.runGameForDebuggingButton.Size = new System.Drawing.Size(150, 23);
            this.runGameForDebuggingButton.TabIndex = 36;
            this.runGameForDebuggingButton.Text = "Run game for debugging";
            this.runGameForDebuggingButton.UseVisualStyleBackColor = true;
            this.runGameForDebuggingButton.Click += new System.EventHandler(this.runGameForDebuggingButton_Click);
            // 
            // pullGameLibraryFileToPCbutton
            // 
            this.pullGameLibraryFileToPCbutton.Enabled = false;
            this.pullGameLibraryFileToPCbutton.Location = new System.Drawing.Point(143, 172);
            this.pullGameLibraryFileToPCbutton.Name = "pullGameLibraryFileToPCbutton";
            this.pullGameLibraryFileToPCbutton.Size = new System.Drawing.Size(150, 23);
            this.pullGameLibraryFileToPCbutton.TabIndex = 24;
            this.pullGameLibraryFileToPCbutton.Text = "Import game library file to PC";
            this.pullGameLibraryFileToPCbutton.UseVisualStyleBackColor = true;
            this.pullGameLibraryFileToPCbutton.Click += new System.EventHandler(this.pullGameLibraryFileToPCbutton_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(554, 9);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(114, 39);
            this.label7.TabIndex = 10;
            this.label7.Text = "Author: fastman92\r\nhttp://fastman92.com\r\nfastman92@gmail.com";
            this.label7.Click += new System.EventHandler(this.label7_Click);
            // 
            // exitImmediatelyCheckBox
            // 
            this.exitImmediatelyCheckBox.AutoSize = true;
            this.exitImmediatelyCheckBox.Checked = true;
            this.exitImmediatelyCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.exitImmediatelyCheckBox.Location = new System.Drawing.Point(332, 346);
            this.exitImmediatelyCheckBox.Name = "exitImmediatelyCheckBox";
            this.exitImmediatelyCheckBox.Size = new System.Drawing.Size(134, 17);
            this.exitImmediatelyCheckBox.TabIndex = 42;
            this.exitImmediatelyCheckBox.Text = "Exit script immediately?";
            this.exitImmediatelyCheckBox.UseVisualStyleBackColor = true;
            this.exitImmediatelyCheckBox.CheckedChanged += new System.EventHandler(this.exitImmediatelyCheckBox_CheckedChanged);
            // 
            // startIDAserverButton
            // 
            this.startIDAserverButton.Enabled = false;
            this.startIDAserverButton.Location = new System.Drawing.Point(455, 62);
            this.startIDAserverButton.Name = "startIDAserverButton";
            this.startIDAserverButton.Size = new System.Drawing.Size(97, 23);
            this.startIDAserverButton.TabIndex = 16;
            this.startIDAserverButton.Text = "Start IDA server";
            this.startIDAserverButton.UseVisualStyleBackColor = true;
            this.startIDAserverButton.Click += new System.EventHandler(this.startIDAserverButton_Click);
            // 
            // InformationTextBox
            // 
            this.InformationTextBox.BackColor = System.Drawing.SystemColors.Window;
            this.InformationTextBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.InformationTextBox.Location = new System.Drawing.Point(142, 379);
            this.InformationTextBox.Multiline = true;
            this.InformationTextBox.Name = "InformationTextBox";
            this.InformationTextBox.ReadOnly = true;
            this.InformationTextBox.Size = new System.Drawing.Size(525, 225);
            this.InformationTextBox.TabIndex = 50;
            this.InformationTextBox.Text = "Informations";
            this.InformationTextBox.Click += new System.EventHandler(this.InformationTextBox_Click);
            // 
            // useDebugLibraryCheckBox
            // 
            this.useDebugLibraryCheckBox.AutoSize = true;
            this.useDebugLibraryCheckBox.Location = new System.Drawing.Point(332, 308);
            this.useDebugLibraryCheckBox.Name = "useDebugLibraryCheckBox";
            this.useDebugLibraryCheckBox.Size = new System.Drawing.Size(122, 17);
            this.useDebugLibraryCheckBox.TabIndex = 40;
            this.useDebugLibraryCheckBox.Text = "Use debug libraries?";
            this.useDebugLibraryCheckBox.UseVisualStyleBackColor = true;
            this.useDebugLibraryCheckBox.CheckedChanged += new System.EventHandler(this.useDebugLibraryCheckBox_CheckedChanged);
            // 
            // wakeUpScreenButton
            // 
            this.wakeUpScreenButton.Enabled = false;
            this.wakeUpScreenButton.Location = new System.Drawing.Point(6, 82);
            this.wakeUpScreenButton.Name = "wakeUpScreenButton";
            this.wakeUpScreenButton.Size = new System.Drawing.Size(97, 23);
            this.wakeUpScreenButton.TabIndex = 3;
            this.wakeUpScreenButton.Text = "Wake up device";
            this.wakeUpScreenButton.UseVisualStyleBackColor = true;
            this.wakeUpScreenButton.Click += new System.EventHandler(this.wakeUpScreenButton_Click);
            // 
            // forceContinueButton
            // 
            this.forceContinueButton.Enabled = false;
            this.forceContinueButton.Location = new System.Drawing.Point(332, 246);
            this.forceContinueButton.Name = "forceContinueButton";
            this.forceContinueButton.Size = new System.Drawing.Size(150, 23);
            this.forceContinueButton.TabIndex = 38;
            this.forceContinueButton.Text = "Force continue";
            this.forceContinueButton.UseVisualStyleBackColor = true;
            this.forceContinueButton.Click += new System.EventHandler(this.forceContinueButton_Click);
            // 
            // updateTheFLAandRunButton
            // 
            this.updateTheFLAandRunButton.Enabled = false;
            this.updateTheFLAandRunButton.Location = new System.Drawing.Point(519, 200);
            this.updateTheFLAandRunButton.Name = "updateTheFLAandRunButton";
            this.updateTheFLAandRunButton.Size = new System.Drawing.Size(150, 23);
            this.updateTheFLAandRunButton.TabIndex = 45;
            this.updateTheFLAandRunButton.Text = "Update the FLA and run";
            this.updateTheFLAandRunButton.UseVisualStyleBackColor = true;
            this.updateTheFLAandRunButton.Click += new System.EventHandler(this.updateTheFLAandRunButton_Click);
            // 
            // updateTheFLAbutton
            // 
            this.updateTheFLAbutton.Enabled = false;
            this.updateTheFLAbutton.Location = new System.Drawing.Point(519, 275);
            this.updateTheFLAbutton.Name = "updateTheFLAbutton";
            this.updateTheFLAbutton.Size = new System.Drawing.Size(150, 23);
            this.updateTheFLAbutton.TabIndex = 47;
            this.updateTheFLAbutton.Text = "Update the FLA";
            this.updateTheFLAbutton.UseVisualStyleBackColor = true;
            this.updateTheFLAbutton.Click += new System.EventHandler(this.updateTheFLAbutton_Click);
            // 
            // detectGameVersionButton
            // 
            this.detectGameVersionButton.Enabled = false;
            this.detectGameVersionButton.Location = new System.Drawing.Point(299, 62);
            this.detectGameVersionButton.Name = "detectGameVersionButton";
            this.detectGameVersionButton.Size = new System.Drawing.Size(150, 23);
            this.detectGameVersionButton.TabIndex = 15;
            this.detectGameVersionButton.Text = "Detect game version";
            this.detectGameVersionButton.UseVisualStyleBackColor = true;
            this.detectGameVersionButton.Click += new System.EventHandler(this.detectGameVersionButton_Click);
            // 
            // updateTheFLAandRunForDebuggingButton
            // 
            this.updateTheFLAandRunForDebuggingButton.Enabled = false;
            this.updateTheFLAandRunForDebuggingButton.Location = new System.Drawing.Point(519, 229);
            this.updateTheFLAandRunForDebuggingButton.Name = "updateTheFLAandRunForDebuggingButton";
            this.updateTheFLAandRunForDebuggingButton.Size = new System.Drawing.Size(150, 40);
            this.updateTheFLAandRunForDebuggingButton.TabIndex = 46;
            this.updateTheFLAandRunForDebuggingButton.Text = "Update the FLA and run for debugging";
            this.updateTheFLAandRunForDebuggingButton.UseVisualStyleBackColor = true;
            this.updateTheFLAandRunForDebuggingButton.Click += new System.EventHandler(this.updateTheFLAandRunForDebuggingButton_Click);
            // 
            // enableDeveloperOptionsButton
            // 
            this.enableDeveloperOptionsButton.Location = new System.Drawing.Point(376, 22);
            this.enableDeveloperOptionsButton.Name = "enableDeveloperOptionsButton";
            this.enableDeveloperOptionsButton.Size = new System.Drawing.Size(172, 23);
            this.enableDeveloperOptionsButton.TabIndex = 9;
            this.enableDeveloperOptionsButton.Text = "Click to enable developer options";
            this.enableDeveloperOptionsButton.UseVisualStyleBackColor = true;
            this.enableDeveloperOptionsButton.Click += new System.EventHandler(this.enableDeveloperOptionsButton_Click);
            // 
            // start_strcpy_button
            // 
            this.start_strcpy_button.Enabled = false;
            this.start_strcpy_button.Location = new System.Drawing.Point(6, 169);
            this.start_strcpy_button.Name = "start_strcpy_button";
            this.start_strcpy_button.Size = new System.Drawing.Size(97, 23);
            this.start_strcpy_button.TabIndex = 6;
            this.start_strcpy_button.Text = "Start Scrcpy";
            this.start_strcpy_button.UseVisualStyleBackColor = true;
            this.start_strcpy_button.Click += new System.EventHandler(this.start_strcpy_button_Click);
            // 
            // runGameForDebuggingAndContinueButton
            // 
            this.runGameForDebuggingAndContinueButton.Enabled = false;
            this.runGameForDebuggingAndContinueButton.Location = new System.Drawing.Point(332, 200);
            this.runGameForDebuggingAndContinueButton.Name = "runGameForDebuggingAndContinueButton";
            this.runGameForDebuggingAndContinueButton.Size = new System.Drawing.Size(150, 40);
            this.runGameForDebuggingAndContinueButton.TabIndex = 37;
            this.runGameForDebuggingAndContinueButton.Text = "Run game for debugging and continue";
            this.runGameForDebuggingAndContinueButton.UseVisualStyleBackColor = true;
            this.runGameForDebuggingAndContinueButton.Click += new System.EventHandler(this.runGameForDebuggingAndContinueButton_Click);
            // 
            // openExternalDirectoryButton
            // 
            this.openExternalDirectoryButton.Enabled = false;
            this.openExternalDirectoryButton.Location = new System.Drawing.Point(142, 200);
            this.openExternalDirectoryButton.Name = "openExternalDirectoryButton";
            this.openExternalDirectoryButton.Size = new System.Drawing.Size(133, 23);
            this.openExternalDirectoryButton.TabIndex = 25;
            this.openExternalDirectoryButton.Text = "Open external directory";
            this.openExternalDirectoryButton.UseVisualStyleBackColor = true;
            this.openExternalDirectoryButton.Click += new System.EventHandler(this.openExternalDirectoryButton_Click);
            // 
            // includeLibCLEOcheckBox
            // 
            this.includeLibCLEOcheckBox.AutoSize = true;
            this.includeLibCLEOcheckBox.Location = new System.Drawing.Point(143, 327);
            this.includeLibCLEOcheckBox.Name = "includeLibCLEOcheckBox";
            this.includeLibCLEOcheckBox.Size = new System.Drawing.Size(108, 17);
            this.includeLibCLEOcheckBox.TabIndex = 34;
            this.includeLibCLEOcheckBox.Text = "Include libcleo.so";
            this.includeLibCLEOcheckBox.UseVisualStyleBackColor = true;
            this.includeLibCLEOcheckBox.CheckedChanged += new System.EventHandler(this.includeLibCLEOcheckBox_CheckedChanged);
            // 
            // additionalSOfileTextBox
            // 
            this.additionalSOfileTextBox.Location = new System.Drawing.Point(142, 258);
            this.additionalSOfileTextBox.Name = "additionalSOfileTextBox";
            this.additionalSOfileTextBox.Size = new System.Drawing.Size(101, 20);
            this.additionalSOfileTextBox.TabIndex = 28;
            this.additionalSOfileTextBox.TextChanged += new System.EventHandler(this.additionalSOfileTextBox_TextChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(140, 229);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(102, 26);
            this.label8.TabIndex = 27;
            this.label8.Text = "Additional SO files\r\nSeparated by space";
            // 
            // updateAdditionalFileButton
            // 
            this.updateAdditionalFileButton.Enabled = false;
            this.updateAdditionalFileButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.updateAdditionalFileButton.Location = new System.Drawing.Point(248, 280);
            this.updateAdditionalFileButton.Name = "updateAdditionalFileButton";
            this.updateAdditionalFileButton.Size = new System.Drawing.Size(45, 20);
            this.updateAdditionalFileButton.TabIndex = 32;
            this.updateAdditionalFileButton.Text = "UPDT";
            this.updateAdditionalFileButton.UseVisualStyleBackColor = true;
            this.updateAdditionalFileButton.Click += new System.EventHandler(this.updateAdditionalFileButton_Click);
            // 
            // deleteAdditionalFileButton
            // 
            this.deleteAdditionalFileButton.Enabled = false;
            this.deleteAdditionalFileButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.deleteAdditionalFileButton.Location = new System.Drawing.Point(197, 280);
            this.deleteAdditionalFileButton.Name = "deleteAdditionalFileButton";
            this.deleteAdditionalFileButton.Size = new System.Drawing.Size(46, 20);
            this.deleteAdditionalFileButton.TabIndex = 31;
            this.deleteAdditionalFileButton.Text = "DEL";
            this.deleteAdditionalFileButton.UseVisualStyleBackColor = true;
            this.deleteAdditionalFileButton.Click += new System.EventHandler(this.deleteAdditionalFileButton_Click);
            // 
            // clearAddtionalFilenameButton
            // 
            this.clearAddtionalFilenameButton.Enabled = false;
            this.clearAddtionalFilenameButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.clearAddtionalFilenameButton.Location = new System.Drawing.Point(142, 280);
            this.clearAddtionalFilenameButton.Name = "clearAddtionalFilenameButton";
            this.clearAddtionalFilenameButton.Size = new System.Drawing.Size(46, 20);
            this.clearAddtionalFilenameButton.TabIndex = 30;
            this.clearAddtionalFilenameButton.Text = "CLR";
            this.clearAddtionalFilenameButton.UseVisualStyleBackColor = true;
            this.clearAddtionalFilenameButton.Click += new System.EventHandler(this.clearAddtionalFilenameButton_Click);
            // 
            // takeScreenshotButton
            // 
            this.takeScreenshotButton.Location = new System.Drawing.Point(6, 111);
            this.takeScreenshotButton.Name = "takeScreenshotButton";
            this.takeScreenshotButton.Size = new System.Drawing.Size(97, 23);
            this.takeScreenshotButton.TabIndex = 4;
            this.takeScreenshotButton.Text = "Take screenshot";
            this.takeScreenshotButton.UseVisualStyleBackColor = true;
            this.takeScreenshotButton.Click += new System.EventHandler(this.takeScreenshotButton_Click);
            // 
            // seeScreenshotsButton
            // 
            this.seeScreenshotsButton.Location = new System.Drawing.Point(6, 140);
            this.seeScreenshotsButton.Name = "seeScreenshotsButton";
            this.seeScreenshotsButton.Size = new System.Drawing.Size(97, 23);
            this.seeScreenshotsButton.TabIndex = 5;
            this.seeScreenshotsButton.Text = "See screenshots";
            this.seeScreenshotsButton.UseVisualStyleBackColor = true;
            this.seeScreenshotsButton.Click += new System.EventHandler(this.seeScreenshotsButton_Click);
            // 
            // helpButton
            // 
            this.helpButton.Location = new System.Drawing.Point(572, 56);
            this.helpButton.Name = "helpButton";
            this.helpButton.Size = new System.Drawing.Size(97, 20);
            this.helpButton.TabIndex = 18;
            this.helpButton.Text = "HELP";
            this.helpButton.UseVisualStyleBackColor = true;
            this.helpButton.Click += new System.EventHandler(this.helpButton_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(6, 25);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(97, 23);
            this.button2.TabIndex = 1;
            this.button2.Text = "Command prompt";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // FLAinformationLabel
            // 
            this.FLAinformationLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.FLAinformationLabel.Location = new System.Drawing.Point(332, 6);
            this.FLAinformationLabel.Name = "FLAinformationLabel";
            this.FLAinformationLabel.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.FLAinformationLabel.Size = new System.Drawing.Size(216, 13);
            this.FLAinformationLabel.TabIndex = 8;
            this.FLAinformationLabel.Text = "FLAinformationLabel";
            this.FLAinformationLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // createModifiedAPKbutton
            // 
            this.createModifiedAPKbutton.Enabled = false;
            this.createModifiedAPKbutton.Location = new System.Drawing.Point(519, 304);
            this.createModifiedAPKbutton.Name = "createModifiedAPKbutton";
            this.createModifiedAPKbutton.Size = new System.Drawing.Size(150, 23);
            this.createModifiedAPKbutton.TabIndex = 48;
            this.createModifiedAPKbutton.Text = "Create modified APK";
            this.createModifiedAPKbutton.UseVisualStyleBackColor = true;
            this.createModifiedAPKbutton.Click += new System.EventHandler(this.updateModifiedAPKbutton_Click);
            // 
            // includeTheFLApluginCheckBox
            // 
            this.includeTheFLApluginCheckBox.AutoSize = true;
            this.includeTheFLApluginCheckBox.Checked = true;
            this.includeTheFLApluginCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.includeTheFLApluginCheckBox.Location = new System.Drawing.Point(143, 304);
            this.includeTheFLApluginCheckBox.Name = "includeTheFLApluginCheckBox";
            this.includeTheFLApluginCheckBox.Size = new System.Drawing.Size(132, 17);
            this.includeTheFLApluginCheckBox.TabIndex = 33;
            this.includeTheFLApluginCheckBox.Text = "Include the FLA plugin";
            this.includeTheFLApluginCheckBox.UseVisualStyleBackColor = true;
            // 
            // updateAdditionalFileAndRunButton
            // 
            this.updateAdditionalFileAndRunButton.Enabled = false;
            this.updateAdditionalFileAndRunButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.updateAdditionalFileAndRunButton.Location = new System.Drawing.Point(248, 258);
            this.updateAdditionalFileAndRunButton.Name = "updateAdditionalFileAndRunButton";
            this.updateAdditionalFileAndRunButton.Size = new System.Drawing.Size(45, 20);
            this.updateAdditionalFileAndRunButton.TabIndex = 29;
            this.updateAdditionalFileAndRunButton.Text = "UPaR";
            this.updateAdditionalFileAndRunButton.UseVisualStyleBackColor = true;
            this.updateAdditionalFileAndRunButton.Click += new System.EventHandler(this.updateAdditionalFileAndRunButton_Click);
            // 
            // PortLabel
            // 
            this.PortLabel.AutoSize = true;
            this.PortLabel.Location = new System.Drawing.Point(456, 87);
            this.PortLabel.Name = "PortLabel";
            this.PortLabel.Size = new System.Drawing.Size(26, 13);
            this.PortLabel.TabIndex = 17;
            this.PortLabel.Text = "Port";
            // 
            // extractGameDataButton
            // 
            this.extractGameDataButton.Enabled = false;
            this.extractGameDataButton.Location = new System.Drawing.Point(519, 333);
            this.extractGameDataButton.Name = "extractGameDataButton";
            this.extractGameDataButton.Size = new System.Drawing.Size(150, 40);
            this.extractGameDataButton.TabIndex = 49;
            this.extractGameDataButton.Text = "Extract game data to root directory";
            this.extractGameDataButton.UseVisualStyleBackColor = true;
            // 
            // apkUsingAndroidUnprotected
            // 
            this.apkUsingAndroidUnprotected.AutoSize = true;
            this.apkUsingAndroidUnprotected.Location = new System.Drawing.Point(332, 327);
            this.apkUsingAndroidUnprotected.Name = "apkUsingAndroidUnprotected";
            this.apkUsingAndroidUnprotected.Size = new System.Drawing.Size(187, 17);
            this.apkUsingAndroidUnprotected.TabIndex = 41;
            this.apkUsingAndroidUnprotected.Text = "APK is using Android_unprotected";
            this.apkUsingAndroidUnprotected.UseVisualStyleBackColor = true;
            this.apkUsingAndroidUnprotected.CheckedChanged += new System.EventHandler(this.apkUsingAndroidUnprotected_CheckedChanged);
            // 
            // externalDirectoryButton
            // 
            this.externalDirectoryButton.Enabled = false;
            this.externalDirectoryButton.Location = new System.Drawing.Point(274, 200);
            this.externalDirectoryButton.Name = "externalDirectoryButton";
            this.externalDirectoryButton.Size = new System.Drawing.Size(19, 23);
            this.externalDirectoryButton.TabIndex = 26;
            this.externalDirectoryButton.Text = "?";
            this.externalDirectoryButton.UseVisualStyleBackColor = true;
            this.externalDirectoryButton.Click += new System.EventHandler(this.externalDirectoryButton_Click);
            // 
            // developmentPackageNamesCheckbox
            // 
            this.developmentPackageNamesCheckbox.AutoSize = true;
            this.developmentPackageNamesCheckbox.Location = new System.Drawing.Point(376, 44);
            this.developmentPackageNamesCheckbox.Name = "developmentPackageNamesCheckbox";
            this.developmentPackageNamesCheckbox.Size = new System.Drawing.Size(168, 17);
            this.developmentPackageNamesCheckbox.TabIndex = 51;
            this.developmentPackageNamesCheckbox.Text = "Development package names";
            this.developmentPackageNamesCheckbox.UseVisualStyleBackColor = true;
            this.developmentPackageNamesCheckbox.CheckedChanged += new System.EventHandler(this.developmentPackageNamesCheckbox_CheckedChanged);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.SelectedPath = "";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(680, 611);
            this.Controls.Add(this.developmentPackageNamesCheckbox);
            this.Controls.Add(this.externalDirectoryButton);
            this.Controls.Add(this.apkUsingAndroidUnprotected);
            this.Controls.Add(this.extractGameDataButton);
            this.Controls.Add(this.PortLabel);
            this.Controls.Add(this.updateAdditionalFileAndRunButton);
            this.Controls.Add(this.includeTheFLApluginCheckBox);
            this.Controls.Add(this.createModifiedAPKbutton);
            this.Controls.Add(this.FLAinformationLabel);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.helpButton);
            this.Controls.Add(this.seeScreenshotsButton);
            this.Controls.Add(this.takeScreenshotButton);
            this.Controls.Add(this.clearAddtionalFilenameButton);
            this.Controls.Add(this.deleteAdditionalFileButton);
            this.Controls.Add(this.updateAdditionalFileButton);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.additionalSOfileTextBox);
            this.Controls.Add(this.includeLibCLEOcheckBox);
            this.Controls.Add(this.openExternalDirectoryButton);
            this.Controls.Add(this.runGameForDebuggingAndContinueButton);
            this.Controls.Add(this.start_strcpy_button);
            this.Controls.Add(this.enableDeveloperOptionsButton);
            this.Controls.Add(this.updateTheFLAandRunForDebuggingButton);
            this.Controls.Add(this.detectGameVersionButton);
            this.Controls.Add(this.updateTheFLAbutton);
            this.Controls.Add(this.updateTheFLAandRunButton);
            this.Controls.Add(this.forceContinueButton);
            this.Controls.Add(this.wakeUpScreenButton);
            this.Controls.Add(this.useDebugLibraryCheckBox);
            this.Controls.Add(this.startIDAserverButton);
            this.Controls.Add(this.exitImmediatelyCheckBox);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.pullGameLibraryFileToPCbutton);
            this.Controls.Add(this.runGameForDebuggingButton);
            this.Controls.Add(this.stopGameButton);
            this.Controls.Add(this.runGameButton);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.updateLibrariesButton);
            this.Controls.Add(this.updateLibrariesAndRunButton);
            this.Controls.Add(this.applyPluginLoaderInstallerButton);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.directoryPathTextBox);
            this.Controls.Add(this.gameComboBox);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.gameVersionComboBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.fastman92_logcat_button);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.InformationTextBox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Android plugin deployment solution";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_Closed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button fastman92_logcat_button;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox gameVersionComboBox;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox gameComboBox;
        private dnGREP.FileFolderDialog openFileDialog1;
        private System.Windows.Forms.TextBox directoryPathTextBox;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button applyPluginLoaderInstallerButton;
        private System.Windows.Forms.Button updateLibrariesAndRunButton;
        private System.Windows.Forms.Button updateLibrariesButton;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button runGameButton;
        private System.Windows.Forms.Button stopGameButton;
        private System.Windows.Forms.Button runGameForDebuggingButton;
        private System.Windows.Forms.Button pullGameLibraryFileToPCbutton;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.CheckBox exitImmediatelyCheckBox;
        private System.Windows.Forms.Button startIDAserverButton;
        private System.Windows.Forms.CheckBox useDebugLibraryCheckBox;
        private System.Windows.Forms.Button wakeUpScreenButton;
        private System.Windows.Forms.Button forceContinueButton;
        private System.Windows.Forms.Button updateTheFLAandRunButton;
        private System.Windows.Forms.Button updateTheFLAbutton;
        private System.Windows.Forms.Button detectGameVersionButton;
        private System.Windows.Forms.Button updateTheFLAandRunForDebuggingButton;
        private System.Windows.Forms.Button enableDeveloperOptionsButton;
        private System.Windows.Forms.Button start_strcpy_button;
        private System.Windows.Forms.Button runGameForDebuggingAndContinueButton;
        private System.Windows.Forms.Button openExternalDirectoryButton;
        public System.Windows.Forms.CheckBox includeLibCLEOcheckBox;
        public System.Windows.Forms.TextBox additionalSOfileTextBox;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button updateAdditionalFileButton;
        private System.Windows.Forms.Button deleteAdditionalFileButton;
        private System.Windows.Forms.Button clearAddtionalFilenameButton;
        private System.Windows.Forms.Button takeScreenshotButton;
        private System.Windows.Forms.Button seeScreenshotsButton;
        private System.Windows.Forms.Button helpButton;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label FLAinformationLabel;
        private System.Windows.Forms.Button createModifiedAPKbutton;
        public System.Windows.Forms.CheckBox includeTheFLApluginCheckBox;
        private System.Windows.Forms.TextBox InformationTextBox;
        private System.Windows.Forms.Button updateAdditionalFileAndRunButton;
        private System.Windows.Forms.Label PortLabel;
        private System.Windows.Forms.Button extractGameDataButton;
        private System.Windows.Forms.CheckBox apkUsingAndroidUnprotected;
        private System.Windows.Forms.Button externalDirectoryButton;
        private System.Windows.Forms.CheckBox developmentPackageNamesCheckbox;
    }
}


namespace Android_plugin_deployment_solution
{
    partial class GetOriginalGameLibForm
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
            this.label1 = new System.Windows.Forms.Label();
            this.getSOlibraryFromAPKfileButton = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.nameOfFileNeededLabel = new System.Windows.Forms.Label();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.getSOlibraryFromAPKfileOnDeviceButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(10, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(247, 40);
            this.label1.TabIndex = 0;
            this.label1.Text = "There are two ways to get an original game library SO file to the computer for fu" +
    "rther processing.";
            // 
            // getSOlibraryFromAPKfileButton
            // 
            this.getSOlibraryFromAPKfileButton.Location = new System.Drawing.Point(10, 309);
            this.getSOlibraryFromAPKfileButton.Name = "getSOlibraryFromAPKfileButton";
            this.getSOlibraryFromAPKfileButton.Size = new System.Drawing.Size(247, 23);
            this.getSOlibraryFromAPKfileButton.TabIndex = 1;
            this.getSOlibraryFromAPKfileButton.Text = "Get game SO library from APK file";
            this.getSOlibraryFromAPKfileButton.UseVisualStyleBackColor = true;
            this.getSOlibraryFromAPKfileButton.Click += new System.EventHandler(this.getSOlibraryFromAPKfile_Click);
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(7, 255);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(250, 51);
            this.label2.TabIndex = 3;
            this.label2.Text = "You will have to select the APK file of your game, from which the SO library will" +
    " be extracted into APDS working directory";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label3.Location = new System.Drawing.Point(76, 90);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(106, 20);
            this.label3.TabIndex = 4;
            this.label3.Text = "FIRST WAY";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label4.Location = new System.Drawing.Point(66, 235);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(128, 20);
            this.label4.TabIndex = 5;
            this.label4.Text = "SECOND WAY";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(7, 49);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(105, 13);
            this.label5.TabIndex = 6;
            this.label5.Text = "Name of file needed:";
            // 
            // nameOfFileNeededLabel
            // 
            this.nameOfFileNeededLabel.AutoSize = true;
            this.nameOfFileNeededLabel.Location = new System.Drawing.Point(118, 49);
            this.nameOfFileNeededLabel.Name = "nameOfFileNeededLabel";
            this.nameOfFileNeededLabel.Size = new System.Drawing.Size(35, 13);
            this.nameOfFileNeededLabel.TabIndex = 7;
            this.nameOfFileNeededLabel.Text = "label6";
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(10, 110);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(247, 57);
            this.label6.TabIndex = 8;
            this.label6.Text = "The SO file and APK package will be imported from your Android device. Rooted dev" +
    "ice is required. Remember that you may only use this option if APK on your Andro" +
    "id device is still original.";
            // 
            // label7
            // 
            this.label7.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label7.Location = new System.Drawing.Point(10, 209);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(247, 10);
            this.label7.TabIndex = 9;
            // 
            // getSOlibraryFromAPKfileOnDeviceButton
            // 
            this.getSOlibraryFromAPKfileOnDeviceButton.Location = new System.Drawing.Point(10, 170);
            this.getSOlibraryFromAPKfileOnDeviceButton.Name = "getSOlibraryFromAPKfileOnDeviceButton";
            this.getSOlibraryFromAPKfileOnDeviceButton.Size = new System.Drawing.Size(247, 36);
            this.getSOlibraryFromAPKfileOnDeviceButton.TabIndex = 10;
            this.getSOlibraryFromAPKfileOnDeviceButton.Text = "Get game SO library and APK package from device";
            this.getSOlibraryFromAPKfileOnDeviceButton.UseVisualStyleBackColor = true;
            this.getSOlibraryFromAPKfileOnDeviceButton.Click += new System.EventHandler(this.getSOlibraryFromAPKfileOnDeviceButton_Click);
            // 
            // GetOriginalGameLibForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(269, 339);
            this.Controls.Add(this.getSOlibraryFromAPKfileOnDeviceButton);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.nameOfFileNeededLabel);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.getSOlibraryFromAPKfileButton);
            this.Controls.Add(this.label1);
            this.Name = "GetOriginalGameLibForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Import game SO library";
            this.Load += new System.EventHandler(this.GetOriginalGameLibForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button getSOlibraryFromAPKfileButton;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label nameOfFileNeededLabel;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button getSOlibraryFromAPKfileOnDeviceButton;
    }
}
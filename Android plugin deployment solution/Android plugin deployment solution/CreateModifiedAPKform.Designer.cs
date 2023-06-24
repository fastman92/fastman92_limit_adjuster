namespace Android_plugin_deployment_solution
{
    partial class CreateModifiedAPKform
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
            this.button1 = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.newAPKpath = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.button3 = new System.Windows.Forms.Button();
            this.InformationTextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.originalAPKfilePath = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(439, 64);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(97, 20);
            this.button1.TabIndex = 11;
            this.button1.Text = "Select";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label3.Location = new System.Drawing.Point(179, 41);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(173, 20);
            this.label3.TabIndex = 12;
            this.label3.Text = "SELECT INPUT APK";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label4.Location = new System.Drawing.Point(188, 103);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(164, 20);
            this.label4.TabIndex = 13;
            this.label4.Text = "CREATE NEW APK";
            // 
            // newAPKpath
            // 
            this.newAPKpath.Location = new System.Drawing.Point(14, 126);
            this.newAPKpath.Name = "newAPKpath";
            this.newAPKpath.Size = new System.Drawing.Size(422, 20);
            this.newAPKpath.TabIndex = 14;
            this.newAPKpath.TextChanged += new System.EventHandler(this.newAPKpath_TextChanged);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(439, 126);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(97, 20);
            this.button2.TabIndex = 15;
            this.button2.Text = "Select";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "APK archive|*.apk|All files|*.*";
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.Filter = "APK archive|*.apk|All files|*.*";
            // 
            // button3
            // 
            this.button3.Enabled = false;
            this.button3.Location = new System.Drawing.Point(239, 152);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 16;
            this.button3.Text = "CREATE";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // InformationTextBox
            // 
            this.InformationTextBox.Location = new System.Drawing.Point(11, 178);
            this.InformationTextBox.Multiline = true;
            this.InformationTextBox.Name = "InformationTextBox";
            this.InformationTextBox.ReadOnly = true;
            this.InformationTextBox.Size = new System.Drawing.Size(525, 215);
            this.InformationTextBox.TabIndex = 23;
            this.InformationTextBox.Text = "Informations";
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(73, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(415, 32);
            this.label1.TabIndex = 24;
            this.label1.Text = "New APK package, which includes the FLA and other libraries can be created and th" +
    "en installed on the Android device. No root is required to install a new APK pac" +
    "kage.";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // originalAPKfilePath
            // 
            this.originalAPKfilePath.Location = new System.Drawing.Point(14, 64);
            this.originalAPKfilePath.Name = "originalAPKfilePath";
            this.originalAPKfilePath.Size = new System.Drawing.Size(422, 20);
            this.originalAPKfilePath.TabIndex = 25;
            // 
            // CreateModifiedAPKform
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(550, 401);
            this.Controls.Add(this.originalAPKfilePath);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.InformationTextBox);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.newAPKpath);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.button1);
            this.Name = "CreateModifiedAPKform";
            this.Text = "Create modified APK";
            this.Load += new System.EventHandler(this.CreateModifiedAPKform_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox newAPKpath;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TextBox InformationTextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox originalAPKfilePath;
    }
}
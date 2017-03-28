namespace Rocket_Stabilization_Configuration
{
    partial class RocketConfig
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
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.Servo1Offset = new System.Windows.Forms.TextBox();
            this.Servo2Pin = new System.Windows.Forms.TextBox();
            this.Servo1Pin = new System.Windows.Forms.TextBox();
            this.Servo4Pin = new System.Windows.Forms.TextBox();
            this.Servo3Pin = new System.Windows.Forms.TextBox();
            this.Servo2Offset = new System.Windows.Forms.TextBox();
            this.Servo3Offset = new System.Windows.Forms.TextBox();
            this.Servo4Offset = new System.Windows.Forms.TextBox();
            this.RollOffset = new System.Windows.Forms.TextBox();
            this.PitchOffset = new System.Windows.Forms.TextBox();
            this.YawOffset = new System.Windows.Forms.TextBox();
            this.ServoPinsLabel = new System.Windows.Forms.Label();
            this.Servo1Label = new System.Windows.Forms.Label();
            this.Servo2Label = new System.Windows.Forms.Label();
            this.Servo3Label = new System.Windows.Forms.Label();
            this.Servo4Label = new System.Windows.Forms.Label();
            this.Servo4OffsetLabel = new System.Windows.Forms.Label();
            this.Servo3OffsetLabel = new System.Windows.Forms.Label();
            this.Servo2OffsetLabel = new System.Windows.Forms.Label();
            this.Servo1OffsetLabel = new System.Windows.Forms.Label();
            this.RollOffsetLabel = new System.Windows.Forms.Label();
            this.PitchOffsetLabel = new System.Windows.Forms.Label();
            this.YawOffsetLabel = new System.Windows.Forms.Label();
            this.ServoOffsetLabel = new System.Windows.Forms.Label();
            this.SensorDataLabel = new System.Windows.Forms.Label();
            this.Mahony = new System.Windows.Forms.RadioButton();
            this.Madgwick = new System.Windows.Forms.RadioButton();
            this.Off = new System.Windows.Forms.RadioButton();
            this.On = new System.Windows.Forms.RadioButton();
            this.SerialDebug = new System.Windows.Forms.GroupBox();
            this.RawAccel = new System.Windows.Forms.RadioButton();
            this.RawGyro = new System.Windows.Forms.RadioButton();
            this.RawMag = new System.Windows.Forms.RadioButton();
            this.Quat = new System.Windows.Forms.RadioButton();
            this.YPR = new System.Windows.Forms.RadioButton();
            this.Alt = new System.Windows.Forms.RadioButton();
            this.Filtering = new System.Windows.Forms.GroupBox();
            this.Datalogging = new System.Windows.Forms.GroupBox();
            this.menuStrip1.SuspendLayout();
            this.SerialDebug.SuspendLayout();
            this.Filtering.SuspendLayout();
            this.Datalogging.SuspendLayout();
            this.SuspendLayout();
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.saveToolStripMenuItem,
            this.loadToolStripMenuItem});
            this.fileToolStripMenuItem.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.fileToolStripMenuItem.ForeColor = System.Drawing.Color.Gainsboro;
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(46, 25);
            this.fileToolStripMenuItem.Text = "File";
            this.fileToolStripMenuItem.Click += new System.EventHandler(this.fileToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.saveToolStripMenuItem.ForeColor = System.Drawing.Color.Silver;
            this.saveToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(168, 26);
            this.saveToolStripMenuItem.Text = "Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.loadToolStripMenuItem.ForeColor = System.Drawing.Color.Silver;
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(168, 26);
            this.loadToolStripMenuItem.Text = "Load";
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(617, 29);
            this.menuStrip1.TabIndex = 16;
            this.menuStrip1.Text = "menuStrip1";
            this.menuStrip1.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.menuStrip1_ItemClicked);
            // 
            // Servo1Offset
            // 
            this.Servo1Offset.AcceptsTab = true;
            this.Servo1Offset.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.Servo1Offset.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Servo1Offset.Font = new System.Drawing.Font("Segoe UI Emoji", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo1Offset.ForeColor = System.Drawing.SystemColors.Window;
            this.Servo1Offset.Location = new System.Drawing.Point(127, 207);
            this.Servo1Offset.Name = "Servo1Offset";
            this.Servo1Offset.Size = new System.Drawing.Size(86, 29);
            this.Servo1Offset.TabIndex = 17;
            this.Servo1Offset.Text = "0";
            this.Servo1Offset.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.Servo1Offset.TextChanged += new System.EventHandler(this.textBox2_TextChanged_1);
            // 
            // Servo2Pin
            // 
            this.Servo2Pin.AcceptsTab = true;
            this.Servo2Pin.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.Servo2Pin.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Servo2Pin.Font = new System.Drawing.Font("Segoe UI Emoji", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo2Pin.ForeColor = System.Drawing.SystemColors.Window;
            this.Servo2Pin.Location = new System.Drawing.Point(225, 106);
            this.Servo2Pin.Name = "Servo2Pin";
            this.Servo2Pin.Size = new System.Drawing.Size(86, 29);
            this.Servo2Pin.TabIndex = 19;
            this.Servo2Pin.Text = "5";
            this.Servo2Pin.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.Servo2Pin.TextChanged += new System.EventHandler(this.textBox3_TextChanged_1);
            // 
            // Servo1Pin
            // 
            this.Servo1Pin.AcceptsTab = true;
            this.Servo1Pin.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.Servo1Pin.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Servo1Pin.Font = new System.Drawing.Font("Segoe UI Emoji", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo1Pin.ForeColor = System.Drawing.SystemColors.Window;
            this.Servo1Pin.Location = new System.Drawing.Point(133, 106);
            this.Servo1Pin.Name = "Servo1Pin";
            this.Servo1Pin.Size = new System.Drawing.Size(86, 29);
            this.Servo1Pin.TabIndex = 18;
            this.Servo1Pin.Text = "3";
            this.Servo1Pin.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.Servo1Pin.TextChanged += new System.EventHandler(this.textBox4_TextChanged_1);
            // 
            // Servo4Pin
            // 
            this.Servo4Pin.AcceptsTab = true;
            this.Servo4Pin.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.Servo4Pin.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Servo4Pin.Font = new System.Drawing.Font("Segoe UI Emoji", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo4Pin.ForeColor = System.Drawing.SystemColors.Window;
            this.Servo4Pin.Location = new System.Drawing.Point(409, 106);
            this.Servo4Pin.Name = "Servo4Pin";
            this.Servo4Pin.Size = new System.Drawing.Size(86, 29);
            this.Servo4Pin.TabIndex = 21;
            this.Servo4Pin.Text = "11";
            this.Servo4Pin.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.Servo4Pin.TextChanged += new System.EventHandler(this.textBox5_TextChanged_1);
            // 
            // Servo3Pin
            // 
            this.Servo3Pin.AcceptsTab = true;
            this.Servo3Pin.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.Servo3Pin.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Servo3Pin.Font = new System.Drawing.Font("Segoe UI Emoji", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo3Pin.ForeColor = System.Drawing.SystemColors.Window;
            this.Servo3Pin.Location = new System.Drawing.Point(317, 106);
            this.Servo3Pin.Name = "Servo3Pin";
            this.Servo3Pin.Size = new System.Drawing.Size(86, 29);
            this.Servo3Pin.TabIndex = 20;
            this.Servo3Pin.Text = "9";
            this.Servo3Pin.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.Servo3Pin.TextChanged += new System.EventHandler(this.textBox6_TextChanged_1);
            // 
            // Servo2Offset
            // 
            this.Servo2Offset.AcceptsTab = true;
            this.Servo2Offset.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.Servo2Offset.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Servo2Offset.Font = new System.Drawing.Font("Segoe UI Emoji", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo2Offset.ForeColor = System.Drawing.SystemColors.Window;
            this.Servo2Offset.Location = new System.Drawing.Point(219, 207);
            this.Servo2Offset.Name = "Servo2Offset";
            this.Servo2Offset.Size = new System.Drawing.Size(86, 29);
            this.Servo2Offset.TabIndex = 22;
            this.Servo2Offset.Text = "0";
            this.Servo2Offset.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.Servo2Offset.TextChanged += new System.EventHandler(this.textBox1_TextChanged_1);
            // 
            // Servo3Offset
            // 
            this.Servo3Offset.AcceptsTab = true;
            this.Servo3Offset.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.Servo3Offset.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Servo3Offset.Font = new System.Drawing.Font("Segoe UI Emoji", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo3Offset.ForeColor = System.Drawing.SystemColors.Window;
            this.Servo3Offset.Location = new System.Drawing.Point(311, 207);
            this.Servo3Offset.Name = "Servo3Offset";
            this.Servo3Offset.Size = new System.Drawing.Size(86, 29);
            this.Servo3Offset.TabIndex = 23;
            this.Servo3Offset.Text = "0";
            this.Servo3Offset.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.Servo3Offset.TextChanged += new System.EventHandler(this.textBox7_TextChanged_1);
            // 
            // Servo4Offset
            // 
            this.Servo4Offset.AcceptsTab = true;
            this.Servo4Offset.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.Servo4Offset.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Servo4Offset.Font = new System.Drawing.Font("Segoe UI Emoji", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo4Offset.ForeColor = System.Drawing.SystemColors.Window;
            this.Servo4Offset.Location = new System.Drawing.Point(401, 207);
            this.Servo4Offset.Name = "Servo4Offset";
            this.Servo4Offset.Size = new System.Drawing.Size(86, 29);
            this.Servo4Offset.TabIndex = 24;
            this.Servo4Offset.Text = "0";
            this.Servo4Offset.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.Servo4Offset.TextChanged += new System.EventHandler(this.textBox8_TextChanged_1);
            // 
            // RollOffset
            // 
            this.RollOffset.AcceptsTab = true;
            this.RollOffset.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.RollOffset.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.RollOffset.Font = new System.Drawing.Font("Segoe UI Emoji", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RollOffset.ForeColor = System.Drawing.SystemColors.Window;
            this.RollOffset.Location = new System.Drawing.Point(357, 314);
            this.RollOffset.Name = "RollOffset";
            this.RollOffset.Size = new System.Drawing.Size(86, 29);
            this.RollOffset.TabIndex = 28;
            this.RollOffset.Text = "0";
            this.RollOffset.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.RollOffset.TextChanged += new System.EventHandler(this.textBox13_TextChanged_1);
            // 
            // PitchOffset
            // 
            this.PitchOffset.AcceptsTab = true;
            this.PitchOffset.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.PitchOffset.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.PitchOffset.Font = new System.Drawing.Font("Segoe UI Emoji", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PitchOffset.ForeColor = System.Drawing.SystemColors.Window;
            this.PitchOffset.Location = new System.Drawing.Point(265, 314);
            this.PitchOffset.Name = "PitchOffset";
            this.PitchOffset.Size = new System.Drawing.Size(86, 29);
            this.PitchOffset.TabIndex = 27;
            this.PitchOffset.Text = "0";
            this.PitchOffset.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.PitchOffset.TextChanged += new System.EventHandler(this.textBox14_TextChanged_1);
            // 
            // YawOffset
            // 
            this.YawOffset.AcceptsTab = true;
            this.YawOffset.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.YawOffset.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.YawOffset.Font = new System.Drawing.Font("Segoe UI Emoji", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.YawOffset.ForeColor = System.Drawing.SystemColors.Window;
            this.YawOffset.Location = new System.Drawing.Point(173, 314);
            this.YawOffset.Name = "YawOffset";
            this.YawOffset.Size = new System.Drawing.Size(86, 29);
            this.YawOffset.TabIndex = 26;
            this.YawOffset.Text = "0";
            this.YawOffset.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.YawOffset.TextChanged += new System.EventHandler(this.textBox15_TextChanged_1);
            // 
            // ServoPinsLabel
            // 
            this.ServoPinsLabel.AutoSize = true;
            this.ServoPinsLabel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ServoPinsLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.ServoPinsLabel.Location = new System.Drawing.Point(271, 52);
            this.ServoPinsLabel.Name = "ServoPinsLabel";
            this.ServoPinsLabel.Size = new System.Drawing.Size(90, 21);
            this.ServoPinsLabel.TabIndex = 65;
            this.ServoPinsLabel.Text = "Servo Pins";
            this.ServoPinsLabel.Click += new System.EventHandler(this.label1_Click);
            // 
            // Servo1Label
            // 
            this.Servo1Label.AutoSize = true;
            this.Servo1Label.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo1Label.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.Servo1Label.Location = new System.Drawing.Point(145, 82);
            this.Servo1Label.Name = "Servo1Label";
            this.Servo1Label.Size = new System.Drawing.Size(67, 21);
            this.Servo1Label.TabIndex = 66;
            this.Servo1Label.Text = "Servo 1";
            this.Servo1Label.Click += new System.EventHandler(this.label2_Click);
            // 
            // Servo2Label
            // 
            this.Servo2Label.AutoSize = true;
            this.Servo2Label.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo2Label.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.Servo2Label.Location = new System.Drawing.Point(236, 82);
            this.Servo2Label.Name = "Servo2Label";
            this.Servo2Label.Size = new System.Drawing.Size(67, 21);
            this.Servo2Label.TabIndex = 67;
            this.Servo2Label.Text = "Servo 2";
            // 
            // Servo3Label
            // 
            this.Servo3Label.AutoSize = true;
            this.Servo3Label.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo3Label.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.Servo3Label.Location = new System.Drawing.Point(327, 82);
            this.Servo3Label.Name = "Servo3Label";
            this.Servo3Label.Size = new System.Drawing.Size(67, 21);
            this.Servo3Label.TabIndex = 68;
            this.Servo3Label.Text = "Servo 3";
            // 
            // Servo4Label
            // 
            this.Servo4Label.AutoSize = true;
            this.Servo4Label.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo4Label.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.Servo4Label.Location = new System.Drawing.Point(420, 82);
            this.Servo4Label.Name = "Servo4Label";
            this.Servo4Label.Size = new System.Drawing.Size(67, 21);
            this.Servo4Label.TabIndex = 69;
            this.Servo4Label.Text = "Servo 4";
            // 
            // Servo4OffsetLabel
            // 
            this.Servo4OffsetLabel.AutoSize = true;
            this.Servo4OffsetLabel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo4OffsetLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.Servo4OffsetLabel.Location = new System.Drawing.Point(414, 183);
            this.Servo4OffsetLabel.Name = "Servo4OffsetLabel";
            this.Servo4OffsetLabel.Size = new System.Drawing.Size(67, 21);
            this.Servo4OffsetLabel.TabIndex = 73;
            this.Servo4OffsetLabel.Text = "Servo 4";
            // 
            // Servo3OffsetLabel
            // 
            this.Servo3OffsetLabel.AutoSize = true;
            this.Servo3OffsetLabel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo3OffsetLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.Servo3OffsetLabel.Location = new System.Drawing.Point(321, 183);
            this.Servo3OffsetLabel.Name = "Servo3OffsetLabel";
            this.Servo3OffsetLabel.Size = new System.Drawing.Size(67, 21);
            this.Servo3OffsetLabel.TabIndex = 72;
            this.Servo3OffsetLabel.Text = "Servo 3";
            // 
            // Servo2OffsetLabel
            // 
            this.Servo2OffsetLabel.AutoSize = true;
            this.Servo2OffsetLabel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo2OffsetLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.Servo2OffsetLabel.Location = new System.Drawing.Point(230, 183);
            this.Servo2OffsetLabel.Name = "Servo2OffsetLabel";
            this.Servo2OffsetLabel.Size = new System.Drawing.Size(67, 21);
            this.Servo2OffsetLabel.TabIndex = 71;
            this.Servo2OffsetLabel.Text = "Servo 2";
            // 
            // Servo1OffsetLabel
            // 
            this.Servo1OffsetLabel.AutoSize = true;
            this.Servo1OffsetLabel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Servo1OffsetLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.Servo1OffsetLabel.Location = new System.Drawing.Point(139, 183);
            this.Servo1OffsetLabel.Name = "Servo1OffsetLabel";
            this.Servo1OffsetLabel.Size = new System.Drawing.Size(67, 21);
            this.Servo1OffsetLabel.TabIndex = 70;
            this.Servo1OffsetLabel.Text = "Servo 1";
            // 
            // RollOffsetLabel
            // 
            this.RollOffsetLabel.AutoSize = true;
            this.RollOffsetLabel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RollOffsetLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.RollOffsetLabel.Location = new System.Drawing.Point(382, 290);
            this.RollOffsetLabel.Name = "RollOffsetLabel";
            this.RollOffsetLabel.Size = new System.Drawing.Size(40, 21);
            this.RollOffsetLabel.TabIndex = 76;
            this.RollOffsetLabel.Text = "Roll";
            // 
            // PitchOffsetLabel
            // 
            this.PitchOffsetLabel.AutoSize = true;
            this.PitchOffsetLabel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PitchOffsetLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.PitchOffsetLabel.Location = new System.Drawing.Point(284, 290);
            this.PitchOffsetLabel.Name = "PitchOffsetLabel";
            this.PitchOffsetLabel.Size = new System.Drawing.Size(49, 21);
            this.PitchOffsetLabel.TabIndex = 75;
            this.PitchOffsetLabel.Text = "Pitch";
            // 
            // YawOffsetLabel
            // 
            this.YawOffsetLabel.AutoSize = true;
            this.YawOffsetLabel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.YawOffsetLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.YawOffsetLabel.Location = new System.Drawing.Point(199, 290);
            this.YawOffsetLabel.Name = "YawOffsetLabel";
            this.YawOffsetLabel.Size = new System.Drawing.Size(41, 21);
            this.YawOffsetLabel.TabIndex = 74;
            this.YawOffsetLabel.Text = "Yaw";
            // 
            // ServoOffsetLabel
            // 
            this.ServoOffsetLabel.AutoSize = true;
            this.ServoOffsetLabel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ServoOffsetLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.ServoOffsetLabel.Location = new System.Drawing.Point(260, 152);
            this.ServoOffsetLabel.Name = "ServoOffsetLabel";
            this.ServoOffsetLabel.Size = new System.Drawing.Size(104, 21);
            this.ServoOffsetLabel.TabIndex = 114;
            this.ServoOffsetLabel.Text = "Servo Offset";
            this.ServoOffsetLabel.Click += new System.EventHandler(this.label50_Click);
            // 
            // SensorDataLabel
            // 
            this.SensorDataLabel.AutoSize = true;
            this.SensorDataLabel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SensorDataLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.SensorDataLabel.Location = new System.Drawing.Point(236, 258);
            this.SensorDataLabel.Name = "SensorDataLabel";
            this.SensorDataLabel.Size = new System.Drawing.Size(151, 21);
            this.SensorDataLabel.TabIndex = 120;
            this.SensorDataLabel.Text = "Sensor Data Offset";
            // 
            // Mahony
            // 
            this.Mahony.AutoSize = true;
            this.Mahony.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Mahony.ForeColor = System.Drawing.Color.Silver;
            this.Mahony.Location = new System.Drawing.Point(6, 59);
            this.Mahony.Name = "Mahony";
            this.Mahony.Size = new System.Drawing.Size(85, 25);
            this.Mahony.TabIndex = 118;
            this.Mahony.TabStop = true;
            this.Mahony.Text = "Mahony";
            this.Mahony.UseVisualStyleBackColor = true;
            // 
            // Madgwick
            // 
            this.Madgwick.AutoSize = true;
            this.Madgwick.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Madgwick.ForeColor = System.Drawing.Color.Silver;
            this.Madgwick.Location = new System.Drawing.Point(6, 28);
            this.Madgwick.Name = "Madgwick";
            this.Madgwick.Size = new System.Drawing.Size(99, 25);
            this.Madgwick.TabIndex = 117;
            this.Madgwick.TabStop = true;
            this.Madgwick.Text = "Madgwick";
            this.Madgwick.UseVisualStyleBackColor = true;
            // 
            // Off
            // 
            this.Off.AutoSize = true;
            this.Off.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Off.ForeColor = System.Drawing.Color.Silver;
            this.Off.Location = new System.Drawing.Point(8, 58);
            this.Off.Name = "Off";
            this.Off.Size = new System.Drawing.Size(50, 25);
            this.Off.TabIndex = 122;
            this.Off.TabStop = true;
            this.Off.Text = "Off";
            this.Off.UseVisualStyleBackColor = true;
            // 
            // On
            // 
            this.On.AutoSize = true;
            this.On.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.On.ForeColor = System.Drawing.Color.Silver;
            this.On.Location = new System.Drawing.Point(8, 28);
            this.On.Name = "On";
            this.On.Size = new System.Drawing.Size(49, 25);
            this.On.TabIndex = 121;
            this.On.TabStop = true;
            this.On.Text = "On";
            this.On.UseVisualStyleBackColor = true;
            // 
            // SerialDebug
            // 
            this.SerialDebug.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.SerialDebug.Controls.Add(this.Alt);
            this.SerialDebug.Controls.Add(this.YPR);
            this.SerialDebug.Controls.Add(this.Quat);
            this.SerialDebug.Controls.Add(this.RawMag);
            this.SerialDebug.Controls.Add(this.RawGyro);
            this.SerialDebug.Controls.Add(this.RawAccel);
            this.SerialDebug.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SerialDebug.ForeColor = System.Drawing.Color.Silver;
            this.SerialDebug.Location = new System.Drawing.Point(12, 370);
            this.SerialDebug.Name = "SerialDebug";
            this.SerialDebug.Size = new System.Drawing.Size(593, 118);
            this.SerialDebug.TabIndex = 125;
            this.SerialDebug.TabStop = false;
            this.SerialDebug.Text = "Serial Debug";
            // 
            // RawAccel
            // 
            this.RawAccel.AutoSize = true;
            this.RawAccel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RawAccel.ForeColor = System.Drawing.Color.Silver;
            this.RawAccel.Location = new System.Drawing.Point(6, 38);
            this.RawAccel.Name = "RawAccel";
            this.RawAccel.Size = new System.Drawing.Size(147, 25);
            this.RawAccel.TabIndex = 120;
            this.RawAccel.TabStop = true;
            this.RawAccel.Text = "Raw Acceleration";
            this.RawAccel.UseVisualStyleBackColor = true;
            // 
            // RawGyro
            // 
            this.RawGyro.AutoSize = true;
            this.RawGyro.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RawGyro.ForeColor = System.Drawing.Color.Silver;
            this.RawGyro.Location = new System.Drawing.Point(6, 69);
            this.RawGyro.Name = "RawGyro";
            this.RawGyro.Size = new System.Drawing.Size(136, 25);
            this.RawGyro.TabIndex = 121;
            this.RawGyro.TabStop = true;
            this.RawGyro.Text = "Raw Gyroscope";
            this.RawGyro.UseVisualStyleBackColor = true;
            // 
            // RawMag
            // 
            this.RawMag.AutoSize = true;
            this.RawMag.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RawMag.ForeColor = System.Drawing.Color.Silver;
            this.RawMag.Location = new System.Drawing.Point(191, 38);
            this.RawMag.Name = "RawMag";
            this.RawMag.Size = new System.Drawing.Size(165, 25);
            this.RawMag.TabIndex = 122;
            this.RawMag.TabStop = true;
            this.RawMag.Text = "Raw Magnetometer";
            this.RawMag.UseVisualStyleBackColor = true;
            // 
            // Quat
            // 
            this.Quat.AutoSize = true;
            this.Quat.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Quat.ForeColor = System.Drawing.Color.Silver;
            this.Quat.Location = new System.Drawing.Point(191, 69);
            this.Quat.Name = "Quat";
            this.Quat.Size = new System.Drawing.Size(170, 25);
            this.Quat.TabIndex = 123;
            this.Quat.TabStop = true;
            this.Quat.Text = "Filtered Quaternions";
            this.Quat.UseVisualStyleBackColor = true;
            // 
            // YPR
            // 
            this.YPR.AutoSize = true;
            this.YPR.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.YPR.ForeColor = System.Drawing.Color.Silver;
            this.YPR.Location = new System.Drawing.Point(375, 38);
            this.YPR.Name = "YPR";
            this.YPR.Size = new System.Drawing.Size(187, 25);
            this.YPR.TabIndex = 124;
            this.YPR.TabStop = true;
            this.YPR.Text = "Filtered Yaw, Pitch, Roll";
            this.YPR.UseVisualStyleBackColor = true;
            // 
            // Alt
            // 
            this.Alt.AutoSize = true;
            this.Alt.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Alt.ForeColor = System.Drawing.Color.Silver;
            this.Alt.Location = new System.Drawing.Point(375, 69);
            this.Alt.Name = "Alt";
            this.Alt.Size = new System.Drawing.Size(148, 25);
            this.Alt.TabIndex = 125;
            this.Alt.TabStop = true;
            this.Alt.Text = "Altitude/Pressure";
            this.Alt.UseVisualStyleBackColor = true;
            // 
            // Filtering
            // 
            this.Filtering.Controls.Add(this.Madgwick);
            this.Filtering.Controls.Add(this.Mahony);
            this.Filtering.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Filtering.ForeColor = System.Drawing.Color.Silver;
            this.Filtering.Location = new System.Drawing.Point(100, 507);
            this.Filtering.Name = "Filtering";
            this.Filtering.Size = new System.Drawing.Size(119, 100);
            this.Filtering.TabIndex = 126;
            this.Filtering.TabStop = false;
            this.Filtering.Text = "Filtering Type";
            // 
            // Datalogging
            // 
            this.Datalogging.Controls.Add(this.On);
            this.Datalogging.Controls.Add(this.Off);
            this.Datalogging.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Datalogging.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.Datalogging.Location = new System.Drawing.Point(401, 507);
            this.Datalogging.Name = "Datalogging";
            this.Datalogging.Size = new System.Drawing.Size(120, 100);
            this.Datalogging.TabIndex = 127;
            this.Datalogging.TabStop = false;
            this.Datalogging.Text = "Datalogging";
            this.Datalogging.Enter += new System.EventHandler(this.groupBox2_Enter);
            // 
            // RocketConfig
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(59)))), ((int)(((byte)(55)))), ((int)(((byte)(55)))));
            this.ClientSize = new System.Drawing.Size(617, 708);
            this.Controls.Add(this.Datalogging);
            this.Controls.Add(this.Filtering);
            this.Controls.Add(this.SerialDebug);
            this.Controls.Add(this.SensorDataLabel);
            this.Controls.Add(this.ServoOffsetLabel);
            this.Controls.Add(this.RollOffsetLabel);
            this.Controls.Add(this.PitchOffsetLabel);
            this.Controls.Add(this.YawOffsetLabel);
            this.Controls.Add(this.Servo4OffsetLabel);
            this.Controls.Add(this.Servo3OffsetLabel);
            this.Controls.Add(this.Servo2OffsetLabel);
            this.Controls.Add(this.Servo1OffsetLabel);
            this.Controls.Add(this.Servo4Label);
            this.Controls.Add(this.Servo3Label);
            this.Controls.Add(this.Servo2Label);
            this.Controls.Add(this.Servo1Label);
            this.Controls.Add(this.ServoPinsLabel);
            this.Controls.Add(this.RollOffset);
            this.Controls.Add(this.PitchOffset);
            this.Controls.Add(this.YawOffset);
            this.Controls.Add(this.Servo4Offset);
            this.Controls.Add(this.Servo3Offset);
            this.Controls.Add(this.Servo2Offset);
            this.Controls.Add(this.Servo4Pin);
            this.Controls.Add(this.Servo3Pin);
            this.Controls.Add(this.Servo2Pin);
            this.Controls.Add(this.Servo1Pin);
            this.Controls.Add(this.Servo1Offset);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "RocketConfig";
            this.Text = "Open Source Rocket Stabilization System Configuration";
            this.Load += new System.EventHandler(this.RocketConfig_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.SerialDebug.ResumeLayout(false);
            this.SerialDebug.PerformLayout();
            this.Filtering.ResumeLayout(false);
            this.Filtering.PerformLayout();
            this.Datalogging.ResumeLayout(false);
            this.Datalogging.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        public System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.TextBox Servo1Offset;
        private System.Windows.Forms.TextBox Servo2Pin;
        private System.Windows.Forms.TextBox Servo1Pin;
        private System.Windows.Forms.TextBox Servo4Pin;
        private System.Windows.Forms.TextBox Servo3Pin;
        private System.Windows.Forms.TextBox Servo2Offset;
        private System.Windows.Forms.TextBox Servo3Offset;
        private System.Windows.Forms.TextBox Servo4Offset;
        private System.Windows.Forms.TextBox RollOffset;
        private System.Windows.Forms.TextBox PitchOffset;
        private System.Windows.Forms.TextBox YawOffset;
        private System.Windows.Forms.Label ServoPinsLabel;
        private System.Windows.Forms.Label Servo1Label;
        private System.Windows.Forms.Label Servo2Label;
        private System.Windows.Forms.Label Servo3Label;
        private System.Windows.Forms.Label Servo4Label;
        private System.Windows.Forms.Label Servo4OffsetLabel;
        private System.Windows.Forms.Label Servo3OffsetLabel;
        private System.Windows.Forms.Label Servo2OffsetLabel;
        private System.Windows.Forms.Label Servo1OffsetLabel;
        private System.Windows.Forms.Label RollOffsetLabel;
        private System.Windows.Forms.Label PitchOffsetLabel;
        private System.Windows.Forms.Label YawOffsetLabel;
        private System.Windows.Forms.Label ServoOffsetLabel;
        private System.Windows.Forms.Label SensorDataLabel;
        private System.Windows.Forms.RadioButton Mahony;
        private System.Windows.Forms.RadioButton Madgwick;
        private System.Windows.Forms.RadioButton Off;
        private System.Windows.Forms.RadioButton On;
        private System.Windows.Forms.GroupBox SerialDebug;
        private System.Windows.Forms.RadioButton Alt;
        private System.Windows.Forms.RadioButton YPR;
        private System.Windows.Forms.RadioButton Quat;
        private System.Windows.Forms.RadioButton RawMag;
        private System.Windows.Forms.RadioButton RawGyro;
        private System.Windows.Forms.RadioButton RawAccel;
        private System.Windows.Forms.GroupBox Filtering;
        private System.Windows.Forms.GroupBox Datalogging;
    }
}


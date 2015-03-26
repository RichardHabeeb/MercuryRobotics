namespace BaseStation
{
    partial class BaseStationGui
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
            this.leftMotorLabel = new System.Windows.Forms.Label();
            this.rightMotorLabel = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.verticalProgressBarArm = new BaseStation.VerticalProgressBar();
            this.verticalProgressBarRight = new BaseStation.VerticalProgressBar();
            this.verticalProgressBarLeft = new BaseStation.VerticalProgressBar();
            this.SuspendLayout();
            // 
            // leftMotorLabel
            // 
            this.leftMotorLabel.AutoSize = true;
            this.leftMotorLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.leftMotorLabel.Location = new System.Drawing.Point(36, 283);
            this.leftMotorLabel.Name = "leftMotorLabel";
            this.leftMotorLabel.Size = new System.Drawing.Size(23, 13);
            this.leftMotorLabel.TabIndex = 2;
            this.leftMotorLabel.Text = "0.0";
            // 
            // rightMotorLabel
            // 
            this.rightMotorLabel.AutoSize = true;
            this.rightMotorLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rightMotorLabel.Location = new System.Drawing.Point(72, 283);
            this.rightMotorLabel.Name = "rightMotorLabel";
            this.rightMotorLabel.Size = new System.Drawing.Size(23, 13);
            this.rightMotorLabel.TabIndex = 3;
            this.rightMotorLabel.Text = "0.0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(111, 19);
            this.label1.TabIndex = 7;
            this.label1.Text = "Motor Throttle";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(139, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(86, 19);
            this.label2.TabIndex = 8;
            this.label2.Text = "Arm Angle";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(197, 31);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(31, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "180˚";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(197, 150);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(25, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "90˚";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(197, 267);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(19, 13);
            this.label5.TabIndex = 12;
            this.label5.Text = "0˚";
            // 
            // verticalProgressBarArm
            // 
            this.verticalProgressBarArm.Location = new System.Drawing.Point(164, 31);
            this.verticalProgressBarArm.Maximum = 180;
            this.verticalProgressBarArm.Name = "verticalProgressBarArm";
            this.verticalProgressBarArm.Size = new System.Drawing.Size(30, 249);
            this.verticalProgressBarArm.TabIndex = 9;
            this.verticalProgressBarArm.MouseClick += new System.Windows.Forms.MouseEventHandler(this.verticalProgressBarArm_MouseClick);
            // 
            // verticalProgressBarRight
            // 
            this.verticalProgressBarRight.Location = new System.Drawing.Point(68, 31);
            this.verticalProgressBarRight.Name = "verticalProgressBarRight";
            this.verticalProgressBarRight.Size = new System.Drawing.Size(30, 249);
            this.verticalProgressBarRight.TabIndex = 6;
            this.verticalProgressBarRight.Value = 50;
            // 
            // verticalProgressBarLeft
            // 
            this.verticalProgressBarLeft.Location = new System.Drawing.Point(32, 31);
            this.verticalProgressBarLeft.Name = "verticalProgressBarLeft";
            this.verticalProgressBarLeft.Size = new System.Drawing.Size(30, 249);
            this.verticalProgressBarLeft.TabIndex = 5;
            this.verticalProgressBarLeft.Value = 50;
            // 
            // BaseStationGui
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(695, 333);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.verticalProgressBarArm);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.verticalProgressBarRight);
            this.Controls.Add(this.verticalProgressBarLeft);
            this.Controls.Add(this.rightMotorLabel);
            this.Controls.Add(this.leftMotorLabel);
            this.Name = "BaseStationGui";
            this.Text = "KSURCT Mercury Robot Base Station";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.BaseStationGui_FormClosing);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.BaseStationGui_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.BaseStationGui_KeyUp);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label leftMotorLabel;
        private System.Windows.Forms.Label rightMotorLabel;
        private VerticalProgressBar verticalProgressBarLeft;
        private VerticalProgressBar verticalProgressBarRight;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private VerticalProgressBar verticalProgressBarArm;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
    }
}
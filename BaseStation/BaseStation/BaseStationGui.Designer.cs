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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.leftMotorLabel = new System.Windows.Forms.Label();
            this.rightMotorLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(97, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Left Motor Throttle:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(104, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Right Motor Throttle:";
            // 
            // leftMotorLabel
            // 
            this.leftMotorLabel.AutoSize = true;
            this.leftMotorLabel.Location = new System.Drawing.Point(122, 9);
            this.leftMotorLabel.Name = "leftMotorLabel";
            this.leftMotorLabel.Size = new System.Drawing.Size(22, 13);
            this.leftMotorLabel.TabIndex = 2;
            this.leftMotorLabel.Text = "0.0";
            // 
            // rightMotorLabel
            // 
            this.rightMotorLabel.AutoSize = true;
            this.rightMotorLabel.Location = new System.Drawing.Point(122, 22);
            this.rightMotorLabel.Name = "rightMotorLabel";
            this.rightMotorLabel.Size = new System.Drawing.Size(22, 13);
            this.rightMotorLabel.TabIndex = 3;
            this.rightMotorLabel.Text = "0.0";
            // 
            // BaseStationGui
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(695, 305);
            this.Controls.Add(this.rightMotorLabel);
            this.Controls.Add(this.leftMotorLabel);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "BaseStationGui";
            this.Text = "BaseStationGui";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.BaseStationGui_FormClosing);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.BaseStationGui_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.BaseStationGui_KeyUp);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label leftMotorLabel;
        private System.Windows.Forms.Label rightMotorLabel;
    }
}
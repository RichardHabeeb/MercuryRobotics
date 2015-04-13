namespace BaseStation
{
    partial class IPModeWindow
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
            this.MenuLablel = new System.Windows.Forms.Label();
            this.AutoDetectButton = new System.Windows.Forms.Button();
            this.ManuaIPButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // MenuLablel
            // 
            this.MenuLablel.AutoSize = true;
            this.MenuLablel.Location = new System.Drawing.Point(6, 6);
            this.MenuLablel.Name = "MenuLablel";
            this.MenuLablel.Size = new System.Drawing.Size(143, 13);
            this.MenuLablel.TabIndex = 1;
            this.MenuLablel.Text = "Which mode would you like?";
            // 
            // AutoDetectButton
            // 
            this.AutoDetectButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.AutoDetectButton.Location = new System.Drawing.Point(23, 22);
            this.AutoDetectButton.Name = "AutoDetectButton";
            this.AutoDetectButton.Size = new System.Drawing.Size(114, 23);
            this.AutoDetectButton.TabIndex = 2;
            this.AutoDetectButton.Text = "IP Auto Detect";
            this.AutoDetectButton.UseVisualStyleBackColor = true;
            this.AutoDetectButton.Click += new System.EventHandler(this.AutoDetectButton_Click);
            // 
            // ManuaIPButton
            // 
            this.ManuaIPButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.ManuaIPButton.Location = new System.Drawing.Point(22, 53);
            this.ManuaIPButton.Name = "ManuaIPButton";
            this.ManuaIPButton.Size = new System.Drawing.Size(115, 23);
            this.ManuaIPButton.TabIndex = 3;
            this.ManuaIPButton.Text = "Manually Enter IP";
            this.ManuaIPButton.UseVisualStyleBackColor = true;
            this.ManuaIPButton.Click += new System.EventHandler(this.ManuaIPButton_Click);
            // 
            // IPModeWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(162, 88);
            this.Controls.Add(this.ManuaIPButton);
            this.Controls.Add(this.AutoDetectButton);
            this.Controls.Add(this.MenuLablel);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "IPModeWindow";
            this.Text = "IP Mode";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label MenuLablel;
        private System.Windows.Forms.Button AutoDetectButton;
        private System.Windows.Forms.Button ManuaIPButton;
    }
}
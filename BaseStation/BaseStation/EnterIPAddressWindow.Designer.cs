namespace BaseStation
{
    partial class EnterIPAddressWindow
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
            this.IPAddressTextbox = new System.Windows.Forms.TextBox();
            this.EnterButton = new System.Windows.Forms.Button();
            this.CancelButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(74, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(136, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Please Enter an IP Address";
            // 
            // IPAddressTextbox
            // 
            this.IPAddressTextbox.Location = new System.Drawing.Point(12, 47);
            this.IPAddressTextbox.Name = "IPAddressTextbox";
            this.IPAddressTextbox.Size = new System.Drawing.Size(260, 20);
            this.IPAddressTextbox.TabIndex = 1;
            // 
            // EnterButton
            // 
            this.EnterButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.EnterButton.Location = new System.Drawing.Point(67, 71);
            this.EnterButton.Name = "EnterButton";
            this.EnterButton.Size = new System.Drawing.Size(75, 23);
            this.EnterButton.TabIndex = 2;
            this.EnterButton.Text = "Enter";
            this.EnterButton.UseVisualStyleBackColor = true;
            // 
            // CancelButton
            // 
            this.CancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.CancelButton.Location = new System.Drawing.Point(148, 71);
            this.CancelButton.Name = "CancelButton";
            this.CancelButton.Size = new System.Drawing.Size(75, 23);
            this.CancelButton.TabIndex = 3;
            this.CancelButton.Text = "Cancel";
            this.CancelButton.UseVisualStyleBackColor = true;
            // 
            // EnterIPAddressWindow
            // 
            this.AcceptButton = this.EnterButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.CancelButton;
            this.ClientSize = new System.Drawing.Size(284, 107);
            this.Controls.Add(this.CancelButton);
            this.Controls.Add(this.EnterButton);
            this.Controls.Add(this.IPAddressTextbox);
            this.Controls.Add(this.label1);
            this.Name = "EnterIPAddressWindow";
            this.Text = "Enter IP Address";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox IPAddressTextbox;
        private System.Windows.Forms.Button EnterButton;
        private System.Windows.Forms.Button CancelButton;
    }
}
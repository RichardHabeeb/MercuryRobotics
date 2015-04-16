using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaseStation
{
    public partial class IPModeWindow : Form
    {
        public string IP { get; private set; }
        public int check { get; private set; }

        /// <summary>
        /// Initializes the IPModeWindow.
        /// </summary>
        public IPModeWindow()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Handles an event with clicking the AutoDetect option of the window.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AutoDetectButton_Click(object sender, EventArgs e)
        {
            check = 1;
            Visible = false;
        }

        /// <summary>
        /// Handles an event with clicking the ManualIP option of the window.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ManuaIPButton_Click(object sender, EventArgs e)
        {
            EnterIPAddressWindow getIPWindow = new EnterIPAddressWindow();
            check = 0;
            if(getIPWindow.ShowDialog() != DialogResult.OK) return;
            IP = getIPWindow.GetIPAddress;
            Visible = false;
        }        
    }
}

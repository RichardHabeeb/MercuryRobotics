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
    public partial class EnterIPAddressWindow : Form
    {
        public EnterIPAddressWindow()
        {
            InitializeComponent();
        }
        public string GetIPAddress
        {
            get
            {
                return IPAddressTextbox.ToString().Trim();
            }
        }
    }
}

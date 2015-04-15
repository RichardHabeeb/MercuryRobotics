using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace BaseStation
{
    public partial class EnterIPAddressWindow : Form
    {
        private StreamReader sr;
        private StreamWriter sw;
        public EnterIPAddressWindow()
        {
            InitializeComponent();
            PopulatePrevIPS(sr);
        }
        public string GetIPAddress
        {
            get
            {
                return IPAddressTextbox.Text.ToString();
            }
        }
        private void PopulatePrevIPS(StreamReader st)
        {
            st = new StreamReader("Previous IPS.txt");
            PrevIPBox.Items.Add(st.ReadLine());
        }

        private void PrevIPBox_SelectedValueChanged(object sender, EventArgs e)
        {
            IPAddressTextbox.Text = PrevIPBox.SelectedItem.ToString();
        }
    }
}

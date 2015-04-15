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
            PopulatePrevIPS();
        }
        public string GetIPAddress
        {
            get
            {
                return IPAddressTextbox.Text.ToString();
            }
        }

        private void PopulatePrevIPS()
        {
            sr = new StreamReader("Previous IPS.txt");
            while (!sr.EndOfStream)
            {
                PrevIPBox.Items.Add(sr.ReadLine());
            }

            sr.Close();
        }

        private void PrevIPBox_SelectedValueChanged(object sender, EventArgs e)
        {
            IPAddressTextbox.Text = PrevIPBox.SelectedItem.ToString();
        }


        private void EnterButton_Click(object sender, EventArgs e)
        {
            sw = new StreamWriter("Previous IPS.txt");
            foreach (String s in PrevIPBox.Items)
            {
                if (s != "") sw.WriteLine(s);
            }
            sw.WriteLine(IPAddressTextbox.Text);
            sw.Close();
        }
    }
}

/*
 * Kansas State University Robotics Team
 * Mecury Robotics Competition
 * 
 * Base Station Enter IP Address Window Form class
 * 
 * This class creates a windows form gui for manually entering the IP address of the robot and a drop down menu with previously entered IP address.
 *  
 * Author's: Richard Habeeb, Brandon Dunn, Daniel Marts, Daniel Wagner and Doug Anjard.
 */

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

        /// <summary>
        /// Instantiates a new IPAddressWindow and populates the previously used IPs on startup.
        /// </summary>
        public EnterIPAddressWindow()
        {
            InitializeComponent();
            PopulatePrevIPS();
        }
        /// <summary>
        /// Returns the IP address entered into the textbox.
        /// </summary>
        public string GetIPAddress
        {
            get
            {
                return IPAddressTextbox.Text.ToString();
            }
        }

        /// <summary>
        /// Populates the combobox with the previously entered IPs.
        /// </summary>
        private void PopulatePrevIPS()
        {
            sr = new StreamReader("Previous IPS.txt");
            while (!sr.EndOfStream)
            { 
                string str = sr.ReadLine();
                bool check = false;
                foreach(String s in PrevIPBox.Items)
                {
                    if(str == s)
                    {
                        check = true;
                    }
                }
                if(!check)
                {
                    PrevIPBox.Items.Add(str);
                }
                
            }

            sr.Close();
        }

        /// <summary>
        /// When an IP is selected from the combobox, it places it into the textbox.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void PrevIPBox_SelectedValueChanged(object sender, EventArgs e)
        {
            IPAddressTextbox.Text = PrevIPBox.SelectedItem.ToString();
        }

        /// <summary>
        /// When connecting to an IP, the entered IP is added to the file of previous IPs if it is not already in the list.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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

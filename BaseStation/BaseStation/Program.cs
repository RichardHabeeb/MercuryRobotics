/*
 * Kansas State University Robotics Team
 * Mecury Robotics Competition
 * 
 * Base Station Software Program.cs
 * 
 * Main for program start.
 *  
 * Author's: Richard Habeeb, Brandon Dunn, Daniel Marts, Daniel Wagner and Doug Anjard.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaseStation
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new BaseStationGUI());
        }
    }
}

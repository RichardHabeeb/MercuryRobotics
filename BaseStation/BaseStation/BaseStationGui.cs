using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Net.Sockets;
using System.Net;
using System.Runtime.InteropServices;
using DeviceManagement;

namespace BaseStation
{
    public partial class BaseStationGui : Form
    {
        KeyCommand commands;
        UdpClient robotConnection; 

        public BaseStationGui()
        {
            InitializeComponent();

            commands = new KeyCommand();
            robotConnection = new UdpClient(4444);
            robotConnection.Connect(IPAddress.Parse("129.130.46.58"), 4444);
        }

        private void BaseStationGui_KeyDown(object sender, KeyEventArgs e)
        {
            bool commandChanged = false;

            switch(e.KeyCode)
            {
                case Keys.Up:
                case Keys.W:
                    commandChanged = !commands.forward;
                    commands.forward = true;
                    break;

                case Keys.Left:
                case Keys.A:
                    commandChanged = !commands.left;
                    commands.left = true;
                    break;

                case Keys.Right:
                case Keys.D:
                    commandChanged = !commands.right;
                    commands.right = true;
                    break;

                case Keys.Down:
                case Keys.S:
                    commandChanged = !commands.reverse;
                    commands.reverse = true;
                    break;

                case Keys.ShiftKey:
                    commandChanged = !commands.sprint;
                    commands.sprint = true;
                    break;

                case Keys.E:
                    commandChanged = !commands.lower;
                    commands.lower = true;
                    break;

                case Keys.Q:
                    commandChanged = !commands.open;
                    commands.open = true;
                    break;
            }

            if(commandChanged) ProcessKeyBoardUpdate();

            
        }

        private void BaseStationGui_KeyUp(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Up:
                case Keys.W:
                    commands.forward = false;
                    break;

                case Keys.Left:
                case Keys.A:
                    commands.left = false;
                    break;

                case Keys.Right:
                case Keys.D:
                    commands.right = false;
                    break;

                case Keys.Down:
                case Keys.S:
                    commands.reverse = false;
                    break;

                case Keys.ShiftKey:
                    commands.sprint = false;
                    break;

                case Keys.E:
                    commands.lower = false;
                    break;

                case Keys.Q:
                    commands.open = false;
                    break;
            }

            ProcessKeyBoardUpdate();

        }


        private void ProcessKeyBoardUpdate()
        {
            MotorControl controller = new MotorControl(commands);

            byte[] dataBuffer = controller.ToArray();
            robotConnection.Send(dataBuffer, dataBuffer.Length);

            UpdateMotorLabels(controller.LeftDriveThrottle, controller.RightDriveThrottle);
        }


        private void UpdateMotorLabels(double left, double right)
        {
            rightMotorLabel.Text = right.ToString();
            leftMotorLabel.Text = left.ToString();
        }


        private void BaseStationGui_FormClosing(object sender, FormClosingEventArgs e)
        {
            robotConnection.Close();
        }
    }
}

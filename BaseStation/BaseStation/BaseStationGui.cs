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
            bool commandChanged = commands.HandleKeyPress(e.KeyCode, true);

            if(commandChanged) ProcessKeyBoardUpdate();
            
        }

        private void BaseStationGui_KeyUp(object sender, KeyEventArgs e)
        {
            commands.HandleKeyPress(e.KeyCode, false);

            ProcessKeyBoardUpdate();
        }


        private void ProcessKeyBoardUpdate()
        {
            MotorControl controller = new MotorControl(commands);

            SendMotorControllerPacket(controller);

            UpdateGui(controller.LeftDriveThrottle, controller.RightDriveThrottle, controller.armAngle, controller.irisAngle);
        }

        private void SendMotorControllerPacket(MotorControl controller)
        {
            byte[] dataBuffer = controller.ToArray();
            robotConnection.Send(dataBuffer, dataBuffer.Length);
        }


        private void UpdateGui(double left, double right, double arm, double iris)
        {
            rightMotorLabel.Text = right.ToString();
            leftMotorLabel.Text = left.ToString();
            verticalProgressBarLeft.Value = (int)Math.Floor(left * 50) + 50;
            verticalProgressBarRight.Value = (int)Math.Floor(right * 50) + 50;
            verticalProgressBarArm.Value = (int)arm;
            verticalProgressBarIris.Value = (int)iris;
        }


        private void BaseStationGui_FormClosing(object sender, FormClosingEventArgs e)
        {
            robotConnection.Close();
        }

        private void verticalProgressBarArm_MouseClick(object sender, MouseEventArgs e)
        {
            if(!checkBoxLock.Checked)
            {
                double ratio = 1.0 - Math.Abs(e.Location.Y) / (float)verticalProgressBarArm.Height;
                verticalProgressBarArm.Value = (int)(ratio * verticalProgressBarArm.Maximum);

                MotorControl controller = new MotorControl(commands);
                controller.armAngle = 180 * (float)ratio;
                SendMotorControllerPacket(controller);
            }
        }

        private void buttonSetTo90_Click(object sender, EventArgs e)
        {
            verticalProgressBarArm.Value = (int)(.5 * verticalProgressBarArm.Maximum);

            MotorControl controller = new MotorControl(commands);
            controller.armAngle = 90;
            SendMotorControllerPacket(controller);

            checkBoxLock.Checked = true;
        }
    }
}

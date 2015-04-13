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

namespace BaseStation
{
    public partial class BaseStationGUI : Form
    {
        KeyCommand commands;
        UdpClient robotConnection;
        MotorControl xcontroller;
        MotorControl kcontroller;
        GetRobotIP getIP;

        GamepadState xboxController;

        public BaseStationGUI()
        {
            InitializeComponent();
            IPModeWindow ipMode = new IPModeWindow();
            robotConnection = new UdpClient(4444);
            commands = new KeyCommand();
            xboxController = new GamepadState(SlimDX.XInput.UserIndex.One);
            xboxController.ControllerUpdate += xboxController_ControllerUpdate;
            xcontroller = new MotorControl();
            kcontroller = new MotorControl();
            if (ipMode.ShowDialog() != DialogResult.OK) System.Environment.Exit(0);
            else
            {
                if (ipMode.check == 1)
                {
                    getIP = new GetRobotIP(robotConnection);
                    robotConnection.Connect(IPAddress.Parse(getIP.GetIP()), 4444);
                }
                else
                {
                    robotConnection.Connect(IPAddress.Parse(ipMode.IP), 4444);
                }
            }     
        }

        private void xboxController_ControllerUpdate(object sender, EventArgs e)
        {
            xcontroller.Update(xboxController);

            //SendMotorControllerPacket(xcontroller);

            UpdateGui(xcontroller.LeftDriveThrottle, xcontroller.RightDriveThrottle, xcontroller.armAngle, xcontroller.irisAngle, xcontroller.Led_State);
        }


        private void BaseStationGUI_KeyDown(object sender, KeyEventArgs e)
        {
            bool commandChanged = commands.HandleKeyPress(e.KeyCode, true);

            if (commandChanged) ProcessKeyBoardUpdate();

        }

        private void BaseStationGUI_KeyUp(object sender, KeyEventArgs e)
        {
            commands.HandleKeyPress(e.KeyCode, false);

            ProcessKeyBoardUpdate();
        }


        private void ProcessKeyBoardUpdate()
        {
            kcontroller.Update(commands);

            //SendMotorControllerPacket(kcontroller);

            UpdateGui(kcontroller.LeftDriveThrottle, kcontroller.RightDriveThrottle, kcontroller.armAngle, kcontroller.irisAngle, kcontroller.Led_State);
        }

        private void SendMotorControllerPacket(MotorControl controller)
        {
            byte[] dataBuffer = controller.ToArray();
            robotConnection.Send(dataBuffer, dataBuffer.Length);
        }

        delegate void threadSafeGuiUpdate(double left, double right, double arm, double iris, byte led);
        private void UpdateGui(double left, double right, double arm, double iris, byte led)
        {
            if (rightMotorLabel.InvokeRequired)
            {
                rightMotorLabel.Invoke(new threadSafeGuiUpdate(UpdateGui), new object[] { left, right, arm, iris, led });
                return;
            }
            rightMotorLabel.Text = right.ToString();
            leftMotorLabel.Text = left.ToString();
            verticalProgressBarLeftMotor.Value = (int)Math.Floor(left * 50) + 50;
            verticalProgressBarRightMotor.Value = (int)Math.Floor(right * 50) + 50;
            verticalProgressBarArmerature.Value = (int)arm;
            verticalProgressBarIris.Value = (int)iris;
            if (led.ToString().Equals("1")) HeadLightsState.Text = "ON";
            else HeadLightsState.Text = "OFF";
        }


        private void BaseStationGUI_FormClosing(object sender, FormClosingEventArgs e)
        {
            robotConnection.Close();
        }


        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}

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
        IPHostEntry host;
        string robotIP;
        SensorDataPacket sensorPacket;
        Thread sensorData;

        GamepadState xboxController;

        [StructLayout(LayoutKind.Sequential)]
        private struct SensorDataPacket
        {
            public float LeftFront;     //Each value holds
            public float LeftBack;      //distance from the
            public float RightFront;    //wall in cm.
            public float RightBack;
        }

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
            sensorPacket = new SensorDataPacket();

            sensorData = new Thread(GetSensorData);
            sensorData.IsBackground = false;//May be wrong
            sensorData.Start();

            if (ipMode.ShowDialog() != DialogResult.OK) System.Environment.Exit(0);
            else
            {
                if (ipMode.check == 1)
                {
                    getIP = new GetRobotIP(robotConnection);
                    robotIP = getIP.GetIP();
                    robotConnection.Connect(IPAddress.Parse(robotIP), 4444);
                }
                else
                {
                    robotIP = ipMode.IP;
                    robotConnection.Connect(IPAddress.Parse(robotIP), 4444);
                }
            }

            string baseip = "";
            host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (IPAddress ip in host.AddressList)
            {
                if (ip.AddressFamily.ToString() == "InterNetwork")
                {
                    baseip = ip.ToString();
                }
            }
            byte[] buff = Encoding.ASCII.GetBytes(baseip);
            robotConnection.Send(buff, buff.Length);



        }

        private void xboxController_ControllerUpdate(object sender, EventArgs e)
        {
            xcontroller.Update(xboxController);

            SendMotorControllerPacket(xcontroller);

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

            //TODO: Make SensorDataRead use an event handler to reset itself
            if (sensorData.ThreadState == ThreadState.Stopped)
            {
                sensorData.Start();
            }
        }

        private void GetSensorData()
        {
            IPEndPoint robot = new IPEndPoint(IPAddress.Parse(robotIP), 4444);
            byte[] data = robotConnection.Receive(ref robot);
            
            sensorPacket.LeftFront = System.BitConverter.ToSingle(data, 0);
            sensorPacket.LeftBack = System.BitConverter.ToSingle(data, 4);
            sensorPacket.RightFront = System.BitConverter.ToSingle(data, 8);
            sensorPacket.RightBack = System.BitConverter.ToSingle(data, 12);

            FrontLeftSensor.Text = (sensorPacket.LeftFront.ToString() + " cm away");
            FrontRightSensor.Text = (sensorPacket.RightFront.ToString() + " cm away");
            RearLeftSensor.Text = (sensorPacket.LeftBack.ToString() + " cm away");
            RearRightSensor.Text = (sensorPacket.RightBack.ToString() + " cm away");
        }

        private void BaseStationGUI_FormClosing(object sender, FormClosingEventArgs e)
        {
            robotConnection.Close();
        }
    }
}

/*
 * Kansas State University Robotics Team
 * Mecury Robotics Competition
 * 
 * Base Station Base Station GUi form class
 * 
 * This class creates a the main GUI that the robot opertator will see while controlling the robot.
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
using System.Threading;
using System.Net.Sockets;
using System.Net;
using System.Runtime.InteropServices;
using System.Diagnostics;

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
        string robotIP { get; set; }
        SensorData sensorData;
        GamepadState xboxController;
        Process ffplay;

        /// <summary>
        /// Initializes the BaseStation GUI.
        /// Attempts to connect to the Python server.  If successful, the GUI opens up for use.
        /// </summary>
        public BaseStationGUI()
        {
            InitializeComponent();
            IPModeWindow ipMode = new IPModeWindow();
            robotConnection = new UdpClient(4444);
            
           
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
            sensorData = new SensorData(robotIP);
            sensorData.SensorUpdate += SensorData_SensorDataUpdate;
            commands = new KeyCommand();
            xboxController = new GamepadState(SlimDX.XInput.UserIndex.One);
            xboxController.ControllerUpdate += xboxController_ControllerUpdate;
            xcontroller = new MotorControl();
            kcontroller = new MotorControl();
            ffplay = new Process();
            ffplay.StartInfo.Arguments = "http://192.168.2.29:8090/live.mpg";
            ffplay.StartInfo.FileName = "ffplay.exe";
            ffplay.Start();
            this.Activate();
        }

        /// <summary>
        /// Handles updates to the GUI from the Xbox controller.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void xboxController_ControllerUpdate(object sender, EventArgs e)
        {
            xcontroller.Update(xboxController);

            SendMotorControllerPacket(xcontroller);

            UpdateGui(xcontroller.LeftDriveThrottle, xcontroller.RightDriveThrottle, xcontroller.armAngle, xcontroller.irisAngle, xcontroller.Led_State);
        }


        /// <summary>
        /// Handles updates to the GUI from the Keyboard press down.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BaseStationGUI_KeyDown(object sender, KeyEventArgs e)
        {
            bool commandChanged = commands.HandleKeyPress(e.KeyCode, true);

            if (commandChanged) ProcessKeyBoardUpdate();

        }

        /// <summary>
        /// Handles updates to the GUI from the Keyboard releases.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BaseStationGUI_KeyUp(object sender, KeyEventArgs e)
        {
            commands.HandleKeyPress(e.KeyCode, false);

            ProcessKeyBoardUpdate();
        }

        /// <summary>
        /// Updates the sensor data labels on the GUI with the most recent data.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SensorData_SensorDataUpdate(object sender, EventArgs e)
        {
            UpdateGui(sensorData.FrontLeftSensorData, sensorData.FrontRightSensorData,
                sensorData.RearLeftSensorData, sensorData.RearRightSensorData);
        }


        /// <summary>
        /// Processes a keyboard press update for the GUI.
        /// </summary>
        private void ProcessKeyBoardUpdate()
        {
            kcontroller.Update(commands);

            SendMotorControllerPacket(kcontroller);

            UpdateGui(kcontroller.LeftDriveThrottle, kcontroller.RightDriveThrottle, kcontroller.armAngle, kcontroller.irisAngle, kcontroller.Led_State);
        }

        /// <summary>
        /// Sends a Motor Control packet to the Python Server
        /// </summary>
        /// <param name="controller">Packet to send.</param>
        private void SendMotorControllerPacket(MotorControl controller)
        {
            byte[] dataBuffer = controller.ToArray();
            robotConnection.Send(dataBuffer, dataBuffer.Length);
        }

        delegate void threadSafeGuiUpdate(double left, double right, double arm, double iris, byte led);
        /// <summary>
        /// Updates the GUI LED labels and VerticalProgressBars.
        /// </summary>
        /// <param name="left">Left motor reading.</param>
        /// <param name="right">Right motor reading.</param>
        /// <param name="arm">Armeture value.</param>
        /// <param name="iris">Iris value.</param>
        /// <param name="led">Led toggle.</param>
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

        delegate void threadSafeSensorGuiUpdate(float fls, float frs,  float rls, float rrs);
        /// <summary>
        /// Updates the GUI sensor labels.
        /// </summary>
        /// <param name="fls">Front left sensor reading.</param>
        /// <param name="frs">Front right sensor reading.</param>
        /// <param name="rls">Rear left sensor reading.</param>
        /// <param name="rrs">Rear right sensor reading.</param>
        private void UpdateGui(float fls, float frs, float rls, float rrs)
        {
            if (FrontLeftSensor.InvokeRequired)
            {
                FrontLeftSensor.Invoke(new threadSafeSensorGuiUpdate(UpdateGui), new object[] { fls, frs, rls, rrs});
                return;
            }

            FrontLeftSensorReading.Text = fls.ToString("F") + " cm away";
            FrontRightSensorReading.Text = frs.ToString("F") + " cm away";
            RearLeftSensorReading.Text = rls.ToString("F") + " cm away";
            RearRightSensorReading.Text = rrs.ToString("F") + " cm away";
        }

        /// <summary>
        /// When the GUI exits, the connection to the Python server is closed.+--7
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BaseStationGUI_FormClosing(object sender, FormClosingEventArgs e)
        {
            robotConnection.Close();
        }
    }
}

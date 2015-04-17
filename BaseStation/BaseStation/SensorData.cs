/*
 * Kansas State University Robotics Team
 * Mecury Robotics Competition
 * 
 * Base Station Sensor Data class
 * 
 * This class creates a background thread that handles the reciving of sensor data from the server and taking an average then updating the GUI with this average.
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

namespace BaseStation
{
    class SensorData
    {

        public EventHandler SensorUpdate;
        private BackgroundWorker worker;
        UdpClient robotConnection;
        IPEndPoint server;
        int theta;

        [StructLayout(LayoutKind.Sequential)]
        private struct MotorControlPacket
        {
            public float FrontLeftSensorData;  
            public float FrontRightSensorData; 
            public float RearLeftSensorData;   
            public float RearRightSensorData;  
        }

        public float FrontLeftSensorData { get; set; }
        public float FrontRightSensorData { get; set; }
        public float RearRightSensorData { get; set; }
        public float RearLeftSensorData { get; set; }


        /// <summary>
        /// Creates a new SensorData object associated with the robot's IP.
        /// </summary>
        /// <param name="robotip">IP address of the robot.</param>
        public SensorData(string robotip)
        {
            FrontLeftSensorData = 0;
            FrontRightSensorData = 0;
            RearLeftSensorData = 0;
            RearRightSensorData = 0;
            robotConnection = new UdpClient(4445);
            server = new IPEndPoint(IPAddress.Parse(robotip), 4445);
            worker = new BackgroundWorker();
            worker.DoWork += SensorDataThread;
            worker.WorkerSupportsCancellation = true;
            worker.RunWorkerAsync();
            theta = 90;
        }

        /// <summary>
        /// Takes the sensor data received from the Python server and averages the readings.
        /// </summary>
        /// <returns>True if the data was valid.</returns>
        public bool updateData()
        {
                var startTime = DateTime.UtcNow;
                float count = 0;
                while (DateTime.UtcNow - startTime < TimeSpan.FromMilliseconds(250))
                {
                    count++;
                    byte[] data = robotConnection.Receive(ref server);
                    if (data == null || data.Length == 0) return false;
                    FrontLeftSensorData += System.BitConverter.ToSingle(data, 0) * (float)Math.Sin(theta);
                    FrontRightSensorData += System.BitConverter.ToSingle(data, 4) * (float)Math.Sin(theta);
                    RearLeftSensorData += System.BitConverter.ToSingle(data, 8) * (float)Math.Sin(theta);
                    RearRightSensorData += System.BitConverter.ToSingle(data, 12) * (float)Math.Sin(theta);
                }

                FrontLeftSensorData /= count;
                FrontRightSensorData /= count;
                RearLeftSensorData /= count;
                RearRightSensorData /= count;
                return true;
        }

        /// <summary>
        /// Invokes a new SensorDataThread.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SensorDataThread(object sender, DoWorkEventArgs e)
        {
            while (!worker.CancellationPending)
            {
                if(updateData())
                {
                    SensorUpdate.Invoke(this, new EventArgs());
                }
            }
        }
    }
}

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

        public bool updateData()
        {
                byte[] data = robotConnection.Receive(ref server);
                if (data == null || data.Length == 0) return false;
                FrontLeftSensorData = System.BitConverter.ToSingle(data, 0) * (float)Math.Sin(theta);
                FrontRightSensorData = System.BitConverter.ToSingle(data, 4) * (float)Math.Sin(theta);
                RearLeftSensorData = System.BitConverter.ToSingle(data, 8) * (float)Math.Sin(theta);
                RearRightSensorData = System.BitConverter.ToSingle(data, 12) * (float)Math.Sin(theta);
                return true;
        }

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

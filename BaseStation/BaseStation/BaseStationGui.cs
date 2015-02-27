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
    public partial class BaseStationGui : Form
    {
        delegate void UpdateGUI(double left, double right);
        KeyCommand commands;
        //BackgroundWorker networkWorker;
        UdpClient robotConnection; 

        public BaseStationGui()
        {
            InitializeComponent();

            commands = new KeyCommand();
            robotConnection = new UdpClient(4444);
            robotConnection.Connect(IPAddress.Parse("127.0.0.1"), 4445);

            //networkWorker = new BackgroundWorker();
            //networkWorker.DoWork += new DoWorkEventHandler(NetworkBackgroundThread);
            //networkWorker.WorkerSupportsCancellation = true;
            //networkWorker.RunWorkerAsync();


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


        //private void NetworkBackgroundThread(object sender, DoWorkEventArgs e)
        //{
        //    while(!networkWorker.CancellationPending)
        //    {
        //        MotorControl controller = new MotorControl(commands);
        //        byte[] dataBuffer = controller.ToArray();

        //        if (robotConnection.Send(dataBuffer, dataBuffer.Length) == 0)
        //        {
        //            throw new Exception();
        //        }

        //        try
        //        {
        //            Invoke(new UpdateGUI(UpdateMotorLabels), new Object[] { controller.LeftDriveThrottle, controller.RightDriveThrottle });
        //        }
        //        catch (ObjectDisposedException)
        //        {
        //            break;
        //        }

        //        Thread.Sleep(10);
        //    }

        //    e.Cancel = true;
        //}



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
            //networkWorker.CancelAsync();
            robotConnection.Close();
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace BaseStation
{
    class MotorControl
    {
        [StructLayout(LayoutKind.Sequential)]
        private struct MotorControlPacket
        {
            public double LeftDriveThrottle;  /* Value from -1 -> 1 (-100% to 100%) */
            public double RightDriveThrottle; /* Value from -1 -> 1 (-100% to 100%) */
            public bool ApatureOpen;
            public bool LowerArm;
        }

        public double LeftDriveThrottle {get; private set;}   /* Value from -1 -> 1 (-100% to 100%) */
        public double RightDriveThrottle {get; private set;}  /* Value from -1 -> 1 (-100% to 100%) */
        private bool apatureOpen;
        private bool lowerArm;

        public MotorControl(KeyCommand commands)
        {
            apatureOpen = commands.open;
            lowerArm = commands.lower;
            LeftDriveThrottle = 0.0;
            RightDriveThrottle = 0.0;

            if(commands.forward)
            {
                LeftDriveThrottle = 0.5;
                RightDriveThrottle = 0.5;
            }
            else if (commands.reverse)
            {
                LeftDriveThrottle = -0.5;
                RightDriveThrottle = -0.5;
            }

            if(commands.left)
            {
                if (commands.forward || commands.reverse)
                {
                    LeftDriveThrottle /= 2;
                }
                else
                {
                    LeftDriveThrottle = -0.5;
                    RightDriveThrottle = 0.5;
                }
            }

            if (commands.right)
            {
                if (commands.forward || commands.reverse)
                {
                    RightDriveThrottle /= 2;
                }
                else
                {
                    RightDriveThrottle = -0.5;
                    LeftDriveThrottle = 0.5;
                }
            }

            if (commands.sprint)
            {
                LeftDriveThrottle *= 2;
                RightDriveThrottle *= 2;
            }

        }

        public byte[] ToArray()
        {
            MotorControlPacket packet = new MotorControlPacket()
            {
                LeftDriveThrottle = this.LeftDriveThrottle,
                RightDriveThrottle = this.RightDriveThrottle,
                ApatureOpen = this.apatureOpen,
                LowerArm = this.lowerArm
            };

            int controllerSize = Marshal.SizeOf(packet);

            byte[] dataBuffer = new byte[controllerSize + 1];
            IntPtr unmanagedPointer = Marshal.AllocHGlobal(controllerSize);
            Marshal.StructureToPtr(packet, unmanagedPointer, false);
            Marshal.Copy(unmanagedPointer, dataBuffer, 0, dataBuffer.Length);
            Marshal.FreeHGlobal(unmanagedPointer);

            dataBuffer[controllerSize] = Encoding.ASCII.GetBytes("\n")[0];

            return dataBuffer;
        }
    }
}

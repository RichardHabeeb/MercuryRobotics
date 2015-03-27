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
            public float LeftDriveThrottle;  /* Value from -1 -> 1 (-100% to 100%) */
            public float RightDriveThrottle; /* Value from -1 -> 1 (-100% to 100%) */
            public float IrisAngle;
            public float ArmAngle;
        }

        public float LeftDriveThrottle {get; set;}   /* Value from -1 -> 1 (-100% to 100%) */
        public float RightDriveThrottle {get; set;}  /* Value from -1 -> 1 (-100% to 100%) */
        public float irisAngle {get; set;}
        public float armAngle {get; set;}

        public MotorControl(KeyCommand commands)
        {
            irisAngle = commands.open ? 180.0f : 0.0f;
            armAngle = commands.lower ? 180.0f : 0.0f;
            LeftDriveThrottle = 0.0f;
            RightDriveThrottle = 0.0f;

            if(commands.forward)
            {
                LeftDriveThrottle = 0.5f;
                RightDriveThrottle = 0.5f;
            }
            else if (commands.reverse)
            {
                LeftDriveThrottle = -0.5f;
                RightDriveThrottle = -0.5f;
            }

            if(commands.left)
            {
                if (commands.forward || commands.reverse)
                {
                    LeftDriveThrottle /= 2;
                }
                else
                {
                    LeftDriveThrottle = -0.5f;
                    RightDriveThrottle = 0.5f;
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
                    RightDriveThrottle = -0.5f;
                    LeftDriveThrottle = 0.5f;
                }
            }

            if (commands.sprint)
            {
                LeftDriveThrottle *= 2.0f;
                RightDriveThrottle *= 2.0f;
            }

        }

        public MotorControl(float left, float right, float arm, float iris)
        {
            irisAngle = iris;
            armAngle = arm;
            LeftDriveThrottle = left;
            RightDriveThrottle = right;
        }

        public byte[] ToArray()
        {
            MotorControlPacket packet = new MotorControlPacket()
            {
                LeftDriveThrottle = this.LeftDriveThrottle,
                RightDriveThrottle = this.RightDriveThrottle,
                IrisAngle = this.irisAngle,
                ArmAngle = this.armAngle
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

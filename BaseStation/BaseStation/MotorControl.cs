/*
 * Kansas State University Robotics Team
 * Mecury Robotics Competition
 * 
 * Base Station Motor Control class
 * 
 * This CLass handles the processing of recived keyboard keys or xbox contrller button presses and makes a motor contorl packet that wil be sent over the server to the robot.
 *  
 * Author's: Richard Habeeb, Brandon Dunn, Daniel Marts, Daniel Wagner and Doug Anjard.
 */

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
            public int Led_toggle;          /* Holds a 0 or 1 for disable/enable Led*/
        }

        public float LeftDriveThrottle { get; set; }   /* Value from -1 -> 1 (-100% to 100%) */
        public float RightDriveThrottle { get; set; }  /* Value from -1 -> 1 (-100% to 100%) */
        public float irisAngle { get; set; }
        public float armAngle { get; set; }
        public byte Led_State { get; set; }  /* Holds a 0 or 1 for disable/enable LED */
        private bool isLedOn;               /* Holds true is leds are on false otherwise*/

        /// <summary>
        /// Creates a new MotorControl object, instantiating everything.
        /// </summary>
        public MotorControl()
        {
            irisAngle = 0;
            armAngle = 0;
            LeftDriveThrottle = 0;
            RightDriveThrottle = 0;
            Led_State = 0;
            isLedOn = false;
        }

        /// <summary>
        /// Updates the status of the robot's parts with the new keyboard commands received.
        /// </summary>
        /// <param name="commands">Keyboard state.</param>
        public void Update(KeyCommand commands)
        {
            irisAngle = commands.open ? 0.0f : 180.0f;
            armAngle = commands.lower ? 180.0f : 0.0f;
            LeftDriveThrottle = 0.0f;
            RightDriveThrottle = 0.0f;
            Led_State = 0;

            isLedOn = (commands.led ^ isLedOn);
            Led_State = Convert.ToByte(isLedOn);

            if (commands.forward)
            {
                LeftDriveThrottle = 0.5f;
                RightDriveThrottle = 0.5f;
            }
            else if (commands.reverse)
            {
                LeftDriveThrottle = -0.5f;
                RightDriveThrottle = -0.5f;
            }

            if (commands.left)
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

        /// <summary>
        /// Updates the status of the robot's parts with the new Xbox controller commands received.
        /// </summary>
        /// <param name="xboxController">State of the Xbox controller.</param>
        public void Update(GamepadState xboxController)
        {
            LeftDriveThrottle = Math.Max(-1.0f, Math.Min(1.0f, (xboxController.LeftStick.Clicked ? 1.0f : 0.5f) *
                       (0.5f * xboxController.LeftStick.Position.X + xboxController.LeftStick.Position.Y) +
               0.1f * (0.5f * xboxController.RightStick.Position.X + xboxController.RightStick.Position.Y)));

            RightDriveThrottle = Math.Max(-1.0f, Math.Min(1.0f, (xboxController.LeftStick.Clicked ? 1.0f : 0.5f) *
                        (-0.5f * xboxController.LeftStick.Position.X + xboxController.LeftStick.Position.Y) +
                0.1f * (-0.5f * xboxController.RightStick.Position.X + xboxController.RightStick.Position.Y)));

            armAngle = xboxController.LeftTrigger * 180.0f;
            irisAngle = xboxController.RightTrigger * 180.0f;

            isLedOn = (xboxController.A ^ isLedOn);
            Led_State = Convert.ToByte(isLedOn);

        }

        /// <summary>
        /// Converts the motor packet into a byte array to send to the Python server.
        /// </summary>
        /// <returns>Byte array of the motor packet.</returns>
        public byte[] ToArray()
        {
            MotorControlPacket packet = new MotorControlPacket()
            {
                LeftDriveThrottle = this.LeftDriveThrottle,
                RightDriveThrottle = this.RightDriveThrottle,
                IrisAngle = this.irisAngle,
                ArmAngle = this.armAngle,
                Led_toggle = this.Led_State
            };

            int controllerSize = Marshal.SizeOf(packet);

            byte[] dataBuffer = new byte[controllerSize];
            IntPtr unmanagedPointer = Marshal.AllocHGlobal(controllerSize);
            Marshal.StructureToPtr(packet, unmanagedPointer, false);
            Marshal.Copy(unmanagedPointer, dataBuffer, 0, dataBuffer.Length);
            Marshal.FreeHGlobal(unmanagedPointer);

            //dataBuffer[controllerSize] = Encoding.ASCII.GetBytes("\n")[0];

            return dataBuffer;
        }

    }
}

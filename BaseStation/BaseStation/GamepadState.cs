/*
 * Kansas State University Robotics Team
 * Mecury Robotics Competition
 * 
 * Base Station Game Pad State class
 * 
 * This class handles reading the state of the game pad plugged.
 *  
 * Author's: Richard Habeeb, Brandon Dunn, Daniel Marts, Daniel Wagner and Doug Anjard.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SlimDX;
using SlimDX.XInput;
using System.Threading;
using System.ComponentModel;
using System.Diagnostics;

namespace BaseStation
{
    class GamepadState
    {
        uint lastPacket;

        public EventHandler ControllerUpdate;

        /// <summary>
        /// Constructor for GamepadState
        /// </summary>
        /// <param name="userIndex"></param>
        public GamepadState(UserIndex userIndex)
        {
            UserIndex = userIndex;
            Controller = new Controller(userIndex);
            xboxControllerLock = new Mutex(false);
            xboxWorker = new BackgroundWorker();
            xboxWorker.DoWork += XboxWorkerThread;
            xboxWorker.WorkerSupportsCancellation = true;
            xboxWorker.RunWorkerAsync();
        }

        Mutex xboxControllerLock;
        BackgroundWorker xboxWorker;

        private readonly UserIndex UserIndex;
        private readonly Controller Controller;

        public DPadState DPad { get; private set; }
        public ThumbstickState LeftStick { get; private set; }
        public ThumbstickState RightStick { get; private set; }

        public bool A { get; private set; }
        public bool B { get; private set; }
        public bool X { get; private set; }
        public bool Y { get; private set; }

        public bool RightShoulder { get; private set; }
        public bool LeftShoulder { get; private set; }

        public bool Start { get; private set; }
        public bool Back { get; private set; }

        public float RightTrigger { get; private set; }
        public float LeftTrigger { get; private set; }

        /// <summary>
        /// Background thread for updating the gui with the updated gamepad state.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void XboxWorkerThread(object sender, DoWorkEventArgs e)
        {
            while (!xboxWorker.CancellationPending)
            {
                if (xboxControllerLock.WaitOne(0))
                {
                    if (CheckControlerState())
                    {
                        if (ControllerUpdate != null)
                        {
                            ControllerUpdate.Invoke(this, new EventArgs());
                        }
                    }


                    xboxControllerLock.ReleaseMutex();
                }
                Thread.Sleep(10);
            }
        }


        /// <summary>
        /// Method for seeing it the controller is plugged in.
        /// </summary>
        public bool Connected
        {
            get
            {
                if (xboxControllerLock.WaitOne(30))
                {
                    bool ret = Controller.IsConnected;
                    xboxControllerLock.ReleaseMutex();
                    return ret;
                }
                return false;
            }
        }

        /// <summary>
        /// Method for handling vibration controls on the gamepad.
        /// </summary>
        /// <param name="leftMotor"></param>
        /// <param name="rightMotor"></param>
        public void Vibrate(float leftMotor, float rightMotor)
        {
            Controller.SetVibration(new Vibration
            {
                LeftMotorSpeed = (ushort)(MathHelper.Saturate(leftMotor) * ushort.MaxValue),
                RightMotorSpeed = (ushort)(MathHelper.Saturate(rightMotor) * ushort.MaxValue)
            });
        }

        /// <summary>
        /// Method for checking the current state of the gamepad.
        /// </summary>
        /// <returns></returns>
        public bool CheckControlerState()
        {
            // If not connected, nothing to update
            if (!Connected) return false;

            // If same packet, nothing to update
            State state = Controller.GetState();
            if (lastPacket == state.PacketNumber) return false;
            lastPacket = state.PacketNumber;

            var gamepadState = state.Gamepad;

            // Shoulders
            LeftShoulder = (gamepadState.Buttons & GamepadButtonFlags.LeftShoulder) != 0;
            RightShoulder = (gamepadState.Buttons & GamepadButtonFlags.RightShoulder) != 0;

            // Triggers
            LeftTrigger = gamepadState.LeftTrigger / (float)byte.MaxValue;
            RightTrigger = gamepadState.RightTrigger / (float)byte.MaxValue;

            // Buttons
            Start = (gamepadState.Buttons & GamepadButtonFlags.Start) != 0;
            Back = (gamepadState.Buttons & GamepadButtonFlags.Back) != 0;

            A = (gamepadState.Buttons & GamepadButtonFlags.A) != 0;
            B = (gamepadState.Buttons & GamepadButtonFlags.B) != 0;
            X = (gamepadState.Buttons & GamepadButtonFlags.X) != 0;
            Y = (gamepadState.Buttons & GamepadButtonFlags.Y) != 0;

            // D-Pad
            DPad = new DPadState((gamepadState.Buttons & GamepadButtonFlags.DPadUp) != 0,
                                 (gamepadState.Buttons & GamepadButtonFlags.DPadDown) != 0,
                                 (gamepadState.Buttons & GamepadButtonFlags.DPadLeft) != 0,
                                 (gamepadState.Buttons & GamepadButtonFlags.DPadRight) != 0);

            // Thumbsticks
            LeftStick = new ThumbstickState(
                Normalize(gamepadState.LeftThumbX, gamepadState.LeftThumbY, Gamepad.GamepadLeftThumbDeadZone),
                (gamepadState.Buttons & GamepadButtonFlags.LeftThumb) != 0);
            RightStick = new ThumbstickState(
                Normalize(gamepadState.RightThumbX, gamepadState.RightThumbY, Gamepad.GamepadRightThumbDeadZone),
                (gamepadState.Buttons & GamepadButtonFlags.RightThumb) != 0);

            return true;

        }


        static Vector2 Normalize(short rawX, short rawY, short threshold)
        {
            var value = new Vector2(rawX, rawY);
            var magnitude = value.Length();
            var direction = value / (magnitude == 0 ? 1 : magnitude);

            var normalizedMagnitude = 0.0f;
            if (magnitude - threshold > 0)
                normalizedMagnitude = Math.Min((magnitude - threshold) / (short.MaxValue - threshold), 1);

            return direction * normalizedMagnitude;
        }

        public struct DPadState
        {
            public readonly bool Up, Down, Left, Right;

            public DPadState(bool up, bool down, bool left, bool right)
            {
                Up = up; Down = down; Left = left; Right = right;
            }
        }

        public struct ThumbstickState
        {
            public readonly Vector2 Position;
            public readonly bool Clicked;

            public ThumbstickState(Vector2 position, bool clicked)
            {
                Clicked = clicked;
                Position = position;
            }
        }
    }

    public static class MathHelper
    {
        public static float Saturate(float value)
        {
            return value < 0 ? 0 : value > 1 ? 1 : value;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaseStation
{
    public class KeyCommand
    {
        public bool forward = false;
        public bool right = false;
        public bool left = false;
        public bool reverse = false;
        public bool sprint = false;
        public bool open = false;
        public bool lower = false;
        public bool led = false;

        /// <summary>
        /// Handles a change in the keyboard presses (new button pressed/released).
        /// </summary>
        /// <param name="key">Keyboard key to check.</param>
        /// <param name="KeyPressed">Whether the key was pressed.</param>
        /// <returns></returns>
        public bool HandleKeyPress(Keys key, bool KeyPressed)
        {
            bool commandChanged = false;

            switch (key)
            {
                case Keys.Up:
                case Keys.W:
                    commandChanged = !this.forward;
                    this.forward = KeyPressed;
                    break;

                case Keys.Left:
                case Keys.A:
                    commandChanged = !this.left;
                    this.left = KeyPressed;
                    break;

                case Keys.Right:
                case Keys.D:
                    commandChanged = !this.right;
                    this.right = KeyPressed;
                    break;

                case Keys.Down:
                case Keys.S:
                    commandChanged = !this.reverse;
                    this.reverse = KeyPressed;
                    break;

                case Keys.ShiftKey:
                    commandChanged = !this.sprint;
                    this.sprint = KeyPressed;
                    break;

                case Keys.E:
                    commandChanged = !this.lower;
                    this.lower = KeyPressed;
                    break;

                case Keys.Q:
                    commandChanged = !this.open;
                    this.open = KeyPressed;
                    break;

                case Keys.L:
                    commandChanged = !this.led;
                    this.led = KeyPressed;
                    break;
            }

            return commandChanged;
        }
    }
}

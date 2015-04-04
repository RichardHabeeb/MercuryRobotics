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
        public bool led_on = false;
        public bool led_off = false;

        public bool HandleKeyPress(Keys key, bool upDown)
        {
            bool commandChanged = false;

            switch (key)
            {
                case Keys.Up:
                case Keys.W:
                    commandChanged = !this.forward;
                    this.forward = upDown;
                    break;

                case Keys.Left:
                case Keys.A:
                    commandChanged = !this.left;
                    this.left = upDown;
                    break;

                case Keys.Right:
                case Keys.D:
                    commandChanged = !this.right;
                    this.right = upDown;
                    break;

                case Keys.Down:
                case Keys.S:
                    commandChanged = !this.reverse;
                    this.reverse = upDown;
                    break;

                case Keys.ShiftKey:
                    commandChanged = !this.sprint;
                    this.sprint = upDown;
                    break;

                case Keys.E:
                    commandChanged = !this.lower;
                    this.lower = upDown;
                    break;

                case Keys.Q:
                    commandChanged = !this.open;
                    this.open = upDown;
                    break;
                
                case Keys.L:
                    commandChanged = !this.led_on;
                    this.led_on = upDown;
                    break;

                case Keys.O:
                    commandChanged = !this.led_off;
                    this.led_off = upDown;
                    break;

            }

            return commandChanged;
        }
    }
}

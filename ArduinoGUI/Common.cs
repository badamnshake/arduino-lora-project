using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoGUI
{
    internal class Common
    {
    }

    public class SenderOrReceiver : EventArgs
    {
        public bool isSender { get; }

        public SenderOrReceiver(bool data)
        {
            isSender = data;
        }
    }
}

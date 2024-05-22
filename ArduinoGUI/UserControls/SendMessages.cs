using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ArduinoGUI.UserControls
{
    public partial class SendMessages : UserControl
    {

        public SerialPort ArduinoPort { get; set; }
        public SendMessages()
        {
            InitializeComponent();
            messageSentSuccess.Visible = false;
        }

        private void sendMessage_Click(object sender, EventArgs e)
        {
            string message = messageText.Text;
            ArduinoPort.Write("send:" + message);
            messageSentSuccess.Visible = true;
            TriggerActionAfterDelay();
        }



        private async void TriggerActionAfterDelay()
        {
            await Task.Delay(3000); // Wait for 3000 milliseconds (3 seconds)

            // Perform the action after 3 seconds
            messageSentSuccess.Visible = false;
        }
    }
}

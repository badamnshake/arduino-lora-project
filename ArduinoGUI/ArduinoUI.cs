using ArduinoGUI.UserControls;
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

namespace ArduinoGUI
{
    public partial class ArduinoUI : Form
    {
        private Login login = new Login() {
            Visible = true };
        private ReceiveMessages receiveMessages = new ReceiveMessages() { Visible = false };
        private SendMessages sendMessages = new SendMessages() { Visible = false };
        public ArduinoUI()
        {
            InitializeComponent();

            Controls.Add(login);
            Controls.Add(receiveMessages);
            Controls.Add(sendMessages);




            receiveMessages.arduinoPort = arduino;
            sendMessages.ArduinoPort = arduino;
            sendMessages.Visible = false;
            receiveMessages.Visible = false;
            login.GoToSenderPage += ShowSenderPage;
            login.serialPort = arduino;
            login.SetEvents();


            arduino.Open();
            // Show the second user control
        }

        private void ShowSenderPage(object sender, SenderOrReceiver e)
        {
            if (InvokeRequired)
            {
                // Use Invoke to run the UpdateUI method on the UI thread
                Invoke(new MethodInvoker(() => ShowSenderPage(sender, e)));
                return;
            }

            // Hide the login control
            login.Visible = false;

            login.ResetEvents();
            

            if (e.isSender)
            {
                // Show the sendMessages control
                sendMessages.Visible = true;
            }
            else
            {
                // Set events and show the receiveMessages control
                receiveMessages.SetEvents();
                receiveMessages.Visible = true;
            }
        }
    }
}

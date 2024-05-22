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
using static System.Windows.Forms.VisualStyles.VisualStyleElement.StartPanel;

namespace ArduinoGUI.UserControls
{
    public partial class Login : UserControl
    {
        public SerialPort serialPort { get; set; }
        private bool loginAsSender = true;
        public event EventHandler<SenderOrReceiver> GoToSenderPage;
        public Login()
        {
            InitializeComponent();
            loginFailedMessage.Visible = false ;
        }

        public void SetEvents()
        {
            serialPort.DataReceived += processData;
        }

        public void ResetEvents()
        {
            serialPort.DataReceived -= processData;
        }


        private void TryLogginIn()
        {
            string uname = username.Text;
            string pword = password.Text;

            string loginstring = "login:" + uname + ":" + pword;

            serialPort.Write(loginstring);


        }


        private void LoginAsSender_Click(object sender, EventArgs e)
        {
            loginAsSender = true;
            TryLogginIn();
        }

        private void LoginAsReceiver_Click(object sender, EventArgs e)
        {
            loginAsSender = false;
            TryLogginIn();

        }

        private void processData(object sender, SerialDataReceivedEventArgs e)
        {
            if (InvokeRequired)
            {
                // Use Invoke to run the processData method on the UI thread
                Invoke(new Action<object, SerialDataReceivedEventArgs>(processData), sender, e);
                return;
            }

            SerialPort serialPort = (SerialPort)sender;
            string data = serialPort.ReadExisting();
            if (data.StartsWith("login 1"))
            {
                GoToSenderPage?.Invoke(this, new SenderOrReceiver(loginAsSender));
                Console.WriteLine("login success");
            }
            else if (data.StartsWith("login 0"))
            {
                // Show the loginFailedMessage on the UI thread
                Invoke(new Action(() => loginFailedMessage.Visible = true));
            }

            // Display the received data
            Console.WriteLine("Received from Arduino: " + data);
        }


    }
}

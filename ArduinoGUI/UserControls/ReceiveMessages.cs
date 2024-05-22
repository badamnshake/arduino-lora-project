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
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace ArduinoGUI.UserControls
{
    public partial class ReceiveMessages : UserControl
    {

        public SerialPort arduinoPort { get; set; }
        public ReceiveMessages()
        {
            InitializeComponent();
        }


        public void SetEvents()
        {
            arduinoPort.DataReceived += processData;
        }


            //if (InvokeRequired)
            //{
            //    // Use Invoke to run the UpdateUI method on the UI thread
            //    Invoke(new MethodInvoker(() => processData(sender, e)));
            //    return;
            //}
        
        private void processData(object sender, SerialDataReceivedEventArgs e)
        {


            SerialPort serialPort = (SerialPort)sender;
            string data = serialPort.ReadExisting();
            if (data == "login 1" || data == "login 0")
                return;


            // Display the received data
            UpdateMessageBoxSafe(data);
        }



        // Thread-safe method to update the RichTextBox
        private void UpdateMessageBoxSafe(string message)
        {
            if (richTextBox1.InvokeRequired)
            {
                // If we are not on the UI thread, marshal the call to the UI thread
                richTextBox1.Invoke(new Action<string>(UpdateMessageBox), message);
            }
            else
            {
                // If we are on the UI thread, just call the method directly
                UpdateMessageBox(message);
            }
        }


        // Method to update the RichTextBox with a new message
        private void UpdateMessageBox(string message)
        {
            // Temporarily set ReadOnly to false to allow modifications
            richTextBox1.ReadOnly = false;
            // Set the bullet style to a custom arrow symbol
            richTextBox1.SelectionBullet = true;
            richTextBox1.BulletIndent = 10; // Adjust the indentation as needed
                                          // Append the new message to the RichTextBox with some line spacing
            richTextBox1.AppendText("➤ " + message + Environment.NewLine);
            // Set ReadOnly back to true to prevent user input
            richTextBox1.ReadOnly = true;
            richTextBox1.HideSelection = true;
        }
    }
}

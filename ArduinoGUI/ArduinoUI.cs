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
        public ArduinoUI()
        {
            InitializeComponent();


            sendMessages1.Visible = false;
            receiveMessages1.Visible = false;
            login1.GoToSenderPage += ShowSenderPage;
        }

        private void ShowSenderPage(object sender, EventArgs e)
        {
            // Hide the first user control
            login1.Visible = false;

            // Show the second user control
            receiveMessages1.Visible = true;
        }
    }
}

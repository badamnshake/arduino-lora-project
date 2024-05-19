using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ArduinoGUI.UserControls
{
    public partial class Login : UserControl
    {
        public event EventHandler GoToSenderPage;
        public Login()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            GoToSenderPage?.Invoke(this, EventArgs.Empty);

        }
    }
}

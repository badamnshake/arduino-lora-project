using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace ArduinoGUI.UserControls
{
    public partial class ReceiveMessages : UserControl
    {
        public ReceiveMessages()
        {
            InitializeComponent();
            UpdateMessageBox("Hello there");
            UpdateMessageBox("How are you");

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
            richTextBox1.AppendText("➤ " + message + Environment.NewLine + Environment.NewLine);
            // Set ReadOnly back to true to prevent user input
            richTextBox1.ReadOnly = true;
            richTextBox1.HideSelection = true;
        }
    }
}

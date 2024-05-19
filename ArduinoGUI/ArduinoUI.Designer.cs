namespace ArduinoGUI
{
    partial class ArduinoUI
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.sendMessages1 = new ArduinoGUI.UserControls.SendMessages();
            this.receiveMessages1 = new ArduinoGUI.UserControls.ReceiveMessages();
            this.login1 = new ArduinoGUI.UserControls.Login();
            this.SuspendLayout();
            // 
            // sendMessages1
            // 
            this.sendMessages1.BackColor = System.Drawing.Color.Azure;
            this.sendMessages1.Location = new System.Drawing.Point(0, 0);
            this.sendMessages1.Name = "sendMessages1";
            this.sendMessages1.Size = new System.Drawing.Size(800, 600);
            this.sendMessages1.TabIndex = 17;
            // 
            // receiveMessages1
            // 
            this.receiveMessages1.BackColor = System.Drawing.Color.Azure;
            this.receiveMessages1.Location = new System.Drawing.Point(0, 0);
            this.receiveMessages1.Name = "receiveMessages1";
            this.receiveMessages1.Size = new System.Drawing.Size(800, 600);
            this.receiveMessages1.TabIndex = 16;
            // 
            // login1
            // 
            this.login1.BackColor = System.Drawing.Color.Azure;
            this.login1.Font = new System.Drawing.Font("Century Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.login1.Location = new System.Drawing.Point(0, 0);
            this.login1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.login1.Name = "login1";
            this.login1.Size = new System.Drawing.Size(800, 600);
            this.login1.TabIndex = 15;
            // 
            // ArduinoUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Azure;
            this.ClientSize = new System.Drawing.Size(802, 613);
            this.Controls.Add(this.sendMessages1);
            this.Controls.Add(this.receiveMessages1);
            this.Controls.Add(this.login1);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MinimumSize = new System.Drawing.Size(820, 660);
            this.Name = "ArduinoUI";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private UserControls.Login login1;
        private UserControls.ReceiveMessages receiveMessages1;
        private UserControls.SendMessages sendMessages1;
    }
}


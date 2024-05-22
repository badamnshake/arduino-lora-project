namespace ArduinoGUI.UserControls
{
    partial class SendMessages
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.sendMessage = new System.Windows.Forms.Button();
            this.messageText = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.messageSentSuccess = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(106, 239);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(64, 16);
            this.label2.TabIndex = 11;
            this.label2.Text = "Message";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(105, 164);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(182, 29);
            this.label1.TabIndex = 10;
            this.label1.Text = "Send Message";
            // 
            // sendMessage
            // 
            this.sendMessage.Location = new System.Drawing.Point(109, 308);
            this.sendMessage.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.sendMessage.Name = "sendMessage";
            this.sendMessage.Size = new System.Drawing.Size(96, 44);
            this.sendMessage.TabIndex = 9;
            this.sendMessage.Text = "Send";
            this.sendMessage.UseVisualStyleBackColor = true;
            this.sendMessage.Click += new System.EventHandler(this.sendMessage_Click);
            // 
            // messageText
            // 
            this.messageText.AccessibleRole = System.Windows.Forms.AccessibleRole.OutlineButton;
            this.messageText.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.messageText.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.messageText.Location = new System.Drawing.Point(109, 263);
            this.messageText.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.messageText.Name = "messageText";
            this.messageText.Size = new System.Drawing.Size(224, 22);
            this.messageText.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Candara", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(51, 43);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(378, 49);
            this.label4.TabIndex = 18;
            this.label4.Text = "Lora Communication";
            // 
            // messageSentSuccess
            // 
            this.messageSentSuccess.AutoSize = true;
            this.messageSentSuccess.ForeColor = System.Drawing.Color.DarkGreen;
            this.messageSentSuccess.Location = new System.Drawing.Point(116, 369);
            this.messageSentSuccess.Name = "messageSentSuccess";
            this.messageSentSuccess.Size = new System.Drawing.Size(171, 16);
            this.messageSentSuccess.TabIndex = 19;
            this.messageSentSuccess.Text = "message sent successfully!";
            // 
            // SendMessages
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Azure;
            this.Controls.Add(this.messageSentSuccess);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.sendMessage);
            this.Controls.Add(this.messageText);
            this.Name = "SendMessages";
            this.Size = new System.Drawing.Size(800, 600);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button sendMessage;
        private System.Windows.Forms.TextBox messageText;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.Label messageSentSuccess;
    }
}

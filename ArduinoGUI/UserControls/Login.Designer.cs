namespace ArduinoGUI.UserControls
{
    partial class Login
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
            this.username = new System.Windows.Forms.TextBox();
            this.password = new System.Windows.Forms.TextBox();
            this.loginAsSenderButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.loginAsReceiverButton = new System.Windows.Forms.Button();
            this.loginFailedMessage = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // username
            // 
            this.username.AccessibleRole = System.Windows.Forms.AccessibleRole.OutlineButton;
            this.username.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.username.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.username.Location = new System.Drawing.Point(68, 226);
            this.username.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.username.Name = "username";
            this.username.Size = new System.Drawing.Size(224, 26);
            this.username.TabIndex = 0;
            // 
            // password
            // 
            this.password.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.password.Location = new System.Drawing.Point(68, 294);
            this.password.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.password.Name = "password";
            this.password.Size = new System.Drawing.Size(224, 26);
            this.password.TabIndex = 1;
            // 
            // loginAsSenderButton
            // 
            this.loginAsSenderButton.Location = new System.Drawing.Point(68, 391);
            this.loginAsSenderButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.loginAsSenderButton.Name = "loginAsSenderButton";
            this.loginAsSenderButton.Size = new System.Drawing.Size(121, 44);
            this.loginAsSenderButton.TabIndex = 2;
            this.loginAsSenderButton.Text = "Login (Sender)";
            this.loginAsSenderButton.UseVisualStyleBackColor = true;
            this.loginAsSenderButton.Click += new System.EventHandler(this.LoginAsSender_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(64, 127);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(141, 29);
            this.label1.TabIndex = 3;
            this.label1.Text = "Login Page";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(65, 202);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 20);
            this.label2.TabIndex = 4;
            this.label2.Text = "Username";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(65, 269);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(79, 20);
            this.label3.TabIndex = 5;
            this.label3.Text = "Password";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Candara", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(51, 43);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(378, 49);
            this.label4.TabIndex = 6;
            this.label4.Text = "Lora Communication";
            // 
            // loginAsReceiverButton
            // 
            this.loginAsReceiverButton.Location = new System.Drawing.Point(205, 391);
            this.loginAsReceiverButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.loginAsReceiverButton.Name = "loginAsReceiverButton";
            this.loginAsReceiverButton.Size = new System.Drawing.Size(183, 44);
            this.loginAsReceiverButton.TabIndex = 7;
            this.loginAsReceiverButton.Text = "Login (Receiver)";
            this.loginAsReceiverButton.UseVisualStyleBackColor = true;
            this.loginAsReceiverButton.Click += new System.EventHandler(this.LoginAsReceiver_Click);
            // 
            // loginFailedMessage
            // 
            this.loginFailedMessage.AutoSize = true;
            this.loginFailedMessage.ForeColor = System.Drawing.Color.Red;
            this.loginFailedMessage.Location = new System.Drawing.Point(65, 335);
            this.loginFailedMessage.Name = "loginFailedMessage";
            this.loginFailedMessage.Size = new System.Drawing.Size(230, 20);
            this.loginFailedMessage.TabIndex = 8;
            this.loginFailedMessage.Text = "Login failed invalid credentials";
            // 
            // Login
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Azure;
            this.Controls.Add(this.loginFailedMessage);
            this.Controls.Add(this.loginAsReceiverButton);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.loginAsSenderButton);
            this.Controls.Add(this.password);
            this.Controls.Add(this.username);
            this.Font = new System.Drawing.Font("Century Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "Login";
            this.Size = new System.Drawing.Size(800, 600);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox username;
        private System.Windows.Forms.TextBox password;
        private System.Windows.Forms.Button loginAsSenderButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button loginAsReceiverButton;
        private System.Windows.Forms.Label loginFailedMessage;
    }
}

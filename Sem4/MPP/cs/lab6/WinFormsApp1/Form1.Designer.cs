namespace WinFormsApp1;

partial class Form1
{
    /// <summary>
    ///  Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    ///  Clean up any resources being used.
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
        button1 = new System.Windows.Forms.Button();
        label1 = new System.Windows.Forms.Label();
        label2 = new System.Windows.Forms.Label();
        textBox1 = new System.Windows.Forms.TextBox();
        textBox2 = new System.Windows.Forms.TextBox();
        SuspendLayout();
        // 
        // button1
        // 
        button1.Location = new System.Drawing.Point(322, 314);
        button1.Name = "button1";
        button1.Size = new System.Drawing.Size(159, 41);
        button1.TabIndex = 0;
        button1.Text = "Login";
        button1.UseVisualStyleBackColor = true;
        button1.Click += button1_Click;
        // 
        // label1
        // 
        label1.Location = new System.Drawing.Point(237, 147);
        label1.Name = "label1";
        label1.Size = new System.Drawing.Size(116, 37);
        label1.TabIndex = 1;
        label1.Text = "Username";
        label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
        label1.Click += label1_Click;
        // 
        // label2
        // 
        label2.Location = new System.Drawing.Point(267, 223);
        label2.Name = "label2";
        label2.Size = new System.Drawing.Size(57, 35);
        label2.TabIndex = 2;
        label2.Text = "Parola";
        label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
        // 
        // textBox1
        // 
        textBox1.Location = new System.Drawing.Point(354, 154);
        textBox1.Name = "textBox1";
        textBox1.Size = new System.Drawing.Size(126, 23);
        textBox1.TabIndex = 3;
        // 
        // textBox2
        // 
        textBox2.Location = new System.Drawing.Point(354, 228);
        textBox2.Name = "textBox2";
        textBox2.Size = new System.Drawing.Size(126, 23);
        textBox2.TabIndex = 4;
        // 
        // Form1
        // 
        AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
        AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        ClientSize = new System.Drawing.Size(800, 450);
        Controls.Add(textBox2);
        Controls.Add(textBox1);
        Controls.Add(label2);
        Controls.Add(label1);
        Controls.Add(button1);
        Text = "Login";
        ResumeLayout(false);
        PerformLayout();
    }

    private System.Windows.Forms.TextBox textBox1;
    private System.Windows.Forms.TextBox textBox2;

    private System.Windows.Forms.Label label2;

    private System.Windows.Forms.Label label1;

    private System.Windows.Forms.Button button1;

    #endregion
}
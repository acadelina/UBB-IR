using System.ComponentModel;

namespace WinFormsApp1;

partial class FormBilete
{
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private IContainer components = null;

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
        SpectacoleView = new System.Windows.Forms.DataGridView();
        id = new System.Windows.Forms.DataGridViewTextBoxColumn();
        artist = new System.Windows.Forms.DataGridViewTextBoxColumn();
        data = new System.Windows.Forms.DataGridViewTextBoxColumn();
        location = new System.Windows.Forms.DataGridViewTextBoxColumn();
        avseats = new System.Windows.Forms.DataGridViewTextBoxColumn();
        soseats = new System.Windows.Forms.DataGridViewTextBoxColumn();
        FilteredSpectacoleView = new System.Windows.Forms.DataGridView();
        artistFS = new System.Windows.Forms.DataGridViewTextBoxColumn();
        oraFS = new System.Windows.Forms.DataGridViewTextBoxColumn();
        locatieFS = new System.Windows.Forms.DataGridViewTextBoxColumn();
        avseatsFS = new System.Windows.Forms.DataGridViewTextBoxColumn();
        soseatsFS = new System.Windows.Forms.DataGridViewTextBoxColumn();
        dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
        Filtreaza = new System.Windows.Forms.Button();
        cump = new System.Windows.Forms.Label();
        label1 = new System.Windows.Forms.Label();
        cumparator = new System.Windows.Forms.TextBox();
        locuri = new System.Windows.Forms.TextBox();
        button1 = new System.Windows.Forms.Button();
        button2 = new System.Windows.Forms.Button();
        ((System.ComponentModel.ISupportInitialize)SpectacoleView).BeginInit();
        ((System.ComponentModel.ISupportInitialize)FilteredSpectacoleView).BeginInit();
        SuspendLayout();
        // 
        // dataGridView1
        // 
        SpectacoleView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
        SpectacoleView.MultiSelect = false;
        SpectacoleView.Location = new System.Drawing.Point(4, 3);
        SpectacoleView.Name = "dataGridView1";
        SpectacoleView.Size = new System.Drawing.Size(645, 131);
        SpectacoleView.TabIndex = 0;
        SpectacoleView.Text = "dataGridView1";
        this.SpectacoleView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.SpectacoleView_CellFormatting);
        SpectacoleView.CellContentClick += dataGridView1_CellContentClick;
       
        // 
        // dataGridView2
        // 
        FilteredSpectacoleView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
        FilteredSpectacoleView.Location = new System.Drawing.Point(4, 237);
        FilteredSpectacoleView.Name = "dataGridView2";
        FilteredSpectacoleView.Size = new System.Drawing.Size(543, 141);
        FilteredSpectacoleView.TabIndex = 1;
        FilteredSpectacoleView.MultiSelect = false;
        this.FilteredSpectacoleView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.FilteredSpectacolView_CellFormatting);
        FilteredSpectacoleView.Text = "dataGridView2";
       
        // 
        // dateTimePicker1
        // 
        dateTimePicker1.Location = new System.Drawing.Point(16, 158);
        dateTimePicker1.Name = "dateTimePicker1";
        dateTimePicker1.Size = new System.Drawing.Size(209, 23);
        dateTimePicker1.TabIndex = 2;
        // 
        // Filtreaza
        // 
        Filtreaza.Location = new System.Drawing.Point(252, 153);
        Filtreaza.Name = "Filtreaza";
        Filtreaza.Size = new System.Drawing.Size(129, 27);
        Filtreaza.TabIndex = 3;
        Filtreaza.Text = "Filtreaza";
        Filtreaza.UseVisualStyleBackColor = true;
        Filtreaza.Click += Filtreaza_Click;
        // 
        // cump
        // 
        cump.Location = new System.Drawing.Point(15, 386);
        cump.Name = "cump";
        cump.Size = new System.Drawing.Size(88, 16);
        cump.TabIndex = 4;
        cump.Text = "Cumparator";
        cump.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
        // 
        // label1
        // 
        label1.Location = new System.Drawing.Point(12, 414);
        label1.Name = "label1";
        label1.Size = new System.Drawing.Size(90, 24);
        label1.TabIndex = 5;
        label1.Text = "Nr. locuri";
        label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
        // 
        // cumparator
        // 
        cumparator.Location = new System.Drawing.Point(106, 384);
        cumparator.Name = "cumparator";
        cumparator.Size = new System.Drawing.Size(119, 23);
        cumparator.TabIndex = 6;
        // 
        // locuri
        // 
        locuri.Location = new System.Drawing.Point(106, 413);
        locuri.Name = "locuri";
        locuri.Size = new System.Drawing.Size(119, 23);
        locuri.TabIndex = 7;
        // 
        // button1
        // 
        button1.Location = new System.Drawing.Point(252, 394);
        button1.Name = "button1";
        button1.Size = new System.Drawing.Size(128, 27);
        button1.TabIndex = 8;
        button1.Text = "Adauga bilet";
        button1.UseVisualStyleBackColor = true;
        button1.Click += button1_Click;
        // 
        // button2
        // 
        button2.Location = new System.Drawing.Point(654, 393);
        button2.Name = "button2";
        button2.Size = new System.Drawing.Size(125, 29);
        button2.TabIndex = 9;
        button2.Text = "Logout";
        button2.UseVisualStyleBackColor = true;
        button2.Click += button2_Click;

        // 
        // FormBilete
        // 
        AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
        AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        ClientSize = new System.Drawing.Size(800, 450);
        Controls.Add(button2);
        Controls.Add(button1);
        Controls.Add(locuri);
        Controls.Add(cumparator);
        Controls.Add(label1);
        Controls.Add(cump);
        Controls.Add(Filtreaza);
        Controls.Add(dateTimePicker1);
        Controls.Add(FilteredSpectacoleView);
        Controls.Add(SpectacoleView);
        Text = "FormBilete";
        ((System.ComponentModel.ISupportInitialize)SpectacoleView).EndInit();
        ((System.ComponentModel.ISupportInitialize)FilteredSpectacoleView).EndInit();
        ResumeLayout(false);
        PerformLayout();
    }

    private System.Windows.Forms.Label cump;

    private System.Windows.Forms.TextBox cumparator;
    private System.Windows.Forms.TextBox locuri;
    private System.Windows.Forms.Button button1;
    private System.Windows.Forms.Button button2;

    private System.Windows.Forms.Label label1;

    private System.Windows.Forms.DataGridViewTextBoxColumn soseatsFS;
    private System.Windows.Forms.DateTimePicker dateTimePicker1;
    private System.Windows.Forms.Button Filtreaza;

    private System.Windows.Forms.DataGridViewTextBoxColumn artistFS;
    private System.Windows.Forms.DataGridViewTextBoxColumn oraFS;
    private System.Windows.Forms.DataGridViewTextBoxColumn locatieFS;
    private System.Windows.Forms.DataGridViewTextBoxColumn avseatsFS;

    private System.Windows.Forms.DataGridView FilteredSpectacoleView;

    private System.Windows.Forms.DataGridViewTextBoxColumn id;
    private System.Windows.Forms.DataGridViewTextBoxColumn artist;
    private System.Windows.Forms.DataGridViewTextBoxColumn data;
    private System.Windows.Forms.DataGridViewTextBoxColumn location;
    private System.Windows.Forms.DataGridViewTextBoxColumn avseats;
    private System.Windows.Forms.DataGridViewTextBoxColumn soseats;

    private System.Windows.Forms.DataGridView SpectacoleView;

    #endregion
}
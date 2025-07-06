

namespace WinFormsApp1
{

    public partial class Form1
    {
       

        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            dataGridViewClienti = new DataGridView();
            dataGridViewComenzi = new DataGridView();
            btnAdaugaComanda = new Button();
            btnStergeComanda = new Button();
            btnActualizeazaComanda = new Button();
            textBoxVarsta = new TextBox();
            labelNume = new Label();
            labelSponsor = new Label();
            labelAn = new Label();
            labelNumeC = new Label();
            labelVarsta = new Label();
            textBoxNume = new TextBox();
            textBoxSponsor = new TextBox();
            textBoxAn = new TextBox();
            textBoxNumeC = new TextBox();
            label1 = new Label();
            ((System.ComponentModel.ISupportInitialize)dataGridViewClienti).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewComenzi).BeginInit();
            SuspendLayout();
            // 
            // dataGridViewClienti
            // 
            dataGridViewClienti.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewClienti.Location = new Point(12, 12);
            dataGridViewClienti.Name = "dataGridViewClienti";
            dataGridViewClienti.RowHeadersWidth = 62;
            dataGridViewClienti.Size = new Size(400, 200);
            dataGridViewClienti.TabIndex = 0;
            dataGridViewClienti.SelectionChanged += dataGridViewClienti_SelectionChanged;
            // 
            // dataGridViewComenzi
            // 
            dataGridViewComenzi.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewComenzi.Location = new Point(12, 220);
            dataGridViewComenzi.Name = "dataGridViewComenzi";
            dataGridViewComenzi.RowHeadersWidth = 62;
            dataGridViewComenzi.Size = new Size(400, 150);
            dataGridViewComenzi.TabIndex = 1;
            // 
            // btnAdaugaComanda
            // 
            btnAdaugaComanda.Location = new Point(430, 220);
            btnAdaugaComanda.Name = "btnAdaugaComanda";
            btnAdaugaComanda.Size = new Size(120, 30);
            btnAdaugaComanda.TabIndex = 2;
            btnAdaugaComanda.Text = "Adaugă premiu";
            btnAdaugaComanda.UseVisualStyleBackColor = true;
            btnAdaugaComanda.Click += btnAdaugaComanda_Click;
            // 
            // btnStergeComanda
            // 
            btnStergeComanda.Location = new Point(430, 260);
            btnStergeComanda.Name = "btnStergeComanda";
            btnStergeComanda.Size = new Size(120, 30);
            btnStergeComanda.TabIndex = 3;
            btnStergeComanda.Text = "Șterge premiu";
            btnStergeComanda.UseVisualStyleBackColor = true;
            btnStergeComanda.Click += btnStergeComanda_Click;
            // 
            // btnActualizeazaComanda
            // 
            btnActualizeazaComanda.Location = new Point(430, 300);
            btnActualizeazaComanda.Name = "btnActualizeazaComanda";
            btnActualizeazaComanda.Size = new Size(120, 30);
            btnActualizeazaComanda.TabIndex = 4;
            btnActualizeazaComanda.Text = "Actualizează premiu";
            btnActualizeazaComanda.UseVisualStyleBackColor = true;
            btnActualizeazaComanda.Click += btnActualizeazaComanda_Click;
            // 
            // txtPretTotal
            // 
            textBoxVarsta.Location = new Point(577, 181);
            textBoxVarsta.Name = "txtPretTotal";
            textBoxVarsta.Size = new Size(120, 31);
            textBoxVarsta.TabIndex = 6;
            // 
            // labelNume
            // 
            labelNume.AutoSize = true;
            labelNume.Location = new Point(441, 19);
            labelNume.Name = "labelNume";
            labelNume.Size = new Size(64, 25);
            labelNume.TabIndex = 15;
            labelNume.Text = "Nume:";
            // 
            // labelSponsor
            // 
            labelSponsor.AutoSize = true;
            labelSponsor.Location = new Point(441, 64);
            labelSponsor.Name = "labelSponsor";
            labelSponsor.Size = new Size(83, 25);
            labelSponsor.TabIndex = 15;
            labelSponsor.Text = "Sponsor:";
            // 
            // labelAn
            // 
            labelAn.AutoSize = true;
            labelAn.Location = new Point(441, 107);
            labelAn.Name = "labelAn";
            labelAn.Size = new Size(38, 25);
            labelAn.TabIndex = 15;
            labelAn.Text = "An:";
            // 
            // labelNumeC
            // 
            labelNumeC.AutoSize = true;
            labelNumeC.Location = new Point(441, 141);
            labelNumeC.Name = "labelNumeC";
            labelNumeC.Size = new Size(75, 25);
            labelNumeC.TabIndex = 15;
            labelNumeC.Text = "NumeC:";
            // 
            // labelVarsta
            // 
            labelVarsta.AutoSize = true;
            labelVarsta.Location = new Point(441, 181);
            labelVarsta.Name = "labelVarsta";
            labelVarsta.Size = new Size(64, 25);
            labelVarsta.TabIndex = 15;
            labelVarsta.Text = "Varsta:";
            // 
            // textBoxNume
            // 
            textBoxNume.Location = new Point(577, 19);
            textBoxNume.Name = "textBoxNume";
            textBoxNume.Size = new Size(120, 31);
            textBoxNume.TabIndex = 11;
            // 
            // textBoxSponsor
            // 
            textBoxSponsor.Location = new Point(577, 64);
            textBoxSponsor.Name = "textBoxSponsor";
            textBoxSponsor.Size = new Size(120, 31);
            textBoxSponsor.TabIndex = 12;
            // 
            // textBoxAn
            // 
            textBoxAn.Location = new Point(577, 101);
            textBoxAn.Name = "textBoxAn";
            textBoxAn.Size = new Size(120, 31);
            textBoxAn.TabIndex = 13;
            // 
            // textBoxNumeC
            // 
            textBoxNumeC.Location = new Point(577, 141);
            textBoxNumeC.Name = "textBoxNumeC";
            textBoxNumeC.Size = new Size(120, 31);
            textBoxNumeC.TabIndex = 14;
            // 
            // label1
            // 
            label1.Location = new Point(0, 0);
            label1.Name = "label1";
            label1.Size = new Size(100, 23);
            label1.TabIndex = 0;
            // 
            // Form1
            // 
            ClientSize = new Size(817, 381);
            Controls.Add(textBoxNumeC);
            Controls.Add(textBoxAn);
            Controls.Add(textBoxSponsor);
            Controls.Add(textBoxNume);
            Controls.Add(labelNume);
            Controls.Add(labelSponsor);
            Controls.Add(labelAn);
            Controls.Add(labelNumeC);
            Controls.Add(labelVarsta);
            Controls.Add(textBoxVarsta);
            Controls.Add(btnActualizeazaComanda);
            Controls.Add(btnStergeComanda);
            Controls.Add(btnAdaugaComanda);
            Controls.Add(dataGridViewComenzi);
            Controls.Add(dataGridViewClienti);
            Name = "Form1";
            Text = "Aplicație Gestionare Comenzi";
            ((System.ComponentModel.ISupportInitialize)dataGridViewClienti).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewComenzi).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        private System.Windows.Forms.DataGridView dataGridViewClienti;
        private System.Windows.Forms.DataGridView dataGridViewComenzi;
        private System.Windows.Forms.Button btnAdaugaComanda;
        private System.Windows.Forms.Button btnStergeComanda;
        private System.Windows.Forms.Button btnActualizeazaComanda;
        private System.Windows.Forms.TextBox textBoxVarsta;
        private System.Windows.Forms.Label labelNume;
        private System.Windows.Forms.Label labelSponsor;
        private System.Windows.Forms.Label labelAn;
        private System.Windows.Forms.Label labelNumeC;
        private System.Windows.Forms.Label labelVarsta;
        private TextBox textBoxNume;
        private TextBox textBoxSponsor;
        private TextBox textBoxAn;
        private TextBox textBoxNumeC;

        private Label label1;
    }
}

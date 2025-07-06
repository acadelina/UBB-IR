

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
            flowLayoutPanel1 = new FlowLayoutPanel();
            dataGridViewChild = new DataGridView();
            dataGridViewParent = new DataGridView();
            btnAdauga = new Button();
            btnSterge = new Button();
            btnActualizeaza = new Button();
            txtPretTotal = new TextBox();
            dtpDataComanda = new DateTimePicker();
            labelDataComanda = new Label();
            labelPretTotal = new Label();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).BeginInit();
            SuspendLayout();
            // 
            // flowLayoutPanel1
            // 
            flowLayoutPanel1.Location = new Point(418, 12);
            flowLayoutPanel1.Name = "flowLayoutPanel1";
            flowLayoutPanel1.Size = new Size(518, 200);
            flowLayoutPanel1.TabIndex = 0;
            // 
            // dataGridViewChild
            // 
            dataGridViewChild.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewChild.Location = new Point(12, 12);
            dataGridViewChild.Name = "dataGridViewChild";
            dataGridViewChild.Size = new Size(400, 200);
            dataGridViewChild.TabIndex = 0;
            // 
            // dataGridViewParent
            // 
            dataGridViewParent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewParent.Location = new Point(12, 220);
            dataGridViewParent.Name = "dataGridViewParent";
            dataGridViewParent.Size = new Size(400, 150);
            dataGridViewParent.TabIndex = 1;
            // 
            // btnAdauga
            // 
            btnAdauga.Location = new Point(430, 220);
            btnAdauga.Name = "btnAdauga";
            btnAdauga.Size = new Size(120, 30);
            btnAdauga.TabIndex = 2;
            btnAdauga.Text = "Adaugă ";
            btnAdauga.UseVisualStyleBackColor = true;
            btnAdauga.Click += btnAdauga_Click;
            // 
            // btnSterge
            // 
            btnSterge.Location = new Point(430, 260);
            btnSterge.Name = "btnSterge";
            btnSterge.Size = new Size(120, 30);
            btnSterge.TabIndex = 3;
            btnSterge.Text = "Șterge";
            btnSterge.UseVisualStyleBackColor = true;
            btnSterge.Click += btnSterge_Click;
            // 
            // btnActualizeaza
            // 
            btnActualizeaza.Location = new Point(430, 300);
            btnActualizeaza.Name = "btnActualizeaza";
            btnActualizeaza.Size = new Size(120, 30);
            btnActualizeaza.TabIndex = 4;
            btnActualizeaza.Text = "Actualizează";
            btnActualizeaza.UseVisualStyleBackColor = true;
            btnActualizeaza.Click += btnActualizeaza_Click;
            // 
            // txtPretTotal
            // 
            txtPretTotal.Location = new Point(0, 0);
            txtPretTotal.Name = "txtPretTotal";
            txtPretTotal.Size = new Size(100, 23);
            txtPretTotal.TabIndex = 0;
            // 
            // dtpDataComanda
            // 
            dtpDataComanda.Location = new Point(0, 0);
            dtpDataComanda.Name = "dtpDataComanda";
            dtpDataComanda.Size = new Size(200, 23);
            dtpDataComanda.TabIndex = 0;
            // 
            // labelDataComanda
            // 
            labelDataComanda.Location = new Point(0, 0);
            labelDataComanda.Name = "labelDataComanda";
            labelDataComanda.Size = new Size(100, 23);
            labelDataComanda.TabIndex = 0;
            // 
            // labelPretTotal
            // 
            labelPretTotal.Location = new Point(0, 0);
            labelPretTotal.Name = "labelPretTotal";
            labelPretTotal.Size = new Size(100, 23);
            labelPretTotal.TabIndex = 0;
            // 
            // Form1
            // 
            ClientSize = new Size(948, 381);
            Controls.Add(flowLayoutPanel1);
            Controls.Add(btnActualizeaza);
            Controls.Add(btnSterge);
            Controls.Add(btnAdauga);
            Controls.Add(dataGridViewParent);
            Controls.Add(dataGridViewChild);
            Name = "Form1";
            Text = "Aplicație Gestionare Comenzi";
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).EndInit();
            ResumeLayout(false);
        }

        private System.Windows.Forms.DataGridView dataGridViewChild;
        private System.Windows.Forms.DataGridView dataGridViewParent;
        private System.Windows.Forms.Button btnAdauga;
        private System.Windows.Forms.Button btnSterge;
        private System.Windows.Forms.Button btnActualizeaza;
        private System.Windows.Forms.TextBox txtPretTotal;
        private System.Windows.Forms.DateTimePicker dtpDataComanda;
        private System.Windows.Forms.Label labelDataComanda;
        private System.Windows.Forms.Label labelPretTotal;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;


    }
}

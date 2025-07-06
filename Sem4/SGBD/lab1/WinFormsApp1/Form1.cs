using System.Data.SqlClient;
using System.Data;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Net.Security;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            LoadTipuri();
        }

        private string connectionString = "Data Source=LAPTOP-Q3R7T602\\SQLEXPRESS; Initial Catalog=Premii; Integrated Security=True; TrustServerCertificate=true;";
        SqlDataAdapter DataAdapter = new SqlDataAdapter();
        DataSet DataSetComanda = new DataSet();
        DataSet DataSetClient = new DataSet();
        BindingSource Source = new BindingSource();


        private void LoadTipuri()
        {

            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                DataAdapter = new SqlDataAdapter("SELECT * FROM Tip", conn);
                DataSetClient.Tables.Clear();
                DataAdapter.Fill(DataSetClient, "Tip");
                dataGridViewClienti.DataSource = DataSetClient.Tables["Tip"];
            }
        }

        void LoadPremii(int id)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                DataAdapter = new SqlDataAdapter("SELECT * FROM Premiu WHERE Id_tip = @id_tip", conn);
                DataAdapter.SelectCommand.Parameters.AddWithValue("@id_tip", id);
                DataSetComanda.Tables.Clear();
                DataAdapter.Fill(DataSetComanda, "Premiu");
                dataGridViewComenzi.DataSource = DataSetComanda.Tables["Premiu"];
            }
        }

       

        private void dataGridViewClienti_SelectionChanged(object sender, EventArgs e)
        {
            if (dataGridViewClienti.SelectedRows.Count > 0)
            {
                int selectedCnp = Convert.ToInt32(dataGridViewClienti.SelectedRows[0].Cells["Id_tip"].Value);
                LoadPremii(selectedCnp);
            }
        }

        private void btnAdaugaComanda_Click(object sender, EventArgs e)
        {
            if (dataGridViewClienti.SelectedRows.Count > 0)
            {
                int selectedCnp = Convert.ToInt32(dataGridViewClienti.SelectedRows[0].Cells["Id_tip"].Value);
                string nume;
                string sponsor;
                int an;
                string numec;
                int varsta;
                try
                {
                    nume = textBoxNume.Text;
                    sponsor=textBoxSponsor.Text;
                    an = Convert.ToInt32(textBoxAn.Text);
                    numec=textBoxNumeC.Text;
                    varsta= Convert.ToInt32(textBoxVarsta.Text);
                   
                }
                catch (FormatException)
                {
                    MessageBox.Show("Date introduse incorect", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }


                using (SqlConnection conn = new SqlConnection(connectionString))
                {
                    string insertCommand = "INSERT INTO Premiu (Nume, Sponsor, An,Nume_castigator,Varsta,Id_tip) VALUES (@Nume, @Sponsor, @An,@Nume_castigator,@Varsta,@Id_tip)";
                    SqlCommand cmd = new SqlCommand(insertCommand, conn);
                    cmd.Parameters.AddWithValue("@Nume", nume);
                    cmd.Parameters.AddWithValue("@Sponsor", sponsor);
                    cmd.Parameters.AddWithValue("@An", an);
                    cmd.Parameters.AddWithValue("@Nume_castigator", numec);
                    cmd.Parameters.AddWithValue("@Varsta", varsta);
                    cmd.Parameters.AddWithValue("@Id_tip", selectedCnp);


                    conn.Open();
                    cmd.ExecuteNonQuery();
                }
                LoadPremii(selectedCnp);
            }
            else
            {
                MessageBox.Show("Selectați un tip înainte de a crea un premiu!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnStergeComanda_Click(object sender, EventArgs e)
        {
            if (dataGridViewComenzi.SelectedRows.Count > 0)
            {

           
                int selectedIdComanda = 0;
                selectedIdComanda=Convert.ToInt32(dataGridViewComenzi.SelectedRows[0].Cells["Id_premiu"].Value);

                using (SqlConnection conn = new SqlConnection(connectionString))
                {
                    string deleteCommand = "DELETE FROM Premiu WHERE Id_premiu = @Id_premiu";
                    SqlCommand cmd = new SqlCommand(deleteCommand, conn);
                    cmd.Parameters.AddWithValue("@Id_premiu", selectedIdComanda);
                    conn.Open();
                    cmd.ExecuteNonQuery();
                }


                int selectedCnp = Convert.ToInt32(dataGridViewClienti.SelectedRows[0].Cells["Id_tip"].Value);
                LoadPremii(selectedCnp);
            }
            else
            {
                MessageBox.Show("Selectați un premiu!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);

            }
        }

        private void btnActualizeazaComanda_Click(object sender, EventArgs e)
        {
            if (dataGridViewComenzi.SelectedRows.Count > 0)
            {
                int selectedIdComanda = 0;
                selectedIdComanda=Convert.ToInt32(dataGridViewComenzi.SelectedRows[0].Cells["Id_premiu"].Value);
                
                string nume;
                string sponsor;
                int an;
                string numec;
                int varsta;
                try
                {
                    nume = textBoxNume.Text;
                    sponsor = textBoxSponsor.Text;
                    an = Convert.ToInt32(textBoxAn.Text);
                    numec = textBoxNumeC.Text;
                    varsta = Convert.ToInt32(textBoxVarsta.Text);

                }
                catch (FormatException)
                {
                    MessageBox.Show("Date introduse incorect", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }


                using (SqlConnection conn = new SqlConnection(connectionString))
                {
                    string updateCommand = "UPDATE Premiu SET Nume = @Nume, Sponsor=@Sponsor, An=@An, Nume_castigator=@Numec,Varsta=@Varsta WHERE Id_premiu= @Id_comanda";
                    SqlCommand cmd = new SqlCommand(updateCommand, conn);
                    cmd.Parameters.AddWithValue("@Nume", nume);
                    cmd.Parameters.AddWithValue("@Sponsor", sponsor);
                    cmd.Parameters.AddWithValue("@An", an);
                    cmd.Parameters.AddWithValue("@Numec", numec);
                    cmd.Parameters.AddWithValue("@Varsta", varsta);
                    cmd.Parameters.AddWithValue("@Id_comanda", selectedIdComanda);
                    conn.Open();
                    cmd.ExecuteNonQuery();
                }


                int selectedCnp = Convert.ToInt32(dataGridViewClienti.SelectedRows[0].Cells["Id_tip"].Value);
                LoadPremii(selectedCnp);
            }
            else
            {
                MessageBox.Show("Selectați un premiu!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

       
    }
}

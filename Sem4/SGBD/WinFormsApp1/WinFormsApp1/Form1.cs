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
using System.Configuration;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Populate();
            dataGridViewParent.SelectionChanged += new EventHandler(LoadChildren);
            dataGridViewChild.SelectionChanged += new EventHandler(LoadInformation);
            LoadParent();

        }

        private static string connectionString = ConfigurationManager.ConnectionStrings["cn"].ConnectionString.ToString();
        SqlDataAdapter da = new SqlDataAdapter();
        DataSet ds = new DataSet();
        private string childTableName = ConfigurationManager.AppSettings["ChildTableName"];
        private string parentTableName = ConfigurationManager.AppSettings["ParentTableName"];
        private string columnNamesInsertParameters = ConfigurationManager.AppSettings["ColumnNamesInsertParameters"];
        private List<string> columnNames = new List<string>(ConfigurationManager.AppSettings["ChildLabelNames"].Split(','));
        private List<string> columnTypes= new List<string>(ConfigurationManager.AppSettings["ChildColumnTypes"].Split(','));
        private List<string> paramsNames = new List<string>(ConfigurationManager.AppSettings["ColumnNamesInsertParameters"].Split(','));
        private List<string> columnInitiate = new List<string>(ConfigurationManager.AppSettings["ChildTextBoxContent"].Split(','));
        private SqlConnection connection = new SqlConnection(connectionString);
        private int nr = Convert.ToInt32(ConfigurationManager.AppSettings["ChildNumberOfColumns"]);
        private List<Control> textBoxes;
        private Label[] labels;

        private void LoadInformation(object sender, EventArgs e)
        {
            LoadInformation();
        }

        private void LoadInformation()
        {
            for (int i = 0; i < nr; i++)
            {
                var cellValue = dataGridViewChild.CurrentRow.Cells[i].Value;

                // Verifică dacă controlul este un DateTimePicker
                if (textBoxes[i] is DateTimePicker dateTimePicker)
                {
                    if (cellValue != DBNull.Value) 
                    {
                        dateTimePicker.Value = Convert.ToDateTime(cellValue); 
                    }
                }
                else if (textBoxes[i] is System.Windows.Forms.TextBox textBox)
                {
                    textBox.Text = Convert.ToString(cellValue); 
                }
            }
        }
        private bool ForeignKeyExists(int foreignKeyValue)
        {
            string checkQuery = $"SELECT COUNT(*) FROM {parentTableName} WHERE Id = @id";
            using (SqlCommand cmd = new SqlCommand(checkQuery, connection))
            {
                cmd.Parameters.AddWithValue("@id", foreignKeyValue);
                if (connection.State != ConnectionState.Open)
                {
                    connection.Open();
                }

                int count = (int)cmd.ExecuteScalar();
                connection.Close();
                return count > 0;
            }
        }
        private void Populate()
        {
            textBoxes = new List<Control>();
            labels = new Label[nr];

            for (int i = 0; i < nr; i++)
            {
                if (columnTypes[i].ToLower().Contains("date")) 
                {
                    DateTimePicker dateTimePicker = new DateTimePicker();
                    dateTimePicker.Format = DateTimePickerFormat.Short;
                    textBoxes.Add(dateTimePicker);
                }
                else
                {
                    System.Windows.Forms.TextBox textBox= new System.Windows.Forms.TextBox();
                    textBox.Text = columnInitiate[i];
                    textBoxes.Add(textBox);
                }

                labels[i] = new Label();
                labels[i].Text = columnNames[i];
            }
            flowLayoutPanel1.Controls.Clear();
            for (int i = 0; i < nr; i++)
            {
                flowLayoutPanel1.Controls.Add(textBoxes[i]);
                flowLayoutPanel1.Controls.Add(labels[i]);
            }

        }

        void LoadParent()
        {
            string select = ConfigurationSettings.AppSettings["SelectParent"];
            da.SelectCommand = new SqlCommand(select, connection);
            ds.Clear();
            da.Fill(ds);
            dataGridViewParent.DataSource = ds.Tables[0];
        }

        private void LoadChildren(object sender, EventArgs e)
        {
            LoadChildren();
        }

        private void LoadChildren()
        {
            int parentId = (int)dataGridViewParent.CurrentRow.Cells[0].Value;
            string select = ConfigurationManager.AppSettings["SelectChild"];
            SqlCommand cmd = new SqlCommand(select, connection);
            cmd.Parameters.AddWithValue("@id", parentId);
            SqlDataAdapter daChild = new SqlDataAdapter(cmd);
            DataSet dataSet = new DataSet();

            daChild.Fill(dataSet);
            dataGridViewChild.DataSource = dataSet.Tables[0];
        }

       

        private void btnAdauga_Click(object sender, EventArgs e)
        {
            try
            {
                string add = ConfigurationManager.AppSettings["InsertQuery"];
                SqlCommand cmd = new SqlCommand(add, connection);
                for (int i = 1; i < nr; i++)
                {
                    if (textBoxes[i] is DateTimePicker dateTimePicker)
                    {
                        cmd.Parameters.AddWithValue(paramsNames[i], dateTimePicker.Value.Date); 
                    }
                    else
                    {
                        if (columnTypes[i].ToLower() == "int" && !System.Text.RegularExpressions.Regex.IsMatch(textBoxes[i].Text, @"^\d+$"))
                        {
                            MessageBox.Show($"{columnNames[i]} trebuie să fie un număr întreg.");
                            return;
                        }
                        else if (columnTypes[i].ToLower() == "date")
                        {
                            
                            if (!DateTime.TryParse(textBoxes[i].Text, out _))
                            {
                                MessageBox.Show($"{columnNames[i]} nu este o dată validă.");
                                return;
                            }
                        }
                        cmd.Parameters.AddWithValue(paramsNames[i], textBoxes[i].Text); 
                    }
                }
                SqlDataAdapter daChild = new SqlDataAdapter(cmd);
                DataSet dataSet = new DataSet();
                connection.Open();
                daChild.Fill(dataSet);
                connection.Close();
                MessageBox.Show("Added!");
                LoadChildren();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
                connection.Close();
            }
        }

        private void btnSterge_Click(object sender, EventArgs e)
        {
            try
            {
                string delete = ConfigurationManager.AppSettings["DeleteQuery"];
                SqlCommand cmd = new SqlCommand(delete, connection);
                cmd.Parameters.AddWithValue("@id", (int)dataGridViewChild.CurrentRow.Cells[0].Value);
                SqlDataAdapter daChild = new SqlDataAdapter(cmd);
                DataSet dataSet = new DataSet();
                connection.Open();
                cmd.ExecuteNonQuery();
                daChild.Fill(dataSet);
                connection.Close();
                MessageBox.Show("Deleted!");
                LoadChildren();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
                connection.Close();
            }

        }

        private void btnActualizeaza_Click(object sender, EventArgs e)
        {
            try
            {
                string update = ConfigurationManager.AppSettings["UpdateQuery"];
                SqlCommand cmd = new SqlCommand(update, connection);
                for (int i = 0; i < nr; i++)
                {
                    if (columnTypes[i].ToLower() == "int" && !int.TryParse(textBoxes[i].Text, out _))
                    {
                        MessageBox.Show($"{columnNames[i]} trebuie să fie un număr întreg.");
                        return;
                    }
                    else if (columnTypes[i].ToLower() == "date" && !DateTime.TryParse(textBoxes[i].Text, out _))
                    {
                        MessageBox.Show($"{columnNames[i]} nu este o dată validă.");
                        return;
                    }
                    cmd.Parameters.AddWithValue(paramsNames[i], textBoxes[i].Text);
                }
                cmd.Parameters.AddWithValue("@id", (int)dataGridViewChild.CurrentRow.Cells[0].Value);
                SqlDataAdapter daChild = new SqlDataAdapter(cmd);
                DataSet dataSet = new DataSet();
                connection.Open();
                //cmd.ExecuteNonQuery();
                daChild.Fill(dataSet);
                connection.Close();
                MessageBox.Show("Updated!");
                LoadChildren();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
                connection.Close();
            }
        }
       

      
    }
}

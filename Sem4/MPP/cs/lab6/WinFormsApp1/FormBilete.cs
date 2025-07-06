using System.ComponentModel;
using Domain;
using WinFormsApp1.Service;

namespace WinFormsApp1;

public partial class FormBilete : Form
{
    private AppService appService;
    
    List<Spectacol> Spectacole = new List<Spectacol>();
    BindingList<Spectacol> SpectacoleBinding;

    List<FilteredSpectacol> FilteredSpectacole = new List<FilteredSpectacol>();
    BindingList<FilteredSpectacol> FilteredSpectacoleBinding;
    
    public FormBilete(AppService appService)
    {
        this.appService = appService;
        InitializeComponent();
        
        SpectacoleBinding = new BindingList<Spectacol>(Spectacole);
        SpectacoleView.DataSource = SpectacoleBinding;

        FilteredSpectacoleBinding = new BindingList<FilteredSpectacol>(FilteredSpectacole);
        FilteredSpectacoleView.DataSource = FilteredSpectacoleBinding;
        
        ShowSpectacole(appService.GetSpectacols());
    }

    void ShowSpectacole(IEnumerable<Spectacol> spectacole)
    {
        Spectacole.Clear();
        Spectacole.AddRange(spectacole);
        SpectacoleBinding.ResetBindings();
    }

    void ShowFilteredSpectacole(IEnumerable<Spectacol> filteredSpectacol)
    {
        FilteredSpectacole.Clear();
        FilteredSpectacole.AddRange(filteredSpectacol.Select(x => new FilteredSpectacol(x)));
        FilteredSpectacoleBinding.ResetBindings();
    }

   

    private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
    {
        throw new System.NotImplementedException();
    }

    private void Filtreaza_Click(object sender, EventArgs e)
    {
        ShowFilteredSpectacole(appService.GetSpectacolsByDate(dateTimePicker1.Value));
    }

    private void button1_Click(object sender, EventArgs e)
    {
        if (cumparator.Text == "" || locuri.Text=="")
        {
                 MessageBox.Show("Complete name and seats");
                 return;
        }
        var name=cumparator.Text;
        var loc = int.Parse(locuri.Text);
        Console.WriteLine(loc);
        Spectacol spectacol=null;
        
        if(FilteredSpectacoleView.SelectedRows.Count > 0)
                 spectacol=(FilteredSpectacoleView.SelectedRows[0].DataBoundItem as FilteredSpectacol).Spectacol;
        else
        {
            MessageBox.Show("Select a Spectacol");
            return;
        }
        

        try
        {
            appService.AddBilet(spectacol.Id, loc, name);
            MessageBox.Show("Bilet added");
            ShowSpectacole(appService.GetSpectacols());
            ShowFilteredSpectacole(appService.GetSpectacolsByDate(dateTimePicker1.Value));
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.StackTrace.ToString());
            MessageBox.Show(ex.Message);
        }
        
    }

    private void button2_Click(object sender, EventArgs e)
    {
        this.Close();
    }
    
    class FilteredSpectacol
    {
        public FilteredSpectacol(Spectacol spectacol)
        {
            Spectacol = spectacol;
        }

        [Browsable(false)]
        public Spectacol Spectacol { get; }

        public string Artist => Spectacol.Artist;

        public string Locatie => Spectacol.Location;
        public string Ora => Spectacol.Date.ToString("HH:mm");

        public int NrLocuriDisponibile => Spectacol.AvailableSeats;
        public int NrLocuriVandute => Spectacol.SoldSeats;

    }

    private void FilteredSpectacolView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
    {
        var row=FilteredSpectacoleView.Rows[e.RowIndex];
        int avseats=Convert.ToInt32(row.Cells["NrLocuriDisponibile"].Value);
        if (avseats == 0)
        {
            e.CellStyle.BackColor = Color.Red;
            e.CellStyle.ForeColor=Color.White;
        }
        else
        {
            e.CellStyle.BackColor = Color.White;
            e.CellStyle.ForeColor=Color.Black;
        }
    }
    
    private void SpectacoleView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
    {
        var row=SpectacoleView.Rows[e.RowIndex];
        int avseats=Convert.ToInt32(row.Cells["AvailableSeats"].Value);
        if (avseats == 0)
        {
            e.CellStyle.BackColor = Color.Red;
            e.CellStyle.ForeColor=Color.White;
        }
        else
        {
            e.CellStyle.BackColor = Color.White;
            e.CellStyle.ForeColor=Color.Black;
        }
    }
}
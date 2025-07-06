using System.ComponentModel;
using Domain;
using WinFormsApp1.Service;

namespace WinFormsApp1;

public partial class FormBilete : Form,Observer
{
    private IAppService appService;
    private Angajat angajat;
    List<Spectacol> Spectacole = new List<Spectacol>();
    BindingList<Spectacol> SpectacoleBinding;

    List<FilteredSpectacol> FilteredSpectacole = new List<FilteredSpectacol>();
    BindingList<FilteredSpectacol> FilteredSpectacoleBinding;
    
    public FormBilete(IAppService appService)
    {
        
        InitializeComponent();
        this.appService = appService;
        
        
        SpectacoleBinding = new BindingList<Spectacol>(Spectacole);
        SpectacoleView.DataSource = SpectacoleBinding;
        
        FilteredSpectacoleBinding = new BindingList<FilteredSpectacol>(FilteredSpectacole);
        FilteredSpectacoleView.DataSource = FilteredSpectacoleBinding;
       
       // ShowSpectacole(appService.GetSpectacols());
    }

    public void SetAngajat(Angajat angajat)
    {
        this.angajat = angajat;
        Init();
    }
    public void Init()
    {
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
            //ShowSpectacole(appService.GetSpectacols());
            //ShowFilteredSpectacole(appService.GetSpectacolsByDate(dateTimePicker1.Value));
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.StackTrace.ToString());
            MessageBox.Show(ex.Message);
        }
        
    }

    private void button2_Click(object sender, EventArgs e)
    {
        try
        {
            appService.logout(angajat);
        }
        catch (Exception ex)
        {
            MessageBox.Show(ex.Message);
        }
       
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

    public void update(Spectacol spectacol)
    {
        BeginInvoke(() =>
        {
            foreach (var spec in Spectacole)
                if (spec.Id == spectacol.Id)
                {
                    spec.AvailableSeats = spectacol.AvailableSeats;
                    spec.SoldSeats = spectacol.SoldSeats;
                    break;
                }

            foreach (var spec in FilteredSpectacole)
                if (spec.Spectacol.Id == spectacol.Id)
                {
                    spec.Spectacol.AvailableSeats = spectacol.AvailableSeats;
                    spec.Spectacol.SoldSeats = spectacol.SoldSeats;
                    break;
                }

            SpectacoleBinding.ResetBindings();
            FilteredSpectacoleBinding.ResetBindings();
        }); 
       

    }
}
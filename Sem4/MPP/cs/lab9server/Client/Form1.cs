using Domain;
using WinFormsApp1.Service;

namespace WinFormsApp1;

public partial class Form1 : Form
{
    private IAppService appService;
    public Form1(IAppService appService)
    {
        this.appService = appService;
        InitializeComponent();
        textBox2.UseSystemPasswordChar = true;
    }

    private void button1_Click(object sender, EventArgs e)
    {
        string username=textBox1.Text;
        string password=textBox2.Text;
        try
        {
            var specView = new FormBilete(appService);
            var ang=new Angajat(username, password,"");
            var angajat = appService.Login(ang,specView);
            if (angajat == null)
            {
                MessageBox.Show("Wrong username or password");
                return;
            }
            specView.SetAngajat(angajat);
            specView.Show();
        }
        catch (Exception exception)
        {
            MessageBox.Show(exception.Message);
            return;
        }

    }

    private void label1_Click(object sender, EventArgs e)
    {
        throw new System.NotImplementedException();
    }

  
}
using WinFormsApp1.Service;

namespace WinFormsApp1;

public partial class Form1 : Form
{
    private AppService appService;
    public Form1(AppService appService)
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
            appService.Login(username, password);
            var specView = new FormBilete(appService);
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
using Repository;
using WinFormsApp1.Service;

namespace WinFormsApp1;

static class Program
{
    /// <summary>
    ///  The main entry point for the application.
    /// </summary>
    [STAThread]
    static void Main()
    {
        
        var angajatRepo = new DbAngajatRepo(Config.DatabaseProperties);
        var spectacolRepo = new DbSpectacolRepo(Config.DatabaseProperties);
        var biletRepo = new DbBiletRepo(Config.DatabaseProperties,spectacolRepo);

        var angajatService=new AngajatService(angajatRepo);
        var spectacolService=new SpectacolService(spectacolRepo);
        var biletService=new BiletService(biletRepo,spectacolRepo);
        
        var appService=new AppService(angajatService, spectacolService, biletService);
        
       // angajatService.AddEmployee("ang","p1");
        
        Application.EnableVisualStyles();
        Application.SetCompatibleTextRenderingDefault(false);
        Application.Run(new Form1(appService));
    }
}
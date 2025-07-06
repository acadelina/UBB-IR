
using System.Globalization;
using log4net.Config;
using log4net;
using System.Reflection;
using System.Runtime.InteropServices.JavaScript;
using Domain;
using Repository;

namespace ConsoleApp1;

internal class Program
{
    private static readonly ILog log = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);

    static void Main(string[] args)
    {
        var logRepository = LogManager.GetRepository(Assembly.GetEntryAssembly());
        XmlConfigurator.Configure(logRepository, new FileInfo("log4net.config"));
        if (log.IsDebugEnabled)
        {
            log.Debug("log4net este inițializat corect.");
        }
        else
        {
            Console.WriteLine("log4net nu este inițializat corect.");
        }
        log.Info("Starting application");
        log.Debug("Acesta este un mesaj de debug.");
        log.Info("Acesta este un mesaj de info.");
        log.Error("Acesta este un mesaj de eroare.");
        var angajatRepo = new DbAngajatRepo(Config.DatabaseProperties);
        var spectacolRepo = new DbSpectacolRepo(Config.DatabaseProperties);
        var biletRepo = new DbBiletRepo(Config.DatabaseProperties,spectacolRepo);

        biletRepo.Add(new Bilet("Marin", 3, spectacolRepo.GetOne(1)));

        Console.WriteLine("\nAngajat dupa username si parola:");
        var angajatDupaUsername = angajatRepo.findByUsernamePassword("angajat1", "parola1");
        Console.WriteLine(angajatDupaUsername);
        Console.WriteLine("\nSpectacol dupa date:");
        foreach( Spectacol s in spectacolRepo.getBetwwenDates(new DateTime(2025, 3, 12,23,59,59),new DateTime(2026, 3, 20,23,59,59)))
        {
            Console.WriteLine(s);
        }

        Console.WriteLine("\nBilet dupa spectacol:");
        foreach (var b in biletRepo.getBiletBySpectacol(spectacolRepo.GetOne(1)) )
        {
            Console.WriteLine(b);
        }
        
        Console.WriteLine("\n\nShowing Angajati");
        Show(angajatRepo);
        Console.WriteLine("\n\nShowing Spectacole");
        Show(spectacolRepo);
        Console.WriteLine("\n\nShowing Bilete");
        Show(biletRepo);


        Console.WriteLine("Done.");
       
    }
    static void Show<ID, E>(Repository<ID, E> repo) where E:Entity<ID>
    {            
        var list = repo.GetAll().ToList();
        foreach(var item in list)
        {
            Console.WriteLine(item);
        }
    }

}
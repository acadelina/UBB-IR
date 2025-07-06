using System.Text.Json.Serialization;
using Domain;
using log4net;

namespace WinFormsApp1.Service;

public class AppService: IAppService
{
    private AngajatService angajatService;
    private SpectacolService spectacolService;
    private BiletService biletService;
    private readonly IDictionary<string, Observer> loggedClients;
    private ILog logger= LogManager.GetLogger(typeof(AppService));

    public AppService(AngajatService angajatService, SpectacolService spectacolService, BiletService biletService)
    {
        this.angajatService = angajatService;
        this.spectacolService = spectacolService;
        this.biletService = biletService;
        loggedClients = new Dictionary<string, Observer>();
        logger.Info("App Service started");
    }

    public Angajat Login(Angajat angajat,Observer observer)
    {
        Angajat ang;
        try
        {
            logger.Info("Login");
            try
            {
                ang = angajatService.connectAngajat(angajat.Username, angajat.Password);
            }
            catch (Exception e)
            {
                throw new Exception("Login failed", e);
            }
            if (loggedClients.ContainsKey(angajat.Username))
            {
                logger.Info("Angajat logged in");
                throw new ServiceException("Angajat is already logged in");
            }
            loggedClients.Add(angajat.Username, observer);
            logger.Info("Angajat succesffuly logged in");

        }
        catch (Exception e)
        {
            
            throw new ServiceException("Angajat login failed");
        }
        return ang;

    }

    public IEnumerable<Spectacol> GetSpectacols()
        => spectacolService.GetSpectacols();
    
    public IEnumerable<Spectacol> GetSpectacolsByDate(DateTime date)
    => spectacolService.GetSpectacolsByDate(date);

    public void AddBilet(long spectacolId, int seats, String name)
    {
      biletService.addBilet(name, spectacolId, seats);  
      var spectacol = spectacolService.GetSpectacolById(spectacolId);
      foreach (var observer in loggedClients.Values)
      {
          Task.Run(() =>observer.update(spectacol));
      }
     
    }

    public void logout(Angajat angajat)
    {
        loggedClients.Remove(angajat.Username);
    }
}
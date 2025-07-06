using System.Text.Json.Serialization;
using Domain;

namespace WinFormsApp1.Service;

public class AppService
{
    private AngajatService angajatService;
    private SpectacolService spectacolService;
    private BiletService biletService;

    public AppService(AngajatService angajatService, SpectacolService spectacolService, BiletService biletService)
    {
        this.angajatService = angajatService;
        this.spectacolService = spectacolService;
        this.biletService = biletService;
    }

    public Angajat Login(string username, string password)
    {
        return angajatService.connectAngajat(username, password);
    }

    public IEnumerable<Spectacol> GetSpectacols()
        => spectacolService.GetSpectacols();
    
    public IEnumerable<Spectacol> GetSpectacolsByDate(DateTime date)
    => spectacolService.GetSpectacolsByDate(date);
    
    public void AddBilet(long spectacolId, int seats,String name)
    =>biletService.addBilet(name, spectacolId, seats);
    
    
}
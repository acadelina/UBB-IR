using Domain;
using WinFormsApp1.Service;


public interface IAppService
{
    public Angajat Login(Angajat angajat,Observer observer);
    public IEnumerable<Spectacol> GetSpectacols();
    public IEnumerable<Spectacol> GetSpectacolsByDate(DateTime date);
    public void AddBilet(long spectacolId, int seats, String name);
    public void logout(Angajat angajat);

}
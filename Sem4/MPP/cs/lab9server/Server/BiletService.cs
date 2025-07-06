using Domain;
using log4net;
using Repository;

namespace WinFormsApp1.Service;

public class BiletService
{
    private static ILog logger = LogManager.GetLogger("BiletService");
    private BiletRepo biletRepo;
    private SpectacolRepo spectacolRepo;

    public BiletService(BiletRepo biletRepo,SpectacolRepo spectacolRepo)
    {
        this.biletRepo = biletRepo;
        this.spectacolRepo = spectacolRepo;
        logger.Info("BiletService initialized");
    }

    public void addBilet(String name, long spectacol, int seats)
    {
        try
        {
            var s = spectacolRepo.GetOne(spectacol);
            if (s.AvailableSeats < seats)
                throw new ServiceException("Not enough seats");
            s.AvailableSeats -= seats;
            s.SoldSeats+= seats;
            spectacolRepo.Update(s);

            Bilet b = new Bilet(name, seats, s);
            biletRepo.Add(b);
            logger.Info("Bilet added");

        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            throw new ServiceException(e.Message);
        }
    }

}
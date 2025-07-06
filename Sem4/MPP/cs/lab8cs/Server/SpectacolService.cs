using Domain;
using log4net;
using Repository;

namespace WinFormsApp1.Service;

public class SpectacolService
{
    private static ILog logger = LogManager.GetLogger("SpectacolService");
    private SpectacolRepo spectacolRepo;

    public SpectacolService(SpectacolRepo spectacolRepo)
    {
        this.spectacolRepo = spectacolRepo;
        logger.Info("SpectacolService initialized");
    }

    public Spectacol GetSpectacolById(long id)
    {
        return spectacolRepo.GetOne(id);
    }

    public IEnumerable<Spectacol> GetSpectacols()
    {
        try
        {
            logger.Info("SpectacolService getting spectacols");
            return spectacolRepo.GetAll();
        }
        catch (Exception ex)
        {
            throw new ServiceException(ex.Message);
        }
    }

    public IEnumerable<Spectacol> GetSpectacolsByDate(DateTime date)
    {
        try
        {
            logger.Info("SpectacolService getting spectacols by date");
            var y = date.Year;
            var m = date.Month;
            var d = date.Day;
            return spectacolRepo.getBetwwenDates(new DateTime(y, m, d, 0, 0, 0), new DateTime(y, m, d, 23, 59, 59));

        }
        catch (Exception e)
        {
            throw new ServiceException(e.Message);
        }
    }
    
}
using System.Runtime.InteropServices.JavaScript;
using Domain;

namespace Repository;

public interface SpectacolRepo:Repository<long,Spectacol>
{
    IEnumerable<Spectacol> getBetwwenDates(DateTime start, DateTime end);
}
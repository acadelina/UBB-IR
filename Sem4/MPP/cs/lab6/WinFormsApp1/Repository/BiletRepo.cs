using Domain;

namespace Repository;

public interface BiletRepo:Repository<long,Bilet>
{
    IEnumerable<Bilet> getBiletBySpectacol(Spectacol spec);
    
}
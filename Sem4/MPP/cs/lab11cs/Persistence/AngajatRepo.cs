
using Domain;

namespace Repository;

public interface AngajatRepo:Repository<long,Angajat>
{
    Angajat findByUsernamePassword(string username);
}
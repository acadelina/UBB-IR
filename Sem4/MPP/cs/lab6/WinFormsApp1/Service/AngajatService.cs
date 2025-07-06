using Domain;
using log4net;
using Repository;

namespace WinFormsApp1.Service;

public class AngajatService
{
    private static ILog logger = LogManager.GetLogger("AngajatService");
    private AngajatRepo angajatRepo;

    public AngajatService(AngajatRepo angajatRepo)
    {
        logger.Info("AngajatService constructor");
        this.angajatRepo = angajatRepo;
    }
    
    public Angajat connectAngajat(String username, String password)
    {
        try
        {
            logger.Info("AngajatService connectAngajat"); 
            var employee = angajatRepo.findByUsernamePassword(username);
           var pas=employee.Password;
           if (!BCrypt.Net.BCrypt.EnhancedVerify(password, pas))
           {
               throw new Exception("Invalid password");
           }
            if (employee == null) 
                throw new ServiceException("Invalid username or password");
            
            return employee;
        }
        catch (Exception ex)
        {
            throw new ServiceException(ex.Message);
        }
    }
    
    public void AddEmployee(string username, string password)
    {
        logger.Info($"add employee {username}");
        var passwordHash = BCrypt.Net.BCrypt.EnhancedHashPassword(password, 13);
        angajatRepo.Add(new Angajat( username, passwordHash,"mail"));
        logger.Info($"added employee {username}");
    }
    
}
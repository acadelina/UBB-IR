using System.Data;
using ConsoleApp1.Repository;
using Domain;
using log4net;

namespace Repository;

public class DbAngajatRepo:DbUtils<long,Angajat>,AngajatRepo
{
    private static readonly ILog log = LogManager.GetLogger("AngajatDbRepo");
    
    public DbAngajatRepo(IDictionary<string,string> props):base(props){}

    public void Add(Angajat entity)
    {
        log.Info($"Adding angajat: {entity.Id} ");
        int result = ExecuteNonQuery(
            "insert into angajati (username, password,email) values (@username, @password,@email) ",
            new Dictionary<string, object>
            {
                { "@username", entity.Username },
                { "@password", entity.Password },
                { "@email", entity.Mail }
            });
        if (result == 0)
        {
            log.Error($"Angajat was not added: {entity}");
            throw new RepoException("Angajat was not added");
        }

        log.Info($"Angajat was added");
    }

    public Angajat findByUsernamePassword(string username, string password)
    {
        log.Info($"Finding angajat :{username} {password}");
        return SelectFirst("select * from angajati where username=@username and password=@password",
            new Dictionary<string, object>
            {
                { "@username", username },
                { "@password", password },
            });
    }
    
    public List<Angajat> GetAll()
    {
        log.Info($"Selecting all angajati");
        return Select("select * from angajati").ToList();
    }

    public Angajat GetOne(long id)
    {
        log.Info($"Finding Angajat with id {id}");
        return SelectFirst("select * from angajati where id=@id", new Dictionary<string, object>
        {
            { "@id", id },
        });
    }

    public void Delete(Angajat entity)
    {
        log.Info($"Deleting Angajat with id {entity.Id}");
        var r=ExecuteNonQuery("delete from angajati where id=@id", new Dictionary<string, object>
        {
            { "@id", entity.Id },
        });
        if (r > 0)
            log.Info($"Deleted Angajat with id {entity.Id}");
    }

    public void Update(Angajat e)
    {
        log.Info($"Deleting Angajat with id {e.Id}");
        var r=ExecuteNonQuery("update angajati set email=@email where id=@id", new Dictionary<string, object>
        {
            { "@id", e.Id },
            {"@email", e.Mail },
        });
        if (r > 0)
            log.Info($"Updated Angajat with id {e.Id}");
    }
    

    protected override Angajat DecodeReader(IDataReader reader)
    {
        log.Info($"Deconding Angajat");
        var id = Convert.ToInt32(reader["id"]);
        var username = reader["username"] as string;
        var password = reader["password"] as string;
        var email = reader["mail"] as string;            
        var angajat = new Angajat(username, password, email);
        angajat.Id = id;
        return angajat;
    }
}

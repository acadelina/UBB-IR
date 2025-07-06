using System.Data;
using Domain;
using log4net;

namespace Repository;

public class DbBiletRepo:DbUtils<long,Bilet>,BiletRepo
{
    private static readonly ILog log = LogManager.GetLogger("BiletDbRepo");
    DbSpectacolRepo spectacolRepo;
        

        public DbBiletRepo(IDictionary<string, string> props,DbSpectacolRepo spectacolRepo) : base(props)
        {
            this.spectacolRepo = spectacolRepo;
        }

       
        public void Add(Bilet e)
        {
           
            Console.WriteLine($"Bilet: {e}");
            int result = ExecuteNonQuery("insert into bilete (buyer, spectacol, seats) " +
                "values (@numeC, @spectacol, @nrLocuri)", new Dictionary<string, object>
                {
                    { "@numeC", e.Buyer },
                    { "@spectacol", e.SpectacolC.Id},
                    { "@nrLocuri", e.SeatsNumber},
                });
            
        }

        public List<Bilet> GetAll()
        {
            return Select("select * from bilete").ToList();
        }

        public Bilet GetOne(long id)
        {
            log.Info($"Getting Bilet with id = {id}");
            return SelectFirst("select * from bilete where id = ?", new Dictionary<string, object>
            {
                { "@id", id },
            });
        }

        public IEnumerable<Bilet> getBiletBySpectacol(Spectacol spectacol)
        {
            log.Info($"Getting Bilet by {spectacol}");
            return Select("select  * from bilete where spectacol=@spectacol", new Dictionary<string, object>
            {
                { "@spectacol", spectacol.Id },
            });
        }

        public void Delete(Bilet e)
        {
            log.Error("Cannot remove Bilet");
            throw new NotImplementedException("Cannot remove Bilet");
        }

        public void Update(Bilet e)
        {
            log.Error("Cannot update Bilet");
            throw new NotImplementedException("Cannot update Bilet");
        }

        public static DateTime ConvertUnixTime(long unixTimeMilliseconds)
        {
            return DateTimeOffset.FromUnixTimeMilliseconds(unixTimeMilliseconds).DateTime;
        }
        protected override Bilet DecodeReader(IDataReader reader)
        {
            log.Info("Decoding Bilet");
            var numeC = reader["buyer"] as string;
            var spectId = Convert.ToInt32(reader["spectacol"]);
            var nrLocuri = Convert.ToInt32(reader["seats"]);
            var id = Convert.ToInt32(reader["id"]);
            
            
            var b = new Bilet(numeC, nrLocuri, spectacolRepo.GetOne(spectId));            
            b.Id = id;
            return b;
        }
    
}
using System.Data;
using System.Runtime.InteropServices.JavaScript;
using Domain;
using log4net;

namespace Repository;

public class DbSpectacolRepo:DbUtils<long,Spectacol>,SpectacolRepo
{
    private static readonly ILog log = LogManager.GetLogger("DbSpectacolRepo");
    
    public DbSpectacolRepo(IDictionary<string,string> properties):base(properties){}

    public void Add(Spectacol spectacol)
    {
        log.Info($"Add spectacol {spectacol}");

        int result = ExecuteNonQuery(
            "insert into spectacole (artist,dat,locatie,avseats,soseats) values(@artist,@dat,@locatie,@avseats,@soseats)",
            new Dictionary<string, object>
            {
                { "@artist", spectacol.Artist },
                { "@data", spectacol.Date },
                { "@locatie", spectacol.Location },
                { "@avseats", spectacol.AvailableSeats },
                { "@soseats", spectacol.SoldSeats },
            });
        if (result == 0)
        {
            log.Error("Spectacol insert failed");
            
        }
        log.Info($"Spectacol insert successful");
    }
    
    public List<Spectacol> GetAll()
        {
            return Select("select * from spectacole").ToList();
        }

        public IEnumerable<Spectacol> getBetwwenDates(DateTime start, DateTime end)
        {
            long startTimestamp = new DateTimeOffset(start).ToUnixTimeMilliseconds();
            long endTimestamp = new DateTimeOffset(end).ToUnixTimeMilliseconds();
            log.Info($"Getting spectacol between {start} and {end}");
            return Select("select * from spectacole where data between @start and @end", new Dictionary<string, object>
            {
                { "@start", startTimestamp },
                { "@end", endTimestamp },
            });
        }

        public Spectacol GetOne(long id)
        {
            log.Info($"Getting spectacol by {id}");
            return SelectFirst("select * from spectacole where id=@id", new Dictionary<string, object>
            {
                { "@id", id },
            });
        }

        public void Delete(Spectacol spectacol)
        {
            log.Info($"Deleting spectacol by {spectacol.Id}");
            var r = ExecuteNonQuery("delete from spectacole where id=@id", new Dictionary<string, object>
            {
                { "@id", spectacol.Id },
            });
            if(r>0)
            {
                log.Info($"Deleted spectacol by {spectacol.Id}");
            }
        }

       

        public void Update(Spectacol s)
        {
            log.Info($"Updating spectacol {s}");
            int result = ExecuteNonQuery("update \"Spectacol\" set " +
                "artist = @artist, " +
                "data = @data, " +
                "locatie = @locatie, " +
                "nrLocuriDisponibile = @nrDisp, " +
                "nrLocuriVandute = @nrVand) " +
                "values (@artist, @data, @locatie, @nrDisp, @nrVand) where id = @id", new Dictionary<string, object>
                {
                    { "@artist", s.Artist },
                    { "@data", s.Date},
                    { "@locatie", s.Location },
                    { "@nrDisp", s.AvailableSeats },
                    { "@nrVand", s.SoldSeats },
                    { "@id", s.Id }
                });
            
            log.Info($"Updated spectacol {s}");
        }

        public static DateTime ConvertUnixTime(long unixTimeMilliseconds)
        {
            return DateTimeOffset.FromUnixTimeMilliseconds(unixTimeMilliseconds).DateTime;
        }
        protected override Spectacol DecodeReader(IDataReader reader)
        {
            log.Info($"Decoding spectacol");
            var artist = reader["artist"] as string;
            var data =ConvertUnixTime( reader.GetInt64(reader.GetOrdinal("data")));
            var locatie = reader["location"] as string;
            var nrDisp = Convert.ToInt32(reader["avseats"]);
            var nrVand = Convert.ToInt32(reader["soseats"]);
            var id = Convert.ToInt32(reader["id"]);
            var s = new Spectacol(artist, data, locatie, nrDisp, nrVand);
            s.Id = id;
            return s;
        }

}
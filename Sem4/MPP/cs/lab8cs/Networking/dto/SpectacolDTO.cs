using System.Text.Json.Serialization;
using Domain;

namespace Networking.dto;

public class SpectacolDTO:EntityDTO
{
    public  string Artist { get; set; }
    public  DateTime Date { get; set; }
    public  string Location { get; set; }
    public  int AvailableSeats { get; set; }
    public  int SoldSeats { get; set; }
    
    [JsonConstructor]
    public SpectacolDTO(string artist, DateTime date, string location, int availableSeats, int soldSeats)
    {
        Artist = artist;
        Date = date;
        Location = location;
        AvailableSeats = availableSeats;
        SoldSeats = soldSeats;
    }

    public static SpectacolDTO FromSpectacol(Spectacol entity)
    {
        var s=new SpectacolDTO(entity.Artist,entity.Date,entity.Location,entity.AvailableSeats,entity.SoldSeats);
        s.Id = entity.Id;
        return s;
    }

    public Spectacol ToSpectacol()
    {
        var s=new Spectacol(Artist,Date,Location,AvailableSeats,SoldSeats);
        s.Id = Id;
        return s;
    }
}
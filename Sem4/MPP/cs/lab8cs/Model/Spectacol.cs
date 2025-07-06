using System.Runtime.InteropServices.JavaScript;

namespace lab8cs.Model;

public class Spectacol:Entity<long>
{
    public Spectacol(string artist, DateTime date, string location, int availableSeats, int soldSeats)
    {
        Artist=artist;
        Date=date;
        Location=location;
        AvailableSeats=availableSeats;
        SoldSeats=soldSeats;
    }
    public string Artist { get; set; }
    public DateTime Date { get; set; }
    public string Location { get; set; }
    public int AvailableSeats { get; set; }
    public int SoldSeats { get; set; }

    public override string ToString()
    {
        return Artist + " : " + Location + " : " + Date.ToShortDateString()+":"+AvailableSeats+":"+SoldSeats;
    }
}
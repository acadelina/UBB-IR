namespace lab8cs.Model;

public class Bilet:Entity<long>
{
    public Bilet(string buyer, int seatsNumber, Spectacol spectacol)
    {
        Buyer = buyer;
        SeatsNumber = seatsNumber;
        SpectacolC = spectacol;
    }
    
    public string Buyer { get; set; }   
    public int SeatsNumber { get; set; }
    public Spectacol SpectacolC { get; set; }

    public override string ToString()
    {
        return Buyer+":"+SeatsNumber+":"+SpectacolC.ToString();
    }
}
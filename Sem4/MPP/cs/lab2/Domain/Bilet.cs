namespace Domain;

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
    
    
    
}
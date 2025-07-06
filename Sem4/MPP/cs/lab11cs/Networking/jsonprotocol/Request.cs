using Networking.dto;

namespace Networking.jsonprotocol;

public class Request
{
    public RequestType Type { get; set; }
    public string String { get; set; }
    public string String2 { get; set; }
    public long Long { get; set; }
    public DateTime DateTime { get; set; }

    public int Int { get; set; }
    public AngajatDTO Angajat { get; set;}
    public SpectacolDTO Spectacol { get; set; }

    public override string ToString()
    {
        return $"Request{{type={Type}, angajat={Angajat}, spectacol={Spectacol}, date={DateTime}, string={String}, long={Long}, dateTime={DateTime}, int={Int},string2={String2}}} ";
    }
}
using Domain;
using Networking.dto;

namespace Networking.jsonprotocol;
[Serializable]
public class Response
{
    public ResponseType Type { get; set; }
    public string ErrorMessage { get; set; }
    public AngajatDTO Angajat { get; set; }
    public SpectacolDTO Spectacol { get; set; }
    public SpectacolDTO[] Spectacols { get; set; }

    public override string ToString()
    {
        return $"Response{{type={Type}, angajat={Angajat}, spectacols={Spectacols}}}";
    }
}
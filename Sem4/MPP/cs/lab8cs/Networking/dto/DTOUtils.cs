using Domain;

namespace Networking.dto;

public class DTOUtils
{
    public static AngajatDTO getAngajatDTO(Angajat angajat)
    {
        return AngajatDTO.fromAngajat(angajat);
    }

    public static SpectacolDTO getSpectacolDTO(Spectacol spectacol)
    {
        return SpectacolDTO.FromSpectacol(spectacol);
    }

    public static SpectacolDTO[] getSpectacolDTOs(IEnumerable<Spectacol> spectacols)
    {
        return spectacols
            .Select(DTOUtils.getSpectacolDTO)
            .ToArray();
    }

    public static Spectacol fromSpectacolDTO(SpectacolDTO spectacolDTO)
    {
        return spectacolDTO.ToSpectacol();
    }

    public static Spectacol[] fromSpectacolDTOs(IEnumerable<SpectacolDTO> spectacolDTOs)
    {
        return spectacolDTOs.Select(DTOUtils.fromSpectacolDTO).ToArray();
    }

    public static Angajat fromAngajatDTO(AngajatDTO angajatDTO)
    {
        return angajatDTO.toAngajat();
    }
}
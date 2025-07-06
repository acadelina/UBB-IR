package ubb.scs.mpp.Network.dto;

import ubb.scs.mpp.model.Angajat;
import ubb.scs.mpp.model.Spectacol;

import java.util.stream.StreamSupport;

public class DTOUtils {
    public static AngajatDTO getAngajatDTO(Angajat angajat) {
        return AngajatDTO.fromAngajat(angajat);
    }

    public static SpetacolDTO getSpetacolDTO(Spectacol spectacol) {
        return SpetacolDTO.fromSpectacol(spectacol);
    }

    public static SpetacolDTO[] getSpetacolDTOs(Iterable<Spectacol> spectacols) {
        return StreamSupport.stream(spectacols.spliterator(),false)
                .map(DTOUtils::getSpetacolDTO)
                .toArray(SpetacolDTO[]::new);
    }

    public static Spectacol fromSpetacolDTO(SpetacolDTO spetacolDTO) {
        return spetacolDTO.toSpectacol();
    }

    public static Spectacol[] fromSpetacolDTOs(Iterable<SpetacolDTO> spetacolDTOs) {
        return StreamSupport.stream(spetacolDTOs.spliterator(),false)
                .map(DTOUtils::fromSpetacolDTO)
                .toArray(Spectacol[]::new);
    }

    public static Angajat fromAngajatDTO(AngajatDTO angajat) {
        return angajat.toAngajat();
    }
}

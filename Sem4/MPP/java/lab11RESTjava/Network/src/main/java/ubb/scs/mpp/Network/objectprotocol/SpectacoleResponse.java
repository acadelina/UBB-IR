package ubb.scs.mpp.Network.objectprotocol;

import ubb.scs.mpp.Network.dto.DTOUtils;
import ubb.scs.mpp.Network.dto.SpetacolDTO;
import ubb.scs.mpp.model.Spectacol;

import java.io.Serializable;
import java.util.Arrays;
import java.util.List;

public class SpectacoleResponse implements Response{
    private final SpetacolDTO[] spetacole;

    protected SpectacoleResponse(final Spectacol[] spetacole) {
        this.spetacole = DTOUtils.getSpetacolDTOs(Arrays.asList(spetacole));
    }

    public List<SpetacolDTO> getSpetacole() {
        return Arrays.asList(spetacole);
    }



}

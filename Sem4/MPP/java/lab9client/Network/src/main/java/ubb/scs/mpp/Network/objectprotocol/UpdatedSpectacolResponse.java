package ubb.scs.mpp.Network.objectprotocol;

import ubb.scs.mpp.Network.dto.SpetacolDTO;

import java.io.Serializable;

public class UpdatedSpectacolResponse implements Response{
    SpetacolDTO spetacol;

    public UpdatedSpectacolResponse(SpetacolDTO spetacol) {
        this.spetacol = spetacol;
    }
    public SpetacolDTO getSpetacol() {
        return spetacol;
    }
}

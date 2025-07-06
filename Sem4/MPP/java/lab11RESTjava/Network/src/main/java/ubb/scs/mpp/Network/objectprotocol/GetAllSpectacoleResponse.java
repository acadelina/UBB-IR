package ubb.scs.mpp.Network.objectprotocol;

import ubb.scs.mpp.model.Spectacol;

public class GetAllSpectacoleResponse extends SpectacoleResponse {
    public GetAllSpectacoleResponse(Spectacol[] spectacoles) {
        super(spectacoles);
    }
}

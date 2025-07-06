package ubb.scs.mpp.Network.objectprotocol;

import ubb.scs.mpp.Network.dto.AngajatDTO;

public class LoginAngajatResponse implements Response {

    private AngajatDTO angajat;
    public LoginAngajatResponse(AngajatDTO angajat) {
        this.angajat = angajat;
    }
    public AngajatDTO getAngajat() {
        return angajat;
    }

}

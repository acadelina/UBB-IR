package ubb.scs.mpp.Network.dto;

import ubb.scs.mpp.model.Angajat;

public class AngajatDTO extends EntityDTO {

    private final String username;
    private final String password;
    private final String mail;
    public AngajatDTO(final String username, final String password,final String mail) {
        this.username = username;
        this.password = password;
        this.mail = mail;
    }
    public String getUsername() {
        return username;
    }
    public String getPassword() {
        return password;
    }
    public String getMail() {
        return mail;
    }
    public static AngajatDTO fromAngajat(Angajat entity) {
            var a=new AngajatDTO(entity.getUsername(), entity.getPassword(), entity.getMail());
            a.setId(entity.getId());
            return a;
    }

    public Angajat toAngajat() {
        var a=new Angajat(getUsername(), getPassword(),getMail());
        a.setId(getId());
        return a;
    }
}

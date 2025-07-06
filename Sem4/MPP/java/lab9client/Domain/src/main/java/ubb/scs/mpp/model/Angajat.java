package ubb.scs.mpp.model;


import jakarta.persistence.Column;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

@jakarta.persistence.Entity
@Table(name="angajati")
public class Angajat extends ubb.scs.mpp.model.Entity<Long> {
    @Id
    @GeneratedValue(generator = "increment")
    @Column(name = "id")
    private Long id;
    private String username;
    private String password;
    private String mail;

    public Angajat(String username, String password, String mail) {
        this.username = username;
        this.password = password;
        this.mail = mail;
    }

    public Angajat() {

    }

    @Column(name="username")
    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    @Column(name="password")
    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Column(name="mail")
    public String getMail() {
        return mail;
    }

    public void setMail(String mail) {
        this.mail = mail;
    }

    @Override
    public String toString() {
        return "Angajat [username=" + username + ", password=" + password + ", mail=" + mail + "]";
    }

    @Override
    public Long getId() {
        return id;
    }

    @Override
    public void setId(Long aLong) {
        this.id = aLong;
    }
}

package ubb.scs.map.vacanta.Domain;

public class Client extends Entity<Long> {
    String name;
    Integer fidelitygrade;
    Integer varsta;
    Hobbies hobbies;

    public Client(String name, Integer fidelitygrade, Integer varsta, Hobbies hobbies) {
        this.name = name;
        this.fidelitygrade = fidelitygrade;
        this.varsta = varsta;
        this.hobbies = hobbies;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getFidelitygrade() {
        return fidelitygrade;
    }

    public void setFidelitygrade(Integer fidelitygrade) {
        this.fidelitygrade = fidelitygrade;
    }

    public Integer getVarsta() {
        return varsta;
    }

    public void setVarsta(Integer varsta) {
        this.varsta = varsta;
    }

    public Hobbies getHobbies() {
        return hobbies;
    }

    public void setHobbies(Hobbies hobbies) {
        this.hobbies = hobbies;
    }
}

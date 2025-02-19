package ubb.scs.map.faptebune.Domain;

import java.time.LocalDateTime;

public class Nevoie extends Entity<Long>{
    String titlu;
    String descriere;
    LocalDateTime deadline;
    Long omInNevoie;
    Long omSalvator;
    String status;

    public Nevoie(String titlu, String descriere, LocalDateTime deadline, Long omInNevoie, Long omSalvator, String status) {
        this.titlu = titlu;
        this.descriere = descriere;
        this.deadline = deadline;
        this.omInNevoie = omInNevoie;
        this.omSalvator = omSalvator;
        this.status = status;
    }

    public Nevoie(String titlu, String descriere, LocalDateTime deadline, Long omInNevoie) {
        this.titlu = titlu;
        this.descriere = descriere;
        this.deadline = deadline;
        this.omInNevoie = omInNevoie;
        this.status = "Caut erou!";
        this.omSalvator = null;
    }

    public String getTitlu() {
        return titlu;
    }

    public void setTitlu(String titlu) {
        this.titlu = titlu;
    }

    public String getDescriere() {
        return descriere;
    }

    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    public LocalDateTime getDeadline() {
        return deadline;
    }

    public void setDeadline(LocalDateTime deadline) {
        this.deadline = deadline;
    }

    public Long getOmInNevoie() {
        return omInNevoie;
    }

    public void setOmInNevoie(Long omInNevoie) {
        this.omInNevoie = omInNevoie;
    }

    public Long getOmSalvator() {
        return omSalvator;
    }

    public void setOmSalvator(Long omSalvator) {
        this.omSalvator = omSalvator;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}

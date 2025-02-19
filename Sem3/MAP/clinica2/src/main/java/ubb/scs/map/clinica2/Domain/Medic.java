package ubb.scs.map.clinica2.Domain;

public class Medic extends Entity<Long>{
    Long idSectie;
    String nume;
    Integer vechime;
    String rezident;

    @Override
    public String toString() {
        return "Medic{" +
                "idSectie=" + idSectie +
                ", nume='" + nume + '\'' +
                ", vechime=" + vechime +
                ", rezident='" + rezident + '\'' +
                '}';
    }

    public Long getIdSectie() {
        return idSectie;
    }

    public void setIdSectie(Long idSectie) {
        this.idSectie = idSectie;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public Integer getVechime() {
        return vechime;
    }

    public void setVechime(Integer vechime) {
        this.vechime = vechime;
    }

    public String getRezident() {
        return rezident;
    }

    public void setRezident(String rezident) {
        this.rezident = rezident;
    }

    public Medic(Long idSectie, String nume, Integer vechime, String rezident) {
        this.idSectie = idSectie;
        this.nume = nume;
        this.vechime = vechime;
        this.rezident = rezident;
    }
}

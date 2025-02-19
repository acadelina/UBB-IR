package ubb.scs.map.clinica2.Domain;

import java.time.LocalDateTime;

public class Consultatie extends Entity<Long>{
    Long idmedic;
    Long cnppacient;
    String numepacient;
    LocalDateTime data;

    public Long getIdmedic() {
        return idmedic;
    }

    public void setIdmedic(Long idmedic) {
        this.idmedic = idmedic;
    }

    public Long getCnppacient() {
        return cnppacient;
    }

    public void setCnppacient(Long cnppacient) {
        this.cnppacient = cnppacient;
    }

    public String getNumepacient() {
        return numepacient;
    }

    public void setNumepacient(String numepacient) {
        this.numepacient = numepacient;
    }

    public LocalDateTime getData() {
        return data;
    }

    public void setData(LocalDateTime data) {
        this.data = data;
    }

    public Consultatie(Long idmedic, Long cnppacient, String numepacient, LocalDateTime data) {
        this.idmedic = idmedic;
        this.cnppacient = cnppacient;
        this.numepacient = numepacient;
        this.data = data;
    }
}

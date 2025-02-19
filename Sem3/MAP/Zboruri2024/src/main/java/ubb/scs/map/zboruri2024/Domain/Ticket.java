package ubb.scs.map.zboruri2024.Domain;

import java.time.LocalDateTime;

public class Ticket extends Entity<Long>{
    String username;
    Long idflight;
    LocalDateTime purchaseTime;

    public Ticket(String username, Long idflight, LocalDateTime purchaseTime) {
        this.username = username;
        this.idflight = idflight;
        this.purchaseTime = purchaseTime;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public Long getIdflight() {
        return idflight;
    }

    public void setIdflight(Long idflight) {
        this.idflight = idflight;
    }

    public LocalDateTime getPurchaseTime() {
        return purchaseTime;
    }

    public void setPurchaseTime(LocalDateTime purchaseTime) {
        this.purchaseTime = purchaseTime;
    }
}

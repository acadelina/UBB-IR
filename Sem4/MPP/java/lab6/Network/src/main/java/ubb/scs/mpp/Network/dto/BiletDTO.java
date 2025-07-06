package ubb.scs.mpp.Network.dto;

public class BiletDTO extends EntityDTO {
    private final String buyer;
    private final int seats;
    private final SpetacolDTO spetacol;

    public BiletDTO(final String buyer, final int seats, final SpetacolDTO spetacol) {
        this.buyer = buyer;
        this.seats = seats;
        this.spetacol = spetacol;
    }

    public String getBuyer() {
        return buyer;
    }
    public int getSeats() {
        return seats;
    }
    public SpetacolDTO getSpetacol() {
        return spetacol;
    }

}

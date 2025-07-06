package ubb.scs.mpp.Network.objectprotocol;

import ubb.scs.mpp.Network.dto.SpetacolDTO;
import ubb.scs.mpp.model.Spectacol;

public class ReserveBiletRequest implements Request {
        SpetacolDTO spetacol;
        String buyer;
        int seats;

        public ReserveBiletRequest(SpetacolDTO spetacol, String buyer, int seats) {
            this.spetacol = spetacol;
            this.buyer = buyer;
            this.seats = seats;
        }
        public SpetacolDTO getSpetacol() {
            return spetacol;
        }
        public String getBuyer() {
            return buyer;
        }
        public int getSeats() {
            return seats;
        }
}

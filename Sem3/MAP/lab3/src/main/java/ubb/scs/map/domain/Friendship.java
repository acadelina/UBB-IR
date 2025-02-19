package ubb.scs.map.domain;

import java.time.LocalDateTime;

public class Friendship extends Entity<Tuple<Long,Long>> {
    private final LocalDateTime date = LocalDateTime.now();
    private User u1,u2;

    public Friendship() {
    }

    public Friendship(User u1, User u2) {
        this.u1 = u1;
        this.u2 = u2;
        super.setId(new Tuple<>(u1.getId(), u2.getId()));
    }

    LocalDateTime getDate() {
        return date;
    }

   public Tuple<Long,Long> getUsers() {
        return super.getId();
   }
}

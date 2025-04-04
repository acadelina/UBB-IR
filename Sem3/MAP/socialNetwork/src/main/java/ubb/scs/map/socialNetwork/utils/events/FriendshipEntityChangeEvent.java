package ubb.scs.map.socialNetwork.utils.events;

import ubb.scs.map.socialNetwork.domain.Friendship;

public class FriendshipEntityChangeEvent implements Event {
    private ChangeEventType type;
    private Friendship data, oldData;

    public FriendshipEntityChangeEvent(ChangeEventType type,Friendship data) {
        this.type = type;
        this.data = data;
    }
    public FriendshipEntityChangeEvent(ChangeEventType type, Friendship data, Friendship oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Friendship getData() {
        return data;
    }

    public Friendship getOldData() {
        return oldData;
    }
}

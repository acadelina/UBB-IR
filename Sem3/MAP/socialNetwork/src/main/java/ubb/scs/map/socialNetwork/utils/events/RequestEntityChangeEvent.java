package ubb.scs.map.socialNetwork.utils.events;

import ubb.scs.map.socialNetwork.domain.FriendRequest;

public class RequestEntityChangeEvent implements Event{
    private ChangeEventType type;
    private FriendRequest data, oldData;

    public RequestEntityChangeEvent(ChangeEventType type,FriendRequest data) {
        this.type = type;
        this.data = data;
    }
    public RequestEntityChangeEvent(ChangeEventType type, FriendRequest data, FriendRequest oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public FriendRequest getData() {
        return data;
    }

    public FriendRequest getOldData() {
        return oldData;
    }
}

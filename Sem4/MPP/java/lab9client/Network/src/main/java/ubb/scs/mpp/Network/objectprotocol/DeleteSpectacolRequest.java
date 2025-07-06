package ubb.scs.mpp.Network.objectprotocol;

public class DeleteSpectacolRequest implements Request{
    private long id;
    public DeleteSpectacolRequest(long id) {
        this.id = id;
    }
    public long getId() {return id;}
}

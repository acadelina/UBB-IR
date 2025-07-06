package ubb.scs.mpp.Network.objectprotocol;

import java.io.Serializable;

public class ErrorResponse implements Response {
    private final String message;
    public ErrorResponse(final String message) {
        this.message = message;
    }
    public ErrorResponse(final Exception e) {
        this.message = e.getMessage();
    }
    public String getMessage() {
        return message;
    }
    @Override
    public String toString() {
        return "ErrorResponse [message=" + message + "]";
    }
}

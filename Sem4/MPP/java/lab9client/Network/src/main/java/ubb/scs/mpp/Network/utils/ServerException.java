package ubb.scs.mpp.Network.utils;

import java.io.IOException;

public class ServerException extends Exception {
    public ServerException(String closingServerError, Throwable e) {
        super(closingServerError, e);
    }
    public ServerException(String message) {
        super(message);
    }
}

package ubb.scs.mpp.Network.objectprotocol;

public class LoginAngajatRequest implements Request {
    private final String username;
    private final String password;

    public String getPassword() {
        return password;
    }

    public String getUsername() {
        return username;
    }

    public LoginAngajatRequest(String username, String password) {
        this.username = username;
        this.password = password;
    }
}

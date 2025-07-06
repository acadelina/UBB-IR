package ubb.scs.mpp.restt.client;

import org.springframework.web.client.ResourceAccessException;
import org.springframework.web.client.RestClient;
import org.springframework.web.client.RestTemplate;
import ubb.scs.mpp.fest.services.rest.LoginRequest;
import ubb.scs.mpp.fest.services.rest.ServiceException;
import org.springframework.web.client.HttpClientErrorException;
import ubb.scs.mpp.model.Spectacol;

import java.util.concurrent.Callable;

import static org.springframework.http.MediaType.APPLICATION_JSON;

public class SpectacolClient {
    private String token;
    public static final String URL = "http://localhost:8080/festival/spectacole";
    private RestTemplate restTemplate = new RestTemplate();

    public void login(String username, String password) {
        var authClient = RestClient.create();
        var request = new LoginRequest(username, password);
        this.token = authClient.post()
                .uri("http://localhost:8080/api/login")
                .contentType(APPLICATION_JSON)
                .body(request)
                .retrieve()
                .body(String.class);
    }

    private <T> T execute(Callable<T> callable) {
        try {
            return callable.call();
        } catch (ResourceAccessException | HttpClientErrorException e) {
            throw new ServiceException(e);
        } catch (Exception e) {
            throw new ServiceException(e);
        }
    }

    public Spectacol[] getAll(){
        return execute(()->restTemplate.getForObject(URL, Spectacol[].class));
    }

    public Spectacol getById(Long id){
        return execute(() -> restTemplate.getForObject(String.format("%s/%s", URL, id), Spectacol.class));
    }

    public Spectacol create(Spectacol user) {
        return execute(() -> restTemplate.postForObject(URL, user, Spectacol.class));
    }

    public void update(Spectacol user) {
        execute(() -> {
            restTemplate.put(String.format("%s/%s", URL, user.getId()), user);
            return null;
        });
    }

    public void delete(Long id) {
        execute(() -> {
            restTemplate.delete(String.format("%s/%s", URL, id));
            return null;
        });
    }
}

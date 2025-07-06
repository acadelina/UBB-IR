package ubb.scs.mpp.start;

import org.springframework.web.client.RestClientException;
import ubb.scs.mpp.fest.services.rest.ServiceException;
import ubb.scs.mpp.model.Spectacol;
import ubb.scs.mpp.model.SpectacolDTO;
import ubb.scs.mpp.restt.client.NewSpectacolClient;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class StartRestClient {
    private final static NewSpectacolClient newSpectacolClient = new NewSpectacolClient();
    public static void main(String[] args) {


        SpectacolDTO spectacol=new SpectacolDTO();
        spectacol.setArtist("a");
        spectacol.setAvailable_seats("10");
        spectacol.setLocation("loc");
        spectacol.setSold_seats("10");
        spectacol.setData(LocalDateTime.now().format(DateTimeFormatter.ISO_DATE_TIME));

        try {
            System.out.println("Adding new spectacol" + spectacol);
            var spectacoladaugat=newSpectacolClient.create(spectacol);
            show(() -> System.out.println(spectacoladaugat));
            System.out.println("\nPrinting all spectacols");
            show(() -> {
                SpectacolDTO[] spectacols = newSpectacolClient.getAll();
                for (SpectacolDTO spec : spectacols) {
                    System.out.println(spec);
                }
            });
            System.out.println("\nPrinting spectacol with id "+spectacoladaugat.getId());
            show(()-> System.out.println(newSpectacolClient.getById(Long.parseLong(spectacoladaugat.getId()))));

            System.out.println("\nUpdating spectacol with id "+spectacoladaugat.getId());
            spectacol.setArtist("updated");
            spectacol.setAvailable_seats("15");
            spectacol.setLocation("updated");
            spectacol.setSold_seats("15");
            spectacol.setData(LocalDateTime.now().format(DateTimeFormatter.ISO_DATE_TIME));
            spectacol.setId(spectacoladaugat.getId());
            show(()-> System.out.println(newSpectacolClient.update(spectacol)));

            System.out.println("\nDeleting spectacol with id "+spectacoladaugat.getId());
            show(()-> newSpectacolClient.delete(Long.parseLong(spectacoladaugat.getId())));
        }catch (RestClientException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void show(Runnable task) {
        try {
            task.run();
        } catch (ServiceException e) {

            System.out.println("Service exception"+ e);
        }
    }
}

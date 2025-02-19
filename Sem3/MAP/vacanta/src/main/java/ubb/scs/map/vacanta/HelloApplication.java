package ubb.scs.map.vacanta;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import ubb.scs.map.vacanta.Controller.ControllerClient;
import ubb.scs.map.vacanta.Controller.ControllerPerioada;
import ubb.scs.map.vacanta.Controller.ControllerSearch;
import ubb.scs.map.vacanta.Repository.*;
import ubb.scs.map.vacanta.Service.Service;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class HelloApplication extends Application {

    private static String[] arguments;
    @Override
    public void start(Stage stage) throws IOException {
        String username="postgres";
        String pasword="Eliada31";
        String url="jdbc:postgresql://localhost:5432/vacanta";

        RepoLocation repoLocation=new RepoLocation(url,username,pasword);
        RepoHotel repoHotel=new RepoHotel(url,username,pasword);
        RepoClient repoClient=new RepoClient(url,username,pasword);
        RepoReservation repoReservation=new RepoReservation(url,username,pasword);
        RepoSpecialOffer repoSpecialOffer=new RepoSpecialOffer(url,username,pasword);
        Service service=new Service(repoClient,repoHotel,repoLocation,repoSpecialOffer,repoReservation);


        String[] args = getParameters().getRaw().toArray(new String[0]);

        if (args.length == 0) {
            System.out.println("Nu au fost specificați clienți în linia de comandă.");
           // System.exit(0);
        }

        List<Stage> stages=new ArrayList<>();
        // Creează câte o fereastră pentru fiecare client
        for (String clientIdStr : arguments) {
            try {
                Long clientId = Long.parseLong(clientIdStr);
                System.out.println(clientId);// Parsează ID-ul clientului din linia de comandă
                FXMLLoader fxmlLoader1 = new FXMLLoader(getClass().getResource("/views/clientview.fxml"));
                Scene clientScene = new Scene(fxmlLoader1.load());

                Stage clientStage = new Stage();
                clientStage.setResizable(true);
                clientStage.setTitle("Client: " + clientId);
                clientStage.setScene(clientScene);

                ControllerClient controller = fxmlLoader1.getController();
                controller.setService(service,service.getClient(clientId),stages); // Setează serviciul și ID-ul clientului
                clientStage.setUserData(controller);
                stages.add(clientStage);
                clientStage.show();
            } catch (NumberFormatException e) {
                System.err.println("ID invalid pentru client: " + clientIdStr);
            }
        }

        for(Stage s:stages)
        {
            ControllerClient c= (ControllerClient) s.getUserData();
            c.setStages(stages);
        }

        FXMLLoader fxmlLoader=new FXMLLoader(getClass().getResource("/views/searchview.fxml"));
        Scene loginScene=new Scene(fxmlLoader.load());
        stage.setResizable(true);
        stage.setTitle("Search");
        stage.setScene(loginScene);
        ControllerSearch loginController =fxmlLoader.getController();
        loginController.setService(service,stages);
        stage.show();
    }


    public static void main(String[] args) {
        arguments=args;
        launch();
    }
}
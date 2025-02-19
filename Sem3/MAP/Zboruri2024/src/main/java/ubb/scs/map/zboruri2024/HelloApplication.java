package ubb.scs.map.zboruri2024;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import ubb.scs.map.zboruri2024.Controller.ControllerLogIn;
import ubb.scs.map.zboruri2024.Repository.RepoClient;
import ubb.scs.map.zboruri2024.Repository.RepoFlight;
import ubb.scs.map.zboruri2024.Repository.RepoTicket;
import ubb.scs.map.zboruri2024.Service.Service;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String username="postgres";
        String pasword="Eliada31";
        String url="jdbc:postgresql://localhost:5432/zboruri";

        RepoFlight repoFlight=new RepoFlight(url,username,pasword);
        RepoTicket repoTicket=new RepoTicket(url,username,pasword);
        RepoClient repoClient=new RepoClient(url,username,pasword);
        Service service=new Service(repoClient,repoFlight,repoTicket);

        FXMLLoader loginLoader=new FXMLLoader(getClass().getResource("/views/viewLogin.fxml"));

        Scene loginScene=new Scene(loginLoader.load());
        stage.setResizable(true);
        stage.setTitle("Login");
        stage.setScene(loginScene);
        ControllerLogIn loginController = loginLoader.getController();
        loginController.setService(service);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}
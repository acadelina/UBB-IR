package ubb.scs.map.faptebune;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import ubb.scs.map.faptebune.Controller.ControllerLogin;
import ubb.scs.map.faptebune.Repository.NevoieRepo;
import ubb.scs.map.faptebune.Repository.PersoanaRepo;
import ubb.scs.map.faptebune.Service.ServiceNevoi;
import ubb.scs.map.faptebune.Service.ServicePersoana;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String username="postgres";
        String pasword="Eliada31";
        String url="jdbc:postgresql://localhost:5432/faptebune";

        PersoanaRepo  persoanaRepo = new PersoanaRepo(url,username,pasword);
        NevoieRepo nevoieRepo = new NevoieRepo(url,username,pasword);
        ServicePersoana servicePersoana = new ServicePersoana(persoanaRepo);
        ServiceNevoi serviceNevoi=new ServiceNevoi(nevoieRepo,persoanaRepo);

        FXMLLoader loginLoader=new FXMLLoader(getClass().getResource("/views/loginview.fxml"));

        Scene loginScene=new Scene(loginLoader.load());
        stage.setResizable(true);
        stage.setTitle("Login");
        stage.setScene(loginScene);
        ControllerLogin loginController = loginLoader.getController();
        loginController.setService(servicePersoana,serviceNevoi);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}
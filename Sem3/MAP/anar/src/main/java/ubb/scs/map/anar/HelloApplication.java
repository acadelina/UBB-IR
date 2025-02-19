package ubb.scs.map.anar;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import ubb.scs.map.anar.Controller.ControllerLocalitati;
import ubb.scs.map.anar.Controller.ControllerRauri;
import ubb.scs.map.anar.Repository.RepoLocalitate;
import ubb.scs.map.anar.Repository.RepoRau;
import ubb.scs.map.anar.Service.Service;

import java.io.IOException;
import java.util.Collections;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String username="postgres";
        String pasword="";
        String url="jdbc:postgresql://localhost:5432/anar";

        RepoRau repo=new RepoRau(url,username,pasword);
        RepoLocalitate repoLocalitate=new RepoLocalitate(url,username,pasword);
        Service service=new Service(repo,repoLocalitate);

        FXMLLoader loginLoader=new FXMLLoader(getClass().getResource("/views/firstview.fxml"));

        Scene loginScene=new Scene(loginLoader.load());
        stage.setResizable(true);
        stage.setTitle("Rauri");
        stage.setScene(loginScene);
        ControllerRauri loginController = loginLoader.getController();
        loginController.setService(service);
        stage.show();

        Stage stage1=new Stage();
        FXMLLoader localitati=new FXMLLoader(getClass().getResource("/views/localitatiview.fxml"));

        Scene loScene=new Scene(localitati.load());
        stage1.setResizable(true);
        stage1.setTitle("Localitati");
        stage1.setScene(loScene);
        ControllerLocalitati loController = localitati.getController();
        loController.setService(service);
        stage1.show();
    }

    public static void main(String[] args) {
        launch();
    }
}

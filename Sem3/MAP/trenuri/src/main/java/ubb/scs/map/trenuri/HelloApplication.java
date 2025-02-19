package ubb.scs.map.trenuri;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import ubb.scs.map.trenuri.Controller.ControllerOpen;
import ubb.scs.map.trenuri.Repository.RepoCity;
import ubb.scs.map.trenuri.Repository.RepoStation;
import ubb.scs.map.trenuri.Service.Service;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String username="postgres";
        String pasword="";
        String url="jdbc:postgresql://localhost:5432/trenuri2";

        RepoStation repo=new RepoStation(url,username,pasword);
        RepoCity repoCity=new RepoCity(url,username,pasword);
        Service service=new Service(repoCity,repo);
        FXMLLoader fxmlLoader=new FXMLLoader(getClass().getResource("/views/openview.fxml"));
        Scene loginScene=new Scene(fxmlLoader.load());
        stage.setResizable(true);
        stage.setTitle("Open");
        stage.setScene(loginScene);
        ControllerOpen loginController =fxmlLoader.getController();
        loginController.setService(service);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}

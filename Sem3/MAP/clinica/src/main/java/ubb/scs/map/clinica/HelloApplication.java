package ubb.scs.map.clinica;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import ubb.scs.map.clinica.Controller.ControllerPacienti;
import ubb.scs.map.clinica.Controller.ControllerPaturi;
import ubb.scs.map.clinica.Repository.RepoPacient;
import ubb.scs.map.clinica.Repository.RepoPat;
import ubb.scs.map.clinica.Service.Service;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String username="postgres";
        String pasword="Eliada31";
        String url="jdbc:postgresql://localhost:5432/clinica";

        RepoPat repoPat=new RepoPat(url,username,pasword);
        RepoPacient repoPacient=new RepoPacient(url,username,pasword);
        Service service=new Service(repoPacient,repoPat);


        FXMLLoader fxmlLoader=new FXMLLoader(getClass().getResource("/views/paturiview.fxml"));
        Scene loginScene=new Scene(fxmlLoader.load());
        stage.setResizable(true);
        stage.setTitle("Paturi");
        stage.setScene(loginScene);
        ControllerPaturi loginController =fxmlLoader.getController();
        loginController.setService(service);
        stage.show();

        Stage stage1=new Stage();
        FXMLLoader fxmlLoader1=new FXMLLoader(getClass().getResource("/views/pacientiview.fxml"));
        Scene loginScene1=new Scene(fxmlLoader1.load());
        stage1.setResizable(true);
        stage1.setTitle("Login");
        stage1.setScene(loginScene1);
        ControllerPacienti loginController1 =fxmlLoader1.getController();
        loginController1.setService(service);
        stage1.show();

    }

    public static void main(String[] args) {
        launch();
    }
}
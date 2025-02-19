package ubb.scs.map.administratiebloc;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import ubb.scs.map.administratiebloc.Controller.Controller;
import ubb.scs.map.administratiebloc.Repository.*;
import ubb.scs.map.administratiebloc.Service.Service;

import java.io.IOException;

public class HelloApplication extends Application {


    @Override
    public void start(Stage stage) throws IOException {

        System.out.println(getClass().getResource("/views/myview.fxml"));

        String username="postgres";
        String pasword="";
        String url="jdbc:postgresql://localhost:5432/administratiebloc";
        BlocRepo blocRepo=new BlocRepo(url,username,pasword);
        AdreseRepo adreseRepo=new AdreseRepo(url,username,pasword);
        ApartamenteRepo apartamenteRepo=new ApartamenteRepo(url,username,pasword);
        PersoanaRepo persoanaRepo=new PersoanaRepo(url,username,pasword);
        ChiriasRepo chiriasRepo=new ChiriasRepo(url,username,pasword,persoanaRepo);
        LocatariRepo locatariRepo=new LocatariRepo(url,username,pasword,persoanaRepo);
        AdministratorRepo administratorRepo=new AdministratorRepo(url,username,pasword,blocRepo,persoanaRepo);
        Service service=new Service(adreseRepo,administratorRepo,apartamenteRepo,blocRepo,chiriasRepo,locatariRepo,persoanaRepo);

        FXMLLoader loader=new FXMLLoader(getClass().getResource("/views/myview.fxml"));
        Scene scene=new Scene(loader.load());
        stage.setResizable(true);
        stage.setTitle("Principal");
        stage.setScene(scene);
        Controller controller=loader.getController();
        controller.setService(service);
        stage.show();

    }

    public static void main(String[] args) {
        launch();
    }
}

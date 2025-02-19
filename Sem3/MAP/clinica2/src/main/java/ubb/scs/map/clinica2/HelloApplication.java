package ubb.scs.map.clinica2;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import ubb.scs.map.clinica2.Controller.ControllerMedic;
import ubb.scs.map.clinica2.Controller.ControllerSectii;
import ubb.scs.map.clinica2.Domain.Medic;
import ubb.scs.map.clinica2.Repository.RepoConsultatie;
import ubb.scs.map.clinica2.Repository.RepoMedic;
import ubb.scs.map.clinica2.Repository.RepoSectie;
import ubb.scs.map.clinica2.Service.Service;

import java.io.IOException;
import java.util.List;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String username="postgres";
        String pasword="Eliada31";
        String url="jdbc:postgresql://localhost:5432/clinica2";

        RepoMedic repoMedic=new RepoMedic(url,username,pasword);
        RepoConsultatie repoConsultatie=new RepoConsultatie(url,username,pasword);
        RepoSectie repoSectie=new RepoSectie(url,username,pasword);
        Service service=new Service(repoConsultatie,repoMedic,repoSectie);

        FXMLLoader fxmlLoader=new FXMLLoader(getClass().getResource("/views/sectiiview.fxml"));
        Scene loginScene=new Scene(fxmlLoader.load());
        stage.setResizable(true);
        stage.setTitle("Sectii");
        stage.setScene(loginScene);
        ControllerSectii loginController =fxmlLoader.getController();
        loginController.setService(service);
        stage.show();

        List<Medic> medici=service.getMedici();
        for(Medic medici1:medici){
            Stage stage1=new Stage();
            FXMLLoader fxmlLoader2=new FXMLLoader(getClass().getResource("/views/medicview.fxml"));
            Scene scene2=new Scene(fxmlLoader2.load());
            stage1.setResizable(true);
            stage1.setScene(scene2);
            stage1.setTitle("Medic"+medici1.getId());
            ControllerMedic controllerMedic=fxmlLoader2.getController();
            controllerMedic.setService(service,medici1);
            stage1.show();
        }
    }

    public static void main(String[] args) {
        launch();
    }
}
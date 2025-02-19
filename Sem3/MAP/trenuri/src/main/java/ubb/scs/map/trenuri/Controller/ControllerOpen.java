package ubb.scs.map.trenuri.Controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import ubb.scs.map.trenuri.Service.Service;
import ubb.scs.map.trenuri.observer.Observer;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ControllerOpen  {
    Service service;
    List<Stage> stages=new ArrayList<>();
    List<ControllerClient> clients=new ArrayList<>();
    public void setService(Service service) {
        this.service = service;
    }
    public void handleButton(ActionEvent event) {

        try{
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/views/clientview.fxml"));
            AnchorPane page = (AnchorPane) loader.load();
            Stage stage2=new Stage();
            stage2.setScene(new Scene(page));
            stage2.setResizable(true);
            int nr=stages.size()+1;
            stage2.setTitle("Client Window "+ Integer.toString(nr));
            stage2.initModality(Modality.WINDOW_MODAL);
            ControllerClient controller = loader.getController();

            clients.add(controller);
            stage2.setUserData(controller);
            controller.setService(service,stages);
            controller.init();
            stages.add(stage2);
            stage2.setOnCloseRequest(e->{stages.remove(stage2);
                clients.remove(controller);
                service.changeSelection();
            });
            clients.forEach(c-> c.setStageList(stages));
            stage2.show();
        } catch (
                IOException e) {
            throw new RuntimeException(e);
        }
    }

}

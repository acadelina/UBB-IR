package ubb.scs.map.trenuri.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.stage.Stage;
import ubb.scs.map.trenuri.Service.Service;
import ubb.scs.map.trenuri.observer.Observer;

import java.util.List;

public class ControllerClient implements Observer {
    @Override
    public void update() {
        updateLabel();
    }
    Service service;
    List<Stage> stageList;
    private ObservableList<String> orase= FXCollections.observableArrayList();
    private ObservableList<String> rutes= FXCollections.observableArrayList();
    @FXML
    ComboBox<String> departure;
    @FXML
    ComboBox<String> destination;
    @FXML
    CheckBox check;
    @FXML
    ListView<String> rute;
    @FXML
    Label label;

    public void setService(Service service,List<Stage> stages) {
        this.service = service;
        this.stageList = stages;
        service.addObserver(this);
    }
    public void init()
    {
        orase.clear();
        orase.addAll(service.getCities());
        departure.setItems(orase);
        destination.setItems(orase);
        check.setSelected(false);

    }
    public void updateLabel()
    {
        String c= String.valueOf(countMatchingPages()-1);
        if (countMatchingPages()<=1)
            label.setText("");
        else {
            label.setText(c + " other user(s) are looking at the same route");
        }
    }

    public void onclick(ActionEvent event)
    {
        String depart=departure.getValue();
        String dest=destination.getValue();
        if(depart==null || dest==null)
        {
            MessageAlert.showErrorMessage(null, "select cities");
            return;
        }
        if (check.isSelected())
        {
            rutes.clear();
            rutes.addAll(service.getRotesStrings(service.getDirectRoutes(service.getCity(depart).getId(),service.getCity(dest).getId())));
        }
        else
        {
            rutes.clear();
            rutes.addAll(service.getRotesStrings(service.findRoutes(service.getCity(depart).getId(),service.getCity(dest).getId())));
        }
        rute.setItems(rutes);
        service.changeSelection();
        update();
    }
    public void setStageList(List<Stage> stageList) {
        this.stageList = stageList;
    }

    public long countMatchingPages() {
        String currentDeparture = departure.getValue();
        String currentDestination = destination.getValue();

        if (currentDeparture == null || currentDestination == null) {
            return 0;
        }


        return stageList.stream()
                .map(stage -> (ControllerClient) stage.getUserData())
                .filter(controller -> controller.departure.getValue() != null &&
                        controller.destination.getValue() != null &&
                        controller.departure.getValue().equals(currentDeparture) &&
                        controller.destination.getValue().equals(currentDestination))
                .count();
    }






}

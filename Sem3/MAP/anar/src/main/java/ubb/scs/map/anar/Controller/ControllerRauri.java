package ubb.scs.map.anar.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import ubb.scs.map.anar.Domain.Rau;
import ubb.scs.map.anar.Service.Service;
import ubb.scs.map.anar.observer.Observer;



public class ControllerRauri implements Observer {
    @Override
    public void update() {
        initModel();
    }
    Service sevice;
    public void setService(Service service) {
        sevice = service;
        service.addObserver(this);
        initModel();
    }
    ObservableList<Rau> raus= FXCollections.observableArrayList();

    @FXML
    TableView<Rau> tabelrauri;
    @FXML
    TableColumn<Rau, Integer> id;
    @FXML
    TableColumn<Rau, String> nume;
    @FXML
    TableColumn<Rau, Float> cotamedie;

    @FXML
    TextField cotan;

    public void initialize() {
        id.setCellValueFactory(new PropertyValueFactory<Rau, Integer>("id"));
        nume.setCellValueFactory(new PropertyValueFactory<Rau, String>("nume"));
        cotamedie.setCellValueFactory(new PropertyValueFactory<Rau, Float>("cotamedie"));
        tabelrauri.setItems(raus);
    }
    public void initModel() {

        raus.clear();
        raus.addAll(sevice.getRauri());
        tabelrauri.setItems(raus);
    }
    public void handleButtonAction(ActionEvent event) {
       Rau rau= tabelrauri.getSelectionModel().getSelectedItem();
       Float cotanoua= Float.valueOf(cotan.getText());
       if(rau==null)
       {
           MessageAlert.showErrorMessage(null, "selectati un rau");
           return;
       }
       if(cotanoua==null)
       {
           MessageAlert.showErrorMessage(null, "alegeti o cota noua");
           return;
       }
       sevice.schimbaCota(rau.getId(), cotanoua);
       update();
    }
}

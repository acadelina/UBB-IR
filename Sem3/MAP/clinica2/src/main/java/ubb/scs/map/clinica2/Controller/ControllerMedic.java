package ubb.scs.map.clinica2.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import ubb.scs.map.clinica2.Domain.Consultatie;
import ubb.scs.map.clinica2.Domain.Medic;
import ubb.scs.map.clinica2.Domain.Sectie;
import ubb.scs.map.clinica2.Service.Service;
import ubb.scs.map.clinica2.observer.Observer;

import java.time.LocalDateTime;

public class ControllerMedic implements Observer {
    @Override
    public void update() {
        initModel();
    }
    Service service;
    Medic m;
    public void setService(Service service,Medic m) {
        this.service = service;
        this.m = m;
        service.addObserver(this);
        initModel();
    }
    ObservableList<Consultatie> consultatie= FXCollections.observableArrayList();
    @FXML
    TableView<Consultatie> consultatii;
    @FXML
    TableColumn<Consultatie, Long> id;
    @FXML
    TableColumn<Consultatie, Long> idmedic;
    @FXML
    TableColumn<Consultatie, Long> cnppacient;
    @FXML
    TableColumn<Consultatie, String> numepacient;
    @FXML
    TableColumn<Consultatie, LocalDateTime> data;

    public void initialize() {
        id.setCellValueFactory(new PropertyValueFactory<>("id"));
        idmedic.setCellValueFactory(new PropertyValueFactory<>("idmedic"));
        cnppacient.setCellValueFactory(new PropertyValueFactory<>("cnppacient"));
        numepacient.setCellValueFactory(new PropertyValueFactory<>("numepacient"));
        data.setCellValueFactory(new PropertyValueFactory<>("data"));
        consultatii.setItems(consultatie);
    }

    public void initModel()
    {
        consultatie.clear();
        consultatie.addAll(service.getConsultatii(m));
        consultatii.setItems(consultatie);
    }
}

package ubb.scs.map.anar.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import ubb.scs.map.anar.Domain.Localitate;
import ubb.scs.map.anar.Domain.Rau;
import ubb.scs.map.anar.Service.Service;
import ubb.scs.map.anar.observer.Observer;

import java.awt.event.ActionEvent;

public class ControllerLocalitati implements Observer {
    @Override
    public void update() {
        initModel();
    }
    Service service;
    ObservableList<Localitate> ridicatO= FXCollections.observableArrayList();
    ObservableList<Localitate> mediuO= FXCollections.observableArrayList();
    ObservableList<Localitate> redusO= FXCollections.observableArrayList();

    public void setService(Service service) {
        this.service = service;
        service.addObserver(this);
        initModel();
    }
    @FXML
    TableView<Localitate> ridicat;
    @FXML
    TableView<Localitate> mediu;
    @FXML
    TableView<Localitate> redus;
    @FXML
    TableColumn<Localitate,Integer> id;
    @FXML
    TableColumn<Localitate,String> localitate;
    @FXML
    TableColumn<Localitate,Integer> rau;
    @FXML
    TableColumn<Localitate,Float> cotaMin;
    @FXML
    TableColumn<Localitate,Float> cotaMax;
    @FXML
    TableColumn<Localitate,Integer> id1;
    @FXML
    TableColumn<Localitate,String> localitate1;
    @FXML
    TableColumn<Localitate,Integer> rau1;
    @FXML
    TableColumn<Localitate,Float> cotaMin1;
    @FXML
    TableColumn<Localitate,Float> cotaMax1;

    @FXML
    TableColumn<Localitate,Integer> id11;
    @FXML
    TableColumn<Localitate,String> localitate11;
    @FXML
    TableColumn<Localitate,Integer> rau11;
    @FXML
    TableColumn<Localitate,Float> cotaMin11;
    @FXML
    TableColumn<Localitate,Float> cotaMax11;

    public void initialize()
    {
        id.setCellValueFactory(new PropertyValueFactory<Localitate,Integer>("id"));
        localitate.setCellValueFactory(new PropertyValueFactory<Localitate,String>("nume"));
        rau.setCellValueFactory(new PropertyValueFactory<Localitate,Integer>("rau"));
        cotaMax.setCellValueFactory(new PropertyValueFactory<Localitate,Float>("cotamax"));
        cotaMin.setCellValueFactory(new PropertyValueFactory<Localitate,Float>("cotamin"));

        id1.setCellValueFactory(new PropertyValueFactory<Localitate,Integer>("id"));
        localitate1.setCellValueFactory(new PropertyValueFactory<Localitate,String>("nume"));
        rau1.setCellValueFactory(new PropertyValueFactory<Localitate,Integer>("rau"));
        cotaMax1.setCellValueFactory(new PropertyValueFactory<Localitate,Float>("cotamax"));
        cotaMin1.setCellValueFactory(new PropertyValueFactory<Localitate,Float>("cotamin"));

        id11.setCellValueFactory(new PropertyValueFactory<Localitate,Integer>("id"));
        localitate11.setCellValueFactory(new PropertyValueFactory<Localitate,String>("nume"));
        rau11.setCellValueFactory(new PropertyValueFactory<Localitate,Integer>("rau"));
        cotaMax11.setCellValueFactory(new PropertyValueFactory<Localitate,Float>("cotamax"));
        cotaMin11.setCellValueFactory(new PropertyValueFactory<Localitate,Float>("cotamin"));

        redus.setItems(redusO);
        mediu.setItems(mediuO);
        ridicat.setItems(ridicatO);


        redus.setOnMouseClicked(ev->handleSelect(null));
        mediu.setOnMouseClicked(ev->handleSelect(null));
        ridicat.setOnMouseClicked(ev->handleSelect(null));

    }

    public void initModel()
    {
        redusO.clear();
        mediuO.clear();
        ridicatO.clear();
        redusO.addAll(service.getRiscMin());
        mediuO.addAll(service.getRiscMed());
        ridicatO.addAll(service.getRiscRid());
        redus.setItems(redusO);
        mediu.setItems(mediuO);
        ridicat.setItems(ridicatO);
    }

    public void handleSelect(ActionEvent event)
    {
        Localitate local=redus.getSelectionModel().getSelectedItem();
        redus.getSelectionModel().clearSelection();
        if(local==null)
        {
            local=mediu.getSelectionModel().getSelectedItem();
            mediu.getSelectionModel().clearSelection();
            if(local==null)
            {
                local=ridicat.getSelectionModel().getSelectedItem();
                ridicat.getSelectionModel().clearSelection();
            }
        }
        Rau rau=service.getRau(local.getRau());
        MessageAlert.showMessage(null, Alert.AlertType.INFORMATION,"Rau","Nume: "+rau.getNume()+" Cota: "+rau.getCotamedie().toString());

    }

}

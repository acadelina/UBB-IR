package ubb.scs.map.clinica2.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import ubb.scs.map.clinica2.Domain.Sectie;
import ubb.scs.map.clinica2.Service.Service;
import ubb.scs.map.clinica2.observer.Observer;

import java.io.IOException;

public class ControllerSectii implements Observer {
    @Override
    public void update() {
        initModel();
    }
    Service service;
    public void setService(Service service) {
        this.service = service;
        initModel();
    }
    ObservableList<Sectie> listaSectie= FXCollections.observableArrayList();
    @FXML
    TableView<Sectie> sectii;
    @FXML
    TableColumn<Sectie, Long> id;
    @FXML
    TableColumn<Sectie, String> nume;
    @FXML
    TableColumn<Sectie, Long> sef;
    @FXML
    TableColumn<Sectie, Integer> pret;
    @FXML
    TableColumn<Sectie, Integer> durata;

    public void initialize() {
        id.setCellValueFactory(new PropertyValueFactory<Sectie, Long>("id"));
        nume.setCellValueFactory(new PropertyValueFactory<Sectie, String>("nume"));
        sef.setCellValueFactory(new PropertyValueFactory<Sectie, Long>("idsef"));
        pret.setCellValueFactory(new PropertyValueFactory<Sectie, Integer>("pret"));
        durata.setCellValueFactory(new PropertyValueFactory<Sectie, Integer>("durataMax"));
        sectii.setItems(listaSectie);
        sectii.setOnMouseClicked(event -> handle());
    }
    public void handle()
    {
        Sectie s=sectii.getSelectionModel().getSelectedItem();
        try{

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/views/makeresview.fxml"));

            AnchorPane page = (AnchorPane) loader.load();
            Stage stage2=new Stage();
            stage2.setScene(new Scene(page));
            stage2.setResizable(true);
            stage2.initModality(Modality.WINDOW_MODAL);
            ControllerConsult controller = loader.getController();
            controller.setService(service,s);
            stage2.show();
        } catch (
                IOException e) {
            throw new RuntimeException(e);
        }
    }
    public void initModel()
    {
        listaSectie.clear();
        listaSectie.addAll(service.getSectii());
    }
}

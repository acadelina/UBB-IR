package ubb.scs.map.vacanta.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import ubb.scs.map.vacanta.Domain.Hotel;
import ubb.scs.map.vacanta.Domain.HotelType;
import ubb.scs.map.vacanta.Service.Service;
import ubb.scs.map.vacanta.observer.Observable;
import ubb.scs.map.vacanta.observer.Observer;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ControllerSearch  implements Observer {
    Service service;
    @FXML
    TableView<Hotel> hoteluri;
    @FXML
    TableColumn<Hotel, Double> id;
    @FXML
    TableColumn<Hotel, String> name;
    @FXML
    TableColumn<Hotel, Double> locatione;
    @FXML
    TableColumn<Hotel, Integer> rooms;
    @FXML
    TableColumn<Hotel, Double> price;
    @FXML
    TableColumn<Hotel, HotelType> type;
    @FXML
    ComboBox<String> locations;

    List<Stage> stages;
    ObservableList<Hotel> hoteluriO= FXCollections.observableList(new ArrayList<Hotel>());
    ObservableList<String> locationsO=FXCollections.observableList(new ArrayList<>());
    public void setService(Service service,List<Stage> stages) {
        this.service = service;
        this.stages = stages;
        initModel();
    }
    public void initialize() {
        id.setCellValueFactory(new PropertyValueFactory<Hotel, Double>("id"));
        name.setCellValueFactory(new PropertyValueFactory<Hotel, String>("name"));
        locatione.setCellValueFactory(new PropertyValueFactory<Hotel, Double>("location"));
        rooms.setCellValueFactory(new PropertyValueFactory<Hotel, Integer>("rooms"));
        price.setCellValueFactory(new PropertyValueFactory<Hotel, Double>("price"));
        type.setCellValueFactory(new PropertyValueFactory<Hotel, HotelType>("hotelType"));

        hoteluri.setItems(hoteluriO);
        hoteluri.setOnMouseClicked(event -> handleSelected());
        locations.setItems(locationsO);
        locations.setOnAction(event -> handle());
    }
    public void handle() {
        String loc=locations.getSelectionModel().getSelectedItem();
        if(loc==null)
        {
            MessageAlert.showErrorMessage(null, "select location");
            return;
        }

        hoteluriO.addAll(service.getHotelsByLocation(loc));
        hoteluri.setItems(hoteluriO);
    }

    public void handleSelected()
    {
        Hotel hot=hoteluri.getSelectionModel().getSelectedItem();
        try{

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/views/perioada.fxml"));

            AnchorPane page = (AnchorPane) loader.load();
            Stage stage2=new Stage();
            stage2.setScene(new Scene(page));
            stage2.setResizable(true);
            stage2.setTitle("Special offerts");
            stage2.initModality(Modality.WINDOW_MODAL);



            ControllerPerioada controller = loader.getController();



            controller.setService(service,hot,stages);
            //controller.init();
            stage2.show();
        } catch (
                IOException e) {
            throw new RuntimeException(e);
        }
    }
    public void initModel()
    {
        List<String> locStr=new ArrayList<>();
        service.getLocations().forEach(l->locStr.add(l.getLocation()));
        locationsO.addAll(locStr);
        locations.setItems(locationsO);

    }


    @Override
    public void update() {
        initModel();
    }
}

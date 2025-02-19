package ubb.scs.map.vacanta.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import ubb.scs.map.vacanta.Domain.Client;
import ubb.scs.map.vacanta.Domain.Hotel;
import ubb.scs.map.vacanta.Domain.SpecialOffer;
import ubb.scs.map.vacanta.Service.Service;
import ubb.scs.map.vacanta.observer.Observer;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Objects;

public class ControllerClient implements Observer {
    Service service;
    Hotel hotel;
    Client client;
    List<Stage> stages = new ArrayList<>();
    public void setService(Service service, Client client,List<Stage> stages) {
        this.service = service;
        this.client = client;
        this.stages = stages;
        initModel();
    }
    @FXML
    TableView<SpecialOffer> oferte;
    @FXML
    TableColumn<SpecialOffer, Double> id;
    @FXML
    TableColumn<SpecialOffer, Double> hotelid;
    @FXML
    TableColumn<SpecialOffer, Date> startdate;
    @FXML
    TableColumn<SpecialOffer, Date> enddate;
    @FXML
    TableColumn<SpecialOffer, Integer> percents;
    @FXML
    Label notif;

    ObservableList<SpecialOffer> offers= FXCollections.observableArrayList();
    public void initialize() {
        id.setCellValueFactory(new PropertyValueFactory<>("id"));
        hotelid.setCellValueFactory(new PropertyValueFactory<>("hotelid"));
        startdate.setCellValueFactory(new PropertyValueFactory<>("startDate"));
        enddate.setCellValueFactory(new PropertyValueFactory<>("endDate"));
        percents.setCellValueFactory(new PropertyValueFactory<>("percents"));
        oferte.setItems(offers);
        notif.setText("");

    }
    public void initModel()
    {
        offers.clear();
        offers.addAll(service.offersForClient(client));
        oferte.setItems(offers);
    }

    public void setStages(List<Stage> stages)
    {
        this.stages = stages;
    }

    @Override
    public void update() {

    }
    public void modif(Long clientid)
    {
        if(!Objects.equals(clientid, client.getId()))
        {
            Client c=service.getClient(clientid);
            if(c.getHobbies().equals(client.getHobbies()))
                notif.setText(c.getName()+"are aceleasi hobbies ca si tine si a faut o rezervare");
        }
    }
}

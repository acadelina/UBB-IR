package ubb.scs.map.zboruri2024.Controller;

import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import ubb.scs.map.zboruri2024.Domain.Client;
import ubb.scs.map.zboruri2024.Domain.Flight;
import ubb.scs.map.zboruri2024.Domain.Ticket;
import ubb.scs.map.zboruri2024.Service.Service;
import ubb.scs.map.zboruri2024.observer.Observer;

import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.Collection;

public class ControllerMain implements Observer {

    Service service;
    String client;

    private final ObservableList<Flight> flights= FXCollections.observableArrayList();
    private final ObservableList<Ticket> tickets= FXCollections.observableArrayList();
    private final ObservableList<Ticket> tickets2= FXCollections.observableArrayList();
    @FXML
    private TableView<Flight> zboruri;

    @FXML
    private TableColumn<Flight, Long> id;
    @FXML
    private TableColumn<Flight, String> from;
    @FXML
    private TableColumn<Flight, String> to;
    @FXML
    private TableColumn<Flight, String> depTime;
    @FXML
    private TableColumn<Flight, String> arTime;
    @FXML
    private TableColumn<Flight, Integer> seats;
    @FXML
    private TableColumn<Flight, Integer> avSeats;

    @FXML
    private TableView<Ticket> bileteUser;
    @FXML
    private TableColumn<Ticket, Long> id2;
    @FXML
    private TableColumn<Ticket,String> username;
    @FXML
    private TableColumn<Ticket,Long> flightid;
    @FXML
    private TableColumn<Ticket,String> purchase;

    @FXML
    private TableView<Ticket> bileteData;
    @FXML
    private TableColumn<Ticket, Long> id1;
    @FXML
    private TableColumn<Ticket,String> username1;
    @FXML
    private TableColumn<Ticket,Long> flightid1;
    @FXML
    private TableColumn<Ticket,String> purchase1;

    @FXML
    private ComboBox<String> fromCB;
    @FXML
    private ComboBox<String> toCB;
    @FXML
    private DatePicker dataCB;
    @FXML
    private Button buy;

    @FXML
    public void initialize() {



        id.setCellValueFactory(new PropertyValueFactory<>("id"));
        from.setCellValueFactory(new PropertyValueFactory<>("from"));
        to.setCellValueFactory(new PropertyValueFactory<>("to"));
        depTime.setCellValueFactory(new PropertyValueFactory<>("departure"));
        arTime.setCellValueFactory(new PropertyValueFactory<>("arrival"));
        seats.setCellValueFactory(new PropertyValueFactory<>("seats"));
        avSeats.setCellValueFactory(cellData->{
            Flight f=cellData.getValue();
            int avs= service.getSeats(f.getId());
            return new SimpleObjectProperty<>(avs);
        });

        id2.setCellValueFactory(new PropertyValueFactory<>("id"));
        username.setCellValueFactory(new PropertyValueFactory<>("username"));
        flightid.setCellValueFactory(new PropertyValueFactory<>("idflight"));
        purchase.setCellValueFactory(new PropertyValueFactory<>("purchaseTime"));
        bileteUser.setItems(tickets);
        id1.setCellValueFactory(new PropertyValueFactory<>("id"));
        username1.setCellValueFactory(new PropertyValueFactory<>("username"));
        flightid1.setCellValueFactory(new PropertyValueFactory<>("idflight"));
        purchase1.setCellValueFactory(new PropertyValueFactory<>("purchaseTime"));


        zboruri.setItems(flights);

        bileteData.setItems(tickets2);
    }


    public void setService(Service service,String client) {
        this.service = service;
        this.client = client;
        service.addObserver(this);
        toCB.getItems().clear();
        fromCB.getItems().clear();

        Collection<String> allFr=(Collection<String>)service.fromUnic();
        Collection<String> allT=(Collection<String>)service.toUnic();
        toCB.getItems().addAll(allT);
        fromCB.getItems().addAll(allFr);
        initModel();
    }


    public void initModel() {
        tickets.clear();
        flights.clear();
        tickets2.clear();

        Collection<Ticket> allT=(Collection<Ticket>)service.zboruriDatad();
        tickets.addAll(allT);


        Collection<Ticket> allU=(Collection<Ticket>)service.bileteClient(client);
        tickets2.addAll(allU);
        if(dataCB.getValue()!=null)
        {LocalDateTime datet=dataCB.getValue().atTime(LocalTime.MIDNIGHT);
        Collection<Flight> allF=(Collection<Flight>)service.zboruriData(datet,fromCB.getValue(),toCB.getValue());
        flights.addAll(allF);

        avSeats.setCellValueFactory(cellData->{
            Flight f=cellData.getValue();
            int avs= service.getSeats(f.getId());
            return new SimpleObjectProperty<>(avs);
        });}
    }

    public void handleFilter(ActionEvent event) {
        flights.clear();
        if (dataCB.getValue() == null) {
            MessageAlert.showErrorMessage(null, "Please select a date.");
            return;
        }
        LocalDateTime datet=dataCB.getValue().atTime(LocalTime.MIDNIGHT);
        Collection<Flight> allF=(Collection<Flight>)service.zboruriData(datet,fromCB.getValue(),toCB.getValue());
        flights.addAll(allF);
    }

    public void handleBuy(ActionEvent event) {
        Flight flight=zboruri.getSelectionModel().getSelectedItem();
        if(flight==null)
            MessageAlert.showErrorMessage(null, "No flight selected.");
        else{
            service.achizitieBilet(client, flight.getId());
            update();
        }
    }

    @Override
    public void update() {
        initModel();
    }
}

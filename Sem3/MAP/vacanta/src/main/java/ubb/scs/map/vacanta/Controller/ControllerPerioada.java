package ubb.scs.map.vacanta.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import ubb.scs.map.vacanta.Domain.Hotel;
import ubb.scs.map.vacanta.Domain.HotelType;
import ubb.scs.map.vacanta.Domain.Reservation;
import ubb.scs.map.vacanta.Domain.SpecialOffer;
import ubb.scs.map.vacanta.Service.Service;
import ubb.scs.map.vacanta.observer.Observer;

import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.Date;
import java.util.List;

public class ControllerPerioada implements Observer {
    Service service;
    Hotel hotel;
    List<Stage> stages;
    public void setService(Service service, Hotel hotel,List<Stage> stages) {
        this.service = service;
        this.hotel = hotel;
        this.stages = stages;
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
    DatePicker data1;
    @FXML
    DatePicker data2;
    @FXML
    TextField idclient;
    @FXML
    TextField numeclient;

    ObservableList<SpecialOffer> offers= FXCollections.observableArrayList();
    List<Stage> stageList;
    public void initialize() {
        id.setCellValueFactory(new PropertyValueFactory<>("id"));
        hotelid.setCellValueFactory(new PropertyValueFactory<>("hotelid"));
        startdate.setCellValueFactory(new PropertyValueFactory<>("startDate"));
        enddate.setCellValueFactory(new PropertyValueFactory<>("endDate"));
        percents.setCellValueFactory(new PropertyValueFactory<>("percents"));

        oferte.setItems(offers);
        data1.setOnAction(event -> handle());
        data2.setOnAction(event -> handle());
    }
    private void handle() {
        offers.clear();
        LocalDate d1=data1.getValue();
        LocalDate d2=data2.getValue();
        if (d1==null)
        {
            MessageAlert.showErrorMessage(null, "select dates");
            return;
        }
        offers.addAll(service.getSpecialOffers(java.sql.Date.valueOf(d1),java.sql.Date.valueOf(d2),hotel));
        oferte.setItems(offers);
    }
    public void handleRezerva()
    {
        Long idC= Long.valueOf(idclient.getText());
        String nume= numeclient.getText();

        if (idC==null||nume==null)
        {
            MessageAlert.showErrorMessage(null, "autentifcate first");
            return;
        }
        Date data=java.sql.Date.valueOf(data1.getValue());
        Integer nrn= Math.toIntExact(ChronoUnit.DAYS.between(data2.getValue(), data1.getValue()));
        Reservation res=new Reservation(idC,hotel.getId(),data,nrn);
        service.addRes(res);
        for(Stage s:stages)
        {
            ControllerClient c= (ControllerClient) s.getUserData();
            c.modif(idC);
        }
    }

    @Override
    public void update() {

    }
}

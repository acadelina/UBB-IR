package ubb.scs.map.faptebune.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import ubb.scs.map.faptebune.Domain.Nevoie;
import ubb.scs.map.faptebune.Domain.Oras;
import ubb.scs.map.faptebune.Domain.Persoana;
import ubb.scs.map.faptebune.Service.ServiceNevoi;
import ubb.scs.map.faptebune.observer.Observer;

import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.Collection;

public class ControllerMain implements Observer {
    ServiceNevoi serviceNevoi;
    Persoana persoana;

    private final ObservableList<Nevoie> fapte= FXCollections.observableList(new ArrayList<Nevoie>());
    private final ObservableList<Nevoie> nevoi=FXCollections.observableList(new ArrayList<>());
    @Override
    public void update() {
        initModel();
    }

    @FXML
    private TableView<Nevoie> ajutor;
    @FXML
    private TableColumn<Nevoie, Long> id;
    @FXML
    private TableColumn<Nevoie, String> titlu;
    @FXML
    private TableColumn<Nevoie, String> descriere;
    @FXML
    private TableColumn<Nevoie, LocalDateTime> deadline;
    @FXML
    private TableColumn<Nevoie, Long> omInNevoie;
    @FXML
    private TableColumn<Nevoie, Long> omSalvator;
    @FXML
    private TableColumn<Nevoie, String> status;

    @FXML
    private TableView<Nevoie> faptebune;
    @FXML
    private TableColumn<Nevoie, Long> id1;
    @FXML
    private TableColumn<Nevoie, String> titlu1;
    @FXML
    private TableColumn<Nevoie, String> descriere1;
    @FXML
    private TableColumn<Nevoie, LocalDateTime> deadline1;
    @FXML
    private TableColumn<Nevoie, Long> omInNevoie1;
    @FXML
    private TableColumn<Nevoie, Long> omSalvator1;
    @FXML
    private TableColumn<Nevoie, String> status1;


    @FXML
    private TextField titlu2;
    @FXML
    private TextField desc;
    @FXML
    private DatePicker deadline2;

    public void initialize() {
        id.setCellValueFactory(new PropertyValueFactory<Nevoie, Long>("id"));
        titlu.setCellValueFactory(new PropertyValueFactory<Nevoie, String>("titlu"));
        descriere.setCellValueFactory(new PropertyValueFactory<Nevoie, String>("descriere"));
        deadline.setCellValueFactory(new PropertyValueFactory<Nevoie, LocalDateTime>("deadline"));
        omInNevoie.setCellValueFactory(new PropertyValueFactory<Nevoie, Long>("omInNevoie"));
        omSalvator.setCellValueFactory(new PropertyValueFactory<Nevoie, Long>("omSalvator"));
        status.setCellValueFactory(new PropertyValueFactory<Nevoie, String>("status"));

        id1.setCellValueFactory(new PropertyValueFactory<Nevoie, Long>("id"));
        titlu1.setCellValueFactory(new PropertyValueFactory<Nevoie, String>("titlu"));
        descriere1.setCellValueFactory(new PropertyValueFactory<Nevoie, String>("descriere"));
        deadline1.setCellValueFactory(new PropertyValueFactory<Nevoie, LocalDateTime>("deadline"));
        omInNevoie1.setCellValueFactory(new PropertyValueFactory<Nevoie, Long>("omInNevoie"));
        omSalvator1.setCellValueFactory(new PropertyValueFactory<Nevoie, Long>("omSalvator"));
        status1.setCellValueFactory(new PropertyValueFactory<Nevoie, String>("status"));

        ajutor.setRowFactory(tv -> new TableRow<Nevoie>() {
            @Override
            protected void updateItem(Nevoie item, boolean empty) {
                super.updateItem(item, empty);

                if (item == null || empty) {
                    setStyle("");
                    setDisable(false);
                } else if ("Ajutat!".equalsIgnoreCase(item.getStatus())) {
                    setStyle("-fx-background-color: lightgray;");
                    setDisable(true);
                } else {
                    setStyle("");
                    setDisable(false);
                }
            }
        });

        ajutor.setItems(nevoi);
        faptebune.setItems(fapte);
    }

    public void setService(ServiceNevoi serviceNevoi,Persoana persoana) {
        this.serviceNevoi = serviceNevoi;
        this.persoana = persoana;
        serviceNevoi.addObserver(this);
       initModel();

    }

    public void initModel()
    {
        nevoi.clear();
        fapte.clear();
        Collection<Nevoie> alln=(Collection<Nevoie>) serviceNevoi.nevoiOras(persoana.getOras(), persoana.getId());
        Collection<Nevoie> allF=serviceNevoi.fapteBune(persoana.getId());
        nevoi.addAll(alln);
        fapte.addAll(allF);


    }
    public void ajutorBtn(ActionEvent event) {
        Nevoie n=ajutor.getSelectionModel().getSelectedItem();
        if(n==null)
        {
            MessageAlert.showErrorMessage(null, "select nevoie");
            return;
        }

        serviceNevoi.saleaza(persoana.getId(), n);

        update();
    }

    public void nevoieBtn(ActionEvent event) {
        String tit=titlu2.getText();
        String descr=desc.getText();
        LocalDateTime deadl=deadline2.getValue().atTime(LocalTime.MIDNIGHT);
        if(tit==null||descr==null||deadl==null)
        {
            MessageAlert.showErrorMessage(null, "select nevoie");
            return;
        }

        serviceNevoi.addNevoie(tit,descr,deadl,persoana.getId());
        update();
    }


}

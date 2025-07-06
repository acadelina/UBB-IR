package ubb.scs.mpp.Controller;

import javafx.application.Platform;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import ubb.scs.mpp.Service.*;
import ubb.scs.mpp.Service.observer.Observer;
import ubb.scs.mpp.model.Angajat;
import ubb.scs.mpp.model.Spectacol;

import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import static ubb.scs.mpp.Controller.ControllerUtils.showMessageBox;



public class BileteController implements Observer {
    @Override
    public void updatedSpectacol(Spectacol s) {
        Platform.runLater(()-> {
            loadAllSpectacole();
         loadFilteredSpectacole();
        });
    }

    private IAppService appService;
    private Angajat angajat;

    public void setService(IAppService service, Angajat angajat1) {
        appService = service;
        this.angajat = angajat1;
        init();
       loadAllSpectacole();
    }


    @FXML
    private TableView<Spectacol> tabelS;

    @FXML
    private TableColumn<Spectacol, Integer> idS;
    @FXML
    private TableColumn<Spectacol, String> artistS;
    @FXML
    private TableColumn<Spectacol, String> dataS;
    @FXML
    private TableColumn<Spectacol, String> locatieS;
    @FXML
    private TableColumn<Spectacol, Integer> avseatsS;
    @FXML
    private TableColumn<Spectacol, Integer> soseatsS;


    @FXML
    private TableView<Spectacol> tabelSF;

    @FXML
    private TableColumn<Spectacol, String> oraSF=new TableColumn<>("Ora");
    @FXML
    private TableColumn<Spectacol, String> artistSF;

    @FXML
    private TableColumn<Spectacol, String> locatieSF;
    @FXML
    private TableColumn<Spectacol, Integer> avseatsSF;
    @FXML
    private TableColumn<Spectacol, Integer> soseatsSF;

    @FXML
    private TextField cumparatorField;
    @FXML
    private DatePicker dataField;
    @FXML
    private TextField locuriField;


    @FXML
    public void init() {
        initSpectacoleTable();
        initSpectacoleFTable();

        Platform.runLater(()->{
            loadAllSpectacole();
        });
    }

    private final ObservableList<Spectacol> spectacole = FXCollections.observableArrayList();
    private final ObservableList<Spectacol> filteredSpectacole = FXCollections.observableArrayList();

    private void initSpectacoleTable(){
        tabelS.setRowFactory(tv -> new TableRow<Spectacol>() {
            @Override
            protected void updateItem(Spectacol s, boolean empty) {
                super.updateItem(s, empty);
                if (s == null)
                    setStyle("");
                else {
                    if (s.getAvailable_seats() == 0) {
                        setStyle("-fx-background-color: rgba(213,39,39,0.62);");
                    } else
                        setStyle("");
                }
            }
        });

        idS.setCellValueFactory(new PropertyValueFactory<>("id"));
        artistS.setCellValueFactory(new PropertyValueFactory<>("artist"));
        dataS.setCellValueFactory(new PropertyValueFactory<>("date"));
        locatieS.setCellValueFactory(new PropertyValueFactory<>("location"));
        avseatsS.setCellValueFactory(new PropertyValueFactory<>("available_seats"));
        soseatsS.setCellValueFactory(new PropertyValueFactory<>("sold_seats"));

        tabelS.setItems(spectacole);
    }

    private void initSpectacoleFTable(){
        tabelSF.setRowFactory(tv -> new TableRow<Spectacol>() {
            @Override
            protected void updateItem(Spectacol s, boolean empty) {
                super.updateItem(s, empty);
                if (s == null)
                    setStyle("");
                else {
                    if (s.getAvailable_seats() == 0) {
                        setStyle("-fx-background-color: rgba(213,39,39,0.62);");
                    } else
                        setStyle("");
                }
            }
        });


        artistSF.setCellValueFactory(new PropertyValueFactory<>("artist"));
        oraSF.setCellValueFactory(p->{
            Spectacol s=p.getValue();
            var data=s.getDate().format(DateTimeFormatter.ofPattern("HH:mm"));
            return new SimpleStringProperty(data);

        });
        locatieSF.setCellValueFactory(new PropertyValueFactory<>("location"));
        avseatsSF.setCellValueFactory(new PropertyValueFactory<>("available_seats"));
        soseatsSF.setCellValueFactory(new PropertyValueFactory<>("sold_seats"));

        tabelSF.setItems(filteredSpectacole);
    }

    private void loadAllSpectacole(){
        try{
            spectacole.clear();
            List<Spectacol> spectacols=  new ArrayList<>();
                   for(var a:appService.allSpectacol()) {
                       spectacols.add(a);
                   }
            spectacole.addAll(spectacols);
        } catch (ServiceException e) {
            showMessageBox(e.getMessage());
        }
    }
    private void loadFilteredSpectacole(){
        try{
            filteredSpectacole.clear();
            if(dataField.getValue()!=null){
            Iterable<Spectacol> spectacols= appService.getFilteredSpectacol(Date.from(dataField.getValue().atStartOfDay(ZoneId.systemDefault()).toInstant()));
            List<Spectacol> spec=new ArrayList<>();
            for(var a : spectacols) {
                spec.add(a);
            }
            filteredSpectacole.addAll(spec);}
        } catch (ServiceException e) {
            showMessageBox(e.getMessage());
        }
    }

    public void handleAddBilet()
    {
        try{
            var spec=tabelSF.getSelectionModel().getSelectedItem();


            if(spec==null)
            {
                showMessageBox("Alegeti un spectacol");
                return;
            }
            var nume=cumparatorField.getText();
            cumparatorField.clear();
            Integer locuri;
            try {
                 locuri= Integer.parseInt(locuriField.getText());
            }
            catch (Exception e)
            {
                showMessageBox("Numarul de locuri trebuie sa fie intreg!");
                return;
            }
            locuriField.clear();

            if(nume=="" || locuri==0)
            {
                showMessageBox("Completati datele de cumparare");
                return;
            }

            appService.addBilet(nume, spec,locuri);
            showMessageBox("Biletul a fost adaugat cu succes!");

        } catch (ServiceException e) {
            showMessageBox(e.getMessage());

        }

    }

    public void handleFilter()
    {
        loadFilteredSpectacole();
    }


    public void handleLogOut()
 {

     try {
         appService.logout(angajat);
     } catch (ServiceException e) {
         showMessageBox(e.getMessage());
     }
     Stage stage=(Stage) tabelS.getScene().getWindow();
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Logout");
        alert.setContentText("Logout successful!");
        alert.showAndWait();
        stage.close();

    }

    public void handleStergeSpectacol()
    {
        try{
            var spec=tabelSF.getSelectionModel().getSelectedItem();


            if(spec==null)
            {
                showMessageBox("Alegeti un spectacol");
                return;
            }

            System.out.println(spec.getId());
            appService.deleteSpectacol(spec.getId());
            showMessageBox("Spectacolul a fost sters cu succes!");
            loadAllSpectacole();
            loadFilteredSpectacole();



        } catch (ServiceException e) {
            showMessageBox(e.getMessage());

        }
    }



}

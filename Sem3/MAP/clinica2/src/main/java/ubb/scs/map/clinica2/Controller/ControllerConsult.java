package ubb.scs.map.clinica2.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.DatePicker;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import ubb.scs.map.clinica2.Domain.Consultatie;
import ubb.scs.map.clinica2.Domain.Medic;
import ubb.scs.map.clinica2.Domain.Sectie;
import ubb.scs.map.clinica2.Service.Service;
import ubb.scs.map.clinica2.observer.Observer;

import java.time.LocalDateTime;
import java.time.LocalTime;

public class ControllerConsult implements Observer {
    @Override
    public void update() {
        initModel();
    }

    Service service;
    Sectie sectie;
    public void setService(Service service,Sectie sectie) {
        this.service = service;
        this.sectie = sectie;
        System.out.println(sectie.getNume());
        service.addObserver(this);
        initModel();
    }
    ObservableList<Medic> medics= FXCollections.observableArrayList();
    @FXML
    ListView<Medic> medici;
    @FXML
    DatePicker data;
    @FXML
    TextField nume;
    @FXML
    TextField cnp;
    public void initialize()
    {
        medici.setItems(medics);
    }
    public void initModel()
    {
        medics.clear();
        medics.addAll(service.getMediciSectie(sectie));
        medici.setItems(medics);
    }
    public void handleAdd()
    {
        Medic m=medici.getSelectionModel().getSelectedItem();
        Long cnp1=Long.parseLong(cnp.getText());
        String nume1=nume.getText();
        LocalDateTime date=data.getValue().atTime(LocalTime.MIDNIGHT);
        if(m==null||cnp1==null||nume1==null||date==null)
        {
            MessageAlert.showErrorMessage(null,"Completati toate fieldurile");
            return;
        }

        service.addConsult(new Consultatie(m.getId(),cnp1,nume1,date));
        update();
    }
}

package ubb.scs.map.clinica.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.ListView;
import ubb.scs.map.clinica.Domain.Pacient;
import ubb.scs.map.clinica.Domain.Pat;
import ubb.scs.map.clinica.Domain.TipPat;
import ubb.scs.map.clinica.Service.Service;
import ubb.scs.map.clinica.observer.Observer;

import java.sql.SQLException;

public class ControllerPacienti implements Observer {
    @Override
    public void update() {
        initModel();
    }
    Service service;
    public void setService(Service service) {
        this.service = service;
        service.addObserver(this);
        initModel();
    }
    ObservableList<Pacient> pacients= FXCollections.observableArrayList();
    ObservableList<TipPat> tipPats= FXCollections.observableArrayList();

    @FXML
    ListView<Pacient> pacienti;
    @FXML
    ComboBox<TipPat> tippat;

    public void initialize()
    {
        pacienti.setItems(pacients);
        tippat.setItems(tipPats);
    }
    public void initModel()
    {
        pacients.clear();
        pacients.addAll(service.getPacienti());
        pacienti.setItems(pacients);
        tipPats.clear();
        tipPats.addAll(service.gettipuri());
    }

    public void handleAdd()
    {
        Pacient p=pacienti.getSelectionModel().getSelectedItem();
        if(p==null)
        {
            MessageAlert.showErrorMessage(null, "select pacient");
            return;
        }
        TipPat t=tippat.getSelectionModel().getSelectedItem();

        if(t==null)
        {
            MessageAlert.showErrorMessage(null, "select tipPat");
            return;
        }
        Pat pat=service.verificTipPat(t);
        if(pat==null)
        {
            MessageAlert.showErrorMessage(null, "tipPat not free");
            return;
        }
        pat.setPacient(p.getId());
        try {
            service.updatePat(pat);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        update();
    }

}

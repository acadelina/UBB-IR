package ubb.scs.map.clinica.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import ubb.scs.map.clinica.Domain.Pat;
import ubb.scs.map.clinica.Domain.TipPat;
import ubb.scs.map.clinica.Service.Service;
import ubb.scs.map.clinica.observer.Observer;

public class ControllerPaturi implements Observer {
    Service service;
    @Override
    public void update() {
        initModel();
    }
    public void setService(Service service) {
        this.service = service;
        service.addObserver(this);
        initModel();
    }
    ObservableList<String> paturiTic= FXCollections.observableArrayList();
    ObservableList<String> paturiTim= FXCollections.observableArrayList();
    ObservableList<String> paturiTiip= FXCollections.observableArrayList();

    @FXML
    ListView<String> tabeltic;
    @FXML
    ListView<String> tabeltim;
    @FXML
    ListView<String> tabeltiip;
    @FXML
    Label paturilibere;

    public void initialize() {
        tabeltic.setItems(paturiTic);
        tabeltim.setItems(paturiTim);
        tabeltiip.setItems(paturiTiip);

    }
    public void initModel()
    {
        paturiTic.clear();
        paturiTim.clear();
        paturiTiip.clear();
        if(service.getPaturiOcupate().get(TipPat.TIC)!=null)
            paturiTic.addAll(service.getPaturiOcupate().get(TipPat.TIC));
        if(service.getPaturiOcupate().get(TipPat.TIM)!=null)
            paturiTim.addAll(service.getPaturiOcupate().get(TipPat.TIM));
        if(service.getPaturiOcupate().get(TipPat.TIIP)!=null)
            paturiTiip.addAll(service.getPaturiOcupate().get(TipPat.TIIP));
        paturilibere.setText(service.getPaturiLibere().toString()+" paturi libere");

    }

}

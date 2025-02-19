package ubb.scs.map.administratiebloc.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import ubb.scs.map.administratiebloc.Domain.Bloc;
import ubb.scs.map.administratiebloc.Domain.Chirias;
import ubb.scs.map.administratiebloc.Domain.Locatar;
import ubb.scs.map.administratiebloc.Domain.Persoana;
import ubb.scs.map.administratiebloc.Service.Service;

import java.awt.*;
import java.util.Collection;
import java.util.List;
import java.util.Map;

public class Controller {
    Service service;

    @FXML
    Button btnch;

    @FXML
    Button btnloc;

    @FXML
    ListView<String> lista;

    @FXML
    TableView<BlocMediu> tabel;
    @FXML
    TableColumn<BlocMediu,Long> Bloc;
    @FXML
    TableColumn<BlocMediu,Integer> Mediu;
    @FXML
    private TextField text;


    public void setService(Service service) {
        this.service = service;
        initModel();
    }

    public void initModel()
    {
        Map<Bloc,Double> rez=service.nrMediu();
        ObservableList<BlocMediu> blocuriMediu = FXCollections.observableArrayList();
        rez.forEach((bloc, mediu) -> blocuriMediu.add(new BlocMediu(bloc.getId(), mediu)));

        // Setăm datele în tabel
        tabel.setItems(blocuriMediu);
    }

    public static class BlocMediu {
        private final Long numeBloc;
        private final Double mediuLocatari;

        public BlocMediu(Long numeBloc, Double mediuLocatari) {
            this.numeBloc = numeBloc;
            this.mediuLocatari = mediuLocatari;
        }

        public Long getNumeBloc() {
            return numeBloc;
        }

        public Double getMediuLocatari() {
            return mediuLocatari;
        }
    }

    public void handleLoc(ActionEvent actionEvent) {
        Long numeBloc=Long.parseLong(text.getText());
        ObservableList<String> info=FXCollections.observableArrayList();
        List<Locatar> list=service.getOameniBloc(service.getBloc(numeBloc));
        list.forEach(l->
                {
                    String str=l.getNume()+" "+l.getPrenume();
                    if (service.esteChirias(l))
                        str+=" chirias";
                    else
                        str+=" loctar";

                    info.add(str);
                }
        );
        lista.getItems().clear();
        lista.setItems(info);

    }


    public void handleCh(ActionEvent actionEvent) {
        Long numeBloc=Long.parseLong(text.getText());
        ObservableList<String> info=FXCollections.observableArrayList();
        List<Chirias> list=service.getChiriasi(service.getBloc(numeBloc));
        list.forEach(l->
                {
                    String str=l.getNume()+" "+l.getPrenume()+" "+l.getChirie()+" "+service.getAp(l);

                    info.add(str);
                }
        );
        lista.getItems().clear();
        lista.setItems(info);

    }

}

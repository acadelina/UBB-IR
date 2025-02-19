package ubb.scs.map.faptebune.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import ubb.scs.map.faptebune.Domain.Oras;
import ubb.scs.map.faptebune.Domain.Persoana;
import ubb.scs.map.faptebune.Service.ServiceNevoi;
import ubb.scs.map.faptebune.Service.ServicePersoana;
import ubb.scs.map.faptebune.observer.Observer;

import java.io.IOException;
import java.util.Collection;

public class ControllerLogin implements Observer {
    @Override
    public void update() {
        initModel();
    }
    private final ObservableList<Persoana> persoane= FXCollections.observableArrayList();
    private ServicePersoana servicePersoana;
    private ServiceNevoi serviceNevoi;

    @FXML
    private TextField username;
    @FXML
    private PasswordField parola;
    @FXML
    private ListView<Persoana> listaUseri;

    @FXML
    private Button login;

    @FXML
    private TextField nume;
    @FXML
    private TextField prenume;
    @FXML
    private TextField username1;
    @FXML
    private PasswordField parola1;
    @FXML
    private PasswordField parola2;
    @FXML
    private ComboBox<Oras> oras;
    @FXML
    private TextField strada;
    @FXML
    private TextField nrstrada;
    @FXML
    private TextField telefon;
    @FXML
    private Button inregistrare;


    public void initialize() {
        listaUseri.setItems(persoane);
        listaUseri.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {

                username.setText(newValue.getUsername());
            }
        });
    }

    public void setService(ServicePersoana servicePersoana,ServiceNevoi serviceNevoi) {
        this.servicePersoana = servicePersoana;
        this.serviceNevoi = serviceNevoi;
        servicePersoana.addObserver(this);
        Collection<Oras> or=(Collection<Oras>) servicePersoana.orase();
        oras.getItems().clear();
        oras.getItems().addAll(or);
        initModel();
    }

    public void initModel()
    {
        persoane.clear();
        Collection<Persoana> per=servicePersoana.getPersoane();
        persoane.addAll(per);


    }

    public void handleReg(ActionEvent event) {
        String par1=parola1.getText();
        String par2=parola2.getText();
        if(!par2.equals(par1))
        {
            MessageAlert.showErrorMessage(null, "Parola invalida");
            return;
        }
        String num=nume.getText();
        String prenum=prenume.getText();
        String user=username1.getText();
        String password=parola1.getText();
        Oras ora=oras.getSelectionModel().getSelectedItem();
        String str=strada.getText();
        String nrs=nrstrada.getText();
        String tel=telefon.getText();
        servicePersoana.addPersoana(num,prenum,user,password,ora,str,nrs,tel);
        update();

    }

    public void handleLogin(ActionEvent event) {
        String par = parola.getText();
        String user = username.getText();
        Persoana persoana=servicePersoana.login(user, par);
        if (persoana==null) {
            MessageAlert.showErrorMessage(null, "Parola invalida");
            return;
        }
        try{
            parola.clear();
            username.clear();
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/views/mainview.fxml"));

        AnchorPane page = (AnchorPane) loader.load();
        Stage stage2=new Stage();
        stage2.setScene(new Scene(page));
        stage2.setResizable(true);
        stage2.setTitle("MAin");
        stage2.initModality(Modality.WINDOW_MODAL);

        ControllerMain controller = loader.getController();
        controller.setService(serviceNevoi,persoana);
        stage2.show();
    } catch (
    IOException e) {
        throw new RuntimeException(e);
    }



    }

}

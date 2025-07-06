package ubb.scs.mpp.Controller;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import ubb.scs.mpp.Domain.Angajat;
import ubb.scs.mpp.Service.ServiceException;
import ubb.scs.mpp.Service.AngajatService;
import ubb.scs.mpp.Service.BiletService;
import ubb.scs.mpp.Service.SpectacolService;

import java.io.IOException;

import static ubb.scs.mpp.Controller.ControllerUtils.showMessageBox;

public class LoginController {
    AngajatService angajatService;
    SpectacolService spectacolService;
    BiletService biletService;
    Stage primaryStage;

    @FXML
    private TextField usernameField;
    @FXML
    private TextField passwordField;

    public void setService(AngajatService angajatService,SpectacolService spectacolService,BiletService biletService,Stage primaryStage) {
        this.angajatService = angajatService;
        this.spectacolService = spectacolService;
        this.biletService = biletService;
        this.primaryStage = primaryStage;
    }

    @FXML
    public void handleLogin() {
        String username = usernameField.getText();
        String password = passwordField.getText();
        try{
            Angajat angajat=angajatService.connectAngajat(username,password);

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/Views/bileteView.fxml"));
            Pane page =  loader.load();
            Platform.runLater(() -> {
                Stage dialogStage=new Stage();
            dialogStage.setTitle("Bilete");
            dialogStage.setResizable(true);
            Scene scene = new Scene(page);

            BileteController bileteController=loader.getController();
            bileteController.setService(spectacolService,biletService);

            dialogStage.setScene(scene);
            dialogStage.show();});

        } catch (ServiceException e) {
            showMessageBox(e.getMessage());
        } catch (IOException e) {
            showMessageBox(e.getMessage());
        }
    }

}

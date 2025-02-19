package ubb.scs.map.zboruri2024.Controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import ubb.scs.map.zboruri2024.Service.Service;

import java.io.IOException;

public class ControllerLogIn {
    @FXML
    private TextField username;

    @FXML
    private Button login;

    private Service service;
    Stage dialogStage;
    public void setService(Service service) {
        this.service = service;
    }

    public void loginBtnClicked(ActionEvent event) {
        String username1 = this.username.getText();
        String nume= service.numeDeUsername(username1);
        if(nume==null)
        {
            MessageAlert.showMessage(dialogStage, Alert.AlertType.ERROR,"Login error","User does not exists!");
            return;
        }
        try {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/views/viewmain.fxml"));

            AnchorPane page = (AnchorPane) loader.load();
            Stage stage2=new Stage();
            stage2.setScene(new Scene(page));
            stage2.setResizable(true);
            stage2.setTitle(nume);
            stage2.initModality(Modality.WINDOW_MODAL);

            ControllerMain controller = loader.getController();
            controller.setService(service,username1);
            stage2.show();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

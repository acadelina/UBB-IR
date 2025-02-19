package ubb.scs.map.socialNetwork.controller;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import ubb.scs.map.socialNetwork.domain.User;
import ubb.scs.map.socialNetwork.service.*;

import java.io.IOException;

public class ProfileController {
    private ServiceUser serviceUser;
    private ServiceRequest serviceRequest;
    private ServiceFriendship serviceFriendship;
    private ServiceMessage serviceMessage;
    private Stage stage;
    private Stage oldStage;
    private User user;


    @FXML
    private TextField email;
    @FXML
    private TextField firstName;
    @FXML
    private TextField lastName;

    @FXML
    private Button updateButton;

    @FXML
    private Button logoutButton;

    public void setService(ServiceUser serviceUser,ServiceFriendship serviceFriendship, ServiceRequest serviceRequest,ServiceMessage serviceMessage, Stage stage,Stage oldStage,User user) {
        this.serviceUser = serviceUser;
        this.serviceFriendship = serviceFriendship;
        this.serviceRequest = serviceRequest;
        this.serviceMessage = serviceMessage;
        this.user = user;
        this.stage = stage;
        this.oldStage = oldStage;
        email.setText(user.getEmail());
        firstName.setText(user.getFirstName());
        lastName.setText(user.getLastName());
    }

    public void handleUpdate(javafx.event.ActionEvent event) {
        try {
            String email = this.email.getText();
            String firstName = this.firstName.getText();
            String lastName = this.lastName.getText();
            serviceUser.updateUser(user.getId(), firstName, lastName, email);
            MessageAlert.showMessage(stage, Alert.AlertType.INFORMATION,"Update","User updated successfully");
            stage.close();
        }catch(ServiceException e)
        {
            MessageAlert.showErrorMessage(stage, e.getMessage());
        }

    }

    public void handleLogout(javafx.event.ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/views/login-view.fxml"));

            AnchorPane root = (AnchorPane) loader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Login");
            dialogStage.initModality(Modality.WINDOW_MODAL);

            dialogStage.setResizable(true);
            Scene scene = new Scene(root,600,385);
            dialogStage.setScene(scene);
            dialogStage.sizeToScene();

            LogInController loginController = loader.getController();
            loginController.setService(serviceUser,serviceFriendship,serviceRequest,serviceMessage,stage);
            stage.close();
            oldStage.close();
            dialogStage.show();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

package ubb.scs.mpp.Controller;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import ubb.scs.mpp.Service.*;
import ubb.scs.mpp.model.Angajat;

import java.io.IOException;

import static ubb.scs.mpp.Controller.ControllerUtils.showMessageBox;

public class LoginController {
    IAppService appService;
    Stage primaryStage;

    @FXML
    private TextField usernameField;
    @FXML
    private TextField passwordField;

    public void setService(IAppService appService,Stage primaryStage) {
        this.appService = appService;
        this.primaryStage = primaryStage;
    }

    @FXML
    public void handleLogin() {
        String username = usernameField.getText();
        String password = passwordField.getText();
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/Views/bileteView.fxml"));
            Pane page = loader.load();
            BileteController bileteController = loader.getController();
            if(username=="" || password=="") {
                 showMessageBox("Wrong username or password");
                 return;
            }
            Angajat angtemp=new Angajat(username,password,"");
            Angajat angajat = appService.login(angtemp, bileteController);
            if (angajat == null) {
                showMessageBox("Wrong username or password");
                return;
            }

            bileteController.setService(appService, angajat);

            Platform.runLater(() -> {
                Stage dialogStage = new Stage();
                dialogStage.setTitle("Bilete");
                dialogStage.setResizable(true);
                dialogStage.setScene(new Scene(page));

                dialogStage.setOnCloseRequest(event -> {
                    try {
                        appService.logout(angajat);
                    } catch (ServiceException e) {
                        throw new RuntimeException(e);
                    }
                    Platform.exit();
                });

                dialogStage.show();
            });

        } catch (IOException e) {
            Platform.runLater(() -> showMessageBox("Eroare la încărcarea interfeței: " + e.getMessage()));
        } catch (ServiceException e) {
            Platform.runLater(() -> showMessageBox("Eroare la login: " + e.getMessage()));
        }
//        try{
//            AtomicReference<Angajat> angajat= new AtomicReference<>();
//            FXMLLoader loader = new FXMLLoader();
//            loader.setLocation(getClass().getResource("/Views/bileteView.fxml"));
//            Pane page =  loader.load();
//            Platform.runLater(() -> {
//                Stage dialogStage=new Stage();
//            dialogStage.setTitle("Bilete");
//            dialogStage.setResizable(true);
//            Scene scene = new Scene(page);
//
//            BileteController bileteController=loader.getController();
//
//                try {
//                    angajat.set(appService.login(username, password, bileteController));
//                } catch (ServiceException e) {
//                    throw new RuntimeException();
//                }
//            if(angajat.get()==null){
//                showMessageBox("Wrong username or password");
//                Platform.exit();
//            }
//            else{
//                Angajat thisangajat=angajat.get();
//
//            }
//            bileteController.setService(appService,angajat.get());
//
//                dialogStage.setScene(scene);
//            dialogStage.show();});
//
//        } catch ( RuntimeException | IOException e) {
//            showMessageBox(e.getMessage());
//        }
    }

}

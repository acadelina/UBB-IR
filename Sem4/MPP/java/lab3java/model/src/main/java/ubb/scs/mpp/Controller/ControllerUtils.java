package ubb.scs.mpp.Controller;

import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;

public class ControllerUtils {
    public static void showMessageBox(String message) {
        var alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Info");
        alert.setHeaderText("Message:");
        alert.setContentText(message);
        alert.showAndWait().ifPresent(rs -> {
            if (rs == ButtonType.OK) {
                System.out.println("Pressed OK.");
            }
        });
    }
}

module ubb.scs.map.zboruri2024 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens ubb.scs.map.zboruri2024 to javafx.fxml;
    exports ubb.scs.map.zboruri2024;
    opens ubb.scs.map.zboruri2024.Controller to javafx.fxml;
    exports ubb.scs.map.zboruri2024.Controller;
    opens ubb.scs.map.zboruri2024.Domain to javafx.fxml;
    exports ubb.scs.map.zboruri2024.Domain;

}
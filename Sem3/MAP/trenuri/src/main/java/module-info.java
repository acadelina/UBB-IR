module ubb.scs.map.trenuri {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens ubb.scs.map.trenuri to javafx.fxml;
    exports ubb.scs.map.trenuri;
    opens ubb.scs.map.trenuri.Controller to javafx.fxml;
    exports ubb.scs.map.trenuri.Controller;
    opens ubb.scs.map.trenuri.Domain to javafx.fxml;
    exports ubb.scs.map.trenuri.Domain;
}
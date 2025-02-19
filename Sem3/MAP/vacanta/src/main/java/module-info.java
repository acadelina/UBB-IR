module ubb.scs.map.vacanta {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens ubb.scs.map.vacanta to javafx.fxml;
    exports ubb.scs.map.vacanta;
    opens ubb.scs.map.vacanta.Controller to javafx.fxml;
    exports ubb.scs.map.vacanta.Controller;
    opens ubb.scs.map.vacanta.Domain to javafx.fxml;
    exports ubb.scs.map.vacanta.Domain;
}
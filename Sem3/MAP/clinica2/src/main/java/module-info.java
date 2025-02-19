module ubb.scs.map.clinica2 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens ubb.scs.map.clinica2 to javafx.fxml;
    exports ubb.scs.map.clinica2;
    opens ubb.scs.map.clinica2.Domain to javafx.fxml;
    exports ubb.scs.map.clinica2.Domain;
    opens ubb.scs.map.clinica2.Controller to javafx.fxml;
    exports ubb.scs.map.clinica2.Controller;
}
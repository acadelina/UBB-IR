module ubb.scs.map.clinica {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens ubb.scs.map.clinica to javafx.fxml;
    exports ubb.scs.map.clinica;
    opens ubb.scs.map.clinica.Domain to javafx.fxml;
    exports ubb.scs.map.clinica.Domain;
    opens ubb.scs.map.clinica.Controller to javafx.fxml;
    exports ubb.scs.map.clinica.Controller;
}
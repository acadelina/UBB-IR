module ubb.scs.map.examen {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens ubb.scs.map.examen to javafx.fxml;
    exports ubb.scs.map.examen;
    opens ubb.scs.map.examen.Domain to javafx.fxml;
    exports ubb.scs.map.examen.Domain;

}
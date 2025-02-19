module ubb.scs.map.comenzi {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens ubb.scs.map.comenzi to javafx.fxml;
    exports ubb.scs.map.comenzi;
    opens ubb.scs.map.comenzi.Domain to javafx.fxml;
    exports ubb.scs.map.comenzi.Domain;
    opens ubb.scs.map.comenzi.Controller to javafx.fxml;
    exports ubb.scs.map.comenzi.Controller;
}
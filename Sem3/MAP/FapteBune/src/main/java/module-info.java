module ubb.scs.map.faptebune {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens ubb.scs.map.faptebune to javafx.fxml;
    exports ubb.scs.map.faptebune;
    opens ubb.scs.map.faptebune.Domain to javafx.fxml;
    exports ubb.scs.map.faptebune.Domain;
    opens ubb.scs.map.faptebune.Controller to javafx.fxml;
    exports ubb.scs.map.faptebune.Controller;
}
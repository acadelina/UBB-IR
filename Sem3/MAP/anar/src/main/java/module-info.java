module ubb.scs.map.anar {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;
    requires java.desktop;


    opens ubb.scs.map.anar to javafx.fxml;
    exports ubb.scs.map.anar;
    opens ubb.scs.map.anar.Domain to javafx.fxml;
    exports ubb.scs.map.anar.Domain;
    opens ubb.scs.map.anar.Controller to javafx.fxml;
    exports ubb.scs.map.anar.Controller;
}
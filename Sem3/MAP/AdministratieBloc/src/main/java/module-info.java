module ubb.scs.map.administratiebloc {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;
    requires java.desktop;


    opens ubb.scs.map.administratiebloc to javafx.fxml;
    exports ubb.scs.map.administratiebloc;

    exports ubb.scs.map.administratiebloc.Controller to javafx.fxml;
    opens ubb.scs.map.administratiebloc.Controller to javafx.fxml;
}
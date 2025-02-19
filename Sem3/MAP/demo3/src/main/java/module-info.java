module ubb.scs.map.demo3 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;

    opens ubb.scs.map.demo3.controller to javafx.fxml;
    exports ubb.scs.map.demo3.controller;

    opens ubb.scs.map.demo3 to javafx.fxml;
    exports ubb.scs.map.demo3;
}
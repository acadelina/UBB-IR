module ubb.scs.map.demo {
    requires javafx.controls;
    requires javafx.fxml;


    opens ubb.scs.map.demo to javafx.fxml;
    exports ubb.scs.map.demo;
}
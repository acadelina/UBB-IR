module ubb.scs.map.demo2 {
    requires javafx.controls;
    requires javafx.fxml;


    opens ubb.scs.map.demo2 to javafx.fxml;
    exports ubb.scs.map.demo2;
}
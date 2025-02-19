module ubb.scs.map.socialNetwork {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;
    requires jdk.httpserver;
    requires java.desktop;


    opens ubb.scs.map.socialNetwork to javafx.fxml;
    exports ubb.scs.map.socialNetwork;
    exports ubb.scs.map.socialNetwork.controller to javafx.fxml;

    opens ubb.scs.map.socialNetwork.controller to javafx.fxml;
    opens ubb.scs.map.socialNetwork.views to javafx.fxml;
    opens ubb.scs.map.socialNetwork.domain to javafx.base;
}
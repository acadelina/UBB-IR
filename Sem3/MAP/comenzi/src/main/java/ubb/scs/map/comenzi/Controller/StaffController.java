package ubb.scs.map.comenzi.Controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import ubb.scs.map.comenzi.Domain.Order;
import ubb.scs.map.comenzi.Domain.OrderStatus;
import ubb.scs.map.comenzi.Service.Service;
import ubb.scs.map.comenzi.observer.Observer;

import java.text.CollationElementIterator;
import java.time.LocalDateTime;
import java.util.Collection;
import java.util.List;

public class StaffController implements Observer {

    Service service;
    public void setService(Service service)
    {
        this.service = service;
        service.addObserver(this);
        initModel();
    }
    @FXML
    TableView<Order> placedorders;
    @FXML
    TableColumn<Order, Integer> id;
    @FXML
    TableColumn<Order, Integer> table;
    @FXML
    TableColumn<Order, List<Integer>> menuitems;
    @FXML
    TableColumn<Order, LocalDateTime> date;
    @FXML
    TableColumn<Order, OrderStatus> status;

    private ObservableList<Order> orders= FXCollections.observableArrayList();

    public void initialize()
    {
        id.setCellValueFactory(new PropertyValueFactory<Order, Integer>("id"));
        table.setCellValueFactory(new PropertyValueFactory<Order, Integer>("idTable"));
        menuitems.setCellValueFactory(new PropertyValueFactory<Order, List<Integer>>("orderItems"));
        date.setCellValueFactory(new PropertyValueFactory<Order, LocalDateTime>("date"));
        status.setCellValueFactory(new PropertyValueFactory<Order, OrderStatus>("status"));
        placedorders.setItems(orders);

    }
    public void initModel()
    {
        orders.clear();
        Collection<Order> orders1 = this.service.getOrders();
        orders.addAll(orders1);
    }
    @Override
    public void update() {
        initModel();
    }
}

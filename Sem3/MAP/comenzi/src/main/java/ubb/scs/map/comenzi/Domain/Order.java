package ubb.scs.map.comenzi.Domain;

import java.time.LocalDateTime;
import java.util.List;

public class Order extends Entity<Integer> {
    Integer idTable;
    List<Integer> orderItems;
    LocalDateTime date;
    OrderStatus status;

    public Order(Integer idTable, List<Integer> orderItems, LocalDateTime date, OrderStatus status) {
        this.idTable = idTable;
        this.orderItems = orderItems;
        this.date = date;
        this.status = status;
    }

    public Integer getIdTable() {
        return idTable;
    }

    public void setIdTable(Integer idTable) {
        this.idTable = idTable;
    }

    public List<Integer> getOrderItems() {
        return orderItems;
    }

    public void setOrderItems(List<Integer> orderItems) {
        this.orderItems = orderItems;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public OrderStatus getStatus() {
        return status;
    }

    public void setStatus(OrderStatus status) {
        this.status = status;
    }
}

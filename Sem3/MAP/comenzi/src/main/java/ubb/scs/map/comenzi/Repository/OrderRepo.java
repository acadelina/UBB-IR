package ubb.scs.map.comenzi.Repository;

import ubb.scs.map.comenzi.Domain.MenuItem;
import ubb.scs.map.comenzi.Domain.Order;
import ubb.scs.map.comenzi.Domain.OrderStatus;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class OrderRepo extends AbstractBDRepo<Integer, Order> {
    public OrderRepo(String url, String username, String password) {
        super(url, username, password);
    }

    private List<Integer> extractMenuItems(Integer idorder) throws SQLException {
        List<Integer> entities = new ArrayList<>();
        String query = "SELECT * FROM orderitems WHERE orderid = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setInt(1, idorder);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    Integer iditem = resultSet.getInt("itemid");
                    entities.add(iditem);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return entities;
    }

    @Override
    protected Order extractEntity(ResultSet resultSet) throws SQLException {
        Integer id=resultSet.getInt("id");
        Integer table=resultSet.getInt("tableid");
        LocalDateTime date=resultSet.getTimestamp("date").toLocalDateTime();
        OrderStatus status=OrderStatus.valueOf(resultSet.getString("status"));
        List<Integer> list=extractMenuItems(id);
        Order order=new Order(table,list,date,status);
        order.setId(id);
        return order;
    }

    @Override
    protected String getTableName() {
        return "orders";
    }

    public void updateOrder(Order order) {
        String updateOrderQuery = "UPDATE orders SET tableid = ?, date = ?, status = ? WHERE id = ?";
        String deleteOrderItemsQuery = "DELETE FROM orderitems WHERE orderid = ?";
        String insertOrderItemsQuery = "INSERT INTO orderitems (orderid, itemid) VALUES (?, ?)";

        try (Connection connection = DriverManager.getConnection(url, username, password)) {

            connection.setAutoCommit(false);


            try (PreparedStatement updateOrderStmt = connection.prepareStatement(updateOrderQuery)) {
                updateOrderStmt.setInt(1, order.getIdTable());
                updateOrderStmt.setTimestamp(2, Timestamp.valueOf(order.getDate()));
                updateOrderStmt.setString(3, order.getStatus().toString());
                updateOrderStmt.setInt(4, order.getId());
                updateOrderStmt.executeUpdate();
            }


            try (PreparedStatement deleteItemsStmt = connection.prepareStatement(deleteOrderItemsQuery)) {
                deleteItemsStmt.setInt(1, order.getId());
                deleteItemsStmt.executeUpdate();
            }


            try (PreparedStatement insertItemsStmt = connection.prepareStatement(insertOrderItemsQuery)) {
                for (Integer itemId : order.getOrderItems()) {
                    insertItemsStmt.setInt(1, order.getId());
                    insertItemsStmt.setInt(2, itemId);
                    insertItemsStmt.addBatch();
                }
                insertItemsStmt.executeBatch();
            }


            connection.commit();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException("Failed to update order: " + e.getMessage(), e);
        }
    }

    public void addOrder(Order order) {
        String insertOrderQuery = "INSERT INTO orders (tableid, date, status) VALUES (?, ?, ?)";
        String insertOrderItemsQuery = "INSERT INTO orderitems (orderid, itemid) VALUES (?, ?)";

        try (Connection connection = DriverManager.getConnection(url, username, password)) {

            connection.setAutoCommit(false);


            int generatedId;
            try (PreparedStatement insertOrderStmt = connection.prepareStatement(insertOrderQuery, Statement.RETURN_GENERATED_KEYS)) {
                insertOrderStmt.setInt(1, order.getIdTable());
                insertOrderStmt.setTimestamp(2, Timestamp.valueOf(order.getDate()));
                insertOrderStmt.setString(3, order.getStatus().toString());
                insertOrderStmt.executeUpdate();


                try (ResultSet generatedKeys = insertOrderStmt.getGeneratedKeys()) {
                    if (generatedKeys.next()) {
                        generatedId = generatedKeys.getInt(1);
                        order.setId(generatedId); // Set the generated ID to the order object
                    } else {
                        throw new SQLException("Failed to retrieve the generated ID for the order.");
                    }
                }
            }


            try (PreparedStatement insertItemsStmt = connection.prepareStatement(insertOrderItemsQuery)) {
                for (Integer itemId : order.getOrderItems()) {
                    insertItemsStmt.setInt(1, generatedId);
                    insertItemsStmt.setInt(2, itemId);
                    insertItemsStmt.addBatch();
                }
                insertItemsStmt.executeBatch();
            }


            connection.commit();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException("Failed to add order: " + e.getMessage(), e);
        }
    }


}

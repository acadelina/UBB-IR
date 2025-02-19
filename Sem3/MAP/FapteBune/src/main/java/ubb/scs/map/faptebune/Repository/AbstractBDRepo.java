package ubb.scs.map.faptebune.Repository;

import ubb.scs.map.faptebune.Domain.*;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public abstract class AbstractBDRepo<ID, E extends Entity<ID>> implements Repository<ID, E> {
    protected final String url;
    protected final String username;
    protected final String password;

    public AbstractBDRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    protected abstract E extractEntity(ResultSet resultSet) throws SQLException;

    @Override
    public Optional<E> findOne(ID id) {
        String query = "SELECT * FROM " + getTableName() + " WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setObject(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Optional.of(extractEntity(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<E> findAll() {
        List<E> entities = new ArrayList<>();
        String query = "SELECT * FROM " + getTableName();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             Statement statement = connection.createStatement();
             ResultSet resultSet = statement.executeQuery(query)) {
            while (resultSet.next()) {
                entities.add(extractEntity(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return entities;
    }

    protected abstract String getTableName();
}

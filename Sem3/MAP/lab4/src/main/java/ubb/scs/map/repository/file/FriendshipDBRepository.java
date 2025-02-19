package ubb.scs.map.repository.file;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.validators.FriendshipValidator;
import ubb.scs.map.repository.Repository;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class FriendshipDBRepository implements Repository<Tuple<Long,Long>, Friendship> {
    private FriendshipValidator validator;
    private String url;
    private String username;
    private String password;

    public FriendshipDBRepository(FriendshipValidator validator, String  url, String username, String password) {
        this.validator=validator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Friendship> findOne(Tuple<Long, Long> tuple) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * FROM friendships WHERE id1 = ? AND id2 = ?;")) {
            statement.setLong(1, tuple.getE1());
            statement.setLong(2, tuple.getE2());
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    Long id1 = resultSet.getLong("id1");
                    Long id2 = resultSet.getLong("id2");


                    Friendship friendship = new Friendship();
                    friendship.setId(new Tuple<>(id1, id2));


                    return Optional.of(friendship);
                }
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();


    }



    @Override
    public Iterable<Friendship> findAll() {
        Set<Friendship> friendships = new HashSet<>();

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * FROM friendships ;");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id1 = resultSet.getLong("id1");
                Long id2 = resultSet.getLong("id2");


                Friendship friendship = new Friendship();
                friendship.setId(new Tuple<>(id1, id2));


                friendships.add(friendship);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return friendships;
    }

    @Override
    public Optional<Friendship> delete(Tuple<Long,Long> tuple) {
        Optional<Friendship> friendship = findOne(tuple);

        if (friendship.isPresent()) {
            try (Connection connection = DriverManager.getConnection(url, username, password);
                 PreparedStatement statement = connection.prepareStatement("DELETE FROM friendships WHERE id1 = ? AND id2 = ?;")) {

                statement.setLong(1, tuple.getE1());
                statement.setLong(2, tuple.getE2());

                statement.executeUpdate();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }

            return friendship;
        } else {
            return Optional.empty();
        }
    }

    @Override
    public Optional<Friendship> save(Friendship entity) {
        if (entity == null) {
            throw new IllegalArgumentException("entity must not be null");
        }

        validator.validate(entity);

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("INSERT INTO friendships (id1, id2) VALUES (?, ?)")) {

            statement.setLong(1, entity.getId().getE1());
            statement.setLong(2, entity.getId().getE2());


            statement.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.of(entity);

    }


    @Override
    public Optional<Friendship> update(Friendship entity) {
        //TO DO: for now we don't use update
        return Optional.empty();
    }
}

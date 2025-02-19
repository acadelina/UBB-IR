package ubb.scs.map.socialNetwork.repository.file;

import ubb.scs.map.socialNetwork.domain.Post;
import ubb.scs.map.socialNetwork.repository.Repository;

import java.sql.*;
import java.util.*;

public class PostDBRepository implements Repository <Long, Post> {

    private final String url;
    private final String username;
    private final String password;

    public PostDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Post> findOne(Long aLong) {
        try(Connection connection= DriverManager.getConnection(url,username,password);
            PreparedStatement preparedStatement=connection.prepareStatement("SELECT * FROM posts WHERE id = ?"))
        {
            preparedStatement.setLong(1,aLong);
            try(ResultSet resultSet=preparedStatement.executeQuery()){
                Long id =resultSet.getLong("id");
                byte[] image = resultSet.getBytes("image");
                String description=resultSet.getString("description");
                Timestamp timestamp= resultSet.getTimestamp("date");
                Long reply=resultSet.getLong("reply");
                String author=resultSet.getString("author");
                List<String> likes= Arrays.stream(resultSet.getString("likes").split(";")).toList();
                Post post=new Post(image,description,author,likes,timestamp.toLocalDateTime());
                post.setId(id);

                return Optional.of(post);

            }
        }catch(SQLException e){
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Post> findAll() {
        Set<Post> posts = new HashSet<>();

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * FROM posts ;");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id =resultSet.getLong("id");
                byte[] image = resultSet.getBytes("image");
                String description=resultSet.getString("description");
                Timestamp timestamp= resultSet.getTimestamp("date");
                Long reply=resultSet.getLong("reply");
                String author=resultSet.getString("author");
                List<String> likes= Arrays.stream(resultSet.getString("likes").split(";")).toList();
                Post post=new Post(image,description,author,likes,timestamp.toLocalDateTime());
                post.setId(id);

                posts.add(post);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return posts;
    }

    @Override
    public Optional<Post> save(Post entity) {
        if (entity == null) {
            throw new IllegalArgumentException("entity must not be null");
        }



        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("INSERT INTO posts (id, image, description, author, date, likes) VALUES (?, ?,?,?,?,?)")) {

            statement.setLong(1, entity.getId());
            statement.setBytes(2, entity.getImage());
            statement.setString(3, entity.getDescription());
            statement.setString(4, entity.getAuthor());
            statement.setTimestamp(5, Timestamp.valueOf( entity.getDate()));
            statement.setString(6, entity.getLikes().toString());


            statement.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.of(entity);
    }

    @Override
    public Optional<Post> delete(Long aLong) {
        Optional<Post> post = findOne(aLong);

        if (post.isPresent()) {
            try (Connection connection = DriverManager.getConnection(url, username, password);
                 PreparedStatement statement = connection.prepareStatement("DELETE FROM posts WHERE id1 = ? ;")) {

                statement.setLong(1, aLong);


                statement.executeUpdate();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }

            return post;
        } else {
            return Optional.empty();
        }
    }

    @Override
    public Optional<Post> update(Post entity) {
        return Optional.empty();
    }
}

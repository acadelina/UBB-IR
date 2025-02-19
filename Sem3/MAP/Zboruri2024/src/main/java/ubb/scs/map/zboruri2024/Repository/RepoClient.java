package ubb.scs.map.zboruri2024.Repository;

import ubb.scs.map.zboruri2024.Domain.Client;

import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoClient extends AbstractBDRepo<Long, Client>{
    public RepoClient(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Client extractEntity(ResultSet resultSet) throws SQLException {
        Long id=resultSet.getLong("id");
        String name=resultSet.getString("name");
        String username=resultSet.getString("username");
        Client client=new Client(name,username);
        client.setId(id);
        return client;
    }

    @Override
    protected String getTableName() {
        return "clienti";
    }
}

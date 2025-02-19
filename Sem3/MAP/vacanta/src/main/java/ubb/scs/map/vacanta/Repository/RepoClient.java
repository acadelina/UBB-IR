package ubb.scs.map.vacanta.Repository;

import ubb.scs.map.vacanta.Domain.Client;
import ubb.scs.map.vacanta.Domain.Hobbies;

import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoClient extends AbstractBDRepo<Long, Client> {
    public RepoClient(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Client extractEntity(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String name = resultSet.getString("name");
        Integer fidelitygrade=resultSet.getInt("fidelitygrade");
        Integer vasta=resultSet.getInt("vasta");
        Hobbies hobbies=Hobbies.valueOf(resultSet.getString("hobbies"));
        Client client=new Client(name,fidelitygrade,vasta,hobbies);
        client.setId(id);
        return client;
    }

    @Override
    protected String getTableName() {
        return "client";
    }
}

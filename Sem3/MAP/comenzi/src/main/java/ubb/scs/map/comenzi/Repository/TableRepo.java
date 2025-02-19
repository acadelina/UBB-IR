package ubb.scs.map.comenzi.Repository;

import ubb.scs.map.comenzi.Domain.Table;

import java.sql.ResultSet;
import java.sql.SQLException;

public class TableRepo extends AbstractBDRepo<Integer, Table> {
    public TableRepo(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Table extractEntity(ResultSet resultSet) throws SQLException {
        Integer id = resultSet.getInt("id");
        Table table = new Table();
        table.setId(id);
        return table;
    }

    @Override
    protected String getTableName() {
        return "tablee";
    }
}

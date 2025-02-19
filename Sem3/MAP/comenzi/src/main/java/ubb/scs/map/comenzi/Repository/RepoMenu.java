package ubb.scs.map.comenzi.Repository;

import ubb.scs.map.comenzi.Domain.MenuItem;

import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoMenu extends AbstractBDRepo<Integer, MenuItem> {
    public RepoMenu(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected MenuItem extractEntity(ResultSet resultSet) throws SQLException {
        Integer id = resultSet.getInt("id");
        String category = resultSet.getString("category");
        String item = resultSet.getString("item");
        Float price = resultSet.getFloat("price");
        String currency = resultSet.getString("currency");
        MenuItem menuItem=new MenuItem(currency,price,item,category);
        menuItem.setId(id);
        return menuItem;
    }

    @Override
    protected String getTableName() {
        return "menuitem";
    }
}

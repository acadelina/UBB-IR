package ubb.scs.mpp.Repository;


import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ubb.scs.mpp.Domain.Entity;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;
import java.util.stream.StreamSupport;

public abstract class DbRepoUtils<ID,E extends Entity<ID>> {
    private final JdbcUtils dbUtils;
    private static final Logger logger= LogManager.getLogger(DbRepoUtils.class);

    protected DbRepoUtils(Properties props) {
        dbUtils = new JdbcUtils(props);
    }

    protected abstract E decodeResult(ResultSet resultSet) throws SQLException, RepoException;

    protected Iterable<E> select(String sql,Object... args) throws RepoException {
        logger.traceEntry(sql);
        logger.trace("Query: {}",sql);
        Connection connection = dbUtils.getConnection();
        List<E> items=new ArrayList<>();
        try(PreparedStatement preparedStatement=connection.prepareStatement(sql)){
            for(int i=0;i<args.length;i++)
                preparedStatement.setObject(i+1,args[i]);
            try(ResultSet resultSet=preparedStatement.executeQuery()){
                while(resultSet.next())
                    items.add(decodeResult(resultSet));
            }
        }catch(SQLException e){
            logger.error(e);
            System.err.println("Error db "+e.getMessage());
            throw new RepoException(e.getMessage());
        }
        logger.trace("Select query returned {} items",items.size());
        logger.traceExit();
        return items;

    }

    protected void executeNonQuery(String sql,Object... args) throws RepoException {
        logger.traceEntry("executing query");
        Connection connection = dbUtils.getConnection();
        try(PreparedStatement preparedStatement=connection.prepareStatement(sql)){
            for(int i=0;i<args.length;i++){
                preparedStatement.setObject(i+1,args[i]);
            }
            int result=preparedStatement.executeUpdate();
            logger.trace("Executed query on {} instances",result);
        }catch(SQLException e){
            logger.error(e);
            System.err.println("Error db "+e.getMessage());
            throw new RepoException(e.getMessage());
        }
        logger.traceExit();
    }

    protected E selectFirst(String sql,Object... args) throws RepoException {
        return StreamSupport.stream(
                select(sql,args).spliterator(),false).findFirst().orElse(null);

    }
}

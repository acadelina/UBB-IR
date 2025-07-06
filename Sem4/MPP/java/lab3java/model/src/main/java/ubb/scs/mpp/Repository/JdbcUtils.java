package ubb.scs.mpp.Repository;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;


public class JdbcUtils {
    private final Properties properties;

    private static final Logger logger= LogManager.getLogger(JdbcUtils.class);
    public JdbcUtils(Properties properties) {
        this.properties= properties;
    }

    private Connection instance=null;

    private Connection getNewConnection() {
        logger.traceEntry();

        String url=properties.getProperty("jdbc.url");
        logger.info("Connecting to "+url);
        Connection connection=null;
        try{
                connection=DriverManager.getConnection(url);
        }catch (SQLException e){
            logger.error(e);
            System.out.println("Error connecting to "+url);
        }

        return connection;
    }

    public Connection getConnection() {
        logger.traceEntry();
        try{
            if(instance==null||instance.isClosed())
                instance=getNewConnection();
        }catch (SQLException e){
            logger.error(e);
            System.out.println("Error connecting "+e);
        }
        logger.traceExit(instance);
        return instance;
    }
}

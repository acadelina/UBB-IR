package ubb.scs.map.demo3.services.config;

import java.util.Properties;

public class ApplicationContext {
        private static final Properties PROPERTIES=Config.getProperties();

    public static Properties getPROPERTIES() {
        return PROPERTIES;
    }
}

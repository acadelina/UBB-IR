package ubb.scs.mpp.start;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Primary;
import org.springframework.context.annotation.Bean;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

@ComponentScan({"ubb.scs.mpp.Repository","ubb.scs.mpp.fest.services.rest"})
@SpringBootApplication
public class StartRestServices {
    public static void main(String[] args) {
        SpringApplication. run(StartRestServices.class, args);
    }
    @Bean(name="properties")
    @Primary
    public Properties getBdProperties(){
        Properties props = new Properties();
        try {
            System.out.println("Searching bd.config in directory "+((new File("")).getAbsolutePath()));
            props.load(new FileReader("C:\\An2\\Sem4\\MPP\\lab11RESTjava\\ServerREST\\bd.config"));
        } catch (IOException e) {
            System.err.println("Configuration file bd.cong not found" + e);
        }
        return props;
    }
}

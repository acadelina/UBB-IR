package ubb.scs.mpp;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import ubb.scs.mpp.Controller.LoginController;
import ubb.scs.mpp.Network.objectprotocol.ServiceObjectProxy;
import ubb.scs.mpp.Network.protobuf.ProtoProxy;
import ubb.scs.mpp.model.Entity;
import ubb.scs.mpp.Repository.*;


import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main extends Application {
    public static void main(String[] args) throws IOException {
        launch(args);
    }
    public static<ID, E extends Entity<ID>> void show(Repository<ID,E> repo) throws RepoException {
        repo.findAll().forEach(System.out::println);
    }

    public static Properties loadProperties() {
        Properties props=new Properties();
        try {
            props.load(new FileReader("bd.config"));
        } catch (IOException e) {
            System.out.println("Cannot find bd.config "+e);
        }
        return props;
    }

    @Override
    public void start(Stage stage) throws Exception {
        var props = loadProperties();
        var ip=props.getProperty("ip");
        var port=Integer.parseInt(props.getProperty("port"));
        var server=new ServiceObjectProxy(ip,port);

//        var angajatRepo = new DbAngajatRepo(props);
//        var spectacolRepo =new DbSpectacolRepository(props);
//        var biletRepo =new DbBiletRepository(props, spectacolRepo);
//
//        var angajatService=new AngajatService(angajatRepo);
//        var spectacolService=new SpectacolService(spectacolRepo);
//        var biletService=new BiletService(biletRepo,spectacolRepo);
//

        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(Main.class.getResource("/Views/loginView.fxml"));
        var scene=new Scene(loader.load());

        stage.setTitle("Login");
        stage.setResizable(true);
        stage.setScene(scene);

        LoginController loginController=loader.getController();
        loginController.setService(server,stage);


        stage.show();
    }
}
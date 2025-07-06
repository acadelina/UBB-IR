package ubb.scs.mpp;

import ubb.scs.mpp.Network.utils.ObjectConcurrentServer;
import ubb.scs.mpp.Repository.*;
import ubb.scs.mpp.Server.ServiceImplementation;
import ubb.scs.mpp.Server.AngajatService;
import ubb.scs.mpp.Server.AppService;
import ubb.scs.mpp.Server.BiletService;
import ubb.scs.mpp.Server.SpectacolService;

import java.io.FileReader;
import java.io.IOException;
import java.rmi.ServerException;
import java.util.Properties;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static Properties loadProperties() {
        Properties props=new Properties();
        try {
            props.load(new FileReader("bd.config"));
        } catch (IOException e) {
            System.out.println("Cannot find bd.config "+e);
        }
        return props;
    }
    public static void main(String[] args) throws IOException {
        var props = loadProperties();
        var angajatRepo = new DbAngajatRepo(props);
        var spectacolRepo =new SpectacolHibernateRepo();
        var biletRepo =new BiletHibernateRepo();

        var angajatService=new AngajatService(angajatRepo);
        var spectacolService=new SpectacolService(spectacolRepo);
        var biletService=new BiletService(biletRepo,spectacolRepo);


        var appService=new AppService(angajatService,biletService,spectacolService);
        var server=new ObjectConcurrentServer(15000,new ServiceImplementation(appService));



        System.out.println("Server started on port 15000...");
        server.start();

    }
}
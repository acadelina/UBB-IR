package ubb.scs.map.comenzi;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import ubb.scs.map.comenzi.Controller.StaffController;
import ubb.scs.map.comenzi.Controller.TableController;
import ubb.scs.map.comenzi.Domain.Table;
import ubb.scs.map.comenzi.Repository.OrderRepo;
import ubb.scs.map.comenzi.Repository.RepoMenu;
import ubb.scs.map.comenzi.Repository.TableRepo;
import ubb.scs.map.comenzi.Service.Service;

import java.io.IOException;
import java.util.List;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String username="postgres";
        String pasword="";
        String url="jdbc:postgresql://localhost:5432/comenzi";
        System.out.println(getClass().getResource("/views/tableview.fxml"));
        RepoMenu repoMenu=new RepoMenu(url,username,pasword);
        TableRepo tableRepo=new TableRepo(url,username,pasword);
        OrderRepo orderRepo=new OrderRepo(url,username,pasword);
        Service service=new Service(repoMenu,tableRepo,orderRepo);

        List<Table> tables=service.getTables();
        for(Table table:tables){
            Stage stage1=new Stage();
            FXMLLoader loginLoader=new FXMLLoader(getClass().getResource("/views/tableview.fxml"));
            Scene loginScene=new Scene(loginLoader.load());
            TableController loginController = loginLoader.getController();
            loginController.setService(service, table.getId(),stage1);
            loginController.init();


            stage1.setResizable(true);
            stage1.setTitle("TABLE"+table.getId());
            stage1.setScene(loginScene);

            stage1.show();
        }
        FXMLLoader loginLoader=new FXMLLoader(getClass().getResource("/views/staffview.fxml"));

        Scene loginScene=new Scene(loginLoader.load());
        stage.setResizable(true);
        stage.setTitle("Staff");
        stage.setScene(loginScene);
        StaffController loginController = loginLoader.getController();
        loginController.setService(service);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}

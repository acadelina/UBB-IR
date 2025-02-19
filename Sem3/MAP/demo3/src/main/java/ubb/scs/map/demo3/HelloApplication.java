package ubb.scs.map.demo3;

import ubb.scs.map.demo3.controller.UtilizatorController;
import ubb.scs.map.demo3.domain.Utilizator;
import ubb.scs.map.demo3.domain.UtilizatorValidator;
import ubb.scs.map.demo3.repository.Repository;
import ubb.scs.map.demo3.repository.dbrepo.UtilizatorDbRepository;
import ubb.scs.map.demo3.services.UtilizatorService;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

//public class HelloApplication extends Application {
//    @Override
//    public void start(Stage stage) throws IOException {
//        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("views/hello-view.fxml"));
//        Scene scene = new Scene(fxmlLoader.load(), 320, 240);
//        stage.setTitle("Hello!");
//        stage.setScene(scene);
//        stage.show();
//    }
//
//    public static void main(String[] args) {
//        launch();
//    }
//}

public class HelloApplication extends Application {

    Repository<Long, Utilizator> utilizatorRepository;
    UtilizatorService service;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
//        String fileN = ApplicationContext.getPROPERTIES().getProperty("data.tasks.messageTask");
//        messageTaskRepository = new InFileMessageTaskRepository
//                (fileN, new MessageTaskValidator());
//        messageTaskService = new MessageTaskService(messageTaskRepository);
        //messageTaskService.getAll().forEach(System.out::println);

        System.out.println("Reading data from file");
        String username="postgres";
        String pasword="postgres";
        String url="jdbc:postgresql://localhost:5432/socialnetwork";
        Repository<Long, Utilizator> utilizatorRepository =
                new UtilizatorDbRepository(url,username, pasword,  new UtilizatorValidator());

        //utilizatorRepository.findAll().forEach(x-> System.out.println(x));
        service =new UtilizatorService(utilizatorRepository);
        initView(primaryStage);
        primaryStage.setWidth(800);
        primaryStage.show();


    }

    private void initView(Stage primaryStage) throws IOException {

        // FXMLLoader fxmlLoader = new FXMLLoader();
        //fxmlLoader.setLocation(getClass().getResource("com/example/guiex1/views/utilizator-view.fxml"));
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("views/utilizator-view.fxml"));

        AnchorPane userLayout = fxmlLoader.load();
        primaryStage.setScene(new Scene(userLayout));

        UtilizatorController userController = fxmlLoader.getController();
        userController.setUtilizatorService(service);

    }
}
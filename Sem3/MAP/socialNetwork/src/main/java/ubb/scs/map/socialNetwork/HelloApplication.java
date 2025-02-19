package ubb.scs.map.socialNetwork;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import ubb.scs.map.socialNetwork.controller.LogInController;
import ubb.scs.map.socialNetwork.domain.User;
import ubb.scs.map.socialNetwork.domain.validators.FriendRequestValidator;
import ubb.scs.map.socialNetwork.domain.validators.FriendshipValidator;
import ubb.scs.map.socialNetwork.domain.validators.MessageValidator;
import ubb.scs.map.socialNetwork.domain.validators.UserValidator;
import ubb.scs.map.socialNetwork.repository.file.FriendshipDBRepository;
import ubb.scs.map.socialNetwork.repository.file.MessageDBRepository;
import ubb.scs.map.socialNetwork.repository.file.RequestDBRepository;
import ubb.scs.map.socialNetwork.repository.file.UserDBRepository;
import ubb.scs.map.socialNetwork.service.ServiceFriendship;
import ubb.scs.map.socialNetwork.service.ServiceMessage;
import ubb.scs.map.socialNetwork.service.ServiceRequest;
import ubb.scs.map.socialNetwork.service.ServiceUser;

import java.io.IOException;
import java.util.List;



public class HelloApplication extends Application {
    ServiceUser serviceUser;
    @Override
    public void start(Stage primaryStage) throws IOException, ClassNotFoundException {
        System.out.println(Class.forName("org.postgresql.Driver"));
        System.out.println(getClass().getResource("/css/chatstyle.css"));
        String username="postgres";
        String pasword="";
        String url="jdbc:postgresql://localhost:5432/socialnetwork1";
        UserDBRepository utilizatorRepository =
                new UserDBRepository(new UserValidator(),url,username, pasword);
        ServiceUser service=new ServiceUser(utilizatorRepository);
        this.serviceUser=service;
        FriendshipDBRepository friendshipDBRepository=new FriendshipDBRepository(new FriendshipValidator(),url,username,pasword);

        ServiceFriendship serviceFriendship =new ServiceFriendship(friendshipDBRepository,utilizatorRepository);

        RequestDBRepository requestDBRepository=new RequestDBRepository(new FriendRequestValidator(),url,username,pasword);
        ServiceRequest serviceRequest=new ServiceRequest(friendshipDBRepository,utilizatorRepository,requestDBRepository);
        MessageDBRepository messageDBRepository=new MessageDBRepository(new MessageValidator(),url,username,pasword);
        ServiceMessage serviceMessage=new ServiceMessage(messageDBRepository,friendshipDBRepository);
        //utilizatorRepository.findAll().forEach(x-> System.out.println(x));
        FXMLLoader loginLoader=new FXMLLoader(getClass().getResource("/views/login-view.fxml"));
        //loginLoader.setLocation());
        Scene loginScene=new Scene(loginLoader.load());
        primaryStage.setResizable(true);
        primaryStage.setTitle("Login");
        primaryStage.setScene(loginScene);
        LogInController loginController = loginLoader.getController();
        loginController.setService(serviceUser,serviceFriendship,serviceRequest,serviceMessage,primaryStage);
        List<User> l=serviceRequest.pendingRequests(1L);
        l.forEach(System.out::println);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

    private void initView(Stage primaryStage) throws IOException {

        // FXMLLoader fxmlLoader = new FXMLLoader();
        //fxmlLoader.setLocation(getClass().getResource("com/example/guiex1/views/utilizator-view.fxml"));
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("ubb/scs/map/socialNetwork/views/login-view.fxml"));

        AnchorPane userLayout = fxmlLoader.load();
        primaryStage.setScene(new Scene(userLayout));

        LogInController loginController = fxmlLoader.getController();
        //loginController.setService(serviceUser);

    }
}

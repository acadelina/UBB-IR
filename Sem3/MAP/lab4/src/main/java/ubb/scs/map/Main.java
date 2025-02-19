package ubb.scs.map;

import ubb.scs.map.UI.Ui;
import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.FriendshipValidator;
import ubb.scs.map.domain.validators.UserValidator;
import ubb.scs.map.domain.validators.ValidationException;
import ubb.scs.map.repository.Repository;
import ubb.scs.map.repository.file.FriendshipDBRepository;
import ubb.scs.map.repository.file.FriendshipRepository;
import ubb.scs.map.repository.file.UserDBRepository;
import ubb.scs.map.repository.file.UserRepository;
import ubb.scs.map.repository.memory.InMemoryRepository;
import ubb.scs.map.service.ServiceFriendship;
import ubb.scs.map.service.ServiceUser;

public class Main {
    public static void main(String[] args) {
        FriendshipDBRepository repoFriendship = new FriendshipDBRepository(new FriendshipValidator(),"jdbc:postgresql://localhost:5432/socialnetwork","postgres","Eliada31");
        UserDBRepository repoUser = new UserDBRepository(new UserValidator(),"jdbc:postgresql://localhost:5432/socialnetwork","postgres","Eliada31");
        ServiceUser serviceUser=new ServiceUser(repoUser);
        ServiceFriendship serviceFriendship =new ServiceFriendship(repoFriendship,repoUser);
        Ui ui = new Ui(serviceUser,serviceFriendship);
        ui.run();

    }
}
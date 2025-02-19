package ubb.scs.map.service;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.FriendshipValidator;
import ubb.scs.map.domain.validators.UserValidator;
import ubb.scs.map.domain.validators.ValidationException;
import ubb.scs.map.repository.file.FriendshipRepository;
import ubb.scs.map.repository.file.UserRepository;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.List;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;

class ServiceFriendshipTest {

    private ServiceFriendship serviceFriendship;
    private FriendshipRepository friendshipRepo;
    private UserRepository userRepo;

    @BeforeEach
    void setUp() throws FileNotFoundException {

        PrintWriter writer = new PrintWriter("./data/testFriendships.txt");
        writer.print("");
        writer.close();
        friendshipRepo = new FriendshipRepository(new FriendshipValidator(), "./data/testFriendships.txt");
        userRepo = new UserRepository(new UserValidator(), "./data/testUsers.txt");

        User user1 = new User("John", "D");
        user1.setId(1L);
        User user2 = new User("Ana", "D");
        user2.setId(2L);
        User user3 = new User("Ale", "S");
        user3.setId(3L);

        userRepo.save(user1);
        userRepo.save(user2);
        userRepo.save(user3);

        serviceFriendship = new ServiceFriendship(friendshipRepo, userRepo);
    }

    @Test
    void getFriendships() {
        assertTrue(serviceFriendship.getFriendships().isEmpty());
        User u1=null,u2=null;
        try {
             u1 = userRepo.findOne(1L).orElseThrow(ValidationException::new);
             u2 = userRepo.findOne(2L).orElseThrow(ValidationException::new);
        }
        catch (ValidationException e) {

        }
        Friendship friendship = new Friendship(u1, u2);
        friendshipRepo.save(friendship);


        List<Friendship> friendships = serviceFriendship.getFriendships();
        assertEquals(1, friendships.size());
        assertEquals(friendship, friendships.get(0));
    }

    @Test
    void addFriendship() throws ServiceException {

        serviceFriendship.addFriendship(1L, 2L);

        List<Friendship> friendships = serviceFriendship.getFriendships();
        assertEquals(1, friendships.size());

        Friendship friendship = friendships.get(0);
        assertEquals(1L, friendship.getId().getE1());
        assertEquals(2L, friendship.getId().getE2());


        ServiceException exception = assertThrows(ServiceException.class, () -> {
            serviceFriendship.addFriendship(1L, 2L);
        });

        assertEquals("Friendship already exist!", exception.getMessage());
    }

    @Test
    void deleteAllFriendships() throws ServiceException {
        serviceFriendship.addFriendship(1L, 2L);
        serviceFriendship.addFriendship(1L, 3L);

        assertEquals(2, serviceFriendship.getFriendships().size());

        serviceFriendship.deleteAllFriendships(1L);

        assertTrue(serviceFriendship.getFriendships().isEmpty());
    }

    @Test
    void removeFriendship() throws ServiceException, FileNotFoundException {

        serviceFriendship.addFriendship(1L, 2L);

        assertEquals(1, serviceFriendship.getFriendships().size());

        serviceFriendship.removeFriendship(new Tuple<>(1L, 2L));

        assertTrue(serviceFriendship.getFriendships().isEmpty());
    }

    @Test
    void getUsers() {
        List<User> users = serviceFriendship.getUsers();

        assertEquals(3, users.size());
        assertEquals("John", users.get(0).getFirstName());
        assertEquals("Ana", users.get(1).getFirstName());
        assertEquals("Ale", users.get(2).getFirstName());
    }

    @Test
    void communitiesNumber() throws ServiceException {
        assertEquals(3, serviceFriendship.communitiesNumber());

        serviceFriendship.addFriendship(1L, 2L);
        serviceFriendship.addFriendship(2L, 3L);

        assertEquals(1, serviceFriendship.communitiesNumber());
    }

    @Test
    void socialCommunity() throws ServiceException, FileNotFoundException {
        PrintWriter writer = new PrintWriter("./data/testFriendships.txt");
        writer.print("");
        writer.close();
        serviceFriendship.addFriendship(1L, 2L);
        serviceFriendship.addFriendship(2L, 3L);

        String result = serviceFriendship.socialCommunity();

        assertTrue(result.contains("1.John,D"));
        assertTrue(result.contains("2.Ana,D"));
        assertTrue(result.contains("3.Ale,S"));
    }
}
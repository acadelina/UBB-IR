package ubb.scs.map.service;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.UserValidator;
import ubb.scs.map.repository.memory.InMemoryRepository;

import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class ServiceUserTest {

    private ServiceUser serviceUser;
    private InMemoryRepository<Long, User> userRepository;
    @BeforeEach
    void setUp() {
        userRepository = new InMemoryRepository<>(new UserValidator());

        serviceUser = new ServiceUser(userRepository);

        serviceUser.addUser("John", "D", 1L);
        serviceUser.addUser("Ana", "D", 2L);
        serviceUser.addUser("Ale", "S", 3L);
    }

    @Test
    void addUser() {
        List<User> users = serviceUser.getUsers();
        assertEquals(3, users.size());

        serviceUser.addUser("Bob", "J", 4L);


        users = serviceUser.getUsers();
        assertEquals(4, users.size());

        User addedUser = users.stream().filter(user -> user.getId().equals(4L)).findFirst().orElse(null);
        assertNotNull(addedUser);
        assertEquals("Bob", addedUser.getFirstName());
        assertEquals("J", addedUser.getLastName());
    }

    @Test
    void removeUser() throws ServiceException {
        List<User> users = serviceUser.getUsers();
        assertEquals(3, users.size());

        serviceUser.removeUser(2L);

        users = serviceUser.getUsers();
        assertEquals(2, users.size());

        assertTrue(users.stream().noneMatch(user -> user.getId().equals(2L)));

        ServiceException exception = assertThrows(ServiceException.class, () -> {
            serviceUser.removeUser(999L);
        });

        assertEquals("User not found", exception.getMessage());
    }

    @Test
    void getUsers() {
        List<User> users = serviceUser.getUsers();

        assertEquals(3, users.size());

        User user1 = users.stream().filter(user -> user.getId().equals(1L)).findFirst().orElse(null);
        assertNotNull(user1);
        assertEquals("John", user1.getFirstName());
        assertEquals("D", user1.getLastName());

        User user2 = users.stream().filter(user -> user.getId().equals(2L)).findFirst().orElse(null);
        assertNotNull(user2);
        assertEquals("Ana", user2.getFirstName());
        assertEquals("D", user2.getLastName());
    }
}
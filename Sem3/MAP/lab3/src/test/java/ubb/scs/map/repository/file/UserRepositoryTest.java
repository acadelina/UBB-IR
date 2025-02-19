package ubb.scs.map.repository.file;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.UserValidator;

import static org.junit.jupiter.api.Assertions.*;
class UserRepositoryTest {

    private UserRepository userRepository;
    @BeforeEach
    void setUp() {
        userRepository = new UserRepository(new UserValidator(), "./data/testUsers.txt");
    }

    @Test
    void createEntity() {
        String line = "1;John;D";
        User user = userRepository.createEntity(line);
        assertEquals(1L, user.getId());
        assertEquals("John", user.getFirstName());
        assertEquals("D", user.getLastName());
    }

    @Test
    void saveEntity() {
        User user = new User("Ana", "D");
        user.setId(2L);
        String result = userRepository.saveEntity(user);
        assertEquals("2;Ana;D", result);
    }
}
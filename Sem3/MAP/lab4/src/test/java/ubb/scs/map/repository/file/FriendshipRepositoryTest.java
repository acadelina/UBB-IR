package ubb.scs.map.repository.file;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.validators.FriendshipValidator;

import static org.junit.jupiter.api.Assertions.*;

class FriendshipRepositoryTest {
    private FriendshipRepository friendshipRepository;
    @BeforeEach
    void setUp() {
        friendshipRepository = new FriendshipRepository(new FriendshipValidator(), "./data/testFriendships.txt");
    }

    @Test
    void createEntity() {
        String line = "1;2";
        Friendship friendship = friendshipRepository.createEntity(line);
        assertEquals(1L, friendship.getId().getE1());
        assertEquals(2L, friendship.getId().getE2());
    }

    @Test
    void saveEntity() {
        Friendship friendship = new Friendship();
        friendship.setId(new Tuple<>(1L, 2L));
        String result = friendshipRepository.saveEntity(friendship);
        assertEquals("1;2", result);
    }
}
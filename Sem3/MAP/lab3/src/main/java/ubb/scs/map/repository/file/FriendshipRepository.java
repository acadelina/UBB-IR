package ubb.scs.map.repository.file;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.Validator;

import java.util.List;

public class FriendshipRepository extends AbstractFileRepository<Tuple<Long,Long>, Friendship> {


    public FriendshipRepository(Validator<Friendship> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    public Friendship createEntity(String line) {
        String[] splited=line.split(";");
        Tuple<Long,Long> tuple=new Tuple(Long.parseLong(splited[0]),Long.parseLong(splited[1]));
        Friendship friendship = new Friendship();
        friendship.setId(tuple);
        return friendship;
    }

    @Override
    public String saveEntity(Friendship entity) {
        Tuple<Long,Long> tuple=entity.getUsers();
        String line=tuple.getE1().toString()+";"+tuple.getE2().toString();
        return line;
    }


}

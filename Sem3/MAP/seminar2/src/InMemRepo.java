import java.util.HashMap;

public class InMemRepo<ID,E extends Entity<ID>> implements Repository<ID,E> {

    private HashMap<ID,E> entities;

    @Override
    public E findOne(ID id) {
        return null;
    }

    @Override
    public Iterable<E> findAll() {
        return null;
    }

    public InMemRepo(HashMap<ID, E> entities) {
        this.entities = entities;
    }

    @Override
    public E save(E entity) {
        entities.put(entity.getId(), entity);
        return null;
    }

    @Override
    public E delete(ID id) {
        return null;
    }

    @Override
    public E update(E entity) {
        return null;
    }
}

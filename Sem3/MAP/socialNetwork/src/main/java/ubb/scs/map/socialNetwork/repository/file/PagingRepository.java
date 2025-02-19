package ubb.scs.map.socialNetwork.repository.file;


import ubb.scs.map.socialNetwork.domain.Entity;
import ubb.scs.map.socialNetwork.repository.Repository;

public interface PagingRepository<ID,E extends Entity<ID>> extends Repository<ID,E> {
    Page<E> findAll(Pageable pageable);
}

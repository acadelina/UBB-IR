package ubb.scs.map.zboruri2024.Repository;


import ubb.scs.map.zboruri2024.Domain.Entity;

import java.util.Optional;

public interface Repository<ID, E extends Entity<ID>> {

    Optional<E> findOne(ID id);


    Iterable<E> findAll();
    
}

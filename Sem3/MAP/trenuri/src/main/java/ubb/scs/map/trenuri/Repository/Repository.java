package ubb.scs.map.trenuri.Repository;


import ubb.scs.map.trenuri.Domain.Entity;

import java.util.Optional;

public interface Repository<ID, E extends Entity<ID>> {

    Optional<E> findOne(ID id);


    Iterable<E> findAll();
    
}

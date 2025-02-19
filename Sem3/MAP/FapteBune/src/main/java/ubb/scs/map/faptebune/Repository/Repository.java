package ubb.scs.map.faptebune.Repository;


import ubb.scs.map.faptebune.Domain.Entity;

import java.util.Optional;

public interface Repository<ID, E extends Entity<ID>> {

    Optional<E> findOne(ID id);


    Iterable<E> findAll();
    
}

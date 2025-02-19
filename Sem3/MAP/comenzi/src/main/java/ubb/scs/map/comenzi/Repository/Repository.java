package ubb.scs.map.comenzi.Repository;


import ubb.scs.map.comenzi.Domain.Entity;

import java.util.Optional;

public interface Repository<ID, E extends Entity<ID>> {

    Optional<E> findOne(ID id);


    Iterable<E> findAll();
    
}

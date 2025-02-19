package ubb.scs.map.vacanta.Repository;


import ubb.scs.map.vacanta.Domain.Entity;

import java.util.Optional;

public interface Repository<ID, E extends Entity<ID>> {

    Optional<E> findOne(ID id);


    Iterable<E> findAll();
    
}

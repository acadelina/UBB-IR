package ubb.scs.map.examen.Repository;


import ubb.scs.map.examen.Domain.Entity;

import java.util.Optional;

public interface Repository<ID, E extends Entity<ID>> {

    Optional<E> findOne(ID id);


    Iterable<E> findAll();
    
}

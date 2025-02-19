package ubb.scs.map.clinica.Repository;


import ubb.scs.map.clinica.Domain.Entity;

import java.util.Optional;

public interface Repository<ID, E extends Entity<ID>> {

    Optional<E> findOne(ID id);


    Iterable<E> findAll();
    
}

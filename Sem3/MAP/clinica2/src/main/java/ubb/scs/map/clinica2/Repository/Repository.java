package ubb.scs.map.clinica2.Repository;


import ubb.scs.map.clinica2.Domain.Entity;

import java.util.Optional;

public interface Repository<ID, E extends Entity<ID>> {

    Optional<E> findOne(ID id);


    Iterable<E> findAll();
    
}

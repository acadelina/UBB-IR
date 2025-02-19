package ubb.scs.map.administratiebloc.Repository;


import ubb.scs.map.administratiebloc.Domain.Entity;
import ubb.scs.map.administratiebloc.Domain.validators.ValidationException;

import java.util.Optional;

public interface Repository<ID, E extends Entity<ID>> {

    Optional<E> findOne(ID id);


    Iterable<E> findAll();
    
}

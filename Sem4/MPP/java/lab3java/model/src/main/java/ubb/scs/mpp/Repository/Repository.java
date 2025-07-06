package ubb.scs.mpp.Repository;

import ubb.scs.mpp.Domain.Entity;

public interface Repository<ID, E extends Entity<ID>> {

    E findOne(ID id) throws RepoException;

    Iterable<E> findAll() throws RepoException;

    E save(E entity) throws RepoException;

    E delete(ID id) throws RepoException;

    E update(E entity) throws RepoException;
    
}

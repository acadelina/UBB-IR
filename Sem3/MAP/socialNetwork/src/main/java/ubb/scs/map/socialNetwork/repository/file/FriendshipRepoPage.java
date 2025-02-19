package ubb.scs.map.socialNetwork.repository.file;

import ubb.scs.map.socialNetwork.domain.Entity;

public interface FriendshipRepoPage<ID,E extends Entity<ID>> extends PagingRepository<ID,E> {
    Page<E> findAllFriendships(Pageable pageable) ;

    Page<E> findAllUserFriends(Pageable pageable,Long userId) ;

    Page<E> findAllUserFriendRequests(Pageable pageable,Long userId) ;
}

package ubb.scs.map.service;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.ValidationException;
import ubb.scs.map.repository.Repository;
import ubb.scs.map.repository.file.FriendshipDBRepository;
import ubb.scs.map.repository.file.FriendshipRepository;
import ubb.scs.map.repository.file.UserDBRepository;
import ubb.scs.map.repository.file.UserRepository;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;

public class ServiceFriendship {

    Repository<Long, User> repoUser;
    Repository<Tuple<Long,Long>, Friendship> repoFriendship;

    public ServiceFriendship(Repository<Tuple<Long,Long>, Friendship>  repoFriendship, Repository<Long, User>  repoUser) {
        this.repoUser = repoUser;
        this.repoFriendship = repoFriendship;
    }

    public List<Friendship> getFriendships() {
            List<Friendship> friendships = new ArrayList<>();
            repoFriendship.findAll().forEach(friendships::add);
            return friendships;
    }

    public List<User> getUsers()
    {
        List<User> users=new ArrayList<>();
        repoUser.findAll().forEach(users::add);
        return users;
    }


    public void addFriendship(Long id1,Long id2) throws ServiceException {
            User user1,user2;
            try {
                user1 = repoUser.findOne(id1).orElseThrow(ValidationException::new);
                user2 = repoUser.findOne(id2).orElseThrow(ValidationException::new);
            }
            catch(ValidationException e) {
                throw new ServiceException("User not found");
            }


            getFriendships().forEach(
                    f->{
                        if((f.getId().getE1().equals(user1.getId())&&f.getId().getE2().equals(user2.getId()))||(f.getId().getE1().equals(user2.getId())&&f.getId().getE2().equals(user1.getId())))
                        {    throw new ValidationException("Friendship already exist!");}
                    }
            );


            user1.addFriend(user2);
            user2.addFriend(user1);
            Friendship friendship=new Friendship(user1,user2);
            repoFriendship.save(friendship);
    }


    public void removeFriendship(Tuple<Long,Long> id) throws ServiceException {
        User user1,user2;
        boolean exist= getFriendships().stream()
                .anyMatch(it-> Objects.equals(id,it.getId()));

        if(!exist)
            throw new ServiceException("Friendship does not exist!");
        try {
            user1 = repoUser.findOne(id.getE1()).orElseThrow(ValidationException::new);
            user2 = repoUser.findOne(id.getE2()).orElseThrow(ValidationException::new);
        }catch(ValidationException e)
        {
            throw new ServiceException("User not found");
        }
        user1.removeFriend(user2);
        user2.removeFriend(user1);
        repoFriendship.delete(id);
    }

    /*
     *
     * @param id -the id of one of the users from the friendships that we want to delete
     *
     */
    public void deleteAllFriendships(Long id) throws ValidationException {
        getFriendships().forEach(
                f->{
                    if(f.getId().getE1().equals(id)||f.getId().getE2().equals(id))
                        try{
                            removeFriendship(f.getId());
                        } catch (ServiceException e) {
                            throw new ValidationException(e);
                        }
                }
        );

    }

    /*
    *
    * @return - the number of communities
    *
    */
    public int communitiesNumber()
    {
        List<Long> visitedUsers=new ArrayList<>();
        List<User> users=getUsers();
        AtomicInteger count= new AtomicInteger();
        users.forEach(u->{
            if(!visitedUsers.contains(u.getId()))
            {
                List<User> comunity=new ArrayList<>();
                try {
                    DFS(u.getId(),visitedUsers,comunity);
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }
                count.getAndIncrement();
            }
        });

        return count.get();
    }


    /*
    *
    * @return- a string with the users that form the most social community
    *
    */
    public String socialCommunity()
    {

        List<Long> visitedUsers = new ArrayList<>();


        AtomicInteger max= new AtomicInteger(-1);
        Iterable<User> all = repoUser.findAll();


        AtomicReference<List<User>> socialCommunity = new AtomicReference<>(new ArrayList<>());
        StringBuilder rez = new StringBuilder();

        all.forEach(it->{
            if(!visitedUsers.contains(it.getId())){
                List<User> currentCommunity = new ArrayList<>();
                try {
                    DFS(it.getId(), visitedUsers, currentCommunity);
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }

                if (currentCommunity.size() > max.get()) {
                    max.set(currentCommunity.size());
                    socialCommunity.set(currentCommunity);
                }
            }
        });


        socialCommunity.get().forEach(user-> rez.append(user.getId()+"."+user.getFirstName()).append(" ").append(user.getLastName()).append("  "));

        return rez.toString();
    }

    private void DFS(Long userId, List<Long> visitedUsers, List<User> community) throws SQLException {

        visitedUsers.add(userId);

        Optional<User> user=repoUser.findOne(userId);
        if(user.isPresent()){

            community.add(user.get());

            List<Friendship> friendships = getFriendships();

            friendships.stream()
                    .filter(friendship -> friendship.getId().getE1().equals(userId) || friendship.getId().getE2().equals(userId))
                    .forEach(friendship ->
                    {
                        Long friendId = (friendship.getId().getE1().equals(userId) ? friendship.getId().getE2() : friendship.getId().getE1());
                        if (!visitedUsers.contains(friendId)) {
                            try {
                                DFS(friendId, visitedUsers, community);
                            } catch (SQLException e) {
                                throw new RuntimeException(e);
                            }
                        }
                    });
        }
    }


}

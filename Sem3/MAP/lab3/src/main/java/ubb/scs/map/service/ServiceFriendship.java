package ubb.scs.map.service;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;
import ubb.scs.map.repository.Repository;
import ubb.scs.map.repository.file.FriendshipRepository;
import ubb.scs.map.repository.file.UserRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;

public class ServiceFriendship {

    Repository<Long, User> repoUser;
    Repository<Tuple<Long,Long>, Friendship> repoFriendship;

    public ServiceFriendship(FriendshipRepository repoFriendship, UserRepository repoUser) {
        this.repoUser = repoUser;
        this.repoFriendship = repoFriendship;
    }

    public List<Friendship> getFriendships() {
            List<Friendship> friendships = new ArrayList<Friendship>();
            for(Friendship friendship:  repoFriendship.findAll())
                 friendships.add(friendship);
            return friendships;
    }

    public List<User> getUsers()
    {
        List<User> users=new ArrayList<>();
        for(User user:repoUser.findAll())
            users.add(user);
        return users;
    }


    public void addFriendship(Long id1,Long id2) throws ServiceException {
            User user1=repoUser.findOne(id1);
            User user2=repoUser.findOne(id2);
            if(user1==null || user2==null)
                throw new ServiceException("User not found");
            boolean exist=false;
            for(Friendship friendship: getFriendships())
                if((friendship.getId().getE1().equals(user1.getId())&&friendship.getId().getE2().equals(user2.getId()))||(friendship.getId().getE1().equals(user2.getId())&&friendship.getId().getE2().equals(user1.getId())))
                    exist=true;

            if(exist)
                throw new ServiceException("Friendship already exist!");
            user1.addFriend(user2);
            user2.addFriend(user1);
            Friendship friendship=new Friendship(user1,user2);
            repoFriendship.save(friendship);
    }


    public void removeFriendship(Tuple<Long,Long> id) throws ServiceException {
        boolean exist= false;
        for(Friendship friendship:  getFriendships())
            if(friendship.getId().equals(id)) {
                exist = true;
                if (friendship.getId().getE1().equals(id.getE2()))
                    id = new Tuple<>(id.getE2(), id.getE1());
                break;
            }
        if(!exist)
            throw new ServiceException("Friendship does not exist!");
        User user1=repoUser.findOne(id.getE1());
        User user2=repoUser.findOne(id.getE2());
        user1.removeFriend(user2);
        user2.removeFriend(user1);
        repoFriendship.delete(id);
    }

    /*
     *
     * @param id -the id of one of the users from the friendships that we want to delete
     *
     */
    public void deleteAllFriendships(Long id) throws ServiceException {
        for(Friendship friendship:  getFriendships())
        {
            if(friendship.getId().getE1().equals(id)||friendship.getId().getE2().equals(id))
                removeFriendship(friendship.getId());
        }
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
        int count=0;
        for(User user:users)
        {
            if(!visitedUsers.contains(user.getId()))
            {
                List<User> comunity=new ArrayList<>();
                DFS(user.getId(),visitedUsers,comunity);
                count++;
            }

        }
        return count;
    }


    /*
    *
    * @return- a string with the users that form the most social community
    *
    */
    public String socialCommunity()
    {

        List<User> users=getUsers();
        List<Long> visitedUsers=new ArrayList<>();
        Integer max=-1;
        List<User> socialComunity=new ArrayList<>();
        String comunityString="";
        for(User user:users)
        {
            if(!visitedUsers.contains(user.getId()))
            {
                List<User> community=new ArrayList<>();
                DFS(user.getId(),visitedUsers,community);
                if(community.size()>max)
                {
                    max=community.size();
                    socialComunity=community;
                }
            }
        }
        for(User user:socialComunity)
            comunityString+=user.getId()+"."+user.getFirstName()+", "+user.getLastName()+"; ";

        return comunityString;
    }

    private void DFS(Long userId, List<Long> visitedUsers, List<User> community) {

        visitedUsers.add(userId);

        User user = repoUser.findOne(userId);

            community.add(user);

            List<Friendship> friendships = getFriendships();

            friendships.stream()
                    .filter(friendship -> friendship.getId().getE1().equals(userId) || friendship.getId().getE2().equals(userId))
                    .forEach(friendship ->
                    {
                        Long friendId = (friendship.getId().getE1().equals(userId) ? friendship.getId().getE2() : friendship.getId().getE1());
                        if (!visitedUsers.contains(friendId)) {
                                DFS(friendId, visitedUsers, community);
                        }
                    });
    }


}

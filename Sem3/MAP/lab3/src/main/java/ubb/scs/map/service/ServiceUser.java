package ubb.scs.map.service;

import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.UserValidator;
import ubb.scs.map.repository.Repository;
import ubb.scs.map.repository.file.UserRepository;

import java.util.ArrayList;
import java.util.List;

public class ServiceUser {

    private Repository<Long, User> repository;

    public ServiceUser(Repository<Long, User> repository) {
        this.repository =repository;
    }

    public void addUser(String firstName, String lastName, Long id) {
        User user=new User(firstName,lastName);
        user.setId(id);
        repository.save(user);
    }

    public void removeUser(Long id) throws ServiceException {
        boolean exist=false;
        for (User user:getUsers()) {
            if(user.getId().equals(id)) {
                exist=true;
            }
        }
        if(!exist) {
            throw new ServiceException("User not found");
        }
        repository.delete(id);
    }

    public List<User> getUsers() {
        List<User> list=new ArrayList<>();
        for(User u:repository.findAll())
            list.add(u);
        return list;
    }



}

package ubb.scs.map.service;

import ubb.scs.map.domain.User;
import ubb.scs.map.repository.Repository;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.atomic.AtomicBoolean;

public class ServiceUser {

    private Repository<Long, User> repository;

    public ServiceUser(Repository<Long, User> repository) {
        this.repository =repository;
    }

    public void addUser(String firstName, String lastName, Long id) throws ServiceException{
        User user=new User(firstName,lastName);
        user.setId(id);
        AtomicBoolean exist= new AtomicBoolean(false);
        repository.findAll().forEach(it -> {
            if (Objects.equals(it.getId(), user.getId())) {
                exist.set(true);
            }
        });
        if(exist.get()){
            throw new ServiceException("User already exists");
        }

        repository.save(user);
    }

    public void removeUser(Long id) throws ServiceException {


        try {
            User user = repository.findOne(id)
                    .orElseThrow(() -> new ServiceException("User not found with ID: " + id));
            repository.delete(id);
            System.out.println("User with ID " + id + " successfully deleted.");
        } catch (ServiceException e) {
            System.err.println(e.getMessage());
            throw e;
        }

    }

    public List<User> getUsers() {
        List<User> list=new ArrayList<>();
        repository.findAll().forEach(list::add);
        return list;
    }



}

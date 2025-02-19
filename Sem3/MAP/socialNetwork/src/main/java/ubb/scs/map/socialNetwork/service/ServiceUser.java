package ubb.scs.map.socialNetwork.service;

import ubb.scs.map.socialNetwork.domain.User;
import ubb.scs.map.socialNetwork.repository.Repository;
import ubb.scs.map.socialNetwork.utils.events.ChangeEventType;
import ubb.scs.map.socialNetwork.utils.events.UtilizatorEntityChangeEvent;
import ubb.scs.map.socialNetwork.utils.observer.Observable;
import ubb.scs.map.socialNetwork.utils.observer.Observer;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.concurrent.atomic.AtomicBoolean;

public class ServiceUser implements Observable {

    private Repository<Long, User> repository;
    List<Observer> observers= new ArrayList<>();

    public ServiceUser(Repository<Long, User> repository) {
        this.repository =repository;
    }

    public void addUser(String firstName, String lastName, String email,String username,String password) throws ServiceException{
        User user=new User(firstName,lastName,email,username,password);

        AtomicBoolean exist= new AtomicBoolean(false);
        repository.findAll().forEach(it -> {
            if (Objects.equals(it.getId(), user.getId())) {
                exist.set(true);
            }
        });
        if(exist.get()){
            throw new ServiceException("User already exists");
        }

        if(repository.save(user).isEmpty())
        {
            UtilizatorEntityChangeEvent event = new UtilizatorEntityChangeEvent(ChangeEventType.ADD, user);
            notifyObservers();

        }
    }

    public void updateUser(Long id,String firstName,String lastName,String email) throws ServiceException{
        User user;
        try{
            user= repository.findOne(id).orElseThrow(() -> new ServiceException("User not found with ID: " + id));
        }catch (ServiceException e) {
            System.err.println(e.getMessage());
            throw e;
        }
        user.setFirstName(firstName);
        user.setLastName(lastName);
        user.setEmail(email);
        repository.update(user);
        notifyObservers();
    }

    public void removeUser(Long id) throws ServiceException {


        try {
            User user = repository.findOne(id)
                    .orElseThrow(() -> new ServiceException("User not found with ID: " + id));
            Optional<User> user2=repository.delete(id);
            notifyObservers();
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

    public User login(String username, String password) {
        Optional<User> user= getUsers().stream().filter(it -> Objects.equals(it.getUsername(), username) && Objects.equals(it.getPassword(),password)).findFirst();
        if(user.isEmpty()) return null;
        return user.get();
    }

    public User findUser(Long id) {
        return repository.findOne(id).orElse(null);
    }

    @Override
    public void addObserver(Observer e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers() {
        observers.forEach(observer -> observer.update());
    }
}

package ubb.scs.map.faptebune.Service;

import ubb.scs.map.faptebune.Domain.Oras;
import ubb.scs.map.faptebune.Domain.Persoana;
import ubb.scs.map.faptebune.Repository.PersoanaRepo;
import ubb.scs.map.faptebune.Validators.ValidationException;
import ubb.scs.map.faptebune.observer.Observable;
import ubb.scs.map.faptebune.observer.Observer;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ServicePersoana implements Observable {
    PersoanaRepo persoanaRepo;
    List<Observer> observers=new ArrayList<>();
    public ServicePersoana(PersoanaRepo persoanaRepo) {
        this.persoanaRepo = persoanaRepo;
    }

    public void addPersoana(String nume,String preume,String username,String parola,Oras oras,String strada,String numarStrada,String telefon) {
        List<Persoana> persoane=new ArrayList<Persoana>();
        persoanaRepo.findAll().forEach(p->persoane.add(p));
        if(persoane.stream().map(Persoana::getUsername).anyMatch(u->u.equals(username)))
            throw new ValidationException("Username deja existent");
        persoanaRepo.addPersoana(new Persoana(nume,preume,username,parola,oras,strada,numarStrada,telefon));
        notifyObservers();
    }

    public List<Persoana> getPersoane() {
       return (List<Persoana>) persoanaRepo.findAll();
    }

    public List<Oras> orase()
    {
        return Arrays.stream(Oras.values()).toList();
    }

    public Persoana login(String username,String password)
    {
        List<Persoana> persoane=new ArrayList<Persoana>();
        persoanaRepo.findAll().forEach(p->persoane.add(p));
        return persoane.stream().filter(p->p.getUsername().equals(username)&&p.getParola().equals(password)).findFirst().orElse(null);
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
        observers.forEach(Observer::update);
    }
}

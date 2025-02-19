package ubb.scs.map.anar.Service;

import ubb.scs.map.anar.Domain.Localitate;
import ubb.scs.map.anar.Domain.Rau;
import ubb.scs.map.anar.Repository.RepoLocalitate;
import ubb.scs.map.anar.Repository.RepoRau;
import ubb.scs.map.anar.observer.Observable;
import ubb.scs.map.anar.observer.Observer;

import java.util.ArrayList;
import java.util.List;

public class Service implements Observable {
    List<Observer> observers=new ArrayList<Observer>();
    RepoLocalitate repoLocalitate;
    RepoRau repoRau;

    public Service(RepoRau repoRau, RepoLocalitate repoLocalitate) {
        this.repoRau = repoRau;
        this.repoLocalitate = repoLocalitate;
    }

    public List<Rau> getRauri()
    {
        List<Rau> rauri=new ArrayList<>();
        repoRau.findAll().forEach(rauri::add);
        return rauri;
    }

    public List<Localitate> getRiscMin()
    {
        List<Localitate> riscMin=new ArrayList<>();
        repoLocalitate.findAll().forEach(riscMin::add);
        return riscMin.stream().filter(l->{
            Rau rau=repoRau.findOne(l.getRau()).orElse(null);
            return l.getCotamin()>=rau.getCotamedie();
        }).toList();
    }

    public List<Localitate> getRiscMed()
    {
        List<Localitate> riscMin=new ArrayList<>();
        repoLocalitate.findAll().forEach(riscMin::add);
        return riscMin.stream().filter(l->{
            Rau rau=repoRau.findOne(l.getRau()).orElse(null);
            return l.getCotamin()<rau.getCotamedie() && l.getCotamax()>=rau.getCotamedie();
        }).toList();
    }

    public List<Localitate> getRiscRid()
    {
        List<Localitate> riscMin=new ArrayList<>();
        repoLocalitate.findAll().forEach(riscMin::add);
        return riscMin.stream().filter(l->{
            Rau rau=repoRau.findOne(l.getRau()).orElse(null);
            return l.getCotamax()<rau.getCotamedie();
        }).toList();
    }

    public void schimbaCota(Integer idrau,Float cota)
    {
        Rau rau=repoRau.findOne(idrau).orElse(null);
        rau.setCotamedie(cota);
        repoRau.update(rau);
        notifyObservers();
    }

    public Rau getRau(Integer id)
    {
        return repoRau.findOne(id).orElse(null);
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

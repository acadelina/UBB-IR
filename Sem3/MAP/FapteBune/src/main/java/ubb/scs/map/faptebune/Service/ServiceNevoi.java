package ubb.scs.map.faptebune.Service;

import ubb.scs.map.faptebune.Domain.Nevoie;
import ubb.scs.map.faptebune.Domain.Oras;
import ubb.scs.map.faptebune.Domain.Persoana;
import ubb.scs.map.faptebune.Repository.NevoieRepo;
import ubb.scs.map.faptebune.Repository.PersoanaRepo;
import ubb.scs.map.faptebune.observer.Observable;
import ubb.scs.map.faptebune.observer.Observer;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class ServiceNevoi implements Observable {
    NevoieRepo nevoieRepo;
    PersoanaRepo persoanaRepo;
    List<Observer> observers=new ArrayList<>();
    public ServiceNevoi(NevoieRepo nevoieRepo, PersoanaRepo persoanaRepo) {
        this.nevoieRepo = nevoieRepo;
        this.persoanaRepo = persoanaRepo;
    }

    public List<Nevoie> nevoiOras(Oras oras,Long id)
    {
        List<Nevoie> nevoi = new ArrayList<Nevoie>();
        nevoieRepo.findAll().forEach(nevoi::add);
        return nevoi.stream()
                .filter(n-> persoanaRepo.findOne(n.getOmInNevoie()).map(p->p.getOras().equals(oras)&&!p.getId().equals(id)).orElse(false)).toList();
    }

    public List<Nevoie> fapteBune(Long id)
    {
        List<Nevoie> nevoi = new ArrayList<Nevoie>();
        nevoieRepo.findAll().forEach(nevoi::add);
        return nevoi.stream().filter(n->n.getOmSalvator().equals(id)).toList();
    }

    public void addNevoie(String titlu, String descriere, LocalDateTime deadline,Long id)
    {
        nevoieRepo.addNeoie(new Nevoie(titlu,descriere,deadline,id));
        notifyObservers();
    }

    public void saleaza(Long id,Nevoie nevoie)
    {
        Nevoie n=nevoieRepo.findOne(nevoie.getId()).orElse(null);
        n.setOmSalvator(id);
        n.setStatus("Ajutat!");
        notifyObservers();
        nevoieRepo.update(n);

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

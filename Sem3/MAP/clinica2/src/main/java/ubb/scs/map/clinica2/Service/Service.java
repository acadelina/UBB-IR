package ubb.scs.map.clinica2.Service;

import ubb.scs.map.clinica2.Domain.Consultatie;
import ubb.scs.map.clinica2.Domain.Medic;
import ubb.scs.map.clinica2.Domain.Sectie;
import ubb.scs.map.clinica2.Repository.RepoConsultatie;
import ubb.scs.map.clinica2.Repository.RepoMedic;
import ubb.scs.map.clinica2.Repository.RepoSectie;
import ubb.scs.map.clinica2.Repository.Repository;
import ubb.scs.map.clinica2.observer.Observable;
import ubb.scs.map.clinica2.observer.Observer;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class Service implements Observable {

    List<Observer> observers=new ArrayList<>();
    RepoConsultatie repoConsultatie;
    RepoMedic repoMedic;
    RepoSectie repoSectie;

    public Service(RepoConsultatie repoConsultatie, RepoMedic repoMedic, RepoSectie repoSectie) {
        this.repoConsultatie = repoConsultatie;
        this.repoMedic = repoMedic;
        this.repoSectie = repoSectie;
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

    public List<Sectie> getSectii()
    {
        List<Sectie> sectii=new ArrayList<>();
        repoSectie.findAll().forEach(sectii::add);
        return sectii;
    }

    public List<Medic> getMedici()
    {
        List<Medic> medici=new ArrayList<>();
        repoMedic.findAll().forEach(medici::add);
        return medici;
    }

    public List<Consultatie> getConsultatii(Medic m)
    {
        List<Consultatie> consultati=new ArrayList<>();
        repoConsultatie.findAll().forEach(consultati::add);
        return consultati.stream().filter(c->c.getIdmedic().equals(m.getId())&&c.getData().isAfter(LocalDateTime.now())).sorted(Comparator.comparing(Consultatie::getData)).toList();
    }

    public List<Medic> getMediciSectie(Sectie s)
    {
        List<Medic> medici=new ArrayList<>();
        repoMedic.findAll().forEach(medici::add);
        return medici.stream().filter(m->m.getIdSectie().equals(s.getId())).toList();
    }

    public void addConsult(Consultatie c)
    {
        repoConsultatie.add(c);
        notifyObservers();
    }
}

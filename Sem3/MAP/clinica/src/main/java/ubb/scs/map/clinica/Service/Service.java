package ubb.scs.map.clinica.Service;

import ubb.scs.map.clinica.Domain.Pacient;
import ubb.scs.map.clinica.Domain.Pat;
import ubb.scs.map.clinica.Domain.TipPat;
import ubb.scs.map.clinica.Repository.RepoPacient;
import ubb.scs.map.clinica.Repository.RepoPat;
import ubb.scs.map.clinica.observer.Observable;
import ubb.scs.map.clinica.observer.Observer;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Service implements Observable {
    List<Observer> observers=new ArrayList<>();
    RepoPacient repoPacient;
    RepoPat repoPat;
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

    public Service(RepoPacient repoPacient, RepoPat repoPat) {
        this.repoPacient = repoPacient;
        this.repoPat = repoPat;
    }

    public Integer getPaturiLibere()
    {
        List<Pat> paturi=new ArrayList<>();
        repoPat.findAll().forEach(paturi::add);
        return Math.toIntExact(paturi.stream().filter(p -> p.getPacient() == 0).toList().size());

    }

    public Map<TipPat,List<String>> getPaturiOcupate()
    {

        List<Pat> paturi=new ArrayList<>();
        repoPat.findAll().forEach(paturi::add);
        return paturi.stream().filter(p->p.getPacient()!=0).collect(Collectors.groupingBy(Pat::getTipPat,Collectors.mapping(p->p.toString(),Collectors.toList())));
    }

    public List<Pacient> getPacienti()
    {
        List<Pacient> pacienti=new ArrayList<>();
        repoPacient.findAll().forEach(pacienti::add);
        List<Pat> paturi=new ArrayList<>();
        repoPat.findAll().forEach(paturi::add);
        return pacienti.stream().filter(p->{
            for(Pat pat:paturi)
                if(pat.getPacient().equals(p.getId()))
                    return false;
            return true;
        }).sorted((a,b)->b.getGravitate()-a.getGravitate()).collect(Collectors.toList());
    }

    public void updatePat(Pat pat) throws SQLException {
        repoPat.update(pat);
        notifyObservers();
    }

    public Pat gatPat(Integer id)
    {
        return repoPat.findOne(id).orElse(null);
    }
    public List<TipPat> gettipuri()
    {
        return List.of(TipPat.values());
    }

    public Pat verificTipPat(TipPat t)
    {
        List<Pat> paturi=new ArrayList<>();
        repoPat.findAll().forEach(paturi::add);
        return paturi.stream().filter(p->p.getTipPat().equals(t)&&p.getPacient()==0).findFirst().orElse(null);
    }
}

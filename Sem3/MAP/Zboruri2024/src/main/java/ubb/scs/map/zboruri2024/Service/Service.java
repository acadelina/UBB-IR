package ubb.scs.map.zboruri2024.Service;

import ubb.scs.map.zboruri2024.Domain.Flight;
import ubb.scs.map.zboruri2024.Domain.Ticket;
import ubb.scs.map.zboruri2024.Repository.RepoClient;
import ubb.scs.map.zboruri2024.Repository.RepoFlight;
import ubb.scs.map.zboruri2024.Repository.RepoTicket;
import ubb.scs.map.zboruri2024.observer.Observable;
import ubb.scs.map.zboruri2024.observer.Observer;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicReference;

public class Service implements Observable {
    RepoClient repoClient;
    RepoFlight repoFlight;
    RepoTicket repoTicket;
    List<Observer> observers= new ArrayList<>();

    public Service(RepoClient repoClient, RepoFlight repoFlight, RepoTicket repoTicket) {
        this.repoClient = repoClient;
        this.repoFlight = repoFlight;
        this.repoTicket = repoTicket;
    }

    public String numeDeUsername(String username)
    {
        AtomicReference<String> nume= new AtomicReference<>();
        repoClient.findAll().forEach(c->{
            if(c.getUsername().equals(username))
                nume.set(c.getName());
        });
        return nume.get();
    }

    public List<Ticket> bileteClient(String userame)
    {
        List<Ticket> tickets= new ArrayList<>();
        repoTicket.findAll().forEach(c->tickets.add(c));
        return tickets.stream().filter(t->t.getUsername().equals(userame)).toList();
    }

    public List<Flight> zboruriData(LocalDateTime date,String from,String to)
    {
        List<Flight> flights= new ArrayList<>();
        repoFlight.findAll().forEach(c->{flights.add(c);});
        return flights.stream()
                .filter(f->f.getFrom().equals(from)&&f.getTo().equals(to)&& f.getDeparture().toLocalDate().equals(date.toLocalDate())).toList();
    }

    public List<Ticket> zboruriDatad() {
        List<Ticket> flights = new ArrayList<>();
        repoTicket.findAll().forEach(flights::add);

        LocalDate targetDate = LocalDate.of(2025, 1, 18);

        return flights.stream()
                .filter(f -> f.getPurchaseTime().toLocalDate().equals(targetDate))
                .toList();
    }

    public List<String> fromUnic()
    {
        List<Flight> flights= new ArrayList<>();
        repoFlight.findAll().forEach(c->{flights.add(c);});
        return flights.stream().map(f->f.getFrom()).distinct().toList();
    }

    public List<String> toUnic()
    {
        List<Flight> flights= new ArrayList<>();
        repoFlight.findAll().forEach(c->{flights.add(c);});
        return flights.stream().map(f->f.getTo()).distinct().toList();
    }

    public void achizitieBilet(String username,Long idZbor)
    {
        Ticket ticket=new Ticket(username,idZbor,LocalDateTime.now());
        repoTicket.addTicket(ticket);
        removeSeats(idZbor);
        notifyObservers();
    }

    public Integer getSeats(Long idZbor)
    {
        Flight flight;
        flight = repoFlight.findOne(idZbor).orElse(null);
        AtomicReference<Integer> nrt= new AtomicReference<>(0);
        repoTicket.findAll().forEach(t->{
            if(t.getIdflight().equals(idZbor))
                nrt.updateAndGet(v -> v + 1);
        });
        return flight.getSeats()-nrt.get();
    }

    public void removeSeats(Long idZbor)
    {
        Flight flight;
        flight = repoFlight.findOne(idZbor).orElse(null);
        flight.setSeats(flight.getSeats()-1);
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
        observers.forEach(e->e.update());
    }
}

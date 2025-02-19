package ubb.scs.map.vacanta.Service;

import ubb.scs.map.vacanta.Domain.*;
import ubb.scs.map.vacanta.Repository.*;
import ubb.scs.map.vacanta.observer.Observable;
import ubb.scs.map.vacanta.observer.Observer;

import java.time.Instant;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Service implements Observable {
    @Override
    public void addObserver(Observer e) {

    }

    @Override
    public void removeObserver(Observer e) {

    }

    @Override
    public void notifyObservers() {

    }

    RepoClient repoClient;
    RepoHotel repoHotel;
    RepoLocation repoLocation;
    RepoSpecialOffer repoSpecialOffer;
    RepoReservation repoReservation;

    public Service(RepoClient repoClient, RepoHotel repoHotel, RepoLocation repoLocation, RepoSpecialOffer repoSpecialOffer,RepoReservation repoReservation) {
        this.repoClient = repoClient;
        this.repoHotel = repoHotel;
        this.repoLocation = repoLocation;
        this.repoSpecialOffer = repoSpecialOffer;
        this.repoReservation = repoReservation;
    }

    public List<Hotel> getHotelsByLocation(String location) {
        List<Location> locations=new ArrayList<>();
        repoLocation.findAll().forEach(locations::add);
        Location location1=locations.stream().filter(l->l.getLocation().equals(location)).findFirst().get();
        List<Hotel> hotels=new ArrayList<>();
        repoHotel.findAll().forEach(hotels::add);
        return hotels.stream().filter(h->h.getLocation().equals(location1.getId())).toList();
    }

    public List<Location> getLocations()
    {
        List<Location> locations=new ArrayList<>();
        repoLocation.findAll().forEach(locations::add);
        return locations;
    }

    public List<SpecialOffer> getSpecialOffers(Date start, Date end,Hotel hotel)
    {
        List<SpecialOffer> specialOffers=new ArrayList<>();
        repoSpecialOffer.findAll().forEach(specialOffers::add);

        return specialOffers.stream().filter(s->s.getStartDate().after(start) && s.getEndDate().before(end)&&s.getHotelid().equals(hotel.getId())).toList();

    }

    public List<SpecialOffer> offersForClient(Client client)
    {
        List<SpecialOffer> specialOffers=new ArrayList<>();
        repoSpecialOffer.findAll().forEach(specialOffers::add);

        return specialOffers.stream().filter(s->!s.getStartDate().before(Date.from(Instant.now()))&&s.getPercents()< client.getFidelitygrade()).toList();
    }

    public void addRes(Reservation reservation)
    {
        repoReservation.addReservation(reservation);
    }

    public Client getClient(Long id)
    {
      return  repoClient.findOne(id).orElse(null);
    }

}

package ubb.scs.map.trenuri.Service;

import ubb.scs.map.trenuri.Domain.City;
import ubb.scs.map.trenuri.Domain.TrainStation;
import ubb.scs.map.trenuri.Repository.RepoCity;
import ubb.scs.map.trenuri.Repository.RepoStation;
import ubb.scs.map.trenuri.observer.Observable;
import ubb.scs.map.trenuri.observer.Observer;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Service implements Observable {



    RepoCity repoCity;
    RepoStation repoStation;
    static final Float pricePerStation= 0.1F;
    List<Observer> observers = new ArrayList<>();




    public Service(RepoCity repoCity, RepoStation repoStation) {
        this.repoCity=repoCity;
        this.repoStation=repoStation;
    }

    public void changeSelection() {
        notifyObservers();
    }


    public List<String> getCities()
    {
        List<String> cities=new ArrayList<>();
        repoCity.findAll().forEach(c->cities.add(c.getName()));
        return cities;
    }

    public City getCity(String cityName)
    {
        List<City> cities=new ArrayList<>();
        repoCity.findAll().forEach(cities::add);
        return cities.stream().filter(c->c.getName().equals(cityName)).findFirst().get();
    }

    public List<List<TrainStation>> findRoutes(String startid, String endtid)
    {

        List<TrainStation> trainStations=new ArrayList<>();
        repoStation.findAll().forEach(trainStations::add);
        List<List<TrainStation>> allRoutes=new ArrayList<>();
        List<String> currentRoute=new ArrayList<>();
        currentRoute.add(startid);
        findRoutesRecursive(startid,endtid,currentRoute,allRoutes,trainStations,new ArrayList<>());
        return allRoutes;
    }

    private void findRoutesRecursive(
            String currentId,
            String endId,
            List<String > currentRoute,
            List<List<TrainStation>> allRoutes,
            List<TrainStation> trainStations,
            List<TrainStation> currentTrainStations) {

        if (Objects.equals(currentId, endId)) {
            allRoutes.add(new ArrayList<>(currentTrainStations));
            return;
        }


        for (TrainStation station : trainStations) {
            if (station.getDeparture().equals(currentId)) {
                String nextId = station.getDestination();


                if (!currentRoute.contains(nextId)) {
                    currentRoute.add(nextId);
                    currentTrainStations.add(station);


                    findRoutesRecursive(nextId, endId, currentRoute, allRoutes, trainStations, currentTrainStations);


                    currentRoute.removeLast();
                    currentTrainStations.removeLast();
                }
            }
        }
    }


    public List<List<TrainStation>> getDirectRoutes(String start,String end) {
        List<List<TrainStation>> allRoutes=findRoutes(start,end);
        return allRoutes.stream().filter(r->
        {
            TrainStation station1=r.getFirst();
            for(TrainStation station:r)
                if (!station1.getId().equals(station.getId()))
                    return false;
            return true;
        }).toList();

    }

    public List<String> getRotesStrings(List<List<TrainStation>> allRoutes) {

        return allRoutes.stream()
                .map(route -> {

                            String routeDescription = route.stream()
                                    .map(station -> {
                                        City departureCity = repoCity.findOne(station.getDeparture()).orElse(null);
                                        return departureCity.getName()+"--"+station.getId()  ;
                                    })
                                    .reduce((a, b) -> a + "-->" + b)
                                    .orElse("");

                            double totalPrice = pricePerStation * route.size();


                            return routeDescription+"-->"+repoCity.findOne(route.getLast().getDestination()).orElse(null).getName() + " | Total Price: " + totalPrice + " RON";
                        })

                .toList();
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

package ubb.scs.map.comenzi.Service;

import ubb.scs.map.comenzi.Domain.MenuItem;
import ubb.scs.map.comenzi.Domain.Order;
import ubb.scs.map.comenzi.Domain.OrderStatus;
import ubb.scs.map.comenzi.Domain.Table;
import ubb.scs.map.comenzi.Repository.OrderRepo;
import ubb.scs.map.comenzi.Repository.RepoMenu;
import ubb.scs.map.comenzi.Repository.TableRepo;
import ubb.scs.map.comenzi.observer.Observable;
import ubb.scs.map.comenzi.observer.Observer;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Service implements Observable {
    RepoMenu repoMenu;
    TableRepo tableRepo;
    OrderRepo orderRepo;
    List<Observer> observers=new ArrayList<>();
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

    public Service(RepoMenu repoMenu,TableRepo tableRepo,OrderRepo orderRepo) {
        this.repoMenu=repoMenu;
        this.tableRepo=tableRepo;
        this.orderRepo=orderRepo;
    }

    public Map<String,List<MenuItem>> categorii()
    {
        List<MenuItem> list=new ArrayList<>();
        repoMenu.findAll().forEach(l-> list.add(l));
        Map<String,List<MenuItem>> map=list.stream().collect(Collectors.groupingBy(MenuItem::getCategory));
        return map;
    }

    public List<Table> getTables()
    {
        List<Table> list=new ArrayList<>();
        tableRepo.findAll().forEach(l-> list.add(l));
        return list;
    }

    public void placeOrder(Integer table, List<Integer> items, LocalDateTime date)
    {
        Order order=new Order(table,items,date,OrderStatus.PLACED);
        orderRepo.addOrder(order);
        notifyObservers();
    }

    public List<Order> getOrders()
    {
        List<Order> list=new ArrayList<>();
        orderRepo.findAll().forEach(l-> list.add(l));
        //return list;
        return list.stream().sorted((o1, o2) -> o2.getDate().compareTo(o1.getDate())).collect(Collectors.toList());
    }
}

package ubb.scs.map.demo3.utils.observer;


import ubb.scs.map.demo3.utils.events.Event;

public interface Observable<E extends Event> {
    void addObserver(Observer<E> e);
    void removeObserver(Observer<E> e);
    void notifyObservers(E t);
}

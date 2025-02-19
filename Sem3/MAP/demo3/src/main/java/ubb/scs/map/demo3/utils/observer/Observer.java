package ubb.scs.map.demo3.utils.observer;


import ubb.scs.map.demo3.utils.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}
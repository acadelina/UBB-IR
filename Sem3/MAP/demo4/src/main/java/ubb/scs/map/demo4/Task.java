package ubb.scs.map.demo4;

import java.util.Random;

public class Task implements Runnable {
    @Override
    public void run() {
        System.out.println(Thread.currentThread().getName() + " is running");
        Random rand = new Random();
        try {
            Thread.sleep((long) (Math.random()*3000));
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}

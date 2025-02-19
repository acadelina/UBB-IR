package ubb.scs.map.demo4;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Starter {
    public static void main(String[] args) throws InterruptedException {
        MyThread myThread = new MyThread();
        Thread thread = new Thread(myThread);
        thread.start();
        MyThread2 thread2 = new MyThread2();
        MyThread2 thread3 = new MyThread2();
        MyThread2 thread4 = new MyThread2();
        Thread thread5 = new Thread(thread2);
        Thread thread6=new Thread(thread3);
        Thread thread7 = new Thread(thread4);
//        thread5.start();
//        thread6.start();
//        thread7.start();


        Counter counter = new Counter();
        Thread thread1 = new Thread(()->{
            for(int i=1;i<=1000;i++)
                counter.increment();
        });

        Thread thread8 = new Thread(()->{
            for(int i=1;i<=1000;i++)
                counter.increment();
        });

        thread1.start();
        thread8.start();
        thread1.join();
        thread8.join();
        System.out.println(counter.getCount());

        ExecutorService executorService= Executors.newFixedThreadPool(5);
        for(int i=0;i<5;i++)
        {
            Runnable runnable = new Task();
            executorService.execute(runnable);
        }
        executorService.shutdown();
    }
}

package ubb.scs.map;

import java.util.ArrayList;
import java.util.List;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        List<String> list=new ArrayList<String>();
        list.add("ana");
        list.add("apple");
        list.add("orange");
        list.add("bANana");

        list=list.stream()
                .map(String::toUpperCase)
                .toList();
        list.stream().forEach(c->System.out.println(c));

        List<Dog> dogList=new ArrayList<>();
        dogList.add(new Dog("rex",5));
        dogList.add(new Dog("otto",6));
        dogList.add(new Dog("pufi",10));
        dogList.add(new Dog("albi",2));
        dogList.add(new Dog("rex",11));
        dogList.add(new Dog("Sam",12));

        dogList.stream()
                .filter(d->d.getAge()>10)
                .forEach(d->System.out.println(d.toString()));

        System.out.println("A doua cerinta:");
        dogList.stream()
                .sorted((d1,d2)->d2.getAge()-d1.getAge())
                .forEach(d->System.out.println(d.toString()));


        System.out.println("A treia cerinta:");
        dogList.stream()
                .filter(d->d.getName().equals("Sam"))
                .forEach(d->System.out.println(d.toString()));

        System.out.println("A patra cerinta");
        dogList.stream().forEach(d->System.out.println(d.getName()));

        List<Integer> intList=new ArrayList<>();
        intList.add(1);
        intList.add(2);
        intList.add(3);
        intList.add(4);
        intList.add(5);

        intList.stream()
                .map(i->i*i);
        intList.stream()
                .forEach(i->System.out.println(i));

        List<Mall> mallList=new ArrayList<>();
        mallList.add(new Mall("mall1","man1",1900,234.5));
        mallList.add(new Mall("mall2","man2",1903,237.5));
        mallList.add(new Mall("mall3","man3",1960,1234.5));
        mallList.add(new Mall("mall4","man4",1990,4234.5));

        mallList.stream()
                .map(mall->{
                     mall.setProfit(mall.getProfit()*3);
                    return mall;
                })
                .sorted((m1,m2)-> (int) (m2.getProfit()- m1.getProfit()))
                .findFirst().ifPresent(m->System.out.println(m.toString()));

    }
}
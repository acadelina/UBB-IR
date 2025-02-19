import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        List<Circle> list = new ArrayList<Circle>();
        double radius=Math.random();
        while(radius>=0.01)
        {
            list.add(new Circle(radius));
            radius=Math.random();
        }

        for(int i=0;i<list.size();i++)
        {
            radius=list.get(i).getRadius();
            System.out.println(radius*radius*Math.PI+"\n");
        }

        MyMap map=new MyMap();
        map.put("a1234","Steve Jobs");
        map.put("a1235","Scott McNealy");
        map.put("a1236","Jeff Bezos");
        map.put("A1237","Larry Ellison");
        map.put("a1238","Bill Gates");



        for(String key:map.get().keySet())
            System.out.println(key+"="+map.get().get(key));
    }
}
import java.util.*;

public class MyMap  {
   private TreeMap<Integer, List<Student>> StudentsMap;
   //nu putem folosi un tip primitiv

    public MyMap() {
        StudentsMap = new TreeMap<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return -o1.compareTo(o2);
            }
        });
    }

    public void add(Student st)
    {
        int medie=Math.round(st.getMedia());
        List<Student> lista=StudentsMap.get(medie);
        if(lista==null) {
            lista = new ArrayList<>();
            lista.add(st);
            StudentsMap.put(medie, lista);
        }
        else
            lista.add(st);
    }

    public Set<Map.Entry<Integer,List<Student>>> getEntries()
    {
        return StudentsMap.entrySet();
    }

}

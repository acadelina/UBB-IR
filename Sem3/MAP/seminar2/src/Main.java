import java.util.*;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        //TIP Press <shortcut actionId="ShowIntentionActions"/> with your caret at the highlighted text
        // to see how IntelliJ IDEA suggests fixing it.
        Student s1=new Student("Dan",4.5f);
        Student s2=new Student("Ana",8.5f);
        Student s3=new Student("Dan",4.5f);
        Student s4=new Student("Dan",7.5f);

        Set<Student> studList=new HashSet<>();
        studList.add(s1);
        studList.add(s2);
        studList.add(s3);
        studList.add(s4);

        for(Student s:studList){
            System.out.println(s);
        }

        Set<Student> studList2=new TreeSet<>(new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return o1.compareTo(o2);
            }
        });
        studList2.add(s1);
        studList2.add(s2);
        studList2.add(s3);
        studList2.add(s4);
        for(Student s:studList2){
            System.out.println(s);
        }
        MyMap myMap=new MyMap();
        for(Student s:getList()){
            myMap.add(s);
        }
        for(var entry: myMap.getEntries()){
            System.out.println("Studentii cu media "+ entry.getKey()+" sunt: ");
            Set<Student> studenti=new TreeSet<>();
            for( Student s:entry.getValue())
            {
             studenti.add(s);
            }
            for(Student s:studenti)
            {
                System.out.println(s);
            }

        }
        System.out.println("Ok");

        Repository<Long,Student> repo=new InMemRepo<>();
        long id=0;
        for(var s:getList()) {
            s.setId(id);
            repo.save(s);
            id++;
        }
        System.out.println("ok");

        }

    public static List<Student> getList(){
        List<Student> l=new ArrayList<Student>();
        l.add(new Student("1",9.7f));
        l.add(new Student("2",7.3f));
        l.add(new Student("3",6f));
        l.add(new Student("4",6.9f));
        l.add(new Student("5",9.5f));
        l.add(new Student("6",9.9f));
        return l;
    }

}
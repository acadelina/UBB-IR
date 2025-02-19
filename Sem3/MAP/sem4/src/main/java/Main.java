import java.util.List;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.stream.Stream;

//import static java.lang.StringUTF16.toUpperCase;


//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        Predicate<String> lungimePara= s->s.length()%2==0;
        Predicate<String> incepeP=s->{
            if(s.indexOf('p')==0)
                return true;
            return false;
        };
        List<String> lista= List.of("pabc","abcd","asne","paieddw");
        afiseazaCriteriu(lista, lungimePara);
        afiseazaCriteriu(lista, incepeP);
        Function<String,Integer> converterLambda=x->Integer.valueOf(x);
        System.out.println(converterLambda.apply("12"));
        Function<String,Integer> converterMethodReference= Integer::valueOf;
        Function<String,String> converterPasareasca=x->{
            String rez="";
            Predicate<Character> vocala=p->{
                if("aeiou".contains(String.valueOf(p)))
                    return true;
                return false;
            };
            for(int i=0;i<x.length();i++) {
                if (vocala.test(x.charAt(i)))
                    rez = rez + x.charAt(i) + 'p';
                rez += x.charAt(i);
            }
            return rez;
        };
        System.out.println(converterPasareasca.apply("Mama merge la piata"));

        Supplier<Cerc> converterLambda2=()->new Cerc();


        List<String> lista2=List.of("asd","bce","asc","bcr","cc");
        Stream<String> stream=lista2.stream();
        stream.
                filter(x->{
                    System.out.println(x);
                    return x.startsWith("b");
                })
                .map(x->{
                    System.out.println(x);
                    return x.toUpperCase();
                })
                .forEach(System.out::println);

        List<Integer> intregi=List.of(1,2,3,4,5,6,7,8,9,10);
        Stream<Integer> streamInt=intregi.stream();
        streamInt.reduce(
                (x,y)->{
                    return x+y;
                }
        )
                .ifPresent(System.out::println);

    }

    public static <E> void afiseazaCriteriu(List<E> l,Predicate<E> p) {
        l.forEach(x->{
            if(p.test(x))
                System.out.println(x);
        });
    }





}
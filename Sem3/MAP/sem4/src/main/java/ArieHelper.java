import org.w3c.dom.ls.LSOutput;

import java.util.ArrayList;
import java.util.List;

public class ArieHelper{
    public static void main(String[] args) {
        List<Patrat> listPat=List.of(new Patrat(2),new Patrat(4));
        List<Cerc> listCerc=List.of(new Cerc(5),new Cerc(6));
//        Arie<Patrat> aria1=x->x.getLat()*x.getLat();
//        Arie<Cerc> aria2=x->x.getRaza()*x.getRaza()*Math.PI;
//        listCerc.forEach(x->System.out.println(aria2.calcul(x)));
//        listPat.forEach(x->System.out.println(aria1.calcul(x)));

        Arie<Patrat> aria1=ArieHelper::ariePatrat;
        Arie<Cerc> aria2=ArieHelper::arieCerc;

        listCerc.forEach(x->System.out.println(aria2.calcul(x)));
        listPat.forEach(x->System.out.println(aria1.calcul(x)));
    }
    public static double ariePatrat(Patrat p)
    {
        return p.getLat()*p.getLat();
    }
    public static double arieCerc(Cerc c)
    {
        return c.getRaza()*c.getRaza()*Math.PI;
    }
}


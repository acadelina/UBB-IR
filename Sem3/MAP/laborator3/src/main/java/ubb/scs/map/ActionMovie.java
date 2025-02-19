package ubb.scs.map;

public class ActionMovie extends Movie{
    boolean isThriller = false;

    public ActionMovie(String name, Integer year, boolean isThriller) {
        super(name, year);
        this.isThriller = isThriller;
    }
}

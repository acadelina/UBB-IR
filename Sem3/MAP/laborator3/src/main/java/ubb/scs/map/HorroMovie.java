package ubb.scs.map;

public class HorroMovie extends Movie{
    String intensityFear;

    public HorroMovie(String name, Integer year,String intensityFear) {
        super(name, year);
        this.intensityFear = intensityFear;
    }
}

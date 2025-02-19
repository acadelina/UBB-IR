package ubb.scs.map;

public class Movie {
    String name;
    Integer year;

    public Movie(String name, Integer year) {
        this.name = name;
        this.year = year;
    }
    public  String toString()
    {
        return name + " " + year;
    }
}

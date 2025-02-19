package ubb.scs.map;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
    List<Movie> movies = new ArrayList<Movie>();
    movies.add(new ActionMovie("ActionMovie",1900,true));
    movies.add(new HorroMovie("HMovie",1910,"3"));
    movies.add(new HorroMovie("HoMovie",1902,"4"));

    for(Movie movie : movies)
        if( movie instanceof HorroMovie )
            System.out.println(((HorroMovie)movie).toString());

    //File file= new File("./resources/text.txt");
    List<String> lines=new ArrayList<>();
    try(BufferedReader reader=new BufferedReader(new FileReader("src/main/resources/text.txt")))
    {
        //BufferedReader reader=new BufferedReader(new FileReader("src/main/resources/text.txt"));
        String line;
        while (true) {
            try {
                if (!((line = reader.readLine()) != null)) break;
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            lines.add(line);
        }
    } catch(FileNotFoundException e){
        throw new RuntimeException(e);
    } catch(IOException e){
        throw new RuntimeException(e);
    }

    for(String line : lines)
    {
        String[] words=line.split(" ");
        for(String word : words)
            if(word.equals("test"))
                System.out.println(line);
    }

        List<String> words=new ArrayList<>();
        try(BufferedReader reader=new BufferedReader(new FileReader("src/main/resources/cuvinte.txt")))
        {
            //BufferedReader reader=new BufferedReader(new FileReader("src/main/resources/cuvinte.txt"));
            String line;
            while (true) {
                try {
                    if (!((line = reader.readLine()) != null)) break;
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
                words.add(line);
            }
        } catch(FileNotFoundException e){
            throw new RuntimeException(e);
        } catch(IOException e){
            throw new RuntimeException(e);
        }

        String wordMax="";
        Integer Max=0;
        for(String word: words)
            if(word.length()>Max)
            {
                Max=word.length();
                wordMax=word;
            }
        System.out.println(wordMax);

        List<String> random=new ArrayList<>();
        for(int i=0;i<7;i++)
            random.add(String.valueOf(Math.random()));
        try(BufferedWriter bw=new BufferedWriter(new FileWriter("src/main/resources/output.txt")))
        {
                bw.write(String.join(" ",random));

        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }
}

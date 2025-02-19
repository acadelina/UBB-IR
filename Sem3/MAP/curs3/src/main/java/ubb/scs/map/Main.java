package ubb.scs.map;

import ubb.scs.map.domain.Utilizator;
import ubb.scs.map.domain.validators.UtilizatorValidator;
import ubb.scs.map.domain.validators.ValidationException;
import ubb.scs.map.domain.validators.Validator;
import ubb.scs.map.repository.Repository;
import ubb.scs.map.repository.file.UtilizatorRepository;
import ubb.scs.map.repository.memory.InMemoryRepository;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {

        Repository<Long, Utilizator> repo = new InMemoryRepository<Long, Utilizator>(new UtilizatorValidator());
        Repository<Long, Utilizator> repoFile = new UtilizatorRepository(new UtilizatorValidator(), "./data/utilizatori.txt");
        Utilizator u1 = new Utilizator("AlexiaUp", "c");
        Utilizator u2 = new Utilizator("Marius", "h");
        Utilizator u3 = null;
        u1.setId(3L);
        u2.setId(7L);
        //u3.setId(5L);
//        try {
//            repoFile.save(u1);
//            repoFile.save(u2);
//            repoFile.save(u3);
//        }catch(IllegalArgumentException e)
//        {
//            System.out.println(e.getMessage());
//        }catch(ValidationException e)
//        {
//            System.out.println(e.getMessage());
//        }

        try{
            repoFile.update(u1);
            repoFile.update(u2);
        }
        catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
        }
        catch(ValidationException e){
            System.out.println(e.getMessage());
        }
        System.out.println();

    }
}
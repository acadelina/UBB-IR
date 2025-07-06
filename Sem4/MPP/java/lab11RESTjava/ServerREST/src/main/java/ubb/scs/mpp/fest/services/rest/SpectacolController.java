package ubb.scs.mpp.fest.services.rest;

import jakarta.servlet.http.HttpServletRequest;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import ubb.scs.mpp.Repository.RepoException;
import ubb.scs.mpp.Repository.SpectacolRepository;
import ubb.scs.mpp.model.Spectacol;
import ubb.scs.mpp.model.SpectacolDTO;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.stream.StreamSupport;

@CrossOrigin
@RestController
@RequestMapping("/festival/spectacole")
public class SpectacolController {
    private static final String template = "Hello, %s!";

    @Autowired
    private SpectacolRepository spectacolRepository;

    @Autowired
    private HttpServletRequest request;

    private void validateJwt() {
        String authHeader = request.getHeader("Authorization");
        if (authHeader == null || !authHeader.startsWith("Bearer ")) {
            throw new RuntimeException("Missing or invalid Authorization header");
        }
        String token = authHeader.substring(7);
        JwtUtils.validateToken(token);
    }

    @RequestMapping("/greeting")
    public  String greeting(@RequestParam(value="name", defaultValue="World") String name) {
        return String.format(template, name);
    }


    @RequestMapping( method= RequestMethod.GET)
    public Spectacol[] getAll(){
        validateJwt();
        System.out.println("Get all shows ...");
        try {
            return StreamSupport.stream(spectacolRepository.findAll().spliterator(),false).toArray(Spectacol[]::new);
        } catch (RepoException e) {
            throw new RuntimeException(e);
        }
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public ResponseEntity<?> getById(@PathVariable Long id) throws RepoException {
        validateJwt();
        System.out.println("Get by id "+id);
        Spectacol spectacol=spectacolRepository.findOne(id);
        if (spectacol==null)
            return new ResponseEntity<>("Spectacol not found",HttpStatus.NOT_FOUND);
        SpectacolDTO spectacolDTO=new SpectacolDTO();
        spectacolDTO.setId(spectacol.getId().toString());
        spectacolDTO.setArtist(spectacol.getArtist());
        spectacolDTO.setData(spectacol.getData().toString());
        spectacolDTO.setLocation(spectacol.getLocation());
        spectacolDTO.setAvailable_seats(spectacol.getAvailable_seats().toString());
        spectacolDTO.setSold_seats(spectacol.getSold_seats().toString());

        return new ResponseEntity<>(spectacolDTO, HttpStatus.OK);
    }

    @RequestMapping(method = RequestMethod.POST)
    public SpectacolDTO create(@RequestBody SpectacolDTO spectacol) throws RepoException {
        validateJwt();
        LocalDateTime dateTime=LocalDateTime.parse(spectacol.getData(), DateTimeFormatter.ISO_DATE_TIME);
        Spectacol newSpec=new Spectacol(spectacol.getArtist(),dateTime,spectacol.getLocation(),Integer.parseInt(spectacol.getAvailable_seats()),Integer.parseInt(spectacol.getSold_seats()));
        newSpec=spectacolRepository.save(newSpec);
        spectacol.setId(newSpec.getId().toString());
        return spectacol;
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.PUT)
    public ResponseEntity<?> update(@RequestBody SpectacolDTO spectacol, @PathVariable Long id) throws RepoException {
        validateJwt();
        System.out.println("Updating spectacol ...");
        try {
            Spectacol spec = spectacolRepository.findOne(id);
            if (spec == null)
                return new ResponseEntity<>("Spectacol not found", HttpStatus.NOT_FOUND);
            else {
                spec.setArtist(spectacol.getArtist());
                spec.setData(LocalDateTime.parse(spectacol.getData(), DateTimeFormatter.ISO_DATE_TIME));
                spec.setLocation(spectacol.getLocation());
                spec.setAvailable_seats(Integer.parseInt(spectacol.getAvailable_seats()));
                spec.setSold_seats(Integer.parseInt(spectacol.getSold_seats()));
                spectacolRepository.update(spec);
                return new ResponseEntity<>(spectacol, HttpStatus.OK);
            }
        }catch (RepoException e) {
            return new ResponseEntity<>(e.getMessage(), HttpStatus.BAD_REQUEST);
        }

    }

    @RequestMapping(value="/{id}", method= RequestMethod.DELETE)
    public ResponseEntity<?> delete(@PathVariable Long id){
        validateJwt();
        System.out.println("Deleting spectacol with id: ... "+id);
        try {
            Spectacol spec = spectacolRepository.findOne(id);
            if (spec == null)
                return new ResponseEntity<>("Spectacol not found", HttpStatus.NOT_FOUND);
            else{
                spec=spectacolRepository.delete(id);
                return new ResponseEntity<Spectacol>(HttpStatus.OK);
            }
        }catch (RepoException ex){
            System.out.println("Ctrl Delete user exception");
            return new ResponseEntity<>(ex.getMessage(),HttpStatus.BAD_REQUEST);
        }
    }




    @ExceptionHandler(RepoException.class)
    @ResponseStatus(HttpStatus.BAD_REQUEST)
    public String userError(RepoException e) {
        return e.getMessage();
    }
}

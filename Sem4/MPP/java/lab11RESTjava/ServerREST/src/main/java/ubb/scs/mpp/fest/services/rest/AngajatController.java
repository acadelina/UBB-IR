package ubb.scs.mpp.fest.services.rest;

import io.jsonwebtoken.Jwts;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import ubb.scs.mpp.Repository.AngajatRepository;
import ubb.scs.mpp.Repository.RepoException;
import ubb.scs.mpp.model.Angajat;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

import java.sql.SQLException;
import java.util.Date;

@RestController
@RequestMapping("/api/login")
public class AngajatController {
    private static final long EXPIRATION_TIME=360000;
    private static BCryptPasswordEncoder encoder = new BCryptPasswordEncoder();

    @Autowired
    private AngajatRepository angajatRepository;

    public static String generateToken(String username) {
        String token =  Jwts.builder()
                .subject(username)
                .expiration(new Date(System.currentTimeMillis() + EXPIRATION_TIME))
                .signWith(JwtUtils.getKEY(), Jwts.SIG.HS512)
                .compact()
                .trim();
        System.out.println(token);
        return token;
    }

    @CrossOrigin(origins = "http://localhost:8081")
    @PostMapping
    public ResponseEntity<?> login(@RequestBody LoginRequest request) {
        System.out.println(request);
        try {
            Angajat angajat = angajatRepository.findByUsername(request.username());
            if (angajat == null) {
                return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body("Username invalid");
            }

            if (!encoder.matches(request.password(), angajat.getPassword())) {
                return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body("Parolă greșită");
            }

            String token = generateToken(request.username());
            return ResponseEntity.ok(token);

        } catch (SQLException e) {
            throw new RuntimeException(e);
        } catch (RepoException e) {
            throw new RuntimeException(e);
        }
    }
}

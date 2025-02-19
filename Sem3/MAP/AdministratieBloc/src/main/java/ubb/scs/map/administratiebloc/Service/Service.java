package ubb.scs.map.administratiebloc.Service;

import ubb.scs.map.administratiebloc.Domain.*;
import ubb.scs.map.administratiebloc.Repository.*;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.Period;
import java.time.ZoneId;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.AtomicReference;
import java.util.stream.Collectors;

public class Service {
    AdreseRepo adreseRepo;
    AdministratorRepo administratorRepo;
    ApartamenteRepo apartamenteRepo;
    BlocRepo blocRepo;
    ChiriasRepo chiriasRepo;
    LocatariRepo locatariRepo;
    PersoanaRepo persoanaRepo;

    public Service(AdreseRepo adreseRepo, AdministratorRepo administratorRepo, ApartamenteRepo apartamenteRepo, BlocRepo blocRepo, ChiriasRepo chiriasRepo, LocatariRepo locatariRepo, PersoanaRepo persoanaRepo) {
        this.adreseRepo = adreseRepo;
        this.administratorRepo = administratorRepo;
        this.apartamenteRepo = apartamenteRepo;
        this.blocRepo = blocRepo;
        this.chiriasRepo = chiriasRepo;
        this.locatariRepo = locatariRepo;
        this.persoanaRepo = persoanaRepo;
    }

    public boolean apartineBloc(Long idap,Bloc bloc)
    {
       return bloc.getApartamente().stream()
                .anyMatch(apartamente -> apartamente.getId().equals(idap));
    }
    public Map<Bloc,Double> nrMediu()
    {
        Map<Bloc,Double> medii;
        List<Bloc> blocuri=new ArrayList<>();
        blocRepo.findAll().forEach(b->blocuri.add(b));
        medii=blocuri.stream().collect(Collectors.toMap(
                bloc->bloc,
                bloc->{
                    long totalLoc=bloc.getApartamente().stream().filter(ap->apartineBloc(ap.getId(),bloc)).count();

                    long totalap=bloc.getApartamente().size();

                    return totalap==0?0:(double)totalLoc/totalap;
                }
        ));
        return medii;
    }

    public List<Locatar> getOameniBloc(Bloc bloc)
    {
        List<Locatar> chiriasi=new ArrayList<>();
        locatariRepo.findAll().forEach(e-> chiriasi.add(e));

        List<Locatar> loc=chiriasi.stream().filter(c->apartineBloc(c.getApartament(),bloc)).collect(Collectors.toList());
        return loc;
    }

    public boolean esteChirias(Locatar loc)
    {
        List<Chirias> chiriasi=new ArrayList<>();
        chiriasRepo.findAll().forEach(e-> chiriasi.add(e));
        return  chiriasi.stream().anyMatch(l->l.getId().equals(loc.getId()));

    }

    public boolean peste25(Chirias ch)
    {
        LocalDate dataNasterii = ch.getDataNasterii().toInstant()
                .atZone(ZoneId.systemDefault())
                .toLocalDate();
        return Period.between(dataNasterii,LocalDate.now()).getYears()>=25;
    }

    public boolean tipAp(Long id)
    {
        Apartament ap=apartamenteRepo.findOne(id).isPresent()?apartamenteRepo.findOne(id).get():null;
        return ap.getTipApartament().equals(TipApartament.semidecomandat);
    }

    public List<Chirias> getChiriasi(Bloc bloc)
    {
        List<Chirias> chiriasi=new ArrayList<>();
        chiriasRepo.findAll().forEach(e-> chiriasi.add(e));

        List<Chirias> loc=chiriasi.stream().filter(c->apartineBloc(c.getApartament(),bloc)&& peste25(c)&& tipAp(c.getApartament())).collect(Collectors.toList());
        return loc;
    }

    public Bloc getBloc(Long id)
    {
        return blocRepo.findOne(id).isPresent()?blocRepo.findOne(id).get():null;
    }

    public String getAp(Chirias ch){
        Apartament ap= apartamenteRepo.findOne(ch.getApartament()).isPresent()?apartamenteRepo.findOne(ch.getApartament()).get():null;
        return ap.getNr_apartamente().toString();
    }

}

package ubb.scs.mpp.Network.protobuf;

import ubb.scs.mpp.model.Angajat;
import ubb.scs.mpp.model.Bilet;
import ubb.scs.mpp.model.Spectacol;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Date;

public class ProtoUtils {
    public static BileteProtobufs.Request createLoginRequest(Angajat user){
        BileteProtobufs.Angajat userDTO=BileteProtobufs.Angajat.newBuilder().setPassword(user.getPassword()).setUsername(user.getUsername()).build();
        BileteProtobufs.Request request= BileteProtobufs.Request.newBuilder().setType(BileteProtobufs.Request.Type.Login)
                .setAngajat(userDTO).build();
        return request;
    }
    public static BileteProtobufs.Request createLogoutRequest(Angajat user){
        BileteProtobufs.Angajat userDTO=BileteProtobufs.Angajat.newBuilder().setId(user.getId()).build();
        BileteProtobufs.Request request= BileteProtobufs.Request.newBuilder().setType(BileteProtobufs.Request.Type.Logout)
                .setAngajat(userDTO).build();
        return request;
    }
    public static BileteProtobufs.Request createGetShowsRequest(){
        BileteProtobufs.Request request= BileteProtobufs.Request.newBuilder().setType(BileteProtobufs.Request.Type.GetShows)
                .build();
        return request;
    }
    public static BileteProtobufs.Request createGetFShowsRequest(Date date){
        String data=date.toInstant()
                .atZone(ZoneId.systemDefault())
                .toLocalDate()
                .toString(); ;
        BileteProtobufs.Request request= BileteProtobufs.Request.newBuilder().setType(BileteProtobufs.Request.Type.GetFShows)
                .setData(data).build();
        return request;
    }

    public static BileteProtobufs.Request createAddBiletRequest(Bilet bilet){
        BileteProtobufs.Bilet biletDTO=BileteProtobufs.Bilet.newBuilder().setBuyer(bilet.getBuyer()).setSeatsNumber(bilet.getSeats_number()).setSpectacol(getSpectacol(bilet)).build();
        BileteProtobufs.Request request= BileteProtobufs.Request.newBuilder().setType(BileteProtobufs.Request.Type.BuyTicket)
                .setBilet(biletDTO).build();
        return request;
    }

    public static BileteProtobufs.Spectacol getSpectacol(Bilet bilet){
        return BileteProtobufs.Spectacol.newBuilder().setId(bilet.getSpectacol().getId()).setArtist(bilet.getSpectacol().getArtist()).setDate(bilet.getSpectacol().getDate().toString()).setLocation(bilet.getSpectacol().getLocation()).setAvailableSeats(bilet.getSpectacol().getAvailable_seats()).setSoldSeats(bilet.getSpectacol().getSold_seats()).build();
    }


    public static String getError(BileteProtobufs.TicketResponse response){
        String errorMessage=response.getError();
        return errorMessage;
    }

    public static Angajat getUser(BileteProtobufs.TicketResponse response){
        Angajat user=new Angajat(response.getAngajat().getUsername(),response.getAngajat().getPassword(),response.getAngajat().getMail());
        user.setId(response.getAngajat().getId());
        return user;
    }

    public static Spectacol getSpectacol(BileteProtobufs.TicketResponse response){
        Spectacol spectacol=new Spectacol(response.getSpectacol().getArtist(), LocalDateTime.parse(response.getSpectacol().getDate()),response.getSpectacol().getLocation(),response.getSpectacol().getAvailableSeats(),response.getSpectacol().getSoldSeats());
        spectacol.setId(response.getSpectacol().getId());
        return spectacol;
    }


    public static Spectacol[] getSpectacole(BileteProtobufs.TicketResponse response){
        Spectacol[] specs=new Spectacol[response.getShowsCount()];
        for(int i=0;i<response.getShowsCount();i++){
            BileteProtobufs.Spectacol specDTO=response.getShows(i);
            Spectacol spec=new Spectacol(specDTO.getArtist(),LocalDateTime.parse(specDTO.getDate()),specDTO.getLocation(),specDTO.getAvailableSeats(),specDTO.getSoldSeats());
            spec.setId(specDTO.getId());
            specs[i]=spec;
        }
        return specs;
    }


}

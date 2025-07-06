using System.Reflection.Metadata;
using Ubb.Scs.Mpp.Network;
using Angajat = Domain.Angajat;

namespace Protobuf;

public class ProtoUtils
{
    
    public static TicketResponse createOkResponse()
    {
        TicketResponse response = new TicketResponse
        {
            Type = TicketResponse.Types.Type.Ok,
        };
        return response;
    }


    public static TicketResponse createErrorResponse(String text)
    {
        TicketResponse response = new TicketResponse
        {
            Type = TicketResponse.Types.Type.Error,
            Error = text,
        };
        return response;
    }

 
    public static TicketResponse createGetSpectacoleResponse(Domain.Spectacol[] spectacols)
    {
        Spectacol[] spectacolArray = new Spectacol[spectacols.Length];
        int i = 0;
        foreach (Domain.Spectacol spectacol in spectacols)
        {
            Ubb.Scs.Mpp.Network.Spectacol specDTO = new Spectacol
            {
                Id = spectacol.Id,
                Artist = spectacol.Artist,
                Location = spectacol.Location,
                AvailableSeats = spectacol.AvailableSeats,
                SoldSeats = spectacol.SoldSeats,
                Date = (spectacol.Date).ToString("yyyy-MM-ddTHH:mm:ss"),
            };
            spectacolArray[i++]=specDTO;
        }

        TicketResponse response = new TicketResponse
        {
            Type = TicketResponse.Types.Type.ShowList,
            Shows =  {spectacolArray }
        };


        return response;
    }


  
    public static Domain.Spectacol getSpectacol(Spectacol spectacol)
    {
        Domain.Spectacol spectacold = new Domain.Spectacol(spectacol.Artist,
            DateTime.Parse(spectacol.Date), spectacol.Location,
            spectacol.AvailableSeats, spectacol.SoldSeats);
        spectacold.Id= spectacol.Id;
        return spectacold;
    }

    public static Domain.Angajat getUser(Request request)
    {
        Domain.Angajat user = new Domain.Angajat(request.Angajat.Username, request.Angajat.Password, request.Angajat.Mail);
        user.Id = request.Angajat.Id;
        return user;
    }

    public static Domain.Bilet getBilet(Request request)
    {
        Domain.Bilet bilet =
            new Domain.Bilet(request.Bilet.Buyer, request.Bilet.SeatsNumber, getSpectacol(request.Bilet.Spectacol));
        bilet.Id = request.Bilet.Id;
        return bilet;
    }

    public static TicketResponse createUpdateBiletResponse(Spectacol spectacol)
    {
        return new TicketResponse()
        {
            Type = TicketResponse.Types.Type.NewTicket,
            Spectacol = spectacol,
        };
    }
    
    public static TicketResponse createAddBiletResponse()
    {
        return new TicketResponse()
        {
            Type = TicketResponse.Types.Type.Ok
        };
    }
    
}
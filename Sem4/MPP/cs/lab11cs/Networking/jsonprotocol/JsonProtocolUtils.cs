using System.Collections.Immutable;
using Domain;
using Networking.dto;

namespace Networking.jsonprotocol;

public class JsonProtocolUtils
{
    public static Response CreateLoginResponse(AngajatDTO angajatDTO)
    {
        return new Response{Type=ResponseType.LOGIN,Angajat=angajatDTO};
    }

    public static Response ErrorResponse(string error)
    {
        return new Response{Type=ResponseType.ERROR,ErrorMessage=error};
    }

    public static Response CreateFilteredSpectacoleResponse(SpectacolDTO[] spectacols)
    {
        return new Response{Type=ResponseType.FILTEREDSPECTACOLE,Spectacols=spectacols};
    }

    public static Response CreateGetAllSpectacoleResponse(SpectacolDTO[] spectacols)
    {
        return new Response{Type=ResponseType.GETALLSPECTACOLE,Spectacols = spectacols };
    }

    public static Response CreateReserveBiletResponse()
    {
        return new Response { Type = ResponseType.REZERVAREBILET };
    }

    public static Response CreateLogOutResponse()
    {
        return new Response { Type = ResponseType.LOGOUT };
    }

    public static Response CreateUpdateSpectacolResponse(SpectacolDTO spectacol)
    {
        return new Response{Type=ResponseType.UPDATESPECTACOL,Spectacol=spectacol};
    }

    public static Request CreateFilteredSpectacoleRequest(DateTime date)
    {
        return new Request{Type=RequestType.FILTEREDSPECTACOLE,DateTime= date};
    }

    public static Request CreateGetAllSpectacoleRequest()
    {
        return new Request{Type=RequestType.GETALLSPECTACOLE};
    }

    public static Request CreateReserveBiletRequest(String buyer, long spectacol, int seats)
    {
        return new Request
        {
            Type = RequestType.REZERVAREBILET, 
            Int = seats, 
            Long = spectacol,
            String = buyer
        };
    }

    public static Request CreateLoginRequest(String username, String password)
    {
        return new Request
        {
            Type = RequestType.LOGIN,
            String = username,
            String2 = password
        };
    }

    public static Request CreateLogoutRequest(AngajatDTO angajatDTO)
    {
        return new Request
        {
            Type = RequestType.LOGOUT,
            Angajat = angajatDTO
        };
    }
}
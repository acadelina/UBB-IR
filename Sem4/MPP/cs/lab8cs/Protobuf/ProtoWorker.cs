using System.Collections;
using System.Net.Sockets;
using Google.Protobuf;
using Protobuf;
using Ubb.Scs.Mpp.Network;
using WinFormsApp1.Service;
using Spectacol = Domain.Spectacol;

namespace Networking.protobuf;

public class ProtoWorker:Observer
{
    private IAppService services;
    private TcpClient connection;
    private NetworkStream stream;
    private volatile bool connected;
    
    public ProtoWorker(IAppService services, TcpClient connection)
    {
        this.services = services;
        this.connection = connection;
        try
        {

	        stream = connection.GetStream();
            connected=true;
        }
        catch (Exception e)
        {
            Console.WriteLine(e.StackTrace);
        }
    }
    
    public virtual void run()
    {
        while(connected)
        {
            try
            {
                Request request =Request.Parser.ParseDelimitedFrom(stream);
                TicketResponse response =handleRequest(request);
                if (response!=null)
                {
                    sendResponse(response);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
				
            try
            {
                Thread.Sleep(1000);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }
        try
        {
            stream.Close();
            connection.Close();
        }
        catch (Exception e)
        {
            Console.WriteLine("Error "+e);
        }
    }

    private TicketResponse handleRequest(Request request)
    {
	    TicketResponse response = null;
	    Request.Types.Type reqType = request.Type;
	    switch (reqType)
	    {
		    case Request.Types.Type.Login:
		    {
			    Console.WriteLine("Login request ...");
			    Domain.Angajat user = ProtoUtils.getUser(request);
			    try
			    {
				    lock (services)
				    {
					    services.Login(user, this);
				    }

				    return ProtoUtils.createOkResponse();
			    }
			    catch (Exception e)
			    {
				    connected = false;
				    return ProtoUtils.createErrorResponse(e.Message);
			    }
		    }
		    case Request.Types.Type.Logout:
		    {
			    Console.WriteLine("Logout request");
			    Domain.Angajat user = ProtoUtils.getUser(request);
			    try
			    {
				    lock (services)
				    {
					    services.logout(user);
				    }

				    connected = false;
				    return ProtoUtils.createOkResponse();

			    }
			    catch (Exception e)
			    {
				    return ProtoUtils.createErrorResponse(e.Message);
			    }
		    }
		    case Request.Types.Type.GetShows:
		    {
			    Console.WriteLine("SendGetShowsRequest ...");

			    try
			    {
				    IEnumerable<Spectacol> spec;
				    lock (services)
				    {
					    spec = services.GetSpectacols();
				    }

				    Spectacol[] s=new Spectacol[spec.Count()];
				    int i=0;
				    foreach (Spectacol sp in spec)
				    {
					    s[i++] = sp;
				    }

				    return ProtoUtils.createGetSpectacoleResponse(s);
			    }
			    catch (Exception e)
			    {
				    return ProtoUtils.createErrorResponse(e.StackTrace);
			    }
		    }

		    case Request.Types.Type.GetFshows:
		    {
			    Console.WriteLine("GetFShows Request ...");

			    string date = request.Data;
			    try
			    {
				    IEnumerable<Spectacol> spec=new List<Spectacol>();
				    lock (services)
				    {
					    spec = services.GetSpectacolsByDate(DateTime.Parse(date));
				    }

				    Spectacol[] s = new Spectacol[spec.Count()];
				    int i = 0;
				    foreach (Spectacol sp in spec)
				    {
					    s[i++]=sp;
				    }

				    return ProtoUtils.createGetSpectacoleResponse(s);
			    }
			    catch (Exception e)
			    {
				    return ProtoUtils.createErrorResponse(e.Message);
			    }
		    }
		    case Request.Types.Type.BuyTicket:
		    {
			    Domain.Bilet bilet = ProtoUtils.getBilet(request);
			    try
			    {
				    lock (services)
				    {
					    services.AddBilet(bilet.SpectacolC.Id, bilet.SeatsNumber, bilet.Buyer);
					    
				    }

				    return ProtoUtils.createAddBiletResponse();
			    }
			    catch (Exception e)
			    {
				    return ProtoUtils.createErrorResponse(e.Message);
			    }


		    }
			   
	    } return response;
    }

    private void sendResponse(TicketResponse response)
		{
			Console.WriteLine("sending response "+response);
            //formatter.Serialize(stream, response);
            response.WriteDelimitedTo(stream);
            stream.Flush();
			
		}
	

        

    public void update(Spectacol spectacol)
    {
	    Ubb.Scs.Mpp.Network.Spectacol spec=new Ubb.Scs.Mpp.Network.Spectacol
        {
	        Artist = spectacol.Artist,
	        AvailableSeats = spectacol.AvailableSeats,
	        Date = spectacol.Date.ToString("yyyy-MM-ddTHH:mm:ss"),
	        Location = spectacol.Location,
	        SoldSeats = spectacol.SoldSeats,
	        Id = spectacol.Id,
        };
        try
        {
	        sendResponse(ProtoUtils.createUpdateBiletResponse(spec));
        }
        catch (Exception e)
        {
	        Console.WriteLine(e.Message);
        }
    }
}
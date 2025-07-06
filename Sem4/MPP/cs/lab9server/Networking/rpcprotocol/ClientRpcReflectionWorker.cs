using System.Net.Sockets;
using System.Reflection;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Text.Json;
using Domain;
using Networking.dto;
using WinFormsApp1.Service;

namespace Networking.rpcprotocol;

public class ClientRpcReflectionWorker:Observer
{
    private IAppService server;
    private TcpClient connection;
    private NetworkStream stream;
    private volatile bool connected;

    public ClientRpcReflectionWorker(IAppService server, TcpClient connection)
    {
        this.server = server;
        this.connection = connection;
        try
        {
            stream = connection.GetStream();
            connected = true;
        }
        catch (IOException e)
        {
            Console.WriteLine(e.StackTrace);
        }
    }

    public void run()
    {
        while (connected)
        {
            try
            {
                var request = ReadRequest();
                var response = HandleRequest(request);
                if (response != null)
                {
                    SendResponse(response);
                }
            }
            catch (IOException e)
            {
                Console.WriteLine(e.StackTrace);
            }
            catch (System.Runtime.Serialization.SerializationException e)
            {
                Console.WriteLine(e.StackTrace);
            }

            Thread.Sleep(1000);
        }

        try
        {
            stream.Close();
            connection.Close();
        }
        catch (IOException e)
        {
            Console.WriteLine("Error " + e);
        }
    }
    
    
    private Request ReadRequest()
    {
        using var reader = new StreamReader(stream, Encoding.UTF8, leaveOpen: true);
        string json = reader.ReadLine();
        return JsonSerializer.Deserialize<Request>(json);
    }

    private static readonly Response OkResponse = new Response.Builder().Type(ResponseType.OK).Build();

    private Response HandleRequest(Request request)
    {
        Response response = null;
        var handlerName = "Handle" + request.Type.ToString();
        Console.WriteLine("HandlerName " + handlerName);

        try
        {
            var method = this.GetType().GetMethod(handlerName, BindingFlags.NonPublic | BindingFlags.Instance);
            response = (Response)method.Invoke(this, new object[] { request });
            Console.WriteLine("Method " + handlerName + " invoked");
        }
        catch (MissingMethodException e)
        {
            Console.WriteLine(e.StackTrace);
        }
        catch (TargetInvocationException e)
        {
            Console.WriteLine(e.StackTrace);
        }
        catch (ArgumentException e)
        {
            Console.WriteLine(e.StackTrace);
        }

        return response;
    }

    private Response HandleLOGIN(Request request)
    {
        Console.WriteLine("Login request ..." + request.Type);
        var udto = (AngajatDTO)request.Data;
        var user = DTOUtils.fromAngajatDTO(udto);
        try
        {
            server.Login(user, this);
            return new Response.Builder().Type(ResponseType.OK).Build();
        }
        catch (Exception e)
        {
            connected = false;
            return new Response.Builder().Type(ResponseType.ERROR).Data(e.Message).Build();
        }
    }

    private Response HandleLOGOUT(Request request)
    {
        Console.WriteLine("Logout request...");
        var udto = (AngajatDTO)request.Data;
        var user = DTOUtils.fromAngajatDTO(udto);
        try
        {
            server.logout(user);
            connected = false;
            return new Response.Builder().Type(ResponseType.OK).Build();
        }
        catch (Exception e)
        {
            return new Response.Builder().Type(ResponseType.ERROR).Data(e.Message).Build();
        }
    }

    private Response HandleGETSPECTACOLE(Request request)
    {
        Console.WriteLine("Getting spectacole ...");
        
        try
        {
            server.GetSpectacols();
            return OkResponse;
        }
        catch (Exception e)
        {
            return new Response.Builder().Type(ResponseType.ERROR).Data(e.Message).Build();
        }
    }

    private Response HandleGETFSPECTACOLE(Request request)
    {
        Console.WriteLine("getting filtered spectacole ...");
        var data =(DateTime) request.Data;
        try
        {
            var friends = server.GetSpectacolsByDate(data);
            var frDTO = DTOUtils.getSpectacolDTOs(friends);
            return new Response.Builder().Type(ResponseType.GETFSPECTACOLE).Data(frDTO).Build();
        }
        catch (Exception e)
        {
            return new Response.Builder().Type(ResponseType.ERROR).Data(e.Message).Build();
        }
    }

    private Response HandleADDBILET(Request request)
    {
        Console.WriteLine("getting filtered spectacole ...");
        var bilet =(Bilet) request.Data;
        try
        {
             server.AddBilet(bilet.SpectacolC.Id,bilet.SeatsNumber,bilet.Buyer);
            var frDTO = DTOUtils.getSpectacolDTO(bilet.SpectacolC);
            return new Response.Builder().Type(ResponseType.ADDBILET).Data(frDTO).Build();
        }
        catch (Exception e)
        {
            return new Response.Builder().Type(ResponseType.ERROR).Data(e.Message).Build();
        }
    }

    private void SendResponse(Response response)
    {
        string json = JsonSerializer.Serialize(response);
        using var writer = new StreamWriter(stream, Encoding.UTF8, leaveOpen: true);
        writer.WriteLine(json);
        writer.Flush();
    }

    public void update(Spectacol spectacol)
    {
        var spec=DTOUtils.getSpectacolDTO(spectacol);
        try
        {
            SendResponse(new Response.Builder().Type(ResponseType.ADDBILET).Data(spec).Build());
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }
    
    }
}
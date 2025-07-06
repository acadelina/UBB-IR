using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using Domain;
using log4net;
using Networking.dto;
using WinFormsApp1.Service;

namespace Networking.jsonprotocol;

public class ClientJsonWorker:Observer
{
    private IAppService server;
    private NetworkStream stream;
    private TcpClient connection;
    private volatile bool connected;
    private static ILog log=LogManager.GetLogger(typeof(ClientJsonWorker));

    public ClientJsonWorker(IAppService server, TcpClient connection)
    {
        this.server = server;
        this.connection = connection;
        try
        {
            stream = connection.GetStream();
            connected = true;
        }
        catch (Exception e)
        {
            log.Error(e.StackTrace);
        }
    }

    public virtual void run()
    {
        using StreamReader reader=new StreamReader(stream,Encoding.UTF8);
        while (connected)
        {
            try
            {
                if (!connection.Connected)
                {
                    log.Warn("Connection is closed. Stopping the server.");
                    break;
                }
                string requestJson = reader.ReadLine();
                if (string.IsNullOrEmpty(requestJson)) continue;
                log.DebugFormat("request {0}", requestJson);
                Request request = JsonSerializer.Deserialize<Request>(requestJson);
                log.DebugFormat("request deserialized {0}", requestJson);
                Response response = handleRequest(request);
                if (response != null)
                {
                    sendResponse(response);
                }
            }
            catch (Exception e)
            {
                log.Error(e.StackTrace);
            }

            try
            {
                Thread.Sleep(1000);
            }
            catch (Exception e)
            {
                log.Error(e.StackTrace);
            }
        }

        try
        {
            stream.Close();
            connection.Close();
        }
        catch (Exception e)
        {
            log.Error(e.StackTrace);
        }
    }

    private Response handleRequest(Request request)
    {
        Response response=null;
        if (request.Type == RequestType.LOGIN)
        {
            log.InfoFormat("Handling request [{0}]", request);
            log.DebugFormat("request type {0}", request.Type);
            Angajat angajat;
            try
            {
                lock (server)
                {
                    Angajat ang = new Angajat(request.String, request.String2, "");
                    angajat = server.Login(ang, this);
                    log.InfoFormat("Sending login response: {0}", JsonSerializer.Serialize(response));
                    response=JsonProtocolUtils.CreateLoginResponse(DTOUtils.getAngajatDTO(angajat));
                }
            }
            catch (Exception e)
            {
                connected=false;
                return JsonProtocolUtils.ErrorResponse(e.Message);
            }
        }
        else if (request.Type == RequestType.GETALLSPECTACOLE)
        {
            log.DebugFormat("request type {0}", request.Type);
            try
            {
                lock (server)
                {
                    response = JsonProtocolUtils.CreateGetAllSpectacoleResponse(DTOUtils.getSpectacolDTOs(server.GetSpectacols().ToArray()));
                }
            }
            catch(Exception e)
            {
                response=JsonProtocolUtils.ErrorResponse(e.Message);
            }
        }
        else if (request.Type == RequestType.FILTEREDSPECTACOLE)
        {
            log.DebugFormat("request type {0}", request.Type);
            try
            {
                lock (server)
                {
                    var spectacole = server.GetSpectacolsByDate(request.DateTime);
                    response = JsonProtocolUtils.CreateFilteredSpectacoleResponse(DTOUtils.getSpectacolDTOs(spectacole.ToArray()));
                }
            }
            catch (Exception e)
            {
                response=JsonProtocolUtils.ErrorResponse(e.Message);
            }
        }
        else if (request.Type == RequestType.REZERVAREBILET)
        {
            log.DebugFormat("request type {0}", request.Type);
            try
            {
                var spectacol = request.Long;
                var buyer = request.String;
                var seats = request.Int;
                lock (server)
                {
                    server.AddBilet(spectacol, seats, buyer);
                    response = JsonProtocolUtils.CreateReserveBiletResponse();
                }
            }
            catch (Exception e)
            {
                response=JsonProtocolUtils.ErrorResponse(e.Message);
            }
        }
        else if (request.Type == RequestType.LOGOUT)
        {
            log.DebugFormat("request type {0}", request.Type);
            try
            {
                lock (server)
                {
                    server.logout(request.Angajat.toAngajat());
                    response = JsonProtocolUtils.CreateLogOutResponse();
                }
            }
            catch (Exception e)
            {
                response=JsonProtocolUtils.ErrorResponse(e.Message);
            }
            connected = false;
        }
        
        if(response==null)
            response=JsonProtocolUtils.ErrorResponse("No response");
        return response;
    }

    public void sendResponse(Response response)
    {
        log.Debug("send response");
        String json = JsonSerializer.Serialize(response);
        lock (stream)
        {
            byte[] data = Encoding.UTF8.GetBytes(json+"\n");
            stream.Write(data,0,data.Length);
            stream.Flush();
        }
        
    }
    public void update(Spectacol spectacol)
    {
        log.Debug("update spectacol");
        var spec=DTOUtils.getSpectacolDTO(spectacol);
        try
        {
            sendResponse(JsonProtocolUtils.CreateUpdateSpectacolResponse(spec));
        }
        catch (Exception e)
        {
            log.Error(e.StackTrace);
        }
    }
}
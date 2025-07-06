using System.Collections.Concurrent;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using Domain;
using log4net;
using Networking.dto;
using WinFormsApp1.Service;

namespace Networking.jsonprotocol;

public class ServerJsonProxy:IAppService
{
    private string host;
    private int port;

    private Observer client;

    private NetworkStream stream;
    private TcpClient connection;
    private Queue<Response> responses;
    private volatile bool finished;
    private EventWaitHandle _waitHandle;
    public ServerJsonProxy(string host, int port)
    {
        this.host = host;
        this.port = port;
        responses = new Queue<Response>();
    }

    private static ILog log = LogManager.GetLogger(typeof(ServerJsonProxy));
    
    private void closeConnection()
    {
        finished=true;
        try
        {
            stream.Close();
            connection.Close();
            _waitHandle.Close();
            client=null;
        }
        catch (Exception e)
        {
            Console.WriteLine(e.StackTrace);
        }
    }
    
    private void sendRequest(Request request)
    {
        try
        {
            lock (stream)
            {
					
                string jsonRequest = JsonSerializer.Serialize(request);
                log.DebugFormat("Sending request {0}",jsonRequest);
                byte[] data = Encoding.UTF8.GetBytes(jsonRequest + "\n"); 
                stream.Write(data, 0, data.Length);
                stream.Flush();
					
            }
        }
        catch (Exception e)
        {
            throw new Exception("Error sending object "+e);
        }

    }
    
    private Response readResponse()
    {
        Response response = null;
        try
        {
            _waitHandle.WaitOne();
            lock (responses)
            {
                response = responses.Dequeue();
                
            }
        }
        catch (InvalidOperationException e)
        {
            throw new Exception("Error reading response " + e);
        }
        if (response == null)
        {
            throw new Exception("Received null response from server.");
        }
        return response;
    }
    private void startReader()
    {
        Thread tw =new Thread(run);
        tw.Start();
    }
    
    private void initializeConnection()
    {
        try
        {
            connection=new TcpClient(host,port);
            stream=connection.GetStream();
            finished=false;
            _waitHandle = new AutoResetEvent(false);
            startReader();
        }
        catch (IOException e)
        {
            throw new Exception("Error initializing connection " + e);
        }
    }

    public virtual void run()
    {
        using StreamReader reader = new StreamReader(stream, Encoding.UTF8);
        while(!finished)
        {
            try
            {
                string responseJson = reader.ReadLine();
                if (string.IsNullOrEmpty(responseJson)) 
                    continue;
                Response response=JsonSerializer.Deserialize<Response>(responseJson);
                log.Debug("response received "+response);
                if (response.Type == ResponseType.UPDATESPECTACOL)
                {
                    handleUpdate(response);
                }
                else
                {
                    lock (responses)
                    {
                        responses.Enqueue(response);
                    }
                    _waitHandle.Set();
                }
            }
            catch (Exception e)
            {
                log.Error("Reading error "+e);
            }
					
        }
    }
    
    public Angajat Login(Angajat angajat, Observer observer)
    {
        log.Info("Login");
        try
        {
            initializeConnection();
        }
        catch (Exception e)
        {
            Console.WriteLine("Error initializing connection: " + e);
        }

        sendRequest(JsonProtocolUtils.CreateLoginRequest(angajat.Username, angajat.Password));
        var response = readResponse();
        Angajat angajat1 = null;
        if (response.Type == ResponseType.LOGIN)
        {
            this.client = observer;
            angajat1=DTOUtils.fromAngajatDTO(response.Angajat);
        }
        else if (response.Type == ResponseType.ERROR)
        {
            finished = true;
            closeConnection();
        }
        else
        {
            finished = true;
            log.Error("Something went wrong");
            closeConnection();
        }
        return angajat1;

    }

    public IEnumerable<Spectacol> GetSpectacols()
    {
        sendRequest(JsonProtocolUtils.CreateGetAllSpectacoleRequest());
        var response = readResponse();
        IEnumerable<Spectacol> spectacols = null;
        if (response.Type == ResponseType.GETALLSPECTACOLE)
        {
            spectacols = DTOUtils.fromSpectacolDTOs(response.Spectacols.ToArray());
        }
        else
        {
            log.Error("Something went wrong");
        }
        return spectacols;
    }

    public IEnumerable<Spectacol> GetSpectacolsByDate(DateTime date)
    {
        sendRequest(JsonProtocolUtils.CreateFilteredSpectacoleRequest(date));
        var response = readResponse();
        IEnumerable<Spectacol> spectacols = null;
        if (response.Type == ResponseType.FILTEREDSPECTACOLE)
        {
            spectacols= DTOUtils.fromSpectacolDTOs(response.Spectacols.ToArray());
        }
        else
        {
            log.Error("Something went wrong");
        }
        return spectacols;
    }

    public void AddBilet(long spectacolId, int seats, string name)
    {
        sendRequest(JsonProtocolUtils.CreateReserveBiletRequest(name,spectacolId,seats));
        var response = readResponse();
        if (!response.Type.Equals(ResponseType.REZERVAREBILET))
        {
            log.Error("Something went wrong");
        }
    }

    public void logout(Angajat angajat)
    {
        finished = true;
        AngajatDTO angajatDto=DTOUtils.getAngajatDTO(angajat);
        sendRequest(JsonProtocolUtils.CreateLogoutRequest(angajatDto));
        var response = readResponse();
        closeConnection();
        if (response.Type.Equals(ResponseType.ERROR))
        {
            log.Error("Something went wrong");
        }
    }

    private void handleUpdate(Response response)
    {
        if (response.Type.Equals(ResponseType.UPDATESPECTACOL))
        {
            var spect=response.Spectacol;
            try
            {
                client.update(DTOUtils.fromSpectacolDTO(spect));
            }
            catch (Exception e)
            {
                log.Error("Error updating spectacol", e);
            }
        }
    }
   
}

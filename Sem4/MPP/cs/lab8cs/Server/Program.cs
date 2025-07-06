using System.Configuration;
using System.Net.Sockets;
using System.Reflection;
using log4net;
using log4net.Config;
using Networking;
using Networking.jsonprotocol;
using Networking.protobuf;
using Networking.rpcprotocol;
using Repository;
using WinFormsApp1.Service;

namespace Server;

static class Program
{
    private static int DEFAULT_PORT=55556;
    private static String DEFAULT_IP="127.0.0.1";
    private static readonly ILog log = LogManager.GetLogger(typeof(Program));
    static void Main()
    {
           var logRepository = LogManager.GetRepository(Assembly.GetEntryAssembly());
            XmlConfigurator.Configure(logRepository, new FileInfo("log4net.config"));
			
            log.Info("Starting chat server");
           log.Info("Reading properties from app.config ...");
           int port = DEFAULT_PORT;
           String ip = DEFAULT_IP;
           String portS= ConfigurationManager.AppSettings["port"];
           if (portS == null)
           {
               log.Debug("Port property not set. Using default value "+DEFAULT_PORT);
           }
           else
           {
               bool result = Int32.TryParse(portS, out port);
               if (!result)
               {
                   log.Debug("Port property not a number. Using default value "+DEFAULT_PORT);
                   port = DEFAULT_PORT;
                   log.Debug("Portul "+port);
               }
           }
           String ipS=ConfigurationManager.AppSettings["ip"];
           
           if (ipS == null)
           {
               log.Info("Port property not set. Using default value "+DEFAULT_IP);
           }
           log.InfoFormat("Configuration Settings for database {0}",GetConnectionStringByName("festival"));
           IDictionary<String, string> props = new SortedList<String, String>();
           props.Add("ConnectionString", GetConnectionStringByName("festival"));
           AngajatRepo angajatRepo = new DbAngajatRepo(props);
           SpectacolRepo spectacolRepo = new DbSpectacolRepo(props);
           BiletRepo biletRepo=new DbBiletRepo(props,(DbSpectacolRepo)spectacolRepo);
           AngajatService angajatService=new AngajatService(angajatRepo);
           SpectacolService spectacolService=new SpectacolService(spectacolRepo);
           BiletService biletService=new BiletService(biletRepo,spectacolRepo);
           IAppService serviceImpl= new AppService(angajatService,spectacolService,biletService);
           
           log.DebugFormat("Starting server on IP {0} and port {1}", ip, port);
            JsonServer server = new JsonServer(ip,port, serviceImpl);
            server.Start();
            log.Debug("Server started ...");
            Console.ReadLine();
      
    }
    static string GetConnectionStringByName(string name)
    {
        
        string returnValue = null;
        ConnectionStringSettings settings =ConfigurationManager.ConnectionStrings[name];
        if (settings != null)
            returnValue = settings.ConnectionString;

        return returnValue;
    }
}

public class JsonServer: ConcurrentServer 
{
    private IAppService server;
    private ProtoWorker worker;
    private static readonly ILog log = LogManager.GetLogger(typeof(JsonServer));
    public JsonServer(string host, int port, IAppService server) : base(host, port)
    {
        this.server = server;
        log.Debug("Creating JsonChatServer...");
    }
    protected override Thread createWorker(TcpClient client)
    {
        worker = new ProtoWorker(server, client);
        return new Thread(worker.run);
    }
}

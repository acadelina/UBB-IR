using System.Configuration;
using System.Reflection;
using log4net;
using log4net.Config;
using Networking.jsonprotocol;
using WinFormsApp1;

namespace Client;

static class Program
{
    private static int DEFAULT_PORT=55556;
    private static String DEFAULT_IP="127.0.0.1";
    private static readonly ILog log = LogManager.GetLogger(typeof(Program));
    static void Main()
    {
        var logRepository = LogManager.GetRepository(Assembly.GetEntryAssembly());
        XmlConfigurator.Configure(logRepository, new FileInfo("log4net.config"));
        ApplicationConfiguration.Initialize();
        log.Debug("Reading properties from app.config");
        int port=DEFAULT_PORT;
        String ip=DEFAULT_IP;
        String portS=ConfigurationManager.AppSettings["port"];
        if (portS == null)
        {
            log.Debug("Port is null using default value");
        }
        else
        {
            bool result = Int32.TryParse(portS, out port);
            if (!result)
            {
                log.Debug("Port is invalid");
                port=DEFAULT_PORT;
            }
        }
        String ipS=ConfigurationManager.AppSettings["ip"];
        if (ipS == null)
        {
            log.Debug("Ip is null using default value");
        }
        log.InfoFormat("Using  server on IP {0} and port {1}", ip, port);
        IAppService server = new ServerJsonProxy(ip, port);
        Application.EnableVisualStyles();
        Application.SetCompatibleTextRenderingDefault(false);
        Application.Run(new Form1(server));
       
    }
}
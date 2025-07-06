package ubb.scs.mpp.Network.utils;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ubb.scs.mpp.Network.objectprotocol.ClientObjectWorker;
import ubb.scs.mpp.Service.AppService;
import ubb.scs.mpp.Service.IAppService;

import java.net.Socket;

public class ObjectConcurrentServer extends ConcurrentServer{

    private IAppService server;

    private static Logger logger = LogManager.getLogger(ConcurrentServer.class);

    public ObjectConcurrentServer(int port, IAppService server) {
        super(port);
        this.server = server;
        logger.info("Chat-ChatObjectConcurrentServer");
    }

    @Override
    protected Thread createWorker(Socket client) {
        ClientObjectWorker worker=new ClientObjectWorker( server, client);
        Thread tw=new Thread(worker);
        return tw;
    }
}
